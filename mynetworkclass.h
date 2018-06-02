#ifndef MYNETWORKCLASS_H
#define MYNETWORKCLASS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>

class MyNetworkClass : public QObject
{
    Q_OBJECT
public:
    explicit MyNetworkClass(QObject *parent = nullptr);
    void Login(QString Login,QString Password,QString URL);
    void Register(QString Login,QString Password,QString URL);
    int isLogged();
    int isRegistered();
    void logOut();
signals:


void dataReadyToRead(QByteArray);


public slots:

void readRead(QNetworkReply *reply);


private:
QNetworkAccessManager *qnam = new QNetworkAccessManager(this);
QNetworkCookieJar *jar = new QNetworkCookieJar(this);
int LogStatus = 0;
int RegStatus = 0;
};

#endif // MYNETWORKCLASS_H
