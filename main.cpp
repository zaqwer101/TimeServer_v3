#include <iostream>
#include "Database.h"
#include <memory>
#include "Server.h"


static std::unique_ptr<Server> server;

static void signalHandler(int signal)
{
    server->stop();
}

int main()
{
    auto db = std::make_shared<Database>("../timezone.db");
    static auto server = std::make_unique<Server>(db, 3229);
    std::signal(SIGTERM, signalHandler);
    server->start();
    return 0;
}

