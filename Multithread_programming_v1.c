/*scrivere un programma che riceve in input un file, genera un thread che lo modifichi e ove un altro thread si occupi della 
visualizzazione dell'output. Il programma resta sempre in attesa di un altro file*/

//*----- PROGRAMMA INGENUO ----

#include <stdio.h>
#include <pthread.h>

void * visualizzazione(void * parametri){
    FILE * parametri_thread = (FILE *)parametri;
    puts("visualizzazione ...");
    fseek(parametri_thread, 0, SEEK_SET);
    char temp[50];
    fgets(temp, sizeof(temp), parametri_thread);
    puts(temp);
    return NULL;
}

void * modifica_file(void * parametri){
    FILE * parametri_thread = (FILE *)parametri;
    puts("inserisci quello che vuoi scrivere");
    char temp[] = "hello";
    fputs(temp, parametri_thread);
    pthread_exit(NULL);
    return NULL;
}

int main(void){

    while (1)
    {
        char nome_file[50];
        puts("inserisci il nome di un file .txt");
        scanf("%s", nome_file);
        FILE * puntatore_a_file = fopen(nome_file, "w+");
        
        if(puntatore_a_file != NULL)
        {
            pthread_t thread_modificatore;
            pthread_t thread_visualizzatore;
            pthread_create(&thread_modificatore, NULL, &modifica_file, puntatore_a_file);
            pthread_join(thread_modificatore, NULL);
            pthread_create(&thread_visualizzatore, NULL, &visualizzazione, puntatore_a_file);
            pthread_join(thread_visualizzatore, NULL);
            fclose(puntatore_a_file);
        } else
        {
            puts("problema nell'apertura del file. Riprova più tardi");
        }
    }
}