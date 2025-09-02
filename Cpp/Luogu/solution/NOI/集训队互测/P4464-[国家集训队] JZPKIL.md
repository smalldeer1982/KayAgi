# [国家集训队] JZPKIL

## 题目描述

给定$ n, x, y$，求

$$\sum_{i=1}^{n}\mathrm{gcd}(i,n)^x \mathrm{lcm}(i,n)^y \bmod (10^9+7)$$



## 说明/提示

30%的数据，$x=y$

另30%的数据，$n \le 10^9, x, y \le 100$

100%的数据，$T \le 100, 1 \le n \le 10^{18}, 0 \le x, y \le 3000$

来源：2012集训队互测，by gyz

## 样例 #1

### 输入

```
5
6 0 0
6 0 1
6 1 0
6 1 1
1000000000 50 50```

### 输出

```
6
66
15
126
393442025```

# 题解

## 作者：Soulist (赞：12)

多次查询，每次给定 $n,x,y$，求：

$$\sum_{i=1}^n \gcd(i,n)^x\textrm{lcm}(i,n)^y \pmod {10^9+7}$$

- $T\le 100,1\le n\le 10^{18},x,y\le 3000$

---

$\rm Sol:$

答案是：

$$\sum_{i=1}^n i^y\cdot n^y\gcd(i,n)^{x-y}$$

枚举 $\gcd=d$，忽略 $n^y$ 则有：

$$\begin{aligned}
    &\sum_{d|n} d^x\sum_{j=1}^{\frac{n}{d}}[\gcd(j,\frac{n}{d})=1]j^{y}
    \\&=\sum_{d|n} d^x\sum_{j=1}^{n/d}\sum_{k|j,k|\frac{n}{d}} \mu(k)j^y
    \\&=\sum_{d|n} d^x\sum_{k|\frac{n}{d}}\mu(k) \sum_{k|j} j^y
    \\&=\sum_{d|n} d^x\sum_{k|\frac{n}{d}}\mu(k)k^y \sum_{j=1}^{n/(kd)} j^y
    \\&=\sum_{d|n} d^x \sum_{k|\frac{n}{d}}\mu(k)k^y S_y(\frac{n}{kd})
\end{aligned}$$

我们将 $S_y(\frac{n}{kd})$ 视为关于其的 $y+1$ 次多项式，那么此处有：

$$\begin{aligned}
    &\sum_{d|n} d^x \sum_{k|\frac{n}{d}}\mu(k)k^y \sum_{i=0}^{y+1}f_i (\frac{n}{kd})^i
    \\&=\sum_{i=0}^{y+1}f_i\sum_{d|n} d^x \sum_{k|\frac{n}{d}}\mu(k)k^y(\frac{n}{kd})^i
\end{aligned}$$

注意到后者可以视为 $f,g,h$ 的迪利克雷卷积，令 $f(d)=d^x,g(d)=\mu(d)d^y,h^c(d)=d^c$，这个卷积满足分配律和交换律以及结合律，同时注意到三者均为积性函数，所以卷积结果也是积性函数。

设结果为 $\Z(x)$，于是我们所求为 $\Z(n)$，那么显然有：

1. $\Z(1)=1$
2. $\Z(p)=p^x+p^c-p^y$
3. $\Z(p^k)=f\cdot h^c(p^k)-f\cdot h^c(p^{k-1})\times p^y$

于是只需要考虑 $f\cdot h^c(p^k)$，其为：

$$\sum_{i+j=k} f(p^i)\cdot h^c(p^j)$$

所以通过 MR 进行暴力质因数分解，然后我们 $\mathcal O(\log n)$ 的枚举每个质因子（include 次幂）然后暴力卷积并计算答案即可。

还有一个问题，如何计算自然数幂的和的多项式？

#### 自然数幂和多项式

构造多项式 $G_n(x)=\frac{e^{nx}-1}{1-e^{-x}}$，一堆神仙分析可以得到 $G_n(x)[x^k]$ 就是 $\sum_{i=1}^n i^k$（其实应该是根据 $G_n(x)[x^k]$ 是 $\sum_{i=1}^n i^k$ 推出 $G_n(x)$ 的表达式的...）

将 $G_n(x)$ 裂项成 $\frac{xe^x}{e^x-1}\times \frac{e^{nx}-1}{x}$，前者的 EGF 序列记为 $\{B_0,B_1,B_2...\}$，后者显然是 EGF 序列 $\{\frac{n}{1},\frac{n^2}{2},\frac{n^3}{3}...\}$

所以我们会发现其实有 $G_n(x)[x^k]$ 是这两个数列的二项卷积的结果，所以有：

$$\begin{aligned}
    &G_n[x^k]=\sum_{i+j=k} B_i \frac{n^{j+1}}{j+1}\binom{k}{i}
    \\&= \frac{1}{k+1}\sum_{i=0}^{k} B_i \binom{k+1}{i}n^{k-i+1}
\end{aligned}$$

换而言之如果能够得到伯努利数那么就可以知道自然数幂和多项式

然后只需要递推伯努利数即可。

注意到 $\frac{xe^x}{e^x-1}\times \frac{e^x-1}{x}=e^x$ 所以 $\mathbf{EGF}\{B_0,B_1...\}\times \mathbf{EGF}\{\frac{1}{1},\frac{1}{2}...\}=\mathbf{EGF}\{1,1,1...\}$

所以有：

$$\begin{aligned}
    &\sum_{i+j=k} B_i\times \frac{1}{j+1}\times \binom{k}{i}=1
    \\& \sum_{i}^k B_i\times\binom{k+1}{i}=k+1 
\end{aligned}$$

于是得到 $B_k=1-\sum_{i<k} \frac{B_i}{k+1}\binom{k+1}{i}$

综上，本题复杂度为 $\mathcal O(T\cdot (n^{\frac{1}{4}}\log n+y\log^2 n)+y^2)$


---

然后这道题卡常，你需要尽可能的省略快速幂，如果你是 $\log^3$ 然后还是我这种大常数玩家就会死得非常惨。

然后千万不要写龟速乘，然后挑一个夜深人静的时候交一发，多洗一下脸，没准就过了。

不过我在 darkbzoj 这道题过得非常稳...但是咕咕就死得非常惨

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int __int128
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int M = 3000 + 5 ; 
const int P = 1e9 + 7 ;
int n, fx, fy, fc, maxn, top, cnt, num, tp[M], st[M], w[M], fac[M], inv[M], B[M], f[M] ; 
int mul( int a, int b, int p ) {
	return a * b % p ; 
}
int fpow( int x, int k, int p ) {
	int ans = 1, base = x ; 
	while(k) {
		if(k & 1) ans = mul(ans, base, p) ;
		base = mul(base, base, p), k >>= 1 ; 
	} return ans ; 
}
int sw( int x ) { return ( ( 1ll * rand() << 16ll ) | rand() ) % x + 1 ; }
bool M_R( int p ) {
	if( p == 2 || p == 3 ) return 1 ; 
	if( p == 1 || ( p % 2 == 0 ) ) return 0 ; 
	re int d = p - 1, s = 0 ; while( !( d & 1 ) ) ++ s, d >>= 1 ; 
	rep( i, 0, 5 ) {
		re int a = sw( p - 3 ) + 2 ; 
		re int x = fpow( a, d, p ), y = 0 ;
		for( register int j = 0; j < s; ++ j ) {
			y = mul( x, x, p ) ; if( y == 1 && ( x != 1 ) && x != ( p - 1 ) ) return 0 ;
			x = y ;
		} if( y != 1 ) return 0 ;
	} return 1 ; 
}
int gcd( int x, int y ) {
	return ( x == 0 ) ? y : gcd( y % x, x ) ;
}
int work( int p ) {
	re int k = 2, x = sw(p - 1), y = x, d = 1, c = sw(99997) ;
	for( re int i = 1; d == 1; ++ i ) {
		x = ( mul( x, x, p ) + c ) % p ;
		d = gcd( (x > y) ? x - y : y - x, p ) ;
		if( i == k ) y = x, k <<= 1 ; 
	} return d ; 
}
void Pollard_Rho(int p) {
	if( p == 1 ) return ; 
	if( M_R(p) ) { st[++ top] = p; return ; }
	int x = p ; while( x == p ) x = work(x) ;
	Pollard_Rho(x), Pollard_Rho(p / x) ;
}
int g[M], gg[M], fg[M], fgg[M], fff[M] ; 
int c( int x, int y ) {
	if( x < y ) return 0 ;
	return fac[x] * inv[y] % P * inv[x - y] % P ;  
}
signed main()
{
	srand(time(NULL)) ;
	int T = gi() ; maxn = 3002 ; B[0] = 1, fac[0] = inv[0] = 1 ; 
	rep( i, 1, maxn ) fac[i] = fac[i - 1] * i % P, inv[i] = fpow( fac[i], P - 2, P ) ;
	rep( i, 1, maxn ) {
		for( re int j = 0; j < i; ++ j ) B[i] = ( B[i] - c(i + 1, j) * B[j] % P + P ) % P ; 
		B[i] = B[i] * fpow( i + 1, P - 2, P ) % P, ++ B[i] ;  
	}
	while( T-- ) {
		n = gi(), fx = gi(), fy = gi() ; int k = fy ; top = 0 ; 
		for( re int i = 0; i <= k; ++ i ) f[k - i + 1] = B[i] * c(k + 1, i) % P * fpow( k + 1, P - 2, P ) % P ; 
		Pollard_Rho(n), sort(st + 1, st + top + 1) ; cnt = 0 ; 
		rep( i, 1, top ) {
			if( st[i] != st[i - 1] ) tp[++ cnt] = st[i] ; 
			++ w[cnt] ; 
		} int Ans = 0 ; 
		rep( j, 1, cnt ) fg[j] = fpow( tp[j], fx, P ), fff[j] = fpow(tp[j], fy, P) ; 
		for( re int ic = 0; ic <= k + 1; ++ ic ) {
			int ans = 1 ;
			for( re int j = 1; j <= cnt; ++ j ) {
				int tk = w[j], qwq = 0, de = 0 ; 
				g[0] = 1, gg[0] = 1 ; fgg[j] = ( !ic ) ? 1 : fgg[j] * tp[j] % P ;  
				int dg = fg[j], dgg = fgg[j] ; 
				for( re int o = 1; o <= w[j]; ++ o ) 
					g[o] = g[o - 1] * dg % P, gg[o] = gg[o - 1] * dgg % P ; 
				for( re int o = 0; o <= w[j]; ++ o )
					qwq = ( qwq + g[o] * gg[(w[j] - o)] % P ) % P ; 
				for( re int o = 0; o < w[j]; ++ o ) 
					de = ( de + g[o] * gg[(w[j] - o - 1)] % P ) % P ; 
				ans = ans * ( qwq - de * fff[j] % P + P ) % P ; 
			}
			Ans = ( Ans + ans * f[ic] % P + P ) % P ; 
		} rep( i, 1, cnt ) w[i] = tp[i] = 0 ;  
		cout << (long long)(Ans * fpow( n, fy, P ) % P) << endl ; 
	}
	return 0 ;
}
```

---

## 作者：Weng_Weijie (赞：9)

这是一道毒瘤题

需要求的是

$$\sum_{i=1}^n(i,n)^x[i,n]^y$$

由 $xy=(x,y)[x,y]$

$$\sum_{i=1}^n(i,n)^{x-y}i^yn^y$$

$n^y$ 是常数，先不考虑

$$\sum_{i=1}^n(i,n)^{x-y}i^y$$

枚举 $\gcd$

$$\sum_{d|n}d^{x-y}\sum_{i=1}^{\frac nd}[(id,n)=d](id)^y$$

把 $d^y$ 提出，顺便套上 Möbius 反演公式

$$\sum_{d|n}d^x\sum_{i=1}^{\frac nd}[\left(i,\frac nd\right)=1]i^y$$

$$\sum_{d|n}d^x\sum_{i=1}^{\frac nd}\sum_{e|\left(i, \frac nd\right)}\mu(e)i^y$$

交换求和顺序

$$\sum_{d|n}d^x\sum_{e|\frac nd}\mu(e)\sum_{i=1}^{\frac n{de}}(ie)^y$$

将 $e^y$ 提出

$$\sum_{d|n}d^x\sum_{e|\frac nd}\mu(e)e^y\sum_{i=1}^{\frac n{de}}i^y$$

众所周知，自然数 $k$ 次幂和是 $k+1$ 次多项式

假设已经求出了这个多项式的系数 $t_i$

$$\sum_{i=1}^ni^k=\sum_{i=0}^{k+1}t_in^i$$

进一步化简

$$\sum_{d|n}d^x\sum_{e|\frac nd}\mu(e)e^y\sum_{i=0}^{y+1}t_i\left(\frac n{de}\right)^i$$

再一次交换求和顺序

$$\sum_{i=0}^{y+1}t_i\sum_{d|n}d^x\sum_{e|\frac nd}\mu(e)e^y\left(\frac n{de}\right)^i$$

后面相当于三个积性函数的狄利克雷卷积

$$F(n)=n^x, G(n)=\mu(n)n^y, H(n)=n^i, Z(n)=(F*G*H)(n)$$

那么卷积后的还是积性函数

于是将 $n$ 分解质因数(使用 Pollard-Rho 算法)

现在只需要计算 $Z(p^k)$

由 Möbius 函数性质，发现只有 $e=1$ 或 $e=p$ 时有意义

枚举 $d=p^q(0\leq q\leq k)$

(1) $e=1$

答案为 $$\sum_{q=0}^kp^{qx}\times p^{(k-q)i}$$

(2) $e=p$

答案为 $$-\sum_{q=0}^{k-1}p^{qx}\times p^y\times p^{(k-q-1)i}$$

得到了 $Z(p^k)$ 的值之后，由积性函数性质可以得到 $Z(n)$

整个问题即可解决

刚才还遗留一个问题，自然数 $k$ 次幂和的多项式怎么求？

这是一个经典问题，可以通过斯特林数，伯努利数，差分，拉格朗日插值等方法求得（我用的是伯努利数）

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <unordered_map>

const int N = 3005;
const int mod = 1E9 + 7;
using LL = long long;
using LD = long double;
int tc, factor[N], ifactor[N], B[N], t[N], x, y;
LL n;
std::unordered_map<LL, int> divisor;
inline int pow(int x, int y, int ans = 1) {
	for (; y; y >>= 1, x = static_cast<LL> (x) * x % mod)
		if (y & 1) ans = static_cast<LL> (ans) * x % mod;
	return ans;
}
inline void reduce(int &x) { x += x >> 31 & mod; }
inline void get_Factor(int R) {
	factor[0] = 1;
	for (int i = 1; i <= R; ++i)
		factor[i] = static_cast<LL> (factor[i - 1]) * i % mod;
	ifactor[R] = pow(factor[R], mod - 2);
	for (int i = R - 1; ~i; --i)
		ifactor[i] = static_cast<LL> (ifactor[i + 1]) * (i + 1) % mod;
}
inline int C(int x, int y) {
	return static_cast<LL> (factor[x]) * ifactor[y] % mod * ifactor[x - y] % mod;
}
inline void get_Bernoulli(int R) {
	B[0] = 1;
	for (int i = 1; i <= R; ++i) {
		int sum = 0;
		for (int j = 0; j < i; ++j)
			reduce(sum -= static_cast<LL> (C(i + 1, j)) * B[j] % mod);
		B[i] = pow(i + 1, mod - 2, sum);
	}
}
inline LL mul(LL x, LL y, LL mod) {
#ifdef ONLINE_JUDGE
	return static_cast<__int128> (x) * y % mod;
#else
	LL ret = (x * y - static_cast<LL> (static_cast<LD> (x) * y / mod + 0.5) * mod) % mod;
	return ret + (ret >> 63 & mod);
#endif
}
inline LL powmod(LL x, LL y, LL mod, LL ans = 1) {
	for (; y; y >>= 1, x = mul(x, x, mod))
		if (y & 1) ans = mul(ans, x, mod);
	return ans;
}
const int primes[] = { 2, 3, 5, 7, 11, 13, 23, 31 };
inline bool prime_test(LL n) {
	LL e = n - 1 >> __builtin_ctz(n - 1); 
	for (int p : primes) if (p < n) {
		for (LL d = e, lst = powmod(p, d, n), now; d != n - 1; d <<= 1, lst = now) {
			now = mul(lst, lst, n);
			if (lst != 1 && lst != n - 1 && now == 1) return false;
		}
		if (powmod(p, n - 1, n) != 1) return false;
	}
	return true;
}
inline void get_Poly(int R) {
	t[0] = 0;
	for (int i = 0; i <= R; ++i)
		t[R + 1 - i] = static_cast<LL> (C(R + 1, i)) * B[i] % mod;
	for (int i = 0; i <= R + 1; ++i)
		t[i] = pow(R + 1, mod - 2, t[i]);
	if (R) ++t[R];
}
inline void pollard_rho(LL n) {
	if (n == 1) return;
	if (prime_test(n)) { ++divisor[n]; return; }
	for (; ; ) {
		int c = std::rand(), k = 1, i = 0;
		LL x = std::rand(), y = x;
		for (; ; ) {
			x = mul(x, x, n) + c;
			LL d = std::__gcd(n, std::abs(x - y));
			if (d > 1 && d < n) { pollard_rho(d), pollard_rho(n / d); return; }
			if (x == y) break;
			if (++i == k) k <<= 1, y = x;
		}
	}
}
inline int G(int i, int p, int k) {
	int ans = 0;
	for (int q = 0; q <= k; ++q)
		reduce(ans += pow(p, (static_cast<LL> (q) * x + static_cast<LL> (k - q) * i) % (mod - 1)) - mod);
	for (int q = 0; q < k; ++q)
		reduce(ans -= pow(p, (static_cast<LL> (q) * x + y + static_cast<LL> (k - q - 1) * i) % (mod - 1)));
	return ans;
}
inline int solve(LL n, int x, int y) {
	divisor.clear(), pollard_rho(n), get_Poly(y);
	int ans = 0;
	for (int i = 0; i <= y + 1; ++i) {
		int p = t[i];
		for (auto pk : divisor)
			p = static_cast<LL> (p) * G(i, pk.first % mod, pk.second) % mod;
		reduce(ans += static_cast<LL> (p) % mod - mod);
	}
	ans = static_cast<LL> (ans) * pow(n % mod, y) % mod;
	return ans;
}
int main() {
	std::ios::sync_with_stdio(0), std::cin.tie(0);
	get_Factor(3001);
	get_Bernoulli(3001);
	std::cin >> tc;
	while (tc--)
		std::cin >> n >> x >> y, std::cout << solve(n, x, y) << '\n';
	return 0;
}
```





---

## 作者：peterwuyihong (赞：4)

题意：多测，求 

$$\sum_{i=1}^n\gcd(i,n)^x\text{lcm}(i,n)^y\bmod(10^9+7)$$

$0\le x,y\le 3000,1\le n\le10^{18},T\le100$

默认 $x/y\rightarrow\lfloor\frac{x}{y}\rfloor$

$$LHS=n^y\sum_{i=1}^n\gcd(i,n)^{x-y}i^y$$

$$n^y\sum_{d|n}d^{x-y}\sum_{i=1}^n[\gcd(i,n)=d]i^y$$

$$n^y\sum_{d|n}d^{x-y}\sum_{i=1}^{n/d}[\gcd(i,n/d)=1]i^y$$

$$n^y\sum_{d|n}d^{x-y}t(\frac n d)$$

$$t(n)=\sum_{i=1}^n[\gcd(i,n)=1]i^y$$

$$=\sum_{i=1}^n\sum_{k|i}\sum_{k|n}\mu(k)i^y$$

$$=\sum_{k|n}k^y\mu(k)\sum_{i=1}^{n/k}i^y$$

自然数幂和你知道是一个多项式，于是设 $\sum_{i=1}^ni^y=\sum_{i=0}^{y+1}a_in^i$

$$t(n)=\sum_{k|n}k^y\mu(k)\sum_{i=0}^{y+1}a_i(n/k)^i$$

$$=\sum_{i=0}^{y+1}a_i\sum_{k|n}k^y\mu(k)(n/k)^i$$

$$LHS=n^y\sum_{d|n}d^{x-y}\sum_{i=0}^{y+1}a_i\sum_{k|(n/d)}k^y\mu(k)((n/d)/k)^i$$

$$=n^y\sum_{i=0}^{y+1}a_i\sum_{d|n}d^{x-y}\sum_{k|(n/d)}k^y\mu(k)((n/d)/k)^i$$

握草，卷王！

你发现后面这一坨东西其实是由 $f(n)=\sum_{d|n}d^{x-y},g(n)=\sum_{d|n}\mu(d)d^y,h(n)=\sum_{d|n}d^i$ 三个东西卷成。

这还是十分 $\texttt{myee}$ 的，然后就大概对于每种因子，枚举次数，然后进行计算。

复杂度巨大多不可算，先嘴着，到时候写写看看是 $O(\text{能过})$ 还是 $O(\text{不能过})$。

写了，是 $O(\text{能过})$。

对于每种因子 $\alpha$，假设它的次数是 $\beta$，那么这个东西是

$$LHS=n^y\sum_{i=0}^{y+1}a_i\sum_{a+b+c=\beta}f(\alpha^a)g(\alpha^b)h(\alpha^c)$$

这个东西中间有一个 $\mu$，要考虑利用好它，分两类讨论后做即可，思考留给读者。

常数较小，可能是用了[这个](https://www.luogu.com.cn/blog/Peterprpr/mu-ban)里面的 Pollard-rho 板子。
```cpp
cmll02不要抓我车/fn/fn/fn
#define maxn 3050
typedef long long i64;
const int p=1e9+7;
template<class _Tp,class _tp>void add(_Tp&x,const _tp& y){((x+=y)>=p)&&(x-=p);}template<class _Tp,class _tp>_Tp Add(_Tp x,const _tp y){add(x,y);return x;}
template<class _Tp,class _tp>void sub(_Tp&x,const _tp&y){((x-=y)<0)&&(x+=p);}template<class _Tp,class _tp>_Tp Sub(_Tp x,const _tp y){sub(x,y);return x;}
template<class _Tp,class _tp>void mul(_Tp&x,const _tp&y){x=1ll*x*y%p;}template<class _Tp,class _tp>_Tp Mul(const _Tp x,const _tp y){return 1ll*x*y%p;}
template<class _Tp,class _tp>_Tp ksm(_Tp a,_tp b){_Tp ans(1);for(;b;b>>=1,mul(a,a))if(b&1)mul(ans,a);return ans;} 
template<class _Tp>_Tp div2(_Tp a){if(a&1)a+=p;return a>>1;}
int B[maxn],C[maxn][maxn],inv[maxn],c[maxn];
void shai(int n){
  rep(i,0,n){
    C[i][0]=C[i][i]=1;
    rep(j,1,i-1)C[i][j]=Add(C[i-1][j],C[i-1][j-1]);
  }
  inv[1]=1;
  rep(i,2,n)inv[i]=Mul(p-p/i,inv[p%i]);
  B[0]=1;
  rep(i,1,n){
    rep(j,0,i-1)add(B[i],Mul(B[j],C[i+1][j]));
    mul(B[i],p-inv[i+1]);
  }
  B[1]++;
}
namespace rho{//https://blog.csdn.net/baiyifeifei/article/details/88074495
    const int MAXP = 1000010;
    const int BASE[] = {2,325,9375,28178,450775,9780504,1795265022};

    long long seq[MAXP];
    int primes[MAXP], spf[MAXP];


    long long gcd(long long a, long long b) {
        int ret = 0;
        while(a) {
            for( ; !(a & 1) && !(b & 1); ++ret, a >>= 1, b >>= 1);
            for( ; !(a & 1); a >>= 1);
            for( ; !(b & 1); b >>= 1);
            if(a < b) swap(a, b);
            a -= b;
        }
        return b << ret;
    }

    inline long long mod_add(long long x, long long y, long long m){
        return (x += y) < m ? x : x - m;
    }

    inline long long mod_mul(long long x, long long y, long long m){
        long long res = x * y - (long long)((long double)x * y / m + 0.5) * m;
        return res < 0 ? res + m : res;
    }

    inline long long mod_pow(long long x, long long n, long long m){
        long long res = 1 % m;
        for (; n; n >>= 1){
            if (n & 1) res = mod_mul(res, x, m);
            x = mod_mul(x, x, m);
        }

        return res;
    }

    inline bool miller_rabin(long long n){
        if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
        if (n < MAXP) return spf[n] == n;

        long long c, d, s = 0, r = n - 1;
        for (; !(r & 1); r >>= 1, s++) {}

        for (int i = 0; primes[i] < n && primes[i] < 38; i++){
            c = mod_pow(primes[i], r, n);
            for (int j = 0; j < s; j++){
                d = mod_mul(c, c, n);
                if (d == 1 && c != 1 && c != (n - 1)) return false;
                c = d;
            }

            if (c != 1) return false;
        }
        return true;
    }

    inline void init(){
        int i, j, k, cnt = 0;

        for (i = 2; i < MAXP; i++){
            if (!spf[i]) primes[cnt++] = spf[i] = i;
            for (j = 0, k; (k = i * primes[j]) < MAXP; j++){
                spf[k] = primes[j];
                if(spf[i] == spf[k]) break;
            }
        }
    }

    long long pollard_rho(long long n){
        while (1){
            long long x = rand() % n, y = x, c = rand() % n, u = 1, v, t = 0;
            long long *px = seq, *py = seq;

            while (1){
                *py++ = y = mod_add(mod_mul(y, y, n), c, n);
                *py++ = y = mod_add(mod_mul(y, y, n), c, n);
                if((x = *px++) == y) break;

                v = u;
                u = mod_mul(u, abs(y - x), n);

                if (!u) return gcd(v, n);
                if (++t == 32){
                    t = 0;
                    if ((u = gcd(u, n)) > 1 && u < n) return u;
                }
            }

            if (t && (u = gcd(u, n)) > 1 && u < n) return u;
        }
    }

    vector <long long> factorize(long long n){
        if (n == 1) return vector <long long>();
        if (miller_rabin(n)) return vector<long long> {n};

        vector <long long> v, w;
        while (n > 1 && n < MAXP){
            v.push_back(spf[n]);
            n /= spf[n];
        }

        if (n >= MAXP) {
            long long x = pollard_rho(n);
            v = factorize(x);
            w = factorize(n / x);
            v.insert(v.end(), w.begin(), w.end());
        }

        sort(v.begin(), v.end());
        return v;
    }
}
int T,x,y;
i64 n;
vector<i64>a;
map<i64,int>b;
int G(int a,int b,int o){
  int ans=0;
  int u=x-o;
  if(u<0)u+=p-1;
  int px_o=ksm(a,u);
  int g=ksm(a,1ll*b*o%(p-1));
  rep(j,0,b)add(ans,g),mul(g,px_o);
  g=ksm(a,((b-1ll)*o+y)%(p-1));
  rep(j,1,b)sub(ans,g),mul(g,px_o);
  return ans;
}
signed main(){
  shai(3030);
  rho::init();
  for(cin>>T;T;T--){
    cin>>n>>x>>y;
    a=rho::factorize(n);
    b.clear();
    for(i64 i:a)b[i]++;
    rep(i,0,y)c[y+1-i]=Mul(C[y+1][i],Mul(ksm(y+1,p-2),B[i]));
    int ans=0;
    rep(i,0,y+1){
      int t=c[i];
      for(pair<i64,int>g:b)mul(t,G(g.first%p,g.second,i));
      add(ans,t);
    }
    cout<<Mul(ksm(int(n%p),y),ans)<<endl;
  }
}
```
小 G 巧，如果想把 $\text{oi-wiki}$ 上的 $\sum_{i=0}^{n-1}i^k$ 变成 $\sum_{i=0}^ni^k$ 只需要把 $B_1$ 自增 $1$ 即可。

彩蛋：《嘴巴是如何炼成的》。

我：算出 $\sum_{i=0}^ni^k$ 的多项式怎么办啊。

$\texttt{myee}$：直接上伯努利数啊。

我：你看看伯努利数公式好不好。

$\texttt{myee}$（盯着看了一会儿）：那你把这里面所有的负号变成正号。

我：为什么是对的？

$\texttt{myee}$：可以证明。

我：证明拿来！

$\texttt{myee}$：我试过，是对的。

我：。。。那么你怎么知道哪些是负号？

$\texttt{myee}$（盯着看了一会儿）：哦，那你把所有 $n+1$ 项二项式展开。

我：。。。。。。

关于只需把 $B_1$ 自增 $1$ 的证明：

$$\sum_{i=0}^{n-1}i^m=\frac 1{m+1}\sum_{k=0}^m\binom{m+1}kB_kn^{m+1-k}$$

$$\sum_{i=0}^{n}i^m=n^m+\frac 1{m+1}\sum_{k=0}^m\binom{m+1}kB_kn^{m+1-k}$$

$$\frac 1{m+1}\sum_{k=0}^m\binom{m+1}k(B_k+[k=1])n^{m+1-k}$$

---

## 作者：b2019dy (赞：4)

莫比乌斯反演+伯努利数  

$$n^y\sum_{i=1}^n(i,n)^{x-y}i^y$$

$$n^y\sum_{d|n}^n\sum_{i=1}^n[(i,n)==d]d^{x-y}i^y$$

$$n^y\sum_{d|n}^nd^x\sum_{i=1}^{\lfloor \frac{n}{d}\rfloor}[(i,\frac{n}{d})==1]i^y$$

$$n^y\sum_{d|n}^nd^x\sum_{i=1}^{\lfloor \frac{n}{d}\rfloor}i^y\sum_{k|(i,\frac{n}{d})}\mu(k)$$

$$n^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)\sum_{k|i}^{{\lfloor \frac{n}{d}\rfloor}}i^y$$

$$n^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)k^y\sum_{i=1}^{{\lfloor \frac{n}{dk}\rfloor}}i^y$$

莫比乌斯反演大概就到这里，下面我们暴力带入伯努利数(接下来所用的都是正伯努利数)，先给出伯努利数公式

$$\sum_{i=1}^ni^m=\frac{1}{m+1}\sum_{k=0}^mC_{m+1}^kB_kn^{m-k+1}$$

$B_k$表示第k个正伯努利数

为了方便接下来的推导，我们令

$$t_k=\frac{1}{m+1}C_{m+1}^kB_k$$

$$\sum_{i=1}^ni^m=\sum_{k=0}^mt_kn^{m-k+1}$$

接下来我们回到推导式，带入伯努利数

$$n^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)k^y\sum_{i=0}^yt_i({\frac{n}{dk}})^{y-i+1}$$

$$\sum_{i=0}^yt_in^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)k^y({\frac{n}{dk}})^{y-i+1}$$

后面是一个积性函数，我们考虑把n唯一分解

$$p_s^{y}\sum_{d|p_s}d^x\sum_{k|\frac{p_s}{d}}\mu(k)k^y(\frac{p_s}{dk})^{y-i+1}$$

$$p_s^{y}\sum_{d|p_s}d^x((\frac{p_s}{d})^{y-i+1}-p^y(\frac{p_s}{dp})^{y-i+1})$$

然后就ok了，贴一份代码，其实第三个循环中的ksm可以全部移出进行优化，可以少掉一个log的复杂度

```cpp
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<ctime>
using namespace std;
const int maxn=3002;
const int mod=1e9+7;
int tot,num;
long long a[105],c[3005][3005],b[3005],vs[3005];
struct que
{
	long long p,v,vs;
	int sum;
}e[105];
long long mul(long long x,long long y,long long z)
{
	return (x*y-(long long)(((long double)x/z*y+0.5))*z+z)%z;
}
long long gcd(long long x,long long y)
{
	if(!y) return x;
	return gcd(y,x%y);
}
long long KSM(long long x,long long n,long long mod)
{
	long long ans=1;
	while(n)
	{
		if(n&1) ans=mul(ans,x,mod);
		x=mul(x,x,mod);
		n>>=1;
	}
	return ans;
}
long long ksm(long long x,long long n)
{
	x%=mod;
	long long ans=1;
	while(n)
	{
		if(n&1) ans=ans*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return ans;
}
bool miller_rabin(long long n)
{
	if(n==2) return 1;
	if(n<2||(!(n&1))) return 0;
	long long m=n-1;
	int t=5,k=0;
	while(!(m&1)) k++,m>>=1;
	while(t--)
	{
		long long a=rand()%(n-1)+1;
		long long x=KSM(a,m,n);
		long long y=0;
		for(int i=1;i<=k;i++)
		{
			y=mul(x,x,n);
			if(y==1&&x!=1&&x!=n-1) return false;
			x=y;
		}
		if(y!=1) return false;
	}
	return true;
}
long long Find(long long n,int c)
{
	long long x,y,d,i=1,k=2;
	x=y=rand()%(n-1)+1;
	while(1)
	{
		i++;
		x=(mul(x,x,n)+c)%n;
		d=gcd((y-x+n)%n,n);
		if(d>1&&d<n) return d;
		if(y==x) return n;
		if(i==k) y=x,k<<=1;
	}
}
void FindFir(long long n,int k)
{
	if(n<=1) return ;
	if(!(n&1))
	{
		a[++tot]=2;
		FindFir(n/2,k);
		return ;
	}
	if(miller_rabin(n))
	{
		a[++tot]=n;
		return ;
	}
	long long d=n;
	while(d>=n) d=Find(n,k--);
	FindFir(d,k),FindFir(n/d,k);
}
void pre()
{
	c[0][0]=1;
	for(int i=1;i<=maxn;i++)
	{
		c[i][0]=1;
		for(int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	b[0]=1;
	for(int i=1;i<=maxn;i++)
	{
		long long sum=0;
		for(int j=0;j<i;j++) sum=(sum+c[i+1][j]*b[j]%mod)%mod;
		b[i]=-sum*ksm(c[i+1][i],mod-2)%mod;
	}
	b[1]=mod-b[1];
}
int main()
{
	srand(time(NULL));
	pre();
	int t;
	scanf("%d",&t);
	while(t--)
	{
		tot=0,num=0;
		long long n,x,y;
		scanf("%lld%lld%lld",&n,&x,&y);
		FindFir(n,100007);
		sort(a+1,a+tot+1);
		for(int i=1;i<=tot;i++)
		{
			if(a[i]==a[i-1]) e[num].v*=a[i],e[num].sum++;
			else num++,e[num].v=e[num].p=a[i],e[num].sum=1;
		}
		for(int i=1;i<=num;i++) vs[i]=ksm(e[i].v,y),e[i].vs=ksm(e[i].p,y);
		long long ans=0;
		for(int k=0;k<=y;k++)
		{
			long long ti=ksm(y+1,mod-2)*c[y+1][k]%mod*b[k]%mod;
			long long v=1;
			for(int i=1;i<=num;i++)
			{
				long long sum=0;
				for(long long d=1,ss=0;ss<=e[i].sum;d*=e[i].p,ss++) sum+=ksm(d,x)*(ksm(e[i].v/d,y-k+1)-e[i].vs*ksm(e[i].v/d/e[i].p,y-k+1)%mod)%mod,sum%=mod;
				sum=vs[i]*sum%mod;
				v=v*sum%mod;
			}
			ans=(ans+(ti*v%mod))%mod;
		}
		printf("%lld\n",(ans%mod+mod)%mod);
	}
}
```

---

## 作者：jun头吉吉 (赞：1)

## 题意
给出 $n,x,y$ 求：
$$\sum_{i=1}^n\gcd(i,n)^x\mathrm{lcm}(i,n)^y\bmod {10^9+7}$$
$n\le 10^{18},x,y\le 3000$，多组询问
## 题解
比较套路，不过还是要 $\rm stO$出题人。
$$
\begin{aligned}
&\sum_{i=1}^n\gcd(i,n)^x\mathrm{lcm}(i,n)^y\\
=&\sum_{i=1}^n\gcd(i,n)^x(in)^y\gcd(i,n)^{-y}\\
=&n^y\sum_{i=1}^ni^y\gcd(i,n)^{x-y}\\
=&n^y\sum_{d|n}\sum_{i=1}^{\frac nd}(id)^yd^{x-y} [\gcd(i,\frac nd)=1]\\
=&n^y\sum_{d|n}\sum_{i=1}^{\frac nd}i^yd^x \sum_{a|\gcd(i,\frac nd)}\mu(a)\\
=&n^y\sum_{a|n}\mu(a)\sum_{d|\frac na}d^x\sum_{i=1}^\frac{n}{da}(ia)^y\\
=&n^y\sum_{a|n}\mu(a)a^y\sum_{d|\frac na}d^x\sum_{i=1}^\frac{n}{da}i^y
\end{aligned}
$$
套路地，考虑设 $T=da$
$$
=n^y\sum_{T|n}\left(\sum_{a|T}\mu(a)a^y\left(\frac{T}{a}\right)^x\right)\left(\sum_{i=1}^\frac nT i^y\right)
$$
考虑后面的一坨可以看做关于 $\frac nT$ 的 $y+1$ 次多项式

设 $F(x)=\sum_{i=1}^xi^y=\sum_{i=0}^{y+1}f_ix^i$
$$\begin{aligned}
=&n^y\sum_{T|n}\left(\sum_{a|T}\mu(a)a^y\left(\frac Ta\right)^x\right)\left(\sum_{i=0}^{y+1}f_i\left(\frac nT\right)^i\right)\\
=&n^y\sum_{i=0}^{y+1}f_i\sum_{T|n}\left(\sum_{a|T}\mu(a)a^y\left(\frac Ta\right)^x\right)\left(\frac nT\right)^i\\
\end{aligned}$$
设 $f_1(d)=\mu(d)d^y,f_2(d)=d^x,f_3(d)=d^i$

$$
=n^y\sum_{i=0}^{y+1}f_i(f_1*f_2*f_3)(n)
$$
显然 $f_1,f_2,f_3$ 都为积性函数,$(f_1*f_2*f_3)$ 同样为积性函数
$$\begin{aligned}
=&n^y\sum_{i=0}^{y+1}f_i\prod_{p^\alpha|n}(f_1*f_2*f_3)(p^\alpha)\\
=&n^y\sum_{i=0}^{y+1}f_i\prod_{p^\alpha|n}\sum_{a+b+c=\alpha}\mu(p^a)p^{ay}p^{bx}p^{ci}\\
=&n^y\sum_{i=0}^{y+1}f_i\prod_{p^\alpha|n}\sum_{a=0}^1\mu(p^a)p^{ay}\sum_{b=0}^{\alpha-a}p^{bx}p^{(\alpha-a-b)i}\\
\end{aligned}
$$
关于系数的求法可以参见[$\color{skyblue}\text{菜鸡の}\mathbb{BLOG}$](https://chen-jia-liang.gitee.io/article/ji-lei-shu.html#_1)

不过需要注意伯努利数的多项式是不包括 $n^y$ 次的，要手动加上去。

剩下的就是考验 $\rm Pollard-Rho$ 的常数了。
## 代码
```cpp
#include<bits/stdc++.h>
#define faster
namespace in{
    #ifdef faster
    char buf[1<<21],*p1=buf,*p2=buf;
    inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    #else
    inline int getc(){return getchar();}
    #endif
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
using std::sort;
using std::swap;
using std::__gcd;
const int N=6e3+100;
const int mod=1e9+7,M=sqrt(mod);
typedef std::mt19937 Random_mt19937;
Random_mt19937 rnd(time(0));
long long factor[50];int cnt=0;
#define ll long long
#define int __int128
int ksm(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1)res=res*a%p;
		a=a*a%p,b>>=1;
	}return res;
}
inline bool mr(ll x,ll b){
	ll k=x-1;
	while(k){
		ll cur=ksm(b,k,x);
		if(cur!=1&&cur!=x-1)return false;
		if((k&1)==1||cur==x-1)return true;
		k>>=1;
	}return true;
}
inline bool prime(ll x){
	if(x==46856248255981ll||x<2)
        return false;
    if(x==2||x==3||x==7||x==61||x==24251)
        return true;
    return mr(x,2)&&mr(x,61);
}
int rd(int x){return ((1ll*rnd()<<16ll)|rnd())%x+1;}
int f(int x,int c,int n){
	return (x*x+c)%n;
}
int PR(int p) {
	int k=2,x=rd(p-1),y=x,d=1,c=rd(99997) ;
	for(int i=1;d==1;i++){
		x=f(x,c,p);
		d=__gcd((x>y)?x-y:y-x,p);
		if(i==k)y=x,k<<=1; 
	}return d;
}
void Gfac(int p) {
	if(p==1)return; 
	if(prime(p)){
		factor[++cnt]=p;
		return;
	}
	int x=p;
	while(x==p)x=PR(x);
	Gfac(x),Gfac(p/x);
}
#undef int
struct modint{
    int x;
    modint(int o=0){x=o;}
    modint &operator = (int o){return x=o,*this;}
    modint &operator +=(modint o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint &operator -=(modint o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint &operator *=(modint o){return x=1ll*x*o.x%mod,*this;}
    modint &operator ^=(int b){
        modint a=*this,c=1;
        for(;b;b>>=1,a*=a)if(b&1)c*=a;
        return x=c.x,*this;
    }
    modint &operator /=(modint o){return *this *=o^=mod-2;}
    modint &operator +=(int o){return x=x+o>=mod?x+o-mod:x+o,*this;}
    modint &operator -=(int o){return x=x-o<0?x-o+mod:x-o,*this;}
    modint &operator *=(int o){return x=1ll*x*o%mod,*this;}
    modint &operator /=(int o){return *this *= ((modint(o))^=mod-2);}
    template<class I>friend modint operator +(modint a,I b){return a+=b;}
    template<class I>friend modint operator -(modint a,I b){return a-=b;}
    template<class I>friend modint operator *(modint a,I b){return a*=b;}
    template<class I>friend modint operator /(modint a,I b){return a/=b;}
    friend modint operator ^(modint a,int b){return a^=b;}
    friend bool operator ==(modint a,int b){return a.x==b;}
    friend bool operator !=(modint a,int b){return a.x!=b;}
    bool operator ! () {return !x;}
    modint operator - () {return x?mod-x:0;}
    modint &operator++(signed){return *this+=1;}
};
modint fac[N],ifac[N],F[N];
modint B[N];
modint C(int n,int m){if(m>n)return 0;return fac[n]*ifac[m]*ifac[n-m];}
signed main(){
	//freopen("JZPKIL.in","r",stdin);
	//freopen("JZPKIL.out","w",stdout); 
    fac[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
    ifac[N-1]=1/fac[N-1];for(int i=N-1;i;i--)ifac[i-1]=ifac[i]*i;
    B[0]=1;
    for(int m=1;m<=3000;m++){
    	modint tmp=0;
    	for(int i=0;i<m;i++)
    		tmp+=C(m+1,i)*B[i];
    	B[m]=-tmp/C(m+1,m);
    }
    int t=1;
	in::read(t);
    while(t--){
    	long long n=970436691605084065;int x= 2312,y= 2977;
    	in::read(n,x,y);
		cnt=0;Gfac(n);
    	sort(factor+1,factor+1+cnt);
    	modint Inv=modint(1)/(y+1);
    	for(int i=0;i<=y;i++)
    		F[y-i+1]=C(y+1,i)*B[i]*Inv;
    	F[y]++;
		modint ans=0;
		F[0]=0;
    	for(int i=0;i<=y+1;i++){
	    	modint res=1;
			for(int l=1;l<=cnt;l++){
	    		int j=l;while(factor[j]==factor[l]&&j<=cnt)j++;
	    		int alpha=j-l;long long p=factor[l]%mod;l=j-1;
	    		modint tmp=0;
	    		
		    		for(int a=0;a<=1;a++){
		    			if(a==0){
		    				for(int b=0;b<=alpha-a;b++)
		    					//tmp+=(modint(p)^b*x)*(1-(modint(p)^i*(alpha-a-b+1)))/(1-(modint(p)^i));
		    					//for(int c=0;c<=alpha-a-b;c++)
		    					//	tmp+=(modint(p)^b*x)*(modint(p)^c*i);
								tmp+=(modint(p)^b*x+i*(alpha-a-b));
						}else{
		    				modint kk=-(modint(p)^y);
		    				for(int b=0;b<=alpha-a;b++)
		    					//tmp+=kk*(modint(p)^b*x)*(1-(modint(p)^i*(alpha-a-b+1)))/(1-(modint(p)^i));
		    					//for(int c=0;c<=alpha-a-b;c++)
		    					//	tmp+=kk*(modint(p)^b*x)*(modint(p)^c*i);
								tmp+=kk*(modint(p)^b*x+i*(alpha-a-b));
		    			}
		    		}
	    		res*=tmp;
	    	}
	    	ans+=res*F[i];
    	}
    	ans*=modint(n%mod)^y;
    	out::write(ans.x);
    	out::putc('\n');
    }
    out::flush();
}
```

---

## 作者：chihik (赞：1)

如果不知道伯努利数的[点这里](https://www.luogu.com.cn/blog/chihik/bo-nu-li-shu)。

$$
\sum_{i=1}^n (i,n)^x[i,n]^y
$$

$$
\sum_{i=1}^n (i,n)^{x-y} \times i^y \times n^y
$$

$$
n^y \sum_{d|n} d ^{x-y} \sum_{i=1}^n [(i,n)=d] i^y
$$

$$
n^y \sum_{d|n} d ^{x} \sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} [(i,\frac{n}{d})=1] i^y
$$

$$
n^y \sum_{d|n} d ^{x} \sum_{i=1}^{\lfloor \frac{n}{d} \rfloor} \sum_{s|(i,\frac{n}{d})}\mu(s)i^y
$$

$$
n^y \sum_{d|n} d ^{x} \sum_{s|\frac{n}{d}}  \mu(s) \sum_{i=1}^{\frac{n}{ds}}(is)^y
$$

$$
n^y \sum_{d|n} d ^{x} \sum_{s|\frac{n}{d}}  \mu(s) s^y \sum_{i=1}^{\frac{n}{ds}}i^y
$$

设 $k_i$ 为 $y$ 次幂展开后 $n^i$ 的系数


$$
n^y \sum_{d|n} d ^{x} \sum_{s|\frac{n}{d}}  \mu(s) s^y \sum_{i=1}^{y+1} k_i (\frac{n}{ds})^i
$$

$$
n^y \sum_{i=1}^{y+1} k_i\sum_{d|n} d ^{x} \sum_{s|\frac{n}{d}}  \mu(s) s^y  (\frac{n}{ds})^i
$$

后面是卷积的形式，记为 $f(i)$。

记 $f_1(n)=n^x,f_2(n)=\mu(n)n^y,f_3(n)=n^i$。


那么 $f=f_1*f_2*f_3$ ，也为一个积性函数,考虑求出 $f(p^w)$ 。

$s$ 只有等于 $1$ 或 $p$ 时 $\mu(s)\not=0$,

当 $s = 1$

$$f(n)=\sum_{d|n} d ^{x} \sum_{s|\frac{n}{d}}  \mu(s) s^y  (\frac{n}{ds})^i$$

$$=n^i\sum_{d|n} d ^{x-i}$$

$$f(p^k)=p^{ki}\sum_{d|p^k}d^{x-i}$$

$$=p^{ki}\sum_{j=0}^k p^{j(x-i)}$$

当 $s=p$

$$f(n)=\sum_{d|n} d ^{x} \sum_{s|\frac{n}{d}}  \mu(s) s^y  (\frac{n}{ds})^i$$

$$=\sum_{d|n} d ^{x} \mu(p) p^y  (\frac{n}{dp})^i$$


$$=-n^i\sum_{d|n} d ^{x-i} p ^{y-i}$$

$$f(p^k)=-p^{ki}\sum_{d|p^k}d^{x-i}p ^{y-i}$$

$$=-p^{ki}\sum_{j=0}^{k-1} p^{j(x-i)}p ^{y-i}$$

$$=-p^{ki+y-i}\sum_{j=0}^{k-1} p^{j(x-i)}$$

然后用 $\text{Pollard~rho}$ 分解质因数后计算。

但计算等比数列和时不能用公式算，也不能暴力算（具体看代码注释）。

~~这份常数极大的代码不开o2会t。~~

```cpp
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define Lint __int128
#define LL long long

template<typename _T>
void Read( _T &x ) {
	x = 0; int f = 1;
	char s = getchar( );
	for( ; s < '0' || s > '9' ; s = getchar( ) ) f = s == '-' ? -f : f;
	for( ; s >= '0' && s <= '9' ; s = getchar( ) ) x = x * 10 + s - '0';
	x *= f;
}
template<typename _T>
void Write( _T x ) {
	if( x < 0 ) putchar( '-' ) , x = -x;
	if( x >= 10 ) Write( x / 10 );
	putchar( x % 10 + '0' );
}

const int MAXN = 3005 , Mod = 1e9 + 7;
LL n;
int t , x , y;

template<typename _T>
_T Quick_pow( _T x , _T po , _T p = Mod ) {
	_T Ans = 1; bool f = 0;
    if( po < 0 ) po = -po , f = 1;
	while( po ) {
		if( po % 2 )
			Ans = (Lint)Ans * x % p;
		x = (Lint)x * x % p;
		po /= 2;
	}
	return f ? Quick_pow( (int)Ans , Mod - 2 ) : Ans;
}
template<typename _T>
_T Gcd( _T x , _T y ) {
	return y == 0 ? x : Gcd( y , x % y );
}
template<typename _T>
_T Abs( _T x ) {
	return x >= 0 ? x : -x;
}
template<typename _T>
_T Inverse( _T x ) {
    return Quick_pow( x , Mod - 2 );
}

template<typename _T>
_T f( _T x , _T a , _T Mod ) {
	return ( (Lint)x * x + a ) % Mod;
}
LL Pollard_rho( LL n ) {
	LL r = rand( ) % ( n - 1 ) + 1;
	LL s = 0 , t = 0 , val , d;
	for( int k = 1 ; k ; k <<= 1 ) {
		val = 1; s = t;
		for( int i = 1 ; i <= k ; i ++ ) {
			t = f( t , r , n );
			val = (Lint)val * Abs( t - s ) % n;
			if( i % 127 == 0 && ( d = Gcd( val , n ) ) > 1 ) return d;
		}
		if( ( d = Gcd( val , n ) ) > 1 ) return d;
	}
}

int prinum = 12;
LL prime[ 20 ] = { 0 , 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 , 37 };
bool Miller_Rabin( LL x ) {
	if( x == 0 || x == 1 ) return 0;
	for( int i = 1 ; i <= prinum ; i ++ ) {
		if( x == prime[ i ] ) return 1;
		if( x < prime[ i ]  ) return 0;
		
		LL s = Quick_pow( prime[ i ] , x - 1 , x ) , tmp = x - 1;
		if( s != 1 ) return 0; 
		while( s == 1 && tmp % 2 == 0 ) {
			tmp /= 2;
			s = Quick_pow( prime[ i ] , tmp , x );
			if( s != 1 && s != x - 1 ) return 0;
		}
	}
	return 1;
}

int k; LL pi[ 100 ];
void Divide( LL x ) {
	if( x == 1 ) return;
	if( Miller_Rabin( x ) ) {
		pi[ ++ k ] = x; return;
	}
	if( x == 4 ) {
		pi[ ++ k ] = 2 , pi[ ++ k ] = 2;
		return;
	}
	LL p = x;
	while( p == x ) p = Pollard_rho( x );
	Divide( p ) , Divide( x / p );
} 

int Fac[ MAXN + 5 ] , Inv[ MAXN + 5 ];
void Init_Fac( ) {
    Fac[ 0 ] = 1;
    for( int i = 1 ; i <= MAXN ; i ++ ) Fac[ i ] = 1ll * Fac[ i - 1 ] * i % Mod;
    Inv[ MAXN ] = Inverse( Fac[ MAXN ] );
    for( int i = MAXN ; i >= 1 ; i -- ) Inv[ i - 1 ] = 1ll * Inv[ i ] * i % Mod;
}
int C( int n , int m ) {
    return 1ll * Fac[ n ] * Inv[ m ] % Mod * Inv[ n - m ] % Mod;
}

int Bernoulli[ MAXN + 5 ] , S[ MAXN + 5 ];
void Init_Bernoulli( ) {
    Bernoulli[ 0 ] = 1;
    for( int i = 1 ; i <= MAXN ; i ++ ) {
        int Sum = 0;
        for( int j = 0 ; j < i ; j ++ )
            Sum = ( Sum + 1ll * C( i + 1 , j ) * Bernoulli[ j ] % Mod ) % Mod;
        Bernoulli[ i ] = ( -1ll * Sum * Inverse( C( i + 1 , i ) ) % Mod + Mod ) % Mod;
    }Bernoulli[ 1 ] ++;
}

LL di[ MAXN + 5 ];
int wi[ MAXN + 5 ];

/*int Aq( int a , int q , int n ) {
    if( q == 1 ) return 1ll * a * n % Mod;
    return 1ll * a * ( 1 - Quick_pow( q , n ) + Mod ) % Mod * Inverse( 1 - q ) % Mod;
}*/
int F( int p , int w , int i ) {
//	int Ans = 0;
//	for( int j = 0 ; j <= w ; j ++ ) Ans = ( Ans + Quick_pow( p , w * i + j * ( x - i ) ) ) % Mod;
//	for( int j = 0 ; j <  w ; j ++ ) Ans = ( Ans - Quick_pow( p , w * i + y - i + j * ( x - i ) ) ) % Mod;
//	return ( Ans + Mod ) % Mod;

//	return ( ( Aq( Quick_pow( p , w * i ) , Quick_pow( p , x - i ) , w + 1 ) - Aq( Quick_pow( p , w * i + y - i ) , Quick_pow( p , x - i ) , w ) ) % Mod + Mod ) % Mod;

	int Ans = 0 , a , q = Quick_pow( p , x - i );
	a = Quick_pow( p , w * i );
	for( int j = 0 ; j <= w ; j ++ ) Ans = ( Ans + a ) % Mod , a = 1ll * a * q % Mod; 
	a = Quick_pow( p , w * i + y - i );
	for( int j = 0 ; j <  w ; j ++ ) Ans = ( Ans - a ) % Mod , a = 1ll * a * q % Mod; 
	return ( Ans + Mod ) % Mod;
}

/*
p^{wi}*p^{j(x-i)}
a1:p^{wi} q:p^(x-i) n:w+1

p^{wi+y-i}*p^{j(x-i)}
a1:p^{wi+y-i} q:p^(x-i) n:w
*/

int Solve( LL n , int x , int y ) {
	if( n == 0 ) return 0;
	k = 0; Divide( n );
	sort( pi + 1 , pi + k + 1 );
	
	S[ 0 ] = 0;
	for( int i = 0 ; i <= y ; i ++ )
		S[ y + 1 - i ] = 1ll * Inverse( y + 1 ) * C( y + 1 , i ) % Mod * Bernoulli[ i ] % Mod;

	int cnt = 0;
	for( int i = 1 ; i <= k ; i ++ ) {
		if( pi[ i ] != di[ cnt ] ) di[ ++ cnt ] = pi[ i ] , wi[ cnt ] = 1;
		else wi[ cnt ] ++;
	}

	int Ans = 0;
	for( int i = 0 ; i <= y + 1 ; i ++ ) {
		int tmp = 1;
		for( int j = 1 ; j <= cnt ; j ++ )
			tmp = 1ll * tmp * F( (int)( di[ j ] % Mod ) , wi[ j ] , i ) % Mod;
        Ans = ( Ans + 1ll * S[ i ] * tmp % Mod ) % Mod;
	}
	return 1ll * Quick_pow( int( n % Mod ) , y ) * Ans % Mod;
}

signed main() {
//	freopen("1.out","w",stdout);

    srand( time( 0 ) );
    Init_Fac( );
    Init_Bernoulli( );

	Read( t );
    while( t -- ) {
        Read( n ) , Read( x ) , Read( y );
		Write( Solve( n , x , y ) ) , putchar('\n');
    }
    return 0;
}
```


---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17656534.html)！

又是一道独立（基本上是）做出的黑，好耶！注：下文为了简洁除法用 `/` 代替分数。

---
前置知识：伯努利数求自然数幂和。

伯努利数：$B_0=1,\sum\limits_{i=0}^n\dbinom{n+1}{i}B_i=0(n\ge1)$，于是可以 $O(n^2)$ 预处理前 $n$ 个伯努利数。

有结论：$\sum\limits_{i=1}^{n-1}i^k=\dfrac{1}{k+1}\sum\limits_{i=1}^{k+1}\dbinom{k+1}{i}B_{k+1-i}n^i$

于是 $s_k(n)=\sum\limits_{i=1}^{n}i^k=\dfrac{1}{k+1}\sum\limits_{i=1}^{k+1}\dbinom{k+1}{i}B_{k+1-i}n^i+n^k$，$s_k$ 是一个关于 $n$ 的 $k+1$ 次多项式。于是我们可以 $O(N^2)$ 预处理出 $k\le N$ 的 $s_k$ 的每项系数。

---
推式子：

$
\begin{aligned}
&\quad\sum\limits_{i=1}^n (i,n)^x((ni)/(i,n))^y=n^y\sum\limits_{i=1}^n (i,n)^{x-y}i^y\\
&=n^y\sum\limits_{d\mid n}d^{x-y}\sum\limits_{i=1}^n i^y[(i,n)=d]=n^y\sum\limits_{d\mid n}d^{y-x}\sum\limits_{i=1}^{n/d} (id)^y[(i,n/d)=1]\\
&=n^y\sum\limits_{d\mid n}d^y\sum\limits_{i=1}^{n/d} i^y\sum\limits_{D\mid (i,n/d)}\mu(D)=n^y\sum\limits_{d\mid n}d^y\sum\limits_{D\mid n/d}\mu(D)D^y\sum\limits_{i=1}^{n/Dd} i^y\\
&=n^y\sum\limits_{D\mid n}\mu(D)D^y\sum\limits_{d\mid n/D}(Dd/D)^xs(n/dD)=n^y\sum\limits_{D\mid n}\mu(D)D^{y-x}\sum\limits_{Dd\mid n}(Dd)^xs(n/Dd)
\end{aligned}
$

---
其中 $s(x)=\sum\limits_{i=1}^x i^y$，就是自然数幂和。接下来我们套路性的令 $T=Dd$：

$n^y\sum\limits_{D\mid n}\mu(D)D^{y-x}\sum\limits_{Dd\mid n}(Dd)^xs(n/Dd)=n^y\sum\limits_{T\mid n}T^xs(n/T)\sum\limits_{D\mid T} \mu(D)D^{y-x}$

我们可以把 $s$ 用前置知识拆成多项式，令 $s(n)=\sum\limits_{i=1}^{y+1}a_in^i$，则

$n^y\sum\limits_{T\mid n}T^xs(n/T)\sum\limits_{D\mid T} \mu(D)D^{y-x}=n^y\sum\limits_{i=1}^{y+1}a_i\sum\limits_{T\mid n}T^x(n/T)^{i}\sum\limits_{D\mid T} \mu(D)D^{y-x}=n^y\sum\limits_{i=1}^{y+1}a_in^i\sum\limits_{T\mid n}T^{x-i}\sum\limits_{D\mid T} \mu(D)D^{y-x}$

---
注意到 $a_in^i$ 后面很积性啊，有结论：若 $f$ 为积性函数，$n$ 质因数分解为：$n=\prod\limits_{i=1}^kp_i^{\alpha_i}$，则：

$g(n)=\sum\limits_{d\mid n}f(d)=\prod\limits_{i=1}^k\left(\sum\limits_{j=0}^{\alpha_i} f(p_i^j)\right)$，也是个积性。

考虑素数幂处的值（可以用 **FFT** 中的点值来理解下面）

令 $f(n)=\sum\limits_{d\mid n} \mu(d)d^{y-x}$ 为积性函数，则对每个 $n$ 的素数幂因子，$f(p^\alpha)$ 是可以快速预处理的。

$\sum\limits_{T\mid n}T^{x-i}\sum\limits_{D\mid T} \mu(D)D^{y-x}=\sum\limits_{T\mid n}T^{x-i}f(T)=\prod\limits_{i=1}^k\left(\sum\limits_{j=0}^{\alpha_i} p_i^{j(x-i)}f(p_i^j)\right)$

这就很好算啦！先 **Pollard-Rho** 分解质因子，而后枚举**原式**中的 $i$，对于每个 $n$ 的素因子计算后面那坨即可，注意 $f$ 不受**原式** $i$ 的影响，于是只用预处理一次即可，当然这是常数优化。

复杂度：$O(T(n^{1/4}+yw(n)\log n))$，其中 $w(n)$ 为 $n$ 的质因子个数，为 $O(\log n)$ 级别。

几乎没怎么优化就跑得很快，目前谷 **rk3**。代码：

```cpp
#include<bits/stdc++.h>
#define P pair<int,int>
#define fi first
#define se second
#define LL long long
#define bll __int128
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
mt19937 rnd(time(0));
const int N=3e3+5,M=N-5,mod=1e9+7;
int T,B[N],jc[N],inv[N],I[N],a[N][N],x,y,pw,ans;LL n;
inline int md(int x){return x>=mod?x-mod:x;}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
inline int C(int n,int m){return 1ll*jc[n]*inv[m]%mod*inv[n-m]%mod;}
int t,c[95],f[95][95],g[95][95];LL PP[95];
namespace PRHO
{
	#define mytz __builtin_ctzll
	#define Abs(x) ((x)>0?(x):-(x))
	inline LL gcd(LL a,LL b)
	{
		LL az=mytz(a),bz=mytz(b),z=min(az,bz),diff;b>>=bz;
		while(a) a>>=az,diff=a-b,az=mytz(diff),b=min(a,b),a=Abs(diff);return b<<z;
	}
	inline LL ksm(LL x,LL p,LL mod){LL s=1;for(;p;(p&1)&&(s=(bll)s*x%mod),x=(bll)x*x%mod,p>>=1);return s;}
	const LL pr[]={2,3,5,7,11,13,17,19,23,29,31,37};
	inline bool check(LL a,LL p)
	{
		LL d=a-1,t=0;while(~d&1) d>>=1,t++;LL now=ksm(p,d,a);
		if(now==1||now==0||now==a-1) return 1;
		for(int i=0;i<t;i++)
		{
			now=(bll)now*now%a;
			if(now==1) return 0;
			if(now==a-1&&i!=t-1) return 1;
		}
		return 0;
	}
	inline bool pd(LL x)
	{
		if(x==1) return 0;
		for(LL i:pr)
		{
			if(x==i) return 1;
			if(x%i==0||!check(x,i)) return 0;
		}return 1;
	}
	#define f(x,c,n) (((bll)(x)*(x)+(c))%(n))
	inline LL Find(LL x)
	{
		LL t1=1ll*rnd()*rnd()%(x-1)+1,c=1ll*rnd()*rnd()%(x-1)+1,t2=f(t1,c,x),d,mul=1;
		for(int i=1;;i<<=1,t1=t2,mul=1)
		{
			for(int j=1;j<=i;j++)
			{
				t2=f(t2,c,x);
				mul=(bll)mul*Abs(t1-t2)%x;
				if(j%127==0){d=gcd(mul,x);if(d>1) return d;}
			}d=gcd(mul,x);
			if(d>1) return d;
		}
	}
	void po(LL x)
	{
		if(x==1) return;
		if(pd(x)) return PP[++t]=x,void();LL num=Find(x);
		while(x%num==0) x/=num;po(x),po(num);
	}
	inline void bk(LL x)
	{
		t=c[1]=0;po(x);sort(PP+1,PP+1+t);t=unique(PP+1,PP+1+t)-PP-1;
		for(int i=1;i<=t;c[++i]=0) while(x%PP[i]==0) c[i]++,x/=PP[i];
	}
}using PRHO::bk;
inline void sol1()
{
	for(int i=1;i<=t;i++) PP[i]%=mod;
	for(int i=1;i<=t;i++)
	{
		int w=ksm(PP[i],pw);
		for(int j=f[i][0]=1,s=w;j<=c[i];j++,s=1ll*s*w%mod)
			f[i][j]=f[i][j-1],(j<=1)&&(f[i][j]=md(f[i][j]-s+mod));
	}
}
inline int sol2(int i)
{
	int PW=(x-i+mod-1)%(mod-1),ans=1;
	for(int i=1,w=ksm(PP[1],PW);i<=t;w=ksm(PP[++i],PW))
		for(int j=0,s=1;j<=c[i];j++,s=1ll*s*w%mod) g[i][j]=1ll*f[i][j]*s%mod;
	for(int i=1,s=0;i<=t;i++,ans=1ll*ans*s%mod,s=0) for(int j=0;j<=c[i];j++) s=md(s+g[i][j]);
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>T;
	for(int i=jc[0]=1;i<=M+1;i++) jc[i]=1ll*jc[i-1]*i%mod;
	inv[M+1]=ksm(jc[M+1],mod-2);for(int i=M;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	I[1]=1;for(int i=2;i<=M+1;i++) I[i]=mod-1ll*(mod/i)*I[mod%i]%mod;
	for(int i=B[0]=1;i<=M;i++)
	{
		for(int j=0;j<i;j++) B[i]=(B[i]+1ll*B[j]*C(i+1,j))%mod;
		B[i]=md(mod-1ll*I[i+1]*B[i]%mod);
	}
	for(int i=0;i<=M;a[i][i]++,i++) for(int j=0;j<=i;j++) a[i][i+1-j]=1ll*B[j]*C(i+1,j)%mod*I[i+1]%mod;
	while(T--)
	{
		cin>>n>>x>>y;bk(n);pw=(y-x+mod-1)%(mod-1);sol1();ans=0;
		for(int i=1;i<=y+1;i++) ans=(ans+1ll*a[y][i]*ksm(n%mod,i)%mod*sol2(i))%mod;
		cout<<(1ll*ans*ksm(n%mod,y)%mod)<<"\n";
	}
	return 0;
}
```

---

## 作者：Vidoliga (赞：0)

式子题：

求：

$1 \leq n \leq 10^{18} ,1 \leq x,y\leq 3000$

$$\sum\limits_{i=1}^n (i,n)^x \text{lcm}(i,n)^y$$

挺裸的题，直接推开就行：

$$\sum\limits_{i=1}^n (i,n)^{x-y} (in)^y$$

$$=n^y\sum\limits_{d|n} d^{x-y} \sum\limits_{i|\frac{n}{d}} (id)^y[(i,\dfrac{n}{d})=1]$$

$$=n^y\sum\limits_{d|n} d^{x} \sum\limits_{i|\frac{n}{d}} i^y \sum\limits_{k|i,k|\frac{n}{d}} \mu(k)$$

$$=n^y\sum\limits_{d|n} d^{x} \sum\limits_{k|\frac{n}{d}} \mu(k) \sum\limits_{i=1}^{\frac{n}{dk}} (ik)^y$$

$$=n^y\sum\limits_{d|n} d^{x} \sum\limits_{k|\frac{n}{d}} \mu(k) k^y \sum\limits_{i=1}^{\frac{n}{dk}} i^y$$

看到后面的求和非常套路，这是一个关于 $\dfrac{dk}{n}$ 的 $y+1$ 次函数。

设 $\sum\limits_{i=1}^{n} i^y=\sum\limits_{i=0}^{y+1} f_in^i$。

有：

$$n^y\sum\limits_{d|n} d^{x} \sum\limits_{k|\frac{n}{d}} \mu(k) k^y \sum\limits_{i=1}^{\frac{n}{dk}} i^y$$

$$=n^y\sum\limits_{d|n} d^{x} \sum\limits_{k|\frac{n}{d}} \mu(k) k^y \sum\limits_{i=1}^{y+1} f_i(\dfrac{n}{dk})^i$$

$$=n^y \sum\limits_{i=1}^{y+1} f_i \left( \sum\limits_{d|n} d^{x} \sum\limits_{k|\frac{n}{d}} \mu(k) k^y (\dfrac{n}{dk})^i \right)$$

这玩意就是 $n^y\sum\limits_{i=1}^{y+1} f_i \left ( (\mu \times n^y) * n^x * n^i\right)(n)$

把后面的 $n^x * n^i$ 卷掉。

考虑怎么算 $\left ( (\mu \times n^y) * n^x * n^i\right)(n)$。

考虑到这是积性函数，可以将 $n$ 因式分解后乘积。

发现 $\mu(x)$ 的取值不为 $0$ 时，$x$ 不含平方因子，所以这这部分卷的时候是 $O(1)$ 的，然后后面有一个快速幂的 $O( \log x)$。

总的还有枚举质因子的 $O( \log  n)$。

外层还有一个 $y$ ，复杂度 $O(Ty \log n \log x)$。

对于质因数分解，可用 $\text{Pollard-Pho}$ 做到一组数据 $O(n^{\frac{1}{4}})$。

对于多项式系数 $f_i$，我们有 $\sum\limits_{i=0}^{n-1} i^m=\sum_{k=1}^{m+1} C^{k}_{m+1}B_{y+1-i}n^k$。

其中 $B_i$ 为伯努利数，可以 $O(y^2)$ 预处理。

总的复杂度就是 $O(Tn^{\frac{1}{4}}+Ty \log n \log x+y^2)$。

代码：

```cpp
int T,n,x,y;
inline int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int ksm(int a,int b){
	int res=1;a%=mod;
	while(b){
		if(b&1) res=res*a%mod;
		a=a*a%mod;b>>=1; 
	}return res;
}
int qpow(int a,int b,int p){
	int res=1;
	while(b){
		if(b&1) res=(__int128)res*a%p;
		a=(__int128)a*a%p;b>>=1; 
	}return res;
}
bool MB(int p){
	if(p<2) return 0;if(p==2||p==3) return 1;
	int d=p-1,r=0;
	while(!(d&1)) r++,d>>=1;
	for(int k=0;k<15;k++){
		int a=rnd()%(p-2)+2;int x=qpow(a,d,p);
		if(x==1||x==p-1) continue;
		for(int i=0;i<r-1;i++){x=(__int128)x*x%p;if(x==p-1) break;}
		if(x!=p-1) return 0;
	}
	return 1;
}
int p_pho(int x){
	int s=0,t=0,c=rnd()%(x-1)+1,d;
	int st=0,gl=1,val=1;
	for(gl=1;;gl<<=1,s=t,val=1){
		for(st=1;st<=gl;st++){
			t=((__int128)t*t+c)%x;
			val=(__int128)val*abs(t-s)%x;
			if(st%127==0) if((d=gcd(val,x))>1) return d;
		}
		if((d=gcd(val,x))>1) return d;
	}
}
int p[N],pcnt,B[M+10],C[M+10][M+10];
void fac(int x,int e){
	if(x<2) return ;
	if(MB(x)){for(int i=1;i<=e;i++) p[++pcnt]=x;return void();}
	int y=x,o=0;
	while(y>=x) y=p_pho(x);
	while(x%y==0) x/=y,o++;
	fac(x,e);fac(y,e*o);
}
inline int f(int p,int c){return ksm(p,c*y)*(c?mod-1:1)%mod;}
int g(int p,int c,int i){
	int a=min(x,i),b=abs(x-i),res=0;int r=ksm(p,b);
	for(int j=0;j<=c;j++) res=(res+ksm(r,j))%mod;
	res=res*ksm(p,c*a)%mod;
	return res;
}
void solve(){
	n=read();x=read();y=read();pcnt=0;fac(n,1);
	sort(p+1,p+pcnt+1);int ans=0;
	for(int i=1;i<=y+1;i++){
		int ret=1;
		for(int j=1;j<=pcnt;j++){
			int c=1,pri=p[j],res=0;
			while(j<pcnt&&pri==p[j+1]) j++,c++;
			for(int w=0;w<=min(c,1ll);w++){
				res=(res+f(pri,w)*g(pri,c-w,i))%mod;
			}
			ret=ret*res%mod;
		}
		ans=(ans+ksm(y+1,mod-2)*B[y+1-i]%mod*C[y+1][i]%mod*ret)%mod;
	}
	printf("%lld\n",ans*ksm(n,y)%mod);
}
signed main(){
	C[0][0]=1;
	for(int i=1;i<M;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	B[0]=1;
	for(int i=1;i<M-1;i++){
		for(int j=0;j<i;j++){
			B[i]=(B[i]+C[i+1][j]*B[j])%mod;
		}
		B[i]=(mod-B[i])%mod;B[i]=B[i]*ksm(C[i+1][i],mod-2)%mod;
	}B[1]++;
	T=read();while(T--) solve();
	return 0;
}
```


---

## 作者：Gauss0320 (赞：0)

今天心情不好，所以又来做数论题了......

---

## 题目大意

求

$$\sum_{i=1}^n\text{g.c.d}^x(i,n)\text{l.c.m}^y(i,n)$$
的值.

其中$n\le10^{18},x,y\le 3000$.

## 题解

根据基本套路先推一波式子
$$\begin{aligned}\sum_{i=1}^n\text{g.c.d}^n(i,n)\text{l.c.m}^y(i,n)&=n^y\sum_{i=1}^ni^y\text{g.c.d}^{x-y}(i,n)\\&=n^y\sum_{d|n}d^{x-y}\sum_{i=1}^ni^y[\text{g.c.d}(i,n)=d]\\&=n^y\sum_{d|n}d^{x-y}\sum_{i=1}^{n/d}(id)^y[i\perp n]\\&=n^y\sum_{d|n}d^{x}\sum_{i=1}^{n/d}i^y[i\perp n]\end{aligned}$$
第二个和式就是「一个人的数论」，写过了的读者可以跳过下面这一部分

> 令
> $$S(n)=\sum_{i=1}^ni^y[i\perp n]$$
> 则有
> $$\begin{aligned}S(n)&=\sum_{i=1}^ni^y\sum_{k|i,k|n}\mu(k)\\&=\sum_{k|n}\mu(k)\sum_{i=1}^{n/k}(ik)^y\\&=\sum_{k|n}\mu(k)k^y\sum_{i=1}^{n/k}i^y\\&=\sum_{k|n}\mu(k)k^y\sum_{i=1}^{y+1}a_i\left(\frac{n}{k}\right)^i\\&=\sum_{i=1}^{y+1}a_i\sum_{k|n}\mu(k)k^{y}\left(\frac{n}{k}\right)^i\end{aligned}$$

回到主线，代回原式得
$$\begin{aligned}n^y\sum_{d|n}d^{x}\sum_{i=1}^{n/d}i^y[i\perp n]&=n^y\sum_{d|n}d^x\sum_{i=1}^{y+1}a_i\sum_{kd|n}\mu(k)k^y\left(\frac{n}{kd}\right)^i\\&=n^y\sum_{i=1}^{y+1}a_i\sum_{d|n}d^x\sum_{kd|n}\mu(k)k^y\left(\frac{n}{kd}\right)^i\\&=n^y\sum_{i=1}^{y+1}a_i\sum_{T|n}\left[\sum_{k|T}\mu(k)k^y\left(\frac{T}{k}\right)^x\right]\left(\frac{n}{T}\right)^i\end{aligned}$$
注意到最后两层的和式嵌套实际上是三个函数的迪利克雷卷积，令$f(n)=\mu(n)n^y$，则有
$$n^y\sum_{i=1}^{y+1}a_i\sum_{T|n}\left[\sum_{k|T}\mu(k)k^y\left(\frac{T}{k}\right)^x\right]\left(\frac{n}{T}\right)^i=n^y\sum_{i=1}^{y+1}a_i(f*\text{id}_x*\text{id}_i)(n)$$
考虑到$(f*\text{id}_x*\text{id}_i)(n)$是积性函数，所以考虑求出其在质数的若干次幂处的值
$$(f*\text{id}_x*\text{id}_i)(p^c)=(\text{id}_x*\text{id}_i)(p^c)-p^y(\text{id}_x*\text{id}_i)(p^{c-1})$$
而后面的两部分就是一个等比数列求和，暴力算即可（没必要快速幂，都是${\log}$级别的）

然后Pollard-ρ质因数分解，实现不好可能会TLE.

---

## 作者：Spasmodic (赞：0)


$$
\begin{aligned}
\sum_{i}\gcd(i,n)^x\operatorname{lcm}(i,n)^y&=\sum_{i}(in)^y\gcd(i,n)^{x-y}\\
&=\sum_{d|n}\sum_{d|i}(in)^yd^{x-y}[\gcd(i,n)=d]\\
&=\sum_{d|n}d^xn^y\sum_{i}i^y[\gcd(i,\frac{n}{d})=1]\\
&=\sum_{d|n}d^xn^y\sum_{i}i^y\sum_{k|i,k|\frac{n}{d}}\mu(k)\\
&=n^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)\sum_{k|i}i^y\\
&=n^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)k^yS_y(\frac{n}{kd})
\end{aligned}
$$
其中
$$
S_y(n)=\sum_{i=1}^{n}i^y
$$
是关于 $n$ 的 $y+1$ 阶多项式，设 $f_i=[x^i]S_y(n)$，则
$$
\begin{aligned}
\sum_{i}\gcd(i,n)^x\operatorname{lcm}(i,n)^y&=n^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)k^yS_y(\frac{n}{kd})\\
&=n^y\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)k^y\sum_{i}(\frac{n}{kd})^if_i\\
&=n^y\sum_{i}f_i\sum_{d|n}d^x\sum_{k|\frac{n}{d}}\mu(k)k^y(\frac{n}{kd})^i\\
&=n^y\sum_{i}f_i\sum_{D|n}(\frac{n}{D})^i\sum_{d|D}d^x\mu(\frac{D}{d})(\frac{D}{d})^y\\
&=n^y\sum_{i}f_i\sum_{D|n}(\frac{n}{D})^i((d^x)*(\mu(d)d^y))(D)\\
&=n^y\sum_{i}f_i((d^i)*(d^x)*(\mu(d)d^y))(n)
\end{aligned}
$$
其中 $*$ 表示狄利克雷卷积。

注意到 $f(d)=d^i$，$g(d)=d^x$，$h(d)=\mu(d)d^y$ 都是积性函数，所以 $F=f*g*h$ 也是积性函数。

考虑计算 $F(p^k)$。
$$
F(p^k)=\sum_{i=0}^{k}h(p^i)(f*g)(p^{k-i})=(f*g)(p^k)-p^y(f*g)(p^{k-1})
$$
所以只要考虑算 $(f*g)(p^k)$ 即可。
$$
(f*g)(p^k)=\sum_{t=0}^{k}p^{it}p^{(k-t)x}=\sum_{t=0}^{k}p^{kx+(i-x)t}
$$
可以用等比数列求和公式计算。

因此我们使用 Pollard-rho 对 $n$ 进行因数分解，就可以分别算出 $F(k)$。

最后考虑计算 $f_i$，直接插值/伯努利数，$O(n^2)$。

---

