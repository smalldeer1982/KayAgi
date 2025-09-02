# Moamen and XOR

## 题目描述

Moamen and Ezzat are playing a game. They create an array $ a $ of $ n $ non-negative integers where every element is less than $ 2^k $ .

Moamen wins if $ a_1 \,\&\, a_2 \,\&\, a_3 \,\&\, \ldots \,\&\, a_n \ge a_1 \oplus a_2 \oplus a_3 \oplus \ldots \oplus a_n $ .

Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND), and $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Please calculate the number of winning for Moamen arrays $ a $ .

As the result may be very large, print the value modulo $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

In the first example, $ n = 3 $ , $ k = 1 $ . As a result, all the possible arrays are $ [0,0,0] $ , $ [0,0,1] $ , $ [0,1,0] $ , $ [1,0,0] $ , $ [1,1,0] $ , $ [0,1,1] $ , $ [1,0,1] $ , and $ [1,1,1] $ .

Moamen wins in only $ 5 $ of them: $ [0,0,0] $ , $ [1,1,0] $ , $ [0,1,1] $ , $ [1,0,1] $ , and $ [1,1,1] $ .

## 样例 #1

### 输入

```
3
3 1
2 1
4 0```

### 输出

```
5
2
1```

# 题解

## 作者：SDqwq (赞：18)

[传送门](https://www.luogu.com.cn/problem/CF1557C)

~~说句闲话，赛时因为和 @[Leasier](https://www.luogu.com.cn/user/201007) 聊天导致没写完代码。~~

# $\texttt{Description}$

- 给定 $n$ 和 $k$，$n$ 为序列长度，$k$ 表示序列中的值上限为 $2^k-1$。

- 求出有多少种满足 $a_1\ \mathrm{and}\ a_2\ \mathrm{and}\ a_3\ \mathrm{and}\ \dots\ \mathrm{and}\ a_n\ge a_1\ \mathrm{xor}\ a_2\ \mathrm{xor}\ a_3\ \mathrm{xor}\ \dots\ \mathrm{xor}\ a_n$ 的序列 $a$，答案对 $10^9+7$ 取模。

- 多测。

**数据范围：$1\le n\le2\times10^5,0\le k\le2\times10^5$。**

# $\texttt{Solution}$

- 不难看出 $k$ 为每个数的二进制的最大位数。

- 对于二进制的每一位分开考虑。

- 令二进制数最高位为第一位，次高位为第二位，以此类推。

- 设 $p1$ 为 $a_1\ \mathrm{and}\ a_2\ \mathrm{and}\ a_3\ \mathrm{and}\ \dots\ \mathrm{and}\ a_n$，$p2$ 为 $a_1\ \mathrm{xor}\ a_2\ \mathrm{xor}\ a_3\ \mathrm{xor}\ \dots\ \mathrm{xor}\ a_n$。

- 要满足 $p1\ge p2$ 的条件，分两种情况讨论：

	- 若 $p1=p2$，那么 $p1$ 和 $p2$ 的每一位一定都相等，对于每一位：
    
    	- 若为 $0$：则 $a_1$ 到 $a_n$ 的这一位必然至少有一个为 $0$，且为 $1$ 的个数有偶数个（因为偶数个 $1$ 异或结果为 $0$），所以方案数为 $\sum\mathcal{C}_{n}^{i}$ 且 $i\equiv0\pmod2$ 且 $i\ne n$。
        
      - 若为 $1$：则 $a_1$ 到 $a_n$ 的这一位必然全为 $1$，但如果 $n$ 为偶数，则这样的情况不成立。当这样的情况成立时，方案数为 $1$。
      
   - 若 $p1>p2$，那么一定存在某一位 $k$ 使得 $p1$ 的第 $k$ 位为 $1$ 且 $p2$ 的第 $k$ 位为 $0$，并且满足 $p1$ 和 $p2$ 的 $1$ 到 $k-1$ 位都相等，**但是只有 $k$ 为偶数时这种情况才能成立**。
   
   - 于是我们可以想到枚举这个 $k$。对于每个 $k$，方案数为前面 $k-1$ 位都相等的方案数（已在上面讨论过）乘上 $(2^n)^{n-k}$，因为第 $k$ 位后面的可以随便乱选。

- 那么这道题就分析完了，之后套一下柿子就可以了。

时间复杂度：$\mathcal{O}(n\log n)$

# $\texttt{Code}$

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll fac[200005];
inline void init(ll n) {
	fac[0] = 1;
	for (ll i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
}
inline ll quick_pow(ll a, ll k, ll p) {
	ll res = 1;
	a %= p;
	while (k) {
		if (k & 1) res = res * a % p;
		a = a * a % p;
		k >>= 1;
	}
	return res;
}
inline ll inv(ll x, ll p) {return quick_pow(x, p - 2, p);}
inline ll getC(ll n, ll m, ll p) {return fac[n] * inv(fac[n - m] * fac[m] % p, p) % p;}

int main() {
	init(2e5);
	int T;
	scanf("%d", &T);
	while (T--) {
		ll n, k, ans = 0, sum = 0;
		scanf("%lld %lld", &n, &k);
		for (ll i = 0; i < n; i += 2) sum = (sum + getC(n, i, mod)) % mod;
		if (n & 1) ans = (ans + quick_pow(sum + 1, k, mod)) % mod;
		else {
			for (ll i = 0; i < k; i++) ans = (ans + quick_pow(sum, i, mod) * quick_pow(quick_pow(2, n, mod), k - i - 1, mod) % mod) % mod;
			ans = (ans + quick_pow(sum, k, mod)) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：zhiyangfan (赞：10)

### 题意简述
（顺便算是提交了翻译？）

$t$ 组数据，每组给出 $n,k$ 。尝试构造一个长度为 $n$ 的数组 $a$ ，满足 $\forall i,a_i<2^k$ 。问这样的数组中有多少个满足 $a_1 \operatorname{and} a_2 \operatorname{and} \cdot\cdot\cdot\operatorname{and}a_n\ge a_1\operatorname{xor} a_2\operatorname{xor}\cdot\cdot\cdot\operatorname{xor}a_n$ 其中 $\operatorname{and}$ 为按位且，$\operatorname{xor}$ 为按位异或，答案对 $10^9+7$ 取模。（ $1\le t\le 5,1\le n\le 2\times10^5,0\le k\le 2\times10^5$​ ）
### 思路解释
注意到对于 $\operatorname{and}$ ，当且仅当 $n$ 个数在第 $i$ 位全为 $1$ ，最终结果才为 $1$ ；对于 $\operatorname{xor}$ ，当且仅当 $n$ 个数在第 $i$ 位有奇数个 $1$ ，最终结果才为 $1$ 。这启示我们按 $n$ 的奇偶性分类讨论。

当 $n$ 为奇数时，对于第 $i$ 位有如下表格：

$\begin{array}{|c|c|c|c|}--&\operatorname{and}&--&\operatorname{xor}\\\text{全为}1&1&=&1\\\text{奇数}0&0&=&0\\\text{偶数}0&0&<&1\end{array}$​​ 

注意到这时候 $\operatorname{and}$​​ 起来的结果不可能大于 $\operatorname{xor}$​​ 的结果，所以每一位只能取等号来避免小于 $\operatorname{xor}$​​ 。所以每一位的情况数就为全为 $1$​​ 和奇数 $0$​​ 的情况数之和，即第 $j$​位的情况 $c_j=1+\sum_{i=1}^{\frac{n+1}{2}}\dbinom{n}{2i-1}$​​​ ，而所有位的情况即为 $\prod_{i=1}^k c_i=c_1^k$​ 。预处理阶乘，按式子求出来之后快速幂求解即可。总复杂度​ $\mathcal{O}(n)$​ 。

当 $n$ 为偶数时，对于第 $i$ 位有如下表格：

$\begin{array}{|c|c|c|c|}--&\operatorname{and}&--&\operatorname{xor}\\\text{全为}1&1&>&0\\\text{奇数}0&0&<&1\\\text{偶数}0&0&=&0\end{array}$

注意到这时候三种运算符都有，不好直接下手，考虑补集转换。求 $\operatorname{and}$​​​​ 出来的结果小于 $\operatorname{xor}$​​​​ 结果的方案数。当 $\operatorname{and}$​​​​ 出来的结果小于 $\operatorname{xor}$​​​​ 结果时，必然存在一位有奇数个 $0$​​​​ 且这一位前面全都是偶数 $0$​​​​ ，而后面的可以随便取（因为这一位的小于已经占据了主要部分，后面的即使再多大于也没有这个小于的值大，而为了保证前面没有大于抢占主要部分且不重复计算，前面只取等于）。这样我们枚举大于号存在的那一位所在的位数即可计算。答案即为 $\sum_{i=1}^k t_1\times t_2^{k-i}\times(2^{i-1})^n$​​​​​ ，其中​ $t_1=\sum_{i=1}^{\left\lfloor\frac{n+1}{2}\right\rfloor} \dbinom{n}{2i-1}$​​​ ，即 $n$​​​ 个数第 $i$​​​ 位有奇数 $0$​​ 的方案数；$t_2\sum_{i=2}^{\frac{n}{2}}\dbinom{n}{2i}$​ ，即 $n$​ 个数第 $i$​​即 $n$​ 个数第 $i$​​ 位有​​偶数 $0$ 的方案数。预处理出阶乘， $t_1,t_2$ 后按式子用快速幂求解即可。总复杂度 $\mathcal{O}(n)$ 。 
### 代码
结束前5秒过了样例，没交上去/kk
```cpp
#include <cstdio>
const int mod = 1e9 + 7, N = 2e5 + 10; int fac[N], ifac[N];
inline int ksm(int a, int b)
{
	int ret = 1;
	while (b)
	{
		if (b & 1) ret = 1ll * ret * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return ret;
}
inline int C(int a, int b) { return 1ll * fac[a] * ifac[b] % mod * ifac[a - b] % mod;  }
int main()
{
	int T; scanf("%d", &T); fac[0] = ifac[0] = 1;
	for (int i = 1; i < N; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[N - 1] = ksm(fac[N - 1], mod - 2);
	for (int i = N - 2; i >= 1; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
	while (T--)
	{
		int n, k; scanf("%d%d", &n, &k);
		if (n & 1)
		{
			int tmp = 1;
			for (int i = 1; i <= (n + 1) / 2; i++)
				tmp = (tmp + C(n, 2 * i - 1)) % mod;
			printf("%d\n", ksm(tmp, k));
		}
		else
		{
			int tmp = 0, t1 = 0, t2 = 0;
			for (int i = 2; i <= n; i += 2) t1 = (t1 + C(n, i)) % mod;
			for (int i = 1; i <= n; i += 2) t2 = (t2 + C(n, i)) % mod;
			for (int i = 1; i <= k; i++)
				tmp = (tmp + 1ll * t2 * ksm(t1, k - i) % mod * ksm(ksm(2, i - 1), n) % mod) % mod;
			printf("%d\n", (ksm(ksm(2, k), n) - tmp + mod) % mod);
		}
	}
	return 0;
}
```

---

## 作者：Meaninglessness (赞：3)

### C. Moamen and XOR

**题目大意：**

> 给定数组 $a$ 的长度 $n$ 与 $k$，请输出有多少种构造方式使得 $a$ 数组中的每个数都小于 $2^k$，且 $a_1\&a_2\&\cdots\&a_n\ge a_1\oplus a_2\oplus\cdots\oplus a_n$，并对 ${10}^9+7$ 取模。

**解题思路：**

考虑计算不符合要求的情况，即 $a_1\&a_2\&\cdots\&a_n < a_1\oplus a_2\oplus\cdots\oplus a_n$。

于是我们将 $a_i$ 用 $2$ 进制表示，然后从高位到低位处理。

在 $2$ 进制下，每个数都有 $k$ 位（不足补前导 $0$），并且共有 $n$ 个数。可以先分为几种情况：

1. 有奇数个 $1$ 但不全是 $1$，此时 $\&=0$，$\oplus=1$。
2. 有奇数个 $1$ 并且全部是 $1$，此时 $\&=1$，$\oplus=1$。
3. 有偶数个 $1$ 但不全是 $1$，此时 $\&=0$，$\oplus=0$。
4. 有偶数个 $1$ 并且全部是 $1$，此时 $\&=1$，$\oplus=0$。

那么当 $\&=\oplus$ 的情况即为：$C_n^0+C_n^2+\cdots+C_n^{num1}$，$num1$ 表示小于 $n$ 的最大偶数。特别地，如果 $n$ 是奇数，需再加上 $C_n^n$。（为了表示方便，将上述式子记为 $pre$）

当 $\&<\oplus$ 的情况即为：$C_n^1+C_n^3+\cdots+C_n^{num2}$，$num_2$ 表示小于 $n$ 的最大奇数。（为了表示方便，将上述式子记为 $tot$）

假设我们当前枚举到了第 $i$ 位，那么其实方案数就是：前 $(i-1)$ 位 $\&=\oplus$，第 $i$ 位 $\&<\oplus$，后 $(n-i)$ 为随便选情况相乘，即为：

$$pre^{i-1}\times tot\times 2^{n*(k-i)}$$

最后的答案用总答案数 $2^{n*k}$ 减去求得不符合要求情况即可。


**代码实现：[$\text{Code}$](https://codeforces.com/contest/1557/submission/125437385)**

---

## 作者：Presentation_Emitter (赞：3)

推式子题。

二进制运算首先拆位。对于一个二进制位，其对结果有影响且 Moamen 能获胜**当且仅当**该位上全为 $1$ 且 $n$ 为偶数。

对结果无影响的情况有两种：

- 该位上全为 $1$ 且 $n$ 为奇数。
- 该位上不全为 $1$ 且有偶数个 $1$。

显然需要按 $n$ 的奇偶性讨论。为方便描述，记 $c_i$ 表示第 $i$ 位 $1$ 的个数。

### $n$ 为奇数

原式的大于号显然不成立。

对于第 $i$ 位，有 $\frac{n-1}{2}+1$ 种 $c_i$。考虑每一个 $1$ 的位置，显然可以用组合数求解。每一位是独立的，所以每一位的贡献的 $k$ 次方即为答案。

$$Ans=(\sum\limits_{i=0}^{\frac{n-1}{2}}\begin{pmatrix}n \\ 2i\end{pmatrix}+1)^k$$

### $n$ 为偶数

这类情形有点麻烦。记 $f_i$ 表示计算到第 $i+1$ 位时的答案。考虑一个类似于递归的过程：

$$f_i=2^{ni}+\sum\limits_{j=0}^{\frac{n-2}{2}}\begin{pmatrix}n \\ 2j\end{pmatrix}f_{i-1}$$

边界 $f_{-1}=1$。

$2^{ni}$ 部分表示当 $i+1$ 位放满时，第 $1$ 到 $i$ 位的额外贡献。

然后这个式子显然可以递推求解。答案即为 $f_{k-1}$。

Code 很 naive，就不贴了。

---

~~给一位非OIer的朋友看这题，然后被他秒了。~~

上面的式子可以继续化简。

设 $a=\sum\limits_{i=0}^{\lfloor\frac{n}{2}\rfloor}\begin{pmatrix}n \\ 2i\end{pmatrix}$。根据某个结论，$a=2^{n-1}$。然后显然 $n$ 为奇数时答案为 $(a+1)^k$。

对于 $n$ 为偶数的情况，设 $t=\sum\limits_{i=0}^{\frac{n-2}{2}}\begin{pmatrix}n \\ 2i\end{pmatrix}=a-1$。

$$
\begin{aligned}
Ans&= f_{k-1}
\\&= t^k+\sum\limits_{i=0}^{k-1}t^i \cdot 2^{n(k-i-1)}
\\&= t^k+2^{n(k-1)} \cdot \sum\limits_{i=0}^{k-1}(\frac{t}{2^n})^i
\\&= t^k+2^{n(k-1)} \cdot \frac{1-(\frac{t}{2^n})^k}{1-\frac{t}{2^n}}
\\&= t^k+\frac{2^{nk}-t^k}{2^n-t}
\\&= t^k+\frac{2^{nk}-t^k}{t+2}
\end{aligned}$$

代码实现简单，就不贴了。

---

## 作者：Leasier (赞：2)

~~做了这道题我才知道——我不会数数，我甚至不配数数。~~

显然，我们并不关心数组中每个数的实际值，我们只关心 $\operatorname{and}$ 和 $\operatorname{xor}$ 运算后得到的值。设 $\operatorname{and}$ 得到的值为 $a$，$\operatorname{xor}$ 得到的值为 $b$。

设 $dp_{i, j}$ 表示从第 $0$ 位（这里指最高位）到第 $i$ 位构造原数组的方法数。若 $j = 0$，此时 $a = b$；否则，此时 $a > b$。

初始值：令 $x = \displaystyle\sum_{i = 0}^{\lfloor \frac{n - 1}{2} \rfloor} C_n^{2i}$，则 $dp_{0, 0} = x$，$dp_{0, 1} = [n \bmod 2 = 0]$。

答案：$dp_{k - 1, 0} + dp_{k - 1, 1}$。

转移：

1. 当 $j = 0 \operatorname{and} n \bmod 2 = 0$

显然必须要让这一位也相同，则 $dp_{i, j} = x dp_{i - 1, 0}$。

2. 当 $j = 0 \operatorname{and} n \bmod 2 = 1$

显然必须要让这一位也相同，但由于全选也合法，则 $dp_{i, j} = (x + 1) dp_{i - 1, 0}$。

3. 当 $j = 1 \operatorname{and} n \bmod 2 = 0$

- 你可以让之前的位已经满足 $a > b$，再随意安排这一位。
- 你可以让之前的位已经满足 $a = b$，再让这一位安排后满足 $a > b$。

则 $dp_{i, j} = 2^n dp_{i - 1, 1} + dp_{i - 1, 0}$。

4. 当 $j = 1 \operatorname{and} n \bmod 2 = 1$

手玩一下会发现此时没有合法情况，则 $dp_{i, j} = 0$。

预处理组合数后直接转移即可。注意需要特判 $k = 0$ 的情况。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 2e5 + 7, M = 1 + 7, mod = 1e9 + 7;
ll fac[N], inv_fac[N], dp[N][M];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(){
	fac[0] = 1;
	for (int i = 1; i < N; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[N - 1] = quick_pow(fac[N - 1], mod - 2, mod);
	for (int i = N - 2; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline ll comb(ll n, ll m, ll mod){
	if (m == 0) return 1;
	if (m > n) return 0;
	return fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

int main(){
	int t;
	scanf("%d", &t);
	init();
	for (int i = 1; i <= t; i++){
		int n, k;
		scanf("%d %d", &n, &k);
		if (k == 0){
			printf("1\n");
			continue;
		}
		ll x = 0, ans;
		for (int j = 0; j < n; j += 2){
			x = (x + comb(n, j, mod)) % mod;
		}
		if (n % 2 == 0){
			ll y = quick_pow(2, n, mod);
			dp[0][0] = x;
			dp[0][1] = 1;
			for (int j = 1; j < k; j++){
				dp[j][0] = dp[j - 1][0] * x % mod;
				dp[j][1] = (dp[j - 1][1] * y % mod + dp[j - 1][0]) % mod;
			}
		} else {
			dp[0][0] = x + 1;
			dp[0][1] = 0;
			for (int j = 1; j < k; j++){
				dp[j][0] = dp[j - 1][0] * (x + 1) % mod;
				dp[j][1] = 0;
			}
		}
		printf("%lld\n", (dp[k - 1][0] + dp[k - 1][1]) % mod);
	}
	return 0;
}
```

---

## 作者：AGentleCat (赞：1)

## 一道计数题
### 题意
给定 $n$ 和 $k$ ，问有多少个这样的数组，使得
$a_1$ $\&$ $a_2$ $\&$ $a_3$ $\&$ … $\&$ $a_n$ $\geq$ $a_1$ $\oplus$ $a_2$ $\oplus$ $a_3$ $\oplus$ … $\oplus$ $a_n$ 成立
。其中，$a_i$ $\leq$ $2^k$，$\&$ 表示按位与，$\oplus$ 表示按位异或。$n$ $\leq$ $10^6$，答案对 $1e9+7$ 取模。
### 分析
因为太菜了……所以只想到了个有点麻烦的计数思路。


涉及到二进制上的大小比较，有一个显而易见的字典序性质：大小关系只取决于最高不相同的位置。一旦最高位确定，低位即可任意取值。


根据这个性质就可以计数了。先考虑取大于号的情况。对于第 $i$ 位，如果这 $n$ 个数 $\&$ 起来为 $1$ 且 $\oplus$ 起来为 $0$，那么这 $n$ 个数一定都为 $1$（按位与的性质），且 $n$ 一定为偶数（异或性质），这时对答案的贡献如何计算呢？

我们将 $i$ 从最高位 $k-1$ 从高到低开始枚举，对于上面这种情况，我们假定枚举过的位按位与和异或答案都为 $0$，未枚举过的位就可以随便取。前面每一位二者都为 $0$ 当且仅当这 $n$ 个数的第 $i$ 个二进制位上有偶数个 $1$，剩余都是 $0$，且不全为 $1$，那么取法就可以表示为：

$C_n^0$ $+$ $C_n^2$ $+$ …… $+$ $C_n^{n-2} $ $=$ $2^{n-1}$ $-$ $1$

由于还有 $k-1-i$ 位，根据乘法原理，对答案贡献就是
$({2^{n-1}-1})$ $^{k-i-1}$。


同理计算后面的数，每一位都可以任选，有 $k$ 位，贡献就是 $2^{nk}$。

那么，这一位取大于号对答案的总贡献就是上面两式相乘。每一位累加到答案即可。

算完了大于号，再来算等于号，还是考虑第 $i$ 位，如果他们（$\&$ 和 $\oplus$ 的结果）都是 $1$，那么 $n$ 必为奇数，也就是说，只有 $n$  为奇数才会出现这种情况。如果他们都是 $0$，那么只需要这 $n$ 个数里有偶数个 $1$ 且不全为 $1$ 即可。与上面的方法同理，简单推导就能得出两者相等对答案的贡献为：


$\begin{cases}
{(2^{n-1}-1)}^k&\text{ n 为偶}\\
{(2^{n-1}+1)}^k&\text{ n 为奇}
\end{cases}$



最终答案就是上面两种情况相加。

### 代码

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int mod = 1e9+7;
const int maxn = 6e5;
typedef long long ll;
ll f[maxn];
ll n, k;

ll ksm(ll a, ll b){
    ll res = 1;
    while(b){
        if(b % 2)
            res = (res * a) % mod;
        b /= 2;
        a = (a * a) % mod;
    }
    return res % mod;
}

int main()
{
    f[0] = 1;
    for(int i = 1; i <= 500000; i++)
        f[i] = f[i-1] * 2ll % mod;
    int T;
    cin >> T;
    while(T--){
        cin >> n >> k;
        ll ans = 0;
        for(ll i = k-1; i >= 0; i--){
            if(n % 2 == 0) ans += ksm(2, n*i) * ksm(f[n-1]-1, k-1-i);
            ans %= mod;
        }
        if(n % 2 == 0) ans += ksm((f[n-1]-1)%mod, k);
        else ans += ksm((f[n-1]+1)%mod, k);
        ans %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}
```


---

## 作者：pomelo_nene (赞：1)

显然按位考虑。如果二进制上某一位不一样，而更高位上全部一样，那么根据这一位就可以确定谁更大。

先考虑如果相等怎么算。

如果 $n$ 是奇数，相同的方法是：

- 这一位是 $1$：$a$ 的所有数这一位全部都是 $1$；   
- 这一位是 $0$：$a$ 中这一位是 $1$ 的个数是偶数。

那么方案数为 $\sum_{i=0}^{\lfloor \frac{n}{2} \rfloor} \binom{n}{2i}+1$。

否则，如果相等，这一位显然只有可能是 $0$。方案数为 $\sum_{i=0}^{\frac{n}{2}} \binom{n}{2i}-1$。

考虑如何算大于。如果 $n$ 是奇数，如果这一位与起来结果为 $1$，异或起来结果也为 $1$，故不存在这样的情况；如果 $n$ 是偶数，只要这一位全是 $1$，就会大于。而更低位可以随便选，计算起来比较容易，套用上面的方法，将更低位的随便填的方案数乘起来就行了。

闲话，$\sum_{i=0}^{\lfloor \frac{n}{2} \rfloor} \binom{n}{2i}+1$ 应该等于 $2^{n-1}+1$，但是交上去 WA 了。如果知道哪里错了可以评论一下。

另外，这个样例水的一比。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
LL dp[200005];
LL QuickPow(LL x,LL p)
{
	LL ans=1,base=x;
	while(p)
	{
		if(p&1)	ans=(ans*base)%MOD;
		base=(base*base)%MOD;
		p>>=1;
	}
	return ans;
}
LL fac[400005],ifac[400005];
LL C(LL n,LL m)
{
	if(n<m)	return 0;
	return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;
}
LL T,n,k;
int main(){
	fac[0]=1;
	for(LL i=1;i<=200000;++i)	fac[i]=fac[i-1]*i%MOD;
	ifac[200000]=QuickPow(fac[200000],MOD-2);
	for(LL i=199999;~i;--i)	ifac[i]=ifac[i+1]*(i+1)%MOD;
	scanf("%lld",&T);
	while(T-->0)
	{
		scanf("%lld %lld",&n,&k);
		LL ans=0;
		if(n&1)
		{
			for(LL i=0;i<=n;i+=2)
				ans+=C(n,i),ans%=MOD;
			ans=QuickPow(ans+1,k);
		}
		else
		{
			for(LL i=0;i<=n;i+=2)	ans+=C(n,i),ans%=MOD;
			LL tmp=ans-1;
			ans=QuickPow(ans-1,k);
			for(LL i=1;i<=k;++i)	(ans+=QuickPow(tmp,i-1)*QuickPow(QuickPow(2,n),k-i))%=MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：registerGen (赞：1)

[这次比赛的题解](https://www.cnblogs.com/registergen/p/cf_round_737_solution.html)

约定这里的位是指二进制位，最低位是第 $0$ 位，最高位是第 $k-1$ 位。

按位考虑。我们枚举一个 $0\le i\le k-1$，那么满足要求当且仅当第 $i+1\sim k-1$ 位相同，第 $i$ 位与起来是 $1$，异或起来是 $0$，第 $0\sim i-1$ 位随便。当然还有一种情况是所有位都相同。

然后对于第 $i$ 位上的 $n$ 个数，我们考虑这样一个表：

|$1$ 的个数的奇偶性|是否有 $0$|$\land$|$\oplus$|
|:-:|:-:|:-:|:-:|
|奇|有|$0$|$1$|
|奇|无|$1$|$1$|
|偶|有|$0$|$0$|
|偶|无|$1$|$0$|

1. 当 $n$ 是奇数的时候，我们只能让所有位相同，因为根本无法让某一位上有偶数个 $1$ 且没有 $0$，此时根据上表可知，对于每一位，满足要求的方案数是 $1+\left(\binom n0+\binom n2+\binom n4+\cdots\right)=1+2^{n-1}$，又因为一共有 $k$ 位，所以最终的答案是 $(1+2^{n-1})^k$。
2. 当 $n$ 是偶数的时候，
	1. 若所有位相同，答案是 $\left(\binom n2+\binom n4+\cdots\right)^k=(2^{n-1}-1)^k$。
	2. 枚举一个 $i$，当第 $i+1\sim k-1$ 位相同，第 $i$ 位与起来是 $1$，异或起来是 $0$，第 $0\sim i-1$ 位随便时，对于第 $i+1\sim k-1$ 位，每一位有 $\binom n2+\binom n4+\cdots=2^{n-1}-1$ 种可能，第 $i$ 位只能全是 $1$，第 $0\sim i-1$ 位每一位有 $2^n$ 种可能，一共就有 $(2^{n-1}-1)^{k-i-1}(2^n)^i$ 种可能。

```cpp
typedef long long ll;

const int P=1e9+7;

inline int qpow(int a,int b,int p){
	int res=1;
	while(b){if(b&1)res=1LL*res*a%p;a=1LL*a*a%p;b>>=1;}
	return res;
}

void mian(){
	int n,k;
	scanf("%d%d",&n,&k);
	int ans=0;
	if(n%2==1)
		ans=qpow(qpow(2,n-1,P)+1,k,P);
	if(n%2==0){
		for(int i=0;i<k;i++)
			ans+=1LL*(qpow(qpow(2,n-1,P)-1,k-i-1,P))*qpow(qpow(2,n,P),i,P)%P,ans%=P;
		ans+=1LL*qpow(qpow(2,n-1,P)-1,k,P);
		ans%=P;
	}
	printf("%d\n",ans);
}
```

---

