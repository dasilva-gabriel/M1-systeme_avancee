TP nº1 : rappels de L3 : vie et mort d'un processus
==================

**M1 Informatique - Programmation Système Avancée**

#### Exercice 1 : échauffement (tranquille)

* Quel est l'effet de la ligne de commande (shell) `exec ls`? Expliquer...

* Écrire un programme qui exécute la commande `ls` (sans
  créer de nouveau processus).

* Modifier votre programme pour qu'il exécute la commande `ls -l`.

* Modifier votre programme pour qu'il exécute la commande dans un
  processus fils (sans oublier d'attendre la fin de l'exécution du
  fils).


#### Exercice 2 : zombies

* Écrire un programme `zombies.c` dont l'exécution permet d'observer
  (durablement) une situation similaire à la suivante (les lignes non
  pertinentes ont été supprimées) : 

```bash
poulalho@lulu:SY5$ ./zombies & sleep 5; ps
    PID TTY          TIME CMD
3743177 pts/19   00:00:00 zombies
3743181 pts/19   00:00:00 sleep <defunct>
3743182 pts/19   00:00:00 sleep <defunct>
3743183 pts/19   00:00:00 sleep <defunct>
```

* Que se passe-t-il à la mort du processus exécutant `zombies` ?
  Pourquoi ?

* Comment modifier le programme pour créer le même nombre de processus,
  effectuant les mêmes tâches (en particulier, le processus principal
  doit continuer à s'exécuter), sans produire de zombies observables ?

#### Exercice 3 : conditionnelle

Écrire un programme `si` qui se comporte (presque) comme la commande `if` du **shell**. Votre programme prendra deux ou trois noms de commande en paramètres : un test, une conséquence et optionnellement une alternative.  Il commencera par exécuter le test; si celui-ci retourne 0 (succès), il exécutera la conséquence; sinon, si une alternative est proposée, il exécutera cette dernière.
  
Votre programme ne doit créer qu'un seul processus fils. 

Par exemple, la commande `./si true emacs` doit exécuter `emacs`, tandis que la commande `./si false emacs vi` doit exécuter `vi` (on rappelle que les commandes `true` et `false` ne  font rien et retournent 0 et 1 respectivement).


#### Exercice 4 : (tous) à table!

* Écrire un programme qui crée deux processus, un père et son fils. Toutes
les secondes, le père ~~appelle son fils~~ affiche le message `À table!`,
tandis que le fils fait obstinément la sourde oreille. Au bout d'un
certain temps (aléatoire), le fils cède, affiche `Oui, voilà, c'est bon
quoi!` (et termine). Le père lâche alors un `C'est pas trop tôt, tu n'es
pas à l'auberge ici!`, avant de terminer à son tour.

* Reprendre l'exercice avec cette fois une plus grande famille : le père
appelle tous ses enfants à table, et répète son appel aussi longtemps que
nécessaire. Il accueille chaque enfant d'un `Ah, voici PID! Les autres, à
table!` (avec le PID adapté). Lorsqu'il n'en manque plus qu'un, il change
son message en `Ah, voici PID1. PID2, à table, on n'attend plus que toi!`
(avec les PID adaptés).

Exemple d'exécution :
```bash
$ a_table 4
5132, 5133, 5134, 5135, à table!
À table!
À table!
À table!
(5133) Voilà, voilà, j'arrive...
Ah, voici 5133! Les autres, à table!
À table!
À table!
(5135) Voilà, voilà, j'arrive...
Ah, voici 5135! Les autres, à table!
À table!
(5132) Voilà, voilà, j'arrive...
Ah, voici 5132! 5134, à table, on n'attend plus que toi!
À table!
À table!
(5134) Voilà, voilà, j'arrive...
Ah, enfin! C'est pas trop tôt, tu n'es pas à l'auberge ici!`
```

_(cela nécessite donc que le père stocke les identifiants de ses fils pour
cocher les terminaisons au fur et à mesure, et cela se rapproche un peu
de ce que doit réellement faire un shell pour gérer les jobs à l'arrière-plan)_


