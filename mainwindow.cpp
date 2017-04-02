/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：mainwindow.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了MainWindow类中，各成员函数的实现，用于
 *         寻路模块的计算，在mainwindow.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4  戴唯 为该文件完善了注释。
 *  2016.5.28 李一鸣 修改了该文件，添加了一些函数。
 *  2016.5.25 曹桢 修改了该文件，添加了一些函数。
 *  2016.5.24 戴唯 修改了该文件，添加了一些成员函数。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数。
 */

/*包含头文件*/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include <QWhatsThis>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

/*
 * 函数名称：MainWindow::MainWindow
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为构造函数，进行初始化操作。
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//设置窗口属性

    SetWindowAttri();//初始化数据库及表格

    SetSQLModel();//时间函数初始化

    SetTimer();//connect相关槽和函数

    SetSlots();

    //QAction *action = QWhatsThis::createAction(this);
    //ui->mainToolBar->addAction(action);

    seqNumnext=0;
    namenext="";
    identNumnext="";
    startnext=20;
}

/*
 * 函数名称：MainWindow::SetWindowAttri
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为设置mainwindow大小及标题的函数，被MainWindow调用。
 */

void MainWindow::SetWindowAttri(){
    this->setGeometry(100,100,1200,742);
    this->setFixedSize(1200,742);//锁死窗口大小

    this->setWindowTitle(tr("Travel_Simulation_System"));//修改程序标题
}

/*
 * 函数名称：MainWindow::SetSQLModel
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数连接数据库的函数，被MainWindow调用。
 */


void MainWindow::SetSQLModel(){
    QFileInfo dbFileInfo(DBFileName);
    isExist = dbFileInfo.exists();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBFileName);
    MainWindow::CreateConnection(isExist);

    ui->tableWidget_query->setColumnCount(6);//设置查询和更改表格样式和表头
    ui->tableWidget_query->setHorizontalHeaderLabels
            (QStringList()<<"旅客号"<<"名字"<<"身份证号"<<"目前状态"<<"出发城市"<<"目的城市");
    ui->tableWidget_alter->setColumnCount(6);
    ui->tableWidget_alter->setHorizontalHeaderLabels
            (QStringList()<<"旅客号"<<"名字"<<"身份证号"<<"目前状态"<<"出发城市"<<"目的城市");

    modelLog = new QSqlTableModel;//设置日志查询表格模式
    modelLog->setTable("log");
    modelLog->setHeaderData(time_dbLog, Qt::Horizontal, "时间");
    modelLog->setHeaderData(strEvent, Qt::Horizontal, "日志记录");
    modelLog->select();
    ui->tableView_log->setModel(modelLog);
    ui->tableView_log->setColumnHidden(seqNum_dbLog, true);
    ui->tableView_log->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_log->setColumnWidth(1,170);
    QHeaderView *header2 = ui->tableView_log->horizontalHeader();
    header2->setStretchLastSection(true);
    ui->tableView_log->show();
}

/*
 * 函数名称：MainWindow::SetTimer
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为设置计时器的函数，被MainWindow调用。
 */

void MainWindow::SetTimer(){
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(ProcessTime()));
    connect(ui->TimerControl,SIGNAL(clicked()),this,SLOT(TimerManager()));
    timer->setSingleShot(false);
    timer->start(TrigFrequency);
}

/*
 * 函数名称：MainWindow::SetSlots
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为将信号与槽函数连接起来的函数，被MainWindow调用。
 */


void MainWindow::SetSlots(){
    //菜单栏
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));//连接下拉菜单的选项与各自的函数
    connect(ui->actionBackup,SIGNAL(triggered()),this,SLOT(File_Backup()));
    connect(ui->actionRestore,SIGNAL(triggered()),this,SLOT(File_Restore()));
    connect(ui->actionAboutUs,SIGNAL(triggered()),this,SLOT(About_AboutUs()));

    connect(ui->AddTraveler,SIGNAL(clicked()),this,SLOT(AddTraveller()));//连接加入旅客选项与AddTraveller函数
    connect(ui->Quit,SIGNAL(clicked()),temp,SLOT(quit()));//连接退出选项与quit函数

    //以下三组分别连接各自的清空选项与清空函数、查询选项与查询函数
    connect(ui->clearInQ,SIGNAL(clicked()),this,SLOT(ClearInQ()));
    connect(ui->lineEditInQ,SIGNAL(textChanged(QString)),this,SLOT(Search()));

    connect(ui->clearInRe,SIGNAL(clicked()),this,SLOT(ClearInRe()));
    connect(ui->yepInRe,SIGNAL(clicked()),this,SLOT(ReTravaller()));//连接确定更改选项与ReTravaller函数
    connect(ui->lineEditInRe,SIGNAL(textChanged(QString)),this,SLOT(SearchAlter()));

    connect(ui->clearInQ_2,SIGNAL(clicked()),this,SLOT(ClearInLog()));
    connect(ui->lineEditInQ_2,SIGNAL(textChanged(QString)),this,SLOT(SearchLog()));

}

/*
 * 函数名称：MainWindow::ProcessTime
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为推进系统时间并打印当前时间的函数，被SetTimer调用。
 */

void MainWindow::ProcessTime(){
    CurrentState();
    //时间函数，通过进度条的推进来推动时间前进
    //首先设置一个timer定时器来使进度条不断前进，当进度条满时时间+60分钟，以此达到每个时间间隔时间递增20分钟
    ui->progressBar->setValue(ui->progressBar->value()+1);
    if(ui->progressBar->value()>=100){
        now+=3600;
        ui->progressBar->reset();
    }
    currentTime=QDateTime::fromString("2016/01/01 00:00:00",TimeFormat);//获取当前时间
    currentTime=currentTime.addSecs(qint64(now));
    ui->labelDate->setText("时间："+currentTime.toString("yyyy/MM/dd"));//打印日期
    ui->labelTime->setText(currentTime.toString("hh:mm:ss"));//打印时间
}

/*
 * 函数名称：MainWindow::TimerManager
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为管理计时器的函数,被SetTimer调用。
 */

void MainWindow::TimerManager(){
    if(timer->isActive()){
        timer->stop();
        ui->TimerControl->setText("开启计时器");
    }
    else{
        timer->start();
        ui->TimerControl->setText("停止计时器");
    }
}

/*
 * 函数名称：MainWindow::AddTraveller
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为加入旅客操作的函数，被SetSlots调用。
 */


void MainWindow::AddTraveller(){

    timer->stop(); //计时器停止

    int num=0;//临时变量

    QSqlQuery query;

    query.exec("SELECT * FROM travellerInfo");//统计当前数据库中的旅客数量
    while(query.next()){
        num++;
    }

    AddTravellerDialog * addtravellerDialog = new AddTravellerDialog(this);
    addtravellerDialog->change=false;
    addtravellerDialog->seqNum=num+1;//获取当前旅客号
    addtravellerDialog->currentTime=currentTime;//获取时间
    addtravellerDialog->exec();
    Traveller * traveller=NULL;
    traveller=addtravellerDialog->traveller;
    if(traveller){
        TravelCityInfo temp=traveller->pathList.front();
        if(currentTime.toString("h").toInt()<temp.begin)//判断当前时间是否小于旅行开始时间
            traveller->waitNextDay=false;
        else
            traveller->waitNextDay=true;
        travellerList.push_back(*traveller);//加入旅客至链表
        delete traveller;
    }
    delete addtravellerDialog;

    timer->start();
    ui->TimerControl->setText("停止计时器");
}

/*
 * 函数名称：MainWindow::ReTravaller
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为更改旅客行程的函数，被SetSlots调用。
 */

void MainWindow::ReTravaller(){

    timer->stop();//计数器停止
    std::list<Traveller>::iterator itor;
    TravelCityInfo temp;
    AddTravellerDialog * retravellerDialog = new AddTravellerDialog(this);//创建新的AddTravellerDialog类对象
    retravellerDialog->status=this->status;//将当前旅客状态赋值给这个对象
    retravellerDialog->change=true;//更改操作标志改为真
    retravellerDialog->ui->startDisplay->setText(IntIntoString(this->startnext));//锁死起点
    retravellerDialog->startCity=IntIntoCity(this->startnext);
    retravellerDialog->namenext=this->namenext;//传递旅客信息
    retravellerDialog->identNum=this->identNumnext;
    retravellerDialog->seqNumnext=this->seqNumnext;

    if(retravellerDialog->status==1){//若状态为旅行中则获取此段旅行的结束时间为更改后的开始时间
        qDebug()<<"seqNum"<<this->seqNumnext;
        for(itor=travellerList.begin(); itor!=travellerList.end(); itor++){

            if(itor->seqNum==this->seqNumnext){
                temp=itor->pathList.front();
                retravellerDialog->startCity=temp.end;
                QString tempstr=currentTime.toString("yyyy/MM/dd")+" "+QString::number(temp.endTime)+":00:00";
                retravellerDialog->startTimenext=QDateTime::fromString(tempstr, TimeFormat);
                qDebug()<<"before erase";
                break;
            }
        }
    }

    for(itor=travellerList.begin(); itor!=travellerList.end(); itor++){

        if(itor->seqNum==this->seqNumnext){
            travellerList.erase(itor);//删除这个旅客结点
            itor--;
            break;
        }
    }







    retravellerDialog->exec();

    Traveller * traveller=NULL;
    traveller=retravellerDialog->traveller;
    travellerList.push_back(*traveller);
    delete traveller;
    delete retravellerDialog;

    timer->start();//开启计时器
    ui->TimerControl->setText("停止计时器");
}

/*
 * 函数名称：MainWindow::ClearInQ
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为清空查询输入的函数，被SetSlots调用。
 */

void MainWindow::ClearInQ(){
    ui->lineEditInQ->setText("");
    //其他操作
}

/*
 * 函数名称：MainWindow::ClearInRe
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为清空更改查询输入的函数，被SetSlots调用。
 */

void MainWindow::ClearInRe(){
    ui->lineEditInRe->setText("");
    //其他操作
}

/*
 * 函数名称：MainWindow::ClearInLog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为清空日志查询输入的函数，被SetSlots调用。
 */

void MainWindow::ClearInLog(){
    ui->lineEditInQ_2->setText("");
    //其他操作
}

/*
 * 函数名称：MainWindow::Search
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为查询旅客信息并打印的函数，被SetSlots调用。
 */

void MainWindow::Search(){
    QSqlQuery query;
    QString nows="";
    QString na;
    QString id;
    int num=0;
    int s=0;
    int t=0;
    QString searchtype = ui->comboBox->currentText();//获取查询类型
    QString searchinfo = ui->lineEditInQ->text();//获取查询信息

    if(searchtype=="身份证号"){//按身份证号查找
        if(searchinfo==""){//输入为空则打印所有旅客信息
            query.exec("SELECT * FROM travellerInfo");
            num=0;
        }
        else{
            query.exec("SELECT * FROM travellerInfo WHERE identNum="+searchinfo);
            num=0;
        }
        while(query.next()){//逐条打印查找出的旅客信息
            if(query.value("nowStatus").toInt()==0)nows="等待中";//将状态转化为字符串打印
            else if(query.value("nowStatus").toInt()==1)nows="旅行中";
            else if(query.value("nowStatus").toInt()==2)nows="停留中";
            else nows="结束旅行";
            ui->tableWidget_query->setRowCount(num+1);
            QTableWidgetItem * item;
            for(int i=0; i<6; i++){
                item=ui->tableWidget_query->item(num, i);
                if(!item){
                item=new QTableWidgetItem;
                ui->tableWidget_query->setItem(num, i, item);
            }
            item->setFlags(item->flags()&(~Qt::ItemIsEditable));
            s=query.value("startCity").toInt();
            t=query.value("endCity").toInt();
            na=query.value("name").toString();
            id=query.value("identNum").toString();
            if(i==0) item->setText(query.value("seqNum").toString());
            else if(i==1) item->setText(query.value("name").toString());
            else if(i==2) item->setText(query.value("identNum").toString());
            else if(i==3) item->setText(nows);
            else if(i==4) item->setText(IntIntoString(query.value("startCity").toInt()));
            else if(i==5) item->setText(IntIntoString(query.value("endCity").toInt()));
            else{
                qDebug()<<"MainWindow::Search()出错";}
            }
            num++;
        }
    }
    else if(searchtype=="姓名"){//按姓名查找
        if(searchinfo==""){//输入为空则打印所有旅客信息
            query.exec("SELECT * FROM travellerInfo");
            num=0;
        }
        else{
            query.exec("SELECT * FROM travellerInfo WHERE name='"+searchinfo+"'");
            num=0;
        }
        while(query.next()){//逐条打印查找出的旅客信息
            if(query.value("nowStatus").toInt()==0)nows="等待中";//将状态转化为字符串打印
            else if(query.value("nowStatus").toInt()==1)nows="旅行中";
            else if(query.value("nowStatus").toInt()==2)nows="停留中";
            else nows="结束旅行";
            ui->tableWidget_query->setRowCount(num+1);
            QTableWidgetItem * item;
            for(int i=0; i<6; i++){
                item=ui->tableWidget_query->item(num, i);
                if(!item){
                    item=new QTableWidgetItem;
                    ui->tableWidget_query->setItem(num, i, item);
                }
                item->setFlags(item->flags()&(~Qt::ItemIsEditable));
                if(i==0) item->setText(query.value("seqNum").toString());
                else if(i==1) item->setText(query.value("name").toString());
                else if(i==2) item->setText(query.value("identNum").toString());
                else if(i==3) item->setText(nows);
                else if(i==4) item->setText(IntIntoString(query.value("startCity").toInt()));
                else if(i==5) item->setText(IntIntoString(query.value("endCity").toInt()));
                else{qDebug()<<"MainWindow::Search()出错";}
            }
            num++;
        }
    }
    else if(searchtype=="旅客号"){//按旅客号查找
        if(searchinfo==""){//输入为空则打印所有旅客信息
            query.exec("SELECT * FROM travellerInfo");
            num=0;
        }
        else{
            query.exec("SELECT * FROM travellerInfo WHERE seqNum="+searchinfo);
            num=0;
        }
        while(query.next()){//逐条打印查找出的旅客信息
            if(query.value("nowStatus").toInt()==0)nows="等待中";//将状态转化为字符串打印
            else if(query.value("nowStatus").toInt()==1)nows="旅行中";
            else if(query.value("nowStatus").toInt()==2)nows="停留中";
            else nows="结束旅行";
            ui->tableWidget_query->setRowCount(num+1);
            QTableWidgetItem * item;
            for(int i=0; i<6; i++){
                item=ui->tableWidget_query->item(num, i);
                if(!item){
                    item=new QTableWidgetItem;
                    ui->tableWidget_query->setItem(num, i, item);
                }
                item->setFlags(item->flags()&(~Qt::ItemIsEditable));
                if(i==0) item->setText(query.value("seqNum").toString());
                else if(i==1) item->setText(query.value("name").toString());
                else if(i==2) item->setText(query.value("identNum").toString());
                else if(i==3) item->setText(nows);
                else if(i==4) item->setText(IntIntoString(query.value("startCity").toInt()));
                else if(i==5) item->setText(IntIntoString(query.value("endCity").toInt()));
                else{qDebug()<<"MainWindow::Search()出错";}
            }
            num++;
        }
    }
}

/*
 * 函数名称：MainWindow::SearchAlter
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为查询并进行更改行程的函数，被SetSlots调用。
 */

void MainWindow::SearchAlter(){

    //然后将搜索得到的结果显示在表格中
    QSqlQuery query;
    QString nows;
    int num=0;

    QString searchtype = ui->comboBox_2->currentText();//首先获得查询的类别
    QString searchinfo = ui->lineEditInRe->text();//获得输入的信息

    if(searchinfo==""){//输入为空则不打印任何信息
        ui->tableWidget_alter->setRowCount(0);
    }
    else{
        if(searchtype=="身份证号"){//查询的类别为身份证号
            num=0;
            query.exec("SELECT * FROM travellerInfo WHERE identNum="+searchinfo);//筛选

            while(query.next()){//逐条打印信息并根据旅客当前状态获取下一个出发城市
                if(query.value("nowStatus").toInt()!=3){//已经结束旅行的旅客不允许进行查找和更改
                    if(query.value("nowStatus").toInt()==0){//等待中则下一个出发城市为当前所在城市
                        nows="等待中";
                        startnext=query.value("startCity").toInt();

                    }
                    else if(query.value("nowStatus").toInt()==1){//旅行中则下一个出发城市为此段旅行终点城市
                        nows="旅行中";
                        startnext=query.value("endCity").toInt();

                    }
                    else if(query.value("nowStatus").toInt()==2){//停留中则下一个出发城市为当前所在城市
                        nows="停留中";
                        startnext=query.value("startCity").toInt();

                    }
                    namenext=query.value("name").toString();//获取旅客身份信息

                    identNumnext=query.value("identNum").toString();
                    seqNumnext=query.value("seqNum").toInt();
                    ui->tableWidget_alter->setRowCount(num+1);
                    QTableWidgetItem * item;//打印查找到的旅客信息
                    for(int i=0; i<6; i++){
                        item=ui->tableWidget_alter->item(num, i);
                        if(!item){
                            item=new QTableWidgetItem;
                            ui->tableWidget_alter->setItem(num, i, item);
                        }
                        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
                        if(i==0) item->setText(query.value("seqNum").toString());
                        else if(i==1) item->setText(query.value("name").toString());
                        else if(i==2) item->setText(query.value("identNum").toString());
                        else if(i==3) item->setText(nows);
                        else if(i==4) item->setText(IntIntoString(query.value("startCity").toInt()));
                        else if(i==5) item->setText(IntIntoString(query.value("endCity").toInt()));
                        else{qDebug()<<"MainWindow::Search()出错";}
                    }
                    num++;
                }
            }
        }
        else if(searchtype=="姓名"){//按姓名查找
            query.exec("SELECT * FROM travellerInfo WHERE name ='"+searchinfo+"'");
            num=0;
            while(query.next()){
                if(query.value("nowStatus").toInt()!=3){
                    if(query.value("nowStatus").toInt()==0){//等待中则下一个出发城市为当前所在城市
                        nows="等待中";
                        startnext=query.value("startCity").toInt();
                    }
                    else if(query.value("nowStatus").toInt()==1){//旅行中则下一个出发城市为此段旅行终点城市
                        nows="旅行中";
                        startnext=query.value("endCity").toInt();
                    }
                    else if(query.value("nowStatus").toInt()==2){//停留中则下一个出发城市为当前所在城市
                        nows="停留中";
                        startnext=query.value("startCity").toInt();
                    }
                    namenext=query.value("name").toString();//获取旅客身份信息
                    identNumnext=query.value("identNum").toString();
                    seqNumnext=query.value("seqNum").toInt();
                    ui->tableWidget_alter->setRowCount(num+1);
                    QTableWidgetItem * item;
                    for(int i=0; i<6; i++){//打印查找到的旅客信息
                        item=ui->tableWidget_alter->item(num, i);
                        if(!item){
                            item=new QTableWidgetItem;
                            ui->tableWidget_alter->setItem(num, i, item);
                        }
                        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
                        if(i==0) item->setText(query.value("seqNum").toString());
                        else if(i==1) item->setText(query.value("name").toString());
                        else if(i==2) item->setText(query.value("identNum").toString());
                        else if(i==3) item->setText(nows);
                        else if(i==4) item->setText(IntIntoString(query.value("startCity").toInt()));
                        else if(i==5) item->setText(IntIntoString(query.value("endCity").toInt()));
                        else{qDebug()<<"MainWindow::Search()出错";}
                    }
                    num++;
                }
            }
        }
        else if(searchtype=="旅客号"){//按旅客号查找
            query.exec("SELECT * FROM travellerInfo WHERE seqNum="+searchinfo);
            num=0;
            while(query.next()){
                if(query.value("nowStatus").toInt()!=3){
                    if(query.value("nowStatus").toInt()==0){//等待中则下一个出发城市为当前所在城市
                        nows="等待中";
                        startnext=query.value("startCity").toInt();
                    }
                    else if(query.value("nowStatus").toInt()==1){//旅行中则下一个出发城市为此段旅行终点城市
                        nows="旅行中";
                        startnext=query.value("endCity").toInt();
                    }
                    else if(query.value("nowStatus").toInt()==2){//停留中则下一个出发城市为当前所在城市
                        nows="停留中";
                        startnext=query.value("startCity").toInt();
                    }
                    namenext=query.value("name").toString();//获取旅客身份信息
                    identNumnext=query.value("identNum").toString();
                    seqNumnext=query.value("seqNum").toInt();
                    ui->tableWidget_alter->setRowCount(num+1);
                    QTableWidgetItem * item;
                    for(int i=0; i<6; i++){//打印查找到的旅客信息
                        item=ui->tableWidget_alter->item(num, i);
                        if(!item){
                            item=new QTableWidgetItem;
                            ui->tableWidget_alter->setItem(num, i, item);
                        }
                        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
                        if(i==0) item->setText(query.value("seqNum").toString());
                        else if(i==1) item->setText(query.value("name").toString());
                        else if(i==2) item->setText(query.value("identNum").toString());
                        else if(i==3) item->setText(nows);
                        else if(i==4) item->setText(IntIntoString(query.value("startCity").toInt()));
                        else if(i==5) item->setText(IntIntoString(query.value("endCity").toInt()));
                        else{qDebug()<<"MainWindow::Search()出错";}
                    }
                    num++;
                }
            }
        }
    }
}

/*
 * 函数名称：MainWindow::SearchLog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为查询日志函数，被SetSlots调用。
 */

void MainWindow::SearchLog(){

    QString searchtype = ui->comboBox_3->currentText();//获取查询类型
    QString searchinfo = ui->lineEditInQ_2->text();//获取查询信息
    if(searchinfo==""){//输入为空则打印全部日志信息
        modelLog->setFilter("");
    }
    else{
        if(searchtype == "时间"){//查询类型为时间
            //modelLog->setFilter("time = '"+searchinfo+"'");
            modelLog->setFilter("time like '%"+searchinfo+"%'");
        }
        else if(searchtype == "内容"){//查询类型为内容
            modelLog->setFilter("string like '%"+searchinfo+"%'");
        }
    }
    modelLog->select();
    ui->tableView_log->setModel(modelLog);//打印日志信息
    ui->tableView_log->show();
}

/*
 * 函数名称：MainWindow::Initial
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为初始化函数。
 */

void MainWindow::Initial(){

}

/*
 * 函数名称：MainWindow::File_Backup
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为备份数据函数，将当前程序数据备份以便下次使用，被SetSlots调用。
 */

void MainWindow::File_Backup(){
    timer->stop();//停止计时器

    db.close();
    QFile fileBackup(BackupFileName);
    QFile fileNow(DBFileName);

    if(fileBackup.exists()){
        fileBackup.remove();
    }
    if(!fileNow.exists()){
        QMessageBox::warning(NULL, "提示","数据库文件不存在。", QMessageBox::Yes | QMessageBox::Yes);
        return;
    }
    fileNow.copy(BackupFileName);
    if(!fileBackup.exists()){
        QMessageBox::warning(NULL, "提示","备份失败，请联系管理员。", QMessageBox::Yes | QMessageBox::Yes);
        return;
    }

    fileBackup.close();
    db.open();

    //需要备份系统信息，用.ini文件存
    QSettings settings(IniFileName, QSettings::IniFormat); // 当前目录的INI文件
    settings.beginGroup("SystemInfo");
    settings.setValue("currenttime", currentTime.toString(TimeFormat));
    settings.setValue("now",now);
    settings.endGroup();

    BackupDialog * backupDialog = new BackupDialog(this);
    backupDialog->exec();
    timer->start(TrigFrequency);
}

/*
 * 函数名称：MainWindow::File_Restore
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为恢复备份数据函数，实现程序接着上一次的数据运行，被SetSlots调用。
 */

void MainWindow::File_Restore(){
    timer->stop();//停止计时器

    db.close();
    QFile fileBackup(BackupFileName);
    QFile fileNow(DBFileName);
    if(fileNow.exists()){
        fileNow.remove();
    }
    if(!fileBackup.exists()){
        QMessageBox::warning(NULL, "提示","备份文件不存在。", QMessageBox::Yes | QMessageBox::Yes);
        return;
    }
    fileBackup.copy(DBFileName);
    if(!fileNow.exists()){
        QMessageBox::warning(NULL, "提示","还原失败，请联系管理员。", QMessageBox::Yes | QMessageBox::Yes);
        return;
    }
    fileNow.close();
    db.open();

    //需要还原系统信息，读.ini文件
    QSettings settings(IniFileName, QSettings::IniFormat);
    currentTime=
            QDateTime::fromString(settings.value("SystemInfo/currenttime").toString(),TimeFormat);//获取当前时间
    qDebug()<<"ini备份文件中，当前时间为："<<currentTime.toString(TimeFormat);//Debug时使用
    now=settings.value("SystemInfo/now").toInt();

    RestoreDialog * restoreDialog = new RestoreDialog(this);
    restoreDialog->exec();
    timer->start(TrigFrequency);
}



/*
 * 函数名称：MainWindow::About_AboutUs
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为开发者信息函数，被SetSlots调用。
 */

void MainWindow::About_AboutUs(){
    timer->stop();
    AboutUsDialog * aboutusDialog = new AboutUsDialog(this);
    aboutusDialog->exec();
    timer->start(TrigFrequency);
}



/*
 * 函数名称：MainWindow::CurrentState
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来刷新状态，被ProcessTime调用。
 */

void MainWindow::CurrentState(){//有计时器触发，刷新频率和计时器一致
    CalculateStatus();//先算旅客的状态迁移
    DisplayStatistics();//显示统计信息
    DisplayTravellerStatus();//表示每个旅客的状态
}

/*
 * 函数名称：MainWindow::CalculateStatus
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来实现自动机，被CurrentState调用。
 */

void MainWindow::CalculateStatus(){
    //自动机
    std::list<Traveller>::iterator itor;
    TravelCityInfo tempCityInfo;
    QSqlQuery query;
    for(itor=travellerList.begin(); itor!=travellerList.end(); itor++){//遍历旅客链表
        if(currentTime.toString("h").toInt()==0) itor->waitNextDay=false;
        if(!itor->pathList.empty())
            tempCityInfo=itor->pathList.front();
        if(itor->nowStatus==waiting){//旅客状态为等待中
            if(currentTime.date()<itor->startDate){//未到出发日期则继续等待
                itor->nowStatus=waiting;
            }
            else if(currentTime.date()>=itor->startDate){//已经到出发日期
                if(currentTime.toString("h").toInt()<tempCityInfo.startTime){//未到出发时间则继续等待
                    itor->nowStatus=waiting;
                }
                else{
                    itor->nowStatus=traveling;//已到出发时间则开始旅行并更改数据库信息
                    query.exec("UPDATE travellerInfo SET nowStatus = "+QString::number(1)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                    query.exec("UPDATE travellerInfo SET startCity = "+QString::number(tempCityInfo.begin)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                    query.exec("UPDATE travellerInfo SET endCity = "+QString::number(tempCityInfo.end)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                    logPrint(itor->name+"("+QString::number(itor->seqNum)+") 于" +IntIntoString(tempCityInfo.begin)+" 开始旅行，从" +IntIntoString(tempCityInfo.begin)+ "到"+IntIntoString(tempCityInfo.end)+ "。");
                }
            }
            else{
                qDebug()<<"MainWindow::CalculateStatus()出错，status==waiting有误";
            }
        }
        else if(itor->nowStatus==traveling){//旅客状态为旅行中
            if(currentTime.toString("h").toInt()<tempCityInfo.endTime){//未到结束时间则继续旅行
                itor->nowStatus=traveling;
            }
            else if(currentTime.toString("h").toInt()>=tempCityInfo.endTime){//已到结束时间
                int temp=tempCityInfo.endTime;
                Cities destination = tempCityInfo.end;
                itor->pathList.pop_front();//在路线链表中删去已经旅行过的
                if(!itor->pathList.empty())//若剩下的路线链表非空
                    tempCityInfo=itor->pathList.front();
                if(temp>tempCityInfo.startTime){//下一段出发时间早于结束时间则等待第二天才能出发
                    itor->waitNextDay=true;
                }
                if(!itor->pathList.empty()){//若剩下的路线链表非空
                    itor->nowStatus=staying;//更改状态为停留并更新数据库信息
                    query.exec("UPDATE travellerInfo SET nowStatus = "+QString::number(2)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                    query.exec("UPDATE travellerInfo SET startCity = "+QString::number(tempCityInfo.begin)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                    query.exec("UPDATE travellerInfo SET endCity = "+QString::number(tempCityInfo.end)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                    logPrint(itor->name+"("+QString::number(itor->seqNum)+") 到达中间站" +IntIntoString(tempCityInfo.begin)+"。");
                }
                else{
                    itor->nowStatus=finished;//剩余路线链表为空则更改状态为结束并更新数据库
                    query.exec("UPDATE travellerInfo SET nowStatus = "+QString::number(3)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                    logPrint(itor->name+"("+QString::number(itor->seqNum)+") 到达终点" +IntIntoString(destination)+ "。");
                }
            }
            else{
                qDebug()<<"MainWindow::CalculateStatus()出错，statue==travelling有误";
            }
        }
        else if(itor->nowStatus==staying){//旅客状态为停留
            if(itor->waitNextDay) continue;//等待第二天出发则继续
            if(currentTime.toString("h").toInt()<tempCityInfo.startTime){//未到出发时间则继续停留
                itor->nowStatus=staying;
            }
            else if(currentTime.toString("h").toInt()>=tempCityInfo.startTime){//已到出发时间则开始旅行
                itor->nowStatus=traveling;//更改状态为旅行中并更新数据库
                query.exec("UPDATE travellerInfo SET nowStatus = "+QString::number(1)+" WHERE seqNum = " +QString::number(itor->seqNum)+"");
                logPrint(itor->name+"("+QString::number(itor->seqNum)+") 在路上：从" +IntIntoString(tempCityInfo.begin)+ "到"+IntIntoString(tempCityInfo.end)+ "。");
            }
            else{
                qDebug()<<"MainWindow::CalculateStatus()出错，statue==staying有误";
            }
        }
        else if(itor->nowStatus==finished){//旅客状态为结束旅行
            travellerList.erase(itor);//删去此旅客结点，但保留数据库数据
            itor--;
        }
        else{
            qDebug()<<"Mainwindow::CalculateStatus()出错，旅客状态错误";
        }
    }
}



/*
 * 函数名称：MainWindow::DisplayStatistics
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来打印各城市的滞留旅客数量，被CurrentState调用。
 */

void MainWindow::DisplayStatistics(){
    QSqlQuery query;
    int num=0;
    for(int i=0;i<20;i++){//遍历城市数组，在数据库中查询在此城市的旅客，统计数量
        num=0;
        query.exec("SELECT * FROM travellerInfo WHERE startCity = "+TntToString(i));
        while (query.next()){
            if(query.value(nowStatus).toInt()==0||query.value(nowStatus).toInt()==2)num++;//旅客状态为等待或停留
        }
        eachCity[i]=num;
    }
}

/*
 * 函数名称：MainWindow::DisplayTravellerStatus
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来打印旅客状态，被CurrentState调用。
 */

void MainWindow::DisplayTravellerStatus(){

}



/*
 * 函数名称：MainWindow::~MainWindow
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

MainWindow::~MainWindow()
{
    db.close();
    QFile::remove(DBFileName);

    delete ui;
}

/*以下二十个函数的功能一致
 * 函数名称：MainWindow::on_城市名_clicked
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来打印被点击的城市的名称和滞留旅客数量。
 */

//按钮函数
void MainWindow::on_Baotou_clicked(){
    ui->city->setText("包头");
    ui->people->setText(QString::number(eachCity[0],10));
}

void MainWindow::on_Huhehaote_clicked(){
    ui->city->setText("呼和浩特");
    ui->people->setText(QString::number(eachCity[1],10));
}

void MainWindow::on_Tongliao_clicked(){
    ui->city->setText("通辽");
    ui->people->setText(QString::number(eachCity[2],10));
}

void MainWindow::on_Beijing_clicked(){
    ui->city->setText("北京");
    ui->people->setText(QString::number(eachCity[3],10));
}

void MainWindow::on_Tianjin_clicked(){
    ui->city->setText("天津");
    ui->people->setText(QString::number(eachCity[4],10));
}

void MainWindow::on_Taiyuan_clicked(){
    ui->city->setText("太原");
    ui->people->setText(QString::number(eachCity[5],10));
}

void MainWindow::on_Changzhou_clicked(){
    ui->city->setText("常州");
    ui->people->setText(QString::number(eachCity[6],10));
}

void MainWindow::on_Shanghai_clicked(){
    ui->city->setText("上海");
    ui->people->setText(QString::number(eachCity[7],10));
}

void MainWindow::on_Hangzhou_clicked(){
    ui->city->setText("杭州");
    ui->people->setText(QString::number(eachCity[8],10));
}

void MainWindow::on_Ningbo_clicked(){
    ui->city->setText("宁波");
    ui->people->setText(QString::number(eachCity[9],10));
}

void MainWindow::on_Wenzhou_clicked(){
    ui->city->setText("温州");
    ui->people->setText(QString::number(eachCity[10],10));
}

void MainWindow::on_Lishui_clicked(){
    ui->city->setText("丽水");
    ui->people->setText(QString::number(eachCity[11],10));
}

void MainWindow::on_Chongqing_clicked(){
    ui->city->setText("重庆");
    ui->people->setText(QString::number(eachCity[12],10));
}

void MainWindow::on_Kunming_clicked(){
    ui->city->setText("昆明");
    ui->people->setText(QString::number(eachCity[13],10));
}

void MainWindow::on_Panzhihua_clicked(){
    ui->city->setText("攀枝花");
    ui->people->setText(QString::number(eachCity[14],10));
}

void MainWindow::on_Xianggelila_clicked(){
    ui->city->setText("香格里拉");
    ui->people->setText(QString::number(eachCity[15],10));
}

void MainWindow::on_Lijiang_clicked(){
    ui->city->setText("丽江");
    ui->people->setText(QString::number(eachCity[16],10));
}

void MainWindow::on_Erhai_clicked(){
    ui->city->setText("洱海");
    ui->people->setText(QString::number(eachCity[17],10));
}

void MainWindow::on_Dali_clicked(){
    ui->city->setText("大理");
    ui->people->setText(QString::number(eachCity[18],10));
}

void MainWindow::on_Xishuangbanna_clicked(){
    ui->city->setText("西双版纳");
    ui->people->setText(QString::number(eachCity[19],10));
}


/*
 * 函数名称：MainWindow::logPrint
 * 参数列表说明：函数接收一个参数：str为事件内容的字符串
 * 返回值：无
 * 功能说明：该函数用来向数据库写入日志，被CalculateStatus调用。
 */

void MainWindow::logPrint(QString str){
    QSqlQuery query;
    QDateTime temp=QDateTime::fromString("2016/01/01 00:00:00",TimeFormat);//获取当前时间
    temp=temp.addSecs(qint64(now));
    bool test = true;
    test = query.prepare("INSERT INTO log( time, strEvent) VALUES( :time, :strEvent)");//向数据库写日志
    if (test){
        query.bindValue(":time", temp.toString(TimeFormat));
        query.bindValue(":strEvent", str);
        test = query.exec();
    }
}

/*
 * 函数名称：MainWindow::StringToCity
 * 参数列表说明：函数接收一个参数：city为转换的城市的名称
 * 返回值：返回一个表示城市的Cities型的值
 * 功能说明：该函数用来实现QString到Cities型的转换。
 */

Cities MainWindow::StringToCity(QString city){
    if(city=="0") return Baotou;
    else if(city=="1") return Huhehaote;
    else if(city=="2") return Tongliao;
    else if(city=="3") return Beijing;
    else if(city=="4") return Tianjin;
    else if(city=="5") return Taiyuan;
    else if(city=="6") return Changzhou;
    else if(city=="7") return Shanghai;
    else if(city=="8") return Hangzhou;
    else if(city=="9") return Ningbo;
    else if(city=="10") return Wenzhou;
    else if(city=="11") return Lishui;
    else if(city=="12") return Chongqing;
    else if(city=="13") return Kunming;
    else if(city=="14") return Panzhihua;
    else if(city=="15") return Xianggelila;
    else if(city=="16") return Lijiang;
    else if(city=="17") return Erhai;
    else if(city=="18") return Dali;
    else if(city=="19") return Xishuangbanna;
    else{
        qDebug()<<"MainWindow::StringToCity中出错";
    }
    return unknown;
}

/*
 * 函数名称：MainWindow::IntIntoCity
 * 参数列表说明：函数接收一个参数：cityInt为转换的城市的名称
 * 返回值：返回一个表示城市的Cities型的值
 * 功能说明：该函数用来实现int到Cities型的转换被ReTravaller调用。
 */

Cities MainWindow::IntIntoCity(int cityInt){
    if(cityInt==0) return Baotou;
    else if(cityInt==1) return Huhehaote;
    else if(cityInt==2) return Tongliao;
    else if(cityInt==3) return Beijing;
    else if(cityInt==4) return Tianjin;
    else if(cityInt==5) return Taiyuan;
    else if(cityInt==6) return Changzhou;
    else if(cityInt==7) return Shanghai;
    else if(cityInt==8) return Hangzhou;
    else if(cityInt==9) return Ningbo;
    else if(cityInt==10) return Wenzhou;
    else if(cityInt==11) return Lishui;
    else if(cityInt==12) return Chongqing;
    else if(cityInt==13) return Kunming;
    else if(cityInt==14) return Panzhihua;
    else if(cityInt==15) return Xianggelila;
    else if(cityInt==16) return Lijiang;
    else if(cityInt==17) return Erhai;
    else if(cityInt==18) return Dali;
    else if(cityInt==19) return Xishuangbanna;
    else{
        qDebug()<<"Map::IntIntoCity中出错";
        return unknown;
    }
    return unknown;
}

/*
 * 函数名称：MainWindow::CityToInt
 * 参数列表说明：函数接收一个参数：cityInt为转换的城市的名称
 * 返回值：返回一个表示城市的Int型的值
 * 功能说明：该函数用来实现Cities型到int的转换。
 */

int MainWindow::CityToInt(Cities cityInt){
    if(cityInt==Baotou) return 0;
    else if(cityInt==Huhehaote) return 1;
    else if(cityInt==Tongliao) return 2;
    else if(cityInt==Beijing) return 3;
    else if(cityInt==Tianjin) return 4;
    else if(cityInt==Taiyuan) return 5;
    else if(cityInt==Changzhou) return 6;
    else if(cityInt==Shanghai) return 7;
    else if(cityInt==Hangzhou) return 8;
    else if(cityInt==Ningbo) return 9;
    else if(cityInt==Wenzhou) return 10;
    else if(cityInt==Lishui) return 11;
    else if(cityInt==Chongqing) return 12;
    else if(cityInt==Kunming) return 13;
    else if(cityInt==Panzhihua) return 14;
    else if(cityInt==Xianggelila) return 15;
    else if(cityInt==Lijiang) return 16;
    else if(cityInt==Erhai) return 17;
    else if(cityInt==Dali) return 18;
    else if(cityInt==Xishuangbanna) return 19;
    else{
        qDebug()<<"Map::IntIntoCity中出错";
        return unknown;
    }
    return unknown;
}

/*
 * 函数名称：MainWindow::CityToNumString
 * 参数列表说明：函数接收一个参数：city为转换的城市的名称
 * 返回值：返回一个表示城市的QString型的值
 * 功能说明：该函数用来实现Cities型到QString的转换。
 */

QString MainWindow::CityToNumString(Cities city){
    if(city==Baotou) return "0";
    else if(city==Huhehaote) return "1";
    else if(city==Tongliao) return "2";
    else if(city==Beijing) return "3";
    else if(city==Tianjin) return "4";
    else if(city==Taiyuan) return "5";
    else if(city==Changzhou) return "6";
    else if(city==Shanghai) return "7";
    else if(city==Hangzhou) return "8";
    else if(city==Ningbo) return "9";
    else if(city==Wenzhou) return "10";
    else if(city==Lishui) return "11";
    else if(city==Chongqing) return "12";
    else if(city==Kunming) return "13";
    else if(city==Panzhihua) return "14";
    else if(city==Xianggelila) return "15";
    else if(city==Lijiang) return "16";
    else if(city==Erhai) return "17";
    else if(city==Dali) return "18";
    else if(city==Xishuangbanna) return "19";
    else{
        qDebug()<<"FillTimeDialog::CityIntToString中出错";
    }
    return "";
}

/*
 * 函数名称：MainWindow::IntIntoString
 * 参数列表说明：函数接收一个参数：cityInt为转换的城市的名称
 * 返回值：返回一个表示城市的QString型的字符串。
 * 功能说明：该函数用来实现Int到QString型的转换，被CalculateStatus，Search,SearchAlter,Retraveller调用。
 */

QString MainWindow::IntIntoString(int cityInt){
    if(cityInt==0) return "包头";
    else if(cityInt==1) return "呼和浩特";
    else if(cityInt==2) return "通辽";
    else if(cityInt==3) return "北京";
    else if(cityInt==4) return "天津";
    else if(cityInt==5) return "太原";
    else if(cityInt==6) return "常州";
    else if(cityInt==7) return "上海";
    else if(cityInt==8) return "杭州";
    else if(cityInt==9) return "宁波";
    else if(cityInt==10) return "温州";
    else if(cityInt==11) return "丽水";
    else if(cityInt==12) return "重庆";
    else if(cityInt==13) return "昆明";
    else if(cityInt==14) return "攀枝花";
    else if(cityInt==15) return "香格里拉";
    else if(cityInt==16) return "丽江";
    else if(cityInt==17) return "洱海";
    else if(cityInt==18) return "大理";
    else if(cityInt==19) return "西双版纳";
    else{
        qDebug()<<"Map::IntIntoString中出错";
    }
    return "";
}


/*
 * 函数名称： MainWindow::TntToString
 * 参数列表说明：函数接收一个参数：city为转换的城市的名称
 * 返回值：返回一个表示城市的QString型的字符串。
 * 功能说明：该函数用来实现Int到QString型的转换，被DisplayStatistics调用。
 */

QString MainWindow::TntToString(int city){
    if(city==0) return "0";
    else if(city==1) return "1";
    else if(city==2) return "2";
    else if(city==3) return "3";
    else if(city==4) return "4";
    else if(city==5) return "5";
    else if(city==6) return "6";
    else if(city==7) return "7";
    else if(city==8) return "8";
    else if(city==9) return "9";
    else if(city==10) return "10";
    else if(city==11) return "11";
    else if(city==12) return "12";
    else if(city==13) return "13";
    else if(city==14) return "14";
    else if(city==15) return "15";
    else if(city==16) return "16";
    else if(city==17) return "17";
    else if(city==18) return "18";
    else if(city==19) return "19";
    else{
        qDebug()<<"Map::IntToNumString中出错";
    }
    return "";
}
