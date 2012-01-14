#include "tags.h"
#include <cstdlib>
#include "jsonParser/parser.h"

tags::tags(QString key, connection *cp)
{
    c = cp;
    c->setAPIKey(key);
}
tags::~tags()
{
    delete c ;
}

void tags::setKey(QString key)
{
    c->setAPIKey(key);
}

void tags::getTagsList()
{
    QString url = "tags/key=";
    c->getData(url);
    t.type = TagsList;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(praseToList(QByteArray)));
}

void tags::getSpecialTagsList(QString tag_def_id)
{
    QString url = "tags/"+tag_def_id+"/items/key=";
    c->getData(url);
    t.type = SpecialTagsList ;
    connect(c,SIGNAL(finshed(QByteArray)),this,SLOT(praseToList(QByteArray)));
}

void tags::praseToList(QByteArray json)
{
    tagsAttributeList attributeList;
    // qFatal(json);
    QJson::Parser parser;
    bool ok ;
    QVariantList result = parser.parse (json, &ok).toList();
    if(json == "Invalid API Key supplied")
    {
        qFatal("Invalid API Key");
        exit (1);
    }
    if (t.type == TagsList)
    {
        for(int i=0 ; i < result.size() ; i++)
        {
            QVariantMap resulTemp = result[i].toMap();
            t.tag = resulTemp["tag"].toString();
            t.tag_def_id = resulTemp["tag_def_id"].toString();
            attributeList.append(t);
        }
    }
    else if (t.type == SpecialTagsList)
    {
        for(int i=0 ; i < result.size() ; i++)
        {
            QVariantMap resulTemp = result[i].toMap();
            t.item_id = resulTemp["item_id"].toString();
            t.item_name = resulTemp["item_name"].toString();
            attributeList.append(t);
        }
    }

    emit parsingListFinshed(attributeList);
}
