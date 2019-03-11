#include "welcomewidget.h"
#include "ui_welcomewidget.h"
#include "QMap"
#include "User.h"
extern QMap<QString, User*> userdb;

WelcomeWidget::WelcomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeWidget)
{

    ui->setupUi(this);
    vBox = new QVBoxLayout;
    vBox->addWidget(ui->layoutWidget);
    setLayout(vBox);
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}

void WelcomeWidget::on_loginBtn_clicked()
{
    QString name(ui->nameLine->text());
    QString password(ui->pwdLine->text());
    switch (User::logIn(name,password)){
    case 1:ui->hintLabel->setText(tr(""));emit loginSuccess(name);close();break;
    case 0:ui->hintLabel->setText(tr("password wrong"));break;
    case -1:ui->hintLabel->setText(tr("not exists"));break;
    }
}

void WelcomeWidget::on_regBtn_clicked()
{
    QString name(ui->nameLine->text());
    QString password(ui->pwdLine->text());
    QString password2(ui->pwd2Line->text());
    if(password != password2)
    {
        ui->hintLabel->setText(tr("different"));
        return;
    }
    int type;
    if(ui->radioBuyer->isChecked()) type = 1;
    else type = 3;
    switch (User::regIn(name,password,type)){
    case 1:ui->hintLabel->setText(tr("success"));emit loginSuccess(name);close();break;
    case 0:ui->hintLabel->setText(tr("name exists"));break;
    case -1:ui->hintLabel->setText(tr("choose radio"));break;
    }
}
