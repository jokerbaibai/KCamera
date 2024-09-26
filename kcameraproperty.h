 #ifndef KCAMERAPROPERTY_H
#define KCAMERAPROPERTY_H
#include "cameraproperty.h"
#include "kcamerapropertylist.h"

class KCameraProperty:public CameraProperty
{
public:
    KCameraProperty();
    void setProperty(int offset,int value);


private:
    KCameraPropertyList* list;

};

#endif // KCAMERAPROPERTY_H

