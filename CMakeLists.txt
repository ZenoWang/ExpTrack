cmake_minimum_required(VERSION 3.12)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp src/Monitor.cpp src/Monitor.h src/DataTrack.cpp src/DataTrack.h src/HandleData.cpp src/HandleData.h lib/Encrypt.cpp lib/Encrypt.h lib/cJSON.cpp lib/cJSON.h)

target_link_libraries(untitled tomcrypt)