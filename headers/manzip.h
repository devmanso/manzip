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

        /* Check if the character is a digit */
        if (isdigit(src[i])) {
            continue;  // If it's a digit, skip encoding
        }
 
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


/* Decodes the Run Length Encoded string */
// char* decodeString(const char* rleSrc)
// {
//     int len = strlen(rleSrc);

//     /* The maximum possible length of the decoded string is twice the length
//        of the input string (in case all characters are encoded). */
//     char* decoded = (char*)malloc(sizeof(char) * (len * 2 + 1));

//     int i, j = 0;

//     for (i = 0; i < len; i++) {
//         char currentChar = rleSrc[i];

//         if (isdigit(currentChar)) {
//             /* Skip numbers, as they are not encoded */
//             continue;
//         } else if (isalpha(currentChar) || strchr("_,(*&^$", currentChar) != NULL) {
//             /* If it's an alphabetical character or a special character, it is encoded */
//             int count = 0;

//             /* Calculate the run length */
//             while (i + 1 < len && isdigit(rleSrc[i + 1])) {
//                 count = count * 10 + (rleSrc[i + 1] - '0');
//                 i++;
//             }

//             /* If count is 0, set it to 1 */
//             count = (count == 0) ? 1 : count;

//             /* Repeat the character count times in the decoded string */
//             for (int k = 0; k < count; k++) {
//                 decoded[j++] = currentChar;
//             }
//         } else {
//             /* Other characters are not encoded, copy them as is */
//             decoded[j++] = currentChar;
//         }
//     }

//     /* Terminate the decoded string */
//     decoded[j] = '\0';

//     return decoded;
// }

char specialCharacters[] = "~!@#$%^&*()_+-={}|[]\\:\";\'<>?,./";

char* decodeString(const char* rleSrc)
{
    int len = strlen(rleSrc);

    /* The maximum possible length of the decoded string is twice the length
       of the input string (in case all characters are encoded). */
    char* decoded = (char*)malloc(sizeof(char) * (len * 2 + 1));

    int i, j = 0;

    for (i = 0; i < len; i++) {
        char currentChar = rleSrc[i];

        if (isdigit(currentChar)) {
            /* Skip numbers, as they are not encoded */
            //continue;
            decoded[j++] = currentChar;
        } else if (isalpha(currentChar) || strchr(specialCharacters, currentChar) != NULL) {
            /* If it's an alphabetical character or a special character, it is encoded */
            int count = 1;  // Assume default run length is 1

            /* Check if the next character is a digit */
            if (i + 1 < len && isdigit(rleSrc[i + 1])) {
                count = rleSrc[i + 1] - '0';
                i++;  // Skip the digit
            }

            /* Repeat the character count times in the decoded string */
            for (int k = 0; k < count; k++) {
                decoded[j++] = currentChar;
            }
        } else {
            /* Other characters are not encoded, copy them as is */
            decoded[j++] = currentChar;
        }
    }

    /* Terminate the decoded string */
    decoded[j] = '\0';

    return decoded;
}


/* Decodes the content of an input file and writes the decoded content to an output file */
void decodeFile(FILE* inputFile, FILE* outputFile) {
    char buffer[1024];  // Adjust the buffer size as needed

    /* Read each line from the input file */
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        /* Remove newline character if present */
        char* newline = strchr(buffer, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        /* Decode the string and write to the output file */
        char* decodedString = decodeString(buffer);
        fprintf(outputFile, "%s\n", decodedString);

        /* Free the memory allocated by decodeString */
        free(decodedString);
    }
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