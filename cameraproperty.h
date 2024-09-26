#ifndef CAMERAPROPERTY_H
#define CAMERAPROPERTY_H
#include <iostream>
#include <QWidget>
//Json库
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
class CameraProperty:public QWidget
{
    Q_OBJECT
public:
    CameraProperty();
    //std::map<int,int> Data(){
    //    return data;
    //}
    //virtual uint8_t* setData()=0;

    // 保存属性到文件
    //virtual void saveToFile(const std::string& filename) const=0;
    // 从文件读取属性
    //virtual void loadFromFile(const std::string& filename)=0;
protected:
    //std::map<int,int> data;
signals:
    void modify(int id,int value);

};

#endif // CAMERAPROPERTY_H

