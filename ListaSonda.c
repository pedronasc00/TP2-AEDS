#include <stdio.h>
#include <stdlib.h>
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

void bruteforce(LCompartimento *rochas, int capacidade, int numSondas, int N, LSonda *melhorSolucao) {
    for (int i = 0; i < numSondas; i++) {
        int melhorValorSonda = -1;
        int melhorNumItensSonda = -1; // Para desempate
        LCompartimento melhorCombinacaoSonda;
        FLVaziaRocha(&melhorCombinacaoSonda);

        for (int k = 0; k < (1 << N); k++) { // Iterar por todas as combinações
            int pesoTotalCombinacao = 0;
            int valorTotalCombinacao = 0;
            int numItensCombinacao = 0; // Contar itens na combinação
            bool combinacaoValida = true;

            // Verificar a validade da combinação ANTES de calcular peso e valor
            for (int j = 0; j < N; j++) {
                if ((k >> j) & 1 && rochas->rochas[j].usada) {
                    combinacaoValida = false;
                    break; // Se uma rocha já foi usada, a combinação é inválida
                }
            }

            // Calcular peso e valor apenas para combinações válidas
            if (combinacaoValida) {
                for (int j = 0; j < N; j++) {
                    if ((k >> j) & 1) {
                        pesoTotalCombinacao += rochas->rochas[j].pesoI;
                        valorTotalCombinacao += rochas->rochas[j].valorI;
                        numItensCombinacao++;
                    }
                }

                // Verificar se a combinação é melhor que a atual
                if (pesoTotalCombinacao <= capacidade && 
                    (valorTotalCombinacao > melhorValorSonda ||
                     (valorTotalCombinacao == melhorValorSonda && numItensCombinacao > melhorNumItensSonda))) {
                    melhorValorSonda = valorTotalCombinacao;
                    melhorNumItensSonda = numItensCombinacao;
                    FLVaziaRocha(&melhorCombinacaoSonda); // Limpar a melhor combinação anterior

                    for (int j = 0; j < N; j++) {
                        if ((k >> j) & 1) {
                            LInsereRocha(&melhorCombinacaoSonda, rochas->rochas[j]);
                        }
                    }
                }
            }
        }

        // Marcar as rochas usadas APÓS encontrar a melhor combinação para a sonda
        for (int j = melhorCombinacaoSonda.firstR; j < melhorCombinacaoSonda.lastR; j++) {
            for (int l = 0; l < N; l++) {  // Encontrar a rocha correspondente na lista original
                if (rochas->rochas[l].idRocha == melhorCombinacaoSonda.rochas[j].idRocha) {
                    rochas->rochas[l].usada = 1;
                    break;
                }
            }
        }

        // Atualizar a melhor solução da sonda
        if (melhorValorSonda > melhorSolucao->Sondas[i].valorAtual) {
            melhorSolucao->Sondas[i].valorAtual = melhorValorSonda;
            FLVaziaRocha(&(melhorSolucao->Sondas[i].CompartimentoR));
            for (int j = melhorCombinacaoSonda.firstR; j < melhorCombinacaoSonda.lastR; j++) {
                LInsereRocha(&(melhorSolucao->Sondas[i].CompartimentoR), melhorCombinacaoSonda.rochas[j]);
            }
        }
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