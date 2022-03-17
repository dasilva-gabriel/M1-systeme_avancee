#include <string.h>
#include <stdlib.h>
#include "prefix_slash.h"

char *prefix_slash(const char *name){
  #define L_NAME 256
  //  static char nom[L_NAME]; 

  char *nom=malloc(L_NAME);
  
  
  if( name[1] != '/' ){
    nom[0] = '/';
    nom[1]='\0';
    strncat(nom, name, L_NAME-3);
  }else{
    strncpy(nom, name, L_NAME);
    nom[L_NAME-1]='\0';
  }
  return nom;
}
