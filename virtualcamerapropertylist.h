#ifndef VIRTUALCAMERAPROPERTYLIST_H
#define VIRTUALCAMERAPROPERTYLIST_H
#include "camerapropertylist.h"
class VirtualCameraPropertyList:public CameraPropertyList
{
    Q_OBJECT
public:
    VirtualCameraPropertyList(QWidget* parent);
private:
    QSpinBox* r;
    QSpinBox* g;
    QSpinBox* b;
    QComboBox* imageTypeComboBox;  //图像选择框
    QSpinBox* fps;
    void setr(int);
    void setg(int);
    void setb(int);
    void settype(int);
    void setfps(int);
signals:
    void rchanged(int val);
    void gchanged(int val);
    void bchanged(int val);
    void typechanged(int val);
    void fpschanged(int val);
};

#endif // VIRTUALCAMERAPROPERTYLIST_H
