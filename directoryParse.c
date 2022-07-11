#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "directoryParse.h"
#include "stringUtils.h"
#include "activityTrees.h"
#define LINE_SIZE 128

bikeNodeT *parseFile(char *filePath, bikeNodeT *raiz);
char *getDate(char *line);
float getDistance(char *line);
float getSpeed(char *line);
int getHr(char *line);
int getCadence(char *line);
float getAltitude(char *line);
int getTime(char *line);

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
        // printf("%s | ", activity->date);
        // printf("%.2f km | ", activity->distance);
        // printf("%.2f km/h | ", activity->avgSpeed);
        // printf("%.2f km/h | ", activity->maxSpeed);
        // printf("%.0f bpm | ", activity->avgHr);
        // printf("%.0f bpm | ", activity->maxHr);
        // printf("%.0f rpm | ", activity->avgCadence);
        // printf("%.2f m\n", activity->elevGain);

        bike->activityByDateRoot = insertActivityNodeDate(bike->activityByDateRoot, activity);
        bike->activityByDistRoot = insertActivityNodeDist(bike->activityByDistRoot, activity);
        bike->activityByElevGainRoot = insertActivityNodeElevGain(bike->activityByElevGainRoot, activity);
    }

    fclose(file);
    return bikeRoot;
}

char *getDate(char *line) {
    char lineCopy[strlen(line)];
    strcpy(lineCopy, line);

    char *date = malloc(sizeof(char)*10);
    *(strrchr(lineCopy, ' ')) = '\0';
    strcpy(date, strchr(lineCopy, ' ')+1);
    return date;
}

float getDistance(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atof(strchr(line, ' ')+1);
}

float getSpeed(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atof(strchr(line, ' ')+1);
}

int getHr(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atoi(strchr(line, ' ')+1);
}

int getCadence(char *line) {
    *(strrchr(line, ' ')) = '\0';
    return atoi(strchr(line, ' ')+1);
}

float getAltitude(char *line) {
    char lineCopy[strlen(line)];
    strcpy(lineCopy, line);

    *(strrchr(lineCopy, ' ')) = '\0';
    return atof(strchr(lineCopy, ' ')+1);
}

int getTime(char *line) {
    char lineCopy[strlen(line)];
    strcpy(lineCopy, line);

    lineCopy[strlen(lineCopy)] = '\0';
    char *arg = strrchr(lineCopy, ' ') + 1;
    int hours = atoi(arg);
    int minutes = atoi(strchr(arg, ':')+1);
    int seconds = atoi(strrchr(lineCopy, ':')+1);
    return 3600 * hours + 60 * minutes + seconds;
    return 0;
}