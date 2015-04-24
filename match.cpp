#include "match.h"
#include "ui_match.h"


match::match(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::match)
{
    ui->setupUi(this);

    Login conn;
    if(!conn.connOpen())
        ui->label_match->setText("failed to open");

    else
        ui->label_match->setText("Connected...");

    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select fname from use");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    ui->comboBox_2->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());





}

void match::on_comboBox_currentIndexChanged(const QString &arg1)
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
            ui->lineEdit_1hv1->setText(qry.value(6).toString());
            ui->lineEdit_1hv2->setText(qry.value(7).toString());
        }

        conn.connClose();
    }

    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }

    QString str4 = ui->lineEdit_1hv1->text();
    QString str1 = ui->lineEdit_1hv2->text();
    QString str2 = ui->lineEdit_2hv1->text();
    QString str3 = ui->lineEdit_2hv2->text();

    if(str4 == str2 && str1 == str3)
    {
        ui->label_6->setText("First Relative");
    }

    else if(str4 == str2)
    {
        ui->label_6->setText("Cousin");
    }

    else if(str1 == str3)
    {
        ui->label_6->setText("Cousin");
    }

    else
    {
        ui->label_6->setText("No relation");
    }

}

void match::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString str = ui->comboBox_2->currentText();

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
            ui->lineEdit_2hv1->setText(qry.value(6).toString());
            ui->lineEdit_2hv2->setText(qry.value(7).toString());
        }

        conn.connClose();
    }

    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }

    QString str4 = ui->lineEdit_1hv1->text();
    QString str1 = ui->lineEdit_1hv2->text();
    QString str2 = ui->lineEdit_2hv1->text();
    QString str3 = ui->lineEdit_2hv2->text();

    if(str4 == str2 && str1 == str3)
    {
        ui->label_6->setText("First Relative");
    }

    else if(str4 == str2)
    {
        ui->label_6->setText("Cousin");
    }

    else if(str1 == str3)
    {
        ui->label_6->setText("Cousin");
    }

    else
    {
        ui->label_6->setText("No relation");
    }
}

match::~match()
{
    delete ui;
}
