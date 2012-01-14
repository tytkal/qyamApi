/************************************************************************************
  Author = Khalid Al-hussayen
  email = tytkal@gmail.com
  Date = WED 13/3/1432 H
  The library deal with  networks
  ************************************************************************************/
#ifndef CONNECTION_H
#define CONNECTION_H
#include <QObject>
#include <QtNetwork/QNetworkReply>
/* the enum Type will not be used by the connection class but it will be used  by any class that use connection
the main idea of enum is to detect wich function have call the getData()  */
enum Type{countriesList,countrieInfo,CitiesInCountryList,citiesList,CitieInfo,ItemList,ItemTopList
      ,RestaurantInfo,BranchInfoList,EvaluationList,PictureList,votesList
  ,TagsList,SpecialTagsList};
class connection : public QObject
{
    Q_OBJECT
public:
    explicit connection(QObject *parent = 0);
    /*setKey(QString) function set the API Key that should be token from http://www.qaym.com/a/get_api_key*/
    void setAPIKey(QString keyAPI);
    void getData(QString url);

signals:
    /*finshed(QByteArray) Signal will apper when the data be ready to use*/
    void finshed(QByteArray);

public slots:
    /*setData(QNetworkReply *r) slot have two main goal 1-it will rescive data when QNetworkAccessManager finsh it work
      2- it send the finshed(QByteArray) Signal  */
    void setData(QNetworkReply *r);
private:
    QString key;

};

#endif // CONNECTION_H
