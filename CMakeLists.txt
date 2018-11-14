cmake_minimum_required(VERSION 3.9)
project(TimeServer_v3)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
FIND_PACKAGE(Boost REQUIRED date_time locale)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(TimeServer_v3 main.cpp)
target_link_libraries(TimeServer_v3 ${Boost_LIBRARIES})
