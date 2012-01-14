#include "place.h"
#include <cstdlib>
#include "jsonParser/parser.h"

place::place(QString key, connection *cp)
{
    c = cp;
    c->setAPIKey(key);
}
place::~place()
{
    delete c ;
}
void place::setKey(QString key)
{
    c->setAPIKey(key);
}

void place::getcountriesList()
{
    QString url = "countries/key=";
    c->getData(url);
    a.type = countriesList;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(parseToList(QByteArray)));
}


void place::getcountrieInfo(QString country_id)
{
    QString url = "countries/"+country_id+"/key=";
    c->getData(url);
    a.type = countrieInfo;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(parseJson(QByteArray)));
}

void place::getCitiesInCountryList(QString country_id)
{
    QString url = "countries/"+country_id+"/cities/key=";
    c->getData(url);
    a.type = CitiesInCountryList;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(parseToList(QByteArray)));
}
void place::getcitiesList()
{
    QString url = "cities/key=";
    c->getData(url);
    a.type = citiesList;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(parseToList(QByteArray)));
}
void place::getCitieInfo(QString city_id)
{
    QString url = "cities/"+city_id+"/key=";
    c->getData(url);
    a.type = CitieInfo;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(parseJson(QByteArray)));
}
void place::getItemList(QString city_id)
{
    QString url = "cities/"+city_id+"/items/key=";
    c->getData(url);
    a.type = ItemList ;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(parseToList(QByteArray)));
}
void place::getItemTopList(QString city_id)
{
    QString url = "cities/"+city_id+"/items/top/key=";
    c->getData(url);
    a.type = ItemTopList;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(parseToList(QByteArray)));
}

/****************** Parsing Functions*************************/
void place::parseJson(QByteArray json)
{
    if(json == "Invalid API Key supplied")
    {
        qFatal("Invalid API Key");
        exit (1);
    }
    QJson::Parser parser;
    bool ok ;
    QVariantMap resulTemp = parser.parse (json, &ok).toMap();
    if (!ok)
    {
        qFatal("An error occurred during parsing");
        exit (1);
    }
    if(json == "false")
    {
        qFatal("ERROR");
    }
    else if (a.type == countrieInfo)
    {
        a.name = resulTemp["name"].toString();
        a.country_id = resulTemp["country_id"].toString();
        a.added_by = resulTemp["added_by"].toString();
        a.addition_timestamp = resulTemp["addition_timestamp"].toString();
        a.latitude = resulTemp["latitude"].toString();
        a.longitude = resulTemp["longitude"].toString();
        a.zoom = resulTemp["zoom"].toString();
    }
    else if(a.type == CitieInfo)
    {
        a.city_id = resulTemp["city_id"].toString();
        a.name = resulTemp["name"].toString();
        a.added_by = resulTemp["added_by"].toString();
        a.addition_timestamp = resulTemp["addition_timestamp"].toString();
        a.latitude = resulTemp["latitude"].toString();
        a.longitude = resulTemp["longitude"].toString();
        a.zoom = resulTemp["zoom"].toString();
    }

    emit parsingFinshed(a);
}

void place::parseToList(QByteArray json)
{
    if(json == "Invalid API Key supplied")
    {
        qFatal("Invalid API Key");
        exit (1);
    }
    placeAttributeList attributeList;
    QJson::Parser parser;
    bool ok ;
    QVariantList result = parser.parse (json, &ok).toList();
    if (!ok)
    {
        qFatal("An error occurred during parsing");
        exit (1);
    }
    if(json == "false")
    {
        qFatal("ERROR");
    }
    else if(a.type == countriesList)
    {
        for(int i =0 ; i < result.size()  ; i++)
        {

            QVariantMap resulTemp = result[i].toMap();
            a.name = resulTemp["name"].toString();
            a.country_id = resulTemp["country_id"].toString();
            attributeList.append(a);
        }
    }
    else if(a.type == CitiesInCountryList )
    {
        for(int i =0 ; i < result.size()  ; i++)
        {

            QVariantMap resulTemp = result[i].toMap();
            a.city_id = resulTemp["city_id"].toString();
            a.name = resulTemp["name"].toString();
            a.added_by = resulTemp["added_by"].toString();
            a.addition_timestamp = resulTemp["addition_timestamp"].toString();
            a.latitude = resulTemp["latitude"].toString();
            a.longitude = resulTemp["longitude"].toString();
            a.zoom = resulTemp["zoom"].toString();
            attributeList.append(a);
        }
    }
    else if(a.type == citiesList )
    {
        for(int i =0 ; i < result.size()  ; i++)
        {

            QVariantMap resulTemp = result[i].toMap();
            a.city_id = resulTemp["city_id"].toString();
            a.name = resulTemp["name"].toString();
            a.added_by = resulTemp["added_by"].toString();
            a.addition_timestamp = resulTemp["addition_timestamp"].toString();
            a.latitude = resulTemp["latitude"].toString();
            a.longitude = resulTemp["longitude"].toString();
            a.zoom = resulTemp["zoom"].toString();
            attributeList.append(a);
        }
    }
    else if(a.type == ItemList )
    {
        for(int i =0 ; i < result.size()  ; i++)
        {
            QVariantMap resulTemp = result[i].toMap();
            a.item_id = resulTemp["item_id"].toString();
            a.item_name = resulTemp["item_name"].toString();
            attributeList.append(a);
        }
    }
    else if(a.type == ItemTopList )
    {
        for(int i =0 ; i < result.size()  ; i++)
        {
            QVariantMap resulTemp = result[i].toMap();
            a.item_id = resulTemp["item_id"].toString();
            a.item_name = resulTemp["item_name"].toString();
            a.number_of_negative_votes = resulTemp["number_of_negative_votes"].toString();
            a.number_of_positive_votes = resulTemp["number_of_positive_votes"].toString();
            a.ratio = resulTemp["ratio"].toString();
            a.score = resulTemp["score"].toString();
            a.total_number_of_votes = resulTemp["total_number_of_votes"].toString();
            a.weighted_score = resulTemp["country_id"].toString();
            attributeList.append(a);
        }
    }

    emit parsingListFinshed(attributeList);
}
