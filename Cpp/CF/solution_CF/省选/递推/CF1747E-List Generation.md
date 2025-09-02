# List Generation

## 题目描述

For given integers $ n $ and $ m $ , let's call a pair of arrays $ a $ and $ b $ of integers good, if they satisfy the following conditions:

- $ a $ and $ b $ have the same length, let their length be $ k $ .
- $ k \ge 2 $ and $ a_1 = 0, a_k = n, b_1 = 0, b_k = m $ .
- For each $ 1 < i \le k $ the following holds: $ a_i \geq a_{i - 1} $ , $ b_i \geq b_{i - 1} $ , and $ a_i + b_i \neq a_{i - 1} + b_{i - 1} $ .

Find the sum of $ |a| $ over all good pairs of arrays $ (a,b) $ . Since the answer can be very large, output it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first testcase, the good pairs of arrays are

- $ ([0, 1], [0, 1]) $ , length = $ 2 $ .
- $ ([0, 1, 1], [0, 0, 1]) $ , length = $ 3 $ .
- $ ([0, 0, 1], [0, 1, 1]) $ , length = $ 3 $ .

Hence the sum of the lengths would be $ {2 + 3 + 3} = 8 $ .

## 样例 #1

### 输入

```
4
1 1
1 2
2 2
100 100```

### 输出

```
8
26
101
886336572```

# 题解

## 作者：EuphoricStar (赞：17)

考虑将问题抽象成：左上角为 $(0,0)$、右下角为 $(n,m)$ 的网格图，求所有满足至少有一条 **只向下或向右走的路径** 经过点集内所有点的的不同的点集大小之和。

显然对于一个合法的点集，经过它的路径可能不止一条，去重也很麻烦。考虑钦定两个点间的访问顺序，比如先向下再向右走，这样对于每个合法的点集，都有且仅有一条经过它的路径。

将路径的 **拐点** 分为两类：先向右再向下和先向下再向右。如下图，红色点表示第一类拐点，蓝色点表示第二类拐点。

![](https://s1.ax1x.com/2022/11/06/xX4Qts.png)

考虑 **枚举先向右再向下的拐点个数** ，设有 $i$ 个。选择拐点的方案为 $\dbinom{n}{i}\dbinom{m}{i}$（纵坐标范围 $[0,n-1]$，横坐标范围 $[1,m]$）。这样就唯一确定了一条路径。路径上还有 $s=n+m-i-1$ 个点，这 $i$ 个点可以任选，总贡献为 $\sum\limits_{j=0}^s \dbinom{s}{j}(i+2+j) = (i+2)2^s + \sum\limits_{j=0}^s \dbinom{s}{j}j$。

考虑 $\sum\limits_{j=0}^s \dbinom{s}{j}j$ 这部分如何快速计算。注意到 $\sum\limits_{j=0}^s \dbinom{s}{j}j = \sum\limits_{j=0}^s \dbinom{s}{j}(s-j)$，相加再除以 $2$ 后得原式 $= s2^{s-1}$。

[code](https://codeforces.com/contest/1747/submission/179483153)

---

## 作者：5ab_juruo (赞：15)

给一种简单一点的式子。

固定长度 $|a|=|b|=k+1$，将 $a,b$ 做差分以后，原题意等价于：有 $k$ 个盒子，$n$ 个相同的红球和 $m$ 个相同的蓝球。没有盒子是空的方案。考虑容斥，钦定 $i$ 个盒子空的方案可以用插板法计算，所以答案就是：

$$
\sum_{k=1}^{n+m}(k+1)\sum_{i=1}^k(-1)^{k-i}\binom{k}{i}\binom{n+i-1}{i-1}\binom{m+i-1}{i-1}
$$

观察到关于 $i$ 的项更多，交换枚举顺序：

$$
\begin{aligned}
&\sum_{i=1}^{n+m}\binom{n+i-1}{i-1}\binom{m+i-1}{i-1}\sum_{k=i}^{n+m}(k+1)(-1)^{k-i}\binom{k}{i}\\
=&\sum_{i=1}^{n+m}\binom{n+i-1}{i-1}\binom{m+i-1}{i-1}(i+1)\sum_{k=i}^{n+m}(-1)^{k-i}\binom{k+1}{k-i}
\end{aligned}
$$

根据 [P8558 黑暗](https://www.luogu.com.cn/problem/P8558) 的套路，用 $j=k-i$ 替代 $k$ 来枚举：

$$
\sum_{k=i}^{n+m}(-1)^{k-i}\binom{k+1}{k-i}=\sum_{j=0}^{n+m-i}(-1)^j\binom{i+j+1}{j}
$$

设 $F(i,j)=(-1)^j\dbinom{i+j+1}{j}$，$G(i)=\sum\limits_{j=0}^{n+m-i}F(i,j)$，考虑 $G(i)$ 的线性递推，先考虑 $F(i,j)$ 的递推：

$$
\begin{aligned}
F(i,j)&=(-1)^j\binom{i+j+1}{j}\\
&=(-1)^j\binom{i+j}{j}+(-1)^j\binom{i+j}{j-1}\\
&=F(i-1, j)-F(i,j-1)
\end{aligned}
$$

则可以得到 $G(i)$ 的递推式：

$$
\begin{aligned}
G(i)&=\sum_{j=0}^{n+m-i}F(i,j)\\
&=\sum_{j=1}^{n+m-i}F(i-1,j)-F(i,j-1)\\
&=\sum_{j=1}^{n+m-i}F(i-1,j)-\sum_{j=0}^{n+m-i-1}F(i,j)\\
&=(G(i-1)-F(i-1,n+m-i+1))-(G(i)-F(i,n+m-i))
\end{aligned}
$$

移项一下：

$$
G(i-1)=2G(i)+F(i-1,n+m-i+1)-F(i,n+m-i)
$$

结合前面的式子直接枚举就好了。复杂度 $\mathcal{O}(n+m)$。注意预处理阶乘要处理到 $n+m+\max(n,m)$。

```cpp
const int mod = int(1e9) + 7, max_n = 5000000, max_fs = max_n * 3;

using mint = mod_int<mod>;
mint fac[max_fs], ifac[max_fs];

inline mint C(int a, int b) { return fac[a] * ifac[b] * ifac[a - b]; }
inline int getpw(int x) { return (x & 1) ? -1 : 1; }
inline mint F(int i, int j) { return C(i + j + 1, j) * getpw(j); }

signed main()
{
	fac[0] = 1;
	for (int i = 1; i < max_fs; i++)
		fac[i] = fac[i - 1] * i;
	ifac[max_fs - 1] = fac[max_fs - 1].inv();
	for (int i = max_fs - 1; i > 0; i--)
		ifac[i - 1] = ifac[i] * i;
	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int cas, n, m;
	
	cin >> cas;
	while (cas--)
	{
		cin >> n >> m;
		
		mint ans = 0, G = F(n + m, 0);
		for (int i = n + m; i >= 1; i--)
		{
			ans += G * (i + 1) * C(n + i - 1, i - 1) * C(m + i - 1, i - 1);
			if (i > 1)
				G = G * 2 - F(i, n + m - i) + F(i - 1, n + m - i + 1);
		}
		
		cout << ans << "\n";
	}
	
	return 0;
}
// started coding at: 11-06 19:49:58
// finished debugging at: 11-06 20:25:52
```

---

## 作者：stntn (赞：10)

## 简要题意

给你两个数 $n,m$，求所有满足以下条件的一对数组，的长度之和：

1.  数组 $a,b$ 长度均为 $k(k \ge 2)$。

1. $a_0=b_0=0,a_k=n,b_k=m$。

1. 对于所有 $1 < i \le k,a_i\ge a_{i-1},b_i \ge b_{i-1},a_i+b_i > a_{i-1}+b_{i-1}$。

## 推式子

化简一下题意就可以知道，$a,b$ 单调不降，且不能同一位置与前一个数相等。

先上初步的答案式（由@Neutralized 大佬提供）：

$$
Ans=\sum_{k=1} (k+1) \sum_{i=1}^k \binom{n-1}{i-1} \binom{k}{i} \sum_{j=1}^k \binom{m-1}{j-1} \binom{i}{k-j}
$$

大概是这个意思：先枚举两个数组的长度，然后枚举并选择 $a$ 数组上升的位置，从 $n-1$ 个数中选若干数填进去，$b$ 同理。

考虑化简，后面枚举 $j$ 的部分显然可以范德蒙德卷积。

$$
Ans=\sum_{k=1} (k+1) \sum_{i=1}^k  \binom{n-1}{i-1} \binom{k}{i} \binom{m+i-1}{k-1}
$$

后面上下减一看起来很烦，我们把它抽出来。

$$
Ans= \frac{1}{n} \sum_{k=1} k(k+1) \sum_{i=1}^k \binom{n}{i} \binom{k}{i} \binom{m+i}{k} \frac{i}{m+i}
$$

把右边的两个 $k$ 处理到一个上面去，然后交换求和顺序。

$$
Ans= \frac{1}{n} \sum_{i=1} \binom{n}{i} \binom{m+i-1}{i-1}  \sum_{k=i} k(k+1)  \binom{m}{k-i}
$$

此时需要注意，后方枚举的 $k$ 的部分有值当且仅当 $k \in [i,m+i]$，所以我们写出它的上界，并且用 $k-i$ 来代替原来的 $k$。

$$
Ans= \frac{1}{n} \sum_{i=1} \binom{n}{i} \binom{m+i-1}{i-1}  \sum_{k=0}^{m} (k+i)(k+i+1)  \binom{m}{k}
$$

现在把后方的括号乘开，我们会发现后方的式子变成如下形式：

$$
\left ( \sum_{k=0}^m k^2 \binom{m}{k} \right ) + (2i+1)\left ( \sum_{k=0}^m k \binom{m}{k} \right ) + (i^2+i) \left ( \sum_{k=0}^m \binom{m}{k} \right )
$$

其中和式部分与 $i$ 无关，听说可以 $O(1)$ 求，但是蒟蒻不会，于是我们可以预处理，设 $F=\sum_{k=0}^m k^2\binom{m}{k},G=\sum_{k=0}^m k \binom{m}{k},H=\sum_{k=0}^m \binom{m}{k}$。

原式：

$$
Ans= \frac{1}{n} \sum_{i=1} \binom{n}{i} \binom{m+i-1}{i-1}  (F + (2i+1)G + (i^2+i)H )
$$

照着做就行了，复杂度 $O(\sum n+m)$，有点卡常。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 20000010
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define mod 1000000007
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int T,n,m,K,fac[N],fav[N],ans,F,G,H;
inline int qpow(int a,int b)
{
	int res=1;
	for(;b;b>>=1,a=(1ll*a*a)%mod) if(b&1) res=(1ll*res*a)%mod;
	return res;
}
inline int inv(int a){return qpow(a,mod-2);}
inline int C(int n,int m){if(m>n||m<0) return 0;return 1ll*fac[n]*fav[m]%mod*fav[n-m]%mod;}
signed main()
{
	read(T);
	fac[0]=1;
	rep(i,1,N-10) fac[i]=1ll*fac[i-1]*i%mod;
	fav[N-10]=qpow(fac[N-10],mod-2);
	per(i,N-11,0) fav[i]=1ll*fav[i+1]*(i+1)%mod;
	while(T--)
	{
		read(n,m);ans=F=G=H=0;
		rep(i,0,m)
		{
			int x=C(m,i);
			F=1ll*(F+1ll*i*i%mod*x%mod)%mod;
			G=1ll*(G+1ll*i*x%mod)%mod;
			H=1ll*(H+1ll*x%mod)%mod;
		}
		rep(i,1,n)
		{
			int res=0;
			res=1ll*(1ll*F+1ll*(2ll*i+1)%mod*G%mod+1ll*(1ll*i*i+i)%mod*H%mod)%mod;
			res=1ll*C(n,i)*C(m+i-1,i-1)%mod*res%mod;
			ans=1ll*(1ll*ans+1ll*res)%mod;
		}
		printf("%d\n",1ll*ans*qpow(n,mod-2)%mod);
	}
	return 0;
}

```

---

## 作者：Sampson_YW (赞：9)

大无语，div2 不会 C 和 D，真就 adhocforces 了？？？

感觉 E 小于 C 和 D 啊？？？但是由于被 CD 卡了一年所以没写完 E。。。

两题遗憾离场！

言归正传，来讲下这题怎么做。

首先，由于要求出所有合法的 $(a,b)$ 的长度之和，  
所以可以枚举长度，算出合法的 $(a,b)$ 数量。

因为 $a$ 序列和 $b$ 序列的开头和结尾的数是固定的，  
我们不妨枚举在中间插入了 $i$ 个数，即序列长度为 $i+2$。

然后，由于 $a$ 序列和 $b$ 序列是单调不降的，  
所以 $a_l+b_l\not=a_{l-1}+b_{l-1}$ 这个条件就是不能同时满足 $a_l=a_{l-1}$ 和 $b_l=b_{l-1}$。

考虑得到 $a$ 和 $b$ 的差分数组 $A$ 和 $B$，则差分数组长度为 $i+1$，  
那么一组满足以下条件的 $(A,B)$ 就能得到一组合法的 $(a,b)$：

$$
\begin{cases}
\sum_{l=1}^{i+1}A_l=n\\
\sum_{l=1}^{i+1}B_l=m\\
\forall l\in [1,i+1],A_l\not=0\  \text{or}\ B_{l}\not=0
\end{cases}
$$

第一个条件和第二个条件容易插板法解决，  
第三个条件不太好直接统计，考虑容斥。

我们钦定有 $j$ 个位置满足 $A_l=B_l=0$，有 $\binom{i+1}{j}$ 种选择，  
其它位置随便分的方案数通过插板法可以得到是 $\binom{n+i-j}{i-j}\binom{m+i-j}{i-j}$。

那么插入了 $i$ 个数的合法 $(a,b)$ 数量为：$\sum_{j=0}^i(-1)^j\binom{n+i-j}{i-j}\binom{m+i-j}{i-j}$。

因为 $A_l$ 和 $B_l$ 至少要有一个不为 $0$，所以最多填 $n+m$ 个数，最后答案为：

$$
\sum_{i=0}^{n+m}(i+2)\sum_{j=0}^i(-1)^j\binom{i+1}{j}\binom{n+i-j}{i-j}\binom{m+i-j}{i-j}
$$

直接算是 $O(n^2)$ 的。

这题的时间限制与数据范围限制了我们只能用线性做法解决，考虑优化。

不妨设 $T=n+m$。

发现式子中 $i-j$ 出现得比较多，  
考虑枚举 $t=i-j$，再枚举 $i$，那么 $j$ 就等于 $i-t$。

原式通过转化得到：

$$
\sum_{t=0}^T\binom{n+t}{t}\binom{m+t}{t}\sum_{i=t}^T(-1)^{i-t}(i+2)\binom{i+1}{i-t}
$$

于是我们只需要求出 $\sum_{i=t}^T(-1)^{i-t}(i+2)\binom{i+1}{i-t}$ 的值。

先把 $(-1)^{-t}$ 提出去，然后通过组合恒等式把 $(i+2)\binom{i+1}{i-t}$ 变成 $(t+2)\binom{i+2}{t+2}$。

然后我们只需要求出 $\sum_{i=t}^T(-1)^i\binom{i+2}{t+2}$。

由于这个东西看起来没有组合恒等式，并且要对于 $t=0\sim T$ 都求出来，我们不难想到递推。

感觉这个 $(-1)^i$ 比较难搞，我们可以对于 $i$ 为偶数和 $i$ 为奇数单独计算然后相减。

设 $f(t)=\sum_{i=t}^T[i\bmod2=0]\binom{i+2}{t+2}$，$g(t)=\sum_{i=t}^T[i\bmod2=1]\binom{i+2}{t+2}$。

由于每个 $t$ 都求的是一段后缀，不难想到从后往前递推。

我们考虑如何从 $f(t+1)$ 和 $g(t+1)$ 转移到 $f(t)$ 和 $g(t)$。

我们发现，$f(t)$ 和 $g(t)$ 的每个组合数在杨辉三角上是在第 $t+2$ 列上交错的。

考虑杨辉三角上 $\binom{i+2}{t+2}+\binom{i+2}{t+3}=\binom{i+3}{t+3}$。

也就是说 $g(t)+g(t+1)=f(t+1)$，$f(t)+f(t+1)=g(t+1)$。

但是直接递推会发现少算了一项，即 $\binom{T+2}{t+2}$，加上就完事了。

递推出 $f$ 和 $g$ 后答案就是

$$
\sum_{t=0}^T\binom{n+t}{t}\binom{m+t}{t}(-1)^t(t+2)(f(t)-g(t))
$$

---

## 作者：Neutralized (赞：7)

首先这个约束看起来就需要移项，所以考虑差分数组 $A_i$ 和 $B_i$。  
则需要满足：$A_0=0,A_i \ge 0,\sum A_i=n$，$B_0=0,B_i \ge 0,\sum B_i=m$。  
然后直接枚举（不算第 $0$ 项的）长度 $K$，枚举 $A$ 中 $\gt 0$ 的有 $l$ 个，$B$ 中 $r$ 个。保证不存在 $i$ 使得 $A_i=0,B_i=0$，也就是 $B$ 中剩下的 $K-r$ 个 $0$ 需要放在对应位置的 $A$ 有值的地方。  
于是可以得到一个很简单的式子：  

$$
ans = \sum_{K=1}^{+\infty}(K+1)\sum_{l=1}^{K}\dbinom{n-1}{l-1}\dbinom{K}{l}\sum_{r=1}^{K}\dbinom{m-1}{r-1}\dbinom{l}{K-r}
$$

可以发现枚举 $r$ 的求和就是范德蒙德卷积，所以我们已经做到 $O(n^2)$ 了。  

剩下两个求和符号的式子长这样：  
$$
\sum_{K=1}^{+\infty}(K+1) \sum_{l=1}^{K}\dbinom{n-1}{l-1}\dbinom{K}{l}\dbinom{m+l-1}{K-1}
$$
很推不动。  

考虑交换一下求和符号：  
$$
\sum_{l=1}^{+\infty} \dbinom{n-1}{l-1} (l+1) \sum_{K=1}^{+\infty} \dbinom{K+1}{l+1}\dbinom{m+l-1}{K-1}
$$

然后人类的智慧启示我们，可以把后面那个组合数乘积拆开之后硬凑，使得求和里只剩下一个组合数：  

$$
= \sum_{l=1}^{+\infty} \dfrac{1}{m} \dbinom{n-1}{l-1} \dbinom{m+l-1}{l} \sum_{K=1}^{+\infty} K(K+1)\dbinom{m}{K-l}
$$

后面是一个带系数组合数求和，但是 $K-l$ 有点难看，所以设 $D = K-l$，转为枚举 $D$：  
$$
ans = \sum_{l=1}^{+\infty} \dfrac{1}{m} \dbinom{n-1}{l-1} \dbinom{m+l-1}{l} \sum_{D=0}^{m} \dbinom{m}{D}[D^2+(2l+1)D+(l^2+l)]
$$

现在只需要 $O(1)$ 求出 $\sum_{i=0}^{m} i^2 \dbinom{m}{i}=m(m+1)2^{m-2}$， $\sum_{i=0}^{m} i \dbinom{m}{i}=m2^{m-1}$ 和 $\sum_{i=0}^{m} \dbinom{m}{i}=2^m$。这三个都是经典组合恒等式。  

如果需要证明，以第二个为例，取 $x=1$：  
$$
F(n) = \sum_{i=0}^{m}i\dbinom{m}{i}x^{i-1}1^{m-i} =\dfrac{d(x+1)^m}{dx}=m(x+1)^{m-1}=m2^{m-1}
$$

预处理 $2$ 的次幂即可做到 $O(n)$ 回答单个询问。  

~~代码很好看~~。  

```cpp
#include <cstdio>
template<class T> inline void rd(T &x,char i=getchar(),bool f=0){ x=0; while(i<48||i>57) f|=i=='-',i=getchar(); while(i>=48&&i<=57) x=(x<<3)+(x<<1)+(i^48),i=getchar(); f&&(x=-x); }
typedef long long ll;
const int N = 5000003, p = 1e9+7;
int n,m,pw[N],fac[N<<1],invf[N<<1];
main(){
	auto C = [](int n,int m){ return m>n?0:1ll*fac[n]*invf[m]%p*invf[n-m]%p; };
	auto Pow = [](ll bs,int b,ll rs=1){ while(b) (b&1)&&(rs=rs*bs%p),bs=bs*bs%p,b>>=1; return rs; };
	auto S0 = [](int n){ return pw[n]; };
	auto S1 = [](int n){ return n<1?0ll:1ll*n*pw[n-1]%p; };
	auto S2 = [](int n){ return n<2?1ll:1ll*(n+1)*n%p*pw[n-2]%p; };
	
	pw[0]=fac[0]=fac[1]=invf[0]=invf[1]=1,pw[1]=2;
	for(int i=2;i<=5e6;++i) pw[i]=(pw[i-1]<<1)%p;
	for(int i=2;i<=1e7;++i) fac[i]=1ll*fac[i-1]*i%p;
	invf[10000000]=Pow(fac[10000000],p-2);
	for(int i=9999999;i>=2;--i) invf[i]=1ll*invf[i+1]*(i+1)%p;
	int T; rd(T); while(T--){
		rd(n),rd(m); int res=0;
		const int invm = Pow(m,p-2);
		for(int l=1;l<=n;++l){
			int t1 = C(n-1,l-1)*C(m+l-1,l)%p*invm%p;
			int t2 = (S2(m)+1ll*S1(m)*(l<<1|1)%p+1ll*S0(m)*l%p*(l+1)%p)%p;
			(res+=1ll*t1*t2%p)>=p&&(res-=p);
		} printf("%d\n",res);
	}
}
```

---

## 作者：OtoriEmu (赞：2)

将问题抽象成从网格图，每次向右或向上，从 $(0,0) \to (n,m)$ 的路径上选出一些点构成点集，问所有本质不同的点集大小和。

假设我们枚举了点集，但是可以形成这个点集的路径太多，我们得通过一种方法让它在所有的路径中只有一种合法供我们计算。在这里我们强制两个点间采用先向上再向右的方式，这样两个点间的方案唯一，进而一个点集只对应一条路径。

那么会形成很多个拐点，我们枚举先右后上的拐点个数（拐点可以是先上后右，也可以是先右后上，这个不重要），记其为 $i$。那么拐点个数为 $i$ 的方案数为 $\dbinom{n}{i}\dbinom{m}{i}$。

注意到我们忽视了路径上的除了拐点和起点终点的所有点，这些点加入仍然对应同一条路径，因此我们需要计算。那么现在有 $s=n+m-i-1$ 个点可以任取，总方案为 $\displaystyle \sum_{i=0}^s \dbinom{s}{i} = 2^s$ 个，拐点上的贡献为 $\displaystyle \sum_{i=0}^s \dbinom{s}{i}i$。这个贡献的处理方式是，你发现 $\displaystyle \sum_{i=0}^s \dbinom{s}{i}i = \displaystyle \sum_{i=0}^s \dbinom{s}{s-i}i$，两者相加就是 $\displaystyle s\sum_{i=0}^s \dbinom{s}{i} = s2^s$，那么答案就是 $s2^{s-1}$。

注意终点和起点以及枚举的拐点个数（即 $i+2$）需要被计算 $2^s$ 次。

[赛时评测记录](https://codeforces.com/contest/1747/submission/179253920)。

---

## 作者：Leasier (赞：2)

Update on 2022.11.9：感谢 @[ClHg2](https://www.luogu.com.cn/user/253946)。

前置芝士：[二项式反演](https://www.cnblogs.com/GXZlegend/p/11407185.html)

考虑不合法序列的那个条件 $a_i + b_i = a_{i - 1} + b_{i - 1}$，即 $a_i = a_{i - 1}, b_i = b_{i - 1}$。

于是我们可以得到合法序列长度 $\leq n + m + 1$——因为每次 $a, b$ 中至少减少一个。

然后发现每存在一个位置不合法，我们就可以把不合法的位置删掉——反正重复了，删了也不影响剩下的部分。当我们把所有不合法位置删完后，你会发现它变成了一个合法序列。

设 $f(x)$ 表示长度**恰好**为 $x$ 的**合法**序列的方案数，$g(x)$ 表示长度**恰好**为 $x$ 的**不一定合法**序列的方案数。

运用二项式反演，由 $g(x) = \displaystyle\sum_{i = 2}^x C_{x - 1}^{i - 1} f(i)$ 可知 $f(x) = \displaystyle\sum_{i = 2}^x (-1)^{x - i} C_{x - 1}^{i - 1} g(i)$。答案即为 $\displaystyle\sum_{i = 2}^{n + m + 1} i f(i)$。

现在考虑 $g(x)$ 怎么算。注意到其实我们可以任取一个长度为 $x$ 的满足不降限制的 $a, b$ 序列，于是 $g(x) = C_{n + x - 2}^n C_{m + x - 2}^m$。代入可知：

原式 $= \displaystyle\sum_{i = 2}^{n + m + 1} i \sum_{j = 2}^i (-1)^{i - j} C_{i - 1}^{j - 1} C_{n + j - 2}^n C_{m + j - 2}^m$

$ = \displaystyle\sum_{j = 2}^{n + m + 1} (-1)^j C_{n + j - 2}^n C_{m + j - 2}^m \sum_{i = j}^{n + m + 1} (-1)^i i C_{i - 1}^{j - 1}$

$ = \displaystyle\sum_{j = 2}^{n + m + 1} (-1)^j j C_{n + j - 2}^n C_{m + j - 2}^m \sum_{i = j}^{n + m + 1} (-1)^i C_i^j$

现在唯一的问题是后半部分。我们考虑按照 $n + m + 1 \to 2$ 的顺序计算每个 $j$ 的贡献。

我们显然要根据 $(-1)^i$ 的奇偶性分开讨论。这里设 $even, odd$ 分别表示当前偶数 / 奇数的 $i$ 的贡献（这里不考虑符号）。

从 $j + 1$ 到 $j$ 时，我们对于 $C_i^{j + 1} \to C_i^j$ 的过程，注意到组合数递推式 $C_{i + 1}^{j + 1} = C_i^j + C_i^{j + 1}$，于是我们：

- $x \leftarrow odd - even$，即扔掉符号时全部偶数 $i$ 的 $C_i^j$ 的和。
- $even \leftarrow x, odd \leftarrow -x$。

但是对于 $C_{n + m + 1}^j$，上面我们会少加上一个 $C_{n + m + 2}^{j + 1}$……这个特判一下加给 $even$ 还是 $odd$ 即可。

时间复杂度为 $O(N + \sum(n + m))$。

代码（~~要贺的话记得用 C++20 提交~~）：
```cpp
#include <stdio.h>

const int N = 1.5e7, mod = 1e9 + 7;
int fac[N + 7], inv_fac[N + 7];

inline int quick_pow(int x, int p){
	int ans = 1;
	while (p){
		if (p & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init(){
	fac[0] = 1;
	for (register int i = 1; i <= N; i++){
		fac[i] = 1ll * fac[i - 1] * i % mod;
	}
	inv_fac[N] = quick_pow(fac[N], mod - 2);
	for (register int i = N - 1; i >= 0; i--){
		inv_fac[i] = 1ll * inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline int sub1(int x, int y){
	return x - y < 0 ? x - y + mod : x - y;
}

inline int comb(int n, int m){
	if (n < 0 || m < 0 || n < m) return 0;
	return 1ll * fac[n] * inv_fac[m] % mod * inv_fac[n - m] % mod;
}

inline void add(int &x, int y){
	if ((x += y) >= mod) x -= mod;
}

inline void sub2(int &x, int y){
	if ((x -= y) < 0) x += mod;
}

int main(){
	int t;
	scanf("%d", &t);
	init();
	for (register int i = 1; i <= t; i++){
		int n, m, even = 0, odd = 0, t, ans = 0;
		scanf("%d %d", &n, &m);
		t = n + m + 1;
		for (register int j = t; j >= 2; j--){
			int x = sub1(odd, even), y = mod - x;
			if (t % 2 == 0){
				add(x, comb(t + 1, j + 1));
			} else {
				add(y, comb(t + 1, j + 1));
			}
			even = x;
			odd = y;
			if (j % 2 == 0){
				add(ans, 1ll * j * sub1(even, odd) % mod * comb(n + j - 2, n) % mod * comb(m + j - 2, m) % mod);
			} else {
				sub2(ans, 1ll * j * sub1(even, odd) % mod * comb(n + j - 2, n) % mod * comb(m + j - 2, m) % mod);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：MoyunAllgorithm (赞：1)

这是一道看起来很困难 *2900 题，但本萌新居然做的很顺利，而且好像我的方法相对比较简单，因此写一篇题解~

**题意**

求所有满足以下要求的有序数组对 $(a,b)$ 的 $a$ 长度和：

- $a,b$ 长度相等且 $\ge 2$；

- $a,b$ 单调不降，$a_1=b_1=0$，两者的末尾元素分别为 $n,m(\le 5 \times 10^6)$；

- 不存在 $i$ 使得 $a_i+b_i=a_{i+1}+b_{i+1}$。

**分析**

首先第三个条件看起来很怪异难以分析，但结合单调性考虑，可以发现第三个条件相当于不存在下标 $i$ 使得 $a_i=a_{i+1}$ 且 $b_i=b_{i+1}$。这样看起来好多了。

对于有两个整数数组且数组间存在约束的问题，能较为自然地将其映射到**网格图**上思考。如果将 $(a_i,b_i)$ 视作网格图上的点，则其必然处于一个 $(0,0 ) \rightarrow (n,m)$ 的只右只上路径上。而且条件三还刚好保证了这些点是不重合的！这侧面印证了这一转化正是出题人所想要的。

一件烦人的事情是 $(a,b)$ 点集和路径都是一对多的关系。例如：若点击为 $\{(0,0),(1,1),(1,2)\}$。则有两个只右只上路径满足要求：$(0,0) \rightarrow (0,1) \rightarrow (1,1) \rightarrow (1,2)$ 和 $(0,0) \rightarrow (1,0) \rightarrow (1,1) \rightarrow (1,2)$。 另一边，路径 $(0,0) \rightarrow (0,1) \rightarrow (1,1) \rightarrow (1,2)$ 也对应很多可能的点集：$\{(0,0),(1,1),(1,2)\},\{(0,0),(1,2)\}$ 等。

因此，**强行规定一个点集只对应一个路径**：对于 $(a_i,b_i)$ 和 $(a_{i+1},b_{i+1})$，路径必须先向右走到 $x=a_{i+1}$ 后向上走到 $y=b_{i+1}$。这样一个点集只对应一个路径。

这仍然不能改变一个路径对应多个点集的事实。但考虑一个路径对应**哪些**点集则是容易的。稍加分析则可发现：

- 一条路径的起点、终点和先上再右的拐点必须位于点集内，其他点则随意。

这是因为，路径连接两个点的方式是先右再上。因此如果出现先上再右的拐点，说明这一定不是在连接两个点，说明这就是一个点所在的位置。

那么如何计算长度呢？**最便捷的方法是计算每个点的贡献**。如果这个点必须在点集内，则会对总长度有**点集方案数**的贡献，因为每个点集都必须包含；否则对总长度有**点集方案数的一半**的贡献，因为有一半的方案它在其中。相加即可。

由于路径长度为 $n+m+1$，设有 $i$ 个先上再右拐点，则其点集总长度为

$(i+2) \times 2^{n+m-1-i}$+$(n+m-1-i) \times 2^{n+m-2-i}$。

因此本题马上就要完成了！对于输入的 $(n,m)$，枚举先右再上拐点数量 $i \in [0,\text{min}(n,m)]$，则拐点有 $C_{i}^{n} C_{i}^{m}$  种方案，对于每种方案的长度和就是上面那个式子。

时间复杂度为 $O(n)$。


```cpp
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=5e6+5,MOD=1e9+7;
int T,N,M;
LL fac[MAXN],ifac[MAXN],po[MAXN*2];
LL QPow(LL base,int po)
{
	LL res=1;
	while(po)
	{
		if(po&1) res=res*base%MOD;
		base=base*base%MOD;
		po>>=1;
	}
	return res;
}
LL C(int n,int m)
{
	return fac[n]*ifac[m]%MOD*ifac[n-m]%MOD;
}
int main()
{
	fac[0]=1;
	for(int i=1;i<=MAXN-5;i++) fac[i]=fac[i-1]*i%MOD;
	ifac[MAXN-5]=QPow(fac[MAXN-5],MOD-2);
	for(int i=MAXN-6;i>=0;i--) ifac[i]=ifac[i+1]*(i+1)%MOD;
	po[0]=1;
	for(int i=1;i<=2*MAXN-5;i++) po[i]=po[i-1]*2%MOD;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&N,&M);
		LL ans=(2ll*po[N+M-1])%MOD;
		ans=(ans+1ll*(N+M-1)*po[N+M-2]%MOD)%MOD;
    //这里是对于有0个拐点情况的单独计算，但其实也是适用下面的算式的
		for(int i=1;i<=min(N,M);i++)
		{
			LL t=C(N,i)*C(M,i)%MOD;
			LL v1=1ll*(i+2)*po[N+M-1-i]%MOD;
			LL v2=1ll*(N+M-1-i)*po[N+M-2-i]%MOD;
			ans=(ans+t*((v1+v2)%MOD)%MOD)%MOD;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：monstersqwq (赞：1)

CF1747E

考虑长度为 $k$ 的差分序列 $c,d$（原序列长度 $k+1$），限制即为 $c_i,d_i$ 不能同时为 $0$，$\sum c_i=n,\sum d_i=m$。

枚举 $c$ 中的 $0$ 个数 $i$，$c,d$ 序列的方案数均为插板（下式 $i$ 为非零个数减一）：

$$\sum_{k=1}^{n+m}(k+1)\sum_{i=0}^{k-1}\binom{n-1}{i}\binom{m+i}{k-1}\binom{k}{i+1}$$

$$\sum_{i=0}^{n+m-1}\binom{n-1}{i}\sum_{k=i+1}^{n+m}(k+1)\binom{m+i}{k-1}\binom{k}{i+1}$$

组合数全部拆开

$$\sum_{i=0}^{n-1}\binom{n-1}{i}\sum_{k=i+1}^{i+m+1}\dfrac{k(k+1)(m+i)!}{(i+1)!(k-i-1)!(m+i-k+1)!}$$

$$\sum_{i=0}^{n-1}\binom{n-1}{i}\dfrac{(m+i)!}{(i+1)!}\sum_{k=i+1}^{i+m+1}\dfrac{k(k+1)}{(k-i-1)!(m+i-k+1)!}$$

第二个分式的分母拼回去组合数

$$\sum_{i=0}^{n-1}\binom{n-1}{i}\dfrac{(m+i)!}{(i+1)!}\sum_{k=i+1}^{i+m+1}k(k+1)\binom{m}{k-i-1}$$

$$\sum_{i=0}^{n-1}\binom{n-1}{i}\dfrac{(m+i)!}{(i+1)!}\sum_{k=0}^{m}(k+i+1)(k+i+2)\binom{m}{k}$$

$$\sum_{i=0}^{n-1}\binom{n-1}{i}\dfrac{(m+i)!}{(i+1)!}((i+1)(i+2)2^m+(2i+4)m2^{m-1}+m(m-1)2^{m-2})$$

可以线性解决。

---

## 作者：Terry2022 (赞：1)


一个不一样的式子推导方法。

**题意**：


给定 $n$ 和 $m$，请问能构造满足以下条件的数组对 $(a,b)$ 中，$a$ 长度之和是多少：

1. 数组长度相等且长度大于 $2$，设数组长度都为 $k$。
2. $a_1=b_1=0$，$a_k=n$，$b_k=m$。
3. 每个数组都单调不下降且对于所有 $1<i\le k$ 都满足 $a_i+b_i\ne a_{i-1}+b_{i-1}$。

答案对 $10^9+7$ 取模。

**思路**：

首先，由于 $a_i\ge a_{i-1}$，$b_{i}\ge b_{i-1}$，$a_{i}+b_{i}\neq a_{i-1}+b_{i-1}$，所以有 $a_{i}+b_{i}> a_{i-1}+b_{i-1}$。

由于 $a_{k}+b_{k}=n+m$，所以 $k\le n+m$。

不妨设 $a,b$ 的差分数组分别为 $A,B$，则 $\forall i\in[1,k-1]\cap \Z$，都满足 $A_{i}+B_{i}>0$。

所以有一个 $O(n^3)$ 的暴力式子：$\sum_{i=2}^{n+m+1}\sum\limits_{j\ge 1}\sum\limits_{k\ge 1}i\binom{i-1}{j}\binom{n-1}{j-1}\binom{j}{k}\binom{m-1}{i-1-j+k-1}$，表示枚举长度为 $i$，$A_{i}\neq 0$ 的位置有 $j$ 个，$B_{i}\neq 0$ 且 $A_{i}\neq 0$ 的位置有 $k$ 个方案数，$\binom{n-1}{j-1},\binom{m-1}{i-1-j+k-1}$ 分别表示对于 $A,B$ 差分数组权值的分配的方案数，隔板法。

直接推式子：

$$
\begin{aligned}

&\sum_{i=2}^{n+m+1}\sum\limits_{j\ge 1}\sum\limits_{k\ge 1}i\binom{i-1}{j}\binom{n-1}{j-1}\binom{j}{k}\binom{m-1}{i-1-j+k-1}
\\
&=\sum_{i=2}^{n+m+1}\sum\limits_{j\ge 1}i\binom{i-1}{j}\binom{n-1}{j-1}\sum\limits_{k\ge 1}\binom{j}{k}\binom{m-1}{i-1-j+k-1}
\\

\end{aligned}
$$


对于 $k$ 做范德蒙德卷积：
$$
\begin{aligned}

&=\sum_{i=2}^{n+m+1}\sum\limits_{j\ge 1}i\binom{i-1}{j}\binom{n-1}{j-1}\binom{m-1+j}{i-2}

\end{aligned}
$$

交换求和符号：

$$
\begin{aligned}

&=\sum_{j=1}^{n+m+1}\sum\limits_{i\ge 1}i\binom{i-1}{j}\binom{n-1}{j-1}\binom{m-1+j}{i-2}&
\\
&=\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\sum\limits_{i\ge 2}i\binom{i-1}{j}\binom{m-1+j}{i-2}&
\\
&=\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\sum\limits_{i\ge 0}(i+2)\binom{i+1}{j}\binom{m-1+j}{i}
\\
&=\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\sum\limits_{i\ge 0}(i+2)\left(\binom{i}{j}+\binom{i}{j-1}\right)\binom{m-1+j}{i}
\\
&=\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\sum\limits_{i\ge 0}(i+2)\left(\binom{m-1+j}{j}\binom{m-1}{i-j}+\binom{m-1+j}{j-1}\binom{m}{i-j+1}\right)
\\
&=\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\sum\limits_{i\ge 0}(i+j+2)\left(\binom{m-1+j}{j}\binom{m-1}{i}+\binom{m-1+j}{j-1}\binom{m}{i-1}\right)
\\
&=\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\binom{m-1+j}{j}(j+2)\sum\limits_{i\ge 0}\binom{m-1}{i}
\\
&+\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\binom{m-1+j}{j}\sum\limits_{i\ge 0}i\binom{m-1}{i}
\\
&+\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\binom{m-1+j}{j-1}(j+1)\sum\limits_{i\ge 0}\binom{m}{i}
\\
&+\sum_{j=1}^{n+m+1}\binom{n-1}{j-1}\binom{m-1+j}{j-1}\sum\limits_{i\ge 0}i\binom{m}{i}

\end{aligned}
$$

$\sum\limits_{i\ge 0}i\binom{m-1}{i},\sum\limits_{i\ge 0}\binom{m-1}{i},\sum\limits_{i\ge 0}i\binom{m}{i},\sum\limits_{i\ge 0}\binom{m}{i}$ 都可以 $O(m)$ 预处理，所以总的时间复杂度为 $O(n+m)$。


**代码**：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cassert>
const int Q=20000005;
const int INF=(1<<30);
const int mod=1e9+7;
typedef long long ll;
#define rg register int
#define cint const register int
//char ibuf[1<<21],*IP1=ibuf,*IP2=ibuf;
//#define gc() (__builtin_expect(IP1==IP2,0)&&(IP2=(IP1=ibuf)+fread(ibuf,1,1<<21,stdin),__builtin_expect(IP1==IP2,0))?EOF:*IP1++)
#define gc getchar
#define pc putchar
inline bool ig(const char c){return c>=48&&c<=57;}
inline void read(rg&oi){char c;rg f=1,res=0;while(c=gc(),(!ig(c))&&c^'-');c^'-'?res=(c^48):f=-1;while(c=gc(),ig(c))res=res*10+(c^48);oi=f*res;}
inline void print(rg oi){char io[23];rg l=0;if(oi<0)pc('-'),oi=~oi+1;do io[++l]=(oi%10+48);while(oi/=10);for(;l;--l)pc(io[l]);}
inline void write(cint oi,const char c){print(oi);pc(c);}char _ST_;
int prd[Q],ivp[Q];
inline int inc(cint x,cint y){return x+y<mod?x+y:x+y-mod;}
inline int dec(cint x,cint y){return x>=y?x-y:x-y+mod;}
inline int mul(cint x,cint y){return 1ll*x*y%mod;}
inline void Inc(rg&x,cint y){((x+=y)>=mod)&&(x-=mod);}
inline void Dec(rg&x,cint y){((x-=y)<0)&&(x+=mod);}
inline void Mul(rg&x,cint y){x=1ll*x*y%mod;}
inline int pow(rg x,rg y){rg res=1;for(;y;y>>=1,Mul(x,x))(y&1)&&(Mul(res,x),1);return res;}
inline int Inv(cint x){return pow(x,mod-2);}
inline int binom(cint N,cint M){return N<0||M<0||N<M?0:mul(prd[N],mul(ivp[M],ivp[N-M]));}
int T,n,m;
char _ED_;int main(){
	fprintf(stderr,"static memory:%.6lf MB\n",(&_ST_-&_ED_)/1024./1024.);
	cint Mx=Q-5;prd[0]=ivp[0]=1;
	for(rg i=1;i<=Mx;++i)Mul(prd[i]=prd[i-1],i);ivp[Mx]=Inv(prd[Mx]);
	for(rg i=Mx-1;i>=1;--i)Mul(ivp[i]=ivp[i+1],i+1);
	read(T);for(;T--;){
		read(n);read(m);cint N=n+m;rg res=0,ss1=0,ss2=0,s1=0,s2=0;
		for(rg i=0,o;i<=N+1;++i)Inc(s1,mul(i,o=binom(m-1,i))),Inc(ss1,o);
		for(rg i=0,o;i<=N+1;++i)Inc(s2,mul(i,o=binom(m,i))),Inc(ss2,o);
		for(rg j=1;j<=N+1;++j){
			Inc(res,mul(binom(n-1,j-1),mul(binom(m-1+j,j),inc(s1,mul(ss1,j+2)))));
			Inc(res,mul(binom(n-1,j-1),mul(binom(m-1+j,j-1),inc(s2,mul(ss2,j+1)))));
		}
		write(res,'\n');
	}
	return 0;
}

```

---

## 作者：foreverlasting (赞：1)

题意：一对序列 $(a,b)$ 被称为好序列当且仅当它们长度相同，设为 $k$，满足 $a_1=b_1=0,a_k=n,b_k=m$，且对任意 $1<i\leq k$，满足 $a_i\geq a_{i-1},b_i\geq b_{i-1}$，且 $a_i+b_i\neq a_{i-1}+b_{i-1}$，求所有可能的 $(a,b)$ 的 $k$ 之和。

题解：递增序列直接是不容易求的，考虑差分，而限制三要求不能为相反数，由于差分 $\geq 0$，所以就是不能同时为零。于是题意改写成，求 $(a,b)$，满足 $a_i,b_i\geq 0$，且 $\sum_{i=1}^{k-1} a_i=n,\sum_{i=1}^{k-1} b_i=m$，且不存在 $i$ 满足 $a_i=b_i=0$，求所有 $k$ 的和。

考虑一对 $(a_i,b_i)$ 的方案数，这个 GF 是容易的，即 $A=\frac{1}{(1-x)(1-y)}-1$，那么总的 GF 就是 $\frac{1}{1-A}$，如果求方案数就是求 $[x^ny^m] \frac{1}{1-A}$，可惜要引入 $k$ 之和，所以再整一维 $t$，即答案为
$$
\sum_{k\geq 1} k\times [x^ny^m] A^{k-1}
$$
这是等差等比序列，可以迅速求得答案为
$$
[x^ny^m]\frac{1}{(1-A)^2}$$
$$
=[x^ny^m] \frac{(1-x)^2(1-y)^2}{(1-(2x+2y-2xy))^2}
$$
分子的东西不用管，因为等价于我们求
$$
([x^ny^m]+[x^{n-2}y^{m-2}]-2[x^{n-2}y^{m-1}]-2[x^{n-1}y^{m-2}]+$$
$$
[x^{n-2}y^m]+[x^ny^{m-2}]+4[x^{n-1}y^{m-1}]-2[x^{n-1}y^m]-2[x^ny^{m-1}])$$
$$
\frac{1}{(1-(2x+2y-2xy))^2}
$$
分母是二次幂并不容易，但可以对某一维积分，即求
$$
(n+1)[x^{n+1}y^m] \frac{1}{2(1-y)}\frac{1}{1-(2x+2y-2xy)}
$$
先展开最右边的，有
$$
\frac{1}{2(1-y)} (1+2(1-x)(1-y)+2^2(1-x)^2(1-y)^2+\cdots)$$
$$
=\frac{1}{2(1-y)}+(1-x)+2(1-x)^2(1-y)+\cdots$$
$$
=\frac{1}{2(1-y)}+(1-x)(\frac{1}{1-(2x+2y-2xy)})
$$
求这东西，等价于
$$
(n+1)([x^{n+1}y^m] \frac{1}{2(1-y)}+([x^{n+1}y^m]-[x^ny^m])\frac{1}{1-(2x+2y-2xy)})
$$
于是就是要求
$$
[x^ny^m] \frac{1}{1-(2x+2y-2xy)}
$$
这东西也是好求的，考虑枚举 $xy$ 的幂次，假设为 $k$，此刻 $x$ 的幂次为 $n-k$，$y$ 的幂次为 $m-k$，所以总的为 $n+m-k$，此时的系数为 $2^{n+m-k} (-1)^k \binom{n+m-k}{k,n-k,m-k}$。于是就求出答案了，时间复杂度 $O(n+m)$。

```cpp
//2022.11.5 by ljz
//email 573902690@qq.com
//if you find any bug in my code
//please tell me
const int N=1e7+20;
Z fac[N],inv[N],pw[N],finv[N];
namespace MAIN {
	int n,m;
	inline void MAIN(const int &Case) {
		auto solve=[&](const int &n,const int &m){
			Z ans=0;
			for(int k=0;k<=min(n,m);k++){
				if(k&1)ans-=pw[n+m-k]*fac[n+m-k]*finv[k]*finv[n-k]*finv[m-k];
				else ans+=pw[n+m-k]*fac[n+m-k]*finv[k]*finv[n-k]*finv[m-k];
			}
			return ans;
		};
		auto f=[&](const int &n,const int &m){
			Z ans=solve(n+1,m)-solve(n,m);
			return (n+1)*ans;
		};
		n=read(),m=read();
		Z ans=f(n,m)-2*f(n-1,m)-2*f(n,m-1)+4*f(n-1,m-1);
		if(n>=2)ans+=f(n-2,m)-2*f(n-2,m-1);
		if(m>=2)ans+=f(n,m-2)-2*f(n-1,m-2);
		if(n>=2&&m>=2)ans+=f(n-2,m-2);
		printf("%d\n",ans);
	}
}
```

实际上也可以合并同类项，这样常数会小很多，不过不是重点。

---

## 作者：Purslane (赞：0)

## Solution

如果不考虑 $(a_{i-1},b_{i-1}) \neq (a_i,b_i)$ 的限制，长度为 $k$ 的二元组 $(a,b)$ 显然有 $g_k=\binom{n+k-2}{n}\binom{m+k-2}{m}$ 个。

设 $f_k$ 表示最终的答案，则

$$
g_k = \sum_{k'=2}^k \binom{k-1}{k'-1} f_{k'}
$$

施二项式反演，得到：

$$
f_k = \sum_{k'=2}^k (-1)^{k-k'}\binom{k-1}{k'-1} g_{k'}
$$

所以

$$
\begin{aligned}
& \sum_{k=2}^{n+m+1} k f_k \\
=& \sum_{k=2}^{n+m+1} k \sum_{i=2}^k (-1)^{k-i} \binom{k-1}{i-1} \binom{n+i-2}{n} \binom{m+i-2}{m} \\
=& \sum_{i=2}^{n+m+1} \binom{n+i-2}{n} \binom{m+i-2}{m}\sum_{k=i}^{n+m+1} (-1)^{k-i} k \binom{k-1}{i-1} \\
=& \sum_{i=2}^{n+m+1} i \binom{n+i-2}{n} \binom{m+i-2}{m} \sum_{k=i}^{n+m+1} (-1)^{k-i} \binom{k}{i}
\end{aligned}
$$

题目保证了 $\sum n + \sum m$ 比较小。

这说明我们可以枚举 $i$（我刚开始没看到这个限制，所以对着这个式子死活化简不了）。

相当于你要对每个 $1 \le a \le b$ 求出

$$
\sum_{k=a}^b (-1)^{k-a} \binom{k}{a}
$$

其中 $b$ 是常数。而这时一个经典问题，对 $a$ 增量即可。

复杂度 $O(n+m)$。

---

## 作者：UKE_Automation (赞：0)

### CF1747E List Generation

[$\text{Link}$](https://codeforces.com/problemset/problem/1747/E)

首先考虑差分，那么我们现在就是要构造两个数组 $a',b'$，使得 $\sum a'=n,\sum b'=m$ 且不存在 $i$ 使得 $a'_i=b'_i=0$。

考虑先枚举长度，然后计算方案数。接下来枚举 $a'$ 中有多少个 $>0$ 的数，把它们放进去然后用插板法计算方案数；最后再枚举 $b'$ 中有多少个 $>0$ 的数，此时剩下的 $=0$ 的数必须放在上面 $a'_i>0$ 的位置上，算出方案数之后再用插板法即可。这样的话我们的式子应该是：
$$
\sum_{i=1}^{n+m}(i+1)\sum_{p=0}^i \binom{i}{p}\binom{n-1}{p-1}\sum_{q=0}^i\binom{p}{i-q}\binom{m-1}{q-1}
$$
最后的那个和式显然是范德蒙德卷积，所以可以化为：
$$
\sum_{i=1}^{n+m}(i+1)\sum_{p=0}^i \binom{i}{p}\binom{n-1}{p-1}\binom{p+m-1}{i-1}
$$
现在我们有了一个 $O(n^2)$ 的做法，考虑优化。先交换求和顺序：
$$
\sum_{p=1}^n \binom{n-1}{p-1}\sum_{i=p}^{n+m}(i+1)\binom{i}{p}\binom{p+m-1}{i-1}
$$
然后 $(i+1)\dbinom{i}{p}$ 可以写成 $(p+1)\dbinom{i+1}{i-p}$，证明是显然的，所以继续改写为：
$$
\sum_{p=1}^n \binom{n-1}{p-1}(p+1)\sum_{i=p}^{n+m}\binom{i+1}{i-p}\binom{p+m-1}{i-1}
$$
然后我们把后面的组合数乘积暴力展开然后重新组合，这样的话可以得到下面的结果：
$$
\sum_{p=1}^n \binom{n-1}{p-1}\frac{(m+p-1)!}{p!\times m!}\sum_{i=p}^{n+m}(i+1)\times i\times \binom{m}{i-p}
$$
改枚举 $i$ 为 $i-p$ 可得：
$$
\sum_{p=1}^n \binom{n-1}{p-1}\frac{(m+p-1)!}{p!\times m!}\sum_{i=0}^{m}(i+p+1)\times (i+p)\times \binom{m}{i}
$$
此时后面的式子可以拆出 $\sum \binom{m}{i},\sum i\binom{m}{i}$ 以及 $\sum i^2\binom{m}{i}$ 三个部分分别求和，这都是比较经典的组合数恒等式。然后我们就可以在 $O(n)$ 的复杂度内求出答案了。注意求上面三个部分和的时候要预处理 $2$ 的幂，不然的话多带个 $\log$ 过不了。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 1e7 + 5;
const int Inf = 2e9;
const int Mod = 1e9 + 7;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int T, n, m;
int fac[Maxn], inv[Maxn], p2[Maxn];

void init(int N) {
	fac[0] = p2[0] = 1; for(int i = 1; i <= N; i++) fac[i] = 1ll * fac[i - 1] * i % Mod, p2[i] = 2ll * p2[i - 1] % Mod;
	inv[N] = Inv(fac[N]); for(int i = N; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % Mod; 
}

int C(int n, int m) {
	if(n < 0 || m < 0 || n < m) return 0;
	return 1ll * fac[n] * inv[m] % Mod * inv[n - m] % Mod; 
}

int S0(int n) {return p2[n];}
int S1(int n) {return 1ll * n * p2[n - 1] % Mod;}
int S2(int n) {return n < 2 ? 1 : 1ll * n * (n + 1) % Mod * p2[n - 2] % Mod;}

void solve() {
	read(n), read(m);
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		int res = Add(1ll * S0(m) * i % Mod * (i + 1) % Mod, Add(1ll * S1(m) * (2 * i + 1) % Mod, S2(m)));
		pls(ans, 1ll * C(n - 1, i - 1) * fac[m + i - 1] % Mod * inv[i] % Mod * inv[m] % Mod * res % Mod);
	}
	write(ans);
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(T); init(1e7);
	while(T--) solve();
	Usd();
	return 0;
}
```

---

## 作者：OIer_Automation (赞：0)

### Solution1

考虑这个需要求解的内容只满足单调不增是容易的，假设长度为 $k$，只需要分别将 $n,m$ 分别划分成 $k-1$ 个可空的集合，方案数显然是 ${n+k-2\choose k-2}{m+k-2\choose k-2}$，但是这样做会存在两个位置同时为空，这不符合 $a_i+b_i\ne a_{i-1}+b_{i-1}$。我们可以考虑容斥设 $F(k)$ 为将 $n,m$ 分成恰好 $k$ 个可空集合且不存在两个位置同时为空的方案，$G(k)$ 表示分成 $k$ 个可空集合但可以存在两个位置同时为空的方案，显然有 $G(k)={n+k-1\choose k-1}{m+k-1\choose k-1}$，同时因为每个长度都可以在这个长度下钦定一些空位置，所以可以得到
$$
G(k)=\sum_{i=1}^{k}{k\choose i}F(i)\Rightarrow F(k)=\sum_{i=1}^{k}(-1)^{k-i}{k\choose i}G(i)
$$
那么计算答案即为
$$
\begin{aligned}\sum_{k=1}^{n+m}(k+1)F(k)&=\sum_{k=1}^{n+m}(k+1)\sum_{i=1}^{k}(-1)^{k-i}{k\choose i}{n+i-1\choose i-1}{m+i-1\choose i-1}\\&=\sum_{i=1}^{n+m}{n+i-1\choose i-1}{m+i-1\choose i-1}(i+1)\sum_{k=i}^{n+m}(-1)^{k-i}{k+1\choose k-i} \end{aligned}
$$
到这里我们可以设 $f(i,j)=(-1)^j{i+j+1\choose j},g(i)=\sum_{j=0}^{n+m-i}f(i,j)$，我们可以推出 $f,g$ 的递推式为f
$$
\begin{aligned}f(i,j)&=(-1)^j{i+j+1\choose j}\\&=(-1)^j{i+j\choose j}+(-1)^j{i+j\choose j-1}\\&=f(i-1,j)-f(i,j-1) \end{aligned}
$$
从而有
$$
\begin{aligned}g(i)&=\sum_{j=0}^{n+m-i}f(i,j)\\&=\sum_{j=0}^{n+m-i}f(i-1,j)-\sum_{j=0}^{n+m-i}f(i,j-1)\\&=g(i-1)-f(i-1,n+m-i+1)-g(i)+f(i,n+m-i) \end{aligned}
$$
移项后得到 $g(i-1)=2g(i)+f(i-1,n+m-i-1)-f(i,n+m-i)$，至此，我们可以 $O(n+m)$ 递推得出答案的值。这种方法比较巧妙，所以写了一下，然而这样做的常数比较大，所以更推荐另一种。注意组合数要预处理到 $1.5\times10^7$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
 
const int N=1.5e7+5,P=1e9+7;
 
il int Add(int x,int y){int v;return (v=x+y)>=P?v-P:v;}il void Dadd(int &x,int y){(x+=y)>=P?x-=P:x;}
il int Mul(int x,int y){return 1ll*x*y%P;}il void Dmul(int &x,int y){x=1ll*x*y%P;}
il int Qpow(int a){int res=1;for(int b=P-2;b;b>>=1,Dmul(a,a))if(b&1)Dmul(res,a);return res;}
 
int T,n,m,k;
int fac[N],inv[N];
 
il int C(int n,int m){return Mul(fac[n],Mul(inv[m],inv[n-m]));}
il int F(int n){return (k-n)&1?C(k+2,n+1):P-C(k+2,n+1);}
il void Build(){
	cin>>n>>m,k=n+m;int G=1,ans=0;
	for(int i=k;i;--i){
		Dadd(ans,Mul(Mul(G,i+1),Mul(C(n+i-1,i-1),C(m+i-1,i-1))));
		if(i>1)Dadd(G,Add(G,F(i)));
	}
	cout<<ans<<"\n";
}
 
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int S=1.5e7;fac[0]=1;
	for(int i=1;i<=S;++i)fac[i]=Mul(fac[i-1],i);
	inv[S]=Qpow(fac[S]);
	for(int i=S;i;--i)inv[i-1]=Mul(inv[i],i);
	for(cin>>T;T;Build(),--T); 
}
```

### Solution2

考虑不要容斥，直接枚举长度 $k$，然后可以考虑枚举 $n$ 分成 $l$ 个非空段，$m$ 分成 $r$ 个非空段，为了两个没有同时非空的段，那么 $k-r$ 个空段一定要和 $l$ 个非空段对应，那么答案是可以简单得出的，即
$$
\sum_{k=1}^{n+m}(k+1)\sum_{l=1}^{k}{n-1\choose l-1}{k\choose l}\sum_{r=1}^{k}{m-1\choose r-1}{l\choose k-r}
$$
后面的求和是显然的 Vandermonde 卷积，结果为 $m+l-1\choose k-1$，考虑交换求和顺序，得到答案为
$$
\begin{aligned}\sum_{l=1}^{n}{n-1\choose l-1}\sum_{k=l}^{n+m}(k+1){k\choose l}{m+l-1\choose k-1}&=\sum_{l=1}^{n}{n-1\choose l-1}(l+1)\sum_{k=l}^{n+m}{k+1\choose l+1}{m+l-1\choose k-1}\\&=\sum_{l=1}^{n}\frac{1}{m}{n-1\choose l-1}{m+l-1\choose l}\sum_{k=l}^{n+m}k(k+1){m\choose k-l}\end{aligned}
$$
考虑将 $k-l$ 换成 $t$，那么里面的和式即为
$$
\sum_{t=0}^{m}[t^2+(2l+1)t+l^2+l]{m\choose t}
$$
于是只需要快速求出 $\sum_{i=0}^{m}{m\choose i}=2^m,\sum_{i=0}^{m}i{m\choose i}=m2^{m-1},\sum_{i=0}^{m}i^2{m\choose i}=m(m+1)2^{m-2}$，这些都是经典组合数恒等式。总之，后面的和式是可以 $O(1)$ 求解的，那么可以在 $O(n)$ 的复杂度内求解，组合数预处理到 $1\times 10^7$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define il inline
 
const int N=1e7+5,P=1e9+7;
 
il int Add(int x,int y){int v;return (v=x+y)>=P?v-P:v;}il void Dadd(int &x,int y){if((x+=y)>=P)x-=P;}
il int Mod(int x,int p){return x-x/p*p;}
il int Mul(int x,int y){return 1ll*x*y%P;}il void Dmul(int &x,int y){x=1ll*x*y%P;}
il int Qpow(int a,int b=P-2){int res=1;for(;b;b>>=1,Dmul(a,a))if(b&1)Dmul(res,a);return res;}
 
int T,n,m;
int fac[N],inv[N];
 
il int C(int n,int m){return Mul(fac[n],Mul(inv[m],inv[n-m]));}
il void Build(){
	cin>>n>>m;int ans=0,pw=m==1?5e8+4:Qpow(2,m-2);
	for(int l=1,A=m+2,B=m*3+4;l<=n;++l,A+=2,B+=4)Dadd(ans,Mul(Mul(C(n-1,l-1),C(m+l-1,l)),Mul(Add(Mul(A,A),B),pw)));
	cout<<Mul(ans,Qpow(m))<<"\n";
}
 
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int S=1e7;fac[0]=1;
	for(int i=1;i<=S;++i)fac[i]=Mul(fac[i-1],i);
	inv[S]=Qpow(fac[S]);
	for(int i=S;i;--i)inv[i-1]=Mul(inv[i],i);
	for(cin>>T;T;Build(),--T); 
}
```

---

## 作者：vectorwyx (赞：0)

考虑容斥，枚举有多少个位置满足 $a_i+b_i=a_{i+1}+b_{i+1}$，假设有 $i$ 个这样的位置，相当于把这些位置右边的那个位置删掉，然后问开头为 $0$ 结尾为 $n(m)$的长为 $k-i$ 的不降序列各自有多少个。隔板法，方案数为 $\binom{n+k-2-i}{k-2-i}\binom{m+k-2-i}{k-2-i}$，那么答案为 $\sum_{k=2}^{n+m+2}k\sum_{i=0}^{k-2}(-1)^i\binom{k-1}{i}\binom{n+k-2-i}{k-2-i}\binom{m+k-2-i}{k-2-i}$。

转为枚举 $w=k-2-i$，$\sum_{w=0}^{n+m}\binom{n+w}{n}\binom{m+w}{m}\sum_{i=0}^{n+m-w}(-1)^i(w+i+2)\binom{w+i+1}{i}=\sum_{w=0}^{n+m}\binom{n+w}{n}\binom{m+w}{m}\sum_{k=w+2}^{n+m+2}(-1)^{k-w-2}k\binom{k-1}{w+1}$，而 $k\binom{k-1}{w+1}=k\frac{(k-1)!}{(w+1)!(k-w-2)!}=(w+2)\frac{k!}{(w+2)!(k-w-2)!}=(w+2)\binom{k}{w+2}$，所以实际上我们只需要对每个 $w$ 求 $\sum_{k=w+2}^{n+m+2}(-1)^k\binom{k}{w+2}$。这个感受一下是杨辉三角上的列和，自然考虑递推，记上式为 $f(w)$，则 $f(w)=-(f(w)-(-1)^{n+m+2}\binom{n+m+2}{w+2})-(f(w-1)-(-1)^{n+m+2}\binom{n+m+2}{w+1})\iff 2f(w)=(-1)^{n+m}(\binom{n+m+2}{w+1}+\binom{n+m+2}{w+2})-f(w-1)$。复杂度 $O(n+m)$。

代码如下：
```cpp
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

const int N=1.5e7+5,mod=1e9+7,ni2=(mod+1)>>1;
#define modA(x) (x=x<0?x+mod:x)
#define modS(x) (x=x>=mod?x-mod:x)
#define add(x,y) x+=y,modS(x)
#define sub(x,y) x-=y,modA(x)
#define pro(x,y) (int)((ll)(x)*(y)%mod)
#define mul(x,y) x=pro(x,y)
int fac[N],ifac[N];

int ksm(int x,int y){
    int ret=1;
    while(y){
        if(y&1) mul(ret,x);
        y>>=1;
        mul(x,x);
    }
    re ret;
}

int C(int x,int y){
    if(x<0||y<0||x<y) re 0;
    re pro(fac[x],pro(ifac[y],ifac[x-y]));
}

void init(int n){
    fac[0]=1;fo(i,1,n) fac[i]=pro(fac[i-1],i);
    ifac[n]=ksm(fac[n],mod-2);go(i,n-1,0) ifac[i]=pro(ifac[i+1],(i+1));    
}

int n,m,f[N];

void solve(){
    cin>>n>>m;fo(i,0,n+m) f[i]=0;
    // init(max(n+m+2,max(n,m)+n+m));
    fo(k,2,n+m+2){
        if(k&1) sub(f[0],C(k,2));
        else add(f[0],C(k,2));
    }
    fo(w,1,n+m){
        int v=C(n+m+2,w+1)+C(n+m+2,w+2);modS(v);
        if((n+m)&1) sub(f[w],v);
        else add(f[w],v);
        sub(f[w],f[w-1]);
        mul(f[w],ni2);
    }
    // cout<<"f:";out(f,0,n+m);
    int ans=0;
    fo(w,0,n+m){
        int v=pro(pro(C(n+w,n),C(m+w,m)),pro(f[w],w+2));
        if(w&1) sub(ans,v);
        else add(ans,v);
    }
    // fo(k,2,n+m+2){
    //     int sum=0;
    //     fo(i,0,k-2){
    //         int v=pro(C(k-1,i),pro(C(n+k-2-i,n),C(m+k-2-i,m)));
    //         if(i&1) sub(sum,v);
    //         else add(sum,v);
    //     }
    //     add(ans,pro(sum,k));
    // }
    cout<<ans<<'\n';
}

signed main(){
    init(N-5);
    int T=read();
    while(T--) solve();
    return 0;
}
}
/*
-------------------------------------------------
*/










signed main(){re vectorwyx::main();}
```

---

## 作者：BreakPlus (赞：0)

+ 考虑题目中合法的一个数组对 $(a, b)$，等价于一条从网格图上 $(0,0)$ 走到 $(n,m)$ 的路径，每一步只能先向右、再向下走。

+ 先考虑 $f_{n,m}$ 表示走到 $(n,m)$ 这个点的方案数。易得：

1. $2f_{i,j} = \sum \limits_{p=0}^i \sum \limits_{q=0}^j f_{p,q} $
2. $f_{0,0} = 1$

+ 令二元 GF $F = \sum \limits_{i,j} f_{i,j}x^iy^j$，则有 $2F = \dfrac{F}{(1-x)(1-y)} + 1$，解得 $F = \dfrac{(x-1)(y-1)}{2xy-2x-2y+1}$。

+ 再考虑求答案。思考组合意义，算出每个点被多少条路径包含再求和就是答案。对于点 $(x,y)$ 贡献为 $f_{x,y}f_{n-x,m-y}$。

+ 因此答案可以被表示为 $F^2$ 的 $x^ny^m$ 项系数。

-----

+ $F^2 = \dfrac{(x-1)^2(y-1)^2}{(2xy-2x-2y+1)^2}$，分子很容易处理，但分母如果直接展开会有很多项，答案也很难计算。

+ 其中一种做法是对其中一维积分，分母可以降为 $1$ 次，再直接套用 $\dfrac{1}{1-A} = \sum \limits_{i=0}^{+\infty}A^i$ ，分配律展开来计算。可以参考 [foreverlasting](https://www.luogu.com.cn/article/d7xesojm) 的做法，拜谢。

```cpp
inline ll calc(ll x,ll y){
	ll ans = 0;
	for(ll i=0; i<=minn(x,y); i++){
		if(i&1)
			ans = (ans - pw[x+y-i] * Fac(x+y-i) % mod * iFac(i) % mod * iFac(x-i) % mod * iFac(y-i)) % mod;
		else ans = (ans + pw[x+y-i] * Fac(x+y-i) % mod * iFac(i) % mod * iFac(x-i) % mod * iFac(y-i)) % mod;
	}
	ans = (ans % mod + mod) % mod;
	return ans;
}
inline ll calc2(ll n,ll m){
	if(n<0 || m<0) return 0;
	return (n+1) * Minus(calc(n+1, m), calc(n,m)) % mod;
}
void solve(){
	n=read(), m=read();
	ll ans = calc2(n,m) + calc2(n-2, m-2) - 2 * calc2(n-2, m-1) - 2 * calc2(n-1, m-2) + calc2(n-2, m) + calc2(n, m-2) + 4 * calc2(n-1, m-1) - 2 * calc2(n-1, m) - 2 * calc2(n, m-1);
	ans = (ans % mod + mod) % mod;
	printf("%lld\n", ans);
}
```

-----

+ 笔者想到的另一种做法是将其中一维作为主元，然后希望把分子化为 $\dfrac{1}{(1-A)^2}$ 的形式。注： $\dfrac{1}{(1-A)^k} = \sum \limits_{i=0}^{+\infty}{i+k-1 \choose k-1}A^i$。

$$\begin{aligned}F^2 &= \dfrac{(x-1)^2(y-1)^2}{(2xy-2x-2y+1)^2} \\&= \dfrac{(x-1)^2(y-1)^2}{((2y-2)x+(1-2y))^2}\\&=  \dfrac{(x-1)^2(y-1)^2}{(2y-1)^2}\dfrac{1}{(1-\frac{2y-2}{2y-1}x)^2}\end{aligned}$$

+ 右边变成了我们想要的形式，可以写成 $\sum \limits_{i=0}^{+\infty}(i+1)\dfrac{(2y-2)^i}{(2y-1)^i}x^i$。

+ 而左边的分母有点烦人，方便起见，我们发现左边 $\dfrac{y-1}{2y-1}$ 和右边的 $\dfrac{2y-2}{2y-1}$ 有点像，可以吸收到右边。

+ 式子变成了 $F^2 = \dfrac{(x-1)^2}{4}\sum \limits_{i=0}^{+\infty}(i+1)\dfrac{(2y-2)^{i+2}}{(2y-1)^{i+2}}x^i$。

+ 左边同样平凡，观察右边，发现 $x^ny^m$ 的系数已经精确定位到只存在于 $i=n$ 这一项了，只需要计算 $\dfrac{(2y-2)^{n+2}}{(2y-1)^{n+2}}$ 中 $y^m$ 的系数。

+ 方便起见，写成 $(1+\dfrac{1}{1-2y})^{n+2}$，二项式定理展开就大功告成了。

```cpp
inline ll calc(ll n,ll m){
	if(n<0 || m<0) return 0;
	ll ans = 0, T = Fac(n+2) * iFac(m) % mod; 
	for(ll i=0; i<=n+2; i++){
		if(i==0 && m==0) {
			ans = (ans + 1) % mod;
			continue;
		}
		ans = (ans + T * iFac(n+2-i) % mod * iFac(i) % mod * Fac(m+i-1) % mod * iFac(i-1)) % mod;
	}
	ans = ans * pw[m] % mod * (n+1) % mod; return ans;
}
void solve(){
	n=read(), m=read();
	ll ans = calc(n, m) - 2 * calc(n-1, m) + calc(n-2, m);
	ans = (ans % mod + mod) % mod;
	printf("%lld\n", ans * inv4 % mod); 
}
```

---

## 作者：Chinese_zjc_ (赞：0)

首先可以把问题转化为：初始有二元组 $r=(n,m)$ ，每轮需要选择一个由非负整数构成的二元组 $(x,y)$ $(0\leq x\leq n,0\leq y\leq m,x+y>0)$ 并令 $r\leftarrow r-(x,y)$ ，直到 $r=(0,0)$ 为止。若执行了 $k$ 次操作，则它对答案的贡献为 $[z](1+z)^{k+1}$ 。

那现在设答案为 $[x^ny^mz]F$ ，其中：
$$
F=\left(\frac{F}{(1-x)(1-y)}-F+1\right)(1+z)
$$
读者可以自行解出方程，这里是答案：
$$
F=\frac{(1-x)(1-y)(1+z)}{1-2x-2y+2xy-xz-yz+xyz}
$$
下面是求解上方程的过程：
$$
a=(1-x)(1-y),b=(1+z)\\
F=\left(\frac{F}{a}-F+1\right)b\\
F-\frac{Fb}{a}+Fb=b\\
(a-b+ab)F=ab\\
F=\frac{ab}{a-b+ab}\\
$$
显然，我们要求 $[x^ny^mz]F$ ，可以先求出 $G=[y^m]F$ ，然后去求出 $[x^nz]G$ 的值：
$$
\begin{aligned}
G&=[y^m]F\\
&=[y^m]\frac{(1-x)(1+z)-(1-x)(1+z)y}{(1-2x-xz)-(2-2x+z-xz)y}\\
&=[y^m]\frac{\frac{(1-x)(1+z)-(1-x)(1+z)y}{1-2x-xz}}{1-\frac{2-2x+z-xz}{1-2x-xz}y}\\
&=\frac{(1-x)(1+z)}{1-2x-xz}\cdot\left(\frac{2-2x+z-xz}{1-2x-xz}\right)^{m}-\frac{(1-x)(1+z)}{1-2x-xz}\cdot\left(\frac{2-2x+z-xz}{1-2x-xz}\right)^{m-1}\\
\end{aligned}
$$
*注：$[x^n]\frac{a}{1-bx}=ab^n$

不妨设 $G_m=\frac{(1-x)(1+z)}{1-2x-xz}\cdot\left(\frac{2-2x+z-xz}{1-2x-xz}\right)^{m}$ ，那么就有 $G=G_m-G_{m-1}$ 。

由于下文中会频繁出现 $1-x$ 和 $1-2x$ ，我们约定 $A=1-x$ ，$B=1-2x$ 。

接下来只需要求出 $[x^nz]G_m$ 。依然令 $H_m=[z]G_m$ ，转化为求 $[x^n]H_m$ ：
$$
\begin{aligned}
H_m&=[z]G_m\\
&=[z]\left(\frac{(1-x)(1+z)}{1-2x-xz}\cdot\left(\frac{2-2x+z-xz}{1-2x-xz}\right)^{m}\right)\\
&=[z]\left(\frac{A(1+z)}{B-xz}\cdot\left(\frac{A(2+z)}{B-xz}\right)^{m}\right)\\
&=[z^0]\frac{A(1+z)}{B-xz}\cdot[z]\left(\frac{A(2+z)}{B-xz}\right)^{m}+[z]\frac{A(1+z)}{B-xz}\cdot[z^0]\left(\frac{A(2+z)}{B-xz}\right)^{m}\\
&=\frac{A}{B}\cdot{m\choose 1}\cdot\left(\frac{2xA}{B^2}+\frac{A}{B}\right)\cdot\left(\frac{2A}{B}\right)^{m-1}+\left(\frac{xA}{B^2}+\frac{A}{B}\right)\cdot\left(\frac{2A}{B}\right)^m\\
&=\frac{A}{B}\cdot{m\choose 1}\cdot\left(\frac{2x-2x^2}{B^2}+\frac{1-3x+2x^2}{B^2}\right)\cdot\left(\frac{2A}{B}\right)^{m-1}+\left(\frac{x-x^2}{B^2}+\frac{1-3x+2x^2}{B^2}\right)\cdot\left(\frac{2A}{B}\right)^m\\
&=\frac{A}{B}\cdot{m\choose 1}\cdot\frac{1-x}{B^2}\cdot\left(\frac{2A}{B}\right)^{m-1}+\frac{1-2x+x^2}{B^2}\cdot\left(\frac{2A}{B}\right)^m\\
&=\frac{A}{B}\cdot{m\choose 1}\cdot\frac{A}{B^2}\cdot\left(\frac{2A}{B}\right)^{m-1}+\frac{A^2}{B^2}\cdot\left(\frac{2A}{B}\right)^m\\
&=\frac{A}{B}\cdot m\cdot\frac{A}{B^2}\cdot\left(\frac{2A}{B}\right)^{m-1}+\frac{A^2}{B^2}\cdot\left(\frac{2A}{B}\right)^m\\
&=2^{m-1}\cdot m\cdot\frac{A^{m+1}}{B^{m+2}}+2^m\cdot\frac{A^{m+2}}{B^{m+2}}\\
\end{aligned}
$$
于是乎接下来只需要求出 $[x^n]H_m$ ，这等价求 $[x^n]\frac{A^a}{B^b}$ ，显然有 $[x^n]A^a=(-1)^n{a\choose n}$ ，$[x^n]\frac{1}{B^b}={n+b-1\choose n}$ 。直接代入求值即得：
$$
[x^n]\frac{A^a}{B^b}=\sum_{i=0}^{n}(-1)^{n-i}2^i{a\choose n-i}{b+i-1\choose i}
$$
至此直接代入答案就是 $O(n)$ 了，但是常数较大，若不在意常数地实现可能 TLE ，可以进行下面优化。

把式子全部代入到 $F$ 中发现答案是：
$$
\begin{aligned}
&[x^n]\left(\frac{A^{m+2}}{B^{m+2}}\cdot2^m+\frac{A^{m+1}}{B^{m+2}}\cdot m\cdot 2^{m-1}-\frac{A^{m+1}}{B^{m+1}}\cdot2^{m-1}-\frac{A^{m}}{B^{m+1}}\cdot (m-1)\cdot 2^{m-2}\right)\\
=&[x^n]\left(\frac{A^{m}4A^2}{B^{m+2}}\cdot2^{m-2}+\frac{A^m2mA}{B^{m+2}}\cdot 2^{m-2}-\frac{A^m2AB}{B^{m+2}}\cdot2^{m-2}-\frac{A^m(m-1)B}{B^{m+2}}\cdot 2^{m-2}\right)\\
=&[x^n]\frac{A^{m}(4A^2+2mA-2AB-(m-1)B)}{B^{m+2}}\cdot2^{m-2}\\
=&[x^n]\frac{A^{m}(4(1-2x+x^2)+2m(1-x)-2(1-3x+2x^2)-(m-1)(1-2x))}{B^{m+2}}\cdot2^{m-2}\\
=&[x^n]\frac{A^{m}(m+3-4x)}{B^{m+2}}\cdot2^{m-2}\\
=&\frac{(m+3)}{4}[x^n]\frac{A^{m}}{B^{m+2}}\cdot2^m-[x^{n-1}]\frac{A^{m}}{B^{m+2}}\cdot2^{m}\\
\end{aligned}
$$
这样就只要两次求值，优化了一半的计算。

```cpp
// This Code was made by Chinese_zjc_.
#include <bits/stdc++.h>
// #define debug
const int MOD = 1000000007;
struct mint
{
    unsigned v;
    mint(unsigned v_ = 0) : v(v_) {}
    mint operator-() const { return v ? MOD - v : *this; }
    mint &operator+=(const mint &X) { return (v += X.v) >= MOD ? v -= MOD : v, *this; }
    mint &operator-=(const mint &X) { return (v += MOD - X.v) >= MOD ? v -= MOD : v, *this; }
    mint &operator*=(const mint &X) { return v = 1llu * v * X.v % MOD, *this; }
    mint &operator/=(const mint &X) { return *this *= X.inv(); }
    mint pow(long long B) const
    {
        B %= MOD - 1;
        if (B < 0)
            B += MOD - 1;
        mint res = 1, A = *this;
        while (B)
        {
            if (B & 1)
                res *= A;
            B >>= 1;
            A *= A;
        }
        return res;
    }
    mint inv() const { return pow(MOD - 2); }
    friend mint operator+(const mint &A, const mint &B) { return mint(A) += B; }
    friend mint operator-(const mint &A, const mint &B) { return mint(A) -= B; }
    friend mint operator*(const mint &A, const mint &B) { return mint(A) *= B; }
    friend mint operator/(const mint &A, const mint &B) { return mint(A) /= B; }
    friend std::istream &operator>>(std::istream &A, mint &B) { return A >> B.v; }
    friend std::ostream &operator<<(std::ostream &A, const mint &B) { return A << B.v; }
    friend bool operator==(const mint &A, const mint &B) { return A.v == B.v; }
    explicit operator bool() const { return v; }
} fact[10000005], ifact[10000005], pw[10000005];
mint C(int n, int m) { return 0 <= m && m <= n ? fact[n] * ifact[m] * ifact[n - m] : 0; }
int T, n, m;
mint work(int A, int B, int n)
{
    mint res = 0;
    for (int i = 0; i <= n; ++i)
        res += ((n - i) & 1 ? -pw[i] : pw[i]) * C(A, n - i) * C(i + B - 1, i);
    return res;
}
signed main()
{
    std::ios::sync_with_stdio(false);
    fact[0] = 1;
    for (int i = 1; i <= 10000002; ++i)
        fact[i] = fact[i - 1] * i;
    ifact[10000002] = fact[10000002].inv();
    for (int i = 10000002; i; --i)
        ifact[i - 1] = ifact[i] * i;
    pw[0] = 1;
    for (int i = 1; i <= 10000002; ++i)
        pw[i] = pw[i - 1] + pw[i - 1];
    std::cin >> T;
    while (T--)
    {
        std::cin >> n >> m;
        std::cout << work(m, m + 2, n) * (m + 3) * pw[m] / 4 - work(m, m + 2, n - 1) * pw[m] << std::endl;
    }
    return 0;
}
```

---

## 作者：Yahbim (赞：0)

前言：复杂度 $O(n+m)$，然后被卡常了 ):

考虑差分数组。问题转化为：对于任意 $k$，画一个 $2\times k$ 的空矩阵，求分别分配 $n$ 个球到第一行、分配 $m$ 个球到第二行，使得不存在一列同时为 $0$ 的方案数对 $k$ 的累和。

条件形式比较经典，考虑容斥，可以得到 $O(n^2)$ 的表达式（下记 $r=n+m$）：

$$
\sum_{len=0}^{r}(len+1)\sum_{k=0}^{len}(-1)^k\binom{len}{k}\binom{n+len-k-1}{len-k-1}\binom{m+len-k-1}{len-k-1}
$$

令 $t=len-k$，整理得：
$$
\sum_{t=0}^{r}\binom{n+t-1}{n}\binom{m+t-1}{m}\sum_{k=0}^{n-t}(-1)^k\binom{t+k}{k}(k+t+1)
$$
再令 $k=k+t$，整理得：
$$
\sum_{t=0}^{r}\binom{n+t-1}{n}\binom{m+t-1}{m}\sum_{k=t}^{n}(-1)^{k+t}\binom{k}{t}(k+1)
$$
设 $f(t)=\sum_{k=t}^{n}(-1)^{k+t}\binom{k}{t}(k+1)$，考虑递推 $f(t)$：
$$
\begin{aligned}
f(t)&=\sum_{k=t}^{n}(-1)^{k+t}\binom{k}{t}(k+1)\\
&=(t+1)\sum_{k=t}^{n}(-1)^{k+t}\binom{k+1}{t+1}\\
&=(t+1)\sum_{k=t+1}^{n+1}(-1)^{k-1+t}\binom{k}{t+1}\\
&=(t+1)[(-1)^{r+t}\binom{r+1}{t+1}+\sum_{k=t+1}^{n}(-1)^{k+t+1}\binom{k}{t+1}]\\
&=(t+1)[(-1)^{r+t}\binom{r+1}{t+1}+g(t+1)]
\end{aligned}
$$
上设 $g(t)=\sum_{k=t}^{n}(-1)^{k+t}\binom{k}{t}$，再考虑递推 $g(t)$。先把 $g(t)$ 变形为 $\sum_{k=t}^{n}(-1)^{k+t}\binom{k}{k-t}$，再观察 $g$ 的后缀和，设为 $h$，可以发现长得是一个抵在杨辉三角最右边的子三角，且每个左上-右下对角线同号。那么可以得到：
$$
\begin{aligned}
h(t+1)-g(t)&=-1+\sum_{i=t+1}^r(-1)^{r-i}\binom{r+1}{i}\\
g(t)&=h(t+1)+1-\sum_{i=t+1}^r(-1)^{r-i}\binom{r+1}{i}\\
&=h(t+1)+1-s(t+1)
\end{aligned}
$$
上设 $s(t)=\sum_{i=t}^r(-1)^{r-i}\binom{r+1}{i}$，$s(t)$ 的递推式显然为：
$$
s(t)=s(t+1)+(-1)^{r-t}\binom{r+1}{t}
$$
递推结束。代码（被卡常）：

```cpp
#include<iostream>
typedef long long ll;
int read(int ret=0,char ch=getchar()){
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch)) ret=ret*10+ch-'0',ch=getchar();
    return ret;
}
void _write(int x){
    if(x>9) _write(x/10);
    putchar('0'+x%10);
}
void write(int x){_write(x),putchar('\n');}
const int N=3e7+5,P=1e9+7;
int n,m,r,fac[N],ifac[N];

inline ll binom(int x,int y){return 1ll*fac[x]*ifac[y]%P*ifac[x-y]%P;}

signed main(){
    fac[0]=1,ifac[N-1]=373753487;
    for(int i=1;i<N;++i) fac[i]=1ll*fac[i-1]*i%P;
    for(int i=N-2;~i;--i) ifac[i]=1ll*ifac[i+1]*(i+1)%P;
    for(int tes=read();tes;--tes){
        n=read(),m=read(),r=n+m;
        ll g=1,h=1,s=binom(r+1,r),f=r+1,ans=binom(n+r-1,n)*binom(m+r-1,m)%P*f%P;
        for(int i=r-1;i;--i){
            f=(g+((r+i)&1?(P-1):1)*binom(r+1,i+1))%P*(i+1)%P;
            g=(h+1+P-s)%P;
            s=(s+binom(r+1,i)*((r-i)&1?P-1:1))%P;
            h=(h+g)%P;
            ans=(ans+binom(n+i-1,n)*binom(m+i-1,m)%P*f)%P;
        }
        write(ans);
    }
    return 0;
}

//~kawaii~
```



---

