#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ListaSonda.h"

void FLVaziaSonda(LSonda* sLista) {
    sLista->first = 0;
    sLista->last = sLista->first;
}

int LEVaziaSonda(LSonda* sLista) {
    return(sLista->last == sLista->first);
}

int LInsereSondas(LSonda* sLista, Sonda pSonda) {
    if (sLista->last == MAXTAMS) {
        return 0;
    }
    sLista->Sondas[sLista->last++] = pSonda;
    return 1;
}

void bruteforce(LCompartimento *rochas, int capacity, int numSondas, LSonda *melhorSolucao) {
    int numRochas = rochas->lastR - rochas->firstR;
    int iter = pow(2, numRochas);
    int melhorValorTotal = -1;

    for (int i = 0; i < iter; i++) {
        LSonda sondasAtual;
        FLVaziaSonda(&sondasAtual);
        for (int k = 0; k < numSondas; k++) {
            Sonda sonda;
            InicializaSonda(&sonda, k + 1);
            LInsereSondas(&sondasAtual, sonda);
        }

        int valorTotalAtual = 0;
        int *rochasUsadas = (int *)calloc(numRochas, sizeof(int));

        for (int j = 0; j < numRochas; j++) {
            if ((i >> j) & 1 && !rochasUsadas[j]) {
                int melhorSonda = -1;


                for (int k = 0; k < numSondas; k++) {
                    int potentialValue = sondasAtual.Sondas[k].valorAtual + rochas->rochas[j].valorI;
                    int potentialWeight = sondasAtual.Sondas[k].pesoAtual + rochas->rochas[j].pesoI;

                    if (potentialWeight <= capacity && (melhorSonda == -1 || potentialValue > sondasAtual.Sondas[melhorSonda].valorAtual + rochas->rochas[j].valorI)) {
                        melhorSonda = k;
                    }
                }

                if (melhorSonda != -1) {
                    sondasAtual.Sondas[melhorSonda].pesoAtual += rochas->rochas[j].pesoI;
                    sondasAtual.Sondas[melhorSonda].valorAtual += rochas->rochas[j].valorI;
                    LInsereRocha(&sondasAtual.Sondas[melhorSonda].CompartimentoR, rochas->rochas[j]);
                    valorTotalAtual += rochas->rochas[j].valorI;
                    rochasUsadas[j] = 1;
                }
            }
        }

        free(rochasUsadas);

        if (valorTotalAtual > melhorValorTotal) {
            melhorValorTotal = valorTotalAtual;

            // Libera a memória da melhor solução anterior (se necessário)
             if (melhorSolucao->Sondas != NULL && melhorSolucao->first != melhorSolucao->last) {
                for (int k = melhorSolucao->first; k < melhorSolucao->last; k++) {
                    FLVaziaRocha(&melhorSolucao->Sondas[k].CompartimentoR); // Libera as rochas
                }
            }


            *melhorSolucao = sondasAtual; // Copia a melhor solução
        } else {
            // Libera a memória de sondasAtual, se não for a melhor
            for (int k = 0; k < numSondas; k++) {
                FLVaziaRocha(&sondasAtual.Sondas[k].CompartimentoR);
            }
        }
    }


    // Impressão da melhor solução APÓS o loop principal
        if(melhorSolucao->first != melhorSolucao->last){ // Verifica se alguma solução foi encontrada

        printf("SOLUCAO\n");
        printf("-------------------------------------\n");
        for (int k = melhorSolucao->first; k < melhorSolucao->last; k++) {
            printf("Sonda %d: Peso: %.0f, Valor: %d, Rochas: [ ",
                   melhorSolucao->Sondas[k].idSonda, melhorSolucao->Sondas[k].pesoAtual, melhorSolucao->Sondas[k].valorAtual);

            for (int r = melhorSolucao->Sondas[k].CompartimentoR.firstR; r < melhorSolucao->Sondas[k].CompartimentoR.lastR; r++) {
                printf("%d ", melhorSolucao->Sondas[k].CompartimentoR.rochas[r].idRocha);
            }
            printf("]\n");
        }
        printf("-------------------------------------\n");
    }

}

void LImprimeSolucao(LSonda* sLista) {
    int i, cont = 1;

    printf("SOLUCAO\n_____________________________\n");
    for (i = sLista->first; i < sLista->last; i++) {
        printf("Sonda %d: ", sLista->Sondas[i].idSonda);
        printf("Peso: %d, Valor: %d, Solucao [", sLista->Sondas[i].pesoAtual, sLista->Sondas[i].valorAtual);
        for (int j = sLista->Sondas[i].CompartimentoR.firstR; j < sLista->Sondas[i].CompartimentoR.lastR; j++) {
            printf("%d ", sLista->Sondas[i].CompartimentoR.rochas[j].idRocha);
        }
        printf(" ]\n");
    }
}