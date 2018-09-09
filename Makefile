all:	TcpClient TcpServer
clean:
	rm -f obj/*.o TcpClient TcpServer

SRCS=\
  client.cpp \
  tcpsocket.cpp \
  abstractsocket.cpp \
  tcpserver.cpp

INCPATH=\
  -I. \
  -I/usr/include/libxml2 \
  -I/usr/lib/x86_64-linux-gnu/

CXXFLAGS	= -Wno-attributes -Wall -Wextra -g $(INCPATH)
LDLIBS	= -lxml2 -lpthread

OBJDIR	= obj
OBJS:=$(patsubset %.cpp, $(OBJDIR)/%.o $(notdir $(SRCS)))

$(OBJDIR)/%.o : %.cpp $(wildcard *.h)
	mkdir -p $(OBJDIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

TcpClient: obj/client.o obj/abstractsocket.o obj/tcpsocket.o
	$(CXX) obj/client.o obj/abstractsocket.o obj/tcpsocket.o -o $@
TcpServer: obj/server.o obj/abstractsocket.o obj/tcpsocket.o obj/tcpserver.o
	$(CXX) obj/server.o obj/abstractsocket.o obj/tcpsocket.o obj/tcpserver.o $(LDLIBS) -o $@
