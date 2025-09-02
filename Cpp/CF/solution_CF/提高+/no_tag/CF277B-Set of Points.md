# Set of Points

## 题目描述

Convexity of a set of points on the plane is the size of the largest subset of points that form a convex polygon. Your task is to build a set of $ n $ points with the convexity of exactly $ m $ . Your set of points should not contain three points that lie on a straight line.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
0 0
3 0
0 3
1 1
```

## 样例 #2

### 输入

```
6 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
6 6
```

### 输出

```
10 0
-10 0
10 1
9 1
9 -1
0 -2
```

## 样例 #4

### 输入

```
7 4
```

### 输出

```
176166 6377
709276 539564
654734 174109
910147 434207
790497 366519
606663 21061
859328 886001
```

# 题解

## 作者：FP·荷兰猪 (赞：2)

我们可以以(0,0) 为基础点 构造出 相邻两点斜率不断增加的图形，如 (1,1) (2,3) (3,6) ...构造出m个后 剩余n-m个对称的构造出来就行了，注意的是 最高点要多输出一次，不能到达最高后，接着往下输出，否则如果m==n/2 的话，按照右半部分，就会有m+1个点构成凸多边形，还有就是注意三点不要在一条直线上，因为m<=100 前m个点两点间最大斜率为99 所以在第m+1个点的x在 10000之后就可以了，就这个地方没注意到，老是错....

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    if(m==3&&(n>4))
    {
        printf("-1\n");
        return 0;
    }
    int cnt=0,y=0;
    for(int i=0;i<m;i++)
        printf("%d %d\n",i,y=y+cnt++);
    if(m<n) printf("%d %d\n",m+100000,y);
    for(int i=m+1;i<n;i++)
        printf("%d %d\n",i+100000,y=y-(--cnt));
    return 0;
}
```

---

## 作者：Dehydration (赞：1)

### 前言：

第一眼看到**凸包**两个字吓得个半死，我还不会做啊，但定睛一看，原来是个构造题，我在行！

ps：[博客](https://www.luogu.com.cn/blog/661534/)，[题目](https://www.luogu.com.cn/problem/CF277B)。

### 思路：

首先，题目并不是求凸包上的顶点数，而是求能形成的凸多边形的最大顶点数，直接构造（打表）。

常识，凸函数上的点都能构成凸多边形。

将 $m$ 个点置于 $y=x_1+100000$，将 $n-m$ 置于 $y=(-x_2)-100000$，由于 $m≥\frac{n}{2}$，此时凸度就是 $m$  了。

注意特判 $m=3$，因为从两条曲线上各取两点凸度就是 $4$   了。

### 代码：

```
#include<bits/stdc++.h>
using namespace std;
int n, m;//定义 
int main()
{
    cin>>n>>m;//输入 
    if(m == 3)//特判 
    {
        if(n==4)
        {
            printf("0 0\n3 0\n0 3\n1 1\n");//有答案 
            return 0;
        }
        if(n >= 5)
        {
            printf("-1\n");//无法 
            return 0;
        }
    }
    for(int i = 0;i < m;i++)  cout<<i<<' '<< 100000+i*i<<'\n';//构造的/qq 
    for(int i = 0;i < n-m;i++)  cout<<i<<' '<< 0-i*i-100000<<'\n';//因为 -i*i-100000 ,我加了个0-i*i-100000 
    return 0;
}
```

### 完美撒花！

---

