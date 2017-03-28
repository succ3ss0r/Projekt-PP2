/*

    PLIK ZAWIERAJĄCY STRUKTURY POTRZEBNE DO DZIAŁANIA PROGRAMU

*/

struct listOfPointers {

    
};



struct listOfDistributors {
    //struktura przeznaczona do trzymania informacji o dostawcach
    char *name;
    char *address;
    short nip;
    char phone[11];
    char *email;
};

struct listOfClients {
    //struktura przeznaczona do trzymania informacji o klientach
    char name[LENGTH];
    char surname[LENGTH];
    char phone[11];
    char email[LENGTH];
};

struct productElement {
    //tablica przeznaczona do trzymania informacji o produktach
    char *name;
    unsigned int available;
    unsigned float price;    
};
