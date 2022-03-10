TP nº6 : segments partagés, sémaphores et mutexes
==================

**M1 Informatique - Programmation Système Avancée**


#### Exercice 1 : auto-blocage

Il est écrit dans le cours qu'un processus qui détient un verrou sur
un mutex ne doit jamais réexécuter ` pthread_mutex_lock()`. En faisant
tourner le programme [betise.c](betise.c), constatez ce qui
se passe si on ne suit pas cette consigne. N'hésitez pas à utiliser
`strace` ou `gdb` pour plus de détail.

#### Exercice 2 : la pile n'est pas partagée

En faisant tourner [betise2.c](betise2.c), constatez que
les mutex doivent absolument être en mémoire partagée et qu'on ne peut
pas se contenter d'une variable héritée. 

(pour suivre le fils, utiliser l'option `-f` de `strace` avec `gdb`, ou configurer
le `follow-fork-mode` de `gdb`)

#### Exercice 3 : une liste vraiment partagée

Cet exercice est à faire sur `lulu`.

J'ai créé sur `lulu` le segment de mémoire partagée `/liste`
(consultable à travers le SGF par le lien `/dev/shm/liste`) et le
sémaphore `/semaphore` (consultable par le lien
`/dev/shm/sem.semaphore`).

Le but de cet exercice est que chacun mette à jour le segment `/liste`
en y ajoutant son nom et son indice d'apparition. L'exclusion mutuelle
sera assurée grâce au sémaphore `/semaphore`.

Le format du segment de mémoire partagée `/liste` est le suivant :

* le début du segment contient deux entiers de type `int` :
  * le premier représente la taille des données déjà écrites,
  * le deuxième représente le dernier indice déjà écrit,

* viennent ensuite des chaînes de caractères de la forme :
  * indice (en décimal sous forme de chaîne)
  * espace
  * nom
  * retour à la ligne

Nous avons commencé à remplir le segment, vous pouvez regarder son
contenu avec la commande `od -c /dev/shm/liste`.

1. Écrire un programme qui permet d'afficher la liste des personnes
   enregistrées précédées de leur indice.
2. Écrire un programme qui permet d'ajouter un nom. Exemple
   d'utilisation :

```
$ ./lecture
1 Anne
2 Berenice
3 Cristina
$ ./ecriture Dominique
$ ./lecture
1 Anne
2 Berenice
3 Cristina
4 Dominique
```

Pour rappel (?) : les primitives de manipulations des sémaphores nommés
utiles pour l'utiliser comme un mutex
sont `sem_open` (pour ouvrir), `sem_wait` (pour attendre que le sémaphore
soit "prêt") et `sem_post` (pour rendre le sémaphore)


#### Exercice 3 : incrémentation simultanée

Écrire un programme qui ouvre un segment de mémoire partagée `/val` et
l'initialise pour contenir l'entier 0.

Écrire ensuite un programme `inc` qui doit incrémenter cent mille fois
la valeur de l'entier contenue dans le segment `/val`. Après la dernière 
itération, le programme lit
une dernière fois la valeur écrite et l'affiche sur sa sortie standard.

Lancer deux instances de ce programme : `./inc & ./inc`.

Si la plus grande valeur affichée n'est pas 200000, c'est que vous
avez oublié de protéger la zone critique de votre programme :
déterminez-la et protégez-la avec des mutex.

