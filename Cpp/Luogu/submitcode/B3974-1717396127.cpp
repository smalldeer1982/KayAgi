#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, p, q, miny = INT_MAX, x, y;
    bool flag = false;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] != 1)
        {
            flag = true;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        if (b[i] != 1)
        {
            flag = true;
        }
    }
    cin >> p >> q;

    if (!flag)
    {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (p == 0 && i == (q - 1))
        {
            continue;
        }
        if (a[i] == 0)
        {
            if (abs(q - 1 - i) < miny || (abs(q - 1 - i) == miny && p == 0))
            {
                miny = abs(q - 1 - i);
                x = 0;
                y = i + 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (p == 1 && i == (q - 1))
        {
            continue;
        }
        if (b[i] == 0)
        {
            if (abs(q - 1 - i) < miny || (abs(q - 1 - i) == miny && p == 1))
            {
                miny = abs(q - 1 - i);
                x = 1;
                y = i + 1;
            }
        }
    }

    cout << x << " " << miny << endl;
    return 0;
}
