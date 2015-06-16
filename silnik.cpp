#include <QList>
#include "silnik.h"


void Silnik::addNowyRok(QDate st1,QDate en1,QDate st2,QDate en2)
{
    Semestr* pierwszy = new Semestr(st1,en1);
    Semestr* drugi = new Semestr(st2,en2);
    Rok* rok = new Rok(pierwszy,drugi);
    listaLat.push_back(rok);
}

void Silnik::addPrzedmiot(Przedmiot *przedmiot)
{
    if(przedmiot != NULL)
        listaPrzedm.push_back(przedmiot);
}

void Silnik::usunPrzedmiotAt(int at)
{
    if(at < listaPrzedm.size() && at >= 0){
        listaPrzedm.removeAt(at);
    }
}

void Silnik::usunPracownikAt(int at)
{
    if(at < pracownicy.size() && at >= 0){
        pracownicy.removeAt(at);
    }
}

void Silnik::usunStudentAt(int at)
{
    if(at < studenci.size() && at >= 0){
        studenci.removeAt(at);
    }
}

void Silnik::zamienPracownikAt(int at,Pracownik* pracownik)
{
    if(at < pracownicy.size() && at >= 0){
        Pracownik* temp = pracownicy.at(at);
        pracownicy.replace(at,pracownik);
        delete temp;
    }
}

void Silnik::zamienStudentAt(int at, Student *student)
{
    if(at < studenci.size() && at >= 0){
        Student* temp = studenci.at(at);
        studenci.replace(at,student);
        delete temp;
    }
}

void Silnik::adStudent(Student *student)
{
    if(student != NULL)
        studenci.push_back(student);
}

void Silnik::adPracownik(Pracownik *pracownik)
{
    if(pracownik != NULL)
        pracownicy.push_back(pracownik);
}

bool Silnik::czyJestPrzedmiotONazwie(QString nazwa)
{
    bool odp = false;
    for(int i = 0; i < listaPrzedm.size(); i++){
        if(listaPrzedm.at(i)->getNazwa() == nazwa)
            odp = true;
    }

    return odp;
}

bool Silnik::czyJestPracownikOID(QString nazwa)
{
    bool odp = false;
    for(int i = 0; i < pracownicy.size(); i++){
        if(pracownicy.at(i)->getID() == nazwa)
            odp = true;
    }

    return odp;
}

bool Silnik::czyJestStudentOIndeksie(int indeks)
{
    bool odp = false;
    for(int i = 0; i < studenci.size(); i++){
        if(studenci.at(i)->getAlbum() == indeks)
            odp = true;
    }

    return odp;
}

QString Silnik::getInfoRokAt(int i)
{
    if(i <= listaLat.size()){
        return listaLat.at(i)->getInfo();
    }else
        return QString("");
}

QStringList Silnik::getLataAkademickie()
{
    QStringList lista;
    lista.clear();
    for(int i = 0; i < listaLat.size(); i++){
        lista<<listaLat.at(i)->getRok();
    }

    return lista;
}

QStringList Silnik::getPrzedmioty()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < listaPrzedm.size(); i++){
        zwrot << listaPrzedm.at(i)->getInfo();
    }

    return zwrot;
}

QStringList Silnik::getPracownicy()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < pracownicy.size(); i++){
        zwrot << pracownicy.at(i)->getInfo();
    }

    return zwrot;
}

QStringList Silnik::getStudenci()
{
    QStringList zwrot;
    zwrot.clear();

    for(int i = 0; i < studenci.size(); i++){
        zwrot << studenci.at(i)->getInfo();
    }

    return zwrot;
}

Pracownik *Silnik::getPracownikAt(int at)
{
    if(at < pracownicy.size() && at >= 0){
        return pracownicy.at(at);
    }else{
        return NULL;
    }
}

Przedmiot *Silnik::getPrzedmiotAt(int at)
{
    if(at < listaPrzedm.size() && at >= 0){
        return listaPrzedm.at(at);
    }else{
        return NULL;
    }
}

QStringList Silnik::getNieprzydzieleniStudenci()
{
    QStringList lista;
    for(int i = 0; i < studenci.size(); i++){
        if(!studenci.at(i)->getCzyPrzydzielonyDoGrupy())
            lista<<studenci.at(i)->getInfo();
    }

    return lista;
}

Student *Silnik::getNieprzydzielonyStudentAt(int at)
{
    Student* student;
    int pom = 0;
    for(int i = 0; i < studenci.size(); i++){
        if(!studenci.at(i)->getCzyPrzydzielonyDoGrupy())
        {
            if(pom == at){
                student = studenci.at(i);
                break;
            }
            else
                pom ++;
        }
    }

    return student;
}

Rok *Silnik::getRokAt(int at)
{
    if(at >= 0 && at < listaLat.size()){
        return listaLat.at(at);
    }else
        return NULL;
}


Silnik::Silnik()
{
    Semestr* pierwszy = new Semestr(QDate(1993,1,15),QDate(1993,6,20));
    Semestr* drugi = new Semestr(QDate(1994,1,15),QDate(1994,6,15));
    Rok* rok = new Rok(pierwszy,drugi);

    Semestr* pierwszy2 = new Semestr(QDate(1995,1,15),QDate(1995,6,15));
    Semestr* drugi2 = new Semestr(QDate(1996,1,15),QDate(1996,6,15));
    Rok* rok2 = new Rok(pierwszy2,drugi2);

    Semestr* pierwszy3 = new Semestr(QDate(1997,1,15),QDate(1997,6,15));
    Semestr* drugi3 = new Semestr(QDate(1998,1,15),QDate(1998,8,15));
    Rok* rok3 = new Rok(pierwszy3,drugi3);

    QList<SkladowaPrzedmiotu> list;
    list<<Egzamin<<Projekt;
    Przedmiot* przed1 = new Przedmiot("programowanie","takie tam sobie","pjc",list,2);
    Przedmiot* przed2 = new Przedmiot("progr","tlakdjflkdjf sobie","aup",list,3);
    Przedmiot* przed3 = new Przedmiot("scada","takie zbiorniczki","scada",list,4);

    Pracownik* prac1 = new Pracownik("air","doktor","1432","grzes","inny","chacina","1893839283","email",QDate(1993,12,12));
    Pracownik* prac2 = new Pracownik("imd","dprof","12","grzsdf","isfsds","csdfdsfa","1sdsd839283","edsfsdil",QDate(1993,1,12));
    Pracownik* prac3 = new Pracownik("mech","doktoras","153","krzys","nowyy","klimena","18252349283","mailosil",QDate(1993,12,12));

    EdycjaPrzedmotu* ed1 =new EdycjaPrzedmotu(przed2,prac1);
    EdycjaPrzedmotu* ed2 =new EdycjaPrzedmotu(przed1,prac2);
    EdycjaPrzedmotu* ed3 =new EdycjaPrzedmotu(przed3,prac3);

    Grupa* gr1 =new Grupa("pier","automaty","mechatro","rokb",rok,1,2);
    Grupa* gr2 =new Grupa("dru","ak","mechatro","rokb",rok2,3,2);
    Grupa* gr3 =new Grupa("trze","tomaty","madfatro","roksd",rok2,3,2);
    Grupa* gr4 =new Grupa("czwar","aty","mecsdfo","rodsd",rok2,4,2);

    Student* stu1 = new Student(2583930,40,"mat","piny","eccina","11899283","qedaail",QDate(1993,12,12));
    Student* stu2 = new Student(2583930,40,"bat","diny","crcina","12899283","ewdaail",QDate(1993,2,15));
    Student* stu3 = new Student(2583930,40,"tat","idny","cctina","18399283","edeaail",QDate(1993,4,14));
    Student* stu4 = new Student(2583930,40,"sat","indsy","ccyyina","14899283","ertdaail",QDate(1993,2,11));
    Student* stu5 = new Student(2583930,40,"pat","inya","ccinau","18995283","edaaiyl",QDate(1993,2,13));
    Student* stu6 = new Student(2583930,40,"kat","insy","ccinai","18992683","edaailu",QDate(1993,2,19));

    gr1->addStudent(stu1);
    gr1->addStudent(stu2);
    gr1->addStudent(stu3);
    gr1->addStudent(stu4);
    gr1->addStudent(stu5);
    gr1->addStudent(stu6);
    gr2->addStudent(stu1);

    rok->dodajEdycjePrzedmiotu(ed1,1);
    rok->dodajEdycjePrzedmiotu(ed2,1);
    rok->dodajEdycjePrzedmiotu(ed3,1);

    listaLat.clear();
    listaLat << rok << rok2 << rok3;
    listaPrzedm << przed1 << przed2 << przed3;
    pracownicy << prac1 << prac2<< prac3;

    rok->adPracownik(prac1);
    rok->adPracownik(prac2);
    rok->adPracownik(prac3);
    rok2->adGrupa(gr1);
    rok2->adGrupa(gr2);
    rok2->adGrupa(gr3);
    rok2->adGrupa(gr4);

}

Silnik::~Silnik()
{

}

