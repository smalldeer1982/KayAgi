# [EC Final 2021] Prof. Pang and Ants

## 题目描述

在庞教授的大房子边上，有一群包含 $m$ 只蚂蚁的蚁群，居住在有 $n$ 个洞口的洞穴里。 它们会外出寻找食物。食物在庞教授的大冰箱里，蚂蚁们试图从里面偷出食物来。

![](https://cdn.luogu.com.cn/upload/image_hosting/afep0zz9.png)

**传神.jpg**

特别的, 一只蚂蚁需要 $1$ 秒从任何洞口离开，并同样需要 $1$ 秒从任何洞口进入洞穴。不同的洞口有不同的位置，对一个洞口来说，它与冰箱的距离以 $a_i$ 表示，同样的，一只蚂蚁从冰箱偷出食物再到第 $i$ 个洞口的时间也是 $a_i$ 秒。由于蚂蚁们技术高超，从冰箱拿出食物不会消耗它们任何时间。

每只蚂蚁都必须且只能从冰箱偷一次食物。蚂蚁可以任意选择一个洞口出发并进入任何一个洞口，**两个洞口可以不同**。一个洞口在 $1$ 秒内只能有一只蚂蚁进出。因为这个原因，有些蚂蚁在偷完食物后需要等待一段时间才能进入洞口。

所以，你作为庞教授的好朋友， 需要计算出蚂蚁们偷出食物的最短时间。时间的定义为至少存在一只蚂蚁在洞穴外的时间总长，正在进出洞口的蚂蚁不被看作在洞穴里。

## 说明/提示

在第三组测试数据中，蚂蚁需要 $2$ 秒通过第一个洞口进出洞穴，并需要 $2$ 秒前往冰箱并搬回食物。

## 样例 #1

### 输入

```
3
2 4
1 2
3 10
1 2 3
5 1
1 2 3 4 5
```

### 输出

```
6
9
4
```

# 题解

## 作者：C1942huangjiaxu (赞：2)

考虑二分答案 $t$，求出在 $t$ 个时刻内最多能有多少只蚂蚁。

对于一个洞口，一定是先放出一些蚂蚁，再接进一些蚂蚁。

可以发现，对于第 $i$ 个洞口，出去的第 $j$ 只蚂蚁到达冰箱的时间是 $a_i+j$，接进来的**倒数**第 $j$ 只蚂蚁要在 $t-j-a_i$ 时刻**前**到达冰箱。

假如我们已经知道每个洞口出去和进来了多少只蚂蚁，那么就变成了一个二分图匹配问题。

因为每个洞口出去和进来的蚂蚁本质是相同的，所以我们会让前一半的时间出蚂蚁，后一半的时间进蚂蚁。

那么在 $t$ 是奇数的时候中间的时刻不好决定，因此我们改成每个时刻可以进去或出来 $2$ 只蚂蚁，中间时刻 $1$ 进 $1$ 出，最后答案除以 $2$。

直接做二分图匹配是不行的，但发现每个左部点连接的都是右部的一个后缀，因此从前到后扫 $t$ 个时刻，每次直接贪心的匹配所有可以匹配的右部点。

这样每次是 $O(t)$ 的，但注意到每个时刻新加入的左部点数量和右部点数量的变化次数是 $O(n)$ 的，于是可以离散化后对于数量相同的一起处理。

时间复杂度 $O(n\log n\log V)$，常数较大，但因为有 $8s$ 的时限可以通过。

注意到每个函数的形状是相同的，所以可以提前将 $a_i$ 排好序后归并几种端点，时间复杂度 $O(n(\log n+\log V))$。

这里只实现了 $O(n\log n\log V)$ 的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int T,n,a[N],cp;
ll m;
struct opt{
	ll x;int t,c;
	bool operator <(const opt b)const{return x<b.x;}
}p[N*6];
bool check(ll t){
	cp=0;
	ll h=t>>1;
	for(int i=1;i<=n;++i){
		if(t&1){
			p[++cp]={a[i]+1,0,2};
			p[++cp]={a[i]+h+1,0,-1};
			p[++cp]={a[i]+h+2,0,-1};
			p[++cp]={h-a[i],1,1};
			p[++cp]={h-a[i]+1,1,1};
			p[++cp]={t-a[i],1,-2};
		}else{
			p[++cp]={a[i]+1,0,2};
			p[++cp]={a[i]+h+1,0,-2};
			p[++cp]={h-a[i],1,2};
			p[++cp]={t-a[i],1,-2};
		}
	}
	ll sf=0,st=0,res=0,rs=0;
	sort(p+1,p+cp+1);
	for(int i=1;i<cp;++i){
		if(!p[i].t)sf+=p[i].c;
		else st+=p[i].c;
		ll dt=p[i+1].x-p[i].x;
		if(!dt)continue;
		if(sf>=st)res+=st*dt,rs+=(sf-st)*dt;
		else{
			rs+=sf*dt;
			ll u=min(st*dt,rs);
			rs-=u,res+=u;
		}
	}
	return res>=m*2;
}
void solve(){
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	ll l=2*m/n,r=2.1e14;
	while(l<r){
		ll mid=l+r>>1;
		if(check(mid))r=mid;
		else l=mid+1;
	}
	printf("%lld\n",l);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/P9884)

**题目大意**

> 给定 $n$ 个洞口，每个洞口每秒至多进或出一只蚂蚁。
>
> 第 $t$ 秒从洞口爬出的蚂蚁会在第 $a_i+t+1$ 秒到达冰箱，第 $t$ 秒进入洞口的蚂蚁至少要在 $t-a_i-1$ 秒前到达冰箱，求至少多少秒后 $m$ 只蚂蚁各经过冰箱一次。
>
> 数据范围：$n\le 10^5,m\le 10^{14}$。

**思路分析**

考虑二分时间 $T$，那么对于一只蚂蚁从第 $s$ 秒从 $i$ 出发，第 $t$ 秒到达 $j$，合法当且仅当 $s+a_i+1\le t-a_j-1$。

如果我们知道每个洞口每个时刻是出蚂蚁还是进蚂蚁，那么一对合法的起点终点可以看成一条边，最多完成的蚂蚁数量就是二分图上的最大匹配。

由于左部每个点连的都是右部一段严格递减的后缀，因此可以贪心匹配每个右部点。

我们只要解决每个洞口是出蚂蚁还是进蚂蚁的问题。

注意到我们可以倒转时间使得进、出蚂蚁的事件交换，根据对称性不难猜测一定是前一半时间出蚂蚁，后一半时间进蚂蚁最优。

那么左、右部点分别是 $\mathcal O(n)$ 个区间，求出极小的连续段之后可以快速维护上面的最大匹配过程。

唯一的细节是 $T\bmod 2=1$ 时最中间的时刻是进蚂蚁还是出蚂蚁，不妨假设这个时刻分别进出 $0.5$ 只蚂蚁，把所有权值 $\times 2$ 再处理即可。

注意到所有差分数组都是 $a_i$ 加减一个定值，预先对 $a_i$ 排序后只需要归并 $\mathcal O(1)$ 个有序数组。

时间复杂度 $\mathcal O(n\log m)$。

**代码呈现**

```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
const int MAXN=1e5+5;
const ll inf=2.5e14;
int n,a[MAXN];
ll m;
struct opr {
	ll x; int c,op;
	friend bool operator <(const opr &x,const opr &y) { return x.x<y.x; }
} s[MAXN*6];
bool chk(ll T) {
	int p=0;
	if(T&1) {
		for(int i=1;i<=n;++i) s[++p]={a[i]+1,2,0};
		for(int i=1;i<=n;++i) s[++p]={a[i]+T/2+1,-1,0};
		for(int i=1;i<=n;++i) s[++p]={a[i]+T/2+2,-1,0};
		for(int i=n;i>=1;--i) s[++p]={T/2-a[i],1,1};
		for(int i=n;i>=1;--i) s[++p]={T/2-a[i]+1,1,1};
		for(int i=n;i>=1;--i) s[++p]={T-a[i],-2,1};
		for(int o=1;o<6;++o) inplace_merge(s+1,s+o*n+1,s+(o+1)*n+1);
	} else {
		for(int i=1;i<=n;++i) s[++p]={a[i]+1,2,0};
		for(int i=1;i<=n;++i) s[++p]={a[i]+T/2+1,-2,0};
		for(int i=n;i>=1;--i) s[++p]={T/2-a[i],2,1};
		for(int i=n;i>=1;--i) s[++p]={T-a[i],-2,1};
		for(int o=1;o<4;++o) inplace_merge(s+1,s+o*n+1,s+(o+1)*n+1);
	}
	ll ans=0,tot=0,lx=0,rx=0;
	for(int i=1;i<p;++i) {
		(s[i].op?rx:lx)+=s[i].c;
		ll d=s[i+1].x-s[i].x;
		if(lx>=rx) ans+=rx*d,tot+=(lx-rx)*d;
		else {
			ans+=lx*d;
			ll w=min((rx-lx)*d,tot);
			tot-=w,ans+=w;
		}
	}
	return ans>=2*m;
}
void solve() {
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	ll l=0,r=inf,z=inf;
	while(l<=r) {
		ll mid=(l+r)>>1;
		if(chk(mid)) z=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",z);
}
signed main() {
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

