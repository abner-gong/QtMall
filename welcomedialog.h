#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H
#include "QPushButton"
#include "QLayout"
#include "QLineEdit"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QLabel"
#include <QWidget>

class WelcomeDialog : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeDialog(QWidget *parent = 0);
private:
    QLabel *nameLabel;
    QLineEdit *nameLineText;
    QLabel *passwordLabel;
    QLineEdit *passwordLineText;
    QPushButton *logBtn;
    QHBoxLayout *boxVH1;
    QLabel *passwordConfirmLabel;
signals:
    
public slots:
    
};

#endif // WELCOMEDIALOG_H
