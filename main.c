#include <stdio.h>
#include <stdlib.h>
#include "headers/manzip.h"

int main() {
    FILE* inputFile = fopen("input.wasd", "r");

    if(!inputFile) {
        perror("could not open input file");
        fclose(inputFile);
        return EXIT_FAILURE;
    }

    FILE* outputFile = fopen("output.wasd", "w");

    if(!outputFile) {
        perror("could not open output file");
        fclose(outputFile);
        return EXIT_FAILURE;
    }

    int max_rlen = 9;

    encodeFile(inputFile, outputFile, max_rlen);

    fclose(inputFile);
    fclose(outputFile);
    printf("Success");

    // FILE* inputFile = fopen("input.wasd", "rb");
    // if(!inputFile) {
    //     perror("could not open input file");
    //     return EXIT_FAILURE;
    // }

    // // Open the output file for writing
    // FILE *outputFile = fopen("output.wasd", "wb");
    // if (!outputFile) {
    //     perror("Error opening output file");
    //     fclose(inputFile);
    //     return 1;
    // }
    // performRLECompression(inputFile, outputFile);
    
    // fclose(inputFile);
    // fclose(outputFile);

    // FILE* compressedFile = fopen("output.wasd", "r");
    // FILE* ogFile = fopen("og.wasd", "w");

    // performRLEDecompression(compressedFile, ogFile);
    // fclose(compressedFile);
    // fclose(ogFile);
    getchar();
    return EXIT_SUCCESS;
}