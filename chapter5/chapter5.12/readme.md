当两台计算机之间需要建立TCP连接时，它们会执行三次握手。三次握手的过程如下：

### `三次握手`：

1. **`第一次握手（SYN）`**：客户端向服务器发送一个TCP数据包，其中标志位SYN（同步请求）被设置为1，表示客户端请求建立连接。客户端选择一个初始序列号（ISN）并将其放入TCP头部。此时，客户端进入SYN_SENT状态。
   ```
   Client -> Server: SYN, Seq=ISN

   10:00:00.001237 IP (客户端IP).12345 > (服务器IP).80: Flags [S], seq 1234567890, win 65535, options [mss 1460,nop,nop,sackOK], length 0
   ```
   - **Flags [S]**: 表示这是一个SYN标志位，表示发起连接请求。
   - **seq 1234567890**: 表示客户端选择的初始序列号。

2. **`第二次握手（SYN + ACK）`**：服务器收到客户端的SYN包后，如果同意建立连接，会发送一个TCP数据包，其中SYN和ACK标志位都被设置为1，表示同意建立连接，并且确认收到了客户端的请求。服务器选择一个自己的初始序列号（ISN）并放入TCP头部。此时，服务器进入SYN_RCVD状态。
   ```
   Server -> Client: SYN, ACK, Seq=Server_ISN, Ack=Client_ISN+1

   10:00:00.001235 IP (服务器IP).80 > (客户端IP).12345: Flags [S.], seq 987654321, ack 1234567891, win 65535, options [mss 1460,nop,nop,sackOK], length 0
   ```
   - **Flags [S.]**: 表示这是一个SYN和ACK标志位，表示接受连接请求，并发起连接确认。
   - **seq 987654321**: 表示服务器选择的初始序列号。
   - **ack 1234567891**: 表示对客户端初始序列号的确认。

3. **`第三次握手（ACK）`**：客户端收到服务器的SYN-ACK包后，会发送一个TCP数据包，其中ACK标志位被设置为1，表示确认收到了服务器的确认。客户端还会把服务器发送过来的序列号加1作为自己的确认号，表示自己也同意建立连接。此时，客户端和服务器都进入ESTABLISHED状态，连接建立完成。
   ```
   Client -> Server: ACK, Seq=Client_ISN+1, Ack=Server_ISN+1

   10:00:00.001236 IP (客户端IP).12345 > (服务器IP).80: Flags [ACK], seq 1234567891, ack 987654322, win 65535, length 0
   ```
   - **Flags [ACK]**: 表示这是一个ACK标志位，表示客户端确认了服务器的连接确认。
   - **seq 1234567891**: 表示客户端的初始序列号。
   - **ack 987654322**: 表示对服务器初始序列号的确认。

### `四次挥手`：

当一方或双方需要关闭连接时，会执行四次挥手。四次挥手的过程如下：

你是对的，我之前描述的四次挥手过程有误。实际的四次挥手过程如下：

#### **`第一次挥手（FIN）`**：
一方（通常是客户端）向另一方（通常是服务器）发送一个TCP数据包，其中FIN标志位被设置为1，表示希望关闭连接。这个时候，发送FIN的一方进入**FIN_WAIT_1**状态。

```plaintext
Client -> Server: FIN, Seq=Client_ISN
10:00:00.001237 IP (客户端IP).12345 > (服务器IP).80: Flags [F.], seq 1234567891, ack 987654322, win 65535, length 0
```

#### **`第二次挥手（ACK）`**：
另一方（服务器）收到FIN包后，会发送一个ACK包作为确认，表示收到了关闭请求。此时，服务器进入**CLOSE_WAIT**状态。

```plaintext
Server -> Client: ACK, Seq=Server_ISN, Ack=Client_ISN+1
10:00:00.001238 IP (服务器IP).80 > (客户端IP).12345: Flags [ACK], seq 987654322, ack 1234567892, win 65535, length 0
```

#### **`第三次挥手（FIN）`**：
另一方（服务器）也向发送方（客户端）发送一个FIN包，表示同意关闭连接。此时，服务器进入**LAST_ACK**状态。

```plaintext
Server -> Client: FIN, Seq=Server_ISN, Ack=Client_ISN+1
10:00:00.001239 IP (服务器IP).80 > (客户端IP).12345: Flags [F.], seq 987654323, ack 1234567892, win 65535, length 0
```

#### **`第四次挥手（ACK）`**：
最后，接收到FIN包的一方（客户端）发送一个ACK包作为确认。接收到ACK包的一方（服务器）在发送这个ACK之后即可进入**CLOSED**状态。

```plaintext
Client -> Server: ACK, Seq=Client_ISN+1, Ack=Server_ISN+1
10:00:00.001240 IP (客户端IP).12345 > (服务器IP).80: Flags [ACK], seq 1234567892, ack 987654324, win 65535, length 0
```

***

`SO_RCVLOWAT` 和 `SO_SNDLOWAT` 是在TCP套接字（Socket）编程中的两个套接字选项。

1. **`SO_RCVLOWAT`**：
   - **含义**：该选项设置了套接字接收缓冲区的下限水位。当接收缓冲区中的数据小于这个下限水位时，`recv` 函数会阻塞等待，直到接收缓冲区中的数据量大于等于 `SO_RCVLOWAT` 的值，或者接收到了带外数据（out-of-band data）。
   - **用途**：通常在非阻塞套接字中使用，用来控制在非阻塞模式下的 `recv` 函数的行为。设置了 `SO_RCVLOWAT` 后，`recv` 函数不会返回接收到的数据量小于 `SO_RCVLOWAT` 的情况，从而减少了频繁的系统调用，提高了效率。
   - **设置方法**：使用 `setsockopt` 函数来设置，示例代码如下：
     ```c
     int optval = 1024; // 设置 SO_RCVLOWAT 的值为 1024 字节
     setsockopt(socket_fd, SOL_SOCKET, SO_RCVLOWAT, &optval, sizeof(optval));
     ```

2. **`SO_SNDLOWAT`**：
   - **含义**：该选项设置了套接字发送缓冲区的下限水位。当发送缓冲区中的空闲空间小于这个下限水位时，`send` 函数会阻塞等待，直到发送缓冲区中的空闲空间大于等于 `SO_SNDLOWAT` 的值。
   - **用途**：类似于 `SO_RCVLOWAT`，`SO_SNDLOWAT` 用于控制在非阻塞套接字中的 `send` 函数的行为。设置了 `SO_SNDLOWAT` 后，`send` 函数不会返回发送缓冲区剩余空间小于 `SO_SNDLOWAT` 的情况，从而避免了频繁的系统调用。
   - **设置方法**：使用 `setsockopt` 函数来设置，示例代码如下：
     ```c
     int optval = 2048; // 设置 SO_SNDLOWAT 的值为 2048 字节
     setsockopt(socket_fd, SOL_SOCKET, SO_SNDLOWAT, &optval, sizeof(optval));
     ```

这两个选项在非阻塞套接字编程中非常有用，可以帮助控制数据的传输和接收，提高程序的性能和效率。

***
`SO_LINGER`: 用于控制close()的系统调用在关闭TCP连接时的行为。

SO_LINGER 选项是一个 linger 结构体，包含两个成员变量：
```
l_onoff：如果设置为非零值，表示启用 SO_LINGER。
l_linger：指示等待的时间（以秒为单位）。如果 l_onoff 是非零值，表示等待 l_linger 秒。
```

当`l_onoff`启用（设置为非零值），且`l_linger > 0`的时候，套接字会在关闭时等待一段时间，以确保发送缓冲区中的数据被成功发送。具体来说：

- 当调用`close()`函数关闭套接字时，如果发送缓冲区中还有数据，并且等待时间小于`l_linger`，`close()`函数会等待，直到所有数据被发送出去或者等待时间超过`l_linger`。

- 如果等待时间超过了`l_linger`（即超时），`close()`函数会立即返回，而不会等待所有数据发送完成。这样可以确保程序不会永久阻塞在`close()`函数上，即使发送缓冲区中的数据没有完全发送出去。

所以，`l_linger`控制了在关闭套接字时的等待时间。如果等待时间用尽，程序会继续执行后续代码，而不会一直阻塞在`close()`函数上。