#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "histogram.h"
#include "directoryParse.h"

#define SIZE 80

int main(int argc, char *argv[]){
    bikeNodeT *bikeRoot;
    bikeNodeT *selectedBike;
    char menuOption[SIZE+1];
    int menuNumber = 1;
    int count = 1;
    char bikeName[SIZE+1];

    int opt;
    while((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
        case 'd':
            bikeRoot = parseDirectory(optarg);

            if (bikeRoot != NULL) {
                while(menuNumber != 0) {
                    printf("\n\nInsira a opção desejada\n");
                    printf("1. Lista todas as bicicletas encontradas.\n");
                    printf("2. Lista as atividades da bicicleta informada.\n");
                    printf("3. Lista todas as atividades, agrupadas por bicicleta, ordenadas por data.\n");
                    printf("4. Lista todas as atividades, agrupadas por bicicleta, ordenadas por distância.\n");
                    printf("5. Lista todas as atividades, agrupadas por bicicleta, ordenadas por subida acumulada.\n");
                    printf("6. Gera o histograma da bicicleta informada.\n");
                    printf("0. Termina o programa.\n");

                    fgets(menuOption, SIZE, stdin);
                    menuNumber = atoi(menuOption);
                    printf("\n");

                    switch (menuNumber) {
                    case 1:
                        printBikeTree(bikeRoot, &count);
                        break;
                    case 2:
                        printf("Informe a bicicleta: ");
                        fgets(bikeName, SIZE, stdin);
                        bikeName[strlen(bikeName)-1] = '\0';
                        selectedBike = findBikeNode(bikeRoot, bikeName);
                        if (selectedBike != NULL) {
                            printActivityTreeDate(selectedBike->activityByDateRoot);
                            printf("Quantidade: %d\n", selectedBike->activityCount);
                            printf("Distância total: %.2f km\n", selectedBike->totalDistance);
                            printf("Menor distância: %.2f km\n", selectedBike->minDistance);
                            printf("Maior distância: %.2f km\n", selectedBike->maxDistance);
                            printf("Distância média: %.2f km\n", selectedBike->avgDistance);
                        } else {
                            printf("Bicicleta não encontrada!");
                        }
                        break;
                    case 3:
                        printBikesActivitiesDate(bikeRoot);
                        break;
                    case 4:
                        printBikesActivitiesDist(bikeRoot);
                        break;
                    case 5:
                        printBikesActivitiesElevGain(bikeRoot);
                        break;
                    case 6:
                        printf("Informe a bicicleta: ");
                        fgets(bikeName, SIZE, stdin);
                        bikeName[strlen(bikeName)-1] = '\0';
                        selectedBike = findBikeNode(bikeRoot, bikeName);
                        if (selectedBike != NULL) {
                            printAsciiHistogram(selectedBike->activityByDistRoot);
                        } else {
                            printf("Bicicleta não encontrada!");
                        }
                        break;
                    case 0:
                        printf("Liberando memória...\n");
                        destroyBikeTree(bikeRoot);
                        break;
                    default:
                        printf("comando inválido\n");
                        break;
                    }
                }
            } else {
                printf("Nenhum arquivo de log válido foi encontrado nesse diretório.\n");
            }
            break;
        default:
            perror("Usage: [-d] [Directory...]\n");
            return 1;
        }
    }


    return 0;
}

