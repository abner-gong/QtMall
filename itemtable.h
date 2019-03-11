#ifndef ITEMTABLE_H
#define ITEMTABLE_H

#include <QWidget>
#include "product.h"
#include <QMap>
#include <QDebug>
#include "ui_itemtable.h"
#include "iteminfo.h"

namespace Ui {
class itemTable;
}

class itemTable : public QWidget
{
    Q_OBJECT
    
public:
    explicit itemTable(QWidget *parent = 0);
    explicit itemTable(QMap<int, Product*> *db, QWidget *parent = 0);
    ~itemTable();
    QMap<int, Product*> *currentdb;
signals:
    void changeItemSignal(Product *pro);
    void updateSignal();
private slots:
    void changeItem(int row, int column);
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void update();
private:
    Ui::itemTable *ui;

};

#endif // ITEMTABLE_H
