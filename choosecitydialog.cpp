/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：map.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了ChooseCityDialog类中，各成员函数的实现，用于进行城市
 *         类别的选择，在choosecitydialog.cpp使用这些定义的函数。
 *
 * 修改日志：
 *  2016.6.4  戴唯 为该文件完善了注释
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数
 */

/*包含头文件*/

#include "choosecitydialog.h"
#include "ui_choosecitydialog.h"

/*
 * 函数名称：ChooseCityDialog::ChooseCityDialog
 * 参数列表说明：函数接收父窗口为参数。
 * 返回值：无
 * 功能说明：该函数为构造函数，进行初始化。
 */

ChooseCityDialog::ChooseCityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseCityDialog)
{
    ui->setupUi(this);//设置窗口属性

    attrSelected=init;//成员变量初始化操作
    change=false;

    btnGroupCity=new QButtonGroup(this);//新建按键群
    if(this->change==true)//若当前操作是更改行程中的操作则没有起点选项
    {
        btnGroupCity->addButton(ui->end,1);
        btnGroupCity->addButton(ui->passing,2);
    }
    else
    {
        btnGroupCity->addButton(ui->start,0);
        btnGroupCity->addButton(ui->end,1);
        btnGroupCity->addButton(ui->passing,2);
    }

    connect(ui->start,SIGNAL(clicked()),this,SLOT(ButtonSelected()));//信号与槽函数的连接
    connect(ui->end,SIGNAL(clicked()),this,SLOT(ButtonSelected()));
    connect(ui->passing,SIGNAL(clicked()),this,SLOT(ButtonSelected()));
}

/*
 * 函数名称：ChooseCityDialog::ButtonSelected
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来确定被选择的类型，被ChooseCityDialog调用。
 */

void ChooseCityDialog::ButtonSelected(){
    if(change){//若正在进行更改操作，起点锁死
        if(btnGroupCity->checkedId()==end){
            attrSelected=end;
        }
        else if(btnGroupCity->checkedId()==pass){
            attrSelected=pass;
        }
        else{
            attrSelected=init;
            qDebug()<<"城市选择出错，ChooseCityDialof::ButtonSelected()";
        }

    }
    else{//进行新增旅客的城市选择操作
        if(btnGroupCity->checkedId()==start){
            attrSelected=start;
        }
        else if(btnGroupCity->checkedId()==end){
            attrSelected=end;
        }
        else if(btnGroupCity->checkedId()==pass){
            attrSelected=pass;
        }
        else{
            attrSelected=init;
            qDebug()<<"城市选择出错，ChooseCityDialof::ButtonSelected()";
        }
    }
}

/*
 * 函数名称：ChooseCityDialog::~ChooseCityDialog
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数为析构函数。
 */

ChooseCityDialog::~ChooseCityDialog()
{
    delete ui;
}

/*
 * 函数名称：ChooseCityDialog::on_yep_clicked
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来确认并关闭窗口。
 */

void ChooseCityDialog::on_yep_clicked()
{
    this->isOK=true;//确认为真
    close();//关闭窗口
}

/*
 * 函数名称：ChooseCityDialog::on_cancel_clicked
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来取消并关闭窗口。
 */

void ChooseCityDialog::on_cancel_clicked()
{
    this->isOK=false;//确认为假
    close();//关闭窗口
}
