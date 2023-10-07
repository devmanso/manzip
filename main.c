#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "headers/manzip.h"

int main(int argc, char *argv[]) {

    if(argc != 4) {
        perror("Incorrect number of arguments! There should be 3 arguments: \n");
        perror("input_file.ext output_file.ext mode \n");
        perror("where mode can either be E for encoding, or D for decoding");
        return EXIT_FAILURE;
    }

    // inputs
    const char* inputFilepath = argv[1];
    const char* outputFilepath = argv[2];
    const char* mode = argv[3];

    if (access(inputFilepath, F_OK) == -1) {
        fprintf(stderr, "Error: File '%s' does not exist.\n", inputFilepath);
        return EXIT_FAILURE;
    }

    FILE* inputFile = fopen(inputFilepath, "r");
    if(inputFile == NULL) {
        perror("Could not open input file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    FILE* outputFile = fopen(outputFilepath, "w");
    if(outputFile == NULL) {
        perror("Could not open output file");
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    if(strcmp(mode, "E") != 0 && strcmp(mode, "D") != 0) {
        perror("incorrect mode: mode must be E or D");
        return EXIT_FAILURE;
    }

    if(strcmp(mode, "E") == 0) {
        encodeFile(inputFile, outputFile, 9);
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_SUCCESS;
    } else if(strcmp(mode, "D") == 0) {
        decodeFile(inputFile, outputFile);
        fclose(inputFile);
        fclose(outputFile);
        return EXIT_SUCCESS;
    }
    
    printf("\n Operation done, press any key to exit");
    
    getchar();
    return EXIT_SUCCESS;
}