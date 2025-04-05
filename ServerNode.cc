// B22CS047 B22CS035
#include <omnetpp.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "RemoteMessages_m.h"

using namespace omnetpp;

class ServerNode : public cSimpleModule
{
  private:
    int nodeId;
    double maliciousProbability;
    std::ofstream outputFile;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    int findMax(const std::vector<int>& array, bool beHonest);
    void logResult(int taskId, int subtaskId, int result, bool isHonest);
};

Define_Module(ServerNode);

void ServerNode::initialize()
{
    nodeId = par("nodeId");
    maliciousProbability = par("maliciousProbability");

    // Validate gate sizes
    EV << "Server " << nodeId << " initialized with gate sizes - in: "
       << gateSize("in") << ", out: " << gateSize("out") << endl;

    if (gateSize("in") == 0 || gateSize("out") == 0) {
        throw cRuntimeError("Gate sizes for ServerNode (id=%d) are not properly set!", nodeId);
    }

    // Open output file
    std::string filename = "server_" + std::to_string(nodeId) + ".txt";
    outputFile.open(filename);

    EV << "Server " << nodeId << " initialized" << endl;
}


void ServerNode::handleMessage(cMessage *msg)
{
    if (TaskMessage *taskMsg = dynamic_cast<TaskMessage *>(msg)) {
        // Process the task
        int clientId = taskMsg->getClientId(); // Declare clientId once
        int taskId = taskMsg->getTaskId();
        int subtaskId = taskMsg->getSubtaskId();

        // Extract array data
        int arraySize = taskMsg->getArrayDataArraySize();
        std::vector<int> array(arraySize);
        for (int i = 0; i < arraySize; i++) {
            array[i] = taskMsg->getArrayData(i);
        }

        // Decide whether to be honest or malicious
        bool beHonest = (uniform(0, 1) > maliciousProbability);

        // Compute result
        int result = findMax(array, beHonest);

        // Log the result
        logResult(taskId, subtaskId, result, beHonest);

        // Create and send result message
        ResultMessage *resultMsg = new ResultMessage("result");
        resultMsg->setClientId(clientId); // Use clientId here without redeclaring
        resultMsg->setTaskId(taskId);
        resultMsg->setSubtaskId(subtaskId);
        resultMsg->setResult(result);
        resultMsg->setIsHonest(beHonest);

        // Send back to the client using correct gate index
        send(resultMsg, "out", clientId);

        delete msg;
    }
}


int ServerNode::findMax(const std::vector<int>& array, bool beHonest)
{
    if (array.empty()) return -1;

    if (beHonest) {
        // Honest behavior: return actual maximum
        return *std::max_element(array.begin(), array.end());
    } else {
        // Malicious behavior: return incorrect maximum
        int maxVal = *std::max_element(array.begin(), array.end());
        return (maxVal > 0) ? maxVal - 1 : maxVal + 1;
    }
}

void ServerNode::logResult(int taskId, int subtaskId, int result, bool isHonest)
{
    std::string status = isHonest ? "honest" : "malicious";
    EV << "Server " << nodeId << " computed result for task " << taskId
       << ", subtask " << subtaskId << ": " << result << " (" << status << ")" << endl;

    outputFile << "Task " << taskId << ", Subtask " << subtaskId
               << ": Result = " << result << " (" << status << ")" << endl;
}
