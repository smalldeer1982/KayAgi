# Student's Camp

## 题目描述

Alex studied well and won the trip to student camp Alushta, located on the seashore.

Unfortunately, it's the period of the strong winds now and there is a chance the camp will be destroyed! Camp building can be represented as the rectangle of $ n+2 $ concrete blocks height and $ m $ blocks width.

Every day there is a breeze blowing from the sea. Each block, except for the blocks of the upper and lower levers, such that there is no block to the left of it is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/422afcf1e06a5628bae49992f52449e3f10a781f.png). Similarly, each night the breeze blows in the direction to the sea. Thus, each block (again, except for the blocks of the upper and lower levers) such that there is no block to the right of it is destroyed with the same probability $ p $ . Note, that blocks of the upper and lower level are indestructible, so there are only $ n·m $ blocks that can be destroyed.

The period of the strong winds will last for $ k $ days and $ k $ nights. If during this period the building will split in at least two connected components, it will collapse and Alex will have to find another place to spend summer.

Find the probability that Alex won't have to look for other opportunities and will be able to spend the summer in this camp.

## 说明/提示

In the first sample, each of the four blocks is destroyed with the probability ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/fda96725ccc697b767e5edbf0d5cfb5ba17d9aa2.png). There are $ 7 $ scenarios that result in building not collapsing, and the probability we are looking for is equal to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/dda8ba13f4feb6c7325a04d07cb771a7084c4ba2.png), so you should print ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/823f9bb4d7539823cd6e4037b4f9a35cb2e52f03.png)

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF708E/2ecb6c84ea76dfa6c7235391533a743f1c25b7f8.png)

## 样例 #1

### 输入

```
2 2
1 2
1
```

### 输出

```
937500007
```

## 样例 #2

### 输入

```
5 1
3 10
1
```

### 输出

```
95964640
```

## 样例 #3

### 输入

```
3 3
1 10
5
```

### 输出

```
927188454
```

# 题解

## 作者：热言热语 (赞：68)

如果题解页面公式崩坏，请 [在博客中查看](/blog/hotwords/solution-cf708e)。

---

首先转化题意。题目中已经限定了最高和最低一行的方块不会被吹走，所以整个建筑「不连通」只可能是被「上下劈开」，不可能是被「左右劈开」。也就是说，整个建筑「连通」，当且仅当对于所有相邻的两行，它们最后剩下的方块连通。

考虑 DP。设 $f(i,l,r)$ 表示第 $i$ 行剩下 $[l,r]$ 的方块且建筑不倒的概率。

先考虑某一行剩下 $[l,r]$ 的方块的概率。

设 $D(i)$ 表示 $k$ 次「吹风」中 $i$ 次成功的概率，显然
$$
D(i) = \binom k i p^i(1-p)^{k-i}
$$

可以 $O(k)$ 预处理求出所有的 $D(i)$。

设 $P(l,r)\ (1 \le l \le r \le m)$ 表示某一行只剩下 $[l,r]$ 的砖块的概率，由于左右两边相互独立，可以得到
$$
P(l,r) = D(l-1) D(m-r)
$$

接下来考虑如何从第 $i-1$ 行转移。

由前面的分析，第 $i$ 行最后剩下的方块所占的区间要和第 $i-1$ 行的区间有交，即
$$
f(i,l,r) = P(l,r) \sum_{[l',r']\cap[l,r] \ne \varnothing} f(i-1,l',r')
$$

边界是 $f(0,1,m) = 1$，答案即为所有 $f(n,l,r)$ 的和。

这样状态数为 $O(nm^2)$，转移复杂度 $O(m^2)$，需要优化。

考虑问题的反面，即 $[l,r]$ 和 $[l',r']$ 没有交集。容易发现，这只有两种互斥的情况：要么 $r' \lt l$，要么 $l' \gt r$。

于是，我们得到：

$$
f(i,l,r) = P(l,r) \left[ \sum_{l' \le r'} f(i-1,l',r') - \sum_{r' \lt l} f(i-1,l',r') - \sum_{l' \gt r} f(i-1,l',r') \right]
$$

发现只要求出三个求和号的部分就能转移了，即

$$
\begin{aligned}
F(i) &= \sum_{l \le r} f(i,l,r) \\
L(i,x) &= \sum_{l \le r \lt x} f(i,l,r) \\
R(i,x) &= \sum_{r \ge l \gt x} f(i,l,r) \\
f(i,l,r) &= P(l,r) \Big[ F(i-1) - L(i-1,l) - R(i-1,r) \Big]
\end{aligned}
$$

注意其中 $F(i)$ 的意义，它表示前 $i$ 行连通的概率，那么答案就是 $F(n)$。

细心的同学可能已经发现了，$L(i,x)$ 和 $R(i,x)$ 在转移、形式和结果上都是高度对称的。事实上，把 $L(i,x)$ 左右翻转就可以得到 $R(i,x)$，即 $L(i,x)=R(i,m-x+1)$。于是我们只要讨论 $L(i,x)$ 的处理就可以了。

由于 $f(i,l,r)$ 会对所有 $x \gt r$ 的 $L(i,x)$ 产生贡献，我们可以先记 $S_L(i,r)$ 表示所有右端点为 $r$ 的 $f(i,l,r)$ 之和，则对 $S_L$ 计算前缀和即可得到 $L$，用公式表达就是：
$$
\begin{aligned}
S_L(i,r) &= \sum_{l \le r} f(i,l,r) \\
L(i,x) &= \sum_{r \lt x} S_L(i,r)
\end{aligned}
$$

同时我们可以发现，所有的 $S_L(i,r)$ 之和就等于 $F(i)$，这样就把 $F(i)$ 也一并解决了。

接下来考虑如何计算 $S_L(i,r)$，把 $f(i,l,r)$ 的转移式代入：
$$
\begin{aligned}
S_L(i,r) &= \sum_{l \le r} f(i,l,r) \\
&= \sum_{l \le r} P(l,r) \Big[ F(i-1) - L(i-1,l) - R(i-1,r) \Big] \\
&= D(m-r) \sum_{l \le r} D(l-1) \Big[ F(i-1) - L(i-1,l) - R(i-1,r) \Big] \\
&= D(m-r) \left( \Big[ F(i-1)-R(i-1,r) \Big] \sum_{l \le r} D(l-1) - \sum_{l \le r} D(l-1) L(i-1,l) \right)
\end{aligned}
$$

到这里思路已经很清晰了，对 $D(l-1)$ 和 $D(l-1) L(i-1,l)$ 做前缀和即可实现 $O(1)$ 转移，最后答案即为 $F(n)$。边界同样是 $f(0,1,m)=1$，即 $S_L(0,m)=1$。

总时间复杂度 $O(nm+k)$，空间复杂度可以用滚动数组优化至 $O(m+k)$。


---

## 作者：chen_03 (赞：32)

看了看题解区，竟然没有一篇题解是我的思路，所以我来分享一下。

我们把行编号为 $0\sim n+1$，对于一个连通的状态，必然存在一条从第 $0$ 行到第 $n+1$ 行的只往左、右、下三个方向走的路径，途中只经过未被摧毁的方块。为了让每个连通的状态对应唯一一条路径，我们强制这条路径：

- 能往下走时，直接往下走；
- 否则，往左或往右走到最近的能往下走的方块，然后往下走。

考虑 DP，设 $f_{i,j}$ 表示从第 $i-1$ 行进入第 $i$ 行时在第 $j$ 列，且在第 $i-1$ 行有往右走时，第 $1\sim i-1$ 行的摧毁状态对应的概率；$g_{i,j}$ 的定义是将上面的 “往右走” 改成 “往左走”；$h_{i,j}$ 的定义是将 “往右走” 改成 “没有左右移动”。

$f_i$ 由 $f_{i-1},h_{i-1}$ 转移而来，$g_i$ 由 $g_{i-1},h_{i-1}$ 转移而来，$h_i$ 由 $f_{i-1},g_{i-1},h_{i-1}$ 转移而来。计算第 $i$ 行的 DP 值时，我们算上第 $i-1$ 行的摧毁状态对应的概率。转移式请读者自行推导（雾）。

转移可以前缀和优化，时间复杂度 $\mathcal{O}(nm)$。

根据这种 “路径” 的思想，应该有更简单的 DP 方法，请读者自行思考。具体地，我们可以调整 “强制每个连通的状态对应唯一一条路径” 的方式。我只是遵循刚想到这种思路时得到的 DP 方法罢了。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int p=1000000007;
int n,m,x,y,q,K,a[1505],s[1505],*f,*F,*g,*G,*h,*H,sum,ans;
int f1[1505],f2[1505],g1[1505],g2[1505],h1[1505],h2[1505];
inline int qpow(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=(ll)res*a%p;
		b>>=1,a=(ll)a*a%p;
	}
	return res;
}
int main(){
	scanf("%d%d%d%d%d",&n,&m,&x,&y,&K);
	q=(ll)x*qpow(y,p-2)%p;
	for(int i=0,C=1;i<=m;++i){
		if(i<=K)a[i]=(ll)C*qpow(q,i)%p*qpow(p+1-q,K-i)%p;
		else a[i]=0;
		s[i]=((i?s[i-1]:0)+a[i])%p;
		C=(ll)C*(K-i)%p*qpow(i+1,p-2)%p;
	}
	f=f1,F=f2,g=g1,G=g2,h=h1,H=h2;
	for(int j=1;j<=m;++j)f[j]=1;
	for(int i=2;i<=n;++i){
		sum=0;
		for(int j=1;j<=m;++j){
			F[j]=(ll)sum*s[m-j]%p;
			sum=(sum+(ll)f[j]*a[j-1]+(ll)h[j]*s[j-1])%p;
			H[j]=((ll)f[j]*a[j-1]%p*s[m-j]+(ll)g[j]*a[m-j]%p*s[j-1]+(ll)h[j]*s[j-1]%p*s[m-j])%p;
		}
		sum=0;
		for(int j=m;j>=1;--j){
			G[j]=(ll)sum*s[j-1]%p;
			sum=(sum+(ll)g[j]*a[m-j]+(ll)h[j]*s[m-j])%p;
		}
		swap(f,F),swap(g,G),swap(h,H);
	}
	for(int j=1;j<=m;++j)
		ans=(ans+(ll)f[j]*a[j-1]%p*s[m-j]+(ll)g[j]*a[m-j]%p*s[j-1]+(ll)h[j]*s[j-1]%p*s[m-j])%p;
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：lottle1212 (赞：13)

# [Student's Camp](https://www.luogu.com.cn/problem/CF708E) 题解

## 前言

很明显，本题是一道概率论。因此，我们必须做好愉快推柿子的准备 qwq。

由于恶心的状态设置与求逆元的繁琐工作（对于本蒟蒻而言），作者花了不少时间才弄明白，便写篇题解加深印象。

为了帮助和本蒟蒻一样蒻的人，本篇题解会详解上述两个部分。

## 解题思路

题目让我们求一个 $(n + 2) \times m$ 的网格 $k$ 天后保持联通的概率。除了首行和末行，其他 $n$ 行左右端点的格子均有 $p = \frac{a}{b}$ 的概率消失。为方便阐述与理解，将中间 $n$ 行编号为 $1 \sim n$，首行和末行编号为 $0$ 和 $n + 1$。

首先针对其中一行进行分析。容易得到，其中一行在第 $k$ 天恰好消失 $i$ 个的概率为：

$$\begin{pmatrix} k \\ i \\ \end{pmatrix} \times p^i \times (1 - p)^{k - i}$$

也就是说，$i$ 天有格子消失，$k - i$ 天没有格子消失，并在 $k$ 天内选出有格子 消失的 $i$ 天。

理清楚了一行的状态，接下来考虑转移。由于图的对称性，我们可以尝试置状态 $dp_{i, r}$ 表示第 $i$ 行右端点为 $r$，且 $0$ 至 $i$ 行联通的概率，而舍弃左端点。为什么可以这样设置呢？我们在转移时分情况讨论。

在转移的过程中，我们枚举左端点。因为丢失了左端点信息，所以判断相交较为复杂。而正难则反，我们考虑求不相交的方案，并从总方案中减去，这样在转移过程中只需要判断 $r' < l$ 或 $l' < r$。

1. 对于 $r' < l$，只需在枚举 $l$ 时直接计算 $\sum_{j = 1}^{l - 1} dp_{i - 1, j}$ 即可。
1. 对于 $l' > r$，此时利用对称性，$dp_{i, r}$ 亦可表示左端点为 $m - r + 1$ 且联通的概率，即左端点 $l'$ 可以用右端点 $m - l' + 1$ 来表示，那么计算 $\sum_{j = 1}^{m - r} dp_{i - 1, j}$ 即可。

![](https://s1.ax1x.com/2023/07/19/pC7BkKx.png)

所以得到转移：

$$dp_{i, r} = \sum_{l = 1}^{r} p_{l - 1} p_{m - r} (\sum_{j = 1}^{m} dp_{i - 1, j} - \sum_{j = 1}^{l - 1} dp_{i - 1, j} - \sum_{j = 1}^{m - r} dp_{i - 1, j})$$

这样转移的复杂度为 $O(nm^{3})$。为了加速求和，设 $dp_{i - 1, j}$ 的前缀和为 $\_dp_j$，则：

$$dp_{i, r} = \sum_{l = 1}^{r} p_{l - 1} p_{m - r} (\_dp_m - \_dp_{l - 1} - \_dp_{m - r})$$

$$= p_{m - r}((\_dp_{m} - \_dp_{m - r})\sum_{l = 1}^{r} p_{l - 1} - \sum_{l = 1} ^ {r} \_dp_{l - 1} p_{l - 1})$$

数学好的巨佬可以跳过此段。为什么要这样拆项呢？容易观察得到：$p_{m - r}, \_dp_m, \_dp_{m - r}$ 是与变量 $l$ 无关的项，$p_{l - 1}$ 是与 $p$ 和变量 $l$ 有关的项，而 $\_dp_{l - 1} p_{l - 1}$ 是与 $\_dp, p$ 以及变量 $l$ 有关的项。首先将和变量有无关系的项区分开，再对与变量有关的项根据其次数进行分类，这样往往能对一个整式进行高效的处理。

接着，我们再设 $p_{l}$ 的前缀为 $\_p_l$，$\_dp_{l} p_{l}$ 的前缀为 $dpp_{l}$ 则：

$$dp_{i, r} = p_{m - r}((\_dp_{m} - \_dp_{m - r}) \_p_{r - 1} - dpp_{r - 1})$$

通过前缀和优化，我们把复杂降到了 $O(nm)$。

## 代码实现

代码实现较为简单，但本蒟蒻仍认为实现的难点在于逆元，因此代码中求逆元的部分会详细注释。


**Code**

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const ll N = 1.5e3 + 10, M = 1e5 + 10, mod = 1e9 + 7;
ll n, m, a, b, k, p1, p2, ans, dp[N][N], _p[N], p[N], dpp[N], _dp[N], fac[M], inv[M]; //变量定义如题、如上文所述，其中 fac 为阶乘，inv 为逆元。
ll pow(ll x, ll y) { ll res = 1; while (y) { if (y & 1) res = res * x % mod; x = x * x % mod, y >>= 1; } return res; } //快速幂。
ll C(ll n, ll m) { return fac[n] * inv[n - m] % mod * inv[m] % mod; } //组合数。
signed main() {
	scanf("%lld%lld%lld%lld%lld", &n, &m, &a, &b, &k);
	p1 = a * pow(b, mod - 2) % mod, p2 = (1 - p1 + mod) % mod; //p1 为格子消失概率，p2 为格子不消失的概率，通过费马小定理求得。
	fac[0] = fac[1] = 1;
	for (ll i = 2; i <= k; ++ i) fac[i] = fac[i - 1] * i % mod; //预处理阶乘。
	inv[k] = pow(fac[k], mod - 2); //同样通过费马小定理求得逆元末项。
	for (ll i = k - 1; i >= 0; -- i) inv[i] = inv[i + 1] * (i + 1) % mod; //逆推，1 / (i !) = 1 / ((i + 1) !) * (i + 1)。
	for (ll i = 0; i <= k && i <= m; ++ i) p[i] = C(k, i) * pow(p1, i) % mod * pow(p2, k - i) % mod; // 预处理 k 天消失 i 个格子的概率。
	dp[0][m] = 1, _p[0] = p[0];
	for (ll i = 1; i <= m; ++ i) _p[i] = (_p[i - 1] + p[i]) % mod; //p 的前缀。
	for (ll i = 1; i <= n; ++ i) {
		for (ll j = 1; j <= m; ++ j) _dp[j] = _dp[j - 1] + dp[i - 1][j], _dp[j] %= mod, dpp[j] = (dpp[j - 1] + p[j] * _dp[j] % mod) % mod;
		for (ll j = 1; j <= m; ++ j) dp[i][j] = p[m - j] * ((_dp[m] - _dp[m - j] + mod) % mod * _p[j - 1] % mod - dpp[j - 1] + mod) % mod;
	}//如上文所述。
	for (ll i = 1; i <= m; ++ i) ans = (ans + dp[n][i]) % mod; //累计答案。
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：pitiless0514 (赞：13)

## 题目大意

一个 $(n + 2) \times m$ 的网格。

除了第一行与最后一行，每一行都有 $p$ 的概率消失，求 $k$ 天后，网格始终保持联通的概率。

答案对 $10^9 + 7$ 取模。

 $\text{Data Range:} 1 \leq n,m \leq 1.5 \times 10^3, k\leq 10^5$。

 ---------
 
来[我的博客](https://ptowo.github.io/post/cf708e-students-camp-ti-jie/)获取更加阅读体验。

不难发现最后每一行剩下的一定都会是一个连续的区间，而且每行之间相互独立。

自然设立状态 $dp_{i,l,r}$ 表示当前是第 $i$ 行，$k$ 天后这一行剩下的区间为 $[l, r]$，第 $0$ 行到第 $i$ 行都联通的概率。

先考虑算变成区间 $[l,r]$ 的概率。

设 $k$ 天内，消失 $i$ 个格子的概率为 $g_i = \binom{k}{i} p^i \times (1-p)^{k-i}$。

所以剩下区间 $[l,r]$ 的概率为  $g_{l-1} \times g_{m-r}$。

当然还需要检查这段区间长度是否合法，因为最多消失 $2k$ 个格子。

转移式子不难写出。

$$dp_{i,l,r} = g_{l-1} \times g_{m-r} \sum_{[l_1, r_1] \cap [l,r] \neq \varnothing} dp_{i-1,l_1,r_1}$$

复杂度 $nm^4$，显然不行，而且状态数都为 $nm^2$。

那考虑优化状态，去掉左端点的限制。

设 $dp_{i,r}$ 表示第 $i$ 行的剩余区间的右端点为 $r$，第 $0$ 行到第 $i$ 行都联通的概率，转移的时候枚举 $l$ 进行转移。

考虑一个和区间 $[l,r]$ 有交的区间 $[l_1,r_1]$。

它满足 $r_1 \geq l, l_1 \leq r$，那么容斥把这一部分算出来即可。

对于 $r_1 < l$ 的部分，枚举 $l$ 时计算 $\sum_{j=1}^{l-1} dp_{i-1,j}$。

对于 $l_1 > r$ 的部分，因为网格是对称的，所以 $f_{i,r}$ 也可以表示左端点为 $m-r+1$ 且联通的概率，因此这一部分可以计算为 $\sum_{j=1}^{m-r} f_{i-1,j}$。

于是转移如下。

$$dp_{i,r} = \sum_{l=1}^r g_{l-1} g_{m-r} (\sum_{j=1}^m f_{i-1, j} - \sum_{j = 1}^ {i-1} f_{i-1,j} - \sum_{j=1}^{m-r} f_{i-1,j})$$

这东西长得就很一脸前缀和的样子，那就考虑前缀和优化。

令 $s_{j}$ 表示 $\sum_{k=1}^j f_{i-1,k}$。

$$ f_{i,r} = g_{m-r} \sum_{l=1}^r g_{l-1} )(s_m - s_{l-1} - s_{m-r}) $$

$$f_{i,r} = g_{m-r} \times( (s_m - s_{m-r}) \sum_{l = 1}^r g_{l-1} - \sum_{l=1}^r g_{l-1} s_{l-1})$$

在令 $p_i$ 和 $q_i$ 依次为 $g_i$ 与 $g_i \times s_i$ 的前缀和，之后即可做到 $O(1)$ 转移，总时间复杂度 $o(nm)$。


```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
// 德丽莎的可爱在于德丽莎很可爱，德丽莎为什么很可爱呢，这是因为德丽莎很可爱！
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
  int x = 0, f = 1;  char ch = getchar();
  while( !isdigit(ch) ) { if(ch == '-') f = -1;  ch = getchar();  }
  while( isdigit(ch) ) {  x = (x << 1) + (x << 3) + (ch ^ 48);  ch = getchar();  }
  return x * f;
}
const int N = 3e6, mod = 1e9 + 7;
int n, m, a, b, pt, pt2, k, ans, fac[N], ifac[N], dp[3005][3005], g[3005];
int power(int a,int b) { int ans = 1; while (b) { if (b & 1) ans = ans * a % mod; a = a * a % mod; b >>= 1;} return ans; }
int binom(int n,int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
int s[N], p[N], q[N];
signed main () {
  n = read(), m = read(), a = read(), b = read(), k = read(); 
  fac[0] = 1; for (int i = 1; i <= k; i++) fac[i] = fac[i - 1] * i % mod;
  ifac[k] = power(fac[k], mod - 2); for (int i = k - 1; ~i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
  pt = a * power(b, mod - 2) % mod; pt2 = 1 - pt; pt2 += mod; pt2 %= mod;
  for (int i = 0; i <= k && i <= m; i++) g[i] = binom(k, i) * power(pt, i) % mod * power(pt2, k - i) % mod;
  dp[0][m] = 1;  p[0] = g[0]; 
  for (int i = 1; i <= m; i++) p[i] = p[i - 1] + g[i], p[i] %= mod;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) s[j] = s[j - 1] + dp[i - 1][j], s[j] %= mod;
    for (int j = 1; j <= m; j++) q[j] = q[j - 1] + g[j] * s[j] % mod, q[j] %= mod;
    for (int r = 1; r <= m; r++) dp[i][r] = g[m - r] * ( (s[m] - s[m - r] + mod) % mod * p[r - 1] % mod - q[r - 1] + mod) % mod;
  }  
  for (int i = 1; i <= m; i++) { ans += dp[n][i]; ans %= mod;}
  printf("%lld\n", ans);
  return 0;
}
```


---

## 作者：_Diu_ (赞：9)

和现有题解都不太一样的魔怔做法。

直接 `dp` 是 $O(nm^2)$，很多人都考虑直接前缀和优化状态，这里采用另一种方法。

看到网格连通块想到网格容斥。

直接网格容斥是错的，因为可能出现凹槽。

对于一种合法方案，那其实是要求每相邻两行都有重合的部分。

对相邻两行重合的部分上网格容斥，假设重合部分是 $S$，统计 $\sum_i [i\in S]-\sum_{i}[i,i+1\in S]$。

最终每个地方都合法的概率相当于求的是上面的式子的乘积的期望。设 $S_i$ 表示最终每一行剩下的位置构成的集合，我们求的东西就是 $\prod_{i=1}^{n-1}(\sum_{j=1}^m[j\in S_i\cap S_{i+1}]-\sum_{j=1}^{m-1}[j,j+1\in S_i\cap S_{i+1}])$ 这个式子的期望。

相当于没两行相邻指定一个 $i$ 必选的贡献是 $1$，指定 $i,i+1$ 必选的贡献是 $-1$。

然后对着这个东西 dp，设 $f_{i,j,0/1}$ 表示前 $i$ 行，第 $i$ 行指定了 $j$ 或者 $j,j+1$ 的情况的期望。

转移枚举下一行钦定的种类和位置 $k/k,k+1$，这个复杂度时 $O(nm^2)$，和暴力 `dp` 一样。

但是容易发现一行的概率只和钦定位置的最左侧和最右侧有关，可以分别讨论当前钦定位置在上一个钦定位置的左侧还是右侧，直接前缀和优化即可。复杂度 $O(nm+k)$ 或者 $O(nm+k\log p)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1510,M=1e5+10,p=1e9+7;
int n,m,k,a,b;
int ifac[M],fac[M],s[M];
int qpow(int x,int y=p-2){
	int m=1;
	for(;y;y>>=1,x=1ll*x*x%p)if(y&1)m=1ll*m*x%p;
	return m;
}
int f[N][N][2],sf[N],sg[N];
int C(int n,int m){
	return 1ll*fac[n]*ifac[m]%p*ifac[n-m]%p;
}
signed main(){
	scanf("%d%d%d%d%d",&n,&m,&a,&b,&k);
	fac[0]=1;
	for(int i=1;i<=k;i++)fac[i]=1ll*fac[i-1]*i%p;
	ifac[k]=qpow(fac[k]);
	for(int i=k-1;i>=0;i--)ifac[i]=1ll*ifac[i+1]*(i+1)%p;
	int pl=1ll*a*qpow(b)%p;
	s[0]=qpow(p+1-pl,k);
	for(int i=1;i<=m;i++){
		if(i<=k)s[i]=(s[i-1]+1ll*C(k,i)*qpow(pl,i)%p*qpow(p+1-pl,k-i))%p;
		else s[i]=s[i-1];
	}
	for(int j=1;j<=m;j++){
		f[1][j][0]=1ll*s[j-1]*s[m-j]%p;
		if(j<m)f[1][j][1]=(p-1ll*s[j-1]*s[m-j-1]%p)%p;
	}
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			sf[j]=(sf[j-1]+1ll*f[i-1][j][0]*s[j-1])%p;
			if(j>1)sf[j]=(sf[j]+1ll*f[i-1][j-1][1]*s[j-2])%p;
		}
		for(int j=m;j>=1;j--){
			sg[j]=(sg[j+1]+1ll*f[i-1][j][0]*s[m-j])%p;
			if(j<m)sg[j]=(sg[j]+1ll*f[i-1][j][1]*s[m-j-1])%p;
		}
		for(int j=1;j<=m;j++){
			f[i][j][0]=(1ll*sf[j]*s[m-j]%p+1ll*sg[j]*s[j-1]%p)%p;
			f[i][j][0]=(f[i][j][0]-1ll*f[i-1][j][0]*s[j-1]%p*s[m-j]%p+p)%p;
		}
		for(int j=1;j<m;j++){
			f[i][j][1]=(1ll*sf[j]*s[m-j-1]%p+1ll*sg[j+1]*s[j-1]%p)%p;
			f[i][j][1]=(f[i][j][1]+1ll*f[i-1][j][1]*s[j-1]%p*s[m-j-1]%p+p)%p;
			f[i][j][1]=(p-f[i][j][1])%p;
		}
	}
	int ans=0;
	for(int j=1;j<=m;j++)ans=(ans+f[n][j][0])%p;
	for(int j=1;j<m;j++)ans=(ans+f[n][j][1])%p;
	printf("%d\n",ans);
}
```

---

## 作者：Graphcity (赞：5)

提供一种新的解法。

分析题目：连通意味着从第一行能够走到最后一行，也就意味着任意相邻两行直接都有至少一个公共位置。

左右两边的消失是独立的，我们设 $h_x$ 为 $k$ 天内共消失 $x$ 个格子的概率，$s_x=\sum_{i=0}^xh_x$。$h_x$ 很好求，它等于：

$$
\binom{k}{x}p^x(1-p)^{k-x}
$$

考虑转化「任意相邻两行都有至少一个公共位置」这一条件。设第一行左右两边共消失了 $l_1,r_1$ 个，第二行消失了 $l_2,r_2$ 个格子。根据条件，存在 $1\le x\le m$ 使得 $l_1,l_2<x\le m-r_1,m-r_2$。继续转化一下：

$$
\begin{cases}
l_1<m-r_1\\
l_1<m-r_2\\
l_2<m-r_1\\
l_2<m-r_2
\end{cases}
$$

也就是说，

$$
\begin{cases}
l_1+r_1<m\\
l_2+r_2<m\\
l_1+r_2<m\\
l_2+r_1<m\\
\end{cases}
$$

不难发现这个条件是充要的。

根据不等式，如果我们钦定了 $l_{1\cdots n}$，那么 $r_{1\cdots n}$ 的最大值也就随之可以求出，答案也就可以容易得到。

我们发现，$r_1$ 受 $l_1,l_2$ 限制，$r_2$ 受 $l_1,l_2,l_3$ 限制，$r_3$ 受 $l_2,l_3,l_4$ 限制，$\cdots\cdots$，$r_n$ 受 $l_{n-1},l_n$ 限制，且限制的内容仅与它们的最大值有关。

根据限制可以得到启发：设 $f_{i,j,0/1}$ 表示考虑到第 $i$ 个位置，$\max(l_{i-1},l_i)=j$，且（下标最小的）最大值在 $i-1/i$ 处的概率之和。

这个动态规划的关键在于 $f_{i-1,a,b}$ 到 $f_{i,c,d}$ 之间的转移。在转移过程中，我们需要考虑 $r_{i-1}$ 和 $l_{i-1}$ 的值。

- 对于 $r_{i-1}$，很好处理，它的贡献就是 $s_{m-1-\max(a,c)}$。
- 对于 $l_{i-1}$，分类讨论：
  1. $b=0,d=0$：此时要求 $c\le a$，贡献为 $h_c$。
  2. $b=0,d=1$：此时要求 $c\ge 1$，贡献为 $s_{\min(a,c-1)}$。
  3. $b=1,d=0$：此时要求 $a=c$，贡献为 $h_a$。
  4. $b=1,d=1$：此时要求 $a<c$，贡献为 $h_a$。

注意特殊处理前面两个位置和最后两个位置。

这样做是 $O(nm^2+k)$ 的，过不去。

但是这个东西可以前缀和优化，最终时间复杂度 $O(nm+k)$，可以顺利通过。

- [**$O(nm^2+k)$ Brute**](https://www.luogu.com.cn/paste/srh3ujs4)

- [**$O(nm+k)$ Code**](https://www.luogu.com.cn/paste/buyn2oar)

---

## 作者：gzw2005 (赞：5)

$\texttt{Part 1}$：

可以发现，**每一行都是独立的**，所以我们可以先算出一行 $k$ 天之后恰好只剩下区间 $[l,r]$ 的概率。容易设 $p_{k,l,r}$ 进行区间 $\texttt{dp}$，但这是 $O(m^2k)$ 的。我们又发现其实 **左右端点也是独立的**，所以可以省掉一维，但 $O(mk)$ 还是没法做。我们思考我们在干什么，其实我们在求 $k$ 天之内可走可不走最后走了 $l$ 步的概率，直接组合数搞定 $p_l=C_k^{l}·P^{l}·(1-P)^{k-l}$。那么恰好只剩下 $[l,r]$ 的概率就是 $p_{l-1}·p_{n-r}$。

$\texttt{Part 2}$：

我们设 $f(n,l,r)$ 表示前 $n$ 行联通并且最后一行空余的区间为 $[l,r]$ 的方案数，转移可以考虑上一层总概率 减去 和 $[l,r]$ 没有交集的概率。容易得出转移方程：

$$f_{n,l,r}=p_{l-1}·p_{n-r}·(\sum\limits_{l'\le r'}f_{n-1,l',r'}-\sum\limits_{l'\le r'<l}f_{n-1,l',r'}-\sum\limits_{r<l'\le r'}f_{n-1,l',r'})$$

然而直接转移是 $O(nm^4)$ 的。我们发现可以用 **前缀和优化**。于是现在变成了 $O(nm^2)$ 还是过不了！如果要 $O(nm)$ 的复杂度，那么我们既要减少状态数，更要减少转移数，两个老大难问题摆在我们面前。

$\texttt{Part 3}$：

我们设 $tot_n=\sum\limits_{l'\le r'}f_{n,l',r'}$， $L_{n,i}=\sum\limits_{l'\le r'\le i}f_{n,l',r'}$，$R_{n,i}=\sum\limits_{r\le l'\le r'}f_{n,l',r'}$，则现在方程变成了

$$f_{n,l,r}=p_{l-1}·p_{n-r}·(tot_{n-1}-\sum_{l'=1}^{l-1} L_{n-1,l'}-\sum_{r'=r+1}^n R_{n-1,r'})$$

并且这个 $f_{n,l,r}$ 算完之后要贡献给 $L_{n,r},R_{n,l}$。不如直接不管这个中间变量 $f_{n,l,r}$ 我们直接计算 $L,R$ 状态之间的转移，这里只给出 $L_{n,r}$ 的情况：

$$L_{n,r}=\sum_{l=1}^r f_{n,l,r} = \sum_{l=1}^r p_{l-1}·p_{n-r}·(tot_{n-1}-\sum_{l'=1}^{l-1} L_{n-1,l'}-\sum_{r'=r+1}^n R_{n-1,r'})$$

我们发现在这个柿子里面 $p_{n-r},tot_{n-1}$ 都是 **固定** 的，并且一重循环的和式 $\sum\limits_{l=1}^r p_{l-1},\sum\limits_{r'=r+1}^n R_{n-1,r'}$ 可以用前缀和优化。剩下一个二重循环的和式 $\sum\limits_{l=1}^r p_{l-1}·p_{n-r}·\sum\limits_{l'=1}^{l-1} L_{n-1,l'}=p_{n-r}\sum\limits_{l=1}^r p_{l-1}·\sum\limits_{l'=1}^{l-1} L_{n-1,l'}$ 怎么办呢？其实也可以用前缀和优化，因为现在和式里面算的东西已经和 $r$ 没有关系了，我们从 $r$ 到 $r+1$ 的时候，这个和式的变化量就为 $p_{n-r}p_{r-1}·\sum\limits_{l'=1}^{r-1} L_{n-1,l'}$，因此我们每次维护 $L_{n-1,l'}$ 的前缀和，然后每次让和式加上这个变化量就好了。

$R_{n,l}$ 的转移也是一样的道理，~~只要再推一遍柿子~~。

$tot_n$ 就是全体 $l_{n,r}$ 或者全体 $R_{n,l}$ 的和。

细节看起来很多，但是只要真正想清楚码量并不大。

时间复杂度 $O(nm+k)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int N,M,P,K;
const int mod=1e9+7;
int fastpow(int a,int b) {
	int ret=1;
	while(b) {
		if(b&1) ret=1ll*ret*a%mod;
		b>>=1; a=1ll*a*a%mod;
	} return ret;
}
const int MAXN=1.5e3+10;
const int MAXK=1e5+10;
int fact[MAXK],invfact[MAXK];
int powp[MAXK],powinvp[MAXK];
void init() {
	fact[0]=1;
	for(int i=1; i<MAXK; i++)
		fact[i]=1ll*fact[i-1]*i%mod;
	invfact[MAXK-1]=fastpow(fact[MAXK-1],mod-2);
	for(int i=MAXK-1; i>0; i--)
		invfact[i-1]=1ll*invfact[i]*i%mod;
	powp[0]=powinvp[0]=1;
	for(int i=1; i<MAXK; i++)
		powp[i]=1ll*powp[i-1]*P%mod;
	powinvp[1]=(1+mod-P)%mod;
	for(int i=2; i<MAXK; i++)
		powinvp[i]=1ll*powinvp[i-1]*powinvp[1]%mod;
}
int C(int a,int b) {
	if(a<b) return 0;
	return 1ll*fact[a]*invfact[b]%mod*invfact[a-b]%mod;
}
int p[MAXN][MAXN],h[MAXN];
int l[MAXN][MAXN],g[MAXN][MAXN],all[MAXN];
int sumprow[MAXN],sumpcol[MAXN];
void solve() {
	for(int i=0; i<=K; i++)
		h[i]=1ll*C(K,i)*powp[i]%mod*powinvp[K-i]%mod;
	for(int i=1; i<=M; i++)
		for(int j=i; j<=M; j++) {
			p[i][j]=1ll*h[i-1]*h[M-j]%mod;
			all[1]=(all[1]+p[i][j])%mod;
			l[1][j]=(l[1][j]+p[i][j])%mod;
			g[1][i]=(g[1][i]+p[i][j])%mod;
			sumprow[i]=(sumprow[i]+p[i][j])%mod;
			sumpcol[j]=(sumpcol[j]+p[i][j])%mod;
		}
	for(int i=2; i<=N; i++) {
		for(int j=1,suml=0,sumhl=0; j<=M; j++) {
			suml=(suml+l[i-1][j-1])%mod;
			sumhl=(sumhl+1ll*h[j-1]*suml%mod)%mod;
			l[i][j]=(mod-1ll*h[M-j]*sumhl%mod)%mod;
			g[i][j]=1ll*sumprow[j]*(all[i-1]+mod-suml)%mod;
		}
		for(int j=M,sumg=0,sumhg=0; j>=1; j--) {
			sumg=(sumg+g[i-1][j+1])%mod;
			sumhg=(sumhg+1ll*h[M-j]*sumg%mod)%mod;
			l[i][j]=(l[i][j]+1ll*sumpcol[j]*(all[i-1]+mod-sumg)%mod)%mod;
			g[i][j]=(g[i][j]+mod-1ll*h[j-1]*sumhg%mod)%mod;
		}
		for(int j=1; j<=M; j++)
			all[i]=(all[i]+l[i][j])%mod;
	}
}
int main() {
	int a,b; scanf("%d%d%d%d%d",&N,&M,&a,&b,&K);
	P=1ll*a*fastpow(b,mod-2)%mod;
	init();
	solve();
	printf("%d",all[N]);
	return 0;
}
```

---

## 作者：xht (赞：5)

> [CF708E Student's Camp](https://codeforces.com/contest/708/problem/E)

## 题意

- 有一个 $(n+2) \times m$ 的网格。
- 除了第一行和最后一行，其他每一行每一天最左边和最右边的格子都有 $p$ 的概率消失。
- 求 $k$ 天后，网格始终保持连通的概率。
- $n,m \le 1.5 \times 10^3$，$k \le 10^5$，答案对 $10^9+7$ 取模。

## 题解

网格始终保持连通，等价于 $k$ 天后任意相邻两行剩下的区间有交。

考虑区间 dp，设 $f_{i,l,r}$ 表示前 $i$ 行连通且第 $i$ 行剩下的区间为 $[l,r]$ 的概率。

初始条件为 $f_{0,1,m} = 1$，转移：

$$f_{i,l,r} = p_{l,r}\sum_{[l^\prime, r^\prime] \cap [l,r] \ne \varnothing} f_{i-1,l^\prime,r^\prime}$$

其中 $p_{l,r}$ 表示 $k$ 天后剩下 $[l,r]$ 的概率，有 $p_{l,r} = p_{l-1} \times p_{m-r}$，$p_i = \binom{k}{i} p^i (1-p)^{k-i}$。

直接做是 $\mathcal O(nm^2)$ 的，显然无法接受。

设 $fr_{i,r} = \sum_{l\le r} f_{i,l,r}$，$sr_{i,j} = \sum_{r \le j} fr_{i,r}$。

同理设 $fl_{i,l} = \sum_{l \le r} f_{i,l,r}$，$sl_{i,j} = \sum_{l \ge j} fl_{i,l}$。

由于左右完全对称，因此 $fl_{i,j} = fr_{i,m+1-j}$，$sl_{i,j} = sr_{i,m+1-j}$。

则有：
$$\begin{aligned}f_{i,l,r}&= p_{l,r}\sum_{[l^\prime, r^\prime] \cap [l,r] \ne \varnothing} f_{i-1,l^\prime,r^\prime} \\\\&= p_{l,r}(sr_{i-1,m} - sr_{i-1,l-1} - sl_{i-1,r+1}) \\\\&= p_{l,r}(sr_{i-1,m} - sr_{i-1,l-1} - sr_{i-1,m-r})\end{aligned}$$
于是我们只需要计算 $fr_{i,j}$，然后前缀和求出 $sr_{i,j}$ 即可。

又有：
$$\begin{aligned}fr_{i,r}&= \sum_{l\le r} f_{i,l,r} \\\\&= \sum_{l\le r} p_{l,r}(sr_{i-1,m} - sr_{i-1,l-1} - sr_{i-1,m-r})\\\\&= \left((sr_{i-1,m}-sr_{i-1,m-r})p_{m-r}\sum_{l\le r} p_{l-1}\right) - \left(p_{m-r} \sum_{l\le r} p_{l-1} sr_{i-1,l-1}\right) \\\\&= p_{m-r}\left((sr_{i-1,m}-sr_{i-1,m-r})\sum_{l\le r} p_{l-1} - \sum_{l\le r} p_{l-1} sr_{i-1,l-1}\right)\end{aligned}$$
那么我们可以预处理 $q_r = \sum_{l\le r}p_{l-1}$，$g_{i,r} = \sum_{l \le r} p_{l-1}sr_{i,l-1}$，然后 $\mathcal O(nm)$ 计算出所有的 $fr_{i,j},sr_{i,j}$，从而计算出最终的答案，也就是 $sr_{n,m}$。

## 代码

```cpp
const int N = 1.5e3 + 7;
int n, m, k, a, b;
modint x, p[N], q[N], f[N][N], s[N][N], g[N][N];

inline modint binom(int i, int j) {
	modint a = 1, b = 1;
	for (int k = 1; k <= j; k++) a *= i + 1 - k, b *= k;
	return a / b;
}

int main() {
	rd(n), rd(m), rd(a), rd(b), rd(k), x = (modint)a / b;
	for (int i = 0; i <= min(m, k); i++)
		p[i] = binom(k, i) * (x ^ i) * ((1 - x) ^ (k - i));
	for (int i = 1; i <= m; i++) q[i] = q[i-1] + p[i-1];
	f[0][m] = s[0][m] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			f[i][j] = p[m-j] * ((s[i-1][m] - s[i-1][m-j]) * q[j] - g[i-1][j]),
			s[i][j] = s[i][j-1] + f[i][j],
			g[i][j] = g[i][j-1] + p[j-1] * s[i][j-1];
	print(s[n][m]);
	return 0;
}
```

---

## 作者：edu1119696004 (赞：4)


> [E. Student's Camp](https://codeforces.com/problemset/problem/708/E)

### 题目简述

有一个 $(n+2)\times m$ 的网格。除了第一行和最后一行，其他每一行每一天都有 $p$ 的概率消失。求 $k$ 天后网格始终保持连通的概率。答案对 $10^9+7$ 取模。

数据范围 $n,m \le 1.5 \times 10^3,k \le 10^5$。

### 分析

相信读者通过读题已经知道了这道题是**动态规划+优化**，[排列组合](https://baike.baidu.com/item/%E6%8E%92%E5%88%97%E7%BB%84%E5%90%88/706498?fromModule=lemma_search-box)的知识本文就不细讲，不懂的可以点开链接去学一下。

为了方便分析，下文称第一行和最后一行分别为 $0$ 和 $n+1$ 行。首先，我们很容易就能想到状态 $f_{i,l,r}$ 表示第 $i$ 行，区间为 $[l,r]$，第 $0$ 行到第 $i$ 行都连同的概率。一行区间为 $[l,r]$ 的概率,为左边消失恰好 $l-1$ 个和右边恰好消失 $m-r$ 个的概率。通过枚举那几天有格子消失，可以得到 $k$ 天恰好消失 $i$ 个的概率 $g_i = \left(^k_i\right)p_i (1-p)^{k-i}$。即可得到转移：

$$f_{i,l,r} = g_{l-1} g_{m-r} \sum\limits_{\max(l,l') \le \min(r,r')} f_{i-1,l',r'}$$

### 减小状态

但是对于这样的状态定义无论怎么优化，状态数是 $O(nm^2)$ 的，显然是过大了。我们要考虑减小状态，只保留区间长度是无法继续完成转移的，所以一定要保留一个端点。将 $f_{i,r}$ 定义为第 $i$ 行的右端点 $r$，第 $0$ 行到第 $i$ 行都连通的概率。在转移的时候，枚举左端点 $l$，并计算与之相交的区间和。由于这样的定义状态丢失了左端点信息，所以考虑求不相交的方案，并将其从总方案中减去，因为求区间不相交仅仅需要 $r' < l$ 或 $l' < r$。

对于 $r' < l$，在枚举 $l$ 的时候，直接计算 $f_{i-1,j}(j \le l-1)$ 的和即可。

而对于 $l' < r$，由于网格是对称的，所以 $f_{i,r}$ 同样可以表示左端点为 $m-r+1$ 连通的概率，直接计算 $f_{i-1,j}(j \le m-r)$ 的和即可。

所以就很容易得到转移：

$$f_{i,r} = \sum\limits_{l=1}^r p_{l-1} p_{m-r} \left(\sum\limits_{j=1}^m f_{i-1, j} - \sum\limits_{j=1}^{l-1} f_{i-1, j} - \sum\limits_{j=1}^{m-r} f_{i-1, j}\right)$$

### 前缀和优化

如果不做任何优化，这样转移的时间复杂度是 $O(nm^3)$ 的，所以仍需要加上一定的优化。为了加速求和，我们可以尝试加入前缀和优化，将 $f_{i-1,j}$ 的前缀和记为 $h_j$，那么有：

$$ \begin{aligned} 
f_{i,r} &= \sum\limits_{l=1}^r p_{l-1} p_{m-r} (h_m - h_{l-1} - h_{m-r})\\
&=p_{m-r} \left((h_m - h_{m-r}) \sum\limits_{l=1}^r p_{l-1} - \sum\limits_{l=1}^r p_{l-1} h_{l-1} \right)
\end{aligned} $$


将 $p_i$ 前缀和为 $a_i$，$p_ih_i$ 前缀和为 $b_i$，则最终的状态转移方程就显而易见了：

$$f_{i,r} = p_{m-r} \left((h_m - h_{m-r}) a_{r-1} - b_{r-1} \right)$$

这样就通过前缀和优化将时间复杂度降到了 $O(nm)$，可以[$\textcolor {green}{Accepted}$](https://codeforces.com/contest/708/submission/214337197)了。

### 代码

最后给出代码，仅供参考！

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1.5e3+10;
const int MAXS=1e5+10;
const int mod=1e9+7;
typedef long long LL;
void reduce(int &x) {
	x += x >> 31 & mod;
}
int mul(int a,int b) {
	return (LL)a*b%mod;
}
int pow(int a,int b,int res=1) {
	for (;b;b>>=1,a=mul(a,a))
		if (b & 1)
			res=mul(res,a);
	return res;
}
void fma(int &x,int y,int z) {
	x = ((LL)y*z+x)%mod;
}
int n,m,K;
int ps[MAXN],pre[MAXN];
int fac[MAXS],inv[MAXS];
int C(int a,int b) {
	return (LL) fac[a] * inv[b] % mod * inv[a-b] % mod;
}
int f[MAXN][MAXN];
int main() {
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for (int i=2;i<MAXS;++i) {
		fac[i]=mul(fac[i-1],i);
		inv[i]=mul(inv[mod%i],mod-mod/i);
	}
	for (int i=2;i<MAXS;++i)
		inv[i]=mul(inv[i-1],inv[i]);
	scanf("%d%d",&n,&m);
	int a,b;
	scanf("%d%d",&a,&b);
	int P=pow(b,mod-2,a);
	scanf("%d",&K);
	for (int i=0;i<=m && i<=K;++i)
		ps[i]=pow(P,i,pow(1+mod-P,K-i,C(K,i)));
	for (int i=0;i<=m;++i)
		reduce(pre[i]=ps[i]+(i ? pre[i-1] - mod : 0));
	f[0][m]=1;
	for (int i=1;i<=n;++i) {
		static int tp[MAXN],ts[MAXN];
		for (int j=1;j<=m;++j) {//处理前缀和 
			reduce(tp[j]=tp[j-1]+f[i-1][j]-mod);
			fma(ts[j]=ts[j-1],ps[j],tp[j]);
		}
		for (int r=1;r<=m;++r) {//处理转移 
			int sm=mul(pre[r-1],tp[m]-tp[m-r]+mod);
			reduce(sm-=ts[r-1]);
			f[i][r]=mul(ps[m-r],sm);
		}
	}
	int ans=0;
	for (int i=1;i<=m;++i)
		reduce(ans+=f[n][i]-mod);
	printf("%d\n",ans);
	return 0;
}
```
最后，感谢洛谷网校给予灵感

---

## 作者：tzc_wk (赞：3)

[Codeforces 题目传送门](https://codeforces.com/contest/708/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF708E)

~~神仙 *3100，%%%~~

首先容易注意到 $\forall i\in[1,m]$，第 $i$ 行剩余的砖块一定构成一个区间，设其为 $[l_i,r_i]$。

其次，由于第 $0$ 行和第 $m+1$ 行的砖块不可能被风吹走，因此该建筑物只可能被上下劈开，i.e.，该建筑物被劈开当且仅当 $\exist i\in[1,m),[l_i,r_i]\cap[l_{i+1},r_{i+1}]=\varnothing$。

这时候就可以考虑 $dp$ 了，$dp_{i,l,r}$ 表示考虑到第 $i$ 行，第 $i$ 行剩余的砖块组成的区间为 $[l,r]$ 的概率。因此我们就有了~~优秀~~的 $n^5$ 的 $dp$：$dp_{i,l,r}=P(l,r)\times\sum\limits_{[l,r]\cap[l',r']\ne \varnothing}dp_{i-1,l',r'}$，其中 $P(l,r)$ 为某一行被风吹得恰好只剩 $[l,r]$ 的概率，如果我们记 $f(i)$ 表示恰好 $i$ 个砖块被吹走的概率，那么有 $f(i)=\dbinom{k}{i}p^i(1-p)^{k-i}$，$P(l,r)=f(l-1)f(m-r)$。

显然我们要对这个 $dp$ 进行优化。怎么优化呢？考虑问题的反面，可拿概率减去 $[l,r]\cap[l',r']=\varnothing$ 的概率，显然概率为 $\sum\limits_{1\le l\le r\le m}dp_{i-1,l,r}$，而 $[l,r]\cap[l',r']=\varnothing$ 当且仅当 $r'<l\lor l'>r$，故 $[l,r]\cap[l',r']=\varnothing$ 的概率为 $\sum\limits_{1\le l'\le r'<l}dp_{i-1,l,r}+\sum\limits_{r<l'\le r'\le m}dp_{i-1,l,r}$，因此 $dp_{i,l,r}=P(l,r)(\sum\limits_{1\le l\le r\le m}dp_{i-1,l,r}-\sum\limits_{1\le l'\le r'<l}dp_{i-1,l,r}-\sum\limits_{r<l'\le r'\le m}dp_{i-1,l,r})$，如果我们记 $R_{i,r}$ 为右端点为 $r$ 的 $dp_{i,l,r}$ 的和，$L_{i,l}$ 为左端点为 $l$ 的 $dp_{i,l,r}$ 的和，那么我们可预处理 $R_{i,r}$ 的前缀和与 $L_{i,l}$ 的后缀和，这样可实现 $\mathcal O(1)$ 转移，复杂度降到了 $n^3$。

但这样还是会炸，事实上，我们状态数已经达到了 $\mathcal O(n^3)$，光是数组都远远开不下，因此考虑优化状态。我们考虑不计算 $dp_{i,l,r}$，直接计算 $R_{i,r},L_{i,l}$ 并写出它们的转移方程式。我们不妨进一步改写下 $dp_{i,l,r}$ 的转移方程式，将 $\sum$ 展开成关于 $L_{i,l},R_{i,r}$ 的表达式，那么有 $dp_{i,l,r}=f(l-1)f(m-r)(\sum\limits_{j=1}^mR_{i-1,j}-\sum\limits_{j=1}^{l-1}R_{i-1,j}-\sum\limits_{j=r+1}^mL_{i-1,j})$。还需注意到的一点是，容易发现 $L_{i,l}$ 的转移方程式与 $R_{i,r}$ 高度相似，事实上如果我们把每一排翻转过来的话即可发现 $R_{i,r}$ 变成了 $L_{i,l}$，因此我们可以得到 $L_{i,l}=R_{i,m-l+1}$，故上述方程可进一步改写为 $dp_{i,l,r}=f(l-1)f(m-r)(\sum\limits_{j=1}^mR_{i-1,j}-\sum\limits_{j=1}^{l-1}R_{i-1,j}-\sum\limits_{j=1}^{m-r}R_{i-1,j})$，我们考虑直接将 $R_{i,r},dp_{i,l,r}$ 的方程式合并，即**不经过 $dp_{i,l,r}$，直接根据 $R_{i-1,j}$ 的值转移到 $R_{i,j}$**：

$$\begin{aligned}R_{i,r}&=\sum\limits_{l=1}^rdp_{i,l,r}\\&=\sum\limits_{l=1}^rf(l-1)f(m-r)(\sum\limits_{j=1}^mR_{i-1,j}-\sum\limits_{j=1}^{l-1}R_{i-1,j}-\sum\limits_{j=1}^{m-r}R_{i-1,j})\\&=f(m-r)((\sum\limits_{l=1}^rf(l-1)(\sum\limits_{j=1}^mR_{i-1,j}-\sum\limits_{j=1}^{m-r}R_{i-1,j}))-\sum\limits_{l=1}^r\sum\limits_{j=1}^{l-1}f(l-1)R_{i-1,j}\end{aligned}$$

emmm……推到这一步应该就非常好维护了吧。

记 $SR_{i,j}=\sum\limits_{r=1}^jR_{i,r}$，即 $R_{i,j}$ 的前缀和，那么 $R_{i,r}=f(m-r)((\sum\limits_{l=1}^rf(l-1)(SR_{i-1,m}-SR_{i-1,m-r}))-\sum\limits_{l=1}^rf(l-1)SR_{i-1,l-1}$

显然 $SR_{i-1,m}-SR_{i-1,m-r}$ 是常数，可 $\mathcal O(1)$ 求出，因此我们只需处理 $f(j)$ 的前缀和和 $f(j)SR_{i-1,j}$ 的前缀和即可实现 $\mathcal O(1)$ 转移。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=1.5e3;
const int MAXK=1e5;
const int MOD=1e9+7;
int n,m,a,b,k,p,fac[MAXK+5],ifac[MAXK+5];
void init_fac(int n){
	fac[0]=ifac[0]=ifac[1]=1;
	for(int i=2;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i]*ifac[i-1]%MOD;
}
int d[MAXN+5],sd[MAXN+5],ss[MAXN+5];
int dp[MAXN+5][MAXN+5],sdp[MAXN+5][MAXN+5];
int binom(int x,int y){return 1ll*fac[x]*ifac[x-y]%MOD*ifac[y]%MOD;}
int qpow(int x,int e=MOD-2){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int main(){
	scanf("%d%d%d%d%d",&n,&m,&a,&b,&k);
	p=1ll*a*qpow(b)%MOD;init_fac(k);
	if(p==1){
		if(k<=m) d[k]=1;
	}
	else{
		int ivp=1ll*p*qpow(MOD+1-p)%MOD,pw=1;
		for(int i=1;i<=k;i++) pw=1ll*pw*(MOD+1-p)%MOD;
		for(int i=0;i<=m;i++) d[i]=1ll*binom(k,i)*pw%MOD,pw=1ll*pw*ivp%MOD;
	}
	sd[0]=d[0];for(int i=1;i<=m;i++) sd[i]=(sd[i-1]+d[i])%MOD;
	dp[0][m]=1;sdp[0][m]=1;
	for(int i=1;i<=n;i++){
		memset(ss,0,sizeof(ss));
		for(int j=1;j<=m;j++) ss[j]=(ss[j-1]+1ll*d[j]*sdp[i-1][j])%MOD;
		for(int j=1;j<=m;j++){
			dp[i][j]=1ll*d[m-j]*(1ll*(sdp[i-1][m]-sdp[i-1][m-j]+MOD)*sd[j-1]%MOD-ss[j-1]+MOD)%MOD;
//			printf("%d %d %d\n",i,j,dp[i][j]);
		}
		for(int j=1;j<=m;j++) sdp[i][j]=(sdp[i][j-1]+dp[i][j])%MOD;
	} printf("%d\n",sdp[n][m]);
	return 0;
}
```



---

## 作者：小粉兔 (赞：3)

代码写的很乱，讲个大概思路：

可以发现上下连通当且仅当相邻层剩下来的区间有交，那么我们考虑自上而下 DP，状态就为当前剩下的区间：  
令 $dp(i, l, r)$ 表示考虑前 $i$ 层，第 $i$ 层的区间为 $[l, r]$ 时的概率，转移时枚举上一层的区间即可。

这个做法状态数就是 $\mathcal O (n m^2)$ 的了，不能接受。

考虑区间 $[l, r]$，和它有交的区间 $[l', r']$ 需要满足 $r' \ge l$ 且 $l' \le r$，当然还有 $l' \le r'$。  
条件比较复杂，容斥一下可以发现也等价于所有区间减去 $r' < l$ 的区间减去 $l' > r$ 的区间（前提是满足 $l' \le r'$）。

那么现在转移就方便了，等于上一层的 DP 值的总和减去上述两个限制条件。

考虑令 $f(x)$ 表示所有满足 $l > x$ 的区间的 DP 值之和，令 $g(x)$ 表示所有满足 $r < x$ 的区间的 DP 值之和。  
（由对称性容易发现 $g(x) = f(m + 1 - x)$）

这时状态数仍然是 $\mathcal O (n m^2)$ 的，考虑直接利用上一层的 $f$（或 $g$）求出这一层的 $f$（或 $g$）。

推一波式子就发现，确实是可以求的，然后按照式子进行计算就行了。  
这部分因为我摸了，所以请详见 @[热言热语](https://www.luogu.com.cn/user/37132) 的[题解](https://www.luogu.com.cn/blog/hotwords/solution-cf708e)。

计算时需要预处理形如 $\displaystyle \binom{k}{i}$ 的组合数。

时间复杂度为 $\mathcal O (nm + k)$，[评测链接](https://codeforces.com/contest/708/submission/66041767)。

---

## 作者：pufanyi (赞：2)

由于公式显示在题解界面是出现了一点巨大的偏差，部分挂掉的公式就用了图，当然也可以到[博客中看](https://www.luogu.com.cn/blog/pufanyi/solution-cf708e-local)，这样体验更好些，希望大家能谅解。

一个简单的想法就是我们令 $h_{i,l,r}$ 表示 $k$ 天后第 $i$ 行还剩下 $[l,r]$，前 $i$ 行联通的概率。$P_{l,r}$ 表示单独一行只剩 $[l,r]$ 的概率。
	
首先我们有：

![](https://pufanyi.github.io/oi-blog/images/1.svg)
	
接下来我们考虑 $P_{l,r}$，我们令 $q_{i}=\binom{k}{i}p^i(1-p)^{k-i}$，不难发现 $P_{l,r}=q_{l-1}q_{m-r}$。
	
然后我们令 $f_{i,r}$ 表示右端点为 $r$ 的所有 $h$ 之和，同理 $g_{i,l}$ 表示以左端点为 $l$ 的所有 $h$ 之和，再令 $F_{i,r}$ 表示右端点小于等于 $r$ 的所有 $h$ 之和，同理 $G_{i,l}$ 表示以左端点大于等于 $l$ 的所有 $h$ 之和。
	
具体地：

![](https://pufanyi.github.io/oi-blog/images/2.svg)

于是我们就有：

![](https://pufanyi.github.io/oi-blog/images/3.svg)
	
将 $h$ 代入 $f$ 和 $g$，我们有：

![](https://pufanyi.github.io/oi-blog/images/4.svg)
	
考虑到最后答案是 $F_{n,m}$，我们发现我们可以绕过 $h$ 来求 $F$。
	
最终复杂度 $\mathcal{O}(k+nm)$。

---

## 作者：Prean (赞：2)

考虑 $f(n,x,y)$ 表示第 $n$ 行左边被删了 $x$ 个右边被删了 $y$ 个的概率。

考虑用所有方案减去不连通的，$g(x,y)$ 表示某行左边被删 $x$ 个右边被删 $y$ 个的的概率，$S(n)=\sum_{x+y<m}f(n,x,y)$有：
$$f(n,x,y)=g(x,y)(S(n-1)-\sum_{Y\geq m-x\texttt{ or } X\geq m-y}f(n-1,X,Y))$$
容易发现 $g$ 的定义中左边和右边没有任何关系，所以可以写成 $g(x,y)=P(x)P(y)$，稍微写写有：
$$P(n)=\binom{k}{n}p^n(1-p)^{k-n}$$
容易发现 $f$ 的转移具有对称性，这样会导致 $f(n,x,y)=f(n,y,x)$。（$g$ 也一样）

设 $F(n,k)=\sum_{x\geq k}f(n,x,y)$。

可以重写转移：
$$f(n,x,y)=P(x)P(y)(S(n-1)-F(n-1,m-x)-F(n-1,m-y))$$
考虑对 $F$ 进行转移而不是 $f$。

容易发现 $S(n)$ 相当于 $F(n,0)$。

重新设 $F(n,k)=\sum_{y=k}f(n-1,x,y)$，这样就只需要最后处理一个后缀和即可。
$$F(n,x)=\sum_{y=0}^{m-x-1}P(x)P(y)(S(n-1)-F(n-1,m-x)-F(n-1,m-y))$$
$$=P(x)(S(n-1)-F(n-1,m-x))\sum_{y=0}^{m-x-1}P(y)-P(x)\sum_{y=0}^{m-x-1}P(y)F(n-1,m-y)$$
随便前缀和优化一下即可，复杂度 $O(nm)$。

初始值 $F(0,0,0)=1$，答案为 $S(n)$。

题外话，这题不值 *3100 吧。
```cpp
#include<cstdio>
namespace SOLVE{
	const int M=1505,mod=1e9+7;
	int n,m,k,p,P[M],F[M],G[M],S1[M],S2[M];
	inline int pow(int a,int b=mod-2){
		int ans(1);for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;return ans;
	}
	inline void main(){
		scanf("%d%d%d%d%d",&n,&m,S1,S2,&k);p=1ll*S1[0]*pow(S2[0])%mod;S1[0]=pow(mod+1-p,k);S2[0]=0;
		const int&q=1ll*p*pow(mod+1-p)%mod;for(int i=1;i<m;++i)S1[i]=1ll*S1[i-1]*q%mod;
		if(2*k<m)return printf("1"),void();if(p==1)return printf("0"),void();
		P[0]=P[1]=1;for(int i=2;i<m&&i<=k;++i)P[i]=1ll*(mod-mod/i)*P[mod%i]%mod;
		for(int i=1;i<m&&i<=k;++i)P[i]=1ll*(k-i+1)*P[i]%mod*P[i-1]%mod;
		for(int i=0;i<m;++i)P[i]=1ll*P[i]*S1[i]%mod;S1[0]=P[0];F[0]=1;
		for(int i=1;i<m;++i)S1[i]=(S1[i-1]+P[i])%mod;
		for(int k=1;k<=n;++k){
			const int&S(F[0]);for(int i=1;i<m;++i)S2[i]=(S2[i-1]+1ll*(mod-P[i])*F[m-i])%mod;
			for(int i=0;i<m;++i)G[i]=(1ll*(S+mod-F[m-i])*S1[m-i-1]+S2[m-i-1])%mod*P[i]%mod;
			for(int i=m-1;i>=0;--i)F[i]=(G[i]+F[i+1])%mod,G[i]=0;
		}
		printf("%d",F[0]);
	} 
}
signed main(){
	SOLVE::main();
}
```

---

## 作者：__Star_Sky (赞：1)

## Description
给定一个 $(n+2)\times m$ 的网格和三个整数 $a,b,k$，除了第一行和最后一行，从第一天开始每一天每一行最左边和最右边的格子都有 $b\times a^{-1}$ 的概率消失,其中 $a^{-1}$ 表示 $a$ 在模 $10^9+7$ 意义下的逆元。求在 $k$ 天网格保持连通的概率，答案对 $10^9+7$ 取模。

其中 $1\le n,m\le1.5\times10^3$，$0\le k\le10^5$，$1\le a,b\le10^9$ 且 $a,b$ 互质。

---
## Solution
考虑动态规划。设 $p=b\times a^{-1}$。为了方便起见，我们先将网格整体上移一格，即原先的第 $1$ 行变成第 $0$ 行，原先的第 $n+2$ 行变成第 $n+1$ 行。第 $0$ 行和第 $n+1$ 行的格子是不会消失的。

先考虑状态的设计。一种简单的想法是：设 $f_{i,j}$ 表示 $k$ 天后第 $i$ 行还剩 $j$ 个格子时整个网格仍保持连通的概率。但是这样的状态设计不仅很难转移，而且我们无法表示出每一行某种状态出现的概率，因为每一行只可能是最左边和最右边消失，我们并不知道左边或右边有多少个格子消失了。于是我们可以试着保留每一行的左端点和右端点：设 $f_{i,l,r}$ 表示 $k$ 天后第 $i$ 行还剩下 $[l,r]$ 这一部分格子时整个网格仍然保持连通的概率。

这样就可以表示每一行某种状态出现的概率了。设每一行左边或右边在第 $k$ 天消失 $i$ 个格子的概率为 $P(i)$。由于左边和右边的格子的消失是相互独立的事件，两边在第 $k$ 天消失 $i$ 个的概率是相等的。有：
$$P(i)=C_{k}^{i}\times p^{i}\times (1-p)^{k-i}$$
有 $i$ 天消失，概率就是 $p^i$，$k-i$ 天不消失，概率就是 $(1-p)^{k-i}$。 $k$ 天当中可以任意有 $i$ 天消失，因此乘以 $C_{k}^{i}$。这样，每一行剩下 $[l,r]$ 的概率就是 $P(l-1)\times P(m-r)$。可以先预处理出所有的 $P(i)$

考虑状态的转移。由于要让网格连通，显然第 $i-1$ 行剩下的格子所处的位置要与第 $i$ 行剩下的格子所处的位置有相交的部分。设第 $i-1$ 行剩下 $[l',r']$ 这部分格子。那么有 $[l,r]\cup[l',r']\ne\varnothing$。状态转移方程：
$$f_{i,l,r}=P(l-1)\times P(m-r)\times(\sum\limits_{[l,r]\cup[l',r']\ne\varnothing}f_{i-1,l',r'})$$
初态：$f_{0,1,m}=1$。最终答案就是 $\sum\limits_{l=1}^{m}\sum\limits_{r=l}^{m}f_{n,l,r}$。

这样一来，我们就得到了一个时间复杂度 $O(nm^4)$ 附带空间复杂度 $O(nm^2)$ 的优秀算法，可以拿下 Unaccepted。

发现这个式子并不好优化。试着转化一下：将“状态有相交部分的总和”转化为“所有状态的总和减去没有相交部分的状态”。也就是

$$f_{i,l,r}$$
$$=P(l-1)\times P(m-r)\times(\sum\limits_{[l,r]\cup[l',r']\ne\varnothing}f_{i,l',r'})$$
$$=P(l-1)\times P(m-r)\times(\sum\limits_{l'=1}^{m}\sum\limits_{r'=l'}^{m}f_{i-1,l',r'}-\sum\limits_{l'=1}^{l-1}\sum\limits_{r'=l'}^{l-1}f_{i-1,l',r'}-\sum\limits_{l'=r+1}^{m}\sum\limits_{r'=l'}^{m}f_{i-1,l',r'})$$

先来尝试一下优化空间。我们试着把 $f_{i,l,r}$ 中 $l$ 这一维去掉，也就是只保留右端点而枚举左端点。此时 $f_{i,r}$ 表示第 $i$ 行还剩下右端点为 $r$ 的格子时整个网格仍然保持连通的概率。这样上面的状态转移方程中 $\sum\limits_{l'=1}^{m}\sum\limits_{r'=l'}^{m}f_{i-1,l',r'}$ 这一部分的计算变成了 $\sum\limits_{r'=1}^{m}f_{i-1,r'}$，$\sum\limits_{l'=1}^{l-1}\sum\limits_{r'=l'}^{l-1}f_{i-1,l',r'}$ 这一部分的计算变成了 $\sum\limits_{r'=1}^{l-1}f_{i-1,r'}$。但是问题来了：$\sum\limits_{l'=r+1}^{m}\sum\limits_{r'=l'}^{m}f_{i-1,l',r'}$  怎么计算？

注意到本题有一个性质：$f_{i,l,r}=f_{i,m-r+1,m-l+1}$。由于两边对称，这条性质正确性显然。因此 $\sum\limits_{l'=r+1}^{m}\sum\limits_{r'=l'}^{m}f_{i-1,l',r'}=\sum\limits_{l'=1}^{m-r}\sum\limits_{r'=l'}^{m-r}f_{i-1,l',r'}=\sum\limits_{r'=1}^{m-r}f_{i-1,r'}$。

新的状态转移方程：
$$f_{i,r}=\sum\limits_{l=1}^{r}P(l-1)\times P(m-r)\times(\sum\limits_{r'=1}^{m}f_{i-1,r'}-\sum\limits_{r'=1}^{l-1}f_{i-1,r'}-\sum\limits_{r'=1}^{m-r}f_{i-1,r'})$$

时间复杂度 $O(nm^3)$，空间复杂度 $O(nm)$，已经有很大进步了。

考虑继续优化。注意到 $\sum\limits_{r'=1}^{m}f_{i-1,r'}-\sum\limits_{r'=1}^{l-1}f_{i-1,r'}-\sum\limits_{r'=1}^{m-r}f_{i-1,r'}$ 的值可以通过求 $f_{i-1}$ 的前缀和求出。设 $sum_j=\sum\limits_{k=1}^{j}f_{i-1,k}$，状态转移方程：
$$f_{i,r}=\sum\limits_{l=1}^{r}P(l-1)\times P(m-r)\times(sum_m-sum_{l-1}-sum_{m-r})$$

时间复杂度减少到了 $O(nm^2)$，但还是不足以通过。

显然 $i$ 和 $r$ 是我们不得不去枚举的，因此尝试在 $l$ 的枚举上做点文章，试一下能不能把 $l$ 的枚举省去。先把状态转移方程中有关 $l$ 和有关 $r$ 的部分拆开：
$$f_{i,r}=\sum\limits_{l=1}^{r}P(l-1)\times P(m-r)\times(sum_m-sum_{l-1}-sum_{m-r})$$
$$=P(m-r)(\sum\limits_{l=1}^{r}P(l-1)\times(sum_m-sum_{l-1}-sum_{m-r}))$$
$$=P(m-r)(\sum\limits_{l=1}^{r}P(l-1)\times(sum_m-sum_{m-r})-\sum\limits_{l=1}^{r}P(l-1)\times sum_{l-1})$$
$$=P(m-r)((sum_m-sum_{m-r})(\sum\limits_{l=1}^{r}P(l-1))-\sum\limits_{l=1}^{r}P(l-1)\times sum_{l-1})$$
这时我们惊奇地发现，$\sum\limits_{l=1}^{r}P(l-1)$ 和 $\sum\limits_{l=1}^{r}P(l-1)\times {sum}_{l-1}$ 这两个求和式中的元素都只和 $l$ 有关。又可以使用前缀和优化了！

设 $sump_i=\sum\limits_{j=0}^{i}P(i)$，$ssum_i=\sum\limits_{j=1}^{i}P(i)\times sum_{i}$。由于 $sum_0=0$，所以可以不用把 $P(0)\times sum_0$ 算进去。最终的状态转移方程：
$$=P(m-r)((sum_m-sum_{m-r})(sump_{r-1})-ssum_{r-1})$$
初态：$f_{0,m}=1$。最终答案即为 $\sum\limits_{r=1}^{m}f_{n,r}$

时间复杂度和空间复杂度均为 $O(nm)$，已经足以通过本题了。

---
## Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
const int N=1.5e3+10,M=1e5+10;
int f[N][N];
int P[M],fac[M],sum[N],sump[N],ssum[N];
int qpow(int a,int b)
{
	int res=1%mod;a%=mod;
	for(;b;b>>=1)
	{
		if(b&1) res=res*a%mod;
		a=a*a%mod;
	}
	return res;
}
int C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*qpow(fac[m],mod-2)%mod*qpow(fac[n-m],mod-2)%mod;
}
signed main()
{
	int n,m,a,b,K;
	scanf("%lld%lld%lld%lld%lld",&n,&m,&a,&b,&K);
	fac[0]=1;for(int i=1;i<=K;i++) fac[i]=fac[i-1]*i%mod;
	int p=a*qpow(b,mod-2)%mod,p1=(b-a)*qpow(b,mod-2)%mod;
	for(int i=0;i<=K;i++) P[i]=C(K,i)*qpow(p,i)%mod*qpow(p1,K-i)%mod;
	sump[0]=P[0];for(int i=1;i<=m;i++) sump[i]=(sump[i-1]+P[i])%mod;
	f[0][m]=1;
	for(int i=1;i<=n;i++)
	{
		sum[0]=0,ssum[0]=0;
		for(int r=1;r<=m;r++) sum[r]=(sum[r-1]+f[i-1][r])%mod,ssum[r]=(ssum[r-1]+sum[r]*P[r])%mod;
		for(int r=1;r<=m;r++)
			f[i][r]=P[m-r]*((sum[m]-sum[m-r]+mod)%mod*sump[r-1]%mod-ssum[r-1]%mod+mod)%mod;
	}
	int ans=0;
	for(int r=1;r<=m;r++)
			ans=(ans+f[n][r])%mod;
	printf("%lld\n",ans);
	return 0;
}
```
---
## Summary
在本题中，我们用一点点组合数学知识以及最简单最常用的前缀和的技巧就成功 AC。这再次印证了对简单算法灵活且熟练运用的重要性。

---

## 作者：Hanx16Kira (赞：0)

# Student's Camp

[Codeforces 708E](https://codeforces.com/problemset/problem/708/E)

[Luogu CF708E](https://www.luogu.com.cn/problem/CF708E)

## Solution

一道神仙前缀和优化概率 $\texttt{DP}$ 题。参考了第一篇题解的做法，然后添加了一些我自己认为不太好理解的地方的解释。

先定义 $D(i)$ 表示 $k$ 次吹风中刚好成功了 $i$ 次的概率。那么 $D(i)$ 很好计算：

$$
D(i) = \begin{pmatrix} k \\ i \end{pmatrix}
\cdot p^i\cdot (1-p)^{k-i}
$$

显然 $D(i)$ 是可以预处理出来的。

因为我们要求的东西是与每一层的区间相关的，所以不如再定义一个 $P(l,r)$ 表示一层中吹风吹的只剩 $(l,r)$ 的概率，那么用前面的 $D$ 就很好表示：

$$
P(l,r) = D(l-1)\cdot D(m-r)
$$

那么由此引出设计的状态：定义 $f(i,l,r)$ 表示第 $i$ 层被吹风吹的只剩下 $[l,r]$ 的概率。因为墙不能悬空，所以转移的时候 $i-1$ 层的区间一定要与 $[l,r]$ 有交，那么推出 $f(i,l,r)$ 的转移方程：

$$
f(i,l,r) = P(l,r) \cdot \sum \limits_{[l',r']\cap[l,r] \neq \varnothing} f(i-1,l',r')
$$

这样求解的话不难发现转移是 $\mathcal O(m^2)$ 的，所以需要优化。

考虑容斥，与 $[l,r]$ 有交的部分就可以表示成为所有区间减去那些没有交的区间。根据这个想法，将原式子变形。

$$
f(i,l,r) = P(l,r)\cdot(\sum \limits _{l'\le r'} f(i-1,l',r')-\sum\limits_{r'<l}f(i-1,l',r')-\sum\limits_{l'>r}f(i-1,l',r'))
$$

将三个带有求和号的部分重新定义一下：

$$
F(i)=\sum\limits_{l\le r} f(i,l,r)
$$
$$
L(i,x)=\sum\limits_{r< x} f(i,l,r)
$$
$$
R(i,x)=\sum\limits_{l>x} f(i,l,r)
$$

那么可以改写一下 $f(i,l,r)$ 的转移：

$$
f(i,l,r) = P(l,r) \cdot (F(i-1) - L(i-1,l) - R(i-1,r))
$$

现在来看怎么转移 $F,L,R$。容易发现，$L,R$ 其实是对称的，所以可以有 $L(i,x)=R(i,m-x+1)$。为了求出 $L$，再定义一个 $S(i,r)=\displaystyle\sum\limits_{l\le r}f(i,l,r)$。根据 $S$ 可以计算出 $F,L$：

$$
F(i)=\sum\limits_{x\le m} S(i,x)
$$
$$
L(i,x) = \sum\limits_{r<x} S(i,r)
$$

其实可以发现：$F(i)=L(i,m+1)$。

考虑怎么计算 $S$，将上面的定义式进行变形：

$$
\begin{array}{lll}
S(i,r) &=& \displaystyle\sum\limits_{l\le r} f(i,l,r) \\
&=& \displaystyle\sum\limits_{l\le r}P(l,r)\cdot (F(i-1)-L(i-1,l)-R(i-1,r)) \\
&=& D(m-r)\cdot\displaystyle\sum\limits_{l\le r}D(l-1)\cdot(F(i-1)-L(i-1)-R(i-1)) \\
&=& D(m-r)\cdot (F(i-1)-R(i-1,r))\displaystyle\sum\limits_{l\le r}D(l-1)-\sum\limits_{l\le r}D(l-1)\cdot L(i-1,l)
\end{array}
$$

发现此时的 $\displaystyle\sum\limits_{l\le r}D(l-1)$ 和 $\displaystyle\sum\limits_{l\le r}D(l-1)\cdot L(i-1,l)$ 已经独立，所以可以对这两个式子维护前缀和，然后就可以实现对 $S$ 的 $\mathcal O(1)$ 转移。

总时间复杂度为 $\mathcal O(nm)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
constexpr int _SIZE = 1.5e3, mod = 1e9 + 7, _MAXN = 1e5;
int Qpow(int x, int y) {
    int res = 1, base = x % mod;
    while (y) {
        if (y & 1) res = res * base % mod;
        y >>= 1, base = base * base % mod;
    }
    return res;
}
int F[2], D[_MAXN + 5], R[2][_SIZE + 5], L[2][_SIZE + 5], S[2][_SIZE + 5];
int sum1[_SIZE + 5], sum2[_SIZE + 5];
int p, fac[_MAXN + 5], inv[_MAXN + 5];
int n, k, m, a, b;
int cur = 1, last = 0;
void init() {
    fac[0] = 1; inv[0] = 1;
    for (int i = 1; i <= k; i++) fac[i] = fac[i - 1] * i % mod, inv[i] = Qpow(fac[i], mod - 2);
}
int C(int x, int y) {
    return fac[x] * inv[y] % mod * inv[x - y] % mod;
}
void initD() {
    for (int i = 0; i <= k; i++) 
        D[i] = C(k, i) * Qpow(p, i) % mod * Qpow(mod + 1 - p, k - i) % mod;
    sum1[0] = D[0];
    for (int i = 1; i <= m; i++) sum1[i] = (sum1[i - 1] + D[i]) % mod;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    cin >> a >> b; p = a * Qpow(b, mod - 2) % mod;
    cin >> k;
    init(); initD();
    S[cur][m] = 1; F[cur] = 1;
    for (int i = 1; i <= n; i++) {
        swap(cur, last);
        sum2[0] = 0;
        for (int j = 1; j <= m + 1; j++) (sum2[j] = sum2[j - 1] + D[j - 1] * L[last][j] % mod) %= mod;
        for (int r = 1; r <= m; r++) {
            S[cur][r] = D[m - r] * (((F[last] - R[last][r] + mod) % mod * sum1[r - 1] % mod - sum2[r] + mod) % mod) % mod;
        }
        for (int j = 1; j <= m + 1; j++) (L[cur][j] = L[cur][j - 1] + S[cur][j - 1]) %= mod, R[cur][m - j + 1] = L[cur][j];
        F[cur] = L[cur][m + 1];
    }
    cout << F[cur] << '\n';
    return 0;
}
```

---

## 作者：Reaepita (赞：0)

**若公式渲染出错请在博客内查看**
---

直观的想法是直接 $O(n^5)$ DP

枚举上一行的状态，枚举本行的状态转移。

但是这样做显然复杂度不正确。

考虑容斥，用上一行总方案数减去不与本行相连的方案数。

因为每一行本质相同，所可以先预处理出，每一行左或者右被吹走 $x$ 个砖块的概率 $c_x$。

设 $c_s$ 满足$c_{s}=\binom{t}{s}{p^s(1-p)^{t-s}}$

$dp_{i,l,r}=(sum_{i-1}-ls_{i-1,l-1}-rs_{i-1,r+1})c_{l-1}c_{m-r}$

$ldp_{i,r}=\sum_{l=1}^rdp_{i,l,r},rdp_{i,l}=\sum_{r=l}^mdp_{i,l,r}$

$
ls_{i,r}=\sum_{j=1}^rldp_{i,j},rs_{i,l}=\sum_{j=l}^mrdp_{i,j}
$

这样做是 $O(n^3)$ ，也不能通过本题。

可以发现：对于一种方案一定存在另一种方案与其对称。

所以 $ls$ 和 $rs$ 数组本质上没有区别。

即 $rs_{i,s}=ls_{i,m-s+1}$

可以得到 
$
dp_{i,l,r}=(ls_{i-1,m}-ls_{i-1,l-1}-ls_{i-1,m-r})c_{l-1}c_{m-r}
$

$
ldp_{i,r}=\sum_{l=1}^{r}(ls_{i-1,m}-ls_{i-1,l-1}-ls_{i-1,m-r})c_{l-1}c_{m-r}
$

可以发现这个式子是可以拆开的

$
ldp_{i,r}=(\sum_{l=1}^{r}(ls_{i-1,m}-ls_{i-1,l-1})c_{l-1}-ls_{i-1,m-r}\sum_{l=1}^{r}c_{l-1})c_{m-r}
$

所以只需要维护这两个个前缀和，就可以快速算出 $ldp_{i,r}$ 

最后答案显然是$ls_{n,m}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int maxn=1e3+5e2+10;
const int maxl=1e5+10;
inline int md(int x){return x>=mod?x-mod:x;}
int c[maxn],inv[maxl],fact[maxl];
int Pow(int a,long long k)
{
    int ret=1;
    while(k)
    {
        if(k&1)ret=ret*1LL*a%mod;
        k>>=1,a=a*1LL*a%mod;
    }
    return ret;
}
int C(int n,int m){return fact[n]*1LL*inv[m]%mod*inv[n-m]%mod;}
int p,a,b,t;
int n,m;
int dp[maxn][maxn],s[maxn][maxn];
int s1[maxn][maxn],s2[maxn][maxn];
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%d%d",&a,&b);
    scanf("%d",&t),inv[0]=fact[0]=1;
    for(int i=1;i<=100000;i++)fact[i]=fact[i-1]*1LL*i%mod,inv[i]=Pow(fact[i],mod-2);
    p=a*1LL*Pow(b,mod-2)%mod;
    for(int i=0;i<=min(t,m);i++)c[i]=C(t,i)*1LL*Pow(p,i)%mod*Pow(md(1-p+mod),t-i)%mod;
    dp[0][m]=s[0][m]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            s1[i][j]=md(s1[i][j-1]+md(s[i-1][m]-s[i-1][j-1]+mod)*1LL*c[j-1]%mod);
            s2[i][j]=md(s2[i][j-1]+c[j-1]);
        }
        for(int j=1;j<=m;j++)
        {
            dp[i][j]=md(s1[i][j]-s[i-1][m-j]*1LL*s2[i][j]%mod+mod)*1LL*c[m-j]%mod;
            s[i][j]=md(s[i][j-1]+dp[i][j]);
        }
    }
    printf("%d\n",s[n][m]);
    //system("pause");
}
```



---

