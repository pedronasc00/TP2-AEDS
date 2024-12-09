#include <stdio.h>
#include <stdlib.h>
#include "Sonda.h"
#define MAXCAP 40

void InicializaSonda(Sonda *sonda, int idSonda) {
    sonda->idSonda = idSonda;
    sonda->capacidade = MAXCAP;
    sonda->pesoAtual = 0;
    sonda->valorAtual = 0;
    FLVaziaRocha(&sonda->CompartimentoR);
}