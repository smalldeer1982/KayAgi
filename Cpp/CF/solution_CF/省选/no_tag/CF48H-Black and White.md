# Black and White

## 题目描述

题目大意：用如下图的a（全黑），b（全白），c（一个角黑，一个角白）三种1×1大小瓷砖铺一个N×M大小的地板，要求一条地板内部格子边的两边必须同黑或同白。

![](www.luogu.org/upload/pic/16880.png)

瓷砖的输出方法：

全黑：
```
##
##
```
全白：
```
..
..
```
半黑半白：
```
\#
.\

./
/#

\.
#\

#/
/.
```

（依次对应图片中的从左至右6个图案）

## 样例 #1

### 输入

```
2 2
0 0 4
```

### 输出

```
\../
#\/#
\##/
.\/.```

## 样例 #2

### 输入

```
2 3
1 2 3
```

### 输出

```
###/\#
##/..\
#/....
/.....```

# 题解

## 作者：ArrogHie (赞：2)

样例有大问题


------------

## 题解
构造。

最开始我考虑的是左上角填全黑，右下角填全白，后面发现黑与白之间的格子的填法和它们的距离的奇偶性有关，太过麻烦。于是考虑把奇偶性消掉。将全黑全填在左上角，全白的格子在与全黑相隔一个格子的地方填，这样全黑与全白之间的距离全是奇数，能轻易构造。对于其他地方随意构造即可。

## Code
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 110;

int n, m;
int t[N][N], s[N][N];
char str[4][4] = {{'#', '/', '/', '.'}, {'\\', '#', '.', '\\'}, {'.', '/', '/', '#'}, {'\\', '.', '#', '\\'}};

inline bool check(int x, int y)
{
    return t[x + 1][y] == 1 || t[x][y + 1] == 1 || t[x - 1][y] == 1 || t[x][y - 1] == 1;
}

inline void solve(int i, int stay)
{
    int j;
    s[i][stay] = 0;
    for (j = stay + 1; t[i][j] == 3 && j <= m; j++)
        s[i][j] = s[i][j - 1] ^ 1;
    for (; t[i][j] != 3 && j <= m; j++)
        ;
    if (j <= m)
    {
        s[i][j] = 1;
        for (j = j + 1; j <= m; j++)
            s[i][j] = s[i][j - 1] ^ 1;
    }

    i++;
    stay--;
    s[i][stay] = 0;
    for (j = stay - 1; j > 0; j--)
        s[i][j] = s[i][j + 1] ^ 1;
}

// #/ \# ./ \.
// /. .\ /# #\
// 0  1  2  3
inline int get_col(int up, int left)
{
    if (up == -1 && left == -1)
        return 0;
    if (up == -1)
        if ((left >> 1) ^ (left & 1))
            return 0;
        else
            return 1;
    if (left == -1)
        if (up < 2)
            return 2;
        else
            return 0;
    if (up < 2)
        if ((left >> 1) ^ (left & 1))
            return 3;
        else
            return 2;
    if (up >= 2)
        if ((left >> 1) ^ (left & 1))
            return 0;
        else
            return 1;
    return 0;
}

inline void solve2(int stax, int stay)
{
    s[stax][stay] = 2;
    for (int j = stay + 1; j <= m; j++)
        s[stax][j] = s[stax][j - 1] ^ 1;

    stax++;
    s[stax][stay - 1] = 2;
    for (int j = stay - 2; j > 0; j--)
        s[stax][j] = s[stax][j + 1] ^ 1;

    for (int i = stax; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i == stax && j < stay)
                continue;
            s[i][j] = get_col((i - 1) ? s[i - 1][j] : -1, (j - 1) ? s[i][j - 1] : -1);
        }
    }
}

int main()
{
    int a, b, c;
    scanf("%d%d%d%d%d", &n, &m, &a, &b, &c);

    int cnt = a ? 0 : 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a)
                t[i][j] = 1, a--;
            else if (b && !check(i, j))
                t[i][j] = 2, b--;
            else
                t[i][j] = 3;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (t[i][j] == 3 && !cnt)
            {
                solve(i, j), cnt = 1;
                i++;
            }
            if (t[i][j] == 3 && cnt)
                solve2(i, j), cnt = 3;
            if (cnt == 3)
                break;
        }
        if (cnt == 3)
            break;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (t[i][j] != 3)
                printf("%c%c", t[i][j] == 1 ? '#' : '.', t[i][j] == 1 ? '#' : '.');
            else
                printf("%c%c", str[s[i][j]][0], str[s[i][j]][1]);
        }
        puts("");
        for (int j = 1; j <= m; j++)
        {
            if (t[i][j] != 3)
                printf("%c%c", t[i][j] == 1 ? '#' : '.', t[i][j] == 1 ? '#' : '.');
            else
                printf("%c%c", str[s[i][j]][2], str[s[i][j]][3]);
        }
        puts("");
    }
}
```


---

