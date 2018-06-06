#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "networkconnection.h"

namespace Ui {
class gui;
}

class gui : public QMainWindow
{
    Q_OBJECT

public:
    explicit gui(QWidget *parent = 0);
    ~gui();


private slots:
    void on_gotoreg_1_clicked();

    void on_gotohasla_2_clicked();

    void on_gotolog_4_clicked();

    void on_gotolog_3_clicked();

    void dataInDaHouse(QByteArray data);
    void PasswordsReady(QByteArray PassData);
    void RegisteredIn(QByteArray PassData);
    void LoggedIn(QByteArray PassData);
    void ModifiedPassword(QByteArray PassData);
    void RemovedPassword(QByteArray PassData);
    void AddedPassword(QByteArray PassData);







    void on_Delete_2_clicked();

    void on_Add_clicked();

private:
    Ui::gui *ui;
    QString Login,Password,URL,User_ID;
    NetworkConnection NetworkConnection;
};

#endif // GUI_H
