/*Questo programma dato un file che contiene dei nomi li inserisce in una lista semplicemente
concatenata (a run-time) in ordine alfabetico, poi li stampa a video ed infine libera la memoria*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Persona
{
    char nome[50];
    char cognome[50];
    struct Persona* next;
} persona;

persona* inserisci(persona* head, persona* occorrenza){
    persona* avant_punt = head;
    persona* post_punt = head;
    while ((post_punt != NULL) && (strcmp(occorrenza->cognome, post_punt->cognome) > 0))
    {
        avant_punt = post_punt;
        post_punt = post_punt->next;
    }
    if (avant_punt == post_punt)
    {
        occorrenza->next = head;
        head = occorrenza;
    } else
    {
        occorrenza->next = post_punt;
        avant_punt->next = occorrenza;
    }
    return head;
}

int main(void) {
    FILE* file = fopen("Nomi_non_ordinati.txt", "r");
    char linea[100];
    persona* head = NULL;

    while (fgets(linea, sizeof(linea), file) != NULL) {
        char tempNome[50];
        char tempCognome[50];
        sscanf(linea, "%s\t%s", tempNome, tempCognome);

        persona* occorrenza = (persona*)malloc(sizeof(persona));

        if (occorrenza == NULL) {
            fprintf(stderr, "Errore di allocazione della memoria.");
            exit(EXIT_FAILURE);
        }

        strcpy(occorrenza->nome, tempNome);
        strcpy(occorrenza->cognome, tempCognome);
        occorrenza->next = NULL;
        head = inserisci(head, occorrenza);
    }

    // Stampa la lista di persone
    persona* temp = head;
    while (temp != NULL) {
        puts(temp->cognome);
        temp = temp->next;
    }

    // Libera la memoria
    while (head != NULL) {
        persona* temp = head;
        head = head->next;
        free(temp);
    }

    // Chiudi il file
    fclose(file);

    return 0;
}