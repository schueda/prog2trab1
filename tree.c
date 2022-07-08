#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

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

bikeNodeT *insertBikeNode(bikeNodeT *node, char key[]) {
    if(node == NULL) {
        node = createBikeNode(key);
    }
    int comp = strcmp(node->gear, key);
    if(comp > 0) {
        node->left = insertBikeNode(node->left, key);
    } else if(comp < 0) {
        node->right = insertBikeNode(node->right, key);
    }
    return node;
}

void printBikeTree(bikeNodeT *node) {
    if (node == NULL) {
        return;
    }
    printBikeTree(node->left);
    printf("%s\n", node->gear);
    printBikeTree(node->right);
}

bikeNodeT *findBikeNode(bikeNodeT *node, char key[]) {
    if(node == NULL) {
        return NULL;
    }
    int comp = strcmp(node->gear, key);
    if(comp > 0) {
        return findBikeNode(node->left, key);
    } else if(comp < 0) {
        return findBikeNode(node->right, key);
    }
    return node;
}

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

activityNodeT *insertActivityNodeSubAcum(activityNodeT *root, activityNodeT *node) {
    if(root == NULL) {
        root = node;
    }
    if(root->elevGain > node->elevGain) {
        root->elevGainLeft = insertActivityNodeSubAcum(root->elevGainLeft, node);
    } else if(root->elevGain < node->elevGain) {
        root->elevGainRight = insertActivityNodeSubAcum(root->elevGainRight, node);
    }
    return root;
}

void printActivityTreeDate(activityNodeT *node) {
    if (node == NULL) {
        return;
    }
    printActivityTreeDate(node->dateLeft);
    printf("%s\n", node->date);
    printActivityTreeDate(node->dateRight);
}