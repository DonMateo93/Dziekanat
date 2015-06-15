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
    QString getInfo(bool szczegolowo = 0);
};

class Grupa
{
    QString id;
    QList<Student*> studList;
    QList<Przedmiot*> przedList;
    Rok* rok;
    int rokStud;
    int semStud;
    QString specjalnosc;
    QString wydzial;
    QString kierunek;
public:
    int getRokStud(){return rokStud;}
    int getSemStud(){return semStud;}
    void usunStudentaAt(int at);
    void addStudent(Student* stud);
    QString getID();
    QString getInfo();
    QString getSpec(){return specjalnosc;}
    QString getWydzial(){return wydzial;}
    QString getKierunek(){return kierunek;}
    QStringList getStudList();
    QString getPrzedmList();


};

#endif // OSOBA_H
