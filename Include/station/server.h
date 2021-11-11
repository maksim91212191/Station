#ifndef SERVER_H
#define SERVER_H

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <station/resources.h>

namespace Station {

class Server {
 public:
    Server(const std::string& ip, uint16_t port);
    int Receive(ReceiveData* dataBuf);
    void Close();
private:

    void Reset();

    sockaddr_in*    serverAddr;
    sockaddr_in*    clientAddr;
    int             fdListen;
    int             fdAccept;
    int             opt;
    char*           buffer;
};
} /* namespace Station */

#endif
