#ifndef ROK_H
#define ROK_H

#include <QDate>
#include "osoba.h"
#include "przedmiot.h"
#include <QList>
#include <QStringList>

class Pracownik;
class Grupa;
class Przedmiot;
class EdycjaPrzedmotu;

class Semestr
{

    QDate start;
    QDate end;
    QList<EdycjaPrzedmotu*> przedmioty;
public:
    EdycjaPrzedmotu* getPrzedmiotAt(int at);
    int getIlePrzedmiotow();
    QDate getStart();
    QDate getEnd();
    QString getInfo();
    QStringList getInfoPrzedmioty();
    Semestr(QDate st, QDate en);
    ~Semestr();
};

class Rok
{
    QList<Pracownik*> pracownicyLista;
    QList<Grupa*> grupyLista;
    Semestr* pierwszy;
    Semestr* drugi;
public:
    EdycjaPrzedmotu* getPrzedmiotAt(int at);
    Pracownik* getPracownikAt(int at);
    Grupa* getGrupaAt(int at);
    Semestr* getSem(int a);
    QStringList getGrupy();
    QStringList getPracownicy();
    QString getRok();
    QString getInfo();
    QStringList getPrzedmioty();
    Rok(Semestr *pierw, Semestr *dru);
    void aktualizujEdycjeWGrupach();
    void dodajEdycjePrzedmiotu(Przedmiot* przedm, Pracownik *pracownik, Semestr *semestr);
    ~Rok();
};

#endif // ROK_H
