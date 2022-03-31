#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define PRECISION 8     // pour la probabilité que la balle sorte

char *ping = "ping ";
char *pong = "pong ";
char *gagne = "\nDehors, j'ai gagné!\n";
char *perdu = "Bravo... une petite revanche?\n";

char *rouge = "\033[91m";
char *vert = "\033[32m";
char *bleu = "\033[34m";

// pour personnalisation
int adversaire; // pid de l'autre processus
char *bruit;    // ping ou pong 
char *couleur;  // vert ou bleu


/*************** affichages et envois de signaux **************/

void tape_la_balle() {
  write(STDOUT_FILENO, couleur, strlen(couleur));
  write(STDOUT_FILENO, bruit, strlen(bruit)); 
  kill(adversaire, SIGUSR1);
}

void crie_victoire() {
  write(STDOUT_FILENO, rouge, strlen(rouge));
  write(STDOUT_FILENO, gagne, strlen(gagne));
  kill(adversaire, SIGUSR2);
}

void avoue_defaite() {
  write(STDOUT_FILENO, couleur, strlen(couleur));
  write(STDOUT_FILENO, perdu, strlen(perdu)); 
}


/********* gestionnaire des signaux SIGUSR1 et SIGUSR2 ********/
void handler(int sig) {
  switch(sig) {
    case SIGUSR2 : 
      avoue_defaite();
      exit(EXIT_SUCCESS); // encore que... ça se discute! 
    default : 
      break;
  }                
}


/**************************** main ****************************/
int main(int argc, char ** argv) {
  struct sigaction action;

  /* préparation commune */

  /* clonage */
  switch(fork()) {
    case -1 : // erreur
      perror("fork : ");
      exit(EXIT_FAILURE);
    case 0 : 
      /* initialisation spécifique au fils */
      break;
    default : 
      /* initialisation spécifique au père */
      /* le père est au service */
      tape_la_balle();
  }

  /* la partie continue */

  while(1) {
    pause();
    /* autres actions ? */
  }

}
