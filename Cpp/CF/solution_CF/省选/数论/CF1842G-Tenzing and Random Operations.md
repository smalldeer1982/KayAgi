# Tenzing and Random Operations

## 题目描述

Yet another random problem.



Tenzing has an array $ a $ of length $ n $ and an integer $ v $ .

Tenzing will perform the following operation $ m $ times:

1. Choose an integer $ i $ such that $ 1 \leq i \leq n $ uniformly at random.
2. For all $ j $ such that $ i \leq j \leq n $ , set $ a_j := a_j + v $ .

Tenzing wants to know the expected value of $ \prod_{i=1}^n a_i $ after performing the $ m $ operations, modulo $ 10^9+7 $ .

Formally, let $ M = 10^9+7 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output the integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

There are three types of $ a $ after performing all the $ m $ operations :

1\. $ a_1=2,a_2=12 $ with $ \frac{1}{4} $ probability.

2\. $ a_1=a_2=12 $ with $ \frac{1}{4} $ probability.

3\. $ a_1=7,a_2=12 $ with $ \frac{1}{2} $ probability.

So the expected value of $ a_1\cdot a_2 $ is $ \frac{1}{4}\cdot (24+144) + \frac{1}{2}\cdot 84=84 $ .

## 样例 #1

### 输入

```
2 2 5
2 2```

### 输出

```
84```

## 样例 #2

### 输入

```
5 7 9
9 9 8 2 4```

### 输出

```
975544726```

# 题解

## 作者：namelessgugugu (赞：49)

组合意义保平安。

#### 题意

有一个长度为 $n$ 的数组 $a$ 和常数 $v$，对数组进行 $m$ 次操作，每一次操作中，均匀随机一个 $[1, n]$ 中的整数 $p$，对于所有 $p \leq i \leq n$，让 $a_i \gets a_i + v$，求最后 $\prod\limits_{i=1}^n a_i$ 的期望值，对 $10^9 + 7$ 取模。

$1 \leq n \leq 5000, 1 \leq m, v, a_i \leq 10^9$。

#### 题解

考虑 $\prod a_i$ 的组合意义，相当于有一个 $n+1$ 个点顺次连接形成的道路，一个人从第 $1$ 个点出发，从第 $i$ 个点走到第 $i+1$ 个点有 $a_i$ 种方案，问这个人走到 $n+1$ 共有多少种方案。

而修改的意义是什么呢，相当于在 $p$ 处放下了一个神奇妙妙工具，这个人走到 $p$ 的时候会拿起这个工具，之后对于任意的 $i$，可以选一个手上有的工具以 $v$ 的方案数从 $i$ 走到 $i+1$。

注意到被使用过的工具数量不超过 $n$，可以考虑在 DP 时记录这个状态，复杂度应该能降下来。

具体地，定义 $f_{i, j}$ 表示考虑了前 $i$ 处，使用了 $j$ 个工具的方案数，转移分三类：

1. 使用 $a_{i+1}$，$f_{i + 1, j} \gets f_{i, j} \cdot a_{i+1}$；
2. 使用一个被使用过的工具，$f_{i+1, j} \gets f_{i, j} \cdot j \cdot v$；
3. 使用一个还未被使用过的工具，需要先确定这个工具是哪里来的，$f_{i+1, j+1} \gets f_{i, j} \cdot (i+1) \cdot (m-j)\cdot v$。

最后的答案即为 $\sum\limits_i \frac{f_{n, i}}{n^i}$。

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
typedef unsigned long long ull;
const int N = 5005, mod = 1000000007;
int n, m, v, a[N], f[N][N];
inline int qpow(int x, int y)
{
    int res = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod)
        if (y & 1)
            res = 1ll * res * x % mod;
    return res;
}
int main(void)
{
    scanf("%d%d%d", &n, &m, &v);
    for (int i = 1; i <= n;++i)
        scanf("%d", a + i);
    f[0][0] = 1;
    for (int i = 0;i < n;++i)
        for (int j = 0; j <= std::min(m, i);++j)
        {
            f[i + 1][j] = (f[i + 1][j] + 1ll * f[i][j] * a[i + 1]) % mod;
            f[i + 1][j] = (f[i + 1][j] + 1ll * f[i][j] * j % mod * v) % mod;
            f[i + 1][j + 1] = (f[i + 1][j + 1] + 1ll * f[i][j] * (i + 1) % mod * v % mod * (m - j)) % mod;
        }
    int res = 0;
    int iv = qpow(n, mod - 2);
    for (int i = 0; i <= std::min(n, m); ++i)
        res = (res + 1ll * f[n][i] * qpow(iv, i)) % mod;
    printf("%d\n", res);
    return 0;
}
```

---

## 作者：Alex_Wei (赞：25)

### *[CF1842G Tenzing and Random Operations](https://www.luogu.com.cn/problem/CF1842G)

太妙了，太妙了。这个 “系数等用到了再算，没用到的东西不区分” 的思想很妙啊！这个乘法分配律解释乘法的思想（组合意义）很妙啊！

将 $\prod (a_i + v + \cdots)$ 用乘法分配律拆开，每个 $a_i + v + \cdots$ 选一项产生贡献，那么只有三种情况：

- 选择 $a_i$，贡献系数 $a_i$。
- 选择以前钦定过的操作对应的 $v$，贡献系数 $j\times v$，其中 $j$ 表示已经钦定过的操作。
- 选择以前没有钦定过的操作对应 $v$，贡献系数 $(m - j) \times i\times v$。$m - j$ 表示在没有钦定的操作中任选一个钦定，$i$ 表示该操作对应 $1\sim i$ 当中的哪个位置。

也就是说，没有被钦定的操作不作区分，也不计算它们的贡献系数。而被钦定的操作数量很少，这样就可以 DP 了：

设 $f_{i, j}$ 表示长度为 $i$ 的前缀钦定了 $j$ 个操作的答案，有转移式：
$$
\begin{aligned}
f_{i, j} (a_i + jv)\to f_{i + 1, j} \\
f_{i, j} (m - j) i v \to f_{i + 1, j + 1}
\end{aligned}
$$
最后枚举 $0\leq j\leq \min(n, m)$，剩下 $m - j$ 个操作随便钦定位置，因此答案为
$$
\frac {\sum _{0\leq j\leq \min(n, m)} f_{n, j} n ^ {m - j}} {n ^ m}
$$
时间复杂度 $\mathcal{O}(n ^ 2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ull = unsigned long long;

bool Mbe;
// mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rnd(0);
int rd(int l, int r) {return rnd() % (r - l + 1) + l;}

constexpr int mod = 1e9 + 7;
void addt(int &x, int y) {x += y, x >= mod && (x -= mod);}
int add(int x, int y) {return x += y, x >= mod && (x -= mod), x;}
int ksm(int a, int b) {
  int s = 1;
  while(b) {
    if(b & 1) s = 1ll * s * a % mod;
    a = 1ll * a * a % mod, b >>= 1;
  }
  return s;
}

constexpr int Z = 1e5 + 5;
int fc[Z], ifc[Z];
int bin(int n, int m) {
  if(n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
void init_fac(int Z) {
  for(int i = fc[0] = 1; i < Z; i++) fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[Z - 1] = ksm(fc[Z - 1], mod - 2);
  for(int i = Z - 2; ~i; i--) ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;
}

// ---------- template above ----------

constexpr int N = 5e3 + 5;

int n, m, v, a[N], f[N][N];
void solve() {
  cin >> n >> m >> v;
  f[0][0] = 1;
  for(int i = 1, a; i <= n; i++) {
    cin >> a;
    for(int j = 0; j <= min(n, m); j++) {
      addt(f[i][j], 1ll * f[i - 1][j] * (a + 1ll * j * v % mod) % mod);
      addt(f[i][j + 1], 1ll * f[i - 1][j] * (m - j) % mod * i % mod * v % mod);
    }
  }
  int ans = 0;
  for(int i = 0; i <= min(n, m); i++) {
    addt(ans, 1ll * f[n][i] * ksm(n, m - i) % mod);
  }
  ans = 1ll * ans * ksm(ksm(n, m), mod - 2) % mod;
  cout << ans << "\n";
}

bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  init_fac(Z);
  int T = 1;
  while(T--) solve();
  cerr << 1e3 * clock() / CLOCKS_PER_SEC << " ms\n";
  return 0;
}
```

---

## 作者：chengch (赞：10)

期望题太神秘了，组合意义搞错了几次，来写篇暴力推式子的题解。  
考虑设 $E_{n,m}$ 是答案；我们直接用期望的定义：概率 $\times$ 权值来求这个值。  
直接枚举 $i$ 位置总共被加了$x_i$ 个 $v$，有 $x_1+x_2+\cdots+x_n=m$，其所对应的概率就是 $\frac{1}{n^m}\frac{m!}{\prod_{i=1}^{n}x_i!}$，而权值是 $\prod_{i=1}^{n}(a_i+v\sum_{j=1}^{i}x_j)$，因此 $E_{n,m}=\frac{m!}{n^m}\sum_{x_1+x_2+\cdots x_n=m}\prod_{i=1}^{n}(\frac{a_i+v\sum_{j=1}^{i}x_j}{x_i!})$，考虑里面有 $\sum_{j=1}^{i}x_j$ 的项，我们不妨枚举 $x$ 的前缀和 $s$，这样就是 $E_{n,m}=\frac{m!}{n^m}\sum_{s_1\le s_2\le \cdots\le s_n=m}\prod_{i=1}^{n}\frac{a_i+vs_i}{(s_i-s_{i-1})!}$。  
这个式子依然不好处理，在尝试若干方法无果后，还是考虑找 $E_{n,m}$ 的递推式，先枚举 $s_{n-1}$ 的取值 $x$，那么 $E_{n,m}=\frac{m!}{n^m}\sum_{x=0}^{m}\frac{a_n+vm}{(m-x)!}\sum_{s_1\le s_2\le \cdots\le x}\prod_{i=1}^{n-1}\frac{a_i+vs_i}{(s_i-s_{i-1})!}$，注意到事实上 $\sum_{s_1\le s_2\le \cdots \le x}$ 这部分就是 $E_{n-1,x}\frac{(n-1)^x}{x!}$。  
由此我们得到了 $E$ 的递推式： $E_{n,m}=\frac{m!}{n^m}\sum_{x=0}^{m}\frac{a_n+vm}{(m-x)!}E_{n-1,x}\frac{(n-1)^x}{x!}$。考虑直接把 $n^m$ 这一项吸收 $E$ 里面，设 $g_{n,m}=E_{n,m}n^m$，（事实上一开始推时可能会想把 $m!$ 也吸收进去，但是下面这步就解释了我们为什么不这么做），那么 $g_{n,m}=m!\sum_{x=0}^{m}\frac{a_n+vm}{(m-x)!}g_{n-1,x}\frac{1}{x!}$，注意到 $\binom{m}{x}=\frac{m!}{x!(m-x)!}$，因此实际上 $g_{n,m}=\sum_{x=0}^{m}\binom{m}{x}(a_n+vx)g_{n-1,x}$。  
熟悉 EGF 的选手已经发现了，我们可以算 $g_{n}$ 和 $g_{n-1}$ 的 EGF 之间的关系，设 $G_{n}$ 是 $g_n$ 的 EGF，我们把左边看成两部分：$a_n\sum_{x=0}^{m}\binom{m}{x}g_{n-1,x}+vm\sum_{x=0}^{m}\binom{m}{x}g_{n-1,x}$，左边的 EGF 就是 $a_nG_{n-1}e^x$，右边多了一个 $m$，这并不难处理，设 $t_m=v
m\sum_{x=0}^{m}\binom{m}{x}g_{n-1,x}$，我们要求的是 $t$ 的 EGF，而已经知道了 $\frac{t_m}{m}$ 的 EGF 就是 $vG_{n-1}e^x$，而这个东西求导再乘 $x$ 就是 $t$ 的 EGF 了。  
加起来，我们就有 $G_n(x)=e^x\left( (a_n+vx)G_{n-1}(x)+vxG_{n-1}'(x)\right)$。  
现在问题转化成怎么求出 $G$，一开始我并没有看出来，于是选择去手玩一下样例，算出来第一组样例中 $G_2(x)=e^{2x}(50x^2+55x+4)$，由此合理猜测 $G_n(x)=e^{nx}F_n(x)$ 的形式，直接狂暴带入计算！我们得到 $F$ 的递推式 $F_n(x)=(a_n+nvx)F_{n-1}(x)+vxF_{n-1}'(x)$。  
归纳不难发现 $\deg F_n(x)=n$，因此我们可以暴力 $O(n^2)$ 算出 $F_n$。  
有了 $F_n$ 后，要计算 $\frac{m!}{n^m}[x^m]e^{nx}F_n(x)$，这是 $\frac{1}{n^m}\sum_{i=0}^{m}\binom{m}{i}F_{n,i}i!n^{m-i}$，由于 $\deg F_n=n$，因此 $i$ 可以只枚举到 $n$，而组合数就暴力乘一下，时间复杂度 $O(n^2)$。  


---

## 作者：Gorenstein (赞：8)

显然最终每个位置皆为 $a_i+kv$。直接枚举第 $i$ 个位置被选择了多少次，这是一个经典的多项式分布：

$$
\begin{aligned}
E&=\sum_{m_1+\cdots+m_n=m}\frac{1}{n^{m}}\binom{m}{m_1,\cdots,m_n}\prod_{i=1}^n\left(a_i+v\sum_{j=1}^im_j\right)\\
&=\frac{m!}{n^m}\sum_{m_1+\cdots+m_n=m}\frac{}{}\left(\prod_{i=1}^nm_i!\right)^{-1}\prod_{i=1}^n\left(a_i+v\sum_{j=1}^im_j\right).
\end{aligned}
$$

不妨设 $E_{i,j}$ 表示考虑前 $i$ 个数、操作 $j$ 次的期望，设 $s_i$ 为 $\{m_i\}$ 的前缀和。则

$$
\begin{aligned}
E_{n,m}&=\frac{m!}{n^m}\sum_{s_1\leqslant\cdots\leqslant s_n=m}\frac{}{}\prod_{i=1}^n\frac{a_i+vs_i}{(s_i-s_{i-1})!}\\
&=\frac{m!}{n^m}\sum_{s_{n-1}=0}^m\sum_{s_1\leqslant\cdots\leqslant s_{n-1}}\frac{a_n+vm}{(m-s_{n-1})!}\prod_{i=1}^{n-1}\frac{a_i+vs_i}{(s_i-s_{i-1})!}\\
&=\frac{m!}{n^m}\sum_{k=0}^m\frac{a_n+vm}{(m-k)!}\frac{(n-1)^k}{k!}E_{n-1,k}\\
&=\frac{1}{n^m}\sum_{k=0}^m\binom{m}{k}(n-1)^k(a_n+vm)E_{n-1,k}\,,
\end{aligned}
$$

即

$$
n^mE_{n,m}=(a_n+vm)\sum_{k=0}^m\binom{m}{k}\Big((n-1)^kE_{n-1,k}\Big).
$$

故设 

$$
G_n(z):=\sum\limits_{t\geqslant 0}n^tE_{n,t}\dfrac{z^t}{t!},\quad g_{n,t}=\left[\frac{z^t}{t!}\right]\!G_n(z),
$$

有

$$
\begin{aligned}
g_{n,t}&=(a_n+vt)\sum_{k=0}^t\binom{t}{k}g_{n-1,k}\\
\sum_{t=0}^{\infty}g_{n,t}\frac{z^t}{t!}&=a_nG_{n-1}(z)e^z+\sum_{t=0}^{\infty}vt\sum_{k=0}^t\binom{t}{k}g_{n-1,k}\frac{z^t}{t!}\\
G_n(z)&=a_nG_{n-1}(z)e^z+vz\,\frac{\text d}{\text dz}\!\left(\sum_{t=0}^{\infty}\frac{z^{t}}{t!}\sum_{k=0}^t\binom{t}{k}g_{n-1,k}\right)\\
G_n(z)&=a_nG_{n-1}(z)e^{z}+vz\big(G_{n-1}(z)e^z\big)'\\
G_{n}(z)&=(a_n+vz)G_{n-1}(z)e^{z}+vzG_{n-1}'(z)e^z.\\
\end{aligned}
$$

其初值为 $G_0(z)=1$。猜想 $G_n(z)$ 为 $e^{nz}p_n(z)$ 的形式，其中 $p_n(z)$ 是不超过 $n$ 次的多项式。多项式的微商是易求的。对于 $n=1$，结论显然成立。归纳：

$$
\begin{aligned}
G_{n}(z)&=(a_n+vz)e^{(n-1)z}p_{n-1}(z)e^{z}+vz\big((n-1)e^{(n-1)z}p_{n-1}(z)+e^{(n-1)z}p_{n-1}'(z)\big)e^z\\
&=e^{nz}\big((a_n+nvz)p_{n-1}(z)+vzp_{n-1}'(z)\big),
\end{aligned}
$$

可得

$$
p_n(z)=(a_n+nvz)p_{n-1}(z)+vz\,p'_{n-1}(z).
$$

由此可得结论正确，并且顺势 $O\big(n^2\big)$ 求出了 $p_n(z)$ 的迭代式。至此，我们只须求

$$
\frac{m!}{n^m}[z^m]e^{nz}p_{n}(z).
$$

它是

$$
\frac{m!}{n^m}\sum_{k=0}^m\frac{n^{m-k}}{(m-k)!}p_{n,k}=\sum_{k=0}^mm^{\underline{k}}n^{-k}p_{n,k}.
$$

---

## 作者：EuphoricStar (赞：7)

原来还不会这种拆期望的套路![](//图.tk/0)

设 $b_j$ 为第 $j$ 次操作中选择的 $i$，所求即为 $E(\prod\limits_{i = 1}^n (a_i + \sum\limits_{j = 1}^m [b_j \le i] \times v))$。

乘法也可以考虑拆期望。我们有最基础的性质 $E((a + b) \times (c + d)) = E(ac) + E(ad) + E(bc) + E(bd)$，这个也可以推广到多个数。于是最后拆成了若干个 $a_i$ 和若干个 $E([b_j \le i]) \times v$ 的积，求这些乘积的和。

如果对于同样的 $j$，要计算 $\prod\limits_{k = 1}^t E([b_j \le i_k]) \times v$，其中 $i_1 < i_2 < \cdots < i_t$，注意到我们只需要关心 $E([b_j \le i_1])$。因为如果它是 $0$，那整条式子的值就是 $0$；如果它不是 $0$，那后面的 $E([b_j \le i_{2 \sim t}])$ 都是 $1$。

到这里就可以 dp 了。设 $f_{i, k}$ 为，当前乘积的所有项中出现了 $k$ 个不同的 $j$，乘积的和。转移讨论 $i$ 是取 $a_i$ 还是某一项 $[b_j \le i] \times v$ 乘上去。如果是后者，还要讨论 $j$ 是不是当前第一次出现的，如果是，那么 $E(b_j \le i) = \frac{i}{n}$；否则 $E(b_j \le i) = 1$。

时间复杂度 $O(n^2)$。

[code](https://codeforces.com/contest/1842/submission/211011952)

---

## 作者：RockyYue (赞：4)

我们不妨求所有方案 $\prod a$ 的和再除以 $n^m$ 即为期望。

将操作用组合意义解释：

点 $0$ 到点 $1$ 有 $a_1$ 条路，点 $1$ 到点 $2$ 有 $a_2$ 条路……点 $n-1$ 到点 $n$ 有 $a_n$ 条路。一次在点 $i$ 的操作相当于在这里放置一个工具，到点 $i$ 立刻捡起，在 $i$ 及以后的任意点都可以用这个工具产生向下一个点的另外 $v$ 条道路，$\prod a$ 即为 $0$ 到 $n$ 的路径数。这里显然每个点上有多个工具，但是只能**选择一个来用**，所以我们定义**工具是互不相同的**，同时定义**使用一个工具**为从这个工具产生的 $v$ 条道路**之一**转移（即在捡到这个工具后每次都可以使用）。

这样的关系考虑 DP。

考虑操作过于复杂，这里我们对于具体点 $i$ 考虑是从上一个点的哪条路径转移过来的。这里可以从原本的 $a_{i}$ 条路径，也可以是从前面任意一个点上的工具。具体地，从 $0$ 到 $1$ 可以用原本的 $a_1$ 条，也可以用 $0$ 上的工具；从 $1$ 到 $2$ 可以用原本 $a_2$ 条，也可以用 $0$ 上的**任意一个**工具**或** $1$ 上的**任意一个**工具……

因为操作次数是恰好为 $m$，所以如果转移到 $n$ 的一条路径上如果用了 $i$ 个**不同的**工具，则另外 $m-i$ 次操作**任意选点**就好了，因为**这一条路径上没有涉及到其余的工具**，即路径数乘上 $n^{m-i}$。这启示我们记录当前路径中使用的工具个数。

设 $f_{i,j}$ 为走到 $i$，用了 $j$ 次工具的路径数，则转移有以下三种：

- 用原本 $a_i$ 条路径转移
	
    ```f[i][j] += f[i - 1][j] * a[i]```
- 用之前用过的工具转移

	```f[i][j] += f[i - 1][j] * j * v```
    
    这里 $\times j$ 表示从之前用过的 $j$ 个工具中任选一个，$\times v$ 表示在这个工具产生的 $v$ 条道路中任选一条。
- 用之前没用过的工具转移

	```f[i][j] += f[i - 1][j - 1] * i * (m - j + 1) * v```
    
    这里 $\times i$ 表示这个新工具是在哪里被捡起来的，可以是 $[1,i]$ 中任意一个点（因为工具两两不同）。
    
最后答案即为 $\frac{\sum_{i=0}^{\min\{n,m\}}{f_{n,i}\cdot n^{m-i}}}{n^m}$，实现中 $f$ 第一维可以滚动，时间复杂度 $O(n\min \{n,m\})$。

---

## 作者：Leasier (赞：4)

dp 会不了一点 /fn

------------

翻译一下题意，答案为 $\dfrac{\displaystyle\sum_b \prod_{i = 1}^n (a_i + v \displaystyle\sum_{j = 1}^m [b_j \leq i])}{n^m}$。

一个直观的想法是：设 $dp_{i, j}$ 表示考虑到 $a_1 \sim a_i$，有 $j$ 个 $t$ 满足 $b_t \leq i$ 的答案。

但这样时间复杂度就已经 $O(n \operatorname{poly}(m))$ 起步了，不能接受。

但是注意到我们可以通过**拆项**来描述这个式子：

- 令 $i = 1 \sim n$，每次考虑是否加入**一个** $b_t \leq i$。
- 若不加入，则将答案乘上当前贡献 $a_i + cnt \times v$；否则，我们有 $i$ 种方案选取一个 $\leq i$ 的数 $s$、还有 $m - cnt + 1$ 种方案填入 $b_t = s$，则将答案乘上当前贡献 $vi(m - cnt + 1)$，最后令 $cnt \leftarrow cnt + 1$。
- 若最终 $cnt \leq m$，则取到该方案的概率为 $\dfrac{1}{n^{cnt}}$。

模拟上述过程 dp 即可。时间复杂度为 $O(n^2)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 1e9 + 7;
int a[5007];
ll dp[5007][5007];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

int main(){
	int n, m, v;
	ll invn, cur_inv = 1, ans = 0;
	scanf("%d %d %d", &n, &m, &v);
	invn = quick_pow(n, mod - 2, mod);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++){
		for (int j = 0; j <= i; j++){
			dp[i][j] = dp[i - 1][j] * (a[i] + (ll)j * v % mod) % mod;
			if (j > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] * v % mod * i % mod * (m - j + 1) % mod) % mod;
		}
	}
	for (int i = 0; i <= n; i++){
		ans = (ans + dp[n][i] * cur_inv % mod) % mod;
		cur_inv = cur_inv * invn % mod;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：wcyQwQ (赞：3)

考虑用所有情况的和除以情况数来进行计算。

我们最后的答案肯定长这样 $\prod_i (a_i + v + \cdots +v)$，相当于我们从每个括号里面挑一个然后乘起来再求和。

记 $f_{i, j}$ 表示考虑到前 $i$ 个括号，已经使用了 $j$ 个操作的 $v$，所有情况的和。

我们考虑从当前括号选取什么来造成贡献。

1. 选择 $a_i$，那么 $f_{i, j} \gets f_{i - 1, j} \cdot a_i$。
2. 选择一个在这 $j$ 次操作中带来的 $v$，那么 $f_{i, j} \gets f_{i - 1, j} \cdot v$
3. 新选择一个操作的 $v$，那么我们可以从剩下的 $m - j + 1$ 个操作中选，每个操作只要作用在 $[1, i]$ 上的点就行，因此 $f_{i, j} \gets f_{i - 1, j - 1} \cdot (m - j + 1) \cdot i \cdot v$。

最后考虑如何统计答案，对于 $f_{n, j}$ 来说，我们只关心那 $j$ 个操作使用的位置，剩下的 $m - j$ 个操作随便选都没问题，所以贡献为 $f_{n, j} \cdot n^{m - j}$，最后的答案即为 $\dfrac{\sum_{j = 0}^{\min(n, m)} f_{n, j} \cdot n^{m - j}}{n^m}$。时间复杂度 $O(n^2)$。

[Code](https://codeforces.com/contest/1842/submission/218131102)



---

## 作者：Little09 (赞：3)

被薄纱了。

乘法的期望想必不好搞，拆贡献。可以把贡献写成一个 $(1+m)\times n$ 的表格的形式，第 $1$ 行是 $a_1,...,a_n$，往后第 $i$ 行是第 $i$ 次操作加的数，如果加到了就是 $v$ 否则是 $0$，那么贡献就是每一列选一个数乘起来的和。

拆开以后单独考虑一项怎么计算。我们会发现如果这一项中有两个来自同一行的变量，那么它们是不独立的；其他来自不同行的是独立的。但是考虑来自同一行的变量 $x_1,x_2$，我们发现 $E(x_1x_2)=E(x_1)v$，因为如果 $x_1=0$ 那么无所谓，如果 $x_1=v$ 那么一定有 $x_2=v$。所以这样就拆成了许多互相独立的变量，我们可以把每个变量的期望乘起来。

对上述过程 DP，我们注意到只需要注意到当前做到第几个数，还有目前已经有几行的变量已经被选过了。每次转移的时候考虑：选 $a_i$，选了一个选过的行的变量（此时期望是 $v$），选了一个没选过的行的变量（此时期望是容易算的）。

复杂度是 $O(n^2)$。

---

## 作者：ღꦿ࿐ (赞：3)

令 第 $i$ 次操作的位置为 $pos_i$，则要求下式的期望：

$$
\prod_{i\in[1,n]}(a_i+v\sum_{j\in[1,m]}[pos_j\leq i])
$$


拆式子，因为乘法分配律，每个括号里选一项的乘积对所有方案求和。

现在这个括号要么选 $a_i$，要么选一个 $v[pos_j\leq i]$。

关心目前选择 $v[pos_j\leq i]$ 的情况，注意我们是一项一项地从左到右选择括号内的东西，这个括号内的 $v[pos_j\leq i]$ 的选择方案之和之前选择了 $v[pos_j\leq i]$ 的项有关。

记录之前选择 $v[pos_j\leq i]$ 的项的不同的 $j$ 的个数为 $c$，即让 $f_{i,c}$ 表示前 $i$ 个括号，选择 $v[pos_j\leq i]$ 的项的不同的 $j$ 的个数为 $c$ 的乘积的期望，显然 $c$ 是 $\leq i$ 的。

接下来要么选择一个之前已经钦定 $\leq$ 某个更小的 $i$ 的 $v[pos_j\leq i]$，其方案数为 $c$，转移系数为 $c\times v$。

要么选择一个新的 $pos_j$ 并钦定其 $\leq i$，总共有 $m-c$ 种项可以选择，其 $pos\leq i$ 的概率是 $\frac i n$，所以转移系数为 $(m-c)\times v\times \frac i n$。

当然，选择 $a_i$ 的转移系数为 $a_i$。

时间复杂度 $O(n^2)$。

---

## 作者：dcmfqw (赞：1)

这个做法比较无脑，好像和正解推出来的式子是一样的。

设 $f_{i,j}$ 表示只考虑前 $i$ 个数，操作 $j$ 次的所有方案的权值和，那么把它转移到 $f_{i+1,k}$ 时，首先要考虑在原有的 $j$ 次中再插入 $k-j$ 个，然后再把所有方案乘个第 $i+1$ 个数的权值，即：

$$
f_{i+1,k}=(vk+a_{i+1})\sum\limits_{j=0}^kf_{i,j}\dbinom kj
$$

初始状态为 $f_{0,0}=1$，答案为 $\frac{f_{n,m}}{n^m}$，但是 $m$ 过大所以不能直接做。

由于有个类似归并的操作，考虑设 `EGF` 为 $F_i(x)=\sum\limits_{j=0}f_{i,j}\frac{x^j}{j!}$，然后转移可视为：

$$
F_i(x)=vx(e^xF_{i-1}(x))'+a_ie^xF_{i-1}(x)
$$

其中乘 $e^x$ 对应上面乘 $\dbinom kj$，求导再乘 $x$ 是为了把多项式第 $i$ 项系数乘 $i$。

初始状态为 $F_0(x)=1$，答案为 $\frac{[x^m]F_n(x)}{n^m}$。

手模一下会发现 $F_i(x)$ 可表示为 $\sum_{j=0}^ig_{i,j}x^je^{ix}$ 的形式，由于求导的线性性：

$$
F_i(x)=\sum\limits_{j=0}^{i-1}vx(e^xg_{i-1,j}x^je^{(i-1)x})'+a_ie^xg_{i-1,j}x^je^{(i-1)x}
$$

$$
=\sum\limits_{j=0}^{i-1}vxg_{i-1,j}(x^je^{ix})'+a_ig_{i-1,j}x^je^{ix}
$$

$$
=\sum\limits_{j=0}^{i-1}vxg_{i-1,j}jx^{j-1}e^{ix}+vxg_{i-1,j}ix^je^{ix}+a_ig_{i-1,j}x^je^{ix}
$$

$$
=\sum\limits_{j=0}^i((vj+a_i)g_{i-1,j}+vig_{i-1,j-1})x^je^{ix}
$$

这样可以归纳证明上面那个手模出来的结论，顺便有 $g_{i,j}=(vj+a_i)g_{i-1,j}+vig_{i-1,j-1}$，当然 $g_{i-1,-1}=g_{i-1,i}=0$，可以直接把 $F_n(x)$ 推出来，甚至能滚动数组。

然后求答案：

$$
\frac1{n^m}[x^m]F_n(x)
$$

$$
=\frac{m!}{n^m}[x^m]\sum\limits_{i=0}^ng_{n,i}x^ie^{nx}
$$

$$
=\frac{m!}{n^m}\sum\limits_{i=0}^n\frac{g_{n,i}}{(m-i)!}n^{m-i}
$$

$$
=\sum\limits_{i=0}^ng_{n,i}m^{\underline i}n^{-i}
$$

时间复杂度 $O(n^2)$。

---

## 作者：Llx2022 (赞：1)

考虑大力推式子。

设操作序列为 $b_1,b_2,\dots,b_m$，那么要求得就是 $E(\prod_{i=1}^n (a_i+v\sum_{j=1}^m[b_j\le i]))$。

考虑拆项，发现共有 $(m+1)^n$ 项，因此推出 $E(\prod_{i=1}^na_i+v^t\times [b_j\le i]\times \dots \times [b_t\le j]+\dots +a_i\times v^t \times [b_j\le i]\times \dots\times [b_t\le j])$，对于 $m$ 次操作中其中一次操作 $b_j$ 来说只有当 $b_j\le \min{id_{p1}\dots id_{p_t}}$ 才会对答案贡献。

根据期望线性性，直接考虑 dp，设 $dp_{i,j}$ 表示当前考虑完 $i$ 位，已经有 $j$ 个 $b$ 被限制住，通过确定 $1\rightarrow n$ 的递推顺序，能够确保转移无后效性，即之前被限制住的势必会影响后面的某一位。

那么考虑添加一个括号的影响。

- 添加 $a_{i+1}$，$f_{i+1,j}\leftarrow f_{i,j}\times a_{i+1}$

- 添加 $v[b_j\le i+1]$
  - 若选择的是限制里面的，那么有 $j$ 种选法，$f_{i+1,j}\leftarrow f_{i,j}\times v\times j$
  - 若不是限制中的，则就是对于剩下的 $m-j$ 个操作有 $P(b_k\le i+1)$ 的概率，即 $\frac{i+1}{n}$ 的概率添加一个新限制，$f_{i+1,j+1} \leftarrow f_{i,j} \times v\times (m-j) \times \frac{i+1}{n}$

# Code

```cpp
#include<iostream>
using namespace std;
template<typename T>inline void read(T &x){
    x=0;T f=1;char ch=getchar();
    while(ch<48||ch>57){if(ch=='-'){f=-1;}ch=getchar();}
    while(ch>=48&&ch<=57){x=x*10+ch-48;ch=getchar();}
    x*=f;
}
template<typename T>inline void write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
const int N=5e3+8;
#define int long long 
int f[N][N];
int n,m,v;
int a[N];
const int mod=1e9+7;
int qmi(int a,int b){
    int res=1;
    while(b){
        if(b&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod;
        b>>=1;
    }
    return res;
}
signed main(){
    read(n),read(m),read(v);
    for(int i=1;i<=n;i++) read(a[i]);
    f[0][0]=1;
    const int Q=qmi(n,mod-2);
    for(int i=0;i<n;i++){
        for(int j=0;j<=min(i,m);j++){
            f[i+1][j]=(f[i+1][j]+f[i][j]*a[i+1])%mod;
            f[i+1][j]=(f[i+1][j]+1ll*f[i][j]*v%mod*j%mod)%mod;
            f[i+1][j+1]=(f[i+1][j+1]+f[i][j]*v%mod*(m-j)%mod*(i+1)%mod*Q%mod)%mod;
        }
    }
    int ans=0;
    for(int j=0;j<=min(n,m);j++){
        ans=(ans+f[n][j])%mod;
    }
    write(ans);
    return 0;
}
```

---

## 作者：N2MENT (赞：0)

[blog](https://www.cnblogs.com/0x0620AF/articles/CF1842G.html)

md 三个月就忘了。

---

$$ans = \mathbb{E}\left(\prod_{i = 1}^{n} \left(a_i + v\sum_{j = 1} ^ m[b_j \leq i]  \right)\right)$$

拆。

每一位选 $a_i$ 或者 $v[b_j \leq i]$ 中的一个。

$f_{i, k}$。

考虑前 $i$ 个，选了 $k$ 个 $j$。

这一位选 $a_i$：

$f_{i, j} \leftarrow f_{i, j} + a_i\cdot f_{i - 1, j} $

这一位选原来有过的 $b_j$：

$f_{i, j} \leftarrow f_{i, j} + v\cdot j \cdot f_{i - 1, j} $

这一位选没选过的 $b_j$，可以选剩下的，每个 $\dfrac{i}{n}$ 概率是 $1$，带来贡献：

$f_{i, j} \leftarrow f_{i, j} +\dfrac{vi}{n} \cdot (m - j + 1) \cdot f_{i - 1, j - 1} $



```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
#define ll long long
    inline ll read() {
        char c = getchar();
        ll x = 0;
        bool f = 1;
        while(c < '0' || c > '9') {
            if(c == '-')
                f = 0;
            c = getchar();
        }
        while(c >= '0' && c <= '9') {
            x = (x << 1) + (x << 3) + (c ^ 48);
            c = getchar();
        }
        return f ? x : ~(x - 1);
    }
    inline void write(ll x) {
        if(x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if(x > 9)
            write(x / 10);
        putchar(x % 10 + '0');
    }
#undef ll
}
using IO::read;
using IO::write;
#define eb(x) emplace_back(x)
#define ep(x) emplace(x)
#define ld long double
#define ll long long
ll Pow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1)
            res *= a;
        a *= a, b >>= 1;
    }
    return res;
}
ll Pow(ll a, ll b, ll mod) {
    ll res = 1;
    while(b) {
        if(b & 1)
            res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return res;
}
const int maxn = 5010;
const int mod = 1e9 + 7;
int n, m, v;
int a[maxn];
int f[maxn][maxn];
int invn;
void Debug() {
#ifdef LOCAL
#endif
}
signed main() {
    n = read(), m = read(), v = read();
    invn = Pow(n, mod - 2, mod);
    for(int i = 1; i <= n; i++) a[i] = read();
    f[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i; j++) {
            f[i][j] = 1ll * f[i - 1][j] * (1ll * a[i] + 1ll * v * j % mod) % mod;
            if(j) f[i][j] = (f[i][j] + 1ll * f[i - 1][j - 1] * (m - j + 1) % mod * i % mod * invn % mod * v % mod) % mod;
        }
    }
    int ans = 0;
    for(int i = 0; i <= n; i++) ans = (ans + f[n][i]) % mod;
    write(ans);
    return 0;
}
```

---

