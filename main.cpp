#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale>

#define ODLID 4
#define ODLSTATE 8
#define ODLNAME 20
#define ODLAMOUNT 6
#define ODLPRICE 9

#define LENGTH 20

using namespace std;

struct sProducts {
    unsigned int productID;

    bool state;

    char name[LENGTH];
    unsigned int amount;
    float price;

    struct sProducts *next;
};

class c_magazyn {
    char filename[20];
    fstream file;
    struct sProducts *productsList;
    unsigned int ID;
public:
    struct sProducts *returnLastElement() {
        struct sProducts *tmp = productsList;
        while(tmp->next)
            tmp = tmp->next;
        return tmp;
    }
    bool addNewProduct(bool state, const char name[LENGTH], unsigned int amount, float price) {
        struct sProducts *lastElement = returnLastElement();
        struct sProducts *tmp = new sProducts;
        if(tmp) {
            tmp->productID = ++ID;
            tmp->state = state;
            for(int i = 0; i < LENGTH; ++i)
                tmp->name[i] = name[i];
            tmp->amount = amount;
            tmp->price = price;

            tmp->next = lastElement->next;
            lastElement->next = tmp;
        }
        return true;
    }
    void printTableHeaders() {
        cout << left << setw(ODLID) << setfill(' ') << "ID";
        cout << left << setw(ODLSTATE) << setfill(' ') << "STATUS";
        cout << left << setw(ODLNAME) << setfill(' ') << "NAZWA";
        cout << left << setw(ODLAMOUNT) << setfill(' ') << "ILOSC";
        cout << left << setw(ODLPRICE) << setfill(' ') << "CENA/SZT";
    }
    void printProductInformation(struct sProducts *tmp) {
            cout << endl;
            cout << left << setw(ODLID) << setfill(' ') << tmp->productID;
            cout << left << setw(ODLSTATE) << setfill(' ') << (tmp->state?'o':'x');
            cout << left << setw(ODLNAME) << setfill(' ') << tmp->name;
            cout << left << setw(ODLAMOUNT) << setfill(' ') << tmp->amount;
            cout << left << setw(ODLPRICE) << setfill(' ') << tmp->price;
    }
    void showAllProducts() {
        struct sProducts *tmp = productsList->next;

        cout << endl << endl << "\t\tWszystkie produkty: " << endl;

        while(tmp) {
            printProductInformation(tmp);
            tmp = tmp->next;
        }
    }
    void showAllActiveProducts() {
        struct sProducts *tmp = productsList->next;

        cout << endl << endl << "\t\tWszystkie aktywne produkty: " << endl;
        printTableHeaders();
        while(tmp) {
            if(!tmp->state) {
                tmp = tmp->next;
                continue;
            }
            printProductInformation(tmp);
            tmp = tmp->next;
        }
    }
    void showAllUnactiveProducts() {
        struct sProducts *tmp = productsList->next;

        cout << endl << endl << "\t\tWszystkie nieaktywne produkty: " << endl;
        printTableHeaders();

        while(tmp) {
            if(tmp->state) {
                tmp = tmp->next;
                continue;
            }
            printProductInformation(tmp);
            tmp = tmp->next;
        }
    }
    void markUnavaible(unsigned int prodctID) {
        if(ID < prodctID) {
            cout << endl << "ID nie ma takiego ID" << endl;
            return;
        }
        struct sProducts *tmp = productsList;
        while(tmp && tmp->productID != ID)
            tmp = tmp->next;
        tmp->state = false;
    }
    void deleteAllFromList() {
        struct sProducts *tmp = productsList;
        while(productsList) {
            productsList = productsList->next;
            free(tmp);
            tmp = productsList;
        }
    }
    void saveToFile(){
        file.open(filename, ios_base::out);
        struct sProducts *tmp = productsList->next;
        while(tmp) {
            file.write((char *)tmp, sizeof(struct sProducts) - sizeof(tmp));
            tmp = tmp->next;
        }
        file.close();
    }
    void readFromFile() {
        struct sProducts *listBegin = productsList;
        file.open(filename, ios_base::in);
        do {
            struct sProducts *tmp = new sProducts;
            file.read((char *)tmp, sizeof(struct sProducts) - sizeof(tmp));

            if(!tmp->productID) {
                delete tmp;
                break;
            }
            tmp->next = listBegin->next;
            listBegin->next = tmp;
            listBegin = listBegin->next;
        }while(!file.eof());
        file.close();
    }
    c_magazyn(const char *nameOfFile) {

        for(int i = 0; i < LENGTH; ++i)
            filename[i] = nameOfFile[i];
        productsList = new sProducts();
        ID = 0;
    }
};

int main(void) {

    c_magazyn Magazyn2k17("plikZapisOdczyt");
    Magazyn2k17.readFromFile();
//    Magazyn2k17.addNewProduct(true, "Mleko", 10, 1.99);
//    Magazyn2k17.addNewProduct(true, "Kawa", 35, 1.15);
//    Magazyn2k17.addNewProduct(false, "Cukier", 35, 1.55);
//    Magazyn2k17.addNewProduct(true, "Maka", 15, 1.45);
//    Magazyn2k17.addNewProduct(false, "Chleb", 20, 2.20);
//    Magazyn2k17.addNewProduct(true, "Bulki", 45, 0.40);


    Magazyn2k17.showAllProducts();
//    Magazyn2k17.showAllActiveProducts();
//    Magazyn2k17.showAllUnactiveProducts();
//
//    Magazyn2k17.markUnavaible(1);
//    Magazyn2k17.showAllActiveProducts();

//    Magazyn2k17.saveToFile();

    Magazyn2k17.deleteAllFromList();
}


//
//
//bool addToList(struct sProducts *first, struct sProducts *tmp)
//{
//    if(!tmp)
//        return true;
//
//    struct sProducts *q = first;
//    while(q->next)
//        q = q->next;
//
//    tmp->next = q->next;
//    q->next = tmp;
//
//    return false;
//}
//
//int checkLastID(char* name)
//{
//    int id;
//
//    FILE* fileID = fopen(name, "r");
//
//    fscanf(fileID, "%d", &id);
//
//    fclose(fileID);
//
//    return id;
//}
//
//void addProduct(struct sProducts *first, int *id)
//{
//    struct sProducts *tmp = (struct sProducts *)calloc(1, sizeof(struct sProducts));
//
//    tmp->productID = ++(*id);
//    printf("Wprowadz nazwe produktu: ");
//    fflush(stdin);
//    fgets(tmp->name, LENGTH, stdin);
//    printf("Wprowadz ilosc sztuk: ");
//    scanf("%d", &(tmp->amount));
//    printf("Wprowadz cene produktu: ");
//    scanf("%f", &(tmp->price));
//    tmp->state = true;
//
//    if(addToList(first, tmp))
//        free(tmp);
//}
//
//void saveLastIdInFile(char* name, int id)
//{
//    FILE* lastID = fopen(name, "w");
//
//    fprintf(lastID, "%d", id);
//
//    fclose(lastID);
//
//}
//
//void checkAmount(struct sProducts *first)
//{
//    first = first->next;
//    while(first){
//        if(first->amount < 20){
//            printf("\nIlosc %s wynosi %d ( dopuszczalna minimalna ilosc w magazynie to 20 )\n", first->name, first->amount);
//        }
//        first = first->next;
//    }
//}
//
//void loadList(struct sProducts *first, char *f_name)
//{
//    FILE* file = fopen(f_name, "r+b");
//    rewind(file);
//
//    struct sProducts *tmp = (struct sProducts *)malloc(sizeof(struct sProducts));
//
//    while(fread(tmp, 1, sizeof(struct sProducts), file) != EOF){
//        addToList(first, tmp);
//    }
//    fclose(file);
//}
//
//void expendProduct(struct sProducts *first, int id)
//{
//    int amount;
//
//    while(first){
//        if(first->productID == id){
//            printf("Jaka ilosc chcesz wydac?\n");
//            scanf("%d", &amount);
//            if(first->amount-amount < 0)
//                printf("Nie mozna wydac takiej ilosci poniewaz nie ma tylu sztuk na magazynie.\n");
//            else{
//                amount = first->amount - amount;
//                first->amount = amount;
//                break;
//            }
//        }
//        first = first->next;
//    }
//}
//
//void orderProduct(struct sProducts *first, int id)
//{
//    int amount;
//
//    while(first){
//        if(first->productID == id){
//            printf("Jaka ilosc chcesz zamowic?\n");
//            scanf("%d", &amount);
//            amount = amount + first->amount;
//            first->amount = amount;
//            break;
//        }
//        first = first->next;
//    }
//}
//
//int searchForProduct(struct sProducts *first)
//{
//    int id;
//    char product[LENGTH];
//
//    fflush(stdin);
//    fgets(product, LENGTH, stdin);
//
//    while(first){
//        if(strcmp(first->name, product) == 0 && first->state == true){
//            id = first->productID;
//
//            return id;
//        }else
//            first = first->next;
//    }
//
//    return -1;
//}
//
//void delProduct(struct sProducts *first, int id)
//{
//    while(first){
//        if(first->productID == id){
//            first->state = false;
//            break;
//        }
//        first = first->next;
//    }
//}
//
//void printAvalibleProducts(const struct sProducts *first)
//{
//    while(first){
//        if(first->state){
//            printf("ID:\t%d\n", first->productID);
//            printf("Nazwa:\t%s", first->name);
//            printf("Ilosc:\t%d\n", first->amount);
//            printf("Cena za sztuke:\t%f\n", first->price);
//        }
//        first = first->next;
//    }
//}
//
//void saveUpdatedList(struct sProducts *first, char *name)
//{
//    FILE *file = fopen(name, "w+b");
//
//    while(first){
//        if(first->state){
//            fwrite(&(first->productID), 1, sizeof(int), file);
//            fwrite(&(first->state), 1, sizeof(bool), file);
//            fwrite(first->name, 1, LENGTH, file);
//            fwrite(&(first->amount), 1, sizeof(int), file);
//            fwrite(&(first->price), 1, sizeof(float), file);
//        }
//        first = first->next;
//    }
//    fclose(file);
//}
//
//void removeList(struct sProducts **first)
//{
//    if (NULL == *first)
//        return;
//
//    do
//    {
//        struct sProducts *next = (*first)->next;
//        free(*first);
//        *first = next;
//    } while (*first != NULL);
//    *first = NULL;
//}
//
//void menu(void)
//{
//    printf("0. Wyjscie\n");
//    printf("1. Dodac produkt\n");
//    printf("2. Usunac produkt\n");
//    printf("3. Wyswietlic produkty\n");
//    printf("4. Zamow produkt\n");
//    printf("5. Wydaj produkt\n");
//    printf("6. Wyszukaj produkt\n");
//}
//
//short opt(void)
//{
//    printf("Wybierz co chcesz zrobic: ");
//    short opt;
//    while(1){
//        scanf("%hi", &opt);
//        printf("Wybrales: %hi\n", opt);
//        if(opt == 0)    break;
//        if(opt >= 1 && opt <= 6){
//            return opt;
//        }else{
//            printf("Cos poszlo nie tak! Wybierz ponownie: ");
//            continue;
//        }
//    }
//    exit(1);
//}
//
//int main(void)
//{
//    struct sProducts *first = (struct sProducts *)calloc(1, sizeof(struct sProducts));
//    int id;
//
//
//    //loadList(first, "products.txt");
//    checkAmount(first);
//
//    while(1){
//        menu();
//        short option = opt();
//
//        if(!option)
//            return -1;
//        else{
//            switch(option){
//                case 1:
//                    id = checkLastID("lastid.txt");
//                    addProduct(first, &id);
//                    saveLastIdInFile("lastid.txt", id);
//                    saveUpdatedList(first, "products.txt");
//                    break;
//                case 2:
//                    printf("Jakiego produkt chcesz usunac? ");
//                    id = searchForProduct(first);
//                    if(id > 0){
//                        delProduct(first, id);
//                        saveUpdatedList(first, "products.txt");
//                        printf("Usuniety produkt mial id: %d\n", id);
//                    }else
//                        printf("Nie mozna usunac produktu poniewaz go nie ma w bazie.\n");
//                    break;
//                case 3:
//                    //loadList(first, "products.txt");
//                    printAvalibleProducts(first);
//                    break;
//                case 4:
//                    //loadList(first, "products.txt");
//                    printf("Jaki produkt chcesz zamowic?\n");
//                    id = searchForProduct(first);
//                    if(id > 0){
//                        orderProduct(first, id);
//                        saveUpdatedList(first, "products.txt");
//                    }else
//                        printf("Nie mozna zamowic produktu poniewaz go nie ma w bazie.\n");
//                    break;
//                case 5:
//                    //loadList(first, "products.txt");
//                    printf("Jaki produkt chcesz wydac z magazynu?\n");
//                    id = searchForProduct(first);
//                    if(id > 0){
//                        expendProduct(first, id);
//                        saveUpdatedList(first, "products.txt");
//                    }else
//                        printf("Nie mozna wydac produktu poniewaz go nie ma w bazie.\n");
//                    checkAmount(first);
//                    break;
//                case 6:
//                    printf("Jakiego produktu szukasz? ");
//                    id = searchForProduct(first);
//                    if(id > 0)
//                        printf("Produkt ktorego szukasz ma id %d\n", id);
//                    else
//                        printf("Nie znaleziono produktu.\n");
//                    break;
//                default:
//                    printf("Wystapil blad, program zostanie zakonczony.");
//                    option = 0;
//            }
//        }
//    }
//    removeList(&first);
//    return 0;
//}
