/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：database.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了MainWindow类中的部分成员函数，数据库的建立连接和添加内容。
 *
 * 修改日志：
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件。
 */

/*包含头文件*/

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QWidget>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * 函数名称：MainWindow::CreateConnection
 * 参数列表说明：该函数接收一个参数isExist，为数据库文件是否存在的布尔值
 * 返回值：无
 * 功能说明：该函数用来连接数据库。
 */

void MainWindow::CreateConnection(bool isExist){
    if(db.open() == false){//数据库打开失败
        QMessageBox::critical(0,QObject::tr("数据库错误"),db.lastError().text());
        return;
    }
    QSqlQuery query;
    if(isExist == false){//数据库第一次建立
        //travellerInfo表示旅客信息
        //log表示日志信息

        query.exec("CREATE TABLE log ("
                   "seqNum INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "time NVARCHAR,"
                   "strEvent NVARCHAR)"
                    );
        query.exec("CREATE TABLE travellerInfo ("
                   "seqNum INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name NVARCHAR,"
                   "identNum NVARCHAR,"
                   "nowStatus INT,"
                   "startCity INT,"
                   "endCity INT"
                   "moneyConsum INT,"
                   "timeConsum INT)"
                   );
        query.exec("CREATE TABLE timeTable("
                   "seqNum INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "method INT,"
                   "startCity INT,"
                   "endCity INT,"
                   "No NVARCHAR,"
                   "startTime INT,"
                   "endTime INT,"
                   "moneyConsum INT)"
                    );
        SetTimeTable();
        InitSQL();
    }
}

/*
 * 函数名称：MainWindow::SetTimeTable
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来向数据库添加交通工具的时刻信息。
 */

void MainWindow::SetTimeTable(){
    QSqlQuery query;
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 7, 'CZ6412', 6, 8, 3470)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 7, 'H01252', 7, 9, 1240)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 7, 'SC1557', 12, 14, 2000)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 7, 'CZ9247', 14, 16, 1240)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 7, 'MU5116', 15, 17, 1230)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 4, 'KN2251', 19, 20, 780)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 4, 'GS7906', 17, 18, 780)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 12, 'CA1427', 7, 10, 1250)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 12, 'ZH1429', 9, 12, 1215)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 12, 'SC4130', 12, 15, 1140)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 12, 'MF1137', 15, 18, 1640)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 12, 'SC4142', 18, 21, 900)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 2, 'KN2917', 7, 10, 550)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 2, 'CA1123', 15, 18, 770)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 8, 'FM9158', 7, 9, 1020)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 8, 'SC1704', 12, 14, 1036)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 8, 'ZH1706', 19, 21, 840)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 5, 'ZH1145', 7, 8, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 5, 'CZ9347', 16, 18, 1000)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 6, 'CA1825', 17, 19, 1650)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 6, 'CZ9186', 22, 23, 840)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 13, 'KY8224', 6, 10, 2400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 13, '3U8723', 7, 11, 1400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 13, 'MU5714', 12, 16, 1600)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 1, 'ZH1103', 6, 7, 600)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 3, 1, 'CA1111', 19, 20, 540)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 7, 3, 'KN5988', 7, 9, 700)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 7, 3, 'CZ9262', 9, 11, 1240)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 7, 3, 'MU5117', 16, 18, 620)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 7, 6, 'MU9421', 8, 11, 1060)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 7, 6, 'CZ9425', 15, 18, 780)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 7, 6, '3U8974', 18, 21, 650)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 7, 8, 'MU2254', 13, 14, 580)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 3, 'SC1155', 7, 10, 800)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 3, 'SC1432', 12, 15, 1160)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 7, 'SC4949', 7, 10, 1400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 7, 'TV6603', 17, 20, 1000)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 5, 'G52687', 7, 10, 600)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 13, 'PN6215', 7, 8, 360)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 13, 'MU2995', 21, 22, 870)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 8, 'CA4553', 8, 11, 580)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 12, 8, 'CA1762', 20, 23, 550)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 2, 3, 'KN2918', 10, 11, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 2, 3, 'CA1124', 20, 21, 600)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 8, 3, 'ZH1701', 7, 9, 780)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 8, 3, 'CA1596', 12, 14, 950)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 8, 12, '3U8165', 7, 10, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 8, 12, 'GJ8691', 18, 21, 1500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 8, 7, 'GJ8849', 12, 13, 580)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 5, 3, 'MU5291', 8, 9, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 5, 3, 'MU5297', 15, 16, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 5, 12, 'G52688', 10, 13, 580)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 6, 3, 'MU2761', 7, 9, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 6, 3, 'CA1826', 20, 22, 1600)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 13, 3, 'CA4171', 7, 10, 820)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 13, 3, 'HU7212', 13, 16, 1200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 13, 12, 'KY8295', 7, 8, 320)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 13, 12, 'CZ8158', 22, 23, 450)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 1, 3, 'ZH1102', 7, 8, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(0, 1, 3, 'ZH1112', 22, 23, 550)");


    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 2, 'K0011', 8, 11, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 2, 'K0012', 10, 13, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 5, 'K0021', 7, 10, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 5, 'K0022', 10, 13, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 5, 'K0031', 19, 22, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 5, 'K0032', 17, 20, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 4, 'K0033', 13, 15, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 4, 'K0034', 11, 13, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 8, 'K0041', 18, 22, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 8, 'K0042', 16, 20, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 13, 'K0043', 11, 17, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 13, 'K0044', 9, 15, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 1, 'K0051', 17, 21, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 1, 'K0052', 13, 17, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 6, 'K0053', 12, 17, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 3, 6, 'K0054', 8, 13, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 2, 1, 'K0011', 11, 12, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 2, 1, 'K0012', 13, 14, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 2, 3, 'K0013', 17, 20, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 2, 3, 'K0014', 19, 22, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 0, 'K0011', 12, 13, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 0, 'K0012', 14, 15, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 2, 'K0013', 16, 17, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 2, 'K0014', 18, 19, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 0, 'K0051', 21, 22, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 0, 'K0052', 17, 18, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 3, 'K0053', 8, 12, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 1, 3, 'K0054', 4, 8, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 0, 13, 'K0011', 13, 19, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 0, 13, 'K0012', 15, 21, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 0, 1, 'K0013', 15, 16, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 0, 1, 'K0014', 17, 18, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 0, 1, 'K0053', 7, 8, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 0, 1, 'K0054', 3, 4, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 19, 'K0011', 19, 20, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 19, 'K0012', 21, 22, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 0, 'K0013', 9, 15, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 0, 'K0014', 11, 17, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 16, 'K0021', 18, 19, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 16, 'K0022', 21, 22, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 12, 'K0023', 9, 12, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 12, 'K0024', 12, 15, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 3, 'K0041', 12, 18, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 3, 'K0042', 10, 16, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 14, 'K0043', 17, 20, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 13, 14, 'K0044', 15, 18, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 19, 13, 'K0013', 8, 9, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 19, 13, 'K0014', 10, 11, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 12, 'K0021', 10, 15, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 12, 'K0022', 13, 18, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 3, 'K0023', 17, 20, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 3, 'K0024', 20, 23, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 12, 'K0031', 22, 23, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 12, 'K0032', 20, 22, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 3, 'K0033', 10, 13, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 5, 3, 'K0034', 8, 11, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 12, 13, 'K0021', 15, 18, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 12, 13, 'K0022', 18, 21, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 12, 5, 'K0023', 12, 17, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 12, 5, 'K0024', 15, 20, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 12, 5, 'K0033', 8, 10, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 12, 5, 'K0034', 6, 8, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 15, 'K0021', 19, 20, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 15, 'K0022', 22, 23, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 13, 'K0023', 8, 9, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 13, 'K0024', 11, 12, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 14, 'K0041', 7, 9, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 14, 'K0042', 5, 7, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 18, 'K0043', 22, 23, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 16, 18, 'K0044', 20, 21, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 15, 16, 'K0023', 7, 8, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 15, 16, 'K0024', 10, 11, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 10, 7, 'K0031', 8, 10, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 10, 7, 'K0032', 6, 8, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 6, 'K0031', 10, 12, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 6, 'K0032', 8, 10, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 10, 'K0033', 22, 23, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 10, 'K0034', 20, 22, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 6, 'K0051', 10, 12, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 6, 'K0052', 6, 8, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 8, 'K0053', 19, 21, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 7, 8, 'K0054', 15, 17, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 4, 'K0031', 12, 17, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 4, 'K0032', 10, 15, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 7, 'K0033', 20, 22, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 7, 'K0034', 18, 20, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 3, 'K0051', 12, 17, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 3, 'K0052', 8, 13, 500)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 7, 'K0053', 17, 19, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 6, 7, 'K0054', 13, 15, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 4, 3, 'K0031', 17, 19, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 4, 3, 'K0032', 15, 17, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 4, 6, 'K0033', 15, 20, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 4, 6, 'K0034', 13, 18, 400)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 18, 16, 'K0041', 6, 7, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 18, 16, 'K0042', 4, 5, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 14, 13, 'K0041', 9, 12, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 14, 13, 'K0042', 7, 10, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 14, 16, 'K0043', 20, 22, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 14, 16, 'K0044', 18, 20, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 11, 'K0041', 22, 23, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 11, 'K0042', 20, 21, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 3, 'K0043', 7, 11, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 3, 'K0044', 5, 9, 300)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 7, 'K0051', 8, 10, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 7, 'K0052', 4, 6, 200)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 9, 'K0053', 21, 22, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 8, 9, 'K0054', 17, 18, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 11, 8, 'K0043', 6, 7, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 11, 8, 'K0044', 4, 5, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 9, 8, 'K0051', 7, 8, 100)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(1, 9, 8, 'K0052', 3, 4, 100)");


    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 18, 17, '011', 8, 12, 20)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 18, 17, '012', 13, 17, 20)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 17, 16, '011', 12, 17, 25)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 17, 16, '012', 17, 22, 25)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 17, 18, '013', 13, 17, 20)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 17, 18, '014', 18, 22, 20)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 17, 18, '033', 10, 14, 30)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 17, 18, '034', 13, 17, 30)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 16, 17, '013', 8, 13, 25)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 16, 17, '014', 13, 18, 25)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 16, 19, '021', 9, 16, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 16, 19, '022', 13, 20, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 15, 16, '023', 9, 16, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 15, 16, '024', 13, 20, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 18, 17, '031', 10, 14, 30)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 18, 17, '032', 13, 17, 30)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 18, 19, '101', 9, 13, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 18, 19, '102', 11, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 19, 13, '041', 7, 17, 80)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 19, 13, '042', 10, 20, 80)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 19, 18, '103', 9, 13, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 19, 18, '104', 11, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 13, 19, '043', 7, 17, 80)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 13, 19, '044', 10, 20, 80)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 0, 1, '051', 8, 12, 50)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 0, 1, '052', 12, 16, 50)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 1, 0, '053', 8, 12, 50)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 1, 0, '054', 12, 16, 50)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 3, 4, '061', 7, 11, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 3, 4, '062', 10, 14, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 4, 3, '063', 7, 10, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 4, 3, '064', 10, 14, 70)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 11, 8, '071', 9, 13, 50)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 11, 8, '072', 12, 16, 50)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 8, 11, '073', 9, 12, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 8, 11, '074', 12, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 8, 10, '113', 8, 12, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 8, 10, '114', 11, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 7, 6, '081', 9, 12, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 7, 6, '082', 12, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 7, 9, '093', 8, 12, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 7, 9, '094', 11, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 6, 7, '083', 9, 12, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 6, 7, '084', 12, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 9, 7, '091', 8, 12, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 9, 7, '092', 11, 15, 40)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 10, 8, '111', 8, 14, 50)");
    query.exec("INSERT INTO timeTable(method, startCity, endCity, No, startTime, endTime, moneyConsum)"
               "VALUES(2, 10, 8, '112', 10, 16, 50)");

}


/*
 * 函数名称：MainWindow::InitSQL
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：该函数用来初始化。
 */

void MainWindow::InitSQL(){//尚不知道要初始化啥

}
