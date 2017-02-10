#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    string name;
    int printflag = 0;
    
    name = GetString();
    
    //print the first initial
    printf("%c", toupper(name[0]));
    
    //look for more initials
    for (int i = 0; i < strlen(name); i++) {
        if (printflag == 1) {
            printf("%c", toupper(name[i]));
            printflag = 0;
        }
        if (name[i] == ' ') {
            printflag = 1;
        }
    }
    printf("\n");
}