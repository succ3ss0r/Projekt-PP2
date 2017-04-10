//
//
//  PLIK ZAWIERAJĄCY STRUKTURY POTRZEBNE DO DZIAŁANIA PROGRAMU
//
//


typedef enum {
    //enum potrzebny do wykluczania dystrybutorow, klientow i produktow zamiast ich usuwania

    false,
    true

} bool;

typedef struct {
    //struktura przeznaczona do trzymania informacji o dostawcach

    unsigned int distributorID;
    bool state;

    char *name;
    char *surname;
    char *address;
    short nip;
    char *phone;
    char *email;

    struct distributor* next;
} distributor;

typedef struct {
    //struktura przeznaczona do trzymania informacji o klientach

    unsigned int clientID;
    bool state;

    char *name;
    char *surname;
    char *phone;
    char *email;

    struct client* next;
} client;

typedef struct {
    //tablica przeznaczona do trzymania informacji o produktach

    unsigned int productID;
    bool state;

    char *name;
    unsigned int available;
    float price;

    struct product* next;
} product;

typedef struct {
    //struktura przechowujaca wskazniki na listy

    distributor* distributorsList;
    client* clientsList;
    product* productsList;

} listsPointers;

void listInitialize(listsPointers *lists){
    lists->distributorsList = NULL;
    lists->clientsList = NULL;
    lists->productsList = NULL;
}
