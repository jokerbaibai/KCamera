#include "virtualcamerapropertylist.h"

VirtualCameraPropertyList::VirtualCameraPropertyList(QWidget* parent):CameraPropertyList(parent) {
    r=new QSpinBox();
    r->setPrefix("R:");
    r->setMaximum(255);
    r->setMinimum(0);
    g=new QSpinBox();
    g->setPrefix("G:");
    g->setMaximum(255);
    g->setMinimum(0);
    b=new QSpinBox();
    b->setPrefix("B:");
    b->setMaximum(255);
    b->setMinimum(0);
    mainLayout=new QVBoxLayout();
    mainLayout->addWidget(r);
    mainLayout->addWidget(g);
    mainLayout->addWidget(b);

    connect(r,&QSpinBox::valueChanged,this,&VirtualCameraPropertyList::setr);
    connect(g,&QSpinBox::valueChanged,this,&VirtualCameraPropertyList::setg);
    connect(b,&QSpinBox::valueChanged,this,&VirtualCameraPropertyList::setb);
    // 初始化图像类型选择框
    imageTypeComboBox = new QComboBox(this);
    imageTypeComboBox->addItem("纯色图像");
    imageTypeComboBox->addItem("棋盘图像");
    imageTypeComboBox->addItem("渐变图像");
    imageTypeComboBox->addItem("随机噪声图像");
    imageTypeComboBox->addItem("条纹图像");
    mainLayout->addWidget(imageTypeComboBox);

    connect(imageTypeComboBox,&QComboBox::currentIndexChanged,this,&VirtualCameraPropertyList::settype);
    fps=new QSpinBox();
    fps->setPrefix("相机帧率:");
    fps->setMaximum(40);
    fps->setMinimum(1);
    mainLayout->addWidget(fps);
    connect(fps,&QSpinBox::valueChanged,this,&VirtualCameraPropertyList::setfps);
    setLayout(mainLayout);
}
void VirtualCameraPropertyList::setr(int val){
    emit rchanged(val);
}
void VirtualCameraPropertyList::setg(int val){
    emit gchanged(val);
}
void VirtualCameraPropertyList::setb(int val){
    emit bchanged(val);
}
void VirtualCameraPropertyList::settype(int val){
    emit typechanged(val);
}
void VirtualCameraPropertyList::setfps(int val){
    emit fpschanged(val);
}
