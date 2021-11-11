#include <station/server.h>
#include <iostream>
#include <cstring>
#include <string>

#define MAX_MSG_SIZE 128

namespace Station {

Server::Server(const std::string &ip, uint16_t port) :
    fdListen(0),
    fdAccept(0),
    opt(1) {
    clientAddr = new sockaddr_in;
    serverAddr = new sockaddr_in;
    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htons(port);
    serverAddr->sin_addr.s_addr = INADDR_ANY;

    fdListen = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(fdListen, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
               &opt, sizeof(opt));

    if (bind(fdListen, reinterpret_cast<sockaddr*>(serverAddr), sizeof(*serverAddr)) == -1) {
        close(fdListen);
    }
}

int Server::Receive(ReceiveData* rData) {
    if (listen(fdListen, 3) == -1) {
        close(fdListen);
        return -1;
    }

    unsigned int clientSize = sizeof(*clientAddr);
    fdAccept = accept(fdListen, reinterpret_cast<sockaddr*>(clientAddr), &clientSize);
    if (fdAccept == -1) {
        std::cout << "Failed to accept connection\n";
    }

    buffer = new char[1];
    int res = recv(fdAccept, reinterpret_cast<void*>(buffer), 1, 0);
    if (res == -1)
        return -1;

    rData->id = atoi(buffer);
    delete[] buffer;

    buffer = new char[MAX_MSG_SIZE];
    rData->size = recv(fdAccept, reinterpret_cast<void*>(buffer), MAX_MSG_SIZE, 0);
    if (rData->size == -1) {
        close(fdAccept);
        close(fdListen);
        return -1;
    }

    rData->data = new char[rData->size];
    std::memcpy(rData->data, buffer, rData->size);
    Reset();
    return 0;
}

void Server::Reset() {
    delete[] buffer;
    close(fdAccept);
}
}    /*namespace Server*/
