#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

    for(int i = 0; i<3; i++) {
        pid_t pid = fork();

        if(pid == 0) {
            printf("Processus zombie.\n");
            execlp("sleep", "sleep", "5", (char*) NULL);
            exit(1);
        }
    }

    sleep(10);

}