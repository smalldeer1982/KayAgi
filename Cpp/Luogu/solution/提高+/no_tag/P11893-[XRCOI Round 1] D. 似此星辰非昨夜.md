# [XRCOI Round 1] D. 似此星辰非昨夜

## 题目背景

> 似此星辰非昨夜，却道故人心易变。

## 题目描述

璀璨星空下，白果给 Genius_Star 出了一些数学题。

我们把一个数称为符合条件的，当且仅当它满足以下所有条件：

- 它的数字只包含 $0,1,2,3,4$，且这五个数字都出现过至少一次。
- 所有的 $0$ 都出现在所有的 $1$ 之前，且所有的 $3$ 都出现在所有的 $4$ 之前。

- 最高位数字不为 $0$。

Genius_Star 需要求出恰好有 $n$ 位的符合条件的数的个数。当然，这个数可能很大，而白果不想让他太累，所以答案还需要对 $10^9+7$ 取模。

他不会这个问题，所以交给你了。

## 说明/提示

#### 样例解释 #1：
符合条件的 $5$ 位数为：

$$
20134,20314,20341,23014,23041,23401,30124,30142,30214,\\30241,30412,30421,32014,32041,32401,34012,34021,34201$$

### 数据范围与约定：

**本题采用捆绑测试。**

| 子任务编号 | 分值 |     $n \leq$     |
| :--------: | :--: | :---------------: |
| $1$ | $10$ | $10^3$ |
| $2$ | $20$ | $10^7$ |
| $3$ | $30$ | $2^{10^4}$ |
| $4$ | $40$ |$10^{10^7}$ |

对于 $100 \%$ 的数据，保证 $1 \le n \le 10^{10^7}$。

## 样例 #1

### 输入

```
1
5
```

### 输出

```
18
```

## 样例 #2

### 输入

```
1
6
```

### 输出

```
200
```

# 题解

## 作者：Genius_Star (赞：10)

出题人题解。

## 思路：

### 动态规划做法（60pts）：

定义：

$$dp[i][1] \to 2$$

$$dp[i][2] \to 3$$ 

$$dp[i][3] \to 0,2$$

$$dp[i][4] \to 0,3$$

$$dp[i][5] \to 2,3$$

$$dp[i][6] \to 3,4$$

$$dp[i][7] \to 0,1,2$$

$$dp[i][8] \to 0,1,3$$

$$dp[i][9] \to 0,2,3$$

$$dp[i][10] \to 0,3,4$$

$$dp[i][11] \to 2,3,4$$

$$dp[i][12] \to 0,1,2,3$$

$$dp[i][13] \to 0,1,3,4$$

$$dp[i][14] \to 0,2,3,4$$

$$dp[i][15] \to 0,1,2,3,4$$

以上表示 $i$ 位数中仅用了后面的数且满足题目要求的数的个数。

则状态转移方程为：

$$dp[i][1]=dp[i][2]=1$$

$$dp[i][3]=dp[i-1][1]+dp[i-1][3] \times 2$$

$$dp[i][4]=dp[i-1][2]+dp[i-1][4] \times 2$$

$$dp[i][5]=dp[i-1][1]+dp[i-1][2]+dp[i-1][5] \times 2$$

$$dp[i][6]=dp[i-1][2]+dp[i-1][6]$$

$$dp[i][7]=dp[i-1][3]+dp[i-1][7] \times 2$$

$$dp[i][8]=dp[i-1][4]+dp[i-1][8] \times 2$$

$$dp[i][9]=dp[i-1][3]+dp[i-1][4]+dp[i-1][5]+dp[i-1][9] \times 3$$

$$dp[i][10]=dp[i-1][4]+dp[i-1][6]+dp[i-1][10] \times 2$$

$$dp[i][11]=dp[i-1][5]+dp[i-1][6]+dp[i-1][11] \times 2$$

$$dp[i][12]=dp[i-1][7]+dp[i-1][8]+dp[i-1][9]+dp[i-1][12] \times 3$$

$$dp[i][13]=dp[i-1][8]+dp[i-1][10]+dp[i-1][13] \times 2$$

$$dp[i][14]=dp[i-1][9]+dp[i-1][10]+dp[i-1][11]+dp[i-1][14] \times 3$$

$$dp[i][15]=dp[i-1][12]+dp[i-1][13]+dp[i-1][14]+dp[i-1][15] \times 3$$

答案为：$dp[n][15]$。

时间复杂度为 $O(N)$，可以得到 $30$ 分。

之后考虑矩阵快速幂：

经过计算得 $base$ 为：

$$\begin{vmatrix}  1 & 1 & 1 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0  \\  0 & 0 & 0 & 1 & 1 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0  \\  0 & 0 & 2 & 0 & 0 & 0 & 1 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0  \\  0 & 0 & 0 & 2 & 0 & 0 & 0 & 1 & 1 & 1 & 0 & 0 & 0 & 0 & 0  \\  0 & 0 & 0 & 0 & 2 & 0 & 0 & 0 & 1 & 0 & 1 & 0 & 0 & 0 & 0  \\  0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 1 & 1 & 0 & 0 & 0 & 0  \\  0 & 0 & 0 & 0 & 0 & 0 & 2 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 2 & 0 & 0 & 0 & 1 & 1 & 0 & 0  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 3 & 0 & 0 & 1 & 0 & 1 & 0  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 2 & 0 & 0 & 1 & 1 & 0  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 2 & 0 & 0 & 1 & 0  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 3 & 0 & 0 & 1  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 2 & 0 & 1  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 3 & 1  \\  0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 3  \end{vmatrix}$$

之后按照初始矩阵 $A$（除了 $(1, 1)$ 和 $(1, 2)$ 处为 $1$，其他都为 $0$），进行快速幂即可。

时间复杂度为 $O(\log N \times W^3), W = 15$，可以获得 60pts。


### 组合数学做法（100pts）

考虑设序列 $A = \{00\cdots0011\cdots11\}$ 的长度为 $x$，序列 $B = \{33\cdots3344\cdots44\}$ 的长度为 $y$，则相当于将这两个序列插入到这 $n$ 个位置中。

容易知道，若 $A$ 的长度为 $x$，则可能的 $A$ 有 $(x - 1)$ 个，$B$ 同理。

且由于首位不能为 $0$，则相当于在后面的 $n - 1$ 选 $x$ 个放 $A$，然后在剩下的 $n - x$ 个位置放 $B$，没放的显然是填 $2$，那么答案为：

$$\begin{aligned} Ans &= \sum_{x = 2}^{n - 1} \sum_{y = 2}^{n - x - 1} \binom{n - 1}{x} (x - 1) \binom{n - x}{y} (y - 1) \\ &= \sum_{x = 2}^{n - 2} \binom{n - 1}{x} (x - 1) \left( \sum_{y = 0}^{n - x} \binom{n - x}{y} (y -1) - n + x + 2\right) \\ &= \sum_{x = 2}^{n - 2} \binom{n - 1}{x} (x - 1) \left( \sum_{y = 0}^{n - x} \binom{n - x}{y} y -2^{n - x}-n + x + 2\right) \\ &= \sum_{x = 2}^{n - 1} \binom{n - 1}{x} (x - 1) \left((n - x)\sum_{y = 0}^{n - x}\binom{n - x - 1}{y - 1} - 2^{n - x} - n + x + 2\right) \\ &= \sum_{x = 2}^{n - 1} \binom{n - 1}{x}(x - 1)\left( (n - x) 2^{n - x - 1} - 2^{n - x}  - n + x + 2\right) \\ &= \sum_{x = 0}^{n-1 }\binom{n - 1}{x}(x - 1)\left( (n - x) 2^{n - x - 1} - 2^{n - x}  - n + x + 2\right) + \left(n2^{n - 1} - 2^n - n + 2\right) \\ &= \sum_{x = 0}^{n - 1} \binom{n - 1}{x} x \left( (n - x) 2^{n - x - 1} - 2^{n - x}  - n + x + 2\right) \\ &-\sum_{x = 0}^{n - 1} \binom{n - 1}{x} \left( (n - x) 2^{n - x - 1} - 2^{n - x}  - n + x + 2\right) \\ &+\left(n2^{n - 1} - 2^n - n + 2\right) \\ &= (n - 1) \sum_{x = 0}^{n - 2} \binom{n - 2}{x} \left( (n - x -  1) 2^{n - x - 2} - 2^{n - x - 1} - n + x + 3\right) \\ &-\sum_{x = 0}^{n - 1} \binom{n - 1}{x} (n - x) 2^{n - x - 1}+ \sum_{x = 0}^{n - 1} \binom{n - 1}{x} 2^{n - x} \\& + n 2^{n - 1} - (n - 1)2^{n - 2}  - 2^n + n2^{n - 1} - 2^n - n + 2 \\ &= (n - 1) \sum_{x = 0}^{n - 2} \binom{n - 2}{x} \left( (n - x -  1) 2^{n - x - 2} - 2^{n - x - 1} - n + x + 3\right) \\ &-\sum_{x = 0}^{n - 1} \binom{n - 1}{x} (n - x) 2^{n - x - 1}+ \sum_{x = 0}^{n - 1} \binom{n - 1}{x} 2^{n - x} \\ &+ (3n - 7) 2^{n - 2} - n + 2  \\&= (n - 1) \sum_{x = 0}^{n - 2} \binom{n - 2}{x} \left( (n - x -  1) 2^{n - x - 2} - 2^{n - x - 1} - n + x + 3\right) \\ &-n\sum_{x = 0}^{n - 1} \binom{n - 1}{x} 2^{n - x - 1} + \sum_{x = 0}^{n - 1} \binom{n - 1}{x} x 2^{n - x - 1} \\&+ 2 \times 3^{n - 1} + (3n - 7) 2^{n - 2} - n + 2 \\ &=(n - 1) \sum_{x = 0}^{n - 2} \binom{n - 2}{x} \left( (n - x -  1) 2^{n - x - 2} - 2^{n - x - 1} - n + x + 3\right) \\ &+(n - 1)\sum_{x = 0}^{n - 2} \binom{n - 2}{x} 2^{n - x - 2} \\&-n 3^{n - 1}+ 2 \times 3^{n - 1} + (3n - 7) 2^{n - 2} - n + 2 \\ &=  (n - 1) \sum_{x = 0}^{n - 2} \binom{n - 2}{x} \left( (n - x -  1) 2^{n - x - 2} - 2^{n - x - 1} - n + x + 3\right) \\ &-(2n - 5)3^{n - 2} + (3n - 7) 2^{n - 2} - n + 2 \\ &= (n - 1) \Big(\sum_{x = 0}^{n - 2} \binom{n - 2}{x} (n - x - 1)2^{n - x - 2} - \sum_{x = 0}^{n - 2} \binom{n - 2}{x}2^{n - x - 1} \\  &- n \sum_{x = 0}^{n - 2} \binom{n - 2}{x}  +  \sum_{x = 0}^{n - 2} \binom{n - 2}{x} x + 3 \sum_{x = 0}^{n - 2} \binom{n - 2}{x} \Big) \\ &-(2n - 5)3^{n - 2} + (3n - 7) 2^{n - 2} - n + 2 \\ &= (n - 1)\Big((n - 1) \sum_{x = 0}^{n - 2} \binom{n - 2}{x} 2^{n - x - 2} - \sum_{x = 0}^{n - 2} \binom{n - 2}{x} x 2^{n - x - 2}  \\ &- 2 \times 3^{n - 2}- n 2^{n - 2} + (n - 2)2^{n - 3} + 3 \times 2^{n - 2} \Big) \\ &-(2n - 5)3^{n - 2} + (3n - 7) 2^{n - 2} - n + 2 \\ &= (n - 1) \left((n - 1) 3^{n - 2} - (n - 2)3^{n - 3} - 2 \times 3^{n - 2} - n 2^{n - 2} + (n - 2)2^{n - 3} + 3 \times 2^{n - 2} \right) \\ &-(2n - 5)3^{n - 2} + (3n - 7) 2^{n - 2} - n + 2 \\ &= -5\,n\,3^{n-2}-9\,2^{n-2}+2\,n^2\,3^{n-3}+22\,3^{n-3}-n^2\,2^{n-3}+ 11\,n\,2^{n-3}-n+2 \end{aligned}$$


上面的推理运用了以下恒等式：

- $$\sum_{i = 0}^n \binom{n}{i} = 2^n$$

> **证明：**
> 考虑组合意义，在 $n$ 个物品中选任意个，每个物品选或不选，方案数是 $2^n$。

- $$\binom{n}{m}m = n \binom{n - 1}{m - 1}$$

> **证明：**
> $$\begin{aligned} \binom{n}{m}m &= \frac{n!}{m!(n - m)!}m \\&= \frac{n!}{(m - 1)(n - m)!} \\&= n \frac{(n - 1)!}{(m - 1)!(n - m)!} \\&=n \binom{n - 1}{m - 1} \end{aligned} $$

- $$\sum_{i = 0}^n \binom{n}{i} 2^{n - i} = 3^n$$

> **证明：**
> 考虑组合意义，每个物品有三种形态，枚举仅有 $i$ 个物品是第一种形态，则剩下的 $n - i$ 个物品在剩下两种形态任选；等价于所有形态的方案数 $3^n$。

时间复杂度为 $O(len + \log mod)$。

**主要考察选手组合数学基本功。**

```cpp
#include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define int long long
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e7 + 10, mod = 1e9 + 7; 
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
int n, mn, mbase = 1, len, sum, base = 1;
char s[N];
inline int qpow(int a, int b){
	if(b < 0)
	  b += mod - 1;
	int ans = 1;
	while(b){
		if(b & 1)
		  ans = 1ll * ans * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ans;
}
bool End;
signed main(){
	len = read();
	scanf("%s", s + 1);
	for(int i = len; i >= 1; --i){
		n += (s[i] - '0') * base;
		mn += (s[i] - '0') * mbase;
		n %= mod;
		mn %= (mod - 1);
		base = base * 10ll % mod;
		mbase = mbase * 10ll % (mod - 1);
	}
	sum = (mod - 5ll * n % mod * qpow(3, mn - 2) % mod) + (mod - 9ll * qpow(2, mn - 2) % mod) + 2ll * n % mod * n % mod * qpow(3, mn - 3) % mod + 22ll * qpow(3, mn - 3) % mod + (mod - n * n % mod * qpow(2, mn - 3) % mod) + 11ll * n % mod * qpow(2, mn - 3) % mod + (mod - n) + 2;
	write(sum % mod);
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Composite_Function (赞：5)

赛时没时间口胡的。赛后已复现。

---

首先考虑 $n$ 位数中选出 $i$ 个是 $0$ 或 $1$，$j$ 个是 $3$ 或 $4$，其余填 $2$。这样答案就是：

$$\sum_{i=2}^{n-1}\sum_{j=2}^{n-i-1}{{n-1}\choose{i}}{{n-i-1}\choose{j}}(i-1)(j-1)$$

分离并作简单的计算得到：

$$\sum_{i=2}^{n-1}{{n-1}\choose{i}}(i-1)\left(\sum_{j=2}^{n-i-1}\left((n-i-1){{n-i-2}\choose{j-1}}-{{n-i-1}\choose{j}}\right)\right)$$

进一步得到：

$$\sum_{i=2}^{n-1}{{n-1}\choose{i}}(i-1)\left((n-i-1)2^{n-i-2}-2^{n-i-1}+1\right)$$

即：

$$\sum_{i=2}^{n-1}\left((n-1){{n-2}\choose{i-1}}-{{n-1}\choose{i}}\right)\left((n-i-1)2^{n-i-2}-2^{n-i-1}+1\right)$$

然后我们如法炮制把上面的东西进一步拆开：

$$(2n^2-15n+22)3^{n-3}-(n^2-11n+18)2^{n-3}-n+2$$

就可以强行算了。常数极小。

当然如果你注意力惊人会知道算到这个地方的时候答案一定会是常数的幂乘以多项式，直接待定系数即可。

---

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FastIO {
	inline FastIO& operator >> (short& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (int& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (long long& x) {
		x = 0;
		char f = 0, ch = getchar();
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
		return x = (f ? -x : x), *this;
	}
	inline FastIO& operator >> (double& x) {
		x = 0;
		char f = 0, ch = getchar();
		double d = 0.1;
		while (ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
		while (ch <= '9' && ch >= '0') x = x * 10 + (ch ^ 48), ch = getchar();
		if (ch == '.') {
			ch = getchar();
			while (ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
		}
		return x = (f ? -x : x), *this;
	}
} rin;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&
#define endl "\n"

inline void qmod(int& x, const int& mod) {
	x = x >= mod? x - mod : x;
}

const int N = 1e7 + 10, mod = 1e9 + 7, Mod = mod - 1;
int l;
ll val, idx;
char ch[N];
inline int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod, b >>= 1;
	}
	return res;
}

signed main() {
	rin >> l, cin >> ch;
	if (l <= 1 && ch[0] <= '4') return puts("0"), 0;
	for (int i = 0; i < l; ++i) {
		val = ((val << 3) + (val << 1) + (ch[i] ^ 48)) % mod;
		idx = ((idx << 3) + (idx << 1) + (ch[i] ^ 48)) % Mod;
	}
	ll res = (2 * val * val - 15 * val + 22) % mod * qpow(3, idx - 3) % mod;
	res -= (val * val - 11 * val + 18) % mod * qpow(2, idx - 3) % mod;
	res = res - val + 2;
	res = (res % mod + mod) % mod;
	cout << res << endl;
	return 0;
}
```

拜谢 @Ruan_ji 提出的错误。

---

## 作者：zyn_ (赞：4)

本文将详细讲解本题的计算推导。

- 你只需要求和号与组合数的定义作为前置知识。
- 本文能有效治疗公式恐惧症。

## 题意

求长为 $n$ 的每一项在 $\{0,1,2,3,4\}$ 中的序列的数量，满足：每种数均出现；所有 $0$ 在 $1$ 之前，所有 $3$ 在 $4$ 之前；首项非 $0$。

## 枚举

考虑枚举有 $i$ 个 $0,1$，$j$ 个 $2$，$k$ 个 $3,4$。

1. 定下 $0,1$ 的位置，由于 $0$ 不为首项且 $0$ 在 $1$ 之前，知：要从后 $n-1$ 个位置取 $i$ 个，有 $\binom{n-1}{i}$ 种取法。
2. 定下 $3,4$ 的位置，还剩 $n-i$ 个位置，选 $k$ 个，有 $\binom{n-i}{k}$ 种取法。
3. 从 $0,1$ 的位置中区分出 $0,1$。由于至少有一个 $0$ 与一个 $1$，且所有 $0$ 在 $1$ 之前，因此有 $i-1$ 种方法。
4. 从 $3,4$ 的位置中区分出 $3,4$。同理，有 $k-1$ 种方法。

于是，答案为：

$$
\sum_{i+j+k=n,i\ge 2,k\ge 2}(i-1)(k-1)\binom{n-1}{i}\binom{n-i}{k}
$$

接下来就是推式子了。

## 计算

$i-1$ 与 $k-1$ 看着很难受，干掉：

$$
\sum_{i+j+k=n-2,i\ge 1,k\ge 1}ik\binom{n-1}{i+1}\binom{n-i-1}{k+1}
$$

因为要有 $2$，所以要保证 $j\ge 1$。然后 $j$ 没用了。

$$
\sum_{i+j\le n-3,i\ge 1,k\ge 1}ik\binom{n-1}{i+1}\binom{n-i-1}{k+1}
$$

写成两层求和号：

$$
\sum_{i=1}^{n-3}\sum_{k=1}^{n-3-i}ik\binom{n-1}{i+1}\binom{n-i-1}{k+1}
$$

把与 $k$ 无关的东西提出来：

$$
\sum_{i=1}^{n-3}i\binom{n-1}{i+1}\sum_{k=1}^{n-3-i}k\binom{n-i-1}{k+1}
$$

考虑计算内层求和。令 $m=n-i-2$，则内层求和为：

$$
\sum_{k=1}^{m-1}k\binom{m+1}{k+1}
$$

### 引理 $1$

$$
\sum_{k=1}^{m-1}k\binom{m+1}{k+1}=(m-1)(2^m-1)
$$

证明：令左边为 $S$。

显然有

$$
S=\sum_{k=1}^{m-1}k\binom{m+1}{k+1}=\sum_{k=0}^{m-1}k\binom{m+1}{k+1}
$$

熟知 $\binom{n}{m}=\binom{n}{n-m}$，于是

$$
S=\sum_{k=0}^{m-1}k\binom{m+1}{k+1}=\sum_{k=0}^{m-1}k\binom{m+1}{m-k}
$$

重新令上式右边的 $m-k$ 为 $l+1$，由 $k$ 从 $0$ 到 $m-1$，知 $l$ 也从 $0$ 到 $m-1$，且 $k=m-1-l$。所以

$$
S=\sum_{l=0}^{m-1}(m-1-l)\binom{m+1}{l+1}=\sum_{k=0}^{m-1}(m-1-k)\binom{m+1}{k+1}
$$

注意到

$$
2S=\sum_{k=0}^{m-1}k\binom{m+1}{k+1}+\sum_{k=0}^{m-1}(m-1-k)\binom{m+1}{k+1}
$$

合并求和号并应用乘法分配律：

$$
S=\frac{1}{2}\sum_{k=0}^{m-1}(m-1)\binom{m+1}{k+1}=\frac{m-1}{2}\sum_{k=0}^{m-1}\binom{m+1}{k+1}
$$

### 引理 $2$

$$
\sum_{i=0}^n\binom{n}{i}=2^n
$$

这是因为，考虑**二项式定理**：

$$
(1+x)^n=\sum_{i=0}^n\binom{n}{i}x^i
$$

这个定理的组合意义是，考虑多项式乘法的本质，$x^i$ 的系数即为 $n$ 个 $(1+x)$ 中恰取 $i$ 个 $x$ 的方案数。

令 $x=1$，引理 $2$ 证毕。

---

回到引理 $1$ 的证明。有

$$
\sum_{k=0}^{m-1}\binom{m+1}{k+1}=\sum_{k=1}^{m}\binom{m+1}{k}
$$

相比引理 $1$，缺了 $k=0$ 和 $k=m+1$ 两项，这两项的值均为 $1$。于是

$$
\sum_{k=0}^{m-1}\binom{m+1}{k+1}=2^{m+1}-2=2(2^m-1)
$$

从而

$$
S=\frac{m-1}{2}\sum_{k=0}^{m-1}\binom{m+1}{k+1}=(m-1)(2^m-1)
$$

引理 $1$ 证毕。

---

支线终于结束了，让我们回到主线证明。

$$
\sum_{i=1}^{n-3}i\binom{n-1}{i+1}\sum_{k=1}^{n-3-i}k\binom{n-i-1}{k+1}
$$

由引理 $1$

$$
\sum_{k=1}^{n-3-i}k\binom{n-i-1}{k+1}=(n-i-3)(2^{n-i-2}-1)
$$

代入得

$$
\sum_{i=1}^{n-3}i\binom{n-1}{i+1}(n-i-3)(2^{n-i-2}-1)
$$

$n-i-3$ 看着很不爽。令 $t=n-3$。

$$
\sum_{i=1}^{t}i(t-i)\binom{t+2}{i+1}(2^{t+1-i}-1)
$$

注意到

$$
\binom{t+2}{i+1}=\frac{(t+2)!}{(i+1)!(t-i+1)!}=\binom{t}{i}\frac{(t+1)(t+2)}{(i+1)(t-i+1)}
$$

$$
i(t-i)=(i+1)(t-i+1)-t-1
$$

代入上式：

$$
\sum_{i=1}^{t}((i+1)(t-i+1)-t-1)\binom{t+2}{i+1}(2^{t+1-i}-1)
$$

乘法分配律，拆成两部分：

$$
A-B
$$

$$
A=\sum_{i=1}^{t}(i+1)(t-i+1)\binom{t+2}{i+1}(2^{t+1-i}-1)
$$

$$
B=\sum_{i=1}^{t}(t+1)\binom{t+2}{i+1}(2^{t+1-i}-1)
$$

### 第一部分

计算 $A$。先将组合数代换掉：

$$
\sum_{i=1}^{t}(i+1)(t-i+1)\binom{t}{i}\frac{(t+1)(t+2)}{(i+1)(t-i+1)}(2^{t+1-i}-1)
$$

约分，提出与 $i$ 无关的项：

$$
(t+1)(t+2)\sum_{i=1}^{t}\binom{t}{i}(2^{t+1-i}-1)
$$

只算求和号。先拆成两部分：

$$
\sum_{i=1}^{t}\binom{t}{i}2^{t+1-i}-\sum_{i=1}^{t}\binom{t}{i}
$$

减号后面好像引理 $2$，但是缺了 $i=0$。由 $\binom{t}{0}=1$ 知减数的值为 $2^t-1$。

被减数中的 $t+1-i$ 不好看。令 $k=t-i$，由于 $i$ 从 $1$ 到 $t$ 知 $k$ 从 $0$ 到 $t-1$。于是被减数可以写成

$$
\sum_{k=0}^{t-1}\binom{t}{t-k}2^{k+1}=2\sum_{k=0}^{t-1}\binom{t}{k}2^k
$$

### 引理 $3$

$$
\sum_{i=0}^n\binom{n}{i}2^i=3^n
$$

还是考虑**二项式定理**：

$$
(1+x)^n=\sum_{i=0}^n\binom{n}{i}x^i
$$

这次令 $x=2$，引理 $3$ 证毕。

---

$$
\sum_{k=0}^{t-1}\binom{t}{k}2^k
$$

和引理 $3$ 只差了 $k=t$ 一项，该项值为 $2^t$，于是

$$
\sum_{k=0}^{t-1}\binom{t}{k}2^k=3^t-2^t
$$

然后回代可知

$$
A=(t+1)(t+2)(2(3^t-2^t)-(2^t-1))
$$

### 第二部分

计算 $B$。提出与 $i$ 无关的部分：

$$
B=(t+1)\sum_{i=1}^{t}\binom{t+2}{i+1}(2^{t+1-i}-1)
$$

只算求和号，拆成两部分：

$$
\sum_{i=1}^{t}\binom{t+2}{i+1}2^{t+1-i}-\sum_{i=1}^{t}\binom{t+2}{i+1}
$$

这里的处理方法与第一部分几乎一样，留给读者练习。

最后算出来：

$$
B=(t+1)(3^{t+2}-(t+6)2^{t+1}+t+3)
$$

---

所以最后的答案是：

$$
A-B=(t+1)(t+2)(2(3^t-2^t)-(2^t-1))-(t+1)(3^{t+2}-(t+6)2^{t+1}+t+3)
$$

前面令 $t=n-3$，代入，答案化为

$$
(n-2)(n-1)(2(3^{n+3}-2^{n+3})-(2^{n+3}-1))-(n-2)(3^{n-1}-(n+3)2^{n-2}+n)
$$

注意到 $n\le 10^{10^7}$，而我们要算这式对质数 $p=10^9+7$ 取模的值。由**费马小定理**知 $p\nmid a$ 时 $a^{p-1}\equiv 1\pmod p$。于是将幂次对 $p-1$ 取模，然后快速幂即可。

注意取模次数不要太多，否则会导致 $O(\log n)$ 的算法被卡常的悲剧。

```cpp
#include<bits/stdc++.h>
#define m 1000000007
#define N 10000009
#define ll long long
int l;
ll qpow(ll a,ll b,ll p){
    ll r=1;
    while(b)(b&1)&&(r=r*a%p),a=a*a%p,b>>=1;
    return r;
}
char s[N];
int md(int p){
    ll r=0;
    for(int i=1;i<=l;++i){
        r=r*10+s[i]-48;
        if((i&7)==0)r%=p;
    }
    return r%p;
}
int main(){
    std::cin>>l>>s+1;
    ll a=md(m),b=md(m-1);
    ll a_1=(a+m-1)%m,a_2=(a+m-2)%m,a_3=(a+m-3)%m;
    ll b_1=(b+m-2)%(m-1),b_2=(b+m-3)%(m-1),b_3=(b+m-4)%(m-1);
    ll p2=qpow(2,b_3,m),p3=qpow(3,b_3,m);
    ll ans=a_2*a_1%m*(2*p3-3*p2+1)-a_2*(p3*9%m-p2*2%m*(a+3)%m+a)%m;
    ans=(ans%m+m)%m;
    std::cout<<ans;
}
```

---

## 作者：wosile (赞：4)

这里是一个非常弱智的做法。

考虑容斥原理，那么设 $f(S)(S \subseteq \{0,1,2,3,4\})$ 表示我们只使用 $S$ 内的数，去掉所有数都出现这个限制的方案数，那么我们有：

$$ans=\sum\limits_{S}(-1)^{|S|+1}f(S)$$

然后我们惊奇的发现有 $32$ 个 $f(S)$ 要求。注意到可以根据 $0/1$ 的出现情况和 $3/4$ 的出现情况把 $S$ 分成 $6$ 类：

- AA：$0,1$ 均在 $S$ 中，$3,4$ 均在 $S$ 中；
- AB：$0,1$ 均在 $S$ 中，$3,4$ 不均在 $S$ 中（只出现一个或两者均不出现）；
- BA：$0$ 在 $S$ 中，$1$ 不在 $S$ 中，$3,4$ 均在 $S$ 中；
- BB：$0$ 在 $S$ 中，$1$ 不在 $S$ 中，$3,4$ 不均在 $S$ 中；
- CA：$0$ 不在 $S$ 中，$3,4$ 均在 $S$ 中；
- CB：$0$ 不在 $S$ 中，$3,4$ 不均在 $S$ 中。

手推一下可以发现，假如我们记 $g(S)=[0 \in S \lor 1 \in S]+[2 \in S]+[3 \in S \lor 4 \in S]$，确定若干个关键位置之后答案和 $g(S)^n$ 有关。那么以上每一类的答案都可以写成一个和 $g(S)$ 有关的式子。

具体的式子推法不再赘述，对于题目中所描述的限制，可以考虑枚举 $0$ 和 $3$ 最后一次出现的位置然后计数。详见代码。

值得注意的是，我们的式子中含有 $3^n$ 和 $2^n$，直接快速幂可能会超时，我们可以使用费马小定理，转而计算 $3^{n \bmod (10^9+6)}$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define moD 1000000006
int qp(int x,int y=mod-2){
    int ans=1;
    while(y){
        if(y&1)ans=1LL*ans*x%mod;
        x=1LL*x*x%mod;
        y>>=1;
    }
    return ans;
}
int p[5][5],m,m2;
// 这里的 p[i][j] 表示 i^(n-j)
int inv[5][5];
int AA(int x){
    return (p[x][0]+1LL*m*p[x][1]%mod+1LL*(mod+m-1)*(x-1)%mod*p[x][2]%mod+1LL*(mod+m-1)*(mod+m-2)%mod*(x-1)%mod*p[x][3]%mod+1LL*(mod+m-1)*p[x][2]%mod)%mod;
}
int AB(int x){
    return (1LL*(mod+m-1)*p[x][2]%mod*(x-1)%mod+p[x][0])%mod;
}
int BA(int x){
    return (p[x][1]+1LL*(x-1)*(mod+m-1)%mod*p[x][2]+1LL*(x-1)*p[x][1]%mod)%mod;
}
int BB(int x){
    return 1LL*(x-1)*p[x][1]%mod;
}
int CA(int x){
    return (p[x][0]+1LL*m*p[x][1])%mod;
}
int CB(int x){
    return p[x][0];
}
char s[10000005];
int main(){
    int l;
    inv[2][0]=inv[3][0]=1;
    for(int i=0;i<5;i++)inv[1][i]=1;
    inv[2][1]=qp(2),inv[3][1]=qp(3);
    for(int i=2;i<5;i++)inv[2][i]=1LL*inv[2][1]*inv[2][i-1]%mod,inv[3][i]=1LL*inv[3][1]*inv[3][i-1]%mod;
    scanf("%d",&l);
    scanf("%s",s+1);
    for(int i=1;i<=l;i++)m=(10LL*m+s[i]-'0')%mod;
    for(int i=1;i<=l;i++)m2=(10LL*m2+s[i]-'0')%moD;
    p[1][0]=1,p[2][0]=qp(2,m2),p[3][0]=qp(3,m2);

    for(int i=1;i<5;i++)for(int j=1;j<=3;j++)p[j][i]=1LL*p[j][0]*inv[j][i]%mod;
    int ans=0;
    for(int i=0;i<32;i++){
        int x=(!!(i&3))+(!!(i&4))+(!!(i&24));
        int val;
        if((i&27)==27)val=AA(x);
        else if((i&3)==3)val=AB(x);
        else if((i&25)==25)val=BA(x);
        else if((i&1)==1)val=BB(x);
        else if((i&24)==24)val=CA(x);
        else val=CB(x);
        if(__builtin_popcount(i)&1)ans=(ans+val)%mod;
        else ans=(ans-val+mod)%mod;
    }
    printf("%d",ans);
    return 0;
}
```

---

