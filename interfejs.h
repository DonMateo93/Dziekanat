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
    void dodajStudenta();
    void usunStudenta();
    void edytujStudenta();
    void dodajRok();
    void dodajSzablonPrzedmiotu();
    void dodajPracownika();
    void usunPracownika();
    void edytujPraownika();
    void ususnSzablonPrzedmiotu();
    void edycjaLataAkademickie();
    void runMenuRokAkademicki(int at);
    void runMenuGrupy(Rok *rok);
    void grupaEdit(Rok *rok);
    void zarzadzajKontemStudentow(Grupa* grupa);
    void zarzadzajKontemStudenta(Student* student);
    void przypiszProwadzacegoDoSkladowej(Student* student);
    void grupaDelete(Rok *rok);
    void grupaAdd(Rok *rok);
    void runMenuPracownicy(Rok *rok);
    void przegladPracownicyRok(Rok* rok);
    void usunPracownikaZRoku(Rok* rok);
    void dodajPracownikaDoRoku(Rok* rok);
    void runMenuPrzedmioty(Rok *rok);
    void przedmiotyRokEdit(Rok *rok);
    void dodajPrzedmiotDoRoku(Rok *rok);
    void usunPrzedmiotZroku(Rok* rok);
    void przedmiotyGrupyEdit(Grupa* grupa);
    void dodajPrzedmiotDoGrupy(Grupa* grupa);
    void dodajStudentaDoGrupy(Grupa* grupa);
    void usunPrzedmiotZGrupy(Grupa* grupa);
    int pobierzIntZZakresu(int gorny, int dolny, QString text);
    bool pytanieTakNie(QString text = "");
    void wydrukListyZNumeracja(QStringList &lista, QString text = "", bool dodajPowrot = 0);
    int wydrukListaWybor(QStringList &lista, QString text = "", bool dodajPowrot = 0);
    Student* tworzStudenta(Grupa *grupa = NULL);
    Pracownik* tworzEdytujPracownika(Pracownik* pracownik = NULL);
    Grupa* tworzGrupe(Rok* rok);
    QDate pobierzDate(QString text);
    Interfejs();
    ~Interfejs();
};

#endif // INTERFEJS_H
