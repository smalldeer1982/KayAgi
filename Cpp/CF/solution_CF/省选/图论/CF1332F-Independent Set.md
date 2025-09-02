# Independent Set

## 题目描述

Eric 是一名图论课的老师。这天，Eric 上的是关于点独立集和边导出子图的内容。

给出一张图 $G = (V, E)$，一个点独立集是指点的一个子集 $V' \subset V$，满足对于任意一对 $u, v \in V'$，$(u, v) \not \in E$（也就是说，不存在一条 $E$ 中的边，连接的两端点同在 $V'$ 中）。

一个边导出子图包含了边的一个子集 $E' \subset E$，和原图上所有与 $E'$ 中至少一条边有相邻的点。

设有 $E' \subset E$，定义 $G[E']$ 表示一个以 $E'$ 作为边集的边导出子图。这是对于上述定义的一个图例说明：


为了帮助他的学生们熟悉这些定义，Eric 留下了这样一个问题作为练习：

给出一棵树 $G = (V, E)$，对于 $G$ 中所有的非空边导出子图 $H$，计算 $w(H)$ 之和。其中 $w(H)$ 表示 $H$ 中点独立集的种类数。形式化地说，求 $\sum \limits_{\emptyset \not= E' \subset E} w(G[E'])$。

为了向 Eric 展现你比他的学生们都要厉害，请你尽可能快地求出正确答案。注意答案可能很大，你需要输出它对 $998, 244, 353$ 取模的值。

## 样例 #1

### 输入

```
2
2 1```

### 输出

```
3```

## 样例 #2

### 输入

```
3
1 2
3 2```

### 输出

```
11```

# 题解

## 作者：George1123 (赞：8)

# 题解-Independent Set

## [博客中阅读](https://www.cnblogs.com/Wendigo/p/12611937.html#F)

> [Independent Set](https://codeforces.com/contest/1332/problem/F)

> 给定树 $G=(V,E)$，$n$ 个点。令 $E'\in E$，求所有 $E'$ 所有边上的节点的独立集数量之和 $\bmod 998244353$（独立集大小可以为 $0$，$E'\neq\varnothing$）。

> 数据范围：$2\le n\le 3\times10^5$。

这么简单的树形 $\texttt{dp}$ 我竟然不会，而且想了好久，我太蒻了。

**设 $f_{o,i}$ 表示：**

1. 如果 $o=0$：$i$ 点**选或不选都可以**，但是连接 $i$ 号点与父亲节点的边**不存在**的 $i$ 的子树中的答案。
2. 如果 $o=1$：$i$ 点**不选**，连接 $i$ 号点与父亲节点的边**存在**的 $i$ 的子树中的答案。
3. 如果 $o=2$：$i$ 点**选**，连接 $i$ 号点与父亲节点的边**存在**的 $i$ 的子树中的答案。

> 以上“答案”均包括选的边为空的情况。

如果该节点**选**，子节点不与该节点连边或者不选是允许的：

$$f_{2,i}=\prod_{to\in i's~sons}(f_{0,to}+f_{1,to})$$

如果该节点**不选**，子节点怎么样都是允许的：

$$f_{1,i}=\prod_{to\in i's~sons}(f_{0,to}+f_{1,to}+f_{2,to})$$

如果该节点不与父亲节点连边，包括**选或不选的情况**，但是要排除所有子节点都不与该节点连边的情况（要不然节点孤立，就不是边两端的点了）：

$$f_{0,i}=f_{1,i}+f_{2,i}-\prod_{to\in i's~sons}f_{0,to}$$

因为答案不应包括选的边为空的情况，而且根节点不与父亲节点连边（根节点的父亲节点不存在），所以最终答案为 $f_{0,1}-1$。

**代码：**

```cpp
//Data
const int N=300000,m=998244353;
int n;
vector<lng> f[3];
vector<vector<int> > e;

//Dfs
il void Dfs(re int x,re int fa){
	f[0][x]=f[1][x]=f[2][x]=1;
	for(re int to:e[x])if(to!=fa){
		Dfs(to,x);
		(f[0][x]*=f[0][to])%=m;
		(f[1][x]*=(f[0][to]+f[1][to]+f[2][to]))%=m;
		(f[2][x]*=(f[0][to]+f[1][to]))%=m;
	}
	f[0][x]=(f[1][x]+f[2][x]-f[0][x]+m)%m;
}

//Main
int main(){
	scanf("%d",&n);
	e.resize(n+7);
	for(re int i=0;i<3;i++) f[i].resize(n+7);
	for(re int i=1,u,v;i<n;i++)
		scanf("%d%d",&u,&v),e[u].pb(v),e[v].pb(u);
	Dfs(1,0);
	printf("%lld\n",(f[0][1]+m-1)%m);
	return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：AutumnKite (赞：5)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

[题目传送门](https://codeforces.com/contest/1332/problem/F)

### 题意

对于一个无向图 $G=(V,E)$，一个**独立集**是一个 $V$ 的子集 $V'$，满足对于所有 $u,v\in V'$，有 $(u,v)\not\in E$。

一个**边导出子图**是由边集 $E$ 的一个子集 $E'$ 以及所有在 $E'$ 的边中出现至少一次的点组成的。

给定一棵树 $G=(V,E)$，我们定义 $G[E']$ 表示边集为 $E'$ 时 $G$ 的边导出子图，$w(G)$ 表示图 $G$ 的独立集数量。求
$$\sum_{E'\subset E, E'\ne \varnothing} w(G[E'])$$

$n\le 3\times 10^5$，答案对 $998\,244\,353$ 取模。

### 题解

对于一棵树求独立集数量，这个问题可以用简单的 DP 解决。

在这个问题中，无非就是多了另外一个决策——断边。我们仍然考虑使用 DP 去解决这个问题。首先我们强制以 $1$ 为根。

设 $f_{u,0/1,0/1}$ 表示以 $u$ 为根的子树，$u$ 与父亲的边在/不在边导出子图内，$u$ 在/不在独立集内时的方案数。转移如下：
$$
\begin{aligned}
f_{u,1,1} &= \prod_{v\in \operatorname{son}(u)} (f_{v,0,0}+f_{v,0,1}+f_{v,1,0}) \\
f_{u,1,0} &= \prod_{v\in \operatorname{son}(u)} (f_{v,0,0}+f_{v,0,1}+f_{v,1,0}+f_{v,1,1}) \\
f_{u,0,1} &= \prod_{v\in \operatorname{son}(u)} (f_{v,0,0}+f_{v,0,1}+f_{v,1,0}) - \prod_{v\in \operatorname{son}(u)} (f_{v,0,0}+f_{v,0,1})\\
f_{u,0,0} &= \prod_{v\in \operatorname{son}(u)} (f_{v,0,0}+f_{v,0,1}+f_{v,1,0}+f_{v,1,1})
\end{aligned}
$$

当 $u$ 的连边都不在边导出子图内时也是合法的，但是此时 $u$ 不能选在独立集内，所以 $f_{u,0,1}$ 的转移需要减去所有与儿子的边都不在子图内的情况，而 $f_{u,0,0}$ 不需要减。

最后答案即为 $f_{1,0,0}+f_{1,0,1}-1$（减 $1$ 是减去边集为空的情况）。

时间复杂度 $O(n)$。

### 代码

```cpp
const int N = 300005, P = 998244353;
int n;
std::vector<int> E[N];
int f[N][2][2];
void dfs(int u, int fa = 0){
	int mul = 1;
	f[u][1][0] = f[u][1][1] = 1;
	for (int v : E[u])
		if (v != fa){
			dfs(v, u);
			f[u][1][0] = 1ll * f[u][1][0] * (0ll + f[v][0][0] + f[v][0][1] + f[v][1][0] + f[v][1][1]) % P;
			f[u][1][1] = 1ll * f[u][1][1] * (0ll + f[v][0][0] + f[v][0][1] + f[v][1][0]) % P;
			mul = 1ll * mul * (0ll + f[v][0][0] + f[v][0][1]) % P;
		}
	f[u][0][1] = (f[u][1][1] - mul + P) % P;
	f[u][0][0] = f[u][1][0];
}
void solve(){
	read(n);
	for (register int i = 1; i <= n; ++i) E[i].clear();
	for (register int i = 1, u, v; i < n; ++i)
		read(u), read(v), E[u].push_back(v), E[v].push_back(u);
	dfs(1);
	print((0ll + f[1][0][0] + f[1][0][1] + P - 1) % P);
}
```


---

## 作者：Mirasycle (赞：2)

如果枚举每一个子图计算的话，必然会重复计算信息，导致复杂度增大。假设 $G' \subset G$，我们可以发现对于 $G'$ 的计算和 $G$ 中 $G'$ 的计算除了子图 $G'$ 的根节点外其余都相同。于是我们设出状态 $f_{i,0/1/2}$ 分别表示 $i$ 作为子图根节点的时候的答案，与父节点联通时 $i$ 点的不选或者选。于是有
$$f_{u,1}=\prod(f_{v,0}+f_{v,1}+f_{v,2})$$
$$f_{u,2}=\prod(f_{v,0}+f_{v,1})$$ 
$$f_{u,0}=f_{u,1}+f_{u,2}\textcolor{blue}{-\prod f_{v,0}}$$
注意蓝笔部分，因为题目中子图是通过边集定义的，而题目要求边集不为空，所以子图就不能由一个点构成。

---

## 作者：Tweetuzki (赞：2)

### 题意

给出一棵 $n ~ (2 \le n \le 3 \cdot 10 ^ 5)$ 的树，求其所有 $2 ^ {n  - 1} - 1$ 种非空的边导出子图中，点独立集个数之和。对 $998\ 244\ 353$ 取模。

### 题解

我写的似乎是一种很奇怪的做法，转移非常冗杂。

首先考虑如果所有边都保留，点独立集个数如何求。

这是一个树上 DP，类似 [没有上司的舞会](https://www.luogu.com.cn/problem/P1352)。以 $1$ 号点为根转成有根树，设 $f_{u, 0 / 1}$ 表示处理完了 $u$ 子树内，$u$ 是否选择的方案数。枚举儿子是否选择进行转移，把那题的取 $\max$ 改成求和就好了。

考虑当边可以断开时，会发生什么样的变化。

- 相邻的两个点可以都进行选择，只要断开中间的那条边。
- 当一个点周围的所有边都被断开时，这个点会在图中被删除，相当于必须不选择。

我们再增加一维，$f_{u, 0/1, 0/1}$ 表示处理完了 $u$ 子树内，$u$ 是否选择，$u$ 从儿子上来的边是否全部断开。

接下来讨论当儿子 $v$ 的答案加入 $u$ 时，怎样进行转移。为了方便，我们设加入前 $u$ 的 DP 数组为 $g_{0/1, 0/1}$。

---

$f_{u, 0, 0}$ 表示不选择 $u$，且从儿子上来的边没有全部被断开。首先分原来情况如何进行讨论，再分 $v$ 的情况进行讨论：
  - $g_{0, 0}$：原来 $u$ 就有从儿子上来的边，那么此时 $u - v$ 的边删不删无所谓，无强制性要求。
    - $f_{v, 0, 0}$：不选择 $v$ 且 $v$ 肯定不会成为孤立点。那么此时 $u - v$ 这条边选不选都是可行的。因此对 $f_{u, 0, 0}$ 贡献为 $2 \times f_{v, 0, 0} \times g_{0, 0}$。
    - $f_{v, 0, 1}$：不选择 $v$ 且 $v$ 可能成为孤立点。选择 $u - v$ 这条边显然没问题；若不选择这条边，相当于让 $v$ 成为孤立点，也就是 $v$ 强制不选择，这与 DP 状态中 “不选择 $v$” 相符，所以也是可以转移的。因此对 $f_{u, 0, 0}$ 贡献为 $2 \times f_{v, 0, 1} \times g_{0, 0}$。
    - $f_{v, 1, 0}$：选择 $v$ 且 $v$ 肯定不会成为孤立点。那么此时 $u - v$ 这条边选不选都是可行的。因此对 $f_{u, 0, 0}$ 贡献为 $2 \times f_{v, 1, 0} \times g_{0, 0}$。
    - $f_{v, 1, 1}$：选择 $v$ 且 $v$ 肯定不可能成为孤立点。此时只有选择 $u - v$ 这条边是可行的，若不选择，则会与状态矛盾（原因见上文 $f_{v, 0, 1}$ 转移部分）。因此对 $f_{u, 0, 0}$ 贡献为 $f_{v, 1, 1} \times g_{0, 0}$。
  - $g_{0, 1}$：原来 $u$ 没有从儿子上来的边，此时有了，说明 $u - v$ 这条边一定选择。
    - $f_{v, 0, 0}$：不选择 $v$ 且 $v$ 肯定不会成为孤立点。显然选择 $u - v$ 这条边可行。因此对 $f_{u, 0, 0}$ 贡献为 $f_{v, 0, 0} \times g_{0, 1}$。
    - 剩下三种状态类似，都在对 $g_{0, 0}$ 转移分析中认为可行，对答案都有系数为 $1$ 的贡献。重复的分析省略。

---

$f_{u, 0, 1}$ 表示不选择 $u$，且从儿子上来的边全部被断开。类似的进行分类讨论分析：
  - $g_{0, 0}$：原来 $u$ 有从儿子上来的边，但此时要求没有从儿子上来的边，条件不符合。这一大类直接被剪去。
  - $g_{0, 1}$：原来 $u$ 就断开了所有儿子上来的边，那么此时 $u - v$ 的边同样需要断开。
    - $f_{v, 0, 0}$：不选择 $v$ 且 $v$ 肯定不会成为孤立点。显然选择 $u - v$ 这条边可行。因此对 $f_{u, 0, 1}$ 贡献为 $f_{v, 0, 0} \times g_{0, 1}$。
    - 仔细观察，发现这段和 $f_{u, 0, 0}$ 内 $g_{0, 1}$ 的转移是完全一样的，故这里也略过。

---

$f_{u, 1, 0}$：表示选择 $u$，且从儿子上来的边没有全部被断开。分类讨论如下：
  - $g_{1, 0}$：原来 $u$ 就有从儿子上来的边，那么此时 $u - v$ 的边删不删无所谓，无强制性要求。
    - $f_{v, 0, 0}$：不选择 $v$ 且 $v$ 肯定不会成为孤立点。那么此时 $u - v$ 这条边选不选都是可行的。因此对 $f_{u, 1, 0}$ 贡献为 $2 \times f_{v, 0, 0} \times g_{1, 0}$。
    - $f_{v, 0, 1}$：不选择 $v$ 且 $v$ 可能成为孤立点。根据上文分析 $u - v$ 这条边选不选都是可行的。因此对 $f_{u, 1, 0}$ 贡献为 $2 \times f_{v, 0, 1} \times g_{1, 0}$。
    - $f_{v, 1, 0}$：选择 $v$ 且 $v$ 肯定不会成为孤立点。此时由于点独立集的限制，这条边必须断开。因此对 $f_{u, 1, 0}$ 贡献为 $f_{v, 1, 0} \times g_{1, 0}$。
    - $f_{v, 1, 1}$：选择 $v$ 且 $v$ 可能成为孤立点。若不断开边，会违反点独立集的限制；若断开边，会违反孤立点的限制。因此这里无法进行转移。
  - $g_{1, 1}$：原来 $u$ 没有从儿子上来的边，此时有了，说明 $u - v$ 这条边一定选择。
    - $f_{v, 0, 0}$：不选择 $v$ 且 $v$ 肯定不会成为孤立点。显然选择 $u - v$ 这条边可行。因此对 $f_{u, 1, 0}$ 贡献为 $f_{v, 0, 0} \times g_{1, 1}$。
    - $f_{v, 0, 1}$：不选择 $v$ 且 $v$ 可能成为孤立点。显然选择 $u - v$ 这条边可行。因此对 $f_{u, 1, 0}$ 贡献为 $f_{v, 0, 1} \times g_{1, 1}$。
    - 上下两种状态由于点独立集的限制，都不满足条件，无法进行转移。

---

$f_{u, 1, 1}$：表示选择 $u$，且从儿子上来的边全部被断开。
  - $g_{1, 0}$：原来 $u$ 有从儿子上来的边，但此时要求没有从儿子上来的边，条件不符合。这一大类直接被剪去。
  - $g_{1, 1}$：原来 $u$ 就断开了所有儿子上来的边，那么此时 $u - v$ 的边同样需要断开。
    - $f_{v, 0, 0}$：不选择 $v$ 且 $v$ 肯定不会成为孤立点。显然断开 $u - v$ 这条边可行。因此对 $f_{u, 1, 1}$ 的贡献为 $f_{v, 0, 0} \times g_{1, 1}$。
    - $f_{v, 0, 1}$：不选择 $v$ 且 $v$ 可能成为孤立点。断开 $u - v$ 这条边可行。因此对 $f_{u, 1, 1}$ 的贡献为 $f_{v, 0, 1} \times g_{1, 1}$。
    - $f_{v, 1, 0}$：选择 $v$ 且 $v$ 肯定不会成为孤立点。断开 $u - v$ 这条边可行。因此对 $f_{u, 1, 1}$ 的贡献为 $f_{v, 1, 0} \times g_{1, 1}$。
    - $f_{v, 1, 1}$：选择 $v$ 且 $v$ 可能成为孤立点。因为必须断开这条边，这就不满足孤立点的限制。因此这里无法进行转移。

于是就讨论完了，码就完事了。最后的答案为 $f_{1, 0, 0} + f_{1, 0, 1} + f_{1, 1, 0} - 1$（因为有减去空集的情况，而且 $f_{1, 1, 1}$ 存在 $1$ 号点作为孤立点却被选择所以不合法）。

时间复杂度 $\mathcal{O}(n)$。
  
代码：

```cpp
#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
 
const int MaxN = 300000;
const int Mod = 998244353;
 
struct Graph {
  int cnte;
  int Head[MaxN + 5], To[MaxN * 2 + 5], Next[MaxN * 2 + 5];
 
  inline void addEdge(int from, int to) {
    cnte++; To[cnte] = to;
    Next[cnte] = Head[from]; Head[from] = cnte;
  }
};
 
int N;
int Fa[MaxN + 5], F[MaxN + 5][2][2];
Graph Gr;
 
inline int add(int x, int y) { return (x += y) >= Mod ? x - Mod : x; }
inline int sub(int x, int y) { return (x -= y) < 0 ? x + Mod : x; }
inline int mul(int x, int y) { return 1LL * x * y % Mod; }
inline int pw(int x, int y) { int z = 1; for (; y; y >>= 1, x = mul(x, x)) if (y & 1) z = mul(z, x); return z; }
inline int inv(int x) { return pw(x, Mod - 2); }
inline int sep(int x, int y) { return mul(x, inv(y)); }
inline void inc(int &x, int y = 1) { x = add(x, y); }
inline void dec(int &x, int y = 1) { x = sub(x, y); }
 
void init() {
  scanf("%d", &N);
  for (int i = 1; i < N; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    Gr.addEdge(u, v);
    Gr.addEdge(v, u);
  }
}
 
void dfs(int u) {
  F[u][0][1] = F[u][1][1] = 1;
  for (int i = Gr.Head[u]; i; i = Gr.Next[i]) {
    int v = Gr.To[i];
    if (v == Fa[u]) continue;
    Fa[v] = u;
    dfs(v);
    int f[2][2];
    f[0][0] = F[u][0][0], f[0][1] = F[u][0][1], f[1][0] = F[u][1][0], f[1][1] = F[u][1][1];
    F[u][0][0] = add(mul(f[0][0], add(add(mul(F[v][0][0], 2), mul(F[v][0][1], 2)), add(mul(F[v][1][0], 2), F[v][1][1]))), mul(f[0][1], add(add(F[v][0][0], F[v][0][1]), add(F[v][1][0], F[v][1][1]))));
    F[u][0][1] = mul(f[0][1], add(add(F[v][0][0], F[v][1][0]), F[v][0][1]));
    F[u][1][0] = add(mul(f[1][0], add(add(mul(F[v][0][0], 2), mul(F[v][0][1], 2)), F[v][1][0])), mul(f[1][1], add(F[v][0][0], F[v][0][1])));
    F[u][1][1] = mul(f[1][1], add(add(F[v][0][0], F[v][1][0]), F[v][0][1]));
  }
  // printf("f[%d] = (%d, %d, %d, %d)\n", u, F[u][0][0], F[u][0][1], F[u][1][0], F[u][1][1]);
}
 
void solve() {
  dfs(1);
  printf("%d\n", sub(add(add(F[1][0][0], F[1][1][0]), F[1][0][1]), 1));
}
 
int main() {
  init();
  solve();
  return 0;
}
```

---

## 作者：hegm (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1332F)

太水了这道题，完全配不上紫。

转化成求子图满足每个选的点至少在一个大小为 $2$ 的连通块内部。

对于每个满足上述条件的子图求独立集方案数。

考虑 `dp`，设 $f_{i,0/1,0/1}$ 表示考虑 $i$ 子树内 $i$ 一定选并且子树内合法前提下，当前 $i$ 所在连通块是否大小为 $2$ 以上，$i$ 在独立集上是否是黑色。

$p_i$ 表示 $i$ 的子树内，不选 $i$ 并且子树内合法的方案数。

转移非常之简单和水。

### $\text{CODE}$

```cpp

#include<bits/stdc++.h>
#define fi first
#define se second
#define ull unsigned long long
#define make make_pair
#define N 300005
#define mod 998244353
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n,f[N][2][2],g[2][2],p[N];
int add(int a,int b){return (1ll*a+b)%mod;}
int mul(int a,int b){return (1ll*a*b)%mod;}
vector<int> v[N];
void dfs(int now,int fa)
{
	f[now][0][0]=1;
	f[now][0][1]=1;
	p[now]=1;
	for(int x:v[now])
	{
		if(x==fa)continue;
		dfs(x,now);
		memcpy(g,f[now],sizeof(g));
		memset(f[now],0,sizeof(f[now]));
		f[now][0][0]=mul(g[0][0],add(f[x][1][1],add(f[x][1][0],p[x])));
		f[now][0][1]=mul(g[0][1],add(f[x][1][1],add(f[x][1][0],p[x])));
		f[now][1][0]=add(mul(g[1][0],add(add(f[x][1][1],f[x][1][0])*2,add(f[x][0][1],add(f[x][0][0],p[x])))),mul(g[0][0],add(add(f[x][1][1],f[x][1][0]),add(f[x][0][0],f[x][0][1]))));
		f[now][1][1]=add(mul(g[1][1],add(add(f[x][1][1],f[x][1][0]*2),add(f[x][0][0],p[x]))),mul(g[0][1],add(f[x][0][0],f[x][1][0])));
		p[now]=mul(p[now],add(f[x][1][0],add(f[x][1][1],p[x])));
	}
}
signed main()
{
	n=read();
	for(int i=1,a,b;i<n;i++)
	{
		a=read();b=read();
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(1,0);
	cout<<(1ll*add(f[1][1][0],add(f[1][1][1],p[1]))-1+mod)%mod;
	return 0;
}

```

---

## 作者：Forever1507 (赞：1)

## CF1332F

简要题意：求一棵树的所有非空边导出子图的独立集个数之和。

注意到一个点在不在导出子图里以及在不在独立集内都是重要的，因此记 dp 状态 $f_{i,0/1,0/1}$ 表示以 $i$ 为根节点的子树，节点 $i$ 不在/在独立集中，节点 $i$ 与父亲的连边不在/在导出子图中。

考虑转移：

```
f[cur][0][0]=f[cur][0][0]*(f[to][0][0]+f[to][1][0]+f[to][0][1]+f[to][1][1])%mod;
f[cur][1][0]=f[cur][1][0]*(f[to][0][0]+f[to][0][1]+f[to][1][1])%mod;
f[cur][0][1]=f[cur][0][1]*(f[to][0][0]+f[to][1][0]+f[to][0][1]+f[to][1][1])%mod;
f[cur][1][1]=f[cur][1][1]*(f[to][0][0]+f[to][0][1]+f[to][1][1])%mod;
```

第一行和第三行，因为我自己没有选所以我的儿子随便怎么选都是对的，全部加上去即可。

第二行和第四行，因为我自己选了，所以如果我的儿子没有断开与父亲的连边那么就不能出现在独立集里。

当然还存在一种特殊情况，就是说，如果我断开了与父亲的连边，然后我的儿子也全部断开了与我的连边，那么我就成为了一个非法的孤立点，因此需要扣掉子节点断开连边的方案的乘积，**但是**只有 $i$ 在独立集中才要扣掉，因为 $i$ 不在独立集中的情况需要用来作为虚拟节点来统计选择若干子节点中的独立集中的方案数，因此不能剪掉（此题最关键的部分，我想了很久/ll）

据此，直接在树上转移即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int N=3e5+5,mod=998244353;
int n;
vector<int>nbr[N];
int f[N][2][2];
void dfs(int cur,int fa){
    for(int i=0;i<=1;++i)for(int j=0;j<=1;++j)f[cur][i][j]=1;
    int tmp=1;
    for(auto to:nbr[cur]){
        if(to==fa)continue;
        dfs(to,cur);
        f[cur][0][0]=f[cur][0][0]*(f[to][0][0]+f[to][1][0]+f[to][0][1]+f[to][1][1])%mod;
        f[cur][1][0]=f[cur][1][0]*(f[to][0][0]+f[to][0][1]+f[to][1][1])%mod;
        f[cur][0][1]=f[cur][0][1]*(f[to][0][0]+f[to][1][0]+f[to][0][1]+f[to][1][1])%mod;
        f[cur][1][1]=f[cur][1][1]*(f[to][0][0]+f[to][0][1]+f[to][1][1])%mod;
        tmp=tmp*(f[to][0][1]+f[to][1][1])%mod;
    }
    f[cur][1][1]=(f[cur][1][1]-tmp+mod)%mod;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1;i<n;++i){
        int u,v;
        cin>>u>>v;
        nbr[u].push_back(v);
        nbr[v].push_back(u);
    }
    dfs(1,0);
    cout<<(f[1][0][1]+f[1][1][1]-1)%mod;
    return 0;
}
```

---

## 作者：Lynkcat (赞：1)

简单树形 dp。

设状态 $dp_{i,0/1/2}$ 分别表示：

$dp_{i,0}$ 表示第 $i$ 个点选入了导出子图中但不选入独立集时 $i$ 子树内的方案数

$dp_{i,1}$ 表示第 $i$ 个点选入了导出子图中并选入独立集时 $i$ 子树内的方案数。

$dp_{i,2}$ 表示第 $i$ 个点是否选入导出子图需要其父亲连向其的那条边确定时子树内的方案数。

对于 $dp_{i,0}$ ，当有一个新子树 $u$ 加入时，更新过程是

$$dp_{i,0}=dp_{i,0}\times (dp_{u,0}+dp_{u,1}+dp_{u,2})+dp_{i,0}\times(dp_{u,0}+dp_{u,1}+dp_{u,2}\times 2)$$

前面一部分是 $i$ 不与 $u$ 连边的情况，后面反之。

对于 $dp_{i,1}$ ，当有一个新子树 $u$ 加入时，更新过程是

$$dp_{i,1}=dp_{i,1}\times (dp_{u,0}+dp_{u,1}+dp_{u,2})+dp_{i,1}\times(dp_{u,0}+dp_{u,2})$$

前面一部分是 $i$ 不与 $u$ 连边的情况，后面反之。

对于 $dp_{i,2}$ ，当有一个新子树 $u$ 加入时，更新过程是

$$dp_{i,2}=dp_{i,2}\times (dp_{u,0}+dp_{u,1}+dp_{u,2})$$

注意这里算 $dp_{i,0}$ 和 $dp_{i,1}$ 的时候也把 $dp_{i,2}$ 的情况包括进去了，所以 $dp_{i,0}-=dp_{i,2},dp_{i,1}-=dp_{i,2}$。
	
最后答案为 $dp_{1,0}+dp_{1,1}+dp_{1,2}-1$，要减去每个点都不选入导出子图的情况。
```
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define foor(i,a,b) for (int i=(a);i<=(b);i++)
#define door(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define IOS ios::sync_with_stdio(false)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf 1000000005
#define mod 998244353
#define int ll
#define N 300005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,dp[N][5];
int ans;
vector<int>G[N];
void ad(int x,int y)
{
	G[x].push_back(y);
}
void dfs(int k,int fa)
{
	dp[k][0]=1;
	dp[k][1]=1;
	dp[k][2]=1;
	for (auto u:G[k])
	{
		if (u==fa) continue;
		dfs(u,k);
		dp[k][0]=(dp[k][0]*(dp[u][0]+dp[u][1]+dp[u][2])%mod+dp[k][0]*(dp[u][0]+dp[u][1]+dp[u][2]*2)%mod)%mod;
		dp[k][1]=(dp[k][1]*(dp[u][0]+dp[u][1]+dp[u][2])%mod+dp[k][1]*(dp[u][0]+dp[u][2])%mod)%mod;
		dp[k][2]=(dp[k][2]*(dp[u][0]+dp[u][1]+dp[u][2])%mod);
	}
	dp[k][0]=(dp[k][0]-dp[k][2]+mod)%mod;
	dp[k][1]=(dp[k][1]-dp[k][2]+mod)%mod;
}
signed main()
{
	n=read();
	for (int i=1;i<n;i++)
	{
		int u=read(),v=read();
		ad(u,v);
		ad(v,u);
	}
	dfs(1,0);
	writeln(((dp[1][0]+dp[1][1]+dp[1][2])%mod-1+mod)%mod);
}
/*

*/
```



---

## 作者：LTb_ (赞：1)

[更好的阅读体验](http://lycltb.top/post/solution-cf1332f/)

纪念第一道自己写出来的 *2500

不妨假设根节点为 $1$。

考虑 $dp$：设 $dp_{i,x,y}$ ( $x,y \in [0,1]$ ) 表示以 $i$ 为根的子树内，是否选 $i$ 上面的边 ( $x$ )，是否选节点 $i$ ( $y$ ) 的答案。

“是否选 $i$ 上面的边”的意思是 连接 $i$ 与 $i$ 的父节点的边 是否包括在当前这个边导出子图中。

“是否选节点 $i$”的意思是节点 $i$ 是否包括在当前这个点独立集中。

考虑转移：
$$
dp_{i,0,0}=\prod\limits_{j\in son_i} dp_{j,0,0}+dp_{j,0,1}+dp_{j,1,0}+dp_{j,1,1}
$$
$$
dp_{i,1,0}=\prod\limits_{j\in son_i} dp_{j,0,0}+dp_{j,0,1}+dp_{j,1,0}+dp_{j,1,1}
$$
$$
dp_{i,1,1}=\prod\limits_{j\in son_i} dp_{j,0,0}+dp_{j,0,1}+dp_{j,1,0}
$$
$dp_{i,0,1}$ 的转移稍微复杂一点：
$$
dp_{i,0,1}=\left(\prod\limits_{j\in son_i} dp_{j,0,0}+dp_{j,0,1}+dp_{j,1,0}\right)
-
\left( \prod\limits_{j\in son_i} dp_{j,0,1}+dp_{j,0,0} \right)
$$
如果节点 $i$ 在子图中，而这个点 $i$ 上方的边又不在子图中，那么需要它的一个子节点提供一条边使得它在子图中。于是考虑补集转化，用总方案数减去没有边连向节点 $i$ 的方案数，即得到上式。

注意题目中给出的是 **非空** 边导出子图，最后答案要减一。

```cpp
// 2020.11.22
// Code by LTb
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define debug puts("QwQ");
inline int read(){
    int x=0,f=1;
    char ch;
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}

const int MAXN=300005;
const int MOD=998244353;
int n;
vector<int> v[MAXN];
int dp[MAXN][2][2];
//          边　点
bool vis[MAXN];

void dfs(int p){
	// 选点选边：选点不选边 / 选边不选点 / 不选边不选点
	// 不选点选边：选点不选边 / 选边不选点 / 不选边不选点 / 选点选边
	// 不选点不选边：选点不选边 / 选边不选点 / 不选边不选点 / 选点选边
	// 选点不选边：选点不选边 / 选边不选点 / 不选边不选点 - 选点不选边 / 不选边不选点
	vis[p]=true;
	int cnt1=1,cnt2=1,cnt0=1;
	for (int i:v[p]){
		if (vis[i]) continue;
		dfs(i);
		cnt1=cnt1*(dp[i][0][1]+dp[i][0][0]+dp[i][1][0])%MOD;
		cnt2=cnt2*(dp[i][0][1]+dp[i][0][0]+dp[i][1][0]+dp[i][1][1])%MOD;
		cnt0=cnt0*(dp[i][0][1]+dp[i][0][0])%MOD;
	}

	dp[p][1][0]=dp[p][0][0]=cnt2;
	dp[p][1][1]=cnt1;
	dp[p][0][1]=(cnt1-cnt0+MOD)%MOD;
}

signed main()

{
	n=read();
	for (int i=1;i<n;i++){
		int x=read(),y=read();
		v[x].push_back(y);
		v[y].push_back(x);
	}

	dfs(1);
	cout<<((dp[1][0][1]+dp[1][0][0]+MOD-1)%MOD)<<endl;
	return 0;
}
```



---

