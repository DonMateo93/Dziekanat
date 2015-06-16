#include "rok.h"

EdycjaPrzedmotu *Rok::getPrzedmiotAt(int at)
{
    if(at < pierwszy->getIlePrzedmiotow() && at >=0){
        return pierwszy->getPrzedmiotAt(at);
    }else{
        at = at - pierwszy->getIlePrzedmiotow();
        if(at < drugi->getIlePrzedmiotow() && at >=0)
            return drugi->getPrzedmiotAt(at);
        else
            return NULL;
    }
}

Pracownik *Rok::getPracownikAt(int at)
{
    if(at < pracownicyLista.size() && at >= 0){
        return pracownicyLista.at(at);
    }else{
        return NULL;
    }
}

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

QStringList Rok::getPrzedmioty()
{
    QStringList zwrot;
    zwrot = pierwszy->getInfoPrzedmioty();
    zwrot += drugi->getInfoPrzedmioty();
    return zwrot;
}

Rok::Rok(Semestr* pierw = NULL, Semestr* dru = NULL):pierwszy(pierw),drugi(dru)
{
    pracownicyLista.clear();
    grupyLista.clear();
}

void Rok::aktualizujEdycjeWGrupach()
{

}

void Rok::dodajEdycjePrzedmiotu(Przedmiot *przedm,Pracownik* pracownik, Semestr* semestr)
{

}

Rok::~Rok()
{

}



EdycjaPrzedmotu *Semestr::getPrzedmiotAt(int at)
{
    if(at < przedmioty.size() && at >= 0){
        return przedmioty.at(at);
    }else{
        return NULL;
    }
}

int Semestr::getIlePrzedmiotow()
{
    return przedmioty.size();
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
