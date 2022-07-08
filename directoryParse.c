#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "directoryParse.h"
#include "stringUtils.h"
#include "tree.h"
#define LINE_SIZE 128

bikeNodeT *parseFile(char *filePath, bikeNodeT *raiz);
char *getDate(char *line);
float getDistance(char *line);
float getSpeed(char *line);
int getHr(char *line);
int getCadence(char *line);
float getAltitude(char *line);

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

bikeNodeT *parseFile(char *filePath, bikeNodeT *bikeRoot) {
    FILE *file;
    char line[LINE_SIZE+1];
    char gear[LINE_SIZE];
    bikeNodeT *bike = NULL;
    activityNodeT *activity = NULL;
    
    int separator;
    
    float previousSpeed;
    float currentSpeed;
    float maxSpeed;
    float avgSpeed;
    float totalDiv;

    int previousHr;
    int currentHr;
    float maxHr;

    float previousAltitude;
    float currentAltitude;
    float altitudeDiff;

    int previousCad;
    int currentCad;

    float previousTime;
    float currentTime;
    float timeDiff;


    file = fopen(filePath, "r");

    if(checkLineStart(fgets(line, LINE_SIZE, file), "Gear:")) {
        line[strlen(line) - 1] = '\0';
        strcpy(gear, &line[6]);

        bikeRoot = insertBikeNode(bikeRoot, gear);
        bike = findBikeNode(bikeRoot, gear);
        activity = createActivityNode();

        
        fgets(line, LINE_SIZE, file);
        while (!checkLineStart(line, "timestamp")){
            if (checkLineStart(line, "\n")) {
                separator = ftell(file);
            }

            fgets(line, LINE_SIZE, file);
        }
        activity->date = getDate(line);

        fseek(file, separator, SEEK_SET);

        while(fgets(line, LINE_SIZE, file) != NULL) {
            if(checkLineStart(line, "speed")) {
                previousSpeed = currentSpeed;
                currentSpeed = getSpeed(line);
            }
            else if(checkLineStart(line, "heart_rate")) {
                previousHr = currentHr;
                currentHr = getHr(line);
            }
            else if(checkLineStart(line, "cadence")) {
                previousCad = currentCad;
                currentCad = getCadence(line);
            }
            else if(checkLineStart(line, "altitude")) {
                previousAltitude = currentAltitude;
                currentAltitude = getAltitude(line);
                altitudeDiff = currentAltitude - previousAltitude;

                if (altitudeDiff > 0) {
                    activity->elevGain += altitudeDiff;
                }
            }
            else if(checkLineStart(line, "timestamp")) {
                //isso aqui vai ser mais treta, vou deixar pra depois kk
            }
            else if(checkLineStart(line, "\n")) {
                separator = ftell(file);
            }
        }

        fseek(file, separator, SEEK_SET);

        fgets(line, LINE_SIZE, file);
        while(!checkLineStart(line, "distance")) {
            fgets(line, LINE_SIZE, file);
        }
        activity->distance = getDistance(line);

        bike->activityByDateRoot = insertActivityNodeDate(bike->activityByDateRoot, activity);
        bike->activityByDistRoot = insertActivityNodeDist(bike->activityByDistRoot, activity);
        bike->activityByElevGainRoot = insertActivityNodeSubAcum(bike->activityByElevGainRoot, activity);
    }

    fclose(file);
    return bikeRoot;
}

char *getDate(char *line) {
    char *date = malloc(sizeof(char)*10);
    line[21] = '\0';
    strcpy(date, &line[11]);
    return date;
}

float getDistance(char *line) {
    line[strlen(line)- 2] = '\0';
    return atof(&line[10]);
}

float getSpeed(char *line) {
    line[strlen(line)- 4] = '\0';
    return atof(&line[7]);
}

int getHr(char *line) {
    line[strlen(line)- 4] = '\0';
    return atoi(&line[12]);
}

int getCadence(char *line) {
    line[strlen(line)- 4] = '\0';
    return atoi(&line[9]);
}

float getAltitude(char *line) {
    line[strlen(line)- 2] = '\0';
    return atof(&line[10]);
}