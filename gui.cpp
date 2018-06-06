#include "gui.h"
#include "ui_gui.h"

#include <windows.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <simplecrypt.h>
#include <QString>
#include <QByteArray>


gui::gui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gui)
{
    ui->setupUi(this);

    connect(&NetworkConnection,SIGNAL(PassesDownloaded(QByteArray)),this,SLOT(PasswordsReady(QByteArray)));
    connect(&NetworkConnection,SIGNAL(Removed(QByteArray)),this,SLOT(RemovedPassword()));
    connect(&NetworkConnection,SIGNAL(Modified(QByteArray)),this,SLOT(ModifiedPassword()));
    connect(&NetworkConnection,SIGNAL(Added(QByteArray)),this,SLOT(AddedPassword()));
    connect(&NetworkConnection,SIGNAL(Registered(bool)),this,SLOT(RegisteredIn(bool)));
    connect(&NetworkConnection,SIGNAL(Logged(bool)),this,SLOT(LoggedIn(bool)));



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
    NetworkConnection.Login(ui->lineEdit->text(), QCryptographicHash::hash(ui->lineEdit_2->text().toLocal8Bit().constData(),QCryptographicHash::Sha512), ui->lineEdit_3->text());
    this->Login = ui->lineEdit->text();
    this->Password = ui->lineEdit_2->text();
    this->Hashed_Pass = QCryptographicHash::hash(ui->lineEdit_2->text().toLocal8Bit().constData(),QCryptographicHash::Sha512);
    //    this->Hashed_Pass = QCryptographicHash::​hash(ui->lineEdit->text().toLocal8Bit().constData(),QCryptographicHash::Sha512);
    this->URL = ui->lineEdit_3->text();
    this->Encryption_Token = qHash(Password);
}

void gui::on_gotolog_4_clicked()
{
    NetworkConnection.logOut();
    ui->tableWidget->clear();
    while(ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setColumnCount(3);
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
void gui::on_gotolog_3_clicked()
{
    this->Login = ui->lineEdit->text();
    this->Password = ui->lineEdit_2->text();
    this->Hashed_Pass = QCryptographicHash::hash(ui->lineEdit_2->text().toLocal8Bit().constData(),QCryptographicHash::Sha512);
    //    this->Hashed_Pass = QCryptographicHash::​hash(ui->lineEdit->text().toLocal8Bit().constData(),QCryptographicHash::Sha512);
    this->URL = ui->lineEdit_3->text();
    this->Encryption_Token = qHash(Password);

    if(ui->lineEdit_13->text() == ui->lineEdit_11->text() && ui->lineEdit_13->text().length() >2)
    {
        //NetworkConnection.Register(ui->lineEdit_12->text(), QCryptographicHash::​hash((ui->lineEdit_13->text()).toLocal8Bit().constData(), QCryptographicHash::Sha512), ui->lineEdit_10->text());
        NetworkConnection.Register(ui->lineEdit_12->text(), QCryptographicHash::hash(ui->lineEdit_13->text().toLocal8Bit().constData(),QCryptographicHash::Sha512),ui->lineEdit_10->text());
        //NetworkConnection.Register(ui->lineEdit_12->text(), ui->lineEdit_13->text(),ui->lineEdit_10->text());
        //    this->Hashed_Pass = QCryptographicHash::hash(ui->lineEdit->text().toLocal8Bit().constData(),QCryptographicHash::Sha512);

        ui->lineEdit_6->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); selection-background-color: rgb(255, 255, 255); }");
        ui->Status_pusty->setText("");
    }
    else
    {

        ui->lineEdit_6->setStyleSheet("QLineEdit { background: rgb(255, 60, 60); selection-background-color: rgb(255, 60, 60); }");
        ui->Status_pusty->setText("Hasła nie takie same lub zbyt krótkie!");




        //highlight()
        //status.hasla nie takie same
    }
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

        NetworkConnection.AddPassword(this->Login, QCryptographicHash::hash(ui->lineEdit_2->text().toLocal8Bit().constData(),QCryptographicHash::Sha512),ui->lineEdit_6->text(),ui->lineEdit_5->text(),ui->lineEdit_4->text(),this->URL);

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
    {/*
        qDebug() << "Pass_ID"           << arr.at(i).toObject().value("Pass_ID").toString();
        qDebug() << "Destination_User"  << arr.at(i).toObject().value("Destination_User").toString();
        qDebug() << "Destination"       << arr.at(i).toObject().value("Destination").toString();
        qDebug() << "Hashed_Password"   << arr.at(i).toObject().value("Hashed_Password").toString();
    */
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        //int x = ui->tableWidget->rowCount() -1;

        this->Passwords.append(arr.at(i).toObject().value("Pass_ID").toString());
        this->Passwords.append(arr.at(i).toObject().value("Destination_User").toString());
        this->Passwords.append(arr.at(i).toObject().value("Destination").toString());
        this->Passwords.append(arr.at(i).toObject().value("Hashed_Password").toString());
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(arr.at(i).toObject().value("Hashed_Password").toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(arr.at(i).toObject().value("Destination_User").toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(arr.at(i).toObject().value("Destination").toString()));
    }
}
void gui::RegisteredIn(bool status)
{
    if(status)
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->Status_pusty->setText("Zarejestrowano Pomyślnie");
    } else {
        ui->Status_pusty->setText("Błąd rejestracji!");
    }
}
void gui::LoggedIn(bool status)
{
    //this->User_ID =
    if(status)
    {
        ui->stackedWidget->setCurrentIndex(1);
        ui->labelOfStatus->setText("Status: ");
        NetworkConnection.GetPasswords(this->Login,this->Hashed_Pass,this->URL);



    } else {
        ui->labelOfStatus->setText("Status: Błąd logowania!");
    }
}
void gui::ModifiedPassword()
{
    ui->Status_pusty_3->setText("Hasła Zapisane Pomyślnie.");
}
void gui::RemovedPassword()
{
    ui->Status_pusty_3->setText("Hasło Usunięte Pomyślnie.");
}
void gui::AddedPassword()
{
    ui->Status_pusty_3->setText("Hasło Dodanie Pomyślnie.");
}

void gui::clearPasswords()
{

}


void gui::on_Cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gui::on_Delete_clicked()
{
while(!ui->tableWidget->selectedItems().empty())
{
    for(int x=0;x<ui->tableWidget->selectedItems().count();x++)
    ui->tableWidget->removeRow(ui->tableWidget->selectedItems().at(x)->row());
}
}

void gui::on_Refresh_clicked()
{
    NetworkConnection.logOut();
    ui->tableWidget->clear();
    while(ui->tableWidget->rowCount() > 0)
    {
        ui->tableWidget->removeRow(ui->tableWidget->rowCount()-1);
    }
    ui->tableWidget->setColumnCount(3);
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

    NetworkConnection.Login(this->Login,this->Hashed_Pass,this->URL);
}




