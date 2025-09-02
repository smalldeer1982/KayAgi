# [ARC042D] あまり

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc042/tasks/arc042_d

$ 4 $ つの整数 $ X,\ P,\ A,\ B\ (1\ ≦\ X\ が与えられます。ただし、P $ は素数です。 $ X^i\ (A\ ≦\ i\ ≦\ B) $ を $ P $ で割った余りの最小値を求めてください。

この問題の入力は得点に影響しない入力例 $ 1 $ を除いて、[このC++プログラム](/img/arc/042/adafrrg/generator.cpp)を用いて生成しました。擬似乱数生成器の初期化に用いられるプログラムの第 $ 1 $ 引数は $ 1 $ 以上 $ 10,000 $ 以下の整数を用いました。[このファイル](/img/arc/042/adafrrg/input.txt)の $ i $ 行目 $ (1\ ≦\ i\ ≦\ 10,000) $ は、入力生成プログラムの第 $ 1 $ 引数が $ i $ であるときの出力と一致します。すなわち、与えられるテストケースは入力例 $ 1 $ を除いて、このファイルのいずれかの行と一致します。

## 说明/提示

### Sample Explanation 1

$ X^i\ (A\ ≦\ i\ ≦\ B) $ を $ P $ で割った余りは $ 8,\ 5,\ 10,\ 9,\ 7,\ 3,\ 6 $ であるので、最小値は $ 3 $ である。 この入力は入力生成プログラムを用いて作られたものではないので、得られる得点に影響しない。

### Sample Explanation 2

この入力は入力生成プログラムの第 $ 1 $ 引数に $ 1 $ を与えて生成した。

### Sample Explanation 3

この入力は入力生成プログラムの第 $ 1 $ 引数に $ 3 $ を与えて生成した。

### Sample Explanation 4

この入力は入力生成プログラムの第 $ 1 $ 引数に $ 25 $ を与えて生成した。

## 样例 #1

### 输入

```
2 11 3 9```

### 输出

```
3```

## 样例 #2

### 输入

```
15 7159 12 12818```

### 输出

```
1```

## 样例 #3

### 输入

```
1400884 50141599 4 458568```

### 输出

```
114```

## 样例 #4

### 输入

```
1591755 291456379 215 1223```

### 输出

```
96324```

# 题解

## 作者：WorldMachine (赞：1)

太神秘。

如果 $\left\lfloor\dfrac{r}{p-1}\right\rfloor\not=\left\lfloor\dfrac{l}{p-1}\right\rfloor$ 说明一定包含了一个 $1$，直接特判掉。

这样 $[l,r]$ 在同一段。如果 $[l,r]$ 不是很长可以直接暴力，这部分是 $\mathcal O(\text{len})$ 的。

区间比较长的情况这个做法就死了，但由于 $X^i$ 可以看作是随机分布的，答案不会很大，在 $\mathcal O\left(\dfrac{p}{\text{len}}\right)$ 级别，直接枚举答案用 BSGS 算即可。

时间复杂度为 $\mathcal O\left(\text{len}+\dfrac{p\sqrt p}{\text{len}}\right)$，取 $\text{len}=\mathcal O(p^{0.75})$ 有最优复杂度 $\mathcal O(p^{0.75})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int x, p, l, r;
int qpow(int a, int b) {
	int c = 1;
	while (b) { if (b & 1) c = c * a % p; a = a * a % p, b >>= 1; }
	return c;
}
int BSGS(int a, int b) {
	unordered_map<int, int> mp;
	b %= p; int t = ceil(sqrt(p));
	for (int i = 1; i <= t; i++) b = b * a % p, mp[b] = i;
	b = qpow(a, t);
	int c = 1;
	for (int i = 1; i <= t; i++) {
		c = c * b % p;
		if (mp[c]) return ((i * t - mp[c]) % p + p) % p;
	}
	return -1;
}
signed main() {
	cin >> x >> p >> l >> r;
	if (r / (p - 1) - l / (p - 1) >= 1) return cout << 1 << '\n', 0;
	l %= p - 1, r %= p - 1;
	if (r - l + 1 <= 1e8) {
		int now = qpow(x, l), ans = now;
		for (int i = l + 1; i <= r; i++) now = now * x % p, ans = min(ans, now);
		cout << ans << '\n';
		return 0;
	}
	for (int i = 1, j; ; i++) {
		j = BSGS(x, i);
		if (l <= j && j <= r) return cout << i << '\n', 0;
	}
}
```

---

