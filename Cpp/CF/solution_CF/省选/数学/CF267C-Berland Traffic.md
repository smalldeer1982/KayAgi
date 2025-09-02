# Berland Traffic

## 题目描述

Berland traffic is very different from traffic in other countries. The capital of Berland consists of $ n $ junctions and $ m $ roads. Each road connects a pair of junctions. There can be multiple roads between a pair of junctions. For each road we know its capacity: value $ c_{i} $ is the maximum number of cars that can drive along a road in any direction per a unit of time. For each road, the cars can drive along it in one of two direction. That it, the cars can't simultaneously move in both directions. A road's traffic is the number of cars that goes along it per a unit of time. For road ( $ a_{i},b_{i} $ ) this value is negative, if the traffic moves from $ b_{i} $ to $ a_{i} $ . A road's traffic can be a non-integer number.

The capital has two special junctions — the entrance to the city (junction 1) and the exit from the city (junction $ n $ ). For all other junctions it is true that the traffic is not lost there. That is, for all junctions except for 1 and $ n $ the incoming traffic sum equals the outgoing traffic sum.

Traffic has an unusual peculiarity in the capital of Berland — for any pair of junctions ( $ x,y $ ) the sum of traffics along any path from $ x $ to $ y $ doesn't change depending on the choice of the path. Such sum includes traffic along all roads on the path (possible with the "minus" sign, if the traffic along the road is directed against the direction of the road on the path from $ x $ to $ y $ ).

Your task is to find the largest traffic that can pass trough the city per one unit of time as well as the corresponding traffic for each road.

## 样例 #1

### 输入

```
2
3
1 2 2
1 2 4
2 1 1000
```

### 输出

```
6.00000
2.00000
2.00000
-2.00000
```

## 样例 #2

### 输入

```
7
11
1 2 7
1 2 7
1 3 7
1 4 7
2 3 7
2 5 7
3 6 7
4 7 7
5 4 7
5 6 7
6 7 7
```

### 输出

```
13.00000
2.00000
2.00000
3.00000
6.00000
1.00000
3.00000
4.00000
7.00000
1.00000
2.00000
6.00000
```

# 题解

## 作者：_slb (赞：4)

## Description

给定一张 $n$ 点 $m$ 边的无向的网络流，源点为 $1$，汇点为 $n$。

第 $i$ 条边用**有序**数对 $(a_i,b_i) (a_i\not= b_i)$ 和容量值 $c_i$ 描述，表示连接 $a_i$ 与 $b_i$，容量为 $c_i$。

你应当给这条边赋一个实数流量 $x_i$，满足 $|x_i|\le c_i$，如果是正的表示从 $a_i$ 流向 $b_i$ 大小为 $x_i$，否则表示从 $b_i$ 流向 $a_i$ 大小为 $-x_i$。

你构造的流需要满足：

- 流守恒。即对所有不为 $1$ 或 $n$ 的点 $u$，进入 $u$ 的流等于从 $u$ 出去的流。

- 对任意两个连通的节点 $x,y$，从 $x$ 到 $y$ 的所有路径 $x_i$（流量）的和都是相等的。

现在请输出最大流（可以理解为 $\sum_v x_{1,v}$），并构造一个方案。

$1\leq n\leq100,1\leq m\leq5000$。

## Solution

这个题看上去挺莫名其妙的。把样例二画出来：

[![sample](https://s4.ax1x.com/2021/12/25/TU3Hl6.png)](https://imgtu.com/i/TU3Hl6)

看看这个图，和红的数字，似乎能发现什么东西...

我们给每个点一个高度（即图中红色的数字）。

根据第二个要求，任意两点之间，不管怎么走，高度的差值是一定的，而相邻两点高度差值就是这条边的流量。

再仔细想一想，在这道题中，图的形态固定，每条边的流量应该是有一个固定的比例的。

根据第一个要求：每个点出的流量和入的流量相等。

设 $out(i)$ 表示 $i$ 连向的点，$in(i)$ 表示连向 $i$ 的点，可以列出来一个方程：$\sum (h_i-h_{in(i)})=\sum(h_{out(i)}-h_i)$。

那么总共有 $n-2$ 个方程。

因为我们实际上是想要求流量，那么源点和汇点高度具体的值是无所谓的，减一下都会按照比例消掉。

我们自己设一下源点和汇点高度。

这样总共就有 $n$ 个方程，我们就可以解出来所有点的高度。（高斯消元）

很显然，如果我们把所有点高度都按照一定比例缩放，这两个限制仍然是成立的。

我们找到能缩放的最大比例，然后进行缩放，就得到了最大流（即和汇点相连的边的流量之和）和每条边的流量。

重边是不用特殊处理的。

复杂度是高斯消元的 $O(n^3)$。

## Code

注意除以 $0$。

```cpp
#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

const int maxn = 110;
const double eps = 1e-8;

int e[maxn][maxn], n, m;

inline double change(double x) { return x < eps ? eps : x; }

double a[maxn][maxn];
double root[maxn];

void guass()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
                continue;
            if (fabs(a[i][i]) < eps)
                continue;
            double d = a[j][i] / a[i][i];
            for (int k = i; k <= n + 1; k++)
                a[j][k] -= a[i][k] * d;
        }
    }
    for (int i = 1; i <= n; i++)
        if (fabs(a[i][i]) > eps)
            root[i] = a[i][n + 1] / a[i][i];
}

struct edge
{
    int x, y;
    double cap;
};
std::vector<edge> edges;

inline void add(int x, int y, double cap)
{
    edges.push_back({x, y, cap});
    if (x != 1 && x < n)
        a[x][x]--, a[x][y]++;
    if (y != 1 && y < n)
        a[y][y]--, a[y][x]++;
}
    
int main()
{
    cin >> n >> m;
    double c;
    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y >> c, add(x, y, c);
    a[1][n + 1] = 1, a[n][n + 1] = n + 1, a[1][1] = 1, a[n][n] = 1;
    guass();
    double mul = 1e18;
    int flag = 0;
    for (auto k : edges)
    {
        if (fabs(root[k.y] - root[k.x]) < eps)
            continue;
        mul = std::min(mul, 1.0 * k.cap / fabs(root[k.y] - root[k.x])), flag = 1;
    }
    if (!flag)
        mul = 0;
    for (int i = 1; i <= n; i++)
        root[i] *= mul;
    double sum = 0;
    for (auto k : edges)
        if (k.x == n || k.y == n)
            sum += fabs(root[k.y] - root[k.x]);
    printf("%lf\n", sum);
    for (auto k : edges)
        printf("%lf\n", root[k.y] - root[k.x]);
}
```



---

