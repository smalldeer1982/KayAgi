# YY的GCD

## 题目描述

神犇 YY 虐完数论后给傻× kAc 出了一题

给定 $N, M$，求 $1 \leq x \leq N$，$1 \leq y \leq M$ 且 $\gcd(x, y)$ 为质数的 $(x, y)$ 有多少对。


## 说明/提示

$T = 10^4$，$N, M \leq 10^7$。


## 样例 #1

### 输入

```
2
10 10
100 100```

### 输出

```
30
2791```

# 题解

## 作者：An_Account (赞：250)

说实话，个人认为这道题不适合作为第一道莫比乌斯反演的题。因为这道题蕴含着一些奇妙的数学技巧。对于莫比乌斯反演的初学者，建议看看我的一篇博客[**莫比乌斯反演-让我们从基础开始**](https://www.luogu.org/blog/An-Amazing-Blog/mu-bi-wu-si-fan-yan-ji-ge-ji-miao-di-dong-xi)。我在这篇博客中详细地介绍了推导莫比乌斯反演的思维过程以及各种常用方法，由浅入深。

下面开始吧

首先我们理一下题意，这道题实际上是求

$$\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)\in prime]$$

根据常规思路，我们不妨枚举一下这里的$gcd(i,j)$，就假设它叫$k$吧。顺便令$n\leq m$，显然有$k\leq n$

$$=\sum_{k=1}^{n}\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=k]\ \ \ (k\in prime)$$

同时除以$k$，将$[gcd(i,j)=k]$化成$[gcd(i,j)=1]$

$$=\sum_{k=1}^{n}\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[gcd(i,j)=1]\ \ \ (k\in prime)$$

下面有请~~我们喜闻乐见的~~莫比乌斯反演

和下面的大佬们不一样，我一看到那个需要设函数的莫比乌斯反演公式就头大，所以我决定，不用那个公式。

我们知道莫比乌斯函数的性质

$$\sum_{d|n}\mu(d)=[n=1]$$

我们把这个$n$换成$gcd(i,j)$

$$[gcd(i,j)=1]=\sum_{d|gcd(i,j)}\mu(d)$$

把这个东西扔到原式中去，于是原式

$$=\sum_{k=1}^{n}\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{d|gcd(i,j)}\mu(d)\ \ \ (k\in prime)$$

套路一下，我们枚举$d$，顺便把$d$提到前面来。
由于$d|gcd(i,j)$，可得$i,j$都是$d$的倍数，要满足这个条件，不妨将$i,j$的上限都除以$d$。相当于把$i$变成$\lfloor\frac{i}{d}\rfloor *d$，$j$变成$\lfloor\frac{j}{d}\rfloor *d$

于是我们就跟中间的那两个$\sum$说再见了

$$=\sum_{k=1}^{n}\sum_{d=1}^{\lfloor\frac{n}{k}\rfloor}\mu(d)*\lfloor\frac{n}{kd}\rfloor*\lfloor\frac{m}{kd}\rfloor\ \ \ (k\in prime)$$

我最开始就是推到这里，然后开心地枚举了一下$k$，结果T掉了

然后仔细地想了一想

对于这种看似已经化成最简的式子，我们有一个常用方法可以降低时间复杂度

我们设$T=kd$，有

$$=\sum_{k=1}^{n}\sum_{d=1}^{\lfloor\frac{n}{k}\rfloor}\mu(d)*\lfloor\frac{n}{T}\rfloor*\lfloor\frac{m}{T}\rfloor\ \ \ (k\in prime)$$

枚举一下$T$，提到前面去

$$=\sum_{T=1}^{n}\lfloor\frac{n}{T}\rfloor*\lfloor\frac{m}{T}\rfloor\sum_{k|T,k\in pimre}\mu(\frac{T}{k})$$

我们惊喜地发现，最后那个东西，是可以预处理的！

考虑每一个质数$k$，对于$k$的倍数$T$，将它的值加上$\mu(\frac{T}{k})$

代码实现如下

``` cpp 
void sieve() {
    mu[1]=1;
    for (int i=2;i<=10000000;i++) {
        if (!flag[i]) prime[++cnt]=i,mu[i]=-1;
        for (int j=1;j<=cnt&&i*prime[j]<=10000000;j++) {
            flag[i*prime[j]]=1;
            if (i%prime[j]==0) break;
            mu[i*prime[j]]=-mu[i];
        }
    }
    for (int i=1;i<=cnt;i++)
        for (int j=1;prime[i]*j<=10000000;j++)
            f[j*prime[i]]+=mu[j];
    for (int i=1;i<=10000000;i++)
        sum[i]=sum[i-1]+f[i];
}
```

处理一下前缀和$sum$，就可以$AC$啦

分享完整代码

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define LL long long
LL mu[10000010];int flag[10000010],prime[10000010],cnt,f[10000010],sum[10000010];
void sieve() {
    mu[1]=1;
    for (int i=2;i<=10000000;i++) {
        if (!flag[i]) prime[++cnt]=i,mu[i]=-1;
        for (int j=1;j<=cnt&&i*prime[j]<=10000000;j++) {
            flag[i*prime[j]]=1;
            if (i%prime[j]==0) break;
            mu[i*prime[j]]=-mu[i];
        }
    }
    for (int i=1;i<=cnt;i++)
        for (int j=1;prime[i]*j<=10000000;j++)
            f[j*prime[i]]+=mu[j];
    for (int i=1;i<=10000000;i++)
        sum[i]=sum[i-1]+f[i];
}
LL solve(int a,int b) {
    LL ans=0;
    if (a>b) swap(a,b);
    for (int l=1,r=0;l<=a;l=r+1) {
        r=min(a/(a/l),b/(b/l));
        ans+=(LL)(sum[r]-sum[l-1])*(LL)(a/l)*(LL)(b/l);
    }
    return ans;
}
int main() {
    sieve();
    int n,m,T;scanf("%d",&T);
    while (T--) {
        scanf("%d%d",&n,&m);
        if (n>m) swap(n,m);
        printf("%lld\n",solve(n,m));
    }
}
```

---

## 作者：pengym (赞：132)

(洛谷评测机似乎变慢了一些，我之前的代码没有太注意**int**和**long long**会TLE。现在重新修改了，并顺便把评论中大佬们提出的错误全部修改OVO)
#### 这应该是我做的第一道莫比乌斯反演的题目。
我顺便来安利一下自己的博客[peng-ym's blog](http://www.cnblogs.com/peng-ym/)里面也有[莫比乌斯反演](http://www.cnblogs.com/peng-ym/p/8647856.html)和[整除分块](http://www.cnblogs.com/peng-ym/p/8661118.html)的介绍，不知道的可以看一看哦！
#### 解题思路
- 显然，题目要求的$Ans$实际上就是$\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(x,y)=prim]$的值
- 接下来，我们就开始进行欢乐的***推式子***了
- 对于这种与$gcd$有关的莫比乌斯反演，一般我们都是套路的去设$f(d)$为$gcd(i,j)=d$的个数，$F(n)$为$gcd(i,j)=d$和$d$的倍数的个数，即：
$$f(d)=\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=d]$$
$$F(n)=\sum_{n|d}f(d)=\lfloor\frac{N}{n}\rfloor\lfloor\frac{M}{n}\rfloor$$
$$f(n)=\sum_{n|d}\mu(\lfloor\frac{d}{n}\rfloor)F(d)$$
- 这样，我们便可以开心的化简这个式子了！
$$Ans=\sum_{p\in prim}\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=p]$$
将$f(p)$带入得：
$$Ans=\sum_{p\in prim}f(p)$$
然后就莫比乌斯反演一下
$$Ans=\sum_{p\in prim}\sum_{p|d}\mu(\lfloor\frac{d}{p}\rfloor)F(d)$$
我们换一个枚举项，我们枚举$\lfloor\frac{d}{p}\rfloor$
$$Ans=\sum_{p\in prim}\sum_{d=1}^{min(\lfloor\frac{n}{p}\rfloor,\lfloor\frac{m}{p}\rfloor)}\mu(d)F(dp)=\sum_{p\in prim}\sum_{d=1}^{min(\lfloor\frac{n}{p}\rfloor,\lfloor\frac{m}{p}\rfloor)}\mu(d)\lfloor\frac{n}{dp}\rfloor\lfloor\frac{m}{dp}\rfloor$$
这个$dp$一看就很不爽，于是我们把它换成$T$
$$Ans=\sum_{T=1}^{min(n,m)}\sum_{t|T,t\in prime}\mu(\lfloor\frac{T}{t}\rfloor)\lfloor\frac{n}{T}\rfloor\lfloor\frac{m}{T}\rfloor$$
$$Ans=\sum_{T=1}^{min(n,m)}\lfloor\frac{n}{T}\rfloor\lfloor\frac{m}{T}\rfloor(\sum_{t|T}\mu(\lfloor\frac{T}{t}\rfloor))$$
- 推到这里，我们就可以开始做了。如果是单组询问，我们就直接$O(n)$做。~~(不过好像一般这种题，都不会让你直接处理。)~~如果是多组数据的话，我们就只要在打一个简单的**整除分块**就可以了。后面的$\mu$函数可以线筛出来。由于整除分块的缘故，我们就只需要记一个前缀和就可以了。
- 下面贴一个完整的代码吧。

```cpp
#include<bits/stdc++.h>
#define N 10000100
using namespace std;
inline void read(int &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;	
}
inline void print(long long x)
{
    static int cnt;
    static int a[15];
    cnt=0;
    do
    {
        a[++cnt]=x%10;
        x/=10;
    }while(x);
    for(int i=cnt;i>=1;i--)putchar(a[i]+'0');
    puts("");
}
bool vis[N];
long long sum[N];
int prim[N];
int mu[N],g[N];
int cnt;
void get_mu(int n)
{
    mu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]){mu[i]=-1;prim[++cnt]=i;}
        for(int j=1;j<=cnt&&prim[j]*i<=n;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]==0)break;
            else mu[prim[j]*i]=-mu[i];
        }
    }
    for(int j=1;j<=cnt;j++)
        for(int i=1;i*prim[j]<=n;i++)g[i*prim[j]]+=mu[i];
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+(long long)g[i];
}
int n,m;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("P2257.in","r",stdin);
    freopen("P2257.out","w",stdout);
#endif
    int t;
    read(t);
    get_mu(10000000);
    while(t--)
    {
        read(n);read(m);
        if(n>m)swap(n,m);
        static long long ans;ans=0;
        for(int l=1,r;l<=n;l=r+1)
        {
            r=min(n/(n/l),m/(m/l));
            ans+=1ll*(n/l)*(m/l)*(sum[r]-sum[l-1]);
        }
        print(ans);
    }
    return 0;
}
```

---

## 作者：Siyuan (赞：99)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io)

---

> 题目链接：[Luogu 2257](https://www.luogu.org/problemnew/show/P2257)

求解（多组数据）
$$\sum\limits_{i=1}^n\sum\limits_{i=1}^m [\gcd(i,j)=\texttt{prime}]$$
数据范围：$T=10^4$，$n,m\leqslant 10^7$

------

## Solution

以下所有过程中默认 $n\leqslant m$！

首先我们很自然想到枚举质数
$$\sum\limits_{p\in\texttt{prime}}\sum\limits_{i=1}^n\sum\limits_{i=1}^m [\gcd(i,j)=p]$$
根据套路提出 $p$
$$\sum\limits_{p\in\texttt{prime}}\sum\limits_{i=1}^{\left\lfloor\frac{n}{p}\right\rfloor}\sum\limits_{i=1}^{\left\lfloor\frac{m}{p}\right\rfloor} [\gcd(i,j)=1]$$
替换 $\gcd$ 得到
$$\sum\limits_{p\in\texttt{prime}}\sum\limits_{i=1}^{\left\lfloor\frac{n}{p}\right\rfloor}\sum\limits_{i=1}^{\left\lfloor\frac{m}{p}\right\rfloor}\sum\limits_{d\mid \gcd(i,j)} \mu(d)$$
枚举 $d$
$$\sum_{d=1}^{\left\lfloor\frac{n}{p}\right\rfloor}\mu(d)\sum\limits_{p\in\texttt{prime}}\sum\limits_{i=1}^{\left\lfloor\frac{n}{p}\right\rfloor}\sum\limits_{i=1}^{\left\lfloor\frac{m}{p}\right\rfloor} [d\mid\gcd(i,j)]$$
由于 $x$ 以内 $d$ 的倍数有 $\left\lfloor\frac{x}{d}\right\rfloor$ 个
$$\sum\limits_{p\in\texttt{prime}}\sum_{d=1}^{\left\lfloor\frac{n}{p}\right\rfloor}\mu(d)\left\lfloor\frac{n}{pd}\right\rfloor\left\lfloor\frac{m}{pd}\right\rfloor$$
这个式子直接求解的复杂度为 $O(\texttt{质数个数}*\sqrt{n}))$ 的，无法通过此题！

考虑优化：令 $k=pd$，代入得
$$\sum\limits_{p\in\texttt{prime}}\sum_{d=1}^{\left\lfloor\frac{n}{p}\right\rfloor}\mu(\frac{k}{p})\left\lfloor\frac{n}{k}\right\rfloor\left\lfloor\frac{m}{k}\right\rfloor$$
枚举 $k$
$$\sum\limits_{k=1}^n\sum\limits_{p\in\texttt{prime},p\mid k}\mu(\frac{k}{p})\left\lfloor\frac{n}{k}\right\rfloor\left\lfloor\frac{m}{k}\right\rfloor$$
设 $f(x)=\sum\limits_{p\in\texttt{prime},p\mid x}\mu(\frac{x}{p})$ ，询问转化为
$$\sum\limits_{k=1}^n f(k)\left\lfloor\frac{n}{k}\right\rfloor\left\lfloor\frac{m}{k}\right\rfloor$$
如果我们能求出 $f$ 的前缀和就能解决问题了，因此考虑对线性筛！

$f(x)=\sum\limits_{p\in\texttt{prime},p\mid x}\mu(\frac{x}{p})$，设 $x$ 的最小质因子为 $y$，即 $x=i\times y$

1. $x\in\texttt{prime}$：显然有 $f(x)=\mu(1)=1$

2. $i\bmod y=0$，即 $x$ 有多个最小质因子：

   - 当 $i$ 没有多个相同质因子时，那么当且仅当枚举的 $p=y$ 时，$\mu(\frac{x}{p})=\mu(i)$ 不为 $0$，故 $f(x)=\mu(i)$
   - 当 $i$ 也有多个相同质因子时，那么对于任何枚举的 $p$，都有 $\mu(\frac{x}{p})$ 的值都为 $0$，此时仍然有 $\mu(\frac{x}{p})=\mu(i)$，故 $f(x)=\mu(i)$

3. $i\bmod y\neq 0$，即 $x$ 有一个最小质因子：

   因为有 $f(i)=\sum\limits_{p\in\texttt{prime},p\mid i}\mu(\frac{i}{p})$，$f(x)=\sum\limits_{p\in\texttt{prime},p\mid x}\mu(\frac{i\times y}{p})$

   根据 $\mu$ 的线性筛过程，有 $\mu(\frac{i\times y}{p})=-\mu(\frac{i}{p})$，因此 $f(i)$ 中的每一项能都在 $f(x)$ 中找到对应的一项。而 $x$ 比 $i$ 多且仅多了一个质因子 $y$，因此 $f(x)$ 比 $f(i)$ 多了一项 $\mu(\frac{i\times y}{y})=\mu(i)$，故 $f(x)=-f(i)+\mu(i)$

综上所述，我们可以得到 $f$ 的线性筛方程
$$f(x)=\begin{cases}\mu(1) & x\in\texttt{prime}\\\mu(i) & i\bmod y=0\\-f(i)+\mu(i) & i\bmod y\neq 0\end{cases}$$
通过求 $f$ 的前缀和，我们可以利用整除分块通过本题！

**时间复杂度**：$O(n+T\sqrt{n})$

------

## Code

```cpp
#include <cstdio>
#include <algorithm>

const int N=1e7+5,lnN=15;
int n,m,tot,p[N/lnN],mu[N],f[N];
bool flg[N];

void init() {
    mu[1]=flg[1]=1;
    for(int i=2;i<N;++i) {
        if(!flg[i]) p[++tot]=i,mu[i]=-1,f[i]=1;
        for(int j=1;j<=tot&&i*p[j]<N;++j) {
            int x=i*p[j];
            flg[x]=1;
            if(i%p[j]==0) {
                f[x]=mu[i];
                mu[x]=0;
                break;
            } else {
                f[x]=-f[i]+mu[i];
                mu[x]=-mu[i];
            }
        }
        f[i]+=f[i-1];
    }
}
int main() {
    init();
    int T;
    for(scanf("%d",&T);T--;) {
        scanf("%d%d",&n,&m);
        long long ans=0;
        if(n>m) n^=m^=n^=m;
        for(int i=1,j;i<=n;i=j+1) {
            j=std::min(n/(n/i),m/(m/i));
            ans+=1LL*(f[j]-f[i-1])*(n/i)*(m/i);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：凄魉 (赞：27)

# 在这里提供一个新思路

想必大家都做过这个题吧
$$\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)=1]$$

有一种做法是利用$\mu$函数的一个性质
$$\sum_{d\mid n}\mu(d)=[n=1]$$
从而可以$O(\sqrt n+\sqrt m)$时间内求解答案

那么这个题让我们求
$$\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)\ is\ prime]$$

怎么办？？

如果有个函数(设为$f(n)$)它如果能有以下性质就好了
$$\sum_{d\mid n}f(d)=[n\ is \ prime]$$

没有还不能自己造嘛？

应该可以通过莫比乌斯反演找到另外一个数论函数求得我们的这个$f(n)$,但找不到怎么办？？~~(其实是我不会)~~

有一种方法可以通过一些加加减减来获得这个函数，就是我先让$f(n)$等于我们想要的那个值，比如我们要构造的这个函数就这样附上初值

$$f(n)=\begin{cases}1&n\ is\ prime\\0& n\ is\ composite \end{cases}$$

其核心就是再让
$$f(n)=f(n)-\sum_{d\mid n,d\neq n}f(d)$$
这样的话不就有

$$\sum_{d\mid n}f(d)=f(n)+\sum_{d\mid n,d\neq n}f(d)=\begin{cases}1& n\ is\ prime\\0&n\ is\ composite\end{cases}$$

（除了f(n)的初值以外其他前面的函数值的和都被抵消掉了）

然后附上实现第二步的代码(赋初值的代码就省略掉了)

```cpp
for (int i=1;i<=MAX;++i)
	for (int j=i<<1;j<=MAX;j+=i)
		f[j]-=f[i];
```

这两层for循环第二维是一个调和级数，总复杂度约为$nln(n)$

这种方法也是比较常用的吧，有些题目里面也需要自己用这个方法构造函数，而且它的常数也比直接用莫比乌斯反演还小~~(我们学校的同学竟然出了卡莫比乌斯反演的数据，让我们只能用这种方法求)~~

那么这个题就愉快地结束了，除了复杂度是$O(nln(n)+T(\sqrt N+\sqrt M))$在4秒时限下跑了3.6秒勉强卡过这道题外，其他都还是很好的

最后感谢DT_Kang神犇的指导，以及附上AC代码

```cpp
#include<cstdio>
#define N 10230040
#define U 10000000
#define ll long long
int min(int a,int b) {return a<b?a:b;}
long long f[N];int prime[N/10],cnt;bool ip[N];//其实10000000内只有660000个质数
int read(){//丑陋的快读
	int n=0;char a;bool z=false;
	while(a=getchar())
	{
		if (a>'9'||a<'0')
			if (z) break;
			else continue;
		if (!z) z=true;
		n=(n<<1)+(n<<3)+(a^48);
	}
	return n;
}
int main()
{
	int n,T,m,up,R;ll ans=0;
	for (int i=2;i<=U;++i)
	{
		if (!ip[i])
		{
			prime[++cnt]=i;
			f[i]=1;
		}
		for (int j=1;j<=cnt&&i*prime[j]<=U;++j)
		{
			ip[i*prime[j]]=true;
			if (i%prime[j]==0) break;
		}
	}
	for (int i=2;i<=U;++i)
		for (int j=i<<1;j<=U;j+=i)
			f[j]-=f[i];
	for (int i=2;i<=U;++i) f[i]+=f[i-1];
	T=read();
	while(T--)
	{
		ans=0;
		n=read();m=read();up=min(n,m);
		for (int i=1;i<=up;i=R+1)
		{
			R=min(n/(n/i),m/(m/i));
			ans+=1ll*(f[R]-f[i-1])*(n/i)*(m/i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Kelin (赞：17)

接下来的p表示质数p


$\sum_{p}\sum_{a=1}^n\sum_{b=1}^m[gcd(a,b)=p]$


$\sum_{p}\sum_{a=1}^{\left \lfloor \frac{n}{p} \right \rfloor}\sum_{b=1}^{\left \lfloor \frac{m}{p} \right \rfloor}[gcd(a,b)=1]$


$\sum_{p}\sum_{a=1}^{\left \lfloor \frac{n}{p} \right \rfloor}\sum_{b=1}^{\left \lfloor \frac{m}{p} \right \rfloor}\sum_{d|gcd(a,b)}\mu(d)$


$\sum_{p}\sum_{d=1}^{\left \lfloor \frac{n}{p} \right \rfloor}\mu(d){\left \lfloor \frac{n}{pd} \right \rfloor}{\left \lfloor \frac{m}{pd} \right \rfloor}$


将pd设为T


$\sum_{T=1}^{n}\sum_{p|T}\mu(\frac{T}{p}){\left \lfloor \frac{n}{T} \right \rfloor}{\left \lfloor \frac{m}{T} \right \rfloor}$


$\sum_{T=1}^{n}f(T){\left \lfloor \frac{n}{T} \right \rfloor}{\left \lfloor \frac{m}{T} \right \rfloor}$


其实暴力求f(T)是O(质数个数\*调和级数\*n)$\approx$O(n)


考虑线性筛f


①:$f(\prod p_i^{k_i})=\sum_{p|\prod p_i^{k_i}}\mu(\frac{\prod p_i^{k_i}}{p})=k*(-1)^{k-1}$


②:$f(pq)=f(p\prod p_i^{k_i})=(k+1)*(-1)^k=(-1)^k-k*(-1)^{k-1}=\mu(q)-f(q)$


③:$f(p^kq)=\sum_{a|p^kq}\mu(\frac{p^kq}{a})$,只有当a=p,k=2时$\mu(\frac{p^kq}{a})$才有值,为$\mu(pq)$


---

## 作者：zh_dou (赞：10)

~~袁野的gcd~~  
#### 首先可以肯定的是这是一道数论题

所以题目就是: $\sum_{i=1}^N \sum_{j=1}^M [gcd(i,j)\in prime]$

接下来就可以愉快的推式子了~   

首先可以按套路枚举$prime$和$gcd$   

$\sum_{p \in prime}\sum_{i=1}^N\sum_{j=1}^M[gcd(i,j)=p]$   

所以我们显然可以将$i$和$j$ 同时除以 $p$,得到
$\sum_{p\in prime}\sum_{i=1}^{N}\sum_{j=1}^{M}[gcd(\frac ip,\frac jp)=1]$   

即等价于  
$\sum_{p\in prime}\sum_{i=1}^{\frac Np}\sum_{j=1}^{\frac Mp} [gcd(i,j)=1]$ 

到了这里,我们发现对于$[gcd(i,j)=1]$ 我们可以根据莫比乌斯函数的定义 $\sum_{d\mid n}\mu(d)\ =[n=1]$ 来进行替换，即

$\sum_{p \in prime}\sum_{i=1}^{\frac Np}\sum_{j=1}^{\frac Mp}\sum_{d\mid i,d\mid j} \mu(d)$  

我们可以按照套路将 $d$ 提前,(这里我们默认$N\le M$)

$\sum_{p \in prime}\sum_{d=1}^{\frac Np}\mu(d)\sum_{i=1}^{\frac Np}[d\mid i]\sum_{j=1}^{\frac Mp}[d\mid j]$

然后我们可以发现后面那两个 $\sum$ 可以用整除分块搞,即 

$\sum_{p \in prime}\sum_{d=1}^{\frac Np}\mu(d)\lfloor\frac N{dp}\rfloor\lfloor\frac M{dp}\rfloor$  

此时,我们应用一个小技巧,将上式中的$dp$换成$Q$~~(或称刘琛薛坷佳崔家贺)~~:

$\sum_{Q=1}^N \sum_{p \in prime}\mu(\frac Qp)\lfloor\frac N{Q}\rfloor\lfloor\frac M{Q}\rfloor$

对于 $\sum_{p \in prime}\mu(\frac Qp)\lfloor\frac N{Q}\rfloor\lfloor\frac M{Q}\rfloor$ ,我们可以用线性筛进行预处理 ,即在筛出 $\varphi$ 后枚举。所以在维护前缀和后就可以对于每一个询问 $O(1)$ 回答啦~

$\mathcal{Code:}$

```cpp
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
#define N 10000010
#define debug cout<<__LINE__<<" "<<__FUNCTION__<<"\n"
inline int read(){
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return x;
}
void put(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) put(x/10);
    putchar((x%10)+48);
}
int prime[N>>2],n,m,cnt;
bool ispri[N];
int mu[N],num[N];
inline void pri(){
    register int i,j;
    for(i=2;i<=N-10;i++){
        if(!ispri[i]){
            prime[++cnt]=i;
            mu[i]=-1;
        }
        for(j=1;j<=cnt&&(i*prime[j]<=N-10);j++){
            if(i*prime[j]<=N-10) ispri[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }else{
                mu[i*prime[j]]=-mu[i];
            }
        }
    }
    int res;
    for(i=1;i<=cnt;i++){
        res=1;
        for(j=prime[i];j<=N-10;j+=prime[i],res++){
            num[j]+=mu[res];
        }
    }
    for(i=2;i<=N-10;i++) num[i]+=num[i-1];
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
    mu[1]=1;
    pri();
    int T=read(),l,r;
    long long ans = 0;
    while(T--){
        n=read();m=read();ans=0;
        if(n>m) swap(n,m);
        for(l=1,r;l<=n;l=r+1){
            r=min(n/(n/l),m/(m/l));
            ans+=(long long)(num[r]-num[l-1])*(n/l)*(m/l);
        }
        put(ans);putchar('\n');
    }
//	fclose(stdin);
//	fclose(stdout);
    return 0;
}
```


---

## 作者：ShuYuMo (赞：6)

即求：

$$\sum_{i=1}^{N}\limits{\sum_{j=1}^{M}\limits{[\text{gcd}(i, j)\in \text P]}}$$
其中$\text P$为质数集。

推导过程如下：

$$\sum_{i=1}^{N}\limits{\sum_{j=1}^{M}\limits{[\text{gcd}(i, j)\in \text P]}}$$
$$\sum_{p \in \text{P}}\limits{\sum_{i=1}^{N}\limits{\sum_{j=1}^{M}\limits{[\text{gcd}(i, j) = p]}}}$$
$$\sum_{p \in \text{P}}\limits{\sum_{i=1}^{\lfloor \frac{N}{p} \rfloor}\limits{\sum_{j=1}^{\lfloor \frac{M}{p} \rfloor}\limits{[\text{gcd}(i, j) = 1]}}}$$
$$\sum_{p \in \text{P}}\limits{\sum_{i=1}^{\lfloor \frac{N}{p} \rfloor}\limits{\sum_{j=1}^{\lfloor \frac{M}{p} \rfloor}\limits{\sum_{d|i, d|j}\limits{\mu(d)}}}}$$
$$\sum_{p \in \text{P}}\limits{\sum_{d=1}^{\frac{\text{min}(N, M)}{p}}\limits{\mu(d) \times \lfloor \frac{N}{pd} \rfloor \lfloor \frac{M}{pd} \rfloor}}$$

设$t = pd$：
$$\sum_{p \in \text{P}}\limits{\sum_{d=1}^{\frac{\text{min}(N, M)}{p}}\limits{\mu(d) \times \lfloor \frac{N}{t} \rfloor \lfloor \frac{M}{t} \rfloor}}$$

$$\sum_{t=1}^{\text{min}(N, M)}\limits{\lfloor \frac{N}{t} \rfloor \lfloor \frac{M}{t} \rfloor \sum_{d \in \text{P},d|t}\limits{\mu(\frac{t}{d})}}$$

设
$$F(x)=\sum_{d \in \text{P},d|x}\limits{\mu(\frac{x}{d})}$$

可以看出， 可以使用数论分块解决问题，数论分块的要求就是函数$F(x)$可以求出前缀和。只需要求出其前缀和即可。可以考虑枚举每一个质数的倍数。
```cpp
void euler1(int n){
    for(int i = 1;i <= tot;i++){
        for(int j = prime[i];j <= n;j += prime[i]){
            F[j] += mu[j / prime[i]];
        }
    }
}
```


# 注意
预处理$\mu(x)$时，**一定记住**给$\mu(1)$**赋值**为$1$。

# code
```cpp


int prime[_];
int not_prime[_], tot = 0;
int mu[_];
void euler0(int n){
	mu[1] = 1;
    for(int i = 2;i <= n;i++){
        if(!not_prime[i]) prime[++tot] = i, mu[i] = -1;
        for(int j = 1;j <= tot && prime[j] * i <= n;j++){
            not_prime[prime[j] * i] = 1;
            if(i % prime[j] != 0) mu[i * prime[j]] = -mu[i];
            else { mu[prime[j] * i] = 0; break; }
        }
    }
}
int F[_];
void euler1(int n){
    for(int i = 1;i <= tot;i++){
        for(int j = prime[i];j <= n;j += prime[i]){
            F[j] += mu[j / prime[i]];
        }
    }
}
signed main()
{
#ifdef LOCAL_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    clock_t c1 = clock();
    euler0(1e7 + 10); euler1(1e7 + 10);
    for(int i = 1;i <= int(1e7 + 10);i++) F[i] += F[i - 1];
//    for(int i = 1e7;i <= int(1e7 + 10);i++) printf("%d%c", F[i], " \n"[i == 20]);
    int T = read();
    while(T--){
        int N = read(), M = read(), _n = min(N, M);
        long long  ans = 0;
        for(int i = 1;i <= _n;){
            int L = i, x0 = N / L, x1 = M / L;
            int R = min(N / x0, M / x1);
            ans += 1LL * (x0 *1ll* x1) * (F[R] - F[L - 1]);

            i = R + 1;
        }
        printf("%lld\n", ans);
    }
    std::cerr << "\n\nTime:  " << clock() - c1 << "  ms" << std::endl;
	return 0;
}
```

---

## 作者：derta (赞：4)

莫比乌斯反演其他题解已经讲的很清楚了，但其实
$$f(n)=\sum_{d|n,d\in\mathbb{P}}\mu(\frac{n}{d})$$
是珂以线性筛的

分类讨论：
- $n=1$，$f(n)=0$
- $n \in \mathbb{P}$，$f(n)=\mu(\dfrac{n}{n})=1$
- 否则，设 $n=ij$，其中 $j$ 为 $n$ 的最小质因子（想想线性筛）
  - $i \operatorname{mod} j=0$，除了 $d=j$ 时，$d$ 都有重复的质因子，$f(n)=\mu(\dfrac{n}{j})=\mu(i)$
  - 否则，$f(n)=(\sum_{d|i,d\in\mathbb{P}}\mu(\dfrac{ij}{d}))+\mu(\dfrac{ij}{j})=-f(i)+\mu(i)$
  
数组意义：

```cpp
Prime[i]：第i个质数
size：目前筛到的质数数量
mark[i]：i是否为合数
mu[i]：莫比乌斯函数
sum[i]：f(1)+f(2)+...+f(n)
```

线性筛代码：

```cpp
void sieve(int n) {
	mark[1] = true; //1不是质数 
	mu[1] = 1;
	//这里把f(n)去掉，只剩sum(n)，可以省去一个数组 
//	sum[1] = 0; //情况1，由于全局变量自动初始化为0，故不必赋值 
	for(int i = 2; i <= n; ++i) {
		if(mark[i] == false) {
			Prime[size++] = i; //加入质数表 
			sum[i] = 1; //情况2 
			mu[i] = -1;
		}
		for(int j = 0; j < size && i*Prime[j] <= n; ++j) {
			mark[i*Prime[j]] = true; //筛掉 
			if(i%Prime[j] == 0) {
				sum[i*Prime[j]] = mu[i]; //情况3
				break;
			}
			mu[i*Prime[j]] = -mu[i];
			sum[i*Prime[j]] = -sum[i] + mu[i]; //情况4 
		}
	}
	for(int i = 1; i <= n; ++i) //前缀和 
		sum[i] += sum[i - 1];
}
```

---

## 作者：szr666 (赞：4)

我这里推荐一下[我的博客](https://www.luogu.org/blog/szr666--blog/)

在博客里观看更美观哦~

[题目](https://www.luogu.org/problemnew/show/P2257)
------------


------------

华丽的分割线
# 解析

### 前置技能

##### 狄利克雷卷积

我们把定义在整数集上的函数成为数论函数,对于两个数论函数

$f,g$它们的狄利克雷卷积为$\sum\limits_{d\mid n}f(d)*g(\frac{n}{d}) $,简记为$f*g$


##### 莫比乌斯函数

$\mu(n)=\begin{cases}1\qquad \ \ n=1 \\ (-1)^k \ \ n=p_1*p_2*...\ *p_k \\ 0 \ \ \qquad else\end{cases}  $

也就是说,将$n$分解质因数,含有平方因子则$\mu(n)=0$，

否则有奇数个质因数为$-1$,偶数个为$1$.有这样一个结论：

$\sum\limits_{d\mid n}\mu(d)=[n==1] $,其中当$n=1$时,$[n==1]=1$否则为$0$

我们来证明一下,当$n=1$时,$\mu(1)=1$,显然成立

否则把$n$质因数分解,从中选取若干个因数,若一个数超过两次,

则值为$0$,无需考虑,现在考虑选取不同的质因数,不选则为$1$,

也就是$C^0_n$，选一个总和为$-C^1_n$,直到$C^n_n$,且正负号交替

根据二项式定理,得$C^0_n-C^1_n+C^2_n...=(-1+1)^n=0$,证毕

我们设$l(n)$为不变函数,即$l(n)=1$,设$\varepsilon(n)=[n==1]$

$\varepsilon(n)$称为单位元,因为任意一个数论函数$f$,有$f*\varepsilon=f$

则上述式子表示为$\mu*l=\varepsilon$,这个结论很重要

##### 积性函数

根据莫比乌斯函数定义,当$n\in prime$时,$\mu(n)=-1$,

当$gcd(n,m)=1$时,$\mu(nm)=\mu(n)*\mu(m)$

类似有这样性质的函数称为积性函数,可用线性筛求出

### 莫比乌斯反演

设$F(n)=\sum\limits_{d\mid n}f(d)$,则$f(n)=\sum\limits_{d\mid n}\mu(d)F(\frac{n}{d})$

证明：$F=l*f$,则$F*\mu=l*\mu*f$,所以$f=\mu*F$,证毕

还有一种形式,设$F(n)=\sum\limits_{n\mid d}f(d)$,则$f(n)=\sum\limits_{n\mid d}\mu(\frac{d}{n})F(d)$

### 本题解法

说了这么多,此题就是求$\sum\limits_{p\in prime}^{min(M,N)}\sum\limits_{i=1}^N\sum\limits_{j=1}^M[gcd(i,j)==p]$

对于此类题,设$f(n)=\sum\limits_{i=1}^N\sum\limits_{j=1}^M[gcd(i,j)==n]$，

$F(n)=\sum\limits_{n\mid d}f(d)$,则$F(n)$表示两个都是$n$的倍数的数对的个数

则$F(n)=\lfloor\frac{N}{n}\rfloor*\lfloor\frac{M}{n}\rfloor$,所以原式为$\sum\limits_{p\in prime}^{min(M,N)}f(p)$

根据反演公式,$f(n)=\sum\limits_{n\mid d}\mu(\frac{d}{n})F(d)$

原式$=\sum\limits_{p\in prime}^{min(M,N)}\sum\limits_{p\mid d}\mu(\frac{d}{p})F(d)$ 设$d'=\frac{d}{p}$ 则

原式$=\sum\limits_{p\in prime}^{min(M,N)}\sum\limits_{p\mid d}\mu(d')F(d'p)$,设$T=d'p$则

原式$=\sum\limits_{T=1}^{min(M,N)}\sum\limits_{p\mid T,p\in prime}\mu(\frac{T}{p})F(T)$,这里调换了枚举顺序

原式$=\sum\limits_{T=1}^{min(M,N)}F(T)\sum\limits_{p\mid T,p\in prime}\mu(\frac{T}{p})$,后者可用线性筛筛出

原式$=\sum\limits_{T=1}^{min(M,N)}\lfloor\frac{N}{n}\rfloor*\lfloor\frac{M}{n}\rfloor*(\sum\limits_{p\mid T,p\in prime}\mu(\frac{T}{p}))$

前者可用数论分块$O(\sqrt n)$求出,后者$O(1)$查询,

### 预处理

设$S(T)=\sum\limits_{p\mid T,p\in prime}\mu(\frac{T}{p})$,则对于一个素数$p$,枚举$i$

则$S(i*p)+=\mu(i)$,用类似埃氏筛的方法$O(nlogn)$算出$S$

并计算$S$的前缀和,总复杂度为$O(nlogn+T\sqrt n)$

关于数论分块,请看[这里](https://www.luogu.org/blog/szr666--blog/ti-gao-xing-xuan-zhuan-ti-shuo-lun-fen-kuai-p2261-cqoi2007-yu-shu)

# 代码

```cpp
#include<cstdio>
#define ll long long
using namespace std;
const int N=10010000;
int prime[N];
bool is_prime[N];
int mu[N],ptot;
ll sum[N];
void getprime(int n)
{
	ptot=0;
	is_prime[1]=1;
	mu[1]=1;
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(is_prime[i]==0)
		{
			ptot++;
			prime[ptot]=i;
			mu[i]=-1;
		}
		for(j=1;j<=ptot&&i*prime[j]<=n;j++)
		{
			is_prime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				break;
			}
			else
			{
				mu[i*prime[j]]=-mu[i];
			}
		}
	}
	for(j=1;j<=ptot;j++)
	{
		for(i=1;i*prime[j]<=n;i++)
		{
			sum[i*prime[j]]+=mu[i];
		}
	}
	for(i=1;i<=n;i++)
	{
		sum[i]+=sum[i-1];
	}
}
void read(int &x)
{
	x=0;
	int f;
	f=1;
	char c;
	c=getchar();
	while((c<'0'||c>'9')&&c!='-')
	{
		c=getchar();
	}
	if(c=='-')
	{
		f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	x=x*f;
}
inline int min(int x1,int x2)
{
	return x1<x2 ? x1 : x2;
}
int main()
{
	int t,ti,m,n,l,r;
	ll ans;
	read(t);
	getprime(10000100);
	for(ti=1;ti<=t;ti++)
	{
		read(n);
		read(m);
		ans=0;
		for(l=1;l<=min(m,n);l=r+1)
		{
			r=min(m/(m/l),n/(n/l));
			ans+=(sum[r]-sum[l-1])*(ll)(n/l)*(ll)(m/l);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：lx_zjk (赞：3)

~~这个屑来水篇题解~~

# 题目意思

$$\sum_{p \in prime}\sum_{i=1}^n\sum_{j=1}^{m}[\gcd(i,j)=p]$$


# 题解
开心的颓柿子


$$
\sum_{p\in prime} \sum_{i=1}^{\lfloor \frac{n}{p} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{p} \rfloor} [\gcd(i,j)=1]
$$
这里有常见的技巧
$$
\sum_{k|n}\mu(k)=[n=1]
$$
所以
$$
[\gcd(i,j)=1] = \sum_{k|\gcd(i,j)} \mu(k)
$$
代入公式
$$
\sum_{p \in prime}\sum_{i=1}^{\lfloor \frac{n}{p} \rfloor}\sum_{j=1}^{\lfloor \frac{m}{p} \rfloor}\sum_{k | \gcd(i,j)}  \mu(k)
$$

$$
\sum_{p \in prime} \sum_{d=1}^{\min(n,m)} \mu(d) \sum_{d|i}^{\lfloor \frac{n}{p} \rfloor} \sum_{d|j}^{\lfloor \frac{m}{p} \rfloor}1
$$

$$
\sum_{p \in prime} \sum_{d=1}^{\min(n,m)} \mu(d) \lfloor \frac{n}{pd}\rfloor \lfloor \frac{m}{pd}\rfloor
$$

$$
\sum_{T=1}^{\min(n, m)} \sum_{p \in prime} \mu(\frac{T}{p}) \lfloor\frac{n}{T}\rfloor \lfloor\frac{m}{T}\rfloor
$$

$$
\sum_{T=1}^{\min(n, m)}\lfloor\frac{n}{T}\rfloor \lfloor\frac{m}{T}\rfloor \sum_{p \in prime,p|T} \mu(\frac{T}{p})
$$

后面那个可以预处理，总时间复杂度为$\Theta(T\sqrt n))$

---

## 作者：chihik (赞：2)

显然，题目求的是：

$$\sum_{p\in prime}\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)=p]$$

$$\sum_{p \in prime}\sum_{i=1}^{ \lfloor\frac{n}{p}\rfloor}\sum_{j=1}^{\lfloor \frac{m}{p} \rfloor}[gcd(i,j)=1] $$

有一个与莫比乌斯函数有关的性质：$\sum_{d | n}\mu(d)=[n=1]$

$$\sum_{p \in prime}\sum_{i=1}^{ \lfloor\frac{n}{p}\rfloor}\sum_{j=1}^{\lfloor \frac{m}{p} \rfloor}\sum_{k|gcd(i,j)}\mu(k)$$

将 $k$ 往前移，然后是一个非常经典的式子了

$$\sum_{p \in prime}\sum_{k=1}^{min(\lfloor \frac{n}{p} \rfloor,\lfloor \frac{m}{p} \rfloor)}\mu(k)\lfloor \frac{n}{kp} \rfloor \lfloor \frac{m}{kp} \rfloor$$

令$T=kp$,将它放到前面枚举：
$$\sum_{T=1}^{min(n,m)}\lfloor \frac{n}{T} \rfloor \lfloor \frac{m}{T} \rfloor\sum_{p|T,p \in prime} \mu(\frac{T}{p}) $$

前面的可以用数轮分块解决，后面的可以将每个数对它的倍数的贡献计算，最后做一遍前缀和也可以分块了。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 10000000;
int t , a , b , d;

int k , prime[ MAXN + 5 ] , mu[ MAXN + 5 ];
long long f[ MAXN + 5 ];
bool vis[ MAXN + 5 ];

void sieve( ) {
	mu[ 1 ] = 1;
	for( int i = 2 ; i <= MAXN ; i ++ ) {
		if( !vis[ i ] ) {
			prime[ ++ k ] = i;
			mu[ i ] = -1;
		}
		for( int j = 1 ; j <= k && 1ll * i * prime[ j ] <= MAXN ; j ++ ) {
			vis[ i * prime[ j ] ] = 1;
			if( i % prime[ j ] == 0 ) break;
            mu[ i * prime[ j ] ] = -mu[ i ];
            
		}
	}
}
void Init( ) {
    sieve( );
    for( int j = 1 ; j <= k ; j ++ )
       for( int i = 1 ; 1ll * i * prime[ j ] <= MAXN ; i ++ )
               f[ i * prime[ j ] ] += mu[ i ];
    for( int i = 2 ; i <= MAXN ; i ++ )
        f[ i ] += f[ i - 1 ];
}

long long solve( int n , int m ) {
    long long Ans = 0;
    for( int l = 1 , r ; l <= min( n , m ) ; l = r + 1 ) {
        r = min( n / ( n / l ) , m / ( m / l ) );
        Ans += 1ll * ( n / l ) * ( m / l ) *  ( f[ r ] - f[ l - 1 ] );
    }
    return Ans;
}

int main( ) {
	Init( );
	scanf("%d",&t);
	while( t -- ) {
		scanf("%d %d",&a,&b);
		printf("%lld\n",solve( a , b ));
	}
	return 0;
}
```

---

## 作者：wasa855 (赞：2)

首先安利我的博客对Mobius反演和整除分块的介绍：[数论](https://www.luogu.org/blog/70780/shuo-lun)。   

解题思路：   
首先套路地设$f(d)=\sum_{i=1}^{n}\sum_{i=1}^{m}[gcd(i,j)=d]$，   
$F(n)=\sum_{n\mid d}f(d)=\lfloor \frac{N}{n} \rfloor \times \lfloor \frac{M}{n} \rfloor$  
那么由莫比乌斯反演：$f(n)=\sum_{n|d}\mu(\frac{d}{n})F(d)$

之后便是推柿子的过程了：   
可见原题相当于求$Ans=\sum_{i=1}^{n}\sum_{i=1}^{m}[gcd(i,j)=prim]$   
改为枚举素数可得$Ans=\sum_{p\in prim}\sum_{i=1}^{n}\sum_{i=1}^{m}[gcd(i,j)=p]$   
代入$f$函数$=\sum_{p\in prim}f(p)$   
代入反演结果$=\sum_{p\in prim}\sum_{p|d}\mu(\frac{d}{p})F(d)$   
改为枚举$\frac{d}{p}$：   
$Ans=\sum_{p\in prim}\sum_{d}^{min(\lfloor \frac{n}{p} \rfloor,\lfloor \frac{m}{p} \rfloor)}\mu(d)F(dp)$   
$=\sum_{p\in prim}\sum_{d}^{min(\lfloor \frac{n}{p} \rfloor,\lfloor \frac{m}{p} \rfloor)}\mu(d) \times \lfloor \frac{N}{dp} \rfloor \times \lfloor \frac{M}{dp} \rfloor$   
设$dp=T$   
$Ans=\sum_{p\in prim}\sum_{d}^{min(\lfloor \frac{n}{p} \rfloor,\lfloor \frac{m}{p} \rfloor)}\mu(\frac{T}{p}) \times \lfloor \frac{N}{T} \rfloor \times \lfloor \frac{M}{T} \rfloor$   
$=\sum_{T=1}^{min(n,m)}\sum_{p\in prim,p|T}\mu(\frac{T}{p}) \times \lfloor \frac{N}{T} \rfloor \times \lfloor \frac{M}{T} \rfloor$    
$=\sum_{T=1}^{min(n,m)}(\lfloor \frac{N}{T} \rfloor \times \lfloor \frac{M}{T} \rfloor) \times \sum_{p\in prim,p|T}\mu(\frac{T}{p})$   
最后，套用整除分块就可以了

#### 在代码之前，祝大家NOIP/NOI/省选 2019 RP++
代码：   
//sum即为$\sum_{p\in prim,p|T}\mu(\frac{T}{p})$的前缀和
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int prime[10000005];
int mu[10000005];
ll f[10000005];
ll sum[10000005];
bool vis[10000005];
int cnt;
void init()
{
    mu[1]=1;
    for(int i=2;i<=10000000;i++)
    {
        if(vis[i]==false)
        {
            mu[i]=-1;
            prime[++cnt]=i;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=10000000;j++)
        {
            vis[i*prime[j]]=true;
            if(i%prime[j]==0)
            {
                break;
            }
            mu[i*prime[j]]=-mu[i];
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        for(int j=1;j*prime[i]<=10000000;j++)
        {
            f[j*prime[i]]+=mu[j];
        }
    }
    for(int i=1;i<=10000000;i++)
    {
        sum[i]=sum[i-1]+f[i];
    }
}
ll solve(int a,int b)//运用整除分块
{
    ll ans=0;
    if(a>b)
    {
        swap(a,b);
    }
    for(int l=1,r=0;l<=a;l=r+1)
    {
        r=min(a/(a/l),b/(b/l));
        ans+=(ll)(sum[r]-sum[l-1])*(a/l)*(b/l);
    }
    return ans;
}
signed main()
{
    init();
    int T;
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%lld\n",solve(a,b));
    }
    return 0;
}
```

---

## 作者：览遍千秋 (赞：1)

## 问题描述

[BZOJ2820](https://www.lydsy.com/JudgeOnline/problem.php?id=2820)

[LG2257](https://www.luogu.com.cn/problem/P2257)

---

## 题解

求 $\sum\limits_{i=1}^{n}{\sum\limits_{j=1}^{m}{[gcd(i,j)==p]}}$ ，其中 $p$为质数，$n<m$ 。

考虑不要求 $gcd(i,j)$ 为质数时的做法：

可以转化为

$$\sum\limits_{g=1}^{n}{g \times \sum\limits_{i=1}^{\lfloor \frac{n}{g} \rfloor}{\sum\limits_{j=1}^{\lfloor \frac{m}{g} \rfloor}{[gcd(i,j)==1]}}}$$

根据狄利克雷卷积和莫比乌斯函数的性质，得

$$\sum\limits_{g=1}^{n}{g \times \sum\limits_{i=1}^{\lfloor \frac{n}{g} \rfloor}{\sum\limits_{j=1}^{\lfloor \frac{m}{g} \rfloor}{\sum\limits_{x|gcd(i,j)}{\mu(x)}}}}$$

转化为枚举倍数，得

$$\sum\limits_{g=1}^{n}{g \times \sum\limits_{x=1}^{\lfloor \frac{n}{g} \rfloor}{\sum\limits_{i=1}^{\lfloor \frac{n}{gx} \rfloor}{\sum\limits_{j=1}^{\lfloor \frac{m}{gx} \rfloor}{1}}}}$$

即

$$\sum\limits_{g=1}^{n}{g \times \sum\limits_{x=1}^{\lfloor \frac{n}{g} \rfloor}{\mu(x) \lfloor \frac{n}{gx} \rfloor \lfloor \frac{m}{gx} \rfloor}}$$

接下来考虑 $g$ 要是质数怎么办

构造函数 $f(x)$,$f(x)=\begin{cases}1&x \in \mathbb{P}\\0&x \notin \mathbb{P}\end{cases}$，其中 $\mathbb{P}$ 为质数集合。

令 $D=gx$ ，则要求的就是

$$\sum\limits_{D=1}^{n}{\lfloor \frac{n}{D} \rfloor \lfloor \frac{m}{D} \rfloor \times \sum\limits_{g|D}{f(g)\mu(\frac{D}{g})}}$$

发现右边的 $\sum\limits_{g|D}{f(g)\mu(\frac{D}{g})}$ 是狄利克雷卷积的形式。

设 $h(x)=f*\mu$ ，则可以通过枚举倍数的时间，在 $O(k \ln n)$ 的时间复杂度求出 $h(x)$ ，其中 $k$ 为 $[1,n]$ 中质数个数，约等于 $\frac{n}{\ln n}$ ，于是约等于 $O(n)$ 。

得到最终答案式子为

$$\sum\limits_{D=1}^{n}{h(D)\lfloor \frac{n}{D} \rfloor \lfloor \frac{m}{D} \rfloor}$$

然后就可以整除分块了。

---

## $\mathrm{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=10000000;

int p[maxn+7],pr[maxn+7],miu[maxn+7];
int h[maxn+7],T,tot;

long long s[maxn+7];

void preprocess(void){
	miu[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!p[i]) p[i]=i,pr[++tot]=i,miu[i]=-1;
		for(int j=1;j<=tot;j++){
			if((long long)i*pr[j]>maxn||pr[j]>p[i]) break;
			p[i*pr[j]]=pr[j];
			if(i%pr[j]) miu[i*pr[j]]=-miu[i];
			else miu[i*pr[j]]=0;
		}
	}
	for(int i=1;i<=tot;i++){
		for(int j=1;(long long)pr[i]*j<=maxn;j++){
			h[pr[i]*j]+=miu[j];
		}
	}
	for(int i=1;i<=maxn;i++) s[i]=s[i-1]+(long long)h[i];
}

void Init(void){
	scanf("%d",&T);
}

long long calc(int x,int y){
	if(x>y) swap(x,y);
	long long res(0);
	for( int l=1,r;l<=x;l=r+1){
		r=min(x/(x/l),y/(y/l));
		res+=(long long)(s[r]-s[l-1])*(long long)(x/l)*(y/l);
	}
	return res;
}

void Work(void){
	preprocess();
	while(T--){
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%lld\n",calc(x,y));
	}
}

signed main(){
	Init();
	Work();
}
```

---

## 作者：GoldenPotato137 (赞：1)

蒟蒻博客：[QwQ](https://www.cnblogs.com/GoldenPotato/p/10302839.html)

---
# Solution

~~推到自闭，我好菜啊~~

显然，这题让我们求：
$\large \sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)\in prime]$

根据套路，我们可以把判断是否为质数改为枚举这个质数,有：

为了方便枚举，我们在这里假设有$m>n$
$\large \sum_{i=1}^{n}\sum_{j=1}^{m}\sum_{k\in prime}^{n}[gcd(i,j)= k]$

显然，要让$gcd(i,j)=k$，必须要有$i,j$均为$k$的倍数，因此有：
$\large \sum_{k\in prime}^{n}\sum_{i=1}^{n/k}\sum_{j=1}^{m/k}[gcd(i,j)= 1]$ (在这里除号指向下取整)

根据套路，我们要去掉这里的判断符号。
因为我们的莫比乌斯函数有这个性质：$[x=1]=\sum_{d|x}\mu(d)$，我们这里可以直接把$gcd(i,j)$作为$x$带入这个性质里面，有：

$\large \sum_{k\in prime}^{n}\sum_{i=1}^{n/k}\sum_{j=1}^{m/k}\sum_{d|gcd(i,j)}\mu(d)$

然后根据套路，我们直接枚举这里的$d$，有：

$\large \sum_{k\in prime}^{n}\sum_{i=1}^{n/k}\sum_{j=1}^{m/k}\sum_{d=1}^{n/k}μ(d)[d|gcd(i,j)]$ （因为前面$i,j$中最小的是$n/k$,所以说我们这里$d$的最大值也为$n/k$）


然后我们这里的$\sum_{d=1}^{n/k}$显然可以直接往前提


$\large \sum_{k\in prime}^{n}\sum_{d=1}^{n/k}\sum_{i=1}^{n/k}\sum_{j=1}^{m/k}μ(d)[d|gcd(i,j)]$

这时候$\mu(d)$显然也可以往前提

$\large \sum_{k\in prime}^{n}\sum_{d=1}^{n/k}μ(d)\sum_{i=1}^{n/k}\sum_{j=1}^{m/k}[d|gcd(i,j)]$

这时候，我们可以发现后面那个判断式为1当且仅当$i,j$均为$d$的倍数，所以我们可以直接把那两个$\sum$简化掉

$\large \sum_{k\in prime}^{n}\sum_{d=1}^{n/k}μ(d)\frac{n}{k*d}\frac{m}{k*d}$

这时候，我们已经可以在$O(logn*\sqrt n)$的时间内算一次答案了（这里的$log$为质数个数），很可惜，这样的复杂度并不能通过这一题。

.

事实上，我们还有一个常见的套路来优化这里：
我们可以设$T=k*d$，于是我们有：

$\large \sum_{k\in prime}^{n}\sum_{d=1}^{n/k}μ(\frac{T}{k})\frac{n}{T}\frac{m}{T}$

然后可以把后面那个和式提前，枚举T，有：

$\large \sum_{T=1}^{n}\frac{n}{T}\frac{m}{T}\sum_{(k\in prime,k|T)}μ(\frac{T}{k})$


搞定，到这里为止，我们一切东西都可以算了。

前面的$\frac{n}{T}\frac{m}{T}$可以整除分块来搞，后面那个$μ$可以在$O(n)$的时间预处理，然后算的时候前缀和一搞就ok啦。

如何预处理呢？我们可以考虑这样做：我们先枚举每一个质数$x$，再考虑这个$x$对它的整数倍$t$的贡献为$\mu(t)$

酱紫，我们就可以在$O(\sqrt n)$的时间内处理每一个询问了。

完结撒花✿✿ヽ(°▽°)ノ✿

---
# Code
```cpp
//Luogu P2257 YY的GCD
//Jan,22ed,2019
//莫比乌斯反演
#include<iostream>
#include<cstdio>
using namespace std;
long long read()
{
	long long x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=10000000+1000;
const int M=10000000;
int mu[N],prime[N],cnt_p;
bool noPrime[N];
void GetPrime(int n)
{
	mu[1]=1;
	noPrime[1]=true;
	for(int i=2;i<=n;i++)
	{
		if(noPrime[i]==false)
			prime[++cnt_p]=i,mu[i]=-1;
		for(int j=1;j<=cnt_p and i*prime[j]<=n;j++)
		{
			noPrime[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=mu[i]*mu[prime[j]];
		}
	}
}
long long f[N],pre_f[N];
int main()
{
	GetPrime(M);
	for(int i=1;i<=cnt_p;i++)
		for(int j=1;prime[i]*j<=M;j++)
			f[prime[i]*j]+=mu[j];
	for(int i=1;i<=M;i++)
		pre_f[i]=pre_f[i-1]+f[i];
	
	int T=read();
	for(;T>0;T--)
	{
		long long n=read(),m=read();
		if(n>m) swap(n,m);
		
		int l=1,r=1;
		long long ans=0;
		for(;l<=n;l=r+1)
		{
			r=min(n/(n/l),m/(m/l));
			ans+=(pre_f[r]-pre_f[l-1])*(n/l)*(m/l);
		}
		
		printf("%lld\n",ans);
	}
	return 0;
}

```














---

## 作者：数学系 (赞：1)

莫比乌斯反演  
公式已经被楼上楼下各位神犇推导的很清楚了，不懂的话可以参考PoPoQQQ同学的PPT，把莫比乌斯反演讲的很清楚。


![莫比乌斯反演](https://wkretype.bdimg.com/retype/zoom/bd477a1955270722192ef754?pn=18&o=jpg_6&md5sum=ef1f65613e8646a86acd58585e0b1a1c&sign=46bbc2128f&png=660819-687205&jpg=2180711-2314307)


![莫比乌斯反演](https://wkretype.bdimg.com/retype/zoom/bd477a1955270722192ef754?pn=19&o=jpg_6&md5sum=ef1f65613e8646a86acd58585e0b1a1c&sign=46bbc2128f&png=687206-713986&jpg=2314308-2456461)

这里我就仅送上一份比较简单的代码，希望帮助更多人理解。  
P.S.为什么开O2优化：  
为了保证代码简洁，使更多人看懂，没有过多的优化，所以时间复杂度稍高，不开O2会T几个点。  




```cpp
#pragma GCC optimize("O2")
#include <iostream>
#include <cstdio>

using namespace std;

const long long maxn=10000007;

long long u[maxn];
long long sum_u_prime[maxn];

bool notprime[maxn]={};
long long prime[maxn]={};
long long primenum=0;

long long prefix[maxn]={};

int p;

long long min(long long a,long long b)
{
	return a<b?a:b;
}

void swap(long long &a,long long &b)
{
	long long tmp=a;
	a=b;
	b=tmp;
	return;
}

void super_Mobius()
{
	u[1]=1;
	for(long long i=2;i<maxn;i++)
	{
		if(!notprime[i])
		{
			prime[++primenum]=i;
			u[i]=-1;
		}
		for(long long j=1;j<=primenum && prime[j]*i<maxn;j++)
		{
			notprime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				u[prime[j]*i]=0;
				break;
			}
			u[prime[j]*i]=-u[i];
		}
	}
	for(long long i=1;i<=primenum;i++)
	{
		p=prime[i];
		for(long long j=1;j*p<maxn;j++)
		    sum_u_prime[j*p]+=u[j];
	}
}

long long T;
long long N,M;

long long solve(long long n,long long m)
{
	long long tot=0,last=0;
	if(m<n)
	    swap(n,m);
	for(long long i=1;i<=n;i=1+last)
	{
		last=min(n/(n/i),m/(m/i));
		tot+=(prefix[last]-prefix[i-1])*(n/i)*(m/i);
	}
	return tot;
}

int main()
{
	super_Mobius();
	for(long long i=1;i<maxn;i++)
		prefix[i]=prefix[i-1]+sum_u_prime[i];
	scanf("%lld",&T);
	for(long long i=0;i<T;i++)
	{
		scanf("%lld%lld",&N,&M);
		printf("%lld\n",solve(N,M));
	}
	return 0;
}
```


说明：    
u数组：莫比乌斯函数μ    
sum_u_prime数组:储存

```
 ∑  μ(T/p)  
p|T   
```  

的值       
prefix数组：储存sum_u_prime的前缀和    

solve函数：枚举除法的取值。会发现有很多除法的值相同，直接将它们的个数算出来，与除法的值和前缀和相乘，可以大大降低时间复杂度。   
super_Mobius()函数：计算莫比乌斯函数μ和sum_u_prime





---

## 作者：totorato (赞：1)

# 一种弱智的做法

首先，按照最正常不过的 ~~题解~~ 套路将我们要求的东西变形：

$\sum_p{\sum(number\ of \ gcd(a,b)=p)}$

$=\sum_p\sum_{p|d}[number\ of\ d|gcd(a,b)]\mu(\frac{d}{p})$

$=\sum_p\sum_{p|d}\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor\mu(\frac{d}{p})$

$=\sum_{d}(\lfloor \frac{n}{d}\rfloor\lfloor \frac{m}{d}\rfloor\sum_{p|d}\mu(\frac{d}{p}))$

由于$\lfloor\frac{n}{d}\rfloor$、$\lfloor\frac{m}{d}\rfloor$的取值只有$2\sqrt{n}$个，且单调递增，所以$\lfloor \frac{n}{d}\rfloor\lfloor \frac{m}{d}\rfloor$的取值只有$4\sqrt{n}$个。那么我们就可以$O(\sqrt{n})$的复杂度枚举这两个东西的积，然后乘上对应的$\sum_{p|d}\mu(\frac{d}{p})$的和。

所以我们需要预处理$\sum_{p|d}\mu(\frac{d}{p})$和它的前缀和。

预处理的方法有很多，其中一种不弱智的是线性筛这东西，另一种我想到的比较弱智的是非线性筛它(总之复杂度很玄学)。

注意到$f(d)=\sum_{p|d}\mu(\frac{d}{p})$的取值只有在$d$的唯一分解为$p_1p_2\dots p_c$或者$p_1p_2\dots p_x^2\dots p_c$时非零，所以我们不妨枚举所有不含平方因子的数，通过这个求出所有令f值非0的d。这些数的数量大概在$10^6$级别，另外枚举其质因子耗费$O(logn)$的复杂度，所以这么求函数值也不会慢到哪里去。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#define MX 10000001
#define REG register

using namespace std;

typedef long long ll;

int prm[MX],pnum;
int miu[MX],msm[MX],myz[MX],que[MX],tmp[MX],top,tnm;
ll smiu[MX],ssmiu[MX];
char vis[MX];
ll n,m;

void init()
{
	miu[1]=1,myz[1]=1;
	for(REG int i=2;i<MX;i++)
	{
		if(!vis[i])prm[++pnum]=i,miu[i]=-1,myz[i]=i;
		for(REG int j=1;j<=pnum;j++)
		{
			if(i*prm[j]>=MX)break;
			myz[i*prm[j]]=prm[j];
			vis[i*prm[j]]=1;
			if(i%prm[j]==0){miu[i*prm[j]]=0;break;}
			else miu[i*prm[j]]=-miu[i];
		}
	}
	for(REG int i=1;i<MX;i++)if(miu[i])que[++top]=i;
	for(REG int i=1;i<=top;i++)
	{
		REG int now=que[i];tnm=0;
		while(now>1)
		{
			tmp[++tnm]=myz[now];
			now/=myz[now];
		}
		for(REG int j=1;j<=tnm;j++)
		{
			smiu[que[i]]+=miu[que[i]/tmp[j]];
			if((ll)que[i]*(ll)tmp[j]<MX)smiu[que[i]*tmp[j]]+=miu[que[i]];
		}
	}
	for(REG int i=1;i<MX;i++)ssmiu[i]=ssmiu[i-1]+smiu[i];
}

ll calc()
{
	ll ans=0;
	ll p=1,q;
	while(n/p&&m/p)
	{
		q=min(n/(n/p),m/(m/p));
		ans+=(n/p)*(m/p)*(ll)(ssmiu[q]-ssmiu[p-1]);
		p=q+1;
	}
	return ans;
}

int main()
{
	int T;
	init();
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		scanf("%lld%lld",&n,&m);
		printf("%lld\n",calc());
	}
	return 0;
}
```



---

## 作者：kradcigam (赞：1)

由于 Latex 挂了，建议到 Luogu 博客或者 [这里](https://blog.csdn.net/qq_46230164/article/details/105795158) 查看，修正了原文章的错误。


# 前置知识
- [莫比乌斯反演](https://blog.csdn.net/qq_46230164/article/details/105877706)
- [数论分块](https://blog.csdn.net/qq_46230164/article/details/105934495)
$$
\begin{aligned}
&\sum_{p\in prim}\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=p] \\
=& \sum_{p\in prim}\sum_{i=1}^{\lfloor\frac{n}{p}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{p}\rfloor}[\gcd(i,j)=1]\\
=& \sum_{p\in prim}\sum_{i=1}^{\lfloor\frac{n}{p}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{p}\rfloor}\varepsilon(\gcd(i,j)=1)\\
=& \sum_{p\in prim}\sum_{i=1}^{\lfloor\frac{n}{p}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{p}\rfloor}\varepsilon(\gcd(i,j))\\
=& \sum_{p\in prim}\sum_{i=1}^{\lfloor\frac{n}{p}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{p}\rfloor} \sum_{d\mid \gcd(i,j)} \mu(d)\\
=&\sum_{p\in prim}\sum_{p\mid d} \mu(d)\sum_{i=1}^{\lfloor\frac{n}{p}\rfloor}[d\mid i]\sum_{j=1}^{\lfloor\frac{m}{p}\rfloor}[d\mid j]\\
=&\sum_{p\in prim}\sum_{p\mid d} \mu(d) \lfloor \frac{n}{kd} \rfloor\lfloor \frac{m}{kd} \rfloor\\
\end{aligned}
$$
设：

$$f(p)=\sum\limits_{p\mid d} \mu(d)$$

则原式化为：

$$
\begin{aligned}
=&\sum_{p\in prim} f(p)\times \lfloor \frac{n}{kd} \rfloor\lfloor \frac{m}{kd} \rfloor\\\end{aligned}
$$

我们先去预处理 $f$ 函数

```cpp
for(int i=1;i<=cnt;i++)
	for(int j=1;j*prim[i]<N;j++)
		f[j*prim[i]]+=mu[j];
```
就是这里的 $f$ 数组。

之后我们就可以求解了。

我们可以使用数论分块来写这题。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void read(T &FF){
	T RR=1;FF=0;char CH=getchar();
	for(;!isdigit(CH);CH=getchar())if(CH=='-')RR=-1;
	for(;isdigit(CH);CH=getchar())FF=(FF<<1)+(FF<<3)+(CH^48);
	FF*=RR;
}
const int N=1e7+10;
int prim[N],mu[N],sum[N],cnt,k,T,f[N];
bool vis[N];
void init(){
	mu[1]=1;
	for(register int i=2;i<N;i++){
		if(!vis[i]){
			mu[i]=-1;
			prim[++cnt]=i;
		}
		for(register int j=1;j<=cnt&&i*prim[j]<N;j++){
			vis[i*prim[j]]=1;
			if(i%prim[j]==0)break;
			mu[i*prim[j]]=-mu[i];
		}
	}
	for(int i=1;i<=cnt;i++)
		for(int j=1;j*prim[i]<N;j++)
			f[j*prim[i]]+=mu[j];
	for(register int i=1;i<N;i++)sum[i]=sum[i-1]+f[i];
}//莫比乌斯反演的板子
ll calc(int a,int b){
	ll ans=0;
	for(register int l=1,r;l<=min(a,b);l=r+1){
		r=min(a/(a/l),b/(b/l));
		ans+=(1ll*a/l)*(1ll*b/l)*(sum[r]-sum[l-1]);
	}
	return ans;
}
int main(){
	init();
	for(read(T);T--;){
		int x,y;
		read(x);read(y);
		printf("%lld\n",calc(x,y));
	}
	return 0;
}
```

---

## 作者：Accoty_AM (赞：1)

~~感觉自己写的挺短的，就发一下吧~~

## 莫比乌斯反演

一般GCD的题都会设两个函数
$ \begin{cases} F(k)  \\f(k) \end{cases} $

$F(k)$ 表示 $ n \geq x , m \geq y, k | gcd(x, y) $

$ f(k) $ 表示 $ n \geq x, m \geq x, gcd(x, y) = k $ 的数对个数

---

$ f(k) = \sum\limits_{(x,y) = k} 1$

$ F(k)= \lfloor \frac n k \rfloor * \lfloor \frac m k \rfloor = \sum\limits_{k | d}f(d)$

$ ans = \sum\limits_{p \in prime} f(p) = \sum\limits_{p \in prime} \sum\limits_{p | k} \mu(\frac k p) * F(k) $

$ ans = \sum\limits_{p \in prime} \sum\limits_{p | k} \mu(\frac k p) * \lfloor \frac n k \rfloor * \lfloor \frac m k \rfloor $

发现里面都有 $k$ 想办法吧 $k$ 提出来 , 把 $\sum\limits_{p | k} \mu(\frac k p)$ 搞成前缀和

$ ans = \sum\limits_{k = 1}^{min(n,m)} \lfloor \frac n k \rfloor * \lfloor \frac m k \rfloor * \sum\limits_{p \in prime,p|k} \mu(\lfloor \frac k p \rfloor) $

这样 $\lfloor \frac n k \rfloor * \lfloor \frac m k \rfloor$ 可以除法分块

对于 $ \sum\limits_{p \in prime,p|k} \mu(\lfloor \frac k p \rfloor) $，可以在筛出所有素数后处理

时间复杂度 $O(T \sqrt n + n)$

code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#pragma GCC optimize(2)
inline int read(){
	rg char ch = getchar();
	rg int x = 0, f = 0;
	while(! isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
const int N = 1e7 + 5;
int prime[N], mu[N], pre[N], cnt, val[N];
#define ll long long
ll sum[N];
inline void ola(int n){
	mu[1] = 1;
	for(int i = 2; i <= n; ++i){
		if(! pre[i]){
			prime[++cnt] = pre[i] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= cnt && prime[j] * i <= n; ++j){
			pre[i * prime[j]] = prime[j];
			if(prime[j] == pre[i]){ mu[i * prime[j]] = 0; break; }
			mu[i * prime[j]] = -mu[i];
		}
	}
	for(int i = 1; i <= cnt; ++i)
		for(int j = 1; prime[i] * j <= n; ++j)
			val[j * prime[i]] += mu[j];
	for(int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + val[i];
}
inline long long calc(int n, int m){
	ll res = 0;
	for(int l = 1, r, il = min(n, m); l <= il; l = r + 1){
		r = min(n / (n / l), m / (m / l));
		res += (sum[r] - sum[l - 1]) * (n / l) * (m / l);
	}
	return res;
}
//x <= n, y <= m
//f(k) gcd(x,y) == k
//F(k) = \sigma_{k | gcd(x,y)} = (n / k) * (m / k)
//F(k) = \sigma_{k | d} f(d)
//p is primer f(p)
//p is primer \sigma_{p | d} \mu(p / d) 
int T;
int n, m;
signed main(){
	T = read();
	ola(1e7);
	while(T--){
		n = read(), m = read();
		printf("%lld\n", calc(n, m));
	}
	return 0;
} 
```


---

## 作者：西园寺世界 (赞：1)

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+5;
int g[N],mu[N],prime[N],not_prime[N],s[N];
int m,n;
int tot=0;
void init(){
    mu[1]=1;
    n=1e7+2;
    for(int i=2;i<=n;i++){
        if(!not_prime[i]){
            prime[++tot]=i;
            mu[i]=-1;//只有一个质数的mu函数值是-1 
            g[i]=1;
        }
        for(int j=1;prime[j]*i<=n;j++){//现在开始枚举在n以内是质数prime[1->j]i倍数的值 
            not_prime[prime[j]*i]=1;//将这个数标记为合数，进行素数筛 
            if((i%prime[j])==0){//如果i这个数本身就可以被这个质数除尽，那么这个数就拥有两个因子相同的素数乘积 
                mu[prime[j]*i]=0;//这个数的mu函数值是0 
                g[i*prime[j]]=mu[i];
                break;
            }
            else{
                mu[prime[j]*i]=-mu[i];//如果i不能被当前素数整除，那么这个数有几种情况：1、它的值本身就是0，取反后还是0，如果它仅由互不相同的质数相乘，那么这个数乘上之后函数值就要取反 
                g[i*prime[j]]=mu[i]-g[i];
            }
        }
    }
    for(int i=1;i<=n;i++){
        s[i]=s[i-1]+g[i];
    }
}
long long mobiwusi(int n,int m){
    if(n<m)swap(n,m);
    long long re=0;
    int last=0;
    for(int i=1;i<=n;i=last+1){
        last=min(n/(n/i),m/(m/i));
        re+=(long long)(n/i)*(m/i)*(s[last]-s[i-1]);
    }
    return re;
}
int main(){
    int t;
    scanf("%d",&t);
    init();
    while(t--){
        scanf("%d%d",&n,&m);long long ans=mobiwusi(n,m);
        printf("%lld\n",ans);
    }
    return 0;
} 
//防止粘代码，在代码里做了一点小改动，直接交上去会RE的2333,各位加油！
```

---

## 作者：huangzirui (赞：0)

题意：

求

$$\sum\limits_{i=1}^n\sum_{j=1}^m[\ \text{gcd}(i,j)\text{ 是质数 }]$$ 

$n,m\leq 10^7\ \ \ $ 数据组数 $T \leq 10^4$

---

### 1.阅读须知

前置知识：

Dirichlet 卷积；Mobius 变换

下文要用到的特殊符号：

$\text{莫比乌斯函数 }\mu\ \ \ \text{单位根 }\epsilon\ \ \ \text{Dirichlet 卷积 }*\ \ \ \text{质数集合 }P$

---

### 2.思路

原问题求：

$$\sum\limits_{i=1}^n\sum_{j=1}^m [\text{gcd}(i,j) \in P]$$ 

由于质数集合不好处理，我们不妨~~按照套路~~先枚举 $\text{gcd}$ 的值。

原式等于：

$$\sum\limits_{d\in P}\sum_{i=1}^{n}\sum_{j=1}^{m}[\text{gcd}(i,j)=x]$$

提出一个 $x$ ，有：

$$\sum\limits_{x\in P}\sum\limits_{i=1}^{\left\lfloor {\frac{n}{x}}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor {\frac{m}{x}}\right\rfloor}[\text{gcd}(xi,xj)=x]$$

$$\sum\limits_{x\in P}\sum\limits_{i=1}^{\left\lfloor {\frac{n}{x}}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor {\frac{m}{x}}\right\rfloor}[\text{gcd}(i,j)=1]$$

其实这一步就相当于把 $\text{gcd}(i,j)$ 变成了单位函数的形式，即

$$[\text{gcd}(i,j)=1] \iff \epsilon(\text{gcd}(i,j))$$

原式等于

$$\sum\limits_{x\in P}\sum\limits_{i=1}^{\left\lfloor {\frac{n}{x}}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor {\frac{m}{x}}\right\rfloor}\epsilon(\text{gcd}(i,j))$$

又根据 $\mu$ 函数的性质 $\sum\limits_{d|n}\mu(d)=0$ 即 $\mu * 1 = \epsilon$

于是原式转化为：

$$\sum\limits_{x\in P}\sum\limits_{i=1}^{\left\lfloor {\frac{n}{x}}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor {\frac{m}{x}}\right\rfloor}\sum\limits_{d|\text{gcd}(i,j)}\mu(d)$$

由最大公约数的性质：

$$\sum\limits_{x\in P}\sum\limits_{i=1}^{\left\lfloor {\frac{n}{x}}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor {\frac{m}{x}}\right\rfloor}\sum\limits_{d|i,j}\mu(d)$$

到这里，我们就把 $\text{gcd}$ 成功干掉了。

然后上面那个式子再改变一下枚举顺序：

$$\sum\limits_{x\in P}\sum\limits_{d}\sum\limits_{i=1}^{\left\lfloor {\frac{n}{dx}}\right\rfloor}\sum\limits_{j=1}^{\left\lfloor {\frac{m}{dx}}\right\rfloor}\mu(d)$$

就可以消掉两个 $\sum$ ：

$$\sum\limits_{x\in P}\sum\limits_{d=1}^{min(\left\lfloor {\frac{n}{x}}\right\rfloor,\left\lfloor {\frac{m}{x}}\right\rfloor)}\left\lfloor {\frac{n}{dx}}\right\rfloor\left\lfloor {\frac{m}{dx}}\right\rfloor\mu(d)$$

假如做到这里的话，复杂度还是太高，不能通过此题。

于是我们再次尝试消掉 $\sum$

不妨设 $T = dx$ ，有 原式等于

$$\sum\limits_{x\in P}\sum\limits_{d=1}^{min(\left\lfloor {\frac{n}{x}}\right\rfloor,\left\lfloor {\frac{m}{x}}\right\rfloor)}\left\lfloor {\frac{n}{T}}\right\rfloor\left\lfloor {\frac{m}{T}}\right\rfloor\mu(d)$$

改变枚举顺序：

$$\sum\limits^{min(n,m)}_{T=1}\sum\limits_{x\in P}\left\lfloor {\frac{n}{T}}\right\rfloor\left\lfloor {\frac{m}{T}}\right\rfloor\mu(\frac{T}{x})$$

$$\sum\limits^{min(n,m)}_{T=1}\left\lfloor {\frac{n}{T}}\right\rfloor\left\lfloor {\frac{m}{T}}\right\rfloor\sum\limits_{x\in P,x|T}\mu(\frac{T}{x})$$

观察后面的式子 $\sum\limits_{x\in P,x|T}\mu(\frac{T}{x})$ ，可以通过预处理前缀和直接求出答案。（关于如何预处理详见细节实现部分）

于是我们就把复杂度优化到了 $O(Tn)$ ，但还不够。

我们发现有一个性质： $\sum\limits_{i=1}^{n} \left\lfloor\frac{n}{i}\right\rfloor$ 的取值最多只有 $2\sqrt{n}$ 个，分别在 $[1,\sqrt n]$ 和 $(\sqrt n,n]$ 中有 $\sqrt n$ 个取值。

同理，**因为取值是单调的**，$\sum\limits_{i=1}^{n} \left\lfloor\frac{n}{i}\right\rfloor\left\lfloor\frac{m}{i}\right\rfloor (m\leq n)$ 的取值个数是 $\sqrt n$ 级别的。

因此，我们就可以把第一个 $\sum$ 的复杂度降到 $O(\sqrt n)$ 。

总复杂度 $O(T\sqrt n)$ ，可以通过此题。

---

### 3.细节实现

#### 1.怎么预处理 $\mu$ 函数？

由 $\mu$ 函数的定义：

$\mu(n)=\begin{cases}1&n=1\\(-1)^k&n=p_1\cdot p_2\cdots p_k \ \ \ \ \text{其中 }p_i\text{ 为质数}\\0&\text{otherwise}\end{cases}$

我们就可以利用线性筛的性质一边筛质数一边求 $\mu$ 了。

#### 怎么预处理式子 $\sum\limits_{x\in P,x|T}\mu(\frac{T}{x})\ $ ?

考虑每个质数的贡献。

对每个质数枚举倍数即可。

复杂度 $O(n\ log\ log\ n)$

#### 怎么用 $O(\sqrt n)$ 的复杂度处理式子 $\ \sum\limits_{i=1}^{n} \left\lfloor\frac{n}{i}\right\rfloor\left\lfloor\frac{m}{i}\right\rfloor\ $ ?

具体实现：

```cpp
for(int l=1,r=0;l<=n;l=r+1){
	r=min(n/(n/l),m/(m/l));
	ans+=(Sum[r]-Sum[l-1])*(n/l)*(m/l);
   //sum 即前文提到的前缀和
}
```

$l$ 表示上次的取值，$r$ 是这次的取值。

若不理解可以手算一组 $n$ 和 $m$ 。

---

## 作者：封禁用户 (赞：0)



$update \ 2020.1.19:$草草草，发现公式全炸了，来[我的博客](https://www.luogu.com.cn/blog/orz-froggod/solution-p2257)里看吧

------------


萌新第一次做反演题，写得不好还请大佬指教...


先讲一个50分的做法

题目要求$  \sum_{i=1}^n \sum_{j=1}^m[gcd(i,j)==prime]$ 

我们先枚举质数p，于是柿子变成了这样
$$  \sum_{p \in prime}^{min(n,m)} \sum_{i=1}^{\left\lfloor \frac{n}{p} \right\rfloor} \sum_{j=1}^{\left\lfloor \frac{m}{p} \right\rfloor} [gcd(i,j)==1]  $$

 又有$\sum_{d|n} \mu(d)=[n=1]  $
 
 所以这个柿子还能变成这样
 
 $$  \sum_{p=2}^{min(n,m)} \sum_{i=1}^{\left\lfloor \frac{n}{p} \right\rfloor} \sum_{j=1}^{\left\lfloor \frac{m}{p} \right\rfloor} \sum_{d|gcd(i,j)} \mu(d)$$
 
 然后我们发现要枚举$gcd(i,j)$，非常难受，于是我们先枚举$d$
 
 于是柿子变成了这样
 
 $$ \sum_{p=2}^{min(n,m)}\sum_{d=1}^{min(\left\lfloor \frac{n}{p} \right\rfloor,\left\lfloor \frac{m}{p} \right\rfloor)} \mu(d) \sum_{i=1}^{\left\lfloor \frac{n}{p} \right\rfloor}  \sum_{j=1}^{\left\lfloor \frac{m}{p} \right\rfloor} [d|gcd(i,j)] $$
 
而
 
 $$
 \sum_{i=1}^{\left\lfloor \frac{n}{p} \right\rfloor} \sum_{j=1}^{\left\lfloor \frac{m}{p} \right\rfloor} [d|gcd(i,j)] = \left\lfloor \frac{\left\lfloor \frac{n}{p} \right\rfloor}{d}\right\rfloor\left\lfloor \frac{\left\lfloor \frac{m}{p} \right\rfloor}{d}\right\rfloor
 $$
 
 这个东西也是很显然的，于是柿子变成了这样...
 
 
 $$
 \sum_{p\in prime}^{min(n,m)}\sum_{d=1}^{min(\left\lfloor \frac{n}{p} \right\rfloor,\left\lfloor \frac{m}{p} \right\rfloor)} \mu(d)  \left\lfloor \frac{\left\lfloor \frac{n}{p} \right\rfloor}{d}\right\rfloor\left\lfloor \frac{\left\lfloor \frac{m}{p} \right\rfloor}{d}\right\rfloor 
 $$
 
 
 这个东西我们大力分块一下，就可以有$O(ln(n) \sqrt{n})$的时间复杂度
 
 （注：枚举质数，而1-n内的质数个数大约在ln(n)左右，如果我记错的话，请到评论区怼我）
 
 
 然而题意中$1\leq n  \leq 10^7$，再加上数据的强大，这种方法只能跑到50分
 
 
 
 
 
 
 下面介绍100分做法
 
 
 设$F(d)=\sum_{i=1}^n\sum_{j=1}^m[d|gcd(i,j)]$
 
 $F(d)$当然就是$\left\lfloor \frac{n}{d} \right\rfloor \left\lfloor \frac{m}{d} \right\rfloor$
 
 
 
 再设$f(d)=\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)==d]$
 
 显然，$F(x)=\sum_{x|d} f(d)$
 
 我们反演一下，得出$f(x)=\sum_{x|d} \mu(\left\lfloor \frac{d}{x} \right\rfloor) F(d)= \sum_{x|d} \mu(\left\lfloor \frac{d}{x} \right\rfloor) \left\lfloor \frac{n}{d} \right\rfloor
\left\lfloor \frac{m}{d} \right\rfloor$


答案$ans=\sum_{p \in prime}^{min(n,m)}f(p)=\sum_{p \in prime}^{min(n,m)}\sum_{p|d} \mu(\left\lfloor \frac{d}{p} \right\rfloor) F(d)$

然后我们枚举一下d...


$$ans=\sum_{p \in prime}^{min(n,m)}\sum_{p|d} \mu(\left\lfloor \frac{d}{p} \right\rfloor) F(d)=\sum_{p \in prime}^{min(n,m)} \sum_{d=1}^{min(\frac{n}{p},\frac{m}{p})} \mu(d)  F(dp)=
\sum_{p \in prime}^{min(n,m)} \sum_{d=1}^{min(\frac{n}{p},\frac{m}{p})} \mu(d) \frac{n}{dp} 
\frac{m}{dp}$$


这个dp看起来挺难受的，于是我们换个方向，改为枚举dp和p，我们设dp=T,t=p

于是...

$$ans=\sum_{T=1}^{min(n,m)} \sum_{t|T,t \in prime} \mu(\frac{T}{t}) \frac{n}{T} \frac{m}{T}=\sum_{T=1}^{min(n,m)} \frac{n}{T} \frac{m}{T} ( \sum_{t|T,t \in prime} \mu({\frac{T}{t}}) \ )$$


（由于$\left\lfloor \right\rfloor$这个东西打起来实在太烦，懒得打...上面的柿子默认全部带$\left\lfloor \right\rfloor$）



前面那部分（(n/t)(m/t)）数论分块一下，后面那部分预处理搞下前缀和，于是我们以优秀的$O(\sqrt{n})$的时间复杂度A了此题





------------

~~其实我主要是来讲50分做法的~~


---

## 作者：_LHF_ (赞：0)

感谢 @Alpha1022 巨佬的帮助！
## 讲一讲这一题

想必大家一定做过[ZAP](https://www.luogu.com.cn/problem/P3455)这一道题目吧，该题目是那一题的升级版。建议先看一下我的一篇题解：[传送门](https://www.luogu.com.cn/blog/LHF/solution-p3455)

好了，就默认大家看完了。那么我们按照讲解ZAP的老套路来试一下，毕竟原式可以转化为：
$$\sum_{k∈prime}\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)=k]$$
老套路：
令$x=\lfloor{\frac{a}{k}}\rfloor,y=\lfloor{\frac{b}{k}}\rfloor,s=min(x,y)$

则原式
$$=\sum_{k∈prime}\sum_{i=1}^{x}\sum_{j=1}^{y}[gcd(i,j)=1]$$
直接套公式

$$=\sum_{k∈prime}\sum_{i=1}^{x}\sum_{j=1}^{y}\sum_{d|gcd(i,j)}μ(d)$$
拆开GCD之后

$$=\sum_{k∈prime}\sum_{i=1}^{x}\sum_{j=1}^{y}\sum_{d=1}^sμ(d)[d|i][d|j]$$
然后各找各的家

$$=\sum_{k∈prime}\sum_{d=1}^sμ(d)\sum_{i=1}^{x}[d|i]\sum_{j=1}^{y}[d|j]$$

后面的好像可以直接计算呀

$$=\sum_{k∈prime}\sum_{d=1}^sμ(d)\lfloor{\frac{x}{d}}\rfloor\lfloor{\frac{y}{d}}\rfloor$$
推到这里，好像再推下去有点难了，我们不妨还原一下原式，得：
$$\sum_{k∈prime}\sum_{d=1}^{min(\lfloor{\frac{a}{k}}\rfloor,\lfloor{\frac{b}{k}}\rfloor)}μ(d)\lfloor{\frac{\lfloor{\frac{a}{k}}\rfloor}{d}}\rfloor\lfloor{\frac{\lfloor{\frac{b}{k}}\rfloor}{d}}\rfloor$$
此时，我们发现$min(\lfloor{\frac{a}{k}}\rfloor,\lfloor{\frac{b}{k}}\rfloor)$这东西太烦人了，可不可以变一下呢？当然可以，因为当$d>\lfloor{\frac{a}{k}}\rfloor$或$d>\lfloor{\frac{b}{k}}\rfloor$时$μ(d)\lfloor{\frac{\lfloor{\frac{a}{k}}\rfloor}{d}}\rfloor\lfloor{\frac{\lfloor{\frac{b}{k}}\rfloor}{d}}\rfloor=0$了，所以这里不用担心，我们可以把$min(\lfloor{\frac{a}{k}}\rfloor,\lfloor{\frac{b}{k}}\rfloor)$替换成$a$或$b$或$min(a,b)$（建议是$min(a,b)$），所以得到：
$$\sum_{k∈prime}\sum_{d=1}^{min(a,b)}μ(d)\lfloor{\frac{\lfloor{\frac{a}{k}}\rfloor}{d}}\rfloor\lfloor{\frac{\lfloor{\frac{b}{k}}\rfloor}{d}}\rfloor$$
好吧，先补充一个定理：$\lfloor{\frac{\lfloor{\frac{a}{b}}\rfloor}{c}}\rfloor=\lfloor{\frac{a}{bc}}\rfloor$

所以原式得：
$$\sum_{k∈prime}\sum_{d=1}^{min(a,b)}μ(d)\lfloor{\frac{a}{kd}}\rfloor\lfloor{\frac{b}{kd}}\rfloor$$
好像有点麻烦，怎么办呢？

行吧我们可以尝试去枚举kd，令T=kd，则原式=
$$\sum_{k∈prime}\sum_{d=1}^{min(a,b)}μ(d)\lfloor{\frac{a}{T}}\rfloor\lfloor{\frac{b}{T}}\rfloor$$
好像没有什么进展，但我们可以把枚举d改成枚举T，这样原式得：
$$\sum_{T=1}^{min(a,b)}\lfloor{\frac{a}{T}}\rfloor\lfloor{\frac{b}{T}}\rfloor\sum_{k∈prime,k|T}μ(\frac{T}{k})$$
XXX：完了，这下怎么办呀！

其实也不难，我们看后面的算式：
$$\sum_{k∈prime,k|T}μ(\frac{T}{k})$$
好像可以初始化一下，我们可以将它初始化一下，因为数据比较小，所以直接用欧拉筛初始化再进行计算，最后求出前缀和（后面会用到的），代码如下：
```cpp
void init()
{
	mobi[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!bz[i])
		{
			len++;
			prime[len]=i;
			mobi[i]=-1;
		}
		for(int j=1;j<=len&&i*prime[j]<=N;j++)
		{
			bz[i*prime[j]]=1;
			if(i%prime[j])
				mobi[i*prime[j]]=-mobi[i];
			else break;
		}
	}
	for(int i=1;i<=len;i++)
	{
		for(int j=1;j*prime[i]<=N;j++)
		{
			f[j*prime[i]]+=mobi[j];
		}
	}
	for(int i=2;i<=N;i++) f[i]+=f[i-1];
}
```
其中，$N=10,000,000$。然后，利用ZAP里面讲解的整除分块，最后单个询问：$O(n^2)→O(\sqrt{n})$，初始化的时间复杂度大概为$O(N)$。上代码：
```cpp
#include<cstdio>
#define N 10000000
#define min(a,b) (a<b?a:b)
using namespace std;
int prime[N],mobi[N+1],bz[N+1];
int n,m,len,T;
long long f[N+1],ans;
void init()
{
	mobi[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!bz[i])
		{
			len++;
			prime[len]=i;
			mobi[i]=-1;
		}
		for(int j=1;j<=len&&i*prime[j]<=N;j++)
		{
			bz[i*prime[j]]=1;
			if(i%prime[j])
				mobi[i*prime[j]]=-mobi[i];
			else break;
		}
	}
	for(int i=1;i<=len;i++)
	{
		for(int j=1;j*prime[i]<=N;j++)
		{
			f[j*prime[i]]+=mobi[j];
		}
	}
	for(int i=2;i<=N;i++) f[i]+=f[i-1];
}
int main()
{
	init();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		ans=0;
		for(int i=1,j;i<=min(n,m);i=j+1)
		{
			j=min((n/(n/i)),(m/(m/i)));
			ans+=(long long)(n/i)*(m/i)*(f[j]-f[i-1]);
		}
		printf("%lld\n",ans);
	}
}
```
### 完美散花（逃

---

## 作者：overflow (赞：0)

这题的做法楼上楼下的大佬们都讲了。我来说一下时限和一些细节。

1. 不能所有变量全开longlong，会TLE。所以尽量少开longlong。经过计算发现只把前缀和数组和答案开成longlong就行了。其他必须开int。

2. 预处理那个奇怪的东西时，第一层枚举必须是所有质数，统计每一个质数的贡献。这样的话虽然我也不知道是什么玄学复杂度，反正能过。但是如果你第一层循环开成1*10^7，那你就凉了。因为10000000以内质数还真不少，O(10^7 *10^7以内的质数个数)是过不了的。不信你自己看看10000000以内有多少质数。

3. 如果还不过，你看看有没有加快读，这个网上到处都是板子。

4. 如果还TLE，说明你被某些奇怪而不可描述的东西卡了。你可以尝试使用一些诸如inline啊，static int啊之类的玄学优化方法。

总之，如果你t了后几个点，先不要急着否决自己。我刚开始就被坑了，还以为算法错了。看了题解发现没错。调了好一会才过。毕竟4000ms这个时限本来就看上去有点奇怪。出题人可能是故意卡了细节。

加油！！！

```cpp
#include<cstdio>
#include<cstring>
#define ll long long
const ll MAXN=10000010;
int mobius[MAXN];
int prime[MAXN];
bool tap[MAXN];
ll sum[MAXN];
int n,m;
int t;
inline int min(int a,int b)
{
	if(a<b)return a;
	return b;
}
inline void read(int &x)
{
	char ch;
	int k=1;
	x=0;
	scanf("%c",&ch);
	while(ch<'0' || ch>'9')
	{
		if(ch=='-')k=-1;
		scanf("%c",&ch);
	}
	while(ch>='0' && ch<='9')
	{
		x=x*10+(ch-'0');
		scanf("%c",&ch);
	}
	return;
}
void get_mobius(int x)
{
	int k,i,j;
	int cnt=0;
	//memset(tap,true,sizeof(tap));
	//memset(mobius,0,sizeof(mobius));
	//memset(sum,0,sizeof(sum));
	for(k=0;k<=x;k++)
	{
		tap[k]=true;
		mobius[k]=sum[k]=0;
	}
	mobius[1]=1;
	for(k=2;k<=x;k++)
	{
		if(tap[k])
		{
			prime[cnt++]=k;
			mobius[k]=-1;
		}
		for(i=0;i<cnt&&k*prime[i]<=x;i++)
		{
			tap[k*prime[i]]=false;
			if(k%prime[i]==0)break;
			mobius[k*prime[i]]=-mobius[k];
		}
	}
	//sum[0]=0;
	for(k=0;k<cnt;k++)
	{
		for(i=1;i*prime[k]<=x;i++)
		{
			sum[i*prime[k]]+=mobius[i];
		}
	}
	for(k=1;k<=x;k++)sum[k]+=sum[k-1];
	return;
}
int main()
{
	int k,i,j;
	ll ans;
	get_mobius(MAXN);
	read(t);
	while(t--)
	{
		read(n);read(m);
		j=min(n,m);
		ans=0;
		for(k=1;k<=j;k=i+1)
		{
			i=min(n/(n/k),m/(m/k));
			ans+=(sum[i]-sum[k-1])*(n/k)*(m/k);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```





---

## 作者：Smokey_Days (赞：0)

lp2257 YY的GCD
不妨设$ n<m$
首先将原提问形式化，可以得到原式为：
$$\sum_{x=1}^{n}\sum_{y=1}^{m}\sum_{p\in P}[gcd(x,y)==p] $$
将所有的$ x,y$都除以$ gcd(x,y)$，则原式可转化为：
$$\sum_{x=1}^{\lfloor \frac{n}{p} \rfloor}\sum_{y=1}^{\lfloor \frac{m}{p} \rfloor}\sum_{p\in P}[gcd(x,y)==1]$$
然后，根据莫比乌斯函数的基本性质，我们有：
$$\sum_{d|n}\mu(d)=[n==1]$$
替换入原式可以得到：
$$\sum_{x=1}^{\lfloor \frac{n}{p} \rfloor}\sum_{y=1}^{\lfloor \frac{m}{p} \rfloor}\sum_{p\in P}\sum_{d|gcd(x,y)}\mu(d)$$
将$ d|gcd(x,y)$一式化简可得：
$$d|gcd(x,y)=d|x\&\&d|y$$
代入原式：
$$\sum_{x=1}^{\lfloor \frac{n}{p} \rfloor}\sum_{y=1}^{\lfloor \frac{m}{p} \rfloor}\sum_{p\in P}\sum_{d|x\&\&d|y}\mu(d)$$
将所有的$ x,y$都除以$ d$，则原式可转化为：
$$\sum_{x=1}^{\lfloor \frac{n}{pd} \rfloor}\sum_{y=1}^{\lfloor \frac{m}{pd} \rfloor}\sum_{p\in P}\mu(d)$$
由于$ x,y$对后半部分式子无影响，且$ pd\le n$原式可变式为：
$$\sum_{p\in P}\sum_{d=1}^{\lfloor \frac{n}{p} \rfloor}\mu(d)\lfloor \frac{n}{pd} \rfloor \lfloor \frac{m}{pd} \rfloor$$
为了减少枚举的数量，不妨设$ q=pd$，那么我们又可以将原式转化为：
$$\sum_{q=1}^{n}\lfloor \frac{n}{q} \rfloor \lfloor \frac{m}{q} \rfloor \sum_{p\in P\&\&pd==q}\mu(d)$$
又，根据狄利克雷卷积的基本式：
$$ g=f*u\Rightarrow g(x)=\sum_{ab=x}f(a)u(b)$$
我们发现，上式靠右的如下部分可以作出变换：
$$\sum_{p\in P\&\&pd==q}\mu(d)=g(q)=\sum_{pd=q}[p\in P]\mu(d)$$
若令：
$$f(p)=[p\in P]$$
则我们可以发现：
$$g(q)=f(p)*\mu(d)$$
故而这一部分的值可以用狄利克雷卷积来$ O(nln_n)$预处理。
一看数据范围，完了：$ 10^7$，$ O(nln_n)$的复杂度显然是不够优秀的。我们需要将它优化到$ O(n)$


我们考虑对这个函数$ g$进行线性筛。
我们发现，上式可以进行如下变换：
$$g(q)=\sum_{pd=q\&\&p\in P}\mu(d)=\sum_{p\in P\&\&p|q}\mu(\frac{q}{p})$$
本质上就是枚举其质因子之和并求其除以该质因子的莫比乌斯函数值之和。
我们分三类讨论。
对于$ g(x)$
如果$ x\in P$，显然$ g(x)=\mu(1)=1$
如果$ x=a^vb,a\in P,v>1$，则显然枚举其他的质数是没有意义的。$ g(x)=\mu(b)$
如果$ x=ab,a\in P$，则，$ g(x)$的值，等价于在计算$ g(b)$的和的时候每一次计算都多乘上一个$ a$的贡献，也就是乘上负一。然后将这个值再加上枚举$ a$的情况，也就是$ \mu(b)$，即$ g(x)=-g(b)+\mu(b)$
然后大力上一个线性筛即可。

对于左半部分，上一个数论分块即可。
```cpp
#include<iostream>
#include<cstdio>

const int N = 10000000+5;

int p[N/10],g[N],mu[N],n,m;
bool ip[N];
void prpr(){
	p[0]=0;mu[1]=1;ip[1]=1;
	for(int i=2;i<=10000000;++i){
		if(!ip[i]){
			p[++p[0]]=i;
			mu[i]=-1;
			g[i]=1;
		}
		for(int j=1;j<=p[0]&&p[j]*i<=10000000;++j){
			ip[i*p[j]]=1;
			if(!(i%p[j])){
				g[i*p[j]]=mu[i];
				mu[i*p[j]]=0;
				break;
			}else{
				mu[i*p[j]]=-mu[i];
				g[i*p[j]]=-g[i]+mu[i];
			}
		}
	}
	for(int i=2;i<=10000000;++i){
		g[i]+=g[i-1]; 
	}
}
long long ans;
void init(){
	scanf("%d%d",&n,&m);
	n>m?n^=m^=n^=m:0;
	ans=0;
	int k=0;
	for(int i=1;i<=n;i=k+1){
		k=std::min(n/(n/i),m/(m/i));
		ans+=1ll*(n/i)*(m/i)*(g[k]-g[i-1]);
	}
	printf("%lld\n",ans);
}

int main(){
	prpr();
	int T;
	scanf("%d",&T);
	while(T--){
		init();
	}
	return 0;
}
```

---

## 作者：hl666 (赞：0)

**莫比乌斯反演**第一题。[莫比乌斯反演入门](https://www.cnblogs.com/cjjsb/p/9876840.html)

数论题不多BB，直接推导吧。

首先，发现题目所求$ans=\sum_{i=1}^n\sum_{j=1}^m [\gcd(i,j)=prime]$

考虑反演，我们令$f(d)$为$\gcd(i,j)(i\in[1,n],j\in[1,m])=d$的个数，$F(n)$为$d|\gcd(i,j)$的个数

即：

$$f(d)=\sum_{i=1}^n\sum_{j=1}^m [\gcd(i,j)=d]$$

$$F(s)=\sum_{s|d}f(d)=\lfloor\frac{n}{s} \rfloor \lfloor\frac{m}{s} \rfloor$$

根据**莫比乌斯反演定理**，有：

$$f(n)=\sum_{n|d} \mu(\lfloor\frac{d}{n} \rfloor)F(d)$$

所以开始化简，原式：

$$ans=\sum_{p\in prime} \sum_{i=1}^n \sum_{j=1}^m[\gcd(i,j)=p]$$

后面那个就是我们设的$f(p)$，所以我们带入得：

$$ans=\sum_{p\in prime} f(p)$$

用上面的公式反演一下：

$$ans=\sum_{p\in prime} \sum_{p|d}\mu(\lfloor\frac{d}{p} \rfloor)F(d)$$

这个不好处理，我们考虑把枚举$p$变成枚举$\lfloor\frac{d}{p} \rfloor$，则有：

$$ans=\sum_{p\in prime} \sum_{d=1}^{\min(\lfloor\frac{n}{p} \rfloor,\lfloor\frac{m}{p} \rfloor)}\mu(d)F(d\cdot p)$$

再根据$F(s)$的性质代进去就有：

$$ans=\sum_{p\in prime} \sum_{d=1}^{\min(\lfloor\frac{n}{p} \rfloor,\lfloor\frac{m}{p} \rfloor)}\mu(d)\lfloor\frac{n}{d\cdot p} \rfloor\lfloor\frac{m}{d\cdot p} \rfloor$$

然后我们用$T$换掉$d\cdot p$，则有：

$$ans=\sum_{T=1}^{\min(n,m)} \sum_{p|T,p\in prime} \mu(\lfloor\frac{T}{p} \rfloor)\lfloor\frac{n}{T} \rfloor\lfloor\frac{m}{T} \rfloor$$

把$\lfloor\frac{n}{T} \rfloor\lfloor\frac{m}{T} \rfloor$提到前面来就有：

$$ans=\sum_{T=1}^{\min(n,m)} \lfloor\frac{n}{T} \rfloor\lfloor\frac{m}{T} \rfloor\sum_{p|T,p\in prime} \mu(\lfloor\frac{T}{p} \rfloor)$$

然后我们发现这个式子就是$O(n)$的了，一看题目，**多组询问！**

结果还是套路，看到那个$\lfloor\frac{n}{T} \rfloor\lfloor\frac{m}{T} \rfloor$发现可以除法分块搞。

后面的式子稍加分析可以发现在筛法结束后枚举每个素数，再枚举$\lfloor\frac{T}{p} \rfloor$来统计。最后做一个**前缀和**即可。

CODE

```cpp
#include<cstdio>
#include<cctype>
#define RI register int
using namespace std;
const int P=10000000;
int t,n,m,prime[P+5],cnt,miu[P+5]; long long sum[P+5],ans; bool vis[P+5];
class FileInputOutput
{
    private:
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        #define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
        #define S 1<<21
        char Fin[S],Fout[S],*A,*B; int Ftop,pt[25];
    public:
        FileInputOutput() { A=B=Fin; Ftop=0; } 
        inline void read(int &x)
        {
            x=0; char ch; int flag=1; while (!isdigit(ch=tc())) flag=ch^'-'?1:-1;
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc())); x*=flag;
        }
        inline void write(long long x)
        {
            if (!x) return (void)(pc(48),pc('\n')); RI ptop=0;
            while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc('\n');
        }
        inline void Fend(void)
        {
            fwrite(Fout,1,Ftop,stdout);
        }
        #undef tc
        #undef pc
        #undef S
}F;
#define Pi prime[j]
inline void Euler(void)
{
    vis[1]=miu[1]=1; RI i,j; for (i=2;i<=P;++i)
    {
        if (!vis[i]) prime[++cnt]=i,miu[i]=-1;
        for (j=1;j<=cnt&&i*Pi<=P;++j)
        {
            vis[i*Pi]=1; if (i%Pi) miu[i*Pi]=-miu[i]; else break;
        }
    }
    for (j=1;j<=cnt;++j) for (i=1;i*Pi<=P;++i) sum[i*Pi]+=miu[i];
    for (i=1;i<=P;++i) sum[i]+=sum[i-1];
}
#undef Pi
inline int min(int a,int b)
{
    return a<b?a:b;
}
inline void swap(int &a,int &b)
{
    int t=a; a=b; b=t;
}
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    for (Euler(),F.read(t);t;--t)
    {
        F.read(n); F.read(m); ans=0; if (n>m) swap(n,m);
        for (RI l=1,r;l<=n;l=r+1)
        {
            r=min(n/(n/l),m/(m/l)); ans+=1LL*(n/l)*(m/l)*(sum[r]-sum[l-1]);
        }
        F.write(ans);
    }
    return F.Fend(),0;
}
```

---

## 作者：become_better (赞：0)

```cpp
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  maxn 10000100
using namespace std;
int prime[maxn],cnt,mo[maxn],x[maxn];
long long sum[maxn];
bool f[maxn];
void data()
{
    cnt=0;
    memset(f,true,sizeof(f));
     memset(x,0,sizeof(x));
     sum[0]=0;
    f[0]=f[1]=false;
    mo[1]=1;
    for(int i=2;i<=maxn;i++)
    {
        if(f[i])
        {
            prime[cnt++]=i;
            mo[i]=-1;
        }
        for(int j=0;j<cnt&&i*prime[j]<=maxn;j++)
        {
            f[i*prime[j]]=false;
            if(i%prime[j])
            mo[i*prime[j]]=-1*mo[i];
            else
            {
                mo[i*prime[j]]=0;
                break;
            }
        }
    }
    //printf("%d\n",prime[0]);
    for(int j=0;j<cnt;j++)
    for(int i=1;i*prime[j]<=maxn;i++)
    {
        x[i*prime[j]]+=mo[i];
    }
    for(int i=1;i<=maxn;i++)
    {
        sum[i]+=sum[i-1]+x[i];
    }
}
int main()
{
    data();
    int t,minn,n,m;
    long long ans;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        minn=min(n,m);
        ans=0;
        for(int l=1,r;l<=minn;l=r+1)
        {
            r=min(n/(n/l),m/(m/l));
            ans+=(long long)(n/l)*(m/l)*(sum[r]-sum[l-1]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

```

---

## 作者：yzhang (赞：0)

### [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/10134439.html)

### [原题传送门](https://www.luogu.org/problemnew/show/P4450)

### 这题需要运用[莫比乌斯反演(懵逼钨丝繁衍)](https://www.cnblogs.com/yzhang-rp-inf/p/10124488.html)

显然题目的答案就是$$ Ans=\sum_{i=1}^N\sum_{j=1}^M[gcd(i,j)=prime]$$

我们先设设F(n)表示满足$gcd(i,j)\%t=0$的数对个数，f(t)表示满足$gcd(i,j)=t$的数对个数

$$f(t)=\sum_{i=1}^N\sum_{j=1}^M[gcd(i,j)=t]$$

$$F(n)=\sum_{n|t}\lfloor \frac{N}{n} \rfloor \lfloor \frac{M}{n} \rfloor$$

那么根据莫比乌斯反演的第二种形式珂以得到

$$f(n)=\sum_{n|t}\mu(\lfloor \frac{t}{n} \rfloor)F(t)$$
 
所以答案珂以变形为：

$$Ans=\sum_{p \in prime}\sum_{i=1}^N\sum_{j-1}^M[gcd(i,j)=p)$$

$$=\sum_{p \in prime}f(p) \qquad \qquad \quad$$

$$=\sum_{p \in prime}\sum_{p|t}\mu(\lfloor \frac{t}{p} \rfloor)F(t)$$

我们不枚举p，我们枚举$\lfloor \frac{t}{p} \rfloor$

$$Ans=\sum_{p \in prime}\sum_{d=1}^{Min(\frac{N}{p},\frac{M}{p})}\mu(t)F(tp)$$

$$\qquad \qquad \qquad=\sum_{p \in prime}\sum_{d=1}^{Min(\frac{N}{p},\frac{M}{p})}\mu(t)\sum_{n|t}\lfloor \frac{N}{tp} \rfloor \lfloor \frac{M}{tp} \rfloor$$

我们把tp换成T继续变形

$$Ans=\sum_{T=1}^{Min(N,M)}\lfloor \frac{N}{T} \rfloor \lfloor \frac{M}{T} \rfloor(\sum_{p|T,p \in prime}\mu(\frac{T}{p}))$$

这样就珂以用整除分块求了qaq

```cpp
#include <bits/stdc++.h>
#define N 10000005
#define ll long long 
#define getchar nc
using namespace std;
inline char nc(){
    static char buf[100000],*p1=buf,*p2=buf; 
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++; 
}
inline int read()
{
    register int x=0,f=1;register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return x*f;
}
inline void write(register ll x)
{
    if(!x)putchar('0');if(x<0)x=-x,putchar('-');
    static int sta[30];register int tot=0;
    while(x)sta[tot++]=x%10,x/=10;
    while(tot)putchar(sta[--tot]+48);
}
inline int Min(register int x,register int y)
{
    return x<y?x:y;
}
int v[N],miu[N],prim[N],cnt=0,g[N];
ll sum[N];
int main()
{
    miu[1]=1;
    for(register int i=2;i<=N;++i)
    {
        if(!v[i])
        {
        	miu[i]=-1;
        	prim[++cnt]=i;
		}
		for(register int j=1;j<=cnt&&prim[j]*i<=N;++j)
		{
			v[i*prim[j]]=1;
			if(i%prim[j]==0)
				break;
			else
				miu[prim[j]*i]=-miu[i];
		}
    }
    for(register int i=1;i<=cnt;++i)
    	for(register int j=1;j*prim[i]<=N;++j)
    		g[j*prim[i]]+=miu[j];
    for(register int i=1;i<=N;++i)
        sum[i]=sum[i-1]+(ll)g[i];
    int t=read();
    while(t--)
    {
    	int n=read(),m=read();
    	if(n>m)
    		n^=m^=n^=m;
    	ll ans=0;
    	for(register int l=1,r;l<=n;l=r+1)
    	{
    		r=Min(n/(n/l),m/(m/l));
    		ans+=(ll)(n/l)*(m/l)*(sum[r]-sum[l-1]);
		}
		write(ans),puts("");
	}
    return 0;
}
```



---

## 作者：小蒟蒻皮皮鱼 (赞：0)

温馨提示：由于如果LaTeX有锅，请在[这里](https://www.luogu.com.cn/blog/lcezych/solution-p2257)查看

题意：给定$N, M$，求

$$
\sum\limits_{i = 1}^N\sum\limits_{j = 1}^N[gcd(i,j)=k](k\in Prime)
$$

先规定：本文中的$\frac{a}{b}$表示$\lfloor \frac{a}{b} \rfloor$~~(因为我懒)~~

不妨设$N<M$

首先，显然原式可以写成这个形式：

$$
\sum\limits_{k = 1,k\in Prime}^{N}\sum\limits_{i = 1}^N\sum\limits_{j = 1}^M[gcd(i,j)=k]
$$

我们设：

$$
\mathbf{f}(k)=\sum\limits_{i = 1}^N\sum\limits_{j = 1}^M[gcd(i,j)=k]
$$

$$
\mathbf{F}(n)=\sum\limits_{n|k}\mathbf{f}(k)
$$

也就是$\mathbf{f}(k)$表示$gcd(i, j)=k$的数的个数，$\mathbf{F}(k)$表示$gcd(i, j)=d\times k(d\in N_+)$的数的个数

由定义可知：

$$
\mathbf{F}(n)=\frac{N}{n}\frac{M}{n}
$$

因为$\mathbf{F}(k)$表示$gcd(i, j)=d\times k(d\in N_+)$的数的个数，那么$i,j$必须要同时包含$k$这个因子

那么由莫比乌斯反演公式得：

$$
\mathbf{f}(n) = \sum\limits_{n|k}\mu(\frac{k}{n})\mathbf{F}(k)
$$

直接代入：

$$
\sum\limits_{k = 1,k\in Prime}^{N}\sum\limits_{i = 1}^N\sum\limits_{j = 1}^M[gcd(i,j)=k]
$$

$$
=\sum\limits_{k = 1,k\in Prime}^{N}f(k)
$$

$$
=\sum\limits_{k = 1,k\in Prime}^{N}\sum\limits_{k|d}\mu(\frac{d}{k})\mathbf{F}(d)
$$

换成枚举$\frac{d}{k}$

$$
=\sum\limits_{k = 1,k\in Prime}^{N}\sum\limits_{d=1}^{\frac{N}{k}}\mu(d)\mathbf{F}(dk)
$$

把$\mathbf{F}(dk)$替换得到：

$$
=\sum\limits_{k = 1,k\in Prime}^{N}\sum\limits_{d=1}^{\frac{N}{k}}\mu(d)\frac{N}{dk}\frac{M}{dk}
$$

设$dk=p$

$$
=\sum\limits_{p=1}^{N}\sum\limits_{k|p,k\in Prime}\mu(\frac{p}{k})\frac{N}{p}\frac{M}{p}
$$

显然后面两项和$k$无关，可以提出来

$$
=\sum\limits_{p=1}^{N}\frac{N}{p}\frac{M}{p}\sum\limits_{k|p,k\in Prime}\mu(\frac{p}{k})
$$

多组数据整除分块+线性筛就可以了

```cpp
void pre()
{
	mu[1] = 1;
	for(int i = 2; i <= N - 1; i ++)
	{
		if(!flag[i]) pri[++cnt] = i, mu[i] = -1;
		for(int j = 1; j <= cnt && i * pri[j] <= N - 1; j ++)
		{
			flag[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
			mu[i * pri[j]] = -mu[i];
		} 
	}
	for(int i = 1; i <= cnt; i ++)
	{
		for(int j = 1; j * pri[i] <= N; j ++)
		{
			f[j * pri[i]] += mu[j];
		}
	}
	for(int i = 1; i <= N ; i ++) sum[i] = sum[i - 1] + f[i];
}

ll solve(int a, int b)
{
	ll ans = 0;
	for(int l = 1, r = 0; l <= a; l = r + 1)
	{
		r = min(a / (a / l), b / (b / l));
		ans += (ll)(sum[r] - sum[l - 1]) * (a / l) * (b / l);
	}
	return ans;
}
```

upd:2020.1.8 增加了LaTeX可能会炸的提示以及（不知道有没有）解决了LaTeX炸掉的原因

---

