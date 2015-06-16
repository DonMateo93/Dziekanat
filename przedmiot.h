#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H

#include <QString>
#include <QDate>
#include <QList>
#include "osoba.h"
#include "rok.h"

class Przedmiot;
class Semestr;
class Pracownik;
class Grupa;

enum Ocena
{
    piec,
    czteryIPol,
    cztery,
    trzyIpol,
    trzy,
    dwa
};

enum SkladowaPrzedmiotu{
    Laboratorium,
    Projekt,
    Cwiczenia,
    Wyklad,
    Egzamin
};


class Przedmiot
{
protected:
    int ects;
    QString nazwa;
    QString opis;
    QString skrot;
    QList<SkladowaPrzedmiotu> skladoweList;

public:
    QString getInfo(bool szczegolowo = 0);
    QStringList jakieSkladowe();
    QString getNazwa(){return nazwa;}
    QString getOpis(){return opis;}
    QString getSkrot(){return skrot;}
    int getECTS(){return ects;}
    QList<SkladowaPrzedmiotu> getSkladowe(){return skladoweList;}
    Przedmiot();
    Przedmiot(QString naz,QString opi,QString skr,QList<SkladowaPrzedmiotu> sklad,int ect)
        :nazwa(naz),opis(opi),skrot(skr),skladoweList(sklad),ects(ect){}
    ~Przedmiot();
};

class EdycjaPrzedmotu: public Przedmiot
{
    Semestr* semestr;
    Pracownik* prowadzacy;
public:
    QString getInfo(bool szczegolowo = 0);
    void setProwadzacy(Pracownik* pr);
    EdycjaPrzedmotu();
    EdycjaPrzedmotu(Przedmiot* przedmiot, Pracownik* prow, Semestr* sem = NULL);
    Semestr* getSemestr(){return semestr;}

};

class SkladowaInfoS{
    SkladowaPrzedmiotu skladowa;
    Pracownik* pracownik;
    Ocena ocena;
};

class PrzedmiotInfoS
{
    QList<SkladowaInfoS> skladowe;
    EdycjaPrzedmotu* przedmiot;
    Ocena koncowa;
};



#endif // PRZEDMIOT_H
