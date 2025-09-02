# [JRKSJ R6] 牵连的世界

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/jdi9nrec.png)

## 题目描述

给定 $n,m$，求

$$\sum_{i=1}^n \sum_{j=1}^m \sigma_0(ij)\varphi(ij)$$

## 说明/提示

$\sigma_0,\varphi$ 分别为因数个数函数，欧拉函数。

本题可能轻微卡常。

### 数据规模
本题采用捆绑测试。

| $\text{Subtask}$ | $n,m\le$ |  $\text{Score}$ |
| :----------: | :----------: | :----------: |
| $1$ | $10^3$ | $10$ |
| $2$ | $10^5$ |  $30$ |
| $3$ | $2\times 10^5$ | $30$ |
| $4$ | $5\times 10^5$ | $30$ |
| $5$ | $3\times 10^6$ | $1$ |

对于所有数据，$1\le n,m\le 3\times 10^6$。

出于某些原因，你只要得到了 $\ge 100$ 分就可以通过此题。

## 样例 #1

### 输入

```
5 5```

### 输出

```
453```

## 样例 #2

### 输入

```
20 20```

### 输出

```
173825```

# 题解

## 作者：Y_B_X (赞：22)

[原题链接](https://www.luogu.com.cn/problem/P8570)

> 题意：  给定 $n,m\leq 5\times 10^5$，求 $\displaystyle \left(\sum_{i=1}^n\sum_{j=1}^md(ij)\varphi(ij)\right)\bmod 10^9+7$。  

不妨设 $n\leq m$。

$$\sum_{i=1}^n\sum_{j=1}^md(ij)\varphi(ij)$$

$$=\sum_{d=1}^n\sum_{i=1}^n\sum_{j=1}^md(ij)\dfrac{\varphi(i)\varphi(j)}{\varphi(d)}d[\gcd(i,j)=d]$$

$$=\sum_{d=1}^n\dfrac{d}{\varphi(d)}\sum_{i=1}^{n/d}\sum_{j=1}^{m/d}d(ijd^2)\varphi(id)\varphi(jd)\sum_{k|i,k|j}\mu(k)$$

$$=\sum_{T=1}^n\left(\sum_{d|T}\dfrac{d}{\varphi(d)}\mu(T/d)\right)\sum_{i=1}^{n/T}\sum_{j=1}^{m/T}d(ijT^2)\varphi(iT)\varphi(jT)$$

设 $\displaystyle f(T)=\sum_{d|T}\dfrac{d}{\varphi(d)}\mu(T/d)$，然后把后面的因数个数拆开。

$$=\sum_{T=1}^nf(T)\sum_{T|i,1\leq i\leq n}\sum_{T|j,1\leq j\leq m}\varphi(i)\varphi(j)d(ij)$$

$$=\sum_{T=1}^nf(T)\sum_{T|i,1\leq i\leq n}\sum_{T|j,1\leq j\leq m}\varphi(i)\varphi(j)\sum_{a|i}\sum_{b|j}[\gcd(a,b)=1]$$

$$=\sum_{T=1}^nf(T)\sum_{T|i,1\leq i\leq n}\sum_{T|j,1\leq j\leq m}\varphi(i)\varphi(j)\sum_{a|i}\sum_{b|j}\sum_{t|a,t|b}\mu(t)$$

$$=\sum_{T=1}^nf(T)\sum_{T|i,1\leq i\leq n}\sum_{T|j,1\leq j\leq m}\varphi(i)\varphi(j)\sum_{t|i,t|j}\mu(t)d(i/t)d(j/t)$$

由于 $t|i,T|i$ 等价于 $\operatorname{lcm}(t,T)|i$，枚举 $x=\operatorname{lcm}(t,T)$。

$$\sum_{t=1}^n\mu(t)\sum_{t|x,1\leq x\leq n}\left(\sum_{x|i,1\leq i\leq n}\varphi(i)d(i/t)\right)\left(\sum_{x|j,1\leq j\leq m}\varphi(j)d(j/t)\right)\sum_{T=1}^nf(T)[\operatorname{lcm}(t,T)=x]$$

直接枚举 $t$ 及 $t|x$，再枚举 $x|i$ 的复杂度是：

$\sum\limits_{t=1}^n\sum\limits_{i=1}^{n/x}n/(xi)=\sum\limits_{t=1}^nn/x\ln(n/x)=O(n\ln^2 n)$

所以只需对 $t,x$ 快速求出 $\displaystyle \sum_{T=1}^nf(T)[\operatorname{lcm}(t,T)=x]$。

但其实我们只需对 $\mu(t)$ 非零的 $t$ 求值。

再观察一下 $f(T)=\sum\limits_{d|T}\dfrac{d}{\varphi(d)}\mu(T/d)$，这显然是积性的。

而 $f(p^k)=\begin{cases}-1+\dfrac{p}{p-1}=\dfrac{1}{p-1},&k=1\\ \dfrac{p^k}{\varphi(p^k)}-\dfrac{p^{k-1}}{\varphi(p^{k-1})}=0,&k\geq 2\end{cases}$，也即 $f(T)$ 仅在 $\mu(T)$ 非零时有值。

既然 $\mu(t)\neq 0,\mu(T)\neq 0,x=\operatorname{lcm}(t,T)$，则 $\mu(x)\neq0$。

所以我们只需要没有平方因子的 $t,T,x$，求出 $\displaystyle \sum_{T=1}^nf(T)[\operatorname{lcm}(t,T)=x]$。

设 $x,t,T$ 的质因子集合分别为 $P_x,P_t,P_T$，则 $P_t\cup P_T=P_x$ 且条件充要。

所以 $P_T$ 必由 $P_x\setminus P_t$ 的全部元素与 $P_t$ 的一部分拼成。

因此 $\displaystyle \sum_{T=1}^nf(T)[\operatorname{lcm}(t,T)=x]=\left(\prod_{p\in P_x,p\not\in P_t}f(p)\right)\left(\prod_{p\in P_t}\left(f(p)+1\right)\right)$。

最后面的 $+1$ 就相当于 $P_t$ 中的元素可选可不选。

另设积性函数 $g(p)=f(p)+1=\dfrac{p}{p-1},g(n)=\prod\limits_{p|n}\dfrac{p}{p-1}$。

则 $\displaystyle \sum_{T=1}^nf(T)[\operatorname{lcm}(t,T)=x]=f(x/t)g(t)$。

线性预处理出 $f,g,d,\varphi,\mu$，便可 $O(n\ln^2 n)$ 做完了，空间线性。

核心代码：  
```cpp
for(t=1;t<=n;++t)if(mu[t]){
  res=0;
  for(x=t;x<=n;x+=t)if(mu[x]){
    sn=sm=0;
    for(i=x;i<=n;i+=x)add(sn,phi[i]*d[i/t]);
    for(i=x;i<=m;i+=x)add(sm,phi[i]*d[i/t]);
    add(res,1ll*sn*sm%mod*f[x/t]%mod*g[t]%mod);
  }
  add(ans,1ll*res*(mu[t]+mod)%mod);
}
```
[评测记录](https://www.luogu.com.cn/record/88708459)
~~为什么时限不开 100ms~~。

但再仔细观察一下，把每次处理的 $t$ 的倍数拉出来，

我们发现在对于 $t|x$ 的 $x$ 做的事无非是一个整除的后缀和。

因为在 $t|x,t|i$ 时，$x|i\Leftrightarrow \frac{x}{t}|\frac{i}{t}$。

所以这部分能被一个 $\text{Dirichlet}$ 后缀和优化掉。

总时间复杂度降至 $O(n\ln n\ln\ln n)$，虽然在数据范围只有 $5\times 10^5$ 时[没太大区别](https://www.luogu.com.cn/record/88787228)。

核心代码：
```cpp
for(t=1;t<=n;++t)if(mu[t]){
  res=0;
  for(i=t;i<=n;i+=t)sn[i/t]=phi[i]*d[i/t];
  for(j=t;j<=m;j+=t)sm[j/t]=phi[j]*d[j/t];
  for(nn=n/t,k=1;k<=prm&&p[k]<=nn;++k)
    for(l=nn/p[k];l;--l)add(sn[l],sn[l*p[k]]);
  for(nn=m/t,k=1;k<=prm&&p[k]<=nn;++k)
    for(l=nn/p[k];l;--l)add(sm[l],sm[l*p[k]]);
  for(x=t;x<=n;x+=t)if(mu[x])
    add(res,1ll*sn[x/t]*sm[x/t]%mod*f[x/t]%mod*g[t]%mod);
  add(ans,1ll*res*(mu[t]+mod)%mod);
}
```
~~为什么数据范围不加个0~~。

---

## 作者：ButterCake (赞：13)

可能更为简洁的推法。

$$\sum_{i=1}^n \sum_{j=1}^m \sigma(ij)\varphi(ij)$$

$$ =\sum_{i,j,t}\frac{\varphi(i)\varphi(j)t}{\varphi(t)}[\gcd(i,j)=t]\sum_{d|t}\mu(d)\sigma(\frac{i}{d})\sigma(\frac{j}{d})$$

$$ =\sum_{d|t}\frac{\mu(d)t}{\varphi(t)}\sum_{i,j}[\gcd(i,j)=1]\varphi(it)\varphi(jt)\sigma(\frac{it}{d})\sigma(\frac{jt}{d})$$

$$ =\sum_{d,t}\mu(d)(\sum_{g|t}\frac{\mu(\frac{t}{g})gd}{{\varphi(gd)}})(\sum_{t|i}^{n/d}\varphi(id)\sigma(i))(\sum_{t|i}^{m/d}\varphi(id)\sigma(i))$$

是 Dirichlet 前缀差分&后缀和，复杂度 $O(n \log n\log\log n)$

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：10)

其它题解基本上都是直接对于题目的式子进行展开的，这里给出一种对于任意积性函数都可行的做法。膜拜 zak。

首先 $\sigma_0(i)\varphi(i)$ 显然是积性函数，记为 $S(i)$。

## 1. 练手

虽然说是练手，实际上是一个需要先解决的问题。

给定 $A,B,C$，求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n A(i)B(j)C(\gcd(i,j))$。

$$
\begin{array}{rl}
&\sum\limits_{i=1}^n\sum\limits_{j=1}^n A(i)B(j)C(\gcd(i,j))\\
=&\sum\limits_{g=1}C(g)\sum\limits_{i=1}^{\lfloor\frac ng\rfloor}\sum\limits_{j=1}^{\lfloor\frac ng\rfloor}A(ig)B(ig)[\gcd(i,j)=1]\\
=&\sum\limits_{g=1}^n C(g)\sum\limits_{i=1}^{\lfloor\frac ng\rfloor}\sum\limits_{j=1}^{\lfloor\frac ng\rfloor}A(ig)B(ig)\sum\limits_{t|i,t|j}\mu(t)\\
=&\sum\limits_{g=1}^n\sum\limits_{t=1}^{\lfloor\frac ng\rfloor}C(t)\mu(g)(\sum\limits_{i=1}^\frac n{tg} A(itg))(\sum\limits_{j=1}^\frac n{tg} B(jtg))
\end{array}
$$

设 $D=C*\mu$，即 $D(n)=\sum\limits_{d|n}C(d)\mu(\frac nd)$，则答案为

$$\sum\limits_{t=1}^n D(t)(\sum\limits_{i=1}^\frac nt A(it))(\sum\limits_{j=1}^\frac nt B(jt))$$

可以 $O(n\log \log n)$ 计算。

## 2. 回到原问题

枚举 $g=\gcd(i,j)$，则每次需要计算：

$$\sum\limits_{i=1}^\frac ng\sum\limits_{j=1}^\frac mg S(ijg^2)[\gcd(i,j)=1]$$

首先看 $g=1$ 怎么做。

$\gcd(i,j)=1$，所以 $S(ij)=S(i)S(j)$。取 $A=B=S,C_n=[n=1]$，式子就和上面算的式子一样了。

接下来考虑 $g>1$ 的情况。

设 $H(n)=\frac{S(g^2n)}{S(g^2)}$，可以证明 $H$ 是积性函数，而此时有 $S(ijg^2)=H(ij)S(g^2)$，可以转化成和前面类似的形式。

这样，总的时间复杂度就是 $\sum\limits_{g=1}^n \frac ng \log\log n=O(n\log n\log\log n)$。

## 3. 实现

时隔快一年，终于回来填坑了。。。。

其实之前就有不少人问过我如何具体实现，但是因为当时我就一贺式子的，所以完全没仔细想，乱答了一些。

首先可以线性筛求出所有数的最小质因子以及其次数，这样可以遍历 $g$ 的所有质因子来算出 $S(g^2)$。

因为 $H$ 是积性函数，所以只需要求出所有 $p^k$ 处的 $H$ 即可。如果 $p\nmid g$，那么$H(p^k)=S(p^k)$。

这样的话在刚才算 $S(g^2)$ 的时候对于每个 $g$ 的质因子 $p$ 其实可以同时考虑计算所有不超过 $\frac ng$ 的 $p^k$ 处的 $H$。容易发现此时只需要考虑 $p$ 部分对答案的贡献，因为其他质数的贡献都被抵消了。

记 $x=v_p(g)$，那么 $H(p^k)=\dfrac{p^k(k+2x+1)}{2x+1}$，其中 $p^k$ 是来自 $\varphi$ 的部分，$k+2x+1$ 和 $2x+1$ 是来自 $\sigma_0$ 的部分。所以直接枚举所有符合条件的 $k$ 计算 $H$。

于是解决了所有 $p^k$ 处的 $H$，就直接扫一遍，根据前面记录的最小质因子及其次数来将剩余所有位置的 $H$ 都算出来即可。

容易发现每个数总共只算了一次 $H$，而且每次计算都是 $O(1)$ 的，所以这块的复杂度只有 $O(\frac ng)$。而枚举质因数什么的复杂度为 $O(w(g))$，所以对于所有 $g$ 求和之后分别是 $O(n\log n)$ 和 $O(n\log\log n)$，都不是瓶颈。

放一下丑陋的代码，经过少量卡常后只需要跑 1.09s/118.89MB。

```cpp
int n,m;
vector<int>pr;
bool isnp[N];
int mnp[N],pv[N],pk[N],inv[N];// 最小质因数 p，对应次数 k，p^k，逆元
ll s[N];// 上面式子中的 S
int a[N],b[N],c[N],h[N];// 上面式子中的 ABDH
void sieve(int n=N-5){// 线性筛
	s[1]=inv[1]=c[1]=1;
	for(int i=2;i<=n;i++){
		if(!isnp[i])pr.push_back(i),
		s[i]=2*(i-1),pv[i]=1,mnp[i]=pk[i]=i,inv[i]=qpow(i,mod-2),c[i]=mod-1;
		for(auto j:pr)if(i*j>n)break;else{
			isnp[i*j]=1;
			s[i*j]=s[i]*s[j];// 直接把 phi 和 sigma0 一起计算
			pv[i*j]=1;
			mnp[i*j]=pk[i*j]=j;
			inv[i*j]=1ll*inv[i]*inv[j]%mod;
            c[i*j]=mod-c[i];// 因为 C(n)=[n=1]，所以 D=mu，所以这里就提前计算了
			if(i%j==0){
				s[i*j]=s[i]*j/(pv[i]+1)*((pv[i*j]=pv[i]+1)+1);
				pk[i*j]=pk[i]*j;
                c[i*j]=0;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)s[i]%=mod,c[i]%=mod;
	// for(int i=1;i<=25;i++)cerr<<i<<": "<<d[i]<<" "<<phi[i]<<" "<<s[i]<<"\n";
}
inline void Add(int&x,int y){(x+=y)>=mod?x-=mod:0;}
ll calc1(int n){
	for(auto p:pr)if(p>n)break;else for(int i=n/p;i;i--){// 狄利克雷后缀和
		Add(a[i],a[i*p]);
		Add(b[i],b[i*p]);
	}
	ll ans=0;
	for(int i=1;i<=n;i++)if(c[i])(ans+=1ll*c[i]*a[i]%mod*b[i])%=mod;
	return ans;
}
struct nd{ll p,k,pw;};
ll calc2(ll g){
	// cerr<<g<<":\n";
	for(int i=1;i<=n/g;i++)h[i]=0;
	h[1]=1;
	for(int i=1;i<=n/g;i++)if(pk[i]==i)h[i]=s[i];
	ll x=g,Sg=1;
	while(x>1){
		ll p=mnp[x],k=pv[x],pw=pk[x];// 枚举质因数
		(Sg*=(p-1)*(pw*pw%mod*inv[p]%mod)%mod*(k*2+1)%mod)%=mod;// 计算 S(g)
		for(ll i=1,wp=p;wp<=n/g;i++,wp*=p)// 计算对应 H
			h[wp]=wp*(i+2*k+1)%mod*inv[k*2+1]%mod;
		x/=pw;
	}
	for(int i=1;i<=n/g;i++)if(!h[i])h[i]=1ll*h[pk[i]]*h[i/pk[i]]%mod;// 计算其他的 H
	for(int i=1;i<=n/g;i++)a[i]=h[i];
	for(int i=1;i<=m/g;i++)b[i]=h[i];
	for(int i=m/g+1;i<=n/g;i++)b[i]=0;
	ll ans=calc1(n/g);// 直接代入回 ABC 的形式
	// cerr<<ans<<" "<<Sg<<" "<<ans*Sg%mod<<"\n";
	return ans*Sg%mod;
}

void __INIT__(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);}
void __SOLVE__(int _case){
	sieve();
	cin>>n>>m;
	if(n<m)swap(n,m);
	ll ans=0;
	for(int g=1;g<=m;g++)(ans+=calc2(g))%=mod;
	cout<<ans<<"\n";
	//cout<<clock()<<" "<<CLOCKS_PER_SEC<<"\n";
}
```

---

## 作者：littlez_meow (赞：8)

为了防止有人再把颜文字看成 FWT，这次干脆没写。

[题目指路](https://www.luogu.com.cn/problem/P8570)

## step 0：引理

dalao 可跳过本节。

【引理一】 $\sigma_0(ij)=\sum_{x|i}\sum_{y|j}[(x,y)=1]$

证明：考虑等式左右两边的质因子 $p$。

记 $r||s$ 表示 $p^r|s$ 且 $p^{r+1}\nmid s$。

设 $a,b,c,d$ 使得 $a||i,b||j,c||x,d||y$。

等式左边 $p$ 被枚举了 $(a+b+1)$ 次，即 $p^0,p^1,\dots,p^{a+b}$。

等式右边可以分成三类：

1. $c>0,d=0$，此时被枚举了 $a$ 次，即 $p^{0+0},p^{1+0},\dots,p^{a+0}$。

2. $c=0,d>0$，此时被枚举了 $b$ 次，即 $p^{0+0},p^{0+1},\dots,p^{0+b}$。

3. $c=0,d=0$，此时被枚举了 $1$ 次，即 $p^0$。

共被枚举 $(a+b+1)$ 次。

由乘法原理，等式左边 $=$ 等式右边

证毕

【引理二】 $\sigma_0(ij)=\sum_{d|(i,j)}\mu(d)\sigma_0(\frac i d)\sigma_0(\frac j d)$

证明：由引理一，等式左边 $=\sum_{x|i}\sum_{y|j}[(x,y)=1]$

第一次莫反

$=\sum_{x|i}\sum_{y|j}\sum_{d|x,d|y}\mu(d)$

$=\sum_{d|i,d|j}\mu(d)\sum_{xd|i}\sum_{yd|j}1$

替换 $x$ 为 $xd$，$y$ 为 $yd$

$=\sum_{d|(i,j)}\mu(d)(\sum_{x|\frac i d}1)(\sum_{y|\frac j d}1)$

$=\sum_{d|(i,j)}\mu(d)\sigma_0(\frac i d)\sigma_0(\frac j d)=$ 等式右边

证毕

【引理三】 $\varphi(ij)=\dfrac{\varphi(i)\varphi(j)(i,j)}{\varphi((i,j))}$

证明：设 $(i,j)=d$，以下若未说明则 $p$ 为质数。

则等式左边 $=ij\prod_{p|ij}(1-\frac 1 p)$

$=\dfrac{(i\prod_{p|i}(1-\frac 1 p))(j\prod_{p|j}(1-\frac 1 p))}{\prod_{p|(i,j)}(1-\frac 1 p)} $

$=\dfrac{\varphi(i)\varphi(j)}{(i,j)\prod_{p|(i,j)}(1-\frac 1 p)}\times(i,j)$

$=\dfrac{\varphi(i)\varphi(j)(i,j)}{\varphi((i,j))}=$ 等式右边

证毕

## step 2：开始推式子

由对称性，不妨令 $n\le m$

$\sum\limits_{i=1}^n\sum\limits_{j=1}^m\varphi(ij)\sigma_0(ij)$

使用引理二、引理三

$=\sum\limits_{i=1}^n\sum\limits_{j=1}^m\dfrac{\varphi(i)\varphi(j)(i,j)}{\varphi((i,j))}\sum\limits_{r|(i,j)}\mu(r)\sigma_0(\dfrac i r)\sigma_0(\dfrac j r)$

枚举 $(i,j)=k$

$=\sum\limits_{k=1}^n\sum\limits_{i=1}^n\sum\limits_{j=1}^m\dfrac{\varphi(i)\varphi(j)k}{\varphi(k)}[(i,j)=k]\sum\limits_{r|k}\mu(r)\sigma_0(\dfrac i r)\sigma_0(\dfrac j r)$

替换 $i,j$ 为 $ik,jk$

$=\sum\limits_{k=1}^n\dfrac k{\varphi(k)}\sum\limits_{i=1}^{\lfloor \frac n k\rfloor}\sum\limits_{j=1}^{\lfloor \frac m k\rfloor}\varphi(i)\varphi(j)[(i,j)=1]\sum\limits_{r|k}\mu(r)\sigma_0(\dfrac{ik}r)\sigma_0(\dfrac{jk}r)$

第二次莫反

$=\sum\limits_{k=1}^n\dfrac k{\varphi(k)}\sum\limits_{i=1}^{\lfloor \frac n k\rfloor}\sum\limits_{j=1}^{\lfloor \frac m k\rfloor}\varphi(ik)\varphi(jk)\sum\limits_{d|i,d|j}\mu(d)\sum\limits_{r|k}\mu(r)\sigma_0(\dfrac{ik}r)\sigma_0(\dfrac{jk}r)$

枚举约数变为枚举倍数，替换 $i,j$ 为 $id,jd$

$=\sum\limits_{k=1}^n\dfrac k{\varphi(k)}\sum\limits_{d=1}^{\lfloor \frac n k\rfloor}\mu(d)\sum\limits_{i=1}^{\lfloor \frac n{kd}\rfloor}\sum\limits_{j=1}^{\lfloor \frac m{kd}\rfloor}\sum\limits_{r|k}\mu(r)\sigma_0(\dfrac{ikd}r)\sigma_0(\dfrac{jkd}r)\varphi(ikd)\varphi(jkd)$

$=\sum\limits_{k=1}^n\dfrac k{\varphi(k)}\sum\limits_{d=1}^{\lfloor \frac n k\rfloor}\mu(d)\sum\limits_{r|k}\mu(r)[\sum\limits_{i=1}^{\lfloor \frac n{kd}\rfloor}\sigma_0(\dfrac{ikd}r)\varphi(ikd)][\sum\limits_{j=1}^{\lfloor \frac m{kd}\rfloor}\sigma_0(\dfrac{jkd}r)\varphi(jkd)]$

记 $f(a,b,c)=\sum\limits_{i=1}^{\lfloor \frac a b\rfloor}\sigma_0(\dfrac{ib}c)\varphi(ib)$

$=\sum\limits_{k=1}^n\dfrac k{\varphi(k)}\sum\limits_{d=1}^{\lfloor \frac n k\rfloor}\mu(d)\sum\limits_{r|k}\mu(r)f(n,kd,r)f(m,kd,r)$

$=\sum\limits_{r=1}^n\mu(r)r\sum\limits_{k=1}^{\lfloor\frac n r\rfloor}\dfrac k{\varphi(kr)}\sum\limits_{d=1}^{\lfloor \frac n{kr}\rfloor}\mu(d)f(n,krd,r)f(m,krd,r)$

这一步后还可以继续推，比如把 $kd$ 换为 $t$ 等。但是，我们可以来推一下时间复杂度。

先考虑函数 $f$。其有三个变量：第一个变量代入的是 $n,m$ 为常数；第二个变量代入的是 $krd$ 和 $n$ 是同一数量级；第三个变量代入的是 $r$，数量级是调和级数 $O(\frac 1 1+\frac 1 2+\dots+\frac 1 n)=O(\log n)$。此外，计算 $f$ 的时间复杂度也是调和级数。综上，记忆化 $f$ 的时间复杂度为 $O(n\log^2 n)$。

其次，计算式子的时间复杂度：第一层的枚举为 $O(n)$，第二层的枚举是调和级数 $O(\log n)$，第三层也是调和级数 $O(\log n)$。综上，总的时间复杂度为 $O(n\log^2 n)$。

## step 3：细节
很显然，如果单纯记忆化的话，你就会[喜提十分](https://www.luogu.com.cn/record/90769487)。

为什么呢？第一，在函数 $f$ 中分母可以消掉；第二，在循环过程中使用的哈希表记忆化很有可能会被卡掉。既然知道了原因，我们就可以来优化。不如把函数 $f$ 的定义改为 $f(a,b,c)=\sum\limits_{i=1}^{\lfloor \frac a{bc}\rfloor}\sigma_0(ib)\varphi(ibc)$。

原式 $=\sum\limits_{r=1}^n\mu(r)r\sum\limits_{k=1}^{\lfloor\frac n r\rfloor}\dfrac k{\varphi(kr)}\sum\limits_{d=1}^{\lfloor \frac n{kr}\rfloor}\mu(d)f(n,kd,r)f(m,kd,r)$

此外，观察式子，我们先枚举的是 $r$，那么在第一层循环中，我们就只有第二个变量不确定，可以预处理出所有 $f$。

至此，此题完成

## step 4：附上代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for(int i(a);i<=b;++i)
#define R(i,a,b) for(int i(a);i>=b;--i)
#define _ 0
using namespace std;
const int MAXN=5e5,MOD=1e9+7;
int n,m,k,MAX;
short mu[MAXN+1];
int phi[MAXN+1],sigma0[MAXN+1];
int num[MAXN+1];
bool v[MAXN+1];
ll a[MAXN+1],b[MAXN+1];
vector<int>prime;
inline void pre(){
    mu[1]=phi[1]=sigma0[1]=1;
    F(i,2,m){
        if(!v[i]){prime.push_back(i);mu[i]=-1,phi[i]=i-1,sigma0[i]=2,num[i]=1;}
        for(int j:prime){
            ll h=(ll)i*j;
            if(h>m) break;
            v[h]=1;
            if(i%j) mu[h]=-mu[i],phi[h]=phi[i]*phi[j],sigma0[h]=sigma0[i]<<1,num[h]=1;
            else{
            	num[h]=num[i]+1;
            	phi[h]=phi[i]*j,sigma0[h]=sigma0[i]/(num[i]+1)*(num[h]+1);
            	break;	
			}
        }
    }
    return;
}
ll f1[MAXN+1],f2[MAXN+1];
inline int qpow(ll base,int expo){
	ll res(1);
	while(expo){
		if(expo&1) res=res*base%MOD;
		base=base*base%MOD;
		expo>>=1;
	}
	return res;
}
inline ll solve(int x,int y){
    ll res(0);
    F(r,1,x){
    	if(!mu[r]) continue;
    	F(k,1,n/r){
			f1[k]=f2[k]=0;
			F(d,1,x/(r*k)) f1[k]=(f1[k]+(ll)sigma0[k*d]*phi[k*r*d]%MOD)%MOD;
			F(d,1,y/(r*k)) f2[k]=(f2[k]+(ll)sigma0[k*d]*phi[k*r*d]%MOD)%MOD;
		}
    	F(k,1,x/r){
    		int inv=qpow(phi[k*r],MOD-2);
    		F(d,1,x/(r*k)){
    			if(!mu[d]) continue;
    			res=(res+mu[d]*mu[r]*(ll)r*k%MOD*inv%MOD*f1[k*d]%MOD*f2[k*d]%MOD+MOD)%MOD;
			}
		}
	}
    return res;
}
int main(){
    scanf("%d%d",&n,&m);
    if(n>m) n=n^m,m=n^m,n=n^m;
    pre();
    printf("%d",solve(n,m));
    return ~~(0^_^0);//每日卖萌(1/1)
}
```
完结撒花 awa

---

## 作者：Little09 (赞：7)

推式子萌新来推推看式子。

$$\sum_{i=1}^n\sum_{j=1}^m\sigma_0(ij)\varphi(ij)$$

先把 $\sigma_0$ 和 $\varphi$ 展开来。

$$\sum_{i=1}^n\sum_{j=1}^m\dfrac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}\sum_{x|i}\sum_{y|j}[\gcd(x,y)=1]$$

替换 $[\gcd(x,y)]=1$。

$$\sum_{i=1}^n\sum_{j=1}^m\dfrac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}\sum_{x|i}\sum_{y|j}\sum_{d|x,d|y}\mu(d)$$

换个枚举顺序，把 $d$ 的枚举提前。

$$\sum_{i=1}^n\sum_{j=1}^m\dfrac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}\sum_{d|\gcd(i,j)}\sigma_0(\frac{i}{d})\sigma_0(\frac{j}{d})\mu(d)$$

再换个枚举顺序，把 $d$ 的枚举再提前。

$$\sum_{d=1}^n\sum_{i=1}^{n/d}\sum_{j=1}^{m/d}\dfrac{\varphi(id)\varphi(jd)\gcd(i,j)d}{\varphi(\gcd(i,j)d)}\sigma_0(i)\sigma_0(j)\mu(d)$$

枚举 $z=\gcd(i,j)$。

$$\sum_{d=1}^n\mu(d)d\sum_{z=1}^{n/d}\sum_{i=1}^{n/dz}\sum_{j=1}^{m/dz}\dfrac{\varphi(idz)\varphi(jdz)z}{\varphi(zd)}\sigma_0(iz)\sigma_0(jz)[\gcd(i,j)=1]$$

换个顺序。

$$\sum_{d=1}^n\mu(d)d\sum_{z=1}^{n/d}\dfrac{z}{\varphi(zd)}\sum_{i=1}^{n/dz}\sigma_0(iz)\varphi(idz)\sum_{j=1}^{m/dz}\sigma_0(jz)\varphi(jdz)[\gcd(i,j)=1]$$

再替换 $[\gcd(i,j)=1]$。

$$\sum_{d=1}^n\mu(d)d\sum_{z=1}^{n/d}\dfrac{z}{\varphi(zd)}\sum_{i=1}^{n/dz}\sigma_0(iz)\varphi(idz)\sum_{j=1}^{m/dz}\sigma_0(jz)\varphi(jdz)\sum_{w|i,w|j}\mu(w)$$

把 $w$ 放到前面枚举。

$$\sum_{d=1}^n\mu(d)d\sum_{z=1}^{n/d}\dfrac{z}{\varphi(zd)}\sum_{w=1}^{n/dz}\mu(w)\sum_{i=1}^{n/dzw}\sigma_0(iwz)\varphi(iwdz)\sum_{j=1}^{m/dzw}\sigma_0(jwz)\varphi(jwdz)$$

定义两个函数：

$$A(x,y)=\sum_{i=1}^{n/xy}\sigma_0(iy)\varphi(ixy)$$

$$B(x,y)=\sum_{i=1}^{m/xy}\sigma_0(iy)\varphi(ixy)$$

原式可以转化为：

$$\sum_{d=1}^n\mu(d)d\sum_{z=1}^{n/d}\dfrac{z}{\varphi(zd)}\sum_{w=1}^{n/dz}\mu(w)A(d,zw)B(d,zw)$$

首先可以发现：乘积小于等于 $n$ 的三元组个数是 $O(n\log^2 n)$ 级别的。所以我们可以在 $O(n\log ^2 n)$ 的时间复杂度内计算出所有 $A(x,y)$ 和 $B(x,y)$。

如果已经算出了 $A$ 和 $B$，剩下的按照上面的式子算，容易发现也是 $O(n\log^2 n)$ 的。所以我们用 $O(n\log^2 n)$ 完成了这道题。

```cpp
// mu 表示莫比乌斯函数，phi 表示欧拉函数，D 表示约束个数和函数，inv 表示逆元
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	init();
	ll ans=0;
	for (int d=1;d<=n;d++)
	{
		for (int j=1;j<=n/d;j++) 
		{
			a[j]=0;
			for (int i=1;i<=n/(d*j);i++) a[j]=(a[j]+1ll*D[i*j]*phi[i*d*j]%mod)%mod;
			b[j]=0;
			for (int i=1;i<=m/(d*j);i++) b[j]=(b[j]+1ll*D[i*j]*phi[i*d*j]%mod)%mod;
		}
		for (int j=1;j<=n/d;j++) 
		{
			for (int w=1;w<=n/(d*j);w++)
			{
				ans=ans+1ll*mu[d]*mu[w]*inv[phi[j*d]]*d%mod*j%mod*a[j*w]%mod*b[j*w]%mod;
				ans=(ans+mod)%mod;
			}
		}
	}
	cout << ans;
	return 0;
}

```


---

## 作者：KaKa_fairy (赞：5)

狂暴推式子。

不失一般性，我们设 $n\le m$，式子中 $a,b,c$ 为正整数。除号代表下取整除法，而分数线结果为实数。
$$
\begin{aligned}
\sum_{i=1}^n\sum_{j=1}^m\sigma(ij)\varphi(ij)&=\sum_{i=1}^n\sum_{j=1}^m\left(\sum_{x|i}\sum_{y|j}[\gcd(x,y)=1]\right)\left(\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}\right)
\\
&=\sum_{i=1}^n\sum_{j=1}^m\sum_{x|i}\sum_{y|j}\sum_{a|\gcd(x,y)}\mu(a)\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}
\\
&=\sum_{i=1}^n\sum_{j=1}^m\sum_{a|\gcd(i,j)}\sigma(\frac{i}{a})\sigma(\frac{j}{a})\mu(a)\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}
\\
&=\sum_{ab\le n}\sum_{i=1}^{n/ab}\sum_{j=1}^{m/ab}\sigma(ib)\sigma(jb)\mu(a)\frac{\varphi(iab)\varphi(jab)ab}{\varphi(ab)}[\gcd(i,j)=1]
\\
&=\sum_{ab\le n}\sum_{i=1}^{n/ab}\sum_{j=1}^{m/ab}\frac{ab\mu(a)}{\varphi(ab)}\sigma(ib)\varphi(iab)\sigma(jb)\varphi(jab)\sum_{c|\gcd(i,j)}\mu(c)
\\
&=\sum_{ab\le n}\sum_{c=1}^{n/ab}\sum_{i=1}^{n/abc}\sum_{j=1}^{m/abc}\frac{ab\mu(a)\mu(c)}{\varphi(ab)}\sigma(ibc)\varphi(iabc)\sigma(jbc)\varphi(jabc)
\\
&=\sum_{abc\le n}\frac{ab\mu(a)\mu(c)}{\varphi(ab)}
\left(\sum_{i=1}^{n/abc}\sigma(ibc)\varphi(iabc)\right)
\left(\sum_{j=1}^{m/abc}\sigma(jbc)\varphi(jabc)\right)
\end{aligned}
$$

不妨设
$$
S^{(t)}(x,y)=\sum_{i=1}^{t/xy}\sigma(iy)\varphi(ixy)
$$
则原式为
$$
\boxed{
\sum_{abc\le n}\frac{ab\mu(a)\mu(c)}{\varphi(ab)}
S^{(n)}(a,bc)
S^{(m)}(a,bc)
}
$$

而我们有：$abc\le n$ 的有序正整数三元组 $(a,b,c)$ 个数为 $O(n\log^2n)$。因为

$$
\sum_{a=1}^{n}\sum_{b=1}^{n/a}\lfloor\frac{n}{ab}\rfloor
\le\sum_{a=1}^{n}\frac{n}{a}\log \frac{n}{a}
\le\log n\sum_{a=1}^{n}\frac{n}{a}
=n\log^2 n
$$
所以枚举 $a,(b\times c)$ 和 $S^{(t)}$ 中的 $i$（三者乘积 $\le n$ 或 $m$）复杂度为 $O(n\log^2n)$，即我们以这个复杂度处理出所有我们会用到的 $S^{(n)},S^{(m)}$。

然后再 $O(n\log^2n)$ 枚举乘积 $\le n$ 的 $a,b,c$ 即可。

最终复杂度 $O(n\log^2n)$。

```cpp
// #pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
template<int P>
class mod_int{
	using Z=mod_int;
private:
	static int mo(int x){return x<0?x+P:x;}
public:
	int x;
	int val()const{return x;}
	mod_int():x(0){}
	template<class T>mod_int(const T&x_):x(x_>=0&&x_<P?static_cast<int>(x_):mo(static_cast<int>(x_%P))){}
	bool operator==(const Z&rhs)const{return x==rhs.x;}
	bool operator!=(const Z&rhs)const{return x!=rhs.x;}
	Z operator-()const{return Z(x?P-x:0);}
	Z pow(long long k)const{Z res=1,t=*this;while(k){if(k&1)res*=t;if(k>>=1)t*=t;}return res;}
	Z&operator++(){x<P-1?++x:x=0;return *this;}
	Z&operator--(){x?--x:x=P-1;return *this;}
	Z operator++(int){Z ret=x;x<P-1?++x:x=0;return ret;}
	Z operator--(int){Z ret=x;x?--x:x=P-1;return ret;}
	Z inv()const{return pow(P-2);}
	Z&operator+=(const Z&rhs){(x+=rhs.x)>=P&&(x-=P);return *this;}
	Z&operator-=(const Z&rhs){(x-=rhs.x)<0&&(x+=P);return *this;}
	Z&operator*=(const Z&rhs){x=1ULL*x*rhs.x%P;return *this;}
	Z&operator/=(const Z&rhs){return *this*=rhs.inv();}
#define setO(T,o) friend T operator o(const Z&lhs,const Z&rhs){Z res=lhs;return res o##=rhs;}
	setO(Z,+)setO(Z,-)setO(Z,*)setO(Z,/)
#undef setO
};
const int P=1e9+7;
using Z=mod_int<P>;
const int N=500005;
Z d[N],phi[N],mu[N],mp[N],sn[N],sm[N],iv[N];
bool vis[N];
vector<int> p;
void init(int lim){
	d[1]=phi[1]=mu[1]=iv[1]=1;
	For(i,2,lim){
		iv[i]=Z(i).inv();
		if(!vis[i]){
			d[i]=2;
			phi[i]=i-1;
			mu[i]=-1;
			mp[i]=2;
			p.emplace_back(i);
		}
		for(int j:p){
			if(i*j>lim) break;
			vis[i*j]=true;
			if(i%j==0){
				mp[i*j]=mp[i]+1;
				d[i*j]=d[i]/mp[i]*mp[i*j];
				mu[i*j]=0;
				phi[i*j]=phi[i]*j;
				break;
			}else{
				mp[i*j]=2;
				mu[i*j]=-mu[i];
				phi[i*j]=phi[i]*(j-1);
				d[i*j]=d[i]*2;
			}
		}
	}
}
signed main(){ios::sync_with_stdio(false),cin.tie(nullptr);
	int n,m;
	Z ans(0);
	cin>>n>>m;
	if(n>m) swap(n,m);
	init(m);
	For(a,1,n){
		For(bc,1,n/a){
			sn[bc]=sm[bc]=0;
			For(i,1,n/a/bc) sn[bc]+=d[i*bc]*phi[i*a*bc];
			For(i,1,m/a/bc) sm[bc]+=d[i*bc]*phi[i*a*bc];
		}
		For(b,1,n/a){
			For(c,1,n/a/b){
				ans+=Z(a*b)*iv[phi[a*b].val()]*mu[a]*mu[c]*sn[b*c]*sm[b*c];
			}
		}
	}
	cout<<ans.val()<<"\n";
return 0;}
```

---

## 作者：critnos (赞：5)

以防有人不知道 P9157 提出的技巧。搬运过来。

警惕筛子入侵莫反题。

求

$$\sum_{i=1}^n \sum_{j=1}^ m f(ij)$$

其中 $f$ 是素数幂可以快速求出的积性函数。

巨大粗暴的想法是只要能快速求 $F(n,x)=\sum_{i=1}^x f(ni)$ 然后求 $\sum_{i=1}^n F(i,m)$ 就可以了！

考虑逐个去除 $n$ 的质因数的贡献，最后 $n=1$ 的时候直接预处理前缀和就行。取 $n$ 的质因数 $p$ 和其指数 $c$，枚举 $1\dots x$ 中 $p$ 上面的指数，可以发现

$$F(n,x)=\sum_{i\ge 0} f(p^{i+c})( F(n/p^c,\lfloor x/p^c\rfloor )-F(n/p^{c-1},\lfloor x/p^{c+1}\rfloor))$$

取 $p$ 为 $n$ 最大的质因数，直接记忆化递归计算。加上预处理 $nx$ 较小的 $f$ 之后，跑 $5\times 10^5$ 大约需要 700ms。可以通过本题 $5\times 10^5$ 的测试点。

[一份不算很好的实现](https://www.luogu.com.cn/paste/9y6174yo)

---

## 作者：critnos (赞：5)

我感觉还好，但是根据赛前的反馈这题还挺难的，就放到 E 的位置了。

有什么好的解法欢迎交流！！

下面把 $\sigma_0$ 写作 $\sigma$，并令 $n\le m$，$m=\Theta(n)$。

$$\sum_{i=1}^n \sum_{j=1}^m \sigma(ij)\varphi(ij)$$

$$\sum_{i=1}^n \sum_{j=1}^m\sigma(ij)\dfrac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}$$

$$\sum_{d=1}^n \dfrac d {\varphi(d)}\sum_{i=1}^n \sum_{j=1}^m \sigma(ij)\varphi(i)\varphi(j)[\gcd(i,j)=d]$$

$$\sum_{d=1}^n \dfrac d {\varphi(d)}\sum_{i=1}^{n/d} \varphi(id)\sum_{j=1}^{m/d}\varphi(jd) \sigma(ijd^2)[\gcd(i,j)=1]$$

$$\sum_{d=1}^n \dfrac d {\varphi(d)}\sum_{i=1}^{n/d} \varphi(id)\sum_{j=1}^{m/d}\varphi(jd) \sigma(ijd^2)\sum_{x|i,x|j} \mu(x)$$

$$\sum_{d=1}^n \dfrac d {\varphi(d)}\sum_{x=1}^{n/d}\mu(x)\sum_{i=1}^{n/dx} \varphi(idx)\sum_{j=1}^{m/dx}\varphi(jdx) \sigma(ijd^2x^2)$$

令 $t=dx$

$$\sum_{t=1}^n \sum_{d|t} \dfrac d {\varphi(d)} \mu(\dfrac t d )\sum_{i=1}^{n/t}\varphi(it)\sum_{j=1}^{m/t}\varphi(jt)\sigma(ijt^2)$$

令 $f(t)=\sum_{d|t} \frac d {\varphi(d)} \mu(\frac t d )$

$$\sum_{t=1}^n f(t)\sum_{i=1}^{n/t}\varphi(it)\sum_{j=1}^{m/t}\varphi(jt)\sigma(ijt^2)$$

这个柿子相当奇怪。不妨考察后面的部分。

$$\sum_{i=1}^{n/t}\varphi(it)\sum_{j=1}^{m/t}\varphi(jt)\sigma(ijt^2)$$

$$\sum_{i=1}^{n/t}\varphi(it)\sum_{j=1}^{m/t}\varphi(jt)\sum_{x|it}\sum_{y|jt}[\gcd(x,y)=1]$$

$$\sum_{x=1}^{n}\sum_{y=1}^{m}[\gcd(x,y)=1]\sum_{i=1}^{n/x}[t|ix]\varphi(ix)\sum_{j=1}^{m/y}[t|jy]\varphi(jy)$$

$$\sum_{x=1}^{n}\sum_{y=1}^{m}\sum_{d|x,d|y}\mu(d)\sum_{i=1}^{n/x}[t|ix]\varphi(ix)\sum_{j=1}^{m/y}[t|jy]\varphi(jy)$$

$$\sum_{d=1}^{n}\mu(d)\sum_{x=1}^{n/d}\sum_{i=1}^{n/dx}[t|idx]\varphi(idx)\sum_{y=1}^{m/d}\sum_{j=1}^{m/dy}[t|jdy]\varphi(jdy)$$

令 $f_n(x)=\sum_{i=1}^{n/x}[t|ix]\varphi(ix)$

$$\sum_{d=1}^{n}\mu(d)\sum_{x=1}^{n/td}f_n(dx)\sum_{y=1}^{m/td}f_m(dy)$$

令 $g_n(x)=\sum_{i=1}^{n/x}f_n(ix)$

$$\sum_{d=1}^{n}\mu(d)g_n(d)g_m(d)$$

存在多种解法。

## 解法 1

注意到 $f,g$ 可以 $O(n\log \log n)$ 求出。

对于单个 $t$ 可以做到 $O(n\log \log n)$ 的时间复杂度。

考虑根号分治。

对于 $t\le B$，时间复杂度为 $O(Bn\log \log n)$。

对于 $t>B$，使用

$$\sum_{i=1}^{n/t}\varphi(it)\sum_{j=1}^{m/t}\varphi(jt)\sigma(ijt^2)$$

计算。

时间复杂度瓶颈在于计算 $\sigma$。可以固定 $t^2$，枚举 $ij$ 加入其质因子进行计算。时间复杂度 $O(\dfrac {n^2 \log \log n} {i^2})$。总时间复杂度 $O(\dfrac {n^2 \log \log n} B)$。

当 $B=\sqrt n$ 时，算法有时间复杂度 $O(n\sqrt n\log \log n)$。可以轻松跑过 $2\times 10^5$。

## 解法 2

我们猜想每次枚举 $t$ 的倍数的约数的约数时间复杂度不会太高，考虑计算其上界。

$$\sum_{i=1}^n \sum_{j=1}^{n/i} \sum_{x|ij}\sigma(x)$$

令 $d=ij$

$$\sum_{d=1}^n \sigma(d) \sum_{x|d} \sigma(x)$$

$$\sum_{x=1}^n\sigma(x)\sum_{d=1}^{n/x}\sigma(d)$$

$$n\log n\sum_{x=1}^n\dfrac {\sigma(x)} x$$

$$n\log n\sum_{x=1}^n\sum_{k=1}^{n/i} \dfrac 1 {ij}$$

即 $O(n\log^3 n )$。

这样想过是比较吃力的。在计算 $g$ 的时候做高维后缀和就可以保证稳过 $2\times 10^5$ 了。


## 解法 3

上面的解法是有很大浪费的。

不妨考察 $g_{n,k}$ 的值。

令 $l=\text{lcm}(t,k)$

$$\sum_{i=1}^{n/l}\varphi(il)\sigma(\dfrac {il} k)$$

显然这个式子只有 $O(n\log n)$ 个值，$O(n\log^2 n)$ 预处理出来后，就可以直接计算 $g_{n,k}$。有个细节是预处理的数组应该是 $G_{k,l}$ 形式的。方便查询 rank。

显然，$g$ 只有 $O(n\log^2 n)$ 个非 $0$ 项，直接计算即可。

发现瓶颈在于算 $\text{lcm}$。不建议使用常数较大的预处理值域 $\gcd$。注意到所有的项都是 $t$ 的倍数的约数，可以直接在倍数上做质因子上的 dfs。

时间复杂度 $O(n\log^2n)$，可以通过。

---

## 作者：ForgotMe (赞：4)

提供一个简洁的做法。

$$
\sum_{i=1}^n \sum_{j=1}^m \sigma_0(ij)\varphi(ij)
$$

显然有 $\sigma_0(ij)=\sum_{x|i}\sum_{y|j} [\gcd(x,y)=1]$（P3327），$\varphi(ij)=\dfrac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}$。

考虑先对 $\sigma_0(ij)$ 反演，$\sigma_0(ij)=\sum_{d|\gcd(i,j)}\mu(d)\sum_{x|i,d|x}1\sum_{y|j,d|y}1$

可以发现 $\sum_{x|i,d|x}1$ 其实就是 $\sigma_0(\frac{x}{d})$。

于是 $\sigma_0(ij)=\sum_{d|\gcd(i,j)}\mu(d)\sigma_0(\frac{i}{d})\sigma_0(\frac{j}{d})$。

然后代回原式。


$$


\sum_{i=1}^n\sum_{j=1}^m \sum_{d|\gcd(i,j)}\mu(d)\sigma_0(\frac{i}{d})\sigma_0(\frac{j}{d})\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}
$$

$$
\begin{aligned}

&=\sum_{D=1}^n \dfrac{D}{\varphi(D)}\sum_{i=1}^{n/D} \sum_{j=1}^{m/D}\sum_{d|D}\mu(d)\sigma_0(\frac{iD}{d})\sigma_0(\frac{jD}{d})\varphi(iD)\varphi(jD)[\gcd(i,j)=1] \\

&=\sum_{D=1}^n\dfrac{D}{\varphi(D)}\sum_{D_2=1}^{n/D}\mu(D_2)\sum_{i=1}^{n/DD_2}\sum_{j=1}^{n/DD_2}\sum_{d|D}\mu(d)\sigma_0(\frac{iDD_2}{d})\sigma_0(\frac{jDD_2}{d})\varphi(iDD_2)\varphi(jDD_2)\\

&=
\sum_{D=1}^n\dfrac{D}{\varphi(D)}\sum_{D_2=1}^{n/D}\mu(D_2)\sum_{d|D}\mu(d)[\sum_{i=1}^{n/DD_2}\varphi(iDD_2)\sigma_0(\frac{iDD_2}{d})][\sum_{j=1}^{n/DD_2}\sigma_0(\frac{jDD_2}{d})\varphi(jDD_2)]
\end{aligned}
$$


发现这个形式十分好看。

不如记 $f(n,T,D)=\sum_{i=1}^{n/T}\varphi(iT)\sigma_0(\dfrac{iT}{D})$。

那么答案为：

$$
\sum_{D=1}^n\dfrac{D}{\varphi(D)}\sum_{D_2=1}^{n/D}\mu(D_2)\sum_{d|D}\mu(d) f(n,DD_2,d)\times f(m,DD_2,d)
$$

看上去十分离谱，加一点小剪枝（如 $\mu$ 的值不能为 $0$）写一发直接过了。

如果对 $f$ 函数记忆化，那么实际上是 $\mathcal{O}(n\log_2^2n)$ 的。

怎么算的呢，显然 $f$ 函数中 $D|T$。

那么复杂度顶满就是 

$$
\begin{aligned}

\sum_{T=1}^n \sigma_0(T)\lfloor\dfrac{n}{T}\rfloor&=\sum_{d=1}^{n}\sum_{T=1}^{n/d}\lfloor\frac{n}{Td}\rfloor \\

&=\sum_{d=1}^{n}\dfrac{n}{d}\log \dfrac{n}{d} \\

&=n\log_2^2n
\end{aligned}
$$

如果不记忆化的话，似乎是 $\mathcal{O}(n\log_2^3n)$ 的，但是由于有 $\mu$ 的值不能为 $0$ 的限制，跑的非常快，完全不用担心过不了。

---

## 作者：LiuIR (赞：1)

## 题目大意

给定 $n,m$，求

$$
\sum_{i=1}^n\sum_{j=1}^md(ij)\varphi(ij)
$$

对 $10^9+7$ 取模，$n,m\le3\times10^6$。

## 题目解法

先给出两个经典转化式子：

$$
\begin{aligned}
\varphi(ij)&=\frac{\varphi(i)\varphi(j)\gcd(i,j)}{\varphi(\gcd(i,j))}\\
d(ij)&=\sum_{x|i}\sum_{y|j}[\gcd(x,y)=1]
\end{aligned}
$$

然后先拆掉 $\varphi(ij)$

$$
\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^md(ij)\varphi(ij)\\
=&\sum_{d=1}^n\frac{d}{\varphi(d)}\sum_{i=1}^n\sum_{j=1}^md(ij)\varphi(i)\varphi(j)[\gcd(i,j)=d]\\
=&\sum_{d=1}^n\frac{d}{\varphi(d)}\sum_{t=1}^n\mu(t)\sum_{dt|i}\sum_{dt|j}d(ij)\varphi(i)\varphi(j)\\
=&\sum_{T=1}^n\left(\sum_{d|T}\frac{d}{\varphi(d)}\mu(\frac{T}{d})\right)\sum_{T|i}\sum_{T|j}d(ij)\varphi(i)\varphi(j)
\end{aligned}
$$

考虑设 $f(T)=\sum_{d|T}\frac{d}{\varphi(d)}\mu(\frac{T}{d})$，那么问题转变为求出后面的式子。接着考虑拆开 $d(ij)$

$$
\begin{aligned}
&\sum_{T|i}\sum_{T|j}d(ij)\varphi(i)\varphi(j)\\
=&\sum_{T|i}\sum_{T|j}\varphi(i)\varphi(j)\sum_{x|i}\sum_{y|j}[\gcd(i,j)=1]\\
=&\sum_{t=1}^n\mu(t)\sum_{T|i}\sum_{T|j}\varphi(i)\varphi(j)\sum_{t|x,x|i}\sum_{t|y,y|j}1\\
=&\sum_{t=1}^n\mu(t)\sum_{T|i,t|i}\sum_{T|j,t|j}\varphi(i)\varphi(j)d(\frac{i}{t})d(\frac{j}{t})
\end{aligned}
$$

然后再结合起来得到

$$
\begin{aligned}
&\sum_{T=1}^nf(T)\sum_{t=1}^n\mu(t)\sum_{t|i,T|i}\sum_{t|j,T|j}\varphi(i)\varphi(j)d(\frac{i}{t})d(\frac{j}{t})\\
=&\sum_{t=1}^n\mu(t)\sum_{t|k}\left(\sum_{T|k}f(T)\right)\sum_{k|i}\sum_{k|j}\varphi(i)\varphi(j)d(\frac{i}{t})d(\frac{j}{t})[\gcd(i,j)=k]\\
=&\sum_{t=1}^n\mu(t)\sum_{t|k}\left(\sum_{T|k}f(T)\right)\sum_{v}\mu(v)\sum_{vk|i}\sum_{vk|j}\varphi(i)\varphi(j)d(\frac{i}{t})d(\frac{j}{t})\\
\end{aligned}
$$

设 $g(d)=\sum_{T|d}f(T),S_1(d,t)=\sum_{d|i,t|i}\varphi(i)d(\frac{i}{t}),S_2(d,t)=\sum_{d|j,t|i}\varphi(j)d(\frac{j}{t})$，得到

$$
\begin{aligned}
=&\sum_{t=1}^n\mu(t)\sum_{t|k}g(k)\sum_{v}\mu(v)S_1(vk,t)S_2(vk,t)\\
=&\sum_{t=1}^n\mu(t)\sum_{t|k}g(k)\sum_{k|T}S_1(T,t)S_2(T,t)\mu(\frac{T}{k})\\
\end{aligned}
$$

注意到 $S_1,S_2$ 可以做狄利克雷后缀和求出，而最后的 $\sum_{k|T}S_1(T,t)S_2(T,t)\mu(\frac{T}{k})$ 可以最地理可累后缀差分求出。这样时间复杂度就是 $O(n\log n\log\log n)$ 的。

主要代码如下

```c++
for (int t = 1; t <= n; t++)
{
    for (int k = t; k <= n; k += t)
        sum1[k] = phi[k] * d[k / t] % MOD;
    for (int k = t; k <= m; k += t)
        sum2[k] = phi[k] * d[k / t] % MOD;
    for (int j = 1; j <= tot && 1ll * prime[j] * t <= n; j++)
        for (int i = (n / (prime[j] * t)) * t; i >= t; i -= t)
            Add(sum1[i], sum1[i * prime[j]]);
    for (int j = 1; j <= tot && 1ll * prime[j] * t <= m; j++)
        for (int i = (m / (prime[j] * t)) * t; i >= t; i -= t)
            Add(sum2[i], sum2[i * prime[j]]);
    for (int k = t; k <= n; k += t)
        val[k] = sum1[k] * sum2[k] % MOD;
    for (int j = 1; j <= tot && 1ll * prime[j] * t <= n; j++)
        for (int i = t; i * prime[j] <= n; i += t)
            Sub(val[i], val[i * prime[j]]);
    ll res = 0;
    for (int k = t; k <= n; k += t)
        Add(res, g[k] * val[k] % MOD);
    Add(ans, mu[t] * res % MOD);
}
```

---

