# [入门赛 #9] 最澄澈的空与海 (Hard Version)

## 题目背景

材料 1：

> 请小心地计算下面的算式：$138 - 108 \div 6 = ?$  
> 你大概难以置信，这个算式的计算结果竟然是 $5!$

材料 2：

> 对于一个正整数 $x$，$x! = 1 \times 2 \times \cdots \times (x - 1) \times x$。我们称 $x!$ 为 $x$ 的阶乘。  
> 特别的，$0! = 1$。

显然，「$138 - 108 \div 6 = 5$」是错误的，而「$(138 - 108) \div 6 = 5$」是正确的，所以对材料 1 中的内容，部分读者会认为「作者没有搞清加减乘除的运算优先级关系而犯错」。

然而，材料 1 最后一行的叹号并不是标点符号，而是材料 2 提到的「阶乘」。

考虑到这一点，「$138 - 108 \div 6 = 5! = 1 \times 2 \times \cdots \times 5 = 120$」显然就是正确的了。

## 题目描述

然而，此题可能与上面的题目背景关系不是很大。

我们会给你 $T$ 组数据，每组数据包括一个正整数 $n$。

对于每组数据，请你帮助求出满足以下条件的整数三元组 $(x, y, z)$ 的组数：

1. $x \geq 0$，$z \geq 1$。
2. $x - y \div z = n!$ 且 $(x - y) \div z = \dfrac{n!}{n}$。

由于答案可能过大，因此你需要输出答案对 $998244353$ 取模后的结果。

不难注意到答案有可能为 $\infty$，这时请按照「输出格式」要求进行处理。

**请注意此处应满足 $(x - y) \div z = \dfrac{n!}{n}$ 而不是 $= n$。**

请注意这里的 $\div$ 不是向下取整的整除，这显然意味着你需要保证 $y \div z$ 和 $(x - y) \div z$ 为整数。

## 说明/提示

### 样例 1 解释

样例中的具体三元组如下：

| $n$ | 所有可能的三元组 |
| :----------: | :----------: |
| $2$ | $(2, 0, 2)$ |
| $3$ | $\begin{matrix}(8, 4, 2) & (5, -5, 5) & (6, 0, 3)\end{matrix}$ |
| $4$ | $\begin{matrix}(19, -95, 19) & (21, -21, 7) & (24, 0, 4) \\ (27, 9, 3) & (20, -40, 10) & (36, 24, 2)\end{matrix}$ |

### 数据规模与约定

对于前 $20\%$ 的数据，保证 $T \leq 10$，$n \leq 10$。

对于前 $40\%$ 的数据，保证 $n \leq 10 ^ 3$。

对于另外 $20\%$ 的数据，保证 $T = 1$。

对于 $100\%$ 的数据，保证 $1 \leq T \leq 10 ^ 5$，$1 \leq n \leq 10 ^ 6$。

## 样例 #1

### 输入

```
3
2
3
4```

### 输出

```
1
3
6```

# 题解

## 作者：Maxmilite (赞：10)

## Source & Knowledge

2023 年 2 月语言月赛，由洛谷网校入门计划/基础计划提供。

## 文字题解

### 题目大意

多测，$T$ 组数据。每次给定一个正整数 $n$，求满足 $x \geq 0$，$z \geq 1$，$x - y \div z = n!$ 且 $(x - y) \div z = \dfrac{n!}{n}$ 的整数三元组 $(x, y, z)$ 的数量。$1 \leq T \leq 10 ^ 5$，$1 \leq n \leq 10 ^ 6$。

### 解析

本题做法可能有很多种，这里提供一种做法。

---

以下先给出两个引理，方便解释后面的做法。

引理 1：对于一个满足条件的整数三元组 $(x, y, z)$，通过 $z$ 可以确定唯一的 $x, y$ 与之对应。

证明：

> 因为整数三元组 $(x, y, z)$ 满足上述条件，所以 $(x - \dfrac yz) - (\dfrac{x - y}{z}) = n! - \dfrac{n!}n$，即 $x \times \dfrac{z - 1}{z} = (n - 1)! \times (n - 1)$。
>
> 即 $x = (n - 1)! \times (n - 1) \times \dfrac{z}{z - 1}$。
> 
> 显然，接下来 $y = x - z \times (n - 1)!$。
>
> 证毕。  

引理 2：在 $z \geq 2$ 的情况下，一个整数三元组 $(x, y, z)$ 满足上述条件的充要条件为 $z - 1$ 是 $(n - 1)! \times (n - 1)$ 的因数。

证明：

> 由引理 1，当 $z \geq 2$ 时，$x = (n - 1)! \times (n - 1) \times \dfrac{z}{z - 1}$，$y = x - z \times (n - 1)!$。此时由于 $(n - 1)! > 0$，$n - 1 \geq 0$，$z - 1 \geq 1$，那么我们就可以保证 $x \geq 0$。如果此时 $x, y$ 都是整数，那么这个整数三元组就符合题面要求的所有约束。
> 
> 考虑如何保证 $x, y$ 都是整数。不难发现如果 $x$ 是整数，$y$ 则一定是整数。因此考虑 $x$ 的问题。
> 
> 注意到导致 $x$ 不是整数的唯一因素是分母 $z - 1$。因此如果想让 $x$ 是整数，只要保证 $(n - 1)! \times (n - 1) \times {z}$ 可以整除 $z - 1$ 即可。
> 
> 又 $\gcd(z, z - 1) = 1$（易证，如果 $k$ 是 $z$ 和 $z - 1$ 的因数，那么 $k$ 就是 $z - z + 1 = 1$ 的因数，所以 $k$ 只能是 $1$），所以如果 $(n - 1)! \times (n - 1) \times {z}$ 可以整除 $z - 1$，则只可能为 $z - 1$ 是 $(n - 1)! \times (n - 1)$ 的因数。
> 
> 对充分性，如果 $z - 1$ 是 $(n - 1)! \times (n - 1)$ 的因数，那么 $x = (n - 1)! \times (n - 1) \times \dfrac{z}{z - 1}$ 就是非负整数，$y$ 同样也是整数。且由引理 1，如果三元组合法，那么当 $z$ 确定时，对应的 $x, y$ 是唯一的。因此一个整数三元组 $(x, y, z)$ 可以满足上述条件。
>
> 证毕。

由上面的引理，我们可以发现，对于每个 $(n - 1)! \times (n - 1)$ 的因数 $p$，我们都可以令 $z = p + 1$ 构造出**唯一**的整数三元组 $(x, y, z)$ 满足题目给出的条件。同时，由引理 $2$，可以得出如果 $z - 1$ 不是 $(n - 1)! \times (n - 1)$ 的因数，则一定不能够构造出满足条件的整数三元组。

因此，满足条件的整数三元组的数量，就是 $(n - 1)! \times (n - 1)$ 的因数数量。考虑如何求 $(n - 1)! \times (n - 1)$ 的因数数量。

根据[唯一分解定理](https://oi.wiki/math/number-theory/basic/#算术基本定理)和[约数个数定理](https://oi.wiki/math/number-theory/sieve/#筛法求约数个数)，我们可以将问题转化为求解 $(n - 1)! \times (n - 1)$ 的质因数及每个质因数的数量。

---

首先考虑单组数据的做法。定义一个整数数组 $f$。其中 $f _ i$ 代表「从 $2$ 开始数的第 $i$ 个质数」作为质因数在 $(n - 1)! \times (n - 1)$ 中出现的次数。将 $i$ 从 $1$ 枚举至 $n - 1$，对于每一个 $i$，将其进行质因数分解。设分解后的结果为 $i = p _ 1 ^ {e _ 1} p _ 2 ^ {e _ 2} \cdots p _ k ^ {e _ k}$，对每个 $p _ j$，让 $f$ 中对应的位置增加 $e _ j$。最后将 $n - 1$ 单独多进行一次这个过程。

上述过程完成后，设 $\leq n$ 的质数为 $cnt$ 个，我们计算出 $(1 + f _ 1) \times (1 + f _ 2) \times \cdots \times (1 + f _ {cnt})$ 取模即可作为答案。

对于上述的整套流程，时间上的瓶颈在质因数分解部分。考虑优化质因数分解过程。

考虑线性筛质数的原理。线性筛质数过程中，每个合数都只被标记一次。在这唯一一次标记的过程中，这个合数是被其最小的质因数标记的。在标记的同时，我们考虑记录下这个最小的质因数。

我们使用 $p$ 数组记录线性筛质数过程，$p _ i$ 代表 $i$ 的最小的质因数。这样做的好处是，在进行质因数分解的过程中，我们可以直接找到对应整数的最小质因数直接进行分拆，而不需要从头遍历质数表逐一匹配。不难发现，我们可以在 $\mathcal{O} (\log n)$ 的时间复杂度内完成对 $n$ 的质因数分解。

我们首先进行一次线性筛质数，同时记录下 $p$ 数组。线性筛完成后，进行「将 $i$ 从 $1$ 枚举至 $n - 1$，对于每一个 $i$，将其进行质因数分解」的过程。这样对于单次询问，最终的总时间复杂度为 $\mathcal{O} (n \log n)$。

然而多测的总时间复杂度为 $\mathcal{O} (Tn \log n)$，按照上述方法只能拿到 $60\%$ 的分数。考虑如何优化的多测的过程。

不难发现我们对 $(n - 1)!$ 的质因数及个数进行了多次重复的运算，这是非常耗时的！考虑如何优化这个过程。

如果只是询问 $(n - 1)!$ 的因数数量，我们显然可以进行递推。使用 $h$ 数组记录答案，将 $i$ 从 $1$ 枚举至 $n - 1$，对于每一个 $i$，将其进行质因数分解，每次分解并操作完 $f$ 数组后，计算 $(1 + f _ 1) \times (1 + f _ 2) \times \cdots \times (1 + f _ {cnt})$ 并取模存入 $h _ i$ 中即可。瓶颈转化为了计算 $(1 + f _ 1) \times (1 + f _ 2) \times \cdots \times (1 + f _ {cnt})$。

考虑使用一个变量 $ans$ 记录当前的 $(1 + f _ 1) \times (1 + f _ 2) \times \cdots \times (1 + f _ {cnt})$。在对 $i$ 筛质因数的过程中，我们每筛出一个质因数及对应的数量（设这个质因数为第 $x$ 个质数，出现 $y$ 次），就将 $ans$ 先除以 $1 + f _ {x}$，再乘 $1 + f _ {x} + y$，再让 $f _ x$ 增加 $y$。最后将 $ans$ 存入 $h _ i$ 即可。

由于 $ans$ 需要取模，因此上述的除法转换为乘逆元即可。这样，如果使用线性预处理逆元，我们即可在 $\mathcal{O} (\log n)$ 的时间内完成对 $n$ 的质因数分解和答案 $ans$ 的更新。最终便可 $\mathcal{O} (n \log n)$ 预处理，$\mathcal{O}(1)$ 回答。实际上不使用线性求逆元也可以在时限一半以内通过本题。

但是本题在 $(n - 1)!$ 外还有一个 $(n - 1)$，考虑处理这个 $(n - 1)$。我们在上面的过程中提到了增添一个 $(n - 1)$ 对答案的处理（将 $ans$ 先除后乘，修改 $f$ 数组，将 $ans$ 存入 $h$ 答案数组），这里，我们考虑对单独的 $(n - 1)$ **先增添后撤销**。具体的，设 $n - 1$ 的某个质因数为第 $x$ 个质数，出现 $y$ 次，先「对所有的质因数，将 $ans$ 先除以 $1 + f _ {x}$，再乘 $1 + f _ {x} + y$，再让 $f _ x$ 增加 $y$。最后将 $ans$ 存入 $h _ i$」，**答案记录完成后**再「对所有的质因数，将 $ans$ 先除以 $1 + f _ x$，**再乘 $1 + f _ {x} - y$**，让 $f _ x$ **减少** $y$。**不**将 $ans$ 存入 $h _ i$」即可。

这样我们即可在 $\mathcal{O}(n \log n)$ 的时间内完成所有的预处理工作，之后 $\mathcal{O} (1)$ 回答即可。总时间复杂度 $\mathcal{O}(n \log n + T)$。

---

最后有一个特殊情况需要处理。对于引理 2，我们只证明了 $z \geq 2$ 的情况。为什么没有证明 $z = 1$ 呢？显然是因为此时分母是 $z - 1=  0$。

那如果我非要让 $z = 1$ 呢？令 $z = 1$，我们会得到这样的一组式子：

$$\begin{cases} x - y = n! \\ x - y = (n - 1)! \end{cases}$$

会得到 $n! = (n - 1)!$，这个式子成立当且仅当 $n = 1$。此时 $n! = (n - 1)! = 1$。

所以，当 $n = 1$ 时，我们让 $z = 1$，只需让 $x - y = 1$，三元组 $(x, y, z)$ 就是符合要求的。显然这样的三元组有无数个。

所以当且仅当 $n = 1$，输出一行 `inf`。

### 代码

标答代码写的很丑陋（诸如没有采用线性求逆元），洛谷上开启 O2 后单个点在 700ms 左右通过，所以考虑后时限设置为两秒。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define lint long long
#define rep(_, __, ___) for (int _ = __; _ <= ___; ++_)

const int maxn = 1e6 + 5;
const int modint = 998244353;
using pii = pair<int, int>;

namespace FactorSieve {

	int prime[maxn];
	int ans[maxn];
	int p[maxn];
	int cnt;
	int f[maxn];

	lint fpow(lint x, lint y) {
		lint ans = 1;
		while (y) {
			if (y & 1) {
				ans = (ans * x) % modint;
			}
			x = (x * x) % modint;
			y >>= 1;
		}
		return ans;
	}

	lint finv(lint x) {
		return fpow(x, modint - 2);
	}

	pii v[maxn];
	int vcnt = 0;

	void init() {
		for (int i = 2; i <= 1000000; i++) {
			if (!p[i]) {
				p[i] = i, prime[++cnt] = i;
			}
			for (int j = 1; j <= cnt && i * prime[j] <= 1000000; j++) {
				p[i * prime[j]] = prime[j];
				if (p[i] == prime[j])
					break;
			}
		}

		lint cur = ans[0] = 1;

		for (int i = 1; i <= 1000000; ++i) {
			vcnt = 0;
			lint var = i;
			while (var != 1) {
				int cnt = 0, cur = p[var];
				while (var % cur == 0)
					var /= cur, ++cnt;
				v[++vcnt] = make_pair(cur, cnt);
			}
			for (int k = 1; k <= vcnt; ++k) {
				pii j = v[k];
				cur *= finv(1 + f[j.first]);
				cur %= modint;
				f[j.first] += j.second * 2;
				cur *= 1 + f[j.first];
				cur %= modint;
			}
			ans[i] = cur;
			for (int k = 1; k <= vcnt; ++k) {
				pii j = v[k];
				cur *= finv(1 + f[j.first]);
				cur %= modint;
				f[j.first] -= j.second;
				cur *= 1 + f[j.first];
				cur %= modint;
			}
		}
	}

	int query(int x) {
		return ans[x];
	}
};

int main() {
	FactorSieve::init();
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		if (n == 1)
			printf("inf\n");
		else
			printf("%d\n", FactorSieve::query(n - 1));
	}
	return 0;
}
```



---

## 作者：2huk (赞：5)

## 题目描述

多测，给定 $n$ ，求出满足以下条件的整数三元组 $(x, y, z)$ 的组数（答案对 $998244353$ 取模）。

- $x \ge 0,\ y \ge 1$
- $z \mid y,\ z \mid (x-y)$
- $x - \dfrac yz = n!$
- $\dfrac{x - y}z = \dfrac{n!}n$

若答案为 $\infty$，输出 `inf`。

## 数据范围

$1 \le T,\ 1 \le n \le 10^6$

## 分析

对于 $x - \dfrac yz = n!$ 和 $\dfrac{x - y}z = \dfrac{n!}n$ 这两个式子，首先将它们变形分析。

将两式相减，得到：

$$
x - \dfrac yz - \dfrac{x - y}z = n! - \dfrac{n!}n
$$

分别将等式两边化简，得到：

$$
x - \dfrac xz = n! - (n - 1)!
$$

此时我们发现 $y$ 消失了。继续变形，得到：

$$
\dfrac{zx - x}z = (n-1) \times (n-1)!
$$

然后把 $x$ 单独提到等式左边，得到：

$$
x = \dfrac{(n - 1) \times (n - 1)! \times z}{z - 1}
$$

得到这个式子，就不继续变形了。

题目要求 $x$ 为整数，所以 $(n - 1) \times (n - 1)! \times z$ 就一定是 $z - 1$ 的倍数。

由于 $z$  一定不是 $z-1$ 的倍数（不考虑 $z = 2$ 的情况），所以 $(n - 1) \times (n - 1)!$ 就一定是 $z - 1$ 的倍数。

而满足这样条件的 $z - 1$ 的数量有多少呢？显然它的数量就是 $(n - 1) \times (n - 1)!$ 的约数个数。

至此，我们得到了一个明确的解题思路，答案为 $(n - 1) \times (n - 1)!$ 的约数个数。

## 约数个数

求一个数 $x$ 的约数个数，方法如下。

首先将 $x$ 分解质因数，得到：$x = p_1^{\alpha_1} \times p_2^{\alpha_2} \times \cdots \times p_k^{\alpha_k}$。

那么 $x$ 的约数个数为 $\prod_{i = 1}^k (\alpha_i + 1)$。

如果我们对于每组测试数据都这样计算，首先分解质因数的时间复杂度为 $\Theta(\sqrt{(n - 1) \times (n - 1)!})$，那么总时间复杂度为 $\Theta(T \times\sqrt{(n - 1) \times (n - 1)!})$。首先 $10^6!$ 没法算出来，其次这个时间复杂度太庞大了。

由于 $n$ 最大到 $10^6$，所以我们可以预处理出所有 $(n-1)\times (n-1)!,\ i \in [1, 10^6]$ 的约数个数，接下来只需要查表即可。

对于递推式，我们来分析。

首先我们定义 $ans_i$ 表示 $i \times i!$ 的约数个数， $f_i$ 表示当前 $i$ 约数出现的次数。那么最终答案就是 $ans_{n - 1}$。

对于 $ans_i$ 的求解，首先要把 $f_i$ 求解出来。根据 $f_i$ 的定义，我们可以先把当前数 $i$ 进行质因数分解，存储到 `v` 中。

```cpp
void get_prime(int n)		// 求合数的最小质因子 mn[i] 
{
	for (int i = 2; i <= n; i ++ )
	{
		if (!mn[i]) p[ ++ cnt] = i, mn[i] = i;
		for (int j = 1; p[j] <= n / i; j ++ )
		{
			mn[i * p[j]] = p[j];
			if (i % p[j] == 0) break;
		}
	}
}

int tmp = i, cnt = 0;
while (tmp != 1)
{
	int x = mn[tmp], num = 0;
	while (tmp % x == 0) num ++, tmp /= x;
	v[ ++ cnt] = {x, num};
}
```

如果我们要从 $(i-1) \times (i-1)!$ 转移到 $i \times i!$ ，那么相当于是 $(i - 1) \times (i - 1)!\div (i-1) \times n^2$。对于 $ans_i$ 来说，首先对于之前所有 旧的 $f_i$ 的贡献移除，也就是 $\div (f_{i} + 1)$，然后再更新新的 $f_i$，并把新一轮也就是 $n^2$ 的贡献加上，也就是 $\times (f_i + 1) \times 2$，这里的 $\times 2$ 是因为 $n^2 = n \times n$，也就是会一次贡献两次。

```cpp
// 加上 n^2 的贡献 
for (auto j : v)
{
	int x = j.x, num = j.num;
	ret = mul(ret, inv(f[x] + 1));
	f[x] += num * 2;
	ret = mul(ret, f[x] + 1);
}

ans[i] = ret;		// 更新答案 

// 由于在下一步时需要减去 (i - 1) 的贡献，所以这里提前为下一步做处理 
for (auto j : v)
{
	int x = j.x, num = j.num;
	ret = mul(ret, inv(f[x] + 1));
	f[x] -= num;
	ret = mul(ret, f[x] + 1);
}
```

## 代码

[Code](https://www.luogu.com.cn/paste/7mmgmb25)

---

## 作者：__ryp__ (赞：3)

题解里头似乎没有离线的做法。实际上，用离线来做，不仅更快，而且更好写。

---

题意即求

$$
\begin{cases}
x-\dfrac yz = n!\\
\dfrac {x-y} z = (n-1)! \\
x\ge 0, z \ge 1
\end{cases}
$$

的 $(x, y, z)$ 数量。

前两式相减，消去 $\dfrac y z$，得到

$$
\dfrac {x(z-1)}z = (n-1)!(n-1)
$$

当 $z = 1$ 时，代入原式发现 $n! = (n-1)!$，即 $n = 1$，于是 $n = 1$ 时有无数解。

当 $z \gt 1$ 时，

$$
x  = (n-1)!(n-1) \dfrac z{z-1}
$$

于是 $z - 1$ 是 $(n-1)!(n-1)$ 的因子。由于这个条件是充要的，所以原方程的解数就是右式的因子数。

显然这玩意儿没法直接算。但我们知道，一个数的因子数，就是它唯一分解后质因子指数的任意组合，也即 $\prod (\alpha_i+1)$。

于是现在的问题，就转化为怎么快速做出 $T$ 个 $n$ 的 $(n - 1)!(n-1)$ 的每个质因子的指数。

---

对于单个 $n$，我们可以枚举 $i$ 从 $2$ 到 $n - 1$，动态维护一个答案 $p$，表示从 $1$ 到 $i - 1$ 的 $\prod (\alpha_i + 1)$。显然的，我们分解出 $i$ 后，它对于 $p$ 的贡献是 $\dfrac {\alpha'_i+\alpha_i+1}{\alpha'_i+1}$（其中 $\alpha'_i$ 表示前 $i - 1$ 个数分解出来的这一位上的指数）。由于是模意义，除法改用逆元。

但本题单单是根号分解就已经过不去了。

可以考虑线性筛筛出每个数的最小质因子，然后从最小质因子开始做分解；于是，复杂度从根号降到对数。

这样，我们就知道了怎么在 $O(n\log n)$ 时间内算出一个 $n$ 的答案。

---

下面考虑对于 $T$ 个 $n$，怎么快速进行计算。

非常显然地，对于 $n \le m$，那么对 $n$ 进行的计算，是被包含在对 $m$ 进行的计算中的。也就是说，如果我们暴力按刚才的方法，以 $O(Tn\log n)$ 时间来算，实际上会进行许多无用功。

于是我们可以考虑离线，然后排序，这样就可以消除无用的计算。维护一个 $u$ 表示下一个要分解的数，于是就可以 $n + T\log n$ 计算出所有询问的答案。

代码实现很简单。

```c++
#include <iostream>
#include <algorithm>
#include <bitset>
#define fi first
#define se second
#define int long long
using namespace std;
using pi = pair<int, int>;
const int N = 1e6 + 10, P = 998244353;
int mn[N], primes[N], res[N], s[N], inv[N], nr = 0;
pi z[N];

// 线性筛求最小质因子
void sieve (int n)
{
	for (int i = 2; i <= n; i++) {
		if (!mn[i]) ++nr, mn[primes[nr] = i] = nr;
		for (int j = 1; primes[j] * i <= n; j++) {
			mn[i * primes[j]] = j;
			if (i % primes[j] == 0) break;
		}
	}
}

signed main (void)
{
	int m;
	
	cin.tie (0)->sync_with_stdio (false);
	// 离线并开筛
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> z[i].fi, --z[i].fi, z[i].se = i;
	sort (z + 1, z + m + 1), sieve (z[m].fi);
	
	// 线性预处理逆元
	inv[1] = 1;
	for (int i = 2; i <= z[m].fi; i++) inv[i] = (P - P / i) * inv[P % i] % P;
	
	int i = 1, ans = 1;
	
	// 特判无解情况
	while (!z[i].fi && i <= m) res[z[i++].se] = -1;
	for (int u = 2; i <= m; i++) {
		// 筛掉 (n - 1)! 中的质因子，并动态维护 ans
		for (; u <= z[i].fi; u++) {
			int v = u;
			while (v > 1) {
				int w = mn[v], cnt = 0;
				while (v % primes[w] == 0) v /= primes[w], cnt++;
				ans = ans * inv[s[w] + 1] % P * (s[w] + cnt + 1) % P, s[w] += cnt;
			}
		}
		
		// 筛 (n - 1) 项，更新到当前询问的 ans 上
		int prod = ans, val = z[i].fi;
		while (val > 1) {
			int w = mn[val], cnt = 0;
			while (val % primes[w] == 0) val /= primes[w], cnt++;
			prod = prod * inv[s[w] + 1] % P * (s[w] + cnt + 1) % P;
		}
		res[z[i].se] = prod;
	}
	
	for (int i = 1; i <= m; i++)
		if (res[i] == -1) cout << "inf\n";
		else cout << res[i] << '\n';
	return 0;
}
```

---

## 作者：Empty_Dream (赞：2)

# P9007 解题报告

## 分析

首先看到那几个方程很不优雅，考虑先解一下这个东西。

方程一：
$$
x - \frac{y}{z} = n! \\
x\cdot z - y =z\cdot n!
$$
方程二：
$$
\frac{(x-y)}{z}=\frac{n!}{n}=(n-1)! \\
x-y=z\cdot(n-1)!
$$
用方程一减去方程二得出：
$$
x\cdot z-y-x+y=z\cdot n! - z\cdot (n-1)! \\
(z-1)\cdot x=z\cdot(n-1)!(n-1)\\
x=\frac{z\cdot(n-1)!(n-1)}{z-1}
$$
题目要求 $x$ 为正数，所以右边也为正数。易知 $z$ 与 $z-1$ 互质，所以 $z-1\mid(n-1)(n-1)!$。现在我们的 $z-1$ 的方案数就很明显了，也就是 $(n-1)(n-1)!$ 的因数个数，但这东西显然不可能在短时间内求出来，所以考虑预处理。

我们从一般形式开始推，也就是 $x = p_1^{\alpha_1} \times p_2^{\alpha_2} \times \cdots \times p_k^{\alpha_k}$，它的因数个数是 $(\alpha_1 + 1) \times (\alpha_2+1)\times \cdots \times(\alpha_k+1)$。如果现在乘上一个数  $y$，那么显然就是把 $y$ 中对应因数的个数加到上式中算贡献。具体的，~~可以类似莫队移动区间那样~~，先除掉原来的 $(\alpha_i+1)$ 再乘上更新过的 $(\alpha_i+1)$。

而我们所预处理的应该是 $i$ 从 $1$ 到 $1\times10^6$ 中每个数的因数个数，那就可以递推了，直接从 $i-1$ 推到 $i$。而有了上面的理论基础，可以直接维护 $(i-1)!$ 的因数个数，乘上 $i$ 就变成了 $i!$ 的贡献，也就是将 $i$ 加入 $(i-1)!$ 中计算贡献。

但是我们处理因数的复杂度是 $O(\sqrt{n})$ 的还是会爆掉，这是后我们加一点小技巧，考虑线性筛的思路，把每一个合数只用它最小的质因数筛出来，分解也可以一样，每个数 $x$ 只按它最小的质因数先除掉，递归进行，直到 $x=1$，这样就可以保证在 $O(\log n)$ 的复杂度分解每一个数。

注意细节：我们目标是 $i\times i!$ 的贡献，也就是要加上双倍的 $i$ 的贡献，但我们维护的只是包含 $i!$ 的贡献，所以加上之后还要减去一倍的贡献（~~其实有点偷~~懒）；还有，需要使用逆元。

最后的最后，判无解，显然 $n=1$ 时 $z$ 可以取任意值。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
#define fir first
#define sec second
#define memset(a, b) memset(a, b, sizeof(a));
using namespace std;

const int mod = 998244353;
const int N = 1e6 + 5;
int T, n, res = 1;
int pri[N], vis[N], inv[N], fac[N], ans[N], cnt[N];
vector<int> v;

void update(int x, int y){
    while (x > 1){//更新每一个因数的贡献
        int tmp = pri[x];//某种小技巧
        res = res * inv[cnt[tmp] + 1] % mod;
        cnt[tmp] += y;
        res = res * (cnt[tmp] + 1) % mod;
        x /= tmp;
    }
}

void init(int x){
    vis[1] = 1;
    for (int i = 2; i <= x; i++){//线性筛筛出来每个合数的最小质因数
        if (!vis[i]) pri[i] = i, v.push_back(i);
        for (auto it : v){
            if (i * it > x) break;
            vis[i * it] = 1, pri[i * it] = it;
            if (i % it == 0) break;
        }
    }
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= x; i++){//线性递推出逆元
        inv[i] = mod - (mod / i * inv[mod % i] % mod) % mod;
    }
    for (int i = 1; i <= x; i++){
        update(i, 2);//加上双倍贡献计算答案
        ans[i] = res;
        update(i, -1);//答案计算完成后减去多余贡献
    }
}

signed main(){
    init(N - 5);
    cin >> T;
    while (T--){
        cin >> n;
        if (n == 1) cout << "inf\n";//特判
        else cout << ans[n - 1] << endl;//求的是(n-1)(n-1)!的因数个数
    }
    return 0;
}
```

---

## 作者：Luckies (赞：2)

### Upd on 2023.10.14 08:21：修改了推式子和题意的一些小错误。

## 前言

一道恐怖的绿题。显然我认为应该是蓝题。（不过在这篇题解写到一半的时候升蓝了，感谢 @[StudyingFather](https://www.luogu.com.cn/user/22030)。）

名字挺好的。

## 题意

给定 $n$，求出满足以下条件的三元组 $(x, y, z)$ 的组数：

1. $x \ge 0, z \ge 1$。

2. $x - \frac{y}{z} = n!$ 且 $\frac{x - y}{z} = \frac{n!}{n}$。

3. $z \mid x,z \mid y$。

答案为 $\infty$ 时，输出 ```inf```。

多组数据。

## 解法

首先我们需要将式子变形。最开始，将两式相减，得到：

$$\begin{aligned}
x - \frac{y}{z} - \frac{x - y}{z} = n! - \frac{n!}{n}
\end{aligned}$$

然后继续化简：

$$\begin{aligned}

x - \frac{y + (x - y)}{z} &= n! - (n - 1)! \\

x - \frac{x}{z} &= n \times (n - 1)! - (n - 1)!\\

\frac{x \times (z - 1)}{z} &= (n - 1) \times (n - 1)!\\

x &= \frac{(n - 1) \times (n - 1)! \times z}{z - 1}

\end{aligned}$$

可以发现 $y$ 被消掉了，于是不再需要考虑 $y$。

考虑 $z > 1$ 的情况，$x$ 要为整数，那么 $(n - 1) \times (n - 1)! \times z \mid z - 1$，而在 $z \ne 2$ 时，显然 $z \nmid z - 1$，那么就需要 $(n - 1) \times (n - 1)! \mid z - 1$。那么这样的 $x$ 的个数显然就是 $(n - 1) \times (n - 1)!$ 的约数个数。

于是这道题就转化为了求 $(n - 1) \times (n - 1)!$ 的约数个数。

根据约数个数定理和唯一分解定理，设 $x = p_1^{q_1} \times p_2^{q_2} \times \dots p_k^{q_k}$，其中 $p_i$ 为质数，那么 $x$ 的约数个数为 $\prod\limits_{i = 1}^{k}{(q_i + 1)}$。

设 $dp_i$ 表示 $i$ 这个质数在 $(n - 1) \times (n - 1)!$ 出现的次数，那么每次的答案即为 $\prod\limits_{i = 1}^{cnt}{(dp_i + 1)}$。

不过显然这样质因数分解很慢，考虑优化。

首先考虑线性筛的本质。在线性筛的过程中，每个合数都只会被它最小的质因数标记。考虑把它存下来，这样质因数分解的复杂度就降到了 $\Theta(\log{n})$。由于是阶乘，显然需要从 $1$ 到 $n - 1$ 枚举，每次都质因数分解存入 $dp_i$ 中，不然 $10^6!$，可想而知。这样的总时间复杂度为 $\Theta(n \log{n})$ 的，但是如果再加上多测，复杂度就变为了 $\Theta(T n \log{n})$，显然是不行的。

考虑继续优化上面的过程。

由于增加了多测，那么我们可以换一种方式，不一定要在线求答案，考虑预处理。

设 $Ans_i$ 表示 $i \times i!$ 的答案。将每一个 $i$ 进行质因数分解，设 $p$ 为当前分解到的质因数，$num$ 为这个质因数出现的次数。那么 $dp_p + num \times 2 \to dp_p$。这里 $dp_p$ 乘 $2$ 的原因是还有一个 $i$ 要乘。不过根据 $dp$ 的定义，乘 $i$ 的答案不能算进来，所以之后将答案存进 $Ans_i$ 后，还要减去一个 $num$。然后将 $\prod\limits_{i = 1}^{cnt}{(dp_i + 1)}$ 存入 $Ans_i$。这时我们会发现处理出 $\prod\limits_{i = 1}^{cnt}{(dp_i + 1)}$ 是一个很慢的过程。考虑优化这个过程。

设 $ans$ 为当前 $\prod\limits_{i = 1}^{cnt}{(dp_i + 1)}$ 的值。对于每一个 $i$，将 $i$ 进行质因数分解。设 $p$ 为当前分解到的质因数，$num$ 为这个质因数出现的次数。那么此时的 $dp_p$ 比上一个 $dp_p$ 增加了 $num$，将 $ans \div dp_p$，再将 $dp_p + num \times 2$，最后将 $ans \times dp_p$ 即可。根据前文所说，$dp_p$ 还需要减去一个 $num$，那么在 $ans$ 存入 $Ans_i$ 后，将 $ans \div dp_p$，$dp_p - num$，再将 $ans \times dp_p$ 即可。

由于 $ans$ 需要取模，所以这里的除法全部改为乘逆元即可。

最后处理一个特殊情况，前文我们都只考虑了 $z > 1$ 的情况，当 $z = 1$ 时，情况就会变成这样：

$$\begin{cases}

x - y = n! \\

x - y = \frac{n!}{n}

\end{cases}$$

那么 $n! = \frac{n!}{n}$，显然 $n = 1$。

那么这时候，$x - y = 1$，符合条件的三元组显然有 $\infty$ 个，输出 ```inf``` 即可。

毒瘤。

### AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5, Mod = 998244353;
int t, n, Ans[N], dp[N], pri[N], fac[N], inv[N];
vector<int> prime;
vector< pair<int, int> > f;
bool vis[N];
void Prime(int x)
{
    vis[1] = true;
    for(int i = 2; i <= x; i++)
    {
        if(!vis[i])
            prime.push_back(i), pri[i] = i;
        for(auto p : prime)
        {
            if(i * p > x)
                break;
            vis[i * p] = true;
            pri[i * p] = p;
            if(!(i % p))
                break;
        }
    }
    return;
}
void p_fac(int x)
{
    f.clear();
    while(x != 1)
    {
        int y = pri[x], cnt = 0;
        while(!(x % y))
            x /= y, cnt++;
        f.push_back(make_pair(y, cnt));
    }
    return;
}
void Inv(int x)
{
    inv[1] = 1;
    for(int i = 2; i <= x; i++)
        inv[i] = (Mod - Mod / i) * inv[Mod % i] % Mod;
    return;
}
void init(int n)
{
    Prime(1e6);
    Inv(1e6);
    int ans = Ans[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        p_fac(i);
        for(auto j : f)
        {
            int p = j.first, num = j.second;
            ans = ans * inv[dp[p] + 1] % Mod;
            dp[p] += num * 2;
            ans = ans * (dp[p] + 1) % Mod;
        }
        Ans[i] = ans;
        for(auto j : f)
        {
            int p = j.first, num = j.second;
            // cout << ans << " " << inv[dp[p] + 1] << " " << dp[p] + 1 << "    ";
            ans = ans * inv[dp[p] + 1] % Mod;
            dp[p] -= num;
            ans = ans * (dp[p] + 1) % Mod;
        }
    }
    return;
}
signed main()
{
    init(1e6);
    cin >> t;
    while(t--)
    {
        cin >> n;
        cout << (n == 1 ? "inf" : to_string(Ans[n - 1])) << "\n";
    }
    return 0;
}
```

---

## 作者：lfxxx (赞：2)

首先大力推式子。

为了方便，先假设 $2 \leq z$。

$x - \frac{y}{z} = n$

$\frac{x-y}{z} = (n-1) !$

很显然的 $z | x$ 以及 $z | y$

令 $m= \frac{x}{z}$ 以及 $k = \frac{y}{z}$

得到 $\frac{m \times z - k}{m - k}=n$ 

$(m \times z - k) = n \times (m - k)$

$(m - k) + (z - 1) \times m = n \times (m - k)$

$(z - 1) \times m = (n - 1) \times (m - k)$

$(z - 1) | (n - 1) \times (m - k)$

$(z - 1) | (n - 1) \times (m - k) \times z$

$(z - 1) | (n - 1) \times (x - y)$

$(z - 1) | (n - 1) \times (n - 1) ! \times z$

因为 $\gcd(z,z - 1)=1$

所以有

$(z - 1) | (n - 1) \times (n - 1) ! $

然后注意到确定了 $n,z$ 后，两个一次方程可以确定一个唯一的一组解。

所以答案就成了 $(n - 1) \times (n - 1) !$ 的因数个数。

但是我们可以预处理。

首先标记需要输出答案的 $n$。

首先我们可以用线性筛筛出每个数每种质因子的幂次。

具体来说，首先在线性筛时存储每个数被那哪些数筛掉了，这些数就是它的质因子做除法得出。接着对于每个数对每个质因子做除法得出幂次。

那么令 $f_i = (i - 1) \times (i - 1) !$。

有 $f_i = \frac{f_{i - 1} \times i^2}{i - 1}$

所以每次 $i$ 的质因子幂次加上 $i$ 中幂次的两倍，$i - 1$ 的质因子幂次减去 $i - 1$ 中幂次的一倍，如果这个 $i$ 被询问，那么用所有质因子幂次加 $1$ 之积计算因数数量。

但是由于幂次过多，这样会 TLE 。

所以只维护答案，每次修改就暴力把每个质因子的贡献修改。

显然这样是要求逆元的，这里需要预处理。

考虑对于 $(n - 1) !$ 某个质因子的幂次 $\leq \sum_{i = 1}^{k} \frac{n}{2^i} \leq n$。

所以只要处理 $1 \to n$ 的逆元即可。

那么总复杂度就是 $O(n \log n + T)$ 的。

那如果 $z = 1$ 呢？

带入前面的式子，有 $n = (n - 1) !$ ，即 $n = 1$。

此时显然任意 $x - y = 1$ 都可以满足条件，故输出 `inf` 即可。



---

## 作者：言琢დ (赞：1)

先把题意给出的式子稍微推一推。

$$xz-y=z\cdot n!~\cdots(1)$$

$$x-y=z\cdot(n-1)!~\cdots(2)$$

$$(2)\Rightarrow y=x-z\cdot(n-1)!~\cdots(3)$$

$$(1)(3)\Rightarrow xz-(x-z\cdot(n-1)!)=z\cdot n!~\cdots(4)$$

$$(4)\Rightarrow z=\dfrac{x}{x-(n-1)\cdot(n-1)!}~\cdots(5)$$

**样例只给出 $n=2\sim4$，说明 $n=5$ 肯定会有新发现。**

根据 $(3)(5)$ 枚举 $x\in[0,10^6]$ 跑出 $n=5$ 的解集：

| $\pink{x=97}$ | $\pink{y=-2231}$ | $\pink{z=97}$ |
| :----------- | :----------- | :----------- |
| $\pink{x=98}$ | $\pink{y=-1078}$ | $\pink{z=49}$ |
| $\pink{x=99}$ | $\pink{y=-693}$ | $\pink{z=33}$ |
| $\pink{x=100}$ | $\pink{y=-500}$ | $\pink{z=25}$ |
| $\pink{x=102}$ | $\pink{y=-306}$ | $\pink{z=17}$ |
| $\pink{x=104}$ | $\pink{y=-208}$ | $\pink{z=13}$ |
| $\pink{x=108}$ | $\pink{y=-108}$ | $\pink{z=9}$ |
| $\pink{x=112}$ | $\pink{y=-56}$ | $\pink{z=7}$ |
| $\blue{x=120}$ | $\blue{y=0}$ | $\blue{z=5}$ |
| $\purple{x=128}$ | $\purple{y=32}$ | $\purple{z=4}$ |
| $\purple{x=144}$ | $\purple{y=72}$ | $\purple{z=3}$ |
| $\purple{x=192}$ | $\purple{y=144}$ | $\purple{z=2}$ |

注意到以

$$\blue{\begin{cases}x=n!\\y=0\\z=n\end{cases}}$$

为分割线，将解集分为三个部分：粉色、蓝色、紫色。

其中蓝色部分的特点不言而喻，粉色部分的特点是：

$$\dfrac{x}{(n-1)!}\in(n-1,n)$$

，紫色部分的特点是:

$$z=2\sim n-1$$

考虑如何处理粉色部分和紫色部分的计数，首先紫色部分的计数不言而喻，因此重点在于处理粉色部分。

根据 $(5)$ 式，设

$$o=(n-1)\cdot(n-1)!$$

得到

$$z=\dfrac{x}{x-o}\ge1$$

的条件是

$$x\ge o$$

，这很明显已经满足了，剩下的要求就是找这个方程的解的个数：

$$x\bmod (x-o)=0$$

不妨设

$$x=k\cdot(x-o)$$

，其中 $k\ge1$，上述方程的解的个数就是合法整数 $k$ 的个数。

容易转证

$$x=\dfrac{k}{k-1}o$$

此时对于

$$\dfrac{x}{(n-1)!}\in(n-1,n)$$

的要求，可以转化为

$$\dfrac{k}{k-1}(n-1)\in(n-1,n)$$

，亦即

$$\dfrac{k}{k-1}\in\left(1,\dfrac{n}{n-1}\right)$$

此时 $k>n$ 即可满足要求，另外 $o$ 必须可以被 $k-1$ 整除，至此问题转化为求 $o$ 的 $\ge n$ 的因子个数。

然后考虑简单地把这个东西容斥一下下，就是我们所熟知的 $\sigma_0(o)-(n-1)$，据此原问题的答案就是：

$$\begin{aligned}
&\pink{\sigma_0(o)-(n-1)}+\blue1+\purple{n-2}\\
=~&\sigma_0(o)
\end{aligned}$$

显然现在唯一的问题就剩下

$$\sigma_0(o)=\sigma_0((n-1)\cdot(n-1)!)$$

怎么求。

考虑到这个东西要支持多测 $T\le10^5$，$n\le10^6$，所以很有可能是 $O(n\log n)$ 预处理（如果不带 $\log$ 按照你谷出题人习惯很有可能就是 $n\le10^7$ 了），然后 $O(1)$ 做单次查询，当然也有可能单次查询是 $O(\log n)$。

比较自然地设出

$$o_n=(n-1)\cdot(n-1)!$$

考虑设

$$ans_n=\sigma_0(o_n)=\prod(1+k_i)$$

，其中 $k_i$ 表示质因子分解后的次数，即

$$o_n=\prod p_i^{k_i}$$

要探索 $ans_n$ 与 $ans_{n-1}$ 的关系，实际上就是探索 $o_n$ 与 $o_{n-1}$ 之间的关系，由于长相就是个阶乘的长相，那当然是两式相除：

$$o_{n-1}=(n-2)\cdot(n-2)!$$

$$o_n=(n-1)\cdot(n-1)!$$

$$\dfrac{o_n}{o_{n-1}}=\dfrac{(n-1)\cdot(n-1)!}{(n-2)\cdot(n-2)!}=\dfrac{n-1}{n-2}\cdot(n-1)=\dfrac{(n-1)^2}{n-2}$$

探索出这一层关系，就发现 $ans_n$ 实际上就是在 $ans_{n-1}$ 的基础上剔除一个 $n-2$ 的因子，再添上两个 $n-1$ 的因子。

一种直观的考虑是，将 $1\sim n$ 暴力进行单次 $O(\sqrt{n})$ 的质因数分解，然后在数组 $k$ 上进行单点修改，另外再设一个变量 $p=\prod(1+k_i)$ 记录每时每刻的变化即可。

考虑到变量 $p$ 的变化每时每刻都需要做除法，因此预处理 $1\sim10^6$ 的逆元，将费马小定理求逆元的那只 $\log$ 给它扔掉！

就可以把预期两只 $\log$ 相乘等于两只 $\log$ 的预处理过程优化成两只 $\log$ 相加等于一只 $\log$ 的预处理啦。（卖萌）

总时间复杂度：$O(n\log n+T)$。

---

## 作者：Targanzqq (赞：0)

一道经典的数学题。

我们做这道题只用到两个思路：化简和优化。我们先尝试化简这个式子。

首先我们列出方程组：
$$\left\{
\begin{aligned}
x-\frac{y}{z}&=n! \\
\frac{x-y}{z}&=(n-1)!
\end{aligned}
\right.$$

我们先消去 $y$，转化为
$$x-\frac{x}{z}=(n-1)(n-1)!$$

我们再将 $z$ 移动到等号右边，转化为
$$x=(n-1)(n-1)!\frac{z}{z-1}$$

我们考虑 $y$ 的值，它可以表示为

$$y=x-z(n-1)!$$

因此其中一组解存在的条件是 $z-1\mid (n-1)(n-1)!z$，而 $z-1\perp z$，因此 $z-1\mid (n-1)(n-1)!$。答案就是满足条件的 $z-1$ 的个数。又因为 $z\ge 1$（此时 $z-1\not =0$，因此 $z\not =1$）。答案就是 $(n-1)(n-1)!$ 的约数个数。接下来我们尝试在可以接受的时间复杂度内解决这个问题。

- 首先我们考虑一个式子：$d(n)=\prod\limits_{i\in prime,i\mid n}^k (f_i+1)$，其中 $d$ 表示约数个数，$f$ 表示出现次数。而 $f$ 可以通过从 $1$ 到 $n-1$ 枚举累加，每次更新复杂度为 $\sqrt n$。因此我们将时间复杂度降到 $O(Tn\sqrt n)$。

- 但是上一种种情况下明显无法通过。我们考虑优化转移。一种较快的分解质因数的方法如下：我们筛出 $n$ 以下每个数的最小质因子，记作 $mp_i$。然后我们每次跳到 $\frac{i}{mp_i}$ 并同时记录每个质因数的出现次数 $cnt_i$。时间复杂度降到 $O(Tn\log n)$，仍然无法通过。

- 由于 $T$ 比较大，我们考虑离线做。我们记录 $ans_i$ 表示 $i\times i!$ 的答案个数，$res_i$ 表示 $i!$ 的答案个数。对于当前枚举到的质因子 $p$，我们转移 $ans_i$ 时从 $res_{i-1}$ 加入 $p^2$ 的贡献，也就是令 $f_p$ 加上 $2\times cnt_p$ （因为 $i^2$ 中每个质因数的出现次数都会是 $i$ 的两倍）。转移 $res_i$ 时从 $res_{i-1}$ 加入 $p$ 的贡献 。我们先把 $res_{i-1}$ 赋给 $res_i$，转移贡献的方式是对于 $p$，先让 $res_i$ 除以 $p$ 的原贡献，也就是 $f_p+1$（这里应改为乘逆元），并令 $f_p$ 加入新的贡献，然后乘回去。我们更新完 $ans$ 后更新 $res$，相当于从 $ans$ 的贡献中减去一倍的 $f_p$。然后我们发现先前的 $res$ 不用被保留，因此我们记录一个 $res$ 用于更新 $ans$ 即可。时间复杂度 $O(n\log n+T)$。

接下来我们找 $z=1$ 的贡献。我们得到这个式子：
$$\left\{
\begin{aligned}
&x-y=n! \\
&x-y=(n-1)!
\end{aligned}
\right.$$
此时 $n=1$。所以我们只要满足 $z=1$ 且 $x-y=1$ 即可，这样的三元组有无数个。 


源代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 1000000
using namespace std;

int T,n,a[N+5],mp[N+5];
int p[N+5],dis[N+5],top;

void find(){
	for(int i=2;i<=N;i++){
		if(!dis[i]){
			p[++top]=i;
			mp[i]=i;
		}
		for(int j=1;j<=top&&i*p[j]<=N;j++){
			int k=i*p[j];dis[k]=1;
			mp[k]=p[j];
			if(i%p[j]==0)break;
		}
	}
}

vector<pair<int,int> > d;
int f[N+5],ans[N+5],inv[N+5],res;

void get_p(int x){
	d.clear();
	while(x!=1){
		int k=mp[x],cnt=0;
		while(x%k==0){
			x/=k;cnt++;
		}
		d.push_back(make_pair(k,cnt));
	}
}

void get_inv(){
	inv[1]=1;
	for(int i=2;i<=N;i++){
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	}
}

signed main(){
	//ios::sync_with_stdio(false);
	cin>>T;
	find();
	get_inv();
	ans[0]=1;res=1;
	for(int i=1;i<=N;i++){
		get_p(i);
		for(auto k:d){
			res=(res*inv[f[k.first]+1])%mod;
		    f[k.first]+=2*k.second;
		    res=(res*(f[k.first]+1))%mod;
		}
		ans[i]=res;
		for(auto k:d){
			res=(res*inv[f[k.first]+1])%mod;
		    f[k.first]-=k.second;
		    res=(res*(f[k.first]+1))%mod;
		}
	}
	while(T--){
		cin>>n;
		if(n==1){
		    cout<<"inf"<<"\n";
	    }
	    else cout<<ans[n-1]<<"\n";
	}
}
```

---

## 作者：Disjoint_cat (赞：0)

# [P9007 最澄澈的空与海 (Hard Version)](https://www.luogu.com.cn/problem/P9007)

## 题意

给出 $n$，求满足下列式子的三元组 $(x,y,z)$ 的数量：

$$\begin{cases}x\in\mathbb N,y\in\mathbb Z,z\in\mathbb N^*\\x-\dfrac yz=n!&(1)\\\dfrac{x-y}z=\dfrac{n!}n&(2)\end{cases}$$

对 $998244353$ 取模，如果无穷多输出 `inf`。

多测，$T\le10^5,n\le10^6$。

## 题解

看见这种题，直接推柿子。

首先如果 $z=1$，则有 $x-y=n! =(n-1)!$，所以 $n=1$，此时有无穷多组 $(x,y)$，所以当 $n=1$ 时答案为 `inf`。以下考虑 $n>1$ 的情况。

当 $n>1$ 时，如果 $z=1$ 则上式无解，所以 $z>1$。所以可得：

$$\begin{aligned}&(1)-(2)\\\Longrightarrow& x-\dfrac xz=n!-(n-1)!\\\Longrightarrow &\dfrac{x(z-1)}z=(n-1)(n-1)!\\\Longrightarrow& x=\dfrac{z(n-1)(n-1)!}{z-1}\end{aligned}$$

将 $z$ 作为自变量，注意到 $(z,z-1)=1$，所以 $x$ 是整数的充要条件为

$$z\mid(n-1)(n-1)!$$

此时，$x$ 和 $z$ 都是整数，由 $(1)$ 得

$$y=z(x-n!)$$

也为整数。

所以当且仅当 $z\mid(n-1)(n-1)!$ 时，方程组有唯一解。

所以 $(x,y,z)$ 的数量即 $(n-1)(n-1)!$ 的因数个数。

下面考虑这东西怎么算。

---

设 $f(n)=(n-1)(n-1)!$。

注意到 $n$ 的值域很小，而询问次数较大，考虑把答案预处理出来。

考虑由 $n=k$ 的答案推出 $n=k+1$ 的答案，注意到

$$\dfrac{f(k+1)}{f(k)}=\dfrac{k\cdot k!}{(k-1)(k-1)!}=\dfrac{k^2}{k-1},$$

所以相当于加了两次 $k$ 的质因子，又减了一次 $k-1$ 的质因子。

令 $c_i$ 为质因子 $i$ 的出现次数，如果要加上 $j$ 个因子 $i$，由因数个数定理，答案会变成原来的 $\dfrac{i+j+1}{i+1}$。去掉质因子也是类似的，维护一下 $c_i$ 即可。

所以如果要将答案乘上 $x$，将 $x$ 分解质因数，然后再去更新即可。

可以直接枚举因数然后在倍数对应的质因数 `vector` 上 `push_back` 即可做到 $\Theta(n\log n)$ 预处理出来所有数的质因数。~~预处理的预处理是吧。~~

（实际上 $1\sim n$ 的不同质因数的个数和只有 $\Theta(n\log\log n)$ 个，可能可以把预处理优化到此复杂度。）

但是加质因子时涉及到除法，而逆元的计算是 $\Theta(\log M)$（$M$ 是模数）的，而 $\Theta(n\log\log n)$ 次加质因数操作再加一个 $\log$，而且 $n$ 可达 $10^6$，再加上大常数，很容易 TLE。

注意到 $f(n)$ 中任何质因数的出现次数都不会超过 $n$，所以实际上我们只会用到 $1\sim n$ 的逆元。所以我们用[线性求逆元](https://www.luogu.com.cn/problem/P3811)搞出 $1\sim10^6$ 的逆元，就能消掉那只 $\log$ 了。

总时间复杂度 $\Theta(n\log n+T)$ 或 $\Theta(n\log\log n+T)$。

代码不给了。

---

## 作者：_Vix_ (赞：0)

[原题链接](https://www.luogu.com.cn/problem/P9007)

---

## 分析

两个式子简单相减有：

$$x-\dfrac{x}{z}=n!-\dfrac{n!}{n}$$

$$x=\dfrac{(n-1)(n-1)!z}{z-1}$$

$z$ 与 $z-1$ 互质，那么要 $x$ 是整数，$z-1$ 必须是 $(n-1)(n-1)!$ 的约数，只需要在 $(i-1)(i-1)! \rightarrow i \times i!$ 时，记录一下 $\dfrac{i^2}{i-1}$ 的贡献。预处理是 $O(n \log n)$ 的，因为一个数的质因数个数是 $O(\log n)$ 级别的，每次枚举最小质因数即可。总时间复杂度 $O(n \log n + T)$。

特别的，当 $n=1$ 时，只需要满足 $x-y=1$ 即可，此时要输出 `inf`。

## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3e6 + 10, mod = 998244353;
int prime[N], v[N], inv[N], cnt;
int ans = 1, f[N], num[N];

void init(int n) {
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!v[i]) prime[++cnt] = i, v[i] = i;
		inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
		for (int j = 1; j <= cnt && i <= n / prime[j]; j++) {
			v[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

inline void upd(int x, int y) {
	while (x > 1) {
		int g = v[x];
		ans = (ll)ans * inv[num[g] + 1] % mod;
		num[g] += y;
		ans = (ll)ans * (num[g] + 1) % mod;
		x /= g;
	}
}

int main() {
	init(3000005);
	for (int i = 1; i <= 1000005; i++) {
		upd(i, 2);
		f[i] = ans;
		upd(i, -1);
	}
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		if (n == 1) puts("inf");
		else printf("%d\n", f[n - 1]);
	}
	return 0;
}
```


---

