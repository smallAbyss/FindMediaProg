cmake_minimum_required(VERSION 3.10)
project(MediaScanner VERSION 4.2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

add_executable(scanner scp.cpp)

target_link_libraries(scanner 
    stdc++fs        # for std::filesystem
    pthread         # for std::this_thread::sleep_for
)