#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int initialiser_mutex(pthread_mutex_t *pmutex){
  pthread_mutexattr_t mutexattr;

  if(pthread_mutexattr_init(&mutexattr)!=0){
    perror("mutexattr init");
    return 1;
  }

  if(pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED)!=0){
    perror("mutexattr setpshared");
    return 1;
  }

  if(pthread_mutex_init(pmutex, &mutexattr)!=0){
    perror("mutex init");
    return 1;
  }
  return 0;
}


int main(){
  /* attention : dans le cas de plusieurs processus il faut mettre le mutex dans la
     mémoire partagée, pas dans la pile du processus */
  pthread_mutex_t mutex;

  if(initialiser_mutex(&mutex)!=0){
    perror("initialiser");
    exit(1);
  }

  pthread_mutex_lock(&mutex);
  printf("je suis passé :)\n");

  printf("deuxième essai...\n");
  pthread_mutex_lock(&mutex);
  printf("je suis passé :)\n");

  return 0;
}
