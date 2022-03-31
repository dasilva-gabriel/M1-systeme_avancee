#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#define PRECISION 8 // pour la probabilité que la balle sorte

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

void tape_la_balle()
{
  write(STDOUT_FILENO, couleur, strlen(couleur));
  write(STDOUT_FILENO, bruit, strlen(bruit));
  kill(adversaire, SIGUSR1);
}

void crie_victoire()
{
  write(STDOUT_FILENO, rouge, strlen(rouge));
  write(STDOUT_FILENO, gagne, strlen(gagne));
  kill(adversaire, SIGUSR2);
}

void avoue_defaite()
{
  write(STDOUT_FILENO, couleur, strlen(couleur));
  write(STDOUT_FILENO, perdu, strlen(perdu));
}

/********* gestionnaire des signaux SIGUSR1 et SIGUSR2 ********/
void handler(int sig)
{
  switch (sig)
  {
  case SIGUSR2:
    avoue_defaite();
    exit(EXIT_SUCCESS); // encore que... ça se discute!
  default:
    break;
  }
}

/**************************** main ****************************/
int main(int argc, char **argv)
{
  struct sigaction signal;

  srand(time(NULL));

  /* préparation commune */

  signal.sa_handler = handler;
  sigfillset(&signal.sa_mask);
  signal.sa_flags = 0;

  if (sigaction(SIGUSR1, &signal, NULL) > 0)
  {
    exit(1);
  }

  if (sigaction(SIGUSR2, &signal, NULL) > 0)
  {
    exit(1);
  }

  /* clonage */
  int pid = fork();
  switch (pid)
  {
  case -1: // erreur
    perror("fork : ");
    exit(EXIT_FAILURE);
  case 0:
    couleur = vert;
    bruit = pong;
    adversaire = getppid();

    while (1)
    {
      pause();
      sleep(1);

      int nbgen=rand()%PRECISION+1;

      if (nbgen == 2)
      {
        crie_victoire();
      }
      else
      {
        tape_la_balle();
      }
    }

    break;
  default:
    /* initialisation spécifique au père */
    /* le père est au service */
    couleur = bleu;
    bruit = ping;
    adversaire = pid;

    sleep(1);

    tape_la_balle();
  }

  /* la partie continue */
  int i = 0;
  while (1)
  {
    pause();
    sleep(1);

    int nbgen=rand()%PRECISION+1;

    if (nbgen == 2)
    {
      crie_victoire();
    }
    else
    {
      tape_la_balle();
    }
    i++;
    /* autres actions ? */
  }
}
