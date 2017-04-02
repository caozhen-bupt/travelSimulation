/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：configdialog.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个ConfigDialog类，用于修改配置信息。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

/*包含头文件*/

#include <QDialog>


namespace Ui {
class ConfigDialog;
}

/*
 * 类名称：ConfigDialog
 * 功能描述：该类用于实现配置信息的修改。
 */

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);//构造函数
    ~ConfigDialog();//析构函数

private:
    Ui::ConfigDialog *ui;//ui界面
};

#endif // CONFIGDIALOG_H
