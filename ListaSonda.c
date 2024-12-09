#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ListaSonda.h"

void FLVaziaSonda(LSonda* sLista) {
    sLista->pPrimeiro = (ApontadorSonda)malloc(sizeof(CSonda));
    sLista->pUltimo = sLista->pPrimeiro;
    sLista->pUltimo->pProx = NULL;
}

int LEVaziaSonda(LSonda* sLista) {
    return(sLista->pUltimo == sLista->pPrimeiro);
}

void LInsereSondas(LSonda* sLista, Sonda *pSonda) {
        sLista->pUltimo->pProx = (ApontadorSonda)malloc(sizeof(CSonda));
        sLista->pUltimo = sLista->pUltimo->pProx;
        sLista->pUltimo->sondas = *pSonda;
        sLista->pUltimo->pProx = NULL;   
}

void LImprimeSonda(LSonda* sLista) {
    ApontadorSonda pAux = sLista->pPrimeiro->pProx;

    printf("\nSONDAS\n");
    printf("---------------------------------\n\n");
    while (pAux != NULL) {
        printf("ID SONDA: %d\n", pAux->sondas.idSonda);
        printf("CAPACIDADE: %d\n", pAux->sondas.capacidade);

        pAux = pAux->pProx;
    }
    printf("---------------------------------\n");
}

void AlgoritmoGuloso(LSonda* listaSondas, Rocha* rochas, int num_rochas) {
    qsort(rochas, num_rochas, sizeof(Rocha), comparar_rochas);

    bool* rochaUsada = (bool*)calloc(num_rochas, sizeof(bool));
    ApontadorSonda sondaAtual;
    ApontadorSonda melhorSonda;


    for (int i = 0; i < num_rochas; i++) {
        if (!rochaUsada[i]) {
            melhorSonda = NULL;

            sondaAtual = listaSondas->pPrimeiro->pProx;
            while (sondaAtual != NULL) {
                float capacidadeRestante = sondaAtual->sondas.capacidade - sondaAtual->sondas.pesoAtual;
                if (rochas[i].pesoI <= capacidadeRestante) {
                    if (melhorSonda == NULL || (sondaAtual->sondas.valorAtual + rochas[i].valorI) > (melhorSonda->sondas.valorAtual + (melhorSonda != NULL? rochas[i].valorI: 0) ) ) {
                        melhorSonda = sondaAtual;
                    }
                }
                sondaAtual = sondaAtual->pProx;
            }

            if (melhorSonda != NULL) {
                LInsereRocha(&melhorSonda->sondas.CompartimentoR, &rochas[i]);
                melhorSonda->sondas.pesoAtual += rochas[i].pesoI;
                melhorSonda->sondas.valorAtual += rochas[i].valorI;
                rochaUsada[i] = true;
            }
        }
    }
    free(rochaUsada);
}

void ImprimeSolucao(LSonda *sLista) {
    ApontadorSonda sondaAtual = sLista->pPrimeiro->pProx;
    while (sondaAtual != NULL) {
        printf("Sonda %d: ", sondaAtual->sondas.idSonda);
        printf("Peso: %.0f, Valor: %d, ", sondaAtual->sondas.pesoAtual, sondaAtual->sondas.valorAtual); // Imprime peso e valor atuais

        printf("Solucao [");
        ApontadorRocha rochaAtual = sondaAtual->sondas.CompartimentoR.pPrimeiro->pProx;
        while (rochaAtual != NULL) {
            printf("%d", rochaAtual->ItemRocha.idRocha);
            rochaAtual = rochaAtual->pProx;
            if (rochaAtual != NULL) {
                printf(", ");
            }
        }
        printf("]\n");

        sondaAtual = sondaAtual->pProx;
    }
}  
