/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int count = ((d * d) - 1);
    // iterate over the 2D array with a nested for loop
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            // check to see if the board has an odd number of tiles
            if (((d * d) - 1) % 2) {
                // check to see if we're on the last tile
                if (count == 1) {
                    // swap 1 & 2 so the puzzle is solvable
                    board[x][(y - 1)] = 1;
                    board[x][y] = 2;
                    count--;
                    continue;
                }
                // set the tile numbers in reverse order
                board[x][y] = count;
            } else {
                // even board -- set all the tile numbers in reverse order
                board[x][y] = count;
            }
            count--;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // loop over the 2d array
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            // print a _ to signify the blank space
            if (board[x][y] == 0) {
                printf(" _ ");
            } 
            // print the value of the board with padding
            else {
                printf("%2d ", board[x][y]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int tileX;
    int tileY;
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;
    
    // sanity check on tile
    if (tile > ((d * d) - 1)) {
        return false;
    }
    
    // locate coordinates of tile
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            if (board[x][y] == tile) {
                tileX = x;
                tileY = y;
            }
        }
    }
    
    // check for valid moves within the gameboard
    if ((tileX - 1) < 0) {
        up = false;
    } 
    if ((tileX + 1) >= d) {
        down = false;
    } 
    if ((tileY - 1) < 0) {
        left = false;
    } 
    if ((tileY + 1) >= d) {
        right = false;
    }
    
    // check for empty spaces and move --
    // this big scary block of code checks to see if you want to make a valid
    // move, and if you do, uses the 3 XOR trick to move spaces in the 
    // appropriate direction
    if ((board[(tileX - 1)][tileY] == 0) && up) {
        board[tileX][tileY] = board[tileX][tileY] ^ board[(tileX - 1)][tileY];
        board[(tileX - 1)][tileY] = board[tileX][tileY] ^ board[(tileX - 1)][tileY];
        board[tileX][tileY] = board[(tileX - 1)][tileY] ^ board[tileX][tileY];
        return true;
    } else if ((board[(tileX + 1)][tileY] == 0) && down) {
        board[tileX][tileY] = board[tileX][tileY] ^ board[(tileX + 1)][tileY];
        board[(tileX + 1)][tileY] = board[tileX][tileY] ^ board[(tileX + 1)][tileY];
        board[tileX][tileY] = board[(tileX + 1)][tileY] ^ board[tileX][tileY];
        return true;
    } else if ((board[(tileX)][tileY - 1] == 0) && left) {
        board[tileX][tileY] = board[tileX][tileY] ^ board[(tileX)][tileY - 1];
        board[(tileX)][tileY - 1] = board[tileX][tileY] ^ board[(tileX)][tileY - 1];
        board[tileX][tileY] = board[(tileX)][tileY - 1] ^ board[tileX][tileY];
        return true;
    } else if ((board[(tileX)][tileY + 1] == 0) && right) {
        board[tileX][tileY] = board[tileX][tileY] ^ board[(tileX)][tileY + 1];
        board[(tileX)][tileY + 1] = board[tileX][tileY] ^ board[(tileX)][tileY + 1];
        board[tileX][tileY] = board[(tileX)][tileY + 1] ^ board[tileX][tileY];
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int count = 1;
    // iterate over the gameboard and check for the correct order of the tiles.
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            if (board[x][y] != count) {
                return false;
            }
            // increment count and deal with the last number being 0, not d^2.
            if(++count == (d * d)) {
                count = 0;
            }
        }
    }
    return true;
}