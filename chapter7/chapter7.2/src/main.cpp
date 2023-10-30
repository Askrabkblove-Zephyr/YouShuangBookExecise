#include <unistd.h>
#include <iostream>

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
    return 0;
}