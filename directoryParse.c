#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "directoryParse.h"
#include "stringUtils.h"
#include "tree.h"
#define LINE_SIZE 256

bikeNodeT *parseFile(char *filePath, bikeNodeT *raiz);
void setActivityDate(activityNodeT *node, char *date);
void setActivityDist(activityNodeT *node, char *line);

bikeNodeT *parseDirectory(char *directoryPath) {
    DIR *dirStream;
    struct dirent *dirEntry;
    
    char filePath[LINE_SIZE+1];

    bikeNodeT *raizBikes = NULL;

    dirStream = opendir(directoryPath);
    if(!dirStream) {
        return NULL;
    }

    while((dirEntry = readdir(dirStream)) != NULL) {
        if(dirEntry->d_type == DT_REG && checkFileExtension(dirEntry->d_name, ".log")) {
            strcpy(filePath, directoryPath);
            strcat(filePath, "/");
            strcat(filePath, dirEntry->d_name);

            raizBikes = parseFile(filePath, raizBikes);
        }
    }

    closedir(dirStream);
    return raizBikes;
}

bikeNodeT *parseFile(char *filePath, bikeNodeT *raiz) {
    FILE *file;
    char line[LINE_SIZE+1];
    char gear[128];
    bikeNodeT *currentBike = NULL;
    activityNodeT *currentActivity = NULL;

    file = fopen(filePath, "r");

    if(checkLineStart(fgets(line, LINE_SIZE, file), "Gear:")) {
        line[strlen(line) - 1] = '\0';
        strcpy(gear, &line[6]);

        raiz = insertBikeNode(raiz, gear);
        currentBike = findBikeNode(raiz, gear);

        currentActivity = createActivityNode();

        while(fgets(line, LINE_SIZE, file) != NULL) {
            //todo: fazer ser inicial pra diminuir o numero de ifs
            if(checkLineStart(line, "timestamp")) {
                if(currentActivity->date == NULL) {
                    setActivityDate(currentActivity, line);
                }
            }
            //todo: por no final pra precisar dar valor uma unica vez
            else if(checkLineStart(line, "distance")) {
                setActivityDist(currentActivity, line);
            }
            else if(checkLineStart(line, "")) {
                
            }
            else if(checkLineStart(line, "")) {
                
            }
            else if(checkLineStart(line, "")) {
                
            }
            else if(checkLineStart(line, "")) {
                
            }
            else if(checkLineStart(line, "")) {
                
            }
            else if(checkLineStart(line, "")) {
                
            }
        }

        currentBike->raizDate = insertActivityNodeDate(currentBike->raizDate, currentActivity);
    }

    fclose(file);
    return raiz;
}

void setActivityDate(activityNodeT *node, char *line) {
    char *date = malloc(sizeof(char)*10);
    line[21] = '\0';
    strcpy(date, &line[11]);
    node->date = date;
}

void setActivityDist(activityNodeT *node, char *line) {
    float dist;
    line[strlen(line)- 2] = '\0';
    dist = atof(&line[10]);
    printf("%.2f\n", dist);
}
