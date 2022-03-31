#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    printf("ping ");
    if (fork() == 0) printf("pong ");
    else printf("pang");
    return 0;
}
