#include "tcpserver.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <libxml/parser.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <libxml/tree.h>
#include "tcpsocket.h"


int TcpServer::maxConnectionRequests = 5;
int TcpServer::numConnections = 5;
int TcpServer::serverFD = 0;
typedef void * (*ThreadFunctionPointer)(void *);
TcpServer::TcpServer()
{
    numConnections = 0;
    int opt = 1;
    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFD == 0){
        std::cout<<"socket failed";
        return;
    }
    if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        std::cout<<"setsockoptfailed ";
        return;
    }
}

TcpServer::~TcpServer()
{

}

bool TcpServer::listen(std::string const& host, int port)
{
    struct sockaddr_in address, *pAddress;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );

    if (bind(serverFD, (struct sockaddr *)&address, sizeof(address))<0){
        std::cout<<"bind failed";
        return false;
    }

    if (::listen(serverFD, maxConnectionRequests) < 0) {
        std::cout<<"listen failed";
        return false;
    }

    pAddress = (struct sockaddr_in *)malloc(sizeof (struct sockaddr_in));
    *pAddress = address;
    if( pthread_create( &mThread , NULL ,  (ThreadFunctionPointer)&TcpServer::listening , (void*)&pAddress) < 0)
    {
        std::cout<<"pthread_create failed";;
        return false;
    }

    return true;
}

void* TcpServer::listening(void *sockaddress)
{
    struct sockaddr_in address = *(struct sockaddr_in *)sockaddress;
    int addrlen = sizeof(address);
    while(true && numConnections < maxConnectionRequests) {
        int socket, *newSocket;
        if ((socket = accept(serverFD, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0){
            std::cout<<"accept";
            continue;
        }
        numConnections++;
        pthread_t pthread;
        newSocket = (int*)malloc(sizeof *newSocket);
        *newSocket = socket;

        if( pthread_create( &pthread , NULL , (ThreadFunctionPointer) &TcpServer::handlerNewConnection , (void*) newSocket) < 0){
            std::cout<<"failed to handlerNewConnection";
        }
    }
    //free(sockaddress);
    pthread_exit(NULL);
}
void* TcpServer::handlerNewConnection(void *socket_desc)
{
    int socketId = *(int*)socket_desc;
    TcpSocket socket(socketId);
    std::string msg;

    socket.read(msg);

    xmlDocPtr doc = xmlParseDoc((const xmlChar*)msg.c_str());
    xmlNodePtr cur;
    if (doc == NULL) {
        std::cout<<"Invalid input data. \n";
        const char * str = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
            "<status res=\"Invalid input data\">\n"
            "</status>";
        socket.write(str);
        free(socket_desc);
        close(socketId);
        pthread_exit(NULL);
    }
    cur = xmlDocGetRootElement(doc);
    if (cur)
        cur = cur->xmlChildrenNode;

    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"event"))) {
            xmlChar *eventName = xmlGetProp(cur, (const xmlChar*)"name");

            //handling events here
            if ((!xmlStrcmp(eventName, (const xmlChar *)"Launch Video")))
            {
                //emit signal to launch video
            }
            else if ((!xmlStrcmp(eventName, (const xmlChar *)"Close Video")))
            {
                //emit signal to close video
            }
            //.....
        }
        cur = cur->next;
    }
    const char * str = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
            "<status res=\"Completed\">\n"
            "</status>";
    socket.write(str);
    free(socket_desc);
    close(socketId);
    pthread_exit(NULL);
}
