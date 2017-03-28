#include <stdio.h>
#include <stdlib.h>
#include "structures.c"

int main()
{
    listsPointers listy;
    listInitialize(&listy);
    short option;
    menu(option);

    return 0;
}

void menu(short opt)
{
    printf("Wybierz co chcesz zrobic:\n");
    printf("\t1. Dodac klienta\n");
    printf("\t2. Dodac dostawce\n");
    printf("\t3. Usunac klienta\n");
    printf("\t4. Usunac dostawce\n");
    printf("\t5. Dodac produkt do magazynu\n");
    printf("\t6. Usunac produkt z magazynu\n");
    while(1)
    {
        scanf("%hi", &opt);
        printf("Wybrales: %hi\n", opt);
        if(opt>=1 && opt<=6){
            puts("siema");
            break;
        }else{
            printf("Cos poszlo nie tak! Wybierz ponownie co chcesz zrobic.\n");
            continue;
        }
    }
}

