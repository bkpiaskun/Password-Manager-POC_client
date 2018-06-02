#include "apiconnection.h"
#include <qDebug>
#include <qString>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>


ApiConnection::ApiConnection()
{

}
int ApiConnection::postRequest(QString requestType, QUrl params){
    QString params_array = params.query();

    //user->url
    QNetworkRequest request;

    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(params_array.size()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QEventLoop waitLoop;
    QNetworkAccessManager* connection = new QNetworkAccessManager(/*`this` can also be passed*/);
    QNetworkReply* reply = connection->post(request, params_array.toUtf8());
    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    int errorCode = reply->error();
    if (errorCode != 0){
        // Show Error Message
    }
    else{
        // Parse "reply"
        qDebug() << reply;
    }

    delete reply;
    delete connection;
    return errorCode;
}
