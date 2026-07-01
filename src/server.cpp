#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

int main()
{
    const int port = 54000;
    const int bufferSize = 4096;

    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        std::cout << "WSAStartup failed." << std::endl;
        return 1;
    }

    SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listeningSocket == INVALID_SOCKET)
    {
        std::cout << "Error: Could not create listening socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    result = bind(
        listeningSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    );

    if (result == SOCKET_ERROR)
    {
        std::cout << "Error: Could not bind socket to port." << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    result = listen(listeningSocket, SOMAXCONN);

    if (result == SOCKET_ERROR)
    {
        std::cout << "Error: Could not listen on socket." << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server started on port " << port << "." << std::endl;
    std::cout << "Waiting for client connection..." << std::endl;

    SOCKET clientSocket = accept(listeningSocket, nullptr, nullptr);

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Error: Could not accept client connection." << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected." << std::endl;

    char buffer[bufferSize];

    while (true)
    {
        ZeroMemory(buffer, bufferSize);

        int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);

        if (bytesReceived <= 0)
        {
            std::cout << "Client disconnected." << std::endl;
            break;
        }

        std::string clientMessage(buffer, bytesReceived);

        std::cout << std::endl;
        std::cout << "Client: " << clientMessage << std::endl;

        if (clientMessage == "exit")
        {
            std::cout << "Client ended the chat." << std::endl;
            break;
        }

        std::string reply;

        std::cout << "You: ";
        std::getline(std::cin, reply);

        send(
            clientSocket,
            reply.c_str(),
            static_cast<int>(reply.size()),
            0
        );

        if (reply == "exit")
        {
            std::cout << "Server ended the chat." << std::endl;
            break;
        }
    }

    closesocket(clientSocket);
    closesocket(listeningSocket);
    WSACleanup();

    return 0;
}
