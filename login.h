#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QProgressDialog>
#include <QtConcurrent>

#include "user.h"
#include "match.h"
#include "region.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:

    explicit Login(QWidget *parent = 0);
    ~Login();

    QSqlDatabase mydb;
    static void doTask(int &number);

    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("/home/charu/mtdna.db");
        if(!mydb.open())
        {
            qDebug()<<("failed to open");
            return false;
        }
        else
        {
            qDebug()<<("Connected...");
            return true;
        }
    }

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
