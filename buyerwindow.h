#ifndef BUYERWINDOW_H
#define BUYERWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include "product.h"
#include "itemtable.h"
#include "headwidget.h"
#include "user.h"

namespace Ui {
class BuyerWindow;
}

class BuyerWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit BuyerWindow(QString theName, QMap<QString, User*> *db, QWidget *parent = 0);
    ~BuyerWindow();
    
private:
    QString name;
    Ui::BuyerWindow *ui;
    itemTable *myTable;
    HeadWidget *head;
    QVBoxLayout *outBox;
public slots:
    void logIn();
    void searchMine(QString name);
    void changeItem(Product * pro);
    void loginSuccess(QString theName);
    void update();
private slots:
    void on_searchBtn_clicked();
};

#endif // BUYERWINDOW_H
