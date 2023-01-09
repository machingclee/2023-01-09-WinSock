#pragma once
#include <WS2tcpip.h>
#include <iostream>
#include <sstream>
using namespace std;

class TcpListener {
public:
    TcpListener(const char* ipAddress, int port);
    int init(); // initialize the listener
    int run();  // run the listener

protected:
    virtual void onClientConnected(int clientSocket) = 0;                              // handler for client connection
    virtual void onClientDisconnected(int clientSocket) = 0;                           // handler for client disconnection
    virtual void onMessageReceived(int currSock, char* buffer, int bytesReceived) = 0; // handler for received message
    void sendToClient(int clientSocket, const char* msg, int length);                  // send message to client
    void broadcastToClients(int sendingClient, const char* msg, int length);

private:
    const char* _ipAddress; // ip of the web server
    int _port;              // port for the web service
    int _socket;            // internal socket fd
    fd_set _fd_set;         // master fd set
};
