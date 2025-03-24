packet TaskMessage {
    int clientId;
    int taskId;
    int subtaskId;
    int arrayData[];
}

packet ResultMessage {
    int clientId;
    int taskId;
    int subtaskId;
    int result;
    bool isHonest;
}

packet GossipMessage {
    string content;
    int timestamp;
    int sourceId;
}
