# Maximum Questions

## 题目描述

Vasya wrote down two strings $ s $ of length $ n $ and $ t $ of length $ m $ consisting of small English letters 'a' and 'b'. What is more, he knows that string $ t $ has a form "abab...", namely there are letters 'a' on odd positions and letters 'b' on even positions.

Suddenly in the morning, Vasya found that somebody spoiled his string. Some letters of the string $ s $ were replaced by character '?'.

Let's call a sequence of positions $ i,i+1,...,i+m-1 $ as occurrence of string $ t $ in $ s $ , if $ 1<=i<=n-m+1 $ and $ t_{1}=s_{i},t_{2}=s_{i+1},...,t_{m}=s_{i+m-1} $ .

The boy defines the beauty of the string $ s $ as maximum number of disjoint occurrences of string $ t $ in $ s $ . Vasya can replace some letters '?' with 'a' or 'b' (letters on different positions can be replaced with different letter). Vasya wants to make some replacements in such a way that beauty of string $ s $ is maximum possible. From all such options, he wants to choose one with the minimum number of replacements. Find the number of replacements he should make.

## 说明/提示

In the first sample string $ t $ has a form 'a'. The only optimal option is to replace all characters '?' by 'a'.

In the second sample using two replacements we can make string equal to "aba?aba??". It is impossible to get more than two occurrences.

## 样例 #1

### 输入

```
5
bb?a?
1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
9
ab??ab???
3
```

### 输出

```
2
```

# 题解

## 作者：emptysetvvvv (赞：7)

## 思路

### Part I

不考虑实现，胡乱想一个转移方程。

我们用 $f_i$ 表示考虑了前 $i$ 位，最多匹配了多少个串 $T$，$g_i$ 表示匹配数最大时，至少要使用多少个 `?`。


那么对于所有情况，首先有：

$$f_i=f_{i-1},g_i=g_{i-1}$$

边界条件：

$$f_0=0,g_0=0$$

将 `?` 出现次数的前缀和记为 $p_i$

若从 $i$ 往前长度 $m$ 一段可以匹配，则进行更新：

$$\begin{cases}f_i=f_{i-m}+1,g_i=g_{i-m}+(p_i-p_{i-m}), &f_{i}<f_{i-m}+1\\g_i=\min\left(g_{i-m}+(p_i-p_{i-m}),g_i\right),& f_i=f_{i-m}+1\\\mathrm{do\ nothing},& f_i>f_{i-m}+1\end{cases}$$

如果我们每次 $O(m)$ 暴力检查可否匹配，总复杂度就会变化为 $O(nm)$。

### PartII

快速检查能否匹配。

这正是此题的精髓所在，考虑这样一个问题，如果 $O(m)$ 匹配，题目完全没有必要保证 $T$ 仅由 `a` `b` 组成，完全可以直接给出，更没必要规定为 `a` `b` 交替出现。

敲黑板，我们用 $h_{1,i}$ 表示从 $i$ 向前最长有多长一段是 `a` `b` 交替出现，且以 `a` 结尾的串。对应的，用 $h_{0,i}$ 表示 `b` 结尾的。

则有：

$$h_{0,i}=h_{1,i-1}+1(s_i\not =\texttt{a})$$
$$h_{1,i}=h_{0,i-1}+1(s_i\not =\texttt{b})$$

那么判定能否匹配，就是说是否有 $h_{m\operatorname{and}2,i}\geqslant m$，复杂度 $O(1)$，总复杂度 $O(n)$。

## 代码

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 100005;
int n, m, p[maxn], g[maxn], f[maxn], h[2][maxn];
char s[maxn];
int main() {
	scanf("%d %s %d", &n, s+1, &m);
	for(int i = 1; i <= n; ++i) {
		p[i] = p[i-1] + (s[i] == '?');
		if(s[i] != 'a') h[0][i] = h[1][i-1] + 1;
		if(s[i] != 'b') h[1][i] = h[0][i-1] + 1;
		f[i] = f[i-1], g[i] = g[i-1];
		if(h[m&1][i] >= m) {
			if(f[i] < f[i-m]+1) f[i] = f[i-m]+1, g[i] = g[i-m]+p[i]-p[i-m];
			else if(f[i] == f[i-m]+1) g[i] = min(g[i], g[i-m]+p[i]-p[i-m]);
		}
	}
	printf("%d\n", g[n]);
}
```

---

## 作者：Erine (赞：0)

简单的 dp，考虑令 $f_i$ 表示前 $i$ 个字符最多匹配几个，$g_i$ 表示前 $i$ 个字符匹配最多的情况下最少用几个问号。

则有：

- 如果当前 $[i-m+1,i]$ 不能匹配成功：

  $f_i=f_{i-1}$，$g_i=g_{i-1}$。

- 如果能匹配，但是 $f_{i-1}>f_{i-m}+1$：

  这时匹配是不优的。仍继承上一个状态，$f_i=f_{i-1}$，$g_i=g_{i-1}$。
  
- 如果能匹配，$f_{i-1}<f_{i-m}+1$：

  匹配是较优者，于是 $f_i=f_{i-m}+1,g_{i}=g_{i-m}+q_i-q_{i-m}$，其中 $q_i$ 表示 $[1,i]$ 内的问号个数。
  
- 如果能匹配，并且有 $f_{i-1}=f_{i-m}+1$：

  $g_i$ 则从两者中择优。
  
然后瓶颈在于判断以 $i$ 结尾能不能匹配。令 $p_{i,0/1}$ 表示 $i$ 处以 $\texttt{b/a}$ 结尾最长能匹配的长度。这个是很好递推的。

线性。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 1e5 + 10;

int n, m;
char s[maxn];
int f[maxn], g[maxn];
int q[maxn];
int p[maxn][2];

signed main() {
	cin >> n >> (s + 1) >> m;
	for (int i = 1; i <= n; i++) q[i] = q[i - 1] + (s[i] == '?');
	for (int i = 1; i <= n; i++) {
		if (s[i] != 'b') p[i][1] = p[i - 1][0] + 1;
		if (s[i] != 'a') p[i][0] = p[i - 1][1] + 1;
	}
	for (int i = m; i <= n; i++) {
		if (p[i][m & 1] < m) {
			f[i] = f[i - 1], g[i] = g[i - 1];
		} else if (f[i - 1] > f[i - m] + 1) {
			f[i] = f[i - 1];
			g[i] = g[i - 1];
		} else if (f[i - 1] < f[i - m] + 1) {
			f[i] = f[i - m] + 1;
			g[i] = g[i - m] + q[i] - q[i - m];
		} else {
			f[i] = f[i - 1];
			g[i] = min(g[i - 1], g[i - m] + q[i] - q[i - m]);
		}
	}
	cout << g[n] << endl;
	return 0;
}
```

---

