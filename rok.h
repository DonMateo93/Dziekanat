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
    Grupa* getGrupaAt(int at);
    Semestr* getSem(int a);
    QStringList getGrupy();
    QStringList getPracownicy();
    QString getRok();
    QString getInfo();
    Rok(Semestr *pierw, Semestr *dru);
    ~Rok();
};

#endif // ROK_H
