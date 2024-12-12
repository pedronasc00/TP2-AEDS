#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
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

        for (int k = 0; k < (1 << N); k++)
        {
            int pesoTotalCombinacao = 0;
            int valorTotalCombinacao = 0;
            bool combinacaoValida = true;

            for (int j = 0; j < N; j++)
            {
                if ((k >> j) & 1)
                {
                    if (rochas->rochas[j].usada)
                    {
                        combinacaoValida = false;
                        break;
                    }
                    pesoTotalCombinacao += rochas->rochas[j].pesoI;
                    valorTotalCombinacao += rochas->rochas[j].valorI;
                }
            }
            if (combinacaoValida && pesoTotalCombinacao <= capacidade && valorTotalCombinacao > melhorValorSonda)
            {
                melhorValorSonda = valorTotalCombinacao;
                FLVaziaRocha(&melhorCombinacaoSonda);

                for (int j = 0; j < N; j++)
                {
                    if ((k >> j) & 1)
                    {
                        LInsereRocha(&melhorCombinacaoSonda, rochas->rochas[j]);
                        rochas->rochas[j].usada = 1;
                    }
                }
            }
        }
        if (melhorValorSonda > melhorSolucao->Sondas[i].valorAtual)
        {
            melhorSolucao->Sondas[i].valorAtual = melhorValorSonda;
             FLVaziaRocha(&(melhorSolucao->Sondas[i].CompartimentoR));

            for (int j = 0; j < N; j++)
            {
                if (rochas->rochas[j].usada == 1)
                {
                    LInsereRocha(&(melhorSolucao->Sondas[i].CompartimentoR), rochas->rochas[j]);
                     
                }
            }
        }
        FLVaziaRocha(&melhorCombinacaoSonda);
        
    }
}

void LImprimeSonda(LSonda *sLista) { 
    printf("SOLUCAO\n");
    printf("-------------------------------------\n");
    for (int k = sLista->first; k < sLista->last; k++) {
         int pesoTotalSonda = 0;
         for (int r = sLista->Sondas[k].CompartimentoR.firstR; r < sLista->Sondas[k].CompartimentoR.lastR; r++) {
             pesoTotalSonda += sLista->Sondas[k].CompartimentoR.rochas[r].pesoI;
         }

        printf("Sonda %d: Peso: %d, Valor: %d, Rochas: [ ",
               sLista->Sondas[k].idSonda, pesoTotalSonda, sLista->Sondas[k].valorAtual); // Adicionado pesoTotalSonda

        for (int r = sLista->Sondas[k].CompartimentoR.firstR; r < sLista->Sondas[k].CompartimentoR.lastR; r++) {
            printf("%d ", sLista->Sondas[k].CompartimentoR.rochas[r].idRocha);
        }
        printf("]\n");
    }
    printf("-------------------------------------\n");
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