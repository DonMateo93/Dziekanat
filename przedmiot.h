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
    Pracownik* getProwadzacy(){return prowadzacy;}
    EdycjaPrzedmotu();
    EdycjaPrzedmotu(Przedmiot* przedmiot, Pracownik* prow, Semestr* sem = NULL);
    EdycjaPrzedmotu(EdycjaPrzedmotu* przedmiot);
    Semestr* getSemestr(){return semestr;}
    void setSemestr(Semestr* sem){semestr = sem;}

};

class SkladowaInfoS{
    SkladowaPrzedmiotu skladowa;
    Pracownik* pracownik;
    Ocena ocena;
public:
    SkladowaInfoS(SkladowaPrzedmiotu sklad,Ocena oc = brak,Pracownik* pra = NULL)
        :skladowa(sklad),ocena(oc),pracownik(pra){}
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
    QList< SkladowaInfoS > skladowe;
    EdycjaPrzedmotu* przedmiot;
    Ocena koncowa;
public:
    PrzedmiotInfoS(QList< SkladowaInfoS > sklad,EdycjaPrzedmotu* przedm = NULL,Ocena konc = brak)
        :skladowe(sklad),przedmiot(przedm),koncowa(konc){}
    EdycjaPrzedmotu* getEdycja(){return przedmiot;}
    Ocena getKoncowa(){return koncowa;}
    void setEdycja(EdycjaPrzedmotu* przedm);
    void setKoncowa(Ocena konc);
    void setListSklad(QList<SkladowaInfoS> skl);
    QString getInfo(bool szczegolowo = 0);
    QStringList getSkladoweAsList();
    QString getOcenaAsString();
    void setProwadzacyAtSkladowa(int at, Pracownik* prowadzacy);
    void setOcenaAtSkladowa(int at, Ocena ocena);
};



#endif // PRZEDMIOT_H
