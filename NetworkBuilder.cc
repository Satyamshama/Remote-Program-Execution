#include <omnetpp.h>
#include <fstream>
#include <sstream>

using namespace omnetpp;
using namespace std;

class NetworkBuilder : public cSimpleModule
{
  protected:
    virtual void initialize() override;
};

Define_Module(NetworkBuilder);

void NetworkBuilder::initialize()
{
    // Read topology from file
    ifstream topoFile("topo.txt");
    string line;
    int numClients, numServers;

    // Skip comments
    while (std::getline(topoFile, line)) {
        if (line[0] != '#') break;
    }

    // Parse number of clients and servers
    istringstream iss(line);
    iss >> numClients >> numServers;

    // Create network
    cModuleType *networkType = cModuleType::get("remoteexecution.RemoteExecutionNetwork");
    cModule *network = networkType->create("network", nullptr);

    // Set parameters
    network->par("numClients") = numClients;
    network->par("numServers") = numServers;

    // Build the network
    network->buildInside();
    network->callInitialize();

    EV << "Network built with " << numClients << " clients and "
       << numServers << " servers" << endl;
}
