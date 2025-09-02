# DCEPC14D - Finding GP

## 题目描述

There is an array A of n elements . You need to tell the number of subsets of size greater than 1 which can form geometric progressions having integral common ratios.

**Constraints:**

1<=N<=1\*10^4  
1<=A\[i\]<=1000000

## 样例 #1

### 输入

```
7\n2 4 4 2 8 16 8```

### 输出

```
\n\n41```

# 题解

## 作者：WorldMachine (赞：1)

题目大意：求长度大于 $1$ 的子序列个数，满足长度大于 $1$ 且能被重排成公比为整数的等比数列。

力大砖飞 $\mathcal O(n\sqrt V+n\sqrt[3]{V}\log V)$ 做法。存在更简单的做法。

先特判掉公比为 $1$ 的情况。

设定阈值 $\text{len}=\mathcal O(1)$。对于长度 $\leq\text{len}$ 的等比数列，对每个出现过的 $a$ 枚举其因数 $d$，则贡献为：
$$
\sum_{i=2}^\text{len}\prod_{j=-1}^{i-2}\text{cnt}_{ad^j}
$$
这部分复杂度是 $\mathcal O(n\sqrt V)$ 的。

对于长度 $>\text{len}$ 的等比数列，其公差 $q<V^{\frac{1}{\text{len}}}$，直接枚举公差暴力算贡献即可。这部分复杂度是 $\mathcal O(nV^{\frac{1}{\text{len}}}\log V)$。

取 $\text{len}=3$ 即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 10005, V = 1e6 + 5, p = 1e9 + 7;
int n, a[N], u, b[N], cnt[V], ans, arr[25];
int qpow(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) c = c * a % p;
		a = a * a % p, b >>= 1;
	}
	return c;
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i], cnt[a[i]]++;
	sort(b + 1, b + 1 + n), u = unique(b + 1, b + 1 + n) - b - 1;
	for (int i = 1; i <= u; i++) (ans += qpow(2, cnt[b[i]]) - 1) %= p;
//	cerr << ans << '\n';
	for (int i = 1, a; i <= u; i++) {
		a = b[i];
		for (int d = 1; d * d <= a; d++) {
			if (a % d) continue;
			if (d != 1) (ans += cnt[a / d] * cnt[a] * (1 + (a * d < V ? cnt[a * d] : 0))) % p;
			if (d != a && d * d != a) (ans += cnt[d] * cnt[a] * (1 + (a * a / d < V ? cnt[a * a / d] : 0))) %= p;
		}
		for (int q = 2, x, t; ; q++) {
			x = a, t = 0;
			while (x < V) arr[t++] = cnt[x], x *= q;
			if (t <= 3) break;
			for (int i = 1; i < t; i++) (arr[i] *= arr[i - 1]) %= p;
			for (int i = 3; i < t; i++) (ans += arr[i]) %= p;
		}
	}
	cout << (ans + p - n) % p;
}
/*
7
2 4 4 2 8 16 8
*/
```

---

