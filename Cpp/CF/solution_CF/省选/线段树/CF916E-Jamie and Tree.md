# Jamie and Tree

## 题目描述

To your surprise, Jamie is the final boss! Ehehehe.

Jamie has given you a tree with $ n $ vertices, numbered from $ 1 $ to $ n $ . Initially, the root of the tree is the vertex with number $ 1 $ . Also, each vertex has a value on it.

Jamie also gives you three types of queries on the tree:

 $ 1\ v $ — Change the tree's root to vertex with number $ v $ .

 $ 2\ u\ v\ x $ — For each vertex in the subtree of smallest size that contains $ u $ and $ v $ , add $ x $ to its value.

 $ 3\ v $ — Find sum of values of vertices in the subtree of vertex with number $ v $ .

A subtree of vertex $ v $ is a set of vertices such that $ v $ lies on shortest path from this vertex to root of the tree. Pay attention that subtree of a vertex can change after changing the tree's root.

Show your strength in programming to Jamie by performing the queries accurately!

## 说明/提示

The following picture shows how the tree varies after the queries in the first sample.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF916E/9b296178af98e90dbbac00c785fb2ed88745e7bd.png)

## 样例 #1

### 输入

```
6 7
1 4 2 8 5 7
1 2
3 1
4 3
4 5
3 6
3 1
2 4 6 3
3 4
1 6
2 2 4 -5
1 4
3 3
```

### 输出

```
27
19
5
```

## 样例 #2

### 输入

```
4 6
4 3 5 6
1 2
2 3
3 4
3 1
1 3
2 2 4 3
1 1
2 2 4 -3
3 1
```

### 输出

```
18
21
```

# 题解

## 作者：Siyuan (赞：29)

> 题目链接：[Codeforces 916E](https://codeforces.com/contest/916/problem/E)

给你一棵有根树标号为 $1\sim n$，每个点都有一个权值 $a_i$。初始时根为 $1$，接下来有 $q$ 次操作，操作分为以下 $3$ 种：

- `1 x`：将整棵树的根变为节点 $x$。
- `2 x y k`：把 $x,y$ 的 $\texttt{LCA}$ 为根的子树中的所有点的权值增加 $k$。
- `3 x`：查询以 $x$ 为根的子树中的节点的权值和。

数据范围：$1\le n,q\le 10^5$，$-10^8\le a_i,k\le 10^8$

------

## Solution

如果没有换根操作，那么我们只需要对这棵树的 $\texttt{DFS}$ 序建立线段树，支持区间修改和区间查询。

接下来考虑换根操作。此时我们显然不能真的把根换掉，根只能一直为 $1$ 节点，而是要对**根**和**操作的节点**的关系进行分类讨论！

由于操作 $2$ 和操作 $3$ 在位置关系分析上的本质是相同的，所以我们只需要考虑**位置关系**和**如何求 LCA** 即可。

### 位置关系

设当前整棵树的根节点为 $R$，询问的子树根节点为 $X$，那么我们可以发现这两者存在以下 $3$ 种关系。

对于每种位置关系的图示，$R$ 和 $X$ 均标记在节点上，蓝色的节点表示**需要被操作的节点**。

1. 如果 $R$ 就是 $X$：

   此时整棵树的所有节点都需要被操作。

   ![](https://old.orzsiyuan.com/images/Codeforces-916E_1.png)

2. 如果 $R$ 不在 $X$ 的子树内：

   此时我们可以发现 $X$ 这棵子树的形态与原图的形态一致，所以只要对以 $1$ 为根节点时的子树 $X$ 进行操作即可。

   ![](https://old.orzsiyuan.com/images/Codeforces-916E_2.png)

3. 如果 $R$ 位于 $X$ 的子树内：

   此时情况比较复杂，需要被操作的节点为： 所有节点除去以 $X$ 到 $R$ 的路径上的第一个节点（这个点满足既是 $R$ 的祖先，又是 $X$ 的儿子）为根的子树。那么我们可以根据容斥原理，先对整棵树进行操作，再对那个子树进行**相反的操作**（如果是查询则减去贡献，如果是修改则减去）。

   那么怎么求这个点呢？我们记 $deep_i$ 表示 $i$ 在原图中的深度，让 $R$ 往上移动 $deep_R-deep_X-1$ 个点即可，这个过程显然可以用倍增实现。

   ![](https://old.orzsiyuan.com/images/Codeforces-916E_3.png)

### 如何求 LCA

其实也是之前的分类讨论的套路啦！QAQ

设当前整棵树的根节点为 $r$，修改的节点为 $x,y$。在以 $1$ 为根节点的前提下，我们也可以分类讨论！（以下内容参考 $\texttt{Codeforces}$ [官方题解](https://codeforces.com/blog/entry/57223)）

1. 如果 $x,y$ 都在 $r$ 的子树内，那么 $\texttt{LCA}$ 显然为 $\texttt{LCA}(x,y)$。
2. 如果 $x,y$ 只有一个在 $r$ 的子树内，那么 $\texttt{LCA}$ 肯定为 $r$。
3. 如果 $x,y$ 都不在 $r$ 的子树内，我们可以先找到 $p=\texttt{LCA}(x,r)$，$q=\texttt{LCA}(y,r)$。如果 $p$ 和 $q$ 不相同，那么我们选择其中较深的一个；如果 $p$ 和 $q$ 相同，那么 $\texttt{LCA}$ 就是 $p$ 或 $q$。

综上所述，我们可以发现我们要求的 $\texttt{LCA}$ 就是 $\texttt{LCA}(x,y)$，$\texttt{LCA}(x,r)$，$\texttt{LCA}(y,r)$ 这三者中深度最大的！

**时间复杂度**：$O(n\log n)$（当然带着巨大常数）

------

## Code

```cpp
#include <cstdio>
#include <algorithm>
#define lson rt<<1
#define rson rt<<1|1

const int N=1e5+5,M=2e5+5,logN=17+1;
int n,m,root,idx,a[N],f[N][logN],dfn[N],seq[N],sz[N],dep[N];
int tot,lnk[N],ter[M],nxt[M];
long long seg[N<<2],tag[N<<2];

void pushup(int rt) {
    seg[rt]=seg[lson]+seg[rson];
}
void build(int rt,int l,int r) {
    if(l==r) {
        seg[rt]=a[seq[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(rt);
}
void update(int rt,int l,int r,long long k) {
    seg[rt]+=1LL*(r-l+1)*k;
    tag[rt]+=k;
}
void pushdown(int rt,int l,int r) {
    if(!tag[rt]) return;
    int mid=(l+r)>>1;
    update(lson,l,mid,tag[rt]);
    update(rson,mid+1,r,tag[rt]);
    tag[rt]=0;
}
void modify(int x,int y,int rt,int l,int r,int k) {
    if(x<=l&&r<=y) {
        update(rt,l,r,k);
        return;
    }
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    if(x<=mid) modify(x,y,lson,l,mid,k);
    if(mid<y) modify(x,y,rson,mid+1,r,k);
    pushup(rt);
}
long long query(int x,int y,int rt,int l,int r) {
    if(x<=l&&r<=y) return seg[rt];
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    long long ret=0;
    if(x<=mid) ret+=query(x,y,lson,l,mid);
    if(mid<y) ret+=query(x,y,rson,mid+1,r);
    return ret;
}
void add(int u,int v) {
    ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot;
}
void dfs(int u,int fa) {
    dep[u]=dep[fa]+1,f[u][0]=fa,dfn[u]=++idx,seq[idx]=u,sz[u]=1;
    for(int i=1;(1<<i)<=dep[u];++i) f[u][i]=f[f[u][i-1]][i-1];
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==fa) continue;
        dfs(v,u),sz[u]+=sz[v];
    }
}
int lca(int u,int v) {
    if(dep[u]>dep[v]) u^=v^=u^=v;
    for(int i=17;~i;--i) if(dep[f[v][i]]>=dep[u]) v=f[v][i];
    if(u==v) return u;
    for(int i=17;~i;--i) if(f[u][i]^f[v][i]) u=f[u][i],v=f[v][i];
    return f[u][0];
}
int getlca(int u,int v,int p) {
    int x=lca(u,v),y=lca(u,p),z=lca(v,p);
    if(dep[y]>dep[x]) x=y;
    if(dep[z]>dep[x]) x=z;
    return x;
}
int jump(int u,int d) {
    for(int i=17;~i;--i) if(d&(1<<i)) u=f[u][i];
    return u;
}
void treeModify(int u,int k) {
    int l=dfn[u],r=dfn[u]+sz[u]-1;
    if(u==root) modify(1,n,1,1,n,k);
    else if(dfn[root]<l||dfn[root]>r) modify(l,r,1,1,n,k);
    else {
        int son=jump(root,dep[root]-dep[u]-1);
        modify(1,n,1,1,n,k),modify(dfn[son],dfn[son]+sz[son]-1,1,1,n,-k);
    }
}
long long treeQuery(int u) {
    int l=dfn[u],r=dfn[u]+sz[u]-1;
    if(u==root) return query(1,n,1,1,n);
    else if(dfn[root]<l||dfn[root]>r) return query(l,r,1,1,n);
    else {
        int son=jump(root,dep[root]-dep[u]-1);
        return query(1,n,1,1,n)-query(dfn[son],dfn[son]+sz[son]-1,1,1,n);
    }
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",&a[i]);
    for(int i=1;i<n;++i) {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs(1,0);
    build(1,1,n);
    root=1;
    while(m--) {
        int opt;
        scanf("%d",&opt);
        if(opt==1) {
            scanf("%d",&root);
        } else if(opt==2) {
            int u,v,x;
            scanf("%d%d%d",&u,&v,&x);
            treeModify(getlca(u,v,root),x);
        } else {
            int x;
            scanf("%d",&x);
            printf("%lld\n",treeQuery(x));
        }
    }
    return 0;
}
```

---

## 作者：绝顶我为峰 (赞：23)

首先，分析得到这是一个树剖

## 题意：

支持以下操作：

$1.$	换根

$2.$	子树修改

$3.$	$LCA$

$4.$	子树查询

我们挨个分析

## $100$分

先以$1$为根将整棵树剖一遍

接着处理每个操作：

$1.$	直接换

$2.$	我们要分类讨论，为了叙述方便，记$x,y$在原树中的$LCA$为$lca(x,y)$

对于任意一点$x$，有以下几种情况：

$(1)$	$x=root$，修改整棵树

$(2)$	$lca(x,root)!=x$，那么换根不影响子树，直接修改

$(3)$	$lca(x,root)=x$，可以画图证明$x$的子树就是$x$原有的子树减去$x$的$root$所在的一个“树枝”，所以我们先修改整棵树，在将$root$所在的树枝还原

$3.$	我们依然要分类讨论：

我们不妨默认$dep[x]\leq dep[y]$

进行分类讨论：

$(1)$ $lca(x,y)=x$

$1)$ $root$在$y$的子树中，那么答案为$y$

![](https://cdn.luogu.com.cn/upload/image_hosting/a3we2g8g.png)
 
$2)$ $root$在$x$与$y$之间，那么答案为$root$

![](https://cdn.luogu.com.cn/upload/image_hosting/84im59ga.png)
 
$3)$ $root$在其他位置，那么答案为$x$

![](https://cdn.luogu.com.cn/upload/image_hosting/6616kv75.png)
 
$(2)$ $lca(x,y)!=x$

$1)$ $root$在$x$的子树中，那么答案为$x$

![](https://cdn.luogu.com.cn/upload/image_hosting/jtq36r9c.png)
 
$2)$ $root$在$y$的子树中，那么答案为$y$

![](https://cdn.luogu.com.cn/upload/image_hosting/vyzsy2ec.png)
 
$3)$ $root$在$x$到$y$的路径上，那么答案为$root$

![](https://cdn.luogu.com.cn/upload/image_hosting/7ria46gd.png)
 
$4)$ 若$lca(x,root)=lca(y,root)$，即$root$在下图所示位置，答案为$lca(x,y)$

![](https://cdn.luogu.com.cn/upload/image_hosting/722z9yfq.png)
 
$5)$ 若$lca(x,y)!=lca(x,root)$，即$root$在下图位置，答案为$lca(x,root)$

![](https://cdn.luogu.com.cn/upload/image_hosting/nwhqgzsw.png)
 
$6)$ 若$lca(x,y)!=lca(y,root)$，即$root$在下图位置，答案为$lca(y,root)$

![](https://cdn.luogu.com.cn/upload/image_hosting/24dgtl1a.png)

$4.$	同$2$，进行分类讨论查询

$code:$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
#define int long long
struct edge
{
	int nxt,to;
}e[300001<<1];
int root,n,m,r,tot,cnt,h[300001],a[300001],dep[300001],fa[300001],s[300001],son[300001],id[300001],w[300001],top[300001],ans[300001<<2],tag[300001<<2],;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void add(int x,int y)
{
	e[++tot].nxt=h[x];
	h[x]=tot;
	e[tot].to=y;
}
inline int ls(int k)
{
	return k<<1;
}
inline int rs(int k)
{
	return k<<1|1;
}
inline void push_up(int k)
{
	ans[k]=ans[ls(k)]+ans[rs(k)];
}
inline void f(int k,int l,int r,int p)
{
	ans[k]+=p*(r-l+1);
	tag[k]+=p;
}
inline void push_down(int k,int l,int r)
{
	int mid=(l+r)>>1;
	f(ls(k),l,mid,tag[k]);
	f(rs(k),mid+1,r,tag[k]);
	tag[k]=0;
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		ans[k]=w[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(k),l,mid);
	build(rs(k),mid+1,r);
	push_up(k);
}
void update(int nl,int nr,int l,int r,int k,int p)
{
	if(l>=nl&&r<=nr)
	{
		ans[k]+=p*(r-l+1);
		tag[k]+=p;
		return;
	}
	push_down(k,l,r);
	int mid=(l+r)>>1;
	if(nl<=mid)
		update(nl,nr,l,mid,ls(k),p);
	if(nr>mid)
		update(nl,nr,mid+1,r,rs(k),p);
	push_up(k);
}
int query(int nl,int nr,int l,int r,int k)
{
	if(l>=nl&&r<=nr)
		return ans[k];
	push_down(k,l,r);
	int mid=(l+r)>>1,res=0;
	if(nl<=mid)
		res+=query(nl,nr,l,mid,ls(k));
	if(nr>mid)
		res+=query(nl,nr,mid+1,r,rs(k));
	return res;
}
void dfs1(int k,int f,int deep)
{
	dep[k]=deep;
	fa[k]=f;
	s[k]=1;
	int maxson=-1;
	for(register int i=h[k];i;i=e[i].nxt)
	{
		if(e[i].to==f)
			continue;
		dfs1(e[i].to,k,deep+1);
		s[k]+=s[e[i].to];
		if(s[e[i].to]>maxson)
		{
			maxson=s[e[i].to];
			son[k]=e[i].to;
		}
	}
}
void dfs2(int k,int t)
{
	id[k]=++cnt;
	w[cnt]=a[k];
	top[k]=t;
	if(!son[k])
		return;
	dfs2(son[k],t);
	for(register int i=h[k];i;i=e[i].nxt)
	{
		if(e[i].to==fa[k]||e[i].to==son[k])
			continue;
		dfs2(e[i].to,e[i].to);
	}
}
inline int lca(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			x^=y^=x^=y;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		x^=y^=x^=y;
	return x;
}
inline int find(int x,int y)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			x^=y^=x^=y;
		if(fa[top[x]]==y)
			return top[x];
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])
		x^=y^=x^=y;
	return son[x];
}
inline int LCA(int x,int y)
{
	if(dep[x]>dep[y])
		x^=y^=x^=y;
	if(lca(x,y)==x)
	{
		if(id[root]>=id[y]&&id[root]<=id[y]+s[y]-1)
			return y;
		if(lca(x,root)==x)
			return lca(y,root);
		return x;
	}
	if(id[root]>=id[x]&&id[root]<=id[x]+s[x]-1)
		return x;
	if(id[root]>=id[y]&&id[root]<=id[y]+s[y]-1)
		return y;
	if((lca(x,root)==root&&lca(x,y)==lca(y,root))||(lca(y,root)==root&&lca(x,y)==lca(x,root)))
		return root;
	if(lca(x,root)==lca(y,root))
		return lca(x,y);
	if(lca(x,y)!=lca(x,root))
		return lca(x,root);
	return lca(y,root);
}
inline void up2(int x,int p)
{
	if(root==x)
	{
		update(1,n,1,n,1,p);
		return;
	}
	int qwq=lca(root,x);
	if(qwq!=x)
		update(id[x],id[x]+s[x]-1,1,n,1,p);
	else
	{
		int node=find(root,x);
		update(1,n,1,n,1,p);
		update(id[node],id[node]+s[node]-1,1,n,1,-p);
	}
}
inline int q2(int x)
{
	if(x==root)
		return query(1,n,1,n,1);
	int qwq=lca(root,x);
	if(qwq!=x)
		return query(id[x],id[x]+s[x]-1,1,n,1);
	int node=find(root,x);
	return query(1,n,1,n,1)-query(id[node],id[node]+s[node]-1,1,n,1);
}
signed main(signed argc,char **argv)
{
	n=read(),m=read(),root=1;
	for(register int i=1;i<=n;++i)
		a[i]=read();
	for(register int i=1;i<n;++i)
	{
	    int x=read(),y=read();
	    add(x,y);
	    add(y,x);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,n);
	while(m--)
	{
		int opt=read();
		if(opt==1)
			root=read();
		if(opt==2)
		{
		    int x=read(),y=read(),p=read();
		    up2(LCA(x,y),p);
		}
		if(opt==3)
		{
		    int k=read();
		    printf("%lld\n",q2(k));
		}
	}
	return 0;
}

```


---

## 作者：zhiyangfan (赞：15)

> LCT 能把任何优雅的题目变成暴力。 ——某题解区

> 所有能用树剖做的题 LCT 都能做。 ——忘了是谁说的了

### 题目
给出一棵 $n$ 个结点的树，每个结点有权值。共 $q$ 次操作，操作有以下三种：
- 把根换为 $u$。
- 给出 $u,v,x$，把 $\mathrm{lca}(x,y)$ 的子树内所有结点权值加上 $x$。
- 给出 $v$，询问 $v$ 的子树内所有点权值和。

($1\le n,q\le10^5,|x|\le 10^8$)
### 题解
~~看到 tag 里面有树剖果断选择写 LCT。~~

在说本题的核心操作——子树加——之前，我们先来看一个简单的 trick，用 LCT 求两点的 $\rm lca$。这个比较简单，两次 `access` 操作就好，如下：
```cpp
inline int access(int x)
{
    int y = 0;
    while (x) { splay(x); Rs(x) = y; pushup(x); x = Fa(y = x); }
    return y;
}
int lca = (access(u), access(v));
```
原因也很显然，我们拉完 $u$ 到根的实链后再拉 $v$ 的。则最后一个需要调整的实链顶对应的结点自然是 $\mathrm{lca}(u,v)$。

好了，接下来进入重头戏，如何用 LCT 去维护子树加。因为维护子树和我们要单独维护一下结点对应虚子树的信息，所以维护子树加其实也是要对应去修改这个虚子树的信息。但不可能直接对虚子树内的每个结点一一修改信息，也不能通过下传标记的方法（因为它们根本就不在一个 $\rm splay$ 里）去修改，所以我们要考虑新的方法。

注意到虚子树的一次修改对里面每个结点都是相同的且可以保存在根节点里，所以我们可以对每个结点开一个 `dlt` 表示当前结点虚子树已经加了多少值了。这样当结点的虚实发生改变时再根据 `dlt` 进行修改就好了，其实跟下传标记的思想是类似的。

来看具体代码实现，首先是我们需要维护什么。注意到下放 `dlt` 其实是针对对应结点的所有子树的（包括虚子树和实子树），所以要维护一个 `dtag` 表示虚子树的下传标记，`stag` 表示实子树的下传标记，然后每次虚实变化的时候对应修改就好。为了维护 `dtag` 和 `stag` 下传时对结点总和 `sum` 造成的影响，我们需要虚子树大小之和 `szt` 和实子树大小之和 `szc`，而为了维护它们，我们又需要每个点的虚子树大小 `szl` 和每个点的子树（原树上的）大小 `sz`。其余要维护的就没有什么好说的了，都是一些比较常规的操作。

然后是一些比较关键的函数，首先是下传 `dtag` 和 `stag` 的 `addD`，`addS`。
```cpp
void addS(int x, ll v) 
{  
    if (!x) return ;
    node[x].stag += v; node[x].w += v;
    node[x].sum += v * node[x].szc;
}
void addD(int x, ll v)
{
    if (!x) return ;
    node[x].dtag += v; node[x].dlt += v;
    node[x].sum += v * node[x].szt;
}
```
需要注意的点是，对于实子树的下放，要算上当前结点，对于虚子树的下放不要算上当前结点。以及对于 `sum` 的更新用的 `sz` 值到底是哪个。

然后是维护虚实变化的 `ins`，`del`。
```cpp
void ins(int x, int y) 
{ 
    if (!y) return ;
    addS(y, -node[x].dlt); addD(y, -node[x].dlt);
    node[x].szl += node[y].sz; node[x].suml += node[y].sum;
}
void del(int x, int y)
{
    if (!y) return ;
    node[x].szl -= node[y].sz; node[x].suml -= node[y].sum;
    addS(y, node[x].dlt); addD(y, node[x].dlt);
}
```
需要注意的点是，加入虚子树时应该先去掉 `dlt` 再加入，而从虚子树删去时应该先删去再撤销 `dlt` 的影响。

还有一点，本题中为了方便，不再维护实子树上的信息，处理询问时这样处理：
```cpp
ll ask(int rt, int x) { return split(rt, x), (node[x].w + node[x].suml + node[x].szl * node[x].dlt); }
```
直接把 `x` 和 `rt` 拉到一个实链里，这样 `x` 的子树就全是虚子树了，直接回答虚子树的信息就好。
### 完整代码及后续
```cpp
#include <cstdio>
#include <algorithm>
#define Ls(x) (node[x].ch[0])
#define Rs(x) (node[x].ch[1])
#define Fa(x) (node[x].fa)
const int N = 1e5 + 10; typedef long long ll;
int st[N], tp;
struct LCT
{
    struct Splay
    {
        //sz 表示这个点在树上的子树大小，szl 表示这个点的虚子树大小
        //szc表示这个点的所在实子树大小，szt 表示这个点所在实子树内所有点的虚子树大小之和
        //sum 表示这个点的树上的子树权值和，suml 表示这个点虚子树子树权值和
        //dlt 表示这个点子树已经加了多少值了
        //dtag 表示要下放到虚子树的标记，stag 表示要下放到实子树的标记
        int fa, ch[2], revFlag; ll w;
        int sz, szl, szc, szt; ll suml, sum, dlt, dtag, stag;
    }node[N]; 
    void pushup(int x) 
    {  
        node[x].sz = node[Ls(x)].sz + node[Rs(x)].sz + node[x].szl + 1;
        node[x].szc = node[Ls(x)].szc + node[Rs(x)].szc + 1;
        node[x].szt = node[Ls(x)].szt + node[Rs(x)].szt + node[x].szl;
        node[x].sum = node[Ls(x)].sum + node[Rs(x)].sum + node[x].w + node[x].suml + node[x].szl * node[x].dlt;
    }
    void reverse(int x) { if (!x) return ; std::swap(Ls(x), Rs(x)); node[x].revFlag ^= 1; }
    void addS(int x, ll v) 
    {  
        if (!x) return ;
        node[x].stag += v; node[x].w += v;
        node[x].sum += v * node[x].szc;
    }
    void addD(int x, ll v)
    {
        if (!x) return ;
        node[x].dtag += v; node[x].dlt += v;
        node[x].sum += v * node[x].szt;
    }
    void pushdown(int x)
    {
        if (node[x].revFlag)
        {
            reverse(Ls(x)); reverse(Rs(x));
            node[x].revFlag = 0;
        }
        if (node[x].stag)
        {
            addS(Ls(x), node[x].stag); addS(Rs(x), node[x].stag);
            node[x].stag = 0;
        }
        if (node[x].dtag)
        {
            addD(Ls(x), node[x].dtag); addD(Rs(x), node[x].dtag);
            node[x].dtag = 0;
        }
    }
    int get(int x) { return Rs(Fa(x)) == x; }
    int nRoot(int x) { return Rs(Fa(x)) == x || Ls(Fa(x)) == x; }
    void rotate(int x)
    {
        int fa = Fa(x), gf = Fa(fa), d = get(x), dd = get(fa);
        if (nRoot(fa)) node[gf].ch[dd] = x;
        node[fa].ch[d] = node[x].ch[d ^ 1]; Fa(node[x].ch[d ^ 1]) = fa;
        node[x].ch[d ^ 1] = fa; Fa(fa) = x; Fa(x) = gf;
        pushup(fa); pushup(x);
    }
    void splay(int x)
    {
        int y = st[tp = 1] = x;
        while (nRoot(y)) st[++tp] = y = Fa(y);
        while (tp) pushdown(st[tp--]);
        for (; nRoot(x); rotate(x))
            if (nRoot(Fa(x))) rotate(get(x) == get(Fa(x)) ? Fa(x) : x);
        pushup(x);
    }
    void ins(int x, int y) 
    { 
        if (!y) return ;
        addS(y, -node[x].dlt); addD(y, -node[x].dlt);
        node[x].szl += node[y].sz; node[x].suml += node[y].sum;
    }
    void del(int x, int y)
    {
        if (!y) return ;
        node[x].szl -= node[y].sz; node[x].suml -= node[y].sum;
        addS(y, node[x].dlt); addD(y, node[x].dlt);
    }
    int access(int x)
    {
        int y = 0;
        while (x)
        {
            splay(x); ins(x, Rs(x)); del(x, y);
            Rs(x) = y; pushup(x); x = Fa(y = x);
        }
        return y;
    }
    void makeroot(int x) { access(x); splay(x); reverse(x); }
    void split(int x, int y) { makeroot(x); access(y); splay(y); }
    void link(int x, int y) { makeroot(x); makeroot(y); access(y); Fa(x) = y; Rs(y) = x; pushup(y); }
    void add(int rt, int x, ll v)
    {   
        split(rt, x); node[x].dlt += v; node[x].w += v;
        node[x].sum += (node[x].szl + 1) * v;
    }   
    ll ask(int rt, int x) { return split(rt, x), (node[x].w + node[x].suml + node[x].szl * node[x].dlt); }
}lct;
int main()
{
    int n, q, rt = 1; scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i) scanf("%lld", &lct.node[i].w), lct.pushup(i);
    for (int i = 1, x, y; i < n; ++i) scanf("%d%d", &x, &y), lct.link(x, y);
    for (int i = 1, opt, u, v, x, lca; i <= q; ++i)
    {
        scanf("%d", &opt);
        switch (opt)
        {
            case 1:
                scanf("%d", &v); rt = v;
                break;
            case 2:
                scanf("%d%d%d", &u, &v, &x); lct.makeroot(rt);
                lca = (lct.access(u), lct.access(v)); lct.add(rt, lca, x);
                break;
            case 3:
                scanf("%d", &v); 
                printf("%lld\n", lct.ask(rt, v));
        }
    }
    return 0;
}
```
感谢 $\tt \color{black}j\color{red}erry3128$ 对我 LCT 的耐心指导和代码参考。

本题中需要维护的信息是满足可加性的，但如果不满足呢？我们就需要对虚子树开一个平衡树维护了，具体见：[P3979 遥远的国度](https://www.luogu.com.cn/problem/P3979)。

萌新初学 LCT 维护子树信息，如果有理解偏颇或者没理解到的地方请轻喷并指出qwq

---

## 作者：Farkas_W (赞：9)

$$\text{前言}$$

$\quad$可以看看我的一篇blog[关于树链剖分"换根操作"笔记](https://www.luogu.com.cn/blog/Farkas/guan-yu-shu-lian-pou-fen-huan-gen-cao-zuo-bi-ji)(内容都差不多)

$\quad$另外洛谷上还有一道关于换根操作的题目：[P3979 【遥远的国度】](https://www.luogu.com.cn/problem/P3979)([我的题解](https://www.luogu.com.cn/blog/Farkas/solution-p3979))

$$\text{关于题目要求的操作}$$

$\quad$其实可以发现在一棵树中，只有父亲(祖先)，儿子(子树)，深度等信息会因为根节点的变化而变化，所以题目一般需要你有换根操作，子树修改操作，求 $LCA$ (最近公共祖先)，我们分别来考虑一下。(可以看看下面这张图来理解，题目中的图)

![](https://cdn.luogu.com.cn/upload/image_hosting/gmu2iblr.png))

$$\text{换根}$$

$\quad$因为每换一次根，树中的很多信息都会改变，不可能每次换根都跑两便 $dfs$ 预处理，所以我们考虑其他方法，对于单纯的换根操作，只需要设置一个全局变量 $root$ 来存储根的编号( $root$ 初始化为 $1$ ，默认以 $1$ 为根)，对于其他操作，再通过分类讨论 $root$ 的位置来进行操作。

$$\text{LCA(最近公共祖先)}$$

$\quad$因为这题我们肯定用树链剖分解题，所以对于原图( $root==1$ )的情况下 $LCA$ 的求法肯定是使用树链剖分的(~~当然如果读者愿意专门打个倍增，那么你们随意~~)

$\quad$**注意：(小写) $lca(x,y)$ 表示在以1为根的树中 $x$ 和 $y$ 的最近公共祖先，(大写) $LCA(x,y)$ 表示在以 $root$ 为根的树中 $x$ 和 $y$ 的最近公共祖先。**

```cpp
il int lca(int x,int y) //模板树链剖分求LCA
{
  int fx=top[x],fy=top[y];
  while(fx!=fy)
    {
      if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
      x=father[fx];fx=top[x];
    }
  if(dep[x]>dep[y])swap(x,y);
  return x;
}
```

$\quad$接下来我们就要对 $root$ 的位置进行分类讨论了，代码先贴出来给你们看看。

```cpp
il int LCA(int x,int y)
{
  if(dep[x]>dep[y])swap(x,y);
  int xr=lca(x,root),yr=lca(y,root),xy=lca(x,y);
  if(xy==x)
  {
  	if(xr==x){if(yr==y)return y;return yr;}
  	return x;
  }
  if(xr==x)return x;if(yr==y)return y;
  if((xr==root&&xy==yr)||(yr==root&&xy==xr))return root;
  if(xr==yr)return xy;
  if(xy!=xr)return xr;return yr;
}
```

$\quad$另外我们可以再画几张图来方便理解。

 一.当 $lca(x,y)==x$ (可以先按深度调序， $dep[x]<=dep[y]$)
 
   ![](https://cdn.luogu.com.cn/upload/image_hosting/hk78elxs.png)
$\quad$ $1$. 情况 $1$ ：$root$ 在 $x$ 的子树中，也在 $y$ 的子树中，即 $lca(x,root)==x$ && $lca(y,root)==y$ ，此时 $LCA(x,y)$ 是 $y$ ，因为图要反过来看(以 $root$ 为根)

$\quad$ $2$. 情况 $2$ ： $root$ 在 $x$ 的子树中，但不在 $y$ 的子树中，即 $lca(x,root)$ ，此时 $LCA(x,y)$ 是 $lca(y,root)$。

$\quad$ $3$. 情况 $3$ ：其他情况下， $LCA(x,y)$ 就是 $x$ 。

二.当 $lca(x,y)!=x$ (因为 $dep[x]<=dep[y]$，所以 $lca(x,y)!=y$ ， $x$ , $y$ 在不同子树上)

![](https://cdn.luogu.com.cn/upload/image_hosting/jg4eo3ji.png)

$\quad$ 1. 情况1：( $lca(x,root)==x$ )||( $lca(x,root)==x$ ),root在x(或y)的子树中时， $LCA(x,y)$ 为 $x$ (或 $y$ )，显然。

$\quad$ 2. 情况2：( $lca(x,root)==root$ && $lca(x,y)==lca(y,root)$ )||( $lca(y,root)==root$ && $lca(x,y)==lca(x,root)$)，即 $root$ 在 $x$ 到 $y$ 的简单路径上时，答案为 $root$ 。(也可以用深度判断， ( $lca(x,root)===root$ && $dep[root]>=dep[lca(x,y)]$ )||( $lca(y,root)==root$ && $dep[root]>=dep[lca(x,y)]$ ))

$\quad$ 3. 情况3： $lca(x,root)==lca(y,root)$ ，即 $root$ 在上方时，$LCA(x,y)$ 为 $lca(x,y)$ 。

$\quad$ 4. 情况4：当 $root$ 在$x$，$y$ 的链上节点的子树中时， $LCA(x,y)$ 为那个链上节点。

$\quad$这样就把树上所有 $root$ 位置的情况都考虑到了，不重不漏。

$$\text{子树修改(查询)}$$

![](https://cdn.luogu.com.cn/upload/image_hosting/4ar4m3w5.png)

$\quad$ 情况 $1$ ：当 $x=root$ 时， $x$ 就是此时整棵树的根，那么就是全局修改(查询)。

$\quad$ 情况 $2$ ：当 $root$ 在x子树中时，就需要特别判断了，根据图像我们可以发现此时x的真正子树是包括除了 $root$ 方向上的子树之外其他所有节点。

$\quad$ 情况 $3$ ：其他情况下 $x$ 的子树以 $root$ 为根和以 $1$ 为根是一样的。

```cpp
il int find(int x,int y)//寻找x中root所在的儿子节点
{
  int fx=top[x],fy=top[y];
  while(fx!=fy)
    {
      if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
      if(father[fx]==y)return top[x];
      x=father[fx];fx=top[x];
    }
  if(dep[x]>dep[y])swap(x,y);
  return son[x];
}
il int query1(int x)
{
  int res=0;
  if(x==root){return query(1,1,n,1,n);}
  if(seg[root]>=seg[x]&&seg[root]<=seg[x]+size[x]-1){//判断root在x的子树中
    res+=query(1,1,n,1,n);int y=find(x,root);
    res-=query(1,1,n,seg[y],seg[y]+size[y]-1);
    return res;
  }
  return query(1,1,n,seg[x],seg[x]+size[x]-1);
}
```

$$\text{完整代码}$$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
using namespace std;
#define int long long
#define next neee
#define re register int
#define il inline
#define inf 1e18
il int read(){
	int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')f=-1,ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
    return x*f;}
il void print(int x)
{
	if(x<0)putchar('-'),x=-x;
    if(x/10)print(x/10);
    putchar(x%10+'0');}
const int N=2e5+5;
int n,m,next[N<<1],go[N<<1],head[N],tot,a[N],top[N],root;
int sum[N<<2],seg[N],rev[N],son[N],size[N],dep[N],father[N],c[N<<2];
il void Add(int x,int y)
{next[++tot]=head[x];head[x]=tot;go[tot]=y;}
il void dfs1(int x,int fa)
{
  father[x]=fa;dep[x]=dep[fa]+1;size[x]=1;
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(y==fa)continue;
      dfs1(y,x);
      size[x]+=size[y];
      if(size[y]>size[son[x]])son[x]=y;
    }
}
il void dfs2(int x,int topf)
{
  top[x]=topf;seg[x]=++seg[0];rev[seg[x]]=x;
  if(!son[x])return;
  dfs2(son[x],topf);
  for(re i=head[x],y;i,y=go[i];i=next[i])
    {
      if(top[y])continue;
      dfs2(y,y);
    }
}
il void build(int k,int l,int r)
{
  if(l==r){sum[k]=a[rev[l]];return;}
  int mid=l+r>>1;
  build(k<<1,l,mid);build(k<<1|1,mid+1,r);
  sum[k]=sum[k<<1]+sum[k<<1|1];
}
il void ADD(int k,int l,int r,int v)
{sum[k]+=(r-l+1)*v;c[k]+=v;}
il void pushdown(int k,int l,int r,int mid)
{
  if(l==r){c[k]=0;return;}
  ADD(k<<1,l,mid,c[k]);ADD(k<<1|1,mid+1,r,c[k]);
  c[k]=0;}
il void change1(int k,int l,int r,int x,int y,int z)
{
  if(x<=l&&y>=r){ADD(k,l,r,z);return;}
  int mid=l+r>>1;
  if(c[k])pushdown(k,l,r,mid);
  if(x<=mid)change1(k<<1,l,mid,x,y,z);
  if(y>mid)change1(k<<1|1,mid+1,r,x,y,z);
  sum[k]=sum[k<<1]+sum[k<<1|1];
}
il int query(int k,int l,int r,int x,int y)
{
  if(x<=l&&y>=r)return sum[k];
  int mid=l+r>>1,res=0;
  if(c[k])pushdown(k,l,r,mid);
  if(x<=mid)res+=query(k<<1,l,mid,x,y);
  if(y>mid)res+=query(k<<1|1,mid+1,r,x,y);
  return res;
}
il int lca(int x,int y)
{
  int fx=top[x],fy=top[y];
  while(fx!=fy)
    {
      if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
      x=father[fx];fx=top[x];
    }
  if(dep[x]>dep[y])swap(x,y);
  return x;
}
il int LCA(int x,int y)
{
  if(dep[x]>dep[y])swap(x,y);
  int xr=lca(x,root),yr=lca(y,root),xy=lca(x,y);
  if(xy==x){if(xr==x){if(yr==y)return y;return yr;}return x;}
  if(xr==x)return x;if(yr==y)return y;
  if((xr==root&&xy==yr)||(yr==root&&xy==xr))return root;if(xr==yr)return xy;
  if(xy!=xr)return xr;return yr;
}
il int find(int x,int y)//寻找x中root所在的儿子节点
{
  int fx=top[x],fy=top[y];
  while(fx!=fy)
    {
      if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
      if(father[fx]==y)return top[x];
      x=father[fx];fx=top[x];
    }
  if(dep[x]>dep[y])swap(x,y);
  return son[x];
}
il void change2(int x,int z)
{
  if(x==root){change1(1,1,n,1,n,z);return;}
  if(seg[root]>=seg[x]&&seg[root]<=seg[x]+size[x]-1){//判断root在x的子树中
    change1(1,1,n,1,n,z);int y=find(x,root);
    change1(1,1,n,seg[y],seg[y]+size[y]-1,-z);
  }
  else change1(1,1,n,seg[x],seg[x]+size[x]-1,z);
}
il int query1(int x)
{
  int res=0;
  if(x==root){return query(1,1,n,1,n);}
  if(seg[root]>=seg[x]&&seg[root]<=seg[x]+size[x]-1){//判断root在x的子树中
    res+=query(1,1,n,1,n);int y=find(x,root);
    res-=query(1,1,n,seg[y],seg[y]+size[y]-1);
    return res;
  }
  return query(1,1,n,seg[x],seg[x]+size[x]-1);
}
signed main()
{
  n=read();m=read();
  for(re i=1;i<=n;i++)a[i]=read();
  for(re i=1;i<n;i++){re x=read(),y=read();Add(x,y);Add(y,x);}
  root=1;dfs1(1,0);dfs2(1,1);build(1,1,n);
  while(m--)
    {
      re k=read();
      if(k==1)root=read();
      if(k==2){re x=read(),y=read(),z=read();change2(LCA(x,y),z);}
      if(k==3){re x=read();print(query1(x));putchar('\n');}
    }
  return 0;
}
```
$\quad$码题解不易，如果觉得不错，不妨点个赞呗！

---

## 作者：jerry3128 (赞：7)

## Euler Tour Tree

- 这个能换根，并不是 splay 维护括号序那个简化版。
- 因为只有子树操作，并且维护的信息为和，具有交换律，那么 ETT 也就够对本题进行维护。
- 考虑使用 ETT 对本题的树进行维护，因为 ETT 自身是将一棵树拍平成欧拉环游序，对于树上一些树形结构的信息有损失。所以考虑使用一颗 LCT 对 ETT 的结构进行辅助维护。
- 我们只在代表节点维护一个节点的权值，因为没有 link 和 cut 操作，所以不涉及 ETT 上点的删除，故也不需要数据的转运，代码量大大减小。
- 换根就是区间平移，新根前面的欧拉序放在后面就行了，因为一个欧拉序就像一个圈把树圈起来，从哪里开始其实无伤大雅。
- 子树修改和查询直接定位子树区间信息就行了。
- 同时本题在 LCT 与 ETT 上，LCT 只对结构进行辅助，二者之间的操作并没有互相映射，所以复杂度仍然只有 $O(\log n)$ 单次操作。

```
//ayame保佑，夸哥保佑，狗妈保佑，MDR保佑，锉刀怪保佑，M99保佑，克爹保佑
#include<bits/stdc++.h>
using namespace std;
int p1=1000000,p2=0;
char buf[1000005],wb[1000005];
int gc() {
	if(p1>=1000000)fread(buf,1,1000000,stdin),p1=0;
	return buf[p1++];
}
#define gc getchar
#define Loli true
#define Kon xor true
long long getint() {
	long long ret=0,flag=1;
	char c=gc();
	while(c<'0'||c>'9') {
		if(c=='-')flag=-1;
		c=gc();
	}
	while(c<='9'&&c>='0') {
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=gc();
	}
	return ret*flag;
}
void pc(char x) {
	if(p2>=1000000)fwrite(wb,1,1000000,stdout),p2=0;
	wb[p2++]=x;
}
void wrt(long long x) {
	if(x<0)pc('-'),x=-x;
	int c[24]= {0};
	if(!x)return pc('0'),void();
	while(x)c[++c[0]]=x%10,x/=10;
	while(c[0])pc(c[c[0]--]+'0');
}
int n,m;
vector<int> vec[100005];
int ind[200005],sign,vst[200005],rep[200005];
void dfs(int x,int prt){
	ind[++sign]=x;
	for(int y:vec[x])if(y^prt)dfs(y,x),ind[++sign]=x;
}
namespace LCT{
	struct node {
		int ch[2],fa,rev,pre,suf;
	} v[100005];
	bool isroot(int x){
		return v[v[x].fa].ch[0]!=x&&v[v[x].fa].ch[1]!=x;
	}
	void tag_rev(int x) {
		swap(v[x].ch[0],v[x].ch[1]);
		swap(v[x].pre,v[x].suf);
		v[x].rev^=1;
	}
	void push_down(int rt) {
		if(v[rt].rev) {
			tag_rev(v[rt].ch[0]);
			tag_rev(v[rt].ch[1]);
			v[rt].rev=0;
		}
	}
	void push_up(int x){
		v[x].pre=v[x].ch[0]?v[v[x].ch[0]].pre:x;
		v[x].suf=v[x].ch[1]?v[v[x].ch[1]].suf:x;
	}
	void rot(int x) {
		int p=v[x].fa,g=v[p].fa;
		bool d=v[p].ch[1]==x;
		if(!isroot(p))v[g].ch[v[g].ch[1]==p]=x;
		v[p].ch[d]=v[x].ch[d^1];
		v[v[x].ch[d^1]].fa=p;
		v[x].ch[d^1]=p;
		v[x].fa=g,v[p].fa=x;
		push_up(p),push_up(x);
	}
	void pre_push_down(int x) {
		if(!isroot(x))pre_push_down(v[x].fa);
		push_down(x);
	}
	void splay(int x) {
		pre_push_down(x);
		while(!isroot(x)) {
			int p=v[x].fa,g=v[p].fa;
			if(!isroot(p))rot(v[g].ch[0]==p^v[p].ch[0]==x?x:p);
			rot(x);
		}
	}
	int access(int x) {
		int ret=0;
		for(int y=0;x;y=x,x=v[x].fa)
			splay(x),v[x].ch[1]=y,push_up(ret=x);
		return ret;
	}
	void makeroot(int x) {
		access(x),splay(x),tag_rev(x);
	}
	void link(int x,int y) {
		makeroot(y),v[y].fa=x;
	}
	void cut(int x){
		access(x),splay(x),v[v[x].ch[0]].fa=0,v[x].ch[0]=0,push_up(x);
	}
	int ask(int x){
		return access(x),splay(x),v[v[x].ch[0]].suf;
	}
}
namespace ETT{
	int root,tot;
	map<int,int> e[100005];
	struct node{
		int ch[2],fa,id,sz,rep,pre,suf;
		long long sum,val,stag;
	}v[200005];
	bool isroot(int x){
		return v[v[x].fa].ch[0]!=x&&v[v[x].fa].ch[1]!=x;
	}
	void push_up(int x){
		if(!x)return;
		v[x].pre=v[x].ch[0]?v[v[x].ch[0]].pre:x;
		v[x].suf=v[x].ch[1]?v[v[x].ch[1]].suf:x;
		v[x].sz=v[v[x].ch[0]].sz+v[v[x].ch[1]].sz+v[x].rep;
		v[x].sum=v[v[x].ch[0]].sum+v[v[x].ch[1]].sum+v[x].val;
	}
	void push_stag(int x,long long val){
		if(!x)return;
		v[x].sum=v[x].sum+v[x].sz*val,v[x].val=v[x].val+v[x].rep*val;
		v[x].stag=v[x].stag+val;
	}
	void push_down(int x){
		if(v[x].stag){
			push_stag(v[x].ch[0],v[x].stag);
			push_stag(v[x].ch[1],v[x].stag);
			v[x].stag=0;
		}
	}
	void pre_push_down(int rt){
		if(v[rt].fa)pre_push_down(v[rt].fa);
		push_down(rt);
	}
	int getpoint(int x,int lim=-1){
		if(e[e[x].begin()->first][x]!=lim)return e[e[x].begin()->first][x];
		return e[e[x].rbegin()->first][x];
	}
	int build(int l,int r){
		int mid=(l+r)>>1,x=++tot;v[x].id=ind[mid];v[x].stag=0,push_up(x);
		if(!vst[v[x].id])vst[v[x].id]=1,v[x].rep=1,rep[v[x].id]=x;
		if(l<mid)v[x].ch[0]=build(l,mid-1),v[v[x].ch[0]].fa=x,e[v[v[v[x].ch[0]].suf].id][v[x].id]=x;
		if(mid<r)v[x].ch[1]=build(mid+1,r),v[v[x].ch[1]].fa=x,e[v[x].id][v[v[v[x].ch[1]].pre].id]=v[v[x].ch[1]].pre;
		return push_up(x),x;
	}
	void rot(int x){
		int p=v[x].fa,g=v[p].fa;
		bool d=v[p].ch[1]==x;
		if(!isroot(p))v[g].ch[v[g].ch[1]==p]=x;
		v[p].ch[d]=v[x].ch[d^1];
		v[v[x].ch[d^1]].fa=p;
		v[x].ch[d^1]=p;
		v[p].fa=x,v[x].fa=g;
		push_up(p),push_up(x);
	}
	void splay(int x,int f=0){
		pre_push_down(x);
		while(v[x].fa!=f){
			int p=v[x].fa,g=v[p].fa;
			if(g!=f)rot(v[g].ch[0]==p^v[p].ch[0]==x?x:p);
			rot(x);
		}
	}
	void makeroot(int x){
		if(root==x)return;
		LCT::makeroot(x),root=x,x=getpoint(x);
		splay(x),splay(x=v[v[x].ch[1]].pre);
		int y=v[x].ch[0];
		v[y].fa=0,v[x].ch[0]=0,push_up(x);
		splay(x=v[x].suf),v[x].ch[1]=y,v[y].fa=x,push_up(x);
	}
	void add(int x,long long val){
		if(x==root)return splay(1),push_stag(1,val);
		int prt=LCT::ask(x),l=e[prt][x],r=e[x][prt];
		splay(l),splay(r,l);
		v[l].val=v[l].val+v[l].rep*val,push_stag(v[r].ch[0],val);
		push_up(r),push_up(l);
	}
	long long ask(int x){
		if(x==root)return splay(1),v[1].sum;
		int prt=LCT::ask(x),l=e[prt][x],r=e[x][prt];
		splay(l),splay(r,l);
		return (v[l].val+v[v[r].ch[0]].sum);
	}
}
int main() {
//	freopen("lct.in","r",stdin);
//	freopen("lct.out","w",stdout);
	n=getint(),m=getint(),ETT::root=1;
	static int a[100005];
	for(int i=1;i<=n;i++)a[i]=getint();
	for(int i=1;i<n;i++){
		int u=getint(),v=getint();
		vec[u].push_back(v),vec[v].push_back(u);
		LCT::link(u,v);
	}
	dfs(1,0),ETT::build(2,sign),LCT::makeroot(1);
	ETT::splay(1),ETT::e[1][ETT::v[ETT::v[1].pre].id]=ETT::v[1].pre;
	for(int i=1;i<=n;i++){
		int x=ETT::getpoint(i);
		ETT::splay(x),ETT::v[x].val=a[i],ETT::push_up(x);
	}
	for(int i=1;i<=m;i++){
		int opt=getint();
		if(opt==1)ETT::makeroot(getint());
		if(opt==2){int x=getint(),y=getint();ETT::add((LCT::access(x),LCT::access(y)),getint());}
		if(opt==3)wrt(ETT::ask(getint())),pc('\n');
	}
	fwrite(wb,1,p2,stdout);
	return Loli Kon;
}
```

---

## 作者：xunzhen (赞：4)

首先，如果没有第一个操作，那这就是一个线段树+LCA。其实第一个操作，并不需要真的去旋转根(一直都以1为根)，只需要在修改和查询的时候分类讨论一下即可。如果新的树根没有在当前操作的子树中就不用管它，如果新的树根正好就是当前子树，就直接操作整棵树。如果新的树根在子树里，就利用容斥原理，先操作整棵树，再把多余的部分排除掉，具体见代码注释。

~~150行工业代码~~

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#define maxn 100010
using namespace std;
typedef long long LL;
vector<int> g[maxn];
struct node{
	LL w,tag;
}A[maxn*4];
int n,q,root=1,dfn=0;
int w[maxn],d[maxn],fa[maxn][22],to[maxn],rk[maxn],L[maxn],R[maxn];
//线段树板子
#define ls (rt<<1)
#define rs (rt<<1|1)
void push_up(int rt){
	A[rt].w=A[ls].w+A[rs].w;
}
void push_down(int rt,int l,int r){
	A[ls].tag+=A[rt].tag;
	A[rs].tag+=A[rt].tag;
	A[rt].w+=A[rt].tag*(LL)(r-l+1);
	A[rt].tag=0;
}
void build(int rt,int l,int r){
	if (l==r){
		A[rt].w=w[rk[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(rt);
}
//dfs一遍预处理
void dfs(int now,int f){
	//to[]:树->线段树 rk[]:线段树->树
	to[now]=++dfn; rk[dfn]=now;
	d[now]=d[f]+1; fa[now][0]=f;
	for (int i=1;i<=20;i++)
		fa[now][i]=fa[fa[now][i-1]][i-1];
	L[now]=R[now]=to[now];
	for (int i=0;i<g[now].size();i++){
		int son=g[now][i];
		if (son!=f){
			dfs(son,now);
			L[now]=min(L[now],L[son]);
			R[now]=max(R[now],R[son]);
		}
	}
}
//LCA板子
void jump(int &x,int c){	//x点在树上向上跳c层
	for (int i=0;i<=20;i++){
		if (c&1) x=fa[x][i];
		c>>=1;
	}
}
int lca(int x,int y){
	if (d[x]<d[y]) swap(x,y);
	jump(x,d[x]-d[y]);
	if (x==y) return x;
	for (int i=20;i>=0;i--)
		if (fa[x][i]!=fa[y][i]){
			x=fa[x][i];
			y=fa[y][i];
		}
	return fa[x][0];
}
int check_son(int u,int v){
	if (lca(u,v)==u) return 1;
	return 0;
}
//线段树板子
void change(int rt,int l,int r,int L,int R,int x){
	if (l>=L && r<=R){
		A[rt].tag+=x;
		LL tmp=x*(LL)(r-l+1);
		while (rt){
			rt>>=1;
			A[rt].w+=tmp;
		}
		return;
	}
	int mid=(l+r)>>1;
	if (L<=mid) change(ls,l,mid,L,R,x);
	if (R>mid) change(rs,mid+1,r,L,R,x);
}
LL query(int rt,int l,int r,int L,int R){
	if (l>=L && r<=R) return A[rt].w+A[rt].tag*(LL)(r-l+1);
	int mid=(l+r)>>1;
	LL sum=0;
	push_down(rt,l,r);
	if (L<=mid) sum+=query(ls,l,mid,L,R);
	if (R>mid) sum+=query(rs,mid+1,r,L,R);
	return sum;
}
//3个操作
void Change_root(int v){
	root=v;
}
void Change(int u,int v,int x){
	int now=lca(u,v);
	if (!check_son(now,root)){
		change(1,1,n,L[now],R[now],x);
		return;
	}
	change(1,1,n,1,n,x);
	int a=lca(root,u),b=lca(root,v);
	if (d[a]>d[b]) u=a;
	else u=b;
	v=root;
	if (u==v) return;
	jump(v,d[v]-d[u]-1);
	change(1,1,n,L[v],R[v],-x);
}
LL Query(int v){
	if (!check_son(v,root)) return query(1,1,n,L[v],R[v]);
	int u=root;
	if (u==v) return query(1,1,n,1,n);
	jump(u,d[u]-d[v]-1);
	return query(1,1,n,1,n)-query(1,1,n,L[u],R[u]);
}
int main(){
#ifdef xunzhen
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
#endif
	cin>>n>>q;
	for (int i=1;i<=n;i++) scanf("%d",&w[i]);
	for (int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs(1,0);
	build(1,1,n);
	for (int i=1;i<=q;i++){
		int k,u,v,x;
		scanf("%d",&k);
		if (k==1){
			scanf("%d",&v);
			Change_root(v);
		}
		if (k==2){
			scanf("%d%d%d",&u,&v,&x);
			Change(u,v,x);
		}
		if (k==3){
			scanf("%d",&v);
			printf("%I64d\n",Query(v));	//CF上要用I64d
		}
	}
	return 0;
}
```

---

## 作者：James_Brady (赞：3)

如果没有换根操作，这道题就是一道裸的dfs序+线段树

但是，出题人给我们加了一个换根操作

好了，我们不可能每次都重构树，太浪费时间了

我们就以1为根，来分类讨论

第一，R在u的子树内，如图：

![无标题.png](https://i.loli.net/2019/08/20/FEaTvWsjX4mbSgH.png)

此时要修改（查询）的点就是红色的点和U（所有点除去R所在的子树）

第二，u在R的子树内，如图：

![无标题2.png](https://i.loli.net/2019/08/20/lrQIjMYaqWZ7oR1.png)
 
此时要修改（查询）的点就是蓝色的点和U（U所在的子树）

第三，如果u就是R，易得出要修改（查询）的就是整颗树

重点是如何通过u，v求U？

依然分类讨论：

如果u，v分居R的上下两侧，则U就是R

如果同居下侧或上侧，则U为lca(u,v)

总结得到：U为lca(u,v)，lca(u,R)，lca(v,R)中最深的一个

code：


```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 100010
#define ll long long
#define lson id<<1,l,m
#define rson id<<1|1,m+1,r
using namespace std;
ll root=1,n,L[N],R[N],q,dep[N];
ll head[N],tot,cnt,p[N][25],dfn[N];
ll s[N<<2],lzy[N<<2],len[N<<2],f[N];
struct node{
	ll v;
	ll nxt;
}e[N<<1];
void add(ll u,ll v)
{
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(ll u,ll fa)
{
	L[u]=++tot;
	dfn[tot]=u;
	dep[u]=dep[fa]+1;
	p[u][0]=fa;
	for(ll i=1;i<=20;i++)
	p[u][i]=p[p[u][i-1]][i-1];
	for(ll i=head[u];i;i=e[i].nxt)
	{
		ll v=e[i].v;
		if(v==fa)
		continue;
		dfs(v,u);
	}
	R[u]=tot;
}
ll lca(ll u,ll v)
{
	if(dep[u]>dep[v])
	swap(u,v);
	for(ll i=20;i>=0;i--)
	if(dep[u]<=dep[v]-(1<<i))
	v=p[v][i];
	if(u==v)
	return u;
	for(ll i=20;i>=0;i--)
	{
		if(p[u][i]==p[v][i])
		continue;
		u=p[u][i];
		v=p[v][i];
	}
	return p[u][0];
}
ll jumping(ll u,ll step)
{
	for(ll i=0;i<=20;i++)
	if(step&(1<<i))
	u=p[u][i];
	return u;
}
ll lcaa(ll a,ll b,ll c)
{
	ll p1=lca(a,b),p2=lca(b,c),p3=lca(a,c);
	if(dep[p1]<dep[p2])
	p1=p2;
	if(dep[p1]<dep[p3])
	p1=p3;
	return p1;
}
void pushup(ll id)
{
	s[id]=s[id<<1]+s[id<<1|1];
}
void pushdown(ll id)
{
	if(lzy[id])
	{
		lzy[id<<1]+=lzy[id];
		lzy[id<<1|1]+=lzy[id];
		s[id<<1]+=lzy[id]*len[id<<1];
		s[id<<1|1]+=lzy[id]*len[id<<1|1];
		lzy[id]=0;
	}
}
void build(ll id,ll l,ll r)
{
	len[id]=r-l+1;
	if(l==r)
	{
		s[id]=f[dfn[l]];
		return;
	}
	ll m=(l+r)>>1;
	build(lson);
	build(rson);
	pushup(id);
}
void update(ll id,ll l,ll r,ll x,ll y,ll z)
{
	if(x<=l&&r<=y)
	{
		s[id]+=len[id]*z;
		lzy[id]+=z;
		return;
	}
	pushdown(id);
	ll m=(l+r)>>1;
	if(x<=m)
	update(lson,x,y,z);
	if(y>m)
	update(rson,x,y,z);
	pushup(id);
}
ll query(ll id,ll l,ll r,ll x,ll y)
{
	if(x<=l&&r<=y)
	return s[id];
	pushdown(id);
	ll m=(l+r)>>1;
	ll ans=0;
	if(x<=m)
	ans+=query(lson,x,y);
	if(y>m)
	ans+=query(rson,x,y);
	return ans;
}
int main()
{
	scanf("%lld%lld",&n,&q);
	for(ll i=1;i<=n;i++)
	scanf("%lld",&f[i]);
	for(ll i=1;i<n;i++)
	{
		ll u,v;
		scanf("%lld%lld",&u,&v);
		add(u,v);
		add(v,u);
	}
	dfs(1,0);
	build(1,1,n);
	while(q--)
	{
		ll op,v,u,x;
		scanf("%lld",&op);
		if(op==1)
		scanf("%lld",&root);
		if(op==2)
		{
			scanf("%lld%lld%lld",&u,&v,&x);
			ll k=lcaa(u,v,root);
			if(k==root)
			update(1,1,n,1,n,x);
			else
			{
				if(L[root]<L[k]||L[root]>R[k])
				update(1,1,n,L[k],R[k],x);
				else
				{
					ll t=jumping(root,dep[root]-dep[k]-1);
					update(1,1,n,1,n,x);
					update(1,1,n,L[t],R[t],-x);
				}	
			}
		}
		if(op==3)
		{
			ll ans=0;
			scanf("%lld",&v);
			if(v==root)
			ans=query(1,1,n,1,n);
			else
			{
				if(L[root]<L[v]||L[root]>R[v])
				ans=query(1,1,n,L[v],R[v]);
				else
				{
					ll t=jumping(root,dep[root]-dep[v]-1);
					ans+=query(1,1,n,1,n);
					ans-=query(1,1,n,L[t],R[t]);
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：zhengrunzhe (赞：3)

#### update:satt找lca的non-local search做法本人已实现，讲解在下面
题意:

1.换根

2.找lca并将其子树加

3.子树求和

显然你可以去dfs序线段树什么的随便搞，但是太低级了

换根使人想到了lct，然后看到子树加使人放弃

这时候就需要用到一个动态树数据结构:toptree

并不是魔改lca(aaa树)，是真正的toptree

采用tarjan的self-adjusting实现

可以去[negiizhao博客](http://negiizhao.blog.uoj.ac/blog/4912)里学

动态找lca需要用non-local search

由于本人比较菜还不会实现non-local search

于是我就另外写了一个lct实现动态kca

具体如何实现有[题](https://www.luogu.com.cn/problem/SP8791)去看就好了

做过sone1的都知道，satt去维护

簇路径和除簇路径以外部分的点权和

由于只有点权，所以可以省去base cluster

一个树的子树在satt上的表现就是access之后的中儿子(无需维护边顺序，compress node的四个儿子压成三个 两个rake儿子合成中儿子表示rake tree)

satt这个科技我并不想将代码公开，其实总共写了315行代码~~(跟我写的sone1一样长，如果会non-local search可以直接省掉lct的将近100行)~~

```cpp
#include<cstdio>
#include<cstddef>
template<class type>inline const void swap(type &a,type &b)
{
	const type c(a);a=b;b=c;
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());bool f(0);
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
typedef long long ll;
const int N(1e5+10);
namespace Self_Adjusting_Top_Trees
{
}
#define satt Self_Adjusting_Top_Trees
namespace Link_Cut_Trees
{
	struct tree
	{
		bool rev;
		tree *son[2],*fa;
		static tree *null;
		void *operator new(size_t size);
		void *operator new[](size_t size);
		inline tree():rev(0)
		{
			static bool init(0);
			if (!init)
				init=1,
				null=new tree,
				null->son[0]=null->son[1]=null->fa=null;
			son[0]=son[1]=fa=null;
		}
		inline const void reverse()
		{
			if (this!=null)swap(son[0],son[1]),rev^=1;
		}
		inline const void pushdown()
		{
			if (rev)
				son[0]->reverse(),
				son[1]->reverse(),
				rev=0;
		}
		inline const bool identity()
		{
			return fa->son[1]==this;
		}
		inline const bool isroot()
		{
			return fa->son[0]!=this&&fa->son[1]!=this;
		}
		inline const void rotate()
		{
			const bool f(identity());
			tree *fa(this->fa),*gfa(fa->fa),*q(son[f^1]);
			if (!fa->isroot())gfa->son[fa->identity()]=this;
			(son[f^1]=fa)->son[f]=q;
			((q->fa=fa)->fa=this)->fa=gfa;
		}
		inline const void relieve()
		{
			if (!isroot())fa->relieve();
			pushdown();
		}
		inline const void splay()
		{
			for (relieve();!isroot();rotate())
				if (!fa->isroot())
					(fa->identity()^identity()?this:fa)->rotate();
		}
	}*tree::null,*node0;
	#define null tree::null
	char memory_pool[N*sizeof(tree)],*tail(memory_pool+sizeof(memory_pool));
	inline void *tree::operator new(size_t size){return tail-=size;}
	inline void *tree::operator new[](size_t size){return tail-=size;}
	inline tree *node(const int &x){return node0+x;}
	inline tree *access(tree *x)
	{
		tree *y(null);
		for (;x!=null;x=(y=x)->fa)x->splay(),x->son[1]=y;
		return y;
	}
	inline const void evert(tree *x)
	{
		access(x);x->splay();x->reverse();
	}
	inline const void link(tree *x,tree *y)
	{
		evert(x);x->fa=y;
	}
	inline tree *lca(tree *x,tree *y)
	{
		access(x);return access(y);
	}
	#undef null
}
#define lct Link_Cut_Trees
int n,m;
int main()
{
	read(n);read(m);
	satt::node0=new satt::tree[n+1];
	lct::node0=new lct::tree[n+1];
	for (int i(1);i<=n;i++)read(satt::node(i)->val);
	for (int u,v,i(1);i<n;i++)
		read(u),read(v),
		satt::link(satt::node(u),satt::node(v)),
		lct::link(lct::node(u),lct::node(v));
	satt::evert(satt::node(1));lct::evert(lct::node(1));
	for (int opt,u,v,w;m--;)
		switch (read(opt),read(u),opt)
		{
			case 1:satt::evert(satt::node(u));lct::evert(lct::node(u));break;
			case 2:
			{
				read(v);read(w);
				const int lca(lct::lca(lct::node(u),lct::node(v))-lct::node0);
				satt::add(satt::node(lca),w);
				break;
			}
			case 3:printf("%lld\n",satt::query(satt::node(u)));break;
		}
	return 0;
}
```

non-local searching for lca:

记$rt$为根 $lca$为$Lca(u,v)$，$dis(x,y)$表示$x,y$路径上点数，则有
$$dis(u,v)=dis(rt,u)+dis(rt,v)-2dis(rt,lca)+1$$
移项得
$$dis(rt,lca)=\frac {dis(rt,u)+dis(rt,v)-dis(u,v)+1}{2}$$

显然分子可以直接求出

这样我们就知道了$lca$到根的距离记作$k$，那我们只需要从根往下到$u$或$v$跳$k$个点即可

这个东西我们可以通过提取根到$u$或$v$的路径，因为root path形态是个Splay，然后在上面找kth即可

non-local search的本质是二分，类似线段树上二分

而toptree的簇结构构成就类似线段树，所以原理不难理解

平衡树kth的本质也是通过左儿子大小这一信息实现对二分的check

代码仍然不提供satt
```cpp
#include<cstdio>
#include<cstddef>
template<class type>inline const void swap(type &a,type &b)
{
	const type c(a);a=b;b=c;
}
template<class type>inline const type max(const type &a,const type &b)
{
	return a>b?a:b;
}
template<class type>inline const void read(type &in)
{
	in=0;char ch(getchar());bool f(0);
	while (ch<48||ch>57){if (ch=='-')f=1;ch=getchar();}
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (f)in=-in;
}
typedef long long ll;
const int N(1e5+10);
namespace Self_Adjusting_Top_Trees
{
}using namespace Self_Adjusting_Top_Trees;
int n,m;
int main()
{
	read(n);read(m);
	node0=new tree[n+1];
	for (int i(1);i<=n;i++)read(node(i)->val);
	for (int u,v,i(1);i<n;i++)
		read(u),read(v),link(node(u),node(v)),
	evert(root=node(1));
	for (int opt,u,v,w;m--;)
		switch (read(opt),read(u),opt)
		{
			case 1:evert(root=node(u));break;
			case 2:read(v);read(w);add(lca(node(u),node(v)),w);break;
			case 3:printf("%lld\n",query(node(u)));break;
		}
	return 0;
}
```

---

## 作者：Goldia (赞：2)

其实top tree对于这些简单的操作挺好写的 ~~但还是太毒瘤了~~

- 操作1显然直接makeroot就行了
- 操作2需要找lca，top tree找lca和lct找lca是一样的，都是先Access(x),然后Access(y)找到最后停下的节点即为lca，然后Access(lca)打个tag就行了
- 操作3就直接Access(x)后统计一下虚链的贡献就好了

~~板子就很毒瘤~~
### code

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse4,mmx")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define int long long
#define R register
const int N=2e5+5;
int n,m;
struct ccf
{
    int ma,mi,sum,siz;
    ccf(){}
    ccf(int a,int b,int c,int d):ma(a),mi(b),sum(c),siz(d){}
};
struct tag
{
    int mul,add;
    tag(){mul=1;add=0;};
    tag(int a,int b):mul(a),add(b){}
    inline bool empty(){return mul==1&&add==0;} 
};
ccf operator+(const ccf&a,const ccf&b)
{
    return ccf(max(a.ma,b.ma),min(a.mi,b.mi),a.sum+b.sum,a.siz+b.siz);
}
ccf operator+(const ccf&a,const tag&b)
{
    if(!a.siz)return a;
    return ccf(a.ma*b.mul+b.add,a.mi*b.mul+b.add,a.sum*b.mul+b.add*a.siz,a.siz);
}
tag operator+(const tag&a,const tag&b)
{
    return tag(a.mul*b.mul,a.add*b.mul+b.add);
}
struct lct
{
    lct *ch[4],*par;
    tag CHAIN,ALL;
    ccf cha,sub,all;
    int rev,inr,val;
    inline void filp(){rev^=1;swap(ch[0],ch[1]);}
    inline void pushshi(const tag&a)
    {
        cha=cha+a;
        CHAIN=CHAIN+a;
        val=val*a.mul+a.add;
        all=cha+sub;
    }
    inline void pushxu(const tag&a,bool fff=1)
    {
        ALL=ALL+a;
        all=all+a;
        sub=sub+a;
        if(fff)pushshi(a);
    }
    inline void rz()
    {
        cha=all=sub=ccf(-(1<<30),1<<30,0,0);
        if(!inr)all=cha=ccf(val,val,val,1);
        for(int i=0;i<2;i++)if(ch[i])cha=cha+ch[i]->cha,sub=sub+ch[i]->sub;
        for(int i=2;i<4;i++)if(ch[i])sub=sub+ch[i]->all;
        for(int i=0;i<4;i++)if(ch[i])all=all+ch[i]->all;
    }
    inline void pushdown()
    {
        if(rev)
        {
            if(ch[0])ch[0]->filp();
            if(ch[1])ch[1]->filp();
            rev=0;
        }
        if(!ALL.empty())
        {
            for(int i=0;i<4;i++)
                if(ch[i])ch[i]->pushxu(ALL,i>=2);
            ALL=tag(1,0);
        }
        if(!CHAIN.empty())
        {
            for(int i=0;i<2;i++)
                if(ch[i])ch[i]->pushshi(CHAIN);
            CHAIN=tag(1,0);
        }
    }
    inline lct *CH(int now){if(ch[now])ch[now]->pushdown();return ch[now];}
    inline bool CHK(int now){return par->ch[now+1]==this;}
    inline int chk(){for(int i=0;i<4;i++)if(par->ch[i]==this)return i;return 0;}
    inline void sets(lct *now,int d){if(now)now->par=this;ch[d]=now;}
    inline bool get(int ty)
    {
        if(!ty)return !par||(par->ch[0]!=this&&par->ch[1]!=this);
        return !par||!par->inr||!inr;
    }
}tr[N<<1],*cur=tr+N,*pool[N],**CUR=pool;
int totcnt=0;
inline lct *newlct()
{
    ++totcnt;
    lct *now=(CUR==pool)?cur++:*(--CUR);
    for(int i=0;i<4;i++)now->ch[i]=0;
    now->par=0;
    now->ALL=now->CHAIN=tag(1,0);
    now->all=now->cha=ccf(-(1<<30),1<<30,0,0);
    now->inr=1;now->rev=0;now->val=0;
    return now;
}
inline void deld(lct *now){*(CUR++)=now;}
inline void zhuan(lct *now,int ty)
{
    lct *p=now->par;int d=now->CHK(ty);
    if(!p->par)now->par=0;
    else p->par->sets(now,p->chk());
    p->sets(now->ch[!d+ty],d+ty);
    now->sets(p,!d+ty);
    p->rz();
}
inline void splay(lct *now,int ty=0)
{
    while(!now->get(ty))
    {
        if(now->par->get(ty))zhuan(now,ty);
        else if(now->CHK(ty)==now->par->CHK(ty))zhuan(now->par,ty),zhuan(now,ty);
        else zhuan(now,ty),zhuan(now,ty);   
    }
    now->rz();
}
inline void add(lct *a,lct *b)
{
    b->pushdown();
    for(int i=2;i<4;i++)
        if(!b->ch[i]){b->sets(a,i);return;}
    lct *x=newlct(),*v;
    for(v=b;v->ch[2]->inr;v=v->CH(2));
    x->sets(v->ch[2],2);x->sets(a,3);
    v->sets(x,2);splay(x,2);
}
inline void del(lct *now)
{
    if(now->par->inr)
    {
        now->par->par->sets(now->par->ch[5-now->chk()],now->par->chk());
        deld(now->par);
        splay(now->par->par,2);
    }
    else now->par->sets(0,now->chk());
    now->par=0;
}
lct *sta[N];
inline lct* Access(lct *now)
{
    int top=0;
    lct *v=now,*u;
    for(u=now;u;u=u->par)sta[++top]=u;
    while(top)sta[top--]->pushdown();
    splay(now);
    if(now->ch[1])
    {
        u=now->ch[1];
        now->ch[1]=0;
        add(u,now);
        now->rz();
    }
    while(now->par)
    {
        //cout<<"f="<<now->par->val<<endl;
        for(u=now->par;u->inr;u=u->par);
        splay(u);
        if(u->ch[1])
        {
            now->par->sets(u->ch[1],now->chk());
            splay(now->par,2);
        }
        else del(now);
        u->sets(now,1);
        (now=u)->rz();
    }
    splay(v);
    return now;
}
inline void makeroot(lct *now)
{
    Access(now);
    now->filp();
}
inline lct *findpar(lct *now)
{
    Access(now);
    now=now->CH(0);
    while(now&&now->ch[1])now=now->CH(1);
    return now;
}
inline lct *findrt(lct *now)
{
    for(;now->par;now=now->par);
    return now;
}
inline lct *cut(lct *now)
{
    lct *v=findpar(now);
    if(v)
    {
        Access(v);
        del(now);
        v->rz();
    }
    return v;
}
inline void link(lct *a,lct *b)
{
    lct *now=cut(a);
    if(findrt(a)!=findrt(b))now=b;
    if(now)
    {
        //cout<<now->val<<endl;
        Access(now);
        //cout<<666<<endl;
        add(a,now);
        now->rz();
    }
}
inline void split(lct *a,lct *b)
{
    makeroot(a);
    Access(b);
    splay(a);
}
int U[N],V[N],root;
inline int rd()
{
    char p=getchar();int x=0,f=1;
    while(p>'9'||p<'0')
    {
        if(p=='-')f=-1;
        p=getchar();
    }
    while(p<='9'&&p>='0')x=(x<<1)+(x<<3)+(p^48),p=getchar();
    return x*f;
}
signed main()
{
    n=rd();m=rd();
	for(int i=1;i<=n;i++)
    {
        tr[i].val=rd();
        tr[i].rz();
    }
	for(int i=1;i<n;i++)
    	U[i]=rd(),V[i]=rd();
    for(int i=1;i<n;i++)
    {
        makeroot(tr+U[i]);
        //cout<<U[i]<<" "<<V[i]<<endl; 
        link(tr+U[i],tr+V[i]);
    }
    root=1;
    makeroot(tr+root);
    int x,op,z;
    lct *u,*lca,*v;
    while(m--)
	{
		op=rd();x=rd();
		makeroot(tr+root);
		if(op==1)root=x;
		else if(op==2)
		{
			u=tr+x;v=tr+rd();
			Access(u);
			lca=Access(v);
			Access(lca);
			z=rd();
			tag fg(1,z);
			lca->val=lca->val*fg.mul+fg.add;
			for(int i=2;i<4;i++)
				if(lca->ch[i])lca->ch[i]->pushxu(fg);
            lca->rz();
		}
		else
		{
			u=tr+x;
			Access(u);
            int ans=u->val;
            for(int i=2;i<4;i++)if(u->ch[i])
            {
                ccf res=u->ch[i]->all;                    
                ans+=res.sum;
            }
            printf("%I64d\n",ans);//cf上要用I64d
		}
	}
    return 0;
}
```


---

## 作者：_lxy_ (赞：1)

### 题意

有一棵 $n$ 个节点的有根树，标号为 $1-n$，你需要维护以下三种操作

1. 给一个点 $v$ ，将整颗树的根变为 $v$。
  
2. 给两个点 $u,v$，将 $lca(u,v)$ 所在的子树都加上 $x$。
  
3. 给一个点 $v$，问以 $v$ 所在的子树的权值和。
  

### 分析

换根树剖板子题。设当前根为 $rt$ ，有几种简单操作：

#### 换根后 LCA

直接分讨即可。

```cpp
int LCA(int x,int y)
{
    if(dep[x]>dep[y]) swap(x,y);
    int xr=lca(x,rt),yr=lca(y,rt),xy=lca(x,y);
    if(xy==x) 
    {
        if(xr==x){if(yr==y) return y;return yr;}
        return x;
    }
    if(xr==x) return x;if(yr==y) return y;
    if((xr==rt&&xy==yr)||(yr==rt&&xy==xr)) return rt;
    if(xr==yr) return xy;
    if(xy!=xr) return xr;return yr;
}
```

#### 换根后子树修改

分几种情况讨论：

1. $u$ 是 $rt$
  
  此时直接把所有点权都加上 $x$ 。
  
2. $u$ 不是 $rt$ 的祖先
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/0mlianm4.png)
  
  此时情况如图所示，不难发现，无论 $u$ 在哪，$u$ 的子树都不变。
  
3. $u$ 是 $rt$ 的祖先
  
  ![](https://cdn.luogu.com.cn/upload/image_hosting/a4ojf8qr.png)
  
  此时情况如图所示，设 $v$ 为是 $rt$ 祖先的 $u$ 的子节点，要想得到 $v$ ，我们可以每次把 $rt$ 向上跳重链，直到跳到 $u$ 的子节点。可以发现，加的部分相当于整棵树刨掉 $v$ 的子树，由于树剖之后子树内节点编号连续，所以可以用线段树区间修改，每次修改 $[1,id_v) \bigcup (id_v,n]$。
  

此部分代码如下：

```cpp
int get(int x,int y)
{
    int fx=top[x],fy=top[y];
    while(top[x]!=top[y])
    {
        if(dep[fx]<dep[fy]) swap(fx,fy),swap(x,y); //跳重链顶深度更深的
        if(fa[fx]==y) return fx; //已经找到了
        x=fa[fx],fx=top[x];
    }
    if(dep[x]>dep[y]) swap(x,y);
    return hson[x];
}
void update_subtree(int u,int k)
{
    if(u==rt) update(1,1,n,1,n,k); //对应情况1
    else if(lca(u,rt)!=u) update(1,1,n,id[u],id[u]+cnt[u]-1,k); //情况2
    else //情况3
    {
        int v=get(u,rt);
        if(id[v]-1>=1) update(1,1,n,1,id[v]-1,k);
        if(id[v]+cnt[v]<=n) update(1,1,n,id[v]+cnt[v],n,k);
    }
}
```

#### 换根后子树求和

原理和子树修改相同。

```cpp
int query_subtree(int u)
{
    int res=0;
    if(u==rt) res=query(1,1,n,1,n);
    else if(lca(u,rt)!=u) res=query(1,1,n,id[u],id[u]+cnt[u]-1);
    else
    {
        int v=get(u,rt);
        if(id[v]-1>=1) res+=query(1,1,n,1,id[v]-1);
        if(id[v]+cnt[v]<=n) res+=query(1,1,n,id[v]+cnt[v],n);
    }
    return res;
}
```

### 完整代码

[Submission #153363241 - Codeforces](https://codeforces.com/problemset/submission/916/153363241)

---

## 作者：Y_B_X (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF916E)  
对这种方法更加详细的介绍与时间复杂度分析: [cnblog](https://www.cnblogs.com/Y-B-X/p/14939291.html) [洛谷blog](https://www.luogu.com.cn/blog/Y-B-X/zhi-chi-zi-shu-cao-zuo-di-dong-tai-shu-mo-gai-lct)  
这里介绍一种能够保证时间复杂度的魔改 $LCT$ 的做法，并非 $AAAT$  
回想 $LCT$ 的局限性就是不能维护子树标记  
那就可以想到用一个数据结构专门维护每个点的虚儿子  
平衡树时空复杂度都表现优秀，那就可以想到直接用一个 $splay$ 来维护虚儿子  
但事实上如果单纯地让每个节点对应一个虚拟节点在对应的维护虚儿子的 $splay$ 中，  
像 $AAAT$ 一样地写，并不能很好地保证单次 $access$ 时间复杂度均摊为 $O(log n)$  
这主要是因为它删除节点时需将前驱（后继）找出来再删  
借鉴一下 $Tarjan$ 的 $Top$ $Tree$ 论文，不难发现另一种方法  
就是把虚儿子 $splay$ 中的真正代表原先 $LCT$ 中信息的点只让它们在叶子结点上  
然后用一些辅助节点串起来，构成一个类似 $leafytree$ 的结构    
若在删一个节点时，由于其没有左右儿子，直接连带他的父节点从整个 $splay$ 中移除，  
再将其原先父节点的父节点旋到根，更新一下即可。  
同时若是换节点的信息，同样直接改然后旋到根更新信息，十分方便。  
而这样是可以保证单次 $access$ 是均摊时间为一个 $log$ 的，具体证明参见上面的链接。  
而这一题中：换根、求 $LCA$ 、子树加、子树查询正是这种魔改 $LCT$ 适用的。  
在虚儿子的 $splay$ 中下传的标记时要对原先 $LCT$ 的节点信息做修改，  
原先 $LCT$ 的子树标记同样要对其虚儿子的 $splay$ 打上标记，  
为了避免一次这样连续打标记不停，可以在每个点的虚 $splay$ 中加一个不动的根节点。   
但不过虽然时间复杂度能保证，常数还是比 $Top$ $Tree$ 要稍微大些。  
代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+10;
int n,m,x,y,opt,root=1;ll v,ans;
int son[N][2],anc[N],sz[N],rt[N],rev[N];ll sum[N],w[N],tag[N];
void tag_(int x,ll v);
struct leafy_Splay{
	int son[N<<2][2],anc[N<<2],sz[N<<2],wsz[N<<2],tot;ll sum[N<<2],wsum[N<<2],tag[N<<2];
	queue<int> q;
	void tag_1(int x,ll v){
		sum[x]+=sz[x]*v;
		wsum[x]+=wsz[x]*v;
		tag[x]+=v;
		if(x<=n)tag_(x,v);
	}
	void fix(int x){if(!x)return;sum[x]=sum[son[x][0]]+sum[son[x][1]]+wsum[x];
		sz[x]=sz[son[x][0]]+sz[son[x][1]]+wsz[x];}
	bool p(int x){return son[anc[x]][1]==x;}
	int newnode(){if(!q.empty()){int x=q.front();return q.pop(),x;}return ++tot;}
	void pushdown(int x){
		if(tag[x]){
			if(son[x][0])tag_1(son[x][0],tag[x]);
			if(son[x][1])tag_1(son[x][1],tag[x]);
			tag[x]=0;
		}
	}
	void pushall(int x){
		if(anc[x])pushall(anc[x]);
		pushdown(x);
	}
	void rotate(int x){int y=anc[x],xx=anc[y];bool b=p(x),bb=p(y);
		anc[x]=xx;if(xx)son[xx][bb]=x;son[y][b]=son[x][b^1];
		anc[son[x][b^1]]=y;son[x][b^1]=y;anc[y]=x;fix(y);fix(x);fix(xx);
	}
	void splay(int x,int y){pushall(x);
		for(int i=anc[x];i=anc[x],i!=y;rotate(x))
			if(anc[i]!=y){if(p(x)==p(i))rotate(i);else rotate(x);}
	}
	void ins(int x,int y,ll sum_,int sz_){
		wsum[x]=sum_;wsz[x]=sz_;fix(x);int tmp=rt[y],f=0;pushdown(tmp);
		if(!son[rt[y]][0])return anc[son[rt[y]][0]=x]=rt[y],fix(rt[y]);
		while(1){
			if(!tmp){
				tmp=newnode();anc[son[anc[f]][p(f)]=tmp]=anc[f];
				son[tmp][x>f]=x;anc[x]=tmp;
				son[tmp][x<f]=f;anc[f]=tmp;
				fix(f);fix(tmp);fix(anc[tmp]);
				return splay(tmp,rt[y]);
			}
			pushdown(tmp);
			f=tmp;tmp=son[tmp][x>tmp];
		}
	}
	void clear(int x){wsz[x]=sz[x]=wsum[x]=sum[x]=son[x][0]=son[x][1]=anc[x]=0;if(x>(n<<1))q.push(x);}
	void del(int x,int y){
		if(anc[x]==rt[y])return son[rt[y]][0]=0,fix(rt[y]),clear(x);
		int yy=anc[x],xx=anc[yy];bool b=p(x),bb=p(yy);
		if(xx==rt[y]){
			anc[son[rt[y]][0]=son[yy][b^1]]=rt[y];
			clear(x),clear(yy),fix(rt[y]);
			return;
		}
		anc[son[xx][p(yy)]=son[yy][b^1]]=xx;
		clear(x);clear(yy);fix(xx);splay(xx,rt[y]);fix(rt[y]);
	}
	void display(int x,int xx,ll sum_,int sz_,int y){
		wsum[xx]=sum_;wsz[xx]=sz_;fix(xx);int yy=anc[x];
		anc[son[yy][p(x)]=xx]=yy;clear(x);fix(yy);if(yy!=rt[y])splay(yy,rt[y]);fix(rt[y]);
	}
}S;
void rev_(int x){rev[x]^=1;son[x][0]^=son[x][1]^=son[x][0]^=son[x][1];}
void tag_(int x,ll v){sum[x]+=v*sz[x];w[x]+=v;tag[x]+=v;S.tag_1(rt[x],v);}
bool p(int x){return son[anc[x]][1]==x;}
bool isroot(int x){return son[anc[x]][0]!=x&&son[anc[x]][1]!=x;}
void fix(int x){
	if(!x)return;
	sum[x]=sum[son[x][0]]+sum[son[x][1]]+w[x]+S.sum[rt[x]];
	sz[x]=sz[son[x][0]]+sz[son[x][1]]+1+S.sz[rt[x]];
}
void pushdown(int x){
	if(rev[x]){if(son[x][0])rev_(son[x][0]);
	if(son[x][1])rev_(son[x][1]);rev[x]=0;}
	if(tag[x]){if(son[x][0])tag_(son[x][0],tag[x]);
	if(son[x][1])tag_(son[x][1],tag[x]);tag[x]=0;}
}
void pushall(int x){
	if(!isroot(x))pushall(anc[x]);
	pushdown(x);
}
void pushall_(int x){
	if(!isroot(x))pushall_(anc[x]);
	else if(anc[x]){
		pushall_(anc[x]);
		S.pushall(x);
	}
	pushdown(x);
}
void rotate(int x){int y=anc[x],xx=anc[y];bool b=p(x),bb=p(y);
	anc[x]=xx;if(!isroot(y))son[xx][bb]=x;son[y][b]=son[x][b^1];
	anc[son[x][b^1]]=y;son[x][b^1]=y;anc[y]=x;fix(y);fix(x);fix(xx);
}
int findrt(int x){if(isroot(x))return x;return findrt(anc[x]);}
void splay(int x){pushall(x);int y=findrt(x);
	if(anc[y]&&x!=y)S.display(y,x,sum[y],sz[y],anc[y]);
	for(int i=anc[x];i=anc[x],!isroot(x);rotate(x)){
		if(!isroot(i)){if(p(i)==p(x))rotate(i);else rotate(x);}
	}
}
int access(int x){
	int y=0;pushall_(x);
	for(;x;y=x,x=anc[x]){
		splay(x);
		if(y&&son[x][1])S.display(y,son[x][1],sum[son[x][1]],sz[son[x][1]],x);
		else if(!y&&son[x][1])S.ins(son[x][1],x,sum[son[x][1]],sz[son[x][1]]);
		else if(y&&!son[x][1])S.del(y,x);
		son[x][1]=y;fix(x);
	}
	return y;
}
void makeroot(int x){access(x);splay(x),rev_(x);}
void split(int x,int y){makeroot(x),access(y),splay(y);}
void link(int x,int y){split(x,y);anc[x]=y;S.ins(x,y,sum[x],sz[x]);fix(y);}
void subtree_add(int x,ll v){
	split(root,x);
	sum[x]+=v*(S.sz[rt[x]]+1);w[x]+=v;
	S.tag_1(rt[x],v);
}
int lca(int x,int y){
	makeroot(root);access(x);return access(y);
}
main(){
	scanf("%d%d",&n,&m);S.tot=n<<1;
	for(int i=1;i<=n;i++)scanf("%lld",&w[i]),fix(i),rt[i]=i+n,S.fix(i);
	for(int i=1;i<n;i++)scanf("%d%d",&x,&y),link(x,y);
	while(m--){
		scanf("%d%d",&opt,&x);
		if(opt==1)root=x;
		if(opt==2)scanf("%d%lld",&y,&v),subtree_add(lca(x,y),v);
		if(opt==3){
			split(root,x);
			ans=sum[son[x][1]]+S.sum[rt[x]]+w[x];
			printf("%lld\n",ans);
		}
	}
}
```

---

## 作者：Erusel (赞：1)

考虑到这题要换根，

有一种很简单的想法就是直接拿高级动态树等数据结构过去。

我们考虑一种更简单的做法

---

我们先随便以 $1$ 为根，倍增预处理出每个节点的 $2^k$ 级父亲

然后每次是要询问子树内的信息，我们把它映射到 $\text{DFS}$ 序上。

考虑到操作 $2$ 需要询问 $\text{LCA}$，我们有两种方法

第一种是在询问的时候处理，第二种是在修改的时候处理

这里讲的是修改时候处理的方法。

我们分类讨论 $u,v$ 的情况，

我们考虑先求出 $u,v$ 在新的树中的 $\text{LCA}$

这个 $\text{LCA} = lca(u,v),lca(u,root),lca(v,root)$ 中深度最大的点。

我们发现 $\text{DFS}$ 序发生了变化，有点难处理

事实上，我们可以换个角度思考，我们只需要知道在原树上我们需要修改的东西。

如果求出的 $\text{LCA}$ 在原树中是 $root$ 的祖先，那么我们要修改的区间相当于 $[1,n] +x$ ，以及将多余部分 $-x$

多余部分在字典序上是连续的，读者可以思考一下

如果不是，那就直接修改 $\texttt{LCA}$ 的子树

时间复杂度 $O(nlogn)$ 就拿线段树维护一下 $\text{DFS}$ 即可

---

## 作者：Styx (赞：1)

**我热爱树链剖分，所以这道题还是用树链剖分写了，尽管有点杀鸡用牛刀**

**这道题大概有以下几个难点**

****
**首先是换根情况下的子树权值和查询，但如果你做过洛谷P3979遥远的国度这道题，而且你还是用树链剖分写的，你大致就会做这个东西了。**

**维护一个LCA，然后从根节点跳到当前这个子树根节点的儿子所处的深度，记这个点为A，如果A点的父亲是我们询问的子树根节点，那么根节点在子树中，此时当前的新子树就是除了A点和A点的原子树以外的所有点，否则的话就是子树根节点的原子树，当然也要特判一下，如果根节点刚好是要查询的子树根节点，那么查询范围就是全部节点**

**修改也是同理的**
****
**然后是包括u和v的最小子树，画一下图就可以知道子树的根节点应该是u到根节点的路径与v到根节点的路径的第一个交点**

![](https://cdn.luogu.com.cn/upload/pic/17233.png)

**这个交点可以通过对根和u，根和v，v和u两两取LCA后取深度最大的点获得，挺简单的想法，可以自行模拟体会一下**

**假设我们已经获得了这个根节点，那么之后的操作就是换根情况下子树的权值修改了，这在上面已经提到过了，就不再赘述了。**
****

**代码如下：**

```cpp
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lson root<<1
#define rson root<<1|1
using namespace std;

struct node
{
	long long l,r,sum,lazy;
} tr[400040];
long long fa[100010][20],son[100010],size[100010],deep[100010],id[100010],c[100010],w[1000010],top[100010],cnt,rt,n,q;
vector<long long> g[100010];

void push_up(long long root)
{
	tr[root].sum=tr[lson].sum+tr[rson].sum;
}

void push_down(long long root)
{
	long long mid=(tr[root].l+tr[root].r)>>1;
	tr[lson].sum+=tr[root].lazy*(mid-tr[root].l+1);
	tr[lson].lazy+=tr[root].lazy;
	tr[rson].sum+=tr[root].lazy*(tr[root].r-mid);
	tr[rson].lazy+=tr[root].lazy;
	tr[root].lazy=0;
}

void build(long long root,long long l,long long r)
{
	if(l==r)
	{
		tr[root].l=l;
		tr[root].r=r;
		tr[root].sum=w[l];
		return ;
	}
	tr[root].l=l;
	tr[root].r=r;
	long long mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	push_up(root);
}

void update(long long root,long long l,long long r,long long val)
{
	if(l>r)
	{
		return;
	}
	if(l==tr[root].l&&r==tr[root].r)
	{
		tr[root].sum+=val*(tr[root].r-tr[root].l+1);
		tr[root].lazy+=val;
		return ;
	}
	if(tr[root].lazy)
	{
		push_down(root);
	}
	long long mid=(tr[root].l+tr[root].r)>>1;
	if(l>mid)
	{
		update(rson,l,r,val);
	}
	else
	{
		if(r<=mid)
		{
			update(lson,l,r,val);
		}
		else
		{
			update(lson,l,mid,val);
			update(rson,mid+1,r,val);
		}
	}
	push_up(root);
}

long long query(long long root,long long l,long long r)
{
	if(l>r)
	{
		return 0;
	}
	if(l==tr[root].l&&r==tr[root].r)
	{
		return tr[root].sum;
	}
	long long mid=(tr[root].l+tr[root].r)>>1;
	if(tr[root].lazy)
	{
		push_down(root);
	}
	if(l>mid)
	{
		return query(rson,l,r);
	}
	else
	{
		if(r<=mid)
		{
			return query(lson,l,r);
		}
		else
		{
			return query(lson,l,mid)+query(rson,mid+1,r);
		}
	}
}

void dfs1(long long now,long long f,long long dep)
{
	deep[now]=dep;
	fa[now][0]=f;
	size[now]=1;
	long long maxson=-1;
	for(long long i=0; i<g[now].size(); i++)
	{
		if(g[now][i]==f)
		{
			continue;
		}
		dfs1(g[now][i],now,dep+1);
		size[now]+=size[g[now][i]];
		if(size[g[now][i]]>maxson)
		{
			maxson=size[g[now][i]];
			son[now]=g[now][i];
		}
	}
}

void dfs2(long long now,long long topf)
{
	id[now]=++cnt;
	w[cnt]=c[now];
	top[now]=topf;
	if(!son[now])
	{
		return ;
	}
	dfs2(son[now],topf);
	for(long long i=0; i<g[now].size(); i++)
	{
		if(g[now][i]==fa[now][0]||g[now][i]==son[now])
		{
			continue;
		}
		dfs2(g[now][i],g[now][i]);
	}
}

long long lca(long long u,long long v)
{
	if(deep[u]<deep[v])
	{
		swap(u,v);
	}
	for(long long i=17; i>=0; i--)
	{
		if(deep[fa[u][i]]>=deep[v])
		{
			u=fa[u][i];
		}
	}
	if(u==v)
	{
		return u;
	}
	for(long long i=17; i>=0; i--)
	{
		if(fa[u][i]!=fa[v][i])
		{
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}

long long get_point(long long u,long long v)
{
	long long tmp=rt;
	long long lca1=lca(tmp,u);
	long long lca2=lca(tmp,v);
	long long lca3=lca(u,v);
	if(deep[lca1]>=deep[lca2]&&deep[lca1]>=deep[lca3])
	{
		return lca1;
	}
	if(deep[lca2]>=deep[lca1]&&deep[lca2]>=deep[lca3])
	{
		return lca2;
	}
	if(deep[lca3]>=deep[lca1]&&deep[lca3]>=deep[lca2])
	{
		return lca3;
	}
}

void sub_update(long long u,long long v,long long val)
{
	long long p=get_point(u,v);
	if(p==rt)
	{
		update(1,1,n,val);
		return ;
	}
	long long tmp=rt;
	for(long long i=17; i>=0; i--)
	{
		if(deep[fa[tmp][i]]>deep[p])
		{
			tmp=fa[tmp][i];
		}
	}
	if(fa[tmp][0]!=p)
	{
		update(1,id[p],id[p]+size[p]-1,val);
	}
	else
	{
		update(1,1,id[tmp]-1,val);
		update(1,id[tmp]+size[tmp],n,val);
	}
}

long long sub_query(long long x)
{
	if(x==rt)
	{
		return query(1,1,n);
	}
	long long tmp=rt;
	for(long long i=17; i>=0; i--)
	{
		if(deep[fa[tmp][i]]>deep[x])
		{
			tmp=fa[tmp][i];
		}
	}
	if(fa[tmp][0]!=x)
	{
		return query(1,id[x],id[x]+size[x]-1);
	}
	else
	{
		return query(1,1,id[tmp]-1)+query(1,id[tmp]+size[tmp],n);
	}
}

int main()
{
	scanf("%lld%lld",&n,&q);
	for(long long i=1; i<=n; i++)
	{
		scanf("%lld",&c[i]);
	}
	for(long long i=1; i<=n-1; i++)
	{
		long long from,to;
		scanf("%lld%lld",&from,&to);
		g[from].push_back(to);
		g[to].push_back(from);
	}
	rt=1;
	dfs1(1,0,1);
	dfs2(1,1);
	build(1,1,n);
	for(long long j=1; j<=17; j++)
	{
		for(long long i=1; i<=n; i++)
		{
			fa[i][j]=fa[fa[i][j-1]][j-1];
		}
	}
	while(q--)
	{
		long long kd;
		scanf("%lld",&kd);
		if(kd==1)
		{
			scanf("%lld",&rt);
		}
		if(kd==2)
		{
			long long u,v,val;
			scanf("%lld%lld%lld",&u,&v,&val);
			sub_update(u,v,val);
		}
		if(kd==3)
		{
			long long v;
			scanf("%lld",&v);
			printf("%lld\n",sub_query(v));
		}
	}
}
```

---

## 作者：SuperTNT (赞：0)

#  [题解] CF916E Jamie and Tree

## 思路

我们发现除去换 $root$  操作就是个裸的树剖  +  线段树，我们可以先以 $1$ 为 $root$ 跑一次树剖，这样我们只要将换   $root$   操作带来的影响解决掉此题就完成了

* 我们发现换完后的  $root$ 与 $LCA/v$ 存在三种位置关系：1. 是  $LCA / v$ 本身 。2. 在  $LCA/ v$ 子树内 3.在 $LCA/v$ 子树外 

* 对于第一种情况，只要对整棵树进行操作即可；对于第二种情况，通过手模可以发现对 $LCA/v$ 的子树是没有影响的；对于第三种情况，我们需要找到换完后的  $root$  在 $LCA/v$ 的子树中属于那棵子树，先对全局进行操作，之后抛去多出来的   $ root$  的这部分影响即可

* 对于如何判断其是否在子树内我是通过判断 $dfn$ 来判断的，如果不在 $LCA /v$ 的子树内，那么 $root$ 的 $dfn$ 序应 $dfn [root]\lt dfn[LCA/v] $  或 $dfn[root] \gt dfn[LCA/v] + size[LCA/v] - 1$  （其中 $size[LCA/v]$ 为 $LCA/v$ 的子树大小 ）

* 如果在 $LCA/v$ 子树内可以仿照找 $LCA$ 一样跳

* 对于操作二我们还需要找到换根以后的 $LCA$ ，因为换完根后 $x,y$ 的$LCA$ 可能会改变，我们设 $lca1 = LCA(x,root),lca2=LCA(y,root),lca =LCA(x,y)$ ，如果 $lca1$  和  $lca2$  的 $LCA$ 相同 ，则在换根意义下 $LCA$ 即为 $lca$ ，否则为 $lca1$ 和 $lca2$ 中深度较深的那个

* 这样我们这道题就做完了

  ```c++
  //好题
  #include <bits/stdc++.h>
  
  #define re register
  #define ls p << 1
  #define rs p << 1 | 1
  
  typedef long long ll;
  
  namespace TNT
  {
      const int MAXN = 1e5 + 10;
  
      inline int read()
      {
          int x = 0, f = 1;
          char ch = getchar();
  
          while (ch < '0' || ch > '9')
          {
              if (ch == '-')
                  f = -1;
  
              ch = getchar();
          }
  
          while (ch >= '0' && ch <= '9')
          {
              x = (x << 3) + (x << 1) + (ch ^ 48);
              ch = getchar();
          }
  
          return x * f;
      }
  
      inline void write(ll x)
      {
          if (x < 0)
              putchar('-'), x = -x;
          if (x > 9)
              write(x / 10);
  
          putchar(x % 10 + '0');
      }
  
      int id[MAXN], rk[MAXN], w[MAXN];
  
      struct Tree
      {
          struct tree
          {
              int l;
              int r;
              int size;
              ll w;
              ll lazy;
          } t[MAXN << 2];
  
          inline void pushup(int p)
          {
              t[p].w = t[ls].w + t[rs].w;
          }
  
          inline void pushdown(int p)
          {
              if (t[p].lazy)
              {
                  t[ls].w += t[p].lazy * t[ls].size, t[rs].w += t[p].lazy * t[rs].size;
                  t[ls].lazy += t[p].lazy, t[rs].lazy += t[p].lazy;
  
                  t[p].lazy = 0;
              }
          }
  
          void build(int p, int l, int r)
          {
              t[p].l = l, t[p].r = r, t[p].size = r - l + 1;
  
              if (l == r)
              {
                  t[p].w = w[rk[l]];
                  return;
              }
  
              int mid = (l + r) >> 1;
  
              build(ls, l, mid);
              build(rs, mid + 1, r);
  
              pushup(p);
          }
  
          void update(int p, int l, int r, int val)
          {
              if (l <= t[p].l && r >= t[p].r)
              {
                  t[p].w += 1ll * val * t[p].size;
                  t[p].lazy += val;
                  return;
              }
  
              pushdown(p);
  
              int mid = (t[p].l + t[p].r) >> 1;
  
              if (l <= mid)
                  update(ls, l, r, val);
              if (r > mid)
                  update(rs, l, r, val);
  
              pushup(p);
          }
  
          ll query(int p, int l, int r)
          {
              if (l <= t[p].l && r >= t[p].r)
                  return t[p].w;
  
              pushdown(p);
  
              int mid = (t[p].l + t[p].r) >> 1;
              ll ans = 0;
  
              if (l <= mid)
                  ans += query(ls, l, r);
              if (r > mid)
                  ans += query(rs, l, r);
  
              return ans;
          }
  
      } T;
  
      struct edge
      {
          int nex;
          int v;
      } e[MAXN << 1];
  
      int head[MAXN], tot;
      inline void add(int x, int y) { e[++tot] = (edge){head[x], y}, head[x] = tot; }
  
      int dep[MAXN], size[MAXN], heavy[MAXN], f[MAXN];
      void dfs1(int lca, int fa)
      {
          f[lca] = fa;
          size[lca] = 1;
          dep[lca] = dep[fa] + 1;
  
          for (re int i = head[lca], v; i; i = e[i].nex)
          {
              v = e[i].v;
  
              if (v == fa)
                  continue;
  
              dfs1(v, lca);
              size[lca] += size[v];
  
              if (size[v] > size[heavy[lca]])
                  heavy[lca] = v;
          }
      }
  
      int top[MAXN], cnt;
      void dfs2(int lca, int tp)
      {
          top[lca] = tp;
          id[lca] = ++cnt;
          rk[cnt] = lca;
  
          if (!heavy[lca])
              return;
  
          dfs2(heavy[lca], tp);
  
          for (re int i = head[lca], v; i; i = e[i].nex)
          {
              v = e[i].v;
  
              if (v == f[lca] || v == heavy[lca])
                  continue;
  
              dfs2(v, v);
          }
      }
  
      inline int LCA(int x, int y)
      {
          while (top[x] != top[y])
          {
              if (dep[top[x]] < dep[top[y]])
                  std::swap(x, y);
  
              x = f[top[x]];
          }
  
          return dep[x] <= dep[y] ? x : y;
      }
  
      inline void main()
      {
          int n = read(), m = read();
  
          for (re int i = 1; i <= n; i++)
              w[i] = read();
  
          for (re int i = 1, x, y; i < n; i++)
          {
              x = read(), y = read();
              add(x, y), add(y, x);
          }
  
          dfs1(1, 0), dfs2(1, 1), T.build(1, 1, n);
  
          int root = 1;
          bool flag = 0;
          for (re int i = 1, opt, x, y, z, lca, lca1, lca2, now; i <= m; i++)
          {
              opt = read(), flag = 0;
  
              if (opt == 1)
                  root = read();
              else if (opt == 2)
              {
                  x = read(), y = read(), z = read(), lca = LCA(x, y), lca1 = LCA(x, root), lca2 = LCA(y, root);
  
                  if (dep[lca] < dep[lca1])
                      lca = lca1;
                  if (dep[lca] < dep[lca2])
                      lca = lca2;
  
                  if (root == lca)
                      T.update(1, 1, n, z);
                  else if ((id[root] < id[lca]) || (id[root] > id[lca] + size[lca] - 1))
                      T.update(1, id[lca], id[lca] + size[lca] - 1, z);
                  else
                  {
                      T.update(1, 1, n, z);
  
                      now = root;
  
                      while (top[now] != top[lca])
                      {
                          if (f[top[now]] == lca)
                          {
                              flag = 1;
                              now = top[now];
                              break;
                          }
  
                          now = f[top[now]];
                      }
  
                      if (!flag)
                          now = heavy[lca];
  
                      T.update(1, id[now], id[now] + size[now] - 1, -z);
                  }
              }
              else
              {
                  x = read();
                  if (root == x)
                      write(T.t[1].w), putchar('\n');
                  else if ((id[root] < id[x]) || (id[root] > id[x] + size[x] - 1))
                      write(T.query(1, id[x], id[x] + size[x] - 1)), putchar('\n');
                  else
                  {
                      now = root;
  
                      while (top[now] != top[x])
                      {
                          if (f[top[now]] == x)
                          {
                              flag = 1;
                              now = top[now];
                              break;
                          }
  
                          now = f[top[now]];
                      }
  
                      if (!flag)
                          now = heavy[x];
  
                      write(T.query(1, 1, n) - T.query(1, id[now], id[now] + size[now] - 1)), 					putchar('\n');
                  }
              }
          }
  
          return;
      }
  } // namespace TNT
  
  int main()
  {
      TNT::main();
      return 0;
  }
  ```

  双倍经验：遥远的国度







---

## 作者：随情英 (赞：0)

题目链接：[Codeforces 916E](https://www.luogu.com.cn/problem/CF916E)

### 题意:

给你一棵有根树，点带权，默认根为 $1$ 号节点，要求支持：

$1$  $v$ ：改变树根为 $v$。

$2$ $u$ $v$ $x$ : 在换根意义下，把 $LCA(u,v)$ 为根的子树的的每个点加上 $x$。

$3$ $v$ : 求换根意义下，以 $v$ 为根的子树的权值和。



------------
### Solution:
很朴素的想法，就是使用重链剖分，每次换根就重新编号，对于 $2$ $3$ 操作就是树剖基本操作了。但是这种想法很容易被卡，所以我们要优化算法。

思考在换根意义下，究竟变化了什么 $?$

假设现在预处理出了以 $1$ 为根的信息，容易知道修改和查询本质是差不多的，以下不作分类。设现在的根为 $root$。

先思考如何求 $LCA$ :

如果要在换根意义下求 $u$, $v$ 的 $LCA$ ，可以先求出 $root$ 和 $u$ 的 $LCA$,设为 $t$,再求出 $root$ 和 $v$ 的 $LCA$ ，设为 $s$。

如果 $t$ = $s$，那么换根意义下的 $LCA$ 即为 $lca$ ( $u$, $v$)；否则为 $t$ 和 $s$ 中较深的那个.


------------

再考虑子树操作假设要对以 $v$ 为根的子树进行操作，分三
种情况 $:$

如果 $v$ $=$ $root$，对整棵树操作。

如果 $root$ 在 $v$ 的子树内，先对整棵树操作，再对 $v$ 包含 $root$ 的
儿子的子树逆操作 $($ 例如，区间加的逆操作就是区间减，区间和的逆操作就是减去区间和 $)$;

否则，直接对以 $v$ 为根的子树进行操作。

------------
我们顺便思考一下链操作，易得换根对链操作无影响，所以直接一般树剖就行。

### Code:

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#define maxn 100010
using namespace std;
int n,q,t;
int root=1;
int a[maxn];
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0',ch=getchar();}
    return x*f;
}
vector<int>G[maxn];
int fa[maxn],son[maxn],siz[maxn],top[maxn],depth[maxn];
int cnt,id[maxn],rk[maxn];
struct SegmentTree{
	int l,r;
	long long sum,add;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define sum(x) tree[x].sum
	#define add(x) tree[x].add
}tree[maxn<<2];
inline void pushup(int p){sum(p)=sum(p<<1)+sum(p<<1|1);}
inline void pushdown(int p){
	sum(p<<1)+=add(p)*(r(p<<1)-l(p<<1)+1);add(p<<1)+=add(p);
	sum(p<<1|1)+=add(p)*(r(p<<1|1)-l(p<<1|1)+1);add(p<<1|1)+=add(p);
	add(p)=0;
}
void build(int p,int l,int r){
	l(p)=l,r(p)=r;
	if(l==r){sum(p)=a[rk[l]];return;}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
void change(int p,int l,int r,long long d){
    if(l<=l(p)&&r>=r(p)){
        sum(p)+=(r(p)-l(p)+1)*d;
        add(p)+=d;
        return;
	}
	pushdown(p);
	int mid=(l(p)+r(p))>>1;
	if(l<=mid)change(p<<1,l,r,d);
	if(mid<r)change(p<<1|1,l,r,d);
	pushup(p);
}
long long ask(int p,int l,int r){
	if(l<=l(p)&&r>=r(p))return sum(p);
	pushdown(p);
	long long ans=0;
	int mid=(l(p)+r(p))>>1;
	if(l<=mid)ans+=ask(p<<1,l,r);
	if(mid<r)ans+=ask(p<<1|1,l,r);
	return ans;
}
void dfs1(int x){
    siz[x]=1;
    depth[x]=depth[fa[x]]+1;
    
    for(unsigned int i=0;i<G[x].size();++i){
        int y=G[x][i];
        if(y==fa[x])continue;
        fa[y]=x;
        dfs1(y);
        siz[x]+=siz[y];
        if(siz[y]>siz[son[x]])son[x]=y;
    }
}
void dfs2(int x,int topf){
    top[x]=topf;id[x]=++cnt;rk[cnt]=x;
    if(!son[x])return;
    dfs2(son[x],topf);
    for(unsigned int i=0;i<G[x].size();++i){
        int y=G[x][i];
        if(y==fa[x]||y==son[x])continue;
        dfs2(y,y);
    }
}
inline int lca(int x,int y){
    while(top[x]!=top[y]){
        if(depth[top[x]]<depth[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    return depth[x]>depth[y]?y:x;
}
inline int la(int x,int y){
	int k=depth[x]-depth[y]-1;
	while(depth[x]-depth[fa[top[x]]]<=k){
    	k-=depth[x]-depth[fa[top[x]]];
		x=fa[top[x]];
	}
	return rk[id[x]-k];
}
int main(){
    n=read(),q=read();
    for(int i=1;i<=n;++i)a[i]=read();
    int u,v,x,type;
    for(int i=1;i<n;++i){
        u=read(),v=read();
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs1(1);
	dfs2(1,1);
	build(1,1,n);
    int t1,t2;
    while(q--){
        type=read();
        if(type==1)root=read();
        if(type==2){
            u=read(),v=read(),x=read();
            t1=lca(u,root),t2=lca(v,root);
            if(t1==t2)t1=lca(u,v);
            else if(depth[t2]>depth[t1])swap(t1,t2);
            if(t1==root)change(1,1,n,x);
            else if(lca(root,t1)==t1){
                t2=la(root,t1);
                change(1,1,n,x);
                change(1,id[t2],id[t2]+siz[t2]-1,-x);
			}
			else change(1,id[t1],id[t1]+siz[t1]-1,x);
		}
        if(type==3){
            t1=read();
            if(t1==root)printf("%lld\n",ask(1,1,n));
            else if(lca(t1,root)==t1){
            	t2=la(root,t1);
                printf("%lld\n",ask(1,1,n)-ask(1,id[t2],id[t2]+siz[t2]-1));
            }
            else printf("%lld\n",ask(1,id[t1],id[t1]+siz[t1]-1));
        }
    }
    return 0;
}
```


---

