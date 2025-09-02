# [ICPC 2020 WF] Ley Lines

## 题目描述

1921 年，业余考古学家阿尔弗雷德·沃特金斯创造了“能量线”一词，用来指代连接多个地理和历史兴趣点的直线。这些线常常与神秘和神秘的理论联系在一起，其中许多理论至今仍然存在。

关于能量线的一个常见批评是，人们在地图上画的线实际上是有非零宽度的，给定足够密集的点和足够粗的铅笔，找到连接多个地方的“线”是微不足道的。在这个问题中，你将探讨这一批评。

为简单起见，我们将忽略地球的曲率，只假设我们处理的是平面上的一组点，每个点都有唯一的 $(x, y)$ 坐标，并且没有三个点在同一条直线上。给定这样的一组点和铅笔的厚度，你可以通过多少个点画出一条线？

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 2
0 0
2 4
4 9
3 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3 1
0 10
2000 10
1000 12```

### 输出

```
2```

# 题解

## 作者：Diaоsi (赞：1)

[[ICPC2020 WF] Ley Lines](https://www.luogu.com.cn/problem/P8133)

抢一下第一篇题解，本题解采用弧度制，其中 $\sin^{-1},\,\tan^{-1}$ 为反三角函数。

首先有一个引理，就是一定存在一个最优解使得有一个点在线的边界上。证明很简单，如果不在边界上的话，我们可以平移两条线，直到其中一条碰到某个点为止。不难发现在这个过程中答案是不会变的。

枚举那个在边界上的点。然后以这个点为原点，模拟粗线转绕原点转一圈的过程，求出在这个过程中每个点分别在哪个角度区间会被覆盖。

遍历其余的点，设当前点的极角为 $\alpha$，与原点（当前）距离为 $d$，粗线宽为 $r$。

若 $d<r$，则该点被覆盖的幅角为 $[\alpha,\alpha+\pi]$。

若 $d\geq r$，则该点被覆盖的幅角为 $[\alpha,\alpha+\beta]$ 和 $[\alpha-\beta+\pi,\alpha+\pi]$。

可以画图理解，下图以区间 $[\alpha,\alpha+\beta]$ 为例：

![10](https://cdn.luogu.com.cn/upload/image_hosting/tol53pul.png)

![11](https://cdn.luogu.com.cn/upload/image_hosting/q5ck1nk1.png)

把所有区间处理出来后，按照极角升序做一遍扫描线即可，时间复杂度 $\mathcal{O}(n^2\log n)$。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=3010,M=30010,INF=0x3f3f3f3f;
const ld eps=1e-6,pi=acos(-1),inf=1e9;
int n,m,ans,res;
vector<pair<ld,int> > v;
struct node{
	ll x,y;
	node(ll xx=0,ll yy=0){x=xx,y=yy;}
	void in(){scanf("%lld%lld",&x,&y);}
	void out(){printf("%lld %lld\n",x,y);}
}p[N];

node operator +(node a,node b){return node(a.x+b.x,a.y+b.y);}
node operator -(node a,node b){return node(a.x-b.x,a.y-b.y);}
ll operator *(node a,node b){return a.x*b.x+a.y*b.y;}
ll operator ^(node a,node b){return a.x*b.y-a.y*b.x;}

node operator *(ll x,node b){return node(x*b.x,x*b.y);}

ld sqr(ld x){return x*x;}
ld dis(node a,node b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}

ld get(ld x){return x<0?2*pi+x:x;}
ld taninv(ld y,ld x){return get(atan2(y,x));}

void add(ld l,ld r){
	v.pb(mp(l,1)),v.pb(mp(r,-1));
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)p[i].in();
	for(int i=1;i<=n;i++){
		v.clear();res=1;
		for(int j=1;j<=n;j++){
			if(i==j)continue;
			node b=p[j]-p[i];
			ld t=taninv((ld)b.y,(ld)b.x),r=dis(p[i],p[j]),s=asin((ld)m/r);
			if(r<(ld)m)add(t,t+pi);
			else add(t,t+s),add(t-s+pi,t+pi);
		}
		sort(v.begin(),v.end());
		for(pair<ld,int> t:v)
			res+=t.se,ans=max(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}
```

---

