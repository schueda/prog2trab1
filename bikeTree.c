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

    node->activityCount = 0;
    node->totalDistance = 0;

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

void summarizeBikes(bikeNodeT *root) {
    if (root == NULL) {
        return;
    }
    summarizeBikes(root->left);
    countActivities(root->activityByDistRoot, &root->activityCount);
    getTotalDistance(root->activityByDistRoot, &root->totalDistance);
    root->minDistance = getMinDistance(root->activityByDistRoot);
    root->maxDistance = getMaxDistance(root->activityByDistRoot);
    root->avgDistance = root->totalDistance / (float) root->activityCount;
    summarizeBikes(root->right);
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
    printf("   data    |distância |  velo med  |  velo max  | hr med  | hr max  |cadencia| ganho de elevação\n");
    printActivityTreeDate(root->activityByDateRoot);
    printf("Quantidade: %d\n", root->activityCount);
    printf("Distância total: %.2f km\n", root->totalDistance);
    printf("Menor distância: %.2f km\n", root->minDistance);
    printf("Maior distância: %.2f km\n", root->maxDistance);
    printf("Distância média: %.2f km\n", root->avgDistance);
    printf("\n\n");
    printBikesActivitiesDate(root->right);
}

void printBikesActivitiesDist(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printBikesActivitiesDist(root->left);
    printf("%s\n", root->gear);
    printf("   data    |distância |  velo med  |  velo max  | hr med  | hr max  |cadencia| ganho de elevação\n");
    printActivityTreeDist(root->activityByDistRoot);
    printf("Quantidade: %d\n", root->activityCount);
    printf("Distância total: %.2f km\n", root->totalDistance);
    printf("Menor distância: %.2f km\n", root->minDistance);
    printf("Maior distância: %.2f km\n", root->maxDistance);
    printf("Distância média: %.2f km\n", root->avgDistance);
    printf("\n\n");
    printBikesActivitiesDist(root->right);
}

void printBikesActivitiesElevGain(bikeNodeT *root) {
    if(root == NULL) {
        return;
    }
    printf("   data    |distância |  velo med  |  velo max  | hr med  | hr max  |cadencia| ganho de elevação\n");
    printActivityTreeElevGain(root->activityByElevGainRoot);
    printf("\n\n");
}

void destroyBikeTree(bikeNodeT *root) {
    if (root == NULL) {
        return;
    }
    destroyBikeTree(root->left);
    destroyBikeTree(root->right);
    free(root->gear);
    destroyActivityTree(root->activityByDateRoot);
    free(root);
}