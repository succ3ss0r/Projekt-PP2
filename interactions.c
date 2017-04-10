//
//
//  PLIK ZAWIERAJACY FUNKCJE POTRZEBNE DO INTERAKCJI Z PROGRAMEM
//
//

void menu(short opt)
{
    printf("Wybierz co chcesz zrobic:\n");
    printf("0. Wyjscie\n");
    printf("1. Dodac klienta\n");
    printf("2. Usunac klienta\n");
    printf("3. Dodac dostawce\n");
    printf("4. Usunac dostawce\n");
    printf("5. Dodac produkt do magazynu\n");
    printf("6. Usunac produkt z magazynu\n");
    while(1)
    {
        scanf("%hi", &opt);
        printf("Wybrales: %hi\n", opt);
        if(opt == 0)    break;
        if(opt>=1 && opt<=6){
            puts("siema");
            break;
        }else{
            printf("Cos poszlo nie tak! Wybierz ponownie co chcesz zrobic.\n");
            continue;
        }
    }
}
