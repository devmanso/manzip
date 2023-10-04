#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void performRLECompression(FILE *inputFile, FILE *outputFile) {
    int currentChar, lastChar;
    int count = 1;

    // Read the first character
    currentChar = fgetc(inputFile);

    while (currentChar != EOF) {
        // Read the next character
        lastChar = currentChar;
        currentChar = fgetc(inputFile);

        // Check if the current character is the same as the last one
        if (currentChar == lastChar) {
            count++;
        } else {
            // Write the character and its count to the output file only if count > 1
            if (count > 1) {
                fprintf(outputFile, "%c%d", lastChar, count);
            } else {
                // If count is 1, just write the character once
                fputc(lastChar, outputFile);
            }

            // Reset count for the new character
            count = 1;
        }
    }

    // Close the files
    //fclose(inputFile);
    //fclose(outputFile);
}


void performRLEDecompression(FILE *inputFile, FILE *outputFile) {
    int currentChar, count;

    while (1) {
        // Read the character
        currentChar = fgetc(inputFile);

        // Check for end of file
        if (currentChar == EOF) {
            break;
        }

        // Check if the character is a letter
        if (isalpha(currentChar)) {
            // Read the count following the letter
            fscanf(inputFile, "%d", &count);

            // Write the letter multiple times based on the count
            for (int i = 0; i < count; i++) {
                fputc(currentChar, outputFile);
            }
        } else {
            // If the character is not a letter, write it once
            fputc(currentChar, outputFile);
        }
    }

    // Close the files
    //fclose(inputFile);
    //fclose(outputFile);
}

