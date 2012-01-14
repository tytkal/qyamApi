#include "connection.h"
//host Path
const QString hostUrl = "http://api.qaym.com/0.1/";
connection::connection(QObject *parent) :
    QObject(parent)
{
}

void connection::setAPIKey(QString keyAPI)
{
    key = keyAPI;
}

void connection::getData(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->get(QNetworkRequest(hostUrl+url+key));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(setData(QNetworkReply*)));
}

void connection::setData(QNetworkReply *r)
{
    emit finshed(r->readAll());
}
