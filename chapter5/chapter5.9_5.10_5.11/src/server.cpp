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
#define BUF_SIZE 1 << 10

int main(int argc, char **argv)
{
    std::cout << "argc = " << argc << "argv = " << *argv << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }

    if (argc <= 3)
    {
        std::cout << "usage: " << basename(argv[0]) << // 从路径中提取文件名
            "  ip_address port_number recvbuf_size\n"
                  << std::endl; // backlog 等待连接队列长度
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]); // 字符串转整型

    // 创建一个新的ipv4套接字，使用TCP协议(SOCK_STREAM)，和默认协议族(ipv4)，返回fd
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    int reuse = 1;
    // 设置socket option 一个服务器在关闭后重新启动,如果不设置特殊选项，操作系统会认为之前的套接字还在关闭过程中，因此新的套接字无法立即绑定到相同的地址和端口，从而导致启动失败。
    // 当设置了SO_REUSEADDR选项后，即使之前的套接字处于TIME_WAIT状态，新的套接字也可以立即绑定到相同的地址和端口上，而不会等待TIME_WAIT状态结束。
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // 创建一个ipv4 socket地址
    struct sockaddr_in address;
    bzero(&address, sizeof(address)); // 置空结构体
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr); // 转换为二进制网络字节序IP地址
    address.sin_port = htons(port);            // 设置端口

    int recvbuf = atoi(argv[3]);
    int len = sizeof(recvbuf);
    // SOL_SOCKET 意思是 Socket Options Level
    // 先设置TCP发送缓冲区的大小, 然后立即读取它
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuf, sizeof(recvbuf));
    getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t*)&len);
    cout << "the tcp send buffer size after setting is " << recvbuf << endl;

    int ret = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t chilent_addrlength = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr *)&client, &chilent_addrlength);
    if (connfd < 0)
    {
        std::cout << "errorno is: " << errno << std::endl;
    }
    else
    {
        char buff[BUF_SIZE];

        memset(buff, '\0', BUF_SIZE);
        while(recv(connfd, buff, BUF_SIZE - 1, 0) > 0) { std::cout << "got normal data : " << buff << std::endl; }
        close(connfd);
    }
    close(sockfd);
    return 0;
}
