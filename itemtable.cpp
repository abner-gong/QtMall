#include "itemtable.h"
#include "ui_itemtable.h"
#include "QHBoxLayout"

itemTable::itemTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemTable)
{
    ui->setupUi(this);
}

itemTable::itemTable(QMap<int, Product*> *db, QWidget *parent) :
    currentdb(db),
    QWidget(parent),
    ui(new Ui::itemTable)
{
    ui->setupUi(this);
    QHBoxLayout *outBox = new QHBoxLayout;
    outBox->addWidget(ui->tableWidget);
    setLayout(outBox);
    //ui->tableWidget->setRowCount(Product::idnum);
    update();
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(changeItem(int,int)));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void itemTable::changeItem(int row, int column)
{
    emit changeItemSignal((*currentdb)[ui->tableWidget->item(row,1)->text().toInt()]);
}

itemTable::~itemTable()
{
    delete ui;
}

void itemTable::on_tableWidget_doubleClicked(const QModelIndex &index)
{

}
void itemTable::update()
{
    qDebug()<<"SLOT:itemTable::update()";
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(10);
    QStringList headerString;
    headerString<<"现价"<<"Id"<<tr("名称")<<"Stock"<<"原价"<<"Seller"<<"过期时间"<<"生产日期"<<"降价日期"<<"因子";
    ui->tableWidget->setHorizontalHeaderLabels(headerString);

    foreach(Product *p, *currentdb)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QString tempstr;
        QTextStream tempstream(&tempstr);
        tempstream<<p->calcPrice()<<" ";
        p->toStream(tempstream);
        int column = 0;
        while(!tempstream.atEnd())
        {
            QString pp;
            tempstream>>pp;
            QTableWidgetItem *newItem = new QTableWidgetItem(pp);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, column, newItem);
            column++;
        }
    }
    emit updateSignal();
}
