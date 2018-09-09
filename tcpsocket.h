#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "abstractsocket.h"
#include <string.h>

class TcpSocket : public AbstractSocket
{
public:
    TcpSocket();
    TcpSocket(int socketId);
    ~TcpSocket();
    void connect(std::string const& host, int port);
};

#endif // TCPSOCKET_H
