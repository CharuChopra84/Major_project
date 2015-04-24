#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QPrintDialog>
#include <QCloseEvent>
#include "login.h"

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = 0);
    ~User();


private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_actionRelation_triggered();
    void on_actionRegion_triggered();
    void on_actionprintPreview_triggered();
    void on_actionprintPage_triggered();
     void closeEvent(QCloseEvent *event);
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void print(QPrinter *printer);


private:
    Ui::User *ui;
    QAction *relationAction;
    QAction *regionAction;
    QAction *printPreview;
    QAction *printPage;
};

#endif // USER_H



