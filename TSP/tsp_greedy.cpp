/*****************************************************************
 * Copyright (c)2020, by Septer(Xiong Yu), Beijing University of Posts and Telecommunication
 * All rights reserved.
 * FileName：		    tsp_greedy.cpp
 * System：          	Algorithm design and analysis
 * SubSystem：        	Backtracking Greedy
 * Author：		Septer(Xiong Yu)
 * Date：		2020.12.2
 * Version：		2.0
 * Description：
        求解课件4城市图的旅行售货员问题
 *
 * Last Modified:

    2020.12.9, 	By Septer(Xiong Yu)
*****************************************************************/

#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

#define cityNum 4
#define edgeNum 16
#define maxCost 0x3f3f3f

int currentCost;           //当前路径长度
int bestCost;              //最佳路径长度
int path[cityNum + 1];     //各城市路径
int bestPath[cityNum + 1]; //各城市最好路径
int start;                 //出发城市

//4城市距离矩阵
int dis[cityNum + 1][cityNum + 1] = {
    -1, -1, -1, -1, -1,
    -1, -1, 3, 6, 7,
    -1, 12, -1, 2, 8,
    -1, 8, 6, -1, 2,
    -1, 3, 7, 6, -1
};

/*
-1, -1, -1, -1, -1,
    -1, -1, 3, 6, 7,
    -1, 12, -1, 2, 8,
    -1, 8, 6, -1, 2,
    -1, 3, 7, 6, -1
*/

void Initial();            //初始化
int GetPos(int pos, vector <int> p);       //求解下一步要走的城市
void Greedy();             //贪心求局部最优
void Swap(int &a, int &b); //交换
void BackTrack(int i);     //第i步去的城市
void Output();             //输出结果

int main()
{
    Initial();
    Greedy();
    start=1;
    //cout<<start<<" "<<currentCost<<" "<<bestCost<<endl;
    BackTrack(2);
    Output();
    system("pause");
    return 0;
}

/////////////////////////////////////////////////////////////////////
// Function：		Initial
// Description:
//	初始化变量
// Args：
//	无
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Initial()
{
    currentCost = 0;
    bestCost = 0;
    for (int i = 1; i <= cityNum; i++)
    {
        path[i] = i;
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		GetPos
// Description:
//	求解下一步要走的城市
// Args：
//	int
//  上一步的城市
// Return Values:
//      int
//      是否终止
/////////////////////////////////////////////////////////////////////
int GetPos(int pos, vector <int> p)
{
    int minDis=maxCost;
    int i;
    int next=pos;
    for(i=1;i<=cityNum;i++)
    {
        if((dis[pos][i]!=-1)&&(dis[pos][i]<minDis)&&(find(p.begin(), p.end(), i)==p.end()))
        {
            minDis=dis[pos][i];
            next=i;
        }
    }
    bestCost+=minDis;
    //cout<<pos<<" "<<next<<" "<<minDis<<endl;
    p.push_back(next);
    if(p.size()==cityNum)
    {
        bestCost+=dis[next][start];
        return 0;
    }
    else
    {
        GetPos(next,p);
    }
}     

/////////////////////////////////////////////////////////////////////
// Function：		Greedy
// Description:
//	贪心求局部最优
// Args：
//	无
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Greedy()
{
    int pos=1;
    vector <int> pass;
    int minBest=maxCost;
    int i,j;
    int next;
    for(i=1;i<=cityNum;i++)
    {
        for(j=1;j<=cityNum;j++)
        {
            if((dis[i][j]<minBest)&&(dis[i][j]!=-1))
            {
                minBest=dis[i][j];
                pos=i;
                next=j;
            }
        }
    }
    //cout<<pos<<" "<<next<<" "<<minBest<<endl;
    start=pos;
    pos=next;
    pass.push_back(start);
    pass.push_back(next);
    bestCost+=minBest;
    GetPos(next,pass);
}

/////////////////////////////////////////////////////////////////////
// Function：		Swap
// Description:
//	交换两变量值
// Args：
//	Arg1	int&  待交换变量A
//	Arg2	int&  待交换变量B
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

/////////////////////////////////////////////////////////////////////
// Function：		BackTrack
// Description:
//	求解第i步前往的城市
// Args：
//	Arg1	int  售货员旅行的第i步
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void BackTrack(int i)
{
    if (i == cityNum)
    {
        if ((dis[path[i - 1]][path[i]] != -1) && (dis[path[i]][path[start]] != -1) && (currentCost + dis[path[i - 1]][path[i]] + dis[path[i]][path[start]] <= bestCost || bestCost == maxCost))
        {
            bestCost = currentCost + dis[path[i - 1]][path[i]] + dis[path[i]][path[start]];
            for (int j = 1; j <= cityNum; j++)
            {
                bestPath[j] = path[j];
            }
        }
    }
    else
    {
        for (int j = i; j <= cityNum; j++)
        {
            if ((dis[path[i - 1]][path[j]] != -1) && (currentCost + dis[path[i - 1]][path[j]] <= bestCost || bestCost == maxCost))
            {
                Swap(path[i], path[j]); //交换了i和j的位置
                currentCost += dis[path[i - 1]][path[i]];
                BackTrack(i + 1);
                currentCost -= dis[path[i - 1]][path[i]];
                Swap(path[i], path[j]);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
// Function：		Output
// Description:
//	输出
// Args：
//	无
// Return Values:
//      void
//      无描述
/////////////////////////////////////////////////////////////////////
void Output()
{
    cout << "最佳路线为：";
    for (int i = 1; i <= cityNum; i++)
    {
        cout << bestPath[i] << "->";
    }
    cout << start << endl;
    cout << "最佳路径长度为：" << bestCost << endl;
}