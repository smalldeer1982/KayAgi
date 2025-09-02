# Nikita and Order Statistics

## 题目描述

Nikita likes tasks on order statistics, for example, he can easily find the $ k $ -th number in increasing order on a segment of an array. But now Nikita wonders how many segments of an array there are such that a given number $ x $ is the $ k $ -th number in increasing order on this segment. In other words, you should find the number of segments of a given array such that there are exactly $ k $ numbers of this segment which are less than $ x $ .

Nikita wants to get answer for this question for each $ k $ from $ 0 $ to $ n $ , where $ n $ is the size of the array.

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
```

### 输出

```
6 5 4 0 0 0 ```

## 样例 #2

### 输入

```
2 6
-5 9
```

### 输出

```
1 2 0 ```

## 样例 #3

### 输入

```
6 99
-1 -1 -1 -1 -1 -1
```

### 输出

```
0 6 5 4 3 2 1 ```

# 题解

## 作者：Rainbow_qwq (赞：12)

[CF993E Nikita and Order Statistics](https://www.luogu.com.cn/problem/CF993E)

---

作为我做的第一道 FFT 的题目，想来发一个题解。

我们把序列中 $\ge x$ 的数设成 $0$ ， $<x$ 的数设成 $1$。

然后再对序列 $a$ 求前缀和，记为 $s$ 。

对于一个 $k$ ，我们只需要求出 $s[i]-s[j]=k$，$0\leq i,j\leq n$ 符合条件的 $i,j$ 共有多少个。

如果 $s[i]-s[j]=k$，那么 $s[i]=s[j]+k$ 。

记 $f[i]$ 表示前缀和 $s$ 数组中共有多少个 $i$ 。

对于一个 $k$ ，我们只需要求 $ans[k]=\sum_{i=0}^{n-k} f[i]\times f[i+k]$ 。

接下来好像是 FFT 的一个~~经典套路~~：反转数组。

设 $g[i]=f[n-i]$ ，用 FFT 做 $f$ 与 $g$ 的卷积，设为 $h[i]$。

那么 $h[n-i]=\sum_{j=0}^{n-i} f[j]\times g[n-i-j]=\sum_{j=0}^{n-i} f[j]\times f[i+j]$

再与上面的 $ans[k]$ 的柿子对比一下，是不是有点眼熟？

对， $ans[i]=h[n-i]$ 。

这样我们只需要求 $f$ 与 $g$ 的卷积 $h$ ，就解决这个问题了。

记得 $ans[0]$ 需要特判，因为不能选长度为 $0$ 的区间。

代码：
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long //开了 long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
#define maxn 2000007
const double pi=acos(-1.0);
struct cpx{
	double x,y;
	cpx operator +(const cpx&b)const{return (cpx){x+b.x,y+b.y};}
	cpx operator -(const cpx&b)const{return (cpx){x-b.x,y-b.y};}
	cpx operator *(const cpx&b)const{return (cpx){x*b.x-y*b.y,x*b.y+y*b.x};}
}a[maxn],b[maxn];
int n,m,l,lim=1,rev[maxn];
void fft(cpx *a,int typ)
{
	For(i,0,lim-1)
		if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int mid=1;mid<lim;mid<<=1)
	{
		cpx wn=(cpx){cos(pi/mid),typ*sin(pi/mid)};
		for(int r=mid<<1,j=0;j<lim;j+=r)
		{
			cpx w=(cpx){1,0};
			for(int k=0;k<mid;++k,w=w*wn){
				cpx x=a[j+k],y=w*a[j+k+mid];
				a[j+k]=x+y,a[j+k+mid]=x-y;
			}
		}
	}
}
int s[maxn],f[maxn],px;
int get0()//ans0的特判
{
	int p=0,res=0;
	For(i,1,n){
		if(s[i]!=s[i-1])p=i;
		res+=i-p;
	} return res;
}
signed main()
{
	n=read(),px=read();
	For(i,1,n){
		int x=read();
		if(x<px)s[i]=s[i-1]+1;
		else s[i]=s[i-1];
		f[s[i]]++;
	}f[0]++;
	while(lim<=n+n)lim<<=1,l++;
	For(i,0,lim-1)rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
	For(i,0,n)a[i].x=f[i],b[i].x=f[n-i];
	fft(a,1);
	fft(b,1);
	For(i,0,lim)a[i]=a[i]*b[i];
	fft(a,-1);
	cout<<get0();
	Rep(i,n-1,0)cout<<' '<<(int)(a[i].x/lim+0.5);
    return 0;
}
```

---

## 作者：Karry5307 (赞：7)

### 题意

给你一个长度为 $n$ 个序列 $a$ 和一个数 $x$，对于 $0\leq k\leq n$ 求出有多少个 $a$ 的子区间满足恰好有 $k$ 个数小于 $x$。

$\texttt{Data Range:}1\leq n\leq 2\times 10^5$

### 题解

CF 标签恶评题。同样是 CRT,FFT,math 人家 CF1054H 就有 $\texttt{*3500}$ 为啥你只有 $\texttt{*2300}$（无能狂怒）

其实是个养生题啦

先考虑一个 $O(n^2)$ 的暴力做法。

注意到我们要维护的区间信息（也即有多少个数小于 $x$）满足可减性，所以可以构造 $b_i=[a_i\lt x]$，并且设 $s$ 为 $b$ 的前缀和，然后枚举区间的左右端点统计一下贡献（也即 $[l,r]$ 给 $s_r-s_{l-1}$ 的贡献）即可。

接下来考虑这样一个性质，注意到 $b_i\in\{0,1\}$，所以 $s$ 是单调不降的。

我们改变一下枚举顺序，考虑枚举左端点 $l-1$ 和 $s_r-s_{l-1}=p$，那么我们可以很快算出 $s_r$ 的答案。

而且，由于 $s$ 单调不降，所以对于所有满足 $s_x=s_{l-1}+p$ 的 $x$ 都会给 $p$ 带来贡献。

于是我们可以考虑设 $g_i$ 表示有多少个 $x$ 满足 $s_x=i$，$f_i$ 表示 $i$ 的贡献，我们用上面的枚举方法可以得到

$$f_i=\sum\limits_{j=0}^{}g_jg_{j+i}$$

注意到这是经典套路，$\texttt{FFT}$ 即可。

但是注意到我们并不保证 $i=0$ 的时候我们枚举的左端点一定在可能的右端点的左边，于是必须要暴力计算。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
typedef long double db;
const ll MAXN=524291;
const db PI=acos(-1);
struct Complex{
	db re,im;
	Complex(db x=0,db y=0)
	{
		this->re=x,this->im=y;
	}
	inline Complex conj()
	{
		return Complex(re,-im);
	}
};
ll n,kk,cnt=1,limit=-1;
Complex f[MAXN],g[MAXN];
ll x[MAXN],rev[MAXN],prefix[MAXN],barrel[MAXN],rb[MAXN];
li res[MAXN];
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
inline Complex operator +(Complex x,Complex y)
{
	return Complex(x.re+y.re,x.im+y.im);
}
inline Complex operator -(Complex x,Complex y)
{
	return Complex(x.re-y.re,x.im-y.im);
}
inline Complex operator *(Complex x,Complex y)
{
	return Complex(x.re*y.re-x.im*y.im,x.re*y.im+x.im*y.re);
}
inline Complex operator /(Complex x,db y)
{
	return Complex(x.re/y,x.im/y);
}
inline void FFT(Complex *cp,ll cnt,ll inv)
{
	ll cur=0;
	Complex res,omg;
	for(register int i=0;i<cnt;i++)
	{
		if(i<rev[i])
		{
			swap(cp[i],cp[rev[i]]);
		}
	}
	for(register int i=2;i<=cnt;i<<=1)
	{
		cur=i>>1,res=Complex(cos(2*PI/i),inv*sin(2*PI/i));
		for(register Complex *p=cp;p!=cp+cnt;p+=i)
		{
			omg=Complex(1,0);
			for(register int j=0;j<cur;j++)
			{
				Complex t=omg*p[j+cur],t2=p[j];
				p[j+cur]=t2-t,p[j]=t+t2;
				omg=omg*res;
			}
		}
	}
	if(inv==-1)
	{
		for(register int i=0;i<cnt;i++)
		{
			cp[i]=cp[i]/cnt;
		}
	}
}
int main()
{
	n=read(),kk=read(),barrel[0]=1;
	for(register int i=1;i<=n;i++)
	{
		x[i]=read(),barrel[prefix[i]=prefix[i-1]+(x[i]<kk)]++;
	}
	for(register int i=0;i<=n;i++)
	{
		rb[i]=barrel[i];
	}
	reverse(rb,rb+n+1);
	for(register int i=0;i<=n;i++)
	{
		f[i].re=barrel[i],g[i].re=rb[i];
	}
	while(cnt<=((n+1)<<1))
	{
		cnt<<=1,limit++;
	}
	for(register int i=0;i<cnt;i++)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<limit);
	}
	FFT(f,cnt,1),FFT(g,cnt,1);
	for(register int i=0;i<cnt;i++)
	{
		f[i]=f[i]*g[i];
	}
	FFT(f,cnt,-1);
	for(register int i=0;i<=n;i++)
	{
		res[i]=(li)(f[i].re+0.5);
	}
	reverse(res,res+n+1),res[0]=0;
	for(register int i=0,p=0;i<=n;i++)
	{
        if(prefix[i]!=prefix[i-1])
        {
            p=i;
        }
		res[0]+=i-p;
	}
	for(register int i=0;i<=n;i++)
	{
		printf("%lld ",res[i]);
	}
}
```

---

## 作者：1saunoya (赞：5)

一眼题吧…

值域并不重要，直接 $pre_i = \sum [a_i < k]$。

然后就是求 $pre_i - pre_j = x$ 的个数了。

直接 fft 就行吧…感觉是不要拆系数的…

---

## 作者：EternalEpic (赞：2)

初看这道题，以为又是什么数据结构数数题，没啥思路，结果推式子时搞出了一个类似可以卷积的玩意儿，所以果断 $FFT$ 解决。

那我们来分析问题：

1. 这道题里，值域没用，每一个数只要管它与 $x$ 的相对大小关系即可。如果它小于 $x$ 那么有贡献，赋值为一，否则为零。然后，可以求前缀和，区间部分和问题往往可以用前缀和配对端点解决。

2. 令 $f_i$ 表示前缀和为 $i$ 的前缀端点数量，$m$ 为总共比 $x$ 小的数的个数。显然的，对于恰好有大于一个数比 $x$ 小的情况中，答案 $g_k = \sum\limits_{i=0}^{m-k} f_i \times f_{i+k}$。 这个式子意思就是取两个端点使区间值符合条件，然后用加乘原理统计一下。

3. 考虑常用技巧，变换顺序，令 $h_i = f_{m-i}$ ，所以 $f_{i+k} = h_{m-i-k}$ ，这样的话，$g$ 就可以写成两者加法卷积了。大功告成。

4. 不要忘了特殊处理 $g_0$ ，经过推导可知 $g_0 = \sum\limits_{i=0}^m \frac{f_i\times{(f_i + 1)}}{2}$ ，暴力算就好。

```cpp
struct Vector {
	double x, y;
	Vector(double _x = 0, double _y = 0) : x(_x), y(_y) {}

	inline Vector Vary(void) { return Vector(x, -y); }

	inline bool operator < (const Vector&rhs)
	const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
	inline Vector operator - (const Vector&rhs)
	const { return Vector(x - rhs.x, y - rhs.y); }
	inline Vector operator + (const Vector&rhs)
	const { return Vector(x + rhs.x, y + rhs.y); }

	inline Vector operator * (const double&rhs)
	const { return Vector(x * rhs, y * rhs); }
	inline Vector operator / (const double&rhs)
	const { return Vector(x / rhs, y / rhs); }

	inline Vector operator * (const Vector&rhs)
	const { return Vector(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
}; typedef Vector Complex;

const double PI = std :: acos(-1.0);
const int Maxn = 6e5 + 5;

int lim = 1, rev[Maxn];
inline void FFT(int limit, Complex *arr, int type) {
	for (int i = 0; i < limit; i++)
		if (i < rev[i]) swap(arr[i], arr[rev[i]]);
	for (int mid = 1; mid < limit; mid <<= 1) {
		Complex w0(cos(PI / mid), type * sin(PI / mid));
		for (int i = 0; i < limit; i += mid << 1) { Complex w(1, 0);
			for (int j = 0; j < mid; j++, w = w * w0) {
				Complex x = arr[i + j], y = w * arr[i + j + mid];
				arr[i + j] = x + y, arr[i + j + mid] = x - y;
			}
		}
	} if (type == -1) for (int i = 0; i < limit; i++) arr[i] = arr[i] / limit;
}

int n, m, x; Complex f[Maxn];

signed main(void) {
	read(n), read(x);
	for (int i = 1, v; i <= n; i++) {
		read(v); m += v < x ? 1 : 0; f[m].x++;
	}
	
	f[0].x++;
	while (lim <= m << 1) lim <<= 1;
	for (int i = 0; i < lim; i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
	
	ll ret = 0;
	for (int i = 0; i <= m; i++) f[m - i].y = f[i].x, ret += (ll) f[i].x * (f[i].x - 1) / 2;
	
	FFT(lim, f, 1);
	for (int i = 0; i < lim; i++) f[i] = f[i] * f[i];
	FFT(lim, f, -1);
	
	writeln(ret, ' ');
	for (int i = 1; i <= m; i++) writeln((ll) (f[m - i].y / 2.0 + 0.5), ' ');
	for (int i = m + 1; i <= n; i++) writeln(0, " \n"[i == n]);
//	fwrite(pf, 1, o1 - pf, stdout);
	return 0;
}
```



---

## 作者：huangzirui (赞：2)

如果这篇题解 $\LaTeX$ 锅了就请到 [我的洛谷博客](https://www.luogu.com.cn/blog/My-luoguBuoke-HZR/the-solution-of-CF993E) 里看吧。。捂脸

题意：

Nikita给你一个序列 $a$，问你对于每个  $\text{k}\in[1,\text{n}]$ 有多少个连续的序列满足恰好有 $\text{k}$ 个数小于指定的常数 $X$

---

首先因为常数是固定的，数字只有有贡献的和无贡献之分。

把所有大于等于 $\text{X}$ 的数改为 0 ，小于 $\text{X}$ 的数字改为 1 ，原问题就转化为问有多少个连续序列满足和为 $\text{k}$ 。

因为只询问连续序列，记前缀和 $\text{sum}_{\text{ i}}= \sum\limits^i_{j=1} a_j$，原问题转化为求：

$
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \sum\limits^n_{i=1}\sum\limits^n_{j=1}[a_i-a_j=k]
$

再设 $S_i = \sum[sum_j=i]$，$S_0=0$

原问题转换为求

$
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \sum\limits^n_{i=k+1}S_i\cdot S_{i-k}
$

复杂度 $O(n^2)$ ，但还不足通过此题。

---

上面的式子转化一下变为

$
\ \ \ \ \ \ \ \ \ \ \ \ \ \ \sum\limits_{i-j=k} S_i\cdot S_j = \sum\limits_{i+j=k} S_i\cdot S_{-j}
$

(注意下标的负数)

那么设

$A(x) = S_0+S_1x+S_2x^2+...$

$B(x) = S_0+S_1x^{-1}+S_2x^{-2}+...$

$C(x) = A(x)B(x)$

那么对于每个 $\text{k}$ 只要求 $C(x)$ 中 $x^k$ 项的系数就是答案。

然后显然是个 FTT 的板子。实际操作时还要把 $B(x)$ 的每个项乘个 $x^n$ 变成正数再做 FFT。注意 k=0 要特判。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int maxn=200010*4;
const double Pi=acos(-1.0);
struct Complex{
	double A,B;
};
int i,j,k,n,m,a[maxn],s[maxn],R[maxn];
Complex A[maxn],B[maxn];
Complex operator +(Complex A,Complex B){return Complex{A.A+B.A,A.B+B.B};}
Complex operator -(Complex A,Complex B){return Complex{A.A-B.A,A.B-B.B};}
Complex operator *(Complex A,Complex B){return Complex{A.A*B.A-A.B*B.B,A.A*B.B+A.B*B.A};}
Complex Get_w(int k,int n,bool op){
	int K=1;if(!op)K=-1;
	return Complex{cos(k*2.0*Pi/n),K*sin(k*2.0*Pi/n)};
}
void FFT(int len,Complex *A,bool op){
	for(int i=0;i<len;i++)
		if(i<R[i])swap(A[i],A[R[i]]);
	Complex Wn,w;
	for(int i=1;i<len;i*=2){
		Wn=Get_w(1,i*2,op);
		for(int j=0;j<len;j+=i*2){
			w=Complex{1,0};
			for(int k=0;k<i;k++,w=w*Wn){
				int K=k+j;
				Complex S1=A[K],S2=w*A[K+i];
				A[K]=S1+S2;
				A[K+i]=S1-S2;
			}
		}
	}
}
int main(){
	cin>>n>>m;
	A[0].A=1;
	for(i=1;i<=n;i++){
		a[i]=read();
//		cout<<a[i]<<' ';
		if(a[i]<m)a[i]=1;
		else a[i]=0;
		s[i]=s[i-1]+a[i];
		A[s[i]].A+=1;
	}
	cout<<endl;
	for(i=0;i<=n;i++)
		B[i].A=A[n-i].A;
	int len=1,L=0;
	while(len<=n*2)len*=2,++L;
	for(i=0;i<len;i++)
		R[i]=R[i/2]/2+((i%2)<<L-1);
	FFT(len,A,1);
	FFT(len,B,1);
	for(i=0;i<=len;i++)A[i]=A[i]*B[i];
	FFT(len,A,0);
	
	ll Ans0=0,Sum=0;
	a[n+1]=1;
	for(i=1;i<=n+1;i++){
		if(a[i]==0)Sum++;
		else Ans0+=Sum*(Sum+1)/2,Sum=0;
	}
	printf("%lld",Ans0);
	
	for(i=1;i<=n;i++)
		printf(" %lld",(ll)(A[i+n].A/len+0.5));
	cout<<endl;
	return 0;
}
```

---

## 作者：i207M (赞：2)

其实这道题比较模板，发这篇题解就是讨论一下大家有没有什么好的想法。

和之前的题解不一样，我是直接做的。首先把序列转化为01序列，现在要求出和为k的区间个数。

我们记$cnt[v]$表示前缀和为v的出现次数，则

$ans[k]=\sum \limits_{i<=k} cnt[i]\times cnt[i-k]$，因为前缀和单调不降，所以$cnt[i]$在原数组的位置一定大于$cnt[i-k]$的。直接反转数组，套用FFT即可。

注意$ans[0]$需要特判，因为$\sum cnt[i]^2$并没有保证左右端点一个在前一个在后。

```cpp
LL calc0()
{
    LL res=0;
    for(ri i=1,p=0; i<=n; ++i)
    {
        if(a[i]!=a[i-1]) p=i;
        res+=i-p;
    }
    return res;
}
cpx f[N],g[N];
LL ans[N];
signed main()
{
    in(n),in(lim);
    g[0].x+=1;
    for(ri i=1; i<=n; ++i)
    {
        in(a[i]),a[i]=(a[i]<lim)+a[i-1];
        g[a[i]].x+=1;
    }
    for(ri i=0; i<=n; ++i) f[i]=g[n-i];
    int m=1;
    for(; m<=(n*2); m<<=1);
    for(ri i=1,hb=m>>1; i<m; ++i) r[i]=(r[i>>1]>>1)|((i&1)?hb:0);
    dft(f,m,1), dft(g,m,1);
    for(ri i=0; i<=m; ++i) f[i]=f[i]*g[i];
    dft(f,m,-1);
    for(ri i=1; i<=n; ++i) ans[i]=(f[n-i].x+0.5);
    ans[0]=calc0();
    for(ri i=0; i<=n; ++i) out(ans[i],' ');
    return 0;
}
```

---

## 作者：litble (赞：2)


# 题外话
[戳我一下嘛QvQ](https://blog.csdn.net/litble/article/details/80963180)

# 解题思路

显然将所有小于$x$的数转化为1，其他的为0，这就是个01序列，然后求区间和是$k$的区间个数。

那么我们首先要取一个左端点，再取一个右端点。

$k$要取遍，并且是$10^5$级的数据，考虑FFT。

考虑左端点取每一个点时，在这个点左边的$1$的个数，若个数为$t$，则$x^t$的系数加1，这样构造一个多项式$A$。

右端点取每一个点时，在这个点右边的$1$的个数，构造一个类似的多项式$B$。

那么$A$和$B$做卷积，第$t$项的系数就是区间外$1$的个数为$t$的区间个数。

桥豆麻袋，有可能出现右端点取得比左端点小的情况。

发现这种情况下，算出来在区间外$1$的个数一定大于等于整个序列$1$的个数，所以受影响的只有$k=0$的情况，所以单独用组合的方法计算一下$k=0$的情况即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0,w=1;char ch=' ';
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') w=-1,ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q*w;
}
typedef long long LL;
typedef double db;
const db pi=3.1415926535897384626;
const int N=524300;
struct com{db r,i;}a[N],b[N];
int n,X,tot,len,kn;
int sum[N],rev[N];LL ans[N];
com operator* (com a,com b) {return (com){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r};}
com operator- (com a,com b) {return (com){a.r-b.r,a.i-b.i};}
com operator+ (com a,com b) {return (com){a.r+b.r,a.i+b.i};}
com operator/ (com a,db b) {return (com){a.r/b,a.i/b};}
void NTT(com *a,int n,int x) {
	for(RI i=0;i<n;++i) if(rev[i]>i) swap(a[i],a[rev[i]]);
	for(RI i=1;i<n;i<<=1) {
		com wn=(com){cos(pi/i),sin(pi/i)*x};
		for(RI j=0;j<n;j+=(i<<1)) {
			com t1,t2,w=(com){1,0};
			for(RI k=0;k<i;++k,w=w*wn)
				t1=a[j+k],t2=w*a[j+i+k],a[j+k]=t1+t2,a[j+i+k]=t1-t2;
		}
	}
	if(x==-1) for(RI i=0;i<n;++i) a[i]=a[i]/(db)n;
}
int main()
{
    n=read(),X=read();
    for(RI i=1;i<=n;++i) sum[i]=sum[i-1]+(read()<X);
    for(RI i=1;i<=n;++i) ++a[sum[i-1]].r;
    for(RI i=1;i<=n;++i) ++b[sum[n]-sum[i]].r;
    kn=1;while(kn<=sum[n]*2) kn<<=1,++len;
    for(RI i=1;i<kn;++i) rev[i]=(rev[i>>1]>>1)|((i&1)<<(len-1));
    NTT(a,kn,1),NTT(b,kn,1);
    for(RI i=0;i<kn;++i) a[i]=a[i]*b[i];
    NTT(a,kn,-1);
    int js=0;
    for(RI i=1;i<=n;++i)
    	if(sum[i]==sum[i-1]) ++js;
    	else ans[0]+=1LL*js*(js-1)/2+js,js=0;
    ans[0]+=1LL*js*(js-1)/2+js;
    for(RI i=0;i<sum[n];++i) ans[sum[n]-i]=(LL)(a[i].r+0.2);
    for(RI i=0;i<=n;++i) printf("%lld ",ans[i]);
    puts("");
    return 0;
}
```


---

## 作者：QiFeng233 (赞：1)

第一道FFT的应用题

# 思路简述

因为$x$是一个给定的常数，而我们只关心大小的相对关系及其的对数，所以我们把$<x$的数设为$1$，$\geq x$的设为$0$，求一个前缀和。因为序列非负，所以前缀大小为$i+k$的一定在前缀大小为$i$的后边，这很重要，只有保证它们的前后关系我们才能进行下一步操作。

设$f_i$是前缀和大小为$i$的前缀和的个数，那么根据乘法原理，显然有$ans_k=\sum\limits_{i=0}^{n-k}f_i \times f_{i+k}$。

接下来就是FFT题目的惯用套路：反转数组。

设$g_i=f_{n-i}$，那么有$f_{i+k}=g_{n-k-i}$，那么再设一个$h$数组，$ans_k=h_{n-k}=\sum\limits_{i=0}^{n-k}f_i \times g_{n-k-i}$，那么$h$数组显然是$f$和$g$的卷积，那这题上个FFT就做完了。

注意$k=0$时特判一下，毕竟我们不能选空区间。$k=0$时入门选手都会，不多赘述，详见代码。

# 代码时间
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using std::swap;
#define int long long
namespace QiFeng233{
	const int maxn=4e6+10;
	const double pi=acos(-1);
	struct complex{//复数类型 
		double r,i;
    	complex(double r=0,double i=0):r(r),i(i){}
		complex operator+(const complex &a)const{
        	return complex(r+a.r,i+a.i);
		}
		complex operator*(const complex &a)const{
	        return complex(r*a.r-i*a.i,r*a.i+i*a.r);
	    }
		void operator*=(const complex &a){
	        *this=complex(r*a.r-i*a.i,r*a.i+i*a.r);
	    }
	    complex operator-(const complex &a)const{
	        return complex(r-a.r,i-a.i);
	    }
	};
	complex F[maxn],G[maxn];
	int n,lim=1,L,rev[maxn],a[maxn],s[maxn],x;
	void FFT(complex *A,int n,int type){
		for(int i=0;i<n;++i){
			if(i>=rev[i])continue;
	        swap(A[i],A[rev[i]]);
	    }
	    //三重循环
	    for(int mid=1;mid<n;mid<<=1){//为了一次处理两个相邻区间，实际上我们枚举区间左端点到中点的长度
	        double d=pi/mid;//2*pi/(mid*2)简化后
	        complex root=complex(cos(d),type*sin(d));
	        int r=mid<<1;//一次搞定两个区间
	        for(int l=0;l<n;l+=r){
	            complex w=complex(1,0);
	            for(int k=0;k<mid;++k){
					complex A0=A[l+k];//相当于递归版A0那一行
	                complex A1=w*A[l+k+mid];//相当于递归版A1那一行
	                A[l+k]=A0+A1;
	                A[l+k+mid]=A0-A1;
	                w*=root;
	            }
			}
	    }
	    if(type==1)return;
	    //别忘了逆变换要除n
	    for(int i=0;i<n;++i)A[i].r/=(1.0*n);
	}
	int read(){
		int res=0,c=getchar(),f=c=='-'?-1:1;
		while(c<'0'||c>'9')c=getchar(),f=c=='-'?-1:f;
		while(c>='0'&&c<='9')res=res*10+c-'0',c=getchar();
		return res*f;
	}
	void solve(){
		n=read(),x=read();
		for(int i=1;i<=n;++i)a[i]=read()<x?1:0,s[i]=s[i-1]+a[i];
		for(int i=0;i<=n;++i)F[s[i]].r+=1.0;
		for(int i=0;i<=n;++i)G[i].r=F[n-i].r;
		while(lim<=2*n)lim<<=1,++L;
		--L;
		for(int i=0;i<=lim;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<L);
		FFT(F,lim,1);
		FFT(G,lim,1);
		for(int i=0;i<=lim;++i)F[i]*=G[i]; 
		FFT(F,lim,-1);
		int ans0=0,head=1,tail=1;
		a[n+1]=-1;
		while(head<=n&&tail<=n){
			while(a[head]==1)++head,++tail;
			while(a[tail]==0)++tail;
			ans0+=(tail-head)*(tail-head+1)/2;
			head=tail;
		}
		printf("%lld ",ans0);
		for(int i=n-1;i>=0;--i){
			printf("%lld ",(int)round(F[i].r));
		}
	}
}
signed main(){
	QiFeng233::solve();
	return 0;
}
```

# 反思总结
- 这题不能用NTT的原因是值域达到了 $4 \times 10^{10}$，那么模数起码比这个要大，这样的话乘法过程中要么爆long long，要么快速乘很慢。

- FFT的题目的一个经典套路就是反转数组

---

## 作者：guoshaoyang (赞：1)

题意很简单，就是给出一个大小为$n$的数组$a$和一个数$x$，对于$0$和$n$ 之间的所有$k$，求有多少个$a$的区间中恰有$k$个数小于$x$

至于解法，其他大佬们已经讲得很清楚了。我发现大佬们用的都是FFT，此处我给出NTT的程序并解释为什么用NTT不好。

注意本题的答案可能很大，所以要用较大的模数，至少要$N^2$，于是在乘法过程中就会爆`long long`，于是要用快速乘，但这样一来，程序的效率就大大降低了，不加常数优化很容易TLE

TLE代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=1e9+7,MAXN=1e6+10;
const LL BASE=3,MOD=75161927681,INV=25053975894;
inline LL mult(LL a,LL b){
	LL ret=0;
	while(b>0){
		if(b&1)
			ret=(ret+a)%MOD;
		a=(a+a)%MOD;
		b>>=1;
	}
	return ret;
}
inline LL fpm(LL base,LL p){
	LL ret=1;
	while(p){
		if(p&1)
			ret=mult(ret,base)%MOD;
		base=mult(base,base)%MOD;
		p>>=1;
	}
	return ret%MOD;
}
int N,X,limit=1,lg,rev[MAXN];
inline void NTT(LL *a,int type){
	for(int i=0;i<limit;i++)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
	for(int mid=1;mid<limit;mid<<=1){
		int len=mid<<1/*n*/;
		LL Wn=fpm(type==1?BASE:INV/*BASE^type*/,(MOD-1)/len);
		for(int j=0;j<limit;j+=len){
			LL w=1;
			for(int k=0;k<mid;k++){
				LL x=a[j+k],y=mult(w,a[j+k+mid]);
				a[j+k]=(x+y)%MOD;
				a[j+k+mid]=(x-y+MOD)%MOD;
				w=mult(w,Wn);
			}
		}
	}
}
LL s[MAXN],f[MAXN],g[MAXN],ans[MAXN];
char ch;
int main(){
	scanf("%d%d",&N,&X);
	for(int i=1;i<=N;i++){
		scanf("%lld",s+i);
		s[i]=(s[i]<X)+s[i-1];
	}
	for(int i=0;i<N;i++){
		f[s[i]]++;
		g[s[N]-s[i+1]]++;
	}
	while(limit<=(N<<1)){
		limit<<=1;
		lg++;
	}
	for(int i=0;i<limit;i++)
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	NTT(f,1);
	NTT(g,1);
	for(int i=0;i<limit;i++)
		f[i]=mult(f[i],g[i]);
	NTT(f,-1);
	LL cnt=0;
	for(int i=1;i<=N;i++)
		if(s[i]==s[i-1])
			cnt++;
		else{
			ans[0]+=cnt*(cnt-1)/2+cnt;
			cnt=0;
		}
	ans[0]+=cnt*(cnt-1)/2+cnt;
	LL limit_inv=fpm(limit,MOD-2);
	for(int i=0;i<s[N];i++)
		ans[s[N]-i]=mult(f[i],limit_inv);
	for(int i=0;i<=N;i++)
		printf("%lld ",ans[i]);
	return 0;
}
```

---

## 作者：AnOldSaltedFish (赞：0)

题解
===
FFT水题。。。

这道题的关键在于意识到 $x$ 是给定不变的，而数组 $\{a_n\}$ 同时也是给定不变的。这样这题便与数组里的各个数分别是什么或者 $x$ 是多少毫无关系了。

我们现在已经知道了数组里符合“比 $x$ 小”要求的数的具体位置，每个符合要求的数将这个数列划分成了数个区域，我们先考虑暴力，对于一个 $k$，我们可以考虑枚举包含在区间里的 $k$ 个比 $x$ 小的数分别是哪几个，那么这些数一定是连续的。也就是说我们可以考虑相隔 $k-1$ 个区域的两个区域，在这两个区域中分别选取区间左端点和右端点就可以保证选出来的区域中一定包含 $k$ 个符合要求的数，而这样一次操作的贡献的方案数就是两个区域大小的乘积。

可以先存一个数组表示被符合要求的数划开的区间的大小，设为 $s$，再假设划出了 $m$ 个区域，然后对于一个 $k$ 我们要求的就是 $\sum_{i=0}^{m-k}(s_i\times s_{i+k})$。

如果暴力算肯定会出问题，因为对于所有的 $k$，总共的时间复杂度大概是 $O(n^2)$ 的。所以我们在这里做一个变形。

我们发现每次被乘起来的两个数的规律：下标之差为定值，这会让熟悉多项式操作的你觉得不爽，而两两相乘，最后相加的形式又让你觉得很熟悉。所以你想到了一个套路：将其中一个数组翻转过来。

对于一个 $k$，我们要求的是 $\sum_{i-j=k}(s_i\times s_j)$。如果将数组翻转过来，其中的一个变量（比如 $j$）就会变成 $-j$ 这时候就会有 $i+(-j)=k$，也就是一个卷积的形式，然后就可以使用神奇的快速傅里叶变换加速了。

最后注意一个细节，如果 $k>0$，很明显选取的区间可以以符合要求的数作为边界。而当 $k=0$ 时不行，所以说我们得要将 $k>0$ 和 $k=0$ 的情况分开讨论。

```cpp
  #include <iostream>
  #include <cctype>
  #include <cstdio>
  #include <cstring>
  #include <algorithm>
  #include <cmath>
  using namespace std;

  #define Pi acos(-1)

  inline int read() {
      char ch;
      int k = 1;
      while (!isdigit(ch = getchar()))
          if (ch == '-')
              k = -1;
      int sum = ch ^ 48;
      while (isdigit(ch = getchar()))
          sum = (sum << 1) + (sum << 3) + (ch ^ 48);
      return sum * k;
  }

  struct complex {
      double x, y;

      inline complex(double a = 0, double b = 0) : x(a), y(b) { };

      inline complex operator + (const complex& n) const {
          return complex(x + n.x, y + n.y);
      }

      inline complex operator - (const complex& n) const {
          return complex(x - n.x, y - n.y);
      }

      inline complex operator * (const complex& n) const {
          return complex(x * n.x - y * n.y, x * n.y + y * n.x);
      }
  };

  int n, x, arr[200010];
  int rev[800010], p, len;
  long long s[200010], cnt, lst, ans;
  complex arr1[800010], arr2[800010];

  inline void get_rev() {
      for (len = 1; len <= cnt * 2; len <<= 1, p++) ;
      for (int i = 1; i < len; i++)
          rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (p - 1));
  }

  inline void FFT(complex* arr, int p, int len, int typ) {
      for (int i = 0; i < len; i++)
          if (rev[i] > i)
              swap(arr[i], arr[rev[i]]);
      int step = 1;
      complex w, dw, x, y;
      for (int i = 1; i < len; i <<= 1) {
          step <<= 1;
          dw = complex(cos(Pi / i), sin(Pi / i) * typ);
          for (int j = 0; j < len; j += step) {
              w = complex(1, 0);
              for (int d = 0; d < i; d++, w = w * dw) {
                  x = arr[j + d], y = w * arr[j + d + i];
                  arr[j + d] = x + y;
                  arr[j + d + i] = x - y;
              }
          }
      }
      if (typ == -1) {
          for (int i = 0; i < len; i++)
              arr[i].x /= (double)len;
      }
  }

  int main() {
      n = read(), x = read();
      for (int i = 0; i < n; i++)
          arr[i] = read();
      ans = 0;
      for (int i = 0; i < n; i++) {
          if (arr[i] < x) {
              s[cnt++] = i - lst + 1;
              ans += (i - lst - 1) * (i - lst) / 2 + i - lst;
              lst = i + 1;
          }
      }
      s[cnt++] = n - lst + 1;
      ans += (n - lst - 1) * (n - lst) / 2 + n - lst;
      for (int i = 1; i < cnt; i++)
          arr1[i - 1].x = s[i];
      for (int i = 0; i < cnt - 1; i++)
          arr2[cnt - 2 - i].x = s[i];
      get_rev();
      FFT(arr1, p, len, 1);
      FFT(arr2, p, len, 1);
      for (int i = 0; i < len; i++)
          arr1[i] = arr1[i] * arr2[i];
      FFT(arr1, p, len, -1);
      printf("%lld ", ans);
      for (int i = 1; i <= n; i++)
          printf("%lld ", (long long)(arr1[cnt - 3 + i].x + 0.5));
      printf("\n");
      return 0;
  }
```

---

## 作者：wwlw (赞：0)

[Link](https://www.luogu.com.cn/problem/CF993E)
---------------

### Solution

考虑先将序列 $<a_i>$ 转换，定义序列 $<b_i>$。令 $b_i=[a_i<X]$，那么对 $b_i$ 做前缀和的话，得到的 $s_i$ 就表示前 $i$ 个数中小于 $X$ 的数的个数。那么对于一个特定的 $k$ ，我们就需要回答 $s_i=s_j+k$ 的有序对 $(i,j)$ 的个数。我们成功地将区间计数转换成了元素统计，这实际上是这类问题的惯用伎俩。

再进一步，$s$ 相同的前缀可以合并，令 $c_i$ 表示 $s=i$ 的前缀个数。那么对于答案 $G(k)$ ，就有
$$G(k)=\sum_{i=0}^{m-k} c_i\times c_{i+k}$$
其中 $m$ 为所有小于 $X$ 的数的个数，容易知道当 $i>m-k$ 时 $c_{i+k}$ 都为零，所以不用统计。

到了这一步就很简单了，容易发现是一个差卷积的形式。具体地，令 $A_{i}=c_i$ 和 $B_{i}=c_{m-i}$，那么上式就可以写成
$$G(k)=\sum_{i=0}^{m-k} A_{i}\times B_{m-i-k}$$
求出 $A$ 和 $B$ 的卷积后再把前 $m$ 项 reverse 一下，就能得到 $G$ 序列。复杂度 $O(n\log n)$。

特别的，$G(0)$ 并不能这么处理，我们可以单独算出 $G(0)$，复杂度 $O(n)$。
$$G(0)=\sum_{i=0}^m \frac{c_i(c_i-1)}{2}$$

```cpp
#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define N ((1<<21)+3)
#define db double
#define ll long long

const db PI=acos(-1);

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct Complex{
    db x,y;
    Complex(db x_=0,db y_=0):x(x_),y(y_){}
    Complex operator +(const Complex X){return Complex(x+X.x,y+X.y);}
    Complex operator -(const Complex X){return Complex(x-X.x,y-X.y);}
    Complex operator *(const Complex X){return Complex(x*X.x-y*X.y,x*X.y+y*X.x);}
}a[N];

int n,X,m=0,op=0,rk[N];
ll G[N];

void FFT(){
    for(int i=0;i<n;i++)
        if(i<rk[i]) swap(a[i],a[rk[i]]);
    for(int p=2;p<=n;p<<=1){
        int len=p>>1;
        Complex w(cos(2*PI/p),op*sin(2*PI/p));
        for(int k=0;k<n;k+=p){
            Complex now(1.0,0.0);
            for(int l=k;l<k+len;l++){
                Complex t=now*a[l+len];
                a[l+len]=a[l]-t;
                a[l]=a[l]+t;
                now=now*w;
            }
        }
    }
}

int main(){
    n=read(),X=read();
    a[0]=1; int n_=n;ll ret=0;
    for(int i=1;i<=n;i++){
        int x=read();
        if(x<X) a[++m].x=1;
        else a[m].x++;
    }
    for(int i=0;i<=m;i++) a[m-i].y=a[i].x,ret+=(ll)a[i].x*(a[i].x-1)/2;
    for(n=1;n<=(m<<1);n<<=1);
    for(int i=0;i<n;i++)
        rk[i]=(rk[i>>1]>>1)|((i&1)? n>>1:0);
    op=1,FFT();
    for(int i=0;i<n;i++) a[i]=a[i]*a[i];
    op=-1,FFT();
    for(int i=0;i<=m;i++) G[i]=(ll)(a[i].y/n/2+0.5);
    reverse(G,G+1+m),G[0]=ret;
    for(int i=0;i<=n_;i++) printf("%lld ",G[i]);
}
```

---

