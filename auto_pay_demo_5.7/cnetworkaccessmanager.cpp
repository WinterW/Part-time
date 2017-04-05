#include "cnetworkaccessmanager.h"

QNetworkReply *CNetWorkAccessManager::createRequest(Operation op, QNetworkRequest &req, QIODevice* outgoingData)
{

    QString req_url = req.url().toString();
    QNetworkReply *reply = this->createRequest(op, req, outgoingData);

    return reply;
}

