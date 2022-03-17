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

int initialiser_cond(pthread_cond_t *pcond){
  pthread_condattr_t condattr;
  int code;
  pthread_condattr_init(&condattr);
  pthread_condattr_setpshared(&condattr,PTHREAD_PROCESS_SHARED);
  if( ( code = pthread_cond_init(pcond, &condattr) ) != 0)
    return code;
  code = pthread_cond_init(pcond, &condattr)  ;
  return code;
}	
