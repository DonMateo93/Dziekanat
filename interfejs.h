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
    void runMenuRokAkademicki(int at);
    void runMenuGrupy(Rok *rok);
    void grupaEdit(Rok *rok);
    void grupaDelete(Rok *rok);
    void grupaAdd(Rok *rok);
    void runMenuPracownicy(Rok *rok);
    void runMenuPrzedmioty(Rok *rok);
    int pobierzIntZZakresu(int gorny, int dolny, QString text);
    Student* tworzStudenta(Grupa *grupa);
    QDate pobierzDate(QString text);
    Interfejs();
    ~Interfejs();
};

#endif // INTERFEJS_H
