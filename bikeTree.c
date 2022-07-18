#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "activityTrees.h"
#include "bikeTree.h"

void printBikeSummary(bikeNodeT *bike); // Exibe o sumário da bicicleta.
void printHeader(); // Exibe o header da tabela de atividades

// Cria o nó de bicicleta.
bikeNodeT *createBikeNode(char key[]) {
    bikeNodeT *node = malloc(sizeof(bikeNodeT)); // Aloca o nodo dinamicamente.

    char *nodeKey = malloc(sizeof(char)*strlen(key));  // Aloca memória para o nome da bicicleta.
    strcpy(nodeKey, key); // Copia o nome passado por parametro para a memória alocada.
    node->gear = nodeKey; // Faz o node apontar para a cópia

    node->activityCount = 0;
    node->totalDistance = 0;

    node->activityByDateRoot = NULL;
    node->activityByDistRoot = NULL;
    node->activityByElevGainRoot = NULL;

    node->left = NULL;
    node->right = NULL;

    return node;
}

// Insere o nó da bicicleta na árvore.
bikeNodeT *insertBikeNode(bikeNodeT *root, char key[]) {
    if(root == NULL) {
        root = createBikeNode(key);
    }
    int comp = strcmp(root->gear, key); // Compara as strings.
    if(comp > 0) { // Utiliza o resultado da comparação para definir a ordem.
        root->left = insertBikeNode(root->left, key);
    } else if(comp < 0) {
        root->right = insertBikeNode(root->right, key);
    }
    return root;
}

// Encontra o nodo de bicicleta na árvore.
bikeNodeT *findBikeNode(bikeNodeT *root, char key[]) {
    if(root == NULL) {
        return NULL;
    }
    int comp = strcmp(root->gear, key); // Compara as strings.
    if(comp > 0) { // Utiliza o resultado da comparação para procurar o nodo.
        return findBikeNode(root->left, key);
    } else if(comp < 0) {
        return findBikeNode(root->right, key);
    }
    return root;
}


// Calcula os sumários das bicicletas.
void summarizeBikes(bikeNodeT *root) {
    if (root == NULL) {
        return;
    }
    summarizeBikes(root->left);
    countActivities(root->activityByDistRoot, &root->activityCount);
    getTotalDistance(root->activityByDistRoot, &root->totalDistance);
    root->minDistance = getMinDistance(root->activityByDistRoot);
    root->maxDistance = getMaxDistance(root->activityByDistRoot);
    root->avgDistance = root->totalDistance / (float) root->activityCount;
    summarizeBikes(root->right);
}

// Exibe a lista de todas bicicletas registradas.
void printBikeTree(bikeNodeT *root, int *count) {
    if (root == NULL) {
        return;
    }
    printBikeTree(root->left, count);
    printf("%d-%s\n", *count, root->gear);
    *count += 1;
    printBikeTree(root->right, count);
}


// Exibe as atividades de uma bicicleta especificada.
void printBikeActivities(bikeNodeT *bike) {
    printActivityTreeDate(bike->activityByDateRoot);
    printBikeSummary(bike);
}

// Exibe a tabela de atividades de uma bicicleta, ordenada por data.
void printBikesActivitiesDate(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printBikesActivitiesDate(root->left);
    printf("%s\n", root->gear);
    printHeader();
    printActivityTreeDate(root->activityByDateRoot);
    printBikeSummary(root);
    printf("\n\n");
    printBikesActivitiesDate(root->right);
}

// Exibe a tabela de atividades de uma bicicleta, ordenada por Distância.
void printBikesActivitiesDist(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printBikesActivitiesDist(root->left);
    printf("%s\n", root->gear);
    printHeader();
    printActivityTreeDist(root->activityByDistRoot);
    printBikeSummary(root);
    printf("\n\n");
    printBikesActivitiesDist(root->right);
}

// Exibe o sumário de uma bicicleta.
void printBikeSummary(bikeNodeT *bike) {
    printf("Quantidade: %d\n", bike->activityCount);
    printf("Distância total: %.2f km\n", bike->totalDistance);
    printf("Menor distância: %.2f km\n", bike->minDistance);
    printf("Maior distância: %.2f km\n", bike->maxDistance);
    printf("Distância média: %.2f km\n", bike->avgDistance);
}

// Exibe o cabeçalho da tabela de atividades.
void printHeader() {
    printf("   data    |distância |  velo med  |  velo max  | hr med  | hr max  |cadencia| ganho de elevação\n");
}

// Exibe todas as atividades, ordenadas por ganho de elevação.
void printBikesActivitiesElevGain(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printHeader();
    printActivityTreeElevGain(root->activityByElevGainRoot);
    printf("\n\n");
}

// Percorre a árvore em pós-ordem, liberando a memória alocada dinamicamente.
void destroyBikeTree(bikeNodeT *root) {
    if (root == NULL) {
        return;
    }
    destroyBikeTree(root->left);
    destroyBikeTree(root->right);
    free(root->gear);
    destroyActivityTree(root->activityByDateRoot);
    free(root);
}