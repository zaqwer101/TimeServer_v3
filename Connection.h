#ifndef TIMESERVER_V3_CONNECTION_H
#define TIMESERVER_V3_CONNECTION_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>
#include "Database.h"
class Server;
class Connection
{
private:
    int terminator;
    std::mutex mutex;
    int sock;
    std::thread thread;
    std::string execInOS(std::string command);
    std::string getTime(std::string timezone);
    void connection_handler();
    std::shared_ptr<Database> db;

public:
    Connection(int sock, std::shared_ptr<Database> db);
    void terminate();
    int isActive(); // Активен ли поток подключения
};


#endif //TIMESERVER_V3_CONNECTION_H
