#ifndef SILNIK_H
#define SILNIK_H


#include <QList>
#include <QStringList>
#include "osoba.h"
#include "przedmiot.h"
#include "rok.h"

class Rok;
class Przedmiot;

class Silnik
{
    QList<Rok*> listaLat;
    QList<Przedmiot*> listaPrzedm;
public:
    void addNowyRok(QDate st1, QDate en1, QDate st2, QDate en2);
    QString getInfoRokAt(int i);
    QStringList getLataAkademickie();
    Rok* getRokAt(int at);
    Silnik();
    ~Silnik();
};

#endif // SILNIK_H
