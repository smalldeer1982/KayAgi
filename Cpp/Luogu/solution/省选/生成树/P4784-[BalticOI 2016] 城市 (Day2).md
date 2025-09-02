# [BalticOI 2016] 城市 (Day2)

## 题目描述

在 Byteland 有 $n$ 个城市，并且其中有 $k$ 个国王经常来访的主要城市。

其中有 $m$ 条道路，每条道路连接两个城市。然而不幸的是，这些道路的环境极差使得国王无法全速驶过。

对于每条道路，翻修的成本是已知的。你的任务是选择性的翻修道路使得 $k$ 个主要城市都可以经过翻修后的道路互相连通，且总成本尽量小。

## 说明/提示

对于所有子任务，$1 \leq c \leq 10^9$ 且 $n \geq k$。

|子任务|分数|数据范围|
|:-:|:-:|-|
|1|22|$2 \leq k \leq 5,n \leq 20,1 \leq m \leq 40$|
|2|14|$2 \leq k \leq 3,n \leq 10^5,1 \leq m \leq 2 \cdot 10^5$|
|3|15|$2 \leq k \leq 4,n \leq 1000,1 \leq m \leq 2000$|
|4|23|$k = 4,n \leq 10^5,1 \leq m \leq 2 \cdot 10^5$|
|5|26|$k = 5,n \leq 10^5,1 \leq m \leq 2 \cdot 10^5$|


## 样例 #1

### 输入

```
4 3 6
1 3 4
1 2 4
1 3 9
1 4 6
2 3 2
2 4 5
3 4 8```

### 输出

```
11```

# 题解

## 作者：Captain_Paul (赞：13)

题意：给定一个无向图，求把重要节点联通的最小代价（重要节点<=5）



------------
将指定点集合中的所有点连通，且边权总和最小的生成树称为**最小斯坦纳树**（Minimal Steiner Tree）

其实最小生成树是最小斯坦纳树的一种特殊情况，联通了图上所有节点

最小斯坦纳树可以用dp求解

令$f[i][j]$表示以$i$为根，指定集合中点的联通状态为$j$的最小总权值

转移分为两重

- 第一重：枚举当前状态的子集进行转移

  方程为：$f[i][j]=min(f[i][j],f[i][k]+f[i][j xor k])$

  枚举子集的技巧是：$for (k=j\&(j-1);k;k=j\&(k-1))$

- 第二重：在当前状态下对其进行松弛操作

  方程为:$f[i][j]=min(f[i][j],f[k][j]+cost)$

  在这一重只需对这一种状态进行松弛即可，因为其他状态会通过第一重转移更新
 
  松弛操作可以通过spfa实现（如果spfa又双叒叕被卡了请使用堆优化dijkstra）
  
相关题目：[JLOI2015]管道连接   [WC2008]游览计划

现在时限扩大了，加上点常数优化就可以AC了orzzzzz

~虽然我不会写fread~

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>
#include<algorithm>
#define reg register
using namespace std;
typedef long long ll;
const int N=1e5+5;
struct node
{
	int to,nxt,dis;
}edge[N<<2];
struct P
{
	int x; ll d;
	inline friend bool operator < (P a,P b) {return a.d>b.d;}
};
int n,m,p,num,head[N];
ll f[N][32],inf,ans=1e18;
bool vis[N];
priority_queue<P>q;
inline int read()
{
	int x=0,w=1;
	char c=getchar();
	while (!isdigit(c)&&c!='-') c=getchar();
	if (c=='-') c=getchar(),w=-1;
	while (isdigit(c))
	{
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*w;
}
inline void add_edge(int from,int to,int dis)
{
	edge[++num]=(node){to,head[from],dis};
	head[from]=num;
}
inline void dijkstra(int S)
{
	memset(vis,0,sizeof(vis));
	while (!q.empty())
	{
		int u=q.top().x; q.pop();
		if (vis[u]) continue; vis[u]=1;
		for (reg int i=head[u];i;i=edge[i].nxt)
		{
			int v=edge[i].to,d=edge[i].dis;
			if (f[v][S]>f[u][S]+d)
			{
				f[v][S]=f[u][S]+d;
				q.push((P){v,f[v][S]});
			}
		}
	}
}
int main()
{
	n=read(),p=read(),m=read();
	memset(f,127/3,sizeof(f)); inf=f[0][0];
	for (reg int i=1;i<=p;i++) f[read()][1<<(i-1)]=0;
	for (reg int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		add_edge(x,y,z); add_edge(y,x,z);
	}
	for (reg int i=1;i<(1<<p);i++)
	{
		for (reg int k=1;k<=n;k++)
		{
		    for (reg int j=i&(i-1);j;j=i&(j-1))
		      f[k][i]=min(f[k][i],f[k][j]+f[k][i^j]);
		    if (f[k][i]<inf) q.push((P){k,f[k][i]});
		}
		dijkstra(i);
	}
	for (reg int i=1;i<=n;i++) ans=min(ans,f[i][(1<<p)-1]);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：cyffff (赞：8)

[$\text{Link}$](https://www.luogu.com.cn/problem/P4784)
## 题意
给出一张 $n$ 个点，$m$ 条有权边的无向连通图，其中有 $k$ 个点是关键点。求图的一个子图，满足包含了所有 $k$ 个关键点，使得所包含的边集的权值和最小，求这个最小值。

$n\le 10^5$，$m\le2\times10^5$，$k\le5$
## 思路
事实上就是 [$\text{P6192}$](https://www.luogu.com.cn/problem/P6192) 的数据加强版。

首先，我们要知道答案子图是一颗树，因为如果其上有个环，可以断开环上任意一条边，点集不会变化但答案会变小。

考虑状压 $\text {dp}$，设 $dp_{i,S}$ 表示以 $i$ 为根的答案中包含了关键点集合 $S$ 时的答案。

有两种情况：$i$ 的度为 $1$ 或大于 $1$。

- 若 $i$ 的度数为 $1$

考虑其与 $j$ 相连，则有转移
$$dp_{j,S}+w_{(i,j)}\to dp_{i,S}$$
再考虑用 $j$ 更新 $i$，可以考虑使用最短路算法，用 $dp_{j,S}$ 更新所有 $dp_{i,S}$，再用被更新的继续更新其它值。这里与板子不同，必须使用 $\text{Dijkstra}$ 。
$$dp_{j,S}+dis_{i,j}\to dp_{i,S}$$
这部分时间复杂度是 $O(2^k\times m\log n)$ 的。

- 若 $i$ 的度数大于 $1$

考虑 $i$ 可以划分成两个子集之并，枚举 $S$ 的子集，用它与其补集的答案之和更新 $dp_{i,S}$，即
$$dp_{i,S}\gets dp_{i,T},dp_{i,S\backslash T}$$
这里简单说明一下枚举子集的时间复杂度：

$$\begin{aligned}\sum_{S⊆\{1,2\dots n\}}2^{|S|}&=\sum_{k=0}^n2^k\sum_{S⊆\{1,2\dots n\}}[|S|=k]\\
&=\sum_{k=0}^n2^k\binom{n}{k}\\
&=\sum_{k=0}^{n}2^{n-k}\binom{n}{k}\\
&=\sum_{k=0}^{n}1^k2^{n-k}\binom{n}{k}\\
&=3^n\\
\end{aligned}$$

所以这部分时间复杂度是 $O(n\times 3^k)$ 的。

总时间复杂度就是 $O(n\times 3^k+m\log n\times 2^k)$ 的

另外，满足题目要求的树为斯坦纳树，这个算法构建出来的树被称为最小斯坦纳树。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1e5+10,K=5;
int n,m,k,p[N],up;
int cnt,head[N];
ll dp[N][1<<K];
struct Edge{
	int to,nxt,w;
}a[N*4];
inline void add(int u,int v,int w){
	cnt++;
	a[cnt].to=v;
	a[cnt].w=w;
	a[cnt].nxt=head[u];
	head[u]=cnt;
}
struct node{
	int p;
	ll w;
	inline friend bool operator<(const node &a,const node &b){
		return a.w==b.w?a.p<b.p:a.w>b.w;
	}
};
priority_queue<node>q;
bool vis[N];
inline void dijkstra(int s){
	memset(vis,0,sizeof(vis));
	while(!q.empty()){
		node p=q.top();
		q.pop();
		int rt=p.p;
		if(vis[rt]) continue;
		vis[rt]=1;
		for(int i=head[rt];i;i=a[i].nxt){
			int t=a[i].to;
			if(dp[t][s]>dp[rt][s]+a[i].w){
				dp[t][s]=dp[rt][s]+a[i].w;
					if(!vis[t])
						q.push({t,dp[t][s]});
			}
		}
	}
}
int main(){
	memset(dp,127/3,sizeof(dp));
	n=read(),k=read(),m=read();
	for(int i=1;i<=k;i++){
		p[i]=read();
		dp[p[i]][1<<i-1]=0;
	}
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w); 
	}
	up=(1<<k)-1;
	for(int s1=0;s1<=up;s1++){
		for(int i=1;i<=n;i++){
			for(int s2=s1&s1-1;s2;s2=s2-1&s1)
				dp[i][s1]=min(dp[i][s1],dp[i][s2]+dp[i][s1^s2]);
			if(dp[i][s1]<1e17)
				q.push({i,dp[i][s1]});
		}
		dijkstra(s1);
	} 
	write(dp[p[1]][up]);
	flush();
}
```
再见 qwq~

---

## 作者：Smallbasic (赞：1)

其实是斯坦利树模板题。

数据范围明显是状压dp，设$f[i][j]$是以i为树根且当前选中集合状态为j的最优情况。

很明显转移方程需要枚举当前集合的子集。

设当前状态的集合j的一个子集为k，由异或的性质，j的状态一定是由k和j^k转移来。

转移完之后直接跑最短路松弛更新就好了。如果SPFA超时的话可以试试堆优化的Dijkstra。

最后，这道题及其卡常。请尽量用各种奇技淫巧+吸氧才能A。

Code:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;


int n, k, m, en(0), ci[15], vis[100005];
long long f[100005][1 << 5], ans = 1LL * 1e17;

inline int read() {
	register int s = 0, f = 1;
	register char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar();}
	while (isdigit(ch)) s = ((s << 1) + (s << 3)) + (ch ^ 48), ch = getchar();
	return f * s;
}

struct Edge {
	int head, to, nxt, val;
	Edge() {
		head = to = nxt = val = 0;
	}
}ed[1000005];

inline void addedge(int from, int to, int v) {
	ed[++en].to = to; ed[en].val = v; ed[en].nxt = ed[from].head;
	ed[from].head = en;
}

inline long long min_(long long a, long long b) {
	return a < b ? a : b; 
}

struct node {
	int st;
    long long val;
	node(int ST, long long VAL) : st(ST), val(VAL) {}
	inline bool operator < (const node& b) const {
		return val < b.val;
	}
	inline bool operator > (const node& b) const {
		return val > b.val;
	}
};

inline void dijkstra(int id) {
	priority_queue<node, vector<node>, greater<node> >q;
	for (int i = 1; i <= n; ++i) q.push(node(i, f[i][id]));
	while (!q.empty()) {
		int x = q.top().st; q.pop();
		if (vis[x]) continue; vis[x] = 1;
		for (register int l = ed[x].head; l; l = ed[l].nxt)
			if (f[ed[l].to][id] > f[x][id] + ed[l].val)
				f[ed[l].to][id] = f[x][id] + ed[l].val, q.push(node(ed[l].to, f[x][id] + ed[l].val));
	}
}

signed main() {
	n = read(); k = read(); m = read();
	for (int i = 1; i <= k; i++) ci[i] = read();
	int u, v, w;
	while (m--) {
		u = read(); v = read(); w = read();
		addedge(u, v, w); addedge(v, u, w);
	}
	memset(f, 40, sizeof(f));
	for (register int i = 1; i <= k; ++i) f[ci[i]][1 << (i - 1)] = 0;
	for (register int i = 1; i < (1 << k); ++i) {
		for (register int j = 1; j <= n; ++j)
			for (register int l = i & (i - 1); l; l = i & (l - 1)) f[j][i] = min_(f[j][i], f[j][l] + f[j][i ^ l]);
		memset(vis, 0, sizeof(vis));
		dijkstra(i);
	}
	for (register int i = 1; i <= n; ++i) ans = min_(ans, f[i][(1 << k) - 1]);
	printf("%lld", ans);
	return 0;
}
```


---

## 作者：Mortidesperatslav (赞：1)

没想明白为什么这道题会在最小生成树题单里，好像主流是最短路？

这道题是一道不太板的模板题，是树形 dp、状压 dp、最短路的综合应用。

我们用 $f_{i,S}$ 表示以 $i$ 为根的子树，要达到 $S$ 的状态，所需的费用。

这里讲一下 $S$ 是什么。

因为 $k$ 很小，所以我们就用集合 $S$ 表示状态，$S$ 的第 $j$ 位表示是否取到第 $j$ 个主要城市。

那么我们可以求得状态转移方程。

$f_{i,S} = \min\{f_{i,S},f_{i,T}+f_{i,S-T}\}$。这里的 $T$ 是 $S$ 的子集。既然是子集，那么就可以用异或来表示。

接下来是一个大问题：怎么把当前节点的值传给其他节点？

其实不难发现，有这样一个方程：$f_{i,S}=\min\{f_{i,S},f_{j,S}+dis_{i,j}\}$。其中 $dis_{i,j}$ 表示 $i$ 到 $j$ 的距离。我们跑一遍最短路，就可以实现了。

最终答案当然是 $f_{i,U}$（$U$ 表示全集）的最小值。

如果上面的看懂了，应该就不需要代码的注释了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k;
int vis[114514];
int f[114514][32];
int ans = LLONG_MAX;
struct node{
	int v, w;
};
struct node2{
	int u, v;
	bool operator < (node2 b) const {
		return this->v > b.v;
	}
};
vector<node>G[114514];
priority_queue<node2>q;
void dijk(int s){//最短路，传给其余节点
	memset(vis, 0, sizeof vis);
	while (!q.empty()){
		node2 tmp = q.top();
		q.pop();
		int u = tmp.u;
		if (vis[u])
			continue;
		vis[u] = 1;
		for (node vv : G[u])
			if (f[vv.v][s] > f[u][s] + vv.w){
				f[vv.v][s] = f[u][s] + vv.w;
				q.push({vv.v, f[vv.v][s]});
			}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	memset(f, 0x3f3f3f3f, sizeof f);
	cin >> n >> k >> m;
	for (int i = 1; i <= k; i++){
		int x;
		cin >> x;
		f[x][1 << i - 1] = 0;//单个节点当然不需要花费
	}
	for (int i = 1; i <= m; i++){
		int u, v, c;
		cin >> u >> v >> c;
		G[u].push_back({v, c});
		G[v].push_back({u, c});
	}
	for (int i = 1; i < (1 << k); i++){
		for (int k = 1; k <= n; k++){
		    for (int j = i & (i - 1); j ;j = i & (j - 1))
		    	f[k][i] = min(f[k][i], f[k][j] + f[k][i ^ j]);
		    if (f[k][i] < 0x3f3f3f3f3f3f3f3fll)
				q.push({k, f[k][i]});
		}//第一个状态转移方程
		dijk(i);
	}
	for (int i = 1; i <= n; i++)
		ans = min(ans, f[i][(1 << k) - 1]);
	cout << ans;
}
```

其实这就是【模板】最小斯坦纳树。

---

## 作者：_iridescent (赞：0)

### 题意

给定一个带权无向图，求联通 $k$ 个关键点的最小代价。

### 思路

可以较为容易的看出，这就是最小斯坦纳树的板子！所以对于这个题，我们可以考虑用状压的思想来解决。

若令 $dp_{i,s}$ 为以 $i$ 为根节点的一棵树包含关键点集合 $s$ 时的最小代价，则可以根据根节点 $i$ 的度数分成两种情况。

* $i$ 的度数为 $1$，那么设有点 $j$ 与之相连，则有 $$dp_{i,s}+e_i.w \to dp_{j,s}$$，不难发现可以跑最短路求出。（这道题好像卡 SPFA，~~至少我的被卡了~~，所以我使用的 Dijkstra 求的）

* $i$ 的度数不为 $1$，直接暴力将关键点集 $j$ 拆成两个子集，有 $$dp_{i,A}+dp_{i,\complement_sA} \to dp_{i,s}$$

跑完整个之后，答案也就是 $dp_{x,(1<<k)-1}$ 就出来了，完结撒花！

最后还有几点需要注意的：

* 请注意数据范围，给 $dp$ 数组设的初始值一定不能只是 $2^{31}-1$，需要开大点。

* 在枚举 $s$ 的子集时有一个小小的优化，如果当前枚举的子集 $A$ 已经小于 $\complement_sA \operatorname{xor} A$ 时，可以直接退出循环，因为后面的组合已经枚举过了。

* 剩下的注意点就看代码注释吧。完结撒花（真）！

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=2e5+5;
const int inf=1e18; //注意这里的inf不能开0x7fffffff 
int n,m,k,x,tot;
int h[N],vis[N],dp[N][50];
struct pq{
	int id,w;
	bool operator<(const pq &T)const{
		return w>T.w;
	}
};
priority_queue<pq>q;
struct edge{
	int to,nxt,w;
}e[N<<2];
inline void add(int x,int y,int w){
	e[++tot].to=y,e[tot].nxt=h[x],e[tot].w=w,h[x]=tot;
	return;
}
inline void dijkstra(int s){
	memset(vis,0,sizeof vis);
	while(!q.empty()){
		int u=q.top().id;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].to,w=e[i].w;
			if(dp[u][s]+w<dp[v][s]){
				dp[v][s]=dp[u][s]+w;
				q.push({v,dp[v][s]});
			}
		}
	}
	return;
}
signed main(){
//	freopen("P6192.in","r",stdin);
//	freopen("mamba.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k>>m;
	memset(dp,127,sizeof dp);
	for(int i=1;i<=k;i++){
		cin>>x;
		dp[x][1<<(i-1)]=0; // 
	}
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w),add(v,u,w);
	}
	for(int i=1;i<(1<<k);i++){ //最小斯坦纳树模板 
		for(int j=1;j<=n;j++){
			for(int u=i&(i-1);u;u=i&(u-1)){
				if(i<(u^i))break;
				dp[j][i]=min(dp[j][i],dp[j][u]+dp[j][i^u]); //枚举子集 
			}
			if(dp[j][i]<inf){
				q.push({j,dp[j][i]});
				//以此点为出发点 
			}
		}
		dijkstra(i);
	}
	cout<<dp[x][(1<<k)-1]<<endl; //这里dp数组的第一维可以是k个重要城市中的任意一个 
}
/*
10 4 8
2 3 5 7
3 4 10
1 2 7
2 6 9
5 4 9
7 9 10
8 7 6
3 6 10
9 3 9
*/ 
```

---

## 作者：liruixiong0101 (赞：0)

# P4784 [BalticOI 2016 Day2] 城市
题目链接：<https://www.luogu.com.cn/problem/P4784>

## 题意：
给定一个 $n$ 个点，$m$ 条边的带权无向图，求联通 $x_1,x_2,\cdots,x_k$ 的原图的子图的最小总边权和。（$1\le k\le 5,1\le n\le 10^5,1\le m\le 2\times 10^5$）

## 思路：
最小斯坦纳树模板题。

容易发现子图一定是一颗树，否则可以删掉环上的一条边，使图仍然联通但是边权减少。考虑 $f_{i,S}$ 表示以 $i$ 为根的树包含点集 $S$（$S$ 只包含 $x_1,x_2,\cdots,x_k$）

考虑转移方程：对于不变的根 $i$ 和两个集合 $S,T$，那么有 $f_{i,S\cup T}=\min(f_{i,S\cup T},f_{i,S}+f_{i,T})$。我们发现若 $S\cap T\neq\varnothing$，那么 $f_{i,S}+f_{i,T}$ 一定不是最优的，所以我们可以枚举 $S\cup T$ 和 $S$（注意 $S$ 为 $S\cup T$ 的子集），就可以算出 $T$ 了。

在考虑不变的 $S$ 如何转移 $f_{i,S}$，先找到与 $i$ 相邻的点 $j$，很明显有 $f_{i,S}=\min(f_{i,S},f_{j,S}+w(i,j))$（$w(i,j)$ 表示连接 $i$ 和 $j$ 的边的边权），虽然这个式子不满足拓补序，但是观察到它和最短路的转移很像，可以用最短路转移。

然后在考虑这两个转移的拓补序，前者需要对于每一个 $S$ 需要知道 $S$ 的子集的信息，所以先枚举集合与子集，然后用第一种转移，然后再枚举集合的同时用第二种转移即可。

答案显然是：
$$\min_{1\le i\le n} f_{i,\{x_1,x_2,\cdots,x_k\}}$$

---

时间复杂度：$O(3^k\cdot n+2^k\cdot m\cdot\log m)$

枚举集合与子集的复杂度使 $3^k$，这里简述一下，时间复杂度应为:
$$\sum_{S\subseteq\{1,2,\cdots,k\}} 2^{|S|}=\sum_{i=0}^k {k\choose i}\cdot 2^i=\sum_{i=0}^k {k\choose i}\cdot 1^{k-i} \cdot 2^i=(2+1)^k=3^k$$

## 代码：
<https://www.luogu.com.cn/record/171263559>

---

## 作者：PineappleSummer (赞：0)

[P4784 [BalticOI 2016 Day2] 城市](https://www.luogu.com.cn/problem/P4784)

题意：给出一个 $n$ 个点 $m$ 条边的边带权无向图，并指定 $k$ 个关键点，求将 $k$ 个关键点联通的最小代价。

这种题一般 $k$ 非常小，如本题中限制 $k\le 5$，所以考虑状压 DP 解决此类问题。

设 $f_{i,S}$ 为以第 $i$ 个点为根，且该 $k$ 个点联通状态为 $S$ 的最小代价。此处定义的以 $i$ 个点为根指的其实是强制让第 $i$ 个点与 $S$ 中的点联通，这样做方便转移。

有两种转移：
- 当合并两个都包含 $i$ 的联通块时，$f_{i,S}=\min(f_{i,S},f_{i,T}+f_{i,S-T})$，其中 $T$ 是 $S$ 的一个子集。

- 当根改变时，$f_{i,S}=\min (f_{i,S},f_{j,S}+e_{i,j})$，这个是不是很像三角形不等式？我们可以类似最短路更新答案的方式进行转移，常见的是使用 Dijkstra 和 SPFA。

这样跑完之后，答案就是 $\min\limits_{i=1}^nf_{i,2^{k-1}-1}$。

来分析一波时间复杂度，枚举所有的子集总共是 $\mathcal O(3^n)$，单次 Dijkstra 是 $\mathcal O(m\log m)$，总时间复杂度是 $\mathcal O(n\times 3^n+m\log m\times 2^k)$。

**由于将状态放在数组第一维效率较高，所以代码中数组的两维与上述是相反的。**

本题参考代码实现：
```cpp
const int N = 1e5 + 10;
const LL INF = 0x3f3f3f3f3f3f3f3f;
LL n, k, m, ans = 1e18;
LL a[N], f[32][N];
vector <pii> G[N];
bool vis[N];
priority_queue <pii, vector <pii>, greater <pii> > q;
void Dijkstra (int s) {
	for (int i = 1; i <= n; i++) vis[i] = 0;
	while (!q.empty ()) {
		int x = q.top ().second; q.pop ();
		if (vis[x]) continue; vis[x] = 1;
		for (auto i : G[x]) {
			int y = i.fi, v = i.se;
			if (f[s][y] > f[s][x] + v) {
				f[s][y] = f[s][x] + v;
				q.push ({f[s][y], y});
			}
		}
	}
}
signed main () {
	n = read (), k = read (), m = read ();
	memset (f, 0x3f, sizeof f);
	for (int i = 1; i <= k; i++) a[i] = read (), f[1 << (i - 1)][a[i]] = 0;
	for (int i = 1, u, v, w; i <= m; i++) {
		u = read (), v = read (), w = read ();
		G[u].push_back ({v, w});
		G[v].push_back ({u, w});
	}
	for (int mask = 1; mask < (1 << k); mask ++) {
		for (int i = 1; i <= n; i++) {
			for (int j = mask & (mask - 1); j; j = (j - 1) & mask)
				f[mask][i] = min (f[mask][i], f[j][i] + f[mask ^ j][i]);
			if (f[mask][i] < INF) q.push ({f[mask][i], i});
		}
		Dijkstra (mask);
	}
	for (int i = 1; i <= n; i++) ans = min (ans, f[(1 << k) - 1][i]);
	cout << ans;
	return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# P4784 城市 题解

## 题目大意

给定 $n$ 个节点，$m$ 条带边权边，和 $k$ 重要节点。选择一些边，使得这些边能让这 $k$ 个节点连通，代价为选出的边权和。求最小代价。（$k\leq5$）

## Solve

前置芝士：[斯坦纳树](https://oi-wiki.org/graph/steiner-tree/)。板子题。

### 定义

将指定点集合（部分点）中的所有点连通，且边权总和最小的生成树称为**最小斯坦纳树**。

### 求解

注意到 $k$ 的范围很小，一般考虑状压 dp。

令 $f(i,s)$（其中 $s$ 为二进制数）表示以 $i$ 号节点为生成树的根，与重要节点的连通性为 $s$ 时的最小代价。考虑状态转移。

- 不换根，$f(i,s)=\min\limits_{t\subseteq s}\{f(i,t)+f(i,\complement_st\}$。
- 换根（即再生成树中加入新节点 $j$ 并以其为根，要求 $i,j$ 相邻），$f(i,s)=\min\limits_{j\in adj(j)}{f(j,s)+w(i,j)}$。

发现换根的状态转移式与最短路的三角形不等式很相似，故可利用最短路算法进行状态转移。

对于不换根的状态转移，[子集枚举](https://oi-wiki.org/math/binary-set/#遍历所有掩码的子掩码)即可。

时间复杂度：$O(3^kn+2^k\times m\log_2n)$。

### 关于卡常

由于内存连续访问问题，开数组时建议把状态放第一维，实测会快一些。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=1e5+10,K=5,inf=1e18;
int n,k,m,f[1<<K][N];
typedef pair<int,int> PII;
vector<PII>e[N];
priority_queue<PII,vector<PII>,greater<PII>>q;
inline void dij(int s)//对于状态 s 跑最短路
{
	while(!q.empty())
	{
		int u=q.top().second,d=q.top().first;q.pop();
		if(d>f[s][u])	continue;
		for(PII i:e[u])
			if(f[s][i.first]>d+i.second)
				q.push({f[s][i.first]=d+i.second,i.first});
	}
}
signed main()
{
	n=read();k=read();m=read();
	for(int s=0;s<(1<<k);s=-~s)
		for(int i=1;i<=n;i=-~i)	f[s][i]=inf;
	for(int i=0;i<k;i=-~i)	f[1<<i][read()]=0;//初始状态，重要节点与自己联通的代价为0
	for(int i=1,u,v,w;i<=m;i=-~i)
		u=read(),v=read(),w=read(),
		e[u].push_back({v,w}),e[v].push_back({u,w});
	for(int s=0;s<(1<<k);s=-~s)
	{
		for(int t=s;t;t=(t-1)&s)//子集枚举
			for(int i=1;i<=n;i=-~i)
				f[s][i]=min(f[s][i],f[t][i]+f[s^t][i]);//异或即为补集
		for(int i=1;i<=n;i=-~i)
			if(f[s][i]!=inf)	q.push({f[s][i],i});//将 可以使得连通性为s 的点放入队列，跑多源最短路
		dij(s);
	}
	return printf("%lld",*min_element(f[(1<<k)-1]+1,f[(1<<k)-1]+n+1)/*找最小值*/),0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

题外话：[双倍经验](https://www.luogu.com.cn/problem/P6192)。（从这里也可以看出它实质上就是斯坦纳树板题。）
### 题意
在 Byteland 有 $n$ 个城市，并且其中有 $k$ 个国王经常来访的主要城市。

其中有 $m$ 条道路，每条道路连接两个城市。然而不幸的是，这些道路的环境极差使得国王无法全速驶过。

对于每条道路，第 $i$ 条道路翻修的成本是 $c_i$。你的任务是选择性的翻修道路使得 $k$ 个主要城市都可以经过翻修后的道路互相连通，且总成本尽量小。

数据范围：$1 \leq c_i \leq 10^9\, ,1 \le k \le \min(n,5) \, ,1 \le n \le 10^5 \, ,1 \le m \le 2 \times 10^5$。      
### 思路
城市和道路可以看做是一张图，选择道路翻修可以看做构造生成树，$k$ 个主要城市可以看做关键点。    
把我们选中的边放在一起，就组成了一棵斯坦纳树。   
我们使用动态规划来求最小斯坦纳树的权值和，设 $f_{i,j}$ 表示以第 $i$ 个点为根，关键点连通情况为 $j$ 的最小权值和。         
这里的 $j$ 指的是：如果第 $i$ 个关键点在这个状态中被连通了，那么 $j$ 这个数从低到高的第 $i$ 位为 $1$，否则为 $0$。
![](https://cdn.luogu.com.cn/upload/image_hosting/yuc8dg4l.png)     
那么接下来分 $2$ 种情况进行分类讨论：

1. 把以同一个点为根的两种状态合并，新状态的权值和为两个状态的权值和之和。即设根节点为 $i$，母状态为 $s$，子状态为 $t$，则 $f_{i,s}=f_{i,t}+f_{i,s-t}$。   
这里我们需要枚举子集，这里有一个很妙的小方法：设一个表示集合的二进制数 $s$ 的一个子集的二进制表示为 $t$，则下一个子集的二进制表示为 $s$ 与 $t-1$ 进行与操作之后的值。这样转移的复杂度是 $3^k$，共有 $n$ 个点，所以这一部分的复杂度为 $O(n \times 3^k)$。      

2. 在一个限定的状态中，进行边的松弛，则新状态的权值和为孩子节点的权值和加上两个点之间的边权。即设根节点为 $u$，孩子节点为 $v$，边权为 $w$，则 $f_u=f_v+w$。  
这个方程很像最短路里面的转移式子，所以可以考虑用最短路的思想转移。但这道题卡 SPFA，必须要用堆优化 Dijkstra。单次松弛时间复杂度为 $O((n+m) \log n)$，枚举集合的复杂度为 $O(2^k)$，所以这一部分的总复杂度为 $O((n+m) \log n \times 2^k)$。    

综上，我们可以完成动态规划的状态转移，时间复杂度为 $O(n \times 3^k+(n+m) \log n \times 2^k)$。最终的答案为 $f_{u,2^k-1}$，其中 $u$ 为任意一个关键点，$2^k-1$ 表示每个关键点都被连通。
### 代码
注意 $f$  数组的初始化。
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;
struct sss{int end,nxt,quan;}bian[400005];bool ff[100005];
int n,m,k,a,b,c,s,fir[100005],num,point;long long f[100005][35];
struct node
{
    int whe;
    bool operator <(const node &xxx)const
    {return f[whe][s]>f[xxx.whe][s]||whe==s&&whe>xxx.whe;}
};
priority_queue<node>dij;
int main()
{
    scanf("%d%d%d",&n,&k,&m),memset(f,0x3f3f3f,sizeof(f));
    for(int i=1;i<=k;i++) scanf("%d",&point),f[point][1<<(i-1)]=0;
    for(int i=1;i<=m;i++) scanf("%d%d%d",&a,&b,&c),
    bian[++num].end=b,bian[num].nxt=fir[a],bian[num].quan=c,fir[a]=num,
    bian[++num].end=a,bian[num].nxt=fir[b],bian[num].quan=c,fir[b]=num;
    for(s=1;s<(1<<k);s++)
    {
        for(int i=1;i<=n;i++) 
        {
            for(int t=s&(s-1);t;t=(t-1)&s) if(f[i][s]>f[i][t]+f[i][s^t]) f[i][s]=f[i][t]+f[i][s^t];
            if(f[i][s]!=f[0][0]) ff[i]=1,dij.push((node){i});
        }
        while(!dij.empty())
        {
            node who=dij.top();dij.pop(),ff[who.whe]=0;
            for(int i=fir[who.whe];i;i=bian[i].nxt)
            if(f[bian[i].end][s]>f[who.whe][s]+bian[i].quan)
            {
                f[bian[i].end][s]=f[who.whe][s]+bian[i].quan;
                if(!ff[bian[i].end]) dij.push((node){bian[i].end}),ff[bian[i].end]=1;
            }
        }
    }
    printf("%lld",f[point][(1<<k)-1]);
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一张 $n$ 个点 $m$ 条边的无向图，边有正边权。指定 $k$ 个点，求这 $k$ 点两两可达的情况下选择的边边权和的最小值。

## 解法

边权非负，显然最终选择的边组成一棵树，否则去掉环上一条边后答案更优且不影响连通性。于是本题转化为最小斯坦纳树的模板题，纯粹的模板题在[这里](https://www.luogu.com.cn/problem/P6192)。特别地，MST 则可以认为是将所有 $n$ 个点连通的最小斯坦纳树。

可以发现 $k$ 很小，可以容得下带 $2^k$ 的时空复杂度。考虑使用状态压缩 dp，设 $f_{i,j}$ 表示以 $i$ 为根，$k$ 个点的包含信息为 $j$（$j$ 二进制下第 $x$ 位为 $1$ 则 $k$ 个点中第 $x$ 个点被包含）时的答案。初始皆为 $+\infty$，对于 $k$ 中的每个点 $u$，$f_{u,2^{u-1}}\gets0$，即连通自己不需要连其他边。

假设当前 $k$ 个点中包含的点集为 $S$，对于第 $i$ 个点，分两种情况转移：

- 如果 $i$ 的度数大于 $1$，考虑从当前状态的子集和补集进行转移，即对于一个被 $S$ 包含的 $T$，$f_{i,S}\gets\min(f_{i,S},f_{i,T}+f_{i,S\backslash T})$。
- 如果 $i$ 的度数等于 $1$，考虑从与 $i$ 相邻的点 $j$ 转移，$f_{i,S}\gets\min(f_{i,S},f_{j,S}+w(i,j))$，其中 $w(i,j)$ 表示 $(i,j)$ 这条边的边权。

前者直接循环计算，后者可以用类似于最短路的松弛操作计算。

## 实现

对于第一种情况，因为我们按照二进制思想压缩状态，所以对于状态 $S$，其最大的子集 $T$ 为 $S\operatorname{and}(S-1)$，其中 $\operatorname{and}$ 表示按位与；在 $T$ 之后的下一个 $S$ 的子集即为 $(T-1)\operatorname{and}S$；$T$ 在 $S$ 中的补集即为 $S\operatorname{xor}T$，其中 $\operatorname{xor}$ 表示按位异或。

对于每一个枚举的状态 $S$，如果在第一种情况的转移完成后，$f_{u,S}$ 有值，则 $u$ 就可以作为第二种情况的一个起点。每一轮都以这些有值的点为可能的起点跑最短路即可。

最后在 $k$ 个点中随意挑一个点 $u$，答案即为 $f_{u,2^k-1}$。时间复杂度 $O(3^kn+m\log n\times2^k)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define mk make_pair
#define ll long long
using namespace std;
const int maxn = 1e5 + 5,maxk = 5;
int n,m,k,im[maxn];
ll f[maxn][(1 << maxk) + 5];
vector<pair<int,ll> > mp[maxn];
void addEdge(int u,int v,ll w) {
	mp[u].push_back(mk(v,w));
}
priority_queue<pair<ll,int> > q;
bool vis[maxn];
void Dijkstra(int now) {
	memset(vis,false,sizeof(vis));
	while (!q.empty()) {
		int u = q.top().second; q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (auto V : mp[u]) {
			int v = V.first; ll w = V.second;
			if (f[v][now] > f[u][now] + w) {
				f[v][now] = f[u][now] + w;
				if (!vis[v]) 
					q.push(mk(-f[v][now],v));
			}
		}
	}
}
int main() {
	scanf("%d%d%d",&n,&k,&m); ll w;
	for (int i = 1;i <= n;i ++)
		for (int s = 0;s <= (1 << k) - 1;s ++)
			f[i][s] = 1e18;
	for (int i = 1;i <= k;i ++) {
		scanf("%d",&im[i]);
		f[im[i]][1 << (i - 1)] = 0;
	}
	for (int i = 1,u,v;i <= m;i ++) {
		scanf("%d%d%lld",&u,&v,&w);
		addEdge(u,v,w); addEdge(v,u,w);
	}
	for (int s = 0;s <= (1 << k) - 1;s ++) {
		for (int i = 1;i <= n;i ++) {
			for (int t = s & (s - 1);t;t = (t - 1) & s)
				f[i][s] = min(f[i][s],f[i][t] + f[i][s ^ t]);
			if (f[i][s] < 1e18) q.push(mk(-f[i][s],i));
		}
		Dijkstra(s);
	}
	printf("%lld",f[im[1]][(1 << k) - 1]);
	return 0;
}
```

---

## 作者：yinqy (赞：0)

### 相关题目

[P6192 【模板】最小斯坦纳树](https://www.luogu.com.cn/problem/P6192)

[P4294 [WC2008] 游览计划](https://www.luogu.com.cn/problem/P4294)

------

### 题意解释

说人话环节：给定一个无向图，求把 $k$ 个节点联通的最小代价（$k \leq 5$）。

这就是最小斯坦纳树（最小树的一般版），给定连通图 $G$ 中的 $n$ 个点与 $k$ 个关键点，连接 $k$ 个关键点，使得生成树的所有边的权值和最小。

### 思路

结合 [斯坦纳树 - OI Wiki](https://oi-wiki.org/graph/steiner-tree/) 中的知识，我们可以知道直接连接这 $k$ 个关键点生成的权值和不一定是最小的，或者这 $k$ 个关键点不会直接（相邻）连接。所以应当使用剩下的 $n-k$ 个点。

而这时我们可以使用**状压 DP** 来求解。用 $f(i,S)$ 表示以 $i$ 为根的一棵树，包含集合 $S$ 中所有点的最小边权值和。

考虑状态转移：

- 首先对连通的子集进行转移，$f(i,S)\leftarrow \min(f(i,S),f(i,T)+f(i,S-T))$。
- 在当前的子集连通状态下进行边的松弛操作，$f(i,S)\leftarrow \min(f(i,S),f(j,S)+w(j,i))$。

松弛操作的表达式与最短路模型的三角形不等式相似，所以对于每个 $S$，将图跑一次最短路即可。

总时间复杂度为 $O(n\times 3^k + m\log(m) \times 2^k)$。

**注意**：不开 longlong 和 O2 会喜提 WA 和 TLE 的大礼包哟。
### Code

```cpp
#include<bits/stdc++.h>
#define ri register int
#define rll register long long
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,int> P;
const ll INF=0x3f3f3f3f3f3f3f3f;
const int N=1e5+10, M=4e5+10;
int n,m,k;
struct graph{
    int to,Next,edge;
}e[M];
int head[N],tot;
int a[6];
ll f[N][40];bitset<N>vis;
priority_queue<P, vector<P>, greater<P> > q;

template<typename T>inline void read(T &x){
    char ch=getchar();int fx=0;x=0;
    for( ;!isdigit(ch);ch=getchar()) fx|=(ch=='-');
    for( ;isdigit(ch);ch=getchar()) x=x*10+(ch-'0');
    x=(fx?-x:x);
}
template<typename T>inline void write(T x){
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10^'0');
}

inline void add(int x, int y, int z){
    e[++tot]={y,head[x],z};
    head[x]=tot;
}

void dijkstra(int s){
    vis.reset();
    while(!q.empty()){
        int u=q.top().second; q.pop();
        if(vis[u]) continue; vis[u]=1;
        for(ri i=head[u]; i;i=e[i].Next){
            int v=e[i].to;ll w=e[i].edge;
            if(f[v][s]>f[u][s]+w){
                f[v][s]=f[u][s]+w;
                q.push({f[v][s],v});
            }
        }
    }
}

int main(){
    read(n), read(k), read(m);
    memset(f,INF,sizeof f);
    for(ri i=1;i<=k;i++)
        read(a[i]), f[a[i]][1<<(i-1)]=0;
    for(ri i=1,u,v,w;i<=m;i++){
        read(u), read(v), read(w);
        add(u,v,w), add(v,u,w);
    }
    for(ri s=1;s<(1<<k);s++){
        for(ri i=1;i<=n;i++){
            for(ri j=s&(s-1); j;j=s&(j-1))// 遍历子图
                f[i][s]=min(f[i][s],f[i][j]+f[i][s^j]);
            if(f[i][s]!=INF) q.push({f[i][s],i});
        }
        dijkstra(s);
    }
    ll ans=INF;
    for(ri i=1;i<=n;i++) ans=min(ans,f[i][(1<<k)-1]);
    write(ans), cout<<'\n';
    return 0;
}
```


---

