#include "restaurant.h"
#include "jsonParser/parser.h"
#include <cstdlib>

restaurant::restaurant(QString key, connection *cp)
{
    c = cp;
    c->setAPIKey(key);
}
restaurant::~restaurant()
{
    delete c ;
}

void restaurant::setKey(QString key)
{
    c->setAPIKey(key);
}

void restaurant::getRestaurantInfo(QString item_id)
{
    QString url = "items/"+item_id+"/key=";
    r.type = RestaurantInfo ;
    c->getData(url);

    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(praseJson(QByteArray)));
}

void restaurant::getBranchInfoList(QString item_id)
{
    QString url = "items/"+item_id+"/locations/key=";
    c->getData(url);
    r.type = BranchInfoList;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(praseToList(QByteArray)));
}

void restaurant::getEvaluationList(QString item_id)
{
    QString url = "items/"+item_id+"/reviews/key=";
    c->getData(url);
    r.type = EvaluationList ;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(praseToList(QByteArray)));
}

void restaurant::getPictureList(QString item_id)
{
    QString url = "items/"+item_id+"/images/key=";
    c->getData(url);
    r.type = PictureList ;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(praseToList(QByteArray)));
}

void restaurant::getvotesList(QString item_id)
{
    QString url = "items/"+item_id+"/votes/key=";
    c->getData(url);
    r.type = votesList;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(praseSpecial(QByteArray)));
}

void restaurant::praseJson(QByteArray json)
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
    if(r.type == RestaurantInfo)
    {
        r.item_id = resulTemp["item_id"].toString();
        r.item_name = resulTemp["item_name"].toString();
        r.url = resulTemp["url"].toString();
        r.score = resulTemp["score"].toString();
        r.vote_count = resulTemp["vote_count"].toString();
        r.ratio = resulTemp["ratio"].toString();
        r.weighted_score = resulTemp["weighted_score"].toString();
        r.username = resulTemp["username"].toString();
        r.user_id = resulTemp["user_id"].toString();
    }

     emit parsingFinshed(r);
}

void restaurant::praseToList(QByteArray json)
{
    restaurantAttributeList attributeList;
    QJson::Parser parser;
    bool ok ;
    if(json == "Invalid API Key supplied")
    {
        qFatal("Invalid API Key");
        exit (1);
    }
    QVariantList result = parser.parse (json, &ok).toList();
    if (!ok)
    {
        qFatal("An error occurred during parsing");
        exit (1);
    }
    if(r.type == BranchInfoList)
    {
        for(int i=0 ; i < result.size() ; i++)
        {
            QVariantMap resulTemp = result[i].toMap();
            r.country = resulTemp["country"].toString();
            r.city = resulTemp["city"].toString();
            r.location_id = resulTemp["location_id"].toString();
            r.score = resulTemp["score"].toString();
            r.address = resulTemp["address"].toString();
            r.user_id = resulTemp["user_id"].toString();
            r.latitude = resulTemp["latitude"].toString();
            r.longitude = resulTemp["longitude"].toString();
            r.title = resulTemp["title"].toString();
            r.phone = resulTemp["phone"].toString();
            r.tiny_thumb_file_detail_id = resulTemp["tiny_thumb_file_detail_id"].toString();
            r.username = resulTemp["username"].toString();
            r.city_id = resulTemp["city_id"].toString();
            r.country_id = resulTemp["country_id"].toString();
             attributeList.append(r);
        }
    }
    else if(r.type ==  PictureList)
    {
        for(int i=0 ; i < result.size() ; i++)
        {
            QVariantMap resulTemp = result[i].toMap();
            r.username = resulTemp["username"].toString();
            r.title = resulTemp["title"].toString();
            r.user_id = resulTemp["user_id"].toString();
            r.score = resulTemp["score"].toString();
            r.time = resulTemp["time"].toString();
            r.number_of_posts = resulTemp["number_of_posts"].toString();
            r.last_poster_id = resulTemp["last_poster_id"].toString();
            r.last_post_time = resulTemp["last_post_time"].toString();
            r.text = resulTemp["text"].toString();
            r.last_edit_user_id = resulTemp["last_edit_user_id"].toString();
            r.last_edit_time = resulTemp["last_edit_time"].toString();
             attributeList.append(r);
        }
    }
        else if(r.type ==  PictureList)
        {
            for(int i=0 ; i < result.size() ; i++)
            {
                QVariantMap resulTemp = result[i].toMap();
                r.username = resulTemp["username"].toString();
                r.user_id = resulTemp["user_id"].toString();
                r.file_detail_id = resulTemp["file_detail_id"].toString();
                r.title = resulTemp["title"].toString();
                 attributeList.append(r);
            }
        }


        emit parsingListFinshed(attributeList);
}

void restaurant::praseSpecial(QByteArray json)
{
    restaurantAttributeList attributeList;
    QJson::Parser parser;
    bool ok ;
    if(json == "Invalid API Key supplied")
    {
        qFatal("Invalid API Key");
        exit (1);
    }
    QVariantMap resultMap = parser.parse (json, &ok).toMap();
    if (!ok)
    {
        qFatal("An error occurred during parsing");
        exit (1);
    }
    QVariantList resultListUp = resultMap["up"].toList();
    QVariantList resultListDown = resultMap["down"].toList();
    if (resultListUp.size() > resultListDown.size())
     {
        for(int i = 0 ; i < resultListUp.size() ; i++)
        {
            QVariantMap resulTempUp = resultListUp.at(i).toMap();
            if(i < resultListDown.size())
            {
                QVariantMap resulTempDown = resultListDown.at(i).toMap();
                r.down_vote = resulTempDown["vote"].toString();
                r.down_user_id = resulTempDown["user_id"].toString();
                r.down_username = resulTempDown["username"].toString();
            }
            else
            {
                r.down_vote = "";
                r.down_user_id = "";
                r.down_username = "";
             }
            r.up_vote = resulTempUp["vote"].toString();
            r.up_user_id = resulTempUp["user_id"].toString();
            r.up_username = resulTempUp["username"].toString();
            attributeList.append(r);
        }
    }
    else
    {
        for(int i = 0 ; i < resultListDown.size() ; i++)
        {
            QVariantMap resulTempDown = resultListDown.at(i).toMap();
            if(i < resultListUp.size())
            {
                QVariantMap resulTempUp = resultListUp.at(i).toMap();
                r.up_vote = resulTempUp["vote"].toString();
                r.up_user_id = resulTempUp["user_id"].toString();
                r.up_username = resulTempUp["username"].toString();
            }
            else
            {
                r.up_vote = "";
                r.up_user_id = "";
                r.up_username = "";
             }
            r.down_vote = resulTempDown["vote"].toString();
            r.down_user_id = resulTempDown["user_id"].toString();
            r.down_username = resulTempDown["username"].toString();
            attributeList.append(r);
        }
    }

    emit parsingListFinshed(attributeList);
}
