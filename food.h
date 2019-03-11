#ifndef FOOD_H
#define FOOD_H
#include"product.h"
#include<QDate>

class Food : public Product
{
public:
    Food();
    Food(QTextStream &qStr);
    Food(QString newName, int newAmount, double newPrice, QString newOwner);
    Food(QString newName, int newAmount, double newPrice, QString newOwner, int newType);
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
    double reductRate; //¹Ì¶¨µÄ´òÕÛ
};

#endif // FOOD_H
