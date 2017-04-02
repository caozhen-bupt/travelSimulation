/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：restoredialog.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个RestorDialog类，用于备份文件的恢复和打印恢复成功的提示信息，在
 *         mainwindow.cpp中实例化并使用该类。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef SHOWIDDIALOG_H
#define SHOWIDDIALOG_H

/*包含头文件*/

#include <QDialog>

namespace Ui {
class ShowIDDialog;
}

/*
 * 类名称：ShowIDDialog
 * 功能描述：该类用于打印当前加入旅行的旅客的旅客号。
 */

class ShowIDDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowIDDialog(QWidget *parent = 0);//构造函数
    ~ShowIDDialog();//析构函数
    void ShowID();//打印旅客号的函数
    unsigned int seqNum;//记录当前旅客的旅客号

private slots:
    void yep();//确认关闭的槽函数

private:
    Ui::ShowIDDialog *ui;//ui界面

};

#endif // SHOWIDDIALOG_H
