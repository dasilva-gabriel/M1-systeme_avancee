#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int compteur = 0;

void handler( int sig ){
    if(sig == SIGINT ){
        printf("PID: %i - compteur: %i", getpid(), compteur);
    }
    
}

void defineSigaction(int fils) {
    struct sigaction signal;
    signal.sa_handler = handler;
    sigfillset(&signal.sa_mask);
    signal.sa_flags = 0;

    if(fils == 0 && sigaction(SIGINT, &signal, NULL) > 0) {
        exit(1);
    }
    if( sigaction(SIGUSR1, &signal, NULL) > 0) {
        exit(1);
    }
    if( sigaction(SIGUSR2, &signal, NULL) > 0) {
        exit(1);
    }
    if( sigaction(SIGKILL, &signal, NULL) > 0) {
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    for(int i = 0; i < 10; i++) {

        if(fork() == 0) {

            defineSigaction(1);

            sleep(rand() % 3);
            compteur++;
            

        }

    }
    defineSigaction(0);
    return 0;
}
