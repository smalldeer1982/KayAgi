# Table

## 题目描述

John Doe has an $ n×m $ table. John Doe can paint points in some table cells, not more than one point in one table cell. John Doe wants to use such operations to make each square subtable of size $ n×n $ have exactly $ k $ points.

John Doe wondered, how many distinct ways to fill the table with points are there, provided that the condition must hold. As this number can be rather large, John Doe asks to find its remainder after dividing by $ 1000000007 $ $ (10^{9}+7) $ .

You should assume that John always paints a point exactly in the center of some cell. Two ways to fill a table are considered distinct, if there exists a table cell, that has a point in one way and doesn't have it in the other.

## 说明/提示

Let's consider the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF232B/8876a3223960f71627c5d6c6a4c6ddb988dcaef6.png) The gray area belongs to both $ 5×5 $ squares. So, if it has one point, then there shouldn't be points in any other place. If one of the white areas has a point, then the other one also must have a point. Thus, there are about $ 20 $ variants, where the point lies in the gray area and $ 25 $ variants, where each of the white areas contains a point. Overall there are $ 45 $ variants.

## 样例 #1

### 输入

```
5 6 1
```

### 输出

```
45```

# 题解

## 作者：MCAdam (赞：4)

[题目](https://www.luogu.com.cn/problem/CF232B)

题意：给定一个$n\times m$的矩阵，问使得每一个$n\times n$的矩阵中都有$k$个点的方案数

$1\leq n\leq 100\quad n\leq m\leq 10^{18}\quad 0\leq k\leq n^2$

注意到$m$很大，明显对于所有的列应该是有一个类似等价性的东西，也就是求出前$n$直接得到$m$列的方案

其实就是说，对于$i,j(i\equiv j\pmod n)$，这两列放的点的个数应该是一样的

不妨设$\displaystyle cnt_i=\sum_{j=1}^{m}[j\bmod n=i]$，这个可以直接求出

然后DP求出前$n$列的方案，$f[i][j]$表示前$i$列放了$j$个点的方案数

$\displaystyle f[i][j]=\sum_{t=0}^{\min(j,n)}f[i-1][j-t]\times \binom{n}{t}^{cnt_i}$

这样子复杂度为$O(n^4\log n)$，把后面那一个快速幂预处理一下就好了

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
const int N=110;
const ll mod=1e9+7;
ll C[N][N],fp[N][N],f[N][N*N];
inline ll power(ll a,ll b)
{
	ll res=1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1) res=res*a%mod;
	return res;
}
int main()
{
	for(int i=1;i<=100;i++)
	{
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	int n,k; ll m;
	scanf("%d%lld%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)
			fp[i][j]=power(C[n][j],(m-1)/n+(i<=(m-1)%n+1));
	f[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=min(k,i*n);j++)
			for(int t=0;t<=min(j,n);t++)
				f[i][j]=(f[i][j]+f[i-1][j-t]*fp[i][t]%mod)%mod;
	printf("%lld\n",f[n][k]);
	return 0;
}
```




---

## 作者：ZHR100102 (赞：3)

蒟蒻模拟赛上场切的一道蓝，~~非常难以置信我竟然能做蓝题~~。

这题的数据范围初看还是比较坑的，$10^{18}$ 的值域很容易让人往矩阵加速那方面想。实际上在列出转移方程式后，我们发现状态是二维的，无法使用矩阵加速（或者说这样做很麻烦）。

# 思路

首先观察到每个边长为 $n$ 的正方形的包含的点都一样，可以画出如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/eyipniv3.png)

可以观察到：左边矩形与右边矩形重合的部分为中间灰色部分，它包含的点数记为 $b$，左边黄绿色部分包含的点数记为 $a$，右边黄绿色部分包含的点数记为 $c$。

那么由题目条件可知：

$$a+b=b+c$$

因此可得：

$$a=c$$ 

所以我们可以发现，正方形每往后移动一位，移动前的第一列和移动后的最后一列的点数是一样的。

而本题求的是方案数，对于有 $x$ 个点的一列，其方案数为 $C_{n}^{x}$ 。并且又由于移动前的第一列和移动后的最后一列的点数一样，所以他们的方案数也一样。

如果我们把正方形每次的移动看做把第一列移动到最后一列接上，那么我们可以发现，正方形各列的点数形成了循环节。

于是对于正方形的每一列，我们把它看做一个类型，第 $i$ 列的类型在整张棋盘中的出现次数则为 $\left \lfloor \frac{m}{n} \right \rfloor$，如果 $ (m \bmod n) \ge i$，那么出现次数还会再加 $1$。

接下来的问题就是求把 $k$ 个点分给 $n$ 个列，求出整个问题的总方案数了。

这是个很显然的分组背包，我们把每一列看做一个组，假设这一列在棋盘中出现了 $y$ 次，按照放的点数 $x$ 将列看做物品，其体积即为 $x$，其贡献的方案数即为 $(C_{n}^{x})^y$。

正确时间复杂度为 $O(n^2k)$。

注意优化常数，如果在转移过程中再计算快速幂和组合数那么会导致复杂度变成 $O(n^2k\log n)$，于是我们需要预处理出这部分，才能保证复杂度正确。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
ll n,m,k,ans=0,f[50005],g[50005],dp[50005],p[105][2];
ll qp(ll x,ll y)
{
	ll res=1;
	while(y)
	{
		if(y&1)res=res*x%mod;
		y>>=1;
		x=x*x%mod;
	}
	return res%mod;
}
ll niyuan(ll x)
{
	return qp(x,mod-2);
}
void init()
{
	f[0]=1;
	g[0]=1;
	for(int i=1;i<=10000;i++)
	{
		f[i]=f[i-1]*i%mod;
		g[i]=g[i-1]*niyuan(i)%mod;
	}
}
ll c(ll m,ll n)
{
	return 1ll*f[m]*g[m-n]%mod*g[n]%mod;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n>>m>>k;
	dp[0]=1;
	for(ll i=0;i<=n;i++)
	{
		p[i][0]=qp(c(n,i),m/n);
		p[i][1]=qp(c(n,i),m/n+1);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=k;j>=0;j--)
		{
			int lmt=min(1ll*j,n);
			for(int l=1;l<=lmt;l++)
			{
				ll tmp;
				if((m%n)>=i)tmp=p[l][1];
				else tmp=p[l][0];
				dp[j]=(dp[j]+dp[j-l]*tmp%mod)%mod;	
			}
		}
	}
	cout<<dp[k];
	return 0;
}
```

---

## 作者：feecle6418 (赞：3)

观察到相距为 $n$ 的两列内被涂色的点数一定相同，可以合并计算。将所有与 $i$（$i\le n$）的差为 $n$ 的倍数的 $j$ 称作“与 $i$ 为一个等价类”。设 $p_i$ 为与 $i$ 为同一等价类的个数，可以 $O(1)$ 求出。

设 $f_{i,j}$ 为前 $i$ 列（包括所有与前 $i$ 列的等价类）的涂色方案数，枚举第 $i$ 列涂的点数：

$$\large f_{i,j}=\sum_{k\le \min(j,n)} f_{i-1,j-k} \binom{n}{j}^{p_i}$$

直接计算是 $O(n^4\log m)$ 的无法通过，需要预处理 $w_{i,j}=\binom{n}{j}^{p_i}$。这样，时间复杂度是 $O(n^4)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
int n,f[105][10005]={1},c[105][105]={1},w[105][105],q;
ll m;
int Power(int x,ll y) {
	int ret=1;
	while(y) {
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
int main(){
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=n;j++)w[i][j]=Power(c[n][j],(i<=(m-1)%n+1)?(m-1)/n+1:(m-1)/n);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=min(n,q);j++){
			for(int k=j;k<=q;k++)f[i][k]=(f[i][k]+1ll*w[i][j]*f[i-1][k-j])%mod;
		}
	}
	cout<<f[n][q];
}

```

---

## 作者：zzw4257 (赞：2)

>转化一下题意,给一个$m$长的序列为第$i$个位置填$x$有$\binom{n}{x}$种方案，求使得每个$n$长的子序列和为$K$的方案数

考虑每个$n$长子序列和均为$K$表示$\forall i\in(n,m]$,$i$和$i-n$都相同，那么我们就只需要放前$n$个位置即可

所以设$f_{i,j}$表示前$i$个位置和为$j$的方案数

枚举最后一个位置放的数$k$,对于要求相同的位置都累乘贡献

$$
f_{i,j}=\sum_{k}f_{i-1,j-k}+\binom{n}{k}^{\lfloor\frac{m-i}{n}\rfloor+1}
$$

```cpp
#include<bits/stdc++.h>
#define N 101
#define mod 1000000007
using namespace std;
#define G if(++ip==ie)if(fread(ip=ibuf,1,L,stdin))
const int L=1<<19;
char ibuf[L],*ie=ibuf+L,*ip=ie-1;
inline char nc(void){G;return *ip;}
#define getchar nc
inline int read(void){
	char opt;int flag=1,res=0;
	while((opt=getchar())<'0')if(opt=='-')flag=-1;
	while(opt>='0'){res=(res<<3)+(res<<1)+opt-'0';opt=getchar();}
	return res*flag;
}
typedef long long ll;
int n,K,f[N][N*N],C[N][N];
long long m;
inline int Mod(int x){return x>=mod?x-mod:x;}
inline int qpow(int a,ll b){int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;}
int main(void){
	int i,j,k,res;scanf("%d%lld%d",&n,&m,&K);
	for(C[0][0]=i=1;i<=n;++i)for(*C[i]=j=1;j<=n;++j)C[i][j]=Mod(C[i-1][j]+C[i-1][j-1]);
	for(f[0][0]=i=1;i<=n;++i)
		for(k=0;k<=n;++k)
			for(res=qpow(C[n][k],(m-i)/n+1),j=0;j<=K-k;++j)f[i][j+k]=(f[i][j+k]+1ll*f[i-1][j]*res)%mod;
	printf("%d\n",f[n][K]);
	return 0;
}
/*
100 1000000 5000
*/
```

---

## 作者：ysl_wf (赞：0)

# 【CF232B】Table（补充版）

## 前言

楼中的大佬们讲解的正解，但并未讲解 $cnt_i = \sum\limits_{j=1}^m [j \bmod n = i]$（$i$、$j$ 这两列放的点的个数应该是相同的）的 $O(1)$ 的代码实现是怎么得来的，我的题解则给出了解释（~~也可能是我太蒟蒻了~~）。

## 分析问题

### 题意

有一个 $n\times m$ 的矩阵，求使得每个 $n\times n$ 的矩阵中都有正好 $k$ 个点的方案数，方案数对 $1000000007$（$10 ^ 9 + 7$）取模。  
$1\le n\le100,n\le m\le10^{18},0\le k\le n^2$。

### 分析

通过题目的样例分析，我们可以得出：$m$ 很大，如果我们可以考虑求出前 $n$，从而直接得到 $m$ 列的方案数（因为我们知道前 $n$ 列一定要放 $k$ 个点，所以，只要知道前 $n$ 列的方案数，那么便知道全部的方案数）。

其实也就是找规律，得到：对于 $i$、$j$（$i\equiv j \pmod{n}$），这两列放的点的个数应该是一样的。

然后，我们便可以使用 DP 的思路，求出前 $n$ 列的方案，其中 $f[i][j]$ 表示前 $i$ 列放 $j$ 个点的方案数。

DP 转移方程如下：
$$
f[i][j] = \sum\limits_{t=0}^{\min(j,n)} f[i-1][j-t] \times \dbinom{n}{t} ^ {p_i}
$$

其中，$p_i = \sum\limits_{j=1}^m [j \bmod n = i]$（显然，相同列数的方案数相乘）。

### 问题

1. $p_i = \sum\limits_{j=1}^m [j \bmod n = i]$ 如何 $O(1)$ 计算（$i \in [1,n]$）？

- 暴力枚举的话就是在 $i$ 的基础上每回加 $n$（不超过 $m$）就是 $j$：

$$
\left\lfloor\dfrac{m-i}{j}\right\rfloor + 1
$$

- 高级的（~~笑死，我当时没懂~~）（常数更快一点）：

```cpp
(m-1)/n + (i <= (m-1)%n+1)
```

2. 组合数的计算
  
- 一种 $O(n^2)$ 预处理：

```cpp
for(int i = 1; i <= n; i++){
	C[i][0] = C[i][i] = 1;
	for(int j = 1; j < i; j++)
		C[i][j] = (C[i-1][j] + C[i-1][j-1]) % mod;
}
```

- 一种是 $O(\log n)$ 预处理（两种都可通过）:

```cpp
lt qp(lt a, lt n, lt p){
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b;
}

void cfac(){
    fac[0] = 1 % p;
    for(int i = 1; i <= 220; i++){
        fac[i] = fac[i-1] * i % p;
    }
}

void cifac(){
    ifac[220] = qp(fac[220], p-2, p);
    for(int i = 220 - 1; i >= 0; i--){
        ifac[i] = ifac[i+1] * (i+1) % p;
    }
}

lt C(lt n, lt k){
    if(n < k) return 0;
    return fac[n] * ifac[k] % p * ifac[n-k] % p;
}
```

## Code 
复杂度：$O(n^4)$

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lt;
const lt N = 110, p = 1000000007;
lt n, m, k;
lt fac[N*N], ifac[N*N];
lt fp[N][N], f[N][N*N], cnt[N];

void re_and_wr(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
}

lt qp(lt a, lt n, lt p){
    lt b = 1;
    for(; n; n >>= 1, a = a * a % p)
        if(n & 1) b = b * a % p;
    return b;
}

void cfac(){
    fac[0] = 1 % p;
    for(int i = 1; i <= 220; i++){
        fac[i] = fac[i-1] * i % p;
    }
}

void cifac(){
    ifac[220] = qp(fac[220], p-2, p);
    for(int i = 220 - 1; i >= 0; i--){
        ifac[i] = ifac[i+1] * (i+1) % p;
    }
}

lt C(lt n, lt k){
    if(n < k) return 0;
    return fac[n] * ifac[k] % p * ifac[n-k] % p;
}

int main(){
    // freopen("6.in", "r", stdin);
    // freopen("6.out", "w", stdout);

    re_and_wr();

    cfac(); cifac();

    cin >> n >> m >> k;

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= n; j++){
            fp[i][j] = qp(C(n, j), (m-i)/n+1, p);
        }
    }

    f[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= min(k, i*n); j++){
            for(int t = 0; t <= min((lt)j, n); t++){
                f[i][j] = (f[i][j] + f[i-1][j-t] * fp[i][t] % p) % p; 
            }
        }
    }

    cout << f[n][k];
    return 0;
}
```

---

## 作者：Flyingsnow (赞：0)

## 题面

有一个 $n\times m$的矩阵，求使得每个 $n\times n$的矩阵中都有正好 $k$个点的方案数，方案数对 $1e9+7$ 取模。 $1\le n\le100,n\le m\le10^{18},0\le k\le n^2$。

## 题解

显然，第 $i$ 列的黑点个数等于第 $i+kn$ 列的（$k$ 为正整数，且 $i+kn\le m$ ），但选取的点方案可以不同。

令 $f(i,j)(0\le i \le n)$ 表示前 $i$ 列放了 $j$ 个点，包括其后对应的第 $l+kn(1\le l\le i)$ 列的总方案数。

记 $s=\lfloor{\frac{m}{n}}\rfloor$ ，转移就讨论一下是否有 $i\le m \pmod n$ 。

- 当 $i\le m \pmod n$ 时，$f(i,j)= \sum_{k} f(i-1,j-k) \times (C_{k}^{n}) ^{s+1}$。
- 当 $i > m\pmod n$ 时，$f(i,j)=\sum_{k}f(i-1,j-k) \times (C_{n}^{k})^s$。



---

## 作者：xxx2022 (赞：0)

我们首先可以观察到这道题的 $m$ 很大，所以要考虑这么多列里面是否存在一个性质，让我们求出前 $n$ 列之后快速求出后 $m$ 列的答案。观察一下可以发现第 $i,j$ 两列的答案等价时满足 $i \equiv j \pmod n$。这样的话我们只需要求出前 $n$ 列的答案即可。记 $s_i$ 为这 $m$ 列中答案与第 $i$ 列等价的列数，$f_{i,j}$ 表示前 $i$ 列涂色 $j$ 个格子的方案数，此时显然有一个转移：

$$f_{i,j}=\sum \limits_{p=0}^{\min{(j,n)}}{f_{i-1,j-p} \binom{n}{p}^{s_i}}$$

我们先预处理 $\binom {n}{p}s_i$ 再转移，即可实现在 $O(n^2k)$ 的时间内解决这个问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int n,m,k;
int C[110][110];
int quickpow(int x,int p){
    int ans=1;
    while(p){
        if(p&1) ans=ans*x%mod;
        x=x*x%mod;
        p>>=1;
    }
    return ans;
}
void init(){
    for(int i=1;i<=100;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
        }
    }
}
int pre[110][110];
int f[110][10010];
signed main(){
    init();
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            int key;
            if(m%n==0)  key=m/n;
            else{
                if(i<=m%n)  key=m/n+1;
                else    key=m/n;
            }
            pre[i][j]=quickpow(C[n][j],key);
        }
    }
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=min(i*n,k);j++){
            for(int p=0;p<=min(n,j);p++){
                f[i][j]+=f[i-1][j-p]*pre[i][p];
                f[i][j]%=mod;
            }
        }
    }
    cout<<f[n][k]%mod<<endl;
    return 0;
}
```



---

