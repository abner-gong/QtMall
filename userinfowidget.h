#ifndef USERINFOWIDGET_H
#define USERINFOWIDGET_H

#include <QWidget>
#include "user.h"
#include <QHBoxLayout>

namespace Ui {
class UserInfoWidget;
}

class UserInfoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit UserInfoWidget(User *user, QWidget *parent = 0);
    ~UserInfoWidget();
    QHBoxLayout *outBox;
    User *user;
private slots:
    void on_addBtn_clicked();

    void on_turnButton_clicked();

private:
    Ui::UserInfoWidget *ui;

};

#endif // USERINFOWIDGET_H
