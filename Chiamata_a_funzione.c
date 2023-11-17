# include <stdio.h>

typedef int (*puntatore_a_funzione) (int, int);
typedef int * puntatore_a_tipo_intero;

int somma(int a, int b){
    return a + b;
}

int main(void){
    int a = 5;
    int b = 5;
    
    puntatore_a_tipo_intero p = &a;
    puntatore_a_tipo_intero p_d = &b;

    puntatore_a_funzione pf = &somma;

    int risultato = pf(*p, *p_d);

    printf("%d\n", risultato);
    
    return 0;
}