/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：traveller.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个Traveller类，用于记录加入旅行的旅客的所有信息，在
 *         mainwindow.cpp中实例化并使用该类。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef TRAVELLER_H
#define TRAVELLER_H

/*包含头文件*/

#include <QApplication>
#include <vector>
#include <list>
#include <QDebug>
#include <QDate>
#include "datastructure.h"

/*
 * 类名称：Traveller
 * 功能描述：该类用于记录系统中所有旅客的信息。
 */

class Traveller
{
public:
    QString name;//姓名
    QString identNum;//身份证号
    unsigned int seqNum;//旅客号
    TravelStatus nowStatus;//旅客当前状态
    std::list<TravelCityInfo> pathList;//记录旅行路线
    unsigned int moneyConsum;//金钱消耗
    unsigned int timeConsum;//时间消耗
    QDate startDate;//出发日期
    bool waitNextDay;//是否等待第二天

    void DisplayObjectInfo();//测试用

    Traveller();//构造函数
    ~Traveller();//析构函数
private:

};

#endif // TRAVELLER_H
