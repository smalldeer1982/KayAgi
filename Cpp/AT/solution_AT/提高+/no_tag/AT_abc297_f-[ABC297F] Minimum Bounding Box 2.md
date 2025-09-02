# [ABC297F] Minimum Bounding Box 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc297/tasks/abc297_f

縦 $ H $ 行、横 $ W $ 列のグリッドがあります。

このグリッドから一様ランダムに $ K $ 個のマスを選びます。選んだマスを全て含むような（グリッドの軸に辺が平行な）最小の長方形に含まれるマスの個数がスコアとなります。

得られるスコアの期待値を $ \text{mod\ }998244353 $ で求めてください。

  有理数 $ \text{mod\ }998244353 $ とは 求める期待値は必ず有理数となることが証明できます。 またこの問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ H,W\ \leq\ 1000 $
- $ 1\leq\ K\ \leq\ HW $
- 入力はすべて整数
 
### Sample Explanation 1

マス $ (1,1) $ とマス $ (2,2) $ が選ばれた場合、またはマス $ (1,2) $ とマス $ (2,1) $ が選ばれた場合の $ 2 $ 通りではスコアは $ 4 $ となります。また、それ以外の $ 4 $ 通りではスコアは $ 2 $ となります。 よって得られるスコアの期待値は $ \frac{4\ \times\ 2\ +\ 2\ \times\ 4}\ {6}\ =\ \frac{8}{3} $ であり、$ 665496238\ \times\ 3\ \equiv\ 8\pmod{998244353} $ なので $ 665496238 $ が答えとなります。

## 样例 #1

### 输入

```
2 2 2```

### 输出

```
665496238```

## 样例 #2

### 输入

```
10 10 1```

### 输出

```
1```

## 样例 #3

### 输入

```
314 159 2653```

### 输出

```
639716353```

# 题解

## 作者：2huk (赞：9)

upd on 2025/1/22：因原文章错误太多且太过啰嗦，重构整篇文章。原版存档[在这](https://www.luogu.com.cn/paste/9nzx4cqp)。

---

令 $f(n, m)$ 表示有多少种放 $k$ 枚棋子的方案，使得每条边上都至少有一枚棋子。那么答案显然是 $\sum_{i=1}^n\sum_{j=1}^m f(i,j) \times i \times j \times (n-i+1) \times (m-j+1)$。考虑求解 $f(n, m)$。

考虑容斥。总方案数是 $\dbinom {nm}k$。

如果一条边上没有棋子：

- 上边或下边没有：方案数为 $2 \times \dbinom {(n-1)m}k$。
- 上边或下边没有：方案数为 $2 \times \dbinom {(m-1)n}k$。

如果两条边上没有棋子：

- 上下没有：方案数为 $\dbinom {(n-2)m}k$。
- 左右没有：方案数为 $\dbinom {(m-2)n}k$。
- 上/下、左/右没有：方案数为 $4 \times \dbinom {(n-1)(m-1)}k$。

如果三条边上没有棋子：

- 左右上或左右下没有：方案数为 $2 \times \dbinom {(n-1)(m-2)}k$。
- 上下左或上下右没有：方案数为 $2 \times \dbinom {(m-1)(n-2)}k$。

如果四条边上都没有棋子，显然方案数为 $\dbinom {(n-2)(m-2)}k$。

然后容斥加减即可。

```cpp
int calc(int n, int m, int k) {
	int a, b, c, d, e, res;
	
	a = C(n * m, k);
	b = add(mul(2, C((n-1) * m, k)), mul(2, C(n * (m-1), k)));
	c = add(C((n-2) * m, k), C(n * (m-2), k), mul(4, C((n-1) * (m-1), k)));
	d = add(mul(2, C((n-1) * (m-2), k)), mul(2, C((n-2) * (m-1), k)));
	e = C((n-2) * (m-2), k);
	
	return add(add(a, -b, c), -d, e);
}
```

---

## 作者：OIer_Eternity (赞：7)

提供一个非常简单的思路。

首先看到期望值，可以转化为求方案数。

而题目要求的是矩形的面积，则只与矩形的长和宽有关。

那么我们可以设 $f_{i,j}$ 表示最小矩形的长为 $i$，宽为 $j$ 的方案数。

首先，如果不考虑矩形是最小的，方案数就为 $\binom {i\times j}k$。

而我们需要减去不合法的，也就是能被更小的矩形包含。

所以我们考虑枚举更小的 $i'\times j'$ 的矩形，它在 $i\times j$ 的矩形中有 $(i-i'+1)(j-j'+1)$ 个位置，而每个位置的方案数为 $f_{i',j'}$。因此：

$$
f_{i,j}=\binom {i\times j}k-\sum_{i'\le i,j'\le j,(i',j')\not=(i,j)}f_{i',j'}\times(i-i'+1)(j-j'+1)
$$

考虑如何优化。

先进行一些观察，当 $j\leftarrow j+1$ 时，第 $i'$ 行的 $f$ 数组贡献系数会增加 $i-i'+1$，从上到下依次递减。

这启发我们与前缀和有关。

设 $g_{i,j}=\sum\limits_{i'\le i,j'\le j}f_{i',j'}$，则：

$$
f_{i,j}=\binom {i\times j}k-\sum_{i'\le i,j'\le j}g_{i',j'}+f_{i,j}
$$

可以再进行一次前缀和！

设 $h_{i,j}=\sum\limits_{i'\le i,j'\le j}g_{i',j'}$，则：

$$
f_{i,j}=\binom {i\times j}k-h_{i,j}+f_{i,j}
$$

答案即为：

$$
\sum\limits_{1\le i\le n,1\le j\le m} f_{i,j}\times i\times j\times(n-i+1)\times(m-j+1)\over\binom{nm}k
$$

于是从 $O(n^2m^2)$ 优化到了 $O(nm)$，可以通过。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int p=998244353;
int n,m,k,f[1005][1005],sum[1005][1005],sum2[1005][1005],fac[1000005],ifac[1000005];
int qpow(int a,int b){
    int res=1;
    for (;b;b>>=1,a=1ll*a*a%p) if (b&1) res=1ll*res*a%p;
    return res;
}
int C(int n,int m){
    return 1ll*fac[n]*ifac[m]%p*ifac[n-m]%p;
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    fac[0]=1;
    for (int i=1;i<=n*m;i++) fac[i]=1ll*fac[i-1]*i%p;
    ifac[n*m]=qpow(fac[n*m],p-2);
    for (int i=n*m-1;~i;i--) ifac[i]=1ll*ifac[i+1]*(i+1)%p;
    int ans=0;
    for (int i=1;i<=n;i++) for (int j=1;j<=m;j++){
        if (i*j<k) continue;
        f[i][j]=C(i*j,k);
        (sum[i][j]+=sum[i-1][j])%=p;
        (sum[i][j]+=sum[i][j-1])%=p;
        (sum[i][j]+=p-sum[i-1][j-1])%=p;
        sum2[i][j]=sum[i][j];
        (sum2[i][j]+=sum2[i-1][j])%=p;
        (sum2[i][j]+=sum2[i][j-1])%=p;
        (sum2[i][j]+=p-sum2[i-1][j-1])%=p;
        (f[i][j]+=p-sum2[i][j])%=p;
        ans=(ans+1ll*f[i][j]*i%p*j%p*(n-i+1)%p*(m-j+1)%p)%p;
        (sum[i][j]+=f[i][j])%=p;
        (sum2[i][j]+=f[i][j])%=p;
    }
    printf("%d\n",1ll*ans*qpow(C(n*m,k),p-2)%p);
    return 0;
}
```

---

## 作者：Strelitzia_ (赞：6)

## 题目大意

一个 $n \times m$ 的网格，上面**随机**撒 $k$ 个不重复点，定义其权值为：能覆盖所有点的最小子矩形的面积。问这个权值的期望值。

-----

## 思路

有一种很强大的容斥做法。

考虑所有贡献 $\displaystyle\sum^{A}V = \sum_{i = 1}^n\sum_{j = 1}^mv_{i, j}\times 1$。

这里，$A$ 是所有子矩形，$V$ 是每个子矩形的大小，也就是每个子矩形的贡献。$v_{i,j}$ 表示 $(i, j)$ 能造成的贡献。我们考虑这样一个点：

![](https://cdn.luogu.com.cn/upload/image_hosting/0og726eb.png)

我们希望求出所有包含他的子矩形的数量（在剩下 $k - 1$ 个点随机时）。

然而这个看起来很难求啊！我们考虑容斥，及算出所有不包含他的子矩形的数量。显然，我们要让所有 $k$ 个点都在这个点上面 / 下面 / 左面 / 右面。例如在上面的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/k8m332mp.png)

假设这个点为 $(i, j)$，那么这时子矩形的数量为：

$$\dbinom{(i - 1)\times m}{k}$$

在下面 / 左面 / 右面的状况同理。

还有一个问题：我们可能算重。比如我们计算了左面和上面的贡献，左上角的子矩形就会被算重：

![](https://cdn.luogu.com.cn/upload/image_hosting/bj9v38df.png)

这时我们显然需要减去：

$$\dbinom{(i - 1) \times (j - 1)}{k}$$

综上，点 $(i, j)$ 的贡献为：

$$\dbinom{(i - 1) \times m}{k} + \dbinom{(n - i) \times m}{k} + \dbinom{(j - 1) \times n}{k} + \dbinom{(m - j) \times n}{k} - \dbinom{(i - 1) \times (j - 1)}{k} - \dbinom{(i - 1) \times (m - j)}{k} - \dbinom{(n - i) \times (j - 1)}{k} - \dbinom{(n - i) \times (m - j)}{k}$$

然后就可以 $\mathcal{O}(nm + k)$ 完成了。

```cpp
signed main() {
	n = read(), m = read(), k = read(), nm = n * m;
	inv[0] = phi[0] = 1;
	for (int i = 1; i <= nm; i++) phi[i] = phi[i - 1] * i % mod, inv[i] = ksm(phi[i], mod - 2);
	all = getC(nm, k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			int now = all;
			int nowres1 = md(getC((i - 1) * m, k) + getC((n - i) * m, k) + getC((j - 1) * n, k) + getC((m - j) * n, k));
			int nowres2 = md(getC((i - 1) * (j - 1), k) + getC((i - 1) * (m - j), k));
			nowres2 = md(nowres2 + getC((n - i) * (j - 1), k) + getC((n - i) * (m - j), k));
			now = md(now - (nowres1 - nowres2));
			ans = md(ans + now);
		}
	}
	printf("%lld", md(ans * ksm(all, mod - 2)));
}
```

---

## 作者：DE_aemmprty (赞：4)

### F - Minimum Bounding Box 2

**题目大意：**

在一个 $n \times m$ 的网格上随机撒 $k$ 个点，问使这 $k$ 个点能覆盖所有点的最小矩阵面积期望。

**数据范围：**

对于 $100\%$ 的数据：

- $1 \leq n, m \leq 1000$
- $1 \leq k \leq nm$

**解法分析：**

考虑每一个点对整体的贡献，那么问题就转化成了有多少个包含一个点的矩阵。

设当前正在考虑点 $(i,j)$，那么正难则反，计算有多少个不包含此点的矩阵。

考虑四个方向。假设现在 $k$ 个点都分布在 $(i,j)$ 的上方，那么容易得出 $\binom{(i - 1) \times m}{k}$。

其他三个方向同理，总共得出 $A = \binom{(i - 1) \times m}{k} + \binom{(n - i) \times m}{k} + \binom{(j - 1) \times n}{k} + \binom{(m-j)\times n}{k}$

但是，我们发现这四种情况并不是一一独立的。比如，上方和左方时，如果 $k$ 个点全部坐落于左上角，那么会被算两次。所以，还需要通过容斥原理嘎掉，即 $B = \binom{(i - 1) \times (j - 1)}{k} + \binom{(n - i) \times (j - 1)}{k} + \binom{(i - 1) \times (m - j)}{k} + \binom{(n - i) \times (m - j)}{k}$。

前面，我们又考虑了正难则反，所以我们要算出来 $k$ 个点分布在整个棋盘组成的矩形数量，即 $C = \binom{n \times m}{k}$。

综上，点 $(i,j)$ 对整体的贡献即 $C - (A - B) = C - A + B$。

注意组合数要预处理，不然会 TLE。

**AC Code：**

```cpp
# pragma GCC optimize(2)
# pragma GCC optimize(3)
# include <bits/stdc++.h>
using namespace std;

# define int long long
# define f(i,a,b) for(int i = a; i <= b; i ++)
# define g(i,b,a) for(int i = b; i >= a; i --)
# define CI const int

CI mod = 998244353;

int n, m, k;
int inv[1000007];
int c[1000007];

int ksm(int x, int y){
	if (y == 0) return 1;
	int res = ksm(x, y / 2);
	if (y & 1) return res * res % mod * x % mod;
	return res * res % mod;
}

int cal(int x, int y){
	if (x < y) return 0;
	return inv[x] * ksm(inv[x - y] * inv[y] % mod, mod - 2) % mod;
}

int binom(int x, int y){ return c[x];}

signed main(){
	cin >> n >> m >> k;
	inv[0] = 1;
	f (i, 1, n * m) inv[i] = inv[i - 1] * i % mod;
	f (i, 0, n * m) c[i] = cal(i, k);
	int ans = 0;
	f (i, 1, n){
		f (j, 1, m){
			int A = binom((i - 1) * m, k) + binom((n - i) * m, k) + binom((j - 1) * n, k) + binom((m - j) * n, k);
			int B = binom((i - 1) * (j - 1), k) + binom((i - 1) * (m - j), k) + binom((n - i) * (j - 1), k) + binom((n - i) * (m - j), k);
			int C = binom(n * m % mod, k);
			A %= mod, B %= mod;
			ans = (ans + (C - A + B + mod) % mod) % mod; 
		}
	}
	printf("%lld\n", (ans * ksm(binom(n * m % mod, k), mod - 2) % mod));
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

组合数学+容斥。

我们先表示出 $\mathbb{E}(s)$：

$$
\mathbb{E}(s) = \sum_{r = 1}^H\sum_{c = 1}^W\mathbb{P}[(r, c)]
$$

接下来我们深入分析 $\mathbb{P}[(r, c)]$。

对于一个特定的单元格 $(r, c)$，它位于最小包围矩形内的条件是：

- 存在至少一个点在第 $1$ 行到第 $r$ 行之间。
- 存在至少一个点在第 $r$ 行到第 $H$ 行之间
- 存在至少一个点在第 $1$ 列到第 $c$ 列之间。
- 存在至少一个点在第 $c$ 列到第 $W$ 列之间。

我们分别将这 $4$ 个条件记为事件 $A,B,C,D$，则 $\mathbb{P}[(r, c)]$ 就是：

$$
\begin{aligned}
\mathbb{P}[(r, c)] &= \mathbb{P}(A \cap B \cap C \cap D) \\ &= 1 - \mathbb{P}(\overline{A \cap B \cap C \cap D}) \\ &= 1 - \mathbb{P}(A^c \cup B^c \cup C^c \cup D^c) \\
&= 1 - [\mathbb{P}(A^c) + \mathbb{P}(B^c) + \mathbb{P}(C^c) + \mathbb{P}(D^c) - \mathbb{P}(A^c \cap B^c) - \mathbb{P}(A^c \cap C^c) - \mathbb{P}(A^c \cap D^c) - \mathbb{P}(B^c \cap C^c) - \mathbb{P}(B^c \cap D^c) - \mathbb{P}(C^c \cap D^c) + \mathbb{P}(A^c \cap B^c \cap C^c) + \mathbb{P}(A^c \cap B^c \cap D^c) + \mathbb{P}(A^c \cap C^c \cap D^c) + \mathbb{P}(B^c \cap C^c \cap D^c) - \mathbb{P}(A^c \cap B^c \cap C^c \cap D^c)
].
\end{aligned}
$$

乍看这个式子很复杂，实际上我们可以消掉一些概率为 $0$ 的事件。

- $A^c$ 和 $B^c$：不可能同时发生，因为 $A^c$ 表示所有点的行号都大于 $r$，而 $B^c$ 表示所有点的行号都小于 $r$，两者产生矛盾。$C^c$ 和 $D^c$ 同理。

- 同上，包含 $A^c \cap B^c$ 或 $C^c \cap D^c$ 的交集概率为 $0$。

所以：

$$
\mathbb{P}(A^c \cup B^c \cup C^c \cup D^c) = \mathbb{P}(A^c) + \mathbb{P}(B^c) + \mathbb{P}(C^c) + \mathbb{P}(D^c) - \mathbb{P}(A^c \cap C^c) - \mathbb{P}(A^c \cap D^c) - \mathbb{P}(B^c \cap C^c) - \mathbb{P}(B^c \cap D^c).
$$

综上，原式变为：

$$
\mathbb{P}(A \cap B \cap C \cap D) = 1 - [\mathbb{P}(A^c) + \mathbb{P}(B^c) + \mathbb{P}(C^c) + \mathbb{P}(D^c)] + [\mathbb{P}(A^c \cap C^c) + \mathbb{P}(A^c \cap D^c) + \mathbb{P}(B^c \cap C^c) + \mathbb{P}(B^c \cap D^c)].
$$

接下来开始计算各个概率项。

- $\mathbb{P}(A^c)$：所有 $K$ 个点的行号都大于 $r$。即这 $K$ 个点都位于行 $r+1$ 到行 $H$ 之间，共有 $W(H - r)$ 个单元格，故可得：

  $$
  \mathbb{P}(A^c) = \frac{\dbinom{W(H - r)}{K}}{\dbinom{HW}{K}}
  $$
- $\mathbb{P}(B^c)$：所有 $K$ 个点的行号都小于 $r$。即这 $K$ 个点都位于行 $1$ 到行 $r-1$ 之间，共有 $W(r - 1)$ 个单元格，故可得：

  $$
  \mathbb{P}(B^c) = \frac{\dbinom{W(r - 1)}{K}}{\dbinom{HW}{K}}
  $$

- $\mathbb{P}(C^c)$：所有 $K$ 个点的列号都大于 $c$。即这 $K$ 个点都位于列 $c+1$ 到列 $W$ 之间，共有 $H(W - c)$ 个单元格，故可得：

  $$
  \mathbb{P}(C^c) = \frac{\dbinom{H(W - c)}{K}}{\dbinom{HW}{K}}
  $$

- $\mathbb{P}(D^c)$：所有 $K$ 个点的列号都小于 $c$。即这 $K$ 个点都位于列 $1$ 到列 $c-1$ 之间，共有 $H(c - 1)$ 个单元格，故可得：

  $$
  \mathbb{P}(D^c) = \frac{\dbinom{H(c - 1)}{K}}{\dbinom{HW}{K}}
  $$

- $\mathbb{P}(A^c \cap C^c)$：所有 $K$ 个点的行号都大于 $r$ 且列号都大于 $c$。即这 $K$ 个点都位于行 $r+1$ 到行 $H$ 且列 $c+1$ 到列 $W$ 之间，共有 $(H - r)(W - c)$ 个单元格，故可得：

  $$
  \mathbb{P}(A^c \cap C^c) = \frac{\dbinom{(H - r)(W - c)}{K}}{\dbinom{HW}{K}}
  $$

- $\mathbb{P}(A^c \cap D^c)$：所有 $K$ 个点的行号都大于 $r$ 且列号都小于 $c$。即这 $K$ 个点都位于行 $r+1$ 到行 $H$ 且列 $1$ 到列 $c-1$ 之间，共有 $(H - r)(c - 1)$ 个单元格，故可得：

  $$
  \mathbb{P}(A^c \cap D^c) = \frac{\dbinom{(H - r)(c - 1)}{K}}{\dbinom{HW}{K}}
  $$

- $\mathbb{P}(B^c \cap C^c)$：所有 $K$ 个点的行号都小于 $r$ 且列号都大于 $c$。即这 $K$ 个点都位于行 $1$ 到行 $r-1$ 且列 $c+1$ 到列 $W$ 之间，共有 $(r - 1)(W - c)$ 个单元格，故可得：

  $$
  \mathbb{P}(B^c \cap C^c) = \frac{\dbinom{(r - 1)(W - c)}{K}}{\dbinom{HW}{K}}
  $$

- $\mathbb{P}(B^c \cap D^c)$：所有 $K$ 个点的行号都小于 $r$ 且列号都小于 $c$。即这 $K$ 个点都位于行 $1$ 到行 $r-1$ 且列 $1$ 到列 $c-1$ 之间，共有 $(r - 1)(c - 1)$ 个单元格，故可得：

  $$
  \mathbb{P}(B^c \cap D^c) = \frac{\dbinom{(r - 1)(c - 1)}{K}}{\dbinom{HW}{K}}
  $$

代入原式，得：

$$
\begin{aligned}
\mathbb{P}[(r, c)] &= 1 - \left[\frac{\dbinom{W(H - r)}{K} + \dbinom{W(r - 1)}{K} + \dbinom{H(W - c)}{K} + \dbinom{H(c - 1)}{K}}{\dbinom{H W}{K}}\right] + \left[\frac{\dbinom{(H - r)(W - c)}{K} + \dbinom{(H - r)(c - 1)}{K} + \dbinom{(r - 1)(W - c)}{K} + \dbinom{(r - 1)(c - 1)}{K}}{\dbinom{HW}{K}}\right] \\
&= \frac{\dbinom{H W}{K} - \left[\dbinom{W(H - r)}{K} + \dbinom{W(r - 1)}{K} + \dbinom{H(W - c)}{K} + \dbinom{H(c - 1)}{K} \right] + \left[\dbinom{(H - r)(W - c)}{K} + \dbinom{(H - r)(c - 1)}{K} + \dbinom{(r - 1)(W - c)}{K} + \dbinom{(r - 1)(c - 1)}{K} \right]}{\dbinom{HW}{K}}.
\end{aligned}
$$

将 $\mathbb{P}[(r, c)]$ 代入原式，得：

$$
\mathbb{E}(s) = \sum_{r = 1}^H\sum_{c = 1} ^ W \left\{\frac{\dbinom{H W}{K} - \left[ \dbinom{W(H - r)}{K} + \dbinom{W(r - 1)}{K} + \dbinom{H(W - c)}{K} + \dbinom{H(c - 1)}{K} \right] + \left[ \dbinom{(H - r)(W - c)}{K} + \dbinom{(H - r)(c - 1)}{K} + \dbinom{(r - 1)(W - c)}{K} + \dbinom{(r - 1)(c - 1)}{K} \right]}{\dbinom{HW}{K}}\right\}
$$

我们以 $O(HW + \log P)$ 的时间内处理完组合数后便可以在 $O(HW)$ 时间内求解答案，足以通过本题。

参考代码：

```cpp
#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 6, P = 998244353;

int power(int a, int b) {
    int res = 1;
    a %= P;
    while (b > 0) {
        if (b & 1) {
            res = res * a % P;
        }
        a = a * a % P;
        b >>= 1;
    }
    return res;
} 

int inv(int x) {
    return power(x, P - 2);
}

void solve() {
    int h, w, k;
    std::cin >> h >> w >> k;
    std::vector<int> fac(h * w + 1, 0);
    fac[0] = 1;
    for (int i = 1; i <= h * w; ++i) {
        fac[i] = fac[i - 1] * i % P;
    }
    std::vector<int> ifac(h * w + 1, 0);
    ifac[h * w] = inv(fac[h * w]);
    for (int i = h * w - 1; i >= 0; --i) {
        ifac[i] = ifac[i + 1] * (i + 1) % P;
    }
    auto comb = [&](int n, int m) -> int {
        return (n < m || m < 0 ? 0 : fac[n] * ifac[m] % P * ifac[n - m] % P);
    };
    int s = 0;
    int ic = inv(comb(h * w, k));
    for (int r = 1; r <= h; ++r) {
        for (int c = 1; c <= w; ++c) {
            int val = (comb(h * w, k) - comb((h - r) * w, k) - comb((r - 1) * w, k) - comb(h * (w - c), k) - comb(h * (c - 1), k)
                + comb((h - r) * (w - c), k) + comb((h - r) * (c - 1), k) + comb((r - 1) * (w - c), k) + comb((r - 1) * (c - 1), k)) % P;
            val = (val + P) % P;
            s = (s + val * ic % P) % P;
        }
    }
    std::cout << s << "\n";
}

int32_t main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0), std::cout.tie(0);

  int t;
  // std::cin >> t;
  t = 1;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

## 作者：white_tiger_yyyy (赞：1)

容斥真有趣。

有一个性质：

+ 两个相同的子矩阵，对答案的贡献一定相同。

所以就只需要枚举矩阵大小即可。

我们设当前矩阵长 $i$ 宽 $j$（对应的，$H$ 为长，$W$ 为宽），假如要给答案做出贡献，矩阵的四条边一定都有点，发现可以容斥了。

1. 至少 $0$ 条边上有点的方案数为 $a=C_{i\times j}^k$。
2. 至少 $1$ 条边上有点的方案数为 $b=2\times C_{(i-1)\times j}^k+2\times C_{i\times(j-1)}^k$。
3. 至少 $2$ 条边上有点的方案数为 $c=4\times C_{(i-1)\times(j-1)}^k+C_{(i-2)\times j}^k+C_{i\times(j-2)}^k$。
4. 至少 $3$ 条边上有点的方案数为 $d=2\times C_{(i-1)\times(j-2)}^k+2\times C_{(i-2)\times(j-1)}^k$。
5. 至少 $4$ 条边上有点的方案数为 $e=C_{(i-2)\times(j-2)}^k$。

根据容斥，答案应为 $a-b+c-d+e$。

长 $i$ 宽 $j$ 的矩阵有 $(H-i+1)\times(W-j+1)$ 个，每个大小为 $i\times j$，所以贡献即为：

$$
(a-b+c-d+e)\times(H-i+1)\times(W-j+1)\times i\times j
$$

时间复杂度 $O(HW)$。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll p=998244353;
const int N=1005;
ll qpow(ll x,int y){
    ll re=1;
    while(y){
        if(y&1) re=re*x%p;
        x=x*x%p;
        y>>=1;
    }return re;
}ll n,m,k,sum;
ll jc[N*N],inv[N*N];
void init(){
    jc[0]=inv[0]=1;
    for(ll i=1;i<=n*m;i++){
        jc[i]=jc[i-1]*i%p;
        inv[i]=qpow(jc[i],p-2);
    }
}ll C(int x,int y){
    if(x<y) return 0;
    if(!y||x==y) return 1;
    return jc[x]*inv[y]%p*inv[x-y]%p;
}int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>k;
    if(k==1){
        cout<<1;
        return 0;
    }init();
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++){
            if(i*j<k) continue;
            ll x=C(i*j,k);
            x=((x-2*C((i-1)*j,k)%p)%p+p)%p;
            x=((x-2*C((j-1)*i,k)%p)%p+p)%p;
            x=(x+4*C((i-1)*(j-1),k)%p)%p;
            x=(x+C((i-2)*j,k)+C((j-2)*i,k))%p;
            x=((x-2*C((i-1)*(j-2),k))%p+p)%p;
            x=((x-2*C((i-2)*(j-1),k))%p+p)%p;
            x=(x+C((i-2)*(j-2),k))%p;
            sum=(sum+(n-i+1)*(m-j+1)*i*j%p*x%p)%p;
        }
    cout<<sum*qpow(C(n*m,k),p-2)%p;
    return 0;
}
```

---

## 作者：robinyqc (赞：1)

### 题意简述

定义 $(a,b)$ 表示网格中从上往下数第 $a$ 个，从左往右数第 $b$ 个方格。你需要在网格 $V=\{(x,y)|x\in[1,H],y\in[1,W],x,y\in\mathbb{N}\}$ 中**等概率**随机选择 $K$ 个互不相同的方格。求这 $K$ 个点的最小覆盖矩形 $R$ 覆盖方格的个数 $S_R$ 的期望。这里 $R$ 满足边都平行于网格的基准线。

### 解题思路

我们发现若要找出 $R$，实在是有些麻烦。一个很好的思路是，因为每种选方格方式的概率都是一样的，于是把期望表示成：
$$
E(S_R)=\frac{\text{（每种选方格情况下矩形覆盖方格个数的和）}}{\text{（选方格的情况总数）}}
$$
但可以发现这也并不是特别好求。不妨思考：如何把抽象的、不确定位置的矩形，转化成**确切的**、已知的信息？我们发现：
$$
{\text{（每种选方格情况下矩形覆盖方格个数的和）}}=\sum_{P\in V}{\text{（所有情况下覆盖方格 } P \text{ 的矩阵个数）}}
$$
也就是说，我们只需要做到求单个方格被覆盖的次数，就可以求解全局的答案。

但是令人不爽的是，就算具体到如此程度，也不是很好求。考虑**正难则反**，求所有情况下**不覆盖**方格 $P(a,b)$ 的矩形个数。这个就很好求了。设选出的方格的集合是 $C(C\subseteq V,|C|=K)$，则应当满足
$$
\begin{aligned}
&\forall (x,y)\in C,x<a,\\
&\forall (x,y)\in C,x>a,\\
&\forall (x,y)\in C,y<b,\\
&\forall (x,y)\in C,y>b.\\
&\end{aligned}
$$
中的**至少一条**。

但是我们发现可能会重复统计完全在左上、左下、右上、右下的情况。容斥一下就可以了。具体实现可以见下面的代码。

### 代码实现

```cpp
#include<cstdio>
#include<iostream>
#include<vector>

//此处省略 10000 字快读。

#define int long long
#define R myio::read_int() 
//也就是说，后面的 R 表示读入一个整数。

const int S=1e6,P=998244353;

int fac[S+6],inv[S+6];
int Qpow(int x,int y) {
	int ret=1;
	for(;y>0;y>>=1) {
		if(y&1) (ret*=x)%=P;
		(x*=x)%=P;
	} return ret;
}
void pret() { //预处理阶乘与阶乘逆元。
	fac[0]=1;
	for(int i=1;i<=S;i++) fac[i]=fac[i-1]*i%P;
	inv[S]=Qpow(fac[S],P-2);
	for(int i=S-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%P;
}

int C(int n,int m) {
	if(n<m) return 0;
	return fac[n]*inv[m]%P*inv[n-m]%P;
}

signed main() {
	pret();
	int h=R,w=R,k=R,cnt=C(h*w,k);
	int invcnt=Qpow(cnt,P-2);
	cnt=cnt*h%P*w%P; //这里就是计算的“选方格的情况总数”。
	for(int i=1;i<=h;i++) for(int j=1;j<=w;j++) {
		int lx=C((i-1)*w,k),ux=C((h-i)*w,k);
		int ly=C((j-1)*h,k),uy=C((w-j)*h,k);
		//计算上文提到条件满足的矩形的个数。
		//l 指的是 "lower"，较小的；r 指的是 "upper"，较大的。
		int lxly=C((i-1)*(j-1),k),uxuy=C((h-i)*(w-j),k);
		int lxuy=C((i-1)*(w-j),k),uxly=C((h-i)*(j-1),k);
		//容斥，去掉重复的部分。
		(cnt-=(lx+ly+ux+uy-lxly-uxuy-lxuy-uxly))%=P;
	}
	myio::print_int(((cnt*invcnt)%P+P)%P);
	//因为取模有可能是负数，因此要转化成自然数。
	return 0;
}
```



---

## 作者：KingPowers (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc297_f)

将期望理解为平均数，则期望就等于所有情况下的权值之和除以总数。

在 $n$ 行 $m$ 列的矩形中选 $k$ 个点，总方案数显然为 $\binom{nm}{k}$，因此我们关心权值和即可。

发现数据范围完全支持平方的复杂度，因此考虑枚举最终矩形的长宽，那么总权值就可以表示为（本题中权值即为围住扔的 $k$ 个点的矩形的面积）：

$$
\sum_{i=1}^n\sum_{j=1}^m(n-i+1)(m-j+1)\times calc(i,j,k)\times i\times j
$$

简单解释下：$i$ 和 $j$ 为枚举的长宽，$(n-i+1)(m-j+1)$ 为整个大矩形中 $i$ 行 $j$ 列子矩形的数量，$calc(i,j,k)$ 为扔 $k$ 个点使得框住它们的最小矩形大小为 $i\times j$ 的方案数，$i\times j$ 即为面积。

考虑如何去实现出来这个 $calc(i,j,k)$，其实它的等价问题可以描述为：在 $i$ 行 $j$ 列的矩形中选 $k$ 个点，使得矩形的四个边界都至少与一个被选中的点相邻的方案数。

先补集转化下，用总数减去至少一条边不符合的方案数。然后答案其实就可以表示为：

$$
\begin{aligned}
\text{总方案数}&-\text{钦定 $1$ 条边不合法的方案数}+\text{钦定 $2$ 条边不合法的方案数} \\
&-\text{钦定 $3$ 条边不合法的方案数}+\text{钦定 $4$ 条边不合法的方案数}
\end{aligned}
$$

发现这五个东西都是好算的，于是做完了。

时间复杂度 $O(nm)$。

[提交记录](https://atcoder.jp/contests/abc297/submissions/45987274)

---

