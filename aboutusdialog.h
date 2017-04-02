/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：aboutusdialog.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个AboutUsDialog类，用于打印开发者信息。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的内容。
 */

#ifndef ABOUTUSDIALOG_H
#define ABOUTUSDIALOG_H

/*包含头文件*/

#include <QDialog>

namespace Ui {
class AboutUsDialog;
}

/*
 * 类名称：AboutUsDialog
 * 功能描述：该类用于打印软件开发者的信息。
 */

class AboutUsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutUsDialog(QWidget *parent = 0);//构造函数
    ~AboutUsDialog();//析构函数

private:
    Ui::AboutUsDialog *ui;//ui界面
};

#endif // ABOUTUSDIALOG_H
