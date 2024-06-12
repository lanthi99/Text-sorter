/* Lan Thi Duong
COMP348 - Assignment 1
ID: 40276821
*/

//file read and skip logic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "wordtype.h"


#define MAX_SIZE 500  // maximum size of the array
#define MAX_WORD 100 // maximum size of the word


char *trim(char *str) {
    while(isspace((unsigned char)*str)) str++; // trim leading whitespace

    if(*str) {
        char *end_str = str + strlen(str) - 1;
        while(end_str > str && isspace((unsigned char)*end_str)) end_str--; // trim trailing whitespace

        end_str[1] = '\0'; // write new null terminator
    }

    return str;
}

void trimArray(char **array, int size) {
    for(int i = 0; i < size; i++) {
        array[i] = trim(array[i]);
    }
}

//read the input file
char **read_file(char *filename, char *wtype, char **skipword, int n) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File not found.\n");
        return NULL;
    }

    char **array = malloc(MAX_SIZE * sizeof(char *));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = malloc(MAX_WORD * sizeof(char));
        if (array[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            // Free any previously allocated memory
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    char **array1 = malloc(MAX_SIZE * sizeof(char *));
    if (array1 == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        array1[i] = malloc(MAX_WORD * sizeof(char));
        if (array1[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            // Free any previously allocated memory
            for (int j = 0; j < i; j++) {
                free(array1[j]);
            }
            free(array1);
            return NULL;
        }
    }
    
    int i = 0;
    while  (i < MAX_SIZE && fscanf(file, "%[^ ,\n]%*[ ,\n]", array[i]) != EOF) {
        i++;
    }  
   
    //check the word type + skipwords
    int z = 0;
    int count3 = 0;
    char **array4 = malloc(MAX_SIZE * sizeof(char *));
    int array4Index = 0;
    if (strcmp(wtype, "ALPHA") == 0) {
        for (int j = 0; j < i; j++) {
            char temp[500] = ""; //temporary array to store the word
            int tempIndex = 0;
            if (isAlpha(array[j]) == 0) { //if the word contains only English words
                count3 = 0;
                for (int k = 0; k < strlen(array[j]); k++) {
                    if (isalpha(array[j][k])){
                       temp[tempIndex++] = array[j][k];
                       count3++;
                    }
                       
                    else { //if the word contains any other character add space
                        temp[tempIndex++] = ' ';
                    }
                }
                temp[tempIndex] = '\0'; //add null terminator
                if (count3 == 0) {
                    array[j] = NULL;
                }
                else {
                    strcpy(array[j], temp); //copy the temporary array to the original array
                }       
            }
            if (array[j] != NULL) { 
                char *splitword = strtok(array[j], " ");
                while (splitword != NULL) {
                    array4[array4Index] = splitword; //store each token of words in a temporary array
                    for (int k = 0; k < n ; k++) {
                        if (strcmp(splitword, skipword[k]) == 0) { //if the word is a skip word
                            array4[array4Index]= NULL; //assign NULL
                            break;
                        }
                    }
                    array4Index++;
                    splitword = strtok(NULL, " "); 
                }
            }
        }
        for (int j = 0; j < MAX_SIZE; j++) { //copy the words to a new array 
            if (array4[j] == NULL) { //don't copy the word if the word is NULL
                continue;
            }
            else {
                strcpy(array1[z], array4[j]); 
                z++;
            }
        }
        for (int p = z; p < MAX_SIZE; p++) {
            array1[p] = NULL;
        }

        trimArray(array1, z);
        return array1;
    }

    else if (strcmp(wtype, "ALPHANUM") == 0) {
        for (int j = 0; j < i; j++) {
            char temp[500] = ""; //temporary array to store the word
            int tempIndex = 0;
            if (isAlphaNum(array[j]) == 0) { //if the word contains only English words and numbers
                count3 = 0;
                for (int k = 0; k < strlen(array[j]); k++) {
                    if (isalnum(array[j][k])){
                       temp[tempIndex++] = array[j][k];
                        count3++;
                    }
                    else {
                        temp[tempIndex++] = ' '; //if the word contains any other character add space
                    }
                }
                temp[tempIndex] = '\0'; //add null terminator
                if (count3 == 0) {
                    array[j] = NULL;
                }
                else {
                    strcpy(array[j], temp); //copy the temporary array to the original array
                }
            }
            if (array[j] != NULL) { 
                char *splitword = strtok(array[j], " ");
                while (splitword != NULL) {
                    array4[array4Index] = splitword; //store each token of words in a temporary array
                    for (int k = 0; k < n ; k++) {
                        if (strcmp(splitword, skipword[k]) == 0) { //if the word is a skip word
                            array4[array4Index]= NULL; //assign NULL
                            break;
                        }
                    }
                    array4Index++;
                    splitword = strtok(NULL, " ");
                }
            }
        }
        for (int j = 0; j < MAX_SIZE; j++) {
            if (array4[j] == NULL) {
                continue;
            }
            else {
                strcpy(array1[z], array4[j]);
                z++;
            }
        }
        for (int p = z; p < MAX_SIZE; p++) {
            array1[p] = NULL;
        }
        trimArray(array1, z);
        return array1;
    }
    else if (strcmp(wtype, "ALL") == 0){
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < n ; k++) {
                if (strcmp(array[j], skipword[k]) == 0) {
                    array[j]= NULL; //assign NULL
                    break;
                }
            }
        }
        for (int j = 0; j < i; j++) {
            if (array[j] == NULL) {
                continue;
            }
            else {
                strcpy(array1[z], array[j]);
                z++;
            }
        }
        for (int p = z; p < MAX_SIZE; p++) {
            array1[p] = NULL;
        }
        return array1;
    }
    else {
        return array1;
    }

    //check for skip words

    fclose(file);

}

