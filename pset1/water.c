#include <stdio.h>
#include <cs50.h>

int getPositiveInt(void);

int main(void) {
    printf("minutes: ");
    int minutes = getPositiveInt();
    int ounces = minutes * 192;
    int bottles = ounces / 16;
    printf("bottles: %d\n", bottles);
}

int getPositiveInt(void) {
    int n = GetInt();
    if (n < 1) {
        do {
            printf("Please select a positive number: ");
            n = GetInt();
        }
        while (n < 1);
    }
    
    return n;
}