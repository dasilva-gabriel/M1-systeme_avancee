#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

    /*for(int i = 0; i<3; i++) {
        pid_t pid = fork();

        if(pid == 0) {
            printf("Processus zombie.\n");
            execlp("sleep", "sleep", "5", (char*) NULL);
            exit(1);
        }
    }

    sleep(10);*/


    /* Comment modifier le programme pour créer le même nombre de processus,
       effectuant les mêmes tâches (en particulier, le processus principal
       doit continuer à s'exécuter), sans produire de zombies observables ? */

    for(int i = 0; i<3; i++) {
        pid_t pid = fork();

        if(pid == 0) {
            if(fork() == 0) {
                printf("Processus zombie.\n");
                execlp("sleep", "sleep", "1", (char*) NULL);
                exit(-1);
            } else {
                exit(0);
            }
            
        } else {
            waitpid(pid, NULL, WNOHANG);
            printf("Parent: %d\n", getpid());
        }
    }

    sleep(10);

}