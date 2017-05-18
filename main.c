#include <stdio.h>
#include <stdlib.h>

#define LENGTH 20

struct sProducts{
    //struktura przeznaczona do trzymania informacji o klientach

    int productID;

    char name[LENGTH];
    int amount;
    float price;

    struct sProducts *next;

};

void checkLastID(FILE* fileID, struct sProducts *tmp){

    fileID = fopen("lastid.txt", "r");

    int id;
    fscanf(fileID, "%d", &id);
    tmp->productID = id;

    fclose(fileID);

}

void addClient(struct sProducts *tmp){

    printf("Wprowadz nazwe produktu: ");
    fflush(stdin);
    fgets(tmp->name, LENGTH, stdin);
    printf("Wprowadz ilosc sztuk: ");
    scanf("%d", &(tmp->amount));
    printf("Wprowadz cene produktu: ");
    scanf("%f", &(tmp->price));
    (tmp->productID)++;

}

void saveInFile(FILE* file, FILE* lastID, struct sProducts *tmp){

    file = fopen("products.txt", "a+");
    lastID = fopen("lastid.txt", "w");


    fprintf(lastID, "%d", tmp->productID);
    fprintf(file, "%d", tmp->productID);
    fprintf(file, "%s", tmp->name);
    fprintf(file, "%d\n", tmp->amount);
    fprintf(file, "%.2f\n", tmp->price);

    fclose(lastID);
    fclose(file);

}

void printFile(FILE* file, struct sProducts *tmp){

    file = fopen("products.txt", "r");



    fclose(file);

}

short menu(void){

    printf("0. Wyjscie\n");
    printf("1. Dodac produkt\n");
    printf("2. Usunac produkt\n"); //wykorzystac funkcje fseek()
    printf("3. Wyswietlic produkty\n"); //czytac po jednej linii
    printf("4. Edytowac produkt\n");
    printf("5. \n");
    printf("6. \n");
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
    struct sProducts *front = (struct sProducts *)malloc(sizeof(struct sProducts));
    FILE *products, *lastID;

    while(1){
        short option = menu();

        if(!option)
            return -1;
        else{
            switch(option){
                case 1:
                    checkLastID(lastID, front);
                    addClient(front);
                    saveInFile(products, lastID, front);
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
    }

    return 0;
}
