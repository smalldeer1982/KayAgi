# [ARC124E] Pass to Next

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc124/tasks/arc124_e

$ 1,\ 2,\ \ldots,\ N $ の番号がついた人が円環状に並んでいます。

$ 1\ \leq\ i\ \leq\ N-1 $ を満たす人 $ i $ の右隣に人 $ i+1 $ がおり、人 $ N $ の右隣には人 $ 1 $ がいます。

人 $ i $ ははじめ、$ a_i $ 個のボールを持っています。

以下の処理を一度だけ行います。

- それぞれの人が現在持っているボールのうちいくつかを選ぶ($ 0 $ 個でもよい)
- その後、選んだボールを全て右隣の人に **同時に** 渡す。
- 長さ $ N $ の数列を作る。数列の $ i $ 番目の要素は人 $ i $ が現在持っているボールの個数と等しい値である。

処理の結果できる数列としてありうるものの集合を $ S $ とします。 たとえば、$ a=(1,1,1) $ のとき $ S=\ \{(0,1,2),(0,2,1),(1,0,2),(1,1,1),(1,2,0),(2,0,1),(2,1,0)\ \} $ です。

$ \sum_{x\ \in\ S}\ \prod_{i=1}^{N}\ x_i $ を $ 998244353 $ で割ったあまりを計算してください。

## 说明/提示

### 制約

- 与えられる入力は全て整数
- $ 3\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

\- $ S=\ \{(0,1,2),(0,2,1),(1,0,2),(1,1,1),(1,2,0),(2,0,1),(2,1,0)\ \} $ です。 - $ \sum_{x\ \in\ S}\ \prod_{i=1}^{N}\ x_i $ は $ 1 $ です。

### Sample Explanation 3

\- $ 998244353 $ で割ったあまりを求めるのを忘れずに。

## 样例 #1

### 输入

```
3
1 1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
3
2 1 1```

### 输出

```
6```

## 样例 #3

### 输入

```
20
5644 493 8410 8455 7843 9140 3812 2801 3725 6361 2307 1522 1177 844 654 6489 3875 3920 7832 5768```

### 输出

```
864609205```

# 题解

## 作者：Rolling_star (赞：22)

设操作序列为 $x_i$，即为每个人向右传递的球数，则传完球的序列 $b_i=a_i-x_i+x_{i-1}$，发现后边其实是 $x_i$ 的差分，所以答案只与差分相关，所以我们只统计 $\min x_i=0$ 的操作序列，因为所有 $\min x_i>0$ 的情况都可以通过使所有 $x_i$ 减去 $\min x_i$ 来实现转化，如果统计 $\min x_i=0$ 的话，只需要容斥一下，分别统计所有 $x_i\in[0,a_i]$ 的情况和所有 $x_i\in[1,a_i]$ 的权值相减即可。

考虑答案：

$$f_n=\prod_{i=1}^n (a_i-x_i+x_{i-1})$$

如果考虑转移的话，那么就可以展开第 $n$ 项得到：

$$a_n\prod_{i=1}^{n-1} (a_i-x_i+x_{i-1})-x_n\prod_{i=1}^{n-1} (a_i-x_i+x_{i-1})+x_{n-1}\prod_{i=1}^{n-1} (a_i-x_i+x_{i-1})$$

因为 $a_n$ 和 $x_n$ 与前边项无关，又因为 $x_n\in [0,a_i]$，所以前两项为 $a_nf_{n-1}$ 和 $\left(\sum_{i=0}^{a_n}i\right)\cdot f_{n-1}$，但是在第三项出现了问题，我们单独将它拿出来审视，设：

$$g_n=x_n\prod_{i=1}^n (a_i-x_i+x_{i-1})$$

考虑它的转移，也拆开第 $n$ 项来分析：

$$x_na_n\prod_{i=1}^{n-1} (a_i-x_i+x_{i-1})-x_n^2\prod_{i=1}^{n-1} (a_i-x_i+x_{i-1})+x_nx_{n-1}\prod_{i=1}^{n-1} (a_i-x_i+x_{i-1})$$

然后发现，$x_na_n$，$x_n^2$ 与前边项无关，直接统计即可，观察最后一项其实就是 $x_ng_{n-1}$，从之前转移即可。

将前边的两个递推公式综合起来可得：

$$f_n=S_1(a_n)f_{n-1}+(a_n+1)g_{n-1}$$
$$g_n=(a_nS_1(a_n)-S_2(a_n))f_{n-1}+S_1(a_n)g_{n-1}$$

然后枚举断点情况和 $x_i$ 值域情况容斥即可。

---

## 作者：ZillionX (赞：20)

# Description

有 $n$ 个人排成一个环传球，第 $i$ 个人初始球数为 $a_i$，每个人同时把求传给下一个人（即不能将上一个人传给自己的球传给下一个人），对所有不同的最终局面，设第 $i$ 个人的最终球数为 $b_i$，求 $\sum\limits_b \prod\limits_{i=1}^n b_i$。

$n \le 10^5, a_i \le 10^9$，时限 2s。

# Solution

不是很懂矩乘转移的做法，这里是官方题解所述简洁的 DP 做法。

本题的转化和优化手段非常之多，同时 DP 状态定义也非常抽象，本题解将试图具体地讲清楚整道题的解决过程。

------------

首先，我们考虑在操作序列 $x_i$（表示第 $i$ 人向第 $i \bmod n+1$ 人的传球数）和最终状态 $b_i$ 间建立映射。

不难发现，若每个 $x_i$ 皆为正数，则我们把所有 $x_i$ 都减去 $1$ 所对应的 $b_i$ 相同。因此，定义存在至少一个人不传球的操作序列为**好的操作序列**。则好操作序列 $x'_i$ 和最终局面 $b_i$ 间存在双射。

下面我们将在 DP 时对每个人都传球的方案进行容斥，先忽略掉这部分内容。

我们考虑怎么方便地算出 $\prod b_i$，不妨考虑其组合意义：在每种最终局面中，从每个人最终的球中拿走一个的方案数。注意到这个计数问题要两部分组成：确定最终局面 + 选走球，我们设计 DP 来解决这个问题。

将球数设计在状态中是一种不可行的行为，完全没有办法对其进行优化。我们可以考虑最终局面中每个人的球的来源：他首先可以拿走自己原来的球，其次又可以拿上一个人传过来的球。

不难发现这两部分互不相干，第一部分只和下一个人有关，第二部分只和上一个人有关，我们可以把它们拆开来 DP。

设 $f_{i,0}$ 表示第 $i$ 个人选原有的球，考虑前 $i-1$ 人选球的方案数；$f_{i,1}$ 表示第 $i$ 个人选传来的球，考虑前 $i$ 人选球的方案数。

这样设计是为了方便考虑第 $i$ 人向第 $i+1$ 人（选前一人传球）的转移。

设 $s_k(n)$ 表示 $\sum\limits_{i=1}^n i^k$。

有转移

$$f_{i+1,0} \leftarrow f_{i,0} \cdot s_1(a_i) + f_{i,1 }\cdot (a_i+1)$$

$$f_{i+1,1} \leftarrow f_{i,0} \cdot  (a_i \cdot s_1(a_i) - s_2(a_i)) + f_{i,1} \cdot s_1(a_i)$$

上面那部分的前半即考虑第 $i$ 人的选择，后半即直接考虑传球的方案。

下面那部分的前半可以考虑第 $i$ 人送出 $x$ 个球，则贡献为 $\sum x (a_i-x)$，后半即考虑直接选定第 $i$ 人送出的球数。

现在我们再次回到前面被忽略的部分，可以发现直接在 $f_{i+1,0}$ 的转移中将 $a_i$ 减去 $1$ 则可以得到钦定所有人都传球的方案数。然后简单容斥即可。

现在我们遇到了最后一个很麻烦的问题，该问题并不是一个序列而是一个环，DP 要怎么初始化才能算出正确答案。我们可以对 $f_{1,0}$ 和 $f_{1,1}$ 分别初始化成 $1$，然后互不干扰地算出各自的答案，再减去 $1$ 即为最终解，具体实现可以参考代码。

时间复杂度线性。

# Code

```cpp
const int N=1e5+5,mo=998244353;
int n,a[N],f[N][2];
int qpow(int x,int y=mo-2) {
	int mul=1;
	while (y) {
		if (y&1) mul=mul*x%mo;
		x=x*x%mo,y>>=1;
	}
	return mul;
}
const int iv2=qpow(2),iv6=qpow(6);
int S(int x) {
	return x*(x+1)%mo*iv2%mo;
}
int G(int x) {
	return x*(x+1)%mo*(x*2+1)%mo*iv6%mo;
}
int calc(int w1,int w2) {
	mes(f);
	f[1][0]=w1,f[1][1]=w1^1;
	for (int i=1;i<=n;i++) {
		int v=i%n+1,w=a[i]-w2;
		ad(f[v][0],f[i][0]*S(w)%mo);
		ad(f[v][0],f[i][1]*(w+1)%mo);
		if (w2) w++;
		ad(f[v][1],f[i][0]*de(w*S(w)%mo,G(w))%mo);
		ad(f[v][1],f[i][1]*S(w)%mo);
	}
	return (w1?f[1][0]:f[1][1])-1;
}
signed main() {
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	printf("%lld",de((calc(1,0)+calc(0,0))%mo,(calc(0,1)+calc(1,1))%mo));
	return 0;
}
```


---

## 作者：APJifengc (赞：15)

我果然还是无脑型选手。

首先还是考虑设 $\{x_i\}$ 表示第 $i$ 个位置的人往后传了几个球，那么考虑如何将操作序列与最终局面一一对应。发现如果 $\{x_i\}$ 中的所有数都 $\ge 1$，那么我们可以直接全部减去一个 $1$，最终局面不变。所以，我们只需要统计所有 $\min x_i = 0$ 时的答案即可。这个可以简单容斥求出，即求出 $x_i \in [0, a_i]$ 时的答案，减去 $x_i \in [1, a_i]$ 时的答案。下面以前者为例子。

考虑我们要求的答案，实际上等于 $\displaystyle \prod_{i=1}^n (a_i - x_i + x_{i  - 1})$（当 $i=1$ 时为 $(a_1 - x_1 + x_n)$）。

直接统计不好统计，而这是一个三项式乘积，我们可以把乘积拆开，每次从三项中选一项乘起来，这样同样也可以得到答案。

考虑每一位怎么选。

- 假如我们选了 $a_i$，那么这一位对于 $x_i \in [0, a_i]$ 中的任意一种情况贡献都为 $a_i$；
- 假如我们选了 $-x_i$，那么对于 $x_i \in [0, a_i]$ 中的任意一种情况的贡献都为 $x_i$，等差数列求和；
- 假如我们选了 $x_{i - 1}$，那么我们需要知道上一次选的是否为 $x_i$，如果是，那么两个数的贡献需要一起来算，即求平方和；否则，这一位还是自己算自己的贡献，求等差数列和。同时，需要乘上 $x_i$ 的方案数。

发现第三种情况很难考虑，我们不妨在选当前一项的时候就先确定下一项是否选 $x_{i - 1}$，如果选就直接从 $f_i$ 转移到 $f_{i + 2}$，否则转移到 $f_{i + 1}$。

具体的，我们可以设 $f_i$ 为考虑到第 $i$ 项，上一项选择了 $x_i$ 且这一项不选择 $x_{i-1}$ 的权值和；$g_i$ 为考虑到第 $i$ 项，上一项没有选择 $x_i$，这一项可以选择 $x_{i-1}$ 的权值和。那么转移直接考虑上述几种情况即可。

但是这个转移是一个环，所以我们需要先断开，钦定好断点处的选择方案，然后再 DP 统计方案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005, P = 998244353;
int n;
int a[MAXN];
int f[MAXN], g[MAXN];
int qpow(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1ll * ans * a % P;
        a = 1ll * a * a % P;
        b >>= 1;
    }
    return ans;
}
const int INV2 = (P + 1) / 2, INV6 = qpow(6, P - 2), INV3 = qpow(3, P - 2);
int solve0() {
    int ans = 0;
    auto dp = [&] {
        for (int i = 1; i <= n; i++) {
            // sel a_i
            g[i + 1] = (g[i + 1]
                + 1ll * (f[i] + g[i]) * (a[i] + 1) % P * a[i]
            ) % P;
            // sel -x_i and no x_i-1
            f[i + 1] = (f[i + 1]
                - 1ll * (f[i] + g[i]) * a[i] % P * (a[i] + 1) % P * INV2 % P + P
            ) % P;
            // sel -x_i and x_i-1
            g[i + 2] = (g[i + 2] 
                - 1ll * (f[i] + g[i]) * a[i] % P * (a[i] + 1) % P * (2 * a[i] + 1) % P * INV6 % P
                * (a[i + 1] + 1) % P + P
            ) % P;
            // sel x_i-1
            g[i + 1] = (g[i + 1]
                + 1ll * g[i] * a[i - 1] % P * INV2 % P * (a[i] + 1) % P
            ) % P;
        }
    };
    // case 1: no x_n
    for (int i = 1; i <= n + 1; i++) 
        f[i] = g[i] = 0;
    f[1] = 1;
    dp();
    ans = (ans + (f[n + 1] + g[n + 1]) % P) % P;
    // case 2: x_n
    for (int i = 1; i <= n + 1; i++) 
        f[i] = g[i] = 0;
    f[1] = g[1] = 0;
    g[2] = a[1] + 1;
    dp();
    ans = (ans + 
        1ll * f[n + 1] * (2 * a[n] + 1) % P * INV3 +
        1ll * g[n + 1] * a[n] % P * INV2
    ) % P;
    return ans;
}
int solve1() {
    int ans = 0;
    auto dp = [&] {
        for (int i = 1; i <= n; i++) {
            // sel a_i
            g[i + 1] = (g[i + 1]
                + 1ll * (f[i] + g[i]) * a[i] % P * a[i]
            ) % P;
            // sel -x_i and no x_i-1
            f[i + 1] = (f[i + 1]
                - 1ll * (f[i] + g[i]) * a[i] % P * (a[i] + 1) % P * INV2 % P + P
            ) % P;
            // sel -x_i and x_i-1
            g[i + 2] = (g[i + 2] 
                - 1ll * (f[i] + g[i]) * a[i] % P * (a[i] + 1) % P * (2 * a[i] + 1) % P * INV6 % P
                * a[i + 1] % P + P
            ) % P;
            // sel x_i-1
            g[i + 1] = (g[i + 1]
                + 1ll * g[i] * (a[i - 1] + 1) % P * INV2 % P * a[i] % P
            ) % P;
        }
    };
    // case 1: no x_n
    for (int i = 1; i <= n + 1; i++) 
        f[i] = g[i] = 0;
    f[1] = 1;
    dp();
    ans = (ans + (f[n + 1] + g[n + 1]) % P) % P;
    // case 2: x_n
    for (int i = 1; i <= n + 1; i++) 
        f[i] = g[i] = 0;
    f[1] = g[1] = 0;
    g[2] = a[1];
    dp();
    ans = (ans + 
        1ll * f[n + 1] * (2 * a[n] + 1) % P * INV3 +
        1ll * g[n + 1] * (a[n] + 1) % P * INV2
    ) % P;
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    // printf("%d\n", solve0());
    // printf("%d\n", solve1());
    printf("%d\n", (solve0() - solve1() + P) % P);
    return 0;
}
```

---

## 作者：tzc_wk (赞：14)

首先第一步是一个浅显的观察：我们要求的是**所有可能的最终序列的贡献之和**，如果能改为计算**所有操作序列的贡献之和**那问题会简单很多，并且我们惊奇地发现，如果一组 $x_i$ 全大于 $0$，那么把它们全减去 $1$ 以后得到的答案序列不会改变，而对于任意一种可能的最终序列，必然存在一组 $\min x_i=0$ 的操作序列能够得到这个答案序列。也就是说我们建立了一组 $\min x_i=0$ 的答案序列到操作序列的映射。那么具体怎么计算这个东西呢？**我们计算所有操作序列的答案之和，再将所有 $b_i$ 减一，计算新的操作序列之和，二者做差就是答案。**

转换贡献体，改为每个人选一个目前在手中的球，计算选择的方案数。

每个人选择的球有两种情况，一是上一个人传过来的，二是自己原有的。

先考虑链的情况，我们设 $dp_{i,0/1}$ 表示考虑到第 $i$ 个人，第 $i$ 个人考虑自己原有的 / 上一个人传过来的球的方案，所有**已经确定贡献**的方案数。注意，之所以说已经确定的贡献，是因为如果第 $i$ 个人考虑自己原有的球，那么有可能下一个人考虑上一个人（也就是 $i$）传过来的球，那么我们把第 $i$ 个人传球的方案放到 $i+1$ 那里计算，这样第 $i$ 个人的方案就不算“已经确定贡献”的方案。转移显然：

- $dp_{i-1,1}·(a_i+1)\to dp_{i,0}$
- $dp_{i-1,0}·(\sum_{j=0}^{a_i} j)\to dp_{i,0}$
- $dp_{i-1,1}·(\sum_{j=0}^{a_i} j)\to dp_{i,1}$
- $dp_{i-1,0}·(\sum_{j=0}^{a_i} (a_i-j)·j)\to dp_{i,1}$

还有一个问题就是环的情况。其实很简单，强制钦定第 $1$ 个人是原有的还是传过来的就行了。代码里有个 $-1$ 是因为我给 $dp_{1,c1}$ 赋了 $1$ 的初值，这个初值不能算入答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5;
const int MOD=998244353;
const int INV6=(MOD+1)/6;
int n,a[MAXN+5],dp[MAXN+5][2];
int getsum1(int x){return 1ll*x*(x+1)/2%MOD;}
int getsum2(int x){return 1ll*x*(x+1)%MOD*(2*x+1)%MOD*INV6%MOD;}
int calc(int c1,int c2){
	memset(dp,0,sizeof(dp));dp[1][c1]=1;
	for(int i=1;i<=n;i++){
		dp[i%n+1][0]=(1ll*dp[i][0]*getsum1(a[i]-c2)+1ll*dp[i][1]*(a[i]-c2+1))%MOD;
		dp[i%n+1][1]=(1ll*dp[i][0]*(1ll*a[i]*getsum1(a[i])%MOD-getsum2(a[i])+MOD)+1ll*dp[i][1]*getsum1(a[i]))%MOD;
	}return (dp[1][c1]-1+MOD)%MOD;
}
int main(){
	scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	printf("%d\n",(0ll+calc(0,0)+calc(1,0)-calc(0,1)-calc(1,1)+MOD+MOD)%MOD);
	return 0;
}
```


---

## 作者：___OccDreamer___ (赞：6)

### 闲话

~~组合意义 dp~~，化式子大法好，暴力出奇迹。

### $\text{Solution}$

#### $\text{Part1}$

在化式子之前，我们先来做一些准备工作。

设 $x_i$ 表示第 $i$ 个人传走的球的数量。那么最终第 $i$ 个人手上有 $a_i-x_i+x_{i-1}$ 个球。

考虑一下如何去重，对于 $x$ 相同的差分数组，最后的结果是一样的。所以我们可以钦定求至少有一个 $x_i=0$ 的答案，这样就能不重不漏的算出所有情况了。

至于怎么求，我们用 $x_i\in[0,a_i]$ 和 $x_i\in[1,a_i]$ 容斥一下即可。下面以 $x_i\in[0,a_i]$ 为例。

再改写一下这个不太好看的式子。

$$
\sum_{1\leq j\leq n,0 \leq x_j\leq a_j}\prod\limits_{i=1}^n (a_i-x_i+x_{i-1})
$$

#### $\text{Part2}$

设 $S_i(a)=\sum\limits_{x=1}^{a} x^i$。

暴力展开一些项，

$$
\begin{aligned}
&\sum\limits_{1\leq j\leq n,0 \leq x_j\leq a_j}(a_1-x_1+x_n)(a_2-x_2+x_1)\prod\limits_{i=3}^n (a_i-x_i+x_{i-1})\\
&\sum_{1\leq j\leq n,0 \leq x_j\leq a_j}(a_1a_2-a_1x_2+a_1x_1-a_2x_1+x_1x_2-x_1^2+a_2x_n-x_2x_n+x_1x_n)\prod\dots
\end{aligned}
$$

我们用分配率把式子拆开，先考虑标红的项，

$$
\sum({\color{red}a_1a_2}-a_1x_2{\color{red}{+a_1x_1}}{\color{red}-a_2x_1}+x_1x_2{\color{red}-x_1^2}+a_2x_n-x_2x_n+x_1x_n)\prod
$$

在 $\prod$ 中不含 $x_1$，所以现在 $x_1$ 是已知的了，因此：

$$
\sum a_1a_2(a_1+1)+S_1(a_1)(a_1-a_2)-S_2(a_1)\prod
$$

记 $f_0=a_1a_2(a_1+1)+S_1(a_1)(a_1-a_2)-S_2(a_1)$，表示都能算出来。

$$
\sum({\color{grey}a_1a_2}{\color{red}-a_1x_2}{\color{grey}{+a_1x_1}}{\color{grey}-a_2x_1}{\color{red}+x_1x_2}{\color{grey}-x_1^2}+a_2x_n-x_2x_n+x_1x_n)\prod
$$

同理，

$$
\sum[-(a_1+1)a_1+S_1(a_1)]x_2\prod
$$

记 $f_p=-(a_1+1)a_1+S_1(a_1)$，表示 含 $x_{i+1}$ 算不出。

$$
\sum({\color{grey}a_1a_2}{\color{grey}-a_1x_2}{\color{grey}{+a_1x_1}}{\color{grey}-a_2x_1}{\color{grey}+x_1x_2}{\color{grey}-x_1^2}{\color{red}{+a_2x_n}}-x_2x_n{\color{red}+x_1x_n})\prod
$$

记 $f_n=(a_1+1)a_2+S_1(a_1)$，表示含 $x_n$ 算不出。

$$
\sum({\color{grey}a_1a_2}{\color{grey}-a_1x_2}{\color{grey}{+a_1x_1}}{\color{grey}-a_2x_1}{\color{grey}+x_1x_2}{\color{grey}-x_1^2}{\color{grey}{+a_2x_n}}{\color{red}-x_2x_n}{\color{grey}+x_1x_n})\prod
$$

记 $f_{np}=-(a_1+1)$ 表示含 $x_{i+1}x_n$ 算不出。

现在式子变成，

$$
\sum\limits_{2\leq j\leq n,0 \leq x_j\leq a_j}(f_0+f_px_2+f_nx_n+f_{np}x_2x_n)\prod\limits_{i=3}^n(a_i-x_i+x_{i-1})
$$

#### $\text{Part3}$

我们再来展开一项，
$$
\sum(f_0+f_px_2+f_nx_n+f_{np}x_2x_n)(a_3-x_3+x_2)\prod\limits_{i=4}^n(a_i-x_i+x_{i-1})
$$
现在 $x_2$ 又是已知的了。同上，
$$
\begin{aligned}
f_0^{(2)}&=f_0(a_2+1)a_3+f_0S_1(a_2)+f_pS_1(a_2)a_3+f_pS_2(a_2)\\
f_p^{(2)}&=-f_0(a_2+1)-f_pS_1(a_2)\\
f_n^{(2)}&=f_n(a_2+1)a_3+f_nS1(a_2)+f_{np}S_1(a_2)a_3+f_{np}S_2(a_2)\\
f_{np}^{(2)}&=-f_n(a_2+1)-f_{np}S_1(a_2)\\
\end{aligned}
$$
以此类推，做 $n-1$ 次。
$$
f_0^{(n)}+f_p^{(n)}x_n+f_n^{(n)}x_n+f_{np}^{(n)}x_n^2
$$
这时 $x_n$ 是已知的，
$$
ans=f_0^{(n)}(a_n+1)+f_p^{(n)}S_1(a_n)+f_n^{(n)}S_1(a_n)+f_{np}^{(n)}S_2(a_n)
$$
初始时，$f_0=a_1,f_p=-1,f_n=1,f_{np}=0$。

完结撒花。



### $\text{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define cout cerr
#define debug cout<<"debug"<<endl;
using namespace std;
const int N=1e5+5;
const int mod=998244353;
const ll inv2=499122177;
const ll inv6=166374059;
int n;
ll a[N];
inline int read() {
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=1; ch=getchar();}
	while(isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return f?-x:x;
}
inline void inc(ll &x,int y) {x+=y-mod;x+=(x>>63)&mod;}
inline ll S1(ll x) {return x*(x+1)%mod*inv2%mod;}
inline ll S2(ll x) {return x*(x+1)%mod*(2*x+1)%mod*inv6%mod;}
inline ll calc(ll op) {
	ll f0=a[1],fp=-1,fn=1,fnp=0;
	for(int i=2;i<=n;i++) {
		ll t0=0,tp=0,tn=0,tnp=0;
		inc(t0,f0*(a[i-1]+op)%mod*a[i]%mod);
		inc(t0,f0*S1(a[i-1])%mod);
		inc(t0,fp*S1(a[i-1])%mod*a[i]%mod);
		inc(t0,fp*S2(a[i-1])%mod);
		
		inc(tp,(mod-f0*(a[i-1]+op)%mod)%mod);
		inc(tp,(mod-fp*S1(a[i-1])%mod)%mod);
		
		inc(tn,fn*(a[i-1]+op)%mod*a[i]%mod);
		inc(tn,fn*S1(a[i-1])%mod);
		inc(tn,fnp*S1(a[i-1])%mod*a[i]%mod);
		inc(tn,fnp*S2(a[i-1])%mod);
		
		inc(tnp,(mod-fn*(a[i-1]+op)%mod)%mod);
		inc(tnp,(mod-fnp*S1(a[i-1])%mod)%mod);
		f0=t0,fp=tp,fn=tn,fnp=tnp;
	}
	ll ans=0;
	inc(ans,f0*(a[n]+op)%mod);
	inc(ans,fp*S1(a[n])%mod);
	inc(ans,fn*S1(a[n])%mod);
	inc(ans,fnp*S2(a[n])%mod);
	return ans;
}
int main()
{
	freopen("random_01.txt","r",stdin);
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	printf("%lld",(calc(1)-calc(0)+mod)%mod);
	return 0;
}
```



---

## 作者：liujy_ (赞：3)

我们设 $c_i$ 表示 $i$ 向 $i\bmod n+1$ 传的球数。可以证明数组 $c$ 中至少有一个 $0$ ，假设 $c$ 中不存在 $0$ 我们可以将每个 $c_i$ 都变成 $c_i-1$，这样最终得到的 $b$ 是一样的。   
那么我们只要对 $c$ 去进行计数就不会计重。以为 $c$ 中有至少一个 $0$ 的位置，我们可以枚举编号最小的 $c_i$ 为 $0$ 的 $i$，相当于 $i$ 不会向后面传球。就可以从 $i$ 和 $i\bmod n+1$ 中间断开，剩下一条链进行动态规划。   
首先有一个暴力的想法就是设 $f_{i,j}$ 表示第 $i$ 个位置向后面传 $j$ 个球的前 $i$ 个人的答案和。有一个暴力的转移是 $f_{i,j}=\sum\limits_{k=0}^{a_{i-1}}(a_i-j+k)\times f_{i-1,k}$。    
可以发现我们只关注 $\sum\limits_{j=0}^{a_i} f_{i,j}$ 的值，那么转移可以写成
$$\begin{aligned} \sum\limits_{j=0}^{a_i} f_{i,j} &=  \sum\limits_{j=0}^{a_i}\sum\limits_{k=0}^{a_{i-1}}(a_i-j+k)\times f_{i-1,k}\\&=(\sum\limits_{j=0}^{a_i}(a_i-j)\cdot \sum\limits_{k=0}^{a_{i-1}}f_{i-1,k})+(\sum\limits_{j=0}^{a_i}\sum\limits_{k=0}^{a_{i-1}}f_{i-1,k}\times k)\\&=\frac{a_i\times (a_i+1)}{2}\times \sum\limits_{k=0}^{a_{i-1}}f_{i-1,k}+(a_i+1)\times \sum\limits_{k=0}^{a_{i-1}}f_{i-1,k}\times k)\end{aligned}$$
。   
所以我们在转移的时候实际上只要维护两个值，分别是 $\sum\limits_{j=0}^{a_i} f_{i,j}$ 和 $\sum\limits_{j=0}^{a_i} f_{i,j}\times j$。容易发现对于每个 $i$ 的转移都可以写成矩阵的形式，我们只要对转移矩阵维护一个前缀积再维护一个后缀积。接下来我们就可以枚举第一个 $c_i=0$ 的位置，就可以直接利用已经维护好的矩阵信息快速得到此时这条链的转移矩阵并得到答案。  
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=1e6+5,mod=998244353;
int n,ans,a[N];
struct Mat{
	int a[2][2];
	Mat(){memset(a,0,sizeof(a));}
	Mat operator * (Mat b){Mat c;
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)c.a[i][j]=((long long)c.a[i][j]+1ll*a[i][k]*b.a[k][j]%mod)%mod;
		return c;
	}
}s[N],t[N];
int get1(int x){return 1ll*x*(x+1)/2%mod;}
int get2(int x){return (1ll*get1(x)%mod*x%mod-((__int128)x*(x+1)*(2*x+1)/6%mod)+mod)%mod;}
signed main(){
	scanf("%lld",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%lld",&x);a[i]=x;
		s[i].a[0][0]=get1(x-1),s[i].a[1][0]=x,s[i].a[0][1]=get2(x),s[i].a[1][1]=get1(x);
		t[i].a[0][0]=get1(x),t[i].a[1][0]=x+1,t[i].a[0][1]=get2(x),t[i].a[1][1]=get1(x);
	}
	s[0].a[0][0]=s[0].a[1][1]=t[n+1].a[0][0]=t[n+1].a[1][1]=1;
	for(int i=1;i<=n;i++)s[i]=s[i-1]*s[i];
	for(int i=n;i>=1;i--)t[i]=t[i]*t[i+1];
	for(int i=1;i<=n;i++){
		Mat g=t[i+1]*s[i-1];
		ans=((long long)ans+1ll*g.a[0][0]*a[i]%mod+g.a[0][1]+mod)%mod;
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}
```


---

## 作者：jijidawang (赞：3)

对于操作序列 $\{x_n\}$，可以发现如果能减的话给每个元素都减一得到的最终局面不变。称一个满足 $\min x_i=0$ 的操作序列 $\{x\}$ 为素操作序列，那么可以发现素操作序列和最终局面之间是存在双射的，于是只需要计算素操作序列个数。

考虑容斥计算，即算出 $x_i\in[0,a_i]$ 的权值和减 $x_i\in[1,a_i]$ 的权值和。做法本质相同，下面以前者为例。

首先大力写出答案：$\displaystyle\prod_{i=1}^n(a_i-x_i+x_{i-1})$。那么一项一项选就行了：
- 如果选 $a_i$，那么这一位的贡献即为 $a_i$。
- 如果选 $-x_i$，那么这一位的贡献即为 $-x_i$，表现出来是一个等差数列求和的形式。
- 如果选 $x_{i-1}$，如果上一位选的是 $x_i$ 那么贡献表现为平方和，否则表现为等差数列求和。

由于有一个上一位的限制那么开一个状态机 DP 表示就好了，具体的，维护：
$$\begin{aligned}&f(n)=\sum_x\prod_{i=1}^n(a_i-x_i+x_{i-1})\\&g(n)=\sum_xx_n\prod_{i=1}^n(a_i-x_i+x_{i-1})\end{aligned}$$
然后提出 $\prod$ 内的一项考虑转移即可。

最后，因为是环状结构所以需要破开然后钦定断点处的选择方案。时间复杂度 $\Theta(n)$，可以通过。

---

## 作者：Felix72 (赞：1)

这是一个不太简单的计数题，模拟赛时没有得分，赛后更是用了两个小时才把题解弄清楚。当然更多的是因为对这类计数技巧的不熟练所致，因此写个题解，希望后人不要像我一样。

首先我们需要明确答案的式子到底是什么。这部分就有两种做法：

1. 如果你希望贡献形式化一点，你会写出形如 $\prod_{i = 1}^{n} (a_i - p_1 + p_{i - 1})$，其中 $p_i$ 是第 $i$ 个人往后传递的球数，且 $p_0$ 和 $p_n$ 表同一意思。我们知道不同的 $p$ 之间取值彼此独立，因此可以通过每个括号中选一个元素的思路列出 DP 状态。

2. 如果你用组合意义思考，那么你会想到一个常用技巧：**把累乘视作每组元素中选一个代表**。这样，分两种（当前的人选出的代表球来自谁）情况讨论，便可以跳过写式子直接进入 DP 环节。

两种方法殊途同归，用组合意义思路，不妨设 DP 状态 $f_{i, 0}$ 表示第 $i$ 个人用自己的球，$f_{i, 1}$ 表示用上一个人的球（如果用拆式子的思路，这个转移的定义会略有修改，但是等价的）。分类讨论转移：

- $f_{i, 0} \to f_{i + 1, 0}$：此时状态数量和移动球的个数以及第 $i$ 个人选哪个球有关；
- $f_{i, 0} \to f_{i + 1, 1}$：把两个人的决策一起计算；
- $f_{i, 1} \to f_{i + 1, 0}$：此时只和移动球的个数相关；
- $f_{i, 1} \to f_{i + 1, 1}$：此时和移动球的个数以及第 $i + 1$ 个人选哪个球相关。

如果不能感性理解，可以参考代码。

注意，到这里为止这个做法还是错的，因为并没有去重。但是如果 $\min p > 0$ 的话，把所有 $p$ 减去一最终序列是不变的，因此直接钦定 $p \neq 0$ 再次计算一次，容斥即可。没有想到容斥也无所谓，枚举 $p_i = 0$ 的最小 $i$，矩阵转移也可以。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 100010, mod = 998244353;
inline void Plus(long long &now, long long add)
{now += add; while(now >= mod) now -= mod;}
int n; long long f[N][2], a[N];
inline long long get(int lim, int op)
{
	for(int i = 1; i <= n; ++i)
	{
		int to = i % n + 1;
		Plus(f[to][0], f[i][0] * ((a[i] - lim) * (a[i] - lim + 1) / 2 % mod) % mod + f[i][1] * (a[i] + 1 - lim) % mod);
		Plus(f[to][1], f[i][0] * (a[i] * (a[i] + 1) / 2 % mod * a[i] % mod - (__int128)a[i] * (a[i] + 1) * (2 * a[i] + 1) / 6 % mod) % mod);
		Plus(f[to][1], f[i][1] * (a[i] * (a[i] + 1) / 2 % mod) % mod);
	}
	return f[1][op] - 1;
}
inline long long work(int lim)
{
	long long res = 0;
	memset(f, 0, sizeof(f));
	f[1][0] = 1; Plus(res, get(lim, 0));
	memset(f, 0, sizeof(f));
	f[1][1] = 1; Plus(res, get(lim, 1));
	return res;
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	cout << ((work(0) - work(1)) % mod + mod) % mod << '\n';
	return 0;
}
/*

*/
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc124_e)

**题目大意**

> $n$ 个人站成环，第 $i$ 个人手里有 $a_i$ 个球，每个人选择 $x_i\in[0,a_i]$，同时把 $x_i$ 个球传给下一个人。
>
> 求所有可能得到的局面中每个人手中球数乘积之和。
>
> 数据范围：$n\le 10^5$。

**思路分析**

首先我们对每种局面刻画一组唯一的 $\{x_i\}$，如果所有 $x_i>0$，可以把他们全部 $-1$，容易证明每一种终态都唯一对应一组解。

因此我们计算所有操作序列的结果之和，减去所有 $x_i>0$ 的操作序列结果之和。

只考虑所有操作序列的结果之和，那么乘积等价于在每个人手中取一个球的方案数，枚举每个人手中的球来自自己还是前一个人。

设 $f_{i,0/1}$ 表示考虑了前 $i$ 个人的 $x$，第 $i$ 个人选择的球来自自己还是前一个人，并且球来自 $1\sim i-1$ 的贡献已经计算完毕。

转移时把原来第 $i$ 个人手中球的贡献计算掉，初始值枚举第 $1$ 个人的状态后断环为链即可。

钦定 $x_i>0$ 只需要简单改变一些转移贡献的计算。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=1e5+5,MOD=998244353,i6=(MOD+1)/6;
ll s1(ll x) { return x*(x+1)/2%MOD; }
ll s2(ll x) { return x*(x+1)%MOD*(2*x+1)%MOD*i6%MOD; }
int n,a[MAXN];
ll f[MAXN][2];
ll dp(int o,int c) {
	memset(f,0,sizeof(f)),f[1][c]=1;
	for(int i=1;i<=n;++i) {
		f[i+1][0]=(f[i][0]*s1(a[i]-o)+f[i][1]*(a[i]+1-o))%MOD;
		f[i+1][1]=(f[i][0]*(s1(a[i])*a[i]%MOD+MOD-s2(a[i]))+f[i][1]*s1(a[i]))%MOD;
	}
	return f[n+1][c];
}
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	printf("%lld\n",(dp(0,0)+dp(0,1)+MOD*2-dp(1,0)-dp(1,1))%MOD);
	return 0;
}
```

---

## 作者：Inui_Sana (赞：0)

讲一种不同的进行最后一步 dp 的解决方法。

前面的大概说一下，就是考虑令 $f_i$ 为 $i$ 给 $i\bmod n+1$ 的球数，则每个 $\min f_i=0$ 的 $f$ 和 $b$ 之间构成双射，于是转化成求 $\sum\prod a_i-f_i+f_{i-1}$。

怎么算这个呢？如果是形如 $a_i-f_i$ 这样，每一位是独立的，就可以分别算然后乘起来。但是还和 $f_{i-1}$ 有关。把乘积用分配律展开，硬上 dp：设 $dp_{i,0/1,0/1}$ 表示当前枚举到第 $i$ 位，这一位的 $f_i$ 是否确定，当前是否已经 $\exists j,f_j=0$。

先算乘积的第一项为 $a_1$ 或 $-f_1$ 的时候的贡献。每一位有四种转移：

1. 这一位选 $a_i$。
2. 这一位选 $-f_i$ 且下一位不选 $f_i$。
3. 这一位选 $f_{i-1}$ 且上一位不选 $f_{i-1}$。
4. 这一位和上一位都选 $f_{i-1}$。

转移很冗长不展开讲，大概就是对于选了的 $f_i$，如果在 $1$ 个位置选了，就乘上 $\sum_{j\le a_i} j=\frac{a_i(a_i+1)}2$，在 $2$ 个位置选了就乘上 $\sum_{j\le a_i}j^2=\frac{a_i(a_i+1)(2a_i+1)}6$，如果没选，这个位置对乘积没有影响，但是对方案数有影响，所以也乘上 $a_i$ 或 $a_i+1$。

同时转移的时候要判断这一位是否有 $f_i=0$，这样的 $i$ 只有在它没有被选到的时候对乘积有影响，在转移的时候加上这个转移即可。

最后统计答案的时候用类似的方法，判断 $f_n$ 的情况即可。

然后算第一位选 $f_{i-1}$ 的贡献，容易发现 dp 转移时类似的，只用改变初始值即可。注意此时 $i=2$ 时的转移 $4$ 不能用。这样把所有贡献累加得到答案即可。

code：

```cpp
int n,m,a[N],dp[N][2][2];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il int calc2(int x){
	return 1ll*x*(x+1)/2%mod;
}
il int calc3(int x){
	return (__int128)x*(x+1)*(2*x+1)/6%mod;
}
void solve(int x,int y,int op){
	mems(dp,0);
	dp[1][0][0]=x,dp[1][1][0]=y;
	rep(i,2,n){
		//选 a[i]
		dp[i][0][0]=Mod(1ll*dp[i-1][0][0]*a[i]%mod*a[i-1]%mod,1ll*dp[i-1][1][0]*a[i]%mod);
		dp[i][0][1]=Mod(1ll*dp[i-1][0][1]*a[i]%mod*(a[i-1]+1)%mod,1ll*dp[i-1][1][1]*a[i]%mod);
		dp[i][0][1]=Mod(dp[i][0][1],1ll*dp[i-1][0][0]*a[i]%mod);
		//选 -f[i]
		dp[i][1][0]=Mod(1ll*dp[i-1][0][0]*a[i-1]%mod*(mod-calc2(a[i]))%mod,1ll*dp[i-1][1][0]*(mod-calc2(a[i]))%mod);
		dp[i][1][1]=Mod(1ll*dp[i-1][0][1]*(a[i-1]+1)%mod*(mod-calc2(a[i]))%mod,1ll*dp[i-1][1][1]*(mod-calc2(a[i]))%mod);
		dp[i][1][1]=Mod(dp[i][1][1],1ll*dp[i-1][0][0]*(mod-calc2(a[i]))%mod);
		//选 f[i-1]
		dp[i][0][0]=Mod(dp[i][0][0],1ll*dp[i-1][0][0]*calc2(a[i-1])%mod);
		dp[i][0][1]=Mod(dp[i][0][1],1ll*dp[i-1][0][1]*calc2(a[i-1])%mod);
		dp[i][0][0]=Mod(dp[i][0][0],1ll*(i==2?op:Mod(1ll*dp[i-2][0][0]*a[i-2]%mod,dp[i-2][1][0]))*(mod-calc3(a[i-1]))%mod);
		dp[i][0][1]=Mod(dp[i][0][1],1ll*(i==2?0:Mod(1ll*dp[i-2][0][1]*(a[i-2]+1)%mod,dp[i-2][1][1]))*(mod-calc3(a[i-1]))%mod);
		dp[i][0][1]=Mod(dp[i][0][1],1ll*(i==2?0:dp[i-2][0][0])*(mod-calc3(a[i-1]))%mod);
	}
}
void Yorushika(){
	read(n);
	rep(i,1,n){
		read(a[i]);
	}
	int ans=0;
	solve(a[1],Mod(0,mod-calc2(a[1])),1);
	ans=Mod(dp[n][1][1],Mod(1ll*dp[n][0][1]*(a[n]+1)%mod,dp[n][0][0]));
	solve(1,0,0);
	printf("%d\n",Mod(Mod(ans,1ll*dp[n][0][1]*calc2(a[n])%mod),1ll*Mod(Mod(dp[n-1][0][0],1ll*dp[n-1][0][1]*(a[n-1]+1)%mod),dp[n-1][1][1])*(mod-calc3(a[n]))%mod));
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：_abcd_ (赞：0)

[[ARC124E] Pass to Next](https://atcoder.jp/contests/arc124/tasks/arc124_e)

显然，如果将所有 $x_i$ 同时加上一个数并不会影响结果，而且相同的结果仅可以通过这种方法产生，这样可以有效去重。这样，我们只需要算存在 $x_i = 0$ 的情况就行了。我们去枚举第一个满足 $x_s = 0$ 的 $s$，那么，就有当 $1 \le i < s$ 时，有 $1 \le x_i \le a_i$，否则 $0 \le x_i \le a_i$。我们令 $f_i$ 表示枚举到第 $i$ 个人所有情况下的权值和，那么当 $s < i \le n$ 时，就有
$$ f_i = \sum\limits_{x_i = 0}^{a_i} f_{i-1} (a_i + x_{i-1} - x_i) = S_1(a_i) f_{i-1} + (a_i + 1) x_{i-1} f_{i-1} $$
对于后半部分，设 $g_i = x_i f_i$，则
$$ g_i = \sum\limits_{x_i = 0}^{a_i} x_i (a_i + x_{i-1} - x_i) f_{i-1} = (a_i S_1(a_i) - S_2(a_i)) f_{i-1} + S_1(a_i) g_{i-1} $$

对于 $1 \le i < s$ 的情况，可以通过相似的推导得到。

同时，由于 $x_{s-1}$ 会影响到 $a_s$，因此在最后的转移需要特殊的推导。有
$$ f_i = \sum\limits_{x_i = 0}^{a_i} (a_i + x_{i-1} - x_i) (a_{i+1} + x_i) f_{i-1} $$
$$ = (a_i a_{i+1} (a_i + 1) + (a_i - a_{i+1}) S_1(a_i) - S_2(a_i)) f_{i-1} + (a_{i+1} (a_i + 1) + S_1(a_i)) g_{i-1} $$
$$ g_i = \sum\limits_{x_i = 0}^{a_i} x_i (a_i + x_{i-1} - x_i) (a_{i+1} + x_i) f_{i-1} $$
$$ = (a_i a_{i+1} S_1(a_i) + (a_i - a_{i+1}) S_2(a_i) - S_3(a_i)) f_{i-1} + (a_{i+1} S_1(a_i) + S_2(a_i)) g_{i-1} $$
枚举 $s$，直接转移是 $O(n^2)$ 的，但是转移是矩阵的形式，因此满足结合律，用后缀和优化可以做到 $O(n)$。

---

### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mclear(a) memset(a,0,sizeof a)
#define fls() fflush(stdout)
#define mod 998244353
#define maxn 100005
#define int ll
using namespace std;
int re()
{
    int x=0,t=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')t=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*t;
}
struct Matrix
{
    int a[2][2];
    Matrix()
    {
        memset(a,0,sizeof a);
    }
    Matrix operator * (const Matrix t)
    {
        Matrix ret;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    ret.a[i][j]=(a[i][k]*t.a[k][j]%mod+ret.a[i][j])%mod;
        return ret;
    }
    void print()
    {
        for(int i=0;i<2;i++,pn)
            for(int j=0;j<2;j++)
                printf("%lld ",a[i][j]);
        pn;
    }
}one,f[maxn];
int n,ans;
int a[maxn];
int s1(int x)
{
    return x*(x+1)%mod*499122177%mod;
}
int s2(int x)
{
    return x*(x+1)%mod*(2*x+1)%mod*166374059%mod;
}
int s3(int x)
{
    return s1(x)*s1(x)%mod;
}
void upd(int &x,int y)
{
    x+=y;
    if(x>=mod)x-=mod;
    if(x<0)x+=mod;
}
signed main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    #endif
    one.a[0][0]=one.a[1][1]=1;
    n=re();
    for(int i=1;i<=n;i++)
        a[i]=re();
    a[0]=a[n];
    f[n]=one;
    for(int i=n-1;i;i--)
    {
        Matrix t;
        t.a[0][0]=s1(a[i]);
        t.a[1][0]=a[i]+1;
        t.a[0][1]=(a[i]*s1(a[i])-s2(a[i])+mod)%mod;
        t.a[1][1]=s1(a[i]);
        f[i]=t*f[i+1];
    }
    Matrix now=one;
    for(int i=0;i<n;i++)
    {
        Matrix t;
        t.a[0][0]=(a[i]*a[i+1]%mod*(a[i]+!i)+(a[i]-a[i+1]+mod)*s1(a[i])-s2(a[i])+mod)%mod;
        t.a[1][0]=((a[i]+!i)*a[i+1]+s1(a[i]))%mod;
        t.a[0][1]=(a[i]*a[i+1]%mod*s1(a[i])+(a[i]-a[i+1]+mod)*s2(a[i])-s3(a[i])+mod)%mod;
        t.a[1][1]=(a[i+1]*s1(a[i])+s2(a[i]))%mod;
        if(i==n-1)
        {
            for(int j=n-2;j;j--)
            {
                Matrix t2;
                t2.a[0][0]=s1(a[j]-1);
                t2.a[1][0]=a[j];
                t2.a[0][1]=(a[j]*s1(a[j])-s2(a[j])+mod)%mod;
                t2.a[1][1]=s1(a[j]);
                t=t2*t;
            }
        }
        else
            t=f[i+2]*now*t;
        upd(ans,t.a[0][0]);
        t.a[0][0]=s1(a[i]-!!i);
        t.a[1][0]=a[i]+!i;
        t.a[0][1]=(a[i]*s1(a[i])-s2(a[i])+mod)%mod;
        t.a[1][1]=s1(a[i]);
        now=now*t;
    }
    printf("%lld",ans);
    return 0;
}
```

---

