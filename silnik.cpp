#include <QList>
#include "silnik.h"


void Silnik::addNowyRok(QDate st1,QDate en1,QDate st2,QDate en2)
{
    Semestr* pierwszy = new Semestr(st1,en1);
    Semestr* drugi = new Semestr(st2,en2);
    Rok* rok = new Rok(pierwszy,drugi);
    listaLat.push_back(rok);
}

QStringList Silnik::getLataAkademickie()
{
    QStringList lista;
    lista.clear();
    if(!listaLat.isEmpty()){
        for(int i = 0; i < listaLat.size(); i++){
            lista<<listaLat.at(i)->getRok();
        }
    }

    return lista;
}

Silnik::Silnik()
{
    listaLat.clear();
}

Silnik::~Silnik()
{

}

