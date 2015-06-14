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
    Pracownik* prowadzacy;
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

class SkladowaInfoP
{
    SkladowaPrzedmiotu* skladowa;
    QList<Grupa*> ktoreGrupy;
};

#endif // PRZEDMIOT_H
