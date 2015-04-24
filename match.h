#ifndef MATCH_H
#define MATCH_H

#include <QDialog>
#include "login.h"

namespace Ui {
class match;
}

class match : public QDialog
{
    Q_OBJECT

public:
    explicit match(QWidget *parent = 0);
    ~match();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

private:
    Ui::match *ui;
};

#endif // MATCH_H




