#include "headwidget.h"
#include "ui_headwidget.h"
#include "user.h"
#include "seller.h"
#include "QStackedLayout"
#include "welcomewidget.h"
#include "userinfowidget.h"
#include "selectitemtype.h"

HeadWidget::HeadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeadWidget)
{
    ui->setupUi(this);
}

HeadWidget::HeadWidget(QString theName, QWidget *parent) :
    name(theName),
    QWidget(parent),
    ui(new Ui::HeadWidget)
{
    ui->setupUi(this);
    outBox = new QStackedLayout;
    outBox->insertWidget(0,ui->horizontalLayoutWidget);
    outBox->insertWidget(1,ui->horizontalLayoutWidget_2);
    setLayout(outBox);
    ui->nameLabel->setText(QString("%1£¬ÄúºÃ£¡").arg(name));
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    outBox->setCurrentIndex(0);
    connect(ui->loginBtn, SIGNAL(clicked()), this, SLOT(logIn()));
    connect(ui->logoutBtn, SIGNAL(clicked()), this, SLOT(logOut()));
    connect(ui->checkBtn, SIGNAL(clicked()), this, SLOT(checkInfo()));
    logOut();
}


HeadWidget::~HeadWidget()
{
    delete ui;
}


void HeadWidget::logOut()
{
    outBox->setCurrentIndex(1);
}

void HeadWidget::logIn()
{
    WelcomeWidget *m = new WelcomeWidget();
    connect(m, SIGNAL(loginSuccess(QString)), this, SLOT(loginSuccess(QString)));
    emit logInSignal();
    m->setWindowModality(Qt::ApplicationModal);
    m->show();
}
void HeadWidget::loginSuccess(QString theName)
{
    outBox->setCurrentIndex(0);
    ui->nameLabel->setText(QString("%1 ÄúºÃ£¡").arg(theName));
    name = theName;
    if(userdb[name]->getType()==3)
    {
        ui->mineBtn->setVisible(true);
        ui->addItemBtn->setVisible(true);
    }
    else
    {
        ui->mineBtn->setVisible(false);
        ui->addItemBtn->setVisible(false);
    }
    emit loginSuccessSignal(name);
}

void HeadWidget::checkInfo()
{
    UserInfoWidget *info = new UserInfoWidget(userdb[name]);
    info->setWindowModality(Qt::ApplicationModal);
    info->show();
}


void HeadWidget::on_mineBtn_clicked()
{
    emit searchMine(name);
}

void HeadWidget::on_addItemBtn_clicked()
{
    SelectItemType *tmpDialog = new SelectItemType();
    tmpDialog->show();
    connect(tmpDialog, SIGNAL(getType(QString, int)),this, SLOT(createPro(QString, int)));
    //ItemInfo *itemWindow = new ItemInfo(userdb[name]);
    //itemWindow->show();
}
void HeadWidget::createPro(QString theName, int t)
{
    switch(t)
    {
    case 1:itemdb[Product::idnum++]=new Food();
        break;
    case 2:itemdb[Product::idnum++]=new Elec();
        break;
    case 3:itemdb[Product::idnum++]=new Live();
        break;
    }
    itemdb[Product::idnum-1]->setName(theName);
    itemdb[Product::idnum-1]->setId(Product::idnum-1);
    itemdb[Product::idnum-1]->setOwner(name);
    ItemInfo *newItem = new ItemInfo(itemdb[Product::idnum-1],userdb[name]);
    connect(newItem, SIGNAL(updateSignal()), this, SLOT(update()));
    newItem->show();
}

void HeadWidget::update()
{
    qDebug()<<"SLOT:HeadWidget::update()";
    emit updateSignal();
}
