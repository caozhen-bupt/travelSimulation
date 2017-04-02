/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：showiddialog.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了ShowIDDialog类中，各成员函数的实现，用于
 *         程序数据的备份，在ShowIDDialog.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数。
 */

/*包含头文件*/

#include "showiddialog.h"
#include "ui_showiddialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * 函数名称：ShowIDDialog::ShowIDDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为默认构造函数，进行初始化。
 */

ShowIDDialog::ShowIDDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowIDDialog)
{
    ui->setupUi(this);//设置窗口格式
    connect(ui->yep,SIGNAL(clicked()),this,SLOT(yep()));//连接确认点击信号和yep函数
}

/*
 * 函数名称：ShowIDDialog::ShowID
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为打印当前旅客的旅客号的函数。
 */

void ShowIDDialog::ShowID(){
    ui->IDnumber->setText(QString::number(seqNum,10));//打印旅客号
}

/*
 * 函数名称：ShowIDDialog::yep
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为确认按键点击信号的槽函数，触发关闭窗口。
 */

void ShowIDDialog::yep(){
    this->close();
}

/*
 * 函数名称：ShowIDDialog::~ShowIDDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为默认析构函数。
 */


ShowIDDialog::~ShowIDDialog()
{
    delete ui;
}
