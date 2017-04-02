/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：map.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个Map类，用于寻路模块的计算，在
 *         choosewayDialog.cpp中实例化并使用该类，打印出具体的
 *         路线。
 * 修改日志：
 *  2016.6.4  李一鸣 将部分成员函数和变量改为private，完善了注释
 *  2016.6.1  李一鸣 去掉了多余的成员变量
 *  2016.5.22 李一鸣 加入了限时最少金钱的定义及相关函数
 *  2016.5.17 李一鸣 加入了最少金钱和最少时间的函数定义，加入了其他相关函数
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef MAP_H
#define MAP_H

/*包含头文件*/

#include <QApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

#include "datastructure.h"

#include <vector>
#include <list>
#include <iterator>
#include <queue>
#include <algorithm>

/*
 * 类名称：Map
 * 功能描述：该类用于实现三种策略的算法。最少金钱策略和最少时间策略
 *     使用A*算法，限时最少时间策略使用DFS并配合剪枝优化，三个策略
 *     的实现均使用了状态压缩的思想。
 */

class Map
{
public://
    std::list<TravelCityInfo> nowPathLeast;//记录限时最少金钱的当前最优路径
    int nowMoneyLeast;//记录限时最少金钱的当前最优耗费
    int nowTimeSum;//记录限时最少金钱的当前最优时间耗费
    int setUpperBound;//限时最少金钱的时间上限

    //三种策略
    std::list<TravelCityInfo> * LeastTime(Cities startCity, Cities endCity, int &currentTime, int &timeSum);//最短时间
    std::list<TravelCityInfo> * LeastMoney(Cities startCity, Cities endCity, int &currentTime, int &timeSum);//最少金钱
    std::list<TravelCityInfo> * LimitTime(Cities startCity, Cities endCity, int currentTime,
                                          std::list<PassCityInfo> passCity, int upperBound);//限时最少费用

    Map();//构造函数
    ~Map();//析构函数

private:
    //A*算法中使用的链表结构
    std::list<CityNode> openList;
    std::list<CityNode> closeList;
    std::list<CityNode> neitherList;

    unsigned int cityAmount;//城市数量

    CityInfo InitCityInfo(Cities city);//初始化城市信息

    //A*算法中的估价函数
    int H_Function_Money(Cities source, Cities target);
    int H_Function_Time(Cities source, Cities target);

    //A*算法中，生成两点间的最优路径
    CityNode TwoCityLeastMoney(Cities a, Cities b);
    CityNode TwoCityLeastTime(Cities a, Cities b, int currentTime);

    //A*算法的判断函数
    bool inOpen(int x);
    bool inClose(int x);

    //Cities枚举类型的相关格式转换
    Cities IntIntoCity(int i);
    int CityToInt(Cities i);
    QString CityToNumString(Cities city);

    void LimitTime_TrackBack(CityInfo nowCity, Cities endCity, int currentTime, int nowMoney,
                            std::list<TravelCityInfo> nowPath, std::list<PassCityInfo> passCity, int upperBound);//限时最少金钱策略的递归函数

    std::list<TravelCityInfo> * MakeWay(Cities startCity, Cities endCity, int &timeSum);//生成A*算法的路径
};

#endif // MAP_H
