# [USACO22DEC] Making Friends P

## 题目描述

FJ 的 $N(2 \le N \le 2 \times 10^5)$ 头编号为 $1 \cdots N$ 的奶牛之中初始时有 $M(1 \le M \le 2 \times 10^5)$ 对朋友。奶牛们一头一头地离开农场去度假。第 $i$ 天，第 $i$ 头奶牛离开了农场，同时第 $i$ 头奶牛的所有仍在农场的朋友互相都成为了朋友。问总共建立了多少新的朋友关系？



## 说明/提示

### 样例 1 解释

第 $1$ 天，三个新的朋友关系被建立：$(3,4)$，$(3,7)$ 和 $(4,7)$。

第 $3$ 天，两个新的朋友关系被建立：$(4,5)$ 和 $(5,7)$。

### 测试点性质

 - 测试点 $2-3$ 满足 $N \le 500$。
 - 测试点 $4-7$ 满足 $N \le 10^4$。
 - 测试点 $8-17$ 没有额外限制。

## 样例 #1

### 输入

```
7 6
1 3
1 4
7 1
2 3
2 4
3 5```

### 输出

```
5```

# 题解

## 作者：EXODUS (赞：25)

# Part 1：前言
谢谢这道题让我意识到我在启发式合并方面一窍不通。

感觉这是 Pt 组最简单的一题

# Part 2：正文

考虑一个性质，每次互相连边显然有些多余，不妨转化成将编号最小的点和其它点连边。

考虑正确性，若一头牛 $x$ 出队，不妨设与他相连且编号大于他的牛的编号排序后的结果为 $y_1,y_2,...,y_k$，我们这种连边策略相当于延时连边，即在 $y_1$ 出队以前连接 $y_1\rightarrow y_2,y_3,\ldots y_k$，$y_2$ 出队以前连接 $y_2\rightarrow y_3,\ldots y_k$，每条应当连的边都被连上了至少一次，故存在充分性，所以正确。

直接连边复杂度是 $O(n^2)$，启发式合并 set 后复杂度是 $O(m\log^2n)$ 可以通过此题。



# Part 3：代码
```cpp
const int N=2e5+7;
int n,m;
set<int>g[N];

void Main(){
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		g[min(u,v)].insert(max(u,v));
	}
	ll ans=-m;
	for(int i=1;i<=n;i++){
		if(g[i].empty())continue;
		ans+=g[i].size();
		int u=*g[i].begin(),v=i;g[v].erase(g[v].begin());
		if(g[u].size()<g[v].size())swap(g[u],g[v]);
		for(auto i:g[v])g[u].insert(i);
	}
	cout<<ans;
	return;
}
```

---

## 作者：蒟蒻君HJT (赞：6)

## 转化：

观察一下样例，可以发现 $(u,v)$ 最后能成为朋友的充要条件是：

存在一条从 $u$ 到 $v$ 的路径，路径上经过的点的编号不大于 $\min(u,v)$ 。

简单证明：

充分性非常显然，下证必要性。

下面简称 $(u,v)$ 之间仅通过小于 $\min(u,v)$ 的点连通的路径为合法路径。

采用反证法，假设两个点 $u,v$，$u<v$，本来之间不存在合法路径，而最后直接相连了，那么自然它们最终满足"可以不经过大于 $\min(u,v)$ 的点连通"，即合法路径在最后出现了。

考虑它们之间第一次存在合法路径的时刻：去掉点 $p$ 前不存在合法路径，去掉点 $p$ 后存在合法路径。因为我们要求 $p$ 走掉后 $u,v$ 还得在场，所以 $p<\min(u,v)$。

设去掉点 $p$ 后边 $(s,p)$ 和 $(p,t)$ 变成了边 $(s,t)$，而 $(u,v)$ 的合法路径上经过 $(s,t)$ 这条边，于是 $s,t<\min(u,v)$。这样的话，在去掉 $p$ 之前，由于 $s,t,p$ 均小于 $\min(u,v)$ ，那么我们可以把合法路径上的 $(s,t)$ 换成 $(s,p),(p,t)$ ，说明去掉 $p$ 之前也是存在合法路径的，与假设矛盾。

因此，必要性得证，对于任意两点 $(u,v)$ 间，若初始不存在合法路径，则最终不可能直接连通。

## 实现：

对于所有点对 $(u,v),u<v$ 不妨枚举 $u$ 。

记 $S_x$ 表示所有与 $x$ 直接相邻的点所构成的集合。

当我们处理点 $x$ 时需要保证所有两端编号均不大于 $x$ 的边已经加进来了，用并查集维护加边的过程。然后，考虑 $x$ 所在连通块，其 
 $\bigcup S$ 中大于 $x$ 的点的个数就是我们要求的东西，**线段树合并**维护区间和即可。

注意去除初始时的朋友关系，即初始 $ans=-m$ 。复杂度 $\mathcal{O}(m+n\log n)$ 。

不介意复杂度多一个 $\log n$ 的话可以用启发式合并平衡树/堆维护 $\bigcup S$ 。
  
## 代码

```cpp
#include <bits/stdc++.h>
int n, m, d[200005], fa[200005];
long long s[200005];
long long ans = 0ll;
std::vector <int> v[200005];
const int M = 7000005;
int ls[M], rs[M], tot = 0, sum[M];
int root[200005];
int fd(int x){
	return x == fa[x] ? x : fa[x] = fd(fa[x]);
}
int Merge(int x, int y, int l, int r){
	if(!x || !y) return x | y;
	if(l == r){
		sum[x] = sum[x] | sum[y];
		return x;
	}
	int mid = l + r >> 1;
	ls[x] = Merge(ls[x], ls[y], l, mid);
	rs[x] = Merge(rs[x], rs[y], mid + 1, r);
	sum[x] = sum[ls[x]] + sum[rs[x]];
	return x;
}
int update(int x, int l, int r, int y){
	if(!x) x = ++tot;
	if(l == r){
		sum[x] = 1;
		return x;
	}
	int mid = l + r >> 1;
	if(y <= mid) ls[x] = update(ls[x], l, mid, y);
	else rs[x] = update(rs[x], mid + 1, r, y);
	sum[x] = sum[ls[x]] + sum[rs[x]];
	return x; 
}
int ask(int x, int l, int r, int L, int R){
	if(!x) return 0;
	if(l == L && r == R) return sum[x];
	int mid = l + r >> 1;
	if(R <= mid) return ask(ls[x], l, mid, L, R);
	else if(L >= mid + 1) return ask(rs[x], mid + 1, r, L, R);
	return ask(ls[x], l, mid, L, mid) + ask(rs[x], mid + 1, r, mid + 1, R);
}
inline void merge(int x, int y){
	x = fd(x), y = fd(y);
	if(x == y) return ;
	fa[y] = x;
	root[x] = Merge(root[x], root[y], 1, n);
	return ;
}
int main(){
	scanf("%d%d", &n, &m);
	ans = -1ll * m;
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int j = 1; j <= m; ++j){
		int x, y;
		scanf("%d%d", &x, &y);
		if(x > y) std::swap(x, y);
		v[y].push_back(x);
		root[x] = update(root[x], 1, n, y);
	}
	for(int i = 1; i <= n; ++i){
		for(int j = 0; j < v[i].size(); ++j)
			merge(i, v[i][j]);
		if(i != n)
			ans = ans + 1ll * ask(root[fd(i)], 1, n, i + 1, n);
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Idtwtei (赞：5)

> $n$ 个点 $m$ 条边的无向图，按编号从小到大依次删点，每次删点后将其邻点补成完全图，求新增边数。
> 
> $1 \le n,m \le 2 \times 10^5$。

最后 $(i,j)(i < j)$ 有连边当前仅当原图存在 $i \to j$ 的路径使得路径上点（除 $j$ 外）的编号均 $\le i$。

考虑枚举 $i$ 统计上述点对的数量，最后减去 $m$ 即为答案。

按编号从小到大枚举 $i$，枚举过的点标 $1$，未枚举的标 $0$。那么 $j$ 的数量即为 $i$ 所在的 $1$ 连通块相邻的 $0$ 点的数量。

用并查集维护连通块，用 `set` 记录相邻的 $0$ 点。当枚举到 $i$ 时，先将相邻的 $0$ 点加入对应的 `set`，再与相邻的 $1$ 点合并，$j$ 的数量即为对应 `set` 的大小。启发式合并，时间复杂度 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

using ll=long long;
#define pb push_back
#define U(x) ((int)x.size())
const int N=2e5+100;
#define gc getchar()
#define rd read()
inline int read(){
	int x=0,f=0; char c=gc;
	for(;c<'0'||c>'9';c=gc) f|=(c=='-');
	for(;c>='0'&&c<='9';c=gc) x=(x<<1)+(x<<3)+(c^48);
	return f?-x:x;
}

int n,m; ll ans=0;
vector<int> G[N];

int fa[N],siz[N]; set<int> s[N];
void init(){ for(int i=1;i<=n;++i) fa[i]=i,siz[i]=1; }
int find(int x){ return fa[x]==x?x:fa[x]=find(fa[x]); }
void mer(int x,int y){
	x=find(x),y=find(y); if(x==y) return;
	if(siz[x]<siz[y]) swap(x,y);
	fa[y]=x,siz[x]+=siz[y]; for(auto v:s[y]) s[x].insert(v);
}

int main(){
	
	n=rd,m=rd,init();
	for(int i=1,x,y;i<=m;++i) G[x=rd].pb(y=rd),G[y].pb(x);
	for(int u=1;u<=n;++u){
		for(int v:G[u]) if(v>u) s[u].insert(v);
		for(int v:G[u]) if(v<u) mer(v,u);
		if(s[find(u)].count(u)) s[find(u)].erase(u); //此时 u 不是 0 点，如果有要删去。
		ans+=U(s[find(u)]);
	}
	
	printf("%lld\n", ans-m);
	
	return 0;
}
```

---

## 作者：vectorwyx (赞：4)

一条边 $(i,j)$ 会产生贡献当且仅当存在一条 $i\to j$ 的路径满足这条路径除 $i,j$ 之外的所有点都小于 $i,j$。我们钦定 $i<j$，从小到大把每个点依次加入。加入 $i$ 时，$i$ 产生的总贡献就是 $i$ 能到达的点中大于 $i$ 的点的个数。开 $n$ 个平衡树，初始时把点 $i$ 的邻居都插入到点 $i$ 对应的平衡树中，然后启发式合并维护连通块信息。视 $n,m$ 同阶，复杂度为 $O(n\log^2n)$。

代码如下：
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace __gnu_pbds;
#define Tree tree<int,null_type,greater<int>,rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

//14:54~15:12~15:13
const int N=2e5+5;
vector<int> e[N];
ll ans;
int n,m,f[N],siz[N];
Tree a[N];

int fin(int x){
	if(f[x]==x) re f[x];
	re f[x]=fin(f[x]);
}

void merge(int x,int y){
	int fx=fin(x),fy=fin(y);
	if(fx==fy) re;
	if(siz[fx]>siz[fy]) swap(fx,fy);
	f[fx]=fy,siz[fy]+=siz[fx];
	for(auto i:a[fx]) a[fy].insert(i);
	Tree tmp;swap(a[fx],tmp);
}

signed main(){
	cin>>n>>m;ans-=m;
	fo(i,1,n) f[i]=i,siz[i]=1;
	fo(i,1,m){
		int x=read(),y=read();
		e[x].eb(y),e[y].eb(x);
		a[x].insert(y);a[y].insert(x);
	}
	fo(i,1,n){
		for(int j:e[i]) if(j<i) merge(i,j);
		ans+=a[fin(i)].order_of_key(i);
	}
	cout<<ans;
	return 0;
}
}










signed main(){re vectorwyx::main();}

```

---

## 作者：luoguhandongheng (赞：3)

（2024NOV10th，Nothing to say）

注意到题目要求按编号从小到大删点。

当我们要删掉 $u$ 时，$ans \gets ans+|e_u|$，$e_u$ 表示 $u$ 的邻居集合。并且不需要将它的邻居两两连边。只需要大家都向邻居中最小的连边就可以。

这实际上是一个类似延迟标记的操作。假设 $u$ 的邻居中编号最小的为 $j$。$j \to v_1,v_2,v_3,\dots$，$v$ 是 $u$ 的邻居。当删去 $j$ 时，$j$ 向 $v_1,v_2,v_3,\dots$ 连边的贡献都会在 $|e_j|$ 中包括。那像 $v_1\to v_2$ 这样的关系什么时候加呢？答案是当删 $v_1$ 的时候被计算。如果说 $j$ 的邻居中最小的是 $v_1$，那么 $v_1 \to v_2,v_3 \dots$。如果不是，那么就会有最小的邻居 $j' \to v_1,v_2,v_3 \dots$，由于比 $v_1 $ 小的邻居总会在 $v_1$ 之前被删掉，所以 $v_1$ 总会变成最小的邻居。所以类似 $v_1\to v_2$ 的朋友关系一定会被计算，这样统计出的答案是不漏的。

视 $M$ 与 $N$ 同阶。直接连边复杂度 $O(N^2)$。注意到这个东西可以用权值线段树维护。对每个点 $u$ 都建一棵动态开点线段树，如果 $v$ 是 $u$ 的邻居就标记为 $1$，否则就为 $0$。维护全局为 $1$ 的中的最小值和为 $1$ 的个数。$j$ 向 $u$ 的邻居连边的时候，就相当于把 $u$ 的线段树和 $j$ 的线段树合并。时间复杂度 $O(N \log N)$。

答案 $ans$ 一开始设为 $-M$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5,inf=1e9;
struct node{
    int ls,rs;
    int val=inf,siz=0;
}tree[N*32];
int cnt,rt[N],n,m;
void pushup(int u){
    tree[u].val=min(tree[tree[u].rs].val,tree[tree[u].ls].val);
    tree[u].siz=tree[tree[u].ls].siz+tree[tree[u].rs].siz;
}
int update(int p,int pl,int pr,int x){
    int rt;
    if(!p)
        rt=++cnt;
    else
        rt=p;
    if(pl==pr){
        tree[rt].val=x,tree[rt].siz=1;
        return rt;
    }
    int mid=(pl+pr)>>1;
    if(x<=mid)
        tree[rt].ls=update(tree[rt].ls,pl,mid,x);
    else 
        tree[rt].rs=update(tree[rt].rs,mid+1,pr,x);
    pushup(rt);
    return rt;
}
void ins(int u,int v){
    rt[u]=update(rt[u],1,n,v);
}
void del(int p,int pl,int pr,int x){
    if(pl==pr){
        tree[p].val=inf;
        tree[p].siz=0;
        return ;
    }
    int mid=(pl+pr)>>1;
    if(x<=mid)
        del(tree[p].ls,pl,mid,x);
    else
        del(tree[p].rs,mid+1,pr,x);
    pushup(p);
}
int merge(int u,int v,int pl,int pr){
    if(!u || !v) return u+v;
    if(pl==pr){
        return u;
    }
    int mid=(pl+pr)>>1;
    tree[u].ls=merge(tree[u].ls,tree[v].ls,pl,mid);
    tree[u].rs=merge(tree[u].rs,tree[v].rs,mid+1,pr);
    pushup(u);
    return u;
}
int top(int x){
    return tree[rt[x]].val;
}
void erase(int x,int y){
    del(rt[x],1,n,y);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int u,v;
        cin>>u>>v;
        ins(min(u,v),max(u,v));
    }
    ll ans=-m;
    for(int i=1;i<=n;++i){
        int x=top(i);
        ans+=tree[rt[i]].siz;
        if(x!=inf){
            erase(i,x);//注意这里要先把x从i中删掉再合并，不然就会有自环。
            rt[x]=merge(rt[x],rt[i],1,n);
        }
    }
    cout<<ans<<'\n';
    return 0;
}

```

---

## 作者：Kx_Triumphs (赞：3)

原题看[这里](https://www.luogu.com.cn/problem/P8907)。

## 简化题意

给定 $n$ 个点和 $m$ 条边，要求从小到大删点，把要删除的点的子节点相连，问有多少条**新边**（重边只看作 $1$ 条新边）。

### 思路

- 由于按编号从小到大删点，所以编号越大的点连的边越多，编号越小的点连边越少。编号小的点由于被删了，所以并不会再与后面的点连边了。
- 考虑到每删一个点，会如下图般连边，如 $2$ 和 $4$ 两点。

![P8907-1](https://cdn.luogu.com.cn/upload/image_hosting/g732sla2.png)

- 因为题目要求每两个点如果建立关系，那么只会建立一次，所以，我们每次删点时，可以把与这个点连边的点集中**编号最小**的点取出来，然后再将点集中的其他点，合并到取出来的这个点上。这样相当于在点 $2$ 完成了**部分**在点 $1$ 的子节点的相互连边操作，以此类推。

![P8907-2](https://cdn.luogu.com.cn/upload/image_hosting/klwtfjf0.png)

- 所以可以使用**启发式合并**或者**线段树合并**来完成合并的操作，时间复杂度分别是 $O(n\log^2 n)$ 和 $O(n\log n)$ ，都可以顺利通过此题。

### 代码

由于本人太菜，只展示**启发式合并**代码。

```cpp
#include<iostream>
#include<set>
using namespace std;
const int N=2e5+5;
int n,m;
set <int> e[N];
int main(){
    freopen("duck.in","r",stdin);
    freopen("duck.out","w",stdout);
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&u,&v);
		e[min(u,v)].insert(max(u,v));
	}
	//因为会统计能连的所有边,所以减去原先就有的边
	long long ans=-m;
	for(int i=1;i<=n;i++){
		if(e[i].empty()) continue;
		u=i;
		v=*e[u].begin();
		ans+=e[i].size();
		e[u].erase(e[u].begin());
		if(e[v].size()<e[u].size()) swap(e[u],e[v]);
		for(auto j:e[u]) e[v].insert(j);
	}
	printf("%lld\n",ans);
	
	return 0;
}
```

---

## 作者：hamster000 (赞：3)

Update2：根据rqy大佬的指导，线段树合并部分可以去掉并查集，原因是通过启发式合并的代码可以看出每次取出最小的元素，延迟维护是可以做的，那么根本不需要并查集，把set的算法复用到线段树上就可以节省一次区间查询，复杂度减少，也不会自己合并自己。文后补充上rqy大佬的代码。

Update1：修改了一些事实错误，哈希是不可以用的（如果你自己写一个哈希函数支持大小比较就当我没说），线段树时间复杂度就是 $n\log n$，以及启发式合并的复杂度也要重新分析了。感谢_rqy大佬。[rqy](rqy.moe)。

前置知识：线段树合并。

简单介绍一下线段树合并：把两颗权值线段树对应位置相加得到一颗新的线段树。

关于垃圾回收：本题垃圾回收不能节省空间，原因不明，实测垃圾回收比不回收空间还大且时间长得多。仅供参考。

Update：原因已查明：删除节点之后不会再加入，因此垃圾回收的节点并不能再次使用，相当于浪费了一倍时间。

本题采用的线段树合并的思路之前已经有题解说过了，下面主要是写一下自己的看法。本题要求的是产生了多少朋友，那么我们考虑这样一个问题：什么样的两个对象能在离开前成为朋友。

事实上只要存在一条路径使得路径上所有点都满足小于路径两头的两个对象且不存在直接从 $u \to v$ 的路径（这意味着一开始就是朋友）就可以了，也就是存在一条路径使路径上每个点编号小于 $\min(u,v)$。理性的证明下面有了，我讲一下感性的证明：假设对于所有路径都有中间某个点 $p$ 的编号大于 $\min(u,v)$ 且 $u$，$v$ 一开始不是朋友，那么当 $v$  或 $u$  离开后 $p$  还没有离开，也就是 $p$   这个路径上的关键点无法通过，于是所有路径都无法通过，得出 $u$，$v$  一开始就是朋友，矛盾。此为必要性。
 
假设从 $u$ 到 $v$ 有至少一条路径满足条件却最终不是朋友，那么假设路径上走不通的任意一点是 $q$，满足  $q<\min(u,v)$，此时容易想到 $q$ 的两侧必有一条路径存在编号大于 $q$ 的点，否则必然可以通过 $q$ 连接，然后递归考虑 $q$ 直到 $q$ 与 $u$ 或 $v$ 直接相连，推出 $q>u$ 或 $q>v$，矛盾，于是不存在点 $q$。此为充分性。

于是我们考虑线段树合并的实现方法了。

由于点对有两个参数不易于枚举，故只枚举小的那个，用邻接表从大向小连边即可，具体代码如下：

```cpp
for(int j=1;j<=m;j++){
    int x,y,tmp;
    cin >> x >> y;
    if(x>y) tmp=x,x=y,y=tmp;//确保连边方向从大到小
    vec[y].push_back(x);
}
```
与此同时，我们发现，统计新的朋友关系可以统计所有朋友关系然后减去原有的朋友关系，于是我们不需要去除一开始就有的朋友情况了，那么线段树合并的一切障碍都扫清了。

那么如何合并呢？会不会出现自己合并自己的情况呢？当然会。

如果对于任意两条边简单粗暴的直接 $merge(a,b,1,n)$，就会出现已经是朋友的人再被合并，因此考虑并查集维护朋友。与此同时，当我们处理一个点的所有出边时必须保证比这个点编号小的边处理完了，然后并查集维护连通块，连通块中比这个点更大的点的个数就是朋友的数量（这也是确保连边方向从大到小的优势——确保初始的朋友一定会被计算在内，最后减去初始朋友数量即可）。

然后就是线段树合并的部分了——我们对每个点开一颗权值线段树，说明这个点和某个点是朋友（注意细节，叶子节点的合并要用按位或而不是加法，因为朋友不能重复计算），然后维护区间和就知道对于在某个连通块中，有几个朋友是比自己大的，把这个朋友数量加到答案中去。

以下是线段树合并的AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+50;
int root[maxn],lc[80*maxn],rc[80*maxn],sum[80*maxn];//存动态开点线段树
int ans,tot;
vector <int> vec[maxn];//存图
int del[maxn*80],cnt;
int newnode(){
	if(cnt) return del[cnt--];
	return ++tot;
}
void erase(int pos){del[++cnt]=pos;
	lc[pos]=rc[pos]=sum[pos]=0;
	
}//以上几行是垃圾回收模板，事实上newnode直接改成++tot是一个效果的。
int n,m,fa[maxn];
int find(int x){//并查集的路径压缩
	return x==fa[x]?x:fa[x]=find(fa[x]);
}

int Merge(int a,int b,int l,int r){
	if(!a||!b) return a|b;//如果只有一颗树存在，直接取即可
	if(l==r){
		sum[a]=sum[a]|sum[b];//不能用加法，否则会导致同一个人被算多次
		erase(b);//b子树永远不会用到了
		return a;
	}
	int mid=(l+r)/2;
	lc[a]=Merge(lc[a],lc[b],l,mid);//递归合并左右子树
	rc[a]=Merge(rc[a],rc[b],mid+1,r);
	sum[a]=sum[lc[a]]+sum[rc[a]];
	erase(b);//同上方，直接删掉避免炸空间
	return a;
	
}

int modify(int rt,int l,int r,int pos){
	if(!rt) rt=newnode();//经典动态开点，垃圾回收就不说了。
	if(l==r) {
		sum[rt]=1;
		return rt;//不传引用是因为我传引用的写挂了。
	}
	int mid=(l+r)/2;
	if(pos<=mid) lc[rt]=modify(lc[rt],l,mid,pos);
	else rc[rt]=modify(rc[rt],mid+1,r,pos);
	sum[rt]=sum[lc[rt]]+sum[rc[rt]];
	return rt;
}

int query(int rt,int l,int r,int L,int R){
	if(!rt) return 0;
	if(l==L&&r==R) return sum[rt];
	int mid=(l+r)>>1;
	if(R<=mid) return query(lc[rt],l,mid,L,R);
	else if(L>=mid+1) return query(rc[rt],mid+1,r,L,R);
	return query(lc[rt],l,mid,L,mid)+query(rc[rt],mid+1,r,mid+1,R);
}

void merge(int a,int b){
	a=find(a),b=find(b);//并查集的合并和线段树合并同时进行。
	if(a==b) return;
	fa[b]=a;
	root[a]=Merge(root[a],root[b],1,n);//第a颗线段树和第b颗线段树进行合并。
	return ;
}

signed main(){
	cin >> n >> m;
	ans-=m;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int j=1;j<=m;j++){
		int x,y,tmp;
		cin >> x >> y;
		if(x>y) tmp=x,x=y,y=tmp;//确保连边方向从大到小
		vec[y].push_back(x);
		root[x]=modify(root[x],1,n,y);
	}
	for(int i=1;i<=n;i++){
		for(auto to:vec[i]){
			merge(i,to);
		}
		if(i<n) ans+=query(root[find(i)],1,n,i+1,n);
	}
	cout << ans  << endl;
}
```

时间复杂度大常数 $n \log n$，考虑并查集没有启发式合并所以复杂度可能会被丧心病狂的出题人卡到 $\log$，根据姚期智和塔扬的论文，平均复杂度仍为 $\alpha(n)$，两个复杂度取  $\operatorname{sum}$，仍为 $n\log n+\alpha(n)=n \log n$。空间复杂度小常数 $n\log n$，可以用科技优化到大常数线性但没必要，因为我也不熟练这个科技。

然后我们惊奇地发现，这题双 $\log$ 能过。

于是我们不需要线段树合并了，直接朴素的启发式合并也可以——对于每个元素，总是把小的连通块暴力塞进大连通块中，那么这个元素最多作为小集合的元素放进大集合的元素中 $\log n$ 次，每次合并最多消耗 $\log n$ 时间，所以每个元素被移动的时间消耗不多于 $\log^2 n$，有 $n$ 个元素，总复杂度 $n\log^2 n$，但是跑起来比线段树合并快一点，实际上你可以哈希优化到 $n\log n$，不过需要手写散列表且常数不小没必要。

由于被指出疏漏，此处补充介绍为什么不用并查集：

每次只要找最小的比当前处理奶牛编号大的那个朋友进行延迟连边，之后该连接的边会通过那个朋友再连接上去，因为每次取的朋友都是最小的，后面的朋友一定比最小的朋友后离开。相当于变成 $m\log^2 n$ 并查集复杂度被去掉了。但是我在写线段树合并的时候没有想到这一点。

AC Code：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
set <int>s[200005];
long long ans;

int main(){
    cin >> n >> m;
    int x,y;
    for(int i=1;i<=m;i++){
        cin >> x >> y;
        if(x>y) swap(x,y);
        s[x].insert(y);
    }
    for(int i=1;i<=n;i++){
        if(s[i].empty()) continue;
        ans+=s[i].size();
        int u=*s[i].begin();
        s[i].erase(s[i].begin());
        if(s[u].size()<s[i].size())swap(s[u],s[i]);
        for(auto v:s[i]) s[u].insert(v);
    }
    cout << ans-m << endl;
    return 0;
}
```
短且好写，且比不加优化的线段树合并更快，因为动态开点的常数巨大。如果数据范围到 $2\times 10^6$，我觉得线段树合并会更有优势。

Code Update：

rqy 对我进行了大力指导并找到了我为什么跑得慢的根源：线段树合并也不需要并查集，因为之前启发式合并正确性的证明对线段树合并依然有效。你其实只是需要一个支持合并、去重、统计总个数，单点修改的数据结构，于是 set 与线段树等价且作用基本相同。



rqy's AC Code比我快约一倍，只比set略慢一点：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200050;
int root[maxn],lc[20*maxn],rc[20*maxn],sum[20*maxn];
int tot;
inline int newnode(){
    return ++tot;
}
int n,m;

int Merge(int a,int b,int l,int r){
    if(!a||!b) return a|b;
    if(l==r) return a;
    int mid=(l+r)/2;
    lc[a]=Merge(lc[a],lc[b],l,mid);
    rc[a]=Merge(rc[a],rc[b],mid+1,r);
    sum[a]=sum[lc[a]]+sum[rc[a]];
    return a;
}

void modify(int &rt,int l,int r,int pos){
    if(!rt) rt=newnode();
    if(l==r) {
        sum[rt]=1;
    } else {
        int mid=(l+r)/2;
        if(pos<=mid) modify(lc[rt],l,mid,pos);
        else modify(rc[rt],mid+1,r,pos);
        sum[rt]=sum[lc[rt]]+sum[rc[rt]];
    }
}

int pop(int &rt,int l,int r) {
    if (l==r) {
        rt=0;
        return l;
    }
    int mid=(l+r)/2,ans;
    if(lc[rt]) ans=pop(lc[rt],l,mid);
    else ans=pop(rc[rt],mid+1,r);
    if(!--sum[rt])rt=0;
    return ans;
}

int main(){
    cin >> n >> m;
    long long ans = -m;
    for(int j=1;j<=m;j++){
        int x,y,tmp;
        cin >> x >> y;
        if(x>y) tmp=x,x=y,y=tmp;
        modify(root[x],1,n,y);
    }
    for(int i=1;i<=n;i++){
        if (!root[i]) continue;
        ans+=sum[root[i]];
        int u=pop(root[i],1,n);
        root[u]=Merge(root[u],root[i],1,n);
    }
    cout << ans << endl;
}
```
其中，$pop$ 函数指的是取出权值线段树里最小的数字。

以上就是这题全部思路了。

---

## 作者：YBJ1006 (赞：1)

启发式合并。

对于 $i$ 的离开，受到影响的只有编号大于 $i$ 的奶牛。所以保存朋友关系时，只需要保存比自己编号大的即可。

合并朋友关系时，如果把所有朋友都建立关系是不必要的，会重复很多，考虑只将 $i$ 的编号最小的朋友 $t$ 与其他所有朋友建立关系，这样的话到 $t$ 离开时照样会把剩下的朋友关系建立。

在 $t$ 与其他所有朋友建立关系时，其实就是将 $t$ 的朋友集合，与 $i$ 的朋友集合合并，此时使用启发式合并。


```cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 10;
set<int>st[N];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        st[min(x, y)].insert(max(x, y));
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (st[i].size() > 0)
        {
            int x = *st[i].begin();
            st[i].erase(x);
            if (st[x].size() < st[i].size())
            {
                swap(st[x], st[i]);
                ll c = 0;
                ll k = st[x].size();
                for (auto it : st[i])
                {
                    if (st[x].count(it) == 0)
                    {
                        st[x].insert(it);
                    }
                    else
                    {
                        c++; //重叠
                    }
                }
                ans += 1ll*k -  c;
            }
            else
            {
                for (auto it : st[i])
                {
                    if (st[x].count(it) == 0)
                    {
                        st[x].insert(it);
                        ans++;
                    }
                }
            }

            st[i].clear();
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：IamZZ (赞：1)

**P组练习总结#4**

### 题目大意

FJ 的农场中有 $n(n\le 2\times10^5)$ 只奶牛，其中有 $m(m\le2\times10^5)$ 对老朋友，如今奶牛们迎来了假期，是时候考虑交新朋友了！

具体的，在第 $i(i\le n)$ 天，$i$ 号奶牛会离开农场享受生活，这时，$i$ 号奶牛现在还在农场的朋友们会互相交个朋友，这样又能交到新朋友啦！

现在奶牛们想知道，这 $n$ 天下来，可以有多少对**新**朋友出现？注意，老朋友们不算哦。

### 题解思路

刚刚被 Platinum 组的抽象题目们创飞了，找到一道简单一点的，休息一下~~CPU 都烧了~~。

这道题目虽然实现起来很简单，但是思想还是很精妙的，能自己想出来，值得记录一下。 

最朴素的想法，删掉一个点直接暴力模拟，该连边的全都一个个连上，很明显，这个复杂度是 $\Theta(n^3)$ 的。

考虑优化，我们发现，在暴力连边时，慢慢的，很多很多边已经连好了，如果我们大费周章去操作连过的边，将会浪费大量的时间。

观察到整道题的处理有顺序，从小到大，那我们思考能不能找到一个点先暂时记录下以后要连的边，然后随着操作的进行，每条边都慢慢连好了。

有这么神奇的点吗？有的，那就是目前与 $i$ 相连的点中编号最小的点 $j$，我们把与 $i$ 相连的点都向它连边，完全图居然就可以一步步连好了！

考虑正确性，首先，在与 $i$ 相连的点中，最先处理到的肯定是 $j$，这时，比 $j$ 小的点都已经去旅游了，比 $j$ 大的点都还在，也都记录下来了。

于是我们就及时处理 $j$ 点的连边情况，可以算答案了！

方法十分巧妙，不求一开始就知道整个图，而是借助时间顺序和完全图的性质巧妙地优化，好题！

### 具体实现

set 好啊，方便合并，求最小点也快，还可以防止有重边！

我们发现只有 $i$ 连向比自己编号大的点才可能被算贡献，所以 set 只记录比自己大的点，比自己小的点都会在自己之前被删掉，没有贡献。

合并的时候，采用启发式合并，两个中小的那个 set 并入大的 set 里面，复杂度多个 $\log_2n$ ，总复杂度 $\Theta(n\log_2^2n)$ 。

答案计算只需要累加目前 $i$ 点的边数减去一开始的，求变化量就好了。

完结撒花(●'◡'●)

### 参考代码

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=2e5+5;
int n,m,x,y,c[N],p;
set<int>h[N];
ll s;
void merge(int x,int y)//合并
{
	if(h[x].size()<h[y].size())//判断哪个大
	  swap(h[x],h[y]);//小了就换
	while(h[y].size())//一个一个扔进去
	{
		h[x].insert(*h[y].begin());
		h[y].erase(h[y].begin());
	}
	return ;
}
int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;++i)
	{
		scanf("%d%d",&x,&y);
		if(x>y)
		  swap(x,y);
		h[x].insert(y);
	}
	for(i=1;i<=n;++i)
	  c[i]=h[i].size();
	for(i=1;i<=n;++i)
	{
		if(!h[i].size())
		  continue;
		while(*h[i].begin()<=i)//一直删除已经删掉的点
		  h[i].erase(h[i].begin());
		s=s+h[i].size()-c[i];
		if(h[i].size()<=1)
		  continue;
		p=*h[i].begin();
		h[i].erase(h[i].begin());//不要加自己哦，自环可不好
		merge(p,i);//合并最小编号的点
	}
	printf("%lld",s);
	return 0;
}
```



---

## 作者：win114514 (赞：1)

明明看着不难的题目，却意外的卡人。

### 思路

考虑两头奶牛可以成为朋友条件是什么。

存在一条路径连接这两头奶牛。

且除去端点外的路径上的所有点的编号小于两端点的较小值。

充分必要性都比较显然。

如何维护。

我们可以从小到大加入点，维护这些路径。

对于每个点维护一个 $\text{set}$。

表示这个点所在的联通块可以去到的还没有加进来的点有多少个。

因为没有加进来的点都比已经加进来的点要大。

那么可以启发式合并维护一下就可以了。

### Code

```cpp
/**
 * @file P8907.cpp
 * @author win114514
 * @date 2023-11-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 1000010;
const int mod = 998244353;

int n, m, fa[N]; i64 ans = 0;
vector<int> to[N];
set<int> q[N];

inline void merge(int x, int y)
{
	if(q[x].size() < q[y].size())
		swap(q[x], q[y]);
	for(auto i : q[y]) q[x].insert(i);
	q[y].clear();
}
inline void calc(int x, int y)
{
	while(q[x].empty() == 0 && *q[x].begin() <= y)
		q[x].erase(q[x].begin());
}
inline int gf(int x)
	{ return fa[x] == x ? x : fa[x] = gf(fa[x]); }
inline void solve()
{
	cin >> n >> m;
	fro(i, 1, m)
	{
		int x, y;
		cin >> x >> y;
		to[x].push_back(y);
		to[y].push_back(x);
	}
	iota(fa + 1, fa + n + 1, 1);
	fro(i, 1, n)
	{
		sort(to[i].begin(), to[i].end());
		for(auto j : to[i]) if(j > i)
			q[i].insert(j);
		int num = q[i].size();
		for(auto j : to[i]) if(j < i && i != gf(j))
			merge(i, gf(j)), fa[gf(j)] = i;
		calc(i, i), ans += q[i].size() - num;
	}
	cout << ans << "\n";
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 256;
	cerr << " Memory: " << Mib << "\n", assert(Mib<=Lim);
	solve();
	return 0;
}
```

---

## 作者：kevinZ99 (赞：0)

# 题意

对于一个 $n$ 个点的图，有 $m$ 条边，第 $i$ 天第 $i$ 个点会消失，并将它连向的边互相连接，即将他连向的那些点形成一个完全图。

# 思路

很明显通对于一个点 $i$ 和它连向的点集 $V_{i}$ 若 $i$ 离开后最早会需要用到点集 $V_{i}$ 的点就是 $V_{i}$ 中的点的编号的最小值，所以我们考虑启发式合并，对于一个点 $i$ 我们将它记录好答案后只将点集 $V_{i}$ 放到 $V_{i}$ 中编号最小的点的点集中即可。

这个过程中需要去重还需要排序，所以 ```set``` 即可。

# 代码

```cpp
//Author:Kevin Z K Y
#include <bits/stdc++.h>
#define up(a,b,c) for(int (a)=(b);(a)<=(c);(a)++)
#define dn(a,b,c) for(int (a)=(b);(a)>=(c);(a)--)
#define fst first
#define sed second
using namespace std;
using ull = unsigned long long ;using ui = unsigned int ;
using ll = long long ;using hint = __int128 ;
using pii = pair<int,int> ;using pll = pair<ll,ll> ;
using vi = vector<int> ;using vl = vector<ll> ;
using vpi = vector<pii> ;using vpl = vector<pll> ;
using db = double ;namespace mystl{
	#define gc() getchar()
	ll qpow(ll a,ll b,const ll&p){if (a==0ll) return 0ll; ll c=1ll;
		while(b) { if(b & 1) c=a*c%p; a=a*a%p; b>>=1; } return c; }
	template<typename T>void read(T&x) {x=0; bool f=false; char ch;
		ch = gc(); while(ch<'0'||ch>'9') f |= ( ch=='-') , ch=gc();
		while(ch>='0'&&ch<='9') x=x*10+ch-'0' , ch=gc(); x=f?-x:x;}
	template<typename T>void write(T x){char s[40];short d=0;T y=x;
		if(x<0) putchar('-'),y=-y;if(x==0){ putchar('0'); return; }
		while(y){s[++d]=y%10+'0';y/=10;}while(d>0)putchar(s[d--]);}
	template<typename T>void wris(T x,char c){write(x);putchar(c);}
}using namespace mystl;
namespace my{
	const int N=(int)(2e5+5);
	set<int>a[N];
	void solve(){
		int n,m;cin>>n>>m;
		up(i,1,m){
			int x,y;cin>>x>>y;if(x==y)continue;
			a[min(x,y)].insert(max(x,y));
		}ll ans=0;up(i,1,n){
			if(a[i].size()==0)continue;
			int to=*(a[i].begin());
			ll frt=a[to].size(),p=a[i].size();
//			cout<<"set:\n";
//			for(int v:a[i])cout<<v<<' ';cout<<'\n';
//			for(int v:a[to])cout<<v<<' ';cout<<'\n';
			if(frt>p){
				for(int v:a[i])
					if(v!=to)
						a[to].insert(v);
			}
			else {
				for(int v:a[to])
					a[i].insert(v);
				a[to].swap(a[i]);
			}
			auto it=a[to].find(to);
			if(it!=a[to].end())	
				a[to].erase(it);
			a[i].clear();
//			cout<<i<<' '<<to<<'\n';
//			for(int v:a[to])cout<<v<<' ';
//			cout<<'\n';
			ans+=(1ll*a[to].size()-frt);
		}cout<<ans<<'\n';
	}
}
int main(){
//  freopen("","r",stdin);
//  freopen("","w",stdout);
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	int _=1;while(_--)my::solve();return 0;
}

```

---

