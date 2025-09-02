# dkw的lcm

## 题目描述

**特别地，一个数的lcm是自身**

善良的dkw决定直接告诉你题面：
$$\prod_{i_1=1}^n\prod_{i_2=1}^n …\prod_{i_k=1}^n \varphi\big(lcm(i_1,i_2,…,i_k)\big)$$
请你求上述式子，答案对 $10^9+7$ 取模。

其中 $lcm(i_1,i_2,...,i_k)$ 代表这 $k$ 个数的最小公倍数。

其中 $\varphi$ 代表欧拉函数，不知道的可以问度娘。

其中 $\prod$ 代表连乘符号，简单来说就是 $\sum$ 的乘法版。

## 说明/提示

对于 50% 的数据，$1\le n,k\le 8$

对于 100% 的数据，$1\le n,k\le 10^6$

## 样例 #1

### 输入

```
2 2```

### 输出

```
1```

# 题解

## 作者：critnos (赞：9)

*800，但是题解做法很怪。

每个质因数的贡献是独立的，$\varphi$ 也可以直接积性拆掉。对于每个质因数 $p$ 的次数 $q$，贡献显然是 $\varphi(p^q)^{(n-n/p^{q+1})^k-(n-n/p^q)^k}$（容斥），就没了。

上面的东西用欧拉定理计算，显然总的计算次数是 $\sum \log_p n=O(n/\log n)$，时间复杂度算是线性的。

---

## 作者：peterwuyihong (赞：5)

题意：求

$$\prod_{i_1=1}^n\prod_{i_2=1}^n\ldots\prod_{i_k=1}^n\varphi(\text{lcm}(i_1,i_2,\ldots i_k))$$

$1\le n,k\le 10^6$

下面默认 $x/y\leftarrow\lfloor\frac x y\rfloor$。

知道有一个东西是 $\min-\max$ 容斥。

$$\min(S)=\sum_{A\subseteq S}(-1)^{|A|+1}\max(A)$$

$$\max(S)=\sum_{A\subseteq S}(-1)^{|A|+1}\min(A)$$

证明我有个螺旋归纳证法，但我大力推 [cmd](https://www.luogu.com.cn/blog/command-block/min-max-rong-chi-xiao-ji) 的博客。

然后对于所有质数求最小最大值，然后通过积性函数可以得到 $\gcd-\text{lcm}$ 容斥，放到积性函数上也成立，于是

$$LHS=\prod_{i_1=1}^n\prod_{i_2=1}^n\ldots\prod_{i_k=1}^n\prod_{S\in A}\varphi(\gcd(S))^{(-1)^{|S|+1}}$$

记 $A=\{i_1,i_2,\ldots i_k\}$，换而枚举 $S$ 的大小。

$$LHS=\prod_{j=1}^kf(n,j)^{(-1)^{j+1}n^{k-j}\binom k j}$$

$$f(n,k)=\prod_{i_1=1}^n\prod_{i_2=1}^n\ldots\prod_{i_k=1}^n\varphi({\gcd}(i_1,i_2,\ldots i_k))$$

$$=\prod_{d=1}^n\varphi(d)^{\sum_{u=1}^{n/d}\mu(u)(n/du)^k}$$

$$\prod_{T=1}^n(\prod_{d|T}\varphi(d)^{\mu(T/d)})^{(n/T)^k}$$

$$LHS=\prod_{j=1}^n(\prod_{T=1}^n(\prod_{d|T}\varphi(d)^{\mu(T/d)})^{(n/T)^j})^{(-1)^{j+1}n^{k-j}\binom k j}$$

记 $\prod_{d|T}\varphi(d)^{\mu(T/d)}$ 为 $g(T)$。

$$LHS=\prod_{j=1}^k(\prod_{T=1}^ng(T)^{(n/T)^j{(-1)^{j+1}n^{k-j}\binom k j}})$$

$$=\prod_{T=1}^ng(T)^{-\sum_{j=1}^k(-n/T)^j{n^{k-j}\binom k j}}$$

$$=\prod_{T=1}^ng(T)^{-\sum_{j=1}^k(-n/T)^j{n^{k-j}\binom k j}}$$

$$=\prod_{T=1}^ng(T)^{n^k-\sum_{j=0}^k(-n/T)^j{n^{k-j}\binom k j}}$$

$$=\prod_{T=1}^ng(T)^{n^k-(n-n/T)^k}$$

然后就可以做了，把 $n,k$ 看做同一阶，复杂度是 $O(n\log n)$，大概还要乘上一个快速幂。

```cpp
#include<stdio.h>
typedef long long i64;
const int p=1e9+7;
int phi[1000010],g[1000010],v[1000010],mu[1000010];
int pri[1000010],tot;
int n,k;
int ksm(int a,int b,const int P){
  int ans=1;
  for(;b;b>>=1,a=(i64)a*a%P)
  if(b&1)ans=(i64)ans*a%P;
  return ans;
}
void shai(int n){
  phi[1]=mu[1]=1;
  for(int i=2;i<=n;i++){
    if(!v[i])pri[++tot]=i,mu[i]=-1,phi[i]=i-1;
    for(int j=1;j<=tot&&i*pri[j]<=n;j++){
      v[i*pri[j]]=1;
      if(i%pri[j]==0){
        phi[i*pri[j]]=phi[i]*pri[j];
        break;
      }
      mu[i*pri[j]]=-mu[i];
      phi[i*pri[j]]=phi[i]*phi[pri[j]];
    }
  }
  for(int i=0;i<=n;i++)g[i]=1;
  for(int i=1;i<=n;i++)
  if(mu[i]==1)
    for(int j=1;j*i<=n;j++)
    g[i*j]=(i64)g[i*j]*phi[j]%p;
  else if(mu[i]==-1)
    for(int j=1;j*i<=n;j++)
    g[i*j]=(i64)g[i*j]*ksm(phi[j],p-2,p)%p;
  for(int i=2;i<=n;i++)g[i]=(i64)g[i]*g[i-1]%p;
}
int ans=1,t,m;
int min(int a,int b){
  if(a<b)return a;return b;
}
int main(){
  scanf("%d%d",&n,&k);
  shai(n);
  for(int L=1,R;L<=n;L=R+1){
    R=n/(n/L);
    m=ksm(n,k,p-1)-ksm(n-n/L,k,p-1);
    if(m<0)m+=p-1;
    t=ksm((i64)g[R]*ksm(g[L-1],p-2,p)%p,m,p);
    ans=(i64)ans*t%p;
  }
  printf("%d",ans);
}
```

---

## 作者：_Fontainebleau_ (赞：3)

##  题意

- 给定 $n,k$，求
- $$\displaystyle \prod_{i_1=1}^n\prod_{i_2=1}^{n}\cdots\prod_{i_k=1}^n\varphi\left(\operatorname{lcm}\left(i_1,i_2,\ldots,i_k\right)\right)$$
- $1\le{n,k}\le10^6$。答案对 $10^9+7$ 取模。

## 做法

这个 $\operatorname{lcm}$ 不好做，我们想想看怎么搞到熟悉的 $\gcd$ 去。

### min-max 容斥

[我的 min-max 容斥学习笔记。](https://www.luogu.com.cn/blog/181775/min-max-rong-chi-xue-xi-bi-ji-post)

记 $\max\left(U\right)$ 为集合 $U$ 的最大值，$\min\left(U\right)$ 为集合 $U$ 的最小值。那么有：

$$\displaystyle \max\left(S\right)=\sum_{T\subseteq{S},T\neq\varnothing}\left(-1\right)^{\left|T\right|-1}\min\left(T\right)$$

> 证明：我们不妨将 $S$ 中元素以大小为第一关键字，出现位置为第二关键字从大到小排序，记为 $a_i$。
>
>对于每个 $a_i$ 作为最小值产生的贡献：
>- $i=1$，$a_i=\max\left(S\right)$，因为既是最大，又是最小，只会被算 $1$ 次。
>- $i>1$，只有在 $a_i$ 之前的 $a_{1,\ldots,i-1}$ 才有可能出现，那么共 $2^{i-1}$ 种可能，其中长度为奇数和偶数的各半，所以抵消了。（或者说直接爆算：$\displaystyle \sum_{j=1,2\nmid{j}}^{i-1}C_{i-1}^{j-1}-\sum_{j=2,2\mid{j}}^{i-1}C_{i-1}^{j-1}=0(i>1)$，其中 $C_{i-1}^{j-1}$ 表示 $1\sim{i}$ 中钦定选 $i$，且共选 $j$ 个的方案数）。
>
>那么最后就是 $a_1$ 也就是 $\max\left(S\right)$ 了。

对于质因子的次数，进行 min-max 容斥，容易得到：

$$\displaystyle\operatorname{lcm}\left(S\right)=\prod_{T\subseteq{S},T\neq\varnothing}\gcd\left(T\right)^{\left(-1\right)^{\left|T\right|-1}}$$

由于是枚举的是质因子，所以外面套一层积性函数也可以，而 $\varphi$ 正是一个积性函数。

记 $S=\left\{i_1,i_2,\ldots,i_k\right\}$，那么原题就有：

$$\operatorname{LHS}=\prod_{i_1=1}^n\prod_{i_2=1}^n\cdots\prod_{i_k=1}^n\prod_{T\subseteq S,T\neq\varnothing}\varphi\left(\gcd\left(S\right)\right)^{\left(-1\right)^{\left|T\right|-1}}$$

### 推式子

枚举 $l=\left|T\right|$，可得

$$\operatorname{LHS}=\prod_{l=1}^ng\left(n,l\right)^{\left(-1\right)^{l-1}n^{k-l}\binom{k}{j}}$$
$$g\left(n,l\right)=\prod_{i_1=1}^n\prod_{i_2=1}^n\cdots\prod_{i_l=1}^n\varphi\left(\gcd\left(i_1,i_2,\ldots,i_l\right)\right)$$

现在来解释一下，首先是上面的式子，为什么次数那里会有 $n^{k-l}\binom{k}j$ 呢？

因为你想，我们取出来 $l$ 个，剩下 $k-l$ 个不论去什么我都不用管，所以有 $n^{k-l}$，而在 $k$ 个数中选 $l$ 个，所以有 $\binom{k}l$。

对于下面的式子，我们枚举 $d=\gcd\left(i_1,i_2,\ldots,i_l\right)$，则有

$$\begin{aligned}g\left(n,l\right)&=\prod_{d=1}^n\varphi\left(d\right)^{\sum_{t=1}^{\left\lfloor\frac{m}d\right\rfloor}\mu\left(t\right)\left\lfloor\frac{m}{td}\right\rfloor^l}\\&=\prod_{T=1}^n\left(\prod_{d\mid{T}}\varphi\left(d\right)^{\mu\left(\frac{T}d\right)}\right)^{\left\lfloor\frac{n}T\right\rfloor^l}\end{aligned}$$

上面的第一行是一个很简单的莫反，把求和换成了乘法。式子如下：

>$$\begin{aligned}\sum_{i_1=1}^m\sum_{i_2=1}^m\cdots\sum_{i_k=1}^m\left[\gcd\left(i_1,i_2,\ldots,i_k\right)=d\right]&=\sum_{i_1=1}^{\left\lfloor\frac{m}d\right\rfloor}\sum_{i_2=1}^{\left\lfloor\frac{m}d\right\rfloor}\cdots\sum_{i_k=1}^{\left\lfloor\frac{m}d\right\rfloor}\left[\gcd\left(i_1,i_2,\ldots,i_k\right)=1\right]\\&=\sum_{i_1=1}^{\left\lfloor\frac{m}d\right\rfloor}\sum_{i_2=1}^{\left\lfloor\frac{m}d\right\rfloor}\cdots\sum_{i_k=1}^{\left\lfloor\frac{m}d\right\rfloor}\sum_{t\mid\gcd\left(i_1,i_2,\ldots,i_k\right)}\mu\left(d\right)\\&=\sum_{t=1}^{\left\lfloor\frac{m}{d}\right\rfloor}\mu\left(t\right)\sum_{i_1=1}^{\left\lfloor\frac{m}{dt}\right\rfloor}\sum_{i_2=1}^{\left\lfloor\frac{m}{dt}\right\rfloor}\cdots\sum_{i_k=1}^{\left\lfloor\frac{m}{dt}\right\rfloor}1\\&=\sum_{t=1}^{\left\lfloor\frac{m}{d}\right\rfloor}\mu\left(t\right)\left\lfloor\frac{m}{dt}\right\rfloor^k\end{aligned}$$

第二行的话，就是枚举了 $T=td$，再枚举 $d$，消掉了次数上的求和号。

我们令 $\displaystyle h\left(T\right)=\prod_{d\mid{T}}\varphi\left(d\right)^{\mu\left(\frac{T}d\right)}$，这个是可以预处理的。

然后代回原式：

$$\begin{aligned}\operatorname{LHS}&=\prod_{l=1}^n\left(\prod_{T=1}^nh\left(T\right)^{\left\lfloor\frac{n}T\right\rfloor^l}\right)^{\left(-1\right)^{l-1}n^{k-l}\binom{k}l}\\&=\prod_{T=1}^nh\left(T\right)^{-\sum_{l=1}^n\left(-\left\lfloor\frac{n}T\right\rfloor\right)^ln^{k-l}\binom{k}l}\\&=\prod_{T=1}^nh\left(T\right)^{n^k-\sum_{l=0}^n\left(-\left\lfloor\frac{n}T\right\rfloor\right)^ln^{k-l}\binom{k}l}\\&=\prod_{T=1}^nh\left(T\right)^{n^k-\left(n-\left\lfloor\frac{n}T\right\rfloor\right)^k}\end{aligned}$$

最后一步是逆用二项式定理，还是挺神奇的。

## 代码

不知道为什么，跑的好慢 /youl

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,Phi=1e9+6;
int prime[100005],cnt,n,k;
bitset<1000006>used;
int mu[1000006],phi[1000006],kk[1000006],inv[1000006],g[1000006];
inline int f(int x,int y,int mod)
{
	int res=1,p=x;
	while(y)
	{
		if(y&1)	res=1ll*res*p%mod;
		p=1ll*p*p%mod;y>>=1;
	}
	return res;
}
inline void sieve(int n)
{
	kk[0]=phi[1]=mu[1]=kk[1]=inv[1]=1;
	for(int i=2;i<=n;i++)	inv[i]=1ll*inv[mod%i]*(mod-mod/i)%mod;
	for(int i=2;i<=n;i++)
	{
		if(!used[i])	phi[i]=i-1,prime[++cnt]=i,mu[i]=-1,kk[i]=f(i,k,Phi);
		for(int j=1;j<=cnt&&1ll*prime[j]*i<=n;j++)
		{
			used[i*prime[j]]=1,kk[i*prime[j]]=1ll*kk[i]*kk[prime[j]]%Phi;
			if(i%prime[j]==0){phi[i*prime[j]]=phi[i]*prime[j];break;}
			phi[i*prime[j]]=phi[i]*(prime[j]-1),mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<=n;i++)	g[i]=1;
	for(int i=1;i<=n;i++)
		for(int j=i,k=1;j<=n;j+=i,k++)
			if(mu[k])	g[j]=1ll*g[j]*(mu[k]==1?phi[i]:inv[phi[i]])%mod;	
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	n=read(),k=read();
	sieve(1000000);
	int ans=1; 
	for(int i=1;i<=n;i++)	ans=1ll*ans*f(g[i],(kk[n]-kk[n-n/i]+Phi)%Phi,mod)%mod;
	printf("%d\n",ans);
	return 0;
}

```


---

## 作者：qwaszx (赞：2)

一个和其他题解殊途同归的做法.

考虑直接展开欧拉函数，那么所求即

$$
\prod_{1\leq i_t\leq n}\text{lcm}\{i_t\}\prod_{p\in prime}(1-\frac{1}{p})^{[\exists t,p|i_t]}
$$

于是可以把乘积拆开，分为

$$
\prod_{1\leq i_t\leq n}\text{lcm}\{i_t\}
$$

和

$$
\prod_{p\in prime}(1-\frac{1}{p})^{\sum\limits_{1\leq i_t\leq n}[\exists t,p|i_t]}
$$

前面一部分我们来枚举每个质数 $p$ 的次数 $j$，计数有多少种 $\{i_t\}$ 满足其在 $p$ 上的次数的 $\max \geq j$ . 那么容斥一下就是总的减去次数都 $<j$ 的方案数，那么算出单个 $i$ 的方案数再快速幂即可. 对于单个 $i$ 的 次数 $<j$ 的方案数，只需要用 $n$ 减去次数 $\geq j$ 的答案，这个就是 $n-\left\lfloor\dfrac{n}{p^j}\right\rfloor$ .

下面一部分是类似的，对于指数上的求和，我们用总的减去所有 $i_t$ 都不被 $p$ 整除的方案数即可计算.

复杂度只需要考虑质数幂次一共有多少个，对于 $p>\sqrt n$ 的情况显然是 $O(\dfrac{n}{\ln n})$，对于 $p\leq \sqrt n$ 的情况是 $O(\dfrac{\sqrt{n}}{\ln n}\cdot \log n)=O(\sqrt{n})$ ，再乘上快速幂复杂度可以近似看做 $O(n)$.

min25套个分块打表做1e9可能性微存.

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=1000000007;
const int N=1005000;
int inv[N],pw[N],prime[N],p[N],n,K,cnt;
int qpower(int a,int b,int mod)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
    return ans;
}
void make(int n)
{
    inv[1]=1;
    for(int i=2;i<=n;i++)
    {
        inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
        if(!p[i])prime[++cnt]=i,pw[i]=qpower(i,K,mod-1);
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
        {
            int x=i*prime[j];p[x]=1;pw[x]=1ll*pw[i]*pw[prime[j]]%(mod-1);
            if(i%prime[j]==0)break;
        }
    }
}
int qpower(int a,int b)
{
    if(b<0)b+=mod-1;
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
    return ans;
}
int main()
{
//	freopen("data.txt","r",stdin);
    scanf("%d%d",&n,&K);
    make(n);
    int ans=1,i;
    for(i=1;i<=cnt&&1ll*prime[i]*prime[i]<=n;i++)
    {       
        long long mi=0;
        for(int x=prime[i];x<=n;x*=prime[i])
            mi+=pw[n]-pw[n-n/x];
        ans=1ll*ans*qpower(prime[i],mi%(mod-1))%mod;
		ans=1ll*ans*qpower((1-inv[prime[i]]),pw[n]-pw[n-n/prime[i]])%mod;
    }
    for(;i<=cnt;i++)ans=1ll*ans*qpower(prime[i]-1,pw[n]-pw[n-n/prime[i]])%mod;
    cout<<(ans+mod)%mod<<endl;
}
```

---

## 作者：ErkkiErkko (赞：2)

## 分析

一个有些不一样的想法。

考虑从欧拉函数的定义式下手，有：

$$\varphi(lcm(i_1,i_2,...,i_k))=\prod_{p_i \in prime\ and\ \exists x,p_i|i_x} (p_i-1)p_i^{q_{i\ max}-1}$$

其中$q_{i\ max}$表示$i_1 \sim i_k$每一项分解质因数后$p_i$这个质因子最大的指数。这个式子的正确性应该是比较好理解的。

把求积符号后面的那坨东西分成两部分考虑。第一部分，首先考虑对于每个质数$p_i$，$(p_i-1)$会被乘几次，我们发现只要$i_1 \sim i_k$中存在$p_i$的倍数时，就会乘一个$(p_i-1)$。所以我们可以考虑求有多少种$i_1 \sim i_k$的取值方案满足其中存在$p_i$的倍数。我们发现要（yao4）求的方案数$=$总方案数$-i_1 \sim i_k$中不存在$p_i$的倍数的方案数，后者十分易求，为$(n-\lfloor\frac{n}{p_i}\rfloor)^k$。所以这部分对答案的贡献为$\prod (p_i-1)^{n^k-(n-\lfloor\frac{n}{p_i}\rfloor)^k}$。

第二部分的话，我们可以转化一下所求。考虑对于每个$p_i$，从$2$开始枚举$p_i$的指数$q_i$，$p_i^{q_i}$对答案的贡献是$p_i^{cnt_{q_i}}$，$cnt_{q_i}$表示$i_1 \sim i_k$中存在$p_i^{q_i}$的倍数的方案数，其求法与第一部分相似。正确性的话，考虑对于一组$i_1 \sim i_k$的取值方案，$p_i^{q_{i\ max}}$是$p_i^2 \sim p_i^{q_{i\ max}}$的倍数，所以其对答案的贡献为$\prod p_i^{q_{i\ max}-1}$，正确性得证。

时间复杂度的话，不会算，大概是$O(n) \sim O(logn)$之间吧。

指数取模的话，根据扩展欧拉定理（好像用不着），模个$1e9+6$就好了。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <algorithm>
#define rin(i,a,b) for(register int i=(a);i<=(b);i++)
#define rec(i,a,b) for(register int i=(a);i>=(b);i--)
#define trav(i,a) for(register int i=head[(a)];i;i=e[i].nxt)
typedef long long LL;
using std::cin;
using std::cout;
using std::endl;

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN=1000005;
const int MOD=1e9+7;
int n,k,prm[MAXN],cnt;
int ans=1;
bool vis[MAXN];

inline void pre_process(){
	rin(i,2,n){
		if(!vis[i]) prm[++cnt]=i;
		for(int j=1;j<=cnt&&i*prm[j]<=n;j++){
			vis[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

inline int qpow(int x,int y,int mod){
	int ret=1,tt=x%mod;
	while(y){
		if(y&1) ret=1ll*ret*tt%mod;
		tt=1ll*tt*tt%mod;
		y>>=1;
	}
	return ret;
}

int main(){
	n=read(),k=read();
	pre_process();
	int tot=qpow(n,k,MOD-1);
	rin(i,1,cnt){//枚举质数
		int p=prm[i],temp=n/p;
		ans=1ll*ans*qpow(p-1,(tot-qpow(n-temp,k,MOD-1)+MOD-1)%(MOD-1),MOD)%MOD;//第一部分
		while(1){//枚举指数
			temp/=p;if(!temp) break;
			ans=1ll*ans*qpow(p,(tot-qpow(n-temp,k,MOD-1)+MOD-1)%(MOD-1),MOD)%MOD;//第二部分
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：I_AK_IOI_and_NOI (赞：1)

## 具体思路

我们令 $q_{i\ max}$ 表示 $i_1 \sim i_k$ 的 $p_i$ 这个质因子最大的指数。

考虑使用欧拉函数的计算公式化简原式，因为有：

$
lcm(i_1,i_2,...,i_k)=p_1^{q_{1 max}} \times p_2^{q_{2 max}} \times ... \times p_m^{q_{m max}} $

其实就是分解质因数，丢到那个式子里：

$\varphi(lcm(i_1,i_2,...,i_k))=\prod (p_i-1)p_i^{q_{i max}-1}$


容易发现可以分开讨论每个质数，计算每个 $p_i^j$ 在多少种 $i_1 \sim i_k$ 的取值方案中作为某一项的倍数出现，

这里可以容斥做，然后把产生的贡献乘到答案里即可。

质数取模的话，不是有扩展欧拉定理嘛，取模一下就好了。

时间复杂度大概是：$O(n \log n)$。

## 代码实现

鼓励大家思考，只显现部分代码。


```
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
const int MAX_N=1000001,mod=1e9+7;
ll n,k,cnt,ans=1,Prime[MAX_N];
bool isPrime[MAX_N];
ll qiuck_pow(ll a,ll b,ll c) //快速幂模版 
{
    ll res=1;
    while(b)
    {
    	if(b&1) res=(res*a)%c;
    	a=(a*a)%c;  
    	b>>=1;
    }
    return res;
}
ll clac(ll x,ll y)
{
    ll tmp1=qiuck_pow(n-n/x,k,mod-1);
    ll tmp2=qiuck_pow(n-n/y,k,mod-1);
    return (tmp1-tmp2+mod-1)%(mod-1);
}
void GetPrime(int n) //筛到n
{
	memset(isPrime, 1, sizeof(isPrime));
	isPrime[1]=0;
	for(int i=2;i<=n;i++)
	{
		if(isPrime[i])
			Prime[++cnt]=i;
		for(int j=1;j<=cnt && i*Prime[j]<=n;j++) 
		{
			isPrime[i*Prime[j]]=0;
			if(i%Prime[j]==0)
				break;
		}
	}
}
int main()
{
    cin>>n>>k;
	GetPrime(MAX_N);
    for(int i=1;i<=cnt;i++)
    {
    	for(ll st=Prime[i];st<=n;st*=Prime[i])
        {
        	ll tmp1=st-st/Prime[i];
        	ll tmp2=clac(st*Prime[i],st);
        	ll tmp3=qiuck_pow(tmp1,tmp2,mod);
        	ans=1ll*ans*tmp3%mod;
		}
	} 
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：FunnyCreatress (赞：1)

一个有点另类的推柿方法？

$\mathrm{lcm}$ 这个东西看起来不是很好做，但我们都知道 $\gcd$ 是有很多办法做的，所以考虑转化。于是我们搬出 $\mathrm{gcd-lcm}$ 容斥这个科技 (实际上就是 $\min-\max$ 容斥的简单推论)。

就是这个：
$$\mathrm{lcm}\{x|x\in S\}=\prod_{T\subseteq S}\gcd\{x|x\in T\}^{{(-1)^{|T|+1}}}$$

并且可以推广到任意积性函数 $f$：
$$f(\mathrm{lcm}\{x|x\in S\})=\prod_{T\subseteq S}f(\gcd\{x|x\in T\})^{{(-1)^{|T|+1}}}$$

于是开始推柿：
$$\begin{aligned}&\prod_{1\le i_{1..k}\le n}\varphi(\mathrm{lcm}\{i_{1..k}\})\\=&\prod_{1\le i_{1..k}\le n}\prod_S\varphi(\gcd\{i_j|j\in S\})^{(-1)^{|S|+1}}\\=&\prod_{s}\big(\prod_{1\le i_{1..s}\le n}\varphi(\gcd\{i_{1..s}\})\big)^{(-1)^{s+1}\binom ksn^{k-s}}\\=&\prod_s\Big(\prod_d\varphi(d)^{\sum_{i_{1..s}}^{\lfloor\frac nd\rfloor}[\gcd(i_{1..s})=1]}\Big)^{(-1)^{s+1}\binom ksn^{k-s}}\\=&\prod_s\Big(\prod_d\varphi(d)^{\sum_t\mu(t)\lfloor\frac n{dt}\rfloor^s}\Big)^{(-1)^{s+1}\binom ksn^{k-s}}\\=&\prod_s\bigg(\prod_T\Big(\prod_{d|T}\varphi(d)^{\mu(\frac Td)}\Big)^{\lfloor\frac nT\rfloor}\bigg)^{(-1)^{s+1}\binom ksn^{k-s}}\\=&\prod_T\Big(\prod_{d|T}\varphi(d)^{\mu(\frac Td)}\Big)^{n^k-\sum_{s=0}^k\binom ks(-\lfloor\frac nT\rfloor)^sn^{k-s}}\\=&\prod_T\Big(\prod_{d|T}\varphi(d)^{\mu(\frac Td)}\Big)^{n^k-(n-\lfloor\frac nT\rfloor)^k}\end{aligned}$$

直接预处理括号内部分即可。事实上可以整除分块做多组数据。


---

## 作者：bztMinamoto (赞：0)

[传送门](https://www.luogu.org/problemnew/show/P5106)

首先我们发现这是个连乘，而且$\phi$是个积性函数，所以我们可以考虑不同的质因子以及它的不同次数的贡献。简单来说就是把每一次的$\phi(lcm(i_1,i_2,...))$拆成一堆$\phi(p^c)$的乘积

如果枚举到的$k$个数里质因子$p$的最大次数为$c$，那么最终的答案就要乘上一个$\phi(p^c)$。所以我们的目的就是要求出这$k$个数里$p$的最大次数为$c$时的方案数$t$，然后这部分对答案的贡献就是$\phi(p^c)^t$

计算方案的部分可以用容斥解决。设$d_p(i)$表示质因子$p$的最高次数为$i$的总方案数，$s_p(i)$表示质因子$p$的最高次数不超过$i$的总方案数，那么$d_p(i)=s_p(i)-\sum_{j=1}^{i-1}d_p(j)$，边界条件为$d_p(0)=s_p(0)$，前缀和优化一下就能快速计算了

最后是$s_p(i)$怎么计算。我们可以单独考虑每一位的方案数最后$k$位乘起来就好了。先考虑质因子$p$的最高次数刚好为$i$的情况，对于某一位来说，能选的数$j$要满足$j\times p^i\leq n$且$j$不包含$p$这个质因子，那么满足条件的$j$的次数就是$\left\lfloor\frac{n}{p^i}\right\rfloor-\left\lfloor\frac{n}{p^{i+1}}\right\rfloor$，于是前缀和一下就能得到对一个数来说的方案数为$n-\left\lfloor\frac{n}{p^i}\right\rfloor$，那么$s_p(i)=(n-\left\lfloor\frac{n}{p^i}\right\rfloor)^k$

然后注意一个细节，因为上面$s_p$和$d_p$的计算基本都是要炸精度所以要取模，然而因为这两个东西是作为次数出现的，所以根据欧拉定理取模的时候要模$\phi(P)$而不是$P$，因为这个东西调死掉……

然后就没有然后了
```
//minamoto
#include<bits/stdc++.h>
#define R register
#define ll long long
#define inf 0x3f3f3f3f
#define fp(i,a,b) for(R int i=a,I=b+1;i<I;++i)
#define fd(i,a,b) for(R int i=a,I=b-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
using namespace std;
const int N=2e6+5,P=1e9+7,Phi=P-1;
int p[N],vis[N],phi[N],kkk[N];bool flag=0;
int n,k,m,ans;ll sum,t;
inline int add(R int x,R int y,R int P){return x+y>=P?x+y-P:x+y;}
inline int dec(R int x,R int y,R int P){return x-y<0?x-y+P:x-y;}
inline int ksm(R int x,R int y,R int P){
	int res=1;
	for(;y;y>>=1,x=1ll*x*x%P)if(y&1)res=1ll*res*x%P;
	return res;
}
void init(int n){
	phi[1]=kkk[1]=1;
	fp(i,2,n){
		if(!vis[i])p[++m]=i,phi[i]=i-1,kkk[i]=ksm(i,k,Phi);
        //预处理一下phi和所有数的k次幂
		for(R int j=1;j<=m&&1ll*i*p[j]<=n;++j){
			vis[i*p[j]]=1,kkk[i*p[j]]=1ll*kkk[i]*kkk[p[j]]%Phi;
			if(i%p[j]==0){phi[i*p[j]]=phi[i]*p[j];break;}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
}
void solve(int p){
	sum=kkk[n-n/p];
	for(R int i=p;i<=n;(1ll*i*p<=n?i*=p:i=inf)){
		t=dec(kkk[n-n/(1ll*i*p)],sum,Phi);
		ans=1ll*ans*ksm(phi[i],t+Phi,P)%P,
		sum=add(sum,t,Phi);
	}
}
int main(){
//	freopen("testdata.in","r",stdin);
	scanf("%d%d",&n,&k),ans=1,init(n);if(n==1)return puts("1"),0;
	fp(i,1,m)solve(p[i]);return printf("%d\n",ans),0;
}
```

---

## 作者：Owen_codeisking (赞：0)

看到 $memset0$ 的题解，终于懂了一点。但是我觉得他说的有点不清楚，所以特地来补充一下。~~昨天打比赛时全世界都会 $T_3$ 就我不会~~

因为 $n,k\leq 10^6$，猜测应该是一个 $O(n\log n)$ 的算法。我们考虑每个 $\varphi(p^a)$ 对答案的贡献。因为 $\varphi$ 是一个积性函数，所以 $\varphi(ab)=\varphi(a)\cdot \varphi(b)(\gcd(a,b)=1)$

注意：以下分析出现的分数均为答案下取整。

若 $p^a|lcm(i_1,i_2,...,i_k)$ 且 $a$ 是 $p$ 的最高次幂，类似我们定义 $p^{a_j}|i_j$ 且 $a_j$ 是 $p$ 的最高次幂，我们可以得到 $a=\max(a_1,a_2,...,a_k)$，其实算的就是这个 $\max$ 的方案数

在 $1\sim n$ 中，$p^a$ 的倍数有 $\frac{n}{p^a}$ 个。若 $p^a|n$，那么 $p^{a-1}|n$，所以在 $1\sim n$ 中，是 $p^0,p^1,...,p^a$ 的倍数但不是 $p^{a+1}$ 次方的倍数有 $n-\frac{n}{p^{a+1}}$ 个

但是 $\max$ 函数至少含有一个 $a_i=a$，所以我们要排除是 $p^0,p^1,...,p^{a-1}$ 的倍数但不是 $p^{a}$ 次方的倍数有 $n-\frac{n}{p^a}$ 个

此时我们对 $k$ 个数都要满足 $\max$ 函数，所以整个方案数应该有
$(n-\frac{n}{p^{a+1}})^k-(n-\frac{n}{p^a})^k$ 个

那么一个 $p^a$ 对答案的贡献为 $\varphi(p^a)^{(n-\frac{n}{p^{a+1}})^k-(n-\frac{n}{p^a})^k}$，最后枚举每一个 $p$ 和 $a$ 就好了。$p$ 有 $O(\frac{n}{\log n})$ 个，$a$ 有 $\log_p n$ 个，快速幂 $O(\log n)$，时间复杂度 $O(n\log n)$

代码就不贴了，大家看 $memset0$ 的好了。

---

