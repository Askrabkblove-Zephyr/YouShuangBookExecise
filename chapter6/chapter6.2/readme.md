### 简单的HTTP服务器

这是一个基于C++的简单HTTP服务器程序，用于处理客户端的HTTP请求并发送相应的HTTP响应。以下是代码示例：

```cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
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
#include <sys/uio.h>

#define BUFFER_SIZE 1 << 10

static const char *status_line[2] = {"200 OK", "500 Internal server error"};

int main(int argc, char *argv[])
{
    // 检查命令行参数
    if (argc <= 3)
    {
        std::cerr << "Usage: " << basename(argv[0]) << " ip_address port_number" << std::endl;
        return 1;
    }

    // 解析命令行参数
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    const char *file_name = argv[3];

    // 创建套接字并进行绑定、监听
    // ...（省略了代码，用于创建套接字、绑定、监听等操作）

    // 接受客户端连接
    // ...（省略了代码，用于接受客户端连接）

    // 处理HTTP请求，发送HTTP响应
    // ...（省略了代码，用于处理HTTP请求，发送响应）

    // 关闭套接字
    close(sock);

    return 0;
}
```

### 简介

这个程序是一个简单的HTTP服务器实现。它通过命令行参数接收服务器的IP地址、端口号和要提供的文件路径。当有客户端连接时，它会读取指定的文件内容并将其作为HTTP响应发送给客户端。如果文件不存在或无法读取，它会返回"500 Internal server error"响应。

### 使用方法

运行程序时，需要提供以下三个命令行参数：

1. `<ip_address>`：服务器的IP地址，可以是本地主机的IP地址（例如 `127.0.0.1`）或者网络上的IP地址。
2. `<port_number>`：服务器监听的端口号，选择一个未被占用的端口号，例如 `8080`。
3. `<file_path>`：要提供的文件的路径，服务器将会把这个文件的内容发送给客户端。

示例：

```
./server 127.0.0.1 8080 index.html
```

这个命令将启动服务器，监听 `127.0.0.1:8080` 地址，并将 `index.html` 文件的内容作为HTTP响应发送给客户端。

请确保在服务器端的当前工作目录下存在指定的 `index.html` 文件，否则服务器可能无法找到该文件。

### 注意事项

这是一个简单的示例，用于演示基本的HTTP服务器功能。在实际应用中，可能需要更加健壮的错误处理、并发连接管理和安全性措施。