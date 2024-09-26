#include "virtualcameraproperty.h"

VirtualCameraProperty::VirtualCameraProperty() {
    list=new VirtualCameraPropertyList(this);
    connect(list,&VirtualCameraPropertyList::rchanged,this,&VirtualCameraProperty::setRed);
    connect(list,&VirtualCameraPropertyList::gchanged,this,&VirtualCameraProperty::setGreen);
    connect(list,&VirtualCameraPropertyList::bchanged,this,&VirtualCameraProperty::setBlue);
    connect(list,&VirtualCameraPropertyList::typechanged,this,&VirtualCameraProperty::setType);
    connect(list,&VirtualCameraPropertyList::fpschanged,this,&VirtualCameraProperty::setFps);

}

void VirtualCameraProperty::setRed(int red) {
    r = red;
    emit modify(rId,r);
}
void VirtualCameraProperty::setGreen(int green) {
    g = green;
    emit modify(gId,g);
}
void VirtualCameraProperty::setBlue(int blue) {
    b = blue;
    emit modify(bId,b);
}
void VirtualCameraProperty::setType(int type){
    type_=type;
    emit modify(typeId,type_);
}
void VirtualCameraProperty::setFps(int fps){
    fps_=fps;
    emit modify(fpsId,fps_);
}
VirtualCameraPropertyList* VirtualCameraProperty::getList(){
    return list;
}
