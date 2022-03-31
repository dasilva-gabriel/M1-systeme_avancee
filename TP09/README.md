TP nº9 : signaux (bis)
==================

**L3 Informatique - Système**



#### Exercice 1 : à table! -- de l'importance du positionnement précoce des gestionnaires

Écrire un programme `a-table.c` qui crée 5 processus, un père et ses
fils. Le père prépare le repas pendant que les fils se reposent. Lorsque
tout est prêt, ce qui lui prend un temps aléatoire entre 1 et 5
secondes, le père appelle ses fils en leur envoyant un signal. Les fils
affichent alors leur `pid` suivi du message `Oui papa, j'arrive!`, puis
terminent. Le père accueille chaque fils nominativement en affichant `Bon
appétit` suivi du `pid` à la terminaison du fils.

Modifier ensuite votre programme pour que le père n'attende plus avant
d'envoyer le signal, et vérifier le bon comportement (déterministe) du 
programme -- en particulier, aucun fils ne doit mourir sans réaliser son
affichage. Revoir le positionnement du gestionnaire dans le cas contraire!


#### Exercice 2 : ping-pong-pang -- de l'utilité du masquage

Qu'affiche le programme suivant? 
```C
int main() {
  printf("ping ");
  if (fork() == 0) printf("pong ");
  else printf("pang");
}
```

* Modifier ce programme pour obtenir (à tous les coups) l'affichage
  `ping pong pang`.

* Proposer une solution à base d'échange de signaux pour obtenir le même
  affichage, mais en inversant les rôles : c'est le fils qui doit
  réaliser le premier et le dernier affichage, tandis que le père réalise
  l'affichage intermédiaire. Ces affichages étant censés symboliser des
  actions potentiellement complexes, ils **ne devront pas** être réalisés
  dans le gestionnaire de signal, mais à l'extérieur.

  Vérifier le bon comportement de ce programme, c'est-à-dire qu'il provoque
  un affichage à la fois déterministe et sans blocage. Pour cela, exécuter le
  programme en boucle :
```
$ for i in `seq 100`; do ./pingpongpang; done
```
  En cas de blocage, penser au masquage!


#### Exercice 3 : un vrai ping-pong

Écrire un programme qui crée deux processus, un père et son fils, qui
jouent au ping-pong (sur la sortie standard) : le père affiche `ping`, le
fils affiche `pong`, etc., jusqu'à ce que l'un des deux, à un moment
aléatoire, affiche `Dehors, j'ai gagné!` puis termine.  L'autre processus
affiche alors `Bravo... une petite revanche?` avant de terminer à son
tour.

Les processus doivent se synchroniser par l'envoi de signaux.  On pourra
par exemple utiliser `SIGUSR1` pour taper dans la balle, et `SIGUSR2`
pour signaler que la balle de l'adversaire est sortie.

Vous pouvez partir du fichier [pingpong_squelette.c](pingpong_squelette.c) fourni. 

#### Exercice 4 : signaux et bascule de processus à l'arrière-plan

Écrire un (embryon de) shell capable de gérer la bascule de jobs entre
l'avant et l'arrière-plan.

Pour cela, on rappelle qu'un terminal ne peut avoir qu'un seul groupe de
processus à l'avant-plan, et que les processus des autres groupes
reçoivent respectivement un `SIGTTIN` ou un `SIGTTOU` s'ils tentent de
lire ou écrire sur le terminal.

À chaque nouvelle commande, il convient donc :
- de créer un nouveau groupe de processus (distinct de celui du shell)
  à l'aide de la primitive `setpgid()`,
- pour un lancement à l'avant-plan, de changer le groupe de contrôle du
  terminal à l'aide de la fonction `tcsetpgrp()`.

À la fin d'une exécution à l'avant-plan, ou si le job correspondant est
stoppé (par `SIGSTOP` ou `SIGTSTP`), le shell doit reprendre la main; pour
cela, il doit, tout d'abord, détecter la terminaison ou la suspension du
job grâce à un appel à `waitpid` correctement paramétré (penser à
`WUNTRACED`). Il doit ensuite reprendre le contrôle du terminal par un
appel à `tcsetpgrp()`. **Mais** cela va provoquer l'envoi d'un `SIGTTOU`
: il faut donc que `mppsh` ignore ou masque ce signal.

*(En revanche, les fils du shell ne doivent pas ignorer `SIGTTOU`; pensez
donc à rétablir le comportement par défaut avant tout `exec`)*

Pour que les jobs stoppés ne soient pas bloqués à jamais, il faut
également programmer des commandes internes `bg` et `fg`, qui devront
d'abord réveiller le job d'un petit coup de `SIGCONT` (à tout le
groupe), avant (pour `fg`) de modifier le groupe de contrôle du terminal.

