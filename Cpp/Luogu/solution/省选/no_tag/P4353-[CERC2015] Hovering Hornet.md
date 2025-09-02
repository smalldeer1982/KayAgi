# [CERC2015] Hovering Hornet

## 题目描述

你把一只蜜蜂困在你餐桌上的一个盒子里。但是，你玩的骰子也被困在里面（你无法取回它）不过，你通过计算蜜蜂可以看到的骰子上的预期点数来消磨时间。

蜜蜂、骰子和盒子位于一个三维坐标系中，x-y轴如图

骰子是一个1×1×1的立方体，放在桌子上，底部的中心为原点。因此，其两个相对角的坐标为(−0.5, −0.5,0）和（0.5,0.5,1）。骰子顶部有5个点，南侧1个点，东侧3个点，北侧6个点，西侧4个点，底部2个点（不可见和不相关）。

盒子是一个5×5×5的立方体，也放在桌子上，里面有骰子。该框通过给出其底部的坐标（一个5×5的正方形）来指定。

假设蜜蜂在盒子内没有骰子的（连续）空间中的一个均匀随机点上盘旋。计算蜜蜂可以看到的点数的数量。骰子是不透明的，因此，只有当连接点数中心和蜜蜂位置的部分不与骰子内部相交时，蜜蜂才能看到斑点。

## 样例 #1

### 输入

```
-2.5 -1.5 
2.5 -1.5 
2.5 3.5 
-2.5 3.5```

### 输出

```
10.6854838710```

## 样例 #2

### 输入

```
3 0 
0 4 
-4 1 
-1 -3```

### 输出

```
10.1226478495```

# 题解

## 作者：pigeonteam (赞：1)

# P4353

## 前置知识

两点确定一直线。  

## 题意概述

见[题目翻译](https://www.luogu.com.cn/problem/P4353)。  

## 分析

首先，我们可以将期望变成求对于每一个面，有多少的面积能看到。  
然后，不难发现，对于顶面和底面，提供的期望是固定的。  
然后，考虑如何计算每一个侧面所对应的面将外部大正方形分成两个部分后没有骰子的那部分的体积。  
易得，对于侧面，提供的期望只与外部的大正方体的俯视图有关。  
所以，我们就把这道题转换成了一道二维计算几何。  
发现，这可以转换成一个半平面交问题，然后直接计算即可。~~（可我太弱了不会，只能暴力硬算了）~~。  

## 代码样例

```cpp
#include <bits/stdc++.h>
using namespace std;
double ans = 5 * (5 * 5 * 4); // 顶面
struct Point2D
{
    double x, y;
    // init
    Point2D(double x = 0, double y = 0) : x(x), y(y) {}
    // 重载输入输出流
    friend istream &operator>>(istream &input, Point2D &rhs)
    {
        input >> rhs.x >> rhs.y;
        return input;
    }
    friend ostream &operator<<(ostream &output, Point2D &rhs)
    {
        output << rhs.x << ' ' << rhs.y;
        return output;
    }
} p[4];

struct Vector2D
{
    double x, y;
    // init
    Vector2D(double x, double y) : x(x), y(y) {}
    Vector2D(Point2D from, Point2D to) : x(to.x - from.x), y(to.y - from.y) {}
    Vector2D(Point2D x) : x(x.x), y(x.y) {}
    // 向量点乘
    double operator*(const Vector2D &rhs) const
    {
        return (this->x * rhs.x) + (this->y * rhs.y);
    }
    // 向量叉乘
    double operator&(const Vector2D &rhs) const
    {
        return abs((this->x * rhs.y) - (this->y * rhs.x));
    }
};

constexpr double lambda(Point2D A, Point2D B, double x)
{
    return (A.y - B.y) / (A.x - B.x) * x + (A.x * B.y - A.y * B.x) / (A.x - B.x);
}
constexpr double lambda2(Point2D A, Point2D B, double y)
{
    return (A.x - B.x) / (A.y - B.y) * y + (A.x * B.y - A.y * B.x) / (B.y - A.y);
}

// @brief get y by x
pair<Point2D, Point2D> get_x(double x)
{
    double k[4];
    for (int i = 0; i < 4; ++i)
    {
        k[i] = lambda(p[i], p[(i + 1) % 4], x);
    }
    sort(k, k + 4, greater<double>());
    return {{x, k[1]}, {x, k[2]}};
}

// @brief get x by y
pair<Point2D, Point2D> get_y(double y)
{
    double k[4];
    for (int i = 0; i < 4; ++i)
    {
        k[i] = lambda2(p[i], p[(i + 1) % 4], y);
    }
    sort(k, k + 4, greater<double>());
    return {{k[1], y}, {k[2], y}};
}

int main()
{
    cin >> p[0] >> p[1] >> p[2] >> p[3];
    // 处理当与坐标轴平行的情况
    if ((p[1].x == p[0].x && p[1].y == p[2].y) || (p[1].y == p[0].y && p[1].x == p[2].x))
    {
        double l = min({p[0].x, p[1].x, p[2].x, p[3].x}),
               r = max({p[0].x, p[1].x, p[2].x, p[3].x}),
               u = max({p[0].y, p[1].y, p[2].y, p[3].y}),
               d = min({p[0].y, p[1].y, p[2].y, p[3].y});
        ans += 25. * ((u - 0.5) * 6 + (-0.5 - d));
        ans += 25. * ((r - 0.5) * 3 + (-0.5 - l) * 4);
    }
    else
    {
        // 东面
        auto ak = get_x(0.5);
        int pos = 0;
        double siz = 0;
        while (p[pos % 4].x >= 0.5)
            ++pos;
        while (p[pos % 4].x <= 0.5)
            ++pos;
        ++pos;
        while (p[pos % 4].x >= 0.5)
        {
            siz += Vector2D(ak.second, p[pos % 4]) & Vector2D(ak.second, p[(pos - 1) % 4]);
            ++pos;
        }
        siz += Vector2D(ak.second, p[(pos - 1) % 4]) & Vector2D(ak.second, ak.first);
        siz /= 2;
        siz *= 3;
        siz *= 5;
        ans += siz;

        // 西面
        siz = 0, pos = 0;
        ak = get_x(-0.5);
        while (p[pos % 4].x <= -0.5)
            ++pos;
        while (p[pos % 4].x >= -0.5)
            ++pos;
        ++pos;
        while (p[pos % 4].x <= -0.5)
        {
            siz += Vector2D(ak.first, p[pos % 4]) & Vector2D(ak.first, p[(pos - 1) % 4]);
            ++pos;
        }
        siz += Vector2D(ak.first, p[(pos - 1) % 4]) & Vector2D(ak.first, ak.second);
        siz /= 2;
        siz *= 4;
        siz *= 5;
        ans += siz;

        // 北面
        siz = 0, pos = 0;
        ak = get_y(0.5);
        while (p[pos % 4].y >= 0.5)
            ++pos;
        while (p[pos % 4].y <= 0.5)
            ++pos;
        ++pos;
        while (p[pos % 4].y >= 0.5)
        {
            siz += Vector2D(ak.first, p[pos % 4]) & Vector2D(ak.first, p[(pos - 1) % 4]);
            ++pos;
        }
        siz += Vector2D(ak.first, p[(pos - 1) % 4]) & Vector2D(ak.first, ak.second);
        siz /= 2;
        siz *= 6;
        siz *= 5;
        ans += siz;

        // 南面
        siz = 0, pos = 0;
        ak = get_y(-0.5);
        while (p[pos % 4].y <= -0.5)
            ++pos;
        while (p[pos % 4].y >= -0.5)
            ++pos;
        ++pos;
        while (p[pos % 4].y <= -0.5)
        {
            siz += Vector2D(ak.second, p[pos % 4]) & Vector2D(ak.second, p[(pos - 1) % 4]);
            ++pos;
        }
        siz += Vector2D(ak.second, p[(pos - 1) % 4]) & Vector2D(ak.second, ak.first);
        siz /= 2;
        siz *= 1;
        siz *= 5;
        ans += siz;
    }
    printf("%.10lf", ans / 124.0);
    return 0;
}
```  

由于我用的是点斜式表示直线，所以需要考虑直线与坐标轴垂直的情况，写了个特判。

---

