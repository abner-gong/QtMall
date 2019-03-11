#include "buyer.h"

Buyer::Buyer()
{
}

Buyer::Buyer(QString name, QString word):User(name,word,1)
{
}

Buyer::Buyer(QString name, QString word, int t):User(name,word,t)
{
}


Buyer::Buyer(QTextStream &stream):User(stream)
{
    setType(1);
}

void Buyer::buy()
{
}

QTextStream& Buyer::operator>>(QTextStream &stream)
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream<<1<<" ";
    toStream(stream);
    return stream;
}
