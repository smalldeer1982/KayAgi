# Conveyor

## 题目描述

工厂中有一条长为 $2l$ 的传送带，前 $l$ 米面向上方，后 $l$ 米面向下方。传送带以 $v_1$ m/s的速度进行匀速运动，Anton以 $v_2$ m/s的速度在传送带上进行与其方向相同的匀速直线运动。传送带上有 $n$ 块巧克力（巧克力不会掉落且随传送带运动），Anton会捡起他经过的所有巧克力（该过程不消耗时间，包含起点而不包含终点的巧克力）。Anton有相等的概率选择任意位置作为起点。请你对于 $0\le i\le n$ ，求出Anton捡得 $i$ 块巧克力的概率。

## 样例 #1

### 输入

```
1 1 1 1
0
```

### 输出

```
0.75000000000000000000
0.25000000000000000000
```

## 样例 #2

### 输入

```
2 3 1 2
2 5
```

### 输出

```
0.33333333333333331000
0.66666666666666663000
0.00000000000000000000
```

# 题解

## 作者：芦苇林 (赞：1)

[~~宣传博客~~](https://www.cnblogs.com/violetholmes/p/14786925.html)

## 题解

当且仅当巧克力下标在Anton起始下标后，且在其到达终点前仍停留在传送带正面才会被他捡起。而Anton到达终点的时间为$\frac{l}{v_1+v_2}$，巧克力在此时间中移动的距离是$\frac{l\cdot v_1}{v_1+v_2}$。因此$a_i+\frac{l\cdot v_1}{v_1+v_2}\le l$，也就是$a_i\le l-\frac{l\cdot v_1}{v_1+v_2}$的巧克力会在起始下标为$0$时被捡起。设起始下标为$x$，则可以捡起的巧克力下标为$x\le a_i\le x+l-\frac{l\cdot v_1}{v_1+v_2}$（暂忽略环形）。

但是下标的数据范围过大，只得从巧克力入手。设巧克力下标为$x$，可以将其捡起的起点下标为$y$，则由上式可得$x-(l-\frac{l\cdot v_1}{v_1+v_2})\le y\le x$（最后处理环形QwQ）。对于每个$x$，我们将$y$所在区间的两端点放入一个优先队列（依下标增序排序）。设$lst$表示当前可以捡起的巧克力个数，$pos$表示上一个起/终点的坐标。对于下标为$x$的起/终点，$x-pos$即为捡起（更新前的）$lst$个巧克力的起始下标个数，累加入答案即可。遍历优先队列，遇起点时$lst+1$，遇终点时$lst-1$，并不断更新$pos$、维护答案。

对于环形，也就是$x-(l-\frac{l\cdot v_1}{v_1+v_2})<0$的情况，将原区间左端点设为$0$，新建区间$[2\cdot l-x+(l-\frac{l\cdot v_1}{v_1+v_2}),2\cdot l]$表示溢出至传送带末端的区间部分即可。

## AC代码

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10; 
const double eps=1e-7;
struct node 
{
	double d; bool op;//d:下标,op:起/终点(0/1)
	bool operator<(const node& x) const {return d-x.d>eps;}
};
int a[N]; double ans[N];
priority_queue<node> q;
signed main()
{
	int n,l,v1,v2;
	scanf("%lld%lld%lld%lld",&n,&l,&v1,&v2);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	double lim=l-l*v1*1.0/(v2+v1);
	for(int i=1;i<=n;i++) 
	{
		q.push((node){max(0.0,a[i]-lim),0}),q.push((node){a[i],1});
		if(a[i]-lim<0) q.push((node){l*2+a[i]-lim,0}),q.push((node){2*l,1});//处理环形
	}
	int lst=0; double pos=0; 
	while(!q.empty())
	{
		node x=q.top(); q.pop();
		ans[lst]+=x.d-pos;
		lst+=x.op?-1:1,pos=x.d;
	}	
	ans[lst]+=2*l-pos;//处理结尾剩余下标
	for(int i=0;i<=n;i++) printf("%.9lf\n",ans[i]*1.0/(2*l));
	return 0;
}
```



---

