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
        zwrot += "GRUPA: " + grupa->getID() + "\n";
        zwrot += "WYDZIAŁ: " + grupa->getWydzial() + "\n";
        zwrot += "KIERUNEK: " + grupa->getKierunek() + "\n";
        zwrot += "SPECJALNOSC: " + grupa->getSpec() + "\n";
        zwrot += "ROK STUDIOW: " + QString::number(grupa->getRokStud()) + "\n";
        zwrot += "SEMESTR STUDIOW: " + QString::number(grupa->getSemStud());
    }else{
        zwrot += imie +" "+ nazwisko +" "+ QString::number(nrAlbumu) +" "+ grupa->getID();
    }

    return zwrot;
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


void Grupa::usunStudentaAt(int at)
{
    if(at >= 0 && at <studList.size())
        studList.removeAt(at);
}

void Grupa::addStudent(Student *stud)
{
    if(stud != NULL)
        studList.push_back(stud);
}

QString Grupa::getID()
{
    QString zwrot = id + " " + rok->getRok();
    return zwrot;
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
