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
<<<<<<< HEAD

    unsigned int distributorID;
    bool state;


=======
>>>>>>> 659b623bd0c91ed1840a38cfed3f37e458c0af34
    char *name;
    char *address;
    short nip;
    char *phone;
    char *email;
} distributor;

typedef struct {
    //struktura przeznaczona do trzymania informacji o klientach
<<<<<<< HEAD

    unsigned int clientID;
    bool state;


=======
>>>>>>> 659b623bd0c91ed1840a38cfed3f37e458c0af34
    char *name;
    char *surname;
    char *phone;
    char *email;


} client;

typedef struct {
    //tablica przeznaczona do trzymania informacji o produktach
<<<<<<< HEAD

    unsigned int productID;
    bool state;


=======
>>>>>>> 659b623bd0c91ed1840a38cfed3f37e458c0af34
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
