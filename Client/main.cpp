#include <WS2tcpip.h>
#include <iostream>
#include <string>

using namespace std;

void main() {
    string ipAddress = "127.0.0.1"; // ip address of the server
    int port = 54000;               // listening port of the server
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data); // return error code
    if (wsResult != 0) {
        cerr << "Can't Start Winsock, Err #" << wsResult << endl;
        return;
    }

    // SOCKET sock = socket()
    // initialize winsock

    // create socket

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
    }

    // fill in a hint structure
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // connect to server
    int connResult = connect(sock, (sockaddr *)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR) {
        cerr << "Can't connect to server, Err #", WSAGetLastError();
        closesocket(sock);
        WSACleanup();
        return;
    }

    // do-while loop to send and receive data
    char buf[4096];
    string userInput;

    do {
        // prompt the user for some text
        cout << "> ";
        getline(cin, userInput);

        if (userInput.size() > 0) {
            // send the text
            int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);

            if (sendResult != SOCKET_ERROR) {
                // wait for response
                ZeroMemory(buf, 4096);
                int bytesReceived = recv(sock, buf, 4096, 0);
                if (bytesReceived > 0) {
                    // echo response to console
                    cout << "SERVER> " << string(buf, 0, bytesReceived) << endl;
                }
            }
        }
    } while (userInput.size() > 0);

    closesocket(sock);
    WSACleanup();
    // gracefully close everything
}