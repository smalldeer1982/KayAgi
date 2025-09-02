# [COTS 2016] 建造费 Pristojba

## 题目背景

译自 [Izborne Pripreme 2016 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2016/) D2T2。$\texttt{5s,0.5G}$。


## 题目描述


有一张 $n$ 个点的简单无向图 $G$。

给定数列 $p$，边 $(i,j)$（$i\neq j$）的边权为 $p_i+p_j$。

然而，不是所有 $i,j$ 间都有边连接。给定 $m$ 个三元组形如 $x,l,r$，表示「$\forall l\le y\le r$，$x,y$ 间有边连接」。

求出这张无向图的[最小生成树](https://www.luogu.com.cn/user/398152)的边权和。


## 说明/提示



对于 $100\%$ 的数据，保证：
- $1\le n,m\le  10^5$；
- $0\le p_i\le 10^6$；
- $1\le x\le n$；
- $1\le l\le r\le n$，$x\not\in [l,r]$；
- 存在一组解。


| 子任务编号 | $n,m\le  $ |  得分 |  
| :--: | :--: | :--: | 
| $ 1 $    | $ 10^3$  |   $ 20 $   |  
| $ 2 $    | $ 10^5 $  | $ 80 $   |  


## 样例 #1

### 输入

```
4 4
2 4 1 0
1 2 3
1 3 4
3 1 1
4 1 2```

### 输出

```
9```

## 样例 #2

### 输入

```
6 8
3 5 8 2 9 4
3 1 2
6 3 3
3 1 1
6 2 2
2 3 6
3 1 2
3 2 2
4 1 1```

### 输出

```
46```

## 样例 #3

### 输入

```
12 10
9 2 7 5 5 9 3 6 5 7 8 8
6 3 3
9 1 1
6 10 11
1 3 11
5 6 12
3 5 5
12 3 7
6 1 4
4 6 6
10 4 6```

### 输出

```
126```

# 题解

## 作者：Reunite (赞：6)

无聊的 Boruvka 模板题。

显然考虑 Boruvka，现在仅需考虑一轮内的情况。转化为，每个点有颜色 $bl_i$ 和点权 $a_i$，我们希望求出每种颜色最小的异色边。

边是区间的形式，考虑线段树，容易发现我们的要求仅是不与某个颜色相同，那只要维护最小和次小，并保证颜色不同就一定能取到最优了。边显然有两种形式，一个是作为给出三元组起点连到区间内，一个是被上面这种连。只需要写一个线段树支持区间合并查询，再写一个线段树支持区间修改单点查询即可。封装一下可以合并到一起。

每轮复杂度 $O(n\log n)$，而每次至少使连通块数减半，复杂度为 $O(n\log^2 n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll long long
#define inf 1000000000
using namespace std;

int n,m;
int a[100005];
int bl[100005];
int fa[100005];
int vl[100005];
int to[100005];
vector <pair <int,int>> g[100005];
struct Edge{int u,v,w;}e[400005];
struct node{int mn1,mn2,co1,co2;};
node t[400005];
node tg[400005];
node bt[100005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

node operator + (node p,node q){
	pair <int,int> a[5];
	a[1]={p.mn1,p.co1};
	a[2]={q.mn1,q.co1};
	a[3]={p.mn2,p.co2};
	a[4]={q.mn2,q.co2};
	sort(a+1,a+1+4);
	node tmp;
	tmp.mn1=a[1].first,tmp.co1=a[1].second;
	if(a[2].second!=a[1].second){
		tmp.mn2=a[2].first,tmp.co2=a[2].second;
		return tmp;
	}
	if(a[3].second!=a[1].second){
		tmp.mn2=a[3].first,tmp.co2=a[3].second;
		return tmp;
	}
	if(a[4].second!=a[1].second){
		tmp.mn2=a[4].first,tmp.co2=a[4].second;
		return tmp;
	}
	tmp.mn2=inf,tmp.co2=0;
	return tmp;
}

inline void build(int u,int l,int r){
	tg[u]={inf,inf,0,0};
	if(l==r){t[u]={a[l],inf,bl[l],0};return ;}
	int mid=(l+r)>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	t[u]=t[u<<1]+t[u<<1|1];
	return ;
}

inline node qry(int u,int l,int r,int L,int R){
	if(L<=l&&r<=R) return t[u];
	int mid=(l+r)>>1;
	if(L>mid) return qry(u<<1|1,mid+1,r,L,R);
	if(R<=mid) return qry(u<<1,l,mid,L,R);
	return qry(u<<1,l,mid,L,R)+qry(u<<1|1,mid+1,r,L,R);
}

inline void upd(int u,int l,int r,int L,int R,node x){
	if(L<=l&&r<=R){tg[u]=tg[u]+x;return ;}
	tg[u<<1]=tg[u<<1]+tg[u];
	tg[u<<1|1]=tg[u<<1|1]+tg[u];
	int mid=(l+r)>>1;
	if(L<=mid) upd(u<<1,l,mid,L,R,x);
	if(R>mid) upd(u<<1|1,mid+1,r,L,R,x);
	return ;
}

inline node qry(int u,int l,int r,int k){
	if(l==r) return tg[u];
	tg[u<<1]=tg[u<<1]+tg[u];
	tg[u<<1|1]=tg[u<<1|1]+tg[u];
	int mid=(l+r)>>1;
	if(k<=mid) return qry(u<<1,l,mid,k);
	else return qry(u<<1|1,mid+1,r,k);
}

inline int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}

int main(){
	in(n),in(m);
	for(int i=1;i<=n;i++) in(a[i]),fa[i]=bl[i]=i;
	while(m--){
		int u,l,r;
		in(u),in(l),in(r);
		g[u].push_back({l,r});
	}
	ll s=0;
	while(1){
		bool ok=1;
		for(int i=1;i<=n;i++) ok&=(Find(i)==Find(1));
		if(ok) break;
		for(int i=1;i<=n;i++) bl[i]=Find(i),bt[i]={inf,inf,0,0},vl[i]=1e9;
		build(1,1,n);
		int m=0;
		for(int i=1;i<=n;i++){
			node tmp={inf,inf,0,0};
			for(auto tt:g[i]){
				tmp=tmp+qry(1,1,n,tt.first,tt.second);
				upd(1,1,n,tt.first,tt.second,{a[i],inf,bl[i],0});
			}
			if(tmp.co1!=bl[i]&&tmp.co1){
				if(vl[bl[i]]>tmp.mn1+a[i]) vl[bl[i]]=tmp.mn1+a[i],to[bl[i]]=tmp.co1;
			}
			if(tmp.co2!=bl[i]&&tmp.co2){
				if(vl[bl[i]]>tmp.mn2+a[i]) vl[bl[i]]=tmp.mn2+a[i],to[bl[i]]=tmp.co2;
			}
		}
		for(int i=1;i<=n;i++){
			auto tmp=qry(1,1,n,i);
			tmp.mn1+=a[i],tmp.mn2+=a[i];
			bt[bl[i]]=bt[bl[i]]+tmp;
		}
		for(int i=1;i<=n;i++){
			if(Find(i)==i){
				if(bt[i].co1!=i&&bt[i].co1){
					if(vl[i]>bt[i].mn1) vl[i]=bt[i].mn1,to[i]=bt[i].co1;
				}
				if(bt[i].co2!=i&&bt[i].co2){
					if(vl[i]>bt[i].mn2) vl[i]=bt[i].mn2,to[i]=bt[i].co2;
				}
				e[++m]={i,to[i],vl[i]};
			}
		}
		sort(e+1,e+1+m,[](Edge p,Edge q){return p.w<q.w;});
		for(int i=1;i<=m;i++){
			int u=Find(e[i].u),v=Find(e[i].v);
			if(u!=v) fa[u]=v,s+=e[i].w;
		}
	}
	printf("%lld\n",s);

	return 0;
}
```

---

## 作者：XZhuRen (赞：6)

## 观前提示

本篇题解为乱搞做法，但实际跑得很快。

## 考虑传统 Prim 算法

传统的 Prim 算法在于，不断找到不在当前集中的点加入点集，统计答案。

根据 Prim 算法，我们把边拆成两条有向边，本题中即单点到区间和区间到单点。

对于第一种边非常容易统计。每次找到新的单点时，把这个单点对应的区间取更小即可。

本题中即线段树维护一个没有被访问过的区间最近距离，时间复杂度是 $\mathcal{O}(\log n)$ 级别的。

对于第二种边，首先想到用线段树优化建图，每次单点查询一下这个点向上的所有区间向其他单点的连边。更新同上。

分析易得这一部分的时间复杂度是 $\mathcal{O}(n^2\log^2n)$ 级别的，无法通过本题。

## 优化

我们尝试优化第二种边。

依然使用线段树优化建图。

考虑到对于一个点，当前的贡献仅有可能是由目前已经在集合中所有点的最小值贡献的。

所以在线段树建图上每个区间记录最小 $p$ 值，只有当当前 $p$ 小于区间 $p$ 的时候才更新。

复杂度 $\mathcal{O}(n^2\log^2n)$。

其实这个复杂度在于你每次找的都是和当前块连通的最小点，所以跑的很快，近似于 $\mathcal{O}(n\log^2n)$。

## 代码

码风很蓝。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll1;
const ll1 inf=1e9+7;
const int N=1e5+5;
struct edge{
	int lt,rt;
	ll1 w;
};
int n;
int m;
ll1 p[N];
//维护区间最小值
//Prim最小生成树（线段树优化）
struct Node{//线段树找最近点
	int l,r;
	ll1 mnp;int mnpoint;
	ll1 mn;int mnr;//最小点
	ll1 mne;//标记，最小加权边
}t[N*4];
#define ls (o<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
/*
//要维护（点权+加权）最小
//每次区间覆盖操作都是整个的，所以对于修改，
//直接记录区间最小点权
//维护最小和，和上一个做对比就行，所以不用记最小加权
//下传标记可以直接维护加权min
*/
void pushup(int o){
	if(t[ls].mnp<t[rs].mnp)t[o].mnp=t[ls].mnp,t[o].mnpoint=t[ls].mnpoint;
	else t[o].mnp=t[rs].mnp,t[o].mnpoint=t[rs].mnpoint;
	if(t[ls].mn<t[rs].mn)t[o].mn=t[ls].mn,t[o].mnr=t[ls].mnr;
	else t[o].mn=t[rs].mn,t[o].mnr=t[rs].mnr;
}
void update(int o,ll1 w){
	t[o].mne=min(t[o].mne,w);
	ll1 tres=w+t[o].mnp;
	if(tres<t[o].mn)t[o].mn=tres,t[o].mnr=t[o].mnpoint;
}
void pushdown(int o){
	if(t[o].mne==inf)return;
	update(ls,t[o].mne);
	update(rs,t[o].mne);
	t[o].mne=inf;
}
void del(int o,int pos){//使x点失效
	int l=t[o].l,r=t[o].r;
	if(l==r){
		t[o].mnp=inf,t[o].mn=inf;
		return;
	}
	pushdown(o);
	if(pos<=mid)del(ls,pos);
	else del(rs,pos);
	pushup(o);
}
void modify(int o,int lt,int rt,ll1 w){
	int l=t[o].l,r=t[o].r;
	if(l>=lt&&r<=rt){
		update(o,w);
		return;
	}
	pushdown(o);
	if(lt<=mid)modify(ls,lt,rt,w);
	if(rt>mid)modify(rs,lt,rt,w);
	pushup(o);
}
struct Point{
	int l,r;
	int minn;
	vector<edge>E;
}seg[N*4];
void build(int o,int l,int r){
	seg[o].l=l,seg[o].r=r;
	seg[o].E.clear();seg[o].minn=inf;
	t[o]=(Node){l,r,inf,l,inf,inf,inf};
	if(l==r){t[o].mnp=p[l];return;}
	build(ls,l,mid);build(rs,mid+1,r);
	pushup(o);
}
vector<edge>Edges[N];
void ins(int o,int u,int lt,int rt,ll1 w){
	int l=seg[o].l,r=seg[o].r;
	if(l>=lt&&r<=rt){
		seg[o].E.push_back((edge){u,u,w});
		return;
	}
	if(lt<=mid)ins(ls,u,lt,rt,w);
	if(rt>mid)ins(rs,u,lt,rt,w);
}

vector<edge>::iterator pos1;
void query(int o,int pos,ll1 w){
	int l=seg[o].l,r=seg[o].r;
	if(!seg[o].E.empty()){
		if(w<seg[o].minn){
			for(pos1=seg[o].E.begin();pos1!=seg[o].E.end();pos1++)
				modify(1,pos1->lt,pos1->rt,w);
			seg[o].minn=w;
		}
	}
	if(l==r)return;
	if(pos<=mid)query(ls,pos,w);
	else query(rs,pos,w);
}
void init(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",&p[i]);
	int u,l,r;
	build(1,1,n);
	while(m--){
		scanf("%d%d%d",&u,&l,&r);
		ins(1,u,l,r,p[u]);
		Edges[u].push_back((edge){l,r,p[u]});
	}
}
ll1 ans=0;
void Prim(){
	del(1,1);
	query(1,1,p[1]);
	for(pos1=Edges[1].begin();pos1!=Edges[1].end();pos1++)modify(1,pos1->lt,pos1->rt,pos1->w);
	int u;ans=0;
	for(int i=1;i<n;i++){
		u=t[1].mnr;
		ans+=t[1].mn;
		query(1,u,p[u]);
		del(1,u);
		if(!Edges[u].empty()){
			for(pos1=Edges[u].begin();pos1!=Edges[u].end();pos1++)
				modify(1,pos1->lt,pos1->rt,pos1->w);
		}
	}
}

void work(){
	Prim();
	printf("%lld",ans);
}
int main(){
	init();
	work();
	return 0;
}
```

---

## 作者：TLEWA (赞：3)

题解区怎么全部都是 $O(n \log^{2} n)$ 的做法，赶快来发篇常数巨大的严格 $O(n \log n)$ 题解！（认为 $n,m$ 同阶）

## 解题思路

考虑优化朴素的最小生成树过程，由区间连边不难想到线段树优化建图，但是仔细思考之后会发现无法构造出合适的连边方式（也有可能是我太弱了），不过感觉线段树优化是一个感觉很正确的方向，于是我们遍历一下常用的最小生成树算法，发现 Prim 算法的流程似乎很容易转化成区间 RMQ 问题，考虑线段树优化 Prim。

考虑 Prim 算法的单轮流程，假设我们已经有了一个加入生成树中的点集 $U$，如何找到一个距离最近且不在点集中的点？从 $U$ 出发的区间连边非常好在线段树上处理，直接使用类似标记永久化的技巧把最优的起点挂载在线段树节点上，在 pushup 时处理路径即可。但是如果区间连边的起点不在点集 $U$ 中，在线段树上无法形成一个连续区间，难以处理。

怎么办？我们不妨利用 Prim 连边的对称性，取 $U$ 的补集 $V$，也采用和维护 $U$ 类似的方法建立一颗线段树，在这颗新树上，之前难以处理的连边情况变成了多段连续区间，也可以采用和 $U$ 一样的方法维护了。

整理一下，现在我们需要实现两个数据结构：

维护点集 $U$ 联向 $V$ 的路径，支持以下操作：

1. 往点集中加入一个点并断开原点集与其的所有连边
2. 查询与点集 $V$ 的最短连边

维护点集 $V$ 联向 $U$ 的路径，支持以下操作：

1. 往点集中删除一个点，连接原点集与其的所有连边
2. 查询与点集 $U$ 的最短连边

最短连边使用前文所述的方法维护，往点集中加点的操作可以直接在挂载时与原最优起点取较小值，如何处理删点？不难想到可以直接使用 `std::set` 暴力维护，直接这样做的复杂度是 $O(n \log^{2} n)$ 的，有没有更好的方法？

是有的，直接在有序序列上在线随机删除的复杂度不太可能低于 $O(\log n)$，但是我们可以把删除操作懒惰化。具体地，当我们从点集中删除一个点的时候，我们先标记一下这个点已经被删除，然后找到这个点连接的所有区间在线段树上对应的点，如果被删除的点是当前节点对应的最优起点，那么我们从起点队列中弹出这个起点，找到第一个未被删除的起点作为新起点，由于一个区间最多对应 $\log n$ 个线段树节点，这么做的复杂度上界为 $O(n \log n + m \log n)$。

剩下就是如何初始化每个节点上的最优起点队列了，如果我们直接把起点下传到连边区间对应节点上进行排序，那么这部分复杂度会退化到最坏 $O(n \log^{2} n)$，不能接受。于是我们直接把 $V$ 中所有起点先排序好，然后从根节点倒着做归并排序的流程就好了，这部分复杂度 $O(n \log n)$。

如果还有没解释清楚的地方，看代码吧。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N=100005,INF=1e9;

/*
常数起飞了/ll 
*/

int n,m;
int p[N];bool vis[N];

struct Node {int p,l,r;};

#define mid (tre[now].l+tre[now].r>>1)
#define lson (now*2)
#define rson (now*2+1)

struct Tre {
	int l,r;
	int min,min_cost; // 最小 p_i 和最小花费 
	int tag,mtag,cost_v,min_v; // 标记永久化与最短路径 
};

queue<int> que[4*N];
vector<pair<int,int>> vec[N];

struct SGT {
	Tre tre[4*N];
	
	void build(int now,int l,int r) {
		tre[now].l=l,tre[now].r=r;tre[now].min=tre[now].min_cost=INF;
		if(l==r) {tre[now].cost_v=tre[now].min_v=l;return;}
		build(lson,l,mid);build(rson,mid+1,r);
	}
	
	void pushup(int now) {
		if(tre[now].l==tre[now].r) {tre[now].min_cost=p[tre[now].tag]+tre[now].min,tre[now].mtag=tre[now].tag;return;}
		if(tre[lson].min<tre[rson].min) tre[now].min=tre[lson].min,tre[now].min_v=tre[lson].min_v;
		else tre[now].min=tre[rson].min,tre[now].min_v=tre[rson].min_v;
		tre[now].min_cost=min({tre[lson].min_cost,tre[rson].min_cost,p[tre[now].tag]+tre[now].min});
		if(tre[now].min_cost==tre[lson].min_cost) tre[now].cost_v=tre[lson].cost_v,tre[now].mtag=tre[lson].mtag;
		else if(tre[now].min_cost==tre[rson].min_cost) tre[now].cost_v=tre[rson].cost_v,tre[now].mtag=tre[rson].mtag;
		else tre[now].cost_v=tre[now].min_v,tre[now].mtag=tre[now].tag;
	}
	
	void change(int now,int p,int k) {
		if(tre[now].l>p || tre[now].r<p) return;
		if(tre[now].l==tre[now].r) {
			tre[now].min=k;
			pushup(now);
			return;
		}
		change(lson,p,k);change(rson,p,k);
		pushup(now);
	}
	
	void cgmin(int now,int l,int r,int k) { // 添加区间 
		if(tre[now].l>r || tre[now].r<l) return;
		if(tre[now].l>=l && tre[now].r<=r) {
			if(p[k]<p[tre[now].tag]) tre[now].tag=k;
			pushup(now);
			return;
		}
		cgmin(lson,l,r,k);cgmin(rson,l,r,k);
		pushup(now);
	}
	
	void init_que(int now,vector<Node>& vec) { // 初始化队列 
		vector<Node> L,R;
		for(auto& node:vec) {
			if(node.l<=tre[now].l && tre[now].r<=node.r) {
				que[now].push(node.p);
				continue;
			}
			if(node.l<=mid) L.push_back(node);
			if(node.r>mid) R.push_back(node);
		}
		if(!que[now].empty()) tre[now].tag=que[now].front();
		pushup(now);
		if(tre[now].l==tre[now].r) return;
		init_que(lson,L);init_que(rson,R);
		pushup(now);
	}
	
	void del(int now,int l,int r) { // 从队列中懒惰删除 
		if(tre[now].l>r || tre[now].r<l) return;
		if(tre[now].l>=l && tre[now].r<=r) {
			while(!que[now].empty() && vis[que[now].front()]) 
				que[now].pop();
			if(!que[now].empty()) tre[now].tag=que[now].front();
			else tre[now].tag=0;
			pushup(now);
			return;
		}
		del(lson,l,r);del(rson,l,r);
		pushup(now);
	}
};
SGT U,V;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	cin >> n >> m;
	p[0]=INF;
	for(int i=1;i<=n;++i) cin >> p[i];
	
	int x,l,r;vector<Node> v;
	for(int i=1;i<=m;++i) {
		cin >> x >> l >> r;
		vec[x].push_back({l,r});
		v.push_back({x,l,r});
	}
	
	U.build(1,1,n);
	V.build(1,1,n);
	
	sort(v.begin(),v.end(),[&](Node a,Node b) {
		return p[a.p]<p[b.p];
	});
	V.init_que(1,v);
	for(int i=1;i<=n;++i) U.change(1,i,p[i]);
	
	int nxt=1,ans=0;
	for(int i=1;i<=n;++i) {
		vis[nxt]=1;
		for(auto& [l,r]:vec[nxt]) {
			V.del(1,l,r);
			U.cgmin(1,l,r,nxt);
		}
		U.change(1,nxt,INF);
		V.change(1,nxt,p[nxt]);
		if(i==n) break;
		if(U.tre[1].min_cost<=V.tre[1].min_cost)
			ans+=U.tre[1].min_cost,nxt=U.tre[1].cost_v;
		else
			ans+=V.tre[1].min_cost,nxt=V.tre[1].mtag;
	}
	
	cout << ans << '\n';
	
	return 0;
}
```

时空复杂度均为 $O(n \log n)$，但是常数较大（时限 5s，最大测试点用时 874ms，远差于最优解的 141ms），希望能给大家提供一些新的解题思路。

---

## 作者：Masterwei (赞：2)

蓝莓板子题。

原题要求最小生成树的边权之和，考虑 Boruvka 算法。

题目给的是点连向区间的无向边，这里我们分讨一下。

先考虑边是点连向区间的，枚举连通块，用线段树维护最小值。

然后考虑区间连向点，用另一个线段树，每次区间修改，在一个节点维护不同连通块的最大、次大值，如果当前节点和最大值所在的连通块相等，就用次大值即可，反之用最大值。

时间复杂度为 $O(n\log^2n)$。


```cpp
#include<bits/stdc++.h>
#define fir first
#define sec second
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e5+5,inf=2e6;
int n,m;
int a[Maxn];
pair<int,int>t[Maxn<<2];
void build(int x,int l,int r){
	t[x]={inf,-1};if(l==r)return;
	int mid=l+r>>1;
	build(x<<1,l,mid);build(x<<1|1,mid+1,r);
}
void change(int x,int l,int r,int d){
	if(l==r)return void(t[x]={a[d],d});
	int mid=l+r>>1;
	if(mid>=d)change(x<<1,l,mid,d);
	else change(x<<1|1,mid+1,r,d);
	t[x]=min(t[x<<1],t[x<<1|1]);
}
pair<int,int>query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[x];
	int mid=l+r>>1;
	if(mid>=L&&mid<R)return min(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
	if(mid>=L)return query(x<<1,l,mid,L,R);
	return query(x<<1|1,mid+1,r,L,R);
}
pair<int,int>wh[Maxn];
vector<int>g[Maxn];
int f[Maxn];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
struct node{int l,r;};
vector<node>e[Maxn];
struct tree{
	struct Tree{
		pair<int,int>val1,val2;
	}t[Maxn<<2],tmpppp;
	void build(int x,int l,int r){
		t[x].val1=t[x].val2={inf,-1};
		if(l==r)return;
		int mid=l+r>>1;
		build(x<<1,l,mid);build(x<<1|1,mid+1,r);
	}
	void change(int x,int l,int r,int L,int R,pair<int,int>p){
		if(L<=l&&r<=R){
			if(p<t[x].val1){
				if(p.sec!=t[x].val1.sec)t[x].val2=t[x].val1;
				t[x].val1=p;
			}else if(p<t[x].val2&&p.sec!=t[x].val1.sec)t[x].val2=p;
			return;
		}
		int mid=l+r>>1;
		if(mid>=L)change(x<<1,l,mid,L,R,p);
		if(mid<R)change(x<<1|1,mid+1,r,L,R,p);
	}
	void dfs(int x,int l,int r,Tree res){
		if(t[x].val1<res.val1){
			if(t[x].val1.sec!=res.val1.sec)res.val2=res.val1;
			res.val1=t[x].val1;
		}else if(t[x].val1<res.val2&&t[x].val1.sec!=res.val1.sec)res.val2=t[x].val1;
		if(t[x].val2<res.val2&&t[x].val2.sec!=res.val1.sec)res.val2=t[x].val2;
		if(l==r){
			pair<int,int>tmp;
			if(find(l)==res.val1.sec)tmp=res.val2;
			else tmp=res.val1;
			tmp.fir+=a[l];wh[find(l)]=min(wh[find(l)],tmp);
			return;
		}
		int mid=l+r>>1;
		dfs(x<<1,l,mid,res);dfs(x<<1|1,mid+1,r,res);
	}
}A;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++){
		int x=read(),l=read(),r=read();
		e[x].push_back({l,r});
	}
	int kuai=n-1;long long ans=0;
	while(kuai){
		A.build(1,1,n);
		for(int i=1;i<=n;i++)g[i].clear(),wh[i]={inf,-1};
		for(int i=1;i<=n;i++)g[find(i)].push_back(i);
		build(1,1,n);
		for(int i=1;i<=n;i++){
			if(find(i)==i){
				for(int k:g[i]){
					for(node j:e[k]){
						pair<int,int>tmp=query(1,1,n,j.l,j.r);
						tmp.fir+=a[k];
						wh[i]=min(wh[i],tmp);
						tmp.sec=i;tmp.fir=a[k];
						A.change(1,1,n,j.l,j.r,tmp);
					}
				}
				for(int j:g[i])change(1,1,n,j);
			}
		}
		build(1,1,n);
		for(int i=n;i;i--){
			if(find(i)==i){
				for(int k:g[i]){
					for(node j:e[k]){
						pair<int,int>tmp=query(1,1,n,j.l,j.r);
						tmp.fir+=a[k];
						wh[i]=min(wh[i],tmp);
					}
				}
				for(int j:g[i])change(1,1,n,j);
			}
		}
		A.tmpppp.val1=A.tmpppp.val2={inf,-1};
		A.dfs(1,1,n,A.tmpppp);
		for(int i=1;i<=n;i++){
//			printf("%d ",find(i));
			if(wh[i].fir<inf&&find(wh[i].sec)!=find(i)){
				ans+=wh[i].fir;
				f[find(wh[i].sec)]=find(i);
				kuai--;
			}
		}//puts("");
	}printf("%lld\n",ans);
	return 0;
}

```

---

## 作者：_Ch1F4N_ (赞：2)

Boruvka 求最小生成树板子。

考虑每轮求解连通块连向其他连通块的最小权边时，可以用一个线段树维护区间最小次小不同颜色的权值，再用这个线段树把 $x$ 贡献到 $[l,r]$ 上再去 pushdown，对于每个点也处理出最小次小不同颜色的权值，然后就可以对每个连通块确定连出的边，并查集维护下连通块合并即可做到 $O((n+m) \log^2 n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int inf = 1e9+114;
const int maxn = 1e5+114;
int vis[maxn];
struct node{
	pair<int,int> mi,cmi;//(val,col)
	node(){
		mi=make_pair(inf,maxn-14);
		cmi=make_pair(inf,maxn-14);
	}
	node operator+(node x){
		node res=node();
		vector< pair<int,int> > vec;
		if(x.mi.first!=inf) vec.push_back(x.mi);
		if(x.cmi.first!=inf) vec.push_back(x.cmi);
		if(mi.first!=inf) vec.push_back(mi);
		if(cmi.first!=inf) vec.push_back(cmi);
		sort(vec.begin(),vec.end());
		for(pair<int,int> x:vec){
			if(vis[x.second]==0){
				vis[x.second]=1;
				if(res.mi==make_pair(inf,maxn-14)) res.mi=x;
				else if(res.cmi==make_pair(inf,maxn-14)) res.cmi=x;
			}
		}
		for(pair<int,int> x:vec){
			vis[x.second]=0;
		}
		return res;
	}
}tr[maxn<<2];
int fa[maxn],p[maxn];
pair<int,int> to[maxn];
int id[maxn];
int n,m;
int x[maxn],l[maxn],r[maxn];
int found(int u){
	return fa[u]=(fa[u]==u?u:found(fa[u]));
}
const int warma = 17;
void build(int cur,int lt,int rt){
	if(lt==rt){
		id[lt]=cur;
		tr[cur]=node();
		tr[cur].mi=make_pair(p[lt],found(lt));
		return ;
	}
	int mid=(lt+rt)>>1;
	build(cur<<1,lt,mid);
	build(cur<<1|1,mid+1,rt);
	tr[cur]=tr[cur<<1]+tr[cur<<1|1];
}
node ask(int cur,int lt,int rt,int l,int r){
	if(r<lt||rt<l) return node();
	if(l<=lt&&rt<=r) return tr[cur];
	int mid=(lt+rt)>>1;
	return (ask(cur<<1,lt,mid,l,r)+ask(cur<<1|1,mid+1,rt,l,r));
}
void clear(int cur,int lt,int rt){
	tr[cur]=node();
	if(lt==rt) return ;
	int mid=(lt+rt)>>1;
	clear(cur<<1,lt,mid);
	clear(cur<<1|1,mid+1,rt);
}
void add(int cur,int lt,int rt,int l,int r,node c){
	if(r<lt||rt<l) return ;
	if(l<=lt&&rt<=r){
		tr[cur]=tr[cur]+c;
		return ;
	}
	int mid=(lt+rt)>>1;
	add(cur<<1,lt,mid,l,r,c);
	add(cur<<1|1,mid+1,rt,l,r,c);
}
void pushdown(int cur,int lt,int rt){
	if(lt==rt) return ;
	tr[cur<<1]=tr[cur<<1]+tr[cur];
	tr[cur<<1|1]=tr[cur<<1|1]+tr[cur];
	int mid=(lt+rt)>>1;
	pushdown(cur<<1,lt,mid);
	pushdown(cur<<1|1,mid+1,rt);
}
long long ans;
void work(){
	for(int i=1;i<=n;i++) to[i]=make_pair(inf,inf);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		node res=ask(1,1,n,l[i],r[i]);
		res.mi.first+=p[x[i]],res.cmi.first+=p[x[i]];
		if(res.mi.second!=found(x[i])) to[found(x[i])]=min(to[found(x[i])],res.mi);
		else to[found(x[i])]=min(to[found(x[i])],res.cmi);	
	}
	clear(1,1,n);
	for(int i=1;i<=m;i++){
		node c=node();
		c.mi.first=p[x[i]],c.mi.second=found(x[i]);
		add(1,1,n,l[i],r[i],c);
	}
	pushdown(1,1,n);
	for(int i=1;i<=n;i++){
		node res=tr[id[i]];
		res.mi.first+=p[i],res.cmi.first+=p[i];
		if(res.mi.second!=found(i)) to[found(i)]=min(to[found(i)],res.mi);
		else to[found(i)]=min(to[found(i)],res.cmi);
	}
	for(int i=1;i<=n;i++){
		if(found(i)==i){
			int val=to[i].first,col=to[i].second;
			if(col<=n&&found(col)!=found(i)){
				ans+=val;
				fa[found(i)]=found(col);
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=m;i++) cin>>x[i]>>l[i]>>r[i];
	for(int i=1;i<=warma;i++) work();
	cout<<ans<<'\n'; 
	return 0;
}
```

---

## 作者：MightZero (赞：1)

本篇题解~~又~~参考了官方题解的解法。

### Solution

首先，根据最小生成树 `Prim` 算法的思想，假设当前已经被加入树中的点的集合为 $P$，其余点的集合为 $Q$，那么构建最小生成树的过程等价于先任选一点放入 $P$，其余点放入 $Q$，再进行 $n-1$ 次操作：每次选择两端点 $u,v$ 满足 $u\in P,v\in Q$ 的所有边中权值最小的一条加入树中，并将 $v$ 从 $Q$ 移至 $P$。

本题的难点是如何找出当前权值最小的边。由于是点与区间连边，可以使用线段树维护。区间向点连边不好直接处理，可以只考虑 $x_k\to [l_k,r_k]$ 中的 $x_k$，建两棵线段树 $T_1,T_2$，分别维护 $x_k\in P$ 和 $x_k\in Q$ 的边。

对于一棵维护 $x_k\in M$（$M$ 为 $P,Q$ 之一）的线段树，由于边的权值可以被拆分为两个端点的权值，首先需要维护区间最小权值来快速得到 $[l_k,r_k]$ 中权值的最小值。具体地，对于点 $x$，若 $x\notin M$，则位置 $x$ 的权值为 $p_x$，否则权值为 $+\infin$；

接下来利用一下线段树优化建图的思想，对线段树上每个节点开一个 `set` ，假设这一节点表示的区间是 $[L,R]$，则将所有满足 $x_k\in M$ 且 $[l_k,r_k]\supseteq [L,R]$ 的 $x_k$ 放入 `set`，按照 $p_x$ 从小到大排列。由于线段树的结构特点，一个 $x_k$ 至多在 $\log n$ 个线段树节点的 `set` 中出现。对于每个线段树节点，区间内权值最小边即为 `set` 中权值最小的点与区间内权值最小的点的连边，`pushup` 时与儿子节点的权值最小边取权值较小者即可。

方便起见，我们称把 $x_k$ 插入所有满足 $[l_k,r_k]\supseteq [L,R]$ 的线段树节点的 `set` 的操作为将 $x_k$ 插入线段树；同样地，称把 $x_k$ 从所有满足 $[l_k,r_k]\supseteq [L,R]$ 的线段树节点的 `set` 中擦除的操作为将 $x_k$ 移出线段树。

初始时所有点都在 $Q$ 中；$T_1$ 中位置 $i$ 的值设为 $p_i$，$T_2$ 所有位置的值全部设为 $+\infin$，将所有 $x_k$ 全部插入 $T_2$。

将一个点 $x$ 从 $Q$ 移动到 $P$ 需要以下两步操作：

- 将 $T_1$ 中位置 $x$ 的值设为 $+\infin$，同时将 $T_2$ 中位置 $x$ 的值设为 $p_i$

- 将 $x$ 插入 $T_1$，同时将 $x$ 移出 $T_2$。

所以只需要先任选一点从 $Q$ 移动到 $P$，再进行 $n-1$ 轮操作，每次操作查询 $T_1,T_2$ 两者的全局权值最小边，取较小者，设为 $u\to v$（$u\in P,v\in Q$），将 $v$ 从 $Q$ 移动到 $P$ ，并将 $p_u+p_v$ 累加到答案即可。

设 $n,m$ 同阶，总体时间复杂度为 $O(n\log^2n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
const ll N=1e5+5,INF=1e18;
vector<pll> rgs[N];
ll n,m,a[N],b[N],ans,ecnt;
bool vis[N];
set<ll> pts;
struct sgt
{
    #define L tr[rt].l
    #define R tr[rt].r
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    struct node{ll l,r;set<pll> st;pll mx;tuple<ll,ll,ll> me;}tr[N<<2];
    void pushup(ll rt)
    {
        if(L!=R)tr[rt].mx=min(tr[ls].mx,tr[rs].mx);
        tr[rt].me={INF,0,0};
        if(tr[rt].st.size())
        {
            auto [mw,mp]=(*tr[rt].st.begin());
            tr[rt].me=min(tr[rt].me,{mw+tr[rt].mx.first,mp,tr[rt].mx.second});
        }
        if(L!=R)tr[rt].me=min({tr[rt].me,tr[ls].me,tr[rs].me});
    }
    void build(ll l,ll r,ll rt,ll* arr)
    {
        L=l,R=r;
        if(L==R)
        {
            tr[rt].mx={arr[l],l};
            pushup(rt);
            return;
        }
        ll mid=L+R>>1;
        build(L,mid,ls,arr);
        build(mid+1,R,rs,arr);
        pushup(rt);
    }
    void insert(ll p,ll l,ll r,ll rt)
    {
        if(l>R||L>r)return;
        if(l<=L&&R<=r)
        {
            tr[rt].st.insert({a[p],p});
            pushup(rt);
            return;
        }
        insert(p,l,r,ls);
        insert(p,l,r,rs);
        pushup(rt);
    }
    void remove(ll p,ll l,ll r,ll rt)
    {
        if(l>R||L>r)return;
        if(l<=L&&R<=r)
        {
            tr[rt].st.erase({a[p],p});
            pushup(rt);
            return;
        }
        remove(p,l,r,ls);
        remove(p,l,r,rs);
        pushup(rt);
    }
    void modify(ll p,ll x,ll rt)
    {
        if(p<L||p>R)return;
        if(L==R)
        {
            tr[rt].mx.first=x;
            pushup(rt);
            return ;
        }
        modify(p,x,ls);
        modify(p,x,rs);
        pushup(rt);
    }
    #undef L
    #undef R
    #undef ls
    #undef rs
}tra,trb;
signed main()
{
    n=read(),m=read();
    loop(i,1,n)a[i]=read(),b[i]=INF;
    tra.build(1,n,1,a);
    trb.build(1,n,1,b);
    loop(i,1,m)
    {
        ll x=read(),l=read(),r=read();
        rgs[x].push_back({l,r});
        pts.insert(x);
    }
    {
        auto x=*pts.begin();
        vis[x]=1;
        pts.erase(x);
        tra.modify(x,INF,1);
        for(auto [l,r]:rgs[x])tra.insert(x,l,r,1);
        trb.modify(x,a[x],1);
        for(auto y:pts)for(auto [l,r]:rgs[y])trb.insert(y,l,r,1);
    }
    while(ecnt<n-1)
    {
        auto ea=tra.tr[1].me;
        auto eb=trb.tr[1].me;
        auto [w,u,v]=min(ea,eb);
        if(vis[v])swap(u,v);
        ans+=w,vis[v]=1;
        tra.modify(v,INF,1);
        for(auto [l,r]:rgs[v])tra.insert(v,l,r,1);
        trb.modify(v,a[v],1);
        for(auto [l,r]:rgs[v])trb.remove(v,l,r,1);
        ecnt++;
    }
    write(ans);
    return 0;
}
```

---

## 作者：xxxxxzy (赞：0)

菠萝板子题，但是讲一下怎么做。

具体算法是维护若干连通块，每次每个连通块连最小的那条边。

这个最多进行 $O(\log n)$ 轮，考虑一轮怎么做。

每次拿个线段树维护不同颜色的最小值，次小值，每次 $(x,l,r)$ 查询 $[l,r]$ 的值，如果最小值的颜色等于 $x$ 的颜色，就选次小值，否则选最小值。

时间 $O(n \log^2 n)$。

---

## 作者：ax_by_c (赞：0)

这种边权看着就比较奇怪，考虑 B 算法：每轮对每个连通块找最小出边，那么每轮连通块个数减半，所以只有 $O(\log n)$ 轮。

把边分成两个方向：

- $x$ 的出边

使用线段树维护区间内权值最小的点和与其不在同一连通块的权值最小的点，那么其中必有至少一个点与 $x$ 不在同一连通块。（单点修改区间查询）

- $y$ 的出边

使用线段树维护对 $y$ 产生贡献的权值最小的 $x$ 和与其不在同一连通块的权值最小的 $x$，那么其中必有至少一个点与 $y$ 不在同一连通块。（区间修改单点查询）

时间复杂度 $O((n+m)\log^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
typedef pair<int,int> pii;
const int intinf=2e9;
const int N=1e5+5;
struct DSU{
	struct node{
		int fa,sz;
	}a[N];
	void Init(int n){
		for(int i=1;i<=n;i++)a[i]={i,1};
	}
	int find(int x){
		if(a[x].fa==x)return x;
		return a[x].fa=find(a[x].fa);
	}
	bool meg(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return 0;
		if(a[x].sz>a[y].sz)swap(x,y);
		a[x].fa=y;
		a[y].sz+=a[x].sz;
		return 1;
	}
}dsu;
int n,m,cnt,a[N],x[N],l[N],r[N],mw[N],mv[N];
ll ans;
pii meg(pii x,pii y){
	if(!x.first||(y.first&&a[x.first]>a[y.first]))swap(x,y);
	if(y.first&&(!x.second||a[y.first]<a[x.second]))if(dsu.find(x.first)!=dsu.find(y.first))swap(x.second,y.first);
	if(y.second&&(!x.second||a[y.second]<a[x.second]))if(dsu.find(x.first)!=dsu.find(y.second))swap(x.second,y.second);
	return x;
}
struct DS1{
	pii tr[N*4];
	void pu(int u){
		tr[u]=meg(tr[u<<1],tr[u<<1|1]);
	}
	void upd(int u,int l,int r,int p){
		if(l==r){
			tr[u]={l,0};
			return ;
		}
		int mid=l+((r-l)>>1);
		if(p<=mid)upd(u<<1,l,mid,p);
		else upd(u<<1|1,mid+1,r,p);
		pu(u);
	}
	pii Q(int u,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr)return tr[u];
		int mid=l+((r-l)>>1);
		if(qr<=mid)return Q(u<<1,l,mid,ql,qr);
		if(mid+1<=ql)return Q(u<<1|1,mid+1,r,ql,qr);
		return meg(Q(u<<1,l,mid,ql,qr),Q(u<<1|1,mid+1,r,ql,qr));
	}
}ds1;
struct DS2{
	pii tr[N*4];
	void pd_(int u,pii x){
		tr[u]=meg(tr[u],x);
	}
	void pd(int u){
		pd_(u<<1,tr[u]),pd_(u<<1|1,tr[u]),tr[u]={0,0};
	}
	void clr(int u,int l,int r){
		tr[u]={0,0};
		if(l==r)return ;
		int mid=l+((r-l)>>1);
		clr(u<<1,l,mid);
		clr(u<<1|1,mid+1,r);
	}
	void upd(int u,int l,int r,int ql,int qr,pii x){
		if(ql<=l&&r<=qr){
			pd_(u,x);
			return ;
		}
		pd(u);
		int mid=l+((r-l)>>1);
		if(ql<=mid)upd(u<<1,l,mid,ql,qr,x);
		if(mid+1<=qr)upd(u<<1|1,mid+1,r,ql,qr,x);
	}
	pii Q(int u,int l,int r,int p){
		if(l==r)return tr[u];
		pd(u);
		int mid=l+((r-l)>>1);
		if(p<=mid)return Q(u<<1,l,mid,p);
		return Q(u<<1|1,mid+1,r,p);
	}
}ds2;
void main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d %d %d",&x[i],&l[i],&r[i]);
	dsu.Init(n),cnt=n;
	while(cnt>1){
		for(int i=1;i<=n;i++)mw[i]=intinf;
		ds2.clr(1,1,n);
		for(int i=1;i<=n;i++)ds1.upd(1,1,n,i);
		for(int i=1,p;i<=m;i++){
			auto it=ds1.Q(1,1,n,l[i],r[i]);
			p=it.first;
			if(dsu.find(p)==dsu.find(x[i]))p=it.second;
			if(p&&a[p]+a[x[i]]<mw[dsu.find(x[i])]){
				mw[dsu.find(x[i])]=a[p]+a[x[i]];
				mv[dsu.find(x[i])]=p;
			}
			ds2.upd(1,1,n,l[i],r[i],{x[i],0});
		}
		for(int i=1,p;i<=n;i++){
			auto it=ds2.Q(1,1,n,i);
			p=it.first;
			if(dsu.find(p)==dsu.find(i))p=it.second;
			if(p&&a[p]+a[i]<mw[dsu.find(i)]){
				mw[dsu.find(i)]=a[p]+a[i];
				mv[dsu.find(i)]=p;
			}
		}
		for(int i=1;i<=n;i++)if(mw[i]!=intinf&&dsu.meg(i,mv[i]))ans+=mw[i],cnt--;
	}
	printf("%lld\n",ans);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

考虑 Boruvka。

计算最小边，显然只有两种情况：$u=x$ 或 $u \in [l,r]$。前者直接暴算，后者扫两遍算贡献。

复杂度 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,INF=0x3f3f3f3f3f3f3f3f;
int n,m,p[MAXN],ans;
vector<pair<int,int>> G[MAXN];
pair<int,int> mn[MAXN<<2],tag[MAXN<<2];
#define lson (k<<1)
#define rson (k<<1|1)
#define mid (l+r>>1)
void update(int k,int l,int r,int pos,pair<int,int> pr) {
	if(l==r) return mn[k]=pr,void();
	if(pos<=mid) update(lson,l,mid,pos,pr);
	else update(rson,mid+1,r,pos,pr);
	return mn[k]=min(mn[lson],mn[rson]),void();	
}
pair<int,int> query(int k,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return mn[k];
	if(y<=mid) return query(lson,l,mid,x,y);
	if(x>mid) return query(rson,mid+1,r,x,y);
	return min(query(lson,l,mid,x,y),query(rson,mid+1,r,x,y));	
}
vector<int> bl[MAXN];
int fa[MAXN],sze[MAXN];
int find(int k) {return (fa[k]==k)?k:(fa[k]=find(fa[k]));}
set<int> pos;
struct Edge {int u,v,w;};
void merge(int u,int v) {
	u=find(u),v=find(v);
	if(sze[u]<sze[v]) swap(u,v);
	pos.erase(v),sze[u]+=sze[v];
	for(auto id:bl[v]) bl[u].push_back(id);
	vector<int>().swap(bl[v]);
	fa[v]=u;
	return ;
}
void Build(int k,int l,int r) {
	mn[k]=tag[k]={INF,0};
	if(l!=r) Build(lson,l,mid),Build(rson,mid+1,r);
	return ;
}
void push_down(int k,int l,int r) {
	return tag[lson]=min(tag[lson],tag[k]),tag[rson]=min(tag[rson],tag[k]),mn[lson]=min(mn[lson],tag[k]),mn[rson]=min(mn[rson],tag[k]),void();	
}
void Update(int k,int l,int r,int x,int y,pair<int,int> v) {
	if(x<=l&&r<=y) return tag[k]=min(tag[k],v),mn[k]=min(mn[k],v),void();
	push_down(k,l,r);
	if(x<=mid) Update(lson,l,mid,x,y,v);
	if(y>mid) Update(rson,mid+1,r,x,y,v);
	return mn[k]=min(mn[lson],mn[rson]),void();
}
pair<int,int> Query(int k,int l,int r,int pos) {
	if(l==r) return mn[k];
	push_down(k,l,r);
	if(pos<=mid) return Query(lson,l,mid,pos);
	return Query(rson,mid+1,r,pos);	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>p[i],fa[i]=i,bl[i].push_back(i),sze[i]=1,pos.insert(i);
	ffor(i,1,m) {
		int x,l,r;
		cin>>x>>l>>r,G[x].push_back({l,r});	
	}
	while(pos.size()>1) {
		ffor(i,1,n) update(1,1,n,i,{p[i],i});
		vector<Edge> vc;
		map<int,pair<int,int>> mn;
		for(auto id:pos) {
			for(auto t:bl[id]) update(1,1,n,t,{INF,t});
			pair<int,int> ot={INF,0};
			for(auto t:bl[id]) for(auto pr:G[t]) {
				auto psl=query(1,1,n,pr.first,pr.second);
				psl.first+=p[t],ot=min(ot,psl);
			}
			if(ot.first!=INF) if(mn.count(id)) mn[id]=min(mn[id],ot); else mn[id]=ot;	
			for(auto t:bl[id]) update(1,1,n,t,{p[t],t});
		}
		Build(1,1,n);
		vector<int> mzx;
		for(auto id:pos) mzx.push_back(id);
		for(auto id:mzx) {
			pair<int,int> ot={INF,0};
			for(auto t:bl[id]) {
				auto pr=Query(1,1,n,t);
				pr.first+=p[t],ot=min(ot,pr);
			}
			if(ot.first!=INF) if(mn.count(id)) mn[id]=min(mn[id],ot); else mn[id]=ot;	
			for(auto t:bl[id]) for(auto pr:G[t]) Update(1,1,n,pr.first,pr.second,{p[t],t});
		}
		reverse(mzx.begin(),mzx.end());
		Build(1,1,n);
		for(auto id:mzx) {
			pair<int,int> ot={INF,0};
			for(auto t:bl[id]) {
				auto pr=Query(1,1,n,t);
				pr.first+=p[t],ot=min(ot,pr);
			}
			if(ot.first!=INF) if(mn.count(id)) mn[id]=min(mn[id],ot); else mn[id]=ot;	
			for(auto t:bl[id]) for(auto pr:G[t]) Update(1,1,n,pr.first,pr.second,{p[t],t});
		}
		for(auto pr:mn) vc.push_back({pr.first,pr.second.second,pr.second.first});
		for(auto pr:vc) {
			int u=pr.u,v=pr.v,w=pr.w;
			if(find(u)!=find(v)) merge(u,v),ans+=w;
		}
	}
	cout<<ans;
	return 0;
}
```

不知为啥写的很丑。可能是我太困了。 /shui

---

## 作者：_WRYYY_ (赞：0)

[在我的博客园观看。](https://www.cnblogs.com/wryyy-233/p/18563697)

这道题还挺有启发性的，至少于我来说，让我清晰的知道了 Prim 和 Kruskal 都适用于什么样的问题上。

### 一些碎碎念

**提示**：你可以不需要看这一部分，这一部分算是作者解决这道题的基本的思路历程。

可能因为最近写多了数据结构优化建图，所以看到这种区间连边的题就不自主的想到了线段树优化建图，但是显然这不太能行，在无向图上添加的这些多的节点是很显然地会影响原图联通性的。

第二眼想到的就是超级钢琴 trick，用一个五元组表示一堆边当中的最优选择，总的来说就是想办法减少边的状态，接着用线段树求解五元组表示的一堆边的最优选择，然后达成我使用 Kruskal 的目的，看上去复杂度就是 $O(n\log_2n)$，但这样也是错的，因为这样实质上并未减少需要的状态，很容易会劣化成 $O(n^2\log n^2)$，你会发现这样不好处理已经在同一集合里的点，最后导致还是把整个区间都加入了优先队列当中。

我在否定了我的很多想法后，只能服输去看官方题解了，但是不好的是官方题解是克罗地亚语，完全看不懂，只能大概知道要用 Prim 和锦标赛树（而且我不是很清楚这是个什么），以及时间复杂度是 $O(n\log_2^2n)$，我尝试用翻译网站翻译也不是很懂，而且也不清楚用 Prim 的理由，但我大概读出一个意思就是分别用两个数据结构维护已经在树上的点和不在树上的点分别到对方的最短的边，这时候我就意识到只有使用 Prim 才能如此做，因为 Kruskal 所维护的集合是散的，只有到最后才会将所有集合并在一起，而 Prim 却是除初状态和末状态之外，一直处于只有在树上的点的集合和不在树上的点的集合这两个集合的状态。

~~写了这么久的题在快退役才认识到这点真是抱歉。~~

### Solution

无论使用 Kruskal 还是 Prim 都无法回避边数过多的问题，而 Kruskal 所产生的集合是散的，不太好维护集合与集合间的边，而 Prim 在算法过程中只会产生两个集合，更方便我们维护，所以我们使用 Prim 算法求解。

以下令 $A$ 表示已经在最小生成树的点中的集合，$B$ 则为不在树上的点的集合。

我们考虑如何将 $B$ 中的点一步一步加入 $A$ 中，因为在一个确定的区间内能覆盖到该区间的点的最小点权加上该区间中的最小点权就是该区间边权最小的边权，而这个信息明显是可以合并的，所以我们可以使用数据结构维护 $A$ 中点覆盖到 $B$ 中的区间所产生的贡献，并同时维护 $B$ 中作为被覆盖的点所产生的贡献，在每个被更新的区间求出最优边权并向上传即可。当然，因为边是双向的，所以也要维护到 $B$ 到 $A$ 中的最优边权。

这里使用的是线段树套 ```set```。

```set``` 维护区间覆盖最小点权，正常线段树维护区间点权。

简述一下过程。

首先一开始 $A$ 是空的，而 $B$ 是全集，所以 $B$ 中覆盖区间是每个点有的区间都要加入，而区间点权每个都是空，$A$ 相反。

接着每次加入点的时候都在 $A$ 中插入点所覆盖到的区间到 ```set``` 里，并在线段树上删除加入点对应的区间点权，在 $B$ 中的操作与在 $A$ 中的操作相反，插入和删除的时候都要更新当前区间的最优边权。

要注意一个区间的最优边权可能会在当前区间直接产生，也可能合并下辖区间的信息。

### Code

```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define ll long long
#define ull unsigned long long
#define m_p make_pair
#define m_t make_tuple
#define N 100010
#define inf 0x3f3f3f3f
using namespace std;
using namespace __gnu_pbds;
typedef pair<int, int> pii;
typedef tuple<int, int, int> Edge;
Edge None = {inf, 0, 0};
int n, p[N];
vector<pii> Seq[N];
bitset<N> vis;
struct SegT_Set
{
	pii tr[N << 2];
	bitset<N << 2> Leaf;
	set<pii> s[N << 2];
	Edge E[N << 2];
	void changE(int k)
	{
		E[k] = None;
		if (!s[k].empty())
		{
			auto [p1, id1] = *s[k].begin();
			auto [p2, id2] = tr[k];
			E[k] = {p1 + p2, id1, id2};
		}
		if (Leaf[k])
			return;
		E[k] = min({E[k], E[k << 1], E[k << 1 | 1]});
		return;
	}
	void tr_up(int k)
	{
		tr[k] = min(tr[k << 1], tr[k << 1 | 1]);
		return changE(k);
	}
	void SetNone(int k, int l, int r)
	{
		if (l == r)
		{
			Leaf.set(k);
			E[k] = None;
			tr[k] = {inf, l};
			return;
		}
		int mid = l + r >> 1;
		SetNone(k << 1, l, mid);
		SetNone(k << 1 | 1, mid + 1, r);
		return tr_up(k);
	}
	void build(int k, int l, int r)
	{
		if (l == r)
		{
			Leaf.set(k);
			E[k] = None;
			tr[k] = {p[l], l};
			return;
		}
		int mid = l + r >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		return tr_up(k);
	}
	void tr_c(int k, int l, int r, int x, int w)
	{
		if (l > x || r < x)
			return;
		if (l == r && r == x)
		{
			tr[k].first = w;
			return changE(k);
		}
		int mid = l + r >> 1;
		if (x <= mid)
			tr_c(k << 1, l, mid, x, w);
		else
			tr_c(k << 1 | 1, mid + 1, r, x, w);
		return tr_up(k);
	}
	void tr_in_del(int k, int l, int r, int x, int y, pii w, bool ty)
	{
		if (l > y || r < x)
			return;
		if (l >= x && r <= y)
		{
			E[k] = None;
			if (ty)
				s[k].insert(w);
			else
				s[k].erase(s[k].find(w));
			return changE(k);
		}
		int mid = l + r >> 1;
		if (x <= mid)
			tr_in_del(k << 1, l, mid, x, y, w, ty);
		if (y > mid)
			tr_in_del(k << 1 | 1, mid + 1, r, x, y, w, ty);
		return tr_up(k);
	}
	Edge tr_a() { return E[1]; }
} T1, T2;
void Unique()
{
	vector<pii> vec;
	for (int i = 1; i <= n; i++)
	{
		sort(Seq[i].begin(), Seq[i].end());
		Seq[i].erase(unique(Seq[i].begin(), Seq[i].end()), Seq[i].end());
		if (Seq[i].empty())
			continue;
		vec.clear();
		auto [l, r] = Seq[i].front();
		for (auto [le, ri] : Seq[i])
		{
			if (le - 1 > r)
			{
				vec.push_back({l, r});
				l = le;
				r = ri;
			}
			else
				r = max(r, ri);
		}
		vec.push_back({l, r});
		Seq[i] = vec;
	}
	return;
}
void Join(int x)
{
	vis.set(x);
	T1.tr_c(1, 1, n, x, inf);
	T2.tr_c(1, 1, n, x, p[x]);
	for (auto [le, ri] : Seq[x])
	{
		T1.tr_in_del(1, 1, n, le, ri, {p[x], x}, 1);
		T2.tr_in_del(1, 1, n, le, ri, {p[x], x}, 0);
	}
	return;
}
signed main()
{
	// auto __IN__ = freopen(".in", "r", stdin);
	// auto __OUT__ = freopen(".out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int m, x, l, r;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	for (int i = 1; i <= m; i++)
	{
		cin >> x >> l >> r;
		Seq[x].push_back({l, r});
	}
	Unique();
	T1.build(1, 1, n);
	T2.SetNone(1, 1, n);
	for (int i = 1; i <= n; i++)
		for (auto [le, ri] : Seq[i])
			T2.tr_in_del(1, 1, n, le, ri, {p[i], i}, 1);
	Join(1);
	ll MST = 0;
	for (int i = 1; i < n; i++)
	{
		auto [w, x, y] = min(T1.tr_a(), T2.tr_a());
		MST += (ll)w;
		if (vis[y])
			swap(x, y);
		Join(y);
	}
	cout << MST;
	return 0;
}
```

---

