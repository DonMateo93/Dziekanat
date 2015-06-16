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

void Student::przypiszProwadzacego(Przedmiot *przedmiot, Pracownik *pracownik, SkladowaPrzedmiotu skladowa)
{

}

void Student::przypiszOcene(Przedmiot *przedmiot, SkladowaPrzedmiotu skladowa, Ocena ocena)
{

}

QString Student::getKartaOcen()
{
    QString zwrot;
    for(int i = 0; i < przedmiotyInfo.size(); i++){
        zwrot += "====================================\n";
        QString pom = przedmiotyInfo.at(i).getInfo();
        zwrot = zwrot + pom;
        zwrot += "====================================\n";
    }
}

bool Student::getCzyPrzydzielonyDoGrupy()
{
    if(grupa == NULL)
        return false;
    else
        return true;
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
