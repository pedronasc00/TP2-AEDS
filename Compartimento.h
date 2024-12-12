#ifndef COMPARTIMENTO_H
#define COMPARTIMENTO_H
#include "Rocha.h"
#define MAXTAMR 1000

typedef int ApontadorRocha;

typedef struct 
{
    Rocha rochas[MAXTAMR];
    ApontadorRocha firstR, lastR;
} LCompartimento;

void FLVaziaRocha(LCompartimento* rLista);
int LEVaziaRocha(LCompartimento* rLista);
int LInsereRocha(LCompartimento* rLista, Rocha pRocha);
void LImprimeRocha(LCompartimento* rLista);

#endif