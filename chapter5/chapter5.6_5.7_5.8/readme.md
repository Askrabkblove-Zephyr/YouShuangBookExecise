`connect()` 函数用于客户端连接到服务器。在客户端代码中，你需要执行以下步骤：

1. **创建Socket：** 和服务器端一样，首先创建一个套接字。

   ```cpp
   int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
   ```

2. **指定服务器地址和端口：** 填充服务器的地址信息。

   ```cpp
   sockaddr_in serverAddress;
   serverAddress.sin_family = AF_INET;
   serverAddress.sin_port = htons(8080);  // 服务器端口号
   inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr));  // 服务器IP地址
   ```

3. **连接到服务器：** 使用 `connect()` 函数连接到服务器。

   ```cpp
   int connectionResult = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
   if (connectionResult == -1) {
       perror("Connection error");
       close(clientSocket);
       exit(EXIT_FAILURE);
   }
   ```

4. **与服务器通信：** 连接建立后，可以使用 `send()` 和 `recv()` 函数与服务器进行数据交换。`send()`失败返回-1, `recv()`出错同样返回-1。

   ```cpp
   char buffer[1024];
   send(clientSocket, "Hello, Server!", 15, 0);
   int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
   ```

5. **关闭套接字：** 数据交换完成后，使用 `close()` 函数关闭套接字。`close() `只是将socket计数-1,不是立刻关闭；想要立刻关闭应该使用`shutdown()`

   ```cpp
   close(clientSocket);
   ```

这就是一个基本的客户端连接服务器的流程。注意，服务器和客户端的地址、端口号必须匹配，否则连接会失败。在实际开发中，还需要考虑错误处理、超时处理等情况。

## 发送带外数据（Out-of-Band Data）

在这个例子中，我们演示了如何在Socket通信中发送带外数据（Out-of-Band Data）。带外数据是一种特殊的数据，可以与主通道的数据分开处理。在这个例子中，我们使用了`send`函数的不同标志位来实现带外数据的发送。

### 1. 客户端（Client）

在客户端代码中，我们发送了带外数据。这是通过在`send`函数中使用了`MSG_OOB`标志位来实现的。以下是客户端代码片段：

```cpp
send(sockfd, normal_data, sizeof(normal_data), 0);
send(sockfd, normal_data, sizeof(normal_data), MSG_MORE); 
send(sockfd, oob_data, sizeof(oob_data), MSG_OOB); // 发送带外数据
send(sockfd, normal_data, sizeof(normal_data), 0);
```

在第三次`send`调用中，我们使用了`MSG_OOB`标志位，表示发送的数据是带外数据。带外数据与主通道的普通数据是分开处理的。通常，带外数据用于发送紧急消息或控制信息，因为它们可以立即被接收端处理，而不需要等待主通道上的其他数据传输完成。

### 2. 服务器端（Server）

在服务器端代码中，我们接收带外数据，并将其与主通道的数据分开处理。以下是服务器端代码片段：

```cpp
memset(buff, '\0', BUF_SIZE);
ret = recv(connfd, buff, BUF_SIZE - 1, 0);
std::cout << "收到 " << ret << " 字节普通数据：" << buff << std::endl;

memset(buff, '\0', BUF_SIZE);
ret = recv(connfd, buff, BUF_SIZE - 1, MSG_MORE);
std::cout << "收到 " << ret << " 字节 MSG_MORE 数据：" << buff << std::endl;

memset(buff, '\0', BUF_SIZE);
ret = recv(connfd, buff, BUF_SIZE - 1, MSG_OOB);
std::cout << "收到 " << ret << " 字节 MSG_OOB 数据：" << buff << std::endl;

memset(buff, '\0', BUF_SIZE);
ret = recv(connfd, buff, BUF_SIZE - 1, 0);
std::cout << "收到 " << ret << " 字节普通数据：" << buff << std::endl;
```

在服务器端，我们使用`recv`函数接收带外数据。第一次调用`recv`用于接收普通数据，第二次调用中使用了`MSG_MORE`标志位，用于接收主通道上的剩余数据。第三次调用中，我们使用了`MSG_OOB`标志位，用于接收带外数据。最后一次调用用于接收剩余的普通数据。

## 总结
要使得server成功接收到数据要使得server和client在同一个网段下才可以