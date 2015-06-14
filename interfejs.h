#ifndef INTERFEJS_H
#define INTERFEJS_H

#include <QDebug>
#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QDate>
#include "osoba.h"
#include "przedmiot.h"
#include "rok.h"
#include "silnik.h"

class Interfejs
{
    Silnik* silnik;
public:
    bool runMenuGlowne();
    void dodajRok();
    void edycjaLataAkademickie();
    int pobierzIntZZakresu(int gorny, int dolny, QString text);
    QDate pobierzDate(QString text);
    Interfejs();
    ~Interfejs();
};

#endif // INTERFEJS_H
