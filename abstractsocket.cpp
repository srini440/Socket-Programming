#include "abstractsocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

AbstractSocket::AbstractSocket()
{
    m_iScoketID = 0;
    connected = false;
}

AbstractSocket::AbstractSocket(int socketId)
    :m_iScoketID(socketId)
{
    connected = true;
}

AbstractSocket::~AbstractSocket()
{

}
void AbstractSocket::write(std::string const& msg)
{
    ::write(m_iScoketID , msg.c_str() , msg.length());
}
//TODO: Need to handle runtime strins, for demo hardcoded
void AbstractSocket::read(std::string& msg)
{
    char buffer[10000];
    int readcount = ::read( m_iScoketID , buffer, 10000);
    buffer[readcount] = '\0';
    std::cout<<buffer<<std::flush;
    msg = buffer;
}
bool AbstractSocket::isConnected()
{
    return connected;
}
