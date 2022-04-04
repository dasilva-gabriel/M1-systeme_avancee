#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#define NB_MAX 3

int main(int argc, char const *argv[])
{
    int desc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (desc < 0)
        exit(0);

    char *path = "/tmp/soquette";
    unlink(path);
    struct sockaddr_un un;
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, path);

    size_t size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    if (bind(desc, (struct sockaddr *)&un, (socklen_t)size) < 0)
    {
        printf("probably you should :  rm /tmp/soquette\n");
        exit(1);
    }

    int i = 0;
    while (i < NB_MAX)
    {

        if (listen(desc, 1) < 0)
        {
            printf("Erreur listen\n");
            exit(1);
        }

        int con = accept(desc, NULL, NULL);
        if (con < 0)
        {
            printf("Erreur accept\n");
            exit(1);
        }

        i++;
        printf("La connexion n°%i a été prise en compte.\n", i);

        if (fork() == 0)
        {

            int i;
            ssize_t v;
            while ((v = read(con, &i, sizeof(i))) > 0)
            {
                if (v != sizeof(i))
                {
                    printf("Erreur read\n");
                    exit(1);
                }
                i++;

                write(con, &i, sizeof(i));

                printf("Enfant %ld créé\n", (long) getpid() );
            }
        }
        return 0;
    }
}
