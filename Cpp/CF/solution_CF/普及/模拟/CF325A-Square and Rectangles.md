# Square and Rectangles

## 题目描述

You are given $ n $ rectangles. The corners of rectangles have integer coordinates and their edges are parallel to the $ Ox $ and $ Oy $ axes. The rectangles may touch each other, but they do not overlap (that is, there are no points that belong to the interior of more than one rectangle).

Your task is to determine if the rectangles form a square. In other words, determine if the set of points inside or on the border of at least one rectangle is precisely equal to the set of points inside or on the border of some square.

## 样例 #1

### 输入

```
5
0 0 2 3
0 3 3 5
2 0 5 2
3 2 5 5
2 2 3 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
0 0 2 3
0 3 3 5
2 0 5 2
3 2 5 5
```

### 输出

```
NO
```

# 题解

## 作者：01Dragon (赞：0)

### 题意
给定 $n$ 个**不重叠**矩形，问能否拼成一个正方形？
### 思路
记录面积总和和最大最小坐标，再判断是不是构成了一个没有空心的正方形。
### 代码
```cpp
#include<iostream>
#include<algorithm>
#include<string>
#include<cmath>
using namespace std;
int n,ix=2147483647,iy=2147483647,ax,ay,a,b,c,d,sum;//别忘了把最小坐标设置成一个很大的数。
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c>>d;
		sum+=(a-c)*(b-d);//记录面积和
		ix=min(ix,a);
		iy=min(iy,b);
		ax=max(ax,c);
		ay=max(ay,d);
	}
	if(sum==(ix-ax)*(iy-ay)&&ix-ax==iy-ay)如果实心且是正方形
	{
		cout<<"YES";
	}
	else
	{
		cout<<"NO";
	}
	return 0;
}

```


---

## 作者：miraculously (赞：0)

题目大意：

翻译有点问题，题目并没有问面积，而是在问矩形是否拼成正方形。

分析：

先求出最小的坐标和最大的坐标，判断是不是正方形，如果不是直接输出 NO，
否则判断是否空心，如果正方形面积等于矩形面积之和，那没有空心，输出 YES，否则输出 NO。

代码如下（有注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d,sx=1e9,sy=1e9,tx,ty,cnt;//sx，sy记录最小坐标，tx，ty记录最大坐标
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		cnt+=(c-a)*(d-b);//统计矩形面积和
		sx=min(sx,a);
		sy=min(sy,b);
		tx=max(tx,c);
		ty=max(ty,d);
	}
	if(cnt==(tx-sx)*(ty-sy)&&tx-sx==ty-sy)//如果拼成正方形且不空心
	printf("YES\n");
	else
	printf("NO\n");
}
```


---

## 作者：Leap_Frog (赞：0)

### P.S.
这人太菜了，都只能发发 div1A 的题解了。  
话说这个难度评分是怎么回事啊，个人认为这题应该 800，结果 CF 评 1200？![](//xn--9zr.tk/jk)  
还有这个洛谷上的通过率是怎么回事啊 $\frac17$ ？![](//xn--9zr.tk/jy)  

### Problem.
给定 $n$ $(n\le5)$ 个**不重叠**矩形，问它们面积并是否是正方形。  

### Solution.
矩形都不重叠了。。。  
那直接判面积就好了。  
首先找出坐标最大值与最小值。  
需要保证的是矩形中间没有留空以两坐标极差是否相等。  
而矩形中间没空直接判如果是正方形，它的面积和实际面积是否相等即可。  

### Coding.
[略](https://codeforces.com/contest/325/submission/111601967)

---

## 作者：封禁用户 (赞：0)

题目说了它不重叠，

那么只要判断 $x$ 的最小值与最大值的差，

等于 $y$ 的最小值与最大值的差，

且两差相乘等于几个正方形的面积之和，

那么就是能合成正方形。

代码实现
---
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,d;
int minx=1e9,miny=1e9;
int maxx,maxy,area;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>b>>c>>d;
		area+=(c-a)*(d-b);
		minx=min(minx,a);
		miny=min(miny,b);
		maxx=max(maxx,c);
		maxy=max(maxy,d);
	}
	printf((maxx-minx==maxy-miny&&area==(maxx-minx)*(maxy-miny))?"YES\n":"NO\n");
}
```

---

