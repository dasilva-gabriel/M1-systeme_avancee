#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>

#include "panic.h"
#include "prefix_slash.h"
#include "data.h"
#include "init_mutex.h"
#include "thread_error.h"


int main(int argc, char **argv){

  if( sysconf(_SC_THREAD_PROCESS_SHARED) < 0 ){
    fprintf(stderr, "sorry, process shared mutexes not supported\n");
    exit(1);
  }
  
  if(argc != 2){
    fprintf(stderr,"%s memory_object_name\n", argv[0]);
    exit(1);
  }

  /* ajouter / au début de nom de l'objet mémoire */
  char *mem_name = prefix_slash(argv[1]);

  /* le code suivant est adapté pour que cela marche aussi 
   * bien sur macOs que sur linux. Sur macOS on ne peut 
   * pas appliquer ftruncate sur l'objet mémoire dont la
   * taille est différente de 0 */ 
  
  int fd = shm_open(mem_name, O_CREAT| O_RDWR,
		    S_IWUSR | S_IRUSR);
  if( fd < 0 )
    PANIC_EXIT( "shm_open" );

#ifdef __linux__
  if( ftruncate( fd, sizeof( memory ) ) < 0 )
    PANIC_EXIT("ftruncate");
#endif
  
#ifdef __APPLE__
  struct stat st;
  if( fstat( fd , &st ) < 0 )
    PANIC_EXIT( "fstat" );
  if( st.st_size == 0 ){
    if( ftruncate( fd, sizeof( memory ) ) < 0 )
      PANIC_EXIT("ftruncate");
  }
  else if( st.st_size != sizeof( memory ) ){
    fprintf(stderr, "l'objet memoire %s existe mais "
	    "la taille incrrecte. Suppression. \n", argv[1]);
    shm_unlink(mem_name);
    fprintf(stderr,
	    "Relancer le processus %s.\n",  argv[0]);
    execv(argv[0], argv);
    PANIC_EXIT("exec");
  }
#endif  


  //  size_t len = sysconf(_SC_PAGESIZE);
  memory *mem;
  
  mem = mmap(NULL, sizeof(memory), PROT_READ|PROT_WRITE,
	     MAP_SHARED, fd, 0);
  if( (void *)mem == MAP_FAILED )
    PANIC_EXIT("mmap");

  /*  initialisation de mémoire partagée */
  int code =  initialiser_mutex( &mem->mutex );
  if( code > 0 )
    thread_error_exit(__FILE__, __LINE__, code, "initialiser_mutex");

  mem->libre = true;
  mem->compteur = 0;
  
  printf("vous pouvez lancer le lecteur\n");
  /* fin d'initialisation de mémoire */
  
  while( true ){

    /*  mutex_lock */
    code = pthread_mutex_lock( &mem->mutex) ;
    if( code > 0 )
      thread_error_exit(__FILE__, __LINE__, code,
		   "mutex_lock");
    /* section critique */
    if( mem->libre ){
      mem->libre = false;
      mem->compteur++;    
      mem->pid = getpid();
      char *message = "Hello!";
      int n = snprintf(mem->msg, sizeof(mem->msg),
		       "%d %s\n", (int)mem->compteur,
		       message ); 
      mem->len = n+1;
    }/* fin section critique */
    
    code = pthread_mutex_unlock( &mem->mutex );
    if( code > 0 )
      thread_error_exit(__FILE__, __LINE__, code,
		   "mutex_unlock");

    
  }
  exit(0);
}
  
