/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：aboutusdialog.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了AboutUsDialog类中，各成员函数的实现，用于打印开发者信息，
 *         在aboutusdialog.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4  戴唯 完成了该文件的注释
 *  2016.5.15 李一鸣 创建了该文件，实现了函数
 */

/*包含头文件*/

#include "aboutusdialog.h"
#include "ui_aboutusdialog.h"

/*
 * 函数名称：AboutUsDialog::AboutUsDialog
 * 参数列表说明：接收父窗口为其参数。
 * 返回值：无
 * 功能说明：该函数为构造函数，用来初始化此类。
 */

AboutUsDialog::AboutUsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutUsDialog)
{
    ui->setupUi(this);//设置窗口属性

}

/*
 * 函数名称：AboutUsDialog::~AboutUsDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

AboutUsDialog::~AboutUsDialog()
{
    delete ui;
}
