#ifndef PRODUCT_H
#define PRODUCT_H
#ifndef FIELDWIDTH
#define FIELDWIDTH 3
#endif

#include <QString>
#include <QTextStream>
#include <QDate>
#include <QFile>
#include <QDebug>
#include <QMap>

class Product;

extern QMap<int, Product*> itemdb;

class Product
{
public:
    Product();
    Product(QTextStream &qStr);
    Product(QString newName, int newAmount, double newPrice, QString newOwner);
    Product(QString newName, int newAmount, double newPrice, QString newOwner, int newType);
    virtual QTextStream& toStream(QTextStream &stream);
    QTextStream& operator>>(QTextStream &stream);

    static void initialItemdb();
    static void saveItemdb();

    int getId(){return id;}
    void setId(int newId){id = newId;}
    QString getName(){return name;}
    void setName(QString newName){name = newName;}
    int getAmount(){return amount;}
    void decreaseAmount(int i){amount -= i;}
    void setAmount(int newAmount){amount = newAmount;}
    double getPrice(){return price;}
    void setPrice(double newPrice){price = newPrice;}
    QString getOwner(){return owner;}
    void setOwner(QString newOwner){owner = newOwner;}
    int getType(){return type;}
    void setType(int newType){type = newType;}
    virtual double calcPrice()=0;
    static QDate getDate(QTextStream &qstr){QString str; qstr>>str; return QDate::fromString(str,"yyyy-M-d");}
    static void printDate(QTextStream &qstr, QDate date){QString str = date.toString("yyyy-M-d"); qstr<<str;}
    static int idnum;
private:
    int id;
    QString name;
    int amount;
    double price;
    QString owner;
    int type;
};

#endif // PRODUCT_H
