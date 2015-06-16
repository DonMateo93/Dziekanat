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
    void przedmiotyRokEdit(Rok *rok);
    void przedmiotyGrupyEdit(Grupa* grupa);
    void dodajPrzedmiotDoGrupy(Grupa* grupa);
    void usunPrzedmiotZGrupy(Grupa* grupa);
    int pobierzIntZZakresu(int gorny, int dolny, QString text);
    bool pytanieTakNie(QString text = "");
    void wydrukListyZNumeracja(QStringList &lista, QString text = "", bool dodajPowrot = 0);
    int wydrukListaWybor(QStringList &lista, QString text = "", bool dodajPowrot = 0);
    Student* tworzStudenta(Grupa *grupa);
    QDate pobierzDate(QString text);
    Interfejs();
    ~Interfejs();
};

#endif // INTERFEJS_H
