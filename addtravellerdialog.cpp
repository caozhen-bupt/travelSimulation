/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：addtravellerdialog.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了AddTravellerDialog类中，各成员函数的实现，用于
 *         旅客的添加，在AddTravellerDialog.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.6.3 戴唯 修改了该文件。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数
 */

/*包含头文件*/

#include "addtravellerdialog.h"
#include "ui_addtravellerdialog.h"
#include "calendardialog.h"
#include "ui_calendardialog.h"
#include "filltimedialog.h"
#include "ui_filltimedialog.h"
#include "choosecitydialog.h"
#include "ui_choosecitydialog.h"

#include <QDebug>

/*
 * 函数名称：AddTravellerDialog::AddTravellerDialog
 * 参数列表说明：函数接收父窗口为参数。
 * 返回值：无
 * 功能说明：该函数为构造函数，进行相应的初始化操作。
 */

AddTravellerDialog::AddTravellerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTravellerDialog)
{
    ui->setupUi(this);//设置窗口属性
    this->setFixedSize(670,525);//锁死窗口大小

    this->traveller=NULL;//初始化
    passCityNum=0;
    passCityList.clear();
    timeSelected.setDate(2500,1,1);
    change=false;
    SetConnect();
    seqNum=0;
    status=0;
    seqNumnext=0;
    namenext="";
    identNumnext="";
}

/*
 * 函数名称：AddTravellerDialog::SetConnect
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为将信号与槽函数连接起来。
 */

void AddTravellerDialog::SetConnect(){
    connect(ui->reset,SIGNAL(clicked()),this,SLOT(ResetInfo()));
    connect(ui->selectTime,SIGNAL(clicked()),this,SLOT(SelectTime()));
    connect(ui->yep,SIGNAL(clicked()),this,SLOT(FillTime()));

    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(close()));
}

/*
 * 函数名称：AddTravellerDialog::ResetInfo
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为清空函数，将所打印内容清空，被SetConnect调用。
 */

void AddTravellerDialog::ResetInfo(){

    if(!change){//如果当前操作被更改旅客，则不清空起点
        ui->endDisplay->setText("");
    
    }
    ui->endDisplay->setText("");//清空相应的打印区域
    ui->passDisplay->setText("");
    ui->timeDisplay->setText("");
    passCityNum=0;
    passCityList.clear();
    timeSelected.setDate(2500,1,1);
}

/*
 * 函数名称：AddTravellerDialog::SelectTime
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为选择时间函数，进行出发时间的选择，并将时间打印，被SetConnect调用。
 */

void AddTravellerDialog::SelectTime(){
    if(status==1){//如果当前被更改的旅客状态为旅行中，则设置出发时间为当前旅行目的城市到达时间
        ui->timeDisplay->setText(startTimenext.toString("yyyy/MM/dd"));
    }
    else{//否则进行出发时间选择
        CalendarDialog * calenderDialog = new CalendarDialog(this);
        calenderDialog->exec();
        if(calenderDialog->isYep){
            timeSelected = calenderDialog->time;
            if(timeSelected>=currentTime.date()){
                ui->timeDisplay->setText(timeSelected.toString("yyyy/MM/dd"));//打印选择时间
            }
            else{
                QMessageBox::warning(NULL, "提示","请选择今天"+currentTime.date().toString()+"或以后的时期", QMessageBox::Yes | QMessageBox::Yes);//提示错误信息
            }
        }
    
        //记得delete对象
        delete calenderDialog;
    }
}


/*
 * 函数名称：AddTravellerDialog::FillTime
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为停留时间的获取函数，进行各途经城市停留时间的输入并记录，被SetConnect调用。
 */

void AddTravellerDialog::FillTime(){
    if(ui->startDisplay->text()!="" && ui->endDisplay->text()!="" && ui->timeDisplay->text()!=""){
        if(ui->startDisplay->text()==ui->endDisplay->text()){//若起始城市和终止城市相同，则显示错误提示
            QMessageBox::warning(NULL, "提示", "请修改起始城市或终止城市，二者不能相同", QMessageBox::Yes | QMessageBox::Yes);
            return ;
        }
        FillTimeDialog * filltimeDialog = new FillTimeDialog(this);//生成新的FillTimeDialog类，记录旅客信息
        if(change){
            filltimeDialog->namenext=this->namenext;
            filltimeDialog->identNumnext=this->identNumnext;
            filltimeDialog->seqNumnext=this->seqNumnext;
        }
        else{
            filltimeDialog->seqNum=this->seqNum;
        }

        filltimeDialog->passCityNum=this->passCityNum;
        filltimeDialog->passCityList=this->passCityList;
        filltimeDialog->startCity=this->startCity;
        filltimeDialog->endCity=this->endCity;
        filltimeDialog->currentTime=this->currentTime.toString("h").toInt();
        filltimeDialog->change=this->change;
        qDebug()<<"change in add"<<filltimeDialog->change;
        filltimeDialog->SetTable();


        filltimeDialog->exec();
        this->traveller=filltimeDialog->traveller;//将当前对象的旅客指针指向新的FillTimeDialog类的旅客指针
        if(traveller){
            TravelCityInfo temp=this->traveller->pathList.front();
            this->traveller->startDate=this->timeSelected;
            if(timeSelected==currentTime.date() && temp.startTime<currentTime.toString("h").toInt()){
                this->traveller->startDate=this->traveller->startDate.addDays(1);
            }
        }
        //记得delete对象
        delete filltimeDialog;
        this->close();
    }
    else{//输入信息不完整提示错误
        QMessageBox::warning(NULL, "提示", "请选择完整的旅行信息", QMessageBox::Yes | QMessageBox::Yes);
    }
}

/*
 * 函数名称：AddTravellerDialog::DisplayCityAttr
 * 参数列表说明：该函数接收三个参数attr为当前城市的类型，nowCityStr为当前城市字符串，nowCityInt为当前城市Cities枚举值
 * 返回值：无
 * 功能说明：该函数将选择的城市按其类型打印，被AddTravellerDialog::on_城市名_clicked调用。
 */

void AddTravellerDialog::DisplayCityAttr(CityChoose attr,QString nowCityStr, Cities nowCityInt){
    if(attr==start){//选择城市为起点
        if(change){//该旅客是正在被更改行程的旅客
            QMessageBox::warning(NULL, "提示", "您不能修改起始城市", QMessageBox::Yes | QMessageBox::Yes);//提示错误信息
        }
        else{
            ui->startDisplay->setText(nowCityStr);//是新旅客则打印起点城市
            startCity=nowCityInt;
        }
    }
    else if(attr==end){//选择城市为终点城市
        ui->endDisplay->setText(nowCityStr);//打印终点城市
        endCity=nowCityInt;
    }
    else if(attr==pass){//选择城市为途经城市
        QString temp;
        if(ui->passDisplay->text()==""){//该城市是第一个途经城市
            temp=nowCityStr;
        }
        else{
            temp=ui->passDisplay->text()+"->"+nowCityStr;//打印途经城市和“->”
        }
        ui->passDisplay->setText(temp);
        passCityNum++;
        PassCityInfo temp_passcityinfo;
        temp_passcityinfo.name=nowCityInt;
        passCityList.push_back(temp_passcityinfo);
    }
    else{
        qDebug()<<"出错，AddTravellerDialog::DisplayCityAttr()";
    }
}

/*
 * 函数名称：AddTravellerDialog::~AddTravellerDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

AddTravellerDialog::~AddTravellerDialog()
{
    delete ui;
}

/* 以下函数功能一致。
 * 函数名称：AddTravellerDialog::on_城市名_clicked
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为接收城市名按键信号的槽函数。
 */

void AddTravellerDialog::on_Baotou_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"包头",Baotou);

    delete choosecityDialog;
}


void AddTravellerDialog::on_Huhehaote_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"呼和浩特",Huhehaote);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Tongliao_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"通辽",Tongliao);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Beijing_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"北京",Beijing);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Tianjin_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"天津",Tianjin);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Taiyuan_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
       DisplayCityAttr(choosecityDialog->attrSelected,"太原",Taiyuan);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Changzhou_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"常州",Changzhou);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Shanghai_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"上海",Shanghai);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Hangzhou_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"杭州",Hangzhou);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Ningbo_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"宁波",Ningbo);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Lishui_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"丽水",Lishui);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Wenzhou_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"温州",Wenzhou);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Chongqing_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"重庆",Chongqing);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Xianggelila_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"香格里拉",Xianggelila);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Panzhihua_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"攀枝花",Panzhihua);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Kunming_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"昆明",Kunming);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Xishuangbanna_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
       DisplayCityAttr(choosecityDialog->attrSelected,"西双版纳",Xishuangbanna);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Lijiang_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"丽江",Lijiang);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Erhai_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"洱海",Erhai);

    delete choosecityDialog;
}

void AddTravellerDialog::on_Dali_clicked()
{
    ChooseCityDialog * choosecityDialog=new ChooseCityDialog(this);
    choosecityDialog->exec();
    if(choosecityDialog->isOK)
        DisplayCityAttr(choosecityDialog->attrSelected,"大理",Dali);

    delete choosecityDialog;
}
