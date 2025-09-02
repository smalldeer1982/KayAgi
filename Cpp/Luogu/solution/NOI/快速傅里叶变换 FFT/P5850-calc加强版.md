# calc加强版

## 题目背景

[原题链接](https://www.luogu.com.cn/problem/P4463)

## 题目描述

一个序列 $a_1,\cdots,a_n$ 是合法的，当且仅当：

长度为给定的 $n$。

$a_1,\cdots,a_n$ 都是 $[1,k]$ 中的整数。

$a_1,\cdots,a_n$ 互不相等。

一个序列的值定义为它里面所有数的乘积，即 $a_1\times a_2\times\cdots\times a_n$ 。

求所有不同合法序列的值的和。

两个序列不同当且仅当他们任意一位不一样。

输出答案对 $998244353$ 取余的结果。

## 说明/提示

$\text{subtask 1 (84 pts)}$：$1\le m\le 500$

$\text{subtask 2 (16 pts)}$：$1\le m\le 5\times 10^5$，建议使用高效输出方式。

对所有数据，$1\le m\le k\le 998244352$。

## 样例 #1

### 输入

```
13 8```

### 输出

```
91
7462
546546
35387352
3869654
396558319
363789591
879373476
```

# 题解

## 作者：iostream (赞：11)

出题人来补上题解 qwq Latex 已重写。

公式可能显示有锅，[建议到博客中查看](https://www.luogu.com.cn/blog/user13052/solution-p5850)。

首先注意到题目中 $a$ 数组是有序的，那我们只用算有序的方案乘上 $n!$ 即可。

而此时的答案显然
$$Ans=[x^n](1+x)(1+2x)\dots (1+Ax)=\prod_{i=1}^A(1+ix)$$

取对数把乘法变加法，即
$$
\prod_{i=1}^A(1+ix)=\exp(\sum_{i=1}^A\ln(1+ix))
$$
这里有 $\ln$ 的展开式
$$
-\ln(1-x)=\sum_{i=1}^\infty\frac{x^i}{i}
$$
故有
$$
\begin{aligned}
&\ln(1+ix)\\
&=\ln(1-(-ix))\\
&=-\sum_{k=1}^\infty \frac{(-ix)^k}{k}\\
&=\sum_{k=1}^\infty \frac{(-1)^{k+1}i^k}{k}x^k
\end{aligned}
$$
则
$$
\begin{aligned}
&\sum_{i=1}^A \ln(1+ix)\\
&=\sum_{k=1}^\infty \frac{(-1)^{k+1}\sum_{i=1}^Ai^k}{k}x^k
\end{aligned}
$$
自然数幂和可以用某种方法（插值、伯努利数之类）算出来。

最后还要多项式 exp，直接 $O(n^2)$ 算。

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 505;

int n, M, P, inv[N], Bo[N], C[N][N], a[N], b[N];

typedef vector<int> poly;

poly F[N];

int calc(const poly&a, int x)
{
	int y = 0;
	for(int i = a.size() - 1; i >= 0; i --)
		y = (1LL * y * x + a[i]) % P;
	return y;
}

int main()
{
	scanf("%d%d%d",&M,&n,&P);
	for(int i = 0; i <= n + 1; i ++)
	{
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % P;
	}
	inv[1] = 1;
	for(int i = 2; i <= n + 1; i ++)
		inv[i] = (ll) inv[P % i] * (P - P / i) % P;
	Bo[0] = 1;
	for(int i = 1; i <= n; i ++)
	{
		int t = 0;
		for(int j = 0; j < i; j ++)
			t = (t + (ll)Bo[j] * C[i + 1][j]) % P;
		Bo[i] = (ll)(P - inv[i + 1]) * t % P;
	}
	F[0] = poly{0, 1};
	for(int i = 1; i <= n; i ++)
	{
		F[i].resize(i + 2);
		for(int j = 1; j <= i + 1; j ++)
		{
			F[i][j] = (ll) Bo[i + 1 - j] * C[i + 1][j] % P * inv[i + 1] % P;
			if((i + 1 - j) & 1)
				F[i][j] = (P - F[i][j]) % P;
		}
	}
	for(int i = 1; i <= n; i ++)
	{
		a[i] = (ll)inv[i] * calc(F[i], M) % P;
		if(~i&1) a[i] = (P - a[i]) % P;
	}
	for(int i = 1; i <= n; i ++)
		a[i - 1] = (ll)i * a[i] % P;
	b[0] = 1;
	for(int i = 1; i <= n; i ++)
	{
		for(int j = 0; j < i; j ++)
			b[i] = (b[i] + (ll)b[j] * a[i - j - 1]) % P;
		b[i] = (ll)b[i] * inv[i] % P;
	}
	int ans = b[n];
	for(int i = 2; i <= n; i ++) ans = (ll)ans * i % P;
	printf("%d", ans);
	return 0;
}
```

注意到复杂度瓶颈在于对所有 $k\in [1,n]$ 预处理自然数幂和。
这东西的EGF
$$
\begin{aligned}
&\sum_{k=0}^\infty \sum_{i=0}^A i^k \frac{x^k}{k!}\\
&=\sum_{i=0}^A \sum_{k=0}^\infty \frac{(ix)^k}{k!}\\
&= \sum_{i=0}^A e^{ix}\\
&= \frac{e^{(A+1)x}-1}{e^x-1}
\end{aligned}
$$

多项式求逆即可，整个复杂度也是 $O(n\log n)$。

代码需要把上面代码的暴力改成多项式全家桶。

---

## 作者：zhiyangfan (赞：8)

## P5850 calc加强版
calc 这道题吧，是之前做练拉插的时候躺在我题单的，刚开始看到鱼鱼的题解，非常震撼。然后现在我居然能写出来这道题了，特此纪念。
### 题意
给出 $k,m$，对于 $1\le n\le m$，求所有满足以下条件的合法有序序列 $\left<a_1,a_2,\cdots,a_n\right>$ 的权值和：
- $1\le a_i\le k$。
- $\forall i\ne j$，都有 $a_i\ne a_j$。

其中一个序列的权值定义为所有数的积，答案对 $998,244,353$ 取模。($1\le m\le 5\times 10^5,1\le k<998244353$)
### 题解
考虑把有序序列转化成无序的，然后就变成一个背包问题了，无序的答案跟有序的就差一个阶乘。变成背包后，$n$ 对应的答案为：
$$[z^n]\prod_{i=1}^k(1+iz)$$
接下来的主要问题就是折腾后面的 $\prod$ 了。首先根据套路，求 $\ln$ 把积变成和：
$$[z^n]\exp \sum_{i=1}^k\ln(1+iz)$$
然后处理 $\ln(1+iz)$，处理 $\ln,\exp$，我们的方法通常都是求导：
$$\begin{aligned}\ln(1+iz)&=\int (\ln(1+iz))'\\&=\int\dfrac{i}{1+iz}\\&=\int\sum_{p\ge 0}i^{p+1}(-1)^pz^p\\&=\sum_{p\ge 0}\dfrac{i^{p+1}(-1)^pz^{p+1}}{p+1}\\&=\sum_{p\ge 1}\dfrac{i^p(-1)^{p-1}z^p}{p}\end{aligned}$$
带回原式：
$$[z^n]\exp \sum_{p\ge 1}\dfrac{(-1)^{p-1}z^p}{p}\sum_{i=1}^ki^p$$
注意到，这个式子里唯一恶心的就是最后一个和式了，接下来就是针对它的推导了。

首先我们先试试找找它的 $\rm OGF$：
$$\begin{aligned}\sum_{p\ge 0}\left(\sum_{i=1}^ki^p\right)z^p&=\sum_{i=1}^k\sum_{p\ge 0}(iz)^p\\&=\sum_{i=1}^k\dfrac{1}{1-iz}\end{aligned}$$
这个形式不是很好看，那就试试 $\rm EGF$ 吧：
$$\begin{aligned}\sum_{p\ge 0}\left(\sum_{i=1}^ki^p\right)\dfrac{z^p}{p!}&=\sum_{i=1}^k\sum_{p\ge 0}\dfrac{(iz)^p}{p!}\\&=\sum_{i=1}^ke^{iz}\end{aligned}$$
这个形式，是等比数列求和的形式！也就是说，我们能找到一个合理的封闭形式！具体来讲，如果设 $\hat{F}(z)$ 表示该 $\rm EGF$，则：
$$\hat{F}(z)=\dfrac{e^z-e^{(k+1)z}}{1-e^z}$$
这个式子只需要一次多项式求逆即可解决。不过跟普通的分式不一样的是，这个分式分母的常数项是 $0$，直接牛迭求逆的话无法处理边界。不过问题不大，注意到分子分母上常数项都为 $0$。那就简单了，同时除一个 $z$ 即可解决问题。

让我们回到最开始的式子，把已知的 $\hat{F}(z)$ 代入，有：
$$\begin{aligned}&[z^n]\exp \sum_{p\ge 1}\dfrac{(-1)^{p-1}z^p}{p}p![z^p]\hat{F}(z)\\=&[z^n]\exp \sum_{p\ge 1}(-1)^{p-1}z^p(p-1)![z^p]\hat{F}(z)\end{aligned}$$
这样这个式子就能求了。处理到第 $z^m$ 项，然后直接做一次 $\exp$ 即可解决问题。最后别忘了，我们求的是无序序列，变成有序序列还要再乘一个阶乘。时间复杂度 $\mathcal{O}(n\log n)$。

不过呢，作为一个不喜欢用缺省源的人，也没有自己的多项式板子从来都是手打，我是非常拒绝牛迭 $\exp$ 的。所以我习惯的是半在线卷积求 $\exp$，具体来讲，利用的是这个式子：
$$B(z) = e^{A(z)}\rightarrow[z^n]B(z)=\dfrac{1}{n}[z^{n-1}]B(z)A'(z)$$
写起来还是蛮好写的，而且跑的还不算慢，时间复杂度 $\mathcal{O}(n\log^2n)$。当然，写起来稍微有点卡常，不过只需要预处理一下单位根，并简单注意一下常数，即可轻松通过。
```cpp
#include <cstdio>
#include <algorithm>
const int N = 3e6 + 10, mod = 998244353; typedef long long ll;
int rev[N], A[N], B[N], f[N], g[N], F[N], G[N], fac[N], ifac[N], w[2][22][N / 2], lim, m;
inline void print(const int& x)
{
	static int st[N], tp; tp = 0; int t = x;
	while (t) st[++tp] = t % 10, t /= 10;
	for (int i = tp; i; --i) putchar(st[i] + '0');
}
inline int ksm(int a, int b)
{
    int ret = 1;
    while (b)
    {
        if (b & 1) ret = (ll)ret * a % mod;
        a = (ll)a * a % mod; b >>= 1;
    }
    return ret;
}
inline void init(int n)
{
    lim = 1; m = 0; while (lim <= n) lim <<= 1, ++m;
    for (int i = 0; i < lim; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (m - 1));
    for (int h = 2, t = 0, gn[2]; h <= lim; h <<= 1, ++t)
    {
        w[0][t][0] = w[1][t][0] = 1; 
        gn[0] = ksm(3, (mod - 1) / h); gn[1] = ksm(gn[0], mod - 2);
        for (int j = 1; j < (h >> 1); ++j)
            for (int d = 0; d < 2; ++d) w[d][t][j] = (ll)w[d][t][j - 1] * gn[d] % mod;
    }
}
inline void initF(int n)
{
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % mod;
    ifac[n] = ksm(fac[n], mod - 2);
    for (int i = n - 1; i; --i) ifac[i] = (ll)ifac[i + 1] * (i + 1) % mod;
}
inline void NTT(int* f, int len, int on)
{
    for (int i = 0; i < len; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
    for (int h = 2, p = 0, o = 1; h <= len; h <<= 1, o <<= 1, ++p)
        for (int j = 0; j < len; j += h)
            for (int k = j, l = 0; k < j + o; ++k, ++l)
            {
                int u = f[k], t = (ll)w[on][p][l] * f[k +o] % mod;
                f[k] = (u + t) % mod; f[k + o] = (u - t + mod) % mod;
            }
    if (on) for (int i = 0, inv = ksm(len, mod - 2); i < len; ++i) f[i] = (ll)f[i] * inv % mod;
}
inline void pre(int* f, int* g, int n, int m)
{
    init(n + m + 1);
    for (int i = 0; i < n; ++i) A[i] = f[i];
    for (int i = 0; i < m; ++i) B[i] = g[i];
    for (int i = n; i < lim; ++i) A[i] = 0;
    for (int i = m; i < lim; ++i) B[i] = 0;
}
inline void mul1(int* f, int* g, int n, int m)
{
    pre(f, g, n, m);
    NTT(A, lim, 0); NTT(B, lim, 0);
    for (int i = 0; i < lim; ++i)  
        A[i] = (ll)A[i] * (mod + 2 - (ll)A[i] * B[i] % mod) % mod;
    NTT(A, lim, 1);
}
inline void mul2(int* f, int* g, int n, int m)
{
    pre(f, g, n, m);
    NTT(A, lim, 0); NTT(B, lim, 0);
    for (int i = 0; i < lim; ++i) A[i] = (ll)A[i] * B[i] % mod;
    NTT(A, lim, 1);
}
inline void Inv(int* f, int* g, int n)
{
    f[0] = ksm(g[0], mod - 2);
    for (int t = 2; t <= n; t <<= 1)
    {
        mul1(f, g, t, t);
        for (int i = 0; i < t; ++i) f[i] = A[i];
    }
}   
inline void Exp(int l, int r)
{
    if (l + 1 == r) return F[l] = l ? (ll)F[l] * ksm(l, mod - 2) % mod : 1, void();
    int mid = (l + r) >> 1; Exp(l, mid);
    mul2(F + l, G, mid - l, r - l - 1);
    for (int i = mid; i < r; ++i) (F[i] += A[i - l - 1]) %= mod;
    Exp(mid, r);
}
int main()
{
    int k, m; scanf("%d%d", &k, &m); initF(m + 10);
    for (int i = 1; i <= m + 1; ++i) f[i - 1] = mod - ifac[i];
    int l = 1; while (l <= (m + 1)) l <<= 1;
    Inv(g, f, l);
    for (int i = 1; i <= m + 1; ++i) 
        f[i - 1] = (mod + ifac[i] - (ll)ksm(k + 1, i) * ifac[i] % mod) % mod;
    for (int i = m + 2; i < l; ++i) f[i] = g[i] = 0;
    mul2(f, g, m + 2, m + 2);
    for (int i = 1; i <= m + 1; ++i)
    {
        G[i] = (ll)fac[i - 1] * A[i] % mod;
        if ((i - 1) & 1) G[i] = (mod - G[i]);
    }
    for (int i = 1; i <= m + 1; ++i) G[i - 1] = (ll)G[i] * i % mod;
    Exp(0, l); 
    for (int i = 1, t; i <= m; ++i)
        t = (ll)fac[i] * F[i] % mod, print(t), putchar('\n');
    return 0;  
}
```

---

## 作者：jun头吉吉 (赞：4)

## 题意
一个序列$a_1,a_2,\ldots,a_n$合法，当且仅当：
- $\forall i\in[1,n],a_i\in[1,k]$
- $\forall i\not=j,a_i\not=a_j$

一个序列的值为它的乘积,即$\prod_{i=1}^na_i$

给定$m,k$,对于$n\in[1,m]$，求所有长度为$n$的不同的序列的值的和。
## 题解
不难发现答案可以写成生成函数的形式：
$$F(x)=\prod_{i=1}^k(1+ix)$$
但此时是无序的，因为$a_1,a_2,\ldots,a_n$互不相等，乘$n!$即可。最后答案为$n![x^n]F(x)$

可以写出$\ln F(x)$，证明见上一篇题解[$\color{skyblue}{\text{P4463 【[集训队互测2012] calc】}}$](https://www.luogu.com.cn/blog/CJL/solution-p4463)
$$\ln F(x)=\sum_{j=1}^\infty\frac{(-1)^{j-1}}{j}(\sum_{i=1}^ki^j)x^j$$
所以我们现在希望能对于$j\in[1,n]$求出$\sum_{i=1}^ki^j$的值。

考虑$<\sum_{i=1}^ki^0,\sum_{i=1}^ki^1,\sum_{i=1}^ki^2,\ldots>$的$\mathbf{EFG}$
$$G(x)=\sum_{j=0}^\infty\frac{\sum_{i=1}^ki^j}{j!}x^j$$
我们交换一下求和顺序
$$=\sum_{i=1}^k\sum_{j=0}^\infty \frac{(ix)^j}{j!}$$
右边那串实际上就是$e^{ix}$的泰勒展开。
$$=\sum_{i=1}^ke^{ix}$$
发现就是一个长度为$k$，首项为$e^x$公比为$e^x$的等差数列，套用公式得到：
$$=\frac{e^{(k+1)x}-e^x}{e^x-1}$$
但此时分子的常数项项为$0$不存在乘法逆。$\rm However,$分母的常数项也为$0$因此上下同除$x$就可以放心大胆地求乘法逆了。
## 代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
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
using namespace std;
template<const int mod>
struct modint{
    int x;
    modint<mod>(int o=0){x=o;}
    modint<mod> &operator = (int o){return x=o,*this;}
    modint<mod> &operator +=(modint<mod> o){return x=x+o.x>=mod?x+o.x-mod:x+o.x,*this;}
    modint<mod> &operator -=(modint<mod> o){return x=x-o.x<0?x-o.x+mod:x-o.x,*this;}
    modint<mod> &operator *=(modint<mod> o){return x=1ll*x*o.x%mod,*this;}
    modint<mod> &operator ^=(int b){
        modint<mod> a=*this,c=1;
        for(;b;b>>=1,a*=a)if(b&1)c*=a;
        return x=c.x,*this;
    }
    modint<mod> &operator /=(modint<mod> o){return *this *=o^=mod-2;}
    modint<mod> &operator +=(int o){return x=x+o>=mod?x+o-mod:x+o,*this;}
    modint<mod> &operator -=(int o){return x=x-o<0?x-o+mod:x-o,*this;}
    modint<mod> &operator *=(int o){return x=1ll*x*o%mod,*this;}
    modint<mod> &operator /=(int o){return *this *= ((modint<mod>(o))^=mod-2);}
	template<class I>friend modint<mod> operator +(modint<mod> a,I b){return a+=b;}
    template<class I>friend modint<mod> operator -(modint<mod> a,I b){return a-=b;}
    template<class I>friend modint<mod> operator *(modint<mod> a,I b){return a*=b;}
    template<class I>friend modint<mod> operator /(modint<mod> a,I b){return a/=b;}
    friend modint<mod> operator ^(modint<mod> a,int b){return a^=b;}
    friend bool operator ==(modint<mod> a,int b){return a.x==b;}
    friend bool operator !=(modint<mod> a,int b){return a.x!=b;}
    bool operator ! () {return !x;}
    modint<mod> operator - () {return x?mod-x:0;}
	modint<mod> &operator++(int){return *this+=1;}
};
const int N=4e6+5;

const int mod=998244353;
namespace residue{
	//求二次剩余
	int I2;
	struct complex{
		long long real,imag;
		complex&operator=(long long x){real=x,imag=0;}
		complex(long long real=0,long long imag=0):real(real),imag(imag){}
		bool operator==(const complex&b)const{return real==b.real&&imag==b.imag;}
		complex operator*(const complex &b)const{return complex((real*b.real+I2*imag%mod*b.imag)%mod,(real*b.imag+imag*b.real)%mod);}
	};
	complex ksm(complex a,int b){
		complex res=1;
		while(b){
			if(b&1)res=res*a;
			a=a*a;b>>=1;
		}return res;
	}
	bool check(int x){return ksm(complex(x,0),(mod-1)/2).real==1;}
	pair<int,int>solve(int n){
	    if(n==0)return {0,0};
		long long a=rand()%mod;
		while(!a||check((a*a+mod-n)%mod))a=rand()%mod;
		I2=(a*a+mod-n)%mod;
		int x0=ksm(complex(a,1),(mod+1)/2).real;
		return {min(x0,mod-x0),max(x0,mod-x0)};
	}
}
const modint<mod> GG=3,Ginv=modint<mod>(1)/3,I=86583718;
struct poly{
	vector<modint<mod>>a;
	modint<mod>&operator[](int i){return a[i];}
	int size(){return a.size();}
	void resize(int n){a.resize(n);}
	void reverse(){std::reverse(a.begin(),a.end());}
};
int rev[N];
inline int ext(int n){int k=0;while((1<<k)<n)k++;return k;}
inline void init(int k){int n=1<<k;for(int i=0;i<n;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));}
inline void ntt(poly&a,int k,int typ){
	int n=1<<k;
	for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<n;mid<<=1){
		modint<mod> wn=(typ>0?GG:Ginv)^((mod-1)/(mid<<1));
		for(int r=mid<<1,j=0;j<n;j+=r){
			modint<mod> w=1;
			for(int k=0;k<mid;k++,w=w*wn){
				modint<mod> x=a[j+k],y=w*a[j+k+mid];
				a[j+k]=x+y,a[j+k+mid]=x-y;
			}
		}
	}
	if(typ<0){
		modint<mod> inv=modint<mod>(1)/n;
		for(int i=0;i<n-1;i++)a[i]*=inv;
	}
}
inline poly one(){poly a;a.a.push_back(1);return a;}
poly operator +(poly a,poly b){
	int n=max(a.size(),b.size());a.resize(n),b.resize(n);
	for(int i=0;i<n;i++)a[i]+=b[i];return a;
}
poly operator -(poly a,poly b){
	int n=max(a.size(),b.size());a.resize(n),b.resize(n);
	for(int i=0;i<n;i++)a[i]-=b[i];return a;
}
inline poly operator*(poly a,poly b){
	int n=a.size()+b.size()-1,k=ext(n);
	a.resize(1<<k),b.resize(1<<k),init(k);
	ntt(a,k,1);ntt(b,k,1);for(int i=0;i<(1<<k);i++)a[i]*=b[i];
	ntt(a,k,-1),a.resize(n);return a;
}
inline poly operator*(poly a,modint<mod> b){for(int i=0;i<a.size();i++)a[i]*=b;return a; }
inline poly operator/(poly a,modint<mod> b){for(int i=0;i<a.size();i++)a[i]/=b;return a; }
inline poly operator-(poly a){for(int i=0;i<a.size();i++)a[i]=-a[i];return a; }
poly inv(poly F,int k){
	int n=1<<k;F.resize(n);
	if(n==1){F[0]=modint<mod>(1)/F[0];return F;}
	poly G,H=inv(F,k-1);
	G.resize(n),H.resize(n<<1),F.resize(n<<1);
	for(int i=0;i<n/2;i++)G[i]=H[i]*2;
	init(k+1),ntt(H,k+1,1),ntt(F,k+1,1);
	for(int i=0;i<(n<<1);i++)H[i]=H[i]*H[i]*F[i];
	ntt(H,k+1,-1),H.resize(n);
	for(int i=0;i<n;i++)G[i]-=H[i];return G;
}
inline poly inv(poly a){
	int n=a.size();
	a=inv(a,ext(n)),a.resize(n);return a;;
}
inline poly deriv(poly a){//求导 
	int n=a.size()-1;
	for(int i=0;i<n;i++)a[i]=a[i+1]*(i+1);
	a.resize(n);return a;
}
inline poly inter(poly a){//求原 
	int n=a.size()+1;a.resize(n);
	for(int i=n;i>=1;i--)a[i]=a[i-1]/i;
	a[0]=0;return a;
}
inline poly ln(poly a){
	int n=a.size();
	a=inter(deriv(a)*inv(a));
	a.resize(n);return a;
}
poly exp(poly a,int k){
	int n=1<<k;a.resize(n);
	if(n==1)return one();
	poly f0=exp(a,k-1);f0.resize(n);
	return f0*(one()+a-ln(f0)); 
}
poly exp(poly a){
	int n=a.size();
	a=exp(a,ext(n));a.resize(n);return a;
}
typedef modint<mod>mint;
mint fac[N];
void add(poly &F,mint a,bool flag){
	//flag?F+=e^ax:F-=e^ax
	for(int i=0;i<F.size();i++)
		flag?(F[i]+=(a^i)/fac[i]):(F[i]-=(a^i)/fac[i]);
}
int n,k;poly F,G;
signed main(){
	fac[0]=1;for(int i=1;i<N;i++)fac[i]=fac[i-1]*i;
	in::read(k,n);
	F.resize(n+2);G.resize(n+2); 
	add(F,k+1,1);add(F,1,0);add(G,1,1);
	for(int i=0;i<=n;i++)F[i]=F[i+1],G[i]=G[i+1];
	F.resize(n+1);G.resize(n+1); 
	F=F*inv(G);G[0]=0;
	for(int i=1;i<=n;i++)
		if((i+1)&1)G[i]=-F[i]*fac[i]/i;
		else G[i]=F[i]*fac[i]/i;
	G=exp(G);for(int i=1;i<=n;i++)out::write((G[i]*fac[i]).x),out::putc('\n');
	out::flush();
	return 0;
}
```

---

## 作者：cyffff (赞：3)

[$\text{Link}$](https://www.luogu.com.cn/problem/P5850)
## 题意
对 $n\in[1,m]$ 求

$$\sum_{a_{1,\cdots n}\in[1,k],a_i\ne a_j(1\le i<j\le n)}\prod_{i=1}^n a_i$$

对 $998244353$ 取模。

$m\le 5\times 10^5$，$k<998244353$.

## 思路
考虑这个式子的意义，先不考虑数列的顺序，写出答案的 $\text{OGF }F(x)$。

不难发现

$$F(x)=\prod_{i=1}^k(1+ix)$$

这个先考虑 $\ln$ 后转成加法。

$$\begin{aligned}F(x)&=\exp\left(\sum_{i=1}^k\ln(1+ix)\right)\\\end{aligned}$$

我们知道：

$$\ln(1-x)=-\sum_{i=1}^{n}\frac{x^i}i$$

$$\begin{aligned}F(x)&=\exp\left(\sum_{i=1}^k\ln(1+ix)\right)\\&=\exp\left(-\sum_{i=1}^k\sum_{j=1}^n\frac{(-ix)^j}j\right)\\&=\exp\left(\sum_{j=1}^n\frac{(-1)^{j+1}}{j}x^j\sum_{i=1}^ki^j\right)\end{aligned}$$
现在要求 $j\in[1,n]$ 的自然数幂和。令它的 $\text{EGF}$ 为 $G(x)$：

$$\begin{aligned}G(x)&=\sum_{i=0}^n\dfrac{x^i}{i!}\sum_{j=1}^kj^i\\&=\sum_{j=1}^k\sum_{i=0}^n\dfrac{(jx)^i}{i!}\\&=\sum_{j=1}^ke^{jx}\\&=\dfrac{e^{x(k+1)}-e^x}{e^x-1}\end{aligned}$$

分子分母常数都是 $0$，同除 $x$ 就好了。

注意 $\text{EGF}$ 乘上 $i!$。

注意答案乘上 $n!$。

时间复杂度 $\Theta(n\log n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=1048576+10,mod=998244353,inv2=mod+1>>1;
namespace Init{
	int fac[N],ifac[N],inv[N],G[21][N];
	inline int qpow(int x,int y){
		int res=1;
		while(y){
			if(y&1) res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			y>>=1;
		}
		return res;
	}
	inline void getG(){
		for(int i=0;i<21;i++){
			int *P=G[i],W=1<<i;
			P[0]=1;
			P[1]=qpow(3,(mod-1)/(1<<i+1));
			const int tmp=P[1];
			for(int j=2;j<W;j++)
				P[j]=1ll*P[j-1]*tmp%mod;
		}
	}
	inline void Prefix(int L){
		fac[0]=1;
		for(int i=1;i<=L;i++)
			fac[i]=1ll*fac[i-1]*i%mod;
		ifac[L]=qpow(fac[L],mod-2);
		for(int i=L;i>=1;i--)
			ifac[i-1]=1ll*ifac[i]*i%mod;
		for(int i=1;i<=L;i++)
			inv[i]=1ll*ifac[i]*fac[i-1]%mod;
	}
}
using namespace Init;
namespace Poly{
	int lim,rev[N];
	int F[N],G[N],H[N];
	int T1[N],T2[N],T3[N];
	inline void init(int n,int mode=1){
		if(mode){
			int l=0;
			for(lim=1;lim<=n;lim<<=1)l++;
			for(int i=1;i<lim;i++)
				rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		}else{
			for(lim=1;lim<=n;lim<<=1);
		}
	}
	inline void NTT(int *a,int T){
		for(int i=0;i<lim;i++)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(int i=1,o=0;i<lim;i<<=1,o++){
			const int *P=::G[o];
			for(int j=0;j<lim;j+=(i<<1)){
				int t1,t2;
				for(int k=0;k<i;k++){
					t1=a[j+k];
					t2=1ll*P[k]*a[i+j+k]%mod;
					a[j+k]=(t1+t2)%mod;
					a[i+j+k]=(t1-t2+mod)%mod;
				}
			}
		}
		if(T==1) return ;
		int Inv=qpow(lim,mod-2);
		reverse(a+1,a+lim);
		for(int i=0;i<lim;i++)
			a[i]=1ll*a[i]*Inv%mod;
	}
	inline void Mul(int *a,int *b){
		for(int i=0;i<lim;i++)
			F[i]=b[i];
		NTT(a,1),NTT(F,1);
		for(int i=0;i<lim;i++)
			a[i]=1ll*a[i]*F[i]%mod;
		NTT(a,-1);
	}
	inline void Sqr(int *a,int *b){
		static int F[N];
		for(int i=0;i<lim;i++)
			F[i]=a[i];
		NTT(F,1);
		for(int i=0;i<lim;i++)
			b[i]=1ll*F[i]*F[i]%mod;
		NTT(b,-1);
	}
	inline void Inv(int *a,int *b,int n){
		static int T4[N];
		if(n==1){
			b[0]=qpow(a[0],mod-2);
			return ;
		}
		Inv(a,b,n+1>>1);
		init(n<<1);
		for(int i=0;i<n;i++)
			T4[i]=a[i];
		for(int i=n;i<lim;i++)
			T4[i]=0;
		NTT(b,1),NTT(T4,1);
		for(int i=0;i<lim;i++)
			b[i]=1ll*b[i]*(2-1ll*b[i]*T4[i]%mod+mod)%mod;
		NTT(b,-1);
		for(int i=n;i<lim;i++)
			b[i]=0;
	}
	inline void Der(int *a,int *b,int n){
		for(int i=1;i<n;i++)
			b[i-1]=1ll*i*a[i]%mod;
		b[n-1]=0;
	}
	inline void Int(int *a,int *b,int n){
		for(int i=1;i<n;i++)
			b[i]=1ll*a[i-1]*inv[i]%mod;
		b[0]=0;
	}
	inline void Log(int *a,int *b,int n){
		for(int i=0;i<lim;i++)
			T1[i]=T2[i]=0;
		Der(a,T1,n);
		Inv(a,T2,n);
		Mul(T1,T2);
		Int(T1,b,n);
	}
	inline void Exp(int *a,int *b,int n){
		if(n==1){
			b[0]=1;
			return ;
		}
		Exp(a,b,n+1>>1);
		init(n<<1,0);
		for(int i=0;i<lim;i++)
			T3[i]=0;
		Log(b,T3,n);
		for(int i=0;i<n;i++)
			T3[i]=(a[i]-T3[i]+mod)%mod;
		for(int i=n;i<lim;i++)
			b[i]=T3[i]=0;
		T3[0]++;
		Mul(b,T3); 
		for(int i=n;i<lim;i++)
			b[i]=0;
	}
	inline void QPow(int *a,int *b,int n,int k1,int k2){//k1:mod p;k2:mod φ(p) 
		static int T4[N],T5[N];
		int fir=0;
		for(;fir<n&&!a[fir];fir++);
		if(1ll*fir*k1>=n){
			for(int i=0;i<n;i++)
				b[i]=0;
			return ;
		}
		const int invf=qpow(a[fir],mod-2);
		const int powf=qpow(a[fir],k2);
		for(int i=0;i<n;i++)
			a[i]=1ll*a[i+fir]*invf%mod;
		Log(a,T4,n);
		for(int i=0;i<n;i++)
			a[i]=1ll*T4[i]*k1%mod;
		Exp(a,T5,n);
		fir*=k1;
		for(int i=0;i<fir;i++)
			b[i]=0;
		for(int i=fir;i<n;i++)
			b[i]=1ll*T5[i-fir]*powf%mod;
	}
	inline void Sqrt(int *a,int *b,int n){
		static int T4[N],T5[N];
		if(n==1){
			b[0]=1;
			return ;
		}
		Sqrt(a,b,n+1>>1);
		init(n<<1);
		for(int i=0;i<lim;i++)
			T4[i]=T5[i]=G[i]=0;
		for(int i=0;i<n;i++)
			T5[i]=a[i];
		Inv(b,T4,n);
		Mul(T4,T5);
		for(int i=0;i<n;i++)
			b[i]=1ll*inv2*(b[i]+T4[i])%mod;
		for(int i=n;i<lim;i++)
			b[i]=0;
	}
}
int k,n;
int T1[N],T2[N],T3[N],T4[N],T5[N];
inline void solve(int n){
	for(int i=1;i<n;i++)
		T1[i-1]=(1ll*(qpow(k+1,i)-1)*ifac[i])%mod,
		T2[i-1]=ifac[i];
	Poly::Inv(T2,T3,n);
	Poly::Mul(T1,T3);
	for(int i=0;i<n;i++)
		T1[i]=1ll*T1[i]*fac[i]%mod;
	for(int i=1;i<n;i++){
		int tmp=1ll*T1[i]*inv[i]%mod;
		if(i+1&1) T4[i]=mod-tmp;
		else T4[i]=tmp;
	}
	Poly::Exp(T4,T5,n);
	for(int i=0;i<n;i++)
		T5[i]=1ll*T5[i]*fac[i]%mod;
}
int main(){
	k=read(),n=read()+1;
	getG();
	Prefix(n+10);
	solve(n+10);
	for(int i=1;i<n;i++)
		write(T5[i]),putc('\n');
	flush();
}
```
再见 qwq~

---

## 作者：tylon2006 (赞：2)

3.00s 勇夺最劣解。 [提交记录](https://www.luogu.com.cn/record/70929185)

---

互不相同，可以集合划分容斥。

将选出的 n 个数分成 k 个集合，钦定每个集合中的数相同。

每个大小的块的贡献系数的生成函数显然为 $F(x)=1+x$。

设容斥系数的生成函数为 $G(x)$。

那么显然有 $F(x)=\exp(G(x))$，$G(x)=\ln F(x)$。

则 $g_i=(-1)^{i-1}(i-1)!$。

因为是乘积，每个块的贡献独立，求出单块贡献 exp 即可。

单块的贡献函数为 $H(x)=\sum_{i=1}^n\dfrac{g_i\sum_{j=1}^kj^i}{i!}$。

自然数幂和可以用伯努利数求。

因为有标号所以最后要乘上 $n!$。

---

#### code
```cpp
int main(){
	init(1<<20);
	work(5e5+10);
	scanf("%d%d",&n,&m);
	memcpy(a,ifac+1,8*(m+1));
	ull s=n+1; c[0]=n+1;
	for(int i=1;i<=m;++i)
	c[i]=c[i-1]*inv[i+1]%p[0]*s%p[0];
	invf(a,b,m+1,0);
	int lim=1;
	while(lim<=m) lim<<=1; lim<<=1;
	NTT(b,1,lim,0),NTT(c,1,lim,0);
	for(int i=0;i<lim;++i)
	c[i]=c[i]*b[i]%p[0];
	NTT(c,-1,lim,0);
	for(int i=1;i<=m;++i){
		h[i]=c[i]*fac[i-1]%p[0];
		if((i^1)&1) h[i]=p[0]-h[i];
	}
	expf(h,f,m+1,0);
	for(int i=1;i<=m;++i)
	out::write(f[i]*fac[i]%p[0]),out::putc('\n');
	out::flush();
}
```

---

## 作者：peterwuyihong (赞：2)

$\bmod\ 998244353$，nice

题意：给定 $k$，定义一个序列 $a_{[1,n]}$ 为牛逼的当且仅当 $1\le a_i\le k$，$a_i$ 互不相同，然后这个序列权值为 $\prod_{i=1}^na_i$，对于每个 $1\le i\le m$，求出 $n=i$ 时的所有牛逼序列权值和。$1\le m\le k\le998244352,m\le5\times10^{5}$。

反正所有 $a_i$ 互不相同，不妨设 $a_i$ 单调递增，最后乘上一个 $n!$ 即可。

于是你一眼看出来答案的生成函数 $\prod_{i=1}^k(1+ix)$，注意答案乘上一个 $n!$，把这个答案生成函数暴力乘开你就能发现这个答案的精神。

但是 $k$ 十分的大，于是你把它 $\ln$ 了，泰勒展开掉。

$$\sum_{i=1}^k\ln(1+ix)=-\sum_{i=1}^k\sum_{j\ge1}\frac{(-ix)^j}{j}$$

$$=\sum_{j\ge 1}\frac{(-1)^{j+1}x^j\sum_{i=1}^ki^j}{j}$$

我去，自然数幂！

$$<\sum_{i=1}^ki^0,\sum_{i=1}^ki^1,\sum_{i=1}^ki^2,\ldots>'s\ \text{EGF}$$

$$\sum_{j\ge0}\frac{\sum_{i=1}^ki^jx^j}{j!}=\sum_{i=1}^k\sum_{j\ge0}\frac{(ix)^j}{j!}=\sum_{i=1}^ke^{ix}=\frac{e^{(k+1)x}-e^x}{e^x-1}$$

上下约掉一个 $x$，大胆求乘法逆。

最后把最初柿子 $\exp$ 回去就行了，复杂度只有 $O(n\log n)$。

现在是 $19:26$，我看我什么时候写完。

现在是 $19:44$，我写完了。

```cpp
int m,k;
signed main(){
	cin>>k>>m;
	poly f(m+2),g(m+2);
	init(extend(m+2));
	for(int i=0;i<=m+1;i++){
		f[i]=Sub(Mul(ksm(k+1,i+1),jcinv[i+1]),jcinv[i+1]);
		g[i]=jcinv[i+1];
	}
	f=f*Inv(g);f.resize(m+2);
	poly ans(m+1);
	for(int i=1;i<=m;i++)ans[i]=Mul(jc[i-1],(i&1)?f[i]:p-f[i]);//注意f是EGF 
	ans=Exp(ans);
	for(int i=1;i<=m;i++)cout<<Mul(ans[i],jc[i])<<endl;
}
```
上面是我的多项式板子，[安利一波](https://www.luogu.com.cn/blog/Peterprpr/mu-ban)。

---

## 作者：TianTian2008 (赞：1)

首先求出不考虑元素顺序的答案，乘上 $n!$ 即为真正的答案。

不考虑元素顺序的答案的生成函数显然为 $\prod\limits_{i=1}^k(1+ix)$，这个形式很经典，直接取 $\ln$ 再 $\exp$ 回来即可。

$\begin{aligned}&\ln(1+ix)\\=&\int\ln'(1+ix)\text dx\\=&\int\frac1{1+ix}(1+ix)'\text dx\\=&\int\frac{i}{1-(-i)x}\text dx\\=&\int\sum\limits_{j=0}^\infty (-1)^ji^{j+1}x^j\text dx\\=&\sum\limits_{j=1}^\infty \frac{(-1)^{j-1}i^j}{j}x^j\end{aligned}$

$\begin{aligned}&\prod\limits_{i=1}^k(1+ix)\\=&\exp\sum\limits_{i=1}^k\sum\limits_{j=1}^\infty \frac{(-1)^{j-1}i^j}{j}x^j\\=&\exp\sum\limits_{j=1}^\infty x^j\frac{(-1)^{j-1}}{j}\sum\limits_{i=1}^ki^j\end{aligned}$

关键在如何求 $\sum\limits_{j=1}^\infty x^j\sum\limits_{i=1}^ki^j$，用 $\text{OGF}$ 就是 $\sum\limits_{i=1}^k\frac1{1-ix}$ 这种难以化简的形式，而用 $\text{EGF}$ 则是 $\sum\limits_{i=1}^k\mathrm{e}^{ix}=\frac{\mathrm{e}^{(k+1)x}-\mathrm{e}^x}{\mathrm{e}^x-1}$ 即可快速计算。

---

