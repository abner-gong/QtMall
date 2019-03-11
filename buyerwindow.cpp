#include "buyerwindow.h"
#include "ui_buyerwindow.h"
#include "itemtable.h"
#include "product.h"
#include <QPushButton>
#include "QDebug"
#include "user.h"
#include "welcomewidget.h"
#include "seller.h"

BuyerWindow::BuyerWindow(QString theName, QMap<QString, User*> *db, QWidget *parent) :
    name(theName),
    QWidget(parent),
    ui(new Ui::BuyerWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ëº´Ð¹ºÎïÍø");
    outBox = new QVBoxLayout;
    head = new HeadWidget(name);
    myTable = new itemTable(&itemdb);
    outBox->addWidget(head);
    outBox->addWidget(ui->horizontalLayoutWidget);
    outBox->addWidget(myTable);
    setLayout(outBox);
    connect(head, SIGNAL(logInSignal()), this, SLOT(logIn()));
    connect(head, SIGNAL(searchMine(QString)), this, SLOT(searchMine(QString)));
    connect(head, SIGNAL(loginSuccessSignal(QString)), this, SLOT(loginSuccess(QString)));
    connect(head, SIGNAL(updateSignal()), this, SLOT(update()));
    connect(head, SIGNAL(updateSignal()), myTable, SLOT(update()));
    connect(myTable,SIGNAL(changeItemSignal(Product*)), this, SLOT(changeItem(Product*)));
    connect(myTable, SIGNAL(updateSignal()), this, SLOT(update()));
}

BuyerWindow::~BuyerWindow()
{
    delete ui;
}

void BuyerWindow::logIn()
{
    this->setAttribute(Qt::WA_ShowWithoutActivating,true);
}


void BuyerWindow::on_searchBtn_clicked()
{
    QMap<int, Product*> *searchdb = userdb[name]->getItems(ui->searchEdit->text(), &itemdb);
    delete myTable;
    myTable = new itemTable(searchdb);
    outBox->addWidget(myTable);
    myTable->setVisible(true);
    connect(myTable,SIGNAL(changeItemSignal(Product*)), this, SLOT(changeItem(Product*)));
}

void  BuyerWindow::searchMine(QString name)
{
    QMap<int, Product*> *searchdb = dynamic_cast<Seller*>(userdb[name])->getItems(&itemdb);
    delete myTable;
    myTable = new itemTable(searchdb);
    outBox->addWidget(myTable);
    myTable->setVisible(true);
    connect(myTable,SIGNAL(changeItemSignal(Product*)), this, SLOT(changeItem(Product*)));
}
void BuyerWindow::changeItem(Product *pro)
{
    ItemInfo *infoWidget = new ItemInfo(pro, userdb[name]);
    infoWidget->show();
    infoWidget->setWindowModality(Qt::ApplicationModal);
    connect(infoWidget, SIGNAL(updateSignal()), myTable, SLOT(update()));
}
void BuyerWindow::loginSuccess(QString theName)
{
    name = theName;
}
void BuyerWindow::update()
{   qDebug()<<"SLOT:BuyerWindow::update()";
    User::saveUserdb();
    Product::saveItemdb();
}
