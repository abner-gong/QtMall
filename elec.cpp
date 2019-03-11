#include "elec.h"

Elec::Elec():Product(),bornDay(QDate::currentDate()),deadDay(QDate::currentDate()),reductDay(QDate::currentDate())
{
    setType(2);
    reductRate = 0.1;
}
double Elec::calcPrice()
{
    QDate today = QDate::currentDate();
    if(today<bornDay) return -2;
    else if(today<reductDay) return getPrice();
    else if(today<deadDay)
    {
        double temp = 1-getReductRate()*getReductDay().daysTo(today);
        temp = temp<0.1?0.1:temp;
        return getPrice()*temp;
    }
    else return -1;
}
QTextStream& Elec::toStream(QTextStream &stream)
{
    Product::toStream(stream);
    Product::printDate(stream,deadDay);
    stream<<" ";
    Product::printDate(stream,bornDay);
    stream<<" ";
    Product::printDate(stream,reductDay);
    stream<<" ";
    stream<<reductRate;
    stream<<" ";
    return stream;
}
