# 『MdOI R1』Treequery

## 题目描述

给定一棵 $n$ 个点的无根树，边有边权。

令 $E(x,y)$ 表示树上 $x,y$ 之间的简单路径上的所有边的集合，特别地，当 $x=y$ 时，$E(x,y) = \varnothing$。

你需要 **实时** 回答 $q$ 个询问，每个询问给定 $p,l,r$，请你求出集合 $\bigcap_{i=l}^r E(p,i)$ 中所有边的边权和，即 $E(p, l\dots r)$ 的交所包含的边的边权和。

通俗的讲，你需要求出 $p$ 到 $[l,r]$ 内每一个点的简单路径的公共部分长度。



## 说明/提示

【样例 1 说明】

样例中的树如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/g6l15zpv.png)

下面解释中的询问参数均为异或 $lastans$ 之后得到的真实值。

对于第一个询问，$p=2$，$l=3$，$r=5$，$\bigcap_{i=3}^5 E(2,i)$ 为边 $(2,3)$，长度为 $3$。

对于第二个询问，$p=1$，$l=2$，$r=4$，$\bigcap_{i=2}^4 E(1,i)$ 为边 $(1,3)$，长度为 $2$；

对于第三个询问，$p=2$，$l=5$，$r=5$，$\bigcap_{i=5}^5 E(2,i)$ 为边集 $\{(2,3),(3,1),(1,5)\}$，长度为 $6$；

对于第四个询问，$p=3$，$l=3$，$r=4$，$\bigcap_{i=3}^4 E(3,i)=\varnothing$，长度为 $0$。


---

【数据范围】

**本题采用捆绑测试。**

| 子任务编号 |   $n,q\leq$    | 特殊性质 | 分值 |
| :--------: | :------------: | :------: | :--: |
|     1      |     $10^5$     |  $l=r$   |  8   |
|     2      |     $10^5$     |  $p=1$   |  20  |
|     3      |     $10^3$     |    无    |  20  |
|     4      |     $10^5$     |    无    |  26  |
|     5      | $2\times 10^5$ |    无    |  26  |

对于 $100\%$ 的数据，$1\leq n,q\leq 2\times 10^5$，$1\leq x,y,p\leq n$，$1\leq l\leq r\leq n$，$1\leq w\leq 10^4$。

## 样例 #1

### 输入

```
5 4
3 1 2
1 5 1
2 3 3
3 4 4
2 3 5
2 1 7
0 7 7
5 5 2```

### 输出

```
3
2
6
0```

## 样例 #2

### 输入

```
10 10
2 1 9907
3 2 8329
4 2 8402
5 4 3636
6 4 8747
7 4 3080
8 6 780
9 6 5414
10 9 3545
2 10 10
26107 26106 26101
4 9 10
14171 14166 14169
8958 8949 8949
36008 36014 36013
11485 11485 11472
3 9 9
30888 30894 30895
8404 8404 8411
```

### 输出

```
26108
0
14161
8959
36015
11482
0
30892
8402
0
```

# 题解

## 作者：Owen_codeisking (赞：21)

好像没人写 $O(n\log n)$ 的解法。。。其实也不难调。。。

首先以 $1$ 为根时的 dfs 序先求出来，那么假定以 $p$ 为根时的 dfs 序为 $[id_x,n]∪[1,id_x)$。

这样的话就只用求出最小和最大的点就行了。

我们建出主席树，在主席树上二分，找到这两个点，有这么几种情况：

1. 这两个点在子树内，$ans=dis_{lca(x,y)}-dis_p$

2. 这两个点一个在子树内，一个在子树外，$ans=0$

3. 这两个点都在子树外：

(1) $lca(x,p)==lca(y,p),ans=dis_{lca(x,y)}+dis_p-2\times dis_{lca(x,p)}$

(2) $dep_{lca(x,p)}>dep_{lca(y,p)},ans=dis_p-dis_{lca(x,p)}$

实测没有 $O(n\log^2 n)$ 快（丢脸），不过我用的是倍增 lca，主席树也没有封装。用其他的写法可能会快一些。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define fi first
#define se second
const int maxn=200005;
int n,m,dep[maxn],dis[maxn],f[maxn][19],st[maxn],ed[maxn],mp[maxn],tim;
int rt[maxn],ls[maxn*20],rs[maxn*20],sum[maxn*20],sz;
vector<pii> g[maxn];
void dfs(int x,int ff)
{
	f[x][0]=ff,dep[x]=dep[ff]+1,st[x]=++tim,mp[tim]=x;
	for(int i=1;i<=17;i++) f[x][i]=f[f[x][i-1]][i-1];
	for(auto y:g[x])
		if(y.fi!=ff)
			dis[y.fi]=dis[x]+y.se,dfs(y.fi,x);
	ed[x]=tim;
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=18;i>=0;i--)
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=18;i>=0;i--)
		if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
void update(int &u,int v,int l,int r,int t)
{
	u=++sz,ls[u]=ls[v],rs[u]=rs[v],sum[u]=sum[v]+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(t<=mid) update(ls[u],ls[v],l,mid,t);
	else update(rs[u],rs[v],mid+1,r,t);
}
int query_min(int u,int v,int l,int r,int x,int y)
{
	if(x>y) return -1;
	if(l==r) return (sum[u]==sum[v])?-1:mp[l];
	if(x<=l && r<=y)
	{
		int mid=(l+r)>>1;
		if(sum[ls[v]]-sum[ls[u]]>0)
			return query_min(ls[u],ls[v],l,mid,x,y);
		if(sum[rs[v]]-sum[rs[u]]>0)
			return query_min(rs[u],rs[v],mid+1,r,x,y);
		return -1;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
	{
		int res=query_min(ls[u],ls[v],l,mid,x,y);
		if(res!=-1) return res;
	}
	if(y>mid)
	{
		int res=query_min(rs[u],rs[v],mid+1,r,x,y);
		if(res!=-1) return res;
	}
	return -1;
}
int query_max(int u,int v,int l,int r,int x,int y)
{
	if(x>y) return -1;
	if(l==r) return (sum[u]==sum[v])?-1:mp[l];
	if(x<=l && r<=y)
	{
		int mid=(l+r)>>1;
		if(sum[rs[v]]-sum[rs[u]]>0)
			return query_max(rs[u],rs[v],mid+1,r,x,y);
		if(sum[ls[v]]-sum[ls[u]]>0)
			return query_max(ls[u],ls[v],l,mid,x,y);
		return -1;
	}
	int mid=(l+r)>>1;
	if(y>mid)
	{
		int res=query_max(rs[u],rs[v],mid+1,r,x,y);
		if(res!=-1) return res;
	}
	if(x<=mid)
	{
		int res=query_max(ls[u],ls[v],l,mid,x,y);
		if(res!=-1) return res;
	}
	return -1;
}
int query_sum(int u,int v,int l,int r,int x,int y)
{
	if(x<=l && r<=y) return sum[v]-sum[u];
	int mid=(l+r)>>1,ans=0;
	if(x<=mid) ans+=query_sum(ls[u],ls[v],l,mid,x,y);
	if(y>mid) ans+=query_sum(rs[u],rs[v],mid+1,r,x,y);
	return ans;
}
inline int solve1(int x,int l,int r)
{
	int res=query_min(rt[l-1],rt[r],1,n,st[x],n);
	if(res!=-1) return res;
	return query_min(rt[l-1],rt[r],1,n,1,st[x]-1);
}
inline int solve2(int x,int l,int r)
{
	int res=query_max(rt[l-1],rt[r],1,n,1,st[x]-1);
	if(res!=-1) return res;
	return query_max(rt[l-1],rt[r],1,n,st[x],n);
}
inline int solve(int x,int l,int r)
{
	int sum=query_sum(rt[l-1],rt[r],1,n,st[x],ed[x]);
	if(sum>0 && sum<r-l+1) return 0;
	int a=solve1(x,l,r),b=solve2(x,l,r);
	if(sum==r-l+1) return dis[LCA(a,b)]-dis[x];
	int c=LCA(a,x),d=LCA(b,x);
	if(c==d) return dis[LCA(a,b)]+dis[x]-2*dis[c];
	return dis[x]-((dep[c]>dep[d])?dis[c]:dis[d]);
}
int main()
{
	scanf("%d%d",&n,&m);
	int x,y,w,l,r,lastans=0;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&w);
		g[x].push_back(pii(y,w));
		g[y].push_back(pii(x,w));
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) rt[i]=rt[i-1],update(rt[i],rt[i],1,n,st[i]);
	while(m--)
	{
		scanf("%d%d%d",&x,&l,&r);
		x^=lastans,l^=lastans,r^=lastans;
		printf("%d\n",lastans=solve(x,l,r));
	}
	return 0;
}
```

---

## 作者：Thinking (赞：17)

（在接下来的描述和图片中，用$dis_u$表示根（1号点）到$u$的路径的边权和；$[l,r]$范围内的点用蓝色表示，$p$用红色表示）

我们考虑$lca_{l,l+1,\cdots,r}$（以下记为$lca$，用橙色表示），有以下情况：

**1.$lca$为$p$的孩子（或$p$）**

![](https://cdn.luogu.com.cn/upload/image_hosting/8r0je99a.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这表明$[l,r]$均为$p$的孩子（或$p$），那么答案为$dis_{lca}-dis_p$

**2.$[l,r]$中既有$p$的孩子（或$p$），又有点不是$p$的孩子（或$p$）**

![](https://cdn.luogu.com.cn/upload/image_hosting/xnt6oizl.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么这两种点到$p$的路径无公共边，答案为0

**3.$[l,r]$中没有$p$的孩子**

这种情况较为复杂，我们还要找出$p$的祖先中最深的一个点，使它也为$[l,r]$中至少一点的祖先（即$lca_{p,l},lca_{p,l+1},\cdots,lca_{p,r}$中最深的一个，以下记为$fa$，用黄色表示）

它和$lca$的位置关系有两种情况：

**3.1.它是$lca$的祖先**

![](https://cdn.luogu.com.cn/upload/image_hosting/5rga0jze.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

答案为$dis_p+dis_{lca}-2dis_{fa}$

**3.2.它是$lca$的孩子**

![](https://cdn.luogu.com.cn/upload/image_hosting/dnp84h93.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

答案为$dis_p-dis_{fa}$

分析完毕。接下来研究如何实现：

求$lca$：树链剖分+线段树。

判断一个点的孩子中是否有$[l,r]$中的点：用线段树合并配合可持久化就可以在线处理。

求$fa$：从$p$开始，沿着重链向上跳，发现这条链上有答案时再在链上二分一下。

时间复杂度$O(nlogn+qlog^2n)$，空间复杂度$O(nlogn)$。

这样就可以愉快地上代码了：

```cpp
#include<cstdio>
#define For(i,A,B) for(i=(A);i<=(B);++i)
#define Go(u) for(i=G[u];i;i=nxt[i])if((v=to[i])!=f[u])
const int N=200050;
char rB[1<<21],*rS,*rT,wB[(1<<21)+50];
int wp=-1;
inline char gc(){return rS==rT&&(rT=(rS=rB)+fread(rB,1,1<<21,stdin),rS==rT)?EOF:*rS++;}
inline void flush(){fwrite(wB,1,wp+1,stdout);wp=-1;}
inline int rd(){
    char c=gc();
    while(c<48||c>57)c=gc();
    int x=c&15;
    for(c=gc();c>=48&&c<=57;c=gc())x=(x<<3)+(x<<1)+(c&15);
    return x;
}
short buf[15];
inline void wt(int x){
	if(wp>(1<<21))flush();
    short l=-1;
    while(x>9){
        buf[++l]=x%10;
        x/=10;
    }
    wB[++wp]=x|48;
    while(l>=0)wB[++wp]=buf[l--]|48;
    wB[++wp]='\n';
}
int G[N],to[N<<1],w[N<<1],nxt[N<<1],sz,sum[N],f[N],dep[N],dfn[N],siz[N],son[N],top[N],ps[N],dfsc,sl[N<<2],rt[N],lc[N*40],rc[N*40],tot,x,y,n;
inline void Swap(int &a,int &b){int t=a;a=b;b=t;}
inline void adde(int u,int v,int c){
	to[++sz]=v;w[sz]=c;nxt[sz]=G[u];G[u]=sz;
	to[++sz]=u;w[sz]=c;nxt[sz]=G[v];G[v]=sz;
}
//可持久化线段树合并部分
int add(int pre,int L,int R,int x){
	int o=++tot;
	if(L<R){
		int M=L+R>>1;
		if(x<=M){lc[o]=add(lc[pre],L,M,x);rc[o]=rc[pre];}
		else{rc[o]=add(rc[pre],M+1,R,x);lc[o]=lc[pre];}
	}
	return o;
}
int merg(int u,int v,int L,int R){
	if(!u||!v)return u|v;
	int o=++tot;
	if(L<R){
		int M=L+R>>1;
		lc[o]=merg(lc[u],lc[v],L,M);
		rc[o]=merg(rc[u],rc[v],M+1,R);
	}
	return o;
}
int ask(int o,int L,int R){
	if(!o)return 0;
	if(x<=L&&y>=R)return 1;
	int M=L+R>>1;
	if(x<=M&&ask(lc[o],L,M))return 1;
	return y>M&&ask(rc[o],M+1,R);
}
//树链剖分部分
void dfs1(int u,int fa){
	int i,v,maxn=0;
	siz[u]=1;
	dep[u]=dep[f[u]=fa]+1;
	rt[u]=add(0,1,n,u);
	Go(u){
		sum[v]=sum[u]+w[i];
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>maxn){son[u]=v;maxn=siz[v];}
		rt[u]=merg(rt[u],rt[v],1,n);
	}
}
void dfs2(int u,int topf){
	top[ps[dfn[u]=++dfsc]=u]=topf;
	if(son[u]){
		int i,v;
		dfs2(son[u],topf);
		Go(u)if(v!=son[u])dfs2(v,v);
	}
}
inline int lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])Swap(u,v);
		u=f[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
//lca线段树部分
void build(int o,int L,int R){
	if(L==R)sl[o]=L;
	else{
		int lc=o<<1,rc=lc|1,M=L+R>>1;
		build(lc,L,M);build(rc,M+1,R);
		sl[o]=lca(sl[lc],sl[rc]);
	}
}
int query(int o,int L,int R){
	if(x<=L&&y>=R)return sl[o];
	int lc=o<<1,rc=lc|1,M=L+R>>1;
	if(x<=M)if(y>M)return lca(query(lc,L,M),query(rc,M+1,R));
	else return query(lc,L,M);
	else return query(rc,M+1,R);
}
inline int getfa(int u){
	while(u){
		if(ask(rt[top[u]],1,n)){
			int l=dfn[top[u]],r=dfn[u],mid;
			while(l<r){
				mid=l+r+1>>1;
				if(ask(rt[ps[mid]],1,n))l=mid;
				else r=mid-1;
			}
			return ps[l];
		}
		u=f[top[u]];
	}
}
int main(){
	int q,i,j,u,v,c,lans=0,p;
	n=rd();q=rd();
	For(i,2,n){
		u=rd();v=rd();c=rd();
		adde(u,v,c);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	while(q--){
		p=rd()^lans;x=rd()^lans;y=rd()^lans;
		if(dfn[u=query(1,1,n)]>=dfn[p]&&dfn[u]<=dfn[p]+siz[p]-1)lans=sum[u]-sum[p];  //1.
		else if(ask(rt[p],1,n))lans=0;  //2.
		else if(dfn[v=getfa(p)]>=dfn[u]&&dfn[v]<=dfn[u]+siz[u]-1)lans=sum[p]-sum[v];  //3.2.
		else lans=sum[p]+sum[u]-(sum[v]<<1);  //3.1.
		wt(lans);
	}
	flush();
	return 0;
}
```


---

## 作者：command_block (赞：13)

挺有意思的一个题,可以当做树论复习题,特别适合我这种无脑选手练反应。

**题意** : 给出一棵无根树,边有边权,点从$1$开始标号。

多次查询标号在$[l,r]$的点到$p$点路径的交集的长度。强制在线。

$n,q\leq 2\times10^5$ ,时限$\texttt{3s}$.

------------

首先尝试观察性质。注意到这条路径等价$p$到虚树的最短路径,可以帮助思考。

这种树上路径问题,一般要分子树和祖先讨论 :

- (1) $l...r$全部在$p$的子树内

	显然,取他们的`LCA`到$p$的距离就好了。其实就是从虚树的根出发。

- (2) $l...r$全部不在$p$的子树内

	取虚树上最近的一个点连过来,具体咋搞后面再说。

- (3) $l...r$全部有一部分在$p$的子树内,另一部分不在

	显然,得到的虚树包含$p$本身,答案为`0`.

我们可以标号为版本轴,根据`dfs`序建立主席树。

我们就可以差分得到任意$l...r$点集的`dfs`序线段树。

$p$的子树可以表示成一个区间。

把`dfs`序分成三部分 : $L=[1,l),M=[l,r],R=(r,n]$.

首先查看是哪种情况,如果$M$中有元素,而且$L,R$中有元素,则为$(3)$.

如果仅有$M$中有则为$(1)$,否则为$(2)$.

对于$(3)$可以直接得出答案。

对于$(1)$,一个众所周知的结论是 : 点集的`LCA`=`dfs`序最大最小的两个点的`LCA`.

对于$(2)$,需要继续分类讨论。

①路径先上后下

这样子,路径的出发点一定是虚树的根,否则可以更短,我们判一下$p$是否在虚树的根的子树内即可。

②路径直接向下

可以相当于把$p$加入虚树,然后查看到父亲的边的长度。

根据虚树的经典结论,分别查询`dfs`序前驱后继取个`min`即可。

总的来说,写一个`LCA`,再写一个`dfs`序主席树即可,这里只需要求前驱后继。

复杂度$O(n\log n+m\log n)$.

自己`YY`了一种比较好写(?)的方法。

warning : 这份代码包含了很多全局调用,可能导致观看者不适。

```cpp
#include<algorithm>
#include<cstdio>
#include<vector>
#define pf printf
#define pb push_back
#define MaxN 200500
using namespace std;
inline int read(){
  register int X=0;
  register char ch=0;
  while(ch<48||ch>57)ch=getchar();
  while(ch>=48&&ch<=57)X=X*10+(ch^48),ch=getchar();
  return X;
}
int dep[MaxN],dis[MaxN],f[17][MaxN];
vector<int> g[MaxN],l[MaxN];
int in[MaxN],out[MaxN],tp[MaxN],tim;
void pfs(int u)
{
  tp[in[u]=++tim]=u;
  for (int i=0,v;i<g[u].size();i++)
    if (!dep[v=g[u][i]]){
      dep[v]=dep[f[0][v]=u]+1;
      dis[v]=dis[u]+l[u][i];
      pfs(v);
    }
  out[u]=tim;
}
int lca(int x,int y){
  int k=16;
  if (dep[y]<dep[x])swap(y,x);
  while(k--)
    while(dep[f[k][y]]>=dep[x])
      y=f[k][y];
  k=16;
  while(k--)
    while(f[k][x]!=f[k][y])
      {x=f[k][x];y=f[k][y];}
  return x==y ? x : f[0][y];
}
struct Node
{int l,r,c;}a[MaxN*20];
int n,tn,rt[MaxN],to,wfl,wfr,rt1,rt2;
#define pr(l,r) wfl=l;wfr=r
void add(int l,int r,int u,int &u2)
{
  a[u2=++tn]=a[u];
  a[u2].c++;
  if (l==r)return ;
  int mid=(l+r)>>1;
  if (to<=mid)add(l,mid,a[u].l,a[u2].l);
  else add(mid+1,r,a[u].r,a[u2].r);
}
bool chk(int l=1,int r=n,int u1=rt1,int u2=rt2)
{
  if (wfl<=l&&r<=wfr)
    return a[u2].c-a[u1].c;
  int mid=(l+r)>>1;
  return (wfl<=mid&&chk(l,mid,a[u1].l,a[u2].l))||
         (mid<wfr&&chk(mid+1,r,a[u1].r,a[u2].r));
}
int qrynxt(int l=1,int r=n,int u1=rt1,int u2=rt2)
{
  if (a[u2].c==a[u1].c)return 0;
  if (l==r)return tp[l];
  int mid=(l+r)>>1;
  if (to<=mid&&a[a[u2].l].c-a[a[u1].l].c){
    int sav=qrynxt(l,mid,a[u1].l,a[u2].l);
    if (sav)return sav;
  }return qrynxt(mid+1,r,a[u1].r,a[u2].r);
}
int qrypre(int l=1,int r=n,int u1=rt1,int u2=rt2)
{
  if (a[u2].c==a[u1].c)return 0;
  if (l==r)return tp[l];
  int mid=(l+r)>>1;
  if (mid<to&&a[a[u2].r].c-a[a[u1].r].c){
    int sav=qrypre(mid+1,r,a[u1].r,a[u2].r);
    if (sav)return sav;
  }return qrypre(l,mid,a[u1].l,a[u2].l);
}
int main()
{
  n=read();int m=read();
  for (int i=1,f,t,len;i<n;i++){
  	f=read();t=read();len=read();
  	g[f].pb(t);l[f].pb(len);
  	g[t].pb(f);l[t].pb(len);
  }pfs(dep[1]=1);
  for (int j=1;j<16;j++)
    for (int i=1;i<=n;i++)
      f[j][i]=f[j-1][f[j-1][i]];
  for (int i=1;i<=n;i++){
    to=in[i];
    add(1,n,rt[i-1],rt[i]);
  }
  for (int i=1,u,l,r,las=0;i<=m;i++){
    u=read()^las;rt1=rt[(read()^las)-1];rt2=rt[read()^las];
    bool fl=0,fm=0,fr=0;
    if (in[u]>1){pr(1,in[u]-1);fl=chk();}
    pr(in[u],out[u]);fm=chk();
    if (out[u]<n){pr(out[u]+1,n);fr=chk();}
    if (fm&&(fl||fr))pf("%d\n",las=0);
    else if (!(fl||fr)){
      to=out[u];int v1=qrypre();
      to=in[u];int v2=qrynxt();
      pf("%d\n",las=(dis[lca(v1,v2)]-dis[u]));
    }else {
      to=1;int v1=qrynxt();
      to=n;int v2=qrypre();
      int v=lca(v1,v2);
      if (in[v]<=in[u]&&in[u]<=out[v]){
        int ans=2100000000;
        if (fl){
          to=in[u]-1;v=qrypre();
          ans=min(ans,dis[u]-dis[lca(u,v)]);
        }if (fr){
          to=out[u]+1;v=qrynxt();
          ans=min(ans,dis[u]-dis[lca(u,v)]);
        }pf("%d\n",las=ans);
      }else pf("%d\n",las=(dis[u]+dis[v]-dis[lca(u,v)]*2));
    }
  }return 0;
}
```

---

## 作者：Mr_Wu (赞：7)

数据结构大杂烩。。

我临结束一个半小时开始写的，没调出来，结束后十分钟才调出来。。

### 前置知识

树的基本知识（dfs 序，欧拉序）

ST 表，线段树，可持久化线段树（主席树）

出题人太强了。。无限 Orz 出题人

### 题解

前置知识：树的基本知识（dfs 序，欧拉序），ST 表，线段树，可持久化线段树（主席树）

我是两个 log，我不知道正解复杂度多少。。

考虑将 $[l,r]$ 的点分成三部分，一部分在 $p$ 的子树里，一部分不在，却与 $p$ 同在 $1$ 的一个子树里，一部分与 $p$ 不在 $1$ 的一个子树里。


![](https://img-blog.csdnimg.cn/20200209191442866.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3d5eTYwMw==,size_16,color_FFFFFF,t_70)

如果 $A$，$B\cup C$ 两者之内都有点，答案就是 $0$。

如果点都在 $A$ 内，我们只需要知道 $\text{lca}(l\sim r)$ 即可。

如果点都在 $B\cup C$ 内，且只在 $C$ 内，我们也只需要知道 $\text{lca}(l\sim r)$ 即可。

接下来只需考虑最后一种情况：没有点在 $A$ 中，有一些点在 $B$ 中。

然后我们还是要分两种情况：

一种是这样的：

![](https://img-blog.csdnimg.cn/20200209192334690.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3d5eTYwMw==,size_16,color_FFFFFF,t_70)

就是 1 到 p 的路径上伸出多条子树里面都有点，那么我们只需要找到那个红色位置（最低的那棵子树）即可。

一种是这样的：

![](https://img-blog.csdnimg.cn/2020020919260372.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3d5eTYwMw==,size_16,color_FFFFFF,t_70)

此时我们不仅要知道红色位置，还需要知道 $\text{lca}(l\sim r)$。

总而言之，我们需要知道怎么求最低的那棵子树，以及 $\text{lca}(l\sim r)$。

首先考虑求 $\text{lca}(l\sim r)$，这个就比较简单，我们使用线段树维护，在 pushup 的时候需要 $O(1)$ 的求两个点的 lca，我们使用 ST 表维护欧拉序上的最小值即可。这一部分的时间复杂度是 $O(n\log n)$。

然后考虑求最低的那棵子树，我们倍增（二分）往上跳，然后只需要知道某个点的子树内是否有 $l\sim r$ 的子树，我们做出 dfs 序，建立以 dfs 序为下标的可持久化权值线段树，对 $1\sim i$ 的子树我们只需要将 $\text{dfn}_{1\sim i}$ 都标为 1 即可。

我们发现我们也顺带获得了判断 4 种情况的方法。

时间复杂度 $O(n\log^2 n)$。

### 代码

~~全场最慢~~ 我都没 rush 出来，我人没了

常数巨大代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll read() {
    ll ret = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}

int N, Q;

const int MAXN = 200005;
ll dep[MAXN]; int fa[MAXN][21], dfn[MAXN], siz[MAXN], in[MAXN], rein[MAXN << 1], euler[MAXN << 1], dfncnt, eulercnt;

struct node { int v, next; ll k; } E[MAXN << 1]; int head[MAXN], Elen;
void add(int u, int v, ll k) { ++Elen, E[Elen].v = v, E[Elen].next = head[u], head[u] = Elen, E[Elen].k = k; }

void dfs(int u, int ff) {
    fa[u][0] = ff, dfn[u] = ++dfncnt, in[u] = ++eulercnt, rein[eulercnt] = u, euler[eulercnt] = u, siz[u] = 1;
    for (int i = 1; i <= 20; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = E[i].next) {
        if (E[i].v != ff) {
            dep[E[i].v] = dep[u] + E[i].k, dfs(E[i].v, u);
            euler[++eulercnt] = u, siz[u] += siz[E[i].v];
        }
    }
}
int st[MAXN << 1][21];
void buildST() {
    for (int i = eulercnt; i >= 1; --i) {
        st[i][0] = in[euler[i]];
        for (int j = 1; i + (1 << j) - 1 <= eulercnt; ++j) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}
inline int lca(int u, int v) {
    if (u == v) return u;
    u = in[u], v = in[v];
    if (u > v) swap(u, v);
    int lg = log2(v - u + 1);
    return rein[min(st[u][lg], st[v - (1 << lg) + 1][lg])];
}

namespace T1 {
    int ans[MAXN << 2];
    #define mid ((l + r) >> 1)
    void build(int o, int l, int r) {
        if (l == r) ans[o] = l;
        else build(o << 1, l, mid), build(o << 1 | 1, mid + 1, r), ans[o] = lca(ans[o << 1], ans[o << 1 | 1]);
    }
    ll query(int o, int l, int r, int L, int R) {
        if (l == L && r == R) return ans[o];
        else {
            if (R <= mid) return query(o << 1, l, mid, L, R);
            else if (L > mid) return query(o << 1 | 1, mid + 1, r, L, R);
            else return lca(query(o << 1, l, mid, L, mid), query(o << 1 | 1, mid + 1, r, mid + 1, R));
        }
    }
};

int sum[MAXN << 5], rt[MAXN], lson[MAXN << 5], rson[MAXN << 5], Tlen;
#define mid ((l + r) >> 1)
void insert(int& o, int l, int r, int rt, int p) {
    o = ++Tlen;
    if (l == r) sum[o] = sum[rt] + 1;
    else {
        lson[o] = lson[rt], rson[o] = rson[rt];
        if (p <= mid) insert(lson[o], l, mid, lson[rt], p);
        else insert(rson[o], mid + 1, r, rson[rt], p);
        sum[o] = sum[lson[o]] + sum[rson[o]];
    }
}
int query(int o, int l, int r, int L, int R) {
    if (l == L && r == R) return sum[o];
    else {
        if (R <= mid) return query(lson[o], l, mid, L, R);
        else if (L > mid) return query(rson[o], mid + 1, r, L, R);
        else return query(lson[o], l, mid, L, mid) + query(rson[o], mid + 1, r, mid + 1, R);
    }
}
#undef mid

inline int Query(int p, int l, int r) { return query(rt[r], 1, N, dfn[p], dfn[p] + siz[p] - 1) - query(rt[l - 1], 1, N, dfn[p], dfn[p] + siz[p] - 1); }

ll lastans;
int main() {
    scanf("%d%d", &N, &Q); int i, u, v, p, l, r; ll k;
    for (i = 1; i < N; ++i) scanf("%d%d%lld", &u, &v, &k), add(u, v, k), add(v, u, k);
    dfs(1, 0);
    buildST();
    T1::build(1, 1, N);
    for (i = 1; i <= N; ++i) {
        insert(rt[i], 1, N, rt[i - 1], dfn[i]);
    }
    while (Q--) {
        scanf("%d%d%d", &p, &l, &r), p ^= lastans, l ^= lastans, r ^= lastans;
        k = Query(p, l, r);
        if (k == r - l + 1) lastans = dep[T1::query(1, 1, N, l, r)] - dep[p];
        else if (k != 0) lastans = 0;
        else {
            u = p;
            for (i = 20; i >= 0; --i) if (dep[fa[u][i]] > 0) u = fa[u][i];
            k = Query(u, l, r);
            if (k == 0) lastans = dep[p] + dep[T1::query(1, 1, N, l, r)];
            else {
                u = p;
                for (i = 20; i >= 0; --i) {
                    if (fa[u][i] && Query(fa[u][i], l, r) == 0) u = fa[u][i];
                }
                u = fa[u][0]; int lc = T1::query(1, 1, N, l, r);
                if (dep[lc] < dep[u]) lastans = dep[p] - dep[u];
                else lastans = dep[p] + dep[lc] - (dep[u] << 1);
            }
        }
        printf("%lld\n", lastans);
    }
    return 0;
}
```

---

## 作者：摸鱼酱 (赞：4)

给定一棵 $n$ 个点带边权的树，$q$ 次**在线**询问 $p$ 到 $[l,r]$ 内的点路径的交的长度。

$1\leq n,q\leq 2\times 10^5$。

考虑用 ST 表求出 $[l,r]$ 内点的 LCA 为点 $u$。

- $u,p$ 无祖先后代关系，答案为 $dis(u,p)$。
- $u$ 在 $p$ 子树内，答案即为 $dis(u,p)$，因为所有点都在 $p$ 子树内，在 $u$ 处汇合。
- $p$ 在 $u$ 子树内。

  - 若 $p$ 子树内有 $[l,r]$ 内的点，则答案是 $0$，因为 $p$ 子树内外都有点，路径会没有交。
  - 否则二分找到最高的点 $p'$ 满足 $p'$ 子树内无 $[l,r]$ 内的点，答案为 $dis(fa_{p'},p)$，因为此时所有点都会走到 $fa_{p'}$ 之后再走向 $p$，这一步可以用主席树来维护。

时间复杂度 $\mathcal O(n\log^2 n)$，空间复杂度 $\mathcal O(n\log n)$。

[code](https://www.luogu.com.cn/paste/doe9ws84)。

---

## 作者：strcmp (赞：3)

典题，感觉数据结构稍微多做点就能秒得很快了。

先钦定 $1$ 为根。

显然 $[l,\,r]$ 要么都在 $p$ 子树内，要么都在 $p$ 子树外。否则答案一定为 $0$。

$[l,\,r]$ 都在 $p$ 子树内，那么它们公共的 LCA 显然一定在 $p$ 子树内，先求出公共 LCA 然后算这个 LCA 到 $p$ 的距离即可。

怎么算 $[l,\,r]$ 的公共 LCA？一种方法是计算 $\text{mindfn}$ 和 $\text{maxdfn}$ 的 LCA，一种是直接 $a_i \leftarrow \text{LCA}(i,\,i + 1)$ 然后算 $[l,\,r - 1]$ 的深度最值。我选择了后者。至于为什么后者是对的[详见这里](https://www.luogu.com.cn/article/a6f6tjgw)。
  
接下来考虑 $[l,\,r]$ 在 $p$ 子树外。

先找到 $p$ 向上走到的最深祖先 $x$，满足 $x$ 子树内存在任意一个编号在 $[l,\,r]$ 内的点。

两种情况：

1. $x$ 包含了所有 $[l,\,r]$ 的点，那么一样，求出公共 LCA，然后答案就是 LCA 到 $p$ 的距离。

2. $x$ 没有包含所有 $[l,\,r]$ 的点，那么答案一定是 $x$ 到 $p$ 的距离。

至此答案是什么就讨论完了，每次相当于倍增，判定 $u$ 子树内有多少个 $[l,\,r]$ 内的点。

持久化线段树合并即可。时间复杂度 $\Theta(n \log^2 n)$，空间复杂度 $\Theta(n \log n)$，可以通过。

写完代码直接 1A1C 了，舒服。

这个做法基本没有思维难度，代码难度也很低。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
#define pb push_back
#define mp make_pair
#define mid (l + r >> 1)
using namespace std;
typedef long long int ll;
using ull = unsigned long long int;
using pii = pair<int, int>;
constexpr int maxn = 2e5 + 10, mx = 2e6 + 5, mod = 998244353;
struct edge { int to, nxt, w; } nd[maxn << 1]; int h[maxn], cnt = 0, n, Q, lg[maxn], ans;
inline void add(int u, int v, int w) { nd[cnt].nxt = h[u], nd[cnt].to = v, nd[cnt].w = w, h[u] = cnt++; }
struct Node { int l, r, v; } t[maxn * 41];
#define ls(x) (t[x].l)
#define rs(x) (t[x].r)
#define val(x) (t[x].v)
#define mid (l + r >> 1)
int fa[maxn][18], a[18][maxn], d[maxn], s[maxn], rt[maxn], tot = 0;
void mg(int& x, int& y) {
	if (!x || !y) x |= y;
	else {
		int u = ++tot; t[u] = t[x]; x = u; val(u) += val(y);
		mg(ls(u), ls(y)), mg(rs(u), rs(y));
	}
}
void mdf(int l, int r, int k, int p, int& x) {
	t[x = ++tot] = t[p]; ++val(x); if (l == r) return void();
	return k <= mid ? mdf(l, mid, k, ls(p), ls(x)) : mdf(mid + 1, r, k, rs(p), rs(x));
}
int qry(int l, int r, int ql, int qr, int x) {
	if (!x || ql <= l && r <= qr) return val(x); int sum = 0;
	(ql <= mid) && (sum += qry(l, mid, ql, qr, ls(x))), (qr > mid) && (sum += qry(mid + 1, r, ql, qr, rs(x))); return sum;
}
void dfs(int u, int f) {
	d[u] = d[fa[u][0] = f] + 1;
	rep(i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1]; 
	for (int i = h[u]; ~i; i = nd[i].nxt) {
		int v = nd[i].to;
		if (v != f) {
			s[v] = s[u] + nd[i].w, dfs(v, u);
			mg(rt[u], rt[v]);
		}
	}
	mdf(1, n, u, rt[u], rt[u]);
}
inline int lca(int u, int v) {
	if (d[u] < d[v]) swap(u, v);
	rep(i, 0, 17) if (d[u] - d[v] >> i & 1) u = fa[u][i];
	if (u == v) return u;
	per(i, 17, 0) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
inline int ck(int u, int v) { return d[u] < d[v] ? u : v; }
inline int LCA(int l, int r) { if (l == r) return l; int g = lg[r-- - l]; return ck(a[g][l], a[g][r - (1 << g) + 1]); }
#define F(l, r, x) qry(1, n, l, r, rt[x])
inline void solve(int p, int l, int r) {
	int W = 0;
	if ((W = F(l, r, p)) == r - l + 1) return void(ans = s[LCA(l, r)] - s[p]);
	else {	
		if (W) return void(ans = 0); int x = p;
		per(i, 17, 0) if (fa[x][i] && !F(l, r, fa[x][i])) x = fa[x][i]; x = fa[x][0];
		if (F(l, r, x) == r - l + 1) {
			int u = LCA(l, r);
			return void(ans = s[p] + s[u] - 2 * s[lca(p, u)]);
		}
		else return void(ans = s[p] - s[x]);
	}
}
int main() {
	memset(h, -1, sizeof(h)); scanf("%d%d", &n, &Q);
	for (int i = 2, u, v, w; i <= n; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w), lg[i] = lg[i >> 1] + 1;
	dfs(1, 0); rep(i, 1, n - 1) a[0][i] = lca(i, i + 1);
	rep(i, 1, 17) rep(j, 1, n - (1 << i - 1)) a[i][j] = ck(a[i - 1][j], a[i - 1][j + (1 << i - 1)]);
	//cout << F(8, 9, 4) << "\n";
	while (Q--) {
		int p, l, r;
		scanf("%d%d%d", &p, &l, &r); p ^= ans, l ^= ans, r ^= ans;
		solve(p, l, r); printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：crashed (赞：3)

&emsp;&emsp;**去往[原博客](https://www.cnblogs.com/crashed/p/13455561.html)食用更佳。**
# 题目

&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/P6071)看题目。   

# 分析

&emsp;&emsp;~~如果这道题可以换根，那它就是一道水题，可是换不得。~~    

&emsp;&emsp;我们首先考虑 $p$ 是根的时候应该怎么做。可以发现，对于所有情况总存在：   
$$
\bigcap_{i=l}^rE(p,i)=E(p,\text{LCA}[l,r])
$$
&emsp;&emsp;这里我们认为 $\text{LCA}[l,r]$ 为集合 $[l, r]$ 的点的 $\text{LCA}$ ，括号决定区间的开或闭。   

&emsp;&emsp;简单说明一下。记左边集合为 $A$ ，右边为 $B$ 。由于 $\text{LCA}[l,r]$ 是 $l\sim r$ 的点的 $\text{LCA}$ ，并且 $p$ 就是根，所以 $\text{LCA}[l,r]$ 必然在 $p$ 到 $l\sim r$ 的公共路径的任意一个点上，就应该有 $B\subset A$ 。又由于 $\text{LCA}[l,r]$ 是 $l\sim r$ 的**最深**的**公共**祖先，就有 $A\subset B$ ，也就是 $A=B$ 。    

&emsp;&emsp;然后考虑 $p$ 不是根的时候会怎么样。首先我们还是需要得到 $u=\text{LCA}[l,r]$ 。然后考虑 $u$ 和 $p$ 的位置，也可以理解为 " 换根 " ：       

&emsp;&emsp; $\mathcal{Case 1:}$  $p$ 是 $u$ 的祖先。此时可以像上面一样直接判断。      

![](https://cdn.luogu.com.cn/upload/image_hosting/59gnku3v.png)

&emsp;&emsp; $\mathcal{Case 2:}$  $p$ 不是 $u$ 的祖先，且 $p$ 是 $l\sim r$ 的某些节点的祖先。此时如果将 $p$ 提做根，那么 $l\sim r$ 必然会分散到 $p$ 的多个子树中，答案为 $0$ 。       

![](https://cdn.luogu.com.cn/upload/image_hosting/2mf3n07z.png)

&emsp;&emsp; $\mathcal{Case 3:}$  $p$ 不是 $l\sim r$ 中任何点的祖先。如果将 $p$ 提做根，此时 $l\sim r$ 的 $\text{LCA}$ 就不一定是 $u$ 了。这里需要再分一些 $\mathcal{Case}$ 。  

&emsp;&emsp; $\mathcal{Case3.1:}$  $u$ 不是 $p$ 作为根的情况下的 $\text{LCA}$ 。那么我们应该多考虑哪一个节点呢？显然这个节点（不妨称之为 $v$ ）应该是 $p$ 的祖先。更近一步的，应该是 $v=\max_{i=l}^r\text{LCA}\{i,p\}$ （按照深度比较取大小）。对于 $w$ 是 $v$ 的祖先，当 $p$ 换做根之后，$w$ 的子树内必然不会包含 $[l,r]$ 的所有点。     

&emsp;&emsp;如果 $u$ 不是 $p$ 作为根的时候的 $\text{LCA}$ ，就说明 $p$ 在 $u$ 的子树内且 $v$ 应该比 $u$ 更深，正如下面这幅图：       

![](https://cdn.luogu.com.cn/upload/image_hosting/4rvs4ey6.png)

&emsp;&emsp; $\mathcal{Case3.2:}$  $u$ 是 $p$ 作为根的情况下的 $\text{LCA}$ 。此时 $p$ 就不应该在 $u$ 的子树内，且 $v$ 比 $u$ 浅。如图：   

![](https://cdn.luogu.com.cn/upload/image_hosting/uihuloxr.png)

&emsp;&emsp;这么分类讨论一下之后，问题就比较好解决了。我们只需要解决几个问题：    

&emsp;&emsp; $\mathcal{1.}$ 查询连续几个点的 $\text{LCA}$ 。我们可以对点进行倍增， $lca[i,j]$ 存储 $\text{LCA}[i,i+2^j)$ 。由于 $\text{LCA}$ 这个运算具有交换律、结合律和等幂性 （ 即 $\text{LCA}\{a,a\}=a$ ），我们可以花费单次 $\text{LCA}$ 的时间查询出连续几个点的 $\text{LCA}$ 。如果使用 $\text{RMQ}$ 查询 $\text{LCA}$ 可以做到 $O(n\log_2n)-O(1)$ 解决。

&emsp;&emsp; $\mathcal{2.}$ 查询一个点是否是某些点的祖先，我们可以直接查询这个点内包含的标记点的数量。由于问题中标记点在一个区间，我们可以将树展开到 $\text{DFS}$ 序上，并利用**可持久化线段树**维护点的前缀上 DFS 序的情况，并直接查询。    

&emsp;&emsp; $\mathcal{3.}$ 查询一个点到某些点的  $\text{LCA}$ 中最深的那一个。显然我们可以从起始点进行**倍增**，每次检查是否有标记点在下一步的点的子树中，如果没有我们就可以跳一下。最终我们可以得到最浅的一个**子树内不包含任何标记点**的点，它的父亲就是我们的目标。这个过程可以配合倍增  $\text{LCA}$ 理解。   

&emsp;&emsp;时间复杂度是 $O(n\log_2^2n)$ ，瓶颈是问题 $\mathcal{3}$ ，占用了两个 $\log$ 。   

&emsp;&emsp;本题的可借鉴之处就在于它的**分类讨论**步骤和多次出现的**倍增思想**。树上换根问题，既可以 $\text{LCT}$ 维护，也可以像这样**分类讨论**。   

# 代码

```cpp
#include <cstdio>

const int MAXN = 2e5 + 5, MAXLOG = 20, MAXS = MAXN * MAXLOG;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

struct edge
{
	int to, nxt, w;
}Graph[MAXN << 1];

int s[MAXS], lch[MAXS], rch[MAXS];
int rt[MAXN], nsiz;

int f[MAXN][MAXLOG], lca[MAXN][MAXLOG];
int lg[MAXN];

int head[MAXN], dist[MAXN], dep[MAXN], DFN[MAXN], siz[MAXN];
int N, Q, cnt, ID, lg2;

void addEdge( const int from, const int to, const int W )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from], Graph[cnt].w = W;
	head[from] = cnt;
}

void addE( const int from, const int to, const int W )
{
	addEdge( from, to, W ), addEdge( to, from, W );
}

void DFS( const int u, const int fa )
{
	f[u][0] = fa;
	dep[u] = dep[fa] + 1, DFN[u] = ++ ID, siz[u] = 1;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa )
			dist[v] = dist[u] + Graph[i].w, 
			DFS( v, u ), siz[u] += siz[v];
}

void balance( int &u, const int stp )
{
	for( int i = 0 ; ( 1 << i ) <= stp ; i ++ )
		if( stp & ( 1 << i ) )
			u = f[u][i];
}

int LCA( int u, int v )
{
	if( dep[u] > dep[v] ) balance( u, dep[u] - dep[v] );
	if( dep[v] > dep[u] ) balance( v, dep[v] - dep[u] );
	if( u == v ) return u;
	for( int i = lg2 ; ~ i ; i -- ) if( f[u][i] ^ f[v][i] ) u = f[u][i], v = f[v][i];
	return f[u][0];
}

int rangeLCA( int l, int r )
{
	int k = lg[r - l + 1];
	return LCA( lca[l][k], lca[r - ( 1 << k ) + 1][k] );
}

void upt( const int x ) { s[x] = s[lch[x]] + s[rch[x]]; }
void copy( int a, int b ) { s[a] = s[b], lch[a] = lch[b], rch[a] = rch[b]; }

int update( const int x, const int l, const int r, const int p )
{
	int cur = ++ nsiz; copy( cur, x );
	if( l == r ) { s[cur] ++; return cur; }
	int mid = l + r >> 1;
	if( p <= mid ) lch[cur] = update( lch[x], l, mid, p );
	else rch[cur] = update( rch[x], mid + 1, r, p );
	upt( cur ); return cur;
}

int query( const int x, const int l, const int r, const int segL, const int segR )
{
	if( ! x ) return 0;
	if( segL <= l && r <= segR ) return s[x];
	int mid = l + r >> 1, ret = 0;
	if( segL <= mid ) ret += query( lch[x], l, mid, segL, segR );
	if( mid < segR ) ret += query( rch[x], mid + 1, r, segL, segR );
	return ret;
}

int query( const int u, const int L, const int R )
{
	return query( rt[R], 1, N, DFN[u], DFN[u] + siz[u] - 1 )
	     - query( rt[L - 1], 1, N, DFN[u], DFN[u] + siz[u] - 1 );
}

void init()
{
	DFS( 1, 0 ); 
	
	lg[1] = 0;
	for( int i = 2 ; i <= N ; i ++ )
		lg[i] = lg[i - 1] + ( i == ( 1 << lg[i - 1] + 1 ) );
	lg2 = lg[N];
	
	for( int j = 1 ; j <= lg2 ; j ++ )
		for( int i = 1 ; i <= N ; i ++ )
			f[i][j] = f[f[i][j - 1]][j - 1];
	for( int i = 1 ; i <= N ; i ++ ) lca[i][0] = i;
	for( int j = 1 ; j <= lg2 ; j ++ )
		for( int i = 1 ; i + ( 1 << j - 1 ) <= N ; i ++ )
			lca[i][j] = LCA( lca[i][j - 1], lca[i + ( 1 << j - 1 )][j - 1] );
			
	for( int i = 1 ; i <= N ; i ++ )
		rt[i] = update( rt[i - 1], 1, N, DFN[i] );
}

int DCA( int u, const int L, const int R ) // Deepest Common Ancestor
{
	int tmp;
	for( int i = lg2 ; ~ i ; i -- )
		if( tmp = f[u][i] )
			if( ! query( tmp, L, R ) )
				u = tmp;
	return f[u][0];
}

int getDist( const int u, const int v )
{
	return dist[u] + dist[v] - 2 * dist[LCA( u, v )];
}

int main()
{
	read( N ), read( Q );
	for( int i = 1, a, b, c ; i < N ; i ++ )
		read( a ), read( b ), read( c ), addE( a, b, c );
	init();
	
	int P, L, R, lst = 0;
	while( Q -- )
	{
		read( P ), read( L ), read( R );
		P ^= lst, L ^= lst, R ^= lst;
		
		int RLCA = rangeLCA( L, R ), 
			num = query( P, L, R );
		if( num == R - L + 1 ) lst = getDist( P, RLCA );
		else if( num ) lst = 0;
		else
		{
			int t = DCA( P, L, R );
			if( dep[t] > dep[RLCA] ) lst = getDist( P, t );
			else lst = getDist( P, RLCA );
		}
		write( lst ), putchar( '\n' );
	}
	return 0;
}
```


---

## 作者：FutaRimeWoawaSete (赞：1)

题解里面的大多方法都是分类讨论，这里介绍一种不用分类讨论的 $O(n \log ^ 2 n)$ 基本上 rush 快的话 10min 就可以写好。 

当然由于存在 $O(n \log n)$ 做法，所以肯定不是最优解法。

~~当然如果你像我一样写挂了就另说。~~                

我们考虑求交，这个东西貌似不是很好形式化的样子。              

我们大不了先直接确定一条路径。比如说我们拿 $(p,l)$ 这条路径开涮，我们将这条路径拆分为两条链，$(p,LCA)$ 段和 $(LCA , l)$。           

对于 $(p,LCA)$ 段，显然的是，从 $p$ 走到 LCA 的路上，深度越浅的边越有可能走不到。因为这时候对应的子树越来越大，倘若下方出现了一个 $[l + 1 , r]$ 的节点那么这条边就肯定不能被计入贡献，更上方的边更无法计入贡献。             

对于 $(LCA,l)$ 段，从 LCA 走到 $l$ 的路上，深度越深的边越有可能走不到。因为这时候对应的子树越来越小，而且只有点 $[l,r]$ 都在下方的子树内这条边才能被计入贡献。                

那么两端答案具有单调性，我们直接二分答案然后主席树查一个子树内值域在 $[l + 1 , r]$ 或是 $[l,r]$ 的点个数，然后滚一个树上前缀和就可以树上差分算路径和了。           

时间复杂度 $O(n \log ^ 2 n)$，空间复杂度 $O(n \log n)$。      

```cpp
/*
log^2就直接在树上瞎跳几下就好了
但是nlog貌似不会，主席树上二分啥的是真的不会
虚树哪里要用啊/yun 
怎么题解里面更麻烦啊，可能是右链不怎么好维护，但是总比你分类讨论强吧（ 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e6 + 5;
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int n,q,head[Len],cnt,top,tot,dfn[Len],id[Len],ID[Len],rt[Len],dp[28][Len],siz[Len],dep[Len];
int Dis[Len];
struct Node
{
	int l,r,sum;
}tree[Len * 55];
int clones(int p)
{
	top ++;
	tree[top] = tree[p];
	tree[top].sum ++;
	return top;
}
int build(int p,int l,int r)
{
	p = ++ top;
	if(l == r) return p;
	int mid = (l + r) >> 1;
	tree[p].l = build(tree[p].l , l , mid);
	tree[p].r = build(tree[p].r , mid + 1 , r);
	return p;
}
int update(int p,int l,int r,int idx)
{
	p = clones(p);
	if(l == r) return p;
	int mid = (l + r) >> 1;
	if(idx <= mid) tree[p].l = update(tree[p].l , l , mid , idx);
	else tree[p].r = update(tree[p].r , mid + 1 , r , idx);
	return p;
}
int query(int L,int R,int l,int r,int nl,int nr)
{
	if(nl > nr) return 0;
	if(nl <= L && R <= nr) return tree[r].sum - tree[l].sum;
	int mid = (L + R) >> 1 , res = 0;
	if(nl <= mid) res += query(L , mid , tree[l].l , tree[r].l , nl , nr);
	if(nr > mid) res += query(mid + 1 , R , tree[l].r , tree[r].r , nl , nr);
	return res; 
}
struct node
{
	int next,to,w;
}edge[Len << 1];
void add(int from,int to,int w)
{
	edge[++ cnt].to = to;
	edge[cnt].w = w;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
void dfs(int x,int f)
{
	siz[x] = 1;
	dep[x] = dep[f] + 1;
	dp[0][x] = f;
	dfn[x] = ++ tot;
	ID[tot] = x;
	for(int i = 1 ; (1 << i) <= dep[x] ; i ++) dp[i][x] = dp[i - 1][dp[i - 1][x]];
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == f) continue;
		Dis[to] = Dis[x] + edge[e].w;
		dfs(to , x);
		siz[x] += siz[to];
	}
}
int FLCA(int x,int y)
{
	if(dep[x] < dep[y]) swap(x , y);
	for(int i = 27 ; i >= 0 ; i --) if(dep[dp[i][x]] >= dep[y]) x = dp[i][x];
	if(x == y) return x;
	for(int i = 27 ; i >= 0 ; i --) if(dp[i][x] != dp[i][y]) x = dp[i][x] , y = dp[i][y];
	return dp[0][x];
}
int Kthau(int x,int k)
{
	for(int i = 27 ; i >= 0 ; i --) if(k >= (1 << i)){x = dp[i][x];k -= (1 << i);}
	return x;
}
int p,L,R;
bool check_l(int mid)
{
	int now = Kthau(p , mid);//dfn_now , dfn_now + siz_now - 1
	int res = query(1 , n , rt[dfn[now] - 1] , rt[dfn[now] + siz[now] - 1] , L + 1 , R);
	if(res) return 0;
	return 1;
}
bool check_r(int mid)
{
	int now = Kthau(L , mid);
	//printf("%d %d %d %d:\n",now,siz[now],dfn[now] - 1,dfn[now] + siz[now] - 1);
	int res = query(1 , n , rt[dfn[now] - 1] , rt[dfn[now] + siz[now] - 1] , L , R);
	if(res != R - L + 1) return 0;
	return 1;
}
signed main()
{
	//freopen("P6071_1.in","r",stdin);
	//freopen("P6071.out","w",stdout);
	n = read() , q = read(); 
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y,w;x = read() , y = read() , w = read();
		add(x , y , w) , add(y , x , w);
	}
	dfs(1 , 0);
	rt[0] = build(1 , 1 , n);
	for(int i = 1 ; i <= n ; i ++) rt[i] = update(rt[i - 1] , 1 , n , ID[i]);
	int lstans = 0;
	for(int i = 1 ; i <= q ; i ++) 
	{
		p = read() , L = read() , R = read();
		p ^= lstans , L ^= lstans , R ^= lstans;
		int LCA = FLCA(p , L);int res = 0;
		int l = 0 , r = dep[p] - dep[LCA] - 1 , anss = -1;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(check_l(mid)){anss = mid , l = mid + 1;}
			else r = mid - 1;
		}
		//if(anss != dep[p] - dep[LCA] - 1) puts("ouicnoaskjpx");
		if(anss != -1) res += Dis[p] - Dis[dp[0][Kthau(p , anss)]];
		l = 0 , r = dep[L] - dep[LCA] , anss = -1;
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(check_r(mid)){anss = mid , r = mid - 1;}
			else l = mid + 1;
		}
		if(anss != -1) res += Dis[Kthau(L , anss)] - Dis[LCA];
		write(lstans = res) , putchar('\n'); 
	}
	return 0;
}
```

---

## 作者：orz_z (赞：1)

### P6071 『MdOI R1』Treequery

分类讨论，设 $[l,r]$ 的点的 `LCA` 为 $u$：

* $p$ 不在 $u$ 的子树内，答案为 $\operatorname{dis}(u,p)$。
* 否则。
  * 若 $p$ 子树内有 $[l,r]$ 的点，则答案为 $0$，因为路径边集无交。
  * 否则从 $p$ 开始二分最浅的点 $x$ 满足 $x$ 子树内无 $[l,r]$ 的点，答案即为 $\operatorname{dis}(\operatorname{fa}(x),p)$。

自己画图思考就行了。

主席树维护跳点，按 `dfs` 序加点，判区间是否无点即可，时间复杂度单 $\log$。

维护 $\mathcal O(n\log n)-\mathcal O(1)$ `LCA`。

再 `ST` 表维护区间 `LCA`。

故时空复杂度 $\mathcal O(n\log n)$，注意细节问题。

代码不给了，需要可以找我。

---

## 作者：chenxia25 (赞：0)

从这题学到许多，故写题解以记之。（orz ix35）

---

分个类：

- 若 $l\sim r$ 全是 $p$ 的后代，则答案就是 $p$ 到它们的 LCA 的距离；
- 若既有后代又有祖先，答案显然是 $0$；
- 只有祖先的话，还要分两种情况：如果它们到 $p$ 的路径的交是不是一条直链的话（即 LCA 不是 $p$ 的祖先），那么答案就是 LCA 到 $p$ 的距离；否则就是 $l\sim r$ 分别与 $p$ 的 LCA 中最深的，下面重点讨论。

对上面情况的判断，就是数 $p$ 子树内有多少 $[l,r]$ 内的节点。把子树问题转化成 dfn 就是个二维数点，由于是静态的，可以直接主席树做到 1log。

先抛个一开始假想的时候的结论：一堆点（一个区间）的 LCA 显然可以直接线段树维护，而可以证明，若按照 dfn 排序，则答案是两端的 LCA。很可以感性理解，但也容易证明，结合虚树理论想一下就出来了。但这对做这题并没有用，直接维护区间反而好写。注意到 LCA 也是可叠加的，于是也可以用 ST 表做到 $\mathrm O(1)$ 查询，预处理由于次数是线对，所以需要用 $\mathrm O(n\log n)-\mathrm O(1)$ 的欧拉序 + ST 表求 LCA。

将 $l\sim r$ 按 dfn / 欧拉序排序后，将 $p$ 也插进去，那么根据欧拉序 + ST 表求 LCA 法可知，$p$ 与后继的 LCA 是与更后面节点的 LCA 的后代（越往后面取，LCA 深度越小）；左边类似。于是我们只需要求 $p$ 的前驱与后继。

自然想到 2log 的树套树。考虑其本质，前驱后继其实是个变了个形的二维数点，范围是第一维是对应区间，第二维是值域上的前缀 / 后缀，运算从加法变成了求 max / min。但是这玩意没有可减性，所以树套树也是只能区间查询，而非前缀查询然后相减。幸运的是，第二维（值域维）是前缀 / 后缀，可以正反两遍对该维主席树，然后对第一维区间查询。

但是这样太麻烦了（大雾）。前驱后继这玩意有更优秀的性质：每个点的点权就是第二维坐标。所以如果我们把第一维压扁的话，那么就不是一个复杂的 RMQ，而是直接找有值的地方，可以用类似树上二分的更简单的写法（但是区间查询的写法更为直观？）。而「有值」这玩意（即 cnt）是可减的，于是我们可以直接将左右两端两棵树相减，然后在上面二分。

**_[code](https://www.luogu.com.cn/paste/9d072snf)_**（写老长了）

---

## 作者：wenhao801 (赞：0)

好题！

提供一种很难写，跑很慢，但感觉比题解好想的解法。

## 题意

给棵树，有边权，每次给 ``p l r``，询问 $p$ 到 $[l, r]$ 内每个点的公共部分长度。强制在线。

## 题解

题解中默认 $1$ 为根。

### Subtask 1: $l = r$

即询问两个点之间的路径长度。可以随便 LCA 再倍增。

### Subtask 2: $p = 1$

考虑如果最后答案不为 $0$，那一定是这样的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/i8ywflui.png)

红色的边权和即为答案。也就是求 $[l, r]$ 这些点的 LCA，然后这个 LCA 到根的路径即为答案。

可以使用了 ST 表维护区间 LCA。

### 正解

我们把 $[l, r]$ 中的点分为三种。

![](https://cdn.luogu.com.cn/upload/image_hosting/cs3o2xex.png)

即：在 $p$ 子树中的点，$p$ 的祖先和其他点，分别对应上图的第 1，2 类点。（红色的点是此时在 $[l, r]$ 中的点）

如果第 1 类点和第 2 类点同时存在，显然此时答案为 0；如果仅存在第 1 类点，那么等同于 Subtask 2 中的情况。

下面讨论存在第 2 类点时的情况。

---

显然，每个点 $x$ 的路径为 $x \rightarrow \text{LCA}(x, p) \rightarrow p$，而且这些 LCA 一定在 $p$ 到根的路径上。

不难推出，设点 $T = \text{LCA}(x_0, p)$ 为 $\text{LCA}(l, p), \text{LCA}(l + 1, p), \cdots, \text{LCA}(r, p)$ 中最深的点，则此时的答案为 $\text{LCA}(T, p) \rightarrow p$ 这条路径的长度。

![](https://cdn.luogu.com.cn/upload/image_hosting/n9jdcv5u.png)

比如在上图中，$p = 9, l = 5, r = 7$，则 $T = 4$，答案即为 $4 \rightarrow 9$ 的这条路径。

但其实这样是不对的，因为我们实际上把 $x \rightarrow p$ 的路径拆成了 $x \rightarrow \text{LCA}(x, p)$ 和 $\text{LCA}(x, p) \rightarrow p$，而且只算了 $\text{LCA}(x, p) \rightarrow p$ 的部分。万一 $x \rightarrow \text{LCA}(x, p)$ 的部分也对答案产生了贡献，那我们就~~死了~~。

![](https://cdn.luogu.com.cn/upload/image_hosting/x5r96w87.png)

如上图，当前有且仅有红色点在 $[l, r]$ 内，此时按照上面的方法只会统计 $T \rightarrow p$ 的答案，而不会统计绿色的边。

有**结论**：如果 $\text{LCA}(l, l + 1, \cdots, r)$ 比点 T **严格深**，则 $\text{LCA}(l, l + 1, \cdots, r)$ 一定在 $T$ 的子树中，即答案需要加上 $\text{LCA} \rightarrow T$ 这段的路径长。

![](https://cdn.luogu.com.cn/upload/image_hosting/2swr3zkk.png)

如图，当 $\text{LCA}(l, l + 1, \cdots, r)$ 比 $T$ 严格深时，只可能 $l, l + 1, \cdots, r$ 是红色的这种点（在 $T$ 子树内）；如果是蓝色的这种点（在 $T$ 子树外），则 $T$ 不符合其定义。

所以这个结论是正确的。~~（感性理解）~~

而且容易发现，即使第 1 类点存在，这个结论仍然正确。

---

整理一下。

我们需要求出 $\text{LCA}(l, l + 1, \cdots, r)$ 和 $T$；如果 $\text{LCA}(l, l + 1, \cdots, r)$ 比 $T$ 严格深，则答案为 $\text{LCA} \rightarrow p$ 的路径长；否则，答案为 $T \rightarrow p$ 的路径长。

求 $\text{LCA}(l, l + 1, \cdots, r)$ 可以用 Subtask 2 中的方法；

而 $T$ 即为最深的、包含至少一个 $[l, r]$ 内节点的 $p$ 的祖先，可以倍增往上跳，再在 dfs 序上使用权值主席树进行判断。

---

### 代码

写的非常丑陋。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

inline int read () {
    int ret = 0, t = 1;
    char c = getchar();
    while ((c < '0' || c > '9') && c != '-') c = getchar();
    if (c == '-') t = -1, c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret * t;
}

const int MAXN = 200200;

int n, q;

struct Edge {
    int nex;
    int to;
    int w;
} edge[MAXN << 1];
int head[MAXN], cnt = 0;
int F[MAXN][22] = {}; // F[i][j] 表示点 i 往上跳 1 << j 级父亲这一路的长度。
int dfn[MAXN] = {}, rdfn[MAXN] = {};
// dfn[i] 表示第 i 个被访问的节点。rdfn 就是反过来。
void add (int u, int v, int w) {
    edge[++cnt].to = v;
    edge[cnt].nex = head[u];
    edge[cnt].w = w;
    head[u] = cnt;
}

int fa[MAXN][22] = {};
int dep[MAXN] = {};
int siz[MAXN] = {};

struct node {
    int lson;
    int rson;
    int val;
} tree[MAXN * 36];

void pushup (int root) { tree[root].val = tree[tree[root].lson].val + tree[tree[root].rson].val; }

void build (int l, int r, int root) {
    if (l == r) {
        tree[root].val = 0;
        return;
    }
    int mid = (l + r) >> 1;
    cnt++;
    tree[root].lson = cnt;
    build(l, mid, cnt);
    cnt++;
    tree[root].rson = cnt;
    build(mid + 1, r, cnt);
}

int hed[MAXN] = {};
// ↑主席树的head
void update (int l, int r, int oldroot, int newroot, int kth) {
    if (l == r) {
        tree[newroot].val = tree[oldroot].val + 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (kth <= mid) {
        tree[newroot].rson = tree[oldroot].rson;
        tree[newroot].lson = ++cnt;
        update(l, mid, tree[oldroot].lson, cnt, kth);
        pushup(newroot);
    }
    else {
        tree[newroot].lson = tree[oldroot].lson;
        tree[newroot].rson = ++cnt;
        update(mid + 1, r, tree[oldroot].rson, cnt, kth);
        pushup(newroot);
    }
}

void dfs (int x, int f) {
    dep[x] = dep[f] + 1;
    fa[x][0] = f;
    dfn[++cnt] = x, rdfn[x] = cnt;
    siz[x] = 1;
    int i, j;
    for (i = head[x]; i; i = edge[i].nex) {
        j = edge[i].to;
        if (j != f) F[j][0] = edge[i].w, dfs(j, x), siz[x] += siz[j];
    }
}

int lca (int u, int v) {
    int i, j;
    if (dep[u] < dep[v]) swap(u, v);
    for (i = 20; i >= 0; i--) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    if (u == v) return u;
    for (i = 20; i >= 0; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}

int st[MAXN][22] = {};
// ↑ st[i][j] 表示 lca(i, i + 1, ..., i + (1 << j))。
int query (int l, int r, int oldroot, int newroot, int L, int R) {
    if (l <= L && R <= r) return tree[newroot].val - tree[oldroot].val;
    int mid = (L + R) >> 1, ret = 0;
    if (l <= mid) ret += query(l, r, tree[oldroot].lson, tree[newroot].lson, L, mid);
    if (mid < r) ret += query(l, r, tree[oldroot].rson, tree[newroot].rson, mid + 1, R);
    return ret;
}

int main () {
    n = read(), q = read();
    int i, j;
    for (i = 1; i < n; i++) {
        int u = read(), v = read(), w = read();
        add(u, v, w), add(v, u, w);
    }
    cnt = 0;
    dfs(1, 0);
    cnt = 1;
    build(1, n, 1);
    hed[1] = 1;
    for (i = 1; i <= n; i++) {
        hed[i + 1] = ++cnt;
        update(1, n, hed[i], cnt, dfn[i]);
    }
    for (i = 1; i <= 20; i++) for (j = 1; j <= n; j++) fa[j][i] = fa[fa[j][i - 1]][i - 1];
    for (i = 1; i <= n; i++) st[i][0] = i;
    for (i = 1; i <= 20; i++) for (j = 1; j <= n; j++) if (j + (1 << (i)) - 1 <= n) st[j][i] = lca(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]);
    for (i = 1; i <= 20; i++) for (j = 1; j <= n; j++) F[j][i] = F[j][i - 1] + F[fa[j][i - 1]][i - 1];
    int lastans = 0; // 上面三个 ST 表都更新了一下。
    while (q--) {
        int p = read() ^ lastans, l = read() ^ lastans, r = read() ^ lastans;
        int len = log2(r - l + 1);
        int rua = lca(st[l][len], st[r - (1 << len) + 1][len]); // 即为 lca(l, l + 1, ..., r)。
        int tmp = p; // 即为文中的 T。
        for (i = 20; i >= 0; i--) if (fa[tmp][i] && query(l, r, hed[rdfn[fa[tmp][i]]], hed[rdfn[fa[tmp][i]] + siz[fa[tmp][i]]], 1, n) == 0) tmp = fa[tmp][i];
        if (query(l, r, hed[rdfn[p]], hed[rdfn[p] + siz[p]], 1, n) != 0) tmp = p; else tmp = fa[tmp][0];
        int ans = 0; // 上面两行即为倍增的往上跳到最后一个不包含 [l, r] 中节点的 p 的祖先；因为 p 可能就已经包含 [l, r] 中的节点，所以要特判。
        if (dep[rua] > dep[tmp])
            for (i = 20; i >= 0; i--)
                if (dep[fa[rua][i]] >= dep[tmp]) ans += F[rua][i], rua = fa[rua][i];
        for (i = 20; i >= 0; i--) // ↑↓正常的统计答案。
            if (dep[fa[p][i]] >= dep[tmp]) ans += F[p][i], p = fa[p][i];
        printf("%d\n", ans);
        lastans = ans; // 别忘了。
    }
    return 0;
}
```

---

