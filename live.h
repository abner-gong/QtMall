#ifndef LIVE_H
#define LIVE_H

#include"Product.h"
#include<QDate>

class Live : public Product
{
public:
    Live();
    Live(QTextStream &qStr):Product(qStr),deadDay(Product::getDate(qStr))
    {setType(3);};
    Live(QString newName, int newAmount, double newPrice, QString newOwner);
    Live(QString newName, int newAmount, double newPrice, QString newOwner, int newType);
    QTextStream& operator>>(QTextStream &stream);
    QTextStream& toStream(QTextStream &stream);
    double calcPrice();
    //QTextStream& operator>>(QTextStream &stream);

    QDate getDeadDay(){return deadDay;}
    void setDeadDay(QDate d){deadDay = d;}
private:
    QDate deadDay;
};

#endif // LIVE_H
