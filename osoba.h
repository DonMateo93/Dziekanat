#ifndef OSOBA_H
#define OSOBA_H

#include <QString>
#include <QDate>
#include <QList>
#include "przedmiot.h"
#include "rok.h"
#include "osoba.h"

class Grupa;
class PrzedmiotInfoS;
class SkladowaInfoP;
class Rok;

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
    QList<SkladowaInfoP*> skladoweLista;

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

};

#endif // OSOBA_H
