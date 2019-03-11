#include "welcomedialog.h"


WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QWidget(parent)
{
    nameLabel = new QLabel(tr("name:"));
    nameLineText = new QLineEdit();
    passwordLabel = new QLabel(tr("password:"));
    passwordLineText = new QLineEdit();
    passwordLineText->setEchoMode(QLineEdit::Password);
    logBtn = new QPushButton(tr("Log in"));
    boxVH1 = new QHBoxLayout;
    boxVH1->addWidget(nameLabel);
    boxVH1->addWidget(nameLineText);
    boxVH1->addWidget(passwordLabel);
    boxVH1->addWidget(passwordLineText);
    boxVH1->addWidget(logBtn);

    passwordConfirmLabel = new QLabel(tr("confirm your password:"));
    QLineEdit *passwordConfirm = new QLineEdit();
    QPushButton *regBtn = new QPushButton(tr("Register"));
    QHBoxLayout *boxVH2 = new QHBoxLayout;
    boxVH2->addWidget(passwordConfirmLabel);
    boxVH2->addWidget(passwordConfirm);
    boxVH2->addWidget(regBtn);

    QVBoxLayout *boxV = new QVBoxLayout;
    boxV->addLayout(boxVH1);
    boxV->addLayout(boxVH2);
    setLayout(boxV);
}
