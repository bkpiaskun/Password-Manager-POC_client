#ifndef RESTCONNECTION_H
#define RESTCONNECTION_H
#include <QString>

class RestConnection
{
public:
    RestConnection(QString Login,QString Password,QString URL);
    void SendRequest();

private:
    QString Login;
    QString Password;
    QString URL;

};

#endif // RESTCONNECTION_H
