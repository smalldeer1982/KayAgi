# Skyscape

## 题目描述

给定一个长度为 $n$ 的排列 $a$ $^{\text{∗}}$。

我们称一个长度为 $n$ 的排列 $b$ 是好的，如果在最多进行 $n$ 次（可以是零次）以下操作后，排列 $a$ 和 $b$ 可以变得相同：

- 选择两个整数 $l, r$，满足 $1 \le l < r \le n$ 且 $a_r = \min(a_l, a_{l + 1}, \ldots, a_r)$。
- 将子段 $[a_l, a_{l + 1}, \ldots, a_r]$ 循环右移一位。换句话说，将 $a$ 替换为：
  $$
  [a_1, \ldots, a_{l - 1}, \; a_r, a_l, a_{l + 1}, \ldots, a_{r - 1}, \; a_{r + 1}, \ldots, a_n]
  $$

同时给定一个长度为 $n$ 的排列 $c$，其中部分元素缺失（用 $0$ 表示）。

你需要找到一个好的排列 $b_1, b_2, \ldots, b_n$，使得 $b$ 可以通过填充 $c$ 中缺失的元素得到（即对于所有 $1 \le i \le n$，如果 $c_i \ne 0$，则 $b_i = c_i$）。如果不存在这样的排列，输出 $-1$。

$^{\text{∗}}$ 长度为 $n$ 的排列是指由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[1,3,4]$ 也不是排列（因为 $n=3$ 但数组中包含 $4$）。

## 说明/提示

- 在第一个测试用例中，$b = [1, 2]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 2$ 并循环右移子段 $[a_1, a_2]$。此时 $a$ 变为 $[1, 2]$。

- 在第二个测试用例中，$b = [2, 3, 4, 1]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 2$ 并循环右移子段 $[a_1, a_2]$。此时 $a$ 变为 $[2, 3, 4, 1]$。

- 在第三个测试用例中，$b = [1, 3, 2, 4, 5]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 1, r = 3$ 并循环右移子段 $[a_1, a_2, a_3]$。此时 $a$ 变为 $[1, 3, 2, 5, 4]$。
  - 选择 $l = 4, r = 5$ 并循环右移子段 $[a_4, a_5]$。此时 $a$ 变为 $[1, 3, 2, 4, 5]$。

- 在第四个测试用例中，$b = [3, 2, 1, 5, 4]$ 是一个有效解，因为 $a$ 和 $b$ 已经相同。

- 在第五个测试用例中，不存在满足条件的好排列 $b$，因此输出 $-1$。

- 在第六个测试用例中，$b = [3, 2, 1, 5, 4, 6]$ 是一个有效解，因为进行以下操作后 $a$ 和 $b$ 会变得相同：
  - 选择 $l = 2, r = 4$ 并循环右移子段 $[a_2, a_3, a_4]$。此时 $a$ 变为 $[3, 2, 5, 6, 1, 4]$。
  - 选择 $l = 3, r = 5$ 并循环右移子段 $[a_3, a_4, a_5]$。此时 $a$ 变为 $[3, 2, 1, 5, 6, 4]$。
  - 选择 $l = 5, r = 6$ 并循环右移子段 $[a_5, a_6]$。此时 $a$ 变为 $[3, 2, 1, 5, 4, 6]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
9
2
2 1
1 2
4
3 2 4 1
2 0 0 1
5
3 2 1 5 4
1 3 0 0 0
5
3 2 1 5 4
3 2 1 5 4
5
3 2 1 5 4
3 2 5 1 4
6
3 5 6 2 1 4
0 2 0 5 0 0
6
3 5 6 2 1 4
0 2 0 6 4 0
9
6 9 2 4 1 7 8 3 5
0 2 5 9 0 0 0 8 0
9
8 5 3 9 1 7 4 6 2
0 0 8 0 7 0 4 0 2```

### 输出

```
1 2
2 3 4 1
1 3 2 4 5
3 2 1 5 4
-1
3 2 1 5 4 6
-1
-1
1 3 8 5 7 9 4 6 2```

# 题解

## 作者：EuphoricStar (赞：1)

一个排列 $b$ 是好的，当且仅当 $a$ 中的顺序对在 $b$ 中也是顺序对。换句话说，对于任意一对 $i < j$，若 $i$ 在 $a$ 中的出现位置比 $j$ 的小，那么 $i$ 在 $b$ 中的出现位置也比 $j$ 的小。

- 证明其必要性：操作后不会让原来在 $a$ 中的顺序对变成逆序对；
- 证明其充分性：对于满足上述条件的 $a, b$，一定能通过以下操作使得 $a$ 与 $b$ 相同：
  - 依次枚举 $i = 1, 2, \ldots, n$。若 $a_i = b_i$ 则跳过；否则设 $j$ 为此时 $b_i$ 在 $a$ 中的位置，进行一次 $l = i, r = j$ 的操作。

对于 $c$ 中非 $0$ 的数，若它们违反了上述条件，那么显然无解。否则，对于一个未在 $c$ 中出现的数 $x$，如果只考虑 $c$ 中出现的数对它的限制，那么它在 $c$ 中位置的合法范围是一段区间 $[l_x, r_x]$。$l_x, r_x$ 可以用树状数组或线段树求得。

这看起来是一个经典的“把一些数填入一些位置，第 $i$ 个数的位置必须在 $[l_i, r_i]$ 内”的贪心问题。这个问题的做法是，从左往右依次确定每个位置的数，第 $i$ 个位置填 $l_j \le i$、$r_j$ 最小且未被填过的数。可以用一个堆实现。

但是我们还要考虑，要被填入 $c$ 中的数互相的限制。

但是实际上我们可以发现，对于任意 $x < y$，若 $x$ 在 $a$ 中出现位置比 $y$ 的小，那么 $l_x \le l_y$ 且 $r_x \le r_y$。所以如果直接使用上述的贪心做法（当有多个 $r_j$ 最小时填 $j$ 最小的数），合法条件会自然被满足。

时间复杂度：每组测试用例 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn = 500100;

int n, a[maxn], b[maxn], c[maxn], p[maxn], q[maxn];

struct node {
	int r, x;
	node(int a = 0, int b = 0) : r(a), x(b) {}
};

inline bool operator < (const node &a, const node &b) {
	return a.r > b.r || (a.r == b.r && a.x > b.x);
}

vector<node> vc[maxn];

struct DS1 {
	int c[maxn];
	
	inline void init() {
		for (int i = 0; i <= n; ++i) {
			c[i] = 0;
		}
	}
	
	inline void update(int x, int d) {
		for (int i = x; i <= n; i += (i & (-i))) {
			c[i] = max(c[i], d);
		}
	}
	
	inline int query(int x) {
		int res = 0;
		for (int i = x; i; i -= (i & (-i))) {
			res = max(res, c[i]);
		}
		return res;
	}
} T1;

struct DS2 {
	int c[maxn];
	
	inline void init() {
		for (int i = 0; i <= n; ++i) {
			c[i] = n + 1;
		}
	}
	
	inline void update(int x, int d) {
		for (int i = x; i; i -= (i & (-i))) {
			c[i] = min(c[i], d);
		}
	}
	
	inline int query(int x) {
		int res = n + 1;
		for (int i = x; i <= n; i += (i & (-i))) {
			res = min(res, c[i]);
		}
		return res;
	}
} T2;

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		p[a[i]] = i;
		q[i] = 0;
		vector<node>().swap(vc[i]);
	}
	for (int i = 1; i <= n; ++i) {
		cin >> b[i];
		if (b[i]) {
			q[b[i]] = i;
		}
	}
	T1.init();
	for (int i = 1; i <= n; ++i) {
		if (q[i]) {
			if (T1.query(p[i]) > q[i]) {
				cout << "-1\n";
				return;
			}
			T1.update(p[i], q[i]);
		}
	}
	T1.init();
	T2.init();
	for (int i = 1; i <= n; ++i) {
		if (q[a[i]]) {
			T1.update(a[i], q[a[i]]);
		} else {
			c[i] = T1.query(a[i]) + 1;
		}
	}
	for (int i = n; i; --i) {
		if (q[a[i]]) {
			T2.update(a[i], q[a[i]]);
		} else {
			int r = T2.query(a[i]) - 1;
			if (c[i] > r) {
				cout << "-1\n";
				return;
			}
			vc[c[i]].emplace_back(r, a[i]);
		}
	}
	priority_queue<node> pq;
	for (int i = 1; i <= n; ++i) {
		for (node u : vc[i]) {
			pq.push(u);
		}
		if (!b[i]) {
			if (pq.empty() || pq.top().r < i) {
				cout << "-1\n";
				return;
			}
			b[i] = pq.top().x;
			pq.pop();
		}
	}
	for (int i = 1; i <= n; ++i) {
		cout << b[i] << " \n"[i == n];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

