#ifndef REGION_H
#define REGION_H

#include <QDialog>
#include "login.h"

namespace Ui {
class region;
}

class region : public QDialog
{
    Q_OBJECT

public:
    explicit region(QWidget *parent = 0);
    ~region();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_haplo_currentIndexChanged(const QString &arg1);

private:
    Ui::region *ui;
};

#endif // REGION_H
