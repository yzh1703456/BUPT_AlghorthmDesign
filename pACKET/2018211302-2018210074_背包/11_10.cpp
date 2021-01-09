#include <iostream>
#define V 500
using namespace std;
int weight[20 + 1];
int value[20 + 1];
int m[20 + 1][V + 1];
int main()
 {
    int n, C;
    cout << "请输入可供选择的物品个数和背包所能容纳的最大容量"<<endl;
    cin >> n>>C;
    cout << "请分行输入" << n << "个物品的重量和价值，以空格间隔:" << endl; 
    for (int i = 1; i <= n; i++) 
    {
        cin >> weight[i] >> value[i];
    }
    for (int i = 1; i <= n; i++) 
    {
        for (int j = 1; j <= C; j++) 
        {
            if (weight[i] > j) 
            {
                m[i][j] = m[i - 1][j];
            }
            else 
            {
                m[i][j] = m[i - 1][j] > m[i - 1][j - weight[i]] + value[i] ? m[i - 1][j] : m[i - 1][j - weight[i]] + value[i];
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=C;j++)
        {
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    cout << "背包能放的最大价值为:" << m[n][C] << endl;
    system("pause");
    return 0;
}