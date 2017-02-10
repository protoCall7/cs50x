#include <stdio.h>
#include <cs50.h>
#include <string.h>

int parsekey(char key);
char rotate(char pt, int key);
int _rotInt(int pt, int key);

int main(int argc, string argv[]) {
    // error handling before we set up
    bool badInput = false;
    if ((argc < 2) || (argc > 2)) {
        printf("Usage: ./vigenere <key>");
        return 1;
    } else {
        for (int i = 0; i < strlen(argv[1]); i++) {
            
            if ((argv[1][i] < 65) || (argv[1][i] > 90)) {
                if ((argv[1][i] < 97) || (argv[1][i] > 122)) {
                    badInput = true;
                }
            }
        }
    }
    
    if (badInput) {
        printf("Usage: ./vigenere <key>");
        return 1;       
    }
    
    int intKey[(strlen(argv[1]))];
    string pt = GetString();
    


    // get the key into integer form
    for (int i = 0; i < strlen(argv[1]); i++) {
        intKey[i] = parsekey(argv[1][i]);
        if (intKey[i] == -1) {
            printf("Something went wrong!\n");
            return 1;
        }
    }
    
    // loop over the string and convert to CT
    for (int i = 0, j = 0; i < strlen(pt); i++) {
        char ct = rotate(pt[i], intKey[j]);
        printf("%c", ct);
        
        // account for variable key length
        if ((ct >= 97 && ct <= 122) || (ct >= 65 && ct <= 90)) {
            if(++j >= strlen(argv[1])) {
                j = 0;
            }
        }
    }
    printf("\n");
    
    return 0;
}


int parsekey(char key) {
    int upperFlag = 0;
    int lowerFlag = 0;
    int result;

        // check for case
        if (key >= 65 && key <= 90) {
            upperFlag = 1;
            lowerFlag = 0;
        } else if (key >= 97 && key <= 122) {
            upperFlag = 0;
            lowerFlag = 1;
        }
        
        if (upperFlag) {
            result = key - 65;
        } else if (lowerFlag) {
            result = key - 97;
        } else {
            result = -1;
        }
    
    return result;
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