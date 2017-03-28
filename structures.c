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
    char *address;
    short nip;
    char *phone;
    char *email;
} distributor;

typedef struct {
    //struktura przeznaczona do trzymania informacji o klientach

    unsigned int clientID;
    bool state;


    char *name;
    char *surname;
    char *phone;
    char *email;


} client;

typedef struct {
    //tablica przeznaczona do trzymania informacji o produktach

    unsigned int productID;
    bool state;


    char *name;
    unsigned int available;
    float price;
} productElement;

typedef struct {
    //struktura przechowujaca wskazniki na listy

    distributor* distributorsList;
    client* clientsList;
    productElement* productsList;
} listsPointers;

void listInitialize(listsPointers *lists) {
    //FUNKCJA INICJUJĄCA STRUKTURĘ PUSTYCH WSKAŹNIKÓW NA LISTY
    lists->distributorsList = NULL;
    lists->clientsList = NULL;
    lists->productsList = NULL;
}
