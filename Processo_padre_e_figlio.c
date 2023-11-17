#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    int pid = fork();
    if (pid == 0)
    {
        execl("Ordinamento", "Ordinamento", NULL);
    } else
    {
        wait(NULL);
        printf("i risultati del processo figlio\n");
    }
    return 0;
}