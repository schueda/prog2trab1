#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "directoryParse.h"
#include "stringUtils.h"
#include "activityTrees.h"
#define LINE_SIZE 128

bikeNodeT *parseFile(char *filePath, bikeNodeT *raiz);

bikeNodeT *parseDirectory(char *directoryPath) {
    DIR *dirStream;
    struct dirent *dirEntry;
    
    char filePath[LINE_SIZE+1];

    bikeNodeT *raizBikes = NULL;

    dirStream = opendir(directoryPath);
    if(!dirStream) {
        return NULL;
    }

    printf("Processando arquivos...\n");
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
    
    float previousSpeed = 0;
    float currentSpeed = 0;
    float maxSpeed = 0;
    float sumSpeed = 0;
    int divSpeed = 0;

    int previousHr = 0;
    int currentHr = 0;
    float maxHr = 0;
    int sumHr = 0;
    int divHr = 0;

    float previousAltitude;
    float currentAltitude;

    int previousCadence = 0;
    int currentCadence = 0;
    int sumCadence = 0;
    int divCadence = 0;

    int previousTime;
    int currentTime;

    float distance;


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

            if(checkLineStart(line, "altitude")) {
                previousAltitude = getAltitude(line);
                currentAltitude = getAltitude(line);
            }

            fgets(line, LINE_SIZE, file);
        }
        activity->date = getDate(line);

        previousTime = getTime(line);
        currentTime = getTime(line);

        fseek(file, separator, SEEK_SET);

        while(fgets(line, LINE_SIZE, file) != NULL) {
            if(checkLineStart(line, "speed")) {
                previousSpeed = currentSpeed;
                currentSpeed = getSpeed(line);

                if (currentSpeed > maxSpeed) {
                    maxSpeed = currentSpeed;
                }
            }
            else if(checkLineStart(line, "heart_rate")) {
                previousHr = currentHr;
                currentHr = getHr(line);

                if (currentHr > maxHr) {
                    maxHr = currentHr;
                }
            }
            else if(checkLineStart(line, "cadence")) {
                previousCadence = currentCadence;
                currentCadence = getCadence(line);
            }
            else if(checkLineStart(line, "altitude")) {
                float altitudeDiff;
                previousAltitude = currentAltitude;
                currentAltitude = getAltitude(line);
                altitudeDiff = currentAltitude - previousAltitude;

                if (altitudeDiff > 0) {
                    activity->elevGain += altitudeDiff;
                }
            }
            else if(checkLineStart(line, "timestamp")) {
                int timeDiff = currentTime - previousTime;

                if(previousCadence > 0) {
                    sumCadence += timeDiff * previousCadence;
                    divCadence += timeDiff;
                }

                if(previousSpeed > 0) {
                    sumSpeed += timeDiff * previousSpeed;
                    divSpeed += timeDiff;
                }

                if (previousHr > 0) {
                    sumHr += timeDiff * previousHr;
                    divHr += timeDiff;
                }

                previousTime = currentTime;
                currentTime = getTime(line);
            }
            else if(checkLineStart(line, "distance")) {
                distance = getDistance(line);
            }
        }

        activity->distance = distance/1000;
        activity->avgSpeed = sumSpeed/divSpeed * 3.6;
        activity->maxSpeed = maxSpeed * 3.6;
        if (divHr != 0) {
            activity->avgHr = sumHr/divHr;
        } else {
            activity->avgHr = 0;
        }
        activity->maxHr = maxHr;
        if (divCadence != 0) {
            activity->avgCadence = sumCadence/divCadence;
        } else {
            activity->avgCadence = 0;
        }

        bike->activityByDateRoot = insertActivityNodeDate(bike->activityByDateRoot, activity);
        bike->activityByDistRoot = insertActivityNodeDist(bike->activityByDistRoot, activity);
        bike->activityByElevGainRoot = insertActivityNodeElevGain(bike->activityByElevGainRoot, activity);
    }

    fclose(file);
    return bikeRoot;
}