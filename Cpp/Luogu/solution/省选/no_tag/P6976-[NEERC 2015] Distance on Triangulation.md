# [NEERC 2015] Distance on Triangulation

## 题目描述

你有一个凸多边形。多边形的顶点按顺序从 $1$ 到 $n$ 编号。你还有这个多边形的一个三角剖分，给出为 $n-3$ 条对角线的列表。

你还会得到 $q$ 个查询。每个查询由两个顶点索引组成。对于每个查询，找到这两个顶点之间的最短距离，前提是你可以通过多边形的边和给定的对角线移动，距离以你经过的边和对角线的总数来衡量。

## 说明/提示

时间限制：2 秒，内存限制：256 MB。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6
1 5
2 4
5 2
5
1 3
2 5
3 4
6 3
6 6
```

### 输出

```
2
1
1
3
0
```

# 题解

## 作者：b6e0_ (赞：12)

### $\mathcal O(n)\sim\mathcal O(1)$ 另解。

考虑将每个三角形建（图论中的）一个点，两个三角形有公共边则它们的点之间连一条边，这样形成了一棵树，且每个点的度数最大为 $3$。

考虑对这棵树做拓扑排序的过程，则在几何图形上，相当于每次删掉一个度数为 $2$ 的顶点，最后剩下一个三角形。不妨让一个三角形，以及它在树上对应的点，代表拓扑排序过程中和它一起被删除的几何图形上的那个顶点。这样，除了最后剩下的 $3$ 个顶点，每个顶点都与对应树上的一个点。

边界情况：最后剩下的三个点在查询时比较难处理，不妨给原图添加上 $(1,2,n+1),(1,n+1,n+2),(n+1,n+2,n+3)$ 三个三角形得到一个 $n+3$ 个顶点的多边形，这样剩下的三个点就是 $n+1,n+2,n+3$，不影响查询。这样，初始的 $n$ 个顶点形成了一棵树，且若树以 $1$ 为根，每个点都最多有两个儿子。

这样，我们对于 $n$ 个顶点建出了一棵树。考虑树上的哪些点在原几何图形中是有边相连的。

首先，树边一定在原图中存在。然后，原图中存在的其他边，对应到树上一定是返祖边，且树上除了点 $1,2$，每个点都有恰好一条返祖边。但仅仅靠这些显然不足以快速求出最短路，考虑挖掘性质。

观察到，若有 $x\rightarrow y$ 的一条返祖边，设 $x$ 到 $y$ 的路径上的点是 $x,a_1,a_2,\cdots,a_{m-1},a_m,y$，其中 $fa(a_i)=a_{i+1},fa(x)=a_1,fa(a_m)=y$，则 $a_1,a_2,\cdots,a_{m-1}$ 的返祖边都连向 $y$。

以上三点，考虑拓扑排序的过程都容易证明，画画图，模拟几个例子就行了。

下面考虑怎么求 $x$ 到 $y$ 的最短路。根据性质，$x$ 往它的子树走是一定不优的（除了 $x$ 是 $y$ 的祖先的情况，此时我们不妨交换 $x,y$），所以路径一定是不断走返祖边，到达 LCA 附近，然后分讨一些情况，再不断向下走返祖边到达 $y$。

具体来说，有以下几种情况：

- 若通过返祖边能直接到达 LCA，则路径形如 $x\rightarrow\text{LCA}\rightarrow y$；
- 若通过返祖边能到达 LCA 的某个儿子 $s$，则路径形如 $x\rightarrow s\rightarrow\text{LCA}\rightarrow y$；
- 若通过返祖边能到达 LCA 的父亲，则路径形如 $x\rightarrow fa(\text{LCA})\rightarrow y$；
- 若通过返祖边能到达 LCA 出发的返祖边的终点 $t$，则路径形如 $x\rightarrow t\rightarrow y$；

$\text{LCA},fa(\text{LCA}),t$ 到 $y$ 的部分同理，对几种情况取 $\min$ 即可。

为了判断 $x$ 能否通过返祖边走到某个点，以及求出要走多少次，我们对于返祖边再建出一棵树，上面只需要判断一个点是否在一棵子树内，以及求出每个点的深度。

瓶颈在求 LCA，可以用四毛子做到 $\mathcal O(n)\sim\mathcal O(1)$。

$\mathcal O(n\log n)$ 实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int MN=52000;
int n,Q,d[MN],nx[MN],ny[MN],pos[MN],q[MN],fr=1,ba,lc[MN],rc[MN],fa[16][MN],dep[MN],dfn[MN],ed[MN],cnt,dis[MN];
vector<int>g[MN];
inline void adde(int x,int y)
{
	g[x].push_back(y);
	g[y].push_back(x);
	d[x]++,d[y]++;
}
void dfs(int x)
{
	for(int j=1;j<16;j++)
		fa[j][x]=fa[j-1][fa[j-1][x]];
	dep[lc[x]]=dep[rc[x]]=dep[x]+1;
	if(lc[x])
		dfs(lc[x]);
	if(rc[x])
		dfs(rc[x]);
}
inline int LCA(int x,int y)
{
	if(dep[x]<dep[y])
		swap(x,y);
	int d=dep[x]-dep[y];
	for(int i=0;i<16;i++)
		if((d>>i)&1)
			x=fa[i][x];
	if(x==y)
		return x;
	for(int i=15;~i;i--)
		if(fa[i][x]!=fa[i][y])
			x=fa[i][x],y=fa[i][y];
	return ny[x];
}
void dfs2(int x)
{
	dfn[x]=++cnt;
	for(int y:g[x])
	{
		dis[y]=dis[x]+1;
		dfs2(y);
	}
	ed[x]=cnt;
}
inline bool in(int x,int y)
{
	return dfn[x]<=dfn[y]&&dfn[y]<=ed[x];
}
inline int ask(int x,int y)
{
	if(in(x,y))
		return dis[y]-dis[x];
	if(in(lc[x],y))
		return dis[y]-dis[lc[x]]+1;
	if(in(rc[x],y))
		return dis[y]-dis[rc[x]]+1;
	if(in(ny[x],y))
		return dis[y]-dis[ny[x]]+1;
	return dis[y]-dis[nx[x]]+1;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		adde(i,i%n+1);
	adde(1,n+1),adde(2,n+1);
	adde(1,n+2),adde(n+1,n+2);
	adde(n+2,n+3),adde(n+2,n+3);
	for(int i=0;i<n-3;i++)
	{
		int x=read(),y=read();
		adde(x,y);
	}
	for(int i=1;i<=n;i++)
		if(d[i]==2)
			q[++ba]=i;
	for(int i=1;i<=n;i++)
	{
		int x=q[fr++];
		pos[x]=i;
		for(int y:g[x])
		{
			if(pos[y])
				continue;
			if(nx[x])
				ny[x]=y;
			else
				nx[x]=y;
			if((--d[y])==2)
				q[++ba]=y;
		}
	}
	for(int i=1;i<=n+3;i++)
		g[i].clear();
	pos[n+1]=pos[n+2]=pos[n+3]=MN;
	ny[1]=0;
	for(int i=2;i<=n;i++)
	{
		if(pos[nx[i]]<pos[ny[i]])
			swap(nx[i],ny[i]);
		if(lc[ny[i]])
			rc[ny[i]]=i;
		else
			lc[ny[i]]=i;
		fa[0][i]=ny[i];
	}
	nx[2]=2,nx[1]=1;
	for(int i=3;i<=n;i++)
		g[nx[i]].push_back(i);
	dfs(1);
	dfs2(1),dfs2(2);
	Q=read();
	while(Q--)
	{
		int x=read(),y=read(),l=LCA(x,y),res=MN;
		if(in(l,x))
			res=dis[x]-dis[l]+ask(l,y);
		if(in(ny[l],x))
			res=min(res,dis[x]-dis[ny[l]]+ask(ny[l],y));
		if(in(lc[l],x))
			res=min(res,dis[x]-dis[lc[l]]+1+ask(l,y));
		if(in(rc[l],x))
			res=min(res,dis[x]-dis[rc[l]]+1+ask(l,y));
		if(in(nx[l],x))
			res=min(res,dis[x]-dis[nx[l]]+ask(nx[l],y));
		write(res);
	}
	return 0;
}
```

---

## 作者：Soulist (赞：9)

写了太久了就~~水~~篇题解纪念一下这个题吧。

考虑分治。

将所有查询离线，枚举一条重心边使得其尽可能的将图切割成两个均匀的部分。

然后预处理两个端点到这张图的最短路，对两个部分当作子问题递归（带着查询）。

如果某查询的两个端点在图的两端就不递归。

tips：这份代码处理不了递归到 $n\le 3$ 的情况，不过这个情况特判一下就 ok 了。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( int i = (t); i >= (s); -- i )
#define mp make_pair
#define pi pair<int, int>
#define pb push_back
#define vi vector<int>
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 1e5 + 5 ; 
int n, t, f[N], g[N] ; 
vector<vector<int>> E ; 
struct node {
	int x, y, ans ; 
} qus[N] ;
queue<int> q ; 
void solve(vector<int> d, vector<int> Id, vector<vector<int>> G) {
	int ua = 0, ub = 0, uz = 0, hf = Id.size() / 2, m = Id.size() ;
	vector<int> dis1, dis2 ; dis1.resize(m), dis2.resize(m) ; -- m ;
	if( m <= 1 ) return ; 
	rep( i, 1, m ) dis1[i] = dis2[i] = -1 ;  
	int cnt = 0, num = 0 ; 
	for(int v : Id) if( v ) f[v] = ++ cnt ;
	for(int i = 1; i < (int)G.size(); ++ i) {
		for( auto v : G[i] ) 
		if( (abs(i - v) > uz) && (abs(i - v) <= hf) ) uz = abs(i - v), ua = i, ub = v ; 
	} if( ua > ub ) swap( ua, ub ) ; 
	for(int i = ua; i <= ub; ++ i) g[i] = 1 ; 
	q.push(ua) ; dis1[ua] = 0 ; 
	while( !q.empty() ) {
		int u = q.front() ; q.pop() ; 
		for(int v : G[u]) if( !(~dis1[v]) ) 
			dis1[v] = dis1[u] + 1, q.push(v) ;  
	}
	q.push(ub) ; dis2[ub] = 0 ; 
	while( !q.empty() ) {
		int u = q.front() ; q.pop() ; 
		for(int v : G[u]) if( !(~dis2[v]) ) 
			dis2[v] = dis2[u] + 1, q.push(v) ;  
	}
	num = ub - ua + 1 ; 
	vector<vector<int>> lG, rG ; 
	vector<int> lq, rq, lId, rId ; 
	lG.resize(num + 1), lId.resize(num + 1) ; //注意有序 
	for(int id : d) {
		if( !id ) continue ; 
		int x = f[qus[id].x], y = f[qus[id].y] ; 
		int z = min(min(dis1[x] + dis2[y], dis1[y] + dis2[x]) + 1, min(dis1[x] + dis1[y], dis2[x] + dis2[y])) ;
		qus[id].ans = min( qus[id].ans, z ) ;  
		if( g[x] ^ g[y] ) continue ; //1 -> l, 0 -> r
		(g[x]) ? lq.pb(id) : rq.pb(id) ; 
	}
	rep( i, 1, m ) g[i] = 0 ;  
	if( m <= 3 ) return ; 
	num = 0 ; 
	for(int i = ua; i <= ub; ++ i) g[i] = ++ num, lId[num] = Id[i] ; 
	for(int i = ua; i <= ub; ++ i) 
		for(int v : G[i]) if( g[v] ) lG[g[i]].pb(g[v]) ; 
	rep( i, ua, ub ) g[i] = 0 ; num = 0 ; 
	for(int i = 1; i <= ua; ++ i) g[i] = ++ num ; 
	for(int i = ub; i <= m; ++ i) g[i] = ++ num ; 
	rId.resize(num + 1), rG.resize(num + 1) ; 
	rep( i, 1, m ) if(g[i]) rId[g[i]] = Id[i] ; 
	for(int i = 1; i <= m; ++ i) {
		if(!g[i]) continue ; 
		for(int v : G[i]) if( g[v] ) rG[g[i]].pb(g[v]) ; 
	}
	rep( i, 1, m ) g[i] = 0 ;  
	solve(lq, lId, lG), solve(rq, rId, rG) ; 
}
signed main()
{
	n = gi() ; int x, y ; E.resize(n + 1) ; 
	rep( i, 4, n ) x = gi(), y = gi(), E[x].pb(y), E[y].pb(x) ; 
	rep( i, 2, n ) E[i].pb(i - 1), E[i - 1].pb(i) ;
	E[n].pb(1), E[1].pb(n) ; 
	t = gi() ; vi d, Id ; d.resize(t + 1) ; 
	rep( i, 1, t ) qus[i].x = gi(), qus[i].y = gi(), d[i] = i ;
	rep( i, 1, t ) qus[i].ans = abs(qus[i].x - qus[i].y) ; 
	Id.resize(n + 1) ; 
	rep( i, 1, n ) Id[i] = i ; 
	solve(d, Id, E) ;
	rep( i, 1, t ) printf("%d\n", qus[i].ans ) ; 
	return 0 ;
}
```

---

## 作者：oisdoaiu (赞：8)

*tag:点分治，对偶图*

# 思路

考虑分治解决问题，每次选一个三角形，处理经过这个三角形的询问，再递归下去。那么我们要做的就是使剩下部分尽量平均。

将原图的对偶图画出来，通俗来讲，就是把一个三角形当成一个点，再把有公共边的三角形连起来，会发现是一棵树(不考虑最外面的那个面)，于是发现这个过程就是点分治的过程。每次处理跨分治中心的询问，并递归解决其它询问

复杂度$O((n+q)logn)$

# 建图

最关键的一步就是把对偶图弄出来。考虑用拓扑，每次将度数为 $2$ 的点拿出来，那么这个点和它相连的两个点就构成了一个三角形，然后删掉这个点和这 $2$ 条边。一直处理下去就可以找出所有三角形。

```cpp
for(register int i=1; i<=n; i++) if(d[i]==2) q[++r] = i;
while(l<=n-2){   //一共只有n-2个三角形
    int x = q[l++]; vis[x] = true;
    int a=-1, b=-1;
    for(register int i=0, tp=to[x].size(); i<tp; i++) 
    	if(!vis[to[x][i]]) 
        	if(a==-1) a = to[x][i]; 
        	else b = to[x][i];
    t[++cnt] = (tri){x,a,b};
    d[a]--; d[b]--;
    if(d[a]==2) q[++r] = a; 
    if(d[b]==2) q[++r] = b;
}
    
```

建树的话，考虑每次处理到 $x$ 的时候，当前三角形为 $(x,a,b)$，那么当前三角形与父亲三角形相连的那条边一定是 $(a,b)$，就把这个三角形记在边 $(a,b)$ 上(我比较懒直接用 $map$)。然后处理到 $(x,a,b)$ 时看一看每条边是否接了一个三角形。

```cpp
if(mp[make(x,a)]) T.Add_Edge(cnt,mp[make(x,a)]);
if(mp[make(x,b)]) T.Add_Edge(cnt,mp[make(x,b)]);
if(mp[make(a,b)]) T.Add_Edge(cnt,mp[make(a,b)]);
else mp[make(a,b)] = cnt;
```

# 分治

分治过程和点分治大同小异，这里主要讲一个直接求出最短路的方法。(当然你也可以直接bfs三遍，不过常数有点大)

先手动赋值根结点对应的三个点的$dis$数组。

假设 $dfs$ 到了 $x$，那么 $x$ 对应的三角形 $(A,B,C)$ 一定有两个顶点是之前处理过的，所以只需要找出没有处理的那个顶点( 设为 $C$ )，然后设 $dis_C=min\{dis_A,dis_B\}+1$ 即可。
```cpp
/*
bel[x]表示x属于哪个子树
::bel[x] 的意思就是 bel[x]，只不过这里和函数内部的bel重名了，所以要用::去调用
*/
if(!::bel[t[x].a]) np = t[x].a;
if(!::bel[t[x].b]) np = t[x].b;
if(!::bel[t[x].c]) np = t[x].c;
::bel[np] = bel; p[++top] = np;
for(register int i=0; i<3; i++) 
    dis[np][i] = inf,
    dis[np][i] = min(min(dis[t[x].a][i],dis[t[x].b][i]),dis[t[x].c][i])+1;
```

# 杂项
这道题写对拍造数据可能不太好造，提供一个思路：用双向链表把 $1$ ~ $n$ 串起来，每次随机一个还在的点 $x$，把 $x$ 左右两个点 $l$ 和 $r$ 连起来(即输出 $l\ r$)，然后删掉 $x$。

[完整代码](https://www.luogu.com.cn/paste/fpz7vtel)

---

## 作者：Astatinear (赞：2)

### [[NEERC 2015] Distance on Triangulation](https://www.luogu.com.cn/problem/P6976)

解释一下，这题哪里淀粉质了/fn。

首先先考虑一个暴力，即从每个点出发进行 $\text{BFS}$，复杂度应该是 $\mathcal{O}(n^2)$。

注意到这 $n-3$ 条边将原图分的死死的，互不交叉，故考虑能不能找到靠近中间的一条边拆成两半。

发现可以分治，即每次找到最中间的一条边，然后分成左右两半，跨过这条边的询问就可以通过 $\text{BFS}$ 得到答案。

时间复杂度 $\mathcal{O}(n\log n+q\log n)$。

---

## 作者：Planetary_system (赞：1)

## 题面解释：
给定一个环，中间连接 $n-3$ 条边，求给定两点间最短距离。

## 思路分析：
不难想到暴力做法 $n$ 遍 $\text{bfs}$，求多元最短路（~~这一定可以过~~）。

观察数据范围直接分治，找一条对角线，把两边的点数尽量分的均匀，然后在这个图中用 $\text{bfs}$ 求出这条对角线两个端点到其它所有点的距离。

每次是 $\mathcal{O}(n)$ 的（注意对角线是不会交叉的，所以在左右两个部分的点想要到达对方，就必定会经过中间的分割边的端点，如果走到分治的区域之外，它一定会浪费步数。）

由于 $n$ 的规模在分治中不断减小，分治层数是的 $\log{n}$，所以总时间复杂度是的 $\mathcal{O}(n\log{n})$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5.5e4+10;
int ans[2*N];
struct enode {
	int u,v;
	enode() {}
	enode(int x,int y) {u=x,v=y;}
};
struct qnode {
	int u,v,id;
	qnode() {}
	qnode(int x,int y,int z) {u=x,v=y,id=z;}
};
vector<int>G[N];
int dis[N],siz[N];
bool L[N],R[N];
void bfs(int s) {
	queue<int >q;
	int u,v,i;
	q.push(s),dis[s]=0;
	while(!q.empty()) {
		u=q.front(),q.pop();
		for(i=0; i<int (G[u].size()); i++) {
			v=G[u][i];
			if(dis[v]==-1)
				dis[v]=dis[u]+1,
				q.push(v);
		}
	}
}
inline int ab(int x) {return x<0?-x:x;}
void solve(vector<int >&a,vector<enode>&e,vector<qnode>&q) {
	int n=a.size(),m=e.size(),Q=q.size(),i,mi=0x3f3f3f3f,u,v,x,y,tmp;
	if(!Q)return;
	if(n==3) {
		for(i=0; i<Q; i++)
			ans[q[i].id]=(q[i].u!=q[i].v);
		return;
	}
	siz[a[0]]=1;
	for(i=1; i<n; i++)siz[a[i]]=siz[a[i-1]]+1;
	for(i=0; i<m; i++) {
		x=e[i].u,y=e[i].v;
		if((tmp=max(n-ab(siz[x]-siz[y]),ab(siz[x]-siz[y])))<mi)
			mi=tmp,u=x,v=y;
	}
	if(u>v)swap(u,v);
	vector<int>a0,a1;
	vector<enode>e0,e1;
	vector<qnode>q0,q1;
	a0.clear(),a1.clear();
	e0.clear(),e1.clear();
	q0.clear(),q1.clear();
	for(i=0; i<n; i++)
		L[a[i]]=R[a[i]]=0,
		G[a[i]].clear();
	for(i=0; i<n; i++) {
		if(u<=a[i]&&a[i]<=v)L[a[i]]=1,a0.push_back(a[i]);
		if(a[i]<=u||a[i]>=v)R[a[i]]=1,a1.push_back(a[i]);
	}
	for(i=0; i<m; i++) {
		x=e[i].u,y=e[i].v;
		G[x].push_back(y),G[y].push_back(x);
		if(L[x]&&L[y])e0.push_back(e[i]);
		if(R[x]&&R[y])e1.push_back(e[i]);
	}
	for(i=0; i<Q; i++) {
		x=q[i].u,y=q[i].v;
		if(L[x]&&L[y])q0.push_back(q[i]);
		if(R[x]&&R[y])q1.push_back(q[i]);
	}
	for(i=0; i<n; i++)dis[a[i]]=-1;
	bfs(u);
	for(i=0; i<Q; i++)ans[q[i].id]=min(ans[q[i].id],dis[q[i].u]+dis[q[i].v]);
	for(i=0; i<n; i++)dis[a[i]]=-1;
	bfs(v);
	for(i=0; i<Q; i++)ans[q[i].id]=min(ans[q[i].id],dis[q[i].u]+dis[q[i].v]);
	solve(a0,e0,q0),solve(a1,e1,q1);
	return;
}
vector<int >a;
vector<enode>e;
vector<qnode>q;
signed main() {
	memset(ans,0x3f,sizeof(ans));
	int n,m,Q,u,v,i;
	scanf("%d",&n);
	m=n-3;
	for(i=1; i<=n; i++)
		a.push_back(i),e.push_back(enode(i,i%n+1));
	for(i=1; i<=m; i++) 
		scanf("%d%d",&u,&v),
		e.push_back(enode(u,v));
	scanf("%d",&Q);
	for(i=1; i<=Q; i++)
		scanf("%d%d",&u,&v),
		q.push_back(qnode(u,v,i));
	solve(a,e,q);
	for(i=1; i<=Q; i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

谢谢！

---

## 作者：Betrayer_of_love (赞：1)

### Description
------------

给定一个正 $n$ 边形及其三角剖分，共 $2n-3$ 条边（$n$ 条多边形的边和 $n-3$ 条对角线），每条边的长度为 $1$ 。

共 $q$ 次询问，每次询问给定两个点，求它们的最短距离。

### Solution
------------
这道题目说明了一个道理，那就是分治不一定需要合并答案。

由于给出的图是一个多边形的三角剖分，因此每条对角线都将这个多边形分成了两部分。考虑分治，每次在选出一条对角线使得两部分点数尽可能均匀，递归求解。

对于一个询问 $(p,q)$，设所选对角线为 $(a,b)$，考虑当他们同时在选出对角线的一侧的情况，分别在选出对角线的两侧的情况。在同一侧的情况可以递归求，在两侧就以 $a$ 和 $b$ 为起点 bfs，不难发现 $p$ 到 $q$ 的路径一定经过 $a,b$ 中至少一个，取 $\min$ 即可。

一开始写的时候非常 naive 的把 $\max$ 打成了 $\min$，$100s$ 的题目卡得我有点~~愧疚~~。

~~据说可以转成对偶图然后点分治，反正我不会写~~。

### CODE

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define rep(i,st,ed) for (int i=st;i<=ed;++i)
#define fill(x,t) memset(x,t,sizeof(x))

const int INF=0x7fffffff;
const int N=2000005;
const int E=4000005;

struct Q {int st,ed,id;} t[N],q[N],g1[N],g2[N];
struct edge {int x,y,next;} e[E];

int dis[2][N],queue[N];
int ls[N],edCnt;
int ans[N],a[N],g3[N],g4[N];
int n,m,tot;

int read() {
    int x=0,v=1; char ch=getchar();
    for (;ch<'0'||ch>'9';v=(ch=='-')?(-1):(v),ch=getchar());
    for (;ch<='9'&&ch>='0';x=x*10+ch-'0',ch=getchar());
    return x*v;
}

void add_edge(int x,int y) {
    e[++edCnt]=(edge) {x,y,ls[x]}; ls[x]=edCnt;
    e[++edCnt]=(edge) {y,x,ls[y]}; ls[y]=edCnt;
}

int find(int l,int r,int x) {
    int ret,mid;
    for (;l<=r;(a[mid=(l+r)/2]>=x)?(r=mid-1):(l=mid+1));
    return r+1;
}

void bfs(int st,int l,int r,int *dis) {
    rep(i,l,r) dis[a[i]]=INF; dis[st]=0;
    int head=1,tail=0;
    queue[++tail]=st;
    while (head<=tail) {
        int now=queue[head++];
        for (int i=ls[now];i;i=e[i].next) {
            if (dis[now]+1<dis[e[i].y]&&a[find(l,r,e[i].y)]==e[i].y) {
                dis[e[i].y]=dis[now]+1;
                queue[++tail]=e[i].y;
            }
        }
    }
}

int get_ans(Q now) {
    int ret=INF;
    ret=std:: min(ret,dis[0][now.st]+dis[0][now.ed]);
    ret=std:: min(ret,dis[1][now.st]+dis[1][now.ed]);
    ret=std:: min(ret,dis[0][now.st]+1+dis[1][now.ed]);
    ret=std:: min(ret,dis[1][now.st]+1+dis[0][now.ed]);
    return ret;
}

void solve(int l1,int r1,int l2,int r2,int l3,int r3) {
    if (l3>r3) return ;
    int rec,mn=INF;
    rep(i,l1,r1) {
        int x=find(l2,r2,t[i].st),y=find(l2,r2,t[i].ed);
        if (x>y) std:: swap(x,y);
        int tmp=std:: max(y-x+1,r2-l2+1-(y-x));
        if (tmp<mn) {
            mn=tmp;
            rec=i;
        }
    }
    bfs(t[rec].st,l2,r2,dis[0]);
    bfs(t[rec].ed,l2,r2,dis[1]);
    int cnt1=0,cnt2=0;
    rep(i,l3,r3) {
        if (q[i].st==t[rec].st&&q[i].ed==t[rec].ed) {
            ans[q[i].id]=1;
            continue;
        }
        ans[q[i].id]=std:: min(ans[q[i].id],get_ans(q[i]));
        if (q[i].st>t[rec].st&&q[i].st<t[rec].ed&&q[i].ed>t[rec].st&&q[i].ed<t[rec].ed) {
            g1[++cnt1]=q[i];
        } else if ((q[i].st<t[rec].st||q[i].st>t[rec].ed)&&(q[i].ed>t[rec].ed||q[i].ed<t[rec].st)) {
            g2[++cnt2]=q[i];
        }
    }
    rep(i,1,cnt1) q[l3+i-1]=g1[i];
    rep(i,1,cnt2) q[l3+cnt1+i-1]=g2[i];
    int cnt3=0,cnt4=0;
    rep(i,l2,r2) {
        if (t[rec].st<=a[i]&&a[i]<=t[rec].ed) g3[++cnt3]=a[i];
        if (t[rec].st>=a[i]||a[i]>=t[rec].ed) g4[++cnt4]=a[i];
    }
    rep(i,1,cnt3) a[l2+i-1]=g3[i];
    rep(i,1,cnt4) a[l2+cnt3+i-1]=g4[i];
    int cnt5=0,cnt6=0;
    rep(i,l1,r1) if (i!=rec) {
        if (t[i].st>=t[rec].st&&t[i].ed<=t[rec].ed) {
            g1[++cnt5]=t[i];
        } else g2[++cnt6]=t[i];
    }
    rep(i,1,cnt5) t[l1+i-1]=g1[i];
    rep(i,1,cnt6) t[l1+cnt5+i-1]=g2[i];
    solve(l1+cnt5,l1+cnt5+cnt6-1,l2+cnt3,l2+cnt3+cnt4-1,l3+cnt1,l3+cnt1+cnt2-1);
    solve(l1,l1+cnt5-1,l2,l2+cnt3-1,l3,l3+cnt1-1);
}

int main(void) {
    n=read();
    rep(i,1,n) a[i]=i;
    rep(i,1,n-3) {
        int st=read(),ed=read();
        if (st>ed) std:: swap(st,ed);
        add_edge(st,ed);
        t[i]=(Q) {st,ed};
    }
    rep(i,1,n) add_edge(i,i%n+1);
    m=read();
    rep(i,1,m) ans[i]=INF;
    rep(i,1,m) {
        int st=read(),ed=read();
        if (st>ed) std:: swap(st,ed);
        if (st==ed) ans[i]=0;
        else if (st%n+1==ed||ed%n+1==st) ans[i]=1;
        else q[++tot]=(Q) {st,ed,i};
        ans[i]=std:: min(ans[i],std:: min(ed-st,st+n-ed));
    }
    solve(1,n-3,1,n,1,tot);
    rep(i,1,m) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：caocao11 (赞：1)

附一个博客链接 [其实观看体验不一定比这里好](https://www.cnblogs.com/jstcao/p/14602891.html)。

考虑多边形三角剖分的实际意义，即每次用一条对角线将一个多边形分为两个。很容易想到分治：每次在当前多边形中选出一条对角线使得两部分点数尽可能均匀,直到当前多边形为三角形为止。

询问时若两个点在选定的对角线同侧，则递归求解。若在两侧，由于三角剖分的性质，不会有任何一条边穿过此对角线。因此两点间最短路必然穿过对角线端点中的一个。bfs 计算每个点到对角线距离即可。

细节注释在代码里。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
using namespace std;
const int N=1002005;
int head[N],dis[2][N],p[N],b[N],h1[N],h2[N],can[N],ans[N],num,cnt,n,m;
struct asd{
	int next,to;
}a[N];
struct edge{
	int x,y;
}e[N],t1[N],t2[N];
struct Q{
	int x,y,id;
}q[N],f1[N],f2[N];
void add(int x,int y){
	a[++num].next=head[x];
	head[x]=num;
	a[num].to=y;
}
void bfs(int s,int l,int r,int *dis){
	cnt++;
	for(int i=l;i<=r;i++) dis[p[i]]=0x3f3f3f3f,can[p[i]]=cnt;//打标记，只需遍历当前多边形上的点即可
	dis[s]=0; queue<int>q; q.push(s);
	while(!q.empty()){
		int k=q.front();q.pop();
		for(int i=head[k];i;i=a[i].next){
			if(dis[a[i].to]==0x3f3f3f3f&&can[a[i].to]==cnt){
				dis[a[i].to]=dis[k]+1;
				q.push(a[i].to);
			}
		}
	}
}
void solve(int pl,int pr,int el,int er,int ql,int qr){//  p：点，e：边，q：询问
	if(ql>qr||el>er||pl>pr) return ;
	int num=0,now=0,Max=0x3f3f3f3f;
	for(int i=pl;i<=pr;i++)
		b[p[i]]=++num;                               // 将多边形上的点离散化
	for(int i=el;i<=er;i++){
		int k=b[e[i].y]-b[e[i].x]+1;
		if(max(k,pr-pl+3-k)<Max){
			Max=max(k,pr-pl+3-k);
			now=i;
		}
	}                                               //找分割边
	bfs(e[now].x,pl,pr,dis[0]);bfs(e[now].y,pl,pr,dis[1]);
	int n1=0,n2=0;
	for(int i=ql;i<=qr;i++){
		if(q[i].x>e[now].x&&q[i].y<e[now].y) f1[++n1]=q[i];
		else if((q[i].x<e[now].x||q[i].x>e[now].y)&&(q[i].y<e[now].x||q[i].y>e[now].y)) f2[++n2]=q[i];
		else ans[q[i].id]=min(ans[q[i].id],min(dis[1][q[i].x]+dis[1][q[i].y],dis[0][q[i].x]+dis[0][q[i].y]));
	}
	for(int i=1;i<=n1;i++) q[ql+i-1]=f1[i];
	for(int i=1;i<=n2;i++) q[ql+n1+i-1]=f2[i];
	int n3=0,n4=0,k=p[pr+1],l=p[pr+2];             //对角线端点重复计算在两个多边形里，覆盖掉p[pr+1],p[pr+2]的值，待会要回溯
	for(int i=pl;i<=pr;i++){
		if(p[i]>=e[now].x&&p[i]<=e[now].y)
			h1[++n3]=p[i];
		if(p[i]<=e[now].x||p[i]>=e[now].y)
			h2[++n4]=p[i];
	}
	for(int i=1;i<=n3;i++) p[pl+i-1]=h1[i];
	for(int i=1;i<=n4;i++) p[pl+n3+i-1]=h2[i];
	int n5=0,n6=0;
	for(int i=el;i<=er;i++){
		if(i==now) continue;
		if(e[i].x>=e[now].x&&e[i].y<=e[now].y) t1[++n5]=e[i];
		else t2[++n6]=e[i];
	}
	for(int i=1;i<=n5;i++) e[el+i-1]=t1[i];
	for(int i=1;i<=n6;i++) e[el+n5+i-1]=t2[i];
	solve(pl,pl+n3-1,el,el+n5-1,ql,ql+n1-1);
	solve(pl+n3,pl+n3+n4-1,el+n5,el+n5+n6-1,ql+n1,ql+n1+n2-1);
	p[pr+1]=k;p[pr+2]=l;                          //回溯
}
int main(){
	int i,j,k,l;
	freopen("bsh.in","r",stdin);
	freopen("bsh.out","w",stdout);
	scanf("%d",&n);
	for(i=1;i<=n;i++) p[i]=i;
	for(i=1;i<n;i++) add(i,i+1),add(i+1,i);
	add(1,n),add(n,1);
	for(i=1;i<=n-3;i++){
		scanf("%d%d",&k,&l);
		if(k>l) swap(k,l);
		add(k,l);add(l,k);
		e[i].x=k;
		e[i].y=l;
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d%d",&k,&l);
		if(k>l) swap(k,l);
		q[i].x=k;
		q[i].y=l;
		q[i].id=i;
		ans[i]=min(l-k,n-(l-k));                   //若k,l为同一个点（且此点不为三角划分的端点）,分治不会处理
	}                                              //此时ans=0，不赋值也可过，这里是为了保险
	solve(1,n,1,n-3,1,m);
	for(i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：bamboo12345 (赞：0)

题意：给出一个三角剖分图，求图上任意两个点的最短路。

做法：

三角剖分图这样的图非常有性质，举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/4lilf3og.png)

我们把每个三角形标号，按照有邻边来连接：

![](https://cdn.luogu.com.cn/upload/image_hosting/375lmgfh.png)

我们会发现这样我们会连出来一颗度数 $\le 3$ 的树！那其实这样的话我们就可以考虑对这棵树边分治，一刀劈开这个多边形，类似猫树的想法去计算答案。

具体的，我们先特判答案为 $0/1$ 的情况，然后因为这棵树上的边一定会跨过中间的一条中间的剖分的边，我们以这条边的两个端点跑 bfs，直接去回答当前分治时的询问集合，但是对于被这条边分在同一侧的询问其实还是有可能有更小的答案的，我们就把他往两边丢即可。

类似地比较多次询问两个点一棵树上的距离，我们考虑对于一个经过当前边的询问其实是不需要再去递归了，但是两侧的询问我们要往左右扔。

可能说的有点抽象，给出代码帮助理解一下：

```
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
int n, deg[maxn], use[maxn], q;
vector<int> e[maxn];
struct Edge{
	int to, val;
};
vector<Edge> g[maxn];
map<pair<int, int>, int> mp, in;
map<pair<int, int>, pair<int, int> > cr;
struct tri {
	int x, y, z;
} t[maxn];
int sx[maxn], sy[maxn], ans[maxn];
vector<int> nw;
void add(int x, int y) {
//	cout << x << " " << y << endl;
	g[x].push_back(Edge{y, 0});
	g[y].push_back(Edge{x, 0});
}
void topo() {
	queue<int> q;
	for (int i = 1; i <= n; i++) {
		if(deg[i] == 2)
			q.push(i);
	//	cout << deg[i] << " ";
	}
//	cout << endl;
	for (int i = 1; i <= n - 2; i++) {
		int u = q.front(); q.pop();
		use[u] = 1;
		int a = 0, b = 0;
		for (int j = 0; j < e[u].size(); j++) {
			if(!use[e[u][j]]) 
				(!a ? a : b) = e[u][j];
		}
		t[i] = {u, a, b};
	//	cout << u << " " << a << " " << b << endl;
		if(mp[make_pair(u, a)])
			add(i, mp[make_pair(u, a)]), cr[make_pair(i, mp[make_pair(u, a)])] = cr[make_pair(mp[make_pair(u, a)], i)] = make_pair(u, a);
		if(mp[make_pair(u, b)])
			add(i, mp[make_pair(u, b)]), cr[make_pair(i, mp[make_pair(u, b)])] = cr[make_pair(mp[make_pair(u, b)], i)] = make_pair(u, b);
		if(mp[make_pair(a, b)])
			add(i, mp[make_pair(a, b)]), cr[make_pair(i, mp[make_pair(a, b)])] = cr[make_pair(mp[make_pair(a, b)], i)] = make_pair(a, b);
		else
			mp[make_pair(a, b)] = i, mp[make_pair(b, a)] = i;
		for (int j = 0; j < e[u].size(); j++) {
			deg[e[u][j]]--;
			if(deg[e[u][j]] == 2)
				q.push(e[u][j]);
		}
	}
	for (int i = 1; i <= n; i++)
		use[i] = 0;
}
int xt, yt, mx, sz[maxn], all;
void getsz(int u, int fa) {
	sz[u] = 1; all++;
	for (int i = 0; i < g[u].size(); i++) {
		Edge v = g[u][i];
		if(v.val || v.to == fa)
			continue;
		getsz(v.to, u);
		sz[u] += sz[v.to];
	}
}
void getrt(int u, int fa) {
	for (int i = 0; i < g[u].size(); i++) {
		Edge v = g[u][i];
		if(v.val || v.to == fa)	
			continue;
		if(max(sz[v.to], all - sz[v.to]) < mx)
			mx = max(sz[v.to], all - sz[v.to]), xt = u, yt = v.to;
		getrt(v.to, u);
	}
}
void clr(int x, int y) {
	for (int i = 0; i < g[x].size(); i++) 
		if(g[x][i].to == y)
			g[x][i].val = 1;
	for (int i = 0; i < g[y].size(); i++)
		if(g[y][i].to == x)
			g[y][i].val = 1;
}
vector<int> pos;
void renew(int u, int c) {
	use[t[u].x] = use[t[u].y] = use[t[u].z] = c;
	pos.push_back(t[u].x), pos.push_back(t[u].y), pos.push_back(t[u].z);
}
void get_col(int u, int fa, int c) {
	renew(u, c);
	for (int i = 0; i < g[u].size(); i++) {
		Edge v = g[u][i];
		if(v.to == fa || v.val)
			continue;
		get_col(v.to, u, c);
	}
}
int dis[maxn];
void bfs(int s) {
	for (int i = 0; i < pos.size(); i++) 
		dis[pos[i]] = -1;
	dis[s] = 0;
	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 0; i < e[u].size(); i++) {
			int v = e[u][i];
			if(dis[v] == -1 && use[v])
				q.push(v), dis[v] = dis[u] + 1;
		}
	}
}
void solve(int x, int y, vector<int> &nw, int d) {
	if(!nw.size())
		return ;
//	cout << x << " adsf" << y << " " << mx << endl;
	clr(x, y);
	get_col(x, y, 1), get_col(y, x, 2);
	int s1 = cr[make_pair(x, y)].first, s2 = cr[make_pair(x, y)].second;
//	cout << s1 << " " << s2 << endl;
	bfs(s1);
	for (int i = 0; i < nw.size(); i++) {
		ans[nw[i]] = min(ans[nw[i]], dis[sx[nw[i]]] + dis[sy[nw[i]]]);
//		if(nw[i] == 29)
//			cout << dis[sx[nw[i]]] << " " << sx[nw[i]] << " " << dis[sy[nw[i]]] << endl;
	}
	bfs(s2);
	for (int i = 0; i < nw.size(); i++)
		ans[nw[i]] = min(ans[nw[i]], dis[sx[nw[i]]] + dis[sy[nw[i]]]);
//	for (int i = 0; i < nw.size(); i++)
//		if(nw[i] == 29)
//			cout << sx[nw[i]] << " " << sy[nw[i]] << " " << ans[nw[i]] << " " << s1 << " " << s2 << endl;
	vector<int> nwl, nwr;
	for (int i = 0; i < nw.size(); i++) {
		if(use[sx[nw[i]]] == use[sy[nw[i]]])
			if(use[sx[nw[i]]] == 1)
				nwl.push_back(nw[i]);
			else
				nwr.push_back(nw[i]);
	}
	for (int i = 0; i < pos.size(); i++)
		use[pos[i]] = 0;
	pos.clear();
	
	all = 0, getsz(x, y), mx = 2e9, getrt(x, y);
	if(sz[x] != 1)
		solve(xt, yt, nwl, d + 1);
	all = 0, getsz(y, x), mx = 2e9, getrt(y, x);
	if(sz[y] != 1)
		solve(xt, yt, nwr, d + 1);
}
int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		deg[i] += 2;
		int x = (i == 1 ? n : i - 1), y = (i == n ? 1 : i + 1);
		e[i].push_back(x), e[i].push_back(y);
		in[make_pair(i, x)] = 1;
		in[make_pair(i, y)] = 1;
	}
	for (int i = 1; i <= n - 3; i++) {
		int x, y; cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
		in[make_pair(x, y)] = 1;
		in[make_pair(y, x)] = 1;
		deg[x]++, deg[y]++;
	}
	topo();
	cin >> q;
	for (int i = 1; i <= q; i++) {
		cin >> sx[i] >> sy[i], ans[i] = 2e9;
		if(in[make_pair(sx[i], sy[i])] || sx[i] == sy[i])
			ans[i] = (sx[i] != sy[i]);
		else
			ans[i] = 2e9, nw.push_back(i);
	}
	all = 0, getsz(1, 0), mx = 2e9, getrt(1, 0);
	solve(xt, yt, nw, 0);
	for (int i = 1; i <= q; i++)
		cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：artofproblemsolving (赞：0)

直接进入正题：

我们可以使用**分治**的思想来简化重复信息的多次计算。

我们对当前的多边形进行分治，选取一条分的最均匀的对角线，可以知道，所有跨过这条对角线的一对点的答案，是可以通过仅计算两块拆分后的多边形内的到对角线两端点的最短路，并将两边的结果分类合并得到的，这是因为我们的询问最小值的路径是一定会经过这条边。

由于我们分治时每一层都需要知道点和边的信息，且要将所有尚未完成的询问带到下一层，所以要注意内存问题。

代码：

```cpp
void ins(int u,int v){e[++cnt]=(edge){v,first[u]};first[u]=cnt;}
int find(int l,int r,int x){return lower_bound(id+1,id+r+1,x)-id;}
void bfs(int S,int pl,int pr,int *dis){
	int head=0,tail=0;
	for(int i=pl;i<=pr;i++) dis[id[i]]=inf;
	qq[tail++]=S;dis[S]=0;
	while(head!=tail){
		int u=qq[head++];
		for(int i=first[u];i;i=e[i].next){
			int to=e[i].to;
			if(!ok[to]) continue;
			if(dis[to]==inf) dis[to]=dis[u]+1,qq[tail++]=to;
		}
	}
}
void work(int dl,int dr,int pl,int pr,int ql,int qr){
	if(dl>dr||pl>pr||ql>qr) return;
	int mn=inf,mnid=0;
	for(int i=dl;i<=dr;i++){
		x=find(pl,pr,l[i].x);y=find(pl,pr,l[i].y);
		if(x>y) swap(x,y);
		tmp=max(y-x,x-y+pr-pl+1);
		if(tmp<mn) mn=tmp,mnid=i;
	}
	for(int i=pl;i<=pr;i++) ok[id[i]]=1;
	bfs(l[mnid].x,pl,pr,disx);
	bfs(l[mnid].y,pl,pr,disy);
	for(int i=pl;i<=pr;i++) ok[id[i]]=0;
	int t1=0,t2=0,t3=0,t4=0,t5=0,t6=0;
	for(int i=ql;i<=qr;i++){
		x=q[i].x;y=q[i].y;t=q[i].id;
		if(x==l[mnid].x&&y==l[mnid].y){ans[t]=1;continue;}
		ans[t]=min(ans[t],disx[x]+disx[y]);
		ans[t]=min(ans[t],disy[x]+disy[y]); 
		ans[t]=min(ans[t],disx[x]+disy[y]+1); 
		ans[t]=min(ans[t],disy[x]+disx[y]+1);  
		if(q[i].x>l[mnid].x&&q[i].y<l[mnid].y) h1[++t1]=q[i];
		else if((q[i].x<l[mnid].x||q[i].x>l[mnid].y)&&(q[i].y<l[mnid].x||q[i].y>l[mnid].y)) h2[++t2]=q[i];
	} 
	for(int i=1;i<=t1;i++) id[ql+i-1]=h1[i];
	for(int i=1;i<=t2;i++) id[ql+t1=i-1]=h2[i];
	for(int i=pl;i<=pr;i++){
		if(id[i]>=l[mnid].x&&id[i]<=l[mnid].y) q1[++t3]=id[i];
		if(id[i]<=l[mnid].x||id[i]>=l[mnid].y) q2[++t4]=id[i]; 
	}
	for(int i=1;i<=t3;i++) id[pl+i-1]=q1[i];
	for(int i=1;i<=t4;i++) id[pl+t3+i-1]=q2[i];
	for(int i=dl;i<=dr;i++){
		if(i==mnid) continue;
		if(l[i].x>=l[mnid].x&&l[i].y<=l[mnid].y) h1[++t5]=l[i];
		else h2[++t6]=l[i];
	}
	for(int i=1;i<=t5;i++) l[dl+i-1]=h1[i];
	for(int i=1;i<=t6;i++) l[dl+t5+i-1]=h2[i];
	work(dl+t5,dl+t5+t6-1,pl+t3,pl+t3+t4-1,ql+t1,ql+t1+t2-1);
	work(dl,dl+t5-1,pl,pl+t3-1,ql,ql+t1-1);
}
int main(){
	n=read();
	for(int i=1;i<=n-3;i++){
		l[i].x=read();l[i].y=read();
		ins(l[i].x,l[i].y);ins(l[i].y,l[i].x);
		if(l[i].x>l[i].y) swap(l[i].x,l[i].y);
	}
	for(int i=1;i<n;i++) ins(i,i+1),ins(i+1,i);
	ins(1,n);ins(n,1);
	m=read();
	for(int i=1;i<=m;i++){
		q[i].x=read();q[i].y=read();q[i].id=i;
		if(q[i].x>q[i].y) swap(q[i].x,q[i].y);
		ans[i]=min(q[i].y-q[i].x,q[i].x-q[i].y+n);
	}
	for(int i=1;i<=n;i++) id[i]=i;
	work(1,n-3,1,n,1,m);
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	return 0;
}
```


---

