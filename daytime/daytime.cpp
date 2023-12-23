#include <iostream>
#include <string>
#include <cstdlib> 
#include <cstring> 
#include <unistd.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#define port 13
#define address "172.16.40.1"
using namespace std;
void Exception(const string & why, const int exitCode ) // Исключения (возможные ошибки завершение программы) 
{
    cout << "Error:"<<exitCode <<endl<< why << endl;
    exit(exitCode);
}
int main()
{ 
    sockaddr_in * selfAddr = new (sockaddr_in); // структура с адресом программы клиента
    selfAddr->sin_family = AF_INET; // интернет протокол IPv4
    selfAddr->sin_port = 0;         // любой порт на усмотрение ОС
    selfAddr->sin_addr.s_addr = 0;  
    sockaddr_in * remoteAddr = new (sockaddr_in);// структура с адресом сервера
    remoteAddr->sin_family = AF_INET;     // интернет протокол IPv4
    remoteAddr->sin_port = htons(13);  // порт 13
    remoteAddr->sin_addr.s_addr = inet_addr("82.179.90.12"); //  адрес 
    char *bufer = new char[1024]; // буфер для передачи и приема данных
    int msgLen = strlen(bufer);     //вычисляем длину строки
    // создаём сокет
    int mySocket = socket(AF_INET, SOCK_DGRAM, 0); 
    if (mySocket == -1) {
        close(mySocket);
        Exception("Error open socket",1);
    }
    //связываем сокет с адрессом
    int rc = bind(mySocket,(const sockaddr *) selfAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error bind socket with local address",2);
        }
    //установливаем соединение
    rc = connect(mySocket, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error connect socket with remote server.", 3);
    }

    // передаём сообщение из буффера
    rc = send(mySocket, bufer, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        Exception("Error send message", 4);
    }
    // принимаем ответ в буффер
    rc = recv(mySocket, bufer, 1024, 0);
    if (rc == -1) {
        close(mySocket);
       Exception("Error receive answer.", 5);
    }
    bufer[rc] = '\0'; // конец принятой строки
    cout << "Daytime from server: " << buffer << endl; 
    // закрыем сокет
    close(mySocket);
    delete selfAddr;
    delete remoteAddr;
    delete[] bufer;
    return 0;
}
