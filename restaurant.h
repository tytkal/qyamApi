/************************************************************************************
  Author = Khalid Al-hussayen
  email = tytkal@gmail.com
  Date = Tue 19/3/1432 H
  The library deal with restaurant functions for more info vist  the wep site:http://www.qaym.com/a/api_01_docs
  ************************************************************************************/
#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QObject>
#include "connection.h"
/* All the attributes that will be return from the restaurant functions
    will be store in the variables in the struct restaurantAttribute */

struct restaurantAttribute
{
    Type type;
    QString item_id , item_name ,  url , score , vote_count , ratio , weighted_score , username ,
    user_id , country , city , location_id , address , latitude , longitude , title , phone ,
    tiny_thumb_file_detail_id , city_id , country_id , time , number_of_posts , last_poster_id ,
    last_post_time , text , last_edit_user_id , last_edit_time , file_detail_id , up_vote , up_user_id ,
    up_username , down_vote , down_user_id , down_username;
};
/* some function return array of data the array will be store as a list of restaurantAttribute */
typedef QList<restaurantAttribute> restaurantAttributeList ;
class restaurant : public QObject
{
    Q_OBJECT
public:
    restaurant(QString key = ""  ,connection *cp = new connection());
    ~restaurant();
    restaurantAttribute r;
    /*******setter function*********/
    void setKey(QString key);
   /******* getter functions*******/
    void getRestaurantInfo(QString item_id);
    void getBranchInfoList(QString item_id);
    void getEvaluationList(QString item_id);
    void getPictureList(QString item_id);
    void getvotesList(QString item_id);
    connection *c;
signals:
    /*parsingListFinshed(restaurantAttributeList) Signal will apper when the parseToList(QByteArray) function finsh it jop */
    void parsingListFinshed(restaurantAttributeList r);
    /*parsingFinshed(restaurantAttribute) signal will apper when the praceJson(QByteArray) function finsh it jop */
    void parsingFinshed(restaurantAttribute r);
public slots:
    /* parseToList(QByteArray) slot will parse the json data to the restaurantAttributeList variables
        then it will send the parsingListFinshed(restaurantAttributeList) signal*/
    void praseToList(QByteArray json);
    /*praceJson(QByteArray) slot will parse the json data to the restaurantAttribute variables
      then it will send the parsingFinshed(restaurantAttribute) signal */
    void praseJson(QByteArray json);
    /*getvotesList(QString) function need a special prase so praseSpecial(QByteArray) do the job*/
    void praseSpecial(QByteArray json);

};

#endif // RESTAURANT_H
