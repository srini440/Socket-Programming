#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H

#include <string.h>
#include <iostream>


class AbstractSocket
{
public:
    AbstractSocket();
    AbstractSocket(int socketId);
    virtual ~AbstractSocket();
    virtual void write(std::string const& msg);
    virtual void read(std::string& msg);
    virtual bool isConnected();

protected:
    int m_iScoketID;
    bool connected;

};

#endif // ABSTRACTSOCKET_H
