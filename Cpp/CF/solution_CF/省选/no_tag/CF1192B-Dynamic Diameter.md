# Dynamic Diameter

## 题目描述

有一个 $n$ 个点的带权无向树，$q$ 次操作，每次修改一条边的权值，要求在每次修改后，输出树的直径大小，强制在线。

## 样例 #1

### 输入

```
4 3 2000
1 2 100
2 3 1000
2 4 1000
2 1030
1 1020
1 890
```

### 输出

```
2030
2080
2050
```

## 样例 #2

### 输入

```
10 10 10000
1 9 1241
5 6 1630
10 5 1630
2 6 853
10 1 511
5 3 760
8 3 1076
4 10 1483
7 10 40
8 2051
5 6294
5 4168
7 1861
0 5244
6 5156
3 3001
8 5267
5 3102
8 3623
```

### 输出

```
6164
7812
8385
6737
6738
7205
6641
7062
6581
5155
```

# 题解

## 作者：x义x (赞：34)

这题有一个很妙的解法，不需要树剖、LCT，是用线段树维护**全dfs序**。

首先考虑$u,v$两节点的距离。

$$dis(u,v)=dep[u]+dep[v]-2dep[lca(u,v)]$$

这很难直接维护，主要的问题是我们没法直接知道$lca(u,v)$。下面我们引入全dfs序。

dfs序是：我们dfs遍历一棵树，每次访问到一个节点就把它记到序列末端，这样形成的序列就是dfs序。

而全dfs序则是：仍然dfs遍历一棵树，每次访问到一个节点就把它记到序列末端（下面称这时序列的长度为该节点的$Tin$，序列记为$dfn$），同时，每当一个节点的子树的访问正式结束，我们也把它的父亲记到序列末端。

这有什么帮助呢？我们考虑节点$u,v$（不妨设$Tin[u]<Tin[v]$）和他们的$lca$。

- 显然地，$u,v$必然分属$lca$的两个子树，于是在访问$v$之前，$u$所在子树的访问一定已经结束，所以$lca$必然出现在了$Tin[u]$到$Tin[v]$之间。

- 显然，访问$v$时，对$lca$子树的访问不可能结束，于是$Tin[u]$到$Tin[v]$之间不可能会有比$lca$更浅的节点。

上面的两个结论翻译一下就是：$lca$的深度是$Tin[u]$到$Tin[v]$这一段区间里所有节点的深度的下界，而且它一定存在。所以它就是这段区间里的深度最小值。

所以我们就可以用线段树在全dfs序上维护一个$dep$的最小值。

那么具体如何得出答案？我们需要维护：

- 区间深度最大值，称作``W``（作为$dep[l]$和$dep[r]$）

- 区间深度最小值，称作``M``（作为$dep[lca]$）

- $dep[l]-2dep[lca]$，称作``LM``。通过左右区间的``LM``，左区间的``L``和右区间的``M``得到。

- ``MR``，``LMR``类似（从名字就可以知道这两个是什么东西了）。

``LMR``就是我们要的答案。

代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int N,Q;ll KK;
int lnk[100005];
int pre[200005],tgt[200005],cnt;ll val[200005];
int pos[100005];ll Val[100005];
void add_E(int u,int v,ll c){
	pre[++cnt]=lnk[u],tgt[cnt]=v,val[cnt]=c,lnk[u]=cnt;
} 

ll dep[100005];
int Tin[100005],Tout[100005];
int dfn[200005],idx;
void dfs(int x,int f){
	dfn[++idx]=x;Tin[x]=idx;
	for(int e=lnk[x];e;e=pre[e])if(tgt[e]!=f)
		pos[(e+1)>>1]=tgt[e],dep[tgt[e]]=dep[x]+val[e],dfs(tgt[e],x),dfn[++idx]=x;
	Tout[x]=idx;
}

ll W[800005],M[800005],LM[800005],MR[800005],LMR[800005],Lzy[800005];
void push_up(int x){
	W[x]=max(W[x<<1],W[x<<1|1]);
	M[x]=max(M[x<<1],M[x<<1|1]);
	LM[x]=max(max(LM[x<<1],LM[x<<1|1]),W[x<<1]+M[x<<1|1]);
	MR[x]=max(max(MR[x<<1],MR[x<<1|1]),M[x<<1]+W[x<<1|1]);
	LMR[x]=max(max(LMR[x<<1],LMR[x<<1|1]),max(LM[x<<1]+W[x<<1|1],W[x<<1]+MR[x<<1|1]));
}
void Add(int x,int l,int r,ll K){
	W[x]+=K;
	M[x]-=2*K;
	LM[x]-=K;MR[x]-=K;
	Lzy[x]+=K;
}
void push_down(int x,int l,int r){
	int mid=(l+r)>>1;
	Add(x<<1,l,mid,Lzy[x]);Add(x<<1|1,mid+1,r,Lzy[x]);
	Lzy[x]=0;
}
void Build(int x,int l,int r){
	if(l==r){
		W[x]=dep[dfn[l]];M[x]=-2*dep[dfn[l]];
		LM[x]=MR[x]=-dep[dfn[l]];LMR[x]=0;
		return;
	}
	int mid=(l+r)>>1;
	Build(x<<1,l,mid);Build(x<<1|1,mid+1,r);
	push_up(x);
}
void Update(int x,int l,int r,int L,int R,ll K){
	if(L<=l&&r<=R){Add(x,l,r,K);return;}
	int mid=(l+r)>>1;
	push_down(x,l,r);
	if(L<=mid) Update(x<<1,l,mid,L,R,K);
	if(R>mid) Update(x<<1|1,mid+1,r,L,R,K);
	push_up(x);
}

ll lstans;

int main(){
	scanf("%d%d%lld",&N,&Q,&KK);
	for(int i=1;i<N;i++){
		int u,v;scanf("%d%d%lld",&u,&v,&Val[i]);
		add_E(u,v,Val[i]);add_E(v,u,Val[i]);
	}
	dfs(1,0);
	Build(1,1,idx);
	while(Q--){
		int d;ll K;scanf("%d%lld",&d,&K);
		d=(d+lstans%(N-1))%(N-1)+1;K=(K+lstans%KK)%KK;
		Update(1,1,idx,Tin[pos[d]],Tout[pos[d]],K-Val[d]);
		Val[d]=K;
		printf("%lld\n",lstans=LMR[1]);
	}
}
```



---

## 作者：duyi (赞：14)

# CF1192B Dynamic Diameter

## 题目大意

[题目链接](https://codeforces.com/problemset/problem/1192/B)

有一个 $n$ 个点的带权无向树，$q$ 次操作，每次修改一条边的权值，要求在每次修改后，输出树的直径大小，强制在线。

数据范围：$1\leq n, q\leq 10^5$。

## 本题题解

介绍一种简单易懂的 $\mathcal{O}(q \log^2 n)$ 做法。

首先，有一个众所周知的结论是：对于树上任意两个点集 $S, T$，设 $S$ 的直径为 $(u_S, v_S)$，$T$ 的直径为 $(u_T, v_T)$，则点集 $S\cup T$ 的直径，两个端点都在 $\{u_S, v_S, u_T, v_T\}$ 中产生。也就是说，我们在合并两个点集，并维护直径时，只需要讨论 $\mathcal{O}(1)$ 种可能的直径。

在 dfs 序上建一棵线段树。线段树的每个区间 $[l,r]$，维护 dfs 序在 $[l,r]$ 内的这些点组成的点集的直径。

考虑修改一条边的权值，会对线段树上哪些点集产生影响。设修改的边的儿子节点为 $x$，记以 $x$ 为根的子树的 dfs 序区间为 $[\text{st}_x, \text{ed}_x]$。则线段树上一段区间 $[l,r]$ 的答案可能发生改变，**仅当 $[l,r]$ 与 $[\text{st}_x, \text{ed}_x]$ 有交且不被 $[\text{st}_x, \text{ed}_x]$ 完全包含**。因为无交时，说明整个点集都在子树外，肯定不会被影响到；被完全包含，说明整个点集都在子树内，也不会被影响到。

考虑“有交且不被包含”，其实就相当于，在线段树上定位 $[\text{st}_x, \text{ed}_x]$ 时，所**经过的所有非终点节点**。这样的节点只有 $\mathcal{O}(\log n)$ 个，只需要对它们的直径进行更新即可。

更新时，还是从儿子那里继承，然后分类讨论。相当于我们只需要实现一个线段树的 ``push_up`` 函数，就能解决所有问题。

``push_up`` 时，涉及到求树上某条路径的长度。另外要支持修改边权。我们可以用数据结构（树状数组或另一棵线段树）维护每个点到根的距离。这样修改就变成区间加。查询就是先求 $\text{LCA}$，然后做三次单点查询。于是查询是 $\mathcal{O}(\log n)$ 的。

总时间复杂度 $\mathcal{O}(n + q \log^2 n)$。



---

## 作者：不知名用户 (赞：11)

动态树的直径。不妨设 1 为根节点。

考虑欧拉序，即 dfs 到 $x$ 时先在欧拉序中插入 $x$，并且在每个子树搜索完毕后也插入 $x$。

考虑欧拉序与 LCA。

> 两个点的 LCA 必然是两个点在欧拉序中的两点位置（每个点位置无论是众多位置哪一个都可以）中间深度最小的点

这个结论很显然（LCA 在欧拉序那段区间中且没有 LCA 的祖先在），不再赘述。

那么在得到欧拉序 $a$ 和每个点 $x$ 到 1 的距离 $d_x$ 后即求 $\max\limits_{1\le l \le a\le r\le len}(d_l+d_r-2d_a)$。

**注意，在负权边时不能使用，因为 $[pos_l,pos_r]$ 中深度最小的点（LCA）不一定是到根距离最短的点。**

那么改变一条边的边权（不妨设为加上 $\Delta$）该怎么在 $d$ 上操作？设该边子节点为 $x$ 那么欧拉序中 $[l_x,r_x]$ 节点深度都要加上 $\Delta$。其中 $l_x,r_x$ 为 $x$ 在欧拉序中第一次和最后一次出现的位置。

脱离了树的结构，考虑使用线段树维护欧拉序中每个点的 $d$，同时可以 $\Theta(1)$ 查询 $\max\limits_{1\le l \le a\le r\le len}(d_l+d_r-2d_a)$。

在线段树一个节点 $x=[L,R]$ 中维护以下几个值：

- ans，即序列的对应答案，$\max\limits_{L\le l \le a\le r\le R}(d_l+d_r-2d_a)$
- mx，即序列到根最大距离，$\max\limits_{L\le a\le R}d_a$
- mn，即序列到根最小距离，$\min\limits_{L\le a\le R}d_a$
- rm，$\max\limits_{L\le a\le r\le R}(d_a-2d_r)$
- lm，$\max\limits_{L\le l\le a\le R}(d_a-2d_l)$

考虑合并两个区间 $A,B$（$A$ 紧贴在 $B$ 左边）

合并 ans：

- $l,a,r$ 均在 $A$ 或 $B$，$\max\{ans[A],ans[B]\}$
- $l,a$ 在 $A$，$r$ 在 $B$，$rm[A]+mx[B]$
- $l$ 在 $A$，$a,r$ 在 $B$，$mx[A]+lm[B]$

综上，$ans[A+B]=\max\{ans[A],ans[B],rm[A]+mx[B],mx[A]+rm[B]\}$。

易知 $mn[A+B]=\min\{mn[A],mn[B]\};mx[A+B]=\max\{mx[A],mx[B]\}$。

合并 lm：

- $l,a$ 均在 $A$ 或 $B$，$\max\{lm[A],lm[B]\}$
- $l$ 在 $A$，$a$ 在 $B$，$mx[B]-2\cdot mn[A]$

综上，$lm[A+B]=\max\{lm[A],lm[B],mx[B]-2\cdot mn[A]\}$。

同理，$rm[A+B]=\max\{rm[A],rm[B],mx[A]-2\cdot mn[B]\}$。

合并结束了，考虑区间所有 $d$ 加上 $\Delta$。
$$
ans\to ans\\
mx\to mx+\Delta\\
mn\to mn+\Delta\\
lm\to lm-\Delta\\
rm\to rm-\Delta
$$
大功告成！

**欧拉序的长度是 $2n-1$（每个点都会在搜索到及回溯时（除了根节点）使序列长度加一），数组别开小！**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;

int n, q, W;

int a[N], b[N], c[N], d[N], eul[N*2], f[N], l[N], r[N], cur;

int h[N], e[N*2], w[N*2], ne[N*2], idx;

inline void add(int a, int b, int c)
{
	e[++idx] = b;w[idx] = c;ne[idx] = h[a];h[a] = idx;
}

void dfs(int x, int fa)
{
	eul[++cur] = x;
	l[x] = r[x] = cur;
	int i, j;
	for(i=h[x];i;i=ne[i])
	{
		j = e[i];
		if(j==fa) continue;
		f[j] = x;
		d[j] = d[x] + w[i];
		dfs(j,x);
		eul[++cur] = x;
		r[x] = cur;
	}
}

struct node
{
	int l, r, lazy;
	int ans, mx, mn, lm, rm;
}
st[N*8];

inline void upd(int p)
{
	st[p].ans = max({st[p*2].ans,st[p*2+1].ans,
	st[p*2].rm+st[p*2+1].mx,st[p*2].mx+st[p*2+1].lm});
	st[p].mx = max(st[p*2].mx,st[p*2+1].mx);
	st[p].mn = min(st[p*2].mn,st[p*2+1].mn);
	st[p].lm = max({st[p*2].lm,st[p*2+1].lm,st[p*2+1].mx-st[p*2].mn*2});
	st[p].rm = max({st[p*2].rm,st[p*2+1].rm,st[p*2].mx-st[p*2+1].mn*2});
}

inline void spd(int p)
{
	int lazy = st[p].lazy;
	st[p*2].mx += lazy;st[p*2+1].mx += lazy;
	st[p*2].mn += lazy;st[p*2+1].mn += lazy;
	st[p*2].lm -= lazy;st[p*2+1].lm -= lazy;
	st[p*2].rm -= lazy;st[p*2+1].rm -= lazy;
	st[p*2].lazy += lazy;st[p*2+1].lazy += lazy;
	st[p].lazy = 0; 
}

void build(int p, int l, int r)
{
	st[p].l = l, st[p].r = r;
	if(l==r)
	{
		st[p].mx = st[p].mn = d[eul[l]];
		st[p].lm = st[p].rm = -d[eul[l]];
		return;
	}
	int mid = l + r >> 1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	upd(p);
}

void add(int p, int l, int r, int x)
{
	if(l<=st[p].l&&st[p].r<=r)
	{
		st[p].lm -= x;st[p].rm -= x;
		st[p].mx += x;st[p].mn += x;
		st[p].lazy += x;
		return;
	}
	spd(p);
	int mid = st[p].l + st[p].r >> 1;
	if(l<=mid) add(p*2,l,r,x);
	if(mid<r) add(p*2+1,l,r,x);
	upd(p);
} 

signed main()
{
	int i, dd, ee, las=0, delta;
	scanf("%lld%lld%lld", &n, &q, &W);
	for(i=1;i<n;i++)
	{
		scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
		add(a[i],b[i],c[i]);
		add(b[i],a[i],c[i]);
	}
	dfs(1,0);
	build(1,1,cur);
	while(q--)
	{
		scanf("%lld%lld", &dd, &ee);
		dd = (dd + las) % (n - 1) + 1;
		ee = (ee + las) % W;
		delta = ee - c[dd];
		if(f[b[dd]]==a[dd]) add(1,l[b[dd]],r[b[dd]],delta);
		if(f[a[dd]]==b[dd]) add(1,l[a[dd]],r[a[dd]],delta);
		c[dd] = ee;
		las = st[1].ans;
		printf("%lld\n", las);
	}
	return 0;
}
```



---

## 作者：whiteqwq (赞：10)

[CF1192B Dynamic Diameter](https://www.luogu.com.cn/problem/CF1192B)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1748675)

## 题意
- 给定一颗$n$个点的树，每条边有一个权值；
- $q$次操作，每次操作修改一条边的权值，并询问当前树的直径；
- **强制在线**；
- 数据范围：$1\leqslant n,q\leqslant 10^5$。

## 分析
欧拉序+线段树维护好题。

对于一个直径$(x,y)$，我们可以把它拆成两条链$(x,lca(x,y))$和$(lca(x,y),y)$，此时，我们要引入一个叫欧拉序的东西：

欧拉序与dfs序很类似，对于每个结点，在进入这个结点子树时记录一遍欧拉序，每一次从儿子子树中出来时也记录一遍欧拉序。

下面给出记录欧拉序的代码：
```
void dfs(int x,int last){
	q[++qs]=x,in[x]=qs;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last)
			continue;
		dfs(y,x);
		q[++qs]=x;
	}
	out[x]=qs;
}
```

其中$q$为欧拉序组成的序列，$in_x$为进入$x$子树时的欧拉序，$out_x$则为出$x$子树时的欧拉序。

这种序列有什么性质呢？

- 序列长度为$2n-1$：这个很显然，我们观察到**每一条边会贡献两遍欧拉序**，再加上**进入根结点贡献一次欧拉序**，总次数为$2(n-1)+1=2n-1$。
- 对于两个结点$x$和$y$的$lca$，它一定会在$in_x$和$in_y$中间记录一遍欧拉序，且它是$in_x$到$in_y$区间内记录了欧拉序的**深度最小结点**：这也很显然，因为在遍历$x$到遍历$y$的过程中，一定不会出$lca$的子树，因此没有比$lca$深度还小的子树。
- **一个子树中所有点贡献的欧拉序一定是一段连续的区间**：由dfs顺序便可得这一点。

有了这个欧拉序，我们就相当于把这个树**拍平**了（类似于dfs序），我们来看这两个操作：

- 修改操作：$(x,y)$的边权赋值可以转化为一个加法，设在$\text{dfs}$中$x$是$y$的父亲（否则可以交换$x,y$），那么我们对$y$子树内所有点的深度进行加法就好了，在序列上就直接进行**线段树区间加操作**。
- 查询操作：考虑把直径的计算方法$dep_x+dep_y-2dep_{lca}$，如何在线段树上维护这个东西呢？我们把它**分成两部分**：$(dep_x-2dep_{lca})+dep_y$（可以交换顺序），然后再维护一些值就好了。

维护直径具体操作：

维护当前区间的最大深度$maxd_x$，最小深度$mind_x$；维护一个深度差$lm_x$，表示左边是深度深的点$x$，右边是深度浅的点$y$，它们的$dep_x-2dep_y$最大是多少，同理维护一个深度差$mr_x$，表示左边是深度浅的点$y$，右边是深度深的点$x$，它们的$dep_x-2dep_y$最大是多少，这两个东西可以很轻松的完成维护。

然后，我们维护一个路径长度$lmr_x$，代表左边一个深度深的点，中间一个深度浅的点（$lca$），右边一个深度深的点，它们的路径长度最长是多少。这个$lmr_x$可以继承左右区间的$lmr_x$，也可以用左区间的$lm_x$和右区间的$maxd_x$来合并，或者用左区间的$maxd_x$和右区间的$mr_x$合并。

维护上述值的代码：
```
inline void pushup(int now){
	maxd[now]=max(maxd[lc[now]],maxd[rc[now]]);
	mind[now]=min(mind[lc[now]],mind[rc[now]]);
	lm[now]=max(max(lm[lc[now]],lm[rc[now]]),maxd[lc[now]]-2*mind[rc[now]]);
	mr[now]=max(max(mr[lc[now]],mr[rc[now]]),maxd[rc[now]]-2*mind[lc[now]]);
	lmr[now]=max(max(lmr[lc[now]],lmr[rc[now]]),max(lm[lc[now]]+maxd[rc[now]],maxd[lc[now]]+mr[rc[now]]));
}
```

时间复杂度：$O(n\log n)$。

## 代码
边权很大，记得开$\text{long long}$。

完整代码：
```
#include<stdio.h>
#define int long long
const int maxn=100005;
int n,m,w,qs,e,lastans;
int start[maxn],to[maxn<<1],then[maxn<<1],worth[maxn<<1],id[maxn<<1],dis[maxn],in[maxn],out[maxn],q[maxn<<1],tid[maxn],val[maxn],maxd[maxn<<3],mind[maxn<<3],lm[maxn<<3],mr[maxn<<3],lmr[maxn<<3],lc[maxn<<3],rc[maxn<<3],lazy[maxn<<3];
inline int max(int a,int b){
	return a>b? a:b;
}
inline int min(int a,int b){
	return a<b? a:b;
}
inline void add(int x,int y,int z,int i){
	then[++e]=start[x],start[x]=e,to[e]=y,worth[e]=z,id[e]=i;
}
void dfs(int x,int last){
	q[++qs]=x,in[x]=qs;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last)
			continue;
		dis[y]=dis[x]+worth[i];
		tid[id[i]]=y;
		dfs(y,x);
		q[++qs]=x;
	}
	out[x]=qs;
}
inline void pushup(int now){
	maxd[now]=max(maxd[lc[now]],maxd[rc[now]]);
	mind[now]=min(mind[lc[now]],mind[rc[now]]);
	lm[now]=max(max(lm[lc[now]],lm[rc[now]]),maxd[lc[now]]-2*mind[rc[now]]);
	mr[now]=max(max(mr[lc[now]],mr[rc[now]]),maxd[rc[now]]-2*mind[lc[now]]);
	lmr[now]=max(max(lmr[lc[now]],lmr[rc[now]]),max(lm[lc[now]]+maxd[rc[now]],maxd[lc[now]]+mr[rc[now]]));
}
inline void getlazy(int now,int v){
	maxd[now]+=v,mind[now]+=v;
	lm[now]-=v,mr[now]-=v;
	lazy[now]+=v;
}
inline void pushdown(int now){
	if(lazy[now]==0)
		return ;
	getlazy(lc[now],lazy[now]),getlazy(rc[now],lazy[now]);
	lazy[now]=0;
}
void build(int l,int r,int now){
	if(l==r){
		getlazy(now,dis[q[l]]);
		return ;
	}
	int mid=(l+r)>>1;
	lc[now]=now<<1,rc[now]=now<<1|1;
	build(l,mid,lc[now]),build(mid+1,r,rc[now]);
	pushup(now);
}
void update(int l,int r,int now,int L,int R,int v){
	if(L<=l&&r<=R){
		getlazy(now,v);
		return ;
	}
	int mid=(l+r)>>1;
	pushdown(now);
	if(L<=mid)
		update(l,mid,lc[now],L,R,v);
	if(mid<R)
		update(mid+1,r,rc[now],L,R,v);
	pushup(now);
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&w);
	for(int i=1;i<n;i++){
		int x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z,i),add(y,x,z,i);
		val[i]=z;
	}
	dfs(1,0);
	build(1,qs,1);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		x=(x+lastans)%(n-1)+1,y=(y+lastans)%w;
		update(1,qs,1,in[tid[x]],out[tid[x]],y-val[x]);
		val[x]=y,lastans=lmr[1];
		printf("%lld\n",lastans);
	}
	return 0;
}
```

---

## 作者：Meteorshower_Y (赞：9)

## CF1192B 题解
[题目链接](https://www.luogu.com.cn/problem/CF1192B)  
跟着 [duyi](https://dfsafdsgaksgh.blog.luogu.org/solution-cf1192b) dalao的思路, 轻而易举(qian nan wan xian)调出了本题。  
既然@ [duyi](https://www.luogu.com.cn/user/100674)没放代码, 那我就~~来一发~~吧。  
(管理大大辛苦了)

2022.8.12 修正错别字(感谢 @ MarchKid_Joe)

### 题意简述
有一个 $n$ 个点的带权无向树， $q$ 次操作，每次修改一条边的权值，要求在每次修改后，输出树的直径大小，强制在线。

### 题目分析
1. 对于两棵树合并后新树的直径, 其两端点一定出自两树直径四个端点中, 根据这一条性质我们就可以用线段树维护原树, 自下向上合并节点就相当于合并它所代表的两棵子树。

2. 每次合并的时候, 需要我们计算树上两点间距离, 记该节点到根的距离为 $\operatorname{d}(x)$ , 则 节点 $x$ 到 $y$ 的距离为 $\operatorname{d}(x)+\operatorname{d}(y)-2 \times \operatorname{d}(\operatorname{lca}(x, y))$ 。在四个点的六组搭配中, 选择直径最大的一组作为答案向上传递。

3. 求树上到根的距离利用线段树(这时候是区别于第一条的另一棵)用两种选择, 将边权化为点权后, 一是单点修改加上区间查询, 二是区间修改加上单点查询(边权改变影响的只有子树, 而子树在树剖后节点编号连续)。而这里我们采取后者。至于为什么不用前者...~~血的教训~~。

### 思路实现
1. 我们对求出原树的 dfs 序, 同时记录以该节点为根的子树在 dfs 序中的开始和结束编号, 记为 $\operatorname{beg}(x)$ 和 $\operatorname{end}(x)$ ,对 dfs 序建立第一棵线段树。 该线段树维护树的直径。
2. 对原树重链剖分,建第二棵线段树维护每个点到根的路径长。当然还要求 LCA  。
3. 可以使用 unordered_map 记录下求过的 LCA, 用 map 会多一个 $\log$ 的复杂度。

### Code
代码中函数名带有 "_1" 的为维护直径的线段树, 带有 "_2" 的为维护到根距离的线段树。  

树剖就不需要解释了吧(
```cpp
auto dfs1(int x, int fa) -> void
{
    f[x] = fa; siz[x] = 1;
    dep[x] = dep[fa]+1;
    int maxson = 0, y;
    for(int i = head[x]; i; i = a[i].next)
    {
        y = a[i].to; if(y == fa) continue;
        dfs1(y, x); siz[x] += siz[y];
        if(siz[y] > siz[maxson]) maxson = y;
    }
    son[x] = maxson;
}
auto dfs2(int x, int tp) -> void
{
    id[x] = ++tim; top[x] = tp;
    if(son[x]) 
    {
        dfs2(son[x], tp); int y;
        for(int i = head[x]; i; i = a[i].next)
        {
            y = a[i].to;
            if(y == f[x] or y == son[x]) continue;
            dfs2(y, y);
        }
    }
}
auto LCA(int x, int y) -> int
{
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]]) y = f[top[y]]; 
        else x = f[top[x]];
    }
    if(id[x] > id[y]) return y;
    return x;
}
```
求 dfs 序
```cpp
auto dfsx(int x) -> void
{
    d[++ct] = x;    //dfs序数组
    beg[x] = ct;    //子树起点
    for(int i = head[x], y; i; i = a[i].next)
    {
        y = a[i].to; if(y == f[x]) continue;
        dfsx(y);
    }
    ::end[x] = ct;  //子树终点(变量名end有冲突,所以加了作用域)
}
```
第一棵线段树
```cpp
auto build_1(int l, int r, int i) -> void
{
    dr[i].l = l;
    dr[i].r = r;
    if(l == r) return (void)(dr[i].u = dr[i].v = d[l]);
    int mid = (l+r)>>1;
    build_1(l, mid, ls(i));
    build_1(mid+1, r, rs(i));
    pushup_1(i);
}
auto change_1(int l, int r, int i) -> void
{
    if(dr[i].l > r or dr[i].r < l) return ;
    if(dr[i].l >= l and dr[i].r <= r) return ;
    change_1(l, r, ls(i));
    change_1(l, r, rs(i));
    pushup_1(i);
}
auto pushup_1(int i) -> void
{
    lu = dr[ls(i)].u, lv = dr[ls(i)].v;
    ru = dr[rs(i)].u, rv = dr[rs(i)].v;

    /*  左右子树的较优解  */
    if(dr[ls(i)].val >= dr[rs(i)].val) 
        dr[i].u = dr[ls(i)].u, 
        dr[i].v = dr[ls(i)].v, 
        dr[i].val = dr[ls(i)].val; 
    else 
        dr[i].u = dr[rs(i)].u, 
        dr[i].v = dr[rs(i)].v, 
        dr[i].val = dr[rs(i)].val; 

    /*  枚举剩下四种情况  */
    U = lu, V = ru; 
    len = calc(U, V);
    if(ru != rv) //重复的不计算了
    {   
        len2 = calc(lu, rv); 
        if(len2 > len) U = lu, V = rv, len = len2;
    }

    if(lu != lv) //重复的不计算了
    {
        len2 = calc(lv, ru); 
        if(len2 > len) U = lv, V = ru, len = len2;
        if(ru != rv) //重复的不计算了 
        {
            len2 = calc(lv, rv); 
            if(len2 > len) U = lv, V = rv, len = len2;
        }
    }

    if(len > dr[i].val) 
        dr[i].val = len, dr[i].u = U, dr[i].v = V;
}
auto calc(int x, int y) -> long
{
    int lca;
    /* 将 x,y 压入一个数, 就不用 pair 了 */
    if( !mp.count(((long)(x)<<32ll)+y) ) mp[((long)(x)<<32ll)+y] = lca = LCA(x, y);
    else lca = mp[((long)(x)<<32ll)+y];
    return query_2(id[x], 1)+query_2(id[y], 1)-2*query_2(id[lca], 1);
}
```
第二棵线段树
```cpp
auto build_2(int l, int r, int i) -> void
{
    tr[i].l = l;
    tr[i].r = r;
    if(l == r) return ;
    int mid = (l+r)>>1;
    build_2(l, mid, ls(i));
    build_2(mid+1, r, rs(i));
}
auto add_2(int l, int r, long k, int i) -> void
{
    if(tr[i].l > r or tr[i].r < l) return ;
    if(tr[i].l >= l and tr[i].r <= r) 
    {
        tr[i].lz += k;
        tr[i].val += k*(tr[i].r-tr[i].l+1);
        return ;
    }
    pushdown_2(i);
    add_2(l, r, k, ls(i));
    add_2(l, r, k, rs(i));
    tr[i].val = tr[ls(i)].val+tr[rs(i)].val;
}
auto query_2(int x, int i) -> long
{
    if(tr[i].l > x or tr[i].r < x) return 0;
    if(tr[i].l == x and tr[i].r == x) return tr[i].val;
    pushdown_2(i);
    return query_2(x, ls(i))+query_2(x, rs(i));
}
auto pushdown_2(int i) -> void
{
    if(!tr[i].lz) return ;
    tr[ls(i)].lz += tr[i].lz;
    tr[rs(i)].lz += tr[i].lz;
    tr[ls(i)].val += tr[i].lz*(tr[ls(i)].r-tr[ls(i)].l+1);
    tr[rs(i)].val += tr[i].lz*(tr[rs(i)].r-tr[rs(i)].l+1);
    tr[i].lz = 0;
}

```
接下来是主函数, ~~得斯~~
```cpp
auto main() -> signed
{
    scanf("%d%d%lld", &n, &q, &w);
    for(int i = 1; i < n; i += 1)
    {
        scanf("%d%d%lld", &u[i], &v[i], &c[i]);
        add_edge(u[i], v[i]);
        add_edge(v[i], u[i]);
    }
    dfs1(1, 0); dfs2(1, 1);  //剖了它
    build_2(1, n, 1);        //_____
    for(int i = 1; i < n; i += 1)
    {
        if(dep[u[i]] > dep[v[i]])       //加入初始边权
            add_2(id[u[i]], id[u[i]]+siz[u[i]]-1, c[i], 1);
        else  
            add_2(id[v[i]], id[v[i]]+siz[v[i]]-1, c[i], 1);
    }
    dfsx(1); 
    build_1(1, n, 1);
    for(int i = 1, D; i <= q; i += 1)
    {
        scanf("%d%lld", &D,&E);
        D = (D+lst)%(n-1)+1;
        E = (E+lst)%w;
        if(dep[u[D]] > dep[v[D]])  
        {
            add_2(id[u[D]], id[u[D]]+siz[u[D]]-1, E-c[D], 1);  //权值的修改
            change_1(beg[u[D]], ::end[u[D]], 1);               //直径的更新
            c[D] = E;
        }
        else 
        {
            add_2(id[v[D]], id[v[D]]+siz[v[D]]-1, E-c[D], 1);
            change_1(beg[v[D]], ::end[v[D]], 1);
            c[D] = E;
        }
        lst = dr[1].val;
        printf("%lld\n", lst);
    }
    return 0;
}
```
### 结语
常数有那么~~亿点点大~~。  
若有什么问题欢迎评论或私信指出。  
$\Huge{The End}$

---

## 作者：zhengrunzhe (赞：9)

提供一个动态dp做法，另外toptree的做法在下面

无根树强行搞成根为1有根树，然后边权推点权记作$w[x]$

记$f[x][0]$表示以x为根的子树中的直径长度，$f[x][1]$表示以x为根的子树中距与x父亲的最大距离

$$f[x][0]=\max\left\{\max_{y \in son_x} \left\{f[y][0]\right\},\max_{y1≠y2\in son_x}\left\{f[y1][1]+f[y2][1]\right\}\right\}$$

$$f[x][1]=\max_{y\in son_x} \left \{f[y][1]\right\}+w[x]$$

然后我是用lct，所以是实链剖分，实儿子记作$real_x$，虚儿子集合记作$imag_x$，树剖的话一样，只不过叫作$heavy_x$和$light_x$而已

$$g[x][0]=\max\left\{\max_{y\in imag_x} \left \{f[y][0]\right\},\max_{y1≠y2\in imag_x} \left \{f[y1][1]+f[y2][1]\right\}\right\}$$

$$g[x][1]=\max_{y\in imag_x}\left\{f[y][1]\right\}$$

然后可以拿g和实儿子一起表示f

$$y=real_x$$

$$f[x][0]=\max\left\{g[x][0],f[y][0],f[y][1]+g[x][1]\right\}$$

$$f[x][1]=\max\left\{g[x][1],f[y][1]\right\}+w[x]$$

然后定义矩阵乘法

$$c_{i,j}=\max\left\{a[i][k]+b[k][j]\right\}$$

然后就可以构造矩阵

![](https://cdn.luogu.com.cn/upload/image_hosting/b3b5vh89.png)

开个$multiset$(可删堆)维护虚儿子就好了
```cpp
#include<set>
#include<cstdio>
using std::greater;
using std::multiset;
typedef long long ll;
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const void read(type &in)
{
	in=0;char ch=getchar();bool f=0;
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
template<class type>inline const void write(type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
template<class type>inline const void writeln(type out)
{
	if (out<0)putchar('-'),out=-out;
	write(out);
	putchar('\n');
}
const int N=1e5+10;
const ll inf=2e14+10;
struct matrix
{
	ll val[3][3];
	inline matrix(ll a=0,ll b=0,ll c=0,ll d=0,ll e=0,ll f=0,ll g=0,ll h=0,ll i=0)
	{
		val[0][0]=a;val[0][1]=b;val[0][2]=c;
		val[1][0]=d;val[1][1]=e;val[1][2]=f;
		val[2][0]=g;val[2][1]=h;val[2][2]=i;
	}
	inline const matrix operator*(const matrix &m)const
	{
		matrix pro(-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf,-inf);
		for (int i=0;i<3;i++)
			for (int j=0;j<3;j++)
				for (int k=0;k<3;k++)
					pro.val[i][j]=max(pro.val[i][j],val[i][k]+m.val[k][j]);
		return pro;
	}
};
struct heap
{
	multiset<ll,greater<ll> >s;
	inline const ll top()
	{
		return s.empty()?0ll:*s.begin();
	}
	inline const void push(ll x)
	{
		s.insert(x);
	}
	inline const void pop(ll x)
	{
		multiset<ll,greater<ll> >::iterator it=s.find(x);
		if (it==s.end())return;
		s.erase(it);
	}
	inline const ll maxpair()
	{
		if (s.empty())return 0;
		multiset<ll,greater<ll> >::iterator it=s.begin();
		ll mx=*it;
		if (s.size()==1)return mx;
		return mx+*(++it);
	}
};
int n,m,head[N],edc,dot[N];
ll w,lastans;
struct edge
{
	int to,next;ll w;
	inline edge(const int &to=0,const ll &w=0ll,const int &next=0):to(to),w(w),next(next){}
}e[N<<1];
inline const void link(int u,int v,ll w)
{
	e[++edc]=edge(v,w,head[u]);head[u]=edc;
	e[++edc]=edge(u,w,head[v]);head[v]=edc;
}
class Link_Cut_Tree
{
	private:
		struct tree
		{
			matrix m;
			heap f0,f1;
			ll val,f[2];
			int son[2],fa;
		}t[N];
		inline const void pushup(int p)
		{
			ll g0=max(t[p].f0.top(),t[p].f1.maxpair()),g1=t[p].f1.top();
			t[p].m=matrix(0,g1,g0,-inf,t[p].val,t[p].val+g1,-inf,-inf,0);
			if (t[p].son[0])t[p].m=t[t[p].son[0]].m*t[p].m;
			if (t[p].son[1])t[p].m=t[p].m*t[t[p].son[1]].m;
		}
		inline const bool identity(int p)
		{
			return t[t[p].fa].son[1]==p;
		}
		inline const bool nroot(int p)
		{
			return t[t[p].fa].son[0]==p||identity(p);
		}
		inline const void rotate(int p)
		{
			bool f=identity(p);
			int fa=t[p].fa,gfa=t[fa].fa,q=t[p].son[f^1];
			if (nroot(fa))t[gfa].son[identity(fa)]=p;
			t[t[p].son[f^1]=fa].son[f]=q;
			t[t[t[q].fa=fa].fa=p].fa=gfa;
			pushup(fa);
		}
		inline const void splay(int p)
		{
			for (int fa;nroot(p);rotate(p))
				if (nroot(fa=t[p].fa))
					rotate(identity(p)^identity(fa)?p:fa);
			pushup(p);
		}
		inline const void access(int x)
		{
			for (int y=0;x;x=t[y=x].fa)
			{
				splay(x);
				if (t[x].son[1])
					t[x].f0.push(max(t[t[x].son[1]].m.val[0][1],t[t[x].son[1]].m.val[0][2])),
					t[x].f1.push(t[t[x].son[1]].m.val[1][2]);
				if (t[x].son[1]=y)
					t[x].f0.pop(max(t[y].m.val[0][1],t[y].m.val[0][2])),
					t[x].f1.pop(t[y].m.val[1][2]);
				pushup(x);
			}
		}
	public:
		inline const void dfs(int p)
		{
			ll mx=0ll,submx=0ll;
			for (int i=head[p];i;i=e[i].next)
			{
				int son=e[i].to;
				if (son==t[p].fa)continue;
				t[son].fa=p;
				t[dot[i+1>>1]=son].val=e[i].w;
				dfs(son);
				t[p].f1.push(t[son].f[1]);
				t[p].f0.push(t[son].f[0]);
				t[p].f[0]=max(t[p].f[0],t[son].f[0]);
				if (t[son].f[1]>mx)submx=mx,mx=t[son].f[1];
				else if (t[son].f[1]>submx)submx=t[son].f[1];
			}
			
			t[p].f[1]=mx+t[p].val;
			t[p].f[0]=max(t[p].f[0],mx+submx);
			pushup(p);
		}
		inline const void modify(int x,ll y)
		{
			access(x);
			t[x].val=y;
			pushup(x);
			splay(x);
		}
		inline const ll query()
		{
			splay(1);return t[1].m.val[0][2];
		}
}lct;
int main()
{
	read(n);read(m);read(w);
	ll l;for (int u,v,i=1;i<n;i++)read(u),read(v),read(l),link(u,v,l);
	lct.dfs(1);
	for (int u;m--;)
		read(u),read(l),
			u=(u+lastans)%(n-1)+1,l=(l+lastans)%w,
			lct.modify(dot[u],l),writeln(lastans=lct.query());
	return 0;
}
```

## Self-Adjusting Top Trees

主要介绍见[negiizhao的博客](http://negiizhao.blog.uoj.ac/blog/4912)

维护直径的详细方法见[negiizhao的另一篇论文](http://negiizhao.blog.uoj.ac/blog/3223)

![](https://cdn.luogu.com.cn/upload/image_hosting/uaoyxhjy.png)

——摘自negiizhao《浅谈动态树上信息的维护》

放在self-adjusting的三叉实现中

$compress \ node$的$maxdis[0/1]$表示到左/右端点的最大距离, $len$表示簇路径长度, $son[2]$表示$rake \ child$

$rake \ node$只需用到$maxdis[0]$表示到$boundary \ node$的最远距离, $son[2]$表示$compress \ child$

$diam$表示该簇的直径

如下更新合并簇信息即可

$compress$:

$len=son[0]\rightarrow len+son[1]\rightarrow len$

$maxdis[0]=\max(son[0]\rightarrow maxdis[0],son[0]\rightarrow len+\max(son[1]\rightarrow maxdis[0],son[2]\rightarrow maxdis[0]))$

$maxdis[1]=\max(son[1]\rightarrow maxdis[1],son[1]\rightarrow len+\max(son[0]\rightarrow maxdis[1],son[2]\rightarrow maxdis[0]))$

$diam=\max \left \{son[0]\rightarrow diam,son[1]\rightarrow diam,son[2]\rightarrow diam,son[0]\rightarrow maxdis[1]+son[1]\rightarrow maxdis[0],son[2]\rightarrow maxdis[0]+\max(son[0]\rightarrow maxdis[1],son[1]\rightarrow maxdis[0]) \right \}$

$rake:$

$maxdis[0]=\max \left \{son[0]\rightarrow maxdis[0],son[1]\rightarrow maxdis[0],son[2]\rightarrow maxdis[0] \right \}$

$diam=\max \left \{son[0]\rightarrow diam,son[1]\rightarrow diam,son[2]\rightarrow diam,son[0]\rightarrow maxdis[0]+son[1]\rightarrow maxdis[0],son[2]\rightarrow maxdis[0]+\max(son[0]\rightarrow maxdis[0],son[1]\rightarrow maxdis[0])\right \}$

$compress$的$maxdis$更新类似区间最大子段和，比较好理解，$diam$的话就是每个簇的$diam$比一下然后讨论一下跨越两簇的情况

$rake$的$maxdis$由于每个簇有共同的$boundary \ node$，直接取最大的那个就完事了，$diam$同理

特别地，$base \ cluster$的$maxdis[0]=maxdis[1]=diam=len$

$O(n \log n)$ 代码不完全公开

~~向论文哥低头~~

```cpp
#include<cstdio>
#include<cstddef>
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());
	while (ch<48||ch>57)ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
}
template<class type>inline const void swap(type &a,type &b)
{
	const type c(a);a=b;b=c;
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
typedef long long ll;
const int N(1e5+10);
namespace Self_Adjusting_Top_Trees
{
	template<>inline const void tree::pushup<compress>()
	{
		len=son[0]->len+son[1]->len;
		diam=max(son[0]->maxdis[1]+son[1]->maxdis[0],max(son[0]->maxdis[1],son[1]->maxdis[0])+son[2]->maxdis[0]);
		diam=max(diam,max(max(son[0]->diam,son[1]->diam),son[2]->diam));
		maxdis[0]=max(son[0]->maxdis[0],son[0]->len+max(son[2]->maxdis[0],son[1]->maxdis[0]));
		maxdis[1]=max(son[1]->maxdis[1],son[1]->len+max(son[2]->maxdis[0],son[0]->maxdis[1]));
	}
	template<>inline const void tree::pushup<rake>()
	{
		diam=max(son[0]->maxdis[0]+son[1]->maxdis[0],son[2]->maxdis[0]+max(son[0]->maxdis[0],son[1]->maxdis[0]));
		diam=max(max(diam,son[2]->diam),max(son[0]->diam,son[1]->diam));
		maxdis[0]=max(son[2]->maxdis[0],max(son[0]->maxdis[0],son[1]->maxdis[0]));
	}
	inline const void modify(tree *p,tree *q,const ll &w)
	{
		expose(p,q);
		p->son[1]->maxdis[0]=p->son[1]->maxdis[1]=p->son[1]->len=p->son[1]->diam=w;
		p->pushup<compress>();
		q->pushup<compress>();
	}
}using namespace Self_Adjusting_Top_Trees;
int n,m,u[N],v[N];
ll maxw,lastans;
int main()
{
	read(n);read(m);read(maxw);
	node0=new tree[n+1];
	ll w;for (int i=1;i<n;i++)read(u[i]),read(v[i]),read(w),link(node(u[i]),node(v[i]),w);
	for (int k;m--;)
		read(k),read(w),
		k=(lastans+k)%(n-1)+1,
		w=(w+lastans)%maxw,
		modify(node(u[k]),node(v[k]),w),
		printf("%I64d\n",lastans=node(v[k])->diam);
	return 0;
}
```

---

## 作者：KaisuoShutong (赞：5)

## 题目描述

标题说的很清楚，动态直径。

## 题目分析

拿到这题。  
DDP？树剖？LCT？

这题我们选择用DDP+树剖/LCT，或者树剖/Splay+LCA，爆踩Segment Tree。  
并不，我们着重介绍线段树上标记拼接的办法。

首先，考虑变树上操作为序列操作。
用什么顺序好呢？

欧拉序。  
看到其他题解告诉我那个叫全DFS序并说了一个很迷的定义，我一脸懵T_T，不就是欧拉序吗？

这时，根据定义，树上任意时间戳之间的序列代表了一段路径。
此时，开一颗线段树，维护以下几个值。

1. 距离根最远的距离；
2. 距离根最近的距离；
3. 选择左端点以及lca的最长距离；
4. 选择右端点以及lca的最长距离；
5. 选择整个区间（也就是一条链）的距离；

维护就非常简单了。  
但是！此时有一个奇技淫巧。为了方便计算，我们在记录2的答案时，记录它的-2倍。

但是因为对欧拉序操作为区间加减，所以还要维护一个tag。

至此，六个标记就可以解决问题。

```cpp
struct Edge{int to,next,v;}a[maxn];
int h[maxn>>2],cnt,n,q,W,la,dfn[maxn>>2],low[maxn<<2],eu[maxn>>1],d[maxn>>2],dep[maxn>>2];
int tag[maxn],mx[maxn],mn[maxn],lm[maxn],rm[maxn],lmr[maxn];
void add(int x,int y,int z) {a[++cnt]=(Edge){y,h[x],z},h[x]=cnt,a[++cnt]=(Edge){x,h[y],z},h[y]=cnt;}
void Dfs(int x,int pa)
{
	dfn[eu[++eu[0]]=x]=eu[0];
	for(int i=h[x];i;i=a[i].next)
		if(a[i].to^pa) dep[a[i].to]=dep[x]+1,d[a[i].to]=d[x]+a[i].v,Dfs(a[i].to,x),eu[++eu[0]]=x;
	low[x]=eu[0];
}
void Pushdown(int k)
{
	if(tag[k])
	{
		tag[k<<1]+=tag[k],tag[k<<1|1]+=tag[k];
		mx[k<<1]+=tag[k],mx[k<<1|1]+=tag[k];
		mn[k<<1]-=tag[k]<<1,mn[k<<1|1]-=tag[k]<<1;
		lm[k<<1]-=tag[k],lm[k<<1|1]-=tag[k];
		rm[k<<1]-=tag[k],rm[k<<1|1]-=tag[k];
		tag[k]=0;
	}
}
void Pushup(int k)
{
	mx[k]=max(mx[k<<1],mx[k<<1|1]);
	mn[k]=max(mn[k<<1],mn[k<<1|1]);
	lm[k]=max(max(lm[k<<1],lm[k<<1|1]),mx[k<<1]+mn[k<<1|1]);
	rm[k]=max(max(rm[k<<1|1],rm[k<<1]),mx[k<<1|1]+mn[k<<1]);
	lmr[k]=max(max(max(lmr[k<<1],lmr[k<<1|1]),mx[k<<1]+rm[k<<1|1]),lm[k<<1]+mx[k<<1|1]);
}
void Build(int k,int l,int r)
{
	if(l==r) return mx[k]=d[eu[l]],mn[k]=-d[eu[l]]<<1,lm[k]=rm[k]=-d[eu[l]],void(0);
	int mid=l+r>>1;
	Build(k<<1,l,mid),Build(k<<1|1,mid+1,r);
	Pushup(k);
}
void Update(int k,int l,int r,int L,int R,int d)
{
	if(R<l||r<L) return;
	if(L<=l&&r<=R) return mx[k]+=d,mn[k]-=d<<1,lm[k]-=d,rm[k]-=d,tag[k]+=d,void(0);
	int mid=l+r>>1;Pushdown(k);
	Update(k<<1,l,mid,L,R,d),Update(k<<1|1,mid+1,r,L,R,d);
	Pushup(k);
}
signed main()
{
	int x,y,z,w;
	n=read(),q=read(),W=read();
	for(int i=1;i<n;i++) x=read(),y=read(),add(x,y,read());
	Dfs(1,0),Build(1,1,eu[0]);
	while(q--) z=(read()+la)%(n-1)+1,w=(read()+la)%W,x=a[z<<1].to,y=a[(z<<1)-1].to,x=dep[x]<dep[y]?y:x,Update(1,1,eu[0],dfn[x],low[x],w-a[z<<1].v),a[z<<1].v=w,printf("%lld\n",la=lmr[1]);
	return 0;
}
```

---

## 作者：renhr2002 (赞：5)

感觉自己好久没写过题解了。并且这还是自己的第1道灰题，就来OF2一发吧。

首先，这题的部分分还是很好拿的。

1. 子任务1&2：每次暴力求出树的直径即可，时间复杂度$O(qn)$；
2. 子任务3：由于树的形态为菊花图，显然此时的直径为最长边加次长边，这样，用线段树维护最大值与次大值即可,$O(nlogn)$；
3. 子任务4：树的形态为平衡二叉树，则对于每个节点，其子树中的直径最大值，以及以这个点为一端，且在其子树中的最大链长，$O(nlogn)$

最后100%做法：

子任务5&6：把直径拆成L~M~R的形式，则直径长度为dis(L)+dis(R)-2dis(M)；这样，我们可以求出树的欧拉序，并且记录下每个点在欧拉序上第一次和最后一次出现的位置，在此基础上建立线段树，维护区间的最大值、M、LM、MR、LMR，可见答案为线段树1号点的LMR。

维护方法：

M：本题要使M尽可能小，则取相反数维护最大值即可。

LM：一种可能是线段树上子节点的值就是该点的值（二者取max），另一种是线段树上左子树val加上右子树M，MR同理。

LMR：一种是在子树内，只需把线段树子节点的LMR取max即可；另一种是经过子树树根，需要利用val、LM、MR进行合并。

修改时，找出对应边上深度较大的点，对这个点子树的欧拉序进行区间修改。

std(c++):

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 102400
#define ll long long
char str;
int n,q;
ll w;
struct edge
{
	int to;
	int nxt;
	ll vl;
}nd[2*maxn];
int head[maxn],cnt;
int st[maxn],ed[maxn],eul[2*maxn];
int fa[maxn],cut;
ll ans,dep[maxn],wei[maxn];
ll val[8*maxn],M[8*maxn],LM[8*maxn],MR[8*maxn],LMR[8*maxn];
ll la[8*maxn];
template<class X> inline void read(X &x)
{
	x=0;
	X f=1;
	while(!isdigit(str))
	{
		if(str=='-')
		{
			f=-1;
		}
		str=getchar();
	}
	while(isdigit(str))
	{
		x*=10;
		x+=str-'0';
		str=getchar();
	}
	x*=f;
	return;
}
void init()
{
	memset(head,-1,sizeof(head));
	cnt=2;
	return;
}
void add(int x,int y,ll z)
{
	nd[cnt].to=y;
	nd[cnt].nxt=head[x];
	nd[cnt].vl=z;
	head[x]=cnt++;
	return;
}
void dfs(int x)
{
	st[x]=++cut;
	eul[cut]=x;
	for(int i=head[x];i!=-1;i=nd[i].nxt)
	{
		int t=nd[i].to;
		if(t!=fa[x])
		{
			wei[t]=nd[i].vl;
			fa[t]=x;
			dep[t]=dep[x]+nd[i].vl;
			dfs(t);
			eul[++cut]=x;
		}
	}
	ed[x]=cut;
	return;
}
void pushdown(int rt,int l,int r)
{
	val[rt]+=la[rt];
	M[rt]-=la[rt]*2;
	LM[rt]-=la[rt];
	MR[rt]-=la[rt];
	if(l!=r)
	{
		la[rt<<1]+=la[rt];
		la[rt<<1|1]+=la[rt];
	}
	la[rt]=0;
	return;
}
void pushup(int rt,int l,int r)
{
	if(l==r)
	{
		return;
	}
	val[rt]=max(val[rt<<1],val[rt<<1|1]);
	M[rt]=max(M[rt<<1],M[rt<<1|1]);
	LM[rt]=max(max(LM[rt<<1],LM[rt<<1|1]),val[rt<<1]+M[rt<<1|1]);
	MR[rt]=max(max(MR[rt<<1|1],MR[rt<<1]),val[rt<<1|1]+M[rt<<1]);
	LMR[rt]=max(max(LMR[rt<<1],LMR[rt<<1|1]),max(LM[rt<<1]+val[rt<<1|1],MR[rt<<1|1]+val[rt<<1]));
	return;
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		int pos=eul[l];
		val[rt]=dep[pos];
		M[rt]=-2*dep[pos];
		LM[rt]=MR[rt]=-dep[pos];
		return;
	}else
	{
		int mid=(l+r)>>1;
		build(l,mid,rt<<1);
		build(mid+1,r,rt<<1|1);
		pushup(rt,l,r);
		return;
	}
}
void addt(int L,int R,int l,int r,int rt,ll z)
{
	if(L<=l&&R>=r)
	{
		la[rt]+=z;
		pushdown(rt,l,r);
		return;
	}else
	{
		int mid=(l+r)>>1;
		pushdown(rt,l,r);
		if(L<=mid)
		{
			addt(L,R,l,mid,rt<<1,z);
		}
		if(R>mid)
		{
			addt(L,R,mid+1,r,rt<<1|1,z);
		}
		pushdown(rt<<1,l,mid);
		pushdown(rt<<1|1,mid+1,r);
		pushup(rt,l,r);
	}
	return;
}
int main()
{
	init();
	read(n),read(q),read(w);
	for(int i=1;i<n;i++)
	{
		int x,y;
		ll z;
		read(x),read(y),read(z);
		add(x,y,z);
		add(y,x,z);
	}
	dfs(1);
	build(1,2*n-1,1);
	while(q--)
	{
		ll x,y;
		read(x),read(y);
		x+=ans;
		x%=(n-1);
		x++;
		y+=ans;
		y%=w;
		if(fa[nd[x<<1].to]==nd[x<<1|1].to)
		{
			x=nd[x<<1].to;
		}else
		{
			x=nd[x<<1|1].to;
		}
		addt(st[x],ed[x],1,2*n-1,1,y-wei[x]);
		wei[x]=y;
		ans=LMR[1];
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：command_block (赞：4)

the 300th Blog.

**题意** : 给出一棵 $n$ 个点的带权无向树。

资瓷修改某条边的边权,并回答树的直径。 

强制在线。$n,q\leq 10^5$ ,边权均为正。

------------

可以直接无脑 `DDP` ,然而复杂度,常数,代码量都比较大。

另一个比较小清新的做法是维护**欧拉序**。

欧拉序 : `dfs` 遍历某棵树,每次**经过**某点时,将其写入欧拉序。

某个点将会被加入度数次,根节点会额外多一次,欧拉序的总长就是 $2n-1$ 的。

我们设点 $u$ 第一次写入欧拉的位置是 $in[u]$ ,可以视作类似`dfs`序的东西。

然后有一条很好的性质 :

- $lca(u,v)$ 一定在 $\big[in[u],in[v]\big]$ 中出现,且是深度最小的那个点。

  $u,v$ 显然一定都在 $lca(u,v)$ 的**不同**子树中。

  所以,遍历完 $u$ 之后,回溯到 $lca$ 才能向下达到 $v$ ,这样就保证了 $lca$ 的出现。

  其次,访问到 $v$ 时,现在对 $lca$ 子树的访问还未结束,不可能涉及到更浅的点。
  
  **附** : 如果这张图有负权边,该结论就不成立,因为可能儿子比祖先“浅”。
  
接下来,我们观察路径长度的计算式:

$$dep[u]+dep[v]-2*dep[lca(u,v)]$$

放到欧拉序上看,就变成了:

$$dep[u]+dep[v]-2*\min\limits_{t=u}^vdep[t]$$

这就是一个序列问题,考虑线段树维护。上述式子最大的对子 $(u,v)$ ,即为直径。

对于一个区间 $[l,r]$ :

设 $m0$ 为区间 $dep$ 最小值, $m1$ 为最大值。

$ls$ 为$dep[u]-2\min\limits_{t=l}^udep[t]$ 的最大值。也就是只有左半边两个点。

$rs$ 为$dep[u]-2\min\limits_{t=u}^rdep[t]$ 的最大值。也就是只有右半边两个点。

$s$ 为区间内最大的直径。也就是三个点都全了。

设我们合并的两个线段树节点为 $u,v$。

当转移时,最大的直径可以取左侧,可以取右侧,也可以跨越左右。

有两种方式跨越:

- $lca$ 在左边 : $u.rs+v.m1$

- $lca$ 在右边 : $u.m1+v.ls$

容易感知最优解一定是其中一种。

$ls$ 可以两端都在左侧 $u.ls$ ,也可以两端都在右侧,取 $v.ls$。

此外,还可以一端在左侧,一段在右侧,即为 $v.m1-2u.m0$。

$rs$ 的处理方法类似。$m0,m1$ 的处理方法是经典的,不再赘述。

而我们的修改操作可以视作对一颗子树的 $dep$ 加上某个值。

可以转为区间加,只需要把对应的值按照端点个数改改就好,具体见代码。

综上,即可在 $O(n\log n)$ 的复杂度内完成。

不到`20min`就写完了,可以说还是非常小清新的。(然而数组开小交了两次qwq)

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define pb push_back
#define ll long long
#define MaxN 150500
using namespace std;
vector<int> g[MaxN];
vector<ll> l[MaxN];
void adl(int f,int t,ll len){
  g[f].pb(t);l[f].pb(len);
  g[t].pb(f);l[t].pb(len);
}
ll dep[MaxN];
int p[MaxN<<1],in[MaxN],out[MaxN],tim;
void pfs(int u)
{
  p[in[u]=++tim]=u;
  for (int i=0,v;i<g[u].size();i++)
    if (!in[v=g[u][i]]){
      dep[v]=dep[u]+l[u][i];
      pfs(v);
      p[++tim]=u;
    }
  out[u]=tim;
}
struct Node{
  ll m0,m1,ls,rs,s,tg;
  void ladd(ll c)
  {tg+=c;m0+=c;m1+=c;ls-=c;rs-=c;}
}a[MaxN<<3];
inline void up(int u)
{
  int l=u<<1,r=u<<1|1;
  a[u].m0=min(a[l].m0,a[r].m0);
  a[u].m1=max(a[l].m1,a[r].m1);
  a[u].ls=max(max(a[l].ls,a[r].ls),-2*a[l].m0+a[r].m1);
  a[u].rs=max(max(a[l].rs,a[r].rs),a[l].m1-2*a[r].m0);
  a[u].s=max(max(a[l].s,a[r].s),max(a[l].rs+a[r].m1,a[l].m1+a[r].ls));
}
inline void ladd(int u)
{
  if (a[u].tg){
    a[u<<1].ladd(a[u].tg);
    a[u<<1|1].ladd(a[u].tg);
    a[u].tg=0;
  }
}
void build(int l=1,int r=tim,int u=1)
{
  if (l==r){
    a[u].m0=a[u].m1=dep[p[l]];
    a[u].ls=a[u].rs=-dep[p[l]];
    return ;
  }int mid=(l+r)>>1;
  build(l,mid,u<<1);
  build(mid+1,r,u<<1|1);
  up(u);
}
int wfl,wfr;ll wfc;
void add(int l=1,int r=tim,int u=1)
{
  if (wfl<=l&&r<=wfr){
    a[u].ladd(wfc);
    return ;
  }ladd(u);
  int mid=(l+r)>>1;
  if (wfl<=mid)add(l,mid,u<<1);
  if (wfr>mid)add(mid+1,r,u<<1|1);
  up(u);
}
int n,m;
struct line
{int f,t;ll w;}s[MaxN];
int main()
{
  ll lim,w,las=0;
  scanf("%d%d%lld",&n,&m,&lim);
  for (int i=1,f,t;i<n;i++){
    scanf("%d%d%lld",&s[i].f,&s[i].t,&s[i].w);
    adl(s[i].f,s[i].t,s[i].w);
  }pfs(1);build();
  for (int i=1,pl;i<=m;i++){
    scanf("%d%lld",&pl,&w);
    pl=(pl+las)%(n-1)+1;
    w=(w+las)%lim;
    wfc=w-s[pl].w;s[pl].w=w;
    int u=s[pl].f;
    if (dep[s[pl].t]>dep[u])u=s[pl].t;
    wfl=in[u];wfr=out[u];
    add();
    printf("%lld\n",las=a[1].s);
  }return 0;
}
```

---

## 作者：wind_whisper (赞：4)

# $\text{Foreword}$
@zhengrunzhe 大佬的矩阵做法过于神奇，蒟蒻无法理解...   
欧拉序的做法确实非常巧妙，但我也想不到这么神仙的做法...  
提供一种可能简单一些的 LCT 做法。  
由于本人 LCT 无法像大佬那么神，讲的会比较详细一些，也许对其他 LCT 平民玩家更加友好？
# $\text{Solution}$
本题有一个很关键的性质：**边权非负**。（欧拉序的做法也要基于这个性质）  
又发现修改无非改大/小，在/不在原直径上，利用非负的性质分别讨论一下，就会发现**新直径至少有一个节点和原来相同**。  
所以我们一开始暴力求出直径后，只需要不断把原直径的两端点提出来，用从二者出发新的最长路径来尝试作为新直径就行了。  
所以现在只需要动态维护**从一个点出发的最长路径**。  

常规套路，先边化点，边权化点权。  
设 $w_x$ 表示 $x$ 的点权，$sum_x$ 表示 $x$ splay子树内点权之和，$dis_x$ 表示从 $x$ **所在 splay 子树内深度最浅的节点出发**往子树延伸的最长路径。  
先不考虑 $x$ 实链父亲，尝试求出**从 $x$ 出发**往子树延伸的最长路径 $res_x$。    

一开始有： 
$$res_x=w_x$$
对于 $x$ 的虚儿子，对每个节点开一个 `std::set`  维护虚子树，进行转移：
$$res_x\gets \max_{son}dis_{son}+w_x$$
还有从 $x$ 的实儿子转移，不难发现其对应的就是 $dis_{rs_x}$：
$$res_x\gets dis_{rs_x}+w_x$$
求完 $res_x$ 后，如果 $x$ 没有左儿子，说明他就是链头，直接让 $dis_x=res_x$ 即可；否则，链头可以不使用 $res_x$ 的转移，或者使用 $res_x$ 的转移，那么还要加上 $x$ 到链头一段的权值和，分别对应 `max` 的前后两项：
$$dis_x=\max(dis_{ls_x},res_x+sum_{ls_x})$$

这样就做完了。由于转移不对称，所以我们还要镜像的处理一个 $dis'x$，在翻转时直接交换两项即可。
# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define ok debug("OK\n")
using namespace std;

const int N=2e5+100;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)) {if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)) {x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;


#define pr pair<ll,int>
#define mkp make_pair
pr operator + (const pr &o,const ll &w){return mkp(o.first+w,o.second);}

int tr[N][2],rev[N],f[N];
ll sum[N],w[N];
pr dis1[N],dis2[N];
multiset<pr>s[N];
#define ls(x) tr[x][0]
#define rs(x) tr[x][1]
inline bool nroot(int x){return ls(f[x])==x||rs(f[x])==x;}
inline bool which(int x){return rs(f[x])==x;}

inline void pushup(int x){
  sum[x]=w[x]+sum[ls(x)]+sum[rs(x)];
  
  dis1[x]=s[x].empty()?mkp(w[x],x<=n?x:-1):(*s[x].rbegin())+w[x];
  if(rs(x)) dis1[x]=max(dis1[x],dis1[rs(x)]+w[x]);
  if(ls(x)) dis1[x]=max(dis1[ls(x)],dis1[x]+sum[ls(x)]);
  
  dis2[x]=s[x].empty()?mkp(w[x],x<=n?x:-1):(*s[x].rbegin())+w[x];
  if(ls(x)) dis2[x]=max(dis2[x],dis2[ls(x)]+w[x]);
  if(rs(x)) dis2[x]=max(dis2[rs(x)],dis2[x]+sum[rs(x)]);
  
  return;
}
inline void Rev(int x){
  if(x){
    rev[x]^=1;
    swap(ls(x),rs(x));
    swap(dis1[x],dis2[x]);
  }
  return;
}
inline void pushdown(int x){
  if(rev[x]){
    rev[x]=0;
    Rev(ls(x));
    Rev(rs(x));
  }
  return;
}
void dfs(int x){
  if(!x) return;
  pushdown(x);
  debug("x=%d f=%d ls=%d rs=%d w=%lld dis1=(%lld %d) s: ",x,f[x],ls(x),rs(x),w[x],dis1[x].first,dis1[x].second);
  for(pr o:s[x]) debug("(%lld %d) ",o.first,o.second);
  debug("\n");
  dfs(ls(x));dfs(rs(x));
}
void print(){
  for(int i=1;i<=n+n-1;i++){
    if(!nroot(i)) dfs(i);
  }
}
inline void rotate(int x){
  int fa=f[x],gfa=f[fa];
  int d=which(x),son=tr[x][d^1];
  f[x]=gfa;if(nroot(fa)) tr[gfa][which(fa)]=x;
  f[fa]=x;tr[x][d^1]=fa;
  if(son) {f[son]=fa;}tr[fa][d]=son;
  pushup(fa);pushup(x);
  return;
}
int zhan[N];
inline void splay(int x){
  int top=0,y=x;
  zhan[++top]=y;
  while(nroot(y)) zhan[++top]=y=f[y];
  while(top) pushdown(zhan[top--]);
  for(int fa;fa=f[x],nroot(x);rotate(x)){
    if(nroot(fa)) which(fa)==which(x)?rotate(fa):rotate(x);
  }
  return;
}
inline void access(int x){
  for(int y=0;x;y=x,x=f[x]){
    splay(x);
    if(rs(x)){
      s[x].insert(dis1[rs(x)]);
    }
    if(y){
      s[x].erase(s[x].find(dis1[y]));
    }
    rs(x)=y;
    pushup(x);
  }
  return;
}
inline void makeroot(int x){
  access(x);splay(x);Rev(x);
}
inline void link(int x,int y){
  makeroot(x);makeroot(y);
  f[x]=y;
  s[y].insert(dis1[x]);
  pushup(y);
  return;
}

ll mod;
ll D;
int a,b;
signed main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  #endif
  n=read();m=read();mod=read();
  for(int i=1;i<n;i++){
    int x=read(),y=read();
    w[n+i]=read();
    link(x,n+i);
    link(y,n+i);
  }
  for(int i=1;i<=n;i++){
    makeroot(i);
    if(dis1[i].first>D){
      D=dis1[i].first;
      a=i;b=dis1[i].second;
    }
  }
  ll lst=0;
  while(m--){
    ll x=(read()+lst)%(n-1)+1 +n,ww=(read()+lst)%mod;    
    makeroot(x);
    w[x]=ww;pushup(x);
    int u=a,v=b;
    D=a=b=0;

    makeroot(u);
    if(dis1[u].first>=D){
      D=dis1[u].first;
      a=u;b=dis1[u].second;
    }
    
    makeroot(v);
    if(dis1[v].first>=D){
      D=dis1[v].first;
      a=v;b=dis1[v].second;
    }

    printf("%lld\n",lst=D);
  }
  return 0;
}
/*
*/
 
```


---

## 作者：Deep_Kevin (赞：3)


没想到啊没想到

调了2h的动态点分治,看了看题解区,落泪了,全是线段树+欧拉序

动态点分治可以轻松做到两个$\log$,看看本题的数据范围和时限,也感觉显然可过.

具体做法就是:对于每一个分治中心,维护一个以当前分治中心进行深搜$dfs$序为下标的一棵线段树,线段树的每一个点存一个权值和两个$pair$,这个权值等会再说,两个$pair$分别记录最大深度的对应子树,最大深度的值,次大深度的对应子树,次大深度的值,合并两个点的时候分类讨论一下.

对于一个分治中心来说,线段树的根节点的两条路径加起来就是答案.

修改就是在点分树上跳,建树的时候记录一下$x$在$y$这个分治中心对应的$dfs$序是多少,对于每一个分治中心记一记$dfs$序为$x$的子树右端点$dfs$序和$dfs$序为$x$在树上的父亲.把每一个分治中心的答案丢进一个multiset里面,更改的时候就找出来删掉,再插入新的,改边权相当于对于一个分治中心改一段的深度,这也是为什么要记这两个值的原因.

然后就做完了,~~简(dai)单(ma)易(e)懂(xin)~~

```cpp
#include<bits/stdc++.h>
#define pii pair<int,long long>
using namespace std;

const int N=100010;
struct tree{
	pii mmax,cmax;
	int ls,rs;
	long long tag,ans;
}tr[N*40];
struct edge{
	int y,nex;
	long long c;
}s[N<<1];
int first[N],len=0,root=0,tot[N],son[N],siz[N],fa[N],dep[N],rt[N];
vector<int> R[N],F[N];//R当前dfs序子树内右端点的dfs序,F当前dfs序节点的父亲(不是父亲的dfs序)
map<int,int> mp[N];//点->dfs序
int sz;
multiset<long long> ANS;
multiset<long long>::iterator it;
bool tf[N];
int n,q,T;
long long w;

void ins(int x,int y,long long c){s[++len]=(edge){y,first[x],c};first[x]=len;}

int pa,ppa;
vector<pii>*P;

void update(tree&now,pii ad){
	if(now.mmax.second<ad.second){
		if(now.mmax.first!=ad.first) now.cmax=now.mmax;
		now.mmax=ad;
	}
	else if(now.mmax.first!=ad.first && ad.second>now.cmax.second) now.cmax=ad;
}

void upd(int now){
	tr[now].mmax=tr[tr[now].ls].mmax;tr[now].cmax=tr[tr[now].ls].cmax;
	update(tr[now],tr[tr[now].rs].mmax);
	update(tr[now],tr[tr[now].rs].cmax);
	tr[now].ans=tr[now].mmax.second+tr[now].cmax.second;
}

void add_tag(int now,long long t){//不用更新cmax,因为cmax必不存在
	tr[now].tag+=t;
	tr[now].mmax.second+=t;
	tr[now].ans+=t;
}

void psd(int now){
	if(tr[now].tag){
		add_tag(tr[now].ls,tr[now].tag);
		add_tag(tr[now].rs,tr[now].tag);
		tr[now].tag=0;
	}
}

void gi(int&now,vector<pii>&S,int l,int r){
	now=++T;
	if(l==r){
		tr[now].mmax=S[l];
		tr[now].ans=S[l].second;
		tr[now].cmax=make_pair(0,0);
		return ;	
	}
	int mid=(l+r)/2;
	gi(tr[now].ls,S,l,mid);
	gi(tr[now].rs,S,mid+1,r);
	upd(now);
}

void add(int now,int x,int y,long long t,int l,int r){
	if(x==l && y==r){add_tag(now,t);return ;}
	psd(now);
	int mid=(l+r)/2;
	if(y<=mid) add(tr[now].ls,x,y,t,l,mid);
	else if(mid<x) add(tr[now].rs,x,y,t,mid+1,r);
	else add(tr[now].ls,x,mid,t,l,mid),add(tr[now].rs,mid+1,y,t,mid+1,r);
	upd(now);
}

void gp(int x,int fa,long long dep,vector<pii>&S,int&dfn){
	int now=++dfn;S[now]=make_pair(pa,dep);F[ppa][now]=fa;mp[ppa][x]=now;sz++;
	for(int i=first[x];i!=0;i=s[i].nex) if(!tf[s[i].y] && s[i].y!=fa)
		gp(s[i].y,x,dep+s[i].c,S,dfn);
	R[ppa][now]=dfn;
}

void fdrt(int x,int fa){
	tot[x]=1;son[x]=0;
	for(int i=first[x];i!=0;i=s[i].nex) if(!tf[s[i].y] && s[i].y!=fa){
		fdrt(s[i].y,x);
		tot[x]+=tot[s[i].y];
		if(tot[s[i].y]>tot[son[x]]) son[x]=s[i].y;
	}
	if(max(tot[son[x]],sz-tot[x])<max(tot[son[root]],sz-tot[root])) root=x;
}

void build(int x,int ff){
	root=0;fdrt(x,0);x=root;
	vector<pii> S;
	fa[x]=ff;dep[x]=dep[ff]+1;tf[x]=true;siz[x]=sz;
	R[x].resize(sz+1);F[x].resize(sz+1);S.resize(sz+1);
	R[x].clear();F[x].clear();S.clear();mp[x].clear();
	R[x][1]=sz;F[x][1]=0;S[1]=make_pair(x,0);mp[x][x]=1;
	int dfn=1;ppa=x;
	for(int i=first[x];i!=0;i=s[i].nex) if(!tf[s[i].y]){
		sz=0;pa=s[i].y;ppa=x;
		gp(s[i].y,x,s[i].c,S,dfn);build(s[i].y,x);
	}
	gi(rt[x],S,1,siz[x]);
	ANS.insert(tr[rt[x]].ans);
}

long long chg(int op,long long c){
	int x=s[op].y,y=s[op-1].y,p=x,q=y,now;
	if(dep[y]<dep[x]) swap(x,y);
	while(dep[y]>dep[x]) y=fa[y];
	while(x!=y) x=fa[x],y=fa[y];
	now=x;x=p;y=q;
	while(now){
		int dfn=mp[now][x];
		if(F[now][dfn]!=y) swap(x,y),dfn=mp[now][x];
		it=ANS.lower_bound(tr[rt[now]].ans);ANS.erase(it);
		add(rt[now],dfn,R[now][dfn],c-s[op].c,1,siz[now]);
		ANS.insert(tr[rt[now]].ans);
		now=fa[now];
	}
	s[op].c=c;
	it=ANS.end();it--;
	return *it;
}

int main(){
	scanf("%d %d %lld",&n,&q,&w);
	int x,y;
	long long c;
	for(int i=1;i<n;i++) 
		scanf("%d %d %lld",&x,&y,&c),ins(x,y,c),ins(y,x,c);
	sz=n;build(1,0);
	long long las=0;
	while(q--){
		scanf("%d %lld",&x,&c);
		x=(x+las)%(n-1)+1,c=(c+las)%w;
		printf("%lld\n",las=chg(x*2,c));
	}
}
```

---

## 作者：wangyibo201026 (赞：3)

## 更新说明

Update 2022.8.8，被 [Ztemily](https://www.luogu.com.cn/user/352961) 指出 pushup 有错误，改正，现已在 codeforces 上 AC。

## 题意

动态维护树上直径问题。

## 思路

最简单的做法是直接用欧拉序奇怪的性质来求解。

因为有修改，所以我们很容易想到用数据结构来维护。

### 什么是欧拉序

欧拉序的简单定义是：当 dfs 时，到达 $x$ 时记录一下编号，回溯到达 $x$ 时再记一下编号，到达叶子节点时要记录两个。

我们可以发现一些有用的性质：

- 由于每一条边只有递归向下与回溯两种情况经过，还需朝根节点贡献一次，所以欧拉序最多只有 $2 \times n - 1$ 从个数。

- 我们设 $in_x$ 为 $x$ 节点最早出现在欧拉序当中的位置，$out_x$ 为 $x$ 节点最晚出现在欧拉序当中的位置。则 $in_x$ 到 $out_x$ 这一段区间一定是以 $x$ **为根的子树**，从定义中就可以知道。

我们只需要知道这两点，就可以来做题了。

### 关于直径

我们知道，一条直径一定是由一个深度最深的点，到达深度最浅的点，再到达深度第二浅的点。

那么我们的修改操作可以这么思考（设直径两端点为 $x, y$，$d = lca(x, y)$。）：

- 修改：利用线段树维护 $dep$。

- 查询：答案为 $dep_x + dep_y - 2 \times dep_d$，我们考虑将它拆成 $(dep_x - 2 \times dep_d) + dep_y$。

我们可以维护一堆值：

- $maxd_x$，维护区间深度最大值。

- $mind_x$，维护区间深度最小值。

- $lm_x$，维护区间当 $dep_x > dep_y$，$dep_x - 2 \times dep_y$。

- $mr_x$，同理。

- $lmr_x$，代表直径长度，具体维护可见以上。

有了这几个东西，我们就可以发现答案就是 $lmr_1$ 了。

这里给一下 pushup 函数：

```cpp
void pushup(int node){
  maxd[node] = max(maxd[node << 1], maxd[node << 1 | 1]);
  mind[node] = min(mind[node << 1], mind[node << 1 | 1]);
  lm[node] = max(max(lm[node << 1], lm[node << 1 | 1]), maxd[node << 1] - mind[node << 1 | 1] * 2);
  mr[node] = max(max(mr[node << 1], mr[node << 1 | 1]), maxd[node << 1 | 1] - mind[node << 1] * 2);
  lmr[node] = max(max(lmr[node << 1], lmr[node << 1 | 1]), max(lm[node << 1] + maxd[node << 1 | 1], maxd[node << 1] + mr[node << 1 | 1]));
}
```

## 代码

Code：

```cpp
#include<bits/stdc++.h>

#define endl '\n'
#define int long long

using namespace std;

const int N = 2e5 + 5;
const int M = 8e5 + 5;

int n, q, w;
int W[N], dep[N];

int id[N], cnt, in[N], out[N], mp[N], tid[N];

// Graph | Start
int head[N], tot;

struct Graph{
  int to, w, next;
}edges[N * 2];

void add(int u, int v, int w, int i){
  tot++;
  edges[tot].to = v;
  edges[tot].w = w;
  edges[tot].next = head[u];
  mp[tot] = i;
  head[u] = tot;
}
// Graph | End

// Segment tree | Start
int maxd[M], mind[M], lm[M], mr[M], lmr[M], tag[M];

void pushup(int node){
  maxd[node] = max(maxd[node << 1], maxd[node << 1 | 1]);
  mind[node] = min(mind[node << 1], mind[node << 1 | 1]);
  lm[node] = max(max(lm[node << 1], lm[node << 1 | 1]), maxd[node << 1] - mind[node << 1 | 1] * 2);
  mr[node] = max(max(mr[node << 1], mr[node << 1 | 1]), maxd[node << 1 | 1] - mind[node << 1] * 2);
  lmr[node] = max(max(lmr[node << 1], lmr[node << 1 | 1]), max(lm[node << 1] + maxd[node << 1 | 1], maxd[node << 1] + mr[node << 1 | 1]));
}

void addtag(int node, int val){
  maxd[node] += val;
  mind[node] += val;
  lm[node] -= val;
  mr[node] -= val;
  tag[node] += val;
}

void pushdown(int node){
  if(!tag[node]){
    return ;
  }
  addtag(node << 1, tag[node]);
  addtag(node << 1 | 1, tag[node]);
  tag[node] = 0;
}

void build(int node, int lt, int rt){
  if(lt == rt){
    addtag(node, dep[id[lt]]);
    return ;
  }
  int mid = lt + rt >> 1;
  build(node << 1, lt, mid);
  build(node << 1 | 1, mid + 1, rt);
  pushup(node);
}

void update(int node, int lt, int rt, int x, int y, int val){
  if(y < lt || x > rt){
    return ;
  }
  if(x <= lt && rt <= y){
    addtag(node, val);
    return ;
  }
  pushdown(node);
  int mid = lt + rt >> 1;
  update(node << 1, lt, mid, x, y, val);
  update(node << 1 | 1, mid + 1, rt, x, y, val);
  pushup(node);
}
// Segment tree | End

void dfs(int x, int fa){
  id[++cnt] = x;
  in[x] = cnt;
  for(int i = head[x]; i; i = edges[i].next){
    if(edges[i].to != fa){
      dep[edges[i].to] = dep[x] + edges[i].w;
      tid[mp[i]] = edges[i].to;
      dfs(edges[i].to, x);
      id[++cnt] = x;
    }
  }
  out[x] = cnt;
}

void Solve(){
  cin >> n >> q >> w;
  for(int i = 1; i < n; i++){
    int u, v, w;
    cin >> u >> v >> w;
    add(u, v, w, i);
    add(v, u, w, i);
    W[i] = w;
  }
  dfs(1, 0);
  build(1, 1, cnt);
  int lastans = 0;
  for(int i = 1; i <= q; i++){
    int x, val;
    cin >> x >> val;
    x = (x + lastans) % (n - 1) + 1;
    val = (val + lastans) % w;
    update(1, 1, cnt, in[tid[x]], out[tid[x]], val - W[x]);
    W[x] = val;
    lastans = lmr[1];
    cout << lastans << endl;
  }
}

signed main(){
#ifdef debug
  freopen("Code.in", "r", stdin);
  freopen("Code.out", "w", stdout);
#endif
  Solve();
  return 0;
}
```

---

## 作者：zzw4257 (赞：3)

>支持动态(强制在线)修改一棵树的边权求每个时刻的直径

提供一个**括号序列映射树上路径的方法**

首先说明一下看清题意，本题树的形态是定的，改的是边权，因此```一个LCT维护动态直径的方法是不可行的```因为那样我们其实需要可删除$LCT$(仔细品这句话意思，不是$Cut$),那样其实可以线段树分治，但要离线

首先解决一个更简单的问题:边权是$1$时

求出一棵树的$dfs$序，$st_i$位置标$($，$ed_i$位置标$)$

有一些神奇的结论

原树括号序任何一个连续子段两两匹配后剩余的括号按相对顺序拼接的结果(一定是唯一且确定的)表示一条路径，路径长为剩余的括号个数

因此问题实际上转成定义$'('=1,')'=-1$转成$0/1$序列后，一个连续子串的划分使得后面减前面最大

这个问题可以通过维护八个标记得到

$lmx,rmx,lmi,rmi,ld,rd,lrd,ans$前缀/后缀的最大/最小和，前缀右减左最大，后缀右减左最大，两端点必须选满右减左最大，任意子串右减左最大

```cpp
void pushup(int x){
	sum[x]=sum[ls(x)]+sum[rs(x)]; 
	lmx[x]=max(lmx[ls(x)],sum[ls(x)]+lmx[rs(x)]); 
	rmx[x]=max(rmx[rs(x)],sum[rs(x)]+rmx[ls(x)]);
	lmi[x]=min(lmi[ls(x)],sum[ls(x)]+lmi[rs(x)]);
	rmi[x]=min(rmi[rs(x)],sum[rs(x)]+rmi[ls(x)]);
	ld[x]=max(ld[ls(x)],max(ld[rs(x)]-sum[ls(x)],lrd[ls(x)]+lmx[rs(x)])); 
	rd[x]=max(rd[rs(x)],max(sum[rs(x)]+rd[ls(x)],lrd[rs(x)]-rmi[ls(x)]));
	lrd[x]=max(lrd[ls(x)]+sum[rs(x)],lrd[rs(x)]-sum[ls(x)]);
	ans[x]=max(max(ans[ls(x)],ans[rs(x)]),max(ld[rs(x)]-rmi[ls(x)],rd[ls(x)]+lmx[rs(x)])); 
}
```

完整的

```cpp
#include<bits/stdc++.h>
#define ls(a) ((a)<<1)
#define rs(a) ((a)<<1|1)
#define N 200001
#define int long long
using namespace std;
typedef long long ll;
#define G if(++ip==ie)if(fread(ip=ibuf,1,LL,stdin))
const int LL=1<<19;
char ibuf[LL],*ie=ibuf+LL,*ip=ie-1;
inline char nc(void){G;return *ip;}
//#define getchar nc
inline ll read(void){
	char opt;ll flag=1,res=0;
	while((opt=getchar())<'0'||opt>'9')if(opt=='-')flag=-1;
	while(opt>='0'&&opt<='9'){res=(res<<3)+(res<<1)+opt-'0';opt=getchar();}
	return res*flag;
}
int n,m,st[N],top,q;
struct edge{int to;ll v;int x;};vector<edge>g[N];
ll w,sum[N<<2],lmx[N<<2],rmx[N<<2],lmi[N<<2],rmi[N<<2],ld[N<<2],rd[N<<2],lrd[N<<2],ans[N<<2],lastans,p[N][2];
void pushup(int x){
	sum[x]=sum[ls(x)]+sum[rs(x)]; 
	lmx[x]=max(lmx[ls(x)],sum[ls(x)]+lmx[rs(x)]); 
	rmx[x]=max(rmx[rs(x)],sum[rs(x)]+rmx[ls(x)]);
	lmi[x]=min(lmi[ls(x)],sum[ls(x)]+lmi[rs(x)]);
	rmi[x]=min(rmi[rs(x)],sum[rs(x)]+rmi[ls(x)]);
	ld[x]=max(ld[ls(x)],max(ld[rs(x)]-sum[ls(x)],lrd[ls(x)]+lmx[rs(x)])); 
	rd[x]=max(rd[rs(x)],max(sum[rs(x)]+rd[ls(x)],lrd[rs(x)]-rmi[ls(x)]));
	lrd[x]=max(lrd[ls(x)]+sum[rs(x)],lrd[rs(x)]-sum[ls(x)]);
	ans[x]=max(max(ans[ls(x)],ans[rs(x)]),max(ld[rs(x)]-rmi[ls(x)],rd[ls(x)]+lmx[rs(x)])); 
}
inline void Build(int pos,int l,int r){
	ll v;if(l==r)return sum[pos]=(v=st[l]),lmx[pos]=rmx[pos]=max(v,0ll),lmi[pos]=rmi[pos]=min(v,0ll),ld[pos]=rd[pos]=lrd[pos]=ans[pos]=v,void();
	int mid=(l+r)>>1;
	Build(ls(pos),l,mid),Build(rs(pos),mid+1,r);
	pushup(pos);
}
inline void Change(int pos,int l,int r,int x,ll v){
	if(l==r)return sum[pos]=v,lmx[pos]=rmx[pos]=max(v,0ll),lmi[pos]=rmi[pos]=min(v,0ll),ld[pos]=rd[pos]=lrd[pos]=ans[pos]=v,void();
	int mid=(l+r)>>1;
	(x<=mid)?Change(ls(pos),l,mid,x,v):Change(rs(pos),mid+1,r,x,v);
	pushup(pos);
}
inline void dfs(int x,int prt){
	int y;for(auto t:g[x])if((y=t.to)^prt)st[*p[t.x]=++top]=t.v,dfs(y,x),st[p[t.x][1]=++top]=-t.v;
}
signed main(void){
	int i,x;ll y,z;n=read(),q=read(),w=read();
	for(i=1;i<n;++i)x=read(),y=read(),z=read(),g[x].push_back({y,z,i}),g[y].push_back({x,z,i});
	dfs(1,0);Build(1,1,top);
	while(q--){
		x=(read()+lastans)%(n-1)+1,y=(read()+lastans)%w;
		Change(1,1,top,*p[x],y),Change(1,1,top,p[x][1],-y);
		printf("%lld\n",lastans=ans[1]);
	}
    return 0;
}
```

---

## 作者：极寒神冰 (赞：2)

蒟蒻来一发支持加边删边的LCT题解。

LCT的辅助树维护树内维护的是一条链，考虑维护这条**实链**上的最浅和最深的节点到**当前子树内**的最远距离。由于轻边实际上是父亲与这棵Splay上深度最小的点连的边，设$lmx[i]$表示$i$这棵**Splay子树**内深度最小的点往下的最大深度。当然因为Splay需要支持翻转操作，我们还需要维护这棵Splay上深度最大的点往下的最大深度rmx，当将Splay翻转过来时直接$swap(lmx,rmx)$即可。

接下来考虑lmx和rmx如何转移。以lmx的转移为例。

先考虑实链的转移

有
$$
lmx[x]=\max(lmx[x],lmx[son[x][0]])
$$
即直接从原树的祖先转移下来。

以及
$$
lmx[x]=\max(lmx[x],lmx[son[x][1]]+sum[son[x][0]]+len[x])
$$
即保留子树的答案再加上祖先和自身这条边的距离。

再考虑虚子树的转移。由于实链上深度最小的点实际上也是原树上子树的根节点。所以$lmx[x]$也可以表示为**子树内深度最小的节点**到子树内一点最远距离，那么有
$$
lmx[x]=\max(lmx[x],Chain.Fir+sum[son[x][0]]+len[x])
$$
即从虚儿子中深度最大的节点转移即可，这可以使用一个可删堆或者multiset来维护。

rmx同理。

接下来考虑$mxd[i]$最长链的转移。

仍然先考虑实链的转移有
$$
mxd[x]=\max(mxd[x],rmx[son[x][0]]+lmx[son[x][1]]+len[x])
$$
即祖先深度最大的点到子树深度最小的点以及自身这条边的距离。

以及
$$
mxd[x]=\max(mxd[x],mxd[son[x][0]],mxd[son[x][1]])
$$
即祖先和子树本来就有的最长链

再考虑虚子树的转移

最长链有可能是虚子树中本来就有的一条最长链，这同样也可以使用可删堆或者multiset维护。
$$
mxd[x]=\max(mxd[x],Path.Fir)
$$
当然也有可能是两条虚子树的链和自身这条边拼起来的，所以还有：
$$
mxd[x]=\max(mxd[x],Chain.Fir+Chain.Sec+len[x])
$$
最后附上代码

```cpp
const int N=4e5+10;
int lmx[N],rmx[N],mxd[N];
int fa[N],len[N],tag[N],son[N][2];
int sum[N];
int n,m,MXW,ans,lst_ans;
vector<int>e[N];
struct inandelheap
{
	priority_queue<int>whl,del;
	inline void ist(int x){if(x!=-inf)whl.push(x);}
	inline void era(int x){if(x!=-inf)del.push(x);}
	inline int Top(){
		while(1)
		{
			if(whl.empty()) return -inf;
			if(del.empty()) return whl.top();
			if(whl.top()==del.top()) whl.pop(),del.pop();
			else return whl.top();
		}
	}
	inline int Sec() {
		int tmp=Top();era(tmp);
		int tmp2=Top();ist(tmp);
		return tmp2;
	}
}chain[N],path[N];
inline void INS(int u,int v) {chain[u].ist(lmx[v]),path[u].ist(mxd[v]);}
inline void ERA(int u,int v) {chain[u].era(lmx[v]),path[u].era(mxd[v]);}
inline int get(int x) {return x==son[fa[x]][1];}	
inline int isnotroot(int x) {return son[fa[x]][0]==x||son[fa[x]][1]==x;}
inline void push_up(int x)
{
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+len[x];
	int oth=max(0ll,chain[x].Top());
	int up=max(oth,rmx[son[x][0]])+len[x];
	int dwn=max(oth,lmx[son[x][1]])+len[x];
	lmx[x]=max(lmx[son[x][0]],sum[son[x][0]]+dwn);
	rmx[x]=max(rmx[son[x][1]],sum[son[x][1]]+up);
	mxd[x]=max(lmx[son[x][1]]+up,rmx[son[x][0]]+dwn);
	mxd[x]=max(mxd[x],max(mxd[son[x][0]],mxd[son[x][1]]));
	mxd[x]=max(mxd[x],path[x].Top());
	mxd[x]=max(mxd[x],oth+max(0ll,chain[x].Sec())+len[x]);
}

inline void rotate(int x){
	int f=fa[x],gf=fa[f],wh=get(x);
	if(isnotroot(f)) son[gf][get(f)]=x;
	son[f][wh]=son[x][wh^1];
	fa[son[x][wh^1]]=f;
	son[x][wh^1]=f;
	fa[f]=x;
	fa[x]=gf;
	push_up(f);
	push_up(x);
}

inline void splay(int x)
{
	for(int f;f=fa[x],isnotroot(x);rotate(x))
		if(isnotroot(f)) rotate(get(x)==get(f)?f:x);
}
inline int access(int x)
{
	int y;
	for(y=0;x;y=x,x=fa[x]) {splay(x);if(y)ERA(x,y);if(son[x][1])INS(x,son[x][1]);son[x][1]=y,push_up(x);}
	return y;
}
void dfs1(int u) 
{
	for(int v:e[u]) if(v^fa[u])
	{
		fa[v]=u;
		dfs1(v);
		INS(u,v);
	}
	push_up(u);
}

inline void modify(int u,int d)
{	
	access(u);
	splay(u);
	len[u]=d;
	push_up(u);
	ans=mxd[u];
}

signed main()
{
	n=read(),m=read(),MXW=read();
	int u,v,d;
	R(i,1,n-1)
	{
		u=read(),v=read(),d=read();
		e[u].pb(i+n),e[i+n].pb(u);
		e[v].pb(i+n),e[i+n].pb(v);
		len[i+n]=d;
	}
	dfs1(1);
	while(m--)
	{
		u=read(),d=read();
		u=(u+lst_ans)%(n-1)+1;
		d=(d+lst_ans)%MXW;
		//printf("u:%lld val:%lld\n",u,d);
		modify(u+n,d);
		writeln(lst_ans=ans);
	}
}
```




---

## 作者：luogu_gza (赞：1)

懒人默认 $nq$ 同阶。

题目描述极其简单，但是题目非常的难。

首先我们考虑一个性质：有点集 $A$ 与 $B$，设其直径分别为 $(a,b)$ 和 $(c,d)$，则其合并后的直径 $(s,t)$ 满足 $s,t \in \{a,b,c,d\}$。

我们利用线段树维护点集来解决问题，每次的合并明显是 $O(\log n)$ 的，因此我们用 $O(n \log^2 n)$ 解决了这个问题（无修改）。

那么带修改呢？树剖，将距离刻画为 $dis_x+dis_y-2dis_{\operatorname{lca}(x,y)}$，我们维护 $dis$ 就会发现其实修改边权等价于子树加，容易用 BIT 解决。

考虑一下哪些 segtree 上的节点的最大直径被改变了，注意到子树内和子树外的最大直径不会变化，只需要处理一半在子树内，一半在子树外的就行了。（这部分表述参考了第一篇题解，也是本题最为重要的观察）

总结：树剖，使用 segtree 维护直径，使用 BIT 维护 dis，每次修改只处理一半在子树内，一半在子树外的就行了。

这里我采用树剖处理了 lca，并且很多实现细节参考了第一篇题解（主要是边权的处理方面），可以说我是 ctj 了！

另注：为了方便改一些东西，我们使用邻接表。

这是 $O(n \log^2 n)$ 的做法，代码如下：

```cpp
// Problem: P6845 [CEOI2019] Dynamic Diameter
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6845
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
namespace gza{
	#define int long long
	#define pb push_back
	#define MT int TTT=R;while(TTT--)
	#define pc putchar
	#define R read()
	#define fo(i,a,b) for(int i=a;i<=b;i++)
	#define rep(i,a,b) for(int i=a;i>=b;i--)
	#define m1(a,b) memset(a,b,sizeof a)
	namespace IO
	{
		inline int read()
		{
		    int x=0;
		    char ch=getchar();
		    bool f=0;
		    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
		    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
		    if(f) x=-x;
		    return x;    
		}
		template<typename T> inline void write(T x)
		{
		    if(x<0) pc('-'),x=-x;
		    if(x>9) write(x/10);
		    pc(x%10+'0');
		}
	};
	using namespace IO;
	
	const int N=1e5+10,M=2e5+10;
	int n,q,W;
	int h[N],w[M],e[M],ne[M],idx=1;
	int dis[N],go[N];
	void add()
	{
		int a=R,b=R;
		idx++,e[idx]=b,ne[idx]=h[a],h[a]=idx;
		idx++,e[idx]=a,ne[idx]=h[b],h[b]=idx;
		w[idx>>1]=R;
	}
	int dep[N],siz[N],fa[N],son[N],top[N],dfn[N],id[N],cnt;
	void dfs1(int u,int f)
	{
		fa[u]=f,dep[u]=dep[f]+1,siz[u]=1;
		for(int i=h[u];i;i=ne[i])
		{
			int j=e[i];
			if(j!=f)
			{
				dis[j]=dis[u]+w[i>>1],go[i>>1]=j;
				dfs1(j,u);
				if(siz[j]>siz[son[u]]) son[u]=j;
				siz[u]+=siz[j];
			}
		}
	}
	void dfs2(int u,int f)
	{
		top[u]=f,dfn[u]=++cnt,id[cnt]=u;
		if(!son[u]) return;
		dfs2(son[u],f);
		for(int i=h[u];i;i=ne[i])
		{
			int j=e[i];
			if(j!=fa[u]&&j!=son[u]) dfs2(j,j);
		}
	}
	int lca(int a,int b)
	{
		while(top[a]!=top[b])
		{
			if(dep[top[a]]<dep[top[b]]) swap(a,b);
			a=fa[top[a]];
		}
		if(dep[a]>dep[b]) swap(a,b);
		return a;
	}
	#define now tr[u]
	#define ls tr[u<<1]
	#define rs tr[u<<1|1]
	#define PII pair<int,int>
	namespace finwick_tree{
		int tr[N];
		void update(int x,int c)
		{
			for(;x<=n;x+=(x&-x)) tr[x]+=c;
		}
		int query(int x)
		{
			int res=dis[id[x]];
			for(;x;x-=(x&-x)) res+=tr[x];
			return res;
		}
		void update(int x,int y,int w)
		{
			update(x,w),update(y+1,-w);
		}
	}
	int Dis(PII a)
	{
		return finwick_tree::query(dfn[a.first])+finwick_tree::query(dfn[a.second])-2*finwick_tree::query(dfn[lca(a.first,a.second)]);
	}
	namespace segtree{
		PII tr[N<<2];
		PII merge(const PII& a,const PII& b)
		{
			pair<int,int> p[6]={a,b,{a.first,b.first},{a.first,b.second},{a.second,b.first},{a.second,b.second}};
			int dis[6];
			fo(i,0,5) dis[i]=Dis(p[i]);
			return p[max_element(dis,dis+6)-dis];
		}
		void build(int u,int l,int r)
		{
			if(l==r) tr[u]={id[l],id[r]};
			else
			{
				int mid=l+r>>1;
				build(u<<1,l,mid),build(u<<1|1,mid+1,r);
				now=merge(ls,rs);
			}
		}
		void update(int u,int nl,int nr,int l,int r)
		{
			if(nl==l&&nr==r) return;
			int mid=nl+nr>>1;
			if(r<=mid) update(u<<1,nl,mid,l,r);
			else if(l>mid) update(u<<1|1,mid+1,nr,l,r);
			else update(u<<1,nl,mid,l,mid),update(u<<1|1,mid+1,nr,mid+1,r);
			now=merge(ls,rs);
		}
	}
	void main(){
		n=R,q=R,W=R;
		fo(i,2,n) add();
		dfs1(1,0),dfs2(1,1);
		segtree::build(1,1,n);
		int last=0;
		while(q--)
		{
			int e=(R+last)%(n-1)+1;
			int v=(R+last)%W;
			finwick_tree::update(dfn[go[e]],dfn[go[e]]+siz[go[e]]-1,v-w[e]),w[e]=v;
			segtree::update(1,1,n,dfn[go[e]],dfn[go[e]]+siz[go[e]]-1);
			write(last=Dis(segtree::tr[1])),puts("");
		}
	}
}
signed main(){
	gza::main();
}
```

---

## 作者：forgotmyhandle (赞：1)

[CF 传送门](http://codeforces.com/problemset/problem/1192/B)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1192B)

21 篇题解的题解区清一色的欧拉序线段树，为数不多的几篇动态 dp 要么 LCT 要么 toptree，我真不好评价。~~我们重剖线段树到底怎么你了~~

## 分析

考虑动态 dp。先把边权下放到点权，设 $f[i][0 / 1]$ 表示 $i$ 子树内（包括 $i$ 向上的边）的直径和还能向上延伸的最长链。重剖一下，设 $g[i][0 / 1]$ 表示 $i$ 子树内（包括 $i$ 向上的边）除重儿子之外的直径和还能向上延伸的最长链。根据 $g$ 的转移方程，需要开两个 set 维护所有轻儿子的两个 $f$ 值。$g$ 对重儿子 $f$ 值转移到当前点 $f$ 值的贡献可以使用矩阵刻画。这个矩阵可以根据转移方程列一下，应当是好列的。

接下来考虑修改。首先对于一个点，如果知道其所有轻儿子的 dp 值，则可以根据当前点权算出其 $g$ 值，进而构造出当前点的转移矩阵。也就是修改一个点权实际上是修改了它的矩阵。这个矩阵更改后会直接影响到其所在链顶的 dp 值，所以这个链顶的 dp 值必须重新计算。由于链顶是轻儿子，而轻儿子的 dp 值变动会导致其父亲的转移矩阵变化，所以还需要重新计算链顶父亲的转移矩阵。然后依次类推，直到更新到根为止。重新计算某个点 dp 值的方法很简单，由于链底必为叶子，直接用这个叶子的初始矩阵按顺序乘上链上所有点的转移矩阵即可。线段树维护转移矩阵，需要注意矩阵乘法的方向。

## 代码

```cpp
#include <iostream>
#include <set>
#define int long long
using namespace std;
const int inf = 4000000000000000000;
int n, q, W;
int head[100005], nxt[200005], to[200005], ew[200005], ecnt;
void add(int u, int v, int ww) { to[++ecnt] = v, nxt[ecnt] = head[u], head[u] = ecnt, ew[ecnt] = ww; }
int down[100005], _dfn[100005], son[100005], top[100005], dfn[100005], dep[100005], sz[100005], fa[100005], w[100005], ncnt;
int eu[100005], ev[100005];
int f[100005][2];
multiset<int, greater<int> > st[100005][2];
struct Matrix {
    int a[3][3];
    int* operator[](int x) { return a[x]; }
    Matrix() { a[0][0] = a[0][1] = a[0][2] = a[1][0] = a[1][1] = a[1][2] = a[2][0] = a[2][1] = a[2][2] = -inf; }
} A[100005], T[400005], E;
Matrix operator*(Matrix a, Matrix b) {
    Matrix c;
    c[0][0] = max(a[0][0] + b[0][0], max(a[0][1] + b[1][0], a[0][2] + b[2][0]));
    c[0][1] = max(a[0][0] + b[0][1], max(a[0][1] + b[1][1], a[0][2] + b[2][1]));
    c[0][2] = max(a[0][0] + b[0][2], max(a[0][1] + b[1][2], a[0][2] + b[2][2]));
    c[1][0] = max(a[1][0] + b[0][0], max(a[1][1] + b[1][0], a[1][2] + b[2][0]));
    c[1][1] = max(a[1][0] + b[0][1], max(a[1][1] + b[1][1], a[1][2] + b[2][1]));
    c[1][2] = max(a[1][0] + b[0][2], max(a[1][1] + b[1][2], a[1][2] + b[2][2]));
    c[2][0] = max(a[2][0] + b[0][0], max(a[2][1] + b[1][0], a[2][2] + b[2][0]));
    c[2][1] = max(a[2][0] + b[0][1], max(a[2][1] + b[1][1], a[2][2] + b[2][1]));
    c[2][2] = max(a[2][0] + b[0][2], max(a[2][1] + b[1][2], a[2][2] + b[2][2]));
    return c;
}
Matrix Construct(int x) {
    if (!son[x]) 
        return E;
    int g0, g1 = *st[x][1].begin();
    if (sz[son[x]] + 1 == sz[x]) 
        g0 = *st[x][0].begin();
    else {
        int tmp = *st[x][1].begin();
        st[x][1].erase(st[x][1].begin());
        g0 = max(*st[x][0].begin(), tmp + *st[x][1].begin());
        st[x][1].insert(tmp);
    }
    g1 += w[x];
    Matrix ret;
    ret[0][0] = ret[2][2] = 0;
    ret[1][0] = g1 - w[x];
    ret[2][1] = g1;
    ret[2][0] = g0;
    ret[1][1] = w[x];
    return ret;
}
void dfs1(int x, int fa, int d) {
    dep[x] = d;
    ::fa[x] = fa;
    sz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) {
            w[v] = ew[i];
            dfs1(v, x, d + 1);
            sz[x] += sz[v];
            if (sz[v] > sz[son[x]]) 
                son[x] = v;
        }
    }
}
void dfs2(int x, int t) {
    top[x] = t;
    _dfn[dfn[x] = ++ncnt] = x;
    if (!son[x]) {
        down[t] = x;
        return;
    }
    dfs2(son[x], t);
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa[x] && v != son[x]) 
            dfs2(v, v);
    }
}
void dfs3(int x) {
    f[x][1] = w[x];
    for (int i = head[x]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa[x]) {
            dfs3(v);
            f[x][0] = max(f[x][0], max(f[v][0], f[x][1] - w[x] + f[v][1]));
            f[x][1] = max(f[x][1], f[v][1] + w[x]);
            if (v != son[x]) {
                st[x][0].insert(f[v][0]);
                st[x][1].insert(f[v][1]);
            }
        }
    }
    if (son[x])
        A[dfn[x]] = Construct(x);
    else 
        A[dfn[x]] = E;
}
struct Segment_Tree {
    void Build(int o, int l, int r) {
        if (l == r) {
            T[o] = A[l];
            return;
        }
        int mid = (l + r) >> 1;
        Build(o << 1, l, mid);
        Build(o << 1 | 1, mid + 1, r);
        T[o] = T[o << 1 | 1] * T[o << 1];
    }
    void Change(int o, int l, int r, int x) {
        if (l == r) {
            T[o] = A[l];
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid) 
            Change(o << 1, l, mid, x);
        else 
            Change(o << 1 | 1, mid + 1, r, x);
        T[o] = T[o << 1 | 1] * T[o << 1];
    }
    Matrix Query(int o, int l, int r, int L, int R) {
        if (L > R) 
            return E;
        if (L <= l && r <= R) 
            return T[o];
        int mid = (l + r) >> 1;
        if (R <= mid) 
            return Query(o << 1, l, mid, L, R);
        if (L > mid) 
            return Query(o << 1 | 1, mid + 1, r, L, R);
        return  Query(o << 1 | 1, mid + 1, r, L, R) * Query(o << 1, l, mid, L, R);
    }
} seg;
void Change(int x) {
    if (son[x]) {
        A[dfn[x]] = Construct(x);
        seg.Change(1, 1, n, dfn[x]);
    }
    Matrix I;
    while (1) {
        int tmp = down[top[x]];
        I[0][0] = I[0][2] = 0, I[0][1] = w[tmp];
        I = I * seg.Query(1, 1, n, dfn[top[x]], dfn[tmp] - 1);
        x = top[x];
        int tmp0 = f[x][0], tmp1 = f[x][1];
        f[x][0] = I[0][0], f[x][1] = I[0][1];
        if (x == 1) 
            break;
        st[fa[x]][0].erase(st[fa[x]][0].find(tmp0));
        st[fa[x]][1].erase(st[fa[x]][1].find(tmp1));
        st[fa[x]][0].insert(f[x][0]);
        st[fa[x]][1].insert(f[x][1]);
        x = fa[x];
        A[dfn[x]] = Construct(x);
        seg.Change(1, 1, n, dfn[x]);
    }
}
signed main() {
    E[0][0] = E[1][1] = E[2][2] = 0;
    cin >> n >> q >> W;
    for (int i = 1; i < n; i++) {
        int ww;
        int &u = eu[i], &v = ev[i];
        cin >> u >> v >> ww;
        add(u, v, ww);
        add(v, u, ww);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    dfs3(1);
    seg.Build(1, 1, n);
    int lans = 0;
    while (q--) {
        int d, ww;
        cin >> d >> ww;
        d = (d + lans) % (n - 1) + 1;
        ww = (ww + lans) % W;
        if (dep[eu[d]] < dep[ev[d]]) {
            w[ev[d]] = ww;
            Change(ev[d]);
        } else {
            w[eu[d]] = ww;
            Change(eu[d]);
        }
        cout << (lans = max(f[1][1], f[1][0])) << "\n";
    }
    return 0;
}

---

## 作者：lfxxx (赞：1)

来个无脑点的单 $\log n$ 做法。

直接对原树建出静态 Top tree 随后对每个簇 $u$ 记录下 $ans,maxdis_{0/1},dis$ 分别表示簇内直径与簇内非界点到界点的最长路径与两个界点间的距离，那么当我们将簇合并时就可以快速合并路径并维护新的 $maxdis_{0/1}$，最后求出直径。

修改就现在被修改的边代表的簇上修改 $dis$ 然后顺着 Top tree 一路向上爬即可。

总时间复杂度是 $O(n + q \log n)$ 的。

```cpp
#include<bits/stdc++.h>
#define int long long
//#define lowbit(x) (x&(-x))
using namespace std;
const int maxn = 2e5+114;
const int inf = 2e18+114;
struct node{
	int u,v,ans,maxu,maxv,id,dis;//簇内答案（不包括界点） 到界定的距离最大的白点的距离
	char type;
	//u 在上面 v 在下面
}cluster[maxn];
int n,m,w;
int fa[maxn],ls[maxn],rs[maxn];
char type[maxn];//P 是边点 C 是 compress 点 R 是 rake 点
int root=1;//根簇
void compress(node x,node y,node &w){
	//x 在上面 y 在下面
	w.ans=w.maxu=w.maxv=-inf;
	w.u=x.u,w.v=y.v;
	w.dis=x.dis+y.dis;
	w.ans=max(x.ans,y.ans);
	w.ans=max(w.ans,x.maxv+y.maxu);
    w.maxu=max(x.maxu,y.maxu+x.dis);
    w.maxv=max(x.maxv+y.dis,y.maxv);
    w.ans=max(w.ans,max(x.maxv,y.maxu));
    w.ans=max(w.ans,0*1ll);
    w.maxu=max(w.maxu,x.dis);
    w.maxv=max(w.maxv,y.dis);
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	w.type='C';
	root=w.id;
}
void rake(node x,node y,node &w){
	//把 x rake 到 y 上
	w.ans=w.maxu=w.maxv=-inf;
	w.u=y.u,w.v=y.v;
	w.dis=y.dis;
	w.ans=max(x.ans,y.ans);
	w.ans=max(w.ans,x.maxu+y.maxu);
    w.maxu=max(x.maxu,y.maxu);
    w.maxv=max(x.maxu+y.dis,y.maxv);
    w.ans=max(w.ans,max(x.maxv,y.maxu+x.dis));
    w.ans=max(w.ans,0*1ll);
    w.maxu=max(w.maxu,x.dis);
    w.maxv=max(w.maxv,x.dis+y.dis);
	fa[x.id]=fa[y.id]=w.id;
	ls[w.id]=x.id;
	rs[w.id]=y.id;
	w.type='R';
	root=w.id;
}
void update(int u){
    if(u==0) return ;
    if(cluster[u].type=='C'){
        compress(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }else{
        rake(cluster[ls[u]],cluster[rs[u]],cluster[u]);
        update(fa[u]);
    }
}
vector< pair<int,int> > E[maxn];
int father_pos[maxn];//一个点到其父亲的边的簇编号
int father[maxn];
int son[maxn],sz[maxn],tot;
vector<int> st[maxn];//重链上的点存到链顶
map<int,int> pos[maxn];
void dfs1(int u){
	sz[u]=1;
	for(pair<int,int> nxt:E[u]){
	    int v=nxt.first,w=nxt.second;
		if(v==father[u]) continue;
		father[v]=u;
		father_pos[v]=++tot;
        pos[u][v]=pos[v][u]=tot;
		cluster[tot].u=u,cluster[tot].v=v,cluster[tot].id=tot,cluster[tot].dis=w,cluster[tot].ans=cluster[tot].maxu=cluster[tot].maxv=-inf;
		dfs1(v);
		if(sz[v]>sz[son[u]]) son[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tp){
	st[tp].push_back(u);
	if(son[u]!=0) dfs2(son[u],tp);
	for(pair<int,int> nxt:E[u]){
	    int v=nxt.first;
		if(v==father[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
//需要虚拟节点 n+1 作为根 只在第一次 dfs 以及最后根簇时调用
vector<int> vec[maxn];
vector<int> pre[maxn];
int solve(int l,int r,int u){
    if(l>r) return 0;
	if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=solve(l,mid,u);
	int rson=solve(mid+1,r,u);
	int res=++tot;
	cluster[tot].id=tot;
	rake(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
int calc(int l,int r,int u){
    if(l>r) return 0;
    if(l==r) return father_pos[vec[u][l]];
	int L=l,R=r;
	while(L+1<R){
		int mid=(L+R)>>1;
		if((pre[u][mid]-pre[u][l-1])*2<=(pre[u][r]-pre[u][l-1])) L=mid;
		else R=mid;
	}
	int mid=L;
	int lson=calc(l,mid,u);
	int rson=calc(mid+1,r,u);
	int res=++tot;
    cluster[tot].id=tot;
	compress(cluster[lson],cluster[rson],cluster[res]);
	return res;
}
void dfs3(int u){
	for(int x:st[u]){
        if(son[x]==0) continue;
		pre[x].push_back(0);
		vec[x].push_back(0);
		for(pair<int,int> nxt:E[x]){
		    int v=nxt.first;
			if(v!=son[x]&&v!=father[x]){
				dfs3(v);
				//收缩 (x,v) 一个簇
				vec[x].push_back(v);
			}
		}
		//在对这些轻儿子簇按中点分治的方法合并起来
		for(int i=1;i<=vec[x].size()-1;i++){
			pre[x].push_back(pre[x][i-1]+sz[vec[x][i]]);
		}
		int rt=solve(1,vec[x].size()-1,x);
		if(rt!=0){
		    tot++;
		    cluster[tot].id=tot;
            rake(cluster[rt],cluster[father_pos[son[x]]],cluster[tot]);
            father_pos[son[x]]=tot;//rake 到重链上		    
		}
	}
	vec[u].clear();
	pre[u].clear();
	pre[u].push_back(0);
	vec[u].push_back(0);
	for(int x:st[u]){
		vec[u].push_back(x);
	}
	for(int i=1;i<=vec[u].size()-1;i++){
		pre[u].push_back(pre[u][i-1]+sz[vec[u][i]]-sz[son[vec[u][i]]]);
	}
	if(u!=1) father_pos[u]=calc(1,vec[u].size()-1,u);//把重链上的边 compress 成一条
	else father_pos[u]=calc(2,vec[u].size()-1,u);
	E[u].clear();
	E[u].push_back(make_pair(father[u],0));
	return ;
}
int lstans;
pair<int,int> edge[maxn];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>w;
    for(int i=2;i<=n;i++){
        int u,v,c;
        cin>>u>>v>>c;
        E[u].push_back(make_pair(v,c));
        E[v].push_back(make_pair(u,c));
        edge[i-2].first=u,edge[i-2].second=v;
    }
    dfs1(1);
    dfs2(1,1);
    dfs3(1);
    while(m--){
        int d,e;
        cin>>d>>e;
        d=(d+lstans)%(n-1);
        e=(e+lstans)%w;
        //cout<<d<<' '<<e<<'\n';
        int u=pos[edge[d].first][edge[d].second];
        cluster[u].dis=e;
        update(fa[u]);
        cout<<(lstans=max(cluster[root].dis,(max(max(cluster[root].ans,cluster[root].maxu),cluster[root].maxv))))<<'\n';
    }
	return 0;
}
```

---

## 作者：happybob (赞：1)

马上省选了不会欧拉序，来补补。

首先看到动态维护直径比较容易想到的肯定还是 LCT。常见套路是两个连通块合并后的两直径端点必然是原来两个连通块 $4$ 个直径端点中的其二。证明显然。新直径要么是原来两个连通块直径，要么经过这条新的边。又一个点到树上最远距离的点一定是直径端点之一，结论必然成立。

于是我们容易搞出 LCT 的只加边维护直径的方法，删除可以离线套线段树分治变成 $2 \log$，但是这题强制在线。所以用 LCT 似乎要 DDP。然而这东西难写难调，考虑一个容易点的做法。

下面提供两个做法。

## 做法 $1$

考虑还是用上面这个套路，令根为 $1$ 号节点，用线段树维护 DFS 序，每个区间维护下这段 DFS 的直径端点。合并的时候分类讨论几种，取路径 $\max$。现在难点在于边权修改。考虑修改一条边对线段树的影响。显然只有经过这条边的路径才会受到边权的改变。令这条边中深度更大的那个为 $u$，以 $u$ 为根的子树对应 DFS 区间为 $[id_u,id_u+sz_u-1]$。线段树上只有和这个区间有交但不被这个区间完全包含的区间才会进行更改。事实上这些区间就是我们进行区间查询这个区间找到的所有最后没有直接返回的区间。这个区间量级显然是 $O(\log n)$ 的。然后进行修改，每次只对这些区间修改并往上合并，就做到了 $O(n \log^2 n)$。口胡的，没写代码。

## 做法 $2$

考虑不用上面的合并套路。直径的本质是什么？如果以一个点（比如 $1$ 号点）为根，那么直径就是 $\max \limits_{1\leq i, j\leq n} (d_i+d_j-2\times d_{\operatorname{LCA}(i,j)}) $，也就是任意两点路径的最大值。

考虑欧拉序，即进行深度优先搜索，到达一个点或者从其儿子回溯到这个点，都将其加到序列后面。最终形成一个长度为 $2n-1$ 的序列，设点 $u$ 第一次出现位置 $fir_u$，最后一次出现位置 $lst_u$。容易知道 $u,v$ 的最近公共祖先是 $[fir_u,fir_v]$ 中深度最小的点。于是我们知道直径就是 $\max \limits_{i \leq j \leq k} (d_i+d_k-2 \times d_j)$。用线段树维护序列并且对每个区间记录 $d$ 的最大最小值以及 $d_i-2\times d_j$ 对于 $i \leq j$ 和 $i \geq j$ 分别的最大值即可容易的合并区间。修改边权转成区间加，即对于 $[fir_u,lst_u]$ 区间加，上述标记都可以 $O(1)$ 更新。复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <functional>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <queue>
using namespace std;

using ll = long long;
const int N = 2e5 + 5;

int n, q;
ll maxw;
ll lastans;
ll dis[N], nd[N];
array<int, N> dep;
vector<pair<int, ll>> G[N];
array<int, N> euler;

array<int, N> U, V;
array<ll, N> W;
int idx;
array<int, N> fir, lst;

class SegmentTree
{
public:
	struct Node
	{
		int l, r;
		ll tag, minn, maxn, res;
		ll r1, r2;
		friend Node operator+(const Node& a, const Node& b)
		{
			if (a.l == -1) return b;
			if (b.l == -1) return a;
			Node c;
			c.l = a.l, c.r = b.r;
			c.tag = 0ll;
			c.minn = min(a.minn, b.minn);
			c.maxn = max(a.maxn, b.maxn);
			c.res = max({ a.res, b.res, a.r2 + b.maxn, a.maxn + b.r1 });
			c.r1 = max({ a.r1, b.r1, b.maxn - 2ll * a.minn });
			c.r2 = max({ a.r2, b.r2, a.maxn - 2ll * b.minn });
			return c;
		}
	}tr[N << 2];
	void pushtag(int u, ll v)
	{
		tr[u].tag += v;
		tr[u].maxn += v;
		tr[u].minn += v;
		tr[u].r1 -= v;
		tr[u].r2 -= v;
	}
	function<void(int)> pushdown = [&](int u)
		{
			if (tr[u].tag)
			{
				pushtag(u << 1, tr[u].tag);
				pushtag(u << 1 | 1, tr[u].tag);
				tr[u].tag = 0;
			}
		};
	function<void(int, int, int, ll*)> build = [&](int u, int l, int r, ll* v)
		{
			tr[u] = { l, r, 0ll, v[r], v[r], 0ll, -v[r], -v[r] };
			if (l == r) return;
			int mid = l + r >> 1;
			build(u << 1, l, mid, v);
			build(u << 1 | 1, mid + 1, r, v);
			tr[u] = tr[u << 1] + tr[u << 1 | 1];
		};
	function<void(int, int, int, ll)> update = [&](int u, int l, int r, ll v)
		{
			if (tr[u].l >= l and tr[u].r <= r)
			{
				pushtag(u, v);
				return;
			}
			pushdown(u);
			int mid = tr[u].l + tr[u].r >> 1;
			if (l <= mid) update(u << 1, l, r, v);
			if (r > mid) update(u << 1 | 1, l, r, v);
			tr[u] = tr[u << 1] + tr[u << 1 | 1];
		};
}sgt;

auto main() -> int
{
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q >> maxw;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w));
		U[i] = u, V[i] = v, W[i] = w;
	}
	auto dfs = [&](auto self, int u, int fa) -> void
		{
			euler[++idx] = u;
			if (!fir[u]) fir[u] = idx;
			lst[u] = idx;
			dep[u] = dep[fa] + 1;
			for (auto& [j, w] : G[u])
			{
				if (j != fa) [[likely]]
					{
						dis[j] = dis[u] + w;
						self(self, j, u);
						euler[++idx] = u;
						lst[u] = idx;
					}
			}
		};
	dfs(dfs, 1, 1);
	for (int i = 1; i <= 2 * n - 1; i++)
	{
		nd[i] = dis[euler[i]];
	}
	sgt.build(1, 1, 2 * n - 1, nd);
	for (int i = 1; i <= q; i++)
	{
		ll d, e;
		cin >> d >> e;
		d = (d + lastans) % (n - 1);
		e = (e + lastans) % maxw;
		d++;
		int u = (dep[U[d]] < dep[V[d]] ? V[d] : U[d]);
		sgt.update(1, fir[u], lst[u], -W[d] + e);
		W[d] = e;
		cout << (lastans = sgt.tr[1].res) << "\n";
	}
	return 0;
}
```


---

## 作者：escapist404 (赞：1)

# Solution to CF1192B Dynamic Diameter

## Statement

给你一棵有 $n$ 个结点的树，边带权。

$q$ 次操作，每次修改一个边权，修改完后求树的直径。

保证 $2\le n\le 10^5$，$1\le q\le 10^5$，$1\le w\le 2\times 10^{13}$，$1\le a_i,b_i\le n$，$0\le c_i,e_j<w$，$0\le d_j<n-1$。

**本题强制在线**。

## Solution

前置知识：欧拉序，线段树。

对一棵树我们定义 $d_u$ 表示结点 $u$ 到根节点的距离。

考虑直径的定义即

$$
\max{\{d_u + d_v - 2 \cdot d_{\mathrm{lca}(u, v)}\}}, u \in T, v \in T
$$

每次修改一条边的边权 $w \gets w'$，必定影响这条边所连子树上的点的信息，效果是 $d_u \gets d_u + w' - w$。

因此考虑将 $d_i$ 拍到欧拉序上维护。

由欧拉序的性质，发现 $\mathrm{lca}(u, v)$ 至少会在 $u, v$ 之间出现一次，且 $\mathrm{lca}(u, v)$ 对应的 $d$ 是 $u, v$ 所在区间最小的。

所以设 $s$ 为欧拉序 $e$ 的长度，令序列 $a_i=d_{e_i}$，答案就是

$$
\max_{l=1}^{s} \max_{r=l}^{s}{\{a_l + a_r - 2 \cdot \min_{i=l}^{r} {a_i}\}}
$$

考虑怎么维护这个式子，就叫它直径 $d$ 吧。

想象一下我们有一个区间 $\mathbf{x} = [l, r)$，它有儿子们 $\mathbf{ls} = [l, m)$ 和 $\mathbf{rs} = [m, r)$。分类一下：

* $a_l$ 和 $\min_{i=l}^{r} {a_i}$ 出现在 $[l, m)$，$a_r$ 出现在 $[m, r)$。
* $a_l$ 出现在 $[l, m)$，$a_r$ 和 $\min_{i=l}^{r} {a_i}$ 出现在 $[m, r)$。

那我们对每一个区间设两个式子

$$
\mathrm{poly}(l) = \max_{i=l}^{r} \{a_i - 2 \cdot \min_{j=i}^{r} a_j\}
$$
$$
\mathrm{poly}(r) = \max_{i=r}^{l} \{a_i - 2 \cdot \min_{j=i}^{l} a_j\}
$$

含义分别是某个区间，选了一个 $a_i$ 后在 $a_i$ 的右边（$\mathrm{poly}(l)$）或左边（$\mathrm{poly}(r)$）选择最小值，整个式子的最大值。有了这个东西我们就能够维护 $d$

$$
d_{\mathbf{x}} =
\max\begin{cases}
d_{\mathbf{ls}}\\
d_{\mathbf{rs}}\\
\mathrm{poly}(l)_{\mathbf{ls}} + \mathrm{max}_{\mathbf{rs}}\\
\mathrm{max}_{\mathbf{ls}} + \mathrm{poly}(r)_{\mathrm{rs}}
\end{cases}
$$

怎么维护 $\mathrm{poly}(l)$ 和 $\mathrm{poly}(r)$？

不难看出我们在左儿子选一个最大值，在右儿子选一个最小值，加上原来两个区间的值就能维护 $\mathrm{poly}(l)$ 了，对于 $\mathrm{poly}(r)$ 同理。

$$
\mathrm{poly}(l)_{\mathbf{x}} =
\max\begin{cases}
\mathrm{poly}(l)_{\mathbf{ls}}\\
\mathrm{poly}(l)_{\mathbf{rs}}\\
\mathrm{max}_{\mathbf{ls}} + \mathrm{min}_{\mathbf{rs}}
\end{cases}
$$

$$
\mathrm{poly}(r)_{\mathbf{x}} =
\max\begin{cases}
\mathrm{poly}(r)_{\mathbf{ls}}\\
\mathrm{poly}(r)_{\mathbf{rs}}\\
\mathrm{min}_{\mathbf{ls}} + \mathrm{max}_{\mathbf{rs}}
\end{cases}
$$

最后维护 $\max$ 和 $\min$，我们就能维护出一个 $d$ 来。

修改呢？在欧拉序上做做文章，我们把当前要修改的边，所连的较深结点的子树进行一个区间修改即可。

设边权变化量为 $k$ 的话，这里 $\max \gets \max + \space k$，$\min \gets \min + \space k$，$\mathrm{poly}(l) \gets \mathrm{poly}(l) - \space k$，$\mathrm{poly}(r) \gets \mathrm{poly}(r) - \space k$（加上 $k$ 减去 $2k$），$d$ 没有变化（不涉及对子树内部边权的修改）。

做完了！时间复杂度 $\mathcal{O}(q \log n)$。

## Code

代码中 `dmt` 代表 $d$，`lpoly` 代表 $\mathrm{poly}(l)$，`rpoly` 同理。

代码中大多数的下标是从零开始的。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

const int _Size = 16;

class io_r {
private:
	static char buf[];
	static int p;
	FILE* f;

public:
	inline void flush() { fread(buf, sizeof(char), 1 << _Size, f), p = 0; }
	inline io_r& operator>>(char& ch) {
		if (p == (1 << _Size)) flush();
		ch = buf[p++];
		return *this;
	}
	template <typename T>
	inline io_r& operator>>(T& x) {
		x = 0;
		short w = 1;
		char ch = 0;
		do w = ch == '-' ? -1 : w, *this >> ch;
		while (ch < '0' || ch > '9');
		do x = (x << 3) + (x << 1) + ch - '0', *this >> ch;
		while ('0' <= ch && ch <= '9');
		x *= w;
		return *this;
	}
	io_r() : f(stdin) {}
	io_r(const char* Filename, const char* Mode = "r") : f(fopen(Filename, Mode)) {
		if (!f) std::perror("File Opening Failed.");
	}
	io_r(FILE* f) : f(f) {}
};

class io_w {
private:
	static char buf[];
	static int p;
	FILE* f;

public:
	inline void flush() { fwrite(buf, p, 1, f), p = 0; }
	inline io_w& operator<<(const char c) {
		if (p == (1 << _Size)) flush();
		buf[p++] = c;
		return *this;
	}
	inline io_w& operator<<(const char* c) {
		int len = strlen(c);
		for (int i = 0; i < len; ++i) *this << c[i];
		return *this;
	}
	template <typename T>
	inline io_w& operator<<(T x) {
		if (x < 0) *this << '-', x = -x;
		static int s[50], d = 0;
		do s[++d] = x % 10, x /= 10;
		while (x);
		do *this << (char)(s[d--] + '0');
		while (d);
		return *this;
	}
	~io_w() { flush(); }
	io_w() : f(stdout) {}
	io_w(const char* Filename, const char* Mode = "w") : f(fopen(Filename, Mode)) {}
	io_w(FILE* f) : f(f) {}
};

char io_r::buf[1 << _Size];
int io_r::p = 0;
char io_w::buf[1 << _Size];
int io_w::p = 0;

// quick_io above

using i64 = long long;

struct Node {
public:
	i64 dmt, min, max, lpoly, rpoly, tag;
	Node(const i64 dmt = i64(), const i64 min = i64(), const i64 max = i64(),
		 const i64 lpoly = i64(), const i64 rpoly = i64(), const i64 tag = i64())
		: dmt(dmt), min(min), max(max), lpoly(lpoly), rpoly(rpoly), tag(tag) {}
	inline Node& operator<<(const i64 _tag) {
		return *this = Node(dmt, min + _tag, max + _tag, lpoly - _tag, rpoly - _tag, tag + _tag);
	}
};
inline Node operator+(const Node ls, const Node rs) {
	return Node(std::max({ls.dmt, rs.dmt, ls.lpoly + rs.max, ls.max + rs.rpoly}),
				std::min(ls.min, rs.min), std::max(ls.max, rs.max),
				std::max({ls.lpoly, rs.lpoly, ls.max - 2ll * rs.min}),
				std::max({ls.rpoly, rs.rpoly, rs.max - 2ll * ls.min}), i64());
}

class SegmentTree {
private:
	std::vector<i64> a;
	std::vector<Node> p;
	size_t n;
	inline size_t ls(const size_t x) { return (x << 1) + 1; }
	inline size_t rs(const size_t x) { return (x << 1) + 2; }
	inline void push_down(const size_t x) {
		p[ls(x)] << p[x].tag;
		p[rs(x)] << p[x].tag;
		p[x].tag = i64();
	}
	void build(const size_t l, const size_t r, const size_t x = 0) {
		if (r - l == 1) return p[x] << a[l], void();
		size_t mid = ((l + r) >> 1);
		build(l, mid, ls(x));
		build(mid, r, rs(x));
		p[x] = p[ls(x)] + p[rs(x)];
	}

public:
	void modify(const size_t ql, const size_t qr, const i64 k, const size_t l, const size_t r,
				const size_t x) {
		if (ql <= l && r <= qr) return p[x] << k, void();
		push_down(x);
		size_t mid = ((l + r) >> 1);
		if (ql < mid) modify(ql, qr, k, l, mid, ls(x));
		if (qr > mid) modify(ql, qr, k, mid, r, rs(x));
		p[x] = p[ls(x)] + p[rs(x)];
	}
	Node query() { return p.front(); }
	size_t size() { return a.size(); }

	SegmentTree(std::vector<i64> a) : a(a), p(a.size() << 2), n(a.size()) { build(0, n, 0); }
};

// segment tree

class Tree {
private:
	struct Edge {
		int to, nxt;
		i64 weight;
		Edge(const int to, const int nxt, const i64 weight) : to(to), nxt(nxt), weight(weight) {}
	};
	struct Edge_t {
		int father, son;
		i64 weight;
		Edge_t(const int father = int(), const int son = int(), const i64 weight = i64())
			: father(father), son(son), weight(weight) {}
	};

	int n;

	std::vector<Edge> ed;
	std::vector<int> head;
	std::vector<i64> dep;

public:
	inline void add_edge(int u, int v, i64 w) {
		ed.push_back(Edge(v, head[u], w));
		head[u] = (int)ed.size() - 1;
	}

	std::vector<Edge_t> ed_t;
	std::vector<int> euler, lbound, rbound;

	void dfs_build_euler_order(int x, int f, i64 d) {
		lbound[x] = euler.size();
		euler.push_back(x);
		dep[x] = d;
		for (int i = head[x]; ~i; i = ed[i].nxt) {
			int to = ed[i].to;
			i64 weight = ed[i].weight;
			if (to == f) continue;

			Edge_t& cur = ed_t[i >> 1];
			cur.father = x;
			cur.son = to;
			cur.weight = weight;

			dfs_build_euler_order(to, x, d + weight);
			euler.push_back(x);
		}
		rbound[x] = euler.size();
	}

	std::vector<i64> generate_dep_by_euler_order() {
		std::vector<i64> dep_t;
		for (int i : euler) {
			dep_t.push_back(dep[i]);
		}
		dep_t.pop_back();
		return dep_t;
	}

	Tree(int n) : n(n), head(n + 1, -1), dep(n + 1), ed_t(n - 1), lbound(n + 1), rbound(n + 1) {}
};

// euler order

io_r qin;
io_w qout;

int main() {
	int n, q;
	i64 w;
	qin >> n >> q >> w;

	Tree T(n);

	for (int i = 1; i < n; ++i) {
		int u, v;
		i64 w;
		qin >> u >> v >> w;
		T.add_edge(u, v, w);
		T.add_edge(v, u, w);
	}

	T.dfs_build_euler_order(1, 0, i64());

	SegmentTree S(T.generate_dep_by_euler_order());

	i64 last_ans = 0;
	while (q--) {
		int d;
		i64 e;
		qin >> d >> e;

		d = (d + last_ans) % (n - 1);
		e = (e + last_ans) % w;

		auto& cur = T.ed_t[d];
		S.modify(T.lbound[cur.son], T.rbound[cur.son], e - cur.weight, 0, S.size(), 0);
		qout << (last_ans = S.query().dmt) << '\n';
		cur.weight = e;
	}
	return 0;
}

```


---

## 作者：Mihari (赞：1)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF1192B)

# 题解

题目交代了是“动态直径”，肯定是在线啦，问题在于我们选用什么数据结构维护，以及怎么维护.

在树上，考虑使用树剖进行维护，但是，在线段树上如何维护一个区间？对于一颗线段树上的区间，它的直径的两个端点必然来源于它的子区间的两条直径的端点，我们只需要用四次枚举每种情况即可.

考虑修改的时候怎么维护线段树，首先，对于一条边 $e$ 被修改，假设它连接的深度较深的点为 $u$，那么，在 $u$ 的子树中的直径没有受到影响，唯一有影响的是**跨越**了 $u$ 的点的直径，在线段树上来说，就是包含了 `dfn[u]` 以及 `dfn[u]+sz[u]-1` 两个端点的区间需要重新计算，一次修改的计算是 $\mathcal O(\log^2n)$，总复杂度 $\mathcal O(n\log^2n)$.

代码中对于单点的深度使用的是 `BIT` 利用差分维护的，或许这样常数更小.

# 代码

```cpp
# include <cstdio>
# include <algorithm>
using namespace std;
namespace Elaina{
    # define rep(i,l,r) for(int i=l, i##_end_ = r; i <= i##_end_; ++ i)
    # define fep(i,l,r) for(int i=l, i##_end_ = r; i >= i##_end_; -- i)
    # define fi first
    # define se second
    # define Endl putchar('\n')
    # define writc(x, c) fwrit(x), putchar(c)
    // # define int long long
    typedef long long ll;
    typedef pair<int, int> pii;
    typedef unsigned long long ull;
    typedef unsigned int uint;
    template<class T>inline T Max(const T x, const T y){return x < y ? y : x;}
    template<class T>inline T Min(const T x, const T y){return x < y ? x : y;}
    template<class T>inline T fab(const T x){return x < 0 ? -x : x;}
    template<class T>inline void getMax(T& x, const T y){x = Max(x, y);}
    template<class T>inline void getMin(T& x, const T y){x = Min(x, y);}
    template<class T>T gcd(const T x, const T y){return y ? gcd(y, x % y) : x;}
    template<class T>inline T readin(T x){
        x=0; int f = 0; char c;
        while((c = getchar()) < '0' || '9' < c) if(c == '-') f = 1;
        for(x = (c ^ 48); '0' <= (c = getchar()) && c <= '9'; x = (x << 1) + (x << 3) + (c ^ 48));
        return f ? -x : x;
    }
    template<class T>void fwrit(const T x){
        if(x < 0)return putchar('-'), fwrit(-x);
        if(x > 9)fwrit(x / 10); putchar(x % 10 ^ 48);
    }
}
using namespace Elaina;

const int maxn = 1e5;
const ll inf = (1ll << 50);

int n, q; ll w;

struct edge{int to, nxt; ll w;
    edge(const int T = 0, const int N = 0, const ll W = 0) : to(T), nxt(N), w(W){}
}e[maxn * 2 + 5];
int ecnt = 1;// pay attention!
int tail[maxn + 5];
inline void add_edge(const int u, const int v, const ll w){
    e[++ ecnt] = edge(v, tail[u], w); tail[u] = ecnt;
    e[++ ecnt] = edge(u, tail[v], w); tail[v] = ecnt;
}

inline void init(){
    n = readin(1), q = readin(1); w = readin(1ll);
    int a, b; ll c;
    rep(i, 1, n - 1){
        a = readin(1), b = readin(1), c = readin(1ll);
        add_edge(a, b, c);
    }
}

ll dis[maxn + 5];
int sz[maxn + 5], wson[maxn + 5], dep[maxn + 5], fa[maxn + 5];
void dfs1(const int u, const int par){
    sz[u] = 1, dep[u] = dep[par] + 1, fa[u] = par;
    for(int i = tail[u], v; i; i = e[i].nxt)
        if((v = e[i].to) != par){
        dis[v] = dis[u] + e[i].w;
        dfs1(v, u), sz[u] += sz[v];
        if(sz[v] > sz[wson[u]]) wson[u] = v;
    }
}
int c[maxn + 5], dfn[maxn + 5], tp[maxn + 5], times;
void dfs2(const int u, const int par){
    c[dfn[u] = ++ times] = u;
    if(!wson[u]) return;
    tp[wson[u]] = tp[u], dfs2(wson[u], u);
    for(int i = tail[u], v; i; i = e[i].nxt)
        if((v = e[i].to) != par && v != wson[u])
            dfs2(tp[v] = v, u);
}

inline int findlca(int u, int v){
    while(tp[u] != tp[v]){
        // printf("Now u == %d, v == %d\n", u, v);
        if(dep[tp[u]] < dep[tp[v]]) swap(u, v);
        u = fa[tp[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

inline int lowbit(const int i){return i & (-i);}
/** @brief maintain the distance of the nodes*/
struct BIT{
    ll c[maxn + 5];
    inline void modify(int i, const ll x){
        for(; i <= n; i += lowbit(i))
            c[i] += x;
    }
    inline void modify(const int l, const int r, const ll x){
        modify(l, x), modify(r + 1, -x);
    }
    inline ll query(int i){
        ll ret = 0;
        for(; i > 0; i -= lowbit(i)) ret += c[i];
        return ret;
    }
}bit;

inline ll query_dis(const int u, const int v){
    // printf("query_dis :> u == %d, v == %d\n", u, v);
    if(u == 0 || v == 0) return -inf;
    int lca = findlca(u, v);
    return bit.query(dfn[u]) + bit.query(dfn[v]) - 2 * bit.query(dfn[lca]);
}

struct diameter{
    int c[2]; ll d;
    inline diameter operator &(const diameter rhs) const{
        diameter ret;
        if(d < rhs.d) ret = rhs;
        else ret = (*this);
        rep(i, 0, 1) rep(j, 0, 1){
            int x = c[i], y = rhs.c[j];
            ll dis;
            if((dis = query_dis(x, y)) > ret.d){
                ret.d = dis;
                ret.c[0] = x, ret.c[1] = y;
            }
        }
        return ret;
    }
};

/** @brief maintain the particular interval's diameter*/
diameter tre[maxn << 2 | 2];
# define ls (i << 1)
# define rs (i << 1 | 1)
# define mid ((l + r) >> 1)
# define _lq ls, l, mid
# define _rq rs, mid + 1, r
inline void pushup(const int i){
    tre[i] = tre[ls] & tre[rs];
}
void Build(const int i = 1, const int l = 1, const int r = n){
    if(l == r){
        tre[i].c[0] = c[l];
        tre[i].d = -inf;
        return;
    }
    Build(_lq), Build(_rq);
    pushup(i);
}
void Modify(const int L, const int R, const int i = 1, const int l = 1, const int r = n){
    if(L <= l && r <= R) return;
    if(L <= mid) Modify(L, R, _lq);
    if(mid < R) Modify(L, R, _rq);
    pushup(i);
}
void print(const int i = 1, const int l = 1, const int r = n){
    if(l != r) print(_lq), print(_rq);
    printf("tre[%d] :> l == %d, r == %d, (%d, %d, %lld)\n", i, l, r, tre[i].c[0], tre[i].c[1], tre[i].d);
}

signed main(){
    init();
    dfs1(1, 0);
    // puts("finished 1!");
    dfs2(tp[1] = 1, 0);
    // puts("finished 2!");
    rep(i, 1, n){
        // 注意此处传的下标
        bit.modify(i, dis[c[i]] - dis[c[i - 1]]);
        // printf("bit[%d].insert %lld\n", i, dis[c[dfn[i]]] - dis[c[dfn[i - 1]]]);
    }
    // puts("finished 3!");
    // rep(i, 1, n){
    //     printf("node %d :> sz == %d, wson == %d, fa == %d, dep == %d, dis == %lld, tp == %d, dfn == %d\n", i, sz[i], wson[i], fa[i], dep[i], dis[i], tp[i], dfn[i]);
    // }
    // rep(i, 1, n) printf("dis %d == %lld\n", i, bit.query(dfn[i]));

    Build();
    // printf("ans 1 == %lld\n", tre[1].d);
    // print();
    // rep(i, 1, n) printf("dis %d == %lld\n", i, bit.query(i));
    ll las = 0, E; int D;
    while(q --){
        D = (0ll + readin(1) + las) % (n - 1) + 1;
        E = (readin(1ll) + las) % w;
        D <<= 1;
        int u = e[D].to;
        if(dep[u] < dep[e[D ^ 1].to])
            u = e[D ^ 1].to;
        // printf("update u == %d\n", u);
        ll delta = E - e[D].w;
        e[D].w = e[D ^ 1].w = E;
        // printf("delta == %lld\n", delta);
        bit.modify(dfn[u], dfn[u] + sz[u] - 1, delta);
        Modify(dfn[u], dfn[u] + sz[u] - 1);
        writc(las = tre[1].d, '\n');
        // rep(i, 1, n) printf("dis %d == %lld\n", i, bit.query(dfn[i]));
        // print();
    }
    return 0;
}
```



---

## 作者：win114514 (赞：0)

### 思路

静态 $\text{top tree}$ 板子题。

#### 定义

我们使用簇来表示树上的一个连通块。

可以按照如下方式定义一个簇：

1. 一个簇可以表示为三元组 $(u,v,E)$，其中 $u,v$ 为树的节点，称为簇的界点，$E$ 为一个边的集合，表示该簇包含的边，路径 $(u,v)$ 称作簇路径。
2. $u,v$ 分别为上界点与下界点，上界点是一个簇内深度最小的点，下界点则是除去上界点外的界点。
3. 界点可以通俗的理解为簇与簇的分界点。
4. 对于树的一条边 $(u,v)$，$(u,v,{(u,v)})$ 是一个簇。
5. 对于簇 $(u,v,E_1)$ 与簇 $(v,w,E_2)$ 且 $E_1\cap E_2=\varnothing$，那么 $(u,w,E_1\cup E_2)$ 也是一个簇，这个操作称为 $\text{compress}$。
6. 对于簇 $(x,v,E_1)$ 与簇 $(x,w,E_2)$ 且 $E_1\cap E_2=\varnothing$，那么 $(x,w,E_1\cup E_2)$ （或者 $(x,v,E_1\cup E_2)$）也是一个簇，这个操作称为 $\text{rake}$。

经典图：

![](https://pic.imgdb.cn/item/66606ae25e6d1bfa05d40934.png)

一个感性理解是 $\text{rake}$ 将簇与簇融合，$\text{compress}$ 将簇与簇拼接。

这两个操作可以帮助我们将整棵树合并为一个簇。

- 对于一度点，进行 $\text{rake}$
- 对于二度点，进行 $\text{compress}$。

![](https://pic.imgdb.cn/item/66606b335e6d1bfa05d469d7.png)

收缩过程中，簇的合并结构形成了一个树，我们把这个树称为 $\text{top tree}$。

现在，这样一个 $\text{top tree}$ 它的树高有可能是 $O(n)$ 的。

#### 更优的树

考虑构造一个树高更小的 $\text{top tree}$。

容易想到的是全局平衡二叉树。

全局平衡二叉树提供了一个分治方案使整棵树的全局平衡二叉树树高为 $O(\log n)$。

我们同样可以把这个分治方案放在 $\text{top tree}$ 上。

具体的，将树进行重链剖分。

然后对于轻儿子，先把它们 $\text{rake}$ 起来。

再对重链分治 $\text{compress}$，找分割点时，我们按每个点合并完轻儿子后的簇的大小带权找到中点。

这样就可以建出一颗树高为 $O(\log n)$ 的 $\text{top tree}$ 了。

#### 关于这道题

建出 $\text{top tree}$ 后有什么用呢。

我们想线段树一样的操作它

对于动态直径。

我们把每一个簇，维护三个值。

簇内部的最长距离及到两个界点的最长距离。

合并时我们对两种操作分类讨论拼接起来即可。

可以发现，维护直径的方式与线段树维护最大子段和的方式是比较类似的。

这种维护方法就可以支持一些简单的修改，比如此题的修改边权。

时间复杂度：$O(n\log n)$。

### Code

```cpp
/*
  ! 如果没有天赋，那就一直重复
  ! Created: 2024/06/05 19:58:38
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)

const int N = 2e5 + 10;

int n, q, w, ct, last, head[N];
int sz[N], sn[N], fa[N], rt[N], dep[N];
struct Node {
  int u, v, w;
} d[N];
struct edge {
  int to, nxt;
} e[N << 1];
struct node {
  enum { UNIT, RAKE, COMP } type;
  int u, v, sz, ls, rs, fa, ln, mi, un, vn;
} t[N << 1];

inline void add(int x, int y) {
  e[++ct] = {y, head[x]}, head[x] = ct;
  e[++ct] = {x, head[y]}, head[y] = ct;
}
inline void dfs(int now, int fa) {
  sz[now] = 1, dep[now] = dep[fa] + 1;
  for (int i = head[now]; i; i = e[i].nxt) {
    int x = e[i].to;
    if (x == fa) continue;
    dfs(x, now);
    t[x] = {node::UNIT, now, x, 1};
    sz[now] += sz[x];
    if (sz[x] > sz[sn[now]]) sn[now] = x;
  }
}
inline void pup(int p) {
  int x = t[p].ls, y = t[p].rs;
  if (t[p].type == node::RAKE) {
    t[p].ln = t[x].ln;
    t[p].mi = max({t[x].mi, t[y].mi, t[x].un + t[y].un});
    t[p].un = max(t[x].un, t[y].un);
    t[p].vn = max(t[x].vn, t[x].ln + t[y].un);
  } else if (t[p].type == node::COMP) {
    t[p].ln = t[x].ln + t[y].ln;
    t[p].mi = max({t[x].mi, t[y].mi, t[x].vn + t[y].un});
    t[p].un = max(t[x].un, t[x].ln + t[y].un);
    t[p].vn = max(t[y].vn, t[y].ln + t[x].vn);
  }
}
inline auto rake(int x, int y) {
  assert(t[x].u == t[y].u);
  return t[++ct] = {node::RAKE, t[x].u, t[x].v, t[x].sz + t[y].sz, x, y}, t[x].fa = t[y].fa = ct, pup(ct), ct;
}
inline auto comp(int x, int y) {
  assert(t[x].v == t[y].u);
  return t[++ct] = {node::COMP, t[x].u, t[y].v, t[x].sz + t[y].sz, x, y}, t[x].fa = t[y].fa = ct, pup(ct), ct;
}
template<typename T, typename Func>
inline int build(T l, T r, Func f) {
  if (r == l) return 0;
  if (r == l + 1) return *l;
  int all = 0, sum = 0;
  for (auto it = l; it != r; it++) all += t[*it].sz;
  T mid = l + 1;
  for (auto it = l; it != r; it++) {
    sum += t[*it].sz;
    if (sum <= all / 2) mid = it + 1; else break;
  }
  return f(build(l, mid, f), build(mid, r, f));
}
inline void sol(int now, int ff, bool f) {
  fa[now] = ff;
  if (sn[now]) sol(sn[now], now, false);
  for (int i = head[now]; i; i = e[i].nxt)
    if (e[i].to != sn[now] && e[i].to != fa[now]) sol(e[i].to, now, true);
  if (f) {
    vector<int> s1;
    if (ff) s1.push_back(now);
    for (int i = sn[now]; i; i = sn[i]) {
      vector<int> s2{i};
      for (int j = head[fa[i]]; j; j = e[j].nxt)
        if (e[j].to != i && e[j].to != fa[fa[i]]) s2.push_back(rt[e[j].to]);
      s1.push_back(build(s2.begin(), s2.end(), rake));
    }
    rt[now] = build(s1.begin(), s1.end(), comp);
  }
}
inline void upd(int x, int w) {
  t[x].un = t[x].vn = t[x].mi = t[x].ln = w;
  while (t[x].fa) {
    pup(t[x].fa), x = t[x].fa;
  }
}

signed main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q >> w;
  fro(i, 1, n - 1) {
    cin >> d[i].u >> d[i].v >> d[i].w;
    add(d[i].u, d[i].v);
  }
  ct = n;
  dfs(1, 0);
  sol(1, 0, 1);
  fro(i, 1, n - 1) {
    if (dep[d[i].u] > dep[d[i].v])
      swap(d[i].u, d[i].v);
    upd(d[i].v, d[i].w);
  }
  fro(i, 1, q) {
    int x, y;
    cin >> x >> y;
    x = (x + last) % (n - 1) + 1;
    y = (y + last) % (w);
    d[x].w = y;
    upd(d[x].v, d[x].w);
    cout << (last = t[rt[1]].mi) << "\n";
  }
  return 0;
}
```

---

## 作者：Star_Cried (赞：0)

## CF1192B Dynamic Diameter

### 题意

一颗带权树，每次更改一条边的权，每次修改后求出最大直径。强制在线。

### 思路

$O(n\log^2n)$ 的暴力做法。

根据经典结论，对于两个点集的树上最大直径（权值非负），并集点集的树上最大直径的端点一定是原四个端点中的两个。

那么我们就可以用线段树维护点集，合并时 $O(\log n)$ 查询两点间距离合并就可以做到 $O(n\log^2n)$ 的复杂度了。

思考如何支持在线修改边权。两点间距离为 $dis(x)+dis(y)-2*dis(lca(x,y))$ 那么先树剖发现修改一条边的权实际上是将子树内 $dis$ 增加，那么子树就是区间加。我们可以用树状数组维护修改。

考虑哪些部分的线段树上的点集最大直径被改了。发现子树内和子树外的最大直径不会变化，那么我们只需要更改子树内与外之间合并的最大直径就行了。我们按照 $dfn$ 用线段树进行维护，那么我们每次只需要将子树区间重新 `pushup` 一下就可以了。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<utility>
using namespace std;
inline long long read(){
	long long x=0;int w=0;char c=getchar();
	while(!isdigit(c)) w|=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=1e5+10;
	int n,q;
	int ecnt=1,head[maxn],to[maxn<<1],nxt[maxn<<1],go[maxn];
	long long W,w[maxn],dis[maxn];
	inline void addedge(){
		int a=read(),b=read();
		to[++ecnt]=b,nxt[ecnt]=head[a],head[a]=ecnt;
		to[++ecnt]=a,nxt[ecnt]=head[b],head[b]=ecnt;
		w[ecnt>>1]=read();
	}
	int dep[maxn],fa[maxn],top[maxn],siz[maxn],son[maxn],dfn[maxn],id[maxn];
	void dfs1(int x,int f){
		fa[x]=f,dep[x]=dep[f]+1,siz[x]=1;
		for(int u,i=head[x];i;i=nxt[i]) if((u=to[i])!=f){
			dis[u]=dis[x]+w[i>>1],dfs1(u,x),go[i>>1]=u;
			if(siz[u]>siz[son[x]]) son[x]=u;
			siz[x]+=siz[u];
		}
	}
	void dfs2(int x,int topf){
		top[x]=topf,dfn[x]=++dfn[0],id[dfn[0]]=x;
		if(!son[x]) return;
		dfs2(son[x],topf);
		for(int u,i=head[x];i;i=nxt[i]) if((u=to[i])!=fa[x] and u!=son[x]) dfs2(u,u);
	}
	inline int LCA(int x,int y){
		while(top[x]!=top[y]) dep[top[x]]>dep[top[y]]?(x=fa[top[x]]):(y=fa[top[y]]);
		return dep[x]<dep[y]?x:y;
	}
	#define ls (ro<<1)
	#define rs (ro<<1|1)
	#define mid ((l+r)>>1)
	namespace S{
		long long c[maxn];
		inline void upd(int x,long long k){for(;x<=n;x+=x&-x) c[x]+=k;}
		inline long long query(int x){long long ans=dis[id[x]];for(;x;x-=x&-x) ans+=c[x];return ans;}
		inline void update(int x,int y,long long w){upd(x,w),upd(y+1,-w);}
	}
	inline long long Dis(pair<int,int> a){return S::query(dfn[a.first])+S::query(dfn[a.second])-2*S::query(dfn[LCA(a.first,a.second)]);}
	namespace T{
		pair<int,int> e[maxn<<2];
		inline pair<int,int> merge(const pair<int,int>& a,const pair<int,int>& b){
			pair<int,int> p[6]={a,b,make_pair(a.first,b.first),make_pair(a.first,b.second),make_pair(a.second,b.first),make_pair(a.second,b.second)};
			long long dis[6];
			for(int i=0;i<6;i++) dis[i]=Dis(p[i]);
			return p[max_element(dis,dis+6)-dis];
		}
		void build(int ro=1,int l=1,int r=n){
			if(l==r) return e[ro]=make_pair(id[l],id[l]),void();
			build(ls,l,mid),build(rs,mid+1,r);
			e[ro]=merge(e[ls],e[rs]);
		}
		void update(int x,int y,int ro=1,int l=1,int r=n){
			if(x==l and y==r) return;
			if(y<=mid) update(x,y,ls,l,mid);
			else if(x>mid) update(x,y,rs,mid+1,r);
			else update(x,mid,ls,l,mid),update(mid+1,y,rs,mid+1,r);
			e[ro]=merge(e[ls],e[rs]);
		}
	}
	#undef ls
	#undef rs
	#undef mid
	inline void work(){
		n=read(),q=read(),W=read();
		for(int i=1;i<n;i++) addedge();	
		dfs1(1,0),dfs2(1,1);
		T::build();
		long long ans=0;
		while(q--){
			int e=(read()+ans)%(n-1)+1;
			long long v=(read()+ans)%W;
			S::update(dfn[go[e]],dfn[go[e]]+siz[go[e]]-1,v-w[e]),w[e]=v;
			T::update(dfn[go[e]],dfn[go[e]]+siz[go[e]]-1);
			printf("%lld\n",ans=Dis(T::e[1]));
		}
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

