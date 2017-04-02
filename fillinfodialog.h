/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：fillinfodialog.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个FillInfoDialog类，用于旅客信息的输入和记录，在
 *         choosewayDialog.cpp中实例化并使用该类。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.26 曹桢 修改了该文件，添加了类的部分内容。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */


#ifndef FILLINFODIALOG_H
#define FILLINFODIALOG_H

/*包含头文件*/

#include <QDialog>
#include <list>
#include <iterator>
#include <QMessageBox>

#include "datastructure.h"
#include "traveller.h"



namespace Ui {
class FillInfoDialog;
}

/*
 * 类名称：FillInfoDialog
 * 功能描述：该类用于获取输入的旅客信息并进行记录，最后将旅客加入旅客链表并打印日志。
 */

class FillInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FillInfoDialog(QWidget *parent = 0);//构造函数
    ~FillInfoDialog();//析构函数

    QString name;//记录旅客姓名
    QString identNum;//记录旅客身份证号
    unsigned int seqNum;//记录旅客的旅客号
    std::list<TravelCityInfo> pathList;//记录旅客路线的链表结构
    unsigned int moneyConsum;//记录旅客旅行消耗金钱
    unsigned int timeConsum;//记录旅客旅行消耗时间
    Cities startcity, endcity;//记录初始城市和终止城市

    Traveller * traveller;//旅客指针

    void logPrint(QString str);//打印日志的函数


private slots:
    void FillFinished();//信息填完关闭窗口的槽函数

private:
    Ui::FillInfoDialog *ui;//ui界面

};

#endif // FILLINFODIALOG_H
