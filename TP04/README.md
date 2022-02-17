TP nº 5 : `mmap`
==================

**M1 Informatique - Programmation Système Avancée**


#### Exercice 1 : `cat` et `cp` sans `read()`

* Écrire un programme qui projette en mémoire (avec `mmap()`)
  un fichier dont le nom lui est passé en paramètre, puis affiche son
  contenu sur sa sortie standard ***sans*** appel à `read()`.

* Écrire un programme qui prend deux paramètres `src` et `dest`, et qui
  copie le fichier de nom `src` vers le fichier de nom `dest` sans
  utiliser de tampons ni les appels système `read()` et `write()`.
  Attention aux tailles relatives des fichiers -- penser à `ftruncate()`.


#### Exercice 2 : chiffrement de César

Écrire un programme qui projette en mémoire un fichier texte supposé
ne contenir que des lettres et décale toutes les lettres de la même
valeur, en suivant le code de César.

On pourra utiliser la fonction suivante :

```C
char cesar(char c, int offset) {
  if(c>='a' && c<='z')
    return (char) ('a' + ( (c-'a'+offset)%26 ));
  if (c>='A' && c<='Z')
    return (char) ('A' + ( (c-'A'+offset)%26 ));
  return c;
}
```

#### Exercice 3 : chiffrement de Vigenère

Écrire un programme qui projette en mémoire un fichier texte supposé
ne contenir que des lettres. Il faut ensuite appliquer un code de
Vigenère de la manière suivante : il y aura autant de fils que la
longueur de la clé, et chaque fils s'occupera de son propre
décalage. Tous les fils travailleront en parallèle sur la projection
mémoire du fichier.
