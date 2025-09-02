# Marunomi for All Prefixes

## 题目描述

Shobon 想到了一个有趣的问题。

> #### 史莱姆吞噬
>
> 现有一个正整数序列 $ W = (w_1, w_2, \dots, w_N) $。
>
> 有 $ N $ 只史莱姆，编号分别是 $ 1, 2, \dots, N $。最初，每只史莱姆 $ i $（$ 1 \leq i \leq N $）的重量是 $ w_i $，胜利次数是 $ 0 $。
> 
> 你可以对这些史莱姆执行以下操作任意次：
>
> - 选择任意两个编号不同且活着的史莱姆，分别是史莱姆 $ i $ 和史莱姆 $ j\ (i \neq j)$。
>   - 设史莱姆 $ i $ 的重量为 $ W_i $，史莱姆 $ j $ 的重量为 $ W_j $。
>   - 如果 $ W_i > W_j $，则史莱姆 $ i $ 的胜利次数加 $ 1 $，其重量变为 $ W_i + W_j $，同时史莱姆 $ j $ 消亡。
>   - 否则，就什么也不做。
>
> ![](https://img.atcoder.jp/ttpc2024_2/a91ebda9babf3e276c4e56e302e4fb46.svg)
>
> 对于每个 $ i = 1, 2, \dots, N $，假设我们尽可能增加史莱姆 $ i $ 的胜利次数，将其最大化，记为 $ S_i $。  
> 求 $ S_1 + S_2 + \dots + S_N $ 的总和。

由于该问题与 [ARC189 D - Takahashi is Slime](https://atcoder.jp/contests/arc189/tasks/arc189_d) 类似，noya2 将其变为：

> #### 前缀史莱姆吞噬
>
> 给定一个正整数序列 $ A = (a_1, a_2, \dots, a_M) $。
>
> 对每个 $ i = 1, 2, \dots, M $，计算当输入序列 $ W = (a_1, a_2, \dots, a_i) $ 时，上述问题的结果。

请解决这个问题。

## 说明/提示

- 输入的所有值均为整数。
- $ 1 \leq M \leq 2 \times 10^5 $。
- $ 1 \leq a_i \leq 10^9 \ (1 \leq i \leq M) $。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
1 2 3 5 20```

### 输出

```
0 1 3 7 11```

## 样例 #2

### 输入

```
3
1 1 1```

### 输出

```
0 0 0```

## 样例 #3

### 输入

```
10
17 3467 115 716 9070 32 12251 237 549 17```

### 输出

```
0 1 3 6 10 15 22 29 38 46```

# 题解

## 作者：Register_int (赞：0)

观察可得：对 $a$ 排序后，一个史莱姆的最终大小一定是 $a_i$ 的一个前缀之和。那么你有个结论：每个史莱姆最终的大小只有 $O(\log)$ 种。证明是简单的：将 $a$ 从小到大排序，若 $i$ 与 $i+1$ 的最终大小不同，设最终大小对应的前缀分别为 $t_i,t_{i+1}$ 则说明 $\sum_{1\le j\le t_i} a_j\le a_{t_{i+1}}$，也就是 $i$ 的最终大小最多是 $i+1$ 的一半，结论得证。

于是我们可以先对 $a$ 离散化，维护若干个段 $(l,r,h)$，表示离散化后在 $[l,r]$ 间的 $a_i$ 的最终大小为 $h$ 位置的前缀和。每次新插入一个数，将数所在的段裂开，再暴力计算每个段的 $h$ 的变化，最后将能合并的段合并即可。维护段需要 set，单点插入可以树状数组，时间复杂度 $O(n\log n(\log n+\log V))$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

struct node {
	int l, r; mutable int h;
	node(int l = 0, int r = 0, int h = 0) : l(l), r(r), h(h) {}
	bool operator < (const node &rhs) const { return l < rhs.l; }
}; set<node> s; deque<node> tmp;

int n, m, a[MAXN], b[MAXN], p[MAXN]; ll c[MAXN];

inline void addp(int k) { for (int i = k; i <= m; i += i & -i) p[i]++; }
inline int askp(int k) { int res = 0; for (int i = k; i; i &= i - 1) res += p[i]; return res; }
inline void add(int k, int x) { for (int i = k; i <= m; i += i & -i) c[i] += x; }
inline ll ask(int k) { ll res = 0; for (int i = k; i; i &= i - 1) res += c[i]; return res; }

inline 
int find(int k) {
	int res = 0, cnt = 0, x = askp(k);
	if (!x) return 0;
	for (int i = __lg(m); ~i; i--) {
		if ((res | 1 << i) <= k && cnt + p[res | 1 << i] < x) cnt += p[res |= 1 << i];
	}
	return res + 1;
}

inline 
ll calc(int k, int x) {
	for (; k < m; ) {
		ll sum = ask(k); if (k < x) sum += b[x];
		int y = lower_bound(b + 1, b + m + 1, sum) - b - 1;
		if (k == y) break; k = y;
	}
	return k;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1), m = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b;
	s.emplace(1, m, 0);
	for (int i = 1; i <= n; i++) {
		addp(a[i]), add(a[i], b[a[i]]);
		node x = *--s.upper_bound(node(a[i])); s.erase(x);
		if (x.l < a[i]) s.emplace(x.l, a[i] - 1, x.h);
		if (x.r > a[i]) s.emplace(a[i] + 1, x.r, x.h);
		s.emplace(a[i], a[i], calc(a[i] - 1, a[i]));
		for (auto it = s.begin(); it != s.end(); ++it) {
			int k = find(it->r); if (k < it->l) continue;
			it->h = calc(it->h, k);
		}
		tmp.clear();
		for (node x : s) {
			if (tmp.empty() || tmp.back().h < x.h) tmp.emplace_back(x);
			else tmp.back().r = x.r;
		}
		ll ans = 0; s.clear();
		for (node x : tmp) s.emplace(x);
		for (node x : tmp) ans += (ll)(askp(x.r) - askp(x.l - 1)) * max(0, askp(x.h) - 1);
		printf("%lld ", ans);
	}
}
```

---

