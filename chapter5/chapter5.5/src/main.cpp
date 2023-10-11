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
    struct sockaddr_in address;
    bzero(&address, sizeof(address)); // 置空结构体
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr); // 转换为二进制网络字节序IP地址
    address.sin_port = htons(port);            // 设置端口

    // 创建一个新的ipv4套接字，使用TCP协议(SOCK_STREAM)，和默认协议族(ipv4)，返回fd
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);
    // 将套接字绑定到指定的IP地址和端口号
    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);
    // 暂停20秒以等待客户端连接和相关操作(掉线或者退出)完成
    sleep(20);

    // 客户端地址结构体
    struct sockaddr_in client;
    // 获取socket地址结构体的长度
    socklen_t client_addrlength = sizeof(client);
    // 接受客户端的连接请求
    int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlength);
    if (connfd < 0)
        std::cout << "errno is " << errno << "\n"
                  << std::endl;
    else
    {
        // 接受连接成功打印客户端IP地址和端口号
        char remote[INET_ADDRSTRLEN];
        printf("connected with ip: %s and port: %d\n",
               inet_ntop(AF_INET, &client.sin_addr, remote, INET_ADDRSTRLEN),
               ntohs(client.sin_port));
        close(connfd);
    }

    close(sock);
    return 0;
}
