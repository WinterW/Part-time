#ifndef CNETWORKACCESSMANAGER_H
#define CNETWORKACCESSMANAGER_H
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class CNetWorkAccessManager : public QNetworkAccessManager
{
protected:
QNetworkReply *createRequest(Operation op, QNetworkRequest &req, QIODevice* outgoingData);
};

#endif // CNETWORKACCESSMANAGER_H
