#ifndef INTERFACELIST_H
#define INTERFACELIST_H
#include "InterfaceItem.h"
#include <vector>

/*
*接口列表类：维护接口列表的数据结构与使用接口
*/
class InterfaceList
{
public:
    InterfaceList();
    std::vector<InterfaceItem*> getList();
private:
    std::vector<InterfaceItem*> list;


};


#endif // INTERFACELIST_H
