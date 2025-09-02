# Product

## 题目背景

${\rm CYJian}$：“听说 $\gcd$ 和 $\sum$ 套起来比较好玩？？那我就……”

## 题目描述

${\rm CYJian}$ 最近闲的玩起了 $\gcd$。他想到了一个非常简单而有意思的式子：

$$\prod_{i=1}^N\prod_{j=1}^N\frac{\operatorname{lcm}(i,j)}{\gcd(i,j)}\pmod{104857601}$$

${\rm CYJian}$ 已经算出来这个式子的值了。现在请你帮他验算一下吧。${\rm CYJian}$ 只给你 $0.2\textrm{s}$ 的时间哦。

2024.5.11 **upd**: 放宽时空限制。

## 说明/提示

样例解释：

|$\frac{\operatorname{lcm}}{\gcd}$|1|2|3|4|5|
|:--:|:--:|:--:|:--:|:--:|:--:|
|**1**|1|2|3|4|5|
|**2**|2|1|6|2|10|
|**3**|3|6|1|12|15|
|**4**|4|2|12|1|20|
|**5**|5|10|15|20|1|

对于 $30\%$ 的数据：$1 \leq N \leq 5000$。

对于 $100\%$ 的数据：$1 \leq N \leq 1000000$。

## 样例 #1

### 输入

```
5
```

### 输出

```
585494
```

# 题解

## 作者：Nemlit (赞：33)

## [原文地址](https://www.cnblogs.com/bcoier/p/10392413.html)

~~先吐槽一波：凉心出题人又卡时间又卡空间~~

先来化简一波柿子

$$\prod_{i=1}^{n}\prod_{j=1}^{n}\frac{lcm(i,j)}{gcd(i,j)}$$

$$=\prod_{i=1}^{n}\prod_{j=1}^{n}\frac{i*j}{gcd(i,j)^2}$$

$$=(\prod_{i=1}^{n}\prod_{j=1}^{n}i*j)*(\prod_{i=1}^{n}\prod_{j=1}^{n}gcd(i,j))^{-2}$$

先看前面的那一坨：

$$\prod_{i=1}^{n}\prod_{j=1}^{n}i*j$$

$$=\prod_{i=1}^{n}(i^n*n!)$$（不理解可以把上述式子打开，就可以发现了）

$$=(n!)^{n}*\prod_{i=1}^{n}i^n$$

$$=(n!)^n*(n!)^n$$

$$=(n!)^{2n}$$

然后我们来看后面那一坨（先不看-2次方）：

$$\prod_{i=1}^{n}\prod_{j=1}^{n}gcd(i,j)$$

$$=\prod_{d=1}^{n}\prod_{i=1}^{n}\prod_{j=1}^{n}[gcd(i,j)==d]$$

$$=\prod_{d=1}^{n}d^{\sum_{i=1}^{n}\sum_{j=1}^{n}[gcd(i,j)==d]}$$

$$=\prod_{d=1}^{n}d^{\sum_{i=1}^{\frac{n}{d}}\sum_{j=1}^{\frac{n}{d}}[gcd(i,j)==1]}$$

先只看指数：

$$\sum_{i=1}^{\frac{n}{d}}\sum_{j=1}^{\frac{n}{d}}[gcd(i,j)==1]$$

这不就是[仪仗队](https://tbr-blog.blog.luogu.org/ou-la-han-shuo-zong-jie)吗？

所以我们只要求出啦欧拉函数前缀和，就可以用欧拉函数$O(1)$算出指数了~

所以我们把柿子综合一下：

令$$sum[x]=\sum_{i=1}^x\phi(i)$$

原式化为：$$(n!)^{2n}*(\Pi_{d=1}^{n}d^{2*sum[\frac{n}{d}]-1})^{-2}$$

然后我们就可以$O(nlogn)$求出答案了

最后注意一下，因为欧拉函数前缀和会爆int，所以要用longlong，但是这样就会MLE，所以我们要考虑优化

根据欧拉定理，因为模数为质数，所以$\phi(mod)=mod-1$，所以原式我们可以进一步化为：

$$(n!)^{2n}*(\prod_{d=1}^{n}d^{(2*sum[\frac{n}{d}]-1)\%(mod-1)})^{-2}$$

这样就可以不需要longlong了

下面给出代码：
```
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define re register
#define debug printf("Now is Line : %d\n",__LINE__)
#define file(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define ll long long
#define mod 104857601
il int read()
{
    re int x=0,f=1;re char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
    while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
    return x*f;
}
#define maxn 1000000+5
int n,cnt,ans1=1,prim[80000],ans2=1,pai[maxn];
bool vis[maxn];
il int qpow(int a,ll b)
{
    int r=1;
    while(b)
    {
        if(b&1ll) r=1ll*r*a%mod;
        b>>=1ll;
        a=1ll*a*a%mod;
    }
    return r;
}
int main()
{
    n=read();
    pai[1]=1;
    for(re int i=2;i<=n;++i)
    {
    	ans1=1ll*ans1*i%mod;
        if(!vis[i]) prim[++cnt]=i,pai[i]=i-1;
        for(re int j=1;j<=cnt;++j)
        {
            if(prim[j]*i>n) break;
            vis[prim[j]*i]=1;
            if(i%prim[j]==0) {pai[i*prim[j]]=pai[i]*prim[j];break;}
            pai[i*prim[j]]=pai[prim[j]]*pai[i];
        }
    }
    for(re int i=1;i<=n;++i) pai[i]=pai[i]*2+pai[i-1]%(mod-1);
    ans1=qpow(ans1,2*n);
    for(re int i=2;i<=n;++i) ans2=1ll*ans2*qpow(i,pai[n/i]-1)%mod;
    printf("%d",(1ll*ans1*qpow(1ll*ans2*ans2%mod,mod-2))%mod);
    return 0;
}
```

---

## 作者：AThousandSuns (赞：17)

一次偶然听到大家说反演就是过不了这题？

出题人标程是反演，但是是 $O(n\log n)$ 的？

有 $O(n)$ 的做法，但不是反演？

…………………………

那我来写 $O(n)$ 的反演做法吧。

---
由 $\operatorname{lcm}(i,j)=\frac{ij}{\gcd(i,j)}$ 得：
$$\prod\limits^n_{i=1}\prod\limits^n_{j=1}\frac{ij}{\gcd^2(i,j)}$$
$$\frac{\prod\limits^n_{i=1}\prod\limits^n_{j=1}ij}{\prod\limits^n_{i=1}\prod\limits^n_{j=1}\gcd^2(i,j)}$$
分子就是 $(n!)^2$。分母是下面这个式子的平方：
$$\prod\limits^n_{i=1}\prod\limits^n_{j=1}\gcd(i,j)$$
枚举 $\gcd$，有多少个数对 $(i,j)$ 满足 $\gcd(i,j)=d$，那么答案的贡献就是 $d$ 的多少次方。
$$\prod\limits^n_{d=1}d^{\sum\limits^n_{i=1}\sum\limits^n_{j=1}[\gcd(i,j)=d]}$$
枚举 $id$ 和 $jd$：
$$\prod\limits^n_{d=1}d^{\sum\limits^{\lfloor n/d\rfloor}_{i=1}\sum\limits^{\lfloor n/d\rfloor}_{j=1}[\gcd(i,j)=1]}$$
由 $\sum\limits_{g|n}\mu(g)=[n=1]$ 得：
$$\prod\limits^n_{d=1}d^{\sum\limits^{\lfloor n/d\rfloor}_{i=1}\sum\limits^{\lfloor n/d\rfloor}_{j=1}\sum\limits_{g|\gcd(i,j)}\mu(g)}$$
$$\prod\limits^n_{d=1}d^{\sum\limits^{\lfloor n/d\rfloor}_{g=1}\mu(g)\lfloor\frac{n}{dg}\rfloor^2}$$
这个指数可以整除分块。（注意，$mod$ 是个质数，根据费马小定理，计算指数时应该对 $mod-1$ 取模）

出题人的做法是一个个枚举 $d$ 然后对每个 $d$ 整除分块。

但是我们可以注意到，指数中 $\sum$ 的上界是 $\lfloor\frac{n}{d}\rfloor$，明显可以对 $d$ 再来一次整除分块！

然后开心的把程序交了上去……

MLE？？？！！！

这就是出题人恶毒所在了。如果我们用两次整除分块，就需要再多一个阶乘数组，分分钟被卡……

那也没事。用尺取法的思想，可以弄两个指针，每次分块的 $[l,r]$ 变化时，指针就移动到相应的位置，边移边对阶乘做乘法。时间复杂度 $O(n)$。

还是有点说不清楚……看代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1000100,mod=104857601;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
	char ch=getchar();int x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,mu[maxn],pr[maxn/10],pl;
bool vis[maxn];
void init(){
	mu[1]=1;
	FOR(i,2,n){
		if(!vis[i]) mu[pr[++pl]=i]=-1;
		FOR(j,1,pl){
			if(i*pr[j]>n) break;
			vis[i*pr[j]]=true;
			if(i%pr[j]) mu[i*pr[j]]=-mu[i];
			else{mu[i*pr[j]]=0;break;}
		}
	}
	FOR(i,2,n) mu[i]+=mu[i-1];
}
int calc(int n){	//内层整除分块，上界是n
	int ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans+=1ll*(n/l)*(n/l)%(mod-1)*(mu[r]-mu[l-1]+mod-1)%(mod-1);
		ans%=mod-1;	//注意对mod-1取模！
	}
	return ans;
}
int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) ans=1ll*ans*a%mod;
	return ans;
}
int main(){
	n=read();
	init();
	int ans=1;
	FOR(i,1,n) ans=1ll*ans*i%mod;
	ans=qpow(ans,2*n);
	int f1=1,f2=1,c1=1,c2=1;	//两个阶乘和两个指针
	for(int l=1,r;l<=n;l=r+1){	//外层整除分块
		r=n/(n/l);
		while(c1<=r) f1=1ll*f1*c1%mod,c1++;	//把指针移到相应的位置
		while(c2<=l-1) f2=1ll*f2*c2%mod,c2++;	//同时修改阶乘
		ans=1ll*ans*qpow(1ll*qpow(f1,mod-2)*f2%mod,2*calc(n/l))%mod;
        //答案除以l到r所有数的积的2*calc(n/l)次方
	}
	printf("%d\n",ans);
}
```

---

## 作者：Makasukaka (赞：15)

## 前言

这场比赛我是现场打的，由于我太菜了qwq，所以不会莫比乌斯反演，只能写
一篇不用莫反的题解水水啦。

## 思路
- 看到了$gcd$和$lcm$， 我们可以想到这样的一条性质：

对于一个正整数$x$，根据唯一分解定理，可以唯一的写出它的一个表示:
$\prod_{i=1}^tp_i^{e_i}$ 这里$p_i$是$x$的素因子，$e_i$是$p_i$的次数。

对于两个数$x,y$:

$gcd(x,y)=\prod_{i=1}^tp_i^{min(e_{xi},e_{yi})}$; $lcm(x,y)=\prod_{i=1}^tp_i^{max(e_{xi},e_{yi})}$

注意这里的素因子，如果一个数$x$的一个素因子$p$的次数是$0$，也是要统计的。

这样，要求的东西就可以转化成：

$\sum_{i=1}^N\sum_{j=1}^N\prod_{k=1}^tp_k^{max(e_{ik},e_{jk})-min(e_{ik}, e{jk})}$

就是 $\prod_{k=1}^t\sum_{i=1}^N\sum_{j=1}^Np_k^{max(e_{ik},e_{jk})-min(e_{ik}, e{jk})}$

相当于我们考虑每一个质因子算它的贡献。

这里i和j是对称的，所以我们可以只计算
$\sum_{i=1}^N\sum_{j=1}^i{max(e_{ik},e_{jk})-min(e_{ik}, e_{jk})}$ 的值，最后次数*2就好了。

我们考虑1~n中哪些数可能对于答案有贡献，易知有$floor(\frac{n}{p_k})$ 个， 这些数的$p_k$的次数非0。($floor$表示下取整，原谅我不会markdown的下取整吧qwq)。

我们设一个$num$数组，$num[i]$表示$1\ to\  N$中有$p_k^i$这个因子的数的个数。如何计算$num$呢？我们考虑$floor(\frac{n}{p_k^i})$计算的是什么，这个计算的实际上是次数$>=i$的因子的个数。我们先用$num$把它存起来，然后对$num$做一个差分就是我们想知道的啦。

这样的话，我们已经把$1\ to\ n$ 的这些数按照其中$p_k$的次数分成了$log_{p_k}n$ 段，每一段中的$p_k$次数都是一样的。

所以我们可以从小到大考虑$p_i$的次数，根据上面的式子，只需要在每一段的分界处统计前面有多少个次数小于它的数和当前枚举到了哪一段。在这里统计这一段对于前面所有段的贡献就可以啦。

最后别忘了把这个次数贡献$*2$哦。

## 点评

我不知道这样说大家是否可以理解，但关于贡献的统计那里稍微有点绕。我自己在写的时候也仔细想了一会。不过大家只要想清楚分段的过程就可以啦！

## codes（注释在下面）

```cpp
#include <cstdio>
#include <vector>
using std :: vector;
vector<int> prime;
typedef long long LL;
const int N = 1e6 + 5, P = 104857601;
int vis[N], num[N], cnt, sum, tot;
int n;
inline void eluer(){
    vis[1] = 1;
    for (int i = 2; i <= (int)1e6; ++i) {
        if (!vis[i]) prime.push_back(i);
        for (int j = 0; j < prime.size(); ++j) {
            int cur = i * prime[j];
            if (cur > (int)1e6) break;
            vis[cur] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
inline LL quick_power(LL a, LL b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = (res * a) % P;
        a = (a * a ) % P;
        b >>= 1;
    }
    return res;
}
int main() {
    //freopen("luoguU61329.out", "w", stdout);
    scanf("%d", &n);
    eluer();
    LL ans = 1; LL sumwork = 0;
    int tt = prime.size();
    for (int i = 0; i < tt; ++i) {
        LL b = 1; sum = 0;
        if (n < prime[i]) break;
        while (n >= b) {
            num[++sum] = n / b;
            b *= prime[i];
        }
        for (int j = 1; j < sum; ++j) num[j] -= num[j + 1];
        sumwork += sum;
        LL res = 0, sumv = 0, sumcos = 0;
        for (int j = 1; j <= sum; ++j) {
            res +=  1LL * num[j] * (sumcos * (j - 1) - sumv);
            sumcos += num[j];
            sumv += num[j] * (j - 1);
        }
        res <<= 1;
        ans = (ans * quick_power(prime[i], res)) % P;
    }
    printf("%lld\n", ans);
    //printf("%lld\n", sumwork);
    return 0;
}

```
这里主要给大家解释一下算贡献的过程; $num[]$的含义就如同我上面说的，$sum$记录的是$p_k$一共有多少个不同次数,
$res$记录的是$p_k$这个质数的次数，$sumcos$记录的是之前一共有多少个
数，$sumv$记录的是之前的因数的总出现次数。我们是按照$j$从小到大枚举的，所以$j-1$可以表示当前这些数的次数。次数是从$0$开始的。

## 复杂度

我们考虑一下时间复杂度，素因子个数嘛，查了一下一个数$n$的互异素因子个数是$O(loglogn)$级别的。 里面枚举$j$的复杂度是$O(logn)$级别的。总复杂度就是$O(n + lognloglogn)$的啦！线性筛倒是瓶颈了qwq。

## 小吐槽

这题空间卡的让我深恶痛绝啊嘤嘤嘤。$8mb$的内存标志着不能同时开$3$个$1e6$的数组。迫不得已我用了$vector$来存素数。

## 结语

这题感觉还是挺有意思的，可惜我太弱了wvw，大家赶紧去享受切题的乐趣啦。

---

## 作者：CYJian (赞：15)

## Product

### 30分

直接枚举。。不用多说吧。。

### 100分

#### 蒟蒻${\rm CYJian}$的辣鸡$O(NlogN)$做法：

首先，我们用一个常识公式：$i \ast j = gcd(i,j)\ast lcm(i,j)$

然后原式可化为：

$$\prod_{i=1}^{N}\prod_{j=1}^{N}\frac{i \ast j}{(gcd(i, j))^2} \ (\bmod\ 104857601)$$

$$(\prod_{i=1}^{N}\prod_{j=1}^{N}i \ast j)\ast(\prod_{i=1}^{N}\prod_{j=1}^{N}gcd(i, j))^{-2} \ (\bmod\ 104857601)$$

$$(\prod_{i=1}^{N}i^N \ast N!) \ast (\prod_{d=1}^{N} d^{\sum_{i=1}^{N}\sum_{j=1}^{N} [gcd(i, j)==d])^{-2}} \ (\bmod\ 104857601)$$

$$(N!)^{2N} \ast (\prod_{d=1}^{N} d^{\sum_{i=1}^{\lfloor \frac{N}{d} \rfloor}\sum_{j=1}^{\lfloor \frac{N}{d} \rfloor} [gcd(i, j)==1])^{-2}} \ (\bmod\ 104857601)$$

这样的话就能做了。。

前面的东西搞一个快速幂，后面的枚举$d$，然后计算$N/d$内有多少组数是互质的，可以用欧拉函数算。这样就解决了。

### 大佬${\rm suwakow}$的强劲$O(N)$(近似)做法

> 对于$\frac{lcm(i,j)}{gcd(i,j)}$，可以考虑枚举每一个质数$p$，这样的话这一坨东西在质数$p$的贡献即为$p^{|t_i-t_j|}$，其中$t_x$表示$x$有多少个为$p$的因子。

> 然后可以考虑筛出所有质数后，对于每一个质数容斥处理出$N$以内所有数的当前质因子个数，然后经过处理后就能得到当前这个质因子的答案了。

STO ${\rm suwakow}$ orz

代码的话。。太丑了还是不放了吧。。

---

## 作者：Soulist (赞：12)

首先观察原式

$$\prod_{i=1}^n\prod_{j=1}^n \dfrac{lcm(i,j)}{gcd(i,j)}$$

因为$lcm(i,j) = ij /gcd(i,j)$

所以原式就是：

$$\prod_{i=1}^n\prod_{j=1}^n \dfrac{ij}{gcd(i,j)^2}$$

然后貌似有个性质，（感性理解）

$$\dfrac{a}{b}\%mod == \dfrac{a\%mod}{b\%mod}$$

这个性质也是：

$$\dfrac{a}{b}\%mod = (a\%mod) * inv(b\%mod)$$

其中$inv$是逆元。

然后我们就可以把原式变成这个样子：

$$\dfrac{\prod_{i=1}^n\prod_{j=1}^n ij}{\prod_{i=1}^n\prod_{j=1}^ngcd(i,j)^2}\%mod$$

于是分别讨论：

$$\prod_{i=1}^n\prod_{j=1}^n ij = \prod_{i=1}^ni^n\prod_{j=1}^n j= \prod_{i=1}^ni^n * n! = (n!)^n * \prod_{i=1}^ni^n$$
$$ = (n!)^{2n}$$

对于下面这一坨东西：

$$\prod_{i=1}^n\prod_{j=1}^ngcd(i,j)^2$$

我们注意到一个这样的性质：

若$i,j$互质，则$gcd(i,j) = 1$

若$i,j$不互质，不妨设$gcd(i,j) = x, $则$i = p*x, j = q*x$

所以$gcd(i,j) = x*gcd(p,q)$

那么实际上我们只需要对$p,q$进行考虑

设$pq$互质，其中$p <= q,$那么我们考虑有多少个数对$(i,j)$，满足：

$i = x*p, j = x*q$ ，那么$gcd(i,j) = x * gcd(p,q) = x$

这样的数对有$\left\lfloor\dfrac{n}{q}\right\rfloor$个（$q > p$）

这些数对对答案产生的贡献为：

$$\prod_{x=1}^{n/q} gcd(x*p,x*q)^2$$

因为$q,p$互质，所以$gcd(p,q) = 1$，原式实际上就是：

$$\prod_{x=1}^{n/q} x^2$$

即

$$\Bigg(\left\lfloor\dfrac{n}{q}\right\rfloor!\Bigg)^2$$

然后我们发现，因为$p<=q$，假设对于$q$而言，这样的$p$有$k$个，实际上$q$对答案产生的贡献就是

$$\Bigg(\left\lfloor\dfrac{n}{q}\right\rfloor!\Bigg)^{2k}$$

不难发现其实$p$的个数就是$1-q$中与$q$互质的数的个数

所以$q$对答案产生的贡献就是：

$$\Bigg(\left\lfloor\dfrac{n}{q}\right\rfloor!\Bigg)^{2φ(q)}$$

因为实际上题目所求的不仅仅有$p<=q$的数对，$p>q$的也包含了，所以对于数对$(p,q)$而言，产生的答案其实还有$(q,p),$所以还要平方一次。

最后，我们把底部化简成为了：（注意对于$1$而言，产生贡献为数对$(1,1)$，这个不需要平方）

$$(n!)^2 * \prod_{i=2}^{n}\Bigg(\left\lfloor\dfrac{n}{i}\right\rfloor!\Bigg)^{2φ(i)*2}$$

然后记得随时取模。

以及其实答案就是：

$$\dfrac{(n!)^{2n}\%mod}{(n!)^2 \prod_{i=2}^{n}\Big(\left\lfloor\dfrac{n}{i}\right\rfloor!\Big)^{4φ(i)}\%mod}$$

然后您这样写，发现$MLE$了，这道题卡空间。。。

按照上述做法，我们需要记录阶乘数组，然后求$φ$函数的时候用欧拉筛要记录质数数组，还要记录$φ$函数数组。。怎么优化？记录了$3$个$int$数组，还要开$long long$

我们考虑对上式下半部变形：

$$(n!)^2 \prod_{i=2}^{n}\Big(\left\lfloor\dfrac{n}{i}\right\rfloor!\Big)^{4φ(i)}$$

忽略那个$(n!)^2$，考虑优化后半部分：

$$\prod_{i=2}^{n}\Big(\left\lfloor\dfrac{n}{i}\right\rfloor!\Big)^{4φ(i)}$$

我们对每个数讨论，考虑它被乘了多少次，不难发现，对于数$x$

假设$\left\lfloor\dfrac{n}{i}\right\rfloor > x$那么$x$就会在计算$\Big(\left\lfloor\dfrac{n}{i}\right\rfloor!\Big)^{4φ(i)}$被乘以$4φ(i)$次。

然后$i$的取值是$2-n$，对于$x$假设$i>j$且有$\left\lfloor\dfrac{n}{i}\right\rfloor > x$

那么：$\left\lfloor\dfrac{n}{j}\right\rfloor > x$

所以我们就可以认为，当$\left\lfloor\dfrac{n}{i}\right\rfloor >= x$的时候，其余比$i$小的数$j$在计算$\Big(\left\lfloor\dfrac{n}{j}\right\rfloor!\Big)^{4φ(j)}$时也会算到$x$。

所以我们统计$φ(i)$的前缀和。记为$f(i)$；对于数$x$，
其会被计算次数为$4*f(n/i)$。

这个应该比较显然吧？然后$f(x)$数组可以直接在原来的$φ(i)$数组上处理，于是只用了一个大小为$N$的$int$数组

以及最后式子就是这样了：

$$\dfrac{(n!)^{2n}\%mod}{(n!)^2\prod_i^{n/2} i^{4f(n/i)}}$$


附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9'){
    	if(cc == '-') flus = -flus;
		cc = getchar();
	}
	while(cc >= '0' && cc <= '9')
	    cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
#define LL long long
#define re register
const int N = 1000000 + 1;
const int mod = 104857601;
int phi[N], pm[80000+5], top;
LL fac;
int n;
bool isp[N];
int pow2(re int x, re int k){//快速幂 
	re LL base = x, ans = 1;//用long long 
	while(k){
		if(k & 1) ans *= base, ans %= mod;
		base *= base, base %= mod;
		k >>= 1;
	}
	return ans % mod;
}
void init(){
	fac = 1;
	for(int i = 2; i <= n; i++){
		fac = fac * i % mod;//求n的阶乘 
		if(!isp[i]) phi[i] = i - 1, pm[++top] = i;
		for(int j = 1; j <= top; j++){
			if(i * pm[j] > n) break;
			isp[i * pm[j]] = 1;
			if(i % pm[j] == 0){
				phi[i * pm[j]] = phi[i] * pm[j];
				break;
			}
			phi[i * pm[j]] = phi[i] * phi[pm[j]];
		}
		
	}
}
void solve(){
	LL ans1 = pow2(fac, 2*n);
	LL ans2 = pow2(fac, 2);
	for(int i = 2; i <= n; i++){
		phi[i] = phi[i - 1] + phi[i], phi[i] = phi[i] % (mod - 1);//求前缀和 
	}
	for(int i = 2; i <= n/2; i++){
		ans2 = (ans2 * pow2(i, 4 * phi[n/i])) % mod;//对每个数讨论，至多讨论到n/2，因为i初始为2，取值最大为n/2 
	}
	LL ans = ans1 * pow2(ans2, mod - 2) % mod;//ans = ans1/ans2（ans2求逆元） 
	printf("%d", ans);//最后的答案取了模，在int内 
}
signed main()
{
	n = read();
	init();
	solve();
	return 0;
}
```

---

## 作者：xgzc (赞：5)

首先，这种式子肯定是莫比乌斯反演之类的套路
$$\begin{aligned}& \prod_{i=1}^n\prod_{j=1}^n \frac{\mathrm{lcm}(i,j)}{\gcd(i,j)} \\=& \prod_{i=1}^n\prod_{j=1}^n \frac{ij}{\gcd^2(i,j)} \\\end{aligned}$$

其中

$$\begin{aligned}&\prod_{i=1}^n\prod_{j=1}^n \gcd(i,j)\\=&\prod_{d=1}^n d^{\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=d]}\end{aligned}$$
然后暴力反演或者求$\varphi$即可

------

这种方法太$\texttt{naive}$了，换一种

考虑筛出$f(i) = \prod_{j=1}^n \gcd(i,j)$

当$i \in \mathrm{prime}$时，$f(i) = i^{n / i}$

否则找到一个质因子$p$

设$i = i' \times p^a$，那么因为$p$能够加到$\prod \gcd(i,j)$的总贡献是$p^{n / p^a}$，所以

$$f(i) = f(i') \times p^{n / p^a}$$

然后暴力线性筛就可以了

时间复杂度大约是$\mathrm{O}(n\log_2 n)$

代码见我的[$blog$](https://www.cnblogs.com/cj-xxz/p/10386719.html)

---

## 作者：henry_y (赞：4)

[$blog$](https://www.cnblogs.com/henry-1202/p/10462180.html)

注，下方$(i,j)$均指$gcd(i,j)$，以及证明过程有一定的跳步，请确保自己会莫比乌斯反演的基本套路。

介绍本题的$O(n)$和$O(n\sqrt{n})$做法，本题还有$O(nlogn)$做法，需要用到欧拉函数，或者是从质因子角度考虑也可以得到另外一个$O(n)$做法。

这个$O(n)$做法能进第一页。

题目就是求
$$\prod_{i=1}^n\prod_{j=1}^n\frac{ij}{(i,j)^2}$$

考虑分解一下

$$\prod_{i=1}^n\prod_{j=1}^n\frac{ij}{(i,j)^2}=        \frac{\prod_{i=1}^n\prod_{j=1}^nij}{\prod_{i=1}^n\prod_{j=1}^n(i,j)^2}$$

对于分子可得

$$\begin{aligned}&\prod_{i=1}^n\prod_{j=1}^nij\\&=\prod_{i=1}^ni\prod_{j=1}^nj\\&=\prod_{i=1}^ni*n!\\&=(n!)^{2n}\end{aligned}$$
对于分母，我们考虑莫比乌斯反演

$$\begin{aligned}&\prod_{i=1}^n\prod_{j=1}^n(i,j)^2\\&=\prod_{d=1}^nd^{2\sum_{i=1}^n\sum_{j=1}^n[(i,j)=d]}\\&=\prod_{d=1}^nd^{2\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}[(i,j)=1]}\\&=\prod_{d=1}^nd^{2\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}\mu(k)\lfloor\frac{n}{kd}\rfloor^2}\\\end{aligned}$$

至此，枚举$d$，对指数整除分块，即可$O(n\sqrt{n})$解决此题。

容易发现$\lfloor\frac{n}{d}\rfloor$是可以整除分块的。那么怎么处理区间$[l,r]$的$d$呢，将它展开，其实就是$\frac{r!}{(l-1)!}$，由于出题人卡空间，所以可以直接计算阶乘而不是预处理（复杂度同样是$O(n)$，每个数只会被遍历一次）

那么就可以做到$O(n)$解决本题了。

```cpp
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

const int mod = 104857601;
const int p = 104857600;
const int N = 1000010;

bool vis[N];
short mu[N];
int pr[N], cnt = 0;
int fac;

int power(int a, int b, int Mod) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = (ll)ans * a % Mod;
		a = (ll)a * a % Mod;
		b >>= 1;
	}
	return ans % Mod;
}

void init(int n) {
	mu[1] = 1;
	for(int i = 2; i <= n; ++i) {
		if(!vis[i]) pr[++cnt] = i, mu[i] = -1;
		for(int j = 1; j <= cnt && i * pr[j] <= n; ++j) {
			vis[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
			mu[i * pr[j]] = -mu[i];
		}
		mu[i] += mu[i - 1];
	}
	fac = 1;
	for(int i = 1; i <= n; ++i) fac = (ll)fac * i % mod;
}

int n;

int calc2(int n) {
	int ans = 0;
	for(int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans = (ans + (ll)(n / l) * (n / l) % p * (mu[r] - mu[l - 1] + p) % p) % p;
	}
	return ans % p;
}

int main() {
	scanf("%d", &n);
	init(n);
	int ans = 1;
	int sum = power((ll)fac * fac % mod, n, mod);
	for(int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l); fac = 1ll;
		for(int i = l; i <= r; ++i) fac = (ll)fac * i % mod;
		int t = power((ll)fac * fac % mod, calc2(n / l), mod);
		ans = (ll)ans * t % mod;
	}
	printf("%lld\n", (ll)sum * power(ans, mod - 2, mod) % mod);
}
```

$O(n\sqrt{n})$代码
```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <deque>
#include <map>
#include <set>

#define ll long long
#define inf 0x3f3f3f3f
#define il inline

namespace io {

#define in(a) a = read()
#define out(a) write(a)
#define outn(a) out(a), putchar('\n')

#define I_int int
inline I_int read() {
    I_int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
char F1[200];
inline void write(I_int x) {
    if (x == 0) return (void) (putchar('0'));
    I_int tmp = x > 0 ? x : -x;
    if (x < 0) putchar('-');
    int cnt = 0;
    while (tmp > 0) {
        F1[cnt++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while (cnt > 0) putchar(F1[--cnt]);
}
#undef I_int

}
using namespace io;

using namespace std;

const ll mod = 104857601;
const ll p = 104857600;
const int N = 1000010;

bool vis[N];
short mu[N];
int pr[N], cnt = 0;
ll fac;

ll power(ll a, int b, int Mod) {
    ll ans = 1;
    while(b) {
        if(b & 1) ans = (long long) ans * a % Mod;
        a = (long long) a * a % Mod;
        b >>= 1;
    }
    return ans % mod;
}

void init(int n) {
    mu[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!vis[i]) pr[++cnt] = i, mu[i] = -1;
        for(int j = 1; j <= cnt && i * pr[j] <= n; ++j) {
            vis[i * pr[j]] = 1;
            if(i % pr[j] == 0) break;
            mu[i * pr[j]] = -mu[i];
        }
        mu[i] += mu[i - 1];
    }
    fac = 1;
    for(ll i = 1; i <= n; ++i) fac = (ll)fac * i % mod;
}

int n;

ll calc2(ll n) {
    ll ans = 0;
    for(ll l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans = ans + (n / l) % p * (n / l) % p * (ll)(mu[r] - mu[l - 1] + p) % p;
        ans %= p; ans += p; ans %= p;
    }
    return ans % p;
}

int main() {
    n = read();
    init(n);
    ll ans = 1;
    for(ll i = 1; i <= n; ++i) 
        ans = ans * power((long long)i * i % mod, calc2(n / i), mod) % mod;
    ll sum = power((long long)fac * fac % mod, n, mod);
    printf("%lld\n", sum % mod * power(ans, mod - 2, mod) % mod);
}
```

---

## 作者：command_block (赞：4)

事实证明,$gcd$和$\sum$套起来真的比较好玩!

$gcd$和$∏$套起来……也很好玩。

下面的解法是**莫比乌斯反演**,运用这个解法,这道题的两个$∏$上面的数字可以不同(会有MLE的危险)。

事实证明我想多了,提交记录里有许多大佬用比我短还比我快的代码华丽AC了,然而我并看不懂,坐等其他解法的题解。

从莫比乌斯反演的角度来看,这题是道好题,解法很机智(至少在我这个蒟蒻看来是这样的。)

[介绍莫比乌斯反演的文章](https://www.luogu.org/blog/command-block/mu-bi-wu-si-fan-yan-ji-ji-ying-yong)

------------

首先呢,题目叫我们求$\large{∏\limits_{i=1}^N∏\limits_{j=1}^N\dfrac{lcm(i,j)}{gcd(i,j)}}$,对大质数取模。

小学奥数告诉我们$lcm(i,j)=\dfrac{i*j}{gcd(i,j)}$

于是式子变成$\large{∏\limits_{i=1}^N∏\limits_{j=1}^N\dfrac{i*j}{gcd(i,j)^2}}$

再变成$\Large{\frac{∏\limits_{i=1}^N∏\limits_{j=1}^Ni*j}{\left(∏\limits_{i=1}^N∏\limits_{j=1}^Ngcd(i,j)\right)^2}}$

$∏\limits_{i=1}^N∏\limits_{j=1}^Ni*j$用一个很simple的快速幂就可以求出来了。

重点是如何求$∏\limits_{i=1}^N∏\limits_{j=1}^Ngcd(i,j)$

我们设$G(x,y)$为$\sum\limits_{i=1}^y\sum\limits_{j=1}^y[gcd(i,j)==x]$。

那么$\large{∏\limits_{i=1}^N∏\limits_{j=1}^Ngcd(i,j)=∏\limits_{i=1}^Ni^{G(i,N)}}$(好好理解哦)

这相当于把$gcd(i,j)$中相同的个数统计出来,然后用快速幂一次搞定。

考虑如何求出$G(1,N),G(2,N)……G(N,N)$。

一个暴力的做法是:直接套用[这道题](https://www.luogu.org/problemnew/show/P3455)的解法,对每个$G(1,N)$用一个整除分块$O(\sqrt{n})$求,超时妥妥的。

讲一下这个做法。

我们要求$G(x,N)=\sum\limits_{i=1}^N\sum\limits_{j=1}^N[gcd(i,j)==x]$

我们把式子中所有的数整除x(这是老套路了)。

得到$G(x,N)=\sum\limits_{i=1}^{N/x}\sum\limits_{j=1}^{N/x}[gcd(i,j)==1]=G(1,N/x)$

也就是说我们只要能够求出求$G(1,N)$(N为变量)就好了。

接下来**反演**。

对一个确定的$N$设$f(x)=\sum\limits_{i=1}^N\sum\limits_{j=1}^N[gcd(i,j)==x]$ , $F(x)=\sum\limits_{i=1}^{N}\sum\limits_{j=1}^{N}[x|gcd(i,j)]$

得出$F(N)=\sum\limits_{N|d}f(d)$

由反演定理得出$f(N)=\sum\limits_{N|d}\mu(d/N)F(d)$

先对$F(d)$进行简化,把式子中所有的数整除x。

得到$F(d)=\sum\limits_{i=1}^{N/x}\sum\limits_{j=1}^{N/x}[1|gcd(i,j)]=(N/x)^2$

我们要求$G(1,N)=f(1)$,直接令上式中$N=1$得到:

$f(1)=\sum\limits_d\mu(d)F(d)$

考虑到$F(d)=(N/x)^2$,在$1<=d<=N$时才有值(意义):

$f(1)=\sum\limits_{d=1}^{N}\mu(d)F(d)=\sum\limits_{d=1}^{N}\mu(d)(N/d)^2$

到这里已经可以$O(n)$求了,我们对$(N/d)$整除分块即可达到$O(\sqrt{n})$,这里不再赘述,感兴趣的同学可以阅读上面介绍莫反的文章。

------------

接下来是正解,在上面的解法中稍作修改即可。

如果你会整除分块,再注意到$G(x,N)=G(1,N/x)$你会发现$N/x$的取值只会有$O(\sqrt{N})$种。

我们对$G(1,N/x)$整除分块,就只用求$O(\sqrt{N})$次$G(1,?)$复杂度从$O(N\sqrt{N})$降到$O(NlogN)$

(瓶颈在快速幂,如果有心思把分块进行到底,还可以变成$O(N)$)

```cpp
#include<algorithm>
#include<cstdio>
#define mod 104857601
using namespace std;
int t,n,m,tn,p[200500],mu[1000500];
bool e[1000500];
long long sav[1000500],ans=1;
long long powM(long long a,long long t=mod-2)
{
  long long ans=1,buf=a;
  while(t){
  	if (t&1)ans=ans*buf%mod;
  	buf=buf*buf%mod;
  	t>>=1;
  }return ans;
}
void getmu()
{
  e[1]=1;mu[1]=1;
  for (int i=2;i<=1000100;i++){
  	if (!e[i]){
  	  p[++tn]=i;
  	  mu[i]=-1;
    }for (int j=1;j<=tn;j++){
      if (1ll*i*p[j]>1000100)break;
      e[i*p[j]]=1;
      mu[i*p[j]]=i%p[j] ? -mu[i] : 0;
      if (!i%p[j])break;
    }
  }//线筛出mu 
}
long long calc(int n)
{
  long long ans=0;
  int l=1,r;
  for (;l<=n;l=r+1){
  	r=n/(n/l);
  	ans+=1ll*(n/l)*(n/l)*(mu[r]-mu[l-1]);
  }return ans;
  //套路反演
}
int main()
{
  scanf("%d",&n);
  getmu();
  for (int i=2;i<=1000100;i++)mu[i]+=mu[i-1];
  //预处理mu前缀和
  for (int i=1;i<=n;i++){
  	int nn=n/i;
  	if (!sav[nn])sav[nn]=calc(nn);
    //如果求过就不用再求,懒人分块法
	ans=(ans*powM(i,sav[nn]))%mod;
  }ans=powM(ans);
  ans=(ans*ans)%mod;

  for (int i=1;i<=n;i++)
   ans=ans*powM(i,n*2)%mod;
  printf("%lld",ans);
  return 0;
}
```

所以这题可以出个加强版:求$\large{∏\limits_{i=1}^N∏\limits_{j=1}^M\dfrac{lcm(i,j)}{gcd(i,j)}},(N,M<=10^7)$。

---

## 作者：蒟蒻君HJT (赞：4)

## 来一个简单的 $O(n)$ 解法：不用卡常，不用筛 $\mu,\phi$，不用整除分块。

只需要线性筛质数。

直接列式：

$$A=\prod_{i=1}^{n}\prod_{j=1}^n\frac{\text{lcm}(i,j)}{\gcd(i,j)}=\prod_{d=1}^n \prod_{i=1}^{\lfloor n/d\rfloor}\prod_{j=1}^{\lfloor n/d\rfloor}(ij)^{[gcd(i,j)=1]}$$

莫比乌斯反演一下。

$$A=\prod_{d=1}^n \prod_{i=1}^{\lfloor n/d\rfloor}\prod_{j=1}^{\lfloor n/d\rfloor}(ij)^{\sum_{s|i,s|j}\mu(s)}=\prod_{d=1}^n \prod_{i=1}^{\lfloor n/d\rfloor}\prod_{j=1}^{\lfloor n/d\rfloor}\prod_{s|i,s|j}(ij)^{\mu(s)}=\prod_{d=1}^n\prod_{s=1}^{\lfloor n / d \rfloor}\prod_{i=1}^{\lfloor n / ds \rfloor}\prod_{j=1}^{\lfloor n / ds \rfloor}(ijs^2)^{\mu(s)}=\prod_{d=1}^n\prod_{s=1}^{\lfloor n / d \rfloor}(\lfloor n / ds \rfloor !)^{2\mu(s)\lfloor n / ds \rfloor}s^{2\mu(s)\lfloor n / ds \rfloor^2}$$

为了方便我们对答案 $A$ 先开个根，最后再平方回去。注意 $t=ds$。

$$\sqrt A=\prod_{d=1}^n\prod_{s=1}^{\lfloor n / d \rfloor}(\lfloor n / ds \rfloor !)^{\mu(s)\lfloor n / ds \rfloor}s^{\mu(s)\lfloor n / ds \rfloor^2}=\prod_{t=1}^n(\lfloor n / t \rfloor !)^{\lfloor n / t \rfloor \sum_{r|s}\mu(r)}(\prod_{s|t}s^{\mu(s)})^{\lfloor n / t \rfloor ^2}$$

注意到 $\sum_{r|s}\mu(r)=[s=1]$，我们把 $t=1$ 和 $t\geq 2 $的情况分开。记数论函数 $g(t)=\prod_{s|t}s^{\mu(s)}$。

$$\sqrt A= (n!)^n\prod_{t=2}^n (g(t))^{\lfloor n / t \rfloor ^2}$$

由于用写出 $t$ 的分解式后，可以用二项式定理简单证明如下性质，因此此处不加证明地直接给出此性质：

（原谅不会打大括号的 LaTeX）

若 $t$ 可以表示为 $p^k$ （$p$ 为质数）的形式，则 $g(t)=\frac{1}{p}$；

否则 $g(t)=1$。

换句话说，我们只需要枚举所有能表示成 $p^k$ 的 $t$ 就行了。筛到某个质数 $p$ 时，直接枚举 $k$ 就行，把幂次累加并对 $mod - 1$ 取模，只需求一次逆元和一次快速幂。设不大于 $n$ 的质数个数为 $\pi(n)$，则这部分复杂度为 $O(\pi(n)\log mod)$。

线性筛的时候，只需要保存一个质数表，一个表示每个数是否为质数的 $\text{bitset}$。空间消耗不到 $\text{1MB}$，掉掉有余。

最终以 $O(n+\pi(n)\log mod)=O(n+n\log mod/\log n)\approx O(n)$ 的时间复杂度解决了本题，可以认为是线性的。虽然推导过程中用到了莫比乌斯函数和其反演，但最终的式子非常简洁。

code：

```cpp
#include <bits/stdc++.h>
const int mod = 104857601;
inline int mul(int x, int y){
	return (int)(1ll * x * y % (1ll * mod));
}
inline int add(int x, int y){
	return x + y >= mod ? x + y - mod : x + y;
}
inline int minus(int x, int y){
	return x < y ? x - y + mod : x - y;
}
inline int Qpow(int x, int y){
	int r = 1;
	while(y){
		if(y & 1) r = mul(r, x);
		x = mul(x, x);
		y >>= 1;
	}
	return r;
}
int n, ans = 1;
int p[100005], cnt = 0;
std::bitset <1000005> is;
void solve(){
	scanf("%d", &n);
	is.set();
	is[1] = 0;
	for(int i = 1; i <= n; ++i) ans = mul(ans, i);
	ans = Qpow(ans, n);
	for(int i = 2; i <= n; ++i){
		if(is[i] == 1){
			p[++cnt] = i;
			int q = i, t = Qpow(i, mod - 2);
			int s = 0;
			while(q <= n){
				s += 1ll * (n / q) * (n / q) % (mod - 1);
				s >= mod - 1 ? s -= (mod - 1) : true; 
				if(i <= 1000) q *= i;
				else break;
			}
			ans = mul(ans, Qpow(t, s));
		}
		for(int j = 1; j <= cnt && i * p[j] <= n; ++j){
			is[i * p[j]] = 0;
			if(i % p[j] == 0) break;
		}
	}
	printf("%d\n", mul(ans, ans));
	return ;
}
int main(){
	int T = 1;
	while(T--) solve();
	return 0;
}

```

后记：作者非常菜，完全不会做这道简单题，一直到 $\sqrt A$ 之前的部分都是 @p31pr 完成的。

---

## 作者：SHZhang (赞：2)

这道题需要我们计算的值：

$ \prod_{i=1}^{n}\prod_{j=1}^{n}\frac{lcm(i, j)}{gcd(i, j)} $

首先，我们知道：

$ lcm(i, j)=\frac{ij}{gcd(i, j)} $

于是，最上面的公式可以转化为：

$ \prod_{i=1}^{n}\prod_{j=1}^{n}\frac{ij}{gcd(i, j)^{2}} $

到这里，分别计算分子的乘积，以及分母的乘积即可。

那么如何计算这两个乘积呢？

### 1. 分子

$ \prod_{i=1}^{n}\prod_{j=1}^{n}ij $

画一个表格（例如在 $ n = 5 $ 的时候，如下）：

| 1 | 2 | 3 | 4 | 5 |
| - | - | - | - | - |
| $ 1 \times 1 $ | $ 1 \times 2 $ | $ 1 \times 3 $ | $ 1 \times 4 $ | $ 1 \times 5 $ |
| $ 2 \times 1 $ | $ 2 \times 2 $ | $ 2 \times 3 $ | $ 2 \times 4 $ | $ 2 \times 5 $ |
| $ 3 \times 1 $ | $ 3 \times 2 $ | $ 3 \times 3 $ | $ 3 \times 4 $ | $ 3 \times 5 $ |
| $ 4 \times 1 $ | $ 4 \times 2 $ | $ 4 \times 3 $ | $ 4 \times 4 $ | $ 4 \times 5 $ | 
| $ 5 \times 1 $ | $ 5 \times 2 $ | $ 5 \times 3 $ | $ 5 \times 4 $ | $ 5 \times 5 $ |

我们先只观察表格中每一格中，乘号**左侧**的数。

| 1 | 2 | 3 | 4 | 5 |
| - | - | - | - | - |
| 1 | 1 | 1 | 1 | 1 |
| 2 | 2 | 2 | 2 | 2 |
| 3 | 3 | 3 | 3 | 3 |
| 4 | 4 | 4 | 4 | 4 |
| 5 | 5 | 5 | 5 | 5 |

它们的乘积是多少？每一列的乘积是 $ n! $，所以这些数的乘积是 $ n!^{n} $。

乘号**右侧**的数也很相似，乘积也是$ n!^{n} $。

所以，最上面的公式，分子部分的乘积是$ n!^{2n} $。

### 2. 分母

$ \prod_{i=1}^{n}\prod_{j=1}^{n}gcd(i, j)^{2} $

我们发现一个特点：虽然我们要对很多个gcd的值求乘积，但是不同的gcd值的数量是相对有限的（n个）。

所以，可以使用这个方法：令 $ f[i] $ 表示在 $ a \in [1, n] $ 且 $ b \in [1, n] $ 的条件下，有多少对 $ a $，$ b $ 满足 $ gcd(a, b)=i $。

我们可以这样计算 $ f[i] $：

1. 先计算有多少对 $ a $，$ b $ 满足 $ gcd(a, b)=i $ 是 **$ i $ 的倍数**。这个值很容易得到，是 $ \lfloor\frac{n}{i}\rfloor\lfloor\frac{n}{i}\rfloor $。
2. 将 $ f[i] $ 的值**减去** $ f[2i] $、$ f[3i] $、$ f[4i]\cdots $的值。

注意 $ f[i] $ 的值必须按照从大到小的顺序计算。可以证明这样做的时间复杂度是 $ O(nlogn) $ 的。

计算完 $ f[i] $ 之后，分母的值就很容易计算了。

### 3.注意事项

这题的内存限制只有8MB，但 $ f[i] $ 的取值是 long long 范围的。

把 $ f[i] $ 开 long long 的话，再加上其他部分的内存占用，很容易就 MLE 了。

所以我使用了一个小技巧：因为对于很大的 $ i $ ，$ f[i] $ 会很小，不需要 long long，所以我把 $ i $ 比较小的 $ f[i] $ 存储在 long long 数组里，把$ i $ 比较大的 $ f[i] $ 存储在 int 数组里。

```cpp
#include <cstdio>

using namespace std;

#define MOD 104857601
#define inv(a) fpow(a, MOD - 2)

// 在代码中，cnt代表了f的意思
#define getcnt(a) ((a) > 100000 ? cntR[a-100000] : cntL[a])
#define setcnt(a, b) ((a) > 100000 ? cntR[a-100000] = b : cntL[a] = b)

long long cntL[100005];
int cntR[900005];

long long n;

int mul(int a, int b)
{
    return ((long long)a * (long long)b) % MOD;
}

int fpow(int base, long long exponent)
{
    int ans = 1;
    int cur = base;
    for (int i = 0; i < 45; i++) {
        if (exponent < ((long long)1 << (long long)i)) break;
        if (exponent & ((long long)1 << (long long)i)) {
            ans = mul(ans, cur);
        }
        cur = mul(cur, cur);
    }
    return ans;
}

int main()
{
    scanf("%lld", &n);
    for (int i = n; i >= 1; i--) {
        setcnt(i, (long long)(n / i) * (long long)(n / i));
        for (int j = i * 2; j <= n; j += i) {
            setcnt(i, getcnt(i) - getcnt(j));
        }
    }
    int nfact = 1;
    for (int i = 2; i <= n; i++) nfact = mul(nfact, i);
    int numerator = fpow(nfact, n * 2);
    int denominator = 1;
    for (int i = 2; i <= n; i++) {
        denominator = mul(denominator, fpow(mul(i, i), getcnt(i)));
    }
    printf("%d", mul(numerator, inv(denominator)));
    return 0;
}

```






---

## 作者：Leasier (赞：2)

1. $30 \operatorname{pts}$ 做法

直接暴力计算即可。时间复杂度为 $O(n^2 \log n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int mod = 104857601;

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

inline ll lcm(int a, int b){
	return (ll)a * b / gcd(a, b);
}

int main(){
	int n;
	ll ans = 1;
	scanf("%d", &n);
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= n; j++){
			ans = ans * (lcm(i, j) / gcd(i, j) % mod) % mod;
		}
	}
	printf("%lld", ans);
	return 0;
}
```
2. $100 \operatorname{pts}$ 做法

前置芝士：[欧拉定理（Euler）](https://www.cnblogs.com/yifusuyi/p/9997009.html)、[杜教筛](https://gypsophila.blog.luogu.org/dls-tql)

我们先来化简原式。

原式 $= \displaystyle\prod_{i = 1}^N \prod_{j = 1}^N \frac{ij}{\gcd(i, j)^2}$

$ = \displaystyle\frac{(N!)^{2N}}{\displaystyle\prod_{i = 1}^N \prod_{j = 1}^N \gcd(i, j)^2}$

$ = \displaystyle\frac{(N!)^{2N}}{\displaystyle(\prod_{i = 1}^N \prod_{j = 1}^N \gcd(i, j))^2}$

$ = \displaystyle\frac{(N!)^{2N}}{\displaystyle(\prod_{d = 1}^N d^{\sum_{i = 1}^{\lfloor \frac{N}{d} \rfloor} \sum_{j = 1}^{\lfloor \frac{N}{d} \rfloor} [\gcd(i, j) = 1]})^2}$

$ = \displaystyle\frac{(N!)^{2N}}{\displaystyle(\prod_{d = 1}^N d^{2 \sum_{i = 1}^{\lfloor \frac{N}{d} \rfloor} \varphi(i) - 1})^2}$

预处理阶乘和欧拉函数前缀和即可。由于 $\varphi(104857601) = 104857601 - 1 = 104857600$，所以只要对分母上的指数模 $104857600$ 即可。由于此题极为卡空间，所以预处理阶乘的数组只能用 int，且需要用杜教筛算欧拉函数前缀和。时间复杂度为 $O(n \log n)$。

代码：
```cpp
#include <iostream>
#include <map>

using namespace std;

typedef long long ll;

const int N = 1e4 + 7, M = 1e6 + 7, mod = 104857601;
int prime[N], phi[N], sum[N], fac[M]; // 万恶的空间限制迫使我用 int
bool p[N];
map<ll, ll> mp;

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n){
	int cnt = 0;
	p[0] = p[1] = true;
	phi[1] = 1;
	for (register int i = 2; i < N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				phi[t] = phi[i] * prime[j];
				break;
			}
			phi[t] = phi[i] * (prime[j] - 1);
		}
	}
	for (register int i = 1; i < N; i++){
		sum[i] = (sum[i - 1] + phi[i]) % (mod - 1);
	}
	fac[0] = fac[1] = 1;
	for (register int i = 2; i <= n; i++){
		fac[i] = (ll)fac[i - 1] * i % mod;
	}
}

inline ll get_euler_sum(int n, int mod){
	if (n < N) return sum[n];
	if (mp.count(n)) return mp[n];
	ll ans = (ll)n * (n + 1) / 2 % mod;
	for (register int i = 2, j; i <= n; i = j + 1){
		int tn = n / i;
		j = n / tn;
		ans = ((ans - get_euler_sum(tn, mod) * (j - i + 1) % mod) % mod + mod) % mod;
	}
	return mp[n] = ans;
}

int main(){
	int n;
	ll ans = 1;
	cin >> n;
	init(n);
	for (register int i = 1, j; i <= n; i = j + 1){
		int tn = n / i;
		j = n / tn;
		ans = ans * quick_pow(fac[j] * quick_pow(fac[i - 1], mod - 2, mod) % mod, ((get_euler_sum(tn, mod - 1) * 2 - 1) % (mod - 1) + (mod - 1)) % (mod - 1), mod) % mod;
	}
	cout << quick_pow(fac[n], n * 2, mod) * quick_pow(ans * ans % mod, mod - 2, mod) % mod;
	return 0;
}
```

---

## 作者：redegg (赞：1)

注意，本文的“/”代表除法向下取整。

$lcm(i,j)=i\times j/gcd(i,j)$

$lcm(i,j)/gcd(i,j)=i\times j / gcd(i,j)^2$

我们可以求出所有$i\times j$的乘积值。

$\prod ^n_{i=1} \prod ^n_{j=1}i\times j=n!^{2n}$

那么，剩下的就是求出所有$gcd(i,j)^2$的乘积值，用$n!^{2n}$去除就行了。

那么怎么求出所有的$gcd(i,j)^2$的乘积呢？

我们知道，对于一个数$x$，有$(n/x)\times (n/x)$对$gcd$可以整除$x$。

如果我们设$x$为质数，那么$(n/x^y)\times (n/x^y)$的含义就是多少个$gcd$分解质因数后质因数中的$x$的数量大于等于$y$个

那么我们枚举$x$和$y$（$x$为质数，$y \ge 1$），那么现在所有$gcd(i,j)^2$的乘积就等于所有
$$x^{2\times(n/x^y)\times (n/x^y)}$$的乘积。

当然了，$x^y\le n$

为什么呢？因为只含$1$个$2$的$gcd$在$x=2,y=1$时求出来了，同时也把含$2$个$2$,$3$个$2$...的$gcd$都提前乘了一个$2$，那么在枚举含$x=2,y=2$时，我们只用乘一个$2$，因为之前已经乘了一个$2$，刚好把只含$2$个$2$的$gcd$给算出来了，但是同时也提前给含$3$个，$4$个..乘了个$2$。以此类推。最后一次一定不会多乘。

这样，可以不重复不多于地求出所有$gcd(i,j)^2$的值。

最后，由于比较大，我们用逆元将除转换成乘法。

答案：$(n!^{2n}\times (\prod ^n_{i=1} \prod ^n_{j=1}gcd(i,j)^2)^{mod-2})\%mod$

代码如下:

```
#include <bits/stdc++.h>
using namespace std;

long long n;
long long mod=104857601;
long long k=1;
long long ans=1;

long long p[1000005];
long long f[1000005];
int m[1000005];
int num;

long long fast(long long x,long long v)
{
    long long an=1;
    while(v)
    {
        if(v%2)
            an=(an*x)%mod;
        x=(x*x)%mod;
        v/=2;
    }
    return an;
}

void Prime()
{
    num=1;
    memset(m,0,sizeof(m));
    for(int i = 2; i <=n; i++)
    {
        if(m[i] == 0)
            p[num++] = i;
        for(int j = 1; j < num && p[j] * i <= n; j++)
        {
            m[i * p[j]] = 1;
            if(i % p[j] == 0)
                break;
        }
    }
    num--;
}

int main()
{
    scanf("%lld",&n);
    for(int i=1; i<=n; i++)
        ans=(ans*i)%mod;
    ans=fast(ans,2*n);
    Prime();
    for(int i=1; i<=num; i++)
    {
        if(f[i]==0)
        {
            f[i]=p[i];
            if(p[i]*p[i]<=n)
            {
                num++;
                p[num]=p[i]*p[i];
                f[num]=p[i];
                while(p[num]*p[i]<=n)
                {
                    num++;
                    p[num]=p[num-1]*p[i];
                    f[num]=p[i];
                }
            }
        }
       ans=(ans*fast(fast(f[i],2*(n/p[i])*(n/p[i])),mod-2))%mod;
    }
    printf("%lld\n",ans);
}

```

---

## 作者：Adove (赞：1)

$$ \prod_{i=1}^{N} \prod_{j=1}^{N} \frac{LCM(i,j)}{(i,j)} $$

$$ \prod_{i=1}^{N} \prod_{j=1}^{N} \frac{ij}{(i,j)^2} $$

先枚举$gcd$

$$\frac{\prod_{i=1}^{N}\prod_{j=1}^{N}ij}{\prod_{d=1}^{N}d^{2\sum_{d|i}\mu(\frac{i}{d})\lfloor \frac{N}{i} \rfloor^2}}$$

然后我们枚举$i$

$$\frac{\prod_{i=1}^{N}\prod_{j=1}^{N}ij}{\prod_{i=1}^{N}(\prod_{d|i}d^{\mu(\frac{i}{d})})^{2\lfloor \frac{N}{i} \rfloor^2}}$$

发现

$$(\prod_{d|i}d^{\mu(\frac{i}{d})})$$

可以在调和级数复杂度内用枚举倍数的方式求得

处理前缀积后分母可以除法分块

分子其实是$(n!)^{2n}$

注意下空间和常数，然后这个问题就$\Theta(n \log n)$解决了

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int MAXN=1e6+5;
const int MOD=104857601;

int n,ans=1;
int p[80005],v[MAXN];
short mu[MAXN];
bool b[MAXN];

int Fpw(int a,int b)
{
	int x=1;
	while(b){
		if(b&1) x=(long long)x*a%MOD;
		b>>=1;a=(long long)a*a%MOD;
	}return x;
}

int main()
{
	scanf("%d",&n);
	mu[1]=v[0]=v[1]=1;
	for(int i=2;i<=n;++i){
		v[i]=1;
		if(!b[i]) p[++p[0]]=i,mu[i]=-1;
		for(int j=1;j<=p[0]&&i*p[j]<=n;++j){
			b[i*p[j]]=1;
			if(i%p[j]) mu[i*p[j]]=-mu[i];
			else{mu[i*p[j]]=0;break;}
		}
	}for(int i=2;i<=n;++i){
		int tmp;
		if(i<<1<=n) tmp=Fpw(i,MOD-2);
		for(int j=i,c=1;j<=n;j+=i,++c){
			if(mu[c]>0) v[j]=(long long)v[j]*i%MOD;
			else if(mu[c]<0) v[j]=(long long)v[j]*tmp%MOD;
		}v[i]=(long long)v[i]*v[i-1]%MOD;
	}for(int l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		int tmp=(long long)v[r]*Fpw(v[l-1],MOD-2)%MOD,c=(long long)(n/l)*(n/l)*2%(MOD-1);
		ans=(long long)ans*Fpw(tmp,c)%MOD;
	}int base=1;for(int i=2;i<=n;++i) base=(long long)base*i%MOD;
	base=Fpw(base,n);base=(long long)base*base%MOD;
	printf("%d\n",(long long)base*Fpw(ans,MOD-2)%MOD);
	return 0;
}
```

---

## 作者：SSerxhs (赞：0)

看到gcd和pai果断反演。（以下分数均为整除）

先化式子：
```latex
\prod_{i=1}^n\prod_{j=1}^n \frac{ij}{gcd(i,j)^2}
```
由于是连乘，所以可以分开分子分母考虑

先看分子：


```latex
\prod_{i=1}^n\prod_{j=1}^n ij
=\prod_{i=1}^ni^n\prod_{j=1}^n j
=\prod_{i=1}^ni^nn!
=(n!)^{2n}
```

算个阶乘就完事了

再看分母(以下为了方便只计算分母的算术平方根，最后平方一下就可以了)：
```latex
\prod_{i=1}^n\prod_{j=1}^n gcd(i,j)
```

考虑枚举gcd(i,j)
```latex
=\prod_{k=1}^nk^{\sum_{i=1}^n\sum_{j=1}^n [gcd(i,j)==k]}
```

这就是一个很简单的反演题了，按照套路
```latex
=\prod_{k=1}^nk^{\sum_{i=1}^\frac{n}{k}\sum_{j=1}^\frac{n}{k}[gcd(i,j)==1]}
=\prod_{k=1}^nk^{\sum_{i=1}^\frac{n}{k}\mu(i)\frac{n}{ki}\frac{n}{ki}}
```
按照反演的套路应该把ki拉出去单独枚举做个整除分块

但这题不用。考虑设
```latex
f(x)=\sum_{i=1}^x\mu(i)\frac{x}{i}\frac{x}{i}
```
则原式为
```latex
=\prod_{k=1}^nk^{f(\frac{n}{k})}
```

预处理出莫比乌斯函数前缀和之后，可以对原式做一次整除分块，求f(x)时做一次整除分块，总复杂度O(sqrt(n)*(sqrt(n)+log(n))+n)=O(n)

这里有几个细节:

1.按照费马小定理，求f(x)的时候模数不是104857601，而是104857600，比赛的时候被坑掉了10分

2.本题卡空间，求莫比乌斯函数可以和存前缀和共用一个数组，素数数组可以估计一下个数来开(本人开了80000)，记录是否素数用bool/bitset节约空间
```cpp
#include <stdio.h>
#include <string.h>
typedef long long ll;
const int N=1e6+2,p=104857601;
int ss[80000],mu[N];
int n,i,j,gs,ans=1,k,l;
bool ed[N];
inline int ksm(int x,int y,int p)
{
    int r=1;
    while (y)
    {
        if (y&1) r=(ll)r*x%p;
        x=(ll)x*x%p;
        y>>=1;
    }
    return r;
}
inline int gcd(int x,int y)
{
    if (x==0) return y;
    if (y==0) return x;
    return gcd(y%x,x);
}
inline int f(int n)
{
    int i,j,k,ans=0;
    for (i=1;i<=n;i=j+1)
    {
        j=n/(k=n/i);
        ans=(ans+(ll)k*k%(p-1)*(mu[j]-mu[i-1]))%(p-1);
    }
    if (ans<0) ans+=p-1;
    return ans;
}
int main()
{
    scanf("%d",&n);mu[1]=1;
    for (i=2;i<=n;i++)
    {
        if (!ed[i]) mu[ss[++gs]=i]=-1;
        for (j=1;(j<=gs)&&(i*ss[j]<=n);j++)
        {
            ed[i*ss[j]]=1;
            if (i%ss[j]==0) break;
            mu[i*ss[j]]=-mu[i];
        }
        mu[i]+=mu[i-1];
    }
    for (i=1;i<=n;i=j+1)
    {
        l=1;
        j=n/(n/i);
        for (k=i;k<=j;k++) l=(ll)l*k%p;
        ans=(ll)ans*ksm(l,f(n/i),p)%p;
    }
    l=1;
    for (i=1;i<=n;i++) l=(ll)l*i%p;
    ans=(ll)ksm(l,n<<1,p)*ksm(ans,p-3,p)%p;
    printf("%d",ans);
}
```

---

