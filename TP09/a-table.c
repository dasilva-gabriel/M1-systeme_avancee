#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler( int sig ){
    
    if(sig == SIGUSR1) {
        printf("[%i] Oui papa, j'arrive!\n", getpid());
        exit(0);
    }
    
}

int main(int argc, char const *argv[]) {
    
    srand(time(NULL));

    int fils[4];
    for(int i = 0; i < 4; i++) {
        int pid = fork();
        fils[i] = pid;
        if(pid == 0) {

            struct sigaction signal;
            signal.sa_handler = handler;
            sigfillset(&signal.sa_mask);
            signal.sa_flags = 0;

            if( sigaction(SIGUSR1, &signal, NULL) > 0) {
                exit(1);
            }
            
            pause();

        }
    }

    sleep(1 + (rand() % 3));

    for(int i = 0; i < 4; i++) {
        kill(fils[i], SIGUSR1); 
    }

    for(int i = 0; i < 4; i++) {

        printf("[PERE] Bon appetit %i !\n", wait(0));

    }
       

    return 0;
}
