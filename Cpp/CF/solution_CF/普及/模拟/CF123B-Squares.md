# Squares

## 题目描述

You are given an infinite checkered field. You should get from a square ( $ x_{1} $ ; $ y_{1} $ ) to a square ( $ x_{2} $ ; $ y_{2} $ ). Using the shortest path is not necessary. You can move on the field squares in four directions. That is, when you are positioned in any square, you can move to any other side-neighboring one.

A square ( $ x $ ; $ y $ ) is considered bad, if at least one of the two conditions is fulfilled:

- $ |x+y|≡0 $ $ (mod 2a) $ ,
- $ |x-y|≡0 $ $ (mod 2b) $ .

Your task is to find the minimum number of bad cells one will have to visit on the way from ( $ x_{1} $ ; $ y_{1} $ ) to ( $ x_{2} $ ; $ y_{2} $ ).

## 说明/提示

In the third sample one of the possible paths in (3;-1)->(3;0)->(3;1)->(3;2)->(4;2)->(4;3)->(4;4)->(4;5)->(4;6)->(4;7)->(3;7). Squares (3;1) and (4;4) are bad.

## 样例 #1

### 输入

```
2 2 1 0 0 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2 2 10 11 0 1
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2 4 3 -1 3 7
```

### 输出

```
2
```

# 题解

## 作者：清小秋ovo (赞：6)

# CF123B

输出从一个点走到另外一个点且经过“坏点”最少的经过点数。

坏点的定义是:

$$ | x+y | \bmod 2a=0$$
$$| x-y | \bmod 2b=0$$

很显然，要想让经过的坏点数量最少，直接走交点就好了。

(附上一个简单的代码)

## 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int a,b,x1,x2,y1,y2;
	cin>>a>>b>>x1>>y1>>x2>>y2;
	int x=x1;
	int y=y1;
	x1=x+y;
	y1=y-x;
	x=x2;
	y=y2;
	x2=x+y;
	y2=y-x;
	a*=2;
	b*=2;
	x1=x1/a+(x1>0);//(0,0)
	x2=x2/a+(x2>0);
	y1=y1/b+(y1>0);
	y2=y2/b+(y2>0);
	cout<<max(abs(y2-y1),abs(x2-x1))<<endl;
}

```



---

## 作者：luosw (赞：2)

这么水的题目居然没有题解???

那好，我来发。

### 题意简述
给出一个无限大的二维坐标平面，现在有一些坏点，规定：
- $x+y≡0(mod\ 2a)$
- $x-y≡0(mod\ 2b)$

满足以上两条件之一的点即为坏点，现在问最少经过多少个坏点的情况下，可以从起点到达终点

---

### 题目分析
这里有一张图（借用$CodeForces$官网题解的图）
![](https://cdn.luogu.com.cn/upload/image_hosting/nqalk22e.png)

那么从一点走到另一点才是最少的呢 ？当然是走两者的交点，正如图中画的那样，因为如果你走交点，你可以越过两条直线， 那么这个交点数怎样算呢 ？就是途中红线和绿线经过途中蓝线的条数的最大值。

### $Code$
```cpp

#include<iostream>
#include<sstream>
#include<map>
#include<cmath>
#include<fstream>
#include<queue>
#include<vector>
#include<sstream>
#include<cstring>
#include<cstdio>
#include<stack>
#include<bitset>
#include<ctime>
#include<string>
#include<cctype>
#include<iomanip>
#include<algorithm>
using namespace std  ;
#define INT __int64
const int INF = 0x3f3f3f ;
const double esp = 0.0000000001 ;
const double PI = acos(-1.0) ;
const int mod = 1000000007 ;
const INT Up = 1000000000 ;
const INT Dn = -1000000000 ;
const int MY = 205 ;
const int MX = 205 ;
int workA(double x1 ,double y1 ,double x2 ,double y2 ,double d)
{
    double dA ,dB ;
    int num1 ,num2 ;
    dA = fabs(y1 + x1)/sqrt(2.0) ;
    dB = fabs(y2 + x2)/sqrt(2.0) ;
    num1 = (int)(dA/d + 1.0) ;
    num2 = (int)(dB/d + 1.0) ;
    if(((x1+y1 > 0)&&(x2 + y2 > 0)) || (x1 + y1 < 0 && x2 + y2 < 0))  // 同在一侧
             return abs(num1 - num2) ;
    else
             return abs(num1 + num2 - 1) ;
}
int workB(double x1 ,double y1 ,double x2 ,double y2 ,double d)
{
    double dA ,dB ;
    int num1 ,num2 ;
    dA = fabs(y1 - x1)/sqrt(2.0) ;
    dB = fabs(y2 - x2)/sqrt(2.0) ;
    num1 = (int)(dA/d) + 1 ;
    num2 = (int)(dB/d) + 1 ;
    if(((y1 > x1)&&(y2 > x2)) || ((y1 < x1)&&(y2 < x2))) // 如果同时大于 同时小于
            return  abs(num1 - num2) ;
    else
            return  abs(num1 + num2 - 1) ;
}
int main()
{
    double a ,b ,x1 ,y1 ,x2 ,y2 ,b1 ,b2 ,x ,y ;
    while(~scanf("%lf%lf%lf%lf%lf%lf" ,&a ,&b ,&x1 ,&y1 ,&x2 ,&y2))
    {
        if(x1 != x2 && y1-y2 == x1 - x2)  // 为 45 度
            cout<<workA(x1 ,y1 ,x2 ,y2 ,sqrt(2.0)*a)<<endl ;
        else if(x1 != x2 && y1 - y2 == x2 - x1) // 为 135 度
            cout<<workB(x1 ,y1 ,x2 ,y2 ,sqrt(2.0)*b)<<endl ;
        else
        {
            b1 = y1 - x1 ;
            b2 = y2 + x2 ;
            x = (b2 - b1)/2.0 ;  // 交点
            y = x + b1 ;
            cout<<max(workA(x1 ,y1 ,x ,y ,sqrt(2.0)*a) ,workB(x2 ,y2 ,x ,y ,sqrt(2.0)*b))<<endl ;
        }
    }
    return 0 ;
}
```


---

## 作者：wyc0607 (赞：1)

### 思路：数学
如果想要经过最少的坏点，则应所有经过的坏点都是两个坏点的交点。

若有一点 $(x+y,x-y)$，则若该点为坏点，满足：

- $2x \equiv 0 \pmod {2a}$。
- $2y \equiv 0 \pmod {2b}$。

故我们先算出 $x_1$，$x_2$，$y_1$，$y_2$ 的坏点数，再取最大值即可。

### 代码：
[AC记录](https://codeforces.com/problemset/submission/123/302197388)
```cpp
#include<bits/stdc++.h>
using namespace std;
main() {
	int a,b,xa,xb,ya,yb;
	cin>>a>>b>>xa>>ya>>xb>>yb;
	
	int x=xa,y=ya;
	xa=x+y,ya=x-y;
	int xx=xb,yy=yb;
	xb=xx+yy;
	yb=xx-yy;
	
	xa=xa/(2*a)+(xa>0);
	xb=xb/(2*a)+(xb>0);
	ya=ya/(2*b)+(ya>0);
	yb=yb/(2*b)+(yb>0);
	
	cout<<max(abs(ya-yb),abs(xa-xb));
}
```

---

## 作者：Mistybranch (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF123B)

题目大概意思是：给你两个常数 $a$ 和 $b$，和起点 $(x1, y1)$、终点 $(x2, y2)$。现在你要从起点走到终点。途中保证满足以下条件的点 $(x, y)$（即为坏点）个数尽可能少：

- $|x + y| \equiv 0 \mod 2a$
- $|x - y| \equiv 0 \mod 2b$

这道题数据量蛮大的，所有变量的最大值都是 $10^9$，暴力肯定不行，考虑数学解决。下面

我们首先看到坏点的定义中 $x + y$ 和 $x - y$ 不太好处理，我们将点 $(x, y)$ 旋转 $45 \degree$，那么这个点就变成 $(x + y, x - y)$，并且这个点能走到的所有点都变成了 $(x + y + 1, x - y + 1)$，$(x + y + 1, x - y - 1)$，$(x + y - 1, x - y + 1)$ 和 $(x + y - 1, x - y - 1)$，也就是对角线。

![](https://cdn.luogu.com.cn/upload/image_hosting/02pyawtb.png)

旋转完之后，我们会发现坏点的条件变成了：

- $x \equiv 0 \mod 2a$
- $y \equiv 0 \mod 2b$

所以说好点就被分成了很多 “块”，如图，蓝线上的点全部为坏点。

![](https://cdn.luogu.com.cn/upload/image_hosting/jbjp2xz7.png)

现在我们将问题转化成了：从一个点走到另一个点，中间经过的点 $(x, y)$ 满足 $2a | x$ 或 $2b | y$ 的点至少有多少个。

我们发现，从一个点到另一个点，横着要经过 $\dfrac{|x1 - x2|}{2a}$ 个坏点，竖着要经过 $\dfrac{|y1 - y2|}{2b}$ 个坏点，而当你沿着对角线走时，最多能走到 $\min{\dfrac{|x1 - x2|}{2a}}{\dfrac{|y1 - y2|}{2b}}$ 对重合的坏点（也就是上图中横竖蓝线的交叉点）。也就是说，最后答案是 $\max{\dfrac{|x1 - x2|}{2a}}{\dfrac{|y1 - y2|}{2b}}$。

需要注意的点是，这个算法不能保证最后的点都在第一象限上，所以需要特判，详见代码。

```cpp


#include <bits/stdc++.h>

using namespace std;

long long a, b, x, y, xx1, yy1, xx2, yy2;

int main () {
	cin >> a >> b >> xx1 >> yy1 >> xx2 >> yy2;
	
	x = xx1;
	y = yy1;
	xx1 = x + y;
	yy1 = y - x;
	
	x = xx2;
	y = yy2;
	xx2 = x + y;
	yy2 = y - x;
	
	a *= 2;
	b *= 2;
	
	xx1 = xx1 / a + (long long)(xx1 > 0);
	xx2 = xx2 / a + (long long)(xx2 > 0);
	yy1 = yy1 / b + (long long)(yy1 > 0);
	yy2 = yy2 / b + (long long)(yy2 > 0);
	
	cout << max(abs(yy2 - yy1), abs(xx2 - xx1)) << endl;
}
```


---

## 作者：YNH_QAQ (赞：0)

## CF123B题解
从起点 $(x1,y1)$ 到 $(x2,y2)$ 选出一条路径使得经过的坏点最少。


满足以下条件之一的点即为坏点。
- $x+y\equiv0 \pmod {2a}$

* $x-y\equiv 0 \pmod {2b}$

将图旋转，把 $x+y$ 和 $x-y$ 的点 $(x,y)$ 变成 $(x+y,x-y)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/dmujv5uc.png)

问题转化为：从起点走到终点，中间经过的点满足 $x$ 被 $2a$ 且 $y$ 被 $2b$ 整除的点数。

### code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a,b,x1,x2,y_1,y2;
signed main(){
	cin>>a>>b>>x1>>y_1>>x2>>y2;
	int x=x1,y=y_1;
	x1=x+y;
	y_1=y-x;
	x=x2;y=y2;
	x2=x+y;y2=y-x;
	x1=x1/(a*2)+(x1>0);
	x2=x2/(a*2)+(x2>0);
	y_1=y_1/(2*b)+(y_1>0);
	y2=y2/(b*2)+(y2>0);
	cout<<max(abs(y2-y_1),abs(x2-x1))<<endl;
	return 0;
}
```

---

