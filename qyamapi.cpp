#include "qyamapi.h"

qyamApi::qyamApi(QString key)
{
    placeObj = new place(key);
    restaurantObj = new restaurant(key);
    tagsObj = new tags(key);
}
qyamApi::~qyamApi()
{
    delete placeObj;
    delete restaurantObj;
    delete tagsObj;
}

void qyamApi::setKey(QString key)
{
   placeObj->setKey(key);
    restaurantObj->setKey(key);
    tagsObj->setKey(key);
}
