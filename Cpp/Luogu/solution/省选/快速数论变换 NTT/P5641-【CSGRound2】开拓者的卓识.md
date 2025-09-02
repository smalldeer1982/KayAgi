# 【CSGRound2】开拓者的卓识

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/s6ozu5pj.png)

（上图转载于某神仙的题目描述）

小 K 又在做白日梦了。他进入到他的幻想中，发现了一个非常有趣的序列$a$和一个非常有趣的数$k$。

## 题目描述

我们记一个序列 $[l,r]$ 的 $k$ 阶子段和为 $sum_{k,l,r}$，有

$$sum_{k,l,r}=\begin{cases}\sum\limits_{i=l}^{r}a_i&,k=1\\\sum\limits_{i=l}^{r}\sum\limits_{j=i}^{r}sum_{k-1,i,j}&,k\geq 2\end{cases}$$

他现在站在位置 $1$ 上，他每一次往右开拓一个格子就可以增加他 IOI 赛场的 rp，所以他想尽可能的多开拓格子。可是每一次他从 $r$ 开拓到 $r+1$ 需要正确的回答 $sum_{k,1,r}$。小 K 不屑于算，就把任务交给你了。

## 说明/提示

### 样例解释 2

$sum_{2,1,1}=sum_{1,1,1}=1$

$sum_{2,1,2}=sum_{1,1,1}+sum_{1,1,2}+sum_{1,2,2}=1+3+2=6$

$sum_{2,1,3}=sum_{1,1,1}+sum_{1,1,2}+sum_{1,1,3}+sum_{1,2,2}+sum_{1,2,3}+sum_{1,3,3}=1+3+6+2+5+3=20$

### 数据范围

| 测试点编号 |  $n$ 的范围 |  $k$ 的范围 |  $a_i$ 的范围 |
| :-: | :-: | :-: | :-: |
|  $1\sim 2$ |  $\le 10$ |  $\le 10$ |  $\le 10$ |
|  $3\sim 8$ |  $\le 10^3$ |  $\le 10^3$ |  $\le 10^5$ |
|  $9$ |  $\le 10^5$ |  $=1$ |  $\le 998244353$ | 
|  $10$ |  $\le 10^5$ |  $=2$ |  $\le 998244353$ |
|  $11$ |  $\le 10^5$ |  $=3$ |  $\le 998244353$ |
|  $12$ |  $\le 10^5$ |  $\le 10$ |  $\le 998244353$ |
|  $13\sim 17$ |  $\le 10^5$ |  $\le 10^2$ |  $\le 998244353$ |
|  $18$ |  $\le 10^5$ |  $\le 10^5$ |  $\le 998244353$ |
|  $19\sim 25$ |  $\le 10^5$ |  $\le 998244353$ |  $\le 998244353$ |

## 样例 #1

### 输入

```
3 1
1 2 3```

### 输出

```
1 3 6```

## 样例 #2

### 输入

```
3 2
1 2 3```

### 输出

```
1 6 20```

## 样例 #3

### 输入

```
3 10
1 2 3```

### 输出

```
1 30 420```

# 题解

## 作者：Cheng_yf (赞：17)

# 题解

当我们求$sum_{k,1,r}$时，我们考虑每一个$a[i](i\in[1,r])$的贡献

通过我们对题目公式描述的理解，可以想象为求$k+1$个二元组$(l,r)$，使$l_i<=l_{i+1},r_i>=r_{i+1},i\in[1,k]$这是一个很显然的组合数问题。

所以$sum_{k,1,r}=\sum_{i=1}^{r}a[i] * C(i+k-2,k-1) * C(r-i+k-1,k-1)$

于是我们就有了一个$O(n^2)$的算法

## Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
#define maxn 1005
using namespace std;
ll power(ll n,ll x){
    ll sp=1LL;
    while(x){
        if(x&1LL) sp=(sp*n)%mod;
        n=(n*n)%mod;
        x>>=1LL;
    }return sp;
}
ll fact[maxn<<1],inv[maxn<<1];
void init(){
    fact[0]=1LL;
    for(int i=1;i<=2000;i++)
    fact[i]=fact[i-1]*i%mod;
    inv[2000]=power(fact[2000],mod-2);
    for(int i=1999;i>=0;i--)
    inv[i]=inv[i+1]*(i+1)%mod;  
}
ll C(ll n,ll m){
    return fact[n]*inv[n-m]%mod*inv[m]%mod;
}
int n;
ll k,a[maxn];
int main(){
	scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	init();
	for(int i=1;i<=n;i++){
		ll res=0;
		for(int j=1;j<=i;j++)
		res=(res+C(j+k-2,k-1)*C(i-j+k-1,k-1)%mod*a[j]%mod)%mod;
		printf("%lld ",res);
	}return 0;
}
```
考虑继续优化这个式子

我们可以发现，在一个$sum_{k,1,r}$中，$(i+k-2)+(r-i+k-1)=r+2\times k - 3$

而这个是一个常量，就可以把它变成一个卷积的式子

设$A_i=C(i+k-1,k-1)\times a_{i+1},B_i=C(i+k-1,k-1)(i\in[0,n))$

$sum_{k,1,r}=\sum_{i=0}^{r-1}A_i * B_{r-i-1} (\mod 998244353)$

因为要模$998244353$，所以可以NTT解决，~~换个模数就是MTT了~~

## Code:

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
#define maxn 100005
using namespace std;
ll power(ll n,ll x){
    ll sp=1LL;
    while(x){
        if(x&1LL) sp=(sp*n)%mod;
        n=(n*n)%mod;
        x>>=1LL;
    }return sp;
}
const ll g=3,gi=332748118;
int r[maxn*3],limit,L;
inline void NTT(ll *a,int type){
	for(int i=0;i<limit;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int mid=1;mid<limit;mid<<=1){
		ll Wn=power(type==1?g:gi,(mod-1)/(mid<<1));
		for(int j=0;j<limit;j+=(mid<<1)){
			ll w=1;
			for(int k=0;k<mid;k++,w=w*Wn%mod){
				ll x=a[j+k],y=w*a[j+k+mid]%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+mid]=(x-y+mod)%mod;
			}
		}
	}
}
int n;
ll k,a[maxn*3],b[maxn*3];
ll in[maxn];
int main(){
	scanf("%d%lld",&n,&k);
	in[0]=in[1]=1;
	for(int i=2;i<n;i++) in[i]=(mod-mod/i)*in[mod%i]%mod;//线性求逆元
	b[0]=1;
	for(int i=1;i<n;i++) b[i]=b[i-1]*(i+k-1)%mod*in[i]%mod;//因为k太大了，无法预处理阶乘，需要递推
	for(int i=0;i<n;i++)
	scanf("%lld",&a[i]),a[i]=(a[i]*b[i])%mod;//处理Ai，Bi
   //开始NTT
	limit=1;
	while(limit<=n*2) limit<<=1,L++;
	for(int i=0;i<limit;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(L-1));
	NTT(a,1);NTT(b,1);
	for(int i=0;i<limit;i++) a[i]=(a[i]*b[i])%mod;
	NTT(a,-1);
	ll inv=power(limit,mod-2);
	for(int i=0;i<n;i++) printf("%lld ",a[i]*inv%mod);
	return 0;
}
```

---

## 作者：Karry5307 (赞：17)

### 前言

CSG R2 T4 官方题解

在这里给大家谢罪了qwq

话说讲题的时候简直是在~~自砸招牌~~啊qwq，希望大家不要 d 我。

Q1：话说您咋讲的一口~~标准~~ HN 口音 + 抑扬顿挫的素普啊

A1：我是 HN 的， zhouwc 是 ZJ 的，沿海地区的口音普遍好一些啊，这是事实啊qwq

Q2：外面的喇叭声是怎么回事啊

A2：我住某一条路旁边，况且刚搬进来，噪声不可避免。

Q3：电音是什么回事啊

A3：这个是我机子的问题，要 d 去 d 我的机子，不要 d 我啊。（要是我拿到 `"zhouwc".toUpperCase().slice(4,6)` 这场比赛的 Au 可能会换一台机子再买个麦？）

Q4：你怎么这么早就停止推流啊qwq

A4：时间原因。

### 题意

题面写的太过直白，不解释。

$\texttt{Data Range:}$


![KXHzKP.jpg](https://s2.ax1x.com/2019/11/03/KXHzKP.jpg)

### 题解

话说我能跑过 100ms？

$\texttt{12 pts}$

爆搜+前缀和。

时间复杂度$O(n^k)$

$\texttt{36 pts}$

有一个很套路的多点求值做法和一个很奇妙的组合做法。

多点求值太超纲，组合做法我不会。

多点求值的做法就是把对于每一个$r$，把计算$sum_{k,1,r}$中每一个位置的数一共计算了几次用多项式你和出来。

当然这个东西你也可以组合算，但是出题人过于智障，不会。

时间复杂度$O(n^2\log^2n)$（多点求值）或者$O(n^2)$（组合）

$\texttt{68 pts}$

注意到我们的答案可以写成如下形式：

$$sum_{k,1,r}=C_{k-2+n-r}^{k-2}\sum\limits_{l=1}^{r}(pre_r-pre_{l-1})C_{k-3+l}^{k-2}$$

证明可以采用数学归纳法。把柿子拆一下（其中$pre$是前缀和）

$$sum_{k,1,r}=C_{k-2+n-r}^{k-2}(pre_r\sum\limits_{l=1}^{r}C_{k-3+l}^{k-2}-\sum\limits_{l=1}^{r}pre_{l-1}C_{k-3+l}^{k-2})$$

可以用前缀和预处理$\sum\limits_{l=1}^{r}C_{k-3+l}^{k-2}$和$\sum\limits_{l=1}^{r}pre_{l-1}C_{k-3+l}^{k-2}$。但是外面的组合数？

这个可以把里面的东西处理出来在做$k$遍前缀和，证明可以利用 P5488 的做法。

如果你的前缀和是暴力的话可以拿到这档分。

时间复杂度$O(nk)$。

$\texttt{72 pts}$

我们发现这个前缀和可以$\texttt{NTT}$优化，但是不能预处理阶乘，会导致$\color{#8e44ad}\texttt{RE}$。

$\texttt{100 pts}$

我们可以不需要预处理组合数，直接在读入的时候一并算即可。

时间复杂度$O(n\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=3e5+51,MOD=998244353,G=3,INVG=332748118;
ll fd,cnt,kk,limit,p;
ll num[MAXN],prefix[MAXN],csum[MAXN],cx[MAXN],g[MAXN];
ll rev[MAXN],res[MAXN],f[MAXN];
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
inline ll qpow(ll base,ll exponent)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=(li)res*base%MOD;
		}
		base=(li)base*base%MOD,exponent>>=1;
	}
	return res;
}
inline void NTT(ll *cp,ll cnt,ll inv)
{
    ll cur=0,res=0,omg=0;
    for(register int i=0;i<cnt;i++)
    {
        if(i<rev[i])
        {
            swap(cp[i],cp[rev[i]]);
        }
    }
    for(register int i=2;i<=cnt;i<<=1)
    {
        cur=i>>1,res=qpow(inv==1?G:INVG,(MOD-1)/i);
        for(register ll *p=cp;p!=cp+cnt;p+=i)
        {
            omg=1;
            for(register int j=0;j<cur;j++)
            {
                ll t=(li)omg*p[j+cur]%MOD,t2=p[j];
                p[j+cur]=(t2-t+MOD)%MOD,p[j]=(t2+t)%MOD;
                omg=(li)omg*res%MOD;
            }
        }
    }
    if(inv==-1)
    {
        ll invl=qpow(cnt,MOD-2);
        for(register int i=0;i<=cnt;i++)
        {
            cp[i]=(li)cp[i]*invl%MOD;
        }
    }
}
int main()
{
	fd=read(),kk=read();
	for(register int i=1;i<=fd;i++)
	{
		p=(i==1?1:(li)p*(kk-3+i)%MOD*qpow((i-1),MOD-2)%MOD);
		prefix[i]=(prefix[i-1]+(num[i]=read()))%MOD;
		csum[i]=(csum[i-1]+p)%MOD;
		cx[i]=(cx[i-1]+(li)prefix[i-1]*p%MOD)%MOD;
	}
	if(kk==1)
	{
		for(register int i=1;i<=fd;i++)
		{
			printf("%d ",prefix[i]);
		}
		puts("");
		return 0;
	}
	for(register int i=1;i<=fd;i++)
	{
		f[i-1]=res[i]=(res[i-1]+((li)prefix[i]*csum[i]%MOD-cx[i]+MOD)%MOD)%MOD;
	}
	g[0]=1,kk-=2;
	for(register int i=1;i<fd;i++)
	{
		g[i]=(li)g[i-1]*(i+kk-1)%MOD*qpow(i,MOD-2)%MOD;
	}
	cnt=1,limit=-1;
	while(cnt<(fd<<1))
	{
		cnt<<=1,limit++;
	}
	for(register int i=0;i<cnt;i++)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<limit);
	}
	NTT(f,cnt,1),NTT(g,cnt,1);
	for(register int i=0;i<cnt;i++)
	{
		f[i]=(li)f[i]*g[i]%MOD;
	}
	NTT(f,cnt,-1);
	for(register int i=0;i<fd;i++)
	{
		printf("%d ",f[i]);
	}
	puts("");
}
```

### 后记

话说请大家祝我 CSP-S 2019 rp++ 并且能去`"zhouwc".toUpperCase().slice(4,6)`，至于能不能拿到 Au 还是 bless me 吧。

~~如果能拿到 Au 我就可以换电脑+买麦+消除路边车辆的杂音了~~

---

## 作者：Serenata_Immortale (赞：8)

# 题意：

给定一个序列$a_n$,定义$sum_{k,l,r}$为:

$k=1$时，$sum_{k,l,r}=\sum\limits_{i=l}^ra_i$

$k\geq2$时，$sum_{k,l,r}=\sum\limits_{l\leq i\leq j\leq r}sum_{k-1,i,j}$

给定$k$,求$sum_{k,1,i}$，这里设$sum_{k,1,i}=ans_i$

# Solution:

在我看来这貌似是月赛最水的一道$T4$了...

比较套路的组合数学问题，直接考虑每个数$a_j$对答案$ans_i$的贡献.

也就是多少种区间选法包括了$a_j$。

反过来想就是说将初始区间$[j,j]$扩展$k$次的方案数。

答案是$C_{j+k-2}^{j-1}C_{i-j+k-1}^{i-j}$

即$ans_i=\sum\limits_{j=1}^ia_jC_{j+k-2}^{j-1}C_{i-j+k-1}^{i-j}$

### 下面给一下我自己的推导(过程太辣鸡可以忽略)：

将初始区间$[j,j]$扩展$k$次的方案数，可以把它想成这样的模型：

有一个$n*m$的网格，从$(1,1)$开始走$k$步，每步只能走到横纵坐标都大

于等于当前点的位置，求方案数。

$e.g.$

$n=3,m=2$从$(1,1)$走$3$步。令$f_{i,j}$表示走到$(i,j)$的方案数。

那么，走一步:

$1$,$1$,$1$

$1$,$1$,$1$

走两步:

$2$,$4$,$6$

$1$,$2$,$3$

走三步:

$3$,$9$,$18$

$1$,$3$,$6$

发现本质上就是求其$k$维的二维前缀和，有点类似于[P5488](https://www.luogu.org/problem/P5488)，用组合数瞎搞一

搞，方案数为是$C_{n+k-2}^{n-1}C_{m+k-2}^{m-1}$。

将初始区间$[j,j]$扩展$k$次的方案数,即为$n=j,m=i-j+1$

因此答案为$C_{j+k-2}^{j-1}C_{i-j+k-1}^{i-j}$

### 回归正题

$ans_i=\sum\limits_{j=1}^ia_jC_{j+k-2}^{j-1}C_{i-j+k-1}^{i-j}$

得到这个式子之后呢？$n<=1e5$，卷积啊！

令$A_j=a_jC_{j+k-2}^{j-1},B_j=C_{j+k-1}^{j}$

那么$ans_i=\sum\limits_{j=1}^iA_jB_{i-j}$，直接$NTT$即可。

至于求$A_j$和$B_j$，$k$比较大，需要转化成连乘形式(上升幂)，即：

$A_j=\frac{a_jk^{\overline{j-1}}}{(j-1)!},B_j=\frac{k^{\overline{j}}}
{j!}$

预处理$k$的上升幂即可。

贴上代码：

```cpp
#include<bits/stdc++.h>
#define N 400010
#define ll long long
#define mod 998244353
using namespace std;
int n,k,a[N],r[N];
ll inv[N],mi[N],A[N],B[N];
ll ksm(ll x,int y)
{
	ll fin = 1;
	while(y)
	{
		if(y&1)fin = fin*x%mod;
		x = x*x%mod,y>>=1;
	}return fin;
}
inline void NTT(ll*A,int lim,int fl)
{
	for(int i = 0;i<lim;i++)if(i<r[i])swap(A[i],A[r[i]]);
	for(int i = 2;i<=lim;i<<=1)
	{
		ll wn = ksm(3,(mod-1)/i);
		if(fl==-1)wn = ksm(wn,mod-2);
		for(int j = 0;j<lim;j+=i)
		{
			ll w = 1;
			for(int k = 0;k<i>>1;k++)
			{
				ll x = A[j+k],y = w*A[j+k+(i>>1)]%mod;
				A[j+k] = (x+y)%mod,A[j+k+(i>>1)] = (x-y)%mod;
				w = w*wn%mod;
			}
		}
	}
	if(fl==-1)
	{
		ll Inv = ksm(lim,mod-2);
		for(int i = 0;i<lim;i++)A[i] = A[i]*Inv%mod;
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i = 1;i<=n;i++)scanf("%d",&a[i]);
	inv[0] = inv[1] = 1;
	for(int i = 2;i<=n;i++)inv[i] = (mod-mod/i)*inv[mod%i]%mod;
	for(int i = 2;i<=n;i++)inv[i] = inv[i]*inv[i-1]%mod;
	B[0] = mi[0] = 1;
	for(int i = 1;i<=n;i++)mi[i] = mi[i-1]*(i+k-1)%mod;
	for(int i = 1;i<=n;i++)
	{
		A[i] = a[i]*mi[i-1]%mod*inv[i-1]%mod;
		B[i] = mi[i]*inv[i]%mod;
	}
	int d = 0,lim = 1;
	while(lim<=n<<1)lim<<=1,d++;
	for(int i = 0;i<lim;i++)r[i] = (r[i>>1]>>1)|((i&1)<<d-1);
	NTT(A,lim,1),NTT(B,lim,1);
	for(int i = 0;i<lim;i++)B[i] = A[i]*B[i]%mod;
	NTT(B,lim,-1);
	for(int i = 1;i<=n;i++)printf("%lld ",(B[i]+mod)%mod);
	return 0;
}
```


---

## 作者：peterwuyihong (赞：4)

题意：给一个序列 $a$，定义它的 $1$ 阶子段和为它的所有元素之和，$2$ 阶子段和为所有子段（不是子序列）的 $1$ 阶子段和之和，$3$ 阶子段和为所有子段的 $2$ 阶子段和之和，$\ldots$。

求这个序列的 $k$ 阶子段和。$n\le 10^5,k\le998244353,\bmod=998244353$

题意奥妙重重，模数奥妙重重，我们考虑每个数的贡献。

第 $i$ 个位置的数被计算了几次呢？考虑到第一层循环产生了一个区间 $[l_1,r_1]$，必须把 $i$ 包进来，第 $2$ 层区间是 $[l_2,r_2]$，包含在 $[l_1,r_1]$ 里面，巴拉巴拉，然后 $i$ 包含在 $[l_k,r_k]$ 里面。

于是就计算对于每一个 $i$，计算左边存在几个 $l_1\le l_2\le\ldots l_k\le i$，右边有几个 $i\le r_k\le r_{k-1}\le\ldots r_1$，乘起来即可。

然后问题就转化为了一个满足 $1\le l_1\le\ldots\le l_k\le n$ 的  $(l_1,l_2,\ldots,l_k)$有多少个。

你对 $l$ 做差分，记 $g_i=l_i-l_{i-1},(l_0=0)$，然后就转化为 $\sum_{g=1}^k\le n$，其中 $g_1\ge1,g_{2\ldots k}\ge0$，两边加 $k-1$，变成 $\sum_{g=1}^k\le n+k-1$，其中 $g_i\ge1$，然后插板法做出来一共有 $\dbinom{n+k-2}{k-1}$。

所以 $i$ 位置的贡献是 $\dbinom{i+k-2}{k-1}\dbinom{n-i+k-1}{k-1}$。

答案就是：

$$\sum_{i=1}^n\dbinom{i+k-2}{k-1}\dbinom{n-i+k-1}{k-1}a_i$$

$$\sum_{i=1}^n(\dbinom{i-1+k-1}{k-1}a_i)\dbinom{n-i+k-1}{k-1}$$

然后你一卷！就做完啦！

现在是 $18:42$，我看我什么时候写完。

现在是 $19:18$，我写完了。

```cpp
int n,k;
poly f,g;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>k;
	init(n);
	f.resize(n);
	g.resize(n);
	g[0]=1;
	for(int i=0;i<n;i++){
		if(i>0)
		g[i]=Mul(g[i-1],Mul(i+k-1,inv[i]));
		cin>>f[i];
		mul(f[i],g[i]);
	}
	f=f*g;
	f.resize(n);
	Print(f);
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
上面是我的多项式板子，[安利一波](https://www.luogu.com.cn/blog/Peterprpr/mu-ban)。

被这个带 $k$ 的组合数埋伏到了，根本预处理不了，草。

---

## 作者：tzc_wk (赞：4)

[我的博客园](https://www.cnblogs.com/ET2006/)

一道挺有意思的题，并且竟然自己搞出来了！

首先要清楚 $sum_{k,l,r}$ 的含义是什么。

$sum_{1,l,r}$ 就不用多说了，就是 $a_l$ 到 $a_r$ 的和。

$sum_{2,l,r}$ 根据 $sum_{k,l,r}$ 的公式，可以看作是选择一个区间 $[l_1,r_1]\subseteq [l,r]$，再将 $a_{l_1}$ 到 $a_{r_1}$ 的和累加入答案中。

$sum_{3,l,r}$ 是选择一个区间 $[l_1,r_1]\subseteq[l,r]$，再对 $[l_1,r_1]$ 求一遍 $sum_{2,l_1,r_1}$，也就是再选择一个区间 $[l_2,r_2]\in [l_1,r_1]$ 将 $a_{l_2}$ 到 $a_{r_2}$ 的和加入答案中。

…………

$sum_{k,l,r}$ 就是选择 $k-1$ 个区间 $[l_{k-1},r_{k-1}]\subseteq [l_{k-2},r_{k-2}]\subseteq\dots\subseteq[l_1,r_1]\subseteq [l,r]$，并将 $[l_k,r_k]$ 的和加入答案中。

考虑转换贡献体，枚举 $a_i$ 会对 $sum_{k,1,r}$ 产生多大的贡献，也就是有多少组区间 $[l_i,r_i]$ 满足 $i\in[l_{k-1},r_{k-1}]\subseteq [l_{k-2},r_{k-2}]\subseteq\dots\subseteq[l_1,r_1]\subseteq [1,r]$，由于是相邻区间之间是包含关系，故 $i\geq l_{k-1}\geq l_{k-2}\geq\dots\geq l_1\geq 1$，记 $d_k=i-l_{k-1},d_{k-1}=l_{k-1}-l_{k-2},\dots,d_2=l_2-l_1,d_1=l_1-1$，那么有 $d_1+d_2+d_3+\dots+d_k=i-1$，其中 $d_i\geq 0$，采用隔板法可求得所有 $(l_1,l_2,\dots,l_{k-1})$ 的个数为 $\dbinom{i+k-2}{k-1}$。同理可得所有 $(r_1,r_2,\dots,r_{k-1})$ 的个数为 $\dbinom{r-i+k-1}{k-1}$。

故 $a_i$ 对 $r$ 产生的贡献为 $a_i\times \dbinom{i+k-2}{k-1}\times \dbinom{r-i+k-1}{k-1}$。记 $A_i=a_i\times \dbinom{i+k-2}{k-1},B_i=\dbinom{i+k-2}{k-1}$，求一遍 $A$ 与 $B$ 的卷积 $C$，那么 $C_{r+1}=sum_{k,1,r}$。 

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int pr=3;
const int MOD=998244353;
const int MAXN=1e5;
const int MAXP=1<<18;
int n,k,x[MAXN+5],t[MAXN+5];
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;return ret;}
int a[MAXP+5],b[MAXP+5],c[MAXP+5],LEN=1,LOG=0,inv[MAXP+5],rev[MAXP+5],prs[MAXP+5][2],ipr;
void NTT(int *a,int len,int type){
	int lg=log2(len);
	for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	for(int i=0;i<len;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=2;i<=len;i<<=1){
		int W=prs[i][type<0];
		for(int j=0;j<len;j+=i){
			int w=1;
			for(int k=0;k<(i>>1);k++,w=1ll*w*W%MOD){
				int X=a[j+k],Y=1ll*a[(i>>1)+j+k]*w%MOD;
				a[j+k]=(X+Y)%MOD;a[(i>>1)+j+k]=(X-Y+MOD)%MOD;
			}
		}
	}
	if(type==-1) for(int i=0;i<len;i++) a[i]=1ll*a[i]*inv[len]%MOD;
}
int main(){
	scanf("%d%d",&n,&k);ipr=qpow(pr,MOD-2);
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);ll mul=1;
	for(int i=1;i<=n;i++) t[i]=mul,mul=1ll*mul*qpow(i,MOD-2)%MOD,mul=1ll*mul*(i+k-1)%MOD;
	for(int i=1;i<=n;i++) a[i]=1ll*t[i]*x[i]%MOD,b[i]=t[i];
	while(LEN<=n+n) LEN<<=1,LOG++;
	for(int i=1;i<=LEN;i<<=1){
		inv[i]=qpow(i,MOD-2);
		prs[i][0]=qpow(pr,(MOD-1)/i);
		prs[i][1]=qpow(ipr,(MOD-1)/i);
	} NTT(a,LEN,1);NTT(b,LEN,1);
	for(int i=0;i<LEN;i++) c[i]=1ll*a[i]*b[i]%MOD;
	NTT(c,LEN,-1);for(int i=1;i<=n;i++) printf("%d ",c[i+1]);
	return 0;
}
```

---

## 作者：cyn2006 (赞：3)

我们考虑计算贡献。

考虑最终的对于一个数 $a_i$，设它在 $k$ 个选定多区间嵌套内的出现次数为 $c_i$，则它对答案的贡献为 $a_ic_i$。

那么现在我们考虑一个区间最终区间 $[1,r]$，它的其中答案来源 $a_i$，来源于若干 $k$ 个区间 $[l_i,r_i]$ 满足 $l_k=1\leqslant l_{k-1}\leqslant l_{k-2}\leqslant \ldots\leqslant l_1\leqslant i\leqslant r_1\leqslant \ldots\leqslant r_{k-1}\leqslant r_k$。

那么现在考虑我们从每一个 $i=1\ldots r$ 开始走，不断向左边或者右边走一步或者不走，这样容易发现左端点 $l$ 和右端点 $r$ 的贡献是互相独立的，因此我们分开考虑。

我们先考虑左端点。

其实就是插板法，左边一共可以走 $k-1$ 次，答案为 $\binom{(i+(k-1))-1}{k-1}=\binom{i+k-2}{k-1}$。

然后右边同理，答案为 $\binom{((r-i+1)+(k-1))-1}{k-1}=\binom{r-i+k-1}{k-1}$。

答案即为
$$
sum_{k,1,r}=\sum_{i=1}^r a_r \binom{i+k-2}{k-1} \binom{r-i+k-1}{k-1}
$$
我们考虑优化。

显然我们需要 NTT 来优化。

令 $p(x)=\binom{x}{k-1}$。

则
$$
sum_{k,1,r}=\sum_{i=1}^r a_i p(i+k-2) p(r-i+k-1)
$$
令 $f(i)=a_ip(i+k-2),g(i)=p(i+k-1)$，则
$$
sum_{k,1,r}=\sum_{i=1}^r f(i) g(r-i)
$$
卷一下即可。

对于组合数部分的递推：
$$
\binom{i+k-2}{k-1}=\dfrac{(i+k-2)!}{(k-1)!(i+k-2-k+1)!}
$$

$$
=\dfrac{(i+k-2)!}{(k-1)!(i-1)!}
$$

$$
=\dfrac{k\times (k+1)\times \ldots\times (i+k-2)}{(i-1)!}
$$
于是这部分递推即可。
$$
\binom{i+k-1}{k-1}=\dfrac{k\times (k+1)\times \ldots \times (i+k-1)}{i!}
$$
于是预处理到 $n$ 的阶乘和从 $k$ 开始的乘积即可（或者直接递推也可以）。

时间复杂度：$O(n\log n)$。

$Code:$

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x,i##end=y;i<=i##end;++i)
#define _rep(i,x,y) for(int i=x,i##end=y;i>=i##end;--i)
#define ll long long
#define N 5000005
const int mod=998244353,G=3,_inv=mod+1>>1;
inline void reduce(int&x){x-=mod,x+=x>>31&mod;}
//inline int upd(int x){x-=mod; return x+=x>>31&mod;}
inline int upd(int x){return x+=x>>31&mod;}
int wn[N],rev[N];
inline int qpow(int x,int y,int ret=1){
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1)
		ret=1ll*ret*x%mod; return ret;
}
namespace ntt{
	inline void install(int n){
		for(int mid=1;mid<n;mid<<=1){
			int w=qpow(G,mod/mid>>1);
			wn[mid]=1;
			rep(i,1,mid-1) wn[mid+i]=1ll*wn[mid+i-1]*w%mod;
		}
	}
	int lim,invlim;
	inline void init(int n){
		for(lim=invlim=1;lim<n;lim<<=1)
			invlim=1ll*invlim*_inv%mod;
		rep(i,1,lim-1) rev[i]=rev[i>>1]>>1|(lim>>1&-(i&1));
	}
	inline void ntt(int *a,int ty){
		static int b[N];
		rep(i,0,lim-1) b[i]=a[rev[i]];
		for(int mid=1;mid<lim;mid<<=1){
			for(int i=0;i<lim;i+=mid<<1){
				rep(j,0,mid-1){
					const int x=1ll*b[i+j+mid]*wn[mid+j]%mod;
					b[i+j+mid]=upd(b[i+j]-x);
					reduce(b[i+j]+=x);
				}
			}
		}
		if(!ty){
			rep(i,0,lim-1) a[i]=1ll*b[i]*invlim%mod;
			std::reverse(a+1,a+lim);
		} else {
			std::memcpy(a,b,lim<<2);
		}
	}
	inline void _ntt(int *a,int *b){
		ntt(a,1),ntt(b,1);
		rep(i,0,lim-1) a[i]=1ll*a[i]*b[i]%mod;
		ntt(a,0);
	}
}
int a[N],n,k,inv[N];
int f[N],g[N];
int main(){
	std::ios::sync_with_stdio(0),std::cin.tie(0),std::cout.tie(0);
	std::cin>>n>>k;
	rep(i,1,n) std::cin>>a[i];
	inv[1]=1;
	rep(i,2,n) inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
	g[0]=1;
	rep(i,1,n) g[i]=1ll*g[i-1]*(i+k-1)%mod*inv[i]%mod;
	rep(i,1,n) f[i]=1ll*g[i-1]*a[i]%mod;
	ntt::install(n+1<<2); ntt::init(n+1<<1);
	ntt::_ntt(f,g);
	rep(i,1,n) std::cout<<f[i]<<" \n"[i==n];
	return 0;
}
```



---

## 作者：JustinRochester (赞：2)

[传送门](https://www.luogu.com.cn/problem/P5641)

---

**【分析】**
--

$sum_{k,l,r}=\begin{cases}
\displaystyle\sum_{i=l}^r a_i,k=1
\\
\displaystyle\sum_{i=l}^r\sum_{j=i}^rsum_{k-1,i,j},k>1
\end{cases}$

考虑第二串式子的含义，其能写为：

$\displaystyle sum_{k,l,r}=\sum_{l\leq i\leq j\leq r}sum_{k-1,i,j}$

考虑继续进行迭代：

$\displaystyle =\sum_{l\leq i_1\leq i_2\leq j_2\leq j_1\leq r}sum_{k-2,i_2,j_2}$

$\displaystyle =\sum_{l\leq i_1\leq \cdots \leq i_{k-1}\leq j_{k-1}\leq \cdots\leq j_1\leq r}sum_{1,i_{k-1},j_{k-1}}$

现考虑 $a_n$ 对 $sum_{k,l,r}$ 的贡献：

显然，当 $k=1$ 时，贡献为 $[l\leq n\leq r]$

同上考虑迭代，统计出 $a_n$ 的贡献为：

$\displaystyle =\sum_{l\leq i_1\leq \cdots \leq i_{k-1}\leq j_{k-1}\leq \cdots\leq j_1\leq r}[i_{k-1}\leq n\leq j_{k-1}]$

即贡献为：$l\leq i_1\leq \cdots\leq i_{k-1}\leq n\leq j_{k-1}\leq \cdots\leq j_1\leq r$ 的方案数

$l\leq i_1\leq \cdots\leq i_{k-1}\leq n$ 的方案数，即为 $(k-1)$ 个数插入到 $[l,n]$ 盒子中的方案数，为 $\dbinom{n-l+k-1}{n-l}$

$n\leq j_{k-1}\leq \cdots\leq j_1\leq r$ 的方案数，同理为 $(k-1)$ 个数插入到 $[n,r]$ 盒子中的方案数，为 $\dbinom{r-n+k-1}{r-n}$

因此，$a_n$ 对 $sum_{k,1,i}$ 的总贡献为 $a_n\cdot \dbinom{n-1+k-1}{n-1}\cdot \dbinom{i-n+k-1}{i-n}$

故 $\displaystyle sum_{k,1}[i]=\sum_{x=1}^na_x\cdot \dbinom{x-1+k-1}{x-1}\cdot \dbinom{i-x+k-1}{i-x}$

定义 $a[0]=0$ ，根据 $\dbinom n m=0(m<0)$ 得

$\displaystyle sum_{k,1}[i]=\sum_{x+y=i}a_x\cdot \dbinom{x-1+k-1}{x-1}\cdot \dbinom{y+k-1}{y}$

记 $\displaystyle A(x)=\sum_{n=0}^\infty a_n\cdot \dbinom{n-1+k-1}{n-1}x^n,F(x)=\sum_{n=0}^\infty \dbinom{n+k-1}{n}$

得 $Sum_{k,1}(x)=A(x)\cdot F(x)$

直接多项式乘法即可（可能要稍微卡一下常数）

---

**【代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=1<<17<<1,MOD=998244353;
int a[M], b[M];

inline int add(int a,int b) { return (a+b>=MOD)?(a+b-MOD):(a+b); }
inline int dis(int a,int b) { return (a-b<0)?(a-b+MOD):(a-b); }
struct NTT{
    static const int G = 3, P = 998244353;
    int N, na, nb, w[2][M], rev[M];
    inline ll kpow(ll a,int b){
        ll c=1;
        for(;b;b>>=1,a=a*a%P) if(b&1) c=c*a%P;
        return c;
    }

    void FFT(int *a,int f){
        for(int i=0;i<N;++i) if(i<rev[i]) swap(a[i],a[rev[i]]);
        for(int i=1;i<N;i<<=1)
            for(int j=0,t=N/(i<<1);j<N;j+=i<<1)
                for(int k=0,l=0,x,y;k<i;++k,l+=t)
                    x=(ll)w[f][l]*a[j+k+i]%P, y=a[j+k], a[j+k]=add(y,x), a[j+k+i]=dis(y,x);
        if(f) for(int i=0,x=kpow(N,P-2);i<N;++i) a[i]=(ll)a[i]*x%P;
    }
    void work(){
        int d=__builtin_ctz(N);
        w[0][0]=w[1][0]=1;
        for(int i=1,x=kpow(G,(P-1)/N),y=kpow(x,P-2);i<N;++i){
            rev[i]=(rev[i>>1]>>1)|((i&1)<<d-1);
            w[0][i]=(ll)x*w[0][i-1]%P, w[1][i]=(ll)y*w[1][i-1]%P;
        }
    }
    void doit(int *a,int *b,int na,int nb){
        for(N=1;N<na+nb-1;N<<=1);
        for(int i=na;i<N;++i) a[i]=0;
        for(int i=nb;i<N;++i) b[i]=0;
        work(); FFT(a,0); FFT(b,0);
        for(int i=0;i<N;++i) a[i]=(ll)a[i]*b[i]%P;
        FFT(a,1);
    }
}ntt;

int n,k,A[M],F[M],InV[M];
inline void pre(){
    InV[1]=1;
    for(int i=2;i<=2e5;++i)
        InV[i]=dis(MOD,(ll)(MOD/i)*InV[MOD%i]%MOD);

    F[0]=1;
    for(int i=1;i<=1e5;++i)
        F[i]=(ll)F[i-1]*(i+k-1)%MOD*InV[i]%MOD;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>k;
    pre();
    for(int i=1,t=1;i<=n;++i,t=(ll)t*(i+k-2)%MOD*InV[i-1]%MOD){
        cin>>A[i];
        A[i]=(ll)A[i]*t%MOD;
    }
    ntt.doit(F,A,n+1,n+1);
    for(int i=1;i<=n;++i) cout<<F[i]<<" ";
    cout.flush();
    return 0;
}
```

---

## 作者：Durancer (赞：1)

# 题解：P5641开拓者的卓识

标签： 多项式 组合数学

---

### 前言

通过找出每一个位置在每一个输出值中的贡献总量的公式，来求得所有答案。

### 思路

从最简单的开始推起。

当前要求的是 $sum_{k,1,r}$，要求出每一个 $a_i,(i\in [1,r])$ 的出现数量。

假设 $cnt_i$ 为 $a_i$ 在 $sum_{k,1,r}$ 中出现的次数，那么：

$$sum_{k,1,r}=\sum_{i=1}^r\ cnt_i\times a_i$$

现在最重要的问题是如何求 $cnt_i$ ，定义一下 $cnt_i$ 的意义，即为位置 $i$ 被 $k-1$ 个区间 $[l_j,r_j],(j\in[1,k-1])$ 都覆盖的方案数，并且因为是从高阶向低阶展开，所以序号小的区间，一定被包含在序号大的区间，$[l_j,r_j]\in[l_{j+1},r_{j+1}]$。

继续形象化一点就是要在 $1…i$ 中选 $k-1$ 个点的方案数乘上 $i+1…r$ 中选出 $k-1$ 个点的方案数（根据上面所说的范围，这些点有些可以重复。

那么如何把它的计算用组合数的公式建立起来起最重要的问题。

提出一个问题，问从 $n$ 种类型的每一种都有无数个的点中选取 $m$ 个(可以类型重复)的方案数。

这个问题因为有重复，那么就和隔板法有联系了，把 $m$ 形象地化为 $m$ 个小球，那么就是要把这 $m$ 个小球用 $n-1$ 个挡板隔开 其中第 $i$ 个挡板和第 $i+1$ 个挡板之间的球数就是第 $i+1$ 个数选的个数。

那么方案就是 $\dbinom{n+m-1}{m}$。

也就是 $n+m-1$ 个位置，找 $m$ 个位置放球。

所以： 

$$sum_{k,1,r}=\sum_{i=1}^{r} a_i \binom{i+k-1-1}{k-1}\binom{r-i+k-1-1}{k-1}$$

$$sum_{k,1,r}=\sum_{i=1}^{r} a_i \binom{i+k-2}{k-1}\binom{r-i+k-1}{k-1}$$

考虑用多项式来优化它，其实这个式子一看有一个 $r-i$ 其实就特别特别符合卷积了

设 $F_{i}=a_i\times \dbinom{i+k-2}{k-1}$,$G_i=\binom{i+k-1}{k-1}$

$$sum_{k,l,r}=\sum_{i=1}^r F_i\times G_{r-i}$$

~~非常美丽的卷积形式，卷卷卷。~~

### 实现细节

肯定是选择递推求解了。

 $k$ 的范围很大是一个头疼的问题，可以先递推出 $G_i$ 来，然后看一看 $F_i $与 $G$ 的关系,用 $F_i=a_i\times G_{i-1}$ 求解即可。
 
扔一个推 $G(i)$ 的式子：

$$G(0)=1$$

$$G(1)=\binom{k}{k-1}=\frac{k!}{(k-1)!\times1}=k$$

$$G(2)=\binom{k+1}{k-1}\frac{(k+1)!}{(k-1)!\times 2!}=\frac{k\times (k+1)}{2}$$

$$G(3)=\binom{k+2}{k-1}=\frac{k\times (k+1)\times (k+2)}{2\times 3}$$

可以发现

$$G(i)=\frac{G(i-1)\times (k+i-1)}{i}$$

### 代码实现

```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<queue>
#include<stack>
#include<map>
#define int long long 
using namespace std;
const int N=3e6+9;
const int mod=998244353;
const int G[]={3,332748118};
int n,k;
int r[N];
int term=1,l;
int inv[N];
int g[N];
int f[N];
int a[N];
int read()
{
	int f=1,x=0;
	char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s^'0');s=getchar();}
	return f*x;
}
int quick(int x,int p)
{
	int ret=1;
	while(p)
	{
		if(p&1) ret=x*ret%mod;
		x=x*x%mod;
		p>>=1; 
	}
	return ret%mod;
}
void NTT(int *A,int type)
{
	for(int i=0;i<term;i++)
		if(i<r[i])
			swap(A[i],A[r[i]]);
	for(int mid=1;mid<term;mid<<=1)
	{
		int R=mid<<1;
		int Wn=quick(G[type],(mod-1)/R);
		for(int j=0;j<term;j+=R)
		{
			int w=1;
			for(int k=0;k<mid;k++,w=w*Wn%mod)
			{
				int x=A[j+k]%mod;
				int y=(w*A[j+k+mid])%mod;
				A[j+k]=(x+y)%mod;
				A[j+k+mid]=(x-y+mod)%mod; 
			}
		}
	}
	if(type==1)
	{
		int inv=quick(term,mod-2);
		for(int i=0;i<term;i++)
		{
			A[i]=A[i]*inv%mod;
		}
	}
}
void prepare()
{
	inv[1]=1;
	g[0]=1;
	g[1]=k%mod;
	for(int i=2;i<=n;i++)
	{
		inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		//printf("%lld\n",i);
	}
	for(int i=1;i<=n;i++)
		g[i]=g[i-1]*inv[i]%mod*(k+i-1)%mod;
	for(int i=1;i<=n;i++)
		f[i]=a[i]*g[i-1]%mod;
	return; 
}
signed main()
{
	n=read();
	k=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	prepare();
	while(term<=n+n)
	{
		term<<=1;
		l++;
	}
	for(int i=0;i<term;i++)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	NTT(f,0);
	NTT(g,0);
	for(int i=0;i<term;i++)
		f[i]=f[i]*g[i];
	NTT(f,1);
	for(int i=1;i<=n;i++)
		printf("%lld ",f[i]%mod);
	return 0;
}
```

---

## 作者：duyi (赞：1)

# P5641 【CSGRound2】开拓者的卓识

考虑一个数 $a_i$，对一段区间 $l,r$ 的贡献。

- $k = 1$ 时，只要 $l\leq i\leq r$ 就能贡献 $1$，否则是 $0$。
- $k = 2$ 时，相当于在 $[l,r]$ 里选一个子区间 $l',r'$，使得 $l\leq l'\leq i\leq r'\leq r$。
- $k = 3$ 时，相当于要在 $[l,r]$ 里选两层。也就是 $l\leq l'\leq l''\leq i\leq r''\leq r'\leq r$。
- ......

考虑枚举 $r$。求 $r$ 的答案。

对于每个 $i\leq r$，它对答案的贡献系数是，在 $[1, i]$ 选 $k - 1$ 个端点，和在 $[i, r]$ 选 $k - 1$ 个端点的方案数之积。端点可以重复。

设在一段长度为 $x$ 的区间里，选 $k - 1$ 个可以重复的点的方案数为 $f(x)$。考虑求 $f(x)$。可以枚举这些点实际占用了多少位置，再用插板法。不难写出：$f(x) = \sum_{i = 1}^{x} {x\choose i}{k - 1\choose i - 1}$。

$r$ 的答案，可以用 $f$ 表示为：$\text{ans}(r) = \sum_{i = 1}^{r}a_i\times f(i)\times f(r - i + 1)$。

把 $f$ 里的组合数 ${x\choose i}$ 拆成 $\frac{x!}{i!(x - i)!}$。容易发现，$f(x)$ 和 $\text{ans}(r)$ 都是卷积的形式。可以用 NTT 计算。

需要注意的是，因为 $k$ 很大，$f(x)$ 式子里的 ${k - 1\choose i - 1}$ 如果拆成阶乘，则处理起来较为麻烦（需要打表，或使用快速阶乘算法），不拆开则可以直接递推求出，要简单的多。

时间复杂度 $\mathcal{O}(n\log n)$。

参考代码：

```cpp
// problem: P5641
#include <bits/stdc++.h>
using namespace std;

#define mk make_pair
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 1e5;
const int MOD = 998244353;

inline int mod1(int x) { return x < MOD ? x : x - MOD; }
inline int mod2(int x) { return x < 0 ? x + MOD : x; }
inline void add(int &x, int y) { x = mod1(x + y); }
inline void sub(int &x, int y) { x = mod2(x - y); }
inline int pow_mod(int x, int i) {
	int y = 1;
	while (i) {
		if (i & 1) y = (ll)y * x % MOD;
		x = (ll)x * x % MOD;
		i >>= 1;
	}
	return y;
}

int fac[MAXN + 5], ifac[MAXN + 5];
inline int comb(int n, int k) {
	if (n < k) return 0;
	return (ll)fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
}
void facinit(int lim = MAXN) {
	fac[0] = 1;
	for (int i = 1; i <= lim; ++i) fac[i] = (ll)fac[i - 1] * i % MOD;
	ifac[lim] = pow_mod(fac[lim], MOD - 2);
	for (int i = lim - 1; i >= 0; --i) ifac[i] = (ll)ifac[i + 1] * (i + 1) % MOD;
}

namespace NTT {

int rev[MAXN * 4 + 5];
int a[MAXN * 4 + 5], b[MAXN * 4 + 5];
void NTT(int a[], int n, int flag) {
	for (int i = 0; i < n; ++i) {
		if (i < rev[i]) {
			swap(a[i], a[rev[i]]);
		}
	}
	for (int i = 1; i < n; i <<= 1) {
		int T = pow_mod(3, (MOD - 1) / (i << 1));
		if (flag == -1) T = pow_mod(T, MOD - 2);
		for (int j = 0; j < n; j += (i << 1)) {
			for (int k = 0, t = 1; k < i; ++k, t = (ll)t * T % MOD) {
				int Nx = a[j + k], Ny = (ll)a[i + j + k] * t % MOD;
				a[j + k] = (Nx + Ny) % MOD;
				a[i + j + k] = (Nx - Ny + MOD) % MOD;
			}
		}
	}
	if (flag == -1) {
		int inv_n = pow_mod(n, MOD - 2);
		for (int i = 0; i < n; ++i) {
			a[i] = (ll)a[i] * inv_n % MOD;
		}
	}
}
void work(int _a[], int _b[], int _res[], int n, int m, int reslen) {
	int lim = 1, ct = 0;
	while (lim <= n + m) {
		lim <<= 1, ct++;
	}
	for (int i = 1; i < lim; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (ct - 1));
	}
	for (int i = 0; i < n; ++i) a[i] = _a[i];
	for (int i = n; i < lim; ++i) a[i] = 0;
	for (int i = 0; i < m; ++i) b[i] = _b[i];
	for (int i = m; i < lim; ++i) b[i] = 0;
	NTT(a, lim, 1);
	NTT(b, lim, 1);
	for (int i = 0; i < lim; ++i) a[i] = (ll)a[i] * b[i] % MOD;
	NTT(a, lim, -1);
	for (int i = 0; i < reslen; ++i) _res[i] = a[i];
}
} // namespace NTT


int n, K, a[MAXN + 5];
int f[MAXN + 5], g[MAXN + 5];

int main() {
	facinit();
	cin >> n >> K;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		a[i] = mod1(a[i]);
	}
	if (K == 1) {
		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			add(sum, a[i]);
			cout << sum << " \n"[i == n];
		}
		return 0;
	}
	
	/*
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i && j <= K - 1; ++j) {
			add(f[i], (ll)comb(i, j) * comb(K - 2, j - 1) % MOD);
		}
	}
	*/
	
	f[1] = 1;
	for (int i = 2; i <= n && i <= K - 1; ++i) {
		f[i] = (ll)f[i - 1] * (K - i) % MOD * ifac[i - 1] % MOD * fac[i - 2] % MOD;
		//f[i] = comb(K - 2, i - 1);
	}
	for (int i = 1; i <= n && i <= K - 1; ++i) {
		f[i] = (ll)f[i] * ifac[i] % MOD;
	}
	for (int i = 0; i <= n; ++i) {
		g[i] = ifac[i];
	}
	NTT :: work(f, g, f, n + 1, n + 1, n + 1);
	for (int i = 1; i <= n; ++i) {
		f[i] = (ll)f[i] * fac[i] % MOD;
	}
	/*
	for (int i = 1; i <= n; ++i) {
		int ans = 0;
		for (int j = 1; j <= i; ++j) {
			add(ans, (ll)a[j] * f[j] % MOD * f[i - j + 1] % MOD);
		}
		cout << ans << " \n"[i == n];
	}
	*/
	for (int i = 0; i < n; ++i) g[i] = f[i + 1];
	for (int i = 1; i <= n; ++i) f[i] = (ll)f[i] * a[i] % MOD;
	NTT :: work(f, g, f, n + 1, n, n + 1);
	for (int i = 1; i <= n; ++i)
		cout << f[i] << " \n"[i == n];
	return 0;
}
```





---

## 作者：yijan (赞：1)

# LG 11 月 月赛 II T4

看到膜数和 $ 10^5 $ 以及 $ n^2 $ 的部分分想到很可能是 NTT 于是开始推式子

首先看到式子可以化作，

- 如果 $k = 0$ , $ f(l , r , k) $ 为 $ [l = r]a[l] $
- 否则，$ f(l , r , k) $ 为 $ \displaystyle \sum_{\forall [a,b] \subset [l,r]} f(a,b,k-1) $ 比较通俗的语言就是对于 $ [l,r] $ 的所有子区间求 $ f(a,b,k-1) $ 的和。

于是可以考虑对于每一个 $ a[i] $ 的贡献，其实就是左端点到 $ i $ 以及右端点到 $ i $ 分别选择 $ k $ 个位置，这个就是经典的隔板法了。最后的式子：

$ sum_{1, r, k}=\sum_{i=1}^{r} a_{i}\left(\begin{array}{c}{i+k-2} \\ {k-1}\end{array}\right)\left(\begin{array}{c}{r-i+k-1} \\ {k-1}\end{array}\right) $

然而出题人把 $ k $ 放到了 $ 998244353 $ 级别，于是只有分块打个表过去了，不知道有没有什么更优秀的处理方法了（

(代码中省略了表。。毕竟太长了)

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
//#define int long long
#define MAXN 1000006
#define P 998244353
typedef long long ll;
int n , k;
int power( int a , int x ) {
    int ans = 1 , cur = a % P;
    while( x ) {
        if( x & 1 ) ans = 1ll * ans * cur % P;
        cur = 1ll * cur * cur % P , x >>= 1;
    }
    return ans;
}
int A[MAXN] , B[MAXN] , r[MAXN];
inline void NTT(int* a, int len, int type) {
    for (int i = 0; i < len; i++) if (i < r[i]) swap(a[i], a[r[i]]);
    for (int mid = 2; mid <= len; mid <<= 1) {
        int Wn = power(3, type ? (P - 1) / mid : P - 1 - (P - 1) / mid);
        for (int i = 0; i < len; i += mid)
            for (int j = i, w = 1, t; j < i + (mid >> 1); j++, w = (ll)w * Wn % P)
                t = (ll)w * a[j + (mid >> 1)] % P, a[j + (mid >> 1)] = (a[j] - t + P) % P, a[j] = (a[j] + t) % P;
    }
    if (!type) for (int inv = power(len, P - 2), i = 0; i < len; i++) a[i] = (ll)a[i] * inv % P;
}
int J[MAXN];
const int jj[] = {/* ... */};
int jk = 0;
int getJ( int x ) {
    int cur = k , res = jk;
    while( cur + 1 <= x ) ++ cur , res = 1ll * res * cur % P;
    while( cur - 1 >= x ) res = 1ll * res * power( cur , P - 2 ) % P , -- cur;
    return res;
}
signed main() {
//    freopen("input","r",stdin);

    cin >> n >> k;
    if( k == 1 ) {
        for( int i = 1 ; i <= n ; ++ i ) scanf("%d",&A[i]) , A[i] = ( A[i] + A[i - 1] ) % P , printf("%d ",A[i]);
        return 0;
    }
    J[0] = 1; for( int i = 1 ; i < MAXN ; ++ i ) J[i] = 1ll * J[i - 1] * i % P;
    jk = jj[k / 1000000];
    for( int r = k / 1000000 * 1000000 + 1 ; r <= k ; ++ r )
        jk = 1ll * jk * r % P;
    int re = getJ( k - 2 ) , re1 = getJ( k - 1 );
//    cout << getJ( 10000000 ) << endl;
    int tm = re1;
    B[0] = re1;
    for( int i = 1 ; i <= n ; ++ i )
        scanf("%d",&A[i]) , re = 1ll * re * ( i + k - 2 ) % P , re1 = 1ll * re1 * ( i + k - 1 ) % P ,
                A[i] = 1ll * A[i] * re % P * power( J[i - 1] , P - 2 ) % P ,
                B[i] = 1ll * re1 * power( J[i] , P - 2 ) % P;
    int len = 1, l = 0;
    while (len <= n * 2) len <<= 1, l++;
    for (int i = 0; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
    NTT( A , len , 1 ) , NTT( B , len , 1 );
    for( int i = 0 ; i < len ; ++ i ) A[i] = 1ll * A[i] * B[i] % P;
    NTT( A , len , 0 );
    int x = power( 1ll * tm * tm % P , P - 2 );
    for( int i = 1 ; i <= n ; ++ i ) printf("%d ", (int) (1ll * x * A[i] % P) );
}


```


---

## 作者：zzw4257 (赞：0)

> 定义
> $$
> s_{l,r,k}=\begin{cases}\sum\limits_{i=l}^ra_i&k=1\\\sum\limits_{i=l}^r\sum\limits_{j=l}^rs_{i,j,k-1}&\mathtt{otherwise.}\end{cases}
> $$
> 求$s_{1,i,k}(i\in[1,n])$

考虑贡献法

对$a_i$,设在$k$重区间嵌套中会被包含$w_i$次,则答案为$\sum\limits_{i=1}^na_iw_i$

求$w_i$,转换问题为找到$k$个区间$\{(l_j,r_j)\}(l_j\leqslant l_{j+1}\&r_j\geqslant r_{j+1},(l_{j+1},r_{j+1})=(i,i))$

发现两个条件是独立的，所以分别考虑左右边界

对左边问题抽象为从$i$向左走$k$次每次可不走共要走$i-1$步的方案数

变成$i-1$个**相同**小球放在$k$个**不同**盒子，要求**可空**的方案数

所以隔板法$\binom{i+k-2}{k-1}$同理右边$\binom{r-i+k-1}{k-1}$

发现$(i+k-2)+(r-i+k-1)$为定值直接以形似组合数为系数用两个函数卷积即可

---

## 作者：Vocalise (赞：0)

考虑一个 $a_i$ 对 $sum_{k,1,r}$ 的贡献。

发现每作一次贡献，就有一个如下过程：选取一个包含 $i$ 的区间，然后选取一个包含上一个选到的区间，一共选 $k$ 个区间，最后一个就是 $[1,r]$。

为什么是 $k$ 次而不是 $k-1$？~~恐怕只有我才会想这种问题~~因为并非第一个一定要选 $[i,i]$，根据 $sum$ 的定义。

容易发现选取区间左端点的方案与右端点的是独立的，于是分开求解最后相乘。考虑左边 $[1,i]$ 中的方案。记左端点为 $l$。

因为 $l$ 始终 $\leq i$，所以把 $l$ 的不断选取看作从 $i$ 向左移动的过程。**任何一次都可以移动 $0$ 步**。最后总是到达 $1$ 的。问题就成了：

需要作出 $i-1$ 个位移，$k$ 次行动，问操作序列数。

这就是隔板的问题了。具体的可以看看其他题目，不细说。

如果有 $n$ 个位移，$m$ 次行动，则方案数为

$$\binom{n+m-1}{m-1}$$

本题即为

$$\binom{i+k-2}{k-1}$$

右端点的方案类似，是

$$\binom{r-i+k-1}{k-1}$$

我们得到

$$sum_{k,1,r}=\sum_{i=1}^ra_i\binom{i+k-2}{k-1}\binom{r-i+k-1}{k-1}$$

这个东西看上去很友好。

设

$$f_i=\binom{i+k-1}{k-1}$$

$$g_i=a_if_{i-1}$$

有

$$sum_{k,l,r}=\sum_{i=1}^rg_if_{r-i}$$

得到卷积，NTT直接算即可。

但是本题中组合数的范围较大，可以由 $\binom{n-1}m$直接推到 $\binom n m$，剩下只要把逆元推到 $n$ 即可。

注意 $f_0,g_0$ 的问题：$f_0$ 根据定义是 $1$,而 $g_0$ 需去除式子中 $i=0$ 项的贡献而设成 $0$。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

typedef long long ll;
const int p = 998244353;
const int MAXN = 400001;

inline ll read() {
    ll x = 0,f = 1; char ch = getchar();
    while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
    do x = (x * 10 + ch - 48) % p, ch = getchar(); while(ch >= '0' && ch <= '9');
    return (x * f % p + p) % p;
}

int n,k,r[MAXN];
ll a[MAXN],f[MAXN],g[MAXN];
ll inv[MAXN];

ll fastpow(ll a,int b) {
    ll res = 1; a %= p;
    while(b) {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void NTT(ll *a,int N) {
    for(int i = 0;i < N;i++) if(i < r[i]) std::swap(a[i],a[r[i]]);
    for(int n = 2,m = 1;n <= N;m = n, n <<= 1) {
        ll g1 = fastpow(3,(p - 1) / n);
        for(int l = 0;l < N;l += n) {
            ll g = 1,t1,t2;
            for(int i = l;i < l + m;i++) {
                t1 = a[i], t2 = g * a[i + m] % p;
                a[i] = (t1 + t2) % p;
                a[i + m] = (t1 - t2 + p) % p;
                g = g * g1 % p;
            }
        }
    }
    return;
}

void INTT(ll *a,int N) {
    NTT(a,N);
    std::reverse(a + 1,a + N);
    int invN = fastpow(N,p - 2);
    for(int i = 0;i < N;i++) a[i] = a[i] * invN % p;
}

int main() {
    n = read(), k = read();
    for(int i = 1;i <= n;i++) a[i] = read();
    int N = 1, l = -1; while(N <= n << 1) N <<= 1, l++;
    for(int i = 1;i < N;i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l);
    inv[1] = 1;
    for(int i = 2;i < n;i++) inv[i] = inv[p % i] * (p - p / i) % p;
    f[0] = 1;
    for(int i = 1;i <= n;i++) f[i] = f[i - 1] * (i + k - 1) % p * inv[i] % p;
    for(int i = 1;i <= n;i++) g[i] = a[i] * f[i - 1] % p;
    NTT(f,N); NTT(g,N);
    for(int i = 0;i < N;i++) f[i] = f[i] * g[i] % p;
    INTT(f,N);
    for(int i = 1;i <= n;i++) std::printf("%lld ",f[i]);
    return 0;
}

```

---

