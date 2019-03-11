#include "vip.h"

Vip::Vip()
{
}

Vip::Vip(QString name, QString word):Buyer(name,word)
{
    type = 2;
}
Vip::Vip(QString name, QString word, int t):Buyer(name,word,t)
{
}

Vip::Vip(QTextStream &stream):Buyer(stream)
{
  stream>>token>>level;
  setType(2);
  return;
}

QTextStream& Vip::toStream(QTextStream &stream) //这是用来输出到文件的，会输出类型标志0
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    Buyer::toStream(stream);
    stream<<token<<" ";
    stream<<level<<" ";
    stream.setFieldWidth(0);
    return stream;
}

QTextStream& Vip::operator>>(QTextStream &stream)
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream<<2<<" ";
    toStream(stream);
    stream.setFieldWidth(0);
    return stream;
}

void Vip::debug()
{
    User::debug();
    qDebug()<<token<<" "<<level<<" ";
}
