#ifndef HEADWIDGET_H
#define HEADWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedLayout>
#include "iteminfo.h"

namespace Ui {
class HeadWidget;
}

class HeadWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HeadWidget(QWidget *parent = 0);
    explicit HeadWidget(QString theName,QWidget *parent = 0);
    ~HeadWidget();
    QString getName(){return name;}
signals:
    void logInSignal();
    void searchMine(QString);
    void loginSuccessSignal(QString);
    void updateSignal();
public slots:
    void logOut();
    void logIn();
    void loginSuccess(QString name);
    void checkInfo();
    void createPro(QString theName, int t);
    void update();
private slots:
    void on_mineBtn_clicked();

    void on_addItemBtn_clicked();

private:
    Ui::HeadWidget *ui;
    QString name;
    QStackedLayout *outBox;


};

#endif // HEADWIDGET_H
