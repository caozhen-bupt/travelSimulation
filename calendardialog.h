/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：map.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个CalendarDialog类，用于出发时间的选择，在
 *         addtravellerdialog.cpp中实例化并使用该类，生成具体的时间。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

/*包含头文件*/

#include <QDialog>
#include<QDate>

namespace Ui {
class CalendarDialog;
}

/*
 * 类名称：CalendarDialog
 * 功能描述：该类用于实现时间的选择，给出日历选择生成出发时间。
 */


class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = 0);//构造函数
    ~CalendarDialog();//析构函数

    bool isYep;//记录是否确认
    bool isCancel;//记录是否取消
    QDate time;//记录所选择时间

private slots:
    void TimeSelected();//时间选择的槽函数
    void WinClose();//关闭对话框的函数

private:
    Ui::CalendarDialog *ui;//ui界面
};

#endif // CALENDARDIALOG_H
