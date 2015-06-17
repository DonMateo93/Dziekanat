#include "interfejs.h"
#include <stdlib.h>

using namespace std;

bool Interfejs::runMenuGlowne()
{
    QStringList lista;
    lista.clear();
    lista << "DODAJ NOWY ROK AKADEMICKI";
    lista << "PRZEGLADAJ/EDYTUJ LATA AKADEMICKIE";
    lista << "DODAJ SZABLON PRZEDMIOTU";
    lista << "USUN SZABLON PRZEDMIOTU";
    lista << "DODAJ PROWADZACEGO";
    lista << "USUN PROWADZACEGO";
    lista << "EDYTUJ PROWADZACEGO";
    lista << "DODAJ STUDENTA";
    lista << "USUN STUDENTA";
    lista << "EDYTUJ STUDENTA";
    lista << "WYJDZ";

    QString pom;
    for(int i = 0; i < lista.size(); i++){
        pom = QString::number(i+1) + "." + lista.at(i);
        lista.replace(i,pom);
    }

    qDebug().noquote() << lista.join("\n") << endl;
    int wybor;
    if(lista.size() != 0){
        wybor = pobierzIntZZakresu( lista.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
        switch(wybor)
        {
        case 1:
            system("CLS");
            dodajRok();
            break;
        case 2:
            system("CLS");
            edycjaLataAkademickie();
            break;
        case 3:
            system("CLS");
            dodajSzablonPrzedmiotu();
            break;
        case 4:
            system("CLS");
            ususnSzablonPrzedmiotu();
            break;
        case 5:
            system("CLS");
            dodajPracownika();
            break;
        case 6:
            system("CLS");
            usunPracownika();
            break;
        case 7:
            system("CLS");
            edytujPraownika();
            break;
        case 8:
            system("CLS");
            dodajStudenta();
            break;
        case 9:
            system("CLS");
            usunStudenta();
            break;
        case 10:
            system("CLS");
            edytujStudenta();
            break;
        }
    }

    if(wybor == lista.size())
        return true;
    else
        return false;
}

void Interfejs::dodajStudenta()
{
    Student* student = tworzStudenta();
    if(!silnik->czyJestStudentOIndeksie(student->getAlbum()))
        silnik->adStudent(student);
    else
        qDebug().noquote() <<"STUDENT O TAKIM INDEKSIE JUŻ ISTNIEJE!"<< endl;
}

void Interfejs::usunStudenta()
{
    bool powrot = false;
    while(!powrot){
        QStringList studenci = silnik->getStudenci();
        int wybor = wydrukListaWybor(studenci,"WYBIERZ PRACOWNIKA DO USUNIECIA",1);
        if(wybor == studenci.size())
            powrot = true;
        else{
            silnik->usunStudentAt(wybor-1);
        }
    }
}

void Interfejs::edytujStudenta()
{
    bool powrot = false;
    while(!powrot){
        QStringList studenci = silnik->getStudenci();
        int wybor = wydrukListaWybor(studenci,"WYBIERZ PRACOWNIKA DO EDYCJI",1);
        if(wybor == studenci.size())
            powrot = true;
        else{
            Student* student = tworzStudenta();
            silnik->zamienStudentAt(wybor-1,student);
        }
    }
}

void Interfejs::dodajRok()
{
    QDate start1,end1,start2,end2;
    bool dobrze2 = false;

    bool Automatycznie = pytanieTakNie("CZY CHCESZ DODAĆ NOWY ROK AUTOMATYCZNIE");
    if(Automatycznie){
        silnik->dodajNowyRokAutomatycznie();
    }else{
        while(!dobrze2){

            bool dobrze = false;
            qDebug().noquote() <<"UZUPELNIJ DANE DOTYCZACE SEMESTRU PIERWSZEGO:"<< endl;
            while(!dobrze)
            {
                start1 = pobierzDate("PODAJ DATE ROZPOCZECIA SEMESTRU I");
                end1 = pobierzDate("PODAJ DATE ZAKONCZENIA SEMESTRU I");
                if(start1 > end1)
                    qDebug().noquote() <<"DATA ROZPOCZECIA NIE MOZE BYC WIEKSZA NIZ ZAKONCZENIA!"<<endl;
                else
                    dobrze = true;
            }

            dobrze = false;
            qDebug().noquote() <<"UZUPELNIJ DANE DOTYCZACE SEMESTRU DRUGIEGO:"<<endl;
            while(!dobrze)
            {
                start2 = pobierzDate("PODAJ DATE ROZPOCZECIA SEMESTRU II");
                end2 = pobierzDate("PODAJ DATE ZAKONCZENIA SEMESTRU II");
                if(start2 > end2)
                    qDebug().noquote() <<"DATA ROZPOCZECIA NIE MOZE BYC WIEKSZA NIZ ZAKONCZENIA!"<<endl;
                else
                    dobrze = true;
            }

            if(start2 < end1)
                qDebug().noquote() <<"SEMESTR PIERWSZY MUSI SIE SKONCZYC ZANIM ZACZNIE SIE NASTEPNY!"<<endl;
            else if(start2.year() - start1.year() >= 2)
                qDebug().noquote() <<"ZA DLUGA PRZERWA POMIEDZY SEMESTRAMI!"<<endl;
            else
                dobrze2 = true;
        }

        silnik->addNowyRok(start1,end1,start2,end2);
    }


}

void Interfejs::dodajSzablonPrzedmiotu()
{

    QTextStream s(stdin);
    QString nazwa,opis,skrot;
    bool ok = false;
    while(!ok){
        qDebug().noquote()<<"PODAJ NAZWE(MIN. 3 LITERY)";
        nazwa = s.readLine();
        if(nazwa.size()>2 && nazwa != "" && !silnik->czyJestPrzedmiotONazwie(nazwa))
            ok = true;
        else
            qDebug().noquote()<<"BLAD! NAZWA JUZ WYSTAPILA LUB JEST ZA KROTKA";
    }

    ok = false;
    while(!ok){
        qDebug().noquote()<<"PODAJ SKROT(MIN. 2 LITERY)";
        skrot = s.readLine();
        if(skrot.size()>1 && skrot != "")
            ok = true;
        else
            qDebug().noquote()<<"BLAD!";
    }

    ok = false;
    while(!ok){
        qDebug().noquote()<<"PODAJ OPIS";
        opis = s.readLine();
        if(opis != "")
            ok = true;
        else
            qDebug().noquote()<<"BLAD!";
    }

    int ects = pobierzIntZZakresu(15,0,"PODAJ LICZBĘ ECTS(MAX 15)");

    QList<SkladowaPrzedmiotu> lista;

    if(pytanieTakNie("CZY PRZEDMIOT MA LABORATORIUM"))
        lista<< Laboratorium;
    if(pytanieTakNie("CZY PRZEDMIOT MA EGZAMIN"))
        lista<< Egzamin;
    if(pytanieTakNie("CZY PRZEDMIOT MA PROJEKT"))
        lista<< Projekt;
    if(pytanieTakNie("CZY PRZEDMIOT MA CWICZENIA"))
        lista<< Cwiczenia;
    if(pytanieTakNie("CZY PRZEDMIOT MA WYKLAD"))
        lista<< Wyklad;

    Przedmiot* przedmiot = new Przedmiot(nazwa,opis,skrot,lista,ects);
    silnik->addPrzedmiot(przedmiot);

    system("CLS");
    qDebug().noquote()<<"SZABLON PRZEDMIOTU DODANY";
    s.readLine();
}

void Interfejs::dodajPracownika()
{
    Pracownik* pracownik = tworzEdytujPracownika();
    if(!silnik->czyJestPracownikOID(pracownik->getID())){
        silnik->adPracownik(pracownik);
    }
}

void Interfejs::usunPracownika()
{
    bool powrot = false;
    while(!powrot){
        QStringList pracownicy = silnik->getPracownicy();
        int wybor = wydrukListaWybor(pracownicy,"WYBIERZ PRACOWNIKA DO USUNIECIA",1);
        if(wybor == pracownicy.size())
            powrot = true;
        else{
            silnik->usunPracownikAt(wybor-1);
        }
    }
}

void Interfejs::edytujPraownika()
{
    bool powrot = false;
    while(!powrot){
        QStringList pracownicy = silnik->getPracownicy();
        int wybor = wydrukListaWybor(pracownicy,"WYBIERZ PRACOWNIKA DO EDYCJI",1);
        if(wybor == pracownicy.size())
            powrot = true;
        else{
            Pracownik* pracownik = tworzEdytujPracownika();
            silnik->zamienPracownikAt(wybor-1,pracownik);
        }
    }
}

void Interfejs::ususnSzablonPrzedmiotu()
{

    bool powrot = false;
    while(!powrot){
        QStringList przedmioty = silnik->getPrzedmioty();
        int wybor = wydrukListaWybor(przedmioty,"WYBIERZ SZABLON DO USUNIECIA",1);
        if(wybor == przedmioty.size())
            powrot = true;
        else{
            silnik->usunPrzedmiotAt(wybor-1);
        }
    }
}

void Interfejs::edycjaLataAkademickie()
{
    int wybor;
    QTextStream s(stdin);
    bool powrot = false;
    while(!powrot){
        system("CLS");
        QStringList lista = silnik->getLataAkademickie();
        for(int i = 0; i < lista.size(); i ++){
            lista.replace(i,QString::number(i+1)+"."+lista.at(i));
        }

        qDebug().noquote()<<"DOSTEPNE LATA AKADEMICKIE:";
        if(!lista.isEmpty()){
            qDebug().noquote() <<lista.join("\n")<< endl;
            qDebug().noquote() <<QString::number(lista.size()+1) + ".POWROT"<< endl;
            wybor = pobierzIntZZakresu(lista.size()+1,1,"WYBIERZ ROK AKADEMICKI DO PRZEGLĄDANIA/EDYCJI:");
            if(wybor == lista.size()+1)
                powrot = true;
            else{
                wybor--;
                runMenuRokAkademicki(wybor);
            }
        }
        else{
            qDebug().noquote() <<"BRAK WCZYTANYCH DANYCH \n NACISNIJ ENTER ABY POWROCIC";
            powrot = true;
            s.readLine();
        }
    }
}

void Interfejs::runMenuRokAkademicki(int at)
{
    QTextStream s(stdin);
    bool powrot = false;

    while(!powrot){
        system("CLS");
        qDebug().noquote() <<"------------------------------------";
        QString info = silnik->getInfoRokAt(at);
        qDebug().noquote() << info;
        qDebug().noquote() <<"------------------------------------";

        QStringList lista;
        lista.clear();
        lista << "PRZEGLADAJ/EDYTUJ GRUPY DZIEKANSKIE";
        lista << "PRZEGLADAJ/EDYTUJ PRACOWNIKOW";
        lista << "PRZEGLADAJ/EDYTUJ PRZEDMIOTY";
        lista << "POWROT";

        QString pom;
        for(int i = 0; i < lista.size(); i++){
            pom = QString::number(i+1) + "." + lista.at(i);
            lista.replace(i,pom);
        }

        qDebug().noquote() << lista.join("\n") << endl;

        int wybor;
        if(lista.size() != 0){
            wybor = pobierzIntZZakresu( lista.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
            switch(wybor)
            {
            case 1:
                system("CLS");
                runMenuGrupy(silnik->getRokAt(at));
                break;
            case 2:
                system("CLS");
                runMenuPracownicy(silnik->getRokAt(at));
                break;
            case 3:
                system("CLS");
                runMenuPrzedmioty(silnik->getRokAt(at));
                break;
            case 4:
                powrot = true;
                break;
            }
        }
    }
}

void Interfejs::runMenuGrupy(Rok* rok)
{
    if(rok != NULL){
        bool powrot = false;
        while(!powrot){
            QStringList grupy = rok->getGrupy();
            qDebug().noquote() << "GRUPY W ROKU AKADEMICKIM " + rok->getRok();
            QString pom;
            for(int j = 0; j < grupy.size(); j++){
                pom = QString::number(j+1) + "." + grupy.at(j);
                grupy.replace(j,pom);
            }
            qDebug().noquote() << grupy.join("\n");

            QStringList lista;
            lista.clear();
            lista << "PRZEGLADAJ/EDYTUJ GRUPE DZIEKANSKA";
            lista << "DODAJ GRUPE";
            lista << "USUN GRUPE";
            lista << "POWROT";


            for(int i = 0; i < lista.size(); i++){
                pom = QString::number(i+1) + "." + lista.at(i);
                lista.replace(i,pom);
            }

            qDebug().noquote() << lista.join("\n") << endl;

            int wybor;
            if(lista.size() != 0){
                wybor = pobierzIntZZakresu( lista.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
                switch(wybor)
                {
                case 1:
                    system("CLS");
                    grupaEdit(rok);
                    break;
                case 2:
                    system("CLS");
                    grupaAdd(rok);
                    break;
                case 3:
                    system("CLS");
                    grupaDelete(rok);
                    break;
                case 4:
                    powrot = true;
                    break;
                }
            }
        }

    }else{
        qDebug().noquote() << "BLAD. BRAK REFERENCJI";
    }
}

void Interfejs::grupaEdit(Rok *rok)
{
    QTextStream s(stdin);
    system("CLS");
    QStringList grupy = rok->getGrupy();
    qDebug().noquote() << "GRUPY W ROKU AKADEMICKIM " + rok->getRok();
    QString pom;
    for(int j = 0; j < grupy.size(); j++){
        pom = QString::number(j+1) + "." + grupy.at(j);
        grupy.replace(j,pom);
    }

    qDebug().noquote() << "KTORA Z GRUP EDYTOWAC?";
    qDebug().noquote() << grupy.join("\n");
    qDebug().noquote() << QString::number(grupy.size()+1) + ".POWROT";
    int wybor = pobierzIntZZakresu( grupy.size()+1, 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
    if(wybor == grupy.size()+1){
        return;
    }else{
        Grupa* grupa = rok->getGrupaAt(wybor-1);
        if(grupa != NULL){
            bool powrot = false;
            while(!powrot){
                system("CLS");
                qDebug().noquote() <<"------------------------------------";
                qDebug().noquote() << grupa->getInfo();
                qDebug().noquote() <<"------------------------------------";

                QStringList lista;
                lista.clear();
                lista << "PRZEGLADAJ STUDENTOW";
                lista << "USUN STUDENTA";
                lista << "DODAJ STUDENTA";
                lista << "ZARZADZAJ KONTEM STUDENTOW";
                lista << "EDYTUJ PRZEDMIOTY";
                lista << "PRZYPISZ WSZYSTKIM STUDENTOM DOSTEPNE PRZEDMIOTY";
                lista << "POWROT";

                QStringList pomocnicza;
                pomocnicza.clear();
                int wybor2 = wydrukListaWybor(lista,"WYBIERZ OPCJE");

                switch(wybor2)
                {
                case 1:
                    system("CLS");
                    qDebug().noquote() << grupa->getID();

                    pomocnicza = grupa->getStudList();
                    for(int k = 0; k < pomocnicza.size(); k++){
                        pom = QString::number(k+1) + "." + pomocnicza.at(k);
                        pomocnicza.replace(k,pom);
                    }

                    qDebug().noquote() << pomocnicza.join("\n");
                    s.readLine();

                    break;
                case 2:
                    system("CLS");
                    qDebug().noquote() << grupa->getID();

                    pomocnicza = grupa->getStudList();
                    for(int k = 0; k < pomocnicza.size(); k++){
                        pom = QString::number(k+1) + "." + pomocnicza.at(k);
                        pomocnicza.replace(k,pom);
                    }

                    qDebug().noquote() << pomocnicza.join("\n");
                    qDebug().noquote() << "KTOREGO USUNAC?";
                    qDebug().noquote() << QString::number(pomocnicza.size() + 1) + ".POWROT";
                    wybor2 = pobierzIntZZakresu( pomocnicza.size()+1, 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
                    if(wybor2 <= pomocnicza.size()){
                        grupa->usunStudentaAt(wybor2);
                    }
                    break;
                case 3:
                    dodajStudentaDoGrupy(grupa);
                    break;
                case 4:
                    system("CLS");
                    zarzadzajKontemStudentow(grupa);
                    break;
                case 5:
                    system("CLS");
                    przedmiotyGrupyEdit(grupa);
                    break;
                case 6:
                    system("CLS");
                    grupa->przypiszStudentomPrzedmioty();
                    break;
                case 7:
                    system("CLS");
                    powrot = true;
                    break;
                }
            }
        }
    }
}

void Interfejs::zarzadzajKontemStudentow(Grupa *grupa)
{
    if(grupa != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList studenci = grupa->getStudList();

            int wybor = wydrukListaWybor(studenci,"WYBIERZ STUDENTA",1);

            if(wybor == studenci.size()){
                powrot = true;
            }else{
                zarzadzajKontemStudenta(grupa->getStudentAt(wybor-1));
            }
        }
    }
}

void Interfejs::zarzadzajKontemStudenta(Student *student)
{
    QTextStream s(stdin);
    if(student != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList lista;
            lista.clear();
            lista << "PRZYPISZ PROWADZACEGO DO SKLADOWYCH PRZEDMIOTU";
            lista << "WPISZ OCENY";
            lista << "PRZEGLADAJ KARTE OCEN";

            int wybor = wydrukListaWybor(lista,"WYBIERZ OPCJE",1);

            if(wybor == lista.size()){
                powrot = true;
            }else{
                switch (wybor) {
                case 1:
                    system("CLS");
                    przypiszProwadzacegoDoSkladowej(student);
                    break;
                case 2:
                    system("CLS");

                    break;
                case 3:
                    system("CLS");
                    qDebug().noquote() << student->getKartaOcen();
                    s.readLine();
                    break;
                }
            }
        }
    }
}

void Interfejs::wpiszStudentowiOcene(Student *student)
{
    if(student != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList przedmioty = student->getPrzedmioty();

            int wybor = wydrukListaWybor(przedmioty,"WYBIERZ PRZEDMIOT",1);

            if(wybor == przedmioty.size()){
                powrot = true;
            }else{
                QStringList skladowe = student->getSkladowePrzedmiotAt(wybor - 1);
                skladowe << "KONCOWA";
                int wybor2 = wydrukListaWybor(skladowe,"WYBIERZ SKLADOWA DO PRZYPISANIA OCENY");
                Ocena ocena = pobierzOcene();
                if(wybor2 == skladowe.size()){
                    student->setKoncowaAt(ocena,wybor - 1);
                }else {
                    student->przypiszOcene(ocena,wybor - 1,wybor2 - 1);
                }
            }
        }
    }
}

void Interfejs::przypiszProwadzacegoDoSkladowej(Student *student)
{

    if(student != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList przedmioty = student->getPrzedmioty();

            int wybor = wydrukListaWybor(przedmioty,"WYBIERZ PRZEDMIOT",1);

            if(wybor == przedmioty.size()){
                powrot = true;
            }else{
                QStringList skladowe = student->getSkladowePrzedmiotAt(wybor - 1);
                int wybor2 = wydrukListaWybor(skladowe,"WYBIERZ SKLADOWA DO PRZYPISANIA PROWADZACEGO");
                QStringList pracownicy = student->getGrupa()->getRok()->getPracownicy();
                int wybor3 = wydrukListaWybor(pracownicy,"WYBIERZ PROWADZACEGO");
                student->przypiszProwadzacego(student->getGrupa()->getRok()->getPracownikAt(wybor3-1),wybor-1,wybor2-1);
            }
        }
    }
}

void Interfejs::grupaDelete(Rok *rok)
{
    if(rok != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList grupy = rok->getGrupy();

            int wybor = wydrukListaWybor(grupy,"WYBIERZ GRUPE DO USUNIECIA",1);

            if(wybor == grupy.size()){
                powrot = true;
            }else{
                rok->usunGrupaAt(wybor - 1);
            }
        }
    }
}

void Interfejs::grupaAdd(Rok *rok)
{
    tworzGrupe(rok);
}

void Interfejs::runMenuPracownicy(Rok* rok)
{
    if(rok != NULL){
        bool powrot = false;
        while(!powrot){
            QStringList grupy = rok->getPracownicy();
            qDebug().noquote() << "PRACOWNICY W ROKU AKADEMICKIM " + rok->getRok();
            qDebug().noquote() << grupy.join("\n");

            QStringList lista;
            lista.clear();
            lista << "PRZEGLADAJ PRACOWNIKOW";
            lista << "DODAJ PRACOWNIKA";
            lista << "USUN PRACOWNIKA";
            lista << "POWROT";

            QString pom;
            for(int i = 0; i < lista.size(); i++){
                pom = QString::number(i+1) + "." + lista.at(i);
                lista.replace(i,pom);
            }

            qDebug().noquote() << lista.join("\n") << endl;

            int wybor;
            if(lista.size() != 0){
                wybor = pobierzIntZZakresu( lista.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
                switch(wybor)
                {
                case 1:
                    system("CLS");
                    przegladPracownicyRok(rok);
                    break;
                case 2:
                    system("CLS");
                    dodajPracownikaDoRoku(rok);
                    break;
                case 3:
                    system("CLS");
                    usunPracownikaZRoku(rok);
                    break;
                case 4:
                    powrot = true;
                    break;
                }
            }
        }
    }else{
        qDebug().noquote() << "BLAD. BRAK REFERENCJI";
    }
}

void Interfejs::przegladPracownicyRok(Rok *rok)
{
    if(rok != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList pracownicy = rok->getPracownicy();

            int wybor = wydrukListaWybor(pracownicy,"WYBIERZ PRACOWNIKA DO PRZEGLADU",1);

            if(wybor == pracownicy.size()){
                powrot = true;
            }else{
                qDebug().noquote() << rok->getPracownikAt(wybor - 1)->getInfo(1);
                QTextStream s(stdin);
                s.readLine();
            }
        }
    }
}

void Interfejs::usunPracownikaZRoku(Rok *rok)
{
    if(rok != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList pracownicy = rok->getPracownicy();

            int wybor = wydrukListaWybor(pracownicy,"WYBIERZ PRACOWNIKA DO USUNIECIA",1);

            if(wybor == pracownicy.size()){
                powrot = true;
            }else{
                if(rok->czyPracownikAtPracuje(wybor - 1)){
                    qDebug().noquote() << "PRACOWNIK MA PRZYDZIELONE PRZEDMIOTY. NIE MOŻNA USUNĄĆ";
                    QTextStream s(stdin);
                    s.readLine();
                }else{
                    rok->usunPracownikAt(wybor - 1);
                }
            }
        }
    }
}

void Interfejs::dodajPracownikaDoRoku(Rok *rok)
{
    if(rok != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList pracownicy = silnik->getPracownicy();

            int wybor = wydrukListaWybor(pracownicy,"WYBIERZ PRACOWNIKA DO DODANIA",1);

            if(wybor == pracownicy.size()){
                powrot = true;
            }else{
                if(!rok->czyJestPracownik(silnik->getPracownikAt(wybor - 1))){
                    rok->adPracownik(silnik->getPracownikAt(wybor - 1));
                }else{

                    qDebug().noquote() << "PRACOWNIK JUŻ PRACUJE W ROKU AKADEMICKIM " + rok->getRok();
                    QTextStream s(stdin);
                    s.readLine();
                }
            }
        }
    }
}

void Interfejs::runMenuPrzedmioty(Rok* rok)
{
    if(rok != NULL){

        int wybor = pobierzIntZZakresu(2,1,"KTORY SEMESTR CHCESZ PRZEGLADAC?");
        QString pomagier;
        if(wybor == 1)
            pomagier = "I";
        else
            pomagier = "II";

        bool powrot = false;
        while(!powrot){
            Semestr* sem = rok->getSem(wybor);

            QStringList przedmioty = sem->getInfoPrzedmioty();
            qDebug().noquote() << "PRZEDMIOTY W SEMESTRZE " + pomagier + " " + rok->getRok();
            qDebug().noquote() << przedmioty.join("\n");

            QStringList lista;
            lista.clear();
            lista << "PRZEGLADAJ/EDYTUJ PRZEDMIOT";
            lista << "DODAJ PRZEDMIOT";
            lista << "USUN PRZEDMIOT";
            lista << "POWROT";

            QString pom;
            for(int i = 0; i < lista.size(); i++){
                pom = QString::number(i+1) + "." + lista.at(i);
                lista.replace(i,pom);
            }

            qDebug().noquote() << lista.join("\n") << endl;

            int wybor;
            if(lista.size() != 0){
                wybor = pobierzIntZZakresu( lista.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
                switch(wybor)
                {
                case 1:
                    system("CLS");
                    przedmiotyRokEdit(rok);
                    break;
                case 2:
                    system("CLS");
                    dodajPrzedmiotDoRoku(rok);
                    break;
                case 3:
                    system("CLS");
                    usunPrzedmiotZroku(rok);
                    break;
                case 4:
                    powrot = true;
                    break;
                }
            }
        }
    }else{
        qDebug().noquote() << "BLAD. BRAK REFERENCJI";
    }
}

void Interfejs::przedmiotyRokEdit(Rok *rok)
{
    if(rok != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList przedmioty = rok->getPrzedmioty();
            wydrukListyZNumeracja(przedmioty,"EDYCJE PRZEDMIOTOW W ROKU AKADEMICKIM" + rok->getRok(),1);

            int wybor = pobierzIntZZakresu( przedmioty.size(), 1,"WYBIERZ PRZEDMIOT");

            if(wybor == przedmioty.size()){
                powrot = true;
            }else{
                EdycjaPrzedmotu* przedmiot = rok->getPrzedmiotAt(wybor -1);
                qDebug().noquote() << przedmiot->getInfo(1);
                if(pytanieTakNie("CZY CHCESZ ZMIENIC PROWADZACEGO?")){
                    QStringList pracownicy = rok->getPracownicy();
                    int wybor2 = wydrukListaWybor(pracownicy,"WYBIERZ NOWEGO PROWADZACEGO" + rok->getRok(),1);
                    if(wybor2 < pracownicy.size()){
                        przedmiot->setProwadzacy(rok->getPracownikAt(wybor2-1));
                    }
                }

                system("CLS");
                qDebug().noquote() << "INNE OPCJE MOŻESZ EYDTOWAĆ TYLKO W SZABLONACH PRZEDMIOTU";
                QTextStream s(stdin);
                s.readLine();
            }
        }
    }
}

void Interfejs::dodajPrzedmiotDoRoku(Rok *rok)
{
    if(rok != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList przedmioty = silnik->getPrzedmioty();

            int wybor = wydrukListaWybor(przedmioty,"WYBIERZ PRZEDMIOT",1);

            if(wybor == przedmioty.size()){
                powrot = true;
            }else{
                Przedmiot* przedmiot = silnik->getPrzedmiotAt(wybor - 1);
                int wybor2 = pobierzIntZZakresu(2,1,"KTORY SEMESTR? \n 1.PIERWSZY \n 2.DRUGI");
                QStringList prowadzacy = rok->getPracownicy();
                int wybor3 = wydrukListaWybor(prowadzacy,"WYBIERZ PRZEDMIOT");
                Pracownik* pracownik = rok->getPracownikAt(wybor3 - 1);
                if(pracownik != NULL && przedmiot != NULL){
                    rok->dodajEdycjePrzedmiotu(przedmiot,pracownik,wybor2);
                }
            }
        }
    }
}

void Interfejs::usunPrzedmiotZroku(Rok *rok)
{
    if(rok != NULL){
        system("CLS");
        bool powrot = false;
        while(!powrot){
            QStringList przedmioty = rok->getPrzedmioty();

            int wybor = wydrukListaWybor(przedmioty,"WYBIERZ PRZEDMIOT",1);

            if(wybor == przedmioty.size()){
                powrot = true;
            }else{
                rok->usunPrzedmiotAt(wybor - 1);
            }
        }
    }
}

void Interfejs::przedmiotyGrupyEdit(Grupa *grupa)
{
    if(grupa != NULL){
        bool powrot = false;
        while(!powrot){

            QString pomoc;
            QStringList przedmioty = grupa->getPrzedmList();
            for(int j = 0; j < przedmioty.size(); j++){
                pomoc = QString::number(j+1) + "." + przedmioty.at(j);
                przedmioty.replace(j,pomoc);
            }

            qDebug().noquote() << "PRZEDMIOTY W GRUPIE " + grupa->getID();
            qDebug().noquote() << przedmioty.join("\n");

            QStringList lista;
            lista.clear();
            lista << "DODAJ PRZEDMIOT";
            lista << "USUN PRZEDMIOT";
            lista << "POWROT";

            QString pom;
            for(int i = 0; i < lista.size(); i++){
                pom = QString::number(i+1) + "." + lista.at(i);
                lista.replace(i,pom);
            }

            qDebug().noquote() << lista.join("\n") << endl;

            int wybor;
            if(lista.size() != 0){
                wybor = pobierzIntZZakresu( lista.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");
                switch(wybor)
                {
                case 1:
                    system("CLS");
                    dodajPrzedmiotDoGrupy(grupa);
                    break;
                case 2:
                    system("CLS");
                    usunPrzedmiotZGrupy(grupa);
                    break;
                case 3:
                    system("CLS");
                    powrot = true;
                    break;
                }
            }
        }
    }else
        qDebug().noquote() << "BLAD. BRAK REFERENCJI";
}

void Interfejs::dodajPrzedmiotDoGrupy(Grupa *grupa)
{
    bool powrot = false;
    while(!powrot){
        QStringList przedmioty = (grupa->getRok())->getPrzedmioty();

        QString pom;
        for(int k = 0; k < przedmioty.size(); k++){
            pom = QString::number(k+1) + "." + przedmioty.at(k);
            przedmioty.replace(k,pom);
        }
        przedmioty << QString::number(przedmioty.size()+1) + ".POWROT";

        qDebug().noquote() << "WYBIERZ PRZEDMIOT DO DODANIA: ";
        qDebug().noquote() << przedmioty.join("\n");

        int wybor = pobierzIntZZakresu( przedmioty.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");

        if(wybor == przedmioty.size()){
            powrot = true;
        }else{
            if(!grupa->czyJestPrzedmiot(grupa->getRok()->getPrzedmiotAt(wybor - 1)))
                grupa->addPrzedmiot(grupa->getRok()->getPrzedmiotAt(wybor - 1));
        }
    }

}

void Interfejs::dodajStudentaDoGrupy(Grupa *grupa)
{
    bool powrot = false;
    while(!powrot){
        QStringList studenci = silnik->getNieprzydzieleniStudenci();

        int wybor = wydrukListaWybor(studenci,"WYBIERZ STUDENTA DO DODANIA",1);

        if(wybor == studenci.size()){
            powrot = true;
        }else{
            grupa->addStudent(silnik->getNieprzydzielonyStudentAt(wybor-1));
        }
    }
}

void Interfejs::usunPrzedmiotZGrupy(Grupa *grupa)
{
    bool powrot = false;
    while(!powrot){
        QStringList przedmioty = grupa->getPrzedmList();

        QString pom;
        for(int k = 0; k < przedmioty.size(); k++){
            pom = QString::number(k+1) + "." + przedmioty.at(k);
            przedmioty.replace(k,pom);
        }
        przedmioty << QString::number(przedmioty.size()+1) + ".POWROT";

        qDebug().noquote() << "WYBIERZ PRZEDMIOT DO USUNIECIA";
        qDebug().noquote() << przedmioty.join("\n");

        int wybor = pobierzIntZZakresu( przedmioty.size(), 1,"WYBIERZ OPCJE WYBIERAJĄC ODPOWIEDNI NUMER I NACISKAJĄC ENTER");

        if(wybor == przedmioty.size()){
            powrot = true;
        }else{
            bool czy = pytanieTakNie("CZY USUNAC TEN PRZEDMIOT TAKZE DLA STUDENTOW TEJ GRUPY?");
            grupa->usunPrzedmiotAt(wybor - 1, czy);
        }
    }
}

int Interfejs::pobierzIntZZakresu(int gorny, int dolny, QString text = "")
{
    bool ok = false;
    int zwrot;
    QTextStream s(stdin);
    QString pobierana;
    do{
        if(text != "")
            qDebug().noquote()<<text<<endl;
        pobierana = s.readLine();
        if(pobierana.size() != 0){
            bool pom1 = true;
            for(int i = 0; i < pobierana.size(); i ++){
                if(pobierana.at(i)< '0' || pobierana.at(i)> '9')
                    pom1 = false;
            }

            if(pom1){
                zwrot = pobierana.toInt();
                if(zwrot >= dolny && zwrot <= gorny){
                    ok = true;
                }
            }
        }
        if(!ok)
            qDebug().noquote()<<"BLAD. WPROWADZ LICZBE PONOWNIE"<<endl;
    }while(!ok);

    system("CLS");
    return zwrot;
}

bool Interfejs::pytanieTakNie(QString text)
{
    qDebug().noquote()<<text;
    qDebug().noquote()<<"0.NIE";
    qDebug().noquote()<<"1.TAK";

    int wybor = pobierzIntZZakresu(1,0);
    if(wybor == 1){
        return true;
    }else{
        return false;
    }
}

void Interfejs::wydrukListyZNumeracja(QStringList &lista, QString text, bool dodajPowrot)
{
    QString pom;
    for(int k = 0; k < lista.size(); k++){
        pom = QString::number(k+1) + "." + lista.at(k);
        lista.replace(k,pom);
    }

    if(dodajPowrot){
        lista << QString::number(lista.size()+1) + ".POWROT";
    }

    qDebug().noquote() << text;
    qDebug().noquote() << lista.join("\n");
}

int Interfejs::wydrukListaWybor(QStringList &lista, QString text, bool dodajPowrot)
{
    QString pom;
    for(int k = 0; k < lista.size(); k++){
        pom = QString::number(k+1) + "." + lista.at(k);
        lista.replace(k,pom);
    }

    if(dodajPowrot){
        lista << QString::number(lista.size()+1) + ".POWROT";
    }

    qDebug().noquote() << text;
    qDebug().noquote() << lista.join("\n");

    return pobierzIntZZakresu(lista.size(),1);
}

Student *Interfejs::tworzStudenta(Grupa* grupa)
{
    QTextStream s(stdin);

    qDebug().noquote()<<"PODAJ IMIE";
    QString imie = s.readLine();

    qDebug().noquote()<<"PODAJ NAZWISKO";
    QString nazwisko = s.readLine();

    qDebug().noquote()<<"PODAJ ADRES";
    QString adres = s.readLine();

    QDate dataUR = pobierzDate("PODAJ DATE URODZENIA");

    qDebug().noquote()<<"PODAJ PESEL";
    QString pesel = s.readLine();

    qDebug().noquote()<<"PODAJ E-MAIL";
    QString mail = s.readLine();

    int album = pobierzIntZZakresu(999999,100000,"PODAJ NR ALBUMU");

    Student *stud = new Student(album,0,imie,nazwisko,adres,pesel,mail,dataUR,grupa);
    if(grupa != NULL)
        grupa->addStudent(stud);

    system("CLS");
    return stud;
}

Pracownik *Interfejs::tworzEdytujPracownika(Pracownik *pracownik)
{
    QTextStream s(stdin);
    qDebug().noquote()<<"PODAJ IMIE";
    QString imie = s.readLine();

    qDebug().noquote()<<"PODAJ NAZWISKO";
    QString nazwisko = s.readLine();

    qDebug().noquote()<<"PODAJ ADRES";
    QString adres = s.readLine();

    QDate dataUR = pobierzDate("PODAJ DATE URODZENIA");

    qDebug().noquote()<<"PODAJ PESEL";
    QString pesel = s.readLine();

    qDebug().noquote()<<"PODAJ E-MAIL";
    QString mail = s.readLine();

    qDebug().noquote()<<"PODAJ INSTYTUT";
    QString instytut = s.readLine();

    qDebug().noquote()<<"PODAJ TYTUL NAUKOWY";
    QString tytul = s.readLine();

    qDebug().noquote()<<"PODAJ NR REFERENCYJNY";
    QString ID = s.readLine();

    Pracownik* pracow = new Pracownik(instytut,tytul,ID,imie,nazwisko,adres,pesel,mail,dataUR);
    return pracow;
}

Grupa *Interfejs::tworzGrupe(Rok* rok)
{
    system("CLS");
    QTextStream s(stdin);
    QString nazwa;

    bool ok = false;
    while(!ok){
        qDebug().noquote()<<"PODAJ NAZWE GRUPY";
        nazwa = s.readLine();
        if(nazwa != "")
            ok = true;
        else
            qDebug().noquote()<<"BŁĘDNA NAZWA. POWTORZ WPISYWANIE";
    }

    int rokS = pobierzIntZZakresu(5,1,"PODAJ ROK STUDIOW");

    nazwa = QString::number(rokS) + nazwa;

    int semestr = 0;
    if(rok->getAktualnySem() == 1)
            semestr = 2*rokS - 1;
    else if(rok->getAktualnySem() == 2)
        semestr = 2*rokS;

    qDebug().noquote()<<"PODAJ SPECJALNOŚĆ";
    QString specjalnosc = s.readLine();

    qDebug().noquote()<<"PODAJ KIERUNEK";
    QString kierunek = s.readLine();

    qDebug().noquote()<<"PODAJ WYDZIAŁ";
    QString wydzial = s.readLine();

    Grupa* grupa = new Grupa(nazwa,specjalnosc,wydzial,kierunek,rok,rokS,semestr);
    rok->adGrupa(grupa);

    system("CLS");
    qDebug().noquote()<<"GRUPA DODANA DO ROKU";
    s.readLine();
    return grupa;
}

QDate Interfejs::pobierzDate(QString text = "")
{
    QDate zwrot;
    QTextStream s(stdin);
    bool dobrze = false;
    QString pobierana;
    QStringList strList;
    if(text != "")
        qDebug().noquote() << text << endl;
    while(!dobrze)
    {
        qDebug().noquote()<<"PODAJ KOLEJNO DZIEN MIESIAC I ROK, W POSTACI NUMERYCZNEJ, ODDZIELAJAC SPACJAMI"<<endl;
        pobierana = s.readLine();
        strList = pobierana.split(" ", QString::SkipEmptyParts);

        if(strList.size() == 3){
            if(strList.at(0).size() != 0 && strList.at(1).size() != 0 && strList.at(2).size() != 0 ){
                bool pomoc = true;
                for(int i = 0; i < strList.size(); i++){
                    for(int j = 0; j < strList.at(i).size(); j++){
                        if(strList.at(i).at(j) < '0' && strList.at(i).at(j) > '9')
                            pomoc = false;
                    }
                }
                if(pomoc){
                    int dzien = strList.at(0).toInt();
                    int miesiac = strList.at(1).toInt();
                    int rok = strList.at(2).toInt();
                    dobrze = QDate::isValid(rok,miesiac,dzien);
                    if(dobrze)
                        zwrot = QDate(rok,miesiac,dzien);
                }
            }
        }
    }
    system("CLS");
    return zwrot;
}

Ocena Interfejs::pobierzOcene()
{
    QStringList lista;
    lista.clear();
    lista << "5.0";
    lista << "4.5";
    lista << "4.0";
    lista << "3.5";
    lista << "3.0";
    lista << "2.0";

    QString pom;
    for(int i = 0; i < lista.size(); i++){
        pom = QString::number(i+1) + "." + lista.at(i);
        lista.replace(i,pom);
    }

    int wybor = wydrukListaWybor(lista,"WYBIERZ OCENE");
    Ocena zwrot;
    switch(wybor){
    case 1:
        zwrot = piec;
        break;
    case 2:
        zwrot = czteryIPol;
        break;
    case 3:
        zwrot = cztery;
        break;
    case 4:
        zwrot = trzyIpol;
        break;
    case 5:
        zwrot = trzy;
        break;
    case 6:
        zwrot = dwa;
        break;
    default:
        zwrot = brak;
        break;
    }
    return zwrot;
}

Interfejs::Interfejs()
{
    silnik = new Silnik;
}

Interfejs::~Interfejs()
{
    delete silnik;
}

