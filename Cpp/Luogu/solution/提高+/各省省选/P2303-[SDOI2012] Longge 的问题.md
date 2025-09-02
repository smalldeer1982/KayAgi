# [SDOI2012] Longge 的问题

## 题目背景

Longge 的数学成绩非常好，并且他非常乐于挑战高难度的数学问题。

## 题目描述

现在问题来了：给定一个整数 $n$，你需要求出 $\sum\limits_{i=1}^n \gcd(i, n)$，其中 $\gcd(i, n)$ 表示 $i$ 和 $n$ 的最大公因数。  

## 说明/提示

#### 数据规模与约定

- 对于 $60\% $ 的数据，保证 $n\leq 2^{16}$。
- 对于 $100\% $ 的数据，保证 $1\leq n< 2^{32}$。

## 样例 #1

### 输入

```
6
```

### 输出

```
15```

# 题解

## 作者：小粉兔 (赞：204)

前几篇题解都是暴力 $\displaystyle \sum d \cdot \varphi(n / d)$。

这里我有一种更优的方法。

推导过程有点复杂，这里只能略提一二，若要了解详细过程，请访问我的博客[题解](http://www.cnblogs.com/PinkRabbit/p/8278728.html)。

前几篇题解都提到的：

$$ \begin{aligned} \sum \gcd(i,n) &= \sum_{j = 1}^{n} j \sum_{i = 1}^{n} [\gcd(i, n) = j] \\ &= \sum_{j \mid n} j \cdot \varphi(n / j) \end{aligned} $$

我进一步把 $\varphi$ 拆开算：

$$ \begin{aligned} &= \sum_{j \mid n} \frac{n}{j} \varphi(j) \\ &= \sum_{j \mid n} \frac{n}{j} \!\left( j \cdot \prod_{p \mid j} \frac{p - 1}{p} \right) \\ &= n \sum_{j \mid n} \prod_{p | j} \frac{p - 1}{p} \end{aligned} $$

这里 $p$ 是质数。

那么令 $n = p_1^{b_1} p_2^{b_2} p_3^{b_3} \cdots p_k^{b_k}$。

那么 $j = p_1^{c_1} p_2^{c_2} p_3^{c_3} \cdots p_k^{c_k}$，满足$0 \le c_i \le b_i$。

根据相同的 $p$ 在不同的 $j$ 中出现的条件，可以推出贡献一定时的 $j$ 在答案中的贡献次数。

总之，总贡献为 $\displaystyle \prod_{i}^{k} \left( \frac{p_i - 1}{p_i} \text{ , (if } c_i > 0 \text{)} \right)$。

这里 $c_i = 0$ 的话，就把这一项变成 $1$（不产生贡献）。

再经过对最终结果的归纳和化简（因式分解），得出答案：

$$n \prod_{i = 1}^{k} \frac{b_i p_i - b_i + p_i}{p_i}$$

时间复杂度为 $\mathcal O(\sqrt{n})$，代码：

```cpp
#include<cstdio>
long long n;
long long f(){
    long long ans=n; long long i;
    for(i=2;i*i<=n;++i) if(n%i==0){
        int b=0;
        while(n%i==0) ++b,n/=i;
        ans/=i;
        ans*=b*i-b+i;
    } if(n>1) ans/=n, ans*=n+n-1; 
    return ans;
}
int main(){
    scanf("%lld",&n);
    printf("%lld",f());
    return 0;
}
```

---

## 作者：拓拓 (赞：73)

题面非常简洁，求 $\sum\limits_{i = 1}^n \gcd(i, n)$


我们设 $t(x)$ 为 $1 - n$ 中与 $n$ 的最大公因数为 $x$ 的数的个数，即

$$t(x) = \sum_{i = 1}^n[\gcd(i, n) = x] = \sum_{i = 1}^{\lfloor\frac nx\rfloor}[\gcd(i, \lfloor\frac nx\rfloor) = 1]$$


考虑 $\phi(x) = \sum\limits_{i = 1}^n[gcd(i, n) = 1]$

即 $t(x) = \phi(\lfloor\frac nx\rfloor)$


由于$\gcd(i, n) | n$，考虑化简原式为：


$$\sum_{i = 1}^n\gcd(i, n) = \sum_{d|n}d\sum_{i = 1}^n[\gcd(i, n) = d] = \sum_{d|n}d\phi(\frac nd)$$

对于所有 $d | n$ 可以在 $O(\sqrt n)$ 的时间复杂度内枚举，$\phi$ 函数可以在 $O(\sqrt n)$ 的时间复杂度内求出，故时间复杂度为 $O(因数个数 * \sqrt n)$





```cpp
#include <cstdio>
long long phi(long long n) {
    long long res = n;
    for(long long i = 2; i * i <= n; i++) {
        if(n % i == 0) res = res / i * (i - 1);
        while(n % i == 0) n /= i; 
    }
    if(n > 1) res = res / n * (n - 1);
    return res;
}
long long f(long long x) {
    long long res = 0LL, i = 1LL;
    for(; i * i < x; i++)
        if(x % i == 0) res += i * phi(x / i) + (x / i) * phi(i);
    if(i * i == x) res += i * phi(i);
    return res;
}
int main(int argc, char *argv[]) {
    long long n;
    scanf("%lld", &n);
    printf("%lld", f(n));
    return 0;
}
```

---

## 作者：Siyuan (赞：39)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/articles/problem-SDOI-2012-Longge-Problem/)

---

## Description

> 题目链接：[Luogu 2303](https://www.luogu.org/problemnew/show/P2303)

Longge 的数学成绩非常好，并且他非常乐于挑战高难度的数学问题。现在问题来了：给定一个整数 $n$，你需要求出：
$$\sum_{i=1}^n\gcd(i,n)$$
数据范围：$1\le n\le 2^{32}$

------

## Solution

我们直接拆一下式子：
$$\begin{aligned}\text{原式}&=\sum_{i=1}^n\gcd(i,n) \\& =\sum_{d\mid n}d\times \sum_{i=1}^n [\gcd(i,n)=d] \\& =\sum_{d\mid n}d\times \sum_{i=1}^{\frac{n}{d}} \left[\gcd\left(i,\frac{n}{d}\right)=1\right] \\ \\& =\sum_{d\mid n}d\cdot \varphi(\frac{n}{d}) \\\end{aligned}$$
这个转化的过程非常套路，我们只要暴力枚举 $n$ 的因数并快速求出单个 $\varphi$ 函数的值即可。

**时间复杂度**：$O(\text{因子个数}\times \sqrt n)$（稳过 QAQ）

------

## Code

```cpp
#include <cstdio>
#include <cmath>

const int N=(1<<16)+5;
int n,tot,p[N];
bool flg[N];

void sieve(int n) {
	for(int i=2;i<=n;++i) {
		if(!flg[i]) p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=n;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
long long phi(long long x) {
	long long ans=x;
	for(int i=1;i<=tot&&1LL*p[i]*p[i]<=x;++i) {
		if(x%p[i]) continue;
		ans=ans/p[i]*(p[i]-1);
		while(x%p[i]==0) x/=p[i];
	}
	if(x>1) ans=ans/x*(x-1);
	return ans;
}
int main() {
	long long n,ans=0;
	scanf("%lld",&n);
	sieve((int)sqrt(n));
	for(long long i=1;i*i<=n;++i) {
		if(n%i==0) {
			ans+=i*phi(n/i);
			if(i*i!=n) ans+=n/i*phi(i);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```





---

## 作者：ycyaw (赞：33)

好水的蓝题啊，~~少数没有看题解做的题~~

题面简洁明了：求$\sum\limits_{i=1}^{n}gcd(i,n)$

设$gcd(i,n)=d$，则$gcd(i/d,n/d)=1$

$d$显然就是$n$的因数

我们对于每个$d$，要求有多少$i$使得$gcd(i/d,n/d)=1$，设求出有$x$个$i$，那么对答案的贡献就是$d \times x$。为什么是这些贡献？很显然，这些$i$与$n$的$gcd$就是$d$，共$x$个这样的$i$，所以是$d \times x$。

因为满足$gcd(i/d,n/d)=$1的$i/d$的个数就是与$n/d$互质的数，每个$i/d$又对应一个$i$，个数就是$φ(n/d)$。前面说了$d$是$n$的因数，我们枚举所有因数，累加$φ(n/d)$即可。

对于每个$φ(n/d)$，$\sqrt{n}$求即可。

代码：
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define oo (1e18)
#define int long long
#define LL unsigned long long
#define hh puts("")
using namespace std;
int ans,n;
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch^48);ch=getchar();}
    return ret*ff;
}
inline int getphi(int x){
    int res=x;
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            res=res/i*(i-1);
            while(x%i==0) x/=i; 
        }
    }
    if(x>1) res=res/x*(x-1);
    return res;
}
signed main(){
    n=read();
    int sq=sqrt(n);
    for(int i=1;i<=sq;i++){
        if(n%i==0){
            ans+=getphi(n/i)*i;
            if(i*i!=n) ans+=getphi(i)*(n/i);
        }
    }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：ysner (赞：26)

膜拜楼下lqzhhh大佬，他的题解我看不懂。。。（也可以理解为我数学不好）

不过说回来，他的程序用港记评测还跑了88ms，而我的程序只跑了1ms，因此我觉得我的方法效率更优，值得推广。

最直观的想法肯定是要枚举n 的所有因子，然后想办法统计出来所有的和 n 的最大公约数正好是这个因子的数的个数，之后乘上这个因子，最后累加，就是需要的答案了，但是问题来了...

问题就在于：如何统计每个因子（设为x）对应的满足 gcd(n,m)= x 的m 的个数，下面是数学分析：

需要求出满足 gcd(n,m)= x 的m 的个数，不难发现，n 和m 的最大公约数为x，那么就可以同时除去x

相当于求满足 gcd(n/x,m/x)=1  的数的个数，额...这不就是欧拉函数吗........

然后就是相乘再累加了.....

明白到这里之后，就能很简单的编程实现了....

注意：

1、枚举n 的因子，只需要枚举到根号n，但是要特别注意 n 是完全平方数的时候，切忌重复统计！

2、程序中所有循环变量都要设为long long。

```cpp
#include<stdio.h>  
#include<math.h>  
typedef long long ll;  
ll euler(ll x)//欧拉函数  
{  
    ll ans=x,tp=sqrt(x);  
    for(ll i=2;i<=tp;++i)  
        if(x%i==0)  
        {  
            ans=ans-ans/i;  
            while(x%i==0)  x/=i;   
        }  
    if(x>1)  ans=ans-ans/x;  
    return ans;  
}  
int main()  
{  
    ll n;
    scanf("%lld",&n);
    ll ans=0,tp=sqrt(n);  
    for(ll i=1;i<=tp;++i)  
      if(n%i==0)  ans+=i*euler(n/i)+n/i*euler(i);   
    if(tp*tp==n) ans-=tp*euler(tp);  
        printf("%lld\n",ans);
    return 0;  
}
```

---

## 作者：Marser (赞：21)

前面的大佬都好强啊，但是本蒟蒻认为本人发现的方法还是挺优秀的啊。
鸣谢[@小粉兔](https://www.luogu.org/space/show?uid=10703)巨强!

题意已经很明确了，首先，我们可以这样来推导：

$\sum_{i=1}^n\gcd(n,i)$

$=\sum_{x|n}x*\sum_{i=1}^n[gcd(i,n)=x]$

$=\sum_{x|n}x*\sum_{i=1}^{[\frac{n}{i}]}[gcd(i,[\frac{n}{i}]=1)]$

$=\sum_{x|n}x*\varphi(\frac{n}{x})$

设$n$的因数个数为$l$，质因数个数为$k$,$p_i$表示$n$的质因子，推导到这一步时，我们已经可以直接通过$O(l+\sqrt{n})$的时间得出答案。但是，我们还可以继续优化：

$\sum_{x|n}x*\varphi(\frac{n}{x})$

$=\sum_{x|n}x*\prod_{i=1}^{k}(\frac{n}{x})(\frac{p_{i}-1}{p_{i}})$

$=n\sum_{x|n}\prod_{p|\frac{n}{x}}(\frac{p_{i}-1}{p_{i}})$

令$n=\prod_{i=1}^{k}p_{i}^{a_{i}}$ , $x=\prod_{i=1}^{k_x}p_{i}^{b_{i}}$ $~(0\le{b_i}\le{a_i})$ , $f(i)=\frac{p_{i}-1}{p_{i}}$ ,

则 $\prod_{p|\frac{n}{x}}(\frac{p_{i}-1}{p_{i}})$

$=\prod_{i=1}^{k}f(i)*[b_{i}>0]$  $(*)$

若存在多个$x$使得它们的 $(*)$ 式相同，则对于每一个$p_{i}$ ,它的$b_i$一定同大于或等于0，易知这样的$x$共有$$\prod_{i=1}^{g}a_{q_i}$$

个，其中$q_i$表示对于这样的$x$，它所含有的指数非0的因子，$g$表示所有$q_i$的个数。

化简可得所有$x$的贡献是$$\prod_{i=1}^{g}f_{q_i}a_{q_i}$$

发现对于每一个因数$p_i$ ， 它的贡献可以独立计算，记作$\chi_i=f_ia_i$,

可以观察到，若一个因数含有$p_i,p_j$两个质因子，那么他的贡献就是$$\chi_i*\chi_j$$

对于任意因数$x$，它含有的质因子$p_i$对他的答案贡献是$\chi_i$，它不含有的质因子的贡献可以看成是1，

因此，$(*)$式可以化简为

$\prod_{i=1}^{k}({\chi_i}+1)$

$=\prod_{i=1}^{k}(\frac{a_ip_i-a_i+p_i}{p_i})$

所以答案是$$n\prod_{i=1}^{k}(\frac{a_ip_i-a_i+p_i}{p_i})$$

使用朴素的分解质因数算法可以在$O(\sqrt{n})$的时间内得出答案，而使用Pollard_rho算法可以在$O(\sqrt[4]{n})$时间内得出答案。
代码如下：
```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define reg register
typedef long long ll;
template<typename T>inline T read(){
	reg T x=0;reg short f=1;reg char c=getchar();
	for(;!isdigit(c);f=c=='-'?-1:1,c=getchar());
	for(;isdigit(c);x=x*10+(c^48),c=getchar());
	return x*f;
}
const int S=10;
inline ll qmul(ll a,ll b,ll c){
    a%=c;b%=c;reg ll res=0;
    while(b){
        if(b&1)res+=a,res%=c;a<<=1;
        if(a>=c)a%=c;b>>=1;
    }
    return res;
}
inline ll qpow(ll x,ll n,ll mod){
    if(n==1)return x%mod;
    x%=mod;reg ll res=1;
    while(n){
        if(n&1)res=qmul(res,x,mod);
        x=qmul(x,x,mod);
        n>>=1;
    }
    return res;
}
inline bool check(ll a,ll n,ll x,ll t){
    reg ll res=qpow(a,x,n),last=res;
    for(int i=1;i<=t;i++){
        res=qmul(res,res,n);
        if(res==1&&last!=1&&last!=n-1)return true;
        last=res;
    }
    if(res!=1)return true;
    return false;
}
inline bool Miller_Rabin(ll n){
    if(n==2)return true;
    if(n<2||(n&1)==0)return false;
    reg ll x=n-1,t=0;
    while((x&1)==0)x>>=1,t++;
    for(int i=0;i<S;i++){
        ll a=rand()%(n-1)+1;
        if(check(a,n,x,t))return false;
    }
    return true;
}
int tot;
ll fac[105];
inline ll gcd(ll a,ll b){
    if(a==0)return 1;
    if(a<0)return gcd(-a,b);
    while(b){reg ll t=a%b;a=b;b=t;}
	return a;
}
inline ll Pollard_rho(ll x,ll c){
    reg ll i=1,k=2,x0=rand()%x,y=x0;
    while(1){
        i++;x0=(qmul(x0,x0,x)+c)%x;
        reg ll d=gcd(y-x0,x);
        if(d!=1&&d!=x)return d;
        if(y==x0)return x;
        if(i==k){y=x0;k<<=1;}
    }
}
inline void findfac(ll n){
    if(Miller_Rabin(n)){fac[tot++]=n;return;}
    reg ll p=n;
    while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
    findfac(p);findfac(n/p);
}
int main(){
	srand(time(NULL));
	reg ll n=read<ll>(),ans=n;
	if(Miller_Rabin(n))return 0*printf("%lld\n",n+n-1);
	findfac(n);
	for(reg ll i=0;i<tot;i++){
		reg int b=0;while(!(n%fac[i]))n/=fac[i],b++;
		ans/=fac[i];ans*=b*fac[i]-b+fac[i];
	}
	printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：sun123zxy (赞：12)

~~洛谷的markdown为啥不支持多行公式啊啊啊~~

想要公式好看点还是去博客看吧 [传送门](https://www.cnblogs.com/sun123zxy/p/luogu2303withmuandphi.html)，里面也多写了一些有关本题的拓展...

---

bux fixed：

修了下无法正常显示的公式

---

&nbsp;

题目传送门：[https://www.luogu.org/problem/P2303](https://www.luogu.org/problem/P2303)

>给定一个整数$n$，求
>$$
>\sum_{i=1}^n \gcd(n,i)
>$$
>

蒟蒻随便yy了一下搞出来个$O(\sqrt{n})$的算法 ~~这题数据怎么这么水~~

首先看到gcd我们就下意识的对它反演一波对吧

### 第一步

$$\sum_{i=1}^n \gcd(n,i) = \sum_{d|n} \varphi(d) \frac{n}{d}$$

这里提供两种化法，得到的结果都是这个。

#### 法一

根据欧拉函数和式

$$n = \sum_{d|n} \varphi(d)$$

暴力推导即可

$$\sum_{i=1}^n \gcd(n,i) = \sum_{i=1}^n \sum_{d|\gcd(n,i)} \varphi(d) $$

$$= \sum_{d|n} \sum_{i=1}^{\frac n d} \varphi(d) $$

$$= \sum_{d|n} \varphi(d) \frac n d$$


#### 法二

根据欧拉函数的定义式
$$\varphi(n) = \sum_{i=1}^n [\gcd(n,i) = 1]$$
PS：$\varphi(n)$表示$1$~$n-1$内与$n$互质的数，将和式上界提升到$n$不但不会影响正确性（$\gcd(n,n) = n \neq 1$），而且让$\varphi(1)$不用特判。

易得
$$\sum_{i=1}^n \gcd(n,i) = \sum_{d|n} d \sum_{i=1}^n [\gcd(n,i) = d] $$
$$= \sum_{d|n} d \sum_{i=1}^{\frac n d} [\gcd(\frac n d,i) = 1] $$
$$= \sum_{d|n} d \varphi(\frac n d) $$
$$= \sum_{d|n} \varphi(d) \frac n d $$

这一步还是比较简单的。~~稍有基础的同学大概都会吧~~

### 第二步

令
$$g(n) = \sum_{i=1}^n \gcd(n,i) = \sum_{d|n} \varphi(d) \frac{n}{d}$$
我们希望求$g$的在$n$的函数值。容易发现右式是狄利克雷卷积$\varphi * Id$，也就是说$g$也是积性函数。所以考虑质因数分解$n$，最后用积性累乘出来

即
$$g(n) = g({p_1}^{c_1}) g({p_2}^{c_2}) ... g({p_n}^{c_n})$$
则只需求$g(p^c)$（这里省略下标）

$p^c$的因数分别为$1$，$p$，$p^2$，...，$ p^c$

所以有
$$g(p^c) = \sum_{i=0}^{c} \varphi(p^i) \frac{p^c}{p^i} $$
$$= \sum_{i=0}^{c} \varphi(p^i) p^{c-i}$$


#### 求$\varphi(p^c)$

考虑先弄出上式中$\varphi(p^i)$的封闭形式，再带回原式看看

根据欧拉函数通式
$$\varphi(n) = n \prod_{i=1}^k (1 - \frac 1 {p_i})$$
（这个$\pi$指的是分解质因数）

易得
$$\varphi(p^c) = p^c (1 - p) $$
$$= p^c - p^{c-1}$$
注意这个式子需要在$c=0$时特判，因为$\varphi(1) = 1$（$1$可以视作分解不出任何质因数）

#### 求$g(p^c)$

得到了$\varphi(p^c)$，带回之前未推完的$g(p^c)$的式子，得
$$g(p^c) = \sum_{i=0}^{c} \varphi(p^i) p^{c-i} $$
$$= p^c + \sum_{i=1}^{c} (p^i - p^{i-1}) p^{c-i} $$
$$= p^c + \sum_{i=1}^{c} (p^c - p^{c-1}) $$
$$= p^c + c (p^c - p^{c-1}) $$
$$= (c+1)p^c - c \ p^{c-1}$$
（中途对$i=0$进行了特殊讨论）（该式同样不适用于$c=0$的情况）

然后积性合并起来就完了

冷静分析一波时间复杂度。质因数分解消耗$O(\sqrt n)$的时间复杂度，分解出不超过$O(log_2 n)$个$p^c$，每个$g(p^c)$的计算是$O(1)$的。所以总时间复杂度为$O(\sqrt n)$

### 代码

非常简单的代码

```c++
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;

ll p[1005],c[1005],g[1005];ll kN;
void Div(ll n){
	kN=0;
	for(ll i=2;i*i<=n;i++){
		if(n%i==0){
			kN++;p[kN]=i;
			g[kN]=1;
			ll e=0;while(n%i==0) e++,n/=i,g[kN]*=i;
			c[kN]=e;
		}
	}
	if(n!=1) kN++,p[kN]=n,c[kN]=1,g[kN]=n;
}
ll N;
int main(){
	cin>>N;
	Div(N);
	ll pdt=1;
	for(int i=1;i<=kN;i++) pdt=pdt*((c[i]+1)*g[i]-c[i]*g[i]/p[i]);
	cout<<pdt;
	return 0;
}
```

~~这式子长得跟[小粉兔菊苣的题解](https://www.luogu.org/blog/PinkRabbit/solution-p2303)很像？~~

---

## 作者：qwaszx (赞：7)

化一化式子

$\sum\limits_{i=1}^n\gcd(i,n)=\sum\limits_{d|n}d\sum\limits_{i=1}^n[\gcd(i,n)=d]=\sum\limits_{d|n}d\sum\limits_{i=1}^{\frac{n}{d}}[\gcd(i,\frac{n}{d})=1]=\sum\limits_{d|n}d\varphi(\frac{n}{d})$

也就是$id\ast\varphi$

考虑把$\varphi$拆开，那么得到

$n\sum\limits_{d|n}\prod\limits_{p|d}\frac{p-1}{p}$

令$n=\prod\limits_ip_i^{k_i}$，设$S=\{p_i\}$

考虑$d$中包含哪些$p_i$，枚举所有$S$的子集，那么这样的子集对应的$d$一共有$\prod k_i$个，要求所有子集的贡献之和.

稍微思考一下可以知道答案是$n\prod\limits_i(k_i\cdot\frac{p_i-1}{p_i}+1)$，就是分别考虑每个元素选和不选对答案的贡献.于是分解质因数之后计算.

$O(\sqrt{n})$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long ans=1,n;
int main()
{
    scanf("%lld",&n);long long nn=n;//解决分数的问题，从外面的n里抽出一个pi给内部
    for(long long i=2;i*i<=n;i++)
    {
        if(n%i==0)
        {
            nn/=i;int t=0;
            while(n%i==0)++t,n/=i;
            ans=ans*(t*(i-1)+i);
        }
    }
    if(n!=1)nn/=n,ans=ans*(2*n-1);
    cout<<ans*nn<<endl;
}
```

如果把$n$改小一些多次询问就照着上面的式子线筛一下就好了，或者直接卷积$O(n\log n)$也行

---

## 作者：kkxhh (赞：7)

题目让我们求 $\sum_{i=1}^{n}gcd(i,n)$

显然对于任意 $i<=n$，$gcd(i,n)$一定是 $n$ 的一个约数

于是我们就可以把问题转化成求

$$\sum_{d|n}d\sum_{i=1}^{n}[gcd(i,n)=d]$$

然后我们又可以发现

$$ \sum_{i=1}^{n}[gcd(i,n)=d]=\sum_{i=1}^{n}[gcd(\frac{i}{d},\frac{n}{d})=1]=\varphi(\frac{n}{d})$$

于是我们将式子转化为求

$$ \sum_{d|n}d\varphi(\frac{n}{d}) $$

于是我们可以 $O(\sqrt{n})$ 枚举约数，对于每个约数用下面这个公式 $O(\sqrt{n})$ 求出 $\varphi(d)$ 即可

$$\varphi(n)=n\prod_{p_{i}\in P,p_{i}|n}(1-\frac{1}{p_{i}})$$

代码如下

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n,ans;

inline ll read(){
    ll num=0,k=1; char c=getchar();
    while(c>'9' || c<'0') k=(c=='-')?0:k,c=getchar();
    while(c>='0' && c<='9') num=num*10+c-'0',c=getchar();
    return k?num:-num;
}

ll phi(ll x){
    ll tmp=x,cur=x;
    for(ll i=2;i*i<=x;i++){
    	if(cur%i==0) tmp=tmp/i*(i-1);
    	while(cur%i==0) cur/=i;
    }
 	if(cur>1) tmp=tmp/cur*(cur-1);
    return tmp;
}

int main(){
    n=read();
    for(ll i=1;i*i<=n;i++) if(n%i==0) ans+=(n/i*phi(i))+((n/i!=i)?(i*phi(n/i)):0);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：洛水·锦依卫 (赞：4)

其他题解做法都好麻烦啊……没必要化式子来来去去的……

我们设 $f(x)$ 为有多少个数和 $n$ 的 $gcd=x$ 。

然后我们从大到小枚举因子，然后对于一个 $f(x)$ 显然有 $\lfloor\frac{n}{x}\rfloor$ 个数和 $n$ 的 $gcd$ 是 $x$ 的倍数，那么先令 $f(x)=\lfloor\frac{n}{x}\rfloor$ ，然后依次减去其他的，$x$ 的倍数的 $f$ ，也就是减去 $\sum  _{d|n\&\&x|d }f(d)$ 就好了……

复杂度 $\sqrt n+$因子数平方

![迷惑](https://github.com/LuoshuiTianyi/Images/blob/master/Eip/%E8%BF%B7%E8%8C%AB.jpg?raw=true)

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 1e3;
LL n, ans;
LL top, stk[Max_n];
LL f[Max_n];

int main() {
#ifndef ONLINE_JUDGE
  freopen("2303.in", "r", stdin);
  freopen("2303.out", "w", stdout);
#endif
  n = read();
  for (LL i = sqrt(n); i; i--)
    if (n % i == 0) {
      stk[++top] = i, stk[++top] = n / i;
      if (i * i == n) top--;
    }
  sort(stk + 1, stk + top + 1);
  for (int i = top; i; i--) {
    f[i] = n / stk[i];
    for (int j = i + 1; j <= top; j++)
      if (stk[j] % stk[i] == 0) f[i] -= f[j];
    ans += f[i] * stk[i];
  }
  cout << ans;
}
```

---

## 作者：Great_Influence (赞：4)

首先，推一下式子。

$ans=g(n)=\sum\limits_{i=1}^n(i,n)$

$=\sum\limits_{d|n}d\sum\limits_{i=1}^\frac{n}{d}[(i,\frac{n}{d})=1]$

$=\sum\limits_{d|n}d\phi(\frac{n}{d})$

因为$\phi$和$N$都是积性函数，因此g也是积性函数。

所以

$g(n=\prod p_i^{q_i})$

$=\prod g(p_i^{q_i})$

$=\prod\limits_{p|n}((q+1)p^q-qp^{q-1})$

最后面那一步可以根据$\phi$的式子推出。

因此直接分解质因数，按照公式计算即可。

记得n的范围会爆int。

代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
    T s=0,f=1;char k=getchar();
    while(!isdigit(k)&&k^'-')k=getchar();
    if(!isdigit(k)){f=-1;k=getchar();}
    while(isdigit(k)){s=s*10+(k^48);k=getchar();}
    x=s*f;
}
void file(void){
    #ifndef ONLINE_JUDGE
    freopen("water.in","r",stdin);
    freopen("water.out","w",stdout);
    #endif
}
static long long ans=1ll;
static long long n;
inline long long power(long long a,long long b)
{
    static long long sum;
    for(sum=1ll;b;b>>=1,a*=a)if(b&1)
        sum*=a;
    return sum;
}
inline void calans(long long x)
{
    static long long cnt;
    for(register long long i=2ll,lim=sqrt(x)+1;i<=lim;++i)
        if(x%i==0)
        {
            cnt=0;
            while(x%i==0)++cnt,x/=i;
            ans*=(1ll*cnt*i+i-cnt)*power(i,cnt-1);
        }
    if(x>1)ans*=2ll*x-1ll;
}
int main(void){
    file();
    read(n);
    calans(n);
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：枫林晚 (赞：3)

（网上全部都是欧拉函数解法~~（甚至还有莫比乌斯反演？？））~~

像我这种蒟蒻就真的想不到了。


我就用容斥解决了这道题。

既然要考虑gcd，而且不能暴力，就肯定要把n质因数分解了。

n=p1^q1 x p2^q2 x... x pk^qk

#### gcd(a,b)的本质是：把a质因数分解，b质因数分解，对于每一个质因子，系数取min再相乘就是gcd

所以考虑一下n的所有因数。（远远不到sqrt（N）个，网上有说ln(n)??）

对于每一个因数p=p1^d1 x p2^d2 x... x pk^dk，它在n以内的倍数都有p，

但是，假设d1<q1时，同样是 p1^(d1+1) x p2^d2 x... * pk^dk的倍数的数，gcd就不是p了。

同理，每一个系数d如果能够加1，那么这个新因数的倍数们与n的gcd 就不是现在的p了。

 

我们把p的每一位的系数d分别能加1就加1，构造一个新数M，M的倍数就是一些不由p贡献的数。

把所有这些M的倍数减去，但是，最小公倍数们又减多了。再加上2个lcm，加上3个lcm们。。。。。。。

这就是容斥啦。

因为，2^32以内的一个数的不同质因子，最多只有10个（2x3x5x7x11x13x17x19x23x29 > 2^32）

所以，每次就2^10容斥一下，一定不会tle~！！！！！！！！！！！！！！

 

就这样，两个dfs。一个枚举因数，一个用这个因数容斥。

复杂度上限：O（因数个数*（2^10））

比网上一般的欧拉函数做法 O（因数个数* sqrt（n））的做法要快。

 

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
ll has[20],cnt;
ll ans;
struct node{
	ll num,mi;
}c[20];
ll tot;//sum of primes
ll sum=0;
void sol(){
	ll k=n;
	for(ll i=2;i*i<=n;i++){
		if(k%i==0){
			c[++tot].num=i;
			while(k%i==0) c[tot].mi++,k/=i;
		}
	}
	if(k!=1) c[++tot].num=k,c[tot].mi++;
}
void dfs1(int x,int cnt,ll digi){
	if(x==tot+1){
		if(cnt&1) sum-=n/digi;
		else sum+=n/digi;
		return;
	}
	dfs1(x+1,cnt,digi);
	if(has[x]<c[x].mi) dfs1(x+1,cnt+1,digi*c[x].num);
}
void dfs2(int x,ll now){
	if(x==tot+1){
		sum=0;
		dfs1(1,0,now);
		ans+=sum*now;
		return;
	}
	ll to=1;
	for(int i=0;i<=c[x].mi;i++){
		has[x]=i;
		dfs2(x+1,now*to);
		to*=c[x].num;
	}
}
int main()
{
	scanf("%lld",&n);
	sol();
	dfs2(1,1);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：封癫 (赞：3)

我有个[博客](http://www.cnblogs.com/cellular-automaton/p/8353385.html)……如果题解体验不好就去博客吧


就让我这样的蒟蒻发一个简单易想的题解吧！！！



这题我一开始一看，woc这不是莫比乌斯反演么，推推推，推到杜教筛，输出结果一看不对



emmm回来仔细想想……woc推错了？



然后撕烤半天打了个暴力，A了



首先我们学过莫比乌斯反演的一般能够想到枚举gcd，记为w



　　所以我们需要求的就是∑w|nw∑w|i[gcd(i,n)=w]

然后……就到了激动人心的构造函数环节……


　　设F(w)=∑w|i[w|gcd(i,n)]


　　f(w)=∑w|i[w=gcd(i,n)]

于是有F(w)=∑w|df(d)


于是……f(w)=∑w|dμ(dw)F(d)


容易（个屁，我手玩了半年）发现，当d|n

时F(d)=nd，其他情况下F(d)=0


　　然后问题就变成了∑w|nw∑w|dμ(dw)F(d)

设t=dw


　　原式化为∑w|nw∑t|dμ(t)F(tw)

然后我们发现了什么？


没错w可以暴力枚举qwq！没错t可以暴力枚举qwq！


因为我们枚举到根n就可以枚举出n的所有因子！t同理！


来吧让我们暴……等等μ


怎么算？


废话啊按着莫比乌斯函数的定义暴力qwq！

  
  ```cpp
  #include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<iostream>
#include<cmath>
#define maxn 5000020
using namespace std;
inline long long read(){
    long long num=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')    f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        num=num*10+ch-'0';
        ch=getchar();
    }
    return num*f;
}

bool vis[maxn];
int prime[maxn],tot;
int mu[maxn];

inline int calcmu(long long n){
    if(n<maxn)    return mu[n];
    long long sqt=sqrt(n);
    long long now=n;int ans=0;
    for(int j=1;j<=tot;++j){
        int i=prime[j];
        if(i>sqt)    break;
        if(now%i)    continue;
        int cnt=0;
        while((now%i)==0){
            cnt++;    now/=i;
            if(cnt>1)    return 0;
        }
        ans++;
    }
    if(now>0)    ans++;
    if(ans&1)    return -1;
    else         return 1;
}
        

int main(){
    mu[1]=vis[1]=1;
    for(int i=2;i<maxn;++i){
        if(vis[i]==0){
            prime[++tot]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=tot&&prime[j]*i<maxn;++j){
            vis[i*prime[j]]=1;
            if(i%prime[j])    mu[i*prime[j]]=-mu[i];
            else            break;
        }
    }
    long long n=read(),ans=0;
    int sqt=sqrt(n);
    for(int i=1;i<=sqt;++i){
        if(n%i)    continue;
        long long d=n/i;long long now=0;
        long long sar=sqrt(d);
        for(int j=1;j<=sar;++j){
            if(d%j)    continue;
            now+=calcmu(j)*(n/(j*i));
            if(j*j==d)    continue;
            now+=calcmu(d/j)*(n/((d/j)*i));
        }
        ans+=now*i;
        
        if(1LL*i*i==n)    continue;
        long long ret=n/i;
        d=n/ret;now=0;
        sar=sqrt(d);
        for(int j=1;j<=sar;++j){
            if(d%j)    continue;
            now+=calcmu(j)*(n/(j*ret));
            if(j*j==d)    continue;
            now+=calcmu(d/j)*(n/((d/j)*ret));
        }
        ans+=now*ret;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：LZWei (赞：3)

gcd(n,i)=i;gcd(n/i,1)=1;

 phi[n/i]就是（1，n）中有几个数和i gcd=i;

既然可以除以i得num，就可以除num得i，判断不i!=num时，再计算ans+=ola(i)\*num;



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define LL long long
using namespace std;
LL n,ans;
int ola(LL x)
{
    LL m=sqrt(x),phi=x;
    for(int i=2;i<=m;i++)
    {
        if(x%i==0)
            phi=phi*(i-1)/i;
        while(x%i==0) x=x/i;
    }
    if(x>1) phi=phi*(x-1)/x;
    return phi;
}
int main()
{
    scanf("%lld",&n);
    for(LL i=1;i*i<=n;i++)
    {
        if(n%i==0)
        {
            LL num=n/i;
            ans+=ola(num)*i;
            if(num!=i)
                ans+=ola(i)*num;
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：CrTsIr400 (赞：2)

介绍一种 $O(\sqrt n \ln n)$ 的算法。

题意：求 $\sum_{i=1}^n\gcd(i,n)$。

按照套路，原式= $\sum_{g|n} g\varphi(n/g)$。（为了方便，这里使用记号 $/$ 表示整除）

我枚举了 $g$ 而且要处理 $\varphi(n/g)$。但是每次计算 $\varphi$ 的时候，不需要 $O(\sqrt {n/g})$。

欧拉函数只和一个数的质因数有关，而一个数的质因数个数是 $O(\ln(n))$ 级别的。所以可以这样处理：

预处理一遍 $O(\sqrt n)$ 分解质因数，而每次计算欧拉函数的时候，判断 $n/g$ 里面有哪几个质因子即可。

时间复杂度 $O(\sqrt n \times c)$，其中 $c$ 为因子个数，比 $\ln(n)$ 略小，不大于 $9$。

```cpp
typedef unsigned int I;
typedef long long LL;
I n;
LL ans=0;
vector<I>v,e; 
void prework(I n){
	I nn=n;
	for(I i=2;1ll*i*i<=n;++i){
		if(n%i)continue;
		v.push_back(i);
		while(n%i==0)n/=i;
	}if(n>1)v.push_back(n);
	n=nn;
	for(I i=1;1ll*i*i<=n;++i){
		if(n%i)continue;
		e.push_back(i);
		if(i^(n/i))e.push_back(n/i);}
}
I phi(I x){
	I ans=x;
	for(I i:v){
		if(x%i==0)ans=(ans/i)*(i-1);}
	return ans;}
int main(){
	in(n);
	prework(n);
	for(I i:e){
		ans+=1ll*i*phi(n/i);}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Huami360 (赞：2)

题意：求$\sum_{i=1}^{n}\gcd(i,n)$

首先可以肯定，$\gcd(i,n)|n$。

所以设$t(x)$表示$gcd(i,n)=x$的$i$的个数。

那么答案很显然就是$\sum_{d|n}t(d)*d$。

那么$t(x)$怎么求呢。

$$t(x)=\sum_{i=1}^{n}[\gcd(i,n)=x]$$
因为若$\gcd(x,y)=1$,则有$\gcd(xk,yk)=k$。
所以
$$t(x)=\sum_{i=1}^{n}[\gcd(i,n)=x]=\sum_{i=1}^{\lfloor\frac{n}{x}\rfloor}[\gcd(i,\lfloor\frac{n}{x}\rfloor)=1]=\phi(\lfloor\frac{n}{x}\rfloor)$$
所以最终答案就是$\sum_{d|n}[\phi(\lfloor\frac{n}{d}\rfloor)*d]$

我们可以在$O(\sqrt n)$的时间复杂度内求出$n$的所有约数，约数个数是$\log n$级别的，求$\phi$是$O(\sqrt n)$的时间复杂度，所以总时间复杂度$O(\log n\sqrt n)$

```cpp
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
ll n;
ll phi(ll x){
    int s = sqrt(x); ll ans = x;
    for(int i = 2; i <= s && x != 1; ++i)
       if(!(x % i)){
         ans = ans / i * (i - 1);
         while(!(x % i))
           x /= i;
       }
    if(x != 1) ans = ans / x * (x - 1);
    return ans;
}
int main(){
    scanf("%lld", &n);
    int i; ll ans = 0;
    for(i = 1; (ll)i * i < n; ++i)
       if(!(n % i))
         ans += phi(n / i) * i + (n / i) * phi(i);
    if(i * i == n) ans += phi(i) * i;
    printf("%lld\n", ans);
    return 0;
} 

```

---

## 作者：xyz32768 (赞：2)

没事刷刷水题..

可以看到，虽然$n$的值很大，但$\gcd(i,n)$的取值并不多（$n$的约数个数）。

当$\gcd(i,n)=1$时，可以想到这样的$i$有$\phi(n)$个。

当$\gcd(i,n)=x,x|n$时，其实可以发现，$\gcd(i/x,n/x)=1$，此时对答案的贡献为$x*\phi(n/x)$。

所以得出，$\sum_{i=1}^n\gcd(i,n)=\sum_{d|n}d*\phi(n/d)$。

代码：

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
ll n, a[N], X[N];
int cnt;
ll phi(ll x) {
    int i, tot = 0; ll w = x;
    for (i = 2; 1ll * i * i <= w; i++) {
        if (x % i) continue; X[++tot] = i;
        while (!(x % i)) x /= i;
    }
    if (x > 1) X[++tot] = x;
    for (i = 1; i <= tot; i++)
        (w /= X[i]) *= X[i] - 1;
    return w;
}
int main() {
    int i; cin >> n; ll res = 0;
    for (i = 1; 1ll * i * i <= n; i++)
        if (n % i == 0) {
            a[++cnt] = i;
            if (i * i != n) a[++cnt] = n / i;
        }
    for (i = 1; i <= cnt; i++) res += a[i] * phi(n / a[i]);
    cout << res << endl;
    return 0;
}
```

---

## 作者：lqzhhh (赞：2)

orz hzwer ;

学习黄学长打的；

枚举n的约数k，令s(k)为满足gcd(m,n)=k,(1<=m<=n)m的个数，则ans=sigma(k\*s(k)) (k为n的约数）

因为gcd(m,n)=k,所以gcd(m/k,n/k)=1,于是s(k)=euler(n/k)

phi可以在根号的时间内求出（转载自http://hzwer.com/3470.html）

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for (long long i=a;i<=b;i++)
#define Rep(i,a,b) for (long long i=b;i>=a;i--)
using namespace std;
ll n,ans,m;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
ll phi(ll x)
{
    ll t=x;
    For(i,2,m)
        if(x%i==0)
        {
            t=t/i*(i-1);
            while(x%i==0)x/=i;
        }
    if(x>1)t=t/x*(x-1);
    return t;
}
int main()
{
    n=read();
    m=sqrt(n);
    For(i,1,m)
        if(n%i==0)
        {
            ans+=i*phi(n/i);
            if(i*i<n)ans+=(n/i)*phi(i);  
        }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：andyli (赞：1)

注意到$\gcd(i, n)$一定是$n$的约数，而$n$的约数只有$O(\sqrt{n})$个。  
考虑枚举$n$的约数（设为$d$），再求出满足$\gcd(i, n)=d$的$i$有多少个。  

假设$\gcd(i,n)=d$，则$gcd(\frac{i}{d},\frac{n}{d})=1$  
注意到$\frac{i}{d}\leq \frac{n}{d}$，因此共有$\varphi(\frac{n}{d})$个$i$满足条件。  
质因数分解求出每个$\varphi(\frac{n}{d})$即可。  

时间复杂度$O(\sqrt{n})$。  

代码如下（[快读模板](https://andyli.blog.luogu.org/read-template)）：  
```cpp
LL phi(LL n)
{
    LL ans = n;
    for (LL i = 2; i * i <= n; i++)
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            ans = ans / i * (i - 1);
        }
    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}
int main()
{
    LL n;
    io.read(n);
    LL ans = 0LL;
    for (LL d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            LL d2 = n / d;
            if (d2 != d)
                ans += d * phi(d2) + d2 * phi(d);
            else
                ans += phi(d) * d;
        }
    }
    writeln(ans);
    return 0;
}
```

---

## 作者：清尘 (赞：1)

#### 解题思路
gcd(i,n)的值一定是n的一个约数，并且n的约数个数并不大(好像不会超过5000)

由此可以想到枚举n的每个约数p，再求出gcd(i,n)的值为p的i的个数num，答案res就为p*num的和

因此只要求出对于每个P满足要求的i的个数即可解决问题

设当gcd(i,n)为p时，i=p·k1,n=p·k2.易得此时k1,k2互质

求与一个数互质的数的个数？这正是欧拉函数解决的问题

由于n的约数很少（计算次数少），不需要用欧拉函数的递推式，直接按照公式计算就可以了

#### 代码
```cpp
#include <stdio.h>
#include <cmath>
using namespace std;
#define ll long long
const int N = 1e5;
ll n, tot, res, h, k[N], p[N];
inline ll P (ll x) { return x * x; }
inline void Pre_work () {        //素数线性筛模板 
	for (int i = 2; P(i) <= n; ++i) {
		if (!k[i]) p[++tot] = i;
		for (int j = 1; j <= tot and P (i * p[j]) <= n; ++j) {
			k[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}
inline ll f (ll x) {
	ll res (x);
	for (int i = 1; i <= tot and p[i] <= x; ++i)    //套用欧拉公式计算 
	  if (x % p[i] == 0) {
	  	res = res * (p[i] - 1) / p[i]; 
	  	while (x % p[i] == 0) x /= p[i];
	  }
	return res * (x - 1 + (x == 1)) / x;        //最后x可能是个质数，要再计算一次（ x为 1时需要特判） 
}
int main() {
	scanf ("%lld", &n);
	Pre_work ();     //找出1——sqrt(n)的素数 
	for (int i = 1; P(i) <= n; ++i)   //找出 n的约数 
		if (n % i == 0) res += i * f (n / i) + (P(i) != n) * n / i * f (i); //如果i*i==n要特判防止重复计算 
	printf ("%lld\n", res);
	return 0;
}
```


---

## 作者：Register (赞：1)

## 一个新的暴力方法
### 解题思路
- 最近经常刷一种类型的题：

> $gcd(i,j)=x$的有多少个，所有的数$gcd$的和是多少，其中$1\le i,j\le10^5$或$10^6$

这种题可以直接使用类似于埃氏筛的容斥原理方法，统计$gcd$是$x$的有多少个

这道题目$n$的范围变成了$1\le n\le2^{32}$，但是$gcd$只有$1$个参数了

依然想采用原来的容斥原理，这时候$gcd$只有可能是$n$的因数

因此可以采用$1$个$map$当做原来的数组，由于不方便枚举倍数相减，可以直接在计算出一个$gcd$的数量后枚举因数相减

时间复杂度？不清楚，乱胡是$\Theta(n log n log log \sqrt{n})$
### 代码

```cpp
#include <cstdio>
#include <map>
#define int long long
using namespace std;
map<int,int> f;
int n,m,ans,sum1,sum2,a[1<<16|1],b[1<<16|1],p[1<<17|1];
inline int read(){
	char ch=getchar();int res=0,w=1;
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {res=res*10+ch-'0';ch=getchar();}
	return res*w;
}
signed main(){
	n=read();
	for(register int i=1;i*i<=n;i++)
		if(i*i==n) a[++sum1]=i;
		else if(n%i==0) {a[++sum1]=i;b[++sum2]=n/i;}
	for(register int i=1;i<=sum1;i++) p[++m]=a[i];
	for(register int i=sum2;i;i--) p[++m]=b[i];
	for(register int i=m;i;i--)
	{
		ans+=(f[p[i]]+=n/p[i])*p[i];
		if(p[i]!=1) f[1]-=f[p[i]];
		for(register int j=2;j*j<=p[i];j++)
			if(j*j==p[i]) f[j]-=f[p[i]];
			else if(p[i]%j==0) {f[j]-=f[p[i]];f[p[i]/j]-=f[p[i]];}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

