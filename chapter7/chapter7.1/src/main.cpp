#include <unistd.h>
#include <iostream>

int main(int argc, char ** argv) {
    uid_t uid = getuid();   // root用户一般是0, 普通用户一般从1000 / 1001 开始
    uid_t euid = geteuid();
    uid_t ppid = getppid();
    uid_t pid = getpid();
    std::cout << "uid = " << uid 
              << " euid = " << euid 
              << std::endl;
    while(1);
    
    return 0;
}