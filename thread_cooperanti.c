/*scrivere un programma che riceve in input un file, genera un thread che lo modifichi e ove un altro thread si occupi della 
visualizzazione dell'output. Il programma resta sempre in attesa di un altro file*/

#include <stdio.h>
#include <pthread.h>

typedef struct Parametri
{
    FILE * puntatore_a_file;
    pthread_t thread_modificatore;
} Parametri;


void * visualizzazione(void * parametri){
    FILE * parametri_thread = (FILE *)parametri;
    puts("visualizzazione ...");
    fseek(parametri_thread, 0, SEEK_SET);
    char temp[50];
    fgets(temp, sizeof(temp), parametri_thread);
    puts(temp);
    pthread_exit(NULL);
    return NULL;
}

void * modifica_file(void * parametri){
    Parametri * parametri_thread = (Parametri *)parametri;
    puts("inserisci quello che vuoi scrivere");
    char temp[] = "hello";
    fputs(temp, parametri_thread->puntatore_a_file);
    pthread_t thread_visualizzatore;
    pthread_create(&thread_visualizzatore, NULL, &visualizzazione, parametri_thread->puntatore_a_file);
    pthread_join(thread_visualizzatore, NULL);
    //!-- fclose(parametri_thread->puntatore_a_file);
    pthread_exit(NULL);
    return NULL;
}

int main(void){

    while (1)
    {
        char nome_file[50];
        puts("inserisci il nome di un file .txt");
        scanf("%s", nome_file);
        
        Parametri Struttura_parametri;
        Struttura_parametri.puntatore_a_file = fopen(nome_file, "w+");
        
        if(Struttura_parametri.puntatore_a_file != NULL)
        {
            pthread_t thread_modificatore;
            Struttura_parametri.thread_modificatore = thread_modificatore;
            pthread_create(&(Struttura_parametri.thread_modificatore), NULL, &modifica_file, &Struttura_parametri);
            pthread_join(Struttura_parametri.thread_modificatore, NULL);
            fclose(Struttura_parametri.puntatore_a_file);
        } else
        {
            puts("problema nell'apertura del file. Riprova più tardi");
        }
    }
}
