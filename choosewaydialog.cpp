/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：choosewaydialog.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了ChooseWayDialog类中，各成员函数的实现，用于
 *         策略的打印和选择，在choosewayDialog.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4  戴唯 为该文件完善了注释。
 *  2016.5.25 曹桢 修改了该文件，添加了一些函数功能。
 *  2016.5.24 戴唯 修改了该文件，添加了一些函数功能。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数。
 */

/*包含头文件*/

#include "choosewaydialog.h"
#include "ui_choosewaydialog.h"
#include "fillinfodialog.h"
#include "ui_fillinfodialog.h"

/*
 * 函数名称：ChooseWayDialog::ChooseWayDialog
 * 参数列表说明：函数接收其父窗口为参数。
 * 返回值：无
 * 功能说明：该函数为构造函数。
 */

ChooseWayDialog::ChooseWayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseWayDialog)
{
    change=false;//初始化操作
    seqNum=0;
    namenext="";
    seqNumnext=0;
    ui->setupUi(this);//设置窗口属性
    this->traveller=NULL;
    this->passCityList.clear();

    ui->tableWidget_leastMoney->setColumnCount(6);//设置三个策略打印表格格式和表头
    ui->tableWidget_leastMoney->setHorizontalHeaderLabels
            (QStringList()<<"起始城市"<<"终止城市"<<"班次"<<"出发时间"<<"到达时间"<<"花费金钱");
    ui->tableWidget_leastTime->setColumnCount(6);
    ui->tableWidget_leastTime->setHorizontalHeaderLabels
            (QStringList()<<"起始城市"<<"终止城市"<<"班次"<<"出发时间"<<"到达时间"<<"花费金钱");
    ui->tableWidget_limitTime->setColumnCount(6);
    ui->tableWidget_limitTime->setHorizontalHeaderLabels
            (QStringList()<<"起始城市"<<"终止城市"<<"班次"<<"出发时间"<<"到达时间"<<"花费金钱");

    listPath_str1.clear();//各策略路线链表初始化
    listPath_str2.clear();
    listPath_str3.clear();

    connect(ui->choosenow,SIGNAL(clicked()),this,SLOT(FillInfo()));//连接选择当前策略点击信号和FillInfo函数
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(close()));//连接取消点击信号和close函数
}

/*
 * 函数名称：ChooseWayDialog::FillInfo
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来创建获取旅客信息的窗口，被ChooseWayDialog调用。
 */

void ChooseWayDialog::FillInfo(){
    if(ui->tabWidget->currentIndex()==2 && listPath_str3.empty()){//策略三为空时进行了选择则报错
        QMessageBox::warning(NULL, "提示", "请选择有效策略", QMessageBox::Yes | QMessageBox::Yes);
        return ;
    }

    FillInfoDialog * fillinfoDialog = new FillInfoDialog(this);//创建新的FillInfoDialog类
    fillinfoDialog->seqNum=this->seqNum;//将旅客信息赋值给新的类
    fillinfoDialog->startcity=this->startCity;
    fillinfoDialog->endcity=this->endCity;

    if(ui->tabWidget->currentIndex()==0){//选择最少金钱策略
        fillinfoDialog->pathList=this->listPath_str2;
        fillinfoDialog->moneyConsum=this->str2_moneyConsum;
        fillinfoDialog->timeConsum=this->str2_timeSum;
        if(change){//若为更改过程中的操作则直接生成新的旅客结点加入链表，不再要求填写个人信息
            traveller = new Traveller;
            traveller->pathList=this->listPath_str2;
            traveller->moneyConsum=this->str2_moneyConsum;
            traveller->timeConsum=this->str2_timeSum;
        }
    }
    else if(ui->tabWidget->currentIndex()==1){//选择最少时间策略
        fillinfoDialog->pathList=this->listPath_str1;
        fillinfoDialog->moneyConsum=this->str1_moneyConsum;
        fillinfoDialog->timeConsum=this->str1_timeSum;
        if(change){//若为更改过程中的操作则直接生成新的旅客结点加入链表，不再要求填写个人信息
            traveller = new Traveller;
            traveller->pathList=this->listPath_str1;
            traveller->moneyConsum=this->str1_moneyConsum;
            traveller->timeConsum=this->str1_timeSum;
        }
    }
    else if(ui->tabWidget->currentIndex()==2){//选择限时最少金钱策略
        fillinfoDialog->pathList=this->listPath_str3;
        fillinfoDialog->moneyConsum=this->str3_moneyConsum;
        fillinfoDialog->timeConsum=this->str3_timeSum;
        if(change){//若为更改过程中的操作则直接生成新的旅客结点加入链表，不再要求填写个人信息
            traveller = new Traveller;
            traveller->pathList=this->listPath_str3;
            traveller->moneyConsum=this->str3_moneyConsum;
            traveller->timeConsum=this->str3_timeSum;
        }
    }
    else{
        qDebug()<<"ChooseWayDialog::FillInfo()出错，ui->tabWidget->currentIndex()值错误";
    }

    if(change){//若为更改过程中的操作则直接生成新的旅客结点加入链表，不再要求填写个人信息
        traveller->name=this->namenext;
        traveller->identNum=this->identNumnext;
        traveller->seqNum=this->seqNumnext;
        qDebug()<<"seqnum"<<traveller->seqNum;

        logPrint(traveller->name+"("+QString::number(traveller->seqNum)+") 更改旅行。");//将更改信息日志加入数据库

        traveller->nowStatus=waiting;//被更改的旅客当前状态改为等待

        TravelCityInfo temp=traveller->pathList.front();
        Cities e=temp.end;
        Cities s=temp.begin;
        qDebug()<<"end"<<temp.end;
        QSqlQuery query;//将此旅客在数据库中的信息更新成更改之后的
        bool test=query.exec("UPDATE travellerInfo SET nowStatus = "+QString::number(0)+" WHERE seqNum = " +QString::number(traveller->seqNum)+"");
        qDebug()<<"test"<<test;
        test=query.exec("UPDATE travellerInfo SET startCity = "+CityToNumString(s)+" WHERE seqNum = " +QString::number(traveller->seqNum)+"");
        qDebug()<<"test1"<<test;
        test=query.exec("UPDATE travellerInfo SET endCity = "+CityToNumString(e)+" WHERE seqNum = " +QString::number(traveller->seqNum)+"");
        qDebug()<<"test2"<<test;
        test=query.exec("SELECT * FROM travellerInfo WHERE seqNum= " +QString::number(traveller->seqNum)+"");
        qDebug()<<"test3"<<test;
        qDebug()<<"seqnum3"<<traveller->seqNum;
        while(query.next()){
            int seq=query.value("seqNum").toInt();
            QString st=query.value("startCity").toString();
            QString en=query.value("endCity").toString();
            QString na=query.value("name").toString();
            qDebug()<<"name"<<na;
            qDebug()<<"start"<<st;
            qDebug()<<"end"<<en;

        }

    }
    else{//若不是更改过程则按照正常加入旅客过程弹出信息确认
        fillinfoDialog->exec();
        this->traveller=fillinfoDialog->traveller;
    }

    delete fillinfoDialog;
    //delete object
    this->close();
}

/*
 * 函数名称：ChooseWayDialog::SetTable
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来打印路线表格。
 */

void ChooseWayDialog::SetTable(){

    GetLeastMoney();//调用获取前两种策略的函数
    GetLeastTime();

    if(str2_timeSum>upperBound){//若最少时间策略消耗时间大于时间上限则报错
        qDebug()<<"时间上限设置不合理";
        if(upperBound>=0){
            QMessageBox::warning(NULL, "提示","时间上限设置不合理，将不显示限时最少金钱策略的路线", QMessageBox::Yes | QMessageBox::Yes);
        }


        return ;
    }
    else if(str2_timeSum==upperBound){//若最少时间策略时间消耗正好等于时间上限
        qDebug()<<"直接使用最少时间策略";
        int count=0;
        std::list<TravelCityInfo>::iterator itor_list;
        for(itor_list=listPath_str2.begin(); itor_list!=listPath_str2.end(); itor_list++, count++){//逐个结点打印路线信息
            ShowLimitTime(count, CityIntToString(itor_list->begin), CityIntToString(itor_list->end), itor_list->No, itor_list->startTime, itor_list->endTime, itor_list->moneyConsum);
        }
        listPath_str3.clear();
        std::copy(listPath_str2.begin(), listPath_str2.end(), std::back_inserter(listPath_str3));//将路线链表赋值
    }
    else if(str2_timeSum<upperBound){//若最少时间策略时间消耗小于时间上限
        if(str1_timeSum<=upperBound){//若最少金钱策略时间消耗小于等于时间上限
            qDebug()<<"直接使用最少金钱策略";
            int count=0;
            std::list<TravelCityInfo>::iterator itor_list;
            for(itor_list=listPath_str1.begin(); itor_list!=listPath_str1.end(); itor_list++, count++){
                ShowLimitTime(count, CityIntToString(itor_list->begin), CityIntToString(itor_list->end), itor_list->No, itor_list->startTime, itor_list->endTime, itor_list->moneyConsum);
            }
            listPath_str3.clear();
            std::copy(listPath_str1.begin(), listPath_str1.end(), std::back_inserter(listPath_str3));
        }
        else{//使用限时最少金钱策略
            GetLimitTime();
        }
    }
    else{
        qDebug()<<"ChooseWayDialog::SetTable()出错，策略2的时间消耗和upperBound无法比较";
    }
}

/*
 * 函数名称：ChooseWayDialog::GetLeastMoney
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来获取最少金钱策略的生成路线，被SetTable调用。
 */

void ChooseWayDialog::GetLeastMoney(){

    str1_endTime=currentTime;

    Map * mapPointer;
    std::list<PassCityInfo>::iterator itor_vec;
    std::list<PassCityInfo>::iterator itor_vec_last;
    std::list<TravelCityInfo>::iterator itor_list;
    std::list<TravelCityInfo> * tempPointer;

    listPath_str1.clear();//初始化

    str1_timeSum=0;
    str1_moneyConsum=0;
    int count = 0;
    if(passCityList.empty()){//途经城市为空
        mapPointer=new Map;
        tempPointer = mapPointer->LeastTime(startCity, endCity, str1_endTime, str1_timeSum);//路径即为从起点直接到终点
        delete mapPointer;
        std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str1));//复制生成的路径链表到最少金钱策略路径链表中
    }
    else{
        for(itor_vec=passCityList.begin(); itor_vec!=passCityList.end(); itor_vec++){//每两个途经城市生成一段最少金钱路径并复制给当前策略的链表
            if(itor_vec==passCityList.begin()){//当结点为起点时当前路段起始城市为起始城市
                mapPointer=new Map;
                tempPointer = mapPointer->LeastMoney(startCity, itor_vec->name, str1_endTime, str1_timeSum);
                delete mapPointer;
                std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str1));//复制路径到最少金钱策略的路线链表
                str1_endTime=(str1_endTime+itor_vec->stayTime)%24;//当前终止时间增加
                str1_timeSum+=itor_vec->stayTime;//时间消耗加上停留时间
            }
            else{//当结点不为起点时当前路段起始城市为上一个终止城市
                mapPointer=new Map;
                tempPointer = mapPointer->LeastMoney(itor_vec_last->name, itor_vec->name, str1_endTime, str1_timeSum);
                delete mapPointer;
                std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str1));//复制路径到最少金钱策略的路线链表
                str1_endTime=(str1_endTime+itor_vec->stayTime)%24;//当前终止时间增加
                str1_timeSum+=itor_vec->stayTime;//时间消耗加上停留时间
            }
            itor_vec_last=itor_vec;
        }

        mapPointer=new Map;
        tempPointer = mapPointer->LeastMoney(itor_vec_last->name, endCity, str1_endTime, str1_timeSum);
        delete mapPointer;
        std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str1));
    }

    for(itor_list=listPath_str1.begin(); itor_list!=listPath_str1.end(); itor_list++, count++){//逐个结点打印路径信息
        str1_moneyConsum+=itor_list->moneyConsum;//金钱消耗逐个结点增加
        ShowLeastMoney(count, CityIntToString(itor_list->begin), CityIntToString(itor_list->end), itor_list->No, itor_list->startTime, itor_list->endTime, itor_list->moneyConsum);
    }
}


/*
 * 函数名称：ChooseWayDialog::GetLeastTime
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来获取最少时间策略的生成路线，被SetTable调用。
 */


void ChooseWayDialog::GetLeastTime(){
    str2_endTime=currentTime;

    Map * mapPointer;//生成新的Map类
    std::list<PassCityInfo>::iterator itor_vec;
    std::list<PassCityInfo>::iterator itor_vec_last;
    std::list<TravelCityInfo>::iterator itor_list;
    std::list<TravelCityInfo> * tempPointer;

    listPath_str2.clear();//初始化路径链表

    str2_timeSum=0;
    str2_moneyConsum=0;
    int count = 0;

    if(passCityList.empty()){//途经城市链表为空时
        mapPointer=new Map;
        tempPointer = mapPointer->LeastTime(startCity, endCity, str2_endTime, str2_timeSum);//路径即为从起点直接到终点
        delete mapPointer;
        std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str2));//复制生成的路径链表到最少金钱策略路径链表中
    }

    else{
        for(itor_vec=passCityList.begin(); itor_vec!=passCityList.end(); itor_vec++){//每两个途经城市生成一段最短时间路径并复制给当前策略的链表
            if(itor_vec==passCityList.begin()){//当结点为起点时当前路段起始城市为起始城市
                mapPointer=new Map;

                tempPointer = mapPointer->LeastTime(startCity, itor_vec->name, str2_endTime, str2_timeSum);
                delete mapPointer;
                std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str2));//复制路径到最少时间策略的路线链表
                str2_endTime=(str2_endTime+itor_vec->stayTime)%24;//当前终止时间增加
                str2_timeSum+=itor_vec->stayTime;//时间消耗加上停留时间
            }
            else{//当结点不为起点时当前路段起始城市为上一个终止城市
                mapPointer=new Map;
                tempPointer = mapPointer->LeastTime(itor_vec_last->name, itor_vec->name, str2_endTime, str2_timeSum);
                delete mapPointer;
                std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str2));//复制路径到最少时间策略的路线链表
                str2_endTime=(str2_endTime+itor_vec->stayTime)%24;//当前终止时间增加
                str2_timeSum+=itor_vec->stayTime;//时间消耗加上停留时间
            }
            itor_vec_last=itor_vec;
        }

        mapPointer=new Map;
        tempPointer = mapPointer->LeastTime(itor_vec_last->name, endCity, str2_endTime, str2_timeSum);
        delete mapPointer;
        std::copy(tempPointer->begin(), tempPointer->end(), std::back_inserter(listPath_str2));
    }
    for(itor_list=listPath_str2.begin(); itor_list!=listPath_str2.end(); itor_list++, count++){//逐个结点打印路径信息
        str2_moneyConsum+=itor_list->moneyConsum;//金钱消耗逐个结点增加
        ShowLeastTime(count, CityIntToString(itor_list->begin), CityIntToString(itor_list->end), itor_list->No, itor_list->startTime, itor_list->endTime, itor_list->moneyConsum);
    }
}

/*
 * 函数名称：ChooseWayDialog::GetLimitTime
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来获取限时最少金钱策略的生成路线，被SetTable调用。
 */

void ChooseWayDialog::GetLimitTime(){
    Map * mapPointer;
    mapPointer=new Map;//创建新的Map类

    mapPointer->setUpperBound=upperBound;//将上限赋值给Map
    mapPointer->LimitTime(startCity, endCity, currentTime, passCityList, upperBound);//调用生成限时策略路线的函数

    std::list<TravelCityInfo>::iterator itor_list;//路线链表结构
    int count=0;
    for(itor_list=mapPointer->nowPathLeast.begin(); itor_list!=mapPointer->nowPathLeast.end(); itor_list++, count++){//逐个结点打印路线信息
        ShowLimitTime(count, CityIntToString(itor_list->begin), CityIntToString(itor_list->end), itor_list->No, itor_list->startTime, itor_list->endTime, itor_list->moneyConsum);
    }
    str3_moneyConsum=mapPointer->nowMoneyLeast;//将路线的金钱消耗和时间消耗赋值给当前对象的成员变量
    str3_timeSum=mapPointer->nowTimeSum;//复制时间到限时最少金钱策略的时间消耗
    this->listPath_str3.clear();
    std::copy(mapPointer->nowPathLeast.begin(), mapPointer->nowPathLeast.end(), std::back_inserter(listPath_str3));//拷贝生成的路线到当前对象的路线链表里
    delete mapPointer;
}

/*
 * 函数名称：ChooseWayDialog::ShowLeastMoney
 * 参数列表说明：函数接收七个参数：num为表格行数，from和to分别为起始城市
 *         和终止城市；no为交通工具班次号；start和end分别为起始时间和终止时间；
 *         consume为此段路程金钱消耗。
 * 返回值：无
 * 功能说明：该函数用来打印限时最少金钱策略路线，被GetLeastMoney调用。
 */

void ChooseWayDialog::ShowLeastMoney(int num,QString from,QString to,QString no,int start,int end,int consume)
{
    ui->tableWidget_leastMoney->setRowCount(num+1);//行数+1

    QTableWidgetItem * item;

    for(int i=0; i<6; i++){
        item=ui->tableWidget_leastMoney->item(num, i);//逐行打印
        if(!item){
            item=new QTableWidgetItem;//创建item
            ui->tableWidget_leastMoney->setItem(num, i, item);
        }
        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
        if(i==0) item->setText(from);//打印路线
        else if(i==1) item->setText(to);
        else if(i==2) item->setText(no);
        else if(i==3) item->setText(QString::number(start));
        else if(i==4) item->setText(QString::number(end));
        else if(i==5) item->setText(QString::number(consume));
        else{qDebug()<<"ChooseWayDailog::ShowLeastMoney出错，i值错误";}
    }
}

/*
 * 函数名称：ChooseWayDialog::ShowLeastTime
 * 参数列表说明：函数接收七个参数：num为表格行数，from和to分别为起始城市
 *         和终止城市；no为交通工具班次号；start和end分别为起始时间和终止时间；
 *         consume为此段路程金钱消耗。
 * 返回值：无
 * 功能说明：该函数用来打印限时最少时间策略路线，被GetLeastTime调用。
 */

void ChooseWayDialog::ShowLeastTime(int num,QString from,QString to,QString no,int start,int end,int consume)
{
    ui->tableWidget_leastTime->setRowCount(num+1);//行数+1

    QTableWidgetItem * item;

    for(int i=0; i<6; i++){//逐行打印
        item=ui->tableWidget_leastTime->item(num, i);
        if(!item){
            item=new QTableWidgetItem;//创建item
            ui->tableWidget_leastTime->setItem(num, i, item);
        }
        item->setFlags(item->flags()&(~Qt::ItemIsEditable));
        if(i==0) item->setText(from);//打印路线
        else if(i==1) item->setText(to);
        else if(i==2) item->setText(no);
        else if(i==3) item->setText(QString::number(start));
        else if(i==4) item->setText(QString::number(end));
        else if(i==5) item->setText(QString::number(consume));
        else{qDebug()<<"ChooseWayDailog::ShowLeastTime出错，i值错误";}
    }
}

/*
 * 函数名称：ChooseWayDialog::ShowLimitTime
 * 参数列表说明：函数接收七个参数：num为表格行数，from和to分别为起始城市
 *         和终止城市；no为交通工具班次号；start和end分别为起始时间和终止时间；
 *         consume为此段路程金钱消耗。
 * 返回值：无
 * 功能说明：该函数用来打印限时最少金钱策略路线，被GetLimitTime,SetTable调用。
 */

void ChooseWayDialog::ShowLimitTime(int num,QString from,QString to,QString no,int start,int end,int consume)
{
    ui->tableWidget_limitTime->setRowCount(num+1);//行数+1

    QTableWidgetItem * item;

    for(int i=0; i<6; i++){
        item=ui->tableWidget_limitTime->item(num, i);//逐行创建item
        if(!item){
            item=new QTableWidgetItem;
            ui->tableWidget_limitTime->setItem(num, i, item);
        }
        item->setFlags(item->flags()&(~Qt::ItemIsEditable));//打印路线
        if(i==0) item->setText(from);
        else if(i==1) item->setText(to);
        else if(i==2) item->setText(no);
        else if(i==3) item->setText(QString::number(start));
        else if(i==4) item->setText(QString::number(end));
        else if(i==5) item->setText(QString::number(consume));
        else{qDebug()<<"ChooseWayDailog::ShowLimitTime出错，i值错误";}
    }
}

/*
 * 函数名称：ChooseWayDialog::CityIntToString
 * 参数列表说明：函数接收一个参数：cityInt为转换的城市名称
 * 返回值：函数返回一个QString字符串
 * 功能说明：该函数用来实现Cities到QString的转化，被GetLeastMoney,GetLeastTime,GetLimitTime,SetTable调用。
 */

QString ChooseWayDialog::CityIntToString(Cities cityInt){
    if(cityInt==Baotou) return "包头";
    else if(cityInt==Huhehaote) return "呼和浩特";
    else if(cityInt==Tongliao) return "通辽";
    else if(cityInt==Beijing) return "北京";
    else if(cityInt==Tianjin) return "天津";
    else if(cityInt==Taiyuan) return "太原";
    else if(cityInt==Changzhou) return "常州";
    else if(cityInt==Shanghai) return "上海";
    else if(cityInt==Hangzhou) return "杭州";
    else if(cityInt==Ningbo) return "宁波";
    else if(cityInt==Wenzhou) return "温州";
    else if(cityInt==Lishui) return "丽水";
    else if(cityInt==Chongqing) return "重庆";
    else if(cityInt==Kunming) return "昆明";
    else if(cityInt==Panzhihua) return "攀枝花";
    else if(cityInt==Xianggelila) return "香格里拉";
    else if(cityInt==Lijiang) return "丽江";
    else if(cityInt==Erhai) return "洱海";
    else if(cityInt==Dali) return "大理";
    else if(cityInt==Xishuangbanna) return "西双版纳";
    else{
        qDebug()<<"FillTimeDialog::CityIntToString中出错";
    }
    return "";
}

/*
 * 函数名称：ChooseWayDialog::CityToNumString
 * 参数列表说明：函数接收一个参数：city为转换的城市名称
 * 返回值：函数返回一个QString字符串
 * 功能说明：该函数用来实现Cities到QString的转化，被FillInfo调用。
 */

QString ChooseWayDialog::CityToNumString(Cities city){
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
        qDebug()<<"FillTimeDialog::CityToNumString中出错";
    }
    return "";
}

/*
 * 函数名称：ChooseWayDialog::~ChooseWayDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

ChooseWayDialog::~ChooseWayDialog()
{
    delete ui;
}

/*
 * 函数名称：ChooseWayDialog::logPrint
 * 参数列表说明：函数接收一个参数：str为事件内容。
 * 返回值：无
 * 功能说明：该函数用来向数据库加入日志，被FillInfo调用。
 */
void ChooseWayDialog::logPrint(QString str){
    QSqlQuery query;
    QDateTime temp=QDateTime::fromString("2016/01/01 00:00:00",TimeFormat);//获取当前时间
    temp=temp.addSecs(qint64(now));
    bool test = true;
    test = query.prepare("INSERT INTO log(time, strEvent) VALUES( :time, :strEvent)");//将日志信息写入数据库
    if (test){
        query.bindValue(":time", temp.toString(TimeFormat));
        query.bindValue(":strEvent", str);
        test = query.exec();
    }
}
