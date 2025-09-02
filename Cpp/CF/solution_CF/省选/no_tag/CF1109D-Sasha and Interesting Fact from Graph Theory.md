# Sasha and Interesting Fact from Graph Theory

## 题目描述

有一次，在上课时，Sasha 感到无聊，决定和朋友们聊天。突然，他看到了 Kefa。关于 Kefa 的话题可以聊个没完没了，所以我们就不展开了。话题转到了图论。Kefa 承诺，如果 Sasha 帮他计算出美丽树的数量，他就会告诉 Sasha 一个有趣的图论事实。

在本题中，一棵树是一个带权连通图，由 $n$ 个顶点和 $n-1$ 条边组成，边的权值是 $1$ 到 $m$ 之间的整数。Kefa 这样定义一棵树的美丽：他在树中找到他最喜欢的两个顶点——编号为 $a$ 和 $b$ 的顶点，并计算它们之间的距离。顶点 $x$ 和 $y$ 之间的距离是从 $x$ 到 $y$ 的简单路径上所有边的权值之和。如果顶点 $a$ 和 $b$ 之间的距离等于 $m$，那么这棵树就是美丽的。

Sasha 喜欢图论，更喜欢有趣的事实，所以他同意帮助 Kefa。幸运的是，Sasha 认识你——Byteland 最棒的程序员。请你帮助 Sasha 计算美丽树的数量。两棵树被认为是不同的，如果存在一条边只出现在其中一棵树中，或者同一条边的权值不同。

Kefa 提醒 Sasha，美丽树的数量可能非常多，因此只需要输出答案对 $10^9+7$ 取模后的结果。

## 说明/提示

在第一个样例中，有 $5$ 棵美丽树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1109D/d88275e8124b7826186324238111a8213d909f6c.png)

在第二个样例中，以下树是美丽的：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1109D/96d3e8f4e82c072eb5d39cd2ef80bfe6884bfbd7.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2 1 3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 1 1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 15 1 5
```

### 输出

```
345444
```

# 题解

## 作者：Tx_Lcy (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/CF1109D)

## 思路

$\rm dalao$ 们的题解怎么都这么复杂，我提供一个简单的解法。

首先这个 $n,m \le 10^6$，显然是一个 $\mathcal O(n/n \log n)$ 解法。

我们考虑枚举 $a,b$ 中间有几条边，不妨设为 $i$，那么插板一下，这 $i$ 条边就有 $\dbinom{m-1}{i-1}$ 种取值。

别的边可以乱填，所以当前答案还要乘上 $m^{n-1-i}$。

然后考虑选出总共 $i+1$ 个点来组成这 $i$ 条边。

两端的 $a,b$ 是不能动的，所以方案数是 $\dbinom{n-2}{i-1}$，然后中间可以乱排，所以再乘上 $(i-1)!$。

接下来考虑另外的点。

现在问题就等价于给你 $n$ 个点，构造出 $i+1$ 棵树，要求有 $i+1$ 个特殊点都要在不同的树中，问方案数。

显然的 广义 $\rm Cayley$ 定理：给你 $n$ 个点，构造出 $k$ 棵树，使得给定的 $k$ 个点没有两个点属于同一颗树的方案数为 $k \times n^{n-k-1}$。

直接套公式即可，注意 $i=n-1$ 时要特判。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int const mod=1e9+7;
int fac[N],inv[N];
inline int qpow(int a,int b,int t=1){for(;b;b>>=1,a=a*a%mod)if(b&1)t=t*a%mod;return t;}
inline void init(int p){
    fac[0]=1;
    for (int i=1;i<=p;++i) fac[i]=fac[i-1]*i%mod;
    inv[p]=qpow(fac[p],mod-2);
    for (int i=p-1;~i;--i) inv[i]=inv[i+1]*(i+1)%mod;
}
inline int C(int n,int m){
    if (n<m) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m,x,y;cin>>n>>m>>x>>y;
    init(max(n,m));
    int ans=0;
    for (int i=1;i<=min(n-1,m);++i){
        int res=C(m-1,i-1);
        //隔板法算出当前长度路径的取值个数
        res*=C(n-2,i-1)*fac[i-1]%mod;
        res%=mod;
        //从 n-2 个点中取出 i-1 个点
        res*=qpow(m,n-1-i);
        res%=mod;
        //另外边的取值可以乱选
        if (i!=n-1)
            res*=(i+1)*qpow(n,n-(i+1)-1)%mod,
            res%=mod;
        ans+=res;
        ans%=mod;
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：do_while_true (赞：3)

先 orz qyc

先考虑枚举 $a$ 和 $b$ 中间有 $i$ 个点，那么中间这些边边权的分配就是一个插板法 $\binom{m-1}{i}$，树中剩余 $(n-1-(i+1))$ 条边的边权就可以任意选了，这部分方案数是 $m^{n-i-2}$．

然后考察树的形态，发现这里相当于 $(i+2)$ 棵有根树，树和树之间有顺序，并且还要求第一棵树根节点编号是 $a$，最后一棵是 $b$．

如果不考虑这两个根节点的编号限制的话，那么就相当于要计算 $n$ 个有标号点连成 $k$ 棵有根树，树和树之间有顺序的方案数。既然限制了第一棵树和最后一棵树的编号，再除掉 $n$ 和 $(n-1)$ 即可（第一棵树的根的标号有 $n$ 种选择方案，只想要其中一种，先除 $n$；除完之后最后一棵树的标号有 $(n-1)$ 种选择方式，同理除掉 $(n-1)$）．

现在问题变为了计算 $n$ 个有标号点连成 $k$ 棵有根树的方案数，并且要求树和树之间有顺序。

令 $T$ 有标号有根树的 EGF，则 $T=ze^T$，答案即为 $n![z^n]T^k$．

拉格朗日反演。

$T$ 的复合逆 $G=\frac{z}{e^z}$，再令 $H=z^k$．
$$
\begin{aligned}
n![x^n]T^k&=n![z^n]H(T)\\
&=(n-1)![z^{n-1}]H'(z)\left(\frac{z}{G}\right)^n
\\
&=k(n-1)![z^{n-1}]z^{k-1}e^{nz}
\\
&=k(n-1)![z^{n-k}]e^{nz}
\\
&=k(n-1)!n^{n-k}\frac{1}{(n-k)!}
\\
&=k\cdot n^{n-k-1}\cdot n^{\underline k}
\end{aligned}
$$

问题解决。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<random>
#include<assert.h>
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define dbg(x) cerr<<"In Line "<< __LINE__<<" the "<<#x<<" = "<<x<<'\n';
#define dpi(x,y) cerr<<"In Line "<<__LINE__<<" the "<<#x<<" = "<<x<<" ; "<<"the "<<#y<<" = "<<y<<'\n';
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int>pii;
typedef pair<ll,int>pli;
typedef pair<ll,ll>pll;
typedef pair<int,ll>pil;
typedef vector<int>vi;
typedef vector<ll>vll;
typedef vector<pii>vpii;
typedef vector<pil>vpil;
template<typename T>T cmax(T &x, T y){return x=x>y?x:y;}
template<typename T>T cmin(T &x, T y){return x=x<y?x:y;}
template<typename T>
T &read(T &r){
	r=0;bool w=0;char ch=getchar();
	while(ch<'0'||ch>'9')w=ch=='-'?1:0,ch=getchar();
	while(ch>='0'&&ch<='9')r=r*10+(ch^48),ch=getchar();
	return r=w?-r:r;
}
template<typename T1,typename... T2>
void read(T1 &x,T2& ...y){read(x);read(y...);}
const int mod=1000000007;
inline void cadd(int &x,int y){x=(x+y>=mod)?(x+y-mod):(x+y);}
inline void cdel(int &x,int y){x=(x-y<0)?(x-y+mod):(x-y);}
inline int add(int x,int y){return (x+y>=mod)?(x+y-mod):(x+y);}
inline int del(int x,int y){return (x-y<0)?(x-y+mod):(x-y);}
int qpow(int x,int y){
	int s=1;
	while(y){
		if(y&1)s=1ll*s*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return s;
}
const int N=2000010;
int n,m,a,b,fac[N],inv[N],t,ans;
int C(int x,int y){
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int calc(int n,int k){
	return n==k?fac[n]:1ll*k*qpow(n,n-k-1)%mod*fac[n]%mod*inv[n-k]%mod;
}
signed main(){
	#ifdef do_while_true
//		assert(freopen("data.in","r",stdin));
//		assert(freopen("data.out","w",stdout));
	#endif
	read(n,m,a,b);t=max(n,m);
	fac[0]=1;for(int i=1;i<=t+1;i++)fac[i]=1ll*fac[i-1]*i%mod;
	inv[t+1]=qpow(fac[t+1],mod-2);
	for(int i=t;~i;--i)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=0;i<=min(n-2,m-1);i++){
		int s=1ll*C(m-1,i)*calc(n,2+i)%mod*qpow(m,n-1-(i+1))%mod;
		cadd(ans,s);
	}
	cout << 1ll*ans*qpow(n,mod-2)%mod*qpow(n-1,mod-2)%mod << '\n';
    #ifdef do_while_true
//		cerr<<'\n'<<"Time:"<<1.0*clock()/CLOCKS_PER_SEC*1000<<" ms"<<'\n';
	#endif
	return 0;
}
```

---

## 作者：Soulist (赞：3)

一个菜鸡的辣鸡做法


树的总数为 $n^{n-2}$，假设某一种方案中两者的距离为 $x$，那么对于另外的 $n-1-x$ 条边其可以任意赋值，对于这 $x$ 条边问题等价于求解将 $[1,m]$ 的数放入这 $x$ 个箱子内使得权值和为 $m$ 的方案数。

视为将 $[0,m-1]$ 放入 $x$ 个盒子内使得权值和为 $m-x$ 的方案数，注意到 $m-1\ge m-x$，所以视为盒子内的大小没有限制。这里视为有 $m-x$ 个球和 $x-1$ 个挡板，将挡板插入球内的方案数，视为有 $m-1$ 个盒子放入 $x-1$ 个数即可，方案数为 $\binom{m-1}{x-1}$

妈的不会插板法，怕推错，生成函数再来一次算了。

考虑每个盒子放置物品的生成函数，其实就是 $\frac{1}{1-x}$，所以答案为 $\Big([x^{m-k}]\frac{1}{(1-x)^k}\Big)$，然后考虑广义二项式定理，我们知道展开式为

$$\sum_{i=0}^{\infty} \frac{(k+i-1)^{\underline{i}}}{i!}x^i$$

所以答案为 $\binom{m-1}{m-k}=\binom{m-1}{k-1}$

同时，我们所认为的 "大球" 的本质是一条链，所以在这上面填入其他数的方案数为 $\binom{n-2}{\rm sz-2}$，同时这些数可以任意排布，所以还有贡献 $\rm (sz-2)!$，插板的方案数 $\binom{\rm m-1}{\rm sz-2}$，那么可以得到答案为：

$$\sum_{i=2}^{n} m^{n-i}\binom{n-2}{i-2}\times (i-2)!\times \dbinom{m-1}{i-2}\times [\text{生成树的数量}]$$

考虑计算生成树的数量，通过 $\rm prufer$ 序列来计树，将这条大小为 $i$ 的链视为一个整体，那么其出现次数等于其度数 $-1$，设其出现次数为 $k$，那么其对于树的形态的影响为 $i^{k+1}$（这是因为其他点可以向这 $i$ 个点的任意一个连边），同时对于剩余的位置有他们可以被填入 $n-i$ 个下标中的任何一个元素。

所以我们可以得到生成树的数量为：

$$\sum_{k=0}^{n-i-1} i^{k+1}\times \dbinom{n-i-1}{k}\times (n-i)^{n-i-1-k}$$

将 $i$ 提取出来，剩余的式子显然是一个二项式的展开式，所以回代得到：

$$i\cdot n^{n-i-1}$$

然后记得特判 $i=n$ 的情况，然后预处理一个组合数，计算答案即可，复杂度是预处理的 $\log$，复杂度 $\mathcal O(n\log n)$（懒得写 $\mathcal O(n)$ 的）

仔细说的话答案其实就是：

$$(n-2)!\times \dbinom{m-1}{n-2}+\sum_{i=2}^{n-1}\frac{(n-2)!}{(n-i)!}\times i\cdot n^{n-i-1}\times \dbinom{m-1}{i-2}\times m^{n-i}$$

为啥别人几乎都不推导就做出来了呢....果然是我太菜了吗...

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
#define int long long
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int P = 1e9 + 7 ;
const int N = 1e6 + 5 ;  
int n, m, fac[N], inv[N], mf[N], nf[N] ;  
int fpow( int x, int k ) {
	int ans = 1, base = x  ;
	while( k ) {
		if( k & 1 ) ans = ans * base % P ;
		base = base * base % P, k >>= 1 ; 
	} return ans ; 
}
int C( int x, int y ) {
	if( x < y ) return 0 ;
	return 1ll * fac[x] * inv[y] % P * inv[x - y] % P ;  
}
signed main()
{
	n = gi(), m = gi(), mf[0] = nf[0] = fac[0] = inv[0] = 1 ; 
	rep( i, 1, max( n, m ) ) fac[i] = fac[i - 1] * i % P, inv[i] = fpow( fac[i], P - 2 ) ;
	rep( i, 1, n ) mf[i] = mf[i - 1] * m % P, nf[i] = nf[i - 1] * n % P ; 
	int Ans = fac[n - 2] * C(m - 1, n - 2) % P ; 
	for( re int i = 2; i < n; ++ i ) {
		int x = fac[n - 2] * inv[n - i] % P * i % P * nf[n - i - 1] % P * C(m - 1, i - 2) % P * mf[n - i] % P ; 
		Ans = ( Ans + x ) % P ; 
	}
	cout << Ans << endl ; 
	return 0 ;
}
```

---

## 作者：Sshenyyyu (赞：2)

这题首先显然a,b是没有用的，因为每个点都一样

枚举这两个定点之间的边数，直接用隔板法就能求出定点中间链的标号方案数

然后我们要求出有多少树满足这两定点距离恰好为枚举的边数

考虑使用prufer序，为了方便，我们把这一条链上的点强制依次标号为n n-1 n-2 ...

我们发现一个结论，prufer序最后几项为恰为n,n-1,n-2,...但这样的prufer序形成的树不一定满足条件，因为n-i与n-i+1间夹了一些奇奇怪怪的点

要使n-i与n-i+1相邻，我们只要使n-i+1的前一项一定为n n-1 n-2 ... n-i 中的一个即可（手动画图的结果，理解一下好像也是这样），prufer序再前面的就随便填了

最后我们为每个点标上标号就行了
（注意一下这里的i与代码中的i不太一样）

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<set>
using namespace std;
const int M=1000000007;
typedef long long ll;
int n,m,a,b,i;
ll s[1000005],ans;
ll exgcd(ll a,ll b,ll &x,ll &y)
{
	if(b==0)
	{
		x=1;
		y=0;
		return a;
	}
	ll g=exgcd(b,a%b,x,y);
	ll tmp=x;
	x=y;
	y=tmp-a/b*y;
	return g;
}
ll ni(ll a)
{
	ll x,y;
	exgcd(a,M,x,y);
	return x;
}
ll C(ll x,ll y)
{
	return s[x]*ni(s[y])%M*ni(s[x-y])%M;
}
ll Quick_pow(ll a,ll b)
{
	ll s=a,ans=1;
	while(b>0)
	{
		if(b&1)
			ans=ans*s%M;
		s=s*s%M;
		b>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d %d %d %d",&n,&m,&a,&b);
	s[0]=1;
	for(i=1;i<=1000000;i++)
		s[i]=s[i-1]*i%M;
	for(i=0;i<=n-2&&i<=m-1;i++)
		if(i==n-2)
			ans=(ans+C(m-1,i)*C(n-2,i)%M*s[i]%M*Quick_pow(m,n-2-i)%M)%M;
		else
			ans=(ans+C(m-1,i)*C(n-2,i)%M*s[i]%M*Quick_pow(n,n-3-i)%M*(i+2)%M*Quick_pow(m,n-2-i)%M)%M;
	cout<<(ans%M+M)%M;
}
```


---

## 作者：EXODUS (赞：1)

# Part 1：前言
纪念一下自己想出来的计数 dp（虽然不是第一道 qwq）。

感觉自己的描述会自然一点，虽然各位大佬写的比我更好/bx。

# Part 2：正文

考虑直接上乘法原理，将这个问题拆开考虑。

这个问题可以分成这样两步

1. 构造一条连接 $a$ 和 $b$ 的长度为 $m$ 的链。

2. 将其它的点挂在这些点下面形成一棵 $n$ 个节点的森林。

已经很有乘法原理的感觉了，但我们不妨再细化一下。

1. 从 $n$ 个点中选 $x$ 个点组成链。

2. 将这 $x$ 个点任意排列。

3. 给每条边赋一个边权，使得链的长度为 $m$。

4. 将其它的点挂在这些点下面形成一棵 $n$ 个节点的森林。

5. 给剩下的边随便赋一个边权。

注意到 1 操作中的 $x$ 可以枚举，且方案数也是容易计算的 $\binom {n-2}{x-2}$，2 和 5 的操作也是容易的，分别是 $x!$ 和 $m^{n-x+1}$，问题就是剩下的 3 和 4 操作。

首先考察 3，其实就是个插板法，相当于向 $m-1$ 个空中插入 $x-2$ 个板子，贡献为 $\binom {m-1}{x-2}$。

问题出在 4 上，这是广义 Cayley 定理的形式，答案为 $kn^{n-k-1}$~~但是现在不会证，回头想出来会补上证明~~。

# Part 3：代码
```cpp
int n,m,k;
const int N=1e6+7;
int fac[N],inv[N];
const int mod=1e9+7;

bool mem2=0;

void mul(int &x,int y){x=1ll*x*y%mod;return;}
int tim(int x,int y){return 1ll*x*y%mod;}
void fix(int &x){x>=mod?x-=mod:x<0?x+=mod:0;return;}
int rem(int x){return x>=mod?x-=mod:x<0?x+=mod:x;}
void add(int &x,int y){fix(x+=y);}
int qp(int b,int m){
	m=(m+mod-1)%(mod-1);
	int res=1;
	for(;m;m>>=1){
		if(m&1)mul(res,b);
		mul(b,b);
	}return res;
}


void init(){
	for(int i=fac[0]=1;i<=1e6;i++)fac[i]=tim(fac[i-1],i);
	inv[1000000]=qp(fac[1000000],mod-2);
	for(int i=1e6-1;i>=0;i--)inv[i]=tim(inv[i+1],i+1);
}

int C(int x,int y){
	return tim(fac[x],tim(inv[y],inv[x-y]));
}

int main(){
	init();
	n=read(),m=read();int a=read(),b=read();
	int ans=0;
	for(int x=2,a,b,c,d,e,f;x<=min(n,m+1);x++){
		a=qp(m,n-x);
		b=tim(a,C(n-2,x-2));
		c=tim(b,C(m-1,x-2));
		d=tim(c,x);
		e=tim(d,qp(n,n-x-1));
		f=tim(e,fac[x-2]);
		add(ans,f);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：蒟蒻tyy (赞：1)

### $\texttt{Descritpion:}$

给定 $n,m,a,b$，让你构造一颗树，边权在 $[1,m]$ 之间。满足 $a \to b$ 的路径的权值的和为 $m$。求方案数目。 

### $\texttt{Solution:}$

考虑 $a \to b$ 的路径上有几个点【包括 $a,b$。】

假设有 $x$ 个点，那么这 $x$ 个点要满足 **权值的和为$m$**。【其他点无限制。】

我们考虑组成这条链的点的编号和排列方式。可以得到：

$$
ans = \sum\limits_{x=2}^n{n \choose x}(x-2)!{m-1 \choose x}m^{n-x}[\mathbf{Tree \ number}]
$$

考虑怎么算 $\mathbf{Tree \ number}$。

显然，由 ~~**广为人知**~~ 的 **广义** $\texttt{Cayley}$ 定理可以知道【文末会给出**广义** $\texttt{Cayley}$ 定理】：

$$
\mathbf{Tree \ Number} = xn^{n-x-1}
$$

所以最后的答案为：

$$
ans = (n-2)!{m-1 \choose n-2}+\sum\limits_{x=2}^{n-1}{{m-1 \choose x-2}x\frac{(n-2)!}{(n-x)!}n^{n-x-1}m^{n-x}}
$$

前面的一项是因为 $x = n$ 的时候要特判。

### **广义** $\texttt{Cayley}$ 定理

$n$ 个标号节点形成一个有 $k$ 颗树的森林,使得给定的 $k$ 个点没有两个点属于同一颗树的方案数为 $kn^{n-k-1}$。

证明可以用 **归纳法** 或者 **$\texttt{Prufer}$** 序列。

---

## 作者：chlchl (赞：0)

本题前置知识：Prufer 序列，[广义 cayley 定理](https://www.zhihu.com/question/497583950/answer/2535178948)。

## Solution
感觉如果知道了上面两个东西这题最多只有绿题难度吧。

将原问题拆分成两个子问题：先确定 $a,b$ 之间有多少条边，再给它们赋权。

枚举 $a,b$ 之间的边数 $i$，那么中间会有 $i-1$ 个点，这里的方案数是 $\binom{n-2}{i-1}$。但是这 $i-1$ 个点的排布是有序的，所以要乘上 $(i-1)!$。

~~其实你可以理解为传说中的排列数 $A_{n-2}^{i-1}$。~~

给这些边赋权，显然就是在 $m-1$ 个缝隙中插 $i-1$ 个板，方案数是 $\binom{m-1}{i-1}$。

然后我们要解决的问题就是以这 $i+1$ 个点为根构造一个森林，总点数为 $n$，并且 $i+1$ 个点都不在同一棵树内。根据广义 cayley 定理，这个的方案数是 $(i+1)n^{n-(i+1)-1}$。

最后，剩下的 $n-i-1$ 条边需要一个边权，带一个 $m^{n-i-1}$ 的系数即可。

剩下的就是注意 $i=n-1$ 的时候广义 cayley 定理是不存在的，特判一下即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 1e6 + 10;
const int MOD = 1e9 + 7;
int n, m, a, b;
ll fac[N], invf[N], ans;

ll exp(ll a, ll b){
	ll cnt = 1;
	while(b){
		if(b & 1)
			(cnt *= a) %= MOD;
		(a *= a) %= MOD, b >>= 1; 
	}
	return cnt;
}

ll C(int a, int b){
	if(a < b)
		return 0;
	return fac[a] * invf[b] % MOD * invf[a - b] % MOD;
}

int main(){
	scanf("%d%d%d%d", &n, &m, &a, &b);
	int mx = max(m, n);
	fac[0] = invf[0] = 1;
	for(int i=1;i<=mx;i++)
		fac[i] = fac[i - 1] * i % MOD;
	for(int i=1;i<=mx;i++)
		invf[i] = exp(fac[i], MOD - 2);
//	cout << C(4, 2) <<endl;
	for(int i=1;i<=min(n-1,m);i++){
		ll res = C(n - 2, i - 1) * fac[i - 1] % MOD;//先选定 a,b 之间的点 
		(res *= exp(m, n - i - 1) * C(m - 1, i - 1) % MOD) %= MOD;//边权 
		if(i != n - 1)//特判 i = n - 1 
			(res *= 1ll * (i + 1ll) * exp(n, n - (i + 1ll) - 1) % MOD) %= MOD;//剩下树的形态
		(ans += res) %= MOD;
	}
	printf("%lld\n", ans % MOD);
	return 0;
}
```

~~组合数学不难的时候还是挺好玩的。~~

---

