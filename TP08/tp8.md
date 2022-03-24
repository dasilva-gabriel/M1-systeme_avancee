TP nº8 : signaux
==================

**L3 Informatique - Système**

Le but de ce TP est d'effectuer quelques manipulations simples pour mieux
comprendre la gestion des signaux.

Une bonne référence est la page `man 7 signal`, très fournie -- en fait,
nettement plus que nécessaire pour ce TP : en dehors des commandes et
fonctions usuelles, vous n'aurez besoin que de la commande `kill` (`man
kill`), et des appels système `kill()` (`man 2 kill`), `pause()` et
`sigaction()`. En particulier, pas de masquage cette fois-ci.


#### Exercice 1 : échauffement -- la belle au bois dormant

* Écrire un programme qui dort (en faisant une boucle de `pause()`
  par exemple) en ignorant tous les signaux (du moins, ceux qu'il peut
  ignorer). 

  Vérifier que votre programme se comporte comme attendu en lui envoyant
  divers signaux avec la commande `kill`, en terminant par `SIGKILL`.

* Modifier votre programme pour qu'il ~~frissonne~~ affiche `"Humm..." à 
  la réception du signal `SIGUSR1`, puis termine.

* Modifier enfin votre programme pour qu'il dorme jusqu'à réception de
  __deux__ signaux `SIGUSR1` : lorsqu'il reçoit un premier ~~baiser~~
  signal `SIGUSR1`, il ~~frissonne~~ affiche `"Humm..."`, puis se rendort 
  et en attend un second pour afficher `"Merci mon prince!"` (puis terminer).


#### Exercice 2 : statistiques intermédiaires

  Écrire un programme qui lance deux processus; le fils écrit des entiers
  aléatoires (entre 1 et 100) dans un tube, sur lequel le père lit en
  boucle. Chacun établit des statistiques des entiers envoyés ou reçus.
  À chaque signal `SIGINT` reçu, chacun affiche les fréquences
  extrémales observées.  S'il reçoit `SIGTERM`, il affiche un
  compte-rendu complet puis termine. Faire en sorte que les compte-rendus
  finaux concordent. Faire également en sorte qu'en cas de décès brutal
  de l'un des deux processus, l'autre termine proprement en affichant
  son compte-rendu (penser à `SIGCHLD` et `SIGPIPE`).


#### Exercice 3 : une petite course (lente)

* Écrire un programme qui crée dix processus, un père et ses 9 fils.
  Le père envoie ensuite le signal `SIGUSR1` à ses fils pour lancer
  le départ. Chaque processus initialise alors un compteur à 0, 
  puis, en boucle infinie :

	* s'endort pour une durée aléatoire de 1 à 3 secondes,

	* puis incrémente son compteur.
	
  Lorsqu'un processus reçoit le signal `SIGINT`, il affiche son pid et
  la valeur de son compteur, puis poursuit.

* Tester votre programme : vérifier notamment que le signal `SIGUSR1` n'a
  tué personne, puis que les processus réagissent comme attendu à
  `SIGINT`. Comparer l'envoi de `SIGINT` sélectivement à un processus
  (grâce à la commande `kill`), ou à tous les processus par la saisie de
  `ctrl-C` dans le terminal. Terminer en envoyant `SIGKILL` à tous les
  processus (noter qu'ils appartiennent tous au même groupe, dont
  l'identifiant est le `pid` du premier processus).

* Modifier votre programme pour en faire une course : le premier processus 
  à atteindre 20 a gagné. Il envoie alors le signal `SIGUSR2` aux autres
  processus, affiche son pid suivi de `"Gnark, j'ai gagné !"`  puis termine.
  À la réception de `SIGUSR2`, tous les autres processus affichent leur pid, 
  suivi de `"Ah, j'ai perdu !"`, puis terminent.

* Que peut-il se passer si les gestionnaires de signaux des fils ne sont
  pas en place dès leur création?

