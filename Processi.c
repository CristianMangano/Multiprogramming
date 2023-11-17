#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    printf("\n");
    char saluto[50] = "ciao mondo ";
    int pid = fork();
    if (pid == 0)
    {
        char saluto_specifico[] = "sono il figlio";
        strcat(saluto, saluto_specifico);
        puts(saluto);
        printf("\n");
        puts("nel codice figlio!");
        printf("\n");
    } else
    {
        wait(NULL); //La syscall wait() fa in modo che per prima venga eseguito il codice padre (quindi la primitiva fork() mi
                    // restituisca subito il pid del processo figlio che è 0, viene eseguito il processo figlio e poi viene esegito
                    // il processo padre
        char saluto_specifico[] = "sono il padre";
        strcat(saluto, saluto_specifico);
        puts(saluto);
        printf("\n");
    }

    char saluto_variabile_globale[] = "ciao, di nuovo nel main!";
    puts(saluto_variabile_globale);
    printf("\n");
    puts(saluto);   //Da notare che dopo essere usciti dal processo figlio viene modificata questa variabile globale ma non viene
                    // modificata la variabile dentro il processo padre
    printf("\n");
    
    return 0;
}