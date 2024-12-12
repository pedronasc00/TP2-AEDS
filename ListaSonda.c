#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ListaSonda.h"

void FLVaziaSonda(LSonda *sLista)
{
    sLista->first = 0;
    sLista->last = sLista->first;
}

int LEVaziaSonda(LSonda *sLista)
{
    return (sLista->last == sLista->first);
}

int LInsereSondas(LSonda *sLista, Sonda pSonda)
{
    if (sLista->last == MAXTAMS)
    {
        return 0;
    }
    sLista->Sondas[sLista->last++] = pSonda;
    return 1;
}

LCompartimento *gerar_combinacoes(LCompartimento *ListaRocha, int N)
{
    int numCombinacoes = pow(2, N);

    LCompartimento *combinacoes = (LCompartimento *)malloc(numCombinacoes * sizeof(LCompartimento));

    if (combinacoes == NULL)
    {
        perror("Erro ao alocar memoria");
    }

    for (int i = 0; i < numCombinacoes; i++)
    {
        FLVaziaRocha(&combinacoes[i]);

        for (int j = 0; j < N; j++)
        {
            if ((i >> j) & 1)
            {
                if (!LInsereRocha(&combinacoes[i], ListaRocha->rochas[j]))
                {
                    perror("Erro ao inserir rocha na combinacao;\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    return combinacoes;
}

void bruteforce(LCompartimento *rochas, int capacidade, int numSondas, int N, LSonda *melhorSolucao)
{
    for (int i = 0; i < numSondas; i++)
    {
        int melhorValorSonda = -1;
        LCompartimento melhorCombinacaoSonda;
        FLVaziaRocha(&melhorCombinacaoSonda);
        
        long int numCombinacoes = pow(2, N);
        LCompartimento *combinacoes = gerar_combinacoes(rochas, N);

        for (int k = 0; k < numCombinacoes; k++)
        {
            int pesoTotalCombinacao = 0;
            int valorTotalCombinacao = 0;

            for (int j = combinacoes[k].firstR; j < combinacoes[k].lastR; j++)
            {
                pesoTotalCombinacao += combinacoes[k].rochas[j].pesoI;
                valorTotalCombinacao += combinacoes[k].rochas[j].valorI;
            }
            
            if (pesoTotalCombinacao <= capacidade && valorTotalCombinacao >= melhorValorSonda) {
                melhorValorSonda = valorTotalCombinacao;
            
                FLVaziaRocha(&melhorCombinacaoSonda);

                for (int t = 0; t < combinacoes[k].lastR; t++) {
                    LInsereRocha(&melhorCombinacaoSonda, combinacoes[k].rochas[t]);
                    combinacoes[k].rochas[t].usada = 1;
                }
            }
        }   
        LImprimeRocha(&melhorCombinacaoSonda);
        free(combinacoes);
    }
}

void LImprimeSonda(LSonda *sLista)
{
    int i, cont = 1;

    printf("SONDAS\n_____________________________\n");
    for (i = sLista->first; i < sLista->last; i++)
    {
        printf("Sonda %d: ", sLista->Sondas[i].idSonda);
        printf("Peso: %d, Valor: %d\n\n", sLista->Sondas[i].pesoAtual, sLista->Sondas[i].valorAtual);
    }
}

/*if(melhorSolucao->first != melhorSolucao->last){ // Verifica se alguma solução foi encontrada

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
    }*/