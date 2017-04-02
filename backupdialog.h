/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：map.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个BackupDialog类，用于备份文件的生成，在
 *         mainwindow.cpp中实例化并使用该类，生成备份文件。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef BACKUPDIALOG_H
#define BACKUPDIALOG_H

/*包含头文件*/

#include <QDialog>

namespace Ui {
class BackupDialog;
}

/*
 * 类名称：BackupDialog
 * 功能描述：该类用于实现文件备份的功能，并打印备份成功的提示信息。
 */


class BackupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BackupDialog(QWidget *parent = 0);//构造函数
    ~BackupDialog();//析构函数

private:
    Ui::BackupDialog *ui;//ui界面
};

#endif // BACKUPDIALOG_H
