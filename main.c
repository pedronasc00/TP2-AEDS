#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ListaSonda.h"

int main() {
   

    LSonda ListaSondas;
    Sonda sondas;
    int valorI, pesoI;
    int QtdSondas = 3;
    
    printf("Nome do arquivo de entrada: ");

    char nomearq[33];
    FILE *arq;
    scanf("%32s", nomearq);
    arq = fopen(nomearq, "r");

    int N;

    fscanf(arq, "%d", &N);
   
    FLVaziaSonda(&ListaSondas);
    
    for (int i = 0; i < QtdSondas; i++) {
        InicializaSonda(&sondas, (i + 1));
        LInsereSondas(&ListaSondas, &sondas);
    }
    
    Rocha *rochas = (Rocha*)malloc(N * sizeof(Rocha));
    for(int i = 0; i < N; i++){
        fscanf(arq, "%d %d", &pesoI, &valorI);
        InicializaRocha(&rochas[i], i, pesoI, valorI);
    }

    fclose(arq);
    clock_t start, stop;
    start = clock();
    AlgoritmoGuloso(&ListaSondas, rochas, N);
    ImprimeSolucao(&ListaSondas);

    free(rochas);

    stop = clock();
    double time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("\n Tempo Gasto = %.5lf segundos\n", time);
}
