# polynomial

## 题目背景

Wolfycz 很喜欢多项式（雾

## 题目描述

Wolfycz 喜欢研究多项式，尤其喜欢研究 $(a+b)^n$ 这样简单的问题，我们知道 $(a+b)^n=\sum\limits_{i=0}^n\binom{n}{i}a^ib^{n-i}$，但是 Wolfycz 对这样的式子并不满足，于是他把所有的系数全部改成了 $1$，即 $\sum\limits_{i=0}^na^ib^{n-i}$，但是 Wolfycz 发现自己太菜了，不会求答案，于是希望你来帮帮他。

UPD：请注意常数因子对程序运行效率的影响。

## 说明/提示

对于$30\%$的数据，$T\leqslant 100,n,a,b,p\leqslant 10^5$

对于$100\%$的数据，$T\leqslant 10^5,n,a,b,p\leqslant 10^{18}$

UPD：不保证$p$为质数！！！

## 样例 #1

### 输入

```
5
12 78 35 317
35 57 19 193
94 31 75 571
64 80 14 857
74 16 42 751
```

### 输出

```
254
24
283
796
407```

# 题解

## 作者：ftiasch (赞：9)


这是一篇关于常数的题解，截止 2022 年 12 月 30 日我是最优解。

## 算法的常数

为了方便分析，假设 $n=2^k - 1$，也就是 $k = O(\log n)$.

如果使用矩阵乘法，两个 $2 \times 2$ 的矩阵相乘需要 $8$ 次乘法（如果考虑 Strassen algorithm 则是 7 次），所以计算 $M^n$ 需要 $16k$ 次乘法（$8k$ 次平方，$8k$ 次乘法）。

一个更好的方法是设 $A(n) = a^n$，$B(n) = b^n$，$S(n) = \sum_{i = 0} a^i b^{n - i}$。我们有递归关系：

* 当 $n$ 是偶数的时候，$A(n) = (A(n/2))^2$，$B(n) = (B(n/2))^2$, $S(n) = S(n/2)\,(A(n/2) + B(n/2)) - A(n/2)\,B(n/2)$，这需要 $4$ 次乘法。
* 当 $n$ 是奇数的时候，$A(n) = a\,A(n-1)$, $B(n) = b\,B(n-1)$，$S(n) = a\,S(n - 1) + B(n)$，这需要 $3$ 次乘法。

所以计算 $S(n)$ 需要 $7k=4k+3k$ 次乘法。

当然，当 $n$ 是奇数的时候，我们可以先计算 $A' = a\,A(n/2)$ 和 $B' = b\,B(n/2)$，然后 $S(n) = S(n/2)\,(A' + B')$, $A(n) = A'\,A(n/2)$, $B(n)=B'B(n/2)$，这需要 5 次乘法。总共计算 $S(n)$ 需要 $5k$ 次乘法。

## 实现的常数

根据我的 benchmark，在 64 位模数下，Barrett Multiplication 比直接调用 `%` 快 4 倍。

```plain
-------------------------------------------------------------------------------
mod_64 - BarrettMod64T<>

benchmark name                            samples    iterations          mean
bench                                          100             3     4.5259 us 

-------------------------------------------------------------------------------
mod_64 - NonConstMod64T<>

benchmark name                            samples    iterations          mean
bench                                          100             1    19.6215 us 
===============================================================================
```

所以你应该使用 Barrett Multiplication。

最后加上快速读入。

---

## 作者：Memory_of_winter (赞：6)

[我的博客](https://www.cnblogs.com/Memory-of-winter/p/10354967.html)

**题目大意：**求：
$$\sum\limits_{i=0}^na^{n-i}b^i\pmod{p}$$
$T(T\leqslant10^5)$组数据，$a,b,n,p\leqslant10^{18}$

**题解：**$\sum\limits_{i=0}^na^{n-i}b^i=\dfrac{a^{n+1}-b^{n+1}}{a-b}$，然后$a-b$可能在$\pmod p$下没有逆元或者干脆是$0$。

出题人给了一个递归讨论$n$奇偶性的做法。（出题人在题解中各种表达他的毒瘤）

这边讲一个矩阵快速幂的。

令$f_n=\sum\limits_{i=0}^na^{n-i}b^i$

考虑$f_n\to f_{n+1}$，发现$f_{n+1}=af_n+b^{n+1}$，于是就可以愉快地矩阵快速幂啦。转移矩阵：
$$\left[\begin{matrix}a&0\\1&b\end{matrix}\right]$$

把$[f_n,b^{n+1}]$左乘转移矩阵就可以得到$[f_{n+1},b_{n+2}]$，为了方便，可以把向量写成矩阵，然后发现若初始矩阵如下时：
$$\left[\begin{matrix}0&0\\1&b\end{matrix}\right]$$
转移矩阵、状态矩阵右上角一定为$0$，就可以减少常数啦！



**C++ Code：**

```cpp
#include <cstdio>
#include <cctype>
namespace std {
	struct istream {
#define M (1 << 22 | 3)
		char buf[M], *ch = buf - 1;
		inline istream() { fread(buf, 1, M, stdin); }
		inline istream& operator >> (int &x) {
			while (isspace(*++ch));
			for (x = *ch & 15; isdigit(*++ch); ) x = x * 10 + (*ch & 15);
			return *this;
		}
		inline istream& operator >> (long long &x) {
			while (isspace(*++ch));
			for (x = *ch & 15; isdigit(*++ch); ) x = x * 10 + (*ch & 15);
			return *this;
		}
#undef M
	} cin;
	struct ostream {
#define M (1 << 20 | 3)
		char buf[M], *ch = buf - 1;
		inline ostream& operator << (long long x) {
			if (!x) {*++ch = '0'; return *this;}
			static int S[20], *top; top = S;
			while (x) {*++top = x % 10 ^ 48; x /= 10;}
			for (; top != S; --top) *++ch = *top;
			return *this;
		}
		inline ostream& operator << (const char x) {*++ch = x; return *this;}
		inline ~ostream() { fwrite(buf, 1, ch - buf + 1, stdout); }
#undef M
	} cout;
}

int Tim;
long long n, a, b, mod;

inline void reduce(long long &x) { x += x >> 63 & mod; }
inline long long mul(long long x, long long y) {
	long long res = x * y - static_cast<long long> (static_cast<long double> (x) * y / mod + 0.5) * mod;
	return res + (res >> 63 & mod);
}

struct Matrix {
	long long s00, s10, s11;
	Matrix() { }
	Matrix(long long __s00, long long __s10, long long __s11) : s00(__s00), s10(__s10), s11(__s11) { }
#define M(l, r) mul(s##l, rhs.s##r)
	inline void operator *= (const Matrix &rhs) {
		static long long __s00, __s10, __s11;
		__s00 = M(00, 00);
		reduce(__s10 = M(10, 00) + M(11, 10) - mod);
		__s11 = M(11, 11);
		s00 = __s00, s10 = __s10, s11 = __s11;
	}
#undef M
} ;

long long calc(long long n) {
	a %= mod, b %= mod;
	Matrix base(a, 1, b), res(0, 1, b);
	for (; n; n >>= 1, base *= base) if (n & 1) res *= base;
	return res.s10;
}

int main() {
	std::cin >> Tim;
	while (Tim --> 0) {
		std::cin >> n >> a >> b >> mod;
		std::cout << calc(n) << '\n';
	}
	return 0;
}

```



---

## 作者：Wolfycz (赞：4)

显然有$\sum\limits_{i=0}^na^ib^{n-i}=\dfrac{a^{n+1}-b^{n+1}}{a-b}$，不过出题人为了卡掉这个做法，选择了读入膜数$p$，这样就导致$a-b$可能不存在$\%p$意义下的逆元……~~(a掉出题人)~~

这题我们考虑分治，对$n$的奇偶性进行讨论：

- 若$n$为奇数，则有$\sum\limits_{i=0}^na^ib^{n-i}=(\sum\limits_{i=0}^{\lfloor n/2\rfloor}a^ib^{\lfloor n/2\rfloor-i})\times(a^{\lfloor n/2\rfloor+1}+b^{\lfloor n/2\rfloor+1})$
- 若$n$为偶数，则有$\sum\limits_{i=0}^na^ib^{n-i}=(\sum\limits_{i=0}^{n/2}a^ib^{n/2-i})\times(a^{n/2}+b^{n/2})-a^{n/2}b^{n/2}$

注意在计算$a^{n/2},b^{n/2}$的时候不能使用快速幂，应该在递归的时候不断平方，否则时间复杂度是$O(T\log^2 n)$，这样显然是过不了的

然后注意由于$p$过大，乘起来会爆long long，于是我们可以用__int128……~~（如果没记错我应该是卡了int128，但是吸口氧应该能过）~~

化乘为加也不行，会给复杂度添个$\log$~~（无良出题人啊）~~，因此我们使用下面这个乘法

```cpp
typedef long long ll;
typedef long double ld;
ll mlt(ll _a,ll _b,ll _p){
	ll _c=ld(_a)*_b/_p;
	ll _ans=_a*_b-_c*_p;
	if (_ans<0)	_ans+=_p;
	return _ans;
}
```

乘的过程中，如果溢出了就不管了，反正两个部分溢出的是一样的，相减即可把溢出部分消掉。~~(你要相信出题人用的也是这个，不然他造不了数据)~~

ps：对于所有的数据点，化乘为加与该乘法输出答案相同

```cpp
/*program from Wolfycz*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define inf 0x7f7f7f7f
#define sqr(x) mlt(x,x)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned int ui;
typedef unsigned long long ull;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for (;ch<'0'||ch>'9';ch=getchar())	if (ch=='-')	f=-1;
	for (;ch>='0'&&ch<='9';ch=getchar())	x=(x<<1)+(x<<3)+ch-'0';
	return x*f;
}
inline void print(int x){
	if (x>=10)	 print(x/10);
	putchar(x%10+'0');
}
ll a,b,n,p,Afac,Bfac;
ll mlt(ll _a,ll _b){
	ll _c=ld(_a)*_b/p;
	ll _ans=_a*_b-_c*p;
	if (_ans<0)	_ans+=p;
	return _ans;
}
ll work(ll n){
	if (n<=1)	return !n?1:(a+b)%p;
	ll sum=work(n>>1);
	Afac=sqr(Afac),Bfac=sqr(Bfac);
	if (n>>1&1)	Afac=mlt(Afac,a),Bfac=mlt(Bfac,b);
	return n&1?mlt(mlt(Afac,a)+mlt(Bfac,b),sum):(mlt(Afac+Bfac,sum)-mlt(Afac,Bfac)+p)%p;
}
int main(){
	for (int Data=read();Data;Data--){
		scanf("%lld%lld%lld%lld",&n,&a,&b,&p),Afac=Bfac=1;
		printf("%lld\n",(work(n)+p)%p);
	}
	return 0;
}
```

---

## 作者：jiangby2011 (赞：0)

### 前言

不开 ( ) 见祖宗。

## 正文

首先发现这个数据范围极其的大。

然后发现这个答案好像能递推。

那么矩阵乘法基本没跑。

以下 $f_n = \sum_{i = 0}^{n} a^i b^ {n - i}$

那么搞一下递推公式。

$$f_{n + 1} = \sum_{i = 0}^{n + 1}a^ib^{n - i + 1} = b\sum_{i = 0}^{n} a^ib^{n - i} + a^{n + 1} = f_n \times b + a ^ {n + 1}$$

直接构造。

$$\begin{bmatrix} f_n & a^n \end{bmatrix} \times \begin{bmatrix} b & 0 \\ a & a\end{bmatrix} = \begin{bmatrix} f_n \times b + a & a^{n + 1} \end{bmatrix} = \begin{bmatrix} f_{n + 1} & a ^{n + 1}\end{bmatrix}$$

这是不是可以根据结合律，直接对咱们构造出来的这个矩阵进行一个快速幂就可以了。

最后别忘了答案还要乘一下最开始的矩阵。卡常力度不大，也不需要什么很高级的优化。


```cpp
#include <bits/stdc++.h>

#define Int __int128 //看范围有点大，保险开一下int128

Int n , a , b , p;

inline Int read() {
	Int x = 0; int f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
	return x * f;
}

inline void write(Int x) {
	if(x > 9) {write(x / 10);}
	putchar(x % 10 + '0');
}

struct Matrix {
	Int c[2][2];
	Matrix() {
		c[0][0] = c[0][1] = c[1][1] = c[1][0] = 0;
	}
	
	inline Matrix operator * (const Matrix & rhs) const {
		Matrix Ans;
		Ans.c[0][0] = (c[0][0] * rhs.c[0][0] + c[0][1] * rhs.c[1][0]); Ans.c[0][0] = Ans.c[0][0] >= p ? Ans.c[0][0] % p : Ans.c[0][0]; 
		Ans.c[1][0] = (c[1][0] * rhs.c[0][0] + c[1][1] * rhs.c[1][0]); Ans.c[1][0] = Ans.c[1][0] >= p ? Ans.c[1][0] % p : Ans.c[1][0];
 		Ans.c[1][1] = (c[1][0] * rhs.c[0][1] + c[1][1] * rhs.c[1][1]); Ans.c[1][1] = Ans.c[1][1] >= p ? Ans.c[1][1] % p : Ans.c[1][1];
        //这里优化一下常数，手动写
		return Ans;
	}
}B;

inline Matrix fastP(Matrix a , register Int n) {//注意这个n不能用int，否则T掉7个点
	Matrix res;
	res.c[0][0] = res.c[1][1] = 1;//单位矩阵
	while(n) {
 		if(n & 1) {
 			res = res * a;
		}
		a = a * a;
		n >>= 1;
	}	
	return res;//对我们构造出来的矩阵做快速幂
}

namespace P5137 {
	
	void Main() {
		n = read() , a = read() , b = read() , p = read();
		B.c[0][0] = b ; B.c[1][0] = B.c[1][1] = a;
		B = fastP(B , n);
		write((B.c[0][0] + B.c[1][0]) % p);//最后直接乘最开始的矩阵，这里直接给算出来了
		putchar('\n');
	}
}
int main() {
	int T; T = read();
	while(T--) {
		P5137 :: Main();
	}
 }
```

---

## 作者：__ZTY__ (赞：0)

## 思路1

不难发现所求内容是多次方差公式的第二部分。

$a^n-b^n=(a-b)\times(a^{n-1}+a^{n-2} \times b+……+a \times b^{n-2}+b^{n-1})$

但是难受的一点题目模数是输入的，并且不保证是个质数，直接卡掉这种方法。

## 思路2

观察题目性质。

令 $f(x)=\sum^{x-1}_{i=0}a^i \times b^{x-i}$ 

不难发现 $f(x)=f(x-1) \times a +b^{x-1}$

这样就很显然可以用矩阵快速幂来做。

构造 $\begin{bmatrix}a&0\\1&b\end{bmatrix}$ 这样一个矩阵便可以满足。

## reminder

也是这道题非常恶心的一点。

乘法取模可能会溢出，会被卡。

```cpp
long long mul(long long s,long long t){
    long long rt=s*t-((long long)((long double)s/p*t+0.5))*p;
    return rt<0?rt+p:rt;
}
```
使用以上方法解决。

## AC代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

inline void read(int& a){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-'){f=-1;}c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	a=s*f;
}

int T,n,p,a,b;
int mul(int s,int t){
    int rt=s*t-((int)((long double)s/p*t+0.5))*p;
    return rt<0?rt+p:rt;
}

struct matrix{
	int m[2][2];
	matrix(){memset(m,0,sizeof(m));}
	void set1(){memset(m,0,sizeof(m));m[0][0]=a;m[1][0]=1;m[1][1]=b;m[0][1]=0;}
	void set2(){m[0][0]=m[1][1]=1;}
	matrix operator*(const matrix &a)const{
		matrix ans;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){ans.m[i][j]+=mul(m[i][k],a.m[k][j]);}
//				for(int k=0;k<2;k++){ans.m[i][j]+=m[i][k]*a.m[k][j];}
//				ans.m[i][j]%=p;
			}
		}
		return ans;
	}
	matrix operator^(int b){
		matrix ans,a=*this;
		ans.set2();
		while(b){if(b&1)ans=ans*a;a=a*a;b>>=1;}
		return ans;
	}
}f;

signed main(){
	read(T);
	while(T--){
		read(n);read(a);read(b);read(p);
		a%=p;b%=p;
		f.set1();f=f^(n+1);
		printf("%lld\n",f.m[1][0]%p); 
	}
	return 0;
}
```


---

## 作者：sjr3065335594 (赞：0)

## 题意简述

求出 $\left(\sum\limits_{i=0}^na^ib^{n-i}\right)\bmod p$ 的值。

## 思路

由于 $\sum\limits_{i=0}^na^ib^{n-i}=a\left(\sum\limits_{i=0}^{n-1}a^ib^{n-i}\right)+a^0b^{n}$，这样看着很复杂，我们可以令 $f(n)=\sum\limits_{i=0}^na^ib^{n-i}$。

这样的话 $f(n)=a\left(\sum\limits_{i=0}^{n-1}a^ib^{n-i}\right)+a^0b^{n}=af(n-1)+b^n$，也就是 $f(n+1)=af(n)+b^{n+1}$。

我们考虑矩阵快速幂，在快速幂的时候我们要维护 $f(n)$ 和 $b^n$ 的值。

初始矩阵应该是 $\begin{bmatrix}f(0)&b\end{bmatrix}$。

转移矩阵是 $\begin{bmatrix}a&0\\1&b\end{bmatrix}$。

直接矩阵快速幂就可以了，但是注意需要卡常，比如不要使用 `__int128`，取模最好用加减，快读快写都用上，还有一个非常重要的，由于转移矩阵右上角是 $0$ 所以矩阵乘法中右上角可以跳过不算。

## 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+5;
const int M=1e6+5;
ll n,a,b,mod,t;
template<typename T>
inline void read(T &x) {//快读
	x=0;
	int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
	x*=f;
} 
ll mul(ll a,ll b) {//这是一个非常神奇的两个long long进行乘法并取模的函数
    ll rt=a*b-((ll)((long double)a/mod*b+0.5))* mod;
    return rt<0?rt+mod:rt;
}

template<typename T>
inline void write(T x) {//快写
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}

inline ll Mod(ll x){//取模
	return x>=mod?x-mod:x;
}

struct Matrix {
	ll a[3][3];
	Matrix() {
		memset(a,0,sizeof(a));
	}
	Matrix operator * (const Matrix &rhs) const {//矩阵乘法拆开写减少常数
		Matrix c;
		c.a[1][1]=Mod(c.a[1][1]+mul(a[1][1],rhs.a[1][1]));
		c.a[1][1]=Mod(c.a[1][1]+mul(a[1][2],rhs.a[2][1]));
		c.a[2][1]=Mod(c.a[2][1]+mul(a[2][1],rhs.a[1][1]));
		c.a[2][1]=Mod(c.a[2][1]+mul(a[2][2],rhs.a[2][1]));
		c.a[2][2]=Mod(c.a[2][2]+mul(a[2][1],rhs.a[1][2]));
		c.a[2][2]=Mod(c.a[2][2]+mul(a[2][2],rhs.a[2][2]));
		return c;
	}
}zy,cs,dw;
Matrix Matrixpow(Matrix a,ll b) {
	Matrix res=dw;
	while(b) {
		if(b&1)res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}

int main() {
	read(t);
	while(t--) {
		read(n),read(a),read(b),read(mod);
		cs.a[1][1]=1,cs.a[1][2]=b%mod;//初始矩阵
		zy.a[1][1]=a%mod,zy.a[1][2]=0,zy.a[2][1]=1,zy.a[2][2]=b%mod;//转移矩阵
		dw.a[1][1]=dw.a[2][2]=1;//单位矩阵
		Matrix res=cs*Matrixpow(zy,n);//矩阵快速幂
		write(res.a[1][1]);//直接输出
		puts(""); 
	}
	return 0;
}


```


---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

计算 $(\sum\limits_{i=0}^na^ib^{n-i})\bmod p$ 的值。

## 解题思路

式子题。

我们定义 $f_i = \sum\limits_{j=0}^ia^jb^{i-j}$，然后我们尝试推出一个递推式。

$$
\begin{aligned}
f_{i+1} &= \sum\limits_{j=0}^{i+1}a^jb^{i+1-j} \\
&= \sum\limits_{j=0}^{i}a^jb^{i+1-j} + a^{i+1}b^{0} \\
&= b\sum_{j=0}^{i} a^jb^{i-j} + a^{i+1} \\
&= bf_i+a^{i+1}
\end{aligned}
$$

而这个递推式我们可以使用矩阵乘法进行加速。

具体地说，定义我们的状态矩阵为 $\begin{bmatrix}f_i \\ a^{i}\end{bmatrix}$，那么应该转移成 $\begin{bmatrix}bf_i+a^{i+1} \\ a^{i+1}\end{bmatrix}$，中间乘的矩阵为 $\begin{bmatrix}b & a \\ 0 & a\end{bmatrix}$。

答案就应该是 $(\begin{bmatrix}b & a \\ 0 & a\end{bmatrix})^n\begin{bmatrix}1 \\ 1\end{bmatrix}$（注意顺序哦）。

因为这道题的特殊性（略卡常），我就给出完整代码供参考。

```cpp
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef unsigned long long i64;
typedef __int128 i128;

inline i64 read()
{
    char c = getchar();
    i64 x = 0;
    for (; !isdigit(c); c = getchar())
        ;
    for (; isdigit(c); c = getchar())
        x = (x * 10) + (c - '0');
    return x;
}

inline void print(i64 x)
{
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

struct matrix
{
    i64 c[4];
    matrix()
    {
        c[0] = c[1] = c[2] = c[3] = 0;
    }
};

i64 mod = -1, T, n, a, b, c, d;

#define pos00 .c[0]
#define pos01 .c[1]
#define pos10 .c[2]
#define pos11 .c[3]

inline matrix mutl(matrix a, matrix b)
{
    matrix res;
    res pos00 = (i128(a pos00) * b pos00 + i128(a pos01) * b pos10) % mod;
    res pos01 = (i128(a pos00) * b pos01 + i128(a pos01) * b pos11) % mod;
    res pos10 = (i128(a pos10) * b pos00 + i128(a pos11) * b pos10) % mod;
    res pos11 = (i128(a pos10) * b pos01 + i128(a pos11) * b pos11) % mod;
    return res;
}
matrix bm2, intl, A;

matrix fastpow(matrix num, i64 p)
{
    matrix res = bm2;
    while (p)
    {
        if (p & 1)
            res = mutl(res, num);
        num = mutl(num, num);
        p >>= 1;
    }
    return res;
}

int main()
{
    intl pos00 = 1;
    intl pos10 = 1;
    bm2 pos00 = 1;
    bm2 pos11 = 1;

    T = read();

    while (T--)
    {
        n = read();
        a = read();
        b = read();
        mod = read();

        A pos00 = b;
        A pos01 = a;
        A pos10 = 0;
        A pos11 = a;

        A = mutl(fastpow(A, n), intl);

        print(A pos00);
        putchar('\n');
    }
}
```

---

## 作者：strlen_s_ (赞：0)

## 分析

看数据范围，我们知道这肯定需要一个单次操作复杂度为  $O(logn)$  的算法。

设 $f_i= a^0 \cdot b^i+a^1\cdot b^{i-1}+a^2\cdot b^{i-2}\cdots+a^i\cdot b^0$。

则 $f_{i+1}=a^0\cdot b^{i+1}+a^1\cdot b^{i}+a^2\cdot b^{i-1}+\cdots+a^{i+1}\cdot b^0$。

整理一下得: $f_{i+1}=b \cdot (a^0\cdot b^i+a^1\cdot b^{i-1}+a^2\cdot b^{i-2}\cdots+a^n\cdot b^0)+a^{i+1}$。

所以得到递推式 $f_i=b\cdot f_{i-1}+a^i$。

递推式出来了，就可以开始矩阵快速幂了。

设 $f_i$ 为所求答案， $g_i$ 为 $2^i$。

所以 $f_0=1$,$g_0=1$。

则因该设计一个矩阵满足：

$\begin{bmatrix}f_i&g_i\end{bmatrix} \times \begin{bmatrix}x&y\\z&w\end{bmatrix}=\begin{bmatrix}b \times f_i+a\times g_i&a \times g_i\end{bmatrix}$。

用手推一推，可得:

$\begin{bmatrix}x&y\\z&w\end{bmatrix}=\begin{bmatrix}b&0\\a&a\end{bmatrix}$。

所以用

$\begin{bmatrix}b&0\\a&a\end{bmatrix}$

进行矩阵快速幂即可。

细节：

1.要开 int128。

2.卡常，要把矩阵乘法的循环展开来写。

### code

```
#include<bits/stdc++.h>
#define in inline
#define re register
#define int __int128
using namespace std;
in int read(){
	int x=0,f=1;
	char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
in void print(re int x){
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
const int N=5;
struct jz{
	int a[N][N];
};
int n,a,b,p,T;
in jz mul(re jz x,re jz y){
	jz c;
	c.a[1][1]=x.a[1][1]*y.a[1][1]+x.a[1][2]*y.a[2][1];		//展开的矩阵乘法。 
	c.a[1][1]=c.a[1][1]>=p?c.a[1][1]%p:c.a[1][1];
	c.a[1][2]=x.a[1][1]*y.a[1][2]+x.a[1][2]*y.a[2][2];
	c.a[1][2]=c.a[1][2]>=p?c.a[1][2]%p:c.a[1][2];
	c.a[2][1]=x.a[2][1]*y.a[1][1]+x.a[2][2]*y.a[2][1];
	c.a[2][1]=c.a[2][1]>=p?c.a[2][1]%p:c.a[2][1];
	c.a[2][2]=x.a[2][1]*y.a[1][2]+x.a[2][2]*y.a[2][2];
	c.a[2][2]=c.a[2][2]>=p?c.a[2][2]%p:c.a[2][2];
	return c;
}
in jz ksm(re jz x,re int b){
	re jz res;
	res.a[1][1]=res.a[2][2]=1;
	res.a[1][2]=res.a[2][1]=0;
	while(b){
		if(b&1)res=mul(res,x);
		x=mul(x,x),b>>=1;
	}
	return res;
}
signed main(){
	T=read();
	while(T--){
		n=read(),a=read(),b=read(),p=read();
		re jz base;
		base.a[1][1]=b,base.a[2][1]=base.a[2][2]=a,base.a[1][2]=0;	//要进行快速幂的矩阵。 
		base=ksm(base,n);
		re jz ans;
		ans.a[1][1]=ans.a[1][2]=1;
		ans.a[2][1]=ans.a[2][2]=0;
		ans=mul(ans,base);
		print(ans.a[1][1]),putchar('\n');
	}
	return 0;
}

```

---

## 作者：Link_Cut_Y (赞：0)

### 前言

首先感谢所有帮助我卡常的大佬们。

### 题意

求 $(\sum_{i = 0}^{n} a^i b^{n - i})\mod p$ 的值（$n \leq 10^{18}$，$p$ 不一定为质数）。

### 分析

看到数据范围，首先想到快速幂 $+$ 乘法逆元或者矩阵乘法。

但是看到 $p$ 不为质数，那就只有可能是矩阵乘法了。

设 $S_n = \sum_{i = 0}^{n} a^i b^{n - i}$，

则有 $S_{n + 1} = \sum_{i = 0}^{n} a^ib^{n + 1 - i} + a^{n + 1}b^0 = b \sum_{i = 0}^{n} a^ib^{n - i} + a^{n + 1} = S_{n} \times b + a^{n + 1}$。


有了递推式，我们就可以设出矩阵。

设向量 $\begin{bmatrix}
 S_n & a^n
\end{bmatrix}$，则有如下等式：

$$\begin{bmatrix} S_n & a^n \end{bmatrix}
   \times 
    \begin{bmatrix} b & 0 \\ a & a \end{bmatrix}
    = \begin{bmatrix} S_{n + 1} & a^{n + 1} \end{bmatrix}$$

矩阵乘法不会的点这里[矩阵乘法](http://matrixmultiplication.xyz/)。


剩下的就交给矩阵快速幂了。

几个注意事项：

1. 两个 `long long` 相乘会爆，要用 `__int128`。
2. 矩阵乘法要展开循环。否则会超时。
3. 一定要快读快写！！

### 代码示例

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

#define LL long long
#define PII pair<int, int>
#define PLL pair<LL, LL>
#define Int __int128

LL T;
Int ans[2], t[2][2];

namespace FastIO {
	char buf[1 << 21], *_now = buf, *_end = buf;
	#define getchar() (_now == _end && (_end = (_now = buf) + fread(buf, 1, 1 << 20, stdin), _now == _end) ? EOF : *_now ++  )
	void read() { return; }
	template <typename T, typename ...T2>
	void read(T &s, T2 &...oth) {
		s = 0; int f = 1; char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = ~f + 1;
		for (; ch >= '0' && ch <= '9'; ch = getchar()) s = (s << 1) + (s << 3) + (ch ^ 48);
		s *= f; read(oth...); return;
	}
	void write() { return; }
	template <typename T, typename ...T2>
	void write(T s, T2 ...oth) {
		if (s == 0) { putchar('0'), putchar('\n'); write(oth...); return; }
		int stk[100], top = 0;
		if (s < 0) putchar('-'), s = ~s + 1;
		while (s) stk[ ++ top] = s % 10, s /= 10;
		do putchar(stk[top -- ] + (1 << 4) + (1 << 5)); while (top);
		putchar('\n'); write(oth...); return;
	}
}
#define read FastIO::read
#define write FastIO::write
#define Inline __inline__ __attribute__((always_inline))

Inline void mul(Int ans[], Int a[], Int b[][2], LL p) 
{
    Int tmp[2] = {0};
    tmp[0] = (tmp[0] + (Int)a[0] * b[0][0]) % p;
	tmp[0] = (tmp[0] + (Int)a[1] * b[1][0]) % p;
	tmp[1] = (tmp[1] + (Int)a[0] * b[0][1]) % p;
	tmp[1] = (tmp[1] + (Int)a[1] * b[1][1]) % p;
    memcpy(ans, tmp, sizeof tmp);
}

Inline void mul(Int ans[][2], Int a[][2], Int b[][2], LL p) {
    Int tmp[2][2] = {0};
    tmp[0][0] = (tmp[0][0] + (Int)a[0][0] * b[0][0]) % p;
	tmp[0][0] = (tmp[0][0] + (Int)a[0][1] * b[1][0]) % p;
	tmp[0][1] = (tmp[0][1] + (Int)a[0][0] * b[0][1]) % p;
	tmp[0][1] = (tmp[0][1] + (Int)a[0][1] * b[1][1]) % p;
	tmp[1][0] = (tmp[1][0] + (Int)a[1][0] * b[0][0]) % p;
	tmp[1][0] = (tmp[1][0] + (Int)a[1][1] * b[1][0]) % p;
	tmp[1][1] = (tmp[1][1] + (Int)a[1][0] * b[0][1]) % p;
	tmp[1][1] = (tmp[1][1] + (Int)a[1][1] * b[1][1]) % p;
    memcpy(ans, tmp, sizeof tmp);
}

Inline void solve(LL a, LL b, LL n, LL p) {
    ans[0] = 1, ans[1] = 1;
    t[0][0] = b, t[0][1] = 0, t[1][0] = a, t[1][1] = a;
    while (n) {
        if (n & 1) mul(ans, ans, t, p);
        mul(t, t, t, p); n >>= 1;
    }
    write(ans[0]);
}

int main() {
    read(T);
    while (T--) {
        LL n, a, b, p;
        read(n, a, b, p);
        solve(a, b, n, p);
    }

    return 0;
}
```

---

