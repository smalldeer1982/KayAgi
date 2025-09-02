# [ABC132D] Blue and Red Balls

## 题目描述

有 $K$ 个蓝球和 $N-K$ 个红球。同一颜色的球是完全相同的。Snuke 和 Takahashi 在玩这些球。

首先，Snuke 将把 $N$ 个球从左到右排成一排。

然后，Takahashi 将收走 $K$ 个蓝球。在一次操作中，他可以收走连续的一个区间的蓝球。他将以最少的操作数收走所有蓝球。

Snuke 有多少种排列这 $N$ 个球的方法，使得 Takahashi 恰好操作 $i$ 次才能收走所有的 $K$ 个蓝球？对于每个 $i$（$1\le i\le K$）计算排列数对 $10^9+7$ 取模的结果。

------------

## 说明/提示

#### 样例解释 1
有三种方法来排列球，使得 Takahashi 恰好操作 $1$ 次：$(B, B, B, R, R)$，$(R, B, B, B, R)$ 和 $(R, R, B, B, B)$。（$R$ 和 $B$ 分别代表红色和蓝色）。

有六种方法来排列球，使得 Takahashi 恰好操作 $2$ 次：$(B, B, R, B, R)$，$(B, B, R, R, B)$，$(R, B, B, R, B)$，$(R, B, B, R, B)$，$(B, R, B, B, R)$，和 $(B, R, R, B, B)$。

有一种方法来排列球，使得 Takahashi 恰好操作 $3$ 次：$(B, R, B, R, B)$。

#### 样例解释 2
务必输出对 $10^9+7$ 的排列数。

## 样例 #1

### 输入

```
5 3```

### 输出

```
3
6
1```

## 样例 #2

### 输入

```
2000 3```

### 输出

```
1998
3990006
327341989```

# 题解

## 作者：Limit (赞：9)

# 题目大意

给出一个长度为 $N$ 的01串,其中有 $K$ 个 $1$,其他都是 $0$,需要求出当着 $K$ 个 $1$ 分成 $1$ 到 $K$ 段每一个的方案数.

# 分析

因为需要将这 $K$ 个 $1$ 分成 $i$($1 \leq i \leq K$)段,那自然就会想到[隔板法](https://baike.baidu.com/item/插空法/4862293?fromtitle=隔板法&fromid=3902458&fr=aladdin),那么方案数就是 $C_{K-1}^{i-1}$,要将这 $i$ 段放入长度为 $N-K$ 的 $0$ 串中,在这样一个串中有 $N-K+1$ 个位置可以插入一个串,但是每个位置只可以插入一个串,所以方案数就是 $C_{N-K+1}^{i}$,所以对于分成 $i$ 段的答案就是 $C_{K-1}^{i-1} \times C_{N-K+1}^{i}$.计算组合数只要预处理一下逆元就好了,如果不知道怎么处理可以看看这篇[文章](https://www.cnblogs.com/Sxy_Limit/p/12327199.html#组合数部分会的可以跳过).

# 代码

```cpp
#include<bits/stdc++.h>
#define REP(i,first,last) for(int i=first;i<=last;++i)
#define DOW(i,first,last) for(int i=first;i>=last;--i)
using namespace std;
const int MAXN=1e7+7;
const long long mod=1e9+7;
int N,M;
int K;
long long fac[MAXN];
long long inv[MAXN];
long long Inv(long long a,long long b=mod-2)//普通的一个快速幂
{
	long long result=1;
	while(b)
	{
		if(b&1)
		{
			result*=a;
			result%=mod;
		}
		a*=a;
		a%=mod;
		b/=2;
	}
	return result;
}
long long C(int N,int M)//计算组合数
{
	if(M>N)//需要特判
	{
		return 0;
	}
	if(N==M)
	{
		return 1;
	}
	long long result=fac[N];
	result=(result*inv[N-M])%mod*inv[M];
	return result%mod;
}
int main()
{
	scanf("%d%d",&N,&K);
	fac[1]=1;
	REP(i,2,N+1)//处理阶乘
	{
		fac[i]=fac[i-1]*i;
		fac[i]%=mod;
	}
	inv[N+1]=Inv(fac[N+1]);//处理逆元
	DOW(i,N,0)
	{
		inv[i]=1ll*inv[i+1]*(i+1);
		inv[i]%=mod;
	}
	//我比较喜欢用N,M
	N=N-K;
	M=K;
	REP(i,1,K)
	{
		long long answer=C(N+1,i)*C(M-1,i-1);//直接带公式
		printf("%lld\n",answer%mod);
	}
	return 0;
}
```


---

## 作者：chu_K (赞：4)

首先，我们需要了解一个事实，这个事实对于解决这道题至关重要，那就是，我们如果要去取篮球，那么就得整个区间都取了。

也就是说，如果要取篮球，就得整块整块的取。形式化地说，就是若你要取篮球 $i$ ，且 $j\rightarrow k$ 都是篮球 （$j \le i \le k$），那么就必须取 $j \rightarrow k$的所有篮球。

**证明:** 若取了一个篮球，而多取连续的一个，不会有多花费，那么不取白不取，肯定是取走一块优。

有了这样一个条件，那么"以最少的步数取走篮球" 意思其实是说 "每次取走连续一块篮球"。

所以，只需要看做将红球插入到篮球里就可以了。

易得答案 $C_n^i\times C_{i-1}^{k - 1}$

这怎么会是易得的呢？根本就不易得吧！那么我们就不要易得吧。不易得就要推导，现在我们就来推导一下。

首先，我们有 $n$ 个篮球， $n-k$ 个红球, 要 $i$ 次就是有 $i$ 个连续的块，由我们前面得到的结论，我们如果要去取篮球，那么就得整个区间都取了就可以轻松得到。所以答案就是 $\binom{i}{n} \times \binom{i-1}{k-1}$,是不是特别的有道理。

如果你还是没有明白，那么我们就不要这么直接了，首先，考虑有 $n$ 个球放在那里，然后插入进去红球，就可以得到上式了。

如果数据大点，可以用费马小定理求个逆元然后再求组合数。

核心代码

```cpp
int C(int m, int n) {
    int ans = 1;
    for (int i = 1; i <= m; i++) ans = (ans * (n - m + i) % mod * ksm(i, mod - 2) % mod) % mod;
    return ans;
}
```

---

## 作者：EuphoricStar (赞：3)

简单组合计数。

## 思路

操作 $i$ 次才能收走全部的蓝球，也就是说所有的蓝球被分成了 $i$ 段。

因为有 $N - K$ 个红球，所以有 $N - K + 1$ 个间隔（最前面和最后面都可以放），在这些间隔中选 $i$ 个放蓝球，一共有 $C_{N-K+1}^i$ 种方案。

同时我们还要将总共 $K$ 个蓝球分成 $i$ 段，运用隔板法易得一共有 $C_{K-1}^{i-1}$ 种方案。感性理解一下，$K$ 个蓝球，就有 $K - 1$ 个间隔，选 $i - 1$ 间隔插入一块板子，就可以分成 $i$ 段，因此方案数为 $C_{K-1}^{i-1}$。

最后的答案就是 $C_{N-K+1}^i \times C_{K-1}^{i-1}$，预处理阶乘和阶乘的逆元可以做到 $O(1)$ 计算。

## 代码

```cpp
/*

p_b_p_b txdy
AThousandMoon txdy
AThousandSuns txdy
hxy txdy

*/

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define scd second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int maxn = 2020;
const ll mod = 1000000007;

ll fac[maxn], inv[maxn], n, m;

void prepare() {
	fac[0] = 1;
	for (int i = 1; i <= 2000; ++i) {
		fac[i] = fac[i - 1] * i % mod;
	}
	inv[1] = 1;
	for (int i = 2; i <= 2000; ++i) {
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
	inv[0] = 1;
	for (int i = 1; i <= 2000; ++i) {
		inv[i] = inv[i - 1] * inv[i] % mod;
	}
}

ll C(ll n, ll m) {
	if (n < m) {
		return 0;
	}
	return fac[n] * inv[m] % mod * inv[n - m] % mod;
}

void solve() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; ++i) {
		printf("%lld\n", C(n - m + 1, i) * C(m - 1, i - 1) % mod);
	}
}

int main() {
	prepare();
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：FrozenDream (赞：1)

### 前言：
~~一眼式子，万年 debug。~~
### 思路：
因为蓝球的数量是固定的，题目让我们求，在取 $i$ 次的情况下，有几种方案，首先我们肯定要枚举 $i$，范围就是 $\sum_{i=1}^{k}$ 了，然后因为他每次只能取连续的蓝球，于是我们就可以想到用插板法求把蓝球分成 $i$ 份有多少种情况，也就是求在 $k-1$ 个空中插 $i-1$ 个板子，就是求 ${k-1}\choose{i-1}$，然后我们要把这 $i$ 份蓝球插到 $n-k$ 个红球中，注意这里有一点不一样，红球的两边都可以插蓝球，所以这里就可以转换为在 $n-k+1$ 个空中插 $i$ 个板子，就是求 ${n-k+1}\choose{i}$，那么答案就可以写成 $\sum_{i=1}^{k}{{k-1}\choose{i-1}}{{n-k+1}\choose{i}}$，这个算法的时间复杂度为 $O(n^2+k)$。
### Code:
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,k,mod=1e9+7,c[2005][2005];
void init(){
	for(int i=0;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
		}
	}
}
int main(){
	cin>>n>>k;
	init();
	for(int i=1;i<=k;i++){
		cout<<(c[k-1][i-1]*c[n-k+1][i])%mod<<endl;
	}
}

```


---

## 作者：Mu_leaf (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc132_d)。


## [前言]

我可能是最离谱的歪解了，类似于[放苹果](https://www.luogu.com.cn/problem/P2386)。

## [思路]

因为要将这 $k$ 个固定的蓝球分成 $i$ 段那么此时对答案的贡献就为 $C_{K-1}^{i-1}$。

还要将要将这 $i$ 段放进长度为 $n-k$ 的红球串中，此时对答案的贡献是 $C_{N-K+1}^{i}$。此时总的答案就是 $C_{K-1}^{i-1} \times C_{N-K+1}^{i}$。

### 大白话：

就是每询问一次，进行一次以上计算，此时会超时，于是考虑将一些答案放入答案数组，要用的时候直接调用即可。



------------
## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,b,r;
int f[2005][2005];
const int mod=1e9+7;
int get(int ns,int ms){
	if(ms==1) return 1;//特判。
	if(ns<0) return 0;//特判。
	if(!f[ns][ms]){//如果这个组合情况未被处理过就处理并储存。
		f[ns][ms]=(get(ns-1,ms)+get(ns,ms-1))%mod;
	}
	return f[ns][ms];
}
int main(){
	scanf("%d%d",&n,&b);
	r=n-b;
	for(int i=1;i<=b;i++){
		printf("%lld\n",1ll*get(b-i,i)*get(r-i+1,i+1)%mod);
                //根据组合数求出答案并按要求取模。
	}
	return 0;//快乐结束。
}
```




---

## 作者：liyixi09 (赞：0)

# 题目大意

给出长度为 $N$ 的一排红蓝球，其中有 $K$ 个蓝色球，求被红色球分成 $i$ 段的蓝色球的这样一排红蓝球有多少种。答案对 $10^9+7$ 取模。

------------

# 分析

由于需要把连续的蓝色球分成 $i$ 段，那么可以想到使用数学中的[排列组合](https://oi-wiki.org/math/combinatorics/combination/)。

我们先只将 $N-K$ 个红色球排成一排。在这一排红色球间（包括左右端）选择 $i$ 个地方放入一个蓝色球，那么总共有 $N-K+1$ 个地方放入蓝色球，所以有 $\dbinom{i}{N-K+1}$ 种放置方法。

由于可以在一个地方插入多个蓝色球，那么有 $i-1$ 个“板子”插入由 $k$ 个蓝色球之间的 $k-1$ 个“空”（[插板法](https://oi-wiki.org/math/combinatorics/combination/#%E6%8F%92%E6%9D%BF%E6%B3%95)）。所以还要乘上 $\dbinom{i-1}{K-1}$ 种放置方法。
所以答案的公式为：

$$ans_i = \dbinom{i}{N-K+1} \times \dbinom{i-1}{K-1}$$

但是，一个组合数 $\dbinom{n}{m} = \dfrac{n!}{m!(n-m)!}$ ,如果硬算预处理，就需要逆元。

如果不会逆元怎么办呢？

杨辉三角啊！

在杨辉三角里，第 $i$ 行第 $j$ 列的数是 $\dbinom{j}{i}$ 的值。

这道题的数据范围 $1 \leq K \leq N \leq 2000$ ，显然可以直接开一个二维数组预处理杨辉三角。

所以，我们可以用 $O(N^2)$ 的复杂度预处理杨辉三角，用 $O(1)$ 的复杂度求出每一种 $i$ 的答案。总共复杂度 $O(N^2+K)$ 。

------------

# code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)) {
		if (ch == '-')
			f=-1;
		ch = getchar();
	}
	while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	return x*f;
}
int __stk[100], __tp;
void put(int x) {
	if (x < 0) putchar('-'), x = -x;
	do {
		__stk[++__tp] = x % 10, x /= 10;
	} while (x);
	while (__tp) putchar(__stk[__tp--] + '0');
}
long long a[4005][4005],n,k,mod=1e9+7;
signed main() {
	n=read(),k=read();
	a[0][0]=1;
	for(int i=1; i<=n; i++)
		a[i][0]=1,a[i][i]=1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<i; j++) {
			a[i][j]=(a[i-1][j]+a[i-1][j-1])%mod;
		}
	}
	for(int i=1; i<=k; i++) {
		put((a[n-k+1][i]*a[k-1][i-1])%mod),putchar('\n');
	}
	return 0;
}


```
(记得取模、开 long long 哦）


------------
这是本蒟蒻的第一篇题解，有写的不好的地方请见谅！



---

## 作者：Morax_ (赞：0)

# AT4741 [ABC132D] Blue and Red Balls 题解

非常显然的要用到组合数学。

将 $k$ 个球分成 $i$ 段，很自然的想到了隔板法。

也就是在 $k-1$ 个空格里放 $i-1$ 个板，即 $C_{k-1}^{i-1}$。

那么，再将这 $i$ 段放入一个 $n-k$ 个元素序列中，注意此处在序列两端都能放，即 $C_{n-k+1}^{i}$。

最后，将两数相乘就可以得到答案。

处理组合数的话预处理出逆元和阶乘就行了，但是我在考试的时候为了练习 [Lucas 定理]((https://www.luogu.com.cn/problem/P3807))，所以就写的 Lucas 求组合数。（可能对于这道题有点小题大做了）

### Code:

```c++
#include <stdio.h>

int mod = 1000000007;//模数

long long power (long long a, long long b) {
    long long ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return ans;
}//快速幂

long long C (long long a, long long b) {
    if (a < b) return 0;
    if (a == b) return 1;
    if (b > a - b) b = a - b;
    long long A = 1, B = 1;
    for (long long i = 0; i < b; ++ i) {
        A = A * (a - i) % mod;
        B = B * (b - i) % mod;
    }
    return A % mod * power (B, mod - 2) % mod;
}

long long Lucas (long long a, long long b) {
    if (b == 0) return 1;
    return C (a % mod, b % mod) * Lucas (a / mod, b / mod) % mod;
}//Lucas 板子，详情去看一下模板题

int main () {
    long long n, k;
    scanf ("%lld%lld", &n, &k);
    for (long long i = 1; i <= k; ++ i)
        printf ("%lld\n", Lucas (n - k + 1, i) * Lucas (k - 1, i - 1) % mod);//直接套公式
}
```

---

完！

点个赞吧！

---

## 作者：迟暮天复明 (赞：0)

[可能更好的阅读体验](https://fyc-1358.github.io/fyc_1358/ABC132D_Sol/)

[题目](https://atcoder.jp/contests/abc132/tasks/abc132_d)

数学题。

我要把蓝色球分割成 $i$ 个块，那么红球相应的被分成 $i+1$ 个块。

这样就想到用隔板法。在篮球之间插 $i-1$ 个板，在红球之间插 $i$ 个板。

但是红球的两侧也可以放蓝球，所以我们把红球个数 $+2$ (左右各多放一个)，蓝球放好了以后再去掉。

所以蓝球个数是 $k$ 个，红球个数是 $n-k+2$ 个。

容易得到答案是 $\dbinom{i}{n} \times \dbinom{i-1}{k-1}$。用杨辉三角维护组合数即可。

代码：
```cpp
ll n, k, f[2010][2010], ans;
int main() {
	read(n), read(k);
	f[0][0] = 1;
	rep(i, 1, n) {
		f[i][0] = 1;
		rep(j, 1, i) f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % MOD;
	}
	rep(i, 1, k) print(f[n - k + 1][i] * f[k - 1][i - 1] % MOD), puts("");
	return 0;
}
```

---

