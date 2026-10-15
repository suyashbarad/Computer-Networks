#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress;

    char buffer[1024] = {0};

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        cout << "Socket creation failed!" << endl;
        return 1;
    }

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to port
    if (::bind(serverSocket, (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0) {
        cout << "Bind failed!" << endl;
        close(serverSocket);
        return 1;
    }

    // Listen for clients
    listen(serverSocket, 5);
    cout << "Server is waiting for a client..." << endl;

    // Accept client connection
    clientSocket = accept(serverSocket, nullptr, nullptr);

    if (clientSocket < 0) {
        cout << "Connection failed!" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Client connected successfully!" << endl;

    // Receive message
    int bytesReceived = recv(clientSocket, buffer,
                             sizeof(buffer) - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        cout << "Client: " << buffer << endl;
    }

    // Send reply
    string reply = "Hello from TCP server!";
    send(clientSocket, reply.c_str(), reply.length(), 0);

    // Close sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
