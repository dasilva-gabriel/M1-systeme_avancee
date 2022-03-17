/***************** panic.h ********************/
#ifndef PANIC_H
#define PANIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define PANIC_EXIT( msg )  do{			\
   fprintf(stderr,\
     "\n %d %s : error \"%s\" in file %s in line %d\n",\
	   (int) getpid(), msg, strerror(errno), __FILE__, __LINE__);	\
   exit(1);\
  } while(0)		
#define PANIC( msg )  do{			\
   fprintf(stderr,\
     "\n %d %s : error \"%s\" in file %s in line %d\n",\
	   (int) getpid(),msg, strerror(errno), __FILE__, __LINE__);	 \
  } while(0)		
#endif
