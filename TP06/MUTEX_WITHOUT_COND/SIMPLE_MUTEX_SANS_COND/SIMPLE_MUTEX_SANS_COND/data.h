/* data.h le contenu de la mémoire partagée */
#ifndef DATA_H
#define DATA_H
#include <pthread.h>
#include <stdbool.h>

#define MESSAGE_LEN 2048

typedef struct{
  pthread_mutex_t mutex;
  bool libre; /* libre == true si on peut écrire un nouveau message, 
		 false sinon */
  size_t compteur; /* compteur de messages */ 
  pid_t  pid;  /* pid du dernier processus qui a modifié la mémoire */
  size_t len;  /* longueur de message */
  char msg[MESSAGE_LEN]; /* message */
} memory;
#endif

