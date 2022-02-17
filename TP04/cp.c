#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    if(argc != 3) {
        perror("Il faut uniquement un nom de fichier en paramètre.");
        return -1;
    } 

    int src = open(argv[1], O_RDONLY);
    int dest = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0775);

    if(src == -1 || dest == -1) {
        perror("Impossible d'ouvrir le fichier.");
        return -1;
    }

    struct stat sb;
    if(stat(argv[1], &sb) == -1) {
        perror("Erreur de stat.");
        return -1;
    }

    size_t length = sb.st_size;

    char *w = mmap(0, length, PROT_READ, MAP_PRIVATE, a, 0);

    if(w == MAP_FAILED) {
        perror("Erreur de lecture");
        return -1;
    }

    printf("%s", w);

    close(src);
    close(dest);

    return 0;
}
