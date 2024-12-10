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
void bruteforce(LCompartimento *rochas, int capacity, int numSondas, LSonda *melhorSolucao);
void LImprimeSolucao(LSonda* sLista);

#endif