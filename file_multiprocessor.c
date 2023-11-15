/*scrivere un programma che riceve in input un file, genera un thread che lo modifichi e ove un altro thread si occupi della 
visualizzazione dell'output. Il programma resta sempre in attesa di un altro file*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct Parametri
{
    FILE * puntatore_a_file;
    pthread_t thread_id;
} Parametri;


void * visualizzazione(void * parametri){
    Parametri * parametri_thread = (Parametri *)parametri;
    pthread_join(parametri_thread->thread_id, NULL);
    //todo: visualizzazione del file di output (usando il puntatore a file della struct)
    fclose(parametri_thread->puntatore_a_file);
    free(parametri_thread);
    return NULL;
}

void * modifica_file(void * parametri){
    
    pthread_t thread_visual;
    pthread_create(&thread_visual, NULL, &visualizzazione, &parametri);

    Parametri * parametri_thread = (Parametri *)parametri; //* cast esplicito del puntatore dei parametri di input del thread
    FILE * puntatore_a_file = parametri_thread->puntatore_a_file;
    //todo: operazioni del thread sul file usando puntatore_a_file ...
    return NULL;
}

int main(void){

    while (1)
    {
        //* per il multithreding ad ogni ciclo viene creata dinamicamente una nuova struttura e viene 
        //* restituito il puntatore ad essa, così non si va a modificare i campi della struttura creata
        //* precedentemente e sulla quale il thread potrebbe star ancora lavorando!

        char nome_file[50];
        scanf("%s", nome_file);
        Parametri * Struttura_di_parametri = (Parametri *)malloc(sizeof(Parametri));
        Struttura_di_parametri->puntatore_a_file = fopen(nome_file, "w");
        pthread_t thread_id;
        Struttura_di_parametri->thread_id = thread_id;
        pthread_create(&thread_id, NULL, &modifica_file, &Struttura_di_parametri);
    }
}
