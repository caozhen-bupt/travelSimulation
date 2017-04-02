/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：filltimedialog.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个FillTimeDialog类，用于打印途经城市并获取停留时间的输入并记录，
 *         在addtravellerdialog.cpp中实例化并使用此类。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.24 戴唯 修改了此文件，添加了类的部分参数。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef FILLTIMEDIALOG_H
#define FILLTIMEDIALOG_H

/*包含头文件*/

#include "datastructure.h"
#include "traveller.h"

#include <QDialog>
#include <QDebug>
#include <QTabWidget>
#include <QApplication>
#include <QTableWidgetItem>
#include <vector>
#include <QMessageBox>
#include <iterator>



namespace Ui {
class FillTimeDialog;
}

/*
 * 类名称：FillTimeDialog
 * 功能描述：该类用于实现停留时间的获取。
 */

class FillTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FillTimeDialog(QWidget *parent = 0);//构造函数
    ~FillTimeDialog();//析构函数

    void SetTable();//打印表格函数

    Traveller * traveller;//旅客指针

    unsigned int passCityNum;//途经城市数量
    unsigned int seqNum;//当前旅客的旅客号

    bool change;//记录是否是正在更改的旅客
    QString namenext;//记录正在被更改的旅客姓名
    QString identNumnext;//记录正在被更改的旅客身份证号
    unsigned int seqNumnext;//记录正在被更改的旅客号
    QDateTime startTimenext;//记录正在被更改的旅客的出发时间
    int status;//记录正在被更改的旅客的当前状态

    int currentTime;//当前时间
    int upperBound;//时间上限
    Cities startCity, endCity;//记录初始城市、终止城市
    std::list<PassCityInfo> passCityList;//记录途经城市的链表结构

private slots:
    void ChooseWay();//生成策略打印的函数
    void on_checkBox_clicked();//设置时间上限输入条是否有效的函数

private:
    Ui::FillTimeDialog *ui;//ui界面
    QString CityIntToString(Cities cityInt);//Cities枚举类型的相关转化
    bool infoCompleted();//信息是否填完整的判断函数
};

#endif // FILLTIMEDIALOG_H
