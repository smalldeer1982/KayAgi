# [ABC325E] Our clients, please wait a moment

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc325/tasks/abc325_e

ある国には都市が $ N $ 個あります。  
あなたは、都市 $ 1 $ にある営業所から $ 0 $ 個以上の都市を経由して都市 $ N $ にある訪問先へ移動しようとしています。  
移動手段は社用車と電車の $ 2 $ 種類があります。都市 $ i $ から都市 $ j $ へ移動するときの所要時間は以下の通りです。

- 社用車を使った場合 : $ D_{i,j}\ \times\ A $ 分
- 電車を使った場合 : $ D_{i,j}\ \times\ B\ +\ C $ 分

ただし、社用車から電車に乗り換えることはできますが、電車から社用車に乗り換えることはできません。  
また、乗り換えは各都市のみで行え、乗り換えに時間はかかりません。

都市 $ 1 $ から都市 $ N $ に移動するのにかかる時間は最短で何分ですか？

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ A,\ B,\ C\ \leq\ 10^6 $
- $ D_{i,j}\ \leq\ 10^6 $
- $ D_{i,i}\ =\ 0 $
- $ D_{i,j}\ =\ D_{j,i}\ >\ 0 $ $ (i\ \neq\ j) $
- 入力される数値はすべて整数

### Sample Explanation 1

以下のように移動することで合計 $ 78 $ 分で都市 $ 1 $ から都市 $ 4 $ に移動することができます。 - 都市 $ 1 $ から都市 $ 3 $ まで社用車で移動する。この移動には $ 2\ \times\ 8\ =\ 16 $ 分かかる。 - 都市 $ 3 $ から都市 $ 2 $ まで社用車で移動する。この移動には $ 3\ \times\ 8\ =\ 24 $ 分かかる。 - 都市 $ 2 $ から都市 $ 4 $ まで電車で移動する。この移動には $ 5\ \times\ 5\ +\ 13\ =\ 38 $ 分かかる。 $ 78 $ 分未満の時間で都市 $ 1 $ から都市 $ 4 $ に移動することはできません。

## 样例 #1

### 输入

```
4 8 5 13
0 6 2 15
6 0 3 5
2 3 0 13
15 5 13 0```

### 输出

```
78```

## 样例 #2

### 输入

```
3 1 1000000 1000000
0 10 1
10 0 10
1 10 0```

### 输出

```
1```

## 样例 #3

### 输入

```
5 954257 954213 814214
0 84251 214529 10017 373342
84251 0 91926 32336 164457
214529 91926 0 108914 57762
10017 32336 108914 0 234705
373342 164457 57762 234705 0```

### 输出

```
168604826785```

# 题解

## 作者：CultReborn (赞：8)

[原题链接](https://atcoder.jp/contests/abc325/tasks/abc325_e)、[洛谷题面](https://www.luogu.com.cn/problem/AT_abc325_e)


[更好的阅读体验](https://www.cnblogs.com/CultReborn/articles/-ABC325E-Our-clients-please-wait-a-moment-fencentu-zuiduanlu-dijkstra-tijie.html)

# 题意

一个国家有 $n$ 个城市，可以看做一个无向连通图。   
你有坐车和坐火车两种通行方式，对于从城市 $i$ 到城市 $j$：

+ 坐汽车会花费 $D_{i,j} \times A$ 分钟
+ 坐火车会花费 $D_{i,j} \times B+C$ 分钟

给出 $n,A,B,C$，以及表示道路的邻接表，求从 $1$ 号城市旅行到 $n$ 号城市的最短路。**途中可以从坐汽车转换成做火车，但不能从坐火车转换成坐汽车。**

# 思路
很容易看出来需要无脑套最短路算法。（你能来切题一定会 Dijkstra 吧！）

至于怎么处理汽车与火车的换乘，我们需要建立一个分层图。（分层图是最短路的一大应用，你一定会吧！）

分层图共有两层：

+ 第一层有节点 $1$ 到 $n$。连通 $i$ 与 $j$ 的边权为乘坐汽车会花费的时间，即 $D_{i,j} \times A$。

+ 第二层有节点 $1 + n$ 到 $n + n$。连通 $i + n$ 与 $j + n$ 的边权为乘坐火车会花费的时间，即 $D_{i,j} \times B+C$。 

+ 两层之间对应的节点，如 $i$ 与 $i + n$ 之间，用边权为 $0$ 的单向边连起来，表示从汽车换乘火车。其中边权为 $0$ 是因为换乘没有代价，单向边是因为我们只能从汽车换乘到火车。

+ 最终答案就是 $1$ 号节点到 $n + n$ 号节点的最短路。

可以配下图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/jx91k0tz.png)

# 代码

[AC 记录](https://atcoder.jp/contests/abc325/submissions/46917321)


```cpp
#include<bits/stdc++.h>
#define RG register
#define IL inline
#define int long long //我很懒，但是别忘记开！
using namespace std;
const int maxn = 2003;
const int maxm = 3000006; //有分层，别开小了
IL int Read();
int n,A,B,C,head[maxm],cnt;
int dis[maxn]; bool vis[maxn];
priority_queue<pair<int,int> > q;
struct node{
	int to,nxt,cst;
}edge[maxm];
void Input(int u,int v,int w){
	edge[cnt] = {v,head[u],w};
	head[u] = cnt++; //邻接表改为链式前向星存图
}
void Dijkstra(int s){ //最短路板子，SPFA 死了
	q.push({0,s}); dis[s] = 0;
	while(!q.empty()){
		int u = q.top().second; q.pop();
		if(vis[u]) continue; vis[u] = 1;
		for(int i = head[u];~i;i = edge[i].nxt){
			int v = edge[i].to,w = edge[i].cst;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				q.push({-dis[v],v});
			}
		}
	}
}
signed main(){
	memset(head,-1,sizeof(head));
	memset(dis,0x3f,sizeof(dis));
	n = Read(); A = Read();
	B = Read(); C = Read();
	for(int i = 1;i <= n;++i){
		for(int j = 1;j <= n;++j){
			int x = Read();
			if(i == j) continue;
			Input(i,j,x * A); 
            //第一层汽车
			Input(i,i + n,0); 
            //两层之间换乘
			Input(i + n,j + n,x * B + C); 
            //第二层火车
		}
	}
	Dijkstra(1);
	printf("%lld",dis[n + n]);
	return 0;
}
IL int Read(){ //快读
	char c(getchar());
	int x(0),f(1);
	while(c < '0' || c > '9'){
		if(c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x * f;
}
```
[![Page Views Count](https://badges.toozhao.com/badges/01HDJTM43N0WRRD12W9405KEDM/blue.svg)](https://badges.toozhao.com/stats/01HDJTM43N0WRRD12W9405KEDM "Get your own page views count badge on badges.toozhao.com")

2023.10.25 提交题解

2023.10.29 修改格式

求审核通过啦！

---

## 作者：osfly (赞：4)

### some interesting things:

CSP 考炸，心态崩了，所以来这里水题解排泄心情。

---
### 正文

考前都在复习分层图，但发现 tg 没考，反而是 pj 考了。有点郁闷。

很明显的分层图。

分两层，一层连汽车，一层连公交，边权都设为通过所需要的时间。

再对每一个点，把汽车连向公交，边权设为 $0$，单向边，这样就能保证只能从汽车转到公交。

时间复杂度 $O(n^2)$，很好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1100;

#define ll long long

struct edge
{
	int u,v;
	ll w;
	int nxt;
}e[N*N<<3];
int head[N<<1],tot;
void add(int u,int v,ll w)
{
	e[++tot]=edge{u,v,w,head[u]};
	head[u]=tot;
}

int n;
ll A,B,C;
ll dis[N<<1];
int vis[N<<1];

void dij()
{
	priority_queue<pair<ll,int> > q;
	q.push({0,1});
	memset(dis,0xf,sizeof(dis));
	dis[1]=0;
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v;
			ll w=e[i].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				if(!vis[v]) q.push({-dis[v],v});
			}
		}
	}
}

int main()
{
	scanf("%d%lld%lld%lld",&n,&A,&B,&C);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			ll d;
			scanf("%lld",&d);
			add(i,j,d*A),add(j,i,d*A);
			add(i+n,j+n,d*B+C),add(j+n,i+n,d*B+C);
			add(i,j+n,d*B+C);
		}
	for(int i=1;i<=n;i++) add(i,i+n,0);
	dij();
	printf("%lld",dis[n<<1]);
	return 0;
}
```

---

## 作者：linxuanrui (赞：3)

### 思路

用两个 Floyd。

设 $f_{i,j,0}$ 为从 $i$ 坐车到 $j$ 的最小开销，$f_{i,j,1}$ 为从 $i$ 坐高铁到 $j$ 的最小开销。

然后根据 Floyd 的状态转移方程转移即可。

最后的答案就是 $\min\limits_{i=1}^n f_{1,i,0}+f_{i,n,1}$。

### 代码

可以说是最劣解了吧。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
typedef long long ll;
using namespace std;
const int N = 1005;
int n,a,b,c,d[N][N],f[N][N][2],ans = LLONG_MAX;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> a >> b >> c;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++)cin >> d[i][j];
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++)f[i][j][0] = d[i][j] * a,f[i][j][1] = d[i][j] * b + c;
	}
	for(int i = 1;i <= n;i++)f[i][i][0] = f[i][i][1] = 0;
	for(int k = 1;k <= n;k++){
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				f[i][j][0] = min(f[i][j][0],f[i][k][0] + f[k][j][0]);
				f[i][j][1] = min(f[i][j][1],f[i][k][1] + f[k][j][1]);
			}
		}
	}
	for(int i = 1;i <= n;i++)ans = min(ans,f[1][i][0] + f[i][n][1]);
	cout << ans;
}
```

---

## 作者：SnapYust (赞：2)

# 题目传送门

[ABC235E](https://www.luogu.com.cn/problem/AT_abc325_e)

# 思路

史上最简单 E？

我们发现一个重要性质：

``ただし、社用車から電車に乗り換えることはできますが、電車から社用車に乗り換えることはできません.``

即我们可以从公司的车换到电车，但不能从电车换到公司的车。

带个套路，我们设 $dis1_S$ 为从第 $1$ 站坐公司车到第 $S$ 的站点用的最短时间，设 $dis2_S$ 为从第 $S$ 站坐电车到第 $N$ 站用的最短时间。

那么：

$$ans=\min dis1_K+dis2_K(1\le K\le N)$$

接下来，我们就是处理最短路，我们记 $d1_{i,j}=d_{i,j}\times A,d2_{i,j}=d_{i,j}\times B+C$，然后对着 $d1,d2$ 跑最短路即可，记得 $d2$ 的源点是 $N$。

# Code

代码短简，不放。

---

## 作者：BugGod (赞：1)

最短路板子题，个人认为还不如 D。由于只能换乘一次，我们可以开两个图，一个存坐车，另一个存火车。我们可以最短路算出不换乘的代价，然后与换乘的情况去较小值，我们可以枚举换乘点，对于每个点 $i$，求出坐车的 $dist_{1,i}$，再加上坐火车的 $dist_{i,n}$，取最小值即可。

---

## 作者：forever_nope (赞：1)

Date 20231024：请注意原题未说明清楚的，是走到的每一条边，都需要按照给出的公式计算。

这里介绍两种算法：「最短路＋枚举」以及「分层图最短路」。

### Solution 1：最短路＋枚举

注意到，$n\le1000$，那么我们就可以 $\mathcal{O}(n)$ 的枚举「在哪一个城市换成火车」。

特别的，如果在 $1$ 号城市换乘火车，说明没有乘坐汽车；如果在 $n$ 号城市换成火车，则说明没用乘坐火车。

也就是将一条路径 $1\rightarrow k_1\rightarrow k_2\rightarrow\cdots\rightarrow n$，分为两条路径，前面的部分乘汽车，后面的部分乘火车。

注意：原图是**无负边权**稠密图，因为 $m=\frac{n(n-1)}{2}$，所以最好使用「朴素版 Dijkstra」。但是我不会写，所以顺手写了一个「堆优化 Dijkstra」。

Dijkstra 算法：求解单元最短路，即从 **原点** 出发，到其他所有点的最短距离；适用于 **没有负权边**，即所有边的长度都是正数。

思路：设集合 $S$ 为已经求解出最短路的点集，从原点出发，每次选一个距离这个点集最近的点，加入点集 $S$，并用这个点更新所有与它有直接连边的点。

代码：<https://atcoder.jp/contests/abc325/submissions/46895951>

### Solution 2：分层图最短路

只有一次换乘的机会，所以我们可以跑分层图最短路。

建两层图，每一层都有 $n$ 个点（可以形象的理解为「第一层是在汽车站，第二层是在火车站」）。

注意：分层图最短路，一般来说第 $i$ 层的编号从 $n\times(i-1)+1$ 开始编号，即第 $1$ 层从 $1$ 开始，第 $2$ 层从 $n+1$ 开始。

除了初始在两层图上独立的边 $(u,v)$、$(u+n,v+n)$，然后额外连边 $(i,i+n)$，即从第一层的点 $i$ 连到第二层的点 $i+n$，边权为 $0$（表示「从汽车站到火车站不需要花费时间」，~~题目给出，说明出题人可以瞬移~~）。

然后就可以从 $1$ 号点开始跑「最短路」，然后结果取 $\min\{\mathit{dis}(n),\mathit{dis}(2n)\}$；然而这道题上下两层图之间的边权为 $0$，所以直接取任意一个点的 $\mathit{dis}$ 即可。

代码：<https://atcoder.jp/contests/abc325/submissions/46897682>


---

## 作者：__Allen_123__ (赞：0)

### 题意简述

有 $n$ 个节点，节点 $i$ 和节点 $j$ 的距离是 $D_{i,j}$，你可以选择以下两种方案从节点 $i$ 到节点 $j$：

1. 花费 $D_{i,j}\times A$ 分钟到达；
2. 花费 $D_{i,j}\times B+C$ 分钟到达。

注意，当你第一次选择方案 $2$ 后，你不能再选择方案 $1$。

请你求出从节点 $1$ 到节点 $n$ 所用的最小时间。

### 题目分析

最短路变式题。

我们令没有执行方案 $2$，到节点 $i$ 的最小时间为 $dis_{i,0}$，执行方案 $2$ 后的最小时间为 $dis_{i,1}$，这里利用了类似 dp 的思想。

每次跑最短路时，如果当前被选中的点已经执行了方案 $2$，那么我们只能向 $dis_{i,1}$ 延伸；如果没有，则既可以向 $dis_{i,0}$ 延伸，又可以向 $dis_{i,1}$ 延伸。

最终的答案就是 $\min\{dis_{n,0},dis_{n,1}\}$。注意在本题中，dij 需要跑 $2n$ 次。

[AC 记录](https://atcoder.jp/contests/abc325/submissions/47054243)

---

## 作者：1234567890sjx (赞：0)

这个题比 `D` 题简单多啦！

因为只能从坐车切换到坐火车，所以考虑用分层图跑最短路。

建立 $G_0$ 和 $G_1$ 两张图，对于一条 $x\to y$ 的边同时加在 $G_0$ 和 $G_1$ 两张图上。

由于可以在任意时刻任意地点从坐车（$G_0$）免费不用时切换到坐火车（$G_1$），所以对于每一个点 $i$，建立一条 $G_0$ 向 $G_1$，边权为 $0$ 的**有向**边。

起点是 $G_0$ 图中的 $1$ 号点。

终点是 $G_1$ 图中的 $n$ 号点。

直接跑 `Dijkstra` 求最短路即可。时间复杂度是 $O(n^2\log n^2)$ 的，有点卡常。

如果采用不优化的 `Dijkstra` 算法，时间复杂度是 $O(n^2)$ 的，随便冲。

好奇的问一嘴：分层图不是绿的吗，为什么这个题是黄啊。


---

## 作者：BYR_KKK (赞：0)

[Here](https://www.luogu.com.cn/problem/AT_abc325_e)

# 思路

考虑采用 dij 的思路，每次选择花费最少且未被访问的一个点，用它来更新其它点，最后的答案就是到终点的两种方式的最小值。

# code

```cpp

#include<bits/stdc++.h>
#define int long long

const int maxn=1010;

int d[maxn][maxn],dp[maxn][2];//dp[i][0]与dp[i][1]分别表示从 1 到 i 的两种方式 

bool vis[maxn];//标记是否访问 

signed main(){
	int n,a,b,c;
	std::cin>>n>>a>>b>>c;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) std::cin>>d[i][j];
	memset(dp,0x7f,sizeof(dp));
	dp[1][0]=dp[1][1]=0;
	int nowmin=1,minf=(int)1e18,mins=(int)1e18;
	vis[1]=1;
	for(int j=1;j<=n;j++){//暴力找最小点 ，顺便更新其它点 
		int znowmin;
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				dp[i][0]=std::min(dp[i][0],dp[nowmin][0]+d[nowmin][i]*a);
				dp[i][1]=std::min(dp[i][1],std::min(dp[nowmin][0]+d[nowmin][i]*b+c,dp[nowmin][1]+d[nowmin][i]*b+c));
				if(minf>=dp[i][0]&&mins>=dp[i][1]) minf=dp[i][0],mins=dp[i][1],znowmin=i;
			}
			dp[i][0]=std::min(dp[i][0],dp[nowmin][0]+d[nowmin][i]*a);
			dp[i][1]=std::min(dp[i][1],std::min(dp[nowmin][0]+d[nowmin][i]*b+c,dp[nowmin][1]+d[nowmin][i]*b+c));
		}
		nowmin=znowmin;
		vis[nowmin]=1;
		minf=mins=(int)1e18;
	}
	std::cout<<std::min(dp[n][0],dp[n][1]);
	return 0;
}

```

---

## 作者：FireRain (赞：0)

# 思路

定义 $d_{0/1,i,j}$ 表示从 $i$ 到 $j$ 只坐 车/火车 最少需要花的时间。

那么枚举一个中转点 $i$ 表示在 $1 \to i$ 坐车，$i \to n$ 坐火车。那么答案为：

$$
\min\{d_{0,1,i} + d_{1,i,n}\}
$$

显然对于 $d_0$ 我们只需要求出 $d_{0,1,i}$，正常跑一遍 Dijkstra 即可；对于 $d_1$ 只需求出 $d_{1,i,n}$，只需建一个反图，再跑一个 Dijkstra 即可。

# code

```cpp
#include <bits/stdc++.h>
#define fst first
#define snd second
#define re register
#define int long long

using namespace std;

typedef pair<int,int> pii;
const int N = 1010,M = 1e6 + 10,inf = 0x3f3f3f3f3f3f3f3f;
int n,a,b,c,ans = inf;

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}


struct edge{
	int idx,h[N],ne[M],e[M],w[M],d[N];
	bool vis[N];
	
	edge(){
		memset(h,-1,sizeof(h));
		memset(d,inf,sizeof(d));
	}
	
	inline void add(int a,int b,int c){
		ne[idx] = h[a];
		e[idx] = b;
		w[idx] = c;
		h[a] = idx++;
	}
	
	inline void dijkstra(int s){
		priority_queue<pii,vector<pii>,greater<pii>> q;
		d[s] = 0;
		q.push({0,s});
		while (!q.empty()){
			pii t = q.top();
			q.pop();
			if (vis[t.snd]) continue;
			vis[t.snd] = true;
			for (re int i = h[t.snd];~i;i = ne[i]){
				int j = e[i];
				if (d[j] > t.fst + w[i]){
					d[j] = t.fst + w[i];
					q.push({d[j],j});
				}
			}
		}
	}
}g[2];

signed main(){
	n = read();
	a = read();
	b = read();
	c = read();
	for (re int i = 1;i <= n;i++){
		for (re int j = 1;j <= n;j++){
			int x;
			x = read();
			g[0].add(i,j,x * a);
			g[1].add(j,i,x * b + c);
		}
	}
	g[0].dijkstra(1);
	g[1].dijkstra(n);
	for (re int i = 1;i <= n;i++) ans = min(ans,g[0].d[i] + g[1].d[i]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：jr_inf (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc325_e)

最短路板题。

乘坐的过程一定是先车再火车（如果有），假设换车地点为 $x$，那么最小代价为坐车从 $1$ 到 $x$ 与坐火车从 $x$ 到 $n$ 的最小代价之和，分开跑最短路即可，时间复杂度 $O(n^2\log n+n)$。

code:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
#define int long long
using namespace std;
const long long linf=9223372036854775807;
const int N=1000+10;
int n,a,b,c,dist[N][N],lst[N],d1[N],d2[N],ans=linf;
bool vis[N];
struct node{int v,w;};
vector<node> g[N];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
void dij(int x)
{
	memset(vis,0,sizeof(vis));
	q.push(make_pair(0,x));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int v=1;v<=n;v++)
		{
			if(u==v)continue;
			int w=(x==1?dist[u][v]*a:dist[u][v]*b+c);
			if(x==1&&d1[v]>d1[u]+w)
			{
				d1[v]=d1[u]+w;
				q.push(make_pair(d1[v],v));
			}
			if(x==n&&d2[v]>d2[u]+w)
			{
				d2[v]=d2[u]+w;
				q.push(make_pair(d2[v],v));
			}
		}
	}
}
signed main()
{
	scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
	memset(d1,127,sizeof(d1));
	memset(d2,127,sizeof(d2));
	d1[1]=0;
	d2[n]=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%lld",&dist[i][j]);
	dij(1),dij(n);
	for(int i=1;i<=n;i++)ans=min(ans,d1[i]+d2[i]);
	printf("%lld",ans);
}
```


---

## 作者：FL_sleake (赞：0)

### 题意简述

有 $n$ 个城市和三个参数 $A,B,C$。给定一个 $n\times n$ 的矩阵 $D$。从城市 $i$ 到 $j$ 有两种方式，坐车花费 $D_{i,j}\times A$ 时间，坐高铁花费 $D_{i,j}\times B + C$ 时间。一开始可以自由选择坐车还是坐高铁，但是如果某次选择坐高铁了，那么之后你只能选择坐高铁。

### 解题思路

感觉很典啊。建一个分层图跑 dijkstra 就可以了。第一个图 $G1$ 全部以坐车需要的时间为边权，第二个图 $G2$ 全部以坐高铁需要的时间为边权。因为坐车可以转坐高铁，所以 $G1$ 中每个点向 $G2$ 中对应的点连一条边权为 $0$ 的边就好了。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,A,B,C;
int a[1010][1010];
struct node{
	int v,w;
	bool operator<(const node &b)const{
		return w>b.w;
	}
};
vector<node> G[200010];
int dis[200010];
void Dijkstra(){
	dis[1]=0;
	priority_queue<node> q;
	q.push({1,0});
	while(!q.empty()){
		int u=q.top().v;
		q.pop();
		for(auto x:G[u]){
			int v=x.v,w=x.w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({v,dis[v]});
			}
		}
	}
}
signed main(){
	memset(dis,0x3f,sizeof(dis));
	cin>>n>>A>>B>>C;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			G[i].push_back({i+n,0});
			G[i].push_back({j,A*a[i][j]});
			G[i+n].push_back({j+n,B*a[i][j]+C});
		}
	}
	Dijkstra();
	cout<<min(dis[n],dis[n+n])<<endl;
	return 0;
}
```

---

## 作者：_Ink (赞：0)

## 题解

最短路板子练习题。

观察到题目有一个性质：**可以从公司汽车换乘火车，但不能反之。** 也就是说我能在某个点选择换乘，换乘之前都是坐汽车，换乘后都是坐火车。

于是这题就很显然了。有 2 种解决方法：

第一种做法：正反跑两遍最短路。计算出从 $1$ 出发，只坐汽车到每个点的最短距离 $disa$；计算从 $n$ 出发，只坐火车到每个点的最短距离 $disb$。于是枚举每个点作为换乘点，取 $disa+disb$ 的最小值即可。 即 $ans=\sum_{i=1}^n \min(disa_i+disb_i)$。

第二种做法：分层图。把只坐汽车和只坐火车分别建两个图，记为 $a$ 图和 $b$ 图。然后把 $a$ 图的每个节点建立一条指向 $b$ 图中对应的点的有向边，边权为 $0$。然后在这个图里跑一遍最短路即可。

第二种做法其实相对更优雅一点，因为只用跑一次最短路。

$n$ 的范围 $[2,1000]$ 可以说非常之小了，随便跑跑都能过。要注意的是存的距离和答案可能会爆 int，所以记得开 long long。

## $\text{Code:}$

这里我用的第一种做法，最短路写的 dijkstra。

```cpp
#include<bits/stdc++.h>
#define maxn 1050
#define maxm 500050 
#define endl '\n'
#define ll long long
using namespace std;

const ll llinf = 999999999999999;

int n, a, b, c; 
ll d[maxn][maxn];
ll disa[maxn], disb[maxn];
bool visa[maxn], visb[maxn];
priority_queue <pair<ll, int> > q;
ll ans = llinf;

void dija(int s)
{
	q.push(make_pair(0, s));
	disa[s] = 0;
	while(q.size())
	{
		int x = q.top().second; q.pop();
		visa[x] = true;
		for(int i = 1; i <= n; i ++)
		{
			if(visa[i]) continue;
			if(disa[x] + d[x][i] * a < disa[i])
			{
				disa[i] = disa[x] + d[x][i] * a;
				q.push(make_pair(-disa[i], i));
			}
		}
	}
}

void dijb(int s)
{
	q.push(make_pair(0, s));
	disb[s] = 0;
	while(q.size())
	{
		int x = q.top().second; q.pop();
		if(visb[x]) continue;
		visb[x] = true;
		for(int i = 1; i <= n; i ++)
		{
			if(disb[x] + d[x][i] * b + c < disb[i])
			{
				disb[i] = disb[x] + d[x][i] * b + c;
				q.push(make_pair(-disb[i], i));
			}
		}
	}
}

void run()
{
	cin >> n >> a >> b >> c;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			cin >> d[i][j];
	memset(disa, -llinf, sizeof(disa));	
	memset(disb, -llinf, sizeof(disb));	
	dija(1); dijb(n);
	for(int i = 1; i <= n; i ++)
		ans = min(disa[i] + disb[i], ans);
	cout << ans << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	int t = 1;
//	cin >> t; 
	while(t --) run();
	
	return 0;
}

```

---

## 作者：sunkuangzheng (赞：0)

最短路板子题。

把汽车、火车分开建图，相当于我们要找一个转折点 $k$，使得 $1 \to k$ 坐汽车，$k \to n$ 坐火车。由于是无向图，直接分别以 $1$ 和 $n$ 为原点跑最短路，枚举 $k$ 加起来。

时间复杂度 $\mathcal O(m \log m)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 21.10.2023 20:14:41
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1005;
namespace Dij{
    const int maxn = 5e5+5;
    int n,dis[maxn],vis[maxn];vector<pair<int,int>> g[maxn];
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    void init(int _n,vector<pair<int,int>> *_g){
        for(int i = 1;i <= n;i ++) g[i].clear();
        n = _n;
        for(int i = 1;i <= n;i ++) for(auto k : _g[i]) g[i].emplace_back(k);
    }void dijk(int s){
        for(int i = 1;i <= n;i ++) dis[i] = 1e18+7,vis[i] = 0;
        dis[s] = 0;q.push({0,s});
        while(q.size()){
            auto [acc,u] = q.top();q.pop();
            if(vis[u]) continue;vis[u] = 1;
            for(auto [v,w] : g[u]) if(dis[v] > dis[u] + w) dis[v] = dis[u] + w,q.push({dis[v],v});
        }
    }
}int t,n,a,b,c,x,d1[N],ans = 1e18;
vector<pair<int,int>> g1[N],g2[N];
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> a >> b >> c;
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= n;j ++)
        cin >> x,g1[i].emplace_back(j,x * a),g2[i].emplace_back(j,x * b + c);
    Dij::init(n,g1);
    Dij::dijk(1);
    for(int i = 1;i <= n;i ++) d1[i] = Dij::dis[i];
    Dij::init(n,g2),Dij::dijk(n);
    for(int i = 1;i <= n;i ++) ans = min(ans,d1[i] + Dij::dis[i]);
    cout << ans;
}
```

---

## 作者：Light_az (赞：0)

简化题意后发现，对于每条路径有两种距离，一种是坐车，一种是坐火车，当然你也可以选择先坐车，再在途中换乘火车，问从点 $1$ 到点 $n$ 的最短距离是多少。

显然我们设 $dp_i$ 为点 $1$ 到点 $i$ 只坐车的最短距离，$ans_i$ 代表点 $1$ 到点 $n$ 只坐火车或者先坐车再换乘火车后的最短距离，那么 $ans_i$ 可以通过其他点到达，而到达的方式有两种:

- 坐车换乘火车。

- 继续坐火车。

每次分类讨论，分别讨论从坐车换乘火车和继续坐火车两种情况，再次求一遍最短路处理 $ans_i$ 即可，代码注释中描述了剩余细节：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define ps push_back
#define sz(x) ((ll)x.size())
#define mem(f,x) memset(f,x,sizeof(f))
#define all(x) x.begin(),x.end()
#define lc id*2
#define rc id*2+1
#define V vector<ll>
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e4+10;
ll n,m,k,x,y,u,v,w,cnt,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
char ch;
ll dis[1005][1005],a,b,c;
ll dp[1005],vis[N],ans[1005];
struct Node{
	ll num,dis;
	friend bool operator <(const Node &a,const Node &b){
		return a.dis>b.dis;
	}
};
void init(){//预处理只坐车的最短路
	priority_queue<Node> q;
	F(i,2,n) dp[i]=1e18;//最短路预处理
	mem(vis,0);
	q.push({1,0});
	while(!q.empty()){//最短路
		Node p=q.top();
		q.pop();
		if(vis[p.num]) continue;
		vis[p.num]=1;
		F(i,1,n){
			if(dp[i]>dp[p.num]+dis[p.num][i]*a){//dis[p.num][i]*a 代表坐车的距离
				dp[i]=dp[p.num]+dis[p.num][i]*a;
				if(!vis[i]) q.push({i,dp[i]});
			}
		}
	}
}
void make(){
	priority_queue<Node> q;
	F(i,2,n) ans[i]=1e18;
	mem(vis,0);
	q.push({1,0});
	while(!q.empty()){//最短路
		Node p=q.top();
		q.pop();
		if(vis[p.num]) continue;
		vis[p.num]=1;
		F(i,1,n){
        //分类讨论
			if(ans[i]>ans[p.num]+dis[p.num][i]*b+c){//继续坐火车
				ans[i]=ans[p.num]+dis[p.num][i]*b+c;
				if(!vis[i]) q.push({i,ans[i]});
			}
			if(ans[i]>dp[p.num]+dis[p.num][i]*b+c){//从车换乘火车
				ans[i]=dp[p.num]+dis[p.num][i]*b+c;
				if(!vis[i]) q.push({i,ans[i]});
			}
		}
	}
}
int main(){
	cin>>n>>a>>b>>c;
	F(i,1,n) F(j,1,n) cin>>dis[i][j];
	init();
	make();
	cout<<min(dp[n],ans[n]);//特判不需要换乘
	return 0;
}

```


---

