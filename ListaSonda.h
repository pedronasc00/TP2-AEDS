#ifndef LISTASONDA_H
#define LISTASONDA_H
#define MAXTAMS 3
#include "Sonda.h"

typedef int ApontadorSonda;

typedef struct
{
    Sonda Sondas[MAXTAMS];
    ApontadorSonda first, last;
} LSonda;

void FLVaziaSonda(LSonda* sLista);
int LEVaziaSonda(LSonda* sLista);
int LInsereSondas(LSonda* sLista, Sonda pSonda);
LCompartimento* gerar_combinacoes(LCompartimento *rochas, int N);
void bruteforce(LCompartimento *rochas, int capacidade, int numSondas, int N, LSonda *melhorSolucao);
void LImprimeSonda(LSonda* sLista);

#endif