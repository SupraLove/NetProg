#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
    sockaddr_in addr;
    addr.sin_family = AF_INET; // интернет протокол IPv4
    addr.sin_port = htons(7777); // порт 7777
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    int s = socket(AF_INET, SOCK_STREAM, 0); // TCP

    int rc = connect(s, (const sockaddr*)&addr, sizeof(sockaddr_in));
    if (rc == -1) {
        cout << "Error: failed to connect to server.\n";
        return 1;
    }
    else {
        cout << "We are connected!\n";
        char msg[50] = "41662";
        send(s, msg, sizeof(msg), 0);
        cout << "Message: " << '"' << msg << '"' << " was sent!\n";
        char returned_msg[50];
        recv(s, returned_msg, sizeof(returned_msg), 0);
        cout << "Message: " << '"' << returned_msg << '"' << " was received!\n";
        cout << "Session closed!" << endl;
    }
    close(s);
    return 0;
}
