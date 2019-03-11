#include "selectitemtype.h"
#include "ui_selectitemtype.h"

SelectItemType::SelectItemType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectItemType)
{
    ui->setupUi(this);

}

SelectItemType::~SelectItemType()
{
    delete ui;
}

void SelectItemType::on_pushButton_clicked()
{
    if(ui->radioFood->isChecked()) emit getType(ui->nameEdit->text(), 1);
    else if(ui->radioElec->isChecked()) emit getType(ui->nameEdit->text(), 2);
    else if(ui->radioLive->isChecked()) emit getType(ui->nameEdit->text(), 3);
    close();
}
