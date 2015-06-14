#include <QDebug>
#include "osoba.h"
#include "przedmiot.h"
#include "rok.h"
#include "silnik.h"
#include "interfejs.h"


int main(int argc, char *argv[])
{
    Interfejs* interfejs = new Interfejs;
    bool koniec;
    do{
        koniec = interfejs->runMenuGlowne();
    }while(!koniec);

    return 0;
}
