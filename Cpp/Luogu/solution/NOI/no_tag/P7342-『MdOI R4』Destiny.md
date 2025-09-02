# 『MdOI R4』Destiny

## 题目背景

T5 的第一句话是假的。

## 题目描述

注意，本题中下标从 $0$ 开始。

一个长度为 $n$ 的序列 $\{a_i\}$ 的权值 $v(a)$ 定义为：
- $n=1$ 时为 $v(a)=a_0$。
- $n>1$ 时为它所有子区间的权值之和，也就是 $v(a_0,a_1,\ldots,a_{n-1})=\sum\limits_{i=0}^{n-2}\sum\limits_{j=0}^{n-i-1}v(a_j,a_{j+1},\ldots,a_{j+i})$. 

给定一个序列，求出它的的权值，答案对 $998244353$ 取模。

这个序列是这样生成的：输入序列 $b_0,b_1,\cdots,b_{k-1}$，然后 $a_i=b_{i\bmod k}$。

## 说明/提示

【样例解释 #1】

生成序列 $a=[3,4,6,3]$，然后：
- $v(3,4)=v(3)+v(4)=7$
- $v(4,6)=v(4)+v(6)=10$
- $v(6,3)=v(6)+v(3)=9$
- $v(3,4,6)=v(3)+v(4)+v(6)+v(3,4)+v(4,6)=30$
- $v(4,6,3)=v(4)+v(6)+v(3)+v(4,6)+v(6,3)=32$
- $v(3,4,6,3)=v(3)+v(4)+v(6)+v(3)+v(3,4)+v(4,6)+v(6,3)+v(3,4,6)+v(4,6,3)=104$

【数据规模与约定】

**本题不使用捆绑测试。**

本题共 $25$ 个测试点，每个测试点 $4$ 分。

|测试点编号|$n\le$|$k$|
|:-|:-|:-|
|$1\sim 3$|$5000$|无特殊限制|
|$4\sim 10$|$10^5$|无特殊限制|
|$11\sim 15$|无特殊限制|$=60928$|
|$16\sim 25$|无特殊限制|无特殊限制|

对于 $100\%$ 的数据 : $1\le n\le 10^9$，$1 \le k \le 10^5$，$0\le a_i\le 998244352$。

感谢 $\rm\textcolor{black}{J}\textcolor{red}{ohnVictor}$ 对此题的贡献。

## 样例 #1

### 输入

```
4 3
3 4 6
```

### 输出

```
104
```

## 样例 #2

### 输入

```
10 10
2 5 3 8 4 5 2 19 3 6
```

### 输出

```
219856
```

# 题解

## 作者：NaCly_Fish (赞：10)

~~教程：如何正确地使用 OEIS~~

首先当然是考虑每个数被算进答案多少次，设 $T_{n,k} \ (k\in[0,n])$ 是长为 $n+1$ 的序列中，第 $k+1$ 个数被算的次数。

随便打个暴力，在 OEIS 上可以找到[这个](http://oeis.org/A059576)数列，然后眼尖的你一眼就看到了递推式：
$$T_{n,k}=2(T_{n-1,k-1}+T_{n-1,k})-(2-[n=2])T_{n-2,k-1}\ (n\ge 2,k\ge1)$$
上面没给每行的生成函数，只好我们自己算了，，

这个 $[n=2]$ 的条件有点麻烦，如果假定 $T_{0,0} = \dfrac12$ 就简单很多。设 $T_n(x)$ 为 $\left\{ T_{n,k}\right\}_{k=0}^n$ 的生成函数，就有：
$$T_n(x)=2(1+x)T_{n-1}(x)-2xT_{n-2}(x)$$
按二阶递推数列解出来就是
$$T_n(x)=\frac{(1+x+\sqrt{x^2+1})^{n+1}-(1+x-\sqrt{x^2+1})^{n+1}}{4\sqrt{1+x^2}}$$
根据数列 $a$ 的构造方法，我们知道答案是
$$\sum_{i=0}^{n-1}b_{i \bmod k}T_{n-1,i}$$
而这实际上就是 $T_{n-1}(x) \bmod (x^k-1)$ 与序列 $b$ 的点积。要计算的话，就是维护一个 $F(x)=f(x)+\sqrt{1+x^2}g(x)$ 形式的多项式；而最后一步除 $\sqrt{1+x^2}$ 实际上就是提取其中 $g(x)$ 的系数。

顺便一提，容易证明 $(1+x+\sqrt{x^2+1})^n$ 和 $(1+x-\sqrt{x^2+1})^n$ 的 $\sqrt{1+x^2}$ 部分是互为相反数的，故可以只算一遍快速幂，常数减半。

代码奉上：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 262147
#define ll long long
#define reg register
#define p 998244353
using namespace std;

inline int read(){
	int x = 0;
	char c = getchar();
	while(c<'0'||c>'9') c = getchar();
	while(c>='0'&&c<='9'){
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	return x;
}

inline int add(const int& x,const int& y){ return x+y>=p?x+y-p:x+y; }
inline int dec(const int& x,const int& y){ return x<y?x-y+p:x-y; }
inline int rec(const int& x){ return x>=p?x-p:x; }

inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}

int siz;
int rev[N],rt[N],inv[N],fac[N],ifac[N];

void init(int n){
    int lim = 1;
    while(lim<=n) lim <<= 1,++siz;
    for(reg int i=0;i!=lim;++i) rev[i] = (rev[i>>1]>>1)|((i&1)<<(siz-1));
    int w = power(3,(p-1)>>siz);
    fac[0] = fac[1] = ifac[0] = ifac[1] = inv[1] = rt[lim>>1] = 1;
    for(reg int i=(lim>>1)+1;i!=lim;++i) rt[i] = (ll)rt[i-1]*w%p;
    for(reg int i=(lim>>1)-1;i;--i) rt[i] = rt[i<<1];
    for(reg int i=2;i<=n;++i) fac[i] = (ll)fac[i-1]*i%p;
    ifac[n] = power(fac[n],p-2);
    for(reg int i=n-1;i;--i) ifac[i] = (ll)ifac[i+1]*(i+1)%p;
    for(reg int i=2;i<=n;++i) inv[i] = (ll)fac[i-1]*ifac[i]%p;
}

inline void dft(int *f,int n){
    static unsigned long long a[N];
    reg int x,shift = siz-__builtin_ctz(n);
    for(reg int i=0;i!=n;++i) a[rev[i]>>shift] = f[i];
    for(reg int mid=1;mid!=n;mid<<=1)
    for(reg int j=0;j!=n;j+=(mid<<1))
    for(reg int k=0;k!=mid;++k){
        x = a[j|k|mid]*rt[mid|k]%p;
        a[j|k|mid] = a[j|k]+p-x;
        a[j|k] += x;
    }
    for(reg int i=0;i!=n;++i) f[i] = a[i]%p;
}

inline void idft(int *f,int n){
    reverse(f+1,f+n);
    dft(f,n);
    int x = p-((p-1)>>__builtin_ctz(n));
    for(reg int i=0;i!=n;++i) f[i] = (ll)f[i]*x%p;
}

inline int getlen(int n){
    return 1<<(32-__builtin_clz(n));
}

struct poly{
	int a[N],b[N];
	int t;
	
	inline poly(int _t=0):t(_t){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
	}
};

inline void getv(int lim,int *v){
	int rt = power(3,(p-1)/lim),x = 1;
	for(reg int i=0;i!=lim;++i){
		v[i] = ((ll)x*x+1)%p;
		x = (ll)x*rt%p;
	}
}

inline poly multiply(poly f,poly g){
	static int A[N],B[N],C[N],D[N],R[N],S[N],v[N];
	int n = f.t,lim = getlen(f.t<<1);
	getv(lim,v); // 这里是线性计算 (1+x^2) 的 dft，以减少此后的一次 idft
	poly h = poly(n);
	memcpy(A,f.a,n<<2),memcpy(B,f.b,n<<2);
	memcpy(C,g.a,n<<2),memcpy(D,g.b,n<<2);
	memset(A+n,0,(lim-n+2)<<2),memset(B+n,0,(lim-n+2)<<2);
	memset(C+n,0,(lim-n+2)<<2),memset(D+n,0,(lim-n+2)<<2);
	dft(A,lim),dft(B,lim),dft(C,lim),dft(D,lim);
	for(reg int i=0;i!=lim;++i){
		R[i] = ((ll)A[i]*C[i]+(ll)B[i]*D[i]%p*v[i])%p;
		S[i] = ((ll)A[i]*D[i]+(ll)B[i]*C[i])%p;
	}
	idft(R,lim),idft(S,lim);
	for(reg int i=0;i!=n;++i){
		h.a[i] = add(R[i],R[i+n]);
		h.b[i] = add(S[i],S[i+n]);
	}
	h.a[0] = add(h.a[0],R[n<<1]);
	h.a[1] = add(h.a[1],R[n<<1|1]);
	return h;
}

inline poly square(poly f){ // 算平方的时候可以减少 dft 次数
	static int A[N],B[N],R[N],S[N],v[N];
	int n = f.t,lim = getlen(f.t<<1);
	getv(lim,v);
	poly h = poly(n);
	memcpy(A,f.a,n<<2),memcpy(B,f.b,n<<2);
	memset(A+n,0,(lim-n+2)<<2),memset(B+n,0,(lim-n+2)<<2);
	dft(A,lim),dft(B,lim);
	for(reg int i=0;i!=lim;++i){
		R[i] = ((ll)A[i]*A[i]+(ll)B[i]*B[i]%p*v[i])%p;
		S[i] = ((ll)A[i]*B[i]<<1)%p;
	}
	idft(R,lim),idft(S,lim);
	for(reg int i=0;i!=n;++i){
		h.a[i] = add(R[i],R[i+n]);
		h.b[i] = add(S[i],S[i+n]);
	}
	h.a[0] = add(h.a[0],R[n<<1]);
	h.a[1] = add(h.a[1],R[n<<1|1]);
	return h;
}

inline poly power(poly f,int n,int t){
	poly g = poly(n);
	g.a[0] = 1;
	while(t){
		if(t&1) g = multiply(f,g);
		t >>= 1;
		if(t==0) break;
		f = square(f);
	}
	return g;
}

int n,k,ans;
poly f;
int a[N];

int main(){
    n = read(),k = read();
    init(k<<1);
    f.t = k;
    f.a[0] = f.a[1] = f.b[0] = 1;
    f = power(f,k,n);
    for(reg int i=0;i!=k;++i) ans = (ans+(ll)f.b[i]*read())%p;
    printf("%lld",(ll)ans*power(2,p-2)%p);
    return 0;   
}
```

---

## 作者：Karry5307 (赞：8)

### 题意

略。

$\texttt{Data Range:}1\leq n\leq 10^9,1\leq k\leq 10^5$

### 题解

验题人题解。

考虑算出每个数被算的次数，设 $f_{i,j}$ 表示当序列长度为 $i$ 的时候位置 $j$ 被算了多少次。

根据定义，对于 $j$ 这个位置，它的答案是所有包含这个位置的区间的贡献之和。同时因为长度相等的区间对应位置被算的次数相等，枚举子区间两个端点有

$$f_{i,j}=\sum\limits_{k\leq i,l\leq j,(k,l)\neq (i,j)}f_{k,l}$$

很明显可以二维前缀和优化。设 $g_{i,j}$ 为 $f_{i,j}$ 的二维前缀和，有 $f_{i,j}=g_{i,j}-f_{i,j}$，即 $g_{i,j}=2f_{i,j}$。

同时结合二维前缀和的递推，即 $g_{i,j}=g_{i-1,j}+g_{i,j-1}-g_{i-1,j-1}+f_{i,j}$ 有

$$f_{i,j}=2f_{i-1,j}+2f_{i,j-1}-2f_{i-1,j-1}$$

暴力 DP 可以拿到 $12$ 分的好成绩。

设 $F_i(x)$ 表示 $f$ 的一行的生成函数，则有

$$F_i(x)=2(x+1)F_{i-1}(x)+2xF_{i-2}(x)$$

用特征方程解递推式有

$$F_n(x)=\frac{(x+\sqrt{x^2+1})^n-(x-\sqrt{x^2+1})^n}{4 \sqrt{x^2+1}}$$

然而序列的特殊性质，我们只需要求出所有 $\bmod\ k$ 为某个值的系数之和，这个其实就是将多项式对 $x^k-1$ 取模，相当于做循环卷积。

这个时候因为循环卷积平方根没办法做，所以考虑扩域维护这个东西。也即维护 $F(x)+G(x)\sqrt{x^2+1}$ 这类东西然后快速幂就好了，时间复杂度 $O(k\log k\log n)$，视实现可获得 $0\sim 100$ pts 不等的好成绩。

讲几个卡常技巧：

- NTT 板子直接决定了你程序跑得快不快。

- 在算两个 $F(x)+G(x)\sqrt{x^2+1}$ 乘积的时候使用类似于 Karatsuba 的思路可以少一次 DFT。

- 快速幂平方的时候不用常规的乘法能少 DFT 次数。

- 将指数拆成 $32768a+b$ 的形式可以多利用平方。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
typedef unsigned long long int ull;
typedef vector<ll> Poly;
const ll MAXN=262151,MOD=998244353,G=3,INVG=332748118,INV4=748683265;
struct F{
	Poly f0,f1;
};
F g;
ll n,fd,res;
ll rev[MAXN],omgs[MAXN],f[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=(li)res*base%MOD;
        }
        base=(li)base*base%MOD,exponent>>=1;
    }
    return res;
}
inline void setupOmg(ll cnt)
{
    ll limit=__lg(cnt)-1;
    omgs[0]=1,omgs[1<<limit]=qpow(31,1<<(21-limit));
    for(register int i=limit;i;i--)
    {
        omgs[1<<(i-1)]=(li)omgs[1<<i]*omgs[1<<i]%MOD;
    }
    for(register int i=1;i<cnt;i++)
    {
        omgs[i]=(li)omgs[i&(i-1)]*omgs[i&-i]%MOD;
    }
}
inline ll& reduce(ll &x)
{
	return x+=x>>31&MOD;
}
inline void DIF(ll *cp,ll cnt)
{
	ll lim=__lg(cnt),len=cnt>>1,x;
	for(register int i=0;i<lim;i++,len>>=1)
	{
		for(register int *j=cp,*omg=omgs;j!=cp+cnt;j+=len<<1,omg++)
		{
			for(register int *k=j;k!=j+len;k++)
			{
				x=(li)*omg*k[len]%MOD,reduce(k[len]=*k-x),reduce(*k+=x-MOD);
			}
		}
	}
}
inline void DIT(ll *cp,ll cnt)
{
	ll lim=__lg(cnt),len=1,x,invl;
	for(register int i=0;i<lim;i++,len<<=1)
	{
		for(register int *j=cp,*omg=omgs;j!=cp+cnt;j+=len<<1,omg++)
		{
			for(register int *k=j;k!=j+len;k++)
			{
				reduce(x=*k+k[len]-MOD);
				k[len]=(li)(*k-k[len]+MOD)**omg%MOD,*k=x;
			}
		}
	}
	reverse(cp+1,cp+cnt),invl=MOD-(MOD-1)/cnt;
	for(register int i=0;i<cnt;i++)
	{
		cp[i]=(li)cp[i]*invl%MOD;
	}
}
inline void NTT(ll *cp,ll cnt,ll inv)
{
    inv==1?DIF(cp,cnt):DIT(cp,cnt);
}
inline void conv(ll fd,ll *f,ll *g,ll *res)
{
    static ll tmpf[MAXN],tmpg[MAXN];
    ll cnt=1,limit=-1;
    while(cnt<(fd<<1))
    {
        cnt<<=1,limit++;
    }
    for(register int i=0;i<cnt;i++)
    {
		tmpf[i]=i<fd?f[i]:0,tmpg[i]=i<fd?g[i]:0;
    }
    NTT(tmpf,cnt,1),NTT(tmpg,cnt,1);
    for(register int i=0;i<cnt;i++)
    {
        tmpf[i]=(li)tmpf[i]*tmpg[i]%MOD;
    }
    NTT(tmpf,cnt,-1),memcpy(res,tmpf,fd<<3);
}
inline void printPoly(const Poly &f)
{
	for(register int i:f)
	{
		printf("%d ",i);
	}
	puts("");
}
inline Poly operator +(const Poly &f,const Poly &g)
{
	Poly res;
	ll fd=f.size(),gd=g.size();
	res.resize(max(fd,gd));
	for(register int i=0;i<res.size();i++)
	{
		reduce(res[i]=(i<fd?f[i]:0)+(i<gd?g[i]:0)-MOD);
	}
	return res;
}
inline Poly operator -(const Poly &f,const Poly &g)
{
	Poly res;
	ll fd=f.size(),gd=g.size();
	res.resize(max(fd,gd));
	for(register int i=0;i<res.size();i++)
	{
		reduce(res[i]=(i<fd?f[i]:0)-(i<gd?g[i]:0));	
	}
	return res;
}
inline Poly operator *(const Poly &f,const Poly &g)
{
	Poly res;
	static ll tmpf[MAXN],tmpg[MAXN];
	ll fd=f.size(),gd=g.size();
	if(!fd||!gd)
	{
		return {};
	}
	res.resize(fd+gd-1);
	if((li)fd*gd<=1000000)
	{
		for(register int i=0;i<fd;i++)
		{
			for(register int j=0;j<gd;j++)
			{
				res[i+j]=(res[i+j]+(li)f[i]*g[j])%MOD;
			}
		}
		for(register int i=res.size()-1;i>=::fd;i--)
		{
			reduce(res[i-::fd]+=res[i]-MOD),res.pop_back();
		}
		return res;
	}
	for(register int i=0;i<max(fd,gd);i++)
	{
		tmpf[i]=i<fd?f[i]:0,tmpg[i]=i<gd?g[i]:0;
	}
	conv(max(fd,gd),tmpf,tmpg,tmpf),copy(tmpf,tmpf+res.size(),res.begin());
	for(register int i=res.size()-1;i>=::fd;i--)
	{
		reduce(res[i-::fd]+=res[i]-MOD),res.pop_back();
	}
	return res;
}
inline F operator -(F f,F g)
{
	return {f.f0-g.f0,f.f1-g.f1};
}
inline F operator *(F f,F g)
{
	Poly r1=f.f0*g.f0,r2=f.f1*g.f1,rs=(f.f0+f.f1)*(g.f0+g.f1),r3;
	ll fd=r2.size(),r=fd+1-::fd;
	r3.resize(fd+2);
	for(register int i=0;i<fd;i++)
	{
		reduce(r3[i]+=r2[i]-MOD),reduce(r3[i+2]+=r2[i]-MOD);
	}
	r>=0?reduce(r3[r]+=r3[fd+1]-MOD),r3.pop_back():(void)1;
	r>=1?reduce(r3[r-1]+=r3[fd]-MOD),r3.pop_back():(void)1;
	return {r1+r3,rs-r1-r2};
}
inline void reduce(vector<ll> &v)
{
	for(register int i=v.size()-1;i>=fd;i--)
	{
		reduce(v[i-fd]+=v[i]-MOD),v.pop_back();
	}
}
inline F sqr(F f)
{
	ll fd0=f.f0.size(),fd1=f.f1.size(),fd=max(fd0,fd1),cnt=1,r;
	ll tmpr1[MAXN],tmpr2[MAXN],tmprs[MAXN];
	Poly r1,r2,r3,rs;
	while(cnt<=(fd<<1))
	{
		cnt<<=1;
	}
	for(register int i=0;i<cnt;i++)
	{
		tmpr1[i]=i<fd0?f.f0[i]:0,tmpr2[i]=i<fd1?f.f1[i]:0;
		tmprs[i]=0;
	}
	NTT(tmpr1,cnt,1),NTT(tmpr2,cnt,1);
	for(register int i=0;i<cnt;i++)
	{
		tmprs[i]=(li)tmpr1[i]*tmpr2[i]%MOD;
		tmpr1[i]=(li)tmpr1[i]*tmpr1[i]%MOD;
		tmpr2[i]=(li)tmpr2[i]*tmpr2[i]%MOD;
	}
	NTT(tmpr1,cnt,-1),NTT(tmpr2,cnt,-1),NTT(tmprs,cnt,-1);
	if(fd0*2-1>0)
	{
		r1.resize(fd0*2-1),copy(tmpr1,tmpr1+r1.size(),r1.begin()),reduce(r1);
	}
	if(fd1*2-1>0)
	{
		r2.resize(fd1*2-1),copy(tmpr2,tmpr2+r2.size(),r2.begin()),reduce(r2);
	}
	if(fd0+fd1-1>0)
	{
		rs.resize(fd0+fd1-1),copy(tmprs,tmprs+rs.size(),rs.begin()),reduce(rs);
	}
	fd=r2.size(),r=fd+1-::fd,r3.resize(fd+2);
	for(register int i=0;i<fd;i++)
	{
		reduce(r3[i]+=r2[i]-MOD),reduce(r3[i+2]+=r2[i]-MOD);
	}
	r>=0?reduce(r3[r]+=r3[fd+1]-MOD),r3.pop_back():(void)1;
	r>=1?reduce(r3[r-1]+=r3[fd]-MOD),r3.pop_back():(void)1;
	return {r1+r3,rs+rs};
}
inline void qpow(ll exponent)
{
	ll lo,hi;
	F rgl,rgh;
	hi=exponent>>15,lo=exponent&32767;
	rgl.f0.push_back(1),rgh.f0.push_back(1);
	while(hi||lo)
	{
		hi&1?rgh=rgh*g,1:1,lo&1?rgl=rgl*g,1:1;
		g=sqr(g),hi>>=1,lo>>=1;
	}
	for(register int i=0;i<15;i++)
	{
		rgh=sqr(rgh);
	}
	g=rgh*rgl;
	for(register int i=0;i<g.f1.size();i++)
	{
		reduce(f[i]=g.f1[i]*2-MOD);
	}
}
int main()
{
	n=read(),fd=read(),setupOmg(262144),g.f0.resize(2),g.f1.resize(2);
	g.f0[0]=g.f0[1]=g.f1[0]=1,qpow(n);
	for(register int i=0;i<fd;i++)
	{
		res=(res+(li)f[i]*read())%MOD;
	}
	printf("%d\n",(li)res*INV4%MOD);
}
```

---

## 作者：JohnVictor (赞：3)

官方题解qwq。

首先可以发现这个性质：最后的答案一定是 $\sum\limits_{i=1}^n v_ia_i$ 的形式，其中 $v_i$ 是和 $a_i$ 无关的常数。

我们试图求出 $v_i$。为了方便定义，定义 $w_{i,j}$ 为序列长度为 $i+j-1$ 时，$v_j$ 的值，也就是前面 $i$ 个，后面 $j$ 个。

根据区间权值的定义，一个区间的权值为所有真子区间的权值之和，考虑 $w_{i,j}$，它是所有包含 $j$ 的子区间对这一项的贡献之和，再注意一下位置，就可以得到

$w_{i,j}=\sum\limits_{x \le i,y \le j,(x,y) \neq (i,j)}w_{x,y}$

这里，只用注意到原来序列的第 $j$ 位可能是一个长为 $x$ 的子区间的 $1,2,...,j$ 位。

这时记 $S_{x,y}=\sum\limits_{i \le x}\sum\limits_{j \le y}w_{i,j}$ 为 $w$ 数组的二维前缀和，上面的式子化简为 $2w_{x,y}=S_{x,y}$。

再结合二维前缀和的基本递推有 $S_{i,j}=S_{i,j-1}+S_{i-1,j}-S_{i-1,j-1}+w_{i,j}$，代入化简得到

$w_{i,j}=2w_{i-1,j}+2w_{i,j-1}-2w_{i-1,j-1}$

如果到此停止，写一个 $O(n^2)$ 的 $dp$，能得到 $10$ 分的好成绩。

继续推式子，我们设第 $i$ 行的生成函数为 $f_i(x)$，那么根据上面的递推式直接能得到

$f_{i+1}(x)=2(x+1)f_i(x)-2xf_{i-1}(x)$

直接当做二阶线性递推数列就能解得 $f_x=\frac{(x+\sqrt{x^2+1})^n-(x-\sqrt{x^2+1})^n}{4 \sqrt{x^2+1}}$。

如果这时候直接计算 $f_n(x)$ 就可以得到所需要的答案，使用倍增或者你喜欢的方法并结合 NTT 都可以做到 $O(n\log n)$ 的复杂度。

然而这还不够优秀，我们只用对所有的 $i$ 求出 $\bmod k$ 于 $i$ 的项的系数和。

为此，我们可以求出 $f_n(x)$ 在 $w,w^2,\cdots,w^k$ 处的点值，其中 $w$ 为本原的 $k$ 次单位根，然后进行一次 IDFT 就能得到系数和。当 $k=60928$ 时，$k|p-1$，所以单位根有模意义，只用扩域维护根号就能求出点值。

当然这一做法还是不够优秀，我们直接写出正解：

本质上我们要求的是这个多项式 $\bmod (x^k-1)$ 之后的余式，那么我们所有的操作都可以直接在这个模意义下完成。

如果是这个模意义下的两个正常的多项式，那么直接循环卷积就能得到最后的答案，但是问题就是根号，所以我们带着根号一起维护，也就是维护 $P(x)+\sqrt{x^2+1}Q(x)$ 形式的多项式，其中 $P,Q$ 为不超过 $k-1$ 次的多项式。乘法的时候直接使用 $(\sqrt{x^2+1})^2=x^2+1$ 就可以了。

对这样的数做快速幂就能在 $O(k\log n \log k)$ 的复杂度内解决问题。

当然这看着是 $2\log$ 但是并不能十分轻松的过题，就好比你 LCT 多一个 $\log$ 不能十分轻松的通过 $10^5$ 的数据范围。

数据还是比较友善的，部分点 $n$ 中的 $1$ 比较少方便常数较大的通过。

稍微说几个卡常技巧：

（1）NTT 板子最好预处理单位根并使用 DIF 版本。

（2）计算这种数的乘法的时候，例如是 $(a+b\sqrt{w^2+1})(c+d\sqrt{w^2+1})$ 的时候，只用计算 $3$ 次乘法 $ab,cd,(a+b)(c+d)$，和 Karatsuba 算法原理相同。

（3）在平方的时候，可以只计算一遍 DFT 点值。 

时限为 std 的 $4$ 倍。



---

