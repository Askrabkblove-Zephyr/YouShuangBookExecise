#include <iostream>  
#include <arpa/inet.h>  
using namespace std;  
  
void function_test() {  
    struct in_addr addr1, addr2;
    // 使用inet_pton将字符串形式的IP地址转换为struct in_addr  
    if (inet_pton(AF_INET, "1.2.3.4", &addr1) == 1) {  
        char* szValue1 = inet_ntoa(addr1);  
        printf("address 1: %s\n", szValue1);  
    } else {  
        cout << "Invalid address 1" << endl;  
    }  
    // 使用inet_pton将字符串形式的IP地址转换为struct in_addr  
    if (inet_pton(AF_INET, "10.194.71.60", &addr2) == 1) {  
        char* szValue2 = inet_ntoa(addr2);  
        printf("address 2: %s\n", szValue2);  
    } else {  
        cout << "Invalid address 2" << endl;  
    }  
}  
  
int main(int argc, char** argv) {  
    function_test();  
    return 0;  
}