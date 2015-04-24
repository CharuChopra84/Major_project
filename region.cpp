#include "region.h"
#include "ui_region.h"

region::region(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::region)
{
    ui->setupUi(this);
    Login conn;
    if(!conn.connOpen())
        ui->label_region_2->setText("failed to open");

    else
        ui->label_region_2->setText("Connected...");

    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select fname from use");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());

    QSqlQueryModel *modal1 = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry1 = new QSqlQuery(conn.mydb);

    qry1->prepare("select haplogroup from use");
    qry1->exec();
    modal1->setQuery(*qry1);
    ui->comboBox_haplo->setModel(modal1);
    conn.connClose();
    qDebug()<<(modal1->rowCount());
}

region::~region()
{
    delete ui;
}

void region::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString str = ui->comboBox->currentText();
    Login conn;

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from use where fname = '"+str+"'");

    if(qry.exec())
    {
        while(qry.next())
        {
            ui->comboBox_haplo->setCurrentText(qry.value(5).toString());
        }

        conn.connClose();
    }



}

void region::on_comboBox_haplo_currentIndexChanged(const QString &arg1)
{
        QString str1 = ui->comboBox_haplo->currentText();
        Login conn1;

        if(!conn1.connOpen())
        {
            qDebug()<<"Failed to open the database";
            return;
        }

        conn1.connOpen();
        QSqlQuery qry1;
        qry1.prepare("select * from data where haplogroup = '"+str1+"'");

        if(qry1.exec())
        {
            while(qry1.next())
            {
                ui->lineEdit_2->setText(qry1.value(0).toString());
            }

            conn1.connClose();
        }

}
