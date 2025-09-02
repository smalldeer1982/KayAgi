# Distance Tree (easy version)

## 题目描述

This version of the problem differs from the next one only in the constraint on $ n $ .

A tree is a connected undirected graph without cycles. A weighted tree has a weight assigned to each edge. The distance between two vertices is the minimum sum of weights on the path connecting them.

You are given a weighted tree with $ n $ vertices, each edge has a weight of $ 1 $ . Denote $ d(v) $ as the distance between vertex $ 1 $ and vertex $ v $ .

Let $ f(x) $ be the minimum possible value of $ \max\limits_{1 \leq v \leq n} \ {d(v)} $ if you can temporarily add an edge with weight $ x $ between any two vertices $ a $ and $ b $ $ (1 \le a, b \le n) $ . Note that after this operation, the graph is no longer a tree.

For each integer $ x $ from $ 1 $ to $ n $ , find $ f(x) $ .

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1632E1/bde039035f2fc0c7e75fd7b5909dff635e928d1e.png) In the first testcase: - For $ x = 1 $ , we can an edge between vertices $ 1 $ and $ 3 $ , then $ d(1) = 0 $ and $ d(2) = d(3) = d(4) = 1 $ , so $ f(1) = 1 $ .
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

## 作者：EricWan (赞：15)

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

## 作者：Cocoly1990 (赞：2)

[Problem - E1 - Codeforces](https://codeforces.ml/contest/1632/problem/E1)

发现对于某个 $x$，所有深度 $<x$ 的点不需要考虑，所以直接把有贡献的点拉出来跑虚树就好。

猜结论，发现肯定连 1，另一端在**有效点直径**上的二分中点左右。这个结论可以利用反证法轻松证明。

令 $f_x$ 表示深度 $>x$ 的所有节点，则对于某个 $x$，应该有 $ans\geq \lceil \frac{f_{ans}}{2}+x\rceil$.

该不等式的意义：大概就是把深度 $>ans$ 的所有节点建虚树，直径中点和 1 拉链的结果，显然每次询问对深度 $\leq ans$ 的节点没有优化效果，所以正确性显然。

因为边权是 $1$，所以 `vector` 存图，直接 dfs 求 $f$ 即可。

发现 $f_x$ 是单调递减的，发现此时 $ans$ 是单增的（显然的），直接双指针枚举即可。

上面是 Hard 的做法， Easy 的话可能真就每次暴力建虚树跑直径，然后最短路做，时间复杂度大概是 $\mathcal{O}\left(n^2\log n\right)$ 的，毕竟是稀疏图，所以清空还算方便，不过写起来还没 Hard 简单。

[Submission #145618714 - Codeforces](https://codeforces.ml/contest/1632/submission/145618714)



---

## 作者：UperFicial (赞：1)

> [**CF1632E1 Distance Tree (easy version & hard version)**](https://www.luogu.com.cn/problem/CF1632E1)

> 解题报告。

> [**不一定更好的阅读体验**](https://www.cnblogs.com/UperFicial/p/16741006.html)。

~~E2 没有地方交了所以就交到 E1 了。~~

震撼挺大的一道题，钦定 $1$ 为根。

先把 $x$ 固定下来，连边的一个端点必定为 $1$ 号点，这样能影响的路径长度最大。

那么现在问题变成，连一条 $1\to u$ 的边，使得 $\max(d_v)$ 尽量小。

后面那个完全可以二分一手，设 $\max(d_u)\le L$，那么问题变成，是否存在一个 $u$，使得添加一条 $1\to u$ 的边后，$\max(d_v)\le L$。

在添加边之前，$d_v\le L$ 的边不用考虑，只需要考虑 $\max(d_v)>L$ 的边。

添加 $1\to u$ 这条边后，影响的是 $u$ 子树内的点，所以考虑一个 $u$ 子树内的点 $v$，$d_v$ 变化为 $x+\operatorname{dis}(u,v)$。

把这个带入二分答案的式子，可以得到 $x+\operatorname{dis}(u,v)\le L$，即 $\operatorname{dis}(u,v)\le L-x$，不等式右边可看做常数项，这个不等式成立的条件可看做最远两个点的成立，那么所有点都成立。

所以问题又转化为，添加一条 $1\to u$ 的边后，$\max_{1\le v\le n}\{\operatorname{dis}(u,v)\}$ 最小是多少。

推到这个问题时我就不会做了，菜逼。当然你把相应的点拉出来建虚树 E1 就做完了。

下面继续考虑 $\Theta(1)$ check 这个问题，也就是 E2 做法。

这个其实也很好做，考虑两个点 $a,b$ 满足 $d_a>L\land d_b>L$，且 $a,b$ 距离 $D$ 尽可能的大。

那么我们直接将 $u$ 放到 $a,b$ 的中点上，然后检查路径长度 $x+\lceil\dfrac{D}{2}\rceil$ 是否 $\le L$，即 $\lceil\dfrac{D}{2}\rceil\le L-x$。

这个的正确性很好证明。

采用反证法，假设存在一个点 $v$ 使得 $\operatorname{dis}(1,v)>L$，也就是 $\operatorname{dis}(u,v)>L-x\ge \lceil\dfrac{D}{2}\rceil$。

考虑这个式子的实际意义，即，当以 $u$ 为根时，$\operatorname{dis}(a,v)=\operatorname{dis}(u,a)+\operatorname{dis}(u,v)>\lceil\dfrac{D}{2}\rceil+\lceil\dfrac{D}{2}\rceil+1\ge D$，矛盾。

代码实现方面，我们对于二分的 $L$，预处理出 $f_i$ 表示 $d_j>i$ 的点集距离最大的两点距离，这个倒推做可以做到 $\Theta(n)$。

最终复杂度 $\Theta(n\log n)$。

---

## 作者：mango2011 (赞：0)

本文将介绍如何通过 E1 和 E2，~~其实是因为 E2 题解已经满了~~。

首先来说一下一个朴素的想法，就是加入的边的两端一定有一个是 $1$，这是因为如果说我们随意找一条其他的路径，都容易进行调整得到更优的结果。

顺着上面的思路继续往下，我们可以想到：

对于 $1\sim n$ 中的每一个 $i$，我们考虑二分答案 $m(1\le m\le \max\{d\})$，重点在于如何检查：

显然，我们只需要再找一个点 $u(2\le u\le n)$，在 $1$ 与 $u$ 之间连一条边。思考一下加入这条边的意义：

1) 对于 $d(v)\le m$ 的节点 $v$，这一次加边没有意义。
2) 对于 $d(v)>m$ 的节点 $v$，只能依靠这一条边，即 $\operatorname{dis}(u,v)+i\le m$，就相当于 $\operatorname{dis}(u,v)\le m-i$，然后问题就转化为如何求 $\max(\operatorname{dis}(u,v))$，以及如何求最优的节点 $v$。我们可以考虑通过预处理解决这个问题：从节点的深度从大到小依次插入，对于每一个 $t$，维护出深度 $\ge t$ 的节点构成的“部分树”的直径。然后在每一次检查当中，我们就取 $u$ 为当前直径的中点（如果有两个，都要取）进行 check 即可。

于是，我们就解决了这个问题，如果说每次都重新二分是 $O(n\log^2 n)$（[好像无法通过](https://codeforces.com/contest/1632/submission/288434312)），但是考虑到答案从左到右的单调性，可以优化到 $O(n\log n)$（[可以通过](https://codeforces.com/contest/1632/submission/288435867)）。

最后对上面的一些做法补充一点细节：

1) 怎样每插入一个点就更新直径？这是容易的，设原本的直径为 $(s,e)$，要插入 $v$，那么只需要找出这三个点中距离最大的一对即可，可以用反证法进行证明。
2) 为什么一定是取直径的中点？这个可以用反证法进行证明，但是还有一种比较感性的理解方式：就是比如说直径是一条链，然后上面长了一堆树杈。然后搞了一个中点，显然不存在一根树杈比中点到两端的距离都要大，于是就可以理解了。

感谢观看！

---

## 作者：SmileMask (赞：0)

喵喵题。

连边最优的定是 $(1,t)$，不妨考虑固定 $x$ 时 $ans$ 成立的条件：

- $dist(1,i)\le ans \bigvee dist(i,t)+x\le ans$ 

不好直接统计 $ans$，类似于 T-shirt，前者对后者不好处理不妨考虑处理后者对前者的情况，也就是枚举 $ans$，统计对 $x$ 的贡献，由于 $ans$ 一定贡献的是前缀，所以我们要最小化 $dist(S,t)$，这里 $S$ 记为 $dist(1,i) > ans$ 的点集。

在普通树上显然为 $\lceil\frac{len}{2} \rceil$，$len$ 为直径长度，到点集上即为端点在点集内的直径 $L$，答案即为 $\lceil\frac{L}{2} \rceil$。

由于从小到大删点不好做，改为从大到小枚举变成加点，考虑动态维护直径端点，看是否能替换某个端点使得答案变大。

复杂度为 $O(n\log n)$。
```cpp
const int N=3e5+10;

int n,fa[N][21],dep[N];
int ans[N],mx;
vector <int> G[N],vec[N];

void dfs(int u,int par){
	fa[u][0]=par,vec[dep[u]].pb(u);
	mx=max(mx,dep[u]);
	for(int i=1;i<=20;i++)
		fa[u][i]=fa[fa[u][i-1]][i-1];
	for(int v:G[u])
		if(v^par) dep[v]=dep[u]+1,dfs(v,u);
}

int LCA(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=20;~i;i--)
		if(dep[fa[u][i]]>=dep[v]) 
			u=fa[u][i];
	if(u==v) return u;
	for(int i=20;~i;i--)
		if(fa[u][i]!=fa[v][i])
			u=fa[u][i],v=fa[v][i];
	return fa[u][0];
}

int dist(int u,int v){
	return dep[u]+dep[v]-2*dep[LCA(u,v)];
}

void Main(){
	n=rd,mx=0;
	for(int i=0;i<=n;i++)
		dep[i]=ans[i]=0,G[i].clear(),vec[i].clear();
	for(int i=0;i<=n;i++)
		for(int j=0;j<=20;j++)
			fa[i][j]=0;
	for(int i=1,u,v;i<n;i++)
		u=rd,v=rd,G[u].pb(v),G[v].pb(u);
	dfs(1,0);for(int i=1;i<=n;i++) ans[i]=mx;
	int A=-1,B=-1,C=0;
	for(int Ans=n-1;Ans>=0;Ans--){
		for(int x:vec[Ans+1]){
			if(A==-1){A=x;continue;}
			if(B==-1){B=x;C=dist(A,B);continue;}
			int dist1=dist(A,x);
			int dist2=dist(B,x);
			if(C<dist1&&dist1>=dist2)
				C=dist1,B=x;
			else if(C<dist2&&dist2>=dist1)
				C=dist2,A=x;
		}
		int tmp=(C+1)/2;
		int idx=Ans-tmp;
		if(idx>0) ans[idx]=min(ans[idx],Ans);
	}
	for(int i=n-1;i;i--) 
		ans[i]=min(ans[i],ans[i+1]);
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	puts("");
}
```

---

