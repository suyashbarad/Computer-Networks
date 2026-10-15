
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    string str;
    cout << "Enter a string: ";
    getline(cin, str);

    sendto(clientSocket, str.c_str(),
        str.length(), 0,
        (sockaddr*)&serverAddr, sizeof(serverAddr));

    char buffer[1024];
    sockaddr_in fromAddr;
    socklen_t fromLen = sizeof(fromAddr);

    int bytes = recvfrom(clientSocket, buffer,
        sizeof(buffer) - 1, 0,
        (sockaddr*)&fromAddr, &fromLen);

    if (bytes > 0) {
        buffer[bytes] = '\0';
        cout << "Reversed string: "
             << buffer << endl;
    }

    close(clientSocket);
    return 0;
}

//Output:
// Enter a string: hello
// Reversed string: olleh
