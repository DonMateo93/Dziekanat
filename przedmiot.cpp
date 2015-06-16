#include "przedmiot.h"

QString Przedmiot::getInfo(bool szczegolowo)
{
    QString zwrot = "";

    if(szczegolowo){
        zwrot += "NAZWA: " + nazwa + "\n";
        zwrot += "SKROT: " + skrot + "\n";
        zwrot += "ECTS: " + QString::number(ects) + "\n";
        zwrot += "PRZEDMIOT SKLADA SIE Z:\n";
        zwrot += jakieSkladowe().join("\n") + "\n";
        zwrot += "OPIS: " + opis + "\n";
    }else{
        zwrot +=  nazwa + " (" + skrot + ")\n";
    }

    return zwrot;
}

QStringList Przedmiot::jakieSkladowe()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < skladoweList.size(); i++){
        if(skladoweList.at(i) == Egzamin){
            zwrot << "Egzamin";
        }else if(skladoweList.at(i) == Laboratorium){
            zwrot << "Laboratorium";
        }else if(skladoweList.at(i) == Cwiczenia){
            zwrot << "Cwiczenia";
        }else if(skladoweList.at(i) == Projekt){
            zwrot << "Projekt";
        }else if(skladoweList.at(i) == Wyklad){
            zwrot << "Wyklad";
        }
    }

    return zwrot;
}

Przedmiot::Przedmiot()
{

}

Przedmiot::~Przedmiot()
{

}



QString EdycjaPrzedmotu::getInfo(bool szczegolowo)
{
    QString zwrot = "";

    if(szczegolowo){
        zwrot = Przedmiot::getInfo(1);
        zwrot += "PROWADZACY: " + prowadzacy->getInfo() + "\n";
    }else{
        zwrot = Przedmiot::getInfo(0);
    }

    return zwrot;
}

void EdycjaPrzedmotu::setProwadzacy(Pracownik *pr)
{
    if(pr != NULL)
        prowadzacy = pr;
}

EdycjaPrzedmotu::EdycjaPrzedmotu(Przedmiot *przedmiot, Pracownik *prow, Semestr *sem )
    :prowadzacy(prow),semestr(sem)
{
    ects = przedmiot->getECTS();
    nazwa = przedmiot->getNazwa();
    opis = przedmiot->getOpis();
    skrot = przedmiot->getSkrot();
    skladoweList = przedmiot->getSkladowe();
}



void SkladowaInfoS::setPracownik(Pracownik *prac)
{
    if(prac != NULL)
        pracownik = prac;
}

QString SkladowaInfoS::getInfo()
{
    QString zwrot = "";

    zwrot += getAsString() + ":\n";
    zwrot =zwrot + "PROWADZACY" + ": ";
    if(pracownik != NULL)
        zwrot = zwrot + pracownik->getTytulImie() + "\n";
    else
        zwrot += "BRAK \n";
    zwrot =zwrot + "OCENA" + ": " + getOcenaAsString();

    return zwrot;
}

QString SkladowaInfoS::getAsString()
{
    QString zwrot;
    switch(skladowa)
    {
    case Egzamin:
        zwrot = "EGZAMIN";
        break;
    case Cwiczenia:
        zwrot = "CWICZENIA";
        break;
    case Wyklad:
        zwrot = "WYKLAD";
        break;
    case Laboratorium:
        zwrot = "LABORATORIUM";
        break;
    case Projekt:
        zwrot = "PROJEKT";
        break;
    }
    return zwrot;
}

QString SkladowaInfoS::getOcenaAsString()
{
    QString zwrot;
    switch(ocena)
    {
    case piec:
        zwrot = "5.0";
        break;
    case czteryIPol:
        zwrot = "4.5";
        break;
    case cztery:
        zwrot = "4.0";
        break;
    case trzyIpol:
        zwrot = "3.5";
        break;
    case trzy:
        zwrot = "3.0";
        break;
    case dwa:
        zwrot = "2.0";
        break;
    case brak:
        zwrot = "BRAK";
        break;
    }
    return zwrot;
}

void PrzedmiotInfoS::setEdycja(EdycjaPrzedmotu *przedm)
{
    przedmiot = przedm;
}

void PrzedmiotInfoS::setKoncowa(Ocena konc)
{
    koncowa = konc;
}

void PrzedmiotInfoS::setListSklad(QList<SkladowaInfoS> skl)
{
    skladowe = skl;
}

QString PrzedmiotInfoS::getInfo()
{
    QString zwrot = "";

    if(przedmiot != NULL){
        zwrot += przedmiot->getInfo();
        zwrot =zwrot + "OCENA" + ": " + getOcenaAsString();
        for(int i = 0; i < skladowe.size(); i++){
            zwrot += "--------------------\n";
            zwrot += skladowe.at(i).getInfo();
            zwrot += "--------------------\n";
        }
    }

    return zwrot;
}

QString PrzedmiotInfoS::getOcenaAsString()
{
    QString zwrot;
    switch(koncowa)
    {
    case piec:
        zwrot = "5.0";
        break;
    case czteryIPol:
        zwrot = "4.5";
        break;
    case cztery:
        zwrot = "4.0";
        break;
    case trzyIpol:
        zwrot = "3.5";
        break;
    case trzy:
        zwrot = "3.0";
        break;
    case dwa:
        zwrot = "2.0";
        break;
    case brak:
        zwrot = "BRAK";
        break;
    }
    return zwrot;
}
