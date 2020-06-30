cmake_minimum_required(VERSION 3.10)
project(epoll)

set(CMAKE_CXX_STANDARD 11)

#add_executable(epoll epoll0_server.cpp)

add_executable(epoll epoll0_client.cpp reactor01.cpp lib/channel_map.h lib/channel_map.cpp)