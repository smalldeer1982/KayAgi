# 「SWTR-5」Sequence

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。他可以选择一个区间 $[l,r]$ 满足其最大值与最小值的差不超过 $k$。

他还需找出 $m$ 个**互不相同的整数** $p_1,p_2,\cdots,p_m$，满足：

- $m$ 为正整数。
- $\prod\limits_{i=l}^ra_i=\prod\limits_{i=1}^mp_i$。即选择区间的乘积等于这 $m$ 个数的乘积。
- $p_i$ 为一个质数的正整数次幂。

这 $m$ 个数的约数个数之和就是小 A 的得分。帮他求出得分的最大值。

## 说明/提示

「样例说明」

样例 $1$：选择区间 $[1,2]$，再选择 $p_1=2$，$p_2=3$，$p_3=4$，可以达到最大值 $7$，方案不唯一。

样例 $2$：选择区间 $[1,4]$，再选择 $p_1=4$，$p_2=8$，$p_3=3$，$p_4=27$，可以达到最大值 $13$。

「数据范围与约定」

**本题采用捆绑测试**。

- Subtask 1（1 points）：$n=1$ 且 $a_1$ 为质数。
- Subtask 2（9 points）：$n=1$。
- Subtask 3（20 points）：$n\leq 10$，$a_i \leq 20$。
- Subtask 4（13 points）：$n\leq 200$，$a_i \leq 200$。
- Subtask 5（17 points）：$n\leq 2\times 10^3$。
- Subtask 6（15 points）：$a_i$ 为质数。
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据：$1 \leq n \leq 10^5$，$2 \leq a_i \leq 10^5$，$0 \leq k \leq 10^5$。

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) B。    
idea & solution：[ET2006](https://www.luogu.com.cn/user/115194)。

## 样例 #1

### 输入

```
4 2
6 4 2 3```

### 输出

```
7```

## 样例 #2

### 输入

```
5 3
8 6 9 6 4```

### 输出

```
13```

## 样例 #3

### 输入

```
17 17
29 38 9 10 16 5 1 10 27 20 11 9 15 11 2 3 10 
```

### 输出

```
17```

# 题解

## 作者：ycx303 (赞：0)

# P6650 「SWTR-5」Sequence题解

# 思路：
思路非常的简短，对于 $k$ 的限制，双指针即可。

然后对于当前区间的答案，显然我们维护每个质因子的个数即可。

假设质因子为 $n$ 个，显然我们 $1, 2, 3, 4\dots$ 这样分配是最优的。

## 代码如下：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6 + 10;
int n, a[N], k, res, ans, cnt[N], mx, vis[N], pos = 1, val[N];
vector<int> v[N];
multiset<int> s;
inline int calc(int x) {
	int l = 1, r = 1e4;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (mid * (mid + 1) <= x * 2) l = mid;
		else r = mid - 1;
	}
	return x + l;
}
inline void add(int x) {
	s.insert(x);
	int y = x;
	for (int i : v[x]) {
		int tmp = 0;
		while (y % i == 0)	y /= i, tmp++;
		res += val[cnt[i] + tmp] - val[cnt[i]];
		cnt[i] += tmp;
	}
}
inline void del(int x) {
	s.erase(s.lower_bound(x));
	int y = x;
	for (int i : v[x]) {
		int tmp = 0;
		while (y % i == 0)	y /= i, tmp++;
		res += val[cnt[i] - tmp] - val[cnt[i]];
		cnt[i] -= tmp;
	}
}
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i], mx = max(mx, a[i]);
	for (int i = 2; i <= mx; i++) if (!vis[i]) {
			for (int j = i; j <= mx; j += i) v[j].push_back(i), vis[j] = 1;
		}
	for (int i = 1; i <= 2e6; i++) val[i] = calc(i);
	for (int i = 1; i <= n; i++) {
		add(a[i]);
		while ((*--s.end()) - *s.begin() > k) del(a[pos++]);
		ans = max(ans, res);
	}
	cout << ans;
	return 0;
}
``````

---

