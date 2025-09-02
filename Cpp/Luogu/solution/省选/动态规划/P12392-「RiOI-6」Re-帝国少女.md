# 「RiOI-6」Re:帝国少女

## 题目背景

![](bilibili:BV1PU4y1Z7AQ)

小萝卜是远近闻名的军师呢（自豪脸）。

不过最近，如果你要找她请教，那么她就会大喊一声：那！我！问！你！

你愿意和他（她）一直在一起吗？你能接受被拒绝被分手吗？你能为了他付出多少呢？你能保证完成自己许下的诺言吗？

——不过萝卜还是很愿意帮忙的，尽管她已经见证了若干自己促成的人们分手了……生气啊啊啊啊啊！

## 题目描述

> 萝卜有 $m$ 件衣服，计划表为长为 $n$ 的序列 $a$，则 $a_i$ 为 $[1,m]$ 中的整数，表示当天穿的是哪一件衣服。  
> 现在给定 $a$，萝卜每次修改可以将 $a_i$ 修改为 $[1,m]$ 中任何一个整数，要求在使得序列中相邻的两个数都不同的前提下，让修改次数最少。

小萝卜的朋友很多，她们也希望和自己的意中人出去玩，她要以此为切入点评判这些情感问题。

具体的，对于一个表示计划表的序列 $a$，令**困难程度** $f(a,n,m)$ 表示以上问题的答案，$g(a,n,m)$ 表示使答案最优的修改方案数。其中两个方案不同当且仅当修改后的序列不同。

在所有长为 $n$ 值域为 $[1,m]$ 的整数序列中，对于每个 $i\in[0,\lfloor\frac{n}2\rfloor]$，小萝卜想知道困难程度为 $i$ 的序列的最优修改方案数之和是多少。

形式化的，给定 $n,m$，令所有长为 $n$ 值域为 $[1,m]$ 的整数序列的集合为 $S$，则对每个 $i\in[0,\lfloor\frac{n}2\rfloor]$ 求：

$$
\sum\limits_{a\in S}[f(a,n,m)=i]g(a,n,m)
$$

答案对 $10^9+7$ 取模。

## 说明/提示

#### 【样例解释】

对于样例 $1$，所有可能的序列以及对应的 $f,g$ 函数值如下：

- $[1,1,1]$：$1,1$。
- $[1,1,2]$：$1,1$。
- $[1,2,1]$：$0,1$。
- $[1,2,2]$：$1,1$。
- $[2,1,1]$：$1,1$。
- $[2,1,2]$：$0,1$。
- $[2,2,1]$：$1,1$。
- $[2,2,2]$：$1,1$。

故 $i=0$ 时答案为 $2$，$i=1$ 时答案为 $6$。

对于样例 $2,3$，暂时不能给你一个明确的答复。

#### 【数据范围】

**本题开启捆绑测试。**

|子任务|分数|$n\le$|$m\le$|
|:-:|:-:|:-:|:-:|
|$1$|$7$|$9$|$5$|
|$2$|$10$|$5\times10^3$|$2$|
|$3$|$13$|$50$|$50$|
|$4$|$15$|$200$|$200$|
|$5$|$20$|$200$|$10^9$|
|$6$|$35$|$5\times10^3$|$10^9$|

对于 $100\%$ 的数据，$1\le n\le 5\times10^3$，$2\le m\le 10^9$。

## 样例 #1

### 输入

```
3 2```

### 输出

```
2 6```

## 样例 #2

### 输入

```
4 5```

### 输出

```
320 1760 1280```

## 样例 #3

### 输入

```
11 4514```

### 输出

```
381390190 652303527 170625074 922115722 774772088 111358420```

# 题解

## 作者：_lmh_ (赞：4)

一个比官方题解更简单的做法。

数据范围与 T1 不同，这里 $n\le 5000$，所以 $O(n^2)$ 的时间复杂度是可以接受的。这启发我们设计一个二维的 `dp` 解决问题。

$m=2$ 的情况是简单的：将偶数位取反（$1$ 变成 $2$，$2$ 变成 $1$）之后相当于需要进行若干次操作使每一位都相同，此时唯一的最优策略是修改所有出现次数更少的数字，所以 $\sum [f(a,n,m)=i]g(a,n,m)=2\binom{n}{i}$。

否则，我们考虑任意一个最优策略，它在每个长度为 $l$ 的全部相等的连续段当中一定修改了 $[\frac{l}{2}]$ 个位置。

令 $0$ 表示没有进行修改，$1$ 表示进行了修改操作，则 $l$ 为奇数时，唯一的可能是形如 $0101010\cdots0$。

而 $l$ 为偶数时，一定存在一个偶数位置作为分界点，前面形如 $0101010\cdots1$，后面形如 $101010\cdots0$。

将它们分割成若干个 $01$ 和 $10$，如果 $l$ 为奇数就把最后一个 $0$ 单独拿出来。

现在对这个分割状态进行 `dp`，令 $f_{i,j,0/1/2}$ 为前 $i$ 个数进行了 $j$ 次修改，最后一个连续段形如 $0/01/10$ 的方案数。

这里定义一种“方案”为：在这 $i$ 个位置内填入 $[1,m]$ 的数作为原来的 $a$，再在放了 $1$ 的位置上进行修改使得相邻位互不相同。

初始令 $f_{1,0,0}=m,f_{2,0,0}=f_{2,0,1}=f_{2,0,2}=m(m-1)$。

转移方程为：

$$f_{i,j,0}=(f_{i-1,j,0}+f_{i-1,j,1}+f_{i-1,j,2})(m-1)$$
$$f_{i,j,1}=(f_{i-2,j-1,0}+f_{i-2,j-1,1}+f_{i-2,j-1,2})(m-1)^2$$

每一位不能和前面一位相同，没有额外限制。

$$f_{i,j,2}=(m-1)(m-2)f_{i-2,j-1,0}+(f_{i-2,j-1,1}+f_{i-2,j-1,2})(m-1)^2$$

注意这里从 $f_{i-2,j-1,0}$ 转移时第 $i$ 位不能和第 $i-2$ 位相同，因为这样会造出一个长度为奇数的连续段，它在 $f_{i,j,0}$ 中被统计。

之后就可以做到 $O(n^2)$ 了。~~可以用倍增 + FFT 做到 $O(n\log n)$ 但是我没写。~~

---

## 作者：P2441M (赞：3)

## 题意
> 给定 $m$ 和一个长度为 $n$ 的序列 $a$，对于 $1\leq i\leq n,a_i\in[1,m]\cap\mathbb{Z}$。现在可以进行若干次修改，每次修改可以选定一个 $a_i$，将其修改为 $[1,m]$ 中的一个整数。求在 $a$ 中任意相邻两数不同的前提下，最小的修改次数。

对于一个序列 $a$，定义**困难程度** $f(a)$ 为上面的问题的答案，$g(a)$ 为使得修改次数最小的修改方案数。

在所有长度为 $n$ 值域为 $[1,m]$ 的整数序列中，对于每个 $k\in\left[0,\lfloor\frac{n}{2}\rfloor\right]$，求出所有 $f(a)=k$ 的序列 $a$ 的 $g(a)$ 之和。$1\leq n\leq 5\times 10^3$，$2\leq m\leq 10^9$。

## 题解
前情回顾：[Luogu P12391](https://www.luogu.com.cn/problem/P12391) | [我的题解](https://www.luogu.com.cn/article/0pcnzark)

很好的细节 DP 题，使我大脑飞速旋转。

先做 $m=2$ 的情况。若 $2k\neq n$，则只能修改为 $0,1,\cdots$ 和 $1,0,\cdots$ 中的一种，各从中选择 $k$ 位翻转就是对应的原序列，方案数为 $2\binom{n}{k}$；若 $2k=n$，有 $2$ 种修改方案，方案数为 $\binom{n}{k}$，答案为 $2\binom{n}{k}$。因此，对于 $m=2$ 的情况，输出 $2\binom{n}{k}$ 即可。

再做 $m>2$ 的情况。还是按极长同色段划分序列，我们先不考虑颜色，思考一个段内的修改方案是怎么样的（我们用 $0/1$ 表示对应位置是否修改）：
- 若长度为奇数，显然只有 $010\cdots 010$ 这种修改方案。
- 若长度为偶数：比较显然有 $0101\cdots 01$ 和 $1010\cdots 10$ 这 $2$ 种方案，还有一种容易忽略的方案是 $0101\cdots11\cdots1010$，也就是修改**中间**的连续 $2$ 个位置 $(i,i+1)$，其中 $i$ 是偶数。计算可得我们能选出 $\frac{len}{2}-1$ 个这样的 $i$。

考虑颜色的限制，我们发现当前段的染色方案数。只会受前面段原来的颜色和前面段最后一个位置的颜色限制，由此设计 DP 状态：令 $f_{i,j,0/1}$ 表示考虑 $a[1,i]$，所有满足 $f(a[1,i])=j$ 的 $g(a[1,i])$ 之和。转移时我们枚举 $k$ 表示 $i$ 所在颜色段的长度，根据 $k$ 的奇偶性分类讨论，需要特判 $j=\left\lfloor\frac{i}{2}\right\rfloor$ 的情况。

下文中我们令 $t=\left\lfloor\frac{k}{2}\right\rfloor$。

$f$ 的计算包含两部分：当前段的初始方案数和染色方案数。

对于当前段的初始方案数，讨论 $f_{i-k,j-t,0/1}$ 中 $0/1$ 的取值：
- 若取值为 $0$，则当前段的颜色与前面的段的颜色不同即可，有 $m-1$ 种。
- 若取值为 $1$，则当前段的颜色既需要与前面的段不同，也需要和前面的段的最后一个位置修改后的颜色不同，有 $m-2$ 种。这是大部分情况，**但是有一个 corner case**：若我们在当前段修改了首位的颜色，则段的初始颜色不必与最后一个位置修改后的颜色不同，此时有 $m-1$ 种方案。

对于染色方案数，分别考虑首位和其他位的染色方案数即可，如果是连续修改中间的 $2$ 位也需要考虑进去。读者可以自行推导。

这样我们就得到了 $\mathcal{O}(n^3)$ 的朴素 DP。后面也会放这部分的代码。

考虑优化。我们发现转移式中大部分都是乘上 $m-1$ 或者 $m-2$ 的形式，可以提出来，于是需要快速计算包含 $k$ 和 $t$ 的那部分式子，更具体地，我们要维护出
$$
\sum_{k=1}^{\min(i-1,2j+1)}f_{i-k,j-t,0/1}(m-1)^{t-1}
$$

以及
$$
\sum_{k=1}^{\min(i-1,2j+1)}f_{i-k,j-t,0/1}(m-1)^{t-1}(t-1)
$$

容易想到前缀和优化。我们分奇偶维护，令
$$
\begin{align*}
g_{i,j,0/1}&=\sum_{k=0}^{\min(\frac{i}{2}, j)}f_{i-2k,j-k,0/1}(m-1)^k\\
h_{i,j,0/1}&=\sum_{k=0}^{\min(\frac{i}{2}, j)}f_{i-2k,j-k,0/1}(m-1)^kk
\end{align*}
$$

不难列出转移方程：
$$
\begin{align*}
g_{i,j,0/1}&=(m-1)g_{i-2,j-1,0/1}+f_{i,j,0/1}\\
h_{i,j,0/1}&=(m-1)(g_{i-2,j-1,0/1}+h_{i-2,j-1,0/1})
\end{align*}
$$

容易用 $g$ 和 $h$ 对应计算出我们所需的式子做到 $\mathcal{O}(1)$ 转移。时间复杂度 $\mathcal{O}(n^2)$。

## 代码
### $\mathcal{O}(n^3)$ DP
```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e3 + 5, MOD = 1e9 + 7;

inline int add(int x, int y) { return x += y, x >= MOD ? x - MOD : x; }
inline int sub(int x, int y) { return x -= y, x < 0 ? x + MOD : x; }
inline void cadd(int &x, int y) { x += y, x < MOD || (x -= MOD); }
inline void csub(int &x, int y) { x -= y, x < 0 && (x += MOD); }

int n, m, fac[N], ifac[N], f[N][N][2], pw[N];

int qpow(int a, ll b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = 1ll * res * a % MOD;
		a = 1ll * a * a % MOD;
	}
	return res;
}
void pre() {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % MOD;
	ifac[n] = qpow(fac[n], MOD - 2);
	for (int i = n - 1; ~i; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % MOD;
}
int C(int n, int m) { return 1ll * fac[n] * ifac[m] % MOD * ifac[n - m] % MOD; }

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    if (m == 2) {
    	pre();
    	for (int i = 0; i <= n >> 1; ++i) cout << C(n, i) * 2 % MOD << ' ';
    } else {
        pw[0] = 1;
    	for (int i = 1; i <= n >> 1; ++i) pw[i] = 1ll * pw[i - 1] * (m - 1) % MOD;
    	f[1][0][0] = m;
    	for (int i = 2; i <= n; ++i) for (int j = 0; j <= i >> 1; ++j) {
    		if (j == (i >> 1)) {
    			if (i & 1) f[i][j][0] = 1ll * m * pw[j] % MOD;
    			else {
    				f[i][j][0] = 1ll * m * pw[j] % MOD;
    				cadd(f[i][j][0], 1ll * m * (j - 1) % MOD * pw[j - 1] % MOD * (m - 2) % MOD);
    				f[i][j][1] = 1ll * m * pw[j] % MOD;
    			}
    		}
    		for (int k = 1; k < i && (k >> 1 <= j); ++k) {
    			int t = k >> 1;
    			int v1 = 1ll * f[i - k][j - t][0] * (m - 1) % MOD;
    			int v2 = 1ll * f[i - k][j - t][1] * (m - 2) % MOD;
    			if (k & 1) {
    				cadd(f[i][j][0], 1ll * v1 * pw[t] % MOD);
    				cadd(f[i][j][0], 1ll * v2 * pw[t] % MOD);
    			} else {
    				// 101010...
    				cadd(f[i][j][0], 1ll * v1 % MOD * (m - 2) % MOD * pw[t - 1] % MOD);
    				cadd(f[i][j][0], 1ll * v2 % MOD * (m - 2) % MOD * pw[t - 1] % MOD);
    				cadd(f[i][j][0], 1ll * f[i - k][j - t][1] * qpow(m - 1, t) % MOD);
    				// 010101...
    				cadd(f[i][j][1], 1ll * v1 % MOD * qpow(m - 1, t) % MOD);
    				cadd(f[i][j][1], 1ll * v2 % MOD * qpow(m - 1, t) % MOD);
    				// 010...11...010
    				cadd(f[i][j][0], 1ll * v1 % MOD * (t - 1) % MOD * pw[t - 1] % MOD * (m - 2) % MOD);
    				cadd(f[i][j][0], 1ll * v2 % MOD * (t - 1) % MOD * pw[t - 1] % MOD * (m - 2) % MOD);
    			}
    		}
    	}
    	for (int i = 0; i <= n >> 1; ++i) cout << add(f[n][i][0], f[n][i][1]) << ' ';
    }
    return 0;
}
```

### $\mathcal{O}(n^2)$ DP
```cpp
#include <iostream>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e3 + 5, MOD = 1e9 + 7;

inline int add(int x, int y) { return x += y, x >= MOD ? x - MOD : x; }
inline int sub(int x, int y) { return x -= y, x < 0 ? x + MOD : x; }
inline void cadd(int &x, int y) { x += y, x < MOD || (x -= MOD); }
inline void csub(int &x, int y) { x -= y, x < 0 && (x += MOD); }

int n, m, f[N][N][2], g[N][N][2], h[N][N][2];
int iv, pw[N], fac[N], ifac[N];

int qpow(int a, ll b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = 1ll * res * a % MOD;
		a = 1ll * a * a % MOD;
	}
	return res;
}
void pre() {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % MOD;
	ifac[n] = qpow(fac[n], MOD - 2);
	for (int i = n - 1; ~i; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % MOD;
}
int C(int n, int m) { return 1ll * fac[n] * ifac[m] % MOD * ifac[n - m] % MOD; }

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    if (m == 2) {
    	pre();
    	for (int i = 0; i <= n >> 1; ++i) cout << C(n, i) * 2 % MOD << ' ';
    } else {
    	pw[0] = 1;
    	for (int i = 1; i <= n >> 1; ++i) pw[i] = 1ll * pw[i - 1] * (m - 1) % MOD;
    	iv = qpow(m - 1, MOD - 2);
    	g[1][0][0] = f[1][0][0] = m;
    	for (int i = 2; i <= n; ++i) for (int j = 0; j <= i >> 1; ++j) {
    		if (j == (i >> 1)) {
    			if (i & 1) f[i][j][0] = 1ll * m * pw[j] % MOD;
    			else {
    				f[i][j][0] = 1ll * m * pw[j] % MOD;
    				cadd(f[i][j][0], 1ll * m * (j - 1) % MOD * pw[j - 1] % MOD * (m - 2) % MOD);
    				f[i][j][1] = 1ll * m * pw[j] % MOD;
    			}
    		}
            int v1 = 1ll * g[i - 1][j][0] * iv % MOD;
            int v2 = 1ll * g[i - 1][j][1] * iv % MOD;
    		cadd(f[i][j][0], 1ll * v1 * (m - 1) % MOD * (m - 1) % MOD);
    		cadd(f[i][j][0], 1ll * v2 * (m - 2) % MOD * (m - 1) % MOD);
    		if (j >= 1) {
	    		v1 = g[i - 2][j - 1][0], v2 = g[i - 2][j - 1][1];
                int x = 1ll * v1 * (m - 1) % MOD;
                int y = 1ll * v2 * (m - 1) % MOD;
	    		// 101010...
	    		cadd(f[i][j][0], 1ll * x * (m - 2) % MOD);
	    		cadd(f[i][j][0], 1ll * v2 * (m - 2) % MOD * (m - 2) % MOD);
	    		cadd(f[i][j][0], 1ll * y);
	    		// 010101...
	    		cadd(f[i][j][1], 1ll * x * (m - 1) % MOD);
	    		cadd(f[i][j][1], 1ll * y * (m - 2) % MOD);
	    		// 010...11...010
	    		v1 = h[i - 2][j - 1][0], v2 = h[i - 2][j - 1][1];
	    		cadd(f[i][j][0], 1ll * v1 % MOD * (m - 2) % MOD * (m - 1) % MOD);
	    		cadd(f[i][j][0], 1ll * v2 % MOD * (m - 2) % MOD * (m - 2) % MOD);
	    	}
	    	if (!j) {
	    		g[i][j][0] = f[i][j][0], g[i][j][1] = f[i][j][1];
	    		h[i][j][0] = h[i][j][1] = 0;
			} else {
		    	g[i][j][0] = add(1ll * g[i - 2][j - 1][0] * (m - 1) % MOD, f[i][j][0]);
		    	g[i][j][1] = add(1ll * g[i - 2][j - 1][1] * (m - 1) % MOD, f[i][j][1]);
		    	h[i][j][0] = add(1ll * h[i - 2][j - 1][0] * (m - 1) % MOD, 1ll * g[i - 2][j - 1][0] * (m - 1) % MOD);
		    	h[i][j][1] = add(1ll * h[i - 2][j - 1][1] * (m - 1) % MOD, 1ll * g[i - 2][j - 1][1] * (m - 1) % MOD);
		    }
		}
    	for (int i = 0; i <= n >> 1; ++i) cout << add(f[n][i][0], f[n][i][1]) << ' ';
    }
    return 0;
}
```

---

## 作者：Register_int (赞：3)

要做这题你首先至少得会 [帝国少女](/problem/P12391) 的 $60$ 分做法。

这题里面 $m=2$ 反而是简单的了。和帝国少女一样奇数位反转后，你发现：$k$ 对应的方案数总和一定是 $2\binom nk$。原因也很简单：若 $2k\not=n$，那么操作次数为 $k$ 的序列就是只有 $k$ 个 $1$ 或 $k$ 个 $2$ 的，否则若 $2k=n$，则所有 $\binom nk$ 个序列都有两种方案进行操作。直接算就好了。

考虑 $m>2$。在帝国少女中我们对同色段拆了贡献，这题也可以这么干。

直接 $dp_{i,j}$ 表示长度为 $i$ 最小次数是 $j$ 的方案数之和。抛开颜色不谈，只考虑段内修改的方案数，每次拼上去长度为 $l$ 的段。大致分为 $l$ 为奇数/偶数两种。

你会发现一些比较神秘的东西，因为偶数段修改是可以动到段头段尾的，而且可以在段中某个位置连续改两个……所以分个类。用 $dp_{i,j,0/1}$ 钦定最后一个位置是否在修改方案内。每次转移相当于枚举一个 $t$，枚举所有 $dp_{i-2t,j-t}$ 或 $dp_{i-2t+1,j-t}$，转移系数是 $t\times(m-1)^t$ 的形式。显然可以前缀和优化，时间复杂度 $O(n^2)$。

当然 std 的实现方式是把 $i$ 拆成 $2i'+0/1$ 了，这样转移的时候是一段连续的东西，会比较方便。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e3 + 10;
const int MAXM = 2.5e3 + 10;
const int mod = 1e9 + 7;

inline int add(int x, int y) { return x += y, x < mod ? x : x - mod; }
inline int del(int x, int y) { return x -= y, x < 0 ? x + mod : x; }
inline void cadd(int &x, int y) { x += y, x < mod || (x -= mod); }
inline void cdel(int &x, int y) { x -= y, x < 0 && (x += mod); }

inline 
int qpow(int b, int p) {
	int res = 1;
	for (; p; p >>= 1, b = (ll)b * b % mod) if (p & 1) res = (ll)res * b % mod;
	return res;
}

int p[MAXN], ip[MAXN], fac[MAXN], ifac[MAXN];

inline 
void init(int n, int m) {
	*p = 1;
	for (int i = 1; i <= n; i++) p[i] = (ll)p[i - 1] * (m - 1) % mod;
	ip[n] = qpow(p[n], mod - 2);
	for (int i = n; i; i--) ip[i - 1] = (ll)ip[i] * (m - 1) % mod;
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = (ll)i * fac[i - 1] % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = (ll)ifac[i] * i % mod;
}

inline 
int c(int n, int m) {
	if (n < 0 || m < 0 || n < m) return 0;
	return (ll)fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, m, dp[MAXM][MAXM][2][2], f[MAXM][2][2], g[MAXM][2][2];

int main() {
	scanf("%d%d", &n, &m), init(n + 1, m);
	if (m == 2) {
		for (int i = 0; i <= n / 2; i++) printf("%d ", add(c(n, i), c(n, n - i)));
		return 0;
	}
	for (int i = 1, x; i <= n; i++) {
		if (i & 1) dp[i / 2][i / 2][1][0] = (ll)p[i / 2] * m % mod;
		else {
			x = (ll)(i / 2 - 1) * p[i / 2 - 1] % mod * (m - 2) % mod;
			dp[i / 2][i / 2][0][0] = (ll)add(x, (ll)p[i / 2]) * m % mod;
			dp[i / 2][i / 2][0][1] = (ll)p[i / 2 - 1] * m % mod;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0, x, y; j <= i / 2; j++) {
			int u = i / 2;
			// odd 01010...
			if (i & 1) {
				x = (ll)f[u - j][0][0] * ip[n / 2 - u] % mod;
				cadd(dp[u][j][1][0], (ll)x * (m - 1) % mod);
				x = (ll)f[u - j][0][1] * ip[n / 2 - u] % mod;
				cadd(dp[u][j][1][0], (ll)x * (m - 2) % mod * (m - 1) % mod);
			} else if (j < u) {
				x = (ll)f[u - j - 1][1][0] * ip[n / 2 - u + 1] % mod;
				cadd(dp[u][j][0][0], (ll)x * (m - 1) % mod);
				x = (ll)f[u - j - 1][1][1] * ip[n / 2 - u + 1] % mod;
				cadd(dp[u][j][0][0], (ll)x * (m - 2) % mod * (m - 1) % mod);
			}
			// even 101010...
			x = (ll)f[u - j][i & 1][0] * ip[n / 2 - u + 1] % mod;
			cadd(dp[u][j][i & 1][0], (ll)x * (m - 2) % mod * (m - 1) % mod);
			x = (ll)f[u - j][i & 1][1] * ip[n / 2 - u + 1] % mod;
			cadd(dp[u][j][i & 1][0], (ll)x * ((ll)(m - 1) * (m - 2) % mod + 1) % mod * (m - 1) % mod);
			// even 010101...
			x = (ll)f[u - j][i & 1][0] * ip[n / 2 - u + 1] % mod;
			cadd(dp[u][j][i & 1][1], (ll)x * (m - 1) % mod);
			x = (ll)f[u - j][i & 1][1] * ip[n / 2 - u + 1] % mod;
			cadd(dp[u][j][i & 1][1], (ll)x * (m - 2) % mod * (m - 1) % mod);
			// even 010110...
			x = (ll)f[u - j][i & 1][0] * ip[n / 2 - u + 1] % mod;
			y = (ll)g[u - j][i & 1][0] * ip[n / 2 - u + 1] % mod;
			cdel(y, (ll)x * (n / 2 - u + 1) % mod);
			cadd(dp[u][j][i & 1][0], (ll)y * (m - 2) % mod * (m - 1) % mod);
			x = (ll)f[u - j][i & 1][1] * ip[n / 2 - u + 1] % mod;
			y = (ll)g[u - j][i & 1][1] * ip[n / 2 - u + 1] % mod;
			cdel(y, (ll)x * (n / 2 - u + 1) % mod);
			cadd(dp[u][j][i & 1][0], (ll)y * (m - 2) % mod * (m - 2) % mod * (m - 1) % mod);
			// upd
			cadd(f[u - j][i & 1][0], (ll)dp[u][j][i & 1][0] * p[n / 2 - u] % mod);
			cadd(f[u - j][i & 1][1], (ll)dp[u][j][i & 1][1] * p[n / 2 - u] % mod);
			cadd(g[u - j][i & 1][0], (ll)dp[u][j][i & 1][0] * p[n / 2 - u] % mod * (n / 2 - u) % mod);
			cadd(g[u - j][i & 1][1], (ll)dp[u][j][i & 1][1] * p[n / 2 - u] % mod * (n / 2 - u) % mod);
		}
	}
	for (int i = 0; i <= n / 2; i++) {
		printf("%d ", add(dp[n >> 1][i][n & 1][0], (ll)dp[n >> 1][i][n & 1][1] * (m - 1) % mod));
	}
}
```

---

## 作者：dream10 (赞：0)

## Hint

先做 T1，再做 T2。

## Solution

### Step 1

对于 $m=2$ 的情况，是简单的，枚举奇数位的 $1$ 个数和偶数位的 $1$ 个数，用组合数计算。

### Step 2

对于 $m>2$ 的情况，是复杂的。首先将答案重新表述为枚举所有的可能的序列，再枚举可能的最小操作方案，使得最小操作方案的次数恰好是 $i$。那么就可以拆分成颜色连续段，每一段枚举序列和方案。

### Step 3

用 $0$ 表示不改，用 $1$ 表示改。

对于奇数长度的串，就是 $010\cdots1010$。

对于偶数长度的串，就是 $010\cdots101,1010\cdots1010,010\cdots011\cdots1010$。（长度为 $n$，第三种有 $\frac{n}{2}-1$ 种可能。）

### Step 4

进行上述计数的 dp，因为两个 $1$ 相邻会影响数数，所以记录 $dp(i,j,k\in \{0,1\})$ 表示前 $i$ 位的序列和方案计算过了，方案中改变了 $j$ 个位置，以及最后一个位置是否改变。

枚举 $i,j,k$ 还有最后一段连续颜色长度可以做到 $O(n^3)$，见代码。

进行 dp 的时候的 trick：（强烈推荐对 Ri 的代码阅读理解，很好懂）

1. 用 $i \bmod 2,\lfloor \frac{i}{2} \rfloor$ 表示 $i$。
2. $k=1$ 的时候最后一个位置的选择暂时先不选，这个也记进状态里。

```
ll dp[MAXN][2][MAXN][2];

void main(){
    cin>>n>>m;
    init();
    if(m==2){
        for(int i=0;i<=(n+1)/2;++i)
            for(int j=0;j<=n/2;++j){
                madd(ans[min(i+j,n-i-j)],C((n+1)/2,i)*C(n/2,j)*(2*(i+j)==n?2:1));
            }
    }else{
        //初始化
        for(int i=1;i<=n;++i){
            if(i&1){
                dp[i>>1][i&1][i/2][0]=m * pw[i/2]%P;//01010
            }else{
                dp[i>>1][i&1][i/2][0]=m * (pw[i/2-1]*(m-2)%P*(i/2-1)%P + pw[i/2])%P;
                dp[i>>1][i&1][i/2][1]=m * (pw[i/2-1])%P;
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=0;j<=i/2;++j){
                for(int k=0;k<=j;++k){
                    //odd

                    if(i&1){
                        madd(dp[i>>1][1][j][0],(m-1) * dp[(i>>1)-k][0][j-k][0]%P *pw[k]);
                        madd(dp[i>>1][1][j][0],(m-1) * dp[(i>>1)-k][0][j-k][1]%P * (m-2)%P * pw[k]);
                    }else{
                        if((i>>1)-k-1>=0){
                            madd(dp[i>>1][0][j][0],(m-1) * dp[(i>>1)-k-1][1][j-k][0]%P *pw[k]);
                            madd(dp[i>>1][0][j][0],(m-1) * dp[(i>>1)-k-1][1][j-k][1]%P * (m-2)%P * pw[k]);
                        }
                    }
                    if(k>0){
                        //even
    
                        //case 1: 10101010
                        madd(dp[i>>1][i&1][j][0],(m-1) * dp[(i>>1)-k][i&1][j-k][0]%P * 1 * pw[k-1] %P * (m-2));
                        madd(dp[i>>1][i&1][j][0],(m-1) * dp[(i>>1)-k][i&1][j-k][1]%P * ((m*m-3*m+3)%P)%P * pw[k-1] %P);
                        
                        //case 2: 01010101
    
                        madd(dp[i>>1][i&1][j][1],(m-1) * dp[(i>>1)-k][i&1][j-k][0]%P * 1 * pw[k-1]);
                        madd(dp[i>>1][i&1][j][1],(m-1) * dp[(i>>1)-k][i&1][j-k][1]%P * (m-2)%P * pw[k-1]);
    
                        //case 3: 01101010
                        madd(dp[i>>1][i&1][j][0],(m-1) * dp[(i>>1)-k][i&1][j-k][0]%P * pw[k-1]%P * (m-2) %P * (k-1));
                        madd(dp[i>>1][i&1][j][0],(m-1) * dp[(i>>1)-k][i&1][j-k][1]%P *(m-2)%P * pw[k-1]%P * (m-2)%P * (k-1));
                    }
                }
            }
        }
        for(int j=0;j<=n/2;++j){
            ans[j]=(dp[n>>1][n&1][j][0]+dp[n>>1][n&1][j][1] * (m-1))%P;
        }
    }
    for(int i=0;i<=n/2;++i)printf("%lld ",(ans[i]+P)%P);
    puts("");
}
```

### Step 5

需要优化时间复杂度。

对于从 $dp(x,i,\ast)$ 到 $dp(y,j,\star)$ 的转移，奇数长度，满足：

$$
i+(\frac{y}{2}-\frac{x}{2}+\circ)=j\\
\quad\\
i-\frac{x}{2}+\circ=j-\frac{y}{2}\\
\quad\\
\frac{x}{2}-i-\circ=\frac{y}{2}-j\\
$$

找到不变量，设置辅助数组，是 dp 优化的常用技巧，使用即可。

这里不变量就是 $\frac{x}{2}-i$。

于是根据这个不变量设计数组。

转移的时候有一个 $\cdots\times(x-y)\quad (y<x)$ 的项，需要拆成 $x,-y$ 然后使用两个辅助数组，分别记录乘不乘 $-x$ 的前缀和就可以做到 $O(n^2)$。

```
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void read(T &a){
    #define gc getchar()
    char c;a=0;int f=1;
    while(!isdigit(c=gc))if(c=='-')f=-1;
    do a=a*10+c-'0';
    while(isdigit(c=gc));
    a*=f;
}
template<typename T>
void write(T a){
    if(a<0)putchar('-'),a=-a;
    if(a>=10)write(a/10);
    putchar('0'+a%10);
}
char GC(){
    char c=getchar();
    while(c<=32)c=getchar();
    return c;
}
template<typename T>
void chmin(T &x,T y){if(x>y)x=y;}
template<typename T>
void chmax(T &x,T y){if(x<y)x=y;}
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> PII;
typedef pair<ll,int> PLI;
typedef __int128 lll;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
int RRand(int n){return (ull)rng()*n>>32;}
namespace GENSOKYO{
int n;ll m;
const int P=1000000007;
const int MAXN=5010;
ll fac[MAXN],ifac[MAXN];
ll qpow(ll a,ll b){
    ll c=1;for(;b;b>>=1,a=a*a%P)if(b&1)c=c*a%P;return c;
}
ll C(int n,int m){
    if(n<0||n<m)return 0;
    return fac[n]*ifac[m]%P*ifac[n-m]%P;
}
ll ans[MAXN];
void madd(ll &x,ll y){x=(x+y)%P;}
ll pw[MAXN],ipw[MAXN];
void init(){
    fac[0]=1;
    for(int i=1;i<=5000;++i)fac[i]=fac[i-1]*i%P;
    ifac[5000]=qpow(fac[5000],P-2);
    for(int i=4999;i>=0;--i)ifac[i]=ifac[i+1]*(i+1)%P;
    pw[0]=ipw[0]=1;
    pw[1]=m-1;
    ipw[1]=qpow(m-1,P-2);
    for(int i=2;i<=5000;++i){
        pw[i]=pw[i-1]*pw[1]%P;
        ipw[i]=ipw[i-1]*ipw[1]%P;
        assert(pw[i]*ipw[i]%P==1);
    }
}
ll dp[MAXN][2][MAXN][2];
ll f[2][MAXN][2];//去掉第一维
ll g[2][MAXN][2];//乘下标
void main(){
    cin>>n>>m;
    init();
    if(m==2){
        for(int i=0;i<=(n+1)/2;++i)
            for(int j=0;j<=n/2;++j){
                madd(ans[min(i+j,n-i-j)],C((n+1)/2,i)*C(n/2,j)*(2*(i+j)==n?2:1));
            }
    }else{
        //初始化
        for(int i=1;i<=n;++i){
            if(i&1){
                dp[i>>1][i&1][i/2][0]=m * pw[i/2]%P;//01010
            }else{
                dp[i>>1][i&1][i/2][0]=m * (pw[i/2-1]*(m-2)%P*(i/2-1)%P + pw[i/2])%P;
                dp[i>>1][i&1][i/2][1]=m * (pw[i/2-1])%P;
            }
        }
        for(int i=1;i<=n;++i){
            for(int j=0;j<=i/2;++j){
                //odd
                if(i&1){
                    madd(dp[i>>1][1][j][0],(m-1) * f[0][i/2-j][0]%P *pw[i>>1]);
                    madd(dp[i>>1][1][j][0],(m-1) * f[0][i/2-j][1]%P * (m-2)%P * pw[i>>1]);
                }else{
                    if(i/2-j-1>=0){
                        madd(dp[i>>1][0][j][0],(m-1) * f[1][i/2-j-1][0]%P * pw[i>>1]%P *ipw[1]);
                        madd(dp[i>>1][0][j][0],(m-1) * f[1][i/2-j-1][1]%P * (m-2)%P * pw[i>>1]%P * ipw[1]);
                    }
                }
                //even

                //case 1: 10101010

                madd(dp[i>>1][i&1][j][0],(m-1) * f[i&1][i/2-j][0]%P * 1 * pw[i>>1] %P * ipw[1]%P * (m-2));
                madd(dp[i>>1][i&1][j][0],(m-1) * f[i&1][i/2-j][1]%P * ((m*m-3*m+3)%P)%P * pw[i>>1]%P *ipw[1]);

                //case 2: 01010101

                madd(dp[i>>1][i&1][j][1],(m-1) * f[i&1][i/2-j][0]%P * 1 * pw[i>>1]%P *ipw[1]);
                madd(dp[i>>1][i&1][j][1],(m-1) * f[i&1][i/2-j][1]%P * (m-2)%P * pw[i>>1]%P *ipw[1]);

                //case 3: 01101010
                madd(dp[i>>1][i&1][j][0],(m-1) * f[i&1][i/2-j][0]%P * pw[i>>1]%P *ipw[1]%P * (m-2) %P * (i/2+P-1));
                madd(dp[i>>1][i&1][j][0],(m-1) * f[i&1][i/2-j][1]%P *(m-2)%P * pw[i>>1]%P *ipw[1]%P * (m-2)%P * (i/2+P-1));

                madd(dp[i>>1][i&1][j][0],(m-1) * g[i&1][i/2-j][0]%P * pw[i>>1]%P *ipw[1]%P * (m-2) %P);
                madd(dp[i>>1][i&1][j][0],(m-1) * g[i&1][i/2-j][1]%P *(m-2)%P * pw[i>>1]%P *ipw[1]%P * (m-2)%P );

                madd(f[i&1][i/2-j][0],dp[i>>1][i&1][j][0]*ipw[i>>1]);
                madd(f[i&1][i/2-j][1],dp[i>>1][i&1][j][1]*ipw[i>>1]);
                madd(g[i&1][i/2-j][0],dp[i>>1][i&1][j][0]*ipw[i>>1]%P*(P-(i>>1)));
                madd(g[i&1][i/2-j][1],dp[i>>1][i&1][j][1]*ipw[i>>1]%P*(P-(i>>1)));
            }
            // for(int j=0;j<=i/2;++j){
            //     printf("dp[%d][%d][0]=%lld\n",i,j,dp[i>>1][i&1][j][0]);
            //     printf("dp[%d][%d][1]=%lld\n",i,j,dp[i>>1][i&1][j][1]);
            // }
        }
        for(int j=0;j<=n/2;++j){
            ans[j]=(dp[n>>1][n&1][j][0]+dp[n>>1][n&1][j][1] * (m-1))%P;
        }
    }
    for(int i=0;i<=n/2;++i)printf("%lld ",(ans[i]+P)%P);
    puts("");
}
}
signed main(){
    int T=1;//cin>>T;
    while(T--)GENSOKYO::main();
    return 0;
}
```

## Thanks & Reference

感谢 Register_int 的高质量题目和题解，受益匪浅。

尝试多加了点空格，让码风更舒服呢。

---

