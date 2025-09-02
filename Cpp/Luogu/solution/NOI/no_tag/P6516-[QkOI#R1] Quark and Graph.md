# [QkOI#R1] Quark and Graph

## 题目背景

SPFA 被卡时在做什么？有没有空？可以来计数吗？

## 题目描述

现有一张边权全为 $1$ 的有标号简单无向连通图，其包含 $n$ 个节点和 $m$ 条边，已知该图上点 $1$ 到所有点的最短路长，求这张图有多少种形态。

特别地，我们认为点 $1$ 到点 $1$ 的最短路为 $0$。

两个图的形态不同当且仅当存在至少一条边 $(u,v)$ 在一张图中出现且在另一张图中没出现。

**由于 little_sun 太巨了，所以数据保证至少存在一张满足条件的图。**

答案对 $998244353$ 取模。

## 说明/提示

### 样例解释

对于第一个样例，有 $\{(1,2),(1,3),(2,4)\}$ 和 $\{(1,2),(1,3),(3,4)\}$ 两种形态。

对于第二个样例，我想到了一个绝妙的解释，可惜这里空白太小，写不下。

### 数据范围

**本题采用捆绑测试。**

- Subtask 1（10 pts），满足 $n\le 7$，$m\le 14$，时限 1s；
- Subtask 2（20 pts），满足 $n\le 50$，$m\le 600$，时限 1s；
- Subtask 3（20 pts），满足 $n\le 1000$，$m\le 5000$，时限 1s；
- Subtask 4（50 pts），无特殊限制，时限 3s。

对于 $100\%$ 的数据，满足 $n\le 10^5$，$m\le 2\times 10^5$。设 $t_i=\sum_j[d_j=i]$，还应满足 $\sum_{i}t_it_{i-1}\le 2\times 10^5$。

**本题强制开启 O2 优化。**

## 样例 #1

### 输入

```
4 3
0 1 1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
5 5
0 1 1 2 2
```

### 输出

```
12```

## 样例 #3

### 输入

```
8 12
0 2 2 2 2 1 1 1```

### 输出

```
128601```

# 题解

## 作者：LCuter (赞：19)

## F - Quark and Graph

#### $\text{Description}$

现有一 $n$ 个点 $m$ 条边的有标号简单无向连通图，边权全为 $1$。

已知 $1$ 节点到所有节点的最短路长，求这张图有多少种可能的形态，答案对 $998244353$ 取模。

两张图 $G=(V,E)$ 和 $G'=(V',E')$ 形态不同当且仅当存在一个二元组 $(u,v)$ 满足 $u,v\in[1,n]\cap N_+,(u,v)\in E,(u,v)\notin E'$。

#### $\text{Solution}$

按照最短路长分层（最短路长即层数），记 $1$ 到 $x$ 的最短路长为 $d_x$，定义 $t_i,T$：

$$t_i=\displaystyle\sum_{j=1}^n[d_j=i],T=\max\limits_{t_i>0}\{i\}$$

我们称相邻两层之间的边为树边，同层之间的边为非树边，定义 $f_i,f^\ast_i$ 分别表示树边取 $i$ 条的方案数，非树边取 $i$ 条的方案数，那么最后答案为：

$$Ans=\displaystyle\sum_{i+j=m}f_i\cdot f^\ast_j$$

上式是一个卷积的形式，我们可以分别求出 $f_i,f^\ast_i $，然后再卷起来。

先考虑 $f_i$。发现最后答案是第 $1$ 层到第 $T$ 层与其上一层之间的答案的卷积。所以我们分别考虑每一层。我们将每一层与其上一层之间的边按照当前层的点分为 $t_i$ 个部分，第 $i$ 个部分包含的是其中一个端点为 $i$ 节点的边。那么每一层与其上一层的答案又是其每个部分的答案的卷积。每个部分的生成函数根据二项式定理可以得到是：

$$K(x)=(1+x)^{t_{i-1}}-1$$

进一步地，每一层的答案实际上是：

$K^{\ast}(x)=[(1+x)^{t_{i-1}}-1]^{t_i}$

那么树边的生成函数实际上就是：

$F(x)=\displaystyle \prod\limits_{i=1}^T[(1+x)^{t_{i-1}}-1]^{t_{i}}$

PS：做到这一步时，我们把每一层的生成函数处理出来，然后用类似合并果子的方法，每次取出次数最低的两个多项式相乘，在本题的限制下可以做到 $O(n\log^2 n)$，做法来自 EA。

为了方便处理，我们定义 $G(x)$：

$$G(x)=F(x-1)=\displaystyle\prod\limits_{i=1}^T[x^{t_{i-1}}-1]^{t_{i}}$$

右边是乘积，不好搞，对它取 $\ln$ 后再做 $\exp$：

$$G(x)=\displaystyle\exp\ln \prod_{i=1}^T[x^{t_{i-1}}-1]^{t_{i}}$$

然后常规地乘化加，幂化乘：

$$G(x)=\displaystyle\exp[\sum_{i=1}^Tt_i\ln(x^{t_{i-1}}-1) ]$$

然后需要把 $\ln $ 化成我们想要的形式：

$$G(x)=\displaystyle\exp\{\sum_{i=1}^Tt_i[\ln(-1)-\ln(\frac{1}{1-x^{t_{i-1}}})] \}$$

发现前半部分可以拆出来：

$$G(x)=\displaystyle\frac{(-1)^{\sum\limits_{i=1}^Tt_i}}{\exp[\sum\limits_{i=1}^Tt_i\cdot\ln(\frac{1}{1-x^{t_{i-1}}})]}$$

我们定义 $H(x)$：

$$H(x)=\displaystyle\sum\limits_{i=1}^Tt_i\cdot\ln(\frac{1}{1-x^{t_{i-1}}})$$

然后对 $\ln$ 来一波泰勒展开：

$$H(x)=\displaystyle\sum\limits_{i=1}^Tt_i\cdot\sum\limits_{j=1}^{+\infty}\frac{x^{jt_{i-1}}}{j}$$

记 $c_k=\displaystyle\sum\limits_{i=1}^Tt_i[t_{i-1}=k]$

枚举 $k$，合并一下同类项：

$$H(x)=\displaystyle\sum_{k=1}^nc_k\sum\limits_{j=1}^{+\infty}\frac{x^{jk}}{j}$$ 

由于我们实际要求的：

$$G(x)=\displaystyle\frac{(-1)^{n-1}}{\exp H(x)}$$

记树边总数为 $s$，我们要求出 $G$ 的前 $s+1$ 项，因为高次项可以通过二项式定理贡献到低次项。

那么怎么通过 $G(x)=F(x-1)$ 求得 $F(x)$ 呢？

注意到 $G(x+ 1)=F(x)$，我们展开按照 CF923E 的做法即可。

---

现在来考虑非树边的生成函数 $F^\ast(x)$。

先求非树边总数：

$S=\displaystyle\sum_{i=1}^T\frac{t_i(t_{i}-1)}{2}$

那么生成函数应该是：

$$F^\ast(x)=\displaystyle\sum_{i=0}^{+\infty}{S\choose i}x^i$$

由于我们是在模 $P=998244353$ 意义下进行运算，所以当 $S>P$ 时会有些奇怪的问题。进一步分析，发现当 $i>S\bmod{P}$ 时系数都为 $0$。这是因为将组合数拆开后，$(S-i)!$ 没能把 $S!$ 的质因子中的 $P$ 全部消去。故我们只需计算：

$$F^\ast(x)=\displaystyle\sum_{i=0}^{\min(m,S\bmod{P})}{S\choose i}x^i$$

我们观察组合数公式：

$$\displaystyle{n\choose m}=\frac{n!}{m!(n-m)!}$$

在式子中，$m$ 的阶乘由于其比较小，我们在上面预处理时已经求过了，所以重点观察另两个阶乘。

注意到我们要求的实际上是：

$$S^{\underline{k}},(0\le k\le S\bmod{P})$$

在求值的时候动态维护一个后缀积即可。

最后复杂度实际上和树边总数有关（一个 log），那个奇怪的限制实际上是对树边总数一个粗略的估计。

---

## 作者：Mr_Wu (赞：5)

## 题面
已知一个 $n$ 个点的无权无向图中 1 号点到 $i (1\le i\le n)$ 号点的最短路 $d_i$，试求恰好 $m$ 条边的方案数。

数据范围：$n\le 10^5, m\le 2\cdot 10^5$，令 $t_i=\sum_j [d_j=i]$ 则有 $\sum_i t_it_{i+1}\le 2\cdot 10^5$。

## 题解

将图变成分层图，边分为两部分，一部分是每层间的边，一部分是相邻两层的边，所以不难知道答案是

$$ [x^m] \prod_{i=0}^{D-1} \left( \sum_{n\ge 1} x^n \binom{a_i}{n} \right)^{a_{i+1}} \prod_{i=0}^n \left( \sum_{n\ge 0} x^n \binom{a_i(a_i-1)/2}{n} \right) $$

这个生成函数是

$$ \left( \prod_{i=0}^{D-1} ((x+1)^{a_i} -1) ^{a_{i+1}} \right) (x+1)^{\sum\limits_{i=0}^D a_i(a_i-1)/2 } $$

接下来应当注意到题目中奇怪的数据范围 $\sum\limits_i a_ia_{i+1} \le 2\cdot 10^5$，令其为 $S$，则可以发现左侧的乘积式的长度是 $S$ 级别的，所以我猜测这里应该已经能够做了，但我不是太清楚。

言归正传，接下来使用套路：

$$ \prod_{i=0}^{D-1} ((x+1)^{a_i} -1) ^{a_{i+1}} = \exp \sum_{i=0}^{D-1} a_{i+1} \ln ((x+1)^{a_i} -1) $$

好吧这是个什么玩意，ln 里边的形式幂级数一次项根本就是 0。

所以重新做一遍，我们做换元 $z=x+1$，再做一次：

$$
G(z)=\prod_{i=0}^{D-1} (z^{a_i} - 1) ^{a_{i+1}} = (-1)^{\sum\limits_{i=1}^D a_i} \exp \left( \sum_{i=0}^{D-1} a_{i+1} \ln (1-z^{a_i})  \right) = (-1)^{\sum\limits_{i=1}^D a_i} \exp \left( - \sum_{i=0}^{D-1} a_{i+1} \sum_{j\ge 1} \frac{z^{ja_i}}{j}  \right)
$$

如果我们要求出这个形式幂级数的前 $L$ 项，由于 exp 里的形式幂级数的有效项为 $O(\sum_i \frac{L}{i})=O(L\log L)$，因此求出这个式子的复杂度是 $O(L\log L)$。

现在我们需要还原换元之前的式子，很明显我们需要知道这个形式幂级数（多项式）所有的信息，所以求出 $[z^{0\sim S}]G(z)$。

$$
\begin{aligned}
F(x) = G(x+1) = \sum_{i\ge 0} g_i (x+1)^i = \sum_{i\ge 0} g_i \sum_{j\ge 0} \binom{i}{j} x^j = \sum_{j\ge 0} x^j \sum_{i\ge 0} g_i \binom{i}{j} \\
= \sum_{j\ge 0} x^j \sum_{i\ge 0} g_{i+j} \frac{(i+j)!}{i!j!} = \sum_{j\ge 0} \frac{x^j}{j!} \sum_{i\ge 0} \frac{h_{S-i-j}}{i!}
\end{aligned}
$$

其中 $h_i=g_{S-i} (S-i)!$，所以这里也 $O(S\log S)$ 解决。

现在要说刚才被忽略的右半部分，理性分析一下发现项数不多所以我们维护下降幂就好了。

时间复杂度 $O(n + S\log S + m\log m)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define ri register int

const int MAXN = 1000005, MOD = 998244353, Gen = 3;

ll q_pow(ll a, ll b, ll p = MOD) {
	ll ret = 1;
	for (; b; a = a * a % p, b >>= 1) if (b & 1) ret = ret * a % p;
	return ret;
}
ll inv(ll x, ll p = MOD) { return q_pow(x, p - 2, p); }

inline int add(int x, int y) { return x + y > MOD ? x + y - MOD : x + y; }
inline int dec(int x, int y) { return x - y < 0 ? x - y + MOD : x - y; }
inline void Add(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void Dec(int& x, int y) { x -= y; if (x < 0) x += MOD; }

int rev[21][MAXN], fac[MAXN], ifac[MAXN], I[MAXN];
int rt[MAXN], irt[MAXN];
void Dft(int* A, int LIM, int L) {
	for (ri i = 0; i < LIM; ++i) if (i < rev[L][i]) swap(A[i], A[rev[L][i]]);
	for (ri l = 2; l <= LIM; l <<= 1) {
		for (ri i = 0; i < LIM; i += l) {
			for (ri j = 0; j < (l >> 1); ++j) {
				ll x = A[j | i], y = (ll)A[j | i | (l >> 1)] * rt[l | j] % MOD;
				A[j | i] = add(x, y), A[j | i | (l >> 1)] = dec(x, y);
			}
		}
	}
}
void iDft(int* A, int LIM, int L) {
	for (ri i = 0; i < LIM; ++i) if (i < rev[L][i]) swap(A[i], A[rev[L][i]]);
	for (ri l = 2; l <= LIM; l <<= 1) {
		for (ri i = 0; i < LIM; i += l) {
			for (ri j = 0; j < (l >> 1); ++j) {
				ll x = A[j | i], y = (ll)A[j | i | (l >> 1)] * irt[l | j] % MOD;
				A[j | i] = add(x, y), A[j | i | (l >> 1)] = dec(x, y);
			}
		}
	}
	int invLIM = inv(LIM);
	for (ri i = 0; i < LIM; ++i) A[i] = 1ll * A[i] * invLIM % MOD;
}
void Multiply(int* A, int* B, int LIM, int L) {
	Dft(A, LIM, L), Dft(B, LIM, L);
	for (ri i = 0; i < LIM; ++i) A[i] = 1ll * A[i] * B[i] % MOD;
	iDft(A, LIM, L);
}

int Tinv[MAXN];
void Inverse(const int* F, int* G, int LIM, int L) {
	G[0] = inv(F[0]);
	for (ri lim = 2, l = 1; lim <= LIM; lim <<= 1, ++l) {
		for (ri i = 0; i < lim; ++i) Tinv[i] = F[i];
		for (ri i = lim; i < (lim << 1); ++i) Tinv[i] = 0;
		Dft(Tinv, lim << 1, l + 1), Dft(G, lim << 1, l + 1);
		for (ri i = 0; i < (lim << 1); ++i) G[i] = dec(add(G[i], G[i]), 1ll * Tinv[i] * G[i] % MOD * G[i] % MOD);
		iDft(G, lim << 1, l + 1);
		for (ri i = lim; i < (lim << 1); ++i) G[i] = 0;
	}
}
void Derivative(int* F, int LIM) {
	for (ri i = 0; i < LIM - 1; ++i) F[i] = 1ll * F[i + 1] * (i + 1) % MOD;
	F[LIM - 1] = 0;
}
void Inter(int* F, int LIM) {
	for (ri i = LIM - 1; i >= 1; --i) F[i] = 1ll * F[i - 1] * I[i] % MOD;
	F[0] = 0;
}
int Tln[MAXN];
void Ln(int* F, int LIM, int L) {
	Inverse(F, Tln, LIM, L);
	Derivative(F, LIM);
	Multiply(F, Tln, LIM << 1, L + 1);
	Inter(F, LIM);
	for (ri i = 0; i < (LIM << 1); ++i) Tln[i] = 0;
}

int Texp[MAXN];
void Exp(const int* F, int* G, int LIM, int L) {
	G[0] = 1;
	for (ri lim = 2, l = 1; lim <= LIM; lim <<= 1, ++l) {
		for (ri i = 0; i < lim; ++i) Texp[i] = G[i];
		for (ri i = lim; i < (lim << 1); ++i) Texp[i] = 0;
		Ln(G, lim, l);
		for (ri i = 0; i < lim; ++i) G[i] = dec(F[i], G[i]);
		G[0] = add(G[0], 1);
		Multiply(G, Texp, lim << 1, l + 1);
		for (ri i = lim; i < (lim << 1); ++i) G[i] = 0;
	}
}

int N, M, LIM = 1, L, a[MAXN], b[MAXN], D, S;
int F[MAXN], G[MAXN], H[MAXN];
int main() {
	scanf("%d%d", &N, &M); int t;
	for (int i = 1; i <= N; ++i) scanf("%d", &t), ++a[t], D = max(t, D);
	for (int i = 0; i < D; ++i) S += a[i] * a[i + 1];

	while (LIM <= max(M, S) + 2) {
        LIM <<= 1, ++L;
        for (ri i = 0; i < LIM; ++i) rev[L][i] = (rev[L][i >> 1] >> 1) | ((i & 1) << (L - 1));
        irt[LIM] = rt[LIM] = 1; int Wn = q_pow(Gen, (MOD - 1) / LIM), iWn = inv(Wn);
        for (ri i = 1; i < (LIM >> 1); ++i) rt[i | LIM] = 1ll * rt[(i - 1) | LIM] * Wn % MOD, irt[i | LIM] = 1ll * irt[(i - 1) | LIM] * iWn % MOD;
    }
    LIM <<= 1, ++L;
    for (ri i = 0; i < LIM; ++i) rev[L][i] = (rev[L][i >> 1] >> 1) | ((i & 1) << (L - 1));
    irt[LIM] = rt[LIM] = 1; int Wn = q_pow(Gen, (MOD - 1) / LIM), iWn = inv(Wn);
    for (ri i = 1; i < (LIM >> 1); ++i) rt[i | LIM] = 1ll * rt[i - 1 | LIM] * Wn % MOD, irt[i | LIM] = 1ll * irt[i - 1 | LIM] * iWn % MOD;
    LIM >>= 1, --L;
    fac[0] = ifac[0] = fac[1] = ifac[1] = I[1] = 1;
    for (ri i = 2; i <= LIM; ++i) {
        fac[i] = 1ll * fac[i - 1] * i % MOD, I[i] = 1ll * (MOD - MOD / i) * I[MOD % i] % MOD, ifac[i] = 1ll * ifac[i - 1] * I[i] % MOD;
    }
    
    for (int i = 0; i < D; ++i) Dec(b[a[i]], a[i + 1]);
	for (int i = 0; i < LIM; ++i) if (b[i]) {
		for (int j = 1; j * i < LIM; ++j) Add(F[j * i], 1ll * b[i] * I[j] % MOD);
	}
	Exp(F, G, LIM, L);
	if (N % 2 == 0) {
		for (int i = 0; i < LIM; ++i) G[i] = dec(0, G[i]);
	}
	for (int i = 0; i < LIM; ++i) H[i] = F[i] = 0;
	for (int i = 0; i <= S; ++i) H[S - i] = 1ll * G[i] * fac[i] % MOD;
	for (int i = 0; i <= S; ++i) F[i] = ifac[i];
	Multiply(H, F, LIM << 1, L + 1);
	for (int i = 0; i <= S; ++i) F[i] = 1ll * H[S - i] * ifac[i] % MOD;
	for (int i = S + 1; i < LIM; ++i) F[i] = 0;
	int sum = 1, tmp = 0;
	for (int i = 0; i <= D; ++i) Add(tmp, 1ll * a[i] * dec(a[i], 1) % MOD * I[2] % MOD);
	for (int i = 0; i < LIM; ++i) G[i] = 0;
	for (int i = 0; i <= max(M, S); ++i) G[i] = 1ll * ifac[i] * sum % MOD, sum = 1ll * sum * tmp % MOD, Dec(tmp, 1);
	Multiply(F, G, LIM << 1, L + 1);
	printf("%d\n", F[M]);
	return 0;
}
```

---

## 作者：jun头吉吉 (赞：4)

## 题意
给出一张$n$个点、$m$条边构成的无向图，已知$1$号点到各定点的最短距离$d_i$，求方案数（对$998244353$取模）

设 $t_i=\sum_j[d_j=i]$，还应满足$\sum_{i}t_it_{i-1}\le 2\times 10^5$
## 题解
这里提供一种大常数的$\mathcal{O}(n\log^2n)$做法，大佬轻喷。

~~首先题目里处处是提示，~~ 观察数据范围，考虑建一张分层图，那么可以把边分成两部分：
- 从前一层到后一层的
- 在一层中连来连去的

那么考虑生成函数。对于前一部分，考虑两个之间的生成函数为$1+x$，那么$t_i$个到一个的生成函数为$(1+x)^{t_i}$，但因为不能不连边，常数项强制为$0$，即$(1+x)^{t_i}-1$。那么连到$t_{i+1}$在次方就行了。

于是对于第一部分生成函数有：
$$\prod_{i=0}^{\max(d)-1}((1+x)^{t_i}-1)^{t_{i+1}}$$
这个我们可以$\ln$+$\exp$实现快速幂，在分治死算得到。直接copy[模板](https://www.luogu.com.cn/blog/CJL/caiji-de-poly)即可。

第二部分一共有$\sum_{i=0}^{\max(d)}\tbinom{t_i}{2}$条边可选，因此生成函数是
$$(1+x)^{\sum_{i=0}^{\max(d)}\tbinom{t_i}{2}}$$

用一下上面的板子就ok了。
## 代码
贴上菜鸡的大常数代码，仅供对拍...
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
	template <typename T>inline void read(T& t){
		t=0;int f=0;char ch=getc();while (!isdigit(ch)){if(ch=='-')f = 1;ch=getc();}
	    while(isdigit(ch)){t=t*10+ch-48;ch = getc();}if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
}
namespace out{
	char buffer[1<<21];int p1=-1;const int p2 = (1<<21)-1;
	inline void flush(){fwrite(buffer,1,p1+1,stdout),p1=-1;}
	inline void putc(const char &x) {if(p1==p2)flush();buffer[++p1]=x;}
	template <typename T>void write(T x) {
		static char buf[15];static int len=-1;if(x>=0){do{buf[++len]=x%10+48,x/=10;}while (x);}else{putc('-');do {buf[++len]=-(x%10)+48,x/=10;}while(x);}
		while (len>=0)putc(buf[len]),--len;
	}
}
using namespace std;
template<const int mod>
struct modint{
    int x;
    modint<mod>(int o=0){x=o;}
    modint<mod> &operator = (int o){return x=o,*this;}
    modint<mod> &operator +=(modint<mod> o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint<mod> &operator -=(modint<mod> o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint<mod> &operator *=(modint<mod> o){return x=1ll*x*o.x%mod,*this;}
    modint<mod> &operator ^=(int b){
        modint<mod> a=*this,c=1;
        for(;b;b>>=1,a*=a)if(b&1)c*=a;
        return x=c.x,*this;
    }
    modint<mod> &operator /=(modint<mod> o){return *this *=o^=mod-2;}
    modint<mod> &operator +=(int o){return x=x+o>=mod?x+o-mod:x+o,*this;}
    modint<mod> &operator -=(int o){return x=x-o<0?x-o+mod:x-o,*this;}
    modint<mod> &operator *=(int o){return x=1ll*x*o%mod,*this;}
    modint<mod> &operator /=(int o){return *this *= ((modint<mod>(o))^=mod-2);}
	template<class I>friend modint<mod> operator +(modint<mod> a,I b){return a+=b;}
    template<class I>friend modint<mod> operator -(modint<mod> a,I b){return a-=b;}
    template<class I>friend modint<mod> operator *(modint<mod> a,I b){return a*=b;}
    template<class I>friend modint<mod> operator /(modint<mod> a,I b){return a/=b;}
    friend modint<mod> operator ^(modint<mod> a,int b){return a^=b;}
    friend bool operator ==(modint<mod> a,int b){return a.x==b;}
    friend bool operator !=(modint<mod> a,int b){return a.x!=b;}
    bool operator ! () {return !x;}
    modint<mod> operator - () {return x?mod-x:0;}
	modint<mod> &operator++(int){return *this+=1;}
};
const int N=4e6+5;

const int mod=998244353;
const modint<mod> GG=3,Ginv=modint<mod>(1)/3,I=86583718;
struct poly{
	vector<modint<mod>>a;
	modint<mod>&operator[](int i){return a[i];}
	int size(){return a.size();}
	void resize(int n){a.resize(n);}
	void reverse(){std::reverse(a.begin(),a.end());}
	void print(){for(int i=0;i<a.size();i++)printf("%d ",a[i].x);puts("");}
};
int rev[N];
inline int ext(int n){int k=0;while((1<<k)<n)k++;return k;}
inline void init(int k){int n=1<<k;for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));}
inline void ntt(poly&a,int k,int typ){
	int n=1<<k;
	for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<n;mid<<=1){
		modint<mod> wn=(typ>0?GG:Ginv)^((mod-1)/(mid<<1));
		for(int r=mid<<1,j=0;j<n;j+=r){
			modint<mod> w=1;
			for(int k=0;k<mid;k++,w=w*wn){
				modint<mod> x=a[j+k],y=w*a[j+k+mid];
				a[j+k]=x+y,a[j+k+mid]=x-y;
			}
		}
	}
	if(typ<0){
		modint<mod> inv=modint<mod>(1)/n;
		for(int i=0;i<n;i++)a[i]*=inv;
	}
}
inline poly one(){poly a;a.a.push_back(1);return a;}
poly operator +(poly a,poly b){
	int n=max(a.size(),b.size());a.resize(n),b.resize(n);
	for(int i=0;i<n;i++)a[i]+=b[i];return a;
}
poly operator -(poly a,poly b){
	int n=max(a.size(),b.size());a.resize(n),b.resize(n);
	for(int i=0;i<n;i++)a[i]-=b[i];return a;
}
inline poly operator*(poly a,poly b){
	int n=a.size()+b.size()-1,k=ext(n);
	a.resize(1<<k),b.resize(1<<k),init(k);
	ntt(a,k,1);ntt(b,k,1);for(int i=0;i<(1<<k);i++)a[i]*=b[i];
	ntt(a,k,-1),a.resize(n);return a;
}
inline poly operator*(poly a,modint<mod> b){for(int i=0;i<a.size();i++)a[i]*=b;return a; }
inline poly operator/(poly a,modint<mod> b){for(int i=0;i<a.size();i++)a[i]/=b;return a; }
inline poly operator-(poly a){for(int i=0;i<a.size();i++)a[i]=-a[i];return a; }
poly inv(poly F,int k){
	int n=1<<k;F.resize(n);
	if(n==1){F[0]=modint<mod>(1)/F[0];return F;}
	poly G,H=inv(F,k-1);
	G.resize(n),H.resize(n<<1),F.resize(n<<1);
	for(int i=0;i<n/2;i++)G[i]=H[i]*2;
	init(k+1),ntt(H,k+1,1),ntt(F,k+1,1);
	for(int i=0;i<(n<<1);i++)H[i]=H[i]*H[i]*F[i];
	ntt(H,k+1,-1),H.resize(n);
	for(int i=0;i<n;i++)G[i]-=H[i];return G;
}
inline poly inv(poly a){
	int n=a.size();
	a=inv(a,ext(n)),a.resize(n);return a;;
}
inline poly deriv(poly a){//求导 
	int n=a.size()-1;
	for(int i=0;i<n;i++)a[i]=a[i+1]*(i+1);
	a.resize(n);return a;
}
inline poly inter(poly a){//求原 
	int n=a.size()+1;a.resize(n);
	for(int i=n;i>=1;i--)a[i]=a[i-1]/i;
	a[0]=0;return a;
}
inline poly ln(poly a){
	int n=a.size();
	a=inter(deriv(a)*inv(a));
	a.resize(n);return a;
}
poly exp(poly a,int k){
	int n=1<<k;a.resize(n);
	if(n==1)return one();
	poly f0=exp(a,k-1);f0.resize(n);
	return f0*(one()+a-ln(f0)); 
}
poly exp(poly a){
	int n=a.size();
	a=exp(a,ext(n));a.resize(n);return a;
}
inline poly pow(poly a,modint<mod> k){//保证a[0]=1 
	a=ln(a);for(int i=0;i<a.size();i++)a[i]*=k.x;
	return exp(a);
}
struct modpair{
	//用于快速幂中的次数
	modint<mod>k1;modint<mod-1>k2;
	struct trueint{
		double lg;int x;
 		trueint &operator=(int o){return x=o,lg=log10(o),*this;}
 		trueint &operator+=(int o){return lg<=8&&(x+=o,lg=log10(x)),*this;}
		trueint &operator*=(int o){return x*=o,lg+=log10(o),*this;}
	}k3;
	modpair(modint<mod>_1,modint<mod-1>_2,trueint _3):k1(_1),k2(_2),k3(_3){}
	modpair(int o=0){k1=o,k2=o,k3=o;}
    modpair &operator = (int o){return k1=o,k2=o,k3=o,*this;}
    modpair &operator +=(int o){return k1+=o,k2+=o,k3+=o,*this;}
    modpair &operator *=(int o){return k1*=o,k2*=o,k3*=o,*this;}
    friend modpair operator +(modpair a,int o){return a+=o;}
    friend modpair operator *(modpair a,int o){return a*=o;}
    modpair operator-(){return modpair(k1,k2,k3);}
};
inline poly pow2(poly a,modpair m){//不保证a[0]=1 
	int k=0;modint<mod> val;
	while(a[k]==0&&k<a.size())k++;
	if(k==a.size()||k!=0&&m.k3.lg>8||1ll*m.k3.x*k>=a.size()){
	for(int i=0;i<a.size();i++)a[i]=0;return a;}//bye~
	val=a[k];poly b;b.resize(a.size()-k);
	for(int i=0;i<b.size();i++)b[i]=a[i+k]/val;
	b=pow(b,m.k1);for(int i=0;i<a.size();i++)a[i]=0;
	for(int i=0;i<b.size()&&i+k*m.k1.x<a.size();i++)
		a[i+k*m.k1.x]=b[i]*(val^m.k2.x);
	return a;
}
int n,m,t[N],M;
#define mid (l+r>>1)
poly solve(int l,int r){
	if(l==r){
		//((1+x)^t[l]-1)^t[l+1]
		//printf("%d,%d\n",l,r);
		poly F;F.resize(t[l]*t[l+1]+1);
		F[0]=F[1]=1;F=pow(F,t[l]);F[0]=0;
		//F.print();
		F=pow2(F,modpair(t[l+1]));
		//F.print();
		return F;
	}
	poly F=solve(l,mid)*solve(mid+1,r);
	//printf("%d,%d\n",l,r);
	if(F.size()>=m+1)F.resize(m+1);
	//F.print();
	return F;
}
#define C(x) (1ll*(x)*((x)-1)/2)
signed main(){
	in::read(n,m);for(int i=1,d;i<=n;i++)in::read(d),t[d]++,M=max(M,d);
	poly f=solve(0,M-1),g;g.resize(m+1);g[0]=g[1]=1;
	//for(int i=0;i<f.size();i++)printf("%d ",f[i].x);puts("");
	modint<mod>T=0;for(int i=0;i<=n;i++)T+=C(t[i]);
	f=f*pow(g,T);out::write(f[m].x);
	out::flush();
	return 0;
}
```

---

