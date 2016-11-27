#include <stdio.h>
#include <signal.h>

void sigterm_handler(int signo)
{
    printf("sig N.O. %d\n", signo);

}

int main()
{
    /*
     *组合键ctrl+c发出的信号就是SIGINT
     *命令行输入kill -2 进程ID也是发出SIGINT,
     *kill -l 查看系统默认信号
     */
    signal(SIGINT, sigterm_handler);
    signal(SIGTERM, sigterm_handler);

    while(1);

    return 0;
}
