#include "restconnection.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QByteArray>
#include <QNetworkCookieJar>
#include <QEventLoop>
#include <QObject>



RestConnection::RestConnection(QString Login,QString Password,QString URL)
{
    this->Login = Login;
    this->Password = Password;
    this->URL = URL;

}


void RestConnection::SendRequest()
{

    QVariantMap feed;
    feed.insert("login",this->Login);
    feed.insert("password",this->Password);
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();

    QUrl myurl;
    myurl.setScheme("http"); //https also applicable
    myurl.setHost(this->URL);
    myurl.setPath("/app_login");

    qDebug() << myurl.toString();

    QNetworkRequest request;
    request.setUrl(myurl);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");


    QNetworkAccessManager *restclient; //in class
    restclient = new QNetworkAccessManager(); //constructor
    QNetworkCookieJar jar;
    //restclient->setCookieJar(jar);
    QNetworkReply *reply = restclient->post(request,payload);

    //while(restclient->finished();)
    //qDebug()<< reply->readAll();
    qDebug() << reply->readAll();
    qDebug() << reply->rawHeaderList();
    qDebug() << reply->attribute((QNetworkRequest::HttpStatusCodeAttribute)).toString();
    qDebug() << reply->errorString();
    qDebug() << reply->error();
    qDebug() << reply->rawHeaderPairs();
    qDebug() << reply->registerUserData();
    qDebug() << reply->Text;
    qDebug() << reply;


}



