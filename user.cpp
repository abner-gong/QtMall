#include "user.h"
#include "buyer.h"
#include "seller.h"
#include "vip.h"
#include <QMessageBox>

int User::idnum = 0;
QMap<QString, User*> userdb;
int User::getType() {     return type; }
void User::setType(int t) {   type = t; }

User::User():id(0),userName(""),password(""),balance(0),type(0) { }
User::User(QTextStream &stream)
{

    type = 0;
    stream>>id;
    stream>>userName;
    stream>>password;
    stream>>balance;
}

User::User(QString name, QString word):type(0),userName(name),password(word),balance(0),id(User::idnum++)
{
}

User::User(QString name, QString word, int t = 0):type(t),userName(name),password(word),balance(0),id(User::idnum++)
{
}

int User::logIn(QString uname, QString upass)
{ //我希望初始时有一个vector<User>，然后logIn是到这个里面去找，则必须先定义User后才能定义vector<User>，最后定义logIn
  //但是为了把logIn整合到User里，我可以把logIn作为User的静态函数，静态和外部没区别，也可以把vector<User>作为它的静态变量成员
  //但是恰恰，logIn不能访问vector<User>，为啥静态成员函数不能访问静态成员变量？不知道
    if(userdb.contains(uname))
    {
        if(userdb.value(uname)->password == upass) return 1; //登录成功
        else return 0;//密码错误
    }
    else
        return -1; //不存在这个用户
}

int User::regIn(QString uname, QString upass, int type)
{  if(!userdb.contains(uname))
    {
        if(type==1) userdb[uname]=new Buyer(uname, upass);
        else if(type==3) userdb[uname]=new Seller(uname, upass);
        else return -1;
        User::saveUserdb();
        return 1; //登录成功
    }
    else
        return 0; //不存在这个用户
}

QTextStream& User::toStream(QTextStream &stream) //这是用来输出到流里的
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream<<id<<" ";
    stream<<userName<<" ";
    stream<<password<<" ";
    stream<<balance<<" ";
    stream.setFieldWidth(0);
    return stream;
}

QTextStream& User::operator>>(QTextStream &stream) //这是用来输出到文件的，会输出类型标志0
{
    stream.setFieldWidth(FIELDWIDTH);
    stream.setFieldAlignment(QTextStream::AlignLeft);
    stream<<getType()<<" ";
    stream.setFieldWidth(0);
    toStream(stream);
    return stream;
}



void User::debug()
{
    qDebug()<<id<<" "<<userName<<" "<<password<<" "<<balance<<" ";
}

/*void User::test()
{
    User *user = new User();
    udb[user->getUserName()] = user;
}
*/

void User::initialUserdb()
{
    try{
    QFile inFile("userinfo.txt");
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {   qDebug()<<"用户数据无法打开";
        throw QString("Userdb can't be open");
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
        if((flag<1)||(flag>3))
        {
            throw QString("Userdb is damaged");
            continue;
        }
        str = str.simplified();
        QStringList strList = str.split(" ");
        switch(flag)
        {
        case 1: case 3:
            if((strList.count()!= 5) )
            {
                throw QString("Userdb is damaged");
                continue;
            }
            break;
        case 2:
            if((strList.count()!= 7) )
            {
                throw QString("Userdb is damaged");
                continue;
            }
            break;
        }
        User *user;
        Buyer *buyer;
        Vip *vip;
        Seller *seller;
        switch(flag)
        {case 0:
            user = new User(strStream);
            userdb[user->getUserName()] = user;
            break;
         case 1:
            buyer = new Buyer(strStream);
            userdb[buyer->getUserName()] = buyer;
            break;
         case 2:
            vip = new Vip(strStream);
            userdb[vip->getUserName()] = vip;
            break;
         case 3:
            seller = new Seller(strStream);
            userdb[seller->getUserName()] = seller;
            break;
        }
    }
    inFile.close();
    User::idnum = userdb.count()+1;
    }
    catch(QString exception)
    {QMessageBox::about(0,"Error",exception);
    }
}

void User::saveUserdb()
{
    QFile ouFile("userinfo.txt");
    if (!ouFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {   qDebug()<<"用户数据无法打开";
        return;
    }
    QTextStream ouStream(&ouFile);
    foreach(User* user, userdb)
        ((*user)>>ouStream)<<endl;
    ouFile.close();
}

QMap<int, Product*> *User::getItems(QString str, QMap<int, Product*> *db)
{
    QMap<int, Product*> *tempdb = new QMap<int, Product*>;
    foreach(Product *prod, (*db))
    {  //对每个prod生成字符串并对str中的字段挨个检查

        QString prodStr("");
        QTextStream prodStream(&prodStr);
        prod->toStream(prodStream);

        QTextStream stream(&str);

        int flag = 1;

        while(!stream.atEnd())
        {
            QString pp;
            stream>>pp;
            if(pp=="") break;
            else
            {
                if(prodStr.indexOf(pp)==-1)
                {
                    flag = 0;
                    break;
                }
            }
        }

        if(flag == 1)
        {
            (*tempdb)[prod->getId()] = prod;
            //这里有安全隐患，应该给每个类重载一个复制函数，然后复制一个副本添加进来
            //我认为User(*prod)这个复制函数可能不自动重载
        }
    }
    return tempdb;
}
