#include "gui.h"
#include "ui_gui.h"
#include <restconnection.h>
#include <windows.h>

gui::gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui)
{
    ui->setupUi(this);
    connect(&NetworkConnection,SIGNAL(dataReadyToRead(QByteArray)),this,SLOT(dataInDaHouse(QByteArray)));

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






