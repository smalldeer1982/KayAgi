# [POI 2007] ZAP-Queries

## 题目描述

密码学家正在尝试破解一种叫 BSA 的密码。

他发现，在破解一条消息的同时，他还需要回答这样一种问题：

给出 $a,b,d$，求满足 $1 \leq x \leq a$，$1 \leq y \leq b$，且 $\gcd(x,y)=d$ 的二元组 $(x,y)$ 的数量。

因为要解决的问题实在太多了，他便过来寻求你的帮助。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 5 \times 10^4$，$1 \leq d \leq a,b \leq 5 \times 10^4$。

## 样例 #1

### 输入

```
2
4 5 2
6 4 3```

### 输出

```
3
2```

# 题解

## 作者：_sys (赞：100)

#### 曾经我好几次想学莫比乌斯反演，但是写完题后还是一脸懵逼，又因为我比较懒，所以已知没有学会，不断摸索摸索，现在已经有了初步的理解。

#### 我决定用初学者的角度写一篇总结，以免我再忘掉。

***
例题：[P3455 [POI2007]ZAP-Queries](https://www.luogu.org/problemnew/show/P3455)

实际上就是求

$\sum_{i=1}^{n}\sum_{j=1}^{m}[gcd(i,j)=k]$

(这里我们让$n>=m$)

我们首先把$k$提出来。为什么呢，因为莫比乌斯反演的条件之一是出现$[...=1]$。即：

$\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[gcd(i,j)=1]$

这是因为$k|i$且$k|j$时才对答案有贡献。

***
现在我们先介绍莫比乌斯反演
***
**定义**

$\mu(x)=\begin{cases} 1 & x=1 \\ 0 & \textrm{存在} p^2|x,p \in Prime \\ (-1)^k & k\textrm{为质因数个数}\end{cases}$

非常奇怪的一个定义$...$

我当初也不太理解为什么要定义成这个鬼样子$...$

***
**定义**

$f_1*f_2(x)=\sum_{i|x}f_1(i)f_2(\frac{n}{i})$

为数论函数(定义域为正整数的函数)$f_1$和$f_2$的**迪利克雷卷积**

那么实际上我们可以把$*$看作两个函数之间的作用，返回一个函数
***
**引理1:**

**若**$f_1$和$f_2$**为积性函数，那么**$f_1*f_2$**也为积性函数**

_证明：_

$(gcd(x,y)=1)$

$\begin{aligned} f_1*f_2(xy)=&\sum_{i|xy}f_1(i)f_2(\frac{xy}{i}) -\textrm{定义}\\ =& \sum_{i|x}\sum_{j|y}f_1(ij)f_2(\frac{xy}{ij})-\textrm{把上一步的}i\textrm{变为这一步的ij}\\  =&\sum_{i|x}\sum_{j|y}f_1(i)f_1(j)f_2(\frac{x}{i})f_2(\frac{y}{j}) -f_1\textrm{和}f_2\textrm{是积性函数}\\ =&(\sum_{i|x}f_1(i)f_2(\frac{x}{i}))(\sum_{j|y}f_1(j)f_2(\frac{y}{j}))\ -\textrm{不理解这步的话可以倒推到上一步}\\ =&f_1(x)*f_2(y)\end{aligned}$


***
**定义**

$\epsilon(x)=[x=1]$

叫做单位函数

***
**定理1：**$($反演本质$)$

$1*\mu=\epsilon$

即：
$\sum_{i|x}\mu(i)=\epsilon(x)$

_证明：_

_若_$x=1$_，显然成立_

_否则，我们让_$t=\Pi_{i=1} p_i^{a_i}$

_如果_$a$_中有一个不为_$1$，_则_$\mu(t)=0$

_所以对_$1*\mu$_真正有贡献的的只有_$a$_全为_$0$_或_$1$_的因数。_

_假设有_$p_{1-n}$，_那么有且仅有_$i$_个_$a$_的值为_$1$_的因数个数为_$C_{n}^{i}$

_根据_$\mu$_的定义，我们可以得到以下式子_

$1*\mu=\sum_{i=0}^{n}(-1)^iC_{n}^{i}$

_而_

$(x-1)^n=\sum_{i=0}^{n}(-1)^iC_{n}^{i}x^{n-i}$

_令_$x=1$_，等式左边为_$0$_，等式右边为上式。所以，这种情况下，_

$1*\mu=\sum_{i=0}^{n}(-1)^iC_{n}^{i}=0$

_综上，_

$1*\mu=\epsilon$

***
**引理2：**

$\mu$为积性函数

_证明：_

$(gcd(x,y)=1)$

_若_$x$_和_$y$_有一个为_$1$_，显然成立_

_若_$\mu(x)$_和_$\mu(y)$_有一个为_$0$_，显然成立_

_否则：_

$\begin{aligned}\mu(x)\mu(y)=&(-1)^{k_x}(-1)^{k_y} -\textrm{定义} \\ =& (-1)^{k_x+k_y} \\ =&\mu(xy) -\textrm{质因数个数函数是加性函数}\end{aligned}$

***
好，说完了一大堆东西，我们继续来看题

$\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[gcd(i,j)=1]$

我们使用莫比乌斯反演得到

$\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{d|gcd(i,j)}\mu(d)$

我们又发现可以直接让$i$变成$i/d$，$j$变成$j/d$，这样就不用考虑$d$是否是$gcd(i,j)$的因数，于是我们枚举$d$，即

$\sum_{d=1}^{n}\sum_{i=1}^{\lfloor\frac{n}{kd}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{kd}\rfloor}\mu(d)$

此时我们发现，诶！$\mu(d)$和里面俩$\sum$没关系了，赶紧提出来

$\sum_{d=1}^{n}\mu(d)\sum_{i=1}^{\lfloor\frac{n}{kd}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{kd}\rfloor}1$

然后，我们就可以顿时消去两个$\sum$!

$\sum_{d=1}^{n}\mu(d)\lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor$

所以我们可以通过线性筛求出$\mu(1)-\mu(n)$，然后就可以$O(n)$求了！

但是我们又发现，询问组数$T=50000$，即使是$O(n)$也过不去。

此时，我们就需要另外一个数论处理工具：整除分块（数论分块）

***
对于$\sum_{i=1}^{n}f(i)$，$f(i)$单调，$f(i)$的取值有$k$种的某些函数，我们可以做到$O(k)$的复杂度

做法：

* 每次求出$f(x)=i$的终点
* 统计起点与终点之间的值
* 把$i$的终点$+1$为下一个值的起点

为什么说某些函数呢，因为有一些函数你不太好确定终点在哪里。

***
**引理3：**

$\lfloor\frac{n}{kd}\rfloor$的取值不会多于$2\sqrt {\lfloor\frac{n}{k}\rfloor}$种

_证明:_

* _若_$d<=\sqrt {\lfloor\frac{n}{k}\rfloor}$_，最多有_$\sqrt {\lfloor\frac{n}{k}\rfloor}$_种取值_

* _若_$d>=\sqrt {\lfloor\frac{n}{k}\rfloor}$，$\lfloor\frac{n}{kd}\rfloor<=\sqrt {\lfloor\frac{n}{k}\rfloor}$_，最多有_$\sqrt {\lfloor\frac{n}{k}\rfloor}$_种取值_

***
于是我们可以$O(n)$预处理，单次询问$O(\sqrt n)$求$\sum_{d=1}^{n}\mu(d)\lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor$啦！注意$\lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor$要分成$\lfloor\frac{n}{kd}\rfloor$和$\lfloor\frac{m}{kd}\rfloor$取值**都一样**的为一段。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int Maxn=50005;
long long ans;
int T,n,m,k,cnt,mu[Maxn],prim[Maxn],sum[Maxn];
bool vis[Maxn];
void init(void)
{
	mu[1]=1;
	for(int i=2;i<=50000;i++)
	{
		if(!vis[i]) prim[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*prim[j]<=50000;j++)
		{
			vis[i*prim[j]]=true;
			if(i%prim[j]==0)
			{
				mu[i*prim[j]]=0;
				break;
			}
			mu[i*prim[j]]=-mu[i];
		}
	}
	for(int i=1;i<=50000;i++)
		sum[i]=sum[i-1]+mu[i];
}
int main()
{
	scanf("%d",&T);
	init();
	while(T--)
	{
		ans=0;
		scanf("%d%d%d",&n,&m,&k);
		int End=0,N=n/k,M=m/k;
		if(N<M) swap(N,M);
		for(int Start=1;Start<=M;Start=End+1)
		{
			End=min(N/(N/Start),M/(M/Start));
			ans+=(sum[End]-sum[Start-1])*(long long)(N/Start)*(M/Start);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：pengym (赞：46)

我顺便来安利一下自己的博客[peng-ym's blog](http://www.cnblogs.com/peng-ym/)里面也有[莫比乌斯反演](http://www.cnblogs.com/peng-ym/p/8647856.html)与[整除分块](http://www.cnblogs.com/peng-ym/p/8661118.html)的介绍，不知道的可以看一看哦！
### 题目大意
- 求$\sum_{i=1}^{a}\sum_{j=1}^{b}[gcd(x,y)=d]$
- 多组输入
- $1\le d\le a,b\le 50000$

### 解题思路
- 根据之前做过的题的经验([YY的GCD](http://www.cnblogs.com/peng-ym/p/8652288.html))，那么这一题就显得十分套路~~(简单)~~了。
- 我们设：
$$f(k)=\sum_{i=1}^{a}\sum_{j=1}^{b}[gcd(i,j)=k]$$
$$F(n)=\sum_{n|k}f(k)=\lfloor\frac{a}{n}\rfloor\lfloor\frac{b}{n}\rfloor$$
则可以由莫比乌斯反演可以推出：
$$f(n)=\sum_{n|k}\mu(\lfloor\frac{k}{n}\rfloor)F(k)$$
- **(PS:如果不知道为什么要设这两个函数，可以点开我上面放的链接)**
- 设完这两个函数之后，我们便惊喜的发现，$Ans=f(d)$
- 于是就直接开始推答案：
$$Ans=\sum_{d|k}\mu(\lfloor\frac{k}{d}\rfloor)F(k)$$
枚举$\lfloor\frac{k}{d}\rfloor$设为$t$
$$Ans=\sum_{t=1}^{min(a,b)}\mu(t)\lfloor\frac{a}{td}\rfloor\lfloor\frac{b}{td}\rfloor$$
这时候，这个式子已经可以做到$O(n)$的时间复杂度了，但是因为有多组数据，所以我们再用一下**整除分块**，这题就可以做到$O(\sqrt{n})$了。
- 下附代码：

```cpp
#include<bits/stdc++.h>
#define N 60010
using namespace std;
inline void read(long long &x)
{
    x=0;
    static long long p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;	
}
bool vis[N];
long long prim[N],mu[N],sum[N],cnt;
void get_mu(long long n)
{
    mu[1]=1;
    for(long long i=2;i<=n;i++)
    {
        if(!vis[i]){mu[i]=-1;prim[++cnt]=i;}
        for(long long j=1;j<=cnt&&i*prim[j]<=n;j++)
        {
            vis[i*prim[j]]=1;
            if(i%prim[j]==0)break;
            else mu[i*prim[j]]=-mu[i];
        }
    }
    for(long long i=1;i<=n;i++)sum[i]=sum[i-1]+mu[i];
}
int main()
{
//	freopen("P3455.in","r",stdin);
//	freopen("P3455.out","w",stdout);
    long long t;
    read(t);
    get_mu(50000);
    while(t--)
    {
        static long long a,b,d;
        read(a);read(b);read(d);
        static long long max_rep,ans;
        max_rep=min(a,b);ans=0;
        for(long long l=1,r;l<=max_rep;l=r+1)
        {
            r=min(a/(a/l),b/(b/l));
            ans+=(a/(l*d))*(b/(l*d))*(sum[r]-sum[l-1]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：GoldenPotato137 (赞：29)

蒟蒻博客传送门：[戳我获得更好的阅读体验w](https://www.cnblogs.com/GoldenPotato/p/10304040.html)

---
# Solution
~~这题比[这题](https://www.cnblogs.com/GoldenPotato/p/10302839.html)不懂简单到哪里去了~~

好吧，我们来颓柿子。

**为了防止重名，以下所有柿子中的$x$既是题目中的$d$**

**为了方便讨论，以下柿子均假设$b>=a$**

**为了方便书写，以下除号均为向下取整**

题目要求的显然是：

$\large \sum_{i=1}^{a}\sum_{j=1}^{b}[gcd(i,j)=x]$

~~根据套路，~~我们这里要先把这个$x$除掉

$\large \sum_{i=1}^{a/x}\sum_{j=1}^{b/x}[gcd(i,j)=1]$

~~再根据套路~~，根据莫比乌斯函数中$[x=1]=\sum_{d|x}\mu(d)$的性质，我们把这个$gcd(i,j)$略作转换：

$\large \sum_{i=1}^{a/x}\sum_{j=1}^{b/x}\sum_{d|gcd(i,j)}\mu(d)$

~~再次根据套路~~，我们把$d$的和号改成枚举$d$的形式：

$\large \sum_{i=1}^{a/x}\sum_{j=1}^{b/x}\sum_{d=1}^{a/x}\mu(d)*[d|gcd(i,j)]$

显然，我们可以把$\mu(d)$和它前面的和号提到前面去

$\large \sum_{d=1}^{a/x}\mu(d)\sum_{i=1}^{a/x}\sum_{j=1}^{b/x}[d|gcd(i,j)]$

显然，若要$[d|gcd(i,j)]=1$，则$i,j$都必须为$d$的倍数

$\large \sum_{d=1}^{a/x}\mu(d)\frac{a}{x*d}\frac{b}{x*d}$

OK,到此为止，我们所有东西都可以算了。

前面那个$\mu(d)$可以配上后面的两个和号用整除分块的方法前缀和计算即可。如果不是很清楚的话可以看一下代码。

时间复杂度$O(m*\sqrt n)$

完结撒花✿✿ヽ(°▽°)ノ✿0

---
# Code
```cpp
//Luogu P3455 [POI2007]ZAP-Queries
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
const int N=50000+100;
const int M=50000;
int cnt_p,prime[N],mu[N];
bool noPrime[N];
void GetPrime(int n)
{
	noPrime[1]=true,mu[1]=1;
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
long long pre_mu[N];
int main()
{
	GetPrime(M);
	for(int i=1;i<=M;i++)
		pre_mu[i]=pre_mu[i-1]+mu[i];
	
	int T=read();
	for(;T>0;T--)
	{
		long long a=read(),b=read(),x=read();
		
		long long ans=0;
		if(a>b) swap(a,b);
		a/=x,b/=x;
		for(int l=1,r;l<=a;l=r+1)
		{
			r=min(a/(a/l),b/(b/l));
			ans+=(pre_mu[r]-pre_mu[l-1])*(a/l)*(b/l);
		}
		
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：Little_Jian (赞：12)

代码和之前的题解都差不多，我就发下莫比乌斯反演的推导过程吧。

推导过程（设$$n\ge m$$）
　　$$ans=\displaystyle\sum^n_{i=1}\sum^m_{j=1}{[gcd(i,j)=d]}$$
　　$$ans=\displaystyle\sum^{n/d}_{i=1}\sum^{m/d}_{j=1}{[gcd(i,j)=1]}$$
　　设$$f(x)=\displaystyle\sum^{n/d}_{i=1}\sum^{m/d}_{j=1}{[gcd(i,j)=x]}$$且$$g(x)=\displaystyle\sum^{n/d}_{i=1}\sum^{m/d}_{j=1}{[x\mid gcd(i,j)]}$$
　　易得$$g(x)=\displaystyle\sum_{x\mid d,d\le n}{f(x)}$$
　　根据莫比乌斯反演得$$f(x)=\displaystyle\sum_{x\mid d,d\le n}{\mu(x)*g(\frac{d}{x})}$$
　　设$$a=n/d,b=m/d$$
　　则$$g(x)=\displaystyle\sum^{a}_{i=1}\sum^{b}_{j=1}{[x\mid gcd(i,j)]}=\sum^{a/x}_{i=1}\sum^{b/x}_{j=1}{[1\mid gcd(i,j)]}$$
　　$$\because [x\mid gcd(i,j)]$$恒成立
　　$$\therefore g(x)=[\frac{n}{d}]*[\frac{m}{d}]$$
　　又$$\because ans = f(1)$$
　　$$\therefore ans = \displaystyle \sum_{i=1}^n{\mu(i)*g(i)} = \displaystyle \sum_{i=1}^n{\mu(i)*[\frac{n}{d}]*[\frac{m}{d}]}$$
　　这个式子就可以$$O(n)$$求了。
　　然后可以发现式子中有整除，所以就可以用数论分块改到$$O(\sqrt{n})$$了。
　　顺便宣传下自己的[博客](http://www.chenhowe.me)。

---

## 作者：xryjr233 (赞：11)

求

$\sum_{i=1}^a\sum_{j=1}^b [gcd(i,j)=d]$

设

$f(x)=\sum_{i=1}^a\sum_{j=1}^b [gcd(i,j)=x]$

$F(n)=\sum_{n|d}f(d)$

由莫比乌斯反演得

$f(n)=\sum_{n|d}\mu(\frac{d}{n})F(d)$

改枚举$\frac{d}{n}$得

$f(n)=\sum_{i=1}^{min(\lfloor\frac{a}{n}\rfloor,\lfloor\frac{b}{n}\rfloor)}\mu(i)F(in)$

则

$f(n)=\sum_{i=1}^{min(\lfloor\frac{a}{n}\rfloor,\lfloor\frac{b}{n}\rfloor)}\mu(i)\lfloor\frac{a}{in}\rfloor\lfloor\frac{b}{in}\rfloor$

预处理$\mu(i)$的前缀和，整除分块即可。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int fr=50000;
int T,a,b,d,l,r,ip[50010],p[50010],sz,mu[50010],sum[50010];
long long ans;
void getmu(){
    mu[1]=1;
    sum[1]=1;
    for(int i=2;i<=fr;i++){
        if(!ip[i]){
            p[++sz]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=sz;j++){
            if(i*p[j]>fr){
                break;
            }
            ip[i*p[j]]=1;
            if(i%p[j]==0){
                break;
            }
            mu[i*p[j]]=-mu[i];
        }
        sum[i]=sum[i-1]+mu[i];
    }
}
void scan(int &x){
    char c=getchar();
    x=0;
    while('0'>c||c>'9'){
        c=getchar();
    }
    while('0'<=c&&c<='9'){
        x*=10;
        x+=c-'0';
        c=getchar();
    }
}
void print(long long x){
    if(x>9){
        print(x/10);
    }
    putchar(x%10+'0');
}
int main(){
    scan(T);
    getmu();
    while(T--){
        scan(a);
        scan(b);
        scan(d);
        if(a>b){
            swap(a,b);
        }
        a/=d;//这里除以d之后分块的时候就不用除了
        b/=d;
        ans=0;
        l=1;
        while(l<=a){
            r=min(a/(a/l),b/(b/l));
            ans+=1ll*(sum[r]-sum[l-1])*(a/l)*(b/l);
            l=r+1;
        }
        print(ans);
        putchar('\n');
    }
    return 0;
}
```

---

## 作者：午夜飘雪 (赞：10)

一道莫比乌斯反演题。

弄了好长时间……QAQ

不知道莫比乌斯反演的看这里->[ACdreamer dalao的莫比乌斯反演介绍](http://blog.csdn.net/acdreamers/article/details/8542292)

题目大意：

“求有多少正整数对x,y，满足x<=a，y<=b，并且gcd(x,y)=d”

显然题目可以转化为

“求有多少正整数对x,y，满足x<=a/d，y<=b/d，并且gcd(x,y)=1”

方便起见设f(i)=gcd(x,y)=i的数对个数，所求即为f(1)

这个函数的值显然不好求，那么考虑反演

构造一个和它满足莫比乌斯反演的函数 F= gcd(x,y)=i的倍数 的数对个数

显然这个函数的值是很好求的

（网上一个dalao的解释：一个数对x,y要满足它们的gcd是i的倍数，则x和y中都必须包含i这个因子，所以F(i)=⌊N/i⌋·⌊M/i⌋。）

于是有反演$f(i)=\sum_{d|n} μ(d)*F(n/d)$

因为1整除所有的数，所以时间复杂度为单组$O(n)$

……然而加上数据组数会T。~~QAQ~~

于是考虑优化……

因为在连续的一段区间内n/i的值是一样的


\*例：\*

    
```cpp
    10/10=1 10/9=1 10/8=1 10/7=1 10/6=1
    10/5=2 10/4=2
    10/3=3
    10/2=5
    10/1=10
```
于是可以预处理μ的前缀和，反演时把每段n/i的值相等的部分一起算（即分块计算）
可以通过n/(n/i)找到值相等的一段的段末位置（~~手推可得(逃)~~

时间复杂度为单组$O(\sqrt{n})$

具体实现见代码

                

```cpp
    #include<iostream>
    #include<cstdio>
    #define ll long long
    #define re register
    using namespace std;
    const int N=100009;
    int T,pri[N],mu[N],cnt;
    ll sum[N];
    bool isp[N];
    int Cirno(){
        mu[1]=1;
        for(re int i=2;i<N;++i){
            if(!isp[i])pri[++cnt]=i,mu[i]=-1;
            for(re int j=1;j<=cnt;++j){
                if(i*pri[j]>=N)break;
                isp[i*pri[j]]=1;
                if(!(i%pri[j])){mu[i*pri[j]]=0;break;}
                else mu[i*pri[j]]=-mu[i];
            }
        }
        for(re int i=1;i<N;++i)sum[i]=sum[i-1]+mu[i];
    }
    void solve(int n,int m,int k){
        ll ans=0;
        n/=k,m/=k;
        int lim=min(n,m);
        for(int i=1;i<=lim;){
            ll j=min(n/(n/i),m/(m/i));
            ans+=1ll*(sum[j]-sum[i-1])*(n/i)*(m/i);
            i=j+1;
        }
        printf("%lld\n",ans);
    }
    int main(){
        Cirno();
        scanf("%d",&T);
        while(T--){
            int n,m,k;
            scanf("%d%d%d",&n,&m,&k);
            solve(n,m,k);
        }
        return 0;
    }

```

---

## 作者：_LHF_ (赞：8)

## 这是一道很经典的莫比乌斯反演题目
这是我做的第一道莫比乌斯反演，让我们一起开始吧。

首先，题目大概要求的是求n次$\sum_{i=1}^{a}\sum_{j=1}^{b}[gcd(i,j)=d]$的结果。

其中：$n \leq 50000,1 \leq d \leq a,b \leq 50000$

暴力？byebye，做完一组询问就已经$TLE$了！

行吧，让我们开始学习莫比乌斯反演吧。
### 莫比乌斯函数
通俗一点的解释：若n能被分成k个不同的质数的乘积，则$μ(n)=(-1)^k$，若不能，则$μ(n)=0$，特殊的，$μ(1)=1$。例如，$10=2×5$。所以，$μ(10)=(-1)^2=1$，因为4就是一个完全平方数(1除外)的倍数，所以4不是k个不同的质数的乘积，所以$μ(4)=0$。再比如，$30=2×3×5$，所以$μ(30)=(-1)^3=-1$

讲到这里，大家应该懂了吧，下面请大家证明一个东西：
$$[n=1]=\sum_{d|n}μ(d)$$

若n=1，则等式成立，但是如果$n≠1$呢？既然k如果是一个1除外的完全平方数的倍数，则$μ(k)=0$，所以，我们只考虑将n分解质因数后看一共有多少个不同的质因数，假设有$p$个。因为如果d选出了两个相同的质因数则$μ(d)=0$，所以我们只用考虑选出了不同的$q$个，则
$$\sum_{d|n}μ(d)=\sum_{q=1}^p(-1)^q C_p^q$$

好像有点像牛顿的二项式定理呀！
$$(a+b)^n=\sum_{i=0}^nC_n^ia^ib^{n-i}$$

所以，$\sum_{q=0}^p(-1)^q C_p^q=(1-1)^p=0 [q>0]$。好的，证明玩了。
### 狄利克雷卷积
狄利克雷卷积可以理解为一种定义新运算，符号是$ * $

定义两个函数，f和g。现在规定一个东西：
$$(f* g)(n)=\sum_{d|n}{f(d)g(\frac{n}{d})}$$

这就是狄利克雷卷积，其中狄利克雷卷积包含以下性质：

$a* b=b* a$交换律

$a* b* c=a* (b* c)$结合律

还有几个常用的函数，其中：

$ϵ(n)=[n=1]$，即只有$n=1$时这个函数的值为1

$1(n)=1$，即n为任何数时1(n)都为1

$id(n)=n$，即n为多少这个函数的值就为多少。

$d(n)=\sum_{d|n}1$，即$n$的因数的个数

$σ(n)=\sum_{d|n}d$，即$n$的因数之和
### 莫比乌斯反演
若$f* 1=g$，则$g=f* μ$（$* $为狄利克雷卷积符号）

$f* 1=g⇒f* (1* μ)=g* μ⇒f* ϵ=g* μ⇒f=g* μ$真爽(^\_^)
## 好了看看题目吧
$\sum_{i=1}^{a}\sum_{j=1}^{b}[gcd(i,j)=d]$
分析：先将$gcd(i,j)=d$想办法变成$gcd(i,j)=1$，然后套公式即可。

令$x=\lfloor{\frac{a}{d}}\rfloor,y=\lfloor{\frac{b}{d}}\rfloor,s=min(x,y)$

则原式
$$=\sum_{i=1}^{x}\sum_{j=1}^{y}[gcd(i,j)=1]$$
直接套公式

$$=\sum_{i=1}^{x}\sum_{j=1}^{y}\sum_{k|gcd(i,j)}μ(k)$$
拆开GCD之后

$$=\sum_{i=1}^{x}\sum_{j=1}^{y}\sum_{k=1}^sμ(k)[k|i][k|j]$$
然后各找各的家

$$=\sum_{k=1}^sμ(k)\sum_{i=1}^{x}[k|i]\sum_{j=1}^{y}[k|j]$$

后面的好像可以直接计算呀

$$=\sum_{k=1}^sμ(k)\lfloor{\frac{x}{k}}\rfloor\lfloor{\frac{y}{k}}\rfloor$$
大功告成

$O(n^2)⇒O(n)$

但是，$O(n)$也会超时，考虑到$\lfloor{\frac{x}{k}}\rfloor\lfloor{\frac{y}{k}}\rfloor$，还要加上一个整除分块。
### 整除分块
先推荐一道例题，**[一道数学题](https://www.luogu.com.cn/problem/U101383)**。

根据例题来分析，我们可以发现$\sum_{k=1}^n\lfloor{\frac{n}{k}}\rfloor$中$\lfloor{\frac{n}{k}}\rfloor$会重复出现很多同样的答案。利用整除分块来去重，时间复杂度大概是$O(\sqrt{n})$，基本思路就是计算出$\lfloor{\frac{n}{k}}\rfloor=a$的结果有多少个，然后再这样做下去。大家可以根据代码来参考一下：
```cpp
#include<cstdio>
using namespace std;
long long n,ans;
int main()
{
	scanf("%lld",&n);
	for(long long i=1,j;i<=n;i=j+1)
	{
		j=(n/(n/i));
		ans+=(j-i+1)*(n/i);
		ans=ans%10000000007;
	}
	printf("%lld",ans);
}
```
其实这一题也可以这样做，但是要处理两个量：$n,m$。其实业没什么大问题，只不过稍微麻烦了一点罢了，分块时要综合两个的最差情况来考虑。好了，上伪代码：
```cpp
for(int i=1,j;i<=min(n,m);i=j+1)
{
	j=min(n/(n/i),m/(m/i));
	ans+=(mobi[j]-mobi[i-1])*(n/i)*(m/i);
}
```
于是：$O(n)⇒O(\sqrt{n})$

#### 上代码：
```cpp
#pragma GCC optimize(3)
#include<cstdio>
#define min(a,b) ((a)<(b)?(a):(b))
#define N 50000
using namespace std;
int n,m,d,mobi[N+10],len,prime[N+10];
bool bz[N+10];
int main()
{
    for(int i=1;i<=N;i++) mobi[i]=1;
    for(int i=2;i<=N;i++)
    {
        if(!bz[i])
        {
            len++;
            prime[len]=i;
            mobi[i]=-1;
        }
        for(int j=1;j<=len&&prime[j]*i<=N;j++)
        {
            bz[i*prime[j]]=true;
            if(i%prime[j])
            {
                mobi[prime[j]*i]=-mobi[i];
            }
            else mobi[prime[j]*i]=0;
        }
    }
    for(int i=2;i<=N;i++)
    {
        mobi[i]+=mobi[i-1];
    }
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&d);
        n=n/d;
        m=m/d;
        int ans=0;
        for(int i=1,j;i<=min(n,m);i=j+1)
        {
            j=min(n/(n/i),m/(m/i));
            ans+=(mobi[j]-mobi[i-1])*(n/i)*(m/i);
        }
        printf("%d\n",ans);
    }
}
```
最后再扩展一下欧拉函数以及反演，其实也挺有用的。
### 欧拉函数以及反演
$φ(n)$表示在1~n-1中与n互质的个数。例如：$φ(3)=2,φ(6)=2$。特殊的：$φ(1)=1$。

反演公式：
$$\sum_{d|n}φ(d)=n$$

例如，求$\sum_{i=1}^{a}\sum_{j=1}^{b}gcd(i,j)$欧拉反演上场了，推算思路与本题的基本一样，留给大家自己思考的机会吧。

update 2019.1.10，更改Latex风格。

update 2019.1.13，增加了两个常见函数

---

## 作者：神之右大臣 (赞：5)

发现这道题的题解不是莫比乌斯反演，就是直接用到了莫比乌斯函数的性质：$\sum_{d\mid n}μ(d)=[n=1]$，并没有给出详细的证明，对于像我这样的萌新菜鸡很不友好，所以发一篇题解，来说一说它的证明；

我是用狄利克雷卷积证的，正好没学过的可以来看看；

(更好的阅读体验：**[我的博客的传送门](https://www.cnblogs.com/kamimxr/p/12160403.html))**


在说狄利克雷卷积之前，最主要的是学会整除分块，不仅仅是结论，更重要的是推导过程（详见这里：[传送门](https://www.cnblogs.com/kamimxr/p/11434286.html)）

整除分块是第一步，第二步是乱七八糟的数论函数；

首先介绍一下数论函数：定义域为正整数，值域为复数的一个子集的函数

对于数论函数$f(x)$,若对于任意互质的正整数x,y,$f(xy)=f(x)f(y)$,则该数论函数是积性函数；

如果不需要互质条件的限制，那么就称这个积性函数是完全积性函数；

常见的数论函数有如下几种：

1.单位函数：$ϵ(n)=\left\{\begin{matrix}1, & n=1 \\ 0, & n\neq 1 \end{matrix}\right.$

   即：$ϵ(n)=[n=1]$;

   它是完全积性函数；

2.标号函数：$Id_{k}(n)=n^{k}$; 

   特殊的，我们规定$Id(n)=Id_{1}(n)=n$, $Id_{0}$记作1；

　它也是完全积性函数；

3.除数函数：$σ_{k}(n)=\sum _{d\mid n}d^{k}$

　特殊的，我们规定$σ_{1}(n)$表示n的约数个数和，$σ_{0}(n)$表示n的约数个数；

　它是积性函数；

4.欧拉函数:这个相必大家都很熟悉，这里就不多说了；

5.莫比乌斯函数：$μ(n)=\left\{\begin{matrix}1,&n=1 \\ (-1)^{k},&n=p_{1}p_{2}...p_{k}\\0,&otherwise\end{matrix}\right.$

　它是一个积性函数；

 

好了，想必第一次看到这里的人一定还没记住上面那些乱七八糟的数论函数，但没关系，函数的定义都已经一一列举了出来，记不住的一边看下面一边看上面就好了；

 

接下来步入正题，也就是第三步：狄利克雷卷积正式出场；

蛤？这是啥鬼东西？

对于数论函数$f(x),g(x),h(x)$,如果$h(x)=\sum _{d\mid n}f(d)g(\frac{n}{d})$,则称h是f和g的狄利克雷卷积，记作$h(x)=f(x)\ast g(x)$,简称f卷g；

 

1.交换律$f∗g=g∗f$

2.结合律$f*(g*h)=(f*g)*h$

3.分配律$f*(g+h)=f*g+f*h$

4.有单位元$ϵ\ast f=f\ast ϵ=f$

 

下面是常用的狄利克雷卷积公式：

1.$\varphi \ast 1=Id$

  证明：

  $\varphi \ast 1\Leftrightarrow \sum_{d\mid n}\varphi (d)=Id(n)$

  设$f(d)=\sum_{1}^{n}[gcd(i,n)=d]$,则：$f(d)=\sum_{i=1}^{\frac{n}{d}}[gcd(i,\frac{n}{d})=1]=\varphi (\frac{n}{d})$

  因为f(d)的定义是1~n中和n的最大公约数为d的个数； 

  所以：$\sum _{d\mid n}f(d)=n$;

  因为：$\sum _{d\mid n}f(d)=n= \sum _{d\mid n}\varphi (\frac{n}{d})= \sum _{d\mid n}\varphi (d)=n$

  所以得证;

2.$μ\ast 1=ϵ$

  证明：

  $μ\ast 1=ϵ\Leftrightarrow \sum_{d\mid n} μ(d)=ϵ(n)$

  $n=1$时，式子显然成立；

  现在要证明的就是:当$n>1$的时候，$\sum_{d\mid n} μ(d)=0$

  根据莫比乌斯函数的定义和组合数的知识：

  $\sum_{d\mid n} μ(d)=\sum_{i=1}^{k}(-1)^{i}C(k,i)$  意义时k的不同的质因子中选取i个使其各取1个；

  根据二项式定理：$(a+b)^{n}=\sum_{i=0}^{k}C(k,i)a^{k-i}b^{i}$

  $\sum_{i=1}^{k}(-1)^{i}C(k,i)=(1-1)^{k}=0$

  得证；

还有一些不是那么常用的，可以自己试着证一证；(太懒了不想打LaTex了)

3.$μ\ast Id=\varphi $

4.$Id \ast 1=σ_{1}$

5.$1 \ast 1=σ_{0}$

 

下面放上一道经久不衰的莫比乌斯反演狄利克雷卷积例题

[传送门：[POI2007]ZAP-Queries](https://www.luogu.com.cn/problem/P3455)

题目大意：求：$\sum_{i=1}^{n}\sum_{j-1}^{m}[gcd(i,j)=k]$

$=\sum_{i=1}^{\frac{n}{k}}\sum_{j-1}^{\frac{m}{k}}[gcd(i,j)=1]$

$=\sum_{i=1}^{\frac{n}{k}}\sum_{j-1}^{\frac{m}{k}}ϵ(gcd(i,j))$

由狄利克雷卷积可知：$μ\ast 1=ϵ$(忘了的看上面迪利克雷卷积常用公式那一块)

$=\sum_{i=1}^{\frac{n}{k}}\sum_{j-1}^{\frac{m}{k}}\sum_{d\mid gcd(i,j)}μ(d)$

这时候发现式子好像推不动的样子了，所以改变枚举的东西(i,j共同的约数d):

$=\sum_{d=1}^{\frac{min(n,m)}{k}}μ(d)\sum_{d\mid i\bigcap i\leqslant \frac{n}{k}}^{}  \sum_{d\mid j \bigcap j\leqslant \frac{m}{k}}^{}1$

$=\sum_{d=1}^{\frac{min(n,m)}{k}}μ(d)\frac{n}{k}\frac{m}{k}$

这时候式子就变得非常非常可爱了；

我们可以用欧拉筛来快速筛出1~n的莫比乌斯函数的前缀和；(不会的可以一边看代码，一边看莫比乌斯函数的定义，通过质数p来枚举p的倍数求得莫比乌斯函数)

而对于式子后面的部分，就用到了文章开头提到的东西:整除分块；

这样我们可以在$\sqrt n$的复杂度下求得这个式子的值了；

总复杂度是($m\sqrt n$);
```cpp
#include <bits/stdc++.h>
#define inc(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
int miu[50010],pre[50010],vis[50010];
void el(){
	inc(i,1,50000) miu[i]=1,vis[i]=0;
	inc(i,2,50000){
		if(vis[i]) continue;
		miu[i]=-1;
		for(int j=2*i;j<=50000;j+=i){
			vis[j]=1;
			if((j/i)%i==0) miu[j]=0;
			else miu[j]*=-1;
		}
	}
	inc(i,1,50000) pre[i]=pre[i-1]+miu[i];
}
int main()
{
	el();
	int T; cin>>T;
	while(T--){
		int a,b,x;
		scanf("%d%d%d",&a,&b,&x);
		if(a>b) swap(a,b);
		a/=x; b/=x;
		long long ans=0;
		for(int l=1,r;l<=a;l=r+1){
			r=min(a/(a/l),b/(b/l));
			ans+=(long long)(pre[r]-pre[l-1])*(long long)(a/l)*(long long)(b/l);
		}
		printf("%lld\n",ans);
	}
}
```


---

## 作者：Regimes (赞：4)

这是一道比较简单的莫反题，还记得某巨巨说过，可以用莫比乌斯反

演解决的问题绝大部分都可以用$\mu$函数的性质解决。

然而我太菜了

$$\sum_{i=1}^{n}\sum_{j=1}^{m}gcd(i,j)$$

$$\sum_{d=1}^nd*\sum_{i=1}^{[n/d]}\sum_{j=1}^{[m/d]}[gcd(i,j)==1]$$

即：

$$\sum_{d=1}^nd*\sum_{i=1}^{[n/d]}\sum_{j=1}^{[m/d]}\sum_{k|gcd(i,j)}\mu(k)$$

也就是：


$$\sum_{d=1}^nd*\sum_{k=1}^{[n/d]}\mu(k)\sum_{i=1}^{[n/(kd)]}\sum_{j=1}^{[n/kd]}1$$

然后：

$$\sum_{d=1}^nd*\sum_{k=1}^{[n/d]}\mu(k)*(1+[n/kd])^2*([n/kd])^2$$

于是我们发现后面的的那堆平方可以$O(1)$算出来，然后两次数论分

块就可以求出来了

蒟蒻的代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define Mod 20101009
#define Min(x,y) x>y?y:x
#define N 10000055
#define int long long
int mu[N] , g[N] , vis[N] , p[N] ;
int num ;
void Init(int x)
{
    mu[1] = 1 ;
    g[1] = 1 ;
    for(int i = 2 ; i <= x ; i++ ){
        if( !vis[i] ) p[++num] = i , mu[i] = -1 ;
        for(int j = 1 ; j <= num && p[j] * i <= x ; j++ ){
            vis[ p[j] * i ] = 1 ;
            if( i % p[j] == 0 ) break ;
            mu[ p[j] * i ] = -mu[i] ;
        }
        g[i] = ( g[ i - 1 ] + 1ll*i * i % Mod * ( mu[i] + Mod ) ) % Mod ;
    }
    return ;
}
int Sum(int x )
{
    return ( ( x + 1 ) * x / 2 ) % Mod ;
}
int Ask(int x ,int y)
{
    int ans = 0 ;
    if( x > y ) swap( x , y ) ;
    for(int l = 1 , r ; l <= x ; l = r + 1 ){
        r = Min( x / ( x / l ) , y / ( y / l ) ) ;
        ans = ( ans + 1ll*( g[r] - g[l - 1] + Mod ) % Mod * ( Sum( x / l ) * Sum( y / l ) ) % Mod ) % Mod ;
    }
    return ans % Mod ;
}
signed main()
{
    int n , m ;
    scanf("%lld%lld" , &n , &m ) ;
    if( n > m ) swap( n , m ) ;
    Init(m+10) ;
    long long ans = 0 ;
    for(int l = 1 , r ; l <= n ; l = r + 1 ){
        r = Min( n / ( n / l ) , m / ( m / l ) ) ;
        ans = ( ans + 1ll * ( 1ll * ( r - l + 1 ) * ( l + r ) / 2  ) % Mod * Ask( n / l , m / l ) % Mod ) % Mod ;
    }
    printf("%lld\n" , ans % Mod ) ;
}
```


---

## 作者：zcysky (赞：4)

同 Problem b但是还要简单一点。

```cpp
#include<bits/stdc++.h>
#define N 100005
#define LL long long
using namespace std;
int prime[N],mu[N],s[N],cnt=0;
bool vis[N];
void read(int &x){
    char ch;int f=1;x=0;
    do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
    do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
    x*=f;
}
void calcmu(){
    cnt=0;mu[1]=1;
    memset(vis,true,sizeof(vis));
    for(int i=2;i<N;i++){
        if(vis[i])prime[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt;j++){
            int t=prime[j]*i;
            if(t>N)break;
            vis[t]=false;
            if(i%prime[j]==0){mu[t]=0;break;}
            mu[t]-=mu[i];
        }
    }
    s[0]=0;
    for(int i=1;i<=N;i++)s[i]=s[i-1]+mu[i];
}
LL calcval(int n,int m,int k){
    LL ans=0;n/=k;m/=k;int i=1;
    if(n>m)swap(n,m);
    while(i<=n){
        int j=min(n/(n/i),m/(m/i));
        ans+=1LL*(s[j]-s[i-1])*(n/i)*(m/i);i=j+1;
    }
    //cout<<ans<<endl;
    return ans;
}
int x,y,d;
int main(){
    int T;scanf("%d",&T);calcmu();
    while(T--){
        read(x);read(y);read(d);
        printf("%lld\n",calcval(x,y,d));
    }
    return 0;
}
```

---

## 作者：nekko (赞：3)

## 题目描述

有$T$组询问，每次给定整数$a,b,d$，求有多少对正整数$x,y$，满足$x \le a \wedge y \le b \wedge (x,y)=d$

$1 \le a,b,d,T \le 50000$

## 题解

$\begin{aligned}a \le b \\\sum_{i=1}^{a}\sum_{j=1}^{b}[(i,j)=d] &=\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}[(i,j)=1] \\&=\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}\sum_{d' \mid (i,j)}\mu(d') \\&=\sum_{i=1}^{\lfloor \frac{a}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{b}{d} \rfloor}\sum_{d' \mid i \wedge d' \mid j}\mu(d') \\&=\sum_{d'=1}^{\lfloor \frac{a}{d} \rfloor}\mu(d')\sum_{d' \mid i}^{\lfloor \frac{a}{d} \rfloor}\sum_{d' \mid j}^{\lfloor \frac{b}{d} \rfloor}1 \\&=\sum_{d'=1}^{\lfloor \frac{a}{d} \rfloor}\mu(d') \lfloor \frac{a}{dd'} \rfloor \lfloor \frac{b}{dd'} \rfloor\end{aligned}$

$\lfloor \frac{a}{dd'} \rfloor \lfloor \frac{b}{dd'} \rfloor$的取值只有$O(\sqrt a + \sqrt b)$种，预处理$\mu$的前缀和，单次询问可以$O(\sqrt n)$计算

## 代码

``` cpp
#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 50000 + 10;

int n, m, d, mu[N], vis[N], p[N], tot;

void sol() {
    ll ans = 0;
    scanf("%d%d%d", &n, &m, &d); if(n > m) swap(n, m);
    n /= d, m /= d;
    for(int i = 1, j ; i <= n ; i = j + 1) {
        j = min(n / (n / i), m / (m / i));
        ans += (ll) (mu[j] - mu[i - 1]) * (n / i) * (m / i);
    }
    printf("%lld\n", ans);
}

int main() {
    mu[1] = 1;
    for(int i = 2 ; i <= 50000 ; ++ i) {
        if(!vis[i]) mu[i] = -1, p[++ tot] = i;
        for(int j = 1 ; j <= tot && (ll) i * p[j] <= 50000 ; ++ j) {
            vis[i * p[j]] = 1;
            if(i % p[j] == 0) break;
            mu[i * p[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
    int T; scanf("%d", &T);
    while(T --) sol();
}
```


---

## 作者：huangzirui (赞：1)

题意：

求：
$$\sum_{i=1}^n\sum_{j=1}^m{\gcd(i,j)=d}$$

---
非常好的莫比乌斯入门题。

套路是所有里面最简单的，非常值得新手练习。

接下来建议的几道题：[P1447](https://www.luogu.com.cn/problem/P1447) [P2257](https://www.luogu.com.cn/problem/P2257)

把 $i,j$ 都乘上一个 $d$ ，有：
$$\sum_{i=1}^{\left\lfloor{\frac{n}{d}}\right\rfloor}\sum_{j=1}^{\left\lfloor{\frac{m}{d}}\right\rfloor}\gcd(i,j)=1$$

这里 $[\gcd(i,j)=1]$ 可以写成 $\epsilon(\gcd(i,j))$ 的形式。

由于 $\epsilon = \mu * 1$ ：
$$\sum_{i=1}^{\left\lfloor{\frac{n}{d}}\right\rfloor}\sum_{j=1}^{\left\lfloor{\frac{m}{d}}\right\rfloor}\sum_{p|\gcd(i,j)}\mu(p)$$

根据 $\gcd$ 性质：
$$\sum_{i=1}^{\left\lfloor{\frac{n}{d}}\right\rfloor}\sum_{j=1}^{\left\lfloor{\frac{m}{d}}\right\rfloor}\sum_{p|i,j}\mu(p)$$

改变枚举顺序：
$$\sum_{p=1}^{\left\lfloor{\frac{n}{d}}\right\rfloor}\sum_{i=1}^{\left\lfloor{\frac{n}{d}}\right\rfloor}\sum_{j=1}^{\left\lfloor{\frac{m}{d}}\right\rfloor}\mu(p)[p|i,j]$$

再给 $i,j$ 乘上 $p$
$$\sum_{p=1}^{\left\lfloor{\frac{n}{d}}\right\rfloor}\mu(p)\sum_{i=1}^{\left\lfloor{\frac{n}{dp}}\right\rfloor}\sum_{j=1}^{\left\lfloor{\frac{m}{dp}}\right\rfloor}$$

后面的式子没有什么实际含义直接拆掉：
$$\sum_{p=1}^{\left\lfloor{\frac{n}{d}}\right\rfloor}\mu(p){\left\lfloor{\frac{n}{dp}}\right\rfloor}{\left\lfloor{\frac{m}{dp}}\right\rfloor}$$

到这里我们已经发现可以 $O(n)$ 做了。

利用整除分块还可以优化成 $O(\sqrt n)$。

总复杂度 $O(T\sqrt n)$ 可以通过此题。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	char c=getchar();ll x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const ll N=50010;
ll prime[N],is_prime[N],num,mu[N],Mu[N];
ll i,j,k,n,m;
void init(){
	for(ll i=2;i<N;i++)is_prime[i]=1;
	mu[1]=1;
	for(ll i=2;i<N;i++){
		if(is_prime[i])prime[++num]=i,mu[i]=-1;
		for(ll j=1;j<=num && i*prime[j]<N;j++){
			is_prime[i*prime[j]]=0;
			if(i%prime[j]==0)break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(ll i=1;i<N;i++)Mu[i]=Mu[i-1]+mu[i];
}
ll T;
ll ans;
int main(){
	init();
	cin>>T;
	while(T--){
		ans=0;
		cin>>n>>m>>k;
		if(n>m)swap(n,m);
		for(ll l=1,r=0;l<=n;l=r+1){
			r=min(n/(n/l),m/(m/l));
			ans+=(n/l/k)*(m/l/k)*(Mu[r]-Mu[l-1]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：kkxhh (赞：1)

$$ \sum_{i=1}^{x} \sum_{j=1}^{y} [gcd(i,j)=d] $$

$$=\sum_{i=1}^{\lfloor \frac{x}{d} \rfloor} \sum_{i=1}^{\lfloor \frac{y}{d} \rfloor} [gcd(i,j)=1]$$

$$=\sum_{i=1}^{\lfloor \frac{x}{d} \rfloor} \sum_{i=1}^{\lfloor \frac{y}{d} \rfloor} \sum_{k|gcd(i,j)} \mu(k)$$

$$=\sum_{k=1}^{\lfloor \frac{min(x,y)}{d} \rfloor} \mu(k) \lfloor \frac{x}{dk} \rfloor \lfloor \frac{y}{dk} \rfloor$$

我们可以发现有 $x,y$ 的地方就有 $\frac{1}{d}$ ，于是对于每次询问我们直接将 $x,y$ 除以 $d$ ，接下来就是一个裸的数论分块了

代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define LL long long

const int maxsize=50000;
int t,vis[50010],prime[50010],siz,mu[50010],sum[50010];

inline int read(){
    int num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?0:k,c=getchar();
    while(c>='0' && c<='9') num=num*10+c-'0',c=getchar();
    return k?num:-num;
}

void sieve(){
	vis[0]=vis[1]=1; mu[1]=1;
	for(int i=2;i<=maxsize;i++){
		if(!vis[i]) prime[++siz]=i,mu[i]=-1;
		for(int j=1;i*prime[j]<=maxsize;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0) break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=maxsize;i++) mu[i]+=mu[i-1];
}

LL query(int a,int b,int d){
	LL ans=0; a/=d; b/=d;
	if(a>b) swap(a,b);
	for(int l=1,r=0;l<=a;l=r+1){
		r=min(a/(a/l),b/(b/l));
		ans+=(LL)(mu[r]-mu[l-1])*(a/l)*(b/l);
	}
	return ans;
}

int main(){
	t=read(); sieve();
	while(t--){
		int x=read(),y=read(),d=read();
		printf("%lld\n",query(x,y,d));
	}
    return 0;
}
```

---

## 作者：hl666 (赞：1)

由于之前做了[Luogu P2257 YY的GCD](https://www.luogu.org/problemnew/show/P2257)，这里的做法就十分套路了。

建议先看[上面一题的推导](https://www.cnblogs.com/cjjsb/p/9852268.html)，这里的话就略去一些共性的地方了。

还是和之前一样设：

$$f(d)=\sum_{i=1}^a \sum_{j=1}^b[\gcd(i,j)=d]$$

$$F(n)=\sum_{n|d} f(d)=\lfloor\frac{a}{n}\rfloor\lfloor\frac{b}{n}\rfloor$$

还是**莫比乌斯反演定理**推出：

$$f(n)=\sum_{n|d}\mu(\lfloor\frac{d}{n}\rfloor)F(d)$$

这时我们发现，不像上面一题那么繁琐~~还要对$f(n)$求和~~，这里$ans=f(d)$

所以可以直接开始推导答案：

$$ans=\sum_{d|k}\mu(\lfloor\frac{k}{d}\rfloor)F(k)$$

还是考虑换个东西枚举，我们设$\lfloor\frac{k}{d}\rfloor=t$，枚举$t$则有：

$$ans=\sum_{t=1}^{\min(\lfloor\frac{a}{d}\rfloor,\lfloor\frac{b}{d}\rfloor)}\mu(t)\lfloor\frac{a}{t\cdot d}\rfloor\lfloor\frac{b}{t\cdot d}\rfloor$$

这个式子已经变成$O(n)$的了，还是注意到$\lfloor\frac{a}{t\cdot d}\rfloor\lfloor\frac{b}{t\cdot d}\rfloor$可以**除法分块**，然后只需要对莫比乌斯函数做一个前缀和即可单次$O(\sqrt n)$。

CODE

```cpp
#include<cstdio>
#include<cctype>
#define RI register int
using namespace std;
const int P=50005;
int t,n,m,d,prime[P+5],cnt,mu[P+5],sum[P+5]; long long ans; bool vis[P+5];
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
    vis[1]=mu[1]=1; RI i,j; for (i=2;i<=P;++i)
    {
        if (!vis[i]) prime[++cnt]=i,mu[i]=-1;
        for (j=1;j<=cnt&&i*Pi<=P;++j)
        {
            vis[i*Pi]=1; if (i%Pi) mu[i*Pi]=-mu[i]; else break;
        }
    }
    for (i=1;i<=P;++i) sum[i]=sum[i-1]+mu[i];
}
#undef Pi
inline int min(int a,int b)
{
    return a<b?a:b;
}
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    for (Euler(),F.read(t);t;--t)
    {
        F.read(n); F.read(m); F.read(d); ans=0; int lim=min(n/d,m/d);
        for (RI l=1,r;l<=lim;l=r+1)
        {
            r=min(n/(n/l),m/(m/l)); ans+=1LL*(n/(l*d))*(m/(l*d))*(sum[r]-sum[l-1]);
        }
        F.write(ans);
    }
    return F.Fend(),0;
}
```

---

## 作者：MFJ0v0 (赞：1)

~~这是一道明显的莫比乌斯反演题~~
### 在你没有思路的时候，你可以从多个方面考虑考虑，就会发现这道题可以用莫比乌斯反演来做。
###  在做此题前，需要学习积性函数 、 Dirichlet 卷积 、 莫比乌斯函数的前缀知识。
### 这里简单介绍一下它们
### 积性函数：若x与y互质，且f(x)f(y)=f(xy)那么它就是个积性函数。欧拉函数，莫比乌斯函数，Dirichlet 卷积 ，因子个数函数都是积性函数！
### 莫比乌斯函数μ：俗一点吧，μ（n）中，当n为1时，μ（n）值为1，当n有平方因子的时候，μ（n）为0，其他时候，μ（n）是-1的k次方（k是n本质不同的质因子数）
### 对于公式嘛，楼上的dalao们已经反演出了最终公式，我来水一下做法
### gcd，积性函数，你想起了什么
### 对了！大名鼎鼎的欧拉筛！
### 我们可以在欧拉筛中顺便计算积性函数！
### 上代码
```cpp
void init(int n){
	noP[1]=true,m[1]=1;
	for(int i=2;i<=n;i++){
		if(noP[i]==false)
			p[++cnt]=i,m[i]=-1;
		for(int j=1;j<=cnt&&i*p[j]<=n;j++){
			noP[i*p[j]]=true;	
			if(i%p[j]==0){
				m[i*p[j]]=0;
				break;
			}
			m[i*p[j]]=m[i]*m[p[j]];
		}	
	} 
}

```
这不就好起来了嘛？
### 欧拉筛好了，剩下的呢？？？
### 对了，如果你不想瞬间爆炸，就一定要用数组记录一下前缀和！
话不多说上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 50000 + 100;
const int M = 50000;
int cnt, p[N], m[N],t,a,b,d,ans;
long long preM[N];
bool noP[N];
void init(int n){
	noP[1]=true,m[1]=1;
	for(int i=2;i<=n;i++){
		if(noP[i]==false)
			p[++cnt]=i,m[i]=-1;
		for(int j=1;j<=cnt&&i*p[j]<=n;j++){
			noP[i*p[j]]=true;	
			if(i%p[j]==0){
				m[i*p[j]]=0;
				break;
			}
			m[i*p[j]]=m[i]*m[p[j]];
		}	
	} 
}
int main(){
	init(M);
	for(int i=1;i<=M;i++){
		preM[i]=preM[i-1]+m[i];//计算前缀和
	}
	cin>>t;
	while(t--){
		ans=0;
		cin>>a>>b>>d;
		if(a>b) swap(a,b);
		a/=d; b/=d;
		for (int l=1,r;l<=a;l=r+1){
			r=min(a/(a/l),b/(b/l));
			ans+=(preM[r]-preM[l-1])*(a/l)*(b/l);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
### 做完此题还可以做一做P2522 [HAOI2011]Problem b
### 没事可以上OI WIKI看看
### 看不懂怎么办？
　~~不慌吃口药~~
### 我教你个超好用的方法
### 好好学，认真学，总有一天你成dalao
### 看看我空间就好了
~~其实我只是想水一篇题解嘿嘿嘿~~


~~第一次发题解竟然因排版被拒了！！~~

---

## 作者：kczno1 (赞：1)

x=[1,a],y=[1,b],[gcd(x,y)=d]

设n=a/d,m=b/d,n<m。

<=>x=[1,n],y=[1,m],[gcd(x,y)=1]

根据d|n,μ(d)=[n==1]

<=>x=[1,n],y=[1,m],d|gcd(x,y),μ(d)

根据d|gcd(x,y)<=>d|x and d|y

<=>d=[1,n],d|x,d|y,μ(d)
<=>d=[1,n],(n/d)\*(m/d)\*μ(d)

根据n/d只有根号种取值，预处理μ的前缀和，可以做到根号时间。

```cpp
#include<bits/stdc++.h>
using std::min;

#define ll long long

const int N=50000;
int miu[N+5];
bool vis[N+5];
int p[N],top,i,j,x,n,m;
void shai()
{
    miu[1]=1;
    for(i=2;i<=N;++i)
    {
        if(!vis[i]) { miu[i]=-1;p[++top]=i; }
        for(j=1;(n=i*(x=p[j]))<=N;++j)
        {
            vis[n]=1;
            if(i%x) miu[n]=miu[i]*miu[x];
            else break;
        }
    }
    for(i=2;i<=N;++i) miu[i]+=miu[i-1];
}

ll solve()
{
    ll ans=0;
    top=min(n,m);
    i=1;
    while(i<=top)
    {
        j=min(n/(n/i),m/(m/i));
        ans+=(ll)(miu[j]-miu[i-1])*(n/i)*(m/i); 
        i=j+1;
    }
    return ans;
}

int main()
{
    freopen("1.in","r",stdin);
    shai();
    int tt;
    scanf("%d",&tt);
    while(tt--)
    {
        scanf("%d%d%d",&n,&m,&x);
        n/=x;m/=x;
        printf("%lld\n",solve());
    }
}
```

---

## 作者：Lates (赞：0)

此题为套路题

## 前置芝士

数论分块，莫比乌斯反演

## 做法

首先可以看出题目求

$$\sum_{i=1}^{a} \sum_{j=1}^{b}[gcd(i,j)=d]$$

首先很套路地转化为

$$\sum_{i=1}^{\left \lfloor \frac{a}{d} \right \rfloor}\sum_{i=1}^{\left \lfloor \frac{b}{d} \right \rfloor}[gcd(i,j)=1]$$

有一个数论函数 $\varepsilon(x)$，当$x=1$时，函数值为$1$否则为$0$

后面的$[gcd(i,j)=1]$可以用$\varepsilon(gcd(i,j))$

$$\sum_{i=1}^{\left \lfloor \frac{a}{d} \right \rfloor}\sum_{i=1}^{\left \lfloor \frac{b}{d} \right \rfloor}\varepsilon(gcd(i,j))$$

用 $\mu*1 = \varepsilon$ 反演

$$\sum_{i=1}^{\left \lfloor \frac{a}{d} \right \rfloor}\sum_{i=1}^{\left \lfloor \frac{b}{d} \right \rfloor}\sum_{p|gcd(i,j)}\mu(p)$$

改变求和顺序

$$\sum_{p=1}\mu(p)\sum_{i=1}^{\left \lfloor \frac{a}{d} \right\rfloor}[p \ | \ i]\sum_{j=1}^{\left \lfloor \frac{b}{d} \right \rfloor}[p \ |\  j]$$

后面两个$\sum$，可以看出求的是$d$有多少个倍数在$\left \lfloor \frac{a}{d} \right\rfloor$和$\left \lfloor \frac{b}{d} \right \rfloor$中。显然，答案分别为$\left \lfloor \frac{a}{pd} \right\rfloor$和
$\left \lfloor \frac{b}{pd} \right\rfloor$

转化为

$$\sum_{p=1}\mu(p)\left \lfloor \frac{a}{pd} \right\rfloor\left \lfloor \frac{b}{pd} \right\rfloor$$

然后数论分块加前缀和就做完了

我Code里的是先把$a/d,b/d$，再做数论分块，这样常数会小一点。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
#define int long long 
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
const int MAX=50100;
int mu[MAX],pri[MAX],f[MAX],tot;
inline void Getmu(int N){
	mu[1]=1;
	for(register int i=2;i<=N;++i){
		if(!f[i]){
			mu[i]=-1;
			pri[++tot]=i;
		} 
		for(register int j=1;j<=tot&&i*pri[j]<=N;++j){
			f[i*pri[j]]=1;
			if(i%pri[j]==0)break;
			mu[i*pri[j]]=-mu[i];
		}
	}
	for(register int i=1;i<=N;++i)mu[i]+=mu[i-1];
} 
int ans;
inline int solve(int n,int m){
	ans=0;
	if(n>m)n^=m^=n^=m;
	for(register int l=1,r;l<=n;l=r+1){
		r=min(n/(n/l),m/(m/l));
		ans+=(mu[r]-mu[l-1])*(n/l)*(m/l);
	}
	return ans;
}
int t,a,b,d;
signed main(){
	Getmu(50000);
	t=read();
	while(t--){
		a=read(),b=read(),d=read();
		a/=d,b/=d;
		printf("%lld\n",solve(a,b));
	}
	return 0;
}


```



---

## 作者：arfa (赞：0)

买个广告 : [$\text{Blog}$](https://www.cnblogs.com/FibonacciHeap/articles/10984275.html) , 自我感觉讲得很清楚 。

大概是这样子的 : 

$$\begin{aligned} & \sum\limits^{n}_{i=1}\sum\limits^{m}_{j=1} [\gcd(i,j)=k] \\= & \sum\limits^{\lfloor\frac{n}{k}\rfloor}_{i=1}\sum\limits^{\lfloor\frac{m}{k}\rfloor}_{j=1} [\gcd(i,j)=1] \\ = & \sum\limits^{\lfloor\frac{n}{k}\rfloor}_{i=1}\sum\limits^{\lfloor\frac{m}{k}\rfloor}_{j=1} \sum\limits_{d|\gcd(i,j)} \mu(d) \\= & \sum\limits^{\min\{\lfloor\frac{n}{k}\rfloor,\lfloor\frac{m}{k}\rfloor\}}_{d=1} \mu(d) \sum\limits^{\lfloor\frac{n}{k}\rfloor}_{i=1}\sum\limits^{\lfloor\frac{m}{k}\rfloor}_{j=1} [d|\gcd(i,j)] \\= & \sum\limits^{\min\{\lfloor\frac{n}{k}\rfloor,\lfloor\frac{m}{k}\rfloor\}}_{d=1} \mu(d) \times \lfloor\frac{n}{dk}\rfloor \lfloor\frac{m}{dk}\rfloor \\\end{aligned}$$

- 第一步转化 : 规律。假设 $k$ 就是 $\gcd(i,j)$ ,那么 $\gcd(\frac{n}{k},\frac{m}{k})=1$。
- 第三步转化 : 直接用 $d$ 来枚举每一个 $\gcd(i,j)$ 即可。
- 第四步转化 : 等差公式 , 后面那一坨直接数论分块即可。

然后注意一下后面那个东西不能拆 , 所以前缀和要套进去搞。

还有就是这里的 $\mu$ 不需要 $O(n)$ 处理 , 直接按照定理 $\sum\limits_{d|n} -\mu(d)[d \not= n]=\mu(n)$ ($n \not= 1$) 就可以了 , 复杂度是 $O(n \log n)$ 的。总复杂度 $O(n^{\frac{3}{2}}+n \log n)$ 喽。


```pascal
Uses math;
 
Const
    total=50000+10;
 
var
    incea,mobius:array[-1..total] of shortint;
    i,j,test,n,m,k:longint;
 
function MaBlTe(num:longint):longint;
var i,j:longint;
begin
    i:=1; j:=0; n:=n div k; m:=m div k; MaBlTe:=0;
    while i<=num do
    begin
        j:=min(n div (n div i),m div (m div i));
        inc(MaBlTe,(n div i)*(m div i)*(incea[j]-incea[i-1])); i:=j+1;
    end;
end;
 
begin
    read(test); mobius[1]:=1;
    for i:=1 to total do for j:=2 to total div i+1 do begin if i*j>total then break; dec(mobius[i*j],mobius[i]); end;
    for i:=1 to total do incea[i]:=incea[i-1]+mobius[i];
    for i:=1 to test do begin read(n,m,k); writeln(MaBlTe(min(n div k,m div k))); end;
end.
```

---

## 作者：chihik (赞：0)

显然，题目求的是：

$$\sum_{i=1}^n\sum_{j=1}^m[gcd(i,j)=d]$$

$$\sum_{i=1}^{ \lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor}[gcd(i,j)=1] $$

有一个与莫比乌斯函数有关的性质：$\sum_{d | n}\mu(d)=[n=1]$

$$\sum_{i=1}^{ \lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor \frac{m}{d} \rfloor}\sum_{k|gcd(i,j)}\mu(k)$$

将 $k$ 往前移，然后是一个非常经典的式子了

$$\sum_{k=1}^{min(\lfloor \frac{n}{d} \rfloor,\lfloor \frac{m}{d} \rfloor)}\mu(k)\lfloor \frac{n}{kd} \rfloor \lfloor \frac{m}{kd} \rfloor$$

用数论分块即可解决。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 10000000;
int t , a , b , d;

int k , prime[ MAXN + 5 ] , mu[ MAXN + 5 ] , f[ MAXN + 5 ];
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
	for( int i = 1 ; i <= MAXN ; i ++ )
		f[ i ] = f[ i - 1 ] + mu[ i ];
}

long long solve( int n , int m ) {
    long long Ans = 0;
    for( int l = 1 , r ; l <= min( n / d , m / d ) ; l = r + 1 ) {
        r = min( n / ( n / l ) , m / ( m / l ) );
        Ans += 1ll * ( n / l / d ) * ( m / l / d ) *  ( f[ r ] - f[ l - 1 ] );
    }
    return Ans;
}

int main( ) {
	sieve( );
	scanf("%d",&t);
	while( t -- ) {
		scanf("%d %d %d",&a,&b,&d);
		printf("%lld\n",solve( a , b ));
	}
	return 0;
}
```

---

## 作者：Huah (赞：0)

莫比乌斯反演

我们要求的是(i<=a,j<=b)gcd(i,j)==d的个数，即gcd(i/d,j/d)==1的(i,j)数

设f(k)为gcd(i,j)==k的数的(i,j)的对数

再设g(n)为gcd(i,j)%n==0的(i,j)的对数

设k=min(a/d,b/d),则gcd(i,j)最大不会超过k,则

g(1)=f(1)+f(2)+f(3)+...f(k)

g(2)=f(2)+f(4)+f(6)+...

g(3)=f(3)+f(6)+...

...

g(k)=f(k)

可以发现g(n)是很容易计算的，即g(n)=(a/n)\*(b/n)，这里的运算是整除运算

a/n得到i<=a能整除n的i的个数，b/n得到j<=bn能整除n的b的个数

则根据乘法原理，gcd(i,j)%n==0的i,j的对数g(n)=(a/n)\*(b/n)

而我们的答案就是f(1)，可以发现g(n)很好计算而f(k)很难计算，我们就根据莫比乌斯反演来计算了,f(1)=(求和1<=i<=k)mu(i)\*(a/i)\*(b/i)

但是直接枚举1~k这样的时间复杂度是线性的，但因为是整除运算，很大一段a/i,b/i都是相同的，就用数论分块来分块一下。
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e4+5;
int n,a,b,d,mu[N],sum[N];
int tot,p[N];
bool vis[N];
void init()
{
    mu[1]=1;
    for(int i=2;i<N;i++)
    {
        if(!vis[i]) {mu[i]=-1;p[++tot]=i;}
        for(int j=1;j<=tot&&i*p[j]<N;j++)
        {
            vis[i*p[j]]=true;
            if(i%p[j]==0) break;
            mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<N;i++)
        sum[i]=sum[i-1]+mu[i];
}
int read()
{
    char c=getchar();int x=0;
    while(c<'0'&&c>'9') c=getchar();
    while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-'0',c=getchar();
    return x;
}
int main()
{
    init();
    n=read();
    while(n--)
    {
        a=read();b=read();d=read();
        a/=d;b/=d;
        static int mx;
        static ll ans;
        mx=min(a,b);ans=0;
        for(register int l=1,r=1;l<=mx;l=r+1)
        {
            r=min(a/(a/l),b/(b/l));
            ans+=(ll)(sum[r]-sum[l-1])*(a/l)*(b/l);
        }
        printf("%lld\n",ans);
    }
}

```


---

## 作者：灯芯糕 (赞：0)

## $solution:$



唉，数论实在有点烂了，昨天还会的，今天就不会了，周末刚证明的，今天全忘了，还不如早点写好题解。

这题首先我们可以列出来答案就是：

### $ans=\sum_{i=1}^{a}{\sum_{j=1}^{b}{[gcd(i,j)==d]}}$

我们发现后面那个东西（只有$gcd(i,j)==d$ 时才为一）跟莫比乌斯很像，莫比乌斯是（只有$n==$1 才为一），所以我们再尝试转化一下（把d转化成1）：

### $ans=\sum_{i=1}^{\frac{a}{d}}{\sum_{j=1}^{\frac{b}{d}}{[gcd(i,j)==1]}}$

于是我们就可以把后面那个东西用莫比乌斯函数的第一条性质转换成这样：

### $ans=\sum_{i=1}^{\frac{a}{d}}{\sum_{j=1}^{\frac{b}{d}}{\sum_{k|gcd(i,j)}{\mu(k)}}}$

但是这样显然还不够，我们想办法把莫比乌斯的式子挪到前面去：

### $ans=\sum_{k}^{min(a,b)}{\mu(k)}{\sum_{i=1}^{\frac{a}{d}}{\sum_{j=1}^{\frac{b}{d}}{[k|gcd(i,j)]}}}$

这个其实就相当于我们从小到大枚举k，但是我们是从上面那个式子转化过来的，所以必须满足$[k|gcd(i,j)]$ 这个条件。好了，现在我们肉眼观察一下，发现如下的东西：

### ${\sum_{i=1}^{\frac{a}{d}}{\sum_{j=1}^{\frac{b}{d}}{[k|gcd(i,j)]}}}=\lfloor \frac{\lfloor \frac{a}{d} \rfloor}{k}  \rfloor \times \lfloor \frac{\lfloor \frac{b}{d} \rfloor}{k}  \rfloor=\lfloor \frac{a}{d\times k}  \rfloor \times \lfloor \frac{b}{d\times k}  \rfloor$

### $ans=\sum_{k}^{min(a,b)}{\mu(k)\times \lfloor \frac{a}{d\times k}  \rfloor \times \lfloor \frac{b}{d\times k}  \rfloor}$

然后我们发现这样子的复杂度是$O(min(a,b)) $ 的，然而它的询问次数太多。于是出现了一个很奇妙的东西：整除分块（又叫数论分块）。举个栗子：

$\frac{10}{1}=10$

$\frac{10}{2}=5$

$\frac{10}{3}=3$

$\frac{10}{4}=\frac{10}{5}=2$

$\frac{10}{6}=\frac{10}{7}=\frac{10}{8}=\frac{10}{9}=\frac{10}{10}=1$

我们发现分子相同分母越大，则出现相同结果的概率越高，所以我们可以一次求出某一段相同结果的左端点和右端点（假设这一段的结果都为y，则这一段的最右端就是用分子除以y得到的值），从而使算法效率变高，这就是整除分块。



------

------



## $code:$



```cpp
#include<iostream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#include<set>

#define ll long long
#define db double
#define inf 0x7fffffff
#define rg register int

using namespace std;

int Q;
int pr[50005];
int mu[50005];
bool use[50005];

inline int min(const rg &x,const rg &y){
    if(x<y)return x; else return y;
}

inline int qr(){
    register char ch; register bool sign=0; rg res=0;
    while(!isdigit(ch=getchar())) if(ch=='-')sign=1;
    while(isdigit(ch)) res=res*10+(ch^48),ch=getchar();
    return sign?-res:res;
}

inline void get_mu(int x){
    rg t=0; mu[1]=1;
    for(rg i=2;i<=x;++i){
        if(!use[i])mu[i]=-1,pr[++t]=i;
        for(rg j=1;j<=t;++j){
            if(i*pr[j]>x)break;
            use[i*pr[j]]=1;
            if(!(i%pr[j]))break;
            else mu[i*pr[j]]=-mu[i];
        }
    }
    for(rg i=2;i<=x;++i) mu[i]+=mu[i-1];
}

int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    Q=qr();
    get_mu(50000);
    while(Q--){
        rg a=qr(),b=qr(),k=qr();
        a/=k; b/=k;
        rg r,n=min(a,b),ans=0;
        for(rg l=1;l<=n;l=r+1){
            r=min(a/(a/l),b/(b/l));
            ans+=((a/l)*(b/l)*(mu[r]-mu[l-1]));
        }printf("%d\n",ans);
    }
    return 0;
}

```

---

## 作者：谁是鸽王 (赞：0)

## 【题解】Zap(莫比乌斯反演)

好像没有我这样化的，发一波题解

[传送门](https://www.luogu.org/problemnew/show/P3455)

所有除法默认向下取整

$\Sigma_{i=1}^x\Sigma_{j=1}^y[(i,j)=k]$
$=\Sigma_{i=1}^{x/k}\Sigma_{j=1}^{y/k}[(i,j)=1]$
$=\Sigma_{i=1}^{x/k}\Sigma_{j=1}^{y/k}\Sigma_{d|(i,j)}\mu(d)$
$=\Sigma_{d=1}^{min(x,y)}\Sigma_{i=1}^{x/k}\Sigma_{j=1}^{y/k}\mu(d)\times[d|(i,j)]$
$=\Sigma_{d=1}^{min(x,y)}(\frac x {dk})(\frac y {dk})\mu(d)$


整除分块直接做...

有一个细节，可能有疑惑：

```cpp
	r=min(x/(x/l),y/(y/l));
	ans+=1ll*(x/(l*k))*(y/((l*k)))*(sum[r]-sum[l-1]);
```

整除分块为什么是这样的？为什么"```r=min(x/(x/l),y/(y/l));```"中的"$l$"和"```ans+=1ll*(x/(l*k))*(y/((l*k)))*(sum[r]-sum[l-1]);```"不统一，为什么是"```(x/(l*k))*(y/(l*k))```"这不是整除分块正常的套路啊？

可以这样理解，整除分块利用了$\lfloor \frac x l \rfloor$在一定范围内不变的性质，所以我们同样也会有$\lfloor\frac {\lfloor \frac x l \rfloor} k\rfloor$在一定范围内不变化，并且前面那个式子包括的$l$的范围一定小于后面的那个$l$的范围，所以我们按照$\lfloor \frac x l \rfloor$整除分块即可。

至于如何按照$\lfloor\frac {\lfloor \frac x l \rfloor} k\rfloor=\lfloor \frac x {lk} \rfloor$分块(复杂度更加优秀?)，我也不知道怎么办，希望有高手指点一下QAQ

```cpp
#include<bits/stdc++.h>

using namespace std;typedef long long ll;
template < class ccf >
 inline ccf qr(ccf b){
    register char c=getchar();register int q=1;register ccf x=0;
    while(c<48||c>57)q=c==45?-1:q,c=getchar();
    while(c>=48&&c<=57)x=x*10+c-48,c=getchar();
    return q==-1?-x:x;}
inline int qr(){return qr(1);}
const int maxn=1e5+5;
bool usd[maxn];
int mu[maxn];
int sum[maxn];
vector < int > ve;
int x,y,k;
#define pb push_back
inline void gen(){
    mu[1]=sum[1]=usd[1]=1;
    for(register int t=2;t< maxn;++t){
	if(not usd[t])
	    ve.pb(t),mu[t]=-1;
	for(register auto p:ve)
	    if(1ll*p*t<maxn)
		if(usd[p*t]=1,t%p) mu[p*t]=-mu[t];
		else break;
	    else break;
	sum[t]=sum[t-1]+mu[t];
    }
}

int main(){
    gen();
    int T=qr();
    while(T--){
	x=qr();y=qr();k=qr();
	ll ans=0;
	for(register int l=1,r=0,edd=min(x,y)/k;l<=edd;l=r+1){
	    r=min(x/(x/l),y/(y/l));
	    ans+=1ll*(x/(l*k))*(y/((l*k)))*(sum[r]-sum[l-1]);
	}
	cout<<ans<<endl;
    }
    return 0;
}

```



---

## 作者：小塘空明 (赞：0)

题目等价于求x<=a/k,y<=b/k,且x与y互质的组数有多少种。

假设gcd(x,y)=i，那么显然这种二元组有(x/i)*(y/i)种。

根据容斥原理，即为没有限制的二元组个数，减去gcd(x,y)为2，3，5……的倍数的二元组个数，再将重复剪掉的部分加回来。

很明显，容斥的过程就是一个求mobius函数的过程。

同时我们可以发现，在j属于(x,min(a/(a/x),b/(b/x)))中，gcd(x,y)是j的倍数的二元组个数是相同的，那么我们预处理mobius函数的前缀和进行计算即可。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
typedef long long ll;
const ll size=1e5+10,maxn=5e4;
ll t,a,b,k,v[size],miu[size],s[size];
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline void prework(){
	for(ll i=1;i<=maxn;i++) miu[i]=1;
	for(ll i=2;i<=maxn;i++){
		if(v[i]) continue;
		miu[i]=-1;
		for(ll j=2*i;j<=maxn;j+=i){
			v[j]=1;
			if((j/i)%i==0) miu[j]=0;
			else miu[j]*=-1;
		}
	}
	for(ll i=1;i<=maxn;i++) s[i]=miu[i]+s[i-1];
}
int main(){
	prework();
	t=read();
	while(t--){
		a=read();b=read();k=read();
		a/=k;b/=k;
		if(a>b) swap(a,b);
		ll ans=0,m=a,c;
		for(ll j=1;j<=m;j=c+1){
			c=min(a/(a/j),b/(b/j));
			ans+=(s[c]-s[j-1])*(a/j)*(b/j);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

