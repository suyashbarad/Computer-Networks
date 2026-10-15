#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;

    char buffer[1024] = {0};

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1) {
        cout << "Socket creation failed!" << endl;
        return 1;
    }

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1",
              &serverAddress.sin_addr);

    // Connect to server
    if (connect(clientSocket,
                (struct sockaddr*)&serverAddress,
                sizeof(serverAddress)) < 0) {
        cout << "Connection failed! Start the server first."
             << endl;
        close(clientSocket);
        return 1;
    }

    cout << "Connected to server!" << endl;

    // Send message
    string message;
    cout << "Enter message: ";
    getline(cin, message);

    send(clientSocket, message.c_str(), message.length(), 0);

    // Receive server reply
    int bytesReceived = recv(clientSocket, buffer,
                             sizeof(buffer) - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        cout << "Server: " << buffer << endl;
    }

    // Close socket
    close(clientSocket);

    return 0;
}
