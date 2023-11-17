#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void childProcess(){
    char input[100];
    printf("dal processo figlio: inserisci qualcosa\n");
    fgets(input, sizeof(input), stdin);
    printf("processo figlio: hai inserito %s", input);
}

int main(void){
    pid_t pid = fork();

    if (pid == -1)
    {
        printf("errore nella creazione del processo figlio");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0)
    {
        childProcess();
        exit(EXIT_SUCCESS);
    } else
    {
        printf("sono il processo padre\n");
        int a = 6;
        int b = 3;
        printf("lo sai che %d per %d fa %d?\n", a, b, a*b);

        int status;
        waitpid(pid, &status, 0);   // il processo padre attende la fine del processo figlio

        if (WIFEXITED(status))
        {
            printf("il processo figlio ha avuto successo\n");
        } else
        {
            printf("il processo figlio ha avuto qualche problema\n");
        }
    }
    return 0;
}