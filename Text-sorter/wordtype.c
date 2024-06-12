/* Lan Thi Duong
COMP348 - Assignment 1
ID: 40276821
*/

//will contain any logic associated with the word types

#include <stdio.h>

//function to check if the word contains only English words ([a-zA-Z])
int isAlpha (char *word) {
    int i = 0;
    while (word[i] != '\0') { 
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) { //compare the ASCII values of the characters
            i++;
        }
        else { //if the word contains any other character
            return 0; //return false
        }
    }
    return 1; //return true
}

//function to check if the word contains only English words and numbers ([a-zA-Z0-9])
int isAlphaNum (char *word) {
    int i = 0;
    while (word[i] != '\0') {
        if ((word[i] >= '0' && word[i] <= '9') || (word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) { //compare the ASCII values of the characters
            i++;
        }
        else { //if the word contains any other character
            return 0; //return false
        }
    }
    return 1; //return true
}



