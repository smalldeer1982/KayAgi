# Hexagons

## 题目描述

Ayrat is looking for the perfect code. He decided to start his search from an infinite field tiled by hexagons. For convenience the coordinate system is introduced, take a look at the picture to see how the coordinates of hexagon are defined:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF615E/7260dcf1ee40fd1194e895987c69d1d7c92f50b5.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF615E/91f722e14e3f2875c1cec2e05543b6613c3b2f75.png) Ayrat is searching through the field. He started at point $ (0,0) $ and is moving along the spiral (see second picture). Sometimes he forgets where he is now. Help Ayrat determine his location after $ n $ moves.

## 样例 #1

### 输入

```
3
```

### 输出

```
-2 0
```

## 样例 #2

### 输入

```
7
```

### 输出

```
3 2
```

# 题解

## 作者：OIer_ACMer (赞：1)

本题是一道推理题，比较简单。

# 思路解析：

首先，我们观察图像，发现每转一次六边形走过的次数都会加 $6$，这样，我们就可以二分找出此时是第几个周期。

之后，我们观察坐标，发现几个坐标变化规律（起点的横坐标是层数减 $1$ 的两倍，纵坐标为 $0$）：

1. 第一次往右上方走时横坐标加 $1$，纵坐标加 $2$，次数总是 $1$ 次；
2. 往左上走，横坐标减 $1$，纵坐标加 $2$，次数是此时的层数减 $1$；
3. 之后，往左边走是横坐标减 $2$，纵坐标不变，次数是此时的层数的值；
4. 往左下走，每次横坐标减 $1$，纵坐标减 $2$，次数是层数的值；
5. 往右下走，每次横坐标加 $1$，纵坐标减 $2$，次数是层数的值；
6. 往右边走，每次横坐标加 $2$，次数是此时的层数的值；
7. 往右上方走，每次横坐标加 $1$，纵坐标加 $2$，次数是此时的层数的值。

综上所述，我们找到此时的层数后直接对坐标处理就行了。

# 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
bool check(int mid)
{
    if (((1 + mid) * mid / 2) * 6 < n)
    {
        return 1;
    }
    return 0;
}
signed main()
{
    // n = 1;
    // while (1)
    // {
    cin >> n;
    int l = 1, r = 2e9 + 10;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    int cs = l, yi = 1, er = cs, san = 2 * cs, si = 3 * cs, wu = 4 * cs, liu = 5 * cs, qi = 6 * cs, res = n - (((1 + (cs - 1)) * (cs - 1) / 2) * 6);
    int x = 2 * (cs - 1), y = 0;
    if (res == 0)
    {
        cout << x << ' ' << y;
        return 0;
    }
    if (res > 0 && res <= yi)
    {
        cout << x + 1 << ' ' << y + 2;
        return 0;
    }
    if (res >yi && res <= er)
    {
        x += 1;
        y += 2;
        cout << x - (res - yi) << ' ' << y + 2 * (res - yi);
        return 0;
    }
    if (res > er && res <= san)
    {
        x += 1;
        y += 2;
        x -= (cs - 1);
        y += 2 * (cs - 1);
        cout << x - 2 * (res - er) << ' ' << y;
        return 0;
    }
    if (res > san && res <= si)
    {
        x += 1;
        y += 2;
        x -= (cs - 1);
        y += 2 * (cs - 1);
        x -= 2 * cs;
        cout << x - (res - san) << ' ' << y - 2 * (res - san);
        return 0;
    }
    if (res > si && res <= wu)
    {
        x += 1;
        y += 2;
        x -= (cs - 1);
        y += 2 * (cs - 1);
        x -= 2 * cs;
        x -= cs;
        y -= 2 * cs;
        cout << x + (res - si) << ' ' << y - 2 * (res - si);
        return 0;
    }
    if (res > wu && res <= liu)
    {
        x += 1;
        y += 2;
        x -= (cs - 1);
        y += 2 * (cs - 1);
        x -= 2 * cs;
        x -= cs;
        y -= 2 * cs;
        x += cs;
        y -= 2 * cs;
        cout << x + 2 * (res - wu) << ' ' << y;
        return 0;
    }
    if (res > liu && res <= qi)
    {
        x += 1;
        y += 2;
        x -= (cs - 1);
        y += 2 * (cs - 1);
        x -= 2 * cs;
        x -= cs;
        y -= 2 * cs;
        x += cs;
        y -= 2 * cs;
        x += 2 * cs;
        cout << x + (res - liu) << ' ' << y + 2 * (res - liu);
        return 0;
    }
    // }
    return 0;
}
```

---

