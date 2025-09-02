# [PA 2020] Trzy drogi

## 题目背景

本题仅评测部分测试点。

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 5 [Trzy drogi](https://sio2.mimuw.edu.pl/c/pa-2020-1/trz/)**

Byteur 国王，Byteotia 的统治者，梦想着征服 Bitotia。梦见打败敌人是件令人愉快的事，然而生活不是一场梦，醒来后情况就有些不同。

Byteotia 由 $n$ 个城市（编号从 $1$ 到 $n$）组成，由 $m$ 条双向道路连接。每条路都连接着两个不同的城市，但也可能有多条道路连接着同一对城市的情况。从任何城市出发，经过一条或多条道路可以到达其他任意城市。

国王想知道，如果 Bitotia 进攻 Byteotia，从现有的 $m$ 条道路中毁掉三条，会发生什么，将严重损害该国的通信的可能性有多大？你的任务是找出答案！数一数有多少条这样的三条路，在这些路被毁之后，至少有一对城市不可以通过剩余的道路互相到达对方。

## 说明/提示

#### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/ew3z3u7s.png)

请注意，例如移除第 $3,5,7$ 条路后，Byteotia 会被分为多于两部分，但这样的三元组只能被计算一次。

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $2\le n\le 2\times 10^5$，$3\le m\le 5\times 10^5$，$1\le a_i,b_i\le n$，$a_i\neq b_i$。

## 样例 #1

### 输入

```
8 11
2 3
4 5
3 1
3 2
5 7
3 6
1 2
3 4
6 5
8 7
7 8```

### 输出

```
103```

# 题解

## 作者：Rainbow_qwq (赞：18)

从 2023.4 鸽到 2024.3，终于过了这个题。

[pjudge 题解](https://pjudge.ac/blog/qingyu/blog/633)虽然写了，但可能是 bot 写的，写的很不清楚。

根据[经典做法](https://www.luogu.com.cn/problem/P5227)，搜出一棵 dfs 树，对非树边赋随机权值，树边权值为跨过它的所有非树边的权值 xor。

那割三条边能割开的条件就是：选三条边的一个子集，这个子集中的边权 xor 为 0。

也就是存在 $w_i = 0$ 或 $w_i \oplus w_j = 0$ 或 $w_i \oplus w_j \oplus w_k = 0$。

考虑对图进行一些预处理，判掉一些简单情况。

首先判掉割边：对于一条割边，先计算割了它的答案，再把两个端点用并查集缩起来，表示以后再也不会割这条边。

处理完了图上不会有 $w_i = 0$ 的边（也就是割边）。

接下来有一步炫酷操作。

先计算割两条边（再加随意一条边）就能把图割开的情况，也就是 $w_i \oplus w_j = 0$ 的情况。只需要找到所有权值相等的边进行计算。

接下来的限制就是只有砍三条边，也就是 $w_i \oplus w_j \oplus w_k = 0$ 的情况。

由于没有 $w_i = 0$，那么 $w_i,w_j,w_k$ 都是不同的，也就是同一权值的边只会割一条。

观察到**相同权值的边割哪条效果都是一样的**，可以对图进行如下处理：

给每条边加上“长度” $l_i$，表示割这条边答案乘上几（也就是说砍三条边的话答案加上 $l_i\times l_j\times l_k$）。把同一颜色的边中，选一条将长度设为边的数量，其他的长度设为 0。容易发现不改变答案。

对于长度为 0 的边，可以直接并查集把两个端点缩起来。

这样缩完以后，图上没有权值相同的边，并且因此图上没有度数 $\le 2$ 的点，这对后面操作的复杂度证明有用。

接下来分类讨论砍三条边的情况。

**零、三条非树边**

由于树边一定使图联通，所以不可能。

**一、一条树边，两条非树边**

枚举这条树边，看看是否恰有两条非树边跨过这条树边。这部分容易统计。

**二、两条树边，一条非树边**

这种情况就是选树边 $a,b$ 和非树边 $c$，满足 $c$ **覆盖了** $a$ 但**没有覆盖** $b$，而且覆盖 $a$ 和 $b$ 的其他边集合相同。

不难发现，选的 $a,b$ 需要是祖先-后代关系。

然后分两种情况讨论：$a$ 比 $b$ 更深或 $a$ 比 $b$ 更浅。下面称一条非树边更浅的一端为“上端点”，更深的一端为“下端点”。

$a$ 比 $b$ 更深的情况：对于覆盖了 $a$ 的所有非树边，只能选择删“上端点最深”的边，不然这条边一定会使 $a,b$ 的覆盖集合不相同。

$a$ 比 $b$ 更浅的情况：这时要考察覆盖了 $a$ 的所有非树边的下端点。

下面进行一些分类讨论（可以自行手玩）：

- 如果跨过 $a$ 的边只有两条，那就可以任意删一条；
- 如果 $\ge 3$ 条：如果下端点全部成祖先-后代关系，那只能删“下端点最浅”的边；
- 否则就会有分叉，发现在只有两个分叉的时候可能可行，而且删完 $c$ 后要满足剩下的下端点全部成祖先-后代关系。这就需要两组中其中一组只有一条边，并且删去那条边。

将所有情况归纳起来，可以发现一个优美的结论：只需要考虑覆盖了 $a$ 的所有非树边的下端点中，dfs 序最小和最大的两条。

那么对于一个 $a$，总共只有 $3$ 个候选的 $c$。注意两种情况下，$3$ 个候选的 $c$ 可能有重复，需要去重。

把所有树边插进 map，作为 $b$ 的候选，在 map 中查询权值等于 $w_a\oplus w_c$ 的边即可。

两者都能用合并子树的可并堆来维护，每次合并子树的可并堆，然后弹掉上端点在子树内的边。一轮的时间复杂度为 $O(m\log m)$。

**三、三条树边**

此时的方案中，非树边一定不会被割。

所以可以将非树边两端的端点用并查集并起来，得到一张新图，在新图上继续做。

由于图中每个点的度数至少为 $3$，因此 $|E| \geq \frac{3}{2} |V|$，故被缩掉的边数至少为 $|E| - |V| + 1 \ge \frac{1}{2}|V|$。

于是缩的轮数只有 $\log m$ 轮。在每轮中都统计前两种情况即可。

而且每轮缩掉的边数 $>\frac{|E|}{3}$，每轮的复杂度是 $O(m\log m)$，因此时间复杂度 $O(m\log m)$。代码实现十分繁琐。

[Submission](https://loj.ac/s/2020677)

```cpp
#define fi first
#define se second
#define pb push_back
#define mkp make_pair
typedef pair<int,int>pii;
typedef vector<int>vi;

#define maxn 500005
#define inf 0x3f3f3f3f

#define umap unordered_map<ull,int>
int n,m,msum;
ll res;

ll C2(int x){
	return 1ll*x*(x-1)/2;
}
ll C3(int x){
	return 1ll*x*(x-1)*(x-2)/6;
}

struct node{
	int u,v,c;
}g[maxn];

int dsu[maxn];
int gf(int x){
	while(x!=dsu[x])x=dsu[x]=dsu[dsu[x]];
	return x;
}

// connect the edge.
bool cut[maxn];
int id[maxn];
void build(){
	int nn=0,mm=0;
	For(i,1,n)dsu[i]=i,id[i]=0;
	For(i,1,m) if(cut[i]) dsu[gf(g[i].u)]=gf(g[i].v);
	For(i,1,n) if(i==dsu[i] && !id[i]) id[i]=++nn;
	msum=0;
	For(i,1,m){
		g[i].u=gf(g[i].u),g[i].v=gf(g[i].v);
		g[i].u=id[g[i].u],g[i].v=id[g[i].v];
		if(g[i].u!=g[i].v) g[++mm]=g[i],msum+=g[i].c;
	}
	n=nn,m=mm;
	For(i,1,m) cut[i]=0;
}

mt19937_64 rnd(64);
int dep[maxn],dfn[maxn],idx;
int fa[maxn],fe[maxn];
int on[maxn];
ull h[maxn],s[maxn];

vector<pii>e[maxn];

void dfs(int u){
//	cout<<"dfs "<<u<<"\n";
	dfn[u]=++idx;
	for(auto [v,i]:e[u]){
		if(i==fe[u])continue;
		if(!dfn[v]){
			fa[v]=u,fe[v]=i,dep[v]=dep[u]+1;
			on[i]=1;
		//	cout<<"on "<<i<<"\n";
			dfs(v);
			s[u]^=s[v];
		}
		else if(dep[u]>dep[v]) h[i]=rnd(),s[u]^=h[i],s[v]^=h[i];
	}
}

void init()
{
	idx=0;
	For(i,1,n)e[i].clear(),dfn[i]=dep[i]=0,s[i]=0,fa[i]=fe[i]=0; idx=0;
	For(i,1,m)on[i]=0,h[i]=0;
	
	For(i,1,m){
		int u=g[i].u,v=g[i].v;
		e[u].pb(mkp(v,i)),e[v].pb(mkp(u,i));
	}
	dep[1]=1,dfs(1);
	For(i,1,n) e[i].clear();
	For(i,1,m) if(on[i]) {
		int u=g[i].u,v=g[i].v;
		if(dep[u]<dep[v])swap(u,v);
		e[v].pb(mkp(u,i));
		h[i]=s[u];
	}
}

// for cut edges
void solve0()
{
	init();
//	For(i,1,m) cout<<h[i]<<" " ;cout<<" h\n";
	umap mp;
	For(i,1,m) {
		if(!h[i]) --msum,res+=C2(msum),cut[i]=1,g[i].c=0;
		else mp[h[i]]++;
	}
	For(i,1,m){
		if(!h[i]) continue;
		if(!mp.count(h[i])) cut[i]=1,g[i].c=0; // don't use the edge
		else {
			g[i].c=mp[h[i]];
//			cout<<"h: "<<h[i]<<" "<<g[i].c<<"\n";
			res+=C2(g[i].c)*(msum-g[i].c);
			res+=C3(g[i].c);
			mp.erase(h[i]);
		}
	}
	build();
}

umap mp;
ll sum[maxn][3];
void dfs1(int u){
	for(auto [v,i]:e[u]){
		dfs1(v);
		For(i,0,2)sum[u][i]+=sum[v][i];
	}
	if(sum[u][0]==2) res+=g[fe[u]].c*((sum[u][1]*sum[u][1]-sum[u][2])/2);
}

struct TR{
	int rt[maxn],ls[maxn],rs[maxn],d[maxn];
	int val[maxn];
	int merge(int u,int v){
		if(!u||!v)return u|v;
		if(val[u]<val[v])swap(u,v);
		rs[u]=merge(rs[u],v);
		if(d[ls[u]]<d[rs[u]])swap(ls[u],rs[u]);
		d[u]=d[ls[u]]+1;
		return u;
	}
	void mg(int u,int v){
		rt[u]=merge(rt[u],rt[v]);
	}
	void pop(int&u){
		u=merge(ls[u],rs[u]);
	}
	void pp(int u,int lim){
		while(rt[u] && dep[g[rt[u]].v]>=lim) pop(rt[u]);
	}
	void dfs(int u){
		if(!u)return;
		cout<<"x: "<<u<<" "<<val[u]<<"\n";
		dfs(ls[u]),dfs(rs[u]);
	}
	void clear(){
		For(i,1,n) rt[i]=0;
		For(i,1,m) ls[i]=rs[i]=d[i]=val[i]=0;
	}
}T,T2;

vector<pii>tmp;
void chk(int x,int y){
	if(!x||!y)return;
	tmp.pb(mkp(min(x,y),max(x,y)));
//	cout<<"chk "<<x<<" "<<y<<"\n";
//	if(x&&y&&mp.count(h[x]^h[y])) 
//		res+=g[x].c*g[y].c*mp[h[x]^h[y]];
}

void dfs2(int u){
//	cout<<"dfs2 "<<u<<"\n";
	for(auto [v,i]:e[u]){
		dfs2(v);
		T.mg(u,v);
	}
	T.pp(u,dep[u]);
	if(T.rt[u] && fe[u]) /*cout<<"u:: "<<u<<"\n",T.dfs(T.rt[u]),*/chk(fe[u],T.rt[u]);
}

void dfs3(int u){
//	cout<<"dfs3 "<<u<<"\n";
	for(auto [v,i]:e[u]){
		dfs3(v);
		T.mg(u,v),T2.mg(u,v);
	}
	T.pp(u,dep[u]),T2.pp(u,dep[u]);
	if(fe[u]) {
		if(T.rt[u]) chk(fe[u],T.rt[u]);
		if(T2.rt[u]) chk(fe[u],T2.rt[u]);
	}
}

void solve1()
{
	For(i,1,m) if(dep[g[i].u]<dep[g[i].v]) swap(g[i].u,g[i].v);
	
//	For(i,1,m) cout<<g[i].u<<" "<<g[i].v<<" "<<g[i].c<<"    "<<on[i]<<"\n"; puts("----------");
	
	// 1 tree & 2 not
	For(i,1,n) For(j,0,2) sum[i][j]=0;
	For(i,1,m) if(!on[i]) {
		int u=g[i].u,v=g[i].v,w=g[i].c;
		sum[u][0]+=1,sum[v][0]-=1;
		sum[u][1]+=w,sum[v][1]-=w;
		sum[u][2]+=w*w,sum[v][2]-=w*w;
	}
	int lst=res;
	dfs1(1);
	
	T.clear();
	For(i,1,m) if(!on[i]){
		T.val[i]=dep[g[i].v];
		T.rt[g[i].u]=T.merge(T.rt[g[i].u],i);
	}
	dfs2(1);
	
	T.clear(),T2.clear();
	For(i,1,m) if(!on[i]){
		int x=g[i].u;
		T.val[i]=dfn[x];
		T.rt[x]=T.merge(T.rt[x],i);
		T2.val[i]=-dfn[x];
		T2.rt[x]=T2.merge(T2.rt[x],i);
	}
	dfs3(1);
//	puts("qaq");
	
	mp.clear();
	For(i,1,m) if(on[i]) mp[h[i]]+=g[i].c;
	sort(ALL(tmp));
	tmp.erase(unique(ALL(tmp)),tmp.end());
	for(auto [x,y]:tmp){
	//	cout<<"chk "<<x<<" "<<y<<" "<<mp[h[x]^h[y]]<<"\n";
		if(mp.count(h[x]^h[y]))
			res+=g[x].c*g[y].c*mp[h[x]^h[y]];
	}
	tmp.clear();
}

// for rest
void solve()
{
	init();
//	For(i,1,m)cout<<g[i].u<<" "<<g[i].v<<" "<<g[i].c<<"\n";
//	For(i,1,m) cout<<h[i]<<" " ;cout<<" h\n";
//	For(i,1,m) For(j,i+1,m) For(k,j+1,m) 
//		if((h[i]^h[j]^h[k])==0) res+=g[i].c*g[j].c*g[k].c; return;
	while(n>1){
		init();
		solve1();
		For(i,1,m) if(!on[i]) cut[i]=1,g[i].c=0;
		build();
	}
}

signed main()
{
	n=read(),m=read(),msum=m;
	For(i,1,n)dsu[i]=i;
	For(i,1,m)g[i].u=read(),g[i].v=read(),g[i].c=1;
	solve0();
	solve();
	cout<<res;
	return 0;
}
/*

*/
```

---

