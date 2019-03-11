#ifndef SELLER_H
#define SELLER_H

#include"User.h"
#include<QList>
class Item;

class Seller : public User
{
public:
    Seller();
    Seller(QString name, QString word);
    Seller(QString name, QString word, int t);
    Seller(QTextStream &stream);
    QList<Item> queryMine();
    void addItem();
    QTextStream& operator>>(QTextStream &stream);
    QMap<int, Product*> *getItems(QMap<int, Product*> *db);
};

#endif // SELLER_H
