#include <stdlib.h>
#include <stdio.h>

#include "histogram.h"

// Conta quantas atividades de cada faixa do histograma estão registradas.
void countDistancesFromTree(activityNodeT *root, int *levels, int BottomLevel);

void printAsciiHistogram(activityNodeT *root) {
    int i, j;
    int min = (int) getMinDistance(root);
    int max = (int) getMaxDistance(root);

    int bottomLevel = min - min%10; // Calcula a menor faixa do histograma.
    int topLevel = max - max%10; // Calcula a maior faixa do histograma.
    int levelsCount = topLevel/10 - bottomLevel/10 + 1; // Calcula a quantidade de faixas do histograma.

    int *levels = malloc(sizeof(int) * levelsCount); // Aloca a contagem das atividades.
    countDistancesFromTree(root, levels, bottomLevel); // Conta as atividades por faixa do histograma.
    
    for (i=0; i<levelsCount; i++) {
        int levelBottom = bottomLevel + i * 10; // Calcula o mínimo da faixa.
        int levelTop = levelBottom + 9; // Calcula o máximo da faixa.
        if (levelBottom < 100) {
            printf(" %d - %d", levelBottom, levelTop); // Configura os espaços dependendo do número de digitos da faixa.
        } else {
            printf("%d -%d", levelBottom, levelTop);
        }
        printf(" |");
        for(j=0; j<levels[i]; j++) {
            printf("*"); // Printa a quantidade de atividades na faixa do histograma
        }
        printf("\n");
    }
    printf("         0123456789#123456789#123456789#\n");
    printf("Distância|          Quantidade\n");

    free(levels); // Libera a memória alocada para a contagem das atividade por faixa
}

// Conta as atividades por faixa, percorrendo a árvore em pós-ordem.
void countDistancesFromTree(activityNodeT *root, int *levels, int bottomLevel) {
    if (root == NULL) {
        return;
    }
    countDistancesFromTree(root->distLeft, levels, bottomLevel);
    levels[(int) (root->distance - bottomLevel)/10] += 1; // Incrementa 1 na faixa da atividade
    countDistancesFromTree(root->distRight, levels, bottomLevel);
}