# QTREE - Query on a tree

## 题目描述

You are given a tree (an acyclic undirected connected graph) with **N** nodes, and edges numbered 1, 2, 3...**N**-1.

We will ask you to perfrom some instructions of the following form:

- **CHANGE i ti** : change the cost of the i-th edge to ti  
   or
- **QUERY a b** : ask for the maximum edge cost on the path from node a to node b

## 样例 #1

### 输入

```
1

3
1 2 1
2 3 2
QUERY 1 2
CHANGE 1 3
QUERY 1 2
DONE```

### 输出

```
1
3```

# 题解

## 作者：Siyuan (赞：13)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[SPOJ 375](https://www.spoj.com/problems/QTREE/)

给定一棵 $n$ 个节点的树，边按照输入顺序编号为 $1\sim n-1$，每条边都有一个权值 $c_i$ 需要对这棵树进行若干次操作，操作分为 $2$ 种：

- `CHANGE i t`：将第 $i$ 条边的权值 $c_i$ 修改为 $t$
- `QUERY a b`：询问从节点 $a$ 到 $b$ 的路径上的边权最大值。

询问以 `DONE` 结束，有 $T$ 组数据。

数据范围：$T\le 20$，$n\le10^4$，$c_i,t\le 10^6$

------

## Solution

对于这类树的题目，我们首先可以想到用**树链剖分**维护。而这题需要维护的边的信息，那么我们可以把每条边的信息放在较深的节点上，就转化成了维护点的信息了。

但是这样做需要注意一个问题：每次查询时，$\texttt{LCA}$ 的节点维护的信息是它上方的边，因此这个点不能被查询到。如何解决？我们根据树剖的性质可以发现以下方法：记 $x$ 的 $\texttt{DFS}$ 序为 $d_x$，那么最后查询 $u,v$ 的信息时（这里令 $u$ 的深度比 $v$ 浅），我们可以发现 $u$ 一定是 $\texttt{LCA}$，所以只要查询 $d_u+1,d_v$ 就可以避开 $\texttt{LCA}$ 了。

**时间复杂度**：$O(n\log^2 n)$（这里认为操作次数和 $n$ 同阶）

------

## Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson rt<<1
#define rson rt<<1|1
inline char nc() {
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template <class Tp> inline void read(register Tp &s) {
    s=0;
    register bool neg=0;
    register char c=nc();
    for(;c<'0'||c>'9';c=nc()) neg|=(c=='-');
    for(;c>='0'&&c<='9';s=s*10+(c^48),c=nc());
    s=(neg?-s:s);
}

const int N=1e5+5,M=2e5+5;
int n,idx,dfn[N],seq[N],U[N],V[N],W[N],val[N],fa[N],dep[N],top[N],sz[N],hvy[N];
int tot,lnk[N],ter[M],nxt[M],wei[M],seg[N<<2];

void add(int u,int v,int w) {
    ter[++tot]=v,wei[tot]=w,nxt[tot]=lnk[u],lnk[u]=tot;
}
void dfs1(int u,int f) {
    fa[u]=f,dep[u]=dep[f]+1,sz[u]=1,hvy[u]=top[u]=0;
    for(int i=lnk[u];i;i=nxt[i]) {
        int v=ter[i];
        if(v==f) continue;
        val[v]=wei[i];
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[hvy[u]]<sz[v]) hvy[u]=v;
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
void pushup(int rt) {
    seg[rt]=std::max(seg[lson],seg[rson]);
}
void build(int rt,int l,int r) {
    if(l==r) {
        seg[rt]=val[seq[l]];
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(rt);
}
void modify(int x,int rt,int l,int r,int val) {
    if(l==r) {
        seg[rt]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) modify(x,lson,l,mid,val);
    else modify(x,rson,mid+1,r,val);
    pushup(rt);
}
int query(int x,int y,int rt,int l,int r) {
    if(x>y) return 0;
    if(x<=l&&r<=y) return seg[rt];
    int mid=(l+r)>>1,res=0;
    if(x<=mid) res=std::max(res,query(x,y,lson,l,mid));
    if(mid<y) res=std::max(res,query(x,y,rson,mid+1,r));
    return res;
}
int chainQuery(int u,int v) {
    if(u==v) return 0;
    int res=0;
    for(int fu=top[u],fv=top[v];fu^fv;u=fa[fu],fu=top[u]) {
        if(dep[fu]<dep[fv]) std::swap(u,v),std::swap(fu,fv);
        res=std::max(res,query(dfn[fu],dfn[u],1,1,n));
    }
    if(dep[u]>dep[v]) std::swap(u,v);
    res=std::max(res,query(dfn[u]+1,dfn[v],1,1,n));
    return res;
}
int main() {
    int T;
    for(read(T);T--;) {
        read(n);
        idx=tot=0,memset(lnk,0,sizeof(lnk));
        for(int i=1;i<n;++i) {
            int u,v,w;
            read(u),read(v),read(w);
            add(u,v,w),add(v,u,w);
            U[i]=u,V[i]=v,W[i]=w;
        }
        dfs1(1,0),dfs2(1,1),build(1,1,n);
        while(1) {
            char c=nc();
            while(c<'A'||c>'Z') c=nc();
            if(c=='D') break;
            int x,y;
            read(x),read(y);
            if(c=='C') {
                int u=U[x],v=V[x];
                if(fa[v]==u) std::swap(u,v);
                modify(dfn[u],1,1,n,y);
            } else {
                printf("%d\n",chainQuery(x,y));
            }
        }
    }
    return 0;
}
```



---

## 作者：VenusM1nT (赞：7)

树链剖分。咕咕这题有 $\text{BUG}$，只能使用 $\text{C}$ 语言，所以我先讲一下这道题的做法，然后再讲如何 $\text{C++}$ 转 $\text{C}$。

这道题涉及树上的区间查询最大值和单点查询，首先有一个问题，给定的是边权，而树链剖分维护的是点权，所以我们要把边权转换到深度更深的一个点上，然后在退出 $top[u]\not=top[v]$ 这个循环时将 $dfn[u]$ 加上 $1$ ，即忽略掉 $\text{LCA}$，因为 $\text{LCA}$ 存储的信息是上一条边，那条边明显是不在路径上的，忽略掉即可。

然后就是很简单的单点修改，线段树数组记录区间最大值即可。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1],w[MAXN<<1];
int n,a[MAXN],t[MAXN<<2],fr[MAXN],tx[MAXN];
int dfn[MAXN],Index,faz[MAXN],siz[MAXN],son[MAXN],dep[MAXN],top[MAXN],rk[MAXN];
char ch[15];
void AddEdge(int u,int v,int c)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
    w[cnt]=c;
}
void Dfs1(int u)
{
    siz[u]=1;
    son[u]=0;
    for(int i=fst[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==faz[u]) continue;
        dep[v]=dep[u]+1;
        faz[v]=u;
        a[v]=w[i];
        Dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
void Dfs2(int u,int rt)
{
    dfn[u]=++Index;
    rk[Index]=u;
    top[u]=rt;
    if(son[u]) Dfs2(son[u],rt);
    for(int i=fst[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==faz[u] || v==son[u]) continue;
        Dfs2(v,v);
    }
}
void PushUp(int rt)
{
    t[rt]=max(t[rt<<1],t[rt<<1|1]);
}
void BuildSegmentTree(int rt,int l,int r)
{
    if(l==r)
    {
        t[rt]=a[rk[l]];
        return;
    }
    int mid=l+r>>1;
    BuildSegmentTree(rt<<1,l,mid);
    BuildSegmentTree(rt<<1|1,mid+1,r);
    PushUp(rt);
}
void Modify(int rt,int l,int r,int pos,int val)
{
    if(l==r)
    {
        t[rt]=val;
        return;
    }
    int mid=l+r>>1;
    if(pos<=mid) Modify(rt<<1,l,mid,pos,val);
    else Modify(rt<<1|1,mid+1,r,pos,val);
    PushUp(rt);
}
int Query(int rt,int l,int r,int tl,int tr)
{
    if(tl<=l && r<=tr) return t[rt];
    int mid=l+r>>1;
    int res=0;
    if(tl<=mid) res=max(res,Query(rt<<1,l,mid,tl,tr));
    if(tr>mid) res=max(res,Query(rt<<1|1,mid+1,r,tl,tr));
    return res;
}
int QueryOnTree(int u,int v)
{
    int res=0;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        res=max(res,Query(1,1,n,dfn[top[u]],dfn[u]));
        u=faz[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    res=max(res,Query(1,1,n,dfn[u]+1,dfn[v]));
    return res;
}
int main()
{
	int Time;
	scanf("%d",&Time);
	while(Time--)
	{
		cnt=Index=0;
		memset(fst,0,sizeof(fst));
		scanf("%d",&n);
		for(int i=1;i<n;i++)
		{
 	       int x,y;
 	       int z;
			scanf("%d %d %intd",&x,&y,&z);
			fr[i]=x;
			tx[i]=y;
			AddEdge(x,y,z);
			AddEdge(y,x,z);
		}
    	Dfs1(1);
    	Dfs2(1,1);
    	BuildSegmentTree(1,1,n);
    	while(1)
    	{
    	    scanf("%s",ch+1);
    	    if(ch[1]=='D') break;
    	    else
			{
				int x,y;
    	        scanf("%d %d",&x,&y);
	            if(ch[1]=='Q') printf("%d\n",QueryOnTree(x,y));
	            else
	            {
	                int t=dep[fr[x]]>dep[tx[x]]?fr[x]:tx[x];
	                Modify(1,1,n,dfn[t],y);
	            }
	        }
	    }
	}
    return 0;
}
```

然而到这里还没有结束，因为有 $\text{BUG}$，所以我们还要将它转成 $\text{C}$ 语言。注意点有以下：

 1. 不能用 `bits/stdc++.h` 要将它拆开来。
 2. 不能用 `c` 开头的头文件，要改成 `.h` 结尾的头文件，如 `cstdio` $\rightarrow$ `stdio.h` 。
 3. 不能用 `algorithm` 库，也不能用 `std` 名字空间，意味着所有 `max` 和 `swap` 都要手打，但是用引用好像会出一点 $\text{BUG}$，所以我的 `swap` 是直接拆开来模拟的。
 4. 宏定义应该还是可以用的。
 5. 用 `Dev-C++` 编译 `.c` 后缀的文件的话应该还要换编译器，很不方便，建议使用 `洛谷IDE`。
 
最后的代码如下。

```c
#include<stdio.h>
#include<string.h>
#define MAXN 100005
int cnt,fst[MAXN],nxt[MAXN<<1],to[MAXN<<1],w[MAXN<<1];
int n,a[MAXN],t[MAXN<<2],fr[MAXN],tx[MAXN];
int dfn[MAXN],Index,faz[MAXN],siz[MAXN],son[MAXN],dep[MAXN],top[MAXN],rk[MAXN];
char ch[15];
void AddEdge(int u,int v,int c)
{
    to[++cnt]=v;
    nxt[cnt]=fst[u];
    fst[u]=cnt;
    w[cnt]=c;
}
int max(int x,int y)
{
    return x>y?x:y;
}
void Dfs1(int u)
{
    siz[u]=1;
    son[u]=0;
    for(int i=fst[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==faz[u]) continue;
        dep[v]=dep[u]+1;
        faz[v]=u;
        a[v]=w[i];
        Dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[son[u]]) son[u]=v;
    }
}
void Dfs2(int u,int rt)
{
    dfn[u]=++Index;
    rk[Index]=u;
    top[u]=rt;
    if(son[u]) Dfs2(son[u],rt);
    for(int i=fst[u];i;i=nxt[i])
    {
        int v=to[i];
        if(v==faz[u] || v==son[u]) continue;
        Dfs2(v,v);
    }
}
void PushUp(int rt)
{
    t[rt]=max(t[rt<<1],t[rt<<1|1]);
}
void BuildSegmentTree(int rt,int l,int r)
{
    if(l==r)
    {
        t[rt]=a[rk[l]];
        return;
    }
    int mid=(l+r)>>1;
    BuildSegmentTree(rt<<1,l,mid);
    BuildSegmentTree(rt<<1|1,mid+1,r);
    PushUp(rt);
}
void Modify(int rt,int l,int r,int pos,int val)
{
    if(l==r)
    {
        t[rt]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid) Modify(rt<<1,l,mid,pos,val);
    else Modify(rt<<1|1,mid+1,r,pos,val);
    PushUp(rt);
}
int Query(int rt,int l,int r,int tl,int tr)
{
    if(tl<=l && r<=tr) return t[rt];
    int mid=(l+r)>>1,res=0;
    if(tl<=mid) res=max(res,Query(rt<<1,l,mid,tl,tr));
    if(tr>mid) res=max(res,Query(rt<<1|1,mid+1,r,tl,tr));
    return res;
}
int QueryOnTree(int u,int v)
{
    int res=-2e9;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]])
        {
            int t=u;
            u=v;
            v=t;
        }
        res=max(res,Query(1,1,n,dfn[top[u]],dfn[u]));
        u=faz[top[u]];
    }
    if(dep[u]>dep[v])
    {
        int t=u;
        u=v;
        v=t;
    }
    res=max(res,Query(1,1,n,dfn[u]+1,dfn[v]));
    return res;
}
int main()
{
    int Time;
    scanf("%d",&Time);
    while(Time--)
    {
        cnt=Index=0;
        memset(fst,0,sizeof(fst));
        scanf("%d",&n);
        for(int i=1;i<n;i++)
        {
            int x,y,z;
            scanf("%d %d %d",&x,&y,&z);
            fr[i]=x;
            tx[i]=y;
            AddEdge(x,y,z);
            AddEdge(y,x,z);
        }
        Dfs1(1);
        Dfs2(1,1);
        BuildSegmentTree(1,1,n);
        while(1)
        {
            scanf("%s",ch+1);
            if(ch[1]=='D') break;
            else
            {
                int x,y;
                scanf("%d %d",&x,&y);
                if(ch[1]=='Q') printf("%d\n",QueryOnTree(x,y));
                else
                {
                    x=dep[fr[x]]>dep[tx[x]]?fr[x]:tx[x];
                    Modify(1,1,n,dfn[x],y);
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：Blunt_Feeling (赞：5)

## SP375 QTREE - Query on a tree 题解

- ## $\texttt{update 2021/05/16}$ 嵌入了 bilibili 视频，更正代码中的错误

>观诸题解，无一甚为中意（无贬低之意）。或未尽其思，或码风诡谲，或代码冗长。虽吾技未佳，亦钻之久矣。今书此题解，以示后人，兼抒吾志。 ——自序（~~语文课代表狂喜~~）

经过长达六个小时的研究，我调出了一份比较清晰的树链剖分的代码。

首先理解一些关键词汇的意思：
```
重儿子：一个节点的子节点中，子树节点数最大的那个儿子节点
轻儿子：除重儿子外，其他的子节点
重边：节点与其重儿子的连边
轻边：节点与其轻儿子的连边
重链：由重边连成的一条链
```

实现原理：把边权移到点权，再把边划分成重边和轻边后，每一条重链中重儿子的编号就连在了一起。于是就可以用线段树的区间最值查询，得到一条重链上的点权最大值。再把各个重链上的最大值合在一起，就能得到正确的答案。

如果你仔细阅读我的代码，可以发现我并没有线段树的建树操作。取而代之地，我用单点修改线段树中每一个节点的值来完成建树操作。这样写可以少开一到两个数组，使代码更加清晰。在边权移至点权的过程中，这里采用了把边权移至该边的儿子节点的写法。

代码中加入了笔者自认为详尽的注释，供读者参考。变量名、函数名可能会与其他的一些题解重复，但是这些变量名、函数名取得确实有独到之处。

十分推荐大家去看一看[【算法讲堂】【电子科技大学】【ACM】树链剖分](https://www.bilibili.com/video/BV1hW411w7bM)，我也从这个视频中得到了许多启发，~~而且爽快地给了三连~~。

![](bilibili:BV1hW411w7bM)

### Code
```cpp
//by Blunt_Feeling 洛谷UID：219866
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=10050;
struct Edge{
    int v,w,nxt;
    Edge() {}
    Edge(int _v,int _w,int _nxt) {
        v=_v; w=_w; nxt=_nxt;
    }
}edge[maxn<<1];
int T,n,ecnt,head[maxn];
int top[maxn],dep[maxn],sz[maxn]; //top[u]:当前重链的顶端节点；dep[u]:深度；sz[u]:子树中的节点数
int fa[maxn],id[maxn],Index,son[maxn];
//fa[u]:父节点编号；id[u]:每个节点到父亲的连边在序列中的位置；Index:序列总大小；son[u]:重儿子编号
int bian[maxn][8]; //记录边
int tree[maxn*4]; //线段树
void init()
{
    ecnt=0;
    memset(head,-1,sizeof(head));
    memset(son,0,sizeof(son));
    memset(tree,0,sizeof(tree));
    Index=0;
}
void addedge(int u,int v,int w)
{
    edge[ecnt]=Edge(v,w,head[u]);
    head[u]=ecnt++;
}
void dfs1(int u,int p,int d) //得到每个节点的fa、深度、重儿子、sz
{
    dep[u]=d;
    sz[u]=1;
    fa[u]=p;
    for(int i=head[u];i!=-1;i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(v==p) continue;
        dfs1(v,u,d+1);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int tp) //得到id、top
{               //tp:当前重链的顶端节点
    top[u]=tp;
    id[u]=++Index; //u到其父亲的边在线段树中的位置
    if(son[u])
        dfs2(son[u],tp); //先搜索重儿子
    for(int i=head[u];i!=-1;i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v); //新的链中v本身是顶端
    }
}
void push_up(int rt) {
    tree[rt]=max(tree[rt<<1],tree[rt<<1|1]);
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
void change(int p,int x,int l,int r,int rt)
{
    if(l==r) tree[rt]=x;
    else
    {
        int mid=(l+r)>>1;
        if(p<=mid)
            change(p,x,lson);
        else change(p,x,rson);
        push_up(rt);
    }
}
int query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R) return tree[rt];
    int mid=(l+r)>>1,res=0;
    if(L<=mid) res=max(res,query(L,R,lson));
    if(R>mid) res=max(res,query(L,R,rson));
    return res;
}
int QueryOnTree(int u,int v)
{
    int f1=top[u],f2=top[v],res=0;
    while(f1!=f2) //u和v不在同一条重链上
    {
        if(dep[f1]<dep[f2]) swap(f1,f2),swap(u,v);
        res=max(res,query(id[f1],id[u],1,Index,1));
        u=fa[f1];
        f1=top[u];
    }
    if(dep[u]>dep[v]) swap(u,v);
    res=max(res,query(id[son[u]],id[v],1,Index,1));
    return res;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        init();
        For(i,1,n-1)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            bian[i][0]=u,bian[i][1]=v,bian[i][2]=w;
            addedge(u,v,w);
            addedge(v,u,w);
        }
        dfs1(1,1,0);
        dfs2(1,1);
        For(i,1,n-1) //边权移至点权
        {
            if(dep[bian[i][0]]<dep[bian[i][1]])
                swap(bian[i][0],bian[i][1]); //保证0为子节点，1为父节点
            change(id[bian[i][0]],bian[i][2],1,Index,1); //建树
        }
        char op[9];
        while(1)
        {
			scanf("%s",op);
            if(op[0]=='D') break;
            if(op[0]=='C')
            {
                int p,x;
                scanf("%d%d",&p,&x);
                change(id[bian[p][0]],x,1,Index,1);
            }
            else
            {
                int u,v;
                scanf("%d%d",&u,&v);
                printf("%d\n",QueryOnTree(u,v));
            }
        }
    }
    return 0;
}
```
这份代码可以在[Virtual Judge](https://vjudge.net/problem/SPOJ-QTREE)上AC（[评测记录](https://vjudge.net/solution/29759982)），在洛谷上由于 RemoteJudge 的语言限制而不能AC。建议在洛谷提交时使用 C 语言。

这里值得一提的是，在手写`swap`的过程中，尽管[GKxx](https://www.luogu.com.cn/user/72071)大佬用`define`也能做，但个人认为最清爽的方法还是用指针。推荐阅读[C语言 指针应用-swap()](https://blog.csdn.net/climbinglei/article/details/76377298)这篇文章，我也从这篇文章中得到了许多启发，~~而且爽快地给了三连（bushi~~。

下面给出 C 语言代码（内附修改意见），[vjudge实测AC](https://vjudge.net/solution/29760808)。

### Code
```c
//by Blunt_Feeling 洛谷UID：219866
#include<stdio.h> //§改头文件§
#include<string.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i>=(b);--i)
#define maxn 10050 //const改define

int vv[maxn<<1],ww[maxn<<1],nxt[maxn<<1]; //§结构体改数组§
int T,n,ecnt,head[maxn];

int max(int a,int b) {return a>b?a:b;} //§手写max()§
void swap(int *a,int *b) {int c; c=*a; *a=*b; *b=c;} //§用指针手写swap()§

int top[maxn],dep[maxn],sz[maxn];
int fa[maxn],id[maxn],Index,son[maxn];
int bian[maxn][8]; //记录边
int tree[maxn*4];
void init()
{
    ecnt=0;
    memset(head,-1,sizeof(head));
    memset(son,0,sizeof(son));
    memset(tree,0,sizeof(tree));
    Index=0;
}
void addedge(int u,int v,int w)
{
	vv[ecnt]=v; ww[ecnt]=w; nxt[ecnt]=head[u];
    head[u]=ecnt++;
}
void dfs1(int u,int p,int d) //得到每个节点的fa、深度、重儿子、sz
{
    dep[u]=d;
    sz[u]=1;
    fa[u]=p;
    for(int i=head[u];i!=-1;i=nxt[i])
    {
        int v=vv[i];
        if(v==p) continue;
        dfs1(v,u,d+1);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]) son[u]=v;
    }
}
void dfs2(int u,int tp) //得到id、top
{               //tp:当前重链的顶端节点
    top[u]=tp;
    id[u]=++Index; //u到其父亲的边在线段树中的位置
    if(son[u])
        dfs2(son[u],tp); //先搜索重儿子
    for(int i=head[u];i!=-1;i=nxt[i])
    {
        int v=vv[i];
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v); //新的链中v本身是顶端
    }
}
void push_up(int rt) {
    tree[rt]=max(tree[rt<<1],tree[rt<<1|1]);
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
void change(int p,int x,int l,int r,int rt)
{
    if(l==r) tree[rt]=x;
    else
    {
        int mid=(l+r)>>1;
        if(p<=mid)
            change(p,x,lson);
        else change(p,x,rson);
        push_up(rt);
    }
}
int query(int L,int R,int l,int r,int rt)
{
    if(L<=l&&r<=R) return tree[rt];
    int mid=(l+r)>>1,res=0;
    if(L<=mid) res=max(res,query(L,R,lson));
    if(R>mid) res=max(res,query(L,R,rson));
    return res;
}
int QueryOnTree(int u,int v)
{
    int f1=top[u],f2=top[v],res=0;
    while(f1!=f2) //u和v不在同一条重链上
    {
        if(dep[f1]<dep[f2]) {swap(&f1,&f2);swap(&u,&v);} //§加上&§
        res=max(res,query(id[f1],id[u],1,Index,1));
        u=fa[f1];
        f1=top[u];
    }
    if(dep[u]>dep[v]) swap(&u,&v);
    res=max(res,query(id[son[u]],id[v],1,Index,1));
    return res;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        init();
        For(i,1,n-1)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            bian[i][0]=u,bian[i][1]=v,bian[i][2]=w;
            addedge(u,v,w);
            addedge(v,u,w);
        }
        dfs1(1,1,0);
        dfs2(1,1);
        For(i,1,n-1)
        {
            int u=bian[i][0],v=bian[i][1];
            if(dep[u]<dep[v])
                swap(&bian[i][0],&bian[i][1]);
            change(id[bian[i][0]],bian[i][2],1,Index,1);
        }
        char op[9];
        while(1)
        {
			scanf("%s",op);
            if(op[0]=='D') break;
            if(op[0]=='C')
            {
                int p,x;
                scanf("%d%d",&p,&x);
                change(id[bian[p][0]],x,1,Index,1);
            }
            else
            {
                int u,v;
                scanf("%d%d",&u,&v);
                printf("%d\n",QueryOnTree(u,v));
            }
        }
    }
    return 0;
}
```

好了本篇题解到这里就结束了，感谢您能看到这里，祝学习愉快！

---

## 作者：_Andy_Lin_ (赞：4)

这题为啥都用树剖，LCT不香吗？

------------
此题要支持修改边权，查询路径边权信息，直接拆点LCT即可。

------------
$Code:$
```c
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define lc son[x][0]
#define rc son[x][1]
int temp,i,ch;
#define swap(x,y)temp=x,x=y,y=temp;
int max(int x,int y) {
	return x>y?x:y;
}
int fa[20000],son[20000][2],tag[20000],mx[20000],n,T,val[20000];
int nroot(int x) {
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
void pushr(int x) {
	tag[x]^=1;
	swap(lc,rc);
}
void pushdown(int x) {
	if(tag[x]) {
		if(lc)pushr(lc);
		if(rc)pushr(rc);
		tag[x]=0;
	}
}
void pushup(int x) {
	mx[x]=max(max(mx[son[x][0]],mx[son[x][1]]),val[x]);
}
void pushall(int x) {
	if(nroot(x))pushall(fa[x]);
	pushdown(x);
}
void rotate(int x) {
	int f=fa[x],witch=son[f][1]==x,ff=fa[f],y=son[x][witch^1];
	if(nroot(f))son[ff][son[ff][1]==f]=x;
	fa[x]=ff;
	son[x][witch^1]=f;
	fa[f]=x;
	son[f][witch]=y;
	if(y)fa[y]=f;
	pushup(f);
	pushup(x);
}
void splay(int x) {
	pushall(x);
	while(nroot(x)) {
		int f=fa[x],ff=fa[f];
		if(nroot(f))rotate((son[f][1]==x)^(son[ff][1]==f)?x:f);
		rotate(x);
	}
}
void access(int x) {
	for(ch=0; x; x=fa[ch=x]) {
		splay(x);
		rc=ch;
		pushup(x);
	}
}
void makeroot(int x) {
	access(x);
	splay(x);
	pushr(x);
}
int findroot(int x) {
	access(x);
	splay(x);
	while(lc)pushdown(x),x=lc;
	splay(x);
	return x;
}
void split(int x,int y) {
	makeroot(x);
	access(y);
	splay(y);
}
void link(int x,int y) {
	makeroot(x);
	if(findroot(y)!=x)fa[x]=y;
}
void cut(int x,int y) {
	makeroot(x);
	if(findroot(y)==x&&fa[y]==x&&!son[y][0]) {
		fa[y]=son[x][1]=0;
		pushup(x);
	}
}
int main() {
	scanf("%d",&T);
	while(T--){
		memset(fa,0,sizeof(fa));
		memset(son,0,sizeof(son));
		memset(tag,0,sizeof(tag));
		memset(mx,0,sizeof(mx));
		memset(val,0,sizeof(val));
		scanf("%d",&n);
		for(i=1; i<n; i++) {
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			val[n+i]=z;
			link(x,n+i);
			link(n+i,y);
		}
		char s[10];
		while(1) {
			scanf("%s",s);
			if(s[0]=='D')break;
			if(s[0]=='C') {
				int x,y;
				scanf("%d%d",&x,&y);
				splay(n+x);
				val[n+x]=y;
			} else {
				int x,y;
				scanf("%d%d",&x,&y);
				split(x,y);
				printf("%d\n",mx[y]);
			}
		}
	}
	return 0;
}
```

---

## 作者：scp020 (赞：3)

双倍经验：[P4114](https://www.luogu.com.cn/problem/P4114)。

### update on 2023/2/15

这道题的 rmj 只允许交 c 语言的代码，我把代码改了改，在洛谷上过了。把 c 语言代码也贴上来。

### 题目大意

给定一颗 $n$ 个节点的树，有 $n - 1$ 条边，给定每条边的两个端点和边权。

这里有两种操作，询问以 `DONE` 结束。

- 第一种为 `CHANGE` 操作，输入格式为 `CHANGE i t`，表示将第 $i$ 条边的边权改为 $t$。

- 第二种为 `QUERY` 操作，输入格式为 `QUERY a b`，表示查询从节点 $a$ 到节点 $b$ 的路径上边权最小值。

**注意：本题多组数据，请在每轮循环结束后清空所有边。**

### 解法

考虑树链剖分做法。

看到询问边权，我们考虑将边权转化为点权，即把一条链接这父节点和子节点的边的边权转化为子节点的点权。

对于两个节点，它们之间的路径一定会经过两个点的最近公共祖先，如下图。节点 $1$ 和节点 $3$ 之间的路径经过了节点 $2$，而我们将 $4$ 到 $2$ 的边权转化为了点 $2$ 的点权，我们要避开他们的最近公共祖先，这个只要在查询时查询从 $id_a +1$ 到 $id_b$ 之间的点权最大值即可。代码与树链剖分模板题很相似，大部分可以直接粘过来用。

![](https://cdn.luogu.com.cn/upload/image_hosting/rzddl5dx.png)

### 代码

```cpp
//这是 c++ 代码
#include<bits/stdc++.h>
using namespace std;
#define ls l,mid,rt*2
#define rs mid+1,r,rt*2+1
#define lc rt*2
#define rc rt*2+1
#define Getchar() p1==p2 and (p2=(p1=Inf)+fread(Inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
char Inf[1<<21],Ouf[1<<21],*p1,*p2,*p3=Ouf,*p4=Ouf+(1<<21);
inline void read(int &x,char c=Getchar())
{
	bool f=c!='-';
	x=0;
	while(c<48 or c>57) c=Getchar(),f&=c!='-';
	while(c>=48 and c<=57) x=(x<<3)+(x<<1)+(c^48),c=Getchar();
	x=f?x:-x;
}
inline void write(int x)
{
	if(x<0) Putchar('-'),x=-x;
	if(x>=10) write(x/10),x%=10;
	Putchar(x^48);
}
int t,n,dep[10010],f[10010],siz[10010],hvson[10010],id[10010],belong[10010],start[10010],neww[10010],cnt;
int sum[40010];
pair<int,int> Pair[10010];
char ch;
struct edge
{
	int to,cost;
};
vector<edge> v[100010];
inline void dfs1(int pos,int fa,int depth,int maxi=-0x3f3f3f3f)
{
	dep[pos]=depth,f[pos]=fa,siz[pos]=1;
	for(int i=0;i<v[pos].size();i++)
	{
		if(v[pos][i].to!=fa)
		{
			neww[v[pos][i].to]=v[pos][i].cost,dfs1(v[pos][i].to,pos,depth+1),siz[pos]+=siz[v[pos][i].to];
			if(siz[v[pos][i].to]>maxi) hvson[pos]=v[pos][i].to,maxi=siz[v[pos][i].to];
		}
	}
}
inline void dfs2(int pos,int Start)
{
	id[pos]=++cnt,belong[cnt]=pos,start[pos]=Start;
	if(hvson[pos])
	{
		dfs2(hvson[pos],Start);
		for(int i=0;i<v[pos].size();i++)
			if(v[pos][i].to!=f[pos] && v[pos][i].to!=hvson[pos]) dfs2(v[pos][i].to,v[pos][i].to);
	}
}
inline void pushup(const int &rt)
{
	sum[rt]=max(sum[lc],sum[rc]);
}
inline void build(int l,int r,int rt)
{
	if(l==r)
	{
		sum[rt]=neww[belong[l]];
		return;
	}
	int mid=(l+r)/2;
	build(ls),build(rs),pushup(rt);
}
inline void fix(const int &pos,const int &val,int l,int r,int rt)
{
	if(l==r)
	{
		sum[rt]=val;
		return;
	}
	int mid=(l+r)/2;
	if(pos<=mid) fix(pos,val,ls);
	else fix(pos,val,rs);
	pushup(rt);
}
inline int ask(const int &L,const int &R,int l,int r,int rt)
{
	if(L>R) return 0;
	if(L<=l && r<=R) return sum[rt];
	int mid=(l+r)/2,ret=0;
	if(L<=mid) ret=max(ret,ask(L,R,ls));
	if(mid<R) ret=max(ret,ask(L,R,rs));
	return ret;
}
inline int ask(int x,int y)
{
	if(x==y) return 0;
	int ret=0;
	while(start[x]!=start[y])
	{
		if(dep[start[x]]<dep[start[y]]) swap(x,y);
		ret=max(ret,ask(id[start[x]],id[x],1,n,1)),x=f[start[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	ret=max(ret,ask(id[x]+1,id[y],1,n,1));
	return ret;
}
int main()
{
	read(t);
	while(t--)
	{
		read(n),cnt=0,memset(hvson,0,sizeof(hvson));
		for(int i=1,x,y,z;i<n;i++)
			read(x),read(y),read(z),v[x].push_back((edge){y,z}),v[y].push_back((edge){x,z}),Pair[i]=make_pair(x,y);
		dfs1(1,0,1),dfs2(1,1),build(1,n,1);
		for(int x,y;;)
		{
			ch=Getchar();
			while(ch<'A' || ch>'Z') ch=Getchar();
			if(ch=='D') break;
			read(x),read(y);
			if(ch=='C')
			{
				if(f[Pair[x].second]==Pair[x].first) swap(Pair[x].first,Pair[x].second);
				fix(id[Pair[x].first],y,1,n,1);
			}
			else write(ask(x,y)),Putchar('\n');
		}
		for(int i=1;i<=n;i++) v[i].clear();
	}
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

```c
//这是 c 语言代码
#include<stdio.h>
#include<stdlib.h>
#define ls l,mid,rt*2
#define rs mid+1,r,rt*2+1
#define lc rt*2
#define rc rt*2+1
#define getchar() p1==p2 && (p2=(p1=inf)+fread(inf,1,1<<21,stdin),p1==p2)?EOF:*p1++
#define putchar(c) p3==p4 && (fwrite(ouf,1,1<<21,stdout),p3=ouf),*p3++=c
char inf[1<<21],ouf[1<<21],*p1,*p2,*p3=ouf,*p4=ouf+(1<<21);
int read()
{
	char c=getchar();
	int f=(c!='-'),x=0;
	while(c<48 || c>57) c=getchar(),f&=c!='-';
	while(c>=48 && c<=57) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	x=f?x:-x;
	return x;
}
void write(int x)
{
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10),x%=10;
	putchar(x^48);
}
int t,n,dep[10010],f[10010],siz[10010],hvson[10010],id[10010],belong[10010],start[10010],neww[10010],cnt,sum[40010];
int head[100010],tot;
struct pair
{
	int first,second;
};
struct pair make_pair(const int x,const int y)
{
	struct pair ret;
	ret.first=x,ret.second=y;
	return ret;
}
struct pair Pair[10010];
char ch;
struct Edge
{
	int to,cost,next;
};
struct Edge edge[200010];
void add(const int x,const int y,const int z)
{
	edge[++tot].to=y,edge[tot].cost=z,edge[tot].next=head[x],head[x]=tot;
}
int max(const int x,const int y)
{
	return (x>y?x:y);
}
void swap(int *x,int *y)
{
	int t;
	t=*x,*x=*y,*y=t;
}
void dfs1(int pos,int fa,int depth)
{
	int maxi=-0x3f3f3f3f;
	dep[pos]=depth,f[pos]=fa,siz[pos]=1;
	for(int i=head[pos];i;i=edge[i].next)
	{
		if(edge[i].to!=fa)
		{
			neww[edge[i].to]=edge[i].cost,dfs1(edge[i].to,pos,depth+1),siz[pos]+=siz[edge[i].to];
			if(siz[edge[i].to]>maxi) hvson[pos]=edge[i].to,maxi=siz[edge[i].to];
		}
	}
}
void dfs2(int pos,int Start)
{
	id[pos]=++cnt,belong[cnt]=pos,start[pos]=Start;
	if(hvson[pos])
	{
		dfs2(hvson[pos],Start);
		for(int i=head[pos];i;i=edge[i].next)
			if(edge[i].to!=f[pos] && edge[i].to!=hvson[pos]) dfs2(edge[i].to,edge[i].to);
	}
}
void pushup(const int rt)
{
	sum[rt]=max(sum[lc],sum[rc]);
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		sum[rt]=neww[belong[l]];
		return;
	}
	int mid=(l+r)/2;
	build(ls),build(rs),pushup(rt);
}
void fix(const int pos,const int val,int l,int r,int rt)
{
	if(l==r)
	{
		sum[rt]=val;
		return;
	}
	int mid=(l+r)/2;
	if(pos<=mid) fix(pos,val,ls);
	else fix(pos,val,rs);
	pushup(rt);
}
int query(const int L,const int R,int l,int r,int rt)
{
	if(L<=l && r<=R) return sum[rt];
	int mid=(l+r)/2,ret=0;
	if(L<=mid) ret=max(ret,query(L,R,ls));
	if(mid<R) ret=max(ret,query(L,R,rs));
	return ret;
}
int ask(int x,int y)
{
	int ret=0;
	while(start[x]!=start[y])
	{
		if(dep[start[x]]<dep[start[y]]) swap(&x,&y);
		ret=max(ret,query(id[start[x]],id[x],1,n,1)),x=f[start[x]];
	}
	if(dep[x]>dep[y]) swap(&x,&y);
	ret=max(ret,query(id[x]+1,id[y],1,n,1));
	return ret;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read(),cnt=0;
		for(int i=1,x,y,z;i<n;i++)
			x=read(),y=read(),z=read(),add(x,y,z),add(y,x,z),Pair[i]=make_pair(x,y);
		dfs1(1,0,1),dfs2(1,1),build(1,n,1);
		for(int x,y;;)
		{
			ch=getchar();
			while(ch<'A' || ch>'Z') ch=getchar();
			if(ch=='D') break;
			x=read(),y=read();
			if(ch=='C')
			{
				if(f[Pair[x].second]==Pair[x].first) swap(&Pair[x].first,&Pair[x].second);
				fix(id[Pair[x].first],y,1,n,1);
			}
			else write(ask(x,y)),putchar('\n');
		}
		for(int i=1;i<=n;i++) head[i]=0,hvson[i]=0;
	}
	fwrite(ouf,1,p3-ouf,stdout),fflush(stdout);
	return 0;
}
```


---

## 作者：KSkun (赞：3)

本题解同步发布于我的博客：[[SPOJ-QTREE]Query on a tree 题解 | KSkun's Blog](https://ksmeow.moe/qtree_spoj_sol/)，欢迎来逛~

好像洛谷的提交有点问题emmm似乎没有人AC，底下的代码交SPOJ过了，所以不用担心。

# 题解
考虑树链剖分，把每条边的权值记在较深的那个点上即可。剩下的就是板子。注意查询的时候LCA不能计算进去。

# 代码
```cpp
// Code by KSkun, 2018/3
#include <cstdio>
#include <cstring>

inline int max(int a, int b) {
	return a > b ? a : b;
}

inline char fgc() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int readint() {
	register int res = 0, neg = 1;
	register char c = fgc();
	while(c < '0' || c > '9') {
		if(c == '-') neg = -1;
		c = fgc();
	}
	while(c >= '0' && c <= '9') {
		res = res * 10 + c - '0';
		c = fgc();
	}
	return res * neg;
}

inline bool isop(char c) {
	return c == 'Q' || c == 'C' || c == 'D';
}

inline char readop() {
	register char c;
	while(!isop(c = fgc()));
	return c;
}

const int MAXN = 10005;

struct Edge {
	int to, w, nxt;
} gra[MAXN << 1];
int head[MAXN], tot;

int T, n, m, ut, vt, wt;
char op;
int w[MAXN], fa[MAXN], siz[MAXN], son[MAXN], dfn[MAXN], ptn[MAXN], top[MAXN], dep[MAXN], cnt;

inline void dfs1(int u) {
	siz[u] = 1;
	son[u] = 0;
	for(register int i = head[u]; i; i = gra[i].nxt) {
		register int v = gra[i].to;
		if(v == fa[u]) continue;
		dep[v] = dep[u] + 1;
		fa[v] = u;
		w[v] = gra[i].w;
		dfs1(v);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

inline void dfs2(int u, int tp) {
	top[u] = tp;
	dfn[u] = ++cnt;
	ptn[dfn[u]] = u;
	if(son[u]) dfs2(son[u], tp);
	for(register int i = head[u]; i; i = gra[i].nxt) {
		register int v = gra[i].to;
		if(v == son[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
}

int sgt[MAXN << 2];

inline void build(int o, int l, int r) {
	if(l == r) {
		sgt[o] = w[ptn[l]];
		return;
	}
	register int mid = (l + r) >> 1, lch = o << 1, rch = (o << 1) | 1;
	build(lch, l, mid);
	build(rch, mid + 1, r);
	sgt[o] = max(sgt[lch], sgt[rch]);
}

inline void modify(int o, int l, int r, int x, int v) {
	if(l == r) {
		sgt[o] = v;
		return;
	}
	register int mid = (l + r) >> 1, lch = o << 1, rch = (o << 1) | 1;
	if(x <= mid) modify(lch, l, mid, x, v);
	else modify(rch, mid + 1, r, x, v);
	sgt[o] = max(sgt[lch], sgt[rch]);
}

inline int query(int o, int l, int r, int ll, int rr) {
	if(l >= ll && r <= rr) {
		return sgt[o];
	}
	register int mid = (l + r) >> 1, lch = o << 1, rch = (o << 1) | 1, res = 0;
	if(ll <= mid) res = max(res, query(lch, l, mid, ll, rr));
	if(rr > mid) res = max(res, query(rch, mid + 1, r, ll, rr));
	return res;
}

inline int query(int u, int v) {
	register int res = 0, tu = top[u], tv = top[v], t;
	while(tu != tv) {
		if(dep[tu] > dep[tv]) {
			t = tu; tu = tv; tv = t;
			t = u; u = v; v = t;
		}
		res = max(res, query(1, 1, n, dfn[tv], dfn[v]));
		v = fa[tv];
		tv = top[v];
	}
	if(dep[u] > dep[v]) { t = u; u = v; v = t; }
	if(u != v) res = max(res, query(1, 1, n, dfn[u] + 1, dfn[v]));
	return res;
}

struct Edge1 {
	int u, v, w;
} edge[MAXN];

int main() {
	T = readint();
	while(T--) {
		tot = cnt = 0;
		memset(head, 0, sizeof(head));
		n = readint();
		for(int i = 1; i < n; i++) {
			ut = readint(); vt = readint(); wt = readint();
			edge[i] = Edge1 {ut, vt, wt};
			gra[++tot] = Edge {vt, wt, head[ut]};
			head[ut] = tot;
			gra[++tot] = Edge {ut, wt, head[vt]};
			head[vt] = tot;
		}
		dfs1(1);
		dfs2(1, 1);
		build(1, 1, n);
		for(;;) {
			op = readop();
			if(op == 'D') break;
			ut = readint();
			vt = readint();
			if(op == 'Q') {
				printf("%d\n", query(ut, vt));
			} else {
				register int u = dep[edge[ut].u] > dep[edge[ut].v] ? edge[ut].u : edge[ut].v;
				modify(1, 1, n, dfn[u], vt);
			}
		}
	}
	return 0;
}
```

---

## 作者：EternalEpic (赞：2)

此题可明显看出可以用轻重链剖分或Link-Cut Tree来维护。

因为本题RemoteJudge原因，只能用C提交，LCT这类数据结构脱离了C++特性后，对于C不太熟悉的人来说，容易CE。

所以在这里，笔者着重于讲HLD（树剖）的做法。虽然比LCT多一个log但是代码适合初学者接受。

首先，根据题目要求，我们想到要用一种单点修改区间查询最值的数据结构维护，笔者使用线段树。

在修改时直接改底层叶子节点，向上更新：

```cpp
void modify(int pos, int l, int r, int o, int val) {
	if (l == r) { tmax[pos] = val; return; }
	int mid = l + r >> 1;
	if (o <= mid) modify(pos << 1, l, mid, o, val);
	else modify(pos << 1 | 1, mid + 1, r, o, val);
	pushup(pos);
}
```

注意，由于是C，不建议封装。函数式也更快一点。

好，那么问题来了，这里维护的不再是熟悉的点权而是边权。
我们考虑用子节点维护自己与父亲的那条边。也就是：

```cpp
void DfsFir(int u) {
	sze[u] = 1;
	for (int i = head[u]; i; i = nxt[i]) {
		if (ver[i] == fat[u]) continue;
		fat[ver[i]] = u;
		dep[ver[i]] = dep[u] + 1;
		val[ver[i]] = edge[i];
		DfsFir(ver[i]); sze[u] += sze[ver[i]];
		if (sze[ver[i]] > sze[son[u]]) son[u] = ver[i];
	}
}
```

在链查询时，我们要注意当两点跳到同一条重链上时，应查询下点维护的边到上点重儿子维护的边的最值，而且如果两者重合就不必查询了，即：

```cpp
int Query(int u, int v) { int ret = 0;
	while (top[u] ^ top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		ret = max(ret, query(1, 1, n, dfn[top[u]], dfn[u]));
		u = fat[top[u]];
	} if (dep[u] > dep[v]) swap(u, v);// printf("%d\n", val[2]);
	return u == v ? ret : max(ret, query(1, 1, n, dfn[u] + 1, dfn[v]));
}
```

最后再注意一下修改操作直接在线段树上改那条边下端的权值就可以了。

好，那么算法部分讲完了，来谈谈C++转C的问题。

把头文件都去了，没有STL里的函数和容器（如：vector），不用读入优化，用scanf。不允许用引用，请手写swap（可以用指针，也可以像Gkxx大佬用define）。

就这样了。

---

## 作者：OldDriverTree (赞：1)

这题就是一道重链剖分的板子题。

不会的重链剖分模板的话先学下 [重链剖分](https://www.luogu.com.cn/blog/guoxiangyu66/xue-xi-bi-ji-zhong-lian-pou-fen)。

这道题的做法就是就先进行树剖，然后再边权转到深度较大的点上，再用线段树维护点权最大值，最后就是单点修改和树上路径查询了，时间复杂度 $O(m\log^2 n)$，$m$ 为总操作数。

转 C 语言实在不会的的可以看一下 [this](https://www.luogu.com.cn/discuss/575057)。

这里就放 C++ 代码了（不确定会不会TLE，代码是从主题库那题的代码复制过来的）。

# 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+1,M=2e4;
int tot,head[N],nxt[M];
int n,a[N],to[M],val[M];

void add(int x,int y,int z) {
    to[tot]=y,val[tot]=z;
    nxt[tot]=head[x];
    head[x]=tot++;
}
int size[N],fa[N],depth[N];
int cnt,id[N],son[N],top[N];

struct SGT
{
    int val[N<<2];
    #define mid (l+r>>1)
    #define pushup val[rt]=max(val[rt<<1],val[rt<<1|1])
    void update(int rt,int l,int r,int p,int x)
    {
        if (l==r) return val[rt]=x,void();
        if (p<=mid) update(rt<<1,l,mid,p,x);
        else update(rt<<1|1,mid+1,r,p,x);
        pushup;
    }
    void query(int rt,int l,int r,int L,int R,int &ans)
    {
        if (L<=l&&r<=R) return ans=max(ans,val[rt]),void();
        if (L<=mid) query(rt<<1,l,mid,L,R,ans);
        if (mid<R) query(rt<<1|1,mid+1,r,L,R,ans);
    }
}A;

int read() {
    int x=0; char ch=0;
    while (!isdigit(ch)) ch=getchar();
    while (isdigit(ch)) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
    return x;
}
void dfs1(int u,int f)
{
    fa[u]=f,size[u]=1;
    depth[u]=depth[f]+1;
    for (int i=head[u];~i;i=nxt[i])
        if (to[i]!=f) {
            dfs1(to[i],u),a[to[i]]=val[i],size[u]+=size[to[i]];
            if (size[to[i]]>size[son[u]]) son[u]=to[i];
        }
}
void dfs2(int u,int topf)
{
    top[u]=topf,id[u]=(++cnt);
    A.update(1,1,n,cnt,a[u]);
    if (son[u]) dfs2(son[u],topf);
    for (int i=head[u];~i;i=nxt[i])
        if (!top[to[i]])
            dfs2(to[i],to[i]);
}
int Query(int x,int y)
{
    int ans=0;
    if (x==y) return 0;
    while (top[x]!=top[y]) {
        if (depth[top[x]]<depth[top[y]]) swap(x,y);
        A.query(1,1,n,id[top[x]],id[x],ans),x=fa[top[x]];
    }
    if (depth[x]>depth[y]) swap(x,y);
    A.query(1,1,n,id[x]+1,id[y],ans);
    return ans;
}
int main()
{
    string s;
    int T=read(),x,y,z;
    while (T--) {
        n=read(),cnt=tot=0;
        memset(head,-1,sizeof head);
        memset(son,0,sizeof son);
        memset(top,0,sizeof top);
        for (int i=1;i<n;i++) {
            x=read(),y=read(),z=read();
            add(x,y,z),add(y,x,z);
        } dfs1(1,0),dfs2(1,1);
        while (cin>>s,s!="DONE")
        {
            x=read(),y=read();
            if (s=="CHANGE") {
                int tx=to[(x<<1)-1],ty=to[(x-1)<<1];
                if (depth[tx]<depth[ty]) swap(tx,ty);
                A.update(1,1,n,id[tx],y);
            } else printf("%d\n",Query(x,y));
        }
    }
    return 0;
}
```

---

## 作者：Laoshan_PLUS (赞：0)

还是很裸的一道树剖，唯一和板子不同的地方就是边权改点权。

边权改点权的方法也很简单，只需要把边权放在深度较深的结点上即可。

唯一需要注意的地方就是，LCA 会有不同的边权信息。**我们发现在退出 `fx != fy` 这个循环时，$\boldsymbol x$ 一定是 LCA，所以我们只需将 $\boldsymbol{\textbf{\textit{dfn}}[x]}$ 加 $\boldsymbol1$，也就是跳过 LCA，即可解决。**

剩下就是很裸的树剖 + 线段树维护区间最大值了。

```cpp
#include <bits/stdc++.h>
#define lp p << 1
#define rp p << 1 | 1
using namespace std;

constexpr int MAXN = 1e4 + 5;
int T, n, w[MAXN];
vector<pair<int, int>> g[MAXN];
struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int u, int v, int w): u(u), v(v), w(w) {}
} e[MAXN];
int fa[MAXN], dep[MAXN], siz[MAXN], son[MAXN], top[MAXN], dfn[MAXN], rnk[MAXN], cnt;
struct SegTree {
	int l, r, c;
} st[MAXN << 2];

void init() {
	for (auto &x : g) x.clear();
	memset(fa, 0, sizeof(fa));
	memset(dep, 0, sizeof(dep));
	memset(siz, 0, sizeof(siz));
	memset(son, 0, sizeof(son));
	memset(top, 0, sizeof(top));
	memset(dfn, 0, sizeof(dfn));
	memset(rnk, 0, sizeof(rnk));
	cnt = 0;
}

void dfs1(int u) {
	siz[u] = 1;
	for (auto vv : g[u]) {
		int v = vv.first, ww = vv.second;
		if (!dep[v]) {
			dep[v] = dep[u] + 1;
			fa[v] = u;
			w[v] = ww;
			dfs1(v);
			siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) son[u] = v;
		}
	}
}

void dfs2(int u, int t) {
	top[u] = t;
	dfn[u] = ++cnt;
	rnk[cnt] = u;
	if (!son[u]) return;
	dfs2(son[u], t);
	for (auto vv : g[u]) {
		int v = vv.first;
		if (v != son[u] && v != fa[u])
			dfs2(v, v);
	}
}

void build(int s, int t, int p) {
	st[p].l = s, st[p].r = t;
	if (s == t) {
		st[p].c = w[rnk[s]];
		return;
	}
	int mid = (s + t) >> 1;
	build(s, mid, lp);
	build(mid + 1, t, rp);
	st[p].c = max(st[lp].c, st[rp].c);
}

void add(int x, int k, int p) {
	int s = st[p].l, t = st[p].r;
	if (s == t) {
		st[p].c = k;
		return;
	}
	int mid = (s + t) >> 1;
	if (x <= mid) add(x, k, lp);
	else add(x, k, rp);
	st[p].c = max(st[lp].c, st[rp].c);
}

int sum(int l, int r, int p) {
	int s = st[p].l, t = st[p].r;
	if (l <= s && t <= r) return st[p].c;
	int mid = (s + t) >> 1, res = 0;
	if (l <= mid) res = max(res, sum(l, r, lp));
	if (mid < r) res = max(res, sum(l, r, rp));
	return res;
}

int qmax(int x, int y) {
	int res = INT_MIN, fx = top[x], fy = top[y];
	while (fx != fy) {
		if (dep[fx] >= dep[fy]) {
			res = max(res, sum(dfn[fx], dfn[x], 1));
			x = fa[fx];
		} else {
			res = max(res, sum(dfn[fy], dfn[y], 1));
			y = fa[fy];
		}
		fx = top[x];
		fy = top[y];
	}
	if (dfn[x] < dfn[y]) res = max(res, sum(dfn[x] + 1, dfn[y], 1));
	else res = max(res, sum(dfn[y] + 1, dfn[x], 1));
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> T;
	while (T--) {
		init();
		cin >> n;
		for (int i = 1; i < n; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			g[u].push_back(make_pair(v, w));
			g[v].push_back(make_pair(u, w));
			e[i] = Edge(u, v, w);
		}
		dep[1] = 1;
		dfs1(1);
		dfs2(1, 1);
		build(1, n, 1);
		string op;
		while (cin >> op) {
			if (op == "DONE") break;
			int x, y;
			cin >> x >> y;
			if (op == "CHANGE") {
				int u = e[x].u, v = e[x].v;
				if (fa[v] == u) swap(u, v);
				add(dfn[u], y, 1);
			} else cout << qmax(x, y) << '\n';
		}
	}

	return 0;
}
```

---

## 作者：Zhangikun (赞：0)

## 前置知识：
树链剖分、线段树。

## 思路：
这题需要我们求树上两点之间最短路径中包含的节点中最大的点权，又有单点修改操作。

可以发现，对于一条重链，链顶到链尾的 dfs 序是连续的，所以可以把每条链当区间，用线段树维护。
## 温馨提示：
本题 C++ 语言提交不了，请用 C 语言。
## 代码
```c
#include<stdio.h>
#include<string.h>
#define int long long 
#define cxk 1000005
#define mid (lt+rt>>1)
int n,m,sz[cxk],fa[cxk],upp[cxk],dep[cxk],top[cxk],dfn[cxk],tot,id[cxk],tree[cxk<<2],pt[cxk],x[cxk],y[cxk],w[cxk],a[cxk],head[cxk],to[cxk*2],nx[cxk*2],tt;
void add(int x,int y)
{
    tt++;
    nx[tt]=head[x];
    to[tt]=y;
    head[x]=tt;
}
int max(int x,int y)
{
    if(x>y)
        return x;
    return y;
}
void dfs(int cur)
{
    dep[cur]=dep[fa[cur]]+1;
    sz[cur]=1;
    int maxi=0;
    for(int i=head[cur];i;i=nx[i])
    {
        int nxt=to[i];
        if(nxt==fa[cur])
            continue;
        fa[nxt]=cur;
        dfs(nxt);
        sz[cur]+=sz[nxt];
        if(maxi<sz[nxt])
        {
            maxi=sz[nxt];
            upp[cur]=nxt;
        }
    }
}
void dfs2(int cur)
{
    dfn[cur]=++tot;
    id[tot]=cur;
    if(upp[cur]==0)
        return; 
    top[upp[cur]]=top[cur];
    dfs2(upp[cur]);
    for(int i=head[cur];i;i=nx[i])
    {
        int nxt=to[i];
        if(nxt==fa[cur]||nxt==upp[cur])
            continue;
        top[nxt]=nxt;
        dfs2(nxt);
    }
}
//---------------------------------------
void pushup(int cur)
{
    tree[cur]=max(tree[cur*2],tree[cur*2+1]);
}
void build(int cur,int lt,int rt)
{
    if(lt==rt)
    {
        tree[cur]=a[id[lt]];
        return;
    }
    build(cur*2,lt,mid);
    build(cur*2+1,mid+1,rt);
    pushup(cur);
}
void update(int cur,int lt,int rt,int q,int val)
{
    if(lt==rt)
    {
        tree[cur]=val;
        return;
    }
    if(q<=mid)
        update(cur*2,lt,mid,q,val);
    else
        update(cur*2+1,mid+1,rt,q,val);
    pushup(cur);
}
int query(int cur,int lt,int rt,int ql,int qr)
{
    if(qr<lt||rt<ql)
        return 0;
    if(ql<=lt&&rt<=qr)
        return tree[cur];
    return max(query(cur*2,lt,mid,ql,qr),query(cur*2+1,mid+1,rt,ql,qr));
}
//---------------------------------------
int query2(int x,int y)
{
    int tx=top[x],ty=top[y],maxi=-1e16;
    while(tx!=ty)//保证不在同一条链
    {
        if(dep[tx]<dep[ty])
        {
            int z=tx;
            tx=ty;
            ty=z;
            z=x;
            x=y;
            y=z;
        }
        maxi=max(maxi,query(1,1,n,dfn[tx],dfn[x]));//链顶、当前点
        x=fa[tx],tx=top[x];//跳链
    }
    if(dep[x]>dep[y])
    {
    	int z=x;
    	x=y;
    	y=z;
	}
    return max(maxi,query(1,1,n,dfn[x]+1,dfn[y]));
}
void help()
{
	tot=tt=0;
    memset(head,0,sizeof(head));
    memset(to,0,sizeof(to));
    memset(nx,0,sizeof(nx));
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    memset(w,0,sizeof(w));
    memset(id,0,sizeof(id));
    memset(tree,0,sizeof(tree));
    memset(sz,0,sizeof(sz));
    memset(fa,0,sizeof(fa));
    memset(upp,0,sizeof(upp));
    memset(nx,0,sizeof(nx));
    scanf("%lld",&n);
    for(int i=1;i<n;i++)
    {
        scanf("%lld%lld%lld",x+i,y+i,w+i);
        add(x[i],y[i]);
        add(y[i],x[i]);
    }
    top[1]=1;
    dfs(1);
    for(int i=1;i<n;i++)
    {
        if(dep[x[i]]<dep[y[i]])
        {
        	int z=x[i];
        	x[i]=y[i];
        	y[i]=z;
		}
        a[x[i]]=w[i];//存点权 
    }
    dfs2(1);
    build(1,1,n);
    char s[1145];
    for(int u,v;1;)
    {
        scanf("%s",s);
        if(s[0]=='D')
            return;
        scanf("%lld%lld",&u,&v);
        if(s[0]=='C')
            update(1,1,n,dfn[x[u]],v);
        if(s[0]=='Q')
            printf("%lld\n",query2(u,v));
    }
}
signed main()
{
	int t;
	scanf("%lld",&t);
	while(t--)
		help();
}
```

---

## 作者：SrsgPrince_ (赞：0)

# SP375 QTREE - Query on a tree Solution

题面传送门：[SP375 QTREE - Query on a tree](https://www.luogu.com.cn/problem/SP375)。

建议在我的 [博客](https://www.luogu.com.cn/blog/fy123333/SP375Solution) 中查看。

## 题目分析

题目如下：

给定 $n$ 个点的树，边按输入顺序编号为 $1,2,…,n−1$，要求作以下操作：

1. `CHANGE i ti` 将第 $i$ 条边权值改为 $ti$；
2. `QUERY a b` 询问从 $a$ 点到 $b$ 点路径上的最大边权。

有多组测试数据，每组数据以 `DONE` 结尾。

根据 QTREE 传统，使用树链剖分做。

这道题是树上的最大值和单点查询，但是给定的是边权，所以我们要把边权转换一下，换成点权，那么就是维护点，直接考虑用 LCA。

按照的我思路做下来，提交，然后……UKE 了。然后看了讨论才发现是 RMJ 背大锅，还要换成 C 来写。注意一些点：

1. 不能用万能头了，要拆开，还要换成 `.h` 结尾的。
2. STL 的所有函数需要自己手写，例如下面的 `max()` 和 `swap()`。
3. 不知道为啥，我不能用 `const int`，用了会 RE，报错大意是“用变量作为数组大小”。

先给出 C++ 代码：

```cpp
inline void addEdge(int b, int e, int v) {
    des[++cnt] = e;
    nxt[cnt] = head[b];
    head[b] = cnt;
    w[cnt] = v;
}
inline void dfs1(int u) {
    siz[u] = 1;
    chd[u] = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = des[i];
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        a[v] = w[i];
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[chd[u]]) chd[u] = v;
    }
}
inline void dfs2(int u, int rt) {
    dfn[u] = ++ind;
    rnk[ind] = u;
    top[u] = rt;
    if (chd[u]) dfs2(chd[u], rt);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = des[i];
        if (v == fa[u] || v == chd[u]) continue;
        dfs2(v, v);
    }
}
inline void pushUp(int p) {
    t[p] = max(t[p << 1], t[p << 1 | 1]);
}
inline void buildTree(int p, int lft, int rgt) {
    if (lft == rgt) {
        t[p] = a[rnk[lft]];
        return;
    }
    int mid = (lft + rgt) >> 1;
    buildTree(p << 1, lft, mid); buildTree(p << 1 | 1, mid + 1, rgt);
    pushUp(p);
}
inline void update(int p, int lft, int rgt, int pos, int val) {
    if (lft == rgt) {
        t[p] = val;
        return;
    }
    int mid = (lft + rgt) >> 1;
    if (pos <= mid) update(p << 1, lft, mid, pos, val);
    else update(p << 1 | 1, mid + 1, rgt, pos, val);
    pushUp(p);
}
inline int query(int p, int lft, int rgt, int l, int r) {
    if (l <= lft && rgt <= r) return t[p];
    int mid = (lft + rgt) >> 1, res = 0;
    if (l <= mid) res = max(res, query(p << 1, lft, mid, l, r));
    if (r > mid) res = max(res, query(p << 1 | 1, mid + 1, rgt, l, r));
    return res;
}
inline int query2(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = max(res, query(1, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res = max(res, query(1, 1, n, dfn[u] + 1, dfn[v]));
    return res;
}
int main() {
    int q; scanf("%d", &q);
    while (q--) {
        cnt = ind = 0;
        memset(head, 0, sizeof(head));
        scanf("%d", &n);
        for (int i = 1; i < n; ++i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            fr[i] = x, tx[i] = y;
            addEdge(x, y, z); addEdge(x, y, z);
        }
        dfs1(1); dfs2(1, 1);
        buildTree(1, 1, n);
        while (true) {
            scanf("%s", ch + 1);
            if (ch[1] == 'D') break;
            else {
                int x, y;
                scanf("%d%d", &x, &y);
                if (ch[1] == 'Q') printf("%d\n", query2(x, y));
                else {
                    x = dep[fr[x]] > dep[tx[x]] ? fr[x] : tx[x];
                    update(1, 1, n, dfn[x], y);
                }
            }
        }
    }
    return 0;
}
```

接下来是按照上面的提示改出来的 C。

```c
int max(int x, int y) {return x > y ? x : y;}
void swap(int x, int y) {
    int tmp = x;
    x = y;
    y = tmp;
}
void addEdge(int b, int e, int v) {
    des[++cnt] = e;
    nxt[cnt] = head[b];
    head[b] = cnt;
    w[cnt] = v;
}
void dfs1(int u) {
    siz[u] = 1;
    son[u] = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = des[i];
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        a[v] = w[i];
        dfs1(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u, int rt) {
    dfn[u] = ++ind;
    rnk[ind] = u;
    top[u] = rt;
    if (son[u]) dfs2(son[u], rt);
    for (int i = head[u]; i; i = nxt[i]) {
        int v = des[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}
void pushUp(int p) {
    t[p] = max(t[p << 1], t[p << 1 | 1]);
}
void buildTree(int p, int lft, int rgt) {
    if (lft == rgt) {
        t[p] = a[rnk[lft]];
        return;
    }
    int mid = (lft + rgt) >> 1;
    buildTree(p << 1, lft, mid); buildTree(p << 1 | 1, mid + 1, rgt);
    pushUp(p);
}
void update(int p, int lft, int rgt, int pos, int val) {
    if (lft == rgt) {
        t[p] = val;
        return;
    }
    int mid = (lft + rgt) >> 1;
    if (pos <= mid) update(p << 1, lft, mid, pos, val);
    else update(p << 1 | 1, mid + 1, rgt, pos, val);
    pushUp(p);
}
int query(int p, int lft, int rgt, int l, int r) {
    if (l <= lft && rgt <= r) return t[p];
    int mid = (lft + rgt) >> 1, res = 0;
    if (l <= mid) res = max(res, query(p << 1, lft, mid, l, r));
    if (r > mid) res = max(res, query(p << 1 | 1, mid + 1, rgt, l, r));
    return res;
}
int query2(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        res = max(res, query(1, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    res = max(res, query(1, 1, n, dfn[u] + 1, dfn[v]));
    return res;
}
int main() {
	int q;
	scanf("%d",&q);
	while (q--) {
		cnt = ind = 0;
		memset(head, 0, sizeof(head));
		scanf("%d", &n);
		for (int i = 1; i < n; ++i) {
 	       int u, v, z;
			scanf("%d %d %d",&u,&v,&z);
			fr[i] = u;
			tx[i] = v;
			addEdge(u, v, z);
			addEdge(v, u, z);
		}
    	dfs1(1); dfs2(1, 1);
    	buildTree(1,1,n);
    	while (1) {
    	    scanf("%s", ch + 1);
    	    if (ch[1] == 'D') break;
    	    else {
				int x, y;
    	        scanf("%d %d", &x, &y);
	            if (ch[1] == 'Q') printf("%d\n", query2(x, y));
	            else {
	                int t = dep[fr[x]] > dep[tx[x]] ? fr[x] : tx[x];
	                update(1,1,n,dfn[t],y);
	            }
	        }
	    }
	}
    return 0;
}
```

总体上没有太多改变。


---

## 作者：xiezheyuan (赞：0)

[也许有更好的阅读体验](https://www.cnblogs.com/zheyuanxie/p/spoj-qtree.html)

## 简要题意

[原题目链接](https://www.spoj.com/problems/QTREE/) | [洛谷题目链接](https://www.luogu.com.cn/problem/SP375)

给出一个 $n$ 个节点的树，树边上有权值，支持以下操作：

- `CHANGE i ti` 将 $i$ 号边（即，第 $i$ 个输入的边）的权赋值为 $t_i$。
- `QUERY a b` 询问树上简单路径 $(a,b)$ 上的最大边权。
- `DONE` 结束当前组数据。

多组数据，共 $T$ 组。

$1 \leq N \leq 10000,1 \leq T \leq 20$

## 思路

这道题树剖比较神，这里写的是 LCT。

但是 LCT 默认是维护点权，而不是边权。我们可以选择将一条边 $(u,v,w)$ 拆成一个点 $i$，然后连边 $(u,i)$ 和 $(i,v)$，将 $i$ 的点权设定为 $w$。这样子原来的路径没有改变，但成功的将边权转换成了点权。

最后记得多组数据，清空数组。

## C++ 转 C 语言

（本题远端评测仍然没有修好，只能交 C 语言）

这里讲一些可能让大家头疼的问题：

- C 语言中没有 `bool` 类型，你需要引用头文件 `stdbool.h` 方可使用 `bool`。
- C 语言中没有 `swap,min,max` 等函数，你需要手动定义。
- C 语言中 `const` 修饰的变量并不是字面量。也就是说，不能用 `const` 修饰的变量定义数组大小。
- `memset` 在头文件 `string.h` 中。

## 代码

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ls (son[i][0])
#define rs (son[i][1])
#define N 100005
#define swap(x,y) {int _t;_t=x;x=y;y=_t;}
#define int long long
#define clean(x) memset(x,0,sizeof(x))

int son[N][2];
int fa[N];
bool tag[N];
int siz[N];
int val[100005];

int max(int x,int y){
	return x>y?x:y;
}

inline void pushup(int i){
	siz[i]=max(siz[ls],max(siz[rs],val[i]));
}
inline void reverse(int i){
	swap(ls,rs);tag[i]^=1;
}
inline void pushdown(int i){
	if(tag[i]){
		// now i want to pushdown the tags.
		if(ls) reverse(ls);
		if(rs) reverse(rs);
		tag[i]=0;
	}
}
inline bool get(int i){
	return son[fa[i]][1]==i;
}
inline bool is_root(int i){
	return son[fa[i]][0]!=i && son[fa[i]][1]!=i;
}
void update(int i){
	if(!is_root(i)){
		update(fa[i]);
	}
	pushdown(i);
}
void rotate(int p){
	int q=fa[p],z=fa[q],k=get(p);
	if(!is_root(q)){
		son[z][son[z][1]==q]=p;
	}
	fa[p]=z;
	son[q][k]=son[p][!k];
	if(son[p][!k]) fa[son[p][!k]]=q;
	son[p][!k]=q;
	fa[q]=p;
	pushup(q);
	pushup(p);
}
void splay(int i){
	update(i);
	for(int f;f=fa[i],!is_root(i);rotate(i)){
		if(!is_root(f)){
			rotate(get(f)==get(i)?f:i);
		}
	}
}
void access(int i){
	int p;
	for(p=0;i;p=i,i=fa[i]){
		splay(i);
		son[i][1]=p;
		pushup(i);
	}
}
int find(int i){
	access(i);
	splay(i);
	while(ls) pushdown(i),i=ls;
	splay(i);
	return i;
}
void make_root(int i){
	access(i);
	splay(i);
	reverse(i);
}
void split(int u,int v){
	make_root(u);
	access(v);splay(v);
}
void link(int u,int v){
	make_root(u);
	if(find(v)!=u){
		fa[u]=v;
	}
}
void cut(int u,int v){
	make_root(u);
	if(find(v)==u&&fa[v]==u&&(!son[v][0])) son[u][1]=fa[v]=0;
}

int n;

void solve(){
	clean(son);clean(fa);clean(siz);clean(val);clean(tag);
	scanf("%lld",&n);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		val[i+n]=w;
		link(u,i+n);link(i+n,v);
	}
	while(1){
		char buffer[10];
		scanf("%s",buffer);
		if(buffer[0]=='C'){
			int i,ti;
			scanf("%lld%lld",&i,&ti);
			splay(i+n);
			val[i+n]=ti;
		}
		else if(buffer[0]=='Q'){
			int a,b;
			scanf("%lld%lld",&a,&b);
			split(a,b);
			printf("%lld\n",siz[b]);
		}
		else{
			break;
		}
	}
}

signed main(){
	int t;
	scanf("%lld",&t);
	while(t--)solve();
	return 0;
}
```

---

## 作者：KEBrantily (赞：0)

本题同洛谷主题库同名题[P4114 Qtree1](https://www.luogu.com.cn/problem/P4114)

考察基础树链剖分操作

------------
## Solution

#### 考察树上点权覆盖以及求最大值操作

------------
对于第一个操作 点权覆盖

在原始 update 的代码上稍作改动即可实现，差别只有一个加号

```cpp
if(L<=l&&R>=r){
    tree[x]=val;
    return ;
}
else{其他正常操作}
```
然后再调用时可以直接用，两边的边界设定为一样的就行

或者写函数时直接写成单点操作

------------
对于第二个操作 求最大值

注意本题要求边权转点权，递归调用的 dfn 要加一

然后对于线段树内只需要维护一个最大值，其他的都不用

也是和普通模板差不多，query 改改就行

------------
## Code
```cpp
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#define maxn 1000010
#define ls x<<1
#define rs x<<1|1 

using namespace std;

int n,head[maxn],tot,cnt;
int dfn[maxn],a[maxn],son[maxn],fa[maxn],top[maxn],siz[maxn];
int sum[maxn],lazy[maxn],maxx[maxn],dep[maxn],pre[maxn];
int f[maxn],t[maxn];
string opt;

struct edge{
	int fr,to,dis,nxt;
}e[maxn];

inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=getchar();}
	return s*w;
}

inline void add(int fr,int to,int dis){
	e[++tot].fr=fr;
	e[tot].to=to;
	e[tot].dis=dis;
	e[tot].nxt=head[fr];
	head[fr]=tot;
}

inline int Max(int x,int y){
	return x>y?x:y;
}

namespace Seg{
	inline void pushup(int x){
		maxx[x]=Max(maxx[ls],maxx[rs]);
	}
	
	inline void build(int x,int l,int r){
		if(l==r){
			maxx[x]=a[pre[l]];
			return ;
		}
		int mid=l+r>>1;
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x);
	}
	
	inline void updateMax(int x,int l,int r,int val,int L,int R){
		if(L<=l&&R>=r){
			maxx[x]=val;
			return ;
		}
		int mid=l+r>>1;
		if(L<=mid) updateMax(ls,l,mid,val,L,R);
		if(R>=mid+1) updateMax(rs,mid+1,r,val,L,R);
		pushup(x);
	}
	
//	inline void addMax(int rt,int x,int l,int r,int val){这是单点修改的实现 
//		if(l==r){
//			maxx[x]=val;
//			return ;
//		}
//		int mid=l+r>>1;
//		if(rt<=mid) addMax(rt,ls,l,mid,val);
//		else addMax(rt,rs,mid+1,r,val); 
//		pushup(x);
//	}
	
	inline int qMax(int x,int l,int r,int L,int R){
		int ans=-101010101;
		if(L<=l&&R>=r){
			return maxx[x];
		}
		int mid=l+r>>1;
		if(L<=mid) ans=Max(ans,qMax(ls,l,mid,L,R));
		if(R>=mid+1) ans=Max(ans,qMax(rs,mid+1,r,L,R));
		return ans;
	}
}

namespace Cut{
	inline void dfs1(int x,int fat){
		fa[x]=fat;dep[x]=dep[fat]+1;siz[x]=1;
		for(int i=head[x];i;i=e[i].nxt){
			int to=e[i].to;
			if(to==fa[x]) continue;
			a[to]=e[i].dis;
			dfs1(to,x);
			siz[x]+=siz[to];
			if(siz[son[x]]<siz[to]) son[x]=to;
		}
	}
	
	inline void dfs2(int x,int tp){
		top[x]=tp;dfn[x]=++cnt;pre[cnt]=x;
		if(son[x]) dfs2(son[x],tp);
		for(int i=head[x];i;i=e[i].nxt){
			int to=e[i].to;
			if(to==fa[x]||to==son[x]) continue;
			dfs2(to,to);
		}
	}
	
	inline int askMax(int x,int y){
		int ans=-101010101;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			ans=Max(ans,Seg::qMax(1,1,n,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		if(dfn[x]>dfn[y]) swap(x,y);
		ans=Max(ans,Seg::qMax(1,1,n,dfn[x]+1,dfn[y]));
		return ans;
	}
	
}

int main(){
	n=read();
	for(int i=1,u,v,w;i<n;i++){
		u=read();v=read();w=read();
		add(u,v,w);add(v,u,w);
		f[i]=u;t[i]=v;
	}
	Cut::dfs1(1,0);Cut::dfs2(1,1);Seg::build(1,1,n);
	
	while(1){
		cin>>opt;
		int l,r;
		if(opt.length()==4) break;
		l=read();r=read();
		if(opt.length()==6){
            int sss=f[l],yyy=t[l];
            if(fa[yyy]==sss) swap(sss,yyy);
            Seg::updateMax(1,1,n,r,dfn[sss],dfn[sss]);
//	        Seg::addMax(dfn[sss],1,1,n,r);另一个函数的调用方法 
		}
		if(opt.length()==5){if(l>r) swap(l,r);printf("%d\n",l==r?0:Cut::askMax(l,r));};
	}
	return 0;
}
```


------------
顺便说下，本题需要用 C 语言才能过，~~但是我不会 哈哈~~

转语言什么的别的题解都有，也不难

懂了思想就没什么大问题了

另外感觉别的题解里都是一句话带过然后直接上代码

虽然是个板子也不难但是对于一些新手来说会很雾

希望可以有帮助吧

------------

## End.

---

## 作者：torque (赞：0)

题目链接[SP375](https://www.luogu.org/problem/SP375)

## 题意

边树剖，两个操作：

1.路径求最大值

2.单点（边）修改

## 思路

不会边树剖请左转[P4114 Qtree1](https://www.luogu.org/problem/P4114)

实际上就是把边权赋到儿子节点再树剖，注意每次操作时忽略掉LCA（因为映射到LCA的边不在路径上）

那么这道题难点在哪呢？为啥是黑的？

重头戏来了(首先声明我用c++)

![](https://cdn.luogu.com.cn/upload/pic/75372.png)

## 我吹(锤)爆C语言！

因为它：

***

> 没有``const``、``inline``、``using``、``namespace``

> 没有``algorithm``(``max``、``min``、``sort``、``swap``)

> 只有``.h``

> 没有``STL``(虽然本题用不到)

***

~~我没有想到世界上有这么好的语言！你们居然不用！~~

我不会告诉泥萌这道题只能用c语言的（小声

所以c++有的这些外挂都给删了吧

给出几个例子

1.``swap(x,y)``请改成手写，如``x^=y^=x^=y``

2.``max(x,y)``改成手写，建议改为函数（我用宏定义T了，还是@StudyingFather dalao腻害）

3.删掉``using namespace``

4.如果你的代码里有``const``、``inline``等，最好删掉

5.``iostream``丢了吧，``cstdio``改为``stdio.h``，``cstdlib``改为``stdlib.h``(指头文件)

大概就列出这些，不懂就看一下代码吧

## 代码

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100001
#define INF 1ll<<60
#define int long long
#define rnt register int
char s[100];
struct edge{
	int to,nxt,len,id;
} e[N*2];
struct tree{int l,r,/*sum,*/maxn,tag1,tag2;}t[N*4];
int T,n,m,x,y,z,cnt,tot,d[N],to[N],fa[N],len[N],son[N],dep[N],top[N],siz[N],dfn[N],rnk[N],head[N];
int max(int a,int b){
    if(a>b) return a;
    else return b;
}
inline void ins(int a,int b,int c,int d){
	e[++cnt].to=b;
    e[cnt].len=c;
    e[cnt].nxt=head[a];
    e[cnt].id=d;
	head[a]=cnt;
}
void dfs1(int cur,int pre,int id){
	to[id]=cur;
	fa[cur]=pre;
	siz[cur]=1;
	d[cur]=len[id];
	dep[cur]=dep[pre]+1;
	rnt i=head[cur];
	for(;i;i=e[i].nxt) if(e[i].to!=pre){
		dfs1(e[i].to,cur,e[i].id);
		siz[cur]+=siz[e[i].to];
		if(siz[e[i].to]>siz[son[cur]]) son[cur]=e[i].to;
	}
}
void dfs2(int cur,int Top){
	dfn[cur]=tot=-~tot;
	rnk[tot]=cur;top[cur]=Top;
	if(!son[cur]) return ;
	dfs2(son[cur],Top);rnt i=head[cur];
	for(;i;i=e[i].nxt){
		int y=e[i].to;
		if(y!=fa[cur] && y!=son[cur]) dfs2(y,y);
	}
}
void pushup(int id){
//	t[id].sum=t[id<<1].sum+t[id<<1|1].sum;
	t[id].maxn=max(t[id<<1].maxn,t[id<<1|1].maxn);
}
void pushdown(int id){
	if(t[id].l==t[id].r) return;
	if(t[id].tag1!=INF){
		int val=t[id].tag1;
		t[id<<1].tag2=t[id<<1|1].tag2=0;
		t[id<<1].maxn=t[id<<1|1].maxn=val;
		t[id<<1].tag1=val,t[id<<1|1].tag1=val;
//		t[id<<1].sum=val*(t[id<<1].r-t[id<<1].l+1);
//		t[id<<1|1].sum=val*(t[id<<1|1].r-t[id<<1|1].l+1);
		t[id].tag1=INF;
	}
	if(t[id].tag2){
		int val=t[id].tag2;
		if(t[id<<1].tag1!=INF) t[id<<1].tag1+=val;
		else t[id<<1].tag2+=val;
		t[id<<1].maxn+=val;/*t[id<<1].sum+=val*(t[id<<1].r-t[id<<1].l+1);*/
		if(t[id<<1|1].tag1!=INF) t[id<<1|1].tag1+=val;
		else t[id<<1|1].tag2+=val;
		t[id<<1|1].maxn+=val;/*t[id<<1|1].sum+=val*(t[id<<1|1].r-t[id<<1|1].l+1);*/
		t[id].tag2=0;
	}
}
void build(int id,int l,int r){
	t[id].l=l,t[id].r=r,t[id].tag1=INF;
	if(l==r){
		t[id].maxn=/*t[id].sum=*/d[rnk[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
	pushup(id);
}
//
void change(int id,int l,int r,int val){
	if(l>r) return ;
	pushdown(id);
	if(t[id].l==l && r==t[id].r){
		t[id].tag1=val,t[id].tag2=0;
		t[id].maxn=val/*,t[id].sum=val*(r-l+1)*/;
		return ;
	}
	int mid=(t[id].l+t[id].r)>>1;
	if(r<=mid) change(id<<1,l,r,val);
	else if(l>mid) change(id<<1|1,l,r,val);
	else{change(id<<1,l,mid,val);change(id<<1|1,mid+1,r,val);}
	pushup(id);
}
inline void ask_cover(int x,int y,int z){
	int sum=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) x^=y^=x^=y;
		change(1,dfn[top[x]],dfn[x],z);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) x^=y^=x^=y;
	change(1,dfn[x]+1,dfn[y],z);
}
/*
int Sum(int id,int l,int r){
	pushdown(id);
	if(t[id].l==l && t[id].r==r) return t[id].sum;
	int mid=(t[id].l+t[id].r)>>1;
	if(r<=mid) return Sum(id<<1,l,r);
	else if(l>mid) return Sum(id<<1|1,l,r);
	else return Sum(id<<1,l,mid)+Sum(id<<1|1,mid+1,r);
}
inline int ask_sum(int x,int y){
	int sum=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		sum+=Sum(1,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	sum+=Sum(1,dfn[x],dfn[y]);
	return sum;
}
*/
int Max(int id,int l,int r){
	if(l>r) return -INF;
	pushdown(id);
	if(t[id].l==l && t[id].r==r) return t[id].maxn;
	int mid=(t[id].l+t[id].r)>>1;
	if(r<=mid) return Max(id<<1,l,r);
	else if(l>mid) return Max(id<<1|1,l,r);
	else return max(Max(id<<1,l,mid),Max(id<<1|1,mid+1,r));
}
inline int ask_max(int x,int y){
	int maxn=-(1ll<<60);
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) x^=y^=x^=y;
		maxn=max(maxn,Max(1,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) x^=y^=x^=y;
	maxn=max(maxn,Max(1,dfn[x]+1,dfn[y]));
	return maxn;
}
//
void Plus(int id,int l,int r,int val){
	if(l>r) return ;
	pushdown(id);
	if(t[id].l==l && t[id].r==r){
		if(t[id].tag1!=INF) t[id].tag1+=val;
		else t[id].tag2+=val;
		/*t[id].sum+=(r-l+1)*val,*/t[id].maxn+=val;
		return ;
	}
	int mid=(t[id].l+t[id].r)>>1;
	if(r<=mid) Plus(id<<1,l,r,val);
	else if(l>mid) Plus(id<<1|1,l,r,val);
	else{Plus(id<<1,l,mid,val);Plus(id<<1|1,mid+1,r,val);}
	pushup(id);
}
inline int ask_add(int x,int y,int z){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) x^=y^=x^=y;
		Plus(1,dfn[top[x]],dfn[x],z);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) x^=y^=x^=y;
	Plus(1,dfn[x]+1,dfn[y],z);
}
//
signed main(){
	scanf("%d",&T);
	Work:if(T){
		memset(siz,0,sizeof(siz));
		memset(son,0,sizeof(son));
		memset(head,0,sizeof(head));
		scanf("%lld",&n);rnt i=1;cnt=0;tot=0;
		for(;i<n;i=-~i){
			scanf("%lld%lld%lld",&x,&y,&z);
			ins(x,y,z,i);ins(y,x,z,i);
			len[i]=z;
		}
		dfs1(1,0,0);dfs2(1,1);
		build(1,1,n);
		for(;;){
			scanf("\n%s",s);
			if(s[0]=='D') break;
			scanf("%lld%lld",&x,&y);
			if(s[0]=='C') if(s[1]=='H') change(1,dfn[to[x]],dfn[to[x]],y);
			else scanf("%lld",&z),ask_cover(x,y,z);
			else if(s[0]=='A') scanf("%lld",&z),ask_add(x,y,z);
			else if(x==y) printf("0\n");
			else printf("%lld\n",ask_max(x,y));
		}
		--T;goto Work;
	}
	return 0;
}
```

---

## 作者：Taoist_Cheewood (赞：0)

这道题的关键就是，化边权为点权。

那么，问题来了，如何化？

~~小道作为一个蒟蒻，自是苦思良久：~~把边往下面（深一点）的点放；但是小道太弱了，不能直接知道那个点更深，只能用一个二维数组来存边，等两遍遍历完后，再对比deep，然后下放，用w存值。
```cpp
for(int i=1;i<n;i++)
{
	scanf("%d%d%d",&line[i][0],&line[i][1],&line[i][2]);
	add(line[i][0],line[i][1]);
	add(line[i][1],line[i][0]);
}
dfs1(1,0,1);
dfs2(1,1);
for(int i=1;i<n;i++)
{
	if(deep[line[i][0]]<deep[line[i][1]])
		swap(line[i][0],line[i][1]);
	w[tid[line[i][0]]]=line[i][2];
}
```

这样就有另一个问题了，那就是：

### LCA那一部分不能取lca点，要取它的重边点！！！

```cpp
int res=0;
while(top[u]!=top[v])
{
	if(deep[top[u]]<deep[top[v]]) swap(u,v);
	res=max(res,query(tid[top[u]],tid[u],1,n,1));
	u=f[top[u]];
}
if(deep[u]>deep[v]) swap(u,v);
return max(res,query(tid[son[u]],tid[v],1,n,1));//是tid[son[u]],不是tid[u].
```

如此这般，套进板子就可以了~~（板子都不会打的，来写这道题干嘛，出门左转模板题）~~

然后，c++转c！去掉命名空间、ios、al；c开头变为.h;
```cpp
#define swap(a,b) {t=a;a=b;b=t;}

int max(int a,int b)
{
	return a>b?a:b;
}
```
然后提交时选C语言~~（小道就是在这卡了很久）~~

下面送上完整代码。
```
#include<math.h>
#include<stdio.h>
#include<string.h>
typedef long long ll;
//#include<iostream>
//using namespace std;
#define lson l,m,rt<<1
#define N 10010
#define rson m+1,r,rt<<1|1
int n,q,cnt,pos,t;
int head[N],top[N],tid[N],rank[N],deep[N],f[N],son[N],siz[N],w[N];
int tree[N<<2],lazy[N<<2],line[N][3];
#define swap(a,b) {t=a;a=b;b=t;}

int max(int a,int b)
{
	return a>b?a:b;
}

struct edge{
	int v,next;
}e[N<<1];

void add(int u,int v)
{
	e[++cnt].v=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}

void dfs1(int u,int fa,int d)
{
	f[u]=fa;
	deep[u]=d;
	siz[u]=1;
	for(int i=head[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dfs1(v,u,d+1);
		siz[u]+=siz[v];
		if(son[u]==-1||siz[v]>siz[son[u]])
			son[u]=v;
	}
}

void dfs2(int u,int fa)
{
	top[u]=fa;
	tid[u]=++pos;
	if(son[u]==-1) return ;
	dfs2(son[u],fa);
	for(int i=head[u];i!=-1;i=e[i].next)
	{
		int v=e[i].v;
		if(v!=son[u]&&v!=f[u]) dfs2(v,v);
	}
}

void build(int l,int r,int rt)
{
	if(l==r)
	{
		tree[rt]=w[l];
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	tree[rt]=max(tree[rt<<1],tree[rt<<1|1]);
}

void update(int x,int k,int l,int r,int rt)
{
	if(l==r){
		tree[rt]=k;
		return ;
	}
	int m=(l+r)>>1;
	if(x<=m) update(x,k,lson);
	else update(x,k,rson);
	tree[rt]=max(tree[rt<<1],tree[rt<<1|1]);
}

int query(int a,int b,int l,int r,int rt)
{
	int res=0;
	if(a<=l&&r<=b)
	{
		return tree[rt];
	}
	int m=(l+r)>>1;
	if(a<=m) res=max(res,query(a,b,lson));
	if(b>m) res=max(res,query(a,b,rson));
	return res;
}

int trque(int u,int v)
{
	int res=0;
	while(top[u]!=top[v])
	{
		if(deep[top[u]]<deep[top[v]]) swap(u,v);
		res=max(res,query(tid[top[u]],tid[u],1,n,1));
		u=f[top[u]];
	}
	if(deep[u]>deep[v]) swap(u,v);
	return max(res,query(tid[son[u]],tid[v],1,n,1));
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		memset(head,-1,sizeof(head));
		memset(son,-1,sizeof(son));
		cnt=pos=0;
		int u,v;
		scanf("%d",&n);
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&line[i][0],&line[i][1],&line[i][2]);
			add(line[i][0],line[i][1]);
			add(line[i][1],line[i][0]);
		}
		dfs1(1,0,1);
		dfs2(1,1);
		for(int i=1;i<n;i++)
		{
			if(deep[line[i][0]]<deep[line[i][1]])
				swap(line[i][0],line[i][1]);
			w[tid[line[i][0]]]=line[i][2];
		}
		build(1,n,1);
		char op[10];
		while(1)
		{
			scanf("%s",op);
			if(op[0]=='D') break;
			scanf("%d%d",&u,&v);
			if(op[0]=='C') update(tid[line[u][0]],v,1,n,1);
			else printf("%d\n",trque(u,v));
		}
	}
	return 0;
}
```


---

## 作者：mzgwty (赞：0)

这个题C++会UKE，~~然而蒟蒻又不会把c++转c~~，但这份代码是经过大数据对拍的，所以请放心，可以正常食用。

首先，显然这题就是树链剖分（~~傻子都看得出来~~）

关键在于边转点的方法，其他题解里都是用的将边的值直接传到连接的两点中的深度较大的那个点，虽然效率会加快，但是码量和细节也会增加。

# 所以

干脆直接用最原始的边转点，将第i条边转为第i+n个点存下来，然后连接u和i+n号点、v和i+n号点，这样写码量会少一些，细节也会少很多，~~因此最适合我这种不想动脑子，只想写板子的人了~~

代码实现就很简单了（~~我们班有巨佬写的LCT，不知道他AC没有~~)~_~


```cpp
#include<bits/stdc++.h>
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
using namespace std;

const int N=100005;

int dep[N],f[N],son[N],size[N],top[N],seg[N],rev[N];

struct Edge {
    int next,to;
}a[N<<2];

int head[N],sze;

inline void add(int u,int v) {
    a[++sze].next=head[u];
    a[sze].to=v;
    head[u]=sze;
    
    a[++sze].next=head[v];
    a[sze].to=u;
    head[v]=sze;
}

inline void dfs1(int u,int fa) {
    dep[u]=dep[fa]+1,size[u]=1,f[u]=fa;
    for(register int i=head[u] ; i ; i=a[i].next) {
        int v=a[i].to;
        if(v!=fa) {
            dfs1(v,u);
            size[u]+=size[v];
            if(size[v]>size[son[u]]) son[u]=v;
        }
    }
}

inline void dfs2(int u) {
    int v=son[u];
    if(v) {
        top[v]=top[u];
        seg[v]=++seg[0];
        rev[seg[0]]=v;
        dfs2(v);
    }
    for(register int i=head[u] ; i ; i=a[i].next) {
        v=a[i].to;
        if(!top[v]) {
            top[v]=v;
            seg[v]=++seg[0];
            rev[seg[0]]=v;
            dfs2(v);
        }
    }
}

int maxn[N<<2],val[N];

inline void build(int k,int l,int r) {
    if(l>r) return ;
    if(l==r) {
        maxn[k]=val[rev[l]];
        return ;
    }
    build(lson,l,mid),build(rson,mid+1,r);
    maxn[k]=max(maxn[lson],maxn[rson]);
}

inline void update(int k,int l,int r,int pos,int key) {
    if(l>pos||r<pos) return ;
    if(l==r&&l==pos) {
        maxn[k]=key;
        return ;
    }
    update(lson,l,mid,pos,key),update(rson,mid+1,r,pos,key);
    maxn[k]=max(maxn[lson],maxn[rson]);
}

inline int query(int k,int l,int r,int x,int y) {
    if(l>y||r<x) return -0x7fffffff;
    if(l>=x&&r<=y) return maxn[k];
    return max(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));
}

inline int ask(int x,int y) {
    int ans=-0x7fffffff;
    while(top[x]!=top[y]) {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans=max(ans,query(1,1,seg[0],seg[top[x]],seg[x]));
        x=f[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans=max(ans,query(1,1,seg[0],seg[x],seg[y]));
    return ans;
}

inline void init() {
    memset(head,0,sizeof(head));
    sze=0;
    memset(val,-0x7f,sizeof(val));
}
int n;

inline void work() {
    int u,v,w;
    scanf("%d",&n);
    for(register int i=1 ; i<n ; ++i) {
        scanf("%d%d%d",&u,&v,&w);
        add(u,n+i),add(n+i,v);
        val[n+i]=w;
    }
    dfs1(1,0);
    top[1]=seg[0]=seg[1]=rev[1]=1;
    dfs2(1);
    build(1,1,seg[0]);
    while(1) {
        char op[10];
        scanf("%s",op);
        if(op[0]=='D') return ;
        if(op[0]=='Q') {
            scanf("%d%d",&u,&v);
            printf("%d\n",ask(u,v));
        }
        else if(op[0]=='C') {
            scanf("%d%d",&u,&v);
            update(1,1,seg[0],seg[u+n],v);
        }
    }
}

int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        init();
        work();
    }
    return 0;
}
```


---

## 作者：King丨帝御威 (赞：0)

其实这个题也不算特别的难，如果你做过有关换边权为点权的题目的话，比如……[月下“毛景树”](https://www.luogu.org/problemnew/show/P4315)，[旅游](https://www.luogu.org/problemnew/show/P1505)等。自我感觉难度都比这道题要大，并且都涉及到化边权为点权然后树链剖分。

不多说了，我们来看这个题，这道题与普通的树链剖分题目不同的是，这道题目给出的是边权，但是普通的树链剖分题目都是给出的点权，那，该怎么办呢？不难发现，每个点有且只有一条边连向它的父亲结点，诶？？有且只有一条？那！！我们就可以用这个点的点权去代替它与它父亲之间边的边权呀！！那这不就又成了树链剖分板子题了嘛？！$QwQ$。还有一个坑就是最后查询的时候，因为LCA的点权不在查询的路径范围内，因此要排除掉。

洛谷上此题的c++评测有些问题，下面给出c的代码(memset必须要全写，不然没法AC，我也不知道为什么)：

```c
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#define maxn 10007
#define ls rt<<1
#define rs rt<<1|1
int id[maxn],d[maxn],n,cnt,son[maxn],top[maxn],maxx[maxn<<2],t;
int head[maxn],num,fa[maxn],siz[maxn],w[maxn],a[maxn];
char s[8];
struct node {
  int v,w,nxt;
}e[maxn<<1];
int max(int a, int b) { return a > b ? a : b; }
#define swap(A, B)   \
    {                \
        int __T = A; \
        A = B;       \
        B = __T;     \
    }

void ct(int u, int v, int w) {
  e[++num].v=v;
  e[num].w=w;
  e[num].nxt=head[u];
  head[u]=num;
}
void pushup(int rt) {
  maxx[rt]=max(maxx[ls],maxx[rs]);
}
void build(int rt, int l, int r) {
  if(l==r) {
    maxx[rt]=a[l];
    return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid);
  build(rs,mid+1,r);
  pushup(rt);
}
void modify(int rt, int l, int r, int L, int val) {
  if(l==r) {
    maxx[rt]=val;
    return;
  }
  int mid=(l+r)>>1;
  if(L<=mid) modify(ls,l,mid,L,val);
  else modify(rs,mid+1,r,L,val);
  pushup(rt);
}
int cmax(int rt, int l, int r, int L, int R) {
  if(L<=l&&r<=R) return maxx[rt];
  int ans=0;
  int mid=(l+r)>>1;
  if(L<=mid) ans=max(ans,cmax(ls,l,mid,L,R));
  if(R>mid) ans=max(ans,cmax(rs,mid+1,r,L,R));
  return ans;
}
void dfs1(int u) {
  siz[u]=1;
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=fa[u]) {
      d[v]=d[u]+1;
      fa[v]=u;
      w[v]=e[i].w;
      dfs1(v);
      siz[u]+=siz[v];
      if(siz[v]>siz[son[u]]) son[u]=v;
    }
  }
}
void dfs2(int u, int t) {
  id[u]=++cnt;
  top[u]=t;
  a[cnt]=w[u];
  if(son[u]) dfs2(son[u],t);
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
  }
}
int query(int x, int y) {
  int ans=0,fx=top[x],fy=top[y];
  while(fx!=fy) {
    if(d[fx]<d[fy]) {
      swap(x,y);
      swap(fx,fy);
    }
    ans=max(ans,cmax(1,1,n,id[fx],id[x]));
    x=fa[fx],fx=top[x];
  }
  if(id[x]>id[y]) swap(x,y);
  ans=max(ans,cmax(1,1,n,id[x]+1,id[y]));
  return ans;
}
int main() {
  scanf("%d",&t);
  while(t--) {
    memset(head,0,sizeof(head));
    memset(siz,0,sizeof(siz));
    memset(id,0,sizeof(id));
    memset(top,0,sizeof(top));
    memset(son,0,sizeof(son));
    memset(w,0,sizeof(w));
    memset(maxx,0,sizeof(maxx));
    memset(a,0,sizeof(a));
    memset(fa,0,sizeof(fa));
    memset(d,0,sizeof(d));num=0;cnt=0;
    scanf("%d",&n);
    for(int i=1,u,v,w;i<n;++i) {
      scanf("%d%d%d",&u,&v,&w);
      ct(u,v,w),ct(v,u,w);
    }
    dfs1(1);dfs2(1,1);build(1,1,n);
    while(1) {
      scanf("%s",s);
      if(s[0]=='D') break;
      if(s[0]=='C') {
        int x,y;
        scanf("%d%d",&x,&y);
        x=d[e[x*2-1].v]<d[e[x<<1].v]?e[x<<1].v:e[x*2-1].v;
        modify(1,1,cnt,id[x],y);
      }
      if(s[0]=='Q') {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
      }
    }
  }
  return 0;
}
```

接下来是在SPOJ上能够AC的c++代码：
``` cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define maxn 10007
#define ls rt<<1
#define rs rt<<1|1
using namespace std;
int id[maxn],d[maxn],n,cnt,son[maxn],top[maxn],maxx[maxn<<2],t;
int head[maxn],num,fa[maxn],siz[maxn],w[maxn],a[maxn];
char s[8];
struct node {
  int v,w,nxt;
}e[maxn<<1];
inline void ct(int u, int v, int w) {
  e[++num].v=v;
  e[num].w=w;
  e[num].nxt=head[u];
  head[u]=num;
}
inline void pushup(int rt) {
  maxx[rt]=max(maxx[ls],maxx[rs]);
}
void build(int rt, int l, int r) {
  if(l==r) {
    maxx[rt]=a[l];
    return;
  }
  int mid=(l+r)>>1;
  build(ls,l,mid);
  build(rs,mid+1,r);
  pushup(rt);
}
void modify(int rt, int l, int r, int L, int val) {
  if(l==r) {
    maxx[rt]=val;
    return;
  }
  int mid=(l+r)>>1;
  if(L<=mid) modify(ls,l,mid,L,val);
  else modify(rs,mid+1,r,L,val);
  pushup(rt);
}
int cmax(int rt, int l, int r, int L, int R) {
  if(L<=l&&r<=R) return maxx[rt];
  int ans=0;
  int mid=(l+r)>>1;
  if(L<=mid) ans=max(ans,cmax(ls,l,mid,L,R));
  if(R>mid) ans=max(ans,cmax(rs,mid+1,r,L,R));
  return ans;
}
void dfs1(int u) {
  siz[u]=1;
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=fa[u]) {
      d[v]=d[u]+1;
      fa[v]=u;
      w[v]=e[i].w;
      dfs1(v);
      siz[u]+=siz[v];
      if(siz[v]>siz[son[u]]) son[u]=v;
    }
  }
}
void dfs2(int u, int t) {
  id[u]=++cnt;
  top[u]=t;
  a[cnt]=w[u];
  if(son[u]) dfs2(son[u],t);
  for(int i=head[u];i;i=e[i].nxt) {
    int v=e[i].v;
    if(v!=fa[u]&&v!=son[u]) dfs2(v,v);
  }
}
int query(int x, int y) {
  int ans=0,fx=top[x],fy=top[y];
  while(fx!=fy) {
    if(d[fx]<d[fy]) {
      swap(x,y);
      swap(fx,fy);
    }
    ans=max(ans,cmax(1,1,n,id[fx],id[x]));
    x=fa[fx],fx=top[x];
  }
  if(id[x]>id[y]) swap(x,y);
  ans=max(ans,cmax(1,1,n,id[x]+1,id[y]));
  return ans;
}
int main() {
  scanf("%d",&t);
  while(t--) {
    memset(head,0,sizeof(head));
    memset(siz,0,sizeof(siz));
    memset(id,0,sizeof(id));
    memset(top,0,sizeof(top));
    memset(son,0,sizeof(son));
    memset(w,0,sizeof(w));
    memset(maxx,0,sizeof(maxx));
    memset(a,0,sizeof(a));
    memset(fa,0,sizeof(fa));
    memset(d,0,sizeof(d));num=0;cnt=0;
    scanf("%d",&n);
    for(int i=1,u,v,w;i<n;++i) {
      scanf("%d%d%d",&u,&v,&w);
      ct(u,v,w),ct(v,u,w);
    }
    dfs1(1);dfs2(1,1);build(1,1,n);
    while(1) {
      scanf("%s",s);
      if(s[0]=='D') break;
      if(s[0]=='C') {
        int x,y;
        scanf("%d%d",&x,&y);
        x=d[e[x*2-1].v]<d[e[x<<1].v]?e[x<<1].v:e[x*2-1].v;
        modify(1,1,cnt,id[x],y);
      }
      if(s[0]=='Q') {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
      }
    }
  }
  return 0;
}
```

---

