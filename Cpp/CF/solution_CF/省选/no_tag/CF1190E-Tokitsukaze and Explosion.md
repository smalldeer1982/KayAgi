# Tokitsukaze and Explosion

## 题目描述

给定平面上 $N$ 个关键点，现在你可以放置 $M$ 条直线，直线之间可以相交，需要满足所有关键点与原点之间的线段至少与你放置的一条直线相交（相交在端点也算相交）。如果有一个关键点就是原点，那么一定要满足有一条直线经过原点。

你需要求出在满足上述条件的情况下原点到所有放置的直线的距离的最小值的最大可能值是多少。

## 样例 #1

### 输入

```
3 1
2 0
0 2
-1 0
```

### 输出

```
0.0000000000
```

## 样例 #2

### 输入

```
1 1
0 0
```

### 输出

```
0.0000000000
```

## 样例 #3

### 输入

```
2 1
-1 -1
-1 -1
```

### 输出

```
1.4142135617
```

## 样例 #4

### 输入

```
3 100000
3 2
-1 -3
2 -5
```

### 输出

```
3.1622776602
```

# 题解

## 作者：猪脑子 (赞：5)

题目要求让距离最短的那条直线距离尽可能大，那么很容易想到二分。

假设我们二分一个答案$d$，此时我们可以以原点为圆心画一个半径为$d$的圆，然后强制所有选择的直线都与该圆相切，因为如果某条直线在圆外面的话，我们完全可以把它向中心平移，这样并不会变差。

这样画出圆来，一条直线就可以被圆上的一个点表示。容易发现，这时一个点$P$与原点之间的连线如果能被一条直线切开，那么这条直线对应的点的范围是一个确定的圆弧。

如果我们求出每个圆弧，那么问题就变成：如何选择不超过$m$个点，使得每个圆弧上至少有一个点被选中。

如果是在直线上的问题（不是环，这时的圆弧就是一个线段），做法很简单：先将所有的线段按照左端点排序，那么我们每次都贪心的选择一个点，使得它能覆盖到编号最小的尽可能多的线段，这样复杂度是$O(n)$的。考虑环上的情况，一个做法是把环断开，然后每次单独跑，但这样是$O(n^2)$的，并不能通过这道题。

另一个做法是这样的：先把环变成链，然后在右边复制一份，这样一共有$2n$条线段。我们对这些线段排序，对于每个编号为$i$的线段，求出一个$next_i$，代表如果我们考虑$i$之后的所有线段，在选择一个点之后，第一个没被覆盖到的线段的编号最大是多少。这个东西可以用类似双指针的方法从右往左算出来。

求出了这个，我们就可以考虑倍增：$f_{i,j}$代表从$i$开始，选择了$2^j$个点，第一个没被覆盖到的线段编号最大是多少。很明显：

$$f_{i,0}=next_i,f_{i,j}=f_{f_{i,j-1},j-1}$$

于是我们就可以对于每个$i$，在$O(\log m)$的时间内求出选出$m$个点之后能覆盖多少的线段。这样，单次判断的复杂度就变成了$O(n\log m)$，在外面套个二分，足以通过此题。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const double PI=acos(-1);
int n,m;
double x[100010];
double y[100010];
struct Seg{
	double l,r;
}s[200010];
bool cmp(Seg a,Seg b){return a.l<b.l;}
double dist(double x,double y){return sqrt(x*x+y*y);}
const int M=19;
int f[200010][M];
int jump(int u,int x)
{
	int now=0;
	while(x){
		if(x&1)u=f[u][now];
		now++;x>>=1;
	}
	return u;
}
bool check(double d)
{
	for(int i=1;i<=n;i++)
	{
		double ang=atan2(y[i],x[i]);
		double delta=acos(d/dist(x[i],y[i]));
		s[i].l=ang-delta;
		s[i].r=ang+delta;
		if(s[i].l<0){
			s[i].l+=2*PI;
			s[i].r+=2*PI;
		}
		s[i+n].l=s[i].l+2*PI;
		s[i+n].r=s[i].r+2*PI;
	}
	int N=n*2;
	sort(s+1,s+N+1,cmp);
	f[N+1][0]=N+1;
	int cur=N;
	for(int i=N;i>=1;i--)
	{
		while(s[cur].l>s[i].r)cur--;
		f[i][0]=cur+1;
	}
	for(int i=1;i<M;i++)
		for(int j=1;j<=N+1;j++)
			f[j][i]=f[f[j][i-1]][i-1];
	for(int i=1;i<=n;i++)
		if(jump(i,m)>=i+n)
			return true;
	return false;
}
int main()
{
	double L=0,R=1e9;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf %lf",&x[i],&y[i]);
		R=min(R,dist(x[i],y[i]));
	}
	if(R<1e-6){
		printf("%.10lf\n",0.0);
		return 0;
	}
	int tim=40;
	while(tim--)
	{
		double mid=(L+R)/2;
		if(check(mid))L=mid;
		else R=mid;
	}
	printf("%.10lf\n",L);
	return 0;
}
```


---

