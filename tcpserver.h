#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <pthread.h>
#include <string.h>
#include <iostream>

class TcpServer
{
public:
    TcpServer();
    ~TcpServer();
    bool listen(std::string const& host, int port);
    static int maxConnectionRequests;
    static int numConnections;
    static int serverFD;
    static void* listening(void*);
    static void *handlerNewConnection(void *);

private:
    pthread_t mThread;
};

#endif // TCPSERVER_H
