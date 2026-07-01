cmake_minimum_required(VERSION 3.20)

project(Chapter15_TcpChatApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ChatServer
    src/server.cpp
)

add_executable(ChatClient
    src/client.cpp
)

if (WIN32)
    target_link_libraries(ChatServer PRIVATE ws2_32)
    target_link_libraries(ChatClient PRIVATE ws2_32)
endif()
