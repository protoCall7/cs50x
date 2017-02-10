/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <math.h>

#include "helpers.h"

bool _sortPass(int values[], int n);
void _xorSwap(int x, int y);
bool _rSearch(int value, int values[], int idxH, int idxL);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
int idxH = (n - 1);
int idxL = 0;
return _rSearch(value, values, idxH, idxL);
}

bool _rSearch(int value, int values[], int idxH, int idxL) {
    float tempF = (idxH / 2.0);
    int idx = round(tempF);
    
    if ((values[idx] == value) || ((values[idxH]) == value) || ((values[idxL]) == value)) {
        return true;
    }
    else if (values[idx] > value) {
        return _rSearch(value, values, idx, idxL);
    }
    else if (values[idx] > value) {
        return _rSearch(value, values, idxH, idx);
    } else {
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool change = false;
    
    // keep making passes across the array until no change is required
    do {
        change = _sortPass(values, n);
    } 
    while (change == true);
}

// makes a single bubble sort pass
bool _sortPass(int values[], int n) {
    bool change = false;
    
    for (int i = 0; i < n; i++) {
        
        // try not to compare beyond bounds of loop
        if ((i + 1) == n) {
            continue;
        }
        
        // check immediate sort order
        if (values[i] > values[i + 1]) {
            // swap values[i] with values[i + 1]
            values[i] = values[i] ^ values[(i + 1)];
            values[(i + 1)] = values[i] ^ values[(i + 1)];
            values[i] = values[(i + 1)] ^ values[i];
            change = true;
        }
    }
    return change;
}