#include "food.h"

Food::Food():Product(),bornDay(QDate::currentDate()),deadDay(QDate::currentDate()),reductDay(QDate::currentDate())
{
    setType(1);
    reductRate = 0.8;
}
Food::Food(QTextStream &qStr)
    :Product(qStr),deadDay(Product::getDate(qStr)),bornDay(Product::getDate(qStr)),reductDay(Product::getDate(qStr))
{
    qStr>>reductRate;
    setType(1);
}

double Food::calcPrice()
{
    QDate today = QDate::currentDate();
    if(today<bornDay) return -2;
    else if(today<reductDay) return getPrice();
    else if(today<deadDay) return getPrice()*getReductRate();
    else return -1;
}
QTextStream& Food::toStream(QTextStream &stream)
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
