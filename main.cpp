#include <iostream>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/algorithm/string.hpp>

int main() {
    std::string timezone = "Europe/Moscow";
    boost::local_time::tz_database tz_db;
    tz_db.load_from_file("../tzdb");
    boost::local_time::time_zone_ptr tz = tz_db.time_zone_from_region(timezone);

    boost::local_time::local_date_time time = boost::local_time::local_sec_clock::local_time(tz);


/*  boost::posix_time::ptime timeUTC = boost::posix_time::second_clock::universal_time();
    boost::local_time::time_zone_ptr tz = tz_db.time_zone_from_region(timezone);
    boost::local_time::local_date_time time(timeUTC, tz);
*/


    std::cout << time.time_of_day().hours() << " " << time.time_of_day().minutes() << std::endl;

    return 0;
}