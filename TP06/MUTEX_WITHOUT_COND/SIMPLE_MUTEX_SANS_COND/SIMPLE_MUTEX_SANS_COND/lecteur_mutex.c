#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>
#include "panic.h"
#include "prefix_slash.h"
#include "data.h"
#include "thread_error.h"

int main(int argc, char **argv){

  if(argc != 2){
    fprintf(stderr,"%s memory_object_name \n", argv[0]);
    exit(1);
  }

  char *mem_name = prefix_slash(argv[1]);

    
  int fd = shm_open(mem_name,  O_RDWR, S_IWUSR | S_IRUSR);
  if( fd == -1){
    PANIC_EXIT("shm_open");
  }


  memory *mem = mmap(NULL, sizeof(memory),
		     PROT_READ|PROT_WRITE, MAP_SHARED,
		     fd, 0);
  if( mem == MAP_FAILED)
    PANIC_EXIT("mmap");


  /* trouver le nombre de lectures dans la variable 
   * enviromement TOTAL*/
  char *tot = getenv("TOTAL");

  int total = 1000;
  if( tot != NULL ){
    total = atoi( tot );
  }

  
  int tentatives = 0; /* compteur de tentatives de lecture */  

  
  for( int i = 0; i < total ;  ){
    int code ;

    code = pthread_mutex_lock( &mem->mutex)  ;
    if( code > 0 )
      thread_error_exit(__FILE__, __LINE__, code,
			"mutex_lock");
    
    if( !mem->libre ){
      i++;
      mem->pid = getpid();
      printf("message numero %d : %s\n", (int)mem->compteur, mem->msg);
      mem->libre = true;
    }
    tentatives ++;
    
     /* mutex unlock */
    code = pthread_mutex_unlock( &mem->mutex ) ;
    if( code > 0 )
      thread_error_exit(__FILE__, __LINE__, code,
			"mutex_unlock");

  }
  printf("#tentatives = %d, #reussites = %d\n", tentatives, total);
}

