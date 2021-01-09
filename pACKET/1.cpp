#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

void knaspack(int* v, int* w,int c, int n, int **m)
{
    int jmax=min(w[n-1],c);
    for(int j=0;j<=jmax;j++)
    {
        m[n][j]=0;
    }
    for(int j=w[n],j<=n;j++)
    {
        m[n][j]=v[n];
    }
    for(int i=n-1;i>1;i--)
    {
        jmax=min(w[i]-1,c);
        for(int j=0;j<=jmax;j++)
        {
            m[i][j]=m[i+1][j];
        }
        for(int j=w[i];j<=c;j++)
        {
            m[i][j]=max(m[i+1][j],m[i+1][j-w[i]+v[i]]);
        }
    }
}

int main()
{
    system("pause");
    return 0;
}