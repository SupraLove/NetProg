#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
//Алгоритм работы сетевого клиента: Подготовить адреснуые структуры(свою и удаленного сервера) формата IPv4, создать сокет для IPv4, привязать сокет к своему адресу,
//установить соединение с сервером, выполнить информационный обмен, закрыть сокет
//формируем структуру
int main() {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1) {
        cout << "Socket error\n";
        return 1;
    }

    sockaddr_in self_addr;
    self_addr.sin_family = AF_INET;
    self_addr.sin_port = htons(44214);
    self_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(44214);
    srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int rc = connect(s, (const sockaddr)&srv_addr, sizeof(sockaddr_in));
    if (rc == -1) {
        cout << "Error: failed connect to server.\n";
        return 1;
    }
    else {
        cout << "We are connected to the server!\n";
        char connection_msg[50] = "Hello, it's client!";
        send(s, connection_msg, sizeof(connection_msg), 0);
        char daytime[50];
        recv(s, daytime, sizeof(daytime), 0);
        cout << "Daytime from server: " << daytime << endl;
        cout << "Session closed!" << endl;
        close(s);
        return 0;
    }
}
