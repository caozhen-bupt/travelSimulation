/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：map.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个ChooseCityDialog类，用于选择旅行中的城市，在
 *         addtravellerdialog.cpp中实例化并使用该类，进行城市选择。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.24 戴唯 修改了该文件，添加了部分参数。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef CHOOSECITYDIALOG_H
#define CHOOSECITYDIALOG_H

/*包含头文件*/

#include "datastructure.h"

#include <QDialog>
#include <QButtonGroup>
#include <QDebug>
#include <QDate>

namespace Ui {
class ChooseCityDialog;
}

/*
 * 类名称：ChooseCityDialog
 * 功能描述：该类用于实现城市类别的选择，确定是起始城市、终止城市或途经城市。
 */


class ChooseCityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseCityDialog(QWidget *parent = 0);//构造函数
    ~ChooseCityDialog();//析构函数

    CityChoose attrSelected;//记录选择的类别

    QButtonGroup * btnGroupCity;//选择按键

    bool change;//记录是否是正在被更改的旅客
    QString namenext;//记录正在被更改的旅客姓名
    QString identNumnext;//记录正在被更改的旅客身份证号
    unsigned int seqNumnext;//记录正在被更改的旅客的旅客号
    QDate startTimenext;//记录正在被更改的旅客的下一个出发时间
    int status;//记录正在被更改的旅客的当前状态
    bool isOK;//记录是否确认

private slots:
    void ButtonSelected();//按键选择槽函数

    void on_yep_clicked();//确认槽函数
    void on_cancel_clicked();//取消槽函数

private:
    Ui::ChooseCityDialog *ui;//ui界面
};

#endif // CHOOSECITYDIALOG_H
