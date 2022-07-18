#ifndef __BIKE_TREE__
#define __BIKE_TREE__

#include "activityTrees.h"

typedef struct bikeNode bikeNodeT;

struct bikeNode {
    char *gear;

    int activityCount;
    float totalDistance;
    float maxDistance;
    float minDistance;
    float avgDistance;

    activityNodeT *activityByDateRoot;
    activityNodeT *activityByDistRoot;
    activityNodeT *activityByElevGainRoot;

    bikeNodeT *left;
    bikeNodeT *right;
};

bikeNodeT *insertBikeNode(bikeNodeT *root, char key[]); // Insere o nó da bicicleta na árvore.
bikeNodeT *findBikeNode(bikeNodeT *root, char key[]); // Encontra o nodo de bicicleta na árvore.

void summarizeBikes(bikeNodeT *root); // Calcula os sumários das bicicletas.
void printBikeTree(bikeNodeT *root, int *count);  // Exibe a lista de todas bicicletas registradas.
void printBikeActivities(bikeNodeT *bike); // Exibe as atividades de uma bicicleta especificada.
void printBikesActivitiesDate(bikeNodeT *root); // Exibe a tabela de atividades de uma bicicleta, ordenada por data.
void printBikesActivitiesDist(bikeNodeT *root); // Exibe a tabela de atividades de uma bicicleta, ordenada por Distância.
void printBikesActivitiesElevGain(bikeNodeT *root); // Exibe todas as atividades, ordenadas por ganho de elevação.


void destroyBikeTree(bikeNodeT *root); // Percorre a árvore em pós-ordem, liberando a memória alocada dinamicamente.

#endif