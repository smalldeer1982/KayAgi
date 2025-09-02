# Tourists

## 题目描述

Cyberland 有 $n$ 座城市，编号从 $1$ 到 $n$，有 $m$ 条双向道路连接这些城市。第 $j$ 条路连接城市 $a_j$ 和 $b_j$。每天，都有成千上万的游客来到 Cyberland 游玩。

在每一个城市，都有纪念品售卖，第 $i$ 个城市售价为 $w_i$。这个售价有时会变动。

每一个游客的游览路径都有固定起始城市和终止城市，且不会经过重复的城市。

他们会在路径上的城市中，售价最低的那个城市购买纪念品。

你能求出每一个游客在所有合法的路径中能购买的最低售价是多少吗？

你要处理 $q$ 个操作：

`C a w`： 表示 $a$ 城市的纪念品售价变成 $w$。

`A a b`： 表示有一个游客要从 $a$ 城市到 $b$ 城市，你要回答在所有他的旅行路径中最低售价的最低可能值。

## 样例 #1

### 输入

```
3 3 3
1
2
3
1 2
2 3
1 3
A 2 3
C 1 5
A 2 3
```

### 输出

```
1
2
```

## 样例 #2

### 输入

```
7 9 4
1
2
3
4
5
6
7
1 2
2 5
1 5
2 3
3 4
2 4
5 6
6 7
5 7
A 2 3
A 6 4
A 6 7
A 3 3
```

### 输出

```
2
1
5
3
```

# 题解

## 作者：Ebola (赞：38)

# 【CF487E】Tourists  题解

之前WC的时候太蠢了，没听懂圆方树，一直感觉是神仙东西，直到做了这道题，才对圆方树稍有了一些感觉

圆方树是这样的：对于一个无向连通图，求出它的所有点-双连通分量，然后对于每个点双新建一个点，称之为“方点”，然后原图的点称之为“圆点”，每个圆点向它所在点双对应的方点连边（注意：一个点可能属于多个点双，因此一个圆点需要向多个方点连边），建出一个新的图。这个新图满足：它是一棵树，它最多只有2n-1个点(n是原图点数)，所有的圆点只与方点相邻、所有的方点只与圆点相邻（“相邻”定义为某两个点有一条边直接连接）

这个题和圆方树有什么关系呢？

一个非常显然的事实就是：当你到达一个点双时，一定存在一条简单路径，从外部进入这个点双，然后经过点双里面的权值最小点，然后再走出这个点双。所以一个点双对答案的贡献必然是点双里面的最小权值

于是我们可以建立圆方树，方点的权值为点双中的最小圆点权值。然后原图就变成了一棵树，询问时就可以直接树剖套线段树求路径最小值了

但是修改操作似乎并不是非常方便。因为一个圆点的权值变动，可能会引发与之相连的方点权值变动（当这个圆点是点双中的的最小权值点时会发生这件事情）。那么我们可以对每个方点维护一个multiset，里面存所有与之相邻的圆点权值，然后权值就是multiset中的最小值，每次修改就删掉原来的权值，插入新的权值。然后我们每修改一个圆点的权值，我们就遍历与之相邻的所有方点并按上述方法修改multiset

但这样是会被菊花图卡成n方的。因为菊花图的根节点，有n-1个方点与之相邻，每次修改都遍历一遍的话，就GG了

于是一位巨佬告诉了我更加优秀的方法：对于一个方点，multiset里面存它所有子节点的权值。然后修改一个圆点时，就只需要动它父亲的multiset（它的父亲必然是一个方点）。询问时，仍然可以正常询问，只不过如果lca是一个方点，那还要额外计算fa[lca]的权值对答案的贡献

具体实现需要用Tarjan求一下点双，然后还要一棵维护区间最小值的线段树，以及STL的multiset

```cpp
#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
using namespace std;

namespace IO
{
	const int S=(1<<20)+5;
	//Input Correlation
	char buf[S],*H,*T;
	inline char Get()
	{
		if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		if(H==T) return -1;return *H++;
	}
	inline int read()
	{
		int x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
	}
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <class I>inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc('\n');
	}
}
using namespace IO;

inline void upmin(int &x,const int &y){if(y<x) x=y;}

const int N=100010;
int val[N<<1],n,m,q,tot;
multiset<int> st[N];

namespace TCD
{
	const int N=200010;
	struct Edge{int to,next;} e[N<<1];
	int h[N],sum=0;
	int fa[N],top[N],hson[N];
	int size[N],dep[N];
	int dfn[N],idx[N],clk=0;
	int mn[N<<2];
	
	void AddEdge(int u,int v)
	{
		e[++sum].to=v;
		e[sum].next=h[u];
		h[u]=sum;
	}
	void add_edge(int u,int v)
	{
		AddEdge(u,v);
		AddEdge(v,u);
	}
	
	void dfs1(int u,int la)
	{
		size[u]=1;int mx=0;
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
		{
			int v=e[tmp].to;
			if(v==la) continue;
			dep[v]=dep[u]+1;
			dfs1(v,u);fa[v]=u;
			size[u]+=size[v];
			if(size[v]>mx) mx=size[v],hson[u]=v;
		}
	}
	
	void dfs2(int u,int tp)
	{
		top[u]=tp;idx[dfn[u]=++clk]=u;
		if(hson[u]) dfs2(hson[u],tp);
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
			if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
				dfs2(e[tmp].to,e[tmp].to);
	}
	
	inline void maintain(int o){mn[o]=min(mn[o<<1],mn[o<<1|1]);}
	
	void Build(int o,int l,int r)
	{
		if(l==r){mn[o]=val[idx[l]];return;}
		int mid=(l+r)/2;
		Build(o<<1,l,mid);
		Build(o<<1|1,mid+1,r);
		maintain(o);
	}
	
	void Modify(int o,int l,int r,int k,int x)
	{
		if(l==r){mn[o]=x;return;}
		int mid=(l+r)/2;
		if(k<=mid) Modify(o<<1,l,mid,k,x);
		else Modify(o<<1|1,mid+1,r,k,x);
		maintain(o);
	}
	
	int Query(int o,int l,int r,int nl,int nr)
	{
		if(l>=nl&&r<=nr) return mn[o];
		int mid=(l+r)/2,res=INF;
		if(nl<=mid) upmin(res,Query(o<<1,l,mid,nl,nr));
		if(nr>mid) upmin(res,Query(o<<1|1,mid+1,r,nl,nr));
		return res;
	}
	
	int PathQuery(int u,int v)
	{
		int res=INF;
		while(top[u]!=top[v])
		{
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			upmin(res,Query(1,1,tot,dfn[top[u]],dfn[u]));
			u=fa[top[u]];
		}
		if(dep[u]>dep[v]) swap(u,v);
		upmin(res,Query(1,1,tot,dfn[u],dfn[v]));
		if(u>n) upmin(res,val[fa[u]]);
		return res;
	}
}

namespace Graph
{
	struct Edge{int to,next;} e[N<<1];
	int h[N],sum=0;
	int pre[N],low[N],dfn=0;
	int bcc[N];
	stack<int> stk;
	
	void add_edge(int u,int v)
	{
		e[++sum].to=v;
		e[sum].next=h[u];
		h[u]=sum;
	}
	
	void Tarjan(int u)
	{
		pre[u]=low[u]=++dfn;stk.push(u);
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
		{
			int v=e[tmp].to;
			if(!pre[v])
			{
				Tarjan(v);
				upmin(low[u],low[v]);
				if(low[v]>=pre[u])
				{
					int o;tot++;
					do{
						o=stk.top();
						stk.pop();
						bcc[o]=tot;
						TCD::add_edge(o,tot);
					}while(o!=v);
					TCD::add_edge(u,tot);
				}
			}
			else upmin(low[u],pre[v]);
		}
	}
}

int main()
{
	int u,v;
	tot=n=read();m=read();q=read();
	for(int i=1;i<=n;i++) val[i]=read();
	for(int i=1;i<=m;i++)
	{
		u=read();v=read();
		Graph::add_edge(u,v);
		Graph::add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!Graph::pre[i]) Graph::Tarjan(i);
	TCD::dfs1(1,0);
	TCD::dfs2(1,1);
	for(int i=2;i<=n;i++)
		st[TCD::fa[i]-n].insert(val[i]);
	for(int i=n+1;i<=tot;i++)
		val[i]=st[i-n].empty()?INF:*st[i-n].begin();
	TCD::Build(1,1,tot);
	while(q--)
	{
		char opt=Get();
		while(opt!='C'&&opt!='A') opt=Get();
		u=read();v=read();
		if(opt=='C')
		{
			TCD::Modify(1,1,tot,TCD::dfn[u],v);
			if(u==1){val[u]=v;continue;}
			int o=TCD::fa[u];
			st[o-n].erase(st[o-n].find(val[u]));
			st[o-n].insert(v);
			int minv=*st[o-n].begin();
			if(minv==val[o]){val[u]=v;continue;}
			TCD::Modify(1,1,tot,TCD::dfn[o],minv);
			val[o]=minv;val[u]=v;
		}
		else print(TCD::PathQuery(u,v));
	}
	flush();
	return 0;
}
```



---

## 作者：GIFBMP (赞：19)

首先吐槽一下：这题确实是一道很好的圆方树模板题，感觉做完这题后对圆方树的理解深了很多。

***
好了，进入正题:

## 一、前置知识
	1.线段树
    2.树剖
    3.tarjan找点双
如果不会这些请自觉去学。

## 二、广义圆方树
	先搬一张从网上找来的图：
   
   ![yfs.png](https://i.loli.net/2019/08/28/TLQl6MomwXPfVGO.png)

是不是看不懂？

解释一下：上图就是在简单无向图中建立广义圆方树的过程。
### 步骤
	1.tarjan找出所有点双连通分量并对于每个点双连通分量建立方点
    2.在新的图中把方点和与它对应的点双中的所有圆点连边

## 三、本题解法
这题很明显是一道圆方树题。
    
一看到所有路径上的最小值，我们很容易想到先建广义圆方树，再用树剖+线段树维护。由于求的是最小值，我们可以把方点的点权设置成周围所有圆点的最小值。

### 然而修改呢？

我们考虑一下建完树后是一个菊花套菊花的情况，那么，在修改某一个特定的点的时候，它周围的方点也都要被修改，这样就容易被卡成$\Theta(nq)$，$\color{darkblue}\texttt{TLE}$了。

所以，我们可以利用圆方树是一棵树的性质，把每个方点的权值设为它的所有儿子权值的最小值。然后对于每个方点开一个$multiset$维护就可以了。

## Code（请勿抄袭）：

```cpp
#include<cstdio>
#include<vector>
#include<set>
#define INF 2147483647
using namespace std;
vector<int>G1[200010],G2[200010]; 
multiset<int>S[200010];
int minn[800010];
int dep[200010],f[200010],size[200010],id[200010],cnt,h[200010],top[200010],loc[200010];
int pos,dfn[200010],low[200010],topp,stack[200010];
int n,m,q,dis[200010],ext;
void swap(int &x,int &y){
	int t=x;x=y;y=t;
}
int min(int a,int b){
	return a<b?a:b;
}
void build_tree(int o,int l,int r){
	if(l==r){
		minn[o]=dis[loc[l]];
		return ;
	}
	int mid=l+r>>1;
	build_tree(o<<1,l,mid);
	build_tree(o<<1|1,mid+1,r);
	minn[o]=min(minn[o<<1],minn[o<<1|1]);
}
void update(int o,int l,int r,int x,int k){
	if(l==r){
		minn[o]=k;
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid)update(o<<1,l,mid,x,k);
	else update(o<<1|1,mid+1,r,x,k);
	minn[o]=min(minn[o<<1],minn[o<<1|1]);
}
int query(int o,int l,int r,int x,int y){
	if(x<=l&&r<=y)
		return minn[o];
	int mid=l+r>>1,ret=INF;
	if(x<=mid)ret=min(ret,query(o<<1,l,mid,x,y));
	if(mid<y)ret=min(ret,query(o<<1|1,mid+1,r,x,y));
	return ret;
}
void dfs1(int x,int fa){
	f[x]=fa;
	dep[x]=dep[fa]+1;
	size[x]=1;
	int tmp=-1;
	for(int i=0;i<G2[x].size();i++){
		int v=G2[x][i];
		if(v==fa)
			continue;
		dfs1(v,x);
		size[x]+=size[v];
		if(size[v]>tmp){
			tmp=size[v];
			h[x]=v;
		}
	}
}
void dfs2(int x,int fa){
	top[x]=fa;
	id[x]=++cnt;
	loc[cnt]=x;
	if(!h[x])
		return ;
	dfs2(h[x],fa);
	for(int i=0;i<G2[x].size();i++){
		int v=G2[x][i];
		if(v==f[x]||v==h[x])
			continue;
		dfs2(v,v);
	}
}
void tarjan(int x){
	dfn[x]=low[x]=++pos;
	stack[++topp]=x;
	for(int i=0;i<G1[x].size();i++){
		int v=G1[x][i];
		if(!dfn[v]){
			tarjan(v);
			low[x]=min(low[x],low[v]);
			if(low[v]==dfn[x]){
				ext++;
				for(int j=0;j!=v;topp--){
					j=stack[topp];
					G2[ext].push_back(j);
					G2[j].push_back(ext);
				}
				G2[ext].push_back(x);
				G2[x].push_back(ext);
			}
		}
		else low[x]=min(low[x],dfn[v]);
	}
}
int querypath(int x,int y){
	int ret=INF;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		ret=min(ret,query(1,1,ext,id[top[x]],id[x]));
		x=f[top[x]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	ret=min(ret,query(1,1,ext,id[x],id[y]));
	if(x>n)
		ret=min(ret,dis[f[x]]);
	return ret;
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	ext=n;
	for(int i=1;i<=n;i++)
		scanf("%d",&dis[i]);
	for(int i=1;i<=m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		G1[u].push_back(v);
		G1[v].push_back(u);
	}
	tarjan(1);
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		if(f[i])
			S[f[i]].insert(dis[i]);
	for(int i=n+1;i<=ext;i++)
		dis[i]=*S[i].begin();
	build_tree(1,1,ext);
	while(q--){
		char s[5];
		scanf("%s",s);
		if(s[0]=='C'){
			int x,y;
			scanf("%d%d",&x,&y);
			update(1,1,ext,id[x],y);
			if(f[x]){
				S[f[x]].erase(S[f[x]].lower_bound(dis[x]));
				S[f[x]].insert(y);
				if(dis[f[x]]!=*S[f[x]].begin()){
					dis[f[x]]=*S[f[x]].begin();
					update(1,1,ext,id[f[x]],dis[f[x]]);
				}
					
			}
			dis[x]=y;
		}
		else if(s[0]=='A'){
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%d\n",querypath(x,y));
		}
	}
	return 0;
}
```
    

---

## 作者：Memory_of_winter (赞：9)

[我的博客链接](https://www.cnblogs.com/Memory-of-winter/p/9451222.html)

**题目大意：**给定一张图（保证连通），每个点有点权。现在有两种操作：

1. $C\;a\;w:$把$a$的点权改为$w$；
2. $A\;a\;b:$询问从$a$到$b$的所有简单路径（不经过重复点）中，点权最小的点的点权。

**题解：**可以发现如果是一棵树，直接用树链剖分维护最值即可。

但是它是一个图，所以可以想到缩点。

题目要求不经过重复点，发现对于一个点双连通分量，如果到了其中的任意一个点，一定可以走到其中的点权最小的点。

于是想到把图中的点双缩点，维护圆方树，把方点的值设为它周围的圆点中点权最小的点的点权，树连剖分。

但是这样做有一个问题，每次修改一个圆点，都要修改周围的所有方点，如果一个点在多个点双中，每次修改的时间复杂度可以达到$n\log_2 n$级别，就会$TLE$

怎么办呢？

这时我们改变一下方点的值，可以把方点中的值改为它的儿子中最小值（而不是周围，也就是说，它的父亲的值不会影响这个方点）

看起来没什么是吧？

但是这样我们可以用$multiset$（**不是set**）来存它的每个儿子的值，修改一个圆点时，我们只修改这个圆点本身和这个点的父亲（也就是一个方点）的信息（注意如果修改的点是根就不修改父亲）。

修改复杂度$O(\log_2 n)$（有可能是假的，我并不怎么会推）

询问时，想原来一样树链剖分，注意如果最后的节点是一个方点（也就是说查询的两个点的$LCA$是方点），那么这个方点的父亲就没有统计到答案中，但是它是有贡献的，于是要计算

时间复杂度$(O(n\log_2^2 n)$。

代码又长又丑，大家看看就好

 

**C++ Code：**
```cpp
#include <cstdio>
#include <set>

#define maxn 100010
#define maxm 100010

#define N 200010 
#define M 200010

using namespace std;
const int inf = 0x7fffffff;
inline int min(int a, int b) {return a < b ? a : b;}
inline void swap(int &a, int &b) {a ^= b ^= a ^= b;}
int n, m, q, cnt;
int w[N];
struct Edge {int to, nxt;};
multiset <int> SM[N];
struct ST { //线段树
	int V[N << 1], W[N];
	void build(int rt, int l, int r) {
		if (l == r) {
			V[rt] = W[l];
			return ;
		}
		int mid = l + r >> 1;
		build(rt << 1, l, mid);
		build(rt << 1 | 1, mid + 1, r);
		V[rt] = min(V[rt << 1], V[rt << 1 | 1]);
	}
	void add(int rt, int l, int r, int x, int num) {
		if (l == r) {
			V[rt] = num;
			return ;
		}
		int mid = l + r >> 1;
		if (x <= mid) add(rt << 1, l, mid, x, num);
		else add(rt << 1 | 1, mid + 1, r, x, num);
		V[rt] = min(V[rt << 1], V[rt << 1 | 1]);
	}
	int ask(int rt, int l, int r, int L, int R) {
		if (L <= l && R >= r) {
			return V[rt];
		}
		int mid = l + r >> 1, ans = inf;
		if (L <= mid) ans = ask(rt << 1, l, mid, L, R);
		if (R > mid) ans = min(ans, ask(rt << 1 | 1, mid + 1, r, L, R));
		return ans;
	}
} S;
struct Tree {//树链剖分
	int head[N], cntE;
	Edge e[M << 1];
	void addE(int a, int b) {
		e[++cntE] = (Edge) {b, head[a]}; head[a] = cntE;
	}
	int idx;
	int fa[N], dep[N], dfn[N], son[N], sz[N], top[N];
	void dfs1(int rt) {
		sz[rt] = 1;
		son[rt] = 0;
		for (int i = head[rt]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (!dep[v]) {
				dep[v] = dep[rt] + 1;
				fa[v] = rt;
				dfs1(v);
				sz[rt] += sz[v];
				if (!son[rt] || sz[v] > sz[son[rt]]) son[rt] = v;
			}
		}
	}
	void dfs2(int rt) {
		dfn[rt] = ++idx;
		int v = son[rt];
		if (v) top[v] = top[rt], dfs2(v);
		for (int i = head[rt]; i; i = e[i].nxt) {
			v = e[i].to;
			if (v != fa[rt] && v != son[rt]) {
				top[v] = v;
				dfs2(v);
			}
		}
	}
	void init(int rt) {//树链剖分初始化
		int v;
		fa[rt] = idx = 0;
		dep[top[rt] = rt] = 1;
		dfs1(rt);
		dfs2(rt);
		for (int i = 1; i <= n; i++) S.W[dfn[i]] = w[i];//圆点初始化
		for (int i = n + 1; i <= cnt; i++) {//方点初始化
			for (int j = head[i]; j; j = e[j].nxt) {
				v = e[j].to;
				if (v != fa[i]) SM[i].insert(w[v]);//只存它儿子的信息
			}
			if (SM[i].empty()) w[i] = inf;
			else w[i] = *SM[i].begin();//求出该方点的值——它儿子中的最小值
			S.W[dfn[i]] = w[i];
		}
		S.build(1, 1, cnt);//线段树初始化
	}
	void add(int x, int num) {//修改
		int f = fa[x];
		if (f) {//如果是修改的节点不是根就更新它的父亲
			SM[f].erase(SM[f].find(w[x]));//清除它父亲中关于修改节点的信息
			SM[f].insert(num);//更新信息
			w[f] = *SM[f].begin();//求出方点儿子中的最小值
			S.add(1, 1, cnt, dfn[f], w[f]);//线段树修改
		}
		w[x] = num;
		S.add(1, 1, cnt, dfn[x], num);//线段树修改
	}
	int ask(int x, int y) {//询问
		int res = inf;
		while (top[x] != top[y]) {
			if (dep[top[x]] < dep[top[y]]) swap(x, y);
			res = min(res, S.ask(1, 1, cnt, dfn[top[x]], dfn[x]));
			x = fa[top[x]];
		}
		if (dep[x] > dep[y]) swap(x, y);
		res = min(res, S.ask(1, 1, cnt, dfn[x], dfn[y]));
		if (x > n) res = min(res, w[fa[x]]);
		return res;
	}
} T;
struct Graph {//tarjan缩点
	int head[maxn], cntE;
	Edge e[maxm << 1];
	int stack[maxn], DFN[maxn], low[maxn];
	int idx, tot;
	bool vis[maxn];
	void addE(int a, int b) {
		e[++cntE] = (Edge) {b, head[a]}; head[a] = cntE;
	}
	void tarjan(int rt) {
		vis[stack[++tot] = rt] = true;
		low[rt] = DFN[rt] = ++idx;
		int v, tmp;
		for (int i = head[rt]; i; i = e[i].nxt) {
			v = e[i].to;
			if (!DFN[v]) {
				tarjan(v);
				low[rt] = min(low[rt], low[v]);
				if (low[v] >= DFN[rt]) {//如果它是这个图的割点，那么在栈内的在它上面的点就是一个点双连通分量
					cnt++;
					w[cnt] = inf;
					T.addE(cnt, rt);//建圆方树
					T.addE(rt, cnt);
					w[cnt] = min(w[cnt], w[rt]);
					do {
						vis[tmp = stack[tot--]] = false;
						T.addE(cnt, tmp);
						T.addE(tmp, cnt);
					} while(tmp != v);//注意不要把当前点弹出栈
				}
			} else {
				low[rt] = min(low[rt], DFN[v]);
			}
		}
	}
} G;

int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
	for (int i = 1; i <= m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		G.addE(a, b);
		G.addE(b, a);
	}
	cnt = n;
	G.tarjan(1);//缩点
	T.init(1);//树链剖分初始化
	while (q--) {
		char op; int x, y;
		scanf("%s%d%d", op, &x, &y);
		if (op[0] == 'C') {
			T.add(x, y);//修改
		} else {
			printf("%d\n", T.ask(x, y));//询问
		}
	}
	return 0;
}
```

---

## 作者：louhao088 (赞：5)

圆方树 + 树链剖分。

由于图上路径问题不好操作，我们可以先建立圆方树，把图变成树。

这可以用 tarjan 很容易完成。

题目要求路径中点最小值，我们很容易想到树链剖分维护。

我们先对每个点进行赋值。

对每个圆点其权值为其值本身。

对于方点，我们原本应将其值设为其周围值得最小值，然而这可能会使复杂度变为 $n^2$ 级别，因为一个圆点可以连向 n 个方点。我们可以做一个调整，在方点记录其儿子节点的最小值，这样每次修改都只需改其父亲节点即可。具体的，我们可以用 multiset 来维护。注意在查询时如果 LCA 是方点要算上其父亲节点，因为我们现在的这个方点未将其父亲算入统计中。

查询时就用树链剖分查询即可。

修改操作则修改其本身和其父亲，注意如果修改根节点则不用改父亲。

时间复杂度 $O(n \log^2 n)$

------

代码如下

```cpp
// Problem: CF487E Tourists
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF487E
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 2022-02-10 09:01:57
// Author : louhao088
// 

#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define ls (rt<<1)
#define rs (rt<<1|1)
#define mid (l+r>>1)
#define lowbit (x&-x)
const int maxn=2e5+5,M=34005;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,low[maxn],dfn[maxn],tot,st[maxn],tp,cnt,id[maxn],b[maxn],a[maxn];
int fa[maxn],son[maxn],siz[maxn],top[maxn],d[maxn],Min[maxn*4],idx,q,x,y;
vector<int>e[maxn],G[maxn];
multiset<int>s[maxn];
char ch;
void tarjan(int x)
{
	dfn[x]=low[x]=++tot,st[++tp]=x;
	for(auto i:G[x])
		if(!dfn[i])
		{
			tarjan(i);low[x]=min(low[x],low[i]);
			if(low[i]==dfn[x])
			{
				cnt++;e[cnt].pb(x),e[x].pb(cnt);
				for(;st[tp+1]!=i;tp--)e[cnt].pb(st[tp]),e[st[tp]].pb(cnt);
			}
		}
		else low[x]=min(low[x],dfn[i]);
}
void dfs1(int x,int f)
{
	d[x]=d[f]+1,fa[x]=f;siz[x]=1;
	for(auto i:e[x])
		if(i^fa[x])
		{
			dfs1(i,x);
			if(x>n)s[x].insert(a[i]);
			if(siz[i]>siz[son[x]])son[x]=i;
			siz[x]+=siz[i];
		}
}
void dfs2(int x,int tf)
{
	top[x]=tf;id[x]=++idx;
	if(x<=n)b[idx]=a[x];else b[idx]=*s[x].begin();
	if(son[x])dfs2(son[x],tf);
	for(auto i:e[x])
		if(i!=fa[x]&&i!=son[x])
			dfs2(i,i);
	
}
void build(int rt,int l,int r)
{
	if(l==r){Min[rt]=b[l];return;}
	build(ls,l,mid),build(rs,mid+1,r);
	Min[rt]=min(Min[ls],Min[rs]);
}
void change(int rt,int l,int r,int x,int num)
{
	if(l>x||r<x)return;
	if(l==r){Min[rt]=num;return;}
	change(ls,l,mid,x,num),change(rs,mid+1,r,x,num);
	Min[rt]=min(Min[ls],Min[rs]);
}
int query(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)return 1e9;
	if(l>=L&&r<=R)return Min[rt];
	return min(query(ls,l,mid,L,R),query(rs,mid+1,r,L,R));
}
int treequery(int x,int y)
{
	int res=1e9;
	while(top[x]!=top[y])
	{
		if(d[top[x]]<d[top[y]])swap(x,y);
		res=min(res,query(1,1,cnt,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(d[x]<d[y])swap(x,y);
	res=min(res,query(1,1,cnt,id[y],id[x]));
	if(y>n)res=min(res,a[fa[y]]);
	return res;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read(),m=read(),q=read();cnt=n;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)x=read(),y=read(),G[x].pb(y),G[y].pb(x);
	tarjan(1);dfs1(1,0);dfs2(1,1);build(1,1,cnt);
	for(int i=1;i<=q;i++)
	{
		ch=getchar();while(ch!='A'&&ch!='C')ch=getchar();x=read(),y=read();
		if(ch=='A')printf("%d\n",treequery(x,y));
		else 
		{
			if(fa[x])
			{
				s[fa[x]].erase(s[fa[x]].find(a[x]));
				s[fa[x]].insert(y);
				change(1,1,cnt,id[fa[x]],*s[fa[x]].begin());
			}
			a[x]=y;change(1,1,cnt,id[x],y);
			
		}
	}
 	return 0;
}


```


---

## 作者：Refined_heart (赞：2)

写完这题已经完全自闭了 调了好久……

## 题目大意

就是求一张图中两点间所有路径中经过的点的最小值，带修。

## 解法

我们先考虑一下性质：对于无向图显然不好做，考虑一下咋转化成一棵树。

那就往圆方树考虑呗，本题有啥性质？

观察到：

> 对于一个点双，必然存在一条路径走过该点双中的最小值。

证明比较简单。由于点双内两点之间没有一个必经点，所以我们必定可以留出一个点从走过的那个最小值点再走出去。

那么就考虑建立圆方树叭。码套路，先上一个 tarjan 找点双……

**细节1 注意点双的形成是需要满足 ```low[j]>=dfn[x]``` 的，不要犯傻打错了。**

好的，接下来怎么修改？考虑回答询问的同时其实也就能想到怎么维护修改：扔一个树剖就好了。

那就考虑写树剖叭。码套路，先上两个 dfs ……

**细节2 注意树剖的 ```query``` 啥的别打错了……**

好嘞，上述准备工作都做好了，写个修改测样例……挂掉了。

冷静分析：发现不论改方点还是圆点，都会影响到周围的点。

怎么办，暴力修改？那显然不切实际，一个菊花图就可以卡爆你。

继续考虑如何高效维护。我们知道，一个方点代表一个点双，那么，对于圆方树的树结构，每一个方点的答案其实除了它的孩子还要包含其父亲。这点也就恰好让维护变得不方便起来。

那么我们不妨先考虑无视掉父亲的影响，只维护孩子，怎么做？

维护一个 ```multiset``` 对每个方点，每次直接拿这个来暴力更新方点权值。

好的，现在这里可以实现了，那带上父亲呢？

冷静分析一波，这个父亲的影响需要满足两个条件：

* 这个点是方点

* 这个点的父亲没有被计算到

那同时满足下列两个条件的点就只有可能是……

**最近公共祖先 $(LCA)$**

所以对于每一组询问实际只有一个点需要被特殊对待！

那么就直接做就好了。

最后再附赠细节3：

更新 ```low[x]``` 不要拿 ```low[j]``` 啊……（在不 dfs 的时候），调了好久……

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=200100;
int head[N],tot,Head[N],tto,n,m,q,w[N];
struct E {
	int nxt,to;
} e[N<<1],edge[N<<1];
inline int read(){
	int s=0;
	char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch)){
		s=s*10-'0'+ch;
		ch=getchar();
	} 
	return s;
}
int nodepos,ddf,rk[N],cir[N],To[N];
inline int Min(int x,int y) {return x<y?x:y;}
multiset<int> S[N];
inline void link(int x,int y,int w=0) {
	if(w) {
		edge[++tto]=(E) {
			Head[x],y
		};
		Head[x]=tto;
		return;
	}
	e[++tot]=(E) {
		head[x],y
	};
	head[x]=tot;
}
int son[N],siz[N],dfn[N],low[N],st[N],top;
int ttop[N],pa[N],dfstime,vis[N],dep[N];
void dfs1(int x,int fa) {
	siz[x]=1;
	dep[x]=dep[fa]+1;
	pa[x]=fa;
	for(int i=Head[x]; i; i=edge[i].nxt) {
		int j=edge[i].to;
		if(j==fa)continue;
		dfs1(j,x);
		siz[x]+=siz[j];
		if(siz[j]>siz[son[x]])son[x]=j;
	}
}
void dfs2(int x,int t) {
	rk[dfn[x]=++ddf]=x;
	ttop[x]=t;
	if(!son[x])return;
	dfs2(son[x],t);
	for(int i=Head[x]; i; i=edge[i].nxt) {
		int j=edge[i].to;
		if(j==son[x]||j==pa[x])continue;
		dfs2(j,j);
	}
}
void tarjan(int x,int root) {
	dfn[x]=low[x]=++dfstime;
	st[++top]=x;
	if(x==root&&!head[x]) {
		++nodepos;
		To[nodepos]=x;
		cir[x]=nodepos;
		link(x,nodepos,1);
		link(nodepos,x,1);
		return;
	}
	int ch=0;
	for(int i=head[x]; i; i=e[i].nxt) {
		int j=e[i].to;
		if(!dfn[j]) {
			++ch;
			tarjan(j,root);
			low[x]=Min(low[x],low[j]);
			if(dfn[x]<=low[j]&&x!=root)vis[x]=1;
			if(x==root&&ch>1)vis[x]=1;
			if(low[j]>=dfn[x]) {
				int vex=-1;
				++nodepos;
				To[nodepos]=x;
				do {
					vex=st[top--];
					cir[vex]=nodepos;
					link(vex,nodepos,1);
					link(nodepos,vex,1);
				} while(vex!=j);
				cir[x]=nodepos;
				link(nodepos,x,1);
				link(x,nodepos,1);
			}
		} else low[x]=Min(low[x],dfn[j]);
	}
}
namespace SGT {
	int mi[N<<2],ls[N<<2],rs[N<<2],node;
	inline void pushup(int x) {
		mi[x]=Min(mi[ls[x]],mi[rs[x]]);
	}
	void build(int &x,int l,int r) {
		x=++node;
		if(l==r) {
			mi[x]=w[rk[l]];
			return;
		}
		int mid=(l+r)>>1;
		build(ls[x],l,mid);
		build(rs[x],mid+1,r);
		pushup(x);
	}
	void change(int x,int L,int R,int pos,int v) {
		if(L==R) {
			mi[x]=v;
			return;
		}
		int mid=(L+R)>>1;
		if(pos<=mid)change(ls[x],L,mid,pos,v);
		else change(rs[x],mid+1,R,pos,v);
		pushup(x);
	}
	int query(int x,int L,int R,int l,int r) {
		if(L>=l&&R<=r){return mi[x];} 
		int mid=(L+R)>>1,res=(1LL<<60);
		if(l<=mid)res=query(ls[x],L,mid,l,r);
		if(mid<r)res=Min(res,query(rs[x],mid+1,R,l,r));
		return res;
	}
}
using namespace SGT;
int rt;
int Query(int u,int v) {
	int res=(1LL<<60);
	while(ttop[u]!=ttop[v]) {
		if(dep[ttop[u]]<dep[ttop[v]])swap(u,v);
		res=Min(res,query(rt,1,nodepos,dfn[ttop[u]],dfn[u]));
		u=pa[ttop[u]];
	}
	if(dep[u]<dep[v])swap(u,v);
	res=Min(res,query(rt,1,nodepos,dfn[v],dfn[u]));
	if(dep[u]>dep[v])swap(u,v);
	if(u>n)res=Min(res,w[pa[u]]);
	return res;
}
void Change(int pos,int v) {
	change(rt,1,nodepos,dfn[pos],v);
	if(pos==1) {
		w[pos]=v;
		return;
	}
	int o=pa[pos];
	S[o-n].erase(S[o-n].find(w[pos]));
	S[o-n].insert(v);
	int minv=*S[o-n].begin();
	if(minv==w[o]){
		w[pos]=v;
		return;
	}
	change(rt,1,nodepos,dfn[o],minv);
	w[o]=minv;
	w[pos]=v;
}
inline void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
signed main() {
	freopen("in.txt","r",stdin);
	n=read();m=read();q=read();
	for(int i=1; i<=n; ++i)w[i]=read();
	for(int i=1; i<=m; ++i) {
		int u=read(),v=read();
		link(u,v);
		link(v,u);
	}
	nodepos=n;
	tarjan(1,1);
	memset(dfn,0,sizeof dfn);
	dfs1(1,0);
	dfs2(1,1);
	for(int i=2; i<=n; ++i) {
		S[pa[i]-n].insert(w[i]);
	}
	for(int i=n+1; i<=nodepos; ++i)
		w[i]=(S[i-n].empty()?(1LL<<60):(*S[i-n].begin()));
	memset(mi,0x7f,sizeof mi);
	build(rt,1,nodepos);
	while(q--) {
		int u,v;
		char opt;
		cin>>opt;
		u=read();v=read();
		if(opt=='A') {
			write(Query(u,v));
			putchar('\n');
			continue;
		}
		Change(u,v);
	}
	return 0;
}
```

---

## 作者：dsidsi (赞：2)

# [「Codeforces487E」Tourists-圆方树](http://codeforces.com/contest/487/problem/E)

## Description

给定一张简单无向连通图，要求支持两种操作：

 1. 修改一个点的点权。

 2. 询问两点之间所有简单路径上点权的最小值。

$n,m,q \leq 10^5$

## Solution

先不考虑修改。

圆方树有一个性质，那就是$(u,v)$路径上的方点所代表的点双并为$(u,v)$间的简单路径并。

所以只需要把方点权值设为其代表的点双中的最小值即可。

考虑修改，可以发现若直接套用上述做法，由于每个圆点连接的方点数为$O(n)$的，所以复杂度会退化为$O(n^2)$。

考虑一个常用的套路，那就是把每个方点的权值设为它子节点的权值最小值，每次修改时只用修改父节点即可，用堆维护。

注意当$lca$为方点时，要用其父节点权值更新答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

inline char gc()
{
	char c = getchar();
	while (c < 'A' || c > 'Z') c = getchar();
	return c;
}

const int maxn = 100005;

int n, m, q, w[maxn << 1];

struct edge
{
	int to, next;
} e[maxn << 1];
int h[maxn], tot;

inline void add(int u, int v)
{
	e[++tot] = (edge) {v, h[u]}; h[u] = tot;
	e[++tot] = (edge) {u, h[v]}; h[v] = tot;
}

vector<int> to[maxn << 1];
int cnt, dep[maxn << 1], siz[maxn << 1], son[maxn << 1], ord[maxn << 1], dfn[maxn << 1], low[maxn << 1], Time, fa[maxn << 1], top[maxn << 1];

struct
{
	priority_queue<int, vector<int>, greater<int> > q1, q2;
	int Top()
	{
		while (!q2.empty() && q1.top() == q2.top()) q1.pop(), q2.pop();
		return q1.top();
	}
	void insert(int x) {q1.push(x);}
	void erase(int x) {q2.push(x);}
} val[maxn];

void dfs1(int u)
{
	dep[u] = dep[fa[u]] + 1; siz[u] = 1;
	for (int v : to[u])
		if (v != fa[u]) {
			fa[v] = u; dfs1(v);
			siz[u] += siz[v];
			if (siz[v] > siz[son[u]]) son[u] = v;
			if (u > n) val[u - n].insert(w[v]);
		}
	if (u > n) w[u] = val[u - n].Top();
}

void dfs2(int u)
{
	ord[dfn[u] = ++Time] = u;
	if (son[u]) top[son[u]] = top[u], dfs2(son[u]);
	else low[top[u]] = Time;
	
	for (int v : to[u])
		if (v != fa[u] && v != son[u]) top[v] = v, dfs2(v);
}

int rt[maxn << 1], Min[maxn << 3], lch[maxn << 3], rch[maxn << 3];

#define mid ((l + r) >> 1)

void build(int &s, int l, int r)
{
	s = ++tot;
	if (s > 2e5 * 4) puts("fuck you"), exit(0);
	if (l == r) return Min[s] = w[ord[l]], void();
	build(lch[s], l, mid);
	build(rch[s], mid + 1, r);
	Min[s] = min(Min[lch[s]], Min[rch[s]]);
}

void modify(int &s, int l, int r, int p)
{
	if (l == r) return Min[s] = w[ord[l]], void();
	if (p <= mid) modify(lch[s], l, mid, p);
	else modify(rch[s], mid + 1, r, p);
	Min[s] = min(Min[lch[s]], Min[rch[s]]);
}

int query(int s, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return Min[s];
	if (qr <= mid) return query(lch[s], l, mid, ql, qr);
	else if (ql > mid) return query(rch[s], mid + 1, r, ql, qr);
	else return min(query(lch[s], l, mid, ql, qr), query(rch[s], mid + 1, r, ql, qr));
}

void modify(int v, int u)
{
	if (fa[u]) val[fa[u] - n].erase(w[u]), val[fa[u] - n].insert(v), w[fa[u]] = val[fa[u] - n].Top();
	w[u] = v; 
	modify(rt[top[u]], dfn[top[u]], low[top[u]], dfn[u]);
	if (fa[u]) u = fa[u], modify(rt[top[u]], dfn[top[u]], low[top[u]], dfn[u]);	
}

int query(int u, int v)
{
	int ans = 1e9;
	while (top[u] != top[v]) {
		if (dep[top[u]] > dep[top[v]]) ans = min(ans, query(rt[top[u]], dfn[top[u]], low[top[u]], dfn[top[u]], dfn[u])), u = fa[top[u]];
		else ans = min(ans, query(rt[top[v]], dfn[top[v]], low[top[v]], dfn[top[v]], dfn[v])), v = fa[top[v]];
	}
	if (dfn[u] > dfn[v]) swap(u, v);
	ans = min(ans, query(rt[top[v]], dfn[top[v]], low[top[v]], dfn[u], dfn[v]));
	if (u > n) ans = min(ans, w[fa[u]]);
	return ans;
}

namespace Tarjan
{

	int dfn[maxn], low[maxn], Time, stk[maxn], top;

	void dfs(int u)
	{
		dfn[u] = low[u] = ++Time;
		stk[++top] = u;
		for (int i = h[u], v; v = e[i].to, i; i = e[i].next)
			if (!dfn[v]) {
				dfs(v);
				low[u] = min(low[u], low[v]);
				if (dfn[u] == low[v]) {
					++cnt;
					while (stk[top + 1] != v)
						to[stk[top]].push_back(cnt), to[cnt].push_back(stk[top]), --top;
					to[u].push_back(cnt), to[cnt].push_back(u);
				}
			} else low[u] = min(low[u], dfn[v]);
	}
	
}

int main()
{
	n = gi(); m = gi(); q = gi();
	for (int i = 1; i <= n; ++i) w[i] = gi();
	for (int i = 1; i <= m; ++i) add(gi(), gi());

	cnt = n;
	for (int i = 1; i <= n; ++i)
		if (!Tarjan::dfn[i]) Tarjan::dfs(i);

	for (int i = 1; i <= cnt; ++i)
		if (!fa[i]) dfs1(i);
	Time = 0;
	for (int i = 1; i <= cnt; ++i)
		if (!top[i]) top[i] = i, dfs2(i);

	tot = 0;
	for (int i = 1; i <= cnt; ++i)
		if (top[i] == i) build(rt[i], dfn[i], low[i]);

	for (int i = 1; i <= q; ++i) {
		char c = gc();
		if (c == 'C') modify(gi(), gi());
		else printf("%d\n", query(gi(), gi()));
	}
	
	return 0;
}
```

---

## 作者：Genius_Z (赞：2)

前置芝士：$tarjan$求点双+圆方树+$LCT$

圆方树就是把每个点双抽象出一个方点，然后把原图中点双中的点向这个方点连边，删除原来的边，易证这样处理后得到的是最多有$2n-1$个点的树，与求一般点双不同的是，我们把连接两个的的边也看做点双。

关于圆方树的几个性质：

- 与每个圆点相连的定为方点
- 与每个方点相连的定为圆点

这两个性质都比较显然。

- 最多有$2n-1$个点

考虑原图的极端情况，即原图本身为一棵树，由于我们把仅仅连接两个点的边也看做点双，树有$n-1$条边，所以加上原图的n个点，共有$2n-1$个点。

如果没有修改的话，知道圆方树的相关知识，这题就非常简单了，硬上树剖或者$LCT$就完事了，本人选择了$LCT$，用$LCT$需要注意几点，每次求$LCA$的时候要重新把根节点$makeroot$，每次修改要先$splay$。

考虑如何处理修改。

- 每个方点维护一个$mulitset$维护最小值！

显然不行，如果是一个菊花图的话，那么单次操作复杂度$\Theta(nlogn)$，总复杂度可能会被卡成$\Theta(n^2logn)$

但是这给我们提供了一种思路。

这个想法的瓶颈就在于修改一个圆点，与它相关的所有方点都要被修改，有没有什么方法可以让每次修改的影响最小呢？

每个节点只有一个父节点，所以我们每个方点只维护它的子节点，不维护父亲圆点，这样的话，每次修改只需要修改每个圆点的父亲方点，单次操作复杂度$\Theta(logn)$，根节点特殊处理，只修改本身的值。

但是这样还需要注意一个小细节，因为不维护方点的父节点，所以当两个点的$lca$为方点时，我们要计算上$lca$的父节点的贡献。至此，本题完结。（代码仅供参考，切忌直接抄袭

Code：

```cpp
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <list>
#define inl inline
#define re register int
#define ll long long
#define fa(x) t[x].fa
#define ls(x) t[x].child[0]
#define rs(x) t[x].child[1]
#define lowbit(x) ((x) & (-x))
#define mit mulitset<int>::iterator
const int inf  = 0x7fffffff;
using namespace std;
template < class Read >
inl Read read(void) {
	Read x  = 0;
	register bool w  = 0;
	register char c  = getchar();
	while (c  > '9' || c  < '0') {
		if (c  == '-') w  = 1;
		c  = getchar();
	}
	while (c  >= '0' && c  <= '9') {
		x  = (x  << 3) + (x  << 1) + (c  ^ 48);
		c  = getchar();
	}
	return w  ? -x  : x;
}
int n, m, q, cnt, fa[1000001];
struct edge { int next, to; }e[1000001];
int head[500001], tot;
multiset<int>s[100001];
inl void add(int x, int y) {
	e[++tot] = edge{ head[x],y  }, head[x] = tot;
	e[++tot] = edge{ head[y],x  }, head[y] = tot;
}
struct node {
	int fa, child[2], w, mn;
	bool filp;
}t[500001];
namespace graph {
	struct edge { int next, to; }e[1000001];
	int dfn[1000001], low[1000001], st[1000001], top, color[1000001], tot, head[1000001], tim;
	inl void add(int x, int y) {
		e[++tot] = edge{ head[x],y }, head[x] = tot;
		e[++tot] = edge{ head[y],x }, head[y] = tot;
	}
	inl void tarjan(int x) {
		dfn[x] = low[x] = ++tim;
		st[++top] = x;
		for (re i  = head[x]; i; i  = e[i].next) {
			if (!dfn[e[i].to]) {
				tarjan(e[i].to);
				low[x] = min(low[x], low[e[i].to]);
				if (low[e[i].to] >= dfn[x]) {
					cnt++;
					while (st[top  + 1] != e[i].to) {
						color[st[top]] = cnt;
						::add(cnt, st[top]);
						top--;
					}
					::add(x, cnt);
				}
			}
			else low[x] = min(low[x], dfn[e[i].to]);
		}
	}
};
inl void maintain(int x) {
	if (x  <= n)t[x].mn  = t[x].w;
	else t[x].mn  = *s[x  - n].begin();
	if (ls(x))t[x].mn  = min(t[x].mn, t[ls(x)].mn);
	if (rs(x))t[x].mn  = min(t[x].mn, t[rs(x)].mn);
}
inl bool nroot(int x) {
	return ls(fa(x)) == x  || rs(fa(x)) == x;
}
inl bool poi(int x) {
	return rs(fa(x)) == x;
}
inl void rotate(int x) {
	re f  = fa(x), gf  = fa(f), fs  = poi(x), gfs  = poi(f), s  = t[x].child[fs  ^ 1];
	if (nroot(f))t[gf].child[gfs] = x;
	t[f].child[fs] = s, t[x].child[fs  ^ 1] = f;
	if (s)fa(s) = f;
	fa(f) = x, fa(x) = gf;
	maintain(f);
}
inl void reverse(int x) {
	swap(ls(x), rs(x));
	t[x].filp  ^= 1;
}
inl void pushdown(int x) {
	if (t[x].filp) {
		if (ls(x))reverse(ls(x));
		if (rs(x))reverse(rs(x));
		t[x].filp  = 0;
	}
}
inl void push(int x) {
	if (nroot(x))push(fa(x));
	pushdown(x);
}
inl void splay(int x) {
	push(x);
	while (nroot(x)) {
		if (nroot(fa(x)))poi(x) == poi(fa(x)) ? rotate(fa(x)) : rotate(x);
		rotate(x);
	}
	maintain(x);
}
inl void access(int x) {
	for (re i  = 0; x; x  = fa(i  = x)) {
		splay(x), rs(x) = i, maintain(x);
	}
}
inl void makeroot(int x) {
	access(x), splay(x), reverse(x);
}
inl void split(int x, int y) {
	makeroot(y), access(x), splay(x);
}
inl void link(int x, int y) {
	split(x, y);
	t[y].fa  = x;
}
inl int lca(int x, int y) {
	access(y);
	re i  = 0;
	for (; x; x  = fa(i  = x)) {
		splay(x), rs(x) = i, maintain(x);
	}
	return i;
}
inl bool spread(void) {
	register char c  = getchar();
	while (c  != 'A'&&c  != 'C')c  = getchar();
	return c  == 'A';
}
inl void dfs(int x) {
	for (re i  = head[x]; i; i  = e[i].next) {
		if (e[i].to  != fa[x]) {
			fa[e[i].to] = x;
			link(x, e[i].to);
			dfs(e[i].to);
			if (x  > n)s[x  - n].insert(t[e[i].to].w);
		}
	}
}
signed main() {
	n  = cnt  = read<int>(), m  = read<int>(), q  = read<int>();
	for (re i  = 1; i  <= n; i++) t[i].w  = read<int>(), s[i].insert(inf);
	for (re i  = 1; i  <= m; i++) graph::add(read<int>(), read<int>());
	for (re i  = 1; i  <= n; i++) {
		if (!graph::dfn[i])graph::tarjan(i);
	}
	dfs(1);
	re op, x, y;
	while (q--) {
		op  = spread(), x  = read<int>(), y  = read<int>();
		if (op) {
			makeroot(1);
			re f  = lca(x, y);
			split(x, y);
			re ans  = t[x].mn;
			if (f  > n)ans  = min(ans, t[fa[f]].w);
			printf("%d\n", ans);
		}
		else {
			splay(x);
			if (fa[x]) {
				s[fa[x] - n].erase(s[fa[x] - n].find(t[x].w));
				s[fa[x] - n].insert(t[x].w  = y);
				splay(fa[x]), maintain(fa[x]);
			}
			else t[x].w  = y;
		}
	}
}
```



---

## 作者：Owen_codeisking (赞：2)

$Tarjan$ 点双 + 圆方树 + 树剖 + 线段树 + $multiset$

如果你看到算法就会写的话，说明你非常的厉害。。。

刚学圆方树就做到这题，后来不耐烦直接上板子了。。。

### 前置知识：好码力

码码码……如果你想要小数据的话，你可以 [右转出门](http://uoj.ac/problem/30)

### 1、无向图的处理利器：圆方树

如果你不知道圆方树是什么，你可以去做模板还有 [[SDOI2018]战略游戏](https://www.luogu.org/problemnew/show/P4606)

因为这道题一条路径每个点**不重复**，所以可以上圆方树。

首先 $Tarjan$ 点双建出圆方树，然后对于每个圆点和方点考虑哪些信息。

### 2、对于一个圆点

圆点的话就直接走吧。。。只要经过的时候算一个最小值即可。

### 3、对于一个方点

走到方点说明要走出这个环了，所以我们有两种方式走出这个环：

![](https://cdn.luogu.com.cn/upload/pic/53777.png)

~~比较简陋，不要在意。~~

蓝色边表示方点连向儿子，红色边表示方点连向父亲。

因为我们计算圆点的时候计算过父亲了，所以我们大可以只维护蓝色边连向的结点的权值最小值。

因为最小值最少会有一个，两种方式出环都可以至少遍历到一个最小值，所以我们开 $n$ 个 $multiset$ 对于方点记录最小值。

### 4、合并最小值的信息

让我们看看操作：

操作 $1$：单点修改

操作 $2$：路径查询

若没修改，我们直接对于一条路径维护一个最小值就可以了。直接上树剖 + 线段树。

不过还要特判！若 $LCA(x,y)$ 是方点的话，可以绕过来，所以还要对 $val[fa[x]]$ 取最小。

带修改的话，我们继续分类。

若修改的是根，那就直接改完顺便在线段树中更新一下。

若修改的不根，我们在更新圆点的信息的同时还要更新方点。

什么意思？？？

就是在它父亲这个方点上的 $multiset$ 上删掉原来的权值，加入新的权值。当然线段树上也要更新。

时间复杂度 $O(n\log^2 n)$，瓶颈在树剖 + 线段树上。

如果采用 $LCT$ 的话就是 $O(n\log n)$ 的，但是这个常数飞起啊。。。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define lson (rt<<1)
#define rson (rt<<1|1)
using namespace std;
const int maxn=200000+10;
const int inf=0x3f3f3f3f;
int n,m,q,head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
int N,low[maxn],dfn[maxn],tim,sta[maxn],top;
multiset<int> s[maxn];

inline int read(){
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

namespace RST{
	int val[maxn],sum[maxn<<2],head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
	int top[maxn],dep[maxn],siz[maxn],son[maxn],fa[maxn],id[maxn],mp[maxn],tim;
	inline void pushup(int rt){sum[rt]=min(sum[lson],sum[rson]);}
	void build(int l,int r,int rt){
		if(l == r){sum[rt]=val[mp[l]];return;}
		int mid=(l+r)>>1;
		build(l,mid,lson);
		build(mid+1,r,rson);
		pushup(rt);
	}
	void update(int x,int v,int l,int r,int rt){
		if(l == r){sum[rt]=v;return;}
		int mid=(l+r)>>1;
		if(x <= mid) update(x,v,l,mid,lson);
		else update(x,v,mid+1,r,rson);
		pushup(rt); 
	}
	int query(int L,int R,int l,int r,int rt){
		if(L <= l && r <= R) return sum[rt];
		int mid=(l+r)>>1,ans=inf;
		if(L <= mid) ans=min(ans,query(L,R,l,mid,lson));
		if(R > mid) ans=min(ans,query(L,R,mid+1,r,rson));
		return ans;
	}
	inline void addedge(int x,int y){
		to[++tot]=y;
		nxt[tot]=head[x];
		head[x]=tot;
	}
	inline void add(int x,int y){addedge(x,y),addedge(y,x);}
	void dfs1(int x,int f){
		siz[x]=1;fa[x]=f;dep[x]=dep[f]+1;
		int maxson=-1;
		for(int i=head[x],y;i;i=nxt[i]){
			y=to[i];
			if(y==f) continue;
			dfs1(y,x);siz[x]+=siz[y];
			if(siz[y]>maxson) maxson=siz[y],son[x]=y;
		}
	}
	void dfs2(int x,int topf){
		id[x]=++tim;mp[tim]=x;top[x]=topf;
		if(son[x]) dfs2(son[x],topf);
		for(int i=head[x],y;i;i=nxt[i]){
			y=to[i];
			if(y==fa[x]||y==son[x]) continue;
			dfs2(y,y);
		}
	}
	inline int ask(int x,int y){
		int ans=inf;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			ans=min(ans,query(id[top[x]],id[x],1,N,1));
			x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		ans=min(ans,query(id[x],id[y],1,N,1));
		if(x>n) ans=min(ans,val[fa[x]]);
		return ans;
	}
	inline void solve(){
		dfs1(1,0);dfs2(1,1);
		for(int i=2;i<=n;i++) s[fa[i]-n].insert(val[i]);
		for(int i=n+1;i<=N;i++) val[i]=s[i-n].empty()?inf:*s[i-n].begin();
		build(1,N,1);
		char op;int x,y;
		while(q--){
			op=getchar();
			while(!isalpha(op)) op=getchar();
			x=read(),y=read();
			if(op=='C'){
				if(x<=n&&x>1){
					s[fa[x]-n].erase(s[fa[x]-n].find(val[x]));
					s[fa[x]-n].insert(y);
					val[fa[x]]=s[fa[x]-n].empty()?inf:*s[fa[x]-n].begin();
					update(id[fa[x]],val[fa[x]],1,N,1);
				}
				val[x]=y;update(id[x],val[x],1,N,1);
			}
			else printf("%d\n",ask(x,y));
		}
	}
}

inline void addedge(int x,int y){
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

void tarjan(int u,int f){
	low[u]=dfn[u]=++tim;sta[++top]=u;
	int x;
	for(int i=head[u],v;i;i=nxt[i]){
		v=to[i];
		if(v==f) continue;
		if(!dfn[v]){
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				N++;RST::add(N,u);
				do {
					x=sta[top--];
					RST::add(N,x);
				}while(x!=v);
			}
		}
		else low[u]=min(low[u],dfn[v]);
	}
}

int main()
{
	n=read(),m=read(),q=read();
	int x,y;
	for(int i=1;i<=n;i++) RST::val[i]=read();
	for(int i=1;i<=m;i++){
		x=read(),y=read();
		addedge(x,y),addedge(y,x);
	}
	N=n;tarjan(1,0);RST::solve();
	return 0;
}
```

---

## 作者：CHHC (赞：1)

圆方树模板题（

前置知识：求点双连通分量（可以用某Tarjan算法）；树链剖分。

## 题意

N个点M条边的图，带点权。有两种操作：`C a w` 修改a点权值为w，以及`A a b`查询a、b之间任意一条简单路径上的最小点权。

## 思路

我们需要快速地表示a、b之间所有简单路径上的点所构成的集合。图的性质不算好，且这里的修改操作并没有涉及图的结构变化，我们考虑缩点把图转化成树。

将所有点双连通分量新建一个点代表它，然后仅将所有点与其所在的所有点双联通分量的代表点之间连边。显然一个点可以同时在多个BCC内，新图可以保证联通。同时新图中若有环，则环上所有BCC可以缩成一个更大的BCC，矛盾。所以新图是一棵树。

**我们将这棵树称作圆方树，原来的点记为圆点，BCC代表点记为方点。**

相对朴素地：对于查询操作，查询树上a、b之间的简单路径（显然唯一）上的最小值即可。用树剖可以较为容易地解决。对于修改操作，修改需要修改的点并更新其所在的所有BCC的代表点的权值。

但是这个方法有一点问题：如果一个点对应很多BCC，再反复对其进行修改，那么显然复杂度爆炸。

优化：我们选择一个圆点当根，则每个圆点之父为方点、每个方点之父为圆点（建树的时候保证了这一点）。这样我们可以发现，在查询(a,b)之间简单路径上最小值的时候，路径上所有方点的父亲都在此路径内（除非，当a,b的lca为方点时，这个点的父节点不在路径内。特判即可）。由此性质，我们在修改时仅修改圆点及其父节点，仍可保证在查询时答案不变。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>

inline void cmin(int &x, int y)
{
    x = min(x, y);
}

const int inf = 1000000007;

int N, M, S, L; // 点数 | 边数 | 询问数量 | ≥总点数的最小2的幂，用于线段树 | (´･_･`)
vector<int> e[100010]; // 存边
int w[200010]; // [1,N]部分存圆点权值，[N,N+bcccnt]部分存方点权值
#define ws ws_
multiset<int> ws[200010]; // 维护方点的可取权值集合。ws好像和某个关键字或者内置函数冲突了

// 这一堆是计算点双联通分量用的
// 顺便，如果Tarjan写存点而不是存边的话应该会简单一些
int dfscnt = 0; // 原图的DFS序
int num[100010]; // 存储某点的原DFS序
int lowpt[100010]; // 就是Tarjan那个lowpt（大雾）
stack<pii> st; // 同上（
int bcccnt = 0; // BCC的序号
vector<int> bcc[100010]; // 存每个BCC内的点
int col[100010]; // 用来配合tbcc[]搞出bcc[]的……

// 这一堆大概是和树剖有关的
vector<int> ne[200010]; // 新边
int fa[200010]; // 父节点
int dep[200010]; // 深度
int sz[200010]; // 子树大小
int hson[200100]; // 重儿子
int reccnt = 0; // 树的新DFS序
int id[200010], rec[200010]; // 存储某点的新DFS序，以及某个序号对应的点
int tp[200010]; // 链的顶端

// 线段树用。
#define data data_
int data[800010]; // …似乎data也和某个关键字或者内置函数冲突了

void DFS(int x, int p) // Tarjan求点双连通分量
{
    num[x] = ++dfscnt;
    lowpt[x] = num[x];
    for (int i = 0; i < e[x].size(); i++)
    {
        int &to = e[x][i];
        if (!num[to])
        {
            st.push(make_pair(x, to));
            DFS(to, x);
            cmin(lowpt[x], lowpt[to]);
            if (lowpt[to] >= num[x]) // 找到一个新的BCC
            {
                bcccnt++;
                vector<int> tbcc; // 可能有重复点。去重之后得到bcc[]。
                while (!st.empty() && num[st.top().first] >= num[to])
                {
                    tbcc.push_back(st.top().first);
                    tbcc.push_back(st.top().second);
                    st.pop();
                }
                stack<pii> nst;
                while (!st.empty() && st.top() != make_pair(x, to))
                {
                    nst.push(st.top());
                    st.pop();
                }
                assert(!st.empty());
                st.pop();
                tbcc.push_back(x);
                tbcc.push_back(to);
                while (!nst.empty())
                {
                    st.push(nst.top());
                    nst.pop();
                }
                for (int j = 0; j < tbcc.size(); j++)
                {
                    int &cur = tbcc[j];
                    if (col[cur] != bcccnt)
                    {
                        bcc[bcccnt].push_back(cur);
                        col[cur] = bcccnt;
                    }
                }
            }
        }
        else if (to != p && num[to] < num[x])
        {
            st.push(make_pair(x, to));
            cmin(lowpt[x], num[to]);
        }
    }
}

void DFS0(int x, int p, int d) // 树剖第一遍DFS。求fa[],dep[],sz[],hson[]
{
    fa[x] = p;
    dep[x] = d;
    sz[x] = 1;
    for (int i = 0; i < ne[x].size(); i++)
    {
        int &to = ne[x][i];
        if (to != p)
        {
            DFS0(to, x, d + 1);
            sz[x] += sz[to];
        }
    }
    int maxsz = -1;
    hson[x] = -1;
    for (int i = 0; i < ne[x].size(); i++)
    {
        int &to = ne[x][i];
        if (to != p && sz[to] > maxsz)
        {
            maxsz = sz[to];
            hson[x] = to;
        }
    }
}

void DFS1(int x, int p, int t) // 树剖第二遍DFS。求新dfs序id[]以及rec[]，顺便求出tp[]
{
    reccnt++;
    id[x] = reccnt;
    rec[reccnt] = x;
    tp[x] = t;
    if (hson[x] != -1)
        DFS1(hson[x], x, t); 
    for (int i = 0; i < ne[x].size(); i++)
    {
        int &to = ne[x][i];
        if (to != p && to != hson[x])
        {
            DFS1(to, x, to);
        }
    }
}

inline void pushup(int o) // 线段树更新当前点
{
    data[o] = min(data[o << 1], data[o << 1 | 1]);
}

void build(int o, int l, int r) // 线段树建树
{
    if (l == r)
    {
        if (l <= N + bcccnt)
            data[o] = w[rec[l]];
        else
            data[o] = inf;
        return;
    }
    int mid = (l + r) >> 1;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    pushup(o);
}

int query(int o, int l, int r, int ql, int qr) // 线段树区间查询最小值
{
    if (l == r || (ql <= l && r <= qr))
        return data[o];
    int mid = (l + r) >> 1;
    int res = inf;
    if (ql <= mid)
        cmin(res, query(o << 1, l, mid, ql, qr));
    if (mid + 1 <= qr)
        cmin(res, query(o << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

void upd(int o, int l, int r, int pos, int val) // 线段树单点更新
{
    if (l == r)
    {
        data[o] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        upd(o << 1, l, mid, pos, val);
    else
        upd(o << 1 | 1, mid + 1, r, pos, val);
    pushup(o);
}

inline int lca(int u, int v) // 树剖求lca
{
    int fu = tp[u], fv = tp[v];
    while (fu != fv)
    {
        if (dep[fu] > dep[fv])
        {
            u = fa[fu];
            fu = tp[u];
        }
        else
        {
            v = fa[fv];
            fv = tp[v];
        }
    }
    if (dep[u] < dep[v])
        return u;
    else
        return v;
}

int getmin(int u, int v) // 树剖求树上两点间最小值
{
    int ans = inf;
    int fu = tp[u], fv = 304; fv = tp[v];
    while (fu != fv)
    {
        if (dep[fu] > dep[fv])
        {
            cmin(ans, query(1, 1, L, id[fu], id[u]));
            u = fa[fu];
            fu = tp[u];
        }
        else
        {
            cmin(ans, query(1, 1, L, id[fv], id[v]));
            v = fa[fv];
            fv = tp[v];
        }
    }
    cmin(ans, query(1, 1, L, min(id[u], id[v]), max(id[u], id[v])));
    int an = lca(u, v);
    if (an > N) // 特判：u,v的lca为方点
    {
        cmin(ans, w[fa[an]]);
    }
    return ans;
}

void update(int x, int val) // 修改操作
{
    if (fa[x] != -1) // 更新圆点父亲的权值
    {
        ws[fa[x]].erase(ws[fa[x]].lower_bound(w[x]));
        ws[fa[x]].insert(val);
        w[fa[x]] = *ws[fa[x]].begin();
        upd(1, 1, L, id[fa[x]], w[fa[x]]);
    }
    w[x] = val; // 更新圆点权值
    upd(1, 1, L, id[x], val);
}

signed main()
{
    ios::sync_with_stdio(false);

    cin >> N >> M >> S;
    for (int i = 1; i <= N; i++)
        cin >> w[i];
    for (int i = 1; i <= M; i++)
    {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    DFS(1, -1);
    L = N + bcccnt;
    while (L & (L - 1))
        L++;
    for (int i = 1; i <= bcccnt; i++) // 重新构图
    {
        for (int j = 0; j < bcc[i].size(); j++)
        {
            int &cur = bcc[i][j];
            ne[cur].push_back(N + i);
            ne[N + i].push_back(cur);
        }
    }
    DFS0(1, -1, 1);
    DFS1(1, -1, 1);
    for (int i = N + 1; i <= N + bcccnt; i++) // 求方点初始权值。注意方点序号从N+1开始
    {
        for (int j = 0; j < ne[i].size(); j++)
        {
            int &to = ne[i][j];
            if (to != fa[i])
                ws[i].insert(w[to]);
        }
        w[i] = *ws[i].begin();
    }
    build(1, 1, L);
    while (S--)
    {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'A')
            cout << getmin(x, y) << endl;
        else
            update(x, y);
    }

    return 0;
}
```

---

## 作者：lhm_ (赞：1)

若从 $x$ 到 $y$ 的任意一条路径经过了一个点双连通分量，则从 $x$ 到 $y$ 一定可以经过该点双连通分量中的每一个点。

用广义圆方树来维护一般无向图，每个方点的权值为其相邻的圆点的权值的最小值，然后可以用树剖来修改和查询。

但是这样修改的复杂度是不正确的，若一个圆点相邻有许多方点，像菊花图一样，那么复杂度是无法接受的。

考虑更改方点的权值定义，权值改为在圆方树上的其儿子权值的最小值。这样修改一个圆点时，只用考虑其父亲方点的权值的变化，这样修改复杂度就正确了。

在每个方点上用 $multiset$ 来维护其儿子的权值，查询时两点的 $lca$ 若为方点，则还要考虑其父亲圆点的贡献。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 400010
#define maxm 1600010
#define inf 2000000000
#define ls (cur<<1)
#define rs (cur<<1|1)
#define mid ((l+r)>>1)
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,q,tot,dfn_cnt,cnt,root=1;
int val[maxn],dfn[maxn],low[maxn],st[maxn];
int fa[maxn],de[maxn],siz[maxn],son[maxn],top[maxn],rev[maxn],mi[maxm];
vector<int> ve[maxn];
multiset<int> s[maxn];
char opt[5];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]=(edge){to,head[from]};
    head[from]=edge_cnt;
}
void addedge(int x,int y)
{
    ve[x].push_back(y);
}
void tarjan(int x)
{
    dfn[x]=low[x]=++dfn_cnt,st[++cnt]=x;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(!dfn[y])
        {
            tarjan(y),low[x]=min(low[x],low[y]);
            if(dfn[x]<=low[y])
            {
                tot++;
                int now;
                do
                {
                    now=st[cnt--];
                    addedge(tot,now),addedge(now,tot);
                }while(now!=y);
                addedge(tot,x),addedge(x,tot);
            }
        }
        else low[x]=min(low[x],dfn[y]);
    }
}
void dfs_son(int x,int fath)
{
    de[x]=de[fath]+1,siz[x]=1,fa[x]=fath,s[fath].insert(val[x]);
    for(int i=0;i<ve[x].size();++i)
    {
        int  y=ve[x][i];
        if(y==fath) continue;
        dfs_son(y,x),siz[x]+=siz[y];
        if(siz[y]>siz[son[x]]) son[x]=y;
    }
}
void dfs_chain(int x,int tp)
{
    dfn[x]=++dfn_cnt,rev[dfn_cnt]=x,top[x]=tp;
    if(son[x]) dfs_chain(son[x],tp);
    for(int i=0;i<ve[x].size();++i)
    {
        int y=ve[x][i];
        if(dfn[y]) continue;
        dfs_chain(y,y);
    }
}
void build(int l,int r,int cur)
{
    if(l==r)
    {
        int x=rev[l];
        if(x<=n) mi[cur]=val[x];
        else mi[cur]=*s[x].begin();
        return;
    }
    build(l,mid,ls),build(mid+1,r,rs);
    mi[cur]=min(mi[ls],mi[rs]);
}
void modify(int l,int r,int pos,int v,int cur)
{
    if(l==r)
    {
        mi[cur]=v;
        return;
    }
    if(pos<=mid) modify(l,mid,pos,v,ls);
    else modify(mid+1,r,pos,v,rs);
    mi[cur]=min(mi[ls],mi[rs]);
}
int query(int L,int R,int l,int r,int cur)
{
    if(L<=l&&R>=r) return mi[cur];
    int v=inf;
    if(L<=mid) v=min(v,query(L,R,l,mid,ls));
    if(R>mid) v=min(v,query(L,R,mid+1,r,rs));
    return v;
}
int ask(int x,int y)
{
    int v=inf;
    while(top[x]!=top[y])
    {
        if(de[top[x]]<de[top[y]]) swap(x,y);
        v=min(v,query(dfn[top[x]],dfn[x],1,tot,root));
        x=fa[top[x]];
    }
    if(dfn[x]>dfn[y]) swap(x,y);
    v=min(v,query(dfn[x],dfn[y],1,tot,root));
    if(x>n) v=min(v,val[fa[x]]);
    return v;
}
int main()
{
    read(n),read(m),read(q),tot=n,val[0]=inf;
    for(int i=1;i<=n;++i) read(val[i]);
    for(int i=1;i<=m;++i)
    {
        int x,y;
        read(x),read(y);
        add(x,y),add(y,x);
    }
    tarjan(1),dfn_cnt=0,memset(dfn,0,sizeof(dfn));
    dfs_son(1,0),dfs_chain(1,1),build(1,tot,root);
    while(q--)
    {
        int x,y;
        scanf("%s",opt),read(x),read(y);
        if(opt[0]=='C')
        {
            s[fa[x]].erase(s[fa[x]].find(val[x]));
            s[fa[x]].insert(y),val[x]=y;
            modify(1,tot,dfn[x],y,root);
            modify(1,tot,dfn[fa[x]],*s[fa[x]].begin(),root);
        }
        else printf("%d\n",ask(x,y));
    }
    return 0;
}
```

---

## 作者：suxxsfe (赞：1)

板子大集合？~~那我不看题解也没做出来/kk~~  
思路不算难，但是实现起来比较码农  

tarjan 建广义圆方树 + 对圆方树树剖 + 用 `multiset` 维护每个双联通分量最小值  

[传送门](http://codeforces.com/problemset/problem/487/E)  
给出一个图，每个点有一个权值  
现在给 $q$ 个操作  

- 更改一个点的权值  
- 查询 $x$ 到 $y$ 的所有简单路径（不能有重复的点）中，能走到的最小权值是多少  

-------------------------  

首先，[要会用 multiset](https://blog.csdn.net/sodacoco/article/details/84798621  )，还要会tarjan，并且会用他构建广义圆方树，[这里](https://www.cnblogs.com/suxxsfe/p/12720339.html)  

再来看这个题，可以~~猜出~~ 一个结论：一个点双连通图（分量），对于其中任意三个点 $a,b,c$，一定能找出一条 $a,b$ 间的简单路径，使得其穿过 $c$  
因为一个点双应该是一个环，然后再加上一堆边组成的，所以找到上面要求的这样一个路径其实很容易，所以就 ~~感性理解~~ 一下就好  
比较详细的证明[CF官方题解](http://codeforces.com/blog/entry/14832)上有  

那么，我们只要走到一个点双中，就直接取这个点双的最小值就行了，然后可以继续往前走出去  
所以就建一棵圆方树就好了，每个方点维护这个点双中的最小值  
对每个方点，还要用一个 `multiset`（自带排序）来存这个点双的所有点的权值，方便删除和添加新权值来实现更改  

对于查询，就直接查这两个点在树上的路径中权值最小值就行了，用树剖维护  
考虑怎么修改  
发现如果像上面那样维护，每次修改一个圆点权值，都会波及到他周围所有的方点，容易被菊花图卡飞  
所以，每个方点的权值应该是：他所有相邻的圆点（就是他所对应的那个点双中的所有点），除了它在圆方树上的父亲，中的点权最小值  
这样，修改操作时，每个圆点被修改，都只会波及到它的父亲，就只去更改一下父亲的信息就行了  
查询时也要加一个，就是如果 $x,y$ 的 LCA 是个方点，那么还要和它的父亲（是个圆点）的权值取 $\min$  

$\texttt{code.}$ 写了我一上午/kk  

```cpp  
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>
#include<set>
#include<iomanip>
#include<cstring>
#define reg register
#define EN std::puts("")
#define LL long long
inline int read(){
	register int x=0;register int y=1;
	register char c=std::getchar();
	while(c<'0'||c>'9'){if(c=='-') y=0;c=std::getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^48);c=std::getchar();}
	return y?x:-x;
}
#define N 200006
#define M 400006
int n,m;
int w[N];
std::multiset<int>set[N];
struct graph{
	int fir[N],nex[M],to[M],tot;
	inline void add(int u,int v){
		to[++tot]=v;
		nex[tot]=fir[u];fir[u]=tot;
	}
}G,T;
struct get_bcc{
	int top,stack[N];
	int dfn[N],low[N],dfscnt;
	int bcccnt;
	void tarjan(int u){
		dfn[u]=low[u]=++dfscnt;stack[top++]=u;
		for(reg int v,i=G.fir[u];i;i=G.nex[i]){
			v=G.to[i];
			if(!dfn[v]){
				tarjan(v);low[u]=std::min(low[u],low[v]);
				if(low[v]>=dfn[u]){
					bcccnt++;
					do{
						T.add(bcccnt,stack[--top]);T.add(stack[top],bcccnt);
					}while(stack[top]^v);
					T.add(bcccnt,u);T.add(u,bcccnt);
				}
			}
			else low[u]=std::min(low[u],dfn[v]);
		}
	}
}BCC;
struct TREE{
	int fa[N],deep[N],size[N],son[N],index[N];
	int top[N],dfn[N],dfscnt;
	void dfs1(int u,int fat){
		fa[u]=fat;deep[u]=deep[fat]+1;size[u]=1;
		for(reg int v,i=T.fir[u];i;i=T.nex[i]){
			v=T.to[i];
			if(v!=fat){
				dfs1(v,u);size[u]+=size[v];
				if(size[v]>size[son[u]]) son[u]=v;
			}
		}
	}
	void dfs2(int u,int topnow){
		top[u]=topnow;dfn[u]=++dfscnt;index[dfscnt]=u;
		if(!son[u]) return;
		dfs2(son[u],topnow);
		for(reg int v,i=T.fir[u];i;i=T.nex[i]){
			v=T.to[i];
			if(!dfn[v]) dfs2(v,v);
		}
	}
	struct tr {
		tr *ls,*rs;
		int min;
	}dizhi[N<<1],*root=&dizhi[0];
	int tot;
	inline void pushup(tr *tree){tree->min=std::min(tree->ls->min,tree->rs->min);}
	void build(tr *tree,int l,int r){
		if(l==r) return tree->min=w[index[l]],void();
		int mid=(l+r)>>1;
		tree->ls=&dizhi[++tot];tree->rs=&dizhi[++tot];
		build(tree->ls,l,mid);build(tree->rs,mid+1,r);
		pushup(tree);
	}
	void change(tr *tree,int l,int r,int pos,int k){
		if(l==r) return tree->min=k,void();
		int mid=(l+r)>>1;
		if(pos<=mid) change(tree->ls,l,mid,pos,k);
		else change(tree->rs,mid+1,r,pos,k);
		pushup(tree);
	}
	int get_min(tr *tree,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return tree->min;
		int mid=(l+r)>>1;
		if(qr<=mid) return get_min(tree->ls,l,mid,ql,qr);
		if(ql>mid) return get_min(tree->rs,mid+1,r,ql,qr);
		return std::min(get_min(tree->ls,l,mid,ql,qr),get_min(tree->rs,mid+1,r,ql,qr));
	}
	inline int find(int x,int y){
		int ret=0x7f7f7f7f;
		while(top[x]!=top[y]){
			if(deep[top[x]]<deep[top[y]]) x^=y,y^=x,x^=y;
			ret=std::min(ret,get_min(root,1,BCC.bcccnt,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		if(deep[x]>deep[y]) x^=y,y^=x,x^=y;
		ret=std::min(ret,get_min(root,1,BCC.bcccnt,dfn[x],dfn[y]));
		if(x>n) ret=std::min(ret,w[fa[x]]);
		return ret;
	}
}Tree;
int main(){
//		std::freopen("tmp.txt","r",stdin);
	BCC.bcccnt=n=read();m=read();int q=read();
	for(reg int i=1;i<=n;i++) w[i]=read();
	for(reg int u,v,i=1;i<=m;i++){
		u=read();v=read();
		G.add(u,v);G.add(v,u);
	}
	BCC.tarjan(1);
//		std::printf("bcccnt : %d\ntot of edges : %d\n\n",BCC.bcccnt,T.tot);
	Tree.dfs1(1,0);
	Tree.dfs2(1,1);
	for(reg int i=2;i<=n;i++) set[Tree.fa[i]-n].insert(w[i]);
	//一定从 2 开始循环，因为 1 是跟，用它的父亲（其实他也没有父亲，这里说的是它的 fa 数组），减 n 减成负数，RE 
	for(reg int i=n+1;i<=BCC.bcccnt;i++)
		w[i]=set[i-n].empty()?0x7f7f7f7f:*set[i-n].begin();
	Tree.build(Tree.root,1,BCC.bcccnt);
	reg int x,y;char op;
	while(q--){
		std::scanf("%c",&op);
		x=read();y=read();
		if(op=='C'){
			Tree.change(Tree.root,1,BCC.bcccnt,Tree.dfn[x],y);
			if(x==1){w[1]=y;continue;}
			int ind=Tree.fa[x]-n;
			set[ind].erase(set[ind].find(w[x]));
			set[ind].insert(y);
			int min=*set[ind].begin();
			w[x]=y;
			if(min!=w[ind+n]) Tree.change(Tree.root,1,BCC.bcccnt,Tree.dfn[ind+n],min);
			w[ind+n]=min;
		}
		else std::printf("%d\n",Tree.find(x,y));
	}
	return 0;
}
```

---

## 作者：Leianha (赞：1)

## 圆方树+树链剖分

[博客阅读](https://www.cnblogs.com/wljss/p/12620024.html)

先建出来圆方树，圆点为本身的权值，方点为与之相连的圆点的最小值。

很明显答案就是询问的两点间的路径上的最小值。

考虑修改操作

$1$ .圆点：直接改

$2$ .方点：对每个方点开一个 $multiset$ ，存储相邻的点的权值。

我们发现这样的话修改一个圆点的时候会修改很多方点，效率低。

我们将 $multiset$ 改为存储儿子的权值，这样我们修改圆点的时候就只用修改相应的父亲节点了。

用树剖维护修改和查询操作就行了。注意查询时若 $lca$ 是方点，还要考虑其父亲圆点。

注意 $multiset$ 的删除操作的正确用法。

```cpp
#include<iostream>
#include<cstdio>
#include<set>
#define lson (k<<1)
#define rson ((k<<1)|1)
using namespace std;
int n, m, q, tot, Tot, num, Top, x, y, cnt, a, b;
const int N = 400010;
int head[N], to[N], nt[N], Head[N], To[N], Nt[N], dfn[N], low[N], zhan[N], w[N], nfd[N], siz[N], son[N], top[N], dep[N], fa[N], tr[N << 2];
char opt[3];
multiset<int>s[N];
multiset<int>::iterator it;
void add(int f, int t)
{
	to[++tot] = t; nt[tot] = head[f]; head[f] = tot;
}
void ADD(int f, int t)
{
	To[++Tot] = t; Nt[Tot] = Head[f]; Head[f] = Tot;
}
void Tarjan(int x)
{
	dfn[x] = low[x] = ++cnt; zhan[++Top] = x;
	for (int i = Head[x]; i; i = Nt[i])
		if (!dfn[To[i]])
		{
			Tarjan(To[i]); low[x] = min(low[x], low[To[i]]);
			if (low[To[i]] >= dfn[x])
			{
				add(++num, x); add(x, num);
				int t;
				do
				{
					t = zhan[Top--]; add(num, t); add(t, num);
				} while (t != To[i]);
			}
		}
		else low[x] = min(low[x], dfn[To[i]]);
}
void dfs1(int x, int f)
{
	fa[x] = f; dep[x] = dep[f] + 1; siz[x] = 1;
	if (x <= n && f)s[f].insert(w[x]);
	for (int i = head[x]; i; i = nt[i])
		if (to[i] != f)
		{
			dfs1(to[i], x);
			siz[x] += siz[to[i]];
			if (siz[to[i]] > siz[son[x]])son[x] = to[i];
		}
	if (x > n)w[x] = *s[x].begin();
}
void dfs2(int x, int t)
{
	top[x] = t; dfn[x] = ++cnt; nfd[cnt] = x;
	if (son[x])dfs2(son[x], t);
	else return;
	for (int i = head[x]; i; i = nt[i])
		if (to[i] != fa[x] && to[i] != son[x])dfs2(to[i], to[i]);
}
void pushup(int k)
{
	tr[k] = min(tr[lson], tr[rson]);
}
void build(int k, int l, int r)
{
	if (l == r)
	{
		tr[k] = w[nfd[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(lson, l, mid); build(rson, mid + 1, r);
	pushup(k);
}
int ask(int k, int l, int r, int x, int y)
{
	if (x <= l && r <= y)return tr[k];
	int mid = (l + r) >> 1, res = 2e9;
	if (x <= mid)res = min(res, ask(lson, l, mid, x, y));
	if (mid + 1 <= y)res = min(res, ask(rson, mid + 1, r, x, y));
	return res;
}
void change(int k, int l, int r, int pos, int val)
{
	if (l == r)
	{
		tr[k] = val;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid)change(lson, l, mid, pos, val);
	else change(rson, mid + 1, r, pos, val);
	pushup(k);
}
int cask(int x, int y)
{
	int res = 2e9;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])swap(x, y);
		res = min(res, ask(1, 1, num, dfn[top[x]], dfn[x])); x = fa[top[x]];
	}
	if (dep[x] < dep[y])swap(x, y);
	res = min(res, ask(1, 1, num, dfn[y], dfn[x]));
	if (y > n)res = min(res, w[fa[y]]);
	return res;
}
int main()
{
	cin >> n >> m >> q; num = n;
	for (int i = 1; i <= n; ++i)scanf("%d", &w[i]); w[0] = 2e9;
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d", &x, &y);
		ADD(x, y); ADD(y, x);
	}
	Tarjan(1); cnt = 0; dfs1(1, 0); dfs2(1, 1); build(1, 1, num);
	while (q--)
	{
		scanf("%s%d%d", opt, &a, &b);
		if (opt[0] == 'C')
		{
			if (fa[a])
			{
				it = s[fa[a]].find(w[a]), s[fa[a]].erase(it), s[fa[a]].insert(b);
				w[fa[a]] = *s[fa[a]].begin(), change(1, 1, num, dfn[fa[a]], w[fa[a]]);
			}
			w[a] = b; change(1, 1, num, dfn[a], b);
		}
		else printf("%d\n", cask(a, b));
	}
	return 0;
}
```


---

## 作者：Larunatrecy (赞：0)


### 解题思路
不会圆方树的可以看我的博客[圆方树学习记录及例题](https://blog.csdn.net/jwg2732/article/details/118659688)。

首先Tarjan寻找点双连通分量，然后建立圆方树，每个方点存这个点双内的最小点权。

将圆方树树链剖分之后，对于修改操作，将这个点连的所有方点的值更新。

对于查询操作，直接查询树上两点之间路径的最小值。

~~然后就AC了~~ 。

怎么可能呢，如果一个圆点连着非常多个方点，那么时间复杂度就飞天了。

正确的做法是：  

建出圆方树后，每个方节点的值是它的所有子节点的最小值，而不包括父节点
可以用multiset维护每个方点的权值。

那么修改操作时，只需要更新这个点和它的父节点就可以了。

查询时，如果这两个点的LCA是方点，他应该有他父亲圆点的值，但是并没有存储，因此在查询一下LCA的父节点的值就行了。

其余的就是树剖的基本操作：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N = 2e5+7;
const LL INF = 1e9+7; 
const LL maxn=1e5+7;
struct node
{
	LL y,next;
}e[2*N];
LL link[N],t=0,w[N],n,m,q,a[N];
void add(LL x,LL y)
{
	e[++t].y=y;
	e[t].next=link[x];
	link[x]=t;
}
inline LL read()
{
	LL X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}
stack<LL> st;
LL dfn[maxn],low[maxn];
bool cut[maxn];
vector<LL> Dcc[N];
LL num=0,root,cnt=0;
LL Size=0;
void tarjan(LL x)
{
	dfn[x]=low[x]=++num;
	st.push(x);
	if(x==root&&link[x]==0)
	{
		Dcc[++cnt].push_back(x);
		return;
	}
	LL flag=0;
	for(LL i=link[x];i;i=e[i].next)
	{
		LL y=e[i].y;
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x])
			{
				flag++;
				if(x!=root||flag>1) cut[x]=1;
				cnt++;
				LL z;
				do
				{
					z=st.top();
					st.pop();
					Dcc[cnt].push_back(z);
				}while(z!=y);
				Dcc[cnt].push_back(x);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}
LL dep[N],fa[N],siz[N],son[N],top[N],id[N];
void dfs1(LL x,LL pre)
{
	dep[x]=dep[pre]+1;
	fa[x]=pre;
	siz[x]=1;
	for(LL i=link[x];i;i=e[i].next)
	{
		LL y=e[i].y;
		if(y==pre) continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])
		{
			son[x]=y;
		}
	}
}
LL idx;
void dfs2(LL x,LL topth)
{
	id[x]=++idx;
	top[x]=topth;
	if(!son[x]) return;
	dfs2(son[x],topth);
	for(LL i=link[x];i;i=e[i].next)
	{
		LL y=e[i].y;
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
LL Min[N<<2];
void pushup(LL k)
{
	Min[k]=min(Min[k<<1],Min[k<<1|1]);
}
void build(LL k,LL l,LL r)
{
	if(l==r) 
	{
		Min[k]=w[l];
		return;
	}
	LL mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
multiset<LL> S[N];
void construct()
{
	t=0;
	memset(link,0,sizeof(link));
	for(LL i=1;i<=cnt;i++)
	{
		LL x=++Size;
		for(LL j=0;j<Dcc[i].size();j++)
		{
			LL y=Dcc[i][j];
			add(x,y);
			add(y,x);
		}
	}
	dfs1(1,0);
	dfs2(1,1);
	for(LL i=1;i<=n;i++)
	w[id[i]]=a[i];
	for(LL x=n+1;x<=Size;x++)
	{
		for(LL i=link[x];i;i=e[i].next)
		{
			LL y=e[i].y;
			if(y==fa[x]) continue;
			S[x].insert(w[id[y]]);
		}
		if(S[x].empty()) w[id[x]]=INF;
		else w[id[x]]=*S[x].begin();
	}
	build(1,1,Size);
}
void update(LL k,LL l,LL r,LL x,LL v)
{
	if(l==r&&l==x)
	{
		Min[k]=v;
		return;
	}
	LL mid=(l+r)>>1;
	if(x<=mid) update(k<<1,l,mid,x,v);
	else update(k<<1|1,mid+1,r,x,v);
	pushup(k);
}
LL query(LL k,LL l,LL r,LL L,LL R)
{
	if(L<=l&&r<=R) return Min[k];
	LL mid=(l+r)>>1;
	LL res=INF;
	if(L<=mid) res=min(res,query(k<<1,l,mid,L,R));
	if(R>mid) res=min(res,query(k<<1|1,mid+1,r,L,R));
	return res;
}
void change(LL x,LL v)
{
	LL f=fa[x];
	if(f!=0)
	{
		S[f].erase(S[f].find(w[id[x]]));
		S[f].insert(v);
		w[id[f]]=*S[f].begin();
		update(1,1,Size,id[f],w[id[f]]);
	}
	w[id[x]]=v;
	update(1,1,Size,id[x],w[id[x]]);
}
LL query_chain(LL x,LL y)
{
	LL res=INF;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=min(res,query(1,1,Size,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) swap(x,y);

	res=min(res,query(1,1,Size,id[x],id[y]));
	if(x>n)
	res=min(res,w[id[fa[x]]]);
	return res;
}
int main()
{
	n=read();
	m=read();
	q=read();
	for(LL i=1;i<=n;i++)
	a[i]=read();
	for(LL i=1;i<=m;i++)
	{
		LL x,y;
		x=read();
		y=read();
		add(x,y);
		add(y,x);
	}
	root=1;
	Size=n;
	tarjan(1);
	construct();
	while(q--)
	{
		char opt[3];
		LL x,y;
		scanf("%s",opt);
		x=read();
		y=read();
		if(opt[0]=='C') change(x,y);
		else printf("%d\n",query_chain(x,y));
	}
	return 0;
}
```
这样就行了。


---

## 作者：Night_Bringer (赞：0)

# 前言
运用算法：点双连通分量，圆方树，树链剖分，splay（可以用 multiset 维护，不知道 OI 可不可以使用，所以就用了 splay ）。

[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14668908.html)。
# 题目大意
有 $n$ 个点， $m$ 条边，每个点 $i$ 都有点权 $w_i$ 。有两个操作：
1. C a w： 表示 a 点的权值变为 w。
2. A a b： 求从 a 点到 b 点的一条路径上，使得每个点只出现一次，且最小权值最小的一条路径的最小值。
# 思路
先说明圆方树，经常用于求解与无向图。下见如何构造圆方树（来自 WC 的 PPT 的一张图）：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210416212811134.png?,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0ZhY2VfdGhlX0JsYXN0,size_16,color_FFFFFF,t_70)

先用 Tarjan 算法求出点双连通分量，原有的点成为圆点。对于每个点双连通分量，建立一个方点，将点双连通分量内的所有圆点都连向这个方点。

显然，有一条重要性质成立：每条边的两个端点，一个是圆点，一个是方点。

对于一个普通的无向图，要进行维护其点权，可以先将其变为圆方树，在进行维护，是一些题的基本思路。树相对于图有更好的性质，可以用树链剖分等来维护。

题目中要维护最小值，那么方点的权值就为所连圆点的最小值。最小值使用 splay 维护，最后按照要求进行维护即可。

修改一个圆点，就会改动其旁边所有的方点。考虑菊花图，会被卡成 $O(nq)$ 。

稍微在上面做出改动，每个方点的权值为子节点的权值，暂时不考虑其父节点。树剖查询时，若两点的 LCA 为方点，最小值多比较一个父节点的权值即可。

时间复杂度 $O(q\log^2n+n\log n)$
# Code
```cpp
#include <stack>
#include <cstdio>
#include <cstring>
using namespace std;
namespace Quick_Function {
	template <typename Temp> void Read(Temp &x) {
		x = 0; char ch = getchar(); bool op = 0;
		while(ch < '0' || ch > '9') { if(ch == '-') op = 1; ch = getchar(); }
		while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
		if(op) x = -x;
	}
	template <typename T, typename... Args> void Read(T &t, Args &... args) { Read(t); Read(args...); }
	template <typename Temp> Temp Max(Temp x, Temp y) { return x > y ? x : y; }
	template <typename Temp> Temp Min(Temp x, Temp y) { return x < y ? x : y; }
	template <typename Temp> Temp Abs(Temp x) { return x < 0 ? (-x) : x; }
	template <typename Temp> void Swap(Temp &x, Temp &y) { x ^= y ^= x ^= y; }
}
using namespace Quick_Function;
#define INF 0x3f3f3f3f
const int MAXN = 1e6 + 5;
struct edge1 { int To, Next; };
edge1 edge1[MAXN << 1], edge2[MAXN << 1];
int head1[MAXN], head2[MAXN];
int edgetot1, edgetot2;
void Addedge1(int u, int v) {
	edge1[++edgetot1].Next = head1[u], edge1[edgetot1].To = v, head1[u] = edgetot1;
	edge1[++edgetot1].Next = head1[v], edge1[edgetot1].To = u, head1[v] = edgetot1;
}
void Addedge2(int u, int v) {
	edge2[++edgetot2].Next = head2[u], edge2[edgetot2].To = v, head2[u] = edgetot2;
	edge2[++edgetot2].Next = head2[v], edge2[edgetot2].To = u, head2[v] = edgetot2;
}
int w[MAXN], n, m, q;
stack<int> stk;
int dfn1[MAXN], low[MAXN];
int tim1, cnt;
void Tarjan(int u) {
	dfn1[u] = low[u] = ++tim1; stk.push(u);
	for(int i = head1[u]; i; i = edge1[i].Next) {
		int v = edge1[i].To;
		if(!dfn1[v]) {
			Tarjan(v);
			low[u] = Min(low[u], low[v]);
			if(low[v] >= dfn1[u]) {
				int Top = -1; cnt++;
				while(Top != v) {
					Top = stk.top(); stk.pop();
					Addedge2(Top, cnt);
				}
				Addedge2(u, cnt);
			}
		}
		else low[u] = Min(low[u], dfn1[v]);
	}
}
struct Segment_Node {
	int Left, Right, MinData;
	#define LS(x) (x << 1)
	#define RS(x) (x << 1 | 1)
	#define L(x) segment_tree[x].Left
	#define R(x) segment_tree[x].Right
	#define M(x) segment_tree[x].MinData
};
struct Segment_Tree {
	Segment_Node segment_tree[MAXN << 2];
	void Push_Up(int pos) { M(pos) = Min(M(LS(pos)), M(RS(pos))); }
	void Build(int pos, int l, int r) {
		L(pos) = l, R(pos) = r;
		if(l == r) return;
		int mid = (l + r) >> 1;
		Build(LS(pos), l, mid), Build(RS(pos), mid + 1, r);
	}
	void Update(int pos, int x, int k) {
		if(L(pos) == R(pos)) { M(pos) = k; return; }
		if(x <= R(LS(pos))) Update(LS(pos), x, k);
		else Update(RS(pos), x, k);
		Push_Up(pos);
	}
	int Query_Min(int pos, int l, int r) {
		if(l <= L(pos) && R(pos) <= r) return M(pos);
		int res = INF;
		if(l <= R(LS(pos))) res = Min(res, Query_Min(LS(pos), l, r));
		if(r >= L(RS(pos))) res = Min(res, Query_Min(RS(pos), l, r));
		return res;
	}
};
Segment_Tree tree1;
struct Splay_Node {
	int Child[2], Val, Cnt, Siz, Father, Belong;
	#define Son(x, y) splay[x].Child[y]
	#define V(x) splay[x].Val
	#define C(x) splay[x].Cnt
	#define S(x) splay[x].Siz
	#define F(x) splay[x].Father
	#define B(x) splay[x].Belong
};
struct Splay_Tree {
	int root[MAXN], tot;
	Splay_Node splay[MAXN * 3];
	bool Ident(int pos) { return Son(F(pos), 1) == pos; }
	int New(int val, int fa, int now) {
		F(++tot) = fa;
		C(tot) = S(tot) = 1;
		V(tot) = val;
		B(tot) = now;
		return tot;
	}
	void Build() {
		for(int i = 1; i <= cnt - n; i++) {
			root[i] = New(-INF, 0, i);
			Son(root[i], 1) = New(INF, root[i], i);
		}
	}
	void Update(int pos) { S(pos) = C(pos) + S(Son(pos, 0)) + S(Son(pos, 1)); }
	void Connect(int pos, int fa, int flag) {
		Son(fa, flag) = pos;
		F(pos) = fa;
	}
	void Rotate(int pos) {
		int fa = F(pos), grand = F(fa);
		int flag1 = Ident(pos), flag2 = Ident(fa);
		Connect(Son(pos, flag1 ^ 1), fa, flag1);
		Connect(fa, pos, flag1 ^ 1);
		Connect(pos, grand, flag2);
		Update(fa);
		Update(pos);
	}
	void Splay(int pos, int to) {
		for(int fa = F(pos); F(pos) != to; Rotate(pos), fa = F(pos))
			if(F(fa) != to) Ident(pos) == Ident(fa) ? Rotate(fa) : Rotate(pos);
		if(!to) root[B(pos)] = pos;
	}
	void Insert(int &pos, int val, int fa) {
		if(!pos) {
			pos = New(val, fa, B(fa));
			Splay(pos, 0);
			return;
		}
		if(val == V(pos)) {
			C(pos)++;
			Splay(pos, 0);
			return;
		}
		else if(val < V(pos)) Insert(Son(pos, 0), val, pos);
		else Insert(Son(pos, 1), val, pos);
	}
	void Remove(int pos, int val) {
		if(!pos) return;
		if(val == V(pos)) {
			if(C(pos) > 1) {
				C(pos)--;
				Splay(pos, 0);
				return;
			}
			if(Son(pos, 0)) Rotate(Son(pos, 0)), Remove(pos, val);
			else if(Son(pos, 1)) Rotate(Son(pos, 1)), Remove(pos, val);
			else {
				int newroot = F(pos);
				Son(F(pos), Ident(pos)) = 0;
				Splay(newroot, 0);
			}
			return;
		}
		else if(val < V(pos)) Remove(Son(pos, 0), val);
		else Remove(Son(pos, 1), val);
	}
	int Query_Min(int pos) {
		if(!pos) return INF;
		if(S(Son(pos, 0)) >= 2) return Query_Min(Son(pos, 0));
		Splay(pos, 0); return V(pos);
	}
};
Splay_Tree tree2;
int dfn2[MAXN], siz[MAXN], dep[MAXN], son[MAXN], fa[MAXN], tp[MAXN];
int tim2;
void dfs1(int u, int pre) {
	dep[u] = dep[pre] + 1, fa[u] = pre, siz[u] = 1;
	int maxn = -INF;
	for(int i = head2[u]; i; i = edge2[i].Next) {
		int v = edge2[i].To;
		if(v == pre) continue;
		dfs1(v, u); siz[u] += siz[v];
		if(siz[v] > maxn) son[u] = v, maxn = siz[v];
	}
}
void dfs2(int u, int Top) {
	dfn2[u] = ++tim2, tp[u] = Top;
	if(son[u]) dfs2(son[u], Top);
	for(int i = head2[u]; i; i = edge2[i].Next) {
		int v = edge2[i].To;
		if(v != son[u] && v != fa[u]) dfs2(v, v);
	}
}
int Min_Past(int x, int y) {
	int res = INF;
	while(tp[x] != tp[y]) {
		if(dep[tp[x]] < dep[tp[y]]) Swap(x, y);
		res = Min(res, tree1.Query_Min(1, dfn2[tp[x]], dfn2[x]));
		x = fa[tp[x]];
	}
	if(dep[x] > dep[y]) Swap(x, y);
	res = Min(res, tree1.Query_Min(1, dfn2[x], dfn2[y]));
	if(x > n) res = Min(res, w[fa[x]]);
	return res;
}
int main() {
	Read(n, m, q); cnt = n;
	for(int i = 1; i <= n; i++) Read(w[i]);
	for(int i = 1, u, v; i <= m; i++)
		Read(u, v), Addedge1(u, v);
	Tarjan(1);
	dfs1(1, 0); dfs2(1, 1);
	tree1.Build(1, 1, tim2);
	tree2.Build();
	for(int i = 2; i <= n; i++) tree2.Insert(tree2.root[fa[i] - n], w[i], 0);
	for(int i = 1; i <= n; i++) tree1.Update(1, dfn2[i], w[i]);
	for(int i = n + 1; i <= cnt; i++)
		tree1.Update(1, dfn2[i], tree2.S(tree2.root[i - n]) == 2 ? INF : tree2.Query_Min(tree2.root[i - n]));
	char opt[2];
	for(int i = 1, a, b; i <= q; i++) {
		scanf("%s", opt), Read(a, b);
		if(opt[0] == 'A') printf("%d\n", Min_Past(a, b));
		else {
			if(a != 1) {
				tree2.Remove(tree2.root[fa[a] - n], w[a]);
				tree2.Insert(tree2.root[fa[a] - n], b, 0);
				int tmp = tree2.Query_Min(tree2.root[fa[a] - n]);
				tree1.Update(1, dfn2[fa[a]], tmp);
			}
			tree1.Update(1, dfn2[a], b), w[a] = b;
		}
	}
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

题意：

> 有一张 $n$ 个点 $m$ 条边的无向图，点上有点权，$q$ 次操作，每次操作有以下两种类型：
>
> - "C $x\ y$"，将 $x$ 点的点权改为 $y$。
> - "A $x\ y$"，求所以 $x\to y$ 的简单路径上点权最小值的最小值。
>
> $1\leq n,m,q\leq 10^5$

首先把握住关键信息。本题的题眼显然在这个“简单路径”上。简单路径意味着不能经过同一个点。

很自然地可以想到点双连通分量。显然，根据点双连通分量的定义，在同一点双连通分量中，我们可以走到其中点权最小的点并走到相邻的点双连通分量中，并且不会经过重复的点。

考虑缩点。不过直接缩点有一个问题，之前我们遇到的连通分量都是“强连通分量”或“边双连通分量”，对于这一类连通分量都有一个特点，那就是每个点恰好属于一个强连通分量或边双连通分量。而有可能出现一个点属于多个点双连通分量的情况，故不能直接缩点。

那么怎么办呢？就要先从点双连通分量的性质开始说起了。

点双连通分量，指不含割点的极大连通子图。特别地，两个点之间有一条边的子图也是点双连通分量。

点双连通分量有以下性质：

1. 点双连通分量以割点连接
2. 每条边必须恰好属于一个点双连通分量。
3. 任意两个点双连通分量至多有一个公共点
4. 同一点双连通分量中任意两点 $u,v$ 之间简单路径的并集恰好等于整个点双。

性质 1,2,3 都比较显然，性质 4 粉兔神仙给出了严格证明，然鹅我看了半天~~一个字也~~没看懂，有兴趣自己去翻他的 blog。

那么什么是圆方树呢？如果我们将原图中的每一个点看作一个“圆点”，对每个点双连通分量新建一个“方点”。对于每一个点双连通分量，在其对应的方点与点双当中每个”圆点“之间连边，那么得到的就是圆方树。

比如下图：

![](https://img2018.cnblogs.com/blog/1126418/201907/1126418-20190711015718548-2063534813.png)

回到此题来。先 tarjan 求出点双连通分量。圆点上的点权为对应点的 $w_i$，方点上的点权为与其相连的圆点的点权的最小值。

那么答案即为 $x,y$ 之间点权值的最小值。

为什么？设 $P$ 为 $x\to y$ 的所有路径经过的点的集合的并集，那么答案显然为 $\min\limits_{u\in P}w_u$。

那么 $P$ 究竟是个什么东西呢？随便找一条 $x,y$ 之间的路径 $T$，假设其经过的边为 $e_1,e_2,\dots,e_k$。

根据点双连通分量的性质 2，这些边可以被划分到一个个点双连通分量中。假设这 $k$ 条边总共属于 $m$ 个点双连通分量，其中边 $e_{i_{j,1}},e_{i_{j,2}},\dots,e_{i_{j,c_j}}$ 属于点双连通分量 $j$。

根据点双连通分量的性质 4，这 $c_j$ 条边可以包含整个点双连通分量 $j$，也就是说，这个点双连通分量的所有点都应当属于 $P$。

也就是说这 $m$ 个点双连通分量点集的并 $\subseteq P$。

而不在这 $m$ 个点双连通分量中的点显然不可能被访问到，不然就违反了点双连通分量的定义了。

故我们得到了一个很重要的性质：这 $m$ 个点双连通分量点集的并 $=P$。

回到圆方树上来，$x,y$ 路径上的方点显然就对应这 $m$ 个点双连通分量，而每个方点上的权值是这个点双中所有点权值的 $\min$，故这 $m$ 个方点权值的 $\min$ 就是 $\min\limits_{u\in P}w_u$。

用个树剖维护一下就行了。

但这样还是会被叉掉——考虑一张菊花图，修改菊花图上度数为 $n-1$ 的点就要修改 $n-1$ 个方点的权值，复杂度最坏为 $n^2\log n$。

那么有什么办法呢？

我们可以在每个方点开一个 `multiset`，储存它所有儿子的权值。则方点的权值即为 `multiset` 中的最小值。这样，修改一个圆点时，就只需要改动它父亲的`multiset`即可。

然后在查询的时候，若两点之间的 LCA 是个方点，则将答案与 LCA 的父亲（必定是个圆点）的权值取 $\min$ 即可。

时间复杂度线性对数方。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MAXN=1e5;
int n,m,qu,w[MAXN*2+5],cnt;
namespace segtree{
	struct node{int l,r,val;} s[MAXN*8+5];
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;s[k].val=0x3f3f3f3f;if(l==r) return;
		int mid=(l+r)>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	}
	void modify(int k,int x,int v){
		if(s[k].l==s[k].r){s[k].val=v;return;}
		int mid=(s[k].l+s[k].r)>>1;
		if(x<=mid) modify(k<<1,x,v);
		else modify(k<<1|1,x,v);
		s[k].val=min(s[k<<1].val,s[k<<1|1].val);
	}
	int query(int k,int l,int r){
		if(l<=s[k].l&&s[k].r<=r) return s[k].val;
		int mid=(s[k].l+s[k].r)>>1;
		if(r<=mid) return query(k<<1,l,r);
		else if(l>mid) return query(k<<1|1,l,r);
		else return min(query(k<<1,l,mid),query(k<<1|1,mid+1,r));
	}
}
namespace tree{
	int hd[MAXN*4+5],nxt[MAXN*4+5],to[MAXN*4+5],ec=0;
	void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
	int siz[MAXN*2+5],fa[MAXN*2+5],wson[MAXN*2+5],dep[MAXN*2+5];
	int top[MAXN*2+5],dfn[MAXN*2+5],tim=0;
	void dfs1(int x,int f){
		fa[x]=f;siz[x]=1;
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e];if(y==f) continue;
			dep[y]=dep[x]+1;dfs1(y,x);siz[x]+=siz[y];
			if(siz[y]>siz[wson[x]]) wson[x]=y;
		}
	}
	void dfs2(int x,int tp){
		dfn[x]=++tim;top[x]=tp;
		if(wson[x]) dfs2(wson[x],tp);
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e];if(y==fa[x]||y==wson[x]) continue;
			dfs2(y,y);
		}
	}
	multiset<int> st[MAXN+5];
	void prework(){
		dfs1(1,0);dfs2(1,1);segtree::build(1,1,cnt);
		for(int i=2;i<=n;i++) w[fa[i]]=min(w[fa[i]],w[i]),st[fa[i]-n].insert(w[i]);
		for(int i=1;i<=n-cnt;i++) st[i].insert(0x3f3f3f3f);
//		for(int i=1;i<=cnt;i++) printf("%d %d %d %d %d %d\n",fa[i],siz[i],dep[i],wson[i],top[i],dfn[i]);
		for(int i=1;i<=cnt;i++) segtree::modify(1,dfn[i],w[i]);
	}
	void change(int x,int v){
		if(x!=1){
			st[fa[x]-n].erase(st[fa[x]-n].find(w[x]));st[fa[x]-n].insert(v);
			w[fa[x]]=*st[fa[x]-n].begin();segtree::modify(1,dfn[fa[x]],w[fa[x]]);
		} w[x]=v;segtree::modify(1,dfn[x],w[x]);
	}
	int query(int x,int y){
		if(dep[x]<dep[y]) swap(x,y);
		int ret=0x3f3f3f3f;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			chkmin(ret,segtree::query(1,dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		if(dep[x]<dep[y]) swap(x,y);
		chkmin(ret,segtree::query(1,dfn[y],dfn[x]));
//		printf("%d\n",y);
		if(y>n) chkmin(ret,w[fa[y]]);
		return ret;
	}
}
namespace graph{
	int hd[MAXN*2+5],nxt[MAXN*2+5],to[MAXN*2+5],ec=0;
	void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
	int dfn[MAXN+5],low[MAXN+5],stk[MAXN+5],top=0,tim=0;
	void tarjan(int x){
		dfn[x]=low[x]=++tim;stk[++top]=x;
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e];if(!dfn[y]){
				tarjan(y);low[x]=min(low[x],low[y]);
				if(low[y]>=dfn[x]){
					cnt++;w[cnt]=0x3f3f3f3f;int z;
					do {
						//printf("%d ",stk[top]);
						z=stk[top];tree::adde(cnt,z);tree::adde(z,cnt);top--;
					} while(z!=y);
					tree::adde(cnt,x);tree::adde(x,cnt);//printf("%d\n",x);
				}
			} else low[x]=min(low[x],dfn[y]);
		}
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&qu);cnt=n;
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);
		graph::adde(u,v);graph::adde(v,u);
	} graph::tarjan(1);tree::prework();
	while(qu--){
		char opt[3];int x,y;scanf("%s%d%d",opt+1,&x,&y);
		if(opt[1]=='C') tree::change(x,y);
		else printf("%d\n",tree::query(x,y));
	}
	return 0;
}
/*
9 9 1
2
4
8
7
7
6
7
8
10
2 1
1 7
3 2
4 3
5 4
5 6
6 7
4 8
2 9
A 4 3
*/
```



---

## 作者：Star_Cried (赞：0)

## CF487E Tourists

~~前排膜拜T神~~

~~上面的话和这道题一点关系都没有~~

### 题意

给一个点带权的无向图，每次询问查询两点间所有简单路径上最小值的最小值，单点修改。

### 思路

> 一眼圆方树。								——@gxy001

这种题只有在树上做才比较好处理这么多次询问。考虑广义圆方树，缩完点双连通分量后建立的方点和圆点。

因为我们找的是最小值，所以必须将代表整个点双的方点的权值设为与其相连的所有圆点的权值的最小值。用一个 multiset 或者一个可删堆（或者堆带懒惰删除）维护即可。

这样我们就可以在树上使用树剖进行查询了。

但是这题带修改。也就是说，按照上面的方法，更改一个圆点就必须遍历与其相连的所有方点进行修改。这样会被菊花图卡死。于是我们用一个经典套路：方点只维护其儿子的权值。这样我们查询时方法相同，只不过如果求出的 LCA 为方点的话需要再考虑一下其父亲节点的贡献。

由于我们需要区间查询加修改，我们可以将圆方树树剖并用线段树维护最小值。

### 代码

如果您追求更快速的代码体验，建议使用手写堆+惰性删除。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cmath>
#include<set>
using namespace std;
inline int read(){
	int w=0,x=0;char c=getchar();
	while(!isdigit(c))w|=c=='-',c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return w?-x:x;
}
namespace star
{
	const int maxn=2e5+10,INF=0x3f3f3f3f;
	int n,m,Q,a[maxn],cnt;
	struct gragh{
		int ecnt,head[maxn],to[maxn<<1],nxt[maxn<<1];
		inline void addedge(int a,int b){
			to[++ecnt]=b,nxt[ecnt]=head[a],head[a]=ecnt;
			to[++ecnt]=a,nxt[ecnt]=head[b],head[b]=ecnt;
		}
	}G1,G2;
	int st[maxn],dfn[maxn],tot,id[maxn];
	struct SegmentTree{
		#define ls (ro<<1)
		#define rs (ro<<1|1)
		#define mid ((l+r)>>1)
		int mn[maxn<<2];
		inline void pushup(const int &ro){
			mn[ro]=min(mn[ls],mn[rs]);
		}
		void build(const int& ro=1,const int &l=1,const int &r=cnt){
			if(l==r) return mn[ro]=a[id[l]],void();
			build(ls,l,mid);build(rs,mid+1,r);
			pushup(ro);
		}
		void update(const int &x,const int &ro=1,const int &l=1,const int &r=cnt){
			if(l==r) return mn[ro]=a[id[l]],void();
			if(x<=mid) update(x,ls,l,mid);
			else update(x,rs,mid+1,r);
			pushup(ro);
		}
		int query(const int &x,const int &y,const int &ro=1,const int &l=1,const int &r=cnt){
			if(x==l and y==r) return mn[ro];
			if(y<=mid) return query(x,y,ls,l,mid);
			else if(x>mid) return query(x,y,rs,mid+1,r);
			else return min(query(x,mid,ls,l,mid),query(mid+1,y,rs,mid+1,r));
		}
		#undef ls
		#undef rs
		#undef mid
	}T;
	void tarjan(int x){
		dfn[x]=id[x]=++tot;
		st[++st[0]]=x;
		for(int i=G1.head[x];i;i=G1.nxt[i]){
			int u=G1.to[i];
			if(!dfn[u]){
				tarjan(u);
				id[x]=min(id[x],id[u]);
				if(id[u]>=dfn[x]){
					cnt++;
					int now=-1;
					G2.addedge(x,cnt);
					while(now^u) now=st[st[0]--],G2.addedge(now,cnt);
				}
			}else id[x]=min(id[x],dfn[u]);
		}
	}
	int dep[maxn],siz[maxn],fa[maxn],son[maxn],top[maxn];
	multiset<int> q[maxn];
	void dfs1(int x,int f){
		fa[x]=f,dep[x]=dep[f]+1,siz[x]=1;
		for(int i=G2.head[x];i;i=G2.nxt[i]){
			int u=G2.to[i];
			if(u==f)continue;
			dfs1(u,x);
			if(x>n) q[x-n].insert(a[u]);
			siz[x]+=siz[u];
			if(siz[u]>siz[son[x]])son[x]=u;
		}
		if(x>n) a[x]=*q[x-n].begin();
	}
	void dfs2(int x,int topf){
		top[x]=topf,dfn[x]=++tot,id[tot]=x;
		if(!son[x])return;
		dfs2(son[x],topf);
		for(int i=G2.head[x];i;i=G2.nxt[i]){
			int u=G2.to[i];
			if(u==fa[x] or u==son[x])continue;
			dfs2(u,u);
		}
	}
	inline int LCA(int x,int y){
		int ans=INF;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			ans=min(ans,T.query(dfn[top[x]],dfn[x]));
			x=fa[top[x]];
		}
		if(dep[x]<dep[y])swap(x,y);
		ans=min(ans,T.query(dfn[y],dfn[x]));
		if(y>n) ans=min(ans,a[fa[y]]);
		return ans;
	}
	inline bool gc(){
		char c=getchar();
		while(!isalpha(c))c=getchar();
		return c=='C';
	}
	inline void work(){
		n=cnt=read(),m=read(),Q=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=m;i++) G1.addedge(read(),read());
		tarjan(1);
		tot=0;
		dfs1(1,0);
		dfs2(1,1);
		T.build();
		while(Q--)
			if(gc()){
				int x=read(),w=read(),u=fa[x];
				if(u)
					q[u-n].erase(q[u-n].find(a[x])),
					q[u-n].insert(w),
					a[u]=*q[u-n].begin(),
					T.update(dfn[u]);
				a[x]=w;
				T.update(dfn[x]);
			}else printf("%d\n",LCA(read(),read()));
	}
}
signed main(){
	star::work();
	return 0;
}
```



---

## 作者：uniqueboy (赞：0)

    题目背景：
    尊者神高达很穷，所以他需要跑商来赚钱
    题目描述：
    基三的地图可以看做 n 个城市，m 条边的无向图，尊者神高达会从任意一个点出发并在起点购买货物，在旅途中任意一点卖出并最终到达终点，尊者神高达的时间很宝贵，所以他不会重复经过同一个城市，但是为了挣钱，他可能会去绕路。当然，由于工作室泛滥，所以一个城市的货物价格可能会发生改变。但是尊者神高达智商不足，他可能在一个很蠢的节点把货物卖掉，所以尊者神高达想知道每一次跑商最多能赔多少钱。
    
   	第一行 n,m;
    接下来 1 行 n 个数，代表每个城市货物的价格；
    接下来 m 行 u，v 代表一条边
    接下来 1 行 Q
    接下来 Q 行
    C x w 代表城市 x 的货物价格变为 w
    Q u v 代表一次从 u 到 v 
    
    Sample Input
    3 3 
    1 2 3
    1 2
    2 3
    1 3
    3
    Q 2 3
    C 1 5
    Q 1 3
    Sample Output

    1
    3

    样例解释：
    1，2，3 都联通，起点购买价格为 2，在 1 点卖出赔得最多2-1=1
    更新后每个点价值为 5，2，3
    起点价格为 5，在 2 点卖出赔得最多，5-2=3
    
    40%的数据为一棵树
    另外 20%的数据没有修改操作
    所以数据满足 n,m,q<=100000;保证图联通，数据合法
solution:
     !!! 圆方树!!!
      ？？？圆方树是什么？？？
      自己的理解：把每一个环拆了，新建一个方点，权值为圆点中的最小值，（原来的点叫圆点）然后方点向这个环原来所有点连边，保留圆点，删原来的边，这样整张图就变为了，一个圆点一个方点间隔的，两个圆点之间也要建方点，因为他也是一个点双。建了之后就显然是一棵树了（en,显然...）。
      
      那么这个有什么用呢？
      突然发现，这时所有方点就是点双中权值最小的点，就是我们要求得答案，查询的话就变为了 求树上两点间点权最小值，树剖剖一下就好了，
      但是修改的话就很恼火了，每次修改时，都要遍历所有他的相邻方点，如果是一棵菊花树的话，就GG了，O（n）!;
      
      再考虑优化：
      现在已经是一树了，随便找个点作为根，我们把方点的值记录为他的所有儿子圆点中的最小值，另一个圆点作为他的父亲，对于每个方点开个multiset维护最小值，那么每次修改的时候，直接在他的父亲方点中删去原来的值，加上现在的值，（因为每个点父亲唯一，所以一个圆点改变只会对他的父亲方点有影响）.最后特判一下两个点的LCA是不是方点，如果是方点，那么再把答案和LCA的父亲取个min就 OK 啦。  求路径最小值，日常树剖。。。
      ```cpp
    
   ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;
const int N=200005;
#define il inline
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){ret=(ret<<3)+(ret<<1)+ch-'0';ch=getchar();}
	return ret*f;
}
multiset<int> SM[N];
int n,tim,m,head[N],tail[N],k,a[N];
struct node{
	int to,nxt;
}edge[N*2];
struct data{
	int l,r,min_val;
}tree[N*4];
il void add(int u,int v){
	edge[++k].to =v; edge[k].nxt =head[u]; head[u]=k;
}
il void add2(int u,int v){
	//printf("##%d %d\n",u,v);
	edge[++k].to =v; edge[k].nxt =tail[u]; tail[u]=k;
}
int size[N],son[N],deep[N],fa[N];
int Min(int x,int y){if(x<y) return x;return y;}
il void dfs1(int u,int father)
{
	size[u]=1;
	for(int i=tail[u];i;i=edge[i].nxt )
	{
		int v=edge[i].to ;
		if(v!=father){
			deep[v]=deep[u]+1;   	fa[v]=u;
			dfs1(v,u);     size[u]+=size[v];
			if(son[u]==0 || size[v]>size[son[u]]) son[u]=v;
		}
	}
}
int top[N],pos[N],cnt,N_pos[N];
il void dfs2(int u,int tp)
{
	top[u]=tp; pos[u]=++cnt; N_pos[cnt]=u;
	if(son[u]==0) return ;
	dfs2(son[u],tp);
	for(int i=tail[u];i;i=edge[i].nxt )
	{
		int v=edge[i].to ;
		if(v!=fa[u] && v!=son[u]) dfs2(v,v);
	}
}
il void build(int id,int l,int r)
{
	tree[id].l =l; tree[id].r =r;  
	if(l==r){
		tree[id].min_val =a[N_pos[l]];
		return ;
	}
	int mid=(l+r)>>1;
	build(id<<1,l,mid); build(id<<1|1,mid+1,r);
	tree[id].min_val =Min(tree[id<<1].min_val,tree[id<<1|1].min_val) ;
}
il int query(int id,int l,int r)
{
	if(tree[id].l >r||tree[id].r <l) return 0x3f3f3f3f;
	if(tree[id].l >=l&&tree[id].r <=r) return tree[id].min_val ;
	return Min(query(id<<1,l,r),query(id<<1|1,l,r));
}
il int Query(int x,int y)
{
	if(x==1&&y==3){
		int tt=1;
	}
	int ans=0x3f3f3f3f;
	while(top[x]!=top[y])
	{
		if(deep[top[x]]<deep[top[y]]) swap(x,y);
		ans=min(ans,query(1,pos[top[x]],pos[x]));
		x=fa[top[x]];
	}
	if(deep[x]<deep[y])swap(x,y);
	ans=min(ans,query(1,pos[y],pos[x]));
	if(y>tim) ans=min(ans,a[fa[y]]);
	return ans;
}
il void update(int id,int x,int val)
{
	if(tree[id].l ==x&&tree[id].r ==x) {
		tree[id].min_val =val; return;
	}
	int mid=(tree[id].l +tree[id].r )>>1;
	if(x<=mid) update(id<<1,x,val);
	if(x>mid) update(id<<1|1,x,val);
	tree[id].min_val =Min(tree[id<<1].min_val,tree[id<<1|1].min_val) ;
}

int dfn[N],low[N],ttttt,S[N],topp;
void tarjan(int u)
{
	dfn[u]=low[u]=++ttttt;  S[++topp]=u;
	for(int i=head[u];i;i=edge[i].nxt )
	{
		int v=edge[i].to;
		if(!dfn[v])  {
			tarjan(v); 	low[u]=Min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				++tim; int tmp; a[tim]=0x3f3f3f3f;
				add2(u,tim);add2(tim,u);
				do{
					tmp=S[topp--];
					add2(tmp,tim);add2(tim,tmp);
				}while(tmp!=v);
			}
		}
		else low[u]=min(low[u],dfn[v]);
	 } 
}
int main()
{
	freopen("paoshang.in","r",stdin);
	freopen("paoshang.out","w",stdout);
	n=read(); m=read();
//	printf("%d %d ",n,m);
	for(int i=1;i<=n;i++) a[i]=read();
	int x,y;
	for(int i=1;i<=m;i++) {
		x=read(); y=read(); add(x,y); add(y,x);
	}
	tim=n;
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	swap(n,tim);
	dfs1(1,0); dfs2(1,1);
//	for(int i=1;i<=4;i++) printf("%d ",pos[i]);
	for(int j=tim+1;j<=n;j++)
	{
		for(int i=tail[j];i;i=edge[i].nxt )
		{
			int v=edge[i].to ;
			if(v!=fa[j]) SM[j].insert(a[v]); 
		}
		if(SM[j].empty() ) a[j]=0x3f3f3f3f;
		else a[j]= *SM[j].begin(); 
	}
	build(1,1,n);                                                                             
	int qq=read();char op[10];
	for(int i=1;i<=qq;i++)
	{
		scanf("%s",op); x=read();y=read();
		if(op[0]=='C')
		{
			if(fa[x]){
				SM[fa[x]].erase(SM[fa[x]].find(a[x]));
				SM[fa[x]].insert(y);
				a[fa[x]]= *SM[fa[x]].begin() ;  
				update(1,pos[fa[x]],a[fa[x]]);
			}
			a[x]=y;  update(1,pos[x],y);
		}
		else  printf("%d\n",a[x]-Query(x,y));
	}
}
```
 

---

