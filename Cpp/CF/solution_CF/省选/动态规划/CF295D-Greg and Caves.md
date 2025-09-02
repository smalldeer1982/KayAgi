# Greg and Caves

## 题目描述

Greg有一个8868，其屏幕为一$n \times m$的矩形，每个像素可以是黑色或白色。我们考虑将8868的行从上到下编号为1到$n$。类似地，8868的列从左到右编号为1到$m$

Greg认为8868显示一个洞时，当且仅当以下情况：

- $\exist$区间$[l,r](1 \leq l \leq r \leq n)$，使得每一行恰有两个黑色像素，而所有其他行只有白色像素
- $\exist$行$t(l \leq t \leq r)$，使得对于$\forall(i,j)(l \leq i \leq j \leq t)$，第$i$行中黑色单元格之间列的集合$S_1$，与第$j$行中黑色单元格之间列的集合$S_2$，满足$S_1 \subseteq S_2$，同样对于$\forall (i,j)(t \leq i \leq j \leq r)$，第$i$行中黑色单元格之间列的集合$S_1$，与第$j$行中黑色单元格之间列的集合$S_2$，满足$S_2 \subseteq S_1$，

Greg想知道，有多少种方案能让他的8868显示一个洞。当且仅当两个屏幕存在一个位置像素颜色不同，两种方案不同

帮帮Greg吧

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4 4
```

### 输出

```
485
```

## 样例 #3

### 输入

```
3 5
```

### 输出

```
451
```

# 题解

## 作者：AutumnKite (赞：7)

打个广告：[蒟蒻的博客](https://www.cnblogs.com/rill7747/p/9872585.html)

# 题意

给定$n,m$，你需要对一个$n\times m$的矩阵黑白染色，满足：

1. 存在一个区间$[l,r]$，满足$l\sim r$这些行有且仅有两个黑色格子，其他行不存在黑色格子。
2. 存在一个$t\ (l\le t\le r)$，使得对于所有的$i,j\ (l\le i\le j\le t)$，满足第$i$行以两个黑色格子为端点的区间（以下简称“区间”）被$j$行的区间包含；同样地，对于所有的$i,j\ (t\le i\le j\le r)$，第$j$行的区间被第$i$行的区间包含。

求染色方案数$\bmod (10^9+7)$的值。

# 题解

比较简单的$\mathrm{DP}$，设$dp_{i,j}$表示上半部分（即$l$到$t$部分）的高度**至多**为$i$，底边宽度（包含两个黑色格子）为$j$且底边位置固定时的方案数。

## 转移方程

$$dp_{i,j}=dp_{i,j-1}+\sum\limits_{k=2}^j dp_{i-1,k}$$

应该还是比较好理解的。初始值$dp_{1,i}=dp_{i,1}=1$。

直接转移是$O(n^3)$的，但是$\sum\limits_{k=2}^j dp_{i-1,k}$可以在枚举$j$的同时计算（即前缀和优化），时间复杂度可以做到$O(n^2)$。

## 答案

下半部分的方案与上半部分同理。

注意如果下半部分的底边长度和上半部分的底边长度相等，会有重复，所以应该减去。

$$ans=\sum\limits_{i=1}^n \sum\limits_{j=2}^m (dp_{i,j}-dp_{i-1,j})\times dp_{n-i+1,j}\times (m-j+1)\bmod 1000000007$$

$i$枚举的是下半部分的起始位置，$j$枚举的是下半部分的底边宽度，第一项是上半部分减去长度相等的方案，第二项是下半部分的方案，第三项是计算底边在矩阵中的位移。

注意需要随时取模。

# 代码

[Code](http://codeforces.com/contest/295/submission/45051328)

```cpp
#include <cstdio>
#define P 1000000007
int n, m, dp[2005][2005], ans;
int main(){
	scanf("%d%d", &n, &m);
	for (register int i = 1; i <= m; ++i) dp[1][i] = 1;
	for (register int i = 2; i <= n; ++i){
		int s = 0;
		dp[i][1] = 1;
		for (register int j = 2; j <= m; ++j)
			(s += dp[i - 1][j]) %= P, dp[i][j] = (dp[i][j - 1] + s) % P; // 前缀和优化
	}
	for (register int i = 1; i <= n; ++i)
		for (register int j = 2; j <= m; ++j)
			(ans += 1ll * (dp[i][j] - dp[i - 1][j] + P) * dp[n - i + 1][j] % P * (m - j + 1) % P) %= P; // 计算答案，随时取模
	printf("%d", ans);
}
```

代码丑陋，巨佬勿喷。

---

## 作者：Macesuted (赞：5)

[View in my blog](https://www.macesuted.cn/article/cf295d/)

---

[题面](https://codeforces.com/problemset/problem/295/D)

# 题意

问满足下列条件的 $n \times m$ 的 01 矩阵 $a$ 的数量：

1. $\exists [l,~r] (1 \le l \le r \le n)$，满足 $\forall i \in [l,~r],~\sum_j a_{i,j} =2$ 且 $\forall i \notin [l,~r],~\sum_j a_{i,j}=0$。
2. 设 $[l,~r]$ 中的每一行的第一个值为 $1$ 的位置的下标为 $x_i$，第二个值为 $1$ 的位置的下标为 $y_i$，则：$\exists t \in [l,~r]$，满足 $\forall i \in [l,~t-1],~x_i \ge x_{i+1},~y_i \le y_{i+1}$ 且 $\forall i \in [t,~r-1],~x_i \le x_{i+1},~y_i \ge y_{i+1}$。

# 分析

考虑使用 DP 解决本题。

令 $f[i][j]$ 表示考虑洞的前 $i$ 行（该 $i$ 行都在洞的中间位置 $t$ 的上方）且第 $i$ 行的 $y_i-x_i+1=j$ 时该洞的构造方案（不考虑洞在矩阵中的摆放位置）。

考虑枚举第 $i-1$ 行的长度以及与第 $i$ 行的相对位置，得出转移方程：

$$
f[i][j]=\sum_{t=0}^{j}f[i-1][t] \times (j-t+1)
$$

尝试使用该数据描述最终答案 $Ans$，考虑枚举中间位置 $t$ 的行编号以及该行 $y_i-x_i+1$ 的大小。同时由于可能存在构造洞的方案满足第 $t$ 行与相邻的几行的形态完全相同，为了防止算重，考虑令 $t$ 为洞的最大的满足 $y_i-x_i+1$ 最大的行数，同时枚举 $t+1$ 行的长度（小于 $t$ 行长度），算出最终答案：

$$
\begin{aligned}
Ans&=\sum_{i=1}^{n} \sum_{a=0}^{m-2} (m-a-1) \times \big( \sum_{l=1}^{i} f[i-l+1][a] \big) \times (1 + \sum_{b=0}^{a-1} \big( \sum_{r=i+1}^{n} f[r-i][b] \big) \times (a - b + 1))\\\\
&=\sum_{i=1}^{n} \sum_{a=0}^{m-2} (m-a-1) \times \big( \sum_{t=1}^{i} f[t][a] \big) \times (1 + \sum_{b=0}^{a-1} \big( \sum_{t=1}^{n-i} f[t][b] \big) \times (a - b + 1))
\end{aligned}
$$

令 $g[i][j] = \sum_{k=1}^{i} f[k][j]$。

$$
Ans=\sum_{i=1}^{n} \sum_{a=0}^{m-2} (m-a-1) \times g[i][a] \times (1 + \sum_{b=0}^{a-1} g[n-i][b] \times (a-b+1))
$$

令 $h[i][j]=\sum_{k=0}^{j-1} g[i][k] \times (j-k+1)$。

$$
Ans=\sum_{i=1}^{n} \sum_{a=0}^{m-2} (m-a-1) \times g[i][a] \times (1 + h[n-i][a])
$$

处理 $f[i][j]$ 前缀和优化到 $O(nm)$，处理 $g[i][j]$ $O(nm)$，处理 $h[i][j]$ 前缀和优化到 $O(nm)$，计算答案 $Ans$ $O(nm)$。

总时间复杂度 $O(nm)$。

# 代码

[View on Github](https://github.com/Macesuted/Code/blob/main/CodeForces/295D.cpp)

```cpp
/**
 * @author Macesuted (macesuted@qq.com)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {
// fread
}  // namespace io
using io::getch;
using io::getstr;
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 2005
#define mod 1000000007

long long f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], cac[maxn][maxn];

int main() {
    int n = read<int>(), m = read<int>();
    for (register int i = 0; i <= m - 2; i++) f[1][i] = 1;
    for (register int i = 2; i <= n; i++) {
        f[i][0] = cac[i][0] = f[i - 1][0];
        for (register int j = 1; j <= m - 2; j++)
            cac[i][j] = (cac[i][j - 1] + f[i - 1][j]) % mod, f[i][j] = (f[i][j - 1] + cac[i][j]) % mod;
    }
    for (register int i = 1; i <= n; i++)
        for (register int j = 0; j <= m - 2; j++)
            g[i][j] = (g[i - 1][j] + f[i][j]) % mod;
    memset(cac, 0, sizeof(cac));
    for (register int i = 1; i < n; i++)
        for (register int j = 1; j <= m - 2; j++)
            cac[i][j] = (cac[i][j - 1] + g[i][j - 1]) % mod, h[i][j] = (h[i][j - 1] + cac[i][j] + g[i][j - 1]) % mod;
    long long answer = 0;
    for (register int i = 1; i <= n; i++)
        for (register int j = 0; j <= m - 2; j++)
            answer = (answer + (m - j - 1) * g[i][j] % mod * (1 + h[n - i][j])) % mod;
    write(answer), putch('\n');
    return 0;
}
```


---

## 作者：legendgod (赞：3)

[CF295D Greg and Caves](https://www.luogu.com.cn/problem/CF295D)

> 首先说一下这题很值得做。

> $Update \times n\ on \ 2021.6.30$。

首先题目我们就直接分成两个三角形来写。

之后发现，其实上一行的具体位置不用知道，因为我们枚举当前的长度是必须 $\ge$ 上一次的长度的，然后其所有可能的位置也是很好算的。

我们就开始 $Dp$，设 $f(i,j)$ 表示从上到下计算到第 $i$ 行，当前行的长度 $\le j$ 的方案数。

很显然，我们考虑每一次找一个长度为 $j$ 的方案数。

$$f(i,j) = \sum_{c = 2} ^ m f(i - 1, c) \times (j - c + 1) + 1$$

注意外面的 $ + 1$ 表示在这边重新开一行。

然后我们考虑计算答案，发现直接通过枚举中间的断点然后两个 $f$ 拼起来是错的。因为存在这样的情况。

![RDiFnx.png](https://z3.ax1x.com/2021/06/30/RDiFnx.png)

那么我们不妨钦定一下中间这一段的长度，之后让两边严格小于即可，同时保证这个长度为 $1$，方案数就是 $f(i, c) - f(i -1, c)$。

然后我们直接暴力枚举计算即可。

$$
\begin{aligned}
\sum_{i = 1} ^ n \sum_{j = i} ^ n \sum_{k =2} ^ m (dp(i, k) - dp(i - 1, k)) \times (dp(n - j + 1, k) - dp(n - j, k)) \times (m - k + 1) \\
\sum_{k = 2} ^ m \sum_{i = 1} ^ n (dp(i, k) - dp(i - 1, k)) \sum_{j = i} ^ n (dp(n - j + 1, k) - dp(n - j, k))\times (m - k + 1) \\
\end{aligned}
$$

但是真的只有这样吗？

在更深的理解意义上，我们思考我们的 $f$ 记录了什么东西。就是顶点在 $1 \sim i$ 的所有情况。

那么我们考虑一下为什么要枚举 $j$，而不是直接计算，这其实是为了钦定中间长度为 $k$ 的部分是 $n - i - j$ 这一段。

> 这边需要更加深刻地理解。

```cpp
#include <bits/stdc++.h>
/*
* @ legendgod
* 纵使前路是无底深渊，下去了也是前程万里
*/
using namespace std;

//#define Fread
#define Getmod

#ifdef Fread
char buf[1 << 21], *iS, *iT;
#define gc() (iS == iT ? (iT = (iS = buf) + fread (buf, 1, 1 << 21, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
#endif // Fread

template <typename T>
void r1(T &x) {
	x = 0;
	char c(getchar());
	int f(1);
	for(; c < '0' || c > '9'; c = getchar()) if(c == '-') f = -1;
	for(; '0' <= c && c <= '9';c = getchar()) x = (x * 10) + (c ^ 48);
	x *= f;
}

#ifdef Getmod
const int hater  = 1e9 + 7;
template <int mod>
struct typemod {
    int z;
    typemod(int a = 0) : z(a) {}
    inline int inc(int a,int b) const {return a += b - mod, a + ((a >> 31) & mod);}
    inline int dec(int a,int b) const {return a -= b, a + ((a >> 31) & mod);}
    inline int mul(int a,int b) const {return 1ll * a * b % mod;}
    typemod<mod> operator + (const typemod<mod> &x) const {return typemod(inc(z, x.z));}
    typemod<mod> operator - (const typemod<mod> &x) const {return typemod(dec(z, x.z));}
    typemod<mod> operator * (const typemod<mod> &x) const {return typemod(mul(z, x.z));}
    typemod<mod>& operator += (const typemod<mod> &x) {*this = *this + x; return *this;}
    typemod<mod>& operator -= (const typemod<mod> &x) {*this = *this - x; return *this;}
    typemod<mod>& operator *= (const typemod<mod> &x) {*this = *this * x; return *this;}
    int operator == (const typemod<mod> &x) const {return x.z == z;}
    int operator != (const typemod<mod> &x) const {return x.z != z;}
};
typedef typemod<hater> Tm;
#endif

template <typename T,typename... Args> inline void r1(T& t, Args&... args) {
    r1(t);  r1(args...);
}

//#define int long long
const int maxn = 2e3 + 5;
const int maxm = maxn << 1;

int n, m;

Tm f[maxn][maxn], g[maxn][maxn];

signed main() {
//    freopen("S.in", "r", stdin);
//    freopen("S.out", "w", stdout);
    int i, j;
    r1(n, m);
    for(i = 2; i <= m; ++ i) f[1][i] = 1;
    for(i = 2; i <= n; ++ i) {
        Tm x(0), y(0);
        for(j = 2; j <= m; ++ j) {
            x += f[i - 1][j];
            y += f[i - 1][j] * j;
            f[i][j] = x * (j + 1) - y + 1;
        }
    }
    for(int c = 2; c <= m; ++ c) {
        for(i = n; i; -- i) {
            g[i][c] = g[i + 1][c] + (f[n - i + 1][c] - f[n - i][c]);
        }
    }
    Tm ans(0);
    for(int c = 2; c <= m; ++ c) {
        for(i = 1; i <= n; ++ i) {
            ans += (f[i][c] - f[i - 1][c]) * g[i][c] * (m - c + 1);
        }
    }

    printf("%d\n", ans.z);

	return 0;
}

```


---

## 作者：xtx1092515503 (赞：2)

# [Portal](https://www.luogu.com.cn/problem/CF295D)

首先一眼就能看出一个DP状态：

我们设 $f_{i,j,k}$ 表示填了 $i$ 行（即这个洞占了 $i$ 行），且第 $i$ 行的洞是在区间 $[j,k]$，且这 $i$ 行中都有 $S_{i-1}\subseteq S_i$ 的方案数。

则我们有显然的转移方程：

$$f_{i,j,k}=\sum\limits_{[l,r]\subseteq[j,k]}f_{i-1,l,r}$$

显然这个可以被一个二维前缀和优化到 $O(m^2)$ 地从 $f_{i-1}$ 推到 $f_i$。

然后我们发现我们并不关心这个区间 $[j,k]$ 到底在哪——我们只关心它的长度。

于是我们可以轻松消减掉一维。我们设 $f_{i,j}$ 表示填了 $i$ 行，且当前行上洞的长度是 $j$ 的方案数。

则有

$$f_{i,j}=f_{i-1,j}+2\times f_{i,j-1}-f_{i,j-2}$$

使用的是二维前缀和的递推方式。

则我们最终要求出答案。显然它是由两半拼在一起（前一半的区间是递增的，后一半的区间是递减）得到的。

故我们可以得出答案为

$$\sum\limits_{i+j\leq n+1}\sum\limits_{k=2}^mf_{i,k}\times f_{j,k}\times(m-k+1)$$

其中 $(m-k+1)$ 是因为整个 $m$ 的大区间一共可以挖出这么多长度为 $k$ 的小区间。

明显我们在 $j$ 这一维上做一个前缀和即可做到总复杂度为 $O(nm)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,f[2010][2010],res,g[2010][2010];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=2;i<=m;i++)f[1][i]=1;
	for(int i=2;i<=n;i++)for(int j=2;j<=m;j++)(f[i][j]=(0ll+f[i-1][j]+f[i][j-1]*2-f[i][j-2]+mod)%mod);
	for(int i=1;i<=n;i++)for(int j=2;j<=m;j++)g[i][j]=(g[i-1][j]+f[i][j])%mod;
	for(int i=1;i<=n;i++)for(int j=2;j<=m;j++)(res+=1ll*f[i][j]*g[n+1-i][j]%mod*(m-j+1)%mod)%=mod;
	printf("%d\n",res);
	return 0;
} 
```

---

## 作者：daniEl_lElE (赞：1)

考虑 $dp_{i,j}$ 表示行数小于等于 $i$ 且最底下行宽度为 $j$ 的方案数。容易发现一行宽度为 $k$ 时包含了 $k-j+1$ 个上行宽度为 $k$ 的方案。也就是说，$dp_{i,j}$ 到 $dp_{i+1,k}$ 的转移系数为 $k-j+1$。由于我们状态定义是小于等于，所以还需要在所有 $dp$ 值上加一才行（这一行是第一行的方案）。

考虑统计答案，我们强制 $t$ 为最小的满足要求的 $t$，则答案就是 $\sum_{i=1}^n\sum_{j=2}^m(m-j+1)\times(dp_{i,j}-dp_{i-1,j})\times dp_{n-i+1,j}$，也就是说上面强制选正好 $i$ 行，利用差分性质即可计算，而下面只要不超过 $n-i+1$ 即可，同时乘上在 $m$ 中取 $j$ 个的系数。

复杂度是 $O(nm^2)$，并不能通过。

考虑优化转移，容易发现 $dp_{i,j}$ 到 $dp_{i+1,k}$ 的转移系数为 $k-j+1$ 是一个显然的~~卷积~~前缀和形式，运用两次前缀和即可计算，复杂度被优化到了 $O(nm)$，即可通过。

~~当然你也可以将 $f(x)=dp_{i,x}$ 和 $g(x)=x$ 做一个和卷积得到 $h(x)$ 即为 $dp_{i+1,k}$，复杂度就是 $O(nm\log m)$，注意您 MTT 的常数，它的模数是 $10^9+7$。~~

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int dp[2005][2005];
signed main(){
	init();
	int n=read(),m=read();
	for(int i=1;i<=n;i++){
		int sum1=0,sum2=0;
		for(int j=2;j<=m;j++){
			sum1=(sum1+dp[i-1][j])%mod;
			sum2=(sum2+sum1)%mod; 
			dp[i][j]=(sum2+1)%mod;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			ans=(ans+(m-j+1)*(dp[i][j]+mod-dp[i-1][j])%mod*dp[n-i+1][j])%mod;
		}
	}
	print(ans);
	endl();
	return 0;
}

```

---

## 作者：Cry_For_theMoon (赞：1)

[传送门](https://codeforces.com/contest/295/problem/D)

推了好久硬莽竟然莽过了。

最慢点 1.4s，总运行时间 9s（洛谷倒数第二位 3s）...

~~这题评 2600 不过分~~

#### 分析：

把题目里的 $t$ 称作中心行。

首先想到枚举最后 $[l,r]$ 长度 $i$，然后枚举中心行的宽度 $j$（以下默认宽度 $\ge 2$），为了去重，我们钦定，中心行的上一行宽度一定严格小于中心行的宽度。这样，如果有若干个中心行，一定只会在枚举最上面一个中心行的时候被统计到。

我们设 $f(i,j)$ 表示第一行的宽度为 $i$，接下来宽度单调不上升，一共 $j$ 行的方案数。显然 $f(i,1)(i\ge 2)=1$，考虑 $j>1$ 的转移：

$$
f(i,j)=\sum_{k=2}^{i}(i-k+1)f(k,j-1)
$$

拆系数变为 $(i+1)$ 和 $-k$，那么我们维护 $j$ 固定时 $\sum f(i,j)$ 和 $\sum i\,\times\,f(i,j)$ 这两个前缀和就可以在 $O(nm)$ 的时间内计算 $f$。$g$ 的转移类似：

$$
g(i,j)=\sum_{k=2}^{i-1}(i-k+1)f(k,j)
$$

当我们维护完了当前 $j$ 的前缀和，就可以计算出当前所有的 $f(i,j)$。

所以我们第一部分 dp 的预处理是 $O(nm)$ 的。

然后考虑最开始的统计答案过程，容易列出这个式子：

$$
ans=\sum_{i=1}^{n}(n-i+1)\sum_{j=2}^{m}(m-j+1)(\,(\sum_{i_1+i_2=i}f(j,i_1)\,\cdot\,g(j,i_2)\,)+f(j,i))
$$

这个式子是 $O(n^2m)$ 的。其中 $i_1,i_2 \ge 1$，同时，为了规避 $i_2=0$ 的时候 $g$ 的定义问题，我们单独考虑 $i_1=i$ 的情况。

考虑交换求和顺序（注意，由于单独考虑 $i_1=i$ 的情况是可以 $O(nm)$ 搞定的，所以从下面开始不再体现在式子里了）：

$$\sum_{j=2}^{m}(m-j+1)\sum_{i=1}^{n}(n-i+1)\sum_{i_1+i_2=i}f(j,i_1)\,\cdot g(j,i_2)$$

注意，由于单独考虑 $i_1=i$ 的情况是可以 $O(nm)$ 搞定的，所以这里不再体现在式子里了。

忽略最外面一层求和，里面的东西可以改变计算方式：

$$
(n+1)\sum_{i_1=1}^{n-1}\sum_{i_2=1}^{n-i_1}f(j,i_1)\,\cdot f(j,i_2)-\sum_{i_1=1}^{n-1}\sum_{i_2=1}^{n-i_1}(i_1+i_2)f(j,i_1)\,\cdot f(j,i_2)
$$

左边的东西可以通过维护 $\sum f(j,i_2)$ 这个前缀和解决。

右边的和式，我们把系数拆分成 $i_1$ 和 $i_2$，对于 $i_1$ 的部分，也可以用 $\sum f(j,i_2)$ 去加速计算。对于 $i_2$ 的部分，另外维护 $\sum i_2\,\cdot\,f(j,i_2)$ 这个前缀和就可以加速计算。

最后一共要维护 $4$ 个前缀和，但是前两个 dp 结束后就不需要了，所以一共只需要两个数组。

时间复杂度 $O(nm)$。

代码异常简短

```
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2010,mod=1e9+7;
ll n,m,ans;
ll f[MAXN][MAXN],g[MAXN][MAXN];
ll sum1[MAXN][MAXN],sum2[MAXN][MAXN];
void predp(){
	rep(j,2,m)f[j][1]=1;
	rep(j,2,m)sum1[j][1]=(sum1[j-1][1]+f[j][1])%mod;
	rep(j,2,m)sum2[j][1]=(sum2[j-1][1]+f[j][1]*j)%mod;
	rep(j,3,m)g[j][1]=(sum1[j-1][1]*(j+1)-sum2[j-1][1]+mod)%mod;
	rep(i,2,n){
		rep(j,2,m)f[j][i]=(sum1[j][i-1]*(j+1)-sum2[j][i-1]+mod)%mod;
		rep(j,2,m)sum1[j][i]=(sum1[j-1][i]+f[j][i])%mod;
		rep(j,2,m)sum2[j][i]=(sum2[j-1][i]+f[j][i]*j)%mod;
		rep(j,3,m)g[j][i]=(sum1[j-1][i]*(j+1)-sum2[j-1][i]+mod)%mod;
	}
	memset(sum1,0,sizeof sum1);
	memset(sum2,0,sizeof sum2);
}
void pre(){
	rep(j,2,m){
		rep(i,1,n)sum1[j][i]=(sum1[j][i-1]+g[j][i])%mod;
		rep(i,1,n)sum2[j][i]=(sum2[j][i-1]+g[j][i]*i)%mod;
	}
}
void solve(){
	rep(j,2,m){
		ll ret=0,s1=0,s2=0;
		//计算s1 
		rep(i,1,n)s1=(s1+f[j][i])%mod;
		rep(i1,1,n-1)s1=(s1+f[j][i1]*sum1[j][n-i1])%mod;
		//计算s2 
		rep(i,1,n)s2=(s2+f[j][i]*i)%mod;
		rep(i1,1,n-1){
			s2=(s2+f[j][i1]*i1%mod*sum1[j][n-i1])%mod;
			s2=(s2+f[j][i1]*sum2[j][n-i1])%mod;
		}
		ret=(s1*(n+1)-s2+mod)%mod;
		ans=(ans+ret*(m-j+1))%mod;
	}
	cout<<ans<<endl;
}
int main(){
	cin>>n>>m;
	predp();	
	pre();
	solve();
	return 0;
}
```

---

## 作者：chenxia25 (赞：1)

**[Portal]( https://www.luogu.com.cn/problem/CF295D )**

我们考虑将整个洞分成两半，一半递增，一半递减。我们分别 DP 求值，最后合并。

显然上下半是对称的。。我们考虑 $dp_{i,l,r}$ 表示前 $i$ 行递增，第 $i$ 行区间为 $l,r$ 的方案数。然后你发现这个空间就炸了。进一步发现，$r-l+1$ 相等的一些 $[l,r]$ 是等价的，于是我们只记录区间长度。于是 $dp_{i,j}$。

转移方程（上面空和不空，不空枚举长度）：
$$
dp_{i,j}=\sum_{k=2}^j(j-k+1)dp_{i-1,k}+1
$$
直接算是三方的，考虑将 $j-k+1$ 拆开得到 $j+1$ 和 $-k$。那么我们只需要维护 $dp_{i,j}$ 的前缀和，和 $-j\cdot dp_{i,j}$ 的前缀和即可平方。

然后我们要做的是求答案。考虑枚举最长的那行和那行的长度，平方？你会发现有重复，因为最长的那行后可能有多个。那怎么办呢？注意到它们长得像一个火箭筒一样，我们枚举极大最长行区间 instead of 最长行。那这样就是三方的了啊。为了优化，我们把式子写出来然后推。
$$
\begin{aligned}ans&=\sum_{i=1}^n\sum_{j=i}^n\sum_{k=2}^m(dp_{i,k}-dp_{i-1,k})(dp_{n-j+1,k}-dp_{n-j,k})\\&=\sum_{k=2}^m\sum_{i=1}^n(dp_{i,k}-dp_{i-1,k})\sum_{j=i}^n(dp_{n-j+1,k}-dp_{n-j,k})\end{aligned}
$$
这样移一下 $\sum$，然后可以将最后一个 $j$ 的 $\sum$ 给后缀和预处理一下，就是平方了。

感觉这种基础的 DP 优化还算是我比较行的一项？其他大概就一无是处了吧

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
const int N=2000,M=N;
int n,m;
int dp[N+1][M+1];
int Sum[N+1][M+1],Sumk[N+1][M+1];
int sum[N+2];
int main(){
	cin>>n>>m;
	for(int i=2;i<=m;i++)dp[1][i]=1,Sum[1][i]=(Sum[1][i-1]+dp[1][i])%mod,Sumk[1][i]=(Sumk[1][i-1]-1ll*i*dp[1][i])%mod;
	for(int i=2;i<=n;i++)for(int j=2;j<=m;j++){
		dp[i][j]=(1ll*(j+1)*Sum[i-1][j]+Sumk[i-1][j]+1)%mod;
		Sum[i][j]=(Sum[i][j-1]+dp[i][j])%mod;
		Sumk[i][j]=(Sumk[i][j-1]-1ll*j*dp[i][j])%mod;
	}
	int ans=0;
	for(int k=2;k<=m;k++){
		for(int j=n;j;j--)sum[j]=(1ll*sum[j+1]+dp[n-j+1][k]-dp[n-j][k])%mod;
		for(int i=1;i<=n;i++)(ans+=1ll*(m-k+1)*(dp[i][k]-dp[i-1][k])%mod*sum[i]%mod)%=mod;
	}
	cout<<(ans+mod)%mod;
	return 0;
}
```


---

