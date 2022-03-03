#include "_public.h"
#include "_ftp.h"

CLogFile logfile;

Cftp ftp;

// 程序退出和信号2、15的处理函数。
void EXIT(int sig);

int main(int argc, char const *argv[])
{
    
    return 0;
}


void EXIT(int sig)
{
    printf("程序退出，sig=%d\n\n", sig);
}