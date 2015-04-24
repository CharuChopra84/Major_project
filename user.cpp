#include "user.h"
#include "ui_user.h"

User::User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
    QMenu *menu = new QMenu("User");
    menu->addAction("Add");
    menu->addAction("Edit");
    menu->addAction("Delete");
    menu->addAction("Search");

    relationAction = new QAction(tr("&Relation"), this);
    regionAction = new QAction(tr("&Region"), this);
    connect(relationAction, SIGNAL(triggered()), this,
            SLOT(on_actionRelation_triggered()));
    connect(regionAction, SIGNAL(triggered()), this,
            SLOT(on_actionRegion_triggered()));
    QMenu *match = new QMenu("Match");
    match->addAction(relationAction);
    match->addAction(regionAction);

    printPreview = new QAction(tr("&Print Preview"), this);
    printPage = new QAction(tr("&Print Page"),this);
    connect(printPreview, SIGNAL(triggered()), this,
           SLOT(on_actionprintPreview_triggered()));

    connect(printPage, SIGNAL(triggered()), this,
            SLOT(on_actionprintPage_triggered()));
    QMenu *print = new QMenu("Print");
    print->addAction(printPreview);
    print->addAction(printPage);

    QMenuBar *menubar = new QMenuBar();
    menubar->addMenu(menu);
    menubar->addMenu(match);
    menubar->addMenu(print);

    layout->setMenuBar(menubar);

    Login conn;
    if(!conn.connOpen())
        ui->label_sec_status->setText("failed to open");

    else
        ui->label_sec_status->setText("Connected...");

    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select distinct country from data");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_country->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());

    QSqlQueryModel *modal1 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry1 = new QSqlQuery(conn.mydb);
    qry1->prepare("select haplogroup from data");
    qry1->exec();
    modal1->setQuery(*qry1);
    ui->comboBox_haplogroup->setModel(modal1);
    conn.connClose();

    QSqlQueryModel *modal2 = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry2 = new QSqlQuery(conn.mydb);
    qry2->prepare("select hv1 from data");
    qry2->exec();
    modal2->setQuery(*qry2);
    ui->comboBox_hv1->setModel(modal2);
    conn.connClose();

    QSqlQueryModel *modal3 = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry3 = new QSqlQuery(conn.mydb);
    qry3->prepare("select hv2 from data");
    qry3->exec();
    modal3->setQuery(*qry3);
    ui->comboBox_hv2->setModel(modal3);
    conn.connClose();

    QSqlQueryModel *modal4 = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(conn.mydb);
    qry4->prepare("select ATP from data");
    qry4->exec();
    modal4->setQuery(*qry4);
    ui->comboBox_atp->setModel(modal4);
    conn.connClose();
}

User::~User()
{
    delete ui;
}

void User::closeEvent(QCloseEvent *event)
{
    event->ignore();

    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation?",
                                                  "Are you sure you want to exit?",
                                                  QMessageBox::Yes|QMessageBox::No))
        event->accept();
}

void User::on_actionprintPage_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog dialog(&printer, this);

    if (dialog.exec() == QDialog::Accepted)
        print(&printer);
}

void User::on_actionprintPreview_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    preview.setWindowFlags ( Qt::Window );
    connect(&preview, SIGNAL(paintRequested(QPrinter *)),
            this, SLOT(print(QPrinter *)));
    preview.exec();
}

void User::print(QPrinter *printer)
{
    QPainter painter(printer);
    painter.setWindow(this->rect());
    this->render(&painter);
}

void User::on_actionRelation_triggered()
{
    match user;
    user.setModal(true);
    user.exec();
}

void User::on_actionRegion_triggered()
{
    region user;
    user.setModal(true);
    user.exec();

}

void User::on_pushButton_edit_clicked()
{
    Login conn;
    QString pid, fname, lname, address, country, haplogroup, hv1, hv2, atp;
    pid = ui->pid->text();
    fname = ui->fname->text();
    lname = ui->lname->text();
    address = ui->address->text();
    country = ui->comboBox_country->currentText();
    haplogroup = ui->comboBox_haplogroup->currentText();
    hv1 = ui->comboBox_hv1->currentText();
    hv2 = ui->comboBox_hv2->currentText();
    atp = ui->comboBox_atp->currentText();
    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update use set fname = '"+fname+"', lname = '"+lname+"', address = '"+address+"',country = '"+country+"', haplogroup = '"+haplogroup+"', hv1 = '"+hv1+"', hv2 = '"+hv2+"',atp = '"+atp+"' where pid ='"+pid+"'");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Edit"), tr("Updated"));
        conn.connClose();
    }

    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }


}

void User::on_pushButton_add_clicked()
{
    Login conn;
    QString pid, fname, lname, address, country, haplogroup, hv1, hv2, atp;
    pid = ui->pid->text();
    fname = ui->fname->text();
    lname = ui->lname->text();
    address = ui->address->text();
    country = ui->comboBox_country->currentText();
    haplogroup = ui->comboBox_haplogroup->currentText();
    hv1 = ui->comboBox_hv1->currentText();
    hv2 = ui->comboBox_hv2->currentText();
    atp = ui->comboBox_atp->currentText();
    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into use (pid, fname, lname, address, country, haplogroup, hv1, hv2, atp) values('"+pid+"','"+fname+"','"+lname+"', '"+address+"','"+country+"','"+haplogroup+"', '"+hv1+"','"+hv2+"','"+atp+"')");

    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Add"), tr("Added"));
        conn.connClose();
    }

    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }


}

void User::on_pushButton_delete_clicked()
{
    Login conn;
    QString pid;
    pid = ui->pid->text();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("Delete from use where pid ='"+pid+"'");


    if(qry.exec())
    {
        QMessageBox::critical(this,tr("Delete"), tr("Deleted"));
        conn.connClose();
    }

    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }


}

void User::on_pushButton_3_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select pid from use");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void User::on_comboBox_currentIndexChanged(const QString &arg1)
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
    qry.prepare("select * from use where pid ='"+str+"' or haplogroup = '"+str+"' or country = '"+str+"' or lname = '"+str+"' or fname = '"+str+"'");


    if(qry.exec())
    {
        while(qry.next())
        {
            ui->pid->setText(qry.value(0).toString());
            ui->fname->setText(qry.value(1).toString());
            ui->lname->setText(qry.value(2).toString());
            ui->address->setText(qry.value(3).toString());
            ui->comboBox_country->setCurrentText(qry.value(4).toString());
            ui->comboBox_haplogroup->setCurrentText(qry.value(5).toString());
            ui->comboBox_hv1->setCurrentText(qry.value(6).toString());
            ui->comboBox_hv2->setCurrentText(qry.value(7).toString());
            ui->comboBox_atp->setCurrentText(qry.value(8).toString());

        }

        conn.connClose();
    }

    else
    {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }

}

void User::on_pushButton_5_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select haplogroup from use");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void User::on_pushButton_4_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select country from use");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}



void User::on_pushButton_2_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select lname from use");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void User::on_pushButton_clicked()
{
    Login conn;
    QSqlQueryModel *modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.mydb);

    qry->prepare("select fname from use");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox->setModel(modal);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}
