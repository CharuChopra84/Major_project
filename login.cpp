#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);


//    QVector<int> vector;
//    for(int i=0;i<101; i++)
//        vector.append(i);

//    QProgressDialog pdialog;
//    pdialog.setLabelText("Processing");

//    QFutureWatcher<void> watcher;

//    connect(&pdialog,SIGNAL(canceled()),&watcher,SLOT(cancel()));
//    connect(&watcher,SIGNAL(finished()),&pdialog,SLOT(reset()));
//    connect(&watcher,SIGNAL(progressRangeChanged(int,int)),&pdialog,SLOT(setRange(int,int)));
//    connect(&watcher,SIGNAL(progressValueChanged(int)),&pdialog,SLOT(setValue(int)));

//    watcher.setFuture(QtConcurrent::map(vector,&Login::doTask));

//    pdialog.exec();
//    watcher.waitForFinished();

//    if(watcher.isCanceled())
//    {
//        qDebug()<<"cancelled";
//        QMessageBox::critical(this,"Cancelled","Application Terminated");
//    }

    if(!connOpen())
        ui->label->setText("failed to open");

    else
        ui->label->setText("Connected...");

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

void Login::doTask(int &number)
{
//    qDebug()<<"Starting"<<number;
//    int max = 10;
//    for(int i =0; i< max; i++)
//    {
//        QThread::currentThread()->msleep(50);
//        qDebug()<<"Processing"<<number<<"-"<<i<<"of"<<max;
//    }

//    qDebug()<<"Stopped"<<number;

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString username, password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();

    if(!connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from login where username = '"+username+"' and password = '"+password+"'");


    if(qry.exec())
    {
        int count = 0;
        while(qry.next())
        {
            count++;
        }
        if(count == 1)
        {
            ui->label->setText("Username and Password are correct");
            connClose();
            this->hide();
            User user;
            user.setModal(true);
            user.exec();
        }


        if(count > 1)
            ui->label->setText("Duplicate Username and Password");

        if(count < 1)
            ui->label->setText("Username and Password are not correct");


    }


}
