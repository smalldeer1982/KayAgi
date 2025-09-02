# [ICPC 2024 Xi'an I] Holes and Balls

## 题目描述

给定 $n$ 个球，第 $i$ 个球的值为 $p_i$。保证 $p_1,p_2,\dots,p_n$ 是 $1,2,3\dots,n$ 的一个排列。

有一棵有根树，包含 $n$ 个顶点，每个顶点是一个洞，每个洞只能容纳一个球。

树的根是第一个顶点。

现在你需要用这些球填满洞。

你需要按 $1$ 到 $n$ 的顺序依次投掷每个球，步骤如下：

1. 将球投到顶点 $1$。
2. 设球所在的顶点为 $p$。
3. 如果第 $p$ 个顶点已经被其他球填满，你需要选择一个顶点 $x$，将球投到第 $x$ 个顶点，然后返回步骤 $2$。你需要保证第 $x$ 个顶点是第 $p$ 个顶点的子节点，并且第 $x$ 个顶点的子树中至少有一个顶点未被填满。
4. 否则，球将填满第 $p$ 个顶点。

投完所有球后，用 $a_i$ 表示第 $i$ 个顶点中球的值。

你需要找到 $\{a_n\}$ 的最小字典序。

我们定义 $dep_i$ 为从第 $i$ 个顶点到树根（第一个顶点）的路径上的顶点数。

特别地，对于任意两个顶点 $x<y$，保证 $dep_x\le dep_y$。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5
3 1 5 4 2
1 2
2 3
3 4
4 5
```

### 输出

```
3 1 5 4 2```

## 样例 #2

### 输入

```
9
9 2 6 3 5 7 1 4 8
1 2
1 3
2 4
2 5
3 6
3 7
4 8
4 9
```

### 输出

```
9 2 1 3 6 4 8 5 7```

# 题解

## 作者：honglan0301 (赞：6)

我好像秒了。

## 分析

<0> 记 $q_i$ 为 $p_i$ 的逆排列。则显然地，一种填数方式合法当且仅当对于每个节点 $i$ 都有 $q_{a_i}=\min\limits_{j\in\text{subtree}_i}\{q_{a_j}\}$。

<1> 对于最小化字典序问题，显然要从前往后逐位确定。那么我们需要解决的问题变为，在 $q_{a_j(j<i)}$ 均已确定的情况下，求出 $p_{q_{a_i}}$ 可能的最小值。那么：

1. 首先考虑判定，即判断 $q_{a_i}$ 是否可以为 $k$：

	记 $lim_i$ 表示 $i$ 所有已确定的祖先 $j$ 中 $q_{a_j}$ 的最大值。由于题目保证 $fa_i(fa_i<i)$ 已被确定，那么只需满足三个要求，一是需要 $\forall j<i,\ k\neq q_{a_j}$，二是需要 $k>lim_i$，三是需要能够把 $[lim_i+1,k-1]$ 这些球全都填到 $i$ 子树外面。
    
  	对于第三个要求，我们注意到这些球显然能填就填，那么类似拓扑排序地，对于每个祖先均被填过的 $j (j\neq i)$，在处理到第 $lim_j$ 个球时将其加入队列，容易做到 $O(n)$ 判定。

2. 观察结论：

	由判定过程可知，$q_{a_i}$ 的可能值是一段区间 $[l,r]$（再去掉已被使用过的 $q_{a_j} (j<i)$），其中 $l=lim_i+1$，我们只需快速求出区间右端点 $r$。
    
3. 观察结论：

	考虑这样一种刻画。记录 $cnt_i=\sum\limits_{j\notin \text{subtree}_i} [lim_j=i]$ 及其前缀和数组 $sum_i$，则可以确定 $r=\min\{i|sum_i<i\}$。
    
   证明：一方面，$sum_i<i$ 意味着第 $i$ 个球一定无处可填，即 $r\leq i$；另一方面，当 $\forall j<i,\ sum_j\geq j$ 时，由于题目保证 $\forall x<y,dep_x \leq dep_y$（已确定的点一定形成包含根的连通块），对子树外未确定的点按照 $(lim,dep)$ 双关键字排序后依次填入球一定合法，因此 $r=i$。
   
4. 那么此时可以做到 $O(n)$ 时间确定一位，总复杂度 $O(n^2)$。

<2> 考虑优化。目前的时间复杂度瓶颈有两处，分别是求右端点 $r$ 和区间求未被选择的数的 $\min$。

1. 后者可以使用线段树简单处理。只需单点修改（每次把被选择的数改成充分大的数）+区间求 $\min$，时间复杂度 $O(n\log n)$。

2. 前者可以利用题目条件。注意到题目保证 $\forall x<y,dep_x\leq dep_y$，这意味着每次确定一个数时，其子树内所有点的 $lim$ 均相同。因此对权值考虑，维护 $sum_i-i$，只需支持“后缀加减，求第一个值为负数的下标”，可以在维护区间加区间 $\min$ 的线段树上二分实现，时间复杂度 $O(n\log n)$。

3. 综上，总时间复杂度 $O(n\log n)$，可以通过本题。

## 代码

```cpp
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define int long long

int n,u,v,fa[500005],dep[500005],sz[500005],ans[500005];
int pp[500005],usd[500005],wz[500005];
vector <int> e[500005];

void dfs0(int x,int fat)
{
	sz[x]=1;
	for(auto i:e[x])
	{
		if(i==fat) continue;
		dep[i]=dep[x]+1; fa[i]=x; dfs0(i,x); sz[x]+=sz[i];
	}
}

struct tree1
{
	pair<int,int> mn;
}tree1[2000005];

#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define m(x) tree1[x].mn
#define md(x,y) ((x+y)>>1)
#define push_up1(x) m(x)=min(m(ls(x)),m(rs(x)))

void build1(int l,int r,int p)
{
	if(l==r) return m(p)=mp(pp[l],l),void(); int mid=md(l,r);
	build1(l,mid,ls(p)); build1(mid+1,r,rs(p)); push_up1(p);
}
void cz1(int l,int r,int x,int p)
{
	if(l==r) return m(p)=mp(10000000,l),void(); int mid=md(l,r);
	if(mid>=x) cz1(l,mid,x,ls(p)); else cz1(mid+1,r,x,rs(p)); push_up1(p);
}
pair<int,int> ask1(int l,int r,int x,int y,int p)
{
	if(l>=x&&r<=y) return m(p); int mid=md(l,r); pair<int,int> na=mp(10000000,0);
	if(mid>=x) na=min(na,ask1(l,mid,x,y,ls(p))); if(mid<y) na=min(na,ask1(mid+1,r,x,y,rs(p))); return na;
}

struct tree2
{
	int mn,tagadd;
}tree2[2000005];

#define n(x) tree2[x].mn
#define push_up2(x) n(x)=min(n(ls(x)),n(rs(x)));
#define tg(x) tree2[x].tagadd

void cza(int k,int p) {n(p)+=k; tg(p)+=k;}
void push_down(int p) {cza(tg(p),ls(p)); cza(tg(p),rs(p)); tg(p)=0;}

void build2(int l,int r,int p)
{
	if(l==r) return n(p)=n-l,void(); int mid=md(l,r);
	build2(l,mid,ls(p)); build2(mid+1,r,rs(p)); push_up2(p);
}
void cza(int l,int r,int x,int y,int k,int p)
{
	if(l>=x&&r<=y) return cza(k,p),void(); int mid=md(l,r); push_down(p);
	if(mid>=x) cza(l,mid,x,y,k,ls(p)); if(mid<y) cza(mid+1,r,x,y,k,rs(p)); push_up2(p);
}
int ask2(int l,int r,int p)
{
	if(l==r) return l; int mid=md(l,r); push_down(p);
	if(n(ls(p))<0) return ask2(l,mid,ls(p)); else return ask2(mid+1,r,rs(p));
}

/*int cnt[500005]; 这是赛时用来验证正确性的暴力。
void dfs1(int x,int fat,int lim)
{
	lim=max(lim,wz[x]);
	cnt[lim]++;
	for(auto i:e[x])
	{
		if(i==fat) continue;
		dfs1(i,x,lim);
	}
}
int calc(int x)
{
	wz[x]=n+1;
	for(int i=1;i<=n;i++) cnt[i]=0;
	dfs1(1,1,1);
	for(int i=1;i<=n;i++)
	{
		cnt[i]+=cnt[i-1]; if(cnt[i]<i) return i;
	}
	return n;
}*/
void solve(int x)
{
	if(x==1) {return ans[x]=pp[1],wz[x]=1,usd[1]=1,cz1(1,n,1,1),void();}
	int nl=wz[fa[x]];
	cza(1,n+1,wz[fa[x]],n+1,-sz[x],1);
	cza(1,n+1,n+1,n+1,sz[x],1);
	int nr=ask2(1,n+1,1);
	pair<int,int> na=ask1(1,n,nl,nr,1);
	ans[x]=pp[na.se],wz[x]=na.se,usd[na.se]=1,cz1(1,n,na.se,1);
	cza(1,n+1,n+1,n+1,-sz[x],1);
	cza(1,n+1,na.se,n+1,sz[x],1);
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>pp[i];
	for(int i=1;i<=n-1;i++) cin>>u>>v,e[u].pb(v),e[v].pb(u);
	dfs0(1,1);
	build1(1,n,1);
	build2(1,n+1,1);
	for(int i=1;i<=n;i++) solve(i);
	for(int i=1;i<=n;i++) cout<<ans[i]<<" "; cout<<endl;
}
```

---

## 作者：Naib (赞：4)

#### [[ICPC2024 Xi'an I] Holes and Balls](https://www.luogu.com.cn/problem/P10560)

> 给定 $n$ 个节点的树，还有一个长度为 $n$ 的排列 $p$。这棵树满足对于任意的 $x < y$，都有 $dep_{x} \le dep_{y}$。
>
> 考虑对于一棵树的一个拓扑序，记 $s_{i}$ 表示点 $i$ 在拓扑序中的位置。求字典序最小的 $(p_{s_{1}},p_{s_{2}}\dots,p_{s_{n}})$。
>
> $n\le 5\times 10^5$。

对于一个点 $i$，考虑 $s_{i}=k$ 带来的限制：

即对于 $i$ 的子树，都要求 $s_{j} > k$。

注意到这个过程就是每个树上的点与排列上的一个点进行匹配，那么我们把合法条件转化成二分图存在完美匹配。

记 $lim_{i}$ 表示 $i$ 祖先中确定的 $s_{j}$ 的最大值。一个树上的点 $i$ 能够与排列 $j$ 匹配即 $j \ge lim_{j}$，即每个点能连出去的出边就是一段后缀。

考虑 Hall 定理：

存在完美匹配即对于任意的一个 $S$，他的临边 $nS$ 都满足 $|nS|\ge S$。这里 $|nS|$ 因为是后缀，所以只和 $S$ 中 $lim_{i}$ 最小的有关。设最小的 $lim_{i}=x$，那么肯定把所有的 $lim_{i} \ge x$ 的 $i$ 加入 $S$。

故最后我们能够推出存在完美匹配的充要条件即 $\forall i,\sum{[lim_{j}\ge i]} \le  n- i+1$。记 $f_{i}=\sum{[lim_{j}=i]}$，条件转化成 $\forall i,\sum_{j=i}^{n} f_{j} \le n-i+1$。

此时再来考虑按位贪心就很简单了，首先我们已知 $lim_{i}$ 的值。现在要决定 $s_{i}$ 的值，影响就是把 $i$ 的子树的 $lim_{j}$ 全部与 $s_{i}$ 取 $\max$。而$j > i$ 一定成立，所以 $lim_{j}$ 此时全部等于 $lim_{i}$，所以实际上对应的就是把 $f_{lim_{i}}$ 的 $siz_{i}$ 个数变成 $f_{s_{i}}$。考虑用线段树来维护 $n-i+1-\sum_{j=i}^{n}f_{j}$。那么对应到线段树上就是从 $lim_{i}+1$ 的一段区间减法。我们只需要找到最大的 $r$，使得 $[lim_{i}+1,r]$ 减完之后仍然合法，直接在线段树上二分即可。

求出了 $r$ 后，只需要再找到 $j\in[lim_{i}+1,r]$ 中最小的 $p_{j}$，注意到这个 $p_{j}$ 不能重复选，所以还需要一棵线段树维护。

复杂度 $O(n\log n)$。

---

## 作者：Graphcity (赞：2)

显然需要考虑贪心做法。

考虑我们如果已经给某些位置放入了一些球，判断是否存在合法方案数。注意到一个位置放了一个编号（不是权值）为 $k$ 的球，就意味着它的子树所有球的编号 $\ge k$。

注意到这类似于判断二分图是否存在完美匹配，考虑 Hall 定理。对于任意一个后缀，这个后缀的球数量一定要大于等于所有可匹配位置被这个后缀包含的位置数量。换一个角度，也就是任意一个前缀，这个前缀的球数量一定要小于等于所有可匹配位置跟这个前缀有交的位置数量。

令 $h_i$ 表示跟 $1\sim i$ 这个前缀有交的位置数量减去 $i$ 的结果，初始 $h_i=n-i$。在位置 $x$ 放入编号为 $k$ 的球后，需要把 $h_{1\cdots k-1}$ 减去 $siz_x$。我们要求任意时刻 $h_i\ge 0$。

注意到字典序最小化的条件，我们按照从小往大的顺序依次考虑每个位置放什么球。考虑位置 $x$ 时，我们可以用线段树二分找到最大的满足 $h_i\ge siz_x$ 的前缀。

那么我们放入的球一定是在这个前缀内，且比 $fa_x$ 放入的球编号更大，权值最小的那一个。也可以使用线段树实现。总时间复杂度 $O(n\log n)$。注意在考虑 $x$ 之前要把父亲结点对应 $h$ 的前缀加上 $siz_x$，因为我们对于每个点只考虑最强的限制。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5;

int n,fa[Maxn+5],h[Maxn+5],siz[Maxn+5],ans[Maxn+5];
int t[Maxn*4+5],mn[Maxn*4+5],tag[Maxn*4+5],id[Maxn+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p)
{t[p]=min(t[ls(p)],t[rs(p)]),mn[p]=min(mn[ls(p)],mn[rs(p)]);}
inline void mk(int p,int k) {t[p]-=k,tag[p]+=k;}
inline void push_down(int p)
{if(tag[p]) mk(ls(p),tag[p]),mk(rs(p),tag[p]),tag[p]=0;}
inline void Build(int l,int r,int p)
{
    if(l==r) {t[p]=n-l,mn[p]=h[l]; return;} int mid=(l+r)>>1;
    Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Modify(int nl,int nr,int l,int r,int p,int k)
{
    if(l>r) return; if(l<=nl && nr<=r) {mk(p,k); return;}
    int mid=(nl+nr)>>1; push_down(p);
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    if(r>mid) Modify(mid+1,nr,l,r,rs(p),k); push_up(p);
}
inline void Insert(int l,int r,int p,int k)
{
    if(l==r) {mn[p]=n+5; return;} int mid=(l+r)>>1; push_down(p);
    if(k<=mid) Insert(l,mid,ls(p),k); else Insert(mid+1,r,rs(p),k); push_up(p);
}
inline int Count(int nl,int nr,int l,int r,int p)
{
    if(l<=nl && nr<=r) return mn[p];
    int mid=(nl+nr)>>1,res=n+5; push_down(p);
    if(l<=mid) res=min(res,Count(nl,mid,l,r,ls(p)));
    if(r>mid) res=min(res,Count(mid+1,nr,l,r,rs(p)));
    return res;
}
inline int Find(int l,int r,int p,int k)
{
    if(l==r) return (t[p]<k?0:l);
    int mid=(l+r)>>1,res=0; push_down(p);
    if(t[ls(p)]>=k) res=Find(mid+1,r,rs(p),k);
    if(res) return res; else return Find(l,mid,ls(p),k);
}

int main()
{
    cin>>n; For(i,1,n) cin>>h[i],id[h[i]]=i;
    For(i,1,n-1)
    {
        int a,b; cin>>a>>b;
        if(a>b) swap(a,b); fa[b]=a;
    } Build(1,n,1);
    Rof(i,n,1) siz[i]++,siz[fa[i]]+=siz[i];
    For(i,1,n)
    {
        if(fa[i]) Modify(1,n,1,ans[fa[i]]-1,1,-siz[i]);
        int p=min(n,Find(1,n,1,siz[i])+1);
        ans[i]=id[Count(1,n,ans[fa[i]]+1,p,1)],Insert(1,n,1,ans[i]);
        Modify(1,n,1,ans[i]-1,1,siz[i]);
    }
    For(i,1,n) printf("%d ",h[ans[i]]); printf("\n");
    return 0;
}
```

---

## 作者：dAniel_lele (赞：1)

考虑逐位贪心。

不难发现对于每个节点，它可以选择的 $p_i$ 一定是一个区间。

当一个节点选择了一个 $p_i$ 后，它子树内的 $siz_i$ 个数一定放在了 $i$ 位置及以后。

加入一个节点的时候，自然就要求钦定 $p_i$ 后加入了 $siz_i$ 个数后所有位置的要求均满足。也就是说，对于每个位置的限制 $lim_i$，我们要求 $\sum_{j=i}^nlim_i\leq n-i+1$。

不难想到先给每个位置一个初始要求 $n,n-1,\dots,1$，每加入一条限制给前缀要求减去 $siz_i$。查询最后一个可以插入的位置可以使用线段树二分。

找到可选择的区间后，使用另一个线段树维护区间最小值位置，贪心选择最小值加入即可。

总复杂度 $O(n\log n)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
#define s(i,j) ((i-1)*m+j)
using namespace std;
struct node2{
	int minv,minpos;
};
int siz[1000005],p[1000005],dep[1000005],cpos[1000005],ff[1000005],n;
vector<int> vc[1000005],lev[1000005];
struct sgt{
	int minv[2000005],lzt[2000005];
	void pushdown(int i){
		lzt[i*2]+=lzt[i];
		lzt[i*2+1]+=lzt[i];
		minv[i*2]+=lzt[i];
		minv[i*2+1]+=lzt[i];
		lzt[i]=0;
	}
	void build(int i,int l,int r){
		if(l==r){
			minv[i]=n-l+1;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		minv[i]=min(minv[i*2],minv[i*2+1]);
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			minv[i]+=cg;
			lzt[i]+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		minv[i]=min(minv[i*2],minv[i*2+1]);
	}
	int qlpos(int i,int l,int r,int lim){
		if(l==r){
			if(minv[i]<lim) return l-1;
			else return l;
		}
		pushdown(i);
		if(minv[i*2]<lim) return qlpos(i*2,l,mid,lim);
		else return qlpos(i*2+1,mid+1,r,lim);
	}
}tree;
struct sgt2{
	node2 f[2000005];
	node2 merge(node2 x,node2 y){
		if(x.minv<y.minv) return x;
		return y;
	}
	void build(int i,int l,int r){
		if(l==r){
			f[i].minv=p[l];
			f[i].minpos=l;
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int pos){
		if(l==r){
			f[i].minv=1e9;
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos);
		else change(i*2+1,mid+1,r,pos);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	node2 qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return merge(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree2;
void dfs(int now,int fa){
	ff[now]=fa;
	siz[now]=1,dep[now]=dep[fa]+1,lev[dep[now]].push_back(now);
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		siz[now]+=siz[v];
	}
}
signed main(){
	cin>>n; for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
	}
	dfs(1,0);
	vector<int> ans;
	for(int i=1;i<=n;i++) sort(lev[i].begin(),lev[i].end());
	tree.build(1,1,n);
	tree2.build(1,1,n);
	for(int i=1;i<=n;i++){
		if(!lev[i].size()) break;
		for(auto v:lev[i]){
			if(ff[v]!=0) tree.change(1,1,n,1,cpos[ff[v]],siz[v]);
			int lpos=cpos[ff[v]]+1,rpos=tree.qlpos(1,1,n,siz[v]);
			cpos[v]=tree2.qry(1,1,n,lpos,rpos).minpos;
			tree2.change(1,1,n,cpos[v]);
			tree.change(1,1,n,1,cpos[v],-siz[v]);
			ans.push_back(p[cpos[v]]);
		}
	}
	for(auto v:ans) cout<<v<<" ";
	return 0;
}
```

---

