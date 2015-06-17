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
    void addPrzedmiot(EdycjaPrzedmotu* przedm);
    void usunPrzedmiotAt(int at);
    int getStartRok(){return start.year();}
    ~Semestr();
};

class Rok
{
    QList<Pracownik*> pracownicyLista;
    QList<Grupa*> grupyLista;
    Semestr* pierwszy;
    Semestr* drugi;
    int aktualny;
    bool obecny;
public:
    void setAktualny(){obecny = true;}
    void setNieAktualny(){obecny = false;}
    EdycjaPrzedmotu* getPrzedmiotAt(int at);
    Pracownik* getPracownikAt(int at);
    Grupa* getGrupaAt(int at);
    void adGrupa(Grupa* grupa);
    Semestr* getSem(int a);
    QStringList getGrupy();
    QStringList getPracownicy();
    QString getRok();
    QString getInfo();
    QStringList getPrzedmioty();
    Rok(Semestr *pierw, Semestr *dru);
    Rok(Semestr *pierw, Semestr *dru,QList<Grupa*> grupy,QList<Pracownik*> pracownicy);
    void aktualizujEdycjeWGrupach();
    void dodajEdycjePrzedmiotu(Przedmiot* przedm, Pracownik *pracownik, int semestr);
    void dodajEdycjePrzedmiotu(EdycjaPrzedmotu *edycja, int sem);
    void usunPrzedmiotAt(int at);
    bool czyPracownikAtPracuje(int at);
    void adPracownik(Pracownik* pracownik);
    void usunPracownikAt(int at);
    void usunGrupaAt(int at);
    int getAktualnySem(){return aktualny;}
    int getStartRok(){return pierwszy->getStartRok();}
    void zmienSem();
    bool czyJestGrupaONazwie(QString nazwa);
    bool czyJestPracownik(Pracownik* pracownik);
    ~Rok();
};

#endif // ROK_H
