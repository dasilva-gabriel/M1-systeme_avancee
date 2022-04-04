#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <stdbool.h>
#include <stddef.h>

#define NB_MAX = 3;

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

#define BACKLOG 5
    while (true)
    {

        if (listen(desc, BACKLOG) < 0)
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
    }
    return 0;
}
