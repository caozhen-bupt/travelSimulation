/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：calendar.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了Calendar类中，各成员函数的实现，用于
 *         旅客的添加，在calendar.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数
 */

/*包含头文件*/

#include "calendardialog.h"
#include "ui_calendardialog.h"

/*
 * 函数名称：CalendarDialog::CalendarDialoge
 * 参数列表说明：函数接收父窗口为参数。
 * 返回值：无
 * 功能说明：该函数为构造函数，进行初始化操作。
 */

CalendarDialog::CalendarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalendarDialog)
{
    ui->setupUi(this);//设置窗口属性
    this->setFixedSize(500,380);//锁死窗口大小

    isYep=false;//初始化
    isCancel=false;

    ui->calendarWidget->setCurrentPage(2016,1);//设置日历初始页

    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(WinClose()));//连结取消按键点击信号和WinClose函数
    connect(ui->yep,SIGNAL(clicked()),this,SLOT(TimeSelected()));//连结确认按键点击信号和TimeSelected函数
}

/*
 * 函数名称：CalendarDialog::TimeSelected
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来记录所选择的时间，被CalendarDialog调用。
 */

void CalendarDialog::TimeSelected(){
    time = ui->calendarWidget->selectedDate();//记录选择时间
    isYep=true;
    this->close();
}

/*
 * 函数名称：CalendarDialog::WinClose
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来关闭窗口，被CalendarDialog调用。
 */

void CalendarDialog::WinClose(){
    isCancel=true;
    this->close();
}

/*
 * 函数名称：CalendarDialog::~CalendarDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

CalendarDialog::~CalendarDialog()
{
    delete ui;
}
