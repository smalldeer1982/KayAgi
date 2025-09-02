# 「EZEC-11」Circle

## 题目描述

有 $n$ 个人，编号为 $1$ 到 $n$，坐在环上玩约瑟夫。

他们从 $1$ 到 $m$ 循环报数，与正常约瑟夫不同的是，没有报到 $1$ 的人都会被淘汰，直至只有一个人活下来为止。

设活下来的人编号为 $x$，则记 $J_m(n)=x$。

给定 $m,l,r$，求 $\sum_{i=l}^{r}J_m(i)$，输出对 $998244353$ 取模。

## 说明/提示

**本题采用捆绑测试。**

- Subtask 1（4 pts）：$T=1$，$m \leq 10$，$r \leq 200$。
- Subtask 2（8 pts）：$T=1$，$m \leq 10^6$，$r\leq 10^7$。 
- Subtask 3（8 pts）：$\sum (r-l+1) \leq 2 \times 10^6$。
- Subtask 4（10 pts）：$m=2$。
- Subtask 5（25 pts）：$T \leq 5$，$m \leq 10^6$。 
- Subtask 6（45 pts）：无特殊限制。 

对于 $100\%$ 的数据，$1 \leq T \leq 10^4$，$2 \leq m \leq 10^{12}$，$1 \leq l \leq r \leq 10^{18}$。

## 样例 #1

### 输入

```
4
2 1 4
3 3 7
8 12 64
2 1 1048976
```

### 输出

```
6
17
1149
148359175
```

# 题解

## 作者：unputdownable (赞：3)

考虑如何求出 $J_m(n)$。

递归，如果 $n < m$，$J_m(n)=1$；

如果 $n \geq m$，考虑报一遍 $1-m$：

![TK7ZSe.png](https://s4.ax1x.com/2021/12/21/TK7ZSe.png)

所以有：

$$J_m(n)=\begin{cases}1 & J_m(n-m+1)=n-m+1\\J_m(n-m+1)+m &  \text{else}\end{cases}$$

于是可以将 $n$ 按模 $m-1$ 分类，这样在每一类中，除了若干个 $J_m(n)=n$ 的位置外，都是公差为 $m$ 的等差数列。

--------

考虑每一类中有哪些不满足等差的位置（下称断点）。

由于 $J_m(n)=n$ 的下一项必然是 $1$，所以一个 $1$ 对应一个断点。

思考 $J_m(n)$ 什么情况下为 $1$：

上面提过 $1 \leq n < m$ 的时候是 $1$；

当 $n \geq m$ 时，易得 $n$ 必然是 $m$ 的倍数，否则报完一圈后 $1$ 一定当场出局，于是除 $m$ 后归纳。

可得断点只有 $k \times m^a$ 的形式，其中 $1 \leq k \leq m-1$。

那么每个同余类中就只有 $\log$ 个断点（$k \times m^a$ 正好在 $k$ 这个同余类中），拆成 $\log$ 个等差数列分别求和即可。

这样就得到了一个 $\Theta(m\log_m a)$ 的算法。

对于每一个 $i$ 暴力找出其前面最后一个断点，就能得到一个 $\Theta(\log_m a)$ 的单点求值算法。

两者结合起来可以得到 $55$ 分的好成绩。

--------

继续观察第 $k$ 组的答案。

事实上断点是 $k \times m^a$ 的形式，而点的个数是 $\lfloor \frac{n-k}{m-1}+1 \rfloor$。

只要断点的个数相同，并且点的个数相同，那么可以发现答案就是关于 $k$ 的不超过 $2$ 次的多项式。而断点个数和点的个数都只有两种，所以按这个把要算的东西分成三段，对每一段插值算即可。

时间复杂度 $\Theta(\log_m a)$。

---

## 作者：Mine_King (赞：1)

容易发现 $J _ m(i) \equiv 1 \pmod{m}$，因此我们考虑 $\frac{J _ m(i) - 1}{m}$。

可以打表发现：  
将 $i$ 按 ${} \bmod (m - 1)$ 分组，其中余 $k$ 的组可以分成若干段，第 $i$ 段的长度为 $k m ^ i$， 使得每段都是首项为 $0$ 公差为 $1$ 的等差数列。

考虑证明这个东西。  
首先容易得到一个关于 $J _ m$ 的递推式：

$$
J _ m(n) =
\begin{cases}
1 & n < m \lor J _ m(n - m + 1) = n - m + 1, \\
J _ m(n - m + 1) + m & \mathrm{otherwise.}
\end{cases}
$$

因此对于 $\frac{J _ m(i) - 1}{m} \ne 0$ 的位置，在按 ${} \bmod (m - 1)$ 分组后其值就等于前一项 $+ 1$。于是我们只需证 $J _ m(i) = 1$ 的位置在 ${} \bmod (m - 1) = k$ 的组中每次出现的位置为 $(\sum _ {i = 0} ^ n k m ^ i) + 1 (n \in \{-1\} \cup \mathbb{N})$。  
容易归纳证明 $J _ m (i) = 1$ 当且仅当 $i = a \cdot m ^ b (1 \le a < m, b \in \mathbb{N})$，并且有 $i \equiv a \pmod{(m - 1)}$。  
考虑从在分组中出现的位置反推原位置：

$$
\begin{aligned}
  & (m - 1) \sum\limits _ {i = 0} ^ n k m ^ i + k \\
= & \sum\limits _ {i = 1} ^ {n + 1} k m ^ i - \sum\limits _ {i = 0} ^ n k m ^ i + k \\
= & k m ^ {n + 1} - k + k \\
= & k m ^ {n + 1}
\end{aligned}
$$

容易发现与原位置中 $J _ m(i) = 0$ 的位置是一一对应的，得证。

然后考虑知道这个后怎么求解。  
以下设 ${J _ m}'(i) = \frac{J _ m(i) - 1}{m}$，我们只需要求出 ${J _ m}'(i)$ 的和，然后再 $\times m + r - l + 1$ 即可得到答案。

首先容斥成 $\sum\limits _ {i = 1} ^ r {J _ m}'(i) - \sum\limits _ {i = 1} ^ {l - 1} {J _ m}'(i)$，然后问题就是求 $\sum\limits _ {i = 1} ^ n {J _ m}'(i)$。

首先一个朴素的暴力是枚举每一组，然后每组只会分割成 $O(\log _ m n)$ 段，所以直接暴力求解，时间复杂度是 $O(m \log n)$ 的。

然后考虑从小的组到大的组的变化，容易发现每段都会增加，因此段数是单调不降的，而且由于一组的段数很少，因此可以直接暴力枚举每次段数减少的分界点。  
接下来就是考虑如何求段数相同的组的总和。  
设有 $cnt + 1$ 个完整的段，这些完整段的总长为 $len = \sum _ {i = 0} ^ {cnt} m ^ i$ 乘上当前组的编号。  
我们首先通过容斥将问题转化成求编号为 $1$ 到 $R$ 的组的总和。

对于完整的段，其答案为：

$$
\begin{aligned}
  & \sum\limits _ {k = 1} ^ R \sum\limits _ {i = 0} ^ {cnt} \frac{(k m ^ i - 1) k m ^ i}{2} \\
= & \frac{1}{2} \sum\limits _ {k = 1} ^ R \left(\sum\limits _ {i = 0} ^ {cnt} k ^ 2 m ^ {2 i} - \sum\limits _ {i = 0} ^ {cnt} k m ^ i\right) \\
= & \frac{1}{2} \sum\limits _ {k = 1} ^ R (k ^ 2 \cdot sqr - k \cdot len) \\
= & \frac{1}{2} \left(sqr \cdot \frac{R (R + 1) (2 R + 1)}{6} - len \cdot \frac{R (R + 1)}{2}\right)
\end{aligned}
$$

其中 $sqr = \sum _ {i = 0} ^ {cnt} m ^ {2 i}$。

对于余下的不完整段：

$$
\begin{aligned}
  & \sum\limits _ {k = 1} ^ R \frac{(n - k \cdot len - 1) (n - k \cdot len)}{2} \\
= & \frac{1}{2} \sum\limits _ {k = 1} ^ R (n - 1) n - (2 n - 1) k \cdot len + k ^ 2 len ^ 2 \\
= & \frac{1}{2} \left(R (n - 1) n - \frac{R (R + 1)}{2} (2 n - 1) len + \frac{R (R + 1) (2 R + 1)}{6} len ^ 2\right)
\end{aligned}
$$

然后注意处理一下完整段数为 $0$ 的情况。

另外，由于组的长度有 $\left\lfloor\frac{n}{m - 1}\right\rfloor$ 和 $\left\lfloor\frac{n}{m - 1}\right\rfloor + 1$ 两种，因此如果用 $f(n, r)$ 表示只考虑 $1$ 到 $r$ 这些组，每组长度为 $n$ 时的答案，则实际的答案为 $f(\left\lfloor\frac{n}{m - 1}\right\rfloor + 1, n \bmod (m - 1)) + f(\left\lfloor\frac{n}{m - 1}\right\rfloor, m - 1) - f(\left\lfloor\frac{n}{m - 1}\right\rfloor, n \bmod (m - 1))$。

```cpp
// Think twice, code once.
#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#define eputchar(c) putc(c, stderr)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)mod
#define eputs(str) fputs(str, stderr), putc('\n', stderr)
using namespace std;

const int mod = 998244353;

int T;
long long m, l, r;

namespace BruteForce1 { // Brute Force & Da Biao
	int J[10000005];

	void main() {
		for (int i = 1; i <= 10000000; i++) {
			if (i <= m) {J[i] = 0; continue;}
			int pos = J[i / m + i % m];
			if (!pos && i % m) J[i] = pos + i / m;
			else J[i] = m * pos - i % m;
		}
		int ans = 0;
		for (int i = l; i <= r; i++) {
			ans = (ans + m * J[i] + 1) % mod;
		}
		printf("%lld\n", ans);
		return ;
	}
}

namespace BruteForce3 { // O(m log n)
	int calc(long long n) {
		if (!n) return 0;
		int _ = n % mod;
		int ans = 0;
		for (int i = 1; i < m; i++) {
			long long k = n / (m - 1) + (i <= n % (m - 1));
			for (long long j = i; j <= k; j *= m)
				ans = (ans + (__int128)(j - 1) * j / 2) % mod, k -= j;
			ans = (ans + (__int128)(k - 1) * k / 2) % mod;
		}
		return ((long long)m * ans + _) % mod;
	}

	void main() {
		printf("%lld\n", (calc(r) - calc(l - 1) + mod) % mod);
		return ;
	}
}

namespace Sol { // O(log n)
	int inv2 = 499122177, inv6 = 166374059;

	int sum(long long x) {x %= mod; return x * (x + 1) % mod * inv2 % mod;}
	int sqrsum(long long x) {x %= mod; return x * (x + 1) % mod * (2 * x + 1) % mod * inv6 % mod;}
	int calc(long long n, long long r) {
		int ans = 0;
		if (!n || !r) return 0;
		int cnt = 0;
		long long len = 1;
		{
			long long _n = n - 1;
			for (long long j = 1; j <= _n / m; ) j *= m, _n -= j, cnt++, len += j;
		}
		long long lst = 0;
		for (int i = cnt; lst < r && i >= 0; i--) {
			len = 0;
			long long sqr = 0;
			for (long long j = 1, k = 0; k <= i; j *= m, k++)
				len += j, sqr = (sqr + (j % mod) * (j % mod)) % mod;
			if (len > n / (lst + 1)) continue;
			long long le = min(max(lst + 1, n / len), r);
			len %= mod;
			int res = 0;
			res = (sqrsum(le) - sqrsum(lst) + mod) % mod * sqr % mod;
			res = (res - (sum(le) - sum(lst) + mod) % mod * len % mod + mod) % mod;
			res = (long long)res * inv2 % mod;
			ans = (ans + res) % mod;
			res = 0;
			res = (sqrsum(le) - sqrsum(lst) + mod) % mod * len % mod * len % mod;
			res = (res -
				(sum(le) - sum(lst) + mod) % mod * ((2 * n - 1) % mod) % mod * len % mod +
				mod) % mod;
			res = (res + (le - lst + mod) % mod * ((n - 1) % mod) % mod * (n % mod) % mod) % mod;
			res = (long long)res * inv2 % mod;
			ans = (ans + res) % mod;
			if (i == 0 && le < r)
				ans = (ans + (n - 1) % mod * (n % mod) % mod * inv2 % mod * ((r - le) % mod)) % mod;
			lst = le;
		}
		return ans;
	}
	int calc(long long n) {
		if (!n) return 0;
		int ans =
			((calc(n / (m - 1) + 1, n % (m - 1)) + calc(n / (m - 1), m - 1)) % mod +
			mod - calc(n / (m - 1), n % (m - 1))) % mod;
		return ((m % mod) * ans + n) % mod;
	}

	void main() {
		printf("%lld\n", (calc(r) - calc(l - 1) + mod) % mod);
		return ;
	}
}

signed main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%lld%lld%lld", &m, &l, &r);
		Sol::main();
	}
	return 0;
}
```

---

