#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "ListaSonda.h"

int main() {
    clock_t start, stop;

    LSonda ListaSondas;
    Sonda sondas;
    LCompartimento ListaRocha;
    Rocha rochas;
    int valorI, pesoI;
    int QtdSondas = 3;
    
    printf("Nome do arquivo de entrada(com extensao): ");

    char nomearq[255];
    scanf("%254s", nomearq);
    FILE *arq = fopen(nomearq, "r");

    if (arq == NULL) {
        perror("Erro ao abrir arquivo\n");
        return 1;
    }

    int N;

    fscanf(arq, "%d", &N);
   
    FLVaziaRocha(&ListaRocha);
    FLVaziaSonda(&ListaSondas);

    for (int i = 0; i < QtdSondas; i++) {
        InicializaSonda(&sondas, i + 1);
        LInsereSondas(&ListaSondas, sondas);
    }
    
    for(int i = 0; i < N; i++){
        fscanf(arq, "%d %d", &pesoI, &valorI);
        InicializaRocha(&rochas, i, pesoI, valorI);
        LInsereRocha(&ListaRocha, rochas);
    }
    fclose(arq);

    start = clock();
    
    bruteforce(&ListaRocha, MAXCAP, QtdSondas, N, &ListaSondas);

    stop = clock();
    double time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("\nTempo gasto %.5lf segundos\n\n", time);

    return 0; 
}