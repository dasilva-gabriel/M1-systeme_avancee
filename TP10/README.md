TP nº10 : `select` et sockets
==================

**M1 Informatique - Programmation Système Avancée**


Le but de ce TP est d’écrire un petit programme de chat, sur le modèle
client-serveur, sans création de processus ou threads auxiliaires.

Le serveur doit tout d’abord créer une socket destinée à recevoir les
connexions des clients. Il doit ensuite, « simultanément », pouvoir
accepter de nouvelles connexions, recevoir des messages à diffuser (et
les diffuser), ou constater qu’un client s’est déconnecté. Le client doit
pour sa part se connecter à la socket, puis, « simultanément », écouter
les messages saisis par l’utilisateur et ceux diffusés par le serveur.

Petit extrait de `man select` :

> Under Linux, select() may report a socket file descriptor as "ready for
> reading", while nevertheless a subsequent read blocks.  This could for
> example happen when data has arrived but upon examination has wrong
> checksum and is discarded.  There may be other circumstances in which a
> file descriptor is spuriously reported as ready.  Thus it may be safer
> to use O_NONBLOCK on sockets that should not block.  

Il est donc vivement conseillé de travailler en mode non bloquant, même
si une lecture après un `select()` ne devrait pas bloquer.


#### Exercice 1 : un serveur (très) rudimentaire

Écrire un serveur rudimentaire qui crée une socket sur `/tmp/soquette`, se
met en condition de recevoir `NB_MAX` connexions, puis en accepte une et
lit un message (court). 

Vous pouvez tester votre serveur à l'aide du "client" suivant :
```bash
echo -n mon premier message | nc -U /tmp/soquette
```

Attention à ne pas oublier de détruire la socket à la fin !


#### Exercice 2 : un client (très) rudimentaire

Écrire un client rudimentaire qui se connecte à `/tmp/soquette`, dort 5
secondes, envoie un message contenant son pseudo, dort à nouveau 5
secondes, puis termine.

Modifier ensuite le client et le serveur pour que chaque message soit
toujours préfixé d'un `int` donnant la nature du message (`0`:
inscription, `1` : message à envoyer) et d'un
`size_t` indiquant la longueur du message (qui sera le pseudo de
l'utilisateur dans le cas d'une inscription). Attention à réaliser
l'écriture de manière atomique!

#### Exercice 3 : un client plus bavard

Modifier le client pour permettre que l’utilisateur saisisse des
messages sur l'entrée standard, qui seront ensuite transmis au serveur.

#### Exercice 4 : un serveur qui répond

Modifier le serveur et le client pour que le serveur réponde `ok` au
client qui lui envoie un message et que le client affiche `ko` 
une fois qu'il sait que le message a été reçu.

#### Exercice 5 : un serveur plus serviable 

Modifier le serveur pour qu’il puisse gérer plusieurs clients du type
précédent : il entre dans une boucle (finie, disons 10 tours) durant
laquelle il accepte les nouvelles connexions et réceptionne les messages
d’identification des clients déjà connectés, quel que soit l’ordre dans
lequel ces événements se produisent. 

Le serveur devra stocker toutes les informations permettant 
l'identification des clients connectés.

Modifier ensuite le serveur pour qu’il repère (et gère !) les
déconnexions de clients. On rappelle que la lecture sur une socket
sans écrivain renvoie 0.

#### Exercice 6 : un serveur plus patient

Modifier le serveur pour qu'il tourne en boucle infinie, mais termine
proprement en supprimant la socket s'il reçoit un signal `SIGINT` ou
`SIGTERM`.

#### Exercice 7 : et finalement, un vrai petit chat!

Modifier le serveur pour qu’il affiche chaque message reçu,
préfixé par le pseudo de l’expéditeur. Attention à bien lire
chaque message intégralement.

Modifier le serveur pour qu’il diffuse les messages reçus à tous
ses clients (toujours préfixé par le pseudo de l’expéditeur).
Modifier le client en conséquence.

