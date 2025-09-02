# Beautiful Mirrors

## 题目描述

Creatnx has $ n $ mirrors, numbered from $ 1 $ to $ n $ . Every day, Creatnx asks exactly one mirror "Am I beautiful?". The $ i $ -th mirror will tell Creatnx that he is beautiful with probability $ \frac{p_i}{100} $ for all $ 1 \le i \le n $ .

Creatnx asks the mirrors one by one, starting from the $ 1 $ -st mirror. Every day, if he asks $ i $ -th mirror, there are two possibilities:

- The $ i $ -th mirror tells Creatnx that he is beautiful. In this case, if $ i = n $ Creatnx will stop and become happy, otherwise he will continue asking the $ i+1 $ -th mirror next day;
- In the other case, Creatnx will feel upset. The next day, Creatnx will start asking from the $ 1 $ -st mirror again.

You need to calculate [the expected number](https://en.wikipedia.org/wiki/Expected_value) of days until Creatnx becomes happy.

This number should be found by modulo $ 998244353 $ . Formally, let $ M = 998244353 $ . It can be shown that the answer can be expressed as an irreducible fraction $ \frac{p}{q} $ , where $ p $ and $ q $ are integers and $ q \not \equiv 0 \pmod{M} $ . Output the integer equal to $ p \cdot q^{-1} \bmod M $ . In other words, output such an integer $ x $ that $ 0 \le x < M $ and $ x \cdot q \equiv p \pmod{M} $ .

## 说明/提示

In the first test, there is only one mirror and it tells, that Creatnx is beautiful with probability $ \frac{1}{2} $ . So, the expected number of days until Creatnx becomes happy is $ 2 $ .

## 样例 #1

### 输入

```
1
50
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
10 20 50
```

### 输出

```
112
```

# 题解

## 作者：_jimmywang_ (赞：22)

牛逼的期望dp。

对期望的理解确实加深了。

首先我们设 $dp_i$ 为**到第 $i$ 面镜子后到第 $n$ 面的期望天数**。

所以在第 $i$ 面镜子会有两种情况。

第一种：镜子回答"漂亮"，**花一天**走到下一面镜子。这种情况的贡献是 $p_i \times (dp_{i+1}+1)$。

第二种：镜子回答"不漂亮"，**花一天**走到第一面镜子。这种情况的贡献是 $(1-p_i) \times (dp_{1}+1)$。

于是

$$dp_i=p_i \times (dp_{i+1}+1)+(1-p_i) \times (dp_{1}+1)$$

$$=p_i \times dp_{i+1}+(1-p_i) \times dp_{1} +1$$

其中 $dp_{n+1}=0$。

然后就尴尬了。

我们要求的是 $dp_1$，但是我们递推dp数组的时候要用到 $dp_1$。


于是我们开始推式子。

从 $dp_1$ 开始。

$$dp_1=p_1 \times dp_{2}+(1-p_1) \times dp_{1} +1$$

$$p_1 \times dp_1=p_1 \times dp_{2} +1$$

$$dp_1=dp_{2} +\frac{1}{p_1}$$

然后是 $dp_2$。


$$dp_2=p_2 \times dp_{3}+(1-p_2) \times dp_{1} +1$$

$$dp_2=p_2 \times dp_{3}+(1-p_2) \times (dp_{2} +\frac{1}{p_1}) +1$$

化简可得：

$$p_2 \times dp_2=p_2 \times dp_{3} +\frac{1}{p_1}-\frac{p_2}{p_1}+1$$

$$dp_2=dp_{3} +\frac{1}{p_1p_2}+\frac{1}{p_2}-\frac{1}{p_1}$$

于是

$$dp_1=dp_{3} +\frac{1}{p_1p_2}+\frac{1}{p_2}$$

于是我们继续推下去，发现 $dp_1=dp_{i+1}+\sum_{j=1}^i\prod_{k=i-j+1}^{i}\dfrac{1}{p_k}$。

后面那些东西说人话就是 $\dfrac{1}{p_1p_2\dots p_i}+\dfrac{1}{p_2p_3\dots p_i}+\dots +\dfrac{1}{p_{i-1}p_i}+\dfrac{1}{p_i}$。

然后我们知道 $dp_{n+1}=0$。

于是从后往前算就算完了。

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<ll>
#define fe(i,e) for(ll i=0;i<e.size();i++) 
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define fn(i,a,b) for(ll i=a;i>=b;i--)
ll qp(ll a,ll b,ll p){
    ll ans=1;while(b){
        if(b&1)ans=ans*a%p;
        a=a*a%p;b>>=1;
    }return ans;
}
ll n;ll a[200010],ans,tmp;
const ll mod=998244353;
int main(){
    scanf("%lld",&n);f(i,1,n)scanf("%lld",&a[i]);tmp=1;
    fn(i,n,1){
        tmp=tmp*100%mod*qp(a[i],mod-2,mod)%mod;
        ans=(ans+tmp)%mod;
    }printf("%lld",ans);
    return 0;
}
```



---

## 作者：万弘 (赞：19)

考虑正向推.

$f(i)$表示从1走到$i$(并且第$i$天也快乐)的代价.显然$f(n)$即为所求.

推一下式子(将$p_i$简写为$p$)

$$f(i)=(f(i-1)+1)\times p/100+(f(i-1)+1+f(i))\times (100-p)/100$$

$$100f(i)=(f(i-1)+1)\times p+(f(i-1)+1+f(i))\times (100-p)$$

$$0=100(f(i-1)+1)-p\times f(i)$$

$$f(i)=(f(i-1)+1)\times 100/p$$

时间复杂度$\mathcal O(n)$
```cpp
/**********/
#define MAXN 200011
ll f[MAXN];
const ll mod=998244353;
ll Qpow(ll a,ll p)
{
    ll res=1;
    while(p)
    {
        if(p&1)res=res*a%mod;
        a=a*a%mod;
        p>>=1;
    }
    return res;
}
int main()
{
    ll n=read();
    f[0]=0;
    for(ll i=1;i<=n;++i)
    {
        ll p=read();
        f[i]=(f[i-1]+1)*100%mod*Qpow(p,mod-2)%mod;
    }
    printf("%lld",f[n]);
    return 0;
}
```

---

## 作者：UltiMadow (赞：14)

若 $\LaTeX$ 崩掉请来我的博客查看（

推的过程比较长，自认为比较好理解（

期望 dp 题

令 $f_i$ 为当前到第 $i$ 个镜子，并且现在开心的期望天数

接下来有一个显然的转移方程：
$$
\begin{aligned}
f_i &= (f_{i-1}+1)\cdot \frac {p_i}{100}+2\cdot (f_{i-1}+1)\cdot \frac {p_i}{100}\cdot (1-\frac {p_i}{100})+3\cdot(f_{i-1}+1)\cdot \frac{p_i}{100}\cdot(1-\frac {p_i}{100})^2+\cdots \\
&= \frac {p_i}{100}(f_{i-1}+1)\sum_{j=1}^\infty j\cdot(1-\frac{p_i}{100})^{j-1} 
\end{aligned}
$$
显然我们要求的就是后面那一坨东西

转化一下：
$$
\begin{aligned}
\sum_{j=1}^\infty j\cdot(1-\frac{p_i}{100})^{j-1} &= \sum_{j=1}^{\infty}\sum_{k=j}^\infty(1-\frac{p_i}{100})^{k-1}
\end{aligned}
$$
发现这就是个等比数列求和，于是有：
$$
\begin{aligned}\sum_{j=1}^{\infty}\sum_{k=j}^\infty(1-\frac{p_i}{100})^{k-1}&=\sum_{j=1}^\infty\frac{100}{p_i}\times (1-\frac{p_i}{100})^{j-1}\\
&=\frac{100}{p_i}\sum_{j=1}^\infty (1-\frac{p_i}{100})^{j-1}\\
&=(\frac{100}{p_i})^2
\end{aligned}
$$
带回原式：
$$
\begin{aligned}
f_i&= \frac {p_i}{100}(f_{i-1}+1)\sum_{j=1}^\infty j\cdot(1-\frac{p_i}{100})^{j-1} \\
&=\frac{100}{p_i}(f_{i-1}+1)
\end{aligned}
$$
接下来直接递推

然后膜数是个质数，费马小定理求逆元即可

---

## 作者：zzr8178541919 (赞：8)

### Solution

非常经典的一道期望$DP$题。

期望$DP$的总体套路一定要会，一般是算从$i$到$n$的期望或从$1$到$i$的期望

考虑设置状态$dp[i]$为从$1→i$的期望次数，那么很自然的有：

$dp[i]=dp[i-1]*pi+1+(1-pi)(dp[i-1]+1+dp[i])=(dp[i-1]+1)/pi$

我们发现$pi×100∈[0,100]$之间，所以我们可以
预处理100个逆元,可以使常数降低。


```cpp
#include<cmath>
#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
#define reg register
using namespace std;
const int maxn=7e7+5;
const int mod=998244353;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-')
        f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
int n;
int p[maxn];
long long inv[105];
long long dp[maxn];
int mul(int x,int y,int mod)
{
	long long res=1;
	while(y)
	{
		if(y & 1)
		res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res%mod;
}
int main()
{
	n=read();
	inv[0]=inv[1]=1;
	for(reg int i=2;i<=100;++i)
	{
		inv[i]=inv[mod%i]*(mod-mod/i)%mod;
	}
	for(reg int i=1;i<=n;++i)
	{
		p[i]=read();
	}
	long long pp=100;
	for(reg int i=1;i<=n;++i)
	{
		dp[i]=pp%mod*(dp[i-1]+1)%mod*inv[p[i]]%mod;
	}
	printf("%lld\n",dp[n]);
 	return 0;
}
/*

7
1
1 2 1 
1 3 3
2 4 2
2 5 5
2 6 2
3 7 2

*/

```


---

## 作者：Computer1828 (赞：4)

upd：加上代码及代码推导过程

设从第 $i$ 个镜子开始的期望天数为 $f_i$。不难推得：

$$f_i = p_i(f_{i+1}+1)+(1-p_i)(f_1+1)$$

边界 $f_{n+1} = 0$，答案为 $f_1$。

当 $i = 1$ 时，$f_1 = f_2+\frac{1}{p_1}$。

当 $i = 2$ 时，$f_1 = f_3+\frac{1+\frac{1}{p_1}}{p_2}$。

当 $i = 3$ 时，$f_1 = f_4+\frac{1+\frac{1+\frac{1}{p_1}}{p_2}}{p_3}$。

推得：

$$f_1 = \frac{1+\frac{1+\frac{1+\frac{...}{p_{n-3}}}{p_{n-2}}}{p_{n-1}}}{p_n}$$

$$=\dfrac{1+p_1+p_1p_2+\dots +p_1p_2\dots p_{n-1}}{p_1p_2p_3\dots p_n}$$

$O(n)$ 递推，预处理一个前缀积即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
#define mod 998244353
using namespace std;
int n;
ll p[N],s[N];
inline ll qpow(ll a,ll b){
	ll res = 1,base = a;
	while(b){
		if(b&1) res = res*base%mod;
		base = base*base%mod;
		b >>= 1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	s[0] = 1;
	for(int i = 1;i<=n;++i) scanf("%lld",p+i),p[i] = p[i]*qpow(100,mod-2)%mod,s[i] = s[i-1]*p[i]%mod;
	ll A = 1,B = s[n];
	for(int i = 2;i<=n;++i) A += s[i-1],A %= mod;
	printf("%lld",A*qpow(B,mod-2)%mod);
	return 0;
}
```


---

## 作者：Plozia (赞：3)

宣传博客 $\to$ [link](https://blog.csdn.net/BWzhuzehao/article/details/113767017)

本题为期望 DP 入门题。

为了方便，下面直接认为 $p_i$ 就是概率。

首先设状态，$f_i$ 为从第一面镜子到第 $i$ 面镜子都高兴的期望天数。

然后列方程：

1. 第 $i$ 天询问失败，从头开始。
此时概率为 $1-p_i$，消耗天数为 $f_{i-1}+1+f_i$，于是概率乘代价为 $(1-p_i)(f_{i-1}+1+f_i)$。
2. 第 $i$ 天询问成功。
此时概率为 $p_i$，消耗天数 $f_{i-1}+1$，于是概率乘代价为 $p_i(f_{i-1}+1)$。

综上，有 $f_i=(1-p_i)(f_{i-1}+1+f_i)+p_i(f_{i-1}+1)$。

然而 $p_i$ 只是概率，真正代码中还需要除以 100 才行。

除以 100 之后最后解得 $f_i=\dfrac{100(f_{i-1}+1)}{p_i}$，线性递推即可，不要忘记逆元。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 2e5 + 10, P = 998244353;
int n, p[MAXN];
LL f[MAXN];

int read()
{
	int sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9') {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

LL ksm(LL a, LL b)
{
	LL ans = 1 % P;
	for (; b; b >>= 1)
	{
		if (b & 1) ans = ans * a % P;
		a = a * a % P;
	}
	return ans;
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i) p[i] = read();
	for (int i = 1; i <= n; ++i) f[i] = 100ll * (f[i - 1] + 1) % P * ksm(p[i], P - 2) % P;
	printf("%lld\n", f[n]);
	return 0;
}
```

---

## 作者：Fairicle (赞：3)

[P6835](https://www.luogu.com.cn/problem/P6835) 的弱化版。

设 $f_i$ 为 $i$ 到 $i+1$ 的期望天数。

$$f_i=\frac{p_i}{100}\times1+\frac{100-p_i}{100}\times(1+s+f_i)$$

其中 $s=\sum_{j=1}^{i-1}f_i$

化简一下能得到

$$f_i=\frac{100+(100-p_i) \times s}{p_i}$$

线性递推即可，答案就是 $\sum_{i=1}^nf_i$。

code：
```cpp
#include"bits/stdc++.h"
using namespace std;
#define ri register int
#define ll long long
#define mod 998244353
inline ll ksm(ll x,int y){
	ll res=1;
	while(y){
		if(y&1) res*=x,res%=mod;
		x*=x,x%=mod;
		y>>=1;
	}
	return res;
}
#define N 200010
int n,p[N];
ll f[N],s;
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(ri i=1;i<=n;++i){
		cin>>p[i];
		f[i]=(100+(100-p[i])*s%mod)*ksm(p[i],mod-2)%mod;
		s=(s+f[i])%mod;
	}
	cout<<s;
	return 0;
}
```


---

## 作者：ADay (赞：1)

[更好的阅读体验](https://www.cnblogs.com/aday526/p/solution-cf1265e.html)

## Solution

我们可以列出 $n$ 个概率方程，然后手玩方程即可。

设第 $i$ 个镜子开始的期望天数为 $x_i$，通过第 $i$ 面镜子的概率为 $p_i$，则依题意有：

$$x_i=p_i(x_{i+1}+1)+(1-p_i)(x_1+1)$$

并且，$x_{n+1}=0$，要求解 $x_1$ 。

由上，$x_1=\dfrac{1}{p_1}+x_2=\dfrac{\dfrac{1}{p_1}+1}{p_2}+x_3=\dfrac{\dfrac{\dfrac{1}{p_1}+1}{p_2}+1}{p_3}+x_4=\cdots=\dfrac{\dfrac{\dfrac{\cdots+1}{p_{n-2}}+1}{p_{n-1}}+1}{p_n}$



$\therefore x_1=\dfrac{\dfrac{\dfrac{\cdots+1}{p_{n-2}}+1}{p_{n-1}}+1}{p_n}$

## Code

那么用一个变量 $ans$ 记录当前 $x_i$ 即可，记得勤取模。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=998244353;
int n,k,ans;
int inv(int x){//逆元
	int res=1,y=P-2;
	for(;y;y>>=1,x=1ll*x*x%P)
		if(y&1)res=1ll*res*x%P;
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);//注意概率以百分数读入
		ans=100ll*(ans+1)%P*inv(x)%P;
	}printf("%d\n",ans);
	return 0;
}
```





---

## 作者：木木！ (赞：1)

大概是本题最简洁的解法（

首先假设 $f_i$ 表示从 $1$ 开始通过第 $i$ 面镜子期望需要花费多少天，$p_i$ 为通过第 $i$ 面镜子的概率，定义 $f_0=0$，则有：

$$
f_i=\frac{f_{i-1}+1}{p_i}
$$

$\Theta(100)$ 预处理出 $[1,100]$ 的逆元，就可以在单次询问 $\Theta(1)$ 的时间内计算出 $\dfrac{1}{p_i}$ 的值，随后直接用一个变量保存 $f_i$ 并顺推即可。

由于 $100$ 可以很轻松地卡进 L1 Cache，所以数组访问几乎不需要花时间。并且顺推时可以直接边读入边处理，不需要 $2\times 10^5$ 的中间数组，时间和空间开销都极小。

需要注意 $100\times 998244352\times 998244352$ 可能会爆 long long，要模两次。或者也可以直接将 $100$ 乘到逆元里面。

时间复杂度 $\Theta(100+n)$。

附 AC 代码：

```cpp
#include <cstdio>
using namespace std;

int getint()
{
	char ch;
	while((ch=getchar()) < '!') ;
	int x = ch^'0';
	while((ch=getchar()) > '!') x = (x*10)+(ch^'0');
	return x;
}

#define mod 998244353

int invi[105];

int main()
{
	invi[1] = 100;  // 将 100 乘入逆元
	for(int i=2; i<=100; ++i)
	{
		invi[i] = 1LL*(mod-mod/i)*invi[mod%i]%mod;
	}
	
	const int n = getint();
	register int fi = 0;
	for(int i=1; i<=n; ++i)
	{
		fi = 1LL*(fi+1)*invi[getint()] %mod;
	}
	
	printf("%d\n",fi);
}
```

---

## 作者：TheShadow (赞：1)

# 闲扯

期望经典模型？

# 题面

[CF1265E Beautiful Mirrors](https://www.luogu.com.cn/problem/CF1265E)

# Solution

我们设 $E(i)$ 表示询问当前在询问第 $i$ 面镜子，离终止的期望天数，那么答案就是 $E(1)$ 。

我们将终止条件转化为问到第 $n+1$ 面镜子，无论回答是什么都结束。那么我们有 $E(n+1)=0$ 。

我们有如下转移方程：
$$
E(i)=\frac{p_i}{100}E(i+1)+\frac{100-p_i}{100}E(1)+1
$$
然后我们有一个经典操作：**设 $E(i)=k\cdot E(1)+b$ ，通过递推求出 $E(n+1)$ 的 $k,b$，然后解出 $E(1)$ ** 。

移项化简可得：
$$
E(i+1)=\frac{100k_i+p_i-100}{p_i}E(1)+\frac{100b_i-100}{p_i}
$$
也就是 $k_{i+1}=\frac{100k_i+p_i-100}{p_i},b_{i+1}=\frac{100b_i-100}{p_i}$ 。

然后解方程 $k_{n+1}E(1)+b_{n+1}=0$ 即可。

# Code

```c++
#include<bits/stdc++.h>
#define del(a,i) memset(a,i,sizeof(a))
#define ll long long
#define inl inline
#define il inl void
#define it inl int
#define ill inl ll
#define re register
#define ri re int
#define rl re ll
#define mid ((l+r)>>1)
#define lowbit(x) (x&(-x))
#define INF 0x3f3f3f3f
using namespace std;
template<class T>il read(T &x){
	int f=1;char k=getchar();x=0;
	for(;k>'9'||k<'0';k=getchar()) if(k=='-') f=-1;
	for(;k>='0'&&k<='9';k=getchar()) x=(x<<3)+(x<<1)+k-'0';
	x*=f;
}
template<class T>il _print(T x){
	if(x/10) _print(x/10);
	putchar(x%10+'0');
}
template<class T>il print(T x){
	if(x<0) putchar('-'),x=-x;
	_print(x);
}
ll mul(ll a,ll b,ll mod){long double c=1.;return (a*b-(ll)(c*a*b/mod)*mod)%mod;}
it qpow(int x,int m,int mod){
	int res=1,bas=x;
	while(m){
		if(m&1) res=(1ll*res*bas)%mod;
		bas=(1ll*bas*bas)%mod,m>>=1;
	}
	return res;
}
const int MAXN = 2e5+5,mod = 998244353;
int n,p[MAXN],inv[105],k=1,b,ans;
it add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
it mul(int x,int y){
	return 1ll*x*y%mod;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	for(ri i=1;i<=n;++i)
		read(p[i]);
	inv[1]=1;
	for(ri i=2;i<=100;++i)
		inv[i]=mul(mod-mod/i,inv[mod%i]);
	for(ri i=1;i<=n;++i){
		k=mul(add(mul(100,k),add(p[i],mod-100)),inv[p[i]]);
		b=mul(add(mul(100,b),mod-100),inv[p[i]]);
	}
	b=mod-b;
	ans=mul(b,qpow(k,mod-2,mod));
	print(ans);
	return 0;
}
```



---

## 作者：t162 (赞：0)

期望 DP 的题为什么一定要用期望 DP 做呢（

设期望需要的天数为 $x$。

如果一次通过，则需要耗费 $n$ 天，概率为 $\prod p_i\ (1\leq i\leq n)$。

如果一次没通过，在第 $i$ 天失败了，则期望需要耗费 $x+i$ 天，概率为 $(1-p_i)\prod p_j\ (1\leq j\lt i)$。

列出方程：

$$x=n\prod_{1\leq i\leq n}p_i+\sum_{1\leq i\leq n}(x+i)(1-p_i)\prod_{1\leq j\lt i} p_j$$

手解得到：

$$x=\frac{n\prod_{1\leq i\leq n}p_i+\sum_{1\leq i\leq n}i(1-p_i)\prod_{1\leq j\lt i} p_j}{1-\sum_{1\leq i\leq n}(1-p_i)\prod_{1\leq j\lt i} p_j}$$

用前缀积对 $p_{1\dots n}$ 处理一下就可以快速求出答案。

```cpp
#include<cstdio>
int const p = 998244353;
int i100;
int plus(int x, int y) { return x + y >= p ? x + y - p : x + y; }
int minus(int x, int y) { return x - y < 0 ? x - y + p : x - y; }
int mul(int x, int y) { return 1ll * x * y % p; }
int pow(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = mul(ret, x);
		x = mul(x, x), y >>= 1;
	}
	return ret;
}
int inv(int x) { return pow(x, p - 2); }
int a[200005], n, b[200005];
int main() {
	scanf("%d", &n), i100 = inv(100), b[0] = 1;
	for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] = mul(a[i], i100);
	for (int i = 1; i <= n; i++) b[i] = mul(a[i], b[i - 1]);
	int A = mul(b[n], n), B = 0;
	for (int i = 1; i <= n; i++) A = plus(A, mul(mul(b[i - 1], minus(1, a[i])), i));
	for (int i = 1; i <= n; i++) B = plus(B, mul(b[i - 1], minus(1, a[i])));
	printf("%d\n", mul(A, inv(minus(1, B))));
}
```

---

## 作者：Presentation_Emitter (赞：0)

期望DP入门题。

原题可以抽象为在一张有向图的随机游走（为方便起见，用 $p_i$ 而不是 $\frac{p_i}{100}$ 表示成功概率）

![](https://cdn.luogu.com.cn/upload/image_hosting/jr3m530y.png)

（有一个节点 $1$ 上的自环没有显示，概率为 $1-p_1$）

对于点 $1$，有以下情况：

|天数|概率|
|:-:|:-:|
|1|$p$|
|2|$p(1-p)$|
|3|$p(1-p)^2$|
|…|…|
|$\infty$|$\lim\limits_{x\rightarrow\infty} p(1-p)^{x}=0$|

据此总结得离开点 $1$ 的期望步数（记为 $E_1$）为：

$$
\begin{aligned} &\quad \sum\limits_{i=1}^{\infty} ip_1(1-p_1)^{i-1}\\
&=p_1 [\sum\limits_{i=1}^{\infty} (1-p_1)^{i-1}]^2\\
\end{aligned}
$$

根据等比数列求和公式，原式
$
=p_1 \cdot \frac{1}{p_1^2}
=\frac{1}{p_1}
$

当然不知道这玩意还是可以的，设 $S=\sum\limits_{i=1}^{\infty} (1-p_1)^{i-1}$，则

$$
\begin{aligned}
(1-p_1)S=\sum\limits_{i=1}^{\infty} (1-p_1)^{i}\\
S-(1-p_1)S=1\\
p_1S=1\\
S=\frac{1}{p_1}
\end{aligned}$$

由此推导，对于点 $i$，离开它的期望步数（记为 $E_i$）为：

$$\frac{E_{i-1}+1}{p_i}$$

其中 $E_{i-1}+1$ 即为到达点 $i$ 的期望步数。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define uint unsigned int
#define ull unsigned ll
#define ll long long
#define reg register
#define db double
#define il inline
#define gc getchar
#define pc putchar
#ifdef ONLINE_JUDGE
#undef pc
#define pc(a) puts("I am a cheater!")
#endif
#define HgS 998244353
il ll rd()
{
	reg ll res=0,lab=1;
	reg char ch=gc();
	while((ch<'0'||ch>'9')&&ch!=EOF)
	{if(ch=='-')lab=-lab;ch=gc();}
	while(ch>='0'&&ch<='9')
		res=(res<<3)+(res<<1)+(ch&15),ch=gc();
	return res*lab;
}
il void prt(ll x,char t='\n')
{
	char ch[70];int tp=0;
	if(!x){fputs("0",stdout);if(t)pc(t);return;}
	if(x<0)pc('-'),x=-x;
	while(x)ch[++tp]=(x%10)^48,x/=10;
	while(tp)pc(ch[tp--]);
	if(t)pc(t);
}
il ll qpow(ll n,ll e=HgS-2,ll p=HgS)
{
	reg ll res=1;
	while(e)
	{
		if(e&1)res=res*n%p;
		n=n*n%p;e>>=1;
	}
	return res;
}
ll n,p[200005],ans[200005];
int main()
{
	n=rd();
	for(int i=1;i<=n;++i)p[i]=rd();
	ans[1]=100*qpow(p[1])%HgS;
	for(int i=2;i<=n;++i)
		ans[i]=(ans[i-1]+1)*qpow(p[i])%HgS*100%HgS;
	prt(ans[n]);
	return 0;
}
```

---

## 作者：Bring (赞：0)

[更好的阅读体验请看这里](https://www.cnblogs.com/BrianPeng/p/13738935.html)

## 一种特殊的概率期望dp方法

设$e_i$表示当前在第$i$个镜子的期望开心天数，则答案为$e_1$，**而且可以设$e_{n+1}=0$**

给出$e_i$的转移方程（假设$p_i$为第$i$天镜子回答'beautiful'的概率）

$$e_i=p_ie_{i+1}+(1-p_i)e_1+1,1\leqslant i\leqslant n$$

移项，以$e_{i+1}$为主元

$$e_{i+1}=\dfrac{e_i+(p_i-1)e_1-1}{p_i}$$

以此可以将所有$e_i,1\leqslant i\leqslant n+1$都用$e_1$表示，并且用归纳法可知它们均可表示为$e_i=ae_1+b$的形式（$a,b$为常数）

所以可以初始化$a=1,b=0$（即$e_1=1e_1+0$），根据输入的$p_i$转移$a,b$直到最后的$ae_1+b=e_{n+1}=0$得到$e_1=-\frac{b}{a}$

可以一边读入一边做，所以不需要开任何数组

**Time complexity: $O(n\log P)$**

**Memory complexity: $O(1)$**

上代码

```cpp
//This program is written by Brian Peng.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define Rd(a) (a=rd())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int rd(){
	int x;char c(getchar());bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	c^'-'?(k=1,x=c&15):k=x=0;
	while(isdigit(Gc(c)))x=x*10+(c&15);
	return k?x:-x;
}
void wr(int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(int i(a);i<(b);++i)
#define Frn1(i,a,b) for(int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define P (998244353)
int n,p,a(1),b;
int fpw(int a,int b){int r(1);while(b)a%=P,b&1?r=r*a%P:0,b>>=1,a*=a;return r;}
int const i100=fpw(100,P-2);
signed main(){
	Rd(n);
	while(n--)p=rd()*i100%P,a+=p-1,--b,a=a*fpw(p,P-2)%P,b=b*fpw(p,P-2)%P;
	wr((P-(b*fpw(a,P-2))%P)%P),exit(0);
}
```


---

## 作者：fanypcd (赞：0)

令 $p_i$ 表示第 $i$ 个镜子回答漂亮的概率。

设 $f_i$ 表示前 $i$ 个镜子‘开心到极点’的期望天数，考虑怎么通过 $f_{i - 1}$ 推出 $f_i$。

如果第 $i$ 个镜子回答漂亮，此时的期望为 $p_i \times (f_{i - 1} + 1)$，如果回答不漂亮，则需要重头再来（有 $f_{i - 1} + 1$ 的期望浪费了，还需要 $f_i$）。

即：

$$f_i = p_i \times (f_{i - 1} + 1) + (1 - p_i) \times (f_{i - 1} + 1 + f_i)$$

整理一下:

$$f_i = \frac{f_{i - 1} + 1}{p_i}$$

直接递推即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
const int mod = 998244353;
#define N 200005
int qpow(int a, int b)
{
	int ans = 1;
	while(b)
	{
		if(b & 1)
		{
			ans = (1ll * ans * a) % mod;
		}
		a = (1ll * a * a) % mod;
		b >>= 1;
	}
	return ans;
}
int n, p[N];
int f[N];
signed main()
{
	read(n);
	for(int i = 1; i <= n; i++)
	{
		read(p[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		f[i] = 100ll * (f[i - 1] + 1) % mod * qpow(p[i], mod - 2) % mod;
	}
	printf("%d", f[n]);
	return 0;
}
```

---

## 作者：Rainbow_qwq (赞：0)

[CF1265E Beautiful Mirrors](https://www.luogu.com.cn/problem/CF1265E)

---

upd:有个地方错了，改一下。

这是一道关于概率的数学题。

设 $e(i)$ 表示从**第 $i$ 面镜子开始，到询问结束**的期望天数。

显然 $e(n+1)=0$ ，而 $e(1)$ 就是要求的答案。

对于 $e(i)$ ，询问下一次有 $p[i]$ 的概率去问下一面镜子，就是 $e(i+1)$ ；有 $1-p[i]$ 的概率回到第 $1$ 面镜子，就是 $e(1)$ 。

所以： $e(i)=p[i]\times e(i+1)+(1-p[i])\times e(1)+1$

那么：

$e(1)=p[1]\times e(2)+(1-p[1])\times e(1)+1$

解得 $e(2)=e(1)-\dfrac{1}{p[1]}$ 。

$e(2)=p[2]\times e(3)+(1-p[2])\times e(1)+1$

解得 $e(3)=e(1)-\dfrac{1}{p[1]}-\dfrac{1}{p[1]\times p[2]}$

~~观察可得，~~ $e(n+1)=e(1)-\dfrac{1}{p[1]}-\dfrac{1}{p[1]\times p[2]} \cdots-\dfrac{1}{p[1]\times p[2]\times \cdots \times p[n]}=0$

所以：$e(1)=\dfrac{1}{p[1]}+\dfrac{1}{p[1]\times p[2]} \cdots+\dfrac{1}{p[1]\times p[2]\times \cdots \times p[n]}$

通分得：

$e(1)=\dfrac{1+p[1]+p[1]\times p[2]+\cdots +p[1]\times p[2]\times \cdots \times p[n-1]}{p[1]\times p[2]\times \cdots \times p[n]}$

这个柿子可以 $O(n)$ 求！

如果知道 $\dfrac{1+p[1]+p[1]\times p[2]+\cdots +p[1]\times p[2]\times \cdots \times p[i-1]}{p[1]\times p[2]\times \cdots \times p[i]}$

那么求 $\dfrac{1+p[1]+p[1]\times p[2]+\cdots +p[1]\times p[2]\times \cdots \times p[i+1-1]}{p[1]\times p[2]\times \cdots \times p[i+1]}$ 时，只要分子先加上分母，分母再乘上 $p[i+1]$ 即可。

然后就能 $O(n)$ 递推了~

代码：
```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define int long long
using namespace std;
inline int read()
{
    char c=getchar();int x=0;bool f=0;
    for(;!isdigit(c);c=getchar())f^=!(c^45);
    for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+(c^48);
    if(f)x=-x;return x;
}
const int mod=998244353;
int p,q,x,n,inv100;
inline int qpow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)res=res*a%mod;
	return res;
}
inline int inv(int a){return qpow(a,mod-2);}
signed main()
{
	n=read();
	p=0,q=1;
    //p:分子 q:分母
	inv100=inv(100);
	For(i,1,n){
		x=read()*inv100%mod;
		p=(p+q)%mod;//分子加分母
		q=q*x%mod;//分母×概率
	}
	cout<<p*inv(q)%mod;
	return 0;
}
```

---

