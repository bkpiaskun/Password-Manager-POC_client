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
    int isLogged();
    int isRegistered();
    int isDownloaded();
    void logOut();


signals:

void dataReadyToRead(QByteArray);
void PassesDownloaded(QByteArray);


public slots:

void readRead(QNetworkReply *reply);


private:
QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
QNetworkCookieJar *jar = new QNetworkCookieJar(this);
int LogStatus = 0;
int RegStatus = 0;
int DownloadStatus =0;
};

#endif // MYNETWORKCLASS_H
