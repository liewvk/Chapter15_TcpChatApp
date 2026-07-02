# TCP Chat Application

A simple yet effective TCP-based chat application built in C++ for multi-client communication over a network.

## Overview

This project implements a network chat application using TCP sockets, allowing multiple clients to connect to a central server and exchange messages in real-time.

## Features

- **Multi-client Support**: Handle multiple client connections simultaneously
- **TCP-based Communication**: Reliable message delivery using TCP protocol
- **Real-time Messaging**: Send and receive messages instantly
- **Client-Server Architecture**: Centralized server managing all connections

## Project Structure

- **Server**: TCP server component handling client connections and message routing
- **Client**: TCP client component for user connections and messaging

## Technologies

- **Language**: C++ (93.8%)
- **Build System**: CMake (6.2%)

## Building

The project uses CMake for building. To build the application:

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Starting the Server

```bash
./server [port]
```

### Connecting a Client

```bash
./client [host] [port]
```

Replace `[host]` with the server's IP address or hostname, and `[port]` with the port number the server is listening on.

## Requirements

- C++11 or later
- CMake 3.0 or later
- Standard socket libraries (platform-dependent)

## License

This project is provided as-is for educational purposes.

## Author

liewvk
