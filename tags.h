/************************************************************************************
  Author = Khalid Al-hussayen
  email = tytkal@gmail.com
  Date = Tue 19/3/1432 H
  The library deal with tags functions for more info visit  the wep site:http://www.qaym.com/a/api_01_docs
  ************************************************************************************/

#ifndef TAGS_H
#define TAGS_H

#include <QObject>
#include "connection.h"
/* All the attributes that will be return from the tags functions
    will be store in the variables in the struct tagsAttribute */
struct tagsAttribute
{
    Type type;
    QString tag , tag_def_id , item_id , item_name  ;
};
/* some function return array of data the array will be store as a list of tagsAttribute */
typedef QList<tagsAttribute> tagsAttributeList ;
class tags : public QObject
{
    Q_OBJECT
public:
    tags(QString key = ""  ,connection *cp = new connection());
    ~tags();
    tagsAttribute t;
    /*******setter function*********/
    void setKey(QString key);
   /******* getter functions*******/
    void getTagsList();
    void getSpecialTagsList(QString tag_def_id);
    connection *c;
signals:
    /*parsingListFinshed(tagsAttributeList) Signal will apper when the parseToList(QByteArray) function finsh it jop */
    void parsingListFinshed(tagsAttributeList r);
public slots:
    /* parseToList(QByteArray) slot will parse the json data to the tagsAttributeList variables
        then it will send the parsingListFinshed(tagsAttributeList) signal*/
    void praseToList(QByteArray json);

};

#endif // TAGS_H
