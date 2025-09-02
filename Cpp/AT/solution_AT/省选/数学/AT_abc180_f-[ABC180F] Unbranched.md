# [ABC180F] Unbranched

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc180/tasks/abc180_f

頂点にラベルが付き辺にはラベルが付いていない $ N $ 頂点 $ M $ 辺の単純とも連結とも限らないグラフであって、以下の条件を満たすものの個数を $ 10^9+7 $ で割ったあまりを求めてください。

- 自己ループを持たない
- すべての頂点の次数が $ 2 $ 以下である
- 各連結成分のサイズを並べたとき、その最大値がちょうど $ L $ である

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 300 $
- $ 1\leq\ M\ \leq\ N $
- $ 1\ \leq\ L\ \leq\ N $
- 入力はすべて整数

### Sample Explanation 1

頂点に $ 1 $ から $ N $ の番号を付けたとき、以下の $ 3 $ 通りのグラフが条件を満たします。 - $ 1-2 $ 間と $ 2-3 $ 間に辺がある。 - $ 1-2 $ 間と $ 1-3 $ 間に辺がある。 - $ 1-3 $ 間と $ 2-3 $ 間に辺がある。

## 样例 #1

### 输入

```
3 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
4 3 2```

### 输出

```
6```

## 样例 #3

### 输入

```
300 290 140```

### 输出

```
211917445```

# 题解

## 作者：NaCly_Fish (赞：17)

[题目链接](https://www.luogu.com.cn/problem/AT_abc180_f)

今天偶然间看到这题，题解中的做法都是 $\Theta(NML)$ 的，能不能给力一点啊？~~既然有这篇 blog 了，那答案是肯定的。~~
****
首先题目中要求「出现的最大连通块大小为 $L$」，可以直接转化为「连通块大小都不超过 $L$」的数量，再减去大小不超过 $L-1$ 的方案数。

我们可以考虑二元生成函数，用形式变量 $x$ 来计量点数，$y$ 来计量边数。求出一个连通块的生成函数后，直接对其做 $\exp$ 即可。由于每个点的度数不超过 $2$，那每个连通块都只能是「链」或「环」。

先考虑链，由于边是无向的，不少于 $2$ 个点的链只有 $i!/2$ 个，点数不超过 $L$，所以
$$A=x+\sum_{i=2}^L\frac{x^iy^{i-1}}{i!} \frac{i!}{2}=x+\frac 12\sum_{i=2}^L x^iy^{i-1}$$
再考虑环，环的大小至少为 $2$，且不少于 $3$ 个点的环只有 $i!/(2i)$ 个，所以
$$B=[L\geq 2]\frac{x^2y^2}{2}+\sum_{i=3}^L \frac{x^iy^i}{2i}$$
而我们要求的是
$$n![x^ny^m]\exp(A+B)$$
$$=n![x^ny^m]\sum_{j\geq 0} \frac{x^j}{j!}\left( 1+\frac 12\sum_{i=2}^L(xy)^{i-1}\right)^j\exp B$$
注意观察后面这一大块不含 $x^j$ 的部分，其展开式仅由形如 $x^ty^t$ 的项组成。因此逐项提取系数时，仅有 $j=n-m$ 这一项可能非零。那答案就简单了：
$$\frac{n!}{(n-m)!}[u^m]\left( 1+\frac 12\sum_{i=2}^Lu^{i-1}\right)^{n-m}\exp \left( [L\geq 2]\frac{u^2}{2}+\sum_{i=3}^L \frac{u^i}{2i}\right)$$
把多项式板子拉过来，就可以轻松做到 $\Theta(N+M\log M)$ 的时间复杂度了。
****
### 能不能再给力一点啊？

考虑到 $B$ 中多的一项很麻烦，而且 $L=1$ 的情况又很简单，以下默认 $L\geq 2$。

首先化简
$$1+\frac 12 \sum_{i=2}^Lu^{i-1}=\frac{2-u-u^L}{2(1-u)}$$
其 $n-m$ 次幂（设为 $f(u)$）显然微分有限，虽然递推阶数达到了 $L+1$，但递推系数是稀疏的：
$$f'(u)(2-3u+u^2-u^L+u^{L+1})=(n-m)f(u)(1-Lu^{L-1}+(L-1)u^L)$$
再来考虑另一部分：
$$g(u)=\exp\left( \frac{u^2}{2}+\sum_{i=3}^L \frac{u^i}{2i}\right)$$
$$g'(u)=\left( u+\sum_{i=2}^{L-1} \frac{u^i}{2}\right)g(u)$$
$$2(1-u)g'(u)=(2u-u^2-u^L)g(u)$$
同样可以直接提取系数然后递推，时间复杂度 $\Theta(M)$。[提交记录链接](https://atcoder.jp/contests/abc180/submissions/46698621)

关于「能不能再给力一点啊？」这个问题，我是感觉比较困难。这个形式太特殊了，刚好分成两个高阶、但系数稀疏的整式递推。

不要跟我说 $\Theta(L^3 \sqrt M+L^2 \sqrt M \log M)$ 直接套板子的池沼做法了（

---

## 作者：Kreado (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc180_f)。

## 思路

我们不妨令 $f_{i,j}$ 表示图中有 $i$ 个点 $j$ 条边，连通块数量小于等于 $L$ 的方案数（如果是直接等于 $L$ 会很难算），两次 DP 求出 $L$ 和 $L-1$ 的方案数相减即可得到答案。

由于这个图的每一个点的度数最多为 $2$，因此我们可以判断这是一条链或者一个环。

我们先枚举一个连通块的大小 $k$。

考虑链的情况，$f_{i,j}$ 可以被 $f_{i-k,j-k+1}$ 转移得到，该状态剩余了 $n-i+k$ 个点，我们需要从这 $n-i+k$ 个点中选出 $k$ 个点做为一条链，但是会出现重复的，这时我们只需钦定一个最小点即可，方案数为 $\dbinom{n-i+k-1}{k-1}$，当然，由于点的顺序是随意的，我们还要乘以一个阶乘 $k!$，我们还要考虑链同构的情况，比如 $\{4,3,2,1\}$ 和 $\{1,2,3,4\}$ 是同构的，因为其中一个翻转后可以得到另一个序列，所以我们还要除以 $2$，得到转移 $f_{i,j}\leftarrow f_{i,j}+f_{i-k,j-k+1}\times\dbinom{n-i+k-1}{k-1}\dfrac{k!}{2}$。

接下来考虑环的情况，$f_{i,j}$ 可以被 $f_{i-k,j-k}$ 转移得到，同理，我们需要在 $n-i+k$ 个点选出 $k$ 个点，钦定一个最小点的方案为 $\dbinom{n-i+k-1}{k-1}$，点的顺序是随意的，而这刚好是一个环，也就是圆排列的数量，得到转移 $f_{i,j}\leftarrow f_{i,j}+f_{i-k,j-k}\times\dbinom{n-i+k-1}{k-1}\dfrac{(k-1)!}{2}$。

接下来预处理组合数即可。

注意当链的长度为 $1$ 时，只有一种方案，当环的长度为 $2$ 时，只有一种方案，都不需要除以 $2$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll Maxn=610,Mod=1e9+7; 
ll fac[Maxn],Inv[Maxn];

inline ll ksm(ll a,ll b,ll mod){
	ll z=1;
	while(b){
		if(b&1) z=z*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return z;
}
inline ll C(ll n,ll m){
	if(m>n) return 0;
	return fac[n]*Inv[n-m]%Mod*Inv[m]%Mod;
}
inline ll up(ll x){
	return (x%Mod+Mod)%Mod;
}

ll f[Maxn][Maxn];

inline ll solve(ll n,ll m,ll l){
	memset(f,0,sizeof f);
	f[0][0]=1;
	for(ll i=1;i<=n;i++){
		for(ll j=0;j<=m;j++){
			for(ll k=1;k<=min(l,min(i,j+1));k++){
				f[i][j]=(f[i][j]+f[i-k][j-k+1]*C(n-i+k-1,k-1)%Mod*(k==1?1:Inv[2])%Mod*fac[k]%Mod)%Mod;
			}
			for(ll k=2;k<=min(l,min(i,j));k++){
				f[i][j]=(f[i][j]+f[i-k][j-k]*C(n-i+k-1,k-1)%Mod*(k==2?1:Inv[2])%Mod*fac[k-1]%Mod)%Mod;
			}
		}
	}
	return f[n][m]%Mod;
}

ll N,M,L;



int main(){
	scanf("%lld%lld%lld",&N,&M,&L);fac[0]=1;
	for(ll i=1;i<=Maxn-7;i++) fac[i]=fac[i-1]*i%Mod;
	Inv[Maxn-7]=ksm(fac[Maxn-7],Mod-2,Mod);
	for(ll i=Maxn-8;~i;i--) Inv[i]=Inv[i+1]*(i+1)%Mod;
	printf("%lld",up(solve(N,M,L)-solve(N,M,L-1)));
	return 0;
}




```


---

## 作者：EuphoricStar (赞：7)

首先进行一个容斥，把连通块最大值 $= K$ 变成 $\le K$ 的方案数减去 $\le K - 1$ 的方案数。

考虑 dp，设 $f_{i, j}$ 表示当前用了 $i$ 个点，$j$ 条边。转移即枚举其中一个连通块的大小 $k$。**为了不算重，我们强制让这个连通块包含点 $1$，类比状压中枚举包含 $\text{lowbit}(S)$ 的子集。**

- 如果这个连通块是环，那么给这个连通块标号 $1 \sim k$ 的方案数为 $\frac{(k - 1)!}{2}$，从 $f_{i - k, j - k}$ 转移。特别地，$2$ 元环的方案数为 $1$。
- 如果这个连通块是链，那么方案数为 $\frac{k!}{2}$，从 $f_{i - k, j - (k - 1)}$ 转移。

还要乘一个给这 $k$ 个点选择标号的方案数。$1$ 被确定一定要选，剩下 $i - 1$ 个标号要选 $k - 1$ 个，所以方案数就是 $\binom{i - 1}{k - 1}$。

时间复杂度 $O(n^3)$。

[code](https://atcoder.jp/contests/abc180/submissions/46571578)

---

## 作者：ttttalk (赞：6)

### [[ABC180F] Unbranched](https://www.luogu.com.cn/problem/AT_abc180_f)

题意非常清楚，就是问 $n$ 个点、$m$ 条边的构造中连通块最大大小恰好为 $l$ 的构造的方案数。

根据经验，我们可以设置 $f_{i,j}$ 的状态为 $i$ 个点、$j$ 条边的构造中连通块大小最大不大于 $l$ 的方案数。这时候发现最终答案的方案数包括了一部分不合法的，也就是连通块大小最大没有达到 $l$ 的。那让最大为 $l$ 的减去最大为 $l-1$ 的不就是恰好为 $l$ 的方案数了嘛。

这个图是由许多个连通分量构成的，所以我们可以遍历当前的连通分量，可以构成链或者是环。

如果当前的连通块是一条链，那么它的大小 $k$ 是由 $1$ 到 $l$ 的，所需要的边是 $k-1$ 条，所以状态是 $f_{i-k,j-k+1}$。如何选点，就是在 $n-i+k$ 个点里面选 $k$ 个。如此想法可能会和前面的有重复，那么就让当前的最小的点必须选，于是选点的方案数就变成了 $C_{n-i+k-1}^{k-1}$。考虑排列。序列的话是 $k!$，但由于每一条链都能找到一条同构的对称链，所以就得除以二。

故链的公式为 $f_{i,j}+=f_{i-k,j-k+1}\times C_{n-i+k-1}^{k-1} \times \frac{k!}{2}$。

考虑一个环，大小 $k$ 由 $2$ 到 $l$，所需的边是 $k$ 条，状态是 $f_{i-k,j-k}$。选点是一样的，然而圆排列比较麻烦。怎么办呢，那就先选择一个点，剩下的 $k-1$ 个点可以随意排列，那么不就是 $(k-1)!$ 嘛！这个题好像把对称的环也算成了一种，所以也得除以二。

故环的公式是 $f_{i,j}+=f_{i-k,j-k}\times C_{n-i+k-1}^{k-1} \times \frac{(k-1)!}{2}$。

由于这个题需要取模，所以需要预处理阶乘求逆元和组合数。

有一个小点，就是当链只有一个点、环只有两个点的时候，构造只有一种，就不用除以二了。

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=310,mod=1e9+7;
int n,m,l,f[N][N],fact[N],inv[N];
int qpow(int a,int n)
{
	int res=1;
	while (n)
	{
		if (n&1) res=res*a%mod;
		n/=2;
		a=a*a%mod;
	}
	return res%mod;
}
void init()
{
	fact[0]=1;
	for (int i=1;i<=n;i++) fact[i]=fact[i-1]*i%mod;
	inv[n]=qpow(fact[n],mod-2)%mod;
	for (int i=n;i>=1;i--) inv[i-1]=inv[i]*i%mod;
}
int C(int n,int m)
{
	return fact[n]*inv[n-m]%mod*inv[m]%mod;
}
int dd(int n,int m,int l)
{
	memset(f,0,sizeof f);
	f[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=m;j++)
		{
			for (int k=1;k<=min(min(l,i),j+1);k++)
			{
				f[i][j]=(f[i][j]+f[i-k][j-k+1]*C(n-i+k-1,k-1)%mod*fact[k]%mod*(k==1?1:inv[2])%mod)%mod;
			}
			for (int k=2;k<=min(l,min(i,j));k++)
			{
				f[i][j]=(f[i][j]+f[i-k][j-k]*C(n-i+k-1,k-1)%mod*fact[k-1]%mod*(k==2?1:inv[2])%mod)%mod;
			}
		}
	}
	return f[n][m]%mod;
}
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&l);
	init();
	printf("%lld\n",(dd(n,m,l)-dd(n,m,l-1)+mod)%mod);
   return 0;
}
```

---

## 作者：masterhuang (赞：2)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17316432.html)！第 $20$ 题。

第一个生成函数题解！

首先发现恰好 $L$ 不好做，于是差分：设 $sol(L)$ 表示（抛去原有第三个条件而后）连通块大小的最大值 $\le L$ 时的答案，于是答案为 $sol(L)-sol(L-1)$。

最大值 $\le L$ 就可以变为所有连通块大小都 $\le L$，就好做了。

考虑对于每个联通块第二个条件，发现每个连通块为**链或环**。这时候条件转化差不多了。

---

这时候不会真有人想 **dp** 吧？显然生成函数啊！由于有标号于是 **EGF**。

设链的 **EGF** 为 $f(x)=\sum\limits_{i\ge 0}a_i\dfrac{x^i}{i!}$，环的 **EGF** 为 $g(x)=\sum\limits_{i\ge 0}b_i\dfrac{x^i}{i!}$。
  
考虑链，发现：$a_0=0,a_1=1,a_i=\dfrac{i!}{2}(i\ge 2)$，这是因为是无向图，如果按 $i!$ 算，则每条链头尾都会被算一次，于是要除 $2$。
  
考虑环，有：$b_0=0,b_1=0,b_i=a_{i-1}(i\ge 2)$，考虑扔掉编号最大的点，就得到了一个 $i-1$ 的链，链加一个点连接头尾得到了环，于是这俩构成双射，这俩个数就一样。
  
---

求出 **EGF** 后考虑计算答案。设最终链有 $A$ 个，环有 $B$ 个。注意到每条链的点数减边数为 $1$，环为 $0$。于是得到 $A=n-m$，$0\le B\le n$。
  
考虑把两者 **EGF** 结合，发现是 $h(x)=f(x)^{n-m}\exp(g(x))$（不理解的可以想想 $\exp$ 的组合意义）。最后求得的就是 $n![x^n]h_n$。
  
但是你发现你 **WA** 了，然后发现多算了，这是因为你 $f(x)$ 快速幂的时候实际上把每条链做了个有标号 $1,2,\dots,n-m$，实际上要链与链要无标号（环你用 $\exp$ 已经做到了），于是最终要除个 $(n-m)!$，这下做完了。
  
---
  
如果用 **NTT** 那套做可以做到 $O(n\log n)$，但是不想写，写了个 $O(n^2\log n)$ 的快速幂，其他部分为 $O(n^2)$。
  
关于多项式 $\exp$ 如何做，我写（贺）个简洁的：

$F_0=0,G(x)=\exp (F(x))\Rightarrow G'(z) = F'(z) \exp F(z) = F'(z)G(z)\Rightarrow G_0 = 1, G_k =\dfrac{1}{k}\sum\limits_{i=1}^k iF_iG_{k-i}$
  
代码：  
```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1005,M=N-5,mod=1e9+7,I2=(mod+1)>>1;
int n,m,L,jc[N],inv[N],a[N],b[N],c[N],d[N],ans;
inline int md(int x){return x>=mod?x-mod:x;}
inline int ksm(int x,int p){int s=1;for(;p;(p&1)&&(s=1ll*s*x%mod),x=1ll*x*x%mod,p>>=1);return s;}
inline void mul(int *a,int *b,int n,int m)
{
	static int c[N];
	for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) c[i+j]=(c[i+j]+1ll*a[i]*b[j])%mod;
	for(int i=0;i<=n+m;i++) a[i]=c[i],c[i]=0;
}
inline void Exp(int *a,int *b,int n)
{
	b[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++) b[i]=(b[i]+1ll*a[j]*b[i-j]%mod*j)%mod;
		b[i]=1ll*ksm(i,mod-2)*b[i]%mod;
	}
}
inline void ksm(int *a,int *b,int n,int p)
{
	for(b[0]=1;p;p>>=1)
	{
		if(p&1){mul(b,a,n,n);for(int i=n;i<=2*n;i++) b[i]=0;}
		mul(a,a,n,n);for(int i=n;i<=2*n;i++) a[i]=0;
	}
}
inline int sol(int L)
{
	for(int i=1;i<=L;i++) a[i]=(i==1)?1:I2;ksm(a,c,n+1,n-m);
	for(int i=2;i<=L;i++) b[i]=(i==2)?I2:ksm(md(i+i),mod-2);Exp(b,d,n);
	mul(c,d,n,n);return 1ll*c[n]*jc[n]%mod*inv[n-m]%mod;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n>>m>>L;
	jc[0]=1;for(int i=1;i<=M;i++) jc[i]=1ll*jc[i-1]*i%mod;
	inv[M]=ksm(jc[M],mod-2);for(int i=M-1;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	ans=sol(L);for(int i=0;i<=M;i++) a[i]=b[i]=c[i]=d[i]=0;ans=md(ans+mod-sol(L-1));
	return cout<<ans,0;
}
```

---

## 作者：Xy_top (赞：2)

简单的 dpt。

首先每个点度数不能大于 $2$ 一定要好好利用，手推一下就能发现每个连通块一定是一个链或者环。

由于最多的连通块点的数量恰好为 $L$ 很难求，考虑求出不超过 $L$ 与不超过 $L-1$ 的，两者相减得出答案。

想到这个之后就很简单了，设 $f_{i,j}$ 为前 $i$ 个数用了 $j$ 条边且每个连通块点的数量都不超过 $L$ 的方案数，转移时枚举当前这个连通块有多少个节点，如果有 $k$ 个节点，那么选择方案就有 $C(n-i+k, k)$ 种，但是如果说有五个点 $1\cdots 5$，我选完 $1$ $2$ 再选 $3$ $4$ $5$ 组成一个连通块和先选 $3$ $4$ $5$ 组成连通块再选 $1$ $2$ 就会重复，所以每次连通块中向其分配一个当前最小的还没用过的就不会算重了。

选出 $k$ 个点组成链的方案数很简单，当 $k=1$ 就是 $1$，否则就是 $\frac{k!}{2}$。（因为可以把所有点排列一下，每个排列和它翻转过来性质又是相同的，所以除以 $2$，$k=1$ 的时候是特殊情况）

环的情况也相当简单，只不过可以把构成环的第一个点挪到最后构成一个性质相同的环，所以是 $\frac{(k-1)!}{2}$。

这题算组合数的时候也不能用快速幂，还要提前预处理好，不然会 T。

代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
#define int long long
using namespace std;
int n, m, l, res;
int dp[305][305], fac[305], inv[305];
const int mod = 1000000007;
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
int i (int x) {return q_pow (x, mod - 2);}
int C (int n, int m) {
	if (n < m || n < 0 || m < 0) return 0;
	return fac[n] * inv[n - m] % mod * inv[m] % mod;
}
signed main () {
	int tmp = 500000004;
	fac[0] = 1;
	For (i, 1, 300) fac[i] = fac[i - 1] * i % mod;
	inv[300] = q_pow (fac[300], mod - 2);
	foR (i, 299, 0) {
		inv[i] = inv[i + 1] * (i + 1) % mod;
	}
	dp[0][0] = 1;
	cin >> n >> m >> l;
	For (i, 1, n) {
		For (j, 0, min (n, m) ) {
			For (k, 1, min (i, l) ) {
				if (n - i + k > n) continue;
				if (j >= k - 1) {
					if (k == 1) dp[i][j] = (dp[i][j] + dp[i - k][j - (k - 1)]) % mod;
					else dp[i][j] = (dp[i][j] + dp[i - k][j - (k - 1)] * C (n - i + k - 1, k - 1) % mod * fac[k] % mod * tmp) % mod;//链
				}
				if (j >= k && k > 1) {
					if (k == 2) dp[i][j] = (dp[i][j] + dp[i - k][j - k] * C (n - i + k - 1, k - 1) ) % mod;
					else dp[i][j] = (dp[i][j] + dp[i - k][j - k] * C (n - i + k - 1, k - 1) % mod * fac[k - 1] % mod * tmp) % mod;
				}
			}
		}
	}
	res = dp[n][m];
	memset (dp, 0, sizeof dp);
	-- l;
	dp[0][0] = 1;
	For (i, 1, n) {
		For (j, 0, min (n, m) ) {
			For (k, 1, min (i, l) ) {
				if (n - i + k > n) continue;
				if (j >= k - 1) {
					if (k == 1) dp[i][j] = (dp[i][j] + dp[i - k][j - (k - 1)]) % mod;
					else dp[i][j] = (dp[i][j] + dp[i - k][j - (k - 1)] * C (n - i + k - 1, k - 1) % mod * fac[k] % mod * tmp) % mod;//链
				}
				if (j >= k && k > 1) {
					if (k == 2) dp[i][j] = (dp[i][j] + dp[i - k][j - k] * C (n - i + k - 1, k - 1) ) % mod;
					else dp[i][j] = (dp[i][j] + dp[i - k][j - k] * C (n - i + k - 1, k - 1) % mod * fac[k - 1] % mod * tmp) % mod;
				}
			}
		}
	}
	cout << (res - dp[n][m] + mod) % mod;
	return 0;
}
```


---

## 作者：Obviathy (赞：2)

>~~florr不好玩了（哪有hornex好玩），所以就玩着hornex写了这篇题解~~

## 题目描述

其实原题面写的很清楚了，我在把它简化一下：

> 给出 $n$ 个点，其中连接 $m$ 条边，使其成为若干条**链**或**环**，且满足最大的一块点数正好是 $L$。

## 题目分析

简单分析（~~观察标签~~）得到这个题是典型的动态规划，根据经验，我们就定义 $f_{i,j}$ 为选了 $i$ 个点，连了 $j$ 条边且最大连通块**不超过** $L$ 的答案。

什么？最大不超过 $L$？那一定会有情况最大值不是 $L$！

于是我们继续分析（~~继续观察标签~~），发现我们可以通过类似差分的套路，把答案容斥出来，即求出一个不超过 $L$ 的，再求出一个不超过 $L-1$ 的，两个答案一减不就是最大值刚好是 $L$ 的了吗！

所以基本想法就是求两边 $f_{n,m}$ 做差。现在应该想想 $f$ 怎么求了。

还是惯用的套路，考虑枚举最后一个连通块由几个点组成，在此设其为 $k$。

首先知道，$k$ 个点的链一定有 $k-1$ 条边，$k$ 个点的环一定有 $k$ 条边，那么我们就分开求就好。

那么就得到状态转移方程大概的模样：

对于链：
$$f_{i,j}=\sum f_{i-k,j-k+1}\times A$$
对于环：
$$f_{i,j}=\sum f_{i-k,j-k}\times B$$

然后考虑后面的两个未知的量。

首先，这两个量是为了干什么的？很显然，是计算对于我们钦定的最后一个大小为 $k$ 的联通块，它也有很多种不同的选择方式，我们就需要计算出来做乘法。

然后考虑它该怎么计算。

### 先研究是一条链的

我们第一眼看上去，就是先从除该连通块之前已经定下的点外剩下 $n-i+k$ 个点里选 $k$ 个，然后排列，得到：

$$\dbinom{n-i+k}{k}k!$$

但显然它凭什么对啊！我们知道图是可以翻转对称的，所以说像 $1-2-3$ 和 $3-2-1$ 不是同一个排列但是同一个图，所以应该是 $\dfrac{k!}{2}$

然后看看前面的，我们是在不断地枚举联通块的，谁也不能保证之前就没有选过大小也是 $k$ 的块，如果这两个块互相选了同一些数，那么就重复了对吧。那就考虑用一些技巧，把它改成：

$$\dbinom{n-i+k-1}{k-1}$$

为什么减 $1$ 就行了呢？考虑我们钦定让没选过得最小的元素一定选，那么就保证了后面的不会与其重复。

于是完善一下，对于连通块是链，有：

$$f_{i,j}=\sum f_{i-k,j-k+1}\cdot\dbinom{n-i+k-1}{k-1}\dfrac{k!}{2}$$

### 然后看看是环的

其实环与链的处理差不多，因为选数是一样的，所以我们只看在选好了之后环里面有几种排列方式。考虑长度为 $k$ 的圆排列 $(k-1)!$，在考虑其翻转对称，就是 $\dfrac{(k-1)!}{2}$，所以：

对于连通块是环，有：

$$f_{i,j}=\sum f_{i-k,j-k}\cdot\dbinom{n-i+k-1}{k-1}\dfrac{(k-1)!}{2}$$

### 于是我们就基本做出来了

最后处理一下逆元就行了。时间复杂度 $O(NML)$。

## AC code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 305,M = 305,mod = 1e9+7;
ll n,m,l,inv2;
ll f[N][M],f1[N][M];
ll fact[N],inv[N];
inline ll ksm(ll a,ll k){
	ll res = 1;
	while(k){
		if(k & 1)res = res * a % mod;
		a = a * a % mod;
		k >>= 1; 
	}
	return res;
}
void init(int n){
	inv2 = ksm(2,mod-2);
	fact[0] = 1;
	for(int i = 1;i <= n;i ++)fact[i] = fact[i-1] * i % mod;
	inv[n] = ksm(fact[n],mod - 2);
	for(int i = n;i >= 1;i --)inv[i-1] = inv[i] * i % mod;
}
inline ll C(ll x,ll y){
	return fact[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
	f[0][0] = f1[0][0] = 1;
	cin >> n >> m >> l;
	init(n);
	for(ll i = 1;i <= n;i ++){
		for(ll j = 0;j <= m;j ++){
			for(ll k = 2;k <= min(l,min(i,j));k ++)f[i][j] = (f[i][j] + (f[i-k][j-k]*C(n-i+k-1,k-1)%mod)*(fact[k-1]*(k> 2?inv2:1)%mod)%mod)%mod;
			for(ll k = 1;k <= min(l,min(i,j+1));k ++)f[i][j] = (f[i][j] + f[i-k][j-k+1]*C(n-i+k-1,k-1)%mod*(fact[k]*(k>=2?inv2:1)%mod)%mod)%mod;
		}
	}
	for(ll i = 1;i <= n;i ++){
		for(ll j = 0;j <= m;j ++){
			for(ll k = 2;k <= min(l-1,min(i,j));k ++)f1[i][j] = (f1[i][j] + (f1[i-k][j-k]*C(n-i+k-1,k-1)%mod)*(fact[k-1]*(k> 2?inv2:1)%mod)%mod)%mod;
			for(ll k = 1;k <= min(l-1,min(i,j+1));k ++)f1[i][j] = (f1[i][j] + f1[i-k][j-k+1]*C(n-i+k-1,k-1)%mod*(fact[k]*(k>=2?inv2:1)%mod)%mod)%mod;
		}
	}
	cout << (f[n][m]-f1[n][m]+mod)%mod << endl;
	return 0;
}
```

---

## 作者：Register_int (赞：1)

~~感谢 Daniel_lele 在我打 florr 的时候把我拖过来做题~~

首先设 $dp_{i,j}$ 为用了 $i$ 个点 $j$ 条边组成的图的个数。为了防止算重，钦定每个连通块的第一个点为当前没被选的第一个点，则选点的方案就是在剩下的点中选点。那么转移方程就大概是这样的：

$$dp_{i,j}=\sum^l_{k=1}\binom{n-i+k-1}{k-1}\times\text{不清楚}\times dp_{i-k,j-\text{不知道}}$$

接下来结合题目中给的条件。由所有点度数不超过 $2$ 可得，每个连通块只有环和链两种情况。设 $f(n),g(n)$ 分别为 $n$ 个点组成链与环的方案数，可得：

$$
f(n)=\left\{
\begin{matrix}
1,&n=1\\
\dfrac{n!}2,&n>1
\end{matrix}
\right.,g(n)=\left\{
\begin{matrix}
1,&n=2\\
\dfrac{(n-1)!}2,&n>2
\end{matrix}
\right.
$$

推导过程简单这里不再赘述。那么最终转移式为：

$$
\begin{aligned}
dp_{i,j}=&\sum^l_{k=1}\binom{n-i+k-1}{k-1}f(n)dp_{i-k,j-k+1}\\
+&\sum^l_{k=2}\binom{n-i+k-1}{k-1}g(n)dp_{i-k,j-k}
\end{aligned}
$$

~~写完这一大坨就会发现样例都过不去~~

为啥呢？因为我们只能保证最大的连通块点数 **不超过** $l$，所以会多算点数 $<l$ 的答案。统计一遍 $l-1$ 的答案从里面扣掉就可以了。

代码有点丑，压行比较严重。

# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e2 + 10;
const int mod = 1e9 + 7;
const int inv2 = mod + 1 >> 1;

inline 
ll inv(ll b, ll p = mod - 2) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = inv(fac[n]);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(ll n, ll m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

ll dp[MAXN][MAXN];

inline 
ll calc(int n, int m, int l) {
	memset(dp, 0, sizeof dp), **dp = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int k = 1; k <= min({ l, i, j + 1 }); k++) {
				dp[i][j] = (dp[i][j] + dp[i - k][j - k + 1] * c(n - i + k - 1, k - 1) % mod * fac[k] % mod * (k > 1 ? inv2 : 1) % mod) % mod;
			}
			for (int k = 2; k <= min({ l, i, j }); k++) {
				dp[i][j] = (dp[i][j] + dp[i - k][j - k] * c(n - i + k - 1, k - 1) % mod * fac[k - 1] % mod * (k > 2 ? inv2 : 1) % mod) % mod;
			}
		}
	}
	return dp[n][m];
}

int n, m, l;

int main() {
	scanf("%d%d%d", &n, &m, &l), init(n);
	printf("%lld", (calc(n, m, l) - calc(n, m, l - 1) + mod) % mod);
}
```

---

## 作者：y3kkc (赞：1)

## 题意  
求 $N$ 个点，$M$ 条边且满足以下条件的图的数量：  
1. 图中无自环。  
2. 每个点度数最多为 2。  
3. 所有连通块中，节点最多的恰好有 $L$ 个点。  

答案对 $10 ^9 + 7$ 取模，顶点有标号。  

## 分析
比较常见的对图的计数 dp，我们要摸清这一类题的套路。  

首先看这题的三个限制条件：  
1. 嗯，没什么好说的。  
2. 每个点度数最多为 2，这个限制条件乍一看非常阴间，但实际上你想象一下这种情况下构成的图中，不难发现图中每个连通块要么是环，要么是链。  
3. 直接求节点恰好有 $L$ 个的不好直接求，而在计数 dp 中有一种常见的套路（~~虽然我当时还不太会~~），就是将恰好转换为 $\le L$，我们在求个 $\le L - 1$ 的答案，将二者作差，即为恰好等于 $L$ 的答案。 

将第三个限制条件转换后我们就可以设状态了。  
状态很显然，点和边肯定要设上，本来可能还需要设 $L$ 的，但是我们转换条件后就可以直接在转移中体现了。  
故设计状态为 $f_{i,j}$ 表示用了 $i$ 个点，$j$ 条边的合法方案数。  
对于顶点有标号的题目，我们不妨假设编号为 1 的点在上个状态还未加入统计，即设**基准点**。  
这样可以确保新增的状态不会重复统计（因为有 1 必然与之前的图不同），做到**不重不漏**。  
如此一来，我们只需围绕 1 构造一个整体即可。  

链和环的情况差差不多，这里就分析 1 组成的整体为链的情况。  
先常规操作枚举 $i$，$j$，$k$ 代表用了 $i$ 个点 $j$ 条边的方案数。$k$ 即为 1 所在链的点数。  
这里要注意 $k$ 要小于等于 $\min(l, i, j + 1)$（后两个不必说，小于等于 $L$ 是确保最大连通块点数小于等于 $L$）。  

那么剩下的点和边组成合法图的方案数为 $f_{i-k,j-k+1}$。 
接下来计算组成链的方案数。  

$n$ 个点中，有 $i - k$ 个点一定不能在链中，又已经确定了一个 1，所以能选的点数就为 $n - i + k - 1$。  

我们要选的点数就是除了 1 外还有 $k - 1$个点。  

所以选点的方案数即为 $\binom{n - i + k - 1}{k - 1}$。  

考虑这 $k$ 个点组成链的方案数。  
很显然这是个排列——但不完全是个排列。  
注意到 $1-2-3$ 实际上跟 $3-2-1$ 是相同的，即可能出现对称的情况。  
所以我们要将 $k!$ 除以 $2$, 但又不能完全除以 $2$, 因为若 $k = 1$ 是不会对称的，所以这里要特判。  
所以状态转移为：  
$f_{i,j} = \sum_{k=1}^{\min(l,i,j+1)}f_{i-k,j-k+1} \times \binom{n-i+k-1}{k-1} \times \frac{k!}{2}$($k > 1$)。  

环的情况自己分析一下吧。  
## 代码  
```cpp  
#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
#define inv2 500000004
using namespace std;
namespace Faster {
// char buf[1 << 23], *p1 = buf, *p2 = buf;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 23, stdin), p1 == p2) ? EOF : *p1++)
inline int read() {
    int num = 0, sgn = 1;
    char ch = getchar();
    for (; ch < 48 || ch > 57; ch = getchar())
        if (ch == '-')
            sgn = -1;
    for (; ch >= 48 && ch <= 57; ch = getchar()) num = (num << 3) + (num << 1) + (ch & 15);
    return sgn * num;
}
inline void write(int num) {
    static int sta[39], top = 0;
    if (num < 0)
        putchar('-'), num *= -1;
    do
        sta[++top] = num % 10, num /= 10;
    while (num);
    while (top) putchar(sta[top--] | 48);
    return;
}
}  // namespace Faster
using namespace Faster;
const int mod = 1e9 + 7;
const int N = 300 + 9;
int n, m, l;
int f[N][N];
int C[N][N], fac[N];
void init() {
    fac[0] = 1;
    C[0][0] = 1;
    for (int i = 1; i <= 300; ++i) C[i][0] = C[i][i] = 1, fac[i] = fac[i - 1] * i % mod;
    for (int i = 1; i <= 300; ++i) {
        for (int j = 1; j < i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    return;
}
signed main() {
    init();
    n = read(), m = read(), l = read();
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 1; k <= min({ l, i, j + 1 }); ++k) {  //链
                f[i][j] = (f[i][j] + (f[i - k][j - k + 1] * C[n - i + k - 1][k - 1] % mod * fac[k] % mod *
                                      (k > 1 ? inv2 : 1) % mod) %
                                         mod) %
                          mod;
            }

            for (int k = 2; k <= min({ l, i, j }); ++k) {  //环
                f[i][j] = (f[i][j] + (f[i - k][j - k] * C[n - i + k - 1][k - 1] % mod * fac[k - 1] % mod *
                                      (k > 2 ? inv2 : 1) % mod) %
                                         mod) %
                          mod;
            }
        }
    }
    int res = f[n][m];
    memset(f, 0, sizeof f);
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int k = 1; k <= min({ l - 1, i, j + 1 }); ++k) {
                f[i][j] = (f[i][j] + (f[i - k][j - k + 1] * C[n - i + k - 1][k - 1] % mod * fac[k] % mod *
                                      (k > 1 ? inv2 : 1) % mod) %
                                         mod) %
                          mod;
            }

            for (int k = 2; k <= min({ l - 1, i, j }); ++k) {
                f[i][j] = (f[i][j] + (f[i - k][j - k] * C[n - i + k - 1][k - 1] % mod * fac[k - 1] % mod *
                                      (k > 2 ? inv2 : 1) % mod) %
                                         mod) %
                          mod;
            }
        }
    }
    printf("%lld\n", (res - f[n][m] + mod) % mod);
    return 0;
}
```

---

## 作者：OIerBoy (赞：0)

# Sol
对于处理方案数问题，我们很容易想到用 dp 解决。

记 $f_{i,j}$ 表示有 $i$ 个点，$j$ 条边时的方案数为多少。转移就是每一次枚举新增 $k$ 个点为一个连通块，边数就是 $k,k-1$，即环和链的情况。

我们还需要考虑去重，因为我们每一次加入去之前相同大小的联通块，就会出现重复计算的情况。如一种方案是先加入 $\{a\}$ 再加入 $\{b\}$，但还存在一种方案是将两者顺序调换过来。对于这种情况我们的处理其实也很简单，我们只需要每次钦定必须将未加入的数中的编号最小的数加入就可以解决了。

对于加入的连通块本身我们也需要去重。

- 对于链，可以能会存在对称相等的情况，我们需要将点数大于 $1$ 的除以 $2$。
- 对于环，可以能会存在旋转相等的情况，我们需要将点数大于 $2$ 的除以连通块大小。

这样我们就可以得到具体的 dp 转移式子了：
$$f_{i,j}\displaystyle\gets_{k=1}^{\min(i,L)} \begin{cases}\dbinom{n-i+k-1}{k-1}k!\times f_{i-k,j-k+1} & j\ge k-1,k=1\\ \\ \dfrac{\dbinom{n-i+k-1}{k-1}k!\times f_{i-k,j-k+1}}{2} & j\ge k-1,k>1\\ \\ \dbinom{n-i+k-1}{k-1}(k-1)!\times f_{i-k,j-k} & j\ge k,k=2\\ \\ \dfrac{\dbinom{n-i+k-1}{k-1}(k-1)!\times f_{i-k,j-k}}{2} & j\ge k,k>2\end{cases}$$

最后，这里我们 $f_{i,j}$ 的方案数其实是记的连通块大小最大的至多为 $L$ 的，而我们需要保证最大连通块大小为 $L$，就需要在 dp 一个最大连通块至多为 $L-1$ 的方案数，两者相减即为答案。

# Code
```cpp
#include<bits/stdc++.h>
#define inf LONG_LONG_MAX
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
#define int long long
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}inline void write(auto x){
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
#define N 405
#define Mod 1000000007
int n,m,k;
int f[N][N];
int fac[N],inv[N];
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%Mod;
		a=a*a%Mod;b>>=1;
	}return res;
}
int C(int n,int m){return fac[n]*inv[m]%Mod*inv[n-m]%Mod;}
void init(int n){
	fac[0]=1;
	For(i,1,n)fac[i]=fac[i-1]*i%Mod;
	inv[n]=ksm(fac[n],Mod-2);
	FOR(i,n,1)inv[i-1]=inv[i]*i%Mod;
}
int dp(int k){
	mem(f,0);f[0][0]=1;
	For(i,1,n)
	For(j,0,m)
	For(l,1,min(i,k)){
		int c=C(n-i+l-1,l-1);
		if(j>=l-1){
			if(l>1)f[i][j]+=c*fac[l]%Mod*inv[2]%Mod*f[i-l][j-l+1]%Mod;
			else f[i][j]+=c*fac[l]%Mod*f[i-l][j-l+1]%Mod;
			f[i][j]%=Mod;
		}if(j>=l&&l>=2){
			if(l>2)f[i][j]+=c*fac[l-1]%Mod*inv[2]%Mod*f[i-l][j-l]%Mod;
			else f[i][j]+=c*fac[l-1]%Mod*f[i-l][j-l]%Mod;
			f[i][j]%=Mod;
		}
	}return f[n][m];
}
signed main(){
	cin>>n>>m>>k;init(400);
	int ans=(dp(k)-dp(k-1)+Mod)%Mod;
	cout<<ans;
	return 0;
}
```

---

## 作者：Felix72 (赞：0)

图不一定连通，于是分一个一个联通块来加，组合数解决标号问题。考虑到度的限制，发现只能是链或者环，于是上排列和圆排列。这样是有重复的，因为先后加入的顺序对最终形态无影响。那么强制选标号最小的点，也就是组合数少取一即可。

如此解决了所有重复问题，但是没考虑最大块一定是定值的限制。这个也好办，把 $L$ 减一再算一次，两次结果相减即得。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 310, mod = 1000000007;
long long n, m, l, f[N][N], g[N][N], pre[N], C[N][N], inv[N], ans1, ans2;
inline void exgcd(long long a, long long b, long long &x, long long &y)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return ;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
inline long long Inv(long long num)
{
	long long x, y;
	exgcd(num, mod, x, y);
	x = (x % mod + mod) % mod;
	return x;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	C[0][0] = 1, pre[0] = 1;
	for(int i = 1; i <= 300; ++i)
	{
		inv[i] = Inv(i);
		C[i][0] = 1; pre[i] = pre[i - 1] * i % mod;
		for(int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
	}
	cin >> n >> m >> l;
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 0; j <= m; ++j)
		{
			for(int k = 1; k <= l; ++k)
			{
				if(k > i) continue;
				if(j >= k - 1) f[i][j] = (f[i][j] + C[n - (i - k) - 1][k - 1] * f[i - k][j - (k - 1)] % mod * pre[k] % mod * ((k == 1) ? 1 : inv[2]) % mod) % mod;
				if(j >= k && k > 1) f[i][j] = (f[i][j] + C[n - (i - k) - 1][k - 1] * f[i - k][j - k] % mod * pre[k - 1] % mod * ((k <= 2) ? 1 : inv[2]) % mod) % mod;
			}
		}
	}
	ans1 = f[n][m];
	memset(f, 0, sizeof(f));
	--l;
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		for(int j = 0; j <= m; ++j)
		{
			for(int k = 1; k <= l; ++k)
			{
				if(k > i) continue;
				if(j >= k - 1) f[i][j] = (f[i][j] + C[n - (i - k) - 1][k - 1] * f[i - k][j - (k - 1)] % mod * pre[k] % mod * ((k == 1) ? 1 : inv[2]) % mod) % mod;
				if(j >= k && k > 1) f[i][j] = (f[i][j] + C[n - (i - k) - 1][k - 1] * f[i - k][j - k] % mod * pre[k - 1] % mod * ((k <= 2) ? 1 : inv[2]) % mod) % mod;
			}
		}
	}
	ans2 = f[n][m];
	cout << ((ans1 - ans2) % mod + mod) % mod << endl;
	return 0;
}
```

---

## 作者：free_fall (赞：0)

首先每个点的度数最大为 2，说明这些连通图不是环就是链，而且不包含自环（但是有重边，不过重边可以看做是有两个点的环）。

很明显这是一道计数 DP，因为有了最多的连通图的节点数为 $L$ 的限制使得直接求解答案变得困难，我们可以将它拆分为两个子问题：所有连通图节点数不超过 $L$ 的答案，所有连通图节点数不超过 $L-1$。将这两个子问题的答案相减即为最终的答案。

接下来就是状态，我们用 $f_{i,j}$ 表示选了 $i$ 个点（包括 1 号节点），$j$ 条边的方案数，进行转移时分为环和链两步。

将 $i$ 个点用 $i$ 条边组成一个环，我们可以固定其中的一个节点，然后将剩下的 $i-1$ 个节点排列接到这个节点的后面，一共有 $(i-1)!$ 种，但是同一个环对称计算了两次，所以最终的组合数量为 $\frac{(i-1)!}{2} $。注意当 $i$ 小于等于 2 时要特判。

同理，将 $i$ 个点用 $i-1$ 条边组成一条链，我们将 $i$ 个点排列然后一次连接，构成了 $i!$ 条链，但是同一条链前后计算了两次，最终组成了 $\frac{i!}{2}$ 条链。当 $i$ 为 1 时记得特判。

设 $tmp1$ 是环的方案数，$tmp2$ 是链的方案数，当 $f_{i,j}$ 从 $f_{k,j}$ 转移而来时，$f_{i,j}=f_{i,j}+C_{i-1}^{k-1} \times f_{k,j}\times(tmp1+tmp2)$。

时间复杂度为 $O(n^3)$。

---

