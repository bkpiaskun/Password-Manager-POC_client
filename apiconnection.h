#ifndef APICONNECTION_H
#define APICONNECTION_H
#include <qstring>
#include <qurl>

class ApiConnection
{
public:
    ApiConnection();
    int postRequest(QString requestType, QUrl params);

};

#endif // APICONNECTION_H
