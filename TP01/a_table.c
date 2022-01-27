#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int randomNum(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

int main(int argc, char const *argv[])
{

    int n = 7;

    pid_t pids[n];
    int found[n];

    for (int i = 0; i < n; ++i)
    {
        if ((pids[i] = fork()) == 0)
        {
            found[i] = 0;
            srand(getpid());
            int num = randomNum(5, 20);

            sleep(num);

            printf("(%d) Voilà, voilà, j'arrive...\n", getpid());

            exit(0);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        printf("%d, ",pids[i]);
    }

    printf("à table!\n");

    int status;
    pid_t pid;
    int remaining = n;
    while (remaining > 0) {

        while((pid=waitpid(-1, NULL, WNOHANG)) <= 0) {
            printf("A table!\n");
            sleep(1);
        }

        int i;
        int lastPid = -1;
        for(i = 0; i < n; i++) {
            if(pid == pids[i]) {
                found[i] = 1;
            } else {
                if(found[i] == 0) {
                    if(lastPid == -1) lastPid = pids[i];
                    else if(lastPid > -1) lastPid = -2;
                }
            }
        }

        switch(lastPid) {
            case -2: printf("Ah, voici %ld! Les autres, à table!\n", (long)pid); --remaining;  break;
            case -1: printf("Ah, enfin! C'est pas trop tôt, tu n'es pas à l'auberge ici!\n"); --remaining; break;
            default: printf("Ah, voici %ld! %i, à table, on n'attend plus que toi!\n", (long)pid, lastPid); --remaining; break;
        }
        
        fflush(stdout);
    }
}

/*int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    int status;

    if(pid == 0) {

        int randTime = 10;
        printf("(%d) dodo zzz %d\n", pid, randTime);
        fflush(stdout);
        sleep(randTime);
        
        printf("(%d) Voilà, voilà, j'arrive...\n", pid);
        fflush(stdout);

        exit(0);

    } else {
        
        while(waitpid(pid, NULL, WNOHANG) <= 0) {
            printf("A table!\n");
            sleep(1);
        }

        printf("Ah, enfin! C'est pas trop tôt, tu n'es pas à l'auberge ici!\n");
        fflush(stdout);

    }

    return 0;
}*/
