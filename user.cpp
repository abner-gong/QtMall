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
{ //��ϣ����ʼʱ��һ��vector<User>��Ȼ��logIn�ǵ��������ȥ�ң�������ȶ���User����ܶ���vector<User>�������logIn
  //����Ϊ�˰�logIn���ϵ�User��ҿ��԰�logIn��ΪUser�ľ�̬��������̬���ⲿû����Ҳ���԰�vector<User>��Ϊ���ľ�̬������Ա
  //����ǡǡ��logIn���ܷ���vector<User>��Ϊɶ��̬��Ա�������ܷ��ʾ�̬��Ա��������֪��
    if(userdb.contains(uname))
    {
        if(userdb.value(uname)->password == upass) return 1; //��¼�ɹ�
        else return 0;//�������
    }
    else
        return -1; //����������û�
}

int User::regIn(QString uname, QString upass, int type)
{  if(!userdb.contains(uname))
    {
        if(type==1) userdb[uname]=new Buyer(uname, upass);
        else if(type==3) userdb[uname]=new Seller(uname, upass);
        else return -1;
        User::saveUserdb();
        return 1; //��¼�ɹ�
    }
    else
        return 0; //����������û�
}

QTextStream& User::toStream(QTextStream &stream) //������������������
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

QTextStream& User::operator>>(QTextStream &stream) //��������������ļ��ģ���������ͱ�־0
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
    {   qDebug()<<"�û������޷���";
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
    {   qDebug()<<"�û������޷���";
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
    {  //��ÿ��prod�����ַ�������str�е��ֶΰ������

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
            //�����а�ȫ������Ӧ�ø�ÿ��������һ�����ƺ�����Ȼ����һ��������ӽ���
            //����ΪUser(*prod)������ƺ������ܲ��Զ�����
        }
    }
    return tempdb;
}
