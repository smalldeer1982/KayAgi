# GSS7 - Can you answer these queries VII

## 题目描述

给定一棵树，有$N(N \le 100000)$个节点，每一个节点都有一个权值$x_i (|x_i| \le 10000)$

你需要执行$Q (Q \le 100000)$次操作：

1. `1 a b` 查询`(a,b)`这条链上的最大子段和，可以为空（即输出$0$）
2. `2 a b c` 将`(a,b)`这条链上的所有点权变为`c` $(|c| <= 10000)$

## 样例 #1

### 输入

```
5
-3 -2 1 2 3
1 2
2 3
1 4
4 5
3
1 2 5
2 3 4 2
1 2 5```

### 输出

```
5
9```

# 题解

## 作者：Siyuan (赞：25)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[SPOJ 6779](https://www.spoj.com/problems/GSS7/)

给你一棵有 $n$ 个节点的树，每个点有一个权值 $x_i$。接下来有 $Q$ 个操作，操作分为以下 $2$ 种：

- `1 a b`：求出 $a$ 到 $b$ （包括 $a$ 和 $b$）这条路径上的权值组成的序列的最大子段和（可以为空）。
- `2 a b c`：将 $a$ 到 $b$（包括 $a$ 和 $b$）的路径上的所有点的权值改为 $c$。

数据范围：$n,Q\le 10^5$，$|x_i|,|c|\le 10^4$

------

## Solution

我们可以用树链剖分来维护这棵树，修改时直接在线段树上覆盖。询问时，我们根据树链剖分的过程，可以发现只不过是把这条链拆成了若干段，那么我们可以对这几段依次查询、维护、更新答案。

关于如何用线段树维护序列的最大子段和（这个方法很套路），详见[「SPOJ 1716」GSS3 - Can you answer these queries III](https://www.luogu.org/blog/49725/solution-sp1716)。

**时间复杂度**：$O(Q\log^2 n)$

------

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson rt<<1
#define rson rt<<1|1

const int N=1e5+5,M=2e5+5;
int n,q,tot,x[N],lnk[N],ter[M],nxt[M];
int idx,dfn[N],seq[N],sz[N],dep[N],hvy[N],top[N],fa[N];
struct Node {
    int sum,lmx,rmx,ret,tag;
    bool cov;
    Node() {sum=lmx=rmx=ret=0;}
}seg[N<<2];

void add(int u,int v) {
    ter[++tot]=v,nxt[tot]=lnk[u],lnk[u]=tot;
}
void dfs1(int u,int f) {
    dep[u]=dep[f]+1,fa[u]=f,sz[u]=1;
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==f) continue;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hvy[u]]) hvy[u]=v;
    }
}
void dfs2(int u,int tp) {
    dfn[u]=++idx,seq[idx]=u,top[u]=tp;
    if(!hvy[u]) return;
    dfs2(hvy[u],tp);
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==fa[u]||v==hvy[u]) continue;
        dfs2(v,v);
    }
}
Node merge(Node x,Node y) {
    Node ans;
    ans.sum=x.sum+y.sum;
    ans.lmx=std::max(x.lmx,x.sum+y.lmx);
    ans.rmx=std::max(y.rmx,y.sum+x.rmx);
    ans.ret=std::max(std::max(x.ret,y.ret),x.rmx+y.lmx);
    ans.tag=ans.cov=0;
    return ans;
}
void build(int rt,int l,int r) {
    if(l==r) {
        seg[rt].sum=x[seq[l]];
        seg[rt].lmx=seg[rt].rmx=seg[rt].ret=std::max(seg[rt].sum,0);
        seg[rt].cov=0;
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    seg[rt]=merge(seg[lson],seg[rson]);
}
void update(int rt,int l,int r,int k) {
    seg[rt].sum=(r-l+1)*k;
    seg[rt].lmx=seg[rt].rmx=seg[rt].ret=std::max(seg[rt].sum,0);
    seg[rt].cov=1,seg[rt].tag=k;
}
void pushdown(int rt,int l,int r) {
    if(!seg[rt].cov) return;
    int mid=(l+r)>>1;
    update(lson,l,mid,seg[rt].tag);
    update(rson,mid+1,r,seg[rt].tag);
    seg[rt].tag=seg[rt].cov=0;
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
    seg[rt]=merge(seg[lson],seg[rson]);
}
Node query(int x,int y,int rt,int l,int r) {
    if(x<=l&&r<=y) return seg[rt];
    pushdown(rt,l,r);
    int mid=(l+r)>>1;
    Node L,R;
    if(x<=mid) L=query(x,y,lson,l,mid);
    if(mid<y) R=query(x,y,rson,mid+1,r);
    return merge(L,R);
}
void chainModify(int u,int v,int k) {
    for(int fu=top[u],fv=top[v];fu^fv;u=fa[fu],fu=top[u]) {
        if(dep[fu]<dep[fv]) std::swap(u,v),std::swap(fu,fv);
        modify(dfn[fu],dfn[u],1,1,n,k);
    }
    if(dep[u]>dep[v]) std::swap(u,v);
    modify(dfn[u],dfn[v],1,1,n,k);
}
Node chainQuery(int u,int v) {
    Node L,R;
    for(int fu=top[u],fv=top[v];fu^fv;) {
        if(dep[fu]<dep[fv]) {
            R=merge(query(dfn[fv],dfn[v],1,1,n),R);
            v=fa[fv],fv=top[v];
        } else {
            L=merge(query(dfn[fu],dfn[u],1,1,n),L);
            u=fa[fu],fu=top[u];
        }
    }
    if(dep[u]>dep[v]) {
        L=merge(query(dfn[v],dfn[u],1,1,n),L);
    } else {
        R=merge(query(dfn[u],dfn[v],1,1,n),R);
    }
    std::swap(L.lmx,L.rmx);
    return merge(L,R);
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&x[i]);
    for(int i=1;i<n;++i) {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    dfs1(1,0),dfs2(1,1),build(1,1,n);
    scanf("%d",&q);
    while(q--) {
        int opt;
        scanf("%d",&opt);
        if(opt==1) {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",chainQuery(l,r).ret);
        } else {
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            chainModify(l,r,k);
        }
    }
    return 0;
}
```



---

## 作者：mzgwty (赞：12)

~~太久没写树上的题了~~

于是就来写一发$LCT$来加深记忆（~~是对板子的，当然不是这道题啊~~）

$GSS$系列规矩:$pre_x$表示以$x$结尾的最大前缀和,$suf_x$表示以$x$开头的最大后缀和,$sum_x$表示$x$所在$Spaly(emm)$子树的权值和,$ans_x$表示$x$所在$Spaly(emm2.0)$子树的最大子段和

```cpp
#define l lc
#define r rc
```

于是就有：

$sum_x=sum_l+sum_r+val_x$

$pre_x=max(pre_l,sum_l+val_x+pre_r)$

话说这里为什么不判一下$pre_l+val_x$呢？

$emming,$只有本蒟蒻可能还想了一会儿吧。

容易证到,因为可以不选任何一个点,所有$pre$值都是一个非负整数,所以$pre_r>=0$,因此就不用特判啦。

继续

同理，$suf_x=max(suf_r,sum_r+val_x+suf_l)$

$ans_x=max(suf_l+val_x+pre_r,max(ans_l,ans_r))$

除此之外，需要注意的还有几点：

1.下传反转标记时，要交换当前节点的$pre$与$suf$

2.由于本题带有负权，因此不能直接将所有节点下传后的标记记为某个特殊值~~当然你要记成一个绝对值大于10000的值也可以~~，我们需要开一个额外数组来记录当前节点的标记是否需要下传

顺便讲讲这个标记下传的问题

这是函数：
```cpp
inline void pushd(int x,int key) {
	tt[x]=val[x]=key;tag[x]=1;//tt是懒标记
	sum[x]=size[x]*key;//改掉子树和
	if(key>0) pre[x]=suf[x]=ans[x]=sum[x];//请自行理解
	else pre[x]=suf[x]=ans[x]=0;//你能理解的
}
```

3.初始时一定要把所有$size$都赋为$0$

$Code:$ 

~~码风濒死~~

```cpp
```cpp
#include<bits/stdc++.h>
#define inf 0x3fffffff
#define R register
#define rep(i,a,b) for(R int i=a ; i<=b ; ++i)
#define dwn(i,a,b) for(R int i=a ; i>=b ; --i)
#define go(i,u) for(R int i=head[u] ; i ; i=a[i].next)
#define lc ch[x][0]
#define rc ch[x][1]
using namespace std;

inline int read() {
	int res=0,f=1;char ch;
	while(!isdigit(ch=getchar())) if(ch=='-') f=-1;
	do {
		res=res*10+ch-'0';
	} while(isdigit(ch=getchar()));
	return res*f;
}

const int N=100005;

int ch[N][2],f[N],size[N],sum[N],pre[N],suf[N],ans[N],val[N],tt[N];
bool rev[N],tag[N];

inline bool nroot(int x) {
	return ch[f[x]][0]==x||ch[f[x]][1]==x;
}

inline bool get(int x) {
	return ch[f[x]][1]==x;
}

inline void pushup(int x) {
	size[x]=size[lc]+size[rc]+1;
	sum[x]=sum[lc]+sum[rc]+val[x];
	pre[x]=max(pre[lc],sum[lc]+val[x]+pre[rc]);
	suf[x]=max(suf[rc],sum[rc]+val[x]+suf[lc]);
	ans[x]=max(suf[lc]+val[x]+pre[rc],max(ans[lc],ans[rc]));
}

inline void rotate(int x) {
	int fa=f[x],grfa=f[fa],k=get(x),c=ch[x][!k];
	if(nroot(fa)) ch[grfa][get(fa)]=x;ch[x][!k]=fa;ch[fa][k]=c;
	if(c) f[c]=fa;f[fa]=x;f[x]=grfa;
	pushup(fa),pushup(x);
}

inline void pushr(int x) {
	rev[x]^=1;swap(lc,rc),swap(pre[x],suf[x]);
}

inline void pushd(int x,int key) {
	tt[x]=val[x]=key;tag[x]=1;
	sum[x]=size[x]*key;
	if(key>0) pre[x]=suf[x]=ans[x]=sum[x];
	else pre[x]=suf[x]=ans[x]=0;
}

inline void pushdown(int x) {
	if(rev[x]) {
		if(lc) pushr(lc);
		if(rc) pushr(rc);
		rev[x]=0;
	}
	if(tag[x]) {
		if(lc) pushd(lc,tt[x]);
		if(rc) pushd(rc,tt[x]);
		tag[x]=0;
	}
}

int s[N],top;

inline void pushall(int x) {
	s[top=1]=x;
	while(nroot(x)) s[++top]=x=f[x];
	while(top) pushdown(s[top--]);
}

inline void splay(int x) {
	pushall(x);
	while(nroot(x)) {
		int fa=f[x];
		if(nroot(fa)) rotate((get(x)!=get(fa))?x:fa);
		rotate(x);
	}
}

inline void access(int x) {
	for(R int fa=0 ; x ; x=f[fa=x]) splay(x),ch[x][1]=fa,pushup(x);
}

inline void makeroot(int x) {
	access(x),splay(x),pushr(x);
}

inline void split(int x,int y) {
	makeroot(x),access(y),splay(y);
}

inline void link(int x,int y) {
	makeroot(x),f[x]=y;
}

int main() {
	int n=read();
	rep(i,1,n) {
		val[i]=sum[i]=read();
		if(val[i]>0) pre[i]=suf[i]=ans[i]=val[i];
		size[i]=1;
	}
	rep(i,2,n) link(read(),read());
	int m=read();
	while(m--) {
		int op=read(),x=read(),y=read(),c;
		if(op==1) split(x,y),printf("%d\n",ans[y]);
		else c=read(),split(x,y),pushd(y,c);
	}
	return 0;
}
```


$P.S.:woc,LCT$比树剖慢了一倍啊，~~常数巨大的好处啊。~~

---

## 作者：ComplexPug (赞：12)

## GSS7解题报告
## 前言
唔，有点恶心哪，废了两个多小时debug
## 思路
很容易看出~~傻子都知道~~，这个是树链剖分+线段树的裸题，只不过是恶心了点，这里重点讲一下细节问题
## 线段树
做过GSS系列的都应该很熟悉了

线段树维护的前缀最大子段和，后缀最大子段和，和区间最大子段和

那么我们就可以很容易的写出他合并~~orpushup~~
```cpp
void pushup(node &a,node x,node y) {
	a.ans=max(max(x.ans,y.ans),x.rk+y.lk);
	a.lk=max(x.sum+y.lk,x.lk);
   	a.rk=max(y.sum+x.rk,y.rk);
	a.sum= x.sum +y.sum;
}
```
这里写成这种形式对下面的跳链比较友好

查询也是比较套路的 返回一个node，如果在mid两边，再次合并，这里就不多说了
## 树剖跳链
#### 修改操作：
跳链，修改,和平常一样
#### 查询操作：
x到y的路径是一条链子

如果我们把它伸直，捋平咯，那他就是一串数列

那我们就可以一块一块的合并喽

想一下我们是怎么跳的

是从链的两端跳，一直跳到他们相遇

那我们就维护两端的信息,也就是从起点到现在的x的区间和从现在的y到终点的区间

最后再合并起来,就是整个区间的信息喽

不过要注意合并时候的次序和l,r的交换

~~也许不swap而分类讨论就没这个东西了吧~~

我们的一条重链是从浅处到深处依次排列

我们跳的时候是从深处到浅出跳(从两端逼近中间)

所以合并就要考虑清楚了

是合并x，y还是合并y，x

文字说起来不太明白，我举个栗子吧

![](https://i.loli.net/2018/12/26/5c2345b921ef9.png)

2号权值为-1，其他权值为1，要从4号到5号点

我们先从5号节点跳到1号所属重链

在跳之前我们先查询一下5号的值，得到一个node，和x
合并

我们再从4号节点跳到1号所属重链

在跳之前我们先查询一下4号的值，又得到一个node，和y合并

然后交换x，y(别问我为什么)

![](https://i.loli.net/2018/12/26/5c23466ee7618.png)

现在x,y都到了一条链子上了（注意前提）

我们考虑一下两端区间的方向

![](https://i.loli.net/2018/12/26/5c23479d33b18.png)

有一个是反着的，我们翻过来其中一个然后全部合并起来就好了

这里给出我的两组简单但易错数据(反正错了我好多次)


```cpp
5
-1 1 1 1 1
1 5
1 2
2 3
2 4
1
1 4 5
ans=2

5
-3 -2 -1 -2 -3
1 2
2 3
1 4
4 5
2	
2 3 4 2
1 2 5
ans=6
```

## 代码

```cpp
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=6e5+7;
const int inf=0x3f3f3f3f;
inline int read() {
	int x=0,f=1;char s=getchar();
	for(;s>'9'||s<'0';s=getchar()) if(s=='-') f=-1;
	for(;s>='0'&&s<='9';s=getchar()) x=x*10+s-'0';
	return x*f;
}
vector<int> G[N];
int n,m;
int a[N],w[N],idx[N],top[N],son[N],siz[N],f[N],dep[N],cnt;
inline int max(const int &x,const int &y) {return x>y?x:y;}
void dfs1(int u,int fa) {
	f[u]=fa;
	siz[u]=1;
	dep[u]=dep[fa]+1;
	for(std::vector<int>::iterator it=G[u].begin();it!=G[u].end();++it) {
		if(fa==*it) continue;
		dfs1(*it,u);
		siz[u]+=siz[*it];
		if(siz[son[u]]<siz[*it]) son[u]=*it;
	}
}
void dfs2(int u,int topf) {
	idx[u]=++cnt;
	a[cnt]=w[u];
	top[u]=topf;
	if(!son[u]) return;
	dfs2(son[u],topf);
	for(std::vector<int>::iterator it=G[u].begin();it!=G[u].end();++it)
		if(!idx[*it]) dfs2(*it,*it);
}
namespace seg_tree {
	#define ls rt<<1
	#define rs rt<<1|1
	struct node {
		int l,r,siz,lk,rk,ans,lazy,sum;
	}e[N<<2];
	inline void pushup(node &a,node x,node y) {
		a.ans=max(max(x.ans,y.ans),x.rk+y.lk);
		a.lk=max(x.sum+y.lk,x.lk);
    	a.rk=max(y.sum+x.rk,y.rk);
    	a.sum= x.sum +y.sum;
	}
	void build(int l,int r,int rt) {
		e[rt].l=l,e[rt].r=r,e[rt].siz=r-l+1;
		e[rt].lazy=inf;
		if(l==r) {
			e[rt].sum=a[l];
			e[rt].lk=e[rt].rk=e[rt].ans=max(a[l],0);
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,ls);
		build(mid+1,r,rs);
		pushup(e[rt],e[ls],e[rs]);
	}
	inline void tag(int rt,int k) {
		e[rt].sum=e[rt].siz*k;
		if(k>=0) e[rt].lk=e[rt].rk=e[rt].ans=e[rt].sum;
		else e[rt].lk=e[rt].rk=e[rt].ans=0;
		e[rt].lazy=k;
	}
	inline void pushdown(int rt) {
		if(e[rt].lazy!=inf) {
			tag(ls,e[rt].lazy);
			tag(rs,e[rt].lazy);
			e[rt].lazy=inf;
		}
	}
	void modify(int L,int R,int k,int rt) {
		if(L<=e[rt].l&&e[rt].r<=R) {
			tag(rt,k);
			return;
		}
		pushdown(rt);
		int mid=(e[rt].l+e[rt].r)>>1;
		if(L<=mid) modify(L,R,k,ls);
		if(R>mid) modify(L,R,k,rs);
		pushup(e[rt],e[ls],e[rs]);
	}
	node query(int L,int R,int rt) {
		if(L<=e[rt].l&&e[rt].r<=R) return e[rt];
		pushdown(rt);
		int mid=(e[rt].l+e[rt].r)>>1;
		if(L<=mid && R>mid) {
			node a=query(L,R,ls),b=query(L,R,rs),c;
			pushup(c,a,b);
			return c;
		}
		if(L<=mid) return query(L,R,ls);
		if(R>mid) return query(L,R,rs);
	}
}
void QQ(int x,int y) {
	seg_tree::node tot_x={},tot_y={};
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y),swap(tot_x,tot_y);
		seg_tree::node tmp=seg_tree::query(idx[top[x]],idx[x],1);
		seg_tree::pushup(tot_x,tmp,tot_x);
		x=f[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y),swap(tot_x,tot_y);
	seg_tree::node tmp=seg_tree::query(idx[x],idx[y],1);
	swap(tot_x.lk,tot_x.rk);
	seg_tree::pushup(tot_x,tot_x,tmp);
	seg_tree::pushup(tot_y,tot_x,tot_y);
	printf("%d\n",tot_y.ans);
}
void CC(int x,int y,int c) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		seg_tree::modify(idx[top[x]],idx[x],c,1); 
		x=f[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	seg_tree::modify(idx[x],idx[y],c,1);
}
int main() {
	n=read();
	FOR(i,1,n) w[i]=read();
	FOR(i,2,n) {
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs1(1,0);
	dfs2(1,1);
	seg_tree::build(1,n,1);
	m=read();
	FOR(i,1,m) {
		int opt=read(),x=read(),y=read(),z;
		if(opt==1) QQ(x,y);
		else z=read(),CC(x,y,z);
	}
	return 0;
}

```

---

## 作者：wsyhb (赞：8)

## 前言

在求解最大子段和时，通常使用**线段树**进行维护。

有两种维护方式：一种是维护**具有可合并性的，区间前缀/后缀/全局最值**（记录前后缀是为了将相邻区间的信息合并起来）；一种是维护**矩阵的区间乘积**，又叫**动态 DP**。

本文讲解后一种方法。

## 题解

首先，这道题是树上路径问题，可通过树剖转为区间问题。（因此下文直接具体讲解最大子段和）

------------

还记得最大子段和 DP 吗？就是一个简单的 DP 方程：

$$dp_i=\max(dp_{i-1},0)+a_i$$

其中 $dp_i$ 表示以 $i$ 位置结尾的最大子段和，$a$ 表示这个序列。

设 $ans_i$ 为长度为 $i$ 的前缀的最大子段和，则：

$$ans_i=\max(ans_{i-1},dp_i)$$

那么全局的最大子段和就是 $ans_n$。

于是有下面这个式子：

$$
\begin{bmatrix}
ans_{i-1} & dp_{i-1} & 0
\end{bmatrix}

*

\begin{bmatrix}
0 & -\infty & -\infty \\
a_i & a_i & -\infty\\
a_i & a_i & 0
\end{bmatrix}

=

\begin{bmatrix}
ans_{i} & dp_{i} & 0
\end{bmatrix}
$$

其中 $*$ 表示**广义矩阵乘法**，即：把普通矩阵乘法中求和（$\Sigma$）换成求最值（$\max$ 或 $\min$，此处是取 $\max$），乘法（$\times$）换成加法（$+$）。易证其满足普通矩阵乘法的运算律。

令

$$
A_i=
\begin{bmatrix}
0 & -\infty & -\infty \\
a_i & a_i & -\infty\\
a_i & a_i & 0
\end{bmatrix}
$$

则

$$
\begin{bmatrix}
ans_{n} & dp_{n} & 0
\end{bmatrix}

=

\begin{bmatrix}
-\infty & -\infty & 0
\end{bmatrix}

*

\prod_{i=1}^{n}{A_i}
$$

其中，把 $ans_0$ 和 $dp_0$ 视为 $-\infty$。

所以将每个权值对应一个矩阵，维护这些矩阵的区间积即可。

P.S. **$A_i$ 的构造方法**：逐项比对，有这一项就配上相应的系数，没有就赋成 $-\infty$（普通矩阵乘法则赋成 $0$）。

------------

考虑一下此做法的时间复杂度——

树剖将树上路径分成 $O(\log{N})$ 段，线段树又将每一段分成 $O(\log{N})$ 个子区间，而 $3 \times 3$ 的矩阵乘法有一个 $27$ 的常数，所以仅就查询而言，时间复杂度是 $O(3^3 \times Q\log^2{N})$。

看起来很吓人，但是矩阵乘法用循环展开常数超小，且树剖和线段树的划分显然都达不到理论上限，所以还 OK。

但还没完：对于**区间赋值**，若使用常规线段树操作，并**直接计算矩阵快速幂**，`push_down` 单次是 $O(3^3 \times \log{N})$，那么**修改时间复杂度是** $O(3^3 \times Q\log^3{N})$。

虽然很明显跑不满——有人拿这个过了，但仍然考虑继续优化。

------------

可以发现，**上述的矩阵 $A_i$ 是很有特征的，以至于它的次幂其实不用快速幂，就可以直接表示出来。**

$$
A_i^2=
\begin{cases}
\begin{bmatrix}
0 & -\infty & -\infty \\
2a_i & 2a_i & -\infty\\
2a_i & 2a_i & 0
\end{bmatrix} (a_i \ge 0)\\
\\
\begin{bmatrix}
0 & -\infty & -\infty \\
a_i & 2a_i & -\infty\\
a_i & a_i & 0
\end{bmatrix} (a_i < 0)\\
\end{cases}
$$

以此类推，显然有

$$
A_i^k=
\begin{cases}
\begin{bmatrix}
0 & -\infty & -\infty \\
ka_i & ka_i & -\infty\\
ka_i & ka_i & 0
\end{bmatrix} (a_i \ge 0)\\
\\
\begin{bmatrix}
0 & -\infty & -\infty \\
a_i & ka_i & -\infty\\
a_i & a_i & 0
\end{bmatrix} (a_i < 0)\\
\end{cases}
$$

（证明的话简单归纳一下即可）

所以线段树的 `lazy` 标记只需记录数值（上文中的 $a_i$）和指数（上文中的 $k$）即可。

**总时间复杂度 $O(3^3 \cdot Q\log^2{N})$。**

## 代码

P.S. 

1. 注意树链剖分查询时，矩阵乘积的顺序是有讲究的——因此要分别记录从左到右和从右到左的矩阵乘积。具体实现见代码。
2. 虽然权值和最小可以达到 $-10^9$，但 `inf` 设为 $10^9$ 就够了，具体原因可以从上述方法的式子，以及所取的答案中看出。
3. 代码有详细注释。如果还是不懂欢迎在评论区提出或私信。~~我不信你看不懂。~~

------------

虽然速度比不过维护 $4$ 个标记的普通线段树，但也能轻松 AC。

(￣▽￣)~*

``` cpp
#include<bits/stdc++.h>
using namespace std;
int N;
const int max_N=1e5+5;
int End[max_N<<1],Last[max_N],Next[max_N<<1],e;
inline void add_edge(int x,int y)
{
	End[++e]=y,Next[e]=Last[x],Last[x]=e;
	End[++e]=x,Next[e]=Last[y],Last[y]=e;
}
int dep[max_N],sz[max_N],son[max_N],fath[max_N];
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	sz[x]=1;
	fath[x]=fa;
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fa)
		{
			dfs1(y,x);
			sz[x]+=sz[y];
			if(sz[y]>sz[son[x]])
				son[x]=y;
		}
	}
}
int top[max_N],dfn[max_N],Time,id[max_N];
void dfs2(int x,int top_now)
{
	top[x]=top_now;
	dfn[x]=++Time;
	id[Time]=x;
	if(son[x])
		dfs2(son[x],top_now);
	for(int i=Last[x];i;i=Next[i])
	{
		int y=End[i];
		if(y!=fath[x]&&y!=son[x])
			dfs2(y,y);
	}
}
int x[max_N];
const int inf=1e9;
struct Matrix
{
	int v[3][3];
	inline Matrix() // 广义矩阵乘法的单位元 I
	{
		v[0][0]=v[1][1]=v[2][2]=0;
		v[0][1]=v[0][2]=v[1][0]=v[1][2]=v[2][0]=v[2][1]=-inf;
	}
	inline Matrix(int a,int b,int c,int d=-inf,int e=-inf,int f=-inf,int g=-inf,int h=-inf,int i=-inf) // 依次传入每一位系数，后六个系数默认为 -inf （为了方便）
	{
		v[0][0]=a,v[0][1]=b,v[0][2]=c,v[1][0]=d,v[1][1]=e,v[1][2]=f,v[2][0]=g,v[2][1]=h,v[2][2]=i;
	}
	inline Matrix(int a,int k=1) // 题解中的用“数值”和“指数”就可以转化成矩阵的幂
	{
		v[0][0]=v[2][2]=0;
		v[0][1]=v[0][2]=v[1][2]=-inf;
		v[1][1]=k*a;
		v[1][0]=v[2][0]=v[2][1]=a>=0?k*a:a;
	}
};
inline Matrix operator * (const Matrix &a,const Matrix &b)
{
	return Matrix(max(max(a.v[0][0]+b.v[0][0],a.v[0][1]+b.v[1][0]),a.v[0][2]+b.v[2][0]),
	max(max(a.v[0][0]+b.v[0][1],a.v[0][1]+b.v[1][1]),a.v[0][2]+b.v[2][1]),
	max(max(a.v[0][0]+b.v[0][2],a.v[0][1]+b.v[1][2]),a.v[0][2]+b.v[2][2]),
	max(max(a.v[1][0]+b.v[0][0],a.v[1][1]+b.v[1][0]),a.v[1][2]+b.v[2][0]),
	max(max(a.v[1][0]+b.v[0][1],a.v[1][1]+b.v[1][1]),a.v[1][2]+b.v[2][1]),
	max(max(a.v[1][0]+b.v[0][2],a.v[1][1]+b.v[1][2]),a.v[1][2]+b.v[2][2]),
	max(max(a.v[2][0]+b.v[0][0],a.v[2][1]+b.v[1][0]),a.v[2][2]+b.v[2][0]),
	max(max(a.v[2][0]+b.v[0][1],a.v[2][1]+b.v[1][1]),a.v[2][2]+b.v[2][1]),
	max(max(a.v[2][0]+b.v[0][2],a.v[2][1]+b.v[1][2]),a.v[2][2]+b.v[2][2])); // 循环展开，建议另外写一个程序生成这一段代码
}
inline void operator *= (Matrix &a,const Matrix &b) {a=a*b;}
namespace SegmentTree
{
	struct Node
	{
		Matrix vl,vr; // vl/vr: 从左到右/从右到左的乘积
		int lazy; // lazy 记数值，因为指数是区间长度
	}node[max_N<<2];
	#define vl(p) node[p].vl
	#define vr(p) node[p].vr
	#define lazy(p) node[p].lazy
	#define ls(p) ((p)<<1)
	#define rs(p) ((p)<<1|1)
	inline void push_up(int p)
	{
		vl(p)=vl(ls(p))*vl(rs(p));
		vr(p)=vr(rs(p))*vr(ls(p));
	}
	void build(int p,int l,int r)
	{
		lazy(p)=inf; // lazy 为 inf 表示没有标记（注意 lazy 的值域是 [-10000,10000]）
		if(l==r)
		{
			vl(p)=vr(p)=Matrix(x[id[l]]); // 线段树下标是树剖 dfs 序，id[] 记录对应原编号
			return;
		}
		int mid=(l+r)>>1;
		build(ls(p),l,mid);
		build(rs(p),mid+1,r);
		push_up(p);
	}
	inline void push_down(int p,int l,int r,int mid)
	{
		vl(ls(p))=vr(ls(p))=Matrix(lazy(p),mid-l+1);
		vl(rs(p))=vr(rs(p))=Matrix(lazy(p),r-mid);
		lazy(ls(p))=lazy(rs(p))=lazy(p);
		lazy(p)=inf;
	}
	void modify(int p,int l,int r,int a,int b,int v)
	{
		if(a<=l&&r<=b)
		{
			vl(p)=vr(p)=Matrix(v,r-l+1);
			lazy(p)=v;
			return;
		}
		int mid=(l+r)>>1;
		if(lazy(p)!=inf)
			push_down(p,l,r,mid);
		if(a<=mid)
			modify(ls(p),l,mid,a,b,v);
		if(b>mid)
			modify(rs(p),mid+1,r,a,b,v);
		push_up(p);
	}
    // query_left()/query_right() 从左到右/从右到左，对应到树上是从上到下/从下到上
	void query_left(int p,int l,int r,int a,int b,Matrix &res) // res 是要更改的答案
	{
		if(a<=l&&r<=b)
		{
			res=vl(p)*res; // 注意 res 是左乘还是右乘，建议画图思考
			return;
		}
		int mid=(l+r)>>1;
		if(lazy(p)!=inf)
			push_down(p,l,r,mid);
		if(b>mid)
			query_left(rs(p),mid+1,r,a,b,res);
		if(a<=mid)
			query_left(ls(p),l,mid,a,b,res);
	}
	void query_right(int p,int l,int r,int a,int b,Matrix &res)
	{
		if(a<=l&&r<=b)
		{
			res*=vr(p);
			return;
		}
		int mid=(l+r)>>1;
		if(lazy(p)!=inf)
			push_down(p,l,r,mid);
		if(b>mid)
			query_right(rs(p),mid+1,r,a,b,res);
		if(a<=mid)
			query_right(ls(p),l,mid,a,b,res);
	}
}
inline int query(int x,int y)
{
	static Matrix resx,resy;
	resx=resy=Matrix(); // static 变量会保存上一次局部函数结束时的值，所以要重新赋值
	while(top[x]!=top[y])
	{
		if(dep[top[x]]>=dep[top[y]]) // 由于 x 和 y 一个从上到下，一个从下到上，不建议使用 swap 操作
		{
			SegmentTree::query_right(1,1,N,dfn[top[x]],dfn[x],resx);
			x=fath[top[x]];
		}
		else
		{
			SegmentTree::query_left(1,1,N,dfn[top[y]],dfn[y],resy);
			y=fath[top[y]];
		}
	}
	if(dep[x]>=dep[y])
		SegmentTree::query_right(1,1,N,dfn[y],dfn[x],resx);
	else
		SegmentTree::query_left(1,1,N,dfn[x],dfn[y],resy);
	return (Matrix(-inf,-inf,0)*resx*resy).v[0][0];
}
inline void modify(int x,int y,int z)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		SegmentTree::modify(1,1,N,dfn[top[x]],dfn[x],z);
		x=fath[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	SegmentTree::modify(1,1,N,dfn[x],dfn[y],z);
}
int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;++i)
		scanf("%d",x+i);
	for(int i=1;i<=N-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
	}
	dfs1(1,0),dfs2(1,1);
	SegmentTree::build(1,1,N);
	int Q;
	scanf("%d",&Q);
	while(Q--)
	{
		int op,a,b,c;
		scanf("%d%d%d",&op,&a,&b);
		if(op==1)
			printf("%d\n",max(query(a,b),0));
		else
		{
			scanf("%d",&c);
			modify(a,b,c);
		}
	}
	return 0;
}
```

另外，附上计算 $A_i$ 幂的代码，从中也可以轻易得出 $A_i$ 的幂所具有的特征。（就不用手算了）

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
struct Matrix
{
	int v[3][3];
	inline Matrix()
	{
		v[0][0]=v[1][1]=v[2][2]=0;
		v[0][1]=v[0][2]=v[1][0]=v[1][2]=v[2][0]=v[2][1]=-inf;
	}
	inline Matrix(int a,int b,int c,int d,int e,int f,int g,int h,int i)
	{
		v[0][0]=a,v[0][1]=b,v[0][2]=c,v[1][0]=d,v[1][1]=e,v[1][2]=f,v[2][0]=g,v[2][1]=h,v[2][2]=i;
	}
	inline void print()
	{
		for(int i=0;i<3;++i)
			for(int j=0;j<3;++j)
			{
				if(v[i][j]<-1000)
					printf("-inf");
				else
					printf("%d",v[i][j]);
				printf("%c",j<2?' ':'\n');
			}
	}
}A,B;
inline Matrix operator * (const Matrix &a,const Matrix &b)
{
	return Matrix(max(max(a.v[0][0]+b.v[0][0],a.v[0][1]+b.v[1][0]),a.v[0][2]+b.v[2][0]),
	max(max(a.v[0][0]+b.v[0][1],a.v[0][1]+b.v[1][1]),a.v[0][2]+b.v[2][1]),
	max(max(a.v[0][0]+b.v[0][2],a.v[0][1]+b.v[1][2]),a.v[0][2]+b.v[2][2]),
	max(max(a.v[1][0]+b.v[0][0],a.v[1][1]+b.v[1][0]),a.v[1][2]+b.v[2][0]),
	max(max(a.v[1][0]+b.v[0][1],a.v[1][1]+b.v[1][1]),a.v[1][2]+b.v[2][1]),
	max(max(a.v[1][0]+b.v[0][2],a.v[1][1]+b.v[1][2]),a.v[1][2]+b.v[2][2]),
	max(max(a.v[2][0]+b.v[0][0],a.v[2][1]+b.v[1][0]),a.v[2][2]+b.v[2][0]),
	max(max(a.v[2][0]+b.v[0][1],a.v[2][1]+b.v[1][1]),a.v[2][2]+b.v[2][1]),
	max(max(a.v[2][0]+b.v[0][2],a.v[2][1]+b.v[1][2]),a.v[2][2]+b.v[2][2]));
}
inline void operator *= (Matrix &a,const Matrix &b) {a=a*b;}
int main()
{
	A=Matrix(0,-inf,-inf,1,1,-inf,1,1,0);
	B=A;
	for(int t=1;t<=4;++t)
	{
		B.print();
		puts("");
		B*=A;
	}
	A=Matrix(0,-inf,-inf,-1,-1,-inf,-1,-1,0);
	B=A;
	for(int t=1;t<=4;++t)
	{
		B.print();
		puts("");
		B*=A;
	}
	return 0;
}
```

---

## 作者：codecode (赞：7)

如果题解界面 $\LaTeX$ 锅了，请移步博客。

------------

做这道题之前，建议先做下面两道题

- [P3384 【模板】轻重链剖分](https://www.luogu.com.cn/problem/P3384)

- [SP1716 GSS3 - Can you answer these queries III](https://www.luogu.com.cn/problem/SP1716)

否则可能这道题可能不是很好做。


------------

#### 题解：

注意到这道题的操作是关于链上的操作，考虑将其树链剖分，转移成序列上的操作。

这里我采用的是轻重链剖分。

在序列上，我们就只需要维护区间最大子段和，根据经验，可以使用线段树。

设区间 $(l,r)$ 的最大子段和为 $\operatorname{data}(l,r)$，区间的最大前缀和 $\operatorname{pre}$ 与区间的最大后缀和 $\operatorname{suf}$，及区间和 $\operatorname{sum}$。

根据做 GSS3 的经验，若设 

$$L=(l,mid) \quad R=(mid+1,r) \quad mid=(l+r)/2$$

则以上的维护数据有如下关系

$$\begin{aligned}\operatorname{data}(l,r) &=\max(\operatorname{suf}L+\operatorname{pre}R,\max(\operatorname{data}L,\operatorname{data}R))\\\operatorname{pre}(l,r) & =\max(\operatorname{pre}L,\operatorname{sum}L+\operatorname{pre}R)\\\operatorname{suf}(l,r) & =\max(\operatorname{suf}R,\operatorname{sum}R+\operatorname{suf}L)\end{aligned}$$

现在考虑区间赋值。

用一个 $\operatorname{lazytag}$ 来标记区间，若该区间全部被赋值 $x$，则令 $\operatorname{lazytag}(l,r)=x$。

注意你不能直接将 $\operatorname{lazytag}$ 初始为 $0$，否则你需要额外一个变量来记录对于这个区间是否进行了区间赋值。这里的 $\operatorname{lazytag}$ 需要初始化为绝对值大于 $10000$ 的数。

~~然后不知道为什么我两个一起用了~~

一个区间若完全被赋值，那么它的 $\operatorname{pre},\operatorname{suf},\operatorname{data}$ 均相等——在 $\operatorname{sum}>0$ 时均为 $\operatorname{sum}$，其它时候均为 $0$。

但是特别注意，$\operatorname{sum}$ 和它们并不一定相等，$\operatorname{sum}$ 是区间和，不存在判断。~~于是我就在这调了2h~~

以上为在序列上的维护方式，详情可见 GSS3 和我的代码。

**这道题还有另一个部分——对树进行剖分。**

树链剖分的跳链操作，修改操作和平时没有什么差别，关键在于查询。

回忆常规的查询操作：将待查询的链分成若干重链，然后累加。

但是这里不是累加，而是要合并它们的 $\operatorname{pre},\operatorname{suf},\operatorname{sum},\operatorname{data}$。

由于待合并的区间在树上其实也是连续的，它们的合并操作就变得和上述的合并没有实质差别了，只是区间的分割点不是 $mid$。

但是这里需要注意到一个细节：累加是可直接结合的，但是我们定义的合并操作需要序列**同向的连续**；但实际上我们将数剖成链的时候，两边都是深的在下，所以我们需要用两个变量分别记录两边的结果，最后再合并这两个变量。

其它的实现细节详见代码。

由于此题区间合并次数较多，建议单独写一个 merge 函数。

时间复杂度 $\Theta(N\log N + Q\log^2 N)$。

@复杂的哈皮狗 提供了两组很强的数据 ~~可能对于我来说很强~~，如果你的代码能过样例但提交是 WA，不妨测一下，毕竟毒瘤 SPOJ 不会告诉你究竟是怎么错的。

```
5
-1 1 1 1 1
1 5
1 2
2 3
2 4
1
1 4 5
ans=2

5
-3 -2 -1 -2 -3
1 2
2 3
1 4
4 5
2   
2 3 4 2
1 2 5
ans=6
```

我的代码：

```
#include<bits/stdc++.h>
using namespace std;
const int maxn=200000+233;
const int special_data=-26241; //所谓的一个绝对值大于10000的数
int n,q,cnt,cnt_,res;
int head[maxn],a[maxn];
struct Edge{
	int to,nxt;
}e[maxn];
struct Tree{ //树链剖分
	int data,size,son,dep,top,fa,id;
   //son:重儿子;top:当前节点所在重链顶;id:当前节点在线段树的编号
}t[maxn];
struct Seg{ //线段树
	int l,r,len,lazytag,sum;
	int pre,suf,data,tag; //tag:是否使用了lazytag
}tree[4*maxn];
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void clean(Seg &x){ //清空
	x.data=x.pre=x.suf=x.sum=x.tag=0;
	x.lazytag=special_data;
}
void pushup(int pos){ //维护 sum,pre,suf,data 的具体推导详见GSS3
	tree[pos].sum=tree[pos*2].sum+tree[pos*2+1].sum;
	tree[pos].data=max(tree[pos*2].data,tree[pos*2+1].data);
	tree[pos].data=max(tree[pos].data,tree[pos*2].suf+tree[pos*2+1].pre);
	tree[pos].pre=max(tree[pos*2].pre,tree[pos*2].sum+tree[pos*2+1].pre);
	tree[pos].suf=max(tree[pos*2+1].suf,tree[pos*2].suf+tree[pos*2+1].sum);
}
void pushdown(int pos){ //下传懒标记
	if(!tree[pos].tag)return; //未使用懒标记则返回！
	int v=tree[pos].lazytag;
	tree[pos*2].lazytag=tree[pos*2+1].lazytag=v;
	tree[pos*2].sum=v*tree[pos*2].len;
	tree[pos*2].data=tree[pos*2].pre=tree[pos*2].suf=(v>0?tree[pos*2].sum:0);
	tree[pos*2].tag=1; //下传至左儿子，具体方法已解释
	tree[pos*2+1].sum=v*tree[pos*2+1].len;
	tree[pos*2+1].data=tree[pos*2+1].pre=tree[pos*2+1].suf=(v>0?tree[pos*2+1].sum:0);
	tree[pos*2+1].tag=1; //同理
	tree[pos].lazytag=special_data;
	tree[pos].tag=0; //一定要清空！
}
Seg merge(Seg a,Seg b){
    Seg res;
    res.sum=a.sum+b.sum;
    res.pre=max(a.pre,a.sum+b.pre);
    res.suf=max(b.suf,b.sum+a.suf);
    res.data=max(max(a.data,b.data),a.suf+b.pre);
    res.lazytag=special_data;
    res.tag=0;
    return res;
}
void build(int pos,int l,int r){
    if(l==r){
        tree[pos].l=tree[pos].r=l; //区间左右端点
        tree[pos].len=1; //区间长度
        tree[pos].data=tree[pos].pre=tree[pos].suf=(a[l]>0?a[l]:0);
        tree[pos].sum=a[l]; //真实输入数据
        return;
    }
    int mid=(l+r)/2;
    tree[pos].tag=0;
    build(pos*2,l,mid);
    build(pos*2+1,mid+1,r);
    tree[pos].l=tree[pos*2].l;
    tree[pos].r=tree[pos*2+1].r;
    tree[pos].lazytag=special_data;
    tree[pos].len=tree[pos].r-tree[pos].l+1;
    pushup(pos);
}
void update(int pos,int l,int r,int val){
    if(l<=tree[pos].l&&tree[pos].r<=r){
        tree[pos].lazytag=val; //打标记，更新sum,pre,suf,data
        tree[pos].sum=val*tree[pos].len;
        tree[pos].data=tree[pos].pre=tree[pos].suf=(val>0?tree[pos].sum:0);
        tree[pos].tag=1;
        return;
    }
    pushdown(pos);
    int mid=(tree[pos].l+tree[pos].r)/2;
    if(l<=mid)update(pos*2,l,r,val);
    if(r>mid)update(pos*2+1,l,r,val);
    pushup(pos);
}
Seg query(int pos,int l,int r){ //注意：查询的返回是一个区间
    if(l<=tree[pos].l&&tree[pos].r<=r)return tree[pos];
    pushdown(pos);
    int mid=(tree[pos].l+tree[pos].r)/2;
    Seg res;
    if(l<=mid&&r>mid){
        return merge(query(pos*2,l,r),query(pos*2+1,l,r));
    }
    else{
        if(l<=mid)return query(pos*2,l,r);
        if(r>mid)return query(pos*2+1,l,r);
    }
}
void upd(int x,int y,int z){
    while(t[x].top!=t[y].top){
        if(t[t[x].top].dep<t[t[y].top].dep)swap(x,y);
        update(1,t[t[x].top].id,t[x].id,z); //更新
        x=t[t[x].top].fa; //跳链
    }
    if(t[x].dep>t[y].dep)swap(x,y);
    update(1,t[x].id,t[y].id,z);
}
Seg que(int x,int y){
    Seg res,res1,res2; //res1:左边的区间;res2:右边的区间
    clean(res);
    clean(res1);
    clean(res2); //要清空！
    while(t[x].top!=t[y].top){
        if(t[t[x].top].dep<t[t[y].top].dep){
            res2=merge(query(1,t[t[y].top].id,t[y].id),res2);
            y=t[t[y].top].fa;
        }else{
            res1=merge(query(1,t[t[x].top].id,t[x].id),res1);
            x=t[t[x].top].fa;
        }
    }
    if(t[x].dep>t[y].dep)
        res1=merge(query(1,t[y].id,t[x].id),res1);
    else res2=merge(query(1,t[x].id,t[y].id),res2);
    swap(res1.pre,res1.suf); //两个区间是反着的，颠倒后才能合并
    res=merge(res1,res2);
    return res;
}
void dfs1(int pos,int fa,int dep){
    t[pos].dep=dep;
    t[pos].fa=fa;
    t[pos].size=1;
    int maxisize=-1;
    for(int i=head[pos];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==fa)continue;
        dfs1(v,pos,dep+1);
        t[pos].size+=t[v].size;
        if(t[v].size>maxisize){
            t[pos].son=v;
            maxisize=t[v].size;
        }
    }
}
void dfs2(int pos,int topdata){
    t[pos].top=topdata;
    t[pos].id=++cnt_;
    a[cnt_]=t[pos].data;
    if(t[pos].son==0)return;
    dfs2(t[pos].son,topdata);
    for(int i=head[pos];i;i=e[i].nxt){
        int v=e[i].to;
        if(v==t[pos].fa||v==t[pos].son)continue;
        dfs2(v,v);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>t[i].data;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    dfs1(1,0,1);
    dfs2(1,1);
    build(1,1,n);
    cin>>q;
    for(int i=1;i<=q;i++){
        int opt,x,y,z;
        cin>>opt>>x>>y;
        if(opt==1)
            cout<<que(x,y).data<<endl;
        if(opt==2)
            cin>>z,upd(x,y,z);
    }
    return 0;
}
```

---

## 作者：hehelego (赞：6)

没人发2018年的陈年老科技吗qwq.  
[我的gss系列题解](https://www.luogu.com.cn/blog/hehelego/GSS-SOL) 目前有两个题不太会.

### intro
许多dp的转移(我们以一维的为例子)
$$dp_i=f( g(dp_j,a_j))$$ 
其中f是max/min/sum等等,g是+,\*,或者奇怪运算.  

我们发现这种东西,大多数是转移有结合律的.  
就是说$merge(merge(dp_{i-2},dp_{i-1}),dp_i)=merge(dp_{i-2},merge(dp_{i-1},dp_i))$.然后就可以喜闻乐见的用一些数据结构维护或者用分治算法.  

具体来说,我们有一套将正常的转移,进行扩充,写成矩阵乘法的形式,其中$dp_i$会扩充成一个$k$维列向量,转移扩充成一个$k\times k$矩阵,转移即左乘一个矩阵,并且考虑这个乘法的结合律,证明结合律之后用数据结构维护矩阵乘法.  

然后发现它可以非常好的与常见数据结构套路结合,从而搞出各种奇怪修改,各种奇怪限制,似乎被称为ddp.

### sol
扯回这个题,我们先搞一个$O(n)$单次的序列上dp来做.  
> 这一小段来自我的GSS1题解,为了方便阅读,搬到了这里.
$$f_i=\max(f_{i-1}+a_i,0)$$
$$g_i=\max(g_{i-1},f_i)$$  

写成一个
$$\vec f=\begin{bmatrix}g_i\\f_i\\0\end{bmatrix}$$  
对于在末尾加一个$a_i=v$的转移.

$A_v=\begin{bmatrix}0&v&-\infty\\-\infty&v&0\\-\infty&-\infty&0\end{bmatrix}$



我们考虑一个初值,和单位矩阵(即不变转移),另外此题的数据范围,用$\text{INF}=2^{30}\gt 10^9$就没问题.

$\vec f=\begin{bmatrix}-\infty\\0\\0\end{bmatrix}$  

$I=\begin{bmatrix}0&-\infty&-\infty\\ -\infty&0&-\infty\\-\infty&-\infty&0\end{bmatrix}$


用线段树维护区间转移矩阵乘法,修改一段区间的话,乘积自然变成矩阵的幂,倍增一下$\log n$求出来,在线段树上面划分$O(\log n)$段,打标记,快速幂.查询时下传标记,没了.  
把它搞上树,没毛病,用个HLD来支持修改.然后这里有个问题,我们这个乘法是没有交换律的所以需要维护dfs序递增/递减方向的乘法.  

然后就?做完啦.qwq.  



-----



### code

```cpp
#include <bits/stdc++.h>
const int N=100000+10;
const int K=3;
typedef int Int;
const int INF=int(1e9)+10;
int read(){
	int x=0,f=1;char c;
	do{c=getchar();if(c=='-')f=-1;}while(!isdigit(c));
	do{x=x*10+c-'0';c=getchar();}while(isdigit(c));
	return x*f;
}
struct Matrix{
	Int a[K][K];
	Int& operator()(int i,int j){ return a[i-1][j-1]; }
	Int operator()(int i,int j)const{ return a[i-1][j-1]; }
	Matrix(){}
	~Matrix(){}
};
inline Matrix identity(){ // identity matrix
	Matrix a;
	a(1,1)=0; a(1,2)=-INF; a(1,3)=-INF;
	a(2,1)=-INF; a(2,2)=0; a(2,3)=-INF;
	a(3,1)=-INF; a(3,2)=-INF; a(3,3)=0;
	return a;
}
inline Matrix cons(Int v){
	Matrix a;
	a(1,1)=0; a(1,2)=v; a(1,3)=-INF;
	a(2,1)=-INF; a(2,2)=v; a(2,3)=0;
	a(3,1)=-INF; a(3,2)=-INF; a(3,3)=0;
	return a;
}
Int max3(Int a,Int b,Int c){ return std::max(a,std::max(b,c)); }
Matrix operator*(const Matrix&a,const Matrix&b){
	Matrix c; for(int i=1;i<=3;i++) for(int j=1;j<=3;j++){
		c(i,j)=std::max(-INF,max3(a(i,1)+b(1,j),a(i,2)+b(2,j),a(i,3)+b(3,j)));
	} return c;
}
Matrix qpow(Matrix a,int p){
	Matrix r=identity();
	while(p){
		if(p&1) r=r*a;
		a=a*a; p>>=1;
	} return r;
}

typedef std::pair<int,int> Pair;
int n,m,a[N],b[N];
Pair tag[N<<2];
Matrix t[2][N<<2];
inline void pushup(int o){
	int lc=o<<1,rc=lc|1;
	t[0][o]=t[0][lc]*t[0][rc];
	t[1][o]=t[1][rc]*t[1][lc];
}
inline void pushdown(int o,int L,int R){
	int mid=(L+R)>>1,lc=o<<1,rc=lc|1;
	if(L==R||tag[o].first==0) return ;
	Matrix tmp=cons(tag[o].second);
	tag[lc]=tag[o]; tag[rc]=tag[o];
	t[0][lc]=t[1][lc]=qpow(tmp,mid-L+1);
	t[0][rc]=t[1][rc]=qpow(tmp,R-mid);
	tag[o]=Pair(0,0);
}
void build(int o,int l,int r){
	if(l==r){
		t[0][o]=t[1][o]=cons(b[l]);
		tag[o]=Pair(0,0);
		return;
	}
	int mid=(l+r)>>1,lc=o<<1,rc=lc|1;
	build(lc,l,mid); build(rc,mid+1,r);
	pushup(o);
}
Matrix qry(int qwq,int o,int L,int R,int l,int r){
	if(L>r||R<l) return identity();
	if(l<=L&&R<=r)  return t[qwq][o];
	pushdown(o,L,R);
	int mid=(L+R)>>1,lc=o<<1,rc=lc|1;
	Matrix ql=qry(qwq,lc,L,mid,l,r),qr=qry(qwq,rc,mid+1,R,l,r);
	return qwq?qr*ql:ql*qr;
}
void upd(int o,int L,int R,int l,int r,int v){
	if(L>r||R<l) return ;
	if(l<=L&&R<=r){
		tag[o]=Pair(1,v);
		t[0][o]=t[1][o]=qpow(cons(v),R-L+1);
		return ;
	}
	pushdown(o,L,R);
	int mid=(L+R)>>1,lc=o<<1,rc=lc|1;
	upd(lc,L,mid,l,r,v); upd(rc,mid+1,R,l,r,v);
	pushup(o);
}

std::vector<int> g[N];
int fa[N],size[N],son[N],dep[N];
int top[N],dfn[N],idx;
void dfs1(int u,int f){
	dep[u]=dep[fa[u]=f]+1; size[u]=1;
	for(int v:g[u]) if(v!=f){
		dfs1(v,u); size[u]+=size[v];
		if(size[v]>size[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int f){
	b[dfn[u]=++idx]=a[u]; top[u]=f;
	if(son[u]) dfs2(son[u],f);
	for(int v:g[u]) if(dfn[v]==0) dfs2(v,v);
}
void update(int x,int y,int v){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
		upd(1,1,n,dfn[top[x]],dfn[x],v);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) std::swap(x,y);
	upd(1,1,n,dfn[y],dfn[x],v);
}
Matrix qry(int o,int l,int r){ return qry(o,1,1,n,l,r); }
Int sol(int x,int y){
	Matrix A=identity(),B=identity();
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			B=qry(0,dfn[top[y]],dfn[y])*B;
			y=fa[top[y]];
		}else{
			A=A*qry(1,dfn[top[x]],dfn[x]);
			x=fa[top[x]];
		}
	}
	if(dep[x]<dep[y]) B=qry(0,dfn[x],dfn[y])*B;
	else A=A*qry(1,dfn[y],dfn[x]);
	Matrix ret=A*B;
	return std::max(ret(1,2),ret(1,3));
}

int main(){
	n=read(); for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1,a,b;i<n;i++){
		a=read();b=read();
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs1(1,1); dfs2(1,1); build(1,1,n);
	int o,x,y;
	m=read(); while(m--){
		o=read();x=read();y=read();
		if(o==1) printf("%d\n",std::max(Int(0),sol(x,y)));
		else update(x,y,read());
	}
	return 0;
}

```


如果仍然过不了,试试这个吧....我也没办法,这个做法常数本来就非常大,SPOJ又是老爷机,我也没用静态LCT去掉log,只能这样了.
```
#pragma GCC optimize("O3")
#pragma GCC optimize("O4")
#pragma GCC optimize("O5")
#pragma GCC optimize("O6")
#pragma GCC optimize("O2")
#pragma GCC optimize("O7")
#pragma GCC optimize("O8")
#pragma GCC optimize("O9")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
```

---

## 作者：GKxx (赞：4)

这题的题解怎么能不发代码呢。。。

这道题我贡献了一整页的提交记录，调了整整两天，尝试了各种办法，终于过了。

其实我一直觉得做最大子段和问题，splay比线段树好写，因为线段树query的方式有一点点迷，而splay非常直接只要提取区间就好了。~~（其实是我懒）~~

所以这道题我当然是先写了lct辣。。。

然后就WAWA大哭，尝试了各种姿势都WA，就非常难受。。。

然后我还是想用splay写~~（我真是太懒了）~~

我就写了个我从没见别人写过的 树链剖分+splay。。。然后非常光荣地TLE了

~~（spoj是真的慢）~~

~~（写不过就怪评测机）~~

所以最终我~~不见棺材不落泪~~老老实实地写了树剖+线段树，过了对拍，然后AC了

看到网上的题解里也有用LCT的，大概是我的LCT水平还没到，还得继续修炼。

至于具体的做法，如果你都做到GSS7了想必我也不用再解释线段树怎么维护了吧。。。不会的朋友请[从GSS1开始做起](https://www.luogu.org/problemnew/show/SP1043)

```cpp
#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& t) {
	int f = 0, c = getchar(); t = 0;
	while (!isdigit(c)) f |= c == '-', c = getchar();
	while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
	if (f) t = -t;
}
template <typename T, typename... Args>
inline void read(T& t, Args&... args) {
	read(t); read(args...);
}

#ifdef WIN32
#define LLIO "%I64d"
#else
#define LLIO "%lld"
#endif // WIN32 long long IO
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define rrep(i, a, b) for (int i = (a); i >= (b); --i)
#define erep(i, x) for (int i = head[x]; i; i = next[i])

const int maxn = 1e5 + 207;
int v[maxn << 1], head[maxn], next[maxn << 1];
int dep[maxn], top[maxn], size[maxn], son[maxn], fa[maxn], dfn[maxn];
int a[maxn], b[maxn];
int sum[maxn << 2], lans[maxn << 2], rans[maxn << 2], ans[maxn << 2];
bool cd[maxn << 2];
int newval[maxn << 2];
int n, m, tot, index;

inline void ae(int x, int y) {
	v[++tot] = y; next[tot] = head[x]; head[x] = tot;
	v[++tot] = x; next[tot] = head[y]; head[y] = tot;
}
void dfs1(int x) {
	size[x] = 1; dep[x] = dep[fa[x]] + 1;
	erep(i, x) if (v[i] != fa[x]) {
		fa[v[i]] = x;
		dfs1(v[i]);
		size[x] += size[v[i]];
		if (size[v[i]] > size[son[x]]) son[x] = v[i];
	}
}
void dfs2(int x, int t) {
	top[x] = t;
	dfn[x] = ++index;
	b[dfn[x]] = a[x];
	if (son[x]) dfs2(son[x], t);
	erep(i, x) if (v[i] != fa[x] && v[i] != son[x])
		dfs2(v[i], v[i]);
}

inline void update(int curr) {
	using std::max;
	sum[curr] = sum[curr << 1] + sum[curr << 1 | 1];
	lans[curr] = max(lans[curr << 1], sum[curr << 1] + lans[curr << 1 | 1]);
	rans[curr] = max(rans[curr << 1 | 1], sum[curr << 1 | 1] + rans[curr << 1]);
	ans[curr] = max({ans[curr << 1], ans[curr << 1 | 1], rans[curr << 1] + lans[curr << 1 | 1]});
}
inline void pushdown(int curr, int l, int r) {
	if (cd[curr]) {
		int mid = (l + r) >> 1, val = newval[curr];
		cd[curr << 1] = cd[curr << 1 | 1] = 1;
		newval[curr << 1] = newval[curr << 1 | 1] = val;
		sum[curr << 1] = (mid - l + 1) * val;
		sum[curr << 1 | 1] = (r - mid) * val;
		lans[curr << 1] = rans[curr << 1] = ans[curr << 1] = std::max(sum[curr << 1], 0);
		lans[curr << 1 | 1] = rans[curr << 1 | 1] = ans[curr << 1 | 1] = std::max(sum[curr << 1 | 1], 0);
		cd[curr] = 0;
	}
}
void build(int curr, int l, int r) {
	if (l == r) {
		sum[curr] = b[l];
		lans[curr] = rans[curr] = ans[curr] = std::max(b[l], 0);
		return;
	}
	int mid = (l + r) >> 1;
	build(curr << 1, l, mid);
	build(curr << 1 | 1, mid + 1, r);
	update(curr);
}
void modifySgt(int curr, int lb, int rb, int l, int r, int val) {
	if (l <= lb && r >= rb) {
		cd[curr] = 1;
		newval[curr] = val;
		sum[curr] = (rb - lb + 1) * val;
		ans[curr] = lans[curr] = rans[curr] = std::max(sum[curr], 0);
		return;
	}
	int mid = (lb + rb) >> 1;
	pushdown(curr, lb, rb);
	if (l <= mid)
		modifySgt(curr << 1, lb, mid, l, r, val);
	if (mid < r)
		modifySgt(curr << 1 | 1, mid + 1, rb, l, r, val);
	update(curr);
}
void querySgt(int curr, int lb, int rb, int l, int r, int &ta, int &tl, int &tr, int &ts) {
	if (l <= lb && r >= rb) {
		ta = ans[curr]; tl = lans[curr]; tr = rans[curr]; ts = sum[curr];
		return;
	}
	int mid = (lb + rb) >> 1;
	pushdown(curr, lb, rb);
	if (mid < l) {
		querySgt(curr << 1 | 1, mid + 1, rb, l, r, ta, tl, tr, ts);
		return;
	}
	if (r <= mid) {
		querySgt(curr << 1, lb, mid, l, r, ta, tl, tr, ts);
		return;
	}
	int lea = 0, lel = 0, ler = 0, les = 0;
	int rea = 0, rel = 0, rer = 0, res = 0;
	querySgt(curr << 1, lb, mid, l, r, lea, lel, ler, les);
	querySgt(curr << 1 | 1, mid + 1, rb, l, r, rea, rel, rer, res);
	using std::max;
	tl = max(lel, les + rel);
	tr = max(rer, res + ler);
	ts = les + res;
	ta = max({lea, rea, ler + rel});
}

inline int query(int x, int y) {
	int xlm = 0, xrm = 0, xsum = 0, xans = 0;
	int ylm = 0, yrm = 0, ysum = 0, yans = 0;
	using std::max;
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) {
			int ta = 0, tl = 0, tr = 0, ts = 0;
			querySgt(1, 1, n, dfn[top[x]], dfn[x], ta, tl, tr, ts);
			xans = max({xans, ta, xlm + tr});
			xlm = max(xlm + ts, tl);
			xrm = max(xrm, xsum + tr);
			xsum += ts;
			x = fa[top[x]];
		} else {
			int ta = 0, tl = 0, tr = 0, ts = 0;
			querySgt(1, 1, n, dfn[top[y]], dfn[y], ta, tl, tr, ts);
			yans = max({yans, ta, ylm + tr});
			ylm = max(ylm + ts, tl);
			yrm = max(yrm, ysum + tr);
			ysum += ts;
			y = fa[top[y]];
		}
	}
	if (dep[x] < dep[y]) {
		int ta = 0, tl = 0, tr = 0, ts = 0;
		querySgt(1, 1, n, dfn[x], dfn[y], ta, tl, tr, ts);
		yans = max({yans, ta, ylm + tr});
		ylm = max(ylm + ts, tl);
		yrm = max(yrm, ysum + tr);
		ysum += ts;
	} else {
		int ta = 0, tl = 0, tr = 0, ts = 0;
		querySgt(1, 1, n, dfn[y], dfn[x], ta, tl, tr, ts);
		xans = max({xans, ta, xlm + tr});
		xlm = max(xlm + ts, tl);
		xrm = max(xrm, xsum + tr);
		xsum += ts;
	}
	return max({xans, yans, xlm + ylm});
}
inline void modify(int x, int y, int val) {
	while (top[x] != top[y]) {
		if (dep[top[x]] > dep[top[y]]) {
			modifySgt(1, 1, n, dfn[top[x]], dfn[x], val);
			x = fa[top[x]];
		} else {
			modifySgt(1, 1, n, dfn[top[y]], dfn[y], val);
			y = fa[top[y]];
		}
	}
	if (dep[x] > dep[y])
		modifySgt(1, 1, n, dfn[y], dfn[x], val);
	else
		modifySgt(1, 1, n, dfn[x], dfn[y], val);
}

int main() {
	read(n);
	rep(i, 1, n) read(a[i]);
	rep(i, 1, n - 1) {
		int x, y; read(x, y);
		ae(x, y);
	}
	dfs1(1);
	dfs2(1, 1);
	build(1, 1, n);
	read(m);
	rep(i, 1, m) {
		int q, x, y; read(q, x, y);
		if (q == 1)
			printf("%d\n", query(x, y));
		else {
			int val; read(val);
			modify(x, y, val);
		}
	}
	return 0;
}
```

---

## 作者：hyfhaha (赞：3)

# 树上最大子段和
终于到树链剖分啦，传说什么区间问题都能搬到树上，最大子段和也不例外。

## 前置技能GSS3和树链剖分

不会的可以先看[这里QvQ](https://www.luogu.org/blog/juruohyfhaha/gss-ji-lie-ti-xie-zui-tai-zi-duan-hu-ji-lie) ！里面是我做过的全部GSS系列最大子段和的BLOG。

先来看看GSS7，要支持两个操作。一查询，二修改。

#### 建树就不用说了吧。

首先修改操作，和普通树链剖分一样，用上面的区间修代码加树链剖分就OK辽。
```cpp
树链剖分过程
void linkadd(int x,int y,int z){
    int fx=top[x],fy=top[y];
    while(fx!=fy){
        if(dep[fx]<dep[fy])swap(x,y),swap(fx,fy);
        update(1,1,seg[0],seg[fx],seg[x],z);
        x=father[fx];fx=top[x];
    }
    if(dep[x]>dep[y])swap(x,y);
    update(1,1,seg[0],seg[x],seg[y],z);
}
```
重点是查询！
## 查询
我们知道树链剖分的核心就在于把树上的链化为序列。所以我们在树链剖分的过程中将链上的序列合并，最后得出的序列即为要求序列。

那么怎么在跳重链的过程将序列合并呢？

我们维护两个结构体L和R，分别表示左链上的序列和右链上的序列。什么意思呢？两个点x和y的最近公共祖先F只有一个。那么我们称F到x那一段为左链，F到y那一段为右链。

跳重链的过程可能是一下跳到F到x那一段，一下跳到F到y那一段，所以如果在F到x那一段，我们将那段区间加入到L，不然加入到R。

最后将L和R合并即是最后序列。小细节：要将L的left和right互换再合并。

还是挺复杂的，看看代码注释比较有帮助：
```cpp
kkk linkquery(int x,int y){
	kkk L,R;
	int fx=top[x],fy=top[y];
	while(fx!=fy){				//跳重链
		if(dep[fx]<dep[fy]){
			R=merge(query(1,1,n,seg[fy],seg[y]),R);     //跳到了F到y那边，和R合并
			y=father[fy];fy=top[y];
		}else{
			L=merge(query(1,1,n,seg[fx],seg[x]),L);     //跳到了F到x那边，和L合并
			x=father[fx];fx=top[x];
		}
	}
	if(dep[x]>dep[y]){
		L=merge(query(1,1,n,seg[y],seg[x]),L);      	//同上
	}else{
		R=merge(query(1,1,n,seg[x],seg[y]),R);
	}
	swap(L.left,L.right);				//交换
	return merge(L,R);				//合并L,R
}
```
剩下也差不多，代码比较长，放剪切板里：[GSS7代码](https://www.luogu.org/paste/qo2lx0on)

---

## 作者：Juan_feng (赞：3)

### NOIP之后无心刷DP题，就又来水数据结构了= =

#### 本题可以用树剖+珂朵莉树水过

**如果不了解珂朵莉树的话可以到[CF896C](https://www.luogu.org/problemnew/show/CF896C)的题解区看一下**

具体做法就是先用树剖处理一下，然后区间修改就用珂朵莉树暴力推平，区间最大子段和直接暴力去求就好啦qwq

注意一下在树剖求区间最大子段和，每次统计的时候要加上之前剩余数值（前一条链上的与当前链相连的最大子段和，因为是x， y两边同时向上跳，所以要用两个变量去保存），交换x， y的时候要同时交换对应的剩余数值，**当最后x， y在同一条链上的时候要再交换一下x，y对应的剩余数值**。（WA了好几次QAQ）

**如果有什么问题或者对题解有什么意见和建议的话欢迎私信小蒟蒻qwqwq。**

**那么代码如下：**


```
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio> 
#include <cmath>
#include <set>
#define re register
#define ll long long
#define maxn 200010
#define FOR(i, l, r) for(re int i = l; i <= r; ++i)
#define IT set<node>::iterator
using namespace std;

int n, m, c, r, t, x, y, z, num, cnt, sss, fir1, fir2;
int a[maxn], ans[maxn], tag[maxn], depth[maxn], fa[maxn], top[maxn], id[maxn], dd[maxn];
int son[maxn], head[maxn], siz[maxn];

struct hz {
    int next;
    int to;
}h[maxn];

inline void in(int &x){
    x=0;int f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c==-1) return;
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
    x=x*f;
}

inline void out(int a){
    if(a<0){
        a*=-1;
        putchar('-');
    } 
    if(a>=10)out(a/10);
    putchar(a%10+'0');
}

struct node{
    int l;
    int r;
    mutable int v;
    node(int L, int R = -1, int V = 0):l(L), r(R), v(V){}
    bool operator <(const node &o)const {
        return l < o.l;
    }
};

set<node> s;

IT split(int pos) { 
    IT it = s.lower_bound(node(pos));
    if(it != s.end() && it->l == pos)
      return it;
    --it;
    int L = it->l;
    int R = it->r;
    int V = it->v;
    s.erase(it);
    s.insert(node(L, pos-1, V));
    return s.insert(node(pos, R, V)).first;
}

void assign_val(int l, int r, int val = 0) { //推平
    IT itr = split(r+1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, val));
}

int query(int l, int r) { //暴力统计
    IT itr = split(r+1), itl = split(l);
    int anss = fir1;
    int res = fir1;
    --itr;
    --itl;
    for(; itl != itr; --itr) {
        res += (itr->r-itr->l+1)*itr->v;
        if(res > anss)
          anss = res;
        if(res < 0)
          res = 0;
    }
    fir1 = res;
    return anss;
}

void add(int from, int to) { 
    h[++num].next = head[from];
    h[num].to = to;
    head[from] = num;
}

void dfs1(int f, int ff) { //树剖预处理
    fa[f] = ff;
    depth[f] = depth[ff]+1;
    siz[f] = 1;
    for(re int i = head[f]; i != 0; i = h[i].next) {
        if(h[i].to == ff)
          continue;
        dfs1(h[i].to, f);
        siz[f] += siz[h[i].to];
        if(siz[h[i].to] > siz[son[f]])
          son[f] = h[i].to;
    } 
}

void dfs2(int x, int topf) { //同上
    top[x] = topf;
    id[x] = ++cnt;
    dd[cnt] = a[x];
    if(!son[x])
      return;
    dfs2(son[x], topf);
    for(re int i = head[x]; i != 0; i = h[i].next) {
        if(h[i].to == fa[x] || h[i].to == son[x])
          continue;
        dfs2(h[i].to, h[i].to);
    }
}

void updrange(int x, int y, int k) { //推平
    while(top[x] != top[y]) {
    	if(depth[top[x]] < depth[top[y]])
    	  swap(x, y);
    	assign_val(id[top[x]], id[x], k);
    	x = fa[top[x]];
    }
    if(depth[x] > depth[y])
      swap(x, y);
    assign_val(id[x], id[y], k);
}

int qrange(int x, int y) { //区间最大子段和
    int anss = 0;
    while(top[x] != top[y]) {
        if(depth[top[x]] < depth[top[y]]) {
            swap(x, y);
            swap(fir1, fir2); //注意
        }  
        anss = max(anss, query(id[top[x]], id[x]));
        x = fa[top[x]];
    }
    if(depth[x] > depth[y]) {
        swap(x, y);
        swap(fir1, fir2); //注意
    }
    swap(fir1, fir2); //最后要再交换一下
    anss = max(anss, query(id[x], id[y]));
    anss = max(anss, fir1+fir2);
    return anss;
}

//void ts(int l, int r) { //用于调试
//	cout << endl;
//	IT itr = split(r+1), itl = split(l);
//	for(; itl != itr; ++itl)
//	  FOR(i, 1, itl->r-itl->l+1)
//	    cout << itl->v << " ";
//	cout << endl;
//  return;
//}

int main() {
    in(n);
    FOR(i, 1, n)
      in(a[i]);
    FOR(i, 1, n-1) {
        in(x), in(y);
        add(x, y);
        add(y, x);
    }	
    dfs1(1, 0);
    dfs2(1, 1);
    FOR(i, 1, n)
      s.insert(node(i, i, dd[i]));
    s.insert(node(1, n+233, 0));
    in(m);
    FOR(i, 1, m) {
    	in(t);
    	if(t == 1) {
    		in(x), in(y);
    		fir1 = 0;
    		fir2 = 0;
    		out(qrange(x, y));
    		putchar(10);
        }
        else {
            in(x), in(y), in(z);
            updrange(x, y, z);
        }
    }
}
```

---

## 作者：kouylan (赞：1)

## 题解 SP6779 【GSS7 - Can you answer these queries VII】

### 【题意】
给一棵树，两种操作
1. $oper==1$，把$x$到$y$的路径上的点权修改成$z$。
2. $oper==2$，查询$x$到$y$路径上的最大子段和。

### 【分析】
树上[最大子段和](https://www.luogu.com.cn/problem/SP1716)，就用[树链剖分](https://www.luogu.com.cn/problem/P3384)即可。

查出每一段上的$mx$，$lsum$，$rsum$，$sum$求出，在进行$merge$即可。

下面是AC代码
```cpp
/*
luogu SP6779
*/
#include <bits/stdc++.h>
using namespace std;

#define lson o<<1
#define rson o<<1|1
#define mid (l+r>>1)

const int INF = 0x7f7f7f7f;

int n,q,v[100005];
int ee,h[100005],nex[100005<<1],to[100005<<1];
int cnt,mark[100005],a[100005];
int dep[100005],f[100005];
int son[100005],top[100005],siz[100005];
struct segtree{
	int mx;
	int ls,rs,sum;
	int lazy;
}dat[100005<<2];

void addedge(int x,int y)
{
	nex[++ee] = h[x];
	to[ee] = y;
	h[x] = ee;
}

void dfs1(int x,int pre)
{
	siz[x] = 1;
	dep[x] = dep[pre]+1;
	f[x] = pre;
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=pre)
		{
			dfs1(to[i],x);
			if(siz[to[i]]>siz[son[x]])
				son[x] = to[i];
			siz[x] += siz[to[i]];
		}
}

void dfs2(int x,int topx,int pre)
{
	mark[x] = ++cnt;
	a[mark[x]] = v[x];
	top[x] = topx;
	if(!son[x])
		return;
	dfs2(son[x],topx,x);
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=pre && to[i]!=son[x])
			dfs2(to[i],to[i],x);
}

void update(int o)
{
	dat[o].sum = dat[lson].sum+dat[rson].sum;
	dat[o].ls = max(dat[lson].ls,dat[lson].sum+dat[rson].ls);
	dat[o].rs = max(dat[rson].rs,dat[rson].sum+dat[lson].rs);
	dat[o].mx = max(max(dat[lson].mx,dat[rson].mx),dat[lson].rs+dat[rson].ls);
}

void build(int o,int l,int r)
{
	dat[o].lazy = -INF;
	if(l==r)
	{
		dat[o].mx = dat[o].sum = dat[o].ls = dat[o].rs = a[l];
		return;
	}
	build(lson,l,mid);
	build(rson,mid+1,r);
	update(o);
}

void pushdown(int o,int l,int r)
{
	if(dat[o].lazy>-INF)
	{
		dat[lson].sum = dat[o].lazy*(mid-l+1);
		dat[lson].ls = dat[lson].rs = dat[lson].mx = (0,dat[lson].sum);
		dat[rson].sum = dat[o].lazy*(r-mid);
		dat[rson].ls = dat[rson].rs = dat[rson].mx = (0,dat[rson].sum);
		dat[lson].lazy = dat[rson].lazy = dat[o].lazy;
	}
	dat[o].lazy = -INF;
}

segtree merge(segtree a,segtree b)
{
	segtree t;
	t.sum = a.sum+b.sum;
	t.ls = max(a.ls,a.sum+b.ls);
	t.rs = max(b.rs,b.sum+a.rs);
	t.mx = max(max(a.mx,b.mx),a.rs+b.ls);
	t.lazy = -INF;
	return t;
}

void modify(int o,int l,int r,int ql,int qr,int v)
{
	if(l>=ql && r<=qr)
	{
		dat[o].sum = v*(r-l+1);
		dat[o].ls = dat[o].rs = dat[o].mx = max(0,dat[o].sum);
		dat[o].lazy = v;
		return;
	}
	pushdown(o,l,r);
	if(ql<=mid)
		modify(lson,l,mid,ql,qr,v);
	if(qr>mid)
		modify(rson,mid+1,r,ql,qr,v);
	update(o);
}

void modify_(int x,int y,int z)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		modify(1,1,n,mark[top[x]],mark[x],z);
		x = f[top[x]];
	}
	if(dep[x]>dep[y])
		modify(1,1,n,mark[y],mark[x],z);
	else
		modify(1,1,n,mark[x],mark[y],z);
}

segtree query(int o,int l,int r,int ql,int qr)
{
	if(l>=ql && r<=qr)
		return dat[o];
	pushdown(o,l,r);
	if(qr<=mid)
		return query(lson,l,mid,ql,qr);
	else if(ql>mid)
		return query(rson,mid+1,r,ql,qr);
	return merge(query(lson,l,mid,ql,qr),query(rson,mid+1,r,ql,qr));
}

int query_(int x,int y)
{
	segtree l,r;
	l.lazy = l.ls = l.mx = l.rs = l.sum = r.lazy = r.ls = r.mx = r.rs = r.sum = 0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]])
		{
			r = merge(query(1,1,n,mark[top[y]],mark[y]),r);
			y = f[top[y]];
		}
		else
		{
			l = merge(query(1,1,n,mark[top[x]],mark[x]),l);
			x = f[top[x]];
		}
	}
	if(dep[x]>dep[y])
		l = merge(query(1,1,n,mark[y],mark[x]),l);
	else
		r = merge(query(1,1,n,mark[x],mark[y]),r);
	return max(max(l.mx,r.mx),l.ls+r.ls);
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;cin>>v[i++]);
	for(int i=1,x,y;i<n&&cin>>x>>y;i++)
	{
		addedge(x,y);
		addedge(y,x);
	}
	dfs1(1,0);
	dfs2(1,1,0);
	build(1,1,n);
	cin>>q;
	while(q--)
	{
		int oper;
		scanf("%d",&oper);
		if(oper==2)
		{
			int x,y,z;
			scanf("%d %d %d",&x,&y,&z);
			modify_(x,y,z);
		}
		else if(oper==1)
		{
			int x,y;
			scanf("%d %d",&x,&y);
			printf("%d\n",query_(x,y));
		}
	}
	
	return 0;
}
```

祝大家AC愉快！

---

## 作者：Setsugesuka (赞：1)

不难发现这道题与[SDOI2011]的做法是可以完全一致的。

对于链赋值，很自然的想到就是在 $DFS$ 序上区间赋值， $ODT$ 可以高效地解决这一类问题。

对于操作 $1$ ，我们每次把 $top$ 深度大的那个点提到它的 $top$ 上，并把之间对应的 $DFS$ 序区间推平。

对于操作 $2$ ，我们像染色那道题一样维护即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

template <class T>
inline bool read(T &ret)
{
    char c;
    int sgn;
    if (c = getchar(), c == EOF)
    {
        return 0;
    }
    while (c != '-' && (c < '0' || c > '9'))
    {
        c = getchar();
    }
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
    {
        ret = ret * 10 + (c - '0');
    }
    ret *= sgn;
    return 1;
}

template <class T>
inline void write(T x)
{
    if (x > 9)
    {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}

const int MAXN=1e6+10;

struct edge
{
    int u,v,nex;
};

struct node
{
    int l,r,v;
    node(int L,int R=-1,int V=0):l(L),r(R),v(V) {}
    bool operator <(const node &o) const
    {
        return l<o.l;
    }
};

edge e[MAXN<<1];
set<node> s;
int head[MAXN],cnt=0;
int dep[MAXN],fa[MAXN],top[MAXN],sz[MAXN],id[MAXN],val[MAXN],rk[MAXN],son[MAXN];
int n,m,tot=0,ans1,ans2;

inline set<node>::iterator split(int pos)
{
    set<node>::iterator it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    it--;
    int L=it->l,R=it->r,V=it->v;
    s.erase(it);
    s.insert(node(L,pos-1,V));
    return s.insert(node(pos,R,V)).first;
}

inline void assignval(int l,int r,int v=0)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,v));
}

inline int query(int l,int r)
{
    set<node>::iterator itr=split(r+1),itl=split(l);
    int cc1=ans1,cc2=ans1;
    --itr,--itl;
    for(;itl!=itr;--itr)
    {
        cc2+=(itr->r-itr->l+1)*itr->v;
        if(cc2>cc1)
            cc1=cc2;
        if(cc2<0)
            cc2=0;
    }
    ans1=cc2;
    return cc1;
}

inline void add(int u,int v)
{
    e[++cnt].u=u;
    e[cnt].v=v;
    e[cnt].nex=head[u];
    head[u]=cnt;
}

void dfs1(int u)
{
    sz[u]=1;
    for(int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;
        dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])
            son[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    id[u]=++tot;
    rk[tot]=u;
    if(!son[u])
        return;
    dfs2(son[u],tp);
    for(int i=head[u];i;i=e[i].nex)
    {
        int v=e[i].v;
        if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
    }
}

inline void update(int x,int y,int v)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        assignval(id[top[x]],id[x],v);
        x=fa[top[x]];
    }
    if(id[x]>id[y]) swap(x,y);
    assignval(id[x],id[y],v);
}

inline int sum(int x,int y)
{
    int ret=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y),swap(ans1,ans2);
        ret=max(ret,query(id[top[x]],id[x]));
        x=fa[top[x]];
    }
    if(id[x]>id[y]) swap(x,y),swap(ans1,ans2);
    swap(ans1,ans2);
    ret=max(ret,query(id[x],id[y]));
    ret=max(ret,ans1+ans2);
    return ret;
}

int main()
{
    read(n);
    for(int i=1;i<=n;i++)
        read(val[i]);
    for(int i=1;i<n;i++)
    {
        int x,y;
        read(x),read(y);
        add(x,y);
        add(y,x);
    }
    dfs1(1);
    dfs2(1,1);
    for(int i=1;i<=n;i++)
        s.insert(node(i,i,val[rk[i]]));
    read(m);
    while(m--)
    {
        int op;
        read(op);
        if(op==1)
        {
            int x,y;
            read(x),read(y);
            ans1=0,ans2=0;
            write(sum(x,y));
            putchar('\n');
        }
        else
        {
            int x,y,z;
            read(x),read(y),read(z);
            update(x,y,z);
        }
    }
    return 0;
}
```


---

## 作者：Jμdge (赞：1)

码农题，想想就是树剖加线段树了吧...
（两个都算板子，当然线段树是...比较恶心的最大子段和板子）

1. 这题的关键是：

>树剖是自上到下合并出解的，在这里是要将两条链合并那么 lmx 和 rmx 会出锅

>解决方法很简单，就是翻转一下最后处理出来的一条链的 lmx 和 rmx 就好了


2. 其实还有一个关键就是你打过 GSS 1 

>洛谷搜索 GSS1 并 A 掉


代码还是有 $90^+$ 行的

```
//by Judge
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+111;
char buf[1<<20],*p1,*p2;
#ifndef Judge
#define getchar() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
#endif
inline int read() { int x=0,f=1; char c=getchar();
	for(; !isdigit(c); c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c); c=getchar()) x=x*10+c-'0'; return x*f;
} char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
inline void print(int x,char chr='\n'){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]=chr;
} int n,pat,tim,head[M],x[M],dfn[M],id[M];
int f[M],son[M],siz[M],dep[M],top[M];
struct Node { int sum,lmx,rmx,mmx,tag,cov;
	Node(){sum=lmx=rmx=mmx=0;} }t[M<<2],opt;
struct Edge{ int to,nxt; }e[M<<1];
inline void add(int u,int v){
	e[++pat]=(Edge){v,head[u]},head[u]=pat;
	e[++pat]=(Edge){u,head[v]},head[v]=pat;
}
#define v e[i].to
void dfs(int u,int fa){ dep[u]=dep[fa]+1,siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt) if(v^fa)
		dfs(v,u),f[v]=u,siz[u]+=siz[v],
		son[u]=siz[son[u]]<siz[v]?v:son[u];
}
void dfs(int u){
	if(!top[u]) top[u]=u; dfn[u]=++tim,id[tim]=u;
	if(son[u]) top[son[u]]=top[u],dfs(son[u]);
	for(int i=head[u];i;i=e[i].nxt)
		if(v^f[u]&&v^son[u]) dfs(v);
}
#undef v
#define ls k<<1
#define rs k<<1|1
#define mid (l+r>>1)
#define lson ls,l,mid
#define rson rs,mid+1,r
inline int Max(int a,int b){ return a>b?a:b; }
Node merge(Node a,Node b) { Node tmp; tmp.tag=tmp.cov=0;
	tmp.lmx=Max(a.lmx,a.sum+b.lmx),tmp.rmx=Max(b.rmx,b.sum+a.rmx);
	tmp.sum=a.sum+b.sum,tmp.mmx=Max(Max(a.mmx,b.mmx),a.rmx+b.lmx); return tmp;
}
void build(int k,int l,int r){
	if(l==r) return t[k].sum=x[id[l]],t[k].cov=0,
		t[k].lmx=t[k].rmx=t[k].mmx=Max(x[id[l]],0),void();
	build(lson),build(rson),t[k]=merge(t[ls],t[rs]);
}
void pushup(int k,int l,int r,int K){
	t[k].sum=(r-l+1)*K,t[k].cov=1,t[k].tag=K,
	t[k].lmx=t[k].rmx=t[k].mmx=Max(t[k].sum,0);
}
void pushdown(int k,int l,int r){ if(!t[k].cov) return ;
	pushup(lson,t[k].tag),pushup(rson,t[k].tag),t[k].tag=t[k].cov=0;
}
void update(int k,int l,int r,int L,int R,int K){
	if(L>r||l>R) return ; if(L<=l&&r<=R) return pushup(k,l,r,K);
	pushdown(k,l,r),update(lson,L,R,K),update(rson,L,R,K),t[k]=merge(t[ls],t[rs]);
}
Node query(int k,int l,int r,int L,int R){
	if(L<=l&&r<=R) return t[k]; pushdown(k,l,r);
	if(R<=mid) return query(lson,L,R); if(L>mid) return query(rson,L,R);
	return merge(query(lson,L,mid),query(rson,mid+1,R));
}
void tupdate(int u,int v,int k){
	for(;top[u]^top[v];u=f[top[u]]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		update(1,1,n,dfn[top[u]],dfn[u],k);
	} if(dep[u]>dep[v]) swap(u,v);
	update(1,1,n,dfn[u],dfn[v],k);
}
Node tquery(int u,int v){ Node L,R;
	for(;top[u]^top[v];) if(dep[top[u]]<dep[top[v]])
			R=merge(query(1,1,n,dfn[top[v]],dfn[v]),R),v=f[top[v]];
		else L=merge(query(1,1,n,dfn[top[u]],dfn[u]),L),u=f[top[u]];
	if(dep[u]>dep[v]) L=merge(query(1,1,n,dfn[v],dfn[u]),L);
	else R=merge(query(1,1,n,dfn[u],dfn[v]),R);
	return swap(L.lmx,L.rmx),merge(L,R);
}
int main() { n=read();
	for(int i=1; i<=n; ++i) x[i]=read();
	for(int i=1,x,y;i<n;++i) x=read(),y=read(),add(x,y);
	dfs(1,0),dfs(1),build(1,1,n);
	for(int q=read(),op,l,r,k;q;--q){ op=read();
		if(op&1) l=read(),r=read(),print(tquery(l,r).mmx);
		else l=read(),r=read(),k=read(),tupdate(l,r,k);
	} return Ot(),0; 
}

```


---

## 作者：nekko (赞：1)

[GSS系列题解](https://www.magichut.pw/index.php/archives/GSS.html)

# 做法1

直接LCT维护一下就行

# 做法2

其实也可以树剖

线段树维护一下区间最大连续子段和、区间和、区间左右为端点的最大连续和

查询的话就把路径拆分成O(logn)个区间咯，然后随便暴力就行……

---

## 作者：xukuan (赞：0)

算法：树链剖分

这题和普通树剖的主要区别在于其转移（也就是pushup的过程）

直接常规转移是不行的，因为最大值横跨多条重链的话你会直接挂掉

那么我们的转移要改变一下

我们可以把用到的几条重链合在一起，合成一个线段树。合成的时候顺路转移

pushup的代码：

一般的pushup就是tree[p]=pushup(tree[p<<1],tree[p<<1|1])

```cpp
inline SegmentTree pushup(SegmentTree x,SegmentTree y){
    SegmentTree ans;
    ans.Amax=x.Amax+y.Amax;
    ans.Lmax=max(x.Lmax,x.Amax+y.Lmax);
    ans.Rmax=max(y.Rmax,y.Amax+x.Rmax);
    ans.Mmax=max(max(x.Mmax,y.Mmax),x.Rmax+y.Lmax);
    ans.tag=ans.cov=0;
    return ans;
}
```

因为要有合并操作，线段树中不建议存下左右端点

时间复杂度：$q log^2 n$，我的代码700ms，不会TLE掉

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

const ll N=100010;
ll n,m,cnt,w[N],a[N],id[N],size[N],d[N],son[N],top[N],father[N];
ll ver[N<<1],Next[N<<1],head[N],tot;
struct SegmentTree{
    ll Amax,Lmax,Rmax,Mmax,tag;
    bool cov;
    SegmentTree(){Lmax=Rmax=Amax=Mmax=0;}
    /*
    Amax代表区间总和
    Lmax代表最大左子段和
    Rmax代表最大右子段和
    Mmax代表最大子段和
    cov代表有无标记
    tag代表标记的值
    */
}tree[N<<2];

inline ll read(){
    ll x=0,tmp=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') tmp=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return tmp*x;
}

inline void write(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<3)+(y<<1);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}

inline void addEdge(ll x,ll y){
    ver[++tot]=y;
    Next[tot]=head[x];
    head[x]=tot;
}

void dfs1(ll x,ll before){
    d[x]=d[before]+1; father[x]=before; size[x]=1;
    for(ll i=head[x]; i; i=Next[i]){
        ll y=ver[i];
        if(y==before) continue;
        dfs1(y,x);
        size[x]+=size[y];
        if(size[y]>size[son[x]]) son[x]=y;
    }
}

void dfs2(ll x,ll topf){
    id[x]=++cnt; a[cnt]=w[x]; top[x]=topf;
    if(!son[x]) return;
    dfs2(son[x],topf);
    for(ll i=head[x]; i; i=Next[i]){
        ll y=ver[i];
        if(y==father[x]||y==son[x]) continue;
        dfs2(y,y);
    }
}

inline SegmentTree pushup(SegmentTree x,SegmentTree y){
    SegmentTree ans;
    ans.Amax=x.Amax+y.Amax;
    ans.Lmax=max(x.Lmax,x.Amax+y.Lmax);
    ans.Rmax=max(y.Rmax,y.Amax+x.Rmax);
    ans.Mmax=max(max(x.Mmax,y.Mmax),x.Rmax+y.Lmax);
    ans.tag=ans.cov=0;
    return ans;
}

inline void spread(ll p,ll l,ll r,ll val){
    tree[p].Amax=(r-l+1)*val;
    tree[p].Lmax=tree[p].Rmax=tree[p].Mmax=max(tree[p].Amax,0ll);
    tree[p].cov=1; tree[p].tag=val;
}

inline void pushdown(ll p,ll l,ll r){
    if(tree[p].cov){
        ll mid=(l+r)>>1;
        spread(p<<1,l,mid,tree[p].tag);
        spread(p<<1|1,mid+1,r,tree[p].tag);
        tree[p].tag=tree[p].cov=0;
    }
}

void build(ll p,ll l,ll r){
    if(l==r){
        tree[p].Amax=a[l];
        tree[p].Lmax=tree[p].Rmax=tree[p].Mmax=max(tree[p].Amax,0ll);
        tree[p].cov=0;
        return;
    }
    ll mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    tree[p]=pushup(tree[p<<1],tree[p<<1|1]);
}

void update(ll p,ll l,ll r,ll L,ll R,ll val){
    if(L<=l&&r<=R){
        spread(p,l,r,val);
        return;
    }
    pushdown(p,l,r);
    ll mid=(l+r)>>1;
    if(L<=mid) update(p<<1,l,mid,L,R,val);
    if(R>mid) update(p<<1|1,mid+1,r,L,R,val);
    tree[p]=pushup(tree[p<<1],tree[p<<1|1]);
}

SegmentTree query(ll p,ll l,ll r,ll L,ll R){
    if(L<=l&&r<=R) return tree[p];
    pushdown(p,l,r);
    ll mid=(l+r)>>1;
    SegmentTree x,y;
    if(L<=mid) x=query(p<<1,l,mid,L,R);
    if(R>mid) y=query(p<<1|1,mid+1,r,L,R);
    return pushup(x,y);
}

inline void Update(ll x,ll y,ll val){
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]]) swap(x,y);
        update(1,1,n,id[top[x]],id[x],val);
        x=father[top[x]];
    }
    if(d[x]>d[y]) swap(x,y);
    update(1,1,n,id[x],id[y],val);
}

inline SegmentTree Query(ll x,ll y){
    SegmentTree L,R;
    while(top[x]!=top[y]){
        if(d[top[x]]<d[top[y]]){
            R=pushup(query(1,1,n,id[top[y]],id[y]),R);
            y=father[top[y]];
        }
        else{
            L=pushup(query(1,1,n,id[top[x]],id[x]),L);
            x=father[top[x]];
        }
    }
    if(d[x]>d[y]) L=pushup(query(1,1,n,id[y],id[x]),L);
    else R=pushup(query(1,1,n,id[x],id[y]),R);
    swap(L.Lmax,L.Rmax);
    return pushup(L,R);
}

int main(){
    n=read();
    for(ll i=1; i<=n; i++) w[i]=read();
    for(ll i=1; i<n; i++){
        ll x=read(),y=read();
        addEdge(x,y);
        addEdge(y,x);
    }
    dfs1(1,0); dfs2(1,1);
    build(1,1,n);
    m=read();
    while(m--){
        ll op=read();
        if(op==1){
            ll x=read(),y=read();
            write(Query(x,y).Mmax); putchar('\n');
        }
        else{
            ll x=read(),y=read(),val=read();
            Update(x,y,val);
        }
    }
    return 0;
}
```

---

## 作者：斗神_君莫笑 (赞：0)

本题相当的考验对树剖的理解  
如果像我这种没有学懂的小蒟蒻就会被卡半天……  
要理解query1中的ans1和ans2分别代表着什么  
建议手画一个图去分析ans1和ans2的左右区间的关系  
为什么要反转ans1的左右区间？原因就在这里了  
附上被恶心过的代码   
```cpp
#include<bits/stdc++.h>
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
struct Edge{
	int u,v,nxt;
}e[200010];
int head[100010],cnt;
inline void add(int u,int v){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
struct Node{
	int l,r,sum,lsum,rsum,ans,lazy;
}T[400010];
int n,m,root;
int a[100010],sub_a[100010];
inline void pushup(int p){
	T[p].sum=T[lc].sum+T[rc].sum;
	T[p].lsum=max(T[lc].lsum,T[lc].sum+T[rc].lsum);
	T[p].rsum=max(T[rc].rsum,T[rc].sum+T[lc].rsum);
	T[p].ans=max(max(T[lc].ans,T[rc].ans),T[lc].rsum+T[rc].lsum);
	T[p].lsum=max(T[p].lsum,0);
	T[p].rsum=max(T[p].rsum,0);
	T[p].ans=max(T[p].ans,0);
}
void build(int p,int l,int r){
	T[p].l=l;T[p].r=r;T[p].lazy=0x3f3f3f3f;
	if(l==r){
		T[p].sum=sub_a[l];
		T[p].lsum=T[p].rsum=T[p].ans=max(sub_a[l],0);
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(p);
}
void pushnow(int p,int v){
	T[p].sum=(T[p].r-T[p].l+1)*v;
	T[p].lazy=v;
	if(T[p].sum>0)T[p].ans=T[p].lsum=T[p].rsum=T[p].sum;
	else  T[p].ans=T[p].lsum=T[p].rsum=0;
}
void pushdown(int p){
	if(T[p].lazy!=0x3f3f3f3f){
		pushnow(lc,T[p].lazy);
		pushnow(rc,T[p].lazy);
		T[p].lazy=0x3f3f3f3f;
	}
}
void update(int p,int ql,int qr,int v){
	if(ql<=T[p].l&&T[p].r<=qr){
		pushnow(p,v);return;
	}
	pushdown(p);
	int mid=(T[p].l+T[p].r)>>1;
	if(ql<=mid)update(lc,ql,qr,v);
	if(qr>mid)update(rc,ql,qr,v);
	pushup(p);
}
Node merge(Node l,Node r){
	Node ans;
	ans.lsum=max(ans.lsum,0);
	ans.rsum=max(ans.rsum,0);
	ans.ans=max(ans.ans,0);
	ans.sum=l.sum+r.sum;
	ans.lsum=max(l.lsum,l.sum+r.lsum);
	ans.rsum=max(r.rsum,r.sum+l.rsum);
	ans.ans=max(max(l.ans,r.ans),l.rsum+r.lsum);
	return ans;
}
Node query(int p,int ql,int qr){
	if(ql<=T[p].l&&T[p].r<=qr)
		return T[p];
	pushdown(p);
	int mid=(T[p].l+T[p].r)>>1;
	if(ql<=mid&&mid<qr)
		return merge(query(lc,ql,qr),query(rc,ql,qr));
	if(ql<=mid)return query(lc,ql,qr);
	if(qr>mid)return query(rc,ql,qr);
}
int siz[100010],fa[100010],deep[100010];
void dfs1(int u,int father,int dis){
	fa[u]=father;
	deep[u]=dis;
	siz[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=father){
			dfs1(v,u,dis+1);
			siz[u]+=siz[v];
		}
	}
}
int sub[100010],top[100010],dfn;
void dfs2(int u,int is_heavy){
	if(is_heavy)top[u]=top[fa[u]];
	else top[u]=u;
	sub[u]=++dfn;
	sub_a[dfn]=a[u];
	int max_siz=0,max_son=0;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(siz[v]>max_siz&&v!=fa[u])
			max_siz=siz[v],max_son=v;
	}
	if(max_son)dfs2(max_son,1);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v!=max_son&&v!=fa[u])
			dfs2(v,0);
	}
}

void update1(int x,int y,int v){
	while(top[x]!=top[y]){
		if(deep[top[x]]<deep[top[y]])swap(x,y);
		update(1,sub[top[x]],sub[x],v);
		x=fa[top[x]];
	}
	if(deep[x]>deep[y])swap(x,y);
	update(1,sub[x],sub[y],v);
}  
int query1(int x,int y){
	Node ans1=(Node){0,0,0,0,0,0},ans2=(Node){0,0,0,0,0,0};
	while(top[x]!=top[y]){
		if(deep[top[x]]<deep[top[y]])swap(x,y),swap(ans1,ans2);
		ans1=merge(query(1,sub[top[x]],sub[x]),ans1);
		x=fa[top[x]];
	}
	if(deep[x]>deep[y])swap(x,y),swap(ans1,ans2);
	swap(ans1.lsum,ans1.rsum);
	ans1=merge(ans1,query(1,sub[x],sub[y]));
	return merge(ans1,ans2).ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d",&a[i]);
	for(int i=1;i<n;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dfs1(1,0,1);
	dfs2(1,0);
	build(1,1,n);
	scanf("%d",&m);
	while(m--){
		int t;scanf("%d",&t);
		if(t==1){
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",max(0,query1(x,y)));
		}
		if(t==2){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			update1(x,y,z);
		}
	}
	return 0;
}
```


---

## 作者：_ctz (赞：0)

题解都是树剖的，没有LCT的？

裸的树上链查询最大子段和+链赋值。一开始想的树剖，不过树剖查询时会在两个点之间来回跳，两边信息的合并是有一定思维量的。~~因为懒得想~~就写的LCT。（毕竟LCT能直接把整个链完整的提取出来真的方便啊）

最大子段和这一系列题都是，维护一下以这个区间总和sum，覆盖左端点的最大和ll，覆盖右端点的最大和rr，最大子段和ma。

给出式子，不再赘述：

$\text{ll=max(左儿子ll，左儿子sum+自己的点权+右儿子ll)}$

$\text{rr=max(右儿子rr，右儿子sum+自己的点权+左儿子rr)}$

$\text{ma=max(左儿子ma，右儿子ma，左儿子rr+自己的点权+右儿子ll)}$

链赋值，若赋值为正，ll、rr、ma就改为sum（所有点都选）；为负，则改为0（可以不选）

细节：

1.注意初始化

2.翻转时ll、rr也要交换

3.不要忘了自己的点权！

上代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>

#define maxn 100005
#define inf 0x3f3f3f3f
#define pn putchar('\n')
#define px(x) putchar(x)
#define ps putchar(' ')
#define pd puts("======================")
#define pj puts("++++++++++++++++++++++")

using namespace std;

inline int read(){
	int x=0,y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}
template<typename T>
inline T read(){
	T x=0;
	int y=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return y?-x:x;
}//快读
int n;
struct Link_Cut_Tree{
	int ll[maxn],rr[maxn],ma[maxn],sum[maxn],siz[maxn],son[maxn][2],fa[maxn],rev[maxn],tag[maxn],st[maxn],dat[maxn];
#define son(x,y) son[x][y]
#define whson(x) (son[fa[x]][1]==x)
#define root(x) (son[fa[x]][0]!=x&&son[fa[x]][1]!=x)
	inline void update(int node){
		siz[node]=siz[son(node,0)]+siz[son(node,1)]+1;//维护siz用于更新sum
		ll[node]=max(ll[son(node,0)],sum[son(node,0)]+dat[node]+ll[son(node,1)]);
		rr[node]=max(rr[son(node,1)],sum[son(node,1)]+dat[node]+rr[son(node,0)]);
		ma[node]=max(max(ma[son(node,0)],ma[son(node,1)]),ll[son(node,1)]+dat[node]+rr[son(node,0)]);
		sum[node]=sum[son(node,0)]+sum[son(node,1)]+dat[node];
	}	
	inline void addedge(int s,int f,int wh){
		fa[s]=f,son(f,wh)=s;
	}
	inline void datadown(int node,int d){
		sum[node]=siz[node]*d;
		if(d>0)ll[node]=rr[node]=ma[node]=sum[node];
		else ll[node]=rr[node]=ma[node]=0;
		dat[node]=d,tag[node]=1;
	}
	inline void reverdown(int node){
		rev[node]^=1;
		swap(son(node,0),son(node,1));
		swap(ll[node],rr[node]);//ll、rr也要交换！
	}
	inline void pushdown(int node){
		if(rev[node]){
			if(son(node,0))reverdown(son(node,0));
			if(son(node,1))reverdown(son(node,1));
			rev[node]=0;
		}
		if(tag[node]){
			if(son(node,0))datadown(son(node,0),dat[node]);
			if(son(node,1))datadown(son(node,1),dat[node]);
			tag[node]=0;
		}
	}
	inline void zhuan(int x){
		int f=fa[x],gf=fa[f],wh=whson(x);
		fa[x]=gf;
		if(!root(f))son(gf,whson(f))=x;
		addedge(son(x,wh^1),f,wh);
		addedge(f,x,wh^1);
		update(f),update(x);
	}
	void splay(int x){
		int top=1,y=x;
		st[1]=x;
		while(!root(y))st[++top]=y=fa[y];
		while(top)pushdown(st[top--]);
		while(!root(x)){
			if(!root(fa[x]))
				zhuan(whson(x)^whson(fa[x])?fa[x]:x);
			zhuan(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),son(x,1)=y,update(x);
	}
	void makeroot(int x){
		access(x),splay(x),reverdown(x);
	}
	void link(int x,int y){
		makeroot(x),access(y),splay(y);
		fa[x]=y;
	}
	void change(int x,int y,int d){
		makeroot(x),access(y),splay(y),datadown(y,d);
	}
	void Get(int x,int y){
		makeroot(x),access(y),splay(y);
		printf("%d\n",ma[y]);
	}
	void init(){
		for(register int i=1;i<=n;++i){
			dat[i]=sum[i]=read();
			if(dat[i]>0)ll[i]=rr[i]=ma[i]=dat[i];
			siz[i]=1;//初始化
		}
	} 
}lct;
int main(){
	n=read();	
	lct.init();
	for(register int i=1;i<n;++i){
		int a=read(),b=read();
		lct.link(a,b);
	}
	int m=read();
	while(m--){
		int s=read(),x=read(),y=read();
		if(s==1)lct.Get(x,y);
		else {
			int d=read();
			lct.change(x,y,d);
		}
	}
}

```

这种讲究查询顺序、信息合并的题（我知道的还有SDOI2011染色），用于树剖练手、锻炼思维很好。不过比赛遇到这种题还是写好想又好写的LCT吧。（毕竟细节写错一点就炸了）

---

## 作者：cold_cold (赞：0)

[安利一波博客](https://www.cnblogs.com/cold-cold/p/10056559.html)

此题真是数据结构大毒瘤，一开始我认为这不过是在GSS3的基础上套上一个树链剖分而已

但事实上此题细节极为多，我WA了5遍，这还是在多次在提交前一秒拍出错来的成果

看到别人说splay比线段树好写，写了LCT等等，可惜我都不会，只能用 树剖+线段树 AC

现在开始讲细节

1.线段树的区间推平

我们除了tag数组以外，还要开一个数组记录是否要推平

为什么呢，如果要变的val值为0，那么tag[o]=val，就等于0了，那么我们在pushdown的时候就会误认为不需要展开tag

加入一个数组记录是否要推平就可以避免这样的问题

```cpp
void pushdown(int o,int lnum,int rnum)
{
    if(bian[o])
    {
        sum[o<<1]=tag[o]*lnum;
        lbig[o<<1]=rbig[o<<1]=mbig[o<<1]=max(0,sum[o<<1]);
        tag[o<<1]=tag[o];
        bian[o<<1]=bian[o<<1|1]=1;
        sum[o<<1|1]=tag[o]*rnum;
        lbig[o<<1|1]=rbig[o<<1|1]=mbig[o<<1|1]=max(0,sum[o<<1|1]);
        tag[o<<1|1]=tag[o];
        tag[o]=bian[o]=0;
    }
}

```
2.树剖上区间合并

因为树剖上较为浅的点，ID值较小，所以在线段树中对应着左边

所以我们在合并的时候一定要把新query出来的结构体放在左边与ans合并

```cpp
ansz=MERGE(query(id[top[u]],id[u],1,n,1),ansz);
ansy=MERGE(query(id[top[v]],id[v],1,n,1),ansy);

```
合并的时候要记得左右分开合并

到最后将左边翻转，再合并左右

总体实现如下：
```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
#define lson l,mid,o<<1
#define rson mid+1,r,o<<1|1
inline int read()
{
    int a=0,q=0;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-')  q=1,ch=getchar();
    while(ch>='0'&&ch<='9') a=a*10+ch-48,ch=getchar();
    return q?-a:a;
}
const int N=100100,INF=0x3f3f3f3f;
int n,m,u,v,w,op,cnt,tim,temp,top[N],dep[N],head[N],ww[N],wn[N],siz[N],fa[N],son[N],id[N],tag[N<<2],bian[N<<2],lbig[N<<2],rbig[N<<2],mbig[N<<2],sum[N<<2];
struct EDGE{int nxt,to;}e[N<<1];
void add(int u,int v){e[++cnt]=(EDGE){head[u],v};head[u]=cnt;}
struct QAQ
{
    int lb,rb,mb,s;
    void newone(){lb=0,rb=0,mb=0,s=0;}
};
void pushup(int o)
{
    lbig[o]=max(lbig[o<<1],lbig[o<<1|1]+sum[o<<1]);
    rbig[o]=max(rbig[o<<1|1],rbig[o<<1]+sum[o<<1|1]);
    mbig[o]=max(rbig[o<<1]+lbig[o<<1|1],max(mbig[o<<1],mbig[o<<1|1]));
    sum[o]=sum[o<<1]+sum[o<<1|1];
}
void pushdown(int o,int lnum,int rnum)
{
    if(bian[o])
    {
        sum[o<<1]=tag[o]*lnum;
        lbig[o<<1]=rbig[o<<1]=mbig[o<<1]=max(0,sum[o<<1]);
        tag[o<<1]=tag[o];
        bian[o<<1]=bian[o<<1|1]=1;
        sum[o<<1|1]=tag[o]*rnum;
        lbig[o<<1|1]=rbig[o<<1|1]=mbig[o<<1|1]=max(0,sum[o<<1|1]);
        tag[o<<1|1]=tag[o];
        tag[o]=bian[o]=0;
    }
}
QAQ MERGE(QAQ xx,QAQ yy)
{
    QAQ temp;
    temp.lb=max(xx.lb,yy.lb+xx.s);
    temp.rb=max(yy.rb,xx.rb+yy.s);
    temp.mb=max(xx.rb+yy.lb,max(xx.mb,yy.mb));
    temp.s=xx.s+yy.s;
    return temp;
}
void build(int l,int r,int o)
{
    if(l==r){sum[o]=wn[l];lbig[o]=rbig[o]=mbig[o]=max(sum[o],0);return;}
    int mid=(l+r)>>1;
    build(lson);build(rson);
    pushup(o);
}
QAQ query(int L,int R,int l,int r,int o)
{
    if(L>R) return (QAQ){0,0,0,0}; 
    if(L<=l&&r<=R){return (QAQ){lbig[o],rbig[o],mbig[o],sum[o]};}
    int mid=(l+r)>>1,lb,rb,mb,s=0,e1=0,e2=0;
    pushdown(o,mid-l+1,r-mid);
    QAQ temp1,temp2;
    if(L<=mid) e1=1,temp1=query(L,R,lson);
    if(R> mid) e2=1,temp2=query(L,R,rson);
    if(e1&&e2)
    {
        lb=max(temp1.lb,temp2.lb+temp1.s);
        rb=max(temp2.rb,temp1.rb+temp2.s);
        mb=max(temp1.rb+temp2.lb,max(temp1.mb,temp2.mb));
        s=temp1.s+temp2.s;
    }
    else if(e1)
    {
        lb=temp1.lb;
        rb=temp1.rb;
        mb=temp1.mb;
        s=temp1.s;
    }
    else
    {
        lb=temp2.lb;
        rb=temp2.rb;
        mb=temp2.mb;
        s=temp2.s;
    }
    return (QAQ){lb,rb,mb,s};
}
void update(int L,int R,int val,int l,int r,int o)
{
    if(L<=l&&r<=R)
    {
        sum[o]=(r-l+1)*val;
        lbig[o]=rbig[o]=mbig[o]=max(0,sum[o]);
        tag[o]=val;bian[o]=1;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(o,mid-l+1,r-mid);
    if(L<=mid) update(L,R,val,lson);
    if(R> mid) update(L,R,val,rson);
    pushup(o);
}
void dfs1(int u,int ff)
{
    fa[u]=ff;dep[u]=dep[ff]+1;siz[u]=1;
    int maxson=0;
    for(int i=head[u],v=e[i].to;i;i=e[i].nxt,v=e[i].to) if(v!=ff)
    {
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[v]>maxson) maxson=siz[v],son[u]=v;
    }
}
void dfs2(int u,int topf)
{
    id[u]=++tim;top[u]=topf;wn[tim]=ww[u];
    if(!son[u]) return;
    dfs2(son[u],topf);
    for(int i=head[u],v=e[i].to;i;i=e[i].nxt,v=e[i].to) if(v!=fa[u]&&v!=son[u])
        dfs2(v,v);
}
void update_tree(int u,int v,int val)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        update(id[top[u]],id[u],val,1,n,1);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    update(id[u],id[v],val,1,n,1);
}
QAQ query_tree(int u,int v)
{
    QAQ ansz,ansy;ansz.newone(),ansy.newone();
    while(top[u]!=top[v])
    {
        if(dep[top[u]]>=dep[top[v]])
        {
            ansz=MERGE(query(id[top[u]],id[u],1,n,1),ansz);
            u=fa[top[u]];
        }
        else
        {
            ansy=MERGE(query(id[top[v]],id[v],1,n,1),ansy);
            v=fa[top[v]];
        }
    }
    if(dep[u]<=dep[v]) ansy=MERGE(query(id[u],id[v],1,n,1),ansy);
    else ansz=MERGE(query(id[v],id[u],1,n,1),ansz);
    swap(ansz.lb,ansz.rb);
    return MERGE(ansz,ansy);
}
int main()
{
//    freopen("a.in","r",stdin);
//    freopen("b.out","w",stdout);
    n=read();
    for(int i=1;i<=n;i++) ww[i]=read();
    for(int i=1;i<n;i++)
    {
        u=read(),v=read();
        add(u,v);add(v,u);
    }
    dfs1(1,1);dfs2(1,1);
    build(1,n,1);
//    for(int i=1;i<=n;i++) printf("%d ",query(i,i,1,n,1).mb);
//    printf("\n");
    m=read();
    while(m--)
    {
       op=read();
       if(op==1)
       {
           u=read(),v=read();
           printf("%d\n",query_tree(u,v).mb);
       }
       else
       {
           u=read(),v=read(),w=read();
           update_tree(u,v,w);
       }
    }
    return 0;
}
/*
 
*/

```



---

## 作者：___new2zy___ (赞：0)

### 题解 SP6779【GSS7 - Can you answer these queries VII】

题目传送门：

https://www.luogu.org/problemnew/show/SP6779

彻彻底底的一道神仙题。。。

我怕不是做数据结构毒瘤题做上瘾了。。。~~（逃~~

贡献了半页提交记录的我来发一篇题解~~~

提示：如果你还不会求最大子段和，请右转[GSS3，线段树求最大子段和裸题](https://www.luogu.org/problemnew/show/SP1716)

================================================================

先来扯一些没用的。。。

上个月刚学完树剖，就发现树剖贼好用

于是乎找到了一大堆的树剖题目开始切。。。

由于要复赛了，想看看别的东西了。。。我菜到分块还不会。。。

所以就想把这题作为我写树剖题的最后一道压轴题

那天晚上来切这道题，发现好像很简单。。。（雾）

其实就是个树剖+线段树维护树上最大子段和而已，只是把 [GSS3](https://www.luogu.org/problemnew/show/SP1716)
的操作变成区间操作之后放到了树上而已

可能是我想简单了。。。结果这题调了5天没调完。。。半夜2点才睡的我精神恍惚

前天终于调完了，也不负我的辛苦，A了之后发现没开O2稳在最优解第三名

也只是统计到2018年9月25日而已了。。。

~~（没到rk1可能还是人丑常数大的原因吧。。。）~~

咳咳。。。还是说正事吧。。。这些都不重要

### 做法：树链剖分+线段树

正如上面所说，其实就是把GSS3的操作变成区间操作之后搬到了树上，本质不变

但是要注意一件事，就是**在链上查询的时候要记录两个值**，一面记录x所在的链,一面记录y所在的链，**最后要注意反转一下x的lmax和rmax**

线段树上更新最大子段和再来复习一下：（把l和r合并到x上）

```cpp
inline void Merge(SeT &x,SeT l,SeT r)
{
    x.sum=l.sum+r.sum;
    x.lmax=max(l.lmax,l.sum+r.lmax);
    x.rmax=max(r.rmax,r.sum+l.rmax);
    x.maxx=max(max(l.maxx,r.maxx),l.rmax+r.lmax);
}
```

然后线段树区间修改之类的就不用我说了吧。。。打个标记就行了

其实都是板子，直接套就好了（雾）

现在看我写的这么顺畅，其实自己做的时候脑袋里是一碗豆腐脑。。。


个人习惯比较不好，总是喜欢把东西写在结构体里面

（还有就是。。。大括号换行~~）（逃~~

请不要在意那些奇怪的变量名（比如说dnf和from之类的。。。）

下面放一下奇丑无比但是写了5天的code

PS：代码里也有解释哦~

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define l_son p<<1
#define r_son p<<1|1
#define re register
using namespace std;
inline int read()
{
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;}
const int maxn=100003;
struct Edge
{
    int from,to;
}p[maxn<<1];
struct SeT
{
    int sum,lmax,rmax,maxx,f,add;
    inline void cover(int k,int len)//修改节点的值为k，节点维护长度为len
        {
            f=1,add=k,sum=len*k;
            lmax=rmax=maxx=max(sum,0);//记得和0取max
        }
    inline void rev()//反转节点信息
        {
            swap(lmax,rmax);
        }
}T[maxn<<2],Clean;
int n,Q,cnt,tot,head[maxn],dnf[maxn],A[maxn],val[maxn];
int depth[maxn],fa[maxn],top[maxn],heavy[maxn],size[maxn];
inline void add_edge(int x,int y)//加边
{
    cnt++;
    p[cnt].from=head[x];
    head[x]=cnt;
    p[cnt].to=y;
}
inline int dfs1(int x,int f)//树剖dfs1:预处理fa,size,depth,heavy数组
{
    fa[x]=f,size[x]=1,depth[x]=depth[f]+1;
    for(int i=head[x];i;i=p[i].from)
    	{
    		int y=p[i].to;
    		if(y==f)continue;
    		dfs1(y,x);
    		size[x]+=size[y];
    		if(size[y]>size[heavy[x]])
    			heavy[x]=y;
        }
}
inline void dfs2(int x,int t)//树剖dfs2:预处理top,dnf,A数组
{
    top[x]=t,dnf[x]=++tot,A[tot]=val[x];
    if(!heavy[x])return ;
    dfs2(heavy[x],t);
    for(int i=head[x];i;i=p[i].from)
        {
            int y=p[i].to;
            if(y==fa[x]||y==heavy[x])continue;
            dfs2(y,y);
        }
}
inline void Merge(SeT &x,SeT l,SeT r)//合并l和r到x上
{
    x.sum=l.sum+r.sum;
    x.lmax=max(l.lmax,l.sum+r.lmax);
    x.rmax=max(r.rmax,r.sum+l.rmax);
    x.maxx=max(max(l.maxx,r.maxx),l.rmax+r.lmax);
}
inline void maintian(int p)//维护节点信息
{
    Merge(T[p],T[l_son],T[r_son]);
}
inline void pushdown(int p,int len)//标记下传
{
    if(T[p].f)
        {
            T[l_son].cover(T[p].add,(len-(len>>1)));
            T[r_son].cover(T[p].add,(len>>1));
            T[p].f=T[p].add=0;
        }
}
inline void Build(int p,int l,int r)//建树
{
    if(l==r)
        {
            T[p].sum=A[l];
            T[p].lmax=T[p].rmax=T[p].maxx=max(T[p].sum,0);
            return ;
        }
    int mid=(l+r)>>1;
    Build(l_son,l,mid),Build(r_son,mid+1,r);
    maintian(p);
}
inline void change(int p,int l,int r,int x,int y,int k)//区间覆盖
{
    if(x<=l&&r<=y)
        {
            T[p].cover(k,r-l+1);
            return ;
        }
    pushdown(p,r-l+1);
    int mid=(l+r)>>1;
    if(y<=mid)change(l_son,l,mid,x,y,k);
    else if(x>mid)change(r_son,mid+1,r,x,y,k);
    else change(l_son,l,mid,x,mid,k),change(r_son,mid+1,r,mid+1,y,k);
    maintian(p);
}
inline SeT query(int p,int l,int r,int x,int y)//区间查询最大子段和
{
    if(x<=l&&r<=y)return T[p];
    pushdown(p,r-l+1);
    int mid=(l+r)>>1;
    if(y<=mid)return query(l_son,l,mid,x,y);//左子树
    else if(x>mid)return query(r_son,mid+1,r,x,y);//右子树
    else//跨越，需要合并左右子树信息
        {
            SeT L=query(l_son,l,mid,x,mid),R=query(r_son,mid+1,r,mid+1,y),ans;
            Merge(ans,L,R);
            return ans;
        }
}
inline void Tree_path_change(int x,int y,int k)//树上路径x->y中的点权覆盖为k
{
    while(top[x]!=top[y])
        {
            if(depth[top[x]]<depth[top[y]])swap(x,y);
            change(1,1,n,dnf[top[x]],dnf[x],k);
            x=fa[top[x]];
        }
    if(depth[x]>depth[y])swap(x,y);
    change(1,1,n,dnf[x],dnf[y],k);
}
inline int Tree_path_ask(int x,int y)//查询树上路径x->y的最大子段和
{
    SeT L=Clean,R=Clean,ans,tmp;
    while(top[x]!=top[y])
        {
            if(depth[top[x]]>=depth[top[y]])//x链上
                {
                    tmp=query(1,1,n,dnf[top[x]],dnf[x]);
                    Merge(L,tmp,L);
                    x=fa[top[x]];
                }
            else//y链上
                {
                    tmp=query(1,1,n,dnf[top[y]],dnf[y]);
                    Merge(R,tmp,R);
                    y=fa[top[y]];
                }
        }
    if(dnf[x]>=dnf[y])
        {
            tmp=query(1,1,n,dnf[y],dnf[x]);
            Merge(L,tmp,L);
        }
    else
        {
            tmp=query(1,1,n,dnf[x],dnf[y]);
            Merge(R,tmp,R);
        }
    L.rev();//反转一下左边的链答案
    Merge(ans,L,R);
    return ans.maxx;
}
int main() 
{
    n=read();
    for(re int i=1;i<=n;i++)
           val[i]=read();
    for(re int i=1;i<n;i++)
       	{
           	int x=read(),y=read();
           	add_edge(x,y);
           	add_edge(y,x);
       	}
    dfs1(1,0),dfs2(1,1);//树剖预处理
    Build(1,1,n);//建立线段树
    Q=read();
  	while(Q--)
       	{
    	    int flag=read();
    	    if(flag==1)//树上路经查询最大子段和
    	       	{
    	       		int x=read(),y=read();
    	          	 printf("%d\n",Tree_path_ask(x,y));
    	       	}
    	    else if(flag==2)//树上路径覆盖
    	   		{
    	       		int x=read(),y=read(),k=read();
    	        	   Tree_path_change(x,y,k);
    	       	}
       	}
    return 0;
}

```

SPOJ的GSS系列都是数据结构的好~~（毒瘤）~~题啊

希望大家好好做，而不是直接复制粘贴code

可能等我有时间了我会做一下GSS系列其他的题目吧，最后总结在一起放出来

真的是毒瘤的一题啊。。。不过也不白费我的5天

可能到这里也就没什么了吧。。。

最后，感谢你的阅读！

最后的最后~~无耻的~~推一波我的blog：

https://www.luogu.org/blog/new2zy/

拜拜~~~



---

## 作者：StudyingFather (赞：0)

如果是序列问题的话，和 GSS3 几乎没啥区别（区间修改的话多写个 pushdown 就没了）。

然而这题很恶心地搬到了树上，多的不仅仅是树剖...

显然做这题的已经事先做完了 GSS 系列的前几道题，所以这里对我们要维护的信息不再赘述。（如果还不清楚的话，可以看 [我的博客](https://studyingfather.com/archives/2817)）

修改操作没啥好说的，重点是查询操作。

序列问题上的查询操作，由于遍历线段树时采用先序遍历，答案是自左向右一段段地合并，所以没有太大问题。

但树上的查询操作则是从两端（为了方便起见姑且叫左端和右端）开始，向中间合并，因此合并的顺序变得非常重要。

我们每次跳重链的时候，都要根据重链的归属（归属左边或是右边）将它的信息合并到相应的链上（一定要注意合并的方向是深度由深到浅）。

经过了几次跳重链的操作后，两个端点终于到了同一条重链。

现在我们拥有了两个链的信息，可以把它们直接合并来得到答案了吗？

并不是。左边的链方向是深度从深到浅，右边的链也是。我们需要反转其中一条链的方向，才能正确对接这两条链。

实现起来坑点真的不少...

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1000000
using namespace std;
vector<int> e[100005];
int id[100005],siz[100005],son[100005],fa[100005],top[100005],dep[100005],cnt;
int x[100005],a[100005],n,q;
struct seg
{
 int ans,sum,pre,post,tag;
 seg operator+(const seg&a)const
 {
  seg res;
  res.sum=sum+a.sum;
  res.ans=max(ans,max(a.ans,post+a.pre));
  res.pre=max(pre,sum+a.pre);
  res.post=max(a.post,a.sum+post);
  res.tag=0;
  return res;
 }
}s[400005];
void dfs1(int u,int f)
{
 fa[u]=f;
 dep[u]=dep[f]+1;
 siz[u]=1;
 for(auto v:e[u])
  if(v!=f)
  {
   dfs1(v,u);
   siz[u]+=siz[v];
   if(siz[v]>siz[son[u]])
    son[u]=v;
  }
}
void dfs2(int u,int t)
{
 top[u]=t;
 id[u]=++cnt;
 a[cnt]=x[u];
 if(son[u])dfs2(son[u],t);
 for(auto v:e[u])
  if(v!=son[u]&&v!=fa[u])dfs2(v,v);
}
void pushup(int root)
{
 int tag=s[root].tag;
 s[root]=s[root<<1]+s[root<<1|1];
 s[root].tag=tag;
}
void pushdown(int root,int l,int r)
{
 if(s[root].tag!=INF)
 {
  int mid=(l+r)>>1,x=s[root].tag,ls=root<<1,rs=root<<1|1;
  s[ls].tag=s[rs].tag=x;
  s[ls].sum=(mid-l+1)*x;
  s[ls].pre=s[ls].post=s[ls].ans=max((mid-l+1)*x,0);
  s[rs].sum=(r-mid)*x;
  s[rs].pre=s[rs].post=s[rs].ans=max((r-mid)*x,0);
  s[root].tag=INF;
 }
}
void build(int root,int l,int r)
{
 if(l==r)
 {
  if(a[l]>=0)s[root]={a[l],a[l],a[l],a[l],INF};
  else s[root]={0,a[l],0,0,INF};
  return;
 }
 int mid=(l+r)>>1;
 build(root<<1,l,mid);
 build(root<<1|1,mid+1,r);
 s[root].tag=INF;
 pushup(root);
}
seg query(int root,int cl,int cr,int l,int r)
{
 if(l<=cl&&cr<=r)return s[root];
 pushdown(root,cl,cr);
 int mid=(cl+cr)>>1;
 if(l<=mid&&mid<r)
  return query(root<<1,cl,mid,l,r)+query(root<<1|1,mid+1,cr,l,r);
 else if(l<=mid)
  return query(root<<1,cl,mid,l,r);
 else
  return query(root<<1|1,mid+1,cr,l,r);
}
void update(int root,int cl,int cr,int l,int r,int x)
{
 if(r<cl||cr<l)return;
 if(l<=cl&&cr<=r)
 {
  s[root].sum=(cr-cl+1)*x;
  s[root].tag=x;
  s[root].pre=s[root].post=s[root].ans=max(0,(cr-cl+1)*x);
  return;
 }
 pushdown(root,cl,cr);
 int mid=(cl+cr)>>1;
 update(root<<1,cl,mid,l,r,x);
 update(root<<1|1,mid+1,cr,l,r,x);
 pushup(root);
}
seg query_chain(int x,int y)
{
 seg lans={0,0,0,0,0},rans={0,0,0,0,0};
 while(top[x]!=top[y])
 {
  if(dep[top[x]]<dep[top[y]])//合并到右边的链
  {
   rans=query(1,1,n,id[top[y]],id[y])+rans;//注意方向由深到浅
   y=fa[top[y]];
  }
  else//合并到左边的链
  {
   lans=query(1,1,n,id[top[x]],id[x])+lans;
   x=fa[top[x]];
  }
 }
 if(dep[x]<dep[y])//合并到右边的链，注意合并方向
  rans=query(1,1,n,id[x],id[y])+rans;
 else//同上
  lans=query(1,1,n,id[y],id[x])+lans;
 swap(lans.pre,lans.post);//反转其中一条链
 return lans+rans;
}
void update_chain(int x,int y,int z)
{
 while(top[x]!=top[y])
 {
  if(dep[top[x]]>dep[top[y]])swap(x,y);
  update(1,1,n,id[top[y]],id[y],z);
  y=fa[top[y]];
 }
 if(dep[x]>dep[y])swap(x,y);
 update(1,1,n,id[x],id[y],z);
}
int main()
{
 ios::sync_with_stdio(false);
 cin>>n;
 for(int i=1;i<=n;i++)
  cin>>x[i];
 for(int i=1;i<n;i++)
 {
  int u,v;
  cin>>u>>v;
  e[u].push_back(v);
  e[v].push_back(u);
 }
 dfs1(1,0);
 dfs2(1,1);
 build(1,1,n);
 cin>>q;
 while(q--)
 {
  int op;
  cin>>op;
  if(op==1)
  {
   int a,b;
   cin>>a>>b;
   cout<<query_chain(a,b).ans<<endl;
  }
  else
  {
   int a,b,c;
   cin>>a>>b>>c;
   update_chain(a,b,c);
  }
 }
 return 0;
}
```

---

