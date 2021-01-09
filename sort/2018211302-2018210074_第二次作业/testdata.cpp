#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

int main()
{
    ofstream OutFile("F:\\AlghorthmDesign\\sort\\TestData.txt"); //利用构造函数创建txt文本，并且打开该文本
    int numOfNum, numOfLine;
    cout << "Please input the number of line and the number of data every line." << endl;
    cin >> numOfLine >> numOfNum;
    int arr[numOfNum], T;
    for (int i = 1; i <= numOfNum; i++)
        arr[i] = 0;
    srand(time(NULL));
    while (numOfLine--)
    {

        for (int i = 1; i <= numOfNum; i++)
        {

            arr[i] = rand() % 100;
        }
        for (int i = 1; i <= numOfNum; i++)
        {
            OutFile << arr[i];
            OutFile << " ";
        }
        OutFile << endl;
    }
    OutFile.close();
    cout << "The test data has been produced successfully." << endl;
    system("pause");
    return 0;
}
