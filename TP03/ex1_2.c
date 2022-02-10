#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define LEN 5

char **split(char *s){
  char **result = (char **)calloc(LEN, sizeof(char *));
  int len = LEN, n = 0;
  char *token;
  const char delim[3] = " \t";

  if(s==NULL || strlen(s)==0){ // chaine vide
    result = realloc(result, 1);
    return result;
  }

  token = strtok(s, delim);
  while(token){
    if(n==len){
      len *= 2;
      result = realloc(result, len*sizeof(char *));
    }
    result[n++] = token;
    token = strtok(NULL, delim);
  }
  if(n==len){
    len++;
    result = realloc(result, len*sizeof(char *));
  }  
  result[n++] = NULL;
  if(n<len)
    result = realloc(result, n*sizeof(char *));

  return result;
}

int init_fic(int argc, char *argv[]) {

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

        int child_process = fork();

        close(fic);

        if (child_process == 0) {

            int output = execvp(cmd, argv+2);

            if (output == -1)
            {
                perror("Erreur à l'éxécution de la commande...");
            }

            exit(0);
        }
        else
        {
            int wstatus;
            wait(&wstatus);
        }

    }
}

int execute(char **argv1, char **argv2, int fd) {

    int pipeCmd[2];

    if(pipe(pipeCmd) == -1) {
        perror("pipe error");
        exit(1);
    }

    if(dup2(pipeCmd, STDOUT_FILENO) == -1)  { 
        perror("Erreur à la redirection");
        exit(1);
    }


}

int main(int argc, char *argv[])
{
    
    //init_fic(argc, argv);

    
    return 0;
}
