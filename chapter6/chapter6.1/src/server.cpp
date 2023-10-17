#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        std::cerr << "Usage: " << basename(argv[0]) << " ip_address port_number" << std::endl; // 使用basename函数提取路径中的文件名
        return 1;
    }

    const char *ip = argv[1]; // 从命令行参数获取IP地址
    int port = atoi(argv[2]); // 将端口号从字符串转换为整数

    struct sockaddr_in address;                // 定义IPv4地址结构体
    bzero(&address, sizeof(address));          // 清空结构体内存空间
    address.sin_family = AF_INET;              // 设置地址家族为IPv4
    inet_pton(AF_INET, ip, &address.sin_addr); // 将IP地址的“表示形式”转换为“网络字节序”的二进制形式
    address.sin_port = htons(port);            // 将端口号从主机字节序转换为网络字节序

    int sock = socket(PF_INET, SOCK_STREAM, 0); // 创建TCP套接字
    assert(sock >= 0);                          // 确保套接字创建成功

    int ret = bind(sock, (struct sockaddr *)&address, sizeof(address)); // 将套接字绑定到指定的IP地址和端口上
    assert(ret != -1);                                                  // 确保绑定成功

    ret = listen(sock, 5); // 开始监听客户端连接请求，最多允许5个连接请求同时等待处理
    assert(ret != -1);     // 确保监听成功

    struct sockaddr_in client;                                                 // 定义客户端地址结构体
    socklen_t client_addrlength = sizeof(client);                              // 客户端地址结构体的长度
    int connfd = accept(sock, (struct sockaddr *)&client, &client_addrlength); // 接受客户端的连接请求，返回新的套接字描述符
    if (connfd < 0)
    {
        std::cout << "errno is " << errno << std::endl; // 输出错误信息
    }
    else
    {
        close(STDOUT_FILENO);             // 关闭标准输出
        dup(connfd);                      // 复制connfd描述符到标准输出，使得后续输出重定向到与客户端的连接
        std::cout << "abcd" << std::endl; // 向标准输出打印内容，实际上会发送到与客户端的连接
        close(connfd);                    // 关闭连接套接字
    }
    close(sock); // 关闭监听套接字
    return 0;
}
