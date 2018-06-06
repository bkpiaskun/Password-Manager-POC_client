#ifndef MYNETWORKCLASS_H
#define MYNETWORKCLASS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>

class NetworkConnection : public QObject
{
    Q_OBJECT
public:
    explicit NetworkConnection(QObject *parent = nullptr);
    void Login(QString Login,QString Password,QString URL);
    void Register(QString Login,QString Password,QString URL);
    void GetPasswords(QString Login,QString Password,QString URL);

    void RemovePassword(QString Login,QString Password,int Pass_ID,QString URL);
    void ModifyPassword(QString Login,QString Password,int Pass_ID,QString Dest,QString Dest_User,QString Pass,QString URL);
    void AddPassword(QString Login,QString Password,QString Dest,QString Dest_User,QString Pass,QString URL);



    int isAdded();
    int isModified();
    int isRemoved();
    int isLogged();
    int isRegistered();
    int isDownloaded();
    void logOut();


signals:

void PassesDownloaded(QByteArray);
void Registered(QByteArray);
void Logged(QByteArray);
void Modified(QByteArray);
void Removed(QByteArray);
void Added(QByteArray);


public slots:

void ResponseReady(QNetworkReply *reply);


private:
QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
QNetworkCookieJar *jar = new QNetworkCookieJar(this);
int LogStatus = 0;
int RegStatus = 0;
int DownloadStatus = 0;
int RemoveStatus = 0;
int ModifyStatus = 0;
int AddingStatus = 0;

};

#endif // MYNETWORKCLASS_H
