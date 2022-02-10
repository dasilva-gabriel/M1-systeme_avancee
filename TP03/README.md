TP nº3 : duplication de descripteurs (rappels) -- verrous
==================

**M1 Informatique - Programmation Système Avancée**

#### Exercice 1 : dupications et redirections

1. Écrire un programme qui prend en paramètre une ligne de commande suivie
d'un nom de fichier, et écrit la sortie de la commande dans le fichier.

Exemple d'utilisation :
```bash
$ ls /usr/
aarch64-linux-gnu  games    lib    libexec  locale  share  x86_64-linux-gnu
bin                include  lib64  local    sbin    src
$ ./a.out ls /usr/ toto
$ cat toto
aarch64-linux-gnu
bin
games
include
lib
lib64
libexec
local
locale
sbin
share
src
x86_64-linux-gnu
```

2. Il s'agit maintenant d'écrire un programme qui 
  * prend trois paramètres : deux lignes de commandes (chacune protégée par des guillemets) et
   un nom de fichier;
  * exécute une combinaison des deux commandes qui communiquent à travers un tube anonyme;
  * écrit le résultat dans le fichier.

Pour cela :
   * dans [split.c](code/split.c) est fournie une fonction `split()` 
     qui prend en argument une chaîne de caractères et renvoie
     un tableau de chaînes obtenu en découpant son argument grâce aux
     espaces, avec `NULL` sur la dernière case;
   * vous devez écrire une fonction
   ```C
   int execute(char **argv1, char **argv2, int fd);
   ```
   qui exécute la commande représentée par `argv1`, fournit sa sortie en
   entrée de la commande représentée par `argv2`, et écrit la sortie de
   celle-ci dans l'ouverture associée au descripteur `fd`;
   * utilisez les fonctions `split()` et `execute()` pour répondre à la
     question.
     
Exemple d'utilisation :
```bash
$ ls /usr/ | wc -l
13
$ ./a.out "ls /usr/" "wc -l" toto
$ cat toto
13
$ ls /usr/ | tr a-z A-Z
AARCH64-LINUX-GNU
BIN
GAMES
INCLUDE
LIB
LIB64
LIBEXEC
LOCAL
LOCALE
SBIN
SHARE
SRC
X86_64-LINUX-GNU
$ ./a.out "ls /usr/" "tr a-z A-Z" toto
$ cat toto
AARCH64-LINUX-GNU
BIN
GAMES
INCLUDE
LIB
LIB64
LIBEXEC
LOCAL
LOCALE
SBIN
SHARE
SRC
X86_64-LINUX-GNU
```


#### Exercice 2 : introduction aux verrous

* Écrire un programme qui ouvre un fichier `compteur` et y écrit
    l'entier 0 (représenté sous format texte). Il doit ensuite,
    100000 fois d'affilée, lire l'entier `n` contenu dans le fichier
    puis le remplacer par l'entier `n + 1`
* Modifier le programme pour qu'il crée *deux* processus,
  chacun incrémentant le compteur. Que constatez-vous?
* Modifier votre programme pour qu'il corrige le problème à l'aide
  de l'appel système `flock`, en réfléchissant au type de
  *lock* qu'il faudra utiliser, et à sa portée.


#### Exercice 3 : exclusion mutuelle

* Écrire une commande `lonely` qui affiche `je suis seul`
  toutes les cinq secondes sur sa sortie standard.  Pour garantir
  qu'au maximum une instance de `lonely` s'exécute à tout instant,
  le programme devra créer (de façon exclusive, `O_EXCL`) un fichier
  `/tmp/lonely.lock`, dans lequel il écrira son *pid*. Si une
  autre instance est déjà en cours d'exécution, le programme retourne 127
  immédiatement.  Au bout de `MAX` affichages, le programme termine,
  sans oublier de supprimer le fichier `/tmp/lonely.lock`.
* Lancer, tuer, puis relancer votre programme.
Quel est le problème?
* Modifier votre programme pour qu'il utilise un verrou exclusif de type BSD,
  en faisant toujours en sorte qu'il quitte immédiatement si une autre
  instance est en cours d'exécution.


#### Exercice 4 : réservation de trains

Le but de cet exercice est d'implémenter un système de réservation de
places dans un train.  Le train sera représenté par un fichier de 1032
octets, où l'octet d'indice `n` vaut 1 si la place `n` est occupée, et
0 sinon.

* Créer un fichier `train.data` de 1032 octets nuls (par
  exemple par `dd if=/dev/zero bs=1032 count=1 of=train.data`).
* Écrire un programme qui prend un *lock* exclusif sur le fichier,
  recherche une place libre, la marque comme occupée, relâche le *lock*,
  puis affiche le numéro de la place réservée.  Si toutes les places
  sont occupées, votre programme affichera un message d'erreur
  compréhensible.
* Modifier le programme pour qu'il utilise un *lock* partagé lors de
  la recherche. S'il trouve une place libre, il devra relâcher le *lock*
  et prendre un *lock* exclusif pour la réservation. Pourquoi faut-il à
  nouveau vérifier la disponibilité de la place après avoir pris le
  *lock* exclusif? Quel est l'avantage de cette approche?
* Serait-il possible de promouvoir le *lock* au lieu de le relâcher?



#### Exercice 5 : verrou brisé

  Tester les comportements respectifs des verrous **POSIX** et **BSD**, après
  chaque étape, dans les contextes suivants (sous linux, vous pouvez
  par exemple introduire des pauses de 5 secondes et consulter
  `/proc/locks`):

* Écrire un programme qui pose un verrou sur un fichier `test_verrou`,
duplique le descripteur, puis ferme le second descripteur. (Vérifier si le verrou est toujours là.)
* Écrire un programme qui pose un verrou sur un fichier `test_verrou`,
ouvre une seconde fois `test_verrou`, puis ferme la seconde
ouverture. (Vérifier si le verrou est toujours là.)
* Écrire un programme qui pose un verrou sur un fichier `test_verrou`,
crée un processus fils, puis (dans le père) ferme le
descripteur. (Vérifier si le verrou est toujours là.)

  Recommencer en utilisant des verrous
  [OFD](https://www.gnu.org/software/libc/manual/html_node/Open-File-Description-Locks.html).



#### Exercice 6 (facultatif...) : substitution de processus

Le mécanisme de substitution de processus généralise d'une certaine
manière la redirection par tube. Il permet de remplacer, dans une ligne
de commande dont les arguments sont censés être des noms de fichiers,
un (ou plusieurs) de ces fichiers par (l'entrée ou) la sortie d'autres
processus.

Un exemple valant mieux qu'un long discours :

```bash
$ cat > toto
a
c
b
a
a
b
$ cat > tutu
b
c
c
a
c
$ cmp toto tutu 
toto tutu sont différents: octet 1, ligne 1
$ cmp <(sort toto) <(sort tutu)
/dev/fd/63 /dev/fd/62 sont différents: octet 3, ligne 2
$ cmp <(sort toto | uniq) <(sort tutu | uniq)
$ 
```

Cet exemple montre au passage par quel artifice cela est rendu possible :
le shell a créé deux fichiers (en l'occurrence des tubes anonymes) qui
apparaissent dans l'arborescence `/dev/fd`, qui sous linux pointe sur
`/proc/self/fd`, qui liste les descripteurs ouverts par le processus
`self`.

Écrire un programme `compare` qui teste si deux fichiers contiennent les
mêmes lignes, dans un ordre et avec une multiplicité pouvant différer --
autrement dit, tel que `compare toto tutu` simule la commande `cmp <(sort
toto | uniq) <(sort tutu | uniq)`.

Pour cela, le programme devra créer deux tubes anonymes et deux processus 
fils pour exécuter les deux commandes "annexes", avant d'exécuter `cmp`.
Les deux processus fils pourront utiliser la fonction `execute()` de
l'exercice précédent.


*Si vous n'êtes pas sous Linux* et ne disposez pas de la
pseudo-arborescence `/proc` : travaillez sur `lulu` par `ssh`, ou bien
créez des tubes nommés en lieu et place des tubes anonymes.
