#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <ifaddrs.h>
using namespace std;
#define BUFFER_SIZE 1 << 9

int main(int argc, char **argv)
{
    std::cout << "argc = " << argc << "argv = " << *argv << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }

    if (argc <= 2)
    {
        std::cout << "usage: " << basename(argv[0]) << // 从路径中提取文件名
            "  ip_address port_number \n"
                  << std::endl; // backlog 等待连接队列长度
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]); // 字符串转整型

    // 创建一个ipv4 socket地址
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address)); // 置空结构体
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr); // 转换为二进制网络字节序IP地址
    server_address.sin_port = htons(port);            // 设置端口

    // 创建一个新的ipv4套接字，使用TCP协议(SOCK_STREAM)，和默认协议族(ipv4)，返回fd
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    // 先设置TCP发送缓冲区的大小, 然后立即读取它
    int sendbuf = atoi(argv[3]);
    int len = sizeof(sendbuf);
    setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuf, sizeof(sendbuf));
    getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t *)&len);
    cout << "the tcp send buffer size after setting is " << sendbuf << endl;

    if (connect(sockfd, (struct sockaddr *)&server_address,
                sizeof(server_address)) != -1)
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, 'a', BUFFER_SIZE);
        send(sockfd, buffer, BUFFER_SIZE, 0);
    }
    close(sockfd);
    return 0;
}
