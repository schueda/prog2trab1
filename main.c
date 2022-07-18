#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "histogram.h"
#include "directoryParse.h"

#define SIZE 128

int main(int argc, char *argv[]){
    bikeNodeT *bikeRoot;
    bikeNodeT *selectedBike;

    char directoryPath[SIZE+1] = "";

    char menuOption[SIZE+1];
    int menuNumber = 1;

    int count = 1;

    char bikeName[SIZE+1];

    int opt;
    while((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
        case 'd':
            strcpy(directoryPath, optarg); // Salva o path inserido.
            break;
        default:
            printf("Usage: [-d] [Directory...]\n"); // Mensagem de erro caso as flags estejam erradas.
            return 1;
        }
    }

    if(strlen(directoryPath) > 0) { // Verifica se realmente foi inserido um path.
        bikeRoot = parseDirectory(directoryPath); // Analisa o diretório do path inserido.

        if(bikeRoot != NULL) {
            while(menuNumber != 0) {
                printf("\n\nInsira a opção desejada\n");
                printf("1. Lista todas as bicicletas encontradas.\n");
                printf("2. Lista as atividades da bicicleta informada.\n");
                printf("3. Lista todas as atividades, agrupadas por bicicleta, ordenadas por data.\n");
                printf("4. Lista todas as atividades, agrupadas por bicicleta, ordenadas por distância.\n");
                printf("5. Lista todas as atividades, ordenadas por subida acumulada.\n");
                printf("6. Gera o histograma da bicicleta informada.\n");
                printf("0. Termina o programa.\n");

                fgets(menuOption, SIZE, stdin); // Recebe a linha inserida pelo usuário.
                menuNumber = atoi(menuOption); // Extrai o inteiro da linha.
                printf("\n");

                switch (menuNumber) {
                case 1:
                    printBikeTree(bikeRoot, &count); // Imprime uma lista com o nome de todas as bikes.
                    break;
                case 2:
                    printf("Informe a bicicleta: ");
                    fgets(bikeName, SIZE, stdin); // Recebe o nome da bicicleta
                    bikeName[strlen(bikeName)-1] = '\0';
                    selectedBike = findBikeNode(bikeRoot, bikeName); // Procura o nome inserido na estrutura de dados.
                    if (selectedBike != NULL) {
                        printBikeActivities(selectedBike); //Imprime as atividades da bicicleta inserida, se foi encontrada.
                    } else {
                        printf("Bicicleta não encontrada!");
                    }
                    break;
                case 3:
                    printBikesActivitiesDate(bikeRoot); // Imprime todas as atividades, ordenadas por data e agrupadas por bicicleta.
                    break;
                case 4:
                    printBikesActivitiesDist(bikeRoot); // Imprime todas as atividades, ordenadas por distância e agrupadas por bicicleta.
                    break;
                case 5:
                    printBikesActivitiesElevGain(bikeRoot); // Imprime todas as atividades, ordenadas por ganho de elevação.
                    break;
                case 6:
                    printf("Informe a bicicleta: ");
                    fgets(bikeName, SIZE, stdin); // Recebe o nome da bicicleta.
                    bikeName[strlen(bikeName)-1] = '\0';
                    selectedBike = findBikeNode(bikeRoot, bikeName); 
                    if (selectedBike != NULL) {
                        printAsciiHistogram(selectedBike->activityByDistRoot); // Printa o histograma da bicicleta, se foi encontrada.
                    } else {
                        printf("Bicicleta não encontrada!");
                    }
                    break;
                case 0:
                    printf("Liberando memória...\n");
                destroyBikeTree(bikeRoot); // Libera todos os nodos alocados dinamicamente.
                    break;
                default:
                    printf("comando inválido\n");
                    break;
                }
            }
        } else {
            printf("Nenhum arquivo de log válido foi encontrado nesse diretório.\n");
        }
    }

    return 0;
}

