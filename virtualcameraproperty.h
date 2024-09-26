#ifndef VIRTUALCAMERAPROPERTY_H
#define VIRTUALCAMERAPROPERTY_H
#include "cameraproperty.h"
#include "virtualcamerapropertylist.h"
class VirtualCameraProperty:public CameraProperty
{
    Q_OBJECT
public:
    VirtualCameraProperty();
    //uint8_t* setData() override;
    // 设置 RGB 值的函数
    void setRed(int red);
    void setGreen(int green);
    void setBlue(int blue);
    void setType(int type);
    void setFps(int fps);
    //返回列表
    VirtualCameraPropertyList* getList();

    // 保存属性到文件
    //void saveToFile(const std::string& filename)  const override;
    // 从文件读取属性
    //void loadFromFile(const std::string& filename) override;

private:
    //属性值
    int r;      //红色分量的值
    int g;      //绿色分量的值
    int b;      //蓝色分量的值
    int type_;   //图像的类型，默认纯色
    int fps_;    //相机传图帧率
    //一一对应的ID
    const int rId=0;
    const int gId=1;
    const int bId=2;
    const int typeId=3;
    const int fpsId=4;

    //属性栏
    VirtualCameraPropertyList* list;
};

#endif // VIRTUALCAMERAPROPERTY_H
