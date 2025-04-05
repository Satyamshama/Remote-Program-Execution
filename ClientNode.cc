// B22CS047 B22CS035
#include <omnetpp.h>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include "RemoteMessages_m.h"

using namespace omnetpp;

class ClientNode : public cSimpleModule
{
  private:
    int nodeId;
    std::string taskType;
    int numElements;
    int elementMin;
    int elementMax;
    int numServers;
    int numClients;
    int currentTaskId;
    int timestamp;
    std::ofstream outputFile;

    // Task tracking
    struct SubtaskInfo {
        int subtaskId;
        std::vector<int> array;
        std::map<int, int> results;  // server -> result
        bool completed;
    };

    std::map<int, std::vector<SubtaskInfo>> tasks;  // taskId -> subtasks
    std::map<int, int> serverScores;  // server -> score
    std::map<int, std::map<int, double>> allServerScores;  // client -> (server -> score)

    // Gossip protocol
    std::unordered_set<std::string> messageLog;  // Seen message hashes

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void setupConnections();
    void startTask(int taskId);
    void distributeTask(int taskId);
    void processResult(ResultMessage *msg);
    void finalizeTask(int taskId);
    void broadcastScores();
    void handleGossipMessage(GossipMessage *msg);
    std::string generateGossipContent();
    std::string hashMessage(const std::string& message);
    std::vector<int> generateRandomArray();
    std::vector<int> selectRandomServers(int count);
};

Define_Module(ClientNode);

void ClientNode::initialize()
{
    nodeId = par("nodeId");
    taskType = par("taskType").stdstringValue();
    numElements = par("numElements");
    elementMin = par("elementMin");
    elementMax = par("elementMax");
    currentTaskId = 0;
    timestamp = 0;

    // Open output file
    std::string filename = "client_" + std::to_string(nodeId) + ".txt";
    outputFile.open(filename);

    // Setup network connections based on topology file
    setupConnections();

    // Initialize server scores
    for (int i = 0; i < numServers; i++) {
        serverScores[i] = 0;
    }

    EV << "Client " << nodeId << " initialized" << endl;
    outputFile << "Client " << nodeId << " initialized" << endl;

    // Start first task after a small delay
    scheduleAt(simTime() + 1.0, new cMessage("startTask"));
}

void ClientNode::setupConnections()
{
    // Read topology from file
    std::ifstream topoFile("topo.txt");
    if (!topoFile.is_open()) {
        throw cRuntimeError("Cannot open topo.txt");
    }

    // Parse numClients and numServers
    std::string line;
    while (std::getline(topoFile, line) && line[0] == '#');
    std::istringstream iss(line);
    if (!(iss >> numClients >> numServers)) {
        throw cRuntimeError("Invalid topology format");
    }

    cModule *network = getParentModule();

    // Set gate sizes FIRST
    int totalGates = numServers + numClients; // Servers + clients
    setGateSize("out", totalGates);
    setGateSize("in", totalGates);

    // Connect to servers
    for (int i = 0; i < numServers; i++) {
        cModule *server = network->getSubmodule("server", i);
        if (!server) {
            EV_ERROR << "Server " << i << " not found!" << endl;
            continue;
        }

        cGate *outGate = gate("out", i);
        cGate *inGate = gate("in", i);

        cGate *serverInGate = server->gate("in", nodeId);
        cGate *serverOutGate = server->gate("out", nodeId);

        outGate->connectTo(serverInGate);
        serverOutGate->connectTo(inGate);
    }

    // Connect to other clients
    for (int i = 0; i < numClients; i++) {
        if (i != nodeId) {
            int gateIndex = numServers + i; // Separate range for client connections

            cModule *otherClient = network->getSubmodule("client", i);
            if (!otherClient) {
                EV_ERROR << "Client " << i << " not found!" << endl;
                continue;
            }

            cGate *outGate = gate("out", gateIndex);
            cGate *inGate = gate("in", gateIndex);

            cGate *otherInGate = otherClient->gate("in", numServers + nodeId);
            cGate *otherOutGate = otherClient->gate("out", numServers + nodeId);

            outGate->connectTo(otherInGate);
            otherOutGate->connectTo(inGate);
        }
    }
}


void ClientNode::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "startTask") == 0) {
        // Start a new task
        startTask(currentTaskId);
        delete msg;
    }
    else if (ResultMessage *resultMsg = dynamic_cast<ResultMessage *>(msg)) {
        // Process result from server
        processResult(resultMsg);
        delete msg;
    }
    else if (GossipMessage *gossipMsg = dynamic_cast<GossipMessage *>(msg)) {
        // Handle gossip message
        handleGossipMessage(gossipMsg);
        delete msg;
    }
}

void ClientNode::startTask(int taskId)
{
    EV << "Client " << nodeId << " starting task " << taskId << endl;
    outputFile << "Starting task " << taskId << endl;

    // Generate random array for the task
    std::vector<int> array = generateRandomArray();

    // Divide array into n subtasks
    int subtaskSize = array.size() / numServers;
    if (subtaskSize < 2) subtaskSize = 2;  // Ensure at least 2 elements per subtask

    tasks[taskId] = std::vector<SubtaskInfo>();

    for (int i = 0; i < numServers; i++) {
        int startIdx = i * subtaskSize;
        int endIdx = (i == numServers - 1) ? array.size() : (i + 1) * subtaskSize;

        if (startIdx >= array.size()) break;

        SubtaskInfo subtask;
        subtask.subtaskId = i;
        subtask.completed = false;

        // Copy elements for this subtask
        for (int j = startIdx; j < endIdx; j++) {
            subtask.array.push_back(array[j]);
        }

        tasks[taskId].push_back(subtask);
    }

    // Distribute the task
    distributeTask(taskId);
}

void ClientNode::distributeTask(int taskId)
{
    // For each subtask, select n/2 + 1 random servers
    int serversPerSubtask = numServers / 2 + 1;

    for (auto& subtask : tasks[taskId]) {
        std::vector<int> selectedServers;

        if (taskId == 0) {
            // First round: random selection
            selectedServers = selectRandomServers(serversPerSubtask);
        } else {
            // Second round: select based on scores
            // Sort servers by score
            std::vector<std::pair<int, double>> serverRankings;
            for (int i = 0; i < numServers; i++) {
                double avgScore = 0;
                int count = 0;

                for (const auto& clientScores : allServerScores) {
                    if (clientScores.second.find(i) != clientScores.second.end()) {
                        avgScore += clientScores.second.at(i);
                        count++;
                    }
                }

                if (count > 0) {
                    avgScore /= count;
                }

                serverRankings.push_back({i, avgScore});
            }

            // Sort by score (descending)
            std::sort(serverRankings.begin(), serverRankings.end(),
                     [](const auto& a, const auto& b) { return a.second > b.second; });

            // Select top n/2 + 1 servers
            for (int i = 0; i < serversPerSubtask && i < serverRankings.size(); i++) {
                selectedServers.push_back(serverRankings[i].first);
            }
        }

        // Send subtask to selected servers
        for (int serverId : selectedServers) {
            TaskMessage *taskMsg = new TaskMessage("task");
            taskMsg->setClientId(nodeId);
            taskMsg->setTaskId(taskId);
            taskMsg->setSubtaskId(subtask.subtaskId);

            // Set array data
            taskMsg->setArrayDataArraySize(subtask.array.size());
            for (int i = 0; i < subtask.array.size(); i++) {
                taskMsg->setArrayData(i, subtask.array[i]);
            }

            // Send to server
            send(taskMsg, "out", serverId);

            EV << "Client " << nodeId << " sent subtask " << subtask.subtaskId
               << " to server " << serverId << endl;
        }
    }
}

void ClientNode::processResult(ResultMessage *msg)
{
    int taskId = msg->getTaskId();
    int subtaskId = msg->getSubtaskId();
    int serverId = msg->getArrivalGate()->getIndex();
    int result = msg->getResult();
    bool isHonest = msg->isHonest();




    EV << "Client " << nodeId << " received result " << result
       << " for task " << taskId << ", subtask " << subtaskId
       << " from server " << serverId << endl;

    outputFile << "Received result " << result << " for task " << taskId
               << ", subtask " << subtaskId << " from server " << serverId
               << " (honest: " << (isHonest ? "yes" : "no") << ")" << endl;

    // Store the result
    for (auto& subtask : tasks[taskId]) {
        if (subtask.subtaskId == subtaskId) {
            subtask.results[serverId] = result;

            // Check if we have enough results to determine majority
            if (subtask.results.size() >= numServers / 2 + 1) {
                // Count occurrences of each result
                std::map<int, int> resultCounts;
                for (const auto& pair : subtask.results) {
                    resultCounts[pair.second]++;
                }

                // Find the majority result
                int majorityResult = -1;
                int maxCount = 0;
                for (const auto& pair : resultCounts) {
                    if (pair.second > maxCount) {
                        maxCount = pair.second;
                        majorityResult = pair.first;
                    }
                }

                // Mark subtask as completed
                subtask.completed = true;

                // Update server scores based on correctness
                for (const auto& pair : subtask.results) {
                    int server = pair.first;
                    int serverResult = pair.second;

                    if (serverResult == majorityResult) {
                        serverScores[server]++;
                    }
                }

                EV << "Client " << nodeId << " determined majority result "
                   << majorityResult << " for subtask " << subtaskId << endl;
                outputFile << "Majority result for subtask " << subtaskId
                           << ": " << majorityResult << endl;
            }
            break;
        }
    }

    // Check if all subtasks are completed
    bool allCompleted = true;
    for (const auto& subtask : tasks[taskId]) {
        if (!subtask.completed) {
            allCompleted = false;
            break;
        }
    }

    if (allCompleted) {
        finalizeTask(taskId);
    }
}

void ClientNode::finalizeTask(int taskId)
{
    // Compute final result (maximum of all subtask results)
    int finalResult = INT_MIN;

    for (const auto& subtask : tasks[taskId]) {
        // Find majority result for this subtask
        std::map<int, int> resultCounts;
        for (const auto& pair : subtask.results) {
            resultCounts[pair.second]++;
        }

        int majorityResult = -1;
        int maxCount = 0;
        for (const auto& pair : resultCounts) {
            if (pair.second > maxCount) {
                maxCount = pair.second;
                majorityResult = pair.first;
            }
        }

        // Update final result
        finalResult = std::max(finalResult, majorityResult);
    }

    EV << "Client " << nodeId << " completed task " << taskId
       << " with final result " << finalResult << endl;
    outputFile << "Task " << taskId << " completed. Final result: "
               << finalResult << endl;

    // Print server scores
    EV << "Server scores after task " << taskId << ":" << endl;
    outputFile << "Server scores after task " << taskId << ":" << endl;

    for (const auto& pair : serverScores) {
        EV << "Server " << pair.first << ": " << pair.second << endl;
        outputFile << "Server " << pair.first << ": " << pair.second << endl;
    }

    // Broadcast scores using gossip protocol
    broadcastScores();

    // Start next task after a delay if this was the first task
    if (taskId == 0) {
        currentTaskId++;
        scheduleAt(simTime() + 5.0, new cMessage("startTask"));
    }
}

void ClientNode::broadcastScores()
{
    // Generate gossip content with scores
    std::string content = generateGossipContent();

    // Create gossip message
    GossipMessage *gossipMsg = new GossipMessage("gossip");
    gossipMsg->setContent(content.c_str());
    gossipMsg->setTimestamp(++timestamp);
    gossipMsg->setSourceId(nodeId);

    // Add to message log
    std::string hash = hashMessage(content);
    messageLog.insert(hash);

    // Send to all connected clients
    for (int i = 0; i < numClients; i++) {
        if (i != nodeId) {
            GossipMessage *copy = gossipMsg->dup();
            send(copy, "out", numServers + i);
        }
    }

    delete gossipMsg;

    EV << "Client " << nodeId << " broadcast scores via gossip" << endl;
    outputFile << "Broadcast scores via gossip: " << content << endl;
}

void ClientNode::handleGossipMessage(GossipMessage *msg)
{
    std::string content = msg->getContent();
    int sourceId = msg->getSourceId();
    int msgTimestamp = msg->getTimestamp();

    // Check if we've seen this message before
    std::string hash = hashMessage(content);
    if (messageLog.find(hash) != messageLog.end()) {
        // Already seen this message, ignore
        return;
    }

    // Add to message log
    messageLog.insert(hash);

    EV << "Client " << nodeId << " received gossip from client " << sourceId
       << ": " << content << endl;
    outputFile << "Received gossip from client " << sourceId
               << " at time " << simTime() << ": " << content << endl;

    // Parse scores from content
    std::istringstream iss(content);
    std::string token;
    std::getline(iss, token, ':'); // timestamp
    std::getline(iss, token, ':'); // source IP
    std::getline(iss, token, ':'); // scores

    std::istringstream scoreStream(token);
    std::string scoreToken;
    std::map<int, double> clientScores;

    while (std::getline(scoreStream, scoreToken, ',')) {
        std::istringstream scoreTokenStream(scoreToken);
        std::string serverIdStr, scoreStr;
        std::getline(scoreTokenStream, serverIdStr, '=');
        std::getline(scoreTokenStream, scoreStr);

        int serverId = std::stoi(serverIdStr);
        double score = std::stod(scoreStr);

        clientScores[serverId] = score;
    }

    // Store scores from this client
    allServerScores[sourceId] = clientScores;

    // Forward to other clients
    for (int i = 0; i < numClients; i++) {
        if (i != nodeId && i != sourceId) {
            GossipMessage *copy = msg->dup();
            send(copy, "out", numServers + i);
        }
    }
}

std::string ClientNode::generateGossipContent()
{
    std::ostringstream oss;

    // Format: <timestamp>:<nodeId>:<server1=score1,server2=score2,...>
    oss << timestamp << ":" << nodeId << ":";

    bool first = true;
    for (const auto& pair : serverScores) {
        if (!first) oss << ",";
        oss << pair.first << "=" << pair.second;
        first = false;
    }

    return oss.str();
}

std::string ClientNode::hashMessage(const std::string& message)
{
    // Simple hash function for message deduplication
    // In a real implementation, use a proper hash function
    return message;
}

std::vector<int> ClientNode::generateRandomArray()
{
    std::vector<int> array;
    int size = numElements;

    for (int i = 0; i < size; i++) {
        array.push_back(intuniform(elementMin, elementMax));
    }

    return array;
}

std::vector<int> ClientNode::selectRandomServers(int count)
{
    std::vector<int> servers;
    std::vector<int> allServers;

    // Create list of all servers
    for (int i = 0; i < numServers; i++) {
        allServers.push_back(i);
    }

    // Randomly select count servers
    int remaining = std::min(count, (int)allServers.size());
    while (remaining > 0) {
        int idx = intuniform(0, allServers.size() - 1);
        servers.push_back(allServers[idx]);
        allServers.erase(allServers.begin() + idx);
        remaining--;
    }

    return servers;
}
