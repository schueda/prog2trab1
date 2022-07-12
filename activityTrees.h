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

activityNodeT *createActivityNode();

activityNodeT *insertActivityNodeDate(activityNodeT *raiz, activityNodeT *node);
activityNodeT *insertActivityNodeDist(activityNodeT *raiz, activityNodeT *node);
activityNodeT *insertActivityNodeElevGain(activityNodeT *raiz, activityNodeT *node);

void printActivityTreeDate(activityNodeT *node);
void printActivityTreeDist(activityNodeT *root);
void printActivityTreeElevGain(activityNodeT *root);

float getMinDistance(activityNodeT *root);
float getMaxDistance(activityNodeT *root);

void destroyActivityTree(activityNodeT *root);

#endif