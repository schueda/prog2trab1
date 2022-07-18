#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "directoryParse.h"
#include "stringUtils.h"
#include "activityTrees.h"
#define LINE_SIZE 128

bikeNodeT *parseFile(char *filePath, bikeNodeT *bikeRoot, activityNodeT *elevGainRoot);

//Função responsável por abrir o diretório e pegar o nome dos arquivos.
bikeNodeT *parseDirectory(char *directoryPath) {
    DIR *dirStream;
    struct dirent *dirEntry;
    
    char filePath[LINE_SIZE+1];

    bikeNodeT *bikesRoot = NULL;
    activityNodeT *elevGainRoot = NULL;

    dirStream = opendir(directoryPath);
    if(!dirStream) {
        return NULL;
    }

    printf("Processando arquivos...\n");
    while((dirEntry = readdir(dirStream)) != NULL) { // Repete enquanto houverem arquivos.
        if(dirEntry->d_type == DT_REG && checkFileExtension(dirEntry->d_name, ".log")) { // Só considera válido files e que terminam com ".log"
            strcpy(filePath, directoryPath);
            strcat(filePath, "/");
            strcat(filePath, dirEntry->d_name); // Junta o nome da file com o path do arquivo para abrí-lo.

            bikesRoot = parseFile(filePath, bikesRoot, elevGainRoot); // Extrai os dados do arquivo.
            elevGainRoot = bikesRoot->activityByElevGainRoot;
        }
    }
    summarizeBikes(bikesRoot); // Calcula o sumário de todas as bicicletas.

    closedir(dirStream); // Fecha a pasta.
    return bikesRoot;
}

bikeNodeT *parseFile(char *filePath, bikeNodeT *bikeRoot, activityNodeT *elevGainRoot) {
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

    if(checkLineStart(fgets(line, LINE_SIZE, file), "Gear:")) { // Desconsidera arquivos que não começam com Gear.
        line[strlen(line) - 1] = '\0';
        strcpy(gear, &line[6]);

        bikeRoot = insertBikeNode(bikeRoot, gear); // Insere a bicicleta na árvore, se já não estiver inserida.
        bike = findBikeNode(bikeRoot, gear); // Acha o nó relacionado a bicicleta dessa atividade.
        activity = createActivityNode(); // Cria um novo nó de atividade

        
        fgets(line, LINE_SIZE, file); // Extrai a linha do arquivo.
        while (!checkLineStart(line, "timestamp")){
            if (checkLineStart(line, "\n")) {
                separator = ftell(file); // Salva a posição do primeiro separador, para retornar depois que a data da atividade foi extraída.
            }

            if(checkLineStart(line, "altitude")) {
                previousAltitude = getAltitude(line);
                currentAltitude = getAltitude(line);
            }

            fgets(line, LINE_SIZE, file);
        }
        activity->date = getDate(line); // Insere a data na atividade.

        previousTime = getTime(line); //Popula os tempos iniciais.
        currentTime = getTime(line); 

        fseek(file, separator, SEEK_SET); // Retorna o cursor para o separador, para de fato começar a análise do arquivo.

        while(fgets(line, LINE_SIZE, file) != NULL) {
            if(checkLineStart(line, "speed")) { // Se a linha começa com speed, atualiza as variaveis de speed.
                previousSpeed = currentSpeed;
                currentSpeed = getSpeed(line);

                if (currentSpeed > maxSpeed) {
                    maxSpeed = currentSpeed; // Atualiza a max speed, a speed atual for maior.
                }
            }
            else if(checkLineStart(line, "heart_rate")) { // Se a linha começa com heart_rate, atualiza as variaveis de hr.
                previousHr = currentHr;
                currentHr = getHr(line);

                if (currentHr > maxHr) {
                    maxHr = currentHr; // Atualiza a maxHr, a Hr atual for maior.
                }
            }
            else if(checkLineStart(line, "cadence")) { // Se a linha começa com cadence, atualiza as variaveis de cadence.
                previousCadence = currentCadence;
                currentCadence = getCadence(line);
            }
            else if(checkLineStart(line, "altitude")) { // Se a linha começa com altitude, atualiza as variaveis de altitude.
                float altitudeDiff;
                previousAltitude = currentAltitude;
                currentAltitude = getAltitude(line);
                altitudeDiff = currentAltitude - previousAltitude;

                if (altitudeDiff > 0) {
                    activity->elevGain += altitudeDiff; // Se houve uma variação positiva de altitude, soma no ganho de elevação
                }
            }
            else if(checkLineStart(line, "timestamp")) { // Se a linha começa com timestamp, atualiza as variaveis de tempo e realiza as somas das médias
                int timeDiff = currentTime - previousTime;

                if(previousCadence > 0) { // Realiza a soma das cadencias para a média, se a cadencia anterior é maior que 0.
                    sumCadence += timeDiff * previousCadence; 
                    divCadence += timeDiff;
                }

                if(previousSpeed > 0) { // Realiza a soma das velocidades para a média, se a velocidade anterior é diferente de 0.
                    sumSpeed += timeDiff * previousSpeed;
                    divSpeed += timeDiff;
                }

                if (previousHr > 0) { // Realiza a soma das velocidades para a média, se a velocidade anterior é diferente de 0.
                    sumHr += timeDiff * previousHr;
                    divHr += timeDiff;
                }

                previousTime = currentTime; // Atualiza as variáveis de tempo.
                currentTime = getTime(line);
            }
            else if(checkLineStart(line, "distance")) { // Se a linha é distância, atualiza a variável de distância.
                distance = getDistance(line);
            }
        }

        activity->distance = distance/1000; // Divide por mil, para mostrar o resultado em km.
        activity->avgSpeed = sumSpeed/divSpeed * 3.6; // Multiplica por 3,6, para mostrar o resultado em km/h.
        activity->maxSpeed = maxSpeed * 3.6; // Multiplica por 3,6, para mostrar o resultado em km/h.
        if (divHr != 0) {
            activity->avgHr = sumHr/divHr; // Calcula a média de Hr, se houve registros.
        } else {
            activity->avgHr = 0;
        }
        activity->maxHr = maxHr;
        if (divCadence != 0) {
            activity->avgCadence = sumCadence/divCadence; // Calcula a média de cadência, se houve registros.
        } else {
            activity->avgCadence = 0;
        }

        bike->activityByDateRoot = insertActivityNodeDate(bike->activityByDateRoot, activity); // Insere a atividade na árvore de data.
        bike->activityByDistRoot = insertActivityNodeDist(bike->activityByDistRoot, activity); // Insere a atividade na árvore de distância.
        elevGainRoot = insertActivityNodeElevGain(elevGainRoot, activity); // Insere a atividade na árvore de ganho de elevação.
        bike->activityByElevGainRoot = elevGainRoot;
    }

    fclose(file); // Fecha o arquivo.
    return bikeRoot;
}