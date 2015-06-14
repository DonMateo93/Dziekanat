#ifndef ROK_H
#define ROK_H

#include <QDate>

class Semestr
{
    QDate start;
    QDate end;
public:
};

class Rok
{
    Semestr* pierwszy;
    Semestr* drugi;
public:
    Rok();
    ~Rok();
};

#endif // ROK_H
