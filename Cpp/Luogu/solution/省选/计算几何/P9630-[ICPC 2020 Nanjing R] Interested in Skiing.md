# [ICPC 2020 Nanjing R] Interested in Skiing

## 题目描述

Kotori 对滑雪很感兴趣。滑雪场是在二维平面上沿着 $y$ 轴无限延伸的直线，其中场中的所有点 $(x,y)$ 满足 $-m\le x\le m$。滑雪时，Kotori 不能离开场地，这意味着他的 $x$ 坐标的绝对值应该始终不超过 $m$。地面上也有 $n$ 个路段是障碍，Kotori 无法越过障碍。

Kotori 将从 $(0, -10^{10^{10^{10^{10}}}})$  开始滑雪（你可以将此 $y$ 坐标视为负无穷大），并朝着 $y$ 轴的正方向移动。她的垂直（平行于 $y$ 轴）速度始终是 $v_y$，此值不变，但是她可以在 $[-v_x, v_x]$ 的间隔内控制她的水平（平行于 $x$ 轴的）速度。Kotori 改变速度的时间可以忽略不计。

你的任务是帮助 Kotori 计算 $v_x^*$ 的最小值，即一旦 $v_x>v_x^*$，她就可以安全地穿过滑雪场而不会遇到障碍物。

## 样例 #1

### 输入

```
3 2 1
-2 0 1 0
-1 4 2 4
0 1 0 3```

### 输出

```
1.000000000000000```

## 样例 #2

### 输入

```
2 1 2
-1 0 1 0
1 1 0 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
2 3 7
-3 0 2 2
3 1 -2 17```

### 输出

```
1.866666666666666```

## 样例 #4

### 输入

```
1 100 1
-100 0 99 0
```

### 输出

```
0.000000000000000```

# 题解

## 作者：WhitD (赞：2)

## 题目大意
给定大小为 $m\times m$ 的二维平面，平面上有 $n$ 条线段，用端点坐标 $(x_1,y_1)$ 和 $(x_2,y_2)$ 表示。有一个点从 $(0,-\infty)$ 以 $v_y$ 的速度向 $y$ 轴正方向运动，终点为 $(0,\infty)$，对于一个 $v_x$ 值，点的水平速度可以在 $[-v_x,v_x]$ 内变化。你需要求出最小的 $v_x^*$，当点的水平速度 $v_x>v_x^*$ 时，点在运动过程中不会碰到任意一条线段。
## 思路
我们考虑点需要经过第 $i$ 条线段，此时最优路线一定会恰好经过 $i$ 的某个端点，并且点由一个端点到下一条需要经过的线段的某个端点的最优路线一定是直线，也就是总路线一定是一条经过若干条线段的端点的折线。
#### 为什么嘞
根据速度公式，我们有 $v=\frac{\Delta x}{\Delta t}$，由于点的垂直速度 $v_y$ 是定值，因此 $\Delta t$ 也是一定的，此时 $v\propto\Delta x$，为了让所求的 $v_x^*$ 最小，$\left|\Delta x\right|$ 也必须最小，根据两点之间线段最短可知我们上述结论是成立的。

------------
### 于是
我们可以先将所有线段按照他们端点的 $y$ 值升序排序，然后进行拓扑转移，设 $dp_i$ 表示到达第 $i$ 个端点所需要的最小水平速度 $v_x$ 的值，每次转移前需要判断这两个端点是否可以到达。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ls (i<<1)
#define rs (i<<1|1)
using namespace std;
struct node
{
    int x,y;
}nd[205];
struct line
{
    node f,l;
}ln[205];
int dis(node a,node b,node c){return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);}
int pos(int x){return (!x)?0:(x>0?1:-1);}
int is(line l1,line l2){return max(l2.f.y,l2.l.y)>min(l1.f.y,l1.l.y)&&max(l2.f.x,l2.l.x)>min(l1.f.x,l1.l.x)&&pos(dis(l2.f,l1.f,l2.l))*pos(dis(l2.f,l1.l,l2.l))<0&&max(l1.f.y,l1.l.y)>min(l2.f.y,l2.l.y)&&pos(dis(l1.f,l2.f,l1.l))*pos(dis(l1.f,l2.l,l1.l))<0&&max(l1.f.x,l1.l.x)>min(l2.f.x,l2.l.x); }
bool cmp(node a,node b){return a.y<b.y;}
int n,m,v;
double dp[205],ans=1e20;
int check(node a,node b)
{
	line x=line{a,b};
    for(int i=0;i<n;i++)
        if(is(x,ln[i])) 
			return 0;
    return 1;
}
int main()
{
	cin>>n>>m>>v;
	for(int i=0;i<2*n;i++)
		dp[i]=1e20;
    for(int i=0;i<n;i++)
        cin>>nd[ls].x>>nd[ls].y>>nd[rs].x>>nd[rs].y,ln[i]=line{nd[ls],nd[rs]};
    sort(nd,nd+2*n,cmp);
    for(int i=0;i<2*n;i++)
	{
        if(nd[i].x<=-m||nd[i].x>=m) 
			continue;
        if(check(node{nd[i].x,-10001},nd[i])) 
			dp[i]=0;
        for(int j=0;j<i;j++)
		{
            if(nd[j].y==nd[i].y) 
				break;
            if(check(nd[j],nd[i]))
                dp[i]=min(dp[i],max(dp[j],abs(1.0*(nd[i].x-nd[j].x)/(nd[i].y-nd[j].y))));
        }
        if(check(node{nd[i].x,10001},nd[i])) 
			ans=min(ans,dp[i]);
    }
    if(check(node{0,-10001},node{0,10001})) 
		ans=0;
    if(ans>1e10) 
		printf("-1");
    else 
    	printf("%.10lf",ans*v);
    return 0;
}
```


---

