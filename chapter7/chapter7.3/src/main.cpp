#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fcntl.h>
// 让进程以守护进程的方式运行
bool daemonize() {
    std::cout << "into daemonize() ... " << std::endl;
    // 创建子进程, 关闭父进程, 使程序在后台运行
    pid_t pid = fork();
    std::cout << "pid = " << pid << std::endl;
    if(pid < 0) // 创建子进程失败
        return false;
    else if(pid > 0) // > 0 代表目前进程是父进程，我们让父进程退出
        exit(0);
    // 设置文件权限掩码。当进程创建新文件(使用open(const char* pathname, int flags, mode_t mode) \
    // 系统调用的时候) 文件的权限将是mode & 0777
    umask(0);

    // 创建新的会话, 设置本进程为进程组的首领
    pid_t sid = setsid();
    if(sid < 0) return false;

    // 切换工作目录
    if( (chdir("/")) < 0) return false;

    // 关闭标准输入设备，标准输出设备和标准错误输出设备
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // 关闭其他已经打开的文件描述符
    // 将标准输入、标准输出和标准错误输出都定向到/dev/null 文件
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    std::cout << "end daemonize() ..." << std::endl;
    return true;
}

static bool switch_to_user(uid_t user_id, gid_t gp_id) {
    // 如果目标用户的UID和GID都为0（root用户的标识），函数直接返回false，即不允许切换到root用户身份。
    if((user_id == 0) && (gp_id == 0)) {
        return false;
    }

    // 如果当前用户既不是root用户，也不是目标用户，函数也返回false，表示切换操作不合法。
    gid_t gid = getgid();
    uid_t uid = getuid();
    if( ((gid != 0) || (uid != 0)) && ((gid != gp_id) || (uid != user_id)) ) {
        return false;
    }

    if(uid != 0) return true;

    // 使用setgid()和setuid()函数切换到目标用户组和用户。
    if( (setgid(gp_id) < 0) || (setuid(user_id) < 0)  ) {
        return false;
    }
}

int main(int argc, char ** argv) {
    uid_t uid = getuid();   // root用户一般是0, 普通用户一般从1000 / 1001 开始
    gid_t gp_id = getgid();
    switch_to_user(uid, gp_id);
    std::cout << "uid = " << uid 
              << " gid = " << gp_id 
              << std::endl;
    daemonize();
    return 0;
}