# Distance Tree (hard version)

## 题目描述

This version of the problem differs from the previous one only in the constraint on $ n $ .

A tree is a connected undirected graph without cycles. A weighted tree has a weight assigned to each edge. The distance between two vertices is the minimum sum of weights on the path connecting them.

You are given a weighted tree with $ n $ vertices, each edge has a weight of $ 1 $ . Denote $ d(v) $ as the distance between vertex $ 1 $ and vertex $ v $ .

Let $ f(x) $ be the minimum possible value of $ \max\limits_{1 \leq v \leq n} \ {d(v)} $ if you can temporarily add an edge with weight $ x $ between any two vertices $ a $ and $ b $ $ (1 \le a, b \le n) $ . Note that after this operation, the graph is no longer a tree.

For each integer $ x $ from $ 1 $ to $ n $ , find $ f(x) $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1632E2/bde039035f2fc0c7e75fd7b5909dff635e928d1e.png) In the first testcase: - For $ x = 1 $ , we can an edge between vertices $ 1 $ and $ 3 $ , then $ d(1) = 0 $ and $ d(2) = d(3) = d(4) = 1 $ , so $ f(1) = 1 $ .
- For $ x \ge 2 $ , no matter which edge we add, $ d(1) = 0 $ , $ d(2) = d(4) = 1 $ and $ d(3) = 2 $ , so $ f(x) = 2 $ .

## 样例 #1

### 输入

```
3
4
1 2
2 3
1 4
2
1 2
7
1 2
1 3
3 4
3 5
3 6
5 7```

### 输出

```
1 2 2 2 
1 1 
2 2 3 3 3 3 3```

# 题解

## 作者：EricWan (赞：16)

miaomiao problem

这是一篇非常详细的有图有证明题解。

## 思考 $a$ 在哪

### 结论：$a=1$

考虑反正：

假设我们 $a,b\ne1$，像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/qchtnx7u.png)

不妨设加边之前 $d(a)\le d(b)$，那么加完边后如果边对最终答案有贡献，那么 $a$ 一定可以通过这条边对 $b$ 进行松弛，换句话说，这条边有用当且仅当 $d(a)+x\le d(b)$。但是如果我们链接 $1$ 和刚才的 $b$，这条边有用当且仅当 $d(1)+x\le d(b)$。发现 $d(1)=0<d(a)$，即把 $a$ 换成 $1$ 一定不会劣。

## 思考 $b$ 在哪

题目问的是最大距离的最小值，想到~二分~。

也对，这也可以二分，我们就来想想如果写这个 check 函数。

对于目前已经设定好的一个答案 $mid$，$d(v)\le mid$ 的点成为放心点（这里用棕色），否咋叫做闹心点（这里用红色）。

![](https://cdn.luogu.com.cn/upload/image_hosting/e573w6df.png)

容易想到，在这个 check 函数中我们可以先确定一个 $b$，然后返回 $[\max_{v\in\mathtt{闹心点}}dis(b,v)\le mid-x]$。

我们称由闹心点和两两闹心点之间简单路径上的点组成的联通子图为“闹心树”。

### 结论：$b$ 为闹心树的直径的最中间位置的任意一点

先设闹心树直径为 $D$。

![](https://cdn.luogu.com.cn/upload/image_hosting/f54kwkka.png)

**前置结论：**\
假设上图横着的那个链是一个直径，闹心点的代价 $\max_{v\in\mathtt{闹心点}}d(b)+dis(b,v)=\max_{v\in\mathtt{闹心点}}x+dis(b,v)=\max\{dis(b,d_1),dis(b,d_2)\}=x+\lfloor\frac{D+1}2\rfloor$，其中 $d_1$ 和 $d_2$ 为选中的直径的端点。\
证明这个前置结论可以反证，假设还有闹心点 $v$ 使得 $x+dis(b,v)>x+\max\{dis(b,d_1),dis(b,d_2)\}$ 如上图，那么 $dis(b,v)>dis(b,d_2)$，因此直径就是 $d_1\leftrightarrow\dots\leftrightarrow v$，$d_1\leftrightarrow\dots\leftrightarrow d_2$ 不可能是直径，与假设矛盾。

**开始证明这个求 $b$ 的结论：**\
还是考虑反正：假设我们找到了一个不是闹心树的任意一直径的最中间位置的任意一点的一个比上面选的 $b$ 还要优的一个结点 $b_{good}$ 使得 $\max_{v\in\mathtt{闹心点}}d(b_{good})+dis(b_{good},v)<\max_{v\in\mathtt{闹心点}}d(b)+dis(b,v)$。那么我们可以发现 $b_{good}$ 到 $d_1$ 或者 $d_2$，一定会至少经过一段长度为 $\lfloor\frac{D+1}2\rfloor$ 闹心树的直径的字段。我们在**前置结论一**中证明了结论中的 $b$ 的代价恰好是 $x+\max\{dis(b,d_1),dis(b,d_2)\}$，而 $b_{good}$ 的代价至少是 $x+\max\{dis(b,d_1),dis(b,d_2)\}$，因此选择结论中的 $b$ 肯定不会劣与 $b_{good}$，然而我们假设找到了严格优于 $b$ 的 $b_{good}$，因此矛盾。

## 怎样计算答案

对于一个目前枚举到的 $x$，我们二分答案（后面会说怎么优化）。暴力找出闹心点和闹心树，跑树形 DP 或两遍 DFS 求直径。时间复杂度 $O(n^2\log n)$，然后你就可以通过 $[450,1500]$ pts 的 E1。

## 两个优化

### 第一个优化

观察~样例输出~随便一棵树，我们发现随着我们的答案的增加（或者说限制的放宽），我们 $x$ 可以变得越来越大。也就是说，随着 $x$ 越来越大，答案不降。

因此我们可以考虑使用双指针之类的东西（我是枚举答案然后计算 $\lfloor\frac{D+1}2\rfloor$，和答案比大小后计算最大的可行 $x$，这样似乎好写一点），一个标记目前的 $x$，一个标记答案，因此我们的这个 $\log n$ 就没了。

### 第二个优化

后面我们需要通过考虑两次 DFS 求直径把复杂度降下去。

我们第一次 DFS 选择以 $1$ 为根，可以发现得到的与 $1$ 最近的点一定是最后一个变得不再闹心的点之一。

我们还有一个结论，就是这个点一定是任意时刻的闹心树直径之一的端点之一。

证明：闹心树中一定有且仅有一个距离 $1$ 最近的点（这就是闹心点的 LCA，很好证），闹心树为以这个“闹心树跟”为根的子树，那么闹心树中距离闹心树根最远的点一定是一个合法的直径端点。证毕。

因此我们直接维护所有闹心点到这个最闹心点的距离即可，距离这个最闹心的点最远的仍然闹心的点和这个最闹心的点的距离就是闹心树直径长度。（维护这个就随便选一个 $O(1)$ 删或加单点，$O(1)$ 查最值的数据结构即可）

这样，每一个闹心点只会变成放心点，因此总复杂度为 $O(n)$。

优美的屎山两题都是一遍过（不想加注释了，代码请自行理解）：

```cpp
// Problem: Distance Tree (easy version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1632E1
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
#define MAXN 300005
using namespace std;
int T, n, dis[MAXN], ans[MAXN], dep[MAXN];
vector<int> e[MAXN], box[MAXN];
void dfs(int u, int k, int *Dis) {
	Dis[u] = k;
	for (int v : e[u])
		if (!Dis[v])
			dfs(v, k + 1, Dis);
}
int getdis(int id, int *Dis) {
	for (int i = 1; i <= n; i++)
		Dis[i] = 0;
	dfs(id, 1, Dis);
	int maxn = 0, maxni = id;
	for (int i = 1; i <= n; i++) {
		Dis[i]--;
		if (Dis[i] > maxn) {
			maxn = Dis[i];
			maxni = i;
		}
	}
	return maxni;
}
signed main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) {
			ans[i] = n;
			e[i].clear();
			box[i].clear();
		}
		for (int i = 1, a, b; i < n; i++) {
			cin >> a >> b;
			e[a].push_back(b);
			e[b].push_back(a);
		}
		int maxdep = getdis(1, dep);
		getdis(maxdep, dis);
		ans[n] = dep[maxdep];
		for (int i = 1; i <= n; i++)
			box[dep[i]].push_back(i);
		for (int i = n, D = 0; i >= 0; i--) {
			if ((D + 1) / 2 <= i)
				ans[i - (D + 1) / 2] = min(ans[i - (D + 1) / 2], i);
			for (int j : box[i])
				D = max(D, dis[j]);
		}
		for (int i = n - 1; i >= 1; i--)
			ans[i] = min(ans[i], ans[i + 1]);
		for (int i = 1; i <= n; i++)
			cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：GaryH (赞：12)

# CF1632E1&E2 题解

**题意**：

给一棵初始边权为 $1$ 的树，对于所有 $x\in[1,n]$，求：

若能添一条权为 $x$ 的无向边 $(a,b)$，则 $\max\limits_{i=1}^n(d_i)$ 的最小值是多少，

其中 $d_i$ 等于 点 $1$ 到点 $i$ 的最短路径的长度。

**做法**：

先考虑对于固定 $x$ 后如何计算答案。

首先，问题可以转化为，我们添加的边至少有一个端点是 $1$。

因为，对于一张加了边 $u\leftrightarrow v(u,v>1)$ 的新图 $A$，此处我们假设 $d_u\leq d_v$，

则加了边 $1\leftrightarrow v$ 的新图 $B$ 一定更优。我们通过枚举 $A$ 中的决策来证明：

任意一条 $A$ 中的路径 $p=1\rightarrow\cdots\rightarrow t$，

若 $p$ 中不包含新边 $u\leftrightarrow v$，则 $B$ 方式中也存在路径 $q=p$；

而若 $p$ 中包含新边 $u\leftrightarrow v$，即 $p=1\rightarrow\cdots\rightarrow u\rightarrow v \rightarrow s\rightarrow\cdots\rightarrow t$，

我们能在 $B$ 方式中找到路径 $q=1\rightarrow v \rightarrow s\rightarrow\cdots \rightarrow t$，

其中 $q$ 中经过了新边 $1\rightarrow v$，且 $q$ 的长度必然不大于 $p$ 的长度。

那么我们考虑新问题的做法，这时我们考虑二分答案，那么问题就又转化为：

对于值 $ans$，是否存在一点 $v$，使得加入边 $1\leftrightarrow v$ 后的新图 $G$ 的 $\max\limits_{i=1}^n(d_i)$ 的最小值不大于 $ans$。

那么，原树里 $d_u>ans$ 的点 $u$ 都必须被新边 $1\leftrightarrow v$ 影响而使得 $d'_u\le ans$，

其中 $d'_u$ 是加边后点 $1$ 到点 $u$ 的距离。

再考虑新家的边是如何影响 $d$ 数组的变化的，即加入权为 $x$ 的新边 $1\leftrightarrow v$ 后，我们有：

$\forall u \in[1,n],d'_u=\min(d_u,x+\text{dist}(v,u))$，其中 $dist(v,u)$ 为原树中 $v$ 到 $u$ 的距离。

那么，对于所有满足 $d_u>ans$ 的点 $u$，右式 $dist(v,u)\le ans-x$ 都必须成立。

我们发现，这个 $ans-x$ 的值，与 $u$ 具体是哪个点并没有关系，

故我们只需让 $\max\limits_{u\in[1,n]}(dist(u,v))$ 尽量小即可，而这是一个经典模型，

求解这个模型，我们只需找到一条最长的路径 $a\rightarrow\cdots\rightarrow b$，满足 $d_a,d_b>ans$，

设这条路径的长度是 $len$，则答案 $ans$ 可行当且仅当右式 $x+\lfloor\frac{len+1}{2}\rfloor\le ans$ 成立。

原因是，我们只需将点 $v$ 放在这条路径的中点处，

则对 $\forall u\in[1,n]$，只要满足 $d_u>ans$，就有 $dist(v,u)\le x+\lfloor\frac{len+1}{2}\rfloor$，

否则一定能找到一条新的长为 $len'$ 的路径 $a'\rightarrow\cdots\rightarrow b'$，满足 $d_{a'},d_{b'}>ans$，

其中 $u$ 等于 $a'$ 和 $b'$ 中的一个。

那最后一个问题就是，对于一个固定的 $ans$，如何求上面的 $len$ 值。 

这个倒不难，可以一次预处理出所有 $ans$ 对应的 $len$，方法可以采用树形DP或找直径后直接计算。

时间复杂度是 $O(n\log n)$，瓶颈在二分上。

当然，因为答案的值域也是 $O(n)$ 的，而答案会随着新边边权 $x$ 的上升而上升，

故可以维护一个当前答案 $t$，每次 $x$ 增加时同时维护 $t$ 的值，这样的时间复杂度就是线性的。

**code for** $O(n\log n)$：

```
#define vi vector
#define ckmax(a, b) ((a) = max((a), (b)))
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)

int read () { /*快读*/ }

const int N (3e5 + 10);
int n, rt;
int f[N];
int d[2][N];
vi < int > G[N];
void dfs (int u, int fa, int o) {
	if (fa) d[o][u] = d[o][fa] + 1;
	for (int v : G[u]) if (v ^ fa) dfs (v, u, o);
}
bool chk (int ans, int x) {
	return ans >= min (d[0][rt], x + (f[ans + 1] + 1) / 2);
}
void work() {
	n = read(); int u, v; f[0] = 0;
	rep (i, 1, n) G[i].clear(), f[i] = d[0][i] = d[1][i] = 0;
	rep (i, 2, n) G[u = read()].pb (v = read()), G[v].pb (u);
	dfs (1, 0, 0), rt = max_element (d[0] + 1, d[0] + n + 1) - d[0], dfs (rt, 0, 1);
	rep (i, 1, n) ckmax (f[d[0][i]], d[1][i]);
	per (i, n - 1, 0) ckmax (f[i], f[i + 1]);
	rep (x, 1, n) {
		int L = 0, R = n, ans = n;
		while (L <= R) {
			int Mid = (L + R) >> 1;
			if (chk (Mid, x)) ans = Mid, R = Mid - 1;
			else L = Mid + 1;
		}
		printf ("%d ", ans);
	}
	puts("");
}
int main() {
	int t = read();
	while (t--) work();
	return 0;
}
```



---

## 作者：I_am_Accepted (赞：6)

### Preface

这道题实属妙极，本蒟蒻确实做不出来。

### Analysis

**定义点 $x$ 的“受益”：指增加了那条边后 $d(x)$ 的变化量（减小值）。**

**定义 $dis(x,y)$：在树上 $x,y$ 间的距离。**

显然，贪心地增加这条边：一端选择为 $1$ 节点（设该边为 $(1,a)$），因为这样受益的节点更多，受益也更多。

我们先固定 $X$ 来求 $f(X)$。

假设 $f(X)\le F$，那么原树中深度 $=y(>F)$ 的点一定受益至少 $y-F$ 才行。

发现如果 $a$ 在相对“树干”上，那么有可能有些点的受益不够导致不可行；如果 $a$ 在相对“树枝”上，那么有可能有些点离 $a$ 太远导致不可行。

妙处：设 $S_F=\{x\ |\ dis(1,x)>F\}$（这些点需求受益，必须经过新增的边），寻找点集中在树上距离最大的两点，设为 $(u,v)$，距离为 $w$，这时如果 $\left\lceil\dfrac{w}{2}\right\rceil+X>F$，即 $a$ 取 $(u,v)$ 路径中点时仍然不行，判断出 $f(X)>F$。否则，$f(X)\le F$（Proof A）。

我们 $O(n)$ DFS 预处理出每个 $i$，$S_i$ 内的最大点对距离（只需 DFS 时处理每个节点 深度最大和次大的子树 即可，具体看代码）。

到此我们对于每个 $X\in[1,n]\cap\mathbb{Z}$ 可以 $O(\log n)$ 二分答案求出 $f(X)$，总时间 $O(n\log n)$。

观察到 $f(X)$ 随着 $X$ 递增而递增（非严格），且树的深度不超过 $n$，我们可以 $O(n)$ 做啦！

### Proof A

反证法：假设有一个点 $o$ 使得 $d(o)>F$，则:

$$dis(o,a)>F-X\ge\left\lceil\dfrac{w}{2}\right\rceil$$

将树假想成以 $a$ 为根定根，则 $u,v$ 必定在 $a$ 的两个不同的儿子子树内，$o$ 必然和其中一个不在同一个子树内，设是 $u$，得 $dis(o,u)=dis(o,a)+dis(a,u)\ge \left\lceil\dfrac{w}{2}\right\rceil+1+\left\lfloor\dfrac{w}{2}\right\rfloor>w$。

与 $w$ 的最大性矛盾，故得证。

### Code

[Link](https://codeforces.com/contest/1632/submission/144909024)

---

## 作者：meyi (赞：3)

首先，连出的边的一个端点必定为 $1$，因为以其他点为端点不会使答案变的更优。

假如我们已经得到 $f(x)$，需要反推方案，那么只用考虑深度 $>f(x)$ 的节点，因为对深度 $\le f(x)$ 的节点连边没有意义。

令 $dis_{ans}$ 表示深度 $>ans$ 的节点两两之间的最大距离，则有 $ans\ge\lceil \frac{dis_{ans}}{2}\rceil+x$。

考虑这个不等式的意义，它其实是将深度 $>ans$ 的节点拉出来建了个虚树，然后连了 $(1,直径中点)$ 这条边，这样做显然最优，那么此时的最大深度显然是 $\lceil\frac{dis_{ans}}{2}\rceil+x$，由于 $ans$ 合法，所以有 $ans\ge\lceil\frac{dis_{ans}}{2}\rceil+x$。

由于 $ans$ 增大会使深度 $>ans$ 的节点数量减少，所以 $dis_{ans}$ 是单调减的，这就可以使用二分 $O(n\log n)$ 计算了。

进一步考虑，$x$ 增大只会使 $ans$ 增大，所以直接 $O(n)$  计算就完事了。

$dis$ 的计算及细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxn=3e5+10;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
int dis[maxn];
vector<int>e[maxn];
int dfs(int p,int f,int d){
	ri a=0,b=0;
	for(ri i:e[p])
		if(i!=f){
			ri c=dfs(i,p,d+1)+1;
			if(c>a)b=a,a=c;
			else ckmax(b,c);
		}
	if(b+d)ckmax(dis[b+d-1],(a+b+1)>>1);
	return a;
}
int n,t_case;
int main(){
	scanf("%d",&t_case);
	while(t_case--){
		scanf("%d",&n);
		for(ri i=1;i<=n;++i)dis[i]=0,vector<int>().swap(e[i]);
		for(ri i=1,x,y;i<n;++i){
			scanf("%d%d",&x,&y);
			e[x].push_back(y),e[y].push_back(x);
		}
		ri lim=dfs(1,0,0);
		for(ri i=n-2;~i;--i)ckmax(dis[i],dis[i+1]);
		ri ans=1;
		for(ri i=1;i<=n;++i){
			while(dis[ans]+i>ans)++ans;
			printf("%d%c",min(ans,lim)," \n"[i==n]);
		}
	}
	return 0;
}
```

---

## 作者：kradcigam (赞：2)

题意：有一棵 $n$ 个点的树，每条边长度为 $1$。现在加一条权值为 $x$ 的边，最小化 $f(x) = \max\limits_{i = 1} ^ {n} d_i$。其中 $d_i$ 表示点 $1$ 到点 $i$ 的最短距离。

对于 $x \in [1, n]$，求出 $f(x)$。

$n \leq 3 \times 10 ^ 5$。

首先，为了最优，我们每次添加的边一定是以 $1$ 为端点。（这很显然）

对于添加长度为 $x$ 的边，判断 $f(y) \leq ans$。如果 $dep_y \leq ans$，那么不需要添加边；否则，添加一条 $1$ 到以这个点为最长链上的中点的边。如果路径长度依旧 $>ans$ 则不合法。

我们每次只需要判断最长链（符合要求的直径）是否合法就可以了。证明：如果有另外一条链它的端点深度 $> ans$，且经最长链的中点到根节点距离 $>ans$，那么它就超过要比最长链还长。

代码：

```cpp
#include <bits/stdc++.h>

#define SZ(x) (int)x.size() - 1
#define all(x) x.begin(), x.end()
#define F(i, a, b) for (int i = (a); i <= (b); i++)
#define DF(i, a, b) for (int i = (a); i >= (b); i--)

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template <typename T> inline void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> inline void chkmin(T &x, T y) {x = min(x, y); }
template <typename T> inline void read(T &x) {
	x = 0; int f = 1; char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}

const int N = 3e5 + 10;
vector <int> v[N];
int dep[N], maxn[N];
int dfs(int x, int fa) {
	if (x != 1) dep[x] = dep[fa] + 1;
	int max1 = dep[x], max2 = dep[x];
	for (int i: v[x])
		if (i != fa) {
			int k = dfs(i, x);
			if (k > max1) max2 = max1, max1 = k;
			else chkmax(max2, k);
		}
	int t = min(max1, max2) - 1;
	if (t >= 0) chkmax(maxn[t], max1 + max2 - 2 * dep[x] + 1);
	return max1;
}

signed main() {
	int _; read(_);
	while (_--) {
		int n; read(n);
		F(i, 0, n) v[i].clear(), maxn[i] = 0;
		F(i, 2, n) {
			int x, y; read(x); read(y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		int k = dfs(1, 0);
		DF(i, k - 1, 0) chkmax(maxn[i], maxn[i + 1]);
		int ans = 0;
		F(i, 1, n) {
			while (ans < k && maxn[ans] / 2 + i > ans) ans++;
			cout << ans << " ";
		} cout << endl;
	}
	return 0;
}
```



---

## 作者：MiRaciss (赞：1)

## 题目链接
[link.](https://codeforces.com/problemset/problem/1632/E2)

## 题解

#### 闲话
神仙题当然要神仙来做，拜谢 @Rabbit_Mua 神仙的三句话题解！！！包讲懂的那种！！1

***

首先有一个结论，每一次加边肯定是从 $1$ 连向其他节点。

这个很好证明，因为我们连边的目的是为了让 $d(v)$ 变小，如果在 $u$ 向 $v$ 连边可以让 $d(v)$ 变小，就说明 $d(u)+x<d(v)$，因为 $d(1)<d(u)$，所以  $1$ 可以让 $v$ 变更小。

可以发现，如果所有点的深度经过操作的后小于一个特定值 $ans$ ，那么这些点经过操作后的深度一定小于 $ans+1$。所以说答案有单调性。

答案具有单调性，所以考虑二分。设当前答案为 $mid$，问题就转换为在 $\mathrm {O(1)}$ 的时间内判断是否可以通过加一条长度为 $x$ 的边使得所有点到 $1$ 的距离都小于 $mid$。

如果一些点本身的深度就小于 $mid$ ，那么我们不用管他们，只需要考虑其他深度大于 $mid$ 的点。也许就是下面的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ardhamny.png)


也就是红线以下的点都是我们需要处理的。

如果红线以下的任一点 $i$ 都满足 $d(i)\leq mid$，那么红线下相距最远的两个点也一定满足，手玩一下可以发现这个条件是充要的。所以我们只需要判断能否让红线下距离最远的两个点满足 $d(i)\leq mid$ 即可。

这里有一个结论，就是红线下距离最远的两个点一定在最长链上。所以我们将 $1$ 和直径的中点 $y$ 连一条长度为 $x$ 的边，如果 $x+\lceil \frac{dist}{2}  \rceil \leq mid$，那么红线下距离最远的两个点 $d(i)\leq mid$ 一定成立。

直径可以预处理，我们用两次 $\mathrm{DFS}$ 就好了


红线下点的集合怎么预处理呢？

第一次 $\mathrm {DFS}$ 以后，为了求出直径，我们需要从深度最深的点开始再跑一次 $\mathrm {DFS}$。因为是深度最深的点，所以第二次 $\mathrm{DFS}$  的根节点在二分中是最有可能在 $mid$ 下方的。而且如果有点在 $mid$ 下方，那么这个点**一定**在 $mid$ 下方。所以我们距离最远的两个点有一个**一定**是这个点。那么我们就可以用第二次 $\mathrm {DFS}$ 的结果来表示红点下集合的最长链了。



所以就可以 $\mathrm {O(1)}$ 判断了。


### code.

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> v[300005];
int dep[2][300005];
int Max[300005];

void DFS(int x,int fa,int op){
	for(auto y:v[x]) if(y^fa) 
		dep[op][y]=dep[op][x]+1,DFS(y,x,op);
}

int n;

int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) v[i].clear(),Max[i]=0;
		for(int i=1,x,y;i<n;i++) scanf("%d%d",&x,&y),v[x].push_back(y),v[y].push_back(x);
		dep[0][1]=0;DFS(1,0,0);
		
		int rt=1;
		for(int i=1;i<=n;i++) if(dep[0][rt]<dep[0][i]) rt=i;
		dep[1][rt]=0;DFS(rt,0,1);
		
		for(int i=1;i<=n;i++) Max[dep[0][i]]=max(Max[dep[0][i]],dep[1][i]);
		for(int i=n-1;i>=1;i--) Max[i]=max(Max[i],Max[i+1]);
		
		for(int i=1;i<=n;i++){
			int l=1,r=n,ans=0;
			while(l<=r){
				int mid=(l+r)>>1; 
				if(min(dep[0][rt],(1+Max[mid+1])/2+i)<=mid) r=mid-1,ans=mid;
				else l=mid+1; 
			}
			printf("%d ",ans);
		}
		printf("\n");
	}
	return 0;
}
```






---

## 作者：Cocoly1990 (赞：1)

[Problem - E2 - Codeforces](https://codeforces.ml/contest/1632/problem/E2)

猜结论，发现肯定连 1，另一端在最长链上的二分中点左右。

令 $f_x$ 表示深度 $>x$ 的所有节点，应该有 $ans\geq \lceil \frac{f_{ans}}{2}+x\rceil$.

该不等式的意义：大概就是把深度 $>ans$ 的所有节点建虚树，直径中点和 1 拉链的结果，显然每次询问对深度 $\leq ans$ 的节点没有优化效果，所以正确性显然。

因为边权是 $1$，所以 `vector` 存图，直接 dfs 求 $f$ 即可。

发现 $f_x$ 是单调递减的，发现此时 $ans$ 是单增的（显然的），直接双指针枚举即可。

[Submission #145150606 - Codeforces](https://codeforces.ml/contest/1632/submission/145150606)



---

## 作者：周子衡 (赞：1)

正面做的话应该比较困难。考虑转化一下：对每个 $1\leq v < n$，边权 $x$ 最大是多少，能使得可以在图上加一条边权为 $x$ 的边，满足加边后 $1$ 到任意节点距离都 $\leq v$。

首先可以发现，加的边一定有一个端点为 $1$。这一点留待读者自证。

对于原来到 $1$ 的距离就 $\leq v$ 的节点，加边后距离一定仍然 $\leq v$，我们可以不管。假设我们在 $1$ 和 $u$ 之间加了边，对于每个原来距离 $1$ 超过 $v$ 的点 $k$，显然新图最短路径一定是从 $1$ 到 $u$ 再到 $k$，这就要求

$$
x+\operatorname{dis}(u,k)\leq v
$$

记所有距离 $1$ 超过 $v$ 的节点集合为 $K_v$，我们需要挑出一个 $u$，使得 $u$ 距离 $K_v$ 中节点距离的最大值尽可能小，从而使得 $x$ 尽可能大。而这个 $u$ 明显应取在 $K_v$ 直径的中点（如果中点在边上，那么应当取在该边两端点的任意一端），这个最大值最小即为直径的一半向上取整。此时计算 $x$ 的取值范围即可，注意我们只研究 $x\in [1,n]$ 的情形。

从大到小枚举 $v$，每次朴素地加入所有深度为 $v+1$ 的点，并维护直径的长度以及端点，可以做到 $O(n\log n)$（需要调用 $O(n)$ 次计算树上两点间距离的算法，该算法一般采用 $O(n\log n)-O(\log n)$ 或 $O(n\log n)-O(1)$ 的实现），足够通过本题。官方题解给出的是一种树形 DP 做法，可以做到 $O(n)$。

---

## 作者：chenxinyang2006 (赞：0)

这场赛时没打，赛后抽 2h 做了下题，结果过了 ABDE，不会 C，这是怎么回事呢？

首先把 $1$ 当作根，记 $dis_i$ 表示 $1$ 到 $i$ 的距离，考虑加了这条 $(a,b,x)$ 边的效果

显然加完这条边后，$dis_a,dis_b$ 首先就会改变，但一定是较大的（不妨认为是 $dis_b$）变为 $\min(dis_b,dis_a + x)$，而较小的没有影响

既然只能改变两者中的一个，我们让那个被改变的尽量小显然是好的，也就是说 $dis_a$ 要尽量小，显然 $dis_1 = 0$ 最小，于是加的边一定是 $(1,u)$ 这种形式

然后我们考虑不计算加一条长度为 $x$ 的边答案最小为多少，而是考虑答案为 $v$ 时，$x$ 最大是多少

我们列出答案为 $v$ 时 $x$ 合法的条件，发现所有点必须满足以下两条中至少一条：

- 原本到 $1$ 距离 $\le v$
    
- 到 $u$ 距离 $\le v - x$
   
我们考虑把所有到 $1$ 距离 $\le v$ 的点涂黑，其他点涂白。那么我们需要找到一个 $u$ 点，使得它到所有白点的最大距离最小

因为边权全都是 $1$，所以 $u$ 点就是白点点集直径的中点

从大到小枚举 $v$，每次会有一些黑点变白，然后我们用动态加边维护直径的方式，维护白点点集直径长度即可

code（实现了一些不必要的部分，大体思路类似）：

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int TEST;
int n;

int cnt;
int head[300005];
struct eg{
	int to,nxt;
}edge[600005];

void make(int u,int v){
	edge[++cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}
int d[300005],dep[300005],to[20][300005];

void dfs1(int u,int f){
	dep[u] = dep[f] + 1;
	d[u] = dep[u];
	to[0][u] = f;
	for(int i = head[u];i;i = edge[i].nxt){
		int v = edge[i].to;
		if(v == f) continue;
		dfs1(v,u);
		d[u] = max(d[v],d[u]);
	}
}

int LCA(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	for(int i = 18;i >= 0;i--) if(dep[to[i][u]] >= dep[v]) u = to[i][u];
	if(u == v) return u;
	for(int i = 18;i >= 0;i--){
		if(to[i][u] != to[i][v]){
			u = to[i][u];
			v = to[i][v];
		}
	}
	return to[0][u];
}

int getdis(int u,int v){
	int d = LCA(u,v);
	return dep[u] + dep[v] - 2 * dep[d];
}

vector <int> S[300005];
void dfs2(int u){
	S[dep[u]].push_back(u);
	for(int i = head[u];i;i = edge[i].nxt){
		int v = edge[i].to;
		if(v == to[0][u]) continue;
		dfs2(v);
	}
}
int ans[300005];

void solve(){
	scanf("%d",&n);
	cnt = 0;
	for(int i = 1;i <= n;i++) head[i] = 0;
	for(int i = 1;i <= n;i++) S[i].clear();
	for(int i = 1;i < n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		make(u,v);make(v,u);
	}
	dep[0] = -1;
	dfs1(1,0);
	//for(int i = 1;i <= n;i++) printf("%d fa %d dep %d d %d\n",i,to[0][i],dep[i],d[i]);
	for(int i = 1;i <= n;i++) ans[i] = d[1];
	int rt = -1,se = 0;
	for(int i = head[1];i;i = edge[i].nxt){
		int v = edge[i].to;
		if(rt == -1 || d[v] > d[rt]){
			se = d[rt];
			rt = v;
		}else if(d[v] > se){
			se = d[v];
		}
	}
	for(int i = 1;i <= 18;i++){
		for(int j = 1;j <= n;j++){
			to[i][j] = to[i - 1][to[i - 1][j]];
		}
	}
	//printf("rt %d se %d\n",rt,se);
	dfs2(rt);
	/*for(int i = 1;i <= n;i++){
		printf("depth %d\n",i);
		for(int j = 0;j < S[i].size();j++) printf("%d ",S[i][j]);
		printf("\n");
	}*/
	int A = -1,B = -1,C,dist = 0,t1,t2;
	for(int v = n - 1;v >= 1;v--){
		for(int i = 0;i < S[v + 1].size();i++){
			C = S[v + 1][i];
			if(A == -1){
				A = B = C;
				//printf("modify %d %d\n",A,B);
				continue;
			}
			t1 = getdis(A,C);
			t2 = getdis(B,C);
			if(t1 < t2){
				swap(t1,t2);
				swap(A,B);
			}
			//默认 t1 较大,即 (A,C)
			if(t1 > dist){
				dist = t1;
				B = C;
			}
			//printf("modify %d %d\n",A,B);
		}
		//printf("v=%d (%d,%d)\n",v,A,B);
		t1 = (dist + 1) / 2;
		if(v - t1 >= 0) ans[v - t1] = min(ans[v - t1],v);
		//希望答案 <= v
		//t1 + x <= v
		//x <= v - t1
		//x 最大值为 v - t1
	}
	for(int i = n - 1;i >= 1;i--) ans[i] = min(ans[i],ans[i + 1]);
	for(int i = 1;i <= n;i++) printf("%d ",max(ans[i],se));
	printf("\n");
}

int main(){
	scanf("%d",&TEST);
	while(TEST--) solve();
	return 0;
}
```

这份代码用了一个没什么用的结论：设 $u$ 属于 $1$ 儿子 $f$ 的子树，那么加完 $(1,u)$ 这条边后只有 $f$ 子树内 $dis$ 会改变，于是上面的一部分操作只要在 $f$ 子树内进行便可，但不这样做也是正确的

---

