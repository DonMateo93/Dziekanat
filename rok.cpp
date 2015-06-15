#include "rok.h"

Grupa *Rok::getGrupaAt(int at)
{
    if(at < grupyLista.size() && at >= 0){
        return grupyLista.at(at);
    }else{
        return NULL;
    }
}

Semestr *Rok::getSem(int a)
{
    if(a == 1){
        return pierwszy;
    }else if(a == 2){
        return drugi;
    }else
        return NULL;
}

QStringList Rok::getGrupy()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < grupyLista.size(); i++){
        zwrot << grupyLista.at(i)->getID();
    }

    return zwrot;
}

QStringList Rok::getPracownicy()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < pracownicyLista.size(); i++){
        zwrot << pracownicyLista.at(i)->getInfo();
    }

    return zwrot;
}

QString Rok::getRok()
{
    QString start = QString::number(pierwszy->getStart().year());
    QString stop = QString::number(drugi->getStart().year());
    return (start + "/" + stop);
}

QString Rok::getInfo()
{
    QString zwracana;
    zwracana = "Rok akademicki " + getRok() + "\n\n";
    zwracana += "Semestr I:\n";
    zwracana += pierwszy->getInfo() + "\n";
    zwracana += "Semestr II:\n";
    zwracana += drugi->getInfo() + "\n";
    return zwracana;
}

Rok::Rok(Semestr* pierw = NULL, Semestr* dru = NULL):pierwszy(pierw),drugi(dru)
{
    pracownicyLista.clear();
    grupyLista.clear();
}

Rok::~Rok()
{

}



QDate Semestr::getStart()
{
    return start;
}

QDate Semestr::getEnd()
{
    return end;
}

QString Semestr::getInfo()
{
    QString zwrot;
    zwrot = "Rozpoczecie: " + start.toString() + "\n";
    zwrot += "Zakonczenie:"  + end.toString() + "\n";
    return zwrot;
}

QStringList Semestr::getInfoPrzedmioty()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < przedmioty.size(); i++){
        zwrot << przedmioty.at(i)->getInfo();
    }

    return zwrot;
}

Semestr::Semestr(QDate st, QDate en):start(st), end(en)
{

}
