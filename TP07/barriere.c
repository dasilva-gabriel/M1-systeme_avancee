#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

typedef struct barriere_t {
	pthread_mutex_t mutex;
	int process;
    bool ouverte;
} barriere_t;

void barriere(barriere_t* barr){

    if(pthread_mutex_lock( &barr->mutex)  > 0 ) perror("mutex_lock");

    barr->process--;
    if(barr->process <= 0) {

        barr->ouverte = true;
        if(pthread_mutex_unlock( &barr->mutex)  > 0 ) perror("mutex_unlock");
        return;

    }

    if(pthread_mutex_unlock( &barr->mutex)  > 0 ) perror("mutex_unlock");

    while(1) {
        if(pthread_mutex_lock( &barr->mutex)  > 0 ) perror("mutex_lock");

        if(barr->ouverte) break;

        if(pthread_mutex_unlock( &barr->mutex)  > 0 ) perror("mutex_unlock");
    }

}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
