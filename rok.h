#ifndef ROK_H
#define ROK_H

#include <QDate>
#include "osoba.h"
#include "przedmiot.h"
#include <QList>

class Pracownik;
class Grupa;
class Przedmiot;

class Semestr
{

    QDate start;
    QDate end;
    QList<Przedmiot*> przedmioty;
public:
    QDate getStart();
    QDate getEnd();
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
    QString getRok();
    Rok(Semestr *pierw, Semestr *dru);
    ~Rok();
};

#endif // ROK_H
