

simple ServerNode
{
    parameters:
        int nodeId;
        double maliciousProbability = default(0.2); // Probability of being malicious
    gates:
        input in[];  // Will be dynamically sized
        output out[]; // Will be dynamically sized
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
        input in[];  // Will be dynamically sized
        output out[]; // Will be dynamically sized
}

network RemoteExecutionNetwork
{
    parameters:
        int numClients @prompt("Number of client nodes");
        int numServers @prompt("Number of server nodes");
    
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
        // Connections will be set up programmatically via NetworkBuilder
}
