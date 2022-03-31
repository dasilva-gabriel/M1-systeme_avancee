#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int freq[101];

void handler( int sig ){
    if(sig == SIGINT) {
        for(int i = 0; i < 101; i++) {
            printf("> %i - freq: %i\n", i, freq[i]);
        }
    } else if(sig == SIGTERM) {
        int min = 0;
        int max = 0;

        for(int i = 1; i < 101; i++) {
            if(freq[i] > freq[max]) {
                max = i;
            }
            if(freq[i] < freq[min]) {
                min = i;
            }
        }

    }
}

void defineSigaction() {
    struct sigaction signal;
    signal.sa_handler = handler;
    sigfillset(&signal.sa_mask);
    signal.sa_flags = 0;

    if( sigaction(SIGINT, &signal, NULL) > 0) {
        exit(1);
    }
    if( sigaction(SIGTERM, &signal, NULL) > 0) {
        exit(1);
    }
}

int main(int argc, char const *argv[])
{

    srand(time(NULL));

    int fd[2];
    pipe(fd);

    for(int i = 0; i < 101; i++) {
        freq[i] = 0;
    }

    if( fork() == 0 ){
        defineSigaction();
        while(1) {
            int r = rand() % 100;
            freq[r]++;
            write(fd[1], &r, sizeof(int));
            //printf("envoi de %i", r);
            sleep(1);
        }
    }

    defineSigaction();

    int mess;
    while(read(fd[0], &mess, sizeof(int)) > 0) {

        freq[mess]++;
        //printf("Reçu %i (freq: %i)\n", mess, freq[mess]);

    }

    return 0;
}
