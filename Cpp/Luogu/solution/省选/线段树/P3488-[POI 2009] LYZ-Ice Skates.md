# [POI 2009] LYZ-Ice Skates

## 题目描述

滑冰俱乐部初始有 $[1,n]$ 号码溜冰鞋各 $k$ 双，已知 $x$ 号脚的人可以穿 $[x,x+d]$ 号码的鞋子。

现在有 $m$ 次操作，每次两个数 $r,x$，表示来了 $x$ 个 $r$ 号脚的人，$x$ 为负则表示离开。在每次操作之后，你需要判断溜冰鞋是否足够。

## 说明/提示

$n\le 2\times 10^5,m\le 5\times 10^5,k\le 10^9,1\le r_i\le n-d,-10^9\le x_i\le 10^9,0\le d<n$

## 样例 #1

### 输入

```
4 4 2 1
1 3
2 3
3 3
2 -1
```

### 输出

```
TAK
TAK
NIE
TAK
```

# 题解

## 作者：大菜鸡fks (赞：18)

这题好妙啊。

首先不看数据范围是二分图匹配的裸题。但显然会爆炸。

从暴力的做法入手，进行思考。这里引用一个Hall定理：对于一个二分图，设左边有个n点，右边有个m点，则左边个点能完全匹配的充要条件是：对于1<=i<=n,左面任意i个点，都至少有i个右面的点与它相连。

要满足如上条件，从最劣情况入手，显然选择连续型号的人会使右边与他相连的人最少。设a[i]为选择i这个型号的人的数量,sum[l,r]为a[l..r]的总和。

那么对于任意的sum[l,r]<=(r-l+1+d)*k

可以换一下形式。

设s[l,r]为l<=i<=r, a[i]-k的和。

那么对于任意的l,r，s[l,r]<=d*k

于是这题就变成动态维护最大子段和了，线段树即可。

```cpp
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
const int N=2e5+5;
struct node{
	int lmx,rmx,sum,ans;
}a[N<<2];
int n,m,K,d;
inline void pushup(int k){
	a[k].sum=a[k<<1].sum+a[k<<1|1].sum;
	a[k].lmx=max(a[k<<1].lmx,a[k<<1].sum+a[k<<1|1].lmx);
	a[k].rmx=max(a[k<<1|1].rmx,a[k<<1|1].sum+a[k<<1].rmx);
	a[k].ans=max(a[k<<1].ans,max(a[k<<1|1].ans,a[k<<1].rmx+a[k<<1|1].lmx));
}
void build(int k,int l,int r){
	if (l==r){
		a[k]=(node){0,0,-K,-K};
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	pushup(k);
}
void update(int k,int l,int r,int x,int y){
	if (l==r){
		a[k].ans+=y; a[k].sum+=y;
		a[k].lmx=a[k].rmx=max(a[k].sum,0ll);
		return;
	}
	int mid=(l+r)>>1;
	if (mid>=x) update(k<<1,l,mid,x,y);
	   else update(k<<1|1,mid+1,r,x,y);
	pushup(k);
}
inline void init(){
	n=read(); m=read(); K=read(); d=read();
	build(1,1,n);
}
inline void solve(){
	for (int i=1;i<=m;i++){
		int x=read(),y=read();
		update(1,1,n,x,y);
		if (a[1].ans<=K*d) puts("TAK"); else puts("NIE");
	}
}
signed main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：Yanami_Anna (赞：8)

> 这是一道关于溜冰和搭脚的题目。

很裸的，看上去像是一个二分图，把人和靴子切割一下然后一堆人连过去然后看有没有针对人的点的最大匹配。

然后我们发现我们知道一个 Hall 定理对吧，他有一个炫酷的变式就是他只针对一边也是可行的，就会变成这一边的所有点是否都会被匹配上。

那太好玩啦！问题突然就变成了我们现在对于他们的区间的并的大小要做文章，然后我们发现不同段之间是一丁点关系都没有的，所以我们考虑同段的情况，假设现在 $[lt,rt]$ 是一个同段的一群人，设脚的大小为 $u$ 的人数有 $a_u$ 个，则根据 Hall 定理，有 $\sum_{i=lt}^{rt}a_i\leqslant (rt-lt+1+d)k$。

嚯！这有什么用？现在他看着没有用是因为他依赖于区间长度，我们考虑把右边的 $(rt-lt+1)k$ 挪左边去，把这些 $k$ 分下去，你一看，$\sum_{i=lt}^{rt}(a_i-k)\leqslant dk$，我去，变魔法了，那你看这个东西右边不依赖于任何区间相关信息，那只需要让左边最大就行了啊，左边这个东西最大，支持单点修改，我去，这不是我们最大子段和吗，下次出题记得注明出处。

然后就变成了线段树挠掺题。

---

## 作者：i207M (赞：6)

写这道题解的主要目的是说一下自己YY的另一道题；

首先希望管理员补全题面，原题保证了$r+d<=n$，这样就简单很多了；

考虑我们什么时候是无解？

当且仅当$sum(l,r)-k\times (r-l+1+d)>0$，就是人比鞋子多的意思；

移项，可得$\sum_l^r val-k > k\times d$，所以说，我们只要用线段树维护区间最大子段和，然后和kd比较即可；

然后我们可以考虑加强版：$r+d>n$的情况：

将式子改一下：$sum(l,r)-k\times (n-l+1)>0(r+d>n)$，移项

$sum(l,r)+k\times l>k\times (n+1)$，于是我们要维护一个区间的和加上左端点的编号乘一个常数的最大值；

看似很难维护，但是发现一个性质：最优解的区间一定是$r=n$，因为左端点不变，每个点权值非负，所以一定越往右越优；所以用线段树维护$i...n$的答案，区间加，查询区间最大值即可；

（代码是第一种情况的）

```cpp
namespace i207M
{
template<class T>il void in(T &x)
{
	x=0; bool f=0; char c=getchar();
	while(c<'0'||c>'9') 
	{
		if(c=='-') f=1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=x*10+(c^'0'),c=getchar();
	if(f) x=-x;
}

#define int LL
#define N 500005
#define M N<<2
#define ls (x<<1)
#define rs (x<<1|1)
#define gm int mid((l+r)>>1)
int n,k,m,d;
const int rt=1;
struct Node
{
	int sum,mx,pre,bak;
	Node(const int v=0)
	{
		sum=mx=pre=bak=v;
	}
}tre[M];
il void up(int x)
{
	tre[x].sum=tre[ls].sum+tre[rs].sum;
	tre[x].mx=max(tre[ls].bak+tre[rs].pre,max(tre[ls].mx,tre[rs].mx));
	tre[x].pre=max(tre[ls].pre,tre[ls].sum+tre[rs].pre);
	tre[x].bak=max(tre[rs].bak,tre[rs].sum+tre[ls].bak);
}
il Node up(const Node &L,const Node &R)
{
	Node res;
	res.sum=L.sum+R.sum;
	res.mx=max(L.bak+R.pre,max(L.mx,R.mx));
	res.pre=max(L.pre,L.sum+R.pre);
	res.bak=max(R.bak,R.sum+L.bak);
	return res;
}
void build(int x,int l,int r)
{
	if(l==r)
	{
		tre[x]=Node(-k);
		return;
	}
	gm;
	build(ls,l,mid), build(rs,mid+1,r);
	up(x);
}
Node ask(int x,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return tre[x];
	gm; Node L,R;
	if(ql<=mid) L=ask(ls,l,mid,ql,qr);
	if(qr>mid) R=ask(rs,mid+1,r,ql,qr);
	return up(L,R);
}
void upd(int x,int l,int r,int p,int k)
{
	if(l==r)
	{
		tre[x]=Node(tre[x].sum+k);
		return;
	}
	gm;
	if(p<=mid) upd(ls,l,mid,p,k);
	else upd(rs,mid+1,r,p,k);
	up(x);
}

signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
#endif
	
	in(n),in(m),in(k),in(d);
	build(rt,1,n);
	int r,x;
	while(m--)
	{
		in(r),in(x);
		upd(rt,1,n,r,x);
		int tmp=ask(rt,1,n,1,n).mx;
		if(tmp>k*d) puts("NIE");
		else puts("TAK");
	}
	return 0;
}

}
```



---

## 作者：Sincerin (赞：4)

[题目传送门！](https://www.luogu.com.cn/problem/P3488)

[更好的阅读体验？](https://www.luogu.com.cn/blog/sincerin520/solution-p3488)

## 题意

给定 $n$ 种号码的鞋，每种号码各 $k$ 双。已知 $x$ 号脚的人可以穿 $i\in[ \ x ,x+d \ ]$ 号码的鞋子。

现在可以进行 $m$ 次操作，每次给定两个数 $x$ 和 $v$，表示 $x$ 号脚的人来了 $v$ 个。$v$ 可以为负数，表示离开 $v$ 个人。

对于每次操作，输出一行一个 `TAK` 或 `NIE` 表示鞋子是否足够。

- $1 \leq d \leq  n \leq 2 \times 10^ 5 $
- $1 \leq k \leq 10^9 \ , 1 \leq m \leq 5 \times 10^ 5  $

## 解析

首先记 $cnt_i \ (i \in [l,r])$ 为区间 $[l,r]$ 中 $i$ 号码出现的次数。则这个区间满足要求当且仅当 $\sum_{i=l}^r{cnt_i} \leq  k \times [ (r-l+1) +d ]$。

接下来再来化简一下柿子：

$$\sum_{i=l}^r{cnt_i} \leq  k \times (r-l+1+d) $$

化简，得：

$$ \sum_{i=l}^r{cnt_i} \leq  k \times (r-l+1)+k \times d $$
$$ \sum_{i=l}^r{cnt_i} \leq  \sum_{i=l}^r{k}+k \times d $$

移项，得：


$$\sum_{i=l}^r{cnt_i}-\sum_{i=l}^r{k} \leq k \times d$$

合并同类项，得：

$$ \sum_{i=l}^r{cnt_i-k} \leq  k \times d $$


也就是说只要该区间的 $ \sum_{i=l}^r{cnt_i-k} $ 的最大值要小于等于 $k \times d $。

即整个序列的最大子段和要小于等于 $k \times d$。

综上，只需维护序列 $\{ cnt_i-k\}$ 的最大子段和即可。



考虑有修改操作，是动态最大子段和，使用线段树维护，每次单点修改，区间查询整个序列的最大子段和并判断是否小于等于 $k \times d $ 即可。

注意在建树的时候 $cnt_i$ 初始都是等于零的，所以一开始序列中的元素都为 $-k$。

本算法总体时间复杂度 $\Theta(m \log n)$。


- 坑点：翻译不做人。

- 要开 long long！

## AC Code

```cpp
// C++14(GCC9)-O2 2.01KB 835ms 24.94MB
#include<iostream>
#include<cstdio>  
using namespace std; 
#define int long long      
const int N=200005; 
int m,n,k,d,x,v;
#define lson(p) p<<1
#define rson(p) p<<1|1
struct SegmentTree{
    int l,r,dat;
    int sum,lmax,rmax;
    #define l(i) t[i].l
    #define r(i) t[i].r
    #define dat(i) t[i].dat
    #define sum(i) t[i].sum
    #define lmax(i) t[i].lmax
    #define rmax(i) t[i].rmax
}t[N<<2];
int a[N];
inline void pushup(int p)
{ 
    sum(p)=sum(lson(p))+sum(rson(p));
    lmax(p)=max(lmax(lson(p)),sum(lson(p))+lmax(rson(p)));
    rmax(p)=max(rmax(rson(p)),sum(rson(p))+rmax(lson(p)));
    dat(p)=max(max(dat(lson(p)),dat(rson(p))),rmax(lson(p))+lmax(rson(p)));
}
inline void build(int p,int l,int r)
{
    l(p)=l;  r(p)=r;
    if(l==r) 
    {
        dat(p)=sum(p)=lmax(p)=rmax(p)=-k;
        return;
    }
    register int mid=(l+r)>>1;
    build(lson(p),l,mid);
    build(rson(p),mid+1,r);
    pushup(p);
} 
inline void change(int p,int x,int y)
{
    if(l(p)==r(p))
    {
        dat(p)+=y; sum(p)+=y;
        lmax(p)+=y; rmax(p)+=y;
        return;
    } 
    register int mid=(l(p)+r(p))>>1;
    if(x<=mid) change(lson(p),x,y);
    else change(rson(p),x,y);
    pushup(p);
}
inline SegmentTree query(int p,int l,int r)
{
    if(l<=l(p)&&r>=r(p)) return t[p]; 
    register int mid=(l(p)+r(p))>>1; 
    if(l<=mid&&r>mid)
    {
    	SegmentTree lt=query(lson(p),l,r); 
		SegmentTree rt=query(rson(p),l,r);
    	SegmentTree ret; 
		ret.sum=lt.sum+rt.sum;
    	ret.lmax=max(lt.lmax,rt.lmax+lt.sum);
    	ret.rmax=max(rt.rmax,lt.rmax+rt.sum);
    	ret.dat=max(max(lt.dat,rt.dat),lt.rmax+rt.lmax);
    	return ret;
	}
	else
	{
		if(l<=mid) return query(lson(p),l,r);
    	if(r>mid) return query(rson(p),l,r);
   	}
}
signed main(void)
{  
	freopen("p3488.in","r",stdin); 
    scanf("%lld%lld%lld%lld",&n,&m,&k,&d); 
    build(1,1,n); 
    while(m--)
    {
    	scanf("%lld%lld",&x,&v); 
    	change(1,x,v);
    	if(query(1,1,n).dat<=d*k) puts("TAK"); 
		else puts("NIE"); 
	}
    return 0;
} 
```

[AC Record](https://www.luogu.com.cn/record/103021315)


---

## 作者：SamariumPhosphide (赞：3)

# 前置知识

霍尔定理给出了**判定二分图是否可以完美匹配的充要条件。**

假设 $A$ 与 $B$ 可以完美匹配，那么它的充要条件是：

+ $|A|=|B|$
+ 对于 $A$ 的任意一个子集 $x$，以及 $x$ 在 $B$ 中所能达到的节点的并 $y$，必须满足 $|x| \leq |y|$。

# 简单推导

运用 Hall 定理，可以得到 $\sum\limits_{i=l}^r num[i] \leq (r-l+1 + d) \times k$。换言之，任何一段人所对应的鞋子数量不能少于人的数量。  
然后我们发现右半部分可以拆成两份，$(r-l+1) \times k$ 和 $d \times k$，第一部分与 $l,r$ 有关，而第二部分为常量。  
我们把第一部分移到左面去，那么就可以得到 $\sum\limits_{i=l}^r (num[i] - k) \leq d \times k$。  
线段树维护即可。

# Code


```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 200010;

struct segmentTree {
  ll l, r;
  ll lmx, rmx, tmx, sum;
};

ll n, m, k, d;
ll r, x;
segmentTree tr[N<<2];

ll len(ll x) {
  return tr[x].r - tr[x].l + 1;
}

void pushup(ll x) {
  tr[x].sum = tr[x << 1].sum + tr[x << 1 | 1].sum;
  tr[x].lmx = max(tr[x << 1].lmx, tr[x << 1].sum + tr[x << 1 | 1].lmx);
  tr[x].rmx = max(tr[x << 1 | 1].rmx, tr[x << 1 | 1].sum + tr[x << 1].rmx);
  tr[x].tmx = max(tr[x << 1].rmx + tr[x << 1 | 1].lmx, max(tr[x << 1].tmx, tr[x << 1 | 1].tmx));
}

void build(ll x, ll l, ll r) {
  if (l == r) {
    tr[x] = (segmentTree) {l, r, -k, -k, -k, -k};
    return;
  } else {
    tr[x].l = l, tr[x].r = r;
    ll mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    pushup(x);
    return;
  }
}

void add(ll x, ll pos, ll toA) {
  if (len(x) == 1) {
    tr[x].lmx += toA;
    tr[x].rmx += toA;
    tr[x].tmx += toA;
    tr[x].sum += toA;
  } else {
    ll mid = (tr[x].l + tr[x].r) >> 1;
    if (pos <= mid) {
      add(x << 1, pos, toA);
    } else {
      add(x << 1 | 1, pos, toA);
    }
    pushup(x);
  }
}

signed main() {
  scanf("%lld %lld %lld %lld", &n, &m, &k, &d);
  build(1, 1, n);
  while (m--) {
    scanf("%lld %lld", &r, &x);
    add(1, r, x);
    if (tr[1].tmx <= d * k) {
      puts("TAK");
    } else {
      puts("NIE");
    }
  }
  return 0;
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

提供一种正常一点的非最大子段和做法。

虽然本质是一样的 hhh。

~~真就 rush 5min 调题 1h 呗。~~

------------------------------------------------

考虑运用 Hall 定理，我们只需要知道是否能选出一个点集 $U$ 使得 $|M(U)| < |U|$，其中 $M(U)$ 为点集 $U$ 的邻接点集。

移一下项，变成 $|M(U)| - |U| < 0$，问题转化成寻找一个点集使得上述条件满足。

考虑逆向思维，构造一个最有可能满足条件的点集，如果选了一种颜色 $x$ 那么所有颜色为 $x$ 的点都选了只会让值变小，所以对于每种颜色 $x$ 只存在不选或选完两种情况。


考虑 $M(U)$ 的性质。可以抽象成 $U$ 是数轴上的一些颜色为 $[l_i,r_i]$ 的区间的点集并，$M(U)$ 是另一条数轴上的一些颜色为 $[l_i,r_i + d]$ 的区间的点集并。其中两条数轴种第一条数轴对应的是人的点集，第二条数轴对应的是溜冰鞋的点集。

考虑如果两个 $M(U)$ 中的区间 $[l_i,r_i]$ 与 $[l_j,r_j]$ 有交，我们应该合并两个区间以最小化值（同时 $U$ 中的对应区间也要合并，如果两个区间没有交那么中间的部分就也要算上），那么现在 $M(U)$ 中任意两个区间不存在交，而由于任意的 $[l_i,r_i] \in [l_i,r_i + d]$，显然 $U$ 中任意两个区间也不存在交。

考虑我们只需要知道是否有 $|M(U)| - |U| < 0$，而此时由上述区间无交的性质我们知道，该式子的值等于每段区间单独计算的值相加。

而 $|M(U)| - |U| < 0$ 告诉我们，我们只需要看这些单独的区间是否有满足 $|M(U)| - |U| < 0$ 的，否则集体值相加值也肯定大于等于 $0$。

问题转化成了记 $v(l,r)$ 表示标号（颜色）在 $[l,r]$ 中的人的数量，$V(l,r)$ 表示标号（颜色）在 $[l,r]$ 中的溜冰鞋的数量，则是求一个最小的 $V(l,r + d) - v(l,r)$ 区间 $[l,r]$。

考虑滚前缀和，暴力拆一个差分出来：

$(V(1,r + d) - v(1,r)) - (V(1,l - 1) - v(1 , l - 1))$

每个位置维护前缀和后维护区间内 $(V(1,r + d) - v(1,r))$ 的最小值，$(V(1,l - 1) - v(1 , l - 1))$ 的最大值以及区间 $(V(1,r + d) - v(1,r)) - (V(1,l - 1) - v(1 , l - 1))$ 的最小值，这些都可以在线段树上面动态维护。

时间复杂度 $O(n \log n)$。

```cpp
/*
这和 T1 没有什么区别吧
考虑将 x 从小到大排序，每个人选择的鞋子个数
那显然如果要构造一种方案卡的话，选了一种 x 该种 x 要选完
问题转化成了是否能选择一些 x 使得它们的 sumval 相加 <= sumpos
问题依然等价于选择一个点，因为将不等式移项后，有负贡献不如直接就用这个点作为 hack 就行了
哦好像有点萎，因为 sumval 是不能直接叠加的
额，那考虑构造出来的最大 hack 一定是一个连续段，如果是多个连续段的并选一个就可以了
所以维护一个最小的区间 V[l,r + d] - v[l,r]
拆成 V_{r + x} - V_{l - 1} - (v_r - v_{l - 1})
合并部分项，即 (V_{r + x} - v_r) - (V_{l - 1} - v_{l - 1})
由于只有 V 会变化，对于第一个值维护一个区间内的最小值，第二个值维护区间最大值以及一个区间的答案
~~SB~~
是 v 会变化
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 5e5 + 5;
const long long Inf = 1e18;
int n,m,k,d;
#define ls(p) p << 1
#define rs(p) p << 1 | 1
long long minn[Len << 2],maxn[Len << 2],ans[Len << 2],tagminn[Len << 2],tagmaxn[Len << 2],v[Len];
void push_up(int x)
{
	minn[x] = min(minn[ls(x)] , minn[rs(x)]);
	maxn[x] = max(maxn[ls(x)] , maxn[rs(x)]);
	ans[x] = min(ans[ls(x)] , ans[rs(x)]);
	ans[x] = min(ans[x] , minn[rs(x)] - maxn[ls(x)]);
}
void push_down(int p)
{
	if(tagminn[p])
	{
		tagminn[ls(p)] += tagminn[p] , tagminn[rs(p)] += tagminn[p];
		minn[ls(p)] += tagminn[p] , minn[rs(p)] += tagminn[p];
		tagminn[p] = 0;
	}
	if(tagmaxn[p])
	{
		tagmaxn[ls(p)] += tagmaxn[p] , tagmaxn[rs(p)] += tagmaxn[p];
		maxn[ls(p)] += tagmaxn[p] , maxn[rs(p)] += tagmaxn[p];
		tagmaxn[p] = 0;
	}
}
void build(int p,int l,int r)
{
	tagminn[p] = tagmaxn[p] = 0;
	if(l == r) 
	{
		minn[p] = v[l + d];
		maxn[p] = v[l];
		ans[p] = Inf;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(p) , l , mid);
	build(rs(p) , mid + 1 , r);
	push_up(p);
}
void update(int p,int l,int r,int nl,int nr,int w)
{
	if(nl <= l && nr >= r)
	{
		tagminn[p] += w;
		minn[p] += w;
		tagmaxn[p] += w;
		maxn[p] += w;
		//printf("%d %d %lld %lld %lld\n",l,r,minn[p],maxn[p],ans[p]);
		return;
	}
	push_down(p);
	int mid = (l + r) >> 1;
	if(nl <= mid) update(ls(p) , l , mid , nl , nr , w);
	if(nr > mid) update(rs(p) , mid + 1 , r , nl , nr , w);
	push_up(p);
}
long long qans(){return (ans[1] >= 0) && (minn[1] >= 0);}
int main()
{
	scanf("%d %d %d %d",&n,&m,&k,&d);
	for(int i = 1 ; i <= n ; i ++) 
	{
		v[i] = k;
		v[i] += v[i - 1];
	}
	build(1 , 1 , n - d);
	for(int i = 1 ; i <= m ; i ++)
	{
		int r,x;scanf("%d %d",&r,&x);
		update(1 , 1 , n - d , r , n - d , -x);
		//printf("%lld %lld\n",ans[1],minn[1]);
		if(qans()) puts("TAK");
		else puts("NIE");
	}
	return 0;
}
```

---

## 作者：hewo (赞：2)

几乎所有的题解都讲到了要求出最大子段和，也就是：

$$
 \begin{aligned}
(TAK)\\
\sum_{i=l}^r{w[i]} & \le k \times (r+d-l+1) \\
\sum_{i=l}^r{w[i]} & \le \sum_{i=l}^{r}{k}+k \times d\\
\sum_{i=l}^r{(w[i]-k)} & \le k \times d
 \end{aligned}
$$

但为什么一定是最大子段和呢？（蒟蒻想了很久）

首先最大子段和一定是正确的这个很容易理解：最大的都满足了，其他的还满足不了吗？

其次，先考虑单点。如果 $ \forall i \in [1,n]:w[i] \le k$，那么皆大欢喜，不需要任何考虑了。

如果 $\exists i \in [1,n]:w[i]>k$，那我们就要将$w_i$ 往 $i+d$ 那里传。这个操作可以理解为推倒（雾），如果推倒了 $w_i$ 导致 $w_j$ 又要被推倒，那就继续推下去。这样可以看出，要考虑是否推倒的区间 $[l,r] (l \in [1,n],r \in [l,n])$，也就是考虑所有子段了。再结合上面的公式，就是最大子段和了。（似乎还是挺好想的，还是我太菜了）。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int MX=5*100000+1000;
#define LL long long
#define inf 0x3f3f3f3f

#define modn 998244353

#define lson now<<1
#define rson now<<1|1

inline LL read()
{
	LL x=0,f=1;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
	return x*f;
}

LL n,m,K,d;

struct tTree
{
	LL lans;
	LL rans;
	LL sum;
	LL ans;
}tree[MX<<2];

inline void pushup(LL now)
{
	tree[now].sum=(tree[lson].sum+tree[rson].sum);
	tree[now].lans=max(tree[lson].lans,tree[lson].sum+tree[rson].lans);
	tree[now].rans=max(tree[rson].rans,tree[rson].sum+tree[lson].rans);
	tree[now].ans=max(max(tree[lson].ans,tree[rson].ans),tree[lson].rans+tree[rson].lans);
}

inline void build(LL now,LL l,LL r)
{
	if(l==r)
	{
		tree[now].lans=tree[now].rans=-K;
		tree[now].sum=tree[now].ans=-K;
		return ;
	}
	LL mid=(l+r)>>1;
	build(lson,l,mid),build(rson,mid+1,r);
	pushup(now);
}

inline void change(LL now,LL l,LL r,LL nl,LL nr,LL k)
{
	if(nl==l&&nr==r)
	{
		tree[now].lans+=k,tree[now].rans+=k;
		tree[now].sum+=k,tree[now].ans+=k;
		return ;
	}
	LL mid=(l+r)>>1;
	if(nl<=mid) change(lson,l,mid,nl,nr,k);
	if(nr>=mid+1) change(rson,mid+1,r,nl,nr,k);
	pushup(now);
}

inline LL get_max()
{
	return tree[1].ans; 
}

int main(int argc, char const *argv[])
{
	n=read(),m=read(),K=read(),d=read();
	build(1,1,n);
	while(m--)
	{
		LL r,x;
		r=read(),x=read();
		change(1,1,n,r,r,x);
		LL now=get_max();
		//printf("NOW: %d\n",now);
		if(now<=K*d)
		{
			printf("TAK\n");
		}
		else
		{
			printf("NIE\n");
		}
	}
	return 0;
}
```



---

## 作者：chenzida (赞：2)

线段树水题

假设每次操作可以 $O(n)$ 做，我们怎么判断是否可行？

我们可以直接扫一遍序列，这个尺码的人肯定尽量用当前尺码的鞋子（因为都已经扫到这里了，这个鞋子不用也浪费了），所以也就是说，每次 $a_i$ 可以加等于 $a_{i-1}-k$ ，当然如果这个值小于 $0$ 了就不能加。但是如果可以发现，如果直接加了，只会使得原来不满足的变满足，而不会使得满足的不满足。也就是说可能把 'NIE' 判断成 'TAK'。

但是我们只要对于每一个 $l,r$ 都判断一次就不会有问题了。所以我们就转化为求是否有 $l,r$ 满足 $(\sum_{i=l}^r a_i )> k\times (r-l+1+d)$。所以我们只要求出最大的 $\sum_{i=l}^r (a_i-k)$ 即可。

所以可以直接线段树求最大子段和。

---

## 作者：Z1qqurat (赞：1)

## Hall 定理

这是一个关于二分图完美匹配存在性的定理。定理内容如下：将二分图分为左部点 $L$ 和右部点 $R$，保证 $|L| = |R|$，该图存在完美匹配当且仅当对于 $\forall S \subseteq L, |f(S)| \ge |S|$，其中 $f(S)$ 表示 $R$ 中与 $S$ 中点有连边的点的集合。这个可以归纳法证明，感性理解可以参考[这篇文章](https://www.zhihu.com/tardis/bd/art/460373184?source_id=1001)，个人认为写得很生动形象。

我们来看一些例题。

### P3488

我将这个题当作 Hall 定理应用的模板题，我会着重解释为什么可以将这个 Hall 定理的形式转化为一个最大子段和。

如果不考虑数据范围，那就是一个二分图最大匹配裸题。但是这数据范围太大，我们不能暴力建边，考虑霍尔定理。我们将脚的大小当作一种类型（左部点），$num_i$ 指脚大小为 $i$ 的人的个数，右部点是鞋的尺码，也可以将每种尺码的 $k$ 双鞋都看作在此位置上的 $k$ 个右部点。取 $S \subseteq L$，那么只有对于 $\forall S$ 都满足 $\sum\limits_{i \in S} num_i \le |f(S)|$ 才会有完美匹配。现在我们就要使得这个上界最紧。考虑这样一件事，如果我们选择的 $S$ 并不是一段连续区间，那么假如 $S \cup T = [l, r], S \cap T = \varnothing$，且 $S, T$ 分别满足上界的限制，那么设 $A = S \cup T$，则$|A| = |S| + |T|$，但是 $|f(A)| \le |f(S)| + |f(T)|$，因为 $f(S)$ 和 $f(T)$ 可能有相同元素。所以我们可以发现，如果取 $S$ 为一段连续的区间 $[l, r]$，得到的上界一定不松于不连续的 $S$。

于是现在我们讨论 $S = [l, r]$，那么就是 $f(S) = k \times (r + d - l + 1)$，上界就是，
$$
\begin{aligned} \sum\limits_{i = l}^{r} num_i &\le k \times (r + d - l + 1)
\\ &= k \times d + k \times (r - l + 1) \end{aligned}
$$
即：
$$
\sum\limits_{i = l}^{r} (num_i - k) \le k \times d
$$
很好，你会发现 $k \times d$ 是一个定值，所以我们只需要求出最大的 $\sum\limits_{i = l}^{r} (num_i - k)$ 且满足 $1 \le l \le r \le n$，如果这个最大的和 $\le n$，那么所有的 $S$ 都会满足上界条件了，所以就一定存在完美匹配，反之不存在。这是一个简单的线段树维护最大子段和问题，具体可以参考 P4513。

给出丑陋的代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define lc p << 1
#define rc p << 1 | 1
using namespace std;
const int N = 2e5 + 5;
int n, m, k, d;

namespace SegT{
    struct Rinne{
        ll lx, rx, ans, sum;
        friend Rinne operator+(const Rinne a, const Rinne b) {
            Rinne c;
            c.sum = a.sum + b.sum;
            c.lx = max(a.lx, a.sum + b.lx);
            c.rx = max(b.rx, b.sum + a.rx);
            c.ans = max(a.rx + b.lx, max(a.ans, b.ans));
            return c;
        }
    } tr[N << 2];
    void pushup(int p) {
        tr[p] = tr[lc] + tr[rc]; return ;
    }
    void build(int p, int l, int r) {
        if(l == r) {
            tr[p].sum = -k, tr[p].ans = tr[p].lx = tr[p].rx = 0;
            return ;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid), build(rc, mid + 1, r);
        pushup(p); return ;
    }
    void modify(int p, int l, int r, int x, int v) {
        if(l == r && l == x) {
            tr[p].sum += v;
            tr[p].ans = tr[p].lx = tr[p].rx = max(tr[p].sum, 0ll);
            return ;
        }
        int mid = (l + r) >> 1;
        if(x <= mid) modify(lc, l, mid, x, v);
        else modify(rc, mid + 1, r, x, v);
        pushup(p); return ;
    }
    void modify(int x, int v) {
        modify(1, 1, n, x, v);
    }
} using namespace SegT;

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &d);
    ll lim = 1ll * k * d;
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int x, v; scanf("%d %d", &x, &v);
        modify(x, v);
        if(tr[1].ans <= lim) puts("TAK");
        else puts("NIE");
    }
    return 0;
}
```



---

## 作者：翼德天尊 (赞：1)

> 滑冰俱乐部初始有 $1$ 到 $n$ 号码溜冰鞋各 $k$ 双，已知 $x$ 号脚的人可以穿 $x$ 到 $x + d$ 号码的鞋子。
>
> 现在有 $m$ 次操作，每次两个数 $r$、$x$，表示 $r$ 号脚的人来了 $x$ 个，$x$ 为负表示离开。对于每次操作，输出溜冰鞋是否足够。
>
> $r\le n-d$，$1\le n,k,m\le 5\times 10^5$，$k\le 10^9$.

很容易想到将人和溜冰鞋一起建二分图，傻瓜式连边，并对于每次操作都跑一遍最大流，但这时间复杂度显然爆炸！

由于题目只询问是否存在完美匹配，所以考虑使用 Hall 定理。

设 $s_x$ 为当前脚码为 $x$ 的人数。由 Hall 定理可知，若该二分图存在完美匹配，则有：
$$
\forall l,r\in[1,n-d],l\le r,\sum_{i=l}^rs_{i}\le k\times (r-l+1+d)
$$
不妨将右侧常变量分离，则有：
$$
\sum_{i=l}^r(s_i-k)\le k\times d
$$
于是我们动态维护所有区间 $\sum s_i-k$ 的最大值，每次询问时判断是否大于 $k\times d$ 即可。

用线段树可以做到 $O(m\log n)$.

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e5+5;
ll n,m,k,d;
struct node1{
    ll maxn,sum,qz,hz;
    node1 (ll maxn=0,ll sum=0,ll qz=0,ll hz=0)
        :maxn(maxn),sum(sum),qz(qz),hz(hz){}
}S;
struct node{
    ll sum[N<<2],qz[N<<2],hz[N<<2],maxn[N<<2];
    void pushup(int i){
        sum[i]=sum[i<<1]+sum[i<<1|1];
        qz[i]=max(qz[i<<1],qz[i<<1|1]+sum[i<<1]);
        hz[i]=max(hz[i<<1|1],hz[i<<1]+sum[i<<1|1]);
        maxn[i]=max(maxn[i<<1],max(maxn[i<<1|1],hz[i<<1]+qz[i<<1|1]));
    }
    void build(int i,int l,int r){
        if (l==r){
            sum[i]=qz[i]=hz[i]=maxn[i]=-k;
            return;
        }
        int mid=l+r>>1;
        build(i<<1,l,mid);
        build(i<<1|1,mid+1,r);
        pushup(i);
    }
    void add(int i,int l,int r,int pos,ll s){
        if (l==r){
            sum[i]+=s;
            qz[i]+=s;
            hz[i]+=s;
            maxn[i]+=s;
            return;
        }
        int mid=l+r>>1;
        if (pos<=mid) add(i<<1,l,mid,pos,s);
        else add(i<<1|1,mid+1,r,pos,s);
        pushup(i);
    }
    // node1 query(int i,int l,int r,int ql,int qr){
    //     if (ql<=l&&r<=qr) return node1(maxn[i],sum[i],qz[i],hz[i]);
    //     int mid=l+r>>1;
    //     if (qr<=mid) return query(i<<1,l,mid,ql,qr);
    //     if (mid<ql) return query(i<<1|1,mid+1,r,ql,qr);
    //     node1 x=query(i<<1,l,mid,ql,qr),y=query(i<<1|1,mid,r,ql,qr),z;
    //     z.qz=max(x.qz,x.sum+y.qz);
    //     z.hz=max(y.hz,y.sum+x.hz);
    //     z.sum=x.sum+y.sum;
    //     z.maxn=max(max(x.maxn,y.maxn),x.hz+y.qz);
    //     return z;
    // }
}T;
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif  
    n=read(),m=read(),k=read(),d=read();
    T.build(1,1,n);
    for (int i=1;i<=m;i++){
        int x=read(),g=read();
        T.add(1,1,n,x,g);
        ll num=T.maxn[1];
        //cout<<num<<"\n";
        if (num>k*d) puts("NIE");
        else puts("TAK");
    }
	return 0;
}


```

---

## 作者：Steven_lzx (赞：0)

[更好的阅读体验。](https://www.cnblogs.com/2020gyk080/p/16776921.html)

## 错解

每次跑二分图匹配，时间复杂度显然爆炸。

~~时间复杂度：我被杀手皇后摸过了~~

## 正解

### 引入

> Hall 定理：设二分图中 $G=<V_1,V_2,E>,|V_1| \le |V_2|$，则 G 中 存在 $V_1$ 到 $V_2$ 的完美匹配当且仅当 $\forall S \sub V_1$，均有 $|S| \le |N(S)|$，其中 $N(S)=\Cup_{V_i \in S}{N(V_i)}$，是 $S$ 的邻域。

通俗来说，对于一个二分图，它的左面有 $n$ 个点，右面有 $m$ 个点，则左边 $n$ 个点能完全匹配的充要条件是对于任意在 $[1,n]$ 之间的 $i$，左面任意 $i$ 个点，都至少有 $i$ 个右面的点与它相连。

#### 证明

**充分性**：假设一个二分图 $G$ 不存在完美匹配，且满足 Hall 定理，那么如果有一种最大匹配的方案，既然不存在完美匹配，可以找到至少一个未被匹配的点 $A$。

因为这个二分图满足 Hall 定理，所以这个点一定连向了至少一个点 $B$（有可能存在多个点）。那么这个点 $B$ 一定在最大匹配中，左边一定有一个点 $C$ 和它匹配。

$C$ 做为一个匹配点可能在右边找到 $D$，就这样一直找下去，由于左部点数是小于等于右部点数，于是最终点落在右部点结束，找到一个增广路，矛盾，假设不成立。

**必要性**：假设一个二分图 $\text{G}$ 存在完美匹配，且不满足 Hall 定理。
那么对于某 $k$ 个点，它们连向的都不足 $k$ 个点，这些点无法匹配，矛盾，假设不成立。

### 转化

我们显然不能枚举所有情况，这样的时间复杂度是 $O(2^p)$ 的，其中 $p$ 为人数，所以我们只能考虑最劣的情况。

显然，选择连续号码的人会使右边与他相邻的人最少。

设 $[l,r]$ 为脚号码的范围，$a_i$ 表示型号为 $i$ 的人数，由 Hall 定理得：

$$
\sum^r_{i=l}a_i \le k(r-l+1+d) \qquad (1)
$$

如果单纯这样做的话，修改是 $O(n^2 \log n)$ 的，询问是 $O(m^2)$ 的，时间复杂度依然接受不了。

考虑将 $(1)$ 式变形，得：

$$
\sum^r_{i=l}(a_i-k)\le d \cdot k \qquad (2)
$$

$(2)$ 式中由于 $d \cdot k$ 是个定值，那么问题变为单点修改+求最大连续子序列和，可以用线段树维护（最开始时令 $a_i=-k$）。

### 代码

```cpp
//P3488 [POI2009]LYZ-Ice Skates
#include <iostream>
#include <cstdio>
using namespace std;
#define int long long
const int MAXN=2e5+5;
struct SegmentTree
{
    int lmx,rmx,sum,res;
}tr[MAXN<<2];
int n,m,k,d;
void pushup(int p)
{
    tr[p].lmx=max(tr[p<<1].lmx,tr[p<<1].sum+tr[p<<1|1].lmx);
    tr[p].rmx=max(tr[p<<1|1].rmx,tr[p<<1|1].sum+tr[p<<1].rmx);
    tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
    tr[p].res=max(tr[p<<1].res,max(tr[p<<1|1].res,tr[p<<1].rmx+tr[p<<1|1].lmx));
    return;
}
void build(int p,int l,int r)
{
    int mid;
    if(l==r)
    {
        tr[p]={0,0,-k,-k};
        return;
    }
    mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    pushup(p);
    return;
}
void update(int p,int l,int r,int k,int c)
{
    int mid;
    if(l==r)
    {
        tr[p].sum+=c;
        tr[p].res+=c;
        tr[p].lmx=tr[p].rmx=max(0ll,tr[p].sum);
        return;
    }
    mid=(l+r)>>1;
    if(k<=mid)
    {
        update(p<<1,l,mid,k,c);
    }
    else 
    {
        update(p<<1|1,mid+1,r,k,c);
    }
    pushup(p);
    return;
}
signed main()
{
    int x,y;
    scanf("%lld%lld%lld%lld",&n,&m,&k,&d);
    build(1,1,n);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld",&x,&y);
        update(1,1,n,x,y);
        if(tr[1].res<=k*d)
        {
            printf("TAK\n");
        }
        else 
        {
            printf("NIE\n");
        }
    }
    return 0;
}
/*
 * 洛谷
 * https://www.luogu.com.cn/problem/P3488
 * C++17 -O0
 * 2022.10.10
 */
```

---

## 作者：人间温柔 (赞：0)

每一个尺寸的脚，都对应 $d$ 个不同的可以取到的鞋子，~~很容易~~ 想到 **二分图匹配问题**。

前置知识
---
前置知识是二分图之匈牙利算法的必备知识：Hall 定理（霍尔定理），内容如下：

现有两组点，其中左边集合 $A$ 中的任意一点 $u$ 只能和右边集合 $B$ 中某些特定的点连边，$B$ 中的这些特定的点就是 $u$ 的邻居。下图中蓝色的边就代表了这一特定的关系。

假设 $w \subseteq A$，$w$ 中所有点的邻居构成的集合是 $n(w)$。如果对于任意的 $w$，都满足 $|w|\leq|n(w)|$，那么这个二分图可以成功匹配。

这个就是 Hall 定理。

![A.png](https://yacs-public.oss-cn-hangzhou.aliyuncs.com/image/1662471020003.png)

回归本题
---
如果把脚看成上图中的 $A$ 集合，鞋子看成 $B$ 集合，那么本题中鞋子够用就对应这二分图可以匹配，不够用就是二分图不能匹配。

假设脚的尺寸 $sz \in [l,r]$。$l$ 的脚可以穿尺寸介于 $[l,l+d]$ 的鞋子，$l+1$ 的脚可以穿尺寸介于 $[l+1,l+d+1]$ 的鞋子，……，$r$ 的脚可以穿尺寸介于 $[r,r+d]$ 的鞋子，那么 $sz\in [l,r]$ 的脚可以穿的鞋子的范围是 $[l,r+d]$。

再维护一个信息：$cnt(i)$ 代表尺寸为 $i$ 的脚出现了几次。那么根据 Hall 定理，鞋子够用的条件就是：
$$
\sum_{i=l}^{r}cnt(i)\leq k(r+d-l+1)
$$
$k$ 是题目中的含义，即每种尺寸的鞋子都有 $k$ 双。

把上面的式子转化一下：
$$
\sum_{i=l}^{r}cnt(i)\leq k(r-l+1+d)
$$
$$
\sum_{i=l}^{r}cnt(i)\leq k(r-l+1)+dk
$$
其中 $k(r-l+1)$ 可以看成 $\sum_{i=l}^{r}k$，所以把它移到不等式的左边，就变成了：
$$
\sum_{i=l}^{r}(cnt(i)-k)\leq dk
$$
其中 $dk$ 是个定值。当 $\sum_{i=l}^{r}(cnt(i)-k)$ 的最大值都能够小于等于 $dk$，那么就是 $\forall l,r$, $\sum_{i=l}^{r}(cnt(i)-k)$ 都小于等于 $dk$，鞋子也就是够用的。

反之，如果 $\sum_{i=l}^{r}(cnt(i)-k)$ 的最大值无法做到小于等于 $dk$，那么鞋子不够用。

那么问题转化成求序列 $\{cnt(i)-k\}$ 的最大字段和了，也就是动态最大字段和。

这个与 [SP1716 GSS3 - Can you answer these queries III](https://www.luogu.com.cn/problem/SP1716) 有这相同的求法。建议先把 SP1716 做掉，那么动态最大字段和就没成问题了。
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=500005;

int n,m;
long long k,d;

struct seg_tree{
	long long maxn,maxl,maxr,sum;
}t[maxn<<2];

void pushup(int pos){
	t[pos].maxl=max(t[pos<<1].maxl,t[pos<<1].sum+t[pos<<1|1].maxl);
	t[pos].maxr=max(t[pos<<1|1].maxr,t[pos<<1].maxr+t[pos<<1|1].sum);
	t[pos].maxn=max(t[pos<<1].maxr+t[pos<<1|1].maxl,max(t[pos<<1].maxn,t[pos<<1|1].maxn));
	t[pos].sum=t[pos<<1].sum+t[pos<<1|1].sum;
}

void build(int pos,int l,int r){
	if(l==r){
		t[pos].maxn=-k;
		t[pos].maxl=-k;
		t[pos].maxr=-k;
		t[pos].sum=-k;
		return;
	}
	int mid=(l+r)>>1;
	build(pos<<1,l,mid);
	build(pos<<1|1,mid+1,r);
	pushup(pos);
}

void modify(int pos,int l,int r,int x,int delta){
	if(l==r){
		t[pos].maxl+=delta;
		t[pos].maxr+=delta;
		t[pos].maxn+=delta;
		t[pos].sum+=delta;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid){
		modify(pos<<1,l,mid,x,delta);
	}
	else{
		modify(pos<<1|1,mid+1,r,x,delta);
	}
	pushup(pos);
}

int main(){
	cin>>n>>m>>k>>d;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int sz,x;
		cin>>sz>>x;
		modify(1,1,n,sz,x);
		if(t[1].maxn<=d*k) cout<<"TAK"<<endl;
		else cout<<"NIE"<<endl;
	}
	return 0;
}
```


---

## 作者：watermonster (赞：0)

#### 简要题意：

- 共有 $n$ 种号码的鞋子，每种号码的鞋子都有 $k$ 双，$x$ 号脚的人可以穿 $x,x+1,\dots\,x + d$ 号码的鞋子
- $m$ 操作，每次会有人到来或离开，每次操作后，判断每个人是否都能匹配到鞋子
- $n \le 2 \times 10^5,m \le 5 \times 10^5,1\le k \le 10^9$



#### 做法：

记$s_i$为 $i$ 号脚的人的个数，那么显然对于任意一段区间 $[l,r]$，都要满足 $\sum_{i=l}^r s_i \le k \times (r+d-l+1)$

将右边拆开可得 $\sum_{i=l}^r s_i \le k \times (r-l+1) + k \times d$

移项得 $\sum_{i=l}^r s_i - k \le k \times d$

要使不等式成立，只需 $\sum_{i=l}^r s_i-k$ 的最大值小于等于 $k \times d$ 即可。

于是我们需要维护序列 $\{s_i-k\}$ 的最大子段和。

如果没有修改操作，这就是一个很简单的[DP题](https://www.luogu.com.cn/problem/P1115)。

令 $f_i$ 为以$i$结尾的最大字段和， $g_i$ 为前 $i$ 个数的最大字段和。

那么 $f_i=f_{i-1}+s_i,g_i=max(g_{i-1},f_i)$，同时 $g_n$ 就是这个序列的最大字段和。

然而现在我们需要修改序列中的值，于是我们要从修改的位置向后重新递推。然而时间复杂度 $O(nm)$显然无法解决问题，所以考虑使用动态DP。

考虑如何优化修改后的递推过程。显然 $f_i$ 的转移方程是一个线性递推式可以使用矩阵加速，但 $g_i$ 的转移方程中有一个取max的操作不能用矩阵来转移，于是我们需要重新定义矩阵乘法。

众所周知，传统的矩阵乘法是 $C_{i,j}=\sum A_{i,k} \times B_{k,j}$，由于矩阵乘法满足结合律所以我们可以通过快速幂来加速运算。

尝试将新的矩阵乘法定义为 $C_{i,j}=max \{ A_{i,k} + B_{k,j} \}$，可以发现，新的乘法运算同样满足结合律。

解决的转移的问题后我们就可以构造出矩阵：

 $\begin{bmatrix}s_i&-inf&s_i\\s_i&0&s_i\\-inf&-inf&0\end{bmatrix} \times \begin{bmatrix}f_{i-1}\\g_{i-1}\\0\end{bmatrix} = \begin{bmatrix}f_i\\g_i\\0\end{bmatrix}$

然而仅有矩阵还不够，我们要快速求出一个区间的乘积才能得到答案，但每个位置的转移矩阵都不相同所以我们不能用快速幂来求。

要支持单点修改和查询区间乘积，显然想到用线段树来维护。我们可以在线段树的每个节点放一个矩阵来维护这个区间的乘积，每次修改只需改对应叶子节点的矩阵，然后向上更新父亲即可。

#### 代码：

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

#define il inline
#define re register
#define file(s) freopen(#s".in","r",stdin),freopen(#s".out","w",stdout)

typedef long long ll;

const int N=5e5+10;
const ll inf=0x3f3f3f3f3f3f3f3f;

namespace FastIO
{
char buf[1<<21],buf2[1<<21],*p1=buf,*p2=buf;
int p4,p3=-1;
il int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
il void Flush(){fwrite(buf2,1,p3+1,stdout),p3=-1;}
#define isdigit(ch) (ch>=48&&ch<=57)
template <typename T>
il void read(T &x)
{
	re int f=0;x=0;re char ch=getc();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getc();
	while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getc();
	x=f?-x:x;
}
template <typename T>
il void print(T x)
{
	if(p3>(1<<20)) Flush();
	if(x<0) buf2[++p3]=45,x=-x;
	re int a[50]={};
	do{a[++p4]=x%10+48;}while(x/=10);
	do{buf2[++p3]=a[p4];}while(--p4);
}
}
using namespace FastIO;

/*矩阵部分*/
struct mat{ll a[3][3];};
il void init(mat &x)
{
	for(re int i=0;i<3;++i)
		for(re int j=0;j<3;++j)
			x.a[i][j]=-inf;
	return;
}
il mat mul(const mat &x,const mat &y)
{
	re mat z;init(z);
	for(re int i=0;i<3;++i)
		for(re int j=0;j<3;++j)
			for(re int k=0;k<3;++k)
				z.a[i][j]=max(z.a[i][j],x.a[i][k]+y.a[k][j]);
	return z;
}
//新的矩阵乘法

int n,m;
ll k,d,s[N];

/*线段树部分*/
int L[N<<2],R[N<<2];
mat val[N<<2];
#define ls(i) (i<<1)
#define rs(i) (i<<1|1)
#define pushup(i) (val[i]=mul(val[ls(i)],val[rs(i)]))
il void build(int i,int l,int r)
{
	L[i]=l;R[i]=r;
	if(l==r)
	{
		val[i].a[0][0]=s[L[i]]; val[i].a[0][1]=-inf; val[i].a[0][2]=s[L[i]];
		val[i].a[1][0]=s[L[i]]; val[i].a[1][1]=0;    val[i].a[1][2]=s[L[i]];
		val[i].a[2][0]=-inf;    val[i].a[2][1]=-inf; val[i].a[2][2]=0;
		return;
	}
	re int mid=(l+r)>>1;
	build(ls(i),l,mid);build(rs(i),mid+1,r);
	pushup(i);return;
}//建树
il void modify(int i,int p)
{
	if(L[i]==R[i])
	{
		val[i].a[0][0]=s[L[i]]; val[i].a[0][1]=-inf; val[i].a[0][2]=s[L[i]];
		val[i].a[1][0]=s[L[i]]; val[i].a[1][1]=0;    val[i].a[1][2]=s[L[i]];
		val[i].a[2][0]=-inf;    val[i].a[2][1]=-inf; val[i].a[2][2]=0;
		return;//重置叶子节点的矩阵
	}
	re int mid=(L[i]+R[i])>>1;
	modify(p>mid?rs(i):ls(i),p);
	pushup(i);return;
}//单点修改

int main()
{
	read(n);read(m);read(k);read(d);
	for(re int i=1;i<=n;++i) s[i]=-k;
	build(1,1,n);
	for(re int i=1,r,x;i<=m;++i)
	{
		read(r),read(x);s[r]+=x;modify(1,r);
		puts(val[1].a[1][2]<=k*d?"TAK":"NIE");
        //根节点的矩阵即为整个序列的答案
	}
	Flush();return 0;
}
```



---

