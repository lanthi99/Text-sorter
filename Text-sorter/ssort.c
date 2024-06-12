/* Lan Thi Duong
COMP348 - Assignment 1
ID: 40276821
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileread.h"
#include "wordtype.h"
#include "output.h"

#define MAX_SIZE 500  // maximum size of the array
#define MAX_WORD 100 // maximum size of the word

//sort the array in ascending order
void sortAsc(char **array, int p) {
    char *temp;
    for (int i = 0;i < p; i++) {
        for (int j = i+1; j < p; j++) {
            if (strcmp(array[i], array[j]) > 0) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

//sort the array in descending order
void sortDesc(char **array, int p) {
    char *temp;
    for (int i = 0;i < p; i++) {
        for (int j = i+1; j < p; j++) {
            if (strcmp(array[i], array[j]) < 0) {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

//main function
int main (int argc, char* argv[]) {
    
    //<inputfile> <n> <wtype> <sorttype> [<skipword1> <skipword2> <skipword3> ...]


    //assign the first argument to variable for input file
    char *inputFile = argv[1]; //input file
        
    //if <n> is not specified
    int n; //array size = number of words to print from input file
    if (argv[2] == NULL) {
        fprintf(stderr, "<n> is missing. Please enter a positive integer.\n");
        return 1; //error code 1
    }
    else {
        n = atoi(argv[2]);
    }

    char *wtype; //word type
    //if <wtype> is not specified
    if (argv[3] == NULL) {
        fprintf(stderr, "<wtype> is missing. Please enter ALPHA, ALPHANUM, or ALL.\n");
        return 2; //error code 2
    }
    else {
        wtype = argv[3];
        if (strcmp(wtype, "ALPHA") != 0 && strcmp(wtype, "ALPHANUM") != 0 && strcmp(wtype, "ALL") != 0) {
            fprintf(stderr, "Invalid value for word type. Please enter ALPHA, ALPHANUM, or ALL.\n");
            return 2; //error code 2
        }
    }
        
    char *sortType;
    if (argv[4] == NULL || (strcmp(argv[4], "ASC") != 0 && strcmp(argv[4], "DESC") != 0)){
        sortType = "ASC"; //default sort type is ascending if not specified
    }
    else if (strcmp(argv[4], "ASC") == 0 || strcmp(argv[4], "DESC") == 0) {
        sortType = argv[4];
    }
    
    //create an array of <skipword> if specified
    int n1; //number of skip words
    if (argv[4] == NULL) { //avoid segmentation fault
        n1 = 0;
    }
    else if (strcmp(argv[4], "ASC") == 0 || strcmp(argv[4], "DESC") == 0) {
        n1 = argc - 5;
    }
    else {
        n1 = argc - 4;
    }

    char **skipWord = malloc((n1)* sizeof(char *));

    for (int i = 0; i < n1; i++) {

        if (argv[4] == NULL) { //avoid segmentation fault
            break;
        }
        
        else if (strcmp(argv[4], "ASC") == 0 || strcmp(argv[4], "DESC") == 0) {
            skipWord[i] = argv[i+5];
        }
        else {
            skipWord[i] = argv[i+4];
        }
    }

    //read the input file
    char **array = read_file(inputFile, wtype, skipWord, n1);

    int count = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (array[i] != NULL) {
            count++;
        }
    }

    //sort the array in ascending order
    if (strcmp(sortType, "ASC") == 0) {
        if (n > count) {
            n = count;
        }
        sortAsc(array, n);
    } 
    
    //sort the array in descending order
    else if(strcmp(sortType, "DESC") == 0) {
        if (n > count) {
            n = count;
        }
        sortDesc(array, n);
    }

    output(array, n);
    
    //free the memory allocated for the array
    for (int i = 0; i < MAX_SIZE; i++) {
        free(array[i]);
    }
    free(array);


    return 0;


}       