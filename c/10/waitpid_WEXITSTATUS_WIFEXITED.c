#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    /*
         * fork 系统调用复制当前进程
         * 如果当前进程为父进程，fork 调用返回子进程 PID
         * 如果当前进程为子进程，fork 调用返回 0
         * 
         * 不同操作系统用不同的整数类型保存进程 ID，有的用short，有的用int，操作系统使用哪种类型，pid_t就设为哪个。
         * */
    __pid_t pid = fork();

    if (pid == -1)
    {
        printf("fork child process failed");

        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        // 如果当前进程为子进程，则执行 exec 函数，子进程被替换为 exec 进程继续执行
        int ret = execl("/usr/bin/slee", "/usr/bin/slee", "3", NULL);

        if (ret == -1)
        {
            printf("exec error: %s\n", strerror(errno));

            return 100;
        }
    }

    printf("start wait child process [%d] executing\n", pid);

    int pid_status = 0;
    int ret = waitpid(pid, &pid_status, 0);

    if (ret == -1)
    {
        printf("wait child process [%d] failed: %s", pid, strerror(errno));

        exit(EXIT_FAILURE);
    }

    // WEXITSTATUS 宏：用于返回子进程的退出状态码
    int child_process_exit_status = WEXITSTATUS(pid_status);

    if (child_process_exit_status)
    {
        printf("child process [%d] error status [%d] \n", pid, child_process_exit_status);
    }

    printf("end wait child process [%d] executed\n", ret);

    return EXIT_SUCCESS;
}
