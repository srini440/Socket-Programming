#include "tcpsocket.h"
#include <stdio.h>

int main(int argc, char* argv[])
{

    TcpSocket socket;
    socket.connect("127.0.0.1", 5000);
    const char * str = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
            "<event name=\"Launch Video\"><url>video</url>\n"
            "</event>";

    socket.write(str);

    std::string msg;
    socket.read(msg);
    getchar();
}

