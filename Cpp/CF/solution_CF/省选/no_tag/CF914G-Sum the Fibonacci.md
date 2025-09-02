# Sum the Fibonacci

## 题目描述

You are given an array $ s $ of $ n $ non-negative integers.

A 5-tuple of integers $ (a,b,c,d,e) $ is said to be valid if it satisfies the following conditions:

- $ 1<=a,b,c,d,e<=n $
- $ (s_{a} $ | $ s_{b}) $ & $ s_{c} $ & $ (s_{d} $ ^ $ s_{e})=2^{i} $ for some integer $ i $
- $ s_{a} $ & $ s_{b}=0 $

Here, '|' is the bitwise OR, '&' is the bitwise AND and '^' is the bitwise XOR operation.

Find the sum of $ f(s_{a} $ | $ s_{b})*f(s_{c})*f(s_{d} $ ^ $ s_{e}) $ over all valid 5-tuples $ (a,b,c,d,e) $ , where $ f(i) $ is the $ i $ -th Fibonnaci number ( $ f(0)=0,f(1)=1,f(i)=f(i-1)+f(i-2) $ ).

Since answer can be is huge output it modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
32
```

## 样例 #2

### 输入

```
3
7 4 1
```

### 输出

```
3520
```

## 样例 #3

### 输入

```
10
1 3 0 7 3 7 6 5 7 5
```

### 输出

```
1235424
```

## 样例 #4

### 输入

```
10
50 9 11 44 39 40 5 39 23 7
```

### 输出

```
113860062
```

# 题解

## 作者：crashed (赞：7)

# 题目
&emsp;&emsp;[点这里](http://codeforces.com/problemset/problem/914/G)看题目。    
# 分析
&emsp;&emsp;我们先放宽条件，重新定义五元组$(a,b,c,d,e)$如下：  
&emsp;&emsp;1.$1\le a,b,c,d,e\le n$。  
&emsp;&emsp;2.$s_a\&s_b=0$。  
&emsp;&emsp;并且设$v(a,b,c,d,e)=(s_a|s_b)\&s_c\&(s_d\oplus s_e)$。（这里的$\oplus$指代异或，下同）  
&emsp;&emsp;于是乎答案可以变成：  
$$
\begin{aligned}
    &\sum_{p}\ \sum_{v(a,b,c,d,e)=2^p}\ f(s_a|s_b)\times f(s_c)\times f(s_d\oplus s_e)\\
   =&\sum_{p}\ \sum_{i\& j\& k=2^p} f(i)\times \left(\sum_{s_a|s_b=i,s_a\& s_b=0}1\right)\times f(j)\times \left(\sum_{s_c=j}1\right)\times f(k)\times \left(\sum_{s_d\oplus s_e=k}1\right)
\end{aligned}
$$   
&emsp;&emsp;中间一层求和实际上是与卷积，内部的第一个求和是一个子集卷积，内部第三个求和是一个异或卷积。与卷积可以 FWT （或者叫 FMT ）， 子集卷积可以 FST ，异或卷积可以 FWT 。总的时间复杂度为$O(n\log_2^2n)$（ FST 最花时间 ）。  
&emsp;&emsp; FST 实际上是 ~~魔改~~ FWT 的思想，只不过为了避免分出来的子集还有交，就加了一位表示集合的大小（子集卷积满足$A,B\subseteq S, A\cup B=S, A\cap B=\varnothing$，$A\cap B=\varnothing$的限制等价于$|A|+|B|=|S|$）。  
# 代码
```cpp
#include <cstdio>

typedef long long LL;

const int mod = 1e9 + 7, inv2 = 5e8 + 4;
const int MAXN = 1e6 + 5, MAXL = ( 1 << 17 ) + 5, MAXLOG = 20;

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

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

int f[MAXLOG][MAXL], h[MAXL];
int A[MAXL], B[MAXL], C[MAXL], fibo[MAXL];
int cnt[MAXL];
int N, len, lg2;

int lowbit( const int x ) { return x & ( -x ); }
int fix( const int a ) { return ( a % mod + mod ) % mod; }
int count( int x ) { int ret = 0; while( x ) ret ++, x -= lowbit( x ); return ret; }

namespace OR
{
	void FWT( int *F, const int mode )
	{
		for( int s = 2 ; s <= len ; s <<= 1 )
			for( int i = 0, t = s >> 1 ; i < len ; i += s )
				for( int j = i ; j < i + t ; j ++ )
					F[j + t] = fix( F[j + t] + mode * F[j] );
	}
}

namespace AND
{
	void FWT( int *F, const int mode )
	{
		for( int s = 2 ; s <= len ; s <<= 1 )
			for( int i = 0, t = s >> 1 ; i < len ; i += s )
				for( int j = i ; j < i + t ; j ++ )
					F[j] = fix( F[j] + mode * F[j + t] );
	}
}

namespace XOR
{
	void FWT( int *F, const int mode )
	{
		int t1, t2;
		for( int s = 2 ; s <= len ; s <<= 1 )
			for( int i = 0, t = s >> 1 ; i < len ; i += s )
				for( int j = i ; j < i + t ; j ++ )
				{
					t1 = F[j], t2 = F[j + t];
					if( mode > 0 ) F[j] = ( t1 + t2 ) % mod, F[j + t] = fix( t1 - t2 );
					else F[j] = 1ll * ( t1 + t2 ) * inv2 % mod, F[j + t] = 1ll * fix( t1 - t2 ) * inv2 % mod;
				}
	}
}

void FST()
{
	for( int i = 0 ; i <= lg2 ; i ++ ) OR :: FWT( f[i], 1 );
	for( int i = 0 ; i <= lg2 ; i ++ )
	{
		for( int S = 0 ; S < len ; S ++ ) h[S] = 0;
		for( int j = 0 ; j <= i ; j ++ )
			for( int S = 0 ; S < len ; S ++ )
				h[S] = ( h[S] + 1ll * f[j][S] * f[i - j][S] % mod ) % mod;
		OR :: FWT( h, -1 );
		for( int S = 0 ; S < len ; S ++ ) if( cnt[S] == i ) A[S] = ( A[S] + h[S] ) % mod;	
	}
}

void init()
{
	fibo[0] = 0, fibo[1] = 1;
	for( int i = 2 ; i < ( 1 << 17 ) ; i ++ ) fibo[i] = ( fibo[i - 1] + fibo[i - 2] ) % mod;
	for( int i = 0 ; i < ( 1 << 17 ) ; i ++ ) cnt[i] = count( i );
}

signed main()
{
	int mx = 0;
	read( N );
	init();
	for( int i = 1, v ; i <= N ; i ++ ) 
	{
		read( v ), mx = MAX( v, mx );
		f[cnt[v]][v] ++, C[v] ++, B[v] = ( B[v] + fibo[v] ) % mod;
	}
	for( lg2 = 0, len = 1 ; len <= mx ; len <<= 1, lg2 ++ );
	FST();
	XOR :: FWT( C, 1 );
	for( int i = 0 ; i < len ; i ++ ) C[i] = 1ll * C[i] * C[i] % mod;
	XOR :: FWT( C, -1 );
	for( int i = 0 ; i < len ; i ++ ) A[i] = 1ll * A[i] * fibo[i] % mod, C[i] = 1ll * C[i] * fibo[i] % mod;
	AND :: FWT( A, 1 ), AND :: FWT( B, 1 ), AND :: FWT( C, 1 );
	for( int i = 0 ; i < len ; i ++ ) A[i] = 1ll * A[i] * B[i] % mod * C[i] % mod;
	AND :: FWT( A, -1 );
	int ans = 0;
	for( int i = 1 ; i <= len ; i <<= 1 ) ( ans += A[i] ) %= mod;
	write( ans ), putchar( '\n' );
	return 0;
}
```
&emsp;&emsp;转载自我的[博客园](https://www.cnblogs.com/crashed/p/12582699.html)。  

---

## 作者：1saunoya (赞：5)

~~经典板子题？~~

令 $i = s_a\&s_b, j = s_c, k = s_d \oplus s_e$

$\sum_{p}\sum_{i\&j\&k = 2^p} f_i \times f_j \times f_k \times (\sum_{s_a|s_b = i, s_a \&s_b = 0}1) \times (\sum_{s_c = j}1)\times (\sum_{s_d \oplus s_e = k}1)$

令 $A_i = (\sum_{s_a|s_b = i, s_a \&s_b = 0}1)$。

$B_j = (\sum_{s_c = j}1)$。

$C_k = (\sum_{s_d \oplus s_e = k}1)$。

$A_i$ 可以通过子集卷积来做，复杂度 $N \log^2 N$。

$B_j$ 显然。

$C_k$ 可以直接 FWTXOR 来做，复杂度 $N \log N$。

最后 FWTAND 卷一下三个就行了。

```cpp
#include <bits/stdc++.h>
const int BL = 2 << 20;
struct streambufcin {
	std::streambuf *in;
	streambufcin() {
		std::ios::sync_with_stdio(false);
		std::cin.tie(NULL);
		in = std::cin.rdbuf();
		bg = ed = NULL;
#ifdef LOCAL
		freopen("in.in", "r", stdin);
#endif
	}
	char buf[BL], *bg, *ed, ch;
	char gc() { return bg == ed ? ed = buf + in -> sgetn(bg = buf, BL), (bg == ed ? -1 : *bg++) : *bg++; }
	template<class T>
	streambufcin &operator >> (T &x) {
		bool neg = false;
		for (ch = gc(); !isdigit(ch); ch = gc());
		if (ch == '-')
			neg = true;
		for (x = 0; isdigit(ch); ch = gc())
			x = x * 10 + ch - 48;
		if (neg)
			x = -x;
		return *this;
	}
	streambufcin &operator >> (char &c) {
		for (c = gc(); isspace(c); c = gc());
		return *this;
	}
} cin;

struct streambufcout {
	std::streambuf *out = std::cout.rdbuf();
	char buf[BL], *optr = buf;
	streambufcout() { out = std::cout.rdbuf(); }
	~streambufcout() { flush(); }
	void flush() { out -> sputn(buf, optr - buf); optr = buf; }
	void pc(char c) {
		if (optr == buf + BL)
			flush();
		*optr++ = c;
	}
	template<class T>
	streambufcout &operator << (T x) {
		static int st[233], top;
		if (x < 0) {
			x = -x;
			pc('-');
		}
		do {
			st[++top] = x % 10;
			x /= 10;
		} while (x);
		while (top)
			pc(st[top--] ^ 48);
		return *this;
	}
	streambufcout &operator << (char c) { pc(c); return *this; }
} cout;

int n;
const int N = 262144;
const int mod = 1e9 + 7;
const int inv2 = mod + 1 >> 1;
int s[N], fib[N], cnt[N];
int A[N], B[N], C[N], F[19][N], h[N], answer[N];

int add(int x, int y) {
	if (x + y >= mod)
		return x + y - mod;
	else
		return x + y;
}
int dec(int x, int y) {
	if (x - y < 0)
		return x - y + mod;
	else
		return x - y;
}

void mul(int &x, int y) { x = 1ll * x * y % mod; }
void _ad(int &x, int y) { x += y; if (x >= mod) x -= mod; }
void _de(int &x, int y) { x -= y; if (x < 0) x += mod; }

void FWTOR(int *f, int inv) {
	for (int len = 1; len < N; len <<= 1) {
		for (int i = 0; i < N; i += len << 1) {
			for (int j = 0; j < len; j++) {
				if (inv > 0)
					_ad(f[i + j + len], f[i + j]);
				else
					_de(f[i + j + len], f[i + j]);
			}
		}
	}
}

void FWTAND(int *f, int inv) {
	for (int len = 1; len < N; len <<= 1) {
		for (int i = 0; i < N; i += len << 1) {
			for (int j = 0; j < len; j++) {
				if (inv > 0)
					_ad(f[i + j], f[i + j + len]);
				else
					_de(f[i + j], f[i + j + len]);
			}
		}
	}
}

void FWTXOR(int *f, int inv) {
	for (int len = 1; len < N; len <<= 1) {
		for (int i = 0; i < N; i += len << 1) {
			for (int j = 0; j < len; j++) {
				int x = f[i + j], y = f[i + j + len];
				f[i + j] = add(x, y), f[i + j + len] = dec(x, y);
				if (inv < 0) 
					mul(f[i + j], inv2), mul(f[i + j + len], inv2);
			}
		}
	}
}

int main() {
	for (int i = 1; i < 262144; i++)
		cnt[i] = cnt[i >> 1] + (i & 1);
	fib[0] = 0; fib[1] = 1;
	for (int i = 2; i < 262144; i++)
		fib[i] = add(fib[i - 1], fib[i - 2]);
	cin >> n;
	for (int i = 1; i <= n; i++) { int x; cin >> x; A[x]++; B[x]++; C[x]++; }
	for (int i = 0; i < 262144; i++) 
		F[cnt[i]][i] = A[i], A[i] = 0;
	for (int i = 0; i < 19; i++)
		FWTOR(F[i], 1);
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 262144; j++)
			h[j] = 0;
		for (int j = 0; j <= i; j++)
			for (int k = 0; k < 262144; k++)
				_ad(h[k], 1ll * F[j][k] * F[i - j][k] % mod);
		FWTOR(h, -1);
		for (int j = 0; j < 262144; j++)
			if (cnt[j] == i)
				_ad(A[j], h[j]);
	}
	FWTXOR(C, 1);
	for (int i = 0; i < 262144; i++)
		mul(C[i], C[i]);
	FWTXOR(C, -1);
	for (int i = 0; i < 262144; i++)
		mul(A[i], fib[i]), mul(B[i], fib[i]), mul(C[i], fib[i]);
	FWTAND(A, 1), FWTAND(B, 1), FWTAND(C, 1);
	for (int i = 0; i < 262144; i++)
		answer[i] = 1ll * A[i] * B[i] % mod * C[i] % mod;
	FWTAND(answer, -1);
	int Answer = 0;
	for (int i = 1; i < 262144; i <<= 1)
		_ad(Answer, answer[i]);
	cout << Answer << '\n';
	return 0;
}
```

---

## 作者：Kelin (赞：4)

题意:翻译已经够直白了吧

考虑到$s_i$的范围很小,所以我们考虑记下$cnt[s_i]$表示$s_i$出现的个数

因为题目要求的是通过$(s_a|s_b)$&$s_c$&$(s_d$ ^$s_e)$得到的数

那么$\sum f(s_a|s_b)*f(s_c)*f(s_d$ ^$s_e)$

$=cnt[s_a|s_b]*f(s_a|s_b)$&$cnt[s_c]*f(s_c)$&$cnt[s_d$^$s_e]*f(s_d$^$s_e)$

这里的&表示与卷积

考虑$cnt[s_a|s_b]=\sum[s_a$&$s_b=0]cnt[s_a]*cnt[s_b]$

其实这就是子集卷积的另外一种表达方式

不会的看$vfk2015$的集训队论文或者右转[这里](https://kelin.blog.luogu.org/solution-p4221)

$cnt[s_d$^$s_e]$这个就是$cnt[s]$与自己的异或卷积

最后把所有的$cnt$都求出来之后再乘上相应位置的$f$

然后求一遍与卷积,把$2^i$次方项的答案加起来就好了

以上的与卷积,异或卷积(还有或卷积)都可以用$FWT$(快速沃尔什变换)求出

这个$FWT$的话我们可以很好的~~通过背代码~~理解[他](http://blog.csdn.net/zhshrs/article/details/54838466)

```
#include<bits/stdc++.h>
#define fp(i,a,b) for(register int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(register int i=a,I=b-1;i>I;--i)
#define go(i,u) for(register int i=fi[u],v=e[i].to;i;v=e[i=e[i].nx].to)
#define file(s) freopen(s".in","r",stdin),freopen(s".out","w",stdout)
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
using namespace std;
char ss[1<<17],*A=ss,*B=ss;
inline char gc(){return A==B&&(B=(A=ss)+fread(ss,1,1<<17,stdin),A==B)?-1:*A++;}
template<class T>inline void sd(T&x){
    char c;T y=1;while(c=gc(),(c<48||57<c)&&c!=-1)if(c==45)y=-1;x=c-48;
    while(c=gc(),47<c&&c<58)x=x*10+c-48;x*=y;
}
char sr[1<<21],z[20];int C=-1,Z;
inline void Ot(){fwrite(sr,1,C+1,stdout),C=-1;}
template<class T>inline void we(T x){
    if(C>1<<20)Ot();if(x<0)sr[++C]=45,x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);sr[++C]='\n';
}
const int N=19,M=1<<17|1,P=1e9+7,inv=5e8+4;
typedef int arr[M];
int n,S,ans,Mi[N];arr a[N],b[N],c,d,e,f,p[N],t,pos,cnt;
inline int add(int a,int b){return a+=b,a>=P?a-P:a;}
inline int sub(int a,int b){return a-=b,a<0?a+P:a;}
inline void fmt(int*a,int op(int,int)){
	fp(i,1,n)fp(s,1,S)if(s&Mi[i])
		a[s]=op(a[s],a[s^Mi[i]]);
}
inline void fwt(int*a,int op){
	fp(i,1,n)fp(s,1,S)
		if(s&Mi[i]){
		int o=a[s],t=Mi[i];
		if(op==1)a[s-t]=add(a[s-t],o);
		else if(op==2)a[s]=sub(a[s-t],o),a[s-t]=add(a[s-t],o);
		else a[s]=add(a[s-t],o);
	}
}
inline void ifwt(int*a,int op){
	fp(i,1,n)fp(s,1,S)if(s&Mi[i]){
		int o=a[s],t=Mi[i];
		if(op==1)a[s-t]=sub(a[s-t],o);
		else if(op==2)a[s]=1ll*sub(a[s-t],o)*inv%P,a[s-t]=1ll*add(a[s-t],o)*inv%P;
		else a[s]=sub(o,a[s-t]);
	}
}
int main(){
    #ifndef ONLINE_JUDGE
        file("s");
    #endif
	pos[1]=Mi[1]=1;fp(i,2,18)pos[Mi[i]=Mi[i-1]<<1]=i;
	sd(n);int x,y=0;fp(i,1,n)sd(x),++t[x],cmax(y,x);
	S=1;while(S<=y)S<<=1;n=pos[S--];
	fp(i,1,S)cnt[i]=cnt[i>>1]+(i&1);
	f[1]=1;fp(i,2,S)f[i]=add(f[i-1],f[i-2]);
	fp(s,0,S)a[cnt[s]][s]=b[cnt[s]][s]=d[s]=t[s],c[s]=1ll*t[s]*f[s]%P;;
	fwt(d,2);fp(s,0,S)d[s]=1ll*d[s]*d[s]%P;
	ifwt(d,2);fp(s,0,S)d[s]=1ll*d[s]*f[s]%P;
	fp(i,0,n)fmt(a[i],add),fmt(b[i],add);
	fp(i,0,n)fp(j,0,n-i)fp(s,0,S)p[i+j][s]=add(p[i+j][s],1ll*a[i][s]*b[j][s]%P);
	fp(i,0,n)fmt(p[i],sub);fp(s,0,S)e[s]=1ll*p[cnt[s]][s]*f[s]%P;
	fwt(c,1),fwt(d,1),fwt(e,1);
	fp(s,0,S)c[s]=1ll*c[s]*d[s]%P*e[s]%P;
	ifwt(c,1);fp(i,1,n)ans=add(ans,c[Mi[i]]);
	printf("%d",ans);
return Ot(),0;
}
```

---

## 作者：丛雨 (赞：3)

## Sum the Fibonacci

本题其实很适合用来做$FWT$的模板题



做法其实很好想：

$set \space\text{g(x)=}$
$\sum_{s_a\And s_b=0, s_a|s_b=x}1$

$\text{g}$可以用子集卷积解决

然后同理解出$\color{red}{\text{h(x)=}\sum_{s_d\oplus s_e}1}(By\space FWT)$

$\sum_{a,b,c,d,e}$
$[(s_a | s_b) \& s_c \& $
$(s_d \oplus s_e)$
$2^i$
$[s_a\&s_b=0]f (s_a | s_b)$
$f(s_c)  f(s_d \oplus s_e)$

$=\sum_{x,y,z}[x\&y\&z=2^i]g(x)f(x)*f(y)*h(z)f(z)$

这里直接用$\color{blue}{FWT}$即可



$\color{pink}\mathfrak{Talk\ is\ cheap,show\ you\ the\ code.}$



```cpp
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define mod 1000000007
# define inv2 500000004
void FWT_or(int *a,int s,int T){
	for(int i=1,j=2;j<=s;i<<=1,j<<=1)
		for(int x=0;x<s;x+=j)
			for(int y=0;y<i;++y)
				a[i+x+y]=(a[i+x+y]+T*a[x+y])%mod;
}
void FWT_and(int *a,int s,int T){
	for(int i=1,j=2;j<=s;i<<=1,j<<=1)
		for(int x=0;x<s;x+=j)
			for(int y=0;y<i;++y)
				a[x+y]=(a[x+y]+T*a[i+x+y])%mod;
}
void FWT_xor(int *a,int s,int T){
	for(int i=1,j=2;j<=s;i<<=1,j<<=1)
		for(int x=0;x<s;x+=j)
			for(int y=0;y<i;++y){
				a[i+x+y]=(a[x+y]-a[i+x+y])%mod;
				a[x+y]=(a[x+y]+a[x+y]-a[i+x+y])%mod;
				if(T!=1)a[i+x+y]=1ll*a[i+x+y]*T%mod,a[x+y]=1ll*a[x+y]*T%mod;
			}
}
int qkpow(int x,ll m){
	if(!m)return 1;
	ll t=qkpow(x,m>>1);
	t=t*t%mod;
	if(m&1)t=t*x%mod;
	return t;
}
const int s=1<<17;
int n,a[18][s],b[s],c[s],w[s],tn[18][s];
int main(){
	n=read;
	for(int i=1;i<s;++i)w[i]=w[i&i-1]+1;
	for(int i=1;i<=n;++i)++b[read];
	memcpy(c,b,s<<2);
	for(int i=0;i<s;++i)a[w[i]][i]=b[i];
	for(int i=0;i<=17;++i){FWT_or(a[i],s,1);
		for(int j=0;j<s;++j){
			tn[i][j]=0;
			for(int k=0;k<=i;++k)
				tn[i][j]=(tn[i][j]+1ll*a[k][j]*a[i-k][j])%mod;
		}
	}
	for(int i=0;i<=17;++i)memcpy(a[i],tn[i],s<<2);
	for(int i=0;i<=17;++i)FWT_or(a[i],s,-1);
	for(int i=0;i<s;++i)a[0][i]=a[w[i]][i];
	FWT_xor(b,s,1);
	for(int i=0;i<s;++i)b[i]=1ll*b[i]*b[i]%mod;
	FWT_xor(b,s,inv2);
	a[0][0]=b[0]=c[0]=0;ll x=0,y=1;
	for(int i=2;i<s;++i){
		y+=x;x=y-x;y%=mod;
		a[0][i]=a[0][i]*y%mod;
		b[i]=b[i]*y%mod;
		c[i]=c[i]*y%mod;
	}
	FWT_and(a[0],s,1);FWT_and(b,s,1);FWT_and(c,s,1);
	for(int i=0;i<s;++i)c[i]=1ll*c[i]*b[i]%mod*a[0][i]%mod;
	FWT_and(c,s,-1);
	int t=0;
	for(int i=0;i<17;++i)t=(t+c[1<<i])%mod;
	cout<<(t+mod)%mod;
	return 0;
}
```



---

## 作者：FLY_lai (赞：1)

## 【题意】

给定长度为 $n$ 的数组 $s$。定义五元组 $(a,b,c,d,e)$ 是**好的**当且仅当:

1. $1\le a,b,c,d,e\le n$；
2. $\exists i\in \mathbb{Z}_+$，使得 $(s_a\operatorname{or}s_b)\operatorname{and}s_c\operatorname{and}(s_d \operatorname{xor} s_e)=2^i$；
3. $s_a\operatorname{and}s_b=0$。

对于所有**好的**五元组 $(a,b,c,d,e)$，求出 $f(s_a\operatorname{or}s_b)\times f(s_c)\times f(s_d \operatorname{xor} s_e)$ 的和。对 $(10^9+7)$ 取模。

其中 $f$ 为 Fibonacci 数列，满足 $f_0=0,f_1=1,f_i=f_{i-1}+f_{i-2}$。$\mathrm{and},\mathrm{or},\mathrm{xor}$ 分别代表按位与，按位或，按位异或运算。

$1\le n \le 10^6$，$0\le s_i \lt 2^{17}$。

## 【解法】

涉及复杂位运算的求和题，考虑集合幂级数 + FMT/FWT。

因为位运算是作用在 $s$ 上的，要把 $s$ 放在指数上；因为求和是对 $fib$ 数组求和，所以 $fib$ 的贡献要放在系数上。集合幂级数的大小和指数挂钩，所以这题我们取 $M=17$ 即可。

难点显然在于处理 $2,3$ 两条限制。

考虑限制 $2$，如果形如 $s_i\operatorname{and}s_j\operatorname{and}s_k=2^i$ 是很好处理的：定义对于 $s_i$ 定义其集合幂级数 $A_i(x)=\sum_{I}a_{i,I}x^I$，其中 $a_{i,I}$ 仅在 $I=s_i$ 时取 $f(s_i)$，然后把所有集合幂级数用与卷积乘起来，取 $x^{2^i}$ 的系数之和就是答案。

沿用这个思路，我们把 $(s_a\operatorname{or}s_b),s_c,(s_d\operatorname{xor}s_e)$ 看作三个变量，$s_a,s_b$ 还额外要求 $s_a\operatorname{and}s_b=0$。

考虑设计两个序列 $p,q$，使得选择 $(s_a,s_b)$ 和 $(s_d,s_e)$ 可以等效到在 $p,q$ 上选数。

这需要解决一个新问题：给定三个序列 $p,q,s$，求和 $f(p_i)f(q_j)f(s_k)$，要求 $p_i\operatorname{and}q_j\operatorname{and}s_k=2^i$。

这其实差异不大，如此构造集合幂级数：

$$
\begin{cases}
\displaystyle P(x)=\sum_{I}p'_Ix^I\\
\displaystyle Q(x)=\sum_{I}q'_Ix^I\\
\displaystyle S(x)=\sum_{I}s'_Ix^I\\
\displaystyle p'_I=\sum_{j,p_j=I}f(p_j)\\
\displaystyle q'_I=\sum_{j,q_j=I}f(q_j)\\
\displaystyle s'_I=\sum_{j,s_j=I}f(s_j)\\
\end{cases}
$$

答案取 $P(x)Q(x)S(x)$ 里 $x^{2^i}$ 的系数和即可。乘法定义为与卷积。

现在的问题变为构造 $p,q$ 序列。

先理清构造的思路。$p,q$ 序列的选择要与 $(s_a,s_b),(s_d,s_e)$ 的选择等效。

$p$ 与 $(s_a,s_b)$，$p$ 的信息量是 $2^M$ 的，$(s_a,s_b)$ 的信息量是 $2^{2M}$ 的，我们到底是简化什么？我们发现 $(s_a\operatorname{or}s_b)$ 相同的一对 $(s_a,s_b)$ 造成的贡献都是 $f(s_a\operatorname{or}s_b)$，也就是我们可以根据 $(s_a\operatorname{or}s_b)$ 进行分类，同类的对贡献都相等。$p$ 把每一类的信息压缩到一起，实现优化。

具体一点，就是 $p_I$ 里保存所有 $(s_a\operatorname{or} s_b)=I$ 的贡献，也就是：

$$
p_I=f(I)\cdot \sum_{s_a\cup s_b=I,s_a\cap s_b=\empty}1
$$

观察后面这一坨式子。令 $cnt_S=\sum_{i=1}^{n}[s_i=S]$，那么 $p_I=f(I)\cdot \sum_{S\cup T=I,S\cap T=\empty}cnt_S\cdot cnt_T$。是子集卷积的经典形式。

对于 $q$，同理构造：

$$
q_I=f(I)\cdot \sum_{s_a\operatorname{xor}s_b=I}1=f(I)\cdot \sum_{S\oplus T=I}cnt_S\cdot cnt_T
$$

做 FWT 即可。

那么这题就做完啦！

## Code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 17, MOD = 1e9 + 7;

int n;
int fib[(1 << N) + 5];

int cnt[(1 << N) + 5] = {};
int p[(1 << N) + 5], q[(1 << N) + 5];

int tmp[(1 << N) + 5];
int dp[N + 1][(1 << N) + 5];
void DMT(int *arr, int *to) {
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < (1 << N); i++)
        dp[0][i] = arr[i];
    for (int i = 1; i <= N; i++)
        for (int S = 0; S < (1 << N); S++)
            if (!((S >> (i - 1)) & 1))
                dp[i][S] = dp[i - 1][S];
            else
                dp[i][S] = (dp[i - 1][S] + dp[i - 1][S - (1 << (i - 1))]) % MOD;
    for (int i = 0; i < (1 << N); i++)
        to[i] = dp[N][i];
}
void iDMT(int *arr, int *to) {
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < (1 << N); i++)
        dp[0][i] = arr[i];
    for (int i = 1; i <= N; i++)
        for (int S = 0; S < (1 << N); S++)
            if (!((S >> (i - 1)) & 1))
                dp[i][S] = dp[i - 1][S];
            else
                dp[i][S] = (dp[i - 1][S] - dp[i - 1][S - (1 << (i - 1))] + MOD) % MOD;
    for (int i = 0; i < (1 << N); i++)
        to[i] = dp[N][i];
}

int A[N + 1][(1 << N) + 5];
int B[N + 1][(1 << N) + 5];
int C[N + 1][(1 << N) + 5];
void setT(int *a, int *b, int *to) { //子集卷积 
	for (int i = 0; i <= N; i++) {
        for (int j = 0; j < (1 << N); j++)
            tmp[j] = (__builtin_popcount(j) == i ? a[j] : 0);
        DMT(tmp, A[i]);
        for (int j = 0; j < (1 << N); j++)
            tmp[j] = (__builtin_popcount(j) == i ? b[j] : 0);
        DMT(tmp, B[i]);
    }

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j < (1 << N); j++)
            tmp[j] = 0; 
        for (int t = 0; t <= i; t++) {
            for (int j = 0; j < (1 << N); j++)
                tmp[j] = (tmp[j] + 1ll * A[t][j] * B[i - t][j] % MOD) % MOD;
        }
        iDMT(tmp, C[i]);
    }
    
    for (int i = 0; i < (1 << N); i++)
    	to[i] = C[__builtin_popcount(i)][i];
}

vector<int> DWT(int *arr, int l, int r) {
	if (l == r) {
		vector<int> ret;
		ret.push_back(arr[l]);
		return ret;
	}
	int m = (l + r) / 2;
	vector<int> lft = DWT(arr, l, m);
	vector<int> rgt = DWT(arr, m + 1, r);
	vector<int> ret;
	for (int i = l, j = 0; i <= m; i++, j++)
		ret.push_back((lft[j] + rgt[j]) % MOD);
	for (int i = m + 1, j = 0; i <= r; i++, j++)
		ret.push_back((lft[j] - rgt[j] + MOD) % MOD);
	return ret;
}
ll fpow(ll a, ll b, ll p) {
	ll mul = 1;
	while (b) {
		if (b & 1)
			mul = mul * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return mul;
}
ll mmi(ll a, ll p) {
	return fpow(a, p - 2, p);
}
void FWT(int *a, int *b, int *to) {
	vector<int> tmp;
	tmp = DWT(a, 0, (1 << N) - 1);
	for (int i = 0; i < (1 << N); i++)
		A[0][i] = tmp[i];
	tmp = DWT(b, 0, (1 << N) - 1);
	for (int i = 0; i < (1 << N); i++)
		B[0][i] = tmp[i]; 
	for (int i = 0; i < (1 << N); i++)
		C[0][i] = 1ll * A[0][i] * B[0][i] % MOD;
	tmp = DWT(C[0], 0, (1 << N) - 1);
	for (int i = 0; i < (1 << N); i++)
		C[0][i] = tmp[i];
	ll inv = mmi(fpow(2, N, MOD), MOD);
	for (int i = 0; i < (1 << N); i++)
		C[0][i] = C[0][i] * inv % MOD;
	for (int i = 0; i < (1 << N); i++)
		to[i] = C[0][i];
}

void DMTand(int *arr, int *to) {
	memset(dp, 0, sizeof dp);
	for (int i = 0; i < (1 << N); i++)
		dp[0][i] = arr[i];
	for (int i = 1; i <= N; i++) {
		for (int S = 0; S < (1 << N); S++) {
			if (((S >> (i - 1)) & 1))
				dp[i][S] = dp[i - 1][S];
			else
				dp[i][S] = (dp[i - 1][S] + dp[i - 1][S + (1 << (i - 1))]) % MOD; 
		}
	}
	for (int i = 0; i < (1 << N); i++)
		to[i] = dp[N][i];
}
void iDMTand(int *arr, int *to) {
	memset(dp, 0, sizeof dp);
	for (int i = 0; i < (1 << N); i++)
		dp[0][i] = arr[i];
	for (int i = 1; i <= N; i++) {
		for (int S = 0; S < (1 << N); S++) {
			if (((S >> (i - 1)) & 1))
				dp[i][S] = dp[i - 1][S];
			else
				dp[i][S] = (dp[i - 1][S] - dp[i - 1][S + (1 << (i - 1))] + MOD) % MOD;
		}
	}
	for (int i = 0; i < (1 << N); i++)
		to[i] = dp[N][i];
}
void FMTand(int *a, int *b, int *to) {
	DMTand(a, A[0]);
	DMTand(b, B[0]);
	for (int i = 0; i < (1 << N); i++)
		C[0][i] = 1ll * A[0][i] * B[0][i] % MOD;
	iDMTand(C[0], to);
}

int main() {
	fib[0] = 0;
	fib[1] = 1;
	for (int i = 2; i < (1 << N); i++)
		fib[i] = (1ll * fib[i - 1] + fib[i - 2]) % MOD;
	
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		cnt[x]++;
	}
	setT(cnt, cnt, p);
	
	for (int i = 0; i < (1 << N); i++)
		p[i] = 1ll * p[i] * fib[i] % MOD;
	
	FWT(cnt, cnt, q);
	
	for (int i = 0; i < (1 << N); i++)
		q[i] = 1ll * q[i] * fib[i] % MOD;
	
	for (int i = 0; i < (1 << N); i++)
		cnt[i] = 1ll * cnt[i] * fib[i] % MOD;
	
	FMTand(p, q, p);
	FMTand(p, cnt, C[0]);

	ll ans = 0;
	for (int i = 0, pw = 1; i < N; i++, pw *= 2)
		ans = (ans + C[0][pw]) % MOD;
	cout << ans << endl;
	return 0;
} 
```

---

## 作者：FyFive (赞：1)

>[也许更好的阅读体验](https://www.cnblogs.com/Fy5-FyFive/articles/17106283.html)

---
>前置芝士：[FWT](https://www.luogu.com.cn/problem/P4717)，[FMT](https://www.luogu.com.cn/problem/P4717)，[子集卷积](https://www.luogu.com.cn/problem/P6097)。

---

>题意已经说得相当清楚了，这里就不复述了。

---

#### 正片

想到这个 $\sum f(s_a|s_b)*f(s_c)*f(s_d \wedge s_e)$ 并不是很好搞，考虑转换，去掉 $\sum$。

开个桶 $\displaystyle cnt[i]=\sum_{i=0}^n [s_j=i]$，那么原式就变成了：
$$cnt[s_a|s_b]*f(s_a|s_b)*cnt[s_c]*f(s_c)*cnt[s_d \wedge s_e]*f(s_d \wedge s_e)$$

显然，剩下的就是用上前置芝士的部分了。

考虑 $cnt[s_a|s_b]$ 部分的卷积，在卷这一部分的时候还有一个限制是 $s_a\&s_b=0$，这样就不能直接上 FMT 了，需要跑子集卷积，~~自己卷自己~~。复杂度 $O(n\log^2 n)$。

具体的卷法可以看代码，也可以去看模板题，反正这道题里的子集卷积还是挺板的。

再考虑 $cnt[s_c]$，没得卷。复杂度 $O(n)$。

再考虑 $cnt[s_d \wedge s_e]$ 部分的卷积，很显然直接跑 FWT 就行了，~~脑子都不用的~~。复杂度 $O(n\log n)$。

卷完之后每个位置乘上相应的斐波那契数就行了。

最后把这些东西卷到一起去。题目中的限制是 &，那么最后跑一遍 FMT 把三个部分卷在一起。

由于还要求了是 $2^i$ 的项，那么输出所有 $2^i$ 项的和就好了。

总复杂度是 $O(n\log^2 n)$ 级别的。

#### 写在最后但是在代码前

FWT 和 FMT 可以直接作为函数封装起来不去管他。其实子集卷积也可，就是我有点懒 qwq。

如果你认为自己的代码应该八九不离十了，但就是死活过不去，请检查以下三点：

- 输入、输出有没有错；
- 执行卷积的数组打没打错；
- 写好的预处理（等）函数加没加进主函数。

如果查不出来，那就重构吧。不过对于封装好的函数，尽量相信自己。

#### Code
放一份方便调试的代码。 owo
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mo 1000000007ll
#define m2 (mo+1)/2
#define sc(i) scanf("%lld",&i);

inline void fmta(int *a,int n,int x) {for(int s=2,t=1;s<=n;s<<=1,t<<=1) for(int i=0;i<n;i+=s) for(int j=0;j<t;++j) a[i+j]=(a[i+j+t]*x+a[i+j]+mo)%mo;}
inline void fmto(int *a,int n,int x) {for(int s=2,t=1;s<=n;s<<=1,t<<=1) for(int i=0;i<n;i+=s) for(int j=0;j<t;++j) a[i+j+t]=(a[i+j+t]+a[i+j]*x+mo)%mo;}
inline void fwt(int *a,int n,int x) {for(int s=2,t=1;s<=n;s<<=1,t<<=1) for(int i=0;i<n;i+=s) for(int j=0;j<t;++j) {a[i+j]=(a[i+j+t]+a[i+j])%mo; a[i+j+t]=(a[i+j]-a[i+j+t]-a[i+j+t]+mo*2)%mo*x%mo; a[i+j]=a[i+j]*x%mo;}}
#define ctt(i) __builtin_popcount(i)

#define N 1<<18|1
int a[20][N],b[20][N],c[N],d[N],s[N];
int cnt[N],f[N],n;
inline void gf() {f[0]=0; f[1]=1; f[2]=1; for(int i=3;i<(1<<17);++i) f[i]=(f[i-1]+f[i-2])%mo;}

signed main()
{
    sc(n);
    gf();
    int mx=-1;
    for(int i=1;i<=n;++i) {int x; sc(x); ++cnt[x]; mx=max(mx,x);}

    int ctn=0,lcn=1;
    while(lcn<=mx) {ctn++; lcn<<=1;}
    

    for(int i=0;i<=mx;++i) a[ctt(i)][i]=c[i]=cnt[i];
    for(int i=0;i<=ctn;++i) fmto(a[i],lcn,1);
    for(int i=0;i<=ctn;++i) for(int j=0;j<=i;++j) for(int k=0;k<lcn;++k) b[i][k]=(b[i][k]+a[j][k]*a[i-j][k]%mo)%mo;
    for(int i=0;i<=ctn;++i) fmto(b[i],lcn,-1);
    

    for(int i=0;i<lcn;++i) d[i]=b[ctt(i)][i]*f[i]%mo;


    fwt(c,lcn,1);
    for(int i=0;i<lcn;++i) c[i]=c[i]*c[i]%mo;
    fwt(c,lcn,m2);
    for(int i=0;i<lcn;++i) c[i]=c[i]*f[i]%mo;
    
    for(int i=0;i<lcn;++i) s[i]=cnt[i]*f[i]%mo;

    
    fmta(s,lcn,1);
    fmta(d,lcn,1);
    fmta(c,lcn,1);
    for(int i=0;i<lcn;++i) s[i]=s[i]*d[i]%mo*c[i]%mo;
    fmta(s,lcn,-1);


    int ans=0;
    for(int i=1;i<=lcn;i<<=1) ans=(ans+s[i])%mo;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Corzica (赞：0)

子集卷积和 fwt 板子题。

把 $s_d ⊕ s_e$ 和 $s_c$ 先算出来。

前者用一遍异或卷积，然后两者之间再用一次和卷积。

然后再计算 $s_a ⊕s_b$。

这个就是子集卷积的板子，直接套上去就可以了。

比较平铺直叙的一题。

代码（可能略有些卡空间，只要数组别太夸张就好）：

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int mod = 1000000007, inv2 = 500000004;
int Cor[2][2]  = {{1, 0}, {1, 1}},
Cand[2][2] = {{1, 1}, {0, 1}},
Cxor[2][2] = {{1, 1}, {1, mod - 1}},
ICor[2][2] = {{1, 0}, {mod - 1, 1}},
ICand[2][2] = {{1, mod - 1}, {0, 1}},
ICxor[2][2] = {{inv2, inv2}, {inv2, mod - inv2}};
inline void fwt(int *f, const int c[2][2], int n) {
	int op;
	for (int len = 1; len < n; len <<= 1) {
		for (int p = 0; p < n; p += ( len << 1)) {
			for (int i = p; i < p + len; i++) {
				op = f[i];
				f[i] = (1ll * c[0][0] * f[i] + 1ll * c[0][1] * f[i + len]) % mod;
				f[i + len] = (1ll * c[1][0] * op + 1ll * c[1][1] * f[i + len]) % mod;
			}
		}
	}
}
inline void bitmul(int *f, int *g, const int c[2][2], const int ic[2][2], int n) {
	fwt(f, c, n);
	fwt(g, c, n);
	for (int i = 0; i < n; i++) {
		f[i] = 1ll * f[i] * g[i] % mod;
	}
	fwt(f, ic, n);
}
inline void print(int *f, int n) {
	for (int i = 0; i < n; i++) {
		cout << f[i] << ' ';
	}
	cout << "\n";
}
inline void cpy(int *f, int *g, int n) {
	memcpy(f, g, sizeof(int) * (n));
}
int n, a[1000006], b[1000006], f[131078], g[131078], fib[131078], m = (1 << 17), siz[131078], ff[18][131078], ans[18][131078], cnt;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i < (1 << 17); i++) {
		siz[i] = (siz[i >> 1] + (i & 1));
	}
	fib[1] = 1;
	for (int i = 2; i <= m; i++) {
		fib[i] = (1ll * fib[i - 1] + fib[i - 2]) % mod;
	}
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		f[a[i]]++;
		g[a[i]] = (1ll * g[a[i]] + fib[a[i]]) % mod;
		ff[siz[a[i]]][a[i]]++;
	}
	fwt(f, Cxor, m);
	for (int i = 0; i < m; i++) {
		f[i] = 1ll * f[i] * f[i] % mod;
	}
	fwt(f, ICxor, m);
	for (int i = 0; i < m; i++) {
		f[i] = 1ll * f[i] * fib[i] % mod;
	}
	bitmul(f, g, Cand, ICand, m);
	for (int i = 0; i <= 17; i++) {
		fwt(ff[i], Cor, m);
	}
	for (int i = 0; i <= 17; i++) {
		for (int j = 0; j <= 17 - i; j++) {
			for (int k = 0; k < (1 << 17); k++) {
				ans[i + j][k] += 1ll * ff[i][k] * ff[j][k] % mod;
				ans[i + j][k] %= mod;
			}
		}
	}
	for (int i = 0; i <= 17; i++) {
		fwt(ans[i], ICor, m);
	}
	memset(g, 0, sizeof(g));
	for (int i = 0; i < m; i++) {
		g[i] = 1ll * ans[siz[i]][i] * fib[i] % mod;
	}
	bitmul(f, g, Cand, ICand, m);
	for (int i = 0; i < m; i++) {
		if (siz[i] == 1) {
			cnt = (1ll * cnt + f[i]) % mod;
		}
	}
	cout << cnt;
}
```

---

## 作者：daniEl_lElE (赞：0)

Bitwise 卷积模板合集。可能需要的前置知识：P4717，P6097。

预处理 $fib_i$。

* 通过子集卷积计算出 $f(x)$ 表示 $s_a\operatorname{or}s_b=x,s_a\operatorname{and}s_b=0$ 的 $(a,b)$ 个数。
* 直接记录 $g(x)$ 表示 $s_c=x$ 的 $c$ 个数。
* 通过 $\operatorname{XOR}$ 卷积计算出 $h(x)$ 表示 $s_d\operatorname{xor}s_e=x$ 的 $(d,e)$ 个数。
* 将 $f(x),g(x),h(x)$ 分别乘上 $fib_x$。
* 通过 $\operatorname{AND}$ 卷积计算出 $p(x)$ 表示符合题目要求且 $\operatorname{and}$ 为 $x$ 的 $(a,b,c,d,e)$ 的答案。最后对于 $2^i$ 累加即可。

总复杂度 $O(n+2^VV^2)$，其中本题中 $V=17$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(i) (i&(-i))
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int fib[150005];
int f[150005],g[150005][20],h[150005],p[150005]; 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	fib[1]=1;
	for(int i=2;i<=150000;i++) fib[i]=(fib[i-1]+fib[i-2])%mod;
	int n; cin>>n;
	while(n--){
		int a; cin>>a; f[a]++;
	}
	for(int i=0;i<(1<<17);i++) g[i][__builtin_popcount(i)]=f[i];
	for(int k=0;k<=17;k++) for(int j=0;j<17;j++) for(int i=0;i<(1<<17);i++) if((i>>j)&1) g[i][k]+=g[i^(1<<j)][k];
	for(int i=0;i<(1<<17);i++){
		int tmp[18]; memset(tmp,0,sizeof(tmp));
		for(int j=0;j<=17;j++){
			for(int k=0;j+k<=17;k++){
				(tmp[j+k]+=g[i][j]*g[i][k])%=mod;
			}
		}
		for(int j=0;j<=17;j++) g[i][j]=tmp[j];
	}
	for(int k=0;k<=17;k++) for(int j=0;j<17;j++) for(int i=0;i<(1<<17);i++) if((i>>j)&1) (g[i][k]+=mod-g[i^(1<<j)][k])%=mod;
	for(int i=0;i<(1<<17);i++) h[i]=f[i];
	for(int j=0;j<17;j++) for(int i=0;i<(1<<17);i++) if((i>>j)&1){
		int x=h[i^(1<<j)],y=h[i];
		h[i^(1<<j)]=x+y,h[i]=x-y;
	}
	for(int i=0;i<(1<<17);i++) h[i]=h[i]*h[i];
	for(int j=0;j<17;j++) for(int i=0;i<(1<<17);i++) if((i>>j)&1){
		int x=h[i^(1<<j)],y=h[i];
		h[i^(1<<j)]=(x+y)/2,h[i]=(x-y)/2;
	}
	for(int i=0;i<(1<<17);i++) (f[i]*=fib[i])%=mod,p[i]=g[i][__builtin_popcount(i)]*fib[i]%mod,h[i]=h[i]%mod*fib[i]%mod;
	for(int j=0;j<17;j++) for(int i=0;i<(1<<17);i++) if((i>>j)&1) (f[i^(1<<j)]+=f[i])%=mod,(p[i^(1<<j)]+=p[i])%=mod,(h[i^(1<<j)]+=h[i])%=mod;
	for(int i=0;i<(1<<17);i++) f[i]=f[i]*p[i]%mod*h[i]%mod;
	for(int j=0;j<17;j++) for(int i=0;i<(1<<17);i++) if((i>>j)&1) (f[i^(1<<j)]+=mod-f[i])%=mod;
	int ans=0;
	for(int i=0;i<(1<<17);i++) if(__builtin_popcount(i)==1) (ans+=f[i])%=mod;
	cout<<ans;
	return 0;
}
```

---

