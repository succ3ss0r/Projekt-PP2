#include <stdio.h>

int main()
{
    printf("Program obslugi sklepu.\n\n");
    printf("Wybierz co chcesz zrobic:\n");
    short option;
    options(&option);
    struct listOfDistributors distributor;
    struct listOfClients client;

    return 0;
}

void options(short *opt)
{
    printf("\t1. Dodac klienta\n");
    printf("\t2. Dodac dostawce\n");
    printf("\t3. Usunac klienta\n");
    printf("\t4. Usunac dostawce\n");
    while(1)
    {
        scanf("%d", opt);
        printf("Wybrales: %d", opt);
        if(opt>=1 && opt<=4)
            break;
    }
}

