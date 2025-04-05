// B22CS047 B22CS035
#include <omnetpp.h>
#include <fstream>
#include <sstream>

using namespace omnetpp;

class NetworkBuilder : public cSimpleModule
{
  protected:
    virtual void initialize() override;
};

Define_Module(NetworkBuilder);

void NetworkBuilder::initialize()
{
    // Read topology from file
    std::ifstream topoFile("topo.txt");
    if (!topoFile.is_open()) {
        throw cRuntimeError("Failed to open topo.txt!");
    }

    int numClients, numServers;
    if (!(topoFile >> numClients >> numServers)) {
        throw cRuntimeError("Invalid format in topo.txt!");
    }

    // Create client modules
    cModuleType *clientType = cModuleType::get("remoteexecution.ClientNode");
    for (int i = 0; i < numClients; i++) {
        cModule *client = clientType->create("client", getParentModule(), i);
        if (!client) throw cRuntimeError("Failed to create client %d", i);
        client->par("nodeId") = i;
        client->finalizeParameters();
        client->buildInside();
    }

    // Create server modules
    cModuleType *serverType = cModuleType::get("remoteexecution.ServerNode");
    for (int i = 0; i < numServers; i++) {
        cModule *server = serverType->create("server", getParentModule(), i);
        if (!server) throw cRuntimeError("Failed to create server %d", i);
        server->par("nodeId") = i;
        server->finalizeParameters();
        server->buildInside();
    }

    // Set gate sizes for clients and servers
    for (int i = 0; i < numClients; i++) {
        cModule *client = getParentModule()->getSubmodule("client", i);
        client->setGateSize("out", numServers + numClients - 1); // Servers + other clients
        client->setGateSize("in", numServers + numClients - 1);  // Servers + other clients
    }

    for (int i = 0; i < numServers; i++) {
        cModule *server = getParentModule()->getSubmodule("server", i);
        server->setGateSize("in", numClients);
        server->setGateSize("out", numClients);
    }

    // Connect clients to servers
    for (int i = 0; i < numClients; i++) {
        cModule *client = getParentModule()->getSubmodule("client", i);
        for (int j = 0; j < numServers; j++) {
            cModule *server = getParentModule()->getSubmodule("server", j);
            client->gate("out", j)->connectTo(server->gate("in", i));
            server->gate("out", i)->connectTo(client->gate("in", j));
        }
    }

    // Connect clients to other clients
    for (int i = 0; i < numClients; i++) {
        cModule *clientA = getParentModule()->getSubmodule("client", i);
        for (int j = 0; j < numClients; j++) {
            if (i != j) {
                cModule *clientB = getParentModule()->getSubmodule("client", j);
                int gateIndex = numServers + (j < i ? j : j - 1);
                clientA->gate("out", gateIndex)->connectTo(clientB->gate("in", numServers + (i < j ? i : i - 1)));
            }
        }
    }

    // Debug output
    for (int i = 0; i < numClients; i++) {
        cModule *client = getParentModule()->getSubmodule("client", i);
        EV << "Client " << i << " gate sizes - in: " << client->gateSize("in")
           << ", out: " << client->gateSize("out") << endl;
    }

    for (int i = 0; i < numServers; i++) {
        cModule *server = getParentModule()->getSubmodule("server", i);
        EV << "Server " << i << " gate sizes - in: " << server->gateSize("in")
           << ", out: " << server->gateSize("out") << endl;
    }

    // Initialize all modules
    for (int i = 0; i < numClients; i++) {
        getParentModule()->getSubmodule("client", i)->callInitialize();
    }
    for (int i = 0; i < numServers; i++) {
        getParentModule()->getSubmodule("server", i)->callInitialize();
    }
}
