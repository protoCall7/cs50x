#include <cs50.h>
#include <stdio.h>

void printSpace(int count);
void printHash(int count);

int main(void) {
    int height;
    int spaces;
    
    // get the height
    do {
        printf("height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);
    
    spaces = height - 1;
    
    for (int j = 1; j <= height; j++) {
        printSpace(spaces);
        printHash(j + 1);
        spaces--;
    }
}

void printSpace(int count) {
    while (count > 0) {
        printf(" ");
        count--;
    }
}

void printHash(int count) {
    while (count > 0) {
        printf("#");
        count--;
    }
    printf("\n");
}