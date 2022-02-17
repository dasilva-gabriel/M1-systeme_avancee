#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char cesar(char c, int offset) {
  if(c>='a' && c<='z')
    return (char) ('a' + ( (c-'a'+offset)%26 ));
  if (c>='A' && c<='Z')
    return (char) ('A' + ( (c-'A'+offset)%26 ));
  return c;
}

int main(int argc, char const *argv[]) {
    
    if(argc != 2) {
        perror("Il faut uniquement un nom de fichier en paramètre.");
        return -1;
    } 

    int a = open(argv[1], O_RDONLY);

    if(a == -1) {
        perror("Impossible d'ouvrir le fichier.");
        return -1;
    }

    struct stat sb;
    if(stat(argv[1], &sb) == -1) {
        perror("Erreur de stat.");
        return -1;
    }

    size_t length = sb.st_size;

    char *w = mmap(0, length, PROT_WRITE | PROT_READ, MAP_PRIVATE, a, 0);

    if(w == MAP_FAILED) {
        perror("Erreur de lecture");
        return -1;
    }

    for(unsigned int i = 0; i < length; i++) {
        w[i] = cesar(w[i], 1);
    }

    printf("%s", w);
    close(a);

    return 0;
}