#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

int main()
{
    const char* serverIp = "127.0.0.1";
    const int port = 54000;
    const int bufferSize = 4096;

    WSADATA wsaData;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        std::cout << "WSAStartup failed." << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Error: Could not create client socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    result = inet_pton(AF_INET, serverIp, &serverAddress.sin_addr);

    if (result <= 0)
    {
        std::cout << "Error: Invalid server IP address." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    result = connect(
        clientSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    );

    if (result == SOCKET_ERROR)
    {
        std::cout << "Error: Could not connect to server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    char buffer[bufferSize];

    while (true)
    {
        std::string message;

        std::cout << std::endl;
        std::cout << "You: ";
        std::getline(std::cin, message);

        send(
            clientSocket,
            message.c_str(),
            static_cast<int>(message.size()),
            0
        );

        if (message == "exit")
        {
            std::cout << "Disconnected from server." << std::endl;
            break;
        }

        ZeroMemory(buffer, bufferSize);

        int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);

        if (bytesReceived <= 0)
        {
            std::cout << "Server disconnected." << std::endl;
            break;
        }

        std::string serverReply(buffer, bytesReceived);

        std::cout << "Server: " << serverReply << std::endl;

        if (serverReply == "exit")
        {
            std::cout << "Server ended the chat." << std::endl;
            break;
        }
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
