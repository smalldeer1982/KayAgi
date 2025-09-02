# Matrix Rank (Hard Version)

## 题目描述

这是该问题的困难版本。两种版本的唯一区别在于 $k$ 的约束条件。只有在解决了所有版本的问题后，才能进行 Hack。

给定整数 $n$、$p$ 和 $k$。保证 $p$ 是一个质数。

对于每个 $r$ 从 $0$ 到 $k$，求在模 $p$ 的整数域 $^\dagger$ 上，秩 $^\ddagger$ 恰好为 $r$ 的 $n \times n$ 矩阵 $A$ 的个数。由于这些值可能很大，你只需要输出它们对 $998\,244\,353$ 取模的结果。

$^\dagger$ [https://en.wikipedia.org/wiki/Field\_(mathematics)](https://en.wikipedia.org/wiki/Field_(mathematics))

$^\ddagger$ [https://en.wikipedia.org/wiki/Rank\_(linear\_algebra)](https://en.wikipedia.org/wiki/Rank_(linear_algebra))

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 3```

### 输出

```
1 49 294 168```

## 样例 #2

### 输入

```
1 51549919 2```

### 输出

```
1 51549918 0```

# 题解

## 作者：xkcdjerry (赞：9)

前置知识：[CF1916H1 的式子](https://www.luogu.com.cn/blog/298051/solution-cf1916h1)

可选知识：[线性求任意数逆元](https://www.cnblogs.com/value0/p/17737873.html#%E4%B9%98%E6%B3%95%E9%80%86%E5%85%83-2)

首先我们把前面的式子再拉出来，这次把 $k$ 视作变量其他的均视为常量：

$$T(k)=\dfrac{\prod_{j=0}^{k-1}{(p^n-p^j)^2}}{\prod_{j=0}^{k-1}{p^k-p^j}}$$

这样比较难看，分离分母和分子有：

$$Num(k)=\prod_{j=0}^{k-1}{(p^n-p^j)^2}$$
$$Dem(k)=\prod_{j=0}^{k-1}{p^k-p^j}$$

显然，$Dem(k)$ 可以 $O(k)$ 递推，这里只需要处理 $Dem(k)$。

发现难点在于 $Dem(k)$ 转移到 $Dem(k+1)$ 的时候所有的 $p^k$ 都会乘 $p$，导致 $p^k-p^j$ 无法 naive 建立一对一关系。考虑经典错位法：

$$
\begin{aligned}
Dem(k+1)&=\prod_{j=0}^{k} p^{k+1}-p^j\\
&=(p^{k+1}-p^0) \prod_{j=1}^{k} p^{k+1}-p^j\\
&=(p^{k+1}-1) \prod_{j=0}^{k-1} p(p^k-p^j)\\
&=(p^{k+1}-1) p^k \prod_{j=0}^{k-1} (p^k-p^j)\\
&=(p^{k+1}-1) p^k Dem(k)\\

\end{aligned}
$$

即预处理出 $p^0 \sim p^{k+1}$ 就可以 $O(k)$ 递推 $Dem(k)$。

至此，我们已经有了一个 $O(k \log P)$ 的做法，瓶颈在于求逆元：

```c++
#include <cstdio>
#define N 500010
#define P 998244353
#define ll long long
ll n,p,k;
ll mpow(ll x,ll y)
{
	ll ans=1;
	for(y%=P-1,x%=P;y;y>>=1,x=x*x%P)
		if(y&1) ans=ans*x%P;
	return ans;
}
ll pw[N],pn,f[N],g[N];
int main()
{
	scanf("%lld%lld%lld",&n,&p,&k);
	pn=mpow(p,n); g[0]=f[0]=pw[0]=1;
	for(int i=1;i<=k+1;i++) pw[i]=pw[i-1]*p%P;
	for(int i=1;i<=k;i++)
	{
		ll tmp=pn-pw[i-1]+P;
		f[i]=f[i-1]*tmp%P*tmp%P;
	}
	for(int i=1;i<=k;i++) g[i]=(pw[i]-1)*pw[i-1]%P*g[i-1]%P;
	for(int i=0;i<=k;i++) printf("%lld ",f[i]*mpow(g[i],P-2)%P);
}
```

[提交记录](https://codeforces.com/contest/1916/submission/239959558)

可以使用线性求逆元做到 $O(k+\log P)$，注意特判 $Dem(i)=0$ 的情况即可。因为代码较长且大部分重复，故不再赘述代码，仅给出[提交记录](https://codeforces.com/contest/1916/submission/239960133)。

~~加上卡常+快读火车头之后直接[榜一](https://www.luogu.com.cn/record/141723188)，耗时仅 [原最优解](https://www.luogu.com.cn/record/141701007) 的一半左右。~~

---

## 作者：feecle6418 (赞：4)

要算 $n\times n$ 秩为 $k$ 矩阵个数，枚举其张成的子空间。先枚举一组基，个数为 $\prod_{0\le i<k}(p^n-p^i)$；对于每个子空间，有 $\prod_{0\le i<k}(p^k-p^i)$ 组基（有序）可以张成他，所以子空间数量为 $\prod_{0\le i<k}\frac{p^n-p^i}{p^k-p^i}$。在子空间里选 $n$ 个向量，方法数为 $p^{kn}\prod_{0\le i<k}\frac{p^n-p^i}{p^k-p^i}$。

这样会算到秩小于 $k$ 的。设上面算出来的向量组数量为 $f(k)$。

要容斥就要算某个秩为 $j$ 的向量组在算秩为 $i$ 的向量时算的次数，也就是它被包含在几个子空间里。一共有 $\prod_{0\le k<i}\frac{p^n-p^k}{p^i-p^k}$ 个子空间，每个子空间 $\prod_{0\le k<j}\frac{p^i-p^k}{p^j-p^k}$ 个 $j$ 维子空间，所以每个 $j$ 维子空间被算了
$$
f(j,i)
\\
=\prod_{0\le k<i}\frac{p^n-p^k}{p^i-p^k}\prod_{0\le k<j}\frac{p^i-p^k}{p^j-p^k}\prod_{0\le k<j}\frac{p^j-p^k}{p^n-p^k}
\\
=
\prod_{j\le k<i}\frac{p^n-p^k}{p^i-p^k}
$$
次。用该系数 $O(n^2)$ 容斥就能通过 H1。

对于 H2，利用 $p^{ij}=p^{\binom {i+j}2}\div p^{\binom i2}\div p^{\binom j2}$，$f(j,i)$ 可以写成 $A_jB_{i-j}C_i$ 的形式，因此这个容斥可以写成卷积形式，多项式求逆即可。

---

这个做法和官方题解差在哪呢？对比该式和官方题解的式子，有
$$
p^{in}\prod_{0\le k<i}\frac{p^n-p^k}{p^i-p^k}=\sum_{0\le j\le i}\prod_{j\le k<i}\frac{p^n-p^k}{p^i-p^k}\prod_{0\le k<j}\frac{(p^n-p^k)^2}{p^j-p^k}
$$
化简得：
$$
p^{in}\prod_{0\le k<i}\frac{1}{p^i-p^k}=\sum_{0\le j\le i}\prod_{j\le k<i}\frac{1}{p^i-p^k}\prod_{0\le k<j}\frac{p^n-p^k}{p^j-p^k}
$$
最后得到恒等式：
$$
p^{in}=\sum_{0\le j\le i}\prod_{0\le k<j}\frac{(p^n-p^k)(p^i-p^k)}{p^j-p^k}
$$
左边是 $i\times n$ 矩阵个数，右边意义是枚举秩 $j$，先在 $n$ 维空间里选一个 $j$ 维子空间，然后在这个子空间内构造一个满秩 $i\times j$ 矩阵表示原矩阵每行在子空间内坐标。

---

## 作者：_sunkuangzheng_ (赞：4)

当 $k$ 固定时，答案是：

$$\prod\limits_{i=0}^{k-1} \dfrac{(p^n-p^i)^2}{p^k-p^i}$$

具体怎么推的可以去看 H1 题解或者 OEIS，这里只讲一种简单的优化方法。

朴素实现是 $\mathcal O(k^2 \log n)$ 的。考虑上面的分子与 $k$ 无关，显然可以前缀积预处理。我们优化分母的计算。

$$\prod \limits_{i=0}^{k-1} (p^k - p^i) = \prod \limits_{i=0}^{k-1} p^i(p^{k-i}-1) = p^{1+2+3+\ldots+k-1}\prod \limits_{i=1}^{k}(p^i-1)= p^{\frac{k(k-1)}{2}}\prod \limits_{i=1}^{k}(p^i-1)$$

直接算就行了。时间复杂度 $\mathcal O(k \log n)$。


```cpp
/**
 *    author: sunkuangzheng
 *    created: 02.01.2024 14:03:39
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 5e5+5,mod = 998244353;
using namespace std;
int T,p,k,pw[N],K,g[N];ll n;
int qp(int a,ll b){
    int r = 1;
    for(;b;b >>= 1,a = 1ll * a * a % mod) if(b & 1) r = 1ll * r * a % mod;
    return r;
}void los(){
    cin >> n >> p >> K,pw[0] = 1,n %= mod - 1;int rnm = qp(p,n);
    pw[1] = 1ll * (rnm - qp(p,0) + mod) * (rnm - qp(p,0) + mod) % mod;
    for(int i = 2;i <= K;i ++) pw[i] = 1ll * pw[i - 1] * (rnm - qp(p,i-1) + mod) % mod * (rnm - qp(p,i-1) + mod) % mod;
    int prod = 1;
    for(int k = 0;k <= K;k ++){
        cout << 1ll * pw[k] * qp(1ll * prod * qp(p,1ll * (k - 1) * k / 2) % mod,mod - 2) % mod << " ",
        prod = 1ll * prod * (qp(p,k+1) - 1) % mod;
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

---

## 作者：wzy2021 (赞：3)

### 前言

这场比赛打得异常痛苦。
虽然场上 H1H2 会做，但是考场上太急了导致脑抽，然后就爆掉了。。。

### 题意

给定 $n$，$p$，$k$。要求：
求有多少个 $n\times n$ 的在 $\bmod p$ 意义下定义的矩阵，使得其秩为 $r$。
将 $r$ 从 $0$ 到 $k$ 分别输出答案，对 998244353 取模。

数据范围：$n \le 5\times10^{18}$，$k \le 5\times 10^5$，$0 \le p < 998244353$。

### 题解

容易想到 dp：$f_{i,r}$ 表示考虑前 $i$ 行的矩阵，秩为 $r$ 的数量。
显然有
$$
f_{i,r} = f_{i - 1,r} \times p^r + f_{i - 1, r - 1} \times (p^n - p^{r - 1})
$$
具体而言，分两种情况：

1. 当前秩不增加，那么这行一定是前面的行向量的组合，因为前面的秩 $r$，所以有 $2^r$ 种方法。
2. 当前秩增加，那么这行一定不是前面的行向量的组合，因为前面的秩为 $r - 1$，所以有 $p^n - p^{r - 1}$ 中选择方法。

那么这样就得到如上转移，最终答案是 $f_{n,0},\cdots,f_{n,k}$。

考虑如何快速求解 $f$ 数组。考虑将 $f$ 数组画在一个二维平面上，等价于：

每次可以从 $(i,r)$ 走到 $(i+1,r)$（称为平走），或者从 $(i,r)$ 走到 $(i + 1, r + 1)$，每次行走带着一定的贡献。

可以发现第 2 种转移一定只有 $r$ 个，且对答案的贡献是确定的，即：

$$
f_{i,r} = g_{r,i-r} \times \Pi_{j=1}^r (p^n - p^{j - 1})
$$

其中，走到 $f_{i,r}$ 需要进行 $i - r$ 次第 1 种转移，那么 $g_{i,r}$ 的意义就明确了。

所以 $g_{i,r}$ 就是在 $1$ 到 $i$ 层种进行若干次（可以为 0）平走，使得总平走的次数恰好为 $r$ 的总贡献，在第 $j$ 层平走的贡献是 $p^j$。
由于有恰好走 $r$ 步，所以考虑生成函数：$G_i(x) = \sum_{r\ge0} f_{i,r}x^r$，

从而可以写出 $G_i(x) = \sum_{j=0}^i \sum_{l\geq0}(p^jx)^l=\sum_{j=0}^i\tfrac{1}{1-p^jx}$，考虑：

$$
G_i(x) = \sum_{j=0}^i\dfrac{1}{1-p^jx}
$$

$$
G_i(px) = \sum_{j=0}^i\dfrac{1}{1-p^j(px)}=\sum_{j=0}^i\dfrac{1}{1-p^{j+1}x}
$$

所以有

$$
(1 - x)G_i(x) = (1 - p^{i+1}x)G_i(px)
$$

对比两边 $r$ 次方系数的：

$$
g_{i,r}- g_{i,r-1}=p^r\times g_{i,r}-p^{i+1}\times p^{r-1} \times g_{i,r-1}
$$

所以就可以得到递推公式：

$$
g_{i,r}=\dfrac{p^{i+r}-1}{p^r-1}\times g_{i,r-1}
$$

所以就得到了通项公式：

$$
g_{i,0}=1,g_{i,r}=\Pi_{j=1}^r\dfrac{p^{i+j}-1}{p^j-1}
$$

从而得到了快速求解 $f$ 的方法：

$$
f_{n,r} = \Pi_{j=1}^{n-r}\dfrac{p^{r+j}-1}{p^j-1} \times \Pi_{j=1}^r (p^n - p^{j - 1})
$$
考虑将 $r$ 从小到大计算，则后者可以直接算，前者考虑分子分母互相抵消后再计算。

然后这样就可以直接过 H1H2 了。

~~~cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int rd() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!('0' <= ch && ch <= '9')) {
		if (ch == '-') f = -1; ch = getchar();
	}
	while ('0' <= ch && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();
	}
	return x * f;
}

void wr(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x >= 10) wr(x / 10); putchar(x % 10 + '0');
}

const int N = 5e5 + 10;
const int mod = 998244353;

int ans[N];

int add (int x) {
	if (x >= mod) x -= mod; else if (x < 0) x += mod;
	return x;
}

int ksm (int x, int y = mod - 2) {
	int res = 1; x = add(x);
	while (y) {
//		cout << y << " " << res << endl;
		if (y & 1) res = 1ll * res * x % mod;
		x = 1ll * x * x % mod; y >>= 1;
	} return res;
}

signed main() {
	int n, p, k; n = rd(); p = rd(); k = rd();
	int res1 = 1, res2 = 1;
	for (int r = 0; r <= min(n,k); ++r) {
		ans[r] = 1ll * res1 * res2 % mod;
		res1 = 1ll * res1 * add(ksm(p, n) - ksm(p, r)) % mod;
		res2 = 1ll * res2 * ksm(ksm(p, r + 1) - 1) % mod * add(ksm(p, n - r) - 1) % mod;
	}
	for (int r = 0; r <= k; ++r) printf ("%d ", ans[r]);
	return 0;
}
~~~

话说，上面最后的式子是可以用找规律的？不清楚了。

---

## 作者：wind_boy (赞：3)

![](https://cdn.luogu.com.cn/upload/image_hosting/21a6bkgn.png?x-oss-process=image/resize,m_lfit,h_280,w_340)

/ll

直接复制样例 OEIS 即可：https://oeis.org/search?q=1+49+294+168+&language=english&go=Search

下面进入次要环节：

（参考了 [wzy2021 的题解](https://www.luogu.com.cn/blog/wang-zhong-yuan/cf1916-goodbye2023-h1h2-ti-xie)）

设 $f_{i,j}$ 表示填完矩阵前 $i$ 行，且前 $i$ 行的秩为 $j$ 的方案.

设 $W:w_1,w_2,\cdots,w_j$ 为前 $i$ 个向量的最大无关组。分两种情况转移：

1. 第 $i+1$ 个行向量可以被前 $i$ 个线性表示，即 $v_i=\prod_{k=1}^j c_kw_k$。由于 $c_k$ 可以取 $[0,p)$ 中的任意整数，且任意两种不同取法所表示的向量不同（否则 $W$ 就线性相关了），因此方案数为 $p^j$。
2. 第 $i+1$ 个行向量不可以被前 $i$ 个线性表示，即加入后矩阵的秩加 $1$。方案数为 $p^n-p^j$。

因此 $f_{i,j}=p^jf_{i-1,j}+(p^n-p^{j-1})f_{i-1,j-1}$。

我们把 $f_{i,j}$ 放到一个平面上，那么 $f_{n,k}$ 就是从 $(0,0)$ 到 $(n,k)$ 的路径的权值和。

容易发现，对于每条路径，其权值必含 $\prod_{i=0}^{k-1}(p^n-p^i)$，因此我们不妨先把这部分的贡献除去。

设 $f_{n,k}=g_{n,k}\prod_{i=0}^{k-1}(p^n-p^i)$。有 $g_{i,j}=p^jg_{i-1,j}+g_{i-1,j-1}$。

我们枚举 $2^j$ 的贡献次数（即这条路径在第 $j$ 列走的步数），有 $g_{i,j}=\sum^{i-1}_{k=0}p^{jk}g_{i-k-1,j-1}$。

设 $g_j(x)=\sum_{i=0}g_{i,j}x^i$ 表示 $g$ 一列的 OGF。$g_{-1}(x)=1$。根据上述转移式子有
$$
\begin{aligned}
g_j(x)&=xg_{j-1}(x)\sum_{k=0}p^{jk}x^k\\
&=\frac{x}{1-p^jx}g_{j-1}(x)\\
&=x^j\prod_{k=0}^{j}\frac1{1-p^kx}
\end{aligned}
$$
因此 $ans_j=[x^{n-j}]\prod_{k=0}^j\dfrac1{1-p^kx}\times\prod_{i=0}^{k-1}(p^n-p^i)$。

直接套用常系数齐次线性递推可以做到 $O(k^2\log n\log k)$，并获得 $0$ 分的好成绩（场上想到这就不会了）。

为方便，我们重新定义 $g_j(x)=\prod_{k=0}^j\dfrac1{1-p^kx}$

观察到 $g_j(x)$ 分母中 $x$ 的系数都是 $p^k$ 的形式，考虑将其错位：
$$
g_j(px)=\prod_{k=0}^j\frac1{1-p^k(px)}=\prod_{k=1}^{j+1}\dfrac1{1-p^kx}
$$
于是有
$$
(1-p^{j+1}x)g_j(px)=(1-x)g_j(x)
$$
对比系数可以得到
$$
p^ig_{i,j}-p^{j+1}\times p^{i-1}g_{i-1,j}=g_{i,j}-g_{i-1,j}
$$
整理得到：
$$
\begin{aligned}
g_{i,j}=\frac{p^{i+j}-1}{p^i-1}g_{i-1,j}\\
=\prod_{k=0}^i\frac{p^{k+j}-1}{p^k-1}
\end{aligned}
$$
因此 $ans_j=\prod_{k=0}^{i-j}\dfrac{p^{k+j}-1}{p^k-1}\times\prod_{k=0}^{j-1}(p^n-p^k)$。

对于前半部分，分子和分母可以互相抵消，最后只剩下 $\prod_{k=0}^{j-1}\dfrac{p^{n-k}-1}{p^k-1}$。维护前缀积即可。

对于右半部分，直接维护前缀积即可。

时间复杂度 $O(k+\log n)$。不理解搬题人搞两个 version 有什么意义。（你把 H1 的 k 调小一点还说得过去~~这样我就可以过了~~）



---

## 作者：Arghariza (赞：2)

q-analog 入门题，竟然没有这个做法。

其实就是 $\mathbb{F}_p^n$ 中大小为 $n$ 的，基底大小为 $r$ 的向量组个数。

考虑加向量的过程，每一步可以选择加/不加进基底，设当前秩为 $i\in [0,r)$：

- 加入基底，也就是线性无关，那么一共有 $p^n-p^i$ 种向量。
- 不加入基底，线性相关，一共有 $p^i$ 种向量。

最后要求基底大小为 $r$，写出生成函数：

$$\text{ans}=\prod\limits_{i=0}^{r-1}(p^n-p^i)\cdot [x^{n-r}]\prod\limits_{i=0}^{r}\frac{1}{1-p^ix}$$

熟悉或者不太熟悉 q-binomial 的同学都知道，后面这个东西其实就是 q-binomial 的生成函数：

$$[x^{n-r}]\prod\limits_{i=0}^r\frac{1}{1-p^ix}=[x^{n-r}]x^{-r}\sum\limits_{i\ge r}\dbinom{n}{r}_px^i=\dbinom{n}{r}_p$$

于是有：

$$\text{ans}=\dbinom{n}{r}_p\prod\limits_{i=0}^{r-1}(p^n-p^i)$$

由于 $n$ 比较大，直接递推算 $n$ 在 q-analog 意义下的下降幂，然后预处理 $[r]!_p$ 的逆元即可做到 $O(k\log P)$ 或者 $O(k)$。

```cpp

// Problem: Matrix Rank (Easy Version)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1916H1
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define eb emplace_back
#define pb pop_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second
#define int long long

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int P = 998244353;
const int N = 5e5 + 5;

int n, p, k, iv;
int pw[N], fc[N], ifc[N];

int qpow(int p, int q) {
	q %= (P - 1);
	int res = 1;
	for (; q; q >>= 1, p = p * p % P)
		if (q & 1) res = res * p % P;
	return res;
}

void init(int lim) {
	fc[0] = pw[0] = 1, iv = qpow(p - 1, P - 2);
	for (int i = 1; i <= lim; i++) {
		pw[i] = 1ll * p * pw[i - 1] % P;
		fc[i] = 1ll * fc[i - 1] * (pw[i] - 1) % P * iv % P;
		if (!fc[i]) { lim = i - 1; break; }
	}
	ifc[lim] = qpow(fc[lim], P - 2);
	for (int i = lim - 1; ~i; i--)	
		ifc[i] = 1ll * ifc[i + 1] * (pw[i + 1] - 1) % P * iv % P;
}

int f(int n) {
	return 1ll * (qpow(p, n) - 1) * iv % P;
}

void solve() {
	cin >> n >> p >> k, init(k + 1);
	cout << 1 << ' ';
	for (int r = 1, s = 1, t = 1; r <= min(n, k); r++) {
		s = 1ll * s * (qpow(p, n) - qpow(p, r - 1) + P) % P;
		t = 1ll * t * f(n - r + 1) % P;
		cout << 1ll * ifc[r] * s % P * t % P << ' ';
	}
	for (int i = n + 1; i <= k; i++) cout << 0 << ' ';
}

bool Med;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：Liuxizai (赞：2)

[My Blog](https://liuxizai.ac.cn/archives/solution-cf1916h2.html)

## Description

给定 $n,p,k$，对于每个 $r\in[0,k]$，求出 $\mathbb{F}_p$ 上有多少个秩为 $r$ 的 $n\times n$ 矩阵。

答案对 $998244353$ 取模。

$n\le 5\times 10^{18},k\le 5\times 10^5,0\le p<998244353$

## Solution

我基本没学过线性代数，如下做法参考 CF 上 [JeanBombeur 的 comment](https://codeforces.com/blog/entry/124138?#comment-1102026)，推导过程可能不严谨。

一个 $n\times n$ 矩阵的秩为 $r$ 也就意味着这个矩阵的所有行向量张成了 $\mathbb F_p^n$ 上的一个 $r$ 维子空间，我们首先对这个子空间计数，考虑确定这个子空间的基。

基由 $r$ 个线性无关的 $n$ 维向量构成。首先确定第一个向量。$\mathbb F_p$ 上的 $n$ 维向量共有 $p^n$ 个，基中向量不能为零向量，所以选取第一个向量的方式共有 $p^n-1$ 种。第二个向量类似，但不能是第一个向量的若干倍，所以共有 $p^n-p$ 中选法。接下来以此类推，后面的向量不能是前面已经选取的向量的线性组合，所以选取 $r$ 个向量的方案数为 $(p^n-p^0)(p^n-p^1)\cdots(p^n-p^{r-1})$。

但是注意基不同却不意味着子空间不同。一个 $r$ 维子空间的基的个数等于选取 $r$ 个线性无关的 $r$ 维向量的方案数，根据上文的分析，这个值等于 $(p^r-p^0)(p^r-p^1)\cdots(p^r-p^{r-1})$。

所以，$\mathbb F_p^n$ 上的 $r$ 维子空间的个数为 $\dfrac{(p^n-p^0)(p^n-p^1)\cdots(p^n-p^{r-1})}{(p^r-p^0)(p^r-p^1)\cdots(p^r-p^{r-1})}$。

接下来，我们要在这个 $r$ 维子空间内选取 $n$ 个向量，并且这 $n$ 个向量仍然张成一个 $r$ 维子空间。这等价于选取一个 $n\times r$ 的矩阵，满足其秩为 $r$，从行秩的角度考虑就是刚才的问题，这个方案数并不好计算，但如果从列秩考虑（矩阵的秩=行秩=列秩，这是线性代数中的结论，也有很多经典的证法），问题就变为了选取 $r$ 个 $n$ 维向量，且这 $r$ 个向量张成一个 $r$ 维子空间的方案数，这显然要求 $r$ 个向量线性无关，方案数在上文已经计算过了。

综上，$\mathbb F_p$ 上秩为 $r$ 的 $n\times n$ 矩阵的个数为 $\dfrac{((p^n-p^0)(p^n-p^1)\cdots(p^n-p^{r-1}))^2}{(p^r-p^0)(p^r-p^1)\cdots(p^r-p^{r-1})}$。

这个分式的上下两部分均可以递推计算，总复杂度视具体实现为 $O(k)$ 或 $O(k\log k)$。

[Submission #239982603](https://codeforces.com/contest/1916/submission/239982603)

---

## 作者：Leasier (赞：1)

考虑一行一行 dp，设 $dp_{i, j}$ 表示前 $i$ 行的秩为 $j$ 的方案数。

初值：$dp_{0, 0} = 1$。

转移分当前行在秩中与否讨论 $dp_{i, j}$：

- 若不在秩中，其必为那 $j$ 行的线性组合，方案数为 $dp_{i - 1, j} p^j$。
- 若在秩中，其必不为那 $j - 1$ 行的线性组合，方案数为 $dp_{i - 1, j - 1} (p^n - p^{j - 1})$。

将两者求和即可得到答案。

答案：$dp_{n, r}$。

但直接做的时间复杂度为 $O(nk)$，显然不能通过。

注意到 dp 转移流程中，每当 $j$ 加一前都会乘上 $p^n - p^j$，方便起见，我们最后乘上即可，写出新的递推式：

- $f_{0, 0} = 1$。
- $f_{i, j} = f_{i - 1, j} p^j + f_{i - 1, j - 1}$。

考虑写出一行的生成函数：

- $F_i(x) = \displaystyle\sum_{j = 0} f_{i, j} x^j$。
- 由递推式可得 $F_i(x) = F_{i - 1}(px) + x F_{i - 1}(x)$。

~~然后就做不动了（~~

考虑写出一列的生成函数：

- $F_i(x) = \displaystyle\sum_{j = 0} f_{j, i} x^j$。
- 考虑枚举**每个 $j$ 在当前列待了多久**，即 $f_{i, j} = \displaystyle\sum_{k = 1}^j f_{i - 1, k - 1} p^{j(j - k)}$，至此是一个明显的卷积形式。
- 进而可得 $F_i(x) = F_{i - 1}(x) \times \dfrac{x}{1 - p^i x}$。
- 展开递归可得 $F_i(x) = x^i \displaystyle\prod_{j = 0}^i \dfrac{1}{1 - p^j x}$。

令 $G_i(x) = \displaystyle\sum_{j = 0} g_{j, i} x^j = \displaystyle\prod_{j = 0}^i \dfrac{1}{1 - p^j x}$，注意到分母中 $x$ 的系数都是 $p^j$ 形式，考虑一个类似**错位相减**的形式：

- $G_i(px) = \displaystyle\prod_{j = 0}^i \dfrac{1}{1 - p^{j + 1} x}$。
- 于是 $G_i(px) (1 - p^{i + 1} x) = G_i(x) (1 - x)$。
- 对照系数可知 $p^j g_{j, i} - p^{i + j} g_{j, i - 1} = g_{j, i} - g_{j, i - 1}$。
- 于是有 $g_{j, i} = g_{j, i - 1} \times \dfrac{p^{i + j} - 1}{p^j - 1}$。

分子分母抵消后可得 $g_{n, i} = \displaystyle\prod_{j = 1}^i \dfrac{p^{n - j} - 1}{p^j - 1}$。

直接计算即可。时间复杂度为 $O(k \log mod)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 998244353;

inline int quick_pow(int x, int p){
	int ans = 1;
	while (p){
		if (p & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline int sub(int x, int y){
	return x - y < 0 ? x - y + mod : x - y;
}

int main(){
	int p, k, x, invp, y = 1, z = 1, ans = 1;
	ll n;
	scanf("%lld %d %d", &n, &p, &k);
	x = quick_pow(p, n % (mod - 1));
	invp = quick_pow(p, mod - 2);
	for (int i = 0; i <= k; i++){
		printf("%d ", ans);
		ans = 1ll * ans * sub(x, y) % mod * (1ll * x * z % mod - 1) % mod;
		y = 1ll * y * p % mod;
		z = 1ll * z * invp % mod;
		ans = 1ll * ans * quick_pow(y - 1, mod - 2) % mod;
	}
	return 0;
}
```

---

## 作者：lupengheyyds (赞：0)

# CF1916H Matrix Rank

直接推式子失败了，于是考虑 dp。

设 $i$ 行 $n$ 列的 $j$ 阶矩阵的方案数为 $f_{i,j}$，则考虑新增一行，总共有 $p^n$ 种方案，由于秩为 $j$，根据线性相关的定义，有 $p^j$ 种方案不会增加秩，所以写出转移方程：

$$
f_{i,j}=f_{i-1,j}p^j+f_{i-1,j-1}(p^n-p^{j-1})
$$

答案就是 $f_{i,0\sim k}$ 这种相邻位置转移的 dp 可以看作路径带权方案数问题，分析发现，对于秩为 $r$ 的答案，$\prod_{i=0}^{n-1}(p^n-p^i)$ 是一定要有的。

然后剩下的位置就是平着走，假设在 $j$ 列走了 $c_j$ 格，则要求 $\sum_{i=0}^nc_i=n-r$，且一旦确定了 $c$，就确定了整个方案。这样我们就可以直接对 $c$ 计数。

这个问题很典型，设第 $i$ 列的生成函数为 $G_i(x)$，得到 $G_i(x)=1+p^ix+p^{2i}x^2+\cdots=\frac1{1-p^ix}$。

于是答案为：

$$
\prod_{i=0}^{n-1}(p^n-p^i)[x^{n-r}]\prod_{i=0}^n\frac1{1-p^ix}。
$$

现在考虑怎么求出最后的生成函数的通项。考虑：


$$
G_i(x)=\prod_i\frac1{1-p^ix}，G(px)=\prod_{i}\frac1{1-p^{i+1}x}
$$

 

做商得：

$$
(1-x)G_i(x)=(1-p^{i+1})G_i(px)
$$

提取第 $s$ 项系数得到：


$$
g_{i,s}-g_{i,s-1}=p^sg_{i,s}-p^{i+1}p^{s-1}g_{i,s-1}
$$

于是得到递推式：

$$
g_{i,s}=\frac{p^{i+s}-1}{p^s-1}g_{i,s-1}
$$

进而得到通向：

$$
g_{i,s}=\prod_{i=1}^r\frac{p^{i+j}-1}{p^j-1}
$$

于是答案为：

$$
\prod_{i=0}^{n-1}(p^n-p^i)\prod_{i=1}^{n-r}\frac{p^{i+j}-1}{p^j-1}
$$

从小到大枚举 $r$，考虑分子分母互相抵消即可。

---

