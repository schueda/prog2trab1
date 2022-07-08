#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

bikeNodeT *createBikeNode(char key[]) {
    bikeNodeT *node = malloc(sizeof(bikeNodeT));

    char *nodeKey = malloc(sizeof(char)*strlen(key));
    strcpy(nodeKey, key);
    node->gear = nodeKey;

    node->raizDate = NULL;
    node->raizDist = NULL;
    node->raizSubAcum = NULL;

    node->filhoEsq = NULL;
    node->filhoDir = NULL;

    return node;
}

bikeNodeT *insertBikeNode(bikeNodeT *node, char key[]) {
    if(node == NULL) {
        node = createBikeNode(key);
    }
    int comp = strcmp(node->gear, key);
    if(comp > 0) {
        node->filhoEsq = insertBikeNode(node->filhoEsq, key);
    } else if(comp < 0) {
        node->filhoDir = insertBikeNode(node->filhoDir, key);
    }
    return node;
}

void printBikeTree(bikeNodeT *node) {
    if (node == NULL) {
        return;
    }
    printBikeTree(node->filhoEsq);
    printf("%s\n", node->gear);
    printBikeTree(node->filhoDir);
}

bikeNodeT *findBikeNode(bikeNodeT *node, char key[]) {
    if(node == NULL) {
        return NULL;
    }
    int comp = strcmp(node->gear, key);
    if(comp > 0) {
        return findBikeNode(node->filhoEsq, key);
    } else if(comp < 0) {
        return findBikeNode(node->filhoDir, key);
    }
    return node;
}

activityNodeT *createActivityNode() {
    activityNodeT *node = malloc(sizeof(activityNodeT));

    node->date = NULL;

    node->dateFilhoDir = NULL;
    node->dateFilhoEsq = NULL;

    node->distFilhoDir = NULL;
    node->distFilhoEsq = NULL;

    node->subAcumFilhoDir = NULL;
    node->subAcumFilhoEsq = NULL;

    return node;
}

activityNodeT *insertActivityNodeDate(activityNodeT *raiz, activityNodeT *node) {
    if(raiz == NULL) {
        raiz = node;
    }
    int comp = strcmp(raiz->date, node->date);
    if(comp > 0) {
        raiz->dateFilhoEsq = insertActivityNodeDate(raiz->dateFilhoEsq, node);
    } else if(comp < 0) {
        raiz->dateFilhoDir = insertActivityNodeDate(raiz->dateFilhoDir, node);
    }
    return raiz;
}

activityNodeT *insertActivityNodeDist(activityNodeT *raiz, activityNodeT *node) {

}

activityNodeT *insertActivityNodeSubAcum(activityNodeT *raiz, activityNodeT *node) {

}

void printActivityTreeDate(activityNodeT *node) {
    if (node == NULL) {
        return;
    }
    printActivityTreeDate(node->dateFilhoEsq);
    printf("%s\n", node->date);
    printActivityTreeDate(node->dateFilhoDir);
}