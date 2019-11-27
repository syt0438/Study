#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char filepath[100];

    for (size_t i = 2; i < 5; i++)
    {
        sprintf(filepath, "%02d", i);

         /*
         * fork 系统调用复制当前进程
         * 如果当前进程为父进程，fork 调用返回子进程 PID
         * 如果当前进程为子进程，fork 调用返回 0
         * 
         * 不同操作系统用不同的整数类型保存进程 ID，有的用short，有的用int，操作系统使用哪种类型，pid_t就设为哪个。
         * */
        pid_t pid = fork();

        // 如果当前进程为子进程，则执行 exec 函数，子进程被替换为 exec 进程继续执行
        if (pid == 0)
        {
            int ret = execl("/usr/bin/echo", "/usr/bin/echo", filepath, NULL);

            if (ret == -1 || errno != 0)
            {
                printf("[%s] exec error: %s\n", filepath, strerror(errno));
            }
        }
    }

    return EXIT_SUCCESS;
}
