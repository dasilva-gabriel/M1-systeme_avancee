#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 124

int isRegularFile(const char *path)
{

    int file = open(path, O_RDONLY);
    if (file < 0)
    {
        perror("Erreur dans le stat...");
        return -1;
    }

    struct stat status;

    if (stat(path, &status) == -1 || (status.st_mode & S_IFMT) != S_IFREG)
    {
        perror("L'une des référence n'est pas un fichier.");
        return -1;
    }

    close(file);

    return 1;
}

int diff(const char *pathA, const char *pathB)
{

    int fileA = open(pathA, O_RDONLY);
    int fileB = open(pathB, O_RDONLY);

    char bufA[BUFSIZE];
    char bufB[BUFSIZE];

    int line = 0;

    ssize_t sizeA, sizeB;
    while ((sizeA = read(fileA, bufA, BUFSIZE)) > 0 && (sizeB = read(fileB, bufB, BUFSIZE)) > 0)
    {

        if (sizeA != sizeB)
            return -1;

        for (int i = 0; i < sizeA; i++)
        {

            if (bufA[i] == '\n')
                line++;

            if (bufA[i] != bufB[i])
            {

                printf("Line: %d ----------------------------------- \n", line);
                printf("File A: %s\n", bufA);
                printf("File B: %s\n", bufB);
                printf("-------------------------------------------- \n");

                return line;
            }
        }
    }

    if (((sizeB = read(fileA, bufB, BUFSIZE)) > 0))
        return -1;

    return -2;
}

int main(int argc, char const *argv[])
{

    if (argc != 3)
    {
        perror("Vous devez inclure deux référence de fichiers.");
        return -1;
    }

    if (isRegularFile(argv[1]) == 1 && isRegularFile(argv[2]) == 1)
    {

        printf("Testing...\n");

        int diffRes = diff(argv[1], argv[2]);

        if (diffRes == -2)
        {
            printf("Les deux fichiers sont identiques\n");
        }
        else
        {
            printf("Oh... Oh... les fichiers ne sont pas identiques, ligne: %d\n", diffRes);
        }
    }

    return 0;
}
