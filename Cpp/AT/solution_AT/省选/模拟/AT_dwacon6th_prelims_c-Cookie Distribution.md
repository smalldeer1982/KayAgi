# Cookie Distribution

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_c

$ N $ 人の子供たちがいます。子供たちには $ 1,2,\ldots,N $ と番号が振られています。 これから $ K $ 日間、子供たちにクッキーが配られることになりました。 $ i $ 日目には $ N $ 人の中から $ a_i $ 人の子供が等確率で選ばれ、選ばれた子供たちはそれぞれクッキーを $ 1 $ 枚受け取ります。($ K $ 回の子供の選択はすべて独立に行われます。)

$ K $ 日間で子供 $ i $ が受け取るクッキーの枚数を $ c_i $ として、子供たちの *うれしさ* を $ c_1\ \times\ c_2\ \times\ \ldots\ \times\ c_N $ で定義します。 うれしさの期待値に $ \binom{N}{a_1}\ \times\ \binom{N}{a_2}\ \times\ \ldots\ \times\ \binom{N}{a_K} $ をかけた値(これは整数となることが示せます)を $ 10^9+7 $ で割ったあまりを求めてください。

## 说明/提示

### 注記

$ \binom{n}{k} $ は異なる $ n $ 個の対象から $ k $ 個を選ぶ選び方の総数を表します。

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ K\ \leq\ 20 $
- $ 1\ \leq\ a_i\ \leq\ N $

### Sample Explanation 1

\- $ 1 $ 日目では、子供 $ 1,2,3 $ のいずれもクッキーを受け取ります。 - $ 2 $ 日目では、子供 $ 1,2,3 $ のいずれか $ 1 $ 人がクッキーを受け取りません。 - どの場合もうれしさは $ 4 $ のため、うれしさの期待値は $ 4 $ となります。これに $ \binom{3}{3}\ \times\ \binom{3}{2} $ をかけた値である $ 12 $ を出力してください。

### Sample Explanation 2

\- 期待値の $ \binom{N}{a_1}\ \times\ \binom{N}{a_2}\ \times\ \ldots\ \times\ \binom{N}{a_K} $ 倍を $ 10^9+7 $ で割ったあまりを求めてください。

## 样例 #1

### 输入

```
3 2
3 2```

### 输出

```
12```

## 样例 #2

### 输入

```
856 16
399 263 665 432 206 61 784 548 422 313 848 478 827 26 398 63```

### 输出

```
337587117```

# 题解

## 作者：Lskkkno1 (赞：3)

- [Atcoder](https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_c)

- [AT5742 Cookie Distribution](https://www.luogu.com.cn/problem/AT5742)

### 题意概述

有 $N$ 个孩子，用 $K$ 天给孩子们发糖果。

第 $i$ 天有 $a_i$ 个糖果，等概率地发给这 $n$ 个孩子(每一天每个孩子最多可以获得一个糖果)，设 $K$ 天后第 $i$ 个孩子获得的糖果为 $c_i$。

求 $\prod_{i = 1}^n c_i$ 的期望乘上 $\prod_{i = 1}^n \binom N {a_i}$ ，答案对 $10^9 + 7$ 取模。

$N \le 10^3, K \le 20$

### 正解

期望乘上那个组合数就是所有方案下的答案了对吧。

直接 dp 肯定不太好做，要记录每一个人选了多少个曲奇，考虑换一种方式来表示原问题。

首先原问题可以转化成这样一个问题：

**"每一个人从拥有的曲奇里选择某一天得到的那一个曲奇， 求不同的选法"**

答案其实也正好是 $\prod c_i$ (神奇的是这样做与原问题是等价的)。

所以我们只需要关心每个人选择的那个曲奇就好了。

设 $x_i$ 表示有 $x_i$ 个孩子在第 $i$ 天得到了它们选择的曲奇。

先不考虑顺序, 钦定就是前面 $x_i$ 个人得到了这 $x_i$ 个曲奇。

转移系数是 $\binom {N - x_i} {a_i - x_i}$ (将剩下还没被选的曲奇随便分给其他人)。

最后再将人排序, 乘上 $\frac {N!} {\prod x_i!}$ (同一天选的与顺序没有关系, 所以要除 $x_i!$)。

答案其实就是：
$$
N! \prod_{i = 1}^n \frac {\binom {N - x_i} {a_i - x_i}} {x_i!}
$$
根据这个式子可以设出状态 $f(i, j)$ 表示前 $i$ 天有 $j$ 个人得到了选择的那个曲奇的方案数。

转移时枚举 $x_i$ 并乘上有关于 $x_i$ 的系数。

状态 $O(NK)$， 转移 $O(N)$， 时间复杂度 $O(N^2 K)$。

$\color {DeepSkyBlue} {Code}$

```cpp
/*
	f[i][j] = \sum f[i - 1][j - x] * comb(n - x, a[i] - x) * ifac[x]
*/
#include <bits/stdc++.h>
#define K 25
#define N 1005

using namespace std;

const int mod = 1e9 + 7;

int n, k;
int a[K], f[K][N];
int fac[N], ifac[N];

inline int fpm(int x, int y) {
	int r = 1;
	while(y) {
		if(y & 1) r = 1LL * r * x % mod;
		x = 1LL * x * x % mod, y >>= 1;
	}
	return r;
}
inline int perm(int x, int y) { return 1LL * fac[x] * ifac[x - y] % mod; }
inline int comb(int x, int y) { return 1LL * perm(x, y) * ifac[y] % mod; }

int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= k; ++i)
		scanf("%d", &a[i]);
	
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = 1LL * i * fac[i - 1] % mod;
	ifac[n] = fpm(fac[n], mod - 2);
	for(int i = n; i; --i) ifac[i - 1] = 1LL * i * ifac[i] % mod;
	
	f[0][0] = 1;
	for(int i = 0; i < k; ++i) {
		for(int j = 0; j <= n; ++j) {
			if(!f[i][j]) continue;
			for(int x = 0; x <= a[i + 1] && j + x <= n; ++x) {
				f[i + 1][j + x] = (f[i + 1][j + x] + 
				1LL * f[i][j] * comb(n - x, a[i + 1] - x) % mod * ifac[x]) % mod;
			}
		}
	}
	
	int ans = 1LL * fac[n] * f[k][n] % mod;
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

# Preface

神仙题 orz

# Solution

题目求的实际上是所有方案的 $\prod c_i$ 之和。

把 $\prod c_i$ 组合意义化，就是每个人在糖果中选一个的方案数。

转化一下，把每个人选的糖果钦定好，然后求满足钦定糖果的分发方案也是一样的。

设第 $i$ 天的糖果被 $x_i$ 个人钦定，满足钦定糖果的分发方案就是 $\displaystyle\prod_{i=1}^{k}\binom{n-x_i}{a_i-x_i}$。

再乘上这些人钦定这些糖果的方案 $\dfrac{n!}{\prod x_i!}$。

所以确定了 $\{x_k\}$，对答案的贡献就是 
$$n!\prod_{i=1}^{k}\frac{1}{x_i!}\cdot\binom{n-x_i}{a_i-x_i}$$

发现关于 $x_i$ 的项是单独的，可以 DP 求解。

有一个限制是 $\sum x_i=n$，于是设 $f_{i,j}$ 为前 $i$ 天 $\sum x_i=j$ 的所有贡献之和。

转移是显然的。

# Code
```cpp
LL n, k, a[N]; MI ans, f[K][N];
Combinations<MI> C;
int main() {
	cin >> n >> k, C.init(n), f[0][0] = 1;
	REP(i, 1, k) {
		cin >> a[i];
		REP(j, 0, n) REP(x, 0, j)
			f[i][j] += f[i - 1][j - x] * C(n - x, a[i] - x) / C.fac[x];
	}
	cout << f[k][n] * C.fac[n] << '\n';
    return 0;
}
```

---

## 作者：win114514 (赞：0)

组合意义保平安。

### 思路

发现 $\prod$ 的贡献不好统计。

我们可以考虑 $\prod$ 的组合意义。

容易发现：

$$
\prod c_i=\prod \sum_{j=1}^{c_i}1
$$

那么依照分配律，我们发现这个东西的组合意义是每个人从获得的饼干中选一个出来的方案。

这样就会变好统计很多。

设 $dp_{i,j}$ 为前 $i$ 天，有 $j$ 个人已经选出了代表的饼干。

那么：

$$
dp_{i,j}=\sum_{k=0}^{j}dp_{i-1,k}\binom{n-k}{j}\binom{n-j}{a_i-j}
$$

时间复杂度：$O(n^2)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;

int n, k;
int f[1010];
int g[1010];
int c[1010][1010];

signed main() {
  cin >> n >> k;
  f[0] = 1;
  for (int i = 0; i <= n; i++) c[i][0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= i; j++)
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
  for (int i = 1; i <= k; i++) {
    int a;
    cin >> a;
    memset(g, 0, sizeof g);
    for (int j = 0; j <= n; j++) {
      for (int k = 0; k <= a; k++) {
        if (j + k > n) break;
        g[j + k] = (g[j + k] + f[j] * c[n - j][k] % mod * c[n - k][a - k]) % mod;
      }
    }
    memcpy(f, g, sizeof g);
  }
  cout << f[n] << "\n";
}
```

---

## 作者：ttq012 (赞：0)

upd：补充了一下 dp 的过程。

设 $f_{i,j}$ 表示第 $i$ 天，前 $i$ 天有 $j$ 个孩子有糖果。则枚举今天有新的 $k$ 个孩子得到糖果，剩下的人为以前就有糖果的人即 $n-k$ 直接用基础组合数来转移 dp 即可。时间复杂度为 $O(n^2k)$，可以通过。

具体的来说：首先维护逆元来求组合数，然后开始 dp：

初始状态：显然有 $f_{0,0}=1$。

答案：显然为 $f_{k,n}$。

转移（最困难的部分）：枚举 $i$ 表示当前是第 $i$ 天，$j$ 表示前 $i-1$ 天中，共计有 $j$ 个不同的孩子得到的至少一个糖果。转移则可以先枚举 $k$ 个人表示这 $k$ 个人和之前得到至少一个糖果的 $j$ 个人没有任何交集，另外的 $a_i-k$ 个人即可以从剩下的人中随便选取出来。

其中 $k$ 个之前没有有过糖果的人可以用 $\binom{n-j}{k}$ 来表示（即从剩下的 $n-j$ 个人中选取 $k$ 个人），另外随便选取的 $a_i-k$ 个人可以用 $\binom{n-k}{a_i-k}$ 来表示。根据乘法原理有 dp 转移式 $f_{i,j+k}=\sum(f_{i-1,j}\times\binom{n-j}{k}\times \binom{n-k}{a_i-k})$。因为 $n$ 和 $k$ 都很小所以直接暴力转移时间复杂度也是对的，为 $O(n^2k)$。

```cpp
void runtest() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < 2; i++)
        fac[i] = inv[i] = ifac[i] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
    f[0][0] = 1;
    for (int i = 1; i <= k; i++)
        cin >> a[i];
    for (int i = 1; i <= k; i++)
        for (int j = 0; j <= n; j++)
            for (int p = 0; p <= a[i]; p++)
                if (j + p <= n)
                    f[i][j + p] = (f[i][j + p] + f[i - 1][j] * binom(n - j, p) % mod * binom(n - p, a[i] - p) % mod) % mod;
    cout << f[k][n] << '\n';
}

---

