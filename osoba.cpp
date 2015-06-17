#include "osoba.h"

Osoba::Osoba()
{

}

Osoba::~Osoba()
{

}



QString Student::getInfo(bool szczegolowo)
{
    QString zwrot = "";

    if(szczegolowo){
        zwrot += "IMIE: " + imie + "\n";
        zwrot += "NAZWISKO: " + nazwisko + "\n";
        zwrot += "ADRES: " + adres + "\n";
        zwrot += "DATA URODZENIA: " + datUr.toString() + "\n";
        zwrot += "PESEL: " + pesel + "\n";
        zwrot += "ADRES E-MAIL: " + mail + "\n";
        zwrot += "NR ALBUMU: " + QString::number(nrAlbumu) + "\n";
        if(grupa != NULL){
            zwrot += "GRUPA: " + grupa->getID() + "\n";
            zwrot += "WYDZIAŁ: " + grupa->getWydzial() + "\n";
            zwrot += "KIERUNEK: " + grupa->getKierunek() + "\n";
            zwrot += "SPECJALNOSC: " + grupa->getSpec() + "\n";
            zwrot += "ROK STUDIOW: " + QString::number(grupa->getRokStud()) + "\n";
            zwrot += "SEMESTR STUDIOW: " + QString::number(grupa->getSemStud());
        }else
            zwrot += "NIEPRZYDZIELONY DO GRUPY";
    }else{
        if(grupa != NULL)
            zwrot += imie +" "+ nazwisko +" "+ QString::number(nrAlbumu) +" "+ grupa->getID();
        else
            zwrot += imie +" "+ nazwisko +" "+ QString::number(nrAlbumu) +" NIEPRZYDZIELNONY DO GRUPY";
    }

    return zwrot;
}

void Student::setGrupa(Grupa *gru)
{
    if(gru != NULL)
        grupa = gru;
}

void Student::przypiszProwadzacego(Pracownik *pracownik, int atP, int atS)
{
    if(atP < przedmiotyInfo.size() && atP >= 0){
        PrzedmiotInfoS przedmiot = przedmiotyInfo.at(atP);
        przedmiot.setProwadzacyAtSkladowa(atS,pracownik);
    }
}

void Student::przypiszOcene(Ocena ocena, int atP, int atS)
{
    if(atP < przedmiotyInfo.size() && atP >= 0){
        PrzedmiotInfoS przedmiot = przedmiotyInfo.at(atP);
        przedmiot.setOcenaAtSkladowa(atS,ocena);
    }
}

void Student::setKoncowaAt(Ocena ocena, int atP)
{
    if(atP < przedmiotyInfo.size() && atP >= 0){
        PrzedmiotInfoS przedmiot = przedmiotyInfo.at(atP);
        przedmiot.setKoncowa(ocena);
    }
}

QString Student::getKartaOcen()
{
    QString zwrot;
    for(int i = 0; i < przedmiotyInfo.size(); i++){
        zwrot += "====================================\n";
        PrzedmiotInfoS przedm = przedmiotyInfo.at(i);
        QString pom = przedm.getInfo(1);
        zwrot = zwrot + pom;
        zwrot += "====================================\n";
    }

    return zwrot;
}

bool Student::getCzyPrzydzielonyDoGrupy()
{
    if(grupa == NULL)
        return false;
    else
        return true;
}

QStringList Student::getPrzedmioty()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < przedmiotyInfo.size(); i ++){
        PrzedmiotInfoS przedmiot = przedmiotyInfo.at(i);
        zwrot << przedmiot.getInfo();
    }

    return zwrot;
}

QStringList Student::getSkladowePrzedmiotAt(int at)
{
    QStringList lista;
    lista.clear();
    if(at < przedmiotyInfo.size() && at >= 0){
        PrzedmiotInfoS przedmiot = przedmiotyInfo.at(at);
        lista = przedmiot.getSkladoweAsList();
    }

    return lista;
}

bool Student::czyMaPrzypisanyPrzedmiot(EdycjaPrzedmotu *przedmiot)
{
    bool odp = false;
    for(int i = 0; i < przedmiotyInfo.size(); i ++){
        PrzedmiotInfoS tmp = przedmiotyInfo.at(i);
        if(tmp.getEdycja() == przedmiot){
            odp = true;
            break;
        }
    }
    return odp;
}

void Student::nowyPrzedmiot(EdycjaPrzedmotu* przedmiot)
{
    QList<SkladowaPrzedmiotu> skladowe = przedmiot->getSkladowe();
    QList<SkladowaInfoS> lista;
    for(int i = 0; i < skladowe.size(); i++){
        SkladowaInfoS tmp(skladowe.at(i));
        lista << tmp;
    }
    PrzedmiotInfoS przedm(lista,przedmiot,brak);
    przedmiotyInfo << przedm;
}


QString Pracownik::getInfo(bool szczegolowo)
{
    QString zwrot = "";

    if(szczegolowo){
        zwrot += "IMIE: " + imie + "\n";
        zwrot += "NAZWISKO: " + nazwisko + "\n";
        zwrot += "ADRES: " + adres + "\n";
        zwrot += "DATA URODZENIA: " + datUr.toString() + "\n";
        zwrot += "PESEL: " + pesel + "\n";
        zwrot += "ADRES E-MAIL: " + mail + "\n";
        zwrot += "ID: " + ID;
    }else{
        zwrot += tytul +" "+ imie +" "+ nazwisko +" " + ID;
    }

    return zwrot;
}

QString Pracownik::getID()
{
    return ID;
}

QString Pracownik::getTytulImie()
{
    QString zwrot = tytul + " " + imie + " " + nazwisko;
    return zwrot;
}


Rok *Grupa::getRok()
{
    return rok;
}

void Grupa::usunStudentaAt(int at)
{
    if(at >= 0 && at <studList.size())
        studList.removeAt(at);
}

void Grupa::addStudent(Student *stud)
{
    if(stud != NULL){
        studList.push_back(stud);
        stud->setGrupa(this);
    }
}

void Grupa::addPrzedmiot(EdycjaPrzedmotu *przedmiot)
{
    if(przedmiot != NULL)
        przedList.append(przedmiot);
}

void Grupa::usunPrzedmiotAt(int at, bool zastDoStud)
{
    if(at < przedList.size() && at >= 0){
        if(!zastDoStud){
            przedList.removeAt(at);
        }else{
            przedList.removeAt(at);
            //USUWANIE PRZEDMIOTOW OD STUDENTOW
        }
    }
}

bool Grupa::czyJestPrzedmiot(EdycjaPrzedmotu *przedmiot)
{
    bool jest = false;
    for(int i = 0; i < przedList.size(); i++){
        if(przedList.at(i) == przedmiot)
            jest = true;
    }

    return jest;
}

QString Grupa::getID()
{
    QString zwrot = id + " " + rok->getRok();
    return zwrot;
}

QString Grupa::getNazwa()
{
    return id;
}

QString Grupa::getInfo()
{
    QString zwrot = "";

    zwrot += "NAZWA: " + getID() + "\n";
    zwrot += "WYDZIAL: " + wydzial + "\n";
    zwrot += "KIERUNEK: " + kierunek + "\n";
    zwrot += "SPECJALNOSC: " + specjalnosc + "\n";
    zwrot += "LICZBA STUDENTOW: " + QString::number(studList.size()+ 1) + "\n";

    return zwrot;
}

QStringList Grupa::getStudList()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < studList.size(); i ++){
        zwrot << studList.at(i)->getInfo();
    }

    return zwrot;
}

QStringList Grupa::getPrzedmList()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < przedList.size(); i ++){
        zwrot << przedList.at(i)->getInfo();
    }

    return zwrot;
}

Student *Grupa::getStudentAt(int at)
{
    if(at < studList.size() && at >= 0){
        return studList.at(at);
    }else{
        return NULL;
    }
}

void Grupa::przypiszStudentomPrzedmioty()
{
    for(int i = 0; i < studList.size(); i++){
        for(int j = 0; j < przedList.size(); j++){
            if(!studList.at(i)->czyMaPrzypisanyPrzedmiot(przedList.at(j)))
            {
                studList.at(i)->nowyPrzedmiot(przedList.at(j));
            }
        }
    }
}
