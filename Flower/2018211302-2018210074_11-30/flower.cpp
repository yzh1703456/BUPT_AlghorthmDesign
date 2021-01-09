#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <math.h>
#include <vector>

#define MaxNumOfBottle 200 //最大花瓶数目
#define MaxNUmOfFlower 100 //最大花束数目

using namespace std;

int main()
{
    cout << "No problem" << endl;
    cout<<endl;
    while (1)
    {
        cout<<"******************************************************************************************"<<endl;
        int F, V; //F为花束数目，V为花瓶数目
        cout << "请输入花束数目和花瓶数目，以空格间隔：" << endl;
        cin >> F >> V;
        cout << "请输入每束花束在每个花瓶里产生的美学值：" << endl;
        int value[MaxNUmOfFlower][MaxNumOfBottle] = {0}; //每一个花束放在每一个花瓶所产生的美学值
        int res[MaxNUmOfFlower][MaxNumOfBottle];         //存结果
        vector<int> place[MaxNUmOfFlower];               //每朵花的放置情况
        for (int i = 1; i <= F; i++)
        {
            for (int j = 1; j <= V; j++)
                res[i][j] = INT_MIN;
        }
        for (int i = 1; i <= F; i++)
        {
            for (int j = 1; j <= V; j++)
                cin >> value[i][j];
        }
        /*
    cout << "每束花束在每个花瓶里产生的美学值是：" << endl;
    for (int i = 1; i <= F; i++)
    {
        for (int j = 1; j <= V; j++)
            cout << value[i][j] << " ";
        cout << endl;
    }
    */
        /*
    cout<<"计算前的结果数组为："<<endl;
    for(int i=1;i<=F;i++)
    {
        for(int j=1;j<=V;j++)
            cout<<res[i][j]<<" ";
        cout<<endl;
    }
    */
        int k = V - F;
        for (int i = 1; i <= F; i++)
        {
            for (int j = i; j <= V && j <= i + k; j++)
            {
                //place[i].push_back(j);
                if (res[i - 1][j - 1] + value[i][j] > res[i][j - 1])
                {
                    //cout<<res[i - 1][j - 1] + value[i][j] <<" "<< res[i][j - 1]<<endl;
                    res[i][j] = res[i - 1][j - 1] + value[i][j];
                    place[i].push_back(j);
                    place[i - 1].push_back(j - 1);
                }
                else
                {
                    //cout<<res[i - 1][j - 1] + value[i][j] <<" "<< res[i][j - 1]<<endl;
                    res[i][j] = res[i][j - 1];
                    place[i].push_back(j);
                    for (int w = 1; w <= i; w++)
                        place[w].pop_back();
                }
                /*
            cout<<"我们看看place"<<i<<endl;
            for(int ww=0;ww<place[i].size();ww++)
                cout<<place[i][ww]<<" ";
            cout<<endl<<endl;
            */
            }
        }
        /*
    cout<<"计算后的结果数组为："<<endl;
    for(int i=1;i<=F;i++)
    {
        for(int j=1;j<=V;j++)
            cout<<res[i][j]<<" ";
        cout<<endl;
    }
    */

        /*
   for(int i=1;i<=F;i++)
   {
       cout<<"我们看看place"<<i<<endl;
       for(int ww=0;ww<place[i].size();ww++)
                cout<<place[i][ww]<<" ";
            cout<<endl<<endl;
   }
   */

        cout << "能产生的最大美学值是：" << res[F][V] << endl;
        cout << "实现此最大美学值的花束摆放方案是：" << endl;
        for (int i = 1; i <= F; i++)
        {
            int temp = place[i][place[i].size() - 1];

            cout << "第" << i << "束花束放在第" << temp << "个花瓶，美学值为：" << value[i][temp] << endl;
        }
        cout<<"******************************************************************************************"<<endl;
    }
    
    system("pause");
    return 0;
}

/*
3 5

7 23 –5 –24 16
5 21 -4 10 23
-21 5 -4 -20 20
*/