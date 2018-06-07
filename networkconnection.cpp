#include "networkconnection.h"
#include <QJsonDocument>
#include <QNetworkCookie>

NetworkConnection::NetworkConnection(QObject *parent) : QObject(parent)
{
    connect(qnam,SIGNAL(finished(QNetworkReply*)),this,SLOT(ResponseReady(QNetworkReply*)));
    qnam->setCookieJar(this->jar);
}
void NetworkConnection::Login(QString Login,QString Password,QString URL)
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
void NetworkConnection::Register(QString Login,QString Password,QString URL)
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
void NetworkConnection::GetPasswords(QString Login,QString Password,QString URL)
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

void NetworkConnection::RemovePassword(QString Login, QString Password, int Pass_ID, QString URL)
{
    QVariantMap feed;
    feed.insert("login",Login);
    feed.insert("password",Password);
    feed.insert("Pass_ID",Pass_ID);
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();
    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost(URL);
    myurl.setPath("/app_rem_pass");
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    qnam->setCookieJar(this->jar);
    qnam->post(request,payload);

}

void NetworkConnection::ModifyPassword(QString Login, QString Password, int Pass_ID, QString Dest, QString Dest_User, QString Pass, QString URL)
{
    QVariantMap feed;
    feed.insert("login",Login);
    feed.insert("password",Password);
    feed.insert("Pass_ID",Pass_ID);
    feed.insert("Destination",Dest);
    feed.insert("Destination_User",Dest_User);
    feed.insert("Hashed_Password",Pass);
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();
    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost(URL);
    myurl.setPath("/app_mod_pass");
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    qnam->setCookieJar(this->jar);
    qnam->post(request,payload);
}

void NetworkConnection::AddPassword(QString Login, QString Password, QString Dest, QString Dest_User, QString Pass, QString URL)
{
    QVariantMap feed;
    feed.insert("login",Login);
    feed.insert("password",Password);
    feed.insert("Destination",Dest);
    feed.insert("Destination_User",Dest_User);
    feed.insert("Hashed_Password",Pass);
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();
    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost(URL);
    myurl.setPath("/app_add_pass");
    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    qnam->setCookieJar(this->jar);
    qnam->post(request,payload);
}

int NetworkConnection::isAdded()
{
    return AddingStatus;
}

int NetworkConnection::isModified()
{
    return ModifyStatus;
}

int NetworkConnection::isRemoved()
{
    return RemoveStatus;
}

int NetworkConnection::isLogged()
{
    return LogStatus;
}
int NetworkConnection::isRegistered()
{
    return RegStatus;
}

int NetworkConnection::isDownloaded()
{
    return DownloadStatus;
}


void NetworkConnection::logOut()
{
    this->LogStatus = 0;
    this->RegStatus = 0;
    this->DownloadStatus = 0;
    this->RemoveStatus = 0;
    this->AddingStatus = 0;
    this->ModifyStatus = 0;
}

void NetworkConnection::ResponseReady(QNetworkReply *reply)
{
    if(reply->request().url().path() == "/app_login")
    {

    if(reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toInt() == 200)
    {
        LogStatus = 1;
        emit(Logged(true));
    } else {
        LogStatus = -1;
        emit(Logged(false));
    }
        //emit(Logged(false));
    }
    if(reply->request().url().path() == "/app_register")
    {
    if(reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toInt() == 200)
    {
        RegStatus = 1;
        emit(Registered(true));
    } else {
        RegStatus = -1;
        emit(Registered(false));
    }

    }

    if(reply->request().url().path() == "/app_getpasswords")
    {
    if(reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toInt() == 200)
    {
        DownloadStatus = 1;

    } else {
        DownloadStatus = -1;
    }
    QByteArray myData;
    myData = reply->readAll();
    QString asd = myData;
    QJsonDocument doc = QJsonDocument::fromJson(myData);
    emit(PassesDownloaded(myData));
    }

}
