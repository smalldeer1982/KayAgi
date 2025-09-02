# Special Olympics

## 题目描述

A renowned abstract artist Sasha, drawing inspiration from nowhere, decided to paint a picture entitled "Special Olympics". He justly thought that, if the regular Olympic games have five rings, then the Special ones will do with exactly two rings just fine.

Let us remind you that a ring is a region located between two concentric circles with radii $ r $ and $ R $ $ (r&lt;R) $ . These radii are called internal and external, respectively. Concentric circles are circles with centers located at the same point.

Soon a white canvas, which can be considered as an infinite Cartesian plane, had two perfect rings, painted with solid black paint. As Sasha is very impulsive, the rings could have different radii and sizes, they intersect and overlap with each other in any way. We know only one thing for sure: the centers of the pair of rings are not the same.

When Sasha got tired and fell into a deep sleep, a girl called Ilona came into the room and wanted to cut a circle for the sake of good memories. To make the circle beautiful, she decided to cut along the contour.

We'll consider a contour to be a continuous closed line through which there is transition from one color to another (see notes for clarification). If the contour takes the form of a circle, then the result will be cutting out a circle, which Iona wants.

But the girl's inquisitive mathematical mind does not rest: how many ways are there to cut a circle out of the canvas?

## 说明/提示

Figures for test samples are given below. The possible cuts are marked with red dotted line.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF199B/f6b80d43e3ef1e929ab8f5af0b211e93ea4d386a.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF199B/5e144d7158ec39b95e73e197fcc3c0319bf3cf78.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF199B/a3ad867f0752e7a06a2c050bd00ad9db2313f977.png)

## 样例 #1

### 输入

```
60 60 45 55
80 80 8 32
```

### 输出

```
1```

## 样例 #2

### 输入

```
60 60 45 55
80 60 15 25
```

### 输出

```
4```

## 样例 #3

### 输入

```
50 50 35 45
90 50 35 45
```

### 输出

```
0```

# 题解

## 作者：npqenqpve (赞：3)

### 思路：
显然答案至多是 $4$ ，那么对每个圆都判断一下即可。

每个圆肯定不会受到跟它组成环的那个圆的影响，问题转化为判断每一个圆和另一个环的关系。所以只有圆内含外环，内环内含圆，圆和外环相离是合法的。

具体而言：

设圆心距为 $d$  ，两圆半径分别 $r_1$，$r_2$ 

内含：$d\leq r_1-r_2$

相离：$r_1+r_2\leq d$

直接统计即可。
### 代码：
```cpp
#include<bits/stdc++.h>
#define double long double
#define int long long
using namespace std;
struct node
{
    int x,y,a,b;
}p1,p2;
int dis(int a,int b,int x,int y)
{
    return (a-x)*(a-x)+(b-y)*(b-y);
}
bool check(double d,int r,int r1,int r2)// r 圆半径  r1 环内 r2 环外
{
    // cout<<(d<=r1-r)<<" "<<(d<=r-r2)<<" "<<(d>=r+r2)<<"\n";
    if((d<=r1-r)||(d<=r-r2)||(d>=r+r2)) return 1;
    return 0;
}
signed main()
{
    cin>>p1.x>>p1.y>>p1.a>>p1.b;
    cin>>p2.x>>p2.y>>p2.a>>p2.b;
    int ans=0;
    double d=sqrt(dis(p1.x,p1.y,p2.x,p2.y));
    ans=check(d,p1.a,p2.a,p2.b)+check(d,p1.b,p2.a,p2.b)+check(d,p2.a,p1.a,p1.b)+check(d,p2.b,p1.a,p1.b);
    cout<<ans;
}
```

---

## 作者：dutianchen1 (赞：0)

# CF199B Special Olympics
------------
## 思路
经过分析容易发现，我们要找到的圆都是不被其他线所经过的完整的圆。所以答案数只会 $ \le 4$。
于是我们思考怎么样才算一个完整的圆。

首先我们计算出圆心距 $dis = \sqrt{ (x_1-x_2) ^ 2 + (y_1-y_2) ^ 2} $。

对于其中任意一个圆环中内圆或外圆，我们在画图后可以发现以下三个条件：

- 当前圆的半径 $r$ 与另一圆环的外圆半径 $R$ 之和小于等于 $dis$。（两者不相交）。

- 当前圆的半径 $r$ 与另一圆环的外圆半径 $R$之差大于等于 $dis$。（较大者包含较小者）。

- 当前圆的半径 $r$ 与另一圆环的内圆半径 $R'$ 之差大于等于 $dis$。（较大者包含较小者）。

这三个条件满足任意一个，这个圆就算完整的圆。

注意，圆心距 $dis$ 得用 ```double``` 类型维护。

------------
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
double dis;
int ans;
int cnt(int a,int b,int c)
{
	return a+c<=dis||a-c>=dis||b-a>=dis;
}
int x,y,r,R;
int xx,yy,rr,RR;

int main()
{
	cin.tie(0);cout.tie(0);
	x=read();y=read();r=read();R=read();
	xx=read();yy=read();rr=read();RR=read();
	dis=sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));//计算圆心之间距离
	if(cnt(r,rr,RR))ans++;
	if(cnt(R,rr,RR))ans++;
	if(cnt(rr,r,R))ans++;
	if(cnt(RR,r,R))ans++; 
	cout<<ans<<'\n';
	return 0;
}
/*
0 0 50 70
1 0 60 80


-64 -47 20 40
-5 -37 79 100
*/
```

---

## 作者：Special_Tony (赞：0)

# 思路
枚举每个圆半径 $a$ 和另一组中的圆环内外圆的半径 $b,c$，设 $x$ 为圆心距 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$，若 $a+c\le x$，说明 $a$ 和 $c$ 没有相交，合法；若 $a-c\ge x$，则说明 $a$ 包含了 $c$，合法；若 $b-a\ge x$，说明 $b$ 包含 $a$，也合法。
# 思路
```cpp
# include <bits/stdc++.h>
using namespace std;
int x_1, y_1, r_1, R_1, x_2, y_2, r_2, R_2;
double x;
int f (int& a, int& b, int& c) {
	return a + c <= x || x <= a - c || x <= b - a;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> x_1 >> y_1 >> r_1 >> R_1 >> x_2 >> y_2 >> r_2 >> R_2;
	x = sqrt ((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
	cout << f (r_1, r_2, R_2) + f (R_1, r_2, R_2) + f (r_2, r_1, R_1) + f (R_2, r_1, R_1);
	return 0;
}
```

---

## 作者：LogicLiu (赞：0)

# 题解
## 题目描述
这个问题是一个几何问题，我们需要找出在两个不同心的环形区域中，最多可以找到多少个完整的圆形轮廓。

每个环形区域由一个中心点和两个半径定义，中心点的坐标为 $(x, y)$ ，两个半径分别为 $r$ 和 $R$ 。

## 算法思路
这个问题的关键在于理解如何判断两个环形区域之间的关系，以及如何从这些环形区域中找出完整的圆形轮廓。

首先，我们需要计算两个环形区域的中心点之间的距离，这可以通过欧几里得距离公式来实现。

然后，我们需要判断两个环形区域之间的关系。这可以通过比较两个环形区域的半径和它们的中心点之间的距离来实现。具体来说，我们需要检查以下三种情况：

1. 两个环形区域的中心点之间的距离小于或等于两个环形区域的内半径之差。这意味着一个环形区域完全包含在另一个环形区域内，因此我们可以从这个环形区域中找出一个完整的圆形轮廓。

2. 两个环形区域的中心点之间的距离小于或等于一个环形区域的内半径和另一个环形区域的外半径之差。这意味着一个环形区域的内圆和另一个环形区域的外圆相交，因此我们可以从这两个环形区域的交集中找出一个完整的圆形轮廓。

3. 两个环形区域的中心点之间的距离大于或等于两个环形区域的外半径之和。这意味着两个环形区域完全分离，因此我们可以从每个环形区域中分别找出一个完整的圆形轮廓。

最后，我们需要对每个环形区域的内半径和外半径，分别与另一个环形区域的内半径和外半径进行上述的判断，将满足条件的情况累加到结果中。

## 算法原理
首先，我们定义了一个结构体 ```Circle``` 来存储每个环形区域的信息，包括中心点坐标 $(x, y)$ 和两个半径 $r$ 和 $R$ 。

然后，我们定义了一个函数 ```computeDistance``` 来计算两个点之间的距离，使用的是欧几里得距离公式： $d = \sqrt{(x_2 - x_1)^2 + (y_2 - y_1)^2}$ 。

接着，我们定义了一个函数 ```isCircle``` 来判断两个环形区域的位置关系。这个函数接受四个参数：两个环心的距离 $d$ ，和两个环的半径 $r1$ 和 $r2$ 。函数返回一个布尔值，表示两个环是否满足内含、外离或相交的条件。

最后，在 ```main``` 函数中，我们读入两个环的信息，计算它们的环心距离，然后对每个环的两个半径，分别与另一个环的两个半径进行位置关系的判断，将满足条件的情况累加到答案中。

## 代码解析
```cpp
#include <iostream>
#include <cmath>

struct Circle
{
    long long x, y, innerRadius, outerRadius;
};

double computeDistance(Circle c1, Circle c2)
{
    return std::sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
}

bool isCircle(double d, long long r, long long r1, long long r2)
{
    return (d <= r1 - r) || (d <= r - r2) || (d >= r + r2);
}

int main()
{
    Circle c1, c2;
    std::cin >> c1.x >> c1.y >> c1.innerRadius >> c1.outerRadius;
    std::cin >> c2.x >> c2.y >> c2.innerRadius >> c2.outerRadius;
    int result = 0;
    double d = computeDistance(c1, c2);
    result += isCircle(d, c1.innerRadius, c2.innerRadius, c2.outerRadius);
    result += isCircle(d, c1.outerRadius, c2.innerRadius, c2.outerRadius);
    result += isCircle(d, c2.innerRadius, c1.innerRadius, c1.outerRadius);
    result += isCircle(d, c2.outerRadius, c1.innerRadius, c1.outerRadius);
    std::cout << result;
    return 0;
}
```

## 时间复杂度
由于我们只需要对输入的两个环进行一次计算，所以这个程序的时间复杂度是$O(1)$。


---

