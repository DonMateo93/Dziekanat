#include "rok.h"

QString Rok::getRok()
{
    QString start = QString::number(pierwszy->getStart().year());
    QString stop = QString::number(drugi->getStart().year());
    return (start + "/" + stop);
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

Semestr::Semestr(QDate st, QDate en):start(st), end(en)
{

}
