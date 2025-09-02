# Card Game

## 题目描述

在伯兰最受欢迎的卡牌游戏中，使用的是一个 $ n \times m $ 的卡牌组。每张卡牌都有两个参数：花色和等级。游戏中的花色编号从 $ 1 $ 到 $ n $，等级编号从 $ 1 $ 到 $ m $。每种花色和等级的组合中恰好有一张卡牌。

一张花色为 $ a $、等级为 $ b $ 的卡牌可以打败一张花色为 $ c $、等级为 $ d $ 的卡牌的条件有两个：
- $ a = 1 $ ， $ c \ne 1 $ （花色为 $ 1 $ 的卡牌可以打败任何其他花色的卡牌）；
- $ a = c $ ， $ b > d $ （同一花色的卡牌可以打败等级较低的卡牌）。

两名玩家进行游戏。在游戏开始之前，他们各自获得正好一半的牌组。第一名玩家获胜的条件是，对于第二名玩家的每一张卡牌，他都能选择一张可以打败它的卡牌，并且没有卡牌被选择两次（即存在一组匹配，第一名玩家的卡牌与第二名玩家的卡牌相匹配，每对中的第一名玩家的卡牌打败第二名玩家的卡牌）。否则，第二名玩家获胜。

你的任务是计算出将卡牌分配的方式，以便第一名玩家获胜的方式数量。两种方式被认为是不同的，如果存在一张卡牌在一种方式中属于第一名玩家，而在另一种方式中属于第二名玩家。结果可能非常大，因此请输出结果对 $ 998244353 $ 取模。

## 样例 #1

### 输入

```
1 4```

### 输出

```
2```

## 样例 #2

### 输入

```
2 2```

### 输出

```
2```

## 样例 #3

### 输入

```
3 6```

### 输出

```
1690```

## 样例 #4

### 输入

```
5 4```

### 输出

```
568```

## 样例 #5

### 输入

```
500 500```

### 输出

```
84693741```

# 题解

## 作者：Exp10re (赞：12)

感谢这道题送我上 CM 2k。

## 解题思路

考虑使用类似于括号匹配的想法类比每一种花色 Alice 和 Bob 应该怎么拿牌合法。

假定一张 Alice 所持有的大牌可以和 Bob 所持有的一张**花色相同**的小牌抵消，则得到以下三个结论：

1. 对于花色 1，Alice 可以有多余的牌，Bob 不能有多余的牌。
2. 对于不为 1 的花色，Bob 可以有多余的牌，Alice 不能有多余的牌。
3. 对于花色 1 中 Alice 多余的牌与不为 1 的花色 Bob 多余的牌数量相等。

则我们只需要得知在一种花色中一方多拿 $k$ 张牌的方案数以及在 $n-1$ 种花色中一方多拿 $k$ 张牌的方案数，两两相乘即可得到答案。

记 $f_{i,j}$ 表示考虑到第 $i$ 大的牌，其中 Alice 多拿了 $j$ 张牌且 Bob 不能有多余的牌的方案数，转移如下：

$$f_{i,j}=\begin{cases}
f_{i-1,1} & j=0 \\
f_{i-1,j-1}+f_{i-1,j+1} & otherwise. \\
\end{cases}$$

边界为 $f_{0,0}=1$，其余为 $0$。

可以发现，Bob 在另外一种花色多拿 $k$ 张牌且 Alice 不能有多余的牌的方案数实际上是相同的。

记 $g_{i,j}$ 表示从第二种花色考虑到第 $i$ 种花色，Bob 总共多拿 $j$ 张牌且在任意一种花色都没有多余的牌的方案数，转移如下：

$$g_{i,j}=\sum\limits_{k=0}^{j} g_{i-1,k}f_{m,j-k}$$

这一部分的转移只需要枚举 $j\leq m$ 的情况，更大部分的状态显然无用。

则根据一开始得到的第三条性质，最终的答案为：

$$S=\sum\limits_{i=0}^{m} g_{n,i}f_{m,i}$$

转移的时间复杂度是 $O(nm^2)$ 的，可以通过。

[Submission.](https://codeforces.com/contest/2025/submission/285905572)

---

## 作者：ccxswl (赞：8)

貌似和大部分做法不太一样？

权当卡特兰数的复习题吧。不会卡特兰数的可以先看文末。

---

如果没有花色 $1$ 这道题就很简单了，对于每个别的花色都有 $C(m)$ 种分配方案。$C(n)$ 表示卡特兰数的第 $n$ 项，答案就是乘起来。

发现除了花色 $1$ 每种花色的牌都是独立的。这启示我们枚举每种牌用了多少张花色 $1$。设 $f_{i,j}$ 表示前 $i$ 种花色的牌用了 $j$ 张花色 $1$ 能使第一名玩家获胜的方案数。

有转移：
$$
f_{i,j}=\sum_{k\le j} f_{i-1,j-k} \times H(k)
$$

枚举的 $k$ 的含义为第 $i$ 个花色用了 $k$ 张花色 $1$。其中 $H(k)$ 表示用了 $k$ 张花色 $1$ 的分配方案。

$H(k)$ 的计算也是简单的，考虑卡特兰数的经典问题，不能经过直线 $y=x$ 的方格路计数（如果不会可以看文末）。我们先得到了 $k$ 张极大的牌，可以看做在网格中先向右走了 $k$ 步，那问题就成了从 $(0,k)$ 走到 $(\frac{m+k}{2},\frac{m+k}{2})$ 且不能经过直线 $y=x$ 的方案数。

答案就是：
$$
H(k)={m \choose \frac{m+k}{2}}-{m\choose\frac{m+k}{2}+1}
$$

至此，已经解决大部分问题了，最后就是解决花色 $1$ 的分配。上面的问题是 $m$ 张牌中需要先拿出 $k$ 张与花色 $1$ 匹配，而现在的问题是 $m$ 张花色 $1$ 需要拿出若干张与其他牌匹配，发现问题是一样的，统计答案时乘上 $H(k)$ 就好了，这里的 $k$ 表示有 $k$ 张花色 $1$ 被用来与其他花色的牌匹配。

复杂度为 $O(n^3)$，如果你是大常数选手就会 [TLE](https://codeforces.com/contest/2025/submission/291179149)，有一个优化是 $\frac{m+k}{2}$ 为整数的状态才合法，加上这个就不卡常了。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxN = 1e3 + 7, mod = 998244353;

int fc[maxN], ifc[maxN];
int ksm(int a, int b = mod - 2) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = 1ll * res * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return res;
}

int n, m;

int C(int n, int m) {
  if (n < 0 || m < 0 || n < m) return 0;
  return 1ll * fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
int H(int k) {
  auto res = C(m, (m + k) / 2) - C(m, (m + k) / 2 + 1);
  res += res < 0 ? mod : 0;
  return res;
}

int f[507][507];

signed main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);

  cin >> n >> m;

  fc[0] = 1;
  for (int i = 1; i <= m * 2; i++)
    fc[i] = 1ll * fc[i - 1] * i % mod;
  ifc[m * 2] = ksm(fc[m * 2]);
  for (int i = m * 2 - 1; i >= 0; i--)
    ifc[i] = 1ll * ifc[i + 1] * (i + 1) % mod;

  f[1][0] = 1;
  for (int i = 2; i <= n; i++)
    for (int j = 0; j <= m; j++)
      for (int k = (m & 1); k <= j; k += 2)
        f[i][j] = (f[i][j] + 1ll * f[i - 1][j - k] * H(k) % mod) % mod;

  int ans = 0;
  for (int k = 0; k <= m; k++)
    ans = (ans + 1ll * f[n][k] * H(k) % mod) % mod;
  cout << ans << '\n';
}
```

---

卡特兰数可以解决这类问题：有一个大小为 $n\times n$ 的方格图左下角为 $(0, 0)$ 右上角为 $(n, n)$ ，从左下角开始每次都只能向右或者向上走一单位，不走到对角线 $y=x$ 上方（但可以触碰）的情况下到达右上角有多少可能的路径？（摘自 OI Wiki）

答案就是所有的路径数减去不合法的路径数，发现不合法的路径一定经过直线 $y=x+1$。对于经过 $y=x+1$ 且终点为 $(n,n)$ 的路径，在它第一次接触 $y=x+1$ 后，把它的所有运动反向，向右走变为向上走，向上走变为向右走，最后它一定会到达 $(n-1,n+1)$。

下图中的橙色虚线和粉色虚线是不合法的路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/fc95q593.png)

可以得出 $C(n)$ 为从 $(0,0)$ 到 $(n,n)$ 的路径数减从 $(0,0)$ 到 $(n-1,n+1)$ 的路径数。

所以：
$$
C(n)={2n\choose n}-{2n\choose n+1}
$$

---

## 作者：xyin (赞：3)

首先分析题目性质（以下均用 $A$ 表示第一名玩家，$B$ 表示第二名玩家）：

1. 对于花色为 $1$ 的牌：$A$ 的花色为 $1$ 的牌肯定不能少于 $B$。否则 $A$ 无法打败 $B$ 多出来的花色为 $1$ 的牌。

2. 对于“其它花色”：$A$ 的“其它花色”牌一定能找到一张同花色的 $B$ 的牌，使得 $A$ 的牌能打败 $B$。否则 $B$ 就一定有一张牌能打败 $A$。

综上，我们能得出一个结论：$A$ 的花色为 $1$ 的牌肯定要多于或等于 $B$，$B$ 的“其它花色”牌肯定要多于或等于 $A$。而 $A$ 比 $B$ 多的花色为 $1$ 的牌，就是用来去匹配 $B$ 比 $A$ 多的“其它花色”牌。

我们先来考虑同一种“其它花色”牌，先分析 $A$ 选的牌和 $B$ 选的牌的数量相等的情况。此时是一个经典的卡特兰数问题：假设**从大到小**分配牌，分配给 $A$ 看作 $+1$，分配给 $B$ 看作 $-1$，则答案就是求一个长度为 $m$ 的，有 $\cfrac{m}{2}$ 个 $+1$ 和 $\cfrac{m}{2}$ 个 $-1$，满足任意前缀和 $\ge 0$ 的序列的方案数（也可以类比于合法括号序列的方案数、从 $(0,0)$ 走到 $(\cfrac{m}{2},\cfrac{m}{2})$ 且不经过 $y=x$ 的方案数......）

我们再来加上 $A$ 选的牌少于 $B$ 选的牌的情况，同样也是类似的，但此时我们把 $B$ 比 $A$ 多选的牌也看作 $+1$，那么答案就是求一个长度为 $m$ 的 $\pm 1$ 序列满足任意前缀和 $\ge 0$，但此时对 $+1$ 和 $-1$ 的数量没有要求。设 $g_{i,j}$ 表示长为 $i$ 的序列选 $j$ 个 $-1$ 的方案数，我们可以用 $O(m^2)$ 的 DP 预处理得到。

然后就来到了最重要的状态设计环节，设 $f_{i,j}$ 表示考虑了前 $i$ 个花色，还剩的花色为 $1$ 的牌的数量。直接枚举第 $i+1$ 个花色选的 $-1$ 数量转移即可，转移为（这里写的是刷表，感觉容易理解）：

$$f_{i+1,j-(m-2\times k)}\leftarrow f_{i+1,j-(m-2\times k)} +f_{i,j}\times g_{m,k}$$

预处理为 $O(m^2)$，总时间复杂度为 $O(m^2+n\times m^2)$，可以通过本题。

[代码在这儿，可以参考对拍](https://www.luogu.com.cn/paste/elq1vvwg)

---

## 作者：Eibon (赞：3)

发现花色为 $1$ 的卡牌是特殊的，并不太好处理，不妨将问题拆开，思考没有花色 $1$ 的情况。

这种情况下，只考虑同种花色即可。

求方案数考虑设 dp。

设 $f_{i,j}$ 表示选到第 $i$ 个位置，选了 $j$ 个卡牌的方案数。显然每个卡牌都要取一半。

显然有约束 $j\times 2 \le i$，因为如果你选择的卡牌超过了，那么就会留下剩余的，剩余的一定比接下来的要小。初始化 $f_{0,0}=1$。

那么则有

$$f_{i,j}=f_{i-1,j-1}+f_{i-1,j}[j\times2\le i-1]$$

即当前选和不选的情况。

接下来考虑有花色 $1$ 的情况。

显然，你可以多去取一些花色 $1$ 用来干掉其他花色。

考虑将花色 $1$ 加入状态。

设 $g_{i,j}$ 表示考虑完花色 $1$ 到 $i$，还剩下多少张花色 $1$。

则有

$$g_{i,j}=g_{i-1,j+k}\times f_{m,(m-k)/2}$$

即这次使用 $k$ 张花色 $1$。

需要保证，$m-k$ 为偶数。

最终答案即为 $g_{n,0}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=500+5;
const int mod=998244353;
const int inf=0x3f3f3f3f3f3f3f3f;
int T=1,n,m;
int f[maxn][maxn],g[maxn][maxn];
void solve()
{
	scanf("%lld%lld",&n,&m);
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		f[i][0]=1;
		for(int j=1;j*2<=i;j++){
			f[i][j]=f[i-1][j-1];
			if(j*2<i){
				f[i][j]+=f[i-1][j];
				f[i][j]%=mod;
			}
		}
	}
	for(int i=0;i<=m;i+=2){
		g[1][i]=f[m][(m-i)/2];
	}
	for(int i=2;i<=n;i++){
		for(int j=0;j<=m;j++){
			for(int k=0;j+k<=m;k++){
				if((m-k)&1){
					continue;
				}
				g[i][j]+=g[i-1][j+k]*f[m][(m-k)/2]%mod;
				g[i][j]%=mod;
			}
		}
	}
	printf("%lld\n",g[n][0]);
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
//	scanf("%lld",&T);
	while(T--){
		solve();
	}
	return 0;
}
//dyyyyds
```

---

## 作者：_Ch1F4N_ (赞：3)

由于花色为 $1$ 的牌只能被花色为 $1$ 的牌打败，所以一定是先手比后手多若干张花色为 $1$ 的牌。

对于其他花色的牌，先手一定先用持有的牌打败后手，再用剩下的花色为 $1$ 的打败后手。

并且先手每种花色不为 $1$ 的牌数量不会多余后手，因为多的没法消耗掉。

于是考虑一个类背包 dp，设计状态 $dp_{i,j}$ 表示考虑完花色 $[1,i]$ 花色为 $1$ 的牌剩 $j$ 张的方案，注意到转移过程中我们还要处理一个形如 $m$ 张牌，从中抽出 $k$ 张作为右括号，使得可以从剩下 $m-k$ 张中抽出 $k$ 张作为左括号与这 $k$ 张形成合法括号序列的抽选方案，再考虑 $DP_{i,j}$ 表示考虑前 $i$ 张，右括号选了 $j$ 的的方案，括号序列的限制就是任意前缀中左括号数量不少于右括号。

直接按照上述状态 dp 即可做到 $O(n \times m^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 998244353;
const int maxn = 600;
int dp[maxn][maxn];//考虑到 n=[1,i] 第一位玩家花色 1 剩 j 张
int g[maxn];//m 个位置 选出 j 个位置满足任意前缀选出的位置数量不超过一半
int f[maxn];//m 个位置,选出 j 个位置满足任意后缀选出的位置数量不超过一半
//g[i]=f[i]
int DP[maxn][maxn];//i 个位置,选出 j 个满足任意前缀选出的位置数量不超过一半的方案
int n,m;
signed main(){
    cin>>n>>m;
    DP[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j*2<=i;j++){
            if(j!=0) DP[i][j]=(DP[i][j]+DP[i-1][j-1])%mod;
            if(j*2<=i-1) DP[i][j]=(DP[i][j]+DP[i-1][j])%mod;
        }
    }
    for(int i=0;i<=m;i++){
        g[i]=(g[i]+DP[m][i])%mod;
    }
    for(int j=0;j<=m;j+=2) dp[1][j]=g[(m-j)/2];
    for(int i=1;i<n;i++){
        for(int j=0;j<=m;j++){
            for(int a=0;a<=m-a;a++){
                if(j>=m-2*a) dp[i+1][j-(m-2*a)]=(dp[i+1][j-(m-2*a)]+dp[i][j]*g[a]%mod)%mod;
            }
        }
    }
    cout<<dp[n][0]<<'\n';
    return 0;
}
```

---

## 作者：Linge_Zzzz (赞：3)

# 前言

再一次完美错过上分场。

# Descr

定义两个二元组 $(a,b)$ 与
 $(c,d)$ 满足 $(a,b)>(c,d)$ 当且仅当：

 - $a=1$ 且 $c\neq 1$。
 - $a=c$ 且 $b>d$。

现在总共有 $n\times m$ 个二元组 $(x,y)$，对于每个 $1\leq x\leq n$ 且 $1\leq y\leq m$ 都有唯一的一个二元组 $(x,y)$ 与之对应。

你需要把这 $n\times m$ 个二元组划分给 Alice 和 Bob，每个人都得到 $\frac{nm}{2}$ 个二元组，Alice 能打败 Bob 当且仅当能够把 Alice 和 Bob 的牌之间两两匹配，每个匹配中 Alice 的二元组都大于 Bob 的二元组。

求 Alice 能打败 Bob 的划分方案数。

$n,m\leq 500$，$m$ 是偶数。

# Sol

观察条件。当二元组 $(x,y)$ 的 $x=1$ 时，它很特殊，能与其他的 $x$ 相匹配。否则他只能与 $x$ 相同的匹配。

简化情况，考虑 $n=1$。

把所有的二元组排成一行，经过分析可以发现，Alice 能打败 Bob 当且仅当对于这一行的任意一个前缀，属于 Alice 的二元组个数大于等于属于 Bob 的二元组个数（显然）。

如果你知道卡特兰数，可以很容易的知道这个方案数就是 $Cat_{\frac{m}{2}}$。

考虑 $n=2$。

此时，因为不只有一行，所以第一行 Alice 比 Bob 多选的可以对第二行造成贡献，考虑枚举第一行 Alice 比 Bob 多选多少，记为 $d$，可以发现 $d$ 一定是偶数。

此时，计算在第一行能给第二行产生 $d$ 的贡献时，第二行选择的方案数，再乘上第一行 Alice 比 Bob 多选 $d$ 时的方案数即为答案。

那么这两个方案数如何计算呢？

回归卡特兰数的推导过程：

> 有一个平面直角坐标系，从 $(0,0)$ 开始，每次可以向上或向右走，问不穿过直线 $y=x$ 到达点 $(n,n)$ 的方案数，即 $Cat_n$。
>
> 结论：$Cat_n=\binom{2n}{n}-\binom{2n}{n-1}$。
>
> 证明：
>
> 不考虑不穿过 $y=x$ 的限制，方案数为 $\binom{2n}{n}$，即为在 $2n$ 步中选 $n$ 步向右走，剩下 $n$ 步向上走。
>
> 考虑减去穿过 $y=x$ 的方案数，此时对于每一个穿过 $y=x$ 的方案，把穿过后除了第一步的移动方向，都取反，那么最终会走到 $(n-1,n+1)$ 而且每个走到这个点的方案能与每个穿过 $y=x$ 的方案一一对应。走到 $(n-1,n+1)$ 的方案数为 $\binom{2n}{n-1}$，合起来总方案数为 $\binom{2n}{n}-\binom{2n}{n-1}$。

仿照上述过程推导。

记第一行能给第二行产生 $d$ 的贡献时，第二行选择的方案数为 $Cat_1(d)$，第一行 Alice 比 Bob 多选 $d$ 时的方案数为 $Cat_2(d)$，则有：

> $Cat_1(d)$ 等价于从 $(0,0)$ 开始，不穿过直线 $y=x+d$ 走到 $(\frac{m-d}{2},\frac{m+d}{2})$ 的方案数，仿照上述推导可得 $Cat_1(d)=\binom{m}{\frac{m-d}{2}}-\binom{m}{\frac{m-d}{2}-1}$。
>
> $Cat_2(d)$ 等价于从 $(0,0)$ 开始，不穿过直线 $y=x$ 走到 $(\frac{m+d}{2},\frac{m-d}{2})$ 的方案数，仿照上述推导可得 $Cat_2(d)=\binom{m}{\frac{m+d}{2}}-\binom{m}{\frac{m-d}{2}-1}$。

所以当 $n=2$ 时，答案为：

$$\sum_{d=0,d \ \text{is even}}^{m}Cat_1(2d)\times Cat_2(2d)$$

考虑最终的问题。

依然考虑先枚举第一行 Alice 比 Bob 多选 $d$ 个，然后把这 $d$ 个多选的分配到剩余的 $n-1$ 行里，求方案数，发现这是一个背包。

具体地，设 $f_{i,j}(i\geq 2,j \ \text{is even})$ 为考虑前 $i$ 行，不考虑第一行，当前一共使用了 $j$ 个第一行多选的方案数，可以得到转移：

$$f_{i,j}=\sum_{k=0,k \ \text{is even}}^j f_{i-1,j-k}\times Cat_1(k)$$

最后统计答案，答案为：

$$\sum_{d=0,d \ \text{is even}}^{m}f_{n,d}\times Cat_2(2d)$$

直接 DP，复杂度 $O(n^3)$。可以通过。

注意特判 $n=1$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N=510,M=1e5+10,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m;
int fac[M],facinv[M];
int qpow(int a,int p){
	int res=1;
	while(p){
		if(p&1)res=res*a%mod;
		a=a*a%mod;
		p>>=1;
	}
	return res;
}
void init(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	facinv[n]=qpow(fac[n],mod-2);
	for(int i=n;i>=1;i--)facinv[i-1]=facinv[i]*i%mod;
}
int C(int n,int m){return fac[n]*facinv[n-m]%mod*facinv[m]%mod;}
int Cat1(int dt){return (C(m,(m-dt)/2)-C(m,(m-dt)/2-1)+mod)%mod;}
int Cat2(int dt){return (C(m,(m+dt)/2)-C(m,(m-dt)/2-1)+mod)%mod;}
int f[N][N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0); 
	init(1e5);
	cin>>n>>m;
	if(n==1){
		cout<<Cat1(0)<<endl;
		return 0;
	}
	f[1][0]=1;
	for(int i=2;i<=n;i++)
		for(int j=0;j<=m;j+=2)
			for(int k=0;k<=j;k+=2)
				f[i][j]=(f[i][j]+f[i-1][j-k]*Cat1(k)%mod)%mod;
	int ans=0;
	for(int dt=0;dt<=m;dt+=2)
		ans=(ans+f[n][dt]*Cat2(dt)%mod)%mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：2)

一眼发现是卡特兰数相关，然后范围很小，直接全 DP 出来即可。\
如果没有 `1` 的特殊牌，每行之间互相独立，直接相乘即可，但是 `1` 可以去帮助其他牌，不难想到枚举分出多少个 `1` 来帮助其他牌。\
分析完上面之后，就可以自然地设计出 $f_{i,j}$ 表示一共分了 $i$ 张牌，需要 $j$ 次帮助才能吃完，转移 $f_{i,j}=f_{i-1,j-1}+f_{i-1,j+1}$，然后枚举分出 `1` 的数量 $cnt$，现在问题就成了把 $cnt$ 个糖分给 $n-1$ 个小朋友类似的问题了，不过每一种方案都有一个系数。\
枚举分给当前小朋友糖的个数，再给他乘个系数，得到转移 $d_{i,j}=\sum_{k=0}^jd_{i-1,j-k}f_{m,k}$，最后答案就是 $\sum_{cnt=0}^{m}f_{m,cnt}d_{n-1,cnt}$，前面的系数表示 `1` 牌富余 $cnt$ 个的方案数（对称性），时间复杂度 $\mathcal{O}(n^3)$，不知道前缀和可不可以优化 $d$ 的转移，但是直接上 `FFT` 就做到了 $n\log n$，然后 $f$ 可以卡特兰数求，整体复杂度做到了 $\mathcal{O}(n\log n)$，不知道推式子能不能更优秀。
```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pii std::pair<int,int>
#define eb emplace_back
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
std::mt19937 myrand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=1000+10,mod=998244353,inf=1e9,P=501;
inline void Min(int &x,int y){if(x>y)x=y;}
inline void Max(int &x,int y){if(x<y)x=y;}
inline void W(int &x,int y){x=(x+y)%mod;}
int n,f[N][N],jc[N],ny[N],m,ans,d[N][N];
inline int R(int x){return x+P;}
signed main(){
    // freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    n=read(),m=read();
    f[0][0]=d[0][0]=1;
    for(int i=1;i<=m;++i)for(int j=0;j<=m;++j)W(f[i][j],f[i-1][j-1]+f[i-1][j+1]);
    for(int i=1;i<=n;++i)for(int j=0;j<=m;++j)for(int k=0;k<=j;++k)W(d[i][j],d[i-1][j-k]*f[m][k]);
    for(int c=0;c<=m;++c)W(ans,f[m][c]*d[n-1][c]);
    std::cout<<ans<<'\n';
}
```

---

## 作者：harmis_yz (赞：2)

题解摘自 [CSP2024 前做题情况](https://www.luogu.com.cn/article/3yyu431w)。

## 分析

考虑 DP。

注意到对于一种花色 $x(x\ge 2)$，第一个人得到的一定不多于第二个人得到的。因为一旦比第二个人多，那么他一定会剩下一些这种花色的牌，并且用不出去。那么对于第二个人比第一个人得到的该花色的牌多的情况，此时只能由第一个人得到的多的花色为 $1$ 的牌抵消掉。

那么思路就有了。我们只需要求出一个 $g_i$，表示 $2\sim n$ 这些花色中，第二个人比第一个人多 $i$ 张牌的方案数（其它的牌都两两抵消掉了）。然后再求一个 $f_{i}$，表示第一个人比第二个人多 $i$ 张花色 $1$ 的牌的方案数。那么答案就是 $\sum\limits_{i=0}^{m} f_i \times g_i$。

对于 $g_i$，不难发现是由 $f'$ 经过 $n-1$ 次背包转移得到的。因为每种花色对应的方案数相同。这里的 $f'_i$ 和 $f_i$ 的区别仅在于是第二个人比第一个人多 $i$ 张牌。那么只要求出 $f_i$，就能得到 $f'_i$，从而得到 $g_i$ 了。

定义状态函数 $dp_{i,j,k}$ 表示前 $i$ 张牌，发给第一个人 $j$ 张，第一个人比第二个多 $k$ 张的方案数。那么分类讨论：

1. 第 $i$ 张牌给第一个人，有：$dp_{i,j,k}\to dp_{i,j,k}+dp_{i-1,j-1,k-1}$。
2. 第 $i$ 张牌给第二个人，有：$dp_{i,j,k}\to dp_{i,j,k}+dp_{i-1,j,k+1}$。

那么有：$f_i=\sum\limits_{j=0}^{m} dp_{m,j,i}$。

然后 $f'_i$ 和 $g_i$ 就能相继求出来了。时间复杂度 $O(m^3+m^2n)$。

---

## 作者：incra (赞：1)

### Sol
先考虑同色的有多少分配方式，注意到此时 $m$ 只能平分，考虑把该问题转化成如下：

1. 一个点初始在 $(0,0)$。
2. 对于每个数字，从小到大枚举，如果当前数字为先手所取，那么往右走一格，否则往上走一格。
3. 答案即为 $(0,0)$ 到 $(\frac{m}{2},\frac{m}{2})$ 的方案数，且途中不经过 $y=x+1$ 的方案数。

这做法显然正确，对于先手拥有的权值 $\le x$ 的卡数一定要多于对手权值 $\le x$ 的卡数，否则显然无解。

注意到这个东西就是卡特兰数。

接下来考虑加入数字 $1$ 之后怎么做，显然 $1$ 可以特殊考虑每个颜色加入了几张 $1$，假设加了 $t$ 张 $1$，那么对于前面的问题转化可以变成如下：

1. 一个点初始在 $(0,0)$。
1. 先往右走 $t$ 步。
1. 对于每个数字，从小到大枚举，如果当前数字为先手所取，那么往右走一格，否则往上走一格。
1. 答案即为 $(0,0)$ 到 $(\frac{m+t}{2},\frac{m+t}{2})$ 的方案数，且途中不经过 $y=x+1$ 的方案数。

注意需要满足 $m+t\equiv 0\pmod 2$，这个转化与上面同理。

那么就可以考虑 DP，设 $f_{i,j}$ 表示前 $i$ 个花色（不包括 $1$）所用去 $1$ 的卡片数量，那么不难得到 $\displaystyle f_{i,j}=\sum_{k=0~\operatorname{and}~2 \mid (m+k)}^{j} f_{i-1,j-k}\times H(k)$，其中 $H(k)$ 为转化的问题 $t=k$ 的答案。

最后答案就是 $\displaystyle \sum_{k=0~\operatorname{and}~2 \mid (m+k)}^{m} f_{n,k}\times H(k)$。

最后讲讲如何计算 $H(k)$。

不难求出从 $(0,0)$ 到 $(n,m)$ 的方案数是 $\binom(n+m,n)$，一共 $n+m$ 个位置，选择 $m$ 个位置往上即可（$n$ 个往右也同理）。

首先我们可以转化成求更加通用的从 $(0,0)$ 到 $(n,m)$ 不经过 $y=x+1$ 的方案数。

那么对于任意一条经过 $y=x+1$ 的路径，可以把路径从**第一个**经过 $y=x+1$ 点位置以后的线沿着 $y=x+1$ 反转（镜像），那么路径就会变成从 $(0,0)$ 到 $(n-1,m+1)$。

注意到任意一条不合法的路径都可以转化成 $(0,0)$ 到 $(n-1,m+1)$ 的路径，反过来也可以对应，那么这两个东西显然是双射，所以等价，故 $(0,0)$ 到 $(n,m)$ 不经过 $y=x+1$ 的方案数为 $\binom{n+m}{n}-\binom{n+m}{n-1}$。
### Code
[Link](https://codeforces.com/contest/2025/submission/312511431)。

---

## 作者：happybob (赞：1)

题意：

在伯兰最受欢迎的卡牌游戏中，使用的是一个 $ n \times m $ 的卡牌组。每张卡牌都有两个参数：花色和等级。游戏中的花色编号从 $ 1 $ 到 $ n $，等级编号从 $ 1 $ 到 $ m $。每种花色和等级的组合中恰好有一张卡牌。

一张花色为 $ a $，等级为 $ b $ 的卡牌可以打败一张花色为 $ c $，等级为 $ d $ 的卡牌的条件有两个：

- $ a = 1 $ 且 $ c \ne 1 $（花色为 $ 1 $ 的卡牌可以打败任何其他花色的卡牌）；
- $ a = c $ 且 $ b > d $（同一花色的卡牌可以打败等级较低的卡牌）。

两名玩家进行游戏。在游戏开始之前，他们各自获得正好一半的牌组。第一名玩家获胜的条件是，对于第二名玩家的每一张卡牌，他都能选择一张可以打败它的卡牌，并且没有卡牌被选择两次（即存在一组匹配，第一名玩家的卡牌与第二名玩家的卡牌相匹配，每对中的第一名玩家的卡牌打败第二名玩家的卡牌）。否则，第二名玩家获胜。

你的任务是计算出将卡牌分配的方式，以便第一名玩家获胜的方式数量。两种方式被认为是不同的，如果存在一张卡牌在一种方式中属于第一名玩家，而在另一种方式中属于第二名玩家。结果可能非常大，因此请输出结果对 $ 998244353 $ 取模。

$1 \leq n, m \leq 500$。

解法：

事实上整个过程类似括号匹配。不妨令第一名玩家获得的卡牌为右括号，第二名获得的为左括号。则可以发现第一行的左括号必须总能找到右括号匹配，同时可能剩下若干没匹配的右括号，这些右括号可以给第 $2$ 到 $n$ 行中多出来的未匹配左括号进行匹配。

考虑 DP，记 $f_{i,j,k}$ 表示长度为 $i$ 的括号序列，目前有 $j$ 个左括号失配，还剩 $k$ 个右括号可以对前面匹配的方案数。这个 DP 可以朴素转移，然后对 $n-1$ 行做卷积，最后枚举第一行剩的右括号数量即可。复杂度 $O(n^3)$。

[Submission Link.](https://codeforces.com/contest/2025/submission/285884278)

---

## 作者：xishanmeigao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF2025E)

首先题目的意思就是，同种花色内部比较，数值大的牌厉害。而花色 $1$ 又可以击败其它任意花色。

我们发现除了 $1$ 以外的不同花色间是不能比较的，所以在没有 $1$ 号牌的情况下，先手能赢肯定是对于任意一种花色，先手后手都各自选择一半，设先手选了 $a_1<a_2<\dots<a_{m/2}$，后手选了 $b_1<b_2<\dots<b_{m/2}$，都有 $a_i>b_i$。将后手的选择看成 $+1$，先手看成 $-1$，则对于同种花色的任意一种合法选择方案，需要满足任意的前缀，前缀和 $s_i\ge 0$，这可以用卡特兰数解决。具体的，可以看作是从 $(0,0)$ 走到 $(\frac{m}{2},\frac{m}{2})$ 且不穿过直线 $y=x$，第一步必须向右走的方案数，为 $\dfrac{\dbinom{m}{\frac{m}{2}}}{\frac{m}{2}+1}$。

现在有了 $1$ 号牌就没那么简单了，我们考虑枚举用去打其它花色的牌的个数 $t$，剩下 $m-t$ 张 $1$ 号牌内部互相斗。那这时候其它牌就不一定要满足上述条件，设 $dp_{i,j}$ 表示 $2\sim i$ 这些花色，用了 $j$ 张花色 $1$ 的合法方案数。枚举花色 $i+1$ 用几张 $1$ 号牌，设为 $k$，则 $dp_{i,j}\times f(k)\to dp_{i+1,j+k}$。其中 $f(k)$ 表示在用 $k$ 张一号牌的情况下，有多少种合法的分牌方式。

如何求 $f(k)$？首先仍然要满足任意前缀 $s_i\ge 0$，但是现在先手只需要选出 $\dfrac{m-k}{2}$ 张牌就好了，这可以看作从 $(0,0)$ 走到 $(m-\frac{m-k}{2},\frac{m-k}{2})$ ，且不穿过直线 $y=x$，第一步必须向右走的方案数。设 $X=m-\frac{m-k}{2},Y=\frac{m-k}{2}$，由 [P1641](https://www.luogu.com.cn/problem/P1641) 的理论，我们知道这个方案数是 $\dfrac{X+1-Y}{X+1}\dbinom{X+Y}{X}$。

现在只需要计算合法的花色 $1$ 的分配方案，再乘上 $dp_{n,t}$ 就好了。发现把合法的一种花色 $1$ 选择方案倒过来（整个序列翻转之后，$1\to -1$，$-1\to 1$），就是一种合法的其它花色选择方案，所以也是 $f(t)$。

最终答案就是 $\sum \limits_{t\in \operatorname{even}} dp_{n,t}\times f(t)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;

const int N=1e3+10,MOD=998244353;

int n,m,dp[N][N];
int fac[N],ifac[N],inv[N];

void addm(int &x,int y){(x+=y<0? MOD+y:y)%=MOD;}

int ksm(int x,int y)
{
	int res=1;
	while(y)
	{
		if(y&1) res=1LL*res*x%MOD;
		x=1LL*x*x%MOD; y>>=1;
	}
	return res;
}

int C(int a,int b)
{
	if(a<b) return 0;
	return 1LL*fac[a]*ifac[b]%MOD*ifac[a-b]%MOD;
}

void init(int n)
{
	fac[0]=ifac[0]=1;
	for(int i=1; i<=n; i++)
		fac[i]=1LL*fac[i-1]*i%MOD;
	ifac[n]=ksm(fac[n],MOD-2);
	for(int i=n-1; i>=1; i--)
		ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;
	for(int i=1; i<=n; i++)
		inv[i]=ksm(i,MOD-2);
}

int f(int a,int b)
{
	return 1LL*(a+1-b)*inv[a+1]%MOD*C(a+b,a)%MOD;
}

int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);

	scanf("%d%d",&n,&m);

	init(N-5);

	dp[1][0]=1;
	for(int i=1; i<n; i++)
		for(int j=0; j<=m; j+=2)
			for(int k=0; j+k<=m; k+=2)
				addm(dp[i+1][j+k],1LL*dp[i][j]*f(m-(m-k)/2,(m-k)/2)%MOD);

	int ans=0;
	for(int t=0; t<=m; t+=2)
		addm(ans,1LL*f(m-(m-t)/2,(m-t)/2)*dp[n][t]%MOD);

	printf("%d\n",ans);

	return 0;
}
```

---

