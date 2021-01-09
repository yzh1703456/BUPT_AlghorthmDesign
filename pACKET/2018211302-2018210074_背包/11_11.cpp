#include <iostream>

#define V 500
using namespace std;
int weight[20 + 1];
int value[20 + 1];
int m[20 + 1][V + 1];

template<class Type>
int pack(int n,Type c,Type v[],Type w[],int **p,int x[]);
template<class Type>
void trace(int n,Type w[],Type v[],Type **p,int *head,int x[]);

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
    int x[20+1]; //针对物品而言，xi被装进去，就置1；否则置0

    int **p=new int *[V];
    for(int i=0;i<V;i++)
    {
        p[i]=new int[2]; //记录跳跃点，第一个int存重量，第二个int存价值
    }
    cout << "背包能放的最大价值为:" << pack(n,C,value,weight,p,x) << endl;
    cout<<"背包装下的物品编号为：";
	for(int i=1; i<=n; i++)
	{
		if(x[i]==1)
		{
			cout<<i<<" ";
		}
	}
	cout<<endl;

	for(int i=0; i<V; i++)
	{
		delete p[i];
	}

	delete[] p;
    system("pause");
    return 0;
}

template<class Type>
int pack(int n,Type c,Type v[],Type w[],int **p,int x[])
{
	int *head = new int[n+2];//下标从1开始，记录n+1个结点 
	head[n+1]=0;

	p[0][0]=0;//第一个记录重量，第二个记录价值
	p[0][1]=0;

	// left 指向p[i+1]的第一个跳跃点，right指向最后一个，next指向下一个跳跃点要存放的位置
	int left = 0,right = 0,next = 1;
	head[n]=1;

	for(int i=n; i>=1; i--)
	{
		int k = left;//k指向p[ ]中跳跃点,移动k来判断p[]与p[]+（w v）中的受控点
		for(int j=left; j<=right; j++)
		{
			if(p[j][0]+w[i]>c) 
                break;//背包装不下第i个物品，直接退出循环
			Type y = p[j][0] + w[i],m = p[j][1] + v[i];

			//若p[k][0]较小则(p[k][0]  p[k][1])一定不是受控点，将其作为p[i]的跳跃点存储
			while(k<=right && p[k][0]<y)
			{
				p[next][0]=p[k][0];
				p[next++][1]=p[k++][1];
			}

			//受控点，不存
			if(k<=right && p[k][0]==y)
			{
				if(m<p[k][1])//对（p[k][0]   p[k][1]）进行判断
				{
					m=p[k][1];
				}
				k++;
			}

			// 若p[k][0]>=y且m> =p[k][1],判断是不是当前i的最后一个跳跃点的受控点
			//若不是跳跃点，则作为i的跳跃点存储
			if(m>p[next-1][1])
			{
				p[next][0]=y;
				p[next++][1]=m;
			}

			//若是，则对下一个元素进行判断。
			while(k<=right && p[k][1]<=p[next-1][1])
			{
				k++;
			}
		}

		while(k<=right)
		{
			p[next][0]=p[k][0];
			p[next++][1]=p[k++][1];//将i+1剩下的跳跃点作为做为i的跳跃点存储
		}

        //更改left和right
		left = right + 1;
		right = next - 1;

		// 第i-1个物品第一个跳跃点的位置  head[n]指第n个物品第一个跳跃点的位置
		head[i-1] = next;
	}

	trace(n,w,v,p,head,x); //回溯踪迹，便于输出
	return p[next-1][1];
}


template<class Type>
void trace(int n,Type w[],Type v[],Type **p,int *head,int x[])
{
	//初始化j,m为最后一个跳跃点对应的第0列及第1列
	Type j = p[head[0]-1][0],m=p[head[0]-1][1];
	for(int i=1; i<=n; i++)
	{
		x[i]=0;// 初始化数组；
		for(int k=head[i+1]; k<=head[i]-1; k++) // 初始k指向p[2]的第一个跳跃点（0 0）
		{
			//判断物品i是否装入，装入就置1
			if(p[k][0]+w[i]==j && p[k][1]+v[i]==m)
			{
				x[i]=1;//物品i被装入，则x[i]置1
				j=p[k][0];
				m=p[k][1];
				break;
			}
		}
	}
}