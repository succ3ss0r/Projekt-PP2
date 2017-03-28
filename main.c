#include <stdio.h>
#include <stdlib.h>

#include "structures.c"
#include "interactions.c"

int main()
{
    listsPointers listy;
    listInitialize(&listy);

    int option = 0;
    menu(option);

    return 0;
}



