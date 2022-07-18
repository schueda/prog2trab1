#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stringUtils.h"
#include "activityTrees.h"

void printActivity(activityNodeT *node);

// Cria o nodo de atividade
activityNodeT *createActivityNode() {
    activityNodeT *node = malloc(sizeof(activityNodeT)); //Aloca memória dinamicamente para o nodo.

    node->date = NULL;

    node->dateLeft = NULL;
    node->dateRight = NULL;

    node->distLeft = NULL;
    node->distRight = NULL;

    node->elevGainLeft = NULL;
    node->elevGainRight = NULL;

    return node;
}

// Insere o nodo de atividade na árvore que ordena por data.
activityNodeT *insertActivityNodeDate(activityNodeT *root, activityNodeT *node) {
    if(root == NULL) {
        root = node;
    }
    int comp = strcmp(root->date, node->date); // Compara duas strings.
    if(comp > 0) { // Usa o resultado da comparação das strings para determinar a ordem.
        root->dateLeft = insertActivityNodeDate(root->dateLeft, node);
    } else if(comp < 0) {
        root->dateRight = insertActivityNodeDate(root->dateRight, node);
    }
    return root;
}

// Insere o nodo de atividade na árvore que ordena por distância.
activityNodeT *insertActivityNodeDist(activityNodeT *root, activityNodeT *node) {
    if(root == NULL) {
        root = node;
    }
    if(root->distance > node->distance) { // Compara as distâncias para determinar a ordem.
        root->distLeft = insertActivityNodeDist(root->distLeft, node);
    } else if(root->distance < node->distance) {
        root->distRight = insertActivityNodeDist(root->distRight, node);
    }
    return root;
}

// Insere o nodo de atividade na árvore que ordena por ganho de elevação.
activityNodeT *insertActivityNodeElevGain(activityNodeT *root, activityNodeT *node) {
    if(root == NULL) {
        root = node;
    }
    if(root->elevGain > node->elevGain) { // Compara os ganhos de elevação para determinar a ordem.
        root->elevGainLeft = insertActivityNodeElevGain(root->elevGainLeft, node);
    } else if(root->elevGain < node->elevGain) {
        root->elevGainRight = insertActivityNodeElevGain(root->elevGainRight, node);
    }
    return root;
}

// Exibe a árvore de atividades, ordenada por data.
void printActivityTreeDate(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    printActivityTreeDate(root->dateLeft);
    printActivity(root);
    printActivityTreeDate(root->dateRight);
}

// Exibe a árvore de atividades, ordenada por distância.
void printActivityTreeDist(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    printActivityTreeDist(root->distLeft);
    printActivity(root);
    printActivityTreeDist(root->distRight);
}

// Exibe a árvore de atividades, ordenada por ganho de elevação.
void printActivityTreeElevGain(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    printActivityTreeElevGain(root->elevGainLeft);
    printActivity(root);
    printActivityTreeElevGain(root->elevGainRight);
}

// Exibe a atividade individualmente, formatando os dados.
void printActivity(activityNodeT *node) {
    char *formattedDate = formatDate(node->date);
    printf("%s | ", formattedDate);
    free(formattedDate);

    printf("%.2f km | ", node->distance);
    printf("%.2f km/h | ", node->avgSpeed);
    printf("%.2f km/h | ", node->maxSpeed);
    printf("%.0f bpm | ", node->avgHr);
    printf("%.0f bpm | ", node->maxHr);
    printf("%.0f rpm | ", node->avgCadence);
    printf("%.2f m\n", node->elevGain);
}

// Conta as atividades de uma árvore.
void countActivities(activityNodeT *root, int *count) {
    if (root == NULL) {
        return;
    }
    countActivities(root->distLeft, count);
    *count += 1;
    countActivities(root->distRight, count);
}


// Retorna a atividade de menor distância de uma árvore.
float getMinDistance(activityNodeT *root) {
    if (root->distLeft != NULL) {
        return getMinDistance(root->distLeft);
    }
    return root->distance;
}

// Retorna a atividade de maior distância de uma árvore.
float getMaxDistance(activityNodeT *root) {
    if (root->distRight != NULL) {
        return getMaxDistance(root->distRight);
    }
    return root->distance;
}

// Calcula a distância total percorrida em uma árvore de atividades.
void getTotalDistance(activityNodeT *root, float *totalDistance) {
     if (root == NULL) {
        return;
    }
    getTotalDistance(root->distLeft, totalDistance);
    *totalDistance += root->distance;
    getTotalDistance(root->distRight, totalDistance);
}

// Percorre a árvore em pós-ordem, liberando as alocações de memória.
void destroyActivityTree(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    destroyActivityTree(root->dateLeft);
    destroyActivityTree(root->dateRight);
    free(root->date);
    free(root);
}