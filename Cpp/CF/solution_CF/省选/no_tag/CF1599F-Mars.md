# Mars

## 题目描述

In the year 2420 humans have finally built a colony on Mars thanks to the work of Elon Tusk. There are $ 10^9+7 $ cities arranged in a circle in this colony and none of them are connected yet. Elon Tusk wants to connect some of those cities using only roads of the same size in order to lower the production cost of those roads. Because of that he gave a list on N cites where some cites can appear more than once and Q queries that you need to answer. For the query you need to determine if it is possible to connect all the cities from $ L_{i} $ to $ R_{i} $ on that list using only roads of length $ D_{i} $ .

## 说明/提示

In the $ 5^{th} $ query of the first test case we can connect cities in this order 0-2-4-6-8-10-12 this way distance between any two connected cities is 2. In the second test case we can connect cities in this order 21-14-7-0 this way distance between any two connected cities is $ 10^9 $ module $ 10^9+7 $ .

## 样例 #1

### 输入

```
9 8
17 0 12 6 10 8 2 4 5
2 3 12
2 3 6
2 4 6
4 6 2
2 8 2
1 2 17
1 8 2
9 9 14```

### 输出

```
Yes
No
Yes
Yes
Yes
Yes
No
Yes```

## 样例 #2

### 输入

```
4 1
7 21 14 0
1 4 1000000000```

### 输出

```
Yes```

# 题解

## 作者：ChuYilin2011 (赞：5)

# [CF1599F](https://www.luogu.com.cn/problem/CF1599F) 题解

## 前言

[P3792](https://www.luogu.com.cn/problem/P3792) 与这道题很类似，感兴趣的可以去做一做。

本人题解大多数通俗易懂，主要供蒟蒻食用，dalao 们不喜勿喷哦~ ~~（其实我也是蒟蒻）~~

声明：数列哈希这条思路不是我本人想出来的，是上课的老师教我的。~~（就我这蒟蒻，这道题能想到哈希？）~~

## 题目大意

有一个序列 $a$，求 $a$ 的一个区间 $\left[l,r\right]$ 能否重排成为一个公差为 $d$ 的等差数列。

## 解题方法

### 必备知识

哈希，快速幂，组合数等。第一个最重要，后面两个主要用来优化。

### 分析

首先，给定这个区间，我们可以求出区间和 $S$。那么，又知道公差 $d$，即可求出，如果该区间满足条件，必有首项
$$a=\dfrac{S-C_n^2d}{n}$$

那么，这个区间“应有的样子”也就知道了。只需判断这个区间“是否是应有的样子”即可。考虑用哈希。

显然，我们要设计的哈希函数 $H$，必须使得对应的序列里元素顺序不影响其函数值，类似交换律。

首先想到的当然是直接累加，即
$$H(l,r)=\sum_{i=l}^ra_i$$

但是这样容易冲突。考虑取每个元素的 $k$ 次方之和。
$$H(l,r)=\sum_{i=l}^ra_i^k$$

这样，问题就解决了，并且还有
$$H(1,r)-H(1,l-1)=H(l,r)$$

所以，我们可以用类似前缀和的方式，求出每个区间实际的哈希值。但还有一个难点在于，如果每次询问都暴力算一遍该区间“应有的样子”的哈希值，那时间复杂度最坏 $O(NQ)$，妥妥 T 飞掉。

考虑等差数列 $\{a,a+d,a+2d,\dots,a+(len-1)d\}$。它对应的哈希值应该是
$$(a+0\cdot d)^k+(a+d)^k+(a+2d)^k+\cdots+\left[a+(len-1)d\right]^k$$

二项式展开得
$$\sum_{i=0}^kC_k^ia^i(0d)^{k-i}+\sum_{i=0}^kC_k^ia^i(1d)^{k-i}+\cdots+\sum_{i=0}^kC_k^ia^i\left[(len-1)d\right]^{k-i}$$

整理得
$$\sum_{j=0}^{len-1}\sum_{i=0}^kC_k^ia^i(jd)^{k-i}$$

交换 $\sum$ 的位置并提公因式
$$\sum_{i=0}^kC_k^ia^id^{k-i}\sum_{j=0}^{len-1}j^{k-i}$$

不难发现，此时，只要预处理组合数 $C$ 与 $\sum_{j=0}^{len-1}j^{k-i}$ 的值就可以了。其余都能用快速幂计算。

所以，设
$$c_{i,j}=\sum_{l=0}^jl^i$$

特别地，$c_{0,0}=1$（这是为了处理 $0^0$ 而特意加上的，否则会有错误）。

那么序列
$$\{a,a+d,a+2d,\dots,a+(len-1)d\}$$

对应的哈希值应该是
$$\sum_{i=0}^kC_k^ia^id^{k-i}c_{k-i,len-1}$$

时间复杂度：

预处理 $c$：$O(Nk)$。

预处理组合数：$O(k)$（这里吐槽一下，别的题解不知道为什么，一定要 $O(k^2)$ 求，直接用公式 $C_n^i=C_n^{i-1}\cdot\dfrac{n-i+1}{i}$ 就行了，$O(k)$ 的复杂度基本可以忽略）。

单次询问：$O(k)$。

总时间复杂度：$O(\ (N+Q)k)$。如果硬是要算上快速幂的时间的话，那就是 $O(\ (N+Q)k\log_2(mod)\ )$，大约再乘个 $20$，~~其实也没必要~~。

## 代码

最终的时间复杂度，就取决于 $k$ 了。这里取 $k=37$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int N=2e5+5;
int qpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=1ll*res*x%mod;
		y>>=1;
		x=1ll*x*x%mod;
	}
	return res;
}
const int K=37;
int C[K+5];//C[i] 表示 C(K,i)
int n,Q,s[N];
int ss[N],c[K+5][N];
int main(){
	scanf("%d%d", &n, &Q);
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i]);
		s[i]=(s[i]+114514)%mod;//防卡技巧之同时加个东西，不影响结果
	}
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		int tmp=1;
		for(int j=0;j<=K;j++,tmp=1ll*tmp*i%mod)
			c[j][i]=(c[j][i-1]+tmp)%mod;
		ss[i]=(ss[i-1]+qpow(s[i],K))%mod;//“前缀哈希和”处理
		s[i]=(s[i]+s[i-1])%mod;//前缀和处理
	}
	C[0]=1;
	for(int i=1;i<=K;i++)
		C[i]=C[i-1]*1ll*(K-i+1)%mod*qpow(i,mod-2)%mod;
	while(Q--){
		int x,y,d;
		scanf("%d%d%d",&x,&y,&d);
		int len=y-x+1,sum=(s[y]-s[x-1]+mod)%mod;
		int st=1ll*(sum-1ll*len*(len-1)/2%mod*d%mod+mod)%mod*qpow(len,mod-2)%mod;
		int res=0;
		for(int i=0;i<=K;i++)
			res=(res+1ll*C[i]*qpow(st,i)%mod*qpow(d,K-i)%mod*c[K-i][len-1]%mod)%mod;
		if(res==(ss[y]-ss[x-1]+mod)%mod) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

经作者亲身试验，可放心食用。

---

## 作者：RAYMOND_7 (赞：2)

给个思路+代码极简的做法。

考虑你知道等差数列的总和，项数，你一定知道等差中项（尽管偶数项时它不实际存在），进而计算出首项。

这样我们可以用一次函数来刻画这个等差数列。

有取模了那考虑哈希，直接计算这个等差数列的 $2, 3$ 次方和，和原数组 check 一下即可。

求 $\sum\limits_{i=1}^n (ki+b)^q$ ，可以二项式定理展开，然后是 $O(1)$ 次自然数平方和和立方和。

如果预处理逆元可以做到线性，但是我懒，所以询问 $O(q \log P)$。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <ctime>

using namespace std;

#define int long long
#define PII pair<int,int>
#define x first
#define y second
#define For(i, l, r) for(int i = l; i <= r; i ++)
#define Rep(i, l, r) for(int i = l; i >= r; i --)

bool START;

void in(int &x)
{
	char c = getchar(); int op = 1;
	while(c > '9' || c < '0') op *= (c == '-' ? -1 : 1), c = getchar();
	for(x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0'; x *= op;
}

const int N = 2e5 + 60, P = 1e9  + 7, i6 = (P + 1) / 6;

int ksm(int x, int y)
{
	int s=1;while(y){if(y&1)s=s*x%P;x=x*x%P;y>>=1;}return s;
}

int n, m, Q, a[N], s1[N], s2[N], s3[N], C[6][6];

int PF(int x){return x * x % P ;}
int LF(int x){return x*x%P*x%P;}

int sum(int n, int k)
{
	if(!k) return n;
	n %= P;
	if(k == 1) return n * (n + 1) / 2 % P;
	if(k == 2) return n * (n + 1) % P * (n + n + 1) % P * i6 % P;
	return PF(n * (n + 1) / 2 % P);
}

int vb[110];
int calc(int k, int b, int n, int q)
{
	int ki = 1, ans = 0; k %= P; b =(b+P-k)%P;
	vb[0] = 1; For(i, 1, q) vb[i]=vb[i-1]*b%P;
	For(p, 0, q) 
	{
		ans = (ans + C[q][p] * ki % P * vb[q-p]%P*sum(n, p))%P;
		ki = ki * k % P;
	}
	return ans;
}

bool ENDPOS = 0;
signed main()
{
	double chu = clock();
	C[0][0] = 1;
	For(i, 1, 5) For(j, 0, i) C[i][j] = (!j?1:C[i-1][j-1]+C[i-1][j])%P;
	in(n);in(m);
	For(i,1,n)in(a[i]),s1[i]=(s1[i-1]+a[i])%P,s2[i]=(s2[i-1]+PF(a[i]))%P,s3[i]=(s3[i-1]+LF(a[i]))%P;
	while(m --)
	{
		int l, r, d; in(l); in(r); in(d);
		int S = (s1[r]+P-s1[l-1])%P;
		int ave = S * ksm(r - l + 1, P-2)%P;
		int L = (ave + P - (P+1)/2*d%P*(r-l))%P;
		int S2=(s2[r]+P-s2[l-1])%P, S3=(s3[r]+P-s3[l-1])%P;
		int P2=calc(d, L, r-l+1,2), P3=calc(d, L, r -l+ 1, 3);
		if(S2 != P2 || S3 != P3) puts("No");
		else puts("Yes");
	}
	cerr << "Time = " << (clock() - chu) / CLOCKS_PER_SEC << endl;
	cerr << (&ENDPOS - &START) * 1.0 / 1024 / 1024 << endl; return 0;
}
//start at 19:08
//finish at 19:24
```

---

## 作者：wmy_goes_to_thu (赞：2)

这题很类似[大母神](https://www.luogu.com.cn/problem/P3792)。

在大母神那题中，有两种做法：

1. 哈希（不确定性）

2. 维护差分的 gcd 值（确定性）

在这题中，加了取模的条件，所以第二种做法就很难了，考虑第一种做法哈希。

怎么知道首项？很容易推得 $a=\dfrac{S-dC_{x}^{2}}{x}$，其中 $x$ 是区间的长度，$S$ 是区间的和，$d$ 是公差。

下一步，我们只要找到一个不依赖于顺序的哈希就可以了，可以选择若干次方和。这里我随了 $3$ 个 $1\sim 50$ 的数。

如果出题人卡你怎么办？把数列每个数加个相同的随机数 $r$ 就完了。

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int a[200005],s[200005],M[1005],S[25][200005];
int L[55][200005],C[105][105];
int powdv(int x,int y)
{
	int ans=1;
	while(y)
	{
		if(y&1)ans=1ll*ans*x%mod;
		y>>=1;
		x=1ll*x*x%mod;
	}
	return ans;
}
int niyuan(int x)
{
	return powdv(x,mod-2);
}
int main()
{
	srand(time(0)+20090908);
	int n,m,r=rand(),T=3,J=50;
	cin>>n>>m;
	for(int i=1;i<=T;i++)M[i]=rand()%J+1;
	for(int i=0;i<=J;i++)
	{
		L[i][0]=powdv(0,i);
		for(int j=1;j<=n;j++)L[i][j]=(L[i][j-1]+powdv(j,i))%mod;
	}
	for(int i=0;i<=J;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		s[i]=(s[i-1]+(a[i]=(a[i]+r)%mod))%mod;
		for(int j=1;j<=T;j++)S[j][i]=(S[j][i-1]+powdv(a[i],M[j]))%mod;
	}
	while(m--)
	{
		int l,r,d;
		scanf("%d%d%d",&l,&r,&d);
		int x=r-l+1,SS=(s[r]-s[l-1])%mod;
		int sx=((SS-1ll*x*(x-1)/2%mod*d)%mod*niyuan(x)%mod+mod)%mod;
		int flag=1;
		for(int j=1;j<=T;j++)
		{
			int k=M[j],he=0;
			for(int l=0;l<=k;l++)
			{
				int SS=1ll*C[k][l]*powdv(d,l)%mod*powdv(sx,k-l)%mod;
				he=(he+1ll*SS*L[l][x-1])%mod;
			}
			if((0ll+he-S[j][r]+S[j][l-1])%mod)
			{
				flag=0;
				break;
			}
		}
		if(flag)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

题意可以转化为询问一个区间是否可以重排为一段模 $P = 10^9 + 7$ 意义下的等差数列。

设等差数列的首项为 $A$，区间长度为 $n$，若我们得到区间内数的和 $S$，那么根据等差数列求和公式：

$$S = n \times A + \dfrac{n\left(n - 1\right)}{2} \times d$$

我们可以得到 $A$ 的表达式：

$$A = \dfrac{S - \dfrac{n\left(n - 1\right)}{2} \times d}{n}$$

既然已经确定了公差，首项和长度，那么我们可以计算出该等差数列的每项的 $k$ 次方和，以达到哈希的目的，再与原区间的 $k$ 次方和比较即可。

考虑如何求出 $k$ 次方和，可以发现其为：

$$\begin{aligned}
\sum\limits_{i = 0}^{n - 1} \left(A + di\right)^k
\end{aligned}$$

可以使用二项式定理展开，得到：

$$\begin{aligned}
&\sum\limits_{i = 0}^{n - 1}\sum\limits_{j = 0}^{k} \dbinom{k}{j} A_{k - j} \left(di\right)^j \\

=&\sum\limits_{j = 0}^{k} \dbinom{k}{j} A^{k - j} d^j\left(\sum\limits_{i = 0}^{n - 1} i^j\right) \\
\end{aligned}$$

$\mathcal{O}(k)$ 计算即可。

---

