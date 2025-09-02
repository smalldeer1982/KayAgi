# Turtle and Nediam 2

## 题目描述

[LGR-205-Div.1 C Turtle and Nediam](https://www.luogu.com.cn/problem/P11283)

给定一个长度为 $n$ 的二进制序列 $s$，仅由 $0$ 和 $1$ 组成。

你可以进行最多 $n - 2$ 次（可以是零次）以下操作：

- 设当前序列 $s$ 的长度为 $m$。选择一个整数 $i$ 满足 $1 \le i \le m - 2$。
- 设子数组 $[s_i, s_{i + 1}, s_{i + 2}]$ 的中位数 $^{\text{∗}}$ 为 $x$，并令 $j$ 为满足 $j \ge i$ 且 $s_j = x$ 的最小整数。
- 从序列中移除 $s_j$ 并将剩余部分拼接。换句话说，将 $s$ 替换为 $[s_1, s_2, \ldots, s_{j - 1}, s_{j + 1}, s_{j + 2}, \ldots, s_m]$。

注意每次操作后，序列 $s$ 的长度会减少 $1$。

求经过若干次操作后，可以得到的不同二进制序列的数量，结果对 $10^9 + 7$ 取模。

$^{\text{∗}}$ 长度为奇数 $k$ 的数组的中位数是指排序后的第 $\frac{k + 1}{2}$ 个元素。

## 说明/提示

- 在第一个测试用例中，可以得到以下二进制序列：$[1, 1]$、$[1, 1, 1]$、$[1, 1, 1, 1]$、$[1, 1, 1, 1, 1]$。

- 在第二个测试用例中，可以得到以下二进制序列：$[0, 1]$、$[0, 1, 1]$、$[1, 0, 1]$、$[1, 0, 0, 1]$、$[1, 0, 1, 1]$、$[1, 0, 0, 0, 1]$、$[1, 0, 0, 1, 1]$、$[1, 0, 0, 0, 1, 1]$。例如，要得到 $[0, 1, 1]$，可以：
  - 选择 $i = 2$。子数组 $[0, 0, 0]$ 的中位数为 $0$。移除 $s_2$，序列变为 $[1, 0, 0, 1, 1]$。
  - 选择 $i = 1$。子数组 $[1, 0, 0]$ 的中位数为 $0$。移除 $s_2$，序列变为 $[1, 0, 1, 1]$。
  - 选择 $i = 1$。子数组 $[1, 0, 1]$ 的中位数为 $1$。移除 $s_1$，序列变为 $[0, 1, 1]$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
5
11111
6
100011
9
000111000
14
11001111111000
16
0010000110100011```

### 输出

```
4
8
30
114
514```

# 题解

## 作者：EuphoricStar (赞：1)

首先提取出 $s$ 中的极长的值相同的连续段。设一共有 $m$ 个连续段，长度为 $a_1, a_2, \ldots, a_m$。那么操作可以被表述成：

- 选择一个 $1 \le i \le |a|$ 使得 $a_i \ge 2$，并将 $a_i$ 减去 $1$；
- 选择一个 $2 \le i < |a|$ 使得 $a_{i - 1} = a_i = 1$，删除 $a_{i - 1}$，若 $i \ge 3$ 则将 $a_{i - 2}$ 加上 $a_i$ 并删除 $a_i$。

特判 $m \le 2$。发现最后一个连续段长度不会变大，且它和前面部分独立，所以只用考虑 $a_1, a_2, \ldots, a_{m - 1}$ 能生成的串，最后答案乘上 $a_m$。

先考虑计数开头字符和 $s_1$ 相同的串。考虑对一个可以生成的连续段序列 $b_1, b_2, \ldots, b_k$，贪心地在 $a$ 中匹配一个最短的前缀，使得这个前缀可以生成 $b_1, b_2, \ldots, b_k$。

设 $f_i$ 为有多少个串可以匹配到 $a_i$。

转移考虑新加入一个连续段 $b_{k + 1}$，那么枚举 $j > i \land j \bmod 2 \ne i \bmod 2$，设上一个 $j$ 能生成的 $b_{k + 1}$ 最大值为 $x$，那么 $j$ 能生成的 $b_{k + 1}$ 最大值为 $\max(x + 1, a_j)$。所以若 $b_{k + 1}$ 匹配到位置 $j$，则 $x < b_{k + 1} \le \max(x + 1, a_j)$，$b_{k + 1}$ 有 $\max(x + 1, a_j) - x$ 种取值。

所以我们的转移形如这样：

```
for i := 1 to m - 1:
    x := 0
    for j := i + 1 to m - 1:
        if j mod 2 != i mod 2:
            f[j] := f[j] + f[i] * (max(x + 1, a[j]) - x)
            x := max(x + 1, a[j])
```

初值为 $f_1 = a_1$，$\forall i \ge 3 \land i \bmod 2 = 1, f_i = 1$。答案为 $a_m \cdot \sum\limits_{i = 1}^{m - 1} [(m - i) \bmod 2 = 1] f_i$。

再考虑计数开头字符和 $s_1$ 不同的串。发现若得到的串开头字符和 $s_1$ 不同，那么为了把第一个连续段删除所以第二个连续段长度最长只能是 $1$。所以我们删除 $a_1$ 并将 $a_2$ 变为 $1$ 后，再做一遍上述过程即可。

接下来我们考虑优化上述的 $O(m^2)$ DP。

考虑求出 $\text{nxt}_i$ 表示最小的 $j$ 使得 $j \bmod 2 = i \bmod 2$ 且 $a_j - \frac{j}{2} > a_i - \frac{i}{2}$。

对于一个 $i$，它的转移形如：

- 维护一个变量 $j$，初始 $j = i + 1$；
- 对 $j$ 特殊转移；
- 将 $j + 2 \le k < \text{nxt}_j$ 且 $k \bmod 2 = j \bmod 2$ 的 $f_k$ 加上 $f_i$（可以用差分数组实现）；
- 令 $j = \text{nxt}_j$ 然后重复这个过程。

直接模拟上述转移过程，可以证明复杂度为 $O(\sum a_i) = O(n)$，因为每个 $a_i$ 只会被它之前的至多 $a_i$ 个位置跳到。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2000100;
const ll mod = 1000000007;

int n, a[maxn], m, nxt[maxn], stk[maxn], top;
ll f[maxn], d[maxn];
char s[maxn];

inline ll calc() {
	top = 0;
	for (int i = m; i >= 1; i -= 2) {
		while (top && a[stk[top]] - stk[top] / 2 < a[i] - i / 2) {
			--top;
		}
		nxt[i] = stk[top];
		stk[++top] = i;
	}
	top = 0;
	for (int i = m - 1; i >= 1; i -= 2) {
		while (top && a[stk[top]] - stk[top] / 2 < a[i] - i / 2) {
			--top;
		}
		nxt[i] = stk[top];
		stk[++top] = i;
	}
	for (int i = 1; i < m; ++i) {
		f[i] = d[i] = 0;
	}
	f[1] = a[1];
	for (int i = 3; i < m; i += 2) {
		f[i] = 1;
	}
	ll ans = 0;
	for (int i = 1; i < m; ++i) {
		if (i >= 3) {
			d[i] = (d[i] + d[i - 2]) % mod;
		}
		f[i] = (f[i] + d[i]) % mod;
		int j = i + 1, x = 0;
		while (j < m) {
			int k = (nxt[j] ? nxt[j] : m);
			f[j] = (f[j] + f[i] * (a[j] - x)) % mod;
			x = a[j] + (k - j) / 2 - 1;
			d[j + 2] = (d[j + 2] + f[i]) % mod;
			d[k] = (d[k] - f[i] + mod) % mod;
			j = k;
		}
		if ((m - i) & 1) {
			ans = (ans + f[i]) % mod;
		}
	}
	return ans * a[m] % mod;
}

void solve() {
	cin >> n >> s;
	m = 0;
	for (int i = 0, j = 0; i < n; i = (++j)) {
		while (j + 1 < n && s[j + 1] == s[i]) {
			++j;
		}
		a[++m] = j - i + 1;
	}
	if (m == 1) {
		cout << n - 1 << '\n';
		return;
	}
	if (m == 2) {
		cout << 1LL * a[1] * a[2] % mod << '\n';
		return;
	}
	ll ans = calc();
	--m;
	for (int i = 1; i <= m; ++i) {
		a[i] = a[i + 1];
	}
	a[1] = 1;
	ans = (ans + calc()) % mod;
	cout << ans << '\n';
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

当然我们还可以进一步地把 DP 过程优化到 $O(m)$。设 $g_i$ 为所有能跳到 $i$ 的位置的 $f$ 值之和。那么转移形如 $g_{\text{nxt}_i} \gets g_{\text{nxt}_i} + g_i$，然后将 $i + 2 \le k < \text{nxt}_i$ 且 $k \bmod 2 = i \bmod 2$ 的 $f_k$ 加上 $g_i$，再对 $f_{\text{nxt}_i}$ 特殊转移。

时间复杂度：每组测试用例 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2000100;
const ll mod = 1000000007;

int n, a[maxn], m, nxt[maxn], stk[maxn], top;
ll f[maxn], g[maxn], d[maxn];
char s[maxn];

inline ll calc() {
	top = 0;
	for (int i = m; i >= 1; i -= 2) {
		while (top && a[stk[top]] - stk[top] / 2 < a[i] - i / 2) {
			--top;
		}
		nxt[i] = stk[top];
		stk[++top] = i;
	}
	top = 0;
	for (int i = m - 1; i >= 1; i -= 2) {
		while (top && a[stk[top]] - stk[top] / 2 < a[i] - i / 2) {
			--top;
		}
		nxt[i] = stk[top];
		stk[++top] = i;
	}
	for (int i = 1; i < m; ++i) {
		f[i] = g[i] = d[i] = 0;
	}
	f[1] = a[1];
	for (int i = 3; i < m; i += 2) {
		f[i] = 1;
	}
	ll ans = 0;
	for (int i = 1; i < m; ++i) {
		if (i >= 3) {
			d[i] = (d[i] + d[i - 2]) % mod;
		}
		f[i] = (f[i] + d[i]) % mod;
		g[i + 1] = (g[i + 1] + f[i]) % mod;
		f[i + 1] = (f[i + 1] + f[i] * a[i + 1]) % mod;
		d[i + 2] = (d[i + 2] + g[i]) % mod;
		if (nxt[i]) {
			g[nxt[i]] = (g[nxt[i]] + g[i]) % mod;
			f[nxt[i]] = (f[nxt[i]] + g[i] * (a[nxt[i]] - a[i] - (nxt[i] - i) / 2 + 1)) % mod;
			d[nxt[i]] = (d[nxt[i]] - g[i] + mod) % mod;
		}
		if ((m - i) & 1) {
			ans = (ans + f[i]) % mod;
		}
	}
	return ans * a[m] % mod;
}

void solve() {
	cin >> n >> s;
	m = 0;
	for (int i = 0, j = 0; i < n; i = (++j)) {
		while (j + 1 < n && s[j + 1] == s[i]) {
			++j;
		}
		a[++m] = j - i + 1;
	}
	if (m == 1) {
		cout << n - 1 << '\n';
		return;
	}
	if (m == 2) {
		cout << 1LL * a[1] * a[2] % mod << '\n';
		return;
	}
	ll ans = calc();
	--m;
	for (int i = 1; i <= m; ++i) {
		a[i] = a[i + 1];
	}
	a[1] = 1;
	ans = (ans + calc()) % mod;
	cout << ans << '\n';
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

