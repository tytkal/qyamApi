/************************************************************************************
  Author = Khalid Al-hussayen
  email = tytkal@gmail.com
  Date = Tue 19/3/1432 H
  The library contain objects of place restaurant tags classes
  ************************************************************************************/

#ifndef QYAMAPI_H
#define QYAMAPI_H

#include <QObject>
#include "place.h"
#include "restaurant.h"
#include "tags.h"
class qyamApi : public QObject
{
    Q_OBJECT
public:
    qyamApi(QString key = "");
    ~qyamApi();
    place *placeObj ;
    restaurant *restaurantObj ;
    tags *tagsObj ;
    void setKey(QString key);


};

#endif // QYAMAPI_H
