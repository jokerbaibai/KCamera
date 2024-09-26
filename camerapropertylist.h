#ifndef CAMERAPROPERTYLIST_H
#define CAMERAPROPERTYLIST_H
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolBar>
#include <QSpinBox>
#include <QComboBox>
#include <QWidget>
#include <QObject>
#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
class CameraPropertyList:public QWidget
{
    Q_OBJECT
public:
    CameraPropertyList(QWidget* parent=0);
protected:
    QVBoxLayout* mainLayout;
};

#endif // CAMERAPROPERTYLIST_H
