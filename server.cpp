#include "tcpserver.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
    TcpServer server;
    server.listen("127.0.0.1", 5000);

    getchar();
}

