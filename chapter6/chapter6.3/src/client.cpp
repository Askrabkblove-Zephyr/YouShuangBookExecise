#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " ip_address port_number" << std::endl;
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int ret = connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        close(sockfd);
        return 1;
    }

    char buffer[BUFSIZ];
    ssize_t nread;
    while ((nread = read(sockfd, buffer, BUFSIZ)) > 0)
    {
        // 在这里可以处理接收到的文件数据，例如将数据写入文件
        // 这里的示例代码将数据写入标准输出
        write(STDOUT_FILENO, buffer, nread);
    }

    close(sockfd);
    std::cout << "File received successfully" << std::endl;

    return 0;
}
