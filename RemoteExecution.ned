

simple ServerNode
{
    parameters:
        int nodeId;
        double maliciousProbability = default(0.2); // Probability of being malicious
    gates:
        input in[];
        output out[];
}

simple ClientNode
{
    parameters:
        int nodeId;
        string taskType = default("findMax");
        int numElements = default(100);
        int elementMin = default(0);
        int elementMax = default(1000);
    gates:
        input in[];
        output out[];
}

network RemoteExecutionNetwork
{
    parameters:
        int numClients = default(3);
        int numServers = default(5);
    submodules:
        client[numClients]: ClientNode {
            parameters:
                nodeId = index;
        }
        server[numServers]: ServerNode {
            parameters:
                nodeId = index;
        }
    connections allowunconnected:
        // Connections will be set up dynamically in initialize()
}
