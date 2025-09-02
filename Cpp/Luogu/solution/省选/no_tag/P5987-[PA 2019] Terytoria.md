# [PA 2019] Terytoria

## 题目描述

在二维平面直角坐标系上，有一个长度为 $X$，宽度为 $Y$ 的地图，注意这个地图的左边界和右边界是连通的，下边界和上边界也是连通的。

在这个地图里，有 $X\times Y$ 个格子以及 $n$ 个边平行坐标轴的矩形。你只知道每个矩形两个对顶点的坐标，请问在最好情况下，被所有 $n$ 个矩形都覆盖住的格子数量有多少？

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 5\times 10^5$，$2\le X,Y\le 10^9$。


### 样例解释：

下图列举了一些情况，其中第3种情况是最优的：

![](https://cdn.luogu.com.cn/upload/image_hosting/9vwqe130.png)

## 样例 #1

### 输入

```
2 10 7
2 1 8 6
5 2 4 4```

### 输出

```
15```

# 题解

## 作者：happy_zero (赞：6)

线段树部分参考：[「题解」PA2019 Terytoria](https://www.luogu.com.cn/article/e37huuox)。

首先需要发现，横纵坐标互不干扰，最终的答案其实就是横坐标的答案乘纵坐标的答案。

以横坐标为例。问题转化成了对于每个 $(x_0,x_1)$ 选择覆盖 $S=[x_0,x_1)$ 或 $T=[1,x_0)\cup(x_1,n]$。

但其实如果直接做考虑每个选择哪一个是很困难的，观察到两种情况区间是不交的，于是有两种办法：

#### 扫描线+线段树

发现若已经确定了 $a$ 在最终答案中，是可以直接推出每组 $(x_0,x_1)$ 到底覆盖什么的。

当然不能直接枚举 $x$，首先要把 $x$ 的个数降下来：将所有 $x_{0/1}$ 离散化成 $x'$，则 $(x'_{i-1},x'_i]$ 内的所有 $x$ 是等价的，因为并没有端点在这个区间内，相当于是处在一个“空隙”中。

$x$ 的个数降到了 $O(n)$ 级别，接着考虑当 $x$ 右移的情况下，每个点的覆盖情况会发生怎样的变化：

- 当 $x=1$ 时，所有点覆盖的都是 $T$。
- 当 $x\to x+1$ 时：
  - 此时 $x_0=x$ 的点原先取 $S$ 已经无法覆盖 $x+1$ 了，于是变成覆盖 $T$。
  - 此时 $x_1=x$ 的点原先取 $T$ 也已经无法覆盖 $x+1$ 了，变成覆盖 $S$。
  - 由于 $S,T$ 中一共就三“段”， $S\Leftrightarrow T$ 最多只会进行 2 次，因此只有上面两种情况。
  
按上面的步骤，复杂度均摊仍是线性的。同时，我们需要一个数据结构（最简单的是线段树）来维护被覆盖个数最多的点的覆盖个数及数量，对应区间加、全局 $\max$ 即 $\max$ 个数。

复杂度 $O(n\log n)$，但常数很大，注意

- 线段树用节点 $l$ 代表 $hsh_l-hsh_{l-1}$，这样可以只离散化 $x_0,x_1$。
- 若同时进行多次区间加，则可以将其合并一些，比如 $[1,a],(b,n]$ 加 $-1$、$(a,b]$ 加 $1$ 可合并为全局加 $1$、$(a,b]$ 加 $2$，常数可减小一半。

---

#### 哈希

当确定了所有区间覆盖 $S$ 还是 $T$ 时是容易的，我们不可能暴力枚举，但可以将 $S$ 和 $T$ 放到一起做。

难点在于保证 $S$ 和 $T$ 不能同时取。由于其是不交的，运用哈希的套路，为每一个 $S$ 和 $T$ 都随机一个权值，若选了 $A$，则将 $A$ 中的所有点的 $w$ 异或上 $A$ 的权值。

定义一种覆盖方案的 $W$ 为所有点的 $w$ 的异或和，大概率下，不同的方案下对应的是不同的 $W$，且由 $S\cup T=U$ 可以知道，每个点都被 $n$ 个区间覆盖，那么每一种 $W$ 下对应的都是一种合法的方案。

于是直接统计出 $W$ 的最大出现次数即是答案。

事实证明，哈希不一定要写异或哈希，和哈希等其实也是可以的。注意，若写异或哈希，生成的随机数得是 64 位的，否则出错概率会比较大，会 WA on #1。

---
[code](https://note.ms/731925P5987)。

---

## 作者：agicy (赞：5)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-p5987)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117635849)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14856261.html)；
- 因为简书系统升级，所以本文未在简书上发布。

## 题目

题目链接：[洛谷 P5987](https://www.luogu.com.cn/problem/P5987)、[LOJ 3320](https://loj.ac/p/3220)、[官网](https://sio2.mimuw.edu.pl/c/pa-2019-1/p/ter/)。

### 题意概述

在二维平面直角坐标系上，有一个长度为 $X$，宽度为 $Y$ 的地图，注意这个地图的左边界和右边界是连通的，下边界和上边界也是连通的，换言之它是个球形结构。

在这个地图里，有 $X\times Y$ 个格子以及 $n$ 个边平行坐标轴的矩形。你只知道每个矩形两个对顶点的坐标，请问在最好情况下，被所有 $n$ 个矩形都覆盖住的格子数量有多少？

$1\leq n\leq 5\times 10^5$，$2\leq X,Y\leq 10^9$。

## 题解

### 几何性质

首先不难发现，$x,y$ 两维是独立的。

考虑一个矩形的选取情况，只有 $00,01,10,11$ 四种情况。

然而，两个状态 $0,1$ 相乘即可得到上面的所有状态，因此我们可以两维分开做。

### 枚举答案区间

考虑对于一维的情况，一个点对 $(x_1,y_1),(x_2,y_2)$ 仅对应两种可能 $[x_1,x_2]$ 或者 $[0,x_1)\cup(x_2,x]$。

这两个集合显然不交，因此，我们可以考虑枚举一个区间 $[i,i+1]$，那么可以轻易地确定每个区间的选择方案，因而求出最终的长度。

这个可以离散化后可以用扫描线维护，用线段树维护：

- 查询操作：区间最大值及个数；
- 修改操作：区间加法。

时间复杂度为 $\Theta(n\log_2n)$，可以通过本题。

### 随机算法有前途

我们想到一个简单的方案，如果区间数量 $\leq 64$，那么我们对于第 $i$ 个区间 $[x_1,x_2]$ 内的数，都异或上 $2^i$，那么操作结束之后，所有异或值相同的区间对应的集合选择方案必然相同，换句话说，它们是一块的。

因此，如果区间数量 $\leq 64$，我们只需要求出相同异或值的出现次数的最大值即可。

可是这个题目显然不会有上面那么紧的约束，我们考虑放松约束。

具体地，我们不再强求异或的值为 $2^i$，而是变成一个随机非负整数 $\in[0,2^{64})$。统计答案的方法与之前相同，时间复杂度为 $\Theta(n\log_2n)$，可是正确性呢？

我们的答案出错，是因为有两个不该在同一块的位置经过异或后出现了相同的值，那么我们考虑每一位上异或值相同的概率均为 $\frac{1}{2}$，那么这个算法正确的概率根据生日悖论为：

$$
\prod_{k=0}^{2n-1}(1-\frac{k}{2^{64}})^2
$$

这个数字经过计算可以知道非常接近 $1$，正确性得到保证。

### 参考程序

线段树的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(min(l,r)),r(max(l,r)){
		return;
	}
};

struct Event{
	int x,id;
	inline Event(reg int x=0,reg int id=0):x(x),id(id){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x;
	}
};

int n,X,Y;
Interval a[MAXN];
Interval b[MAXN];
vector<int> V;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,cnt;
		int tAdd;
		#define Max(x) unit[(x)].Max
		#define cnt(x) unit[(x)].cnt
		#define tAdd(x) unit[(x)].tAdd
	};
	Node unit[MAXN<<3];
	inline void pushup(reg int k){
		if(Max(lson)>Max(rson))
			Max(k)=Max(lson),cnt(k)=cnt(lson);
		else if(Max(lson)==Max(rson))
			Max(k)=Max(lson),cnt(k)=cnt(lson)+cnt(rson);
		else
			Max(k)=Max(rson),cnt(k)=cnt(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		tAdd(k)=0;
		if(l==r){
			Max(k)=0,cnt(k)=V[l+1]-V[l];
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int val){
		Max(k)+=val,tAdd(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tAdd(k)){
			add(lson,tAdd(k)),add(rson,tAdd(k));
			tAdd(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef Max
	#undef cnt
	#undef tAdd
}

inline int solve(reg int n,reg Interval a[],int X){
	V.clear();
	V.reserve((n+1)<<1);
	for(reg int i=1;i<=n;++i){
		V.push_back(a[i].l);
		V.push_back(a[i].r);
	}
	V.push_back(0),V.push_back(X);
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		a[i].l=lower_bound(V.begin(),V.end(),a[i].l)-V.begin();
		a[i].r=lower_bound(V.begin(),V.end(),a[i].r)-V.begin();
	}
	X=lower_bound(V.begin(),V.end(),X)-V.begin();
	reg int s=V.size()-1;
	vector<Event> E;
	E.reserve(n<<1);
	SegmentTree::build(1,0,s-1);
	for(reg int i=1;i<=n;++i){
		E.push_back(Event(a[i].l,i));
		E.push_back(Event(a[i].r,-i));
		SegmentTree::update(1,0,s-1,0,s-1,1);
		SegmentTree::update(1,0,s-1,a[i].l,a[i].r-1,-1);
	}
	sort(E.begin(),E.end());
	reg int ptr=0;
	reg int res=0;
	for(reg int i=0;i<s;++i){
		while(ptr<(int)E.size()&&E[ptr].x<=i){
			reg int id=abs(E[ptr].id);
			if(E[ptr].id>0){
				SegmentTree::update(1,0,s-1,0,s-1,-1);
				SegmentTree::update(1,0,s-1,a[id].l,a[id].r-1,2);
			}
			else{
				SegmentTree::update(1,0,s-1,0,s-1,1);
				SegmentTree::update(1,0,s-1,a[id].l,a[id].r-1,-2);
			}
			++ptr;
		}
		res=max(res,SegmentTree::unit[1].cnt);
	}
	return res;
}

int main(void){
	n=read(),X=read(),Y=read();
	for(reg int i=1;i<=n;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		a[i]=Interval(x1,x2);
		b[i]=Interval(y1,y2);
	}
	reg int ansx=solve(n,a,X);
	reg int ansy=solve(n,b,Y);
	reg ll ans=1ll*ansx*ansy;
	printf("%lld\n",ans);
	return 0;
}
```

随机化算法的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e5+5;

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(min(l,r)),r(max(l,r)){
		return;
	}
};

int n,X,Y;
Interval a[MAXN];
Interval b[MAXN];

struct Event{
	int x;
	ull val;
	inline Event(reg int x=0,reg ull val=0):x(x),val(val){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x;
	}
};

struct Segment{
	int len;
	ull val;
	inline Segment(reg int len=0,reg ull val=0):len(len),val(val){
		return;
	}
	inline bool operator<(const Segment& a)const{
		return val<a.val;
	}
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int solve(reg int n,reg Interval a[],reg int X){
	vector<Event> E;
	E.reserve((n+1)<<1);
	for(reg int i=1;i<=n;++i){
		reg ull tag=rng();
		E.push_back(Event(a[i].l,tag));
		E.push_back(Event(a[i].r,tag));
	}
	E.push_back(Event(0,0));
	E.push_back(Event(X,0));
	sort(E.begin(),E.end());
	vector<Segment> V;
	reg ull val=0;
	for(reg int i=0,siz=E.size();i<siz-1;++i){
		val^=E[i].val;
		if(E[i].x<E[i+1].x)
			V.push_back(Segment(E[i+1].x-E[i].x,val));
	}
	sort(V.begin(),V.end());
	reg ull las=0;
	reg int sum=0;
	reg int res=0;
	for(reg int i=0,siz=V.size();i<siz;++i){
		if(las==V[i].val)
			sum+=V[i].len;
		else
			las=V[i].val,sum=V[i].len;
		res=max(res,sum);
	}
	return res;
}

int main(void){
	n=read(),X=read(),Y=read();
	for(reg int i=1;i<=n;++i){
		static int x1,y1,x2,y2;
		x1=read(),y1=read(),x2=read(),y2=read();
		a[i]=Interval(x1,x2);
		b[i]=Interval(y1,y2);
	}
	reg int ansx=solve(n,a,X);
	reg int ansy=solve(n,b,Y);
	reg ll ans=1ll*ansx*ansy;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：__ycx2010__ (赞：4)

### 思路

首先容易发现横纵都是相互独立的，于是问题变为给定 $n$ 个线段 $(l,r)$，每个线段可以不变或者变为补集 $(0,l) \cup (r,M)$。

对坐标离散化，然后枚举所有不包含节点的小段，由于每一条线段要么在当前状态下包含此小段，要么在补集状态下包含，所以所有线段的状态一定是固定的。

两个不同的小段能相加，当且仅当它们的线段的状态一致，所以我们要采用哈希，设当前端为 $s$，被一条线段 $l$ 包含表示为 $s\in l$，则其哈希值为 $hash(s)=\bigoplus_{i=1}^n [s \in l_i] val_i$（其中 $val_i$ 为随机生成的值）。

然后用 map 维护相同哈希值的小段的权值和。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1000010;
int n, X, Y;
ll change[N];
vector<pair<int, int>> EX, EY;

int solve(vector<pair<int, int>> E, int m) {
	memset(change, 0, sizeof change);
	vector<int> v;
	for (auto i : E) v.push_back(i.first), v.push_back(i.second);
	v.push_back(0), v.push_back(m);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	unordered_map<ll, int> ma, ma2;
	for (int i = 0; i < v.size(); i ++ ) ma[v[i]] = i;
	for (auto &i : E) {
		ll val = 1ll * rand() * rand() * rand() * rand();
		i.first = ma[i.first], i.second = ma[i.second];
		change[i.second] ^= val;
		change[i.first] ^= val;
	}
	ll r = 0;
	int ans = 0;
	for (int i = 0; i < v.size() - 1; i ++ ) {
		r ^= change[i];
		ma2[r] += v[i + 1] - v[i];
		ans = max(ans, ma2[r]);
	}
	return ans;
}

int main() {
	srand(time(0));
	scanf("%d%d%d", &n, &X, &Y);
	for (int i = 1; i <= n; i ++ ) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		EX.push_back({x1, x2});
		EY.push_back({y1, y2});
	}
	sort(EX.begin(), EX.end());
	sort(EY.begin(), EY.end());
	int xlen = solve(EX, X);
	int ylen = solve(EY, Y);
	printf("%lld\n", 1ll * xlen * ylen);
	return 0;
}
```

---

## 作者：DengDuck (赞：3)

这题显然每一维都是独立的，我们应该单独考虑并分别最大化。

线段要么向内连，要么向外连。

我们发现，对于每个格子，想要在一条线段中，线段的状态是唯一的。

我们考虑将所有线段的状态转换为数值来保存，来表示一种方案，这一点可以考虑随机权值哈希，给每个线段随机一个权值，如果方案中线段向内连，那么就加上这个权值。

那么我们可以用点差分小科技，就可以算出每个格子对应的线段的哈希权值，进一步得出每种哈希权值对应格子长度，统计最长的即可。

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define X first
#define Y second
using namespace std;
const LL N=5e5+5;
vector<pair<LL,LL> >xl,yl,v;
map<LL,LL>ma;
LL n,x,y,xx,yy,mxx,mxy;
LL rd()
{
	LL a=rand()*rand(),b=rand()*rand();
	return a*b;
}
LL work(vector<pair<LL,LL> >li,LL Mx)
{
	ma.clear(),v.clear();
	for(auto i:li)
	{
		LL val=rd();
		v.push_back({i.X,val});
		v.push_back({i.Y,val});
	}
	v.push_back({0,0});
	v.push_back({Mx,0});
	sort(v.begin(),v.end());
	LL len=v.size(),sum=0;
	for(int i=0;i<len-1;i++)
	{
		sum^=v[i].Y;
		if(v[i].X<v[i+1].X)ma[sum]+=v[i+1].X-v[i].X;
	}
	LL mx=0;
	for(auto i:ma)
	{
		mx=max(mx,i.Y);
	}
	return mx;
}
int main()
{
	srand(time(0));
	scanf("%lld%lld%lld",&n,&mxx,&mxy);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld%lld",&x,&y,&xx,&yy);
		if(x>xx)swap(x,xx);
		if(y>yy)swap(y,yy);
		xl.push_back({x,xx});
		yl.push_back({y,yy});
	}
	printf("%lld",work(xl,mxx)*work(yl,mxy));
}
```

---

## 作者：b6e0_ (赞：2)

[题目链接](/problem/P5987)

确定性单 $\log$ 数据结构题解。

和其他做法一样，两维独立开来，下面考虑一维问题。

离散化，使得值域大小变为 $\mathcal O(n)$，这个大小设为 $m$。而对于每一个在 $[1,m]$（下标从 $1$ 开始）中的 $i$，对应的其实是原值域上的一段区间，记这个区间大小为 $a_i$。下文中的位置都指的是离散化后的位置。

对于一对位置 $x,y$，它们能同时对答案产生贡献，当且仅当对于每一个区间 $i$，$i$ 同时包含或者同时不包含 $x,y$。假如我们用一个二进制数 $s_x$ 表示每个区间对 $x$ 这个位置的覆盖情况，那么将 $s_x$ 相同的位置归为一类，一类的答案就是这一类中每个 $x$ 的 $a_x$ 和，最后的答案就是所有类答案的最大值。

考虑对于每一个 $i$，求出最小的 $j$ 使得 $i$ 和 $j$ 在同一类。将所有区间 $[l,r]$ 按照在 $i$ 左边（$r<i$）、包含 $i$（$l\le i\le r$）、在 $i$ 右边（$l>i$）分别分成三类。

因为 $j\le i$，所以第三类区间对 $j$ 没有限制。

然后考虑第二类区间，令 $j_0$ 为它们 $l$ 的最大值（如果不存在第二类区间则 $j_0=1$），则一定有 $j\ge j_0$。通过枚举 $i$ 时维护一个 set 可以 $\mathcal O(n\log n)$ 地求出每个 $j_0$。

最后考虑第一类区间的限制。对于一个第一类区间 $[l,r]$，如果有 $l\le j_0\le r$，那么 $j$ 的更严格的一个下界是 $r+1$。将 $j_0$ 调整为 $r+1$，继续寻找包含 $j_0$ 的区间并调整下界，不断重复这个过程，直到不能再调整，此时 $j_0$ 就是 $j$。

这个过程很像并查集找父亲，所以考虑用并查集维护这个过程。具体来说，当一个第二类区间 $[l,r]$ 变为第一类区间时，将 $[l,r]$ 内的所有位置的父亲设为 $r+1$。这样我们只需要查询初始 $j_0$ 的祖先就能找到最终的 $j$。容易证明这样做是正确的。

这个过程可以等价于，在序列上将 $[l,r]$ 中的所有位置删去，查询 $j_0$ 后第一个没有删去的位置。$[l,r]$ 内已经删去的点显然不必再删，所以我们从 $l$ 开始，每次删去一个点后，用 getfather 操作跳过中间已经被删过的点，直到处理完 $[l,r]$ 内的所有点。这样每个点只会被删除一次，加上并查集查询的复杂度，这部分是 $\mathcal O(n\alpha(n))$ 的。

总时间复杂度 $\mathcal O(n\log n)$。代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define y1 _y1
int read()
{
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
struct range
{
	int l,r;
}a[500005],b[500005];
int n,c[1000005],fa[1000005],res[1000005],tot[1000005];
vector<int>le[1000005];
int get(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=get(fa[x]);
}
int solve(range*a,int X)
{
	int m=0,i,j;
	multiset<int>st;
	for(i=1;i<=n;i++)
	{
		if(a[i].l)
			c[++m]=a[i].l;
		c[++m]=a[i].r;
	}
	c[++m]=X;
	sort(c+1,c+m+1);
	m=unique(c+1,c+m+1)-c-1;
	for(i=1;i<=m;i++)
	{
		le[i].clear();
		fa[i]=i;
		res[i]=tot[i]=0;
	}
	fa[m+1]=m+1;
	for(i=1;i<=n;i++)
	{
		a[i].l=lower_bound(c,c+m+1,a[i].l)-c+1;
		a[i].r=lower_bound(c,c+m+1,a[i].r)-c;//离散化
		tot[a[i].l]++;
		le[a[i].r].push_back(a[i].l);
	}
	st.insert(1);
	for(i=1;i<=m;i++)
	{
		while(tot[i]--)
			st.insert(i);
		res[get(*st.rbegin())]+=c[i]-c[i-1];
		for(j=0;j<le[i].size();j++)
		{
			st.erase(st.find(le[i][j]));
			int x=get(le[i][j]);
			while(x<=i)//删去区间
			{
				fa[x]=i+1;
				x=get(x+1);
			}
		}
	}
	int ans=0;
	for(i=1;i<=m;i++)
		ans=max(ans,res[i]);
	return ans;
}
int main()
{
	n=read();
	int X=read(),Y=read();
	for(int i=1;i<=n;i++)
	{
		int x1=read(),y1=read(),x2=read(),y2=read();
		a[i]={min(x1,x2),max(x1,x2)};
		b[i]={min(y1,y2),max(y1,y2)};
	}
	printf("%lld",(long long)solve(a,X)*solve(b,Y));
	return 0;
}
```

---

下面是口胡的，不保证正确，如有错误麻烦在评论区指出，谢谢。

如果值域缩小到 $10^6$ 左右，哈希做法可以做到线性。对于这个做法，瓶颈在 set 维护最大值，考虑优化。我们的目标是对于每个位置求出 $mx_i$ 表示包含 $i$ 的区间的 $l$ 的最大值。将所有区间按 $l$ 从大到小枚举，每次我们要做的就是将 $[l,r]$ 内之前未被赋值过的 $mx_i$ 赋值为 $l$。这个过程显然也是在区间上删除位置，可以用并查集解决。

这样可以做到 $\mathcal O(n\alpha(n))$。貌似有不实用的科技能将这个并查集优化到 $\mathcal O(n)$。

---

## 作者：5k_sync_closer (赞：1)

两维独立，问题变为给一堆线段，每个线段可以选中间或两边，求选出的东西之交最大是多少。

按端点把数轴分段，则钦定任意一段在最终的交中，就可以确定所有线段的选择方案。

定义 $f(i)$ 表示钦定 $i$ 段在最终的交中时交的大小，则答案为 $\max f(i)$。

考虑从左往右依次钦定每段在最终的交中，则所有线段初始都选两边，

钦定到一条线段内部时这条线段切换为选中间，再次钦定到一条线段外部时这条线段切换为选两边。

## Sol 1

考虑扫描时，线段树维护当前选择方案下，每段被覆盖多少次。

则切换选择方案相当于区间加减，当前 $f(i)$ 为 $n$ 的个数。

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int n, X, Y, l1[500050], r1[500050], l2[500050], r2[500050];
inline int R()
{
    int q = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        q = q * 10 + c - '0', c = getchar();
    return q;
}
struct S
{
    struct T
    {
        int v, w, z;
        T() : v(0), w(0), z(0) {}
    } R[1000050 << 2];
    struct E
    {
        int v, w, t;
    } e[1000050];
    int c, h[1000050], b[1000050];
    inline void A(int u, int v, int w)
    {
        e[++c] = {v, w, h[u]};
        h[u] = c;
    }
    inline void u(int p)
    {
        if (R[p << 1].v == R[p << 1 | 1].v)
            R[p].v = R[p << 1].v, R[p].w = R[p << 1].w + R[p << 1 | 1].w;
        if (R[p << 1].v > R[p << 1 | 1].v)
            R[p].v = R[p << 1].v, R[p].w = R[p << 1].w;
        if (R[p << 1].v < R[p << 1 | 1].v)
            R[p].v = R[p << 1 | 1].v, R[p].w = R[p << 1 | 1].w;
    }
    inline void f(int p, int x)
    {
        R[p].v += x;
        R[p].z += x;
    }
    inline void d(int p)
    {
        if (R[p].z)
            f(p << 1, R[p].z), f(p << 1 | 1, R[p].z), R[p].z = 0;
    }
    void B(int s, int t, int p)
    {
        if (s == t)
        {
            R[p].w = b[s + 1] - b[s];
            return;
        }
        int m = s + t >> 1;
        B(s, m, p << 1);
        B(m + 1, t, p << 1 | 1);
        u(p);
    }
    void M(int l, int r, int x, int s, int t, int p)
    {
        if (l <= s && t <= r)
            return f(p, x);
        d(p);
        int m = s + t >> 1;
        if (l <= m)
            M(l, r, x, s, m, p << 1);
        if (r > m)
            M(l, r, x, m + 1, t, p << 1 | 1);
        u(p);
    }
    int Q(int *l, int *r, int X)
    {
        memset(R, 0, sizeof R);
        memset(b, 0, sizeof b);
        int m = 0, q = 0;
        c = 0;
        for (int i = 1; i<= 1e6; ++i)
            h[i] = 0;
        b[++m] = 0;
        b[++m] = X;
        for (int i = 1; i <= n; ++i)
            b[++m] = l[i], b[++m] = r[i];
        sort(b + 1, b + m + 1);
        m = unique(b + 1, b + m + 1) - b - 1;
        for (int i = 1; i <= n; ++i)
        {
            A(l[i] = lower_bound(b + 1, b + m + 1, l[i]) - b, i, 1);
            A(r[i] = lower_bound(b + 1, b + m + 1, r[i]) - b, i, 2);
        }
        B(1, m - 1, 1);
        for (int i = 1; i <= n; ++i)
        {
            if (l[i] != 1)
                M(1, l[i] - 1, 1, 1, m - 1, 1);
            if (r[i] != m)
                M(r[i], m - 1, 1, 1, m - 1, 1);
        }
        for (int i = 1; i < m; ++i)
        {
            for (int v = h[i]; v; v = e[v].t)
            {
                int j = e[v].v;
                if (e[v].w == 1)
                {
                    if (l[j] != 1)
                        M(1, l[j] - 1, -1, 1, m - 1, 1);
                    if (r[j] != m)
                        M(r[j], m - 1, -1, 1, m - 1, 1);
                    if (l[j] != r[j])
                        M(l[j], r[j] - 1, 1, 1, m - 1, 1);
                }
                else
                {
                    if (l[j] != r[j])
                        M(l[j], r[j] - 1, -1, 1, m - 1, 1);
                    if (l[j] != 1)
                        M(1, l[j] - 1, 1, 1, m - 1, 1);
                    if (r[j] != m)
                        M(r[j], m - 1, 1, 1, m - 1, 1);
                }
            }
            q = max(q, R[1].w);
        }
        return q;
    }
} SA, SB;
signed main()
{
    // freopen("globe.in", "r", stdin);
    // freopen("globe.out", "w", stdout);
    n = R();
    X = R();
    Y = R();
    for (int i = 1; i <= n; ++i)
    {
        l1[i] = R(), l2[i] = R(), r1[i] = R(), r2[i] = R();
        if (l1[i] > r1[i])
            swap(l1[i], r1[i]);
        if (l2[i] > r2[i])
            swap(l2[i], r2[i]);
    }
    printf("%lld", 1ll * SA.Q(l1, r1, X) * SA.Q(l2, r2, Y));
    return 0;
}
```


## Sol 2

考虑哈希当前选择方案，对每条线段随机赋权，线段 $i$ 的权值 $v_i$ 为 $\begin{cases}a_i&i\text{ 在当前方案中选中间}\\b_i&i\text{ 在当前方案中选两边}\end{cases}$，其中 $a_i,b_i$ 随机生成,

则钦定 $i$ 段必选时，选择方案的哈希值 $h_i$ 为 $\sum v_j$，于是 $f(i)$ 即为哈希值与其相同的段的长度之和。

```cpp
%:include <cstdio>
%:include <cstring>
%:include <vector>
%:include <algorithm>
%:include <unordered_map>
#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
using namespace std;
char buf[1 << 23], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
int n, X, Y, l1[500050], r1[500050], l2[500050], r2[500050];
inline int R()
{
    int q = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        q = q * 10 + c - '0', c = getchar();
    return q;
}
struct S
{
    struct Z
    {
        int x, y;
        bool operator<(Z b) const { return x < b.x; }
    };
    int c, b[1000050], U[1000050], V[1000050];
    Z P[1000050];
    int Q(int *l, int *r, int X)
    {
        unordered_map<unsigned long long, int> C;
        int m = 0, q = 0;
        unsigned long long Z = 0;
        b[++m] = 0;
        b[++m] = X;
        for (int i = 1; i <= n; ++i)
            b[++m] = l[i], b[++m] = r[i], U[i] = rand(), V[i] = rand();
        sort(b + 1, b + m + 1);
        m = unique(b + 1, b + m + 1) - b - 1;
        c = 0;
        for (int i = 1; i <= n; ++i)
        {
            P[++c] = {l[i] = lower_bound(b + 1, b + m + 1, l[i]) - b, i};
            P[++c] = {r[i] = lower_bound(b + 1, b + m + 1, r[i]) - b, -i};
        }
        sort(P + 1, P + c + 1);
        for (int i = 1; i <= n; ++i)
            Z += U[i];
        for (int i = 1, p = 0; i < m; ++i)
        {
            while (p < c && P[p + 1].x <= i)
            {
                ++p;
                if (P[p].y > 0)
                    Z = Z - U[P[p].y] + V[P[p].y];
                else
                    Z = Z - V[-P[p].y] + U[-P[p].y];
            }
            q = max(q, C[Z] += b[i + 1] - b[i]);
        }
        return q;
    }
} SA;
signed main()
{
    // freopen("globe.in", "r", stdin);
    // freopen("globe.out", "w", stdout);
    srand(388651);
    n = R();
    X = R();
    Y = R();
    for (int i = 1; i <= n; ++i)
        l1[i] = R(), l2[i] = R(), r1[i] = R(), r2[i] = R();
    printf("%lld", 1ll * SA.Q(l1, r1, X) * SA.Q(l2, r2, Y));
    return 0;
}
```


---

## 作者：Eznibuil (赞：1)

这是个甜甜圈。

简单手模以后可以发现 $x$ 坐标与 $y$ 坐标独立，于是转化为一维的问题。

可以发现对于每一个段，只有一种方法使得这个段被所有区间覆盖。

于是考虑所有区间的覆盖都未跨越一端（即没有分成两半），将其作为基准。

这样段就可以以哪些区间覆盖了它分类，同类的长度相加以更新答案。

显然 $n^2$ 记录是不现实的，所以考虑随机哈希。异或比较好，但是加法乘法也行。

用差分的方法覆盖每个区间即可。

时间复杂度 $O(n\log n)$。不过小心，正确率没有想象中的高，原因是异或线性基大小最多值域的对数。（我手气很好，第一次运行就跑出错误答案。）
```cpp
#include<stdio.h>
#include<algorithm>
#include<random>
typedef unsigned long long ull;
ull h[500001],hx,hy;
struct dot
{
	int p,id;
}ex[1000001],ey[1000001];
struct ha
{
	int len;
	ull id;
}sx[1000001],sy[1000001];
int main()
{
	std::mt19937_64 rng;
	int n,x,y,mx=0,my=0;
	scanf("%d%d%d",&n,&x,&y);
	for(int i=0,xl,yl,xr,yr;i<n;i++)
		scanf("%d%d%d%d",&xl,&yl,&xr,&yr),ex[i<<1]=dot{xl,i},ex[i<<1|1]=dot{xr,i},ey[i<<1]=dot{yl,i},ey[i<<1|1]=dot{yr,i},h[i]=rng();
	std::sort(ex,ex+(n<<1),[](const dot&a,const dot&b){return a.p<b.p;}),std::sort(ey,ey+(n<<1),[](const dot&a,const dot&b){return a.p<b.p;});
	for(int i=0;i<n<<1;i++)
		sx[i]=ha{i<(n<<1)-1?ex[i+1].p-ex[i].p:ex[0].p+x-ex[i].p,hx^=h[ex[i].id]};
	std::sort(sx,sx+(n<<1),[](const ha&a,const ha&b){return a.id<b.id;});
	for(int i=x=0;i<n<<1;i++)
		if(i&&sx[i].id>sx[i-1].id)
			mx<x?mx=x:0,x=sx[i].len;
		else
			x+=sx[i].len;
	if(mx<x)
		mx=x;
	for(int i=0;i<n<<1;i++)
		sy[i]=ha{i<(n<<1)-1?ey[i+1].p-ey[i].p:ey[0].p+y-ey[i].p,hy^=h[ey[i].id]};
	std::sort(sy,sy+(n<<1),[](const ha&a,const ha&b){return a.id<b.id;});
	for(int i=y=0;i<n<<1;i++)
		if(i&&sy[i].id>sy[i-1].id)
			my<y?my=y:0,y=sy[i].len;
		else
			y+=sy[i].len;
	if(my<y)
		my=y;
	printf("%llu",1ull*mx*my);
	return 0;
}
```

---

## 作者：binbin_200811 (赞：0)

# P5987 [PA2019] Terytoria / 2023NOIP A层联测13  T3 全球覆盖

[题面及数据范围](https://www.luogu.com.cn/problem/P5987)

对于一个点对，可以降维为线段，转化为 $1$ 维的问题。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/f6e6aa4i.png)

我们可以在横着的方向和竖着的方向个选择一种颜色的线段，任意一种选择可以构成一个合法的矩形。

我们需要求最大重叠面积，可以转化为两个一维的求最大公共线段交的问题，最后将答案相乘即为原问题。（横着选和竖着选互不干扰）

一维的问题为：

在数轴上有若干条线段，线段有一个起点和一个终点，选择这条线段或选择这条线段的补集，求最大公共交集。

先分析线段数小于 $64$ 的情况。

我们给每一条线段左端点和右端点一个相同的值 $val$，$val$ 为 $2$ 的整数次方且每个 $val$ 各不相同。

如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/59xcncv8.png)

$f[i]$ 为取到第 $i$ 个点的选择情况，$f[i]=f[i-1]\bigoplus val[i]$。

如果 $f[i]$ 中第 $i$ 位为 $1$ 表示需要选这条线段才可以选这个点。

求相同 $f[i]$ 的点有多少即可。

如果大于 $64$ 我们无法给每个线段分配唯一的 $val$ 值，我们可以在 $[0,2^{64}]$ 中随机一个数作为 $val$ 值。

尽管可能有错误，不过根据生日悖论正确率高达 $99.9936\%$。

#### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define int long long
#define piu pair<int,ull>

mt19937_64 rnd(random_device{}());

const int maxn=1e6+5;

int n,x,y;
int a[2][maxn];

piu b[maxn];

int sv(int *a,int X)
{
    for(int i=0;i<n;i+=2)
    {
        ull v=rnd();
        b[i]=make_pair(a[i],v);
        b[i+1]=make_pair(a[i+1],v);
    }
    ull now=0;sort(b,b+n);
    unordered_map<ull,int>mp;
    b[n].first=X;
    mp[0]=b[0].first;
    for(int i=0;i<n;i++)
    {
        now^=b[i].second;mp[now]+=b[i+1].first-b[i].first;
    }
    int ans=0;
    for(auto v:mp) ans=max(ans,v.second);
    return ans;
}

signed main()
{
    scanf("%lld%lld%lld",&n,&x,&y);
    n<<=1;
    for(int i=0;i<n;i++) for(int j=0;j<2;j++) scanf("%lld",&a[j][i]);
    printf("%lld",sv(a[0],x)*sv(a[1],y));
}
```



---

## 作者：Meteor_ (赞：0)

# P5987 [PA2019] Terytoria 题解

## 题目大意

[题意不易描述所以给个传送门。](https://www.luogu.com.cn/problem/P5987)

## 题解

因为我模拟赛赛时没想出来所以我来写篇题解。

手玩一下或者感性理解一下可以发现，横纵坐标可以分开考虑。

分开后横纵是一样的处理方法，只讲横着的。

值域较大，先对坐标进行离散化。

我们将所有端点都称作关键点，那么每两个相邻的关键点会夹出一个线段。我们对于每一个线段，直接考虑如果要让这个线段产生贡献，所有矩形的选择情况。把所有矩形的选择情况哈希一下。

我们对于每一种所有矩形的选择情况，会有很多线段，这种情况产生的贡献就是这些线段长度的和。我们选一个长度最大的。

横纵都选出的长度最大的，相乘就是答案。

考虑怎么实现上述过程。

如果每一条线段都枚举所有矩形，显然时间复杂度过不去，所以对于每一个关键点，预处理出这个关键点会有哪些矩形的选择情况会变。这个是 $O(n)$ 的。然后再从左往右枚举关键点，初始哈希值为 $0$，枚举到一个关键点直接让哈希值加上当前关键点的哈希值。这也是 $O(n)$ 的。

所以复杂度瓶颈在离散化的排序，$O(n \log n)$。但是后面的实现常数也不小。

实现不是很难，就不再细讲了。

## 代码

```
#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;

inline int read() {
    int x = 0, s = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9') {
        if(ch == '-')
            s = -s;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * s;
}

void write(int x) {
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + 48);
}

const int M = 1000005;
const int base = 13331;
int n, X, Y, w1[M], w2[M], len1, len2, has[M], cur, maxn1, maxn2, vec1[M << 1], vec2[M << 1];
pair<int, int> hang[M], lie[M];
unordered_map<int, int> mp;

inline void pre() {
    has[0] = 1;
    for(int i = 1; i <= n; ++ i)
        has[i] = has[i - 1] * base;
}

signed main() {
    n = read();
    X = read();
    Y = read();
    pre();
    for(int i = 1; i <= n; ++ i) {
        hang[i].first = read();
        lie[i].first = read();
        hang[i].second = read();
        lie[i].second = read();
        w1[++ len1] = hang[i].first;
        w1[++ len1] = hang[i].second;
        w2[++ len2] = lie[i].first;
        w2[++ len2] = lie[i].second;
    }
    w1[++ len1] = X;
    w2[++ len2] = Y;
    stable_sort(w1 + 1, w1 + 1 + len1);
    stable_sort(w2 + 1, w2 + 1 + len2);
    len1 = unique(w1 + 1, w1 + 1 + len1) - w1 - 1;
    len2 = unique(w2 + 1, w2 + 1 + len2) - w2 - 1;
    for(int i = 1; i <= n; ++ i) {
        hang[i].first = lower_bound(w1 + 1, w1 + 1 + len1, hang[i].first) - w1;
        hang[i].second = lower_bound(w1 + 1, w1 + 1 + len1, hang[i].second) - w1;
        lie[i].first = lower_bound(w2 + 1, w2 + 1 + len2, lie[i].first) - w2;
        lie[i].second = lower_bound(w2 + 1, w2 + 1 + len2, lie[i].second) - w2;
        vec1[hang[i].first] += has[i];
        vec1[hang[i].second] -= has[i];
        vec2[lie[i].first] += has[i];
        vec2[lie[i].second] -= has[i];
    }
    for(int i = 1; i <= len1; ++ i) {
        mp[cur] += w1[i] - w1[i - 1];
        maxn1 = max(maxn1, mp[cur]);
        cur += vec1[i];
    }
    mp.clear();
    for(int i = 1; i <= len2; ++ i) {
        mp[cur] += w2[i] - w2[i - 1];
        maxn2 = max(maxn2, mp[cur]);
        cur += vec2[i];
    }
    write(maxn1 * maxn2);
}
```

---

