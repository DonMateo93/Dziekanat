#include <QList>
#include "silnik.h"


void Silnik::addNowyRok(QDate st1,QDate en1,QDate st2,QDate en2)
{
    Semestr* pierwszy = new Semestr(st1,en1);
    Semestr* drugi = new Semestr(st2,en2);
    Rok* rok = new Rok(pierwszy,drugi);
    listaLat.push_back(rok);
}

QString Silnik::getInfoRokAt(int i)
{
    if(i <= listaLat.size()){
        return listaLat.at(i)->getInfo();
    }else
        return QString("");
}

QStringList Silnik::getLataAkademickie()
{
    QStringList lista;
    lista.clear();
    for(int i = 0; i < listaLat.size(); i++){
        lista<<listaLat.at(i)->getRok();
    }

    return lista;
}

Rok *Silnik::getRokAt(int at)
{
    if(at >= 0 && at < listaLat.size()){
        return listaLat.at(at);
    }else
        return NULL;
}


Silnik::Silnik()
{
    Semestr* pierwszy = new Semestr(QDate(1993,1,15),QDate(1993,6,20));
    Semestr* drugi = new Semestr(QDate(1994,1,15),QDate(1994,6,15));
    Rok* rok = new Rok(pierwszy,drugi);

    Semestr* pierwszy2 = new Semestr(QDate(1995,1,15),QDate(1995,6,15));
    Semestr* drugi2 = new Semestr(QDate(1996,1,15),QDate(1996,6,15));
    Rok* rok2 = new Rok(pierwszy2,drugi2);

    Semestr* pierwszy3 = new Semestr(QDate(1997,1,15),QDate(1997,6,15));
    Semestr* drugi3 = new Semestr(QDate(1998,1,15),QDate(1998,8,15));
    Rok* rok3 = new Rok(pierwszy3,drugi3);

    listaLat.clear();
    listaLat.push_back(rok);
    listaLat.push_back(rok2);
    listaLat.push_back(rok3);
}

Silnik::~Silnik()
{

}

