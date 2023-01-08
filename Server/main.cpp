#include <WS2tcpip.h>
#include <iostream>
#include <sstream>
using namespace std;

void main() {
    // initialize winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0) {
        cerr << "Can't Initialize winsock! Quitting" << endl;
        return;
    }

    // create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);

    if (listening == INVALID_SOCKET) {
        cerr << "can't create a socket, quitting" << endl;
        return;
    }

    // bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    // hint.sin_addr.S_un.S_addr = INADDR_ANY;
    hint.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    bind(listening, (sockaddr *)&hint, sizeof(hint));

    // tell winsock the socket is for listening
    listen(listening, SOMAXCONN);

    fd_set master;

    FD_ZERO(&master);
    FD_SET(listening, &master);

    while (true) {
        fd_set copy = master;
        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
        for (int i = 0; i < socketCount; i++) {
            SOCKET sock = copy.fd_array[i];
            if (sock == listening) {
                // accept a new connection

                // sockaddr_in client;
                // int clientSize = sizeof(client);
                // SOCKET clientSocket = accept(listening, (sockaddr *)&client, &clientSize);

                SOCKET clientSocket = accept(listening, nullptr, nullptr);

                // add the new connection the list of connected clients
                // socket <-> fd <-> u_int
                FD_SET(clientSocket, &master);

                // send a welcome message to the connected client
                string welcomeMsg = "Welcome to the chat server";
                send(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
            } else {
                char buffer[4096];
                ZeroMemory(buffer, 4096);

                //  receive message
                int bytesReceived = recv(sock, buffer, 4096, 0);
                if (bytesReceived <= 0) {
                    // drop the client
                    closesocket(sock);
                    FD_CLR(sock, &master);
                } else {
                    // send message to other clients, excluding the listening socket
                    for (int i = 0; i < master.fd_count; i++) {
                        SOCKET outSock = master.fd_array[i];
                        bool isNullSenetence = buffer[0] == 13 && buffer[1] == 10;
                        if (outSock != listening && outSock != sock && !isNullSenetence) {
                            ostringstream ss;
                            ss << "SOCKET #" << sock << ": " << buffer << "\r\n";
                            string strOut = ss.str();
                            send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                        }
                    }
                }
            }
        }
    }

    // cleanup  winsock
    WSACleanup();
}
