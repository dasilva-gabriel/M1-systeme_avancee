TP nº2 : manipulations de fichiers et de réprtoires
==================

**M1 Informatique - Programmation Système Avancée**

#### Exercice 1 : `diff`

Écrire un programme qui prend en arguments deux chaines de caractères
et teste s'il s'agit des références de deux fichiers ordinaires ayant 
le même contenu.

Pour cela, écrire deux fonctions distinctes :

* l'une, prenant en paramètre une chaîne de caractères, testera s'il
  s'agit de la référence valide d'un fichier ordinaire,

* l'autre, prenant en paramètre deux références valides de fichiers
  ordinaires, testera si leur contenu est identique; pour cela, elle
  lira en boucle leur contenu à l'aide de buffers de taille `BUFSIZE`.

Effectuez ensuite des tests pour différentes valeurs de BUFSIZE` (1,
1<<10, 1<<20) sur de très gros fichiers -- par exemple un gros fichier `csv` 
tel qu'on peut en trouver
[ici](https://www.data.gouv.fr/fr/datasets/parcoursup-2021-voeux-de-poursuite-detudes-et-de-reorientation-dans-lenseignement-superieur-et-reponses-des-etablissements/) : comparer un fichier à lui-même, puis faire une copie comportant 
une erreur assez loin dans le fichier.

Modifier la deuxième fonction pour qu'elle s'arrête à la première
différence trouvée, en affichant *la ligne concernée* (numéro et contenu
dans chaque fichier). 


#### Exercice 2 : `diff` récursif

Modifier le programme précédent pour qu'il puisse prendre en arguments
deux références de répertoires lorsqu'il est appelé avec l'option `-r`,
et compare dans ce cas les sous-arborescences dont ils sont les racines
respectives.

Il faudra donc :

* vérifier si les arguments sont des références valides de répertoires;

* pour chaque entrée de chacun des deux répertoires, tester si le même
  nom apparaît dans l'autre répertoire, et référence un fichier de même
  type;

* si une entrée identique est trouvée de part et d'autre, et qu'il s'agit
  de fichiers ordinaires, appeler la fonction écrite à l'exercice
  précédent;

* si une entrée identique est trouvée de part et d'autre, et qu'il s'agit
  de liens symboliques, vérifier que le `linkname` est le même;

* si une entrée identique est trouvée de part et d'autre, et qu'il s'agit
  de répertoires, poursuivre récursivement le parcours.


#### Exercice 3 : recodage des entrées/sorties haut niveau

L'exécution d'un appel système est particulièrement gourmande en temps
(environ 10000 fois plus lente que l'appel à une fonction qui ne contient
pas elle-même un appel système). Il est donc préférable de limiter les
appels systèmes. C'est dans ce but que les fonctions d'entrées/sortie
haut niveau (`fopen`, `fread`, `fwrite`, `fclose`) ont été écrites. On se
propose de vous les faire réécrire dans cet exercice.

Qu'est-ce-qui différencie `read` de `fread` ? Évidemment, si `fread`
se contentait d'appeler `read`, il ne serait pas plus rapide. En fait
chaque appel à `read` fait une lecture sur disque, alors que `fread`
gère un buffer qui lui permet de prendre de l'avance : même si
l'utilisateur demande à lire moins de caractères que la taille du
buffer, `fread` remplit ce buffer. À la lecture suivante, au lieu
d'accéder à nouveau au fichier, il récupère les données dans son
buffer. Ce buffer est caché dans le type opaque `FILE`.

Similairement, `fwrite` stocke les données
à écrire dans un buffer et les données ne sont a priori pas écrites
au moment de l'appel à `fwrite`. Les données sont en général écrites
quand le buffer est plein, mais pas uniquement : on peut forcer leur
écriture avec `fflush`, et sur certains `FILE *` elles peuvent être
écrites à d'autres moments (par exemple en cas de retour à la ligne si
`stdout` est un terminal).

Nous vous proposons de définir un type `MYFILE` de la manière suivante :

```C
#define BUFSIZE

enum mode {r, w, a};

typedef struct myfile {
   int fd;
   enum mode m;
   int begin, end;
   char buffer[BUFSIZE];
} MYFILE;
```

et d'écrire les fonctions

```C
MYFILE *myfopen(char *pathname, enum mode m);
void myfclose(MYFILE *stream);
int myfread(void *ptr, int size, int nmemb, MYFILE *stream);
int myfwrite(void *ptr, int size, int nmemb, MYFILE *stream);
int myfflush(MYFILE *stream);
```
dont les comportements doivent être équivalents respectivement à `fopen`,
`fclose`, `fread`, `fwrite` et `fflush`.

Par exemple, `myfread` peut appliquer l'algorithme suivant :

* si le buffer contient suffisamment de données non encore traitées,
  les lire directement dans le buffer (sans appel à `read`, donc);
* sinon,
  * commencer par traiter les données éventuellement disponibles dans le buffer;
  * tant que toutes les données demandées n'ont pas été lues et qu'il reste des
    données à lire dans le fichier,
  * remplir le buffer (soit en entier, soit avec les données
    disponibles)
  * utiliser les nouvelles données dans le buffer pour continuer la
    lecture.


