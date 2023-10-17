#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <netdb.h>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        std::cerr << "Usage: " << basename(argv[0]) << " ip_address port_number" << std::endl;
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Error: Failed to create socket." << std::endl;
        return 1;
    }

    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Error: Failed to connect to server." << std::endl;
        close(sockfd);
        return 1;
    }

    char buffer[1024];
    ssize_t recv_len;
    while ((recv_len = recv(sockfd, buffer, sizeof(buffer), 0)) > 0)
    {
        write(STDOUT_FILENO, buffer, recv_len); // 将接收到的数据写入标准输出
    }

    close(sockfd);
    return 0;
}
