QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network
QT += multimedia
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CameraView.cpp \
    CameraWindow.cpp \
    CommandSender.cpp \
    DeviceDelegate.cpp \
    DisplayArea.cpp \
    InterfaceItem.cpp \
    InterfaceList.cpp \
    InterfaceListWidget.cpp \
    KBaseCamera.cpp \
    KDataProcessor.cpp \
    KImageFrame.cpp \
    KVirtualCamera.cpp \
    SaveFile.cpp \
    cameraproperty.cpp \
    camerapropertylist.cpp \
    crosslineitem.cpp \
    gridlineitem.cpp \
    interfacearea.cpp \
    kcameraproperty.cpp \
    kcamerapropertylist.cpp \
    main.cpp \
    mainwindow.cpp \
    virtualcameraproperty.cpp \
    virtualcamerapropertylist.cpp

HEADERS += \
    CameraView.h \
    CameraWindow.h \
    CommandSender.h \
    DeviceDelegate.h \
    DisplayArea.h \
    InterfaceItem.h \
    InterfaceList.h \
    InterfaceListWidget.h \
    KBaseCamera.h \
    KDataProcessor.h \
    KICTypeDef.h \
    KImageFrame.h \
    KVirtualCamera.h \
    SaveFile.h \
    cameraproperty.h \
    camerapropertylist.h \
    crosslineitem.h \
    gridlineitem.h \
    interfacearea.h \
    kcameraproperty.h \
    kcamerapropertylist.h \
    mainwindow.h \
    virtualcameraproperty.h \
    virtualcamerapropertylist.h

FORMS += \
    mainwindow.ui
# Include paths for npcap and OpenCV
INCLUDEPATH += C:/MyProgram/npcap-sdk/npcap-sdk-1.13/Include \
                 D:/work/keyetech/opencv/build/include \
                 D:/work/keyetech/opencv/build/include/opencv2

# Library paths and linking for npcap and OpenCV
LIBS += -LC:/MyProgram/npcap-sdk/npcap-sdk-1.13/Lib/x64 -lwpcap

LIBS += -LD:/work/keyetech/opencv/build/x64/vc15/lib \
        -lopencv_world412 \
        -lopencv_world412d

LIBS += -lws2_32
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
