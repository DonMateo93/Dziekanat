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

class SkladowaPrzedmiotu
{
public:
    virtual void f() = 0;
};

class Egzamin: SkladowaPrzedmiotu
{
public:

};

class Laboratorium: SkladowaPrzedmiotu
{
public:

};

class Projekt: SkladowaPrzedmiotu
{
public:

};

class Cwiczenia: SkladowaPrzedmiotu
{
public:

};

class Wyklad: SkladowaPrzedmiotu
{
public:

};


class Przedmiot
{
protected:
    int ects;
    QString nazwa;
    QString opis;
    QString skrot;
    QList<SkladowaPrzedmiotu*> skladoweList;

public:
    QString getInfo(bool szczegolowo = 0);
    QStringList jakieSkladowe();
    QString getNazwa(){return nazwa;}
    QString getOpis(){return opis;}
    QString getSkrot(){return skrot;}
    int getECTS(){return ects;}
    QList<SkladowaPrzedmiotu*> getSkladowe(){return skladoweList;}
    Przedmiot();
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
    EdycjaPrzedmotu(Przedmiot* przedmiot);

};

class SkladowaInfoS
{
    SkladowaPrzedmiotu* skladowa;
    Ocena ocena;
    Pracownik* prowadzacy;
};

class PrzedmiotInfoS
{
    EdycjaPrzedmotu* przedmiot;
    Ocena koncowa;
    QList<SkladowaInfoS*> skladowa;
};

class SkladowaInfoP
{
    SkladowaPrzedmiotu* skladowa;
    QList<Grupa*> ktoreGrupy;
};

#endif // PRZEDMIOT_H
