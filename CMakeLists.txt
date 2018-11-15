cmake_minimum_required(VERSION 3.9)
project(TimeServer_v3)

set(CMAKE_CXX_STANDARD 17)

add_executable(TimeServer_v3 main.cpp Database.cpp Database.h)
target_link_libraries(TimeServer_v3 -lsqlite3)
