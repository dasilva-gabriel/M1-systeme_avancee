#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    printf("ping\n");
    int pid = fork();
    if (pid == 0) printf("pong\n");
    else {
        wait(0);
        printf("pang\n");
    }
    return 0;
}
