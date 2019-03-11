#ifndef USER_H
#define USER_H
#ifndef FIELDWIDTH
#define FIELDWIDTH 3
#endif

#include <QString>
#include <QFile>
#include <QObject>
#include <QDebug>
#include <QVector>
#include "product.h"


class User;

extern QMap<QString, User*> userdb; //û��������Ϊ��̬��������Ϊ��̬����Ҫ���þ�̬�����������������externҲһ���ˡ�

class User
{
public:
    User();
    User(QString name, QString word);
    User(QString name, QString word, int t);
    QString getUserName(){return userName;}

    QMap<int, Product*> *getItems(QString str, QMap<int, Product*> *db);

    int getId(){return id;}
    QString getPassword(){return password;}
    double getBalance(){return balance;}
    void addBalance(double addb){balance += addb;}
    static int logIn(QString uname, QString upass);
    static int regIn(QString uname, QString upass, int t);
    int logOut();
    int showItems();
    User(QTextStream &stream);
    virtual QTextStream& operator>>(QTextStream &stream);
    virtual QTextStream& toStream(QTextStream &stream);
    virtual void debug();
    QString toStr();
    static QMap<QString, User*> udb;
    //static void test();
    static int idnum; //id����
    int getType();
    void setType(int t);
    static void initialUserdb();
    static void saveUserdb();
protected:
    int type;
private:
    int id;
    QString userName;
    QString password;
    double balance;
};

#endif // USER_H
