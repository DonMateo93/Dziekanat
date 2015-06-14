#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H

#include <QString>
#include <QDate>
#include "osoba.h"
#include "rok.h"

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
protected:
    Przedmiot* przedmiot;

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
    QString opis;
    QString skrot;
    QList<SkladowaPrzedmiotu*> skladoweList;

public:
    Przedmiot();
    ~Przedmiot();
};

class EdycjaPrzedmotu: public Przedmiot
{
    Semestr* semestr;
    Prowadzacy* prowadzacy;
public:

};

class SkladowaInfoS
{
    SkladowaPrzedmiotu* skladowa;
    Ocena ocena;
    Pracownik* prowadzacy;
};

class PrzedmiotInfoS
{
    Przedmiot* przedmiot;
    Ocena koncowa;
    QList<SkladowaInfoS*> skladowa;
};

#endif // PRZEDMIOT_H