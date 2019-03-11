#ifndef SELECTITEMTYPE_H
#define SELECTITEMTYPE_H

#include <QDialog>

namespace Ui {
class SelectItemType;
}

class SelectItemType : public QDialog
{
    Q_OBJECT
    
public:
    explicit SelectItemType(QWidget *parent = 0);
    ~SelectItemType();
signals:
    void getType(QString, int);
private slots:
    void on_pushButton_clicked();

private:
    Ui::SelectItemType *ui;
};

#endif // SELECTITEMTYPE_H
