#include "rok.h"
#include <QChar>
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

void Rok::adGrupa(Grupa *grupa)
{
    if(grupa != NULL && !czyJestGrupaONazwie(grupa->getNazwa()))
        grupyLista.push_back(grupa);
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
    aktualny  = 1;
}

Rok::Rok(Semestr *pierw, Semestr *dru, QList<Grupa *> grupy, QList<Pracownik *> pracownicy)
{
    pierwszy = pierw;
    drugi = dru;

    for(int i = 0; i < grupy.size(); i++){
        if(grupy.at(i)->getNazwa().at(0)>='0' && grupy.at(i)->getNazwa().at(0)<'9'){

        }
    }
}

void Rok::aktualizujEdycjeWGrupach()
{

}

void Rok::dodajEdycjePrzedmiotu(Przedmiot *przedm, Pracownik* pracownik, int semestr)
{
    if(semestr == 1 || semestr == 2){
        EdycjaPrzedmotu* edycja = new EdycjaPrzedmotu(przedm,pracownik);
        dodajEdycjePrzedmiotu(edycja,semestr);
    }
}

void Rok::dodajEdycjePrzedmiotu(EdycjaPrzedmotu* edycja, int sem)
{
    if(sem == 1){
        pierwszy->addPrzedmiot(edycja);
    }else if(sem == 2){
        drugi->addPrzedmiot(edycja);
    }
}

void Rok::usunPrzedmiotAt(int at)
{
    if(at < pierwszy->getIlePrzedmiotow() && at >=0){
       pierwszy->usunPrzedmiotAt(at);
    }else{
        at = at - pierwszy->getIlePrzedmiotow();
        if(at < drugi->getIlePrzedmiotow() && at >=0)
            drugi->usunPrzedmiotAt(at);
    }
}

bool Rok::czyPracownikAtPracuje(int at)
{
        //sprawdzanie czy prowadzi przedmioty jakies
    return true;
}

void Rok::adPracownik(Pracownik *pracownik)
{
    bool ok = true;
    for(int i = 0; i < pracownicyLista.size(); i++){
        if(pracownicyLista.at(i) == pracownik)
            ok = false;
    }
    if(ok)
        pracownicyLista.push_back(pracownik);
}

void Rok::usunPracownikAt(int at)
{
    if(at < pracownicyLista.size() && at >= 0)
        pracownicyLista.removeAt(at);
}

void Rok::usunGrupaAt(int at)
{
    if(at < grupyLista.size() && at >= 0)
        grupyLista.removeAt(at);
}

void Rok::zmienSem()
{
    if(aktualny == 1){
        aktualny = 2;
    }else
        aktualny = 1;
}

bool Rok::czyJestGrupaONazwie(QString nazwa)
{
    bool jest = false;

    for(int i = 0; i < grupyLista.size(); i++){
        if(grupyLista.at(i)->getNazwa() == nazwa)
            jest = true;
    }

    return jest;
}

bool Rok::czyJestPracownik(Pracownik *pracownik)
{
    bool jest = false;
    for(int i = 0; i < pracownicyLista.size(); i++){
        if(pracownicyLista.at(i) == pracownik)
            jest = true;
    }
    return jest;
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

void Semestr::addPrzedmiot(EdycjaPrzedmotu *przedm)
{
    przedmioty.push_back(przedm);
}

void Semestr::usunPrzedmiotAt(int at)
{
    if(at < przedmioty.size() && at >= 0){
        przedmioty.removeAt(at);
    }
}
