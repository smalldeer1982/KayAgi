# Fox and Meteor Shower

## 题目描述

天空中下起了流星雨，且其中有n颗流星。天空可以被看做一个二维的平面，而每颗流星都可以被看做平面上的一点。
小狐狸Ciel看着天空。她发现每颗流星划过天空的轨迹都是一条直线，且每颗流星都以固定的速度运动。Ciel想知道：最多能有几颗流星在一定时间内能与其他流星相遇？（时间范围不限且时间点有可能为负数）流星在处于同一位置时不会相撞。

## 说明/提示

样例1中，流星1和流星2在时间点-1于点（0,0）相遇，故有2颗流星可以与其他流星相遇。
样例2中，流星1和流星2在时间点-1于点（1,0）相遇，流星1和流星3在时间点0于点（0.0）相遇，流星2和流星3在时间点2于点（0,1）相遇，故有3颗流星可以与其他流星相遇。
在样例3中，没有流星能与其他流星相遇，故输出1。
在样例4中，只有一颗流星，且速度为0，故输出1。
若你的浏览器不支持动图，请点击以下链接以查看样例示意gif。

## 样例 #1

### 输入

```
2
0 0 1 1 0 2
0 1 0 1 2 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
-1 -1 0 3 3 0
0 2 -1 -1 3 -2
-2 0 -1 6 0 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
4
0 0 0 1 0 1
0 0 1 1 1 1
0 1 1 1 1 0
0 1 0 1 0 0
```

### 输出

```
1
```

## 样例 #4

### 输入

```
1
0 0 0 1 0 0
```

### 输出

```
1
```

# 题解

## 作者：henryhu2006 (赞：1)

## 题意

平面上有 $n$ 个流星在运动，运动轨迹为直线，给定每个流星的运动轨迹、速度、时刻等信息，求最大的集合 $S$ 的大小，使得 $\forall u,v\in S,u\neq v$，流星 $u$ 和流星 $v$ 都会相遇（时空坐标相同），流星相遇后不会消失。

$n\le 1000$。

## 解法

首先可以将时间看为第三个维度，于是题目要求三维直线的“最大团”。

显然这些直线的关系有两种：

- 集合 $S$ 中的所有直线共点。
- 集合 $S$ 中的所有直线在同一平面内。

对于共点，枚举每条线 $i$，找出所有和它相交的线 $j$，直接统计交点重合数量即可。

对于共面，需要注意平行线不能同时选。枚举每个 $i$，再枚举每个 $j\neq i$，计算 $i,j$ 的速度向量之差。可以发现共线的那些线段的**速度**向量的辐角相同，计算同一辐角有多少个不同的向量即可。

关于速度向量辐角相同者平行，如果不考虑 $\Delta x=0$ 或者 $\Delta y=0$ 的繁琐情况，本质是在平面上 $|\dfrac{\partial y}{\partial x}|$ 恒定，与 $\partial t$ 无关。也就是向量所对应的斜率恒定。但 $x,y$ 和 $-x,-y$ 是不同的，因为这决定了平面关于 $z$ 的倾斜方向的正负。

## 代码

注意精度误差的 $\epsilon$ 不要取太小，$10^{-7}$ 为宜。

计算答案的时候不要忘了 $+1$（$i$ 本身）。

排序以后的数组差值和 $\epsilon$ 比较时也要加绝对值。

直接维护三维直线平面比较麻烦，可以利用 $\Delta t\neq 0$ 的性质。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1005;
const double eps=1e-7;
int n,ans; double c[N];
struct line{
	double x,y,vx,vy;
	void scan(double t1=0,double t2=0){
		cin>>t1>>x>>y>>t2>>vx>>vy,t2-=t1;
		vx=(vx-x)/t2,vy=(vy-y)/t2,x-=vx*t1,y-=vy*t1;
	}
} a[N];
struct point{
	double x,y,ang;
} b[N];
bool cmp(const point &a,const point &b){
	if(abs(a.ang-b.ang)<eps) return (abs(a.x-b.x)<eps)?a.y<b.y:a.x<b.x;
	return a.ang<b.ang;
}
int main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;++i) a[i].scan();
	for(int i=1;i<=n;++i){
		int tot=0;
		for(int j=1;j<=n;++j){
			if(j==i) continue;
			double x=a[j].x-a[i].x;
			double y=a[j].y-a[i].y;
			double vx=a[j].vx-a[i].vx;
			double vy=a[j].vy-a[i].vy;
			double t=vx?x/vx:(vy?y/vy:0);
			if(abs(x-vx*t)<eps&&abs(y-vy*t)<eps)
				c[++tot]=t,b[tot]={vx,vy,atan2(vy,vx)};
		}
		sort(c+1,c+tot+1);
		for(int j=1,k;j<=tot;j=k){
			for(k=j;k<=tot&&abs(c[k]-c[j])<eps;++k);
			ans=max(ans,k-j);
		}
		sort(b+1,b+tot+1,cmp);
		for(int j=2,cnt=1;j<=tot;++j){
			if(abs(b[j-1].ang-b[j].ang)<eps)
				cnt+=(abs(b[j].x-b[j-1].x)>eps||abs(b[j].y-b[j-1].y)>eps);
			else cnt=1; ans=max(ans,cnt);
		}
	}
	cout<<ans+1;
	return 0;
}

```

---

