#ifndef LISTASONDA_H
#define LISTASONDA_H
#define MAXTAM 3
#include "Sonda.h"

typedef struct CelulaSonda *ApontadorSonda;
typedef struct CelulaSonda
{
    Sonda sondas;
    struct CelulaSonda *pProx;
} CSonda;

typedef struct
{
    ApontadorSonda pPrimeiro;
    ApontadorSonda pUltimo;
} LSonda;

void FLVaziaSonda(LSonda* sLista);
int LEVaziaSonda(LSonda* sLista);
void LInsereSondas(LSonda* sLista, Sonda *pSonda);
void LImprimeSonda(LSonda* sLista);
void AlgoritmoGuloso(LSonda *sLista, Rocha *rochas, int num_rochas);
void ImprimeSolucao(LSonda *sLista);

#endif