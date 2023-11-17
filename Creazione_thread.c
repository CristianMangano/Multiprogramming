/*Questo programma dovra' creare due thread ai quali dovra' fare stampare un numero di volte n (deciso dall'utente)
un certo carattere c (deciso dall'utente)*/

#include <stdio.h>
#include <pthread.h>

struct Dati_di_ingresso
{
    int n;
    char c;
};

void * stampa_carattere(void * parametri){
    struct Dati_di_ingresso * var;
    var = (struct Dati_di_ingresso *)parametri; // caste del puntatore void a puntatore a struct Dati_di_ingresso
    for (int i = 0; i < var->n; i++)
    {
        printf(" %c\n", var->c);
    }
    return NULL;
}

int main(void){
    
    struct Dati_di_ingresso variabile_uno, variabile_due;

    struct Dati_di_ingresso * p = &variabile_uno;
    struct Dati_di_ingresso * pps = &variabile_due;

    int * n = &(variabile_uno.n);
    int * nn = &(variabile_due.n);
    
    char * c = &(variabile_uno.c);
    char * cc = &(variabile_due.c);
    
    printf("Inserisci il numero di volte che vuoi stampare il primo carattere\n");
    scanf("%d", n);
    printf("Inserisci il primo carattere\n");
    scanf(" %c", c);

    printf("Inserisci il numero di volte che vuoi stampare il secondo carattere\n");
    scanf(" %d", nn);
    printf("Inserisci il secondo carattere\n");
    scanf(" %c", cc);

    pthread_t thread_id, thread_idd;
    
    pthread_create(&thread_id, NULL, &stampa_carattere, &variabile_uno);

    pthread_create(&thread_idd, NULL, &stampa_carattere, &variabile_due);

    pthread_join(thread_id, NULL);
    pthread_join(thread_idd, NULL);
    
    return 0;
}