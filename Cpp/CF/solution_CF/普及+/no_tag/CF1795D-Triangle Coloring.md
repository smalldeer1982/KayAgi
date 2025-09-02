# Triangle Coloring

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and $ n $ edges, where $ n $ is divisible by $ 6 $ . Each edge has a weight, which is a positive (greater than zero) integer.

The graph has the following structure: it is split into $ \frac{n}{3} $ triples of vertices, the first triple consisting of vertices $ 1, 2, 3 $ , the second triple consisting of vertices $ 4, 5, 6 $ , and so on. Every pair of vertices from the same triple is connected by an edge. There are no edges between vertices from different triples.

You have to paint the vertices of this graph into two colors, red and blue. Each vertex should have exactly one color, there should be exactly $ \frac{n}{2} $ red vertices and $ \frac{n}{2} $ blue vertices. The coloring is called valid if it meets these constraints.

The weight of the coloring is the sum of weights of edges connecting two vertices with different colors.

Let $ W $ be the maximum possible weight of a valid coloring. Calculate the number of valid colorings with weight $ W $ , and print it modulo $ 998244353 $ .

## 说明/提示

The following picture describes the graph from the first example test.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1795D/4ae4faa6e7106558b0f38fa8feb77e73227352e2.png)The maximum possible weight of a valid coloring of this graph is $ 31 $ .

## 样例 #1

### 输入

```
12
1 3 3 7 8 5 2 2 2 2 4 2```

### 输出

```
36```

## 样例 #2

### 输入

```
6
4 2 6 6 6 4```

### 输出

```
2```

# 题解

## 作者：Hanx16Kira (赞：6)

# Triangle Coloring

[Luogu CF1795D](https://www.luogu.com.cn/problem/CF1795D)

## 简要题意

> 给定 $2n$ 个三元环，边有正权，将这 $6n$ 个点中的 $3n$ 染成白色，剩下染成黑色。如果一条边连接的两个点颜色不同，那么称这条边是特殊的，求使得所有特殊的边的边权和最大的染色方案数量。

## Solution

首先这道题有一个很显然的性质，就是一个三元环一定会被选择两条边。这一点虽然简单，但是极其重要。证明的话，因为总共有 $2n$ 个三元环，所以如果一个三元环染出了 $2$ 黑 $1$ 白，那么总会有另一个三元环染成 $1$ 黑 $2$ 白。如果一个三元环染成了 $3$ 黑，与之对应的三元环染成了 $3$ 白，那么这两个三元环都无法对答案产生贡献，这种方案一定不优。

那么最优的答案就一定是通过**选择每个三元环中权值更大的两条边**得到的。

考虑这样的染色方案怎么计数。首先如果一个选边方案固定，那么染色方案会是 $\displaystyle\binom{2n}{n}$（即 $2n$ 个三元环中选择 $n$ 个染成 $1$ 黑 $2$ 白，剩余全部染成 $2$ 黑 $1$ 白），这部分可以直接 $\mathcal O(n)$ 计算。

考虑有多少合法的选边方案，记一个三元环中边权从小到大为 $w_1,w_2,w_3$。那么：

- 当 $w_1=w_2=w_3$ 时这个三元环将会有 $3$ 种选边方法。
- 当 $w_1=w_2,w_1\neq w_3$ 时这个三元环将会有 $2$ 种选边方法。
- 剩余情况一定只有一种选边方案，即选择 $w_2,w_3$。

答案根据乘法原理乘起来即可，注意取模过程中爆 `int` 的问题。

### Code

```cpp
#include<bits/stdc++.h>

using namespace std;

constexpr int _SIZE = 3e5, mod = 998244353;
int n, w[_SIZE + 5];
int fac[_SIZE + 5], ifac[_SIZE + 5];

inline int Qpow(int x, int y) {
	int res = 1, base = x;
	
	for (; y; y >>= 1, base = 1ll * base * base % mod)
		if (y & 1) res = 1ll * res * base % mod;
	
	return res;
}

#define Inv(_) (Qpow(_, mod - 2))

void Init() {
	fac[0] = 1;
	
	for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % mod;
	
	ifac[n] = Inv(fac[n]);
	
	for (int i = n; i; --i)
		ifac[i - 1] = 1ll * ifac[i] * i % mod;
}

inline int Binom(int x, int y) {
	if (y > x || y < 0) return 0;
	
	return 1ll * fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}

void Solve() {
	cin >> n;
	Init(); // 其实可以直接 for 计算阶乘的，但是我预处理写习惯了
	int ans = Binom(n / 3, n / 6); // 基础染色方案数
	
	for (int i = 1; i <= n; ++i)
		cin >> w[i];
	
	for (int i = 1, iend = n / 3; i <= iend; ++i) { // 枚举每一组三元组
		int t[] = {w[i * 3 - 2], w[i * 3 - 1], w[i * 3]};
		sort(t, t + 3);
		
		if (t[1] == t[2] && t[0] == t[1]) ans = 3ll * ans % mod; // 三个边权相等
		else if (t[0] == t[1]) ans = 2ll * ans % mod; // 较小的两个边权相等
	}
	
	cout << ans << '\n';
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	Solve();
} 
```

---

## 作者：ダ月 (赞：3)

### 题目分析：

对于每个三角形，显然染成红红蓝或者蓝蓝红产生的权值最大。因为你染成红红红或者蓝蓝蓝明显血亏。所以有一般三角形染成蓝蓝红，一半红红蓝。

如果三条边权值都相同，那么染色方式可以在三条边里轮换，共有 $3$ 种贡献。

如果最大两条边权值相同，那么这两条边染色可以染红蓝或蓝红 $2$ 种贡献。

根据乘法原理，把每个方案相乘即可。

接下来是 $n/3$ 个边里选择 $n/6$ 个三角形染成蓝蓝红。根据组合的定义，那么有 $\binom{n/3}{n/6}$ 种方案。

根据乘法原理，答案就是所有三角形贡献的乘积乘上方案数。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;
const int N=3e5+10;
ll QP(ll x,ll y){ll ans=1;for(;y;y>>=1,x=x*x%mod) if(y&1) ans=ans*x%mod;return ans;}
ll fac[N],nfac[N];
ll sum=1;
ll a[N];
void init(){
	fac[0]=1;for(int i=1;i<=N-10;i++) fac[i]=fac[i-1]*i%mod;
	nfac[N-10]=QP(fac[N-10],mod-2);for(int i=N-11;i>=0;i--) nfac[i]=nfac[i+1]*(i+1)%mod;
}
ll C(ll x,ll y){if(x<y||x<0||y<0) return 0;return nfac[y]*nfac[x-y]%mod*fac[x]%mod;}
bool cmp(int x,int y){return x>y;}
int main(){
	init();
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i+=3){
		sort(a+i,a+i+3,cmp);
		if(a[i]==a[i+1]&&a[i+1]==a[i+2]) sum=sum*3%mod;
		else if(a[i+1]==a[i+2]) sum=sum*2%mod;
	}
	printf("%lld\n",sum*C(n/3,n/6)%mod);
	return 0;
}
```

时间复杂度：$O(n)$。


---

## 作者：ztlh (赞：1)

# Solution

容易发现，只有每个三角形的三个顶点的颜色都不全相同（即“红蓝蓝”或“红红蓝”）才可能是最优解。

于是遍历每个三角形：

- 如果三数均相同，则这个三角形有三种染法，$ans$ 变为原来的 $3$ 倍。

- 如果两个较小数相同，则有两种染法， $ans$ 变为原来的 $2$ 倍。

- 否则染色方案唯一，$ans$ 不变。

最后，一定有恰好一半的三角形为“红蓝蓝”型，另一半为“红红蓝”型。

- $ans$ 乘上 $C_{n/3}^{n/6}$ 即可。

# Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define Mod 998244353
using namespace std;
int n;
ll w[N];
ll ans=1;
ll fac[N];
ll inv[N];
ll C(ll _n,ll _m){
	return fac[_n]*inv[_m]%Mod*inv[_n-_m]%Mod;
}
int main(){
	scanf("%d",&n);
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(int i=2;i<=n;i++) fac[i]=fac[i-1]*i%Mod;
	for(int i=2;i<=n;i++) inv[i]=(Mod-Mod/i)*inv[Mod%i]%Mod;
	for(int i=1;i<=n;i++) inv[i]=inv[i-1]*inv[i]%Mod;
	for(int i=1;i<=n;i++)
		scanf("%lld",&w[i]);
	for(int i=1;i<=n;i+=3){
		if(w[i]<w[i+1]) swap(w[i],w[i+1]);
		if(w[i]<w[i+2]) swap(w[i],w[i+2]);
		if(w[i+1]<w[i+2]) swap(w[i+1],w[i+2]);
		if(w[i]==w[i+1]&&w[i+1]==w[i+2]) ans=ans*3%Mod;
		else if(w[i+1]==w[i+2]) ans=ans*2%Mod;
	}
	printf("%lld",ans*C(n/3,n/6)%Mod);
	return 0;
}
```

---

## 作者：kjhhjki (赞：1)

先来找使总权值最大的情况。

先不记具体染色，只讨论单个三角形。对于一个三角形，我们可以发现，它要么三点同色，要么两点同色，另一点与它们异色（定义为孤点）。

要使总权值最大，则应满足：
- 没有同色三角形（即每个三角形都有一个孤点和两个与之异色的点）
- 所有孤点必然是三角形内边权最大的两条边的公共点

对于同色三角形，它对 $W$ 的贡献为0，而如果与另一个三角形交换点的颜色使另一个不是同色三角形则可以使贡献增加两条边的边权。同样的，每一个三角形最大贡献为边权最大的两条边的权值和。因此这些染色方案应满足以上两点。

现在来寻找最大的染色方案数。

首先，我们可以发现，当孤点颜色确定时，三角形内另外两个点颜色也确定，所以对于 $2n$ 个三角形，只需要分配孤点的颜色即可。由于各种颜色的点总数相同，所以应该为 $n$ 个孤点分配一种颜色， 另 $n$ 个 分配另一种， 为答案贡献 $C^{n}_{2n}$ 。

接着来寻找每个三角形孤点的分配方案。每个三角形都可以由其边权关系划分为一下四类：

- 等边三角形
- 等腰三角形且底大于腰
- 等腰三角形且腰大于底
- 一般三角形

对于后两类，孤点选择固定，不再贡献；等边三角形孤点为三点中任意一个，贡献3倍；底大于腰的等腰三角形孤点可选择为底边两点的任意一个，贡献两倍。

统计各类三角形数量并乘出答案即可。

Code：

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
typedef long long _ll;
using namespace std;
const _ll P = 998244353;
 
_ll ans,n,a,c,d,x[4],y[4],p[MAXN];
 
//因为我赛场上用sort时挂掉了所以我自己重写了一个
void sort()
{
    for(int i = 1; i <= 3; ++i)
        for(int j = i+1; j <= 3; ++j)
            if(x[i] > x[j])
                swap(x[i],x[j]);
    for(int i = 1; i <= 3; ++i)
        for(int j = i+1; j <= 3; ++j)
            if(y[i] > y[j])
                swap(y[i],y[j]);
}
 
_ll qpow(_ll x,int n)
{
    _ll base = x,res = 1;
    while(n)
    {
        if(n&1) res = base*res%P;
        base = base*base%P; n >>= 1;
    }
    return res;
}
 
int main()
{
    cin >> n; n /= 6; p[1] = 1;
    for(int i = 2; i <= 2*n; ++i)
        p[i] = p[i-1]*i%P;
    ans = p[2*n] * qpow(p[n],P-2)%P * qpow(p[n],P-2)%P;
    for(int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld%lld%lld%lld%lld",x+1,x+2,x+3,y+1,y+2,y+3);
        sort();
        if(x[1]==x[3]) ++d;
        else if(x[1]==x[2]) ++c;
        if(y[1]==y[3]) ++d;
        else if(y[1]==y[2]) ++c;
    }
    ans = ans * qpow(2,c)%P * qpow(3,d)%P;
    cout << ans;
    return 0;
}
```


---

## 作者：undefined_Ryan (赞：0)

### 问题转化

有 $n$（记为 $6k$）个点，分为 $2k$ 个三点组，每一个三点组形成一个环且不同环互相没有连边。对每个三点组染色时，共有 $2$ 种情况：
1. $1$ 红 $2$ 蓝或 $2$ 红 $1$ 蓝，此时共有 $2$ 条边计入总分，这 $2$ 条边可以通过调整红、蓝的位置来改变；
2. $3$ 红或 $3$ 蓝，不会有边计入总分。

输入格式中说明了 $w_i \ge 1$，因此第 $1$ 种情况永远更优。

### 取值条件

在这一部分中，将忽略 $1$ 红 $2$ 蓝和 $2$ 红 $1$ 蓝的区别。

显然，对于一个三点组，最优解是权值最大的 $2$ 条边计入总分，此时取两边的公共结点与另外两点颜色不同。

对于不同的边权 $(a_1,a_2,a_3)$（不妨 $a_1\le a_2\le a_3$），权值最大的 $2$ 条边有不同的情况：
1. $a_1<a_2\le a_3$，此时只有 $1$ 种情况，即取 $a_2$ 和 $a_3$。
2. $a_1=a_2<a_3$，取 $a_3$ 以及 $a_1$ 和 $a_2$ 中任意一个，有 $2$ 种情况。
3. $a_1=a_2=a_3$，任意取 $2$ 条边，共有 $3$ 种情况。

### 红蓝分配

可以只考虑红色结点的数量，共有 $3k$ 个，且对于每一个三点组，有 $1$ 或 $2$ 个红色结点。

记第 $m$ 个三点组有 $x_m$ 个红色结点，则

$$x_1+x_2+\cdots+x_{2k}=3k$$

即

$$(x_1-1)+(x_2-1)+\cdots+(x_{2k}-1)=k$$

注意到 $x_m-1$ 为 $0$ 或 $1$，则解的数量即为 $2k\choose k$。

### 计算杂项

主要涉及的难点为组合数的计算。

因为快速幂较为方便 ~~不会扩欧~~，此处使用快速幂计算：

```cpp
int fastpow(int a,int b) {
    int ans=1;
    while (b) {
        if (b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
```

对于组合数，这里采用这样的做法：

$$\begin{aligned}{2k\choose k}&=\frac{(2k)!}{(k!)^2}\\&\equiv F_{2k}\times(F_k)^{-2}\\&\equiv F_{2k}\times(F_k)^{\texttt{mod }-\,1}\times(F_k)^{-2}\\&\equiv F_{2k}\times(F_k)^{\texttt{mod }-\,3}\pmod{\texttt{mod}}\end{aligned}$$

其中 $F_t$ 表示 $t!$，$\texttt{mod}$ 即 $998244353$。

可以简单地计算出本题的时间复杂度为 $O(n)$，代码实现的难度不大，不贴代码。

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

首先，没有环会 $3$ 点同色，否则可以有更优的解法。

在 $\dfrac{n}{3}$ 个环中，有 $\dfrac{n}{6}$ 个环是红 $2$ 蓝 $1$，剩下 $\dfrac{n}{6}$ 个环是红 $1$ 蓝 $2$。分配它们的方案数就是 $C_{n/3}^{n/6}$。

考虑每个环取到最优有多少种可能。不妨设一个环是红 $2$ 蓝 $1$ 的。

可以发现，如果 $3$ 边相同，则可以任意涂色，就是 $3$ 种情况；

否则如果最小的 $2$ 边相同，则剩下的最大边两端异色，最小边交点不管；

否则只有 $1$ 种可能，就是最小边同色，第三点异色。

乘法原理乘上去即可。

### 2 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 300000
#define mod 998244353
long long fac[max_n+2];
long long inv[max_n+2];
int n;
long long a[max_n+2];
long long cnt1=0;
long long cnt2=0;
long long cnt3=0;
long long qp(long long a,long long b){
	long long res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
long long c(int n,int m){
	if(n<m||n<0||m<0)return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1795D_1.in","r",stdin);
	freopen("CF1795D_1.out","w",stdout);
	#endif
	fac[0]=1;
	for(int i=1;i<=max_n;++i)fac[i]=fac[i-1]*i%mod;
	inv[max_n]=qp(fac[max_n],mod-2);
	for(int i=max_n-1;i>=0;--i)inv[i]=inv[i+1]*(i+1)%mod;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%lld",a+i);
	for(int i=1;i<=n;i+=3){
		sort(a+i,a+i+3);
		if(a[i]==a[i+1]&&a[i+1]==a[i+2])++cnt3;
		else if(a[i]==a[i+1])++cnt2;
		else ++cnt1;
	}
	printf("%lld\n",c(n/3,n/6)*qp(2,cnt2)%mod*qp(3,cnt3)%mod);
	return 0;
}
```

**By dengziyue**

---

## 作者：Ginger_he (赞：0)

用 $\texttt{R}$ 表示红色，$\texttt{B}$ 表示蓝色。

因为红点和蓝点总个数相等，所以对于所有三元组， $\texttt{RRR}$ 和 $\texttt{BBB}$ 个数相等，$\texttt{RRB}$ 和 $\texttt{BBR}$ 个数相等。

不难发现，若一个三元组的颜色都相同，则对 $W$ 没有贡献。为了保证 $W$ 最大化，故应该有 $\dfrac{n}{6}$ 个 $\texttt{RRB}$ 和 $\dfrac{n}{6}$ 个 $\texttt{BBR}$。

![](https://espresso.codeforces.com/56fc24895819318d9cb93e0b212b2a1bf75a558d.png)

设第 $i$ 个三元组的答案为 $ans_i$，

若三条边的权值都相等，即上图左下角的情况，则可以任意选一个点为异色点，故 $ans_i=3$。

若两条边的权值相等且为较小值，即上图左上角的情况，我们可以选择 $10$ 或 $12$ 号点为异色点，故 $ans_i=2$。

若两条边的权值相等且为较大值，即上图右上角的情况，我们只能选择 $3$ 号点为异色点，故 $ans_i=1$。

若三条边的权值均不相等，即上图右下角的情况，我们只能选择 $4$ 号点为异色点，故 $ans_i=1$。

综上，令 $m=\dfrac{n}{6}$，则答案为

$$\binom{2m}{m}\times\prod_{i=1}^{2m}ans_i$$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 300005
const ll p=998244353;
int n,a,b,c,x,y,z;
ll f[N],g[N],ans;
ll quickpow(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		b>>=1;
		a=a*a%p;
	}
	return res;
}
ll binom(ll n,ll m)
{
	return f[n]*g[m]%p*g[m]%p;
}
int main()
{
	scanf("%d",&n);
	f[0]=1;
	for(int i=1;i<=n;i++)
		f[i]=f[i-1]*i%p;
	g[n]=quickpow(f[n],p-2);
	for(int i=n-1;i>=1;i--)
		g[i]=g[i+1]*(i+1)%p;
	ans=binom(n/3,n/6);
	for(int i=1;i<=n/3;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		a=min(x,min(y,z)),c=max(x,max(y,z)),b=x+y+z-a-c;
		if(a==b&&b==c) ans=ans*3%p;
		else if(a==b) ans=ans*2%p;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

