# [CEOI 2019] Magic Tree

## 题目描述

有一棵以 $1$ 为根，节点从 $1$ 到 $n$ 编号的树。

在这棵树上有许多果实，第 $j$ 个果实会于第 $d_j$ 天在节点 $v_j$ 成熟，并且在收获后可获得 $w_j$ 的果汁。

第 $j$ 个果实仅能在第 $d_j$ 天收获。

收获的方式是断掉这棵树的一条边，这会获得在这条边上作为儿子的那个点的子树上的当天成熟的果实的果汁。

您要求出最多可以获得多少果汁。

## 说明/提示

#### 样例解释
最优方案如下：
- 在第四天，断掉 $(4,5)$ 和 $(1,2)$，获得第一个和第三个果实，获得的果汁数量累计为 $6$。
- 在第七天，虽然我们有一个果实成熟，但是我们最好什么都不干。
- 在第九天，断掉 $(1,4)$，获得最后一个果实，获得的果汁数量累计为 $9$。
#### 数据范围
对于 $100\%$ 的数据，保证 $2\le n\le 10^5$，$1\le m\le n-1$，$1\le k\le 10^5$，$1\le p_i\le i-1$，$2\le v_j\le n$，$1\le d_j\le k$，$1\le w_j\le 10^9$，$v_j$ 互不相同。

详细子任务限制及分值如下表：

| 子任务编号 | 限制 | 分值 |
| :-: |:-:|:-:|
| 1 | $n,k\le 20$ 且 $w_j=1$ | $6$ | 
| 2 | $v_j\in $ 叶子节点 | $3$ | 
| 3 | 图是一条链且 $w_j=1$ | $11$ | 
| 4 | $k\le 2$ | $12$ | 
| 5 | $k\le 20$ 且 $w_j=1$ | $16$ | 
| 6 | $m\le 10^3$ | $13$ | 
| 7 | $w_j=1$ | $22$ | 
| 8 | 无特殊性质 | $17$ | 
#### 说明
本题译自 [Central-European Olympiad in Informatics 2019](https://ceoi.sk/) [Day 2](https://ceoi.sk/tasks/) [T2 Magic Tree](https://ceoi.sk/static/statements/magictree-ENG.pdf)。

## 样例 #1

### 输入

```
6 4 10
1
2
1
4
4
3 4 5
4 7 2
5 4 1
6 9 3
```

### 输出

```
9
```

# 题解

## 作者：_LPF_ (赞：17)

提供一种别样的线段树合并写法。

# $\mathcal Magic$

[魔法树](https://www.luogu.com.cn/problem/P6847)

> 给定一棵 $n$ 个节点的树，有些节点上有果实，有值 $d,w$，分别表示果实成熟的日期和价值。
>
> 如果恰好在日期当天切掉该节点与根的连通，那么就能得到该价值。求能得到的价值的最大值。

转化一下题意，在树上选择一些点，使得所有被选择的点对 $(u,v)$，若 $v$ 在以 $u$ 为根的子树中，那么有 $d(v)\leq d(u)$。

考虑最朴素的树形 DP，设 $f(u,i)$ 表示以 $u$ 为根的子树，所有切断操作都在 $\leq i$ 天内完成的最大价值。

那么对于 $u$ 的一个儿子 $v$，它的贡献有：

1. 不考虑加入 $u$ 点的价值：$f(u,i)=\sum f(v,i)$。
2. 考虑加入 $u$ 点的价值：$f(u,j)=w(u)+\sum f(v,d(u))$，其中 $j\geq d(u)$。

因为两者是互斥关系，所以需要取个 $\max$。

这样就得到了 $O(nk)$ 的暴力算法，考虑使用数据结构优化它，不难想到线段树合并。

对于转移一可以直接合并，打上个区间加标价即可，对于二相当于是区间 $[d(u),k]$ 对那个值取 $\max$。

然后提供一个小 trick，不考虑使用普通线段树的区间赋值标记（比较难合并），而是记录下区间 $\min,\max$。

如果一个区间的 $\min=\max$，那么这个区间所有值相等，这种情况下，

合并时直接被合并，更新时直接删掉左右儿子，修改时添加左右儿子，就相当于有了区间赋值的作用了。

时间复杂度 $O(n\log n)$，若写个空间回收那么空间复杂度同样为 $O(n\log n)$，可以参考下面的写法：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long LL;
const int N = 100010;
const int M = N * 40;

int n, m, k, tot, d[N], w[N], rt[N];
struct Tree{int l, r; LL mx, mn, add;} t[M];
vector<int> bac, G[N];

int read(){
	int x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') f = (c == '-') ? -1 : 1, c = getchar();
	while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
	return x * f;
}

bool Same(int p){return (t[p].mx == t[p].mn);}

int New(){
	if(!bac.empty()){
		int p = bac.back();
		bac.pop_back();
		return p;
	}
	return ++ tot;
}

void Delet(int &x){
	if(!x) return;
	bac.push_back(x);
	t[x].l = t[x].r = 0;
	t[x].mx = t[x].mn = t[x].add = 0;
	x = 0;
}

void Plus(int p, LL v){
	if(!p) return;
	t[p].mx += v;
	t[p].mn += v;
	t[p].add += v;
}

void Push_Down(int p){
	if(!t[p].add) return;
	Plus(t[p].l, t[p].add);
	Plus(t[p].r, t[p].add);
	t[p].add = 0;
}

void Push_Up(int p){
	int l = t[p].l, r = t[p].r;
	t[p].mx = max(t[l].mx, t[r].mx);
	t[p].mn = min(t[l].mn, t[r].mn);
	if(t[p].mn == t[p].mx)
		Delet(t[p].l), Delet(t[p].r);
}

int Merge(int p, int q){
	if(!p || !q) return p + q;
	if(Same(q)){Plus(p, t[q].mx); return p;}
	if(Same(p)){Plus(q, t[p].mx); return q;}
	Push_Down(p), Push_Down(q);
	t[p].l = Merge(t[p].l, t[q].l);
	t[p].r = Merge(t[p].r, t[q].r);
	Push_Up(p);
	return p;
}

LL Query(int p, int l, int r, int k){
	if(Same(p)) return t[p].mx;
	int mid = (l + r) >> 1;
	Push_Down(p);
	if(k <= mid)
		return Query(t[p].l, l, mid, k);
	else
		return Query(t[p].r, mid + 1, r, k);
}

void Modify(int p, int l, int r, int L, int R, LL v){
	if(t[p].mn >= v) return;
	if(L <= l && r <= R && t[p].mx <= v){
		t[p].mx = t[p].mn = v; t[p].add = 0;
		Delet(t[p].l), Delet(t[p].r);
		return;
	}
	Push_Down(p);
	if(Same(p)){
		t[p].l = New(), t[p].r = New();
		int ls = t[p].l, rs = t[p].r;
		t[ls].mx = t[ls].mn = t[rs].mx = t[rs].mn = t[p].mx;
	}
	int mid = (l + r) >> 1;
	if(L <= mid)
		Modify(t[p].l, l, mid, L, R, v);
	if(R > mid)
		Modify(t[p].r, mid + 1, r, L, R, v);
	Push_Up(p);
}

void dfs(int u){
	rt[u] = New();
	for(int i = 0; i < (int) G[u].size(); i ++){
		int v = G[u][i];
		dfs(v);
		rt[u] = Merge(rt[u], rt[v]);
	}
	if(d[u]){
		LL val = Query(rt[u], 1, k, d[u]);
		Modify(rt[u], 1, k, d[u], k, val + w[u]);
	}
}

int main(){
	n = read(), m = read(), k = read();
	for(int v = 2; v <= n; v ++){
		int u = read();
		G[u].push_back(v);
	}
	for(int i = 1; i <= m; i ++){
		int p = read();
		d[p] = read(), w[p] = read();
	}
	dfs(1);
	printf("%lld\n", t[rt[1]].mx);
	return 0;
}
```



---

## 作者：UltiMadow (赞：12)

首先有一个显然的暴力dp

设 $f_{u,t}$ 表示 $t$ 时刻前断掉 $u$ 和 $u$ 的父亲这条边的最大收益

显然有 $f_{u,t}=val(u,t)+\sum\limits_{v\in son(u)} f_{v,t}$，$val(u,t)$ 表示 $t$ 时刻之前断掉 $u$ 和 $u$ 父亲这条边节点 $u$ 的收益

有 $val(u,t)=w_u\times [d_u\le t]$

不难发现 $f_u$ 是单调不降的，并且连续的一段值是相等的，而且拐点不会很多

于是，我们可以用一个 map 存储这些拐点，以及对应的 $f$ 值

对于一个节点 $u$，和它的儿子 $v$，我们只要把 $v$ 的 map 中所有值都加到 $u$ 的 map 中即可

接下来考虑 $u$ 自己的贡献，我们需要对所有 $\ge d_u$ 的 $f$ 都加上 $w_u$，于是就是要进行一个后缀加操作，可以把 map 中维护的东西换成 $f$ 的差分数组（当然如果你直接用线段树维护的话直接区间加就行了）

每次暴力合并 map 显然会超时，于是用启发式合并

时间复杂度 $\mathcal O(n\log n\log k)$

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 100010
#define int long long
#define iter map<int,int>::iterator 
using namespace std;
int n,m,K;
int rt[MAXN],fa[MAXN],d[MAXN],w[MAXN];
map<int,int>f[MAXN];
void merge(int &a,int b){
	if(f[a].size()<f[b].size())swap(a,b);
	for(iter it=f[b].begin();it!=f[b].end();it++)
		f[a][it->first]+=it->second;
}
signed main(){
	scanf("%lld%lld%lld",&n,&m,&K);
	for(int i=2;i<=n;i++)scanf("%lld",&fa[i]);
	for(int i=1;i<=m;i++){
		int p;scanf("%lld",&p);
		scanf("%lld%lld",&d[p],&w[p]);
	}
	for(int i=1;i<=n;i++)rt[i]=i;
	for(int i=n;i;i--){
		f[rt[i]][d[i]]+=w[i];iter it;
		for(it=f[rt[i]].find(d[i]),it++;it!=f[rt[i]].end();){
			if(it->second>w[i]){it->second-=w[i];break;}
			w[i]-=it->second;iter tmp=it;it++;f[rt[i]].erase(tmp);
		}
		merge(rt[fa[i]],rt[i]);
	}int ans=0;
	for(iter it=f[rt[1]].begin();it!=f[rt[1]].end();it++)
		ans+=it->second;
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Aleph1022 (赞：9)

设 $f_{u,i}$ 表示第 $i$ 天收获 $u$ 点时 $u$ 子树内的答案。

考虑合并 $u$ 和儿子 $v$ 的答案。  
有
$$
f'_{u,i} = \max\{\max\limits_{j=0}^i\{f_{u,i}+f_{v,j}\}.\max\limits_{j=0}^i\{f_{u,j}+f_{v,i}\}\}
$$

发现是一个 max 卷积的形式，可以考虑使用线段树合并维护。  
复杂度 $O(n \log n)$。

代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 1e5;
int n,m,k;
int d[N + 5],w[N + 5];
int to[N + 5],pre[N + 5],first[N + 5];
inline void add(int u,int v)
{
	static int tot = 0;
	to[++tot] = v,pre[tot] = first[u],first[u] = tot;
}
namespace SEG
{
	struct node
	{
		long long val,tag;
		int ls,rs;
	} seg[(N << 6) + 5];
	inline void push(int p)
	{
		if(seg[p].tag)
		{
			if(seg[p].ls)
				seg[seg[p].ls].val += seg[p].tag,
				seg[seg[p].ls].tag += seg[p].tag;
			if(seg[p].rs)
				seg[seg[p].rs].val += seg[p].tag,
				seg[seg[p].rs].tag += seg[p].tag;
			seg[p].tag = 0;
		}
	}
	void insert(int x,long long k,int &p,int tl,int tr)
	{
		static int tot = 0;
		!p && (seg[p = ++tot] = seg[0],1),seg[p].val = max(seg[p].val,k);
		if(tl == tr)
			return ;
		push(p);
		int mid = tl + tr >> 1;
		x <= mid ? insert(x,k,seg[p].ls,tl,mid) : insert(x,k,seg[p].rs,mid + 1,tr);
	}
	long long query(int r,int p,int tl,int tr)
	{
		if(!p || r >= tr)
			return seg[p].val;
		push(p);
		int mid = tl + tr >> 1;
		long long ret = -0x3f3f3f3f3f3f3f3f;
		ret = max(ret,query(r,seg[p].ls,tl,mid));
		r > mid && (ret = max(ret,query(r,seg[p].rs,mid + 1,tr)));
		return ret;
	}
	long long val(int x,int p,int tl,int tr)
	{
		if(tl == tr)
			return seg[p].val;
		push(p);
		int mid = tl + tr >> 1;
		return x <= mid ? val(x,seg[p].ls,tl,mid) : val(x,seg[p].rs,mid + 1,tr);
	}
	int merge(int p,int q,long long ptag,long long qtag,int tl,int tr)
	{
		if(!p && !q)
			return 0;
		if(!p)
		{
			seg[q].val += qtag,seg[q].tag += qtag;
			return q;
		}
		if(!q)
		{
			seg[p].val += ptag,seg[p].tag += ptag;
			return p;
		}
		if(tl == tr)
		{
			ptag = max(ptag,seg[q].val),qtag = max(qtag,seg[p].val);
			seg[p].val = max(seg[p].val + ptag,seg[q].val + qtag);
			return p;
		}
		push(p),push(q);
		int mid = tl + tr >> 1;
		long long plval = seg[seg[p].ls].val;
		long long qlval = seg[seg[q].ls].val;
		seg[p].ls = merge(seg[p].ls,seg[q].ls,ptag,qtag,tl,mid);
		seg[p].rs = merge(seg[p].rs,seg[q].rs,max(ptag,qlval),max(qtag,plval),mid + 1,tr);
		seg[p].val = max(seg[seg[p].ls].val,seg[seg[p].rs].val);
		return p;
	}
}
int fa[N + 5];
int rt[N + 5];
void dfs(int p)
{
	for(register int i = first[p];i;i = pre[i])
		dfs(to[i]),
		rt[p] = SEG::merge(rt[p],rt[to[i]],0,0,1,N);
	d[p] && (SEG::insert(d[p],w[p] + max(SEG::query(d[p],rt[p],1,N),0LL),rt[p],1,N),1);
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(register int i = 2;i <= n;++i)
		scanf("%d",fa + i),add(fa[i],i);
	int x,y,z;
	for(register int i = 1;i <= m;++i)
		scanf("%d%d%d",&x,&y,&z),d[x] = y,w[x] = z;
	dfs(1);
	printf("%lld\n",SEG::seg[rt[1]].val);
}
```

---

## 作者：Yansuan_HCl (赞：8)

写篇题解纪念一下我 $\color{red}{-17}$ 的光辉提交以及三个假算法。~~顺便抢了个最优解。~~

## 题意简述

> 每天你可以砍下树上的某些边，然后当天与 $1$ 节点不再联通的果实如果恰好在当天成熟，则能够收获该果实的果汁。
>
> 求最大能收获的果汁量。

## 题解

首先**需要**想到一个维度含有时间的暴力 dp.

设 $f_u(t)$ 表示在第 $t$ 天砍断 $(u,\mathrm{fa}_u)$ 的最大收益，则有：

$$f_u(t)\gets w_u[t=d_u] + \sum_v \min_{i=1}^tf_v(i)$$

暴力转移可以做到 $O(n^3)$。

设 $g_u(t)=\min_{i=1}^tf_u(t)$，则可以把上面的转移优化到 $O(n^2)$。不过同时存在 $f$ 和 $g$ 并不很雅观，而且难以进一步优化。

试着直接转移 $g$，则可以得到：

$$\begin{aligned} g_u(t)&\gets\sum_vg_v(t) \\

g_u(j) &\gets \max \left\{ g_u(j), w_u+\sum_v g_v(d_u) \right\} \ (j \in [d_u,k])\end{aligned}$$

这样，则可以比较方便地使用数据结构维护。这里使用线段树合并。

对于操作 1，直接合并即可。操作 2 的区间取 $\max$ 则不好处理。一种暴力的做法是对于区间打取 $\max$ 的 tag, 合并的时候暴力下传（需要新建点）。但是这样做时间复杂度是错的。

还有一种经典做法是，把取 $\max$ 的区间分解为一些最大值小于 $\max$ 的区间，再把这些区间推平。本题就可以这样做！为什么复杂度是对的呢？**此时不妨回顾一下转移的式子。**所有的操作 2 中，被取 $\max$ 的都是一段后缀。因此，**$f_u(t)$ 关于 $t$ 单调不降**。这说明我们只需要**推平一段区间**。

此外，想要时间复杂度是正确的，就要求不能下传标记。只有标记永久化的线段树满足这个条件。这要求信息是可叠加的。标记永久化的区间加线段树满足这个条件，尝试用它维护区间推平。

区间推为 $0$，可以用删除一个子树实现。之后再把这个区间加上 $\max$ 即可。

## 代码

```cpp
const int N = 100005;
int n, m, k;
// 设 f[u][t] 为在第 t 天割掉 u, u 子树内最大收益。
// 若在第 t 天割掉 u, 则子树内所有割的操作只能在第 [1..t] 天完成

// 施加 u 的限制:
// f[u][d[u]]=w[u]+\sum{g[v][d[u]]}
// g[u][i]=sum{g[u][i]+g[v][i]}
// g[u][d[u]..k] \gets w[u]+\sum{g[v][d[u]]}

struct Node { ll mn, mx, tag; int ls, rs; } tr[N << 6];
#define mid ((l + r) >> 1)
#define LS(p) tr[p].ls
#define RS(p) tr[p].rs
#define TAG(p) tr[p].tag
#define N(p) tr[p].mn
#define X(p) tr[p].mx

int trash[N << 6], tp, ap;
#define alloc() (tp ? trash[tp--] : ++ap);
#define del(p) if (p) { trash[++tp] = p; p = LS(p) = RS(p) = X(p) = TAG(p) = N(p) = 0; }

// 标记永久化线段树
// 支持区间 min max, 区间推平为 0, 区间加
// 加法是典型的可加信息。
#define maintain(p) { \
    N(p) = min(N(LS(p)), N(RS(p))) + TAG(p); \
    X(p) = max(X(LS(p)), X(RS(p))) + TAG(p); \
}
void merge(int &p, int &q, int l = 1, int r = k) {
    if (!p || !q) { p = p | q; return; }
    if (l == r) {
        TAG(p) += TAG(q);
        X(p) = N(p) = TAG(p);
        del(q);
        return;
    }
    TAG(p) += TAG(q);
    merge(LS(p), LS(q), l, mid);
    merge(RS(p), RS(q), mid + 1, r);
    del(q);
    maintain(p);
}
// [b, e] 删除并加上 v
// 其中 f[e]<=v
void cover(int b, ll v, int &p, int l = 1, int r = k) {
    if (!p) p = alloc();
    if (b <= l) {
        if (X(p) <= v) {
            del(LS(p)); del(RS(p));
            TAG(p) = X(p) = N(p) = v;
        } else {
            v -= TAG(p);
            if (N(LS(p)) <= v)
                cover(b, v, LS(p), l, mid);
            if (N(RS(p)) <= v)
                cover(b, v, RS(p), mid + 1, r);
            maintain(p);
        }
        return;
    }
    v -= TAG(p);
    if (b <= mid) cover(b, v, LS(p), l, mid);
    cover(b, v, RS(p), mid + 1, r);
    maintain(p);
}
ll query(int x, int p, int l = 1, int r = k) {
    if (!p) return 0;
    if (l == r) return TAG(p);
    return TAG(p) + ((x <= mid) ? query(x, LS(p), l, mid) : query(x, RS(p), mid + 1, r));
}


int fa[N], root[N];
int d[N]; ll w[N];

int main() {
    rd(n); rd(m); rd(k);
    U (i, 2, n) rd(fa[i]);
    U (i, 1, m) {
        int u, td; ll tw;
        rd(u); rd(td); rd(tw);
        d[u] = td;
        w[u] = tw;
    }

    D (u, n, 2) {
        if (d[u]) cover(d[u], w[u] + query(d[u], root[u]), root[u]);
        merge(root[fa[u]], root[u]);
    }

    ll f = 0;
    U (i, 1, k) f = max(f, query(i, root[1]));
    printf("%lld", f);
}
```

## 几种错误解法

### 贪心

按 $d$ 从小到大加入，若 $w_u > \sum_{1\to u}$ 则把这些点删掉。

如果一个点下面有很多 $w$ 较小但是 $\sum w$ 较大的点就寄了。

### 不含时间的 dp

分为砍下 $u$ 和不砍下 $u$ 两类，在上方减去贡献。

这样无法处理不摘取 $u$ 但子树内对时间有限制的情况。

### 暴力 pushdown

若对一棵满树进行 2 操作，则复杂度退化为 $O(n)$。满树是容易构造的。

~~这些错误例我全写过。~~

---

## 作者：mRXxy0o0 (赞：6)

# 分析

考虑两个祖孙关系的点对，若它们都可以计入贡献，则它们的时间自上而下单调不递增。

据此，直接掏出 DP 状态 $f_{u,i}$ 表示 $u$ 子树内选的点中最大时间恰好为 $i$ 的最大贡献。

先解决维护好的 $f_u$ 与一个新儿子 $f_v$ 的转移，即 $f'_{u,i}=\max(f_{u,i}+\max\limits_{j=1}^if_{v,j},f_{v,i}+\max\limits_{j=1}^if_{u,j})$。

然后再加入 $u$ 这个点的贡献，$f'_{u,d_u}=\max(f_{u,d_u},w_u+\max\limits_{j=1}^{d_u}f_{u,j})$。

考虑使用线段树合并实现，比较棘手的就是前缀 $\max$ 的维护了。这里可以维护两个全局变量表示这两个前缀 $\max$，因为线段树合并的区间是可以从左到右依次进行的，所以只要线段树上维护区间 $\max$ 就可以简单维护这两个前缀 $\max$。

然后会发现一个小问题，这个地方会涉及到区间加（一个区间两棵树一颗有一颗没有时），也就是 `pushdown` 操作，这会不会导致建出新点、复杂度爆炸呢？

实际上不会，因为任意区间要么是线段树的叶子，要么是有儿子的节点，而没存的节点实际上是默认为极小值的。所以 `pushdown` 操作时直接不管空节点就好。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
const ll inf=1e9;
int n,m,k,h[N],ne[N],e[N],idx,a[N],b[N],root[N],tot;
struct node{
	int ls,rs;
	ll mx,ad;
}tr[N<<5];
inline void add(int u,int v){
	ne[++idx]=h[u],h[u]=idx,e[idx]=v;
}
inline void pushup(int u){
	tr[u].mx=max(tr[tr[u].ls].mx,tr[tr[u].rs].mx);
}
inline void pushdown(int u){
	int sn=tr[u].ls;
	if(sn){
		tr[sn].mx+=tr[u].ad;
		tr[sn].ad+=tr[u].ad;
	}
	sn=tr[u].rs;
	if(sn){
		tr[sn].mx+=tr[u].ad;
		tr[sn].ad+=tr[u].ad;
	}
	tr[u].ad=0;
}
inline void mdf(int &u,int l,int r,int x,ll v){
	if(!u) u=++tot;
	if(l==r){
		tr[u].mx=max(tr[u].mx,v);
		return ;
	}
	pushdown(u);
	int mid=l+r>>1;
	if(x<=mid) mdf(tr[u].ls,l,mid,x,v);
	else mdf(tr[u].rs,mid+1,r,x,v);
	pushup(u);
}
ll su,sv;
inline int merge(int u,int v,int l,int r){
	if(!u&&!v) return 0;
	if(!u){
		sv=max(sv,tr[v].mx);
		tr[v].mx+=su;
		tr[v].ad+=su;
		return v;
	}
	if(!v){
		su=max(su,tr[u].mx);
		tr[u].mx+=sv;
		tr[u].ad+=sv;
		return u;
	}
	if(l==r){
		su=max(su,tr[u].mx),sv=max(sv,tr[v].mx);
		tr[u].mx=max(tr[u].mx+sv,tr[v].mx+su);
		return u;
	}
	pushdown(u),pushdown(v);
	int mid=l+r>>1;
	tr[u].ls=merge(tr[u].ls,tr[v].ls,l,mid);
	tr[u].rs=merge(tr[u].rs,tr[v].rs,mid+1,r);
	pushup(u);
	return u;
}
inline ll query(int u,int l,int r,int x){
	if(!u) return 0;
	if(r<=x) return tr[u].mx;
	pushdown(u);
	int mid=l+r>>1;
	ll res=query(tr[u].ls,l,mid,x);
	if(x>mid) res=max(res,query(tr[u].rs,mid+1,r,x));
	return res;
}
inline void dfs(int u){
	for(int i=h[u];i;i=ne[i]){
		int v=e[i];
		dfs(v);
		su=sv=0;
		root[u]=merge(root[u],root[v],1,m);
	}
	if(a[u]) mdf(root[u],1,m,a[u],b[u]+query(root[u],1,m,a[u]));
}
int main(){
	scanf("%d%d%d",&n,&k,&m);
	for(int i=2,x;i<=n;++i){
		scanf("%d",&x);
		add(x,i);
	}
	for(int i=1,x,y,z;i<=k;++i){
		scanf("%d%d%d",&x,&y,&z);
		a[x]=y,b[x]=z;
	}
	dfs(1);
	printf("%lld",tr[root[1]].mx);
	return 0;
}
```

---

## 作者：Elma_ (赞：6)

好题！

先考虑一个暴力的 DP，设 $f_{i,j}$ 为 $i$ 号点子树在 $j$ 时刻之前的最大收益，考虑 $u$ 号点在时刻 $j$ 是否收获：

- $u$ 此时不收获：

$$f_{u,j} = \sum_{v \in son_u}f_{v,j}$$

- $u$ 此时收获，那么对于 $u$ 上的果实 $i$，需要保证 $j \geq d_i$，此时有：

$$f_{u,j} = w_i + \sum_{v \in son_u} f_{v, d_i}$$

最后我们令 $f_{u,i} = \max( f_{u,i},f_{u,i -1})$。容易发现只有 $O(n)$ 个时刻，因此我们可以对时刻离散化，这样暴力转移是 $O(n^2)$ 的。

简单的观察是，$f_{u,i}$ 随着 $i$ 的增加是单调不降的。进一步我们可以发现，事实上 $f_{u,i}$ 有很长的段值都是相同的，它的拐点并不会很多，也就是说 $f_u$ 的差分数组只有 $O(n)$ 的位置有值（我们稍后对这部分进行更具体的说明）。

我们考虑用 map 维护这些差分。发现在第二种转移中我们需要查询 $\sum f_{v,d_i}$，那么我们可以先完成第一种转移，这样在第二种转移中我们就可以直接在已经转移好的 map 中操作。

对于 $u$ 不收获的情况需要把 $u$ 和 $v$ 对应的 map 合并，我们使用启发式合并来保证复杂度。对于 $u$ 收获的情况，我们是对合并后的一个后缀进行了修改，相当于在位置 $d_i$ 插入了差分 $w_i$，但此时可能会删掉后面的一部分差分，并对常数个差分进行修改，类似于下图这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/b2vglp0z.png)

绿色部分内的差分被 $w_i$ 干掉了，后面的那个差分也被 $w_i$ 截掉了一段。二分找到插入差分的位置，直接修改即可。

下面我们分析一下复杂度：观察转移，每个点 $u$ 的 map 是所有儿子 map 的并再加上 $u$ 上的一个差分，并且这个过程可能会删掉一些差分。因此，点 $u$ 的 map 中的差分个数不会超过子树大小。那么根据启发式合并的经典结论，合并的复杂度是 $O(n \log^2 n)$。而每个差分至多被删除一次，因此总时间复杂度为 $O(n \log^2 n)$。


```cpp
/*
也许所有的执念 就像四季的更迭
没有因缘 不需致歉
是否拥抱着告别 就更能读懂人间
还是感慨 更多一点
*/
#define int long long

const int MN = 1e5 + 5;
int N, M, K, d[MN], w[MN], vr[MN];
map <int, int> f[MN];

vector <int> G[MN];

inline void DFS(int u) {
    for (int v : G[u]) {
        DFS(v);
        if (f[u].size() > f[v].size())
            swap(f[u], f[v]);
        for (auto it = f[v].begin(); it != f[v].end(); it++)
            f[u][it -> fi] += it -> se;
        f[v].clear();
    }
    if (vr[u]) {
        int i = vr[u];
        f[u][d[i]] += w[i];
        int rest = w[i];
        for (auto it = f[u].upb(d[i]), t = it; it != f[u].end(); ) {
            if (rest >= it -> se) {
                rest -= it -> se, t = it++;
                f[u].erase(t);
            } else {
                it -> se -= rest;
                break;
            }
        }
    }
}

signed main(void) {
    N = read(), M = read(), K = read();
    for (int i = 2; i <= N; i++) {
        int fa = read();
        G[fa].pb(i);
    }
    for (int i = 1; i <= M; i++) {
        int v = read(); d[i] = read(), w[i] = read();
        vr[v] = i;
    }
    DFS(1);
    int ans = 0;
    for (auto it = f[1].begin(); it != f[1].end(); it++)
        ans += it -> se;
    printf("%lld\n", ans);
    return 0;       
}
```


---

## 作者：Flash_Man (赞：2)

[link](https://www.luogu.com.cn/problem/P6847)

[双倍经验](https://www.luogu.com.cn/problem/CF1193B)

$f(u,i)$ 表示 $u$ 节点在 $i$ 天之前收割的最大收益。
$$
f(u,i)=\max\begin{cases}\sum f(v,i)\\w_i+\sum f(v,d_u)&,\text{if}\ i\ge d_u \end{cases}
$$
考虑到转移方程是求和和后缀加，所以用 map 维护断点即可。第一行转移方程相当于 map 按秩合并，第二行转移方程相当于在 map 里加一个差分标记。

细节：由于两行转移方程要取 $\max$，所以用第二行更新时要把后面的一些差分标记覆盖掉，具体实现见代码。

```cpp
#include <cstdio>
#include <map>
#include <algorithm>
#define int long long
const int maxn = 1e5 + 3;
int n, m, k, fa[maxn], a[maxn], d[maxn], w[maxn];
std::map<int, int> f[maxn];
int rt[maxn], ans = 0;
void merge(int &x, int y) {
	if (f[x].size() < f[y].size()) std::swap(x, y);
	for (auto p : f[y]) f[x][p.first] += p.second;
}
signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 2; i <= n; i++) scanf("%lld", &fa[i]);
	for (int i = 1, v; i <= m; i++) scanf("%lld", &v), scanf("%lld%lld", &d[v], &w[v]);
	for (int i = 1; i <= n; i++) rt[i] = i;
	for (int i = n; i >= 1; i--) {
		f[rt[i]][d[i]] += w[i];
		auto it = f[rt[i]].find(d[i]);
		for (it++; it != f[rt[i]].end(); ) {
			if (it->second > w[i]) { it->second -= w[i]; break; }
			w[i] -= it->second;
			auto tmp = it++;
			f[rt[i]].erase(tmp);
		}
		merge(rt[fa[i]], rt[i]);
	}
	for (auto p : f[rt[1]]) ans += p.second;
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：Mirasycle (赞：1)

可以发现约束条件就是子节点被切断的时间要在祖先节点之前，否则就没机会切断了。

于是设出 dp，用 $f_{u,i}$ 表示在 $u$ 节点，它和其父亲的边在 $\le i$ 时刻被切断所得到的最大价值。


$$f_{u,i}=\begin{cases}
\max(\sum\limits_v f_{v,d_u}+val_u,\sum\limits_v f_{v,i}) & i\ge d_u
\\ \sum\limits_v f_{v,i} & i<d_u
\end{cases}$$


注意这里的 $f$ 其实是前缀最大值因为定义是 $ \le i$。暴力做的话时间复杂度 $O(nk)$。

但是这里是二维的，复杂度显然不行，一般这种二维 dp 想要优化的话，一般就是第二维通过转化为图像或者线段树合并啥的或者更难点就是找性质。本题第二维显然是整体 dp 的形式，我们只需要用 STL 或者数据结构维护第二维，每次直接继承儿子的第二维并且进行 $O(1)$ 个修改。

本题采用 ` std::map ` 来维护。

可以发现有用的点并不多，因此 map 中的第二维信息只有子树内出现的 $d_v$（相邻 $d_v$ 之间的 $f$ 是相同的）。这就会出现一个问题，在合并两个 map 的时候，假设是 $rt_u\gets rt_v$，如果 $rt_v$ 中出现过的一个值在 $rt_u$ 中没出现过，那么对应点累加的时候该点对应的值在 $rt_u$ 中将会是 $0$，这不符合前缀 $\max$ 的要求啊。于是我们考虑维护差分 $g_{u,i}$，可以注意到差分也是可以对应位置相加的且可以自动完成对于空白位置的前缀 $\max$ 要求。

这样子我们就完成了 $\sum f_{v,i}$ 的转移处理，直接启发式合并 map，然后对应位置相加即可。

现在要处理的就是单点（$d_u$ 位置） $+val_u$，并且作为前缀值往后更新前缀 $\max$。

$d_u$ 位置 $+val_u$，是很好做的，我们直接对于差分数组 $g_{u,d_u}\gets val_u$，然后不可在后面直接 $-val_u$，因为前缀 $\max$ 的要求需要保证差分数组恒正。于是我们就直接把中间的一段 $\sum g_{v,i}\le val_u$ 的差分值直接舍去即可（可以看看下面一张图），这一段是暴力往后更新，因为我们可以发现每个点只会进入 map 一次，然后最多被舍去一次，所以时间复杂度均摊是正确的。

![](https://cdn.luogu.com.cn/upload/image_hosting/sq7iptdt.png)


```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int maxn=1e5+10;
map<int,ll> dp[maxn]; vector<int> G[maxn];
map<int,ll>::iterator it,it2;
int n,m,k,d[maxn],val[maxn],rt[maxn];
int merge(int u,int v){
	if(dp[rt[u]].size()<dp[rt[v]].size()) swap(rt[u],rt[v]);
	for(auto it:dp[rt[v]]) dp[rt[u]][it.fi]+=it.se;
	dp[rt[v]].clear(); return rt[u];
}
void dfs(int u){
	for(auto v:G[u]){
		dfs(v); 
		rt[u]=merge(u,v);
	}
	if(!val[u]) return ;
	dp[rt[u]][d[u]]+=val[u];
	for(it=dp[rt[u]].upper_bound(d[u]);it!=dp[rt[u]].end();it=it2){
		if(val[u]>=it->se){
			it2=it; it2++; val[u]-=it->se;
			dp[rt[u]].erase(it); 
		}else{ it->se-=val[u]; break; }
	}
}
int main(){
	cin>>n>>m>>k;
	for(int i=2;i<=n;i++){
		int fa; cin>>fa;
		G[fa].push_back(i);
	}
	for(int i=1;i<=m;i++){
		int x; cin>>x; 
		cin>>d[x]>>val[x];
	}
	for(int i=1;i<=n;i++) rt[i]=i;
	dfs(1); ll ans=0;
	for(it=dp[rt[1]].begin();it!=dp[rt[1]].end();it++) 
		ans+=it->second;	
	cout<<ans;
	return 0;
}
```
时间复杂度 $O(n\log^2 k)$。

---

## 作者：pikiuk (赞：1)

分享两种做法：


我们把剪枝看作一种选择点的操作，考察一种合法的选择方案，若两个被选点存在祖孙关系，那么孙子的成熟时间一定早于祖先。

那么我们记 $f(u,k)$ 表示对于点 $u$ 及其子树，选出的最晚点的时间为 $k$ 的选点最大和。

那么转移相当于加前缀 $\max$，后缀加，线段树合并维护即可。

----

下面是我的做法：

我们记 $f(u,k)$ 表示对于子树 $u$，当前时间 $\leq k$ 的最大收益。

转移：$f(u,k)=\max \{[k\geq d_u] w_u+\sum\limits_{v\in son(u)}  f(v,\min \{k,d_u\}),\sum\limits_{v\in son(u)}  f(v,k)\}$。

不难发现，$u$ 子树内第二维有效位置只有子树大小个，也就是，除了有效位置外，其他位置的 dp 值和前项相等，且 dp 值单调不减。

然后我们发现这个 dp 的形式其实是“对应位置相加/单点加/后缀 chkmax”，对于第二个操作，可以把问题转化为”单点加，区间推平“的操作，区间推平相当于删除若干个有效 dp 值，对复杂度没有影响。对于“对应位置相加”，直接维护子树内有效的 dp 值合并的复杂度是 $siz(u)+siz(v)$ 的，因为对某个 dp 值更新需要实现”区间加“操作，那么我们考虑维护差分，那么一次合并相当于”插入一个值“。

特别注意：在删除有效 dp 值的时候不能一边遍历一边删，笔者赛时在代码实现的出现了该错误，最终导致没有通过。


---

## 作者：Genius_Star (赞：0)

### 思路：

首先考虑树形 dp，定义 $dp_{i, j}$ 表示 $i \to fa_i$ 这条边在第 $j$ 天恰好剪掉的最大贡献；然后设 $w(u, i)$ 表示在第 $i$ 天剪掉 $u \to fa_u$ 这条边可以得到的贡献。

这里我们考虑下怎么减最优，若有两个果实在同一天成熟，我们可以先减更深的，再减浅的；所以存在一种最优方案，使得每次只收获一个果实。

故我们有状态转移：

$$dp_{u, i} = w(u, i) + \sum_{v \in son_u} f_{v, i}$$

这里 $f_v$ 是 $dp_v$ 的前缀 $\max$ 数组；显然如果子树内减的时间是 $>i$ 的那么不会造成贡献（因为在 $i$ 时刻减 $u \to fa_u$ 后 $u$ 子树已经掉下来）。

考虑优化，注意到我们减的时刻如果没有任何果实，那么不如不减，所以一个子树 $u$ 减的本质不同时间的状态数 $O(siz_u)$ 的，故可以线段树合并。

考虑直接转移到 $f_{u, i}$ 上去，我们有：

$$\begin{aligned} f_{u, i} &= \max\limits_{j = 1}^i \left( w(u, j) + \sum_{v \in son_u} f_{v, j}\right) \\ &= \max \left( \sum_{v \in son_u} f_{v, i}, [i \ge d_u] \left( w_u + \sum_{v \in son_u} f_{v, d_u} \right) \right)\end{aligned}$$

故先合并，然后将 $[d_u, k]$ 对一个定值取 $\max$，直接打加法与 $\max$ 肯定会炸。

考虑维护区间 $\min, \max$ 即可判断是否相同即可，加法标记我们只需要保证是打在一个相同的段中即可。

这是因为由于任意时刻时一个 $f_u$ 中全部相同的段数是 $O(siz_u)$ 的，故区间取 $\max$ 时我们可以直接去找需要取 $\max$ 的段复杂度就是正确的。 

时间复杂度为 $O(N \log N)$。

[**link**](https://www.luogu.com.cn/record/213054005)

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e5 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int lson, rson;
	ll Max, Min, tag;
}X[N << 5];
ll ans;
int n, m, k, cnt;
int rt[N], a[N], h[N], fa[N];
vector<int> E[N];
inline int newnode(){
	++cnt;
	return cnt;
}
inline void pushup(int k){
	X[k].Max = max(X[X[k].lson].Max, X[X[k].rson].Max);
	X[k].Min = min(X[X[k].lson].Min, X[X[k].rson].Min);
}
inline void upd(int k, ll v){
	if(!k)
	  return ;
	X[k].Max += v, X[k].Min += v, X[k].tag += v;
}
inline void push_down(int k){
	if(X[k].tag){
		upd(X[k].lson, X[k].tag);
		upd(X[k].rson, X[k].tag);
		X[k].tag = 0;
	}
}
inline bool check(int k){
	return X[k].Min == X[k].Max;
} 
inline ll ask(int k, int l, int r, int i){
	if(check(k))
	  return X[k].Max;
	push_down(k);
	int mid = (l + r) >> 1;
	if(i <= mid)
	  return ask(X[k].lson, l, mid, i);
	else
	  return ask(X[k].rson, mid + 1, r, i);
}
inline int merge(int x, int y){
	if(!x || !y)
	  return x + y;
	if(check(x)){
		upd(y, X[x].Max);
		return y;
	}
	if(check(y)){
		upd(x, X[y].Max);
		return x;
	}
	push_down(x), push_down(y);
	X[x].lson = merge(X[x].lson, X[y].lson);
	X[x].rson = merge(X[x].rson, X[y].rson);
	pushup(x);
	return x; 
}
inline void getnew(int k){
	if(!check(k))
	  return ;
	int ls = newnode(), rs = newnode();
	X[k].lson = ls, X[k].rson = rs;
	X[ls].Max = X[rs].Max = X[ls].Min = X[rs].Min = X[k].Max;
}
inline void update(int k, int l, int r, int ql, int qr, ll v){
	if(X[k].Min >= v)
	  return ;
	if(l == ql && qr == r && X[k].Max <= v){
		X[k].Min = X[k].Max = v;
		X[k].tag = 0;
		return ;
	}
	push_down(k);
	getnew(k);
	int mid = (l + r) >> 1;
	if(qr <= mid)
	  update(X[k].lson, l, mid, ql, qr, v);
	else if(ql > mid)
	  update(X[k].rson, mid + 1, r, ql, qr, v);
	else{
		update(X[k].lson, l, mid, ql, mid, v);
		update(X[k].rson, mid + 1, r, mid + 1, qr, v);
	}
	pushup(k);
}
inline void dfs(int u){
	rt[u] = newnode();
	for(auto v : E[u]){
		if(v == fa[u])
		  continue;
		dfs(v);
		rt[u] = merge(rt[u], rt[v]);
	}
	if(a[u])
	  update(rt[u], 1, k, a[u], k, h[u] + ask(rt[u], 1, k, a[u]));
}
bool End;
int main(){
	n = read(), m = read(), k = read();
	for(int i = 2; i <= n; ++i){
		fa[i] = read();
		E[fa[i]].push_back(i);
	}
	while(m--){
		int v = read(), d = read(), w = read();
		a[v] = d, h[v] = w;
	}
	dfs(1);
	write(X[rt[1]].Max);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：AC_love (赞：0)

设 $f(i, j)$ 表示 $i$ 的子树在第 $j$ 天前被全部割掉的最大收益，考虑 $i$ 位置的果实贡献。

如果不收割 $i$ 位置的果实，有 $f(i, j) = \sum_{x \in son_i} f(x, j)$。

如果收割 $i$ 位置的果实，有 $f(i, j) = w + \sum_{x \in son_i} f(x, d)$。

二者取 $\max$ 即可。

暴力转移，复杂度 $O(nk)$，考虑优化。

考虑线段树合并。

发现收割 $i$ 位置的果实时，这个贡献一定是个定值，计算出这个定值，令其为 $x$，扔到线段树上做区间推平下界。

区间推平下界的具体做法是：维护每个区间的 $\min$ 和 $\max$。暴力 + 剪枝，当 $\max$ 小于等于 $x$ 时整块修改，当 $\min$ 大于等于 $x$ 时不用修改。这是个比较老套的套路了，复杂度是正确的。

加法操作的标记很难下传，标记永久化即可。

---

## 作者：derta (赞：0)

考虑 DP。设 $f_{i,j}$ 表示以 $i$ 为根的子树在第 $j$ 天**前**全部剪掉收获的最大果汁量。注意到在剪掉 $(p_i,i)$ 前将其子树全部剪掉一定是最优的，故有转移方程：

$$f_{i,j}=\max\left\{f_{i,j-1},w_x[v_x=i]+\sum_{k \in \mathrm{son}(i)}f_{k,j}\right\}$$

由于 $v_j \geq 2$ 的数据范围，不必对 $i=1$ 的情况分类讨论。

现在我们需要将第二维压掉。发现从 $i$ 的子节点转移到 $i$ 的过程并没有涉及 $j$ 的改变，所以这可以看作一个合并的过程。具体地，我们维护 $f_i$ 的「拐点」，也就是满足 $f_{i,j} \neq f_{i,j-1}$ 的点。$w_x[v_x=i]$ 造成了这些「拐点」，而 $\sum_{k \in \mathrm{son}(i)} f_{k,j}$ 则负责将子树中的「拐点」合并。所以，「拐点」数量不超过 $i$ 的子树大小，使用启发式合并即可降低时间复杂度。另外，$w_x[v_x=i]$ 这一项相当于后缀加的操作，所以需要维护差分数组。实现的细节较多，给出代码。

```cpp
#include <bits/stdc++.h>
const int MAXN = 100005;
typedef long long LL;
int n, m, k, d[MAXN], w[MAXN], son[MAXN], sz[MAXN];
std::vector<int> G[MAXN];
std::map<int, LL> f[MAXN]; //注意long long

void DFS(int x) { //找重儿子
	sz[x] = 1;
	for(int v : G[x]) {
		DFS(v);
		sz[x] += sz[v];
		if(sz[son[x]] < sz[v])
			son[x] = v;
	}
}

void Merge(int x) {
	if(son[x] != 0)
		Merge(son[x]), f[x] = std::move(f[son[x]]);
	for(int v : G[x])
		if(v != son[x]) {
			Merge(v);
			for(auto t : f[v]) {
				auto p = f[x].insert(t);
				if(p.second == false)
					p.first->second += t.second;
			}
		}
   //这里要先全部合并再插入
	if(d[x] != 0) {
		auto p = f[x].insert({d[x], w[x]}); // insert 返回值为 pair<iterator, bool>，前者表示插入或阻止插入的迭代器，后者表示是否成功插入
		auto it = p.first;
		if(p.second == false)
			it->second += w[x]; // 拐点已存在，直接加上
		if(++it == f[x].end()) // 判边界。如果先插入再合并，这里会以为后面没有拐点而错误地结束
			return ;
		LL sum = it->second; // sum 也要开long long，否则时间全部相同时只是 it->second 也有可能导致溢出
		while(sum <= w[x]) {
			auto t = it++;
			f[x].erase(t);
			if(it == f[x].end()) // 判边界
				return ;
			sum += it->second;
		}
		it->second = sum - w[x];
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 2; i <= n; ++i) {
		int p;
		scanf("%d", &p);
		G[p].push_back(i);
	}
	for(int i = 1; i <= m; ++i) {
		int v;
		scanf("%d", &v);
		scanf("%d%d", &d[v], &w[v]);
	}
	DFS(1);
	Merge(1);
	LL ans = 0;
	for(auto it = f[1].begin(); it != f[1].end(); ++it)
		ans += it->second;
	printf("%lld", ans);
	return 0;
}
```

---

