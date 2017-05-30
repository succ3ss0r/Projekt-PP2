#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 20

struct sProducts{

    int productID;

    bool state;

    char name[LENGTH];
    int amount;
    float price;

    struct sProducts *next;

};

int checkLastID(FILE* fileID){

    int id;

    fileID = fopen("lastid.txt", "r");

    fscanf(fileID, "%d", &id);

    fclose(fileID);

    return id;
}

void addProduct(struct sProducts *tmp, int id){

    tmp->productID = id;
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
    fwrite(&(tmp->productID), 1, sizeof(int), file);
    fwrite(tmp->name, 1, LENGTH, file);
    fwrite(&(tmp->amount), 1, sizeof(int), file);
    fwrite(&(tmp->price), 1, sizeof(float), file);

    fclose(lastID);
    fclose(file);

}

void checkAmount(struct sProducts *first){

    if(first){
        if(first->amount < 20){
            printf("Ilosc %s wynosi %d ( dopuszczalna minimalna ilosc w magazynie to 20 )\n", first->name, first->amount);
            printf("Nalezy zamowic wiecej %s", first->name);
            checkAmount(first->next);
        }else
            checkAmount(first->next);
    }
}

void loadList(struct sProducts *first, FILE* lastID){

    lastID = fopen("lastid.txt", "r");

    int id = checkLastID(lastID);

    fclose(lastID);

    if(id == 0)
        return;
    else{

    }

}

void searchProductNamed(char product[LENGTH]){

    printf("Jakiego produktu szukasz? ");
    fflush(stdin);
    fgets(product, LENGTH, stdin);

}

int searchForProduct(struct sProducts *first, char product[LENGTH]){

    int id;

    if(first){
        if(strcmp(first->name, product) == 0){
            id = first->productID;

            return id;
        }else{
            searchForProduct(first->next, product);
        }
    }

    return -1;
}

void printFile(FILE* file, struct sProducts *first){

    if(first != NULL){
        if(first->state){
            fread(&(first->productID), 1, sizeof(int), file);
            fread(first->name, 1, sizeof(first->name), file);
            fread(&(first->amount), 1, sizeof(int), file);
            fread(&(first->price), 1, sizeof(float), file);
            printFile(file, first->next);
        }
    }

}

void menu(void){

    printf("0. Wyjscie\n");
    printf("1. Dodac produkt\n");
    printf("2. Usunac produkt\n"); //wykorzystac funkcje fseek()
    printf("3. Wyswietlic produkty\n"); //czytac po jednej linii
    printf("4. Zamow produkt\n");
    printf("5. Wydaj produkt\n");
    printf("6. Wyszukaj produkt\n");

}

short opt(void){

    printf("Wybierz co chcesz zrobic: ");
    short opt;
    while(1){
        scanf("%hi", &opt);
        printf("Wybrales: %hi\n", opt);
        if(opt == 0)    break;
        if(opt >= 1 && opt <= 6){
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
    struct sProducts *first = (struct sProducts *)malloc(sizeof(struct sProducts));
    FILE *products, *lastID;
    int id;
    char product[LENGTH];

    //loadList(first, lastID);
    //checkAmount(first);

    menu();

    while(1){

        short option = opt();

        if(!option)
            return -1;
        else{
            switch(option){
                case 1:
                    id = checkLastID(lastID);
                    addProduct(first, id);
                    saveInFile(products, lastID, first);
                    break;
                case 2:
                    //delProd();
                    break;
                case 3:
                    products = fopen("products.txt", "a+");
                    rewind(products);
                    printFile(products, first);
                    fclose(products);
                    break;
                case 4:
                    //plusProd();
                    break;
                case 5:
                    //minusProd();
                    break;
                case 6:
                    searchProductNamed(product);
                    id = searchForProduct(first, product);
                    if(id > 0)
                        printf("Produkt ktorego szukasz ma id %d\n", id);
                    else
                        printf("Nie znaleziono produktu.\n");
                    break;
                default:
                    printf("Wystapil blad, program zostanie zakonczony.");
                    option = 0;
            }
        }
    }

    return 0;
}
