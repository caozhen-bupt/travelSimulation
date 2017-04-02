/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：fillinfodialog.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了FillInfoDialog类中，各成员函数的实现，用于
 *         获取并记录旅客信息，在fillinfodialog.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4  戴唯 为该文件完善了注释。
 *  2016.5.24 曹桢 修改了该文件，添加了部分函数。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数。
 */

/*包含头文件*/

#include "fillinfodialog.h"
#include "ui_fillinfodialog.h"
#include "showiddialog.h"
#include "ui_showiddialog.h"
#include <QSqlQuery>
#include <QDebug>
#include "mainwindow.h"

/*
 * 函数名称：FillInfoDialog::FillInfoDialog
 * 参数列表说明：该函数接收其父窗口为参数
 * 返回值：无
 * 功能说明：该函数为构造函数，进行初始化。
 */

FillInfoDialog::FillInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FillInfoDialog)
{
    ui->setupUi(this);
    this->traveller=NULL;//初始化操作

    connect(ui->yep,SIGNAL(clicked()),this,SLOT(FillFinished()));//连接确认点击信号和FillFinished函数
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(close()));//连接取消点击信号和close函数
}

/*
 * 函数名称：FillInfoDialog::FillFinished
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来记录旅客信息并生成旅客链表的新结点，被FillInfoDialog调用。
 */

void FillInfoDialog::FillFinished(){
    if(ui->lineEdit->text()!="" && ui->lineEdit_2->text()!=""){//输入信息不为空时
        traveller = new Traveller;//创建新的旅客指针
        traveller->name=ui->lineEdit->text();//获取旅客姓名
        traveller->identNum=ui->lineEdit_2->text();//获取旅客身份证号
        traveller->seqNum=this->seqNum;//给旅客号赋值
        traveller->nowStatus=waiting;//初始状态为等待中
        traveller->pathList=this->pathList;//将选择的路径赋给新结点的路径
        traveller->moneyConsum=this->moneyConsum;//将选择的路径的金钱消耗赋给新结点的路径的金钱消耗
        traveller->timeConsum=this->timeConsum;//将选择的路径的时间消耗赋给新结点的路径的时间消耗

        ShowIDDialog * showidDialog = new ShowIDDialog(this);//创建新的ShowIDDialog类并打印旅客号
        showidDialog->seqNum=this->seqNum;
        showidDialog->ShowID();
        showidDialog->exec();

        name = ui->lineEdit->text();
        identNum = ui->lineEdit_2->text();

        QSqlQuery query;
        QString str;
        TravelCityInfo temp=traveller->pathList.front();

        QString sql = "INSERT INTO travellerInfo(seqNum, name, identNum, nowStatus, startCity, endCity)"" VALUES(";//将旅客加入旅行时间写入数据库

        sql=sql+str.setNum(seqNum)+",'"+name+"','"+identNum+"',"+"'waiting'"+","+QString::number(temp.begin)+","+QString::number(temp.end)+")";
        bool test=query.exec(QString(sql));



        this->close();
        logPrint(name+"("+QString::number(seqNum)+") 加入旅行。");



    }

    else{
        ui->lineEdit->setText("");//输入信息为空时提示错误
        ui->lineEdit_2->setText("");
        QMessageBox::warning(NULL, "提示","请正确输入姓名和身份证号", QMessageBox::Yes | QMessageBox::Yes);
    }
}

/*
 * 函数名称：FillInfoDialog::logPrint
 * 参数列表说明：该函数接收一个参数：str为日志内容
 * 返回值：无
 * 功能说明：该函数用来向数据库写入日志，被FillFinished调用。
 */

void FillInfoDialog::logPrint(QString str){
    QSqlQuery query;
    QDateTime temp=QDateTime::fromString("2016/01/01 00:00:00",TimeFormat);//获取当前时间
    temp=temp.addSecs(qint64(now));
    bool test = true;
    test = query.prepare("INSERT INTO log(seqNum, time, strEvent) VALUES(:seqNum, :time, :strEvent)");//将日志内容加入数据库
    if (test){
        query.bindValue(":time", temp.toString(TimeFormat));
        query.bindValue(":strEvent", str);
        test = query.exec();
    }
}


/*
 * 函数名称：FillInfoDialog::~FillInfoDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

FillInfoDialog::~FillInfoDialog()
{
    delete ui;
}

