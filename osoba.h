#ifndef OSOBA_H
#define OSOBA_H

#include <QString>
#include <QDate>
#include <QList>
#include <QStringList>
#include "przedmiot.h"
#include "rok.h"
#include "osoba.h"

class Grupa;
class PrzedmiotInfoS;
class SkladowaInfoP;
class Rok;

class Osoba
{
protected:
    QString imie;
    QString nazwisko;
    QString adres;
    QDate datUr;
    QString pesel;
    QString mail;

public:
    virtual QString getInfo(bool szczegolowo = 0) = 0;
    Osoba(QString im,QString naz,QString adr,QString pes,QString mai,QDate dat)
        :imie(im),nazwisko(naz), adres(adr), datUr(dat), pesel(pes), mail(mai){}
    Osoba();
    ~Osoba();
};

class Student: public Osoba
{
    int nrAlbumu;
    int ECTS;
    Grupa* grupa;
    QList<PrzedmiotInfoS*> przedmiotyInfo;
public:
    QString getInfo(bool szczegolowo = 0);
    void setGrupa(Grupa* gru);
    Student();
    Student(int nrAl,int ects,QString im,QString naz,QString adr,QString pes,QString mai,QDate dat,Grupa* gru = NULL)
        :Osoba(im,naz,adr,pes,mai,dat),nrAlbumu(nrAl),ECTS(ects),grupa(gru){}
    ~Student();
};

class Pracownik: public Osoba
{
protected:
    QString instytut;
    QString tytul;
    QString ID;
    QList<SkladowaInfoP*> skladoweLista;
public:
    Pracownik();
    Pracownik(QString inst,QString tyt,QString id,QString ime,QString nazw,QString adr,QString pesel,QString email,QDate data)
        :instytut(inst),tytul(tyt),ID(id),Osoba(ime,nazw,adr,pesel,email,data){}
    QString getInfo(bool szczegolowo = 0);
};

class Grupa
{
    QString id;
    QList<Student*> studList;
    QList<EdycjaPrzedmotu*> przedList;
    Rok* rok;
    int rokStud;
    int semStud;
    QString specjalnosc;
    QString wydzial;
    QString kierunek;
public:
    Grupa();
    Grupa(QString idi,QString spec,QString wydz,QString kier,Rok* ro,int rokk,int sem)
        :id(idi),specjalnosc(spec),wydzial(wydz),kierunek(kier),rok(ro),rokStud(rokk),semStud(sem){}
    Rok *getRok();
    int getRokStud(){return rokStud;}
    int getSemStud(){return semStud;}
    void usunStudentaAt(int at);
    void addStudent(Student* stud);
    void addPrzedmiot(EdycjaPrzedmotu* przedmiot);
    void usunPrzedmiotAt(int at, bool zastDoStud = 0);
    bool czyJestPrzedmiot(EdycjaPrzedmotu* przedmiot);
    QString getID();
    QString getNazwa();
    QString getInfo();
    QString getSpec(){return specjalnosc;}
    QString getWydzial(){return wydzial;}
    QString getKierunek(){return kierunek;}
    QStringList getStudList();
    QStringList getPrzedmList();


};

#endif // OSOBA_H
