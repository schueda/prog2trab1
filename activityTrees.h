#ifndef __ACTIVITY_TREES__
#define __ACTIVITY_TREES__

typedef struct activityNode activityNodeT;

struct activityNode {
    char *date;
    float distance;
    float avgSpeed;
    float maxSpeed;
    float avgHr;
    float maxHr;
    float avgCadence;
    float elevGain;

    activityNodeT *dateRight;
    activityNodeT *dateLeft;

    activityNodeT *distRight;
    activityNodeT *distLeft;

    activityNodeT *elevGainRight;
    activityNodeT *elevGainLeft;
};

// Cria o nodo de atividade
activityNodeT *createActivityNode();

activityNodeT *insertActivityNodeDate(activityNodeT *root, activityNodeT *node); // Insere o nodo de atividade na árvore que ordena por data.
activityNodeT *insertActivityNodeDist(activityNodeT *root, activityNodeT *node); // Insere o nodo de atividade na árvore que ordena por distância.
activityNodeT *insertActivityNodeElevGain(activityNodeT *root, activityNodeT *node); // Insere o nodo de atividade na árvore que ordena por ganho de elevação.

void printActivityTreeDate(activityNodeT *node); // Exibe a árvore de atividades, ordenada por data.
void printActivityTreeDist(activityNodeT *root); // Exibe a árvore de atividades, ordenada por distância.
void printActivityTreeElevGain(activityNodeT *root); // Exibe a árvore de atividades, ordenada por ganho de elevação.

void countActivities(activityNodeT *root, int *count); // Conta as atividades de uma árvore.
float getMinDistance(activityNodeT *root); // Retorna a atividade de menor distância de uma árvore.
float getMaxDistance(activityNodeT *root); // Retorna a atividade de maior distância de uma árvore.
void getTotalDistance(activityNodeT *root, float *totalDistance); // Calcula a distância total percorrida em uma árvore de atividades.


void destroyActivityTree(activityNodeT *root); // Percorre a árvore em pós-ordem, liberando as alocações de memória.

#endif