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
class SkladowaInfoS;
class Rok;
enum SkladowaPrzedmiotu;
enum Ocena;

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
    QList<PrzedmiotInfoS> przedmiotyInfo;
public:
    QString getInfo(bool szczegolowo = 0);
    void setGrupa(Grupa* gru);
    void przypiszProwadzacego(Pracownik* pracownik,int atP,int atS);
    void przypiszOcene(Ocena ocena,int atP,int atS);
    void setKoncowaAt(Ocena ocena,int atP);
    QString getKartaOcen();
    Grupa* getGrupa(){return grupa;}
    int getAlbum(){return nrAlbumu;}
    bool getCzyPrzydzielonyDoGrupy();
    Student();
    QStringList getPrzedmioty();
    QStringList getSkladowePrzedmiotAt(int at);
    Student(int nrAl,int ects,QString im,QString naz,QString adr,QString pes,QString mai,QDate dat,Grupa* gru = NULL)
        :Osoba(im,naz,adr,pes,mai,dat),nrAlbumu(nrAl),ECTS(ects),grupa(gru){}
    ~Student(){}
    bool czyMaPrzypisanyPrzedmiot(EdycjaPrzedmotu* przedmiot);
    void nowyPrzedmiot(EdycjaPrzedmotu *przedmiot);
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
    QString getID();
    QString getTytulImie();
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
    void setNazwa(QString naz){id = naz;}
    bool czyJestPrzedmiot(EdycjaPrzedmotu* przedmiot);
    QString getID();
    QString getNazwa();
    QString getInfo();
    QString getSpec(){return specjalnosc;}
    QString getWydzial(){return wydzial;}
    QString getKierunek(){return kierunek;}
    QStringList getStudList();
    QStringList getPrzedmList();
    Student *getStudentAt(int at);
    void przypiszStudentomPrzedmioty();


};

#endif // OSOBA_H
