#ifndef SILNIK_H
#define SILNIK_H


#include <QList>
#include <QStringList>
#include "osoba.h"
#include "przedmiot.h"
#include "rok.h"

class Rok;
class Przedmiot;
class Student;

class Silnik
{
    QList<Rok*> listaLat;
    QList<Przedmiot*> listaPrzedm;
    QList<Pracownik*> pracownicy;
    QList<Student*> studenci;
public:
    void dodajNowyRokAutomatycznie();
    void addNowyRok(QDate st1, QDate en1, QDate st2, QDate en2);
    void addNowyRok(Rok* rok);
    void addPrzedmiot(Przedmiot* przedmiot);
    void usunPrzedmiotAt(int at);
    void usunPracownikAt(int at);
    void usunStudentAt(int at);
    void zamienPracownikAt(int at, Pracownik *pracownik);
    void zamienStudentAt(int at, Student *student);
    void adStudent(Student* student);
    void adPracownik(Pracownik* pracownik);
    void porzadkujRoczniki();
    bool czyJestPrzedmiotONazwie(QString nazwa);
    bool czyJestPracownikOID(QString nazwa);
    bool czyJestStudentOIndeksie(int indeks);
    QString getInfoRokAt(int i);
    QStringList getLataAkademickie();
    QStringList getPrzedmioty();
    QStringList getPracownicy();
    QStringList getStudenci();
    Pracownik* getPracownikAt(int at);
    Przedmiot* getPrzedmiotAt(int at);
    QStringList getNieprzydzieleniStudenci();
    Student *getNieprzydzielonyStudentAt(int at);
    Rok* getRokAt(int at);
    Silnik();
    ~Silnik();
};

#endif // SILNIK_H
