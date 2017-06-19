#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 20

struct sProducts
{
    int productID;

    bool state;

    char name[LENGTH];
    int amount;
    float price;

    struct sProducts *next;
};

void menu(void);
short opt(void);
void addProduct(struct sProducts *first, int *id);
bool addToList(struct sProducts **first, struct sProducts *tmp);
int checkLastID(char* name);
void saveLastIdInFile(char* name, int id);
void checkAmount(struct sProducts *first);
void loadList(struct sProducts **first, char *f_name);
void expendProduct(struct sProducts *first, int id);
void orderProduct(struct sProducts *first, int id);
int searchForProduct(struct sProducts *first);
void delProduct(struct sProducts *first, int id);
void printAvalibleProducts(const struct sProducts *first);
void saveUpdatedList(struct sProducts *first, char *name);
void removeList(struct sProducts **first);


int main(void)
{
    struct sProducts *first = (struct sProducts *)calloc(1, sizeof(struct sProducts));
    int id;

    loadList(&first, "products");
    checkAmount(first);
    menu();

    while(1) {
        short option = opt();

        if(!option)
            return -1;
        else {
            switch(option) {
                case 1:
                    id = checkLastID("lastid.txt");
                    addProduct(first, &id);
                    saveLastIdInFile("lastid.txt", id);
                    saveUpdatedList(first, "products");
                    menu();
                    break;
                case 2:
                    printf("Jakiego produkt chcesz usunac? ");
                    id = searchForProduct(first);
                    if(id > 0) {
                        delProduct(first, id);
                        saveUpdatedList(first, "products");
                        printf("Usuniety produkt mial id: %d\n\n", id);
                    } else
                        printf("\nNie mozna usunac produktu poniewaz go nie ma w bazie.\n\n");
                    break;
                case 3:
                    system("cls");
                    printAvalibleProducts(first);
                    menu();
                    break;
                case 4:
                    printf("Jaki produkt chcesz zamowic?\n");
                    id = searchForProduct(first);
                    if(id > 0) {
                        orderProduct(first, id);
                        saveUpdatedList(first, "products");
                    } else
                        printf("Nie mozna zamowic produktu poniewaz go nie ma w bazie.\n");
                    break;
                case 5:
                    printf("Jaki produkt chcesz wydac z magazynu?\n");
                    id = searchForProduct(first);
                    if(id > 0) {
                        expendProduct(first, id);
                        saveUpdatedList(first, "products");
                    } else
                        printf("Nie mozna wydac produktu poniewaz go nie ma w bazie.\n");
                    checkAmount(first);
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

void menu(void)
{
    printf("0. Wyjscie\n");
    printf("1. Dodac produkt\n");
    printf("2. Usunac produkt\n");
    printf("3. Wyswietlic produkty\n");
    printf("4. Zamow produkt\n");
    printf("5. Wydaj produkt\n");
    printf("6. Wyszukaj produkt\n");
}

short opt(void)
{
    printf("Wybierz co chcesz zrobic: ");
    short opt;
    while(1) {
        fflush(stdin);
        scanf("%hi", &opt);
        if(opt == 0)    break;
        if(opt >= 1 && opt <= 6) {
            return opt;
        } else {
            printf("Cos poszlo nie tak! Wybierz ponownie: ");
            continue;
        }
    }
    exit(1);
}

void addProduct(struct sProducts *first, int *id)
{
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
    system("cls");

    if(addToList(&first, tmp))
        free(tmp);
    else
        printf("Pomyslnie dodano produkt\n\n");
}

bool addToList(struct sProducts **first, struct sProducts *tmp)
{
    if(!tmp)
        return true;

    struct sProducts *q = *first;
    while(q->next)
        q = q->next;

    tmp->next = q->next;
    q->next = tmp;

    return false;
}

int checkLastID(char* name)
{
    int id = 0;

    FILE* fileID = fopen("lastid.txt", "r");

    if(!fileID) {
        fileID = fopen(name, "w");
        fprintf(fileID, "%d", id);
        fclose(fileID);
    } else {
        fscanf(fileID, "%d", &id);
        fclose(fileID);
    }

    return id;
}

void saveLastIdInFile(char* name, int id)
{
    FILE* lastID = fopen(name, "w");

    fprintf(lastID, "%d", id);

    fclose(lastID);

}

void checkAmount(struct sProducts *first)
{
    first = first->next;

    while(first){
        if(first->amount < 20 && first->state){
            printf("\nIlosc %s wynosi %d ( dopuszczalna minimalna ilosc w magazynie to 20 )\n\n", first->name, first->amount);
        }
        first = first->next;
    }
}

void loadList(struct sProducts **first, char *f_name)
{
    FILE* file = fopen(f_name, "r+b");

    if(!file)
        file = fopen(f_name, "w");

    struct sProducts *temporary = (struct sProducts *)malloc(sizeof(struct sProducts));

    while(fread(&(*temporary), sizeof(struct sProducts), 1, file) == 1) {
        struct sProducts *tmp = (struct sProducts *)malloc(sizeof(struct sProducts));
        tmp->productID = temporary->productID;
        tmp->state = temporary->state;
        strcpy(tmp->name, temporary->name);
        tmp->amount = temporary->amount;
        tmp->price = temporary->price;
        struct sProducts *next = *first;
        while(next->next)
            next = next->next;

        next->next = tmp;
        tmp->next = NULL;
    }
    free(temporary);

    fclose(file);
}

void expendProduct(struct sProducts *first, int id)
{
    int amount;

    while(first) {
        if(first->productID == id) {
            printf("Jaka ilosc chcesz wydac?\n");
            scanf("%d", &amount);
            if(first->amount-amount < 0)
                printf("Nie mozna wydac takiej ilosci poniewaz nie ma tylu sztuk na magazynie.\n");
            else {
                amount = first->amount - amount;
                first->amount = amount;
                break;
            }
        }
        first = first->next;
    }
}

void orderProduct(struct sProducts *first, int id)
{
    int amount;

    while(first) {
        if(first->productID == id) {
            printf("Jaka ilosc chcesz zamowic?\n");
            scanf("%d", &amount);
            amount = amount + first->amount;
            first->amount = amount;
            break;
        }
        first = first->next;
    }
}

int searchForProduct(struct sProducts *first)
{
    int id;
    char product[LENGTH];

    fflush(stdin);
    fgets(product, LENGTH, stdin);

    while(first) {
        if(strcmp(first->name, product) == 0 && first->state == true) {
            id = first->productID;

            return id;
        } else
            first = first->next;
    }

    return -1;
}

void delProduct(struct sProducts *first, int id)
{
    while(first) {
        if(first->productID == id) {
            first->state = false;
            break;
        }
        first = first->next;
    }
    printf("\nPomyslnie usunieto produkt\n");
}

void printAvalibleProducts(const struct sProducts *first)
{
    if(!first->next)
        printf("Baza produktow jest pusta!\n\n");

    while(first) {
        if(first->state) {
            printf("ID:\t%d\n", first->productID);
            printf("Nazwa:\t%s", first->name);
            printf("Ilosc:\t%d\n", first->amount);
            printf("Cena za sztuke:\t%f\n", first->price);
            puts("");
        }
        first = first->next;
    }
}

void saveUpdatedList(struct sProducts *first, char *name)
{
    FILE *file = fopen(name, "w+b");

    while(first) {
        if(first->state) {
                fwrite(&(*first), sizeof(struct sProducts), 1, file);
        }
        first = first->next;
    }

    fclose(file);
}

void removeList(struct sProducts **first)
{
    if (NULL == *first)
        return;

    do {
        struct sProducts *next = (*first)->next;
        free(*first);
        *first = next;
    } while (*first != NULL);

    *first = NULL;
}
