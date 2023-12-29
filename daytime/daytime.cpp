#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[4096];

    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socket creation error\n";
        return 1;
    }

    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13); 
    server_addr.sin_addr.s_addr = inet_addr("172.16.40.1"); 

    
    if (sendto(sockfd, "GET TIME", strlen("GET TIME"), 0, (struct sockaddr *)&server_addr, addr_len) < 0) {
        std::cerr << "Sendto failed\n";
        return 1;
    }

    
    int bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
    if (bytes_received < 0) {
        std::cerr << "Recvfrom failed\n";
        return 1;
    }

    buffer[bytes_received] = '\0'; 

    
    std::cout << "Daytime from server: " << buffer << std::endl;

    
    close(sockfd);

    return 0;
}
