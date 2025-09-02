# [APIO2023] 赛博乐园 / cyberland

## 题目背景

**由于部分 BUG，使用 C++14 (GCC9) 提交会产生编译错误，请使用 C++14 等语言进行提交。**

提交时，无需引用 `cyberland.h`。你提交的代码中需要实现以下函数：

```cpp
double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr)
```

## 题目描述

3742 年已经到来，现在轮到赛博乐园主办 APIO 了。在这个世界上有 $N$ 个国家，这些国家由 $0$ 到 $N − 1$ 标号，还有 $M$ 条双向道路（每条边双向都可以通行），这些道路由 $0$ 到 $M − 1$ 标号。每条道路连接两个不同的国家，$x[i]$ 和 $y[i]$，并需要花费时间 $c[i]$ 来通过该道路。除了你所在的国家的选手，所有选手都已经聚集在赛博乐园参加 APIO 了。你生活在国家 $0$，而赛博乐园是国家 $H$。你作为你的国家最聪明的人，你的帮助刻不容缓。更具体地，你需要确定从你的国家到达赛博乐园所需的最少时间。

在经过有些国家时，你可以清除你的当前总通过时间。此外，还有些国家在你经过他们时可以将你的当前总通过时间除以 $2$（我们称之为“除以 $2$ 的能力”）。你可以重复经过一个国家。每次你经过一个国家时，你可以选择是否使用这个国家的特殊能力。但你每次经过一个国家时最多可以使用一次特殊能力（如果你多次经过一个国家，你每次经过都可以使用至多一次该国家的特殊能力）。此外，为了防止被赛博乐园化学基金会抓住，你最多只能使用“除以 $2$ 的能力”$K$ 次。一旦你到达赛博乐园，你就不能移动到其他任何地方，因为伟大的 APIO 竞赛即将开赛了！

给出一个数组 $arr$ ，其中 $arr[i]$ 表示国家 $i (0 \le i \le N − 1)$ 的特殊能力。每个国家有下面 $3$ 种特殊能力之中的一种：

 - $arr[i] = 0$，意思是这个国家可以让当前总通过时间为 $0$。
 - $arr[i] = 1$，表示这个国家不会改变你的当前总通行时间。
 - $arr[i] = 2$，表示这个国家拥有让当前总通行时间除以 $2$ 的能力。

保证 $arr[0] = arr[H] = 1$ 成立。换句话说，赛博乐园和你所在的国家没有任何特殊能力。

你的国家不希望错过 APIO 的任何时刻，所以你需要找到到达赛博乐园的最短时间。如果你不能到达赛博乐园，你的答案应该是 $−1$。

### 实现细节

你需要实现以下函数：

```cpp
double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr);
```

 - $N$ : 国家的数量。
 - $M$ : 双向道路的数量。
 - $K$: “除以 $2$ 的能力”的最大使用次数。
 - $H$: 国家“赛博乐园”的标号。
 - $x, y, c$: 三个长度为 $M$ 的数组。三元组 $(x[i], y[i], c[i])$ 表示第 $i$ 条用来连接国家 $x[i]$ 和 $y[i]$ 的双向边，通过它的时间消耗是 $c[i]$。
 - $arr$: 一个长度为 $N$ 的数组。$arr[i]$ 表示国家 $i$ 的特殊能力。
 - 如果你能到达赛博乐园，调用该函数应返回从你的国家到达赛博乐园的最短时间，如果你不能，则返回 $−1$。
 - 这个过程可能会被多次调用。

假设选手的答案为 $ans_1$ ，标准输出为 $ans_2$ ，当且仅当 $\dfrac{|ans_1-ans_2|}{\max\{ans_2,1\}} \le 10 ^ {-6}$ 时你的输出被视为是正确的。

注意：由于函数调用可能会发生多次，选手需要注意之前调用的残余数据对于后续调用的影响。

## 说明/提示

### 例子

#### 样例 1

考虑下面的调用：

```cpp
solve(3, 2, 30, 2, {1, 2}, {2, 0}, {12, 4}, {1, 2, 1});
```

唯一的到达赛博乐园的路径是 $0 \rightarrow 2$，因为你到达了赛博乐园之后不能再移动到其他任何地方。通行时间的计算过程如下：

| 国家编号 | 通行时间 |
| :--: | :--: |
| $0$ | $0$ |
| $2$ | $0 + 4 \rightarrow 4(\text{求和}) \rightarrow 4(\text{特殊能力})$|

#### 样例 2

考虑下面的调用：

```cpp
solve(4, 4, 30, 3, {0, 0, 1, 2}, {1, 2, 3, 3}, {5, 4, 2, 4}, {1, 0, 2, 1});
```

从你的国家到赛博乐园有两条路径：$0 \rightarrow 1 \rightarrow 3$ 和 $0 \rightarrow 2 \rightarrow 3$。

如果选择路径 $0 \rightarrow 1 \rightarrow 3$，通行时间的计算如下：

| 国家编号 | 通行时间 |
| :--: | :--: |
| $0$ | $0$ |
| $1$ | $0 + 5 \rightarrow 5(\text{求和}) \rightarrow 0(\text{特殊能力})$|
| $3$ | $0 + 2 \rightarrow 2(\text{求和}) \rightarrow 2(\text{特殊能力})$|

如果选择路径 $0 \rightarrow 2 \rightarrow 3$，通行时间的计算如下：

| 国家编号 | 通行时间 |
| :--: | :--: |
| $0$ | $0$ |
| $2$ | $0 + 4 \rightarrow 4(\text{求和}) \rightarrow 2(\text{特殊能力})$|
| $3$ | $2 + 4 \rightarrow 6(\text{求和}) \rightarrow 6(\text{特殊能力})$|

所以，上述调用应该返回 $2$。

### 约束条件

 - $2 \le N \le 10^5 , \sum N \le 10^5$.
 - $0 ≤ M ≤ \min\{10^5, \dfrac{N(N-1)}{2} \}, \sum M ≤ 10^5$.
 - $1 \le K \le 10^6$.
 - $1 \le H < N$
 - $0 \le  x[i], y[i] < N , x[i] \neq y[i]$.
 - $1 \le c[i] \le 10^9$.
 - $arr[i] \in \{0, 1, 2\}$.
 - 保证每两个国家之间至多使用一条道路进行连接。

### 子任务

1. (5 分)：$N \le 3, K \le 30$.
2. (8 分)：$M = N − 1, K \le 30, arr[i] = 1$，你可以通过这 $M$ 条道路从任意国家到另外一个国家。
3. (13 分)：$M = N − 1, K \le 30, arr[i] \in \{0, 1\}$，你可以通过这 $M$ 条道路从任意国家到另外一个国家。
4. (19 分)：$M = N − 1, K \le 30, x[i] = i, y[i] = i + 1$.
5. (7 分)：$K \le 30, arr[i] = 1$.
6. (16 分)：$K \le 30, arr[i] \in \{0, 1\}$.
7. (29 分)：$K \le 30$.
8. (3 分)：没有特殊限制。

## 样例 #1

### 输入

```
3 2 30
2
1 2 1
1 2 12
2 0 4```

### 输出

```
4```

## 样例 #2

### 输入

```
4 4 30
3
1 0 2 1
0 1 5
0 2 4
1 3 2
2 3 4```

### 输出

```
2```

# 题解

## 作者：novax (赞：10)

感谢土耳其老哥送我铁牌。

分层图好题。

#### 思路

先考虑 $K\leq 30$ 的部分分。

既然求最短距离，那当然是考虑最短路了。

题目要求了到达 $H$ 点就不能再离开，因此需要先建出图跑一个搜索找出所有可以不经由 $H$ 点到达的所有点。若 $H$ 点不能被到达，那么无解。任何可以由起点不经 $H$ 到达的类型 $0$ 城市可以被作为最短路的起点：因为可以先走到这个点上把累积时间清零，再走向 $H$ 点。

很自然地想到把使用除二能力的次数放到状态里：设 $dis_{i,j}$ 表示到达 $i$ 使用了 $j$ 次除二能力的最小距离。

建立分层图，共有 $K+1$ 层：第 $i$ 层对应的 $x$ 点表示使用了 $i$ 次除二能力到达的状态。对于每一条边 $(x_i,y_i,c_i)$，我们在每一层内双向连边。在第 $j$ 层与第 $j+1$ 层之间，我们对于所有 $(x_i,y_i,c_i),arr_{y_i}=2$ 的边，从第 $j$ 层的 $x_i$ 向第 $j+1$ 层的 $y_i$ 连一条权值为 $c_i$ 的边。$H$ 点不连任何出边。

当跨过两层时累积的时间会被除以 $2$，因此需要对层间的边加一个除二标记，表示走过这条边将时间除二。

将前述的可以做起点的点入堆跑 Dijkstra 最短路。为保证转移顺序，需要先以层号为第一关键字，再以距离为第二关键字作为堆的比较方式。

最终在全部 $K+1$ 层的 $H$ 点中取距离最小的就是答案。

对于 $K>30$ 的部分，只需要将 $K$ 与 $70$ 取 $\min$
 即可。
 
证明：题目只需要你的答案与标准答案误差小于 $10^{-6}$，本题的最大累计时间为 $10^{14}$ 级别，因此当走过层数使得理论最大累计时间都小于 $10^{-6}$ 时，继续走下去就没有意义了。$2^{67}\approx 1.48\times 10^{20}$，因此只要将层数与一个不小于 $67$ 的数取 $\min$ 即可。

#### 代码

```cpp
#include <algorithm>
#include <queue>
const int Nx=100010;
const double inf=1e24;
int n,m,k,h,ab[Nx];
struct edge{int to,nex,val,typ;};
edge a[300*Nx];
int head[75*Nx],cnt;
void add(int u,int v,int w,int t)
{
	a[++cnt]=edge{v,head[u],w,t};
	head[u]=cnt;
}
struct node
{
	int idx;double val;
	bool operator < (const node &x) const
	{
		if(idx/n!=x.idx/n)
			return idx/n>x.idx/n;
		return val>x.val;
	}
};
int id(int x,int lev){return x+lev*n;}
void find_zpair(int p)
{
	ab[p]=1;
	int i;
	for(i=head[p];i;i=a[i].nex)
	{
		if(ab[a[i].to]==0&&p!=h)
			find_zpair(a[i].to);
	}
}
double dis[75*Nx];
int fin[75*Nx];
void clear_all()
{
	int i;
	for(i=0;i<n;i++)
		ab[i]=0;
	for(i=0;i<=(k+1)*n+1;i++)
		head[i]=dis[i]=fin[i]=0;
	cnt=n=m=k=h=0;
}
double solve(int N,int M,int K,int H,std::vector<int> X,std::vector<int> Y,std::vector<int> C,std::vector<int> arr)
{
	clear_all();
	K=std::min(K,72);
	n=N,m=M,k=K,h=H;
	int i,j,now,fx,fy;
	for(i=0;i<M;i++)
	{
		add(X[i],Y[i],C[i],1);
		add(Y[i],X[i],C[i],1);
	}
	find_zpair(0);
	if(ab[H]==0)
		return -1;
	for(i=0;i<=N;i++)
		head[i]=0;
	cnt=0;
	for(i=0;i<M;i++)
	{
		for(j=0;j<=K;j++)
		{
			if(X[i]!=H)
				add(id(X[i],j),id(Y[i],j),C[i],1);
			if(Y[i]!=H)
				add(id(Y[i],j),id(X[i],j),C[i],1);
			if(j!=K&&X[i]!=H&&arr[Y[i]]==2)
				add(id(X[i],j),id(Y[i],j+1),C[i],2);
			if(j!=K&&Y[i]!=H&&arr[X[i]]==2)
				add(id(Y[i],j),id(X[i],j+1),C[i],2);
		}
	}
	for(i=0;i<=(K+1)*N+1;i++)
		dis[i]=inf,fin[i]=0;
	std::priority_queue<node> hea;
	for(i=0;i<N;i++)
	{
		if(arr[i]==0&&ab[i]==1)
		{
			hea.push(node{i,0});
			dis[i]=0;
		}
	}
	hea.push(node{0,0});
	dis[0]=0;
	while(hea.size())
	{
		node ax=hea.top();
		hea.pop();
		now=ax.idx;
		if(fin[now])
			continue;
		fin[now]=1;
		for(i=head[now];i;i=a[i].nex)
		{
			if(dis[a[i].to]>(dis[now]+a[i].val)/a[i].typ)
			{
				dis[a[i].to]=(dis[now]+a[i].val)/a[i].typ;
				if(!fin[a[i].to])
					hea.push(node{a[i].to,dis[a[i].to]});
			}
		}
	}
	double ans=inf;
	for(i=0;i<=K;i++)
		ans=std::min(ans,dis[id(H,i)]);
	return ans;
}
```


---

## 作者：dbxxx (赞：10)

[欢迎您到我的博客阅读本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/luogu-p9370.html)

题目就是让我们求一个有各种优惠政策的单源点 $0$，单汇点 $H$ 的最短路。优惠政策是：

- 到达能力为 $2$ 的点，可以让之前走过的距离除以 $2$。
- 到达能力为 $0$ 的点，可以让之前走过的距离直接变成 $0$。

有限制：不能经过 $H$ 多次。那其实也就是说，$H$ 只能作为答案路径的终点，不能作为路径的途经点。

**优惠政策最短路**，再加上 97 分中 $K$ 的限制为 $K \le 30$，**优惠政策能使用的次数很低**。

上面加粗的两句正是分层图最短路的两条重要特征。于是想到建立 $K$ 层的分层图，来解决“除以 $2$”这个优惠政策。

> 这里默认读者已经学会分层图，若不会，请先学习并完成分层图模板：[JLOI2011 飞行路线](https://www.luogu.com.cn/problem/P4568)。这里还有[分层图题单](https://www.luogu.com.cn/training/5811#problems)，供读者练习。

原图为第 $0$ 层图，总共建立 $K +1$ 层图（编号 $0 \sim K$），第 $p$ 层的点 $u$ 代表之前使用优惠恰好 $p$ 次，到达点 $u$ 的状态。我们记其为 $(p, u)$。设它的最短路为 $\mathrm{dis}(p, u)$。

最短路算法必须使用 dijkstra，用 spfa 虽然可以通过原题的数据，但复杂度是错的，讨论区中有 hack 数据。

定义 $w(u, v)$ 为原图上 $u$ 和 $v$ 两点之间的边权。如果 $u$，$v$ 两点之间没有相连接的边则 $w(u, v)$ 未定义。

## 思路一

首先想一下，到达能力为 $0$ 的点可以清空最短路，那其实就相当于从这个点开始走。

因此，我们将所有能从 $0$ 出发，不途径 $H$ 到达的，能力同时为 $0$ 的点看做源点，跑多源最短路即可。

那么能力为 $0$ 就解决了，现在只需要解决能力 $2$。

考虑在 dijkstra 枚举出边时进行如下松弛：

- 尝试用 $\mathrm{dis}(p, u) + w(u, v)$ 更新 $\mathrm{dis}(p, v)$。代表不使用优惠政策。
- 尝试用 $\dfrac{\mathrm{dis}(p, u) + w(u, v)}2$ 更新 $\mathrm{dis}(p + 1, v)$。代表使用优惠政策。

同时注意 $H$ 不能是途经点，因此 $\mathrm{dis}(p, H)$ 强制不松弛其它点即可。

跑一个源点为 $(0, 0)$ 的单源最短路，然后取 $\mathrm{dis}(0, H)$，$\mathrm{dis}(1, H)$，$\mathrm{dis}(2,H)$……中的最小值，作为答案即可。

然而这种思路的问题在于，上面的第二种松弛并不是平凡的最短路松弛，违背了 dijkstra 的正确性。

但是只要进行一步修改，上面的思路就是正确的了：

考虑朴素的 dijkstra 的优先队列，我们会优先取出 $\mathrm{dis}$ 最小的 $(p, u)$。而这里我们修改成：

- 对于 **不同层** 的两个点 $(p, u)$ 和 $(q, v)$，不妨令 $p <q$，则 $(p, u)$ 更优先，不管最短路；
- 对于 **同层** 的两个点 $(p, u)$ 和 $(p, v)$，则取 $\mathrm{dis}$ 更小的更优先。

每次取最优先的开始松弛就一定没有问题。解释一下原因：

**分层图是单向导通的，高层点的最短路一定不会影响低层点。**

观察全局上优先队列取出的过程，大体上是优先低层，然后再优先低距离。

也就是说，在第 $0$ 层图上，只有从点 $0$ 出发能到达（中途不经过 $H$）的所有点，都当过一次队头，并松弛一遍其它点之后，才会开始处理第 $1$ 层图的点。

我们称 dijkstra 的过程中，层号为 $p$ 的点充当队头的阶段为第 $p$ 阶段。那么整个 dijkstra 过程就是 $k + 1$ 个阶段的综合：第 $0$ 阶段，第 $1$ 阶段，……，第 $k$ 阶段。

那么在第 $0$ 阶段之后，第 $0$ 层的所有点的最短路都已经被计算好，并且已经为真实值了（原因就是高层最短路不会影响低层）。此时，目前第 $1$ 层的点 $(1, u)$ 最短路的值是：只途径 $0$ 层的所有点，到达 $(1, u)$ 这个点的距离的一半。

先不进行第 $1$ 阶段，来看第 $1$ 阶段之前，我们只看第 $1$ 层的点，会发现只有这个变化：

一般的单源最短路，在初始时，都是源点距离为 $0$，而其它点距离为 $+\infty$。

而这里的单源最短路，若干点的距离已知，而其它点的距离为 $+\infty$。

会发现这种变化是不影响 dijkstra 的。可以联想一下，将这些距离已知的点 $(1, u)$，新建一个虚点，对虚点向 $(1, u)$ 连一条权值为 $\mathrm{dis}(1, u)$ 的边。然后对虚点为源点，跑单源最短路，那么第一步松弛的结果就是目前第 $1$ 层点的状态。

显然 dijkstra 经过一次松弛之后仍然是正确的，所以该算法是没问题的。

上面我们阐述了从第 $0$ 阶段到第 $1$ 阶段的正确性，事实上，在第 $p$ 个阶段结束后，前 $p$ 层的最短路都已经确定，而第 $p + 1$ 层的最短路可以看作若干个点的距离已经已知的最短路，所以第 $p +1$ 个阶段仍然是正确的。

因此所有阶段都是正确的，算法正确。

这里设边数为小写 $m$，复杂度为 $\Theta(mK \log mK)$。

## 100 分做法

上面的做法是 97 分的，$K \le 30$。考虑 100 分的 $K \le 10^6$。

我们发现，事实上用一些次优惠政策之后，最短路会变的很低，远远低于精度。

具体来说，本题中最短路最大不超过边数乘边权最大值，即 $10^{14}$。只需让这个数除以 $70$ 次 $2$ 就可以掉到 $10^{-7}$ 以下（$8 \times 10^{-8}$）。

也就意味着使用 $70$ 次优惠政策之后，再优惠只可能会让最短路再少个 $10^{-7}$ 以下。

而题目要求精度 $10^{-6}$ 就够了，所以求出的最短路比真实最短路多个 $10^{-7}$ 以下是可以接受的。

因此，令 $k = \min(K, 70)$，然后再按照 97 分做法做即可。复杂度 $\Theta(mk \log mk)$。

当然，如果你当心上面的 $10^{-7}$ 误差能多次累计，以至于影响答案（虽然笔者感觉应该是不会的），把阈值设的高一点也没问题。

```cpp
#include <bits/stdc++.h>

const int N = (int)1e5 + 5;
const int K = 75;
typedef std :: pair <int, int> pii;
struct node {
	int p;
	int u;
	double dis;
	bool operator < (const node b) const {
		if (this -> p != b.p)
			return this -> p > b.p;
		return this -> dis > b.dis;
	}
};
std :: vector <pii> G[N];
double dis[K][N];
std :: bitset <N> vis[K];
std :: bitset <N> con;

inline void init(int n, int k) {
	con.reset();
	for (int u = 0; u < n; ++u)
		G[u].clear();
	for (int p = 0; p <= k; ++p)
		vis[p].reset();
	for (int p = 0; p <= k; ++p)
		for (int u = 0; u < n; ++u)
			dis[p][u] = 1e17;
}

void dfs(int u, int t) {
	con.set(u);
	for (pii e : G[u]) {
		int v = e.first;
		if (!con[v] && v != t)
			dfs(v, t);
	}
}

double solve(int n, int m, int k, int t, std :: vector <int> us, std :: vector <int> vs, std :: vector <int> wei, std :: vector <int> a) {
	if (k > 70)
		k = 70;
	init(n, k);

	for (int i = 0; i < m; ++i) {
		int u = us[i], v = vs[i], w = wei[i];
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	dfs(0, t);
	std :: priority_queue <node> q;
	for (int u = 0; u < n; ++u) {
		if (con[u] && (a[u] == 0 || u == 0)) {
			dis[0][u] = 0;
			q.push({0, u, 0});
		}
	}

	while (!q.empty()) {
		node now = q.top();
		q.pop();
		int u = now.u, p = now.p;
		if (vis[p][u] || u == t)
			continue;
		vis[p].set(u);
		for (pii e : G[u]) {
			int v = e.first, w = e.second;
			if (dis[p][v] > dis[p][u] + w) {
				dis[p][v] = dis[p][u] + w;
				if (!vis[p][v])
					q.push({p, v, dis[p][v]});
			}
			if (a[v] == 2 && p < k) {
				if (dis[p + 1][v] > (dis[p][u] + w) / 2) {
					dis[p + 1][v] = (dis[p][u] + w) / 2;
					if (!vis[p + 1][v])
						q.push({p + 1, v, dis[p + 1][v]});
				}
			}
		}
	}

	double ans = DBL_MAX;
	for (int p = 0; p <= k; ++p)
		ans = std :: min(ans, dis[p][t]);
	if (ans > 1e15)
		return -1;
	return ans;
}
```

## 思路二

如果你想不到修改堆排序方式，还有一种思路，我们只需要对原题进行转化并进行合理地分层之后，套一个裸 dijkstra 就可以解决。

考虑建立反图（虽然无向图的反图和原图是一样的），观察反的最短路径上，优惠政策的含义：

- 原先遇到能力为 $0$ 的点，会把当前距离设置为 $0$；
- 那么现在遇到能力为 $0$ 的点，相当于让之后走过的所有边权都变成 $0$。
- 原先遇到能力为 $2$ 的点，会把当前距离减半；
- 那么现在遇到能力为 $2$ 的点，相当于让之后走过的所有边权都变成原来的一半。

我们发现，直接让第 $p$ 层上 $u$ 和 $v$ 之间的边权为原图上 $u$ 和 $v$ 之间边权的 $\dfrac{1}{2^p}$，就能满足能力为 $2$ 的点；至于能力为 $0$ 的点，我们可以新建一层 $K + 1$ 层，让这一层内 $u$ 和 $v$ 之间的边权都改成 $0$。然后让所有 $a[v] = 0$ 的 $(p, v)$ 直接单向导通到 $K + 1$ 层即可。

这样以来，裸的 dijkstra 就可以解决问题。此时汇点是 $H$，源点是 $0$。

同时注意一下不能途径 $H$ 的问题。思路一中，我们是允许某个点松弛 $(p, H)$ 的，只是不允许 $(p, H)$ 松弛别人而已；思路二中我们是从 $H$ 出发，这里我们不能允许任意一个点松弛 $(p, H)$。

```cpp
#include <bits/stdc++.h>
const int N = (int)1e5 + 5;
const int K = 75;
typedef std :: pair <int, int> pii;
struct node {
	int p;
	int u;
	double dis;
	bool operator < (const node b) const {
		return this -> dis > b.dis;
	}
};

std :: vector <pii> G[N];
double dis[K][N];
std :: bitset <N> vis[K];
double val[K];

inline void init(int n, int k) {
	val[0] = 1;
	for (int i = 1; i <= k; ++i)
		val[i] = val[i - 1] / 2;
	val[k + 1] = 0;
	for (int u = 0; u < n; ++u)
		G[u].clear();
	for (int p = 0; p <= k + 1; ++p)
		vis[p].reset();
	for (int p = 0; p <= k + 1; ++p)
		for (int u = 0; u < n; ++u)
			dis[p][u] = 1e17;
}

double solve(int n, int m, int k, int t, std :: vector <int> us, std :: vector <int> vs, std :: vector <int> wei, std :: vector <int> a) {
	if (k > 70)
		k = 70;
	init(n, k);

	for (int i = 0; i < m; ++i) {
		int u = us[i], v = vs[i], w = wei[i];
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	std :: priority_queue <node> q;
	dis[0][t] = 0;
	q.push({0, t, 0});

	while (!q.empty()) {
		node now = q.top();
		q.pop();
		int u = now.u, p = now.p;
		if (vis[p][u])
			continue;
		vis[p].set(u);
		for (pii e : G[u]) {
			int v = e.first, w = e.second;
			if (v == t)
				continue;// 这里阻止松弛的方式和思路一不同，原理已经解释
			if (a[v] == 0) {
				if (dis[k + 1][v] > dis[p][u] + w * val[p]) {
					dis[k + 1][v] = dis[p][u] + w * val[p];
					if (!vis[k + 1][v])
						q.push({k + 1, v, dis[k + 1][v]});
				}
				continue;
			}
			if (dis[p][v] > dis[p][u] + w * val[p]) {
				dis[p][v] = dis[p][u] + w * val[p];
				if (!vis[p][v])
					q.push({p, v, dis[p][v]});
			}
			if (a[v] == 2 && p < k) {
				if (dis[p + 1][v] > dis[p][u] + w * val[p]) {
					dis[p + 1][v] = dis[p][u] + w * val[p];
					if (!vis[p + 1][v])
						q.push({p + 1, v, dis[p + 1][v]});
				}
			}
		}
	}

	double ans = DBL_MAX;
	for (int p = 0; p <= k + 1; ++p)
		ans = std :: min(ans, dis[p][0]);
	if (ans > 1e15)
		return -1;
	return ans;
}
```

---

## 作者：ningago (赞：6)

记 $dis_{k,t}$ 表示使用恰好 $t$ 次 $2$ 类魔法到达节点 $k$ 的最小花费。

对于 $k\to nx$ 这一条边（边权为 $v$），显然转移为：

1. $dis_{k,t} +v\to dis_{nx,t}$
2. $(dis_{k,t}+v)\times 0\to dis_{nx,t}(arr_{nx}=0)$
3. $(dis_{k,t}+v)\times \dfrac{1}{2}\to dis_{nx,t+1}(arr_{nx}=2,t<K)$。

复杂度 $O(nK\log (mK))$。

考虑到第 $3$ 类转移会尽可能地靠后使用，根据 SPJ 精度判断方式，只需要保证 $(\dfrac{1}{2})^{K'}\times \sum v\leq 10^{-6}$ 即可。

取 $K'=67$ 即可。

https://www.luogu.com.cn/paste/ou0vc13t

---

## 作者：ZLRest (赞：5)

## 题目大意：

求从单源点到终点的最短路，经过的点有两种能力：

- 时间花费减半
- 清空所用时间
## 思路：
一眼分层图，~~虽然蒟蒻一晚上没调出来~~。
不会分层图的看[这里](https://www.luogu.com.cn/blog/xuduo-cyj/xue-xi-bi-ji-qian-tan-fen-ceng-tu)

因为最多只能使用 $K$ 次花费减半的能力，所以考虑建 $K$ 层图。
而清空时间的能力可以看做源点跑多源最短路。**但这里一定要注意题目中要求**：**一旦你到达赛博乐园，你就不能移动到其他任何地方，因为伟大的 APIO 竞赛即将开赛了！** 所以我们先遍历一遍图，找出所有在走到 $H$ 之前就可以到达的能力为 $0$ 的点作为源点跑最短路，然后在建边时不给 $H$ 建出边,就可以避免到了 $H$ 后乱跑了。

这样就可以拿到 97pts 了。然后我们再考虑 $k\geqslant30$ 的部分，看题目的 spj 的要求，只要 $(\dfrac{1}{2})^K\times\sum_{i=1}^Nc_i\leqslant10^{-6}$ 即可。而 $\sum_{i=1}^Nc_i$  最大 超不过 long long， $K$ 与 $70$ 取 min 即可。

另：若 TLE 卡卡常就过了 ~~链式前向星好快~~
## 完整代码：
```cpp
//#include "cyberland.h"
#include <bits/stdc++.h>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;
int n,m,k,h;
struct node{
	int next,to;
	double w,val;
}edge[1000010*30];
struct ss{
	int now;
	double sum;
	bool operator < (const ss &x) const
	{
		if(now/n!=x.now/n)
			return now/n>x.now/n;
		return sum>x.sum;
	}//若不在同一层则层数小的一定更优，不管边权。
	bool operator > (const ss &x) const
	{
		if(now/n!=x.now/n)
			return now/n<x.now/n;
		return sum<x.sum;
	}
};
int head[100010*300];
bool vis[100010*300];
int cnt;
double f[100010*300];
void add(int u,int v,int w,double k){
	edge[cnt].to=v;
	edge[cnt].w=w;
	edge[cnt].val=(double)k;
	edge[cnt].next=head[u];
	head[u]=cnt++;
}
void dfs(int now){
	vis[now]=1;
	if(now==h){
		return;
	}
	for(int i=head[now];i;i=edge[i].next){
		if(!vis[edge[i].to]&&edge[i].val==1) dfs(edge[i].to);
	}
	return;
}
double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr){
	cnt=n=m=k=h=0;
    cnt=1;
	k=K=min(70,K);
	n=N,m=M,h=H;
	for(int i=0;i<=(n+1)*(k+1);i++)vis[i]=0,head[i]=0,f[i]=1e24;
	for(int i=0;i<M;i++){
		for(int j=0;j<=K;j++){
			if(x[i]!=H)
			add(x[i]+j*n,y[i]+j*n,c[i],1.0);
			if(y[i]!=H)
			add(y[i]+j*n,x[i]+j*n,c[i],1.0);
			if(arr[x[i]]==2&&y[i]!=H&&j!=k)
				add(y[i]+j*N,x[i]+(j+1)*N,c[i],2.0);
			if(arr[y[i]]==2&&x[i]!=H&&j!=k)
				add(x[i]+j*N,y[i]+(j+1)*N,c[i],2.0);
		}
	}
	dfs(0);
	if(!vis[H]) return -1;
	priority_queue <ss> q;
	q.push((ss){0,0});
	f[0]=0;
	for(int i=0;i<n;i++){
		if(arr[i]==0&&vis[i]) q.push({i,0}),f[i]=0;
	}
	for(int i=0;i<=N+1;i++) vis[i]=0;
	while(!q.empty()){
		int g=q.top().now;
		q.pop();
		if(vis[g]) continue;
		//if(g==h) continue;
		vis[g]=1;
		for(int i=head[g];i;i=edge[i].next){
			if(f[edge[i].to]>(f[g]+edge[i].w)/edge[i].val){
				f[edge[i].to]=(f[g]+edge[i].w)/edge[i].val;
				if(!vis[edge[i].to])
				q.push({edge[i].to,f[edge[i].to]});
			}
		}
	}
	double ans=1e24;
	for(int i=0;i<=k;i++) ans=min(ans,f[H+i*n]);
	return ans;
}
```
码风巨丑， dalao 见谅。

---

## 作者：DaydreamWarrior (赞：4)

[才不是很好的阅读体验！](https://rainlycoris.github.io/#/post/29)

## 分析

首先把图反着跑，这样总通行时间除以 $2$ 就变成了后续时间都除以 $2$，当前总通过时间为 $0$ 就变成了后续时间都为 $0$。

然后把一个点拆开成 $K+2$ 个，第 $i$ 个代表经过 $i$ 次除以二操作的点，最后一个代表经过清零操作的点，然后跑最短路。

注意一下 $H$ 不能多次经过和不能达到为 $-1$，这样就有 $97$ 分了。

发现除以二操作做 $\log_2 \frac{10^5\times10^9}{10^{-6}}$ 次就会变成可以忽略的值，所以 $K$ 和 $70$ 取小的那一个就行。

## 代码

```cpp
const int N = 100005,C = 72,L = 70;
typedef pair<double,pair<int,int>> LDII;
vector<pair<int,int>> g[N];
double dis[N][C];//清零和超过 L 次除以 2 视为一致

double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr){
    for(int k=0;k<N;k++){
        g[k].clear();
        for(int j=0;j<=L;j++)
            dis[k][j] = 2e18;
    }
    for(int k=0;k<M;k++){
        g[x[k]].emplace_back(y[k],c[k]);
        g[y[k]].emplace_back(x[k],c[k]);
    }
    priority_queue<LDII,vector<LDII>,greater<LDII>> q;
    q.push({0,{H,0}});
    dis[H][0] = 0;
    while(!q.empty()){
        auto [u,k] = q.top().second;
        q.pop();
        for(auto[v,w]:g[u]){
            if(v==H)
                continue;
            if(k>=L){//视作清零操作
                if(dis[v][L]>dis[u][k]){
                    dis[v][L] = dis[u][k];
                    q.push({dis[v][L],{v,L}});
                }
                continue;
            }
            if(arr[v]==0){
                if(dis[v][L]>dis[u][k]+w*1.0/(1ll<<k)){
                    dis[v][L] = dis[u][k]+w*1.0/(1ll<<k);
                    q.push({dis[v][L],{v,L}});
                }
                continue;
            }
            if(arr[v]==2&&k<K){
                if(dis[v][k+1]>dis[u][k]+w*1.0/(1ll<<k)){
                    dis[v][k+1] = dis[u][k]+w*1.0/(1ll<<k);
                    q.push({dis[v][k+1],{v,k+1}});
                }
            }
            if(dis[v][k]>dis[u][k]+w*1.0/(1ll<<k)){
                dis[v][k] = dis[u][k]+w*1.0/(1ll<<k);
                q.push({dis[v][k],{v,k}});
            }
        }
    }
    double ans = 2e18;
    for(int k=0;k<=L;k++)
        ans = min(ans,dis[0][k]);
    if(ans>1e18)
        return -1;
    return ans;
}
```

## 闲话
考试的时候用的是 $50$ 过了，死过以内。

---

## 作者：zac2010 (赞：4)

## 方法 $1$：分层图 SPFA

### $97$ 分做法

一个分层图 SPFA，直接对模板改改就行了。

具体的，状态 $d_{u,i}$ 表示走到 $u$ 这个节点，用了 $i$ 次“除以 $2$ 的能力”所花费的最少时间。同时，这道题的 SPFA 转移多了一种：对于一条边 $u$ 到 $v$ 权值为 $w$ 的边，若 $a_v=2$，那么拿 $\frac{(d_{u,i}+w)}{2} \to d_{v,i+1}$。 

中途若拓展到 $a_u=0$ 的点，直接 $d_{u,i}=0$。

### $100$ 分做法

只需要把 $k$ 和 $70$ 取个 $\min$ 就行了。

证明：考虑假设有一条路径上有超过 $70$ 个位置用了“除以 $2$ 的能力”，会发现前面的所有的“除以 $2$ 的能力”现在都不用了，只保留最后 $70$ 次也能使精度误差在 $10^{-6}$ 以内。考虑只保留后 $70$ 次的方案中的第一次除以 $2$ 前的那条路径，总时间不会超过 $n \times v$，$v$ 表示通过一条路的最大时间，所以不超过 $10^5 \times 10^9=10^{14}$。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/dr01ldds.png)

在后面的 $70$ 次除以 $2$ 便能把前面那一个极端的数给除到 $10^{-6}$ 以下。

### 代码

注意点：
* 多测清空。
* 途中不能经过 $h$。

以下代码使用了 SPFA 的 SLF 优化。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 1e5 + 10, K = 71;
struct E{int v, w;};
struct Node{int u, t;};
int n, m, k, h, a[N], vis[N][K];
db ans, d[N][K];
vector<E> g[N];
deque<Node> q;
void spfa(){
	L(i, 1, n) L(j, 0, k) d[i][j] = 1e18, vis[i][j] = 0;
	L(j, 0, k) vis[h][j] = 1;
	while(!q.empty()) q.pop_front();
	d[1][0] = 0; q.push_back({1, 0}), vis[1][0] = 1;
	while(!q.empty()){
		int u = q.front().u, t = q.front().t;
		q.pop_front(), vis[u][t] = 0;
		for(auto &e: g[u]){
			int v = e.v, w = e.w;
			if(t < k && a[v] == 2 && d[u][t] + w < d[v][t + 1] * 2){
				d[v][t + 1] = (d[u][t] + w) / 2.0;
				if(!vis[v][t + 1]){
				    if(!q.empty() && d[v][t + 1] < d[q.front().u][q.front().t])
				        q.push_front({v, t + 1});
				    else q.push_back({v, t + 1});
				    vis[v][t + 1] = 1;
				}
			}
			if(d[u][t] + w < d[v][t]){
				d[v][t] = d[u][t] + w;
				if(!a[v]) d[v][t] = 0;
				if(!vis[v][t]){
				    if(!q.empty() && d[v][t] < d[q.front().u][q.front().t])
				        q.push_front({v, t});
				    else q.push_back({v, t});
				    vis[v][t] = 1;
			    }
			}
		}
	}
}
double solve(int N, int M, int K, int H, vector<int> X, vector<int> Y, vector<int> C, vector<int> ARR){
	n = N; m = M; k = min(K, 70); h = H + 1; ans = 1e18;
	L(i, 1, n) a[i] = ARR[i - 1], g[i].clear();
	L(i, 0, m - 1){
		int u = X[i] + 1, v = Y[i] + 1, w = C[i];
		g[u].emplace_back((E){v, w}), g[v].emplace_back((E){u, w});
	}
	spfa();
	L(j, 0, k) ans = min(ans, d[h][j]);
	return ans == 1e18? -1 : ans;
}
```
## 方法 $2$：分层图 Dijkstra

### 解题思路

我们知道对于一条边，它最终的贡献取决于它的权值以及经过它之后使用的“除以 $2$ 的能力”次数。又由于是无向图，所以考虑倒着 Dijkstra，分层图的状态设计和 SPFA 的一样。这样就可以知道每条边后面使用了多少次“除以 $2$ 的能力”。特别的，若遇到 $a_u=0$ 的点，直接让“除以 $2$ 的能力”使用次数变成 $70$，那样的话就能巧妙的在一定的误差内处理。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
using namespace std;
const int N = 1e5 + 10, K = 72;
struct E{int v, w;};
int n, m, k, h, a[N], vis[N][K];
db ans, d[N][K], pw[K];
vector<E> g[N];
struct Node{
    int u, t; db d;
    bool operator < (const Node &cmp)const{return d > cmp.d;}
};
priority_queue<Node> q;
void Dijkstra(){
    L(i, 1, n) L(j, 0, 70) vis[i][j] = 0, d[i][j] = 1e18;
    while(!q.empty()) q.pop();
    q.push({h, 0, d[h][0] = 0});
    while(!q.empty()){
        int u = q.top().u, t = q.top().t;
        q.pop();
        if(vis[u][t]) continue;
        vis[u][t] = 1;
        for(auto &e: g[u]){
            int v = e.v, w = e.w; if(v == h) continue;
            if(!a[v]){
                if(d[u][t] + w * pw[t] < d[v][70])
                    q.push({v, 70, d[v][70] = d[u][t] + w * pw[t]});
            }
            else if(t < k && a[v] == 2){
                if(d[u][t] + w * pw[t] < d[v][t + 1])
                    q.push({v, t + 1, d[v][t + 1] = d[u][t] + w * pw[t]});
            }
            else{
                if(d[u][t] + w * pw[t] < d[v][t])
                    q.push({v, t, d[v][t] = d[u][t] + w * pw[t]});
            }
        }
    }
}
double solve(int N, int M, int K, int H, vector<int> X, vector<int> Y, vector<int> C, vector<int> ARR){
	n = N; m = M; k = min(K, 70); h = H + 1; ans = 1e18;
	L(i, 1, n) a[i] = ARR[i - 1], g[i].clear();
	pw[0] = 1; L(i, 1, 70) pw[i] = pw[i - 1] / 2;
	L(i, 0, m - 1){
		int u = X[i] + 1, v = Y[i] + 1, w = C[i];
		g[u].emplace_back((E){v, w}), g[v].emplace_back((E){u, w});
	}
	Dijkstra();
	L(i, 0, 70) ans = min(ans, d[1][i]);
	return ans == 1e18? -1 : ans;
}
```

---

## 作者：hoko (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P9370)

## 题目大意

有 $N$ 个国家，$M$条双向道路，每一条道路的花费为 $c_i$，有些国家有超能力，用 $arr_i$ 来表示第 $i$ 个国家的超能力编号，若 $arr_i=0$，表示第 $i$ 个国家可以把之前的所有花费清零，若 $arr_i=1$ 表示这个国家没有超能力，若 $arr_i=2$ 表示这个国家可以把当前花费除以 $2$，但是这个能力最多用 $k$ 次。国家可以重复经过，每次经过都可以选择是否使用超能力，至多用一次。求从 $0$ 号点到 $H$ 的最小花费，误差 $<10^{-6}$。

## 思路

容易发现当 $k>70$ 时，误差已经小于 $10^{-6}$。所以我们想到用分层图跑  `dijkstra`， 以 $0$ 号点和所有的$arr_i=0$ 的点为起点，对于 $arr_i=2$ 的国家记得 $dis \div 2$，其他国家正常跑最短路。优先队列排序时以层数为第一关键字，花费为第二关键字。

思路比较清晰，但是代码有很多细节。注意是多测，要及时清空，特别是链式前向星，一定要把 $head$ 数组归零。还有要先跑一遍 `dfs` 判断连通性。不建议使用 `memset` 清空数组，很慢，建议直接用 `for`。`vector` 存图也有点慢，链式前向星会快一点。

## 代码

```cpp
#include<bits/stdc++.h>
#include "cyberland.h"
#define INF 1e18
using namespace std;
const int N=101010;
int vis[70*N],head[70*N],tot,n,h,k;
double dis[70*N];
int id(int x,int y){return x+y*n;}
struct tt{
    int to,w,next,div;
}e[200*N];
struct node{
    int id;
    double val;
    bool operator < (const node &a)const{
        if(id/n!=a.id/n)return id/n>a.id/n;
        return val>a.val;
    }
};
void add(int u,int v,int w,int div){e[++tot]=(tt){v,w,head[u],div},head[u]=tot;}
priority_queue<node>q;
void dfs(int u){
    vis[u]=1;
    if(u==h)return;
    for(int i=head[u];i;i=e[i].next){
    	int v=e[i].to;
        if(vis[v])continue;
        dfs(v);
    }
}
void init(){
    for(int i=0;i<=n*(k+1)+10;i++)vis[i]=0,head[i]=0,dis[i]=INF;
	tot=0;
}
double solve(int N,int M,int K,int H,std::vector<int>x,std::vector<int>y,std::vector<int>c,std::vector<int>arr){
    K=min(K,68);
	n=N,h=H,k=K;
    init();
    for(int i=0;i<M;i++){
        add(x[i],y[i],c[i],1);
        add(y[i],x[i],c[i],1);
    }
    dfs(0);
    if(!vis[H])return -1;
    for(int i=0;i<=(n+1)*k+1;i++)head[i]=0;
    tot=0;
    for(int i=0;i<M;i++){
        for(int j=0;j<=K;j++){
            if(x[i]!=H)add(id(x[i],j),id(y[i],j),c[i],1);
            if(y[i]!=H)add(id(y[i],j),id(x[i],j),c[i],1);
			if(j!=K&&x[i]!=H&&arr[y[i]]==2)add(id(x[i],j),id(y[i],j+1),c[i],2);
            if(j!=K&&y[i]!=H&&arr[x[i]]==2)add(id(y[i],j),id(x[i],j+1),c[i],2);
        }
    }
    for(int i=0;i<N;i++)if(!arr[i]&&vis[i])q.push((node){i,0}),dis[i]=0;
    for(int i=0;i<=(N+1)*K+10;i++)vis[i]=0;
	q.push((node){0,0});
	dis[0]=0;
    while(!q.empty()){
        node now=q.top();
		int u=now.id;
        q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(int i=head[u];i;i=e[i].next){
            int v=e[i].to;
            int w=e[i].w;
            int d=e[i].div;
            if((dis[u]+w)/d<dis[v]){
                dis[v]=(dis[u]+w)/d;
                if(!vis[v])q.push((node){v,dis[v]});
            }
        }
    }
    double ans=INF;
    for(int i=0;i<=K;i++)ans=min(ans,dis[id(H,i)]);
    return ans;
}
```

---

## 作者：_Ch1F4N_ (赞：1)

这个问题令人很熟悉。

最短路上优惠路径显然是用**分层图**解决。

记数组 $dis_{i,j}$ 表示到达点 $i$ 且使用了 $j$ 次特殊能力的前提下的最短路。

那么我们可以根据题意模拟出简单的转移，写上一个 SPFA。

然后这理论复杂度不太对，考虑换成迪杰斯特拉。

首先简化转移。

注意到对于 $arr_i = 0$ 的点，显然无论之前的路径多长，只要到了这个点花费就变成 $0$，因此加入可以到这个点，那么在过来的路径上**一定不要用“除以 $2$ 的能力”**，原因是无论之前的能力是否使用，花费都会变成 $0$，那还不如不用，那么我们发现这个点**相当于一个不会被更新的最短路起点。**

所以搜出所有可以到达的 $arr_i = 0$ 的点，视作起点来处理。

那么只剩下“除以 $2$ 的能力”的问题，显然，这个能力等同于**负边权**，那应该怎么办呢？

注意到这个能力一旦使用就会让**进入到下一层图，也就是说只有相邻两层图之间的点的边权可能为负**，那我们就可以每次**优先松弛所在层更靠上的点**，这样的好处是这次松弛只会对更低层的图的点产生影响，**迪杰斯特拉算法中的贪心仍然成立。**

又发现当 $k$ 很大时答案会变得很小以至于小于这个精度范围，所以让 $k$ 变成 $\min(70,k)$。

那么就可以写出代码了：

```cpp
#include<bits/stdc++.h>
double dis[2000005][90];
const double inf = 1e17;
std::vector< std::pair<int,double> > edge[2000005];
#define min(a,b) (a<b?a:b)
struct Node{
    int u,k;
	double dis;
    bool operator < (const Node b) const {
		  if(b.k!=k){
            return k>b.k;
        }
        else{
            return dis>b.dis;
        }
	}
};
int hash(Node A){
  return ((A.u+1)*150+A.k+1)%20000005;
}
std::bitset<20000005> use;
std::priority_queue< Node > q;
std::bitset<2000005> cnt;
void search(int u,int H){
  if(cnt[u]==1||u==H) return ;
  cnt[u]=1;
  for(std::pair<int,double> nxt:edge[u]){
    int v=nxt.first;
    search(v,H);
  }
}
double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr){
  K=min(K,75);
  use.reset();
  cnt.reset();
  for(int i=0;i<=N+10;i++) edge[i].clear();
  for(int i=M-1;i>=0;i--){
    int u=x[i],v=y[i],w=c[i];
    std::pair<int,double> New;
    New.first=v,New.second=w;
    edge[u].push_back(New);
    New.first=u;
    edge[v].push_back(New);
  }
  for(int i=0;i<N+10;i++){
    for(int j=0;j<=K+10;j++) dis[i][j]=inf;
  }
  search(0,H);
  for(int i=0;i<N;i++){
    if(cnt[i]==1&&(i==0||arr[i]==0)){
      Node start;
      start.u=i;
      start.k=0;
      start.dis=0;
      dis[i][0]=0.0;
      q.push(start);
    }
  }
  while(q.size()!=0){
    Node f=q.top();
    q.pop();
    if(use[hash(f)]) continue;
    if(f.u==H) continue;
    use[hash(f)]=1;
    for(std::pair<int,double> nxt:edge[f.u]){
      int v=nxt.first;
      double w=nxt.second;
      Node New;
      New.u=v;
      New.k=f.k;
      if(dis[f.u][f.k]+w<dis[v][f.k]&&use[hash(New)]==0){
        dis[v][f.k]=dis[f.u][f.k]+w;
        New.dis=dis[v][f.k];
        q.push(New);
      }
      if(arr[v]==2){
        New.u=v;
        New.k=f.k+1;
        if((dis[f.u][f.k]+w)/2<dis[v][f.k+1]&&f.k+1<=K&&use[hash(New)]==0){
          dis[v][f.k+1]=(dis[f.u][f.k]+w)/2;
          New.dis=dis[v][f.k+1];
          q.push(New); 
        }
      }
    }
  }
  double ans=inf;
  for(int i=0;i<=K;i++) ans=min(ans,dis[H][i]);
  if(ans>=inf) return -1;
  else return ans;
}
```

其实这里还有第二种写法。

我们用 SPFA 写，但是考虑一个经典优化——以队列长度分之一的概率按照上面的优先级别重排整个队列，速度快得起飞。

```cpp
#include<bits/stdc++.h>
double dis[200005][80];
const double inf = 1000000000000000.00;
std::vector< std::pair<int,double> > edge[200005];
#define min(a,b) (a<b?a:b)
struct Node{
	int u,k;
	double dis;
};
Node q[40000005];
int L,R;
bool cmp(Node A,Node B){
	if(A.k!=B.k) return A.k<B.k;
	else return A.dis<B.dis;
}
double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr){
  K=min(K,70);
  R=20000005,L=20000006;
  for(int i=0;i<=N;i++) edge[i].clear();
  for(int i=0;i<M;i++){
    int u=x[i],v=y[i],w=c[i];
    std::pair<int,double> New;
    New.first=v,New.second=w;
    edge[u].push_back(New);
    New.first=u;
    edge[v].push_back(New);
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<=K;j++) dis[i][j]=inf;
  }
  dis[0][0]=0;
  Node start;
  start.u=0,start.k=0,start.dis=0.0;
  q[++R]=start;
  while((R-L+1)!=0){
    if(rand()%(R-L+1)==1){
      std::stable_sort(q+L,q+R+1,cmp);
    }    
    Node f=q[L];
    L++;
    if(f.u==H) continue;
    for(std::pair<int,double> nxt:edge[f.u]){
      int v=nxt.first;
      double w=nxt.second;
      if(arr[v]==0){
        if(dis[v][f.k]>0){
          dis[v][f.k]=0;
          Node New;
          New.u=v;
          New.k=f.k;
          New.dis=dis[v][f.k];
          q[++R]=New;
        }
      }
      else if(arr[v]==1){
        if(dis[f.u][f.k]+w<dis[v][f.k]){
          dis[v][f.k]=dis[f.u][f.k]+w;
          Node New;
          New.u=v;
          New.k=f.k;
          New.dis=dis[v][f.k];
          q[++R]=New;
        }
      }
      else{
        if(dis[f.u][f.k]+w<dis[v][f.k]){
          dis[v][f.k]=dis[f.u][f.k]+w;
          Node New;
          New.u=v;
          New.k=f.k;
          New.dis=dis[v][f.k];
          q[++R]=New;
        }
        if((dis[f.u][f.k]+w)/2.0<dis[v][f.k+1]&&f.k+1<=K){
          dis[v][f.k+1]=(dis[f.u][f.k]+w)/2.0;
          Node New;
          New.u=v;
          New.k=f.k+1;
          New.dis=dis[v][f.k+1];
          q[++R]=New;
        }
      }
    }
  }
  double ans=inf;
  for(int i=0;i<=K;i++) ans=min(ans,dis[H][i]);
  if(ans==inf) return -1;
  else return ans;
}
```


---

## 作者：Iniaugoty (赞：1)

## problem

有 $N$ 个结点，$M$ 条边的**无向图**，求点 $0$ 到点 $H$ 的最短路径。

到达结点 $i$ 后，可以对目前路径长度进行**最多 $1$ 次**操作，操作有以下 $3$ 种类型：

- $arr_i=0$ 时：将目前路径长度清零。这种操作没有使用次数限制。

- $arr_i=1$ 时：没有任何影响。

- $arr_i=2$ 时：将目前路径长度除以 $2$，**不取整**（故答案可能为小数）。这种操作可以使用**最多 $K$ 次**。

此外，还有一些限制：

- **结点 $H$ 只能到达 $1$ 次**。

- 其它结点可以不限制地经过。

- 保证 $arr_0=arr_H=1$。

## solution

发现 $2$ 操作次数有使用限制，在大部分 subtask 中限制很小，$K\le30$，所以可以建立 $0\sim K$ 层的分层图，第 $i$ 层为 $i$ 次 $2$ 操作的结点，再求最短路。

至于这种方法为何不用 dijkstra：因为将路径除以 $2$ 实际上相当于负边权。

松弛不难。设 $t$ 为当前结点，$f$ 是其层数，$y$ 为下一个结点，$d$ 为经过 $t$ 在结点 $y$ 不使用 $2$ 操作的路径距离，$dis_{i,j}$ 为结点 $i$ 在 $j$ 层的最短路径。

- $arr_y=2$，且 $f<K$（即 $2$ 操作没用完）：若  $\displaystyle\frac{d}{2}<dis_{y,f+1}$，则 $dis_{y,f+1}\gets \displaystyle\frac{d}{2}$。如果 $(y,f+1)$ 不在队列中，就将 $(y,f+1)$ 加入队列。

- 否则，若 $d<dis_{y,f+1}$，则 $dis_{y,f}\gets d$。如果 $(y,f)$ 不在队列中，就将 $(y,f)$ 加入队列。

注意点：

- 若 $arr_y=0$，直接令 $d\gets0$；否则 $d\gets dis_{t,f}+w$，$w$ 是 $t$ 到 $y$ 的边长度。

- 若 $y=H$，无论如何都不加入队列，因为 $H$ 只到达一次。

核心 SPFA 代码：

```cpp
//链式前向星存边
queue<pair<int,int> >q;
q.push(make_pair(0,0));
while(!q.empty()){
	int t=q.front().first,f=q.front().second;
	q.pop(),vis[t][f]=0;
	for(int i=head[t];i;i=e[i].next){
		int y=e[i].to;
		double d=!arr[y]?0:dis[t][f]+e[i].val;//可以进行操作 1 的话直接归零
      		if(arr[y]==2&&f<K&&dis[y][f+1]>d/2.0){//操作 2
			dis[y][f+1]=d/2.0;
			if(!vis[y][f+1]&&y!=H) vis[y][f+1]=1,q.push(make_pair(y,f+1));
		}
		if(dis[y][f]>d){//正常松弛
			dis[y][f]=d;
			if(!vis[y][f]&&y!=H) vis[y][f]=1,q.push(make_pair(y,f));
		}
	}
}
```

然而这样还有最后一个 subtask 的 3 分得不到。

仔细想想，$\max\{K\}=10^6$，除以这么多次 $2$ 真的有用吗？很明显是没有的，根据 Special Judge 的判定公式，当 $K>70$ 后的误差几乎为 $0$。所以在 SPFA 之前令 $K\gets\min\{K,70\}$ 即可。

（Updata 2023.5.31：第一次审核没过，补充一下 $K\gets\min\{K,70\}$ 里的 $70$ 怎么来的。路径总和的最大值为 $\max\{M\}\times\max\{c_i\}=10^{14}$，再除以 Special Judge 的最大误差值 $10^{-6}$ 得到 $10^{20}$，将其一直除以 $2$，总共可以除 $\log_210^{20}\approx66.438561897747246957406388589788\cdots$ 次，所以 $K$ 取 $\min\{K,67\}$ 即可，为了保险起见~~和美观~~四舍五入个 $70$ 出来）

当然，要是能加上 Small Label First 和 Large Label Last 优化就更好了，避免某算法已死的惨案。

## code

这里是完整版代码，由于懒惰，并没有把优化加上去。

```cpp
#include<bits/stdc++.h>
#define maxn 100005
#define inf 1e15
#define min(a,b) (a<b?a:b)
using namespace std;
int head[maxn],cnt;
struct star{//链式前向星存边
	int next,to,val;
}e[maxn<<1];
void add(int u,int v,int w){
	e[++cnt].next=head[u];
	e[cnt].to=v;
	e[cnt].val=w;
	head[u]=cnt;
}
double dis[maxn][75];
bool vis[maxn][75];
double solve(int N,int M,int K,int H,vector<int>x,vector<int>y,vector<int>c,vector<int>arr){
	memset(head,0,sizeof head);
	memset(e,0,sizeof e);//多测不清空见祖宗
	cnt=0,K=min(K,70);
	for(int i=0;i<M;i++)
		add(x[i],y[i],c[i]),add(y[i],x[i],c[i]);

	for(int i=0;i<N;i++)
		for(int j=0;j<=K;j++)
			dis[i][j]=inf;//不初始化见祖宗
	dis[0][0]=0;
	queue<pair<int,int> >q;
	q.push(make_pair(0,0));
	while(!q.empty()){
		int t=q.front().first,f=q.front().second;
		q.pop(),vis[t][f]=0;
		for(int i=head[t];i;i=e[i].next){
			int y=e[i].to;
			double d=!arr[y]?0:dis[t][f]+e[i].val;
			if(dis[y][f]>d){
				dis[y][f]=d;
				if(!vis[y][f]&&y!=H) vis[y][f]=1,q.push(make_pair(y,f));
			}
			if(arr[y]==2&&f<K&&dis[y][f+1]>d/2.0){
				dis[y][f+1]=d/2.0;
				if(!vis[y][f+1]&&y!=H) vis[y][f+1]=1,q.push(make_pair(y,f+1));
			}
		}
	}

	double ret=inf;
	for(int i=0;i<=K;i++)//注意这里不是 dis[H][K]，而是取最小值
		ret=min(ret,dis[H][i]);
	return (ret>=inf?-1:ret);//要判断无解
}
```

全文完。

不过好像大佬有倒着跑分层图 dijkstra 的做法，我太蒻了没想到。

---

## 作者：_ANIG_ (赞：1)

考虑暴力做法，对于每个 $k$，建 $n$ 个点，$(i,j)$ 表示到了第 $i$ 个点使用 $j$ 次除以 $2$ 的最短路，直接 SPFA 即可。

对于 $k$ 很大的，由于每次都是除以 $2$，所以除的次数足够多，前面的和几乎可以忽略不计。也就是当图相同且 $k$ 很大时，实际上与 $k$ 很小时的答案差不多。直接让大于 $100$ 的 $k$ 变成 $100$，再跑 SPFA 就能通过此题。
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
	int to,sum;
};
vector<node>p[100005];
int n,m,k,h;
double f[100005][105];
deque<node>q; 
void add(int x,int y,int z){
	p[x].push_back((node){y,z});
}
double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr) {
	n=N,m=M,k=min(K,100),h=H;
    for(int i=1;i<=n;i++)p[i].clear();
    for(int i=1;i<=n;i++)
    	for(int j=0;j<=k;j++)f[i][j]=1e15;
    for(int i=1;i<=m;i++){
    	add(x[i-1]+1,y[i-1]+1,c[i-1]);
    	add(y[i-1]+1,x[i-1]+1,c[i-1]);
	}
	q.clear();
	q.push_back((node){1,0});
	f[1][0]=0;
	while(q.size()){
		int qq=q.front().to,sm=q.front().sum;
		q.pop_front();
		if(qq==h+1)continue;
		if(arr[qq-1]==0){
			f[qq][sm]=0;
		}
		for(int i=0;i<p[qq].size();i++){
			int c=p[qq][i].to;
			if(f[c][sm]>f[qq][sm]+p[qq][i].sum){
				f[c][sm]=f[qq][sm]+p[qq][i].sum;
				q.push_back((node){c,sm});
			}
			if(arr[c-1]==2&&sm<k&&f[c][sm+1]>(f[qq][sm]+p[qq][i].sum)/2){
				f[c][sm+1]=(f[qq][sm]+p[qq][i].sum)/2;
				q.push_back((node){c,sm+1});
			}
		}
	}
	double res=1e15;
	for(int i=0;i<=k;i++)res=min(res,f[h+1][i]);
	if(res>=1e15)return -1;
	return res;
}
```


---

## 作者：DengDuck (赞：1)

考场上我写了个 97pts 做法，感觉自己像个智障。

不难想到直接跑 SPFA。

具体地，我们想到设 $dis_{i,j}$ 表示从起点到达第 $i$ 个点使用 $j$ 次除二魔法的最少代价。

在最短路的过程中,目前点为 $x$，下一个点为 $y$：

对于 $arr_y=0$ 的点，可以直接将最短路径更新为 $0$。

对于 $arr_y=1$ 的点，进行朴素的最短路更新。

对于 $arr_y=2$ 的点，进行朴素的最短路更新，同时尝试使用除二魔法更新 $dis_{y,j+1}$。

这个过程很暴力，但是在 $k\leq 30$ 的数据过得很轻松。

对于 $k\leq 80$ 的数据我们同样可以这么做，进一步地，我们可以令 $k\gets \min(k,80)$。

这是因为题面给出了一定的误差，$k\leq 10^6$ 除很多，最后和转换后的答案误差不大。

由于我没登上网站，拿不到代码，所以就不贴了。

---

## 作者：Z3k7223 (赞：0)

[更好的阅读体验](https://www.cnblogs.com/Z3k7223/p/18917145)

可能是第一次最优解？写发题解纪念一下。

## Solution

观察到 $K\le 30$ 占了 $97$ 分，盲猜后面的是诈骗。

由于“将已经累积的权值减半”这种操作比较抽象，考虑将其转化为比较好做的操作。反向建图，从终点倒着走回起点，发现减半操作其实对应着将后面的边权值减半，结合 $K\le 30$ 很容易想到分层图，第 $k$ 层的边权自然是 $w\times2^{-k}$，同时这样建图后还可以看出当 $k$ 过大时 $w\times2^{-k}$ 已经可以忽略不计了，实际上当 $K$ 取到 $70$ 左右时就已经有 $\sum w_{\max}\times2^{-k}\le 10^{-6}$ 了，故 $K$ 可以与 $70$ 取 $\min$。

然后考虑归零操作，注意到原图上任意一个可归零的点都可当作起点，则在反图上这些点都可当作终点。

额外要注意的是，由于不允许离开终点，还要特判掉从家不经过终点无法走到零点的情况，这个是可以预处理的。

那么就做完了，提一些小优化：

1. 可以不用直接把 $mK$ 大小的图建出来，在跑 Dij 的时候再把边权推出来。
2. 由于我们找的是单个源点到一个集合的任意一点的最短路，由 Dij 的贪心特性，到达第一个集合内的点即可退出。

时间复杂度 $O(mK\log nK)$，正常写法就拿下最优解。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(x,y)(n*(x)+(y))
const int N=1e5+10;
const long double inf=2e18,eps=1e-7;
struct node{
	int v;
	long double w;
	friend bool operator<(node x,node y){
		return x.w>y.w;
	}
};
struct edge{
	int v;
	long double w;
	int nxt;
}e[N<<1];
long double dis[N*72];
long double t[72];
bool vis[N];
int tot,head[N];
void add(int u,int v,long double w){
	e[++tot]={v,w,head[u]};
	head[u]=tot;
}
void bfs(int s,int h){
	queue<int>q1;
	q1.push(s);
	vis[s]=1;
	while(!q1.empty()){
		int x=q1.front();
		q1.pop();
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].v;
			if(!vis[v]&&v!=h){
				vis[v]=1;
				q1.push(v);
			}
		}
	}
}
void dij(int s,int n,int k,vector<int>&arr){
	priority_queue<node>q2;
	for(int i=0;i<=f(k,n);i++){
		dis[i]=inf;
	}
	q2.push({s,0});
	dis[s]=0;
	while(!q2.empty()){
		node tmp=q2.top();
		q2.pop();
		int x=tmp.v;
		long double val=tmp.w;
		if(val>dis[x]){
			continue;
		}
		if(x%n==0||(!arr[x%n]&&vis[x%n])){
			return;
		}
		for(int i=head[x%n];i;i=e[i].nxt){
			int v=f(x/n,e[i].v);
			long double w=e[i].w/t[x/n];
			if(e[i].v==s){
				continue;
			}
			if(dis[v]>dis[x]+w+eps){
				dis[v]=dis[x]+w;
				q2.push({v,dis[v]});
			}
			if(arr[v%n]==2&&x/n<k){
				v=f(x/n+1,e[i].v);
				if(dis[v]>dis[x]+w+eps){
					dis[v]=dis[x]+w;
					q2.push({v,dis[v]});
				}
			}
		}
	}
}
double solve(int n,int m,int k,int h,vector<int>u,vector<int>v,vector<int>w,vector<int>arr){
	k=min(k,70);
	t[0]=1;
	for(int i=1;i<=k;i++){
		t[i]=t[i-1]*2.0;
	}
	for(int i=0;i<n;i++){
		head[i]=0;
		vis[i]=0;
	}
	for(int i=0;i<m;i++){
		add(u[i],v[i],w[i]);
		add(v[i],u[i],w[i]);
	}
	bfs(0,h);
	dij(h,n,k,arr);
	long double ans=inf;
	for(int i=0;i<n;i++){
		if((i&&arr[i])||!vis[i]){
			continue;
		}
		for(int j=0;j<=k;j++){
			ans=min(ans,dis[f(j,i)]);
		}
	}
	if(ans>1e18){
		ans=-1;
	}
	return ans;
}
```

---

## 作者：liugh_ (赞：0)

[P9370 [APIO2023] 赛博乐园 / cyberland](https://www.luogu.com.cn/problem/P9370)

主要讲了一些**细节和实现上的要点**（如有手误还请海涵）。坑点很多，但做完后真的很爽！

---

给定一包含 $N$ 个点的无向图和长度为 $N$ 的序列 $arr$。

- 若 $arr_u=0$，**到达**点 $u$ 时可将当前走过的**路径长度**变为 $0$。
- 若 $arr_u=1$，到达点 $u$ 时当前走过的路径长度不变。
- 若 $arr_u=2$，**到达**点 $u$ 时可将当前走过的**路径长度**除以 $2$。

其中将路径长度除以 $2$ 的次数不得超过给定的 $K$，求单源最短路。

---

注意到路径长度有可能变为 $0$ 或除以 $2$ 导致路径长度变小（类似负权边的作用），不满足 bfs 的性质，不能直接跑最短路。

先看除以 $2$ 的解决方法。考虑分层图，同时注意排序时**以层数为第一关键字，距离为第二关键字**，这样保证了先把当前层的所有点走完，使得同一层内路径长度递增，同时走到下一层时也无法重新回到上一层，保证了正确性。

再看变为 $0$ 的解决方法。考虑建立超源，向点 $1$ 和**满足条件**的点连一条边权为 $0$ 的边，因为把路径长度变为 $0$ 等价于从这个点出发跑最短路。关键在于哪些点是**满足条件**的？

>一旦你到达赛博乐园，你就不能移动到其他任何地方。

比如下面的 hack，如果超源向点 $3$ 连边，会得到错误的答案 $1$，可以发现只有穿过点 $2$ 才能得到这个答案，因此我们考虑用一个 dfs 预处理出所有从点 $1$ 出发、不经过点 $H$ 能到达的、$arr_u=0$ 的点 $u$，这些点才是满足条件的。

```
3 2 0
1
1 1 0
0 1 2
1 2 1
```

最后，关于 $K\le 10^6$，注意到边权最大为 $10^9$，最多 $10^5$ 条边，精确度为 $10^{-6}$，故除以 $2$ 的操作最多有 $\log_2 10^{9+5-(-6)}=\log_2 10^{20}\approx 70$ 次是对答案有贡献的，故取 $K'=\min(K,70)$ 即可。总复杂度 $O((N+M)K'\log MK')$。

---

一些优化：

- 给**分层图**加边时，仅当 $u\ne H$ 时，才加入边 $(u,v)$，可以减少一些边数，同时省去了后面跑最短路时的特判。
- 从超源向满足条件的点连边时，只用连第 $0$ 层的点，因为可用的层数越多，答案显然不会更劣。

其他的一些坑点：

- dfs 前加的是原图中的边，dfs 后最好将前向星清空，重新给分层图加边。
- 到达一个点时才会触发其能力，故加边时边的 $op$ 要根据边指向的点来取，详见代码。
- 注意 0-index。
- 原图是无向图，建分层图别加漏边。

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace lgh {

const int Maxn = 8e6 + 5, Maxm = 2e7 + 5, Maxk = 70 + 5;
const double inf = 1e18;

struct Edge {int to, pre, w, op;};
Edge eg[Maxm * 2]; int index = 1, head[Maxn];
void adde(int u, int v, int w, int op) {eg[++index] = {v, head[u], w, op}; head[u] = index;}

int N, K, H, S, rt[Maxn], lv[Maxn];
#define id(i, k) ((i) + (k) * N)

struct Node {
	double d; int x;
	friend bool operator< (const Node &a, const Node &b) {
		if (lv[a.x] != lv[b.x]) return lv[a.x] > lv[b.x];
		return a.d > b.d;
	}
};
double dis[Maxn];
bool vis[Maxn];
void dij() {
	fill(dis, dis + S + 1, inf);
	fill(vis, vis + S + 1, 0);
	priority_queue<Node> q;
	dis[S] = 0;
	q.push({dis[S], S});
	while (q.size()) {
		int u = q.top().x;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u], v, w; i; i = eg[i].pre) {
			v = eg[i].to, w = eg[i].w;
			if (eg[i].op == 1) {
				if (dis[u] + w < dis[v]) {
					dis[v] = dis[u] + w;
					q.push({dis[v], v});
				}
			}
			else {
				if ((dis[u] + w) / 2.0 < dis[v]) { // 注意是整个路径长度除以2，而不是这条边的边权除以2
					dis[v] = (dis[u] + w) / 2.0;
					q.push({dis[v], v});
				}
			}
		}
	}
}

void dfs(int u) {
	if (u == H) return; // 到达H就要回溯，保证了满足条件的点一定是能从点1出发不经过点H所能到达的
	for (int i = head[u]; i; i = eg[i].pre) 
		if (!vis[eg[i].to]) vis[eg[i].to] = 1, dfs(eg[i].to);
}

void init() {
	fill(head, head + S + 1, 0), index = 1;
	fill(vis, vis + S + 1, 0);
}

} using namespace lgh;

double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr) {
	init();
	K = min(K, 70), H++, S = id(N, K) + 1;
	lgh::N = N, lgh::K = K, lgh::H = H;
	for (int i = 1; i <= N; ++i) 
		for (int k = 0; k <= K; ++k)
			rt[id(i, k)] = i;
	for (int i = 1; i <= N; ++i) 
		for (int k = 0; k <= K; ++k)
			lv[id(i, k)] = k;
	
	for (int i = 1; i <= M; ++i) {
		adde(x[i - 1] + 1, y[i - 1] + 1, c[i - 1], 1);
		adde(y[i - 1] + 1, x[i - 1] + 1, c[i - 1], 1);
	}
	vis[1] = 1, dfs(1);
	if (!vis[H]) return -1;

	fill(head, head + S + 1, 0); // 清空前向星，由于我在最短路的时候不加特判，所以这里若不清空会有H的出边存在，影响答案
	adde(S, 1, 0, 1); // 为方便，建立超级源点向点1和满足条件的点连边权为0的边
	for (int i = 1; i <= N; ++i) 
		if (arr[i - 1] == 0 && vis[i]) adde(S, i, 0, 1);
	for (int i = 1, u, v, w; i <= M; ++i) {
		u = x[i - 1] + 1, v = y[i - 1] + 1, w = c[i - 1];
		if (u != H) { // H不能有出边
			adde(u, v, w, 1);
			for (int k = 1; k <= K; ++k) 
				adde(id(u, k), id(v, k), w, 1);
			if (arr[v - 1] == 2) { // 指向的点是否有除以2的能力
				for (int k = 1; k <= K; ++k) 
					adde(id(u, k - 1), id(v, k), w, 2);
			}
		}
		if (v != H) { // 同上
			adde(v, u, w, 1);
			for (int k = 1; k <= K; ++k) 
				adde(id(v, k), id(u, k), w, 1);
			if (arr[u - 1] == 2) { // 同上
				for (int k = 1; k <= K; ++k)
					adde(id(v, k - 1), id(u, k), w, 2);
			}
		}
	}
	dij();
	double ans = inf;
	for (int k = 0; k <= K; ++k) ans = min(ans, dis[id(H, k)]);
	return ans;
}
```

---

## 作者：许多 (赞：0)

前置知识：[分层图](https://www.luogu.com.cn/blog/xuduo-cyj/xue-xi-bi-ji-qian-tan-fen-ceng-tu)。

这题确实是分层图好题。

这个题有两种特殊功能，一个可以让当前总通过时间为 $0$。一个拥有让当前总通行时间除以 $2$ 的能力，除以二的能力最多用 $k$ 次。

我们先看第一个特殊能力，也就是 $arr[i]=0$，实际上就是把这个点当做起点跑最短路，但注意题目还有一个要求，就是一旦到达重点，就不能移动到其他任何地方。所以我们先跑一遍 DFS 找到所有不经过终点就能到达的点，如果终点不能到达，输出 $-1$，如果能到达，将起点和 $arr[i]=0$ 的点放入队列跑多源最短路。

我们再看第二种特殊能力，也就是 $arr[i]=2$，很显然的想法，我们对于每个与这种点连边的点，向下一层的 $i$ 连一个特殊的边，经过这条边时就将总通过时间除以二，但有一点，就是他是将**总时间**除以二，所以我们在跑 dijkstra 时应当**以层数以第一关键词，边权为第二关键词**，因为对于下一层的点，**可能到达这个点所花费的时间要低于上一层的点**，这就跟负边权类似。为了避免这种情况，我们要将层数以第一关键词，边权为第二关键词，因为上一层的最短路是相对独立的，我们可以先将上层的最短路跑完，再去跑下一层的最短路。

这题说起来比较复杂，代码上也有很多细节，建议大家在**建边的时候**终点不向其他点连边。

这题有点难度，放完整代码。

# code


```cpp
#include<bits/stdc++.h>
#include<cstdio>
//#include "cyberland.h"
#define n 100010
#define k 70
#define ar(now) arr[now-1]
using namespace std;
struct node{
    int to,w,next;
}b[n*300];
int cnt=0;
struct node2{
    int to;
    double fnow;
};
const double inf=1e24;
int nn,hh;
bool operator<(node2 a1,node2 a2){
    if((a1.to-1)/nn==(a2.to-1)/nn)return a1.fnow>a2.fnow;
    return (a1.to-1)/nn>(a2.to-1)/nn;
}
bool operator>(node2 a1,node2 a2){
    if((a1.to-1)/nn==(a2.to-1)/nn)return a1.fnow<a2.fnow;
    return (a1.to-1)/nn<(a2.to-1)/nn;
}
double f[n*k];
int vis[n*k],head[n*k];
void add(int u,int v,int w){
    b[cnt].to=v;
    b[cnt].w=w;
    b[cnt].next=head[u];
    head[u]=cnt++;
}
priority_queue<node2>q;
inline void dfs(int now){
    vis[now]=1;
    if(now==hh)return ;
    for(int i=head[now];i!=-1;i=b[i].next)
        if(!vis[b[i].to]&&b[i].w>0)
            dfs(b[i].to);
    return ;
}
double solve(int N, int M, int K, int H, std::vector<int> x, std::vector<int> y, std::vector<int> c, std::vector<int> arr){
    K=min(K,68);
    H++;
    nn=N;hh=H;
    for(int i=0;i<M;i++)
        x[i]++,y[i]++;
    for(int i=1;i<=(N+1)*(K+1);i++)f[i]=inf,vis[i]=0,head[i]=-1;
    for(int i=0;i<M;i++){
        for(int j=0;j<=K;j++){
            if(x[i]!=H)add(j*N+x[i],j*N+y[i],c[i]);
            if(y[i]!=H)add(j*N+y[i],j*N+x[i],c[i]);
            if(ar(x[i])==2&&j!=K&&y[i]!=H)
                add(j*N+y[i],(j+1)*N+x[i],-c[i]);
            if(ar(y[i])==2&&j!=K&&x[i]!=H)
                add(j*N+x[i],(j+1)*N+y[i],-c[i]);//这里我对于向下一层的的边连负边权，表示需要/2，具体见最短路
        }
    }
    dfs(1);
    if(!vis[H])return -1;
    for(int i=1;i<=N;i++){
        if((vis[i]&&ar(i)==0)||i==1)
            f[i]=0,q.push((node2){i,0});
        vis[i]=0;
    }
    while(!q.empty()){
        int now=q.top().to;q.pop();
        if(vis[now])continue;
        vis[now]=1;
        for(int i=head[now];i!=-1;i=b[i].next){
            double d=(b[i].w<0? (f[now]-b[i].w)*1.0/2.0:f[now]+b[i].w);
            //如果边权是负的，我们就需要将总时间/2
            if(d<f[b[i].to]){
                f[b[i].to]=d;
                if(!vis[b[i].to])q.push((node2){b[i].to,d});
            }
        }
    }
    double ans=inf;
    for(int i=0;i<=K;i++)ans=min(ans,f[H+i*N]);
    return ans;
}
```

闲话：邻接表被卡了，真的很慢。

[邻接表](https://www.luogu.com.cn/record/128059465)。


[链式前向星](https://www.luogu.com.cn/record/128063213)。



---

