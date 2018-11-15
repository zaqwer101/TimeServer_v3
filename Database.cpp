#include "Database.h"

Database::Database(std::string filename)
{
    rc = sqlite3_open(filename.c_str(), &db);
}

std::string Database::execute(std::string sql)
{
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    sqlite3_step(stmt); // Нужна только одна запись

    auto result = sqlite3_column_text(stmt, 0);
    if (result != NULL)
    {
        std::string data = std::string(reinterpret_cast<const char *>(result));
        sqlite3_finalize(stmt);
        return data;
    } else
    {
        sqlite3_finalize(stmt);
        return "";
    }
}

Database::~Database()
{
    sqlite3_close(db);
}