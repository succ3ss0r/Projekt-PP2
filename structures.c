//
//
//  PLIK ZAWIERAJĄCY STRUKTURY POTRZEBNE DO DZIAŁANIA PROGRAMU
//
//

typedef struct {
    //struktura przeznaczona do trzymania informacji o dostawcach
    char *name;
    char *address;
    short nip;
    char *phone;
    char *email;
} distributor;

typedef struct {
    //struktura przeznaczona do trzymania informacji o klientach
    char *name;
    char *surname;
    char *phone;
    char *email;
} client;

typedef struct {
    //tablica przeznaczona do trzymania informacji o produktach
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

void listInitialize(listsPointers *listy)
{
    listy->distributorsList = NULL;
    listy->clientsList = NULL;
    listy->productsList = NULL;
}
