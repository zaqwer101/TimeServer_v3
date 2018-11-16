#include <cstring>
#include "Connection.h"
// #include "Server.cpp"

Connection::Connection(int sock, std::shared_ptr<Database> db)
{
    this->sock = sock;
    terminator = 1;
    thread = std::thread([this] {connection_handler(); });
    this->db = db;
    thread.detach();
}

std::string Connection::execInOS(std::string command)
{
    char buffer[128];
    std::string result = "";
    FILE *stream = popen(command.c_str(), "r");

    while (!feof(stream)) {
        if (fgets(buffer, 128, stream) != NULL)
            result += buffer;
    }
    pclose(stream);
    return result;
}

std::string Connection::getTime(std::string timezone)
{
    mutex.lock();
    std::string tz = db->execute("select timezone from timezone where abbrev=\"" + timezone + "\"");
    mutex.unlock();

    std::string command = "TZ=\"" + tz + "\" date";
    return execInOS(command);
}

void Connection::connection_handler()
{
    char buf[128];
    int bytes_read = 0;
    while(sock && terminator > 0)
    {
        std::memset(buf, 0, sizeof(buf)); // Очистка буфера
        bytes_read = recv(sock, buf, 1024, 0);
        if (bytes_read <= 0) break;
        std::string recv_string(buf);
        recv_string.erase(recv_string.find("\r\n"), 2); // Потому что в recv_string прилетают лишние служебные символы
        std::string send_string = getTime(recv_string);
        send(sock, send_string.c_str(), send_string.size(), 0);
    }
    close(sock);
    terminate();
    std::cout << "Connection stopped; " << std::endl;
}

void Connection::terminate()
{
    this->terminator = -1;
}

int Connection::isActive()
{
    return terminator > 0;
}