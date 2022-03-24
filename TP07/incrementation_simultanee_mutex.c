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

typedef struct memory {
	pthread_mutex_t mutex;
	int compteur;
} memory;

int initialiser_mutex(pthread_mutex_t *pmutex){
  pthread_mutexattr_t mutexattr;
  int code;
  if( ( code = pthread_mutexattr_init(&mutexattr) ) != 0)	    
    return code;

  if( ( code = pthread_mutexattr_setpshared(&mutexattr,
					    PTHREAD_PROCESS_SHARED) ) != 0)	    
    return code;
  code = pthread_mutex_init(pmutex, &mutexattr)  ;
  return code;
}

int main(int argc, char const *argv[])
{

    int shm = shm_open("/valQUiMarche", O_CREAT | O_RDWR | O_TRUNC, 0775);
    if(shm == -1) {
        perror("Problème au shm_open()"); 
        exit(1);
    }

    int truncate = ftruncate(shm, sizeof(memory));
    if(truncate == -1) {
        perror("Problème au ftruncate()");
        exit(1);
    }

    memory* map = mmap((void *) 0, sizeof(memory), PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0);
    if( (void*) map == MAP_FAILED) {
        perror("Problème avec le mmap()");
        exit(EXIT_FAILURE);
    }


    if(argc == 2 && strcmp(argv[1], "-init")) {
        initialiser_mutex(&map->mutex);
        map->compteur = 0;
    } else if(argc == 2 && strcmp(argv[1], "-incr")) {

        int loop = 100000;
        for(int i = 0; i < loop; i++) {
            int code;
            code = pthread_mutex_lock( &map->mutex) ;
            if( code > 0 ) perror("mutex_lock");

            map->compteur++;

            if(i == loop-1) {
                printf("Compteur de fin %i", map->compteur);
            }

            code = pthread_mutex_unlock( &map->mutex );
            if( code > 0 ) perror("mutex_unlock");
        }

    } else {
        printf("Arg invalide");
    }
    


    return 0;
}