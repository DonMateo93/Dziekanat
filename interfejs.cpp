#include "interfejs.h"
#include <stdlib.h>

using namespace std;

bool Interfejs::runMenuGlowne()
{
    bool NieWychodz = false;
    QStringList lista;
    lista.clear();
    lista << "DODAJ NOWY ROK AKADEMICKI";
    lista << "PRZEGLADAJ/EDYTUJ LATA AKADEMICKIE";
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
        }
    }

    if(wybor == lista.size())
        return true;
    else
        return false;
}

void Interfejs::dodajRok()
{
    QDate start1,end1,start2,end2;
    bool dobrze2 = false;

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
                lista << "USUN PRZEDMIOT";
                lista << "DODAJ PRZEDMIOT";
                lista << "POWROT";

                QStringList pomocnicza;
                pomocnicza.clear();
                int wybor2;

                switch(wybor)
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
                    system("CLS");
                    qDebug().noquote() << grupa->getID();
                    tworzStudenta(grupa);
                    break;
                case 4:
                    system("CLS");

                    break;
                case 5:
                    system("CLS");

                    break;
                case 6:
                    powrot = true;
                    break;
                }
            }
        }
    }
}

void Interfejs::grupaDelete(Rok *rok)
{

}

void Interfejs::grupaAdd(Rok *rok)
{

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
            lista << "PRZEGLADAJ/EDYTUJ PRACOWNIKA";
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

                    break;
                case 2:
                    system("CLS");

                    break;
                case 3:
                    system("CLS");

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

                    break;
                case 2:
                    system("CLS");

                    break;
                case 3:
                    system("CLS");

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
                if(pobierana.at(0) != '0'){
                    zwrot = pobierana.toInt();
                    if(zwrot >= dolny && zwrot <= gorny){
                        ok = true;
                    }
                }
            }
        }
        if(!ok)
            qDebug().noquote()<<"BLAD. WPROWADZ LICZBE PONOWNIE"<<endl;
    }while(!ok);

    system("CLS");
    return zwrot;
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
    grupa->addStudent(stud);

    system("CLS");
    qDebug().noquote()<<"STUDENT DODANY";
    s.readLine();
    return stud;
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

Interfejs::Interfejs()
{
    silnik = new Silnik;
}

Interfejs::~Interfejs()
{
    delete silnik;
}

