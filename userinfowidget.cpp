#include "userinfowidget.h"
#include "ui_userinfowidget.h"
#include "vip.h"
#include "seller.h"

UserInfoWidget::UserInfoWidget(User* theUser, QWidget *parent) :
    user(theUser),
    QWidget(parent),
    ui(new Ui::UserInfoWidget)
{
    ui->setupUi(this);
    outBox = new QHBoxLayout();
    outBox->addWidget(ui->verticalLayoutWidget);
    setLayout(outBox);
    ui->idLabel->setText(QString("����ID��%1").arg(user->getId()));
    ui->nameLabel->setText(QString("�����ǳƣ�%1").arg(user->getUserName()));
    ui->balanceLabel->setText(QString("�˻���%1").arg(QString().setNum(user->getBalance())));
    if(user->getType()==2)
    {
        Vip* vip = dynamic_cast<Vip*>(user);
        ui->tokenLabel->setText(QString("˺ȯ������%1").arg(QString().setNum(vip->getToken())));
        ui->levelLabel->setText(QString("��Ա�ȼ���%1").arg(QString().setNum(vip->getLevel())));
        ui->turnButton->setVisible(true);
        ui->tokenLabel->setVisible(true);
        ui->levelLabel->setVisible(true);
    }
    else
    {
        ui->turnButton->setVisible(false);
        ui->tokenLabel->setVisible(false);
        ui->levelLabel->setVisible(false);
    }
}

UserInfoWidget::~UserInfoWidget()
{
    delete ui;
}

void UserInfoWidget::on_addBtn_clicked()
{
    userdb[user->getUserName()]->addBalance(ui->balanceEdit->text().toDouble());
    ui->balanceLabel->setText(QString("�˻���%1").arg(QString().setNum(user->getBalance())));
    ui->balanceEdit->setText("");
    User::saveUserdb();
}

void UserInfoWidget::on_turnButton_clicked()
{
    Vip *vip = dynamic_cast<Vip*>(userdb[user->getUserName()]);
    vip->addBalance(vip->getToken()*0.1);
    vip->clearToken();
    ui->balanceLabel->setText(QString("�˻���%1").arg(QString().setNum(vip->getBalance())));
    ui->tokenLabel->setText("˺ȯ������0");
    User::saveUserdb();
}
