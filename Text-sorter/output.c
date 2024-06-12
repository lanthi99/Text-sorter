/* Lan Thi Duong
COMP348 - Assignment 1
ID: 40276821
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//write output to the console

void output(char **array, int n) {
    
    if (array == NULL) {
        fprintf(stderr, "Array is empty.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        if (array[i] != NULL) {
            if (i % 10 == 9) {
            printf("%s\n", array[i]);
            continue;
            }
            printf("%s ", array[i]);  
        }
    }
}

