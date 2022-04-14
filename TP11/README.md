TP nº11 : sockets unix et sql
==================

**M1 Informatique - Programmation Système Avancée**

Dans ce TP on vous propose de coder un serveur et un client `sqlite` extrêmement simplifiés. Les requêtes seront du type
```C
struct query {
   int select;
   char from[LEN];
   int where;
   char equals[LEN];
}
```
qui correspondrait à la requête `sql` : `SELECT select FROM from WHERE where=equals`. On suppose qu'après le dernier caractère
intéressant dans `from` et `equals`, il y a un `\0`.

Contrairement aux requêtes `sql` classiques, on désigne donc les attributs par des numéros de colonne et on se restreint 
à afficher un seul attribut dans le résultat et à imposer une seule condition dans la sélection.

Chaque table est en fait un fichier `csv` dont le séparateur est une virgule et sans délimiteur de texte. Exemple :
```csv
Dupond,Patrick,32
Ali,Mohamed,47
```
Dans cet exemple, si on veut la liste des prénoms des gens ayant 32 ans, la requête correspondante sera
```C
struct query requete = {1, "fichier.csv", 2, "32"};
```

Pour faire cela, il faut mettre en place un serveur et un client. Si vous respectez bien les formats de l'énoncé, vous 
pourrez tester en croisant entre vous serveur et client (sur `lulu`). Tirez au hasard lequel vous codez en premier.

La communication devra se faire par sockets UNIX en mode datagramme.

Le client prendra en paramètre sur la ligne de commande la référence (dans le SGF) de la socket du serveur qu'il veut interroger.
Chaque message envoyé au serveur contiendra un `struct query` décrivant la requête.

Les envois et réceptions peuvent se faire indifféremment avec `sendto` et `recvfrom` ou `sendmsg` et `recvmsg`.

Le serveur retournera la réponse au format suivant :
```C
struct result {
   int nb;
   char rep[N][LEN];
}
```
où `N` désigne un nombre maximal de réponses, `nb` le nombre réel de réponses (supposé inférieur à `N`). 


Un exemple de fichier `csv` que vous pouvez utiliser : [ratp.csv](ratp.csv).
