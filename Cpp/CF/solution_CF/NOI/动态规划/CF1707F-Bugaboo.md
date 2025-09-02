# Bugaboo

## 题目描述

对于一个正整数数组 $a_1,a_2,\dots,a_n$，定义一种变换：将 $a$ 替换为数组 $b_1,b_2,\dots,b_n$，其中 $b_i = a_i \oplus a_{(i\bmod n)+1}$，$\oplus$ 表示按位异或运算。

给定整数 $n$、$t$ 和 $w$。我们称一个数组 $c_1,c_2,\dots,c_n$（$0 \le c_i \le 2^w-1$）为 bugaboo，当且仅当存在一个数组 $a_1,a_2,\dots,a_n$，使得对 $a$ 进行 $t$ 次上述变换后，$a$ 变为 $c$。

例如，当 $n=6$，$t=2$，$w=2$ 时，数组 $[3,2,1,0,2,2]$ 是 bugaboo，因为它可以通过对数组 $[2,3,1,1,0,1]$ 进行 $2$ 次变换得到：

$$
[2,3,1,1,0,1] \to [2\oplus 3,3\oplus 1,1\oplus 1,1\oplus 0,0\oplus 1,1\oplus 2] = [1,2,0,1,1,3]; \\
[1,2,0,1,1,3] \to [1\oplus 2,2\oplus 0,0\oplus 1,1\oplus 1,1\oplus 3,3\oplus 1] = [3,2,1,0,2,2].
$$

而数组 $[4,4,4,4,0,0]$ 不是 bugaboo，因为 $4 > 2^2 - 1$。数组 $[2,3,3,3,3,3]$ 也不是 bugaboo，因为它无法通过对某个数组进行 $2$ 次变换得到。

现在给定一个数组 $c$，其中部分位置丢失（初始时只有 $m$ 个位置已知，其余位置丢失）。有 $q$ 次修改操作，每次操作可以更改 $c$ 的某个位置。一次修改可能会改变该位置是丢失还是已知，也可能重新定义一个已知的位置。

你需要在每次修改后，计算有多少种可能的数组 $c$（丢失位置可以任意取值）是 bugaboo。输出第 $i$ 次修改的答案对 $p_i$ 取模的结果（$p_i$ 是给定的 $q$ 个数）。

## 说明/提示

在第一个样例中，$n=3$，$t=1$，$w=1$。用 $?$ 表示 $c$ 的丢失位置。

第一次询问，$c=[1,0,1]$。唯一可能的数组 $[1,0,1]$ 是 bugaboo，因为它可以通过对 $[0,1,1]$ 进行一次变换得到。所以答案是 $1 \bmod 123\,456\,789 = 1$。

第二次询问，$c=[1,1,1]$。唯一可能的数组 $[1,1,1]$ 不是 bugaboo。所以答案是 $0 \bmod 111\,111\,111 = 0$。

第三次询问，$c=[?,1,1]$。有两种可能的数组 $[1,1,1]$ 和 $[0,1,1]$。只有 $[0,1,1]$ 是 bugaboo，因为它可以通过对 $[1,1,0]$ 进行一次变换得到。所以答案是 $1 \bmod 987\,654\,321 = 1$。

第四次询问，$c=[?,1,?]$。有四种可能的数组。$[0,1,1]$ 和 $[1,1,0]$ 是 bugaboo。$[1,1,0]$ 可以通过对 $[1,0,1]$ 进行一次变换得到。所以答案是 $2 \bmod 555\,555\,555 = 2$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 1 1
1 1
3 1
4
2 0 123456789
2 1 111111111
1 -1 987654321
3 -1 555555555```

### 输出

```
1
0
1
2```

## 样例 #2

### 输入

```
24 8 5 4
4 4
6 12
8 12
15 11
16 7
20 2
21 9
22 12
13
2 13 11
3 15 12
5 7 13
9 3 14
10 5 15
11 15 16
13 14 17
14 1 18
18 9 19
19 6 20
23 10 21
24 8 22
21 13 23```

### 输出

```
1
4
9
2
1
0
1
10
11
16
16
0
16```

# 题解

## 作者：feecle6418 (赞：4)

好牛逼啊。

不妨假设 $n=2^k$。如果 $t\ge n$，$c$ 一定全是 0，以下假设 $t<n$。

这个操作见过很多次，显然就是设 $t$ 的子集为 $S$，$c_i=\oplus_{j\in S}a_{(i+j)\bmod n}$。

接下来的 idea 也比较正常：尝试对 $t$ 分治。（第一个试错点：从低位往高位考虑，顺序不要反）如果 $t$ 为偶数，说明 $a_{0,2,\dots},a_{1,3,\dots}$ 两边互不影响，因此可以递归计算 $ans([c_{0,2,\dots}],t/2)$ 和 $ans([c_{1,3,\dots}],t/2)$ 乘起来。否则，考虑先（试错：先还是最后）对 $a$ 做一次操作变为 $[a_{0}\oplus a_1,a_1\oplus a_2,\dots]$，这之后 $a$ 的奇数位、偶数位互不干扰了。此时 $a$ 奇数位和偶数位异或和相等。

接下来，要跳出思维定势，因为有了上述观察就已经可做了！注意到我们已经有了”从 $c$ 恢复 $a$ 的和“的工具：（和皆指异或和）

- 如果 $t$ 是偶数，异或和就是奇偶分开、$t/2$ 的和之和。
- 如果 $t$ 是奇数，奇偶分开、$t/2$，要求这两边的返回值相等。返回这个相等的返回值。

由此我们设计出来 dp：设 $f[\{c\},k,t]$ 表示 $c=\{c\}$ 且 $a$ 的异或和为 $k$ 的合法 $c$ 的数量。转 移：$t$ 是偶数就是递归两边，然后结果对 $k$ 做 $\mathrm{xor}$ 卷积；$t$ 是奇数就是递归两边，然后结果对 $k$ 做点积。

观察到整个 dp 数组在 $k$ 这维只有三种形态：

- 全相等，且为 $2^{x}$。
- 只有一个位置非 0，且为 $2^{x}$。

归纳易证。因此点积和 $\mathrm{xor}$ 卷积都是容易 $O(1)$ 维护的。所以可以设计类似翻转的线段树的结构来维护 dp，模数在变就只维护 $x$ 最后快速幂。

如果 $n\ne 2^k$，这步也不显然。设 $n=2^m(2x+1)$，数组 $b[0,2^m-1]_i=a_i\oplus a_{i+2^m}\oplus \dots$，注意到每次操作对 $b$ 的影响和对 $a$ 的影响形式完全相同，在 $2^m$ 步后 $b$ 变为全 0。结论：只要 $b$ 合法 $a$ 就合法。

结论的证明其实并不难。分析上面的递归过程在 $n\ne 2^k$ 时出了什么问题：第一次出问题一定是 $n$ 是奇数时，也即 $n=2x+1$，现在递归的 $c$ 就是 $b$ 的组成。如果 $t$ 在之前已经变成了 0，那在 $t$ 变成 0 时每个位置已经独立了。递归到现在这时当然还是独立的。因此，只需证明 $n$ 是奇数且 $t>0$ 的情况，合法只需要全部 $\mathrm{xor}$ 和为 0。只需证能唯一恢复上一层的序列，也即在已知全体 $\mathrm{xor}$ 和、相邻 $\mathrm{xor}$ 和时有唯一解，这是显然的！

直接用（bitrev 之后的）线段树维护，时间复杂度 $O(n+(m+q)\log n)$。

---

## 作者：Scintilla (赞：4)

好神仙的题目啊，每一步我都想不到。

与题面中不同，我们钦定所有下标从 $0$ 开始。

首先，我们可以得到 $c$ 和 $a$ 的定量关系为

$$ c_i = \oplus_{j = 0} ^ {n - 1} a_{(i + j) \bmod n} \left( \left( \sum\limits_{k = 0} \binom{t}{kn + j} \right) \bmod 2 \right) $$

组合数 $\bmod\ 2$ 引导我们往二进制位方面思考，我们不妨考虑一种特殊情况：$n = 2^k$。

此时若 $t = n$，不难得到 $c_i = 0$，所以对于所有 $t \ge n$，$c$ 合法当且仅当其中元素全部为 $0$，只用考虑 $t < n$ 的情况。

以下不区分**数**与**其二进制下为 $1$ 的位的集合**，即 $s \subseteq t$ 意味着 $t$ 的二进制位包含 $s$ 的二进制位。

当 $t < n$ 时，一个数不可能走一圈再来贡献，所以我们有 $c_i = \oplus_{s \subseteq t} a_{(i + j) \bmod n}$，我们尝试一些寻找一组解的方法。不妨对当前 $t$ 的**奇偶性**进行分类讨论。

 - 若 $2 \mid t$，则所有的 $s$ 都是偶数，即只有奇偶性相同的下标才能产生贡献。所以奇数下标和偶数下标就独立了，我们可以递归解决。

 - 若 $2 \nmid t$，则我们可以先对 $a$ 进行一次操作，这样 $a$ 就变为了 $\{a_0 \oplus a_1, a_1 \oplus a_2, \cdots, a_{n - 1} \oplus a_0\}$。此时可以继续递归下去，但是我们不能保证两边的解一定能够合并——我们需要两边的解的**异或和**相同。

这引导我们再加上一维记录异或和并进行 dp。

我们设 $f(t, d, k)$ 表示有多少长度为 $|d|$ 的序列 $a$ 满足异或和为 $k$，且经过 $t$ 次操作后可以得到序列 $\{c_{d_0}, c_{d_1}, \cdots, c_{d_{|d| - 1}}\}$。根据上面的讨论，我们可以写出转移方程：

$$ f(t, d, k) = \begin{cases}
  \sum\limits_{x \oplus y = k} f(\frac{t}{2}, \{d_0, d_2, \cdots, d_{|d| - 2}\}, x) \times f(\frac{t}{2}, \{d_1, d_3, \cdots, d_{|d| - 1}\}, y) & 2 \mid t \\
  f(\frac{t - 1}{2}, \{d_0, d_2, \cdots, d_{|d| - 2}\}, k) \times f(\frac{t - 1}{2}, \{d_1, d_3, \cdots, d_{|d| - 1}\}, k) & 2 \nmid t
\end{cases} $$

但是 $w < 30$，我们并不能暴力去做异或卷积和点积。

再仔细观察一下，对于 $k$ 这一维，dp 的初值有两种情况：只有一个位置为 $1$；以及全部为 $1$。而我们的运算只有异或卷积和点积，不难发现对于 $\forall t, d$，$k$ 这一维只有三种情况：

 - 全部为某个相等的值，且为 $2^w$ 的幂次。
 - 只有一个点的值非零，且为 $2^w$ 的幂次。
 - 全部为 $0$。

于是我们可以 $\mathcal{O}(1)$ 地维护异或卷积和点积了。

至于修改操作，我们发现 $d$ 的分裂就是 FFT 时做的分裂，所以我们可以把下标按位翻转之后用线段树维护。

至此，我们已经能够在 $\mathcal{O}(n + (m + q) \log n)$ 的时间复杂度内解决 $n = 2^k$ 时的问题。

对于 $n$ 任意的情况，我们设 $2^b \times r$，其中 $2 \nmid r$，我们有结论：对于 $t < 2^b$，设 $c'_i = \oplus_{j \equiv i \pmod {2^b}} c_j \ (i = 0, 1, \cdots, 2^b - 1)$，那么 $c$ 合法当且仅当 $c'$ 合法。

> 证明：考虑对 $c$ 进行 $b$ 次上述分治，那么每一次都都是 $2 \mid t$ 的情况，这显然是正确的，因为分治并没有用到 $n$ 是 $2$ 的幂次的性质。进而我们只用证明 $n$ 为奇数的时候结论正确即可。$t = 0$ 时显然；$t > 0$ 时即证 $c$ 合法等价于异或和为 $0$。这个条件是必要的，并且注意到异或和为 $0$ 时因为 $n$ 是奇数所以可以消元得到 $t - 1$ 次操作后的序列，即前驱存在，所以也证明了充分性。

于是我们证明了这个结论。对于 $t \ge 2^b$ 的情况，合法条件同理也是 $c'$ 中的元素全部为 $0$。

于是我们在 $\mathcal{O}(n + (m + q) \log n)$ 的时间复杂度内解决了原问题。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
#define mp make_pair
#define pb emplace_back
#define rep(i, s, e) for (int i = s; i <= e; ++i)
#define drep(i, s, e) for (int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define pv(a) cout << #a << " = " << a << endl
#define pa(a, l, r) cout << #a " : "; rep(_, l, r) cout << a[_] << ' '; cout << endl
 
const int N = 1e7 + 10;
 
int read() {
  int x = 0, f = 1; char c = getchar();
  for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = -1;
  for (; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - 48;
  return x * f;
}
 
int qpow(int a, int b, int p) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % p) {
    if (b & 1) res = 1ll * res * a % p;
  }
  return res;
}
 
int n, m, lim, o, t, w, s[N], c[N], cnt[N], c0, cur, rev[N];
 
struct node {
  int typ, pos, z;
  node(int a = 1, int b = -1, int c = 0) { typ = a, pos = b, z = c; }
  friend node operator + (node a, node b) { // 点乘
    if (a.typ > b.typ) swap(a, b);
    if (a.typ == 0) {
      if (b.typ == 0) return node(0, -1, a.z + b.z);
      else if (~b.pos) return node(1, b.pos, a.z + b.z);
      else return node(1, -1, 0);
    }
    else {
      if (~a.pos && a.pos == b.pos) return node(1, a.pos, a.z + b.z);
      else return node(1, -1, 0);
    }
  }
  friend node operator * (node a, node b) { // xor 卷积
    if (a.typ > b.typ) swap(a, b);
    if (a.typ == 0) {
      if (b.typ == 0) return node(0, -1, a.z + b.z + 1);
      else if (~b.pos) return node(0, -1, a.z + b.z);
      else return node(1, -1, 0);
    }
    else {
      if (~a.pos && ~b.pos) return node(1, a.pos ^ b.pos, a.z + b.z);
      return node(1, -1, 0);
    }
  }
  int val(int mod = 998244353) {
    if (typ == 0) return qpow(2, w * (z + 1), mod);
    else if (~pos) return qpow(2, w * z, mod);
    else return 0;
  }
} mask[30], dat[N];
 
#define ls lson[u]
#define rs rson[u]
#define mid (l + r >> 1)
 
int rt, tot, lson[N], rson[N];
 
int newnode(int l, int r) {
  dat[++ tot] = mask[__lg(r - l + 1)];
  return tot;
}
 
void maintain(int u, int l, int r) {
  if (t & (1 << o - __lg(r - l + 1))) dat[u] = dat[ls] + dat[rs];
  else dat[u] = dat[ls] * dat[rs];
}
 
int modify(int p, int x, int u, int l, int r) {
  if (!u) u = newnode(l, r);
  if (l == r) {
    dat[u] = ~x ? node(1, x, 0) : node(0, -1, 0);
    return u;
  }
  if (p <= mid) {
    ls = modify(p, x, ls, l, mid);
    if (!rs) rs = newnode(mid + 1, r);
  }
  else {
    rs = modify(p, x, rs, mid + 1, r);
    if (!ls) ls = newnode(l, mid);
  }
  return maintain(u, l, r), u;
}
 
void Modify(int p, int x) {
  int lst = c[p]; c[p] = x;
  p %= lim, cur -= cnt[p] == 0 && s[p] > 0;
  if (~lst) s[p] ^= lst;
  if (~x) {
    s[p] ^= x;
    if (~lst || -- cnt[p] == 0) rt = modify(rev[p], s[p], rt, 0, lim - 1);
    else -- c0;
  }
  else {
    if (!~lst || ++ cnt[p] == 1) rt = modify(rev[p], -1, rt, 0, lim - 1);
    else ++ c0;
  }
  cur += cnt[p] == 0 && s[p] > 0;
}
 
int main() {
  n = read(), m = read(), t = read(), w = read();
  lim = n & -n, o = __lg(lim);
  rep(i, 0, lim - 1) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << o - 1);
  }
  rep(i, 0, n - 1) {
    c[i] = -1;
    if (++ cnt[i % lim] != 1) ++ c0;
  }
  mask[0] = node(0, -1, 0);
  rep(i, 1, o) {
    if (t & (1 << o - i)) mask[i] = mask[i - 1] + mask[i - 1];
    else mask[i] = mask[i - 1] * mask[i - 1];
  }
  rt = newnode(0, lim - 1);
  rep(i, 1, m) {
    int p = read() - 1, x = read();
    Modify(p, x);
  }
  for (int q = read(); q; -- q) {
    int p = read() - 1, x = read(), mod = read();
    Modify(p, x);
    int res = 1ll * (t < lim ? dat[rt].val(mod) : !cur) * qpow((1 << w) % mod, c0, mod) % mod;
    printf("%d\n", res);
  }
  return 0;
}
```

---

## 作者：tzc_wk (赞：1)

非常惊艳的题目！

下文中假设下标从 $0$ 开始。

一开始完全想错方向了，以为是将某个形如 $x^{kn}-1$ 的式子写成 $\bmod 2$ 意义下 $F(x)=\sum\limits_{v\subseteq t}x^v$ 的倍数。。。。。。

我们先来考虑 $n$ 是 $2$ 的幂的情况（此题的难点之一，想不到先从这种情况入手，这可能是这道题最大的难点）。对于 $t\ge n$，可以得到 $c_i$ 可以通过某个 $\{a_i\}$ 进行 $t$ 次操作得到的充要条件是 $c_i=0$，因为根据 Kummer 定理，$c_i=\operatorname{xor}_{v\subseteq t}a_{(i+v)\bmod n}$。而对于 $t=n$，显然有 $c_i=a_i\oplus a_{(i+n)\bmod n}=0$，再进行下去肯定也是全 $0$ 序列，因此接下来考虑 $t<n$ 的情况。

考虑什么样的序列 $c$ 能够由某个序列 $a$ 进行 $t$ 次操作得到。考虑按 $t$ 的最低位分类讨论（本题的难点之二，要用分治的思想判定合法性而不是像我一样将下标集合拆成若干个基），对于 $t$ 是偶数的情况，根据上面 Kummer 定理的式子可以直接得出 $c$ 序列的奇偶位是独立的，因此 $t$ 是偶数的情况等价于 $c$ 的奇数位和偶数位分别可以表示成某个数组进行 $\dfrac{t}{2}$ 次操作后的结果。对于 $t$ 是奇数的情况，对于任意一个 $a$，我们先对其进行一次操作，这样可以得到一个奇数位异或和等于偶数位的数组 $a'$，此时规约到 $t$ 是偶数的情况。

知道这个性质以后考虑 DP。$f(t,S,k)$ 表示有多少个填下标为 $S$ 的子序列的方案使得存在一个异或和为 $k$ 的序列进行 $t$ 次操作之后得到 $a$，考虑 $S_0$ 为 $S$ 中下标偶数的位置，$S_1$ 为 $S$ 中下标奇数的位置，那么 
$$
f(t,S,k)=\begin{cases}\sum\limits_{x\oplus y=k}f(t/2,S_0,x)·f(t/2,S_1,y)&(t\equiv 0\pmod{2})\\
f(t/2,S_0,k)·f(t/2,S_1,k)&(t\equiv 1\pmod{2})\end{cases}
$$
显然我们类比 FFT 进行 butterfly 变换后，每个 $S$ 的取值范围都是一个长度 $2$ 的幂的区间，因此考虑线段树维护。并且我们还发现对于一个固定的 $t,S$，对于所有的 $k$ 情况如下：

- 所有值都相同，且都是 $2^w$ 的幂。
- 只有一个值非零，且是 $2^w$ 的幂。
- 全部都是 $0$。

这样我们可以 $O(1)$ 维护点乘和异或卷积。（难点之三，如何上推信息，其实这步还挺自然的，稍加分析应该可以分析出来）。

这样我们解决了 $n$ 是 $2$ 的幂的情况。时间复杂度 $n+(m+q)\log n$。

接下来考虑普遍情况，我们假设 $K$ 为最大的满足 $2^K\mid n$ 的 $K$。那么有结论，记 $c'_i=\operatorname{xor}_{j\equiv i\pmod{2^K}}c_j$，那么 $c$ 合法当且仅当 $c'$ 合法。（本题的难点之四，如何从特殊情况规约到一般情况）。证明大概就，我们先对 $c$ 进行 $K$ 次分治，显然得到的 $\bmod 2^K$ 的剩余系的独立的，而对于 $t>1,n\equiv 1\pmod{2}$，进行一次操作以后显然所以数异或和都是 $0$，而如果我们考虑高斯消元的过程，那么这个矩阵的秩是 $n$，因此对于所有异或和为 $0$ 长度是奇数的序列必然可以通过某个序列进行 $t\ge 1$ 次操作得到。

这样我们只用维护 $2^K$ 的序列即可。时间复杂度还是 $n+(m+q)\log n$。

```cpp
const int MAXN = 1e7;
const int MAXP = 8388608;
int qpow(int x, int e, int mod) {
	int ret = 1;
	for (; e; e >>= 1, x = 1ll * x * x % mod)
		if (e & 1) ret = 1ll * ret * x % mod;
	return ret;
}
int n, m, t, w, qu, b = 1, a[MAXN + 5], lg, hib[MAXP + 5];
int val[MAXP + 5], cnt[MAXP + 5];
struct dat {
	int opt, pos, v;
	dat() {opt = pos = v = 0;}
	dat(int V, int C) {
		if (!C) opt = 1, pos = V, v = 0;
		else opt = 0, pos = 0, v = (C - 1) * w;
	}
	friend dat operator ^ (const dat &X, const dat &Y) { // xor convolution
		dat ret;
		if (X.opt == 2 || Y.opt == 2) ret.opt = 2;
		else if (X.opt == 1 && Y.opt == 1) ret.opt = 1, ret.pos = X.pos ^ Y.pos, ret.v = X.v + Y.v;
		else {
			ret.opt = 0;
			if (!X.opt && !Y.opt) ret.v = X.v + Y.v + w;
			else ret.v = X.v + Y.v;
		}
		return ret;
	}
	friend dat operator * (const dat &X, const dat &Y) { // dot
		dat ret;
		if (X.opt == 2 || Y.opt == 2) ret.opt = 2;
		else if (X.opt == 1 && Y.opt == 1) {
			if (X.pos != Y.pos) ret.opt = 2;
			else ret.opt = 1, ret.pos = X.pos, ret.v = X.v + Y.v;
		}
		else if (X.opt == 0 && Y.opt == 0) ret.opt = 0, ret.v = X.v + Y.v;
		else ret.opt = 1, ret.pos = X.pos + Y.pos, ret.v = X.v + Y.v;
		return ret;
	}
};
int rev[MAXP + 5];
struct node {int l, r; dat v;} s[MAXP * 2 + 5];
void pushup(int k) {
	if (t >> hib[k] & 1) s[k].v = s[k << 1].v * s[k << 1 | 1].v;
	else s[k].v = s[k << 1].v ^ s[k << 1 | 1].v;
}
void build(int k, int l, int r) {
	s[k].l = l; s[k].r = r; if (l == r) return s[k].v = dat(val[rev[l]], cnt[rev[l]]), void();
	int mid = l + r >> 1; build(k << 1, l, mid); build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
void modify(int k, int p) {
	if (s[k].l == s[k].r) return s[k].v = dat(val[rev[p]], cnt[rev[p]]), void();
	int mid = s[k].l + s[k].r >> 1;
	if (p <= mid) modify(k << 1, p); else modify(k << 1 | 1, p);
	pushup(k);
}
int main() {
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	for (int i = 2; i <= MAXP; i++) hib[i] = hib[i >> 1] + 1;
	scanf("%d%d%d%d", &n, &m, &t, &w); int tmp = n;
	while (tmp % 2 == 0) tmp >>= 1, b <<= 1, lg++; memset(a, -1, sizeof(a));
	for (int i = 0; i < b; i++) cnt[i] = n / b, val[i] = 0;
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y); --x; a[x] = y;
		cnt[x & (b - 1)]--; val[x & (b - 1)] ^= y;
	}
	if (t >= b) {
		int sum = 0, ban = 0;
		for (int i = 0; i < b; i++) {
			if (!cnt[i] && val[i]) ban++;
			sum += max(cnt[i] - 1, 0);
		}
		scanf("%d", &qu);
		while (qu--) {
			int x, y, mod; scanf("%d%d%d", &x, &y, &mod); --x;
			if (!cnt[x & (b - 1)] && val[x & (b - 1)]) ban--;
			sum -= max(cnt[x & (b - 1)] - 1, 0);
			if (~a[x]) cnt[x & (b - 1)]++, val[x & (b - 1)] ^= a[x];
			a[x] = y;
			if (~a[x]) cnt[x & (b - 1)]--, val[x & (b - 1)] ^= a[x];
			if (!cnt[x & (b - 1)] && val[x & (b - 1)]) ban++;
			sum += max(cnt[x & (b - 1)] - 1, 0);
			if (ban) puts("0"); else printf("%d\n", qpow(2, w * sum, mod));
		}
	} else {
		for (int i = 0; i < b; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << lg - 1);
		// for (int i = 0; i < b; i++) printf("%d ", rev[i]); printf("\n");
		// printf("%d\n", b);
		build(1, 0, b - 1); scanf("%d", &qu);
		while (qu--) {
			int x, y, mod; scanf("%d%d%d", &x, &y, &mod); --x;
			if (~a[x]) cnt[x & (b - 1)]++, val[x & (b - 1)] ^= a[x];
			a[x] = y;
			if (~a[x]) cnt[x & (b - 1)]--, val[x & (b - 1)] ^= a[x];
			modify(1, rev[x & (b - 1)]);
			if (s[1].v.opt == 2) puts("0");
			else printf("%d\n", qpow(2, s[1].v.v + ((s[1].v.opt == 1) ? 0 : w), mod));
		}
	}
	return 0;
}
```

---

## 作者：Galex (赞：0)

/崇拜

首先考虑 $n$ 是 $2$ 的幂的情况。

考虑用 $a$ 表示 $c$，可以发现

$$
c_i=\oplus_{j=0}^{n-1}a_{(i+j)\bmod n}\left(\left(\sum_{k\ge 0} \binom{t}{kn+j} \right)\bmod 2 \right)
$$

当 $t=n$ 时，$\sum_{k\ge 0} \binom{t}{kn+j}$ 恒为偶数，即 $c_i$ 恒为 $0$。而一个全 $0$ 的序列变换一次显然仍全部是 $0$。所以当 $t\ge n$ 时，当且仅当所有 $c_i$ 均为 $0$ 时合法。

接下来只需考虑 $t<n$ 的情况，那么 $\sum_{k\ge 0} \binom{t}{kn+j}$ 就会等于 $\binom{t}{j}$。根据 Lucas 定理，$\binom{t}{j}=[j \subseteq t]$，即 $c_i=\oplus_{j\subseteq t} a_{(i+j)\bmod n}$。

然后对 $t$ 的奇偶性分类。

当 $t$ 为偶数时，显然 $j$ 也会是偶数，可以直接把序列 $c$ 按照下标的奇偶性分成 $c_0$ 和 $c_1$，两边分别做 $t\div 2$ 后的子问题。

当 $t$ 为奇数时，可以对 $a$ 先进行一次变换，就变成了 $t$ 为偶数的情况。进行一次变换后的 $a$ 会有一个性质：下标为奇数的 $a_i$ 的异或和 $=$ 下标为偶数的异或和 $=$ 原来的 $a$ 的异或和。

我们发现对于序列 $c$，能够经过 $t$ 次变换变成他的所有 $a$ 的异或和是相同的。具体的，我们设 $f(S,t)$ 表示只考虑 $c$ 中那些下标 $\in S$ 的数，所有长度为 $|S|$，且经过 $t$ 次变换之后会变成 $c$ 的异或和是什么。那么根据 $t$ 的奇偶性能得到以下转移：

$$
f(S,t)=
\begin{cases}
f(\{S_0,S_2,\cdots,S_{|S|-2}\},\dfrac t 2)\oplus f(\{S_1,S_3,\cdots,S_{|S-1|}\},\dfrac t 2)& t\bmod 2 = 0\\
\\
f(\{S_0,S_2,\cdots,S_{|S|-2}\},\dfrac {t-1} 2)= f(\{S_1,S_3,\cdots,S_{|S-1|}\},\dfrac {t-1} 2)& t\bmod 2 = 1
\end{cases}
$$

那么我们可以考虑一个 dp：$dp(S,t,k)$ 表示有多少个长度为 $|S|$，异或和为 $k$ 的 $a$，与上面类似可得到转移：

$$
dp(S,t,k)=
\begin{cases}
\sum\limits_{x\oplus y=k}dp(\{S_0,S_2,\cdots,S_{|S|-2}\},\dfrac t 2,x)\times dp(\{S_1,S_3,\cdots,S_{|S-1|}\},\dfrac t 2,y)& t\bmod 2 = 0\\
\\
dp(\{S_0,S_2,\cdots,S_{|S|-2}\},\dfrac {t-1} 2,k)\times f(\{S_1,S_3,\cdots,S_{|S-1|}\},\dfrac {t-1} 2,k)& t\bmod 2 = 1
\end{cases}
$$

初值是 $dp(\{i\},0,k)=[k=c_i]$。

由于 $k$ 的范围非常大（$2^w$），直接做显然不太现实。但是我们观察到，如果 $S,t$ 固定，把 $dp(S,t,?)$ 当成一个长度为 $2^w$ 的序列，这个序列中每个数的值实际上只有以下几种情况：

- 全是 $0$。

- 全是 $2^w$ 的某个幂。

- 有一个数是 $2^w$ 的某个幂，其余的全是 $0$。

那么我们就能 $O(1)$ 维护异或卷积和点积了。

对于修改，我们发现这个转移的形式非常像 FFT。于是做一个蝴蝶变换后线段树维护即可。

综上，我们用 $O(n+(m+q)\log n)$ 的时间解决了 $n=2^k$ 的情况。

对于 $n\not = 2^k$ 的情况，我们找到 $n$ 的因数中最大的 $2$ 的幂 $2^p$，然后设 $C_i=\oplus_{j\equiv i \bmod 2^p} c_j$，对 $C$ 做上面那个玩意即可。至于证明，我也不知道。

---

