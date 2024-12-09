#include <stdio.h>
#include <stdlib.h>
#include "Compartimento.h"

void FLVaziaRocha(LCompartimento *rLista) {
    rLista->pPrimeiro = (ApontadorRocha)malloc(sizeof(CCompartimento));
    rLista->pUltimo = rLista->pPrimeiro;
    rLista->pPrimeiro->pProx = NULL;
}

void LInsereRocha(LCompartimento* rLista, Rocha* pRocha) {
    rLista->pUltimo->pProx = (ApontadorRocha)malloc(sizeof(CCompartimento));
    rLista->pUltimo = rLista->pUltimo->pProx;
    rLista->pUltimo->ItemRocha = *pRocha;
    rLista->pUltimo->pProx = NULL;
}

void LImprimeRocha(LCompartimento *rLista) {
    int cont = 1;
    ApontadorRocha pAux = NULL;
    pAux = rLista->pPrimeiro->pProx;

    printf("\nROCHAS\n");
    printf("----------------------------------\n\n");
    while (pAux != NULL) {
        printf("ID: %d\n", cont++);
        printf("Peso: %d\n", pAux->ItemRocha.pesoI);
        printf("Valor: %d\n\n", pAux->ItemRocha.valorI);

        pAux = pAux->pProx;
    }
    printf("----------------------------------\n");
}