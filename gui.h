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

    void PasswordsReady(QByteArray PassData);
    void RegisteredIn(bool status);
    void LoggedIn(bool status);
    void ModifiedPassword();
    void RemovedPassword();
    void AddedPassword();





    void on_Add_clicked();

    void on_Cancel_clicked();

    void on_Delete_clicked();

    void on_Refresh_clicked();

private:
    Ui::gui *ui;
    QString Login,Password,URL,User_ID,Hashed_Pass;
    uint Encryption_Token;
    NetworkConnection NetworkConnection;
};

#endif // GUI_H
