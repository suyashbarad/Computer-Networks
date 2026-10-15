
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm>
using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr,
         sizeof(serverAddr));

    char buffer[1024];
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    cout << "UDP Server is waiting..." << endl;

    int bytes = recvfrom(serverSocket, buffer,
        sizeof(buffer) - 1, 0,
        (sockaddr*)&clientAddr, &clientLen);

    if (bytes > 0) {
        buffer[bytes] = '\0';
        string str = buffer;

        cout << "Received: " << str << endl;

        reverse(str.begin(), str.end());

        sendto(serverSocket, str.c_str(),
            str.length(), 0,
            (sockaddr*)&clientAddr, clientLen);

        cout << "Reversed string sent: "
             << str << endl;
    }

    close(serverSocket);
    return 0;
}

//Output:
// UDP Server is waiting...
// After the client sends "hello":
// UDP Server is waiting...
// Received: hello
// Reversed string sent: olleh
