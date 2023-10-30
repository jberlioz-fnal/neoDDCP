cmake_minimum_required(VERSION 3.16)
project(neoInstrumentation)

set(CMAKE_CXX_STANDARD 11)

add_executable(publisher publisher.cpp)
add_executable(client subscriber.cpp)
target_link_libraries(publisher zmq)
target_link_libraries(client zmq)
