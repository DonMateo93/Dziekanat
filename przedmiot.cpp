#include "przedmiot.h"

QString Przedmiot::getInfo(bool szczegolowo)
{
    QString zwrot = "";

    if(szczegolowo){
        zwrot += "NAZWA: " + nazwa + "\n";
        zwrot += "SKROT: " + skrot + "\n";
        zwrot += "ECTS: " + QString::number(ects) + "\n";
        zwrot += "ADRES E-MAIL PRZEDMIOT SKLADA SIE Z:\n";
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
        if(dynamic_cast<Egzamin*>(skladoweList.at(i))){
            zwrot << "Egzamin";
        }else if(dynamic_cast<Laboratorium*>(skladoweList.at(i))){
            zwrot << "Laboratorium";
        }else if(dynamic_cast<Cwiczenia*>(skladoweList.at(i))){
            zwrot << "Cwiczenia";
        }else if(dynamic_cast<Projekt*>(skladoweList.at(i))){
            zwrot << "Projekt";
        }else if(dynamic_cast<Wyklad*>(skladoweList.at(i))){
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

EdycjaPrzedmotu::EdycjaPrzedmotu(Przedmiot *przedmiot)
{
    ects = przedmiot->getECTS();
    nazwa = przedmiot->getNazwa();
    opis = przedmiot->getOpis();
    skrot = przedmiot->getSkrot();
    QList<SkladowaPrzedmiotu*> lista = przedmiot->getSkladowe();

    QStringList listas = przedmiot->jakieSkladowe();
    QString str = "Egzamin";
    if(listas.contains(str)){
        SkladowaPrzedmiotu* skl = new Egzamin;
        skladoweList<<skl;
    }
}

