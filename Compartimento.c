#include <stdio.h>
#include <stdlib.h>
#include "Compartimento.h"

void FLVaziaRocha(LCompartimento *rLista) {
    rLista->firstR = 0;
    rLista->lastR = rLista->firstR;
}

int LEVaziaRocha(LCompartimento *rLista) {
    return (rLista->lastR == rLista->firstR);
}

int LInsereRocha(LCompartimento* rLista, Rocha pRocha) {
    if (rLista->lastR == MAXTAMR) {
        return 0;
    }
    rLista->rochas[rLista->lastR++] = pRocha;
    return 1;
}

void LImprimeRocha(LCompartimento *rLista) {
    int i;

    printf("\nROCHAS\n");
    printf("----------------------------------\n\n");
    for (i = rLista->firstR; i < rLista->lastR; i++) {
        printf("ID: %d\n", rLista->rochas[i].idRocha);
        printf("PESO: %d\n", rLista->rochas[i].pesoI);
        printf("VALOR: %d\n", rLista->rochas[i].valorI);
    }
}