# Wish Upon a Satellite (Hard Version)

## 题目描述

这是该问题的困难版本。与简单版本的区别在于，本版本中 $t \le 10^4$、$n \le 5 \times 10^5$ 且所有测试用例的 $n$ 之和不超过 $5\times 10^5$。只有当你解决了该问题的所有版本时才能进行 hack。

对于一个长度为 $k$ 的非空序列 $c$，定义 $f(c)$ 如下：

- Turtle 和 Piggy 正在一个序列上玩游戏。他们被给定序列 $c_1, c_2, \ldots, c_k$，由 Turtle 先手。Turtle 和 Piggy 轮流进行操作（Turtle 第一步，Piggy 第二步，Turtle 第三步，依此类推）。
- 游戏规则如下：
  - 设当前序列长度为 $m$。如果 $m = 1$，游戏结束。
  - 如果游戏未结束且轮到 Turtle，Turtle 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\min(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
  - 如果游戏未结束且轮到 Piggy，Piggy 必须选择一个整数 $i$（$1 \le i \le m - 1$），将 $c_i$ 设为 $\max(c_i, c_{i + 1})$，并删除 $c_{i + 1}$。
- Turtle 希望最终 $c_1$ 的值最大化，而 Piggy 希望最终 $c_1$ 的值最小化。
- $f(c)$ 表示双方都采取最优策略时，最终 $c_1$ 的值。

对于一个长度为 $n$ 的排列 $p$ $^{\text{∗}}$，Turtle 定义该排列的美观度为 $\sum\limits_{i = 1}^n \sum\limits_{j = i}^n f([p_i, p_{i + 1}, \ldots, p_j])$（即所有 $p$ 的非空子段 $^{\text{†}}$ $c$ 的 $f(c)$ 之和）。

Piggy 给 Turtle 一个长度为 $n$ 的排列 $a$，其中部分元素缺失（用 $0$ 表示）。

Turtle 请你确定一个排列 $b$，满足以下条件：

- $b$ 可以通过填充 $a$ 中缺失的元素得到（即对于所有 $1 \le i \le n$，如果 $a_i \ne 0$，则 $b_i = a_i$）。
- 排列 $b$ 的美观度最大化。

为了方便，你只需要找到这样的排列 $b$ 的最大美观度。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

$^{\text{†}}$ 序列 $a$ 是序列 $b$ 的子段，当且仅当 $a$ 可以通过从 $b$ 的开头和结尾删除若干（可能为零或全部）元素得到。

## 说明/提示

- 在第一个测试用例中，美观度最大的排列 $b$ 是 $[1, 2]$。$[1, 2]$ 的美观度为 $4$，因为 $f([1]) + f([2]) + f([1, 2]) = 1 + 2 + 1 = 4$。如果 $c = [1, 2]$，则 $f(c) = 1$，因为 Turtle 只能选择 $i = 1$，并将 $c_1$ 设为 $\min(c_1, c_2) = 1$。

- 在第二个测试用例中，美观度最大的排列之一是 $[3, 2, 1]$。$[3, 2, 1]$ 的美观度为 $12$，因为 $f([3]) + f([2]) + f([1]) + f([3, 2]) + f([2, 1]) + f([3, 2, 1]) = 3 + 2 + 1 + 2 + 1 + 3 = 12$。

- 在第三个测试用例中，美观度最大的排列之一是 $[2, 1, 3]$。

- 在第四个测试用例中，如果 $c = [3, 2, 4, 5, 1]$，则 $f(c) = 3$。一种可能的游戏过程如下：
  - Turtle 选择 $i = 3$，将 $c_3$ 设为 $\min(c_3, c_4) = 4$ 并删除 $c_4$。序列变为 $[3, 2, 4, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3, 4, 1]$。
  - Turtle 选择 $i = 2$，将 $c_2$ 设为 $\min(c_2, c_3) = 1$ 并删除 $c_3$。序列变为 $[3, 1]$。
  - Piggy 选择 $i = 1$，将 $c_1$ 设为 $\max(c_1, c_2) = 3$ 并删除 $c_2$。序列变为 $[3]$。
  - 序列长度为 $1$，游戏结束。最终 $c_1$ 的值为 $3$。

- 在第五个测试用例中，美观度最大的排列之一是 $[1, 3, 2, 5, 6, 4, 7]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
2
1 0
3
0 0 0
3
0 1 0
5
3 2 4 5 1
7
0 3 2 5 0 0 0
10
1 2 6 5 8 9 0 0 0 0
5
0 4 1 0 0
5
0 1 5 2 3```

### 输出

```
4
12
11
44
110
300
45
40```

# 题解

## 作者：EuphoricStar (赞：2)

## Easy Version

首先，我们有：

$$
f(c) = \begin{cases} \min(c_1, c_k) & k \bmod 2 = 0 \\ \max(c_1, c_k) & k \bmod 2 = 1 \end{cases}
$$

对称地设 $g(c)$ 为调换先后手顺序后的答案，那么：

$$
g(c) = \begin{cases} \max(c_1, c_k) & k \bmod 2 = 0 \\ \min(c_1, c_k) & k \bmod 2 = 1 \end{cases}
$$

证明：考虑归纳。$k \le 2$ 显然成立。对于 $k \ge 3$，考虑 $f(c)$ 的计算。假设 $k$ 为奇数。若先手选择 $2 \le i \le k - 2$ 递归到 $g(c')$，那么答案为 $\max(c_1, c_k)$；若先手选择 $i = 1$ 或 $i = k - 1$，那么答案 $\le \max(c_1, c_k)$。其余情况同理。

所以对于一个排列 $p_1, p_2, \ldots, p_n$：

$$
\begin{aligned} & \sum\limits_{i = 1}^n \sum\limits_{j = i}^n f([p_i, p_{i + 1}, \ldots, p_j]) \\ = & \sum\limits_{i = 1}^n \sum\limits_{j = i}^n \Big([i \bmod 2 = j \bmod 2] \max(p_i, p_j) + [i \bmod 2 \ne j \bmod 2] \min(p_i, p_j)\Big) \\ = & \sum\limits_{i = 1}^n \sum\limits_{j = i}^n \max(p_i, p_j) - [i \bmod 2 \ne j \bmod 2] (\max(p_i, p_j) - \min(p_i, p_j)) \\ = & \sum\limits_{i = 1}^n i^2 - \sum\limits_{i = 1}^n \sum\limits_{j = i + 1}^n [i \bmod 2 \ne j \bmod 2] |p_i - p_j| \end{aligned}
$$

所以现在的问题变成了最小化以下式子：

$$
\sum\limits_{i = 1}^n \sum\limits_{j = i + 1}^n [i \bmod 2 \ne j \bmod 2] |b_i - b_j|
$$

这个问题可以进一步变成：有一个 $1 \sim n$ 的数轴，点 $i$ 可能是黑色、白色或未确定。若 $i$ 在 $a$ 中的位置为奇数就是黑色，为偶数就是白色，在 $a$ 中未出现则为不确定。我们现在要把未确定的点染成黑色或者白色，使得：

- 恰好有 $\left\lceil\frac{n}{2}\right\rceil$ 个黑点；
- 最小化所有不同颜色点对的距离之和。

所有不同颜色点对的距离之和可以变成：对于所有 $1 \le k < n$，$1 \sim k$ 中的黑点数量乘 $k + 1 \sim n$ 的白点数量加上 $1 \sim k$ 中的白点数量乘 $k + 1 \sim n$ 的黑点数量之和。

这个简化后的问题可以 DP 了。设 $f_{i, j}$ 表示已经确定了 $1 \sim i$ 中的点的颜色，其中有 $j$ 个黑点，对于所有 $1 \le k < i$ 上述式子的和的最小值。

至于转移，考虑先将 $f_{i, j}$ 加上 $k = i$ 时上述式子的值，即将所有 $f_{i, j}$ 加上 $j \times (\left\lfloor\frac{n}{2}\right\rfloor - (i - j)) + (i - j) \times (\left\lceil\frac{n}{2}\right\rceil - j)$。

然后考虑第 $i + 1$ 个点是黑点或者白点。

- 若第 $i + 1$ 个点可以是白点，有转移 $f_{i + 1, j} = \min(f_{i + 1, j}, f_{i, j})$；
- 若第 $i + 1$ 个点可以是黑点，有转移 $f_{i + 1, j + 1} = \min(f_{i + 1, j + 1}, f_{i, j})$。

最后的答案即为 $\sum\limits_{i = 1}^n i^2 - f_{n, \left\lceil\frac{n}{2}\right\rceil}$。

时间复杂度：每组测试用例 $O(n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n + 1, -1);
	vector< vector<ll> > f(n + 1, vector<ll>(n + 1, 1e18));
	for (int i = 1, x; i <= n; ++i) {
		cin >> x;
		if (x) {
			a[x] = i & 1;
		}
	}
	if (a[1] != 1) {
		f[1][0] = 0;
	}
	if (a[1] != 0) {
		f[1][1] = 0;
	}
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			f[i][j] += j * (n / 2 - (i - j)) + (i - j) * ((n + 1) / 2 - j);
			if (a[i + 1] != 1) {
				f[i + 1][j] = min(f[i + 1][j], f[i][j]);
			}
			if (a[i + 1] != 0) {
				f[i + 1][j + 1] = min(f[i + 1][j + 1], f[i][j]);
			}
		}
	}
	ll ans = -f[n][(n + 1) / 2];
	for (int i = 1; i <= n; ++i) {
		ans += i * i;
	}
	cout << ans << '\n';
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

## Hard Version

考虑我们每次要对 DP 数组进行什么操作：

- 对于所有 $j$，将 $f_{i, j}$ 加上 $j \times (\left\lfloor\frac{n}{2}\right\rfloor - (i - j)) + (i - j) \times (\left\lceil\frac{n}{2}\right\rceil - j) = 2 j^2 + (-2i - (n \bmod 2)) j + i \cdot \left\lceil\frac{n}{2}\right\rceil$ 即关于 $j$ 的一个二次函数；
- 执行 $f_{i + 1, j} = \min(f_{i + 1, j}, f_{i, j})$；
- 执行 $f_{i + 1, j + 1} = \min(f_{i + 1, j + 1}, f_{i, j})$。

可以归纳地证明 $f_{i, j}$ 下凸，即 $f_i$ 的差分数组是不降的。考虑维护 $f_{i, j}$ 的差分数组即 $g_{i, j} = f_{i, j + 1} - f_{i, j}$。那么操作变成：

- 对于所有 $j$，将 $g_{i, j}$ 加上一个关于 $j$ 的一次函数；
- 将 $g_{i, j}$ 整体向右平移一位；
- 向 $g_i$ 中插入一个 $0$，并保持 $g_i$ 有序。

考虑用 Treap 维护 $g_{i, j}$。Treap 的每个结点维护对应的 $g_{i, j}$ 的值以及下标 $j$ 的值，那么操作都可以改写成 $(g_{i, j}, j)$ 的线性的变换，可以用向量和矩阵维护。

时间复杂度：每组测试用例 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 500100;

int n, a[maxn];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int p[maxn], nt, ls[maxn], rs[maxn], sz[maxn];
bool vis[maxn];

struct vec {
	ll a0, a1, a2;
	vec(ll a = 0, ll b = 0, ll c = 0) : a0(a), a1(b), a2(c) {}
} val[maxn];

struct mat {
	ll a00, a01, a02, a10, a11, a12, a20, a21, a22;
	mat(ll a = 0, ll b = 0, ll c = 0, ll d = 0, ll e = 0, ll f = 0, ll g = 0, ll h = 0, ll i = 0) : a00(a), a01(b), a02(c), a10(d), a11(e), a12(f), a20(g), a21(h), a22(i) {}
} I, tag[maxn];

inline vec operator * (const vec &a, const mat &b) {
	vec res;
	res.a0 = a.a0 * b.a00 + a.a1 * b.a10 + a.a2 * b.a20;
	res.a1 = a.a0 * b.a01 + a.a1 * b.a11 + a.a2 * b.a21;
	res.a2 = a.a0 * b.a02 + a.a1 * b.a12 + a.a2 * b.a22;
	return res;
}

inline mat operator * (const mat &a, const mat &b) {
	mat res;
	res.a00 = a.a00 * b.a00 + a.a01 * b.a10 + a.a02 * b.a20;
	res.a01 = a.a00 * b.a01 + a.a01 * b.a11 + a.a02 * b.a21;
	res.a02 = a.a00 * b.a02 + a.a01 * b.a12 + a.a02 * b.a22;
	res.a10 = a.a10 * b.a00 + a.a11 * b.a10 + a.a12 * b.a20;
	res.a11 = a.a10 * b.a01 + a.a11 * b.a11 + a.a12 * b.a21;
	res.a12 = a.a10 * b.a02 + a.a11 * b.a12 + a.a12 * b.a22;
	res.a20 = a.a20 * b.a00 + a.a21 * b.a10 + a.a22 * b.a20;
	res.a21 = a.a20 * b.a01 + a.a21 * b.a11 + a.a22 * b.a21;
	res.a22 = a.a20 * b.a02 + a.a21 * b.a12 + a.a22 * b.a22;
	return res;
}

inline void init() {
	for (int i = 0; i <= nt; ++i) {
		p[i] = ls[i] = rs[i] = sz[i] = 0;
		val[i] = vec();
		tag[i] = I;
		vis[i] = 0;
	}
	nt = 0;
}

inline int newnode(ll x, ll y) {
	int u = ++nt;
	p[u] = rnd();
	ls[u] = rs[u] = 0;
	sz[u] = 1;
	val[u] = vec(x, y, 1);
	tag[u] = I;
	vis[u] = 0;
	return u;
}

inline void pushup(int x) {
	sz[x] = sz[ls[x]] + sz[rs[x]] + 1;
}

inline void pushtag(int x, const mat &y) {
	if (!x) {
		return;
	}
	val[x] = val[x] * y;
	tag[x] = tag[x] * y;
	vis[x] = 1;
}

inline void pushdown(int x) {
	if (!vis[x]) {
		return;
	}
	pushtag(ls[x], tag[x]);
	pushtag(rs[x], tag[x]);
	vis[x] = 0;
	tag[x] = I;
}

void split(int u, int &x, int &y) {
	if (!u) {
		x = y = 0;
		return;
	}
	pushdown(u);
	if (val[u].a0 < 0) {
		x = u;
		split(rs[u], rs[u], y);
	} else {
		y = u;
		split(ls[u], x, ls[u]);
	}
	pushup(u);
}

int merge(int x, int y) {
	if (!x || !y) {
		return x | y;
	}
	pushdown(x);
	pushdown(y);
	if (p[x] < p[y]) {
		rs[x] = merge(rs[x], y);
		pushup(x);
		return x;
	} else {
		ls[y] = merge(x, ls[y]);
		pushup(y);
		return y;
	}
}

ll f[maxn], tot;

void dfs(int u) {
	if (!u) {
		return;
	}
	pushdown(u);
	dfs(ls[u]);
	f[++tot] = val[u].a0;
	dfs(rs[u]);
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		a[i] = -1;
	}
	for (int i = 1, x; i <= n; ++i) {
		cin >> x;
		if (x) {
			a[x] = (i & 1);
		}
	}
	init();
	int rt = 0;
	ll l = 0, r = 0, x = 0;
	if (a[1] == 1) {
		l = r = 1;
	} else if (a[1] == -1) {
		rt = newnode(0, 1);
		r = 1;
	}
	for (ll i = 1; i < n; ++i) {
		x += l * l * 2 + (-i - i - (n & 1)) * l + i * ((n + 1) / 2);
		pushtag(rt, mat(1, 0, 0, 4, 1, 0, -i - i - (n & 1) - 2, 0, 1));
		if (a[i + 1] == 1) {
			pushtag(rt, mat(1, 0, 0, 0, 1, 0, 0, 1, 1));
			++l;
			++r;
		} else if (a[i + 1] == -1) {
			int u, v;
			split(rt, u, v);
			pushtag(v, mat(1, 0, 0, 0, 1, 0, 0, 1, 1));
			rt = merge(merge(u, newnode(0, l + 1 + sz[u])), v);
			++r;
		}
	}
	tot = 0;
	dfs(rt);
	ll ans = -x;
	for (int i = 1; i <= (n + 1) / 2 - l; ++i) {
		ans -= f[i];
	}
	for (ll i = 1; i <= n; ++i) {
		ans += i * i;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	I.a00 = I.a11 = I.a22 = 1;
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

