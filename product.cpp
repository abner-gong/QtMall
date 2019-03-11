#include "product.h"
#include "elec.h"
#include "food.h"
#include "live.h"

int Product::idnum;
QMap<int, Product*> itemdb;

Product::Product():amount(0),price(0.0)
{
}

Product::Product(QTextStream &qStr):type(0)
{
    qStr>>id>>name>>amount>>price>>owner;
}
Product::Product(QString newName, int newAmount, double newPrice, QString newOwner)
    :id(Product::idnum++),name(newName),amount(newAmount),price(newPrice),owner(newOwner)
{
}

Product::Product(QString newName, int newAmount, double newPrice, QString newOwner, int newType)
    :id(Product::idnum++),name(newName),amount(newAmount),price(newPrice),owner(newOwner),type(newType)
{
}
QTextStream& Product::toStream(QTextStream &stream) //这是用来输出到流里的
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream<<id<<" ";
    stream<<name<<" ";
    stream<<amount<<" ";
    stream<<price<<" ";
    stream<<owner<<" ";
    stream.setFieldWidth(0);
    return stream;
}
QTextStream& Product::operator>>(QTextStream &stream)
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream<<getType()<<" ";
    stream.setFieldWidth(0);
    toStream(stream);
    return stream;
}
void Product::initialItemdb()
{
    QFile inFile("iteminfo.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {   qDebug()<<"用户数据无法打开";
        return;
    }
    QTextStream inStream(&inFile);
    while(!inStream.atEnd())
    {
        QString str = inStream.readLine();
        qDebug()<<str;
        QTextStream strStream(&str);
        int flag;
        strStream>>flag;
        Product *product;
        Live *live;
        Food *food;
        Elec *elec;
        switch(flag)
        {/*case 0:
            product = new Product(strStream);
            userdb[product->getId()] = product;
            break;*/
         case 1:
            food = new Food(strStream);
            itemdb[food->getId()] = food;
            break;
         case 2:
            elec = new Elec(strStream);
            itemdb[elec->getId()] = elec;
            break;
         case 3:
            live = new Live(strStream);
            itemdb[live->getId()] = live;
            break;
        }
    }
    inFile.close();
    Product::idnum = itemdb.count()+1;
}
void Product::saveItemdb()
{
    QFile ouFile("iteminfo.txt");
    if (!ouFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {   qDebug()<<"用户数据无法打开";
        return;
    }
    QTextStream ouStream(&ouFile);
    foreach(Product* item, itemdb)
        ((*item)>>ouStream)<<endl;
    ouFile.close();
}
