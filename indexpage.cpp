#include "indexpage.h"
#include "ui_indexpage.h"

IndexPage::IndexPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndexPage)
{
    ui->setupUi(this);
}

IndexPage::~IndexPage()
{
    delete ui;
}
