#include <stdio.h>
#include <stdlib.h>

#define LENGTH 20

typedef enum {
    //enum potrzebny do wykluczania dystrybutorow, klientow i produktow zamiast ich usuwania

    false,
    true

} bool;

struct sProducts{
    //struktura przeznaczona do trzymania informacji o klientach

    bool state;

    char name[LENGTH];
    int amount;
    float price;

    struct sProducts *next;
};

void addClient(struct sProducts *tmp){

    tmp->state = true;
    printf("Wprowadz nazwe produktu: ");
    scanf("%s", tmp->name);
    printf("Wprowadz ilosc sztuk: ");
    scanf("%d", &(tmp->amount));
    printf("Wprowadz cene produktu: ");
    scanf("%f", &(tmp->price));

}

void saveInFile(FILE* file, struct sProducts *tmp){

    file = fopen("products.txt", "a+");

    fprintf(file, "%s ", tmp->name);
    fprintf(file, "%d ", tmp->amount);
    fprintf(file, "%.2f ", tmp->price);
    fprintf(file, "\n");

    fclose(file);

}

short menu(void){

    printf("0. Wyjscie\n");
    printf("1. Dodac klienta\n");
    printf("2. Usunac klienta\n");
    printf("3. Dodac dostawce\n");
    printf("4. Usunac dostawce\n");
    printf("5. Dodac produkt do magazynu\n");
    printf("6. Usunac produkt z magazynu\n");
    printf("Wybierz co chcesz zrobic: ");
    short opt;
    while(1){
        scanf("%hi", &opt);
        printf("Wybrales: %hi\n", opt);
        if(opt == 0)    break;
        if(opt>=1 && opt<=6){
            return opt;
        }else{
            printf("Cos poszlo nie tak! Wybierz ponownie: ");
            continue;
        }
    }
    exit(1);

}

int main(void)
{
    struct sProducts *new_client = (struct sProducts *)malloc(sizeof(struct sProducts));
    FILE *clients;
    short option = menu();
    if(!option)
        return -1;
    else{
        switch(option){
            case 1:
                addClient(new_client);
                saveInFile(clients, new_client);
                break;
            case 2:
                //delClient(&listy);
                break;
            case 3:
                //addDistrib(listy, distrib);
                break;
            case 4:
                //delDistrib(listy, distrib);
                break;
            case 5:
                //addProd(listy, prod);
                break;
            case 6:
                //delProd(listy, prod);
                break;
            default:
                printf("Wystapil blad, program zostanie zakonczony.");
                option = 0;
        }
    }

    return 0;
}
