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

