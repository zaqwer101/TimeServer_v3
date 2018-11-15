#include <iostream>
#include "Database.h"
#include <memory>
#include <ctime> // Для профилирования
int main() {

    std::string filename = "../timezone.db";
    std::string timezone = "IRKT";
    std::string sql = "select timezone from timezone where abbrev=\""+ timezone +"\"";
    std::string result;
    unsigned int start_time, end_time, full_start_time, full_end_time;
    auto db = std::make_unique<Database>(filename);

    full_start_time = clock();
    for(int i = 0; i < 1000; i++) {
        start_time = clock();
        result = db->execute(sql);
        end_time = clock();
        std::cout << result << ": " << end_time - start_time << std::endl;
    }
    full_end_time = clock();
    std::cout << "Full time: " << full_end_time - full_start_time << std::endl;

    return 0;
}