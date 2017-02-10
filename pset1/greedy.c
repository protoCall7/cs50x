// greedy.c
// CS50x pset 1
// a program that calculates the minimum number of coins required to give a user change.
// Peter H. Ezetta (protocall7@gmail.com)

#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    // declare variables
    float input;
    int cents;
    int coins = 0;
    
    // get and validate user input
    do {
        printf("How much change is owed? ");
        input = GetFloat();
    }
    while(input < 0);
    
    // calculate cents
    cents = round(input * 100);
    
    // calculate number of coins despensed
    while(cents >= 25) {
        cents -= 25;
        coins++;
    }
    while(cents >= 10) {
        cents -= 10;
        coins++;
    }
    while(cents >= 5) {
        cents -= 5;
        coins++;
    }
    while(cents > 0) {
        cents--;
        coins++;
    }
    
    printf("%d\n", coins);
}
