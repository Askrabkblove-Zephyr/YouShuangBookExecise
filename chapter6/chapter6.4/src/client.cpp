#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " ip_address port_number" << std::endl;
        return 1;
    }

    const char *ip = argv[1];
    int port = std::atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Failed to create socket." << std::endl;
        return 1;
    }

    sockaddr_in serverAddr;
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serverAddr.sin_addr);

    if (connect(sockfd, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Error: Failed to connect to server." << std::endl;
        close(sockfd);
        return 1;
    }

    const char *message = "Hello, Server!";
    ssize_t totalSent = 0;
    ssize_t bytesSent = send(sockfd, message, strlen(message), 0);
    if (bytesSent < 0) {
        std::cerr << "Error: Failed to send data to server." << std::endl;
    } else {
        totalSent += bytesSent;
    }

    std::cout << "Sent " << totalSent << " bytes of data to server." << std::endl;

    close(sockfd);
    return 0;
}
