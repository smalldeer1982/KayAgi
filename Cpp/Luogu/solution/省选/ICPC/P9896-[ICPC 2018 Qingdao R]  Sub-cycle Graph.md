# [ICPC 2018 Qingdao R]  Sub-cycle Graph

## 题目描述

对于一个有 $n(n\ge3)$ 个点和 $m$ 条边的无向简单图，其中点的编号为 $1$ 到 $n$。如果加非负整数条边能使这个图是变为 $n$ 个点的简单环，我们称这个是一个 “半环” 图。

给定两个整数 $n$ 和 $m$，你的任务是计算有多少个**不同的** $n$ 个点，$m$ 条边的 “半环” 图。考虑到答案会很大，请将答案模 $10^{9} + 7$ 的结果输出。

定义

- 一个简单图是指一个没有自环和重边的图；
- $n$ 个点的 “简单环” 是指任意一个有 $n$ 个点和 $n$ 条边的无向简单连通图，其中所有点的度均为 $2$；
- 如果两个有着 $n$ 个点和 $m$ 条边的无向简单图是不同的，那么它们具有着不同的边集；
- 现在有两个点 $u$ 和 $v(u < v)$，记 $(u,v)$ 表示连接 $u,v$ 两点的无向边。两条无向边 $(u_1,v_1)$ 和 $(u_2,v_2)$ 如果是不同的，那么 $u_1\ne u_2$ 或 $v_1\ne v_2$。

## 样例 #1

### 输入

```
3
4 2
4 3
5 3```

### 输出

```
15
12
90```

# 题解

## 作者：MadokaKaname (赞：5)

其实是很笨蛋的一个题啦，不知道为什么大家都在 GF，其实压根不用的呢。

需要求的就是链的方案数，考虑把链分成单点和大于等于 2 的链。

我们先枚举不是单点的链的个数，同时也知道了单点链的个数。计算出这样的链长度之和是容易的，所以可以求出有序的链的方案数。然后往这些不是单点的链之间插入单点，得到了标号是 $1$ 到 $n$ 的方案数。

现在考虑有标号。对于每一次枚举，先对之前的方案数乘上一个 $n$ 的阶乘，那么需要考虑的就是去重。考虑对于每一种情况而言，重复的次数正好就是对于所有不是单点的段翻转的方案数乘上所有段重排的方案数，因此乘上这个数即可。

由上得出答案为

$$\sum_{i=1}^{n-m}\dfrac{\binom{n-(x-i)-i-1}{i-1}\binom{x}{i}n!}{2^ix!}$$

其中 $x$ 为链的段数。

柿子中前面两个组合数就是一开始所需要求的方案数，其他的即为后面计算并去重的过程。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
LL n,i,j,k,m,t;
LL val[1000005],invval[1000005];
LL ans[1000005],p2[1000005],invp2[1000005];
const LL mod=1e9+7;
LL qpow(LL x,LL y){
	LL sum=1;
	while(y){
		if(y&1) sum*=x,sum%=mod;
		x*=x,x%=mod;
		y>>=1;
	}
	return sum;
}
LL inv(LL x){
	return qpow(x,mod-2);
}
LL C(LL x,LL y){
	return val[x]*invval[y]%mod*invval[x-y]%mod;
}
int main(){
	val[0]=1,invval[0]=1,p2[0]=1,invp2[0]=1;
	for(i=1;i<=100000;i++)
	  val[i]=val[i-1]*i%mod,invval[i]=inv(val[i]),p2[i]=p2[i-1]*2%mod,invp2[i]=inv(p2[i]);
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&n,&m);
		if(n<m){
			printf("0\n");
			continue;
		}
		if(n==m){
			printf("%lld\n",val[n-1]*inv(2)%mod);
			continue;
		}
		if(m==0){
			printf("1\n");
			continue;
		}
		LL num=n-m,ans=0;
		for(i=1;i<=num;i++){
			LL tmp=num-i;
			ans+=val[n]*C(n-tmp-i-1,i-1)%mod*C(num,i)%mod*invp2[i]%mod*invval[num]%mod,ans%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Petit_Souris (赞：3)

能把 $1+\frac{1}{1-x}$ 当成 $\frac{2-x}{1-x}$ 做然后上下分开展开也真是神人了，有种第一天学 GF 喜欢把式子写的像你的小学数学试卷答案的美感。不过剩下几篇题解统一使用了这个搞笑推法，究竟是什么道理呢？

显然当 $n>m$ 时，问题相当于分成 $n-m$ 条链，$n\le m$ 特殊处理一下即可。

我们可以先求有顺序的方案数，再除掉 $(n-m)!$。

显然可以考虑 EGF，一条长度为 $l$ 的链的方案数为 $\frac{l!}{2}$，注意特判 $l=1$ 时方案数为 $1$。那么 GF 就是 $F(x)=x+\frac{1}{2}x^2+\frac{1}{2}x^3+\dots =\frac{x}{2}(1+\frac{1}{1-x})$，所求即 $[x^n]F(x)^{n-m}$。

三部分分别求幂次即可，$F(x)^{n-m}=\frac{x^{n-m}}{2^{n-m}}\sum\limits_{i=0}^{n-m}\binom{n-m}{i}\frac{1}{(1-x)^i}$。显然我们只关心后面那个求和式的 $[x^m]$ 次系数，对于一个 $i$，$[x^m]\frac{1}{(1-x)^i}$ 显然是 $\binom{m+i-1}{i-1}$，因此可以 $\mathcal O(1)$ 计算一个系数，总复杂度 $\mathcal O(n)$。

---

## 作者：Jerrywang09 (赞：2)

非常基础的组合数学题，考察的知识不超过小学奥数。

观察“半环”的性质，由于 $n$ 的范围可以枚举，因此考虑“半环”有 $x$ 条链。

因此度数为 $1$ 的点 $d_1=2x$。总度数为 $2m$，因此度数为 $2$ 的点 $d_2=\frac {2m-d_1} 2$。剩下的点度数为 $0$。

下面分步计算：

1. 给这三类点选择编号，方案数为 $\binom n {d_1} \binom {n-d_1} {d_2}$。
2. 给度数为 $1$ 的点两两配对组成 $x$ 条链。先选出 $x$ 个点，剩下的 $x$ 个点全排列，注意 $(u,v)$ 与 $(v,u)$ 是同构的，因此方案数为 $\frac {\binom {d_1} x x!} {2^x}$。
3. 度数为 $2$ 的点要划分进这 $x$ 条链内。先全排列，然后就是经典的隔板法。方案数为 $d_2! \binom {d_2+x-1} {x-1}$。

因此答案的计算公式是：
$$
\sum_{x=1}^{\lfloor \frac n 2 \rfloor} \binom n {d_1} \binom {n-d_1} {d_2} \frac {\binom {d_1} x x!} {2^x} d_2! \binom {d_2+x-1} {x-1}
$$

特判一些情况：$m=0$ 时只有一种方案，$m>n$ 时不合法，$m=n$ 时计数环排列个数（旋转、翻转同构），方案数为 $\frac {(n-1)!} 2$。

```cpp
// P9896 [ICPC2018 Qingdao R] Sub-cycle Graph 
#include <cstdio>
#include <iostream>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cerr<<#x<<":"<<x<<endl;
const int N=100010, mod=1e9+7;
using namespace std;
char buf[1<<23], *p1=buf, *p2=buf;
#define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read()
{
    int x=0, f=1; char c=gc();
    while(c<'0' || c>'9') c=='-' && (f=-1), c=gc();
    while('0'<=c && c<='9') x=(x<<3)+(x<<1)+c-'0', c=gc();
    return x*f;
}

int T, n, m; ll res, tmp;
ll fac[N], inv[N], inv2[N], Inv2;
ll qp(ll x, ll y=mod-2)
{
    ll res=1;
    for(; y; y>>=1, x=x*x%mod) if(y&1) res=res*x%mod;
    return res;
}
ll C(int n, int m)
{
    if(n<m) return 0;
    return fac[n]*inv[n-m]%mod*inv[m]%mod;
}
void solve()
{
    n=read(), m=read(); res=-1;
    if(!m) res=1;
    if(m>n) res=0;
    if(m==n) res=fac[n-1]*Inv2%mod;
    if(~res) {printf("%lld\n", res); return;}
    res=0;
    rep(x, 1, n/2)
    {
        int d1=x+x, d2=(m+m-d1)>>1, d3=n-d1-d2;
        tmp=C(n, d1)*C(n-d1, d2)%mod;
        tmp=tmp*C(d1, x)%mod*fac[x]%mod*inv2[x]%mod;
        tmp=tmp*fac[d2]%mod*C(d2+x-1, x-1)%mod;
        res=(res+tmp)%mod;
    }
    printf("%lld\n", res);
}

int main()
{
#ifdef Jerrywang
    freopen("../in.txt", "r", stdin);
#endif
    fac[0]=1; rep(i, 1, N-1) fac[i]=fac[i-1]*i%mod;
    inv[N-1]=qp(fac[N-1]), Inv2=qp(2);
    for(int i=N-1; i; i--) inv[i-1]=inv[i]*i%mod;
    inv2[0]=1; rep(i, 1, N-1) inv2[i]=inv2[i-1]*Inv2%mod;
    T=read(); while(T--) solve();
    return 0;
}
```

---

## 作者：qsn123 (赞：1)

~~非常好组合数学，使我推可爱的大柿子，而不是什么看起来就令人畏惧的生成函数。~~

抢到最优解了，于是考虑写个题解。

考虑一个“半环图”是什么样子的，不难发现其实就是一堆链和单点。于是发现我们可以按照度数把点分类，即度数为 $0,1,2$ 的三类点。注意到度数为 $0$ 的点看起来就很特殊，我们考虑暴力枚举它的个数。

设枚举的 $0$ 度数点个数为 $k$，当前求解的图点数为 $n$，边数为 $m$。我们先假定当前 $0<m<n$ 成立，一步一步推导整个式子。

首先，当然是要从 $n$ 个点中挑选出 $k$ 个度数为 $0$ 的点，答案是：$\begin{pmatrix} n\\ k\\ \end{pmatrix}$。

其次，我们考虑剩余的点。不难发现所有点一定构成 $n-m$ 个连通块，而其中有 $k$ 个单点，剩下的链数则为 $n-m-k$，每条链有两个端点，则度数为 $1$ 的点数为 $2 \times (n-m-k)$，度数为 $2$ 的点个数为 $2 \times m+k-n$，于是我们要在剩余的点中挑选出度数为 $1$ 的点，答案是 $\begin{pmatrix} n-k\\ 2 \times (n-m-k)\\ \end{pmatrix}$。

接下来，考虑将这些度数为 $1$ 的点两两配对形成链的两端。我们想到规定每条链的一个端点，乘上另一组点的排列，每一个排列都对应着一个合法的方案。但是这样显然会算重。不难发现，对于一种方案中连有边的两个点，将其所在点集互换，仍然为一个方案，这就是算重的部分。因此，最终的答案需要将其去掉。则答案为 $\begin{pmatrix} 2 \times (n-m-k)\\ n-m-k\\ \end{pmatrix}(n-m-k)! \div 2^{(n-m-k)} $

最后，我们需要将剩余度数为 $2$ 的点插入当前的链中。同样的，即使插入同一个链，其顺序也会有影响，因此考虑先确定剩余点的一个排列。剩下的就是一个球无标号盒有标号的经典问题，插板法可得这一步的答案是 $\begin{pmatrix} m-1\\ n-m-k-1\\ \end{pmatrix} \times (2 \times m+k-n)！$

于是根据乘法原理相乘即可得到结果为：

$$
\begin{pmatrix} n\\ k\\ \end{pmatrix}
\begin{pmatrix} n-k\\ 2 \times (n-m-k)\\ \end{pmatrix}
\begin{pmatrix} 2 \times (n-m-k)\\ n-m-k\\ \end{pmatrix}(n-m-k)!
\begin{pmatrix} m-1\\ n-m-k-1\\ \end{pmatrix} (2 \times m+k-n)！\div 2^{(n-m-k)}
$$

其中，$k$ 的取值范围可以根据 $n$ 和 $m$ 求得，对所有 $k$ 的可能取值求解上式并求和即可。预处理后上式可以 $O(1)$ 求出。

但是，我们其实可以注意到，上式如果化简，则可以消去大量冗余的阶乘。最终化简后的形式实际上如下：

$$
\frac{(n)!(m-1)!}{(k)!(n-m-k)!(2 \times m+k-n)!(n-m-k-1)!2^{(n-m-1)}}
$$

发现好算了不少，于是可以求得飞快。

给出代码：


```cpp
#include<bits/stdc++.h>
#define R register
using namespace std;
typedef long long ll;
const int N=1e5+20,mod=1e9+7;
int jc[N],inv[N],inv2[N];
inline int pwr(int a,int b){
	int ans=1;
	for(;b;b>>=1){
		if(b&1)ans=(ll)ans*a%mod;
		a=(ll)a*a%mod;
	}
	return ans;
}
inline int calc(int i,int j,int k){
	int ans=1;
	ans=1ll*ans*jc[j-1]%mod;
	ans=1ll*ans*inv[k]%mod;
	ans=1ll*ans*inv[i-j-k]%mod;
	ans=1ll*ans*inv2[i-j-k]%mod;
	ans=1ll*ans*inv[2*j+k-i]%mod;
	ans=1ll*ans*inv[i-j-k-1]%mod;
	return ans;
}
int main()
{
	int T;
	scanf("%d",&T);
	int mx=N-10;
	jc[0]=1;
	for(R int i=1;i<=mx;i++)jc[i]=(ll)i*jc[i-1]%mod;
	inv[mx]=pwr(jc[mx],mod-2);
	inv2[mx]=pwr(pwr(2,mx),mod-2);
	for(R int i=mx-1;i>=0;i--){
		inv[i]=(ll)inv[i+1]*(i+1)%mod;
		inv2[i]=(ll)inv2[i+1]*2ll%mod;
	}
	while(T--){
		int x,y;
		scanf("%d%d",&x,&y);
		if(x==y){
			printf("%d\n",(ll)jc[x-1]*inv2[1]%mod);
			continue;
		}
		if(y>x){
			printf("%d\n",0);
			continue;
		}
		if(y==0){
			printf("%d\n",1);
			continue;
		} 
		int ans=0;
		for(int z=max(0,x-2*y);z<=x-y-1;z++){
			ans=(ans+calc(x,y,z))%mod;
		}
		ans=(ll)ans*jc[x]%mod;
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：zzafanti (赞：1)

2024/12/11 upd：修了式子

[传送门](https://www.luogu.com.cn/problem/P9896)

## description

求 $n$ 个点 $m$ 条边的简单无向图（可以不连通）满足加入非负整数条边后可以变成 $n$ 个点的环的个数。

要求线性复杂度。

- $n\ge 3$

## solution

当 $m>n$ 时，答案为 $0$。

当 $m=n$ 时，相当于问 $n$ 个点构成一个环的方案数，为 $\dfrac{(n-1)!}{2}$。

考虑当 $m<n$ 的情况。

这时候的无向图一定是 $k=n-m$ 条互不联通的链。**我们不妨先把这些链看成是有序的，最后除以 $k!$ 即可。**

如果我们知道了每种大小的链有多少种方案，求出原答案就是一个有标号计数问题了，这让我们联想到指数生成函数。

设 $g_{i}$ 表示大小（即点数）为 $i$ 的有标号非空链的数量，有以下关系式：

- $g_{1}=1,g_{0}=0$

- $g_{i}=\dfrac{i!}{2},i\ge 2$

第一个式子是容易看出的，第二个式子是因为链不应该考虑正着放还是反着放，所以要阶乘除以 2。

我们写出 $g$ 的指数生成函数 $G(x)=\sum\limits_{i\ge 1} \dfrac{g_i}{i!} x^i=x+\dfrac{1}{2}x^2+\dfrac{1}{2}x^3\dots$

把它推成封闭形式：

- $xG(x)=x^2+\dfrac{1}{2}x^3+\dfrac{1}{2}x^4+\dots$

- $(x-1)G(x)=\dfrac{1}{2}x^2-x$

- $G(x)=\dfrac{x}{2}\cdot\dfrac{x-2}{x-1}$

我们要求 $k$ 条链拼起来，总点数为 $n$ 的方案数，就是求 $[x^n]G(x)^k$。

来推 $G(x)^k$ ！

乘积的几部分分别 $k$ 次方，有 $G(x)^k=\dfrac{x^k}{2^k}\cdot (\dfrac{1}{1-x})^k \cdot (2-x)^k$。

第一部分很好处理，第二部分 $(\dfrac{1}{1-x})^k=(1+x+x^2+x^3+\dots)^k$，其第 $t$ 项就是把 $t$ 分成 $k$ 个有序非负整数的方案数，使用插板法可知方案数是 $\dbinom{t+k-1}{k-1}$，最后一部分二项式展开就可以了。

于是我们可以写出 $[x^n]G(x)^k=\dfrac{1}{2^k}\sum\limits_{i=0}^{n-k}\dbinom{n-i-1}{k-1}\dbinom{k}{k-i}2^{k-i}(-1)^{i}$

可以线性求出。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;

using E=long long;
using ui=uint32_t;
using lint=__int128;
constexpr E inf=1e16,mod=1e9+7;

namespace Comb{
  vector<E> fac(1,1ll),ifac(1,1ll),INV(2,1ll),pw;

  inline E ksm(E a,E b,const E MOD=mod){
    E ret=1;
    assert(b>=0);
    while(b){
      if(b&1) ret=ret*a%MOD;
      a=a*a%MOD;
      b>>=1;
    }
    return ret;
  }
  int _n;
  void CombPrework(int n){
    pw.resize(n+1);
    pw[0]=1;
    for(int i=1; i<=n; i++) pw[i]=pw[i-1]*2%mod;
    _n=n;
    for(int i=2; i<=n; i++) INV.emplace_back((mod-mod/i)*INV[mod%i]%mod);
    fac.resize(n+1),ifac.resize(n+1);
    fac[0]=ifac[0]=1;
    for(int i=1; i<=n; i++) fac[i]=fac[i-1]*i%mod;
    ifac[n]=ksm(fac[n],mod-2);
    for(int i=n-1; i; i--) ifac[i]=ifac[i+1]*(i+1)%mod;
  }

  E Inv(E x){ return x<=_n?INV[x]:(x==1?1:Inv(mod%x)*(mod-mod/x)%mod); }

  inline E C(E n,E m){
    if(n<0||m<0||n<m) return 0;
    while(fac.size()<=n){
      fac.emplace_back(fac.back()*(fac.size())%mod);
      ifac.emplace_back(ifac.back()*ksm(ifac.size(),mod-2)%mod);
    }
    return fac[n]*ifac[m]%mod*ifac[n-m]%mod;
  }

  inline E A(E n,E m){
    if(m<0) return 0;
    return C(n,m)*fac[m]%mod;
  }
};
using namespace Comb;

void solve(){
  E n,m;
  cin>>n>>m;
  if(n==m){
    cout<<fac[n]*ksm(2*n,mod-2)%mod<<'\n';
    return ;
  }
  E k=n-m;
  if(k<0){
    cout<<0<<'\n';
    return ;
  }
  E ans=0;
  for(E i=0; i<=m&&i<=k; i++){
    E x=C(n-i-1,k-1)*C(k,i)%mod;
    x=x*pw[k-i]%mod;
    if(i&1) ans=(ans-x+mod)%mod;
    else ans=(ans+x)%mod;
  }
  ans=ans*ksm(pw[k],mod-2)%mod*fac[n]%mod*ifac[k]%mod;
  cout<<(ans%mod+mod)%mod<<'\n';
}

int main(){

  cout.tie(nullptr),cin.tie(nullptr)->sync_with_stdio(false);

  CombPrework(5e5);
  int T;
  cin>>T;
  while(T--) solve();

  return 0;
}
```

---

## 作者：OrinLoong (赞：0)

## LGP9896 [ICPC-2018-R QGD] Sub-cycle Graph 学习笔记
[Luogu Link](https://www.luogu.com.cn/problem/P9896)

### 前言
不会GF。暂时看来组合意义大抵还是能保平安的。

### 题意简述
我们对于一个 $n$ 点 $m$ 边的无向有标号简单图，定义其为“半环图”当且仅当其添加若干条边后整个图可以变为一个 $n$ 个点的简单环。特别定义一个环也是半环图。

给定 $n,m$，问有多少这样的半环图。答案对 $10^9+7$ 取模。

$n\le 10^5$。

### 做法解析
“半环图”实际上可以被理解为若干条链。再进一步，这个问题也等价于：求将 $n$ 个元素划分成 $n-m$ 个排列的方案数（其中排列可以翻转）。

$m\ge n$ 时显然答案为 $0$，$m=n$ 时显然答案为环排列个数，$m=0$ 时答案为 $1$。然后呢？

你发现，一般而言，长为 $x$ 的可翻转排列数为 $\frac{x!}{2}$，但是 $x=1$ 的时候这式子要特殊处理。而这道题的数据范围又告诉我们，我们基本上只被允许枚举某种 $O(n)$ 的要素，而显然非单点链条数肯定是小于 $n$ 的，所以你枚举有多少条非单点链，设有 $x$ 条。

接下来有两种思维方式。

#### 思路一
第一种，是将所有点分成度数为 $0$、$1$、$2$ 三类来讨论。

度数为 $1$ 的点（即链的两端）数量为 $2x$，而总度数为 $2m$，因此度数为 $2$ 的点有 $\frac{2m-2x}{2}=m-x$ 个，剩下 $n-(m-x)-2x=n-m-x$ 个点即为度数为 $0$ 的。

我们先给每个点分配一种类型。这里的方案数显然为 $\binom{n}{2x}\binom{n-2x}{m-x}$。

然后你让每个度数为 $1$ 的点两两配对。即先选出 $x$ 个点，让另外 $x$ 个点全排列。最后因为 $(u,v)$ 同构于 $(v,u)$，所以还要去重，这部分答案为 $\frac{\binom{2x}{x}x!}{2^x}$。

最后度数为 $2$ 的点要划分到这些链条里。这部分方案即为先全排列后隔板法。这部分答案为 $(m-x)!\binom{m-x+(x-1)}{x-1}=(m-x)!\binom{m-1}{x-1}$。

综上答案为 $\sum_{x=1}^{\lfloor\frac{n}{2}\rfloor}\binom{n}{2x}\binom{n-2x}{m-x}\frac{\binom{2x}{x}x!}{2^x}(m-x)!\binom{m-1}{x-1}$。

#### 思路二
第二种，是先思考无标号情况，再拓展到有标号情况。

总体和思路一类似。

### 代码实现
这题也没必要给代码啊。蒜鸟蒜鸟。

### 反思总结
长为 $1$ 的链（即单点）作为排列时，在去重翻转时不需要除以二，所以对单点和非单点链条有时应该分开计数。

---

## 作者：modfish_ (赞：0)

## 思路
首先特判一些特殊情况，$m>n$ 答案为 $0$，$m=n$ 答案为环排列数量 $\displaystyle\frac{(n-1)!}{2}$，$m=0$ 答案为 $1$。

剩下的问题就是：求出将 $n$ 个不同元素划分为 $n-m$ 个排列的方案数。注意此处的排列翻转后算同一种。即 $\{1,2,3\}$ 与 $\{3,2,1\}$ 是一样的。

首先让我们考虑这种排列如何计数。很明显长为 $x$ 的排列数量即为 $\displaystyle\frac{x!}{2}$，除以 $2$ 就把翻转造成的重复去掉了。不过 $x=1$ 时，答案不能这么算。

既然长为 $1$ 的排列要另行考虑，那么我们不妨就枚举有多少个元素在长大于 $1$ 的排列内，设为 $i$ 个。

考虑令 $f_{i,x,y}$ 表示总共 $i$ 个元素中，将 $x$ 个元素划分为 $y$ 个**长度大于 $1$** 的排列中的方案数（此处 $y$ 个排列之间有顺序）。很明显有转移：

$$f_{i,x,y}=\sum_{j=0}^{x-2}f_{i,j,y-1}\times\binom{i-j}{x-j}\times\frac{(x-j)!}{2}$$

边界为 $f_{i,0,0}=1$，将 $\displaystyle\binom{i-j}{x-j}$ 展开并化简，有：

$$(i-x)!f_{i,x,y}=\sum_{j=0}^{x-2}\frac{(i-j)!}{2}f_{i,j,y-1}$$

可以记 $g_{i,x,y}=\displaystyle\frac{2^y(i-x)!}{i!}f_{i,x,y}$。除以 $i!$ 是为了让边界仍为 $g_{i,0,0}=1$。得到转移式：

$$g_{i,x,y}=\sum_{j=0}^{x-2}g_{i,j,y-1}$$

$g_{i,x,y}$ 有一个很清晰的组合意义：在数轴上从 $0$ 开始跳跃，一次至少跳过距离 $2$，求有多少种方案跳 $y$ 步到达 $x$。

至少跳过距离 $2$ 不是很好做。考虑将跳过的每一步中抽出来距离 $1$，这样就可以算每一步至少跳距离 $1$ 的方案。即跳 $y$ 步到达 $x-y$，共有：

$$\binom{x-y-1}{y-1}$$

种方案。这是容易说明的，其实就是要在中间 $x-y-1$ 个点中选择 $y-1$ 个途径点，答案自然如上。

故 $g_{i,x,y}=\displaystyle\binom{x-y-1}{y-1}$。进而 $f_{i,x,y}=\displaystyle\frac{i!}{2^y(i-x)!}\binom{x-y-1}{y-1}$。

我们要求的是 $f_{i,i,i-m}=\displaystyle \frac{i!}{2^{i-m}}\binom{m-1}{i-m-1}$。

注意，我们设的 $f_{i,x,y}$ 是计入各个排列之间的顺序的，所以真实的答案应为：

$$\frac{i!}{2^{i-m}(i-m)!}\binom{m-1}{i-m-1}$$

最后把答案求和：

$$\sum_{i=m+1}^{\min(2m,n)}\frac{i!}{2^{i-m}(i-m)!}\binom{m-1}{i-m-1}\times\binom{n}{i}$$

整理得：

$$n!(m-1)!\sum_{i=m+1}^{\min(2m,n)}\frac{1}{2^{i-m}(i-m)!(n-i)!(i-m-1)!(2m-i)!}$$

直接计算即可。时间复杂度 $O(\sum n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 1e5 + 5, p = 1e9 + 7;

ll fac[maxn], infa[maxn], pw[maxn];

ll qpow(ll a, ll x){
    ll res = 1;
    while(x){
        if(x & 1) res = res * a % p;
        a = a * a % p;
        x >>= 1;
    }
    return res;
}

int main(){
    fac[0] = pw[0] = 1;
    ll _2 = qpow(2, p - 2);
    for(int i = 1; i <= 1e5; i ++) fac[i] = fac[i - 1] * i % p, pw[i] = pw[i - 1] * _2 % p;
    infa[(int)1e5] = qpow(fac[(int)1e5], p - 2), pw[(int)1e5] = qpow(pw[(int)1e5], p - 2);
    for(int i = 1e5; i >= 1; i --) infa[i - 1] = infa[i] * i % p;
    int T;
    scanf("%d", &T);
    while(T --){
        int n;
        ll m;
        scanf("%d %lld", &n, &m);
        if(m > n) printf("0\n");
        else if(m == n) printf("%lld\n", fac[n - 1] * _2 % p);
        else if(m == 0) printf("1\n");
        else{
            ll ans = 0;
            for(int i = m + 1; i <= min((int)m * 2, n); i ++){
                ans = (ans + infa[i - m] * infa[n - i] % p * infa[i - m - 1] % p * infa[m * 2 - i] % p * pw[i - m] % p) % p;
            }
            printf("%lld\n", ans * fac[n] % p * fac[m - 1] % p);
        }
    }
    return 0;
}
```

---

## 作者：zheng_zx (赞：0)

## P9896 [ICPC2018 Qingdao R] Sub-cycle Graph

[题目传送门](https://www.luogu.com.cn/problem/P9896)

### 分析

---

一道数学题。一个连接 $n$ 个点的环包含 $m$ 条边的子图中，一定包含 $k=n-m$ 个连通分量，其中每个连通分量要么是一个点，要么是包含多个点的一条链，则问题转化成把 $n$ 个顶点划分成 $k$ 个连通分量的方案数。我们可以对所有点进行染色，将同一连通分量中的点染成相同的颜色，则问题转化成将 $n$ 个点染成 $k$ 种染色的方案数（注意是带权的方案数，因为将一些点染成相同的颜色的方法有多种）。

用 $k$ 种颜色给 $n$ 个点染色的生成函数(指数型)为：

$$f(x)=\sum^k_{i=1} \frac{a_i}{i!} x^i,a_i=\left\{\begin{aligned}&1,i=1 \\&\frac{i!}2,i>1 \\\end{aligned}\right.$$

上式化简得：

$$f(x)=\frac 1 2(2x+x^2+x^3+\ldots+x^k)=\frac 1 2x(\frac{1-x}{2-x})$$

则答案的生成函数为：

$$[f(x)]^k=\frac 1 {2^k}x^k(2-x)^k\frac 1 {(1-x)^k}$$

所求的结果即为上式中 $x^n$ 项的系数乘上 $n!$ 再除以 $k!$。

其中 $(2-x)^k$ 中项的系数可以用二项式定理求，而后面的 $\frac 1 {(1-x)^k}$ 比较特殊，与这个函数相乘，相当于对整个多项式求了 $k$ 次前缀和，自己算一算就会发现，求 $k$ 次前缀和后第 $n$ 项的系数为

$$\sum^n_{i=0} C^{k-1}_{k-1+n-i}a_i$$

因此时间复杂度为 $O(n)$。

注：

- $k=0$ 和 $k<0$ 的情况要特殊处理。

### Code：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 1e5 + 10, INF = 0x3f3f3f3f, mod = 1e9 + 7;
ll a[N], n, k, f[N], invf[N], inv[N], ans, invp2[N], T;
ll C(ll a,ll b) {
    return f[a] * invf[b] % mod * invf[a - b] % mod;
}
int main() {
    f[0] = invf[0] = f[1] = invf[1] = 1, inv[1]=1;
    for(ll i = 2; i < N; ++i) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        f[i] = f[i - 1] * i % mod;
        invf[i] = invf[i - 1] * inv[i] % mod;
    }
    invp2[0] = 1;
    for(ll i = 1; i < N; ++i)
        invp2[i] = invp2[i - 1] * inv[2] % mod;
    cin >> T;
    while(T--){
        cin >> n >> k;
        k = n - k;
        if(k < 0)
            ans = 0;
        else if(k == 0)
            ans = f[n - 1] * inv[2] % mod;
        else {
            ans = 0;
            for(ll i = 0; i <= n; ++i)
            a[i] = 0;
            for(ll i = 0; i <= k && i + k <= n; ++i) {
                a[i + k] = C(k, i) * invp2[i] % mod;
                if(i & 1)
                    a[i + k] = -a[i + k];
            }
            for(ll i = 0; i <= n; ++i)
                ans = (ans + C(k - 1 + n - i, k - 1) * a[i]) % mod;
            ans = (ans * f[n] % mod * invf[k] % mod + mod) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Nelofus (赞：0)

首先考虑把一个 $k$ 阶排列放进一条 $k$ 个点链里，有多少种本质不同的链，设其方案数为 $f(i)$，那么若 $i=1$，则 $f(i)=1$，否则 $f(i)=\frac{i!}{2}$。

其 EGF $F(x)$ 满足

$$
\Big[\frac{x^n}{n!}\Big]F(x)=\begin{cases}
1, &n=1\\
\frac{n!}{2}, &n>1\\
\end{cases}
$$

也就是说

$$
\begin{aligned}
F(x)&=x+\frac{1}{2}x^2+\frac{1}{2}x^3+\cdots\\
&=\frac{1}{2}\Bigg(2x+\frac{x^2}{1-x}\Bigg)\\
&=\frac{1}{2}x\bigg(\frac{2-x}{1-x}\bigg)
\end{aligned}
$$

现在我们有 $k=n-m$ 条链，那么答案即

$$
\frac{1}{k!}\Big[\frac{x^n}{n!}\Big]F^k(x)
$$

考虑 $F^k(x)$。

$$
\begin{aligned}
F(x)&=\frac{1}{2^k}x^k(2-x)^k(1-x)^{-k}\\
&=\frac{1}{2^k}x^k\sum_{i=0}^{k}\binom{k}{i}2^{k-i}(-x)^i\sum_{i=0}^{\infty}\binom{-k}{i}1^{-k-i}(-x)^i\\
&=\frac{1}{2^k}x^k\sum_{i=0}^{k}\binom{k}{i}2^{k-i}(-x)^i\sum_{i=0}^{\infty}\frac{k^{\overline{i}}}{i!}x^i\\
&=\frac{1}{2^k}x^k\sum_{i=0}^{k}\binom{k}{i}2^{k-i}(-x)^i\sum_{i=0}^{\infty}\frac{(k+i-1)!}{(k-1)!i!}x^i\\
&=\frac{1}{2^k}x^k\sum_{i=0}^{k}\binom{k}{i}2^{k-i}(-x)^i\sum_{i=0}^{\infty}\binom{k+i-1}{i}x^i\\
\end{aligned}
$$

---

