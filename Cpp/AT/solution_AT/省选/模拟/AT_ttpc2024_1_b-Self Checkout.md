# Self Checkout

## 题目描述

给你一个由数字 1, 2, 3 组成且长度为 $N$ 的数列 $S$。请找出所有由数字 1 和 2 组成的数列 $A$，使通过一定的操作后，生成的数列 $T$ 等于 $S$。我们要计算这样的数列 $A$ 的个数，并对结果取 $998244353$ 的余数。可以证明，符合要求的数列 $A$ 的个数是有限的。

> 操作描述如下：
>
> 1. 初始化变量 $C = 0$。
> 2. 如果数列 $A$ 中存在数字 1，将最前面的一个 1 移除，并将 $C$ 加 1。
> 3. 如果此时 $A$ 仍然不为空，移除 $A$ 的第一个元素 $x$，并将 $C$ 加上 $x$ 的值。
> 4. 将 $C$ 添加到数列 $T$ 的末尾。
> 5. 如果此时 $A$ 为空，操作结束；否则，返回步骤 1。

## 说明/提示

- 所有输入均为整数。
- $1 \le N \le 10^6$
- $1 \le S_i \le 3$

### 样例解释 1

如果 $S = (3, 2)$，则满足条件的数列 $A$ 有 $(1, 2, 2)$, $(2, 1, 2)$, $(2, 2, 1)$, $(2, 1, 1, 1)$ 和 $(1, 2, 1, 1)$，共 5 种。例如，对于 $A = (2, 1, 1, 1)$：

- 移除 $A$ 中首个 $1$，此时 $A = (2, 1, 1)$，$C = 1$。
- 移除 $A$ 的第一个元素 2，此时 $A = (1, 1)$，$C = 3$。
- 把 $C$ 加入 $T$，得到 $T = (3)$。
- 再移除 $A$ 中首个 $1$，此时 $A = (1)$，$C = 1$。
- 移除 $A$ 的第一个元素 1，$A$ 变为空，$C = 2$。
- 将 $C$ 加入 $T$，得到 $T = (3, 2)$。

### 样例解释 3

也有可能没有符合条件的数列 $A$，这种情况结果为 0。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2
3 2```

### 输出

```
5```

## 样例 #2

### 输入

```
6
3 2 2 3 2 1```

### 输出

```
4```

## 样例 #3

### 输入

```
5
3 2 1 3 2```

### 输出

```
0```

# 题解

## 作者：Register_int (赞：1)

容易发现中间是不能出现 $1$ 的，因此 $1$ 只能出现在末尾，不会影响总方案数。只要考虑 $2$ 和 $3$ 的情况。大致以下几种情况：

#### 1. 一段全为 $3$ 的串的方案数。

设长度为 $n$。此时每个 $3$ 都由一个 $1$ 和一个 $2$ 组成。将这些 $1,2$ 任意重排，能全组成出 $3$ 当且仅当不存在一次操作操作到两个 $1$，也即第 $i$ 个 $1$ 前面至少有 $i-1$ 个 $2$。将 $1$ 视作向上走一格，$2$ 视作向右走一格，则方案数就是从 $(0,0)$ 走到 $(n,n)$ 且不碰到 $y=x+2$ 的方案数，反射容斥即可。

#### 2. 两端全为 $3$ 的串中间夹了个 $2$。

此时的 $2$ 必定为两个 $1$ 组成，相当于一个隔断。把两边方案数乘起来就好。

#### 3. 末尾有若干个连续的 $2$。

比较特殊，因为我们可以选一个全是 $2$ 的后缀，此时序列里没有 $1$ 了，因此 $2$ 可以直接用一个 $2$ 表示。把这一段和上一段 $3$ 合并计算即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;
const int mod = 998244353;

inline int add(int x, int y) { return x += y, x < mod ? x : x - mod; } 
inline int sub(int x, int y) { return x -= y, x < 0 ? x + mod : x; } 

inline 
int qpow(int b, int p) {
	int res = 1;
	for (; p; p >>= 1, b = (ll)b * b % mod) if (p & 1) res = (ll)res * b % mod;
	return res;
}

int fac[MAXN << 1], ifac[MAXN << 1];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = (ll)fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
}

inline 
int c(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

inline 
int way(int x, int y) {
	if (x < 0 || y < 0) return 0;
	return c(x + y, y);
}

inline 
int calc(int x, int y) {
	return sub(way(x, y), way(y - 2, x + 2));
}

int n, p, a[MAXN], x, ans = 1, sum;

int main() {
	scanf("%d", &n), init(n * 2);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if (a[n] != 2) {
		for (int i = 1; i < n; i++) {
			if (a[i] == 1) return puts("0"), 0;
			if (a[i] == 2) ans = (ll)ans * calc(x, x) % mod, x = 0;
			if (a[i] == 3) x++;
		}
		if (a[n] == 1) ans = (ll)ans * calc(x, x) % mod;
		if (a[n] == 3) x++, ans = (ll)ans * calc(x, x) % mod;
		return printf("%d", ans), 0;
	}
	for (p = 1; p <= n; p++) if (a[n - p] != 2) break;
	for (int i = 1; i <= n - p; i++) {
		if (a[i] == 1) return puts("0"), 0;
		if (a[i] == 2) ans = (ll)ans * calc(x, x) % mod, x = 0;
		if (a[i] == 3) x++;
	}
	ans = (ll)ans * add((ll)calc(x, x) * p % mod, calc(x + p, x)) % mod;
	printf("%d", ans);
}
```

---

## 作者：xyz105 (赞：1)

2025 年度个人首篇题解祭！

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.018 }\bold{AT\_ttpc2024\_1\_b}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$


### 题目描述

给定一个长为 $N$ 的序列 $S$，它仅由 $1,2,3$ 组成。试求出由 $1,2$ 组成的序列 $A$ 的个数，使得执行以下程序后得到的新序列 $T$ 与 $S$ 一致。答案模 $998244353$。$(1\le N\le 10^6)$
> **程序**
> 
> 将 $T$ 初始化为空序列，随后执行以下步骤：
> 1. 设置变量 $C=0$。
> 2. 如果 $A$ 中至少包含一个 $1$，则从 $A$ 中删除第一个出现的 $1$，并将 $C$ 加上 $1$。
> 3. 如果 $A$ 不为空，则删除 $A$ 中第一个元素 $x$，并将 $C$ 加上 $x$。
> 4. 将 $C$ 追加到 $T$ 的末尾。
> 5. 若 $A$ 不为空，返回步骤 $1$，否则停止程序。


### 解题思路

**组合数学**题。

首先有一个很**直接**的观察。在序列 $S$ 中，
- $3$ 必然是 $A$ 中的 $1$ 和 $2$ 组合得到的。
- $2$ 要么是被 $A$ 中的两个 $1$ 组合出，要么直接来源于 $A$ 中的 $2$。
- $1$ 只能来源于 $A$ 中的 $1$。

$1$ 是最**特殊**的，不妨先考虑它。结论为：若 $1$ 出现在 $S$ 中不是末尾的位置，则 $A$ 无解。  
证明显然，在执行程序时，你能给 $T$ 末尾追加 $1$ 当且仅当 $A$ 中只剩一个数字 $1$ 了，加了它程序就结束了，所以 $1$ 如果在 $S$ 中出现只能是末尾。  
特判掉无解情况后，你发现你把 $S$ 末尾的 $1$ 删了也不影响答案计数。所以 $1$ 真没用。

问题转化为 $S$ **只由** $2,3$ 组成的情况。其中 $3$ 是只有 $1+2$ 一种组合方式的，比较简单，不妨先考虑 $S$ 中全是 $3$ 的情况。

当 $S$ 中**全是** $3$ 时，$A$ 必然是由 $N$ 个 $1$ 和 $N$ 个 $2$ 组成的序列。这里引出另一个结论。
> 记 $cnt_{x,i}$ 为 $A_1,A_2,\ldots,A_i$ 中 $x$ 的出现次数。$A$ 能通过程序生成全是 $3$ 的 $S$，当且仅当 $\forall i\isin [1,N],\ cnt_{2,i}-cnt_{1,i}\ge -1$。
>
> 证明：当 $cnt_{2,i}-cnt_{1,i}\ge -1$ 不成立，也就是说当 $cnt_{1,i}-cnt_{2,i}\ge 2$ 成立时，在最好情况下 $A_1\sim A_i$ 中所有的 $2$ 都能与某一个 $1$ 组合，最终也会剩下至少两个 $1$ 自组成 $2$，与 $S$ 中全是 $3$ 矛盾。

这样一来，咱们就可以把这个问题往**格路计数**的方向去想了。将 $A$ 中数字 $2$ 看成 $\nearrow$ 箭头，数字 $1$ 看成 $\searrow$ 箭头，假设从平面上 $(0,0)$ 出发走到 $(2N, 0)$，那么只要保证不越过 $y=-1$ 这条线就可以了，如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/yimww5uu.png)

这个是经典问题，定义 $f(n,m)$ 表示 $n$ 个 $\nearrow$ 箭头和 $m$ 个 $\searrow$ 箭头所组合路径从 $(0,0)$ 出发不越过 $y=-1$ 这条线的方案数，那么有 $f(n,m)=\dbinom{n+m}{n}-\dbinom{n+m}{n-2}$。只要对**反射容斥**有一点了解就可以推出该公式。

于是 $S$ 中全是 $3$ 的情况就做完了，等于 $f(N,N)$。

现在考虑 $S$ 中有出现 $2$ 的情况。下面这段话可能有点绕，请耐着性子看完。  
如果 $S$ 中某个 $2$ **后面有** $3$，那么这个 $2$ 只能是由 $A$ 中**连续两个** $1$ 组合而来，而非 $A$ 中单独的 $2$（否则这个 $A$ 中单独的 $2$ 会和后面的 $1$ 组成 $3$）。并且在 $S$ 中的这个 $2$ 前面的 $3$（如果有的话）在组合时用到的 $A$ 中的 $1$ 的位置显然也在“组合这个 $2$ 时用到的两个 $1$ 的位置”的前面。  
所以，这个 $2$ 对答案没有影响（只有 $1+1$ 一种组合方式）；将所有 $3$ 连续段按上述“$S$ 中全是 $3$”的讨论分别计算答案（若 $3$ 连续段的长为 $L$ 则答案为 $f(L,L)$），再用**乘法原理**乘起来即可。

但事情没那么简单，因为还没考虑 $2$ **后面没有** $3$ 的情况，要对最后一个 $3$ 连续段特判。也就是说 $S$ 可能长这样：$S=[\ldots,\underbrace{3,3,\ldots,3}_{L\text{ 个}},\underbrace{2,2,\ldots,2}_{X\text{ 个}}]$。

这末尾 $X$ 个 $2$ 的生成方式必然为：前 $Y$ 个 $2$ 是 $A$ 中“$1+1$”得到的，后 $X-Y$ 个 $2$ 是由 $A$ 中单独的 $2$ 得到的。若 $2$ 在 $1+1$ 前面，则这个 $2$ 会先和后面某个 $1$ 生成 $3$ 了。

当 $Y=0$ 时，$3$ 连续段的结果要和 $2$ 连续段混杂在一起计算，结果是 $f(L+X,L)$。  
当 $0<Y\le X$ 时，“$1+1$”把 $3$ 连续段 和 后 $X-Y$ 个 $2$ 隔开了，结果是 $f(L,L)$。

总结果为 $f(L+X,L)+X\times f(L,L)$，将其乘进答案即可。

特判掉 $S$ 中全为 $2$ 的情况（答案为 $N+1$）。总时间复杂度 $O(N)$。


### 参考代码

[Submission on AtCoder](https://atcoder.jp/contests/ttpc2024_2/submissions/61289242)。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

const int MAXN = 2e6 + 10;

int n, a[MAXN];

ll fac[MAXN], ifac[MAXN];

inline ll pow_(ll a, ll b, ll p)
{
	ll res = 1;
	for (; b; b >>= 1, a = a * a % p) if (b & 1) res = res * a % p;
	return res;
}

inline ll inv(ll x) {return pow_(x, MOD - 2, MOD);}

inline ll C(ll n, ll m)
	{return (n < 0 || m < 0 || m > n) ? 0 : fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;}

inline ll calc(ll x, ll y)
	{return C(x + y, x) + MOD - C(x + y, x - 2);}

int main()
{
	fac[0] = ifac[0] = 1;
	for (int i = 1; i < MAXN; i++) fac[i] = fac[i - 1] * i % MOD;
	ifac[MAXN - 1] = inv(fac[MAXN - 1]);
	for (int i = MAXN - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	
	ll suf2 = n + 1, ans = 1;
	for (int i = n; i && a[i] == 2; i--) suf2 = i;
	
	if (suf2 == 1) return cout << n + 1, 0;
	
	for (int i = 1; i < n; i++) if (a[i] == 1) return cout << 0, 0;
	if (a[n] == 1)
	{
		n--; if (!n) return cout << 1, 0;
		suf2 = n + 1;
	}
	
	for (int i = 1, i1 = 0; i <= suf2; i++)
	{
		if (i == suf2 || a[i] != 3)
		{
			if (!i1) continue;
			if (i == suf2 && suf2 <= n)
				ans = ans * ((calc(i1, i1 + n + 1 - suf2) + calc(i1, i1) * (n + 1 - suf2)) % MOD) % MOD;
			else
				ans = ans * calc(i1, i1) % MOD;
			i1 = 0;
		}
		else i1++;
	}
	cout << ans;
	
	return 0;
}
```


### 后记

![](https://cdn.luogu.com.cn/upload/image_hosting/0j9tdu8u.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/odps3fjo.png)

矩阵群竟然这么细致，orz。

---

