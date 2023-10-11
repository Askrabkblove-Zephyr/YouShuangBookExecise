#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <iostream>
#include <assert.h>


static bool stop = false;
static void handle_term(int sig) {
    stop = true;
}

// 监听指定的IP地址和端口，然后在接收到SIGTERM信号时退出
int main(int argc, char ** argv) {
    std::cout << "argc = " << argc << "argv = " << *argv << std::endl;
    for(int i = 0; i < argc; i++) {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }
    // 注册SIGTERM信号处理函数, 程序被kill的时候调用  
    signal(SIGTERM, handle_term); 

    if(argc <= 3) {
        std::cout << "usage: " << 
             basename(argv[0]) << // 从路径中提取文件名
             "  ip_address port_number backlog\n" << std::endl; // backlog 等待连接队列长度
        return 1;
    }

    const char* ip = argv[1]; 
    int port = atoi(argv[2]); // 字符串转整型
    int backlog = atoi(argv[3]); // 等待连接队列长度
    // 创建一个新的ipv4套接字，使用TCP协议(SOCK_STREAM)，和默认协议族(ipv4)，返回fd
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0); // 

    // 创建一个ipv4 socket地址
    struct sockaddr_in address; 
    bzero(&address, sizeof(address)); // 置空结构体
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr); // 转换为二进制网络字节序IP地址
    address.sin_port = htons(port); // 设置端口

    // 将套接字绑定到指定的IP地址和端口号
    int ret = bind(sock, (struct sockaddr*) &address, sizeof(address));
    assert(ret != -1);
    // 开始监听连接请求
    ret = listen(sock, backlog);
    assert(ret != -1);

    while(!stop) {
        sleep(1);
    }

    close(sock);
    return 0;

}

