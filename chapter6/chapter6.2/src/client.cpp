#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " ip_address port_number" << std::endl;
        return 1;
    }

    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    if (connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    const char* request = "GET / HTTP/1.1\r\nHost: localhost\r\n\r\n";
    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("send");
        close(sockfd);
        return 1;
    }

    char buffer[4096];
    bzero(buffer, sizeof(buffer));
    while (recv(sockfd, buffer, sizeof(buffer) - 1, 0) > 0) {
        std::cout << buffer;
        bzero(buffer, sizeof(buffer));
    }

    close(sockfd);
    return 0;
}
