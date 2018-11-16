#include "Server.h"

Server::Server(std::shared_ptr<Database> db, int port)
{
    terminator = 1;
    this->db = db;
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_listener = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(this->sock_listener, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) < 0)
    {
        std::cout << "Can't bind socket" << std::endl;
        exit(1);
    }
}

void Server::addConnection(std::unique_ptr<Connection> connection)
{
    connections.push_back(std::move(connection));
}

void Server::removeConnection(std::unique_ptr<Connection> connection)
{
    connection->terminate();
    connections.erase(std::remove(connections.begin(), connections.end(), connection),connections.end());
}

void Server::removeConnection(int index)
{
    connections[index]->terminate();
    connections.erase(connections.begin() + index);
}

void Server::start()
{
    listen(this->sock_listener, 10);
    while(sock_listener && terminator > 0)
    {
        removeDeadConnections();
        sock = accept(sock_listener, NULL, NULL);
        auto connection = std::make_unique<Connection>(sock, db);
        this->addConnection(std::move(connection));
        std::cout << "Currently " << connections.size() << " connections; " << std::endl;
    }
    stop();
}

void Server::stop()
{
    terminator = -1;
    for(int i = 0; i < connections.size(); i++)
    {
        removeConnection(i);
    }
    std::cout << "Server stopped; " << std::endl;
}

void Server::removeDeadConnections()
{
    for(int i = 0; i < connections.size(); i++)
    {
        if(!connections[i]->isActive())
        {
            removeConnection(i);
            i--;
        }
    }

}




