# [ABC236Ex] Distinct Multiples

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc236/tasks/abc236_h

正整数 $ N,\ M $ および正整数列 $ D\ =\ (D_1,\ \dots,\ D_N) $ が与えられます。

以下の条件を満たす正整数列 $ A\ =\ (A_1,\ \dots,\ A_N) $ の総数を $ 998244353 $ で割った余りを求めてください。

- $ 1\ \leq\ A_i\ \leq\ M\ \,\ (1\ \leq\ i\ \leq\ N) $
- $ A_i\ \neq\ A_j\ \,\ (1\ \leq\ i\ \lt\ j\ \leq\ N) $
- 各 $ i\ \,\ (1\ \leq\ i\ \leq\ N) $ について、$ A_i $ は $ D_i $ の倍数

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 16 $
- $ 1\ \leq\ M\ \leq\ 10^{18} $
- $ 1\ \leq\ D_i\ \leq\ M\ \,\ (1\ \leq\ i\ \leq\ N) $
- 入力は全て整数である。

### Sample Explanation 1

条件を満たす $ A $ は $ (2,\ 3,\ 4),\ (2,\ 6,\ 4),\ (6,\ 3,\ 4) $ の $ 3 $ 通りです。

### Sample Explanation 2

条件を満たす $ A $ は存在しません。

### Sample Explanation 3

$ 998244353 $ で割った余りを求めることに注意してください。

## 样例 #1

### 输入

```
3 7
2 3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
1 2 2```

### 输出

```
0```

## 样例 #3

### 输入

```
6 1000000000000000000
380214083 420492929 929717250 666796775 209977152 770361643```

### 输出

```
325683519```

# 题解

## 作者：ningago (赞：17)

考虑题目所求的条件为：$a_i\ne a_j(i\ne j)$ 全部满足，转化一下可得 $a_i=a_j (i\ne j)$ 满足 $0$ 个。

此时有暴力的容斥做法：令 $S$ 表示这 $\dfrac{n(n-1)}{2}$ 条边有些选有些不选共 $2^{n(n-1)/2}$ 种状态，对于一个 $S$ 类似并查集地考虑其构成了若干连通块 $s_1,s_2,\cdots, s_k$，则有：

$$Ans=\sum_{S}(-1)^{|S|}\prod_{i=1}^k\left\lfloor\dfrac{m}{lcm(s_i)}\right\rfloor$$

令 $E(s)$ 表示两个端点均在**点集** $s$ 中的**边**的集合，此时考虑枚举 $s_{1\sim k}$ 的构成，则有：

$$Ans=\sum_{s_1,s_2,\cdots, s_k}\prod_{i=1}^k\left\lfloor\dfrac{m}{lcm(s_i)}\right\rfloor\cdot (\sum_{S\subseteq E(s_i)}[\text{S 中的边使得这} |s_i| \text{个点连通}](-1)^{|S|})$$

这里的 $S$ 本质上是把式一中的 $S$ 分解了。

令 $f(n)$ 表示 $n$ 个点的无向连通图的**容斥系数**（$(-1)^{|S|}$）的总和，其可以用一个小容斥得出。具体令 $g(n)$ 表示 $n$ 个点的无向图的容斥系数总和，考虑钦定集合大小，则有：

$$g(n)=\sum_{i=0}^{n(n-1)/2}\dbinom{n(n-1)/2}{i}(-1)^i=(-1+1)^{n(n-1)/2}=[n=1]$$

对于 $f$，钦定 $1$ 所在的连通块大小，则有：

$$f(n)=g(n)-\sum_{i=1}^{n-1}\dbinom{n-1}{i-1}f(i)g(n-i)=[n=1]-(i-1)\cdot f(i-1)$$

故容易 $O(n)$ 算出，此时答案为：

$$Ans=\sum_{s_1,s_2,\cdots, s_k}\prod_{i=1}^k\left\lfloor\dfrac{m}{lcm(s_i)}\right\rfloor\cdot f(|s_i|)$$

此时可以使用 DP，令 $dp_{S}$ 表示已经确定了 $S$ 集合内的点的连通块归属 的答案，转移时考虑确定**最小的**未确定的点 $mn_S$ 所在的连通块，即可枚举子集进行转移。

$$dp_S\cdot \left\lfloor\dfrac{m}{lcm(T)}\right\rfloor\cdot f(|T|)\to dp_{S\cup T}(S\cap T=\varnothing, mn_S\in T)$$

复杂度 $O(3^n+2^n\log m)$。

https://atcoder.jp/contests/abc236/submissions/46956980

---

## 作者：冰雾 (赞：11)

这是一个爆标做法。

直接计数很难考虑到 $A_i$ 互不相同的限制，考虑容斥。

这是一个经典的容斥模型，即集合划分容斥。

考虑将原序列划分成若干集合，每个集合内的数强制相等，然后一个集合内的容斥系数就是 $(-1)^{|S|-1}(|S|-1)!$，证明可以考虑枚举圆排列，然后用下斯特林数相关结论就得证了。

然后就是要计算对于可能的集合个数，其带上容斥系数的方案数之和。

不妨设一个集合的集合幂级数是 $F$，那么就是要求 $\exp F$。

$F$ 的计算显然可以枚举一个集合，然后求出 $\text{lcm}$。

可以用除法规避爆 long long 的问题。

复杂度是 $O(n^22^n+2^n\log V)$ 的。

---

## 作者：zhouyuhang (赞：5)

感觉总算略懂一点容斥了……

春赛前神仙曾经教过我怎么猜容斥系数，当时应该是胡了一个生成函数的证明。做了 GDKOI D1T3 以后来稍微写一写怎么顺理成章的推出来这个系数。

首先我们将所有的数互不相同这一条件看成 $m=\frac{n(n-1)}{2}$ 个无序点对 $(x_i,y_i)$，每一个点对代表一个限制，即 $A_{x_i}\neq A_{y_i}$。显然满足所有的限制的方案数即为答案。

容斥，令 $f(S)$ 为钦定集合 $S$ 内的限制全部**不满足**的方案数（这样一来集合就被分成了一些部分，部分与部分间无关，而每个部分内部需全部相等），则答案为 $\sum_{S}(-1)^{|S|}f(S)$。于是我们得到了一个 $O(2^m)$ 的暴力。

考虑优化这个容斥。注意到如果将 $(x_i,y_i)$ 看作一条边，$f(S)$ 其实只与 $S$ 将所有点划分成怎样的几个连通块有关。我们不妨来看一看对于某种集合划分，其对于容斥过程的贡献（就是在容斥中被算到的容斥系数之和）是多少。不难发现，对于点的全集 $U$ 的一种划分 $U=\{s_1,s_2,…,s_k\}$ 中的一个小集合 $s_i$ 而言，其贡献为：**对于每一个恰好包含 $s_i$ 内所有点的连通子图，设其包含 $e$ 条边，定义其权值为 $(-1)^e$**。$s_i$ 的贡献就是这些子图的权值之和（由传统容斥的式子可以直接得到），而划分的贡献则为 $s_1,s_2,…,s_k$ 的贡献之积（小集合间相互独立）。

我们发现，关键的问题还是在于一个集合 $s_i$ 的贡献是什么。一个很关键的事情，是题目中所给出的其实是一个完全图，因此点集 $s_i$ 的贡献只与 $|s_i|$ 有关（大小相同则同构）。于是我们可以考虑 dp 来计算系数。令 $coef_i$ 表示大小为 $i$ 的集合的贡献。连通子图这个限制很棘手，考虑正难则反，先算所有子图的权值之和。这是一个很经典的二项式定理的形式，其答案为 $[i=1]$。接着算不连通的情况，枚举最后一个点所在集合的大小，有答案为 $\sum_{j=1}^{i-1}\binom{i-1}{j-1}coef_j[i-j=1]=(i-1)coef_{i-1}$。用总情况数减去不合法数量，就有 $coef_i=[i=1]-(i-1)coef_{i-1},coef_1=1$。显然可以得到 $coef_{i}=(-1)^{i-1}(i-1)!$。这也就是一些题解中所提到的容斥系数。

回到题目，我们还需要对每一个集合划分算出对应的容斥系数与方案数并求和。对于这种划分的形式，很容易想到 dp，于是后面的部分都是一些平凡的技巧。无论是暴力 dp 还是使用集合幂级数技巧都可以通过。

可以看到，这篇题解花费了很长的时间作了很多有些笨重的推导，最后得到了一个简单甚至可以直接 看出来/猜出来 的结论。但是不要小瞧这样的推导，当题目不具有完全图这样的性质时，只需将我们的容斥系数 dp 从关于集合大小改成集合本身，依旧可以解决问题。具体可以参考 GDKOI2023 D1T3。

---

## 作者：云浅知处 (赞：4)

考虑建出 $n$ 点的图，若 $a_i=a_j$ 则连无向边 $(i,j)$。那么互不相同相当于图中一条边都不能连。设 $C(E)\subseteq 2^V$ 为连上边集 $E$ 后的连通块集合，$F(P)$ 表示连通块形态为 $P$ 时的答案（$P\subseteq 2^V$），则答案为

$$
\sum_{E}(-1)^{|E|}F(C(E))=\sum_{P}F(P)\sum_{C(E)=P}(-1)^{|E|}
$$

不难发现重点在计算后面那一项。显然各个连通块独立，只需要对每个连通块 $S\in P$，求出所有使 $S$ 以内点集联通的边集 $E$ 的 $(-1)^{|E|}$ 之和。设 $f_k$ 表示 $k$ 个点的方案数，发现没有联通限制的时候答案是 $[k=1]$，即 $(\exp f)_k=[k=1]$，取 $\ln$ 得到 $f_k=(-1)^{k-1}(k-1)!$，因此

$$
ANS=\sum_{P}F(P)\prod_{S\in P}(-1)^{|S|-1}(|S|-1)!$$

>具体来说，考虑怎么算 $f$：较好理解的方式是采用容斥，用随意连的贡献和减去不连通的贡献和。不连通时维护 $1$ 所在连通块，有
> $$f_i=-\sum_{j=1}^{i-1}\binom{i-1}{j-1}f_j[i-j=1]=-(i-1)f_{i-1}$$
>再结合 $f_1=1$，自然有 $f_k=(k-1)!(-1)^{k-1}$。当然，你可以发现上述过程就是做了一次 $\ln$。

本题中 $F(P)=\prod_{S\in P}\lfloor\frac{M}{\text{lcm}(S)}\rfloor$ 容易计算，其中 $\text{lcm}(S)$ 表示 $S$ 以内所有元素的 $\text{lcm}$。子集卷积优化 exp 即可做到 $O((n^2+\log M)2^n)$。

偷懒写的 $O(3^n+2^n\log M)$ 代码：[Link](https://atcoder.jp/contests/abc236/submissions/39927152)

---

## 作者：kyEEcccccc (赞：3)

这篇题解主要补充最高赞题解没有写的一些平凡内容。高水平选手建议跳过。

这里重点解释其中提到的“集合划分容斥”容斥系数，存在一个比较容易理解的推导。考虑一个子集 $T\subseteq U$ 的容斥系数是关于其大小的函数 $\lambda(|T|)$，记集合 $S$ 最终被算进答案里的总系数为 $f(S)$，则我们希望对于 $S$，如果 $|S| = 1$，则 $f(S) = \lambda(1) = 1$；而对于 $|S| > 1$，我们希望有对于所有划分方案 $S = T_1\cup T_2\dots\cup T_k$ 有 $f(S) = \sum_{\text{all devisions}}\prod_{i=1}^k \lambda(|T_i|) = 0$。然后考虑算容斥系数 $\lambda$，我们考虑一个巧妙的递推：记 $f(S) = F(|S|)$，则 $F(n) = (n-1)\lambda(n-1)F(1) + \lambda(n)$，这是因为对于 $x > 1$，有 $F(x) = 0$，从它们转移过来的方案不用考虑。根据上述转移容易得到 $\lambda(n) = -(n-1)\lambda(n - 1)$，所以 $\lambda(n) = (-1)^{n-1}(n-1)!$。

关于集合幂级数 Exp 的知识则可以前往 <https://loj.ac/p/154>。具体地，考虑子集（无交并）卷积的一般做法——给下标为集合 $S$ 的元素附带上集合大小指标 $x^{|S|}$，将其从一个数值扩充为一个多项式（这里是单项式 $a_Sx^{|S|}$），接下来用 FMT/IFMT 做 OR-卷积，但是将加减乘法运算替换成对应的多项式运算，最终得到每个位置上是一个多项式，其 $x^{|S|}$ 项系数即为答案。容易发现，这一过程可以重复多次，具体地，一个数列反复卷自己 $t$ 次，等价于 FMT 后多项式求 $t$ 次幂。因此可以推导出，如果要求原集合幂级数的 Exp，道理也是同样的：直接在 FMT 后，对多项式求 Exp 再进行 IFMT 即可。Exp 当然可以直接 $n^2$ 做。

---

## 作者：BINYU (赞：3)

设 $dp_S$（$S$ 是一个由点对构成的集合）表示 $S$ 中的点对的值必须相等，其他任意，则答案为  $\sum(-1)^{|S|}dp_S$。

$dp_S$ 的计算：

我们把相等关系看做边，则每个连通块内的所有数都必须相等，设最终形成了 $m$ 个连通块，每个连通块的点集为 $\{s_1,s_2,\dots,s_m\}$，则 $dp_S = \prod\limits_{i=1}^{m}\lfloor{\frac{m}{lcm(s_i)}}\rfloor$。

发现 $dp$ 的计算只跟连通性相关，不妨直接将状态改为 $dp_{\{s_1,s_2,\dots,s_m\}}$ 并**带上容斥系数**，则 $dp_{\{s_1,s_2,\dots,s_m\}}=\sum{(-1)^{|E|}}\prod\limits_{i=1}^{m}\lfloor{\frac{m}{lcm(s_i)}}\rfloor$，其中 $E$ 是一个边集，且构成的连通块必须为 $\{s_1,s_2,\dots,s_m\}$。

我们再将边集拆开，式子变为：$dp_{\{s_1,s_2,\dots,s_m\}}=\prod\limits_{i=1}^{m}\lfloor{\frac{m}{lcm(s_i)}}\rfloor\sum(-1)^{|E_i|}$

其中 $E_i$ 是保证 $s_i$ 连通的一个边集。

因为每个 $s_i$ 内的点之间两两均可连边，所以 $\sum(-1)^{|E_i|}$ 只跟 $|s_i|$ 有关。

设 $g_{i,0}$ 表示 $i$ 个点且有奇数条边的连通图。

设 $g_{i,1}$ 表示 $i$ 个点且有偶数条边的连通图。

易得：$\sum(-1)^{|E_i|}=g_{|s_i|,0}-g_{|s_i|,1}$

参考 $n$ 个点连通图计数方法，有：

$$g_{n,0}=2^{\frac{n(n-1)}{2}-1}-\sum\limits_{i=1}^{n-1}\dbinom{n-1}{i-1}(g_{i,0}+g_{i,1})2^{\frac{(n-i)(n-i-1)}{2}-1}-g_{n-1,0}(n-1)$$

$$g_{n,1}=2^{\frac{n(n-1)}{2}-1}-\sum\limits_{i=1}^{n-1}\dbinom{n-1}{i-1}(g_{i,0}+g_{i,1})2^{\frac{(n-i)(n-i-1)}{2}-1}-g_{n-1,1}(n-1)$$

边界为：$g_{1,0}=1,g_{1,1}=0$

则 $g_{n,0}-g_{n,1}=(n-1)(g_{n-1,1}-g_{n-1,0})=(-1)^{n-1}(n-1)!$。

化简 $dp$ 的求值：$dp_{\{s_1,s_2,\dots,s_m\}}=\prod\limits_{i=1}^{m}\lfloor{\frac{m}{lcm(s_i)}}\rfloor(|s_i|-1)!(-1)^{|s_i|-1}$。

我们再定义 $f_{S}$ 表示 $\sum dp_{\{s_1,s_2,\dots,s_m\}}$，$\{s_1,s_2,\dots,s_m\}$ 是 $S$ 的一组划分。

则：$f_S=\sum_{lowbit(S)\in S'\subseteq S}f_{S-S'}\lfloor{\frac{m}{lcm(S')}}\rfloor(|S'|-1)!(-1)^{|S'|-1}$

边界为 $f_{\varnothing}=1$。

答案就是 $f_{\{1,2,\dots,n\}}$。时间复杂度 $O(2^n\log V+3^n)$。

---

## 作者：Register_int (赞：3)

~~再次感谢 Daniel_lele 指导~~ 这里是一种大力容斥的解法。

考虑 dp。设 $dp_S$ 为集合 $S$ 中的答案，则有转移方程：

$$dp_{S\cup d_i}=\left\lfloor\dfrac m{d_i}\right\rfloor dp_S$$

然而这个式子是错的，因为会算进 $a_i$ 与 $S$ 中任意一个元素相同的情况，所以要减去。那么就变成了这样：

$$dp_{S\cup d_i}=\left\lfloor\dfrac m{d_i}\right\rfloor dp_S-\sum_{d_j\in S,i\not=j}\left\lfloor\dfrac m{\text{lcm}(d_i,d_j)}\right\rfloor dp_{S/d_i,d_j}$$

写出来这玩意就可以过样例 $1,3$ 了，但交上去后惨不忍睹。为啥呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/relqdm4z.png)

那么还要套一层容斥把这个加回来。刚开始我算的容斥系数是 $|T|$，因为每次容斥的最后一位都会被前面加上 $|T|$，所以要消掉。但交上去也获得了很优秀的成绩……

![](https://cdn.luogu.com.cn/upload/image_hosting/61tp2opv.png)

可以发现，当 $|S|-|T|>1$ 时，由于剩下几个元素都是合法解，也就是满足不相等关系，导致错解不会被计算。所以会对这种情况产生贡献的只有 $|S|-|T|\le1$ 的情况。设 $f(|S|)$ 为集合 $S$ 对应的容斥系数，则满足递推关系 $f(1)=-1,f(n)=-f(n-1)\times\binom n{n-1}=-nf(n-1)$，即 $f(n)=(-1)^nn!$。

那么系数有了就可以开始大力容斥了。不过凉心出题人卡了 $O(3^nn\log m)$ 算法，要再预处理一层 $\text{lcm}$，复杂度为 $O(3^n+2^n\log m)$，可以通过。

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;

inline 
ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

inline 
ll lcm(ll a, ll b) {
	return a / gcd(a, b) * b;
}

int n, x, c[1 << 16];

ll m, a[16], f[17], l[1 << 16], dp[1 << 16];

int main() {
	scanf("%d%lld", &n, &m), *dp = *l = *f = 1;
	for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % mod;
	for (int s = 1, k, i; s < 1 << n; s++) {
		i = __lg(s & -s), k = s & -s ^ s, c[s] = c[k] + 1;
		dp[s] = (dp[s] + dp[k] * (m / a[i] % mod) % mod) % mod;
		l[s] = !l[k] || a[i] / gcd(a[i], l[k]) > m / l[k] ? 0 : lcm(a[i], l[k]);
		for (int t = k; t; t = t - 1 & k) {
			if (!l[t | 1 << i]) continue;
			if (c[t] & 1) dp[s] = (dp[s] - dp[k ^ t] * (m / l[t | 1 << i] % mod) % mod * f[c[t]] % mod + mod) % mod;
			else dp[s] = (dp[s] + dp[k ^ t] * (m / l[t | 1 << i] % mod) % mod * f[c[t]] % mod) % mod;
		}
	}
	printf("%lld", dp[(1 << n) - 1]);
}
```

zxx 好闪，拜谢 zxx！

---

## 作者：gdf_yhm (赞：2)

[abc236h](https://www.luogu.com.cn/problem/AT_abc236_h)

[图计数相关](https://yhddd123.github.io/post/tu-ji-shu)。

### 思路

钦定若干组组内相等，每组的方案为 $\frac{m}{lcm (d_i)}$。状压，枚举包含 $mn_S$ 的子集 $t$ 乘方案数和大小为 $\lvert t\rvert$ 的组的容斥系数转移。

对于 $\binom{n}{2}$ 个不等关系钦定 $i$ 个相等的容斥系数为 $(-1)^i$。钦定组内相等的容斥系数为构成大小为 $siz$ 无向连通图的选边方案的容斥系数之和。

仿照 [无向连通图计数](https://www.luogu.com.cn/problem/P10982)。$n$ 个点乱连的系数为 $\sum_{i=0}^{\binom{n}{2}}\binom{\binom{n}{2}}{i} (-1)^i=[\binom{n}{2}=0]=[n=1]$。减去不连通图的贡献，$n$ 个点的组的容斥系数之和为 $f_n=[n=1]-\sum_{i=1}^{n-1}\binom{n-1}{i-1}f_i[n-i=1]$。

### code

```cpp
int n,m,a[maxn];
int f[17];
int dp[1<<maxn],val[1<<maxn];
void work(){
	n=read();m=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		f[i]=(i==1);
		for(int j=1;j<i;j++)f[i]-=C(i-1,j-1)*f[j]*(i-j==1)%mod;
		f[i]+=mod,f[i]%=mod;
	}
	for(int s=1;s<(1<<n);s++){
		int p=__lg(s&(-s)),gg=gcd(val[s^(1<<p)],a[p]);
		if(!val[s^(1<<p)])val[s]=a[p];
		else if(a[p]/gg>m/val[s^(1<<p)])val[s]=m+1;
		else val[s]=a[p]/gg*val[s^(1<<p)];
	}
	dp[0]=1;
	for(int s=1;s<(1<<n);s++){
		int p=__lg(s&(-s));
		for(int t=s;t;t=(t-1)&s)if(t&(1<<p)){
			(dp[s]+=(m/val[t])%mod*dp[s^t]%mod*f[__builtin_popcount(t)])%=mod;
		}
	}
	printf("%lld\n",dp[(1<<n)-1]);
}
```

---

## 作者：Purslane (赞：1)

# Solution

安徽省集考了一个类似的题。

如果不加上 $A$ 互不相同的限制，那么方案显然为 $\prod_{i=1}^n \lfloor \frac{M}{D_i} \rfloor$。

如果 $A_i=A_j$，就在 $i$ 和 $j$ 之间连边。我们希望边数 $=0$，所以考虑容斥，钦定若干条边。

直接钦定边是不好做的，但是考虑钦定的边的效果——一定是将 $n$ 个点合并成若干连通块。

考虑枚举效果，对每个连通块，计算他的容斥系数。一个大小为 $k$ 的连通块的容斥系数意思是：对于所有使得图连通的边集，计算 $(-1)^{|E|}$ 并求和。

设容斥系数为 $f_n$。

如果不要求连通，发现容斥系数的和为 $[n=1]$。

使用图计数的常见套路，有：

$$
f_n = [n=1]-\sum_{i=1}^{n-1} \binom{n-1}{i-1} f_i [i=n-1]
$$

容易得到 $f_n = (-1)^{n-1} (n-1)!$。

跑一个集合幂级数 exp 即可做到 $O(n^2 2^n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=(1<<16)+10,MOD=998244353;
int n,m,frac[MAXN],a[MAXN],f[17][MAXN],g[17][MAXN];
void fwt(int *f,int l,int r) {
	if(l==r) return ;
	int mid=(l+r)>>1;
	fwt(f,l,mid),fwt(f,mid+1,r);
	ffor(i,l,mid) {
		int j=i-l+mid+1;
		int x=f[i],y=f[j];
		f[i]=(x+y)%MOD,f[j]=(x-y)%MOD;
	}
	return ;
}
int inv[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
void exp(int *f,int *g) {
	g[0]=1;
	ffor(i,1,n) {
		ffor(j,1,i) g[i]=(g[i]+g[i-j]*f[j]%MOD*j)%MOD;
		g[i]=g[i]*inv[i]%MOD;	
	}
	return ;
}
int zzz[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m,frac[0]=1;
	ffor(i,1,n) frac[i]=frac[i-1]*(-i)%MOD;
	ffor(i,1,n) cin>>a[i];
	memset(zzz,-1,sizeof(zzz));
	zzz[0]=1;
	ffor(i,1,(1<<n)-1) {
		int lb=(i&-i),lid=log2(lb)+1;
		if(zzz[i-lb]!=-1) {
			__int128 val=((__int128)1)*zzz[i-lb]*a[lid]/__gcd(zzz[i-lb],a[lid]);
			if(val<=m) zzz[i]=val;
		}
	}
	memset(a,0,sizeof(a));
	ffor(i,1,(1<<n)-1) if(zzz[i]!=-1) a[i]=(m/zzz[i])%MOD*frac[__builtin_popcount(i)-1]%MOD;
	ffor(i,0,(1<<n)-1) f[__builtin_popcount(i)][i]=a[i];
	ffor(i,1,n) inv[i]=qpow(i,MOD-2);
	ffor(i,0,n) fwt(f[i],0,(1<<n)-1);
	ffor(i,0,(1<<n)-1) {
		int F[21],G[21];
		memset(F,0,sizeof(F)),memset(G,0,sizeof(G));
		ffor(j,0,n) F[j]=f[j][i];
		exp(F,G);
		ffor(j,0,n) g[j][i]=G[j]; 
	}
	ffor(i,0,n) fwt(g[i],0,(1<<n)-1);
	int div=qpow(1<<n,MOD-2);
	cout<<(g[n][(1<<n)-1]*div%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：analysis (赞：1)

序列条件如下：

- 值域在 $[1,M]$。

- 互不相等。

- $D_i|A_i$。

还是对条件 $2$ 进行容斥，钦定序列被划分为 $k$ 个内部相等的集合。目标是最后集合大小均为 $1$ 且集合元素互不相同。

发现容斥系数并不常规，我们得推理一下。考虑对于极大的相等集合 $S$，合法当且仅当 $|S| \leq 1$。在钦定的情况下可能会被割裂为若干集合。具体来说，假设容斥系数为 $P$，则 $\exp{P}=1+x \Rightarrow P=\ln{(1+x)}$。也就是 $p_i=(i-1)!(-1)^{i}$。

然后考虑钦定的相等集合 $S$，选择方案就是 $\lfloor\frac{M}{\operatorname{lcm}_{x \in S}(d_x)}\rfloor$。

先 $O(n2^n\log{n})$ 预处理下 $\operatorname{lcm}$，不是瓶颈。

剩下就是个子集 $\exp$ 了。

枚举子集 $O(3^n)$ 也可以，集合幂级数 $O(n^22^n)$ 也可以。

[code](https://atcoder.jp/contests/abc236/submissions/61525070)

---

## 作者：kzos (赞：1)

> [[ABC 236Ex] Distinct Multiples](https://atcoder.jp/contests/abc236/tasks/abc236_h) *600
>
> 给定两个正整数 $N,M$ 和一个正整数序列 $D$，询问满足条件的序列 $A$ 的个数：
>
> 1. $1\leq A_i\leq M(1\leq i\leq N)$
> 2. $A_i\neq A_j(1\leq i<j\leq N)$
> 3. $D_i|A_i$
>
> - $2\leq N\leq 16,1\leq M\leq 10^{18},1\leq D_i\leq M$

显然要容斥，补集的条件就是钦定某些数字都相等。这个东西不好做，不妨把这个东西放在图上考虑。

对于两个数 $i,j$，如果 $a_i=a_j$，那么在 $(i,j)$ 之间建边。那么每一个边集 $S\in E$，设 $f(S)$ 表示已经钦定了一定选择 $S$ 中的边，满足条件的图的总数，那么答案就是：
$$
\sum_{S\in E} (-1)^{|S|}f(S)
$$
注意 $S$ 可以为空。

但是边数是 $O(n^2)$ 的，还是得考虑放在点上。注意到一个连通块的很多种联通方式实际上最后的值是相同的。

设 $dp_{S}$ 表示点集为 $S$ 的包含的所有边 $E$ 的 $\sum_{E\in S} (-1)^{|E|}f(E)$，那么就是要求 $dp_{\{1,\cdots ,n\}}$。考虑通过找特殊点计数。不妨就枚举子集中 $u$ 所在的联通块，对于这个连通块，价值已经确定了，假设是 $g(T)$，那么还需要的就是容斥系数的和，假设是 $h(|T|)$，那么自然有转移：
$$
dp_S=\sum_{T\in S,u\in T} g(T)h(|T|)dp_{S-T}\\
dp_{0}=1\\
$$
 $g(T)$ 显然为 $\frac{M}{\operatorname{lcm_{u\in T}}d_u}$，$h(i)$ 仍然考虑特殊点计数。

首先 $h(1)=1$。必须联通这个性质不好做，如果不要求联通的话，那么容斥系数总和一定是 0，这个可以推一下组合数得到。那么考虑求不联通的容斥系数总和。

对于 $h(i)$，假设 $u$ 所在的连通块大小为 $j$，假设 $j\leq n-2$，也就是剩下的部分的点数 $\geq 2$，因为剩下的部分的点不要求联通或者不连通，所以容斥系数总和为 0，所以乘起来仍然是 0，所以可以忽略这个部分。

那么就是要考虑当 $j=n-1$ 时的容斥系数总和，那么枚举孤立点，剩下的是一个子问题，也就是 $h(i)=-(n-1)h_{i-1}$。那么 $h(i)=(-1)^{i-1}(i-1)!$。

那么这个题目就做完了，总的复杂度在于最后的枚举子集的 $O(3^n)$。

---

## 作者：mskqwq (赞：0)

由于后面两条限制比较难处理，考虑容斥其中一个，显然容斥第二个更可做。那么我们需要钦定几对位置 $(i,j)$ 相等，然后方案乘上容斥系数。这时候我们将所有的 $(i,j)$ 连一条无向边，那么同个连通块内的数都相等，接着考虑状压，每次枚举一个连通块进行转移。

然后就是转移系数的问题，我们需要知道所有 $n$ 个点的连通图的容斥系数之和，发现和经典的[连通图计数](https://www.luogu.com.cn/problem/P4841)问题类似，考虑容斥。设 $g_n$ 表示 $n$ 个点的无向图的容斥系数之和，由容斥定理得 $g_n=[n=1]$。然后设 $f_n$ 表示 $n$ 个点的连通图的容斥系数之和，那么 $f_n = g_n-\sum_{i=1}^{n-1} \binom {n-1}{i-1} f_ig_{n-i}=(-1)^{n-1}(n-1)!$。

最后注意枚举连通块的时候一定要包含当前没有被选的编号最小的点，否则会算重。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define LL __int128_t
#define eb emplace_back
#define pii pair<int,int>
#define pc(x) __builtin_popcountll(x)
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline ll read(){
    char ch=getchar();ll f=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
const int N=1e5+10,mod=998244353;
ll n,m,d[N],f[1<<16],g[1<<16],fac[N];
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(LL a,LL b){return min(a*b/gcd(a,b),(LL)m+1);}
void misaka(){
    n=read(),m=read();
    rep(i,1,n) d[i]=read();
    f[0]=g[0]=fac[0]=1;
    rep(i,1,n) fac[i]=fac[i-1]*i%mod;
    rep(i,1,(1<<n)-1){
        g[i]=1;
        rep(j,1,n)if(i>>j-1&1) g[i]=lcm(g[i],d[j]);
        g[i]=(m/g[i])%mod*fac[pc(i)-1]%mod;
        for(int j=i;j;j=(j-1)&i)if((j&-j)==(i&-i)){
            if(pc(j)&1) (f[i]+=f[i^j]*g[j]%mod)%=mod;
            else f[i]=(f[i]-f[i^j]*g[j]%mod+mod)%mod;
        }
    }
    printf("%lld",f[(1<<n)-1]);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB",abs(&__st-&__ed)/1024./1024);});
    #endif
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

