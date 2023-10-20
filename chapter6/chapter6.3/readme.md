
---

# 使用 `sendfile` 函数进行文件传输

在Linux系统中，`sendfile` 函数可以高效地将文件内容从一个文件描述符传输到另一个文件描述符，通常用于网络编程中的文件传输。

## 函数签名：

```c
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
```

- `out_fd`：目标文件的文件描述符，数据将被写入到这个文件。
- `in_fd`：源文件的文件描述符，数据将从这个文件读取。
- `offset`：源文件中的起始偏移量，如果为NULL，则从当前偏移量处开始。
- `count`：要传输的字节数。

## 使用方法：

```c
#include <sys/sendfile.h>

// 打开源文件和目标文件，获取它们的文件描述符 in_fd 和 out_fd

struct stat stat_buf;
fstat(in_fd, &stat_buf); // 获取源文件的状态信息

off_t offset = 0; // 设置起始偏移量为0，从文件开始处开始传输
ssize_t sent_bytes = sendfile(out_fd, in_fd, &offset, stat_buf.st_size);

if (sent_bytes == -1) {
    // 错误处理
} else {
    // 文件传输成功，sent_bytes为传输的字节数
}

// 关闭文件描述符
close(in_fd);
close(out_fd);
```

## 注意事项：

- `sendfile` 函数是一个系统调用，效率非常高，适用于大文件传输。
- 它仅适用于两个文件描述符之间的传输，通常用于网络编程中的文件发送。
- 在使用前，需要确保源文件和目标文件的文件描述符已经打开。
- 传输的字节数由 `count` 指定，可以控制每次传输的数据量。
- 如果 `offset` 参数不为NULL，传输将从源文件的指定偏移量处开始，否则从当前文件偏移量处开始。

以上是关于 `sendfile` 函数的基本介绍和使用方法。

---