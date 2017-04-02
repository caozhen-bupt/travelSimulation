/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：datastructure.h
 * 版本号：2.0
 * 内容及功能说明：该头文件中声明了在工程中所有的常量、枚举变量和数据结构。
 * 修改日志：
 *  2016.6.4 曹桢 修改了注释
 *  2016.6.4 戴唯 完善了注释。
 *  2016.5.15 李一鸣 创建了该文件，定义了类的部分内容。
 */


#ifndef DATASTRUCTURE
#define DATASTRUCTURE

/*包含头文件*/

#include <QApplication>

const unsigned int CitiesAmount = 20;//城市数量20个
const unsigned int MapNodeAmount = 20;//地图点数量20个
const unsigned int MapEdgeAmount = 31;//地图边数量31条
const unsigned int TransportationAmount = 3;//交通方式3种

const unsigned int TrigFrequency = 50;//计数器触发频率

const QString DBFileName = "database.db";
const QString BackupFileName = "dbbackup.db";
const QString IniFileName = "travelsimulation.ini";

const QString TimeFormat = "yyyy/MM/dd hh:mm:ss";//时间格式

const unsigned int MoneyEachJump = 20;//每一跳的代价估值
const unsigned int TimeEachJump = 1;//每一跳的时间估值

#define Infinity 0xffff//定义无穷大


const unsigned int jump[CitiesAmount][CitiesAmount]={
    { 0, 1, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 2, 1, 2, 3, 2, 3, 3, 2},
    { 1, 0, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 3, 4, 3, 4, 4, 3},
    { 2, 1, 0, 1, 2, 2, 2, 2, 2, 3, 3, 3, 2, 2, 3, 4, 3, 4, 4, 3},
    { 2, 1, 1, 0, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 3, 2, 3, 3, 2},
    { 3, 2, 2, 1, 0, 2, 1, 2, 2, 3, 3, 3, 2, 2, 3, 4, 3, 4, 4, 3},
    { 3, 2, 2, 1, 2, 0, 1, 2, 2, 3, 3, 3, 1, 2, 3, 4, 3, 4, 4, 3},
    { 3, 2, 2, 1, 1, 1, 0, 1, 2, 2, 2, 3, 2, 2, 3, 4, 3, 4, 4, 3},
    { 3, 2, 2, 1, 2, 2, 1, 0, 1, 1, 1, 2, 1, 2, 3, 4, 3, 4, 4, 3},
    { 3, 2, 2, 1, 2, 2, 2, 1, 0, 1, 1, 1, 1, 2, 3, 4, 3, 4, 4, 3},
    { 4, 3, 3, 2, 3, 3, 2, 1, 1, 0, 2, 2, 2, 3, 4, 5, 4, 5, 5, 4},
    { 4, 3, 3, 2, 3, 3, 2, 1, 1, 2, 0, 2, 2, 3, 4, 5, 4, 5, 5, 4},
    { 4, 3, 3, 2, 3, 3, 3, 2, 1, 2, 2, 0, 2, 3, 4, 5, 4, 5, 5, 4},
    { 2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 2, 2, 0, 1, 2, 3, 2, 3, 3, 2},
    { 1, 2, 2, 1, 2, 2, 2, 2, 2, 3, 3, 3, 1, 0, 1, 2, 1, 2, 2, 1},
    { 2, 3, 3, 2, 3, 3, 3, 3, 3, 4, 4, 4, 2, 1, 0, 2, 1, 2, 2, 2},
    { 3, 4, 4, 3, 4, 4, 4, 4, 4, 5, 5, 5, 3, 2, 2, 0, 1, 2, 2, 3},
    { 2, 3, 3, 2, 3, 3, 3, 3, 3, 4, 4, 4, 2, 1, 1, 1, 0, 1, 1, 2},
    { 3, 4, 4, 3, 4, 4, 4, 4, 4, 5, 5, 5, 3, 2, 2, 2, 1, 0, 1, 2},
    { 3, 4, 4, 3, 4, 4, 4, 4, 4, 5, 5, 5, 3, 2, 2, 2, 1, 1, 0, 1},
    { 2, 3, 3, 2, 3, 3, 3, 3, 3, 4, 4, 4, 2, 1, 2, 3, 2, 2, 1, 0}
};

enum Transportation{//旅行方式
    plane,//飞机
    train,//火车
    coach//汽车
};

enum TravelStatus{//旅客旅行状态
    waiting,//等待出发
    traveling,//在旅途中
    staying,//某城市停留
    finished//完成旅行
};

enum Cities{//20 cities
    Baotou,
    Huhehaote,
    Tongliao,
    Beijing,
    Tianjin,
    Taiyuan,
    Changzhou,
    Shanghai,
    Hangzhou,
    Ningbo,
    Wenzhou,
    Lishui,
    Chongqing,
    Kunming,
    Panzhihua,
    Xianggelila,
    Lijiang,
    Erhai,
    Dali,
    Xishuangbanna,
    unknown
};

enum dbLogItem{//日志信息选项
    seqNum_dbLog,//旅客号
    time_dbLog,//时间
    strEvent,//事件
};

enum dbTravellerInfoItem{//旅客信息选项
    seqNum_dbTraInfo,//旅客号
    name,//姓名
    identNum,//身份证号
    nowStatus,//当前状态
    startCity,//起始城市
    endCity,//终止城市
    moneyConsum,//金钱消耗
    timeConsum//时间消耗
};

enum CityChoose{//城市选项
    start,//起始城市
    end,//终止城市
    pass,//途经城市
    init//初始化
};

enum Strategy{//策略选项
    leasttime,//最短时间
    leastmoney,//最少金钱
    limittime//限时最少金钱
};

typedef struct TimeTable{//时间表选项
    Cities start;//起始城市
    Cities end;//终止城市
    QString number;//城市序号
    int startTime;//开始时间
    int endTime;//结束时间
    int timeConsum;//时间消耗
    int moneyConsum;//金钱消耗
}TimeTable;

typedef struct CityNode{
    Cities name;//该城市的名字
    unsigned int adjCities;//邻接城市信息，压缩存储
    Cities from;//城市指针
    int F, G, H;//估价
    int method;//到达该城市的方式
    QString No;//达到该城市所乘工具的班次号
    int startTime;//该趟车的出发时间（0-24）
    int endTime;//该趟车的到达时间（0-24）
    int moneyConsum;//该趟车的金钱消耗
    int timeConsum;//该趟车的耗时，包括在上一城市的等待时间
    int timeSum;//到达该城市的总耗时，包括在上一城市的等待时间(起点包括，终点不包括)
    int currentTime;//到达该城市的时间点(0-24)

    bool operator <(const CityNode &a) const{
        if(F!=a.F)
            return F<a.F;
        else
            return timeConsum<a.timeConsum;
    }

}CityNode;

typedef struct {//旅行路线（节点），游客使用
    Cities begin;//出发城市
    Cities end;//结束城市
    QString No;//班次
    int tran;//旅行工具
    int startTime;//开始时间
    int endTime;//结束时间
    int moneyConsum;//耗费金钱
    int timeConsum;//耗费时间


}TravelCityInfo;

typedef struct{//途经城市
    Cities name;//城市名
    int stayTime;//停留时间
}PassCityInfo;

typedef struct{//城市信息
    Cities name;//城市名
    unsigned int adjCities;//相邻城市数量
    unsigned int notPassed;//不经过城市数量
}CityInfo;

#endif // DATASTRUCTURE
