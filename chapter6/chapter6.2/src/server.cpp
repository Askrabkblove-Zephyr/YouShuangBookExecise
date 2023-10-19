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
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/uio.h> // writev

#define BUFFER_SIZE 1 << 10
// 定义两种HTTP状态码和状态信息
static const char *status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char *argv[])
{
    if (argc <= 3)
    {
        std::cerr << "Usage: " << basename(argv[0]) << " ip_address port_number" << std::endl; // 使用basename函数提取路径中的文件名
        return 1;
    }

    const char *ip = argv[1];        // 从命令行参数获取IP地址
    int port = atoi(argv[2]);        // 将端口号从字符串转换为整数
    const char *file_name = argv[3]; // 将目标文件作为程序的第三个参数传入

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
        // 用于保存http应答的状态行, 头部字段, 一个空行的缓存区
        char header_buf[BUFFER_SIZE];
        memset(header_buf, '\0', BUFFER_SIZE);
        // 用于存放目标文件内容的应用程序缓存
        char *file_buf;
        // 用于获取目标文件的属性, 比如是否为目录，文件大小等
        struct stat file_stat;
        // 记录目标文件是否为有效文件
        bool valid = true;
        // 缓存区header_buf目前已经使用了多少字节的空间
        int len = 0;
        if (stat(file_name, &file_stat) < 0) // 目标文件不存在
        {
            valid = false;
        }
        else
        {
            if (S_ISDIR(file_stat.st_mode)) // 目标文件是一个目录
            {
                valid = false;
            }
            else if (file_stat.st_mode & S_IROTH)
            {                                       // 当前用户有读取目标文件的权限
                int fd = open(file_name, O_RDONLY); // fcntl.h
                // 动态分配缓存区file_buf,并指定其大小为目标文件的大小file_stat.st_size + 1,
                // 然后将文件目标读入缓存区file_buf中
                file_buf = new char[file_stat.st_size + 1];
                memset(file_buf, '\0', file_stat.st_size + 1);
                if (read(fd, file_buf, file_stat.st_size) < 0)
                {
                    valid = false;
                }
            }
            else
            {
                valid = false;
            }
        }
        // 如果目标文件有效, 则发送正常的HTTP应答
        if (valid)
        {
            // 下面这部分内容将HTTP应答的状态行, "Content-Length"头部字段和一个空行一次加入header_buf中
            ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n", "HTTP/1.1", status_line[0]);
            len += ret;
            ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "Content-Length: %d\r\n", file_stat.st_size);
            len += ret;
            ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");
            // 利用writev将header_buf和file_buf的内容一并写出
            struct iovec iv[2];
            iv[0].iov_base = header_buf;
            iv[0].iov_len = strlen(header_buf);
            iv[1].iov_base = file_buf;
            iv[1].iov_len = file_stat.st_size;
            ret = writev(connfd, iv, 2);
        }
        else
        { // 如果目标文件无效， 则通知客户端服务器发生了内部错误
            ret = snprintf(header_buf, BUFFER_SIZE - 1, "%s %s\r\n", "HTTP/1.1", status_line[0]);
            len += ret;
            ret = snprintf(header_buf + len, BUFFER_SIZE - 1 - len, "%s", "\r\n");
            send(connfd, header_buf, strlen(header_buf), 0);
        }
        close(connfd);
        delete[] file_buf;
    }
    close(sock); // 关闭监听套接字
    return 0;
}
