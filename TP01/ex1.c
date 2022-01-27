#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    /* Écrire un programme qui exécute la commande `ls` */

    //execlp("ls", "ls", (char*) NULL);

    /* Modifier votre programme pour qu'il exécute la commande `ls -l`. */

    //execlp("ls", "ls", "-l", (char*) NULL);


    /* Modifier votre programme pour qu'il exécute la commande dans un processus fils */
    pid_t pid = fork();

    if(pid == 0) {
        printf("Exécution depuis le fils.\n");
        execlp("ls", "ls", "-l", (char*) NULL);
    }
    wait(NULL);
    printf("Père terminé.\n");

    return 0;
}
