#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "activityTrees.h"
#include "bikeTree.h"

bikeNodeT *createBikeNode(char key[]) {
    bikeNodeT *node = malloc(sizeof(bikeNodeT));

    char *nodeKey = malloc(sizeof(char)*strlen(key));
    strcpy(nodeKey, key);
    node->gear = nodeKey;

    node->activityByDateRoot = NULL;
    node->activityByDistRoot = NULL;
    node->activityByElevGainRoot = NULL;

    node->left = NULL;
    node->right = NULL;

    return node;
}

bikeNodeT *insertBikeNode(bikeNodeT *root, char key[]) {
    if(root == NULL) {
        root = createBikeNode(key);
    }
    int comp = strcmp(root->gear, key);
    if(comp > 0) {
        root->left = insertBikeNode(root->left, key);
    } else if(comp < 0) {
        root->right = insertBikeNode(root->right, key);
    }
    return root;
}

bikeNodeT *findBikeNode(bikeNodeT *root, char key[]) {
    if(root == NULL) {
        return NULL;
    }
    int comp = strcmp(root->gear, key);
    if(comp > 0) {
        return findBikeNode(root->left, key);
    } else if(comp < 0) {
        return findBikeNode(root->right, key);
    }
    return root;
}

void printBikeTree(bikeNodeT *root, int *count) {
    if (root == NULL) {
        return;
    }
    printBikeTree(root->left, count);
    printf("%d-%s\n", *count, root->gear);
    *count += 1;
    printBikeTree(root->right, count);
}

void printBikesActivitiesDate(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printBikesActivitiesDate(root->left);
    printf("%s\n", root->gear);
    printActivityTreeDate(root->activityByDateRoot);
    printf("\n\n");
    printBikesActivitiesDate(root->right);
}

void printBikesActivitiesDist(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printBikesActivitiesDist(root->left);
    printf("%s\n", root->gear);
    printActivityTreeDist(root->activityByDistRoot);
    printf("\n\n");
    printBikesActivitiesDist(root->right);
}

void printBikesActivitiesElevGain(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printBikesActivitiesElevGain(root->left);
    printf("%s\n", root->gear);
    printActivityTreeElevGain(root->activityByElevGainRoot);
    printf("\n\n");
    printBikesActivitiesElevGain(root->right);
}