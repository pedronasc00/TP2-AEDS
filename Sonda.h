#ifndef SONDA_H
#define SONDA_H
#include "Compartimento.h"

typedef struct
{
    int idSonda;
    float capacidade;
    float pesoAtual;
    int valorAtual;
    LCompartimento CompartimentoR;
} Sonda;

void InicializaSonda(Sonda* sonda, int idSonda);

#endif