#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ListaSonda.h"

int main() {
    clock_t start, stop;

    LSonda ListaSondas;
    Sonda sondas;
    LCompartimento ListaRocha;
    Rocha rochas;
    int valorI, pesoI;
    int QtdSondas = 3;
    
    printf("Nome do arquivo de entrada: ");

    char nomearq[33];
    FILE *arq;
    scanf("%32s", nomearq);
    arq = fopen(nomearq, "r");

    int N;

    fscanf(arq, "%d", &N);
   
    FLVaziaSonda(&ListaSondas); // Não é mais necessário inicializar as sondas individualmente
    FLVaziaRocha(&ListaRocha);
    
    for(int i = 0; i < N; i++){
        fscanf(arq, "%d %d", &pesoI, &valorI);
        InicializaRocha(&rochas, i, pesoI, valorI);
        LInsereRocha(&ListaRocha, rochas);
    }
    fclose(arq);

    LSonda melhorSolucao;
    FLVaziaSonda(&melhorSolucao); // Initialize melhorSolucao

    start = clock();

    bruteforce(&ListaRocha, MAXCAP, QtdSondas, &melhorSolucao);

    stop = clock();
    double time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("\nTempo gasto %.5lf segundos\n\n", time);

    return 0; 
}