#ifndef __TREE__
#define __TREE__

typedef struct bikeNode bikeNodeT;
typedef struct activityNode activityNodeT;

struct bikeNode {
    char *gear;
    bikeNodeT *left;
    bikeNodeT *right;

    activityNodeT *activityByDateRoot;
    activityNodeT *activityByDistRoot;
    activityNodeT *activityByElevGainRoot;
};


struct activityNode {
    char *date;
    float distance;
    float veloMed;
    float veloMax;
    float hrMed;
    float hrMax;
    float cadMed;
    float elevGain;

    activityNodeT *dateRight;
    activityNodeT *dateLeft;

    activityNodeT *distRight;
    activityNodeT *distLeft;

    activityNodeT *elevGainRight;
    activityNodeT *elevGainLeft;
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