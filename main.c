#include <stdio.h>
#include <stdlib.h>
#include "structures.c"
#include "interactions.c"

int main()
{
    listsPointers listy;
    listInitialize(&listy);
    short option;
    menu(option);

    return 0;
}



