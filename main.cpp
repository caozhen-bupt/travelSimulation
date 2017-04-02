/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：main.cpp
 * 版本号：2.0
 * 内容及功能说明：工程主函数。
 *
 * 修改日志：
 *  2016.6.4  李一鸣 修改了该文件，修改了欢迎界面停留时间函数。
 *  2016.5.22 曹桢 修改了该文件，添加了欢迎界面的文字。
 *  2016.5.20 戴唯 修改了该文件，添加了欢迎界面和应用程序标题和图标。
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数。
 */

/*包含头文件*/

#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>
#include <QPushButton>

//除了main.cpp外，所有的#include<> 写在""头文件（自定义头文件）中
//除了const等修饰的变量／常量外，其余变量的命名均已小写字母开头（若有单词组合，之后的单词首字母大写，如nowFormat），函数名用大写字母开头

QApplication * temp;//为了通过button退出程序，而声明的
int now;//计时器使用

/*
 * 函数名称：main
 * 参数列表说明：
 * 返回值：1
 * 功能说明：工程主函数。
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    temp = &a;
    QSplashScreen *splash =new QSplashScreen;//创建新的QSplashScreen用于播放欢迎界面
    splash->setPixmap(QPixmap(":/image/image/welcome.jpg"));//欢迎界面图片路径
    splash->show();

    a.processEvents();

    Qt::Alignment botCenter = Qt::AlignBottom|Qt::AlignHCenter;//欢迎界面文字格式设置
    splash->showMessage(QObject::tr("loading..."), botCenter, Qt::blue);

    QDateTime n=QDateTime::currentDateTime();
    QDateTime temp;
    while(n.secsTo(temp)<=3){//欢迎界面停留时间
        temp=QDateTime::currentDateTime();
    }

    MainWindow w;//创建新的MainWindow
    w.show();

    a.setWindowIcon(QIcon(":/icon/icon/earth.png"));//修改应用程序图标
    splash->finish(&w);//关闭欢迎界面
    delete splash;

    return a.exec();
}



