# [AGC043C] Giant Graph

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc043/tasks/agc043_c

$ N $ 頂点の、それぞれ $ M_1 $, $ M_2 $, $ M_3 $ 辺の単純な無向グラフ $ X $, $ Y $, $ Z $ が与えられます。 頂点をそれぞれ $ x_1,\ x_2,\ \dots,\ x_N $, $ y_1,\ y_2,\ \dots,\ y_N $, $ z_1,\ z_2,\ \dots,\ z_N $ とします。 $ X $, $ Y $, $ Z $ の辺はそれぞれ $ (x_{a_i},\ x_{b_i}) $, $ (y_{c_i},\ y_{d_i}) $, $ (z_{e_i},\ z_{f_i}) $ です。

$ X,\ Y,\ Z $ を元に $ N^3 $ 頂点の無向グラフ $ W $ を作ります。 $ X,\ Y,\ Z $ から $ 1 $ つずつ頂点を選ぶ方法は $ N^3 $ 通りありますが、これがそれぞれ $ W $ の頂点と一対一に対応します。$ x_i,\ y_j,\ z_k $ を選ぶことに対応する頂点を $ (x_i,\ y_j,\ z_k) $ で表すこととします。

$ W $ の辺を、以下の手順に沿って張ります。

- $ X $ の各辺 $ (x_u,\ x_v) $、及び全ての $ w,\ l $ について、$ (x_u,\ y_w,\ z_l) $, $ (x_v,\ y_w,\ z_l) $ 間に辺を張る
- $ Y $ の各辺 $ (y_u,\ y_v) $、及び全ての $ w,\ l $ について、$ (x_w,\ y_u,\ z_l) $, $ (x_w,\ y_v,\ z_l) $ 間に辺を張る
- $ Z $ の各辺 $ (z_u,\ z_v) $、及び全ての $ w,\ l $ について、$ (x_w,\ y_l,\ z_u) $, $ (x_w,\ y_l,\ z_v) $ 間に辺を張る

そして、$ W $ の頂点 $ (x_i,\ y_j,\ z_k) $ の重みを $ 1,000,000,000,000,000,000^{(i\ +j\ +\ k)}\ =\ 10^{18(i\ +\ j\ +\ k)} $ とします。$ W $ の[独立集合](https://ja.wikipedia.org/wiki/%E7%8B%AC%E7%AB%8B%E9%9B%86%E5%90%88)のうち、頂点の重みの総和の最大値を求めてください。そしてそれを $ 998,244,353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100,000 $
- $ 1\ \leq\ M_1,\ M_2,\ M_3\ \leq\ 100,000 $
- $ 1\ \leq\ a_i,\ b_i,\ c_i,\ d_i,\ e_i,\ f_i\ \leq\ N $
- $ X $, $ Y $, $ Z $ は単純、つまり自己ループや多重辺は存在しない

### Sample Explanation 1

$ (x_2,\ y_1,\ z_1) $, $ (x_1,\ y_2,\ z_1) $, $ (x_1,\ y_1,\ z_2) $, $ (x_2,\ y_2,\ z_2) $ を選ぶ場合が最適です。 答えは $ 3\ \times\ 10^{72}\ +\ 10^{108} $ を $ 998,244,353 $ で割ったあまりの $ 46,494,701 $ です。

## 样例 #1

### 输入

```
2
1
1 2
1
1 2
1
1 2```

### 输出

```
46494701```

## 样例 #2

### 输入

```
3
3
1 3
1 2
3 2
2
2 1
2 3
1
2 1```

### 输出

```
883188316```

## 样例 #3

### 输入

```
100000
1
1 2
1
99999 100000
1
1 100000```

### 输出

```
318525248```

# 题解

## 作者：Kewth (赞：23)

一个点 $(x, y, z)$ 的权值为 $K^{x+y+z}$ ，这个 $K$ 足够大，可以看做正无穷，也就是说求这张图的最大权独立集要尽量把 $x+y+z$ 最大的选满。

那么一个暴力的 $O(n^3)$ 贪心做法就呼之欲出了：从大到小枚举 $S = x + y + z$ ，然后对于所有和为 $S$ 的 $(x, y, z)$ ，如果之前没有与之连边的点被选，那么这个点一定要出现在最优解中。

可以给边定向，边从小连到大，那么整个图就是 DAG ，在 DAG 中抽象这个贪心：每次选择一个未确定的点满足其出边连接到的点都已经确定不在最优解（或者没有出边），然后把该点加入最优解集合，把该点入边连接的点确定为不在最优解。

那么一个点在最优解当且仅当其出边连接到的点都不在最优解，一个点不在最优解当且仅当其出边连接到的点存在一个在最优解的点（或没有出度）。

可以发现这个关系完全可以对应到博弈中的必胜必败态，这个 DAG 可以看做博弈转移图，答案就是所有必败态的权值和。

考虑对于一个 $(x, y, z)$ ，如何快速求出其必胜必败态。由于每次移动只能移动一维，所以这个博弈三维独立，就相当于每个维度有一个子游戏。对于每一维的 DAG 分别求出 SG 值 $f(x), g(y), h(z)$ ，三者异或和就是 $(x, y, z)$ 的 SG 值。

至此，问题转换为求 $\sum_{f(x) \oplus g(y) \oplus h(z) = 0} K^{x+y+z}$ ，其中 $\oplus$ 是异或。

可以用 FWT 可以直接求出 $f, g, h$ 的异或卷积。

但是也有更简单的方法，对于一个博弈转移图，任意一个点的 SG 值上界是 $O(\sqrt{m})$ 的。所以可以 $O(m\sqrt{m})$ 或 $O(m)$ 直接枚举 $f(x), g(y), h(z)$ 统计答案。

~~这个很重要，因为遭受降智打击后 FWT 容易打挂~~

参考实现：

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005, mod = 998244353;
std::vector<int> G[maxn];
int sg[3][maxn];
ll f[3][maxn];
ll po[maxn * 3];

int main () {
	int n = read, len = 1;
	while (len < n)
		len <<= 1;

	po[0] = 1;
	ll bs = 1000000000000000000ll % mod;
	for (int i = 1; i <= n * 3; i ++)
		po[i] = po[i - 1] * bs % mod;

	for (int o = 0; o < 3; o ++) {
		int m = read;
		for (int i = 1; i <= n; i ++)
			G[i].clear();
		for (int i = 1; i <= m; i ++) {
			int u = read, v = read;
			if (u < v) G[u].push_back(v);
			if (v < u) G[v].push_back(u);
		}
		for (int i = n; i; i --) {
			std::set<int> mex;
			for (int j : G[i])
				mex.insert(sg[o][j]);
			while (mex.count(sg[o][i]))
				++ sg[o][i];
		}
		for (int i = 1; i <= n; i ++)
			(f[o][sg[o][i]] += po[i]) %= mod;
	}

	ll ans = 0;
	for (int i = 0; i < 500; i ++)
		for (int j = 0; j < 500; j ++)
			(ans += f[0][i] * f[1][j] % mod * f[2][i ^ j]) %= mod;
	printf("%lld\n", ans);
}
```

小彩蛋：![](https://cdn.luogu.com.cn/upload/image_hosting/qaj8x83v.png)



---

## 作者：xht (赞：13)

以下设 $n,m$ 同阶。

由于 $10^{18}$ 非常大，因此求最大独立集，相当于贪心地从权值大的往小的选，能选则选。

考虑 dp，设 $f_{x,y,z}$ 表示点 $(x,y,z)$ 是否要被选。

转移方程为 $f_{x,y,z} = \prod_{(x^\prime,y^\prime,z^\prime) \to (x,y,z)} [f_{x^\prime,y^\prime,z^\prime} = 0]$，其中 $(x^\prime,y^\prime,z^\prime) \to (x,y,z)$ 表示 $(x^\prime,y^\prime,z^\prime), (x,y,z)$ 之间有边且 $x^\prime + y^\prime + z^\prime \ge x + y + z$。

时间复杂度 $\mathcal O(n^3)$，显然过不了。

考虑如下这样一个博弈问题：

> 有三张 $n$ 个点的有向图，每张图在某个点上都有一个标记。
>
> 有两个人轮流进行移动，每次移动可以将一个标记从一条出边移动过去。
>
> 谁不能移动了谁就输了。

对于这样一个博弈问题，用 $\operatorname{SG}$ 函数可以解决。

然后可以发现，这个博弈问题的 $\operatorname{SG}$ 函数和上面那个 dp 的状态是一样的。

而这个博弈问题中，三张图之间相互独立。

这让我们想到了 $\operatorname{Nim}$ 游戏，即我们可以将三张图的 $\operatorname{SG}$ 函数分开算，最后 $\operatorname{xor}$ 起来得到原来的 $\operatorname{SG}$ 函数。$\operatorname{SG}$ 函数为 $0$ 的点，即为原问题中要选择的点。

注意到，对于一个 DAG 博弈转移图，$\operatorname{SG}$ 函数值的上界是 $\mathcal O(\sqrt n)$ 的，因此我们可以 $\mathcal O(n)$ 求出答案。

```cpp
const int N = 1e5 + 7;
const modint K = 1000000000000000000ll % P;
int n;
modint ans;
struct Graph {
	int n, m, sg[N], k;
	modint c[N];
	vi e[N];
	inline Graph() {}
	inline Graph(int n) : n(n) {}
	int SG(int x) {
		if (~sg[x]) return sg[x];
		map<int, bool> p;
		for (int y : e[x]) p[SG(y)] = 1;
		while (p[++sg[x]]);
		return sg[x];
	}
	inline void main() {
		rd(m);
		for (int i = 1; i <= n; i++) sg[i] = -1;
		for (int i = 1, x, y; i <= m; i++) {
			rd(x), rd(y);
			if (x > y) swap(x, y);
			e[x].pb(y);
		}
		for (int i = 1; i <= n; i++) if (!~sg[i]) SG(i);
		for (int i = 1; i <= n; i++) k = max(k, sg[i]), c[sg[i]] += K ^ i;
	}
} G[3];

int main() {
	rd(n);
	for (int i = 0; i < 3; i++) G[i] = Graph(n), G[i].main();
	for (int i = 0; i <= G[0].k; i++)
		for (int j = 0; j <= G[1].k; j++)
			ans += G[0].c[i] * G[1].c[j] * G[2].c[i^j];
	print(ans);
	return 0;
}
```

---

## 作者：SafariMo (赞：4)

[Giant Graph](https://www.luogu.com.cn/problem/AT_agc043_c)

首先 $10^{18}$ 很大，所以我们优先选取 $x+y+z$ 最大的点。

按 $x+y+z$ 从大到小选择即可。

但是时间复杂度为 $\mathcal O(n^3)$。

给边定向，边从小连到大，那么整个图就是一个 **DAG**。

发现对于每个点 $i$:

- 如果 $i$ 的出边被选了，则不能选择 $i$。
- 如果都不能被选或者 $i$ 没有出边，选择 $i$。

这和博弈转移一模一样。

答案为必败点的权值和。

容易发现每一张图都是独立的（每次相当于换一张图操作），SG 记为 $A_{0,i}$，$A_{1,i}$，$A_{2,i}$。

则答案为 $\sum_{A_{0,i}\operatorname{xor} A_{1,j}\operatorname{xor} A_{2,k}=0} 10^{18(i+j+k)}$。

同时有一个很重要的性质：博弈转移图中的点的 SG 值的 $\max$ 不会超过 $\sqrt m$。

于是枚举 $A_{0,i},A_{1,j}$ 即可。

时间复杂度 $\mathcal O(n+m)$。

[Submission](https://atcoder.jp/contests/agc043/submissions/53719515)。

---

## 作者：Claire0918 (赞：3)

我们注意到 $10^{18}$ 是充分大的，所以对于 $a < b$，$(10^{18})^a$ 极其小于 $(10^{18})^b$。

于是，问题可以近似转化为在选择的任意两点无连边的情况下尽量多选 $x + y + z$ 较大的点。

我们可以得到一种暴力的做法：从大到小枚举 $x + y + z$，再分别确定 $x, y, z$，如果该点与已选的点没有连边，则选择该点，否则跳过。

我们肯定先选较大的点再选较小的点，所以可以给每一条边定向，使其从后选的较小点连向先选的较大点。这样得到的图显然是 DAG。

一个点在答案中当且仅当其所有出边连向的点都不在答案中，一个点不在答案中当且仅当其存在一条出边使得其连向的点在答案中。

我们发现这很类似 DAG 上一般无环博弈的结构，所有答案里的点都是游戏中的必败态。

考虑如何求出必败态。由于连边每次只能改变 $x, y, z$ 之一，所以可以拆为 $3$ 个图分别讨论。

参考 Nim 游戏，设 $\operatorname{sg}(g, u)$ 表示在图 $g$ 上第 $i$ 个点的 sg 值，则最终图中 $u$ 点为必败态当且仅当 $\operatorname{xor}_{i = 1}^{3} \operatorname{sg}(i, u) = 0$。

求出 sg 是 $\mathcal{O}(n \log n)$ 的，我们考虑如何快速找出使得 $\operatorname{sg}(1, x) \operatorname{xor} \operatorname{sg}(2, y) \operatorname{xor} \operatorname{sg}(3, z) = 0$ 的 $x, y, z$。

我们要尝试证明对于一个 $m$ 条边的 DAG，sg 值的上界是 $\mathcal{O}(\sqrt{m})$ 的。

  设某一点的 sg 值为 $t$，则其至少有 $t$ 个后继且它们的 sg 值分别为 $0, 1, \ldots , t - 1$。点的数量是无法通过这里确定的，因为一个点可能重复地进行贡献，但边的贡献是不会重复的，从而我们可以确定此处一定有至少 $t$ 条边。归纳可得整张图至少有 $\sum_{i = 1}^{t}i = \mathcal{O}(t^2)$ 条边。所以 $m$ 条边的图 sg 值不可能超过 $\mathcal{O}(\sqrt{m})$。

从而我们可以直接枚举 $\operatorname{sg}(1, x)$ 和 $\operatorname{sg}(2, y)$。$\operatorname{sg}(3, z) = \operatorname{sg}(1, x) \operatorname{xor} \operatorname{sg}(2, y)$ 是确定的。时间复杂度 $\mathcal{O}(\sqrt{m})^2 = \mathcal{O}(m)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 1e5 + 10, maxm = 1e5 + 10, maxsqrt = 5e2, mod = 998244353, base = 1000000000000000000ll % mod;

struct{
    int v, nex;
} edge[maxm];

int n, m, res = 0;
long long power[maxn], f[3][maxn];
int sg[maxn];
int head[maxn], top;

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x & x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

inline void add(int u, int v){
    edge[++top].v = v;
    edge[top].nex = head[u];
    head[u] = top;
}

int main(){
    scanf("%d", &n);
    power[0] = 1;
    for (int i = 1; i <= n; i++){
        power[i] = power[i - 1] * base % mod;
    }
    for (int t = 0; t < 3; t++){
        mem(head, 0);
        mem(sg, 0);
        top = 0;
        scanf("%d", &m);
        for (int i = 1; i <= m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            if (u > v){
                swap(u, v);
            }
            add(u, v);
        }
        for (int u = n; u; u--){
            set<int> mex;
            for (int i = head[u]; i; i = edge[i].nex){
                const int v = edge[i].v;
                mex.insert(sg[v]);
            }
            for (;mex.count(sg[u]); sg[u]++);
        }
        for (int i = 1; i <= n; i++){
            mod_add(f[t][sg[i]], power[i]);
        }
    }
    for (int i = 0; i <= maxsqrt; i++){
        for (int j = 0; j <= maxsqrt; j++){
            mod_add(res, f[0][i] * f[1][j] % mod * f[2][i ^ j] % mod);
        }
    }
    printf("%d", res);

return 0;
}
```

---

## 作者：FstAutoMaton (赞：1)

## [[AGC043C] Giant Graph](https://www.luogu.com.cn/problem/AT_agc043_c)

一道很有教育意义的题。

### 题目描述

感觉题目讲的很清楚了，建议读原题题面。

### 题解

首先观察一下题目的一些特殊性。注意到对于点 $\left(x,y,z\right)$，其代价是 $\left(10^{18}\right)^{x+y+z}$ 这件事情非常鬼畜，不妨从这一点入手。

类似很多 `01-trie` 上贪心的题目进行考虑，由于 $10^{18}$ 远大于 $n$，所以不难发现我们肯定要尽量选择 $x+y+z$ 大的点。于是就有了一个 $\operatorname{O}(n^3)$ 的贪心，把每一个点都建出来，然后按照 $x+y+z$ 从大到小选点，能选就选。

根据上面这个贪心，我们可以把无向边 $\left(u,v\right)$ 变为一条有向边，从编号小的点连向编号大的点。这样整张图就变成了 `DAG`。

继续分析 **最大权独立集** 这个东西。令 $f_{x,y,z}$ 表示点 $\left(x,y,z\right)$ 有没有选，我们规定 $f_{x,y,z}=0$ 表示选，其他情况都表示不选。设 $G$ 表示这些 **三维** 的点通过这三张图连出的图，由于这是一个 `DAG` ，所以可以反拓扑序 dp，转移如下：

$$f_{x,y,z}=\operatorname{mex}_{\left(\left(x',y',z'\right),\left(x,y,z\right)\right)\in G} f_{x',y',z'}$$ 

如果出边连向的点是已经选择（即 $f$ 值为 $0$）的，那么当前点的 $\operatorname{mex}$ 值一定不会为 $0$，这是显然的。所以这样转移可以保证不会选择相邻的，而且我们是从权值大的点开始 `dp` 的，所以保证了权值最大。

观察一下，注意到 **$f$ 的 `dp` 与 `SG` 函数的计算方式很像**（这也是这道题最有教育意义的地方），实际上这两个可以说一模一样。那么便考虑能否像 `SG` 函数一样把 **若干维分开** 进行 `dp`，最后异或在一起。

考虑 `SG` 函数在什么时候可以分开计算最后用异或合并，我们只要保证每一维都互不干扰。而这道题中三张图上的边都只会改变某一维的编号，所以说并不会互相干扰。于是我们可以直接拆开考虑。

设这三张图上点 $x$ 的 `SG` 值分别是 $F(x),G(x),H(x)$，那么答案就是：

$$\sum_{x,y,z,F(x)\oplus G(y)\oplus H(x）=0} \left(10^{18}\right)^{x+y+z}$$

但这样依旧是 $\operatorname{O}(n^3)$ 的，考虑优化.

设 $F'(x)$ 表示在第一张图上 `SG` 值等于 $x$ 的点的权值之和，$G'(x)$，$H'(x)$ 同理。那么答案式子变为：

$$\sum_{x,y}F'(x)\times G'(y)\times H'(x \oplus y)$$

直接暴力是 $\operatorname{O}(n^2)$ 的，但 `SG` 函数的值最大是 $\operatorname{O}(\sqrt m)$ 级别的。感性理解一下，对于一个 `SG` 函数值为 $x$ 的点，其至少需要向 $\left[0,x-1\right]$ 中每个权值的任意一个点连边，归纳的考虑，我们想要有一个 `SG` 值为 $x$ 的点至少需要 $\frac{x\times \left(x+1\right)}{2}$ 条边，所以 `SG` 值是 $\operatorname{O}(\sqrt{m})$ 级别的。

这样我们就可以直接枚举前面答案式中的 $x,y$ 暴力计算了，时间复杂度 $\operatorname{O}(m)$。

[code](https://atcoder.jp/contests/agc043/submissions/65408326)

### 扩展

####  题目描述

在原题目的基础上，点由三维变成了 $k$ 维，但每一维的图都是一样的（图会给定）。对于城市 $\left(p_1,p_2,\cdots,p_k\right)$，其代价为 $10^{n^k\left(p_1+p_2+\cdots+p_k\right)}$，依旧求最大权独立集。

$1\le n\le 2\times 10^5,1\le k\le 10^{50000}, 1\le m\le 5\times 10^5$

#### 题解

首先这个权值显然是搞笑的，这道题怎么处理这个东西就怎么处理。至于权值计算可以用十进制倍增计算 $n^k$ 然后费马小定理解决。

与这题一样，我们将其转化为 `SG` 函数的问题，由于这道题每一个维度图都一样，所以每一维的 `SG` 函数是一样的。

定义多项式运算：

$$A\cdot B=\sum_{i,x,y, x\oplus y=i} a_x\times b_y$$

设 `SG` 值为 $x$ 的点**权值和** 为 $f_x$， $F(x)=\sum_{i=0} f_i\times x^i$，那么答案就是：

$$[x^0]F^k(x)$$

那么直接做的时间复杂度就是 $\operatorname{O}(m\log k)$，这个式子显然可以用 $FWT$ 优化，可以优化到 $\operatorname{O}(\sqrt{m}\log \sqrt{m}\log k)$。

PS：这里有一个小 trick，可以直接对 $k$ 进行十进制倍增，就不用写高精度了。

[code](https://www.luogu.com.cn/paste/m2rqriy4)

---

## 作者：Galois_Field_1048576 (赞：1)

首先考虑如果是只有一个图 $\Gamma$ 该怎么办。考虑按照节点标号从大往小来枚举，如果 $S \sqcup \{v\}$ 还是独立集，则 $S \gets S \sqcup \{v\}$。这样，我们有递归的对 $S$ 的定义：
$$
v \in S \iff \nexists u \in S, u > v, (u, v) \in E.
$$
如果让小的节点连向大的节点，导出 $\Gamma$ 的定向，则 $u > v, (u, v) \in E$ 变为 $v \to u$。也就是说
$$
v \in S \iff \nexists v \to u, u \in S.
$$
我们发现这就是 $\Gamma$ 作为博弈的 Win 谓词：$v \in S \iff \mathrm{Win}(v)$。

现在，发现我们对这些图做的操作在定向下化为游戏的并置。对于游戏的并置的 Win 谓词，我们有 Sprauge-Grundy 定理：「游戏的并置的 SG 是异或。」这样，我们所要求的是
$$
\sum_{\mathrm{SG}(x) \oplus \mathrm{SG}(y) \oplus \mathrm{SG}(z) = 0} B^{x+y+z}, B = 10^{18}.
$$

```cpp
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/all"
using namespace atcoder;

using Z = modint998244353;

const Z B = 1'000'000'000'000'000'000;

vector<int> grundy(vector<vector<int>> gr) {
    int n = gr.size();
    vector<int> ret(n);
    for (int i = n - 1; i >= 0; i--) {
        set<int> S;
        for (int nx : gr[i]) S.insert(ret[nx]);
        while (S.count(ret[i])) ret[i]++;
    }
    return ret;
}

vector<Z> cvl(vector<vector<Z>> args) {
    auto fwt = [](vector<Z> &a, bool invert) {
        int n = a.size();
        for (int len = 1; len < n; len <<= 1)
            for (int i = 0; i < n; i += len << 1)
                for (int j = 0; j < len; j++) {
                    Z x = a[i + j], y = a[i + j + len];
                    if (invert) swap(x, y);
                    a[i + j] = x + y, a[i + j + len] = x - y;
                    if (invert) a[i + j] /= 2, a[i + j + len] /= 2;
                }
    };
    int n = accumulate(args.begin(), args.end(), 0,
                       [](size_t a, auto &b) { return max(a, b.size()); });
    n = __lg(n - 1) + 1;
    for (auto &a : args) a.resize(1 << n);
    for (auto &a : args) fwt(a, false);
    vector<Z> ret(1 << n);
    for (int i = 0; i < (1 << n); i++)
        ret[i] = accumulate(args.begin(), args.end(), Z(1),
                            [i](Z a, auto &b) { return a * b[i]; });
    fwt(ret, true);
    return ret;
}

vector<vector<int>> read_gr(int n) {
    vector<vector<int>> gr(n);
    int m;
    cin >> m;
    for (int i = 0, u, v; i < m; i++)
        cin >> u >> v, u--, v--, gr[min(u, v)].push_back(max(u, v));
    return gr;
}

int main() {
    int n;
    cin >> n;
    vector<vector<vector<int>>> gr(3);
    for (auto &G : gr) G = read_gr(n);
    auto aft_grundy = [&](vector<int> gr) {
        int m = *max_element(gr.begin(), gr.end()) + 1;
        vector<Z> ret(m);
        for (int i = 0; i < n; i++) ret[gr[i]] += B.pow(i + 1);
        return ret;
    };
    vector<Z> res = cvl({aft_grundy(grundy(gr[0])), aft_grundy(grundy(gr[1])),
                         aft_grundy(grundy(gr[2]))});
    cout << res[0].val() << endl;
}
```

---

## 作者：UnyieldingTrilobite (赞：1)

首先上来第一眼看到的想必是这个略显夸张的贡献形式。不过只要稍加思索便会发现，这个 $10^{18}$ 的贡献形式其实就是在最大（权）独立集中钦定了 $x+y+z$ 大的要尽量多加，仅此而已……

于是我们得到了一个很显然的贪心算法：把所有点按照 $x+y+z$ 分层，每条边从高层连向低层。从高到低遍历每一层，对于其中的每一个点，若其不与任意一个已取点（容易发现这样的点一定比当前考虑的这个点层更高）相邻，则取之。

接下来出现了一步比较抽象的事情。我们从隔壁博弈论专题里把 Alice 和 Bob 拉过来，并定下这样一个游戏：初始时有一枚棋子在给定点上，二人轮流行动，每次可以沿着边把棋子向相邻的更高层点移动一步，不能移动者败。如此一来，我们逐层考虑，可以观察到，棋子初始在一个点上时先手必败，当且仅当这个点在最后的最大独立集中。具体地，每个最大独立集中的点都只能移动到非最大独立集中点，而每个非最大独立集中点都能移动到最大独立集中点。同时我们意识到，在这个视角下，三个维度是独立的，等于是三场同时进行的游戏，我们只需要对于每个点求出三个 sg。

最后是答案的计算，我们注意到这个形式是多少可以用分配律进行一些合并的。由于 sg 的上界是根号规模的，我们只需要枚举两个 sg，利用异或等于零算出第三个 sg，然后把贡献乘起来即可。

```cpp
#include <bits/stdc++.h>

#include <atcoder/modint>
using namespace std;
typedef atcoder::modint998244353 mint;
constexpr int N = 2e5 + 9, B = 1 << 9;
int n, m, vst[B], sg[N];
mint pw[N], kv[3][N], ans;
vector<int> es[N];
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n, pw[0] = 1;
  mint k = mint(10).pow(18);
  for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * k;
  for (int T = 0; T < 3; ++T) {
    cin >> m, memset(vst, 0, sizeof vst);
    for (int i = 1; i <= n; ++i) es[i].clear();
    for (int u, v; m; --m) {
      if (cin >> u >> v, u > v) swap(u, v);
      if (u < v) es[u].push_back(v);
    }
    for (int i = n; i; --i) {
      for (int j : es[i]) vst[sg[j]] = i;
      sg[i] = 0;
      while (vst[sg[i]] == i) ++sg[i];
      kv[T][sg[i]] += pw[i];
    }
  }
  for (int i = 0; i < B; ++i)
    for (int j = 0; j < B; ++j) ans += kv[0][i] * kv[1][j] * kv[2][i ^ j];
  return cout << ans.val() << endl, 0;
}
```

---

## 作者：ImmortalWatcher (赞：1)

- 从特殊状态转移方式转换到博弈，从而解决问题。

观察答案贡献的形式： $10^{{18(x+y+z)}}$ ，$10^{18}$ 远比 $n$ 大，所以不可能出现几个编号小的数加起来的贡献大于选编号大的数。

因此可以考虑贪心，优先从大的往小选，可以做到 $O(n^3)$，并不能通过此题。

思考一下贪心的过程，即从最大的点开始，如果当前点的所有出边均为不选或无出边，则选这个点，否则不选这个点。

发现这个过程类似博弈问题必胜必败态的对应关系，选为必败，不选为必胜。

考虑用 SG 函数来解决这个问题，点有三维，不是很好处理，但是发现每次只会动一维坐标，所以三维实际上是独立的，是原问题的三个子问题。

接下来就好办了，每个图分开求 SG 函数，全部异或起来就是总问题的 SG 函数。

保证总问题 SG 函数为 $0$ 即可。

合并答案的时候，似乎需要 FWT 异或卷积，实际上我们知道，对于一个 DAG 博弈转移图，SG 函数的上限 $\sqrt{m}$ 的，即可在 $O(m)$ 时间内解决本问题。

```cpp
#include<cstdio>
#include<vector>
#include<cmath>
#include<set>
#define int long long
using namespace std;
const int mo=998244353;
int n,m,x,y,mi[100010],sg[100010],f[3][100010],ans,mx;
vector<int> e[100010];
signed main()
{
    scanf("%lld",&n);
    mi[0]=1;mi[1]=(long long)1e18%mo;
    for (int i=2;i<=n;i++)
        mi[i]=1ll*mi[i-1]*mi[1]%mo;
    for (int t=0;t<=2;t++)
    {
        for (int i=1;i<=n;i++) e[i].clear(),sg[i]=0;
        scanf("%lld",&m);mx=max(mx,m);
        for (int i=1;i<=m;i++)
        {
            scanf("%lld%lld",&x,&y);
            if (x>y) swap(x,y);
            e[x].push_back(y);
        }
        set<int> mex;
        for (int i=n;i>=1;i--)
        {
            mex.clear();
            for (auto v:e[i])
                mex.insert(sg[v]);
            while (mex.count(sg[i]))
                sg[i]++;
        }
        for (int i=1;i<=n;i++)
            f[t][sg[i]]=(f[t][sg[i]]+mi[i])%mo;
    }
    mx=sqrt(mx);
    for (int i=0;i<=500;i++)
        for (int j=0;j<=500;j++)
            ans=(ans+1ll*f[0][i]*f[1][j]%mo*f[2][i^j]%mo)%mo;
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：strcmp (赞：0)

这道题的突破点就在于它的点权，$10^{18(x+y+z)}$ 关于 $x + y + z$ 的增大，增长极为迅速。因此我们可以想象出要构造最大的 $x + y + z$，在最大的前提下使得最大的 $x + y + z$ 最多，以此类推必然是最优的。

将 $x + y + z$ 称为 $(x,\,y,\,z)$ 的**级别。**

因为 $G_1,\,G_2,\,G_3$ 都是简单无向图不存在自环，所以 $G$ 不会出现同级别的点互相连接的情况。

因此不妨将边定向，$G$ 变成从级别小的点连向级别大的点的 DAG。

设 $f(x,\,y,\,z)$  代表 $(x,\,y,\,z)$ 是否会选，则 $(x,\,y,\,z)$ 会选当且仅当其后继都没有被选，只要存在一个后继是被选的则 $(x,\,y,\,z)$ 必定不会选。

我们发现这很像有向图游戏中的必胜态和必败态，$(x,\,y,\,z)$ 是一个状态，$f(x,\,y,\,z) = 1$ 代表 $(x,\,y,\,z)$ 是必败态，最后要求所有必败态的权值和。

同时我们得到的图 $G$ 也有特殊性，每次只在一个维度上改变，如 $(u,\,a,\,b) \to (v,\,a,\,b)$。

因此我们可以将 $(x,\,y,\,z)$ 看作三个起点分别为 $x,\,y,\,z$ 的有向图游戏，根据 SG 定理，状态 $(x,\,y,\,z)$ 是否必败取决于 $\text{SG}(x) \oplus \text{SG}(y) \oplus \text{SG}(z)$ 的值，当且仅当 $\text{SG}(x) \oplus \text{SG}(y) \oplus \text{SG}(z) = 0$ 的时候状态 $(x,\,y,\,z)$ 先手必败。

对每个有向图游戏求出每个点的 $\text{SG}$ 值，合并看起来需要 FWT 合并，但实际上我们有结论 $\max \{ \text{SG}(x) \} = \mathcal O(\sqrt n)$（这个结论观察 $\text{SG}$ 的定义就很容易得出），于是直接暴力合并即可。

时间复杂度 $\Theta(n \log m)$，瓶颈在求 $\text{SG}$ 使用 `std::set`。

```cpp
#include <bits/stdc++.h>
#define X first
#define Y second
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define per(i, a, b) for(int i = a; i >= b; i--)
using namespace std;
typedef long long int ll;
using pli = pair<ll, int>;
using ppi = pair<pli, int>;
using vec = vector<int>;
const ll inf = 1LL << 60;
constexpr int maxn = 3e5 + 10, mod = 998244353;
constexpr ll b = 716070898; vector<int> g[maxn]; set<int>s;
int n, m, x, y, sg[3][maxn]; ll f[3][maxn], p[maxn], ans;
int main() {
    scanf("%d", &n); p[0] = 1; 
    rep(i, 1, n * 3) p[i] = p[i - 1] * b % mod;
    rep(o, 0, 2) {
        scanf("%d", &m);
        rep(i, 1, m) scanf("%d%d", &x, &y), x > y && (swap(x, y), 0), g[x].push_back(y);
        per(i, n, 1) {
            for (auto d : g[i]) s.insert(sg[o][d]);
            while (s.find(sg[o][i]) != s.end()) ++sg[o][i]; s.clear();
        }
        rep(i, 1, n) f[o][sg[o][i]] = (f[o][sg[o][i]] + p[i]) % mod, g[i].clear();
    }
    rep(i, 0, 600) rep(j, 0, 600) ans = (ans + f[0][i] * f[1][j] % mod * f[2][i ^ j] % mod) % mod;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Phartial (赞：0)

好题。

首先注意到点权式子中不同寻常的 $10^{18}$，这个权值足够大，所以我们可以按 $x+y+z$ 的值从大往小贪心的尝试将点 $(x,y,z)$ 加入独立集。显然这个贪心是对的。

考虑给 $G$ 中的边按 $x+y+z$ 的大小关系定向，由小点指向大点（显然这两个点的 $x+y+z$ 必然不等），则这给出了一张 DAG，容易发现以下性质：

- 点 $(n,n,n)$ 必选；
- 一个点 $(x,y,z)$ 被选当且仅当其出边指向的每个点都不被选；
- 一个点 $(x,y,z)$ 不被选当且仅当其存在出边使指向的点被选；

发现这和有向图博弈非常像！如果两个人轮流沿着这张 DAG 的边移动一枚棋子，且不能移动者输，那么一个点被选当且仅当从该点开始先手必败。

这时候 $G$ 的神秘构造方式就体现出了意图：$G$ 上的游戏和 $G_1,G_2,G_3$ 上的游戏的组合是一样的。

考虑求出 $G_i$ 中点 $x$ 的 SG 函数值 $\operatorname{SG}(i,x)$，那么一个点 $(x,y,z)$ 被选当且仅当 $\operatorname{SG}(1,x)\oplus\operatorname{SG}(2,y)\oplus\operatorname{SG}(3,z)=0$（即先手必败）。

由于一张 $m$ 条边的 DAG 中的最大 SG 值是 $\sqrt{2m}$ 量级的（因为一个 $\operatorname{SG}$ 值为 $v$ 的点需要 $v$ 个出点，而这 $v$ 个出点又各需要 $0,1,\cdots,v-1$ 个出点，所以这张图至少需要 $\frac{v(v+1)}{2}$ 条边，竞赛图可以得到这个下界），所以可以直接暴力求出并枚举三张图的 SG 值以计算答案。时间复杂度 $\mathcal{O}((n+m)\sqrt{m})$，可能会带一些 $\log$ 或者 $\omega^{-1}$。

```cpp
#include <atcoder/modint>
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;
using LL = atcoder::modint998244353;

const int kN = 1e5 + 1, kS = 450;
const LL kB = atcoder::internal::pow_mod_constexpr(10, 18, 998244353);

int n, m[3], sg[3][kN];
vector<int> e[3][kN];
bitset<kS> v;
LL a[3][kS];

int main() {
  cin >> n;
  for (int o = 0; o < 3; ++o) {
    cin >> m[o];
    for (int i = 1, x, y; i <= m[o]; ++i) {
      cin >> x >> y;
      if (x > y) {
        swap(x, y);
      }
      e[o][x].push_back(y);
    }
    for (int i = n; i >= 1; --i) {
      v = 0, v.flip();
      for (int j : e[o][i]) {
        v.set(sg[o][j], 0);
      }
      sg[o][i] = v._Find_first();
    }
    for (int i = 1; i <= n; ++i) {
      a[o][sg[o][i]] += kB.pow(i);
    }
  }
  LL ans = 0;
  for (int x = 0; x < kS; ++x) {
    for (int y = 0; y < kS; ++y) {
      for (int z = 0; z < kS; ++z) {
        if ((x ^ y ^ z) == 0) {
          ans += a[0][x] * a[1][y] * a[2][z];
        }
      }
    }
  }
  cout << ans.val();
  return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

$10^{18}$ 非常大，以至于我们对于一个权值 $v$，把所有 $x+y+z$ 小于 $v$ 的排列的 $10^{18(x+y+z)}$ 全加起来还没有 $10^v$ 大。

因此考虑直接贪心，按 $x+y+z$ 从大到小排序后看每个点，如果它可以选就直接选上。

这个贪心显然会超时，于是考虑怎么转化。首先整个图按照 $x+y+z$ 从小到大定向后是一个 DAG。

而考虑贪心的过程。如果这个点相连的点都没有选才可以选中它。

这让我们联想到了博弈论的必胜必败态。答案是所有必败的点的权值之和。

问题转化为了在一个 DAG 上求必败点的权值和。首先我们发现三维都是独立的，所以我们对于三维分别算出它们的 $SG$ 函数，然后求出 $\sum\limits_{X(x)\oplus Y(y)\oplus Z(z)=0}10^{18(x+y+z)}$。即可。

每一维的 SG 函数是好算的，因为 $n$ 只有 $10^5$。直接从大到小看每个点然后取所有它连接的点的 SG 的 mex 即可。

最后就是看怎么求这个和的式子。

这里要想到一个经典结论：一个图上的 SG 至多为 $O(\sqrt m)$。因此直接 $O(m)$ 枚举其中两维即可，另一维为它们的异或和。

另外，如果这题转化到 $k$ 维也是一样的做法，如果有需要可以使用 FWT 来解决。

---

## 作者：小超手123 (赞：0)



### 分析：

由于点权为 $10^{18(x+y+z)}$，显然求最大权独立集时可以直接贪心，因为取编号大的一定更优。

考虑只有 $G_1$ 的情况，我们首先把 $G_1$ 中的边**定向**（编号小的连到编号大的），然后可以发现，独立集的定义可以转化成一个经典的博弈问题：给定一张 DAG，两个人轮流操作，最先无法操作的人失败。

因此可以使用 SG 函数解决。对重构图中出度为 $0$ 的点定义其 $SG(x)=0$，然后转移 $SG(x)=mex(SG(y))$。

这样做后可以发现 $SG$ 值为 $0$ 的点一定会取，因为根据 $mex$ 的定义，即存在至少一个 $SG(y)$ 为 $0$，那么 $SG(x)$ 一定不为 $0$。这里先手必败就一定会取。

那这里三个图怎么做呢？可以发现每个点的三个维度的值的变换是**独立**的。

根据 $SG$ 定理：

> 对于由 $n$个有向图游戏组成的组合游戏，设它们的起点分别为 $s_1,s_2,\dots,s_{n}$，则有定理：**当且仅当 $SG(s_1) \oplus SG(s_2) \oplus \dots \oplus SG(s_n) \ne 0$  时，这个游戏是先手必胜的。**

因此我们需要统计：
$$
\sum_{x_1=1}^{n} \sum_{x_2=1}^{n}\sum_{x_3=1}^{n} V^{x_1+x_2+x_3}[SG(x_1) \oplus SG(x_2) \oplus SG(x_3)==0]
$$
这东西就很好做了，记 $f_{i,j}$ 表示目前处理到 $x_i$，异或和为 $j$ 的所有方案的**权值和**。

转移显然为 `f[i + 1][j ^ a[i].SG[g]] += f[i][j] * h[g]`。

暴力转移是 $O(n^2)$ 的。但众所周知，一个 DAG 的 $SG$ 函数的值域在 $[0,\sqrt m]$。因此可以做到 $O(m)$ 或 $O(n \sqrt m)$ 的时间复杂度，前者需要搞个 $SG$ 的桶。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 100005
using namespace std;
int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
	return x * f;
}
void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar('0' + x % 10);
}
int Pow(int a, int n) {
	if(n == 0) return 1;
	if(n == 1) return a;
	int x = Pow(a, n / 2);
	if(n % 2 == 0) return x * x % mod;
	else return x * x % mod * a % mod;
}
int n, k, v, h[N];
int z[N], f[7][N]; //f[i][j]表示考虑前i行,异或和为j的权值和 
struct Graph{
	vector<int>G[N], p[N];
	int outd[N], SG[N], t[N]; //t[i]是SG函数的桶 
	void work(int x) {
		for(auto y : p[x]) z[SG[y]] = 1;
		SG[x] = 0; while(z[SG[x]]) SG[x]++;
		for(auto y : p[x]) z[SG[y]] = 0;
	}
	void GetSG() { //拓扑排序求SG函数 
		queue<int>Q;
		for(int i = 1; i <= n; i++) 
			if(outd[i] == 0) Q.push(i);
		while(!Q.empty()) {
			int x = Q.front();
			Q.pop();
			for(auto y : G[x]) {
				outd[y]--;
				if(outd[y] == 0) work(y), Q.push(y);
			}
		}
		for(int i = 1; i <= n; i++) t[SG[i]] += i;
	}
}a[7];
signed main() {
    n = read(); 
	k = 3;
    v = Pow(10, 18) % mod;
    h[0] = 1; for(int i = 1; i <= n; i++) h[i] = h[i - 1] * v % mod;
    for(int i = 1; i <= k; i++) {
    	int mi = read();
    	while(mi--) {
    		int u = read(), v = read();
    		if(u > v) swap(u, v); //小的往大的连边 
    		a[i].G[v].push_back(u); //连反向边
    		a[i].p[u].push_back(v); //连正向边
			a[i].outd[u]++; 
	    }
	}
	for(int i = 1; i <= k; i++) a[i].GetSG(); 
	f[1][0] = 1;
	for(int i = 1; i <= k; i++) 
		for(int j = 0; j <= 700; j++) 
			for(int g = 1; g <= n; g++) {
				f[i + 1][j ^ a[i].SG[g]] += f[i][j] * h[g];
				f[i + 1][j ^ a[i].SG[g]] %= mod;
		    }
	write(f[k + 1][0]);
	return 0;
}
```























---

