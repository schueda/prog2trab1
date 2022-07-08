#ifndef __TREE__
#define __TREE__

typedef struct bikeNode bikeNodeT;
typedef struct activityNode activityNodeT;

struct bikeNode {
    char *gear;
    bikeNodeT *filhoEsq;
    bikeNodeT *filhoDir;

    activityNodeT *raizDate;
    activityNodeT *raizDist;
    activityNodeT *raizSubAcum;
};


struct activityNode {
    char *date;
    float dist;
    float veloMed;
    float veloMax;
    float hrMed;
    float hrMax;
    float cadMed;
    float subAcum;

    activityNodeT *dateFilhoDir;
    activityNodeT *dateFilhoEsq;

    activityNodeT *distFilhoDir;
    activityNodeT *distFilhoEsq;

    activityNodeT *subAcumFilhoDir;
    activityNodeT *subAcumFilhoEsq;
};

bikeNodeT *createBikeNode(char key[]);
bikeNodeT *insertBikeNode(bikeNodeT *node, char key[]);
bikeNodeT *findBikeNode(bikeNodeT *node, char key[]);
void printBikeTree(bikeNodeT *node);

activityNodeT *createActivityNode();
activityNodeT *insertActivityNodeDate(activityNodeT *raiz, activityNodeT *node);
activityNodeT *insertActivityNodeDist(activityNodeT *raiz, activityNodeT *node);
activityNodeT *insertActivityNodeSubAcum(activityNodeT *raiz, activityNodeT *node);
void printActivityTreeDate(activityNodeT *node);
#endif