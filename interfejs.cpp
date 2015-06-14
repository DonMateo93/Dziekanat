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
    system("CLS");
    QStringList lista = silnik->getLataAkademickie();
    qDebug().noquote()<<"DOSTEPNE LATA AKADEMICKIE:";
    if(!lista.isEmpty())
        qDebug().noquote() <<lista.join("\n");
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

}

