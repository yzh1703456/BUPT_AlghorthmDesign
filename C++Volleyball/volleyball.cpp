#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>

#define MAXNUMOFRACER 200

using namespace std;

//APP[i][j]表示第i号选手在第j天遇到的对手是几号
int APP[MAXNUMOFRACER + 2][MAXNUMOFRACER + 2];
int numOfRacer; //比赛人数

void Race(int n);  //比赛函数
void Merge(int n); //分治函数
void PrintRes();   //打印结果函数

int main()
{
    while (1)
    {
        cout << "请输入需要完成循环赛的选手数目：";
        cin >> numOfRacer;
        if(numOfRacer==0)
        {
            cout<<"选手数不能为0！异常退出！"<<endl;
            break;
        }
        Race(numOfRacer);
        PrintRes();
        
    }
    system("pause");
    return 0;
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

void Merge(int n)
{
    int dayOfRace;             //比赛天数
    int dayOfPast;             //已经安排好的天数
    int halfN = ceil(n / 2.0); //n折半
    int oddFlag = 0;           //奇数标志位，用它来更改后续奇数时的增量，使得总体不出错
    if (n % 2 == 0)
    {
        dayOfRace = n - 1;
    }
    else
    {
        dayOfRace = n;
    }
    if (halfN % 2 == 0)
    {
        dayOfPast = halfN - 1;
    }
    else
    {
        dayOfPast = halfN;
    }

    for (int i = 1; i <= halfN; i++)
    {
        for (int j = 1; j <= dayOfPast; j++)
        {
            if (APP[i][j] != 0) //i号在第j天已经有了选手，我们让i+m号在第j天的选手变成APP[i][j]+m
                APP[i + halfN][j] = APP[i][j] + halfN;
            else //i号在第j天没有选手，就让i和i+m在第j天互为选手
            {
                APP[i][j] = i+halfN;
                APP[i + halfN][j] = i;
            }
        }
    }
    if (APP[1][dayOfPast] == halfN + 1)
        oddFlag = 1;
    int count = 0; //计数来更改增量
    for (int i = 1; i <= halfN; i++)
    {
        for (int j = dayOfPast + 1,count=0; j <= dayOfRace; j++, count++)
        {
            //安排i号在第j天的对手
            int temp = (count + oddFlag + i - 1) % halfN + halfN + 1;
            APP[i][j] = temp;
            APP[temp][j] = i;
        }
    }

    //此处进行最后修缮，如果n为奇数，我们刚刚运算时其实多算了一列，需要清零
    if ((n % 2) != 0)
    {
        for (int i = 1; i <= 2 * halfN; i++)
        {
            for (int j = 1; j <= dayOfRace; j++)
            {
                if (APP[i][j] == n + 1)
                    APP[i][j] = 0;
            }
        }
    }
}

void Race(int n)
{
    int NewN;
    if (n <= 1)
    {
        return;
    }
    else
    {
        if (n == 2)
        {
            APP[1][1] = 2;
            APP[2][1] = 1;
        }
        else
        {
            NewN = ceil(n / 2.0);
            Race(NewN);
            Merge(n);
        }
    }
}