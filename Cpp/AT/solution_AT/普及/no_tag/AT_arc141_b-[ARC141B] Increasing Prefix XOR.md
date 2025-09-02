# [ARC141B] Increasing Prefix XOR

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc141/tasks/arc141_b

正整数 $ N,\ M $ が与えられます。

長さ $ N $ の正整数列 $ A=(A_1,\ A_2,\ \dots,\ A_N) $ であって、以下の条件を満たすものの個数を $ 998244353 $ で割った余りを求めてください。

- $ 1\ \leq\ A_1\ <\ A_2\ <\ \dots\ <\ A_N\ \leq\ M $
- $ B_i\ =\ A_1\ \oplus\ A_2\ \oplus\ \dots\ \oplus\ A_i $ としたとき、 $ B_1\ <\ B_2\ <\ \dots\ <\ B_N $

ただしここで、 $ \oplus $ はビット単位 $ \mathrm{XOR} $ 演算を表します。

  ビット単位 $ \mathrm{XOR} $ 演算とは  非負整数 $ A,\ B $ のビット単位 $ \mathrm{XOR} $ 、$ A\ \oplus\ B $ は、以下のように定義されます。

- $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。
 
 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の非負整数 $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ のビット単位 $ \mathrm{XOR} $ は $ (\dots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ p_2,\ p_3,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ M\ <\ 2^{60} $
- 入力される値はすべて整数

### Sample Explanation 1

例えば $ (A_1,\ A_2)=(1,\ 3) $ とすると $ A_1\ <\ A_2 $ であり、$ B_1=A_1=1,\ B_2=A_1\oplus\ A_2=2 $ より $ B_1\ <\ B_2 $ が成り立つので条件を満たします。 この他には $ (A_1,\ A_2)=(1,\ 2),\ (1,\ 4),\ (2,\ 4),\ (3,\ 4) $ が条件を満たします。

## 样例 #1

### 输入

```
2 4```

### 输出

```
5```

## 样例 #2

### 输入

```
4 4```

### 输出

```
0```

## 样例 #3

### 输入

```
10 123456789```

### 输出

```
205695670```

# 题解

## 作者：FiraCode (赞：1)

## 思路：

首先看到序列长度是 $2^{60}$ 一眼不太可做的样子。

实际上我们仔细分析一下，假如前 $i$ 个数的异或和的最高位为 $k$。

那么因为要求 $a$ 递增，又因为是异或，所以之前的数中二进制的第 $k$ 位为最高位的至少有一个，所以当前若最高位是 $k$，那么也应该是 $1$，但这样一异或就抵消的第 $k$ 为的 $1$，不满足异或和严格单调递增，所以最高位只要要比之前的 $+1$，所以方案数不为 $0$ 的 $n$ 也就是 $\log m$ 级别的。

那么就可以考虑 DP，设 $dp_i$ 表示序列长为 $i$ 的方案数。

那么枚举 $2^i < m$ 的 $i$，对于 $j < i$，都可以加上这一位（因为若长度为 $i$ 那么最大的数的二进制至少要 $i$ 位）的贡献（就是取第 $i$ 位，那么异或和无论如何都比以前大，所以剩下的位乱取即可，别忘了最多取到 $m$ 的限制就行）。

## Code：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int mod = 998244353;
typedef long long ll;

ll n, m;
ll dp[100] = {0, 1};

int main() {
	scanf("%lld%lld", &n, &m);

	int Log2 = 1;
	for (ll x = 1; x <= m; ++Log2, x *= 2) {
		ll t = (min(m, x * 2 - 1ll) - x + 1) % mod;
		for (int j = Log2; j; --j) dp[j] = (dp[j] + dp[j - 1] * t % mod) % mod;
	}

	if (n > Log2) puts("0");
	else printf("%lld\n", dp[n]); 

	return 0;
}
```

---

## 作者：xz001 (赞：0)

- 首先我们发现一个性质，那就是若 $2^n>m$ 那一定不存在解，具体证明见 [P8942](https://www.luogu.com.cn/blog/hugocaicai/solution-p8942)，直接 ```puts("0")```。
- 这样有解的情况的 $n$ 就很小了，我们 ```dp``` 一下，设立 $f_i$ 表示前 $i$ 个元素的方案数，则 $f_i=\sum_{i+1}^{1}{f_{j-1}\times (\min(m,2^i)-2^{i-1})}+f_j$（此为滚动数组优化后）。
- 答案即为 $f_n$。
- 代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int ksm (int a, int n) {
	if(!n) return 1;
	int ans = 1;
	while (n) {
		if (n & 1) ans = ans * a ;
		a = a * a;
		n >>= 1; 
	}
	return ans;
}
int n, m, f[105];
signed main() {
	scanf("%lld%lld", &n, &m);
	if (__lg(m) + 1 < n) {
		puts("0");
		return 0;
	}
	f[0] = 1;
	for (int i = 1; ksm (2, i-1) <= m; ++ i) {
		int l = ksm (2, i - 1), r = min(m, ksm (2, i) - 1);
		int k = ((r - l + 1) % mod + mod) % mod;
		for (int j = i + 1; j >= 1; -- j) f[j] = (f[j - 1] * (k + mod) % mod + f[j]) % mod;
	}
	printf("%lld", f[n]);
	return 0;
}
```

---

