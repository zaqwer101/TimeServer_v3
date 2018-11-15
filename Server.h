#ifndef TIMESERVER_V3_SERVER_H
#define TIMESERVER_V3_SERVER_H

#include <algorithm>
#include <vector>
#include "Connection.h"
#include <csignal>

class Server
{
private:
    int terminator;
    std::shared_ptr<Database> db;
    int sock, sock_listener;
    std::vector<std::unique_ptr<Connection>> connections;
    void removeDeadConnections();
    void addConnection(std::unique_ptr<Connection> connection);
    void removeConnection(int index);
    void removeConnection(std::unique_ptr<Connection> connection);

public:
    Server(std::shared_ptr<Database> db, int port);

    void start();

    void stop();
};
#endif //TIMESERVER_V3_SERVER_H


