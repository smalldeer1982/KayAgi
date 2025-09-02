# Nauuo and Pictures (hard version)

## 题目描述

简单版与困难版的唯一区别在于数据范围。

Nauuo 是一个喜欢随机图片网站的女孩。

有一天，她自己制作了一个包含 $n$ 张图片的随机图片网站。

当 Nauuo 访问该网站时，她会看到且仅看到一张图片。网站展示每张图片的概率并不相同。第 $i$ 张图片有一个非负权值 $w_i$，第 $i$ 张图片被展示的概率为 $\frac{w_i}{\sum_{j=1}^n w_j}$。也就是说，图片被展示的概率与其权值成正比。

然而，Nauuo 发现有些她不喜欢的图片被展示得太频繁了。

为了解决这个问题，她想出了一个好主意：当她看到一张喜欢的图片时，她会将其权值加 $1$；否则，她会将其权值减 $1$。

Nauuo 将访问该网站 $m$ 次。她想知道所有 $m$ 次访问后，每张图片的期望权值是多少（对 $998244353$ 取模）。你能帮帮她吗？

第 $i$ 张图片的期望权值可以表示为 $\frac{q_i}{p_i}$，其中 $\gcd(p_i, q_i) = 1$。你需要输出一个整数 $r_i$，满足 $0 \le r_i < 998244353$ 且 $r_i \cdot p_i \equiv q_i \pmod{998244353}$。可以证明这样的 $r_i$ 存在且唯一。

## 说明/提示

在第一个样例中，如果唯一一次访问展示了第一张图片，概率为 $\frac{2}{3}$，最终权值为 $(1,1)$；如果展示了第二张图片，概率为 $\frac{1}{3}$，最终权值为 $(2,2)$。

因此，两张图片的期望权值都是 $\frac{2}{3} \cdot 1 + \frac{1}{3} \cdot 2 = \frac{4}{3}$。

因为 $332748119 \cdot 3 \equiv 4 \pmod{998244353}$，所以你需要输出 $332748119$，而不是 $\frac{4}{3}$ 或 $1.3333333333$。

在第二个样例中，只有一张图片是 Nauuo 喜欢的，所以每次访问都会将 $w_1$ 增加 $1$。

因此，期望权值为 $1 + 2 = 3$。

Nauuo 很调皮，所以她没有给出第三个样例的任何提示。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 1
0 1
2 1
```

### 输出

```
332748119
332748119
```

## 样例 #2

### 输入

```
1 2
1
1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 3
0 1 1
4 3 5
```

### 输出

```
160955686
185138929
974061117
```

# 题解

## 作者：zhylj (赞：9)

似乎和其他题解不太一样？

首先一个朴素做法（easy version）如下：

对每个照片 $x$，将照片分成三部分：$x$、喜欢的中不是 $x$ 的、不喜欢的中不是 $x$ 的，记 $f_x(i,j,k)$ 表示进行了 $i+j+k$ 次操作，这三部分分别被选中 $i,j,k$ 次的概率，不难得到转移方程，然后求出期望。

可以发现这样的复杂度是 $\mathcal O(nm^3)$ 的，无法通过 hard version，考虑优化。

考虑我们先求出，进行了 $i+j$ 次，所有喜欢的照片被选中 $i$ 次，不喜欢的被选中 $j$ 次的概率 $f(i,j)$，那么类似上面可以得到转移方程（显然有 $f(0,0)=1$）：
$$
f(i+1,j) \gets f(i,j)\cdot \frac{i+\sum w_k[a_k=1]}{i-j+\sum w_k},\quad f(i,j+1) \gets f(i,j)\cdot \frac{-j+\sum w_k[a_k=0]}{i-j+\sum w_k}
$$
那么现在我们已知喜欢的照片的期望权值和，不妨记作 $\mathbb E[S_1]$：
$$
\mathbb E[S_1]=\sum_{i+j=m} \left(i+\sum_{k=1}^n w_k[a_k=1]\right)f(i,j)
$$
我们要如何求得每个照片被选中次数的期望呢？

考虑将初始的所有照片抽象为拆成了 $\sum w_i$ 个权值为 $1$ 的照片，然后仍然进行上述的操作，这样就不难发现所有喜欢的照片的地位是相等的（同样，所有不喜欢的照片的地位也是相等的），也就是它们的期望权值必然相等，而我们又可以根据期望线性性把最后拆出来的的 $w_i$ 张照片的权值期望加起来得到原先照片的答案：
$$
\frac {w_i}{\sum w_j[a_j=1]}\mathbb E[S_1],\quad a_i=1
$$
对于不喜欢的照片的答案时类似的，这里不再赘述。

于是可以做到 $\mathcal O(n+m^2\log p)$ 或者 $\mathcal O(n+m^2)$ 的时间复杂度，其中 $p = 998244353$，取决于是否预处理逆元。



```cpp
const int N = 2e5 + 5, M = 3000 + 5, MOD = 998244353;

int QPow(int a, int b) {
	int ret = 1, bas = a;
	for(; b; b >>= 1, bas = 1LL * bas * bas % MOD)
		if(b & 1) ret = 1LL * ret * bas % MOD;
	return ret;
}

int n, m, a[N], w[N], f[M][M];
void Plus(int &x, int y) { x += y; x -= x >= MOD ? MOD : 0; }

int main() {
	rd(n, m);
	for(int i = 1; i <= n; ++i) rd(a[i]);
	int w_n = 0, w_p = 0;
	for(int i = 1; i <= n; ++i) {
		rd(w[i]);
		if(a[i]) Plus(w_p, w[i]);
		else Plus(w_n, w[i]);
	}
	f[0][0] = 1;
	for(int i = 0; i < m && i <= w_n; ++i)
		for(int j = 0; i + j < m; ++j) {
			int d = QPow((w_n + w_p - i + j) % MOD, MOD - 2);
			Plus(f[i + 1][j], 1LL * (w_n - i) * d % MOD * f[i][j] % MOD);
			Plus(f[i][j + 1], 1LL * (w_p + j) * d % MOD * f[i][j] % MOD);
		}
	int s_1 = 0, s_2 = 0;
	for(int i = 0; i <= m && i <= w_n; ++i) {
		int j = m - i;
		Plus(s_1, 1LL * f[i][j] * (w_n - i) % MOD);
		Plus(s_2, 1LL * f[i][j] * (w_p + j) % MOD);
	}
	for(int i = 1; i <= n; ++i) {
		int ans = 0;
		if(a[i]) ans = 1LL * s_2 * w[i] % MOD * QPow(w_p, MOD - 2) % MOD;
		else ans = 1LL * s_1 * w[i] % MOD * QPow(w_n, MOD - 2) % MOD;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：ouuan (赞：5)

**裸dp**

先只看一个“被喜欢的”位置，这个位置的初始值是 $w$。

计 $SA$ 为“被喜欢的”数之和，$SB$ 为“不被喜欢的”数之和。

令 $f_w[i][j][k]$ 表示：现在 $SA=j$，$SB=k$，一个值为 $w$ 、“被喜欢的”位置经过 $i$ 次操作后的期望值。

边界情况：$f_w[0][j][k]=w$。

转移：

1. 下一次操作选到了当前这个位置。概率：$\frac w{j+k}$。转移到：$f_{w+1}[i-1][j+1][k]$。
2. 下一次操作选到了另一个“被喜欢的”位置。概率：$\frac{j-w}{j+k}$。转移到：$f_w[i-1][j+1][k]$。
3. 下一次操作选到了一个“不被喜欢的”位置。概率：$\frac k{j+k}$。转移到：$f_w[i-1][j][k-1]$。

所以，$f_w[i][j][k]=\frac w{j+k}f_{w+1}[i-1][j+1][k]+\frac{j-w}{j+k}f_w[i-1][j+1][k]+\frac k{j+k}f_w[i-1][j][k-1]$。

令 $g_w[i][j][k]$ 表示“不被喜欢的”的对应状态，计算方式类似。

这样大约能过简单版。

**优化**

有两个优化：

1. $f_w[i][j][k]=wf_1[i][j][k]$

   证明：

   $i=0$ 时显然成立。

   假设已经证明了 $f_w[i-1][j][k]=wf_1[i-1][j][k]$，就可以归纳地证明 $f_w[i][j][k]=wf_1[i][j][k]$：

   $\begin{aligned}f_1[i][j][k]&=\frac 1{j+k}f_2[i-1][j+1][k]+\frac{j-1}{j+k}f_1[i-1][j+1][k]+\frac k{j+k}f_1[i-1][j][k-1]\\&=\frac2{j+k}f_1[i-1][j+1][k]+\frac{j-1}{j+k}f_1[i-1][j+1][k]+\frac k{j+k}f_1[i-1][j][k-1]\\&=\frac{j+1}{j+k}f_1[i-1][j+1][k]+\frac k{j+k}f_1[i-1][j][k-1]\end{aligned}$

   $\begin{aligned}f_w[i][j][k]&=\frac w{j+k}f_{w+1}[i-1][j+1][k]+\frac{j-w}{j+k}f_w[i-1][j+1][k]+\frac k{j+k}f_w[i-1][j][k-1]\\&=\frac{w(w+1)}{j+k}f_1[i-1][j+1][k]+\frac{w(j-w)}{j+k}f_1[i-1][j+1][k]+\frac {wk}{j+k}f_1[i-1][j][k-1]\\&=\frac{w(j+1)}{j+k}f_1[i-1][j+1][k]+\frac {wk}{j+k}f_1[i-1][j][k-1]\\&=wf_1[i][j][k]\end{aligned}$

   还有一个比较简单但不那么严谨的理解方式：每一步期望的增量都与期望成正比。（这里被 _rqy 喷了，出题人就是菜，这个证明写不严谨。）

   这样的话就只用计算 $f_1[i][j][k]$ 了。

2. 注意到 $i,\,j,\,k,\,m$ 有一些联系。实际上可以令 $f'_w[i][j]$ 表示 $f_w[m-i-j][SA+i][SB-j]$（这里的 $SA$ 和 $SB$ 都是未操作时的初始值）。

令 $g'_1[i][j]$ 表示 $g_w[m-i-j][SA+i][SB-j]$，计算方式类似。

**总结**

$f'_1[i][j]=1\ (i+j=m)$

$f'_1[i][j]=\frac{SA+i+1}{SA+SB+i-j}f'_1[i+1][j]+\frac{SB-j}{SA+SB+i-j}f'_1[i][j+1]\ (i+j<m)$

$g'_1[i][j]=1\ (i+j=m)$

$g'_1[i][j]=\frac{SA+i}{SA+SB+i-j}g'_1[i+1][j]+\frac{SB-j-1}{SA+SB+i-j}g'_1[i][j+1]\ (i+j<m)$

“被喜欢的”位置答案是 $w_if'_1[0][0]$，“不被喜欢的”位置答案是 $w_ig'_1[0][0]$。

如果每次去算逆元就是 $\mathcal O(n+m^2\log p)$，预处理出来就是 $\mathcal O(n+m^2+m\log p)$。

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 200010;
const int M = 3010;
const int mod = 998244353;

int qpow(int x, int y) //calculate the modular multiplicative inverse
{
	int out = 1;
	while (y)
	{
		if (y & 1) out = (ll) out * x % mod;
		x = (ll) x * x % mod;
		y >>= 1;
	}
	return out;
}

int n, m, a[N], w[N], f[M][M], g[M][M], inv[M << 1], sum[3];

int main()
{
	int i,j;
	
	scanf("%d%d", &n, &m);
	
	for (i = 1; i <= n; ++i) scanf("%d", a + i);
	
	for (i = 1; i <= n; ++i)
	{
		scanf("%d", w + i);
		sum[a[i]] += w[i];
		sum[2] += w[i];
	}
	
	for (i = max(0, m - sum[0]); i <= 2 * m; ++i) inv[i] = qpow(sum[2] + i - m, mod - 2);
	
	for (i = m; i >= 0; --i)
	{
		f[i][m - i] = g[i][m - i] = 1;
		for (j = min(m - i - 1, sum[0]); j >= 0; --j)
		{
			f[i][j] = ((ll) (sum[1] + i + 1) * f[i + 1][j] + (ll) (sum[0] - j) * f[i][j + 1]) % mod * inv[i - j + m] % mod;
			g[i][j] = ((ll) (sum[1] + i) * g[i + 1][j] + (ll) (sum[0] - j - 1) * g[i][j + 1]) % mod * inv[i - j + m] % mod;
		}
	}
	
	for (i = 1; i <= n; ++i) printf("%d\n", int((ll) w[i] * (a[i] ? f[0][0] : g[0][0]) % mod));
	
	return 0;
}
```

---

## 作者：Phartial (赞：2)

假设我们想要求出第 $x$ 张图片最后的期望权值，那么对于其他图片，我们只在乎它的 $a$ 是多少。将其他图片中 $a$ 值相同的合并到一起，就只剩下了三张图片。

设 $f_{i,j,k}$ 表示现在第 $x$ 张图片被选了 $i$ 次，除它之外的 $a=0$ 的图片被选了 $j$ 次，除它之外的 $a=1$ 的图片被选了 $k$ 次的概率。枚举最后一次选的图片转移即可。

时间复杂度 $\mathcal{O}(nm^3)$。可以通过 Easy version。

考虑优化。先不管第 $x$ 张图片，将所有 $a=0$ 的图片和所有 $a=1$ 的图片分别合并到一起，设 $f_{i,j}$ 为 $a=0$ 的图片被选了 $i$ 次，$a=1$ 的图片被选了 $j$ 次的概率，转移是简单的。

为了从这个状态中获得具体的信息，考虑拆分，我们将一张权值为 $w$ 的图片拆成 $w$ 张权值为 $1$ 的图片，显然这并不会影响最后的期望总权重，并且由于每张图片的地位变得相同，我们可以直接以比例的方式取出其中第 $x$ 张图片拆分成的那些图片。于是问题转化为求所有 $a=0\text{ or }1$ 的图片最后的期望总权重，枚举这种图片被选了多少次即可。

时间复杂度 $\mathcal{O}(n+m^2)$，忽略逆元复杂度。

```cpp
#include <iostream>

using namespace std;
using LL = long long;

const int kN = 2e5 + 1, kV = 3002;
const int kM = 998244353;

int n, m, a[kN], w[kN], s[2];
LL f[kV][kV], e[2], v[2];

LL P(LL b, int e) {
  LL s = 1;
  for (; e; e /= 2, b = b * b % kM) {
    (e & 1) && (s = s * b % kM);
  }
  return s;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> w[i];
    s[a[i]] += w[i];
  }
  v[0] = P(s[0], kM - 2), v[1] = P(s[1], kM - 2);
  f[0][0] = 1;
  for (int i = 0; i <= min(m, s[0]); ++i) {
    for (int j = 0; i + j <= m; ++j) {
      LL iv = P(s[0] - i + s[1] + j, kM - 2);
      f[i + 1][j] = (f[i + 1][j] + f[i][j] * (s[0] - i) % kM * iv % kM) % kM;
      f[i][j + 1] = (f[i][j + 1] + f[i][j] * (s[1] + j) % kM * iv % kM) % kM;
    }
  }
  for (int i = 0; i <= min(m, s[0]); ++i) {
    e[0] = (e[0] + f[i][m - i] * (s[0] - i) % kM) % kM;
  }
  for (int i = 0; i <= m; ++i) {
    e[1] = (e[1] + f[m - i][i] * (s[1] + i) % kM) % kM;
  }
  for (int i = 1; i <= n; ++i) {
    cout << e[a[i]] * w[i] % kM * v[a[i]] % kM << '\n';
  }
  return 0;
}
```

---

## 作者：N2MENT (赞：1)

[blog](https://www.cnblogs.com/0x0620AF/articles/CF1172C2.html)

[CF1172C2](https://www.luogu.com.cn/problem/CF1172C2)

---

> 前情提要：聪明猫跟金勾爷 lzy duel，输掉了……
>
> 大概想到能分开每个位置考虑，以及 $\texttt{01}$ 分开，然后意识到不得不回宿舍了，没继续想了。

---

首先注意到对于整个序列 dp 实在是太奢侈了，根本没法设计状态，只能对每个位置考虑。

先想到一个暴力 dp。设 $f^k_{x, s_0, s_1}$ 表示对于某一位考虑，自己、喜欢的、不喜欢的操作次数分别为 $x,\ s_0,\ s_1$ 时，继续操作，当前位被操作次数的期望。

这个大概是 $O(nm^3)$ 的，于是可以过掉 easy version。

---

还是有点浪费，这种多个对象之间关系的 dp 大多可以拆成许多独立的部分，这个也一样。

我们注意到实际上“在对应的部分操作 $k$ 次，某个位置被操作次数的期望”、“全局操作 $k$ 次，两部分之一被操作次数的期望”，这两部分是完全分开的，因为操作在单个对象内的体现是一致的，要么 $+1$ 要么 $-1$。

先考虑“全局操作 $k$ 次，两部分之一被操作次数的期望”。这个可以直接暴力 dp。设 $f^k_{x}$ 表示一共操作 $k$ 次，已经对喜欢的部分操作了 $x$ 次，对喜欢的部分的操作的次数期望。复杂度 $O(m^2)$。

还有“在对应的部分操作 $k$ 次，某个位置被操作次数的期望”。我 duel 的时候没想清楚这个。

> lzy：我们大胆猜测，对一个部分操作 $k$ 次，某个位置 $x$ 和这个部分其他的位置 $y$，它们被操作次数的期望是和权值成比例的。

具体怎么证 lzy 也没说，只说这挺好证的……

---

大概说说吧。归纳一下应该很好搞。

假如操作是 $+1$，设：

$$f^k_{x, y}$$

表示两个数的权值为 $x$ 和 $y$ 的时候，再操作 $k$ 次之后 $x$ 的期望。

$$f^0_{x, y} = x$$

$$f^k_{x, y} = \dfrac{1}{x + y}\left(xf^{k - 1}_{x + 1, y} + yf^{k - 1}_{x, y + 1}\right)$$

要证：

$$f^k_{x, y} = \dfrac{x}{x + y}\cdot k + x$$

$k = 0$ 显然满足。

$$f^k_{x, y} = \dfrac{1}{x + y}\left(x\left(\dfrac{x + 1}{x + y + 1} \cdot (k - 1) + x + 1\right) + y\left(\dfrac{x}{x + y + 1} \cdot (k - 1) + x\right) \right)$$

$$f^k_{x, y} = \dfrac{1}{x + y}\left(x\left(\dfrac{x}{x + y + 1} \cdot (k - 1) + x\right) + y\left(\dfrac{x}{x + y + 1} \cdot (k - 1) + x\right) + \dfrac{x\cdot(k - 1)}{x + y + 1} + x \right)$$

$$f^k_{x, y} = \dfrac{x\cdot (k - 1)}{x + y + 1}  + x +\dfrac{1}{x + y}\left(  \dfrac{x\cdot(k - 1)}{x + y + 1} + x \right)$$

$$f^k_{x, y} = \dfrac{x + y + 1}{x + y}\cdot\dfrac{x\cdot (k - 1)}{x + y + 1}  + x +\dfrac{1}{x + y}\cdot x $$

$$f^k_{x, y} = \dfrac{x\cdot k}{x + y}  + x $$


感觉挺脱裤子放屁的，总之就是这样。

code：

```cpp
//        No mind to think.
//
//        No will to break.
//
//        No voice to cry suffering.
//
//        Born of God and Void.
//
//        You shall seal the blinding light that plagues their dreams.
//
//        You are the Vessel.
//
//        You are the Hollow Knight.
#ifdef N2
#define _GLIBCXX_DEBUG
#define LOG(...) fprintf(stderr, __VA_ARGS__)
#define DO(...) __VA_ARGS__
#else 
#define LOG(...) void(0)
#define DO(...) void(0)
#define NDEBUG
#endif
#define syncoff ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 2e5 + 10;
const int maxm = 3010;
using ll = long long;
ll Pow(ll a, ll b = mod - 2, ll mod = mod) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return res;
}
int d;
int w[maxn];
int lk[maxn];
int s[2];
int n, m;
int f[maxm][maxm];
int F(int k, int d1) {
    if(~f[k][d1]) return f[k][d1];
    if(k == m) return f[k][d1] = d1;
    int d0 = k - d1;
    int w0 = (s[0] - d0 + mod) % mod;
    int w1 = (s[1] + d1) % mod;
    return f[k][d1] = ((ll)w0 * F(k + 1, d1) % mod + (ll)w1 * F(k + 1, d1 + 1) % mod) % mod * Pow((w0 + w1) % mod) % mod;
}
int main() {
    syncoff;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> lk[i];
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i <= n; i++) {
        s[lk[i]] += w[i];
        if(s[lk[i]] >= mod) s[lk[i]] -= mod;
    } 
    memset(f, -1, sizeof(f));
    int d1 = F(0, 0);
    int d0 = (m - d1 + mod) % mod;
    LOG("%d %d\n", d1, d0);
    for(int i = 1; i <= n; i++) {
        if(lk[i]) {
            cout << (w[i] + (ll)d1 * w[i] % mod * Pow(s[1]) % mod) % mod << '\n';
        } else {
            cout << (w[i] - (ll)d0 * w[i] % mod * Pow(s[0]) % mod + mod) % mod << '\n';
        }
    }
}
```

---

## 作者：Hoks (赞：0)

## 前言
牛牛的概率题。

摘自 [杂题选做](https://www.luogu.com.cn/training/597433)。

建议先看：[CF1172C1 解题报告（杂题选做）](https://www.luogu.com.cn/article/chgq8sf4)。
## 思路分析
我们考虑优化在 C1 时的做法。

首先第一个要优化的肯定就是 dp 状态了，$4$ 维 dp 能过才有鬼了。

这个操作次数 $m$ 的枚举很难规避，结合观察数据范围，$m$ 可以放两个，而 $n$ 放一个就爆了，所以我们考虑能不能搞掉 $n$。

那怎么搞掉 $n$，就是考虑划分等价类。

首先我们知道的，对于两个照片，如果都是喜欢/讨厌并且初始权值相同，那么答案肯定相同。

那我们先把 dp 定义式改成这个写下转移方程试试。

于举例而言，我们就假设这张照片是喜欢的好了。

$f_{i,j,l,r}$ 表示初始权值为 $i$ 的数被操作 $j$ 次，喜欢/讨厌的数被操作 $l,r$ 次的概率，$s_{0/1}$ 是讨厌/喜欢的照片的总权值。

$$f_{i+j,j+1,l,r+1}\leftarrow f_{i,j,l,r}\cdot\frac{i+j}{s_0+s_1-l+r}$$
$$f_{i,j,l+1,r}\leftarrow f_{i,j,l,r}\cdot\frac{s_0-l}{s_0+s_1-l+r}$$
$$f_{i,j,l,r+1}\leftarrow f_{i,j,l,r}\cdot\frac{s_1+r-(i+j)}{s_0+s_1-l+r}$$

但这个条件也未免太弱了，值域可以非常大，划分后的数字种类数还是可能有 $n$ 种。

那我们只能进一步观察性质尝试划分等价类。

这里就出现人类智慧了，我们可以知道 $f_{i,j,l,r}=i\cdot f_{1,j,l,r}$。

证明考虑使用归纳法，类似于上面，我们还是只关心喜欢的图片就行了，讨厌的证明是恰好相反的。

首先归纳奠基有：$f_{i,0,l,r}=i\cdot f_{1,0,l,r}$。

然后考虑设已有 $f_{i,j-1,l,r}=i\cdot f_{1,j-1,l,r},(j\in[1,x))$，证明 $f_{i,x,l,r}=i\cdot f_{1,x,l,r}$。

那么我们有：
$$f_{i,x,l,r}=\frac{i}{l+r}\cdot f_{i+1,x-1,l,r+1}+\frac{r-i}{l+r}\cdot f_{i,x-1,l,r+1}+\frac{l}{l+r}\cdot f_{i,x-1,l,r}$$
拆开合并一下就可以得到：
$$f_{i,x,l,r}=i\cdot f_{1,x,l,r}$$
那这样的话我们就成功的把第一维的 $n$ 个状态化为了喜欢/讨厌这个 $0/1$ 状态。

那现在我们的 dp 数组就是 $f_{0/1,j,l,r}$。

那现在就还得对 $m$ 这一维进行优化。

这时我们可以发现，喜欢/讨厌的照片的选择次数和当前照片没多少关系。

直接拆开做，先跑一遍 dp 算出喜欢/讨厌的选择 $l/r$ 次的概率，然后再计算一张照片在所有和他同种的照片中选择 $i$ 次的概率即可。
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=2e5+10,V=1e6,M=3e3+10,INF=1e9+10,mod=998244353;
int n,m,a[N],w[N],s[N],f[M][M],g[M][M];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='('||c==')'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline int ksm(int x,int y,int mod)
{
    int res=1;
    while(y){if(y&1) res=res*x%mod;x=x*x%mod;y>>=1;}
    return res;
}
inline void solve()
{
	n=read();m=read();for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) w[i]=read(),s[a[i]]+=w[i];g[0][0]=f[0][0]=1;
	for(int i=0;i<=m;i++) for(int j=0;j<=min(s[0],m-i);j++)
		f[i+1][j]=(f[i+1][j]+f[i][j]*(s[1]+i)%mod*ksm(s[0]+s[1]+i-j,mod-2,mod)%mod)%mod,
		f[i][j+1]=(f[i][j+1]+f[i][j]*(s[0]-j)%mod*ksm(s[0]+s[1]+i-j,mod-2,mod)%mod)%mod;
	for(int i=0;i<=m;i++) for(int j=0;j<=m;j++)
		g[i+1][j]=(g[i+1][j]+g[i][j]*(1+i)%mod*ksm(s[1]+i+j,mod-2,mod)%mod)%mod,
		g[i][j+1]=(g[i][j+1]+g[i][j]*(s[1]-1+j)%mod*ksm(s[1]+i+j,mod-2,mod)%mod)%mod;s[1]=0;
	for(int i=0;i<=m;i++) for(int j=0;j<=i;j++) s[1]=(s[1]+f[i][m-i]*(j+1)%mod*g[j][i-j]%mod)%mod;
	memset(g,0,sizeof g);g[0][0]=1;
	for(int i=0;i<=min(1ll,m);i++) for(int j=0;j<=min(s[0]-1,m-i);j++)
		g[i+1][j]=(g[i+1][j]+g[i][j]*(1-i)%mod*ksm(s[0]-i-j,mod-2,mod)%mod)%mod,
		g[i][j+1]=(g[i][j+1]+g[i][j]*(s[0]-1-j)%mod*ksm(s[0]-i-j,mod-2,mod)%mod)%mod;s[0]=0;
	for(int i=0;i<=m;i++) for(int j=0;j<=min(i,1ll);j++) s[0]=(s[0]+f[m-i][i]*(1-j)%mod*g[j][i-j]%mod)%mod;
	for(int i=1;i<=n;i++) print(w[i]*s[a[i]]%mod),put('\n');
}
signed main()
{
	int T=1;
	// T=read();
	while(T--) solve();
	genshin:;flush();return 0;
}
```

---

## 作者：Rain_chr (赞：0)

本文是从概率入手，而不是从期望入手。

先考虑 C1，我们将所有喜欢和不喜欢的合并成一张大图片，对于三张图片进行 DP。

设 $dp[i][j][k]$ 表示喜欢的图片出现了 $i$ 次，不喜欢的图片出现了 $j$ 次，当前图片出现了 $k$ 次。请注意，这里喜欢和不喜欢的图片不包括当前的图片。最后答案就是 $dp[i][j][k]\times k [i+j+k=m]$ 之和，复杂度为 $O(nm^3)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int ksm(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
const int N=60;
int a[N],w[N];
int f[N][N][N];
int inv(int x)
{
    return ksm(x,mod-2);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>w[i];
    int A=0,B=0;
    for(int i=1;i<=n;i++)
        if(a[i]) A+=w[i];
        else B+=w[i];
    int sum=A+B;
    for(int i=1;i<=n;i++)
    {
        memset(f,0,sizeof(f));
        f[0][0][0]=1;
        if(a[i])
        {
            A-=w[i];
            int ans=0;
            for(int j=0;j<=m;j++)
                for(int k=0;k<=m;k++)
                    for(int l=0;l<=min(B,m);l++)
                    {
                        f[j+1][k][l]=(f[j+1][k][l]+f[j][k][l]*(w[i]+j)%mod*inv(sum+j+k-l)%mod)%mod;
                        f[j][k+1][l]=(f[j][k+1][l]+f[j][k][l]*(A+k)%mod*inv(sum+j+k-l)%mod)%mod;
                        f[j][k][l+1]=(f[j][k][l+1]+f[j][k][l]*(B-l)%mod*inv(sum+j+k-l)%mod)%mod;
                        if(j+k+l==m) ans=(ans+f[j][k][l]*(w[i]+j)%mod)%mod;
                    }
            A+=w[i];
            cout<<ans<<'\n';
        }
        else
        {
            B-=w[i];
            int ans=0;
            for(int j=0;j<=min(w[i],m);j++)
                for(int k=0;k<=m;k++)
                    for(int l=0;l<=min(B,m);l++)
                    {
                        f[j+1][k][l]=(f[j+1][k][l]+f[j][k][l]*(w[i]-j)%mod*inv(sum-j+k-l)%mod)%mod;
                        f[j][k+1][l]=(f[j][k+1][l]+f[j][k][l]*(A+k)%mod*inv(sum-j+k-l)%mod)%mod;
                        f[j][k][l+1]=(f[j][k][l+1]+f[j][k][l]*(B-l)%mod*inv(sum-j+k-l)%mod)%mod;
                        if(j+k+l==m) ans=(ans+f[j][k][l]*(w[i]-j)%mod)%mod;
                    }
            B+=w[i];
            cout<<ans<<'\n';
        }
    }
    return 0;
}
```


笔者的思考到此为止，直到听到一个结论：对于每一个喜欢和不喜欢的图片，设其出现次数为 $w_i$，所有喜欢图片最终期望与 $w_i$ 的比值一定，不喜欢的图片同理。感觉上很对，可以考虑将这一张图片拆成 $w_i$ 张小图片，这样显然是成正比的。严谨证明可以看其他题解或官方题解。

那么我们不用对于每一张图片都求了，只用对于喜欢的图片和不喜欢的图片分别求一次 $w_i=1$ 的情况，复杂度是 $O(n+m^3)$。但是注意，由于这一张图片是我们虚拟的，所以我们应该将其他图片相同类型初始的数量减一。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int ksm(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
const int N=60;
int a[N],w[N];
int f[N][N][N];
int inv(int x)
{
    return ksm(x,mod-2);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>w[i];
    int A=0,B=0;
    for(int i=1;i<=n;i++)
        if(a[i]) A+=w[i];
        else B+=w[i];
    int ans1=0,ans2=0,sum=A+B;
    f[0][0][0]=1;
	for(int j=0;j<=m;j++)
        for(int k=0;k<=m;k++)
            for(int l=0;l<=min(B,m);l++)
            {
                f[j+1][k][l]=(f[j+1][k][l]+f[j][k][l]*(1+j)%mod*inv(sum+j+k-l)%mod)%mod;
                f[j][k+1][l]=(f[j][k+1][l]+f[j][k][l]*(A-1+k)%mod*inv(sum+j+k-l)%mod)%mod;
                f[j][k][l+1]=(f[j][k][l+1]+f[j][k][l]*(B-l)%mod*inv(sum+j+k-l)%mod)%mod;
                if(j+k+l==m) ans1=(ans1+f[j][k][l]*(1+j)%mod)%mod;
            }
    memset(f,0,sizeof(f)); 
    f[0][0][0]=1;
    for(int j=0;j<=min(1ll,m);j++)
        for(int k=0;k<=m;k++)
            for(int l=0;l<=min(B,m);l++)
            {
                f[j+1][k][l]=(f[j+1][k][l]+f[j][k][l]*(1-j)%mod*inv(sum-j+k-l)%mod)%mod;
                f[j][k+1][l]=(f[j][k+1][l]+f[j][k][l]*(A+k)%mod*inv(sum-j+k-l)%mod)%mod;
                f[j][k][l+1]=(f[j][k][l+1]+f[j][k][l]*(B-1-l)%mod*inv(sum-j+k-l)%mod)%mod;
                if(j+k+l==m) ans2=(ans2+f[j][k][l]*(1-j)%mod)%mod;
            }
    for(int i=1;i<=n;i++)
    {
        if(a[i]) cout<<ans1*w[i]%mod<<'\n';
        else  cout<<ans2*w[i]%mod<<'\n';
    }
    return 0;
}
```

最后的优化，我们可以发现当前的图片被选中几次和喜欢与不喜欢的图片选中次数根本不互相影响。所以我们可以先 DP 出 $f[i][j]$ 喜欢的图片出现 $i$ 次，不喜欢的图片出现 $j$ 次的概率，再 DP $g[i][j]$ 表示出当前图片出现 $i$ 次，其他图片出现 $j$ 次的概率，两者相乘即可。

```cpp
// LUOGU_RID: 157849474
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int ksm(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
const int N=3010;
int a[200010],w[200010];
int f[N][N],g[N][N];
int inv(int x)
{
    return ksm(x,mod-2);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>w[i];
    int A=0,B=0;
    for(int i=1;i<=n;i++)
        if(a[i]) A+=w[i];
        else B+=w[i];
    int ans1=0,ans2=0,sum=A+B;
    f[0][0]=1;
	for(int k=0;k<=m;k++)
        for(int l=0;l<=min(B,m-k);l++)
        {
            f[k+1][l]=(f[k+1][l]+f[k][l]*(A+k)%mod*inv(sum+k-l)%mod)%mod;
            f[k][l+1]=(f[k][l+1]+f[k][l]*(B-l)%mod*inv(sum+k-l)%mod)%mod;
        }
    g[0][0]=1;
    for(int i=0;i<=m;i++)
        for(int j=0;j<=m;j++)
        {
            g[i+1][j]=(g[i+1][j]+g[i][j]*(1+i)%mod*inv(A+i+j)%mod)%mod;
            g[i][j+1]=(g[i][j+1]+g[i][j]*(A-1+j)%mod*inv(A+i+j)%mod)%mod;
        }
    for(int i=0;i<=m;i++)
        for(int j=0;j<=i;j++)
            ans1=(ans1+f[i][m-i]*(j+1)%mod*g[j][i-j]%mod)%mod;    

    memset(g,0,sizeof(g));
    g[0][0]=1;
    for(int i=0;i<=min(1ll,m);i++)
        for(int j=0;j<=min(B-1,m-i);j++)
        {
            g[i+1][j]=(g[i+1][j]+g[i][j]*(1-i)%mod*inv(B-i-j)%mod)%mod;
            g[i][j+1]=(g[i][j+1]+g[i][j]*(B-1-j)%mod*inv(B-i-j)%mod)%mod;
        }
    for(int i=0;i<=m;i++)
        for(int j=0;j<=min(i,1ll);j++)
            ans2=(ans2+f[m-i][i]*(1-j)%mod*g[j][i-j]%mod)%mod;
    for(int i=1;i<=n;i++)
    {
        if(a[i]) cout<<ans1*w[i]%mod<<'\n';
        else  cout<<ans2*w[i]%mod<<'\n';
    }
    return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

省队集训时讲的一道题。

多个照片肯定不好做，我们将 $a_i$ 相同的压成一张照片，那么这样子就只有两个照片——喜欢的和不喜欢的。

然后就可以 dp 了，设 $f(i,j)$ 表示 $i$ 张喜欢的照片和 $j$ 张不喜欢的照片的概率。

然后我们可以通过加一张照片，填出 $f(i,j+1)$ 和 $f(i+1,j)$ 的值，也就是：

$$
\begin{aligned}
f(i+1,j)=f(i+1,j)+\frac{i+S_1}{i-j+S}\cdot f(i,j)\\
f(i,j+1)=f(i,j+1)=\frac{S_0-j}{i-j+S}\cdot f(i,j)
\end{aligned}
$$

其中 $S$ 表示 $\sum w_i$，$S_k$ 表示 $\sum [a_i=k]w_i$。

然后考虑如何计算出压缩后一张图片的期望，我们可以枚举最后的照片情况，最后求和：

$$
\begin{aligned}
&E_1 = \sum_{i=0}^{m}(E_1+i-m)f(i,m-i)\\
&E_0=\sum_{i=0}^{m}(E_i+i)f(i,m-i)
\end{aligned}
$$

然后就是魔法，如何求出原本每个照片的期望呢？考虑到所有 $a_i$ 相等的照片本质上是相同的，权重是按照 $w_i$ 大小来选择的，具体选择哪一个照片并不重要。

于是我们可以将压缩后的“大照片”拆成 $S_k$ 个小照片，然后每一个照片的期望就对应 $w_i$ 个小照片，乘上即可，也就是：

$$
\frac{w_iE_{a_i}}{S_{a_i}}
$$

时间复杂度 $O(m^2\log P+n)$，轻微卡常。

[Code](https://vjudge.net/solution/51088712/i0fTQ4fEF5aiznnP6POp)

---

## 作者：LCuter (赞：0)

考虑 DP，我们发现概率的计算牵涉三个值，一个是不喜欢的图片的权值和，一个是喜欢的图片的权值和，还有一个是本身的权值。

我们记初始时喜欢的权值和是 $W_a$，不喜欢的权值和是 $W_b$，当前的是 $W'_a,W'_b$，一次操作会使得 $W_a'$ 加一或是 $W_b'$ 减一。

对于一张图片，我们在意的并非其编号，而是其初始权值，同时其它图片也可以看作两大类而无需分析，于是令 $F(w,i,a,b)$  表示一个权值为 $w$ 的且被喜欢的图片，经过 $i$ 次操作，$W_a'=a,W_b'=b$ 时的期望权值，为了计算概率，我们选择在操作序列前插入一个操作，而非在操作序列后插入一个操作，那么一共有三种转移来源：

- 选到自己，概率为 $\frac{w}{a+b}$，从 $F(w+1,i-1,a+1,b)$ 转移过来；
- 选到喜欢的图片但不是自己，概率为 $\frac{a-w}{a+b}$，从 $F(w,i-1,a+1,b)$ 转移过来；
- 选到不喜欢的图片，概率为 $\frac{b}{a+b}$，从 $F(w,i-1,a,b-1)$ 转移过来。

所以有：
$$
F(w,i,a,b)=\frac{w}{a+b}F(w+1,i-1,a+1,b)+\frac{a-w}{a+b}F(w,i-1,a+1,b)+\frac{b}{a+b}F(w,i-1,a,b-1)
$$
复杂度过高，需要优化。

发现 $w$ 这一维很恶心，可以去掉它吗？

经过观察，我们惊人地发现 $F(w,i,a,b)=wF(1,i,a,b)$！

证明可以使用归纳法。

那么我们令 $F(i,a,b)$ 表示原来的 $F(1,i,a,b)$，就有：

$$F(i,a,b)=\frac{1}{a+b}((a+1)F(i-1,a+1,b)+bF(i-1,a,b-1))$$

初值 $F(0,a,b)=1$，最后要求的是 $F(m,W_a,W_b)$。

我们观察 $F(m,W_a,W_b)$ 会从哪里转移过来，也就是有效的状态是哪些，可以发现后两维的变化量之和就等于第一维的变化量，而且随着第一维减少一，可能是第二维增加一，或者是第三维减少一。

我们新搞一个 $F^*(a,b)$ 表示第二维和第三维的相较于 $W_a$ 与 $W_b$ 的变化量，那么我们知道 $F^*(a,b)=F(m-a-b,W_a+a,W_b-b)$。

记 $W=W_a+a+W_b-b$，于是有转移：
$$
F^*(a,b)=\frac{1}{W}((W_a'+1)F(a+1,b)+W_b'F(a,b+1))
$$
类似的令 $G^*(a,b)$ 表示不喜欢的图片，有转移：
$$
G^*(a,b)=\frac{1}{W}((W_b'+1)G(a,b+1)+W_a'G(a+1,b))
$$
初值 $\forall a+b=m,F^*(a,b)=G^*(a,b)=1$，最终需要 $F^*(0,0),G^*(0,0)$。

时间复杂度 $O(n+m^2\log P)$，其中 $P=998244353$。

---

