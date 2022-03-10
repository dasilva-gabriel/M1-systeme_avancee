#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


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
  /* attention : cet exercice est là pour vous convaincre que dans le cas de plusieurs
     processus il faut mettre le mutex dans la mémoire partagée, pas dans la pile des
     processus, ce n'est donc pas un exemple à suivre */
  pthread_mutex_t mutex;

  if(initialiser_mutex(&mutex)!=0){
    perror("initialiser");
    exit(1);
  }


  if(fork()!=0){ //pere
    pthread_mutex_lock(&mutex);
    pause();
  } else { //fils
    sleep(1);
    pthread_mutex_lock(&mutex);
  }
  return 0;
}
