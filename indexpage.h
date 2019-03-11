#ifndef INDEXPAGE_H
#define INDEXPAGE_H

#include <QWidget>

namespace Ui {
class IndexPage;
}

class IndexPage : public QWidget
{
    Q_OBJECT
    
public:
    explicit IndexPage(QWidget *parent = 0);
    ~IndexPage();
    
private:
    Ui::IndexPage *ui;
};

#endif // INDEXPAGE_H
