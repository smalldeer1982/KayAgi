# [USACO20OPEN] Exercise P

## 题目描述

Farmer John（又）想到了一个新的奶牛晨练方案！  
如同之前，Farmer John 的 $N$ 头奶牛站成一排。对于 $1\le i\le N$ 的每一个 $i$，从左往右第 $i$ 头奶牛的编号为 $i$。他告诉她们重复以下步骤，直到奶牛们与她们开始时的顺序相同。

给定长为 $N$ 的一个排列 $A$，奶牛们改变她们的顺序，使得在改变之前从左往右第 $i$ 头奶牛在改变之后为从左往右第 $A_i$ 头。  
例如，如果 $A=(1,2,3,4,5)$，那么奶牛们总共进行一步就回到了同样的顺序。如果 $A=(2,3,1,5,4)$，那么奶牛们总共进行六步之后回到起始的顺序。每步之后奶牛们从左往右的顺序如下：

0 步：$(1,2,3,4,5)$  
1 步：$(3,1,2,5,4)$  
2 步：$(2,3,1,4,5)$  
3 步：$(1,2,3,5,4)$  
4 步：$(3,1,2,4,5)$  
5 步：$(2,3,1,5,4)$  
6 步：$(1,2,3,4,5)$  
**请你计算出所有可能的 $N!$ 种长为 $N$ 的排列 $A$ 回到起始顺序需要的步数的乘积。**

由于这个数字可能非常大，输出答案模 $M$ 的余数（$10^8\le M\le 10^9+7$，$M$ 是质数）。

-----

使用 C++ 的选手可以使用 [KACTL](https://github.com/kth-competitive-programming/kactl/blob/master/content/various/FastMod.h) 中的这一代码。这一名为 [Barrett 模乘](https://en.wikipedia.org/wiki/Barrett_reduction) 的算法可以以比通常计算快上数倍的速度计算 $a \% b$，其中 $b>1$ 为一个编译时未知的常数。（不幸的是，我们没有找到对于 Java 的这样的优化）。（译注：中文选手可以参考 几种取模优化方法[（译自 min-25 的博客）](https://loj.ac/article/327)）
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);

int main() {
    int M = 1000000007; F = FastMod(M);
    ull x = 10ULL*M+3; 
    cout << x << " " << F.reduce(x) << "\n"; // 10000000073 3
}
```

## 说明/提示

#### 样例解释：
对于每一个 $1\le i\le N$，以下序列的第 $i$ 个元素等于奶牛需要使用 $i$ 步的排列数量：$[1,25,20,30,24,20]$。所以答案等于 $1^1\cdot 2^{25}\cdot 3^{20}\cdot 4^{30}\cdot 5^{24}\cdot 6^{20}\equiv 369329541\pmod{10^9+7}$。

**注意：这个问题的内存限制增加为 512 MB。**

---
对于 $100\%$ 的数据，满足 $1\le N\le 7500$。

共 $16$ 个测试点，其中 $1$ 为样例，其余性质如下：

测试点  $2$ 满足 $N=8$。  
测试点 $3\sim 5$ 满足 $N\le 50$。  
测试点 $6\sim 8$ 满足 $N\le 500$。  
测试点 $9\sim 12$ 满足 $N\le 3000$。  
测试点 $13\sim 16$ 没有额外限制。

----
  
出题人：Benjamin Qi

## 样例 #1

### 输入

```
5 1000000007```

### 输出

```
369329541```

# 题解

## 作者：orangejuice (赞：23)

# 「USACO 2020 US Open Platinum」Exercise

做法与模数是否是质数无关

问题可能比较复杂，需要多步分析

1.对于一个已知的排列

显然这样的置换会构成若干个环，设每个环长度为$a_i,i\in [1,m]$，显然答案就是$lcm(a_i)$

2.对于已知的$a_i$序列(注意这里说的是有序的)，计算其方案数

考虑已经排列的个数为$i$，加入一个环大小为$j$

为了避免重复，应当固定这个环的初始位置为1号点，其余位置按照原先顺序插入

则方案数可以分为两部分考虑:

2-1.环内排列，固定的环首不可排列，即$(j-1)!$

2-2.剩下的$j-1$一个点位置未知，从未固定的$i+j-1$个点中选择

即$C(i+j-1,j-1)$

所以就是$C(i+j-1,j-1)(j-1)!=\frac{(i+j-1)!}{i!}$

归纳一下，发现更形象的描述就是$\begin{aligned}\frac{n!}{\prod_{i=1}^{m-1} (\sum_{j=1}^i a_j)}\end{aligned}$

也就是每次除掉转移时的大小，将$n!$分成若干段，这似乎有利于理解下面的dp优化



3.计算$lcm$之积

考虑对于每个质因数计算其出现的幂次，注意这个幂次是对于$\varphi$取模的

原先是求恰好包含$x^k$的方案数，得到的$dp$不好优化，考虑转换为: 

求质因数$x$出现在答案里的幂次$\ge k$的方案数$F_k$，答案就是$x^{\sum F_k}$

## Solution 1

那么反向求解，令$dp_i$表示当前已经确定了$i$个点，没有出现$x^k$倍数大小的联通块

暴力转移，枚举$i$从所有$x^k\not|j$转移过来即可，单次求解复杂度为$O(n^2)$，不可行

优化1:

考虑分解系数$\frac{(i+j-1)!}{i!}$，累前缀和，对于$j$为$x^k$倍数的情况枚举减掉

这样单次求解复杂度为$O(\frac{n^2}{x^k})$，总复杂度为$O(n^2\ln n)$，且不好处理阶乘逆元

优化2:

不枚举$x^i$的倍数，直接再用一个前缀和数组$s_i$记录下来，让$s_i$从$s_{i-x^k}$转移过来即可

如何将系数$\frac{(i+j-1)!}{i!}$分解？

每次$i+j$增大1，就多乘上一个$i+j$即可

当$s_{i}$从$s_{i-x^k}$转移过来时，需要补上$\begin{aligned}\prod_{j=i-x^k+1}^{i-1}j\end{aligned}$

也就是模拟了上面提到的把$n!$分段的过程

这样就去掉了阶乘逆元的求解

Tips:发现需要预处理$T_{i,j}=\prod_{k=i}^j k$，可以滚动一下会快一点，内存为$O(n)$

$$ \ $$

不同的$x^i$上限为$O(n)$种，实际大概可能是$O(\pi(n)\log \log n=\frac{n\log \log n}{\log n})$?

因此复杂度为$O(n^2)$

可以看到代码还是很简单的

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define Mod2(x) ((x<0)&&(x+=P2))
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
 
const int N=7510;
 
int n,P,P2;
int mk[N];
int s[N],T[N],dp[N];
 
ll qpow(ll x,ll k=P-2) {
    ll res=1;
    for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
    return res;
}
 
 
int main(){
    scanf("%d%d",&n,&P),P2=P-1;
    int ans=1;
    rep(i,2,n) if(!mk[i]) {
        for(int j=i+i;j<=n;j+=i) mk[j]=1;
        for(int x=i;x<=n;x*=i) mk[x]=i;
    }
    rep(i,1,n) T[i]=1;
    int r=1;
    rep(i,1,n) r=1ll*r*i%P2;
    rep(x,2,n) {
        rep(j,1,n-x+1) T[j]=1ll*T[j]*(j+x-2)%P2;
        // 滚动求解区间乘积
        if(mk[x]<=1) continue;
        dp[0]=1,s[0]=1;
        int sum=1;
 
        rep(i,1,n) {
            s[i]=0;
            if(i>=x) s[i]=1ll*s[i-x]*T[i-x+1]%P2;
            dp[i]=sum-s[i]; Mod2(dp[i]);
            s[i]=(1ll*s[i]*i+dp[i])%P2;
            sum=(1ll*sum*i+dp[i])%P2;
        }
        ans=1ll*ans*qpow(mk[x],P2+r-dp[n])%P;
    }
    printf("%d\n",ans);
}
```



## Solution 2

为了便于表达，设满足条件为至少出现一个$x$的倍数

实际用min-max容斥确实比较好理解，设对于集合$S$，求其最大值

$\begin{aligned} \max \lbrace S\rbrace =\sum_{T\sube S} (-1)^{|T|+1}\min\lbrace T \rbrace\end{aligned}$

简要证明的话:

把$S$中的元素倒序排成一排分别为$S_i$

对于$S_1$即最大值，显然被计算一次

对于剩下的值$S_i(i>1)$，则它作为最小值产生贡献意味着选的数都在$1-i$内，显然有$2^{i-1}$次为奇数集合大小，$2^{i-1}$为偶数集合大小，两部分抵消

$$ \ $$

要计算最大值为1的方案数，那么就要计算最小值为1的子集方案数

考虑强制一个子集中每一个环大小均为$x$的倍数，设选出了$i$个这样的环，总大小为$j$的方案数为$dp_{i,j}$

则实际对答案的贡献还要考虑这样的子集出现的次数

考虑选择子集的位置，以及剩下的$n-j$个点任意排布，方案数应该为$C(n,j)\cdot (n-j)!=\frac{n!}{j!}$

如果真的用$dp_{i,j}$，复杂度显然太高，考虑$i$这一维的影响只在于系数$(-1)^{|T|+1}$，可以直接在转移过程中解决

因此可以直接记录大小$i$，从前面转移过来

(可以看到依然需要访问上面提到的$T_{i,j}$，要滚动的话还会更难处理)

这样的$dp$状态有$\frac{n}{x}$种，转移为$(\frac{n}{x})^2$，最后统计复杂度为$O(\frac{n}{x})$

实际上这样的复杂度已经足够了，是$O(\sum \frac{n^2}{i^2}\approx n^2)$

以下是$O(n^2)$内存的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
typedef long long ll;

const int N=7510;

int n,P,P2,T[N][N],mk[N],dp[N];
ll qpow(ll x,ll k) {
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}
int Calc(int x){
	int m=n/x,s=P2-1;
	rep(i,1,m) {
		s=1ll*s*T[(i-1)*x+1][i*x-1]%P2;
		dp[i]=P2-s;
		s=(1ll*s*i*x+dp[i])%P2;
	}
	int ans=0;
	rep(i,1,m) ans=(ans+1ll*dp[i]*T[i*x+1][n])%P2;
	return ans;
}

int main(){
	scanf("%d%d",&n,&P),P2=P-1;
	rep(i,2,n) if(!mk[i]) {
		for(int j=i;j<=n;j+=i) mk[j]=1;
		for(int j=i;j<=n;j*=i) mk[j]=i;
	}
	rep(i,1,n+1){
		T[i][i-1]=1;
		rep(j,i,n) T[i][j]=1ll*T[i][j-1]*j%P2;
	}
	int ans=1;
	rep(i,2,n) if(mk[i]>1) ans=ans*qpow(mk[i],Calc(i))%P;
	printf("%d\n",ans);
}
```



$$ \ $$

### 最终优化

可以看到，这个做法和Sol1的转移有十分的相同之处，因此考虑用同样的方法优化掉

但是预处理系数的部分依然是$O(n^2)$的，如何解决呢?

1.线段树大法

预处理复杂度为$O(n)$，查询复杂度为$O(\log n)$，总复杂度$O(n\log^2 n)$

空间复杂度为$O(n)$

Oh这个代码是ZKW线段树

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
typedef long long ll;

const int N=7510;

int n,P,P2;
struct Tree {
	int s[N<<2],bit;
	void Build() {
		for(bit=1;bit<=n;bit<<=1);
		rep(i,1,n) s[i+bit]=i;
		for(int i=bit;i>=1;--i) s[i]=1ll*s[i<<1]*s[i<<1|1]%P2;
	}
	int Que(int l,int r){
		if(l>r) return 1;
		if(l==r) return l;
		int res=1;
		for(l+=bit-1,r+=bit+1;l^r^1;l>>=1,r>>=1){
			if(~l&1) res=1ll*res*s[l^1]%P2;
			if(r&1) res=1ll*res*s[r^1]%P2;
		}
		return res;
	}
} T;

int mk[N];
ll qpow(ll x,ll k) {
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}

int dp[N];
int Calc(int x){
	int m=n/x,s=P2-1;
	rep(i,1,m) {
		s=1ll*s*T.Que((i-1)*x+1,i*x-1)%P2;
		dp[i]=P2-s;
		s=(1ll*s*i*x+dp[i])%P2;
	}
	int ans=0;
	rep(i,1,m) ans=(ans+1ll*dp[i]*T.Que(i*x+1,n))%P2;
	return ans;
}

int main(){
	scanf("%d%d",&n,&P),P2=P-1;
	T.Build();
	rep(i,2,n) if(!mk[i]) {
		for(int j=i;j<=n;j+=i) mk[j]=1;
		for(int j=i;j<=n;j*=i) mk[j]=i;
	}
	int ans=1;
	rep(i,2,n) if(mk[i]>1) ans=ans*qpow(mk[i],Calc(i))%P;
	printf("%d\n",ans);
}
```



2.模数分解+CRT(Chinese Remainder Theory)

分解后，可以用模逆元处理，然后就直接做，最后CRT合并一下，其实我并不会实现。。。



3.猫树~~(嘿嘿)~~

这是一个$O(n\log n)$预处理，$O(1)$查询的数据结构，空间复杂度为$O(n\log n)$

因此复杂度为$O(n\log n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
typedef long long ll;

const int N=7510;

int n,P,P2;
struct SuckCat{
	int s[14][8200],Log[8200],bit;
	void Build() {
		for(bit=1;bit<=n;bit<<=1);
		rep(i,2,bit) Log[i]=Log[i>>1]+1;
		for(int l=1,d=0;l*2<=bit;l<<=1,d++){
			for(int i=l;i<=bit;i+=l*2){
				s[d][i-1]=i-1,s[d][i]=i;
				drep(j,i-2,i-l) s[d][j]=1ll*s[d][j+1]*j%P2;
				rep(j,i+1,i+l-1) s[d][j]=1ll*s[d][j-1]*j%P2;
			}
		}
	}
	int Que(int l,int r){
		if(l>r) return 1;
		if(l==r) return l;
		int d=Log[l^r];
		return 1ll*s[d][l]*s[d][r]%P2;
	}
} T;

int mk[N];
ll qpow(ll x,ll k) {
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}

int dp[N];
int Calc(int x){
	int m=n/x,s=P2-1;
	rep(i,1,m) {
		s=1ll*s*T.Que((i-1)*x+1,i*x-1)%P2;
		dp[i]=P2-s;
		s=(1ll*s*i*x+dp[i])%P2;
	}
	int ans=0;
	rep(i,1,m) ans=(ans+1ll*dp[i]*T.Que(i*x+1,n))%P2;
	return ans;
}

int main(){
	scanf("%d%d",&n,&P),P2=P-1;
	T.Build();
	rep(i,2,n) if(!mk[i]) {
		for(int j=i;j<=n;j+=i) mk[j]=1;
		for(int j=i;j<=n;j*=i) mk[j]=i;
	}
	int ans=1;
	rep(i,2,n) if(mk[i]>1) ans=ans*qpow(mk[i],Calc(i))%P;
	printf("%d\n",ans);
}
```





























---

## 作者：qwaszx (赞：9)

一个置换的步数显然是所有环长的 $\mathrm{lcm}$，又要求乘积，因此我们枚举每个质因子计算贡献. 考虑枚举一个质数 $p$，我们需要知道它的指数. 一个置换的贡献是所有环长在 $p$ 处的次数的 $\max$，于是我们枚举 $\max=d$，计数有多少个置换的 $\max\geq d$. 令 $t=p^d$，那么现在需要求出的就是满足存在一个长为 $t$ 的倍数的环的置换的个数，我们可以容斥为不存在的方案数. 那么现在一个环的 EGF 就是

$$
C(z)=\sum_{i\geq 1}\frac{z^i}{i}[i\bmod t\neq 0]=\ln\left(\frac{1}{1-z}\right)-\frac{1}{t}\ln\left(\frac{1}{1-z^t}\right)
$$

那么置换的个数就是

$$
[n!z^n]\exp(C(z))=[n!z^n]\frac{(1-z^t)^{1/t}}{1-z}
$$

注意乘以 $\dfrac{1}{1-z}$ 相当于在做部分和，令 $k=\left\lfloor\dfrac{n}{t}\right\rfloor$，那么答案就是

$$
[n!z^k](1-z)^{1/t-1}=n!(-1)^k\binom{1/t-1}{k}=\frac{n!(t-1)(2t-1)\cdots(kt-1)}{k!t^k}
$$

现在的问题是因为这个在指数上，所以要对 $M-1$ 取模，而这个相当于任意模数. 于是大概有两个做法，它们都要依赖一个复杂度上的结论:

$$
\sum_{p\ is\ prime,k\geq 1}\left\lfloor\frac{n}{p^k}\right\rfloor=\Theta(n\log\log n)
$$

这个可以用素数倒数和的界来简单证明:

$$
\begin{aligned}
&\sum_{p\ is\ prime,k\geq 1}\left\lfloor\frac{n}{p^k}\right\rfloor\\
\leq &\sum_{p\ is\ prime,k\geq 1}\frac{n}{p^k}\\
=&\ n\sum_{p\ is\ prime}\frac{1}{p-1}\\\leq&\ n\left(1+\sum_{p\ is\ prime}\frac{1}{p}\right)\\
=&\ \Theta(n\log\log n)
\end{aligned}
$$

那么我们现在考虑计算 $\dfrac{n!}{k!t^k}\bmod (M-1)$， 这相当于是

$$
\prod_{i=1}^ni^{[i\bmod t\neq 0]}
$$

于是其中一个做法就是:上面这个乘积会被分成 $\lfloor n/t\rfloor$ 段连续区间，我们使用数据结构来查询区间乘积. 那么这是经典的静态区间半群信息查询，在这里有 $\Theta(n\log\log n)$ 次查询，于是我们使用 $\Theta(n\log\log n)-\Theta(1)$ 的 Sqrt Tree 即可.  

另一个稍微简单一点(?)的做法来自 [EI](https://blog.csdn.net/EI_Captain/article/details/105205834)，我们把 $M-1$ 的质因子中 $\leq n$ 的分解出来:

$$
M-1=R\prod_i p_i^{\alpha_i}
$$

有 $\omega\leq 9$ 个质因子，我们从小到大枚举 $t$，这样 $k$ 就是递减的，我们维护 $\dfrac{n!}{k!}$ 以及其中和 $p_i$ 互质的部分的乘积以及每个 $p_i$ 的次数. 暴力加入的复杂度就是 $\sum_{i}\lfloor n/p_i \rfloor=O(n\log\log n)$，写得不好（比如我）可能还要加个 $n\omega$. 对于一个和 $p_i$ 都互质的 $t$，我们暴力 exgcd 计算 $t^{-k}\bmod (M-1)$ 乘上去，exgcd 的执行次数是 $n$ 以内质数幂的个数 $=\Theta(n/\ln n)$（只要对 $>\sqrt{n}$ 和 $\leq \sqrt{n}$ 的质数分别考虑即可证明）；对于其余的 $t$ （不超过 $\sum_i \log_{p_i}n$ 个）我们用之前记录的指数计算，这部分不是复杂度瓶颈. 最后还要对每个质数做快速幂，这部分复杂度 $\Theta(\dfrac{n\log M}{\ln n})$. 于是我们可以在 $O(\sqrt{M}+n\log\log n+\dfrac{n\log M}{\ln n})$ 复杂度内完成整道题.

代码是第二种方法的，不过我觉得还能写得短很多(

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int N=10000;
int pm[10],lim[10],pm_cnt,is_modp[N],mod,n;
struct modprod
{
    int nwn,res,all;
    int cnt[10],pw[10][N];
    void clear()
    {
        res=all=1,nwn=n;
        for(int i=1;i<=pm_cnt;i++)
        {
            pw[i][0]=1;cnt[i]=0;
            int s=0;
            for(long long t=pm[i];t<=n;t*=pm[i])
                s+=n/t;
            for(int j=1;j<=s;j++)pw[i][j]=1ll*pw[i][j-1]*pm[i]%(mod-1);
        }
    }
    int get(){return all;}
    int get(int p,int k)
    {
        int ans=res;
        for(int i=1;i<=pm_cnt;i++)
            if(pm[i]==p)
                ans=1ll*ans*pw[i][cnt[i]-k]%(mod-1);
            else ans=1ll*ans*pw[i][cnt[i]]%(mod-1);
        return ans;
    }
    void mul(int x)
    {
        all=1ll*all*x%(mod-1);
        for(int i=1;i<=pm_cnt;i++)
        {
            while(x%pm[i]==0)++cnt[i],x/=pm[i];
        }
        res=1ll*res*x%(mod-1);
    }
    void maintain(int t)
    {
        while(nwn>t)mul(nwn--);
    }
}a;
void factor(int x)
{
    for(int i=2;i*i<=x&&i<=n;i++)
    {
        if(x%i==0)
        {
            pm[++pm_cnt]=i;
            while(x%i==0)x/=i,++lim[pm_cnt];
            is_modp[i]=1;
        }
    }
    if(x!=1&&x<=n)
    {
        pm[++pm_cnt]=x,lim[pm_cnt]=1,is_modp[x]=1;
    }
}
int ecnt[N],ispw[N],prime[N],p[N],pwcnt[N],prime_cnt;
int qpower(int a,int b)
{
    int ans=1;for(;b;b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
    return ans;
}
int spower(int a,int b)
{
    int ans=1;for(;b;b>>=1,a=1ll*a*a%(mod-1))if(b&1)ans=1ll*ans*a%(mod-1);
    return ans;
}
void exgcd(int a,int b,int &x,int &y)
{
    if(!b){x=1,y=0;return;}
    exgcd(b,a%b,y,x);y-=a/b*x;
}
int Inv(int a)
{
    int x,y;exgcd(a,mod-1,x,y);
    return (x%(mod-1)+mod-1)%(mod-1);
}
void solve()
{
    int fac=1;for(int i=1;i<=n;i++)fac=1ll*fac*i%(mod-1);
    for(int i=2;i<=n;i++)
    {
        if(!p[i]){prime[++prime_cnt]=i;ispw[i]=i;pwcnt[i]=1;}
        if(ispw[i])
        {
            int k=n/i,p=ispw[i];
            a.maintain(k);
//            cout<<i<<" "<<p<<" "<<pwcnt[i]*k<<endl;
            int s=1;for(int j=1;j<=k;j++)s=1ll*s*(j*i-1)%(mod-1);
//            cout<<i<<" "<<p<<" "<<s<<endl;
            if(is_modp[p])s=1ll*s*a.get(p,pwcnt[i]*k)%(mod-1);
            else s=1ll*s*a.get()%(mod-1)*spower(Inv(i),k)%(mod-1);            
            ecnt[p]=(ecnt[p]+fac-s)%(mod-1);//cout<<i<<" "<<p<<" "<<ecnt[p]<<endl;
        }
        for(int j=1;j<=prime_cnt&&i*prime[j]<=n;j++)
        {
            int x=i*prime[j];p[x]=1;
            if(i%prime[j])ispw[x]=0;
            else{ispw[x]=ispw[i],pwcnt[x]=pwcnt[i]+1;break;}
        }
    }
    int ans=1;
    for(int i=2;i<=n;i++)
    if(!p[i])
    {
//        cout<<i<<" "<<ecnt[i]<<endl;
        ans=1ll*ans*qpower(i,(ecnt[i]+(mod-1))%(mod-1))%mod;
    }
    cout<<ans<<endl;
}
int main()
{
    scanf("%d%d",&n,&mod);
    factor(mod-1);a.clear();
    solve();
}
```

---

## 作者：cff_0102 (赞：9)

~~由于教练要求所以~~本题解写的较为详细，可能有参考其它题解导致内容上有相似部分，但这篇题解的内容都是我自己打的。

首先，转换一下题意：求所有 $n$ 的排列内的所有置换环长度的 lcm 之积。

直接计算比较麻烦，不妨设 $F(x)$ 表示有多少个 $n$ 的排列内的所有置换环长度的 lcm 是 $x$ 的倍数。

那么答案可以转化为 $\prod\limits_{p\text{ is a prime}}p^{F(p^k)}$。

那么，只需要枚举每个 $p^k$，分别求出对应的 $F(p^k)$ 即可。

不难发现，求解 $F(p^k)$ 实际上相当于求有多少个 $n$ 的排列存在置换环的长度是 $p^k$ 的倍数。

但是，求至少有一个置换环长度是 $p^k$ 的倍数的排列个数还是比较困难的，不如先求没有一个置换环长度是 $p^k$ 的倍数的排列的数量，再用 $n!$ 减去它就行了。设 $x=p^k$，记没有一个置换环长度是 $x$ 的倍数的 $i$ 的排列的数量为 $f_i$，至少有一个置换环长度是 $x$ 的倍数的 $n$ 的排列的个数就是 $n!-f_n$。现在只需要求 $f$ 即可。

考虑 dp，发现直接推 $f$ 是困难的，但是还是可以使用刚才所说的容斥的方法：把至少有一个置换环长度是 $x$ 的倍数的 $i$ 的排列的个数计算出来，再用 $i!$ 减去它。这看起来像是回到了刚刚的那个问题，但是由于已经定义了 $f$，要计算至少有一个置换环长度是 $x$ 的倍数的 $i$ 的排列的个数，可以把这种排列拆成两部分：一部分的置换环长度都是 $x$ 的倍数，另一部分则都不是 $x$ 的倍数。设前者包含 $j$ 个点，则后者包含 $i-j$ 个点。后者的方案数是已知的，也就是 $f_{i-j}$，那么只需要求出前者即可。

继续设所有置换环长度都是 $x$ 的倍数的大小为 $i$ 的排列的个数为 $g_i$。首先，可以写出 $f_i$ 的递推式了：

$$f_i=i!-\sum\limits_{x|j,j\le i}\binom{i}{j}g_jf_{i-j}$$

枚举 $j$，在 $i$ 个数里面任意选 $j$ 个，这 $j$ 个数内部的置换环长度都是 $x$ 的倍数，另外 $i-j$ 个数内部的置换环长度都不是 $x$ 的倍数。把这些方案数乘起来即可。

那么，$g$ 应该怎么求呢？继续考虑 dp。具体的，在 $g_i$ 的 dp 过程中，可以枚举其中第一个点所在的环的长度 $j$。这个长度确定了，乘上 $\binom{i-1}{j-1}$ 就是第一个点所在的环中的点的可能的情况数量，再乘上圆排列的情况数 $(j-1)!$ 就能得到这个环可能的情况数量。把这个环排除掉，剩下的部分直接取 $g_{i-j}$ 即可。即：

$$g_i=\sum\limits_{x|j,j\le i}\binom{i-1}{j-1}(j-1)!g_{i-j}$$

先计算 $g$ 再计算 $f$，这样 dp 的状态个数是 $O(n)$ 的，转移做 $\frac n x$ 次，乘上还要枚举所有 $x=p^k$ 的复杂度，发现最终复杂度是 $\sum\limits_{x=1}^n\frac{n^2}x=O(n^2\log n)$，过不了。

继续考虑优化。注意到最终只需要 $f_n$ 的值，而要计算 $f_n$，只需要知道所有满足 $x|j$ 的 $g_j$ 的值和 $f_n-j$ 的值即可。继续推下去，可以发现实际上只需要所有满足 $i\equiv n\pmod x$ 的 $f_i$ 值和 $i\equiv0\pmod x$ 的 $g_i$ 值。也就是说，状态数量可以优化到 $\frac n x$。那么最终的复杂度就变成了 $\sum\limits_{x=1}^{n}\frac{n^2}{x^2}$。而我们知道 $\sum\limits_{x=1}^{\infty}\frac1{x^2}=\frac{\pi^2}{6}$，这是个常数啊！这样复杂度就优化到了 $O(n^2)$ 的，能过，把题面给的快速取模删掉也能在一半时限内通过。

还要注意取模的问题。最终推出的这个 $n!-f_n$ 是在指数上的，根据费马小定理 $p^{M-1}\equiv1\pmod M$，也就是说指数上的数要取模 $M-1$，别弄混了。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull r(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
FastMod F(2);
#define int unsigned long long
const int N=7575;
int C[N][N],jc[N];
int n,mod;
void init(){
	C[0][0]=1;
	for(int i=1;i<=7550;i++){
		for(int j=0;j<=i;j++){
			C[i][j]=C[i-1][j];
			if(j)C[i][j]+=C[i-1][j-1];
			C[i][j]=F.r(C[i][j]);
		}
	}
	jc[0]=1;
	for(int i=1;i<=7550;i++){
		jc[i]=F.r(jc[i-1]*i);
	}
}
int ksm(int a,int b){
	int s=1;
	while(b){
		if(b&1)(s*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return s;
}
int f[N],g[N];
int dp(int x){
	g[0]=f[0]=1;
	for(int i=x;i<=n;i+=x){
		g[i]=0;
		for(int j=x;j<=i;j+=x){
			g[i]=F.r(g[i]+F.r(C[i-1][j-1]*F.r(jc[j-1]*g[i-j])));
		}
	}
	for(int i=n%x;i<=n;i+=x){
		f[i]=jc[i];
		for(int j=x;j<=i;j+=x){
			f[i]=F.r(f[i]+mod-1-F.r(C[i][j]*F.r(g[j]*f[i-j])));
		}
	}
	return F.r(jc[n]+mod-1-f[n]);
}
bool v[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>mod;
	F=FastMod(mod-1);init();
	int ans=1;
	for(int i=2;i<=n;i++){
		if(!v[i]){
			for(int j=i;j<=n;j+=i){
				v[j]=1;
			}
			for(int j=i;j<=n;j*=i){
				(ans*=ksm(i,dp(j)))%=mod;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

这题还能进一步优化到 $O(n\log\log n)$，具体方法~~我不会~~留作习题。

---

## 作者：EndSaH (赞：6)

[欢迎光临个人博客，这里的可能不会更新](https://endsah.tk/blog/USACO-2020-US-Open-Solution/)

建议到上面的链接或者洛谷博客里阅读，题解界面的公式渲染有些问题

## Solution

容易发现，设 $F(x)$ 表示有多少个排列得到的置换的 lcm 是 $x$ 的倍数，那么答案就是 $\prod p ^{F(p ^c)}$，其中 $p$ 是一个质数。

注意这里的 $F(x)$ 是指数，所以只能对 $mod - 1$ 取模，这是一个合数，比较麻烦。

下面的过程是求出 $F(p ^c)$ 的过程，令 $x = p ^c$。

称一个环是合法的当且仅当其环长为 $x$ 的倍数。现在相当于是要求出有多少个排列满足其对应的置换至少有一个合法环。

考虑 DP，设 $f _i$ 表示所有大小为 $i$ 的排列中，满足「该排列所对应的置换中，没有任意一个环合法」的排列数，$g _i$ 反过来表示全部环均合法的排列数。

简单容斥，用任意排列数减去至少有一个环合法的排列数。枚举这些合法的环的环长总和为 $j$：

$$f _i = i! - \sum _{x|j, j \le i} {i \choose j} g _j f _{i - j}$$

现在考虑如何求出 $g _i$。

先来思考一个其他的问题：如果已经给出了一个 $n$ 的有序划分，如何求出其对应的排列数？

一种可行思路是从前往后考虑所有的环，每个环都一定会选当前剩下的最小编号，然后其他的任选。

比如第一个环大小为 $i$，那么钦定其一定会选到 $1$，其他的任选的方案数即为 ${n - 1 \choose i - 1}$，再乘上 $(i - 1)!$ 考虑圆排列。

可以发现这样操作剩下的 $n - i$ 会变成一个子问题。所以可以对 $g _i$ 这样转移：

$$g _i = \sum _{x|j, j \le i} {i - 1 \choose j - 1} (j - 1)! g _{i - j}$$

还有一些优化。可以发现对 $f _n$ 能产生贡献的 $f, g$ 是 $O(\lfloor \frac n x \rfloor)$ 级别的（观察转移方程，有值的 $f_i$ 总可以表示成 $(n \bmod x) + kx(k \in \mathbb{N})$ 的形式），总复杂度为 $\sum \limits _{x = 1} ^n \frac {n^2} {x ^2} = n ^2 \sum \limits _{x = 1} ^n x ^{-2} = n ^2 \frac {\pi ^2} 6 \le n ^2$。


## Code

代码里用到了快速取模。

```cpp
#include <cstdio>
#include <iostream>

#define Dec(x, mod) (x >= (mod) ? x -= (mod) : 0)

using namespace std;

typedef unsigned long long ULL;

const int maxN = 7505;

int n, mod;
int f[maxN], g[maxN], fac[maxN];
bool vis[maxN];
int C[maxN][maxN];

namespace Mod
{
    ULL b, m;

    inline void Init(int x)
    { b = x, m = ULL((__int128(1) << 64) / b); }

    inline ULL Reduce(ULL a)
    {
        ULL q = (ULL)((__int128(m) * a) >> 64);
        ULL r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
} using Mod::Reduce;

int FPM(int bas, int ind)
{
    int res = 1;
    while (ind)
    {
        if (ind & 1)
            res = (ULL)res * bas % mod;
        bas = (ULL)bas * bas % mod;
        ind >>= 1;
    }
    return res;
}

void Init()
{
    cin >> n >> mod;
    Mod::Init(mod - 1);
    C[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j <= n; ++j)
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j], Dec(C[i][j], mod - 1);
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = Reduce((ULL)fac[i - 1] * i);
}

int DP(int x)
{
    g[0] = 1;
    for (int i = x; i <= n; i += x)
    {
        g[i] = 0;
        for (int j = x; j <= i; j += x)
            g[i] = Reduce(g[i] + Reduce((ULL)g[i - j] * C[i - 1][j - 1]) * fac[j - 1]);
    }
    f[0] = 1;
    for (int i = n % x; i <= n; i += x)
    {
        f[i] = fac[i];
        for (int v = 1; v * x <= i; ++v)
        {
            int j = v * x;
            f[i] = Reduce(f[i] + mod - 1 - Reduce(Reduce((ULL)C[i][j] * g[j]) * f[i - j]));
        }
    }
    return Reduce(fac[n] - f[n] + mod - 1);
}

int main()
{
    ios::sync_with_stdio(false);
    Init();

    int ans = 1;
    for (int i = 2; i <= n; ++i) if (!vis[i])
    {
        for (int j = i; j <= n; j += i)
            vis[j] = true;
        for (int j = i; j <= n; j *= i)
            ans = (ULL)ans * FPM(i, DP(j)) % mod;
    }
    cout << ans << endl;

    return 0;
}
```

---

## 作者：dAniel_lele (赞：5)

考虑 $\min-\max$ 容斥。（这里其实是 $\gcd-\operatorname{lcm}$）

不难发现原题本质上要求求每种排列环长 $\operatorname{lcm}$ 的乘积。

类比 $\min-\max$ 容斥：$\operatorname{lcm}_{x\in S}x=\prod_{T\subseteq S}(\gcd_{x\in T}x)^{(-1)^{|T|-1}}$。

考虑钦定 $\gcd=x$ 计算答案。

先预处理一个 $dp_i$ 表示 $i$ 个位置分成若干个环的方案数。转移考虑要不重不漏，于是可以钦定每新增一个环，必须其中第一个数在最前面，有序插入。

于是转移式是：$dp_i\times\binom{i+j-1}{j-1}\times (j-1)!\to dp_{i+j}$。（环排列有 $(j-1)!$ 钟）

接下来，对于每个 $\gcd=x$，均做一遍类似 $f_i$。不同之处在于，由于容斥系数原因，我们需要转移的时候乘上 $-1$。最后钦定选出 $\gcd=x$ 的答案就是 $\sum_{i=1}^{\frac{n}{x}}f_idp_{n-ix}\binom{n}{ix}$。

容易发现对于 $\gcd=x$，我们的上界其实是 $\frac{n}{x}$。所以总复杂度是 $\sum_{i=1}^{n}(\frac{n}{i})^2=n^2\sum_{i=1}^n\frac{1}{i^2}=O(n^2)$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long 
#define add(i,j) ((i+j>=mod)?(i+j-mod):(i+j))
using namespace std;
int qp(int a,int b,int mod){
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[7505],dp[7505],f[7505],ans[7505];
signed C[7505][7505],A[7505][7505];
signed main(){
	int n,p; cin>>n>>p;
	const int mod=p-1;
	for(int i=0;i<=7500;i++) C[i][0]=1;
	for(int i=1;i<=7500;i++) for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	fac[0]=1; for(int i=1;i<=7500;i++) fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=7500;i++) for(int j=0;j<=i;j++) A[i][j]=C[i][j]*fac[j]%mod;
	dp[0]=1;
	for(int i=0;i<=7500;i++){
		for(int j=1;i+j<=7500;j++){
			if(i!=0) (dp[i+j]+=dp[i]*A[i+j-1][j-1])%=mod;
			else (dp[i+j]+=dp[i]*fac[j-1])%=mod;
		}
	}
	for(int i=1;i<=n;i++){
		int m=n/i;
		memset(f,0,sizeof(f));
		f[0]=mod-1;
		for(int j=0;j<=m;j++){
			for(int k=1;j+k<=m;k++){
				if(j!=0) f[j+k]=add(f[j+k],mod-f[j]*A[(j+k)*i-1][k*i-1]%mod);
				else f[j+k]=add(f[j+k],mod-f[j]*fac[k*i-1]%mod);
			}
		}
		for(int j=1;j<=m;j++){
//			cout<<f[j]<<" "<<f[j]*dp[n-j*i]%mod*C[n][j*i]%mod<<"  ";
			(ans[i]+=f[j]*dp[n-j*i]%mod*C[n][j*i])%=mod;
		}
//		cout<<" "<<ans[i]<<"\n";
	}
	for(int i=n;i>=1;i--){
		for(int j=i*2;j<=n;j+=i) (ans[i]+=mod-ans[j])%=mod;
	}
	int ret=1;
	for(int i=1;i<=n;i++){
//		cout<<ans[i]<<" "<<qp(i,ans[i],p)<<"  ";
		(ret*=qp(i,ans[i],p))%=p;
	}
	cout<<ret;
	return 0;
}
```

---

## 作者：AC_Lover (赞：3)

**简要题意：** 求长度为 $n$ 所有的排列置换环长的 $\mathrm{lcm}$ 乘积。

**做法：**

考虑类比 $\min-\max$ 容斥，有 $\gcd-\mathrm{lcm}$ 容斥：

$$
\mathrm{lcm}_{x\in S}\space x=\prod_{T\subseteq S} \left(\gcd_{x\in T}\space x\right)^{(-1)^{|T|-1}} 
$$

于是原来的答案相当于要求：

$$
\prod_{S} \left[\prod_{T\subseteq S}\left(\gcd_{x\in T} \space x\right)^{{(-1)}^{|T|-1}} \right]
$$

交换枚举顺序，枚举 $T$：

$$
\prod_{T}\left(\gcd_{x\in T}\space x\right)^{(-1)^{|T|-1}\times |\sup(T)|}
$$

把其中的 $\gcd$ 提出来记作 $k$：

$$
\prod_{k} k^{\large \left[\sum_{(\gcd_{x\in T}x)=k} (-1)^{|T|-1}\times |\sup(T)|\right]}
$$

于是我们要想办法求出

$$
F_k=\sum_{(\gcd_{x\in T}x)=k} (-1)^{|T|-1}\times |\sup(T)|
$$

先考虑定义 $f_i$ 表示长度为 $i$、由若干置换环组成的排列的方案数。假设原来有长度为 $i$ 的满足要求的排列，现在往其中加入一个大小为 $j$ 的置换环，就能得到长度 $(i+j)$ 的满足要求的排列，由于是环所以要固定其中一个数进行计数，于是大小为 $j$ 的置换环有 $(j-1)!$ 个，选取组成置换环的数的方案是 $\binom{i+j-1}{j-1}$，于是得到转移：

$$
f_{i+j}\leftarrow \binom{i+j-1}{j-1}(j-1)!\times f_i
$$

这个计数 $\mathrm{dp}$ 的优越性在于我们可以通过限定 $j$ 来限定最后的计数。回到原来 $F_k$ 的计算，如果我们限定 $j$ 是 $k$ 的倍数，那么就可以求出【长度为 $i$，置换环长度都是 $k$ 的倍数的排列个数】，记其为 $g_{xk}$，同时，$(-1)^{|T|-1}$ 的容斥系数也可以在转移的时候 $\times (-1)$ 来实现，现在只剩下 $|\sup(T)|$，组成了长度为 $(xk)$ 的排列后还剩下 $(n-xk)$ 个数，可以任意组合，选择数的方案是 $\binom{n}{xk}$，剩下的组成排列方案数为 $f_{n-xk}$，于是可以得到：

$$
F^{\prime}_k=\sum_{x=1}^{\frac{n}{k}}g_{xk}\binom{n}{xk}f_{n-xk}
$$

但是此时计算的是 $\gcd$ 为 $k$ 的倍数的答案，使用 $\gcd$ 容斥即可求出 $F_k$，因此答案就是：

$$
\prod_{k} k^{F_k}
$$

时间复杂度：$O(n^2)$。

---

注意一些细节：

$F_k$ 位于指数上，因此根据扩展欧拉定理:

$k^{F_k}\bmod m\equiv k^{F_k\bmod \varphi(m)+\varphi(m)}\pmod m$

其中 $\varphi(m)=m-1$，因此计算 $F_k$ 时应使用 $(m-1)$ 作为模数。

---

**代码:**

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int N=7510;
int n,p,mod;
int C[N][N],fac[N],A[N][N];
int f[N],g[N],F[N];

inline int Mod(int x) { return (x<0) ? x+mod : ((x>=mod) ? x-mod : x); }
inline void adm(int &x,int y) { x=Mod(x+y); }

inline int qmi(ll a,int b)
{
	ll res=1;
	while (b)
	{
		if (b&1) res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}

inline void Init()
{
	fac[0]=1;
	for (int i=1;i<=n;i++) fac[i]=(ll)fac[i-1]*i%mod;
	
	C[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=0;j<=i;j++)
		{
			if (!j) C[i][j]=1;
			else C[i][j]=Mod(C[i-1][j]+C[i-1][j-1]);
		}
	}
	for (int i=0;i<=n;i++)
	{
		for (int j=0;j<=i;j++)
		{
			A[i][j]=(ll)C[i][j]*fac[j]%mod;
		}
	}
}

int main()
{
	cin >> n >> p;
	mod=p-1;
	
	Init();
	
	f[0]=1;
	for (int i=0;i<=n;i++)
	{
		for (int j=1;i+j<=n;j++)
		{
			adm(f[i+j],1ll*A[i+j-1][j-1]*f[i]%mod);
		}
	}
	
	for (int k=1;k<=n;k++)
	{
		int m=n/k;
		
		memset(g,0,sizeof(g));
		g[0]=mod-1;
		for (int i=0;i<=m;i++)
		{
			for (int j=1;i+j<=m;j++)
			{
				int x=i*k,y=j*k;
				adm(g[i+j],mod-1ll*A[x+y-1][y-1]*g[i]%mod);
			}
		}
		
		for (int i=1;i<=m;i++) adm(F[k],(ll)g[i]*C[n][i*k]%mod*f[n-i*k]%mod);
	}
	
	for (int i=n;i;i--)
	{
		for (int j=(i<<1);j<=n;j+=i)
		{
			adm(F[i],mod-F[j]);
		}
	}
	
	int ans=1;
	for (int i=1;i<=n;i++) ans=(ll)ans*qmi(i,F[i])%p;
	cout << ans << "\n";
	
	return 0;
}
```

---

## 作者：Petit_Souris (赞：3)

首先，题意要求所有长度为 $n$ 的置换的所有环长的 lcm 之积。

设 $f_x$ 表示有多少置换满足所有环长的 lcm 为 $x$ 的倍数，那么答案即为 $\prod\limits_{p^c\le n} p^{f_{p^c}}$，其中 $p$ 为质数（容易发现每个 $p^c$ 恰好贡献了 $c$ 个 $p$，是正确的）。

那么现在问题转为求解 $f_{1},f_2,\dots,f_{n} \bmod 10^9+\color{red}{6}$（因为 $f$ 在指数上）。枚举 $x$，假设现在正在计算 $f_{x}$。

考虑容斥，设 $g_{i}$ 为长度为 $i$ 的置换中有多少满足**每个环长度都不是** $x$ 的倍数，$h_{i}$ 为长度为 $i$ 的置换中有多少满足**每个环长度都是** $x$ 的倍数。容易得到转移：

$$g_{i}=i!-\sum\limits_{j\le i,x|j}\binom{i}{j}g_{i-j}h_{j}$$

$$h_{i}=\sum\limits_{j\le i,x|j}\binom{i-1}{j-1}(j-1)!h_{i-j}$$

第一条转移式中，我们用所有置换减去有至少一个环是 $x$ 的倍数的方案数，枚举这些满足条件的环的长度总和 $j$ 并从 $i$ 个中选出 $j$ 个转移。

第二条转移式中，我们枚举 $1$ 所在置换环的大小 $j$，即从 $2\sim i$ 中选出 $j-1$ 个和 $1$ 放在一个环里，再乘上圆排列的系数 $(j-1)!$。

预处理一下组合数就可以避免逆元了（现在的模数是合数），需要 $\mathcal O(n^2)$ 的空间。

直接做的复杂度是 $\mathcal O(n^2\log n)$ 的，但是容易发现每次 dp，$g$ 只有 $i\equiv n \pmod x$ 的 $i$ 有用，$h$ 只有 $i\equiv 0 \pmod x$ 的 $i$ 有用，因此复杂度实际上为 $\mathcal O(\sum\limits_{i=1}^{n}{\frac{n^2}{i^2}})=\mathcal O(n^2)$，完全不卡常，不用 barrett 也可以在 1/2 时限内通过。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=7503;
ll n,Mod,Mod2,f[N],g[N],fac[N];
ll C[N][N],pr[N],prc;
bool vis[N];
using L=__uint128_t;
struct FastMod{
    ull b,m;
    FastMod(ull b):b(b),m(ull((L(1)<<64)/b)){}
    ull operator()(ull a){
        ull q=(ull)((L(m)*a)>>64);
        ull r=a-q*b;
        return r>=b?r-b:r;
    }
}R(2);
ll pw(ll x,ll p){
    ll res=1;
    while(p){
        if(p&1)res=res*x%Mod;
        x=x*x%Mod,p>>=1;
    }
    return res;
}
void Init(){
    vis[1]=1;
    rep(i,2,n){
        if(!vis[i])pr[++prc]=i;
        rep(j,1,prc){
            if(pr[j]*i>n)break;
            vis[pr[j]*i]=1;
            if(i%pr[j]==0)break;
        }
    }
}
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read(),Mod=read(),Mod2=Mod-1;
    R=FastMod(Mod2);
    Init();
    rep(i,0,n){
        C[i][0]=1;
        rep(j,1,i)C[i][j]=R(C[i-1][j]+C[i-1][j-1]);
    }
    fac[0]=1;
    rep(i,1,n)fac[i]=R(fac[i-1]*i);
    ll ans=1;
    rep(p,1,n){
        if(vis[p])continue;
        ll x=p,c=0,tot=0;
        while(x<=n){
            f[0]=1,g[0]=1;
            rep(i,1,n){
                if(i%x==0){
                    g[i]=0;
                    for(ll j=x;j<=i;j+=x)g[i]=R(g[i]+R(g[i-j]*C[i-1][j-1])*fac[j-1]);
                }
                if((n-i)%x==0){
                    f[i]=fac[i];
                    for(ll j=x;j<=i;j+=x)f[i]=R(f[i]-R(R(g[j]*f[i-j])*C[i][j])+Mod2);
                }
            }
            tot=R(tot+fac[n]-f[n]+Mod2);
            x*=p;
        }
        tot=R(tot+Mod2);
        ans=ans*pw(p,tot)%Mod;
    }
    write(ans);
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：forest114514 (赞：2)

一个更无脑的（?）GF做法（至少所有的步骤都是常见操作），还有这是第一次见有 DS 优化的纯计数题还挺有趣的。

所有排列的置换的所有环长 LCM 之积，我们直接拆贡献到每个质数，相当于就是对于一个 $p^c$，存在一个数有 $p^c$ 因子，对于一个 $p^c$ 我们实际计算的是为 $p^c$ 倍数的排列的数量，所以可以差分一下得到恰好为 $p^c$ 的。

计算至少存在一个考虑容斥，我们先钦定一个子集合法，相当于设计容斥系数 $f_i$ 满足 $g_{n}=\sum\limits_{i=0}^{n}\binom{n}{i}f_{i},g_{n}=[n\neq 0]$，这个系数为 $f_{i}=[i\neq 0](-1)^{i-1}$。

有标号计数考虑 EGF 分配点的编号，注意到我们环的 EGF 形式是 $\sum\limits_{i\geq 1} \frac{a_ix^i}{i}$，对一个环的 EGF 就是 $\sum\limits_{i\geq 1} \frac{x^i}{i}=-\ln(1-x)$，所以没被钦定是倍数的环 EGF 就是 $\exp(-\ln(1-x))=\frac{1}{1-x}$；钦定是倍数的部分呢我们在 exp 的时候把 $-1$ 的系数加上，最后把多的 $-1$ 的系数补回去再修正常数项误差使得满足容斥系数 $[i\neq 0]$ 的限制，这样发现 EGF 就是 $1-\exp(-\sum\limits_{i\geq 1} \frac{x^{p^ci}}{p^ci})=1-\exp(\frac{1}{p^c}\ln(1-x^{p^c}) )=1-(1-x^{p^c})^{\frac{1}{p^c}}$。

所以对于 $p^c$ 我们的答案就是 $[x^n]\frac{n!}{1-x}(1-(1-x^{p^c})^{\frac{1}{p^c}})=n!-[x^n]\frac{n!}{1-x}(1-x^{p^c})^{\frac{1}{p^c}}$。

注意到乘上 $\frac{1}{1-x}$  相当于做前缀和，所以我们最后要解决的问题是对 $(1-x)^{\frac{1}{p^c}}$ 求出 $0\sim\lfloor\frac{n}{p^c}\rfloor$ 项的系数和。

注意到 $F(x)=(1-x)^{\frac{1}{p^c}}$ 是一个短多项式的幂次，套路地考虑 ODE，不难发现有 $F(x)+p^c(1-x)F^{\prime}(x)=0$，对 $[x^n]$ 提取系数得到：
$$
\begin{aligned}
\ [x^n]F(x)+(n+1)p^c [x^{n+1}]F(x)-p^cn[x^n] F(x)&=0\\
(n+1)p^c[x^{n+1}]F(x)&=(p^cn-1)[x^n]F(x)\\
[x^{n+1}]F(x)&=\frac{p^cn-1}{(n+1)p^c}[x^n]F(x)
\end{aligned}
$$
因为 $[x^0]F(x)=1$，所以我们不难得到：
$$
[x^n]F(x)=\frac{1}{n!(p^c)^n}\prod\limits_{i=0}^{n-1}(p^ci-1)
$$
所以我们的答案为 $-\sum\limits_{i=1}^{\lfloor\frac{n}{p^c}\rfloor}\frac{n!}{i!(p^c)^i}\prod\limits_{j=0}^{i-1}(p^cj-1)$，不难发现关键在于我们要在模数不为质数的时候求出 $\frac{n!}{i!(p^c)^i}=\frac{n!}{\prod\limits_{j=1}^{i}p^cj}$。

注意到 $n\geq p^ci$，所以 $n!$ 中 $p^c$ 的这些倍数都出现过，直接考虑哪些被删了，所以不难发现我们要求的是 $\prod\limits_{i=1}^{n} [p^c\nmid i]i\times \prod\limits_{j=i+1}^{n} p^cj$，后者简单的，前者可以拆成 $O(\lfloor\frac{n}{p^c}\rfloor)$ 段区间乘积。

注意到 $O(\sum\limits_{p\in prime,p^c\leq n}\lfloor\frac{n}{p^c}\rfloor)=O(\sum\limits_{p\in prime}\lfloor\frac{n}{p}\rfloor)=O(n\log\log n)$，所以最后相当于瓶颈在于求 $O(n\log \log n)$ 次区间乘积，写一个任意的你喜欢的静态区间半群查询就能做到 $O(n\log \log n)$ 了。

偷懒写的线段树，反正本题 $n=7500$ 也不用那么严格的 $O(n\log\log n)$：

```cpp
const int N=7600;
int n,M,P,fac[N];
LL ksm(LL a,LL b,LL mod){
    LL res=1;for(;b;b>>=1,a=a*a%mod) if(b&1) res=res*a%mod;return res;
}
struct DS{
    int mul[N<<2];
    void init(int x,int l,int r){
        if(l==r) return mul[x]=l,void();
        int mid=l+r>>1;
        init(ls(x),l,mid),init(rs(x),mid+1,r);
        mul[x]=1ll*mul[ls(x)]*mul[rs(x)]%P;

    }
    int query(int x,int l,int r,int L,int R){
        if(L<=l&&r<=R) return mul[x];
        int mid=l+r>>1,res=1;
        if(mid>=L) res=query(ls(x),l,mid,L,R);
        if(mid<R) res=1ll*res*query(rs(x),mid+1,r,L,R)%P;
        return res;
    }
}TR;
bitset<N> vis;
LL pre[N],suf[N];
LL solve(int x){
    LL res=0;
    int lim=n/x;
    pre[0]=1;
    rep(i,1,lim) pre[i]=(1ll*x*(i-1)+P-1)%P*pre[i-1]%P;
    suf[lim+1]=1;
    per(i,lim,1) suf[i]=suf[i+1]*x%P*i%P;
    LL tmp=1,cur=0;
    for(cur=x;cur<=n;cur+=x)tmp=tmp*TR.query(1,1,n,cur-x+1,cur-1)%P;
    cur-=x;
    if(cur<n) tmp=tmp*TR.query(1,1,n,cur+1,n)%P;
    rep(i,1,lim) res+=tmp*suf[i+1]%P*pre[i]%P;
    return (P-res%P)%P;

}
LL ret[N];
bool _ED;
signed main(){
	fprintf(stderr,"%.20lf MB\n",(&_ST-&_ED)/1048576.0);
    read(n,M),P=M-1;
    TR.init(1,1,n);
    fac[0]=1;
    rep(i,1,n) fac[i]=fac[i-1]*i%P;
    LL ans=1;
    rep(i,2,n){
        if(vis[i]) continue;
        for(int j=i+i;j<=n;j+=i) vis[j]=1;
        int k=1;
        for(int j=i;;j*=i,++k){
            ret[k]=solve(j);
            if(j>n/i) break;
        }
        ret[k+1]=0;
        rep(j,1,k) ans=ans*ksm(i,(ret[j]-ret[j+1]+P)*j%P,M)%M;
    }
    write(ans,'\n');
	fprintf(stderr,"%.4lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：vectorwyx (赞：2)

大家好，我不会 Min-Max 容斥，所以我用生成函数机械地解决了本题。

前置知识：$\sum_i\frac{x^i}{i}=-\ln(1-x)$（证明考虑两边求导），以及广义二项式定理 $(x+y)^\alpha=\sum_{i=0}^{\infty}\binom{\alpha}{i}x^iy^{\alpha-i}$。

一个排列的阶等于这个排列中所有环环长的 lcm。本题所求是所有的 lcm 乘起来，那一个自然的想法是对于每个质数 $p$ 单独考虑它在乘积中出现了多少次。对于一个排列，记它包含的第 $i$ 个环的环长质因数分解后 $p$ 的指数为 $a_i$，那么这个排列的贡献是 $\max a_i$ 次。考虑 $\max a_i=\sum_{j=1}^{n}[\max a_i\ge j]$，所以其实我们只需要对每个 $p^k\le n$ 求有多少个排列包含环长为 $p^k$ 倍数的环。

正难则反，改为求有多少个排列不包含环长为 $p^k$ 倍数的环。接下来我们考虑一个类似背包的东西，把大小为 $i(p^k\nmid i)$ 的环看做物品，那么相当于用这些物品去做一个大小为 $n$ 的背包。问题在于，同样大小的环如果有多个，系数会额外带一个阶乘逆元。类似多重背包，我们需要枚举大小为 $i$ 的环有多少个，写出来就是：
$$
n!\prod_{p^k\nmid i}\sum_{j=0}^\infty \frac{x^{ij}}{i^jj!}
$$
$\frac{n!}{i^j}$ 是说，假设我们选出来的环长依次为 $a_1,a_2,\cdots,a_m(\sum_{i=1}^ma_i=n,i\not=j\iff a_i\not=a_j)$，记 $S_i=\sum_{j=1}^i a_j$，那么方案数是 $\prod_{i=1}^m\binom{n-S_{i-1}}{a_i}(a_i-1)!$，把组合数写成阶乘的形式再约分就变成了 $\frac{n!}{\prod a_i}$。$\frac{1}{j!}$ 是说，如果有相同长度的环，只需要再乘上该长度的环的个数的阶乘逆元。

继续推（令 $d=p^k$）：
$$
\because\sum_{j}\frac{x^{ij}}{i^jj!}=\sum_j(\frac{x^i}{i})^j\frac{1}{j!}=e^{\frac{x^i}{i}}\\
\therefore n!\prod_{d\nmid i}\sum_{j=0}^\infty \frac{x^{ij}}{i^jj!}=n!\prod_{d\nmid i}e^{\frac{x^i}{i}}=n!\frac{\exp\left(\sum_i\frac{x^i}{i}\right)}{\exp\left(\sum_{d|i}\frac{x^i}{i}\right)}\\
又\because \sum_i \frac{x^i}{i}=-\ln(1-x),\sum_{d|i}\frac{x^{i}}{i}=\frac{\sum_{i}\frac{(x^d)^i}{i}}{d}=\frac{-\ln(1-x^d)}{d}\\
\therefore n!\frac{\exp\left(\sum_i\frac{x^i}{i}\right)}{\exp\left(\sum_{d|i}\frac{x^i}{i}\right)}=n!\frac{1}{1-x}(1-x^d)^{\frac{1}{d}}
$$
然后展开成幂级数，$\frac{1}{1-x}=\sum_i x^i$，$(1-x^d)^{\frac{1}{d}}=\sum_{i=0}^{\infty}\binom{\frac{1}{d}}{i}x^{di}(-1)^i$。由于我们只关心这两个幂级数的乘积在 $x^n$ 处的点值，其实就是求 $\sum_{i=0}^{\frac{n}{d}}(-1)^i\binom{\frac{1}{d}}{i}$。注意这是不包含环长为 $d$ 倍数的环时的情况，包含的方案数即为 $n!-n!\sum_{i=0}^{\frac{n}{d}}(-1)^i\binom{\frac{1}{d}}{i}=n!\sum_{i=1}^{\frac{n}{d}}(-1)^{i-1}\binom{\frac{1}{d}}{i}$。这里难受的点在于这个式子是在指数上的，所以模数是 $M-1$ 而非 $M$，此时 $d$ 可能不存在逆元。怎么办呢？把 $\binom{\frac{1}{d}}{i}$ 写成 $\frac{\prod_{j=0}^{i-1}(1-jd)}{d^i i!}$，然后把 $n!$ 放进来变成 $\frac{n!}{d^i i!}\prod_{j=0}^{i-1}(1-jd)$。$\frac{n!}{d^ii!}$其实就是 $\left(\prod_{j=1}^{di}[d\nmid j]j\right)\left(\prod_{j=di+1}^nj\right)$，这样就避开了逆元。然后你发现 $\prod_{j=di+1}^nj$ 和 $\prod_{j=0}^{i-1}(1-jd)$ 都可以方便地预处理出来，$\prod_{j=1}^{di}[d\nmid j]j$ 可以拆成 $i$ 段区间半群信息查询，这是复杂度瓶颈。由于质数倒数和是 $\log\log n$ 级别的，所以这里有 $O(n\log\log n)$ 次查询，采用 $O(n\log\log n)-O(1)$ 的 sqrt tree 即可做到 $O(n\log\log n)$。不过本题 $n\le 7500$，完全可以暴力查询。

代码如下：（码 $\LaTeX$ 不易，点个赞再走好不好QAQ）
```
#include<bits/stdc++.h>
namespace vectorwyx{
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define uint unsigned
#define ull unsigned long long
#define umap unordered_map
#define db double
#define fo(i,x,y) for(int i=(x);i<=(y);++i)
#define go(i,x,y) for(int i=(x);i>=(y);--i)
#define ptc putchar
#define gtc getchar
#define emp emplace
#define re return
#define co continue
#define brk break
#define HH (ptc('\n'))
#define bctz __builtin_ctz
#define bclz __builtin_clz
#define bppc __builtin_popcount
using namespace std;
ll seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return (int)(rnd()%(y-x+1ll)+x);}
inline int read(){signed ch=getchar();int x=0,f=1;while(!isdigit(ch)){if(ch==(int)('-'))f=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
template<typename T> void out(T *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

namespace Fmod{
// typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod{
    ull b, m;
    FastMod(ull b) : b(b), m((ull)((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
}
using Fmod::FastMod;
FastMod F(2);
const int N=7505;
int n,mod,fac[N],C[N][N],ifac[N],inv[N],vis[N],ti,tmp[N],coe[N];
#define pro(x,y) (int)(F.reduce((ll)(x)*(y)))
#define mul(x,y) x=pro(x,y)
#define modS(x) x=x>=mod?x-mod:x
#define modA(x) x=x<0?x+mod:x
#define sub(x,y) x-=y,modA(x)
#define add(x,y) x+=y,modS(x)
int ksm(int x,int y){
    int ret=1;
    while(y){
        if(y&1) ret=(int)((ll)ret*x%(mod+1));
        x=(int)((ll)x*x%(mod+1));
        y>>=1;
    }
    re ret;
}

bool chk(int x){
    fo(i,2,x-1){
        if(x%i==0) re 0;
        if(i*i>x) break;
    }
    re 1;
}

int f[N];

int calc(int d,int i){//n!*C(1/d,i)
    // printf("calc(%d,%d)\n",d,i);
    int ret=1;
    fo(j,1,i*d) if(j%d) mul(ret,j);
    fo(j,i*d+1,n) mul(ret,j);
    fo(j,1,i) mul(ret,(1-(j-1)*d+mod));
    // printf("ret=%d\n",ret);
    re ret;
}

signed main(){
    cin>>n>>mod;--mod;F=FastMod(mod);
    fo(i,0,n){
        C[i][0]=1;
        fo(j,1,i) C[i][j]=C[i-1][j-1]+C[i-1][j],modS(C[i][j]);
    }
    fac[0]=1;fo(i,1,n) fac[i]=pro(i,fac[i-1]);
    int ans=1;
    fo(i,2,n) if(chk(i)){
        // printf("%d!!!!!!!!!!!!\n",i);
        int x=i,rp=0;
        while(x<=n){
            f[++rp]=0;
            fo(j,1,n/x){
                int v=calc(x,j);
                if(j&1) add(f[rp],v);
                else sub(f[rp],v);
            }
            x*=i;
        }
        // cout<<"f:";out(f,1,rp);
        // fo(j,1,rp-1) sub(f[j],f[j+1]);
        int sum=0;
        fo(j,1,rp) add(sum,f[j]);
        // fo(j,1,rp) add(sum,pro(j,f[j]));
        // printf("sum=%d\n",sum);
        ans=(int)((ll)ans*ksm(i,sum)%(mod+1));
    }
    cout<<ans;
    return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：7KByte (赞：2)

综合数数题。技巧性很强。

转化一下，求所有长度为 $n$ 的排列的置换环的长度的 $\rm lcm$ 的乘积。

考虑转化为数数问题，求 $x=\rm lcm$ 的排列个数。

还是不好求，转化为前缀和，求 $x\mid \rm lcm$ 的排列个数。

这个形式就比较好看，因为这等价于对于每个质数幂，求 $p^c \mid \rm lcm$ 的排列个数，记作 $\mathcal{F}(p^c)$，那么答案就是 $\prod\limits_{p,c}p^{\mathcal{F}(p^c)}$。

现在我们要求 $\mathcal{F}(x)$ ，表示 $x\mid \rm lcm$ 的排列个数，等价于存在一个置换环是 $x$ 的倍数的排列个数。

**存在至少一个** 这个玩意不好求，我们求补集，即不存在长度为 $x$ 的倍数的置换环的排列数。记作 $f(x)$。

发现这 $f(x)$ 还是不好求，我们考虑再求一次补集，即枚举长度为 $x$ 的倍数的置换环长度之和，对应的方案数为 $g(x)$。那么我们不难得到转移方程。

$$f_i=i!-\sum\limits_{0\le j< i}\binom{i}{j}f_j\times g_{i-j}$$

那么 $g(i)$ 的转移呢？首先 $g(i)$ 中 $i$ 一定是 $x$ 的倍数。我们枚举包括第一个点的置换长度，得到转移方程。

$$g_i=\sum\limits_{0\le j<i}\binom{i-1}{i-j-1}(i-j-1)!g_j$$ 

有值的 $g$ 只有 $\frac{n}{x}$ 个，所以有用的 $f$ 也只有 $\frac{n}{x}$个，时间复杂度为 $\mathcal{O}(n^2)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 7505
using namespace std;
int n,P,Q,f[N],g[N],c[N][N],v[N],fac[N];
int Pow(int x,int y){int now=1;for(;y;y>>=1,x=1LL*x*x%P)if(y&1)now=1LL*now*x%P;return now;}
int calc(int x){
	g[0]=1;
	for(int i=x;i<=n;i+=x){
		g[i] = 0;
		for(int j=0;j<i;j+=x)g[i]=(g[i]+1LL*g[j]*c[i-1][i-j-1]%Q*fac[i-j-1])%Q;
	}
	int st = n % x;
	f[st] = fac[st] ;
	for(int i=st+x;i<=n;i+=x){
		f[i] = fac[i] ;
		for(int j=st;j<i;j+=x)f[i]=(f[i]-1LL*c[i][j]*f[j]%Q*g[i-j])%Q;
	}
	return (0LL+fac[n]-f[n]+Q)%Q;
}
int main(){
	scanf("%d%d",&n,&P);Q=P-1;
	rep(i,0,n){c[i][0]=1;rep(j,1,i)c[i][j]=(c[i-1][j]+c[i-1][j-1])%Q;}
	fac[0]=1;rep(i,1,n)fac[i]=1LL*fac[i-1]*i%Q;
	int ans=1;
	rep(i,2,n)if(!v[i]){
		for(int j=i*i;j<=n;j+=i)v[j]=1;
		for(int j=i;j<=n;j*=i)ans=1LL*ans*Pow(i,calc(j))%P;
	}
	printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：DaiRuiChen007 (赞：1)

# P6276 题解



**题目大意**

> 对于一个长度为 $n$ 的排列 $p$，定义 $S(p)$ 为最小的 $n$ 使得 $p^n=e$，其中 $e$ 是单位排列。
>
> 求 $\prod_pS(p)$。
>
> 数据范围：$n\le 7500$。

**思路分析**

显然 $S(p)$ 就是 $p$ 分解出的每一个置换环的 $\operatorname{lcm}$。

经典套路，先拆成质因数分析，然后考虑对每个 $p^c$ 计算有多少个排列 $q$ 使得 $p^c\mid f(q)$，记为 $S(p^c)$，显然答案就是 $\prod_pp^{\sum_cF(p^c)}=\prod_p\prod_c p^{F(p^c)}$。

考虑如何计算 $F(x)$，注意到 $p^c\mid f(q)$ 当且仅当存在一个置换环大小为 $p^c$ 的倍数。

因此反面考虑，设 $f_i$ 表示 $1\sim i$ 的排列的所有置换环都不是 $x$ 的倍数的方案数，再容斥，设 $g_i$ 表示 $1\sim i$ 的排列所有置换环都是 $x$ 倍数的方案数。

求 $g_i$ 就是经典枚举 $i$ 所在置换环大小：
$$
g_i=\sum_{x\mid j}\binom{i-1}{j-1}\times (j-1)!\times g_{i-j}
$$


求 $f_i$ 就容斥枚举是 $x$ 倍数的环有多少：
$$
f_i=i!-\sum_{x\mid j}\binom{i}{j}g_jf_{i-j}
$$
最终 $F(x)=n!-f_n$，答案记得对 $P-1$ 取模。

观察到我们只要 $i\bmod x=0$ 处的 $g_i$ 和 $i\bmod x=n\bmod x$ 处的 $f_i$，暴力容斥复杂度为 $\mathcal O\left(\dfrac{n^2}{x^2}\right)$，总复杂度不超过 $\mathcal O\left(n^2\times \sum_{i=1}^n\dfrac{1}{i^2}\right)=O(n^2)$。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=7505;
int n,MOD,P,f[MAXN],g[MAXN],C[MAXN][MAXN],fac[MAXN];
//f[]: all non p, g[]: all p
bool isp[MAXN];
inline int ksm(int a,int b,int p) {
	int res=1;
	for(;b;a=1ll*a*a%p,b=b>>1) if(b&1) res=1ll*res*a%p;
	return res;
}
inline int solve(int p) {
	g[0]=1;
	for(int i=p;i<=n;i+=p) {
		g[i]=0;
		for(int j=p;j<=i;j+=p) g[i]=(g[i]+1ll*C[i-1][j-1]*fac[j-1]%P*g[i-j])%P;
	}
	for(int i=n%p;i<=n;i+=p) {
		f[i]=fac[i];
		for(int j=p;j<=i;j+=p) f[i]=(f[i]+P-1ll*g[j]*f[i-j]%P*C[i][j]%P)%P;
	}
	return (fac[n]+P-f[n])%P;
}
signed main() {
	scanf("%d%d",&n,&MOD),P=MOD-1;
	for(int i=0;i<=n;++i) for(int j=C[i][0]=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	for(int i=fac[0]=1;i<=n;++i) fac[i]=1ll*fac[i-1]*i%P;
	int ans=1; fill(isp+2,isp+n+1,true);
	for(int i=2;i<=n;++i) if(isp[i]) {
		for(int j=i;j<=n;j+=i) isp[j]=false ;
		for(int j=i;j<=n;j*=i) ans=1ll*ans*ksm(i,solve(j),MOD)%MOD;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：zifanwang (赞：1)

[传送门](https://www.luogu.com.cn/problem/P6276)

## Statement

求所有长度为 $n$ 的排列的所有置换环的长度的**最小公倍数**的乘积。

$n\le 7500$。

## Solution

显然有：

$$\text{答案}=\prod_{p^k, p\in \operatorname{prime}}p^{\text{存在一个置换环的长度为} p^k \text{的倍数的排列的个数}}$$

枚举 $p^k$，记 $x=p^k$，考虑怎么计算 “存在一个置换环的长度为 $p^k$ 的倍数的排列的个数”。发现直接求不好求，正难则反，考虑求其补集。

记 $f_n$ 表示 “不存在一个置换环的长度为 $p^k$ 的倍数的排列的个数”。发现还是不好求，于是再做一次减法。记 $g_n$ 表示 “所有置换环的长度为 $p^k$ 的倍数且长度为 $n$ 的排列的个数”。易得：

$$g_n=\sum_{x\le i\le n,x|i}{n-1\choose i-1}(i-1)!g_{n-i}$$

$$f_n=n!-\sum_{x\le i\le n,x|i}{n\choose i}g_i\times f_{n-i}$$

那么对答案的贡献就是 $\times p^{n!-f_n}$。

发现 $g_n$ 和 $f_n$ 都只有 $\lfloor\frac{n}{x}\rfloor$ 个的值不为 $0$，总时间复杂度 $\le O(\sum_{x=1}^n\frac{n^2}{x^2})=O(n^2)$。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 7503
#define rep(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
int n,t,md,md1,d[mxn],p[mxn],f[mxn],g[mxn],c[mxn][mxn];
ll ans,fac[mxn];
int power(int x,int y){
	int ans=1;
	for(;y;y>>=1){
		if(y&1)ans=(ll)ans*x%md;
		x=(ll)x*x%md;
	}
	return ans;
}
signed main(){
	cin>>n>>md,md1=md-1;
	fac[0]=1;
	rep(i,1,n)fac[i]=fac[i-1]*i%md1;
	c[0][0]=1;
	rep(i,1,n){
		c[i][0]=1;
		rep(j,1,i)c[i][j]=(c[i-1][j-1]+c[i-1][j])%md1;
	}
	rep(i,2,n){
		if(!d[i])d[i]=p[++t]=i;
		rep(j,1,t){
			if(p[j]>d[i]||p[j]>n/i)break;
			d[i*p[j]]=p[j];
		}
	}
	ans=1;
	rep(i,2,n)if(d[i]==i){
		int x=i;
		while(1){
			g[0]=1;
			for(int i=x;i<=n;i+=x){
				g[i]=0;
				for(int j=x;j<=i;j+=x){
					g[i]=(g[i]+g[i-j]*fac[j-1]%md1*c[i-1][j-1])%md1;
				}
			}
			f[0]=1;
			rep(i,1,n)if((n-i)%x==0){
				f[i]=fac[i];
				for(int j=x;j<=i;j+=x)f[i]=(f[i]-(ll)f[i-j]*g[j]%md1*c[i][j])%md1;
			}
			ans=ans*power(i,(fac[n]-f[n]+md1)%md1)%md;
			if((ll)x*i>n)break;
			x*=i;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Anonymely (赞：0)

优秀的 Min-Max 容斥练习题。

显然答案为环长的 $\text{lcm}$ 乘积，而对于 $\text{lcm}$ 不好记数，故考虑 Min-Max 容斥，变为对子集的 $\gcd$ 计数带上容斥系数。

考虑枚举一个 $d$ 表示 $\gcd$，做一个 dp 求出 $x$ 个数被许多环长为 $d$ 的倍数的环组成的方案数，这里要带容斥系数，最后枚举一下 $x$，剩下的 $n-x$ 的数没有限制，也就是 $n-x$ 随便被环分割的方案数，这个众所周知是 $(n-x)!$，可以考虑排列是环排列的 $\exp$。

但是这样无法保证 $\gcd$ 正好是 $d$，实际上计算的是 $\gcd$ 为 $d$ 的倍数的方案数，于是最后再做一遍莫反即可。

复杂度为 $\sum_{i=1}^n (\frac{n}{i})^2=n^2\times\sum_{i=1}^n \frac{1}{i^2}= n^2 \times \frac{\pi^2}{6}=O(n^2)$。

---

