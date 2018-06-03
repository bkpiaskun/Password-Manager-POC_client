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
    connect(&NetworkConnection,SIGNAL(dataReadyToRead(QByteArray)),this,SLOT(dataInDaHouse(QByteArray)));

    connect(&NetworkConnection,SIGNAL(PassesDownloaded(QByteArray)),this,SLOT(PasswordsReady(QByteArray)));

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

    //RestConnection *con = new RestConnection( ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());
    //con->SendRequest();
    NetworkConnection.Login(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());

/*    int i=1;
    while(NetworkConnection.isLogged() == 0)
    {
        i++;
        ui->textBrowser->setText("Logowanie");
        for(int n=0;n<i;n++)
        {
            ui->textBrowser->append(".");
        }
        if(i>=3)
        i=1;
        Sleep(30);
    }*/

    if(NetworkConnection.isLogged() == 1)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(NetworkConnection.isLogged() == -1)
    {
        ui->textBrowser->setText("Błąd logowania");
    }



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
    if(NetworkConnection.isRegistered() == 1)
    ui->stackedWidget->setCurrentIndex(0);




}

void gui::dataInDaHouse(QByteArray data)
{
    QString dataString;
    dataString = data;

}
/*
void gui::moveToPasswords()
{
    ui->stackedWidget->setCurrentIndex(1);
}
*/

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
    /*qDebug() << "Pass_ID"           << arr.at(1).toObject().value("Pass_ID").toString();
    qDebug() << "Destination_User"  << arr.at(1).toObject().value("Destination_User").toString();
    qDebug() << "Destination"       << arr.at(1).toObject().value("Destination").toString();
    qDebug() << "Hashed_Password"   << arr.at(1).toObject().value("Hashed_Password").toString();
    qDebug() << arr.size();
*/
    QJsonObject obj = doc.object();
    //doc.setObject(obj);
    //qDebug() << obj;



    //qDebug() << dest.size() << dest.count();
    //qDebug() << obj.size() << obj.count();
    //qDebug() << obj.length();

    for(int i =0;i<arr.size();i++)
    {
        qDebug() << "Pass_ID"           << arr.at(i).toObject().value("Pass_ID").toString();
        qDebug() << "Destination_User"  << arr.at(i).toObject().value("Destination_User").toString();
        qDebug() << "Destination"       << arr.at(i).toObject().value("Destination").toString();
        qDebug() << "Hashed_Password"   << arr.at(i).toObject().value("Hashed_Password").toString();
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
        ui->textBrowser->setText("Błąd logowania");
    }

}
