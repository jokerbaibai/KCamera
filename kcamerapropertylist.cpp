#include "kcamerapropertylist.h"

KCameraPropertyList::KCameraPropertyList(QWidget* parent) {
    toolbar=new QToolBar();
    //标签页
    tabwidget=new QTabWidget();
    page1=new QTreeWidget();
    tabwidget->addTab(page1,"属性树");
    page2=new QTreeWidget();
    tabwidget->addTab(page2,"常用属性");
    page3=new QTreeWidget();
    tabwidget->addTab(page3,"触发");
    page4=new QTreeWidget();
    tabwidget->addTab(page4,"图像处理");
}
void KCameraPropertyList::set_frame_rate(int val){
    emit propertychanged(ICReg_Frame_Rate,val);
};
void KCameraPropertyList::set_exposure_mode(int val){
    emit propertychanged(ICReg_Exposure_Mode,val);
}
void KCameraPropertyList::set_exposure_time(int val){
    emit propertychanged(ICReg_Exposure_Mode,val);
}
void KCameraPropertyList::set_frame_size(int val){
    //emit propertychanged(ICReg_Fra,val);
}
void KCameraPropertyList::set_pixel_format(int){

}
void KCameraPropertyList::set_image_format(int val){
    emit propertychanged(ICReg_Image_Output,val);
}
void KCameraPropertyList::set_trigger_mode(int val){
    emit propertychanged(ICReg_Trig_Mode,val);
}
void KCameraPropertyList::set_digit_gain(int val){
    emit propertychanged(ICReg_Digital_Gain,val);
}
void KCameraPropertyList::set_rdigit_gain(int val){
    emit propertychanged(ICReg_RDigital_Gain,val);
}
void KCameraPropertyList::set_gdigit_gain(int val){
    emit propertychanged(ICReg_GDigital_Gain,val);
}
void KCameraPropertyList::set_bdigit_gain(int val){
    emit propertychanged(ICReg_BDigital_Gain,val);
}


void KCameraPropertyList::set_analog_gain(int val){
    emit propertychanged(ICReg_Analog_Gain,val);
}
void KCameraPropertyList::set_rwbalance_gain(int val){
    emit propertychanged(ICReg_RWhite_Balance,val);
}
void KCameraPropertyList::set_gwbalance_gain(int val){
    emit propertychanged(ICReg_GWhite_Balance,val);
}
void KCameraPropertyList::set_bwbalance_gain(int val){
    emit propertychanged(ICReg_BWhite_Balance,val);
}


void KCameraPropertyList::set_camera_delay(int val){
    emit propertychanged(ICReg_Camera_TrigDelay,val);
}
void KCameraPropertyList::set_light_delay(int val){
    emit propertychanged(ICReg_Light_TrigDelay,val);
}
void KCameraPropertyList::set_light_pulse(int val){
    emit propertychanged(ICReg_Light_PulseWidth,val);
}
