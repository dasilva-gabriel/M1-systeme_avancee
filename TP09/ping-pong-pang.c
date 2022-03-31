#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*

PARTIE 1

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

}*/

void handler(int sig) {}

int main(int argc, char const *argv[])
{

    struct sigaction signal;
    signal.sa_handler = handler;
    sigfillset(&signal.sa_mask);
    signal.sa_flags = 0;

    if (sigaction(SIGUSR1, &signal, NULL) > 0)
    {
        exit(1);
    }

    int pid = fork();
    if (pid == 0)
    {

        printf("ping\n");

        kill(getppid(), SIGUSR1);
        pause();

        printf("pang\n\n");
    }
    else
    {

        pause();

        printf("pong\n");

        kill(pid, SIGUSR1);
    }

    return 0;
}
