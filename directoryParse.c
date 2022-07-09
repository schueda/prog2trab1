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
    float maxSpeed;
    float avgSpeed;
    int speedDiv;

    int previousHr;
    int currentHr;
    float maxHr;
    float avgHr;
    int hrDiv;

    float previousAltitude;
    float currentAltitude;

    int previousCadence = 0;
    int currentCadence = 0;
    float avgCadence;
    int cadenceDiv;

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
            }
            else if(checkLineStart(line, "heart_rate")) {
                previousHr = currentHr;
                currentHr = getHr(line);
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

                previousTime = currentTime;
                currentTime = getTime(line);
            }
            else if(checkLineStart(line, "distance")) {
                distance = getDistance(line);
            }
        }

        bike->activityByDateRoot = insertActivityNodeDate(bike->activityByDateRoot, activity);
        bike->activityByDistRoot = insertActivityNodeDist(bike->activityByDistRoot, activity);
        bike->activityByElevGainRoot = insertActivityNodeSubAcum(bike->activityByElevGainRoot, activity);
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