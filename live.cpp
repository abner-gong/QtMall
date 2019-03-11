#include "live.h"

Live::Live():Product(),deadDay(QDate::currentDate())
{
    setType(3);
}
double Live::calcPrice()
{
    QDate today = QDate::currentDate();
    if(today<deadDay) return getPrice();
    else return -1;
}
QTextStream& Live::toStream(QTextStream &stream)
{
    Product::toStream(stream);
    Product::printDate(stream,deadDay);
    stream<<" ";
    return stream;
}
