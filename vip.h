#ifndef VIP_H
#define VIP_H
#include"buyer.h"

class Vip : public Buyer
{
public:
    Vip();
    Vip(QString name, QString word); //用于新建一个VIP对象
    Vip(QString name, QString word, int t); //用于帮助子类的对象设置成员值
    Vip(QTextStream &stream);
    int getLevel(){return level;}
    int getToken(){return token;}
    void clearToken(){token = 0;}
    QTextStream& toStream(QTextStream &stream);
    QTextStream& operator>>(QTextStream &stream);
    void debug();
private:
    int token;
    int level;
};

#endif // VIP_H
