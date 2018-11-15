#include <iostream>
#include <sqlite3.h>
#include <string>
#ifndef TIMESERVER_V3_DATABASE_H
#define TIMESERVER_V3_DATABASE_H


class Database {
private:
    sqlite3 *db;
    sqlite3_stmt* stmt;
    int rc;

public:
    Database(std::string filename);
    ~Database();
    std::string execute(std::string sql);
};

#endif //TIMESERVER_V3_DATABASE_H
