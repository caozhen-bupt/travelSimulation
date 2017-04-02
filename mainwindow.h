/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：mainwindow.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了一个MainWindow类，用于打印主要界面和所有的功能键，在
 *         main.cpp中实例化并使用该类，打印程序的各种功能入口。
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.25 曹桢 修改了该文件，添加了类的部分内容。
 *  2016.5.24 戴唯 修改了该文件，添加了类的部分内容。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*包含头文件*/

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QtGui>
#include <QAction>
#include <QDateTime>
#include <QMessageBox>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
#include <QDebug>
#include <vector>
#include <list>

#include "addtravellerdialog.h"
#include "ui_addtravellerdialog.h"
#include "aboutusdialog.h"
#include "ui_aboutusdialog.h"
#include "backupdialog.h"
#include "ui_backupdialog.h"
#include "restoredialog.h"
#include "ui_restoredialog.h"

#include "datastructure.h"
#include "map.h"
#include "traveller.h"


extern QApplication * temp;//当前用户图形界面
extern int now;//当前系统时间

namespace Ui {
class MainWindow;
}

/*
 * 类名称：MainWindow
 * 功能描述：该类用于打印主要界面和所有的功能键。
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);//构造函数
    ~MainWindow();//析构函数

    void CreateConnection(bool isExist);//创建数据库连接
    void InitSQL();//初始化数据库

    QDateTime currentTime;//当前时间

    int eachCity[20];//记录城市旅客滞留信息的数组

    std::list<Traveller> travellerList;//系统中的旅客链表

    QString namenext;//记录正在被更改的旅客姓名
    QString identNumnext;//记录正在被更改的旅客身份证号
    unsigned int seqNumnext;//记录正在被更改的旅客号
    QDateTime startTimenext;//记录正在被更改的旅客的出发时间
    int status;//记录正在被更改的旅客的当前状态
    int startnext;//记录下一个起始城市

    QSqlTableModel * modelAlter;//更改信息表
    QSqlTableModel * modelSearch;//旅客信息表
    QSqlTableModel * modelLog;//日志表
    QSqlDatabase db; //数据库

private slots:
    void ProcessTime();//推移processBar
    void TimerManager();

    void AddTraveller();//添加新的旅客
    void ReTravaller();//更改旅客行程

    void ClearInQ();//清除lineEditor_InQ的内容
    void ClearInRe();//清除lineEditor_InRe的内容
    void ClearInLog();//清除lineEditor_InLog的内容

    void Search();//查询旅客信息
    void SearchAlter();//查询并更改旅客信息
    void SearchLog();//查询日志信息

    void Initial();//初始化函数

    void File_Backup();//保存当前的模拟进度
    void File_Restore();//恢复上一次的模拟进度
    void About_AboutUs();//显示制作者的信息


    //Cities枚举类型的相关转化
    QString TntToString(int);
    Cities IntIntoCity(int);
    int CityToInt(Cities);
    QString CityToNumString(Cities);
    Cities StringToCity(QString);

    //统计显示的按键
    void on_Baotou_clicked();
    void on_Huhehaote_clicked();
    void on_Tongliao_clicked();
    void on_Beijing_clicked();
    void on_Tianjin_clicked();
    void on_Taiyuan_clicked();
    void on_Changzhou_clicked();
    void on_Shanghai_clicked();
    void on_Hangzhou_clicked();
    void on_Ningbo_clicked();
    void on_Wenzhou_clicked();
    void on_Lishui_clicked();
    void on_Chongqing_clicked();
    void on_Kunming_clicked();
    void on_Panzhihua_clicked();
    void on_Xianggelila_clicked();
    void on_Lijiang_clicked();
    void on_Erhai_clicked();
    void on_Dali_clicked();
    void on_Xishuangbanna_clicked();

private:
    Ui::MainWindow *ui;//ui界面
    QTimer * timer;//计时器

    //QFileInfo dbFileInfo;
    bool isExist;//记录数据库文件是否存在

    //初始化函数
    void SetWindowAttri();
    void SetSQLModel();
    void SetTimer();
    void SetSlots();

    void SetTimeTable();
    void logPrint(QString);//日志打印函数

    //当前状态的函数
    void CurrentState();
    void CalculateStatus();//计算所有在旅行旅客的状态
    void DisplayStatistics();//子函数，显示统计信息
    void DisplayTravellerStatus();//子函数，显示每个旅客的状态

    QString IntIntoString(int);//整型到字符串型的转化函数
};

#endif // MAINWINDOW_H
