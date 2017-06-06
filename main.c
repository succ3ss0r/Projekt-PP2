#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

bool addToList(struct sProducts *first, struct sProducts *tmp) {
    if(!tmp)
        return true;

    struct sProducts *q = first;
    while(q->next)
        q = q->next;

    q->next = tmp;

    return false;
}

int checkLastID(FILE* fileID){

    int id;

    fileID = fopen("lastid.txt", "r");

    fscanf(fileID, "%d", &id);

    fclose(fileID);

    return id;
}

void addProduct(struct sProducts *first, int *id) {

    struct sProducts *tmp = (struct sProducts *)calloc(1, sizeof(struct sProducts));

    tmp->productID = ++(*id);
    printf("Wprowadz nazwe produktu: ");
    fflush(stdin);
    fgets(tmp->name, LENGTH, stdin);
    printf("Wprowadz ilosc sztuk: ");
    scanf("%d", &(tmp->amount));
    printf("Wprowadz cene produktu: ");
    scanf("%f", &(tmp->price));
    tmp->state = true;

    if( addToList(first, tmp) )
        free(tmp);
}

void saveLastIdInFile(FILE* lastID, int id){

    lastID = fopen("lastid.txt", "w");

    fprintf(lastID, "%d", id);

    fclose(lastID);

}

void checkAmount(struct sProducts *first){

    if(first){
        if(first->amount < 20){
            printf("Ilosc %s wynosi %d ( dopuszczalna minimalna ilosc w magazynie to 20 )\n", first->name, first->amount);
            printf("Nalezy zamowic wiecej %s\n\n", first->name);
            checkAmount(first->next);
        }else
            checkAmount(first->next);
    }
}

void loadList(struct sProducts *first, char *f_name){

    FILE* file = fopen(f_name, "r+b");
    rewind(file);

    while(!feof(file)){
        struct sProducts *tmp = (struct sProducts *)malloc(sizeof(struct sProducts));
        fread(tmp, 1, sizeof(struct sProducts), file);
        printf("XDDD");
        addToList(first, tmp);
    }

    fclose(file);

}

int searchForProduct(struct sProducts *first){

    int id;
    char product[LENGTH];

    fflush(stdin);
    fgets(product, LENGTH, stdin);

    while(first){
        if(strcmp(first->name, product) == 0 && first->state == true){
            id = first->productID;

            return id;
        }else
            first = first->next;
    }

    return -1;
}

void delProduct(struct sProducts *first, int id){

    while(first){
        if(first->productID == id){
            first->state = false;
            break;
        }
        first = first->next;
    }

}

void printAvalibleProducts(const struct sProducts *first){
    while(first){
        if(first->state){
            printf("ID:\t%d\n", first->productID);
            printf("Nazwa:\t%s", first->name);
            printf("Ilosc:\t%d\n", first->amount);
            printf("Cena za sztuke:\t%f\n", first->price);
        }
        first = first->next;
    }
}

void saveUpdatedList(struct sProducts *first, char *name){

    FILE *file = fopen(name, "w+b");

    while(first){
        fwrite(&(first->productID), 1, sizeof(int), file);
        fwrite(&(first->state), 1, sizeof(bool), file);
        fwrite(first->name, 1, LENGTH, file);
        fwrite(&(first->amount), 1, sizeof(int), file);
        fwrite(&(first->price), 1, sizeof(float), file);

        first = first->next;
    }

    fclose(file);

}

void removeList(struct sProducts **first){
    if (NULL == *first)
        return;

    do
    {
        struct sProducts *next = (*first)->next;
        free(*first);
        *first = next;
    } while (*first != NULL);
    *first = NULL;
}

void menu(void){

    printf("0. Wyjscie\n");
    printf("1. Dodac produkt\n");
    printf("2. Usunac produkt\n");
    printf("3. Wyswietlic produkty\n");
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
    struct sProducts *first = (struct sProducts *)calloc(1, sizeof(struct sProducts));
    FILE *f_lastID = NULL;
    int id;

    //loadList(first, "products.txt");
    checkAmount(first);

    menu();

    while(1){

        short option = opt();

        if(!option)
            return -1;
        else{
            switch(option){
                case 1:
                    id = checkLastID(f_lastID);
                    addProduct(first, &id);
                    saveLastIdInFile(f_lastID, id);
                    saveUpdatedList(first, "products.txt");
                    break;
                case 2:
                    printf("Jakiego produkt chcesz usunac? ");
                    id = searchForProduct(first);
                    if(id > 0){
                        delProduct(first, id);
                        saveUpdatedList(first, "products.txt");
                        printf("Usuniety produkt mial id: %d\n", id);
                    }else
                        printf("Nie mozna usunac produktu poniewaz go nie ma w bazie.\n");
                    break;
                case 3:
                    //loadList(first, "products.txt");
                    printAvalibleProducts(first);
                    break;
                case 4:
                    //loadList(first, "products.txt");
                    break;
                case 5:
                    //loadList(first, "products.txt");
                    break;
                case 6:
                    printf("Jakiego produktu szukasz? ");
                    id = searchForProduct(first);
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
    removeList(&first);

    return 0;
}
