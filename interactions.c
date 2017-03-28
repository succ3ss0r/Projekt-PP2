//
//
//  PLIK ZAWIERAJACY FUNKCJE POTRZEBNE DO INTERAKCJI Z PROGRAMEM
//
//

void menu(short opt)
{
    printf("Wybierz co chcesz zrobic:\n");
    printf("1.\tDodac klienta\n");
    printf("2.\tDodac dostawce\n");
    printf("3.\tUsunac klienta\n");
    printf("4.\tUsunac dostawce\n");
    printf("5.\tDodac produkt do magazynu\n");
    printf("6.\tUsunac produkt z magazynu\n");
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
