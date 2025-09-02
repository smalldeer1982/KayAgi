# [USACO24JAN] Island Vacation P

## 题目描述

Bessie 正在一个 $N$（$2\le N\le 10^4$）座岛组成的岛屿网络中度假，编号为 $1\ldots N$，由 $M$ 座双向通行的桥连接，每座桥连接两座岛（$N−1\le M\le \dfrac{3(N-1)}{2}$）。保证所有桥形成连通的简单图（具体地说，没有两座桥连接同一对岛屿，也没有一座桥连接一座岛到其自身）。

另外保证没有一座桥处在多于一个简单环上。一个简单环是一个不包含重复岛的环。

Bessie 从岛 $1$ 开始，按以下过程旅行。假设她目前在岛 $i$ 上，

1. 如果不存在连接岛 $i$ 的她尚未穿过的桥，则她的度假结束。
2. 否则，以 $p_i \pmod {10^9+7}$ 的概率，她的度假结束。
3. 否则，在连接岛 $i$的所有她还没有穿过的桥中，她均匀地随机选择一座并穿过它。

对于每座岛，输出她在该岛上结束度假的概率，对 $10^9+7$ 取模。 

## 说明/提示

### 样例解释 1

在第一个测试用例中，$p_3\equiv \frac{1}{9}\pmod {10^9+7}$。Bessie 有 $\frac{1}{9}$ 的概率在岛 $3$ 结束（经过路径 $1\to 3$），$\frac{8}{9}$ 的概率在岛 $2$ 结束（经过路径 $1\to 3\to 2$）。

在第二个测试用例中，$p_1\equiv \frac{1}{2}\pmod {10^9+7}$。Bessie 有 $\frac{1}{2}$ 的概率在岛 $1$ 结束，各 $\frac{1}{6}$ 的概率在岛 $2$ 和 $3$ 结束，各 $\frac{1}{12}$ 的概率在岛 $4$ 和岛 $6$ 结束。

### 样例解释 2

在第一个测试用例中，$p_1\equiv p_2\equiv \frac{1}{3}\pmod {10^9+7}$。Bessie 有 $\frac{7}{9}$ 的概率在岛 $1$ 结束（经过路径 $1$，$1\to 2\to 3\to 4\to 5\to 1$ 与 $1\to 5\to 4\to 3\to 2\to 1$ 之一），$\frac{2}{9}$ 的概率在岛 $2$ 结束。

在第二个测试用例中，Bessie 有 $\frac{1}{3}$ 的概率在岛 $3$ 结束，$\frac{2}{3}$ 的概率在岛 $5$ 结束。

### 测试点性质

- 测试点 $4-5$：$N\le 11$。
- 测试点 $6-7$：不存在简单环。
- 测试点 $8-11$：没有一座岛处在多于一个简单环上。
- 测试点 $12-15$：没有一座岛处在多于 $5$ 个简单环上。
- 测试点 $16-19$：没有一座岛处在多于 $50$ 个简单环上。
- 测试点 $20-23$：没有额外限制。

## 样例 #1

### 输入

```
2

3 2
0 10 111111112
1 3
2 3

6 5
500000004 0 0 0 0 0
1 5
1 3
4 5
5 6
1 2```

### 输出

```
0 888888896 111111112
500000004 166666668 166666668 83333334 0 83333334```

## 样例 #2

### 输入

```
2

5 5
333333336 333333336 0 0 0
1 2
2 3
3 4
4 5
1 5

5 5
0 0 0 0 0
1 2
2 3
2 4
1 4
1 5```

### 输出

```
777777784 222222224 0 0 0
0 0 333333336 0 666666672```

## 样例 #3

### 输入

```
1

11 13
2 3 4 5 6 7 8 9 10 11 12
1 2
1 3
2 3
2 4
4 5
2 5
4 8
5 9
2 6
6 7
2 7
6 10
5 11```

### 输出

```
133332478 200000394 577778352 999999971 399999938 933333282 355555536 800000020 18 600000029 18```

# 题解

## 作者：Alan_Zhao (赞：9)

## 题解

建出原图的广义圆方树，令所有方点的编号为 $N+1,N+2,\dots$。钦定圆点 $1$ 为根，且钦定每个方点的儿子是按照环上的顺序排列的。设圆方树上一个方点的权值 $\mathrm{val}_u$ 为其儿子个数对 $2$ 取 $\min$ 的值。

原图上的随机游走等价于，设当前在圆方树上的点 $u$：

- 如果 $u$ 是圆点：首先有 $p_u$	的概率停下。
  
	设 $s=[\mathrm{val}_{\mathrm{fa}_u}>1]+\sum_{v\in \mathrm{son}_u} \mathrm{val}_v$，那么有 $[\mathrm{val}_{\mathrm{fa}_u}>1]\cdot s^{-1}$ 的概率走向 $u$ 的下一个兄弟。这里“下一个兄弟”取决于从 $u$ 的父亲走下来时的方向。此外，如果 $u$ 是最后一个点，那么回到 $u$ 的父亲。
  
	对于 $u$ 的每个没有被访问过的儿子 $v$，有 $\mathrm{val}_v\cdot s^{-1}$ 的概率走向 $v$。
- 如果 $u$ 是方点：如果以前没有访问过 $u$，那么等概率走向 $u$ 的第一个儿子或最后一个儿子，否则回到 $u$ 的父亲。

也就是说，对于一个圆点，我们可能走到它的一些儿子，然后绕一圈回来，最后可能走到它的兄弟，或是停在它上面。

开始 DP：设 $g_u$ 表示到达圆点 $u$ 后走向其左右兄弟的概率（这里只有可能走向左右兄弟中的一个，但两种情况的概率是相等的），$h_u$ 表示走到方点 $u$ 后从底下绕一圈回到 $u$ 的概率。

对于每个点 $u$，$g_u$ 可以用一次背包计算，$h_u$ 就是直接把所有儿子的 $g_u$ 乘起来。

算出 $g,h$ 后，设 $f_{u,0/1}$ 表示：

- 如果 $u$ 是圆点，那么 $f_{u,0}$ 是从 $\mathrm{fa}_u$ 走到 $\mathrm{fa}_u$ 的第一个儿子再走到 $u$ 的概率，$f_{u,1}$ 同理；
- 如果 $u$ 是方点，那么 $f_{u,0}$ 表示走到 $u$ 的概率，而 $f_{u,1}=0$。

由于已经算出了 $g,h$，所以在兄弟之间的转移是容易的；对于从圆点 $u$ 走到 $u$ 的某个儿子的情况，在 $u$ 处做一次可撤销背包即可。

具体地，从 $u$ 到儿子 $v$ 的转移是：设

$$
F(x)=\prod_{v'\in \mathrm{son}_u\land v'\neq v} (1+h_{v'}x),
$$

那么

$$
f_{v,0}=\sum_{i\ge 0} [x^i]F(x)\cdot i!\cdot (1-p_u)^{i+1}\cdot \mathrm{val}_v\cdot (s-2i)^{-1}\cdot \frac{2^i s!!}{(s-2i)!!}.
$$

（$s$ 的定义在上面有。）

而停在 $u$ 的概率就是 $1$ 减去走向兄弟的概率，再减去走向某个儿子且不回来的概率，在算完 $f$ 以后这些都是好算的。

时间复杂度 $O(N^2)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define For(Ti, Ta, Tb) for (auto Ti = (Ta); Ti <= (Tb); ++Ti)
#define Dec(Ti, Ta, Tb) for (auto Ti = (Ta); Ti >= (Tb); --Ti)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx), end(Tx)
using ll = long long;
using mint = modint1000000007;
const int N = 1e4 + 5;
int T, n, m, dfn[N], low[N], dfx, stk[N], top, tot;
mint p[N];
vector<int> gr[N], e[N * 2];
void link(int u, int v) {
	e[u].push_back(v);
	e[v].push_back(u);
}
void tarjan(int u) {
	low[u] = dfn[u] = ++dfx;
	stk[++top] = u;
	for (int v : gr[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			if (low[v] == dfn[u]) {
				link(++tot, u);
				for (int x = 0; x != v;) {
					link(tot, x = stk[top--]);
				}
			}
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
}
int fa[N * 2], val[N * 2], pre[N], nxt[N], sum[N];
mint f[N * 2][2], g[N], h[N * 2], ans[N];
void get_dp(int u, int &tot, mint *dp) {
	fill(dp, dp + n + 1, 0);
	dp[0] = 1;
	for (int v : e[u]) {
		if (v != fa[u] && val[v] > 1) {
			Dec(i, tot, 0) { dp[i + 1] += dp[i] * h[v]; }
			++tot;
		}
	}
}
void dfs(int u) {
	val[u] = (u <= n ? val[fa[u]] : min(2, int(e[u].size()) - 1));
	sum[u] = (val[u] > 1);
	for (int v : e[u]) {
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
			sum[u] += val[v];
		}
	}
	if (u > n) {
		int x = u;
		for (int v : e[u]) {
			if (v != fa[u]) {
				pre[v] = x;
				x = v;
			}
		}
		reverse(range(e[u]));
		x = u;
		for (int v : e[u]) {
			if (v != fa[u]) {
				nxt[v] = x;
				x = v;
			}
		}
		reverse(range(e[u]));
	}
	if (val[u] <= 1)
		return;
	if (u <= n) {
		static mint dp[N];
		int tot = 0;
		get_dp(u, tot, dp);
		mint pw = 1;
		For(i, 0, tot) {
			pw *= 1 - p[u];
			g[u] += dp[i] * C.fac(i) * pw * C.inv(sum[u] - i * 2);
			pw *= 2 * C.inv(sum[u] - i * 2);
		}
	} else {
		h[u] = 1;
		for (int v : e[u]) {
			if (v != fa[u]) {
				h[u] *= g[v];
			}
		}
	}
}
void dfs2(int u) {
	if (u <= n) {
		static mint dp[N];
		int tot = 0;
		get_dp(u, tot, dp);
		mint all = 1 - g[u];
		for (int v : e[u]) {
			if (v == fa[u])
				continue;
			if (val[v] > 1) {
				For(i, 1, tot) { dp[i] -= dp[i - 1] * h[v]; }
				--tot;
			}
			mint pr = 0, pw = 1;
			For(i, 0, tot) {
				pw *= 1 - p[u];
				pr += dp[i] * C.fac(i) * pw * val[v] * C.inv(sum[u] - i * 2);
				pw *= 2 * C.inv(sum[u] - i * 2);
			}
			all -= pr * (1 - h[v]);
			f[v][0] += pr * (f[u][0] + f[u][1]);
			if (val[v] > 1) {
				++tot;
				Dec(i, tot, 1) { dp[i] += dp[i - 1] * h[v]; }
			}
		}
		ans[u] = (f[u][0] + f[u][1]) * all;
	} else {
		mint cur = f[u][0] / 2;
		for (int v : e[u]) {
			if (v != fa[u]) {
				f[v][0] = cur;
				cur *= g[v];
			}
		}
		reverse(range(e[u]));
		cur = f[u][0] / 2;
		for (int v : e[u]) {
			if (v != fa[u]) {
				f[v][1] = cur;
				cur *= g[v];
			}
		}
		reverse(range(e[u]));
	}
	for (int v : e[u]) {
		if (v != fa[u]) {
			dfs2(v);
		}
	}
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		For(i, 1, n) { cin >> p[i]; }
		For(i, 1, m) {
			int u, v;
			cin >> u >> v;
			gr[u].push_back(v);
			gr[v].push_back(u);
		}
		tot = n;
		tarjan(1);
		f[1][0] = 1;
		dfs(1);
		dfs2(1);
		For(i, 1, n) { cout << ans[i] << " \n"[i == n]; }
		For(i, 1, n) {
			dfn[i] = low[i] = 0;
			g[i] = ans[i] = 0;
			gr[i].clear();
		}
		For(i, 1, tot) {
			f[i][0] = f[i][1] = h[i] = fa[i] = 0;
			e[i].clear();
		}
		dfx = top = 0;
	}
	return 0;
}
```

有板子的：<https://loj.ac/s/2014541>。

---

## 作者：Mars_Dingdang (赞：7)

USACO 这么猛的嘛？

update：修改了部分标点。

### 题目大意

Bessie 正在一个 $N$（$2\le N\le 10^4$）座岛组成的岛屿网络中度假，编号为 $1\ldots N$，由 $M$ 座双向通行的桥连接，每座桥连接两座岛，$N-1\le M\le \frac{3(N-1)}{2}$。保证所有桥形成连通的简单图（具体地说，没有两座桥连接同一对岛屿，也没有一座桥连接一座岛到其自身）。

另外保证没有一座桥处在多于一个简单环上。一个简单环是一个不包含重复岛的环。

Bessie 从岛 $1$ 开始，按以下过程旅行。假设她目前在岛 $i$ 上，

1. 如果不存在连接岛 $i$ 的她尚未穿过的桥，则她的度假结束。
2. 否则，以 $p_i \pmod {10^9+7}$ 的概率，她的度假结束。
3. 否则，在连接岛 $i$ 的所有她还没有穿过的桥中，她均匀地随机选择一座并穿过它。

对于每座岛，输出她在该岛上结束度假的概率，对 $10^9+7$ 取模。

### 题解

记 $d_i=\deg (i)-1$，特别地 $d_1=\deg (1)$。记 $K$ 表示某个节点最多处在几个简单环上。

#### 算法 $1$：$N\le 11$ 

注意到此时 $M\le 15$，也就是说我们可以使用一个 $\mathcal O(2^M M)$ 的 DP。记 $f_{i,E}$ 表示目前在节点 $i$，没有访问过的边集为 $E$ 这一状态被到达的概率。

记 $E'$ 为 $E$ 中 $i$ 的邻域，如果 $E'=\varnothing$，则 $f_{i,E}$ 可以贡献到 $ans_i$；否则 $f_{i,E}$ 将以 $p_i$ 的概率贡献到 $ans_i$，同时所有 $e=(i,j)\in E'$，$f_{i,E}$ 将以 $\dfrac{1-p_i}{|E'|}$ 的概率贡献到 $f_{j,E\backslash\{e\}}$。期望得分 $10$。

#### 算法 $2$：$K=0$ 

此时整个图构成一棵树，令树根为 $1$。记 $f_i$ 表示从 $1$ 访问到 $i$ 的概率，答案即为 $ans_i=f_ip_i$。

对于 $j\in \text{son}(i)$，有 $f_j=f_i\cdot \dfrac{1-p_i}{d_i}$，DP 的时间复杂度 $\mathcal O(M)$，期望得分 $10$，结合算法 $1$ 期望得分 $20$。

#### 算法 $3$：$K=1$ 

此时整个图是一棵仙人掌，同时每个点最多属于一个简单环。

我们对仙人掌建出圆方树，并且类似地，我们记 $f_i$ 表示从 $1$ 访问到 $i$ 的概率。非环边的转移是类似算法 $2$ 的，关键在于如何转移环边。

记当前考虑的环为 $C$，点 $i$ 为环 $C$ 在圆方树上深度最浅的那个圆点，考虑如何从 $i$ 转移到其他环 $C$ 上的点 $j$。容易发现，在环上 $i\to j$ 有两条路径 $\mathcal R_1,\mathcal R_2$，每条路径贡献的概率为路径上所有点 $u$ 的 $\dfrac{1-p_u}{d_u}$ 的乘积，因此 $\displaystyle f_j=f_i\sum_{r=1}^2\prod_{u\in \mathcal R_r} \dfrac{1-p_u}{d_u}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0fohqe15.png)

需要特殊处理的是，可能可以从环回到 $i$，此时从 $i$ 继续往下走的概率不止有 $f_i\dfrac{1-p_i}{d_i}$，还有绕一圈回来的概率，此时不用乘以 $d_i$。

![](https://cdn.luogu.com.cn/upload/image_hosting/9wsr35uz.png)

时间复杂度 $\mathcal O(M)$，至此期望得分 $35$。

#### 算法 $4$

我们发现进入一个环之后，可能停在某个点，可能会绕完整的一圈然后出去（这样的“出边”至多只有一条）。

记 $f_i$ 表示从 $1$ 访问到 $i$ 的概率，$g_i$ 表示从 $i$ 开始最终使用了 $i$ 的“出边”绕出去的概率（若没有“出边”则 $g_i=0$），$h_{i,j}$ 表示从 $i$ 出发访问到子仙人掌（圆方树的子树）中后继节点 $j$ 的概率。

$f_i$ 的转移可以利用 $h_{i,j}$。具体地，对于 $i$ 在圆方树上的后继节点 $j$，有 $f_j=f_i\cdot h_{i,j}$。
![](https://cdn.luogu.com.cn/upload/image_hosting/8l6v0huf.png)

$ans_i$ 需要访问到 $i$ 并且停留在 $i$，可以容斥地减去从 $i$ 绕出去的概率以及停留在后继节点 $j$ 的概率，即 
$$
ans_i=f_i\left(1-g_i-\sum_{j\in \text{son}(i)}h_{i,j}(1-g_j)\right)
$$
考虑如何计算 $g,h$。记 $G_C=\prod_{i\in C} g_i$，记 $\mathcal C_i$ 为所有以 $i$ 为深度最浅点的环的集合。 

记 $pC_{bridge}$ 表示最终选择了一个和 $i$ 相邻的桥边（即非环边，也即 $i$ 的“出边”）$bridge$ 的概率，$pC_C$ 表示最终选择了 $C\in \mathcal C_i$ 的两条边中的一条的概率。

那么，对于所有非环边连接的后继 $j$，我们得到了 $h_{i,j}=pC_{bridge}$，同时我们也得到了 $g_i$ 的值。

现在我们需要求解的是所有 $j\in C$，$C\in \mathcal C_i$ 的 $h_{i,j}$。类似算法 $3$ 中处理环上路径概率的方法，此时 $h_{i,j}=\displaystyle pC_C\cdot\sum_{r=1}^2 \prod_{u\in \mathcal R_r} g_u$。

考虑如何计算 $pC_{bridge}$ 和 $pC_C$。

![](https://cdn.luogu.com.cn/upload/image_hosting/0vgkd8zp.png)

对于 $pC_{bridge}$，最终选择了路径是绕出了了一系列的环 $C_1,\cdots,C_k$ 然后选择了一条“出边”。因此有
$$
pC_{bridge}=\sum_{\mathcal S\subseteq \mathcal C_i}\left(k!\dfrac{1-p_i}{d_i-2k}\cdot (\prod_{t=0}^{k-1}\dfrac {2(1-p_i)}{d_i-2t})\cdot (\prod_{C\in \mathcal S}G_C)\right)
$$
类似地，我们用 $\mathcal C_i\backslash \{C\}$ 代替上式中的 $\mathcal C_i$ 即可得到 $pC_C$。

直接枚举所有子集 $\mathcal S$ 的时间复杂度是 $\mathcal O(2^KK^2)$，期望得分 $55$。

注意到所有 $|\mathcal S|=k$ 的情况有公因式 
$$
\displaystyle w_k=k!(1-p_i)^{k+1}2^k\prod_{t=0}^k \dfrac{1}{d_i-2t}
$$
考虑生成函数
$$
F(x)=\prod_{C\in \mathcal C_i}(1+G_C\cdot x)
$$
然后 $pC_{bridge}=\sum_k w_k\cdot [x^k]F(x)$，处理 $pC_C$ 时，可以 $\mathcal O(K)$ 的时间除以 $(1+G_c x)$。

时间复杂度为 $\mathcal O(\sum K^2)=\mathcal O(N^2)$，期望得分 $100$。

#### 算法 $5$：能不能再快一点啊？

在计算 $F(x)$ 的时候可以使用分治，每次将两边乘起来，复杂度为 $T(K)=2T(\dfrac K 2)+O(K\log K)$，即 $\mathcal O(K\log^2 K)$。

对于单次删去 $C$ 的情况，利用删物品背包的分治，假设当前求解的是不包含 $[l,r]$ 的 $C$ 的 $F(x)$，每次取 $mid=\dfrac{l+r}{2}$，计算 $(mid,r]$ 区间 $(1+G_cx)$ 的乘积。将两次分治合并起来，每次计算好 $[l,mid]$ 和 $(mid,r]$ 的乘积 $F_l,F_r$，然后令当前乘积变成 $F\times F_l$ 处理不包含 $(mid,r]$ 的情况；令当前乘积变成 $F\times F_r$ 处理不包含 $[l,mid]$ 的情况，最后再返回 $F_l\times F_r$。

总的时间复杂度 $\mathcal O(N\log^2 N)$，期望得分 $100$。

什么？$10^9+7$ 不是 NTT 模数？你说得对但是……

---

## 作者：NianFeng (赞：3)

好题要点赞！作为元芳厨，能推出来这个题觉得非常开心 >w<！

# 0x01 题意观察

比较关键的条件是好找的：**一**、Bessie 不走回头路；**二**、图中一条边属于 **不超过一个环**，即图是一个可爱的 **仙人掌**。$n \le 10^{4}$ 给的信息目前不多，只能推出复杂度上界 $\mathcal{O}(n^{2})$；$m \le \dfrac{3 (n - 1)}{2}$ 应该是仙人掌带来的性质，没啥用。

# 0x02 思路分析

这么一看条件还挺简洁。由于一般图 **有环** 是不好处理概率问题的，不难想到最后要建出 **狭义元芳树** 刻画问题。（诶是狭义吧，元芳树毕竟起源于仙人掌，广义元芳树是用于点双的吧……）但当务之急是找到 **有关于概率计算** 的性质，元芳树等下再管 qwq。（upd：如果推导过程有发现比较奇怪的地方，可以看 **0x04** 部分给出的两种元芳树定义……）

看一眼部分分，给的有点少，树的部分直接搜一边路径就没了，所以直接考虑 **环** 的处理。~~这个时候可以像我一样画几张图然后手算 4 整整版的路径概率然后发现啥规律也没有。~~ 其实是有微弱发现的：正着走和反着走环，到环上点的概率不同，但 **走完的概率相同**，又因为入环点有两条路走各带 $\dfrac{1}{2}$ 的概率，合起来就是环上每个点继续走环的概率乘积。

确实很微（mei）弱（yong），所以只能从 **暴力推式子** 的角度考虑了。放到元芳树上考虑游走，首先点 $x$ 的答案可以直接看作 $1 \rightsquigarrow x$ 的概率乘上停在 $x$ 的概率，于是只用关心 **走各种边的概率** 以及回到某个点的 **状态和概率**，因为能不能继续走会影响当前停不停的概率（不能走就成 $1$ 了）。接着对于一个 **元点**，游走过程形如 **走若干芳点后** 在任意子树内节点结束，或者本身在环里的话 **走环的下一步**；而 **芳点** 只能走完元点回去或者子树内结束。复杂之处在哪里呢？元点，因为 **走先导环** 会影响接下来选边的概率，于是对其重点讨论。

# 0x03 式子推导

思考哪些信息对元点的决策有影响。发现不论是走儿子元点还是走当前环的下一步，其结果都是 **不再回来**，说明这些决策的概率是 **没有后效性且相等的**。考虑一起计算，设 $q_{x} \ (x \le n)$ 为元点 $x$ 走完若干芳点后走这种 **不归路** 的概率；又发现走芳点也有可能在芳点内部结束游走，需要知道走完芳点的概率，也设为 $q_{x} \ (x > n)$，为作区分下面记为 $q'_{x}$。

发现这俩玩意儿存在 **互相依赖** 的关系，但都是树上父子关系的依赖，并不影响。$q'$ 实际上是好算的，$q'_{x} = \prod_{y \in \text{son}(x)} q_{y}$；$q$ 则需要一点点推导，考虑先导环组合对 $q$ 的概率影响，有式子：

$$
q_{x} = \sum_{S \subseteq \text{sonFang}(x)} (\prod_{i \in S} q'_{i}) \times (\prod_{i = 1}^{\lvert S \rvert} (1 - p_{x}) \cdot \frac{2 (\lvert S \rvert - i + 1)}{a + 2 (b - i + 1)}) \times (1 - p_{x}) \cdot \frac{1}{a + 2 (b - \lvert S \rvert)}
$$

意义是走完所有环的概率，乘上每一步不在 $x$ 结束且选中 $S$ 中环的概率（注意 $q'_{x}$ 只算了 **走完** 的概率！），再乘上选中任意出边的概率。然而看着非常不可以做，注意到与 $S$ **实际值** 有关的只有 $\prod q'$ 项，考虑枚举 $\lvert S \rvert$：

$$
q_{x} = \sum_{i = 0}^{b} (\prod_{j = 1}^{i} \frac{2 (i - j + 1)}{a + 2 (b - j + 1)}) \times (1 - p_{x}) \cdot \frac{1}{a + 2 (b - i)} \times \sum_{S \subseteq \text{sonFang}(x), \lvert S \rvert = i} \prod_{j \in S} (1 - p_{x}) \cdot q'_{j}
$$

诶这个时候我们发现后面一块是可以 $\mathcal{O}(n^{2})$ 背包的！（$1 - p_{x}$ 扔到后面是不想预处理幂次放背包里处理。）那么我们就只用关心前面了，设其为 $\text{calc}(a, b, i)$，我们需要让 $\text{calc}$ 是个 $\mathcal{O}(1)$ 的函数，于是大力拆式子（甚至是第一次写 $\LaTeX$ 的除号）：

$$
\begin{aligned}
\text{calc}(a, b, i) &= \prod_{j = 1}^{i} \frac{2 (i - j + 1)}{a + 2 (b - j + 1)} \\
&= \prod_{j = 0}^{i - 1} 2 (i - j) \div \prod_{j = 0}^{i - 1} a + 2 (b - j) \\
&= 2^{i} \times i! \div
\begin{cases}
2^{i} \times (\frac{a + 2 b}{2})! \div (\frac{a + 2 b - 2 i}{2})! &  2 \mid x \\
(x + 2 y + 1)! \div (x + 2 y - 2i - 1)! \div (2^{i} \times (\frac{a + 2 b + 1}{2})! \div (\frac{a + 2 b - 2 i - 1}{2})!) & 2 \nmid x
\end{cases} \\
&= \begin{cases}
i! \div (\frac{a + 2 b}{2})^{\underline{i}} & 2 \mid x \\
2^{2 i} \times i! \div ((x + 2 y + 1)^{\underline{i}} \div (\frac{x + 2 y + 1}{2})^{\underline{i}}) & 2 \nmid x
\end{cases}
\end{aligned}
$$

非常恐怖，不知道哪来的耐心推了三遍的，~~大概是厨力罢~~。不过感谢 @[Larryyu](https://www.luogu.com.cn/user/475329) 提醒，其实 [双阶乘](https://baike.baidu.com/item/%E5%8F%8C%E9%98%B6%E4%B9%98/9500461) 是可以预处理的，不用阶乘暴力推，大家不要学鼠（

总之 $\text{calc}$ 做到 $\mathcal{O}(1)$ 了，求 $q_{x}$ 的复杂度也可以接受力。整理一下，我们现在知道了走环的成功率、元点走不归路的概率，差了啥？**走芳点的概率以及走到环上某个点的概率。**

后者是好处理的，既然我们已经求出环上每个元点走向 **不归路** 的方案，那只要模拟一下按顺序乘概率就好了。思考前者，我们发现走点（或者说走边）的决策过程都是相似的，可以依照先前求 $q$ 的思路，枚举先导环算走入的概率。唯一的问题是，走的先导环不能包括自己，咋搞捏？这个简单，由于我们之前的背包 **不是判定性背包**，而是类似 **计数背包** 的形式，我们可以对于每个芳点 $\mathcal{O}(n)$ 做 **撤销背包**，由于搜索总 $\mathcal{O}(n)$ 不是瓶颈，总复杂度依旧 $\mathcal{O}(n^{2})$ 轻松通过。

于是这个章节就撒花了！但你先别急，还有代码，如果愿意且听我有点菜的实现……

# 0x04 小小细节

现在可以考虑元芳树了。相比于大部分人先学的广义元芳树，仙人掌上的狭义元芳树有这么一个特点：**存在两个直接相连的元点**。

![img](https://img2023.cnblogs.com/blog/3531269/202502/3531269-20250223213121932-750272196.png)

上（~~博客中为数不多~~）图就是一个示例。狭义元芳树路径不是元芳点交替的原因在于，其只将 **一个环** 当作一个整体，而不是 **一个点双连通分量**。这限制了其对一般图的处理，却有一个有点：更为 **完整地** 保留了环的信息（相对点双），同时减少了特殊图上的分讨问题。所以广义元芳树在这题是可以做的，只不过细节更多。

于是相对应的，改一下 tarjan 建元芳树的代码：

```cpp
/* declaration */
int dfn[N], low[N], cnt, tot;    // 时间戳，总点数
std::vector<std::pair<int, int>> G[M][2];
// 元芳树用 vector 存，pair<int, int> 相当于把走边的概率记为边权了方便处理
static std::stack<int> s;        // 定义在 tarjan 里记录路径的栈

/* kernel */
if (!dfn[y]) {
   tarjan(y, x);

   if (low[y] > dfn[x]) {
      // 最小后继大于时间戳，说明 DFS 生成树子树中没有连向祖先的边
      // 人话就是可以直接连
      G[x][0].emplace_back(y, 0);
      G[y][0].emplace_back(x, 0);

      s.pop();
   } else if (low[y] == dfn[x]) {
      // 刚好成环，x 是环开始的地方，于是取出环上的点连虚点
      // 注意到 stack 中的存点顺序是搜索序，我们取出来的点实际上保存了环的相对顺序
      G[++tot][0].clear(), G[tot][1].clear();

      while (s.top() ^ y) {
         int k = s.top();
         s.pop();

         G[tot][0].emplace_back(k, 0);
         G[k][1].emplace_back(tot, 0);
      }

      s.pop();

      G[tot][0].emplace_back(y, 0);
      G[tot][0].emplace_back(x, 0);

      G[y][1].emplace_back(tot, 0);
      G[x][1].emplace_back(tot, 0);
   } else
      chkMn(low[x], low[y]);
} else
   chkMn(low[x], dfn[y]);
```

随后是处理 $q_{x}$ 等信息。有没有发现前面漏讲了 **停在某个点的概率** 怎么求，这是跟 $q_{x}$ 差不多的，只不过要考虑剩下出边的数量，于是俩小只放一起求，这也就是为啥上面推式子时给 $\text{calc}$ 函数求的东西留了一手。同样为了方便起见，吾将元芳点分别封装成一个 DFS 函数：

```cpp
/* kernel */

int q[M], res[N];
// q：元点是不归路概率，芳点是走完环概率；res：停住的概率
void DFS_Yuan(int, int), DFS_Fang(int, int);
// 注意到两个 DFS 互相嵌套，事先声明
int calc(int x, int y, int i) {  // 这个实现随意了 qwq
   int t = x + y * 2 + (x & 1);

   if (x & 1)
      return mod(mod(1ll * fac[i] * pw[i * 2]) *
                 mod(1ll * fallInv(t, 2 * i) * fallFac(t / 2, i)));
   else
      return mod(1ll * fac[i] * fallInv(t / 2, i));
}

void DFS_Yuan(int x, int fa) {
   auto &G0 = G[x][0], &G1 = G[x][1];

   if (fa > n)                                     // 提前删父亲
      G1.erase(std::find(G1.begin(), G1.end(), std::make_pair(fa, 0)));
   else if (fa)
      G0.erase(std::find(G0.begin(), G0.end(), std::make_pair(fa, 0)));

   // a, b 分别是不归路数量和芳点数量，dp 就是背包数组
   int a = G0.size() + (fa > n), b = G1.size(), t = sub(1, p[x]);
   std::vector<int> dp(b + 1);

   dp[0] = 1;
   for (auto [y, z] : G1) {
      DFS_Fang(y, x);                              // 先处理芳点，算元点概率需要

      int k = mod(1ll * t * q[y]);                 // 算上 x 点不停的概率

      for (int i = b; i; --i) pls(dp[i], mod(1ll * dp[i - 1] * k));
   }

   q[x] = res[x] = 0;
   for (int i = 0; i <= b; ++i) {
      pls(q[x], mod(mod(1ll * calc(a, b, i) * dp[i]) *
                    mod(1ll * t * inv[a + b * 2 - i * 2])));

      pls(res[x], mod(mod(1ll * calc(a, b, i) * dp[i]) *
                      (a + b - i ? p[x] : 1)));    // 判掉剩余出边
   }

   for (auto &[y, z] : G1) {
      int k = mod(1ll * t * q[y]);

      // 撤销背包，计算走芳点的概率
      for (int i = 1; i <= b; ++i) dec(dp[i], mod(1ll * dp[i - 1] * k));

      for (int i = 0; i < b; ++i)
         pls(z, mod(mod(1ll * calc(a + 2, b - 1, i) * dp[i]) *
      mod(2ll * t * inv[a + b * 2 - i * 2])));

      for (int i = b; i; --i) pls(dp[i], mod(1ll * dp[i - 1] * k));
   }

   for (auto &[y, z] : G0) {
      z = q[x];

      DFS_Yuan(y, x);
   }
}
void DFS_Fang(int x, int fa) {
   auto &G = ::G[x][0];

   G.erase(std::find(G.begin(), G.end(), std::make_pair(fa, 0)));

   int t = INV_2;

   for (auto &[y, z] : G) {
      DFS_Yuan(y, x);

      pls(z, t), mul(t, q[y]);      // 前后缀就没啥技术含量了
   }

   t = INV_2;
   for (int i = G.size() - 1; ~i; --i) {
      auto &[y, z] = G[i];

      pls(z, t), mul(t, q[y]);

      if (!i) q[x] = add(t, t);     // 注意一下初始概率是 0.5
   }
}
```

诶怎么写的时候感觉那么困难勒，鉴定为菜导致的。

# 0x05 纯享代码

7.5 KB 其实不那么纯享。是不是应该放剪切板（鼠鼠异或 /yiw）……

```cpp
/* 年挽红枫，溪傍芦荻。*/

#ifdef DEBUG
#include <iostream>
#include <cmath>
#include <ctime>

bool Mbe;
void _Dihan();
#endif

#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>

typedef long long i64;
typedef unsigned long long ull;
typedef double f32;
typedef long double ldb;
typedef __int128 i28;
typedef unsigned uit;

template <typename T>
inline bool chkMx(T &x, T y) { return x < y ? x = y, true : false; }
template <typename T>
inline bool chkMn(T &x, T y) { return x > y ? x = y, true : false; }

namespace IO {

#define file(s) freopen(#s".in", "r", stdin), freopen(#s".out", "w", stdout)

constexpr int SIZE = 1 << 21;

char ibuf[SIZE], *p1 = ibuf, *p2 = ibuf, obuf[SIZE], *p3 = obuf;

#define flush() (fwrite(obuf, 1, p3 - obuf, stdout), p3 = obuf)
#define gc()                                                               \
   (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, SIZE, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
#define pc(ch) (p3 == obuf + SIZE && flush(), *p3++ = ch)

class Flush { public: ~Flush() { flush(); } } _;

template <typename T>
inline void read(T &x) {
   static char c;
   static int f;

   x = f = 0;
   while (!isdigit(c = gc())) f |= c == '-';

   while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
   f && (x = -x);
}
template <typename T>
inline T read() {
   static T x;

   return read(x), x;
}

template <typename T>
inline void write(T x) {
   static char s[50];
   static int t;

   x < 0 && (pc('-'), x = -x);
   do s[++t] = x % 10 ^ 48; while (x /= 10);

   while (t) pc(s[t--]);
}
inline void write(char c) { pc(c); }
template <typename T>
inline void write(T *s) { while (*s) pc(*s++); }

template <typename ...Args>
inline void read(Args &...args) { (read(args), ...); }
template <typename ...Args>
inline void write(Args ...args) { (write(args), ...); }

}  // namespace IO
using namespace IO;

constexpr int N = 1e4 + 5;
constexpr int M = 1.5e4 + 5;

namespace Math {

constexpr int P = 1e9 + 7;
constexpr int INV_2 = 5e8 + 4;

#define mod(x) ((x) % P)

inline int &pls(int &x, int y) { return (x += y) < P || (x -= P), x; }
inline int &dec(int &x, int y) { return (x -= y) < 0 && (x += P), x; }
inline int &mul(int &x, int y) { return x = mod(1ll * x * y); }

inline int add(int x, int y) { return pls(x, y); }
inline int sub(int x, int y) { return dec(x, y); }

inline int quickPow(int a, int x = P - 2, int ret = 1) {
   for (; x; x >>= 1, mul(a, a)) x & 1 && mul(ret, a);

   return ret;
}

int fac[N], iFac[N];
void initFac() {
   fac[0] = 1;
   for (int i = 1; i < N; ++i) fac[i] = mod(1ll * fac[i - 1] * i);

   iFac[N - 1] = quickPow(fac[N - 1]);
   for (int i = N - 1; i; --i) iFac[i - 1] = mod(1ll * iFac[i] * i);
}
int fallFac(int a, int x) {
   if (a - x <= 0) return fac[a];

   return mod(1ll * fac[a] * iFac[a - x]);
}
int fallInv(int a, int x) {
   if (a - x <= 0) return iFac[a];

   return mod(1ll * iFac[a] * fac[a - x]);
}

int inv[N];
void initInv() {
   inv[1] = 1;
   for (int i = 2; i < N; ++i) inv[i] = sub(0, mod(1ll * P / i * inv[P % i]));
}

int pw[N];
void initPw() {
   pw[0] = 1;
   for (int i = 1; i < N; ++i) pw[i] = add(pw[i - 1], pw[i - 1]);
}

class Init { public: Init() { initFac(), initInv(), initPw(); } } $;

}  // namespace Math
using namespace Math;

int n, m, p[N];
struct Edge {
   int t, nx;
} eg[M << 1];
int nm, hd[N];
void addEdge(int f, int t) {
   eg[++nm] = {t, hd[f]};
   hd[f] = nm;
}

int dfn[N], low[N], cnt, tot;
std::vector<std::pair<int, int>> G[M][2];
void tarjan(int x, int fa) {
   static std::stack<int> s;

   dfn[x] = low[x] = ++cnt, s.emplace(x);
   G[x][0].clear(), G[x][1].clear();

   for (int i = hd[x]; i; i = eg[i].nx) {
      int y = eg[i].t;
      if (y == fa) continue;

      if (!dfn[y]) {
         tarjan(y, x);

         if (low[y] > dfn[x]) {
            G[x][0].emplace_back(y, 0);
            G[y][0].emplace_back(x, 0);

            s.pop();
         } else if (low[y] == dfn[x]) {
            G[++tot][0].clear(), G[tot][1].clear();

            while (s.top() ^ y) {
               int k = s.top();
               s.pop();

               G[tot][0].emplace_back(k, 0);
               G[k][1].emplace_back(tot, 0);
            }

            s.pop();

            G[tot][0].emplace_back(y, 0);
            G[tot][0].emplace_back(x, 0);

            G[y][1].emplace_back(tot, 0);
            G[x][1].emplace_back(tot, 0);
         } else
            chkMn(low[x], low[y]);
      } else
         chkMn(low[x], dfn[y]);
   }
}

int q[M], res[N];
void DFS_Yuan(int, int), DFS_Fang(int, int);
int calc(int x, int y, int i) {
   int t = x + y * 2 + (x & 1);

   if (x & 1)
      return mod(mod(1ll * fac[i] * pw[i * 2]) *
                 mod(1ll * fallInv(t, 2 * i) * fallFac(t / 2, i)));
   else
      return mod(1ll * fac[i] * fallInv(t / 2, i));
}

void DFS_Yuan(int x, int fa) {
   auto &G0 = G[x][0], &G1 = G[x][1];

   if (fa > n)
      G1.erase(std::find(G1.begin(), G1.end(), std::make_pair(fa, 0)));
   else if (fa)
      G0.erase(std::find(G0.begin(), G0.end(), std::make_pair(fa, 0)));

   int a = G0.size() + (fa > n), b = G1.size(), t = sub(1, p[x]);
   std::vector<int> dp(b + 1);

   dp[0] = 1;
   for (auto [y, z] : G1) {
      DFS_Fang(y, x);

      int k = mod(1ll * t * q[y]);

      for (int i = b; i; --i) pls(dp[i], mod(1ll * dp[i - 1] * k));
   }

   q[x] = res[x] = 0;
   for (int i = 0; i <= b; ++i) {
      pls(q[x], mod(mod(1ll * calc(a, b, i) * dp[i]) *
                    mod(1ll * t * inv[a + b * 2 - i * 2])));

      pls(res[x], mod(mod(1ll * calc(a, b, i) * dp[i]) *
                      (a + b - i ? p[x] : 1)));
   }

   for (auto &[y, z] : G1) {
      int k = mod(1ll * t * q[y]);

      for (int i = 1; i <= b; ++i) dec(dp[i], mod(1ll * dp[i - 1] * k));

      for (int i = 0; i < b; ++i)
         pls(z, mod(mod(1ll * calc(a + 2, b - 1, i) * dp[i]) *
                    mod(2ll * t * inv[a + b * 2 - i * 2])));

      for (int i = b; i; --i) pls(dp[i], mod(1ll * dp[i - 1] * k));
   }

   for (auto &[y, z] : G0) {
      z = q[x];

      DFS_Yuan(y, x);
   }
}
void DFS_Fang(int x, int fa) {
   auto &G = ::G[x][0];

   G.erase(std::find(G.begin(), G.end(), std::make_pair(fa, 0)));

   int t = INV_2;

   for (auto &[y, z] : G) {
      DFS_Yuan(y, x);

      pls(z, t), mul(t, q[y]);
   }

   t = INV_2;
   for (int i = G.size() - 1; ~i; --i) {
      auto &[y, z] = G[i];

      pls(z, t), mul(t, q[y]);

      if (!i) q[x] = add(t, t);
   }
}

void getResult(int x, int cur) {
   if (x <= n) mul(res[x], cur);

   for (int i : {0, 1}) for (auto [y, z] : G[x][i])
      getResult(y, mod(1ll * z * cur));
}

void work() {
   read(n, m);
   for (int i = 1; i <= n; ++i) read(p[i]);

   nm = 0, memset(hd + 1, 0, n * sizeof(int));
   for (int i = 1, x, y; i <= m; ++i)
      read(x, y), addEdge(x, y), addEdge(y, x);

   cnt = 0, memset(dfn + 1, 0, n * sizeof(int)), tot = n;
   tarjan(1, 0);
   
   DFS_Yuan(1, 0), getResult(1, 1);

   for (int i = 1; i <= n; ++i) write(res[i], " \n"[i == n]);
}

int main() {
#ifdef DEBUG
   file(cur);
#endif

   for (int _T = read<int>(); _T; --_T) work();

#ifdef DEBUG
   _Dihan();
#endif
   return 0;
}

#ifdef DEBUG
bool Med;
void _Dihan() {
   std::cerr << "Memory: " << abs(&Med - &Mbe) / 1048576.0 << " MB\n";
   std::cerr << "Time: " << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
}
#endif
```

# 0x3f 总结后话

发现不看题解写出来题其实是一种享受，没必要纯粹为了量而刷题。题目的中心思想就是 **用较为简单的模型刻画复杂的过程**。在写代码的过程中还是有多次停下来重构，反映出在纸上推导的能力仍不足，虽然分讨也有点小烦就是啦。应该是改码风后的第一篇题解，实际上在总结反思题目方面还有很大的进步空间，需要努力。

感谢您的垂阅，有错误/不足之处欢迎指出 owo！

---

## 作者：tobie (赞：0)

考虑拆分一次游走过程：我们定义“一次操作”为在 $u$ 处进行一次判定后发现没有结束，然后从 $u$ 走到 $v$。

设当前状态下 $u$ 的出度为 $d$，则该次操作的贡献为 $\dfrac {(1-p_u)} d$。

以下 dp 过程中使用“概率”一词似乎并不是非常恰当，我们认为一条路径的“权值”为每次操作的贡献的乘积。自然想到设 $f_u$ 表示所有**第一次**走到 $u$ 的路径的权值和。

首先建出圆方树。对于一个节点 $u$，如果我们钦定最后在 $u$ 节点停下，则我们的过程必然会分为如下阶段：

1. 首先我们要走到 $u$，贡献为 $f_u$。
2. 然后我们可能会穿过 $u$ 节点**子树内**的若干个环回到 $u$ 节点，然后再下一次操作的“判定”时倒闭。

这里我们发现从 $u$ 出发穿过一个环然后回到 $u$ 的过程也是很重要的。结合以上分析，我们定义如下状态：

1. $f_u$ 表示从 $1$ 出发，**第一次**走到 $u$ 的所有路径权值和。
2. $g_u$ 表示从 $fa_u$ 出发，绕着 $u$ 对应的点走一圈的路径权值和。$g_u$ 只在方点处有定义。
3. $h_u$ 表示从 $1$ 出发到达 $u$ 后，在 $u$ 上绕若干圈之后，再从 $u$ 出发走一步的路径在 $u$ 之后的所有操作的权值和。

![](https://cdn.luogu.com.cn/upload/image_hosting/0ypfhcuk.png)

- - -

$g_u$ 的转移是最容易的：蓝色环的贡献为 $h_v$，红色边的贡献直接计算即可。

现在考虑计算 $h_u$。

假设我们从 $u$ 节点出发，选择了 $S$ 中的方点对应的环，最后回到 $u$ 节点的贡献差不多长成这个样子：

$$\frac {d_0^{|S|} d_0!!|S|!}{(d_0-2|S|)!!}\prod_{v\in S} g_v$$

解释一下意思：每个环的贡献显然就是 $g_v$，先乘上，然后考虑修正。

每次从 $u$ 出发时，$u$ 的出度分别为 $d_0,d_0-2,d_0-4,\cdots$，而 $g_v$ 里的贡献为 $\frac 1 d$，所以需要乘上 $\frac d {d_0-2k}$ 的修正项；$S$ 中元素没有顺序还会带来 $|S|!$ 的贡献；

你发现我们只在乎选取的集合的 $|S|$ 和 $\prod g_v$，跑一遍背包，然后带入公式计算即可。

写代码时发现这个式子还需要进行一些修补，比如需要考虑走完之后的那个红色的出边，以及 $u=1$ 时的 $d_0$ 和其他情况略有不同，需要特别注意。

计算 $g_u$ 和 $h_u$ 可以自底向上跑一遍 dfs。复杂度 $O(n^2)$。

- - -

接下来考虑如何计算 $f_u$。

![](https://cdn.luogu.com.cn/upload/image_hosting/k7uxhvq8.png)

如图。目前已知你第一次走到了 $u$，则你会先走绿色的环，然后颜色红色边走到 $v$，途中还可能经过一些蓝色的环。

蓝色的环贡献就是 $h_x$，红色边可以直接计算，现在只需要考虑绿色边。

我们发现，可以选的绿色圈的集合 $S_0$ 是 $u$ 子树内所有可以选择的圈的集合 $S$ 去掉当前这个环，所以跑一个撤销背包即可，式子同上。

至于答案的计算，你只需要把 $f_u$ 和 $h_u$ 拼起来就行了。

综上，总复杂度为 $O(n^2)$，瓶颈在背包。可以用分治 NTT 做到 $O(n \log ^2 n)$，懒得写了，就这样吧。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int N=20009;
const int mod=1e9+7;

int inv[N];

int n,ncnt=0,a[N],deg[N];

vector<int> to[N];
int siz[N];

namespace Build{

vector<int> G[N];
int m;

int dfn[N],low[N],dfncnt=0;
int sta[N],tp=0;

void dfs(int u,int f)
{
	dfn[u]=low[u]=++dfncnt;
	sta[++tp]=u;
	for(int v:G[u])
	if(!dfn[v])
	{
		dfs(v,u);
		low[u]=min(low[u],low[v]);
		if(low[v]==dfn[u])
		{
			ncnt++;
			to[ncnt].push_back(u);
			to[u].push_back(ncnt);
			siz[ncnt]=1;
			for(int x=0;x!=v;tp--)
			{
				x=sta[tp];
				to[ncnt].push_back(x);
				to[x].push_back(ncnt);
				siz[ncnt]++;
			}
		}
	}
	else low[u]=min(low[u],dfn[v]);
}

void ReadIn()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n*2;i++) to[i].clear(),G[i].clear(),siz[i]=0;
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	for(int i=1;i<=n*2;i++) dfn[i]=low[i]=0;
	dfncnt=0,tp=0;
	for(int i=1;i<=n;i++) deg[i]=G[i].size();
	ncnt=n;
	dfs(1,0);
}

}
using Build::ReadIn;

int g[N],h[N];

void dfs1(int u,int f)
{
	if(u>n)
	{
		g[u]=2ll*(mod+1-a[f])*inv[deg[f]]%mod;
		for(int v:to[u])
		if(v!=f)
		{
			dfs1(v,u);
			g[u]=1ll*g[u]*h[v]%mod;
		}
	}
	else
	{
		for(int v:to[u]) if(v!=f) dfs1(v,u);
		vector<int> tmp; tmp.push_back(1);
		for(int v:to[u])
		if(v!=f&&siz[v]>2)
		{
			tmp.push_back(0);
			for(int i=(int)(tmp.size())-1;i;i--)
			tmp[i]=(1ll*tmp[i-1]*g[v]+tmp[i])%mod;
		}
		int d1=deg[u],d2=deg[u]-(f!=0),s1=(mod+1-a[u])%mod;
		for(int i=0;i<tmp.size();i++)
		{
			h[u]=(h[u]+1ll*tmp[i]*s1%mod*inv[d2])%mod;
			s1=1ll*s1*d1%mod*inv[d2]%mod*(i+1)%mod;
			d2-=2;
		}
	}
}

int f[N],ans[N];
void dfs2(int u,int fa)
{
	vector<int> tmp; tmp.push_back(1);
	for(int v:to[u])
	if(v!=fa&&siz[v]>2)
	{
		tmp.push_back(0);
		for(int i=(int)(tmp.size())-1;i;i--)
		tmp[i]=(1ll*tmp[i-1]*g[v]+tmp[i])%mod;
	}
	int d1=deg[u], d2=deg[u]-(fa!=0), s1=1;
	for(int i=0;i<tmp.size();i++)
	{
		ans[u]=(ans[u]+1ll*tmp[i]*(d2==0?1:a[u])%mod*s1)%mod;
		s1=1ll*s1*d1%mod*inv[d2]%mod*(i+1)%mod;
		d2-=2;
	}
	ans[u]=1ll*ans[u]*f[u]%mod;
	
	for(int vv:to[u])
	if(vv==fa) continue;
	else if(siz[vv]==2)
	{
		for(int v:to[vv])
		if(v!=u)
		{
			d1=deg[u], d2=deg[u]-(fa!=0), s1=1ll*f[u]*(mod+1-a[u])%mod;
			for(int i=0;i<tmp.size();i++)
			{
				f[v]=(f[v]+1ll*tmp[i]*s1%mod*inv[d2])%mod;
				s1=1ll*s1*d1%mod*inv[d2]%mod*(i+1)%mod;
				d2-=2;
			}
			dfs2(v,vv);
		}
	}
	else
	{
		vector<int> tmp2=tmp;
		for(int i=1;i<tmp.size();i++)
		tmp[i]=(tmp[i]+1ll*(mod-g[vv])*tmp[i-1])%mod;
		tmp.pop_back();
		int coaf=1ll*f[u]*(mod+1-a[u])%mod;
		for(int i=1;i<to[vv].size();i++)
		{
			d1=deg[u], d2=deg[u]-(fa!=0), s1=coaf;
			for(int j=0;j<tmp.size();j++)
			{
				(f[to[vv][i]]+=1ll*tmp[j]*s1%mod*inv[d2]%mod)%=mod;
				s1=1ll*s1*d1%mod*inv[d2]%mod*(j+1)%mod;
				d2-=2;
			}
			coaf=1ll*coaf*h[to[vv][i]]%mod;
		}
		coaf=1ll*f[u]*(mod+1-a[u])%mod;
		for(int i=(int)(to[vv].size())-1;i>=1;i--)
		{
			d1=deg[u], d2=deg[u]-(fa!=0), s1=coaf;
			for(int j=0;j<tmp.size();j++)
			{
				(f[to[vv][i]]+=1ll*tmp[j]*s1%mod*inv[d2]%mod)%=mod;
				s1=1ll*s1*d1%mod*inv[d2]%mod*(j+1)%mod;
				d2-=2;
			}
			coaf=1ll*coaf*h[to[vv][i]]%mod;
		}
		
		swap(tmp,tmp2);
		
		for(int v:to[vv]) if(v!=u) dfs2(v,vv);
	}
}

void work()
{
	ReadIn();
	for(int i=1;i<=ncnt;i++) f[i]=g[i]=h[i]=ans[i]=0;
	dfs1(1,0);
	f[1]=1;
	dfs2(1,0);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	puts("");
}
signed main()
{
	int T;
	scanf("%d",&T);
	inv[0]=inv[1]=1; 
	for(int i=2;i<=20000;i++) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	while(T--) work();
}
```

---

