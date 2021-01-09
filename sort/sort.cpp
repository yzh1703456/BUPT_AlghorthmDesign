#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>

#define MaxLineNum 100
#define MaxDataNum 1000

using namespace std;

int numOfNum, numOfLine;              //测试数据组数，每组数据量
int DefaultNum = 10, DefaultLine = 5; //默认测试数据组数，默认每组数据量
int TestData[MaxLineNum][MaxDataNum] = {0};
int NumOfSwap = 0, NumOfCmp = 0; //腾挪次数，比较次数
int NumOfBranch = 10;            //分支数
int Branch[10] = {0};            //分支计数

void ProduceTestData()
{
    ofstream OutFile("G:\\AlghorthmDesign\\sort\\TestData.txt"); //利用构造函数创建txt文本，并且打开该文本

    cout << "Please input the number of line and the number of data every line." << endl;
    cin >> numOfLine >> numOfNum;
    int arr[numOfNum], T;
    for (int i = 1; i <= numOfNum; i++)
        arr[i] = 0;
    srand(time(NULL));
    int line = 0;
    int tempLine = numOfLine;
    while (tempLine--)
    {

        for (int i = 1; i <= numOfNum; i++)
        {

            arr[i] = rand() % 100;
        }
        for (int i = 1; i <= numOfNum; i++)
        {
            OutFile << arr[i];
            TestData[line][i - 1] = arr[i];
            OutFile << " ";
        }
        OutFile << endl;
        line++;
    }
    OutFile.close();
    cout << "The test data has been produced successfully." << endl;
}

void InitialTestData()
{
    ifstream InFile("G:\\AlghorthmDesign\\sort\\TestData.txt", ios::in);
    int x;
    int num = 0;
    while (InFile >> x) //可以像用cin那样用ifstream对象
    {
        TestData[num / DefaultNum][num % DefaultNum] = x;
        num++;
    }
    InFile.close();
    numOfNum = DefaultNum;
    numOfLine = DefaultLine;
}

//交换函数
void Swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;

    return;
}

//插入排序
void InsertSort(int *h, size_t len)
{
    if (h == NULL)
    {
        Branch[0]++;
        return;
    }
    else
        Branch[1]++;
    NumOfCmp++;
    if (len <= 1)
    {
        Branch[2]++;
        return;
    }
    else
    {
        Branch[3]++;
    }

    NumOfCmp++;

    int i, j;
    //i是次数，也即排好的个数;j是继续排
    for (i = 1; i < len; ++i)
    {
        NumOfCmp++;
        for (j = i; j > 0; --j)
        {
            NumOfCmp++;
            NumOfCmp++;
            if (h[j] < h[j - 1])
            {
                Branch[4]++;
                NumOfSwap++;
                Swap(h[j], h[j - 1]);
            }
            else
            {
                Branch[5]++;
                break;
            }
        }
        NumOfCmp++;
    }
    NumOfCmp++;

    return;
}

//合并排序
void MergeArray(int *arr, size_t left, size_t mid, size_t right, int *temp)
{
    if (arr == NULL)
    {
        Branch[0]++;
        return;
    }
    Branch[1]++;
    NumOfCmp++;
    size_t i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        NumOfCmp++;
        if (arr[i] <= arr[j])
        {
            Branch[2]++;
            temp[k++] = arr[i++];
            continue;
        }
        else
        {
            Branch[3]++;
        }

        NumOfCmp++;

        temp[k++] = arr[j++];
    }
    NumOfCmp++;

    while (i <= mid)
    {
        NumOfCmp++;
        temp[k++] = arr[i++];
    }
    NumOfCmp++;

    while (j <= right)
    {
        NumOfCmp++;
        temp[k++] = arr[j++];
    }
    NumOfCmp++;

    memcpy(&arr[left], temp, k * sizeof(int));

    return;
}

void MMergeSort(int *arr, size_t left, size_t right, int *temp)
{
    NumOfCmp++;
    if (left < right)
    {
        Branch[4]++;
        size_t mid = (left + right) / 2;
        MMergeSort(arr, left, mid, temp);
        MMergeSort(arr, mid + 1, right, temp);
        MergeArray(arr, left, mid, right, temp);
    }
    else
    {
        Branch[5]++;
    }
}

void MergeSort(int *h, size_t len)
{
    NumOfCmp++;
    if (h == NULL)
    {
        Branch[6]++;
        return;
    }
    else
        Branch[7]++;
    NumOfCmp++;
    if (len <= 1)
    {
        Branch[8]++;
        return;
    }
    else
    {
        Branch[9]++;
    }

    int *temp = (int *)calloc(len, sizeof(int));
    MMergeSort(h, 0, len - 1, temp);

    memcpy(h, temp, sizeof(int) * len);

    free(temp);
    return;
}

//快速排序，随机选取哨兵放前面
void QuickSort(int *h, int left, int right)
{
    NumOfCmp++;
    if (h == NULL)
    {
        Branch[0]++;
        return;
    }
    Branch[1]++;
    NumOfCmp++;
    if (left >= right)
    {
        Branch[2]++;
        return;
    }
    else
    {
        Branch[3]++;
    }

    //防止有序队列导致快速排序效率降低
    srand((unsigned)time(NULL));
    int len = right - left;
    int kindex = rand() % (len + 1) + left;
    NumOfSwap++;
    Swap(h[left], h[kindex]);

    int key = h[left], i = left, j = right;
    while (i < j)
    {
        NumOfCmp++;
        while (h[j] >= key && i < j)
        {
            NumOfCmp++;
            --j;
        }
        NumOfCmp++;
        if (i < j)
        {
            Branch[4]++;
            h[i] = h[j];
        }
        else
            Branch[5]++;
        NumOfCmp++;
        while (h[i] < key && i < j)
        {
            NumOfCmp++;
            ++i;
        }
        NumOfCmp++;
        NumOfCmp++;
        if (i < j)
        {
            Branch[6]++;
            h[j] = h[i];
        }
        else
            Branch[7]++;
    }
    NumOfCmp++;

    h[i] = key;

    //QuickSort(&h[left],0,i-1);
    //QuickSort(&h[j+1],0,right-j-1);

    QuickSort(h, left, i - 1);
    QuickSort(h, j + 1, right);
}

//冒泡排序
void BubbleSort(int *h, size_t len)
{
    NumOfCmp++;
    if (h == NULL)
    {
        Branch[0]++;
        return;
    }
    Branch[1]++;
    NumOfCmp++;
    if (len <= 1)
    {
        Branch[2]++;
        return;
    }
    Branch[3]++;
    //i是次数，j是具体下标
    for (int i = 0; i < len - 1; ++i)
    {
        NumOfCmp++;
        for (int j = 0; j < len - 1 - i; ++j)
        {
            NumOfCmp++;
            NumOfCmp++;
            if (h[j] > h[j + 1])
            {
                Branch[4]++;
                NumOfSwap++;
                Swap(h[j], h[j + 1]);
            }
            else
            {
                Branch[5]++;
            }
        }
        NumOfCmp++;
    }
    NumOfCmp++;

    return;
}

//选择排序
void SelectionSort(int *h, size_t len)
{
    NumOfCmp++;
    if (h == NULL)
    {
        Branch[0]++;
        return;
    }
    Branch[1]++;
    NumOfCmp++;
    if (len <= 1)
    {
        Branch[2]++;
        return;
    }
    else
    {
        Branch[3]++;
    }

    int minindex, i, j;
    //i是次数，也即排好的个数;j是继续排
    for (i = 0; i < len - 1; ++i)
    {
        NumOfCmp++;
        minindex = i;
        for (j = i + 1; j < len; ++j)
        {
            NumOfCmp++;
            NumOfCmp++;
            if (h[j] < h[minindex])
            {
                Branch[4]++;
                minindex = j;
            }
            else
            {
                Branch[5]++;
            }
        }
        NumOfCmp++;
        NumOfSwap++;
        Swap(h[i], h[minindex]);
    }
    NumOfCmp++;

    return;
}

//希尔排序
void ShellSort(int *h, size_t len)
{
    NumOfCmp++;
    if (h == NULL)
    {
        Branch[0]++;
        return;
    }
    Branch[1]++;
    NumOfCmp++;
    if (len <= 1)
    {
        Branch[2]++;
        return;
    }
    else
    {
        Branch[3]++;
    }

    for (int div = len / 2; div >= 1; div /= 2)
    {
        NumOfCmp++;
        for (int k = 0; k < div; ++k)
        {
            NumOfCmp++;
            for (int i = div + k; i < len; i += div)
            {
                NumOfCmp++;
                for (int j = i; j > k; j -= div)
                {
                    NumOfCmp++;
                    NumOfCmp++;
                    if (h[j] < h[j - div])
                    {
                        Branch[4]++;
                        NumOfSwap++;
                        Swap(h[j], h[j - div]);
                    }
                    else
                    {
                        break;
                        Branch[5]++;
                    }
                }
                NumOfCmp++;
            }
            NumOfCmp++;
        }
        NumOfCmp++;
    }
    NumOfCmp++;

    return;
}

//堆排序
/*
大顶堆sort之后，数组为从小到大排序
*/
//====调整=====
void AdjustHeap(int *h, int node, int len) //----node为需要调整的结点编号，从0开始编号;len为堆长度
{
    int index = node;
    int child = 2 * index + 1;
    while (child < len)
    {
        NumOfCmp++;
        NumOfCmp++;
        //右子树
        if (child + 1 < len && h[child] < h[child + 1])
        {
            Branch[0]++;
            child++;
        }
        else
        {
            Branch[1]++;
        }

        NumOfCmp++;
        if (h[index] >= h[child])
        {
            Branch[2]++;
            break;
        }
        else
            Branch[3]++;
        NumOfSwap++;
        Swap(h[index], h[child]);
        index = child;
        child = 2 * index + 1;
    }
    NumOfCmp++;
}

//====建堆=====
void MakeHeap(int *h, int len)
{
    for (int i = len / 2; i >= 0; --i)
    {
        NumOfCmp++;
        AdjustHeap(h, i, len);
    }
    NumOfCmp++;
}

//====排序=====
void HeapSort(int *h, int len)
{
    MakeHeap(h, len);
    for (int i = len - 1; i >= 0; --i)
    {
        NumOfCmp++;
        NumOfSwap++;
        Swap(h[i], h[0]);
        AdjustHeap(h, 0, i);
    }
    NumOfCmp++;
}

//【黑盒测试】输出未排序数据，再输出排序数据，两相比对；同时输出比较次数和腾挪次数
void BlackBoxTest(int *h, int len)
{
    cout << "Sort:" << endl;
    for (int j = 0; j < numOfNum; ++j)
    {
        cout << h[j] << " ";
    }
    cout << endl;
    cout << "NumOfCompare:" << NumOfCmp << ", NumOfSwap:" << NumOfSwap << endl;
    cout << endl;
}

void ClearBranch()
{
    for (int i = 0; i < NumOfBranch; i++)
        Branch[i] = 0;
}

//【白盒测试】用数据让每个分支都被遍历到
void WhiteBoxTest(int num)
{
    for (int i = 0; i < num; i++)
        cout << "The num Of Branch " << i << " is : " << Branch[i] << endl;
    cout << endl;
}

int main()
{
    //ProduceTestData();
    InitialTestData();
    cout << numOfLine << " " << numOfNum << endl;
    cout << endl;

    cout << "Unsort" << endl;
    for (int i = 0; i < numOfLine; i++)
    {
        for (int j = 0; j < numOfNum; j++)
            cout << TestData[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < numOfLine; i++)
    {
        //插入排序
        /*
        cout<<"InsertSort"<<endl;
        NumOfSwap = 0;
        NumOfCmp = 0;
        ClearBranch();
        InsertSort(TestData[i], numOfNum);
        BlackBoxTest(TestData[i],numOfNum);
        WhiteBoxTest(6);
        */

        //合并排序
        /*
        cout<<"MergeSort"<<endl;
        NumOfSwap = 0;
        NumOfCmp = 0;
        ClearBranch();
        MergeSort(TestData[i],numOfNum);
        BlackBoxTest(TestData[i],numOfNum);
        WhiteBoxTest(10);
        */

        //快速排序
        /*
        cout<<"QuickSort"<<endl;
        NumOfSwap = 0;
        NumOfCmp = 0;
        ClearBranch();
        QuickSort(TestData[i],0,numOfNum);
        BlackBoxTest(TestData[i],numOfNum);
        WhiteBoxTest(8);
        */

        //冒泡排序
        /*
        cout<<"BubbleSort"<<endl;
        NumOfSwap = 0;
        NumOfCmp = 0;
        ClearBranch();
        BubbleSort(TestData[i],numOfNum);
        BlackBoxTest(TestData[i],numOfNum);
        WhiteBoxTest(6);
        */

        //选择排序
        /*
        cout<<"SelectionSort"<<endl;
        NumOfSwap = 0;
        NumOfCmp = 0;
        ClearBranch();
        SelectionSort(TestData[i],numOfNum);
        BlackBoxTest(TestData[i],numOfNum);
        WhiteBoxTest(6);
        */

        //希尔排序
        /*
        cout<<"ShellSort"<<endl;
        NumOfSwap = 0;
        NumOfCmp = 0;
        ClearBranch();
        ShellSort(TestData[i],numOfNum);
        BlackBoxTest(TestData[i],numOfNum);
        WhiteBoxTest(6);
        */

        //堆排序
        /*
        cout<<"HeapSort"<<endl;
        NumOfSwap = 0;
        NumOfCmp = 0;
        ClearBranch();
        HeapSort(TestData[i],numOfNum);
        BlackBoxTest(TestData[i],numOfNum);
        WhiteBoxTest(4);
        */
    }

    system("pause");
    return 0;
}
