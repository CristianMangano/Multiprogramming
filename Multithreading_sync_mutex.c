//* PROGRAMMA FATTO DALLA IA

#include <stdio.h>
#include <pthread.h>

typedef struct Parametri {
    FILE *puntatore_a_file;
    pthread_t thread_modificatore;
    pthread_t thread_visualizzatore;
    pthread_mutex_t mutex; // Mutex per la sincronizzazione
} Parametri;

void *visualizzazione(void *parametri) {
    Parametri *parametri_thread = (Parametri *)parametri;

    pthread_mutex_lock(&parametri_thread->mutex); // Blocca il mutex prima di accedere al file
    fseek(parametri_thread->puntatore_a_file, 0, SEEK_SET);
    char temp[50];
    fgets(temp, sizeof(temp), parametri_thread->puntatore_a_file);
    puts(temp);
    pthread_mutex_unlock(&parametri_thread->mutex); // Sblocca il mutex dopo aver acceduto al file

    pthread_exit(NULL);
    return NULL;
}

void *modifica_file(void *parametri) {
    Parametri *parametri_thread = (Parametri *)parametri;

    pthread_mutex_lock(&parametri_thread->mutex); // Blocca il mutex prima di accedere al file
    puts("inserisci quello che vuoi scrivere");
    char temp[] = "hello";
    fputs(temp, parametri_thread->puntatore_a_file);
    pthread_mutex_unlock(&parametri_thread->mutex); // Sblocca il mutex dopo aver acceduto al file

    // Crea e avvia il thread visualizzatore
    pthread_create(&parametri_thread->thread_visualizzatore, NULL, &visualizzazione, parametri_thread);
    pthread_join(parametri_thread->thread_visualizzatore, NULL);

    pthread_exit(NULL);
    return NULL;
}

int main(void) {
    while (1) {
        char nome_file[50];
        puts("inserisci il nome di un file .txt");
        scanf("%s", nome_file);

        Parametri Struttura_parametri;
        Struttura_parametri.puntatore_a_file = fopen(nome_file, "w+");
        pthread_mutex_init(&Struttura_parametri.mutex, NULL); // Inizializza il mutex

        if (Struttura_parametri.puntatore_a_file != NULL) {
            pthread_create(&Struttura_parametri.thread_modificatore, NULL, &modifica_file, &Struttura_parametri);
            pthread_join(Struttura_parametri.thread_modificatore, NULL);
            //fclose(Struttura_parametri.puntatore_a_file);
        } else {
            puts("problema nell'apertura del file. Riprova più tardi");
        }

        pthread_mutex_destroy(&Struttura_parametri.mutex); // Distruggi il mutex
    }
}
