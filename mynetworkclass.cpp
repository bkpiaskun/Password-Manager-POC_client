#include "mynetworkclass.h"
#include <QJsonDocument>
#include <QNetworkCookie>

MyNetworkClass::MyNetworkClass(QObject *parent) : QObject(parent)
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(readRead(QNetworkReply*)));
    qnam->setCookieJar(this->jar);
}
void MyNetworkClass::Login(QString Login,QString Password,QString URL)
{
    QVariantMap feed;
    feed.insert("login",Login);
    feed.insert("password",Password);
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();
    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost(URL);
    myurl.setPath("/app_login");
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    qnam->post(request,payload);
}
void MyNetworkClass::Register(QString Login,QString Password,QString URL)
{
    QVariantMap feed;
    feed.insert("login",Login);
    feed.insert("password",Password);
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();
    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost(URL);
    myurl.setPath("/app_register");
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    qnam->setCookieJar(this->jar);
    qnam->post(request,payload);
}
void MyNetworkClass::GetPasswords(QString Login,QString Password,QString URL)
{
    QVariantMap feed;
    feed.insert("login",Login);
    feed.insert("password",Password);
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();
    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost(URL);
    myurl.setPath("/app_getpasswords");
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    qnam->setCookieJar(this->jar);
    qnam->post(request,payload);
}

void MyNetworkClass::readRead(QNetworkReply *reply)
{
    if(reply->request().url().path() == "/app_login")
    {
    qDebug() << reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toString();
    if(reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toInt() == 200)
    {
        LogStatus = 1;
    } else {
        LogStatus = -1;
    }

    QByteArray myData;
    myData = reply->readAll();
    emit(dataReadyToRead(myData));
    }
    if(reply->request().url().path() == "/app_register")
    {
    qDebug() << reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toString();
    if(reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toInt() == 200)
    {
        RegStatus = 1;

    } else {
        RegStatus = -1;
    }
    QByteArray myData;
    myData = reply->readAll();
    emit(dataReadyToRead(myData));
    }

    if(reply->request().url().path() == "/app_getpasswords")
    {
    qDebug() << reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toString();
    if(reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toInt() == 200)
    {
        DownloadStatus = 1;

    } else {
        DownloadStatus = -1;
    }
    QByteArray myData;
    myData = reply->readAll();
    //reply->re
    QString asd = myData;
    QJsonDocument doc = QJsonDocument::fromJson(myData);
    /*qDebug() <<doc;
    qDebug() << asd;
    qDebug() << endl;
    qDebug() << endl;*/
    emit(PassesDownloaded(myData));
    }


}
int MyNetworkClass::isLogged()
{
    return LogStatus;
}
void MyNetworkClass::logOut()
{
    this->LogStatus = 0;
    this->RegStatus = 0;
    this->DownloadStatus = 0;
}
int MyNetworkClass::isRegistered()
{
    return RegStatus;
}

int MyNetworkClass::isDownloaded()
{
    return DownloadStatus;
}
