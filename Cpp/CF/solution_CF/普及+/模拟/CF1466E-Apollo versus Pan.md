# Apollo versus Pan

## 题目描述

Only a few know that Pan and Apollo weren't only battling for the title of the GOAT musician. A few millenniums later, they also challenged each other in math (or rather in fast calculations). The task they got to solve is the following:

Let $ x_1, x_2, \ldots, x_n $ be the sequence of $ n $ non-negative integers. Find this value: $ $$$\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n (x_i \, \& \, x_j) \cdot (x_j \, | \, x_k) $ $ </p><p>Here  $ \\&amp; $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#AND">bitwise and,</a> and  $ | $  denotes the <a href="https://en.wikipedia.org/wiki/Bitwise_operation#OR">bitwise or.</a></p><p>Pan and Apollo could solve this in a few seconds. Can you do it too? For convenience, find the answer modulo  $ 10^9 + 7$$$.

## 样例 #1

### 输入

```
8
2
1 7
3
1 2 4
4
5 5 5 5
5
6 2 2 1 0
1
0
1
1
6
1 12 123 1234 12345 123456
5
536870912 536870911 1152921504606846975 1152921504606846974 1152921504606846973```

### 输出

```
128
91
1600
505
0
1
502811676
264880351```

# 题解

## 作者：do_while_true (赞：6)

# $\mathcal{Translate}$

[题目链接](https://codeforces.com/contest/1466/problem/E)

给定 $n$ 和长度为 $n$ 的序列 $x$，求下面的式子。

$$
\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n (x_i \, \& \, x_j) \cdot (x_j \, | \, x_k)
$$

$1 \leq n \leq 5 \cdot 10^5,0 \leq x_i < 2^{60}$

# $\mathcal{Solution}$

先交换求和号之后就可以拆位求了。

$$
\sum_{i=1}^n \sum_{j=1}^n \sum_{k=1}^n (x_i \, \& \, x_j) \cdot (x_j \, | \, x_k)
$$

$$
\sum_{j=1}^n \sum_{i=1}^n \sum_{k=1}^n (x_i \, \& \, x_j) \cdot (x_j \, | \, x_k)
$$

$$
\sum_{j=1}^n \sum_{i=1}^n \left((x_i \, \& \, x_j) \cdot \sum_{k=1}^n  (x_j \, | \, x_k)\right)
$$

$$
\sum_{j=1}^n \left(\sum_{i=1}^n (x_i \, \& \, x_j)\right) \cdot \left(\sum_{k=1}^n  (x_j \, | \, x_k)\right)
$$

先拆位预处理后就能快速计算里面两个式子了。

时间复杂度 $\mathcal{O(n\log x_i)}$

# $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#define ll long long
#define re register
#define int long long
inline int Max(int x, int y) { return x > y ? x : y; }
inline int Min(int x, int y) { return x < y ? x : y; }
inline int Abs(int x) { return x < 0 ? ~x + 1 : x; }
inline int read() {
	int r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') w = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		r = (r << 3) + (r << 1) + (ch ^ 48);
		ch = getchar();
	}
	return w ? ~r + 1 : r;
}
#undef int
const int N = 5e5 + 10; 
const ll mod = 1e9 + 7;

int T, n;
ll a[N], sum[N], ans;

signed main() { T = read(); while(T--) {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 0; i <= 60; ++i) sum[i] = 0; ans = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j <= 60; ++j)
			if((1ll << j) & a[i])
				++sum[j];
	}
	for(int i = 1; i <= n; ++i) {
		ll sum1 = 0, sum2 = 0;
		for(int j = 0; j <= 60; ++j) {
			ll ss = (1ll << j) % mod;
			if((1ll << j) & a[i]) sum1 += sum[j] * ss % mod,  sum2 += n * ss % mod;
			else sum2 += sum[j] * ss % mod;
			sum1 %= mod, sum2 %= mod;
		}
		ans = (ans + sum1 * sum2 % mod) % mod;
	}
	printf("%lld\n", ans);
}
	return 0;
}
```

---

## 作者：lnwhl (赞：4)

## Description
给定一个序列 $x_{1},x_{2},\dots,x_{n}$，求 
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{k=1}^n(x_{i}\ \mathsf{and}\ x_{j})\times(x_{j}\ \mathsf{or}\ x_{k})$$
## Solution
观察上式，考虑到两个括号内都含 $x_{j}$，可以将之提出，原式可化为：
$$\sum\limits_{j=1}^n(\sum\limits_{i=1}^n(x_{i}\ \mathsf{and}\ x_{j}))\times(\sum\limits_{k=1}^n(x_{k}\ \mathsf{or}\ x_{j}))$$
穷举每个 $j$，对于每个 $j$ 快速求出 $x_{i}\ \mathsf{and}\ x_{j}$ 和 $x_{k}\ \mathsf{or}\ x_{j}$，对于这个东西我们只需要预处理一下 $\sum\limits_{i=1}^na_{i}$，对于每种情况分别考虑，用桶统计一下即可。复杂度 $O(n\log n)$。
## Code
```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=5e5+5;
const int mod=1e9+7;
int T,n;
ll a[maxn],x[maxn],y[maxn],ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);ans=0;
		for(int i=1;i<=n;++i)
		{
			scanf("%lld",&a[i]);
			x[i]=y[i]=0;
		}
		for(int i=0;i<=60;++i)
		{
			int now=0;
			for(int j=1;j<=n;++j) 
				if((a[j]&(1ll<<i)))
					now++;
			for(int j=1;j<=n;++j) 
			{
				if((a[j]&(1ll<<i))) 
				{
					x[j]+=(1ll<<i)%mod*now%mod;
					x[j]%=mod;
					y[j]+=(1ll<<i)%mod*n%mod;
					y[j]%=mod;
				}
				else 
				{
					y[j]+=(1ll<<i)%mod*now%mod;
					y[j]%=mod;
				}
			}
		} 
		for(int i=1;i<=n;i++)
		{
			ans+=x[i]*y[i]%mod;
			ans%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Eibon (赞：4)

先进行化简。

$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\sum\limits_{k=1}^{n}(x_i \text{ and }x_j) \times (x_j \text{ or } x_k)$

$=\sum\limits_{j=1}^{n}(\sum\limits_{i=1}^{n}(x_i \text{ and } x_j) \times \sum\limits_{k=1}^{n}(x_j \text{ or } x_k))$

我们需要将 $x_i \text{ and } x_j$ 与 $x_i \text{ or } x_j$ 求出。

因为二进制可以进行拆分计算，所以对每一位进行分析。

$i$ 与 $k$ 是等价的，不妨都当做 $i$。

令 $a$ 数组表示 $x_i$ 的二进制每一位。

如果 $a_j$ 是 $1$，则按位与的结果为 $a_i$ 的值，按位或的结果为 $1$。

如果 $a_j$ 是 $0$，则按位与的结果为 $0$，按位或的结果为 $a_i$ 的值。

我们可以对所有 $x_i$ 的 $a_i$ 之和进行预处理统计，得到 $sum_i$。

因为得到的是所有数二进制某一位之和，对于答案的贡献还需乘上当前这一位的权值 $2^{i}$。

最后按照转化的式子运算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e5+5;
const int mod=1e9+7;
int T,n,m,ans,c;
int a[maxn],sum[65];
signed main()
{
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		memset(sum,0,sizeof sum);
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=60;j++){
				if((1ll<<j)&a[i]){
					sum[j]++;
				}
			}
		}
		for(int i=1;i<=n;i++){
			int s1=0,s2=0;
			for(int j=0;j<=60;j++){
				int s=(1ll<<j)%mod;
				if((1ll<<j)&a[i]){
					s1=(s1+sum[j]*s%mod)%mod;
					s2=(s2+n*s%mod)%mod;
				}
				else{
					s2=(s2+sum[j]*s%mod)%mod;
				}
			}
			ans=(ans+s1*s2%mod)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
//dyyyyds
```

---

## 作者：dead_X (赞：4)

## 前言
看到没人写题解水一点经验。

这个 E 怎么比 C 还简单啊 QAQ
## 思路
看到位运算题，先想到拆位，现在假设每个数都是 $0$ 或 $1$。

发现两个式子都和 $j$ 相关，我们考虑对于每个 $j$ 算出 $\sum\limits_{i=1}^n a_i\&a_j$ 和 $\sum\limits_{k=1}^n a_k|a_j$ 的乘积，最后加起来。

这个东西显然非常好求。

$a_j=1$ 的时候 $\sum\limits_{i=1}^n a_i\&a_j=\sum\limits_{i=1}^na_i,\sum\limits_{i=1}^n a_i|a_j=n$。

$a_j=0$ 的时候 $\sum\limits_{i=1}^n a_i\&a_j=0,\sum\limits_{i=1}^n a_i|a_j=\sum\limits_{i=1}^na_i$。

于是我们只需要预处理 $\sum\limits_{i=1}^na_i$ 后计算上方的式子即可。
## 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1000003];
int x[1000003],y[1000003];
const int p=1000000007;
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read();
		for(int i=1; i<=n; i++) a[i]=read(),x[i]=y[i]=0;
		long long ans=0;
		for(int i=0; i<=60; ++i)
		{
			int X=0;
			for(int j=1; j<=n; j++) X+=((a[j]&(1ll<<i))>0);
			for(int j=1; j<=n; j++) 
			{
				if((a[j]&(1ll<<i))>0) x[j]+=(1ll<<i)%p*X%p,x[j]%=p,y[j]+=(1ll<<i)%p*n%p,y[j]%=p;
				else y[j]+=(1ll<<i)%p*X%p,y[j]%=p;
			}
		} 
		for(int i=1; i<=n; i++) ans+=x[i]*y[i]%p,ans%=p;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：3)

## CF1466E 【Apollo versus Pan】

### 题意

+ 给出长度为 $n$ 的序列 $x$；
+ 求 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\sum\limits_{k=1}^{n}(x_i\&x_j)\times(x_j|x_k)\mod(10^9+5)$；
+ 多组数据，$n\le5\times10^5,0\le x_i\le2\times10^{18}$。

### 做法

$\begin{aligned}
&\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\sum\limits_{k=1}^{n}(x_i\&x_j)\times(x_j|x_k)\\
=&\sum\limits_{j=1}^{n}[\sum\limits_{i=1}^{n}(x_i\&x_j)]\times[\sum\limits_{k=1}^{n}(x_j|x_k)]
\end{aligned}$

问题就转化成对于任意 $j$，求 $\sum\limits_{i=1}^{n}(x_i\&x_j)$ 和 $\sum\limits_{k=1}^{n}(x_j|x_k)$。

二进制下每一位显然可以独立计算，现在对任意 $i$，$x_i\in\{0,1\}$。

当 $x_j=1$ 时，$\sum\limits_{i=1}^{n}(x_i\&x_j)=\sum\limits_{i=1}^{n}x_i$，$\sum\limits_{k=1}^{n}(x_j|x_k)=n$。

当 $x_j=0$ 时，$\sum\limits_{i=1}^{n}(x_i\&x_j)=0$，$\sum\limits_{k=1}^{n}(x_j|x_k)=\sum\limits_{i=1}^{n}x_i$。

预处理每一位的 $\sum\limits_{i=1}^{n}x_i$。

---

## 作者：Unordered_OIer (赞：3)

# CF1466E 题解
按位考虑经典题型

## Description
给定 $n$ 和 $x_1,x_2,...,x_n$，求：

$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{k=1}^n(x_i \text{ and }x_j) \times (x_j \text{ or }x_k)$$

其中 $\text{and}$ 为按位与，$\text{or}$ 为按位或。

## Solution
说明：下文将把 $\text{and}$ 写作 $\&$，$\text{or}$ 写作 $|$。

##

我们先把这个式子转化一下：
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^n\sum\limits_{k=1}^n(x_i \text{ and }x_j) \times (x_j \text{ or }x_k)$$

$$=\sum\limits_{j=1}^n(\sum\limits_{i=1}^n(x_i \text{ and }x_j)) \times (\sum\limits_{k=1}^n(x_j \text{ or }x_k))$$

所以我们只要快速求出括号里的两个东西即可。

然后按位考虑，设当前位为第 $i$ 位，$x_j$ 的第 $i$ 位为 $y_j$：
1. 如果 $y_j=1$，那么这位对所有的 $\&$ 都不会改变其结果，对所有的 $|$ 都使结果变为 $1$，即：  
$$\sum\limits_{i=1}^ny_i\&y_j=\sum\limits_{i=1}^ny_i,\sum\limits_{i=1}^ny_j|y_k=\sum\limits_{i=1}^n1=n$$

2. 如果 $y_j=0$，那么这位对所有的 $\&$ 都使结果变为 $0$，对所有的 $|$ 都不会改变其结果，即：
$$\sum\limits_{i=1}^ny_i\&y_j=0,\sum\limits_{i=1}^ny_i|y_j=\sum\limits_{i=1}^ny_i$$

所以预处理 $\sum\limits_{i=1}^ny_i$ 即可。

单次复杂度 $\mathcal O(n \log n)$。

## Code
```cpp
inline ll calc1(ll a,ll b){return a&(1ll<<b);}
inline ll calc2(ll pos,ll q){return (1ll<<pos)%P*q%P;}
...
ll ans=0;
for(ll i=0;i<=60;i++){//枚举当前位
	ll cnt=0;
	for(ll j=1;j<=n;j++)cnt+=(calc1(x[j],i)>0);
	for(ll j=1;j<=n;j++){
		if(calc1(x[j],i))c1[j]=(c1[j]+calc2(i,cnt))%P,c2[j]=(c2[j]+calc2(i,n))%P;
		else c2[j]=(c2[j]+calc2(i,cnt))%P;
	}
}
```

快来和我一起膜拜 [$\mathsf{\color{black}Y\color{red}outhjoy\_Creator}$](https://www.luogu.com.cn/user/278629) 吧！虽然这篇题解除了名字和 T♂A♀ 没有任何关系。

---

## 作者：Plozia (赞：2)

宣传博客->[link](https://blog.csdn.net/BWzhuzehao/article/details/113766515)

本题是一道数学题。

我们首先需要交换一下求和符号，然后利用二进制的性质拆式子即可。

具体过程如下：

$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}\sum\limits_{k=1}^{n}(x_i \text{ and }x_j) \times (x_j \text{ or } x_k)$

$=\sum\limits_{j=1}^{n}\sum\limits_{i=1}^{n}\sum\limits_{k=1}^{n}(x_i \text{ and }x_j) \times (x_j \text{ or } x_k)$

$=\sum\limits_{j=1}^{n}\sum\limits_{i=1}^{n}(x_i \text{ and } x_j) \times \sum\limits_{k=1}^{n}(x_j \text{ or } x_k)$

$=\sum\limits_{j=1}^{n}(\sum\limits_{i=1}^{n}(x_i \text{ and } x_j) \times \sum\limits_{k=1}^{n}(x_j \text{ or } x_k))$

于是我们只需要按二进制位拆分，然后处理即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 5e5 + 10, P = 1e9 + 7;
int t, n;
LL x[MAXN], ans, sum[MAXN];

LL read()
{
	LL sum = 0, fh = 1; char ch = getchar();
	while (ch < '0' || ch > '9')  {if (ch == '-') fh = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {sum = (sum << 3) + (sum << 1) + (ch ^ 48); ch = getchar();}
	return sum * fh;
}

int main()
{
	t = read();
	while (t--)
	{
		n = read(); ans = 0;
		for (int i = 1; i <= n; ++i) x[i] = read();
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 60; ++j)
				if (1ll << j & x[i]) sum[j]++;
		for (int i = 1; i <= n; ++i)
		{
			LL sum1 = 0, sum2 = 0;
			for (int j = 0; j < 60; ++j)
			{
				LL tmp = (1ll << j) % P;
				if (1ll << j & x[i]) sum1 = (sum1 + sum[j] * tmp % P) % P, sum2 = (sum2 + n * tmp) % P;
				else sum2 = (sum2 + sum[j] * tmp) % P;
			}
			ans = (ans + sum1 * sum2 % P) % P;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

