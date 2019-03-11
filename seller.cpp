#include "seller.h"

Seller::Seller()
{
}

Seller::Seller(QString name, QString word):User(name,word,3)
{
}

Seller::Seller(QString name, QString word, int t):User(name,word,t)
{
}

Seller::Seller(QTextStream &stream):User(stream)
{
    setType(3);
}

QTextStream& Seller::operator>>(QTextStream &stream)
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream<<3<<" ";
    toStream(stream);
    return stream;
}
QMap<int, Product*> *Seller::getItems(QMap<int, Product*> *db)
{
    return User::getItems(getUserName(), db);
}
