#include "iteminfo.h"
#include "ui_iteminfo.h"
#include <QErrorMessage>
#include <QMessageBox>


ItemInfo::ItemInfo(Product *thePro, User* theUser, QWidget *parent) :
    pro(thePro),
    user(theUser),
    QWidget(parent),
    ui(new Ui::ItemInfo)
{
    ui->setupUi(this);
    outBox = new QHBoxLayout;
    outBox->addWidget(ui->gridLayoutWidget);
    setLayout(outBox);
    update();

}

ItemInfo::~ItemInfo()
{
    delete ui;
}

void ItemInfo::on_buyBtn_clicked()
{
    int i = ui->numberEdit->text().toInt();
    if(i>pro->getAmount())
    { QMessageBox *q = new QMessageBox();
      q->setText("对不起，库存不足，请减少购买数量");
      q->show();
    }
    else if(pro->calcPrice()<0)
    { QMessageBox *q = new QMessageBox();
      q->setText("对不起，此商品已过期，不能购买");
      q->show();
    }
    else if((i*pro->calcPrice())>user->getBalance())
    { QMessageBox *q = new QMessageBox();
      q->setText("对不起，余额不足，请充值后再购买");
      q->show();
    }
    else
    {
        user->addBalance(-i*pro->getPrice());
        userdb[ui->sellerLabel->text()]->addBalance(i*pro->calcPrice());
        pro->decreaseAmount(i);
        ui->numberEdit->setText("");
        update();
    }
}

void ItemInfo::update()
{
    ui->idEdit->setText(QString().setNum(pro->getId()));
    ui->nameEdit->setText(pro->getName());
    ui->priceEdit->setText(QString().setNum(pro->calcPrice()));
    ui->sellerLabel->setText(pro->getOwner());
    ui->stockEdit->setText(QString().setNum(pro->getAmount()));

    Food *food;
    Live *live;
    Elec *elec;
    switch(user->getType()){
    case 3: ui->buyBtn->setVisible(false);
        ui->changeBtn->setVisible(true);
        ui->numberEdit->setVisible(false);
    break;
    default: ui->buyBtn->setVisible(true);
        ui->changeBtn->setVisible(false);
        ui->numberEdit->setVisible(true);
    break;
    }

    switch(pro->getType()){
    case 1: food = dynamic_cast<Food*>(pro);
        ui->deadEdit->setDate(food->getDeadDay());
        ui->bornEdit->setDate(food->getBornDay());
        ui->reductDateEdit->setDate(food->getReductDay());
        ui->reductEdit->setText(QString().setNum(food->getReductRate()));
        ui->bornDateLabel->setVisible(true);
        ui->bornEdit->setVisible(true);
        ui->reductDateEdit->setVisible(true);
        ui->reductDateLabel->setVisible(true);
        ui->reductEdit->setVisible(true);
        ui->reductLabel->setVisible(true);
        break;
    case 2: elec = dynamic_cast<Elec*>(pro);
        ui->deadEdit->setDate(elec->getDeadDay());
        ui->bornEdit->setDate(elec->getBornDay());
        ui->reductDateEdit->setDate(elec->getReductDay());
        ui->reductEdit->setText(QString().setNum(elec->getReductRate()));
        ui->bornDateLabel->setVisible(true);
        ui->bornEdit->setVisible(true);
        ui->reductDateEdit->setVisible(true);
        ui->reductDateLabel->setVisible(true);
        ui->reductEdit->setVisible(true);
        ui->reductLabel->setVisible(true);
        break;
    case 3: live = dynamic_cast<Live*>(pro);
        ui->deadEdit->setDate(live->getDeadDay());
        ui->bornDateLabel->setVisible(false);
        ui->bornEdit->setVisible(false);
        ui->reductDateEdit->setVisible(false);
        ui->reductDateLabel->setVisible(false);
        ui->reductEdit->setVisible(false);
        ui->reductLabel->setVisible(false);
        break;
    }
    emit updateSignal();
    qDebug()<<"SIGNAL:ItemInfo::updateSignal()";
}

void ItemInfo::on_changeBtn_clicked()
{
    if(ui->changeBtn->text() == "修改")
    {
        if(pro->getOwner() != user->getUserName())
        {
            QMessageBox *q = new QMessageBox();
            q->setText("对不起，您只能修改自己商品的信息");
            q->show();
            return;
        }
        ui->changeBtn->setText("应用");
        ui->nameEdit->setReadOnly(false);
        ui->bornEdit->setReadOnly(false);
        ui->deadEdit->setReadOnly(false);
        ui->reductDateEdit->setReadOnly(false);
        ui->reductEdit->setReadOnly(false);
        ui->stockEdit->setReadOnly(false);
        ui->priceLabel->setText("原价：");
        ui->priceEdit->setText(QString().setNum(pro->getPrice()));
        ui->priceEdit->setReadOnly(false);
    }
    else
    {
        pro->setName(ui->nameEdit->text());
        pro->setAmount(ui->stockEdit->text().toInt());
        pro->setPrice(ui->priceEdit->text().toDouble());

        Food *food;
        Live *live;
        Elec *elec;
        switch(pro->getType()){
        case 1: food = dynamic_cast<Food*>(pro);
            food->setDeadDay(ui->deadEdit->date());
            food->setBornDay(ui->bornEdit->date());
            food->setReductDay(ui->reductDateEdit->date());
            food->setReductRate(ui->reductEdit->text().toDouble());
            break;
        case 2: elec = dynamic_cast<Elec*>(pro);
            elec->setDeadDay(ui->deadEdit->date());
            elec->setBornDay(ui->bornEdit->date());
            elec->setReductDay(ui->reductDateEdit->date());
            elec->setReductRate(ui->reductEdit->text().toDouble());
            break;
        case 3: live = dynamic_cast<Live*>(pro);
            live->setDeadDay(ui->deadEdit->date());
            break;
        }

        ui->changeBtn->setText("修改");
        ui->nameEdit->setReadOnly(true);
        ui->bornEdit->setReadOnly(true);
        ui->deadEdit->setReadOnly(true);
        ui->reductDateEdit->setReadOnly(true);
        ui->reductEdit->setReadOnly(true);
        ui->stockEdit->setReadOnly(true);
        ui->priceLabel->setText("现价：");
        ui->priceEdit->setText(QString().setNum(pro->calcPrice()));

        update();
    }
}
