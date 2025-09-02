# Little Pony and Elements of Harmony

## 题目描述

题意翻译：

谐律精华是六个超自然的神器，它们代表着"和谐"自身主观的意志。它们被认为是小马国最强大的力量。

谐律精华的内部，可以被看作是一个有 $n$  个节点的完全图，从 $0$  到 $n-1$  标号，$n$  是一个二的幂次，等于 $2^m$ 。

![](https://cdn.luogu.org/upload/pic/13948.png)

上图是六个谐律精华。

谐律精华中的能量在不断变化。根据古籍记载，节点 $u$  在时间 $i$  时的能量(记作 $e_i[u]$  )为：

$e_i[u]=\sum_ve_{i-1}[v]\cdot b[f(u,v)]$ 。这里 $b[]$  称作变换系数——一个有 $m+1$  个元素的数组。而 $f(u,v)$  为二进制数 $(u\;xor\;v)$  中 $1$  的个数。

给定变换系数 $b[]$  和在时间 $0$  时的初始能量分布 $e_0[]$ 。帮助暮光闪闪预测在时刻 $t$  时的能量分布。答案可能非常大，你只要输出答案除以 $p$  的余数即可。

## 样例 #1

### 输入

```
2 2 10000
4 1 2 3
0 1 0
```

### 输出

```
14
6
6
14
```

# 题解

## 作者：crashed (赞：7)

# 题目
&emsp;&emsp;[点这里](http://codeforces.com/problemset/problem/453/D)看题目。  
# 分析  
&emsp;&emsp;设$count(x)$为$x$的二进制中$1$的个数。因此$f(u,v)=count(u\oplus v)$  
&emsp;&emsp;看一看每次转移，我们发现最不友好的东西就是$f(u,v)$，因此我们得想办法把它从我们的计算中丢掉。  
&emsp;&emsp;发现对于$[0,n)$中的所有数，两两异或之后不会超过$n$。并且对于一个固定的数$x$，其$count(x)$是不会变的。因此我们考虑将$b$数组转存出来：    
$$a[i]=b[count(i)]$$  
&emsp;&emsp;因此有： 
$$e[u]=\sum_v a[u\oplus v]e[v]$$  
&emsp;&emsp;考虑改变枚举顺序：  
$$e[u]=\sum_{v} a[u\oplus v]e[v]$$
$$=\sum_{i=0}^{m}a[i]\sum_{u\oplus v=i}e[v]$$
$$=\sum_{i=0}^{m}a[i]\sum_{v\oplus i=u}e[v]$$
$$=\sum_{v\oplus i=u}a[i]e[v]$$   
&emsp;&emsp;因此每次转移都是一个异或卷积的形式，可以用 FWT 优化一发。由于需要转移$t$次，还可用快速幂。 FWT 只需要在初始和最后做，中途快速幂不需要。时间是$O(mn + n\log_2t)$。  
&emsp;&emsp;这里还有一问题。由于本题给的是任意模数，可能不存在$2$逆元。  
&emsp;&emsp;~~众所周知，~~ 异或 FWT 还有一种版本，也就是像 FFT 一样，正变换和逆变换大部分一样，但是逆变换会在最后除掉向量长度（事实上 FWT 和 FFT 有很多相似处，可以在 [K 进制 FWT](https://www.cnblogs.com/reverymoon/p/10197711.html) 中了解到）    
&emsp;&emsp;因此我们可以使用上述的 FWT 。但是这里还有问题，$p$可能也没有$n$的逆元。根据同余基本性质：
$$a\equiv b\pmod p\Leftrightarrow \frac a d\equiv \frac b d\pmod {\frac p d}(d|\gcd\{a,b,m\})$$    
&emsp;&emsp;我们把$p$扩大$n$倍之后就可以直接除得正确答案了。  
&emsp;&emsp;最后一个问题，$n\times p$是$10^{15}$的，如果直接乘法会溢出（什么？ __int128 ？）。因此我们需要用 long double 来模拟取模（龟速乘太慢了）。    
# 代码
```cpp
#include <cstdio>

typedef long long LL;
typedef long double LB;

const int MAXM = 25, MAXN = 1.5e6 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

LL E[MAXN], C[MAXN];
int B[MAXM];
LL T, mod;
int N, M;

int lowbit( const int &x ) { return x & ( -x ); }
LL fix( const LL a ) { return ( a % mod + mod ) % mod; }
int count( int x ) { int ret = 0; while( x ) ret ++, x -= lowbit( x ); return ret; }

LL mul( const LL a, const LL b ) { return fix( a * b - ( LL ) ( ( LB ) a / mod * b ) * mod ); }

void FWT( LL *f, const int mode )
{
	LL t1, t2;
	for( int s = 2 ; s <= N ; s <<= 1 )
		for( int i = 0, t = s >> 1 ; i < N ; i += s )
			for( int j = i ; j < i + t ; j ++ )
			{
				t1 = f[j], t2 = f[j + t];
				f[j] = ( t1 + t2 ) % mod, f[j + t] = fix( t1 - t2 );
			}
	if( ~ mode ) return ;
	for( int i = 0 ; i < N ; i ++ ) f[i] /= N;
}

void mul( LL *ret, LL *mult )
{
	for( int i = 0 ; i < N ; i ++ ) 
		ret[i] = mul( ret[i], mult[i] );
}

int main()
{
	read( M ), read( T ), read( mod );
	N = 1 << M, mod *= N;
	for( int i = 0 ; i < N ; i ++ ) read( E[i] );
	for( int i = 0 ; i <= M ; i ++ ) read( B[i] );
	for( int i = 0 ; i < N ; i ++ ) C[i] = B[count( i )];
	FWT( E, 1 ), FWT( C, 1 );
	while( T )
	{
		if( T & 1 ) mul( E, C );
		mul( C, C ), T >>= 1;
	}
	FWT( E, -1 );
	for( int i = 0 ; i < N ; i ++ ) write( E[i] ), puts( "" );
	return 0;
}
```
&emsp;&emsp;~~不要脸的小广告：~~ 本文转载自[我的博客](https://blog.csdn.net/crashed/article/details/105095932)，欢迎大家前来阅读！

---

## 作者：chenzhiyv (赞：1)

[CF453D](https://www.luogu.com.cn/problem/CF453D)

# 题意简述

$u$ 在时间 $i$  时的能量(记作 $e_i[u]$  )为：

$$e_i[u]=\sum_ve_{i-1}[v]\cdot b[f(u,v)]$$ 

这里 $b$ 有 $m+1$ 个元素，而 $f(u,v)$  为二进制数 $(u\;xor\;v)$  中 $1$  的个数。

给定变换系数 $b$  和在时间 $0$  时的初始能量分布 $e_0$ 。预测在时刻 $t$  时的能量分布。输出答案模 $p$  。

# 思路

改变式子形式

$$ e_i[u]=\sum_v e_{i-1}[v]\cdot b[popcount(u^v)] $$

观察到很像一个 FWT 的异或卷积形式，则设

$$ f[u^v]=b[popcount(u^v)] $$

所以

$$ e_i[u]=\sum_v e_{i-1}[v]\cdot b[popcount(u^v)] $$

$$  =\sum_v e_{i-1}[v]\cdot f[u^v] $$

$$= \sum_v e_{i-2} \cdot f[u^v] \cdot f[u^v] $$

$$= \cdots  $$

$$ =\sum_v e_0[v]\cdot f[u^v]^i $$

所以

$$ e_t[u] = \sum_v e_0[v] \cdot f[u^v]^t $$

这时，我们可以直接多项式快速幂。

但同时我们知道， FWT 后每一项变成了一个个点值，可以直接进行操作，所以我们先把 $f$ 数组 FWT 一遍，对每一项做 $k$ 次的快速幂，与 $e_0$ 相乘，在 IFWT 回去，就是答案

最后还有一个小细节，这个题是任意模数，不一定有我们 FWT 需要的逆元，所以我们改变一下写法，将模数扩大 $n$ 倍，再在 IFWT 中除回来，就可以了，详细证明其他题解有。~~太菜了不会证~~

同时，这道题会爆，可以手动模拟或 __int128 。

代码：
```cpp
#include<bits/stdc++.h>
#define int __int128
using namespace std;
namespace fast_IO {
#define IOSIZE 100000
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
const int N=(1<<20)+10;
int n,t,p;
int e[N],b[40];
int c[N];
int qpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res%p;
}
void FWT_xor(int *a,int opt)
{
	for(int mid=1;mid<n;mid<<=1)
	{
		for(int r=mid<<1,j=0;j<n;j+=r)
		{
			for(int k=0;k<mid;k++)
			{
				int x=a[j+k],y=a[mid+j+k];
				a[j+k]=(x+y)%p;
				a[mid+j+k]=((x-y)%p+p)%p;
			}
		}
	}
	if(!opt)
	{
		for(int i=0;i<n;i++)
			a[i]=a[i]/n;
	}
}
signed main()
{
	cin>>n>>t>>p;
	p=p*(1<<n);
	for(int i=0;i<(1<<n);i++)
		cin>>e[i],e[i]=e[i]%p;
	for(int i=0;i<=n;i++)
		cin>>b[i],b[i]=b[i]%p;
	n=1<<n;
	for(int i=0;i<n;i++)
		c[i]=b[__builtin_popcount(i)];
	FWT_xor(c,1);
	FWT_xor(e,1);
	for(int i=0;i<n;i++)
		c[i]=qpow(c[i],t);
	for(int i=0;i<n;i++)
		c[i]=c[i]*e[i]%p;
	FWT_xor(c,0);
	for(int i=0;i<n;i++)
		cout<<(c[i]%p+p)%p<<endl;
	return 0;
}
```

---

