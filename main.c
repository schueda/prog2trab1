#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "histogram.h"
#include "directoryParse.h"

int main(int argc, char *argv[]){
    bikeNodeT *bikeRoot;

    int opt;
    while((opt = getopt(argc, argv, "d:")) != -1) {
        switch (opt) {
        case 'd':
            bikeRoot = parseDirectory(optarg);

            if (bikeRoot != NULL) {
                printBikeTree(bikeRoot);
                printActivityTreeDate(bikeRoot->activityByDateRoot);
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

