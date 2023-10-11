#include <iostream>
using namespace std;

/// 判断机器字节序
void byteOrder() {
    union MyUnion
    {
        short value;
        char union_bytes[sizeof(short)];
    } test;
    test.value = 0x0102;
    if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2)) 
        std::cout << "大端" << std::endl;
    else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1))
        std::cout << "小端" << std::endl;
    else 
        std::cout << "unknown...\n";
}


int main(int argc, char** argv) {
    byteOrder();
    return 0;
}