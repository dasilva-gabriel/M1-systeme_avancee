#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

    printf("top\n");
    
    pid_t pid = fork();

    if(pid == 0) {
        
        if(fork() == 0) {
            waitpid(getppid(), NULL, WNOHANG);
            int randTime = rand() % 101;
            if(randTime < 50) {
                printf("(%d) pas envie...", pid);
                waitpid(getppid(), NULL, WNOHANG);
            } else {
                printf("(%d) Voilà, voilà, j'arrive...", pid);
            }
        } else {
            exit(0);
        }

    } else {

        while(1) {
            printf("A table!");
            kill(pid, SIGUSR1);
            sleep(1);
        }

    }

    return 0;
}
