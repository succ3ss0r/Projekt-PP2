#include <stdio.h>
#include <stdlib.h>

#include "structures.c"

int main()
{
    listsPointers listy;
    listInitialize(&listy);
    int option;
    menu(option);

    return 0;
}

void menu(int opt)
{
    printf("\t1. Dodac klienta\n");
    printf("\t2. Dodac dostawce\n");
    printf("\t3. Usunac klienta\n");
    printf("\t4. Usunac dostawce\n");
    while(1)
    {
        scanf("%d", &opt);
        printf("Wybrales: %d", opt);
        if(opt>=1 && opt<=4){
            puts("siema");
            break;
        }else
            continue;
    }
}

