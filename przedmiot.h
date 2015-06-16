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
    dwa,
    brak
};

enum SkladowaPrzedmiotu{
    Laboratorium,
    Projekt,
    Cwiczenia,
    Wyklad,
    Egzamin
};


class Przedmiot
{
protected:
    int ects;
    QString nazwa;
    QString opis;
    QString skrot;
    QList<SkladowaPrzedmiotu> skladoweList;

public:
    QString getInfo(bool szczegolowo = 0);
    QStringList jakieSkladowe();
    QString getNazwa(){return nazwa;}
    QString getOpis(){return opis;}
    QString getSkrot(){return skrot;}
    int getECTS(){return ects;}
    QList<SkladowaPrzedmiotu> getSkladowe(){return skladoweList;}
    Przedmiot();
    Przedmiot(QString naz,QString opi,QString skr,QList<SkladowaPrzedmiotu> sklad,int ect)
        :nazwa(naz),opis(opi),skrot(skr),skladoweList(sklad),ects(ect){}
    ~Przedmiot();
};

class EdycjaPrzedmotu: public Przedmiot
{
    Semestr* semestr;
    Pracownik* prowadzacy;
public:
    QString getInfo(bool szczegolowo = 0);
    void setProwadzacy(Pracownik* pr);
    EdycjaPrzedmotu();
    EdycjaPrzedmotu(Przedmiot* przedmiot, Pracownik* prow, Semestr* sem = NULL);
    Semestr* getSemestr(){return semestr;}

};

class SkladowaInfoS{
    SkladowaPrzedmiotu skladowa;
    Pracownik* pracownik;
    Ocena ocena;
public:
    SkladowaPrzedmiotu getSkladowa(){return skladowa;}
    Pracownik* getPracownik(){return pracownik;}
    Ocena getOcena(){return ocena;}
    void setSkladowa(SkladowaPrzedmiotu skl){skladowa = skl;}
    void setPracownik(Pracownik* prac);
    void setOcena(Ocena oce){ocena = oce;}
    QString getInfo();
    QString getAsString();
    QString getOcenaAsString();
};

class PrzedmiotInfoS
{
    QList<SkladowaInfoS> skladowe;
    EdycjaPrzedmotu* przedmiot;
    Ocena koncowa;
public:
    EdycjaPrzedmotu* getEdycja(){return przedmiot;}
    Ocena getKoncowa(){return koncowa;}
    void setEdycja(EdycjaPrzedmotu* przedm);
    void setKoncowa(Ocena konc);
    void setListSklad(QList<SkladowaInfoS> skl);
    QString getInfo();
    QString getOcenaAsString();
};



#endif // PRZEDMIOT_H
