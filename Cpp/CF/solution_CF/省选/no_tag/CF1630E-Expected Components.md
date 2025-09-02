# Expected Components

## 题目描述

Given a cyclic array $ a $ of size $ n $ , where $ a_i $ is the value of $ a $ in the $ i $ -th position, there may be repeated values. Let us define that a permutation of $ a $ is equal to another permutation of $ a $ if and only if their values are the same for each position $ i $ or we can transform them to each other by performing some cyclic rotation. Let us define for a cyclic array $ b $ its number of components as the number of connected components in a graph, where the vertices are the positions of $ b $ and we add an edge between each pair of adjacent positions of $ b $ with equal values (note that in a cyclic array the first and last position are also adjacents).

Find the expected value of components of a permutation of $ a $ if we select it equiprobably over the set of all the different permutations of $ a $ .

## 说明/提示

In the first test case there is only $ 1 $ different permutation of $ a $ :

- $ [1, 1, 1, 1] $ has $ 1 $ component.
- Therefore the expected value of components is $ \frac{1}{1} = 1 $

In the second test case there are $ 4 $ ways to permute the cyclic array $ a $ , but there is only $ 1 $ different permutation of $ a $ :

- $ [1, 1, 1, 2] $ , $ [1, 1, 2, 1] $ , $ [1, 2, 1, 1] $ and $ [2, 1, 1, 1] $ are the same permutation and have $ 2 $ components.
- Therefore the expected value of components is $ \frac{2}{1} = 2 $

In the third test case there are $ 6 $ ways to permute the cyclic array $ a $ , but there are only $ 2 $ different permutations of $ a $ :

- $ [1, 1, 2, 2] $ , $ [2, 1, 1, 2] $ , $ [2, 2, 1, 1] $ and $ [1, 2, 2, 1] $ are the same permutation and have $ 2 $ components.
- $ [1, 2, 1, 2] $ and $ [2, 1, 2, 1] $ are the same permutation and have $ 4 $ components.
- Therefore the expected value of components is $ \frac{2+4}{2} = \frac{6}{2} = 3 $

In the fourth test case there are $ 120 $ ways to permute the cyclic array $ a $ , but there are only $ 24 $ different permutations of $ a $ :

- Any permutation of $ a $ has $ 5 $ components.
- Therefore the expected value of components is $ \frac{24\cdot 5}{24} = \frac{120}{24} = 5 $

## 样例 #1

### 输入

```
5
4
1 1 1 1
4
1 1 2 1
4
1 2 1 2
5
4 3 2 5 1
12
1 3 2 3 2 1 3 3 1 3 3 2```

### 输出

```
1
2
3
5
358642921```

# 题解

## 作者：dead_X (赞：7)

## 前言

* 我都会做的数数题。
* CF 经常会把题目评分的第一位搞混，可能这是 *900 而不是 *2900。

所以能不能评红。

## 思路

下文记 $i$ 出现次数为 $c_i$，序列下标从 $0$ 开始（为了取模方便）。

不难发现连通块数量等价于相邻且不相同的位置数。

一个特例为整张图只有一个连通块，但是我们可以特判所有数相同情况。

我们不难设计一个简单算法：

* 钦定 $a_0=a_1$，统计满足条件的排列数为 $S$。
* 统计总排列数为 $T$。
* 答案即为 $\frac{nS}{T}$。

如果去掉题目中“循环重构算同一个排列”的限制，$S$ 和 $T$ 的计算都很平凡，就是一个组合数 $\dbinom{n}{c_1,c_2,\cdots,c_n}$。

那么加上这个限制我们还能做吗？能！

我们考虑对于所有 $i|n$，分别求出最小循环周期**恰好**为 $\frac{n}{i}$ 的合法排列和总排列数，然后计算答案，显然答案即为 $\dfrac{n\sum S_i}{\sum T_i}$。

不难先想到求出最小循环周期为 $\frac{n}{i}$ **的因数**的合法排列和总排列数，即 $S'_i=\sum\limits_{i|j}S_j,T'_i=\sum\limits_{i|j}T_j$，这就等价于 $a_t=a_{t\bmod i}$ 的合法方案数。

$S'_x,T'_x$ 是相对好求的：所有 $c_i$ 都需要是 $x$ 的因数，$T'_x$ 即为 $\dbinom{\frac{n}{x}}{\frac{c_1}{x},\frac{c_2}{x}\cdots,\frac{c_n}{x}}$，我们求 $S'_x$ 时只是将 $\frac{n}{x}\to \frac{n}{x}-2,\frac{c_i}{x}\to \frac{c_i}{x}-2$，预处理阶乘倒数和整体答案即可。

最后枚举因数去掉不合法的即可求出每个 $S_x,T_x$。

稍微分析一下复杂度：

* 预处理阶乘和阶乘倒数：$O(n)$。
* 计算 $S'_x$：$n$ 只有 $\sqrt n$ 个因数，而本质不同的 $c_i$ 只有 $\sqrt n$ 个，对于每种不同的 $c_i$ 我们直接快速幂，时间复杂度 $O(\log n)$，总时间复杂度 $O(n\log n)$。
* 计算 $T'_x$：直接通过 $S'_x$ 乘上阶乘和阶乘倒数得到，$O(n)$。
* 枚举倍数求出 $S_x,T_x$：$O(n\ln n)$。

总时间复杂度为 $O(n\log n)$。

## 代码

可读性可能较差，仅供对拍。

```cpp
// Problem: E. Expected Components
// Contest: Codeforces Round #768 (Div. 1)
// URL: https://codeforces.com/contest/1630/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//And in that light,I find deliverance.
#include<bits/stdc++.h>
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
int a[1000003],b[1000003],c[1000003],fac[1000003],ifac[1000003];
int f[1000003],F[1000003],F_[1000003],FF[1000003],iv[1000003];
signed main()
{
	fac[0]=ifac[0]=1;
	for(int i=1; i<=1000000; ++i) 
	iv[i]=qp(i,p-2),fac[i]=fac[i-1]*i%p,ifac[i]=qp(fac[i],p-2);
	for(int T=read();T--;)
	{
		int n=read();
		for(int i=1; i<=n; ++i) a[i]=b[i]=0,f[i]=-1;
		for(int i=1; i<=n; ++i) ++a[read()];
		for(int i=1; i<=n; ++i) ++b[a[i]];
		int cnt=0;
		for(int i=1; i<=n; ++i) if(b[i]) c[++cnt]=i;
		int O=n;
		for(int i=1; i<=n; ++i) if(a[i]) O=__gcd(O,a[i]);
		for(int i=1; i<=O; ++i)if(O%i==0)
		{
			F[i]=fac[n/i];
			for(int j=1; j<=cnt; ++j)
				F[i]=F[i]*qp(ifac[c[j]/i],b[c[j]])%p;
			FF[i]=F[i];
		}
		for(int i=O; i>=1; --i) if(O%i==0)
			for(int j=2; i*j<=O; ++j) if(O%(i*j)==0)
				FF[i]=(FF[i]+p-FF[i*j])%p;
		bool S=0;
		for(int i=1; i<=n; ++i) if(a[i]==n) S=1;
		if(S){puts("1");continue;}
		int ans=0;
		for(int i=1; i<=O; ++i) if(O%i==0) ans=(ans+FF[i]*iv[n/i]%p)%p;
		int AA=ans;
		for(int i=1; i<=n; ++i) if(a[i]>=2)
		{
			if(f[a[i]]!=-1){ans=(ans+f[a[i]])%p;continue;}
			int R=0;
			for(int j=1; j<=O; ++j) if(O%j==0) if(a[i]/j>=2)
				F_[j]=F[j]*fac[a[i]/j]%p*ifac[a[i]/j-2]%p*ifac[n/j]%p*fac[n/j-2]%p;
				else F_[j]=0;
			for(int j=O; j>=1; --j)if(O%j==0)
				for(int k=2; j*k<=O; ++k)if(O%(j*k)==0)
					F_[j]=(F_[j]+p-F_[j*k])%p;
			for(int j=1; j<=O; ++j) if(O%j==0)
				R=(R+F_[j]*iv[n/j]%p)%p;
			f[a[i]]=(p-R)%p;
			ans=(ans+f[a[i]])%p;
		}
		printf("%lld\n",ans*n%p*qp(AA,p-2)%p);
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

> *III. [CF1630E Expected Components](https://www.luogu.com.cn/problem/CF1630E)
>
> [群论学习小记](https://www.cnblogs.com/alex-wei/p/Group_theory.html)。

高妙计数题。考虑将问题分为两部分来做：一是求方案数，二是求总连通块数量。

性质 1：我们并不关心数字的值，仅关心每个数字的出现次数 $cnt$。因此，设不同的数共有 $c$ 个，大小分别为 $1\sim c$，出现次数分别为 $cnt_1, cnt_2, \cdots, cnt_c$。

求方案数：循环同构自然想到 Burnside 引理。我们需要求出在旋转 $k\ (1\leq k\leq n)$ 个单位下不动点的数量。

我们知道，旋转 $k$ 单位的置换 $g_k$ 会将大小为 $n$ 的循环队列分成 $\gcd(n, k)$ 个大小为 $\dfrac n {\gcd(n, k)}$ 的等价类，每个等价类内部所有数应相等，才能保证它在置换 $g_k$ 下 **不动**。例如当 $k = 2$，$n = 6$ 时，只有 $a_1 = a_3 = a_5$ 且 $a_2 = a_4 = a_6$ 时它是 $g_2$ 的不动点，故只需要确定 $a_1, a_2$ 即可确定整个序列。换句话说，$a_1 \sim a_{\gcd(n, k)}$ 是 **自由变量**，$g_k$ 把循环队列的大小从 $n$ 缩成了 $\gcd(n, k)$。

考虑枚举 $k$，令 $L = \gcd(n, k)$，$d = \dfrac n L$，则相当于我们将问题规模缩小了 $d$ 倍：因为 $a_1 \sim a_L$ 是自由变量，而 $a_i\ (L < i \leq n)$ 依赖于 $a_{i - L}$ 的取值（必须与 $a_{i - L}$ 相等），这样才能保证 $a$ 在置换 $g_k$ 下不动。

因此，总方案数即 $\dbinom {L}{\frac {cnt_1} d, \frac {cnt_2} d, \cdots, \frac {cnt_c} d}$ 表示往 $L$ 个位置分别放入 $\dfrac {cnt_i} d$ 个相同的数，这是经典的多重组合数。

直接枚举 $k$，时间复杂度平方，无法接受。但注意到很多 $k$ 均无解：对应算出的 $d$ 不整除于某个 $cnt$。此时我们无法将问题规模缩小 $d$ 倍，即 $g_k$ 不存在不动点。另有很多 $k$ 和 $n$ 的 $\gcd$ 相等，说明我们进行了很多次重复计算。

容易发现 $d$ 应当满足 $d\mid \gcd(cnt_i, n)$，故直接枚举 $\gcd(cnt_i, n)$ 的因数 $d$，算出 $L$ 以及对应的多重组合数，记为 $f_L$，表示长为 $L$ 的循环队列的答案。总方案数即
$$
\dfrac{\sum_{i = 1} ^ n f_{\gcd(i, n)}} n
$$
类似的，对于连通块数量，由于任意两个相邻的不同的数均会产生 $1$ 的贡献，故直接枚举这两个数 $x, y\ (x\neq y)$。总方案数为 $g_L = \dbinom {L - 2}{\frac {cnt_1} d, \frac {cnt_2} d, \cdots , \frac {cnt_x} d - 1, \cdots , \frac {cnt_y} d - 1, \frac {cnt_c} d}\times n$，这是因为我们钦定了某两个相邻元素分别为 $x, y$，贡献即剩下来的所有数的排列方案数，乘以可能产生贡献的所有位置数量。注意乘以的是 $n$ 而非 $L$：即使 $a_{L + 1} \sim a_n$ 依赖于 $a_1\sim a_L$，但当 $a_1\sim a_L$ 产生贡献时，它们也会相应产生贡献。

发现上式即 $\dfrac{f_L\times cnt_x\times cnt_y}{L\times (L - 1) \times d ^ 2}$，故只需求出 $\sum\limits_{x\neq y} cnt_x \cdot cnt_y$。这容易做到。

求 $f, g$ 的时间复杂度在精细实现下均为线性。复杂度瓶颈在于为计算答案 $\dfrac {\sum\limits_{i = 1} ^ n g_{\gcd(n, i)}}{\sum\limits_{i = 1} ^ n f_{\gcd(n, i)}}$，求每个数与 $n$ 的 $\gcd$ 的线性对数，但常数非常小。注意特判 $c = 1$ 的特殊情况。[代码](https://codeforces.com/contest/1630/submission/146245747)。

---

## 作者：周子衡 (赞：6)

如果全部 $a_i$ 都相同答案则为 $1$，接下来我们假设不会出现这种情况。记 $cnt_i$ 表示数字 $i$ 出现的次数，可以发现答案只和 $cnt_1,...,cnt_n$ 构成的多重集有关。

为了方便理解，这里声明：下文所有“相同”指“完全相同”，即两个序列对应位置全部一样；“本质相同”指两个序列可以通过旋转变成同一个序列。“不同”和“本质不同”分别是“相同”和“本质相同”的反义词。

本题最重要的是处理旋转时的周期问题。正常情况下，一个圆排列旋转 $n$ 次都能得到不同的圆排列。但如果一个圆排列有长度为 $\dfrac{n}{k}$ 的周期的话，它每转 $\dfrac{n}{k}$ 次就能回到起始状态，也就是说，它通过旋转只能旋转出 $\dfrac{n}{k}$ 种不同的圆排列。

可以知道，连通块数等于总点数减去两个端点同色的边数。我们不妨把这题拆成两部分来做：计算所有本质不同的排列数量，以及这些排列对应的同色边数之和。先来求解本质不同的排列数量。考虑全部本质不同的排列中，最小周期为 $\dfrac{n}{k}$ 的恰有 $a_k$ 个。取 $d=(cnt_1,...,cnt_n)$，显见当 $k\nmid d$ 时 $a_k=0$。我们要求的便是 $\sum_{k|d}a_k$。

我们知道，在环上任意安排 $1\sim n$ 的方法总数为 $\binom{n}{cnt_1,...,cnt_n}=\dfrac{n}{cnt_1!\times ...\times cnt_n!}$。而这些方法中，每个最小周期为 $\dfrac{n}{k}$ 的都出现了恰好 $\dfrac{n}{k}$ 次，我们有

$$
\sum_{k|d}\dfrac{n}{k}\times a_k=\dfrac{n!}{cnt_1!\times \cdots\times cnt_n!}=g_1
$$

这便是一个关于 $a_1\sim a_d$ 的方程。当然仅凭这一个方程求解 $\sum a_i$ 远远不够。我们来考虑，对每个 $k|d$，所有存在长度为 $\dfrac{n}{k}$ 循环节的圆排列的数量。一方面，由于只需确定其一个循环节就能确定整个排列，这样的排列的数量一共有 $\dfrac{(\frac{n}{k})!}{(\frac{cnt_1}{k})!\times\cdots\times (\frac{cnt_n}{k})!}$ 个；另外地，对每个 $k|u,u|d$，每个最小周期为 $\dfrac{n}{u}$ 的本质不同圆排列在这些排列中出现了 $\dfrac{n}{u}$ 次。所以对每个 $k|d$，我们都可以列出一个方程：

$$
\sum_{k|u,u|d}\dfrac{n}{u}\times a_u=\dfrac{(\frac{n}{k})!}{(\frac{cnt_1}{k})!\times\cdots\times (\frac{cnt_n}{k})!}=g_k
$$

经过一些数论上的计算，我们得到：

$$
\sum_{k|d} a_k=\dfrac{\sum_{k|d}\varphi(k)\times g_k}{n}
$$

其中 $\varphi(k)$ 是欧拉函数。关于它的推导过程我们放在正文末尾。

----------------------

接下来我们来解决后一部分：计算全部本质不同排列对应的同色边数之和。如法炮制，设在全部本质不同的排列中，最小周期为 $\dfrac{n}{k}$ 的排列同色边数之和为 $b_k$。（同色边就是指一对值相同、位置相邻的元素。）欲求即 $\sum b_k$。类似上文，我们来利用全部拥有周期 $\dfrac{n}{k}$ 的排列列方程：

$$
\sum_{k|u,u|d}\dfrac{n}{u}\times a_u=f_k
$$

这里 $f_k$ 即为全部拥有周期 $\dfrac{n}{k}$ 的排列的同色边数总和。我们来计算 $f_k$。显见，我们可以对每种颜色的同色边分开考虑。对某种颜色 $i$ 和某条固定的边 $j$，$j$ 两边都是 $i$ 的情况数有

$$
\binom{\frac{n}{k}-2}{\frac{cnt_i}{k}-2,\frac{cnt_1}{k},...,\frac{cnt_{i-1}}{k},\frac{cnt_{i+1}}{k},...,\frac{cnt_n}{k}}
$$

这是因为，考虑包含这条边的某个周期，该周期内与该边相邻的两点颜色固定为 $i$，其他点可以任意染色。所以我们得到

$$
f_k=\sum_{i=1}^nn\times \binom{\frac{n}{k}-2}{\frac{cnt_i}{k}-2,\frac{cnt_1}{k},...,\frac{cnt_{i-1}}{k},\frac{cnt_{i+1}}{k},...,\frac{cnt_n}{k}}
$$

当然直接计算由于组合数项数很多，会导致时间复杂度过高。考虑利用已经计算出的 $g_k$：

$$
f_k=\sum_{i=1}^nn\times g_k\times \dfrac{\binom{\frac{n}{k}-2}{\frac{cnt_i}{k}-2}}{\binom{\frac{n}{k}}{\frac{cnt_i}{k}}}
$$

我们便可以高效地计算出 $f_k$ 了。在获得 $f_k$ 的值后，我们还是通过数论计算，得出：

$$
\sum_{k|d} b_k=\dfrac{\sum_{k|d}\varphi(k)\times f_k}{n}
$$

最后输出 $\dfrac{\sum b_k}{\sum a_k}$ 即可。注意到实际参与计算的 $i$ 只有 $\dfrac{n}{d}$ 个（这是因为每个 $cnt_i$ 都是 $d$ 的倍数），这样可以分析得到总时间复杂度 $O(n)$（需要预处理阶乘及其逆元）。下面的代码由于偷懒，总时间复杂度 $O(n\log n)$，也可以通过本题。

-------------------------------------------

在进入代码环节之前先补证上面的结论。实际上，这两个问题都等价于下面的问题：

- 设实数 $c_1,...,c_d$ 满足对每个 $k|d$， $\sum_{k|u,u|d}\dfrac{c_u}{u}=z_k$。用 $z_1\sim z_d$ 表示 $\sum_{k|d}c_k$。

实际上我们知道

$$
\sum_{k|d} \varphi(k) z_k=\sum_{k|d}\sum_{k|u,u|d}\dfrac{c_u}{u}\varphi(k)=\sum_{u|d}\dfrac{c_u}{u}\sum_{k|u}\varphi(k)=\sum_{u|d}\dfrac{c_u}{u}\times u=\sum_{u|d} c_u
$$

即证。

----------------------------------

代码：

```cpp
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
int gcd(int x,int y){return y?gcd(y,x%y):x;}
 
const long long MOD=998244353,G=3;
long long add(long long x,long long y){return x+y>=MOD?x+y-MOD:x+y;}
long long sub(long long x,long long y){return x>=y?x-y:x+MOD-y;}
 
long long fast_pow(long long b,long long p)
{
	long long ans=1;while(p){if(p&1)ans=ans*b%MOD;b=b*b%MOD;p>>=1;}
	return ans;
}
long long INV(long long x){return fast_pow(x,MOD-2);}
 
long long fac[2000000],invf[2000000];
void init_fac(int n)
{
	fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%MOD;
	invf[n]=INV(fac[n]);for(int i=n-1;i>=0;i--)invf[i]=invf[i+1]*(i+1)%MOD;
}
long long C(int n,int m)
{
	if(n<0||m<0||n<m)return 0;return fac[n]*invf[m]%MOD*invf[n-m]%MOD;
}
 
int cnt[2000000];
 
long long phi[2000000],mu[2000000];
bool prm[2000000];int prm_lst[2000000],prm_cnt;
 
void init_mu(int n)
{
	for(int i=2;i<=n;i++)prm[i]=1;
	mu[1]=1,phi[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(prm[i])prm_lst[++prm_cnt]=i,mu[i]=MOD-1,phi[i]=i-1;
		for(int j=1;j<=prm_cnt&&prm_lst[j]*i<=n;j++)
		{
			int x=prm_lst[j];prm[x*i]=0;
			if(i%x==0)
			{
				mu[i*x]=0;phi[i*x]=phi[i]*x;break;
			}
			mu[i*x]=mu[i]*mu[x]%MOD,phi[i*x]=phi[i]*phi[x];
		}
	}
}
 
long long f[2000000],g[2000000];
int main()
{
	int T=0;scanf("%d",&T);init_fac(1000000),init_mu(1000000);
	while(T--)
	{
		int n=0;scanf("%d",&n);
		for(int i=1;i<=n;i++)cnt[i]=0;int d=0;
		for(int i=1,a=0;i<=n;i++){scanf("%d",&a);cnt[a]++;}
		for(int i=1;i<=n;i++)d=gcd(d,cnt[i]);
		sort(cnt+1,cnt+n+1);reverse(cnt+1,cnt+n+1);
		if(d==n){puts("1");continue;}
		for(int i=1;i<=d;i++)
		{
			f[i]=g[i]=0;
			if(d%i!=0)continue;
			g[i]=fac[n/i];
			for(int j=1;j<=n;j++)
			{
				if(cnt[j]==0)continue;
				
				f[i]=add(f[i],n*C(n/i-2,cnt[j]/i-2)%MOD*INV(C(n/i,cnt[j]/i))%MOD);
				g[i]=g[i]*invf[cnt[j]/i]%MOD;
				//printf("%lld %lld %lld\n",C(n/i-2,cnt[j]/i-2),C(n/i,cnt[j]/i),f[i]);
			}
			f[i]=f[i]*g[i]%MOD;
		}
		//printf("%lld %lld\n",f[1],f[2]);
		//for(int i=1;i<=d;i++)printf("%lld ",phi[i]);puts("");
		long long ans=0,ansg=0;for(int i=1;i<=d;i++)ans=add(ans,phi[i]*f[i]%MOD),ansg=add(ansg,phi[i]*g[i]%MOD);
		ans=ans*INV(ansg)%MOD;
		printf("%lld\n",sub(n,ans));
	}
}
```

----------------------------------

**后记**

其实这题挺无聊的……官方题解用的是 Polya 定理推式子，不过本质上和上面的做法区别不大。而且总感觉类似的数论题已经出过无数遍了……

---

## 作者：happybob (赞：0)

先计算本质不同的环数，用总连通块数除以这个值即为期望。

对本质不同序列计数很容易，考虑每个本质不同的环对应几个序列。不难发现若这个环的最小循环节为 $x$，则对应着 $x$ 个序列，因为你只关心这个环在循环节上的起点。

最小循环节不是很容易，考虑容斥。只需要对于每个 $x$ 求 $x$ 为循环节的序列数量然后容斥即可。

对于连通块总和，考虑若所有数相等，则答案为 $1$。否则对于一个环，连通块数即为 $n - c$，其中 $c$ 为相邻两个相同的边数。

和上面一样考虑对每个 $x$ 求 $x$ 为循环节的联通块数总和，由于每条边本质相同，于是考虑每条边的贡献，枚举 $y$ 表示这条边相邻两个都是 $y$ 的序列数量即可。

复杂度 $O(nd(n))$。

---

## 作者：lfxxx (赞：0)

连通块数量？这怎么做，考虑判掉全部是一种颜色的情况（环）后变为点数减去边数（森林）。

然后考虑期望转方案权值和除以方案数，先思考怎么算方案数。

旋转之后相同的算一个，这又要咋办，不妨先对不同的序列计数，然后我们观察一下一个环会对应多少个序列。

通过观察样例加手搓，不难猜到，一个最小循环节为 $i$ 的环会对应 $i$ 个不同序列。因为其实你只在乎断开的那个循环节是怎么断开的。

最小循环节还是太难做了，不妨设计状态 $p_{i}$ 表示 $\frac{n}{i}$ 是一个循环节的本质不同序列数量，通过容斥不难使得 $p_i$ 变为最小循环节是 $\frac{n}{i}$ 的本质不同序列数量，总方案数就是 $\sum p_i \times \frac{i}{n}$。

那么我们计算方案权值和也可以相仿的做，只需要对于每个 $i$ 求解 $\frac{n}{i}$ 是其的一个循环节的不同序列的边数和即可。

此处考虑转回期望，具体而言，对于循环节为 $x$ 的情况，算出一个循环节内权值和再乘上 $\frac{n}{x}$ 即可，算出权值和考虑每条边出现的概率相加，此处由于所有边等价，所以计算一条边出现的概率即可，不妨令每种颜色的出现次数分别为 $S_1,S_2,\dots,S_k$，概率就是 $\frac{\sum_{i=1}^k {S_i \choose 2} }{n \choose 2}$。

由于只有 $i$ 是所有数的出现次数的因数情况下才需要做上述操作，所以时间复杂度是 $O(n \times d(n))$，其中 $d(n)$ 是 $n$ 以内因数最多的数的因数个数，再加上若干剪枝卡常后可以通过。

[代码](https://codeforces.com/contest/1630/submission/300371313)

---

## 作者：Mashu77 (赞：0)

先考虑没有循环同构条件时的答案。用 
$c_1,c_2,…c_m$
 表示各数值的出现次数，总排列数显然为 
$S=C^{c_1,c_2,...,c_m}_n$。连通块个数等于相邻且不同的元素对数，可以枚举这两个数值 
$x
,
y$
 以及它们的位置，于是总连通块个数为 
$\displaystyle T=\sum_{x\ne y}nC_{n-2}^{c_1,...c_x-1,...,c_y-1,...,c_m}$。答案为 
$\dfrac{T}{
S}$。

再考虑有循环同构条件。解决循环同构的利器是 Burnside 引理，先尝试解决 
$S$。$S
=\dfrac{\sum^n_{i=1}f_i}{n}$，其中 
$f_
i$
 表示旋转 
$i$
 单位时不变的排列个数。稍微做过几道 Burnside 的题目就会知道此时序列被分割为 
$\gcd
(
i
,
n
)$
 个相互独立的环，环上所有元素要求相等。于是 
$f_i=
g_{
\gcd
(
i
,
n
)}$，其中 
$g_i=C^{\frac{c_1}{n/i},...,\frac{c_m}{n/i}}_{i-2}$。

参考上面的思路，枚举 
$x
,
y$
 的值及位置，
$T=\dfrac{\sum^n_{i=1}h_{\gcd(i,n)}}{n}$，其中 
$h_i=\sum\limits_{x\neq y}n\dbinom{i-2}{\frac{c_1}{n/i},\dots,\frac{c_x}{n/i}-1,\dots,\frac{c_y}{n/i}-1,\dots,\frac{c_m}{n/i}}$。注意前面的系数，为什么是 
$n$
 不是 
$i$？因为环上的元素相等，如果 
$a_{
p}$
 与 
$a_{
p
+
1}$
 不相等，$a_{
p
+
i}$
 与 
$a_{
p
+
1
+
i}$
 也不相等。
$ii\times\frac{n}{i}=n$。化一下式子，$h_i=\sum\limits_{x\neq y}\frac{f_ic_xc_yn}{i(i-1)(n/i)^2}$，而 
$∑
c_
x
c_
y$
 易求，于是可以速算。

设枚举了 
$t$
 次 
$i$，复杂度为 
$O
(
t
m
)$。但由于 
$i
|
c_
1
,
c_
2
,
…
c_
m
,
n$，这个值并不大。

于是此题得解。

---

## 作者：MiniLong (赞：0)

##### CF1630E

[题目链接](https://www.luogu.com.cn/problem/CF1630E)

首先特判 $\forall i<n,a_i=a_{i+1}$，答案是 $1$。然后每种序列的价值就是 $n-\sum\limits_{i} [a_i = a_{i+1 \mod n}]$。即 $n$ 减去相邻相同的个数。

因为序列在循环同构下相同即本质相同，所以考虑枚举 **最小周期**。考虑分别计算序列的方案数和相邻相同的和 $f,g$。设 $c_i= \sum\limits_j [a_j =i]$，周期为 $d$，则有 $d|n \and \dfrac{n}{d}| \gcd(c)$，设 $c_i'= \dfrac{c_i}{\frac{n}{d}}$。因为枚举了最小周期了，所以这些数可以任意排列（当然可能出现周期小于它的情况，等会减去即可）。即 $f(d) = \dfrac{d!}{\prod\limits_i (c'_i)!},g(d)=\dfrac{n}{d} \sum\limits_i \dfrac{(m-2)!m}{(\prod\limits_{j \neq i} (c'_j)!) (c_{i} -2)!}$，$g(d)$ 就是枚举哪个数相邻，去掉其中的两个，剩下的排列数。然后开始容斥，设 $f'(d) = f(d) - \sum\limits_{p|d} f'(p),g$ 同理。此时的 $f',g'$ 保证了最小周期是 $d$，所以一种序列会循环同构 $d$ 次算到答案中，所以再将 $f'(d) \leftarrow \dfrac{f'(d)}{d},g'(d) \leftarrow \dfrac{g'(d)}{d}$。答案即 $\dfrac{n(\sum\limits_d f'(d))-\sum\limits_d g'(d)}{\sum\limits_d f'(d)}$。复杂度 $\Theta(n d(n))$，精细实现可以做到 $\Theta(n\log n + n\ln n)$。

---

## 作者：daniEl_lElE (赞：0)

考虑钦定循环节，分成两部分计算：所有方案相邻位置相同的位置数量和方案数。

方案数是容易的，对于每个循环节 $k$ 算出 $\binom{\frac{n}{k}}{\frac{cnt_1}{k},\frac{cnt_2}{k},\dots,\frac{cnt_n}{k}}$。

对于每个循环节，考虑钦定一组相同，答案就是 $\sum_{i=1}^n\binom{\frac{n}{k}-2}{\frac{cnt_1}{k},\frac{cnt_2}{k},\dots,\frac{cnt_i}{k}-2,\dots,\frac{cnt_n}{k}}\times n$，而不同的就用总方案数乘 $n$ 减去这个值即可。

然后跑一遍容斥（或者直接 Burnside 引理）即可。

总复杂度有一个显然的上届 $O(nd(n))$，实际远跑不满，可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
const int mod=998244353;
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) ans=(1ll*ans*a)%mod;
		a=(1ll*a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[3000005],inv[3000005];
void init(){
	fac[0]=1; for(int i=1;i<=3000000;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[3000000]=qp(fac[3000000],mod-2); for(int i=2999999;i>=0;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return 1ll*fac[i]*inv[j]%mod*inv[i-j]%mod;
}
int f[1000005],g[1000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init();
	int t; cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+1],cnt[n+1];
		for(int i=1;i<=n;i++) cnt[i]=f[i]=g[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++) cnt[a[i]]++;
		int gcd=0;
		vector<int> vc;
		for(int i=1;i<=n;i++) gcd=__gcd(gcd,cnt[i]);
		for(int i=1;i<=n;i++) if(cnt[i]) vc.push_back(cnt[i]);
		if(gcd==n){
			cout<<1<<"\n";
			continue;
		}
		for(int i=1;i<=n;i++){
			if(n%i==0) if(gcd%(n/i)==0){
				int tot=1;
				for(auto v:vc){
					(tot*=inv[v/(n/i)])%=mod;
				}
				f[i]=tot*fac[i]%mod;
				for(auto v:vc){
					if(v/(n/i)>=2){ 
						int ttot=tot*fac[v/(n/i)]%mod*inv[v/(n/i)-2]%mod;
						(g[i]+=ttot*fac[i-2])%=mod;
					}
				}
				(g[i]*=n)%=mod;
				g[i]=(f[i]*n%mod+mod-g[i])%mod;
			}
		}
		for(int i=1;i<=n;i++){
			if(n%i==0) if(gcd%(n/i)==0){
				for(int j=i*2;j<=n;j+=i){
					if(n%j==0){
						g[j]=add(g[j],mod-g[i]);
						f[j]=add(f[j],mod-f[i]);
					}
				}
			}
		}
		int t1=0,t2=0;
		for(int i=1;i<=n;i++){
			(t1+=f[i]*qp(i,mod-2))%=mod;
			(t2+=g[i]*qp(i,mod-2))%=mod;
//			cout<<f[i]*qp(i,mod-2)%mod<<" "<<g[i]*qp(i,mod-2)%mod<<"\n";
		}
		cout<<t2*qp(t1,mod-2)%mod<<"\n";
	}
	return 0;
}
```

---

## 作者：intel_core (赞：0)

先考虑怎么算答案。钦定 $a_1=a_2$ 之后算出合法的排列数 $G$，再算出原来合法的排列数 $F$，答案就是 $\frac{nG}{F}$。

再来计算合法排列的数量，显然之和 $\{cnt_x\}$ 有关。枚举排列的最小正周期 $d$，算出周期个数 $\frac{n}{d}$，那么显然 $\frac{n}{d}\mid cnt_i$。

通过简单计算，可以知道周期为 $d$ 的排列数量就是一个组合数，再减掉不合法的即可算出答案。

分析一下复杂度：注意到 $\frac{n}{d}$ 要是 $\gcd(cnt_i)$ 的倍数，而单次计算的复杂度是 $O(k)$，其中 $k$ 是 $cnt_i$ 中不为 0 的数量。而 $d \ge k$，因此复杂度 $O(n\log n)$。

---

## 作者：Leasier (赞：0)

首先判掉 $a_i$ 全部相等的情况，此时答案为 $1$。

答案即为所以本质不同序列中相邻不同项对个数之和除以本质不同序列个数。

------------

对于本质不同序列个数，考虑 Pólya 定理。

枚举置换为 $\{i, i \bmod n + 1, \cdots, (i + n - 2) \bmod n + 1\}$，则有循环节 $\gcd(i, n)$。

设数 $j$ 有 $cnt_j$ 个，则当 $\exists j, \frac{n}{\gcd(i, n)} \nmid cnt_j$ 时不存在任何一种方案。

否则，问题转换为一个长为 $\gcd(i, n)$ 的序列中的可重集排列。

枚举 $d = \gcd(i, n)$，则满足条件的 $i$ 有 $\varphi(\frac{n}{d})$ 个。对每个 $d$ 计算并求和即可。

------------

对于本质不同序列中相邻不同项对个数之和，考虑算贡献。

当 $d > 1$，对于循环节内部出现 $a_i \neq a_{i + 1}$，枚举其为 $a_i = x, a_{i + 1} = y$，则方案数为 $\dfrac{(d - 2)!}{\displaystyle\prod_{i = 1}^n (cnt_i - [i = x \operatorname{or} i = y])!}$，这是容易对每个 $x, y$ 求和的。

当 $1 < d < n$，对于循环节间出现 $a_i \neq a_{i + 1}$，同上计算即可。

------------

综上，我们枚举 $d \mid n$ 求和即可。时间复杂度为 $O(n \tau(n))$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 1e6, mod = 998244353;
int prime[N + 7], phi[N + 7], cnt[N + 7];
ll fac[N + 7], inv_fac[N + 7];
bool p[N + 7];

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = ans * x % mod;
		x = x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline void init1(){
	int cnt = 0;
	p[0] = p[1] = true;
	phi[1] = 1;
	for (register int i = 2; i <= N; i++){
		if (!p[i]){
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= N; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				phi[t] = phi[i] * prime[j];
				break;
			}
			phi[t] = phi[i] * (prime[j] - 1);
		}
	}
	fac[0] = 1;
	for (register int i = 1; i <= N; i++){
		fac[i] = fac[i - 1] * i % mod;
	}
	inv_fac[N] = quick_pow(fac[N], mod - 2, mod);
	for (register int i = N - 1; i >= 0; i--){
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}
}

inline void init2(int n){
	for (register int i = 1; i <= n; i++){
		cnt[i] = 0;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

int main(){
	int t = read();
	init1();
	for (register int i = 1; i <= t; i++){
		int n = read(), m = 0;
		init2(n);
		for (register int j = 1; j <= n; j++){
			int a = read();
			cnt[a]++;
		}
		for (register int j = 1; j <= n; j++){
			if (cnt[j] > 0) cnt[++m] = cnt[j];
		}
		if (cnt[1] == n){
			printf("1\n");
			continue;
		}
		ll x = 0, y = 0;
		for (register int j = 1; j <= n; j++){
			if (n % j == 0){
				int tn = n / j;
				ll p = 1, q = (ll)j * j % mod;
				bool flag = true;
				for (register int k = 1; k <= m; k++){
					if (cnt[k] % tn != 0){
						flag = false;
						break;
					}
					int tcnt = cnt[k] / tn;
					p = p * inv_fac[tcnt] % mod;
					q = ((q - (ll)tcnt * tcnt % mod) % mod + mod) % mod;
				}
				if (!flag) continue;
				q = q * p % mod * n % mod * fac[j - 2] % mod;
				p = p * fac[j] % mod;
				x = (x + p * phi[tn] % mod) % mod;
				y = (y + q * phi[tn] % mod) % mod;
			}
		}
		printf("%lld\n", y * quick_pow(x, mod - 2, mod) % mod);
	}
	return 0;
}
```

---

