TP nº7 : segments partagés et mutexes (bis)
==================

**M1 Informatique - Programmation Système Avancée**

Si vous n'avez pas terminé le TP nº6, commencez par l'exercice 0!

#### Exercice 0 : incrémentation simultanée

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


#### Exercice 1 : barrière de synchronisation

*Attention : ce qu'il est demandé de programmer ici n'est pas la
bonne manière de faire, une amélioration est proposée dans l'exercice suivant*

Quand on parallélise un algorithme, il peut arriver qu'on soit en
mesure de paralléliser le début, mais qu'à un moment donné on ait
besoin des résultats de tous les calculs parallèles pour pouvoir
continuer. Comme exemple simple, si on trie un tableau par fusion, on
sépare le tableau en deux, chaque moitié est triée (et ces deux tris
sont indépendants donc peuvent être effectués en parallèle), puis on
fusionne les deux sous-tableaux triés qu'on a obtenus: on ne peut pas
commencer la fusion tant que les tris de ces deux sous-tableaux ne
sont pas terminés. On a donc besoin que les deux processus de tri
s'attendent à un moment.

Le but de cet exercice est d'implémenter une *barrière de
synchronisation* pour un nombre `N` de processus. Les processus
atteignant cette barrière de synchronisation doivent attendre que le
dernier processus atteigne la barrière pour continuer leurs exécutions
respectives. Concrètement, il faut implémenter :

* un type `barriere_t` qui pourra contenir
  * un mutex servant à protéger les parties critiques du code,
  * le nombre de processus qui ne sont pas encore arrivés à la
    barrière (au début cet entier vaut bien entendu `N`),
  * un entier qui vaudra vrai si et seulement si le barrière peut être
    ouverte,
* une fonction `void barriere(barriere_t*)` qui sera appelée exactement
une fois dans chaque processus, et qui vérifiera la propriété suivante:
  * si un processus n'est pas le dernier à atteindre la barrière, alors
    il doit attendre jusqu'à ce que le dernier processus atteigne la
    barrière pour pouvoir continuer; c'est-à-dire que la fonction
    `barriere` doit bloquer le processus appelant jusqu'à ce que le
    dernier processus appelle `barriere`;
  * lorsque le dernier processus appelle `barriere`, tous les processus
    sont débloqués simultanément.

La structure de type `barriere_t` devra bien sûr être stockée en mémoire partagée.

Veillez à initialiser le mutex à l'aide de `pthread_mutexattr_init`,
`pthread_mutexattr_sepshared` et enfin `pthread_mutex_init`, ou à
utiliser les deux fonctions fournies en cours et disponibles dans [init_memory.c](init_memory.c).

Vous testerez votre implémentation en deux étapes :

* un processus père initialisera la structure `barriere_t` et son
    contenu puis créera `N` processus fils grâce l'appel système `fork`;
* chacun des processus fils attendra un temps aléatoire de quelques
    secondes avant de faire un appel à `barriere`; chaque fils
    affichera un message à l'écran avec son pid à son arrivée à la
    barrière et juste après l'avoir franchie.

*Via* la commande `top`, vous surveillerez la consommation CPU des
processus en attente.  Que constatez-vous ?


#### Exercice 2 : barrière de synchronisation avec variables de condition

Modifiez votre solution de l'exercice précédent en utilisant des
variables de condition (*via* `pthread_cond_wait`) plutôt qu'une
attente active.

*Via* la commande `top`, vous surveillerez la consommation CPU des
processus en attente. Comparez avec la solution de l'exercice précédent.



#### Exercice 3 (_facultatif_) : le tri de Shell (Shellsort)

Si cela vous amuse, allez consulter la page Wikipedia du tri de (Donald)
Shell (plutôt [celle en anglais](https://en.wikipedia.org/wiki/Shellsort)).  

Cet algorithme de tri consiste en une succession d'étapes
parallèl(isabl)es, chacune consistant, pour un `gap` inférieur à celui de
l'étape précédente, à trier par insertion les `gap` sous-tableaux de la
forme `T[i::gap]` (en notation python); ces `gap` sous-tableaux étant
disjoints, chacun peut être trié indépendamment des autres par un
processus (ou thread, si vous préférez) dédié.  À la dernière étape,
`gap` vaut 1 et on réalise donc un tri par insertion classique, très
efficace car le tableau est déjà presque trié. En choisissant bien la
suite décroissante des `gap`s, on obtient un algorithme particulièrement
efficace en pratique.

Vous pouvez implémenter cet algorithme de tri à l'aide des barrières
précédemment programmées (en faisant attention au fait que le nombre de
processus parallèles diminue à chaque étape).

