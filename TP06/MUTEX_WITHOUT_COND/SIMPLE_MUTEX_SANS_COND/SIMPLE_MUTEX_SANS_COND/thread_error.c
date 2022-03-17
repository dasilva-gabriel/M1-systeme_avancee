#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "thread_error.h"
/* afficher le message d'erreur d'une fonction de la bibliothèque pthread
 * code - le code d'erreur 
 * txt - text supplémentaire à afficher ou NULL
 * file : le nom du ficher source
 * line : le numéro de ligne de fichier source 
 */
void thread_error_exit(const char *file, int line, int code, char *txt){
  if( txt != NULL )
    fprintf( stderr,  "[%s] in file %s in line %d :  %s\n",
	     txt, file , line, strerror( code ) );
  else
    fprintf( stderr,  "in file %s in line %d :  %s\n",
	     file , line, strerror( code ) );
  exit(1);
}
