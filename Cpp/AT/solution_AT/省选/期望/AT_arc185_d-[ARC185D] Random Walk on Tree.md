# [ARC185D] Random Walk on Tree

## 题目描述

有一棵包含 $N \times M + 1$ 个顶点的树，顶点编号为 $0, 1, \dots, N \times M$。第 $i$ 条边（$1 \leq i \leq N \times M$）连接顶点 $i$ 和顶点 $\max(i - N, 0)$。

此外，顶点 $0$ 已经被染色，其他顶点尚未染色。

高桥君现在位于顶点 $0$。只要存在未被染色的顶点，他就会重复进行如下操作：

- 从当前所在顶点的相邻顶点中，等概率随机选择一个顶点并移动到该顶点。（每次选择都是独立的。）如果当前所在顶点尚未被染色，则将其染色。

请你求出进行操作的次数的期望值，并对 $998244353$ 取模后输出。

期望值 $\bmod\ 998244353$ 的定义：可以证明，所求的期望值一定是有理数。在本题的约束下，将其表示为最简分数 $\frac{P}{Q}$ 时，$Q \not\equiv 0 \pmod{998244353}$ 也成立。此时，存在唯一的整数 $R$ 满足 $R \times Q \equiv P \pmod{998244353},\ 0 \leq R < 998244353$。请输出这个 $R$。

## 说明/提示

### 数据范围

- $1 \leq N \leq 2 \times 10^5$
- $1 \leq M \leq 2 \times 10^5$
- $N, M$ 均为整数

### 样例解释 1

高桥君可能按如下方式行动：

- 移动到顶点 $1$ 并将其染色。该操作被选择的概率为 $\frac{1}{2}$。
- 移动到顶点 $0$。该操作被选择的概率为 $\frac{1}{2}$。
- 移动到顶点 $1$。该操作被选择的概率为 $\frac{1}{2}$。
- 移动到顶点 $3$ 并将其染色。该操作被选择的概率为 $\frac{1}{2}$。
- 移动到顶点 $1$。该操作被选择的概率为 $1$。
- 移动到顶点 $0$。该操作被选择的概率为 $\frac{1}{2}$。
- 移动到顶点 $2$ 并将其染色。该操作被选择的概率为 $\frac{1}{2}$。
- 移动到顶点 $4$ 并将其染色。该操作被选择的概率为 $\frac{1}{2}$。

高桥君以这种方式行动的概率为 $\frac{1}{128}$，此时操作次数为 $8$。操作次数的期望值为 $20$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2```

### 输出

```
20```

## 样例 #2

### 输入

```
123456 185185```

### 输出

```
69292914```

# 题解

## 作者：xwh_Marvelous (赞：6)

提供一种由 DP 角度思考的方法。

分析一下问题，它给出的图形是一个点挂了 $n$ 条长为 $m$ 的链的图，不难发现当我们走到了每条链的叶子就把这条链都涂完了。

定义一个点是有效点当且仅当所在链的叶子未被涂色，在行走过程中大致分为两个阶段：

1. 从 0 号点向叶子行走。
2. 从叶子回到 0 号点。

定义深度为距离 0 号点的距离。对于阶段一，直接设 $f_i$ 表示深度为 $i$ 的点走到叶子的期望步数是行不通的，因为此时转移会成环，需要上高斯消元，直接爆炸。

于是考虑使用 P3750 [六省联考 2017] 分手是祝愿的 trick，设 $f_i$ 表示由深度为 $i$ 的有效点走到深度为 $i+1$ 的有效点所花的期望步数。

写一下转移式：

$$f_i=\frac 1 2 (f_{i-1}+f_i+1)+\frac 1 2$$
移项，
$$f_i-\frac1 2 f_i=\frac 1 2 (f_{i-1}+1)+\frac 1 2$$
整理，
$$f_i=f_{i-1}+2$$

考虑一下特殊情况 $f_0$，其特殊之处在于处在这个点有概率走到无效点上，此时需要先回到 0 号点，记 $p_i$ 表示从深度为 $i$ 的点走到深度为 $i-1$ 的点所花的期望步数。

枚举一下当前有 $k$ 条链已经被涂色了，为了方便记 $t=\frac k n$，那么 $f_0$ 即为：

$$f_0=t(p_1+f_0+1)+(1-t)$$
类似上面的整理后可得：
$$f_0=\frac {tp_1+1}{1-t}$$

所以 $p_1$ 怎么求呢？类似的写出 $p_i$ 的转移。

$$p_i=\frac1 2(p_{i+1}+p_i+1)+\frac 1 2$$
那么
$$p_i=p_{i+1}+2$$

考虑边界，$p_m=1$，因为它只能向 0 号点走一步。

发现这些式子都过于简单了，因此考虑是否有更简单的公式。

它们都可以表示为：$g_0=x,g_i=g_{i-1}+2$。

这是一次函数，对于每一项即可表示为 $g_i=x+2i$。

根据我们的定义我们需要对其求和才能得到由 0 号点走到叶子的期望步数，这是容易的，因为。

$$\sum_{i=0}^{m-1}x+2i=mx+m(m-1)$$

对于由叶子回到 0 号点的期望步数就是 $\sum_{i=1}^m p_i$，化简得到 其等于 $m^2$。

最后只剩枚举 $k$ 的复杂度，于是就得到了 $O(n)$ 的算法（我写的是带 $\log$ 的，因为懒得线性求逆元）。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
#define N 200005
//#define pii pair<int,int>
//#define fi first
//#define se second
//#define rep(i,j,k) for(int i=j;i<=k;i++)
int fpow(int x,int y){
	int ret=1,op=x;
	op%=mod;
	while(y){
		if(y&1)ret=ret*op%mod;
		op=op*op%mod;
		y>>=1;
	}
	return ret;
}
int n,m;
int p[N];
int pn,p1;
int ans;
signed main(){
	cin>>n>>m;
	p[m]=1;
	for(int i=m-1;i;i--){
		p[i]=p[i+1]+2;
	}
	p1=p[1];
	for(int i=1;i<=m;i++)pn+=p[i],pn%=mod;
	ans=pn*(n-1);
	for(int i=1;i<=n;i++){
		int x=(i-1)*fpow(n,mod-2)%mod;
		int o=(x*p1%mod+1)%mod*fpow(1+mod-x,mod-2)%mod;
		int op=(o*m+((m*(m-1))%mod)%mod)%mod;
		ans+=op;
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：win114514 (赞：4)

一个很套路的做法。

### 思路

题目要求走完整个树的时间，这并不好算，容易想到 min-max 容斥。

依据 min-max 容斥，我们可以轻松把它转化成第一次走到所有子集的时间。

考虑在这道题中，有什么特殊的。

第一，任何包含根节点的子集答案都是零。

第二，由于我们只关心第一次走到的点的时间，因此假如一个点的祖先被选中，那么这个点是否选中是无关紧要的。

这些无关紧要的点地位相同，所以我们可以一起考虑。

假设有 $n$ 个点是无关紧要的。

它们对答案的贡献是什么呢？

是：

$$
(-1)^k\sum_{i=0}^n (-1)^i\binom{n}{i}
$$

这是非常令人熟悉的二项式定理。

因此：

$$
(-1)^k\sum_{i=0}^n (-1)^i\binom{n}{i}
=(-1)^k[n=0]
$$

我们发现，只有当 $n=0$ 的时候才对答案有贡献。

在 $n=0$ 的时候，每一条链只有最底部的点可能被选。

现在计算这样的时间即可。

首先，对于底部被选的链而言。

我们设 $f_i$ 表示到达深度为 $i$ 的点还要走的期望步数，根节点的深度为 $0$。

那么有：

$$
\begin{align}
f_m&=0\nonumber\\
f_{m-1}&=\frac{(f_m+f_{m-2})}{2}+1\nonumber\\
&=\frac{f_{m-2}}{2}+1\nonumber\\
f_{m-2}&=\frac{f_{m-3}+f_{m-1}}{2}+1\nonumber\\
&=\frac{f_{m-3}+\frac{f_{m-2}}{2}+1}{2}+1\nonumber\\
&=\frac{2f_{m-3}}{3}+2\nonumber\\
f_{m-i}&=\frac{if_{m-i-1}}{i+1}+i\nonumber\\
\end{align}
$$

对于底部没有被选的链而言。

有：

$$
\begin{align}
f_n&=f_{m-1}+1\nonumber\\
f_{m-1}&=\frac{(f_n+f_{m-2})}{2}+1\nonumber\\
&=f_{m-2}+3\nonumber\\
f_{m-i}&=f_{m-i}+2\times i +1\nonumber\\
\end{align}
$$

所有期望都可以推到根上。

因此，假设有 $i$ 条链被选，则有 $(n-i)$ 条链没有被选：

$$
f_{0}=\frac{i(\frac{(m-1)f_0}{m}+m-1)+(n-i)(f_0+2\times m-1)}{n}+1
$$

可以继续化简。

$$
\begin{align}
f_{0}&=\frac{i(\frac{(m-1)f_0}{m}+m-1)+(n-i)(f_0+2\times m-1)}{n}+1\nonumber\\
\frac{i}{n}f_{0}&=\frac{i(\frac{(m-1)f_0}{m}+m-1)+(n-i)(2\times m-1)}{n}+1\nonumber\\
(\frac{i}{n}-\frac{i(m-1)}{nm})f_{0}&=\frac{i(m-1)+(n-i)(2\times m-1)}{n}+1\nonumber\\
(i-\frac{i(m-1)}{m})f_{0}&=i(m-1)+(n-i)(2\times m-1)+n\nonumber\\
\frac{i}{m}f_{0}&=i(m-1)+(n-i)(2\times m-1)+n\nonumber\\
\end{align}
$$

算出 $f_0$ 后，不要忘记乘负一和组合数的系数。

时间复杂度：$O(n\log mod)$。

瓶颈在求逆元，可以线性预处理，但没有必要。

### Code

```cpp
/*
  ! 前途似海，来日方长。
  ! Created: 2024/10/13 21:48:58
*/
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define int long long
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for (int i = (x); i <= (y); i++)
#define pre(i, x, y) for (int i = (x); i >= (y); i--)
inline void JYFILE19();

using i64 = long long;
using pii = pair<int, int>;

bool ST;
const int N = 1e6 + 10;
const int mod = 998244353;

int n, m;

namespace Math {
int Fc[1000010], Iv[1000010];
template<typename T> inline void add(T&x, int y) { if ((x += y) >= mod) x -= mod; }
template<typename T> inline void del(T&x, int y) { if ((x -= y) < 0) x += mod; }
template<typename T> inline void add(T&x, int y, int z) { x = (x + (long long) y * z) % mod; }
template<typename T> inline void mo(T&x) { x = (x % mod + mod) % mod; }
inline long long power(long long x, long long y) {
  long long res = 1;
  while (y) { if (y & 1) res = res * x % mod; x = x * x % mod, y /= 2; }
  return res;
}
inline void init(int n) {
  Fc[0] = 1;
  for (int i = 1; i <= n; i++) Fc[i] = (long long) Fc[i - 1] * i % mod; Iv[n] = power(Fc[n], mod - 2);
  for (int i = n; i >= 1; i--) Iv[i - 1] = (long long) Iv[i] * i % mod;
}
inline long long C(int x, int y) { return (x < 0 || y < 0 || x < y ? 0 : (long long) Fc[x] * Iv[y] % mod * Iv[x - y] % mod); }
} using namespace Math;

signed main() {
  JYFILE19();
  cin >> n >> m, init(n);
  int ns = 0;
  fro(i, 1, n) {
    int x = C(n, i);
    int up = (i * (m - 1) + (n - i) * (2 * m - 1)) % mod;
    int dw = (i * power(m, mod - 2)) % mod;
    int sm = ((up + n) * power(dw, mod - 2)) % mod;
    ns = (ns + (i & 1 ? 1 : -1) * x * sm) % mod;
  }
  cout << (ns % mod + mod) % mod << "\n";
  return 0;
}

bool ED;
inline void JYFILE19() {
  // freopen(".in", "r", stdin);
  // freopen(".out", "w", stdout);
  srand(random_device{}());
  ios::sync_with_stdio(0), cin.tie(0);
  double MIB = fabs((&ED - &ST) / 1048576.), LIM = 32;
  cerr << "MEMORY: " << MIB << endl, assert(MIB <= LIM);
}
```

---

## 作者：qcode_aya (赞：4)

其实这棵树的形态就是一个点连了 $n$ 条长为 $m$ 的链。

考虑 $m=1$ 时，这个东西是一个菊花图，看一下此时期望做多少次染完：

定义 $f_i$ 为染了根底下 $i$ 个节点的期望次数，则每次尝试有 $n - i + 1 \over n$ 的概率染到未染到的节点，所以期望染色次数为 $n \over n - i + 1$ 。

（如果你和我一样突然大脑宕机忘记怎么概率转期望了：
设 $E$ 表示期望尝试次数，$p$ 表示每次尝试的成功概率，则有 $E = 1 + (1 - p)E$ 。这个式子的含义是每次尝试花费 $1$ 的代价，且有 $1 - p$ 的概率重新尝试。挪项得 $E = {1 \over p}$ 。）

故而， $f_i = f_{i - 1} + {n \over n - i + 1}$ 。

所以期望染色次数为 $\sum_{i=1}^n{n \over n - i + 1} = \sum_{i=1}^n{n \over i}$ ，每次需要走下去再走上来，且最后一次不需要走上来，所以最终为 $2 \times ({\sum_{i=1}^n{n \over i}}) - 1$ 。

然后呢考虑链长 $m > 1$ 的情况，发现对于每条链，只有走到链底才算走完这条链，而此时这条链上其余点都已经被走过了，所以仅对 $n$ 个链底考虑。

同时若我们仿照上面菊花图的思路，则不需要考虑到达的是哪一个链底，一切都仅以 $\text{dep}$ 考虑，这棵树的形态变为了一条长为 $m + 1$ 的链，节点 $0$ 与 节点 $m$ 都只能有回头这一种选择，需要计算在节点 $0$ 与 节点 $m$ 间穿梭的期望代价，这是经典问题。（顺带一提，若不强行走到节点 $0$ 就计算走到节点 $m$ 的代价，是错误的。）

若我们需要从节点 $0$ 走到节点 $m$ ，设 $g_i$ 表示从 $i$ 走到 $m$ 的期望次数，则

$$
g_m = 0 \\
g_i = 1 + {g_{i - 1} + g_{i + 1} \over 2}, i\in[1, m - 1] \\
g_0 = 1 + g_1
$$

通过手算前几项并进行不优美的猜测，~~或者求助于同学~~，可以得到 $g_0 = m^2$ 。

若希望这步做得好看些，可以看 AT 日文题解区的两篇补足说明。

所以最终答案即为 $m^2 \times (2{\sum_{i=1}^n{n \over i}} - 1)$ 。

实现上如果不是很怠惰可以线性求逆元，复杂度 $O(n)$，~~但是它只给 2e5 欸！~~

---

## 作者：Eraine (赞：3)

编号：AT_arc185_d  
tag：概率 DP  
难度：$\color{orange}{2649}$  

作为本场唐氏 ARC 的最难题个人感觉反倒是最简单的，套路挺经典的。

发现对于一条链，只有到达该链深度为 $m$ 的点时才算整条链被覆盖，不到达深度为 $m$ 的链时是无用的，不妨设 $f_i$ 为完整覆盖完 $i$ 条链之后返回到 $0$ 的期望步数。那么答案就是 $f_n-P$，其中 $P$ 为从深度为 $m$ 第一次走到深度为 $0$ 的步数期望。

发现从深度为 $0$ 到任意一个深度为 $m$ 的点也和 $P$ 等价。那么我们可不可以求出 $P$ 呢？

设 $g_i$ 为从深度为 $0$ 的点第一次碰到深度为 $i$ 的点，$h_i$ 为深度为 $i$ 的点向深度更小的点徘徊的期望，则 $g_0=h_0=0$。

$g_i=g_{i-1}+h_{i-1}+1$，$h_i=h_{i-1}+2$。

显然 $g_i$ 的递推是由第一次到达 $i-1$，在 $[0,i-1]$ 徘徊和从 $i-1$ 直接走到 $i$ 三部分构成，对应 $g_{i-1},h_{i-1},1$。

考虑 $h_i$ 的递推式，设 $P^\prime$ 为从 $i$ 到 $i-1$ 的期望次数，则 $h_i=P^\prime(h_{i-1}+2)$。那么关键是要如何求出 $P^\prime$。由于从 $i$ 到 $i+1$ 和 $i-1$ 概率相等，所以 $P^\prime=\frac{P^\prime}{2}$，容易解得有意义解为 $P^\prime=1$。所以 $h_i=P^\prime(h_{i-1}+2)$。

所以 $P=g_n$。

那么现在问题变成如何利用以求出的 $P$ 递推求出 $f_n$，我们知道 $n$ 个数还有 $i$ 个数未选那么首次选出未选数的期望步数为 $\frac{n}{i}$。那么加上权值即可出递推式 $f_i=f_{i-1}+2P\frac{n}{n-i+1}$。所以答案即为 $f_{n}-P$。

预处理 $\text{inv}(i)$ 可以做到线性。

$\Theta(n)$。

[submission](https://atcoder.jp/contests/arc185/submissions/58780736)

若有疑问或错误请指出，虚心接受您的意见。

---

## 作者：Galois_Field_1048576 (赞：3)

**前言.** 在该 ARC 中，我已经推得正确的公式，但是并没有认为它是正确的。

## $n = 1$ 情形
此时图为链。

设 $f_m(i)$ 为在链长为 $m$ 时，你的点为第 $k$ 个时，期望**还**需要走多少步。我们有：
$$
f_m(m) = 0, f_m(k) = 1 + \dfrac{f_m(k-1) + f_m(k+1)}{2}, f_m(0) = 1 + f_m(1),
$$
我们发现只有第二个式子看起来不太和谐：
$$
\begin{aligned}
f_m(k) = 1 + \dfrac{f_m(k-1) + f_m(k+1)}{2} \\
2f_m(k) = 2 + f_m(k-1) + f_m(k+1) \\
f_m(k) - f_m(k-1) = 2 + f_m(k+1) - f_m(k) \\
g(k-1) = 2 + g(k) &\quad (g(k) = f_m(k+1) - f_m(k)).
\end{aligned}
$$
注意到 $f_m(0) = 1 + f_m(1) \implies g(0) = -1$，而 $g(k) = -(2k+1)$。发现
$$
-f(0) = f(m)-f(0) = \sum_{i=0}^{m-1} g(i) = -m^2,
$$
这样我们就发现 $\mathrm{ans} = f(0) = m^2$，解决！

## $m = 1$ 情形
此时图为菊花。问题变为：有 $n$ 个等概率出现的卡片，求期望需要抽多少次才能收集完整个卡组。（当然，对于本题，答案要乘 $2$ 再减 $1$）

考虑已经抽完 $k$ 个卡之后，你每次得到一个新卡的概率为 $\dfrac{n-k}n$，所以你期望需要 $\dfrac n{n-k}$ 抽得到一个新卡，这样，答案为
$$
\sum_{k=0}^{n-1} \dfrac n{n-k} = n H_n,
$$
其中 $H_n$ 为
$$
\sum_{k=1}^n \dfrac 1k.
$$
所以 $\mathrm{ans} = 2n H_n - 1$，解决！

## 一般的情形
注意到只要我们不到达这个树的叶子节点，我们就相当于浪费这些步，所以我们其实可以直接把它们乘起来：
$$
\mathrm{ans} = (2nH_n - 1) m^2,
$$
解决！

---

## 作者：Nangu (赞：2)

首先，题目中给的树是一个由 $n$ 条长度为 $m$ 的链再加上一个端点所组成的树，题目中要求经过所有点，等价于经过所有深度为 $m$ 的点。

以下记节点的编号为节点的深度。

记 $f_i$ 表示由 $i$ 转移到为 $i-1$ 的期望。

有 $f_m=1$。

对于 $i<m$，有 
$$f_i=\frac{1}{2}(f_{i+1}+f_i)+1$$

$$f_i=f_{i+1}+2$$

$$f_i=2\times m - 2\times i+1$$

设 $g_i$ 表示由 $i$ 转移到 $i+1$ 的期望。特别地 $g_0$ 表示走到一个没有走过的链的期望。

对于 $i>0$，有 $g_i=g_{i-1}+2$。

对于 $i=0$，我们记此时已经走过了 $k$ 个点，则有 

$$g_0=\frac k n(f_1+g_0)+1$$

$$g_0=\frac {k\times f_1}{n-k}+\frac n {n-k}$$

由此，从走过 $k$ 条链，到做过 $k+1$ 条链，其期望为
$$\sum_{i=0}^{n-1} g_i=m\times g_0+m\times (m-1)$$

特别地，若 $k>0$，还需加上 $\sum f_i=m^2$ 的贡献，表示从 $m$ 走到 $0$ 的期望。

最终的式子

$$ans=(n-1)\times m^2+n\times m\times(m-1)+\sum_{k=0}^{n-1} m\times(\frac {k\times f_1}{n-k}+\frac n {n-k})$$

到这一步已经完全可以开始写代码啦。

超短十行代码：

```cpp
#include<iostream>
const int mod=998244353;
long long n, m, inv[200007], ans;
signed main(){
    std::cin>>n>>m, inv[1]=1;
    for(int i=2; i<=n; ++i) inv[i]=mod-1ll*mod/i*inv[mod%i]%mod;
    ans=1ll*m*(n-1)%mod+1ll*(m-1)*n%mod;
    for(int i=0; i<n; ++i) ans+=1ll*(1ll*i*(m+m-1)+n)%mod*inv[n-i]%mod;
    std::cout<<ans%mod*m%mod;
}

---

## 作者：zhicheng (赞：1)

另一种理解方式。感觉其他题解对最后一步直接乘起来说的不太清楚。

原图相当于一个点挂了 $n$ 个长为 $m$ 的链。我们不对这些链做区分。考察走到**随便**某个链底的期望步数。因为第一步无论怎么走都可以，等同于数轴随机游走，通过经典结论或者代数推导一下（可以参考其他题解）可以得到是 $m^2$。并且如果之前访问了 $i$ 个链底，走到一个没有访问过的链底的概率是 $\dfrac{n-i+1}{n}$，期望加起来就是 $\sum\limits_{i=1}^{n} \dfrac{n}{n-i+1}$。每次的代价是 $2m^2$（因为要走回去，最后一次不用回去就是 $m^2$）。这样为什么是直接乘就比较清楚了。

时间复杂度线性。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int inv[200010];
int main(){
	int n,m,sum=1;
	scanf("%d%d",&n,&m);
	m=1ll*m*m%mod;
	inv[1]=1;
	for(int i=2;i<=n;i++){
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
		sum=(sum+inv[i])%mod;
	}
	printf("%lld",(1ll*sum*n%mod*2*m%mod-m+mod)%mod);
}
```

---

## 作者：louisliang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc185_d)

题目大意：根上挂了 $n$ 条长为 $m$ 的链，从根开始，每次随机选择和当前点直接相连了点并走过去，求期望多少步后能走每个点至少一次。

设 $f_i$ 表示当前走到第i层，期望还需要多少步能走完一条链（到达链底）。

可以列出方程：$f_i=\left\{ \begin{array}{rcl}
f_1+1 &  i=0 \\  \frac{f_{i-1}+f_{i+1}}{2}+1 & 1 \leq i <m \\
0 & i=m
\end{array}\right.$

不难推出 $f_{m-i}=\frac{i}{i+1} f_{m-i-1}+i$，所以 $f_1=\frac{m-1}{m} f_0+m-1$，又有 $f_0=f_1+1$，所以 $f_0=m^2$。

同理从链底走到根节点期望也是 $m^2$ 步。

走完 $n-i$ 条链后，由于走的方式是随机的，所以可以理解为在 $n$ 条链中随机找一条来走，走对的概率是 $\frac{i}{n}$ 的，所以期望要走 $\frac{n}{i}$ 次。

注意到最后一次走完不用回到根节点，所以答案为 $(2\sum\limits_{i=1}^n \frac{n}{i}-1)m^2$。

Code：

```cpp
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cassert>
#include<vector>
#include<cmath>
#include<cstring>
#include<set>
#include<climits>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
const int N = 2e5 + 10, MOD = 998244353;
long long ny[N];
int n, m;
int main(){
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	ny[0] = ny[1] = 1;
	for(int i = 2; i <= n; i++)
		ny[i] = (MOD - MOD / i) * ny[MOD % i] % MOD;
	long long sum = 0, t = 1ll * m * m % MOD;
	for(int i = n; i; i--){
		sum = (sum + n * t % MOD * 2 % MOD * ny[i] % MOD) % MOD;
	}
	sum = (sum - t + MOD) % MOD;
	cout << sum << "\n";
}
```

---

## 作者：DerrickLo (赞：0)

提供一个比较容易理解的做法。

先考虑一条链怎么做，考虑记 $f_i$ 表示从 $i-1$ 走到 $i$ 期望需要多少步，显然 $f_i=\dfrac{1}{2}+\dfrac{1}{2}(f_i+f_{i-1}+1)$，移项得 $f_i=f_{i-1}+2$，再记 $s_i=\displaystyle\sum_{j=1}^i f_i$。

事实上，对于一种情况，我们可以将原树抽象成两条链，一条是已经走过了的，一条是还没走的，设走过了 $i$ 条链，那么从根节点就有 $\dfrac{i}{n}$ 的概率走到已经走过的链，有 $\dfrac{n-i}{n}$ 的概率走到没走过的链。
 
考虑第一步是随机选一条链走过去，显然这期望要 $s_m$ 步，然后就是从一个链头走到另一个链头，不难发现这也是一条链，跟上面的情况也是类似的，只有 $0$ 点走到下一个点的期望有些改变，直接计算即可。

时间复杂度 $\mathcal O(n\log \bmod)$，可以通过预处理逆元做到 $\mathcal O(n)$。

```cpp
#include<bits/stdc++.h>
#define mod 998244353
#define int long long
using namespace std;
int n,m,ans;
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod,b>>=1;
	}
	return res;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0); 
	cin>>n>>m,ans=m*m%mod;
	for(int i=1;i<n;i++){
		ans+=m*m%mod;
		int now=((2*m-1)*i%mod*ksm(n-i,mod-2)+n*ksm(n-i,mod-2)%mod)%mod;
		ans+=m*(2*now+2*m-2)%mod*ksm(2,mod-2)%mod,ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：happybob (赞：0)

考虑只有一条链怎么做。这是很经典的，记 $f_i$ 表示点 $i-1$ 到 $i$ 的期望步数，不难发现 $f$ 是差为 $2$ 的等差数列，直接简单求和即可。

对于若干条链来说，先考虑两条链怎么做，考虑将过程分为到达某个链底端，然后走到另一个链底端。第二部分就等价于一条链从左走到右，第一部分等价于只有一条链，因为每次往上和往下都可以对应成一条链的情况。

对于更多的链，考虑仍然将过程分段，依次是到达每条链的底端。根据期望的线性性将每段答案求和即为最终期望。

第一次到达链底相当于就是只有一条链，而后面的每次等价于事实上只有两条链，但是到根后往已经走过的链和未走过的链的概率不同，这个东西和一条链上的部分一样，只需要把根往下的答案重算一下即可。复杂度 $O(n \log mod)$。

---

## 作者：ax_by_c (赞：0)

[可能更好的阅读体验](https://www.cnblogs.com/axbyc/articles/18718058)

~~这题我都会，但是国家队场上没过，可以装逼了！/kx/kx/kx~~

题意：给定 $n,m$，有一颗根节点下面挂着 $n$ 条有 $m$ 个点的链的树，一开始你在根节点且只有根节点被染色，每次操作你会等概率随机选择一条相邻的边移动，如果到达的点还未被染色则将其染色，问将所有点染色所需操作次数的期望，$1\le n,m\le 2\times 10^5$，对 $998244353$ 取模。

分析一下，其实要求的是到达过所有链底所需操作次数的期望。

考虑 $n=1$ 怎么做，考虑期望 DP，设 $f_i$ 为从深度（从零开始）为 $i$ 的点到链底所需操作次数的期望。

显然 $f_m=0,f_0=f_1+1,f_{1\le i<m}=\frac{f_{i-1}+f_{i+1}}{2}+1$。

令 $f_{0\le i<m}=k_if_{i+1}+b_i$，则只需求得所有的 $k_i,b_i$ 即可求得所有的 $f_i$。

$f_{i+1}=\frac{f_i+f_{i+2}}{2}+1=\frac{k_if_{i+1}+b_i+f_{i+2}}{2}+1$。

$(1-\frac{k_i}{2})f_{i+1}=\frac{b_i+f_{i+2}}{2}+1$。

$f_{i+1}=\frac{f_{i+2}}{2-k_i}+\frac{\frac{b_i}{2}+1}{1-\frac{k_i}{2}}$。

于是 $k_{i+1}=\frac{1}{2-k_i},b_{i+1}=\frac{b_i+2}{2-k_i}$。

显然 $k_0=b_0=1$，于是就可以求出所有的 $f_i$ 了，答案即为 $f_0$。

接下来考虑原问题怎么做，注意到在根节点经过期望 $f_0$ 次操作后会等概率随机到达一个链底，那么设 $g_i$ 为当前在根节点且已经到达过 $i$ 个链底时到达一个未到达过的链底所需操作次数的期望。

显然 $g_i=\frac{i}{n}(2f_0+g_i)+\frac{n-i}{n}f_0$。（$f_0$ 也可表示从链底到根所需操作次数的期望）

$(1-\frac{i}{n})g_i=\frac{n+i}{n}f_0$。

于是 $g_i=\frac{(n+i)f_0}{n-i}$。

最终答案即为 $\sum_{i=0}^{n-1}g_i+(n-1)f_0$。（前 $n-1$ 次到达链底后还要回到根节点）

[整理后的代码提交记录](https://atcoder.jp/contests/arc185/submissions/62838965)。

---

## 作者：冷却心 (赞：0)

这说明你我还不足以上 3 Dan。

容易发现这棵树就是结点 $0$ 向外挂了 $n$ 条长度为 $m$ 的链。这个对染色有很好的性质：如果你没有染到这条链的底部就回到 $0$ 了，说明你这次染色是无效的，还需要在染一次。

注意到这个染色有 $n$ 次从 $0$ 前往链底以及 $n-1$ 次链底返回 $0$。我们记 $0$ 的深度为 $0$，又记 $f_i$ 表示深度从 $i$ 走到 $i+1$ 的期望步数，$g_i$ 表示从深度 $i$ 走到 $i-1$ 的期望步数。

先考虑 $g$，显然 $g_m=1$，因为它一定只能向 $m-1$ 走一步。并且我们有：

$$g_i=\frac{1}{2}+\frac{1}{2}(g_{i+1}+g_i+1).$$

意思即当前在深度 $i$，有 $\frac{1}{2}$ 的概率走到 $i-1$，也有 $\frac{1}{2}$ 的概率花一步走到 $i+1$，然后花 $g_{i+1}$ 走回来，再花费 $g_i$ 走到 $i-1$，一共是 $(1+g_i+g_{i+1})$。

对这个转移方程移项可得到 $g_i=g_{i+1}+2$，联立上 $g_m=1$ 可得 $g_i=2(m-i)+1$。那么从链底部走到 $0$ 的总期望步数就是 $\sum g_i=1+3+\cdots+(2m-1)=m^2$，总共要从底部走上来 $n-1$ 次，总贡献就是 $(n-1)m^2$。

再考虑 $f$。类比 $g$，我们也有：

$$f_i=\frac{1}{2}+\frac{1}{2}(f_{i-1}+f_i+1).$$

得到 $f_i=f_{i-1}+2$，则 $f_i=f_0+2i$，但是我们不能直接求出 $f_0$，因为 $f_0$ 有可能走到一条曾经染完色的链。

所以我们枚举当前染完了 $k$ 条链，则有：

$$f_0=\frac{k}{n}(1+g_1+f_0)+\frac{n-k}{n}.$$

意为结点 $0$ 有 $\frac{k}{n}$ 的概率走到一个原来到过的链，花费 $1$，然后花费 $g_1$ 的代价回到 $0$，再花费 $f_0$ 走到新的链，总共 $(1+g_1+f_0)$；或者有 $\frac{n-k}{n}$ 的概率走到一条新的链。记 $p=\frac{k}{n}$，移项化简以下得到：

$$f_0=\frac{pg_1+1}{1-p}.$$

则从 $0$ 下到链底的总期望就是：

$$E_{\text{down}}=\sum_{i=0}^{m-1}f_i=\sum_{i=0}^{m-1}f_0+2i=mf_0+m(m-1).$$

于是就做完了，得到答案是这样一个丑陋的式子：

$$
\text{Answer}=(n-1)m^2+nm(m-1)+\sum_{k=0}^{n-1}\left(m\frac{\frac{k}{n}(2m-1)+1}{1-\frac{k}{n}}\right).
$$

整理一下有：

$$
\text{Answer}=(n-1)m^2+nm(m-1)+\sum_{k=0}^{n-1}m\frac{k(2m-1)+n}{n-k}.
$$

代码很好写，时间复杂度 $O(n)$，如果不线性求逆元那么还要一只 $\log$。

[https://atcoder.jp/contests/arc185/submissions/62730196](https://atcoder.jp/contests/arc185/submissions/62730196)。

---

## 作者：KingPowers (赞：0)

从简单情况开始思考会更好做一些。

考虑 $m=1$ 时，整张图会变成一个菊花。假设当前有 $i$ 个叶子已经被访问过了，那么此时我们有 $\frac{n-i}{n}$ 的概率走到一个没访问过的叶子，根据经典结论此时访问到一个没访问过的叶子期望需要尝试概率的倒数 $\frac{i}{n-i}$ 次（$E=1+(1-p)E$ 移项得到 $E=\frac{1}{p}$），每次都要在根和叶子之间走个来回，所以总的期望步数是 $(2\sum_{i=0}^{n-1}\frac{n}{n-i})-1$，减去 $1$ 是因为最后访问完所有点后不需要回去。

尝试扩展到一般情况，此时的图形如根节点 $0$ 挂出来 $n$ 条长度为 $m$ 的链。注意到如果一条链没有被完整访问完和没进去过是没有区别的，尝试枚举当前已经访问过了多少条链，设 $E_0$ 表示从根节点期望走几步能走到一条链的链底（由对称性可以知道从链底走回根的期望步数也是 $E_0$），类比一下菊花的情况可以得到答案为 $(2\sum_{i=0}^{n-1}\frac{n}{n-i}E_0)-E_0$，所以现在只需要尝试求出 $E_0$。

设 $E_i$ 表示当前在一个深度为 $i$ 的点（定义根节点的深度为 $0$）期望走几步走到某个链底，转移是容易的：

- 边界：$E_0=E_1+1$，$E_m=0$。

- 当 $0<i<n$ 时，有 $E_i=\frac{E_{i-1}+E_{i+1}}{2}+1$。

看上去转移关系带环，但是因为是在链上做可以使用一个经典的消元手法，把每个 $E_i$ 写成 $k_iE_{i-1}+b_i$ 的形式并特殊处理 $E_0$，然后再通过反代 $E_m=0$ 解出来 $E_0$。

得到 $E_0$ 后直接代入上式计算即可得到答案，容易做到 $O(n)$ 或 $O(n\log p)$，取决于是否预处理逆元。

---

## 作者：不知名用户 (赞：0)

### 题意

一个 $n\times m$ 的方格图，每个点向右边的点连边，第一列（最左边）的点向 $0$ 号点连边（容易发现形成一棵树），从 $0$ 号点出发每次等概率选择一个相邻（有边项链）的点移动，问第一次访问所有点的期望时间。

### 解法

（是我的思考过程，可能有点看不懂，懒得看的可以直接跳到下面，不影响接替）把两个到 $0$ 点之间的移动称为一次“行动”，容易发现一次没有到达第 $m$ 列的行动都是没用的，所以我们只用关注一次有效行动的期望时间和需要（期望）几次有效行动，下面两个性质分别就是在求这两个。

#### 特殊情况 1：菊花（m=1）

其实是个集齐所有颜色卡问题，挺典的，有很多原题比如 [P1291](https://www.luogu.com.cn/problem/P1291)。题意是 $n$ 种颜色的卡，每次等概率选择一种颜色的卡，问集齐所有颜色卡的期望时间。

分析：考虑从拥有 $i$ 种卡到 $i+1$ 种卡的期望时间。每次有 $\frac{n-i}{n}$ 的概率抽到，而根据 $pE=1$，故期望 $\frac{n}{n-i}$，总期望 $n(\frac11+\frac12+\cdots+\frac1n)$。

回到本问题，一次抽卡的花费为 $2$，但是最后一次不用回来，故答案为 $2n(\frac11+\frac12+\cdots+\frac1n)-1$。

#### 特殊情况 2：一条链（n=1）

DP。$f_i$ 表示 $i$ 移动到 $m$ 的期望步数。$f_m=0,f_0=f_1+1,f_i=\frac12(f_{i-1}+f_{i+1})+1$。直接高斯消元 $O(n^3)$，但是可以从后往前做，虽然不能求出来但是可以得到 $f_i=k_if_{i-1}+b_i$，可以从后往前做，具体方法为 $f_i=\frac12(k_{i+1}f_i+b_{i+1})+\frac12f_{i-1}+1$，可以做一些简单的消元，$f_0$ 略不同，不作赘述。$f_{-1}$ 不存在故可以直接得出 $f_0=b_0$。

#### 回到正解

答案就是两个乘一下：$f_0(2n(\frac11+\frac12+\cdots+\frac1n)-1)$。很容易理解，就是每次从 $0$ 移动的代价从 $1$ 改成了 $f_0$。

### 代码

时间复杂度 $O(n\log n)$，懒得预处理逆元了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10, mod = 998244353;
int inv[N], f[N], k[N], b[N];

int power(int a, int b)
{
	a %= mod;
	int c = 1;
	while(b)
	{
		if(b&1) c = c * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return c;
}

signed main()
{
	int n, m, i;
	scanf("%lld%lld", &n, &m);
	inv[1] = 1;for(i=2;i<=N-10;i++) inv[i] = (mod - mod / i) * inv[mod%i] % mod;
	for(i=m-1;i>=1;i--)
	{
		int c = power(1-k[i+1]*(mod+1)/2%mod,mod-2);
		k[i] = (mod + 1) / 2 * c % mod, b[i] = (b[i+1] * (mod + 1) / 2 % mod + 1) * c % mod;
	}
	f[0] = power(1-k[1],mod-2) * (b[1] + 1) % mod;
	int k = 0;
	for(i=1;i<=n;i++) k = (k + inv[i]) % mod;
	k = (k * n * 2 - 1) % mod;
	int ans = k * f[0] % mod;
	ans = (ans + mod) % mod;
	printf("%lld", ans);
	return 0;
}
```

后话：场上看这题通过人数很少就一直在搞 C/E，错过了这题。也许可以推出 $f_0$ 的封闭形式但是并不重要。（也许某些题解直接大力推 $f_0$，不过 $n,m$ 也不是很大足够放带 $\log$ 过）感觉如果见过抽卡和不直接高斯消元解方程其实想想也不难啊（？）。

---

## 作者：Felix72 (赞：0)

这个问题等价于求 $M$ 个叶子都被染色时的期望步数。

首先对只有一条链考虑：$(0 < i < m)$

$$
f_i = 1 + \frac{1}{2}(f_{i - 1} + f_{i + 1})
$$
$$
f_0 = 1 + f_1, f_m = 0
$$

$f$ 表示走到当前深度，期望还要走几步。

对于 $f_i$，它只与 $f_{i - 1}$ 和 $f_{i + 1}$ 相关，可以直接树上消元，但是不必那么麻烦，因为该式子可化为 $(f_i - f_{i - 1}) = 2 + (f_{i + 1} - f_i)$。这告诉我们 $f$ 的差分是等差数列，公差是 $-2$，那么自然有 $f_0 = m^2$。

这个式子可以扩展到多条链的情况，但是要注意走到哪一条链都有同等可能性。具体的，若当前已经覆盖完 $i$ 条链，此时有 $\frac{i}{n}$ 的概率期望走 $2m^2$ 步并不做任何事回到原点，有 $\frac{n - i}{n}$ 的概率期望走 $2m^2$ 步（如果 $i = n - 1$ 则只需要走 $m^2$ 步），途中完全覆盖一条新链再回到原点。

列出式子递推转移即可。

```cpp
/*Good Game, Well Play.*/
#include <bits/stdc++.h>
using namespace std;

const int N = 200010, mod = 998244353;
int n, m; long long fac[N], inv[N];
inline long long qpow(long long a, long long b)
{
	long long ans = 1;
	while(b)
	{
		if(b & 1) ans = ans * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return ans;
}
inline long long Inv(long long num)
{
	num = (num % mod + mod) % mod;
	return qpow(num, mod - 2);
}
inline void init()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= 200000; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[200000] = qpow(fac[200000], mod - 2);
	for(int i = 199999; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}

struct Rel
{
	long long k, b;
	Rel operator + (const Rel &w) const {return {(k + w.k) % mod, (b + w.b) % mod};}
	Rel operator - (const Rel &w) const {return {(k - w.k + mod) % mod, (b - w.b + mod) % mod};}
	Rel operator * (const long long &w) const {return {w * k % mod, w * b % mod};}
}; Rel f[N]; long long g[N], ans;

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m; init();
	f[m] = {0, 0};
	for(int i = m - 1; i >= 1; --i)
		f[i] = (Rel){Inv(2), 1 + Inv(2) * f[i + 1].b % mod} * Inv(1 - Inv(2) * f[i + 1].k % mod);
	f[0] = (Rel){0, 1 + f[1].b} * Inv(1 - f[1].k);
	g[n - 1] = n % mod * ((n - 1) * Inv(n) % mod * 2 * f[0].b % mod + 1 * Inv(n) % mod * f[0].b % mod) % mod;
	for(int i = n - 2; i >= 0; --i) g[i] = n * Inv(n - i) % mod * (2 * f[0].b + (n - i) * Inv(n) % mod * g[i + 1] % mod) % mod;
	cout << g[0] << '\n';
	return 0;
}
/*

*/
```

---

