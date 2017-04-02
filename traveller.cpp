/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：traveller.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了Traveller类中，各成员函数的实现，用于
 *         程序数据的备份，在Traveller.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数。
 */

/*包含头文件*/

#include "traveller.h"

/*
 * 函数名称：Traveller::DisplayObjectInfo
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为调试，打印旅客信息。
 */

void Traveller::DisplayObjectInfo(){
    qDebug()<<this->name;
    qDebug()<<this->identNum;
    qDebug()<<this->nowStatus;
    qDebug()<<this->seqNum;
    qDebug()<<this->moneyConsum;
    qDebug()<<this->timeConsum;
}

/*
 * 函数名称：Traveller::Traveller
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为默认构造函数，进行初始化。
 */

Traveller::Traveller()
{

}

/*
 * 函数名称：Traveller::~Traveller
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为默认析构函数。
 */

Traveller::~Traveller(){

}
