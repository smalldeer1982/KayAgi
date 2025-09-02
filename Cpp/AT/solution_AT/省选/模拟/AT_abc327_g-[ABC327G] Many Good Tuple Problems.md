# [ABC327G] Many Good Tuple Problems

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc327/tasks/abc327_g

> この問題における良い数列の組の定義は D 問題と同じです。

$ N $ 以下の正整数からなる長さ $ M $ の数列の組 $ (S,\ T)\ =\ ((S_1,\ S_2,\ \dots,\ S_M),\ (T_1,\ T_2,\ \dots,\ T_M)) $ が **良い数列の組である** とは、$ (S,\ T) $ が次の条件を満たすことを言います。

- $ 0,1 $ からなる長さ $ N $ の数列 $ X\ =\ (X_1,\ X_2,\ \dots,\ X_N) $ であって次の条件を満たすものが存在する。
  - $ i=1,\ 2,\ \dots,\ M $ それぞれについて、$ X_{S_i}\ \neq\ X_{T_i} $ が成立する。
 
$ N $ 以下の正整数からなる長さ $ M $ の数列の組 $ (A,\ B)\ =\ ((A_1,\ A_2,\ \dots,\ A_M),\ (B_1,\ B_2,\ \dots,\ B_M)) $ としてあり得るものは $ N^{2M} $ 通りありますが、そのような数列の組のうち良い数列の組であるものの個数を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 30 $
- $ 1\ \leq\ M\ \leq\ 10^9 $
- $ N,\ M $ は整数
 
### Sample Explanation 1

例えば $ A=(1,2),\ B=(2,3) $ のとき $ (A,\ B) $ は良い数列の組です。$ X=(0,1,0) $ とすると、$ X $ は $ 0,1 $ からなる長さ $ N $ の数列で、 $ X_{A_1}\ \neq\ X_{B_1} $ かつ $ X_{A_2}\ \neq\ X_{B_2} $ を満たします。よって、$ (A,B) $ は良い数列の組としての条件を満たしています。 良い数列の組は全部で $ 36 $ 個あるので、これを出力します。

## 样例 #1

### 输入

```
3 2```

### 输出

```
36```

## 样例 #2

### 输入

```
3 3```

### 输出

```
168```

## 样例 #3

### 输入

```
12 34```

### 输出

```
539029838```

## 样例 #4

### 输入

```
20 231104```

### 输出

```
966200489```

# 题解

## 作者：teylnol_evteyl (赞：8)

赛时想到大致思路，但同一个图存在不同染色方式的情况没有处理好，导致最后两个样例过不去。

答案为 $n$ 个点 $m$ 条边（可能有重边）代标号二分图个数乘以 $2^m$，因为每条边可以有两种方向。

设 $G_{n,m}$ 表示 $n$ 个点、$m$ 条边简单二分图的个数，**染色方式不同算多种**，枚举左边点的个数 $i$，则最多有 $i(n-i)$ 条边，所以

$$G_{n,m}=\sum_{i=0}^nC_n^iC_{i(n-i)}^m$$

设 $F_{n,m}$ 表示 $n$ 个点、$m$ 条边简单**连通**二分图的个数，染色方式不同算多种（显然有且只有两种染色方式），考虑容斥，总方案减去不合法方案，可以枚举编号为 $1$ 的点所在连通块大小及边数，则

$$F_{n,m}=G_{n,m}-\sum_{i,j}C_{n-1}^{i-1}F_{i,j}G_{n-i,m-j}$$

边界为 $F_{1,0}=1$。

设 $H_{n,m}$ 表示 $n$ 个点、$m$ 条边简单二分图的个数，染色方式不同算一种，则枚举 $1$ 所在连通块的大小及边数转移，由于每种连通二分图在 $F$ 中被计算了两次，需要除以 $2$，所以

$$H_{n,m}=\dfrac{\sum_{i,j}C_{n-1}^{i-1}F_{i,j}H_{n-i,m-j}}{2}$$

边界为 $H_{0,0}=1$。

最后枚举去重后的边数 $m'$，则对答案的贡献为 $H_{n,m'}$ 乘以长度为 $m$、不同元素个数为 $m'$ 的序列数量，即 $m$ 个小球装进 $m'$ 个盒子里没有空盒的方案数，根据容斥原理，枚举空盒数量 $i$，所以这个问题的答案为

$$\sum_{i=0}^{m'-1}(-1)^iC_{m'}^i(m'-i)^m$$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 35, M = 230, P = 998244353, INV2 = (P + 1) / 2;

int n, m;
LL c[M][M], g[N][M], f[N][M], h[N][M];

inline LL ksm(LL a, LL n)
{
	LL res = 1;
	while(n)
	{
		if(n & 1) res = res * a % P;
		a = a * a % P;
		n >>= 1;
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	
	for(int i = 0; i < M; i ++ )
	{
		c[i][0] = 1;
		for(int j = 1; j <= i; j ++ ) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
	}
	
	for(int i = 1; i <= n; i ++ )
		for(int j = 0; j <= n; j ++ )
			for(int k = 0; k <= j * (i - j); k ++ )
				g[i][k] = (g[i][k] + c[i][j] * c[j * (i - j)][k]) % P;
	
	f[1][0] = 2;
	for(int i = 2; i <= n; i ++ )
		for(int j = i - 1; j <= i * i / 4; j ++ )
		{
			f[i][j] = g[i][j];
			for(int k = 1; k <= i; k ++ )
				for(int l = k - 1; l <= min(k * k / 4, j); l ++ )
					f[i][j] = (f[i][j] - c[i - 1][k - 1] * f[k][l] % P * g[i - k][j - l] % P + P) % P;
		}
	
	h[0][0] = 1;
	for(int i = 1; i <= n; i ++ )
		for(int j = 0; j <= i * i / 4; j ++ )
			for(int k = 1; k <= i; k ++ )
				for(int l = k - 1; l <= min(k * k / 4, j); l ++ )
					h[i][j] = (h[i][j] + c[i - 1][k - 1] * h[i - k][j - l] % P * f[k][l] % P * INV2) % P;
	
	LL res = 0;
	for(int i = 1; i <= n * n / 4; i ++ )
		for(int j = 0, x = 1; j < i; j ++ , x = -x)
			res = (res + h[n][i] * c[i][j] % P * ksm(i - j, m) % P * x + P) % P;
	
	printf("%lld\n", res * ksm(2, m) % P);
	return 0;
}
```

---

## 作者：vegetable_king (赞：8)

[可能更好的阅读体验](https://yjh965.github.io/post/abc327g-many-good-tuple-problems-ti-jie/)

这能红？

首先发现重边是没有影响的，且边的端点顺序不重要，所以考虑求出有 $i$ 个点 $j$ 条边的简单二分图个数 $f_{i, j}$，则答案为 $2^m \sum_{i = 0}^{L(n)} {m \brace i} f_{n, i} i!$，可以 $O(n^4 \log m)$ 计算，其中 $L(n) = \lfloor \frac n2 \rfloor \lceil \frac n2 \rceil$，即 $n$ 个点的二分图的最大可能边数。

至于计算 $f_{i, j}$，由于我们不关心二分图的染色情况，所以为了避免重复计数，我们钦定：对于每个连通块，编号最小的点染成白色。如果对染色的角度考虑的话是不好计数的，所以我们对连通的二分图进行计数，最后再将连通块拼起来。即设 $g_{i, j}$ 为有 $i$ 个点 $j$ 条边的简单连通二分图个数，枚举 $1$ 号点所在的连通块大小及边数，则有：
$$
f_{i, j} = g_{i, j} + \sum_{k = 1}^{i - 1} \sum_{l = 0}^j \binom{i - 1}{k - 1} g_{k, l} f_{i - k, j - l}
$$
计算 $g_{i, j}$ 可以使用类似[有标号无向连通图计数](https://www.luogu.com.cn/problem/P4841)的思想进行容斥，枚举 $1$ 号点所在的连通块大小及边数，则有：
$$
g_{i, j} = h_{i, j} - \sum_{k = 1}^{i - 1} \sum_{l = 0}^j 2\binom{i - 1}{k - 1} g_{k, l} h_{i - k, j - l}
$$
因为剩下一部分的二分图可以选择令最小标号点与 $1$ 染成同色 / 异色。

其中 $h_{i, j}$ 为有 $i$ 个点 $j$ 条边，满足连通图的染色条件（即 $1$ 染成白色），但是不一定连通的简单连通二分图个数，枚举与 $1$ 号点同色的点个数 $x$，有：
$$
h_{i, j} = \sum_{x = 1}^i \binom{i - 1}{x - 1} \binom{x(i - x)}{j}
$$
时间复杂度为 $O(n^6 + n^4 \log m)$，常数很小可以通过。

---

## 作者：Lgx_Q (赞：3)

~~为什么我的做法每次都和别人不一样啊~~

重边是没有用的，我们只需要记录使用的边的集合。

考虑一张图，他是二分图当且仅当他能被黑白染色。

从黑白染色的角度入手，我们尝试**利用 $\text{BFS}$ 进行 $\text{DP}$**。

考虑一个连通块，从**编号最小的点**开始搜索，设 $g[i,j,k]$ 为 $i$ 个点的连通块，边集大小为 $j$，$\text{BFS}$ 过程中最后一层有 $k$ 个点。

枚举下一层有 $x$ 个点，用了 $y$ 条边。设 $h[i,j,k]$ 表示一层点数为 $i$，边集大小为 $j$，上一层点数为 $k$ 的方案数。那么 

$$g[i,j,k]\times h[x,y,k]\times {i+x-1\choose x}\rightarrow g[i+x,j+y,x]$$

考虑求 $h[i,j,k]$，按每个点与上一层连得边数分成若干个等价类，背包转移。

枚举连得边数 $p$，一共有 $r$ 个这样的点，那么

$$h[i,j,k]\leftarrow h[i-r,j-p\times r,k]\times {k\choose p}^r\times {i\choose r}$$

设 $f[i,j]$ 表示 $i$ 个点，边集大小为 $j$ 的方案数，相当于分成若干个连通块，每个连通块用 $g$ 转移即可。

最后对于 $f[n,i]$，他对答案的贡献是 $S(m,i)\times i!$，其中 $S(m,i)$ 是第二类斯特林数。

时间复杂度 $O(n^5\log n+n^7)$，常数很小，可以通过。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=35, mod=998244353;
ll n,m,f[maxn][maxn*maxn],s[maxn][maxn*maxn],g[maxn][maxn*maxn][maxn],pw[maxn][maxn],c[maxn*maxn][maxn*maxn],fc;
ll ans,h[maxn][maxn*maxn][maxn],t[maxn*maxn];
ll power(ll a,ll b)
{
	ll s=1;
	while(b)
	{
		if(b&1) s=s*a%mod;
		a=a*a%mod; b>>=1;
	}
	return s;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	c[0][0]=1;
	ll M=n*n; M=min(M,m);
	for(ll i=1;i<=M||i<=n;i++)
	{
		c[i][0]=1;
		for(ll j=1;j<=i;j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	for(ll i=1;i<=n;i++) h[0][0][i]=1;
	for(ll p=1;p<=M&&p<=n;p++)
		for(ll i=n;i;i--)
			for(ll j=p;j<=M;j++)
			{
				for(ll k=p;k<=n&&i+k<=n;k++)
				{
					ll y=c[k][p];
					for(ll x=1;x<=i&&p*x<=j;x++)
					{
						h[i][j][k]=(h[i][j][k]+h[i-x][j-p*x][k]*c[i][x]%mod*y)%mod;
						y=y*c[k][p]%mod;
					}
				}
			}
	g[1][0][1]=1;
	for(ll i=1;i<=n;i++)
	{
		for(ll j=0;j<=M;j++)
		{
			for(ll k=1;k<=i;k++)
			{
				if(!g[i][j][k]) continue;
				for(ll x=1;i+x<=n;x++)
					for(ll y=x;j+y<=M;y++)
					{
						g[i+x][j+y][x]=(g[i+x][j+y][x]+g[i][j][k]*h[x][y][k]%mod*c[i+x-1][x])%mod;
					}
//				printf("g[%lld,%lld,%lld] = %lld\n",i,j,k,g[i][j][k]);
				s[i][j]=(s[i][j]+g[i][j][k])%mod;
			}
			//printf("s[%lld,%lld] = %lld\n",i,j,s[i][j]);
		}
	}
	f[0][0]=1;
	for(ll i=1;i<=n;i++)
		for(ll j=0;j<=M;j++)
			for(ll k=1;k<=i;k++)
				for(ll x=0;x<=j;x++)
					f[i][j]=(f[i][j]+f[i-k][j-x]*s[k][x]%mod*c[i-1][k-1])%mod;
	for(ll i=1;i<=M;i++)
	{
		for(ll j=1;j<=i;j++)
			t[i]=(t[i]+((i-j)&1? mod-1:1)*power(j,m)%mod*c[i][j])%mod;
		ans=(ans+f[n][i]*t[i])%mod;
	}
	printf("%lld",ans*power(2,m)%mod);
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：3)

## 题意

对于一对长度均为 $M$ 且元素值在 $\left[1, N\right]$ 之间的序列 $(S, T)$，定义其为好的当且仅当：

- 存在一个长度为 $N$ 的 $01$ 序列 $X$，使得其满足如下条件：

    - 对于任意 $i \in \left[1, M\right]$，有 $X_{S_i} \neq X_{T_i}$。

给定 $N, M$，求在所有可能的 $N^{2M}$ 种长度均为 $M$ 且元素值在 $\left[1, N\right]$ 之间的序列对 $(A, B)$ 中，有多少对序列是好的。

对 $998244353$ 取模。

$1 \le N \le 30, 1 \le M \le 10^9$。

## 题解

发现对于所有的 $i \in \left[1, M\right]$，可以建边 $(S_i, T_i)$。其中每一条边均代表着其连接的两个顶点的 $X$ 值不能相同。由于 $X_i$ 的取值只有两种，那么一个对序列合法当且仅当其建出的图为二分图。

所以我们可以对 $N$ 个点，$M$ 条边的二分图进行计数，设其为 $a(N, M)$。由于一条边 $(u, v)$ 可以对应 $(S_i, T_i)$ 或 $(T_i, S_i)$，所以最终答案即为 $a(N, M) \times 2^M$。

发现由 $N$ 个点组成的二分图最多有 $\left\lfloor\frac{N}{2}\right\rfloor \times \left\lceil\frac{N}{2}\right\rceil$ 种本质不同的边，设其为 $L$。那么我们可以将 $M$ 条边进行分类，设 $b(M, k)$ 代表将 $M$ 条相互区分的边划分为 $k$ 个相互区分的集合的方案数，$f(n, k)$ 代表 $n$ 个点，$k$ 条本质不同的边的二分图数量，那么有

$$a(N, M) = \sum\limits_{k = 0}^{L} b(M, k) \times f(N, k)$$

---

下面考虑如何求出 $b(M, k)$ 的值，根据斯特林数的定义，有

$$b(M, k) = {M \brace k} k!$$

考虑斯特林数的通项公式

$${n \brace m} = \sum\limits_{i = 0}^{m} \dfrac{\left(-1\right)^{m - i} i^n}{i! \times (m - i)!}$$

将其代入，有

$$\begin{aligned}
b(M, k) &= {M \brace k} k! \\
&= \sum\limits_{i = 0}^{k} \dfrac{\left(-1\right)^{k - i} i^M}{i! \times (k - i)!} \times k! \\
&= \sum\limits_{i = 0}^{k} \left(-1\right)^{k - i} \dbinom{k}{i} i^M
\end{aligned}$$

通过预处理组合数，我们可以在 $\mathcal{O}(N^4 \log M)$ 的复杂度内计算出 $b(M, 0), b(M, 1), b(M, 2), \cdots, b(M, L)$ 的值。

---

下面我们考虑如何求出 $f(N, k)$ 的值，考虑应用容斥 $\tt{DP}$。

设 $g(n, m)$ 代表将 $n$ 个点黑白染色后，存在 $m$ 条本质不同的边使得每个边连接的两个顶点颜色均不同的方案数，通过枚举白色点的数量，我们有

$$g(n, m) = \sum\limits_{i = 0}^{n} \dbinom{n}{i} \dbinom{i \times \left(n - i\right)}{m}$$

发现我们不能通过 $g$ 的值计算出 $f$ 的值，原因为在 $g$ 的计算中，每一个联通块都会被重复计算两次（考虑钦定每个联通块编号最小的点的颜色为黑色或白色），而 $g(n, m)$ 中计算了多少个联通快是不便于计算的，因此我们需要计算出将 $n$ 个点黑白染色后，存在 $m$ 条本质不同的边使得每个边连接的两个顶点颜色均不同**且使得图联通**的方案数，设其为 $h(n, m)$。

考虑如何计算其值，我们可以考虑容斥掉 $g(n, m)$ 中的不合法情况，若存在图使得其不合法，那么其一定存在多于一个联通块，也就是说 $1$ 号节点所在的联通块大小不为 $n$。可以发现，$1$ 号节点所在的联通块大小等于 $n$ 与图联通为充要条件。因此我们可以通过枚举 $1$ 号节点所在联通块的大小来计算不合法情况的方案数，有

$$h(n, m) = g(n, m) - \sum\limits_{i = 1}^{n - 1}\sum\limits_{j = 0}^{m} \dbinom{n - 1}{i - 1}h(i, j)g(n - i, m - j)$$

发现对于一个图，因为 $1$ 号节点的颜色不确定，所以其在 $h(n, m)$ 的中会被计算两次。

下面考虑如何计算 $f(n, m)$，发现若图不联通，我们可以通过枚举 $1$ 号节点所在联通块的大小完成计算，有

$$f(n,m) = \dfrac{h(n,m)}{2} + \sum\limits_{1 \le i < n}\sum\limits_{0 \le j \le m}\dbinom{n-1}{i-1}\dfrac{h(i, j)}{2}f(n -i, m - j)$$

至此我们以 $\mathcal{O}(N^6)$ 的复杂度完成了 $f(N, k), k \in \left[0, L\right]$ 的计算。

---

总复杂度为 $\mathcal{O}(N^6 + N^4 \log M)$，可以通过。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

namespace MODINT {
    constexpr valueType MOD = 998244353;

    template<typename T1, typename T2, typename T3 = valueType>
    void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a + b;

        if (a >= mod)
            a -= mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
        a = a - b;

        if (a < 0)
            a += mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
        return a + b >= mod ? a + b - mod : a + b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
        return a - b < 0 ? a - b + mod : a - b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
        return (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
        a = (long long) a * b % mod;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
        T1 result = 1;

        while (b > 0) {
            if (b & 1)
                Mul(result, a, mod);

            Mul(a, a, mod);
            b = b >> 1;
        }

        return result;
    }
}// namespace MODINT

using namespace MODINT;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    valueType const L = (N / 2) * ((N + 1) / 2), S = L + 100;

    ValueMatrix C(S + 1, ValueVector(S + 1, 0));

    C[0][0] = 1;
    for (valueType i = 1; i <= S; ++i) {
        C[i][0] = 1;

        for (valueType j = 1; j <= i; ++j)
            C[i][j] = sum(C[i - 1][j - 1], C[i - 1][j]);
    }

    ValueVector divideCount(L + 1, 0);

    for (valueType k = 0; k <= L; ++k) {
        divideCount[k] = 0;

        for (valueType i = 0; i <= k; ++i) {
            if ((k - i) & 1)
                Dec(divideCount[k], mul(C[k][i], pow(i, M)));
            else
                Inc(divideCount[k], mul(C[k][i], pow(i, M)));
        }
    }

    ValueMatrix F(N + 1, ValueVector(L + 1, 0)), G(N + 1, ValueVector(L + 1, 0)), H(N + 1, ValueVector(L + 1, 0));

    // calc G
    for (valueType n = 1; n <= N; ++n)
        for (valueType m = 0; m <= L; ++m)
            for (valueType i = 0; i <= n; ++i)
                Inc(G[n][m], mul(C[n][i], C[i * (n - i)][m]));

    // calc H
    for (valueType n = 1; n <= N; ++n) {
        for (valueType m = 0; m <= L; ++m) {
            H[n][m] = G[n][m];

            for (valueType i = 1; i < n; ++i)
                for (valueType j = 0; j <= m; ++j)
                    Dec(H[n][m], mul(C[n - 1][i - 1], mul(H[i][j], G[n - i][m - j])));
        }
    }

    constexpr valueType Inv2 = (MOD + 1) / 2;

    for (auto &h : H)
        for (auto &iter : h)
            Mul(iter, Inv2);

    // calc F
    for (valueType n = 1; n <= N; ++n) {
        for (valueType m = 0; m <= L; ++m) {
            F[n][m] = H[n][m];

            for (valueType i = 1; i < n; ++i)
                for (valueType j = 0; j <= m; ++j)
                    Inc(F[n][m], mul(C[n - 1][i - 1], mul(H[i][j], F[n - i][m - j])));
        }
    }

    valueType ans = 0;

    for (valueType i = 0; i <= L; ++i)
        Inc(ans, mul(F[N][i], divideCount[i]));

    Mul(ans, pow(2, M));

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：ckain (赞：2)

图计数．

先考虑对简单（没有重边的）二分图计数．以下二分图均指简单二分图．

设 $f_{n, m}$ 表示有 $n$ 个点，$m$ 条边的二分图个数．

思考黑白染色，不妨先尝试写出可能重复的统计方法：将 $n$ 个点划分成黑白两部分，然后在黑白之间中选出 $m$ 条边连接．会有结果为

$$
\sum_{i=0}^{n} \binom{n}{i}\binom{i(n-i)}{m}
$$

但它存在重复．当一张二分图上存在 $k$ 个联通块时，其每个联通块都存在 $2$ 种不同的染色方案，它被统计了 $2^k$ 次．我们不妨将这种二分图黑白染色方案数记为 $g_{n, m}$．

考虑图计数的经典手段，就是枚举一个钦定点所在的联通块．不妨设 $h_{n, m}$ 为 $n$ 个点 $m$ 条边的连通二分图黑白染色方案数，它等于二分图个数 $\times 2$．有

$$
h_{n, m}=g_{n, m}-\sum_{i=1}^{n-1}\binom{n-1}{i-1}\sum_{j=0}^{min(m, i(i-1)/2)}h_{i, j}g_{n-i, m-j}
$$

有了这个，我们同理可以写出 $f_{n, m}$ 的转移式

$$
f_{n, m}=h_{n, m}/2+\sum_{i=1}^{n-1}\binom{n-1}{i-1}\sum_{j=0}^{min(m, i(i-1)/2)}h_{i, j}f_{n-i, m-j}/2
$$

现在考虑如何求出答案．设 $c_{x, y}$ 为将 $x$ 带标号小球放入 $y$ 个带标号的碗里，要求碗非空的方案数．则题目所求的答案为

$$
2^M\sum_{i=0}^{N(N-1)/2}f_{N, i}c_{M, i}
$$

$2^M$ 怎么来的？因为 $(A_i, B_i)$ 是有序对．

那么现在我们关心 $c_{x, y}$ 怎么求．我们有

$$
y^x=\sum_{i=1}^{y}\binom{y}{i}c_{x, i}
$$

根据二项式反演有

$$
c_{x, y}=\sum_{i=1}^{y}(-1)^{y-i}\binom{y}{i}i^x
$$

至此我们做完了．所有转移和系数处理全部暴力循环实现．总时间复杂度为 $O(n^6)$．可以通过本题．


code:

```cpp
#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define int long long
using namespace std;

inline int rd(){
	int s=0, f=1; char c=getchar();
	while(!isdigit(c)) f^=(c=='-'), c=getchar();
	while(isdigit(c)) s=s*10+c-'0', c=getchar();
	return f? s:-s;
}

void wt(int x, char c=0){
	if(x<0) return putchar('-'), wt(-x, c);
	if(x>9) wt(x/10); putchar(x%10+'0');
	if(c) putchar(c);
}

const int N=31, M=N*N, Mod=998244353, inv2=499122177;

int n, m, C[M][M], h[N][M], g[N][M], f[N][M];

inline int qpow(int a, int b){
	int re=1; for(; b; b>>=1, a=a*a%Mod) if(b&1) re=re*a%Mod;
	return re;
}

inline int coef(int y){
	int re=0;
	for(int i=1; i<=y; i++){
		re+=(y-i&1? Mod-1:1)*C[y][i]%Mod*qpow(i, m)%Mod;
		re%=Mod;
	}
	return re;
}

signed main(){
	n=rd(), m=rd();
	
	C[0][0]=1;
	for(int i=1; i<=n*n; i++){
		C[i][0]=1;
		for(int j=1; j<=i; j++){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
		}
	}
	
	for(int i=1; i<=n; i++){
		for(int j=0; j<=i*(i-1)/2; j++){
			for(int k=0; k<=i; k++){
				g[i][j]+=C[i][k]*C[k*(i-k)][j]%Mod;
				g[i][j]%=Mod;
			}
		}
	}
	
	for(int i=1; i<=n; i++){
		for(int j=0; j<=i*(i-1)/2; j++){
			h[i][j]=g[i][j];
			for(int k=1; k<i; k++){
				for(int l=0; l<=min(j, k*(k-1)/2); l++){
					h[i][j]+=Mod-C[i-1][k-1]*h[k][l]%Mod*g[i-k][j-l]%Mod;
					h[i][j]%=Mod;
				}
			}
		}
	}
	
	for(int i=1; i<=n; i++){
		for(int j=0; j<=i*(i-1)/2; j++){
			f[i][j]=h[i][j]*inv2%Mod;
			for(int k=1; k<i; k++){
				for(int l=0; l<=min(j, k*(k-1)/2); l++){
					f[i][j]+=C[i-1][k-1]*h[k][l]%Mod*inv2%Mod*f[i-k][j-l]%Mod;
					f[i][j]%=Mod;
				}
			}
		}
	}
	
	int ans=0;
	
	for(int i=1; i<=n*(n-1)/2; i++){
		ans+=coef(i)*f[n][i]%Mod;
		ans%=Mod;
	}
	
	wt(ans*qpow(2, m)%Mod, '\n');
	return 0;
}
```

---

## 作者：Judgelight (赞：2)

考虑最终把连出的边去重之后得到的应该是一个二分图，不妨设 $f(n,m)$ 表示 $n$ 个节点 $m$ 条没有重边（显然不能有自环）的边的二分图方案数，则

$$ans=2^m\sum\limits_{i=0}\limits^{\frac{n(n-1)}{2}}f(n,i)s_2(m,i)m!$$

$2^m$ 的系数是因为边 $u\rightarrow v$ 可以写成 $(u,v)$ 也可以写成 $(v,u)$（由于没有重边所以 $u,v$ 不同）。而后面那个是球不同盒子不同盒子不空的方案数，其中 $s2(m,i)$ 表示第二类斯特林数。

考虑 $f(n,m)$ 不好算的原因是因为有多个连通块染色方法不唯一，那么如果能用染色法表示单一连通块的方案数就能推出 $f$ 了。

设 $h(n,m)$ 表示 $n$ 个点 $m$ 条边的所有图的所有染色方案之和，则 $h(n,m)=\sum\limits_{i=0}\limits^{n}C_{n}^{i}C_{i(n-i)}^{m}$，务必注意 $f$ 与 $h$ 的差别。

设 $g(n,m)$ 表示 $n$ 个点 $m$ 条边的所有**连通**图的所有染色方案之和，则 $g(n,m)=h(n,m)-\sum\limits_{i=1}\limits^{n-1}\sum\limits_{j=0}\limits^{m}C_{n}^{i}g(i,j)h(n-i,m-j)$，注意到由于这是一个连通块，所以每个二分图对应恰好两种染色方案，即有 $\frac{g(n,m)}{2}$ 个 $n$ 个点 $m$ 条边的连通二分图。

那么现在就有 $f(n,m)=\frac{g(n,m)}{2}+\sum\limits_{i=1}\limits^{n-1}\sum\limits_{j=0}\limits^{m}\frac{g(i,j)}{2}f(n-i,m-j)$。

那么最终复杂度为 $O(n^6+n^4\log n)$。

---

## 作者：Purslane (赞：1)

# Solution

发现自己一点不会数数啊。那就写一篇题解来增长一点水平。

很明显，我们把问题转化为求 $n$ 个点 $m$ 条边的二分图个数。其中边**区分顺序**，点**区分编号**。（最后答案要乘上 $2^m$ 因为每条边有两种方向。）这个问题中，二分图不一定是简单图，可能有重边，但是当然没有自环。假设答案是 $f(n,m)$。

非简单图不具有简单图的性质。于是我们尝试计算 $n$ 个点 $m$ 条边的二分图个数，边**不区分顺序**（其实这里无所谓，因为没有重边，要区分顺序乘上 $m!$ 即可），点区分编号。设答案是 $g(n,m)$。

我们先考虑 $f$ 和 $g$ 的关系。很容易写出这个式子：

$$f(n,m)=\sum_{i=1}^{m} k(m,i) \times g(n,i)$$

其中 $k(m,i)$ 表示把 $m$ 条边分配给 $i$ 个集合，每个集合至少有一个元素的方案数。这个可以使用二项式反演来计算。考虑如果把 $m$ 条边分给 $i$ 个集合不要求所有集合非空的方案数是 $i^m$，那么可以求出：

$$k(m,i) = \sum_{j=1}^i (-1)^{i-j} C_i^j \times j^m$$

你可能会说，这个 $m$ 很大，根本枚举不动啊！但是我们发现，$n$ 个点的简单图最多有 $\frac{n(n+1)}{2}$ 条边，也就是 $i \ge \frac{n(n+1)}{2}$ 的时候根本不需要算。

好的，现在压力来到了求 $g$ 上面。

这个二分图可能不连通对不对，于是我们来求 $n$ 个点 $m$ 条边的有标号的联通二分图个数。设这样的答案是 $h(n,m)$。

首先，我们可以先把节点们黑白染色。然后我们可以知道如果不管啥连通性的话，可以枚举白色点的数量，得到

$$\sum_{i=0}^n C_n^i \times C_{i(n-i)}^m$$

> 关于这个东西为啥不能直接用来求 $g$：其实从本场的 D 题你可以看出，一个二分图可能对应很多种染色方式，到底有多少种其实由其连通块数量决定。而你在求出这个东西的时候你并不知道到底有多少个连通块，也就很难直接删掉重复的情况。但是如果你求出了只有一个连通块的情况，那么就可以进行拼接，这个过程中你就可以拿捏有几个连通块了。

考虑删掉其中不是连通块的情况。我们先记上式为 $p(n,m)$。

对于不是连通块的情形，有一个经典套路就是枚举 $1$ 所在连通块大小。那么很简单啊，可以写出

$$h(n,m)=p(n,m) - \sum_{i=1}^{n-1} C_{n-1}^{i-1} \sum_{j=0}^m h(i,j) \times p(n-i,m-j)$$

感觉很对啊！但是你发现，一个整的连通块的染色其实还是有两种情况的。因此实际上 $n$ 个点 $m$ 条边的有标号联通二分图个数为 $\frac{h(n,m)}{2}$，方便期间我们记为 $q(n,m)$。

然后考虑拼接出 $g(n,m)$。还是一样的套路，我们枚举 $1$ 所在连通块的大小。写出式子

$$g(n,m) = q(n,m) + \sum_{i=1}^{n-1} C_{n-1}^{i-1} \sum_{j=0}^m q(i,j) \times g(n-i,m-j)$$

然后分析一下复杂度。求这些函数的复杂度分别是：

- $f$：$O(n^2)$；
- $g$：$O(n^6)$；
- $k$：$O(n^4 \log m)$；（要快速幂）
- $p$：$O(n^4)$；
- $h$ 和 $q$：$O(n^6)$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3000+10,MAXM=3000+10,MOD=998244353;
int n,mx,m,g[MAXM][MAXM],h[MAXM][MAXM],C[MAXM][MAXM],p[MAXM][MAXM];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int calc_C(int u,int d) {
	int res=1;
	ffor(i,d-u+1,d) res=res*i%MOD;
	ffor(i,1,u) res=res*qpow(i,MOD-2)%MOD;
	return res;	
}
int k(int m,int i) {
	int ans=0;
	ffor(j,1,i) {
		if((i-j)%2==0) ans=(ans+calc_C(j,i)*qpow(j,m))%MOD;
		else ans=(ans-calc_C(j,i)*qpow(j,m))%MOD;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m,mx=n*(n+1)/2;
	C[0][0]=1;
	ffor(i,1,mx) {C[i][0]=1;ffor(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;}
	ffor(i,1,n) ffor(j,0,mx) ffor(k,0,i) p[i][j]=(p[i][j]+C[i][k]*C[k*(i-k)][j])%MOD;
	ffor(i,1,n) ffor(j,0,mx) {
		h[i][j]=p[i][j];
		ffor(k,1,i-1) ffor(s,0,j) h[i][j]=(h[i][j]-C[i-1][k-1]*h[k][s]%MOD*p[i-k][j-s]%MOD)%MOD;
	}
	ffor(i,1,n) ffor(j,0,mx) h[i][j]=(h[i][j]*(MOD+1)/2)%MOD;
	ffor(i,1,n) ffor(j,0,mx) {
		g[i][j]=h[i][j];
		ffor(k,1,n-1) ffor(s,0,j) g[i][j]=(g[i][j]+C[i-1][k-1]*h[k][s]%MOD*g[i-k][j-s]%MOD)%MOD;
	}
	int res=0;
	ffor(i,1,min(m,mx)) res=(res+k(m,i)*g[n][i])%MOD;
	res=(res%MOD+MOD)%MOD;
	cout<<res*qpow(2,m)%MOD;
	return 0;
}
```

已经做不出 NOIp T2 难度的题了 /cf /ll /dk

---

## 作者：daniEl_lElE (赞：0)

不难发现符合要求等价于连边后是二分图。考虑将二分图染色。

考虑计算出图最终最多被分为 $i$ 个二分图子图的方案数 $f_i$。

考虑容斥，设 $g_i$ 为图被分为 $i$ 个二分图子图的方案数。

考虑 $dp_{i,j,k}$ 表示目前用了 $i$ 个点，有 $j$ 条边可以被连，目前分为 $k$ 个连通块。

转移的时候枚举新连通块有多少黑/白点，注意当黑/白点数相等时不应乘 $2$。

计算完 $dp_{n,j,k}$ 后，$g_k=\sum_{j=1}^{n^2}dp_{n,j,k}\times(2j)^m$，其中 $(2j)^m$ 表示选边的方案数。

最后考虑容斥，直接容斥不能计算出 $f_i$。考虑预处理容斥系数，设 $pre_{i,j}$ 表示将 $i$ 部分合并成 $j$ 部分的方案数。由于 dp 时已经确定每个点事黑还是白了，$pre_{i,j}$ 直接枚举下一个合并部分并拼上转移即可。

最终，$f_i=g_i-\sum_{j=i+1}^{n}f_j\times pre_{j,i}$。

最终答案由于是不需要染色的，故 $ans=\sum_{i=1}^nf_i\frac{1}{2^i}$。

总复杂度 $O(n^6+n^3\log m)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int dp[35][905][35],f[35],C[35][35],pre[35][35][35];
signed main(){
	for(int i=0;i<=30;i++) C[i][0]=1;
	for(int i=1;i<=30;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	for(int i=1;i<=30;i++){
		pre[i][0][0]=1;
		for(int j=0;j<i;j++){
			for(int k=0;k<=i;k++){
				for(int l=1;j+l<=i;l++){
					(pre[i][j+l][k+1]+=pre[i][j][k]*C[j+l-1][j]%mod)%=mod;
				}
			}
		}
	}
	int n,m; cin>>n>>m;
	dp[0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=n*n;j++){
			for(int p=0;p<=n;p++){
				for(int k=0;i+k+k<=n;k++){
					(dp[i+k*2][j+k*k][p+1]+=dp[i][j][p]*C[i+k*2-1][i]%mod*C[k*2][k]%mod)%=mod;
					for(int l=k+1;i+k+l<=n;l++){
						(dp[i+k+l][j+k*l][p+1]+=dp[i][j][p]*C[i+k+l-1][i]%mod*C[k+l][k]*2%mod)%=mod;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n*n;j++){
			(f[i]+=dp[n][j][i]*qp(2*j,m))%=mod; 
		}
	}
	int ans=0;
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++){
			(f[i]+=mod-f[j]*pre[j][j][i]%mod)%=mod;
		}
		(ans+=f[i]*qp((mod+1)/2,i))%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Jryno1 (赞：0)

# ABC327G

虽然是自己做出来的，但是花的时间堪忧。

### 题意

直接说化简后的。

求有多少个 $N$ 个点 $M$ 条边的有标号的无向图，满足其中没有奇环。

$N\le 30,M\le 10^9$。

### Sol

先不考虑重边，那么就是问对于每个连通块都是一个二分图的方案数。此时需要处理这样一个子问题：给定 $n$ 个点和 $m$ 条边有多少种有标号联通二分图的方案。

设 $f_{n,m}$ 表示 $n$ 个点 $m$ 条边黑白染过色（不一定要联通）的二分图个数。有
$$
f_{n,m}=\sum_{i=0}^n \binom{n}{i}\binom{i(n-i)}{m}
$$
之后容斥可以得到 $g_{n,m}$ 表示黑白染过色的联通二分图个数。
$$
g_{n,m}=\sum_{i=1}^{n-1}\sum_{j=0}^m\binom{n-1}{i-1}g_{i,j}f_{n-i,m-j}
$$
由于这是二分染色之后的答案，所以上述子问题的答案就应该是 $\dfrac{g_{n,m}}{2}$。

考虑枚举所有连通块的大小，那么直接背包可以求出来这一种拆分方式用 $x$ 条边的方案数。这个 $x$ 不会很大，因为 $n$ 个点的二分图最多边数只有 $\lfloor \dfrac{n}{2}\rfloor \times \lceil \dfrac{n}{2}\rceil$ 种。之后对于每一个连通块需要分配点，为了避免算重可以把相同大小的连通块拿出来一起算（具体就是对于每一种大小的连通块分别枚举每一个的方案，枚举的时候钦定这一种大小的连通块分配到的最小的点在当前这个连通块中）。最后乘上这个系数即可。

如此可以算出来没有重边的情况下，用了 $m$ 条边的满足要求图的个数。最后考虑重边，显然重边只能和 $m$ 条边相同。相当于用恰好 $m$ 个元素填满 $M$ 个位置的方案数，简单二项式反演一下即可。

预处理 $\mathcal{O}(n^6)$。 注意到 $30$ 的拆分方式并不多（大约 $6000$ 种），枚举 + 背包的时候卡着连通块最多能拥有边数的上限，实际怕跑计算 $4\times 10^6$ 不到。

[ATC 提交记录](https://atcoder.jp/contests/abc327/submissions/47594078)

---

## 作者：Terdy (赞：0)

# ABC327G

## 很考验基础的数学计数题

本蒟蒻在看过了多篇题解后终于明白了其中一种方法。

## Solution

我们连接 $s_i \to t_i$，发现合法的序列等价于图中没有自环和奇数边环，可以有重边，这其实就是一张二分图，我们要求的本质上是 $n$ 个点 $m$ 条边的有标号二分图个数，还要乘以 $2^m$ 给每条边的方向定向。

考虑如何去实现“$n$ 个点 $m$ 条边的有标号二分图个数”这个东西。

设 $G(n,m)$ 表示 $n$ 个点 $m$ 条边简单二分图（没有重边）的个数，不同的染色方案算多种，我们可以枚举左半部分的数量 $i$，那么最多有 $i(n-i)$ 条边，我们可以计算：

$$
G(n,m)= \sum_{i=0}^n \binom{n}{i} \binom{i(n-i)}{m}
$$

继续，设 $F(n,m)$ 表示 $n$ 个点 $m$ 条边简单联通二分图的个数，不同的染色方案算多种，当然有且仅有两种染色方案。考虑容斥，我们用所有的方案减去不联通的方案数，我们枚举 $1$ 号结点联通块的大小 $i$ 以及边数 $j$，我们可以计算：

$$
F(n,m)=G(n,m)-\sum_{i,j} \binom {n-1}{i-1}F(i,j)G(n-i,m-j)
$$

边界为 $F(1,0)=1$。

最后，设 $H(n,m)$ 表示 $n$ 个点 $m$ 条边的简单二分图的个数，不同的染色方案算一种，我们枚举 $1$ 号结点联通块的大小 $i$ 以及边数 $j$，我们可以计算：

$$
H(n,m)=\dfrac{\sum_{i,j} \binom{n-1}{i-1}F(i,j)H(n-i,m-j)}{2}
$$

边界 $H(0,0)=1$。

我们已经算了很多，马上了。其实就差在边数上了。我们枚举去重之后边的数量为 $x$，设 $K(m,x)$ 表示将 $m$ 个不同的小球放进 $x$ 个不同的盒子不为空的方案数，显然可以容斥，我们可以计算：

$$
K(m,x)=\sum_{i=0}^{x-1}(-1)^i\binom{x}{i}(x-i)^m
$$

### 代码

~~~cpp
# include <bits/stdc++.h>

using namespace std;

# define ll long long
# define int ll

const int N = 35 , M = 230 , mod = 998244353 , inv2 = (mod + 1) / 2;
ll n , m , c[M][M] , f[N][M] , g[N][M] , h[N][M] , ans;

int ksm(int a , int b) {int res = 1; for(; b; b >>= 1) {if(b & 1) res = 1ll * res * a % mod; a = 1ll * a * a % mod;} return res;}

signed main()
{
    cin >> n >> m;
    for(int i = 0; i < M; i++)
    {
        c[i][0] = 1;
        for(int j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }

    for(int i = 1; i <= n; i++) for(int j = 0; j <= n; j++) for(int k = 0; k <= j * (i - j); k++)
        g[i][k] = (g[i][k] + c[i][j] * c[j * (i - j)][k] % mod) % mod;
    
    f[1][0] = 2;
    for(int i = 2; i <= n; i++)
    {
        for(int j = i - 1; j <= i * i / 4; j++)
        {
            f[i][j] = g[i][j];
            for(int k = 1; k <= i; k++) for(int l = k - 1; l <= min(k * k / 4 , j); l++)
                f[i][j] = (f[i][j] - c[i - 1][k - 1] * f[k][l] % mod * g[i - k][j - l] % mod + mod) % mod;
        }
    }

    h[0][0] = 1;
    for(int i = 1; i <= n; i++) for(int j = 0; j <= i * i / 4; j++) 
        for(int k = 1; k <= i; k++) for(int l = k - 1; l <= min(k * k / 4 , j); l++)
            h[i][j] = (h[i][j] + c[i - 1][k - 1] * f[k][l] % mod * h[i - k][j - l] % mod * inv2 % mod) % mod; 
    
    for(int i = 1; i <= n * n / 4; i++) 
        for(int j = 0 , o = 1; j < i; j++ , o = -o)
            ans = (ans + h[n][i] * c[i][j] % mod * ksm(i - j , m) % mod * o + mod) % mod;

    cout << ans * ksm(2 , m) % mod;
    return 0;
}
~~~



---

