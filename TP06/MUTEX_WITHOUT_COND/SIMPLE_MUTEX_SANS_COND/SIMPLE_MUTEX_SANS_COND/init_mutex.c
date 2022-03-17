#include <pthread.h>
#include "init_mutex.h"


int initialiser_mutex(pthread_mutex_t *pmutex){
    pthread_mutexattr_t mutexattr;
  int code;

  code = pthread_mutexattr_init(&mutexattr) ;
  if( code != 0 )
    return code;

  code = pthread_mutexattr_setpshared(&mutexattr,
				      PTHREAD_PROCESS_SHARED) ;	    
  if( code != 0 )
    return code;
  
  code = pthread_mutex_init(pmutex, &mutexattr)  ;
  return code;
}

int initialiser_cond(pthread_cond_t *pcond){
  pthread_condattr_t condattr;
  int code;
  code = pthread_condattr_init(&condattr);
  if( code != 0 )
    return code;
  
  code = pthread_condattr_setpshared(&condattr,
				     PTHREAD_PROCESS_SHARED);
  if( code != 0 )
    return code;
  
  code = pthread_cond_init(pcond, &condattr) ; 
  return code;
}	
