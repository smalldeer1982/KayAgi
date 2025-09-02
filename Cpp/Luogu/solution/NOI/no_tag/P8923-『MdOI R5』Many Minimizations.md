# 『MdOI R5』Many Minimizations

## 题目背景

本题不是多项式题，建议先做 E。

[![2.gif](https://i.postimg.cc/3JN9j60M/2.gif)](https://postimg.cc/xcrKn6Pg)

## 题目描述

小 L 遇到了一个经典题：给定一个长度为 $n$ 的**整数**序列 $a$，你需要在所有**单调不降**的**实数**序列中选出一个作为 $b$，最小化 $\sum\limits_{i=1}^n |a_i-b_i|$。可以证明答案是整数。

他一眼就秒了这个题：这不是保序回归板子吗！

他觉得这题太水了，于是决定加强一下：

对于所有长度为 $n$ 的且满足 $\forall i\in[1,n],a_i\in[1,m]$ 的**整数**序列 $a$，求出上面这个问题的答案的总和对**质数** $p$ 取模后的结果。其中 $n,m,p$ 是给定的常数。

这下小 L 不会了。为了不让你看出来他根本就不会，他随便写了一个数据范围就把这题扔给你做了。

现在压力来到了你这边，你能否顺利切掉这个题呢？

## 说明/提示

对于 $100\%$ 的数据，$1\le n\le 5\times 10^3$，$1\le m\le 10^9$，$10^9<p\le 1.01\times 10^9$，保证 $p$ 是质数。

$\operatorname{Subtask} 1(10\%)$：$n,m\le 7$。

$\operatorname{Subtask} 2(10\%)$：$m\le 2$。

$\operatorname{Subtask} 3(10\%)$：$n,m\le 50$。

$\operatorname{Subtask} 4(10\%)$：$n\le 50$。

$\operatorname{Subtask} 5(10\%)$：$n,m\le 500$。

$\operatorname{Subtask} 6(10\%)$：$n\le 500$。

$\operatorname{Subtask} 7(10\%)$：$m\le 5\times 10^3$。

$\operatorname{Subtask} 8(30\%)$：无特殊限制。

#### 样例说明 1

有以下 $8$ 种可能的情况：

$a=(1,1,1),b=(1,1,1),ans=0$。

$a=(1,1,2),b=(1,1,2),ans=0$。

$a=(1,2,1),b=(1,1,1),ans=1$。

$a=(1,2,2),b=(1,2,2),ans=0$。

$a=(2,1,1),b=(1,1,1),ans=1$。

$a=(2,1,2),b=(1,1,2),ans=1$。

$a=(2,2,1),b=(2,2,2),ans=1$。

$a=(2,2,2),b=(2,2,2),ans=0$。

因此答案为 $0+0+1+0+1+1+1+0=4$。

注意，对于一个固定的 $a$，最优的 $b$ 不一定唯一。上面只给出了一种可能的解。

$\operatorname{Bonus}$：在 $p$ 为 NTT 模数的情况下做到 $O(n\log n)$。实际上在本题正解的基础上这一部分并不困难。

## 样例 #1

### 输入

```
3 2 1000000007```

### 输出

```
4```

## 样例 #2

### 输入

```
5 5 1000000007```

### 输出

```
11040```

## 样例 #3

### 输入

```
50 50 1000000009```

### 输出

```
875463033```

# 题解

## 作者：Kubic (赞：8)

先考虑给定 $a$ 怎么算出答案。

设 $f_{i,j}$ 表示当前考虑到 $i$，且 $b_i=j$ 的答案。

$$f_{i,j}=\min\limits_{k\le j}\{f_{i-1,k}\}+|a_i-j|$$

可以发现对于每一个 $i$，$f$ 是一个下凸函数，那么可以考虑一个经典套路：用堆维护所有斜率增加 $1$ 的断点。

同时设 $mn_i=\min\{f_{i,j}\}$。

每次操作相当于是往堆中**先**加入两个 $a_i$ **然后**弹出最大值 $mx$，可以发现 $mn_i=mn_{i-1}+mx-a_i$。

去掉一些可以快速计算的东西之后，我们实际上只需要考虑过程结束时堆中剩下的数之和。

我们考虑拆开每个数的贡献。具体地，钦定一个 $x\in [0,m]$，并把 $\le x$ 的数设为 $0$，$>x$ 的数设为 $1$。

现在只需要对所有 $x$ 算出答案之和即可。

对于一个 $x$，设 $g_{i,j}$ 表示当前考虑到 $i$，当前堆中有 $j$ 个 $1$ 的方案数。

每次操作有 $x$ 种方案减少一个 $1$，有 $m-x$ 种方案增加一个 $1$。特别地，任意时刻 $1$ 的个数会对 $0$ 取 $\max$。

可以发现，每一个 $g_{i,j}$ 都是一个关于 $x$ 的不超过 $n$ 次的多项式，直接暴力维护这些多项式即可做到 $O(n^3)$ 的复杂度。

但这还不够，我们需要进一步优化这个算法。

考虑把这个问题转化为格路计数。

对于一条当前意义下的路径，每次找到第一个对 $0$ 取 $\max$ 的位置并把它前面的部分全部往上平移一格。

这样我们就把对 $0$ 取 $\max$ 的要求去掉了。可以发现这两种路径是一一对应关系。

此时问题转化为了：

- 起点为横坐标为 $0$ 的任意一个点。
- 每次有 $x$ 种方案往右下，有 $m-x$ 种方案往右上走。
- 终点为横坐标为 $n$ 的任意一个点。
- 路径上所有点纵坐标都 $\ge 0$ 且至少有一个点纵坐标为 $0$。

设走到 $(n,i)$ 的方案数为 $w_i$。我们要求的是 $\sum\limits_i i\times w_i$。

路径上至少有一个点纵坐标为 $0$ 这个限制比较麻烦，我们将其容斥掉。

令 $w_i=w_{0,i}-w_{1,i}$，其中 $w_0$ 和 $w_1$ 分别描述纵坐标都 $\ge 0$ 和纵坐标都 $\ge 1$ 的情况。

根据经典的反射容斥方法可以得到：

$$w_{0,i}=\sum\limits_{i+2j\ge n}x^j(m-x)^{n-j}\left(\dbinom{n}{j}-\dbinom{n}{i+j+1}\right)$$

$$w_{1,i}=\sum\limits_{i+2j\ge n}x^j(m-x)^{n-j}\left(\dbinom{n}{j}-\dbinom{n}{i+j}\right)$$

$$w_i=w_{0,i}-w_{1,i}=\sum\limits_{i+2j\ge n}x^j(m-x)^{n-j}\left(\dbinom{n}{i+j}-\dbinom{n}{i+j+1}\right)$$

代回我们要求的式子里可以得到：

$$\sum\limits_{i\ge 0} w_i\times i=\sum\limits_{i\ge 0} i\sum\limits_{i+2j\ge n}x^j(m-x)^{n-j}\left(\dbinom{n}{i+j}-\dbinom{n}{i+j+1}\right)$$

$$=\sum\limits_{i\ge 0} x^i(m-x)^{n-i}\sum\limits_{j\ge\max\{i,n-i\}} (j-i)\left(\dbinom{n}{j}-\dbinom{n}{j+1}\right)$$

推到这里，我们已经可以非常简单地在 $O(n^2)$ 的时间复杂度内求出这个多项式。

再用你喜欢的方式求出自然数幂和带进多项式计算，时间复杂度 $O(n^2)$。

进一步地，可以用卷积求出这个多项式，然后将自然数幂和代入计算。时间复杂度 $O(n\log n)$。

参考代码（$O(n^2)$）：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 5005
int n,m,MOD,ans,pw[N],inv[N],z[N],bn[N][N],o[N][N];
void W(int &x,int y) {x+=y;if(x>=MOD) x-=MOD;}
int add(int x,int y) {x+=y;return x<MOD?x:x-MOD;}
int qPow(int x,int y)
{
	int res=1;
	for(;y;y/=2,x=1ll*x*x%MOD) if(y&1)
		res=1ll*res*x%MOD;return res;
}
void init(int n)
{
	pw[0]=o[0][0]=1;
	for(int i=1;i<=n;++i) pw[i]=1ll*pw[i-1]*m%MOD;
	for(int i=1;i<=n+1;++i)
		inv[i]=i>1?1ll*inv[MOD%i]*(MOD-MOD/i)%MOD:1;
	for(int i=0;i<=n;++i) for(int j=0;j<=i;++j)
		bn[i][j]=j?add(bn[i-1][j],bn[i-1][j-1]):1;
	for(int i=1;i<=n;++i) for(int j=1;j<=i;++j)
		o[i][j]=(1ll*o[i-1][j]*j+o[i-1][j-1])%MOD;
}
int main()
{
	scanf("%d %d %d",&n,&m,&MOD);init(n);
	for(int i=0,t1,t2;i<=n;++i)
	{
		t1=0;
		for(int j=max(i,n-i);j<=n;++j)
			W(t1,1ll*(j-i)*(bn[n][j]-bn[n][j+1]+MOD)%MOD);
		for(int j=0;j<=n-i;++j)
		{
			t2=1ll*t1*bn[n-i][j]%MOD*pw[n-i-j]%MOD;
			W(z[i+j],(j&1?MOD-t2:t2));
		}
	}
	for(int i=0,t1,t2;i<=n;++i)
	{
		t1=0;t2=1;
		for(int j=0;j<=i;++j)
		{
			t2=1ll*t2*(m-j+1)%MOD;
			W(t1,1ll*t2*o[i][j]%MOD*inv[j+1]%MOD);
		}W(ans,1ll*t1*z[i]%MOD);
	}ans=add(MOD-ans,1ll*m*(m+1)/2%MOD*n%MOD*qPow(m,n-1)%MOD);
	printf("%d\n",ans);return 0;
}
```

---

## 作者：dead_X (赞：3)

## 前言
死去的保序回归突然攻击我。
## 题解

我们发现这题的原问题居然是原题 P4331。

考虑第一篇题解的做法：

- 维护一个堆，一开始为空。
- 对于每个 $a_i$，先向堆中加入 $a_i$。
- 再取出堆中最大的数 $x$，放回 $a_i$。
- 答案加上 $x-a_i$。

直接维护堆比较困难，不难想到差分，即第三步改为如果 $x\leq t<a_i$ 就计入贡献。

这样我们就可以将 $a_i$ 的值域减小到 $[0,1]$，堆里只需要维护有几个 $1$ 即可。

现在 $1$ 的效果是加入一个 $1$，$0$ 的效果是如果有 $1$ 就减少一个 $1$。

那么我们已经通过 dp 在 $O(n^2)$ 的时间复杂度内对于一个 $t$ 求值了。

不难发现答案一定是 $t$ 的 $n$ 次多项式，我们只需要求 $n+2$ 个值就可以得到答案。

这样是 $O(n^3)$ 的，有更好的方法吗？

考虑如果我们不能从在没有 $1$ 的时候放 $0$，问题就是经典的反射容斥。

假设我们执行了 $t$ 次操作，考虑将原问题转化为从 $(0,t)$ 走到 $x=n$ 且必须经过 $y=0$ ，不难发现和原问题等价，而一条从 $(0,x)$ 到 $(n,y)$ 的路径贡献为 $\frac{n-x-y}{2}$。

这样就能做到 $O(n^2)$ 了。

## 代码

没用 Barrett，跑的很慢。

```cpp
//不回家了，我们去鸟巢！
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int n=read(),m=read(),p=read();
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
struct Lagrange
{
	int F[5003],G[5003],H[5003],x[5003],y[5003];
	signed main(int n,int x0)
	{
		F[0]=1;
		for(int i=1; i<=n; ++i) 
		{
			for(int j=0; j<i; ++j)
				G[j]=(G[j]+p-1ll*F[j]*x[i]%p)%p,
				G[j+1]=(G[j+1]+F[j])%p;
			for(int j=0; j<=i; ++j) F[j]=G[j],G[j]=0;
		}
		for(int i=1; i<=n; ++i)
		{
			for(int j=0; j<=n; ++j) G[j]=F[j];
			int S=1;
			for(int j=1; j<=n; ++j)
				if(j!=i) S=1ll*S*(p+x[i]-x[j])%p;
			S=1ll*qp(S,p-2)*y[i]%p;
			for(int j=n-1; j>=0; --j)
				H[j]=(H[j]+1ll*G[j+1]*S)%p,
				G[j]=(G[j]+1ll*G[j+1]*x[i])%p;
		}
		int ans=0;
		for(int i=0,t=1; i<n; ++i,t=1ll*t*x0%p)
			ans=(ans+1ll*t*H[i])%p;
		return ans;
	}
}T;
int C[5003][5003],A[5003];
int G(int x,int y)
{
	if(y<-x||y>x) return 0;
	return C[x][(x+y)>>1];
}
int F(int x,int y){return (p+G(n,-y-x)-G(n,-y-x-2))%p;}
signed main()
{
	int ans=0;
	for(int i=0; i<=n; ++i)
	{
		C[i][0]=1;
		for(int j=1; j<=i; ++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	}
	for(int i=0; i<=n; ++i)
		for(int j=0; i+j<=n; ++j)
			if((n+i+j+1)&1)
				A[i+((n-i-j)>>1)]=(A[i+((n-i-j)>>1)]
				+1ll*F(i,j)*((n-i-j)>>1))%p;
	for(int i=1; i<=n+2&&i<m; ++i)
	{
		int w=qp(m-i,n),t=1ll*i*qp(m-i,p-2)%p;
		for(int j=0; j<=n; ++j,w=1ll*w*t%p)
			ans=(ans+1ll*A[j]*w)%p;
		T.x[i]=i,T.y[i]=ans;
	};
	printf("%d\n",T.main(n+2,m-1));
	return 0;
}
```

---

## 作者：yyyyxh (赞：1)

双倍经验 ARC163F/P8923。

讲下本题 Bonus 部分 $O(n\log n)$ 且复杂度与 $m$ 几乎无关的做法。

不难发现让我们计数的问题是保序回归 $L_1$ 中一条链的情况。这个情况有一个简单的 slope-trick 做法：用堆维护斜率，每次 `push` 进去两个当前的数，然后 `pop` 出一个最大值。最终所有数的和减去堆中的数的和就是答案。

有一个来自 [ARC128F](https://atcoder.jp/contests/arc128/tasks/arc128_f) 经典思维技巧：对于这类弹堆压堆还要求堆中元素和的计数问题，考虑转化成值域为 01 的问题。即活用 $i=\sum_{x=1}^{\infin} [i\ge x]$ 的等式。将 $\ge x$ 的数标成 $1$，剩余的数标成 $0$。那么如果原先堆中有 $s$ 个 $1$，遇到一个 $1$ 会变成一个 $s+1$，遇到一个 $0$ 会变成 $\max(s-1,0)$。这就是一个格路游走问题，容易验证最终 $s$ 的值等于路程中 $1$ 的个数减去路程中 $0$ 的个数再加上如果没有对 $0$ 取 $\max$ 的情况下，$s$ 在整个过程中的最小值。

发现唯一难算的就是最后一部分的“最小值之和”。考虑继续运用上面的思维技巧，继续活用等式 $i=\sum_{x=1}^{\infin} [i\ge x]$，将 $s$ 的游走过程看作 $(0,0)$ 到 $(n,\times)$ 的游走过程，那么最小值之和（的相反数）可以拆成触碰 $y=-t\ (t>0)$ 这条线的方案数之和。钦定触碰一条线的格路游走就是我们熟悉的反射容斥。我们设原来有 $p$ 个 $1$，那么原先终点在 $(n,2p-n)$，如果 $2p-n>t$ 则经过那条线的方案数等于到终点 $(n,-2t-2p+n)$ 的方案数。

所以对于一个固定的 $p$，我们需要对以下东西求和：

$$
S_p=\sum_{t=1}^{\infin} {n\choose \min(n-t-p,p)}
$$

这个可以预处理 ${n\choose \times}$ 这一行的组合数前缀和简单算出来。

现在考虑对于 $x$ 你需要依次带入 $x=1,2,\dots,m$，不妨把结果看成一个关于 $x$ 的多项式，则这个多项式实际上是：

$$
F(x)=\sum_{p=0}^n x^p(m-x)^{n-p}S_p
$$

展开 $(m-x)^{n-p}$，容易发现可以用一遍卷积求出 $F$。

最后我们只需要解决 $\sum_{i=1}^m F(i)$，相当于要对一个固定的 $n$ 求出 $k=0,1,2,\dots,n$ 的自然数幂和 $S_k(n)=\sum_{i=0}^n i^k$，可以用多项式求逆求出伯努利数，然后卷一次得到自然数幂和。于是我们就做到复杂度 $O(n\log n)$。

[关于伯努利数求自然数幂和](https://www.cnblogs.com/yyyyxh/p/18263819/many_isotonic_regression_countings)。

```cpp
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
// headers
struct poly{/** my poly template **/};
int n,m;
const int N=100103;
int fac[N],fiv[N];
int arr[N],pre[N];
int coe[N],pw[N];
inline int C(int a,int b){return (ll)fac[a]*fiv[b]%P*fiv[a-b]%P;}
void calc(int lim){
	pw[0]=1;
	for(int i=1;i<=lim;++i) pw[i]=(ll)pw[i-1]*m%P;
	fac[0]=1;
	for(int i=1;i<=lim;++i) fac[i]=(ll)fac[i-1]*i%P;
	fiv[lim]=qp(fac[lim]);
	for(int i=lim;i;--i) fiv[i-1]=(ll)fiv[i]*i%P;
}
int main(){
	n=read();m=read();
	calc(n+3);int res=(ll)n*(m-1)%P*pw[n]%P;
	if(res&1) res+=P;
	res>>=1;
	pre[0]=1;
	for(int i=1;i<=n;++i){
		pre[i]=pre[i-1]+C(n,i);
		if(pre[i]>=P) pre[i]-=P;
	}
	poly F(n+1),G(n+1);
	for(int i=0;i<=n;++i){
		if(2*i<=n) F[i]=(pre[i-1]+(ll)C(n,i)*(n-i*2))%P;
		else F[i]=pre[n-1-i];
		F[i]=(ll)F[i]*fac[n-i]%P;
	}
	for(int i=0;i<=n;++i) if(i&1) G[i]=fiv[i];else G[i]=P-fiv[i];
	G=F*G;
	for(int i=0;i<=n;++i) coe[i]=(ll)G[i]*pw[n-i]%P*fiv[n-i]%P;
	F.f.resize(n+2);
	G.f.resize(n+2);
	for(int i=0;i<=n+1;++i) F[i]=fiv[i+1];
	F=F.inv(n+2);
	for(int i=0,tt=1;i<=n+1;++i){
		G[i]=(ll)tt*fiv[i]%P;
		tt=(ll)tt*(m+1)%P;
	}
	G=F*G;
	for(int i=0;i<=n;++i) res=(res+(ll)coe[i]*(G[i+1]-F[i+1]+P)%P*fac[i])%P;
	res-=coe[0];
	if(res<0) res+=P;
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：OptimisticForever (赞：0)

### [Many Minimizations](https://www.luogu.com.cn/problem/P8923)

>对于序列 $a$，问单调不降的序列 $b$，使得对应位置的差的绝对值之和最小。
>
>对于长度为 $n$ 的序列，值域在 $[1,m]$，的序列 $a$ 求上述问题的答案之和。
>
>$n\leq 5000,m\leq 10^9$。

考虑子问题是一个经典问题，维护一个大根堆，每次先加入这个数，每次看这个数是否比堆顶的数小，如果小则弹出，计算贡献堆顶减去这个数，并且加入这个数进入堆。

注意到是 $x-y$ 的贡献形式，于是拆贡献，考虑枚举 $v$，表示 $[v,v+1)$ 这一段被贡献的答案，我们注意到一件很牛的事情，此时问题转化为了 $m=2$，其中选 $0$ 有了一个方案数，选 $1$ 有了一个方案数。

考虑 $m=2$ 怎么做，我们重新思考此问题。下文中值域调整为 $[0,m-1]$。

枚举分界点 $i$，设前缀和为 $s_i$，那么答案就是 $\min_{i=0}^n(s_i+n-i-(s_n-s_i))$。

大概是三部分，一部分是 $n$，一部分是 $s_n$，一部分是 $\min_{i=0}^{n}{2s_i-i}$。

前面两部分，我们直接枚举最终有多少个 $1$，是一个组合数。

后面这个，我们考虑式子每次加上 $0,2$，减去 $1$，所以可以转化为值域是 $\{-1,1\}$ 的最大前缀和。对于这个问题，我们考虑格路计数，枚举最后走到的点，相当于要恰好经过一个直线，且不越过一个直线，直线的斜率为 $1$。

容斥，计算不越过的方案，然后相减。具体的，使用反射容斥计算方案数。这样做是 $O(n^2)$ 的。

注意到它的计算答案方式大概是 $(a_i-a_{i-1})i$ 的求和，所以可以抵消使得 $a_i$ 只用算一次，此时你发现只需要预处理组合数后缀和，这样子就变成 $O(n)$。

我们终于解决了 $m=2$ 的问题，此时复杂度为 $O(nm)$，注意到答案肯定是关于 $m$ 的多项式，此时在 $O(n)$ 级别，直接拉插即可，总时间复杂度 $O(n^2)$。

但是我们还可以直接进一步推导。

我们发现最后计算的是这样一个式子：
$$
\sum _{v=1}^{m-1}\sum _{i}v^i(m-v)^if(i)
$$
其中 $f(i)$ 是一个关于 $i$ 的式子，这个东西可以 $O(n)$ 预处理。

直接拆组合数，调换枚举顺序，发现我们要预处理自然数幂和，使用伯努利数就可以做到 $O(n\log n)$ 了。

---

