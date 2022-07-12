#include <stdlib.h>
#include <stdio.h>

#include "histogram.h"

void countDistancesFromTree(activityNodeT *root, int *levels, int BottomLevel);

void printAsciiHistogram(activityNodeT *root) {
    int i, j;
    int min = (int) getMinDistance(root);
    int max = (int) getMaxDistance(root);

    int bottomLevel = min - min%10;
    int topLevel = max - max%10;
    int levelsCount = topLevel/10 - bottomLevel/10 + 1;

    int *levels = malloc(sizeof(int) * levelsCount);
    countDistancesFromTree(root, levels, bottomLevel);
    
    for (i=0; i<levelsCount; i++) {
        int levelBottom = bottomLevel + i * 10;
        int levelTop = levelBottom + 9;
        if (levelBottom < 100) {
            printf(" %d - %d", levelBottom, levelTop);
        } else {
            printf("%d -%d", levelBottom, levelTop);
        }
        printf(" |");
        for(j=0; j<levels[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("         0123456789#123456789#123456789#\n");
    printf("Distância|          Quantidade\n");

    free(levels);
}

void countDistancesFromTree(activityNodeT *root, int *levels, int bottomLevel) {
    if (root == NULL) {
        return;
    }
    countDistancesFromTree(root->distLeft, levels, bottomLevel);
    levels[(int) root->distance / 10 - (bottomLevel/10)] += 1;
    countDistancesFromTree(root->distRight, levels, bottomLevel);
}