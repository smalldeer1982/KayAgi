# COT - Count on a tree

## 题目描述

# 本题必须使用 C++98 提交

给你一棵有n个结点的树，节点编号为1~n。

每个节点都有一个权值。              

要求执行以下操作：

U V K：求从节点u到节点v的第k小权值。

## 样例 #1

### 输入

```
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
2 5 2
2 5 3
2 5 4
7 8 2 ```

### 输出

```
2
8
9
105
7 ```

# 题解

## 作者：xfrvq (赞：11)

[SP10628 COT - Count on a tree](/problem/SP10628)

## 扯淡

定义 $n,m$ 同阶。

首先，通过分析大多数 根号数据结构 和 $\log$ 数据结构，可以得出

+ 根号套根号，复杂度仍是根号（如分块套莫队，序列分块套值域分块）
+ $\log$ 套 $\log$，复杂度是多个 $\log$ 相乘（如树剖套线段树，树套树）。
+ 根号和 $\log$ 之间不太兼容，它们套起来是 $n\sqrt n\log n$，跑 $10^5$ 都非常吃力。

首先这个题是树上询问一些不太好做的东西，考虑树上莫队，它还要套上一个可以求 $k$ 大的东西，考虑平衡树。

但是我说过根号是不能和 $\log$ 兼容的，所以我们要把平衡树换成其它东西，比如 **值域分块**。

莫队所套数据结构是 $O(n\sqrt n)$ 次修改，$O(n)$ 次查询，所以我们应该让这个值域分块 $O(1)$ 插入或删除一数 $O(\sqrt n)$ 查询全局 $k$ 小。

## 值域分块

同样这玩意求区间 $k$ 小的题：[P4278](/problem/P4278)，[P4119](/problem/P4119)，过程如下：

+ 值域分块，维护每个值域块的和以及每个位置的和
+ 查询时先不停比较 $k$ 与从小到大每个值域块的出现次数，如果 $k$ 更大就让 $k$ 减去这个出现次数。
+ $k$ 减不动的时候答案就在这个值域块里
+ 不停比较 $k$ 与这个值域块从小到大每一个值的出现次数，如果 $k$ 更大就让 $k$ 减去这个出现次数。
+ $k$ 减不动的时候答案就是这个值

```cpp
namespace Blk{
	int s1[maxn],s2[sqr],B,C,st[sqr],ed[sqr];
	
	// B: 块长, C: 块数 
	// s1: 每个位置的出现次数
	// s2: 每个值域块的总出现次数
	// st,ed: 每个值域块的开头/结尾 
	
	int qry(int k){
		for(int i = 1;i <= C;++i){
			if(k > s2[i]){ k -= s2[i]; continue; }
			for(int j = st[i];j <= ed[i];++j)
				if(k > s1[j]) k -= s1[j];
				else return j;
		}
		return -1;
	}
}
```

## 实现

于是剩下~~贺~~个树上莫队板子即可。

```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
 
inline int read(){
    register int x = 0;
    register char c = getchar();
    for(;c < '0' || c > '9';c = getchar());
    for(;c >= '0' && c <= '9';c = getchar())
        x = x * 10 + (c ^ '0');
    return x;
}
 
#define maxn 200005
#define maxm 400005
#define sqr  450
 
int n,m;
 
int c[maxn],d[maxn];
int ans[maxn];
 
std::vector<int> G[maxn];
 
int L[maxn],R[maxn],path[maxm],dfn = 0;
int lg2[maxn],dep[maxn],fa[maxn][20];
 
void dfs(int u = 1,int ft = 0){
	L[u] = ++dfn; path[dfn] = u;
	dep[u] = dep[ft] + 1; fa[u][0] = ft;
	for(int i = 1;i <= 19;++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for(int i = 0;i < (int)G[u].size();++i) if(G[u][i] != ft) dfs(G[u][i],u);
	R[u] = ++dfn; path[dfn] = u;
}
 
int LCA(int x,int y){
	if(dep[x] < dep[y]) x ^= y ^= x ^= y;
	while(dep[x] > dep[y]) x = fa[x][lg2[dep[x] - dep[y]]];
	if(x == y) return x;
	for(int i = 19;~i;--i) if(fa[x][i] != fa[y][i]) x = fa[x][i],y = fa[y][i];
	return fa[x][0];
}
 
namespace Blk{
	int s1[maxn],s2[sqr],B,C,st[sqr],ed[sqr],bl[maxn];
	
	void init(){
		B = sqrt(n); C = (n - 1) / B + 1;
		for(int i = 1;i <= C;++i){
			st[i] = (i - 1) * B + 1;
			ed[i] = i == C ? n : i * B;
			for(int j = st[i];j <= ed[i];++j) bl[j] = i;
		}
	}
	
	void ins(int x){ ++s1[x]; ++s2[bl[x]]; }
	
	void ers(int x){ --s1[x]; --s2[bl[x]]; }
	
	int qry(int k){
		for(int i = 1;i <= C;++i){
			if(k > s2[i]){ k -= s2[i]; continue; }
			for(int j = st[i];j <= ed[i];++j)
				if(k > s1[j]) k -= s1[j];
				else return j;
		}
		return -1;
	}
}
 
bool use[maxn];
 
void upd(int i){ use[i] = !use[i]; use[i] ? Blk::ins(c[i]) : Blk::ers(c[i]); }
 
struct qry{
	int l,r,k,lca,i,be;
	bool operator<(const qry& q) const {
		return be ^ q.be ? be < q.be : be & 1 ? r < q.r : r > q.r;
	}
} q[maxn];
 
signed main(){
	n = read(),m = read();
	Blk::init();
	int bl = sqrt(n * 1.0);
	for(int i = 1;i <= n;++i) c[i] = d[i] = read();
	std::sort(d + 1,d + n + 1);
	int k = std::unique(d + 1,d + n + 1) - d - 1;
	for(int i = 1;i <= n;++i) c[i] = std::lower_bound(d + 1,d + k + 1,c[i]) - d;
	for(int i = 1;i < n;++i){
		int u = read(),v = read();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs();
	for(int i = 2;i <= n;++i) lg2[i] = lg2[i >> 1] + 1; 
	for(int i = 1;i <= m;++i){
		int u = read(),v = read(),lca = LCA(u,v); q[i].k = read();
		if(L[u] > L[v]) u ^= v ^= u ^= v;
		if(lca == u) q[i].l = L[u],q[i].r = L[v];
		else q[i].l = R[u],q[i].r = L[v],q[i].lca = lca;
		q[i].i = i; q[i].be = q[i].l / bl;
	}
	std::sort(q + 1,q + m + 1);
	int l = 1,r = 0;
	for(int i = 1;i <= m;++i){
		while(l < q[i].l) upd(path[l++]);
		while(l > q[i].l) upd(path[--l]);
		while(r > q[i].r) upd(path[r--]);
		while(r < q[i].r) upd(path[++r]);
		if(q[i].lca) upd(q[i].lca);
		ans[q[i].i] = Blk::qry(q[i].k);
		if(q[i].lca) upd(q[i].lca);
	}
	for(int i = 1;i <= m;++i) printf("%d\n",d[ans[i]]);
	return 0;
} 
```

**注意**：这题不能交 C++11 及以上版本，而 SPOJ C++ 语言不能以 `const` 变量大小建立数组，把我弄 CE 了好几回

---

## 作者：LawrenceSivan (赞：9)

# SP10628 COT - Count on a tree

## 前言

最近在刷树上差分的题目。

然后突然想到自己主席树也该复习一下了。

于是我找到了这道题。

~~其实还有一个双倍经验：[P2633 Count on a tree](https://www.luogu.com.cn/problem/P2633) 就是一个强制在线另一个没有而已~~

## 前置知识

1. [主席树](https://www.luogu.com.cn/blog/LawrenceSivan/p3834-ke-chi-jiu-hua-xian-duan-shu-mu-ban-zhu-xi-shu-post)

2. [树上差分](https://www.luogu.com.cn/blog/LawrenceSivan/shu-shang-ci-fen-zong-jie)（这个我写的其实是针对题目的一些问题。~~不过相信刷到这种题的人都是会这些玩意的吧~~）

## 题意及解法

给定一棵有 $n$ 个节点的树，每次求一条路径上的第 $k$ 小。

一条路径可以看做是一个区间，那么一个区间的第 $k$ 小应该是可以联想到主席树的。

回想一般的主席树，对于求某一个区间 $[L,R]$ 的第 $k$ 小，运用到的是前缀和思想，之后差分，用 $root[r]-root[l-1]$ 就得到了当前答案。

对于本题，唯一不同的就是一个序列变成了树上的一段区间。

于是可以想到应该用主席树来维护树上前缀和信息，之后树上差分就可以得出答案。

对于每个节点，都以他的父节点为基础，插入权值。

之后我们发现我们需要一个东西，同时可以支持查找 $lca$ (下面用于查询）和在 dfs 的同时建出主席树。

于是想到了树剖。

~~（其实树剖常数小很多的，而且还很优雅）~~

```cpp
void dfs1(int u,int f){
    size[u]=1;
    fa[u]=f;
    dep[u]=dep[f]+1;
    for(re int i=head[u];i;i=nxt[i]){
        int v=to[i];
        if(v==f)continue;
        root[v]=modify(root[u],1,tmp,a[v]);//以父节点为基础插入值
        dfs1(v,u);
        size[u]+=size[v];
        if(size[v]>size[son[u]])son[u]=v;
    }
}
```

发现权值是带在节点上的，于是自然就是点差分。

于是每次查询 $root[x]+root[y]-root[LCA]-root[fa[LCA]]$.

和一般的主席树差别并不算大，只是在 `query` 的时候需要更改一下。

```cpp
int query(int x,int y,int z,int fz,int l,int r,int k){
    int xx=st[ls(x)].v+st[ls(y)].v-st[ls(z)].v-st[ls(fz)].v;

    if(l==r)return l;

    int mid=(l+r)>>1;
    if(xx>=k)return query(ls(x),ls(y),ls(z),ls(fz),l,mid,k);
    else return query(rs(x),rs(y),rs(z),rs(fz),mid+1,r,k-xx);
}
```

## 细节相关

**要离散化！！！**

~~似乎就是唯一的细节了~~

由于码量并不算小，所以为了看得清楚一下，可以封个 `namespace`.

## CODE：

```cpp
//#define LawrenceSivan

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define re register
const int maxn=1e5+5;
#define INF 0x3f3f3f3f

int n,m,tmp;

int a[maxn],num[maxn];

int head[maxn],to[maxn<<1],nxt[maxn<<1],cnt;

inline void add(int u,int v){
    nxt[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
}

namespace SegmentTree{
    struct SegmentTree{
        int v,lc,rc;
    }st[maxn<<5];

    #define ls(x) st[x].lc
    #define rs(x) st[x].rc

    int tot,root[maxn];

    inline void Discretization(){
        sort(num+1,num+1+n);
        tmp=unique(num+1,num+1+n)-num-1;
        for(re int i=1;i<=n;i++)a[i]=lower_bound(num+1,num+1+tmp,a[i])-num;
    }

    int modify(int rt,int l,int r,int x){
        int t=++tot;
        ls(t)=ls(rt),rs(t)=rs(rt);
        st[t].v=st[rt].v+1;

        if(l==r)return t;

        int mid=(l+r)>>1;
        if(x<=mid)ls(t)=modify(ls(t),l,mid,x);
        else rs(t)=modify(rs(t),mid+1,r,x);

        return t;
    }

    int query(int x,int y,int z,int fz,int l,int r,int k){
        int xx=st[ls(x)].v+st[ls(y)].v-st[ls(z)].v-st[ls(fz)].v;

        if(l==r)return l;

        int mid=(l+r)>>1;
        if(xx>=k)return query(ls(x),ls(y),ls(z),ls(fz),l,mid,k);
        else return query(rs(x),rs(y),rs(z),rs(fz),mid+1,r,k-xx);
    }

}

using namespace SegmentTree;

namespace Tree_chain_partition{
    int size[maxn],dep[maxn],fa[maxn],son[maxn],top[maxn];
    
    void dfs1(int u,int f){
        size[u]=1;
        fa[u]=f;
        dep[u]=dep[f]+1;
        for(re int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v==f)continue;
            root[v]=modify(root[u],1,tmp,a[v]);
            dfs1(v,u);
            size[u]+=size[v];
            if(size[v]>size[son[u]])son[u]=v;
        }
    }

    void dfs2(int u,int topf){
        top[u]=topf;
        if(!son[u])return;
        dfs2(son[u],topf);
        for(re int i=head[u];i;i=nxt[i]){
            int v=to[i];
            if(v==fa[u]||v==son[u])continue;
            dfs2(v,v);
        }
    }

    inline int lca(int x,int y){
        while(top[x]!=top[y]){
            if(dep[top[x]]<dep[top[y]])swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }

}

using namespace Tree_chain_partition;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int main(){
#ifdef LawrenceSivan
    freopen("aa.in","r",stdin);
    freopen("aa.out","w",stdout);
#endif
    n=read();m=read();
    for(re int i=1;i<=n;i++){
        a[i]=read();
        num[i]=a[i];
    }

    Discretization();

    for(re int i=1,u,v;i<n;i++){
        u=read();v=read();
        add(u,v);
        add(v,u);
    }

    root[1]=modify(root[0],1,tmp,a[1]);

    dfs1(1,0);
    dfs2(1,1);

    for(re int i=1,x,y,k;i<=m;i++){
        x=read();y=read();k=read();
        int LCA=lca(x,y);
        printf("%d\n",num[query(root[x],root[y],root[LCA],root[fa[LCA]],1,tmp,k)]);
    }


    return 0;
}
```








---

## 作者：Strelitzia (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/SP10628)

---

一来就看到这个静态第 $\operatorname{k}$ 大，有主席树是肯定的。

在看到是统计一条路径上的，我想到了欧拉序，可能因为我一开始写的是 $\text{COT2}$ ，但其实不用。

我们想，序列上的主席树是如何求第 $\operatorname{k}$ 大的，是差分的想法。

如求 $\texttt{[l,r]}$ 是用加入到 $\texttt{r}$ 的减去 $\texttt{l - 1}$ 的，剩下的就是 $\texttt{[l,r]}$ 之间的。

树上的路径也可以这样做，这里是统计点权，所以用点差分。

也就是统计 $val_u + val_v - val_{lca(u,v)},val_{fa_{lca(u,v)}}$。

其实没有什么大的变化，就主要是 $\operatorname{query}$ 多传了几个参而已。

还有注意细节，我因为 $\operatorname{cnt}$ 和 $\operatorname{tot}$ 弄反了，调了三小时。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 100005;

int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int x,int y) {
	nxt[++ tot] = head[x];ver[tot] = y;head[x] = tot;
}

int l[maxn * 20],r[maxn * 20],val[maxn * 20];
int n,m,a[maxn],b[maxn],dep[maxn],root[maxn],fa[maxn][20],lg[maxn],num,cnt;

int newnode(int k) {
	l[++ cnt] = l[k];
	r[cnt] = r[k];
	val[cnt] = val[k];
	return cnt;
}

int build(int b,int e,int k) {
	k = ++ cnt;
	if (b == e) return k;
	int mid = b + e >> 1;
	l[k] = build(b,mid,l[k]);
	r[k] = build(mid + 1,e,r[k]);
	return k;
}

int update(int b,int e,int k,int x,int y) {
	k = newnode(k);
	if (b == e) val[k] += y;
	else {
		int mid = b + e >> 1;
		if (x <= mid) l[k] = update(b,mid,l[k],x,y);
		else r[k] = update(mid + 1,e,r[k],x,y);
		val[k] = val[l[k]] + val[r[k]];
	}
	return k;
}

int query(int L,int R,int fa,int faa,int b,int e,int k) {
	if (b == e) return b;
	int mid = b + e >> 1;
	int sum = val[l[L]] + val[l[R]] - val[l[fa]] - val[l[faa]];
	return sum >= k ? query(l[L],l[R],l[fa],l[faa],b,mid,k) : query(r[L],r[R],r[fa],r[faa],mid + 1,e,k - sum);
}

void dfs(int u,int faa) {
	fa[u][0] = faa;
	dep[u] = dep[faa] + 1;
	root[u] = update(1,num,root[faa],a[u],1);
	for (int i = 1 ; i <= lg[dep[u]]; ++ i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int i = head[u] ; i ; i = nxt[i]) {
		int v = ver[i];
		if (v == faa) continue;
		dfs(v,u);
	}
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	while(dep[x] > dep[y]) x = fa[x][lg[dep[x] - dep[y]] - 1];
	if(x == y) return x;
	for(int k = lg[dep[x]] - 1; ~k ; --k)
		if(fa[x][k] != fa[y][k])
			x = fa[x][k], y = fa[y][k];
	return fa[x][0];
}

int main () {
	read(n);read(m);
	
	for (int i = 1 ; i <= n ; ++ i) read(a[i]),b[i] = a[i],lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	sort(b + 1,b + 1 + n);
	num = unique(b + 1,b + 1 + n) - b - 1;
	for (int i = 1 ; i <= n ; ++ i) a[i] = lower_bound(b + 1,b + 1 + num,a[i]) - b;
	
	root[0] = build(1,num,0);
	
	int x,y,k;
	for (int i = 1 ; i < n ; ++ i) {
		read(x);read(y);
		addEdge(x,y);addEdge(y,x);
	}
	
	dfs(1,0);
	
	for (int i = 1 ; i <= m ; ++ i) {
		read(x);read(y);read(k);
		int lca = LCA(x,y);
		print(b[query(root[x],root[y],root[lca],root[fa[lca][0]],1,num,k)]),putchar('\n');
	}
	return 0;
}
```

---

## 作者：wucstdio (赞：4)

看到这道题，我们先考虑序列上怎么做，如果不会请转[这里](https://www.luogu.org/problemnew/show/P3834)

那么这样的问题如何放到树上呢？

我们先想序列上的做法。对于一个位置$i$，先令$root[i]=root[i-1]$，然后再在$root[i]$里面插入$a[i]$。这样每一个位置实际上维护了$[1,n]$的信息。

同理，放到树上，对于一个节点$i$，先令$root[i]=root[pa[i]]$，然后再在$root[i]$里面插入$a[i]$。这样每一个位置实际上维护了这个节点到根的信息。

查询的时候，对于序列上的情况，我们只需要用$root[r]-root[l-1]$，就可以得到需要的信息了。

放到树上，对于一个询问$(u,v)$，我们需要用$root[u]+root[v]-root[lca]-root[pa[lca]]$，得到需要的信息。

没看懂的可以看下面这张图：

![](https://cdn.luogu.com.cn/upload/pic/54583.png)

代码如下，注意要动态开点：

```
#include<cstdio>
#include<algorithm>
#include<cstring>
#define lson tree[o].child[0]
#define rson tree[o].child[1]
#define mid (l+r)/2
using namespace std;
struct Tree
{
	int child[2];
	int size;
}tree[8000005];
struct Edge
{
	int to;
	int nxt;
}e[200005];
int n,m,edgenum,head[100005],pa[100005],root[100005],tot;
int a[100005],sa[100005],rnk[100005],dep[100005],anc[26][100005],lastans;
int cmp(int x,int y)
{
	return a[x]<a[y];
}
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void add2(int t,int p)
{
	tree[++tot]=tree[root[t]];
	root[t]=tot;
	int o=root[t],l=1,r=n;
	while(l!=r)
	{
		tree[o].size++;
		if(p<=mid)
		{
			tree[++tot]=tree[lson];
			lson=tot;
			o=lson,r=mid;
		}
		else
		{
			tree[++tot]=tree[rson];
			rson=tot;
			o=rson,l=mid+1;
		}
	}
	tree[o].size++;
}
int query(int a,int b,int c,int d,int l,int r,int k)
{
	if(l==r)return l;
	int la=tree[a].child[0],ra=tree[a].child[1];
	int lb=tree[b].child[0],rb=tree[b].child[1];
	int lc=tree[c].child[0],rc=tree[c].child[1];
	int ld=tree[d].child[0],rd=tree[d].child[1];
	if(tree[la].size+tree[lb].size-tree[lc].size-tree[ld].size>=k)return query(la,lb,lc,ld,l,mid,k);
	else return query(ra,rb,rc,rd,mid+1,r,k-(tree[la].size+tree[lb].size-tree[lc].size-tree[ld].size));
}
void dfs(int node)
{
	dep[node]=dep[pa[node]]+1;
	root[node]=root[pa[node]];
	add2(node,a[node]);
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		pa[to]=node;
		dfs(to);
	}
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v])swap(u,v);
	for(int i=0;dep[u]-dep[v];i++)
	  if((1<<i)&(dep[u]-dep[v]))
		u=anc[i][u];
	if(u==v)return u;
	for(int i=25;i>=0;i--)
	  if(anc[i][u]!=anc[i][v])
	    u=anc[i][u],v=anc[i][v];
	return pa[u];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		sa[i]=i;
	}
	sort(sa+1,sa+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		rnk[i]=a[sa[i]];
		a[sa[i]]=i;
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1);
	for(int i=1;i<=n;i++)anc[0][i]=pa[i];
	for(int i=1;i<26;i++)
	  for(int j=1;j<=n;j++)
	    anc[i][j]=anc[i-1][anc[i-1][j]];
	while(m--)
	{
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		u^=lastans;
		int d=LCA(u,v);
		printf("%d\n",lastans=rnk[query(root[u],root[v],root[d],root[pa[d]],1,n,k)]);
	}
	return 0;
}
```


---

## 作者：mrclr (赞：3)

区间第$k$大扯到树上啦

但是不要慌，仍是不难，仔细想一下就行了。
主席树中的每一棵线段树维护的是一个前缀的答案。利用这一点，把前缀放到树上的话，就是每一个节点到根节点的答案。

所以主席树就建出来啦。

对于每一组询问$(x, y, k)$，令$z = lca(x, y)$，则$(x, y)$这条路径上的答案就可以拆成$root[x] + root[y] - root[z] - root[fa(z)]$四个主席树。然后就没啦。

刚开始我写成了减去$root[z] * 2$，但这样就会把$z$的贡献减掉，也就WA了几发。
```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define rg register
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxt = 2e7 + 5;
const int maxn = 1e5 + 5;
inline ll read()
{
  ll ans = 0;
  char ch = getchar(), last = ' ';
  while(!isdigit(ch)) last = ch, ch = getchar();
  while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
  if(last == '-') ans = -ans;
  return ans;
}
inline void write(ll x)
{
  if(x < 0) x = -x, putchar('-');
  if(x >= 10) write(x / 10);
  putchar(x % 10 + '0');
}

int n, _n, m, a[maxn], b[maxn];

struct Edge
{
  int nxt, to;
}e[maxn << 1];
int head[maxn], ecnt = -1;
void addEdge(int x, int y)
{
  e[++ecnt] = (Edge){head[x], y};
  head[x] = ecnt;
}

struct Tree
{
  int ls, rs, sum;
}t[maxt];
int root[maxn], cnt = 0;

void insert(int old, int& now, int l, int r, int id)
{
  t[now = ++cnt] = t[old];
  t[now].sum++;
  if(l == r) return;
  int mid = (l + r) >> 1;
  if(id <= mid) insert(t[old].ls, t[now].ls, l, mid, id);
  else insert(t[old].rs, t[now].rs, mid + 1, r, id);
}
int query(int f, int z, int x, int y, int l, int r, int k)
{
  if(l == r) return l;
  int mid = (l + r) >> 1, Sum = t[t[x].ls].sum + t[t[y].ls].sum - t[t[z].ls].sum - t[t[f].ls].sum;
  if(k <= Sum) return query(t[f].ls, t[z].ls, t[x].ls, t[y].ls, l, mid, k);
  else return query(t[f].rs, t[z].rs, t[x].rs, t[y].rs, mid + 1, r, k - Sum);
}

int dep[maxn], fa[21][maxn];
void dfs(int now, int _f)
{
  insert(root[_f], root[now], 1, _n, a[now]);
  for(int i = 1; (1 << i) <= dep[now]; ++i)
    fa[i][now] = fa[i - 1][fa[i - 1][now]];
  for(int i = head[now], v; i != -1; i = e[i].nxt)
    {
      if((v = e[i].to) == _f) continue;
      dep[v] = dep[now] + 1;
      fa[0][v] = now;
      dfs(v, now);
    }
}
int lca(int x, int y)
{
  if(dep[x] < dep[y]) swap(x, y);
  for(int i = 20; i >= 0; --i)
    if(dep[x] - (1 << i) >= dep[y]) x = fa[i][x];
  if(x == y) return x;
  for(int i = 20; i >= 0; --i)
    if(fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
  return fa[0][x];
}

int main()
{
  Mem(head, -1);
  n = read(); m = read();
  for(int i = 1; i <= n; ++i) a[i] = b[i] = read();
  sort(b + 1, b + n + 1);
  _n = unique(b + 1, b + n + 1) - b - 1;
  for(int i = 1; i <= n; ++i)
    a[i] = lower_bound(b + 1, b + _n + 1, a[i]) - b;
  for(int i = 1; i < n; ++i)
    {
      int x = read(), y = read();
      addEdge(x, y); addEdge(y, x);
    }
  dfs(1, 0);
  for(int i = 1; i <= m; ++i)
    {
      int x = read(), y = read(), k = read();
      int z = lca(x, y);
      write(b[query(root[fa[0][z]], root[z], root[x], root[y], 1, _n, k)]), enter;
    }
  return 0;
}

```

---

## 作者：Karry5307 (赞：3)

### 题意

给定一棵 $n$ 个点的树，每个点有点权，$q$ 次询问，每次询问需要回答 $u$ 到 $v$ 路径上点权第 $k$ 大的值。

$\texttt{Data Range:}n,q\leq 10^5$

### 题解

首先考虑序列上的怎么做。用主席树维护一段前缀，对于每个询问在两棵主席树相减的主席树上做就行了，这里利用到了差分的思想，同时也说明了**主席树具有可减性**。

现在考虑将这个做法搬到树上来。所有前缀和操作替换成树上前缀和（也即一个点到根路径上所有节点），查询的话改为树上差分。相当于在 $u,v,lca(u,v),fa_{lca(u,v)}$ 的四棵主席树上操作，然后就做完了，实现的话应该不难。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
struct Edge{
	ll to,prev;
};
struct SegmentTree{
	ll l,r,sm;
};
Edge ed[MAXN<<2];
SegmentTree tree[MAXN<<5];
ll n,qcnt,tot,totn,totd,u,v,kk;
ll last[MAXN],rt[MAXN],x[MAXN],dsc[MAXN],ls[MAXN<<5],rs[MAXN<<5];
ll fa[MAXN],depth[MAXN],sz[MAXN],hv[MAXN],top[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void addEdge(ll from,ll to)
{
	ed[++tot].prev=last[from];
	ed[tot].to=to;
	last[from]=tot;
}
inline void create(ll l,ll r,ll &node)
{
	tree[node=++totn]=(SegmentTree){l,r,0};
	if(l==r)
	{
		return;
	}
	ll mid=(l+r)>>1;
	create(l,mid,ls[node]),create(mid+1,r,rs[node]);
}
inline ll insert(ll pos,ll node)
{
	ll cur=++totn;
	tree[cur]=tree[node],tree[cur].sm++,ls[cur]=ls[node],rs[cur]=rs[node];
	if(tree[node].l==tree[node].r)
	{
		return cur;
	}
	ll mid=(tree[node].l+tree[node].r)>>1;
	pos<=mid?ls[cur]=insert(pos,ls[node]):rs[cur]=insert(pos,rs[node]);
	return cur;
}
inline void dfs(ll node,ll f)
{
	ll mx=-1;
	depth[node]=depth[fa[node]=f]+1,sz[node]=1;
	rt[node]=insert(lower_bound(dsc+1,dsc+totd+1,x[node])-dsc,rt[f]);
	for(register int i=last[node];i;i=ed[i].prev)
	{
		if(ed[i].to!=f)
		{
			dfs(ed[i].to,node),sz[node]+=sz[ed[i].to];
			sz[ed[i].to]>mx?mx=sz[hv[node]=ed[i].to]:1;
		}
	}
}
inline void dfs2(ll node,ll link)
{
	ll to;
	top[node]=link;
	if(!hv[node])
	{
		return;
	}
	dfs2(hv[node],link);
	for(register int i=last[node];i;i=ed[i].prev)
	{
		(to=ed[i].to)!=fa[node]&&to!=hv[node]?dfs2(to,to):(void)1;	
	}
}
inline ll LCA(ll x,ll y)
{
	while(top[x]!=top[y])
	{
		depth[top[x]]<depth[top[y]]?swap(x,y):(void)1,x=fa[top[x]];
	}
	return depth[x]<depth[y]?x:y;
}
inline ll queryVal(ll l,ll r,ll rk,ll l1,ll l2,ll l3,ll l4)
{
	if(l==r)
	{
		return l;
	}
	ll mid=(l+r)>>1;
	ll diff=tree[ls[l1]].sm+tree[ls[l2]].sm-tree[ls[l3]].sm-tree[ls[l4]].sm;
	if(rk<=diff)
	{
		return queryVal(l,mid,rk,ls[l1],ls[l2],ls[l3],ls[l4]);
	}
	else
	{
		return queryVal(mid+1,r,rk-diff,rs[l1],rs[l2],rs[l3],rs[l4]);
	}
}
inline ll query(ll u,ll v,ll rk)
{
	ll l=LCA(u,v);
	return dsc[queryVal(1,totd,rk,rt[u],rt[v],rt[l],rt[fa[l]])];
}
int main()
{
	n=read(),qcnt=read();
	for(register int i=1;i<=n;i++)
	{
		x[i]=dsc[i]=read();
	}
	for(register int i=0;i<n-1;i++)
	{
		u=read(),v=read(),addEdge(u,v),addEdge(v,u);
	}
	sort(dsc+1,dsc+n+1),totd=unique(dsc+1,dsc+n+1)-dsc-1;
	create(1,totd,rt[0]),dfs(1,0),dfs2(1,1);
	for(register int i=1;i<=qcnt;i++)
	{
		u=read(),v=read(),kk=read(),printf("%d\n",query(u,v,kk));
	}
}
```

---

## 作者：abs001 (赞：2)

[更好的阅读体验](http://abs001.top/blog/?p=106)

前置知识：[主席树](https://www.luogu.org/problemnew/show/P3834)

此题可采用主席树做法，用来求树上第k小。对于从u到v上第k小的值，可以转换成u到lca（u，v）和v到lca（u，v）的第k小。

便可以转换成 
z = lca(x,y);
rt[x], rt[y], rt[z], rt[fa[z]] 四个主席树上求第k小的问题了

当然，还是要离散化的。

注：spoj只能用c语言，所以c++要变成c

代码：
```cpp
//我是通过树链剖分找lca的
#include<stdio.h>
#include<algorithm>
#define N 200001
using namespace std;

struct node{
    int to, ne;
}e[N];

int n, m, cnt, len, l1, last;
int he[N], a[N], b[N], c[N], rt[N], lc[N << 5], rc[N << 5], val[N << 5];
int si[N], de[N], fa[N], son[N], rk[N], id[N], up[N];

void add(int x, int y)
{
    e[++l1].to = y;
    e[l1].ne = he[x];
    he[x] = l1;
    return;
}
void dfs1(int x)
{
    si[x] = 1;
    for(int i = he[x]; i; i = e[i].ne)
    {
        int y = e[i].to;
        if(y == fa[x]) continue;
        fa[y] = x, de[y] = de[x] + 1;
        dfs1(y);
        si[x] += si[y];
        if(si[y] > si[son[x]]) son[x] = y;
    }
    return;
}

void dfs2(int x, int f)
{
    id[x] = ++len, up[x] = f, rk[len] = x;
    if(!son[x]) return;
    dfs2(son[x], f);
    for(int i = he[x]; i; i = e[i].ne)
    {
        int y = e[i].to;
        if(y == fa[x]) continue;
        if(son[x] != y) dfs2(y, y);
    }
    return;
}

int lca(int x, int y)
{
    while(up[x] != up[y])
    {
        if(de[up[x]] < de[up[y]]) swap(x, y);
        x = fa[up[x]];
    }
    if(id[x] > id[y]) return y;
    return x;
}


inline void build(int &rt, int l, int r)
{
    rt = ++len;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(lc[rt], l, mid);
    build(rc[rt], mid + 1, r);
    return;
}

inline int change(int rt, int l, int r, int x)
{
    int now = ++len;
    lc[now] = lc[rt], rc[now] = rc[rt], val[now] = val[rt] + 1;
    if(l == r) return now;
    int mid = (l + r) >> 1;
    if(x <= mid) lc[now] = change(lc[rt], l, mid, x);
    else rc[now] = change(rc[rt], mid + 1, r, x);
    return now;
}

inline int query(int x, int y, int z, int zf, int l, int r, int k)
{
    if(l == r) return l;
    int mid = (l + r) >> 1, s = val[lc[x]] + val[lc[y]] - val[lc[z]] - val[lc[zf]], res;
    if(s >= k) res = query(lc[x], lc[y], lc[z], lc[zf], l, mid, k);
    else res = query(rc[x], rc[y], rc[z], rc[zf], mid + 1, r, k - s);
    return res;
}

void dfs(int x, int fa)
{
    for(int i = he[x]; i; i = e[i].ne)
    {
        int y = e[i].to;
        if(y == fa) continue;
        rt[y] = change(rt[x], 1, cnt, c[y]);
        dfs(y, x);
    }
    return;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(register int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
    sort(b + 1, b + n + 1);
    cnt = unique(b + 1, b + n + 1) - b - 1;//离散化
    for(int i = 1; i <= n; i++) c[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;//二分查找
    for(register int i = 1; i < n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);//邻接表储存数据
    }
    dfs1(1);//树链剖分lca
    dfs2(1, 0);//树链剖分lca
    len = 0;
    rt[1] = change(rt[0], 1, cnt, c[1]);//建立根主席树
    dfs(1, 0);//dfs建立主席树
    for(int i = 1; i <= m; i++)
    {
        int x, y, k, w, z;
        scanf("%d%d%d", &x, &y, &k);
        z = lca(x, y);//找lca
        w = query(rt[x], rt[y], rt[z], rt[fa[z]], 1, cnt, k);//询问
        printf("%d\n", b[w]);
        last = b[w];
    }
    return 0;
}
```


---

## 作者：wcyQwQ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/SP10628)

[可能更好的阅读体验](https://chenyu-w.github.io/2022/06/25/SP10628%20COT/)

## 前言

这个蒟蒻因为 LCA 中 `f[f[u][i - 1]][i - 1]` 打成 `f[u][f[u][i - 1]]` 调了两天。

### 前置芝士

主席树，LCA

## 分析

观察到这个题其实就是树上的静态第 $k$ 小问题，那么考虑建立主席树。

我们建立主席树的时候考虑用 $root[i]$ 来表示从根节点到 $i$ 号节点的主席树的根，然后和模板题一样，维护每个主席树上 $[l, r]$ 中数字出现的个数(即 $cnt$ 值)。

然后考虑查询，这里运用到树上差分的思想，我们发现 $u, v$ 两点路径上的 $cnt$ 值其实等于
$$
cnt[u] +cnt[v] - cnt[lca(u ,v)] - cnt[fa[lca(u, v)]]
$$
其中 $fa[x]$ 表示某个节点的父亲，那么我们就可以用主席树来写完这题了。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;

struct node
{
    int lc, rc, cnt;
} t[N << 5];

int root[N];
int h[N], e[N << 1], ne[N << 1], idx;
int f[N][21], dep[N];
int tot, len;
int a[N], b[N];
int n, m;

inline int read()
{
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int find(int x)
{
    return lower_bound(b + 1, b + len + 1, x) - b;
}

inline void add(int a, int b)
{
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

inline int build(int p, int l, int r)
{
    p = ++tot;
    if (l == r) return p;
    int mid = (l + r) >> 1;
    t[p].lc = build(t[p].lc, l, mid);
    t[p].rc = build(t[p].rc, mid + 1, r);
    return p;
}

inline int clone(int p)
{
    t[++tot] = t[p];
    return tot;
}

inline void pushup(int p)
{
    t[p].cnt = t[t[p].lc].cnt + t[t[p].rc].cnt;
}

inline int insert(int p, int l, int r, int x, int k)
{
    p = clone(p);
    if (l == r)
    {
        t[p].cnt += k;
        return p;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) t[p].lc = insert(t[p].lc, l, mid, x, k);
    else t[p].rc = insert(t[p].rc, mid + 1, r, x, k);
    pushup(p);
    return p;
}

inline void dfs(int u, int p)
{
    root[u] = insert(root[p], 1, len, a[u], 1);
    dep[u] = dep[p] + 1, f[u][0] = p;
    for (int i = 1; (1 << i) <= dep[u]; i++)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = h[u]; ~i; i = ne[i])
    {
        int v = e[i];
        if (v == p) continue;
        dfs(v, u);
    }
}

inline int lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = log2(n); i >= 0; i--)
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y) return x;
    for (int i = log2(n); i >= 0; i--)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

inline int query(int p, int q, int x, int y, int l, int r, int k)
{
    if (l == r) return l;
    int lcnt = t[t[p].lc].cnt + t[t[q].lc].cnt - t[t[x].lc].cnt - t[t[y].lc].cnt;
    int mid = (l + r) >> 1;
    if (k <= lcnt) return query(t[p].lc, t[q].lc, t[x].lc, t[y].lc, l, mid, k);
    else return query(t[p].rc, t[q].rc, t[x].rc, t[y].rc, mid + 1, r, k - lcnt);
}

int main()
{
    memset(h, -1, sizeof h);
    n = read(), m = read();
    for (int i = 1; i <= n; i++)
        a[i] = read(), b[i] = a[i];
    sort(b + 1, b + n + 1);
    len = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        a[i] = find(a[i]);
    for (int i = 1; i <= n - 1; i++)
    {
        int u = read(), v = read();
        add(u, v);
        add(v, u);
    }
    root[0] = build(0, 1, len);
    dfs(1, 0);
    while (m--)
    {
        int u = read(), v = read(), k = read();
        int p = lca(u, v);
        int res = b[query(root[u], root[v], root[p], root[f[p][0]], 1, len, k)];
        printf("%d\n", res);
    }
    return 0;
}
```



---

## 作者：Dirichlet (赞：1)

主席树相信大家都会吧

这里只遇需到对于一组询问拆除4棵主席树:
x,y,lca(x,y),fa(lca(x,y)).

感觉是个板子题~~虽然RE了两天~~

蒟蒻的代码

```cpp
#include<algorithm>
#include<cctype>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<map>
#include<queue>
#include<stack>
#include<vector>
#define siz 4001000
#define eds 200010
#define tp to[p]
#define gc getchar()
#define db double
#define ll long long
#define rep(i,s,n) for (register int i=s;i<=n;i++)
#define drep(i,n,s) for (register int i=n;i>=s;i--)
#define il inline
#define mmid int mid=(l+r)>>1

using namespace std;

struct Po
{
	int x,id;
}a[eds];

int x,y,ans=0,k=0,z;
vector<int> V[eds];
int cnt[siz],lch[siz],rch[siz];
int rt[eds],dfn[eds],rev[eds];
int head[eds],to[eds<<1],nxt[eds<<1],num,n,tot,m,dfn_num,col=0;
int fa[eds][30],dep[eds],in[eds],out[eds],pv[eds],rank[eds],b[10];

bool cmp(Po a, Po b) {return (a.x<b.x);}

void add(int x,int y)
{
	num++; to[num]=y;nxt[num]=head[x];head[x]=num;
}

void dfs(int x,int fat)
{
	dfn[++dfn_num]=x; in[x]=dfn_num;
	for (int p=head[x];p;p=nxt[p])
		if (tp!=fat)
		{
			fa[tp][0]=x,dep[tp]=dep[x]+1;
			dfs(tp,x);
		}
			
	out[x]=dfn_num;
}

int jump(int x,int d)
{
	for (int i=19;i>=0;i--)
	  if (d&(1<<i)) x=fa[x][i];
	return x;
}

int lca(int x,int y)
{
	if (dep[x]>dep[y]) x=jump(x,dep[x]-dep[y]);
	else y=jump(y,dep[y]-dep[x]);
	if (x==y) return x;
	for (int i=19;i>=0;i--)
	  if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

int modify(int pre,int l,int r,int x,int sgn)
{
	int now=++tot;
	if (l==r) {lch[now]=rch[now]=0; cnt[now]=cnt[pre]+sgn; return now;}
	mmid;
	if (x<=mid) rch[now]=rch[pre],lch[now]=modify(lch[pre],l,mid,x,sgn);
	else lch[now]=lch[pre],rch[now]=modify(rch[pre],mid+1,r,x,sgn);
	cnt[now]=cnt[lch[now]]+cnt[rch[now]]; return now;
}

int query(int l,int r,int k)
{
	if (l==r) return l;
	int sum=cnt[lch[b[1]]]+cnt[lch[b[2]]]-cnt[lch[b[3]]]-cnt[lch[b[4]]];
	int mid=(l+r)/2; 
	if (sum>=k)
	{
		for (int i=1;i<=4;i++) b[i]=lch[b[i]];
		return query(l,mid,k);
	}
	else
	{
		for (int i=1;i<=4;i++) b[i]=rch[b[i]];
		return query(mid+1,r,k-sum);
	}
}

int main()
{
//	freopen("a.in","r",stdin);
//	freopen("y.out","w",stdout);
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&a[i].x); rep(i,1,n) a[i].id=i; sort(a+1,a+n+1,cmp);
	col=1; rank[1]=a[1].x; rev[a[1].id]=1; 
	rep(i,2,n)
	{
		if (a[i].x!=a[i-1].x) rank[++col]=a[i].x;
		rev[a[i].id]=col;
	}
	rep(i,1,n-1) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	dep[1]=0; fa[1][0]=0;dfs(1,0);
	rep(j,1,19)
	  rep(i,1,n)
	    if (fa[i][j-1]) fa[i][j]=fa[fa[i][j-1]][j-1]; else fa[i][j]=0;
	rep(i,1,n) pv[in[i]]=rev[i];
	rep(i,1,n) V[out[i]+1].push_back(rev[i]);
	tot=rt[0]=lch[0]=rch[0]=cnt[0]=0;
	rep(i,1,n) 
	{
		rt[i]=modify(rt[i-1],1,col,pv[i],1);
		for (int j=0;j<V[i].size();j++)  rt[i]=modify(rt[i],1,col,V[i][j],-1);
	}
	while (m--)
	{
		int x,y,k;
		scanf("%d%d%d",&x,&y,&k); 
		z=lca(x,y); 
		b[1]=rt[in[x]];b[2]=rt[in[y]];b[3]=rt[in[z]];b[4]=rt[in[fa[z][0]]];
		ans=rank[query(1,col,k)];
		if (m!=0) printf("%d\n",ans);
		else printf("%d",ans);
	}
	return 0;
}


```


---

## 作者：Acc_Robin (赞：0)

求树上一条链的第$k$大——主席树.

像树上差分一样，在查询时查询

$$
val[x]+val[y]-val[LCA(x,y)]-val[fa[LCA(x,y)]]
$$

即可.

建树时要跟着$dfs$一起建，顺便做了树剖.

代码：
```cpp
#include<cstdio>
#include<string>
#include<algorithm>
namespace Acc{
	const int N = 1e5+10;
	std::basic_string<int>G[N];
	int n,m,a[N],b[N],d[N],tp[N],s[N],fa[N],sz[N],rt[N],len;
	int LCA(int x,int y){
		while(tp[x]!=tp[y])d[tp[x]]>d[tp[y]] ? x=fa[tp[x]] : y=fa[tp[y]];
		return d[x]>d[y]?y:x;
	}
	struct Seg{
		static const int M = N<<5;
		int sum[M],ls[M],rs[M],sz;
		int upd(int rt,int l,int r,int x){
			int mid=l+r>>1,o=++sz;
			sum[o]=sum[rt]+1,ls[o]=ls[rt],rs[o]=rs[rt];
			if(l==r)return o;
			x<=mid ? ls[o]=upd(ls[o],l,mid,x) : rs[o]=upd(rs[o],mid+1,r,x);/////////////////////////////////////////////
			return o;
		}
		int query(int u,int v,int w,int p,int l,int r,int k){
			if(l==r)return l;
			int s=sum[ls[u]]+sum[ls[v]]-sum[ls[w]]-sum[ls[p]],mid=l+r>>1;
			if(k<=s) return query(ls[u],ls[v],ls[w],ls[p],l,mid,k);
			else return query(rs[u],rs[v],rs[w],rs[p],mid+1,r,k-s);
		}
	}t;
	void dfs1(int u){
		int i,v;
		for(sz[u]=1,s[u]=-1,i=0;i<G[u].size();i++){
			if(!d[v=G[u][i]]){
				rt[v]=t.upd(rt[u],1,len,a[v]);
				if(d[v]=d[u]+1,fa[v]=u,dfs1(v),sz[u]+=sz[v],(s[u]==-1 || sz[v]>sz[s[u]]))s[u]=v;
			}
		}
	}
	void dfs2(int u,int T){
		int i,v;
		if(tp[u]=T,s[u]!=-1)dfs2(s[u],T);
		for(i=0;i<G[u].size();i++){
			v=G[u][i];
			if(v!=s[u] && v!=fa[u])dfs2(v,v);
		}
	}
	void work(){
		int x,y,z;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
		std::sort(b+1,b+n+1),len=std::unique(b+1,b+n+1)-b-1;
		for(int i=1;i<=n;i++)a[i]=std::lower_bound(b+1,b+len+1,a[i])-b;
		for(int i=1;i<n;i++)scanf("%d%d",&x,&y),G[x]+=y,G[y]+=x;
		rt[1]=t.upd(rt[0],1,len,a[1]);
		d[1]=1,dfs1(1),dfs2(1,1);
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&x,&y,&z);
			int lca=LCA(x,y);
			printf("%d\n",b[t.query(rt[x],rt[y],rt[lca],rt[fa[lca]],1,len,z)]);
		}
	}
}
int main(){
	return Acc::work(),0;
}
```

---

## 作者：MuYC (赞：0)

#### 前言

带来一种思路，虽然复杂度为 $O(n \log^2 n)$，但是普适性更高，其实属于树剖的一个 $trick$ ，可以普遍处理一些信息重复或者需要合并从而引起冲突的问题。

#### 思路

+ 树上求路径点权第 $k$ 大问题：

路径统计，第 $k$ 大，熟悉的配方引导我们使用树链剖分 + 主席树来解决这个问题。不需说什么，直接按照常规的树链剖分处理即可。按照 $dfs$ 序的递增来依次往主席树插入每一个点的权值。

处理完了这个以后，我们发现一个问题：

树剖在处理一条路径的问题的时候，我们发现它需要处理很多段连续的 $dfs$ 序区间，现在我们需要把这些区间的信息全部合并起来求第 $k$ 大。

但是这些信息不好合并，怎么办？

那就暴力一点，把所有需要求的连续 $dfs$ 段给拿下来，因为经过了轻重链剖分，我们得到的连续 $dfs$ 段不超过 $\log n$ 个，这并不会引起复杂度的退化。

然后直接在主席树上求第 $k$ 大，普通主席树的查询左区间有多少个数是求 :

$T[T[v].lson].sum - T[T[u].lson].sum$。 $v,u$ 表示要处理的两个版本 

但是我们可以把这个左区间有多少个数定义为:

$\sum T[T[v_i].lson].sum - T[T[u_i].lson].sum$ 

$v_i,u_i$ 表示第 $i$ 个要处理的连续 $dfs$ 段的左右端点的两个版本。

这样子我们就解决了这个问题，当然这个做法还可以解决一些问题，比如我现在口胡一个题：

给定一棵 $n$ 个节点的树，每个点带点权，支持下面两种操作 $m$ 次:

+ $op = 1$ 表示修改，给定 $k$ 个点对 $u_i$ $v_i$ 和一个数 $w_i$，你需要将 $u_i$ to $v_i$ 这些路径形成的联通块中的每个点点权 + $w_i$

+ $op = 2$ 给定一个 $x$ ，求以 $x$ 为根的子树内所有点的权值和。

$1 <= n,m, \sum k <= 10^5$。

这个题目其实跟本题也是一样的，对于操作二自然是不用多讲，关键是 $op = 1$ 的操作。这个问题普通的树剖写法难以处理，但是假设我们把一次所有要修改的区间像上面那题全部拿下来，然后 $sort$ 一遍，再合并需要修改的区间段，这样就可以避免重复。

因为每次最多涉及到 $k \log n$ 个区间段，需要 $sort$ 之后合并需要修改的区间，合并后肯定少于 $k \log n$ 个区间，因为线段树修改的复杂度是 $O(\log n)$ 的， 所以单次修改的复杂度是 $O(k \log^2 n)$ 的，因为保证了 $\sum k <= 10^5$，所以复杂度有保证。

那么就讲完了，实际上所有的树剖都可以这么写，而且这样写的话也不会导致复杂度变劣，也就相当于把树剖的修改操作离线了，但是又不是传统意义的离线，(还是在线算法)，意会一下吧，说起来有点玄学。

#### 喜闻乐见代码时间

这是本题的 AC 代码

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#define mid ((l + r) >> 1)
using namespace std;
inline int read() {
	int x = 0, flag = 1;
	char ch = getchar();
	for( ; ch > '9' || ch < '0' ; ch = getchar()) if(ch == '-') flag = -1;
	for( ; ch >= '0' && ch <= '9' ; ch = getchar()) x = (x << 3) + (x << 1) + ch - '0';
	return x * flag;
}

const int MAXN = 1e5 + 50;
int n, Q, start[MAXN], tot = 0;
int val[MAXN], mp[MAXN], nowid = 0, dfn_id[MAXN], rt[MAXN], Cnt = 1;
int fa[MAXN], tp[MAXN], N, siz[MAXN], son[MAXN], dfn[MAXN], dep[MAXN], tail = 0;
pair <int, int> q[MAXN];
struct LISAN {
	int val, id;
} Lis[MAXN];
struct Edge {
	int next, to;
} edge[MAXN << 1];
struct SegmentTree {
	int ls, rs, sum;
} T[MAXN * 25];

bool cmp(LISAN A, LISAN B) {return A.val < B.val;}

void add(int from, int to) {
	edge[++ tot] = (Edge){start[from], to};
	start[from] = tot;
	return ;
}

void init() {
	n = read(), Q = read();
	for(int i = 1 ; i <= n ; i ++) {
		val[i] = read(); Lis[i].id = i;
		Lis[i].val = val[i];
	}
	sort(Lis + 1, Lis + 1 + n, cmp); // 离散化
	for(int i = 1, now = 0 ; i <= n; i ++) {
		if(Lis[i].val != Lis[i - 1].val) now ++, mp[now] = Lis[i].val, N = now;
		val[Lis[i].id] = now;
	}
	for(int i = 1 ; i <= n - 1 ; i ++) {
		int u = read(), v = read();
		add(u, v), add(v, u);
	}
	return ;
}

void DFS1(int x, int from) {// 传统树剖的 DFS1
	siz[x] = 1, dep[x] = dep[from] + 1;
	fa[x] = from;
	for(int i = start[x] ; i ; i = edge[i].next) {
		int to = edge[i].to;
		if(to == fa[x]) continue;
		DFS1(to, x); siz[x] += siz[to];
		if(siz[to] > siz[son[x]]) son[x] = to;
	}
	return ;
}

void DFS2(int x, int top) { // 传统树剖的 DFS2
	tp[x] = top, dfn[x] = ++ nowid, dfn_id[nowid] = x;
	if(son[x]) DFS2(son[x], top);
	for(int i = start[x] ; i ; i = edge[i].next) {
		int to = edge[i].to;
		if(to == son[x] || to == fa[x]) continue;
		DFS2(to, to);
	}
	return ;
}

int insert(int x, int l, int r, int pos) { //主席树插入节点
	int cur = ++ Cnt;
	T[cur] = T[x], T[cur].sum ++;
	if(l == r) return cur;
	if(pos <= mid) T[cur].ls = insert(T[x].ls, l, mid, pos);
	else T[cur].rs = insert(T[x].rs, mid + 1, r, pos);
	return cur;
}

int GetAns(int l, int r, int K) {
	if(l == r) return mp[l];
	int SumL = 0;
	for(int i = 1 ; i <= tail ; i ++) // 跟普通主席树不同的地方
		SumL += T[T[q[i].second].ls].sum - T[T[q[i].first].ls].sum;
	if(K <= SumL) {
		for(int i = 1 ; i <= tail ; i ++)
		q[i].first = T[q[i].first].ls, q[i].second = T[q[i].second].ls; // 全部版本都转移到左儿子
		return GetAns(l, mid, K);
	}
	else {
		for(int i = 1 ; i <= tail ; i ++)
		q[i].first = T[q[i].first].rs, q[i].second = T[q[i].second].rs;
		return GetAns(mid + 1, r, K - SumL);
	}
}

int deal(int x, int y, int k) {
	tail = 0;
	while(tp[x] != tp[y]) {
		if(dep[tp[x]] < dep[tp[y]]) swap(x, y);
		q[++ tail] = make_pair(rt[dfn[tp[x]] - 1], rt[dfn[x]]);
        // 将需要修改的连续 dfs 段给扒下来
		x = fa[tp[x]];
	}
	if(dfn[x] < dfn[y]) swap(x, y);
	q[++ tail] = make_pair(rt[dfn[y] - 1], rt[dfn[x]]);
    // 一样的扒下来
	return GetAns(1, N, k);
}

void work() {
	rt[0] = 1;
	for(int i = 1 ; i <= n ; i ++) 
		rt[i] = insert(rt[i - 1], 1, N, val[dfn_id[i]]);
	int lastAns = 0;
	while(Q --) {
		int x = read(), y = read(), k = read();
		x ^= lastAns;
		lastAns = deal(x, y, k);
		printf("%d\n", lastAns);
	}
	return ;
}

int main() {
	init(); 
	DFS1(1, 0); DFS2(1, 1); 
	work();
	return 0;
}
```

---

## 作者：斜揽残箫 (赞：0)

## Description

静态区间第 $k$ 小，肯定是主席树，但是我不会，所以我就用树上莫队 + 值域分块 A 了这道题。

不的不说，还真有点卡常，~~喜提最劣解~~。

温馨提示 ： 这个题好像不能用 C ++ 11，14，17 来交，我交了后一直 waiting，建议用 C ++。

## Solution

首先这个题目的数据范围也没说，我为了保险，还是写了个离散化，后来在原站上的知是在 ```int``` 范围内。

我用的是值域分块和树上莫队，查询区间第 $k$ 小，

树上莫队不会的请去 [SP10707](https://www.luogu.com.cn/problem/SP10707) 学一下。

讲一下值域分块，我们分块的时候借用莫队的分块即可，树上莫队的区间长度是 $2n$，肯定能够盛下离散化后的值域。

所以只需要值域分块即可。

之后用两个数组 $cnt[i]$ 和 $tmp[i]$，$cnt$ 数组来存每个数字出现多少次，$tmp$ 数组来存每个块中有多少个数字。

查询的时候，枚举每个块，之后查询即可。

```cpp
int Work(int k)
{
  int Sum = 0;//统计前面的数的个数
  for(int i = 1;i <= T;i ++) {
    if(Sum + tmp[i] < k) {Sum += tmp[i];continue;}
    //如果这个块中的数字全部加起来都没有 k 大，就肯定不在这个块里面
    else {
      for(int j = L[i];j <= R[i];j ++) {
        Sum += cnt[j];
        //不断加上数值，直到达到目标。
        if(Sum >= k) return j;
      }
    }
  }
}
```

那么这是我们离散化后的数值，我们是要求原数值，我搞了个 ```map``` 来存，从 $\color{red}{TLE \ \ on \ \ 4}$ 改到了 $\color{red}{TLE \ \ on \ \ 11}$，连平板电视都用上了，实在改不动了，才想到用数组，/ch。

我建立了四个数组，$a,b,c,d$，$a$ 数组离散化，$b$ 数组帮助离散化，$c$ 数组是原来的 $a$ 数组的复制版，$d$ 数组用来建立离散化后的值和原数的对应关系。

就这么卡过了。

献上我巨长的代码。(逃

## Code
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
const int Maxk = 1e6 + 10;
int n,size,cnt1,m,Q,cnts,cntq,T;
int st[Maxk],ed[Maxk],sum[Maxk];
int tot[Maxk],dfn[Maxk << 1],top[Maxk];
int deep[Maxk],fa[Maxk],used[Maxk],cnt[Maxk];
int a[Maxk],son[Maxk],tmp[Maxk],b[Maxk],c[Maxk],d[Maxk];
int head[Maxk],L[Maxk],R[Maxk],block[Maxk];
int ans[Maxk],Ans;
struct node{
  int from;
  int to;
  int next;
}e[Maxk << 1];
struct Query{
  int l;
  int r;
  int pos;
  int k_;
  int Lca_;
}s[Maxk];
struct Modify {
  int past;
  int Now;
}q[Maxk];
inline int read()
{
	int x = 0,f = 0;char ch = getchar();
	while(!isdigit(ch)) f |= ch == '-',ch = getchar();
	while(isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48),ch = getchar();
	return f ? -x : x;
}
void add_edge(int from,int to)//连边 
{
  e[++ cnt1].to = to;
  e[cnt1].from = from;
  e[cnt1].next = head[from];
  head[from] = cnt1;
  return;
}

void BLOCK()
{
  sort(b + 1,b + n + 1);
  int tot = unique(b + 1,b + n + 1) - b - 1;
  for(int i = 1;i <= n;i ++) {
    a[i] = lower_bound(b + 1,b + tot + 1,a[i]) - b;//离散化
    d[a[i]] = c[i];//建立一个关系
  }
  int nn = n << 1;//莫队的分块和值域分块
  //这里我估计重新开一个长为 n 的块可能会更快，但我不想写了。
  int len = pow(nn,0.6666667);
  T = nn / len;
  for(int i = 1;i <= T;i ++) {
    L[i] = (i - 1) * len + 1;
    R[i] = i * len; 
  }
  if(R[T] < nn) T ++,L[T] = R[T - 1] + 1,R[T] = nn;
  for(int i = 1;i <= T;i ++) 
    for(int j = L[i];j <= R[i];j ++)
      block[j] = i;
  return; 
}

void dfs1(int now,int f)//树剖的 dfs1
{
  deep[now] = deep[f] + 1;
  fa[now] = f;
  st[now] = ++ size;
  dfn[size] = now;
  tot[now] = 1;
  for(int i = head[now];i;i = e[i].next) {
    int y = e[i].to;
    if(y == f) continue;
    dfs1(y,now);
    tot[now] += tot[y];
    if(tot[y] > tot[son[now]]) son[now] = y;
  }
  ed[now] = ++size;
  dfn[size] = now;
}

void dfs2(int now,int topfa)//树剖的 dfs2
{
  top[now] = topfa;
  if(!son[now]) return ;
  dfs2(son[now],topfa);
  for(int i = head[now];i;i = e[i].next) {
    int y = e[i].to;
    if(y == fa[now] || y == son[now]) continue;
    dfs2(y,y);
  }
}

int LCA(int x,int y)
//树上莫队判断是否需要加上 LCA
{
  while(top[x] ^ top[y]) {
    if(deep[top[x]] < deep[top[y]]) swap(x,y);
    x = fa[top[x]];
  }
  return deep[x] < deep[y] ? x : y;
}
inline bool CMP(Query a,Query b)//莫队排序
{
  return block[a.l] ^ block[b.l] ? block[a.l] < block[b.l] : a.r < b.r;
}
void Prepare()//处理询问，离线储存
{
  for(int i = 1;i <= Q;i ++) {
    int x = read(),y = read(),k = read();
    if(st[x] > st[y]) swap(x,y);
    int Lca = LCA(x,y);
    s[i].k_ = k;
    s[i].pos = i;
    if(Lca == x) {//同一个子树内不用 LCA
      s[i].l = st[x];
      s[i].r = st[y];
    }
    else {
      s[i].l = ed[x];//否则需要 LCA
      s[i].r = st[y];
      s[i].Lca_ = Lca;
    }
  }
  return;
}

void add(int x)
{
  cnt[x] ++;//这个值的个数 ++ 
  tmp[block[x]] ++;//
}
void del(int x)
{
  cnt[x] --;
  tmp[block[x]] --; 
}

void calc(int x)
{
  used[x] ? del(a[x]) : add(a[x]);
  used[x] ^= 1;
}

int Work(int k)//值域分块的查询第 k 小
{
  int Sum = 0;
  for(int i = 1;i <= T;i ++) {
    if(Sum + tmp[i] < k) {Sum += tmp[i];continue;}
    else {
      for(int j = L[i];j <= R[i];j ++) {
        Sum += cnt[j];
        if(Sum >= k) return j;
      }
    }
  }
}

void Solve()//莫队
{
  sort(s + 1,s + Q + 1,CMP);
  int l = 1,r = 0;
  for(int i = 1;i <= Q;i ++) {
    int ql = s[i].l;
    int qr = s[i].r;
    while(l < ql) calc(dfn[l ++]);
    while(l > ql) calc(dfn[-- l]);
    while(r > qr) calc(dfn[r --]);
    while(r < qr) calc(dfn[++ r]);
    if(s[i].Lca_) calc(s[i].Lca_);
    ans[s[i].pos] = d[Work(s[i].k_)];
    if(s[i].Lca_) calc(s[i].Lca_);
  }
  for(int i = 1;i <= Q;i ++) printf("%d\n",ans[i]);
  return;
}

signed main()
{
  n = read(),Q = read();
  for(int i = 1;i <= n;i ++) a[i] = b[i] = c[i] = read();//读入
  for(int i = 1;i <= n - 1;i ++) {//连边
    int x = read(),y = read();
    add_edge(x,y);
    add_edge(y,x);
  }
  BLOCK();//分块 + 离散化
  dfs1(1,0);//树剖
  dfs2(1,1);
  Prepare();//读入询问
  Solve();//莫队解决
  return 0;
}
```


---

## 作者：Limit (赞：0)

主席树的综合运用题.

# 前置芝士

1. [可持久化线段树](https://www.baidu.com/s?wd=可持久化线段树&ie=UTF-8):~~其实就是主席树了~~.
2. [LCA](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin):最近公共祖先,本题需要在$\log_2N$及以内的时间复杂度内解决这个问题.

# 具体做法

主席树维护每个点到根节点这一条链上不同树出现的次数,然后发现这个东西是可以相减的,于是这条链上每个数出现的次数就变成了$sum[u]+sum[v]-2*sum[LCA(u,v)]$.然后就可以发现这个是错的,如果按这个式子计算最后的链上就没有LCA位置的值了,所以在范围包含$val[LCA(u,v)]$时需要加一,然后正常去找kth就好了.

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int maxN=2e5+7;

int N,M,point[maxN];
int root[maxN];
int sor[maxN];
map<int,int>Hash;
int val[maxN];
//一下为主席树部分
int point_cnt=0;
struct Tree//对于树的一个结构体
{
	int sum,lson,rson;
}tree[maxN*32];
//主席树标准define
#define LSON tree[now].lson
#define RSON tree[now].rson
#define MIDDLE ((left+right)>>1)
#define LEFT LSON,left,MIDDLE
#define RIGHT RSON,MIDDLE+1,right
#define NEW_LSON tree[new_tree].lson
#define NEW_RSON tree[new_tree].rson
void PushUp(int now)//合并信息
{
	tree[now].sum=tree[LSON].sum+tree[RSON].sum;
}
void UpData(int num,int &new_tree,int now,int left=1,int right=N)
//修改并产生一个新版本到new_tree中
{
	if(num<left||right<num)
	{
		new_tree=now;
		return;
	}
	new_tree=++point_cnt;
	if(left==right)
	{
		tree[new_tree].sum=tree[now].sum+1;
		return;
	}
	UpData(num,NEW_LSON,LEFT);
	UpData(num,NEW_RSON,RIGHT);
	PushUp(new_tree);
}
int QueryKth(int k,int LCA_num,int tree1/*相对于式子中的u*/,int tree2/*相当于式子中的v*/,int tree3/*相当于式子中的LCA(u,v)*/,int left=1,int right=N)
{
	if(left==right)
	{
		return left;
	}
	int sum=tree[tree[tree1].lson].sum
		   +tree[tree[tree2].lson].sum
		 -2*tree[tree[tree3].lson].sum;//计算出这条链上在left~right中的数出现的次数
	if(left<=LCA_num&&LCA_num<=MIDDLE)//如果LCA位置的数在当前的范围内就加一
	{
		sum++;
	}
	if(sum>=k)//左子树查询kth
	{
		return
		QueryKth(k,LCA_num,
		tree[tree1].lson,
		tree[tree2].lson,
		tree[tree3].lson,
		left,MIDDLE);
	}
	return//右子树查询
	QueryKth(k-sum,LCA_num,
	tree[tree1].rson,
	tree[tree2].rson,
	tree[tree3].rson,
	MIDDLE+1,right);
}
//一下为链式前向星部分(非主要内容,不多讲)
int head[maxN];
int edge_cnt=0;
struct Edge
{
	int to,next;
}edge[maxN];
#define FOR(now) for(int i_edge=head[now];i_edge;i_edge=edge[i_edge].next)
#define TO edge[i_edge].to
void AddEdge(int form,int to)
{
	edge[++edge_cnt].to=to;
	edge[edge_cnt].next=head[form];
	head[form]=edge_cnt;
}
//一下为倍增LCA部分(非主要内容,不多讲)
int kth_father[maxN][25];
bool visit[maxN];
int deep[maxN],father[maxN];
void DFS(int now)
{
	UpData(Hash[point[now]],root[now],root[father[now]]);//在DFS的过程中把主席树建好
	deep[now]=deep[father[now]]+1;
	kth_father[now][0]=father[now];
	REP(i,0,22)
	{
		kth_father[now][i+1]=kth_father[kth_father[now][i]][i];
	}
	FOR(now)
	{
		if(father[now]!=TO)
		{
			father[TO]=now;
			DFS(TO);
		}
	}
}
int LCA(int x,int y)//LCA核心代码
{
	if(deep[x]<deep[y])
	{
		swap(x,y);
	}
	DOW(i,22,0)
	{
		if(deep[kth_father[x][i]]>=deep[y])
		{
			x=kth_father[x][i];
		}
		if(x==y)
		{
			return x;
		}
	}
	DOW(i,22,0)
	{
		if(kth_father[x][i]!=kth_father[y][i])
		{
			x=kth_father[x][i];
			y=kth_father[y][i];
		}
	}
	return father[x];
}

int main()
{
	scanf("%d%d",&N,&M);
	REP(i,1,N)
	{
		scanf("%d",&point[i]);
		sor[i]=point[i];
	}
	int fa,son;
	REP(i,1,N-1)
	{
		scanf("%d%d",&fa,&son);
		AddEdge(fa,son);
		AddEdge(son,fa);
	}
	sort(sor+1,sor+1+N);//离散化
	sor[0]=-114514;
	int cnt_num=0;
	REP(i,1,N)
	{
		if(sor[i]!=sor[i-1])
		{
			Hash[sor[i]]=++cnt_num;
			val[cnt_num]=sor[i];
		}
	}
	N=cnt_num;
	DFS(1);//DFS,建树+倍增LCA预处理
	int u,v,k;
	int point_LCA;
	REP(i,1,M)
	{
		scanf("%d%d%d",&u,&v,&k);
		point_LCA=LCA(u,v);//找到LCA
		printf("%d\n",
			val[QueryKth(k,Hash[point[point_LCA]],
					 root[u],root[v],root[point_LCA])]
			);//直接查找kth
	}
	return 0;
}
```

---

## 作者：zzxzzximi (赞：0)

# 	看到之前的题解都是用树链剖分+lca+主席树，就好想写一篇就树链剖分+主席树的题解
	因为每次查询都是几个连续的dfs序段组成的，我们只需要把这几段保存下来（段数量不会超过lgn个），减去每段左区间的数量，加上右区间的数量(类似于动态主席树的思想）


```cpp
#include<bits/stdc++.h>
#include<set>
using namespace std;
typedef long long ll;
#define pb push_back
#define ull unsigned long long
#define mp make_pair
const int maxn=1e5+5;
const ll inf=1e18+7;
ll mod=1e9+7;

int in[maxn],out[maxn]; //初点 出点
int son[maxn],f[maxn]; //重儿子，祖先
int father[maxn];       //父亲
int sonNum[maxn];       //儿子数量
int root=1;             //根
int dep[maxn],rk[maxn]; //深度，反序列
int tot=0;              //dfs序编号
vector<int>g[maxn];     //存边
int t1[maxn],t2[maxn],n1,n2;    //存每段dfs序
struct node{int l,r,sum;}s[maxn*40];
int cnt=0,n,m,len,a[maxn],rt[maxn]; //根
vector<int>t;                       //权值线段树必须品

/*树链剖分*/
inline void dfs1(int x,int fa){
    int len=g[x].size();
    sonNum[x]=1;
    father[x]=fa;
    dep[x]=dep[fa]+1;
    son[x]=-1;
    for(int i=0;i<len;i++){
        int to=g[x][i];
        if(to==fa)continue;
        dfs1(to,x);
        sonNum[x]+=sonNum[to];
        if(son[x]==-1 || sonNum[to]>sonNum[son[x]]){
            son[x]=to;
        }
    }
    return;
}
inline void dfs2(int x,int fa,int zx){
    int len=g[x].size();
    f[x]=zx;
    in[x]=++tot;
    rk[tot]=x;
    if(son[x]==-1){
        out[x]=tot;
        return;
    }
    dfs2(son[x],x,zx);
    for(int i=0;i<len;i++){
        int to=g[x][i];
        if(to==fa||to==son[x])continue;
        dfs2(to,x,to);
    }
    out[x]=tot;
}
inline void getAns(int x,int y){
    n1=n2=0;
    while(f[x]!=f[y]){
        if(dep[f[x]]<dep[f[y]])swap(x,y);
        ll res=0;
        t1[++n1]=rt[in[f[x]]-1];
        t2[++n2]=rt[in[x]];
        x=father[f[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    t1[++n1]=rt[in[x]-1];
    t2[++n2]=rt[in[y]];
    return ;
}

/*主席树板子*/
bool cmp(int x,int y){return x<y;}
inline int getid(int x){
    return lower_bound(t.begin(),t.end(),x)-t.begin()+1;
}
inline int built(int l,int r){
    int x=cnt++;
    s[x].sum=0;
    if(l!=r){
        int mid=(l+r)>>1;
        s[x].l=built(l,mid);
        s[x].r=built(mid+1,r);
    }
    return x;
}
inline int upd(int rt,int pos){
    int x=cnt++;
    int temp=x;
    int l=1,r=len;
    s[x].sum=s[rt].sum+1;
    while(l<r){
        int mid=(l+r)>>1;
        if(pos<=mid){
            s[x].r=s[rt].r;
            s[x].l=cnt++;
            x=s[x].l;
            rt=s[rt].l;
            r=mid;
        }
        else{
            s[x].l=s[rt].l;
            s[x].r=cnt++;
            x=s[x].r;
            rt=s[rt].r;
            l=mid+1;

        }
        s[x].sum=s[rt].sum+1;
    }
    return temp;
}

inline int query(int l,int r,int k){
    if(l==r)return l;
    int sum=0;
    for(int i=1;i<=n1;i++){             //减去左区间的
        sum-=s[s[t1[i]].l].sum;
    }
    for(int i=1;i<=n2;i++){             //加上右区间的,前缀和思路
        sum+=s[s[t2[i]].l].sum;
    }

    int mid=(l+r)>>1;
    if(sum>=k){                         //当左子树的个数超过K，往左子树递归
        for(int i=1;i<=n1;i++){
            t1[i]=s[t1[i]].l;
        }
        for(int i=1;i<=n2;i++){
            t2[i]=s[t2[i]].l;
        }
        return query(l,mid,k);
    }
    else{                               //右子树递归
        for(int i=1;i<=n1;i++){
            t1[i]=s[t1[i]].r;
        }
        for(int i=1;i<=n2;i++){
            t2[i]=s[t2[i]].r;
        }
        return query(mid+1,r,k-sum);
    }

}

int main(){
    cin>>n>>m;
    int lastAns=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        t.pb(a[i]);
    }
    sort(t.begin(),t.end(),cmp);
    t.erase(unique(t.begin(),t.end()),t.end());
    len=t.size();
    rt[0]=built(1,len);

    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs1(root,root);
    dfs2(root,root,root);

    for(int i=1;i<=n;i++){
        rt[i]=upd(rt[i-1],getid(a[rk[i]]));
    }

    for(int i=1;i<=m;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        //x^=lastAns;
        getAns(x,y);                    //求每段
        lastAns=t[query(1,len,z)-1];
        printf("%d\n",lastAns);
    }
    return 0;
}

/*

*/

```

  
  ~~然后快乐AC！！~~


---

## 作者：AIskeleton (赞：0)

> [SP10628 COT - Count on a tree](https://www.luogu.com.cn/problem/SP10628)

> 给定一棵有 $n$ 个节点的数，每个点有权值，每次操作输出节点 $u,v$ 之间的第 $k$ 小值。

因为有**静态区间第 $k$ 小**，所以考虑**主席树**。

因为题目要求在树上操作，所以考虑**树上差分**。

建树的过程就是跑一个 dfs，每个节点继承其父节点的权值建树。

对于一般的维护区间第 $k$ 小的主席树，应用前缀和的思想，之后差分出 $rt_r - rt_{l-1}$ 得到结果。

转成树上差分就变成 $rt_u + rt_v - rt_{lca(u,v)} - rt_{fa_{lca(u,v)}}$。

剩下的就是[主席树的模板](https://www.luogu.com.cn/problem/P3834)了。
具体实现看代码。
```cpp
#include <bits/stdc++.h>
#define MID int m=(l+r)>>1;
#define V e[i].v
using namespace std;int rd(){
	int w=0,v=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')v=-1;c=getchar();}
	while(c>='0'&&c<='9'){w=(w<<1)+(w<<3)+(c&15);c=getchar();}return w*v;
}void wr(int x){
    char c[20];int l=0;if(x<0){putchar((1<<5)+(1<<3)+(1<<2)+1);x=~x+1;}
    do{c[l++]=x%10+(1<<4)+(1<<5); x/=10; }while(x>0);for(int i=l-1;i>=0;i--)putchar(c[i]);putchar('\n');
}const int N=2e5+100;int a[N],n,m,b[N],tot,lst,fa[N],tp,rt[N*18];struct tree{int l,r,z;}s[N*18];
struct E{int v,nt;}e[N<<1];int fir[N],c;void I(int u,int v){e[++c].v=v;e[c].nt=fir[u];fir[u]=c;}
struct ox{
	int rt=1,a,b,n,m,cnt,dep[N],dx[N],olx[N],st[N][25];void dfs(int u,int d){
		dx[u]=++cnt;olx[cnt]=u;dep[cnt]=d;
		for(int i=fir[u];i;i=e[i].nt)if(!dx[V])dfs(V,d+1),olx[++cnt]=u,dep[cnt]=d;
	}void init(){
		for(int i=1;i<=cnt;i++)st[i][0]=i;for(int j=1;j<=log2(cnt);j++)for(int i=1;i+(1<<j)-1<=cnt;i++)
		a=st[i][j-1],b=st[i+(1<<(j-1))][j-1],st[i][j]=(dep[a]<dep[b])?a:b;
	}int lca(int l,int r){
		l=dx[l],r=dx[r];if(l>r)swap(l,r);int k=log2(r-l+1);a=st[l][k],b=st[r-(1<<k)+1][k];
		return (dep[a]<dep[b])?olx[a]:olx[b];
	}
}LCA;int id(int x){return lower_bound(a+1,a+tot+1,x)-a;}int C(int t,int l,int r,int x){
	int p=++tp;s[p]=s[t];s[p].z++;if(l==r)return p;MID 
	if(x<=m)s[p].l=C(s[t].l,l,m,x);else s[p].r=C(s[t].r,m+1,r,x);return p;
}void d2(int u,int f){fa[u]=f;rt[u]=C(rt[fa[u]],1,N,id(b[u]));for(int i=fir[u];i;i=e[i].nt)if(V!=f)d2(V,u);}
int query(int a,int b,int c,int d,int l,int r,int k){
	if(l==r)return l;int e=s[s[a].l].z+s[s[b].l].z-s[s[c].l].z-s[s[d].l].z;
	MID if(e>=k)return query(s[a].l,s[b].l,s[c].l,s[d].l,l,m,k);
	else return query(s[a].r,s[b].r,s[c].r,s[d].r,m+1,r,k-e);
}int main(){
	n=rd();m=rd();for(int i=1;i<=n;i++)b[i]=rd(),a[i]=b[i];sort(a+1,a+n+1);tot=unique(a+1,a+n+1)-a-1;
	for(int i=1,u,v;i<n;i++)u=rd(),v=rd(),I(u,v),I(v,u);LCA.dfs(1,1);LCA.init();d2(1,0);
	for(int i=1,u,v,k,l;i<=m;i++)u=rd(),v=rd(),k=rd(),l=LCA.lca(u,v),wr(a[query(rt[u],rt[v],rt[l],rt[fa[l]],1,N,k)]);
}
```

---

