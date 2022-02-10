#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    
    int fic = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0775);

    if(fic < 0) {
        perror("Erreur à l'ouverture...");
        exit(1);
    } else {

        if(dup2(fic, STDOUT_FILENO) == -1)  {
            perror("Erreur à la redirection");
            exit(1);
        }

        char *cmd = argv[2];

        close(fic);

        int child_process = fork();

        if (child_process == 0) {

            execvp(cmd, argv+2);

            perror("Erreur à l'éxécution de la commande...");

            exit(1);
        }
        else
        {
            int wstatus;
            wait(&wstatus);
        }

    }

    
    return 0;
}
