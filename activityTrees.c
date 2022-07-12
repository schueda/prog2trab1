#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stringUtils.h"
#include "activityTrees.h"

void printActivity(activityNodeT *node);

activityNodeT *createActivityNode() {
    activityNodeT *node = malloc(sizeof(activityNodeT));

    node->date = NULL;

    node->dateLeft = NULL;
    node->dateRight = NULL;

    node->distLeft = NULL;
    node->distRight = NULL;

    node->elevGainLeft = NULL;
    node->elevGainRight = NULL;

    return node;
}

activityNodeT *insertActivityNodeDate(activityNodeT *root, activityNodeT *node) {
    if(root == NULL) {
        root = node;
    }
    int comp = strcmp(root->date, node->date);
    if(comp > 0) {
        root->dateLeft = insertActivityNodeDate(root->dateLeft, node);
    } else if(comp < 0) {
        root->dateRight = insertActivityNodeDate(root->dateRight, node);
    }
    return root;
}

activityNodeT *insertActivityNodeDist(activityNodeT *root, activityNodeT *node) {
    if(root == NULL) {
        root = node;
    }
    if(root->distance > node->distance) {
        root->distLeft = insertActivityNodeDist(root->distLeft, node);
    } else if(root->distance < node->distance) {
        root->distRight = insertActivityNodeDist(root->distRight, node);
    }
    return root;
}

activityNodeT *insertActivityNodeElevGain(activityNodeT *root, activityNodeT *node) {
    if(root == NULL) {
        root = node;
    }
    if(root->elevGain > node->elevGain) {
        root->elevGainLeft = insertActivityNodeElevGain(root->elevGainLeft, node);
    } else if(root->elevGain < node->elevGain) {
        root->elevGainRight = insertActivityNodeElevGain(root->elevGainRight, node);
    }
    return root;
}

void printActivityTreeDate(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    printActivityTreeDate(root->dateLeft);
    printActivity(root);
    printActivityTreeDate(root->dateRight);
}

void printActivityTreeDist(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    printActivityTreeDist(root->distLeft);
    printActivity(root);
    printActivityTreeDist(root->distRight);
}

void printActivityTreeElevGain(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    printActivityTreeElevGain(root->elevGainLeft);
    printActivity(root);
    printActivityTreeElevGain(root->elevGainRight);
}

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

void countActivities(activityNodeT *root, int *count) {
    if (root == NULL) {
        return;
    }
    countActivities(root->distLeft, count);
    *count += 1;
    countActivities(root->distRight, count);
}

float getMinDistance(activityNodeT *root) {
    if (root->distLeft != NULL) {
        return getMinDistance(root->distLeft);
    }
    return root->distance;
}

float getMaxDistance(activityNodeT *root) {
    if (root->distRight != NULL) {
        return getMaxDistance(root->distRight);
    }
    return root->distance;
}

void getTotalDistance(activityNodeT *root, float *totalDistance) {
     if (root == NULL) {
        return;
    }
    getTotalDistance(root->distLeft, totalDistance);
    *totalDistance += root->distance;
    getTotalDistance(root->distRight, totalDistance);
}

void destroyActivityTree(activityNodeT *root) {
    if (root == NULL) {
        return;
    }
    destroyActivityTree(root->dateLeft);
    destroyActivityTree(root->dateRight);
    free(root->date);
    free(root);
}