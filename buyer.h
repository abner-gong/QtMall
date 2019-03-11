#ifndef BUYER_H
#define BUYER_H

#include"user.h"


class Buyer : public User
{
public:
    Buyer();
    Buyer(QString name, QString word);
    Buyer(QString name, QString word, int t);
    Buyer(QTextStream &stream);
    void buy();
    QTextStream& operator>>(QTextStream &stream);
};

#endif // BUYER_H
