#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int baiser = 0;
void handler( int sig ){
    baiser++;
    if(baiser > 1) {
        printf("Merci mon prince!\n");
        exit(0);
    }
    printf("Hmmmmm...\n");
    
}

int main(int argc, char const *argv[]) {

    struct sigaction str;
    str.sa_handler = SIG_IGN;
    sigemptyset(&str.sa_mask);
    str.sa_flags = SA_NOCLDWAIT;

    for(int i = 0; i < 31; i++) {
        if(i == SIGUSR1) continue;
        if(sigaction(i, &str, NULL) > 0) exit(1);
    }

    struct sigaction signal;
    signal.sa_handler = handler;
    sigfillset(&signal.sa_mask);
    signal.sa_flags = 0;

    if( sigaction(SIGUSR1, &signal, NULL) > 0) {
        exit(1);
    }

    while(1) {
        pause();
    }

    return 0;
}
