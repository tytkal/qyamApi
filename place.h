/************************************************************************************
  Author = Khalid Al-hussayen
  email = tytkal@gmail.com
  Date = WED 13/3/1432 H
  The library deal with places functions for more info visit  the wep site:http://www.qaym.com/a/api_01_docs
  ************************************************************************************/
#ifndef PLACE_H
#define PLACE_H

#include <QObject>
#include "connection.h"
/* All the attributes that will be return from the places functions
    will be store in the variables in the struct placeAttribute */
struct placeAttribute
{
    Type type;
    QString name ,country_id , added_by , addition_timestamp , latitude , longitude ,
    zoom , city_id , item_name , item_id , score , weighted_score , ratio , tags ,
    total_number_of_votes , number_of_positive_votes , number_of_negative_votes;
};
/* some function return array of data the array will be store as a list of placeAttribute */
typedef QList<placeAttribute> placeAttributeList;
class place : public QObject
{
    Q_OBJECT
public:
     place( QString key = ""  ,connection *cp = new connection() );
     ~place();
     placeAttribute a;
     /*******setter function*********/
     void setKey(QString key);
    /******* getter functions*******/
    void getcountriesList();
    void getcountrieInfo(QString country_id);
    void getCitiesInCountryList(QString country_id);
    void getcitiesList();
    void getCitieInfo(QString country_id);
    void getItemList(QString city_id);
    void getItemTopList(QString city_id);
    connection *c;
signals:
    /*parsingListFinshed(placeAttributeList) Signal will apper when the parseToList(QByteArray) function finsh it jop */
    void parsingListFinshed(placeAttributeList p);
    /*parsingFinshed(placeAttribute) signal will apper when the praceJson(QByteArray) function finsh it jop */
    void parsingFinshed(placeAttribute p);
public slots:
    /* parseToList(QByteArray) slot will parse the json data to the placeAttributeList variables
        then it will send the parsingListFinshed(placeAttributeList) signal*/
    void parseToList(QByteArray json);
    /*praceJson(QByteArray) slot will parse the json data to the placeAttribute variables
      then it will send the parsingFinshed(placeAttribute) signal */
    void parseJson(QByteArray json);

};

#endif // PLACE_H
