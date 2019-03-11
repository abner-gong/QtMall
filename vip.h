#ifndef VIP_H
#define VIP_H
#include"buyer.h"

class Vip : public Buyer
{
public:
    Vip();
    Vip(QString name, QString word); //�����½�һ��VIP����
    Vip(QString name, QString word, int t); //���ڰ�������Ķ������ó�Աֵ
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
