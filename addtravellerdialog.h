/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：addtravellerdialog.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个AddTravellerDialog;类，用于添加旅客信息，在
 *         mainwindow.cpp中实例化并使用该类，进行加入旅客操作。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.26 戴唯 添加了类的部分参数。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef ADDTRAVELLERDIALOG_H
#define ADDTRAVELLERDIALOG_H

/*包含头文件*/

#include "datastructure.h"
#include "traveller.h"

#include <QDialog>
#include <QDebug>
#include <QDate>
#include <vector>
#include <QMessageBox>

namespace Ui {
class AddTravellerDialog;
}

/*
 * 类名称：AddTravellerDialog
 * 功能描述：该类用于实现选择旅行起始、终点、途经城市和时间以及记录旅客身份信息。
 */

class AddTravellerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTravellerDialog(QWidget *parent = 0);//构造函数
    ~AddTravellerDialog();//析构函数

    QDate timeSelected;//记录出发时间
    QString name;//记录旅客姓名
    QString identNum;//记录旅客身份证号
    unsigned int seqNum;//记录旅客序号
    unsigned int moneyConsum;//记录旅行的金钱消耗
    unsigned int timeConsum;//记录旅行的时间消耗

    bool change;//记录是否是正在更改的旅客
    QString namenext;//记录正在被更改的旅客姓名
    QString identNumnext;//记录正在被更改的旅客身份证号
    unsigned int seqNumnext;//记录正在被更改的旅客号
    QDateTime startTimenext;//记录正在被更改的旅客的出发时间
    int status;//记录正在被更改的旅客的当前状态
    
    Traveller * traveller;//旅客指针

    unsigned int passCityNum;//记录途经城市的顺序

    QDateTime currentTime;//记录当前时间

    Cities startCity, endCity;//记录开始城市和目的城市
    std::list<PassCityInfo> passCityList;//记录途经城市的链表结构

    Ui::AddTravellerDialog *ui;//ui界面

private slots:
    void ResetInfo();//重新置入信息的函数
    void SelectTime();//选择开始时间的函数
    void FillTime();//选择停留城市时间的函数

    void on_Baotou_clicked();//城市按键点击后的槽函数
    void on_Huhehaote_clicked();
    void on_Tongliao_clicked();
    void on_Beijing_clicked();
    void on_Tianjin_clicked();
    void on_Taiyuan_clicked();
    void on_Changzhou_clicked();
    void on_Shanghai_clicked();
    void on_Hangzhou_clicked();
    void on_Ningbo_clicked();
    void on_Lishui_clicked();
    void on_Wenzhou_clicked();
    void on_Chongqing_clicked();
    void on_Xianggelila_clicked();
    void on_Panzhihua_clicked();
    void on_Kunming_clicked();
    void on_Xishuangbanna_clicked();
    void on_Lijiang_clicked();
    void on_Erhai_clicked();
    void on_Dali_clicked();

private:
    void DisplayCityAttr(CityChoose attr,QString nowCityStr,Cities nowCityInt);//打印选择后的城市的函数
    void SetConnect();//信号宇槽函数的连接函数
};

#endif // ADDTRAVELLERDIALOG_H
