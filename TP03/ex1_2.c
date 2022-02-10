#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define LEN 5
#define SIZE 1024

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
int execute(char **argv1, char **argv2, int fd) {

    int pipeCmd[2];

    if(pipe(pipeCmd) == -1) {
        perror("pipe error");
        exit(1);
    }

    int child_process = fork();

    if (child_process == 0) { 

        if(dup2(pipeCmd[1], STDOUT_FILENO) == -1)  { 
            perror("Erreur à la redirection");
            exit(1);
        }

        close(pipeCmd[1]);
        close(pipeCmd[0]);

        execvp(argv1[0], argv1);
        perror("Erreur de commande 1");
        exit(1);

    } else {
        
        char buffer[SIZE];
        
        int r = 0;
        if((r = read(pipeCmd[0], buffer, SIZE)) == -1) {
            perror("Erreur du Read");
            exit(1);
        }

        write(fd, buffer, r);

        if(dup2(fd, STDIN_FILENO) == -1) {
            perror("Erreur de redirection dans le fichier");
            exit(1);
        }
        
        execvp(argv2[0], argv2);
        perror("Erreur de commande 2");
        exit(1);
        
    }


}

int main(int argc, char *argv[])
{
    
    //init_fic(argc, argv);

    int fic = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0775);

    execute(split(argv[2]), split(argv[3]), fic);

    return 0;
}
