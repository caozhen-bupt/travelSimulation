/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：choosewaydialog.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个ChooseWayDialog类，用于确定所选择城市的类别，在
 *         filltimedialog.cpp中实例化并使用该类。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.25 曹桢 修改了该文件，添加了部分函数声明。
 *  2016.5.24 戴唯  修改了该文件，添加了部分参数。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef CHOOSEWAYDIALOG_H
#define CHOOSEWAYDIALOG_H

/*包含头文件*/

#include <QDialog>
#include <vector>
#include <list>
#include <iterator>
#include <queue>
#include <algorithm>
#include <QMessageBox>

#include "map.h"
#include "traveller.h"

extern int now;//记录当前系统时间
namespace Ui {
class ChooseWayDialog;
}

/*
 * 类名称：ChooseWayDialog
 * 功能描述：该类用于实现三种策略的打印和选择。
 */


class ChooseWayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseWayDialog(QWidget *parent = 0);//构造函数
    ~ChooseWayDialog();//析构函数

    int currentTime;//记录当前时间
    int str1_timeSum;//记录策略一的时间消耗
    int str2_timeSum;//记录策略二的时间消耗
    int str3_timeSum;//记录策略三的时间消耗
    int str1_moneyConsum;//记录策略一的金钱消耗
    int str2_moneyConsum;//记录策略二的金钱消耗
    int str3_moneyConsum;//记录策略三的金钱消耗
    int str1_endTime;//记录策略一的结束时间
    int str2_endTime;//记录策略二的结束时间
    int upperBound;//记录时间上限
    Cities startCity, endCity;//记录始发城市和终止城市
    std::list<PassCityInfo> passCityList;//记录途经城市的链表结构
    std::list<TravelCityInfo> listPath_str1;//记录策略一的路线信息链表
    std::list<TravelCityInfo> listPath_str2;//记录策略一的路线信息链表
    std::list<TravelCityInfo> listPath_str3;//记录策略一的路线信息链表

    Traveller * traveller;//所有旅客信息链表结构

    bool change;//记录是否是正在更改的旅客
    QString namenext;//记录正在被更改的旅客姓名
    QString identNumnext;//记录正在被更改的旅客身份证号
    unsigned int seqNumnext;//记录正在被更改的旅客号
    QDateTime startTimenext;//记录正在被更改的旅客的出发时间
    int status;//记录正在被更改的旅客的当前状态

    //Cities枚举类型的相关转化
    QString CityToNumString(Cities);
    QString CityIntToString(Cities);

    void GetLeastMoney();//获取最少金钱策略路线的函数
    void GetLeastTime();//获取最少时间策略路线的函数
    void GetLimitTime();//获取限时最少金钱策略路线的函数


    void logPrint(QString);//打印日志函数
    void SetTable();//打印路线表格函数
    //三种策略路线的打印函数
    void ShowLeastMoney(int,QString,QString,QString,int,int,int);
    void ShowLeastTime(int,QString,QString,QString,int,int,int);
    void ShowLimitTime(int,QString,QString,QString,int,int,int);

    unsigned int seqNum;//记录当前旅客的旅客号

private slots:
    void FillInfo();//停留时间选择的槽函数

private:
    Ui::ChooseWayDialog *ui;//ui界面

};

#endif // CHOOSEWAYDIALOG_H
