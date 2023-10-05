#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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


/* Returns the Run Length Encoded string for the 
   source string src */
char* encodeString(char* src, int max_rlen)
{
    int rLen;
    char count[max_rlen];
    int len = strlen(src);
 
    /* If all characters in the source string are different, 
    then size of destination string would be twice of input string.
    For example if the src is "abcd", then dest would be "a1b1c1d1"
    For other inputs, size would be less than twice.  */
    char* dest = (char*)malloc(sizeof(char) * (len * 2 + 1));
 
    int i, j = 0, k;
 
    /* traverse the input string one by one */
    for (i = 0; i < len; i++) {
 
        /* Copy the first occurrence of the new character */
        dest[j++] = src[i];
 
        /* Count the number of occurrences of the new character */
        rLen = 1;
        while (i + 1 < len && src[i] == src[i + 1]) {
            rLen++;
            i++;
        }
 
        /* Store rLen in a character array count[] */
        sprintf(count, "%d", rLen);
 
        /* Copy the count[] to destination */
        for (k = 0; *(count + k); k++, j++) {
            dest[j] = count[k];
        }
    }
 
    /*terminate the destination string */
    dest[j] = '\0';
    return dest;
}

void encodeFile(FILE* inputFile, FILE* outputFile, int max_rlen) {
    // Buffer to read each line from the file
    char buffer[1024];

    // Read lines from the input file
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // Remove newline character from the end of the line
        buffer[strcspn(buffer, "\n")] = '\0';

        // Encode the line using encodeString
        char* encodedLine = encodeString(buffer, max_rlen);

        // Write the encoded line to the output file
        fprintf(outputFile, "%s\n", encodedLine);

        // Free the memory allocated by encodeString
        free(encodedLine);
    }
}