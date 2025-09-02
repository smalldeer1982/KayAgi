# 【模板】扩展卢卡斯定理/exLucas

## 题目背景

这是一道模板题。

## 题目描述

求

$${\mathrm{C}}_n^m \bmod{p}$$

其中 $\mathrm{C}$ 为组合数。

## 说明/提示

对于 $100 \%$ 的数据，$1 \le m \le n \le {10}^{18}$，$2 \le p \le {10}^6$，**不保证** $p$ 是质数。

## 样例 #1

### 输入

```
5 3 3```

### 输出

```
1```

## 样例 #2

### 输入

```
666 233 123456```

### 输出

```
61728```

# 题解

## 作者：Fading (赞：246)

### 扩展 Lucas 定理 exLucas 

其他题解讲的都很不清楚，而且很奇怪。。。

所以我来发一篇良心题解，求大家点赞~

### 问题

求

$$C_n^m \bmod{p}$$

其中$p\leq 10^6$

### 算法

设

$$p=p_1^{\alpha_1}p_2^{\alpha_2}...$$

求出

$$\left\{\begin{aligned}C_n^m \bmod\ {p_1^{\alpha_1}} \\C_n^m \bmod\ {p_2^{\alpha_2}}\\ ......\end{aligned} \right.$$

最后用中国剩余定理合并即可。

假设我们现在要求

$$C_n^m\bmod{P^k}([P\in {\texttt{prime}}])$$

$$\therefore\ =\frac {n!}{m!(n-m)!}\bmod{P^k}$$

我们无法求得$m!,(n-m)!$的逆元，理由很简单，不一定有解。

怎么办呢？发现$a$对$p$有逆元的充要条件为

$$\gcd(a,p)=1$$

所以我们换一个式子：

$$=\frac {\frac {n!}{P^{x}}}{\frac {m!}{P^{y}}\frac {(n-m)!}{P^{z}}}P^{x-y-z}\bmod{P^k}$$

其中

$x$为$n!$中$P$因子的个数（包含多少$P$因子）。

其他都是同理的。

所以如果我们对于一个$n$，可以求出$\frac {n!}{P^x}$，那不就完事了吗？（这样我们就可以求逆元了）

问题等价于求

$$\frac {n!}{P^x}\bmod{P^k}$$

我们对$n!$进行变形：

$$n!=1\cdot 2\cdot 3\cdot ...\cdot n$$

$$=(P\cdot 2P\cdot 3P...)(1\cdot 2\cdot ...)$$

左边是$1\sim n$中所有$\leq n$的$P$的倍数。

右边反之。

因为$1\sim n$中有$\lfloor \frac nP\rfloor$个$P$的倍数，

$$\therefore\ =P^{\lfloor \frac nP\rfloor}(1 \cdot 2 \cdot 3...)(1\cdot 2\cdot ...)$$

$$=P^{\lfloor \frac nP\rfloor}(\lfloor \frac nP\rfloor)!\prod_{i=1,i\not\equiv 0\pmod {P}}^ni$$


显然后面这个$\bmod\ P$是有循环节的。

$$=P^{\lfloor \frac nP\rfloor}(\lfloor \frac nP\rfloor)!(\prod_{i=1,i\not\equiv 0\pmod {P}}^{P^k}i)^{\lfloor \frac n{P^k}\rfloor}(\prod_{i=P^k\lfloor \frac n{P^k}\rfloor,i\not\equiv 0\pmod {P}}^ni)$$

其中

$$(\prod_{i=1,i\not\equiv 0\pmod {P}}^{P^k}i)^{\lfloor \frac n{P^k}\rfloor}$$


是循环节$1\sim P$中所有无$P$因子数的乘积。

$$(\prod_{i=P^k\lfloor \frac n{P^k}\rfloor,i\not\equiv 0\pmod {P}}^ni)$$

是余项的乘积。

比如

$$22!\equiv(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8)(10\cdot 11\cdot 13\cdot 14\cdot 16\cdot 17)(19\cdot 20\cdot 22)(3\cdot 6\cdot 9\cdot 12\cdot 15\cdot 18\cdot 21)\pmod {3^2}$$

$$\equiv(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8)^2(19\cdot 20\cdot 22)3^7(1\cdot 2\cdot 3\cdot 4\cdot 5\cdot 6\cdot 7)\pmod {3^2}$$

$$\equiv3^77!(1\cdot 2\cdot 4\cdot 5\cdot 7\cdot 8)^2(19\cdot 20\cdot 22)\pmod {3^2}$$

发现正好是一样的。$\lfloor \frac {22}{3^2}\rfloor=2 $

理解了吧...

$$=P^{\lfloor \frac nP\rfloor}(\lfloor \frac nP\rfloor)!(\prod_{i=1,i\not\equiv 0\pmod {P}}^{P^k}i)^{\lfloor \frac n{P^k}\rfloor}(\prod_{i=P^k\lfloor \frac n{P^k}\rfloor,i\not\equiv 0\pmod {P}}^ni)$$

发现前面这个$P^{\lfloor \frac nP\rfloor}$是要除掉的。

然而$(\lfloor \frac nP\rfloor)!$里可能还包含$P$。

所以，我们定义函数：

$$f(n)=\frac {n!}{P^x}$$

$$\therefore\ f(n)=f(\lfloor \frac nP\rfloor)(\prod_{i=1,i\not\equiv 0\pmod {P}}^{P^k}i)^{\lfloor \frac n{P^k}\rfloor}(\prod_{i=P^k\lfloor \frac n{P^k}\rfloor,i\not\equiv 0\pmod {P}}^ni)$$

这样就好了。时间复杂度是$O(\log_{P}n)$。

边界$f(0)=1$

看看原式

$$=\frac {\frac {n!}{P^{x}}}{\frac {m!}{P^{y}}\frac {(n-m)!}{P^{z}}}P^{x-y-z}\bmod{P^k}$$

$$=\frac {f(n)}{f(m)f(n-m)}P^{x-y-z}\bmod{P^k}$$

由于$f(m)$一定与$P^k$互质，所以我们可以直接用$exgcd$求逆元啦。

最后我们还有一个问题，$P^{x-y-z}$咋求?

其实很好求。

比如说，我们要求$f(n)=\frac {n!}{P^x}$中的$x$

设$g(n)=x$(上述的$x$)

再看看阶乘的式子

$$n!=P^{\lfloor \frac nP\rfloor}(\lfloor \frac nP\rfloor)!(\prod_{i=1,i\not\equiv 0\pmod {P}}^{P^k}i)^{\lfloor \frac n{P^k}\rfloor}(\prod_{i=P^k\lfloor \frac n{P^k}\rfloor,i\not\equiv 0\pmod {P}}^ni)$$

很显然我们要的就是$P^{\lfloor \frac nP\rfloor}$

而且$(\lfloor \frac nP\rfloor)!$可能还有$P$因子。

所以我们可以得到以下递推式

$$g(n)=\lfloor \frac nP\rfloor+g(\lfloor \frac nP\rfloor)$$

时间复杂度是$O(\log_{P}n)$。

边界$g(n)=0(n<P)$

所以答案就是

$$=\frac {\frac {n!}{P^{x}}}{\frac {m!}{P^{y}}\frac {(n-m)!}{P^{z}}}P^{g(n)-g(m)-g(n-m)}\bmod{P^k}$$

最后用中国剩余定理合并答案即可得到$C_n^m$。

代码:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#ifndef Fading
inline char gc(){
    static char now[1<<16],*S,*T;
    if (T==S){T=(S=now)+fread(now,1,1<<16,stdin);if (T==S) return EOF;}
    return *S++;
}
#endif
#ifdef Fading
#define gc getchar
#endif
void exgcd(ll a,ll b,ll &x,ll &y){
    if (!b) return (void)(x=1,y=0);
    exgcd(b,a%b,x,y);
    ll tmp=x;x=y;y=tmp-a/b*y;
}
ll gcd(ll a,ll b){
    if (b==0) return a;
    return gcd(b,a%b); 
}
inline ll INV(ll a,ll p){
    ll x,y;
    exgcd(a,p,x,y);
    return (x+p)%p;
}
inline ll lcm(ll a,ll b){
    return a/gcd(a,b)*b;
}
inline ll mabs(ll x){
    return (x>0?x:-x);
}
inline ll fast_mul(ll a,ll b,ll p){
    ll t=0;a%=p;b%=p;
    while (b){
        if (b&1LL) t=(t+a)%p;
        b>>=1LL;a=(a+a)%p;
    }
    return t;
}
inline ll fast_pow(ll a,ll b,ll p){
    ll t=1;a%=p;
    while (b){
        if (b&1LL) t=(t*a)%p;
        b>>=1LL;a=(a*a)%p;
    }
    return t;
}
inline ll read(){
    ll x=0,f=1;char ch=gc();
    while (!isdigit(ch)) {if (ch=='-') f=-1;ch=gc();}
    while (isdigit(ch)) x=x*10+ch-'0',ch=gc();
    return x*f;
}
inline ll F(ll n,ll P,ll PK){
    if (n==0) return 1;
    ll rou=1;//循环节
    ll rem=1;//余项 
    for (ll i=1;i<=PK;i++){
        if (i%P) rou=rou*i%PK;
    }
    rou=fast_pow(rou,n/PK,PK);
    for (ll i=PK*(n/PK);i<=n;i++){
        if (i%P) rem=rem*(i%PK)%PK;
    }
    return F(n/P,P,PK)*rou%PK*rem%PK;
}
inline ll G(ll n,ll P){
    if (n<P) return 0;
    return G(n/P,P)+(n/P);
}
inline ll C_PK(ll n,ll m,ll P,ll PK){
    ll fz=F(n,P,PK),fm1=INV(F(m,P,PK),PK),fm2=INV(F(n-m,P,PK),PK);
    ll mi=fast_pow(P,G(n,P)-G(m,P)-G(n-m,P),PK);
    return fz*fm1%PK*fm2%PK*mi%PK;
}
ll A[1001],B[1001];
//x=B(mod A)
inline ll exLucas(ll n,ll m,ll P){
    ll ljc=P,tot=0;
    for (ll tmp=2;tmp*tmp<=P;tmp++){
        if (!(ljc%tmp)){
            ll PK=1;
            while (!(ljc%tmp)){
                PK*=tmp;ljc/=tmp;
            }
            A[++tot]=PK;B[tot]=C_PK(n,m,tmp,PK);
        }
    }
    if (ljc!=1){
        A[++tot]=ljc;B[tot]=C_PK(n,m,ljc,ljc);
    }
    ll ans=0;
    for (ll i=1;i<=tot;i++){
        ll M=P/A[i],T=INV(M,A[i]);
        ans=(ans+B[i]*M%P*T%P)%P;
    }
    return ans;
}
signed main(){
    ll n=read(),m=read(),P=read();
    printf("%lld\n",exLucas(n,m,P));
    return 0;
}

```


---

## 作者：Great_Influence (赞：94)

扩展卢卡斯定理。

首先，得确定先会扩展欧几里得算法和扩展中国剩余定理。至于卢卡斯定理，那并不重要。

设$p=\prod p_i^{k_i}$，则:

假如你已经求出了$\binom{n}{m}\bmod{p_i^{k_i}}$，那么明显是可以利用$CRT$来合并答案的。

那么问题转换为如何求出$\binom{n}{m}\bmod{p^k}$($p$是质数)。

可以知道:
$$\binom{n}{m}=\frac{n!}{m!(n-m)!}$$
那么问题即转化为求出几个阶乘和阶乘的逆元。

现在，问题归为如何快速求出阶乘。

为了便于统计出现了多少个$p$的次幂，先将阶乘中所有$p$的倍数提出来。可以简单算出，一共有$\displaystyle\lfloor\frac{n}{p}\rfloor$个。这中间每一项都除去$p$，可以得到$\displaystyle\lfloor\frac{n}{p}\rfloor!$。该部分可以选择递归求解。

那么接下来只剩下非$p$的倍数的几项了。通过简单观察可以知道，剩余几项具有循环节，循环节长度小于$p^k$。原因是剩余项关于$p$具有循环节，而$a+p^k\equiv a\pmod{p^k}$，所以可以一起计算。结果会剩下几项凑不齐一个循环节，但是这几项长度已经小于一个循环节了，可以选择暴力求解。

为了更好地理解上方几条，可以举个栗子:

当$n=19,p=3,k=2$时:

$n!=1*2*3*\cdots*19$

$=(1*2*4*5*7*8*10*11*13*14*16*17*19)*3^{6}*6!$

$\equiv(1*2*4*5*7*8)^2*19*3^6*6!$

这样就可以在可承受的时间复杂度内求出阶乘。但是，为了达到除法的效果，我们需要考虑$p$的次幂一共出现了多少次。根据前面的计算，可以知道只除去一个$p$时，$n!$内包括了$\displaystyle\lfloor\frac{n}{p}\rfloor$个$p!$。剩下的数字如果要可能存在$p$的次幂也可以归为一个阶乘，即$\displaystyle\lfloor\frac{n}{p}\rfloor!$。设$f(n)$表示$n!$中有多少个$p$的因数，那么，我们就可以得到一个递推式:
$$f(n)=f(\displaystyle\lfloor\frac{n}{p}\rfloor)+\displaystyle\lfloor\frac{n}{p}\rfloor$$
边界为:
$$f(x)=0(x<p)$$

开始计算时间复杂度。

首先是中国剩余定理的复杂度，可以简单查到是$O(plogP)$的。(其中$P$是模数，$p$是最大质因子)。

然后是求阶乘复杂度。当求$n!\bmod p^k$时，时间复杂度为$O(p^klogn(log_pn-k))$(玄学)

最后是求逆元的复杂度。利用扩展欧几里得可以做到$O(logp)$(可忽略)。

因此，总复杂度为
$$O(\sum p^klogn(log_pn-k)+plogP)$$

这个复杂度和$PlogP$同级。

ext:

如果要同时计算多个组合数膜同一个合数时，可以选择对每个质因子 $p$ ，对每个 $n\le p^k$ 预处理出小于等于它且不整除 $p$ 的数字之积。这样的话，求阶乘的复杂度会变成 $O(\log_{p^k}n)$ ，总复杂度就可以降到

$$O(\sum p^k +T\log_{p^k} n)$$

代码(ext部分没有贴代码):
```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(!b){x=1;y=0;return a;}
    ll res=exgcd(b,a%b,x,y),t;
    t=x;x=y;y=t-a/b*y;
    return res;
}

ll p;

inline ll power(ll a,ll b,ll mod)
{
    ll sm;
    for(sm=1;b;b>>=1,a=a*a%mod)if(b&1)
        sm=sm*a%mod;
    return sm;
}

ll fac(ll n,ll pi,ll pk)
{
    if(!n)return 1;
    ll res=1;
    for(register ll i=2;i<=pk;++i)
        if(i%pi)(res*=i)%=pk;
    res=power(res,n/pk,pk);
    for(register ll i=2;i<=n%pk;++i)
        if(i%pi)(res*=i)%=pk;
    return res*fac(n/pi,pi,pk)%pk;
}

inline ll inv(ll n,ll mod)
{
    ll x,y;
    exgcd(n,mod,x,y);
    return (x+=mod)>mod?x-mod:x;
}

inline ll CRT(ll b,ll mod){return b*inv(p/mod,mod)%p*(p/mod)%p;}

const int MAXN=11;

static ll n,m;

static ll w[MAXN];

inline ll C(ll n,ll m,ll pi,ll pk)
{
    ll up=fac(n,pi,pk),d1=fac(m,pi,pk),d2=fac(n-m,pi,pk);
    ll k=0;
    for(register ll i=n;i;i/=pi)k+=i/pi;
    for(register ll i=m;i;i/=pi)k-=i/pi;
    for(register ll i=n-m;i;i/=pi)k-=i/pi;
    return up*inv(d1,pk)%pk*inv(d2,pk)%pk*power(pi,k,pk)%pk;
}

inline ll exlucus(ll n,ll m)
{
    ll res=0,tmp=p,pk;
	static int lim=sqrt(p)+5;
    for(register int i=2;i<=lim;++i)if(tmp%i==0)
    {
        pk=1;while(tmp%i==0)pk*=i,tmp/=i;
        (res+=CRT(C(n,m,i,pk),pk))%=p;
    }
	if(tmp>1)(res+=CRT(C(n,m,tmp,tmp),tmp))%=p;
    return res;
}

int main()
{
    scanf("%lld%lld%d",&n,&m,&p);
    printf("%d\n",exlucus(n,m));
    return 0;
}
```

---

## 作者：Eznibuil (赞：9)

Upd：2023.9.7 改进了一点式子。

看看题解区其他大佬都是用的神仙方法，蒟蒻我看不懂，所以决定使用和 $\text{Lucas}$ 一样的套路（递归解决）处理这个柿子……

其中 $n/p$ 表示 $\lfloor\frac np\rfloor$，$n_p!$ 表示 $\dfrac{n!}{\prod_{i=1}^{n/p}pi}$（就是把 $n!$ 中所有含 $p$ 的项排除）。
$$
\begin{aligned}
\binom nm&\equiv\frac{n!}{m!(n-m)!}\\
&\equiv\frac{n_p!}{m_p!(n-m)_ p!}\cdot p^{n/p-m/p-(n-m)/p}\cdot\frac{(n/p)!}{(m/p)!((n-m)/p)!}\\
&\equiv\tiny\frac{(n\bmod p^k)_ p!}{(m\bmod p^k)_ p!((n-m)\bmod p^k)_ p!}\cdot(p^k-1)_ p!^{n/p^k-m/p^k-(n-m)/p^k}\cdot p^{n/p-m/p-(n-m)/p}\cdot\frac{(n/p)!}{(m/p)!((n-m)/p)!}\\
&\equiv\tiny\frac{(n\bmod p^k)_ p!}{(m\bmod p^k)_ p!((n-m)\bmod p^k)_ p!}\cdot\begin{cases}(-1)^{n/p^k-m/p^k-(n-m)/p^k}&p>2\textrm{ 或 }k<3\\1&p=2\textrm{ 且 }k\ge3\end{cases}\cdot\begin{cases}\dbinom{n/p}{m/p}&,\operatorname{if}n/p=m/p+(n-m)/p\\(n/p)\cdot p\cdot\dbinom{n/p-1}{m/p}&,\operatorname{otherwise}\end{cases}\\
&\pmod{p^k}
\end{aligned}
$$

注意到最后一步运用了扩展威尔逊定理。（闲话：最开始应用扩展威尔逊定理时忘了讨论了，没想到还通过了，看来数据真的弱。）

定睛一看，柿子前面可以 $O(p^k)$ 预处理，后面可以分类讨论加上递归。

所以对着 $p^k$ 取一个模是 $O(p^k+\log n)$ 的。

那么分解模数 $p=\prod p_i^{k_i}$，最后使用中国剩余定理合并，就可以愉快的 $\text{AC}$ 了。

总时间复杂度 $O\left(\sum(p_i^{k_i}+\log n)\right)$。

顺便说一句，下面的代码可以过 $2\le p\le 10^{18}$ 的数据，只要分解出的满足 $p_i^{k_i}\le10^6$ 就行。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
bool ip[1000001];
ll lp,p[1000001],n,k,m;
lll fac[1000001],inf[1000001],lm,r[1000001],cp[1000001],cm[1000001],ans;
void Euler(ll n)
{
	for(ll i=2ll;i<=n;i++)
		ip[i]=1ll;
	for(ll i=2ll;i<=n;i++)
	{
		if(ip[i])
			p[lp++]=i;
		for(ll j=0ll;j<lp&&i*p[j]<=n;j++)
		{
			ip[i*p[j]]=0;
			if(i%p[j]==0ll)
				break;
		}
	}
	return;
}
lll Pow(lll a,lll b,lll p=m)
{
	ll s=1ll;
	for(a%=p;b;a=a*a%p,b>>=1ll)
		if(b&1ll)
			s=s*a%p;
	return s;
}
void init(lll p,lll m)
{
	fac[0]=inf[0]=1ll;
	for(ll i=1ll;i<=m;i++)
		if(i%p)
			fac[i]=fac[i-1]*i%m;
		else
			fac[i]=fac[i-1];
	inf[m-1]=Pow(fac[m-1],m/p*(p-1ll)-1ll,m);
	for(ll i=m-1ll;i>1ll;i--)
		if(i%p)
			inf[i-1]=inf[i]*i%m;
		else
			inf[i-1]=inf[i];
	return;
}
lll Lucas(lll n,lll k,lll p,lll m)
{
	return k<0||k>n?0:n<p&&k<p?fac[n]*inf[k]%m*inf[n-k]%m:fac[n%m]%m*inf[k%m]%m*inf[(n-k)%m]%m*(n/m-k/m-(n-k)/m&&(p>2||m<8)?m-1:1)%m*(n/p>k/p+(n-k)/p?Lucas(n/p-1,k/p,p,m)*(n/p)%m*p%m:Lucas(n/p,k/p,p,m))%m;
}
int main()
{
	scanf("%lld%lld%lld",&n,&k,&m),Euler(1000000ll);
	for(ll i=0ll;i<lp&&p[i]<=m;i++)
		if(m%p[i]==0ll)
		{
			cp[lm]=p[i],cm[lm]=1ll;
			while(m%p[i]==0ll)
				cm[lm]*=p[i],m/=p[i];
			m*=cm[lm],init(p[i],cm[lm]),r[lm]=Lucas(n,k,p[i],cm[lm]),lm++;
		}
	for(ll i=0ll;i<lm;i++)
		ans=(ans+r[i]*(m/cm[i])%m*Pow(m/cm[i],cm[i]/cp[i]*(cp[i]-1ll)-1ll,cm[i])%m)%m;
	printf("%lld",ll(ans));
	return 0;
}
```

---

## 作者：BlueQuantum (赞：6)

# 扩展卢卡斯

求：
$$
\binom n m \bmod p
$$
其中 $p$ 不保证为质数。

------

### 前置知识

中国剩余定理（CRT）

ExGCD求逆元

（应该都会吧）

-----

考虑令 $p=p_1^{k_1}p_2^{k_2}p_3^{k_3} \dots$

原问题转化为求：
$$
\begin{cases}
C_n^m \bmod p_1^{k_1} \\
C_n^m \bmod p_2^{k_2} \\
C_n^m \bmod p_3^{k_3} \\
\dotsm
\end{cases}
$$

的一个解，使用中国剩余定理合并即可。

针对其中一个式子 $C_n^m \bmod p^{k}$ 即 $\frac {n!} {m!(n-m)!} \bmod p^k$ ，使用求逆元的方法是不行的，因为 $p$ 不保证为质数， $m!(n-m)!$ 可能不存在逆元。

设 $f(n)=n! \bmod p^k$ ，进一步考虑，既然不互质，那就把他们的公因子都约掉，我们把阶乘展开看一看：
$$
\begin{aligned}
n! &= 1 \times 2 \times 3 \cdots n \\
   &= (p \cdot 2p \cdot 3p \cdots) \cdot [1 \times 2 \times 3 \cdots (p-1) \cdot (p + 1) \cdot (p + 2) \cdots] \\

   &= p^{\lfloor \frac{n}{p} \rfloor} (1 \times 2 \times 3 \cdots) \cdot [1 \times 2 \times 3 \cdots (p-1)] \cdot [(p + 1) \cdot (p + 2) \cdots)] \\
   & \text{注意，这里很重要！！！} \\
   &= \large p^{\lfloor \frac{n}{p} \rfloor} (\frac{n}{p})! \prod_{p \nmid i}^n i \\
   &= \large p^{\lfloor \frac{n}{p} \rfloor} (\frac{n}{p})! (\prod_{p \nmid i}^{p^k} i)^{\frac {n}{p^k}} \textit{rest} \\
\end{aligned}
$$

其中 $\text{rest}$ 是指最后不够一整段 $p^k$ 的剩下的项， $\displaystyle \large (\prod_{p \nmid i}^{p^k} i)$ 是在 $\bmod p^k$ 意义下的一个循环节，这样的循环节有 $\frac n {p^k}$ 个。

每进行一次上述操作，我们都可以从阶乘提取出 $p^{\lfloor \frac n p \rfloor}$ 这个因子，并把原问题变为一个规模更小的问题 $f(\frac n p)$ ，可以递归进行，并在过程中累加 $\lfloor \frac n p \rfloor$ ，记为 $h(n)$ ，最后的 $h(n)$ 就是 $n!$ 中 $p$ 这个因子的数量。

至此，我们成功把 $n!$ 里的 $p$ 的因子分离出来。回归原来的问题 $C_n^m \bmod p^{k}$ ：
$$
\large \frac {\frac {n!}{p^{h(n)}}} {\frac {m!}{p^{h(m)}}\frac {(n-m)!}{p^{h(n-m)}}} p^{h(n)-h(m)-h(n-m)} \bmod p^k
$$
即
$$
\frac{f(n)}{f(m)f(n-m)} p^{h(n)-h(m)-h(n-m)} \bmod p^k
$$

由于 $f(n)$ 已经是被约掉 $p$ 因子的，一定有逆元，于是CRT的一个式子就解决了，最后合并就好了。

> Talk is cheap, show me your code

```cpp
#include <cstdio>

typedef long long ll;
const int N = 100000;
int p, cnt, pri[N], k[N], cpoy_p;
ll n, m;

inline ll qpow(ll base, ll exp, const int &mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) return x = 1, y = 0, void();
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

namespace CRT {

int a[N], ans = 0, pk;
ll inv, y;

inline int solve() {
    for (int i = 1; i <= cnt; ++i) {
        pk = qpow(pri[i], k[i], p + 1);
        exgcd(p / pk, pk, inv, y);
        ans += a[i] * inv % p * (p / pk) % p;
        if (ans >= p) ans -= p;
        if (ans < 0) ans += p;
    }
    return ans;
}

}  // namespace CRT

namespace Exlucas {

int prime, mod;  // mod = p^k
ll h;            //指数也要开long long

inline void MOD(ll &x, const int &mod) {
    if (x >= mod) x %= mod;
}

ll f(ll n) {
    if (n == 0) return 1;
    h += n / prime;
    ll res = 1, tmp = 1;
    res *= f(n / prime);
    MOD(res, mod);
    for (int i = 1; i <= mod; ++i) {
        if (i % prime) (tmp *= i) %= mod;
    }
    res *= qpow(tmp, n / mod, mod);
    MOD(res, mod);
    for (ll i = n / mod * mod; i <= n; ++i) {
        if (i % prime) {
            res *= i % mod;
            MOD(res, mod);
        }
    }
    return res;
}

inline ll solve(int i) {
    prime = pri[i], mod = qpow(prime, k[i], p + 1);
    int exp = 0;
    ll res = 1, inv, y;
    h = 0, res *= f(n), exp += h;

    h = 0, exgcd(f(m), mod, inv, y);
    inv = (inv % mod + mod) % mod;
    res *= inv;
    MOD(res, mod);
    exp -= h;

    h = 0, exgcd(f(n - m), mod, inv, y);
    inv = (inv % mod + mod) % mod;
    res *= inv;
    MOD(res, mod);
    exp -= h;

    return res * qpow(prime, exp, mod) % mod;
}

}  // namespace Exlucas

signed main() {
#ifndef ONLINE_JUDGE
#ifdef LOCAL
    freopen("testdata.in", "r", stdin);
    freopen("testdata.out", "w", stdout);
#else
    freopen("ExLucas.in", "r", stdin);
    freopen("ExLucas.out", "w", stdout);
#endif
#endif

    scanf("%lld%lld%d", &n, &m, &p);
    cpoy_p = p;
    for (int i = 2; i * i <= p; ++i) {
        if (cpoy_p % i == 0) {
            pri[++cnt] = i;
            while (cpoy_p % i == 0) { cpoy_p /= i, k[cnt]++; }
        }
    }
    if (cpoy_p != 1) pri[++cnt] = cpoy_p, k[cnt] = 1;
    for (int i = 1; i <= cnt; ++i) { CRT::a[i] = Exlucas::solve(i); }
    printf("%d", CRT::solve());
    return 0;
}
```



---

## 作者：maxiaomeng (赞：1)

求 ${\mathrm{C}}_n^m \bmod{p}$，$p$ 不一定是质数。

首先有组合数公式：

$${\mathrm{C}}_n^m=\frac{n!}{(n-m)!m!}$$

但是在 $p$ 为合数时上面的方法遇到了困难：不一定有逆元。

这时可以先对 $p$ 质因数分解，得到若干形如 $P^Q$（$P$ 为质数）的数的乘积，显然这些数两两互质，因此对每一个求出 ${\mathrm{C}}_n^m$ 对它取模的结果，用 CRT 合并即可。现在问题转化为求出：
$${\mathrm{C}}_n^m \bmod{P^Q}=\frac{n!}{(n-m)!m!} \bmod{P^Q}$$

$P^Q$ 这个数满足不被 $P$ 整除的数就是跟它互质的数。所以我们可以把三个阶乘中的 $P$ 质因子全部取出单独处理，以 $n!$ 为例，也就是转换为如下形式：

$$n!=F(n)\times P^{G(n)}\ (\gcd(F(n),P)=1)$$

其中，$G(n)$，即 $n!$ 中的 $P$ 因子个数，求解方法是：将 $n$ 不断除以 $P$ 下取整，直到结果为 $0$，再将每次下取整的结果加起来。这样有 $i$ 个 $P$ 因子的数恰好贡献 $i$ 次。例如 $P=3$ 时 $G(10)=\lfloor \frac{10}{3}\rfloor+\lfloor \frac{10}{3^2}\rfloor=3+1=4$。

而 $F(i)$ 则是 $n!$ 去除所有 $P$ 因子的剩余部分，显然，所有不被 $P$ 整除的数会被原封不动的乘进 $F(i)$，但这些数太多了，不能暴力乘。由于只需要 $F(i) \bmod P^Q$ 的结果，而 $P^Q\leq p \leq 10^6$，可以以 $P^Q$ 为一周期，暴力计算其中一周期，其它周期乘积与它模 $P^Q$ 同余，未形成完整的周期的数暴力乘即可。

而被 $P$ 整除的数，也就是 $1\times P,\ 2\times P,\ \dots,\ \lfloor \frac{n}{P} \rfloor \times P$ 要先除掉所有 $P$ 因子才能乘进去，先将这些数都除以 $P$，得到 $1,2,\ \dots,\ \lfloor \frac{n}{P} \rfloor$。现在要求这些数去掉 $P$ 因子后的乘积，正是 $F(\lfloor \frac{n}{P} \rfloor)$。因此可以用递归求解 $F(n)$。

因为 $F(n)$ 不被 $P$ 整除，所以与 $P^Q$ 互质，一定有逆元，可用 exgcd 求。最终，组合数模 $P^Q$ 转化成如下形式：

$${\mathrm{C}}_n^m \bmod{P^Q}=\frac{n!}{(n-m)!m!}=\frac{F(n)}{F(n-m)F(m)}\times P^{G(n)-G(n-m)-G(m)} \bmod{P^Q}$$

**记得开 `__int128`。**

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=1000005;
int n,m,mod,a[N],p[N],pq[N],c;
inline int fp(int x,int y,int m){
	int r=1;
	while(y){
		if(y&1)r=r*x%m;
		x=x*x%m;
		y>>=1;
	}
	return r;
}
int exgcd(int a,int b,int &x,int &y,int c){
	if(!b){
		x=c/a,y=0;
		return a;
	}
	int t=exgcd(b,a%b,y,x,c);
	y-=a/b*x;
	return t;
}
int F(int a,int p,int pq){
	if(!a) return 1;
	int x=F(a/p,p,pq);
	int y=1;
	for(int i=1;i<=pq;i++){
		if(i%p) y=(y*i)%pq;
	}
	y=fp(y,a/pq,pq);
	int z=1;
	for(int i=a/pq*pq+1;i<=a;i++){
		if(i%p) z=(__int128(1)*z*i)%pq; //此处须开__int128！！！ 
	}
	return (((x*y)%pq)*z)%pq;
}
inline int G(int x,int p){
	int r=0;
	while(x) r+=(x/=p);
	return r;
}
inline int cc(int n,int m,int p,int pq){
	int x=0,y=0;
	exgcd(F(n-m,p,pq)*F(m,p,pq)%pq,pq,x,y,1);
	int g=fp(p,G(n,p)-G(n-m,p)-G(m,p),pq);
	x=(x%pq+pq)%pq;
	return ((F(n,p,pq)*g)%pq*x)%pq;
}
inline int C(int n,int m){
	if(n<m) return 0;
	int r=0;
	for(int i=1;i<=c;i++){
		int k=mod/pq[i],x=0,y=0;
		exgcd(k,pq[i],x,y,1);
		x=(x%pq[i]+pq[i])%pq[i];
		(r+=((cc(n,m,p[i],pq[i])*k)%mod*x)%mod)%=mod;
	}
	return r;
}
inline void init(){
	int t=mod;
	for(int i=2;i*i<=t;i++){
		if(t%i==0){
			++c;
			p[c]=i;
			pq[c]=1;
			while(t%i==0){
				t/=i;
				pq[c]*=i;
			}
		}
	}
	if(t!=1){
		++c;
		p[c]=pq[c]=t;
	}
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>mod;
    init();
    cout<<C(n,m);
    return 0;
}
```

---

