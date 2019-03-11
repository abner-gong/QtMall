#ifndef ELEC_H
#define ELEC_H

#include"Product.h"
#include"QDate"

class Elec : public Product
{
public:
    Elec();
    Elec(QTextStream &qStr):Product(qStr),deadDay(Product::getDate(qStr)),bornDay(Product::getDate(qStr)),reductDay(Product::getDate(qStr))
    {qStr>>reductRate; setType(2);}
    Elec(QString newName, int newAmount, double newPrice, QString newOwner);
    Elec(QString newName, int newAmount, double newPrice, QString newOwner, int newType);
    double calcPrice();
    QTextStream& toStream(QTextStream &stream);
    //QTextStream& operator>>(QTextStream &stream);

    QDate getBornDay(){return bornDay;}
    void setBornDay(QDate d){bornDay = d;}
    QDate getDeadDay(){return deadDay;}
    void setDeadDay(QDate d){deadDay = d;}
    QDate getReductDay(){return reductDay;}
    void setReductDay(QDate d){reductDay = d;}
    double getReductRate(){return reductRate;}
    void setReductRate(double rate){reductRate = rate;}

private:
    QDate deadDay;
    QDate bornDay;
    QDate reductDay;
    double reductRate;
};

#endif // ELEC_H
