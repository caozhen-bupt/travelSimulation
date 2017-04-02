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

#ifndef RESTOREDIALOG_H
#define RESTOREDIALOG_H

/*包含头文件*/

#include <QDialog>

namespace Ui {
class RestoreDialog;
}

/*
 * 类名称：RestoreDialog
 * 功能描述：该类用于实现备份文件的数据恢复，使程序接着上一次备份的数据开始运行。
 */

class RestoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RestoreDialog(QWidget *parent = 0);//构造函数
    ~RestoreDialog();//析构函数

private:
    Ui::RestoreDialog *ui;//ui界面
};

#endif // RESTOREDIALOG_H
