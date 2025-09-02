# [ABC396G] Flip Row or Col

## 题目描述

给定一个 $H$ 行 $W$ 列的网格，每个格子中写有 $0$ 或 $1$。从上往下第 $i$ 行、从左往右第 $j$ 列的格子中写有整数 $A_{i,j}$。

你可以对网格进行以下两种操作任意次，顺序不限：

- 操作 X：选择一个整数 $x$ $(1 \leq x \leq H)$。对于所有 $1 \leq y \leq W$，将 $A_{x,y}$ 替换为 $1 - A_{x,y}$。
- 操作 Y：选择一个整数 $y$ $(1 \leq y \leq W)$。对于所有 $1 \leq x \leq H$，将 $A_{x,y}$ 替换为 $1 - A_{x,y}$。

请计算操作结束后，$\displaystyle \sum_{x=1}^H \sum_{y=1}^W A_{x,y}$ 可能达到的最小值。

## 说明/提示

### 约束条件

- $1 \leq H \leq 2 \times 10^5$
- $1 \leq W \leq 18$
- $H$ 和 $W$ 为整数
- $A_{i,1}A_{i,2}\ldots A_{i,W}$ 是由 `0` 和 `1` 组成的长度为 $W$ 的字符串

### 样例解释 1

通过以下操作，可以使网格状态变化如下

![](https://img.atcoder.jp/abc396/efeef604adf229d32bc42042f0a4e066.png)

，此时 $\displaystyle \sum_{x=1}^H \sum_{y=1}^W A_{x,y} = 2$：  
1. 执行操作 Y，选择 $y=1$  
2. 执行操作 X，选择 $x=2$  

由于无法使 $\displaystyle \sum_{x=1}^H \sum_{y=1}^W A_{x,y} \leq 1$，因此答案为 $2$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3 3
100
010
110```

### 输出

```
2```

## 样例 #2

### 输入

```
3 4
1111
1111
1111```

### 输出

```
0```

## 样例 #3

### 输入

```
10 5
10000
00111
11000
01000
10110
01110
10101
00100
00100
10001```

### 输出

```
13```

# 题解

## 作者：不知名用户 (赞：10)

### 题意

给定 $h$ 行 $w$ 列的 01 矩阵，每次操作可以将一行或一列异或 1，问若干次操作后所有数的和最小是多少。$h\le2\times10^5,w\le18$。

### 做法

肯定要从 $w\le 18$ 入手。如果确定了操作哪些列每行就只有两种情况，对比一下即可。

把每行看作一个二进制数 $a_1,a_2,\cdots,a_h$，再选择二进制数 $x\in[0,2^w)$，将 $a_i$ 变为 $a_i\oplus x$ 再看 $a_i\oplus x,a_i\oplus x\oplus(2^w-1)$ 哪个 $\text{popcount}$ 更小，记 $f_i=\min(\text{popcount}(i),\text{popcount}(i\oplus(2^w-1)))$。那么确定 $x$ 之后答案为 $\sum\limits_{i=1}^hf_{a_i\oplus x}$。

记 $cnt_i$ 表示 $i$ 在 $a$ 中的出现次数。那么 $x$ 的答案 $ans_x=\sum\limits_{i=0}^{2^w-1}cnt_if_{x\oplus i}$。因为 $x=i\oplus(x\oplus i)$，所以 $ans=cnt*f$，$*$ 表示异或卷积！这就是 FWT 的[板题](https://www.luogu.com.cn/problem/P4717)。时间复杂度 $\Theta(hw+w2^w)$，即输入复杂度加上 FWT 复杂度。

想到这个做法只需观察到异或逆运算性质即可，非常无脑。好像有不太无脑的 DP，大家自行查看官方题解。

### 代码

<https://atcoder.jp/contests/abc396/submissions/63544660>

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 18;
char s[N+10];
int f[1<<N], cnt[1<<N], g[1<<N];

void XOR(int *f, int n, int x)
{
	int i, j, k;
	for(i=0;(1<<i)<=n;i++) for(j=0;j<n;j+=(1<<i)) for(k=0;k<(1<<(i-1));k++)
	{
		int a = f[j+k], b = f[j+(1<<(i-1))+k];
		f[j+k] = a + b, f[j+(1<<(i-1))+k] = a - b;
		if(x==-1) f[j+k] >>= 1, f[j+(1<<(i-1))+k] >>= 1;
	}
}

signed main()
{
	int n, m, i, j;
	scanf("%lld%lld", &n, &m);
	for(i=1;i<=n;i++)
	{
		int t = 0;
		scanf("%s", s);
		for(j=0;j<m;j++) t = t + (1 << (m - j - 1)) * (s[j] - '0');
		cnt[t]++;
	}
	for(i=0;i<(1<<m);i++) f[i] = min(__builtin_popcount(i),__builtin_popcount(((1<<m)-1)^i));
	XOR(cnt,1<<m,1), XOR(f,1<<m,1);
	for(i=0;i<(1<<m);i++) g[i] = f[i] * cnt[i];
	XOR(g,1<<m,-1);
	int ans = 1e18;
	for(i=0;i<(1<<m);i++) ans = min(ans,g[i]);
	printf("%lld", ans);
	return 0;
}
```

### 本人赛时想法

很快想到了异或。感觉很可以 FWT 的样子。最开始我并未注意到异或的逆运算性质，然后开始了一通思考。

感觉不太行。换种想法，别 FWT？思考中……感觉怎么样都不行。

令 $g_i=[i=x]$，那么就是 $(g*cnt)\cdot f$，$\cdot$ 表示对应位相乘再相加。

$*$ 好像可以 FWT，那么得出 FWT 之后每个位置的贡献？因为是再 IFWT 和 $f$ 点积，那么就是把 $f$ FWT 一下？

思考中……

注意到好像 FWT 之后要 IFWT 回来，那么感觉唯一靠谱的方案就是 $f*cnt$？

哦，异或自己是自己的逆运算，赢！（回归上文）写写过了。

---

## 作者：DengStar (赞：2)

> [$\mathcal{CNBLOG}$](https://www.cnblogs.com/dengstar/p/18763698)

UPD on 2025/4/8: 发现公式有点小错误，现已修改，辛苦管理员了！

这道题用 FWT 似乎更加直接，可惜我目前不会。本文的做法和官方题解相同，都是使用 dp。（但不得不吐槽官方题解讲的实在太过于抽象，有的式子甚至打错了，所以你也可以把这篇题解看作是官方题解的人话翻译）

下文把题目中的 $H$ 和 $W$ 分别记为 $n$ 和 $m$。

首先发现 $m$ 很小，这肯定是我们的切入点。如果确定了有哪些列要翻转，那么显然就可以逐行计算答案。不妨把列的翻转状态看作一个 $m$ 位二进制数 $s$，第 $i$ 位为 $1$ 表示翻转第 $i$ 列，否则表示不翻转。对于每一列，也把它的状态记为 $m$ 位二进制数，第 $i$ 行记为 $b_{i}$。

那么，如果列的翻转状态为 $s$，则第 $i$ 行翻转后的状态就是 $b_{i} \oplus s$。此时如果不翻转第 $i$ 行，则有 $\operatorname{popcount}(b_{i} \oplus s)$ 个 $1$，否则有 $(m - \operatorname{popcount}(b_{i} \oplus s))$ 个 $1$。也就是说答案为
$$
\sum_{i = 1}^{n} \min(\operatorname{popcount}(b_{i} \oplus s), m - \operatorname{popcount}(b_{i} \oplus s))
$$
如果暴力枚举所有 $2^{m}$ 种列的翻转状态，总时间复杂度就为 $O(2^{m}n)$，无法接受。

考虑用 dp 优化求解的过程（本质上是信息复用）。如何设计状态呢？直接设 $f(s)$ 表示翻转状态为 $s$ 时的答案肯定是不可行的，因为没有给出任何额外信息。不妨设 $f(s, i)$ 表示有多少行 $j$ 满足 $b_{j}$ 和 $s$ 有 $i$ 位不同。这实际上代表着 $\operatorname{popcount}(b_{j} \oplus s) = i$，因此翻转列之后第 $j$ 行有 $i$ 个 $1$。于是答案为
$$
\boxed{\min_{0 \le s < 2^{m}} \sum_{i = 0}^{m} \min(i, m - i) \cdot f(s, i)}
$$
但这样还是不能转移。于是我们强制多设一维状态：设 $f(s, t, i)$ 表示有多少行 $j$ 的**最低 $t$ 位**和 $s$ 的**最低 $t$ 位**有 $i$ 位不同，而**前 $(m - t)$ 位全相同**。这样设是为了能够逐位转移。转移到第 $m$ 位的时候，就可以用来统计答案了，因为此时不再要求和 $s$ 的某个前缀相同。

初始化 $\forall 1 \le i \le n$，$f(b_{i}, 0, 0) \gets f(b_{i}, 0, 0) + 1$。

转移：
$$
f(s, t, i) = f(s, t - 1, i) + f(s \oplus 2^{t}, t - 1, i - 1)
$$
这是讨论了两种情况：如果有一行 $j$，它只在最后 $t$ 位和 $s$ 不同，且不同的位数为 $i$，那么要么第 $t$ 位和 $s$ 相同，这样的行有 $f(s, t - 1, i)$ 个；要么第 $t$ 位和 $s$ 不同，这样的行有 $f(s \oplus 2^{t}, t - 1, i - 1)$ 个。

dp 的状态数为 $O(2^{m} m^{2})$，转移的时间复杂度为 $O(1)$，所以总时间复杂度为 $O(2^{m} m^{2})$。

[AC 记录](https://atcoder.jp/contests/abc396/submissions/63596176)

---

## 作者：冷却心 (赞：2)

[更好的阅读体验](https://ladexx.github.io/2025/03/17/at_abc396_g-sol/)。

[ABC396G Flip Row or Col](https://atcoder.jp/contests/abc396/tasks/abc396_g)。不带脑子都能做的 FWT 题。赛时这么多人过是不是都贺的板子还是用的 AtCoder Library /fn，使得 diff 2195 紫题。

> 给定一个 $01$ 矩阵 $A$，长 $H$，宽 $W$，可以任意次数取反某一行或某一列，使得矩阵内数总和最小，求这个最小值。$H\leq 2\times 10^5,W\leq 18$。

注意到 $W$ 很小，于是我们把每一行的状态压成一个二进制数 $a_i$ 方便处理。

先考虑一个朴素做法，能发现每一列被取反的结果只和取反次数模 $2$ 有关，也就是每一列的取反结果是一个 $0/1$，所以我们枚举一个 $W$ 位的二进制数 $w$ 表示每一列是否被取反了。然后枚举每一行，这一行最终结果要么是 $a_i\oplus w$ 要么是 $a_i\oplus w$ 取反，所以这一行的总和最小即为 $\min(\text{popcount}(a_i\oplus w),W-\text{popcount}(a_i\oplus w))$，于是当列的状态为 $w$ 的答案便是每一行的前面这个 $\min$ 求和。然后对每个 $w$ 的答案取最小值就是总答案。时间复杂度 $O(H2^W)$。

我们记 $f(x)=\min(\text{popcount}(x),W-\text{popcount}(x))$，$h(w)$ 表示列的状态为 $w$ 的答案，那么有：
$$
h(w)=\sum_{i=1}^n f(a_i \oplus w).
$$
注意到，$a_i\oplus (a_i\oplus w)=w$，于是我们开一个桶 $g(i)$ 表示 $i$ 在 $a$ 序列中出现了几次，那么有：
$$
h(w)=\sum_{x\oplus y=w}g(x)f(y),h=g*f.
$$
然后就愉快地 FWT，做完了。

```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 5e5 + 10;
const LL MOD = 998244353;
LL Qpow(LL x, LL k, LL P) {
	LL ret = 1, tmp = (x + P) % P;
	while (k) {
		if (k & 1) ret = ret * tmp % P;
		tmp = tmp * tmp % P; k >>= 1;
	} return ret;
}
int n, m, A[N]; LL F[N], G[N]; 

void FWT(LL* A, int len, LL inv) {
	for (int i = 1; i < len; i <<= 1) {
		int h = (i << 1);
		for (int j = 0; j < len; j += h) for (int k = 0; k < i; k ++) {
			LL a = A[j + k], b = A[j + k + i];
			A[j + k] = (a + b) * inv % MOD, A[j + k + i] = (a + MOD - b) * inv % MOD;
		}
	} return ;
}

int main() {
	freopen(".in", "r", stdin); freopen(".out", "w", stdout);
	ios :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m; char x;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= m; j ++) { cin >> x; A[i] = (A[i] << 1) | (x - '0'); }
		G[A[i]] ++;
	}
	for (int i = 0; i < (1 << m); i ++) 
		F[i] = min(__builtin_popcount(i), m - __builtin_popcount(i));
	FWT(F, 1 << m, 1); FWT(G, 1 << m, 1);
	for (int i = 0; i < (1 << m); i ++) (F[i] *= G[i]) %= MOD;
	FWT(F, 1 << m, Qpow(2, MOD - 2, MOD));
	LL Ans = 1e18;
	for (int i = 0; i < (1 << m); i ++) Ans = min(Ans, F[i]);
	cout << Ans;
	return 0;
}
```

---

## 作者：__little__Cabbage__ (赞：2)

每行的状态用一个二进制数记录，先数出来 $f_S$ 为状态为 $S$ 的行数。

假设作用在列上的翻转为 $T$，那么答案就是：

$$
\sum_S f_Sw_{S\oplus T}
$$

其中 $w_S=\min(|S|,W-|S|)$ 是最终状态为 $S$ 情况下这一行的贡献。

显然可以 FWT 做到 $O((2^W+H)W)$，但是我不会 FWT，于是用 dp 解决。具体来说，因为 $w_S$ 只和 $|S|$ 有关，所以可以枚举这个： 

$$
\sum_S w_Sf_{S\oplus T}=\sum_i w_i\sum_{|S|=i}f_{S\oplus T}
$$

其中：

$$
g_{T,i}=\sum_{|S|=i}f_{S\oplus T}
$$

是满足 $S$ 翻转 $i$ 个位置能变成 $T$ 的 $f_S$ 之和，可以 dp 计算。

这样就是 $O(2^WW^2+WH)$ 的时间复杂度。

---

## 作者：wmrqwq (赞：2)

这是一篇视频题解。

![](bilibili:BV1TNRhYVEkp?t=0)

[代码链接](https://atcoder.jp/contests/abc396/submissions/63595543)

---

## 作者：biyi_mouse (赞：1)

题目的操作相当于每次对一行或一列异或 $1$。下文为了方便称 $n$ 为总行数，$m$ 为总列数。

首先对于一行来说，如果不考虑列的操作，那么它可以选择整行操作也可以不操作。显然如果这一行有 $cnt_i$ 个 $1$，并且 $cnt_i > m - cnt_i$ ，那么我们肯定操作比不操作优。换句话说，在列操作确定的情况下，行 $i$ 的最小贡献是 $\min(cnt_i, m - cnt_i)$。

观察数据范围可以发现 $M \leq 18$，显然很可以状压。所以我们把每行给压缩成 $B_i$，同时所有列上的操作也可以用整数 $X$ 来表示。此时我们要求 $\underset{0 \leq X < 2^m}{\min}\{\sum_{i = 1}^{n} \min(\operatorname{popcount}(B_i \oplus X), m - \operatorname{popcount}(B_i \oplus X))\}$，其中 $\operatorname{popcount}(x)$ 指 $x$ 的二进制中 $1$ 的个数。

一个简单的方法是对于每个 $X$ 都计算一遍，这样做是 $O(n\times 2^m)$ 的，炸了。

我们考虑优化计算过程，令 $f_{k, c, x}$ 表示 $X$ 的值为 $x$ 时，满足 $\operatorname{popcount}(B_i \oplus x) = c$ 且 $0\leq B_i < 2^k$ 的 $B_i$ 个数。

转移：$f_{k, c, x} \to f_{k + 1, c, x}$，$f_{k, c, x \oplus 2 ^ k} \to f_{k + 1, c + 1, x}$，即分为第 $k + 1$ 位 $B_i$ 是否等于 $X$ 两种情况。

那么最终的答案就是 $\underset{0\leq X < 2^m}{\min}\{\sum_{c = 0}^{m} \min(c, m - c) \times f_{m, c, X}\}$。

这么做的时间复杂度是 $O(m^2 \times 2^m)$，注意到 DP 的第一维可以优化掉，所以空间是 $O(m\times 2^m)$。

```cpp
const int N = 200010, M = 20;
int n, m;
LL f[M][1 << M], b[N];

int main() {
    n = read(), m = read();
    rep(i, 1, n) rep(j, 1, m) {
        char c; scanf(" %c", &c);
        if (c == '1') b[i] |= (1 << m - j);
    } 
    rep(i, 1, n) f[0][b[i]] ++;
    rep(i, 0, m - 1)
        fro(j, i, 0)
            rep(k, 0, (1 << m) - 1)
                f[j + 1][k] += f[j][k ^ (1 << i)];
    LL ans = 1e18;
    rep(k, 0, (1 << m) - 1) {
        LL res = 0;
        rep(i, 0, m) res += min(i, m - i) * f[i][k];
        ans = min(ans, res);
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：H_Kaguya (赞：1)

[相似推荐](https://www.luogu.com.cn/article/5yx5rjav)  
来点线段树做法。  
以下我们认为 $H$ 与 $2^W$ 同阶。  
则该算法时间复杂度 $O(W^2 2^W)$，空间复杂度 $O(2^W)$。  

---

首先考虑一个暴力做法，枚举列的翻转情况，总情况数 $2^W$。  
然后每行的翻转情况相互独立，在两种情况中选取值最小的即可。  
复杂度 $O(4^W)$。  

考虑对每一行进行状压，然后放进**权值线段树**。  
观察到对于数字 $i$，$popcount(i) = k$，则对答案的贡献是 $\min(k, W - k)$。  
线段树上维护子树内 $popcount = k$ 的数的个数。  
不难发现每个节点的状态数是 $O(W)$ 的。  
统计贡献和直接访问根节点即可。  

现在我们要支持两种操作：  
1. 给权值线段树内的每个点异或一个数。
2. 查询根节点的信息。

其中异或的数遍历 $[0, 2^W)$。  

我们先考虑给权值线段树内的元素异或 $2^k$ 如何实现。  
由于值域为 $2$ 的幂，这个线段树是一个完全二叉树。  
只需要找到所有深度为 $W - k$ 的节点，交换其左右子树，然后再向上 `update`。  
被修改的节点数量 $O(2^{W - k})$。  

接下来，我们顺序枚举需要异或的数。  
若当前异或的数为 $i$，则转移到 $i+1$ 需要异或上 $i \oplus (i+1)$，拆位之后按照上述方法暴力修改。  
根据我们对二进制加法器的理解，整个过程中从高到低第 $i$ 位一共会被修改 $2^i$ 次。  
这启发我们可以对二进制位翻转之后进行维护（低位与高位互换）  
第 $i$ 位需要修改 $O(2^i)$ 次，每次修改需要影响 $O(2^{W - i})$ 个节点。  
因此影响到的总节点量 $\sum_{i = 0}^W 2^i 2^{W - i} = O(W 2^W)$。  
由于我们每个节点维护的信息量是 $O(W)$ 的，所以总复杂度 $O(W^2 2^W)$。  

然后是空间复杂度。  
不难发现，若子树大小为 $k$，则需要维护的 $popcount$ 种类只有 $O(\log k)$。  
因此空间复杂度 $\sum_{k = 1}^{W} (W-k)2^k = O(2^W)$。  

虽说空间可以线性，但是为了方便实现还是写了 $O(W2^W)$ 的写法。  
贴代码~  
（被各种化简已经看不出来线段树的样子了）  

```cpp
#include <stdio.h>
#include <algorithm>
using namespace std;
const int siz = 1 << 18;
const int sz = 200005;
int n, m;
char str[19];
bool rev[siz];
int seg[siz * 2][19];
void update(int);
void build(int);
int main()
{
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf ("%s", str);
		int x = 0;
		for (int j = 0; j < m; ++j)
			x |= str[j] - '0' << j;
		++seg[x | 1 << m][0];
	}
	for (int i = (1 << m) - 1; i; --i)
		update(i);
	int ans = 1000000000;
	for (int i = 0; ; ++i)
	{
		int x = 0;
		for (int j = 1; j <= m; ++j)
			x += min(j, m - j) * seg[1][j];
		ans = min(ans, x);
		if (i + 1 == (1 << m))
			break;
		for (int j = (1 << __builtin_ctz(i + 1) + 1) - 1; j; --j)
		{
			rev[j] ^= 1;
			update(j);
		}
	}
	printf ("%d\n", ans);
	return 0;
}

void update(int a)
{
	seg[a][0] = seg[a << 1 ^ rev[a]][0];
	for (int i = 1; i <= m - __lg(a); ++i)
		seg[a][i] = seg[a << 1 ^ rev[a]][i] + seg[a << 1 ^ 1 ^ rev[a]][i - 1];
}
```

---

## 作者：ln001 (赞：1)

[思路参考](https://www.luogu.com.cn/article/um2obhf5)

## 题意
给定 $n \times m$ 的网格 $a_{i, j} \in \{0, 1\}$，你可以进行**任意次**行取反和列取反，求在网格 $a$ 能达到的所有状态中 $1$ 的个数的最小值。

其中 $n \in [1, 2 \times 10^5], m \in [1, 18]$。
## 做法

首先注意到行很短，列很少。

题意可以转化为求进行最少多少次单点修改，使得矩阵可以通过行取反列取反变为全 $0$ 矩阵。

发现对每一点、行、列进行的操作至多一次，且操作的先后顺序不重要。不妨将操作排序：先进行点操作，再进行行操作，最后进行列操作。

由于第三步是若干列操作，想让矩形全为 $0$，只需要在第二步操作之后让每一列的颜色一致，所以[可以](#:~:text=注意到行很短，-,列很少,-。)在统计答案时枚举每一列的颜色。

问题转化为至少进行多少次点取反，能让每行均达到指定状态或取反后的指定状态。

将所求设为 dp 状态，可得设 $f_{i, s}$ 表示**至少**进行 $i$ 次单点修改**才**能将状态改为 $s$ 的**行的个数**。

转移时为保证条件中的**至少**，需在最外层枚举被修改的单点 $k$。得到转移式：

$$
f_{i, s} \gets f_{i, s} + f_{i - 1, s \oplus 2^{k - 1}}
$$

目前来看答案应该为 $\min_{s \in [0, 2 ^ m)} \sum_{i \in [0, m]}{f_{i, s} \times i}$。

但上述做法并未考虑到行取反，行取反只会在某一行与目标状态差异过大时会被用到，此时操作的代价由 $i$ 变为 $m - i$，所以答案应为

$$
\min_{s \in [0, 2 ^ m)} \sum_{i \in [0, m]}{f_{i, s} \times \min(i, m - i)}
$$

[Code](https://vjudge.net/solution/59094406/MRlrtqpJpnVpU9lseQFW)

---

## 作者：Milthm (赞：1)

唔，我不太喜欢行这么多列这么少，所以下文我们把行列换了一下（

行数 $n\le 18$，启示我们状压。那么如果知道了行的状压状态了，我们就可以直接枚举每一列算出答案了，设每列的状压为 $a_i$，则有：

$$ans=\min\limits_{x=0}^{2^n-1}(\sum\limits_{i=1}^m\min(\text{popcount}(a_i \oplus x),n-\text{popcount}(a_i \oplus x))$$

令 $f(x)=\min(\text{popcount}(x),n-\text{popcount}(x))$，则：

$$ans=\min\limits_{x=0}^{2^n-1}(\sum_{i=1}^mf(a_i\oplus x))$$

$a_i$ 在这里看着不是很舒服，考虑设 $cnt(i)$ 表示 $i$ 在 $a$ 中出现的次数，则有：

$$ans=\min\limits_{x=0}^{2^n-1}(\sum_{i=0}^{2^n-1}f(i\oplus x)\times cnt(i))$$

所以，令 $j=i\oplus x$，可以转化为：

$$ans=\min\limits_{x=0}^{2^n-1}(\sum_{i\oplus j =x}f(j)\times cnt(i))$$

里面的东西是一个完完全全的 FWT 板子，所以我们就做完啦！时间复杂度 $O(2^nn+mn)$。


```cpp
#include<bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
const int mod=998244353;
int n,m,a[25][N],f[N];
void XOR(vector<int>&f,int op){
	int len=f.size();
	if(len==1)return;
	vector<int>l,r;
	for(int i=0;i<len/2;++i)l.push_back(f[i]);
	for(int i=len/2;i<len;++i)r.push_back(f[i]);
	XOR(l,op);XOR(r,op);
	for(int i=0;i<len/2;++i)f[i]=(l[i]+r[i])%mod;
	for(int i=len/2;i<len;++i)f[i]=(l[i-len/2]-r[i-len/2]+mod)%mod;
	for(int i=0;i<len;++i)f[i]=f[i]*op%mod;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)scanf("%1d",&a[j][i]);
	}
	swap(n,m);
	vector<int>cnt(1<<n);
	for(int j=1;j<=m;++j){
		int x=0;
		for(int i=1;i<=n;++i)x=x*2+a[i][j];
		++cnt[x];
	}
	vector<int>f;
	for(int i=0;i<(1<<n);++i)f.push_back(min(1ll*__builtin_popcount(i),n-__builtin_popcount(i)));
	XOR(f,1);XOR(cnt,1);
	for(int i=0;i<(1<<n);++i)f[i]=f[i]*cnt[i]%mod;
	XOR(f,499122177);
	int ans=1e9;
	for(int i=0;i<(1<<n);++i)ans=min(ans,f[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：水星湖 (赞：1)

我们把每一行压缩成一个 $W$ 位的整数 $x$ $(0 \le x < 2^W)$，令  
$$
h(x) = \text{出现该行的次数}.
$$
对于一个固定的列翻转模式 $c$（同样用 $W$ 位表示），行 $x$ 翻转后实际得到的行是 $x \oplus c$；而我们可以选择是否翻转该行，从而使得该行贡献的 $1$ 的数目为  
$$
\min(\mathrm{popcount}(x \oplus c), W - \mathrm{popcount}(x \oplus c)).
$$
令  
$$
g(u) = \min(\mathrm{popcount}(u), W - \mathrm{popcount}(u)).
$$
那么对于模式 $c$ 总代价为  
$$
F(c) = \sum_{x} h(x) \, g(x \oplus c).
$$

这正是对函数 $h$ 与 $g$ 的 XOR 卷积。

由于 $2^W \le 262144$，可以使用 FWT 计算卷积，然后枚举所有 $c$ 得到答案的最小值。

---

## 作者：emmoy (赞：1)

提供一个 FWT 做法。

首先，我们看到输入的 $W$ 十分小，于是考虑 $2^W$ 枚举每一列是否翻转的状态，记为 $s$。对于第 $i$ 行，将这一行的数改为用二进制表示，记为 $B_i$。

我们设 $\text{popcount(x)}$ 表示 $x$ 在二进制下 $1$ 的个数，$\oplus$ 表示异或运算，那么说如果 $W-\text{popcount}(B_i\oplus s)<\text{popcount}(B_i\oplus s)$，就说明这一行全部异或一产生的贡献会更小，于是选择异或一。

设 $f(s)$ 表示当每一列是否翻转的状态为 $s$ 时矩阵中一的个数最少是多少，那么容易得出:

$$
f(s)=\sum_{i=1}^H\min(\text{popcount}(B_i\oplus s),W-\text{popcount}(B_i\oplus s))\\
ans=\min_{s=0}^{2^W-1}f(s)
$$

现在我们考虑如何快速求出所有 $f(s)$。

设 $h(s)=\min(\text{popcount}(s),W-\text{popcount}(s))$，$g(s)=\sum_{i=1}^{H}[B_i=s]$。

于是我们考虑化繁一下式子：

$$
\begin{aligned}
f(s)=&\sum_{i=1}^Hh(B_i\oplus s)\\
=&\sum_{i=1}^H\sum_{y=0}^{2^W-1}[B_i\oplus s=y]h(y)\\
=&\sum_{y=0}^{2^W-1}h(y)\sum_{i=1}^H[B_i\oplus y=s]\\
=&\sum_{y\oplus z=s}h(y)g(z)
\end{aligned}
$$

然后就可以用 FWT 快速求解了。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=(1<<18)+10;
int m,n;
ll A[N],B[N];
ll a[N],b[N];
void xorr(ll*f,double type)
{
	for(int len=2;len<=n;len<<=1)
	{
		int mid=len>>1;
		for(int i=0;i<n;i+=len)
		{
			for(int j=0;j<mid;j++)
			{
				f[i+j]+=f[i+j+mid];
				f[i+j+mid]=f[i+j]-2*f[i+j+mid];
				f[i+j]=f[i+j]*type,f[i+j+mid]=f[i+j+mid]*type;
			}
		}
	}
}
int we;
string s;
#define popcount(x) __builtin_popcount(x)
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>we>>m,n=1<<m;
	for(int i=1;i<=we;i++){
		cin>>s;
		int sum=0;
		for(int i=0;i<m;i++) sum=sum+((s[i]-'0')<<i);
		a[sum]++;
	}
	for(int i=0;i<n;i++) b[i]=min(popcount(i),popcount(n-1-i));
	xorr(a,1),xorr(b,1);
	for(int i=0;i<n;i++) a[i]=a[i]*b[i];
	xorr(a,0.5);
	ll ans=1e18;
	for(int i=0;i<n;i++) ans=min(ans,a[i]); 
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：dengchengyu (赞：0)

# abc396_g & CF662C 题解

做 abc 做到了原题。

考虑暴力，我们枚举每一列是否翻转，然后每一行的贡献就是 $0,1$ 个数的最小值，时间复杂度 $O(n2^m)$。

我们把上述东西写成式子，设 $a_i$ 为行的初始状态为 $i$ 的行数，$b_i$ 为 $i$ 二进制 $0,1$ 个数的最小值。我们枚举给每一行异或上的是 $k$，答案为
$$
\sum _{i=0} ^{2^m-1} a_i\times b_{i\oplus k}
$$
在这个式子中，相乘的两个数异或恒为 $k$，于是设 $f_i$ 为 $k=i$ 时的答案，有
$$
f_i=\sum _{j\oplus k} a_j\times b_k
$$
这是异或卷积的形式，直接用 FWT 做即可，复杂度 $O(m2^m)$。

代码如下

```cpp
const int N=1<<18;
int n,m;
void fwt(int *a) {
	for(int i=1;i<1<<m;i<<=1) {
		for(int j=0;j<1<<m;j+=i<<1) {
			fu(k,j,j+i) {
				int t=a[k+i];
				a[k+i]=(a[k]-a[k+i]);
				a[k]+=t;
			}
		}
	}
}
void ifwt(int *a) {
	for(int i=1;i<1<<m;i<<=1) {
		for(int j=0;j<1<<m;j+=i<<1) {
			fu(k,j,j+i) {
				int t=a[k+i];
				a[k+i]=(a[k]-a[k+i]);
				a[k]+=t;
			}
		}
		fu(j,0,1<<m) a[j]=a[j]/2;
	}
}
int a[N],b[N];
char s[20];
signed main(){
	cin>>n>>m;
	fo(i,1,n) {
		scanf("%s",s+1);
		int t=0;
		fo(j,1,m) if(s[j]=='1') t|=(1<<j-1);
		a[t]++;
	}
	#define popc __builtin_popcount
	fu(i,0,1<<m) b[i]=min(popc(i),popc(i^((1<<m)-1)));
	fwt(a),fwt(b);
	fu(i,0,1<<m) a[i]*=b[i];
	ifwt(a);
	int ans=1e18;
	fu(i,0,1<<m) ans=min(ans,a[i]);
	cout<<ans;
	return 0;
}
```

---

## 作者：xiezheyuan (赞：0)

## 简要题意

给定一个 $n\times m$ 的 $01$ 矩阵 $A$，你可以进行任意次操作，每次操作选定一行或一列，将每一个单元格的数字取反，你需要最小化所有数的和，输出这个最小值。

$1\leq n\leq 2\times 10^5,1\leq m\leq 18$。

## 思路

首先注意到 $O(2^m)$ 是可以接受的，于是可以考虑枚举每一列是否操作，然后快速判断一行是否操作（操作显然可交换）。

根据这个思路，可以发现我们需要求的就是下面这个式子：

$$
\min_{S=1}^{2^m-1} \sum_{i=1}^{n}\min(|a_i\oplus S|,m-|a_i\oplus S|)
$$

其中 $a_i$ 表示 $A$ 的第 $i$ 行的 bitmask。

于是只需要快速计算上述式子即可。注意到我们要求和的东西是一个关于 $a_i\oplus S$ 的函数，不妨记 $f(x)=\min(|x|,m-|x|)$，则将式子改写为：

$$
\min_{S=1}^{2^m-1} \sum_{i=1}^{n} f(a_i\oplus S)
$$

由于 $\min$ 结构和异或在本题中似乎不太相容，于是我们只需要对于每一个 $S$ 求出和式的值，然后取最小值即可。我们直接考察和式：

$$
\sum_{i=1}^{n} f(a_i\oplus S)
$$

尝试改为枚举 $a_i\oplus S$：

$$
\sum_{T=1}^{2^m-1} f(T)c_{S\oplus T}
$$

其中 $c_i=\sum_{j}[a_j=i]$ 即 $i$ 在 $a$ 中的出现次数。

将和式进一步改写得：

$$
\sum_{X\oplus Y=S}f(X)c_Y
$$

这是 XOR 卷积的形式，直接用 FWT 解决即可。时间复杂度 $O(n+m2^m)$。

[Submission](https://atcoder.jp/contests/abc396/submissions/63973571)。

---

## 作者：newwzl (赞：0)

## 思路
我们先转换一下题意：给你一个数组 $a$ 包含 $n$ 个长度为 $m$ 的二进制数，让你找出一个二进制数 $s$ 满足 $\sum{\min(\operatorname{popcount}(a_i\operatorname{xor} s),m-\operatorname{popcount}(a_i\operatorname{xor} s))}$ 的值最小，并且输出那个值。

我们定义 $f_{s,i}$ 表示对于二进制数 $s$ 和数字 $i$ 来说，$a$ 中有多少个数字和 $s$ 的[汉明距离](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E8%B7%9D%E7%A6%BB/475174)恰好为 $i$。

最后转移的式子如下：
$$f_{s,i}=\frac{1}{i}\times\sum_{\operatorname{popcount}(t\operatorname{xor} s)=1}{\sum_{k=0}^{i-1}{[k和i不同奇偶]\times f_{t,k}-[k和i同奇偶]\times f_{s,k}}}$$

当然这个式子还是太抽象了，大概说一下含义。

假设每个二进制数都是一个点，然后与之汉明距离为 $1$ 的点连一条边，再设置该点权值为 $a$ 中出现多少次该点，那么 $f_{s,i}$ 就是距离 $s$ 为 $i$ 的点的权值之和。

我们先加上 $\sum{f_{t,i-1}}$ 的值，发现算重了走过 $s$ 的路径，所以减去 $m\times\sum{f_{s,i-2}}$，后面以此类推。

然而算完之后却发现多算了好多。这是因为对于每条路径，都有 $i$ 种开始的方法，也就是乘上 $\frac{1}{i}$ 就可以了。

最终复杂度 $O(2^M\times M^3)$，当然显然可以优化掉一个 $M$，但没必要。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=18,inf=1e18;
int n,m,f[(1<<N)+2][N+2];
int ans;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n>>m;
	ans=inf;
	for(int i=1;i<=n;i++){
		int x=0;
		for(int j=1;j<=m;j++){
			char y;cin>>y;
			x=(x<<1)|(y-'0');
		}
		f[x][0]++;
	}
	for(int i=1;i<=m;i++){
		for(int s=0;s<1<<m;s++){
			for(int j=1;j<=m;j++){
				int t=s^(1<<j-1);
				for(int k=i-1;k>=0;k--){
					if((i^k)&1)f[s][i]+=f[t][k];
					else f[s][i]-=f[s][k];
				}
			}
			f[s][i]/=i;
		}
	}
	for(int s=0;s<1<<m;s++){
		int num=0;
		for(int i=0;i<=m;i++)num+=min(i,m-i)*f[s][i];
		ans=min(ans,num);
	}
	cout<<ans<<"\n";
	return 0;
}
```
顺带，这题评紫真的合适吗……

---

## 作者：PeppaPig_qwq (赞：0)

提供一篇 FWT 的题解。

注意到 $w \le 18$，所以可以枚举每一列有没有被进行操作。

将网格中每一行看成一个二进制数，设 $s_i$ 表示网格第 $i$ 行对应的数，$f(i)$ 表示 $i$ 进行若干次操作能得到的最少的 $1$ 的个数。所以 $f(i)=\min\{popcount(i),w-popcount(i)\}$。

设 $cnt_i$ 表示 $\sum_{j=1}^{h}[s_j=i]$，$g(i)$ 表示网格中被进行操作的列的集合状压后为 $i$，网格中 $1$ 的个数能达到的最少值。
所以 $g(i)=\sum_{j=0}^{2^w-1}cnt_j\times f(j \oplus i)$，答案即为 $\min_{i=0}^{2^w-1}g(i)$。

但是这样复杂度是 $O(2^2w)$ 的，过不了。注意到 $g(i)$ 就是个卷积，FWT 优化即可。

---

## 作者：__vector__ (赞：0)

这题被恶心了很久，不知道为啥一直没有题解。    
### 做法  
显然操作顺序不会影响结果，每一行或每一列最多操作一次。  

注意到最多 $18$ 列，考虑暴力做法，先枚举哪些列执行了操作。    

随后，枚举每一行，如果 $1$ 的数量大于 $0$ 的数量，就翻转这一行。   

考虑将每一行视为一个二进制数。  

问题转化为下面的形式：  
> 给定一个长度为 $n$ 的非负整数序列 $b$，一个整数 $m$，每个数严格小于 $2^{m}$。  
> 定义 $popcount(x)$ 为 $x$ 的二进制表示中 $1$ 的个数。  
> 求出 $\min\limits_{x=0}^{2^m-1}\sum\limits_{i=1}^n\min(popcount(a_i\oplus x),m-popcount(a_i\oplus x))$。

设 $f_{s,i,j}$ 代表所有数异或 $s$，仅考虑最后 $i$ 位，二进制中 $1$ 的数量是 $j$ 的数有多少个。  

遗憾的是，这样仍然很难设计转移方程，主要难点在于，新加入一位 $i'=i+1$ 之后，难以得到新的 $j'$。  

考虑一些更严格的限制，$f_{s,i,j}$ 代表所有数异或 $s$，最后 $i$ 位中有 $j$ 位为 $1$，且前 $m-i$ 位都是 $0$ 的数字个数。  

转移如下：  
1. $f_{s,i,j} \leftarrow f_{s,i,j}+ f_{s,i-1,j}$，这个代表第 $i$ 位为 $0$ 的情况。
2. $f_{s,i,j} \leftarrow f_{s\oplus 2^i,i-1,j-1}$，代表第 $i$ 位为 $1$ 的情况。

另外，初始状态是 $f_{b_i,0,0}\leftarrow f_{b_i,0,0}+1$。

---

## 作者：cyq32ent (赞：0)

第一次赛时通过 G 题，写篇题解纪念一下。

题意：有一个 01 矩阵，可以任意翻转行或列，求操作后矩阵元素之和最小值。

这道题需要用到 [快速沃尔什变换（Fast Walsh Hadamard Transform）](https://oi-wiki.org/math/poly/fwt/#%E5%BC%82%E6%88%96%E8%BF%90%E7%AE%97)。

不难发现翻转的顺序是不重要的。因此我们考虑将列的翻转表示为 $C$（$C$ 的第 $i$ 为表示第 $i$ 列是否翻转）。

设某一行为 $r$。那么，该行经过列翻转后为 $r \operatorname{xor} C$。设 $n_r$ 为 $\operatorname{popcnt}(r \operatorname{xor} C)$。我们也可以决定这一行是否翻转。所以这一行内 $1$ 的个数的最小值为 $\min(n_r,W-n_r)$。

我们令 $f_i$ 为二进制表示为 $i$ 的行的数量，$g_i$ 为 $\min(\operatorname{popcnt}(i),W-\operatorname{popcnt}(i))$，则当列的翻转为 $C$ 时，答案为 $h_C=\sum_{r}f_rg_{r \operatorname{xor} C}=\sum_{r\operatorname{xor}s=C}f_rg_s$。这样，我们可以直接用 FWT 算出所有的 $h_C$，并取最小值即可。时间复杂度 $\mathcal O(2^WW)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll f[1<<18],g[1<<18],ans=LLONG_MAX,H,W,n;
void fwt(ll *a,int inv){
	for(int len=1;len<n;len<<=1){
		for(int i=0;i<n;i+=(len<<1)){
			for(int j=0;j<len;j++){
				ll u=a[i+j],v=a[i+j+len];
				a[i+j]=u+v;
				a[i+j+len]=u-v;
			}
		}
	}
	if(inv)for(int i=0;i<n;i++)a[i]/=n;
}int main(){
	cin>>H>>W;
	n=1<<W;
	for(int i=0;i<H;i++){
		string s;cin>>s;
		int m=0;for(char c:s)m=(m<<1)|(c-'0');f[m]++;
	}for(int i=0;i<n;i++)g[i]=min((ll)__builtin_popcount(i),W-__builtin_popcount(i));
	fwt(f,0);fwt(g,0);
	for(int i=0;i<n;i++)f[i]*=g[i];
	fwt(f,1);
	for(int i=0;i<n;i++)ans=min(ans,f[i]);
	cout<<ans;
	return 0;
}

```

本题的数据非常水，实际上不用 FWT，直接暴力计算 $h_C$，通过卡常也可以通过。

---

