#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
    printf("%s | ", node->date);
    printf("%.2f km | ", node->distance);
    printf("%.2f km/h | ", node->avgSpeed);
    printf("%.2f km/h | ", node->maxSpeed);
    printf("%.2f bpm | ", node->avgHr);
    printf("%.2f bpm | ", node->maxHr);
    printf("%.2f rpm | ", node->avgCadence);
    printf("%.2f m\n", node->elevGain);
}