# Xenia and Tree

## 题目描述

Xenia the programmer has a tree consisting of $ n $ nodes. We will consider the tree nodes indexed from 1 to $ n $ . We will also consider the first node to be initially painted red, and the other nodes — to be painted blue.

The distance between two tree nodes $ v $ and $ u $ is the number of edges in the shortest path between $ v $ and $ u $ .

Xenia needs to learn how to quickly execute queries of two types:

1. paint a specified blue node in red;
2. calculate which red node is the closest to the given one and print the shortest distance to the closest red node.

Your task is to write a program which will execute the described queries.

## 样例 #1

### 输入

```
5 4
1 2
2 3
2 4
4 5
2 1
2 5
1 2
2 5
```

### 输出

```
0
3
2
```

# 题解

## 作者：EndSaH (赞：13)

[博客使用效果更佳，加载较慢请稍候片刻](https://endsah.cf/blog/CF342E-Xenia-and-Tree/#more)

# Solution

点分树可以做，参考另一篇题解。不过有比这更简单的做法。

有两种形式的暴力：

1. 对每个询问点，都和在其之前所有的红色点求 LCA 并计算出距离，再取最小值。
2. 对每个被修改为红色点的点，都在树上 BFS 并更新所有点到红色点的最小值。

这两个暴力各有优劣，如何把它们的优劣点综合起来？

最常用的操作就是分块。

考虑对操作序列分块，设块大小为 $S$。

如何回答询问？

首先对于在这个询问所属块之前的那些整块而言，每块都把所有的修改丢到队列里多源 BFS 一遍，每块复杂度 $O(n)$；

与这个询问在同一个块内的修改点，直接暴力求 LCA 并更新答案即可，复杂度 $O(S ^2 \log n)$。

总复杂度为 $O(n \cdot \frac m S + S ^2 \log n \cdot \frac m S)$，易知 $S$ 取 $\sqrt {\frac n {\log n}}$ 最优，此时总复杂度为 $O(m \cdot \sqrt {n \log n})$。

看起来这个复杂度很悬，实际上还会带上大约 $\frac 1 4$ 的常数，并且树剖的 $\log$ 根本跑不满，所以能轻松的过掉。

类似的分块思想的题今年 APIO 也出了，[[APIO2019]桥梁](https://www.luogu.org/problem/P5443)，可以再拿这题练下手。

# Code

一遍过了hhh

```cpp
/**********************************************************
 * Author        : EndSaH
 * Email         : hjxhb1@gmail.com
 * Created Time  : 2019-09-14 09:00
 * FileName      : wib.cpp
 * Website       : https://endsah.cf
 * *******************************************************/

#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <vector>
#include <queue>

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define Debug(s) debug("The message in line %d, Function %s: %s\n", __LINE__, __FUNCTION__, s)
#define getchar() (ipos == iend and (iend = (ipos = _ibuf) + fread(_ibuf, 1, __bufsize, stdin), ipos == iend) ? EOF : *ipos++)
#define putchar(ch) (opos == oend ? fwrite(_obuf, 1, __bufsize, stdout), opos = _obuf : 0, *opos++ = (ch))
#define __bufsize (1 << 21 | 1)

char _ibuf[__bufsize], _obuf[__bufsize], _stk[50];
char *ipos = _ibuf, *iend = _ibuf, *opos = _obuf, *oend = _obuf + __bufsize, *stkpos = _stk;

struct END
{ ~END() { fwrite(_obuf, 1, opos - _obuf, stdout); } }
__;

inline int read()
{
    register int x = 0, flag = 1;
    register char ch;
    while (!isdigit(ch = getchar()))
        if (ch == '-')
            flag = -1;
    while (x = x * 10 + (ch & 15), isdigit(ch = getchar()));
    return x * flag;
}

template <typename _INT>
inline void write(_INT x)
{
    if (x < 0)
        putchar('-'), x = -x;
    while (*++stkpos = x % 10 ^ 48, x /= 10, x);
    while (stkpos != _stk)
        putchar(*stkpos--);
}

template <typename _Tp>
inline bool Chkmax(_Tp& x, const _Tp& y)
{ return x < y ? x = y, true : false; }

template <typename _Tp>
inline bool Chkmin(_Tp& x, const _Tp& y)
{ return x > y ? x = y, true : false; }

const int maxN = 1e5 + 5;
const int maxM = 1e5 + 5;

int n, m, len;
int dep[maxN], fa[maxN], top[maxN], son[maxN], size[maxN];
int mindis[maxN], dis[maxN];
int opt[maxM], node[maxM], id[maxM];
std::vector<int> G[maxN];
std::queue<int> q;

void DFS1(int u)
{
    size[u] = 1;
    for (int v : G[u])
    {
        if (fa[u] == v)
            continue;
        fa[v] = u, dep[v] = dep[u] + 1;
        DFS1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}

void DFS2(int u)
{
    if (son[u])
        top[son[u]] = top[u], DFS2(son[u]);
    for (int v : G[u]) if (!top[v])
        top[v] = v, DFS2(v);
}

int Dis(int u, int v)
{
    int res = dep[u] + dep[v];
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            std::swap(u, v);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        std::swap(u, v);
    return res - (dep[u] << 1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("wib.in", "r", stdin);
    freopen("wib.out", "w", stdout);
#endif
    n = read(), m = read();
    len = sqrt(n * log(n) / log(2));
    for (int i = 2; i <= n; ++i)
    {
        int u = read(), v = read();
        G[u].push_back(v), G[v].push_back(u);
    }
    DFS1(1), memcpy(mindis + 1, dep + 1, n * sizeof(int));
    top[1] = 1, DFS2(1);
    for (int i = 1; i <= m; ++i)
        opt[i] = read(), node[i] = read();
    id[0] = 1;
    for (int i = 1; i <= m; ++i)
        id[i] = (i - 1) / len + 1;
    for (int i = 1; i <= m; ++i)
    {
        if (id[i] != id[i - 1])
        {
            memset(dis + 1, 0x3F, n * sizeof(int));
            for (int j = i - len; j < i; ++j)
                if (opt[j] == 1)
                    q.push(node[j]), dis[node[j]] = 0;
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                for (int v : G[u]) if (Chkmin(dis[v], dis[u] + 1))
                    q.push(v);
            }
            for (int i = 1; i <= n; ++i)
                Chkmin(mindis[i], dis[i]);
        }
        if (opt[i] == 2)
        {
            int ans = mindis[node[i]];
            for (int j = i - 1; j and id[j] == id[i]; --j) if (opt[j] == 1)
                Chkmin(ans, Dis(node[j], node[i]));
            write(ans), putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：Umbrella_Leaf (赞：7)

### 题意

> $n$ 个点的树，初始根节点 $1$ 是黑色其余白色。$q$ 次操作，每次操作把一个点染黑或询问离某个点最近的黑色点离它的距离。$n,q\le 10^5$。

### 题解

貌似做法很多，题解区树剖/LCT/点分树/分块神仙打架，我只能想到离线做 CDQ 分治。。。

暴力是遍历所有黑色点然后取 $min$，考虑 CDQ 分治，那么以一个 $\log$ 的做法转化成：

> 有一棵树，若干个点是黑色，然后给出若干个点分别询问离它最近的黑色点距离。

这个显然可以换根 DP $O(n)$ 解决，但是因为是 CDQ 分治所以不能在完整树上跑……那就建棵虚树呗。

复杂度是 $O(n\log n)$ 的。

[Code](https://codeforces.com/contest/342/submission/172351490)

---

## 作者：mrsrz (赞：5)

[可能更好的体验](https://mrsrz.github.io/2019/11/18/CF342E/)

有动态点分治和操作分块的做法了，这里再来一个不一样的。

考虑两点的距离的计算方法为 $\mathrm{dist}(u,v)=dep[u]+dep[v]-2\times dep[\mathrm{LCA}(u,v)]$。

考虑新加入一个关键点，在其所有祖先处记录信息，询问的时候，也直接在每个点的祖先上询问。相当于枚举最近公共祖先，计算其最小贡献。

但是更新答案时，会涉及到 $O(n)$ 个点的修改，而且每个点作为 LCA 的 $dep$ 要计算进去以便于取最小值。所以加入关键点时，更新的答案是一个类似等差数列。

这里也许可以使用树剖+李超树实现 $O(m\log^3 n)$，但可能因为一些重复计算之类的问题而出错~~而且复杂度看起来不好看虽然常数挺小~~。

考虑树链剖分维护轻儿子信息，每个点维护轻儿子所在子树和自己节点本身，节点深度最小和第二小的节点的深度及所在子树。然后，令最小的深度为 $d$，将 $d-2\times dep[v]$ 插入 $v$ 对应的线段树节点中，用以查询最小值。

更新的时候，显然只会在每条重链链顶更新，复杂度是 $O(\log^2 n)$。

查询的时候，对于重链上的，直接区间查询最小值即可。

但是当切换链的时候会出现一些情况：

1. 链顶的父亲节点保存的最大值在链顶所在子树中。这里为了防止重复（其实不会错误因为计算的是最小值，出现此种情况最小值在之前应该已经更新了），使用次大值进行计算。
2. 链顶的父亲节点的重儿子所在子树未计算贡献。那么我们再开一棵线段树，用来查询子树中深度最小的节点的深度，然后直接查询重儿子中的最小深度，计算贡献即可。

这里的复杂度也是 $O(\log^2 n)$ 的。

那么总时间复杂度 $O(m\log^2 n)$。

## Code：

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1e5+6;
struct edge{
	int to,nxt;
}e[N<<1];
struct info{
	int mx1,mx2,id1,id2;
}f[N];
int n,m,head[N],cnt,sz[N],son[N],dep[N],fa[N],top[N],dfn[N],idfn[N],idx;
int d[N<<2],dd[N<<2];
void build(int l,int r,int o){
	if(l==r)d[o]=(l==1)?-1:0x3f3f3f3f,dd[o]=d[o]==-1?1:d[o];else{
		const int mid=l+r>>1;
		build(l,mid,o<<1),build(mid+1,r,o<<1|1);
		d[o]=min(d[o<<1],d[o<<1|1]);
		dd[o]=min(dd[o<<1],dd[o<<1|1]);
	}
}
void modify1(int l,int r,int o,const int&pos,const int&val){
	if(l==r)d[o]=val;else{
		const int mid=l+r>>1;
		if(pos<=mid)modify1(l,mid,o<<1,pos,val);else modify1(mid+1,r,o<<1|1,pos,val);
		d[o]=min(d[o<<1],d[o<<1|1]);
	}
}
void modify2(int l,int r,int o,const int&pos,const int&val){
	if(l==r)dd[o]=val;else{
		const int mid=l+r>>1;
		if(pos<=mid)modify2(l,mid,o<<1,pos,val);else modify2(mid+1,r,o<<1|1,pos,val);
		dd[o]=min(dd[o<<1],dd[o<<1|1]);
	}
}
int query1(int l,int r,int o,const int&L,const int&R){
	if(L<=l&&r<=R)return d[o];
	const int mid=l+r>>1;
	int ret=0x3f3f3f3f;
	if(L<=mid)ret=query1(l,mid,o<<1,L,R);
	if(mid<R)ret=min(ret,query1(mid+1,r,o<<1|1,L,R));
	return ret;
}
int query2(int l,int r,int o,const int&L,const int&R){
	if(L<=l&&r<=R)return dd[o];
	const int mid=l+r>>1;
	int ret=0x3f3f3f3f;
	if(L<=mid)ret=query2(l,mid,o<<1,L,R);
	if(mid<R)ret=min(ret,query2(mid+1,r,o<<1|1,L,R));
	return ret;
}
inline void update(int id,int sn,int depu){
	info&x=f[id];
	if(depu<x.mx1){
		x.mx2=x.mx1,x.id2=x.id1;
		x.mx1=depu,x.id1=sn;
		modify1(1,n,1,dfn[id],depu-2*dep[id]);
	}else
		if(depu<x.mx2){
			x.mx2=depu,x.id2=sn;
		}
}
void dfs(int now){
	sz[now]=1;
	for(int i=head[now];i;i=e[i].nxt)
	if(!dep[e[i].to]){
		dep[e[i].to]=dep[now]+1,fa[e[i].to]=now;
		dfs(e[i].to);
		sz[now]+=sz[e[i].to];
		if(!son[now]||sz[son[now]]<sz[e[i].to])son[now]=e[i].to;
	}
}
void dfs2(int now){
	idfn[dfn[now]=++idx]=now;
	if(son[now])top[son[now]]=top[now],dfs2(son[now]);
	for(int i=head[now];i;i=e[i].nxt)
		if(e[i].to!=son[now]&&e[i].to!=fa[now])dfs2(top[e[i].to]=e[i].to);
}
void modify(int u){
	const int du=dep[u];
	modify2(1,n,1,dfn[u],du);
	update(u,u,du);
	while(top[u]!=1){
		update(fa[top[u]],top[u],du);
		u=fa[top[u]];
	}
}
int query(int u){
	int ret=0x3f3f3f3f,depu=dep[u];
	ret=min(ret,query2(1,n,1,dfn[u],dfn[u]+sz[u]-1)-depu);
	for(;;){
		int x=top[u],y=fa[top[u]];
		ret=min(ret,query1(1,n,1,dfn[x],dfn[u])+depu);
		if(y){
			ret=min(ret,(f[y].id1==x?f[y].mx2:f[y].mx1)+depu-2*dep[y]);
			if(son[y])
				ret=min(ret,query2(1,n,1,dfn[son[y]],dfn[son[y]]+sz[son[y]]-1)+depu-2*dep[y]);
			u=y;
		}else break;
	}
	return ret;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<n;++i){
		int u,v;
		cin>>u>>v;
		e[++cnt]=(edge){v,head[u]},head[u]=cnt;
		e[++cnt]=(edge){u,head[v]},head[v]=cnt;
	}
	dfs(dep[1]=1),dfs2(top[1]=1);
	build(1,n,1);
	memset(f,0x3f,sizeof f);
	modify(1);
	while(m--){
		int op,u;
		cin>>op>>u;
		if(op==1)modify(u);else cout<<query(u)<<'\n';
	}
	return 0;
}
```


---

## 作者：tommy0221 (赞：4)

水 LA 的时候有人提到这题就来看了。一看，这不是点分树板子？后来看到说这题没有人写正常点分（三度化。。。），我就来写一个。

首先建出点分树，考虑对于每一个分治中心维护离它最近的红点。

查询的时候，从查询点往分治树根跳，对于跳到的每一个分治中心，贡献是：分治中心到查询点的距离 加上 距离分治中心最近的红点距离。

修改的时候，一路跳到根，更新每一个分治中心的最近距离就好了。

查询距离用 ST表 可以 $O(1)$ ，总复杂度就是 $O((n+q)\log n)$。

根据点分树性质，一个点到树上所有点的路径 都会有一个点在它到分治根路径上，所以跳到根可以维护出所有路径，正确性得以保证。

```cpp
const int N = 100005;
const int inf = 0x3f3f3f3f;
int n, q;
int hed[N], et;
int vt[N], rt, mx[N], siz[N], tsz, val[N];
int ST[20][N << 1], dep[N], tmr, dfn[N], lg[N << 1], pw2[40];
bool used[N];
struct edge { int nx, to; } e[N << 1];
inline void adde(int u, int v) {
	e[++et].to = v, e[et].nx = hed[u], hed[u] = et;
}
void dfs(int u, int ft) {
	ST[0][dfn[u] = ++tmr] = dep[u];
	for(int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if(v == ft) continue;
		dep[v] = dep[u] + 1, dfs(v, u), ST[0][++tmr] = dep[u];
	}
}
inline void init_dis(){
	lg[0] = -1, pw2[0] = 1;
	for(int i = 1; i <= tmr; ++i) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i <= 20; ++i) pw2[i] = pw2[i - 1] << 1;
	for(int i = 1; i <= lg[tmr]; ++i)
		for(int j = 1; j + pw2[i] - 1<= tmr; ++j) 
			ST[i][j] = min(ST[i - 1][j], ST[i - 1][j + pw2[i - 1]]);
}
inline int dis(int x, int y) {
	int l = dfn[x], r = dfn[y];
	if(l > r) l ^= r ^= l ^= r;
	int t = lg[r - l + 1];
	return dep[x] + dep[y] - (min(ST[t][l], ST[t][r - pw2[t] + 1]) << 1);
}
void getrt(int u, int ft) {
	siz[u] = 1, mx[u] = 0;
	for(int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if(v == ft || used[v]) continue;
		getrt(v, u), siz[u] += siz[v], ckmax(mx[u], siz[v]);
	}
	ckmax(mx[u], tsz - siz[u]);
	if(mx[u] < mx[rt]) rt = u;
}
void solve(int u) {
	used[u] = 1;
	int tmp = tsz;
	for(int i = hed[u]; i; i = e[i].nx) {
		int v = e[i].to; if(used[v]) continue;
		tsz = siz[v] > siz[u] ? tmp - siz[u] : siz[v];
		rt = 0, getrt(v, u), vt[rt] = u, solve(rt);
	}
}
inline void upd(int x) {
	for(int i = x; i; i = vt[i]) ckmin(val[i], dis(x, i));
}
inline int ask(int x) {
	int res = inf;
	for(int i = x; i; i = vt[i]) ckmin(res, val[i] + dis(x, i));
	return res;
}
signed main() {
	n = read(), q = read();
	rep(i, 2, n) {
		int x = read(), y = read();
		adde(x, y), adde(y, x);
	}
	dfs(1, 0), init_dis();
	mx[rt = 0] = tsz = n, getrt(1, 0);
	solve(rt);
	memset(val, 0x3f, sizeof(val));
	upd(1);
	while(q--) {
		int op = read(), x = read();
		if(op == 1) upd(x);
		else printf("%d\n", ask(x));
	}
	return 0;
}
```

---

## 作者：whiteqwq (赞：4)

[CF342E Xenia and Tree](https://www.luogu.com.cn/problem/CF342E)解题报告：

[更好的阅读体验](https://www.luogu.com.cn/blog/xiaoziyaoxzy/solution-cf342e)

吐槽：好奇怪呀，为什么交了两份相同的代码一份AC一份WA，不应该返回相同的答案吗。

## 题意
- 给定一个$n$个点的树，一开始结点$1$为红点，其他点为蓝点；
- $m$次操作，操作分两类：把一个点变成红点，询问一个点离最近的红点的距离。
- 数据范围：$1\leqslant n,m\leqslant 10^5$。

## 分析
操作分块。

我们设定一个阈值$S$，对操作序列每$S$个操作分一块。

对于每一次询问，我们对红点分类讨论：

- 对于不在这个询问块内的红点，我们预处理出来这些红点对于询问的点的距离；
- 对于在这个询问块内的红点，我们暴力枚举然后求距离。

具体地，每跨越一次块，我们就把这个块内所有的红点bfs一遍，更新它们到所有点的距离，这是$O(n)$的，但是由于只会跨越$O(\frac{m}{S})$次块，所以总复杂度为$O(n\times\frac{m}{S})$。

对于在这个块内的红点，我们枚举它们，然后用ST表的$O(n\log n)-O(1)$的lca求距离，这样我们的复杂度为$O(S)$，总复杂度为$O(m\times S)$。

故时间复杂度为：$O(\frac{n\times m}{S}+m\times S)$，很显然$S$取$\sqrt{m}$时复杂度较优，为$O((n+m)\sqrt{m})$。

## 代码

分块常数小，加了个快读就到最优解了。
```
#include<stdio.h>
#include<math.h>
#define inf 1000000000
const int maxn=100005,maxm=200005,maxk=20,maxt=405,maxq=100005;
int n,m,e,qs,t,now;
int start[maxn],to[maxm],then[maxm],lg[maxn<<1],ST[maxn<<1][maxk],dep[maxn],in[maxn],bl[maxt],br[maxt],opt[maxq],k[maxq],dis[maxn],q[maxn];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int calc(int a,int b){
	return dep[a]<dep[b]? a:b;
}
inline void swp(int &a,int &b){
	a+=b,b=a-b,a-=b;
}
inline void add(int x,int y){
	then[++e]=start[x],start[x]=e,to[e]=y;
}
void dfs(int x,int last){
	dep[x]=dep[last]+1,in[x]=++qs,ST[qs][0]=x;
	for(int i=start[x];i;i=then[i]){
		int y=to[i];
		if(y==last)
			continue;
		dfs(y,x);
		ST[++qs][0]=x;
	}
}
void getST(){
	lg[0]=-1;
	for(int i=1;i<=qs;i++)
		lg[i]=lg[i/2]+1;
	for(int i=1;i<=18;i++)
		for(int j=1;j+(1<<i)-1<=qs;j++)
			ST[j][i]=calc(ST[j][i-1],ST[j+(1<<(i-1))][i-1]);
}
int lca(int a,int b){
	if(in[a]>in[b])
		swp(a,b);
	int l=in[a],r=in[b],k=lg[r-l+1];
	return calc(ST[l][k],ST[r-(1<<k)+1][k]);
}
int getdis(int a,int b){
	int c=lca(a,b);
	return dep[a]+dep[b]-2*dep[c];
}
void bfs(int a,int b){
	qs=0;
	if(a==-1)
		q[++qs]=1;
	else for(int i=a;i<=b;i++)
		if(opt[i]==1)
			q[++qs]=k[i];
	int now=1;
	while(now<=qs){
		int x=q[now];
		now++;
		for(int i=start[x];i;i=then[i]){
			int y=to[i];
			if(dis[y]<=dis[x]+1)
				continue;
			dis[y]=dis[x]+1,q[++qs]=y;
		}
	}
}
int query(int x,int a,int b){
	int res=dis[x];
	for(int i=a;i<=b;i++)
		if(opt[i]==1)
			res=min(res,getdis(x,k[i]));
	return res;
}
void read(int &x){
	char c=getchar();
	x=0;
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+c-48;
}
int main(){
	read(n),read(m);
	for(int i=1;i<n;i++){
		int x,y;
		read(x),read(y);
		add(x,y),add(y,x);
	}
	dfs(1,0),getST();
	t=sqrt(m);
	for(int i=1;i<=t;i++)
		bl[i]=br[i-1]+1,br[i]=i*t;
	if(br[t]<m)
		t++,bl[t]=bl[t-1]+1,br[t]=m;
	for(int i=1;i<=n;i++)
		dis[i]=inf;
	int last=1;
	dis[1]=0,bfs(-1,-1);
	for(int i=1;i<=m;i++){
		if(i>br[last])
			bfs(bl[last],br[last]),last++;
		read(opt[i]),read(k[i]);
		if(opt[i]==1)
			dis[k[i]]=0;
		if(opt[i]==2)
			printf("%d\n",query(k[i],bl[last],i));
	}
	return 0;
}
```

---

## 作者：xfrvq (赞：3)

[$\tt Link$](/problem/CF342E)，$\tt^{\ast}2400$。

明明是 $\tt LCT$ 或点分树，我却只想操作分块。

我们把操作序列以 $\sqrt m$ 为块长分块。

一个询问的答案是如下红点的贡献的 $\min$。

+ 和询问同块的修改
+ 在询问所在块之前的块的修改

第一类，我们枚举每个操作块，从前往后扫，询问直接用当前的红点的距离取 $\min$。

一个块的操作仅会带来根号个红点。如何快速算距离？考虑 $O(n\log n)-O(1)$ 的 $\tt LCA$。

第二类，我们用一个 $ans$ 数组记录下当上一个操作块刚刚结束时，每个点的答案。

这个可以在扫完这个块之后，在树上跑 $\tt dfs$，更新这根号个红点的新贡献。

准确来说是跑两遍 $\tt dfs$，第一遍用儿子更新父亲，第二遍用父亲更新儿子。

总复杂度 $O(m\sqrt m)$。

---

## 作者：xyf007 (赞：3)

这题是 [SPOJ2939. QTREE5 - Query on a tree V](https://www.spoj.com/problems/QTREE5/) 的严格弱化版（修改操作只有蓝变红），但是不知道为什么没有人写 LCT 的题解。  
我们定义 $lmin_x,rmin_x$ 分别代表在 splay 中 $x$ 的子树里深度最浅的点能够到达最近的白点的距离和深度最深的点能够到达最近的白点的距离，并且用一个 `std::multiset` 维护一下虚子树中的 $lmin$ 最小值。合并的时候考虑是否跨过整棵子树即可。
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
#include <set>
constexpr int kInf = 1e9;
char Gc() {
  static char now[1 << 20], *S, *T;
  if (T == S) {
    T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
    if (T == S) return EOF;
  }
  return *S++;
}
template <typename T>
void Read(T &x) {
  x = 0;
  int f = 1;
  char c;
  while ((c = Gc()) < '0' || c > '9')
    if (c == '-') f = -1;
  x = c - '0';
  while ((c = Gc()) >= '0' && c <= '9') x = x * 10 + (c - '0');
  x *= f;
}
template <typename T, typename... Args>
void Read(T &x, Args &...args) {
  Read(x);
  Read(args...);
}
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
struct Edge {
  int to, nxt;
} e[200001];
int n, q, E, head[100001], c[100001];
std::multiset<int> s[100001];
int Min(int x) { return s[x].empty() ? kInf : *s[x].begin(); }
class LinkCutTree {
 public:
  int lmin_[100001], rmin_[100001];
  LinkCutTree() {}
  void Pushup(int x) {
    sz_[x] = sz_[ch_[x][0]] + sz_[ch_[x][1]] + 1;
    lmin_[x] = std::min(
        lmin_[ch_[x][0]],
        sz_[ch_[x][0]] +
            std::min(c[x] ? 0 : kInf, std::min(lmin_[ch_[x][1]], Min(x)) + 1));
    rmin_[x] = std::min(
        rmin_[ch_[x][1]],
        sz_[ch_[x][1]] +
            std::min(c[x] ? 0 : kInf, std::min(rmin_[ch_[x][0]], Min(x)) + 1));
  }
  void Splay(int x) {
    while (NotRoot(x)) {
      int y = fa_[x];
      if (NotRoot(y)) Rotate(IsRson(x) == IsRson(y) ? y : x);
      Rotate(x);
    }
    Pushup(x);
  }
  void Access(int x) {
    for (int y = 0; x; x = fa_[y = x]) {
      Splay(x);
      s[x].emplace(lmin_[ch_[x][1]]);
      if (auto it = s[x].find(lmin_[y]); it != s[x].end()) s[x].erase(it);
      ch_[x][1] = y;
      Pushup(x);
    }
  }
  void Link(int x, int y) { fa_[x] = y; }
  ~LinkCutTree() {}

 private:
  int ch_[100001][2], fa_[100001], sz_[100001];
  bool NotRoot(int x) { return ch_[fa_[x]][0] == x || ch_[fa_[x]][1] == x; }
  bool IsRson(int x) { return ch_[fa_[x]][1] == x; }
  void Rotate(int x) {
    int y = fa_[x], z = fa_[y], d1 = IsRson(x), d2 = IsRson(y),
        w = ch_[x][d1 ^ 1];
    if (NotRoot(y)) ch_[z][d2] = x;
    ch_[x][d1 ^ 1] = y;
    ch_[y][d1] = w;
    if (w) fa_[w] = y;
    fa_[x] = z;
    fa_[y] = x;
    Pushup(y);
    Pushup(x);
  }
} T;
void Add(int f, int t) {
  e[E].to = t;
  e[E].nxt = head[f];
  head[f] = E++;
}
void Dfs(int u, int fa) {
  for (int i = head[u]; i != -1; i = e[i].nxt) {
    int v = e[i].to;
    if (v == fa) continue;
    T.Link(v, u);
    Dfs(v, u);
  }
}
int main(int argc, char const *argv[]) {
  std::memset(head, -1, sizeof(head));
  Read(n, q);
  for (int i = 1; i < n; i++) {
    int u, v;
    Read(u, v);
    Add(u, v);
    Add(v, u);
  }
  T.lmin_[0] = T.rmin_[0] = kInf;
  Dfs(1, 0);
  T.Access(1);
  T.Splay(1);
  c[1] ^= 1;
  T.Pushup(1);
  while (q--) {
    int op, x;
    Read(op, x);
    T.Access(x);
    T.Splay(x);
    if (op == 1) {
      c[x] ^= 1;
      T.Pushup(x);
    } else {
      std::printf("%d\n", T.rmin_[x] > n ? -1 : T.rmin_[x]);
    }
  }
  return 0;
}
```

---

## 作者：qiyue7 (赞：2)

点分树入门题，先重构树使每点度数转为3，建出树后自底向上暴力扫一遍所有子树修改+询问（度数为3复杂度有保证）， 每一级节点只需要保存子树中离节点最近的值，修改O(3*logn),查询O(3*logn),重构树后大小最多为原树两倍大小。复杂度O(6nlogn).  (实际上快的飞起，不加快读所有case3000ms都跑完了...)


```cpp
#include<memory>
#include<memory.h>
#include<array>
#include <iostream>
#include<vector>
#include<string>
#include<list>
#include<set>
#include<queue>
#include<map>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;
const int MAXN = 200000 + 1;
const int MAXG = MAXN * 2 + 1;
const int MAX_LOG = 19;
const int inf = 0x3f3f3f3f;
int n, q;

struct Edge {
	long long v, w;

	Edge(int v, int w) : v(v), w(w) {}
};

std::vector<Edge> edge[MAXN], g[MAXG];
int a[MAXN];
int tot;

inline void addEdge(int u, int v, int w) {
	//cout << u <<" "<< v << endl;
	g[u].emplace_back(v, w);
	g[v].emplace_back(u, w);
}

inline void binarize(int u, int pre)
{
	static std::vector<Edge *> now;
	now.clear();
	for (auto &p : edge[u])
		if (p.v != pre) now.push_back(&p);
	int o = u;
	for (int i = 0; i < (int)now.size(); i++) {
		addEdge(o, now[i]->v, now[i]->w);
		if (now.size() - i > 2) {
			addEdge(o, ++tot, 0);
			o = tot;
		}
	}
	for (auto &p : edge[u])
		if (p.v != pre) binarize(p.v, u);
}

bool vis[MAXG],vis2[MAXG];
long long sz[MAXG], idx[MAXG], dep[MAXG], fa[MAXG], weight[MAXG];
long long dis[MAXG][MAX_LOG];
long long trans[MAXG][3];

void dfsSize(int u, int pre) {
	sz[u] = 1;
	for (auto &p : g[u]) {
		if (!vis[p.v] && p.v != pre) {
			dfsSize(p.v, u);
			sz[u] += sz[p.v];
		}
	}
}

int get(int u, int pre, int n) {
	for (auto &p : g[u])
		if (!vis[p.v] && p.v != pre && sz[p.v] > n) return get(p.v, u, n);
	return u;
}

void dfs(int u, int pre, int d, int kk) {
	for (auto &p : g[u]) {
		if (!vis[p.v] && p.v != pre) {
			idx[p.v] = idx[u];
			dis[p.v][kk] = dis[u][kk] + p.w;
			if (p.v <= n && vis2[p.v] == 1)
				trans[d][idx[p.v]] = min(trans[d][idx[p.v]], dis[p.v][kk]);
			dfs(p.v, u, d, kk);
		}
	}
}

void build(int u, int d, int f)
{
	dfsSize(u, 0);
	vis[u = get(u, 0, sz[u] / 2)] = true;
	fa[u] = f;
	dep[u] = d;
	int c = 0;
	for (auto &p : g[u]) {
		if (!vis[p.v]) {
			dis[p.v][d] = p.w;
			idx[p.v] = c++;
			if (p.v <= n && vis2[p.v] == 1)
				trans[u][idx[p.v]] = min(trans[u][idx[p.v]], p.w);
			dfs(p.v, u, u, d);
			build(p.v, d + 1, u);
		}
	}
}
long long L, R;
long long cur_ans;
long long query(int cur, int kk, int id)
{
	if (!cur)
		return 0;
	for (int i = 0; i < 3; ++i)
		if (id != i)
			cur_ans = min(cur_ans, trans[cur][i] + dis[kk][dep[cur]]);
	if (vis2[cur])
		cur_ans = min(cur_ans, dis[kk][dep[cur]]);
	query(fa[cur], kk, idx[cur]);
}
void update(int cur,int kk,int id)
{
	if (!cur)
		return;
	if (id != -1)
		trans[cur][id] = min(trans[cur][id],dis[kk][dep[cur]]);
	update(fa[cur], kk, idx[cur]);
}
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int  u, v, w, a, b,q,kk;
	cin >> n>>q;
	
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < MAXG; ++j)
			trans[j][i] = inf;
	memset(vis2, 0, sizeof(vis2));
	vis2[1] = 1;
	for (int i = 0; i < n - 1; ++i)
	{
		cin >> u >> v;
		edge[u].push_back({ v,1 });
		edge[v].push_back({ u,1 });
	}
	int opt;
	tot = n;
	binarize(1, 0);
	build(1, 1, 0);
	while (q--)
	{
		cin >> opt>>kk;
		if (opt == 1)
		{
			if (vis2[kk] == 0)
			{
				vis2[kk] = 1;
				update(kk,kk,-1);
			}
		}
		else
		{
			cur_ans = inf;
			if (vis2[kk])
				cout << 0 << '\n';
			else
			{
				query(kk, kk, -1);
				cout << cur_ans << '\n';
			}
		}
	}
	return 0;
}
```


---

## 作者：do_while_true (赞：1)

想到点分树就做完了（

假如能维护 $c_x$ 为 $x$ 子树内离 $x$ 最近的红色点距离。

一开始想的是树剖这个东西，询问拆成查询它到根的链中最低的红点，和以它到根的链中的点为 LCA 的红点。前者很容易树剖两个 $\log$ 解决。如果维护的 $c_x$ 都是加上它到重链底部的距离的值，这样查询就是查询一个最小值，而修改变成了公差为 $2$ 的等差数列加。对于每一个重链开一个李超树支持区间插入线段查询区间最低点（修改 $\log^2$，查询 $\log$ ）可以做到 $\log^3$。总复杂度就是 $\mathcal{O}(n\log^3 n)$，没有实现是口胡的所以可能有误的一个想法（

如果把询问看成对端点为 $x$ 的所有路径看哪个最短路径满足端点为红色，从而想到树分治。建出点分树之后，端点 $x$ 的路径一定经过 $x$ 在点分树内的祖先，那么维护每个点在点分树的子树内的红点，在原树里离它最近的距离是多少，查询的时候 $x$ 加上到它点分树内祖先的距离加上这个最小值，取个 $\min$ 就好。

修改的话直接暴力跳点分树里的父亲然后更新就可以。统计到的路径可能会产生折返，但其实比它优的一定能统计到所以无关紧要。

[code](https://codeforces.com/contest/342/submission/127421460)

---

