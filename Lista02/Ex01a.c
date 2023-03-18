#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "sys/wait.h"

int main(void)
{
    pid_t f, w;
    // int status = 3;

    printf("Odin (A) PID=%u\n", getpid());
    f = fork();
    if (f == 0)
    {
        printf("pai PID=%u\n", getppid());
        printf("filho (D) PID=%u\n", getpid());
        // status = 9;
    }
    else
    {
        f = fork();
        if (f == 0)
        {
            printf("pai PID=%u\n", getppid());
            printf("filho (B) PID=%u\n", getpid());
        }
        else
        {
            f = fork();
            if (f == 0)
            {
                printf("pai PID=%u\n", getppid());
                printf("filho (C) PID=%u\n", getpid());
            }
        }
    }
        // printf("%d\n",status);
        return 0;
}