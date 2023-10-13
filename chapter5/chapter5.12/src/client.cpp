#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <hostname>" << std::endl;
        return 1;
    }

    const char *host = argv[1];
    struct hostent *hostinfo = gethostbyname(host);
    if (hostinfo == nullptr) {
        std::cerr << "Error: Cannot resolve hostname." << std::endl;
        return 1;
    }

    struct servent *servinfo = getservbyname("domain", "tcp");
    if (servinfo == nullptr) {
        std::cerr << "Error: Cannot get daytime service information." << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = servinfo->s_port;
    serverAddress.sin_addr = *(struct in_addr *) *hostinfo->h_addr_list;

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error: Cannot create socket." << std::endl;
        return 1;
    }

    if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error: Cannot connect to the daytime service." << std::endl;
        close(sockfd);
        return 1;
    }

    char buffer[128];
    ssize_t bytesRead = read(sockfd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Received data: " << buffer << std::endl;
    } else {
        std::cerr << "Error: Failed to read from the socket." << std::endl;
    }

    close(sockfd);
    return 0;
}
