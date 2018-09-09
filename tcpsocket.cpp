#include "tcpsocket.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

TcpSocket::TcpSocket()
    :AbstractSocket()
{
    m_iScoketID = socket(AF_INET, SOCK_STREAM, 0);
    if (m_iScoketID == 0){
        std::cout<<"socket failed";
        return;
    }
}
TcpSocket::TcpSocket(int socketId)
    :AbstractSocket(socketId)
{
}
TcpSocket::~TcpSocket()
{

}
void TcpSocket::connect(std::string const& host, int port)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if(inet_pton(AF_INET, host.c_str(), &serv_addr.sin_addr)<=0){
        std::cout<<" Invalid address Address not supported";
        connected = false;
        return;
    }

    if (::connect(m_iScoketID, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        std::cout<<"Connection Failed";
        connected = false;
        return;
    }
    connected = true;
}
