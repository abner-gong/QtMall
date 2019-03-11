#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
    Q_OBJECT
    

public:
    explicit WelcomeWidget(QWidget *parent = 0);
    ~WelcomeWidget();
    QVBoxLayout *vBox;
signals:
    void loginSuccess(QString);
private:
    Ui::WelcomeWidget *ui;
private slots:
    void on_loginBtn_clicked();
    void on_regBtn_clicked();

};

#endif // WELCOMEWIDGET_H
