# 检测计算机字节序（大端还是小端）


这段代码通过判断一个短整型变量在内存中的字节序，确定计算机系统是大端(Big Endian)还是小端(Little Endian)。

在大端字节序/<font color="blac">网络字节序（Big Endian）</font>中，高位字节在前，低位字节在后。以十六进制数值0x1234为例，在大端系统中，会以0x12 0x34的形式储存。在这种情况下，最高位字节（0x12）存储在内存的最低地址。

在小端字节序/主机字节序（Little Endian）中，低位字节在前，高位字节在后。同样以十六进制数值0x1234为例，在小端系统中，会以0x34 0x12的形式储存。在这种情况下，最低位字节（0x34）存储在内存的最低地址。


小端（Little Endian）：低位字节在前，高位字节在后，这是一些计算机系统（如x86架构）处理数据的方式。比如，十六进制的数值0x1234，在小端系统中，会以0x34 0x12的形式储存。在小端系统中，最低位字节存储在内存的最低地址。

这里做了以下操作:

1. 定义一个包含一个短整型和一个字符数组的联合体(union)。由于短整型和字符数组大小相等，因此可以用字符数组逐个访问短整型的每一个字节。
2. 将短整型变量设置为0x0102。
3. 检查字符数组的前两个字节，判断计算机系统是大端还是小端。

具体来说，如果第一个字节是1，第二个字节是2，那么这是大端系统；如果第一个字节是2，第二个字节是1，那么这是小端系统。

```markdown
#include <stdio.h>

int main() {
    union {
        short num;
        char bytes[sizeof(short)];
    } endianness;

    endianness.num = 0x0102;

    if ((endianness.bytes[0] == 1) && (endianness.bytes[1] == 2)) {
        printf("大端\n");
    } else if ((endianness.bytes[0] == 2) && (endianness.bytes[1] == 1)) {
        printf("小端\n");
    } else {
        printf("未知\n");
    }
  
    return 0;
}
```
主机字节序/网络字节序转换函数
==================

下面是一些用于在主机字节序和网络字节序之间进行转换的函数：

* htonl：host to network long（32位整数）
* htons：host to network short（16位整数）
* ntohl：network to host long（32位整数）
* ntohs：network to host short（16位整数）