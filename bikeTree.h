#ifndef __BIKE_TREE__
#define __BIKE_TREE__

#include "activityTrees.h"

typedef struct bikeNode bikeNodeT;

struct bikeNode {
    char *gear;
    bikeNodeT *left;
    bikeNodeT *right;

    activityNodeT *activityByDateRoot;
    activityNodeT *activityByDistRoot;
    activityNodeT *activityByElevGainRoot;
};

bikeNodeT *createBikeNode(char key[]);
bikeNodeT *insertBikeNode(bikeNodeT *root, char key[]);
bikeNodeT *findBikeNode(bikeNodeT *root, char key[]);
void printBikeTree(bikeNodeT *root, int *count);
void printBikesActivitiesDate(bikeNodeT *root);
void printBikesActivitiesDist(bikeNodeT *root);
void printBikesActivitiesElevGain(bikeNodeT *root);

#endif