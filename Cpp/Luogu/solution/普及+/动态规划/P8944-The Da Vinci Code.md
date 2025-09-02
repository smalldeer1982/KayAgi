# The Da Vinci Code

## 题目背景

> 圣杯在罗斯琳教堂下静待。  
> 大师杰作掩映中相拥入眠。  
> 剑刃圣杯守护着她的门宅。  
> 星空下她可安息无碍。

好的题目不需要花里胡哨的背景。

## 题目描述

给定一个长度为 $n$ 的数列 $a$，初始情况下 $a_i=i$。

另有一个取值在 $[1,n]$ 内的随机的整数 $x$，它取 $i$ 的概率为 $b_i$。

接下来进行 $k$ 次操作，每次**均匀随机**地选两个 $[1,n]$ 中的整数 $i,j$（允许 $i=j$），交换 $a_i,a_j$ 的值（如果 $i=j$ 则什么也不干）。问最后 $x$ 在位置 $i$ 上的概率，你需要对所有 $1\leq i\leq n$ 求出答案。你需要输出答案模 $3221225473$ 的值。

我们定义 $x$ 在位置 $i$ 上指 $a_i=x$。

## 说明/提示

#### 【样例解释】

对于样例 #1：

$b$ 数组为 $\{2134949164 ,1086276310\}$，操作 $9$ 次后 $x$ 在两个位置的概率均为 $\dfrac12$。

对于样例 #2：

$b$ 数组为 $\{1863763622,1043615898,1055155266,1556793106,1763540175,1239801170,1141007183\}$。

#### 【数据范围】
对于 $100\%$ 的数据：

* $2\leq n\leq2\times10^7$，$0\leq k,seed<2^{64}$。
* $1<b_i<3221225473$，$\sum\limits_{i=1}^n b_i\equiv 1\pmod{3221225473}$。
* 数据保证 $1<b_n<3221225473$ 且 $3221225473$ 是质数。

---

**本题采用捆绑测试**。

| $\text{Subtask}$ |$n\le$|$k\le$|分值|
|:-:|:-:|:-:|:-:|
|$0$|$2$|$2^{64}-1$|$1$|
|$1$|$5$|$5$|$4$|
|$2$|$200$|$200$|$6$|
|$3$|$200$|$2^{64}-1$|$9$|
|$4$|$2000$|$2000$|$7$|
|$5$|$2\times10^7$|$1$|$5$|
|$6$|$10^6$|$10^6$|$8$|
|$7$|$2\times10^7$|$10^7$|$10$|
|$8$|$10^6$|$2^{64}-1$|$15$|
|$9$|$2\times10^7$|$2^{64}-1$|$35$|

## 样例 #1

### 输入

```
2 9 998244353
```

### 输出

```
2684354563
```

## 样例 #2

### 输入

```
7 3 123456789
```

### 输出

```
24313281849
```

## 样例 #3

### 输入

```
10 9000000000000000000 1000000000000000000
```

### 输出

```
20026214895
```

## 样例 #4

### 输入

```
4 0 123456789
```

### 输出

```
12357556560
```

# 题解

## 作者：cyffff (赞：7)

[$\text{Link}$](https://www.luogu.com.cn/problem/P8944)

和官方题解不同的解释方法。
## 题意
有一个排列 $a_i=i$。有 $k$ 次操作，每次操作均匀随机选取 $i,j\in[1,n]$，交换 $a_i,a_j$。$x$ 在 $[1,n]$ 中以 $b_i$ 为权随机，求 $k$ 次操作后 $x=a_i$ 的概率。对质数 $3221225473$ 取模。

$n\le 2\times 10^7$，$k<2^{64}$。
## 思路
交换 $a_i,a_j$ 和交换 $b_i,b_j$ 是相同的。

考虑进行一次操作后 $b_i$ 的期望。用总和除以方案数求。总方案为 $n^2$，其中有 $n^2-2n$ 种与 $b_i$ 无关。剩下的 $b_i$ 与 $b_j,j\in[1,n]$ 交换各两种。

$$b_i\gets \dfrac{(n^2-2n)b_i+2\sum b}{n^2}$$

注意到 $\sum b=1$。

$$b_i\gets \dfrac{(n-2)}{n}b_i+\dfrac{2}{n^2}$$

我们定义 $f(x)=\dfrac{(n-2)}nx+\dfrac{2}{n^2}$，$f^{(k)}(x)=f(f^{(k-1)}(x))$，则最终 $b_i$ 等于 $f^{(k)}(b_i)$。我们只需要求出 $f^{(k)}(x)$ 的解析式，将每个 $b_i$ 代入即可。

显然，$f^{(k)}(x)$ 也是一次函数，我们设 $f(x)=px+q$，归纳可得 $f^{(k)}(x)=p^kx+q(\sum_{i=0}^{k-1}p^i)$，我们所需的只有求逆元，等比数列求和，写个快速幂即可。注意特判 $k=1$。

时间复杂度 $O(n+\log\bmod)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
namespace IO{//by cyffff
	
}
typedef unsigned int uint;

const uint mod = 3221225473u;
const int N = 20000010;

ull seed;

ull getnext() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

uint rd(uint l, uint r) {
	return getnext() % (r - l + 1) + l;
}

int n;
ull k;
uint b[N];

inline uint qpow(uint a,uint b){
	uint res=1;
	while(b){
		if(b&1) res=(ull)res*a%mod;
		a=(ull)a*a%mod;
		b>>=1;
	}
	return res;
}
//bi=(n-2)/nbi+2/n^2
ull ans;
int main() {
	n=read(),k=read(),seed=read();
	ull sum = 0;
	for (int i = 1; i < n; ++ i) b[i] = rd(2u, mod - 1), (sum += b[i]) %= mod;
	b[n] = mod + 1 - sum;
	uint in=qpow(n,mod-2),in2=(ull)in*in%mod;
	uint k1=(ull)(n-2)*in%mod,b1=(ull)2*in2%mod;
	uint k2,b2;
	if(k==1){k2=k1,b2=b1;}
	else{
		uint ki=qpow(((ull)k1%mod+mod-1)%mod,mod-2);
		k2=qpow(k1,k%(mod-1)),b2=((ull)k2+mod-1)%mod*ki%mod*b1%mod;
	}
	for(int i=1;i<=n;i++)
		b[i]=((ull)k2*b[i]%mod+b2)%mod,ans^=(ull)b[i]*i;
	write(ans);
	flush();
}
```
再见 qwq~

---

## 作者：Register_int (赞：3)

upd：转移方程写反了，感谢指出。

概率 $dp$。

设 $dp_{i,0}$ 表示 $i$ 次操作后任意一个位置上的数在原位的概率，$dp_{i,1}$ 表示在不原位的概率。通过直接计算出符合要求的交换方案数，可以得到转移方程如下：

$$dp_{i,0}=\dfrac{n^2-2n+2}{n^2}dp_{i-1,0}+\dfrac{2n-2}{n^2}dp_{i-1,1}$$
$$dp_{i,1}=\dfrac2{n^2}dp_{i-1,0}+\dfrac{n^2-2}{n^2}dp_{i-1,1}$$

使用矩阵快速幂可以优化到 $O(\log k)$，最终答案 $ans_i=b_idp_{k,0}+(1-b_i)dp_{k,1}$。

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef unsigned uint;
typedef long long ll;

const uint mod = 3221225473u;

ull seed;

inline 
ull getnext() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}

inline 
uint randint(uint l, uint r) {
    return getnext() % (r - l + 1) + l;
}

inline 
ull inv(ull b, ull p = mod - 2) {
    ull res = 1;
    while (p) {
        if (p & 1) res = res * b % mod;
        b = b * b % mod, p >>= 1;
    }
    return res;
}

struct matrix {
    ull a[2][2];
    matrix(ull k = 0) { a[0][0] = a[1][1] = k, a[1][0] = a[0][1] = 0; }
    ull* operator [] (const int k) { return a[k]; }
    matrix operator * (const matrix &rhs) const {
        matrix res = 0;
        for (int k = 0; k < 2; k++) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) res[i][j] = (res[i][j] + a[i][k] * rhs.a[k][j] % mod) % mod;
            }
        }
        return res;
    }
} dp, base;

inline 
matrix qpow(matrix b, ull p) {
    matrix res = 1;
    while (p) {
        if (p & 1) res = res * b;
        b = b * b, p >>= 1;
    }
    return res;
}

ull n, k, x;

ull b, sum, ans;

int main() {
    scanf("%llu%llu%llu", &n, &k, &seed), x = inv(n * n % mod) % mod;
    dp[0][1] = 2 * x % mod, dp[1][1] = mod + 1 - dp[0][1];
    dp[1][0] = (2 * n - 2) % mod * x % mod, dp[0][0] = mod + 1 - dp[1][0];
    dp = qpow(dp, k);
    for (int i = 1; i < n; i++) {
        b = randint(2, mod - 1), sum = (sum + b) % mod;
        ans ^= (b * dp[0][0] % mod + (mod + 1 - b) * dp[0][1] % mod) % mod * i;
    }
    printf("%llu", ans ^ ((mod + 1 - sum) * dp[0][0] % mod + sum * dp[0][1] % mod) % mod * n);
}
```

---

## 作者：myyyIisq2R (赞：1)

## P8944 The Da Vinci Code 题解

换 $a_i$ 和换 $b_i$ 等价，所以我们可以考虑对 $b_i$ 进行交换，对于位置的交换一共有 $n^2$ 种，其中只有 $2n$ 种交换是能影响到 $b_i$ 的。我们考虑用期望除以总情况数来计算新概率新交换一轮的 $b_i$，因此每一次交换，$n^2$ 种情况中 $n^2 - 2n$ 种 $b_i$ 不变，剩下 $2n$ 种情况为 $\sum b$。那么 $b_i \Leftarrow \frac{n^2-2n}{n^2}b_i + \frac{\sum b}{n^2}$，由于生成 $b$ 的性质，$\sum b = 1$，则每次交换后 $b_i \Leftarrow \frac{n-2}{n}b_i + \frac{2}{n^2}$，这个递推过程可以用矩阵快速幂优化，最后得到的 $b_i$ 就是答案概率了。

注意取模，因为 $n^2$ 会爆精度。

```cpp
const int MOD = 3221225473;
int seed;

int getnext() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

int rd(int l, int r) {return getnext() % (r - l + 1) + l;}

int n;
const int N = 2e7+5;
int k;
int b[N];
inline int qp(int a,int b)
{
	int res{1};
	while(b)
	{
		if(b & 1)(res *= a) %= MOD;
		(a *= a) %= MOD;
		b>>=1;
	}return res;
}
struct MATRIX
{
	int a[5][5]{};
	inline MATRIX operator * (MATRIX b) const
	{
		MATRIX res;
		for(int i{1};i<=2;i++)
			for(int j{1};j<=2;j++)
				for(int k{1};k<=2;k++)
				(res.a[i][j] += a[i][k] * b.a[k][j] % MOD) %= MOD;
		return res;
	}
	inline void print()
	{
		for(int i{1};i<=2;i++)
		{
			for(int j{1};j<=2;j++) writek(a[i][j]);
			putchar(10);
		}
	}
	inline void buildi(){a[1][1] = a[2][2] = 1;}
};
inline MATRIX qp(MATRIX a,int b)
{
	MATRIX res;
	res.buildi();
	while(b)
	{
		if(b & 1) res = res * a;
		a = a * a;
		b>>=1;
	}return res;
	return res;
}
signed main()
{
	#ifdef LOCAL
	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	#endif
	cin.tie(0);
	n = read(),k = read(),seed = read();
	int sum = 0;
	for (int i = 1; i < n; ++ i) b[i] = rd(2u, MOD - 1), (sum += b[i]) %= MOD;
	b[n] = MOD + 1 - sum;
	MATRIX ori;
	ori.a[1][1] = qp(n,MOD-2) * ((n-2+MOD )% MOD) % MOD;
	ori.a[1][2] = qp(n * n % MOD,MOD-2);
	ori.a[2][2] = 1;
	ori = qp(ori,k);
//	ori.print();
	
	int ans{};
	for(int i{1};i<=n;i++)
	{
		MATRIX now;
		now.a[1][1] = b[i],now.a[2][1] = 2;
		now = ori * now;
		
//		now.print();
		ans ^= now.a[1][1] * i;
	 } 
	 writeln(ans);
	exit(0);
}
```

---

## 作者：Missa (赞：1)

非矩乘做法。理论上常数应该小点，但没跑进最优解第一页。可以当个好写做法看。

首先发现变换后的答案分布仅与变换前的答案分布有关。所以来研究一次变换中单点的变化。

设 $p_u$ 表示 $x$ 在 $u$ 处的概率，考虑选到几个 $u$，容易写出

$$
p_u \gets
\begin{cases}
p'_u & \text{probability } \ \dfrac{(n-1)^2}{n^2} \\
\dfrac{\sum_{i \neq u} p'_i}{n-1} = \dfrac{1-p'_u}{n-1} & \text{probability } \ \dfrac{2(n-1)}{n^2} \\
p'_u & \text{probability } \ \dfrac{1}{n^2} \\
\end{cases}
$$

$p'_u$ 是操作前对应答案。

第一项代表两个下标均不等于 $u$，第二项代表其中之一为 $u$，第三项代表两项均为 $u$。

随便化简一下得到 $p_u \gets \dfrac{2}{n^2} + \dfrac{n-2}{n} p'_u$。看到这种线性递推，应该立刻想到不动点。

[啥是不动点啊？](https://www.cnblogs.com/purplevine/p/16732819.html)

解 $X=\dfrac{2}{n^2} + \dfrac{n-2}{n}X$ 得到 $X=\dfrac{1}{n}$。两边减不动点得到 $p_u - \dfrac{1}{n} = \dfrac{n-2}{n}(p'_u - \dfrac{1}{n})$。然后直接算就行了。$n$ 的逆元一定存在，算起来很方便。

把 $\left(\dfrac{n-2}{n}\right)^k$ 算出来就能 $O(1)$ 求 $ans_i$。总复杂度就是线性。

本来想说也不是 dp 做法的。想了想 dp 与递推关系挺紧密的，而我觉得这偏递推，也就不这么说了。

为什么用 $p'_u$ 是因为显然操作后的一项只与操作一次前有关。

为什么出题人要用这么一个爆 `int` 的膜数和刚好卡着 `long long` 的 $k$ 啊？全开 `unsigned long long` 才过。中间一直只有 $1$ 分一度以为自己错得离谱。

```cpp
#include <cstdio>
#include <assert.h>
#define LL unsigned long long
using namespace std;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef long long ll;
const uint mod = 3221225473u;
const int N = 20000010;
LL qpow(LL a, ull b){
    long long ans = 1ll;
    for(; b; b >>= 1) {if(b & 1) ans = 1ll * ans * a % mod; a = 1ll * a * a % mod;}
    return ans;
}
LL inv(LL n) {return qpow(n, mod-2);}
ull seed;
ull getnext() {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;
    return seed;
}
uint rd(uint l, uint r) {
    return getnext() % (r - l + 1) + l;
}
int n; ull k; uint b[N];
int main() {
    scanf("%d%llu%llu", &n, &k, &seed);
    ull sum = 0;
    for (int i = 1; i < n; ++ i) b[i] = rd(2u, mod - 1), (sum += b[i]) %= mod;
    b[n] = mod + 1 - sum;
    LL ans = 0;
    LL invn = inv(n), s = qpow(invn * (n-2) % mod, k);
    for(int i = 1; i <= n; i++) {
        LL t = (long long)b[i] + mod - invn; t %= mod;
        t = t * s % mod;
        t += invn; t %= mod;
        ans ^= (t * i);
    }
    printf("%lld\n", ans);
}
```

---

## 作者：JackMerryYoung (赞：1)

# 前言

较为基础的概率 DP, 但是被题面搞傻了所以不会。

# 正文

设 $f_{i, 0}$ 为第 $i$ 次操作之后这个数仍然在原位的概率，$f_{i, 1}$ 为第 $i$ 次操作之后这个数不在原位的概率。

那么总共有 $N^2$ 种可能，有 $2$ 种可能 $i, j$ 相同，所以第一个转移方程为：

$$
f_{i, 0} = \frac{2}{N^2} f_{i - 1, 0} + \frac{N^2 - 2}{N^2} f_{i - 1, 1}
$$

那么来考虑第二类，~~根据容斥原理~~排除一类剩下 $N - 1$，有两个变量，多排除了一个重合的所以是 $(N - 1)^2 + 1$，于是可知第二个方程为：

$$
f_{i, 1} = \frac{(N - 1)^2 + 1}{N^2} f_{i - 1, 0} + \frac{2N - 2}{N^2} f_{i - 1, 1}
$$

可惜无法通过，考虑优化。

我们发现四个项前面系数是常数，所以可以使用矩阵快速幂优化 DP. 复杂度为 $\mathcal{O}(\log_2 K)$，可以通过。

# 后言

感谢出题人出的 DP 题目！

---

