# Girl Permutation

## 题目描述

猜测了一个长度为 $n$ 的排列。

你得到了它的前缀最大值和后缀最大值的下标。

回忆一下，长度为 $k$ 的排列是一个大小为 $k$ 的数组，其中每个整数 $1$ 到 $k$ 恰好出现一次。

前缀最大值是指在以该元素结尾的前缀中最大的元素。更正式地说，若 $a_i > a_j$ 对于所有 $j < i$，则元素 $a_i$ 是前缀最大值。

同理，后缀最大值的定义是：若 $a_i > a_j$ 对于所有 $j > i$，则元素 $a_i$ 是后缀最大值。

你需要输出可能被猜测的不同排列的数量。

由于答案可能非常大，请输出答案对 $10^9 + 7$ 取模后的结果。

## 说明/提示

对于第二组输入数据，满足条件的排列有：

- $[1, 4, 3, 2]$
- $[2, 4, 3, 1]$
- $[3, 4, 2, 1]$

对于第六组输入数据，满足条件的排列有：

- $[2, 1, 6, 5, 3, 4]$
- $[3, 1, 6, 5, 2, 4]$
- $[3, 2, 6, 5, 1, 4]$
- $[4, 1, 6, 5, 2, 3]$
- $[4, 2, 6, 5, 1, 3]$
- $[4, 3, 6, 5, 1, 2]$
- $[5, 1, 6, 4, 2, 3]$
- $[5, 2, 6, 4, 1, 3]$
- $[5, 3, 6, 4, 1, 2]$
- $[5, 4, 6, 3, 1, 2]$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
1 1 1
1
1
4 2 3
1 2
2 3 4
3 3 1
1 2 3
3
5 3 4
1 2 3
2 3 4 5
20 5 4
1 2 3 4 12
12 13 18 20
6 2 3
1 3
3 4 6```

### 输出

```
1
3
1
0
317580808
10```

# 题解

## 作者：Yharimium (赞：17)

题目链接：[CF1946E](https://www.luogu.com.cn/problem/CF1946E)

## 题目大意

一个长度为 $n$ 的排列，**数字 $1\sim n$ 各只出现一次**。分别给出其「前缀最大值」和「后缀最大值」的下标序列 $p$ 和 $s$，问这样的排列有几种。答案对 $10^9+7$ 取模。

- 若 $a_i$ 为「前缀最大值」，则 $a_i$ 是 $a_1\sim a_i$ 的最大值
- 若 $a_i$ 为「后缀最大值」，则 $a_i$ 是 $a_i\sim a_n$ 的最大值

## 观察 0

$a_1$ 必定是「前缀最大值」，$a_n$ 必定是「后缀最大值」。

## 观察 1

山谷中的数不可能是「前缀 / 后缀最大值」。

> 设 $a_{i-1} > a_i < a_{i+1}$，那么
> 
> - $a_i$ 比前一个小，不可能是「前缀最大值」；
> - $a_i$ 比后一个小，不可能是「后缀最大值」。

## 观察 2

若存在这样的排列，则「前缀最大值」的下标序列 和「后缀最大值」的下标序列 有且仅有一个共同值，并且

「前缀最大值」的下标 $\le$「后缀最大值」的下标

> - 若 $a_i$ 是「前缀最大值」，则 $a_i$ 前面都比它小，没有「后缀最大值」；
> - 若 $a_i$ 是「后缀最大值」，则 $a_i$ 后面都比它小，没有「前缀最大值」。
>
> 因此「前缀最大值」都在前面，「后缀最大值」都在后面，并且在中间有且仅有一个数，同时为「前缀 / 后缀最大值」（$p_{m_1}=s_1$）。

将「前缀 / 后缀最大值」写进以下「不等式链」：

$$a[p_1]<a[p_2]<\cdots<a[p_{m_1}]=a[s_1]>a[s_2]>\cdots>a[s_{m_2}]$$

## 观察 3

$a[p_{m_1}]$ $\big(a[s_1]\big)$ 是整个序列中的最大值，也就是 $n$。

> - 根据 **观察 2**，$a[p_{m_1}]$ $\big(a[s_1]\big)$ 首先是「不等式链」中的最大值
> - 根据 **观察 1**，「不等式链」之外的数一定处于山谷，不可能是最大值
>
> 因此 $a[p_{m_1}]$ $\big(a[s_1]\big)$ 一定是总的最大值。

## 解法

首先确定 $a[p_{m_1}]$ 是最大的数 $n$，此时左边还有 $p_{m_1}-1$ 个数代定，右边还有 $n-p_{m_1}$ 个数待定。

将余下的 $n-1$ 个数分为左右两部分，有 ${n-1}\choose{p_{m_1}-1}$ 种方案。

- 同理可以确定 $a[p_{m_1-1}]$ 是左边最大的数
	- 将左边余下的数再二分，有 ${p_{m_1}-2}\choose{p_{m_1-1}-1}$ 种方案。
	- $a[p_{m_1-1}]$ 和 $a[p_{m_1}]$ 之间的数可以任意排列，又有 $(p_{m_1}-p_{m_1-1}-1)!$ 种排列办法。

- 向右也是一样的做法。

一直向左和向右二分，可以得到一系列方案数。

根据乘法原理，将这些数在模意义下相乘，就能得到最终的答案。

---

根据前面的观察，当 $p_1\not=1$ 或 $s_{m_2}\not=n$ 或者 $p_{m_1}\not=s_{1}$ 时，这样的排列不存在，直接输出 $0$。

``` cpp
if (p[1] != 1 || s[m2] != n || p[m1] != s[1]) {
	printf("0\n");
	return;
}

llong res = binomial(n - 1, p[m1] - 1);

for (int i = m1 - 1; i >= 1; i --) {
	res = res * binomial(p[i + 1] - 2, p[i] - 1) % Mod;
	res = res * fac[p[i + 1] - p[i] - 1] % Mod;
}

for (int i = 2; i <= m2; i ++) {
	res = res * binomial(n - s[i - 1] - 1, n - s[i]) % Mod;
	res = res * fac[s[i] - s[i - 1] - 1] % Mod;
}

printf("%lld\n", res);
```

## 代码

``` cpp
#include <bits/stdc++.h>

using namespace std;

/*
0:
a[1] 必为前缀极值，a[n] 必为后缀极值

1:
谷中数非前缀 / 后缀极值
	设 a[i-1] > a[i] < a[i+1]，则
		a[i] 负于前，非前缀极值
		a[i] 负于后，非后缀极值

2:
index of 前缀极值 <= index of 后缀极值
	若 a[i] 为后缀极值，则 a[i] 之后无胜其者，无前缀极值
	前缀后缀互易同理
	故 (index of 前缀极值) 均居前，(index of 后缀极值) 均居后
	有以下不等式链：
		a[p1] < a[p2] < ... < a[p(m1)] = a[s1] > a[s2] > ... > a[s(m2)]

3:
a[p(m1)](a[s1]) = n
	其一，a[p(m1)](a[s1]) = max(不等式链)
	其二，链外数皆谷中数
	故 a[p(m1)](a[s1]) = max(1~n) = n

4:
a[p(m1)] 既定，二分余下 n-1 数，有 binom(n-1, p(m1)-1) 方法
向左:
	a[p(m1-1)] 亦可定，二分余下，有 binom(p(m1)-2, p(m1-1)-1) 方法
	a[p(m1-1)] 与 a[p(m1)] 间任意排列有 (p(m1) - p(m1-1) - 1)! 方法
向右同理 ...
求积
*/

typedef long long llong;

const llong Mod = 1e9 + 7;
const llong N = 1e6 + 1;

llong fac[N], inv[N];

llong binomial(llong n, llong m) {
	if (n < m)
		return 0;
	return fac[n] * inv[m] % Mod * inv[n - m] % Mod;
}

void pretask() {
	fac[0] = fac[1] = 1;
	for (int i = 2; i < N; i ++)
		fac[i] = fac[i - 1] * i % Mod;
	
	inv[0] = inv[1] = 1;
	for (int i = 2; i < N; i ++)
		inv[i] = (Mod - Mod / i) * inv[Mod % i] % Mod;
	for (int i = 2; i < N; i ++)
		inv[i] = inv[i - 1] * inv[i] % Mod;
}

int n, m1, m2;
int p[N], s[N];

void solution() {
	scanf("%d%d%d", &n, &m1, &m2);
	
	for (int i = 1; i <= m1; i ++)
		scanf("%d", &p[i]);
	
	for (int i = 1; i <= m2; i ++)
		scanf("%d", &s[i]);
	
	if (p[1] != 1 || s[m2] != n || p[m1] != s[1]) {
		printf("0\n");
		return;
	}
	
	llong res = binomial(n - 1, p[m1] - 1);
	
	for (int i = m1 - 1; i >= 1; i --) {
		res = res * binomial(p[i + 1] - 2, p[i] - 1) % Mod;
		res = res * fac[p[i + 1] - p[i] - 1] % Mod;
	}
	
	for (int i = 2; i <= m2; i ++) {
		res = res * binomial(n - s[i - 1] - 1, n - s[i]) % Mod;
		res = res * fac[s[i] - s[i - 1] - 1] % Mod;
	}
	
	printf("%lld\n", res);
}

int main() {
	
	pretask();
	
	int t;
	scanf("%d", &t);
	
	while (t --)
		solution();
	
	return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：10)

先判定一些必然条件，$a_1=1,b_{m_2}=n,a_{m_1}=b_1$。然后考虑刻画前缀最大值的要求。建出一棵外向树，$x$ 向 $y$ 连边表示要求 $p_x>p_y$。对于 $a$ 数列，遍历 $i\in[1,m_1)$，$a_{i+1}$ 向 $a_{i}$ 连边，$a_{i}$ 向 $[a_{i}+1,a_{i+1}-1]$ 之间所有数连边；对于 $b$ 数列，遍历 $i\in[1,m_2)$，$b_{i}$ 向 $b_{i+1}$ 连边，$b_{i+1}$ 向 $[b_{i+1}+1,b_i-1]$ 之间所有数连边。然后 $\rm dfs$，求出树上所有点的子树大小 $siz_i$，树的拓扑序个数 $\displaystyle\frac{n!}{\prod_{i=1}^nsiz_i}$ 就是答案。

复杂度 $O(n)$。答案还可以刻画成连续段 $\rm DP$ 的形式，也即若干组合数的乘积。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define MAXN 200005
#define mod 1000000007

const int INF = 1000000000000000000ll;

int fac[MAXN],inv[MAXN],ifac[MAXN];
int n,m1,m2,siz[MAXN],a[MAXN],b[MAXN];
vector<int> E[MAXN];

inline int C( int n , int m ){ return n >= m ? fac[n] * ifac[m] % mod * ifac[n - m] % mod : 0; }
inline int fp( int x , int p ){ int res = 1; while( p ){ if( p & 1 ) res = res * x % mod; x = x * x % mod; p >>= 1; } return res; }

int Ans = 1;
void dfs( int x ){
	siz[x] = 1;
	for( int v : E[x] ) dfs( v ),siz[x] += siz[v];
	Ans = Ans * inv[siz[x]] % mod;
}

inline void solve(){
	scanf("%lld%lld%lld",&n,&m1,&m2);
	for( int i = 1 ; i <= m1 ; i ++ ) scanf("%lld",&a[i]);
	for( int i = 1 ; i <= m2 ; i ++ ) scanf("%lld",&b[i]);
	if( a[m1] != b[1] || a[1] != 1 || b[m2] != n ){ puts("0"); return; }
	for( int i = 1 ; i < m1 ; i ++ ){
		for( int j = a[i] + 1 ; j < a[i + 1] ; j ++ ) E[a[i]].emplace_back( j );
		E[a[i + 1]].emplace_back( a[i] );
	}
	for( int i = m2 ; i > 1 ; i -- ){
		for( int j = b[i] - 1 ; j > b[i - 1] ; j -- ) E[b[i]].emplace_back( j );
		E[b[i - 1]].emplace_back( b[i] );
	}
	Ans = fac[n];
	dfs( a[m1] );
	printf("%lld\n",Ans);
	for( int i = 1 ; i <= n ; i ++ ) E[i].clear();
}

signed main(){
	fac[0] = inv[1] = ifac[0] = 1;
	for( int i = 1 ; i < MAXN ; i ++ ) fac[i] = fac[i - 1] * i % mod;
	for( int i = 2 ; i < MAXN ; i ++ ) inv[i] = ( mod - mod / i ) * inv[mod % i] % mod;
	for( int i = 1 ; i < MAXN ; i ++ ) ifac[i] = ifac[i - 1] * inv[i] % mod;
	int testcase; scanf("%lld",&testcase);
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：FBW2010 (赞：8)

[传送门](https://www.luogu.com.cn/problem/CF1946E)

# 题意

如果 $a_i$ 之前的数都比 $a_i$ 小，那么 $a_i$ 就是一个前缀最大值。后缀最大值同理。现在给出一个序列的每一个前缀与后缀最大值，求有多少种序列。答案模 $10^9+7$。

# 思路 

这题乍一看好像没什么思路，我们可以先从特殊的值来考虑，看能不能发现一些特性。不妨先考虑数列的**最大值**，那么它有几种情况：

+ 如果最大值在 $p_{m1}$ 前，那么 $a_{p_{m1}}$ 一定小于它，这与它是前缀最大值矛盾。

+ 如果最大值在 $p_{m1}$ 后，那么它就一定是前缀最大值，也矛盾。

因此，**最大值一定就在 $p_{m1}$ 上**。同理，**最大值也在 $s_1$ 上**。也就是说，问题要有解，那么就有 $p_{m1}=s_1$。

这时，序列就由 $p_{m1}$ 分成了两半，问题就分成了左右两个**独立的子问题**。因为剩下的 $n-1$ 个数可以随意分到左右两边，所以这里的方案数为 $C_{n-1}^{p_{m1}-1}$。

我们可以先考虑左边部分。用同样的方式，我们又可以得出左半部分的最大值在 $p_{m1-1}$。除去最大值，就还剩下 $p_{m1}-2$ 个数可以塞进 $p_{m1}$ 和 $p_{m1-1}$ 之间。这时的方案数为 $A_{p_{m1}-2}^{p_{m1}-p_{m1-1}-1}$。接着对剩下的又进行类似的操作即可，右半部分也同理。最后把所有的**相乘**即为最终答案。

对于求**组合数**，我们可以通过**预处理阶乘和逆元** $O(1)$ 求出。~~由于本人太蒟了，不会线性求逆元，只好用费马小定理，不过也稳过。~~

除此之外，我们还需要**特判几个无解的情况**。当 $p_1 \ne 1$ 或 $s_{m2} \ne n$ 或 $p_{m1} \ne s_1$ 时，直接输出零。~~本人就这样 WA 过。~~

具体可参考代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long //不开 long long 见祖宗 
const int N=2e5+5,mod=1e9+7;
int t,n,m1,m2,a[N],b[N],sum[N]/*阶乘*/,fsum[N]/*阶乘的逆元*/;
int po(int x,int y){
	if(y==0)return 1;
	if(y==1)return x;
	int p=po(x,y/2);
	if(y%2)return p*p%mod*x%mod;
	return p*p%mod;
}
int C(int x,int y){
	return sum[x]*fsum[x-y]%mod*fsum[y]%mod;
}
int A(int x,int y){
	return sum[x]*fsum[x-y]%mod;
}
signed main(){
	scanf("%lld",&t);
	sum[0]=fsum[0]=1;
	for(int i=1;i<=2e5;i++){
		sum[i]=sum[i-1]*i%mod;
		fsum[i]=po(sum[i],mod-2); //作者太屑只会费马小 
	}
	while(t--){
		scanf("%lld %lld %lld",&n,&m1,&m2);
		for(int i=1;i<=m1;i++){
			scanf("%lld",&a[i]);
		}
		for(int i=1;i<=m2;i++){
			scanf("%lld",&b[i]);
		}
		if(a[m1]!=b[1]||a[1]!=1||b[m2]!=n){ //特判无解 
			printf("0\n");
			continue;
		}
		int ans=C(n-1,a[m1]-1); //分成两半 
		for(int i=m1-1;i>=1;i--){ //左半部分 
			ans*=A(a[i+1]-2,a[i+1]-a[i]-1);
			ans%=mod;
		}
		for(int i=2;i<=m2;i++){ //右半部分 
			ans*=A(n-b[i-1]-1,b[i]-b[i-1]-1);
			ans%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：3)

# Solution

$n$ 所在的位置一定为 $p_x$ 与 $s_1$。故若 $p_x\neq s_1$，方案数为 $0$。

发现以 $p_x$ 为分界线，两边是独立的，故考虑计数将 $1\sim(p_x-1)$ 填入 $[1,p_x)$ 的位置，满足前缀最大值的位置为给定的位置的方案数。

枚举每一个 $i$，考虑填 $[p_i,p_{i+1})$ 的数。显然填完 $p_{i+1}$ 后还剩下 $(p_{i+1}-1)$ 个数，为了保证 $\forall j\in(p_i,p_{i+1}),p_{i}>p_j$，$p_i$ 一定要填剩下的最大的数。剩下 $[1,p_i)$ 的数可以在剩下的数里随便选，方案数为 $\displaystyle\binom{p_{i+1}-2}{p_{i}-1}$。而 $(p_i,p_{i+1})$ 这段数可以随意排列，方案数为 $(p_{i+1}-p_{i}-1)!$。

处理 $s$ 也是对称的。为了方便，可以令 $q_i=n-s_{y-i+1}+1$，然后处理方式和 $p$ 一模一样。

最后，需要将 $[1,n)$ 划分成两个集合分别填入 $[1,p_x),(p_x,n]$，方案数还要再乘上 $\displaystyle\binom{n-1}{p_x-1}$。

故总方案数为：
$$f(p)=\prod_{i=2}^{\lvert p\rvert}(p_{i+1}-p_{i}-1)!\binom{p_{i+1}-2}{p_{i}-1}$$
$$\binom{n-1}{p_x-1}\cdot f(p)\cdot f(q)$$

需要注意特判 $p_1\neq 1$ 或 $q_y\neq n$ 时方案数为 $0$。

# Code

```cpp
// templates ...
int n, x, y, p[N], q[N];
int main() {
	cin >> n >> x >> y;
	REP(i, 1, x) cin >> p[i];
	REP(i, 1, y) cin >> q[i];
	if (p[x] != q[1] || p[1] != 1 || q[y] != n) { cout << "0\n"; return 0; }
	
	REP(i, 1, y) q[i] = n - q[i] + 1;
	reverse(q + 1, q + 1 + y);
	
	Comb<MI> C; C.init(n);
	
	auto solve = [&](int n, int* p) {
		MI rs = 1;
		REP(i, 2, n)
			rs *= C(p[i] - 2, p[i - 1] - 1) * C.fac[p[i] - p[i - 1] - 1];
		return rs;
	};
	
	cout << solve(x, p) * solve(y, q) * C(n - 1, p[x] - 1) << '\n';
	
    return 0;
}
```

---

## 作者：arrow_king (赞：2)

# 题意

有一个长度为 $n$ 的排列，告诉你它前缀后缀 max 的位置，求满足条件的排列数量

# 思路

你考虑dp，由于这是个排列两两不同，可以忽略元素的值，最后再用组合数分配即可。

首先考虑无解：显然如果 $p_1\not=1$或者 $s_{m2}\not=n$或者 $p_{m1}\not=s_1$ 时不存在满足条件的排列。

接下来考虑求值，先考虑前缀最大值（其实两种情况是对称的）。设 $dp_i$ 表示考虑到第 $i$个前缀最大值，并且当前 $[1,i]$ 中放的是 $1$ 到 $i$ 的排列的情况数。（这里可以这么样因为忽略元素大小关系）

然后考虑转移，观察 $dp_i$ 和 $dp_{i-1}$ 关系可得，我从 $dp_{i-1}$ 到 $dp_i$ 首先需要在 $[1,p_i-2]$ 这个区间内选取一些数字塞到 $p_{i-1}$ 和 $p_i$ 中间，这个方案数是 $A_{p_i-2}^{p_i-p_{i-1}-1}$ 的。其次还有 $p_{i-1}$ 对应的可行方案，是 $dp_{i-1}$。$dp_i$ 的答案就是将这两个东西乘起来。

然后你求出了 $dp_{m1}$，按照相似的方式求出后缀的答案 $dp_{m2}$，两个乘起来就是不考虑元素值的答案。

最后考虑元素值，显然除了最大值外都可以随意放，你考虑最大值左边的元素有 $p_{m1}-1$ 个，在 $n-1$ 个里选，将答案再乘上 $\dbinom{n-1}{p_{m1}-1}$ 即可。

时间复杂度 $O(n+m1+m2)$。

# 代码

赛时原汁原味 AC 代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 200005
#define mod 1000000007
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
il ll qpow(ll x,ll y) {
	ll ans=1;
	while(y) {
		if(y&1) ans=(ans*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return ans;
}
ll frac[N],inv[N];
il ll C(ll x,ll y) {
	if(y<x) return 0;
	if(x>y-x) x=y-x;
	return frac[y]*inv[x]%mod*inv[y-x]%mod;
}
il ll A(ll x) {
	return frac[x];
}
ll n,m1,m2,dp[N];
ll p[N],q[N];
int mian() {
	n=read(),m1=read(),m2=read();
	for(int i=1;i<=m1;i++) p[i]=read();
	for(int i=1;i<=m2;i++) q[i]=read();
	if(p[m1]!=q[1]||p[1]!=1||q[m2]!=n) {
		printf("0\n");
		return 0;
	}
	dp[1]=1;
	for(int i=2;i<=m1;i++) dp[i]=dp[i-1]*C(p[i-1]-1,p[i]-2)%mod*A(p[i]-p[i-1]-1)%mod;
	ll ans=dp[m1];
	for(int i=1;i*2<=m2;i++) swap(q[i],q[m2-i+1]);
	for(int i=1;i<=m2;i++) q[i]=n-q[i]+1;
	for(int i=1;i<=m2;i++) dp[i]=0;
	dp[1]=1;
	for(int i=2;i<=m2;i++) {
		dp[i]=dp[i-1]*C(q[i-1]-1,q[i]-2)%mod*A(q[i]-q[i-1]-1)%mod;
	}
	ans=(ans*dp[m2])%mod;
	printf("%lld\n",ans*C(p[m1]-1,n-1)%mod);
	return 0;
}
il void clean() {
	for(int i=1;i<=n;i++) p[i]=q[i]=0;
	for(int i=1;i<=n;i++) dp[i]=0;
	n=m1=m2=0;
}
int main() {
	frac[0]=1;
	for(int i=1;i<=200000;i++) frac[i]=frac[i-1]*i%mod;
	inv[200000]=qpow(frac[200000],mod-2);
	for(int i=199999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	int t=read();
	while(t--) {
		mian();
		clean();
	}
	return 0;
}

```

---

## 作者：Super_Cube (赞：1)

# Solution

首先 $p_1=1$，$s_{m_2}=n$，$p_{m_1}=s_1$ 这三个条件必须满足，否则无解。现在 $a$ 中最大值 $n$ 的位置在 $p_{m_1}$，那么要在剩下 $n-1$ 个数中选 $p_{m_1}-1$ 个数放在最大值左边，方案为 $\displaystyle\binom{n-1}{p_{m_1}-1}$。选出来的这些数其实并不关心它们的实际大小，只在乎它们的相对大小，即它们离散化后的值。所以对于位置 $p_{m_1-1}$ 来说，它在 $p_m$ 左边所以值域范围为 $1\sim p_{m_1}-1$，而它又是这一堆数中的最大值，就是要在 $p_{m_1}-2$ 个数中选 $p_{m_1-1}-1$ 个数放在它左边，而它右边的数可以任意排列，于是方案为 $\displaystyle\binom{p_{m_1}-2}{p_{m_1-1}-1}(p_{m_1}-p_{m_1-1}-1)!$。这个过程每次计算的实质都是统一的，化简过后的答案为 $\displaystyle\prod_{i=1}^{m_1-1}\dfrac{(p_{i+1}-2)!}{(p_i-1)!}$。 $s_1$ 右边的计算同理，与上文类似，不展开讨论，答案为 $\displaystyle\prod_{i=2}^{m_2}\dfrac{(n-s_{i-1}-1)!}{(n-s_i)!}$。

最终答案为：$\displaystyle\binom{n-1}{p_{m_1}-1}\prod_{i=1}^{m_1-1}\frac{(p_{i+1}-2)!}{(p_i-1)!}\prod_{i=2}^{m_2}\frac{(n-s_{i-1}-1)!}{(n-s_i)!}$。

---

## 作者：hh弟中弟 (赞：1)

### [CF1946E Girl Permutation](https://www.luogu.com.cn/problem/CF1946E)
考虑 DP，设 $f_i$ 表示到了第 $i$ 个前缀最大值的位置 $pos_i$，且只用了前 $pos_i$ 个数的方案数。\
考虑一些性质：
- 第 $i$ 个前缀最大值一定是前 $pos_i$ 中最大的数。
- 两个前缀最大值之间的数一定小于这两个值，所以如果要使 $1$ 到 $pos_i$ 合法，那么 $pos_{i-1}$ 一定是前 $pos_i$ 中的次大值。

此时转移就比较显然了，有 $f_i=\operatorname{A}_{pos_i-2}^{pos_{i}-pos_{i-1}-1}\cdot f_{i-1}$，其中 $\operatorname{A}_{pos_i-2}^{pos_i-pos_{i-1}-1}$ 表示在第 $i$ 个前缀最大值和 $i-1$ 个前缀最大值之间插数的方案数，然后直接乘上到第 $i-1$ 个前缀最大值的合法方案数就是 $f_i$。\
考虑这样转移为什么是对的，因为 $f_i$ 表示的是只用了前 $pos_i$ 个数的方案数，所以在转移的时候，针对每一种插数方案，都有一种对应的合法方案在前 $pos_{i-1}$ 个数中，因为离散关系是不变的，所以并不会影响后面的转移。\
对于后缀最大值同样处理，然后两边乘起来后在乘上个 $\operatorname{C}_{n-1}^{pos_{cnt}-1}$（表示分配数）就是答案。
```cpp
#include<bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=2e5+10,mod=1e9+7;
int ny[N],jc[N],a[N],b[N],f[N];
inline int mo(int x){return x<0?(x+mod)%mod:(x>=mod?x%mod:x);}
inline int C(int x,int y){return mo(mo(jc[x]*ny[y])*ny[x-y]);}
inline int A(int x,int y){return mo(jc[x]*ny[x-y]);}
inline void work(){
	int n=read(),c1=read(),c2=read();
	int ans=0;
	for(int i=1;i<=c1;++i)a[i]=read();
	for(int i=c2;i;--i)b[i]=read();
	if(a[c1]!=b[c2]||a[1]!=1||b[1]!=n){std::cout<<0<<'\n';return;}
	f[1]=1;
	for(int i=2;i<=c1;++i)f[i]=mo(f[i-1]*A(a[i]-2,a[i]-a[i-1]-1));
	ans=f[c1];
	c1=c2;
	for(int i=1;i<=c1;++i)a[i]=n-b[i]+1;
	for(int i=2;i<=c1;++i)f[i]=mo(f[i-1]*A(a[i]-2,a[i]-a[i-1]-1));
	ans=mo(mo(ans*f[c1])*C(n-1,a[c1]-1));
	std::cout<<ans<<'\n';
}
signed main(){
	// freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	jc[0]=ny[1]=1;ny[0]=1;
	for(int i=1;i<=2e5;++i)jc[i]=mo(jc[i-1]*i);
	for(int i=2;i<=2e5;++i)ny[i]=mo((mod-mod/i)*ny[mod%i]);
	for(int i=2;i<=2e5;++i)ny[i]=mo(ny[i-1]*ny[i]);
	std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
	int T=read();while(T--)work();
}
```

---

## 作者：pyiming (赞：1)

# Girl Permutation 题解
updata:修改了一部分表述错误
## 题目描述
本题是关于一个长度为 $ n $ 的排列，给出其前缀最大值和后缀最大值的索引，要求计算有多少种可能的排列。
## 思路分析
首先，注意到排列的最后一个前缀最大值和第一个后缀最大值的索引必然相同，并且指向序列中的最大值。如果这个条件不满足（如样例4），那么直接输出 $0$。

接着，我们将序列分为两个部分来考虑：$[1, p_{m1}]$ 和 $[s_1, n]$。

对于区间 $[1, p_{m1}]$，我们可以从1遍历到 $p_{m1}$。如果当前遍历到的数 $i$ 在前缀最大值的索引数组 $p$ 中，则将其放到当前队尾；如果不在 $p$ 中，则可以放到除队尾外的任何一个位置，那就有 $i-1$ 种可以放置的位置，答案就乘以 $i-1$。

同理，我们可以倒序对区间 $[s_1, n]$ 进行相同的操作。

最后，我们需要处理的是两个区间内分别包含哪些数。由于最大的数已经在 $p_{m1}$ 和 $s_1$ 处确定，剩下的 $n-1$ 个数需要被分为两部分，分别位于 $[1, p_{m1}-1]$ 和 $[s_1+1, n]$。这两部分数的组合数是 $C(n-1, p_{m1}-1)$。

因此，最终答案为两个区间的大小关系方案数的乘积再乘以 $C(n-1, p_{m1}-1)$。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=2e5,mod=1e9+7;
ll pow(ll a,ll b,ll p){
    ll ans=1;
    while(b){
        if(b&1)ans=ans*a%p;
        a=a*a%p;
        b>>=1;
    }
    return ans;
}
ll a[N+1];
ll b[N+1];
ll jie[N+1],injie[N+1];
ll C(ll n,ll m){
    return jie[n]*injie[m]%mod*injie[n-m]%mod;
}
int main(){
    jie[0]=1;
    for(ll i=1;i<=N;i++){
        jie[i]=jie[i-1]*i%mod;
    }
    injie[N]=pow(jie[N],mod-2,mod);
    for(ll i=N-1;i>=0;i--){
        injie[i]=injie[i+1]*(i+1)%mod;
    }
    int T; 
    scanf("%d",&T);
    while(T--){
        ll n,m1,m2;
        scanf("%lld%lld%lld",&n,&m1,&m2);
        for(ll i=1;i<=m1;i++){
            scanf("%lld",&a[i]);
        }
        for(ll i=1;i<=m2;i++){
            scanf("%lld",&b[i]);
        }
        if(a[m1]!=b[1]){
            printf("0\n");
            continue;
        }
        ll t1=1;
        for(ll i=1,j=0;i<=a[m1];i++){
            if(a[j+1]==i){
                j++;
                continue;
            }
            t1=(t1*(i-1))%mod;
        }
        ll t2=1;
        for(ll i=n,j=m2+1;i>=b[1];i--){
            if(b[j-1]==i){
                j--;
                continue;
            }
            t2=(t2*(n-i))%mod;
        }
        printf("%lld\n",t1*t2%mod*C(n-1,a[m1]-1)%mod);
    }
    return 0;
}
```
代码中，我们使用了预处理阶乘和逆元的方法来快速计算组合数。这是解决这类问题的常见技巧。

---

## 作者：Rt__ (赞：1)

[CF1946E Girl Permutation](https://www.luogu.com.cn/problem/CF1946E)
## 题意简述
给定一个序列所有**前缀最大值**和**后缀最大值**的下标，求出所有合法序列数。

>设序列为 $a$，若某一前缀最大值的下标为 $x$，说明 $a_x > a_y (y\in [0, x-1])$；同理，若某一后缀最大值为 $x$，说明 $a_x>a_y(y\in [x + 1, n])$。
## 思路
仔细观察样例，我们可以发现，对于每一个前缀 / 后缀最大值，我们都容易找见一段最大区间，使得这段区间的最大值为该最大值。然后如果设这段区间为 $[l, r]$，最大值的位置为 $x$，我们先不考虑顺序，那么该段区间对应的可能情况为 $C_{r-l}^{x-l}$。

如果**左边的子区间**（$[l,x-1]$)没有其他限制，就再将答案乘上 $A_{x-l}^{x-l}$；同理，如果**右边的子区间**（$[x+1,r]$）没有限制，就将答案再乘上 $A_{r-x}^{r-x}$。

运算方法明确了，我们来看怎么实现。首先设前缀最大值为 $fr_i$，后缀最大值为 $ba_i$，那么一定有 $fr_{m1}=ba_{1}$，即为整个区间的最大值。然后分别向左（$fr_{m1}$ -> $fr_1$）和向右（$ba_1$ -> $ba_{m2}$）“压缩”序列。向左压缩时，左边的一定还有另外的限制，右边的一定没有限制；向右压缩时，右边的一定有限制，左边的一定没有限制。以这个规律跟着上面的运算法则算就可以。

另外，不合法：

1.  $fr_1 \ne 1$
2.  $ba_{m2} \ne n$
3.  $fr_{m1}\ne ba_{1}$

~~很显然对吧~~
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 200010, mod = 1000000007;

int ksm(int a, int b){
    int res = 1;
    while(b){
        if(b & 1)res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}
int mul[N], remul[N];
void init(){
    mul[0] = remul[0] = 1;
    for(int i = 1; i <= N - 10; i ++){
        mul[i] = (mul[i - 1] * i) % mod;
        remul[i] = (remul[i - 1] * ksm(i, mod - 2)) % mod;
    }
    return;
}
int C(int a, int b){
    if(a < b)return 0;
    return ((mul[a] * remul[b]) % mod * remul[a - b]) % mod;
}
int A(int a, int b){
    if(a < b)return 0;
    return (mul[a] * remul[a - b]) % mod;
}
int fr[N], ba[N];
signed main(){
    int t;
    cin >> t;
    init();
    while(t --){
        int n, m1, m2;
        cin >> n >> m1 >> m2;
        for(int i = 1; i <= m1; i ++){
            cin >> fr[i];
        }
        for(int i = 1; i <= m2; i ++){
            cin >> ba[i];
        }
        int ans = 1;
        if(fr[m1] != ba[1] || fr[1] != 1 || ba[m2] != n){
            cout << 0 << endl;
            continue;
        }
        ans = (ans * C(n - 1, fr[m1] - 1)) % mod;
        int now = fr[m1] - 1;
        for(int i = m1 - 1; i >= 1; i --){
            ans = (ans * C(now - 1, fr[i] - 1)) % mod;
            now = fr[i] - 1;
        }
        now = n - ba[1];
        for(int i = 2; i <= m2; i ++){
            ans = (ans * C(now - 1, n - ba[i])) % mod;
            now = (n - ba[i]);
        }
        for(int i = m1; i > 1; i --){
            ans = (ans * A(fr[i] - 1 - fr[i - 1], fr[i] - 1 - fr[i - 1])) % mod;
        }
        for(int i = 1; i < m2; i ++){
            ans = (ans * A(ba[i + 1] - 1 - ba[i], ba[i + 1] - 1 - ba[i])) % mod;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：aimcf (赞：0)

题意：

> 有一个长度为 $n$ 的排列，现在给出排列所有的前缀最大值和后缀最大值的位置，问有多少个合法的排列。
>
> $n\le 10^5$，**多测**。

题解：

**结论**：排列存在最大值 $p_i=n$，且 $a_{m_1}=b_1=i$。证明显然。

因此考虑找出位置 $a_{m_1}=b_1$，此时剩余的 $n-1$ 个数将被分为 $[1,b_1)$ 和 $(b_1,n]$ 两个区间。因此考虑选出 $b_1-1$ 个数并将其放到序列的左侧。方案数为 $\binom{n-1}{b_1-1}$。

对于左侧区间 $[1,b_1)$：

此时区间内最大的数显然为 $a_{m_1-1}$。因此确定这个数的位置后继续在序列左右两侧分治即可。特殊的，此时在 $a_{m_1-1}$ 和 $a_{m_1}$ 之间的数没有限制条件，可以任意组合，因此答案还需要乘以 $(a_{m_1}-a_{m_1-1}-1)!$。

右侧区间同理。

因此总的时间复杂度为 $O(\sum n)$，可以简单通过。

---

## 作者：mango2011 (赞：0)

十分简单的题目，不知道大佬们的题解为何如此复杂。

显然，$a_{p_{m_1}}$ 就是整个排列中的最大值，所以 $p_{m_1}$ 应当与 $b_1$ 相等。于是，整个序列就被划分成了左右部分；中间的值就是 $n$。

显然，两个部分互相不影响，所以我们可以选出 $p_{m_1}-1$ 个数给左侧，方案数为 $C_{n-1}^{p_{m_1}-1}$；考虑一段数怎样分配，整个序列一定是形如：ABBBBABBBB....X...BBBBABBBA。其中 A 表示前后缀最大值；X 是整个序列的最大值；B 不是前后缀最大值。

对于右侧的一段区间 $l\sim r$，设其中 $l$ 为前缀最大值；$l+1\sim r$ 都不是前缀最大值。假设我们还有 $t$ 个数可以选，则：

$a_l$ 一定为最大值；$l+1\sim r$ 可以从剩下 $t-1$ 个数中任选 $r-l-1$ 个，于是总得方案数要乘上 $A_{t-1}^{r-l-1}$。

对于右侧的区间我们可以类似讨论，于是最终的答案就出来了。

具体实现的时候可以预处理组合数，然后利用快速幂查询排列组合数，总复杂度 $O(n)$。

**注意特殊情况。**

[评测链接](https://codeforces.com/contest/1946/submission/272893843)

---

## 作者：baka24 (赞：0)

首先，观察得到有解的三个条件：

1. $p_{m1}=s_{1}$，这个位置一定是 $n$。
2. $p_1=1$，这一定。
3. $s_{m2}=n$，同上。

你发现左右不好同时考虑，于是我们考虑左右分开处理。

我们发现题目中只要求了大小关系，所有这些数具体是什么是不重要的，所以我们可以枚举哪些数填到左边，哪些数填到右边。

当然你不可能真的去枚举，你只需要将答案乘上 $C_{n-1}^{p_{m1}-1}$。

然后你就可以分别考虑左右内部的答案了（开心）！，我们拿前缀举例，因为后缀也同理。


观察任意两个前缀最大值之间，我们注意到
![](https://cdn.luogu.com.cn/upload/image_hosting/9i08oh43.png)

红色一定是当前能填的所有数中的最大值，而紫色是次大值。

对于蓝色的部分，我们可以随便填，因为它不会影响其他的部分。

也就是说这一段的贡献是 $A_{p_i-2}^{p_i-p_{i-1}-1}$。

后缀同理，是 $A_{n-s_i+1-2}^{s_{i+1}-s_i-1}$。

#### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=200510,N=30,base=131,Mod=1000000007;
int n,x,y,ans,a[MAXN],b[MAXN],jc[MAXN],ny[MAXN];
//快速幂&&组合数
int Pow(int x,int y){int rt=1;while(y){if(y&1)rt=rt*x%Mod;x=x*x%Mod;y>>=1;}return rt;}
int C(int x,int y){
    return (x<y)?0:jc[x]*ny[x-y]%Mod*ny[y]%Mod;
}
int A(int x,int y){
    return (x<y)?0:jc[x]*ny[x-y]%Mod;
}
void slv(){
    n=read(),x=read(),y=read();
    jc[0]=ny[0]=1;
    for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%Mod,ny[i]=Pow(jc[i],Mod-2);//预处理组合数
    for(int i=1;i<=x;i++)a[i]=read();
    for(int i=1;i<=y;i++)b[i]=read();
    if(a[x]!=b[1]||a[1]!=1||b[y]!=n){//判断无解
        printf("0\n");
        return;
    }
    ans=C(n-1,a[x]-1);//直接算
    for(int i=x;i>1;i--){
        ans*=A(a[i]-2,a[i]-a[i-1]-1);ans%=Mod;
    }
    for(int i=1;i<y;i++){
        ans*=A(n-b[i]+1-2,b[i+1]-b[i]-1);ans%=Mod;
    }
    printf("%lld\n",ans);
}
signed main(){
    int _=read();while(_--)
	slv();
    return 0;
} 	
```

---

## 作者：cqbzlzm (赞：0)

### Description

一个长度为 $n$ 的排列，分别给出这个排列的前缀最大值和后缀最大值位置，求合法的排列个数。

**数据范围：** $n\leq 2\times 10^5$。

### Solution1

我们发现：前/后缀最大值把数组分成了很多块。如图（样例6）。

![](https://pic.imgdb.cn/item/661a4f3c68eb93571355a2a4.png)

显然，3是最大的。3把区间 $[1,6]$ 分成我们看区间 $[1,2]$ 和 $[4,6]$，显然，这一步有 $\binom{6-1}{2}$ 的方案。表示：一共有6个元素，除去最大的一个已经确定的以外，把剩下5个元素分配给左右两边。

下一步，我们求解 $[4,6]$，区间一共有3个数，除了最大的4以外，还有2个数，平均分配给区间 $[4,3]$ 和 $[5,6]$，这一步有 $\binom{3-1}{2}$。然后我们继续缩小问题规模，递归求解。显然，区间里面的数的具体大小与当前区间的答案无关。因此我们不用管具体的分配方案。

另外，对于“山谷”里面的数，交换位置无影响，所以答案再乘一下他们各自的方案。

```cpp
int ans = C(n - 1, a[m1] - 1);
for (int i = m1 - 1; i >= 1; i--) ans = ans * C(a[i + 1] - 2, a[i] - 1) % mod;
for (int i = 2; i <= m2; i++) ans = ans * C(n - b[i - 1] - 1, n - b[i]) % mod;
for (int i = m1 - 1; i >= 1; i--) ans = ans * fac[a[i + 1] - a[i] - 1] % mod;//山谷
for (int i = 2; i <= m2; i++) ans = ans * fac[b[i] - b[i - 1] - 1] % mod;//山谷
```

### Solution2

观察发现，题目中的信息可以刚好表示为 $n-1$ 个大小关系。我们将大连小，便得到一棵树。

如图，我们可以连接5条边：

![](https://pic.imgdb.cn/item/661e35350ea9cb14032ec290.png)

既然得到了一棵树，我们便从根节点开始给每个子节点分配，这里同法1类似。

```cpp
//连边
for (int i = 2; i <= m1; i ++) {
    for (int j = a[i - 1] + 1; j <= a[i] - 1; j ++) G[a[i - 1]].push_back(j);
    G[a[i]].push_back(a[i - 1]);
}
for (int i = 2; i <= m2; i ++) {
    for (int j = b[i - 1] + 1; j <= b[i] - 1; j ++) G[b[i]].push_back(j);
    G[b[i - 1]].push_back(b[i]);
}
//分配
void dfs(int u) {
    sum[u] = 1;
    for (int v : G[u]) {
        dfs(v); 
		sum[u] += sum[v];
        ans = ans * C(sum[u] - 1, sum[v]) % mod;
    }
	return ;
}
```

---

## 作者：yqr123YQR (赞：0)

> 文中的 $A_n^m$ 表示“从 $n$ 个不同物中选 $m$ 个的**排列**数”，$C_n^m$ 表示“从 $n$ 个不同物中选 $m$ 个的**组合**数”。
>
> $A_n^m=\dfrac{n!}{(n-m)!}\\C_n^m=\dfrac{n!}{(n-m)!m!}$
### 题意

分别给定 $n$ 及 $\{a_n\}$ 的前 / 后缀最大值的位置集合，问有多少种符合的 $1\sim n$ 的排列。多组询问。

### 分析

经过简单的思考，有以下结论：

1. $p_1=1,s_{m2}=n$

   显然（应该算是定义）。
2. $a_{p_{m1}}=a_{s_1}=n$

   考虑 $n$ 的位置。由于是排列，所以其余的数自然比 $n$ 小，$n$ 也就同时是前缀、后缀最大值。而在 $n$ 之后，不可能有其他数比它大。也就是说，$n$ 的位置即为最后一个前缀最大值与第一个后缀最大值的位置。
3. 一个局部也可以当成排列考虑

   我们只需考虑相对大小，则这些数均可直接映射至一个排列，自然可以当成排列考虑。

由此，我们可以得到思路：

首先特判无解：`p[m1] != s[1] || p[1] != 1 || s[m2] != N`。

下面考虑求解方案数：

现在已知 $n$ 的位置 $s_1$，则右边的数只需要符合 $s$ 的限制，左边的数只需考虑 $p$ 的限制。设 $f(i,j)$ 表示 $[1,i]$ 序列中，满足限制 $p_{1\sim j}$ 的 $1\sim i$ 排列数，$g(i,j)$ 表示 $[i,n]$ 序列中，满足限制 $s_{j\sim m2}$ 的排列数。此处只考虑 $f$。

对于 $f(i,j)$，类似开头的方式，最大的数位置就是 $p_j$。所以 $[p_j+1,i]$ 的数可从 $[1,i-1]$ 中任取，而且顺序也任意（因为不影响 $p$ 序列），故共有 $A_{i-1}^{i-p_j}$ 种；左边剩余部分则转化为 $f(p_j-1,j-1)$ 所描述的。两边一乘，得到 $f(i,j)=A_{i-1}^{i-p_j}f(p_j-1,j-1)$，其中 $f(0,0)=1$。

$g$ 同理。又因为 $s_1$ 左右两部分的数可以在 $1\sim n$ 中任取，最后的答案即为 $C_{n-1}^{s_1-1}f(s_1-1,m1-1)g(s_1+1,2)$。

~~阶乘、阶乘的逆元应该都会~~

### 代码
```cpp
#include<stdio.h>
#include<ctype.h>
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 200000, mod = 1e9 + 7;
namespace IO {
	const int bufsize = 230005;
	static char obuf[bufsize], *p3 = obuf, *p4 = obuf + bufsize;
	char gtchar()
	{
		static char buf[bufsize], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufsize, stdin), p1 == p2)? EOF: *p1++;
	}
	void flush() {fwrite(obuf, 1, p3 - obuf, stdout), p3 = obuf;}
	void ptchar(char ch)
	{
		if(p3 == p4) flush();
		*p3++ = ch;
	}
	void write(ll x)
	{
		if(x < 0) ptchar('-'), x = -x;
		if(x > 9) write(x / 10);
		ptchar(x - x / 10 * 10 ^ 48);
	}
	ll read()
	{
		ll ret = 0;
		char ch = gtchar();
		bool f = false;
		while(!isdigit(ch)) f = ch == '-', ch = gtchar();
		while(isdigit(ch)) ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
		return f? -ret: ret;
	}
}
using IO::read;
using IO::write;
int T, N, m1, m2, p[maxn + 5], s[maxn + 5];
ll fac[maxn + 5], rfac[maxn + 5];
ll A(int n, int m) {return n < m? 0: fac[n] * rfac[n - m] % mod;}
ll C(int n, int m) {return n < m? 0: fac[n] * rfac[n - m] % mod * rfac[m] % mod;}
ll f(int n, int m)//1 to n,s_1 to s_m
{
	if(!m) return 1;//边界（因为 m 到 0 时，n 必然同时到 0，只用判其中一个即可）
	return A(n - 1, n - p[m]) * f(p[m] - 1, m - 1) % mod;
}
ll g(int n, int m)//n to N,s_m to s_m2
{
	if(m > m2) return 1;
	return A(N - n, s[m] - n) * g(s[m] + 1, m + 1) % mod;
}
int main()
{
	//预处理⬇
	fac[0] = fac[1] = rfac[0] = rfac[1] = 1;
	for(int i = 2; i <= maxn; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
		rfac[i] = (mod - mod / i) * rfac[mod % i] % mod;
	}
	for(int i = 2; i <= maxn; i++) rfac[i] = rfac[i] * rfac[i - 1] % mod;
	T = read();
	while(T--)
	{
		N = read(), m1 = read(), m2 = read();
		for(int i = 1; i <= m1; i++) p[i] = read();
		for(int i = 1; i <= m2; i++) s[i] = read();
		if(p[m1] != s[1] || p[1] != 1 || s[m2] != N)//判存在性
		{
			IO::ptchar('0'), IO::ptchar('\n');
			continue;
		}
		int pos = s[1];
		write(C(N - 1, pos - 1) * f(pos - 1, m1 - 1) % mod * g(pos + 1, 2) % mod), IO::ptchar('\n');
	}
	IO::flush();
	return 0;
}
```

---

