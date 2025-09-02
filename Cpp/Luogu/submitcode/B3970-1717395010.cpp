#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a[20], k;
    char str[20];
    cin >> str >> k;
    int n = strlen(str);

    bool leadingZero = true;
    for (int i = 0; i < n; i++)
    {
        a[i] = (str[i] - '0') % k;
    }

    for (int i = 0; i < n; i++)
    {
        if (a[i] != 0 || !leadingZero)
        {
            cout << a[i];
            leadingZero = false;
        }
    }

    // 如果全为零
    if (leadingZero) 
    {
        cout << "0";
    }

    return 0;
}