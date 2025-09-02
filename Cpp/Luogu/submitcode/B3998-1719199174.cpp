#include <iostream>
#include <string>
using namespace std;

int main() 
{
    int n, sum = 0;
    char a[105];
    for (int i = 0; i < 105; i++) 
    {
        a[i] = ' ';
    }
    string b;
    cin >> n;
    int current_index = 0;

    for (int i = 0; i < n; i++) 
    {
        cin >> b;
        if (b == "<bs>") 
        {
            if (current_index > 0) // 确保在退格时不删除空字符串的内容
            {
                a[current_index - 1] = ' ';
                current_index--; // 删除最后一个字符并更新索引
            }
        } 
        else 
        {
            a[current_index] = b[0];
            current_index++; // 添加字符并更新索引
        }
    }

    for (int i = 0; i < current_index; i++) 
    {
        if (a[i] != ' ') 
        {
            cout << a[i];
        }
    }
    cout << endl;

    return 0;
}
