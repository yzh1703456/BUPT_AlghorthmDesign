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

int numOfNum, numOfLine; //测试数据组数，每组数据量
int TestData[MaxLineNum][MaxDataNum] = {0};

void ProduceTestData()
{
    ofstream OutFile("F:\\AlghorthmDesign\\sort\\TestData.txt"); //利用构造函数创建txt文本，并且打开该文本

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
    int pc = 0;
    if (h == NULL)
    {
        pc++;
        return;
    }
    if (len <= 1)
    {
        pc++;
        return;
    }

    int i, j;
    //i是次数，也即排好的个数;j是继续排
    for (i = 1; i < len; ++i)
    {
        pc++;
        for (j = i; j > 0; --j)
        {
            pc++;
            if (h[j] < h[j - 1])
            {
                Swap(h[j], h[j - 1]);
                pc++;
                pc++; //判断和交换
            }
            else
                break;
        }
    }

    cout << "Insert Sort Time:" << pc << endl;
    return;
}

//合并排序
void MergeArray(int *arr, size_t left, size_t mid, size_t right, int *temp, int &pc)
{
    if (arr == NULL)
    {
        pc++;
        return;
    }

    size_t i = left, j = mid + 1, k = 0;
    pc += 3;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
            pc++;
            pc++;
            continue;
        }

        temp[k++] = arr[j++];
        pc++;
        pc++; //while判断次数
    }

    while (i <= mid)
    {
        temp[k++] = arr[i++];
        pc++;
        pc++;
    }

    while (j <= right)
    {
        temp[k++] = arr[j++];
        pc++;
        pc++;
    }

    memcpy(&arr[left], temp, k * sizeof(int));

    return;
}

void MMergeSort(int *arr, size_t left, size_t right, int *temp, int &pc)
{
    if (left < right)
    {
        size_t mid = (left + right) / 2;
        pc++;
        MMergeSort(arr, left, mid, temp, pc);
        MMergeSort(arr, mid + 1, right, temp, pc);
        MergeArray(arr, left, mid, right, temp, pc);
        pc++;
    }
}

void MergeSort(int *h, size_t len)
{
    int pc = 0;
    if (h == NULL)
    {
        pc++;
        return;
    }
    if (len <= 1)
    {
        pc++;
        return;
    }
    int *temp = (int *)calloc(len, sizeof(int));
    MMergeSort(h, 0, len - 1, temp, pc);

    memcpy(h, temp, sizeof(int) * len);

    free(temp);

    cout << "Merge Sort Time:" << pc << endl;
    return;
}

//快速排序，随机选取哨兵放前面
void QuickSort(int *h, int left, int right)
{
    int pc = 0;
    if (h == NULL)
    {
        pc++;
        return;
    }
    if (left >= right)
    {
        pc++;
        return;
    }

    //防止有序队列导致快速排序效率降低
    srand((unsigned)time(NULL));
    int len = right - left;
    int kindex = rand() % (len + 1) + left;
    Swap(h[left], h[kindex]);
    pc += 3;

    int key = h[left], i = left, j = right;
    pc += 3;
    while (i < j)
    {
        while (h[j] >= key && i < j)
        {
            --j;
            pc++;
        }
        if (i < j)
        {
            h[i] = h[j];
            pc++;
            pc++;
        }
        while (h[i] < key && i < j)
        {
            ++i;
            pc++;
            pc++;
        }
        if (i < j)
        {
            h[j] = h[i];
            pc++;
            pc++;
        }
        pc++;
    }

    h[i] = key;
    pc++;

    //QuickSort(&h[left],0,i-1);
    //QuickSort(&h[j+1],0,right-j-1);

    QuickSort(h, left, i - 1);
    QuickSort(h, j + 1, right);
    cout << "Quick Sort Time:" << pc << endl;
}

//冒泡排序
void BubbleSort(int *h, size_t len)
{
    int pc = 0;
    if (h == NULL)
    {
        pc++;
        return;
    }
    if (len <= 1)
    {
        pc++;
        return;
    }
    //i是次数，j是具体下标
    for (int i = 0; i < len - 1; ++i)
    {
        for (int j = 0; j < len - 1 - i; ++j)
        {
            if (h[j] > h[j + 1])
            {
                Swap(h[j], h[j + 1]);
                pc++;
                pc++;
            }
            pc++;
        }
        pc++;
    }

    cout << "Bubble Sort Time:" << pc << endl;
    return;
}

//选择排序
void SelectionSort(int *h, size_t len)
{
    int pc = 0;
    if (h == NULL)
    {
        pc++;
        return;
    }
    if (len <= 1)
    {
        pc++;
        return;
    }

    int minindex, i, j;
    //i是次数，也即排好的个数;j是继续排
    for (i = 0; i < len - 1; ++i)
    {
        minindex = i;
        pc++;
        for (j = i + 1; j < len; ++j)
        {
            if (h[j] < h[minindex])
            {
                minindex = j;
                pc++;
                pc++;
            }
            pc++;
        }
        Swap(h[i], h[minindex]);
        pc++;
        pc++;
    }

    cout << "Select Sort Time:" << pc << endl;

    return;
}

//希尔排序
void ShellSort(int *h, size_t len)
{
    int pc = 0;
    if (h == NULL)
    {
        pc++;
        return;
    }
    if (len <= 1)
    {
        pc++;
        return;
    }

    for (int div = len / 2; div >= 1; div /= 2)
    {
        pc++;
        for (int k = 0; k < div; ++k)
        {
            pc++;
            for (int i = div + k; i < len; i += div)
            {
                pc++;
                for (int j = i; j > k; j -= div)
                {
                    if (h[j] < h[j - div])
                        {
                            Swap(h[j], h[j - div]);
                            pc++;
                        }
                    else
                        break;
                    pc++;
                    pc++;
                }
            }
        }
    }

    cout << "Shell Sort Time:" << pc << endl;
    return;
}

//堆排序
/*
大顶堆sort之后，数组为从小到大排序
*/
//====调整=====
void AdjustHeap(int *h, int node, int len,int &pc) //----node为需要调整的结点编号，从0开始编号;len为堆长度
{
    int index = node;
    int child = 2 * index + 1; //
    pc+=2;
    while (child < len)
    {
        pc++;
        //右子树
        if (child + 1 < len && h[child] < h[child + 1])
        {
            pc++;
            child++;
            pc++;
        }
        if (h[index] >= h[child])
            {
                pc++;
                break;
            }
        Swap(h[index], h[child]);
        pc++;
        index = child;
        child = 2 * index + 1;
        pc++;
        pc++;
    }
}

//====建堆=====
void MakeHeap(int *h, int len,int &pc)
{
    for (int i = len / 2; i >= 0; --i)
    {
        pc++;
        pc++;
        AdjustHeap(h, i, len,pc);
    }
}

//====排序=====
void HeapSort(int *h, int len)
{
    int pc=0;
    MakeHeap(h, len,pc);
    for (int i = len - 1; i >= 0; --i)
    {
        Swap(h[i], h[0]);
        AdjustHeap(h, 0, i,pc);
        pc++;
        pc++;
    }
    cout << "Heap Sort Time:" << pc << endl;
}

int main()
{
    ProduceTestData();
    cout << numOfLine << " " << numOfNum << endl;
    cout << endl;

    //【黑盒测试】输出未排序数据，再输出排序数据，两相比对即可。
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
        //InsertSort(TestData[i],numOfNum);

        //合并排序
        //MergeSort(TestData[i],numOfNum);

        //快速排序
        //QuickSort(TestData[i],0,numOfNum); cout<<"A QuickSort is over"<<endl<<endl; //存在递归调用，通过这种方式区分计数

        //冒泡排序
        //BubbleSort(TestData[i],numOfNum);

        //选择排序
        //SelectionSort(TestData[i],numOfNum);

        //希尔排序排序
        //ShellSort(TestData[i],numOfNum);

        //堆排序
        //HeapSort(TestData[i],numOfNum);
    }
    cout<<endl;
    cout << "Sort" << endl;
    for (int i = 0; i < numOfLine; i++)
    {
        for (int j = 0; j < numOfNum; ++j)
        {
            cout << TestData[i][j] << " ";
        }
        cout << endl;
    }

    system("pause");
    return 0;
}
