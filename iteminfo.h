#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QWidget>
#include "product.h"
#include <QHBoxLayout>
#include "live.h"
#include "food.h"
#include "elec.h"
#include "user.h"

namespace Ui {
class ItemInfo;
}

class ItemInfo : public QWidget
{
    Q_OBJECT
    
public:
    explicit ItemInfo(Product *pro, User *user, QWidget *parent = 0);
    ~ItemInfo();
    QHBoxLayout *outBox;
    User *user;
    Product *pro;
signals:
    void updateSignal();
private slots:
    void on_buyBtn_clicked();
    void update();

    void on_changeBtn_clicked();

private:
    Ui::ItemInfo *ui;
};

#endif // ITEMINFO_H
