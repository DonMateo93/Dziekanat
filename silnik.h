#ifndef SILNIK_H
#define SILNIK_H


#include <QList>
#include <QStringList>
#include "osoba.h"
#include "przedmiot.h"
#include "rok.h"

class Rok;

class Silnik
{
    QList<Rok*> listaLat;
public:
    void addNowyRok(QDate st1, QDate en1, QDate st2, QDate en2);
    QStringList getLataAkademickie();
    Silnik();
    ~Silnik();
};

#endif // SILNIK_H
