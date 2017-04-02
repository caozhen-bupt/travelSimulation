/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：filltimedialog.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了FillTimeDialog类中，各成员函数的实现，用于
 *         获取并记录途经城市的停留时间，在filltimedialog.cpp使用这些定义的
 *         函数。
 *
 * 修改日志：
 *  2016.6.4  戴唯 为该文件完善了注释
 *  2016.5.24 戴唯 修改了该文件。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数
 */

/*包含头文件*/

#include "filltimedialog.h"
#include "ui_filltimedialog.h"
#include "choosewaydialog.h"
#include "ui_choosewaydialog.h"

/*
 * 函数名称：FillTimeDialog::FillTimeDialog
 * 参数列表说明：函数接收其父窗口为参数
 * 返回值：无
 * 功能说明：该函数为构造函数，进行相应的初始化。
 */

FillTimeDialog::FillTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FillTimeDialog)
{
    ui->setupUi(this);
    seqNumnext=0;//初始化操作
    this->passCityList.clear();
    this->traveller=NULL;
    passCityList.clear();

    ui->lineEdit->setEnabled(false);

    upperBound=-1;
    change=false;

    connect(ui->yep,SIGNAL(clicked()),this,SLOT(ChooseWay()));//连接确认点击信号与ChooseWay槽函数
    connect(ui->cancel,SIGNAL(clicked()),this,SLOT(close()));//连接取消点击信号与close槽函数
}

/*
 * 函数名称：FillTimeDialog::ChooseWay
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来生成路线，被FillTimeDialog调用。
 */

void FillTimeDialog::ChooseWay(){
    if(infoCompleted()){//若填写信息完整
        ChooseWayDialog * choosewayDialog = new ChooseWayDialog(this);//创建新的ChooseWayDialog类，并将其中的部分成员变量赋值

        choosewayDialog->startCity=this->startCity;
        choosewayDialog->endCity=this->endCity;
        choosewayDialog->passCityList = this->passCityList;
        choosewayDialog->currentTime=this->currentTime;
        choosewayDialog->change=this->change;
        if(change){//若为更改过程则直接将旅客身份信息赋值给新的ChooseWayDialog
            choosewayDialog->namenext=this->namenext;
            choosewayDialog->identNumnext=this->identNumnext;

            choosewayDialog->seqNumnext=this->seqNumnext;
            qDebug()<<"seqnUmNExtinfilltime"<<choosewayDialog->seqNumnext;
        }
        else{
            choosewayDialog->seqNum=this->seqNum;
        }
        //if(upperBound>=0)//若时间上限有效则赋时间上限到新的ChooseWayDialog中
        choosewayDialog->upperBound=this->upperBound;
        choosewayDialog->SetTable();

        choosewayDialog->exec();
        this->traveller=choosewayDialog->traveller;//将新的ChooseWayDialog的traveller赋值给当前对象的traveller

        this->close();
        delete choosewayDialog;
    }
    else{
        QMessageBox::warning(NULL, "提示","请正确完整地填写所有信息，", QMessageBox::Yes | QMessageBox::Yes);
    }

}

/*
 * 函数名称：FillTimeDialog::infoCompleted
 * 参数列表说明：无
 * 返回值：函数返回信息是否填写完整的布尔值
 * 功能说明：该函数用来判断信息是否填写完整，被ChooseWay调用。
 */

bool FillTimeDialog::infoCompleted(){
    bool ok;

    QTableWidgetItem * item;
    std::list<PassCityInfo>::iterator itor;
    if(!passCityList.empty()){//途经城市链表不为空时
        itor=passCityList.begin();
        for(unsigned int i=0; i<passCityNum && itor!=passCityList.end(); i++){//遍历链表，若没有停留时间信息则报错
            item=ui->tableWidget->item(i,1);
            if(!item){
                qDebug()<<"FillTimeDialog::infoCompleted()出错，item指向NULL";
                return false;
            }
            int temp;
            temp=item->text().toInt(&ok,10);
            if(!ok || temp<0) return false;
            itor->stayTime=temp;
            itor++;
        }
    }

    if(ui->lineEdit->isEnabled()){//若限时输入条有效
        int temp=ui->lineEdit->text().toInt(&ok,10);//获取输入时间
        if(!ok || temp<0) return false;
        upperBound=temp;//将时间上限赋值为输入的时间
    }
    else{
        upperBound=-1;//否则时间上限为-1
    }
    return true;
}

/*
 * 函数名称：FillTimeDialog::SetTable
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来将途经城市以表格方式打印并获取停留时间的输入，被ChooseWay调用。
 */

void FillTimeDialog::SetTable(){
    ui->tableWidget->setColumnCount(2);//设置表格栏数和大小
    ui->tableWidget->setColumnWidth(0,190);
    ui->tableWidget->setColumnWidth(1,190);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"途径城市"<<"停留时间");//设置表头
    if(passCityList.empty()) return ;
    QTableWidgetItem * item;
    ui->tableWidget->setRowCount(this->passCityNum);//表格行数为途经城市数量
    std::list<PassCityInfo>::iterator itor_list;//记录途经城市的链表结构
    unsigned int i = 0;
    for(itor_list=passCityList.begin();itor_list!=passCityList.end();i++, itor_list++){//将停留时间记录进链表中
        item=ui->tableWidget->item(i,0);
        if(item){
            item->setFlags(item->flags()&(~Qt::ItemIsEditable));
        }
        else{
            item = new QTableWidgetItem;
            item->setFlags(item->flags()&(~Qt::ItemIsEditable));
            ui->tableWidget->setItem(i,0,item);
        }
        item->setText(CityIntToString(itor_list->name));
    }
}

/*
 * 函数名称：FillTimeDialog::CityIntToString
 * 参数列表说明：该函数接收一个参数：cityInt为转换的城市名称
 * 返回值：返回城市的中文字符串
 * 功能说明：该函数用来实现从Cities到QString的转化，被SetTable调用。
 */

QString FillTimeDialog::CityIntToString(Cities cityInt){
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
 * 函数名称：FillTimeDialog::~FillTimeDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

FillTimeDialog::~FillTimeDialog()
{
    delete ui;
}

/*
 * 函数名称：FillTimeDialog::on_checkBox_clicked
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来设置限时输入条是否有效。
 */

void FillTimeDialog::on_checkBox_clicked()
{
    if(ui->lineEdit->isEnabled()==false){//不勾选限时选项
        ui->lineEdit->setEnabled(true);
    }
    else if(ui->lineEdit->isEnabled()==true){//勾选限时选项
        ui->lineEdit->setEnabled(false);
    }
}
