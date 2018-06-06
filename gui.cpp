#include "gui.h"
#include "ui_gui.h"

#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


gui::gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui)
{
    ui->setupUi(this);

    connect(&NetworkConnection,SIGNAL(PassesDownloaded(QByteArray)),this,SLOT(PasswordsReady(QByteArray)));
    connect(&NetworkConnection,SIGNAL(Removed(QByteArray)),this,SLOT(RemovedPassword(QByteArray)));
    connect(&NetworkConnection,SIGNAL(Modified(QByteArray)),this,SLOT(ModifiedPassword(QByteArray)));
    connect(&NetworkConnection,SIGNAL(Added(QByteArray)),this,SLOT(AddedPassword(QByteArray)));
    connect(&NetworkConnection,SIGNAL(Registered(QByteArray)),this,SLOT(RegisteredIn(QByteArray)));
    connect(&NetworkConnection,SIGNAL(Logged(QByteArray)),this,SLOT(LoggedIn(QByteArray)));



    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->adjustSize();
    QStringList labels;
    labels.append("Domena");
    labels.append("Użytkownik");
    labels.append("Hasło");
    ui->tableWidget->setHorizontalHeaderLabels(labels);
    for(int c =0; c< ui->tableWidget->horizontalHeader()->count();++c)
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(c,QHeaderView::Stretch);

    for(int i = 1; i <= ui->tableWidget->columnCount() -1;i++)
    {
        ui->tableWidget->setItem(ui->tableWidget->rowCount() -1,i,new QTableWidgetItem(QString::number(i)));
    }
}

gui::~gui()
{
    delete ui;
}


void gui::on_gotoreg_1_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}
void gui::on_gotohasla_2_clicked()
{
    //QByteArray hash = QCryptographicHash::​hash(s.toLocal8bit(), QCryptographicHash::Md5);
    NetworkConnection.Login(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());
}

void gui::on_gotolog_4_clicked()
{
    NetworkConnection.logOut();
    ui->stackedWidget->setCurrentIndex(0);
}
void gui::on_gotolog_3_clicked()
{
    if(ui->lineEdit_13->text() == ui->lineEdit_11->text())
    {
        NetworkConnection.Register(ui->lineEdit_12->text(), ui->lineEdit_13->text(), ui->lineEdit_10->text());
    }
    else
    {
        //highlight()
        //status.hasla nie takie same
    }
}


void gui::on_Delete_2_clicked()
{
    NetworkConnection.GetPasswords(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());

    if(NetworkConnection.isLogged() == 1)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(NetworkConnection.isLogged() == -1)
    {
        //ui->textBrowser->setText("Błąd logowania");
    }

}
void gui::on_Cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void gui::on_Add_clicked()
{
    if(ui->lineEdit_4->text().length() <3 )
    {
        ui->lineEdit_4->setStyleSheet("QLineEdit { background: rgb(255, 60, 60); selection-background-color: rgb(255, 60, 60); }");
    } else {
        ui->lineEdit_4->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(255, 255, 255); }");
    }

    if(ui->lineEdit_5->text().length() <3)
    {
        ui->lineEdit_5->setStyleSheet("QLineEdit { background: rgb(255, 60, 60); selection-background-color: rgb(255, 60, 60); }");
    } else {
        ui->lineEdit_5->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(255, 255, 255); }");
    }


    if(ui->lineEdit_6->text().length() <3)
    {
        ui->lineEdit_6->setStyleSheet("QLineEdit { background: rgb(255, 60, 60); selection-background-color: rgb(255, 60, 60); }");
    } else {
        ui->lineEdit_6->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(255, 255, 255); }");
    }
    if(ui->lineEdit_4->text().length() >2 && ui->lineEdit_5->text().length() >2 && ui->lineEdit_6->text().length() >2)
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int x = ui->tableWidget->rowCount() -1;
        ui->tableWidget->setItem(x,0,new QTableWidgetItem(ui->lineEdit_4->text()));
        ui->tableWidget->setItem(x,1,new QTableWidgetItem(ui->lineEdit_5->text()));
        ui->tableWidget->setItem(x,2,new QTableWidgetItem(ui->lineEdit_6->text()));
    }
}





void gui::PasswordsReady(QByteArray PassData)
{
    QString dataString;
    dataString = PassData;
    //ui->tableView
    //ui->tableView
    //qDebug() << dataString;
    QJsonDocument doc = QJsonDocument::fromJson(PassData);
    qDebug() << doc;

    QJsonArray arr = doc.array();
    /*
    qDebug() << "Pass_ID"           << arr.at(1).toObject().value("Pass_ID").toString();
    qDebug() << "Destination_User"  << arr.at(1).toObject().value("Destination_User").toString();
    qDebug() << "Destination"       << arr.at(1).toObject().value("Destination").toString();
    qDebug() << "Hashed_Password"   << arr.at(1).toObject().value("Hashed_Password").toString();
    qDebug() << arr.size();
    */
    QJsonObject obj = doc.object();


    for(int i =0;i<arr.size();i++)
    {
        qDebug() << "Pass_ID"           << arr.at(i).toObject().value("Pass_ID").toString();
        qDebug() << "Destination_User"  << arr.at(i).toObject().value("Destination_User").toString();
        qDebug() << "Destination"       << arr.at(i).toObject().value("Destination").toString();
        qDebug() << "Hashed_Password"   << arr.at(i).toObject().value("Hashed_Password").toString();
    }
    // ###########################################################################
    //
    // ############################## HANDLING PASSWORDS #########################
    //
    // ###########################################################################


}
void gui::RegisteredIn(QByteArray PassData)
{
    ui->Status_pusty->setText("Zarejestrowano Pomyślnie");
}
void gui::LoggedIn(QByteArray PassData)
{
    ui->stackedWidget->setCurrentIndex(1);
}
void gui::ModifiedPassword(QByteArray PassData)
{
    ui->Status_pusty_3->setText("Hasła Zapisane Pomyślnie.");
}
void gui::RemovedPassword(QByteArray PassData)
{
    ui->Status_pusty_3->setText("Hasło Usunięte Pomyślnie.");
}
void gui::AddedPassword(QByteArray PassData)
{
    ui->Status_pusty_3->setText("Hasło Dodanie Pomyślnie.");
}

