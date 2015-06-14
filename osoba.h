#ifndef OSOBA_H
#define OSOBA_H

#include <QString>
#include <QDate>
#include <przedmiot.h>
#include "rok.h"

class Osoba
{
protected:
    QString imie;
    QString nazwisko;
    QString adres;
    QDate datUr;
    QString pesel;
    QString mail;

public:
    Osoba();
    ~Osoba();
};

class Student: public Osoba
{
    int nrAlbumu;
    int ECTS;
    Grupa* grupa;
    QList<PrzedmiotInfoS*> przedmiotyInfo;
public:
    Student();
    ~Student();
};

class Pracownik: public Osoba
{
protected:
    QString instytut;
    QString tytul;
public:

};

class Prowadzacy: public Pracownik
{
    QList<Przedmiot*> przedList;
public:
};

class Grupa
{
    QString id;
    QList<Student*> studList;
    QList<Przedmiot*> przedList;
    Rok* rok;
    QString specjalnosc;
    QString wydzial;
    QString kierunek;
public:

};



#endif // OSOBA_H
