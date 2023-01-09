#include "WebServer.h"
#include "utils/split.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void WebServer::onClientConnected(int clientSocket){

};
void WebServer::onClientDisconnected(int clientSocket){

};
void WebServer::onMessageReceived(int currSock, char* buffer, int bytesReceived) {
    // GET /index.html HTTP/1.1
    // parse out the doucment requested
    // open the document in local file system
    // write the document back to the client
    std::string clientMessage{buffer};
    // std::istringstream iss(buffer);
    std::vector<std::string> parsed = split(clientMessage, " ");

    std::string method = parsed[0];
    std::string targetHtml = parsed[1];

    if (method == "GET") {
        std::string fileRootLocation = "C:\\Users\\user\\Repos\\Javascript\\2021-02-18-machingclee.github.io";
        int htmlPos = targetHtml.find(".html");
        if (htmlPos != std::string::npos) {
            targetHtml.erase(htmlPos, htmlPos + 5);
        }
        targetHtml.erase(0, 1);
        std::string filePath = fileRootLocation + "\\" + (targetHtml == "" ? "" : (targetHtml + "\\")) + "index.html";
        std::ifstream file{filePath};
        std::string content{"404 Not Found"};

        if (file.good()) {
            std::ostringstream ss;
            ss << file.rdbuf();
            content = ss.str();
            // std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            // content = str;
        }
        file.close();

        std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\r\n"
           << "Cache-Control: no-cache, private\r\n"
           << "Content-Type: text/html\r\n"
           << "Content-Length: "
           << content.size()
           << "\r\n"
           << "\r\n"
           << content;

        std::string res = ss.str();
        sendToClient(currSock, res.c_str(), res.size() + 1);
    }
};