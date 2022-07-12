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

bikeNodeT *createBikeNode(char key[]);
bikeNodeT *insertBikeNode(bikeNodeT *root, char key[]);
bikeNodeT *findBikeNode(bikeNodeT *root, char key[]);

void summarizeBikes(bikeNodeT *root);
void printBikeTree(bikeNodeT *root, int *count);
void printBikesActivitiesDate(bikeNodeT *root);
void printBikesActivitiesDist(bikeNodeT *root);
void printBikesActivitiesElevGain(bikeNodeT *root);


void destroyBikeTree(bikeNodeT *root);

#endif