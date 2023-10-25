当你在终端中输入命令 `ps -p 37251 -o pid,uid,euid,ruid,suid,ppid` 时，输出的结果如下：

    | PID   | UID   | EUID  | RUID  | SUID  | PPID  |
    |-------|-------|-------|-------|-------|-------|
    | 37251 | 1000  | 1000  | 1000  | 1000  | 28623 |

在上表中：

*   **PID（Process ID）：** 进程标识，用于唯一标识操作系统中运行的每个进程。
*   **UID（User ID）：** 用户标识，唯一标识系统中的每个用户。
*   **EUID（Effective User ID）：** 有效用户标识，表示进程当前的有效用户。
*   **RUID（Real User ID）：** 实际用户标识，表示进程的真实所有者的用户标识。
*   **SUID（Saved Set-User ID）：** 保存的设置用户标识，用于在进程执行时保存特定用户标识。
*   **PPID（Parent Process ID）：** 父进程标识，表示创建当前进程的父进程的PID。
