# [ABC370G] Divisible by 3

## 题目描述

称正整数 $x$ 是**好的**，当且仅当 $x$ 的约数之和是 $3$ 的倍数。

给定 $n,m$，求有几个长度为 $m$ 的正整数序列，设其积为 $s$，满足 $s\le n$ 且 $s$ 是**好的**，答案对 $998244353$ 取模。

## 说明/提示

$1\le n\le 10^{10},1\le m\le 10^5$。

by @hxy0629

## 样例 #1

### 输入

```
10 1```

### 输出

```
5```

## 样例 #2

### 输入

```
4 2```

### 输出

```
2```

## 样例 #3

### 输入

```
370 907```

### 输出

```
221764640```

## 样例 #4

### 输入

```
10000000000 100000```

### 输出

```
447456146```

# 题解

## 作者：Nightingale_OI (赞：7)

## 大意

对于一个长度为 $m$ 的序列 $A_m$，记 $P(A_m)=\prod\limits_{i=1}^mA_i$。

一个数 $X$ 是好数当且仅当其所有正因数之和是 $3$ 的倍数。

求有多少长度为 $m$ 的正整数序列 $A_m$，使得 $P(A_m)$ 是不大于 $n$ 的好数。

$1\leq n\leq 10^{10},1\leq m\leq 10^5$。

## 思路

假设大家用传统做法通过了 Min_25 筛模板。或者你有优秀的注意力。

文中 $p$ 默认为质数，$p_i$ 表示第 $i$ 个质数，$p_0=0$。$P$ 表示所有质数构成的集合。

$E$ 为不大于 $\sqrt n$ 的质数数。$K$ 为不大于 $n$ 的质数数。$U=\bigg\{\Big\lfloor\dfrac{n}{i}\Big\rfloor\bigg | 1\leq i\leq n \bigg\}$。

设 $n=\prod\limits_{i=1}^Kp_i^{c_i}$；$n$ 所有正因数之和是 $\prod\limits_{i=1}^K\dfrac{p_i^{c_i+1}-1}{p_i-1}$；$P(A_m)=n$ 的序列数为 $\prod\limits_{i=1}^K\binom{m+c_i-1}{c_i}$。

定义积性函数 $g$，其中 $g(p^k)=\binom{m+k-1}{k}$。显然 $g(x)$ 表示有多少 $P(A_m)=x$ 的序列。

定义积性函数 $h$，其中 $h(p^k)=\binom{m+k-1}{k}[\dfrac{p^{k+1}-1}{p-1}\not\equiv 0\pmod 3]$。

当 $x$ 是好数是 $h(x)=0$，否则为 $h(x)=g(x)$，于是答案为 $\sum\limits_{x=1}^ng(x)-\sum\limits_{x=1}^nh(x)$。

---

Min_25 筛，设 $S(n,i)$ 表示 $2$ 到 $n$ 中所有最小质因子大于 $p_i$ 的函数值之和。

设 $G(n,i)=\sum\limits_{j=i+1}^Kg(p_j)$，$H(n,i)=\sum\limits_{j=i+1}^Kh(p_j)$。

$$S_g(n,i)=G(n,i)+\sum\limits_{p_k^c\leq n\land k>i}g(p_k^c)\bigg(S_g\bigg(\bigg\lfloor\frac{n}{p_k^c}\bigg\rfloor,k\bigg)+[c\neq 1]\bigg)$$

$$S_h(n,i)=H(n,i)+\sum\limits_{p_k^c\leq n\land k>i}h(p_k^c)\bigg(S_h\bigg(\bigg\lfloor\frac{n}{p_k^c}\bigg\rfloor,k\bigg)+[c\neq 1]\bigg)$$

最终答案为 $S_g(n,0)-S_h(n,0)$。不妨设 $f(n,r)=\sum\limits_{i=1}^n[i\equiv r\pmod 3][i\in P]$，则有：

$$G(n,i)=m\sum\limits_{t=0}^2\bigg(f(n,t)-f(p_i,t)\bigg)\ ;\ H(n,i)=m\sum\limits_{t=0}^1\bigg(f(n,t)-f(p_i,t)\bigg)$$

我们只要算出所有 $f(x,r)\ (1\leq x\leq\sqrt n\lor x\in U)$ 就可以。$x\leq\sqrt n$ 时直接跑前缀和即可。

我们加一维，$f(n,r,j)=\sum\limits_{i=2}^n[i\equiv r\pmod 3][i\in P\text{ or minp}>p_j]$。

其中 $\text{minp}$ 表示 $i$ 的最小质因子。

$f(n,r,j)$ 的意义是对 $2\sim n$ 做埃筛，筛完第 $j$ 个质数后，剩下的数有多少是模 $3$ 余 $r$ 的。

最终 $f(n,r)=f(n,r,E)$；转移为：

$$f(n,r,j)=f(n,r,j-1)-[n\leq p_j^2]\sum_{u\times p_j\equiv r\pmod 3}f\bigg(\bigg\lfloor\frac{n}{p_j}\bigg\rfloor,u,j-1\bigg)-g(p_{j-1},u)$$

注意到第三维永远是 $j$ 从 $j-1$ 转移，可以滚掉。

时间复杂度就是 Min_25 筛，据说是 $O\bigg(\dfrac{n^{0.75}}{\log n}\bigg)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int N=2e5,mo=998244353;
int jc[N],ny[N];
int ksm(int x,int p=mo-2,int y=1){for(;p;p/=2,x=x*x%mo)if(p&1)y=x*y%mo;return y;}
int C(int n,int m){return (n<m||m<1)?0:jc[n]*ny[m]%mo*ny[n-m]%mo;}
void ycl(int n){
	jc[0]=1;
	f(i,1,n)jc[i]=jc[i-1]*i%mo;
	ny[n]=ksm(jc[n]);
	g(i,n,1)ny[i-1]=ny[i]*i%mo;
}
int p[N],ip[N],b[N][2],c[N][3],g[N][3],w[N],P,E;
#define id(x)(x<=E?b[x][0]:b[n/(x)][1])
void YCL(int n){
	f(i,2,n)ip[i]=1;
	f(i,2,n){
		if(ip[i]){
			p[++P]=i;
			f(t,0,2)c[P][t]=(c[P-1][t]+(i%3==t))%mo;
		}
		f(j,1,P){
			if(i*p[j]>n)break;
			ip[i*p[j]]=0;
			if(i%p[j]==0)break;
		}
	}
}
void clc(int n){
	YCL(E=sqrt(n));
	int t=0,l=1,r,q;
	for(;l<=n;l=r+1){
		q=w[id(n/l)=++t]=n/l;r=(n/q);
		g[t][0]=q/3;g[t][1]=(q-1)/3;g[t][2]=(q+1)/3;
    }
    f(i,1,P)f(j,1,t){
		if(p[i]*p[i]>w[j])break;
		f(u,0,2){
			q=id(w[j]/p[i]);r=u*p[i]%3;
			g[j][r]=(g[j][r]+mo-g[q][u]+c[i-1][u])%mo;
		}
	}
}
int G(int x,int y,int r){int q=id(x);return (g[q][r]+mo-c[y][r])%mo;}
struct Min_25{
	function<int(int,int)>F,G;
	int clac(int n,int i=0){
		if(p[i]>=n)return 0;
		int re=G(n,i);
		f(j,i+1,P){
			int q=p[j],p=q,k=1;if(p*p>n)break;
			for(;q<=n;q*=p,++k)re=(re+F(k,(p*q-1)/(p-1)%3)*(clac(n/q,j)+(k>1)))%mo;
		}
		return re;
	}
};
signed main(){
	cin>>n>>m;clc(n);ycl(m+99);
	Min_25 A;A.F=[&](int k,int t){return C(m+k-1,k);};A.G=[&](int x,int y){return m*(G(x,y,0)+G(x,y,1)+G(x,y,2))%mo;};
	Min_25 B;B.F=[&](int k,int t){return t?C(m+k-1,k):0;};B.G=[&](int x,int y){return m*(G(x,y,0)+G(x,y,1))%mo;};
	return printf("%lld\n",(A.clac(n)+mo-B.clac(n))%mo),0;
}
```

---

## 作者：Limie (赞：5)

其实应该是 min_25 筛板子题，但没开（

题意转化一下就是求 $\sum\limits_{i=1}^n [3\mid \sum\limits_{d\mid i} d] f(i)=\sum_{i=1}^n f(i)-\sum\limits_{i=1}^n [3 \nmid \sum\limits_{d\mid i} d]$。

$f(i)$ 表示将 $i$ 分成 $m$ 个数的积的方法数。

容易观察到 $f(i)$ 是积性函数，$[3 \nmid \sum\limits_{d\mid i} d]$ 也是积性函数，所以两个的点积也是积性函数。

考虑 min_25 筛式子，注意到你只需要求出质数处点值的和即可，相当于你只需要对模三余一和模三余零的质数处的点值即可。

你发现模三余零实际上就是 $3$，于是重点就是区分模三余一和模三余二。

容易注意到 $2 \times 2 \equiv 1 \pmod 3$，若要保证考虑设模三余二处的点值为 $-1$，模三余一处的点值为 $1$，其他为 $0$。

容易发现这是个完全积性函数，前缀和易求，只需将质数处点值加一便可得到贡献。

直接写，发现拿到了目前的最短解+最优解（截至 2024.9.9）（Upd 2024.9.10 最短解被抢了，但是那人马蜂有点过于马蜂了。。）。

#### Code

不要直接贺！！

```cpp
#include<bits/stdc++.h>
namespace Limie{
	#define x first
	#define y second
	#define int long long
	using namespace std;
	typedef long long LL;
	typedef pair<int,int> PII;
	typedef unsigned long long ULL;
	typedef long double LD;
}
using namespace Limie;
const int mod=998244353;
LL n;int m,k,cnt;
int p[100010],s1[100010],s2[100010],t,h[65];
int id1[100010],id2[100010],g1[200010],g2[200010];LL w[200010];
bool st[100010];
inline int id(LL x){return x<=m?id1[x]:id2[n/x];} 
int qmi(int a,int b=mod-2)
{
	int ans=1;
	while(b){
		if(b&1)ans=(LL)ans*a%mod;
		a=(LL)a*a%mod;b>>=1;
	}
	return ans;
}
void get_prime(int x)
{
	for(int i=2;i<=x;i++){
		if(!st[i])p[++t]=i,s1[t]=t,s2[t]=s2[t-1]+(i%3==2?-1:i%3);
		for(int j=1;p[j]*i<=x;j++){
			st[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
inline int S1(LL x,int j)
{
	if(p[j]>x)return 1;
	int ans=0,i;
	for(i=j+1;i<=t&&(LL)p[i]*p[i]<=x;i++)
	for(LL s=p[i],w=1;s<=x;s*=p[i],w++)
	ans=((LL)ans+h[w]*S1(x/s,i))%mod;
	ans=((LL)ans+(LL)k*(g1[id(x)]-s1[i-1])+1)%mod;
	return ans<0?ans+mod:ans;
}
inline int S2(int x,int j)
{
	if(p[j]>x)return 1;
	int ans=0,i;
	for(i=j+1;i<=t&&(LL)p[i]*p[i]<=x;i++)
	for(LL s=p[i],w=1,k=(1+s)%3;s<=x;s*=p[i],k=(k+s)%3,w++)
	if(k)ans=((LL)ans+h[w]*S2(x/s,i))%mod;
	ans=(ans+k*((g1[id(x)]-s1[i-1])+(g2[id(x)]-s2[i-1])+(x>=3)-(p[i-1]>=3))%mod*(mod+1>>1))%mod;
	return (ans%mod+mod+1)%mod;
}
signed main()
{
	int i,j;
	cin>>n>>k,m=sqrt(n);
	get_prime(m);
	h[0]=1;for(i=1;i<=60;i++)h[i]=(LL)h[i-1]*(k+i-1)%mod*qmi(i)%mod;
	LL l=1,r;
	while(l<=n){
		r=n/(n/l);
		w[++cnt]=n/l;
		g1[cnt]=(w[cnt]-1)%mod;
		g2[cnt]=(w[cnt]-1)/3-(w[cnt]+1)/3;
		if(w[cnt]<=m)id1[w[cnt]]=cnt;else id2[n/w[cnt]]=cnt;
		l=r+1; 
	}
	for(i=1;i<=t;i++)for(j=1;(LL)p[i]*p[i]<=w[j];j++)
	g1[j]=((LL)g1[j]-(g1[id(w[j]/p[i])]-s1[i-1]))%mod,
	g2[j]=((LL)g2[j]-(p[i]%3==2?-1:p[i]%3)*(g2[id(w[j]/p[i])]-s2[i-1]))%mod;
	cout<<(S1(n,0)-S2(n,0)+mod)%mod;
}
```

---

## 作者：Kreado (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc370_g)。

## 思路

令 $f(x)$ 表示长度为 $m$ 的正整数序列，其乘积为 $x$ 的方案数，那么答案就是 $\sum_{i=1}^n f(i)[3\mid \sigma_1(i)]$。

$f(x)$ 是好求的，不妨分解质因数 $x=\prod_k p_k^{c_k}$，由于质因子之间的贡献是独立的， 我们可以仅考虑 $p^c$，也就是将 $c$ 个相同的球放进 $m$ 个不同的箱子的方案数（可以为空），插板法即可，总贡献就是每个质因子贡献的乘积，即 $f(x)=\prod_k \binom{k+m-1}{k}$。

构造函数 $g(x)=f(x)[3\nmid \sigma_1(x)]$，答案就是 $\sum_{i=1}^n f(i)-\sum_{i=1}^n g(i)$。

容易发现 $f,g$ 均为积性函数，而且两者在素数处的取值都很好算，直接 [min25 筛](https://www.luogu.com.cn/problem/P5325)即可，时间复杂度 $O\left( \dfrac{n^{3/4}}{\log n} \right)$。

---

## 作者：RiceFruit (赞：3)

设 $f(x)$ 表示积为 $x$ 的序列个数，注意到 $f$ 是一个积性函数，且显然有：$f(p^k)=\binom{m+k-1}{m-1}$，如果这道题没有要求成积为好的，那么直接套上 `Min25` 筛板子即可，考虑如何做积为好的。

一个数的约数之和可以拆到每个质因子上，只要有一个质因子合法那么整个数就是合法的，但这样就不是积性函数了，考虑用总方案减去不合法方案，总方案数已经解决了，定义函数 $g(x)$，当 $x$ 是好的时，$g(x)=0$，否则 $g(x)=f(x)$，这个函数显然也是积性函数，那么套 `Min25` 板子即可。

接下来考虑一下 `Min25` 筛具体的如何实现（此题的实现与模板有一些不同，大佬可以跳过），在求开始的质数点函数值前缀和时，我们定义积性函数 $h(x)=[x\not\equiv 2\pmod 3]$，然后统计这个函数的前缀和，注意到在质数点时 $h(x)\cdot m$ 是等于 $g(x)$，从而这个函数是对的，剩下的部分和模板也大差不差了。

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc370_g)

**题目大意**

> 求有多少长度为 $m$ 的序列元素乘积 $S$ 不超过 $n$，且 $S$ 的因数个数和是 $3$ 的倍数。
>
> 数据范围：$n\le 10^{10},m\le 10^5$。

**思路分析**

假设 $S$ 已知，考虑有多少这样的序列，很显然只需要分配每个质因子的质数到 $m$ 个位置即可。

设答案为 $f(S)$，那么 $f(S)$ 是积性函数且 $f(p^c)=\binom{c+m-1}{m-1}$。

我们要求的就是积性函数 $f(S)$ 在 $[1,n]$ 处的前缀和，注意到 $f(p)=m$，因此可以用 Min25 筛计算。

预处理出 $1\sim \lfloor n/t\rfloor$ 中的质数个数，即可知道 $f(p)$ 在 $\lfloor n/t\rfloor$ 处的质数前缀和。

然后要考虑 $S$ 的因数个数和是 $3$ 的倍数，只要存在 $S$ 的一个质因子 $p^c$ 满足 $3\mid 1+p^1+\cdots+p^c$ 即可。

这并不好维护，但我们可以反面考虑计算因数个数和不是 $3$ 倍数的 $f'(S)$，那么 $f'(p^c)=[3\nmid 1+p^1+\cdots+p^c]f(p^c)$。

还是要处理 $f'(p)$ 在 $\lfloor n/t\rfloor$ 处的质数前缀和，也就是 $1\sim \lfloor n/t\rfloor$ 中有多少 $\bmod 3\ne 2$ 的质数。

直接设 $g(p)=[p\bmod 3\ne 2]$ 的话，构造出的完全积性函数不好维护前缀和。

考虑作差，即计算 $1\sim \lfloor n/t\rfloor$ 中 $\bmod 3=1$ 和 $\bmod 3=2$ 质数个数之差，$\bmod 3= 0$ 的质数显然只有 $3$，容易处理。

那么 $g(p)$ 在 $p\bmod 3= 2$ 的时候为 $-1$，其他时候为 $p\bmod 3$，容易发现构造出完全积性函数后也满足这个规律，维护前缀和是容易的，然后就能带入 Min25 筛的过程求解了。

时间复杂度 $\mathcal O\left(\dfrac{n^{3/4}}{\log n}\right)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353,r[3]={0,1,-1},i2=(MOD+1)/2;
ll ksm(ll a,ll b=MOD-2) { ll s=1; for(;b;a=a*a%MOD,b>>=1) if(b&1) s=s*a%MOD; return s; }
bool isc[MAXN];
int p[MAXN],tot,idx1[MAXN],idx2[MAXN],m;
ll n,q,B,v[MAXN],fp2[MAXN],g1[MAXN],g2[MAXN],h[45];
int id(ll x) { return x<=B?idx1[x]:idx2[n/x]; }
ll S1(ll N,int k) {
	if(p[k]>N) return 0;
	ll s=(g1[id(N)]+MOD-k)%MOD*q%MOD;
	for(int i=k+1;i<=tot&&1ll*p[i]*p[i]<=N;++i) for(ll c=1,w=p[i];w<=N;++c,w*=p[i]) {
		s=(s+h[c]*((c>1)+S1(N/w,i)))%MOD;
	}
	return s;
}
ll S2(ll N,int k) {
	if(p[k]>N) return 0;
	ll s=(g2[id(N)]+MOD-fp2[k])%MOD*q%MOD;
	for(int i=k+1;i<=tot&&1ll*p[i]*p[i]<=N;++i) for(ll c=1,w=p[i];w<=N;++c,w*=p[i]) {
		if((w*p[i]-1)/(p[i]-1)%3) s=(s+h[c]*((c>1)+S2(N/w,i)))%MOD;
	}
	return s;
}
signed main() {
	scanf("%lld%lld",&n,&q),B=sqrt(n);
	for(int i=h[0]=1;i<=40;++i) h[i]=h[i-1]*(q+i-1)%MOD*ksm(i)%MOD;
	for(int i=2;i<=B;++i) {
		if(!isc[i]) p[++tot]=i;
		for(int j=1;j<=tot&&i*p[j]<=B;++j) {
			isc[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
	for(int i=1;i<=tot;++i) fp2[i]=fp2[i-1]+r[p[i]%3];
	for(ll l=1;l<=n;l=n/v[m]+1) {
		v[++m]=n/l;
		if(v[m]<=B) idx1[v[m]]=m;
		else idx2[n/v[m]]=m;
	}
	for(int i=1;i<=m;++i) {
		g1[i]=(v[i]-1)%MOD;
		g2[i]=((v[i]-1)/3+MOD-(v[i]+1)/3)%MOD;
	}
	for(int k=1;k<=tot;++k) for(int i=1;i<=m&&1ll*p[k]*p[k]<=v[i];++i) {
		g1[i]=(g1[i]+(k-1)+MOD-g1[id(v[i]/p[k])])%MOD;
		g2[i]=(g2[i]+MOD+r[p[k]%3]*(fp2[k-1]+MOD-g2[id(v[i]/p[k])]))%MOD;
	}
	for(int i=1;i<=m;++i) g2[i]=(g1[i]+g2[i]+(v[i]>=3))*i2%MOD;
	for(int i=1;i<=tot;++i) fp2[i]=fp2[i-1]+(p[i]%3!=2);
	printf("%lld\n",(S1(n,0)+MOD-S2(n,0))%MOD);
	return 0;
}
```

---

## 作者：qiuzx (赞：1)

由于 $n=\prod p_i^{e_i}$ 的因数之和等于 $\prod(1+p_i+p_i^2+\cdots+p_i^{e_i})$，所以若我们希望 $n$ 的因数之和模 $3$ 余 $0$，就要存在一个 $n$ 的质因子 $p$ 使得 $\sum_{i=0}^e p^i\equiv 0\pmod 3$。存在一个是比较难处理的，所以考虑计算不存在任何一个这样的 $p$ 的序列个数，再用所有可能的序列数减去即可。注意这里所有可能的序列数值得是 $\prod a_i\le n$ 的序列数目，而不是所有长度为 $m$ 的正整数序列数。

如果固定了 $n=\prod p_i^{e_i}$，考虑计算有多少种填 $a_i$ 的方案。容易发现可以看作有一个初始全部为 $1$ 的序列，依次考虑每个质数 $p_i$，可以选择若干个在上面乘上总共 $e_i$ 个 $p_i$，对于一个 $p_i$ 的方案数为 $\binom{m+e_i-1}{e_i}$。而显然所有质数之间相互独立，因此答案就是 $\prod\binom{m+e_i-1}{e_i}$。质数之间相互独立意味着这是一个积性函数，又因为判定 $n$ 是否合法的时候也是对每个质数分别判定，所以这启发我们将原问题转化为一个积性函数求和的问题。

定义积性函数 $f(n)$，其中 $f(p^c)$ 在 $\sum_{i=0}^cp^i\equiv 0\pmod 3$ 时取值为 $0$，否则取值为 $\binom{m+c-1}c$。容易验证 $f(n)$ 表示的就是满足 $\prod a_i=n$ 且 $n$ 的因子之和不是 $3$ 的倍数的序列数目。类似地可以定义积性函数 $g(n)$，其中 $g(p^c)=\binom{m+c-1}c$，此时 $g(n)$ 表示的是满足 $\prod a_i=n$ 的序列数目。则最终的答案就是 $\sum_{i=1}^ng(i)-f(i)$，因此只需要计算 $f,g$ 的前缀和即可。

下面以 $f$ 的前缀和为例，$g$ 比 $f$ 更容易，稍加修改即可求得。由于这个积性函数没有什么特殊性质，所以直接考虑使用 min25 筛。min25 筛的过程分为两个部分，其中一个部分是对所有 $m=\lfloor\frac ni\rfloor$ 求出 $F_{\text{prime}}(m)$，即 $\le m$ 的质数的 $f$ 之和，另一个部分是通过这些 $F_{\text{prime}}(m)$ 来递推求得 $F(n)$。

注意到第二部分的推导不需要积性函数具有任何额外的性质，所以在这里可以直接套用。具体来说，记 $F_k(n)$ 表示最小质因子不小于第 $k$ 个质数的 $n$ 的 $f(n)$ 之和，则答案为 $F_1(n)+f(1)$，而 $F_k(n)$ 可以这样求：
$$
\begin{align}
F_k(n)&=\sum_{i\ge k,p_i^2\le n}\sum_{c\ge 1,p_i^c\le n}f(p_i^c)(F_{i+1}(\lfloor\frac n{p_i^c}\rfloor)+[c>1])+\sum_{k\le i,p_i\le n}f(p_i)\\
&=\sum_{i\ge k,p_i^2\le n}\sum_{c\ge 1,p_i^c\le n}f(p_i^c)(F_{i+1}(\lfloor\frac n{p_i^c}\rfloor)+[c>1])+F_{\text{prime}}(n)-F_{\text{prime}}(p_{k-1})\\
&=\sum_{i\ge k,p_i^2\le n}\sum_{c\ge 1,p_i^{c+1}\le n}(f(p_i^c)F_{i+1}(\lfloor\frac n{p_i^c}\rfloor)+f(p_i^{c+1}))+F_{\text{prime}}(n)-F_{\text{prime}}(p_{k-1})\\
\end{align}
$$
显然只有所有 $\le \sqrt n$ 以及能表示为 $\lfloor\frac ni\rfloor$ 的 $O(\sqrt n)$ 个 $F_{\text{prime}}(n)$ 的值是有用的，假如已经算出了这些值，则可以证明求 $F_1(n)$ 的理论最优复杂度为 $O(\dfrac{n^{3/4}}{\log n})$，但实际应用时一般直接用递推式记忆化搜索，复杂度 $O(n^{1-\epsilon})$，实际效果更好而且更好写。

而求 $F_{\text{prime}}(n)$ 对于一般的积性函数来说，需要 $f(p)$ 是一个关于 $p$ 的低阶多项式才可以快速计算。但在这里 $f(p)=m\times [p\not\equiv 2\pmod 3]$，并不是一个多项式，于是我们需要使用别的方法计算 $F_{\text{prime}}(n)$ 的值。先提取一个 $m$ 出来，则转化为一个类似于质数计数的问题，只需要计算 $\le n$ 的质数中模 $3$ 为 $1,2$ 的分别有多少个即可。考虑一个朴素的埃氏筛，从小到大考虑每个质数（显然只需要考虑到 $\sqrt n$），将最小质因子为它们的数从贡献里面踢掉。则记 $S_k(n,i)$ 表示 $\le n$ 的数中最小质因子 $\ge$ 第 $k$ 个质数的那些数中有多少个 $\equiv i\pmod 3$ 的，那么转移为 $S_k(n,i)=S_{k-1}(n,i)+S_{k-1}(\lfloor\frac n{p_k}\rfloor,i)+S_{k-1}(p_k-1,i)$，其中 $n\ge p_k^2$。另一方面，若 $n<p_k^2$ 则 $S_k(n,i)=S_{k-1}(n,i)$。这样直接暴力做这个转移，显然可能在 $S$ 里出现的 $n$ 就是能被表示为 $\lfloor\frac ni\rfloor$ 的这些数，而我们也恰好需要对所有这样的数算 $S$，因此转移一次 $S$ 即可求出所有的 $F_{\text{prime}}(i)$。可以证明这个转移的复杂度为 $O(\dfrac{n^{3/4}}{\log n})$（只做 $n\ge p_k^2$ 的更新，在原地更新，这样就不用动剩下的部分）。

综上，整个做法的复杂度为 $O(\dfrac{n^{3/4}}{\log n})$。[代码](https://atcoder.jp/contests/abc370/submissions/57544369)

---

