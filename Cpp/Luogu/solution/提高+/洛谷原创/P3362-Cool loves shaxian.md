# Cool loves shaxian

## 题目背景

Cool 非常非常喜欢吃沙县,确切地说,他非常非常把各种无辜群众拉到沙县去吃饭(╯‵□′)╯(┻━┻。大家都非常非常想知道沙县到底给了 Cool 多少钱带盐沙县小吃,以便未来威逼利诱 Cool 来请客吃隔壁的 KFC。经过多方追踪,大家发现了带盐费发放的某一些规律ヾ(o◕∀◕)ノヾ。


## 题目描述

沙县发放带盐费以壕著称。这家沙县发放带盐费时有个指数 $d$。他会发放 $n$ 轮带盐费，在第 $i$ 轮中，都会发放 $f(i) = \sum_{k|i} k^d (i \leq n)$ 这么多的钱。

现在大家有了 $Q$ 个问题，每个问题都形如 Cool 参加从第 $L_i$ 轮到第 $R_i$ 轮的带盐活动，将能获得多少钱。（保证 $1 \leq L_i \leq R_i \leq n$）

由于开在南大街的沙县小吃不是一般的有钱啊，所以呢，我们要计算的是 Cool 收到的钱对 $10^ 9 + 7$ 取模得到的答案。


## 说明/提示

样例 $1$：

$f(4) = 1^2 + 2^2 + 4^2 = 21$

$f(5) =1^2+5^2= 26$

$f(8) + f(9) + f (10) = 85 + 91 + 130= 306$

样例 $2$：

就相当于在数 $720$ 的因数个数呢~


## 样例 #1

### 输入

```
10 2 2
4 5
8 10```

### 输出

```
47
306```

## 样例 #2

### 输入

```
1000 0 1
720 720```

### 输出

```
30```

# 题解

## 作者：夏色祭 (赞：6)

本题数据范围:n<=1e7 d<=1e18 q<=5e4

## 算法一

先 _O(n log d)_ 预处理出1~n的$d$次方。

然后先枚举一个$i$，再枚举一个$i$的倍数$j$，$f(i*j)$就加上$i$的$d$次方。

在做一个前缀和就行了。

时间复杂度: _O(n log d+n log n+q)_ 预计得分:45

```
//by zykykyk
#include<cstdio>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#define rg register
#define il inline
#define vd void
#define ll long long
#define mod 1000000007
#define maxn 5000010
#define For(i,x,y) for (rg int i=(x);i<=(y);i++)
#define Dow(i,x,y) for (rg int i=(x);i>=(y);i--)
#define cross(i,k) for (rg int i=first[k];i;i=last[i])
using namespace std;
il ll max(ll x,ll y){return x>y?x:y;}
il ll min(ll x,ll y){return x<y?x:y;}
il ll read(){
    ll x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
int n,q,p[maxn],sum[maxn];
ll d;
il int power(int x,ll y){
    int ans=1;
    for (;y;y>>=1,x=1ll*x*x%mod) if (y&1) ans=1ll*ans*x%mod;
    return ans;
}
il vd init(){
    n=read(),d=read(),q=read();
    For(i,1,n) p[i]=power(i,d);
    For(i,1,n)
        For(j,1,n/i) (sum[j*i]+=p[i])%=mod;
    For(i,1,maxn-1) (sum[i]+=sum[i-1])%=mod;
}

int l,r;
il vd work(){
    while (q--){
        l=read(),r=read();
        printf("%d\n",((sum[r]-sum[l-1])%mod+mod)%mod);
    }
}

int main(){
    init(),work();
}
```

## 算法二

我们发现主要复杂度在预处理1~n的$d$次方。

考虑怎么优化。

我们设$q(i)$为$i^d$，不难发现$q(i)$是个完全积性函数。

因此我们可以直接欧拉筛 _O(n)_ 预处理。

接下来同算法一。

时间复杂度: _O(n+n log n+q)_ 预计得分:60

~~这样就可以看AC代码了~~

```
//by zykykyk
#include<cstdio>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#define rg register
#define il inline
#define vd void
#define ll long long
#define mod 1000000007
#define maxn 5000010
#define For(i,x,y) for (rg int i=(x);i<=(y);i++)
#define Dow(i,x,y) for (rg int i=(x);i>=(y);i--)
#define cross(i,k) for (rg int i=first[k];i;i=last[i])
using namespace std;
il ll max(ll x,ll y){return x>y?x:y;}
il ll min(ll x,ll y){return x<y?x:y;}
il ll read(){
    ll x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
int n,tot,q,vis[maxn],P[maxn],p[maxn],sum[maxn];
ll d;
il int power(int x,ll y){
    int ans=1;
    for (;y;y>>=1,x=1ll*x*x%mod) if (y&1) ans=1ll*ans*x%mod;
    return ans;
}
il vd init(){
    n=read(),d=read(),q=read();
    For(i,2,n){
        if (!vis[i]) p[i]=power(i,d),P[++tot]=i;
        for (int j=1;i*P[j]<=n&&j<=tot;j++){
            vis[i*P[j]]=P[j];
            if (i%P[j]==0) break;
        }
    }
    int l=sqrt(n);
    For(i,1,l) p[i]=power(i,d);
    For(i,l+1,n) 
        if (vis[i]) p[i]=1ll*p[vis[i]]*p[i/vis[i]]%mod;
    For(i,1,n)
        For(j,1,n/i) (sum[j*i]+=p[i])%=mod;
    For(i,1,n) (sum[i]+=sum[i-1])%=mod;
    
}

int l,r;
il vd work(){
    while (q--){
        l=read(),r=read();
        printf("%d\n",((sum[r]-sum[l-1])%mod+mod)%mod);
    }
}

int main(){
    init(),work();
}
```

## 算法三

再仔细看可以发现$f(i)$是个积性函数，那么我们就可以欧拉筛 _O(n)_ 预处理出$f(i)$，然后做个前缀和就行了。

$f(i)$分为三种情况:

1.i为素数，$f(i)=i^d$

2.i%p[j]!=0 $f(i*p_j)=f(i)*f(p_j)$

3.i%p[j]==0 这个比较复杂，以下是f老板说的：我们要考虑的是$i*p_j$比$i$多的约数是什么，假设$i*pj$是pj的k次，那多出来的约数都是$pj^k$再乘个数，否则已经被$i$包含了，那只要考虑这些数的贡献就行，也就是$f(i*p_j/p_j^k)*(p_j^k)^d$

时间复杂度: _O(n+q)_ 预计得分:100

```
//by zykykyk
#include<cstdio>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
#define rg register
#define il inline
#define vd void
#define ll long long
#define mod 1000000007
#define maxn 10000010
#define For(i,x,y) for (rg int i=(x);i<=(y);i++)
#define Dow(i,x,y) for (rg int i=(x);i>=(y);i--)
#define cross(i,k) for (rg int i=first[k];i;i=last[i])
using namespace std;
il ll max(ll x,ll y){return x>y?x:y;}
il ll min(ll x,ll y){return x<y?x:y;}
il ll read(){
    ll x=0;int ch=getchar(),f=1;
    while (!isdigit(ch)&&(ch!='-')&&(ch!=EOF)) ch=getchar();
    if (ch=='-'){f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return x*f;
}
int n,tot,q,x,P[maxn],minp[maxn],minpd[maxn],sum[maxn];
bool vis[maxn];
ll d;
il int power(int x,ll y){
    int ans=1;
    for (;y;y>>=1,x=1ll*x*x%mod) if (y&1) ans=1ll*ans*x%mod;
    return ans;
}
il vd init(){
    n=read(),d=read(),q=read();
    sum[1]=1;
    For(i,2,n){
        if (!vis[i]) P[++tot]=minp[i]=i,minpd[i]=sum[i]=power(i,d),sum[i]=(sum[i]+1)%mod;
        for (int j=1;i*P[j]<=n&&j<=tot;j++){
        	int k=i*P[j];
            vis[k]=1;
            if (i%P[j]==0){
            	minp[k]=minp[i]*P[j];
            	minpd[k]=1ll*minpd[i]*minpd[P[j]]%mod;
            	sum[k]=(sum[i]+1ll*minpd[k]*sum[k/minp[k]]%mod)%mod;
            	break;
            }
            else {
                minp[k]=P[j];
                minpd[k]=minpd[P[j]];
                sum[k]=1ll*sum[i]*sum[P[j]]%mod;
            }
        }
    }
    For(i,2,n) (sum[i]+=sum[i-1])%=mod;
}

int l,r;
il vd work(){
    while (q--){
        l=read(),r=read();
        printf("%d\n",((sum[r]-sum[l-1])%mod+mod)%mod);
    }
}

int main(){
    init(),work();
}
```
~~原来此题128MB，丧心病狂~~


---

## 作者：Gaode_Sean (赞：1)

通过观察，不难发现 $f$ 函数是一个积性函数，因此对于 $f(i)$ 和 $i$ 的质因子 $p_j$，我们可以分三种情况讨论：

$1.$ $i$ 为质数，此时 $f_i=i^d$（需要用快速幂来求）

$2.$ $p_j|i$ 时，我们设 $p_j^k|i \times p_j$，$p_j^{k+1}$ 与 $i \times p_j$ 互质，此时 $f(i \times p_j)$ 与 $f(i)$ 相比多出的贡献即与 $p_j^k$ 有关，此时 $f(i \times p_j)=f(\frac{i \times p_j}{p_j^k}) \times (p_j^k)^d$。

$3.$ $i$ 与 $p_j$ 互质时，由积性函数的定义得 $f(i \times p_j)=f(i) \times p_j^d$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e7+1;
typedef long long ll;
const ll mod=1e9+7;
bool v[N];
int tot,n,q;
ll d,pr[N],s[N],p[N],mn[N];
ll power(ll x,ll y)
{
	ll res=1;
	for(;y;y>>=1)
	{
		if(y&1) res=res*x%mod;
		x=x*x%mod;
	}
	return res;
}
void init()
{
	s[1]=mn[1]=p[1]=1;
	for(ll i=2;i<N;i++)
	{
		if(!v[i]) pr[++tot]=i,p[i]=power(i,d),s[i]=p[i]+1,mn[i]=i;
		for(int j=1,nx;j<=tot&&i*pr[j]<N;j++)
		{
			nx=i*pr[j]; v[nx]=true;
			mn[nx]=pr[j],s[nx]=s[i]*s[pr[j]]%mod;
			if(i%pr[j]==0)
			{
				mn[nx]=mn[i]*pr[j];
				if(i==mn[i]) s[nx]=(1+p[pr[j]]*s[i])%mod;
		        else s[nx]=s[i/mn[i]]*s[pr[j]*mn[i]]%mod;
				break;
			}
		}
	}
	for(int i=2;i<N;i++) s[i]=(s[i]+s[i-1])%mod;
}
int main()
{
	scanf("%d%lld%d",&n,&d,&q); init();
	for(int i=1,l,r;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		printf("%lld\n",(s[r]-s[l-1]+mod)%mod);
	}
	return 0;
}
```

---

## 作者：xwh_hh (赞：0)

### [我第一道独立AC的蓝题——P3362](https://www.luogu.com.cn/problem/P3362)题解：  
乍一看，这题似乎挺难（至少我这个小学生认为难），可是，仔细分析，我们很快就能得到一个思路：  
我们令 $p[i]=i^d,i∈[1,n]$ ，可以 $O(n\log_2d)$ 求出。  
然后，用类似埃氏筛的方法，枚举 $i$，再枚举 $i$ 的倍数 $j$，要求 $i,j∈[1,n]$，将 $f(j)$ 加上 $p[i]$ ，全部跑完后即可求出题目所说的 $f(k),k∈[1,n]$。  
时间复杂度：$O(n\log_2d+n\log_2d)$，$60$ 分。  
这个算法的时间复杂度瓶颈在于算 $p[i]$ ，对于 $i$ 来说，如果它是个合数，那么对于$k|i,k≠1,i\,,\,i^d=k^d\times(i/k)^d$。
可以先线性筛，筛出每个数的最小质因子 $s[i]$，线性求出 $p[i]$，时间复杂度变为 $O(n\log_2n)$。  
然后，我们发现，对于 $i=j\times k,\ \gcd(j,k)=1,\ f(i)=f(j)\times f(k)$。  
所以，我们就能$O(n)$ 求出 $f(i)$，来一遍前缀和即可。  
代码如下：
```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
typedef long long ll;
int qpow(ll a,int b){
	ll ans=1;
	a%=mod;
	while(b){
		if(b&1) ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return int(ans);
}
int n,d,q;
ll tmp;
int prime[1000005],len;
int s[10000005];
ll pw[10000005];
ll g[10000005];
int main(){
	cin>>n>>tmp>>q;
	d=tmp%(mod-1);//费马小定理，优化常数 
	for(int i=2;i<=n;i++){
		if(!s[i]) prime[++len]=i;
		for(int j=1;j<=len&&prime[j]*i<=n;j++){
			s[i*prime[j]]=prime[j];
			if(i%prime[j]==0) break;
		}
	}
	pw[1]=1;
	for(int i=1;i<=len;i++)
		pw[prime[i]]=qpow(prime[i],d);
	for(int i=1;i<=n;i++)
		if(s[i]) pw[i]=pw[s[i]]*pw[i/s[i]]%mod;
	g[1]=1;
	for(int i=2;i<=n;i++){
		if(!s[i]) g[i]=(pw[i]+1)%mod;//i是质数 
		else{//i是合数 
			int k=i,cnt=0;
			while(k%s[i]==0){//产生两个互质的数 
				k/=s[i];
				cnt++;
			}
			if(k==1){//质数的多次幂 
				ll now=1;
				for(int j=0;j<=cnt;j++){//暴力 
					g[i]+=now;
					now=now*pw[s[i]]%mod;
					g[i]%=mod;
				}
			}else{//乘一下，搞定 
				int m=i/k;
				g[i]=g[m]*g[i/m]%mod;				
			}
		}
	}
	for(int i=2;i<=n;i++) g[i]=(g[i]+g[i-1])%mod;
	while(q--){
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%lld\n",(g[v]+mod-g[u-1])%mod);//注意，取模时一定要正的 
	}
 	return 0;
}
```

---

## 作者：yizcdl2357 (赞：0)

# 题意
给定 $n,d$。

$q$ 组询问：输入 $l,r\le n$，求：

$$\sum_{i=l}^r \sum_{k|i} k^d$$

$1\le n\le 10^7,1\le d\le 10^{18},1\le q\le 5\times 10^4$。

# 前置知识

前缀和，快速幂，线性筛素数。

# 解法

如果我们可以对于所有 $1\le i\le n$ 求出 $f(i)=\sum_{k|i} k^d$，那只需对 $f$ 数组做一次前缀和就可以得到答案。于是问题变成 $f$ 怎么求。

突破口在于 $f$ 是一个**积性函数**。证明方法很多种，最简单的是利用迪利克雷卷积：

$$f(i)=\sum_{k|i} k^d=\sum_{k|i} k^d\times1^{i/d}=i^d*1$$

对于积性函数求值，我们可以使用**线性筛**。下面我将会介绍如何用线性筛求**任意积性函数**的值。

------------

线性筛前，要知道 $f(1),f(p)$ 的值以及 $f(p^k)$ 和 $f(p^{k-1})$ 的**递推关系**。在本题中：

$f(1)=1$

$f(p)=1^d+p^d=p^d+1$

$\begin{aligned}
f(p^k)&=1+p^d+p^{2d}+\cdots+p^{kd}\\
&=1+p^d(1+p^d+p^{2d}+\cdots+p^{(k-1)d})\\
&=1+p^d\times f(p^{k-1})
\end{aligned}$

线性筛时，维护 $low(i)$ 为 $(i$ 的最小质因子$)$ 的 $($此质因子出现次数$)$ 次方。

即，记 $i=p_1^{a_1}\times p_2^{a_2}\times\cdots\times p_x^{a_x}$，则 $low(i)=p_1^{a_1}$。

------------


让我们回顾一下线性筛素数的过程。枚举一个 $i$ 一个 $p_j$，此时 $p_j$ 是 $i\times p_j$ 的最小质因子。然后分两种情况讨论：一种 $p_j\perp i$，一种 $p_j|i$。

筛积性函数时也要分这两种情况，每种情况中都要构造**一对互质的数**乘起来等于 $i\times p_j$，并利用 $f$ 是**积性函数**这一特性求出 $f(i\times p_j)$ 的值。

------------
第一种情况：$p_j\perp i$。

此时显然有 $f(i\times p_j)=f(i)\times f(p_j)$，$low(i\times p_j)=p_j$（因为 $p_j$ 是 $i\times p_j$ 的最小质因子）。

------------
第二种情况：$p_j|i$。

此时有 $low(i\times p_j)=low(i)\times p_j$（因为 $p_j$ 是 $i\times p_j$ 的最小质因子）。

注意到此时 $p_j$ 是 $i$ 的最小质因子，故 $low(i)$ 是 $p_j$ 的方幂。

因为 $\frac{i}{low(i)}$ 没有质因子 $p_j$，而 $p_j\times low(i)$ 只有质因子 $p_j$，所以它们俩互质。

所以由 $f$ 是积性函数得

$f(i\times p_j)=f(\frac{i}{low(i)})\times f(p_j\times low(i))$

当然，你会想到：**$i=low(i)$ 怎么办？这样不就变成 $f(i\times p_j)=f(1)\times f(i\times p_j)$ 了吗？**

不慌，我们发现 $i=low(i)$ 仅出现在 $i$ 是 $p_j$ 的方幂即质数幂的时候。

套用 $f(p^k)$ 和 $f(p^{k-1})$ 的递推关系，用 $f(i)$ 表示 $f(i\times p_j)$ 即可。

此题中有 $f(i\times p_j)=1+f(i)\times (p_j)^d$，**预处理**每个质数的 $d$ 次方即可。
# 代码
小优化：根据欧拉定理可将 $d$ 对 $10^9+6$ 取模。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
#define N 10000000
#define M 1000000007
using namespace std;
int n,d,q,pn,p[N+1],low[N+1],Pow[N+1],f[N+1];
bool ip[N+1];
inline int P(int x,int y)
{
	if(!y) return 1;
	if(y&1) return x*P(x,y^1)%M;
	int tmp=P(x,y>>1);
	return tmp*tmp%M;
}
inline void sieve(int x)
{
	memset(ip,1,sizeof(ip));
	ip[1]=0,low[1]=Pow[1]=f[1]=1;
	for(int i=2;i<=x;i++)
	{
		if(ip[i]) p[++pn]=i,low[i]=i,Pow[i]=P(i,d),f[i]=Pow[i]+1;
		for(int j=1;j<=pn;j++)
		{
			if(i*p[j]>x) break;
			int _=i*p[j];
			ip[_]=0;
			low[_]=p[j];
			f[_]=f[i]*f[p[j]]%M;
			if(i%p[j]==0)
			{
				low[_]=low[i]*p[j];
				if(i==low[i]) f[_]=(1+Pow[p[j]]*f[i])%M;
				else f[_]=f[i/low[i]]*f[p[j]*low[i]]%M;
				break;
			}
		}
	}
}
signed main()
{
	cin>>n>>d>>q;d%=1000000006;
	sieve(n);
	for(int i=1;i<=n;i++)
	//	cout<<f[i]<<endl,
		f[i]=(f[i]+f[i-1])%M;
	while(q--)
	{
		int l,r;
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",(f[r]-f[l-1]+M)%M);
	}
	return 0;
}
```

---

## 作者：ricky0916 (赞：0)

~~线性筛板子~~

解一：

容易发现$ f(i) $是个积性函数，所以显然可以线性筛。

~~但是由于蒟蒻实在太菜了，开了一堆数组才做出来~~

给一种比较好理解但是空间不小的做法：

首先有一条公式：令
$$n=\prod_{i=1}^k p_i^{a_i}$$
则有
$$ f(n)=\prod_{i=1}^k \sum_{j=0}^{a_i} (p_i^j)^d $$

~~读者自证不难~~

所以若$ n=\prod_{i=1}^k p_i^{a_i},n'=\prod_{i=1}^k p_i^{a_i}\times p_1 $

则有$ f(n')=f(n)+f(\dfrac{n}{p_1^{a_1}})\times (p_1^{a_1+1})^d $

这样就可以记录$ f(n),f(\dfrac{n}{p_1^{a_1}}),p_1^d,(p_1^{a_1})^d $就能线性筛了。

~~更简单的解法请参考其他代码。~~

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
inline long long rd(){
	long long x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
void write(int x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
void we(int x){
	write(x);
	putchar('\n');
}
const int mod=1e9+7;
int prime[1000010],f[10000010],bh[10000010],hh[10000010],hhh[10000010],tot,n,d,q,l,r;
bool check[10000010];
int ksm(int x,int y){
	if(y==0) return 1;
	if(y&1) return 1ll*ksm(1ll*x*x%mod,y>>1)*x%mod;
	return ksm(1ll*x*x%mod,y>>1)%mod;
}
inline void md(int &x){
	if(x>=mod) x-=mod;
}
void init(){
	f[1]=bh[1]=hh[1]=hhh[1]=1;
	for(int i=2;i<=n;i++){
		if(!check[i]){
			prime[tot++]=i;
			bh[i]=1;
			hh[i]=hhh[i]=ksm(i,d);
			f[i]=hh[i]+1;
			md(f[i]);
			
		}
		for(int j=0;j<tot&&i*prime[j]<=n;j++){
			int temp=i*prime[j];
			check[temp]=1;
			if(i%prime[j]==0){
				bh[temp]=bh[i];
				hh[temp]=hh[i];
				hhh[temp]=1ll*hhh[i]*hh[i]%mod;
				f[temp]=f[i]+1ll*bh[i]*hhh[temp]%mod;
				md(f[temp]);
				break;
			}
			bh[temp]=f[i];
			hh[temp]=hh[prime[j]];
			hhh[temp]=hh[temp];
			f[temp]=1ll*f[i]*f[prime[j]]%mod;
		}
	}
	for(int i=1;i<=n;i++){
		f[i]+=f[i-1];
		md(f[i]);
	}
}
int main(){
	n=read();
	d=rd()%(mod-1);
	q=read();
	init();
	while(q--){
		l=read();
		r=read();
		we(((f[r]-f[l-1])%mod+mod)%mod);
	}
	return 0;
}
```
解二：

注意到$ i^d $是个完全积性函数，且$ f(i) $是一个`` Dirichlet ``前缀和的形式，所以我们可以线性筛出$ i^d $，``Dirichlet``前缀和得到$ f(i) $

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
inline long long rd(){
	long long x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x;
}
void write(int x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
void we(int x){
	write(x);
	putchar('\n');
}
const int mod=1e9+7;
int prime[1000010],f[10000010],tot,n,d,q,l,r;
bool check[10000010];
int ksm(int x,int y){
	if(y==0) return 1;
	if(y&1) return 1ll*ksm(1ll*x*x%mod,y>>1)*x%mod;
	return ksm(1ll*x*x%mod,y>>1)%mod;
}
inline void md(int &x){
	if(x>=mod) x-=mod;
}
void init(){
	f[1]=1;
	for(int i=2;i<=n;i++){
		if(!check[i]){
			prime[tot++]=i;
			f[i]=ksm(i,d);
		}
		for(int j=0;j<tot&&i*prime[j]<=n;j++){
			int temp=i*prime[j];
			check[temp]=1;
			f[temp]=1ll*f[i]*f[prime[j]]%mod;
			if(i%prime[j]==0) break;
		}
	}
	for(int i=0;i<tot;i++){
        for(int j=1;prime[i]*j<=n;j++){
            f[prime[i]*j]+=f[j];
            md(f[prime[i]*j]);
        }
    }
    for(int i=1;i<=n;i++){
        f[i]+=f[i-1];
        md(f[i]);
    }
}
int main(){
	n=read();
	d=rd()%(mod-1);
	q=read();
	init();
	while(q--){
		l=read();
		r=read();
		we(((f[r]-f[l-1])%mod+mod)%mod);
	}
	return 0;
}
```
解一复杂度略优。

---

## 作者：Leasier (赞：0)

纯暴力和暴力倍数预处理略。

1. $45 \operatorname{pts}$ 做法

前置芝士：[Dirichlet 前缀和](https://www.luogu.com.cn/blog/comeon123/solution-p5495)

$f$ 函数显然可以用 Dirichlet 前缀和预处理出。

预处理 $f$ 函数和其前缀和即可。时间复杂度为 $O(n \log d + n \ln \ln n + q)$。

代码：
```cpp
#include <stdio.h> // 为了写题解测试部分分

typedef long long ll;

const int N = 1e7 + 7, mod = 1e9 + 7;
int prime[N];
ll f[N], sum[N];
bool p[N];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n, ll d){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i <= n; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= n; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i <= n; i++){
		f[i] = quick_pow(i, d, mod);
	}
	for (register int i = 1; i <= cnt; i++){
		for (register int j = 1; j * prime[i] <= n; j++){
			int t = j * prime[i];
			f[t] = (f[t] + f[j]) % mod;
		}
	}
	for (register int i = 1; i <= n; i++){
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
}

int main(){
	int n, q;
	ll d;
	scanf("%d %lld %d", &n, &d, &q);
	init(n, d);
	for (register int i = 1; i <= q; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%lld\n", ((sum[r] - sum[l - 1]) % mod + mod) % mod);
	}
	return 0;
}
```
2. $60 \operatorname{pts}$ 做法

前置芝士：[欧拉定理（Euler）](https://www.cnblogs.com/yifusuyi/p/9997009.html)

由于 $10^9 + 7$ 为质数，所以我们可以考虑优化求 $k^d$ 的部分。显然，$k^d \equiv k^{d \bmod (10^9 + 6)} \pmod {10^9 + 7}$。

时间复杂度为 $O(n \log \operatorname{mod} + n \ln \ln n + q)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 1e7 + 7, mod = 1e9 + 7;
int prime[N];
ll f[N], sum[N];
bool p[N];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n, ll d){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i <= n; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= n; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i <= n; i++){
		f[i] = quick_pow(i, d, mod);
	}
	for (register int i = 1; i <= cnt; i++){
		for (register int j = 1; j * prime[i] <= n; j++){
			int t = j * prime[i];
			f[t] = (f[t] + f[j]) % mod;
		}
	}
	for (register int i = 1; i <= n; i++){
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
}

int main(){
	int n, q;
	ll d;
	scanf("%d %lld %d", &n, &d, &q);
	init(n, d % (mod - 1));
	for (register int i = 1; i <= q; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%lld\n", ((sum[r] - sum[l - 1]) % mod + mod) % mod);
	}
	return 0;
}
```
3. $100 \operatorname{pts}$ 做法

~~由于我不会线性筛预处理 $f$ 函数，所以~~考虑卡常。

尽可能少用 $\operatorname{long\ long}$，并减少函数传参即可。时间复杂度为 $O(n \log \operatorname{mod} + n \ln \ln n + q)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 1e7 + 7, mod = 1e9 + 7;
int prime[N], f[N], sum[N];
bool p[N];

inline int quick_pow(int x, int p){
	int ans = 1;
	while (p){
		if (p & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(int n, int d){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i <= n; i++){
		if (!p[i]) prime[++cnt] = i;
		for (register int j = 1; j <= cnt && i * prime[j] <= n; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	for (register int i = 1; i <= n; i++){
		f[i] = quick_pow(i, d);
	}
	for (register int i = 1; i <= cnt; i++){
		for (register int j = 1; j * prime[i] <= n; j++){
			f[j * prime[i]] = (f[j * prime[i]] + f[j]) % mod;
		}
	}
	for (register int i = 1; i <= n; i++){
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
}

int main(){
	int n, q;
	ll d;
	scanf("%d %lld %d", &n, &d, &q);
	init(n, d % (mod - 1));
	for (register int i = 1; i <= q; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		printf("%d\n", ((sum[r] - sum[l - 1]) % mod + mod) % mod);
	}
	return 0;
}
```

---

