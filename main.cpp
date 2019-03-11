#include <QApplication>
#include "seller.h"
#include "vip.h"
#include "welcomedialog.h"
#include "welcomewidget.h"
#include "QDate"
#include "live.h"
#include "food.h"
#include "elec.h"
#include "itemtable.h"
#include "QTableWidget"
#include "QTextCodec"
#include "buyerwindow.h"


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    QApplication a(argc, argv);
    User::initialUserdb();
    User::saveUserdb();
    Product::initialItemdb();
    Product::saveItemdb();
    BuyerWindow w("gonghe",&userdb);
    w.show();
    return a.exec();
}

