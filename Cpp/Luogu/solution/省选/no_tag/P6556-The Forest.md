# The Forest

## 题目背景

Deep in the forest, swift in the night.

They come out, with the frightening shouting under the moonlight.

You stare at the horrible figures. They are real, alive.

I promise you've never experienced a worse night.

They come nearer, nearer, till a meter left.

You see their real faces. Scary eyes and hair in a mess.

You think they coming for you, then you are wrong.

They only want your delicious cheese, which is produced in a scary farm.

That's what happens in the forest. Enjoy your time!

## 题目描述

**请注意，本题的时间限制为 5s！**

探险家小 A 和小 B 需要用灯泡照亮这个森林。

有 $n$ 个灯泡，编号为 $1, 2, \cdots, n$。小 A 用 $n - 1$ 条红色绳子把它们连成了一棵树，小 B 用 $n - 1$ 条蓝色绳子把它们连成了另一棵树。

一开始所有灯泡都是熄灭的，现在要点亮若干个灯泡。小 A 喜欢联通块，而小 B 喜欢链。他们想知道：有多少种点亮灯泡的方案，满足点亮的灯泡在小 A 的树上形成一个联通块，在小 B 的树上形成一条链呢？

## 说明/提示

**样例解释：**

[点击查看三组数据的图解](https://www.luogu.com.cn/paste/l5u1f2ob)。

对于第一组数据，可以点亮的灯泡集合有：

+ $\{1\}$；
+ $\{2\}$；
+ $\{3\}$；
+ $\{1, 2\}$；
+ $\{1, 2, 3\}$。

注意不能点亮集合 $\{1, 3\}$，因为编号为 $1, 3$ 的灯泡在小 A 的树上不构成联通块；也不能点亮集合 $\{2, 3\}$，因为编号为 $2, 3$ 的灯泡在小 B 的树上不构成一条链。

对于第二组数据，可以点亮的，**至少包含两个灯泡的**的灯泡集合有：

+ $\{1, 2\}$；
+ $\{1, 2, 3\}$；
+ $\{1, 2, 3, 4\}$；
+ $\{1, 2, 3, 4, 5\}$。

显然大小为 $1$ 的灯泡集合都合法，所以答案为 $4 + 5 = 9$。

**限制与约定：**

对于 $20 \%$ 的数据，$n \le 50$，满足特殊限制 $X$。  
对于 $40 \%$ 的数据，$n \le 3000$，满足特殊限制 $X$。  
对于 $70 \%$ 的数据，满足特殊限制 $X$。  
对于 $100 \%$ 的数据，$T = 3, 1 \le n \le 10^5$。

特殊限制 $X$：$c_i = i, d_i = i + 1$，也就是说**小 B 的树**是一条链，编号相邻的点之间有边。

## 样例 #1

### 输入

```
3
3
1 2
2 3
1 2
1 3
5
1 2
1 3
2 4
2 5
1 2
2 3
3 4
4 5
5
3 1
3 2
3 4
3 5 
1 2
2 3
3 4
3 5
```

### 输出

```
5
9
14
```

# 题解

## 作者：yizhiming (赞：8)

呃呃了，在以为其他题解做麻烦的前提下写了写发现假了，结果优化成了和其他人一样的做法。

### 题目大意

给定 $n$ 个点的两棵树 $A,B$，求有多少个点集满足将点集内的点按照树上的边连边后，在 $A$ 树上形成一个联通块，在 $B$ 树上形成一条链。

$T$ 组数据。

$T = 3,1\leq n\leq10^5$。

### 题目分析

先考虑一个性质，对于一个树上的点集 $T$，若其内部边的数量为 $x$，那么这个点集的联通块数是 $|T|-x$，证明考虑一开始每个点都单独一个联通块，每次连一条边就是把两个联通块合并成一个。

有了这个性质如何做呢？这启发了我们维护联通块数。

首先考虑特殊性质，对于 $B$ 树是链，等价于要求点集是个区间，所以考虑扫描线，设 $s_i$ 表示在当前扫描线右端点在 $r$，左端点在 $i$ 时，这个区间点集在 $A$ 树上有几个联通块，答案显然是区间内 $1$ 的个数，由于区间最小值一定最小为 $1$，所以可以直接维护区间最小值个数。

如何转移，考虑由 $r$ 推到 $r+1$，此时对于 $[1,r+1]$ 来说都新加入了一个点，所以区间加 $1$，然后对于 $A$ 树上的一条边 $(u,r+1)$ 满足 $u<r+1$ 来说，$[1,u]$ 的 $s_i$  对应的点集内一定有这条边，所以区间减 $1$ 即可，答案就是所有版本的 $1$ 的个数和。

考虑扩展到树上，如何将区间转换成链，不难想到令每个点作为根，求出每个点到根路径形成的点集在 $A$ 树上的联通块个数，不妨设 $f_i$ 表示这个，答案会算多，原因是对于一条合法的链 $(u,v)$ 在 $u,v$ 为根时都会计算一遍，所以要去掉，注意 $(u,u)$ 不会算重。

接下来的内容默认会换根意义下的区间加减，若不会请去[遥远的国度](https://www.luogu.com.cn/problem/P3979)。

假设当前根为 $u$，要换到他的儿子 $v$，如何转移 $s_i$，令 $W(x,y)$ 表示以 $x$ 为根时，$y$ 的子树表达的点集。

首先由于 $v$ 提到了根的位置，所以除了 $W(u,v)$ 以外的所有点，所对应的点集都插入了一个点，区间加，同理 $W(u,v)$ 整体少了一个点。

现在考虑新的边的贡献，$v$ 对于 $W(u,v)$ 的贡献在 $u$ 为根的时候已经统计过了，所以对于 $A$ 树边 $(v,x)$，若 $x \notin W(u,v)$ 那么就对 $W(v,x)$ 进行一次子树减，因为这部分都会被这条边影响。同理我们也要删除 $u$ 的在 $W(u,v)$ 内的 $A$ 树上邻居的贡献，但是发现每次换根都枚举一圈 $A$ 树的邻居，总的枚举个数就成了两树度数的平方。

注意到对于 $u$ 需要删掉的贡献只有在 $W(u,v)$ 内的，容易发现对于 $u$ 每个儿子，其子树区间不相交，所以我们可以将 $A$ 边按照 $B$ 树的 dfs 序排序，这样的话每个贡献只会增减各一次。

### Code

注意要做到从 $v$ 版本回溯到 $u$，所以记录下来操作反着做一遍即可。

对于最开始的 $1$ 号版本，可以暴力预处理出来初始情况。

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N = 1e5+5;
int n;
vector<int>in[N],ed[N];

int minx,cnt,rt;
struct seg{
	struct aa{
		int lc,rc,mi,sum,tag;
		void clear(){
			lc = rc = mi = sum = tag = 0;
		}
	}node[N*2];
	void pushup(int u){
		aa x = node[node[u].lc],y = node[node[u].rc];
		node[u].mi = min(x.mi,y.mi);
		node[u].sum = (x.mi==node[u].mi?x.sum:0)+(y.mi==node[u].mi?y.sum:0);
	}
	int tot;
	int newnode(){
		int u = ++tot;
		node[u].clear();
		return u;
	}
	void build(int &u,int l,int r){
		u = newnode();
		node[u].sum = (r-l+1);
		if(l==r){
			return;
		}
		int mid = (l+r)/2;
	
		build(node[u].lc,l,mid);
		build(node[u].rc,mid+1,r);
	}
	void lazy_tag(int u,int x){
		node[u].mi+=x;
		node[u].tag+=x;
	}
	void pushdown(int u){
		if(!node[u].tag){
			return;
		}
		lazy_tag(node[u].lc,node[u].tag);
		lazy_tag(node[u].rc,node[u].tag);
		node[u].tag = 0;
	}
	void upd(int u,int l,int r,int ll,int rr,int x){
		if(l==ll&&r==rr){
			lazy_tag(u,x);
			return;
		}
		pushdown(u);
		int mid = (l+r)/2;
		if(rr<=mid){
			upd(node[u].lc,l,mid,ll,rr,x);
		}else if(ll>mid){
			upd(node[u].rc,mid+1,r,ll,rr,x); 
		}else{
			upd(node[u].lc,l,mid,ll,mid,x);
			upd(node[u].rc,mid+1,r,mid+1,rr,x);
		}
		pushup(u);
	}
	void ask(int u,int l,int r,int ll,int rr){
		if(l==ll&&r==rr){
			if(node[u].mi<minx){
				minx = node[u].mi;
				cnt = node[u].sum;
			}else if(node[u].mi==minx){
				cnt+=node[u].sum;
			}
			return;
		}
		pushdown(u);
		int mid = (l+r)/2;
		if(rr<=mid){
			ask(node[u].lc,l,mid,ll,rr);
		}else if(ll>mid){
			ask(node[u].rc,mid+1,r,ll,rr);
		}else{
			ask(node[u].lc,l,mid,ll,mid);
			ask(node[u].rc,mid+1,r,mid+1,rr);
		}
	}
}T;
int siz[N],dep[N],son[N],fa[N],top[N],dfn[N],tt;
bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
void dfs1(int u,int f){
	siz[u] = 1;
	son[u] = 0;
	for(auto x:in[u]){
		if(x==f){
			continue;
		}
		fa[x] = u;
		dep[x] = dep[u]+1;
		dfs1(x,u);
		siz[u]+=siz[x];
		if(siz[x]>siz[son[u]]){
			son[u] = x;
		}
	}
}
void dfs2(int u,int t){
	top[u] = t;
	dfn[u] = ++tt;
	if(!son[u]){
		return;
	}
	dfs2(son[u],t);
	for(auto x:in[u]){
		if(x==fa[u]||x==son[u]){
			continue;
		}
		dfs2(x,x);
	}
}
int Lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]){
			swap(u,v);
		}
		u = fa[top[u]];
	}
	if(dep[u]<dep[v]){
		swap(u,v);
	}
	return v;
}
int query(){
	minx = 1e9;
	cnt = 0;
	T.ask(rt,1,n,1,n);
	if(minx==1){
		return cnt;
	}else{
		return 0;
	}
}
struct bb{
	int l,r,x;
};
vector<bb>op[N];
void add(int u,int l,int r,int x){
	op[u].push_back((bb){l,r,x});
	T.upd(rt,1,n,l,r,x);
}
int RT,res;
int get(int u,int x){
	while(top[u]!=top[x]){
		if(fa[top[u]]==x){
			return top[u];
		}
		u = fa[top[u]];
	}
	return son[x];
}
void dfs(int u){
	if(u!=1){
		add(u,1,n,1);
		add(u,dfn[u],dfn[u]+siz[u]-1,-2);
		for(auto x:ed[u]){
			if(dfn[u]<=dfn[x]&&dfn[x]<=dfn[u]+siz[u]-1){
				continue;
			}
			if(dfn[x]<=dfn[u]&&dfn[u]<=dfn[x]+siz[x]-1){
				int v = get(u,x);
				add(u,1,n,-1);
				add(u,dfn[v],dfn[v]+siz[v]-1,1);
			}else{
				add(u,dfn[x],dfn[x]+siz[x]-1,-1);
			}
		}
	}
	res+=query();
	int r = 0;
	int sz = ed[u].size(); 
	while(r<sz){
		int y = ed[u][r];
		if(dfn[y]<dfn[u]||dfn[y]>dfn[u]+siz[u]-1){
			r++;
		}else{
			break;
		}
	}
	for(auto x:in[u]){
		if(x==fa[u]){
			continue;
		}
		int R = r;
		while(r<sz){
			int y = ed[u][r];
			if(dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+siz[x]-1){
				T.upd(rt,1,n,dfn[y],dfn[y]+siz[y]-1,1);
				r++;
			}else{
				break;
			}
		}
		dfs(x);
		for(int i=R;i<r;i++){
			int y = ed[u][i];
			T.upd(rt,1,n,dfn[y],dfn[y]+siz[y]-1,-1);
		}
	}
	
	for(auto x:op[u]){
		T.upd(rt,1,n,x.l,x.r,-x.x);
	}
}
int U[N],V[N];
void init(){
	n = read();
	T.tot = 0;rt = 0;res = 0;tt = 0;
	for(int i=1;i<=n;i++){
		in[i].clear();ed[i].clear();op[i].clear();
	}
	for(int i=1;i<n;i++){
		int u,v;
		u = read();v = read();
		U[i] = u;V[i] = v;
	}
	for(int i=1;i<n;i++){
		int u,v;
		u = read();v = read();
		in[u].push_back(v);
		in[v].push_back(u);
	}
	dfs1(1,1);
	dfs2(1,1);
	T.build(rt,1,n);
	for(int i=1;i<=n;i++){
		T.upd(rt,1,n,dfn[i],dfn[i]+siz[i]-1,1);
	}
	for(int i=1;i<n;i++){
		int u,v;
		u = U[i];v = V[i];
		ed[u].push_back(v);
		ed[v].push_back(u);
		if(dep[u]>dep[v]){
			swap(u,v);
		}
		int L = Lca(u,v);
		if(u==L){
			T.upd(rt,1,n,dfn[v],dfn[v]+siz[v]-1,-1);
		}
	}
	for(int i=1;i<=n;i++){
		sort(ed[i].begin(),ed[i].end(),cmp);
		sort(in[i].begin(),in[i].end(),cmp);
	}
	RT = 1;
	dfs(1);
	cout<<(res-n)/2+n<<"\n";
}
signed main(){
	int T = read();
	while(T--){
		init();
	}
	return 0;
}
```


---

## 作者：command_block (赞：6)

**题意**:

有 $n$ 个灯泡,用红色边连成一棵红色树,再用蓝色边连成一棵蓝色树。

问有多少个灯泡的子集,在红色树上形成联通块,在蓝色树上形成一条链。

多组数据, $T\leq 3,n\leq 10^5$ ,时限$\texttt{5s}$。

------------

好的套路题。

**结论** : 树上点集形成的连通块个数为 : 点数$-$点集内部的边数。

- 蓝色树为链

考虑逐步移动蓝色区间的 $r$ ,用数据结构维护 $l$。

记 $R[i]$ 为左端点为 $l$ 时形成的连通块个数。

当加入 $r$ 点时,所有区间都会加入一个点,给 $R[1,r]$ 加一。

对于每个红树上的邻居 $u$ 因为 $l\in [1,u]$ 时会包含该点,也就会新产生一条边,将 $R[1,u]$ 减一。

我们需要统计 $1$ 的个数,不难发现 $R$ 中最小值总是 $1$ ,只需要统计最小值个数即可。

度数的总和是 $O(n)$ 的,复杂度为 $O(n\log n)$。

- 一般情况

先对于每个点 $u$ ,维护当前 $p$ 点到 $u$ 的链形成几个联通块。对于 $p=1 $的情况,使用一次 `dfs` 预先计算。

考虑类似换根的操作,将 $p$ 按照 `dfs` 的顺序移动。其中的一步移动如图 :

![](https://cdn.luogu.com.cn/upload/image_hosting/xqqc5pph.png)

那么,蓝色部分的链都需要增加红点,而红色部分的链都需要删去蓝点。

枚举红点在红树上的邻居 $u$ ,当链端点在 $u$ 的子树 (默认树以 $p$ 为根) 中,才会包含 $u$ ,也就包含了一条新的链。

所以删除和增加操作对应着若干个子树修改。

在换根的情况下如何子树修改 : [[DS记录]P3979 遥远的国度](https://www.luogu.com.cn/blog/command-block/ds-ji-lu-p3979-yao-yuan-di-guo-du)

问题在于,我们只能在相邻的两个点之间移动,对于度数大的点,会反复经过很多次,若其在红树度数也很大,复杂度将会退化。

在如上图 $p$ 点的儿子间处理时,“给蓝色部分删去红点”这一步,每个红点只会做一次,复杂度没问题。

复杂度分析的瓶颈在于需要删去 $O($儿子数量$)$ 次的蓝点。

我们发现,枚举红树邻居时,还附带着在红色子树内的要求,否则没有贡献。而同一个点的各个儿子的子树显然是不交的。

我们可以先把邻居按照 `dfs` 序排序,这样每次只需要处理一段的点就可以了。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define ll long long
#define pb push_back
#define MaxN 100500
using namespace std;
int read(){
  int X=0;char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
struct Node{
  int m,c,tg;
  inline void ladd(int add)
  {m+=add;tg+=add;}
}a[MaxN<<2];
inline void up(int u){
  int l=u<<1,r=u<<1|1;
  a[u].m=min(a[l].m,a[r].m);
  a[u].c=(a[l].m==a[r].m) ? a[l].c+a[r].c
        :(a[l].m<a[r].m ? a[l].c : a[r].c);
}
int n,R[MaxN],tp[MaxN];
void build(int l=1,int r=n,int u=1)
{
  a[u].tg=0;
   if (l==r){
    a[u].m=R[tp[l]];
    a[u].c=1;return ;
  }int mid=(l+r)>>1;
  build(l,mid,u<<1);
  build(mid+1,r,u<<1|1);
  up(u);
}
inline void ladd(int u){
  if (a[u].tg){
    a[u<<1].ladd(a[u].tg);
    a[u<<1|1].ladd(a[u].tg);
    a[u].tg=0;
  }   
}
int wfl,wfr,wfc;
void add(int l=1,int r=n,int u=1)
{
  if (wfl<=l&&r<=wfr)
    {a[u].ladd(wfc);return ;}
  int mid=(l+r)>>1;ladd(u);
  if (wfl<=mid)add(l,mid,u<<1);
  if (mid<wfr)add(mid+1,r,u<<1|1);
  up(u);
}
vector<int> g[MaxN],g2[MaxN];
int dfn[MaxN],out[MaxN],tim,f[17][MaxN],dep[MaxN];
void pfs(int u)
{
  tp[dfn[u]=++tim]=u;
  for (int i=0,v;i<g[u].size();i++)
    if (!dfn[v=g[u][i]]){
      dep[v]=dep[u]+1;
      f[0][v]=u;
      pfs(v);
    }
  out[u]=tim;
}
void pfs2(int u)
{
  for (int i=0,v;i<g2[u].size();i++){
    v=g2[u][i];
    if (dfn[v]<=dfn[u]&&dfn[u]<=out[v])
      R[u]--;
  }
  for (int i=0,v;i<g[u].size();i++)
    if (dfn[v=g[u][i]]>dfn[u]){
      R[v]=R[u]+1;
      pfs2(v);
    }
}
int las(int u,int v){
  int k=16;
  while(k--)
    while(dep[f[k][u]]>dep[v])
      u=f[k][u];
  return u;
}
struct Data{
  int l,r,c;
  void undo()
  {wfl=l;wfr=r;wfc=-c;add();}
}stk[MaxN<<2];
int top;
#define pre(x,y,c) {\
  wfl=x;wfr=y;wfc=c;\
  stk[++top]=(Data){wfl,wfr,wfc};\
}
void upd(int u,int c)
{
  for (int i=0,v;i<g2[u].size();i++){
    v=g2[u][i];
    if (dfn[v]<dfn[u]||out[u]<dfn[v]){
      if (dfn[v]<=dfn[u]&&dfn[u]<=out[v]){
        int t=las(u,v);
        if (1<dfn[t]){pre(1,dfn[t]-1,c);add();}
        if (out[t]<n){pre(out[t]+1,n,c);add();}
      }else {pre(dfn[v],out[v],c);add();}
    }
  }
}
bool cmp(int A,int B)
{return dfn[A]<dfn[B];}
ll ans;
void dfs(int u)
{
  ans+=a[1].c;
  sort(g2[u].begin(),g2[u].end(),cmp);
  int sav=top;
  for (int i=0,v,p=0;i<g[u].size();i++)
    if (dfn[v=g[u][i]]>dfn[u]){
      a[1].ladd(1);upd(v,-1);
      pre(dfn[v],out[v],-2);wfc=-2;add();
      for (int r;p<g2[u].size()&&dfn[r=g2[u][p]]<=out[v];p++)
        if (dfn[v]<=dfn[r])
          {pre(dfn[r],out[r],1);add();}
      dfs(v);
      a[1].ladd(-1);
      while(top>sav)stk[top--].undo();
    }
}
void clear()
{
  for (int i=1;i<=n;i++){
    g[i].clear();g2[i].clear();
    dfn[i]=0;
  }ans=tim=0;
}
void solve()
{
  n=read();
  for (int i=1,fr,to;i<n;i++){
    fr=read();to=read();
    g2[fr].pb(to);g2[to].pb(fr);
  }for (int i=1,fr,to;i<n;i++){
    fr=read();to=read();
    g[fr].pb(to);g[to].pb(fr);   
  }dep[1]=1;pfs(1);
  for (int j=1;j<16;j++)
    for (int i=1;i<=n;i++)
      f[j][i]=f[j-1][f[j-1][i]];
  R[1]=1;pfs2(1);build();
  ans=0;dfs(1);
  printf("%lld\n",(ans+n)/2);
  clear();
}
int main()
{
  int T=read();
  while(T--)solve();
  return 0;
}
```



---

## 作者：lgswdn_SA (赞：2)

这是一个关于和同学想了好久点分治并把两个人都给想晕（生物意义上）然后转换思路后发现解法和点分治并没有什么关系的故事。这个故事告诉我们，不要在一个树枝上吊死。死前好歹想想别的做法。被两年半前的高爸吊着打。

首先考虑链如何做。相当于统计有多少区间 $[l,r]$ 满足在另一棵树上区间的所有点连通。这种统计区间的题目可以考虑用类似扫描线的做法。对于目前扫描线所在的点 $i$，用一棵线段树维护 $[j,i]$ 区间的连通块数量 $a_j$。加进来 $i$ 后，看会有什么影响。

1. 所有点会加上 $1$。
2. 然后我们连边。对于所有满足 $x<i$ 的树边 $(x,i)$，我们发现连上后仅会影响 $[1,x]$ 的 $a$ 值。更进一步，这个变化是所有 $a_1,\dots, a_x$ 会减少一。
3. 统计贡献。连通块个数即 $a_j=1$ 的个数（通过维护最小值和最小值个数得到）。

然后我们把这个做法搬到树上来。搜到 $u$ 时，维护全树的 $v$，求其到 $u$ 的链在另一棵树上的连通块值。也就是说，我们需要去支持换根。这个并不困难。由于无论是加一个点还是删一个点，都对应着一个子树的减或加，所以我们在 dfs 序上修改，每个子树（无论以哪个节点为根）都可以拆分成至多两个区间的操作。

再理一下我们把根从 $u$ 换成 $v$ 需要的操作（红边为 $A$ 树上的边了，蓝边为 $B$ 树上的边）

1. （$u$ 为根）将满足 $x\in T_v$ 的红边 $(u,x)$ 全部删除，即对于这些 $x$，对它们进行一次子树加一。
2. （$u$ 为根）对于 $x\in T_v$ 的点，它们到根的链上不再有 $u$ 了。于是对于 $v$，我们做一次子树减一。
3. 将根换成 $v$。这一步不需有任何操作。
4. （$v$ 为根）对于 $x\in T_u$ 的点，它们到根上的链会多出了 $v$。于是对于 $u$，我们做一次子树加一。
5. （$v$ 为根）将满足 $x\in T_u$ 且 $x\notin T_v$ 的红边 $(v,x)$ 全部加入，即对于这些 $x$，对它们进行一次子树减一。（这一个操作要分三种情况讨论：$x$ 是 $u$ 的祖先，$x=u$，和其他情况）

容易发现，如果暴力找 $x$ 是假的，因为每个数都需要找红树上度数乘蓝树上度数次。但是我们冷静思考一下，$u$ 换根到 $v$ 时，删除 $(u,x)$ 时修改的节点必然是在 $T_v$ 内的。也就是说，我们可以先对每个点的红色出边按照蓝树 dfn 序排序，然后直接定位到 $T_v$ 区间内，找到那些点即可；而添加 $(v,x)$ 时我们暴力枚举就行了。

```cpp
const int N=1e5+9;
int T,n,st[N],ed[N],tick,ans;
vi a[N],b[N],son[N];

namespace SegT {
    int ls[N<<1],rs[N<<1],tag[N<<1],tot;
    pii s[N<<1];
    pii operator + (pii &a,pii &b) {
        if((!a.se)||(!b.se)) return a.se?a:b;
        else if(a.fi==b.fi) return pii(a.fi,a.se+b.se);
        else return a.fi<b.fi?a:b;
    }
    void build(int p,int l,int r) {
        s[p]=pii(0,r-l+1); tag[p]=0;
        if(l==r) return; int mid=l+r>>1;
        build(ls[p]=++tot,l,mid), build(rs[p]=++tot,mid+1,r);
    }
    void init() {
        tot=1;
        build(1,1,n);
    }
    void pushdown(int p) {
        if(!tag[p]) return;
        s[ls[p]].fi+=tag[p], s[rs[p]].fi+=tag[p];
        tag[ls[p]]+=tag[p], tag[rs[p]]+=tag[p];
        tag[p]=0;
    }
    void add(int p,int l,int r,int x,int y,int z) {
        if(x>y) return;
        if(l==x&&r==y) {s[p].fi+=z,tag[p]+=z; return;} int mid=l+r>>1;
        pushdown(p);
        if(y<=mid) add(ls[p],l,mid,x,y,z);
        else if(x>mid) add(rs[p],mid+1,r,x,y,z);
        else add(ls[p],l,mid,x,mid,z), add(rs[p],mid+1,r,mid+1,y,z);
        s[p]=s[ls[p]]+s[rs[p]]; 
    }
    int qry() {
        return s[1].se;
    }
}

bool cmpd(int x,int y) {
    return st[x]<st[y];
}
void clear() {
    rep(i,1,n) st[i]=ed[i]=0; tick=0;
    rep(i,1,n) a[i].clear(), b[i].clear(), son[i].clear();
    SegT::init();
    ans=0;
}
void readin() {
    rep(i,2,n) {
        int u=read(), v=read();
        a[u].emplace_back(v), a[v].emplace_back(u);
    }
    rep(i,2,n) {
        int u=read(), v=read();
        b[u].emplace_back(v), b[v].emplace_back(u);
    }
}

bool in(int x,int y) { //y \in T_x
    return st[x]<=st[y]&&ed[y]<=ed[x];
}
void predfs(int u,int fa) { //计算dfn和求出son
    st[u]=++tick;
    for(auto v:b[u]) if(v!=fa) {
        predfs(v,u);
        son[u].emplace_back(v);
    }
    ed[u]=tick;
}
void dfs1(int u) { //先把u=1的情况维护出来
    for(auto v:son[u]) {
        dfs1(v);
    }
    SegT::add(1,1,n,st[u],ed[u],1);
    for(auto v:a[u]) if(in(u,v)) {
        SegT::add(1,1,n,st[v],ed[v],-1);
    }
}
void dfs2(int u) {
    int x=0; ans+=SegT::qry();
    while(x<a[u].size()&&!in(u,a[u][x])) x++;
    for(auto v:son[u]) {
        stack<pair<pii,int> >op; //用栈记录操作之后方便撤销
        while(x<a[u].size()&&in(v,a[u][x])) { //Operation 1
            SegT::add(1,1,n,st[a[u][x]],ed[a[u][x]],1);
            op.push(make_pair(pii(st[a[u][x]],ed[a[u][x]]),-1));
            x++;
        }
        SegT::add(1,1,n,st[v],ed[v],-1); //Operation 2
        op.push(make_pair(pii(st[v],ed[v]),1));
        SegT::add(1,1,n,1,st[v]-1,1), SegT::add(1,1,n,ed[v]+1,n,1); //Operation 4
        op.push(make_pair(pii(1,st[v]-1),-1)), op.push(make_pair(pii(ed[v]+1,n),-1));
        for(auto x:a[v]) if(!in(v,x)) { //Operation 5
            if(in(x,u)&&x!=u) {
                int l=0,r=son[x].size()-1,y=-1;
                while(l<=r) {
                    int mid=l+r>>1;
                    if(st[son[x][mid]]<=st[u]) y=son[x][mid], l=mid+1;
                    else r=mid-1;
                }
                SegT::add(1,1,n,1,st[y]-1,-1), SegT::add(1,1,n,ed[y]+1,n,-1);
                op.push(make_pair(pii(1,st[y]-1),1)), op.push(make_pair(pii(ed[y]+1,n),1));
            } else if(x==u) {
                SegT::add(1,1,n,1,st[v]-1,-1), SegT::add(1,1,n,ed[v]+1,n,-1);
                op.push(make_pair(pii(1,st[v]-1),1)), op.push(make_pair(pii(ed[v]+1,n),1));
            } else {
                SegT::add(1,1,n,st[x],ed[x],-1);
                op.push(make_pair(pii(st[x],ed[x]),1));
            }
        }
        dfs2(v);
        while(!op.empty()) {
            auto x=op.top(); op.pop();
            SegT::add(1,1,n,x.fi.fi,x.fi.se,x.se);
        }
    }
}

signed main() {
    T=read();
    while(T--) {
        n=read();
        clear();
        readin();
        predfs(1,0);
        rep(i,1,n) sort(a[i].begin(),a[i].end(),cmpd);
        dfs1(1);
        dfs2(1);
        printf("%lld\n",(ans+n)/2);
    }
    return 0;
}
```

---

## 作者：Luciylove (赞：1)

## Out of problem

写这个题一半是为了表达敬仰吧。

再高没有______

怎么没有人写 $O(\log^2 n)$，明显好写很多好不好/kk

## Solution

考虑 dsu on tree。

我们利用 $V -E = 1$ 来数连通块吗，并联想到线段树维护最小值来维护之。

我们称 $B$ 树为主树，$A$ 树为副树。

考虑每条副树的边都挂在主树上，然后 dsu on tree 的时候不清空所有的「祖先-后代链」边。

然后不是这样的边我们在 dfs 序大的那一端统计就好了。

换根做法确实强。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define lc x << 1
#define rc x << 1 | 1

using namespace std;

const int _ = 1e5 + 5, mod = 1e9 + 7;

int read () {
    int ans = 0; char c = getchar(), last = ' ';
    while(c < '0' || c > '9') last = c,c = getchar();
    while(c >= '0' && c <= '9') ans = (ans << 1) + (ans << 3) + c - '0',c = getchar();
    return last == '-' ? - ans : ans;
}
int power (int x, int y) {
	int ret = 1;
	for ( ; y; y >>= 1, x = 1ll * x * x % mod)
		if (y & 1) ret = 1ll * ret * x % mod;
	return ret;
}

int T;
int n, m;

int tr[_ << 2], tag[_ << 2], cnt[_ << 2];
void apply (int x, int k) { tr[x] += k, tag[x] += k; }
void pushdown (int x) {
	if (tag[x]) 
		apply(lc, tag[x]), apply(rc, tag[x]), tag[x] = 0;
}
void pushup (int x) {
	tr[x] = min(tr[lc], tr[rc]);
	cnt[x] = (tr[x] == tr[lc]) * cnt[lc] + (tr[x] == tr[rc]) * cnt[rc];
}
void modify (int x, int l, int r, int ql, int qr, int k) {
	if (ql <= l && r <= qr) return apply(x, k);
	int mid = (l + r) >> 1; pushdown(x);
	if (ql <= mid) modify(lc, l, mid, ql, qr, k);
	if (qr > mid) modify(rc, mid + 1, r, ql, qr, k);
	return pushup(x);
}
int query (int x, int l, int r, int ql, int qr) {
	if (tr[x] > 1) return 0;
	if (ql <= l && r <= qr) return cnt[x];
	int mid = (l + r) >> 1, ret = 0; pushdown(x);
	if (ql <= mid) ret += query(lc, l, mid, ql, qr);
	if (qr > mid) ret += query(rc, mid + 1, r, ql, qr);
	return ret;
}
void build (int x, int l, int r) {
	tag[x] = tr[x] = 0, cnt[x] = r - l + 1;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build(lc, l, mid), build(rc, mid + 1, r);
}

int dfc;
int dep[_], sz[_], son[_], dfn[_], ed[_], pa[_], top[_];
int Px[_], Py[_];

vector <int> e[_];
void dfs1 (int x, int fa) {
	pa[x] = fa, sz[x] = 1, dep[x] = dep[fa] + 1, son[x] = 0;
	for (int y : e[x]) {
		if (y == fa) continue ; 
		dfs1(y, x), sz[x] += sz[y];
		if (sz[y] > sz[son[x]]) son[x] = y;
	}
}
void dfs2 (int x, int tp) {
	top[x] = tp, dfn[x] = ++ dfc;
	if (son[x]) dfs2(son[x], tp);
	for (int y : e[x]) if (!dfn[y]) dfs2(y, y);
	ed[x] = dfc;
}
int LCA (int x, int y) {
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = pa[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
vector <pair<int, int> > vc[_];
long long ret = 0;

int vL, vR;
void ins (int x, int rt) {
	for (auto [y, lca] : vc[x]) 
		if (y == rt) modify(1, 1, n, dfn[x], ed[x], -1);
	for (int y : e[x]) if (y ^ pa[x]) ins(y, rt);
}
void qry (int x, int rt, long long &S) {
	modify(1, 1, n, 1, n, 1);
	for (auto [y, lca] : vc[x]) {
		if (y == lca && dep[lca] >= dep[rt]) modify(1, 1, n, 1, n, -1);
		else if (lca == rt && dfn[y] < dfn[x]) modify(1, 1, n, dfn[y], ed[y], -1);
	}
	S += query(1, 1, n, vL, vR);
	for (int y : e[x]) if (y ^ pa[x]) qry(y, rt, S);
	modify(1, 1, n, 1, n, -1);
	for (auto [y, lca] : vc[x]) 
		if (y == lca && dep[lca] >= dep[rt]) modify(1, 1, n, 1, n, 1);
		else if (lca == rt && dfn[y] < dfn[x]) modify(1, 1, n, dfn[y], ed[y], 1);
}

void solve (int x) {
	for (int y : e[x]) if (y ^ pa[x] && y ^ son[x]) solve(y);
	modify(1, 1, n, dfn[x], dfn[x], 1);
	if (son[x]) {
		solve(son[x]);
		modify(1, 1, n, dfn[son[x]], ed[son[x]], 1);
		for (auto [y, lca] : vc[x]) 
			if (dfn[son[x]] <= dfn[y] && ed[y] <= ed[son[x]]) {
				modify(1, 1, n, dfn[y], ed[y], -1);
			}
		long long S = query(1, 1, n, dfn[son[x]], ed[son[x]]);
		ret += S;
	}
	vL = dfn[x], vR = ed[son[x]];
	for (int y : e[x]) 
		if (y ^ son[x] && y ^ pa[x]) {
			long long S = 0;
			qry(y, x, S), ret += S;
			modify(1, 1, n, dfn[y], ed[y], 1);
			ins(y, x), vR = ed[y];
		}
}
int main () {
	// freopen("gen.in", "r", stdin);
	// freopen("sol.out", "w", stdout);
	T = read();
	while (T --) {
		n = read(), ret = dfc = 0;
		rep(i, 1, n) e[i].clear(), vc[i].clear(), dfn[i] = 0;
		rep(i, 1, n - 1) Px[i] = read(), Py[i] = read();
		rep(i, 1, n - 1) {
			int x = read(), y = read();
			e[x].push_back(y), e[y].push_back(x);
		}
		build(1, 1, n), dfs1(1, 0), dfs2(1, 1);
		rep(i, 1, n - 1) {
			int x = Px[i], y = Py[i], lca = LCA(x, y);
			vc[x].push_back({y, lca}), vc[y].push_back({x, lca});
		}
		solve(1);
		printf("%lld\n", (ret + n));
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：1)

看到这个题回想起四年前我还是个小朋友的时候在 luogu 举办的 SHjOI，当时对于那些大神永远都只能是仰望。如今 UM，lgd，glx 等等各位前辈也都结束了自己的最后一场 NOI。Past Glory 很快也就荣光不再了，可是即将正为正式选手的自己看起来完全没有准备好成为 Present Glory 啊...

首先考虑 70 分的链怎么做：对右端点进行扫描线，用一棵线段树维护每个左端点对应的「点数 - 边数」，那么每次就是进行若干个区间加，查询最小值个数。时间复杂度 $\mathcal O(n\log n)$。

把这个做法推广到树上。考虑 dfs 一个端点，维护另一个端点对应的「点数 - 边数」，每次一条红边带来的贡献是一个子树 $-1$（注意可能是在不同根意义下的）。那么我们在将根从 $u$ 换到 $v$ 的时候，枚举 $u$ 往 $v$ 子树方向的红边和 $v$ 往 $v$ 子树外方向的红边并进行更新。直接枚举复杂度容易退化成 $\mathcal O(\sum deg_i^2)$，但是由于均摊次数是 $\mathcal O(n)$ 的，所以可以先把所有的红边按照 dfs 序排序，用个指针扫过去就行了。时间复杂度 $\mathcal O(n\log n)$。

给 z 宝讲做法的时候他听完 dfs 一个端点之后就把做法报完了，并表示后面那个复杂度退化的避免是显然的。可能这就是 CNOI 的 Future Glory 吧。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=1e5+9,INF=1e9;
ll T,n,U[N],V[N],ans,dfn[N],tim,sz[N];
ll mn[N<<2],cnt[N<<2],tag[N<<2];
vector<ll>to[N],es[N],vson[N];
void Build(ll x,ll l,ll r){
    mn[x]=INF,cnt[x]=r-l+1,tag[x]=0;
    if(l==r)return ;
    ll mid=(l+r)>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
}
void Pushup(ll x){
    mn[x]=min(mn[x<<1],mn[x<<1|1]);
    cnt[x]=cnt[x<<1]*(mn[x<<1]==mn[x])+cnt[x<<1|1]*(mn[x<<1|1]==mn[x]);
}
void Pushtag(ll x,ll k){
    mn[x]+=k,tag[x]+=k;
}
void Pushdown(ll x){
    if(!tag[x])return ;
    Pushtag(x<<1,tag[x]);
    Pushtag(x<<1|1,tag[x]);
    tag[x]=0;
}
void Upd(ll x,ll l,ll r,ll ql,ll qr,ll k){
    if(l>qr||r<ql||ql>qr)return ;
    if(ql<=l&&r<=qr){
        Pushtag(x,k);
        return ;
    }
    Pushdown(x);
    ll mid=(l+r)>>1;
    Upd(x<<1,l,mid,ql,qr,k);
    Upd(x<<1|1,mid+1,r,ql,qr,k);
    Pushup(x);
}
void dfs1(ll x,ll f){
    dfn[x]=++tim,sz[x]=1;
    for(ll y:to[x]){
        if(y==f)continue;
        dfs1(y,x);
        vson[x].push_back(y);
        sz[x]+=sz[y];
    }
}
bool In(ll x,ll y){
    return dfn[x]<=dfn[y]&&dfn[y]<=dfn[x]+sz[x]-1;
}
void dfs2(ll x){
    for(ll y:vson[x])dfs2(y);
    Upd(1,1,n,dfn[x],dfn[x]+sz[x]-1,1);
    for(ll y:es[x]){
        if(In(x,y))Upd(1,1,n,dfn[y],dfn[y]+sz[y]-1,-1);
    }
}
void dfs3(ll x){
    ans+=cnt[1];
    ll p=0;
    while(p<(ll)es[x].size()&&!In(x,es[x][p]))p++;
    for(ll y:vson[x]){
        vector<pair<pii,ll> >v;
        while(p<(ll)es[x].size()&&In(y,es[x][p])){
            Upd(1,1,n,dfn[es[x][p]],dfn[es[x][p]]+sz[es[x][p]]-1,1);
            v.push_back({{dfn[es[x][p]],dfn[es[x][p]]+sz[es[x][p]]-1},-1});
            p++;
        }
        Upd(1,1,n,dfn[y],dfn[y]+sz[y]-1,-1);
        v.push_back({{dfn[y],dfn[y]+sz[y]-1},1});
        Upd(1,1,n,1,dfn[y]-1,1);
        Upd(1,1,n,dfn[y]+sz[y],n,1);
        v.push_back({{1,dfn[y]-1},-1});
        v.push_back({{dfn[y]+sz[y],n},-1});
        for(ll z:es[y]){
            if(!In(y,z)){
                if(In(z,x)&&z!=x){
                    ll l=0,r=vson[z].size()-1,q=-1;
                    while(l<=r){
                        ll mid=(l+r)>>1;
                        if(dfn[vson[z][mid]]<=dfn[x])q=vson[z][mid],l=mid+1;
                        else r=mid-1;
                    }
                    Upd(1,1,n,1,dfn[q]-1,-1);
                    Upd(1,1,n,dfn[q]+sz[q],n,-1);
                    v.push_back({{1,dfn[q]-1},1});
                    v.push_back({{dfn[q]+sz[q],n},1});
                }
                else if(z==x){
                    Upd(1,1,n,1,dfn[y]-1,-1);
                    Upd(1,1,n,dfn[y]+sz[y],n,-1);
                    v.push_back({{1,dfn[y]-1},1});
                    v.push_back({{dfn[y]+sz[y],n},1});
                }
                else {
                    Upd(1,1,n,dfn[z],dfn[z]+sz[z]-1,-1);
                    v.push_back({{dfn[z],dfn[z]+sz[z]-1},1});
                }
            }
        }
        dfs3(y);
        for(pair<pii,ll> p:v)Upd(1,1,n,p.first.first,p.first.second,p.second);
    }
}
void solve(){
    n=read();
    rep(i,0,n+1)to[i].clear(),es[i].clear(),vson[i].clear();
    rep(i,2,n)U[i]=read(),V[i]=read();
    tim=0,ans=0;
    rep(i,2,n){
        es[U[i]].push_back(V[i]);
        es[V[i]].push_back(U[i]);
    }
    rep(i,2,n){
        ll x=read(),y=read();
        to[x].push_back(y);
        to[y].push_back(x);
    }
    Build(1,1,n);
    dfs1(1,0);
    rep(i,1,n){
        sort(es[i].begin(),es[i].end(),[&](ll x,ll y){
            return dfn[x]<dfn[y];
        });
    }
    dfs2(1);
    dfs3(1);
    write((ans+n)/2),putchar('\n');
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

