#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char rotate(char pt, int key);
int _rotInt(int pt, int key);

int main(int argc, string argv[]) {
    // declare vars
    string pt;
    int key;
    
    // check for arvg[1]
    if (argc != 2) {
        printf("Usage: ./caesar <key length>");
        return 1;
    }
    
    // get string and key
    pt  = GetString();
    key = atoi(argv[1]);
    
    // iterate through each letter of string and process
    for (int i = 0; i < strlen(pt); i++) {
        printf("%c", rotate(pt[i], key));
    }
    printf("\n");
}

// implements rotation algorithm while accounting for
// ASCII table as well as special chars
char rotate(char pt, int key) {
    // declare vars
    char ct;
    int upperFlag = 0;
    int lowerFlag = 0;
    
    // check for case
    if (pt >= 65 && pt <= 90) {
        upperFlag = 1;
        lowerFlag = 0;
    } else if (pt >= 97 && pt <= 122) {
        upperFlag = 0;
        lowerFlag = 1;
    }
    
    // Process letter
    if (upperFlag) {
        pt -= 64;
        ct = _rotInt(pt, key);
        ct += 64;
    } else if (lowerFlag) {
        pt -= 96;
        ct = _rotInt(pt, key);
        ct += 96;
    } else {
        ct = pt;
    }
    
    return ct;
}

// Implementation of rotation algorithm
int _rotInt(int pt, int key) {
    return ((pt + key) % 26);
}