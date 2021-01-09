#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <vector>

#define MAXNUMOFRACER 200

using namespace std;

typedef struct s
{
    vector<int> compete;
};

//APP[i][j]表示第i号选手在第j天遇到的对手是几号
int APP[MAXNUMOFRACER + 2][MAXNUMOFRACER + 2] = {0};
//A[i]记录i号选手已经比过的人
s A[MAXNUMOFRACER + 2];
int numOfRacer; //比赛人数

void Race(int n, int day); //比赛函数
void PrintRes();           //打印结果函数
void LoopPlus(int &k, int &time); //循环自增

int main()
{
    while (1)
    {
        cout << "请输入需要完成循环赛的选手数目：";
        cin >> numOfRacer;
        int k=0,time=1;
        
        if (numOfRacer == 0)
        {
            cout << "选手数不能为0！异常退出！" << endl;
            break;
        }
        int dayOfRacer;
        if (numOfRacer % 2 == 0)
            dayOfRacer = numOfRacer - 1;
        else
        {
            dayOfRacer = numOfRacer;
        }

        Race(numOfRacer, dayOfRacer);
        PrintRes();
    }
    system("pause");
    return 0;
}

void LoopPlus(int &k, int &time)
{
    k++;
    k=k%(numOfRacer+1);
    time++;
    //cout<<k<<" "<<time<<endl;
}

void PrintRes()
{
    cout << endl;
    cout << "当有" << numOfRacer << "参与循环赛时，日程安排如下：" << endl;
    int raceDay;
    if (numOfRacer % 2 == 0)
    {
        raceDay = numOfRacer - 1;
    }
    else
        raceDay = numOfRacer;
    cout.flags(ios::left);
    cout << setw(8) << "";
    for (int i = 1; i <= numOfRacer; i++)
        cout << setw(2) << i << "号";
    cout << endl;
    cout.flags(ios::left);
    for (int j = 1; j <= raceDay; j++)
    {
        cout << "第" << setw(2) << j << "天  ";
        for (int i = 1; i <= numOfRacer; i++)
        {
            cout << setw(4) << APP[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void Race(int n, int day)
{
    int NewN;
    if (n <= 1)
    {
        return;
    }
    else
    {
        for (int i = 1; i <= numOfRacer; i++)
        {
            for (int j = 1; j <= day; j++)
            {
                
                if (APP[i][j] == 0)
                {
                    
                    for (int k = i+1,time=1; (k <= numOfRacer) && (k != i) && (time<=numOfRacer); LoopPlus(k,time))
                    {
                        //cout<<k<<endl;
                        if (!(count(A[i].compete.begin(), A[i].compete.end(), k)) && ((APP[k][j] == 0) || (APP[k][j] == i)))
                        {
                            APP[i][j] = k;
                            APP[k][j] = i;
                            A[i].compete.push_back(k);
                            A[k].compete.push_back(i);
                            
                            break;
                        }
                    }
                    
                }
            }
        }
    }
}