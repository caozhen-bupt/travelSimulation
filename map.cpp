/*
 * Created by 李一鸣 on 2016/5/15.
 * Copyright © 2016 李一鸣、戴唯、曹桢. All rights reserved.
 * 文件名：map.cpp
 * 版本号：2.0
 * 内容及功能说明：该源文件中完成了Map类中，各成员函数的实现，用于
 *         寻路模块的计算，在choosewayDialog.cpp使用这些定义的
 *         函数。
 *
 * 修改日志：
 *  2016.6.4  李一鸣 为该文件完善了注释
 *  2016.6.1  李一鸣 去掉了多余的成员变量
 *  2016.5.22 李一鸣 实现了限时最少金钱的定义及相关函数
 *  2016.5.17 李一鸣 实现了最少金钱和最少时间的函数定义，加入了其他相关函数
 *  2016.5.15 李一鸣 创建了该文件，实现了一些辅助函数
 */

/*包含头文件*/

#include "map.h"

/*
 * 函数名称：Map::LeastTime
 * 参数列表说明：函数接收四个参数：startCity和endCity分别为起始城市
 *         和终止城市；currentTime记录出发的最早时间（取值范围0-23），
 *         以引用的方式传递；timeSum记录耗时总和，以引用方式传递。
 * 返回值：函数返回指向已经生成的路径的指针
 * 功能说明：该函数用来实现最少时间策略。
 */

std::list<TravelCityInfo> * Map::LeastTime(Cities startCity, Cities endCity, int &currentTime, int &timeSum){
    Map();//初始化成员变量
    CityNode curCity;//当前城市结点
    CityNode childCity;//当前城市结点的子结点

    std::list<CityNode>::iterator itor_list;//在表中找到起始城市
    for(itor_list=neitherList.begin(); itor_list!=neitherList.end(); itor_list++){
        curCity=*itor_list;
        if(curCity.name == startCity){
            neitherList.erase(itor_list);
            break;
        }
    }

    curCity.H=H_Function_Time(curCity.name, endCity);//算起点的H
    curCity.G=0;
    curCity.F=curCity.G+curCity.H;
    curCity.currentTime=currentTime;//初始化相关值
    curCity.endTime=currentTime;
    curCity.moneyConsum=0;
    curCity.timeConsum=0;
    curCity.timeSum=0;

    openList.push_back(curCity);//将起点放入open

    while(!openList.empty()){//考察openList中的每一个城市结点
        curCity=openList.front();//取出第一个城市
        openList.pop_front();

        if(curCity.name==endCity){//若搜到目标城市
            currentTime=curCity.currentTime;
            closeList.push_back(curCity);
            return MakeWay(startCity, endCity, timeSum);//声称路线
        }

        for(int i=0;i<20;i++){//遍历邻接点
            if((curCity.adjCities & (0X1<<i)) == 0) continue;//如果当前城市与i城市相邻

            if(inClose(i)){//若i城市已添加到Close表中
                continue;
            }

            if(inOpen(i)){//若i在openList中
                for(itor_list=openList.begin(); itor_list!=openList.end() && (*itor_list).name!=i; itor_list++);//在open表中取出城市i
                CityNode temp_city=TwoCityLeastTime(curCity.name, itor_list->name, curCity.currentTime);

                int temp;//算childCity经过curCity的G值
                temp=curCity.G+temp_city.timeConsum;

                if(temp<(*itor_list).G){//若小于原来的G值，更新
                    itor_list->from=curCity.name;
                    itor_list->G=temp;
                    itor_list->F=itor_list->G+itor_list->H;
                    itor_list->method=temp_city.method;
                    itor_list->No=temp_city.No;
                    itor_list->startTime=temp_city.startTime;
                    itor_list->endTime=temp_city.endTime;
                    itor_list->moneyConsum=temp_city.moneyConsum;
                    itor_list->timeConsum=temp_city.timeConsum;
                    itor_list->timeSum+=itor_list->timeConsum;
                    itor_list->currentTime=temp_city.currentTime;
                }
            }

            else{//若不在openList和closeList中
                for(itor_list=neitherList.begin(); itor_list!=neitherList.end(); itor_list++){//在neither表中取出城市i
                    childCity=*itor_list;
                    if(childCity.name == i){
                        neitherList.erase(itor_list);
                        break;
                    }
                }

                childCity.from=curCity.name;
                CityNode temp_city=TwoCityLeastTime(curCity.name, childCity.name, curCity.currentTime);
                childCity.G=curCity.G+temp_city.timeConsum;//修改childCity的G值，等于curCity的G值，加上两个城市之间的代价
                childCity.H=H_Function_Time(childCity.name, endCity);
                childCity.F=childCity.G+childCity.H;
                childCity.method=temp_city.method;
                childCity.No=temp_city.No;
                childCity.startTime=temp_city.startTime;
                childCity.endTime=temp_city.endTime;
                childCity.moneyConsum=temp_city.moneyConsum;
                childCity.timeConsum=temp_city.timeConsum;
                childCity.timeSum+=childCity.timeConsum;
                childCity.currentTime=temp_city.currentTime;

                openList.push_back(childCity);//压入openList连表中
            }
        }

        closeList.push_back(curCity);//将当前考察城市压入closeList中
        openList.sort();//对openList重排序
    }
    return NULL;
}

/*
 * 函数名称：Map::LeastMoney
 * 参数列表说明：函数接收四个参数：startCity和endCity分别为起始城市
 *         和终止城市；currentTime记录出发的最早时间（取值范围0-23），
 *         以引用的方式传递；timeSum记录耗时总和，以引用方式传递。
 * 返回值：函数返回指向已经生成的路径的指针
 * 功能说明：该函数用来实现最少金钱策略。
 */

std::list<TravelCityInfo> * Map::LeastMoney(Cities startCity, Cities endCity, int &currentTime, int &timeSum){
    Map();//初始化
    CityNode curCity;//当前城市
    CityNode childCity;//当前城市的子结点

    std::list<CityNode>::iterator itor_list;//在表中找到起始城市
    for(itor_list=neitherList.begin(); itor_list!=neitherList.end(); itor_list++){
        curCity=*itor_list;
        if(curCity.name == startCity){
            neitherList.erase(itor_list);
            break;
        }
    }

    curCity.H=H_Function_Money(curCity.name, endCity);//算起点的H
    curCity.G=0;
    curCity.F=curCity.G+curCity.H;
    curCity.currentTime=currentTime;
    curCity.endTime=currentTime;
    curCity.moneyConsum=0;
    curCity.timeConsum=0;
    curCity.timeSum=0;

    openList.push_back(curCity);//将起点放入open

    while(!openList.empty()){//考察openList中的结点
        curCity=openList.front();//取出首结点
        openList.pop_front();

        if(curCity.name==endCity){//若找到目标城市
            currentTime=curCity.currentTime;
            closeList.push_back(curCity);
            return MakeWay(startCity, endCity, timeSum);//生成路线
        }
        for(int i=0; i<20; i++){//遍历当前结点的子结点
            if((curCity.adjCities & (0X1<<i)) == 0) continue;//如果当前城市与i城市相邻

            if(inClose(i)){//若i城市已添加到Close表中
                continue;
            }

            if(inOpen(i)){//若城市i在openList中
                for(itor_list=openList.begin(); itor_list!=openList.end() && (*itor_list).name!=i; itor_list++);//在open表中取出城市i
                CityNode temp_city=TwoCityLeastMoney(curCity.name, itor_list->name);

                int temp;//算childCity经过curCity的G值
                temp=curCity.G+temp_city.moneyConsum;
                if(temp<(*itor_list).G){//若小于openList中的G值，更新
                    itor_list->from=curCity.name;
                    itor_list->G=temp;
                    itor_list->F=itor_list->G+itor_list->H;
                    itor_list->method=temp_city.method;
                    itor_list->No=temp_city.No;
                    itor_list->startTime=temp_city.startTime;
                    itor_list->endTime=temp_city.endTime;
                    itor_list->moneyConsum=temp_city.moneyConsum;
                    if(itor_list->startTime>=curCity.endTime){
                        itor_list->timeConsum=temp_city.timeConsum+itor_list->startTime-curCity.endTime;
                    }
                    else{
                        itor_list->timeConsum=temp_city.timeConsum+24-curCity.endTime+itor_list->startTime;
                    }
                    itor_list->timeSum+=itor_list->timeConsum;
                    itor_list->currentTime=temp_city.endTime;
                }
            }

            else{//不在open和close
                for(itor_list=neitherList.begin(); itor_list!=neitherList.end(); itor_list++){//在neither表中取出城市i
                    childCity=*itor_list;
                    if(childCity.name == i){
                        neitherList.erase(itor_list);
                        break;
                    }
                }
                childCity.from=curCity.name;
                CityNode temp_city=TwoCityLeastMoney(curCity.name, childCity.name);
                childCity.G=curCity.G+temp_city.moneyConsum;//修改childCity的G值，等于curCity的G值，加上两个城市之间的代价
                childCity.H=H_Function_Money(childCity.name, endCity);
                childCity.F=childCity.G+childCity.H;
                childCity.method=temp_city.method;
                childCity.No=temp_city.No;
                childCity.startTime=temp_city.startTime;
                childCity.endTime=temp_city.endTime;
                childCity.moneyConsum=temp_city.moneyConsum;
                if(childCity.startTime>=curCity.endTime){//判断当前时间和下一阶段开始时间的关系
                    childCity.timeConsum=temp_city.timeConsum+childCity.startTime-curCity.endTime;
                }
                else{
                    childCity.timeConsum=temp_city.timeConsum+24-curCity.endTime+childCity.startTime;
                }
                childCity.timeSum+=childCity.timeConsum;
                childCity.currentTime=childCity.endTime;

                openList.push_back(childCity);//将该子结点压入openList中
            }
        }
        closeList.push_back(curCity);//将该城市压入closeList中
        openList.sort();//重拍openList列表
    }
    return NULL;
}

/*
 * 函数名称：Map::LimitTime
 * 参数列表说明：函数接收五个参数：startCity和endCity分别为起始城市
 *         和终止城市；currentTime记录出发的最早时间（取值范围0-23）；
 *         passCity为途径城市列表；upperBound为设置的时间上限。
 * 返回值：函数返回指向已经生成的路径的指针
 * 功能说明：该函数用来实现限时最少金钱策略，函数调用了递归函数LimitTime_TrackBack,
 *         用来生成具体的路线。
 */

std::list<TravelCityInfo> * Map::LimitTime(Cities startCity, Cities endCity, int currentTime,
                                           std::list<PassCityInfo> passCity, int upperBound){

    std::list<TravelCityInfo> path;//记录已走路径的链表
    path.clear();

    nowPathLeast.clear();//初始化工作
    nowMoneyLeast=Infinity;

    CityInfo startCityInfo;//初始化
    startCityInfo=InitCityInfo(startCity);
    startCityInfo.notPassed=0x000FFFFF ^ (0x1<<startCityInfo.name);

    LimitTime_TrackBack(startCityInfo, endCity, currentTime, 0, path, passCity, upperBound);//调用递归函数

    return NULL;
}

/*
 * 函数名称：Map::LimitTime_TrackBack
 * 参数列表说明：函数接收七个参数：startCity和endCity分别为起始城市
 *         和终止城市；currentTime记录出发的最早时间（取值范围0-23）；
 *         nowMoney记录当前的金钱耗费；nowPath记录当前路径；passCity
 *         记录未途径的城市列表；upperBound记录时间上限。
 * 返回值：无
 * 功能说明：该函数用来实现限时最少策略的递归部分，当得到当前的最优解时，
 *         更新Map类成员变量中，记录最优解的相关变量。
 */

void Map::LimitTime_TrackBack(CityInfo nowCity, Cities endCity, int currentTime, int nowMoney,
                  std::list<TravelCityInfo> nowPath, std::list<PassCityInfo> passCity, int upperBound){

    if(upperBound<0){//如果已超过上限
        return ;
    }
    //未超上限
    if(nowCity.name==endCity){//搜索到终点城市
        if(passCity.empty()){//若途径城市全部经过
            if(nowMoney<nowMoneyLeast){//并且花费少于当前最优解
                nowPathLeast.clear();
                std::copy(nowPath.begin(), nowPath.end(), std::back_inserter(nowPathLeast));//拷贝当前路径到最优解
                nowMoneyLeast=nowMoney;//更新当前最少花费
            }
        }
        //其他情况，不执行更新操作
        return ;
    }

    if(nowCity.name == passCity.front().name){//若当前城市为途径城市，在列表中弹出第一项
        PassCityInfo temp;
        temp=passCity.front();
        passCity.pop_front();
        currentTime=(currentTime+temp.stayTime)%24;//计算停留后的时间
        upperBound=upperBound-temp.stayTime;//更新上限
        if(upperBound<=0) return;//若此时已经没有多余的时间，直接返回上一层
    }

    for(int i=0; i<20; i++){//搜索邻接点
        if( ((nowCity.adjCities & (0x1<<i))==0) || ((nowCity.notPassed & (0x1<<i))==0) ){//若不邻接，或者邻接但已经途经过，则查看下一节点
            continue;
        }
        TravelCityInfo temp;
        temp.begin=nowCity.name;
        temp.end=IntIntoCity(i);

        CityInfo childCity=InitCityInfo(IntIntoCity(i));
        childCity.notPassed=nowCity.notPassed ^ (0x1<<i);//更新没有通过的城市信息，二进制压缩存储

        int waitTime=Infinity;

        QSqlQuery query;

        //查找交通方式为公交的时刻表
        query.exec("SELECT * FROM timeTable WHERE startCity = '"+CityToNumString(nowCity.name)+"' AND endCity = '"+CityToNumString(IntIntoCity(i))+"' AND method = '2'");
        while(query.next()){//剪枝优化
            int temp_wait=query.value("startTime").toInt()-currentTime;
            if(temp_wait<0) temp_wait+=24;
            if(temp_wait < waitTime){
                waitTime = temp_wait;
                temp.No=query.value("No").toString();
                temp.tran=2;
                temp.startTime=query.value("startTime").toInt();
                temp.endTime=query.value("endTime").toInt();
                temp.moneyConsum=query.value("moneyConsum").toInt();
                temp.timeConsum=temp.endTime-temp.startTime+waitTime;
            }
        }
        if(waitTime!=Infinity){//递归下一层
            nowPath.push_back(temp);
            LimitTime_TrackBack(childCity, endCity, temp.endTime, nowMoney+temp.moneyConsum, nowPath, passCity, upperBound-temp.timeConsum);
            nowPath.pop_back();
        }

        //查找交通方式为火车的时刻表
        waitTime=Infinity;
        query.exec("SELECT * FROM timeTable WHERE startCity = '"+CityToNumString(nowCity.name)+"' AND endCity = '"+CityToNumString(IntIntoCity(i))+"' AND method = '1'");
        while(query.next()){//剪枝优化
            int temp_wait=query.value("startTime").toInt()-currentTime;
            if(temp_wait<0) temp_wait+=24;
            if(temp_wait < waitTime){
                waitTime = temp_wait;
                temp.No=query.value("No").toString();
                temp.tran=1;
                temp.startTime=query.value("startTime").toInt();
                temp.endTime=query.value("endTime").toInt();
                temp.moneyConsum=query.value("moneyConsum").toInt();
                temp.timeConsum=temp.endTime-temp.startTime+waitTime;
            }
        }
        if(waitTime!=Infinity){//递归下一层
            nowPath.push_back(temp);
            LimitTime_TrackBack(childCity, endCity, temp.endTime, nowMoney+temp.moneyConsum, nowPath, passCity, upperBound-temp.timeConsum);
            nowPath.pop_back();
        }

        //查找交通方式为飞机的时刻表
        waitTime=Infinity;
        query.exec("SELECT * FROM timeTable WHERE startCity = '"+CityToNumString(nowCity.name)+"' AND endCity = '"+CityToNumString(IntIntoCity(i))+"' AND method = '0'");
        while(query.next()){//逐个递归下一层
            waitTime = query.value("startTime").toInt()-currentTime;
            if(waitTime<0) waitTime+=24;
            temp.No=query.value("No").toString();
            temp.tran=0;
            temp.startTime=query.value("startTime").toInt();
            temp.endTime=query.value("endTime").toInt();
            temp.moneyConsum=query.value("moneyConsum").toInt();
            temp.timeConsum=temp.endTime-temp.startTime+waitTime;
            nowPath.push_back(temp);
            LimitTime_TrackBack(childCity, endCity, temp.endTime, nowMoney+temp.moneyConsum, nowPath, passCity, upperBound-temp.timeConsum);
            nowPath.pop_back();
        }
    }
    return ;
}

/*
 * 函数名称：Map::InitCityInfo
 * 参数列表说明：函数接收一个参数：city表示需要初始化的城市结点
 * 返回值：函数返回一个CityInfo结构体
 * 功能说明：该函数完成指定结点的初始化工作，并返回结点的全部信息
 *         包括城市名称和城市邻接状况。
 */

CityInfo Map::InitCityInfo(Cities city){
    CityInfo temp;
    temp.name=city;//初始化名称
    switch (temp.name) {//初始化邻接状态
    case Baotou:temp.adjCities=0x00002002; break;
    case Huhehaote:temp.adjCities=0x0000000D; break;
    case Tongliao:temp.adjCities=0x0000000A; break;
    case Beijing:temp.adjCities=0x000031f6; break;
    case Tianjin:temp.adjCities=0x00000048; break;
    case Taiyuan:temp.adjCities=0x00001008; break;
    case Changzhou:temp.adjCities=0x00000098; break;
    case Shanghai:temp.adjCities=0x00001348; break;
    case Hangzhou:temp.adjCities=0x00001E88; break;
    case Ningbo:temp.adjCities=0x00000180; break;
    case Wenzhou:temp.adjCities=0x00000180; break;
    case Lishui:temp.adjCities=0x00000100; break;
    case Chongqing:temp.adjCities=0x000021A8; break;
    case Kunming:temp.adjCities=0x00095009; break;
    case Panzhihua:temp.adjCities=0x00012000; break;
    case Xianggelila:temp.adjCities=0x00010000; break;
    case Lijiang:temp.adjCities=0x0006E000; break;
    case Erhai:temp.adjCities=0x00050000; break;
    case Dali:temp.adjCities=0x000B0000; break;
    case Xishuangbanna:temp.adjCities=0x00042000; break;
    default:
        qDebug()<<"Map::InitCityInfo()出错，城市名无法识别";
        break;
    }
    return temp;
}

/*
 * 函数名称：Map::MakeWay
 * 参数列表说明：函数接收三个参数：startCity和endCity分别为起始城市
 *         和终止城市；timeSum记录当前的耗时的总和，以引用方式传递。
 * 返回值：函数返回指向所生成路径的指针
 * 功能说明：该函数用来生成最少金钱策略和最少时间策略的旅行路线，在LeastTime
 *         LeastMoney中调用该函数，并使用该函数的返回值。
 */

std::list<TravelCityInfo> * Map::MakeWay(Cities startCity, Cities endCity, int &timeSum){

    std::list<TravelCityInfo> * p=new std::list<TravelCityInfo>;//new出记录路线的链表
    TravelCityInfo temp_info;

    std::list<CityNode>::iterator itor_list;

    while(startCity!=endCity){//反向遍历，生成路线
        for(itor_list=closeList.begin(); itor_list!=closeList.end(); itor_list++){
            if(endCity==itor_list->name){
                endCity=itor_list->from;
                temp_info.begin=itor_list->from;
                temp_info.end=itor_list->name;
                temp_info.No=itor_list->No;
                temp_info.startTime=itor_list->startTime;
                temp_info.endTime=itor_list->endTime;
                temp_info.moneyConsum=itor_list->moneyConsum;
                temp_info.timeConsum=itor_list->timeConsum;
                temp_info.tran=itor_list->method;
                timeSum+=temp_info.timeConsum;
                p->push_front(temp_info);
                break;
            }
        }
    }
    return p;
}

/*
 * 函数名称：Map::inOpen
 * 参数列表说明：该函数接收一个参数：x用来表示某一城市
 * 返回值：函数返回判断结果，如果x在openList中返回true，反之返回false
 * 功能说明：该函数用来判断x是否在openList列表中，LeastTime和LeastMoney中会
 *         调用该函数。
 */

bool Map::inOpen(int x){
    std::list<CityNode>::iterator itor_list;
    for(itor_list=openList.begin(); itor_list!=openList.end(); itor_list++){//遍历openList
        if((*itor_list).name == x){//找到
            return true;
        }
    }
    return false;
}

/*
 * 函数名称：Map::inClose
 * 参数列表说明：该函数接收一个参数：x用来表示某一城市
 * 返回值：函数返回判断结果，如果x在closeList中返回true，反之返回false
 * 功能说明：该函数用来判断x是否在closeList列表中，LeastTime和LeastMoney中会
 *         调用该函数。
 */

bool Map::inClose(int x){
    std::list<CityNode>::iterator itor_list;
    for(itor_list=closeList.begin(); itor_list!=closeList.end(); itor_list++){//遍历closeList
        if((*itor_list).name == x) return true;//找到
    }
    return false;
}

/*
 * 函数名称：Map::H_Function_Time
 * 参数列表说明：该函数接收两个参数：source代表源城市，target代表目标城市
 * 返回值：函数返回在时间维度上的估价值
 * 功能说明：该函数用来实现最少时间策略中的估价函数，LeastTime中调用该函数。
 */

int Map::H_Function_Time(Cities source, Cities target){
    return jump[source][target] * TimeEachJump;
}

/*
 * 函数名称：Map::H_Function_Time
 * 参数列表说明：该函数接收两个参数：source代表源城市，target代表目标城市
 * 返回值：函数返回在金钱维度上的估价值
 * 功能说明：该函数用来实现最少金钱策略中的估价函数，LeastMoney中调用该函数。
 */

int Map::H_Function_Money(Cities source, Cities target){
    return jump[source][target] * MoneyEachJump;
}

/*
 * 函数名称：Map::TwoCityLeastTime
 * 参数列表说明：该函数接收三个参数：start和end分别代表其实城市和终止城市，currentTime为当前
 *         时间（取值范围0-23）
 * 返回值：函数返回一个CityNode结构体
 * 功能说明：计算两城市之间的最少时间路线，并以CityNode的形式返回该路线，LeastTime中调用了该函数。
 */

CityNode Map::TwoCityLeastTime(Cities start, Cities end, int currentTime){
    QSqlQuery query;
    bool find=false;
    CityNode temp_city;

    //查询数据库
    find=query.exec("SELECT * FROM timeTable WHERE startCity = '"+CityToNumString(start)+"' AND endCity = "+CityToNumString(end));
    if(!find){
        qDebug()<<"Map::TwoCityLeastMoney，查询数据库失败";
        return temp_city;
    }

    temp_city.timeConsum=Infinity;
    while(query.next()){//遍历找最少时间
        int temp_time;
        if(query.value("startTime").toInt()<currentTime){
            temp_time=24-currentTime+query.value("endTime").toInt();
        }
        else{
            temp_time=query.value("endTime").toInt()-currentTime;
        }

        if(temp_time<temp_city.timeConsum){//找到，更新
            temp_city.moneyConsum=query.value("moneyConsum").toInt();
            temp_city.method=query.value("method").toInt();
            temp_city.No=query.value("No").toString();
            temp_city.startTime=query.value("startTime").toInt();
            temp_city.endTime=query.value("endTime").toInt();
            temp_city.timeConsum=temp_time;
            temp_city.currentTime=(currentTime+temp_time)%24;
        }
    }
    return temp_city;
}

/*
 * 函数名称：Map::TwoCityLeastMoney
 * 参数列表说明：该函数接收两个参数：start和end分别代表其实城市和终止城市。
 * 返回值：函数返回一个CityNode结构体
 * 功能说明：计算两城市之间的最少金钱路线，并以CityNode的形式返回该路线，LeastMoney中调用了该函数。
 */

CityNode Map::TwoCityLeastMoney(Cities start, Cities end){
    QSqlQuery query;
    bool find=false;
    CityNode temp_city;

    //查询数据库
    find=query.exec("SELECT * FROM timeTable WHERE startCity = '"+CityToNumString(start)+"' AND endCity = "+CityToNumString(end));
    if(!find){
        qDebug()<<"Map::TwoCityLeastMoney，查询数据库失败";
        return temp_city;
    }

    temp_city.moneyConsum=Infinity;
    while(query.next()){//遍历找最少金钱
        if(query.value("moneyConsum").toInt()<temp_city.moneyConsum){//找到，更新
            temp_city.moneyConsum=query.value("moneyConsum").toInt();
            temp_city.method=query.value("method").toInt();
            temp_city.No=query.value("No").toString();
            temp_city.startTime=query.value("startTime").toInt();
            temp_city.endTime=query.value("endTime").toInt();
            temp_city.timeConsum=temp_city.endTime-temp_city.startTime;
        }
    }
    return temp_city;
}

/*
 * 函数名称：Map::CityToNumString
 * 参数列表说明：该函数接收一个参数：city表示转换的城市名称
 * 返回值：函数返回一个QString字符串
 * 功能说明：函数完成城市名称到表示城市数字的字符串的转换。
 */

QString Map::CityToNumString(Cities city){
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
        qDebug()<<"Map::CityToNumString中出错";
    }
    return "";
}

/*
 * 函数名称：Map::IntIntoCity
 * 参数列表说明：该函数接收一个参数：cityInt表示转换的城市名称
 * 返回值：函数返回一个Cities的枚举类型
 * 功能说明：函数完成int型到Cities的转换。
 */

Cities Map::IntIntoCity(int cityInt){
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
 * 函数名称：Map::CityToInt
 * 参数列表说明：该函数接收一个参数：cityInt表示转换的城市名称
 * 返回值：函数返回一个表示城市的int值
 * 功能说明：函数完成Cities型到int的转换。
 */

int Map::CityToInt(Cities cityInt){
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
 * 函数名称：Map::Map
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：Map类的默认构造函数，初始化所有必要的成员变量。
 */

Map::Map(){
    //清空所有链表
    openList.clear();
    closeList.clear();
    neitherList.clear();

    cityAmount=20;//初始化城市结点数量

    CityNode temp;

    for(unsigned int i=0;i<cityAmount;i++){//初始化每一个城市结点
        temp.name=IntIntoCity(i);
        switch (i) {//初始化邻接状态，二进制压缩存储
        case 0:temp.adjCities=0x00002002; break;
        case 1:temp.adjCities=0x0000000D; break;
        case 2:temp.adjCities=0x0000000A; break;
        case 3:temp.adjCities=0x000031f6; break;
        case 4:temp.adjCities=0x00000048; break;
        case 5:temp.adjCities=0x00001008; break;
        case 6:temp.adjCities=0x00000098; break;
        case 7:temp.adjCities=0x00001348; break;
        case 8:temp.adjCities=0x00001E88; break;
        case 9:temp.adjCities=0x00000180; break;
        case 10:temp.adjCities=0x00000180; break;
        case 11:temp.adjCities=0x00000100; break;
        case 12:temp.adjCities=0x000021A8; break;
        case 13:temp.adjCities=0x00095009; break;
        case 14:temp.adjCities=0x00012000; break;
        case 15:temp.adjCities=0x00010000; break;
        case 16:temp.adjCities=0x0006E000; break;
        case 17:temp.adjCities=0x00050000; break;
        case 18:temp.adjCities=0x000B0000; break;
        case 19:temp.adjCities=0x00042000; break;
        default:
            break;
        }
        //初始化其他信息
        temp.from=unknown;
        temp.F=Infinity; temp.G=Infinity; temp.H=Infinity;
        temp.method=Infinity;
        temp.No="";
        temp.startTime=Infinity;
        temp.endTime=Infinity;
        temp.moneyConsum=Infinity;
        temp.timeConsum=Infinity;
        temp.currentTime=Infinity;
        neitherList.push_back(temp);
    }
}

/*
 * 函数名称：Map::～Map
 * 参数列表说明：无
 * 返回值：无
 * 功能说明：Map类的析构函数。
 */

Map::~Map(){

}
