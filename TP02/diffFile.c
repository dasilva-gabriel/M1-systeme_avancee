#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int isRegularFile(const char* path) {

    if(open(path, O_RDONLY) < 0) {
        perror("Erreur dans le stat...");
        return -1;
    }

    struct stat status;

    if ( stat(path, &status) == -1 || (status.st_mode & S_IFMT) != S_IFREG) {
        perror("L'une des référence n'est pas un fichier.");
        return -1;
    } 

    return 1;

}

int diff(const char* pathA, const char* pathB) {
}

int main(int argc, char const *argv[])
{
    
    if(argc != 3) {
        perror("Vous devez inclure deux référence de fichiers.");
        return -1;
    }

    if(isRegularFile(argv[1]) == 1 && isRegularFile(argv[2]) == 1) {
        printf("TOUT EST OK!");
    }

    return 0;
}
