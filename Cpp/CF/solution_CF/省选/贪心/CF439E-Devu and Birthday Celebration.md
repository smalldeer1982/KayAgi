# Devu and Birthday Celebration

## 题目描述

Today is Devu's birthday. For celebrating the occasion, he bought $ n $ sweets from the nearby market. He has invited his $ f $ friends. He would like to distribute the sweets among them. As he is a nice guy and the occasion is great, he doesn't want any friend to be sad, so he would ensure to give at least one sweet to each friend.

He wants to celebrate it in a unique style, so he would like to ensure following condition for the distribution of sweets. Assume that he has distributed $ n $ sweets to his friends such that $ i^{th} $ friend is given $ a_{i} $ sweets. He wants to make sure that there should not be any positive integer $ x&gt;1 $ , which divides every $ a_{i} $ .

Please find the number of ways he can distribute sweets to his friends in the required way. Note that the order of distribution is important, for example \[1, 2\] and \[2, 1\] are distinct distributions. As the answer could be very large, output answer modulo $ 1000000007 $ $ (10^{9}+7) $ .

To make the problem more interesting, you are given $ q $ queries. Each query contains an $ n $ , $ f $ pair. For each query please output the required number of ways modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

For first query: $ n=6,f=2 $ . Possible partitions are \[1, 5\] and \[5, 1\].

For second query: $ n=7,f=2 $ . Possible partitions are \[1, 6\] and \[2, 5\] and \[3, 4\] and \[4, 3\] and \[5, 3\] and \[6, 1\]. So in total there are 6 possible ways of partitioning.

## 样例 #1

### 输入

```
5
6 2
7 2
6 3
6 4
7 4
```

### 输出

```
2
6
9
10
20
```

# 题解

## 作者：szh_AK_all (赞：5)

### 前言
思路与[这篇题解](https://www.luogu.com.cn/article/u0pkm9t7)差不多，但这里会具体解释计算过程。

### 分析
使用容斥原理，题目的要求分为两点：

- $\sum_{i=1}^f a_i=n$。

-  $\gcd(a_1,a_2\dots a_f)=1$。

显然，第一点要求是容易满足的，所以可以根据第二点要求来容斥。

先来一个前置知识：满足 $\sum_{i=1}^n x_i=m$ 且 $x_i$ 为自然数的解的个数为 $C_{n+m-1}^{m-1}$（写成 $C_{n+m-1}^{n-1}$ 是一样的），这个结论可以根据隔板法得出。

再来看这题，先不管第二个条件是否满足，计算出满足第一个条件的解的数量。也就是要求出满足 $\sum_{i-1}^f x_i=n$ 且 $x_i\ge1$ 的正整数解的数量，将 $x_i\ge1$ 装换一下得到 $x_i-1\ge 0$，再设 $y_i=x_i-1$，则可以将原问题转换为求 $\sum_{i=1}^f y_i=n-f$ 且 $y_i$ 为自然数的解的个数，观察下前置知识，可以得到解的个数为 $C_{f+n-f-1}^{f-1}$，也即 $C_{n-1}^{f-1}$。可以理解为这是容斥的全集 $|S|$ 的大小。

接着，考虑第二个条件，容斥的一般思路是正难则反，既然很难求出满足 $\gcd(a_1,a_2\dots a_f)=1$ 的解的个数，那么可以考虑求出满足 $\gcd(a_1,a_2\dots a_f)\ne1$ 的解的个数。具体的，设 $|S_l|$ 表示 $\gcd(a_1,a_2\dots a_f)$ 为 $l$ 的倍数的解的个数，那么如何求 $|S_l|$ 呢？

观察一下，既然要满足 $\gcd(a_1,a_2\dots a_f)$ 为 $l$ 的倍数，也就是所有的 $a_i$ 都为 $l$ 的倍数，那么 $n=\sum_{i=1}^f a_i$ 也应该是 $l$ 的倍数。设 $k=\frac{n}{l}$，则说明可以把 $n$ 这个数分成 $k$ 份 $l$，而应该将这 $k$ 份 $l$ 分给这些 $a_i$，并且由于 $a_i$ 都是正整数，所以每个 $a_i$ 分到的份数也应该是正整数。那么这又可以转换成求解 $\sum_{i=1}^f x_i=k$ 且 $x_i\ge1$ 的正整数解的个数，设 $y_i=x_i-1$，则可以将原问题转换为求 $\sum_{i=1}^f y_i=k-f$ 且 $y_i$ 为自然数的解的个数，观察下前置知识，可以得到解的个数为 $C_{f+k-f-1}^{f-1}$，也即 $C_{k-1}^{f-1}$。这说明 $|S_l|=C_{\frac{n}{l}-1}^{f-1}$。

算出了单个的 $|S_l|$ 的大小，再来看看 $|S_{l_1}\bigcap S_{l_2}|$ 的大小。根据定义可知，$|S_{l_1}\bigcap S_{l_2}|$ 代表满足 $\gcd(a_1,a_2\dots a_f)$ 既是 $l_1$ 的倍数，又是 $l_2$ 的倍数的解的个数。假设 $l_1,l_2$ 不互质，则这两个数本身就有相同的因子，所以在计算的时候处理起来比较麻烦，所以，应将所有的 $l_i$ 定为质数，一来如果是合数的话则所有情况不一定能全部覆盖，二来计算起来更加方便。

那么当 $l_1,l_2$ 互质时，$|S_{l_1}\bigcap S_{l_2}|$ 即为 $|S_{l_1\times l_2}|$，计算方法同计算 $|S_l|$ 的方法。

最终答案即为 $|S|-\sum_{k=1}^m (-1)^{k+1}|S_{l_1}\bigcap S_{l_2} \bigcap \dots \bigcap S_{l_k}|(l_1<l_2<\dots<l_k)$。

由于 $n$ 不超过 $10^5$，所以容斥时 $l_i$ 的乘积也无需超过 $10^5$，所以 $k$ 的上界 $m$ 不会很大，可以暴力容斥。

一些细节看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1e9 + 7;
int jie[100005], inv[100005];
int pri[100005], vis[100005], tot;
int t[100005];

int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b % 2 == 1)
			ans = ans * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return ans % mod;
}

int C(int n, int m) {
	return jie[n] * inv[n - m] % mod * inv[m] % mod;
}

signed main() {
	int q;
	cin >> q;
	jie[0] = inv[0] = 1;
	for (int i = 1; i <= 100000; i++) {//预处理阶乘及阶乘的逆元，用于计算组合数
		jie[i] = jie[i - 1] * i % mod;
		inv[i] = qpow(jie[i], mod - 2);
	}
	for (int i = 2; i <= 100000; i++) {//素数筛
		if (!vis[i])
			pri[++tot] = i;
		for (int j = 1; j <= tot && i * pri[j] <= 100000; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0)
				break;
		}
	}
	for (int a = 1; a <= tot; a++) {//m不超过6，所以可以6重循环枚举l[i]的乘积
		t[pri[a]] = 1;
		for (int b = a + 1; b <= tot && pri[a]*pri[b] <= 100000; b++) {
			t[pri[a] * pri[b]] = 1;
			for (int c = b + 1; c <= tot && pri[a]*pri[b]*pri[c] <= 100000; c++) {
				t[pri[a] * pri[b] * pri[c]] = 1;
				for (int d = c + 1; d <= tot && pri[a]*pri[b]*pri[c]*pri[d] <= 100000; d++) {
					t[pri[a] * pri[b] * pri[c] * pri[d]] = 1;
					for (int e = d + 1; e <= tot && pri[a] * pri[b] * pri[c] * pri[d] * pri[e] <= 100000; e++) {
						t[pri[a] * pri[b] * pri[c] * pri[d] * pri[e]] = 1;
						for (int f = e + 1; f <= tot && pri[a] * pri[b] * pri[c] * pri[d] * pri[e]*pri[f] <= 100000; f++) {
							t[pri[a] * pri[b] * pri[c] * pri[d] * pri[e]*pri[f]] = 1;
						}
					}
				}
			}
		}
	}
	while (q--) {
		int n, f;
		cin >> n >> f;
		int ans = C(n - 1, f - 1);
		for (int i = 1; i * i <= n; i++) {//枚举因子，容斥
			if (n % i == 0 && t[i] && n / i >= f) {
				if (t[i] % 2 == 1)//因子i
					ans -= C(n / i - 1, f - 1), ans = (ans % mod + mod) % mod;
				if (t[i] % 2 == 0)
					ans += C(n / i - 1, f - 1), ans %= mod;
			}
			if (n % i == 0 && t[n / i] && i * i != n && i >= f) {//因子n/i
				if (t[n / i] % 2 == 1)
					ans -= C(i - 1, f - 1), ans = (ans % mod + mod) % mod;
				if (t[n / i] % 2 == 0)
					ans += C(i - 1, f - 1), ans %= mod;
			}
		}
		cout << ans << endl;
	}
}
```

---

## 作者：EDqwq (赞：4)

题目即是让你求：

$\sum_{a_1 = 1}^n\sum_{a_2 = 1}^n\cdots\sum_{a_f=1}^n[\gcd(a_1,a_2,\cdots,a_f) = 1][a_1 + a_2 + \cdots + a_f = n]$

我们此处简化为讨论两个数。

$\sum_{i = 1}^n\sum_{j = 1}^n[\gcd(i,j) = 1][i + j = n]$

把 $\gcd = 1$ 拆掉：

$\sum_{i = 1}^n\sum_{j = 1}^n\sum_{d|\gcd(i,j)} \mu(d) [i + j = n]$

套路，改为枚举倍数：

$\sum_{d = 1}^n\mu(d)\sum_{i = 1}^{\frac{n}{d}}\sum_{j = 1}^{\frac{n}{d}}[i + j = \frac{n}{d}]$

首先，序列里的数都是整数，所以 $\frac{n}{d}$ 一定为整数，那么 $d$ 必然是 $n$ 的因数，于是我们可以根号枚举因数。

然后，要算出有多少种构造序列的方法，使得所有数的和为 $\frac{n}{d}$。

小学奥数内容，插板法，相当于有 $\frac{n}{d}$ 个 $1$ ，在中间插板，每一种不同的插板的位置显然对应不同的分解方式，并且和一定。

$\frac{n}{d}$ 个 $1$ ，有 $\frac{n}{d} - 1$  个空间（不可以为 0 ），要插 $f - 1$ 块板（分成 $f$ 块），显然是组合数。

于是枚举因数，对于每个因数叠加组合数即可。

```cpp
#include<bits/stdc++.h>

#define int long long
#define mem(x,y) memset(x,y,sizeof(x))
#define frein freopen("in.in","r",stdin)
#define freout freopen("out.out","w",stdout)
#define debug(x) cout << (#x) << " = " << x << endl;

using namespace std;

int read(){
   int s = 0,w = 1;
   char ch = getchar();
   while(ch < '0' || ch > '9'){if(ch == '-')w = -1;ch = getchar();}
   while(ch >= '0' && ch <= '9')s = s * 10 + ch - '0',ch = getchar();
   return s * w;
}

int t;
int n,m;
bool isprime[1000010];
int prime[1000010];
int cnt;
int mu[1000010];
int fac[1000010];
int inv[1000010];
int finv[1000010];
const int mod = 1e9 + 7;

void init(){
	n = 100000;
	fac[0] = fac[1] = inv[1] = finv[1] = inv[0] = finv[0] = 1;
	for(int i = 2;i <= n;i ++){
		fac[i] = (fac[i - 1] * i) % mod;
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	}
	for(int i = 2;i <= n;i ++)finv[i] = (finv[i - 1] * inv[i]) % mod;
	mu[1] = 1;
	for(int i = 2;i <= n;i ++){
		if(!isprime[i]){
			prime[++ cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1;j <= cnt && i * prime[j] <= n;j ++){
			isprime[i * prime[j]] = true;
			if(i % prime[j])mu[i * prime[j]] = -mu[i];
			else break;
		}
	}
}

int C(int x,int y){
	if(x > y)return 0;
	return fac[y] * finv[y - x] % mod * finv[x] % mod;
}

signed main(){
	init();
	cin>>t;
	while(t --){
		n = read(),m = read();
		int ans = 0;
		for(int i = 1;i * i <= n;i ++){
			if(n % i == 0){
				ans = (ans + mu[i] * C(m - 1,n / i - 1)) % mod;
				if(n / i != i)ans = (ans + mu[n / i] * C(m - 1,i - 1)) % mod;
			}
		}
		printf("%lld\n",(ans + mod) % mod);
	}
}
```

---

## 作者：MCAdam (赞：4)

[题目](https://www.luogu.com.cn/problem/CF439E)

题意：$Q$次询问，给定$n$和$f$，求满足以下条件的序列$\{a_i\}$的数量

$\displaystyle \sum_{i=1}^{f}a_i=n\quad \gcd(a_1,a_2,...,a_f)=1$

$1\leq f\leq n\leq 10^5\quad Q\leq 10^5$

$\displaystyle \sum_{a_1=1}^{n}\sum_{a_2=1}^{n}...\sum_{a_f=1}^{n}[\sum_{i=1}^{f}a_i=n,\gcd(a_i)=1]$

$\displaystyle =\sum_{a_1=1}^{n}\sum_{a_2=1}^{n}...\sum_{a_f=1}^{n}[\sum_{i=1}^{f}a_i=n]\sum_{d\mid \gcd(a_i)}\mu(d)$

$\displaystyle =\sum_{d=1}^{n}\mu(d)\sum_{d\mid a_1}^{n}\sum_{d\mid a_2}^{n}...\sum_{d\mid a_f}^{n}[\sum_{i=1}^{f}a_i=n]$

$\displaystyle =\sum_{d=1}^{n}\mu(d)\sum_{a_1=1}^{n/d}\sum_{a_2=1}^{n/d}...\sum_{a_f=1}^{n/d}[\sum_{i=1}^{f}a_i=\frac{n}{d}]$

然后枚举一下$d$，先判断$d$是否整除$n$，如果整除，就直接隔板法算后面那一坨就可以了

注意到这里$a_i$都是正整数
    
如果把$n$分成$m$份，且每一份不能为空
    
方案数为$\binom{n-1}{m-1}$

如果可以为空，就是$\binom{n+m-1}{m-1}$（与此题无瓜）

预处理一下$\mu$函数，阶乘和阶乘的逆元，时间复杂度$O(Q\times \sqrt{n})$

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const int N=1e5;
const ll mod=1e9+7;
int vis[N+10],prim[N+10];
ll fac[N+10],inv[N+10],miu[N+10];
inline ll power(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}
inline ll C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline void pre()
{
	fac[0]=1;
	for(int i=1;i<=N;i++)
		fac[i]=fac[i-1]*i%mod;
	inv[N]=power(fac[N],mod-2);
	for(int i=N-1;i>=0;i--)
		inv[i]=inv[i+1]*(i+1)%mod;
	miu[1]=1;
	int cnt=0;
	for(int i=2;i<=N;i++)
	{
		if(!vis[i]) vis[i]=1,prim[++cnt]=i,miu[i]=-1;
		for(int j=1;j<=cnt&&i*prim[j]<=N;j++)
		{
			vis[i*prim[j]]=1;
			if(i%prim[j]) miu[i*prim[j]]=-miu[i];
			else{ miu[i*prim[j]]=0; break; }
		}
	}
}
int main()
{
	pre();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m,k; ll ans=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=sqrt(n);i++)
		{
			if(n%i) continue;
			ans=(ans+miu[i]*C(n/i-1,m-1)%mod+mod)%mod;
			if(n/i!=i) ans=(ans+miu[n/i]*C(i-1,m-1)%mod+mod)%mod;
		}	
		printf("%lld\n",ans);
	}
	return 0;
}
```

  

---

## 作者：lottle1212__ (赞：3)

# [Devu and Birthday Celebration](https://www.luogu.com.cn/problem/CF439E)

设 $d=\gcd(a_1, a_2, \dots, a_f)$，则题目要求的是 $d$ 为 $1$ 时 $\sum_{i=1}^fa_i=n$ 的答案。而对于 $\sum_{i=1}^fa_i=n$ 这个问题的答案记为 $g(f, n)$。则用插板法可以容易地求出 $g(f, n)=(^{n-1}_{f-1})$，则接下来的问题就是消去 $d\not=1$ 时的答案。首先显然有 $d|n$，且这个问题应当是使用容斥解决，而对于有关 $\gcd=1$ 的容斥，可以使用莫比乌斯反演。莫比乌斯反演的结论是若有 $f(n)=\sum_{d|n}g(d)$，则 $g(n)=\sum_{d|n}f(d)\times\mu(\frac nd)$ 。此题中，设整道题的答案为 $h(f, n)$，则有 $g(f, n)=\sum_{d|n}h(f, \frac nd)$，其中 $h(f, \frac nd)$ 的意义为长度为 $f$ 的数列 $\gcd=d$ 时的答案。此时使用莫比乌斯反演，就有 $h(f, n)=\sum_{d|n}g(f, d)\times\mu(\frac nd)$。

使用线性筛筛出 $\mu$，每个询问直接 $O(\sqrt n)$ 卷积即可。时间复杂度 $O(q\sqrt n)$。

Code 在[此](https://codeforces.com/contest/439/submission/306341262)。

---

## 作者：thecold (赞：3)

[CF439E Devu and Birthday Celebration](https://www.luogu.com.cn/problem/CF439E)

看题解里面全是$μ$函数，我来补一篇容斥原理的题解。

基本思路：我们可以很容易求出来如果没有$gcd(a_1 , a_2 ……a_f) = 1$限制的方案数，即考虑隔板法$C_{n - 1}^{f - 1}$可是这时不免会出现一些$gcd$不为1的组合$i$，那么我们可以枚举$n$的约数，然后减去$gcd$恰好为$i$的方案数，最终就是我们的答案啦

具体来说，我们使用记忆化搜索来完成我们的$dp$过程，设$f[s , l]$表示我现在要把$s$分成$l$个合法的方案数，那么当我们的$s$为质数的时候，我们可以发现，无论如何分（每个分得的数至少为1），其不可能出现$gcd$大于1

证明：如果$gcd$大于1，那么也就是说$s$除去$gcd$后仍然是个整数，与$s$是个质数相矛盾

所以如果$s$为质数的时候，方案数就为$C_{s - 1}^{l - 1}$

当$s$ 不是质数的时候，如果$l > s$直接返回0 就可以，因为不够每人一个糖(如果宁好奇为啥这回出来“人”和“糖”，宁可以去康康英文题面）

否则，我们先求出来总的方案数$C_{s - 1}^{l - 1}$,之后$O(\sqrt n)$枚举其约数$i$递归求$f[s/i , l]$也就是说我枚举了他们的$gcd$，
减去$gcd$恰好为$i$的方案数

有一点需要注意的是，我们并不能开下$f[1e5 , 1e5]$的记忆化数组，所以我们选择离线处理，将询问按照$l$排序，因为我们发现$l$不同的是互不干扰的，那么对于每个$l$的询问我单独记忆化搜索，当$l$改变时，我就不管别的$l$的值，即直接覆盖就可以了，所以我们的空间复杂度就变为了$O(n)$。

可以特殊判断的一点就是当$l = 1$的时候，看一下我的$s$是多少，如果是1，那么方案数就是1，否则为0.

$ code:$
```
#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
inline int read()
{
	int res = 0;
	char c;
	bool flag = false;
	c = getchar();
	while(!isdigit(c))
	{
		flag = (c == '-');
		c = getchar();
	}
	while(isdigit(c))
	{
		res = res * 10 + (c ^ 48);
		c = getchar();
	}
	return !flag ? res : -res;
}
typedef long long ll;
const int MOD = 1e9 + 7;
const int Max_n = 1e5 + 5;
ll jc[Max_n];
struct Node
{
	int sum, len , id;
	Node(int a , int b)
	{
		sum = a , len = b;
	}
	Node(int a , int b , int c)
	{
		sum = a , len = b , id = c;
	}
	Node() {}
} query[Max_n] , f[Max_n];
inline bool cmp(Node a , Node b)
{
	return a.len < b.len;
}
int prime[Max_n] , vis[Max_n] , tot , maxn;
inline int quickpow(ll x , int y)
{
	ll ret = 1;
	while(y)
	{
		if(y & 1)	ret *= x , ret %= MOD;
		x *= x , x %= MOD;
		y >>= 1;
	}
	return ret;
}
inline int ni(int x)
{
	return quickpow(x , MOD - 2);
}
inline int C(int n , int m)
{
	if(m > n)	return 0;
	return jc[n] * ni(jc[m] * jc[n - m] % MOD) % MOD;
}
inline ll dfs(int s , int l)//s candys need to be divided by l people;
{
	if(s < l)
	{
		f[s] = Node(0 , l);
		return 0;
	}
	if(f[s].len == l)	return f[s].sum;
	if(s == prime[vis[s]])
	{
		f[s] = Node(C(s - 1 , l - 1) , l);
		return f[s].sum;
	}
	ll val = C(s - 1 , l - 1);
	for(int i = 2 ; i * i <= s ; ++ i)
	{
		if(s % i)	continue;
		val -= dfs(s / i , l) , val %= MOD;
		if(i * i == s)	break;
		val -= dfs(s / (s / i) , l) , val %= MOD;
	}
	val = (val + MOD) % MOD;
	f[s] = Node(val , l);
	return val;
}
inline void build()
{
	vis[1] = 0;
	prime[0] = 1;
	for(int i = 2 ; i <= maxn ; ++ i)
	{
		if(!vis[i])
		{
			prime[ ++ tot] = i;
			vis[i] = tot;
		}
		for(int j = 1 ; j <= tot && (ll) i * prime[j] <= maxn; ++ j)
		{
			vis[i * prime[j]] = j;
			if(i % prime[j] == 0)	break;
		}
	}
}
ll ans[Max_n];
int main()
{
	int q = read();
	for(int i = 1 ; i <= q ; ++ i)
	{
		int ui = read() , vi = read();
		maxn = max(ui , maxn);
		query[i] = Node(ui , vi , i);
	}
	build();
	jc[0] = 1;
	for(int i = 1 ; i <= maxn ; ++ i)
		jc[i] = jc[i - 1] * i % MOD;
	sort(query + 1 , query + q + 1 , cmp);
	for(int i = 1 ; i <= q ; ++ i)
	{
		if(query[i].len == 1)	ans[query[i].id] = (query[i].sum == 1);
		else ans[query[i].id] = dfs(query[i].sum , query[i].len);
	}
	for(int i = 1 ; i <= q ; ++ i)
		printf("%lld\n" , ans[i]);
	return 0;
}
```


---

## 作者：xuyiyang (赞：2)

### [CF439E Devu and Birthday Celebration](https://www.luogu.com.cn/problem/CF439E)
### Solution
为什么题解区全是莫反啊？提供一个简单的 DP 做法。
考虑总情况减去不合法的。记答案为 $f(n,m)$。总情况显然是 $\dbinom{n-1}{m-1}$。考虑 $\gcd(a_1,a_2,\dots a_m)=k$，则令 $a_p=kb_p$，则有 $\gcd(b_1,b_2,\dots b_m)=1$，且 $\sum b=\frac{n}{k}$，那么不合法的情况就是 $f(\frac{n}{k},m)$。直接 `map` 记忆化搜索即可。由于 $k$ 是 $n$ 的因数，所以只会牵连 $d(n)$ 个 $f$，$\mathcal O(q\sqrt n)$。

---

## 作者：Kazdale (赞：2)

做法：DP + 暴力容斥

- ## 分析

	观察题面给出的两个要求，要求二感觉不太好计算，那么就先计算满足要求一的数列个数。
    
    尝试 DP，设 $f_{i,j}$ 表示和为 $j$ 的 $i$ 位数列个数，那么 $f_{i,j}=\sum_{k=i-1}^{j-1}f_{i-1,k}$。
    
    因为 $f_{i,j-1}=\sum_{k=i-1}^{j-2}f_{i-1,k}$，所以 $f_{i,j}=f_{i,j-1}+f_{i-1,j-1}$。我们发现这个式子非常熟悉，因为杨辉三角的递推式子也是这个，于是我们就可以直接套用杨辉三角的通项公式，所以 $f_{i,j}=\binom{j-1}{i-1}$。
    
    结合题面给出的变量，符合第一个条件的数列个数为 $\binom{n-1}{f-1}$。
    
    接下来考虑条件二，然后我们可以发现，一个 $\gcd$ 不为 $1$ 的数列之和显然为 $\gcd$ 的倍数且数列里每一位上的数 $a_i$ 均可以表示为 $a_i \times \gcd$。那么如果我们设 $g_{i,j,k}$ 表示一个长度为 $k$ 的数列的和为 $j$ 且 $\gcd$ 为 $i$ 的倍数时的数列数，那么 $g_{i,j,k}=[i\;|\;j] \times  [\frac{j}{i} \geq k] \times \binom{\frac{j}{i}-1}{k-1}$。
    
    那么我们是否可以枚举能够整除数列和的质数，然后减去它们的 $g$ 呢？答案显然是否定的，因为当 $\gcd$ 为合数时，会出现被多个 $g$ 统计然后被减去多次的情况。于是考虑容斥。
    
    然后我们发现 $2\times3\times5\times7\times11\times13\times17=510510>10^5$，所以对于一个数而言最多存在 $6$ 个互不相同的质因子，于是预处理出所有因子只有 $1 \sim 6$ 个互不相同的质因子的数，然后进行容斥（减一个质因子的 $g$，加两个质因子的 $g$，再减去三个质因子的 $g\dots$）。
    
    如何预处理？暴力六层循环即可，接下来分析暴力六层循环的时间复杂度。
    
    我们可以在当前质数之积大于 $10^5$ 的时候跳出当前循环，于是我们的总操作次数就等于积合法处理数字数和判断数 $+$ 积非法时判断数。
    
    积非法的时候判断数小于等于处理数字数，因为每一个积要么是从一个处理数字乘一个新质数转移而来的，要么是从一个处理数字增大了一个质数转移而来的。因为一个积非法后会直接跳出循环所以不可能从非法数字转移来，同时由于不一定每个处理数字增大之后一定非法，所以积非法的时候判断数小于等于处理数字数。
    
    积合法处理数字数和判断数一定等于处理数字乘以一个常数，所以我们只要分析出处理数字的规模即可。因为算数基本定理，每个数的质因数分解是唯一的，所以不同质因数分解对应的数是不同的。可以发现我们枚举的几个质数就是积的质因数分解，而我们枚举时可以使质数序列严格递增保证不会重复出现两次枚举的质数均相同（因为就算前面和后面均相同，当前位上每个质数也只能出现一次，而且因为严格递增所以当前位上的质数也不可能在前面或者后面再次出现导致交换后实际上是重复的），所以这些质数之积，即处理数字是互不相同且均 $\leq 10^5$ 的，所以处理数字的数量最多为 $10^5$ 个。
    
    积非法的时候判断数小于等于处理数字数，积合法处理数字数和判断数为处理数字数乘以一个常数，所以总操作次数的规模和处理数字的规模相同，均为 $10^5$ 级别，即 $\mathcal{O(w)}$ 的时间复杂度（这里 $w$ 为值域，大小为 $10^5$，后文中的 $w$ 为同一定义）。
    
    所以最后的时间复杂度为 $\mathcal{O(w+q\sqrt{n}\log mod)}$，可以通过本题。

- ## 代码

```
#include <iostream>
#define int long long
using namespace std;
constexpr int MAXN(1000007);
constexpr int mod(1000000007);
int fct[MAXN], vis[MAXN], pr[MAXN], num[MAXN];
int q, cnt;
inline void read(int &temp) { cin >> temp; }
inline void DealFact() { fct[0] = 1;  for (int i(1); i <= 100000; ++i)  fct[i] = fct[i - 1] * i % mod; }
inline void DealPrime() {
	for (int i(2); i <= 100000; ++i) {
		if (!vis[i])  pr[++cnt] = i;
		for (int j(1); j <= cnt; ++j) {
			if (i * pr[j] > 100000)  break;
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0)  break;
		}
	}
}
inline void DealRc() {
	for (int a(1); a <= cnt; ++a) {
		num[pr[a]] = 1;
	for (int b(a + 1); b <= cnt; ++b) {
		if (pr[a] * pr[b] > 100000)  break;
		num[pr[a] * pr[b]] = 2;
	for (int c(b + 1); c <= cnt; ++c) {
		if (pr[a] * pr[b] * pr[c] > 100000)  break;
		num[pr[a] * pr[b] * pr[c]] = 3;
	for (int d(c + 1); d <= cnt; ++d) {
		if (pr[a] * pr[b] * pr[c] * pr[d] > 100000)  break;
		num[pr[a] * pr[b] * pr[c] * pr[d]] = 4;
	for (int e(d + 1); e <= cnt; ++e) {
		if (pr[a] * pr[b] * pr[c] * pr[d] * pr[e] > 100000)  break;
		num[pr[a] * pr[b] * pr[c] * pr[d] * pr[e]] = 5;
	for (int f(e + 1); f <= cnt; ++f) {
		if (pr[a] * pr[b] * pr[c] * pr[d] * pr[e] * pr[f] > 100000)  break;
		num[pr[a] * pr[b] * pr[c] * pr[d] * pr[e] * pr[f]] = 6;
	}}}}}}
}
inline int ksm(int base, int k) {
	int res(1);
	while (k) {
		if (k & 1)  res = res * base % mod;
		base = base * base % mod, k >>= 1;
	}
	return res;
}
inline int C(int n, int m) { return fct[n] * ksm(fct[n - m] * fct[m] % mod, mod - 2) % mod; }
inline int calc(int n, int k) {
	int res = C(n - 1, k - 1);
	for (int i(1); i * i <= n; ++i) {
		if (n % i == 0 && num[i] && n / i >= k) {
			if (num[i] % 2 == 1)  res = ((res - C(n / i - 1, k - 1)) % mod + mod) % mod;
			if (num[i] % 2 == 0)  res = (res + C(n / i - 1, k - 1)) % mod;
		}
		if (n % i == 0 && num[n / i] && i * i != n && i >= k) {
			if (num[n / i] % 2 == 1)  res = ((res - C(i - 1, k - 1)) % mod + mod) % mod;
			if (num[n / i] % 2 == 0)  res = (res + C(i - 1, k - 1)) % mod;
		}
	}
	return res;
}
signed main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	read(q);
	DealFact(), DealPrime(), DealRc();
	for (int i(1), x, y; i <= q; ++i) {
		read(x), read(y);
		cout << calc(x, y) << '\n';
	}
	return 0;
}
```

---

## 作者：Kelvin2009 (赞：1)

这是一道排列组合加莫比乌斯变换。

首先，原答案可以表达为：
$$\displaystyle\sum_{a_1=1}^n\displaystyle\sum_{a_2=1}^n…\displaystyle\sum_{a_f=1}^n\lbrack\gcd(a_1,a_2,…,a_f)=1\rbrack\lbrack a_1+a_2+…+a_f=n\rbrack$$ 

设 $\gcd(a_1,a_2,…,a_f)$ 为 $g$。

则原式可以转化为：
$$\displaystyle\sum_{a_1=1}^n\displaystyle\sum_{a_2=1}^n…\displaystyle\sum_{a_f=1}^n\displaystyle\sum_{d\mid g}\mu(d)\lbrack a_1+a_2+…+a_f=n\rbrack$$ 

考虑到 $g$ 与 $n$ 一定满足 $g\mid n$，否则 $a_1+a_2+…+a_f\not =n$。

先枚举 $d$：
$$\sum_{d\mid n}\mu(d)\displaystyle\sum_{a_1=1}^{\frac{n}{d}}\displaystyle\sum_{a_2=1}^{\frac{n}{d}}…\displaystyle\sum_{a_f=1}^{\frac{n}{d}}\displaystyle\lbrack a_1+a_2+…+a_f=\frac{n}{d}\rbrack$$ 

对于式子的后半段，可以看作把 $\frac{n}{d}$ 个 1 分给 $f$ 个数，所以使用插板法：在 $\frac{n}{d}$ 个 1 中间入 $f-1$ 个板，将隔开的各块按顺序分给 $f$ 个数。

最后化简为：
$$\sum_{d\mid n}\mu(d)C_{\frac{n}{d}-1}^{f-1}$$ 


---

代码：

---


```cpp
#include<bits/stdc++.h>
using namespace std;
const int range=1e5+5;
const long long mod=1e9+7;
int q;
int n,f;
int mu[range];
bool flag[range];
int len,prime[range];
inline void init()
{
	mu[1]=1;
	for(int i=2;i<=1e5;i++)
	{
		if(!flag[i])
		{
			prime[++len]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=len && i*prime[j]<=1e5;j++)
		{
			flag[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
	return ;
}
struct com
{
	long long fac[range];
	long long inv[range];
	inline void init()
	{
		fac[0]=fac[1]=1ll;
		inv[0]=inv[1]=1ll;
		for(int i=2;i<=1e5;i++)
		{
			fac[i]=fac[i-1]*i%mod;
			inv[i]=(mod-mod/i)*inv[mod%i]%mod;
		}
		for(int i=2;i<=1e5;i++) inv[i]=inv[i]*inv[i-1]%mod;
		return ;
	}
	inline long long C(int n,int m)
	{
		if(m<n) return 0ll;
		return fac[m]*inv[m-n]%mod*inv[n]%mod;
	}
}com;
int main()
{
	init();
	com.init();
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%d",&n,&f);
		int ran=sqrt(n);
		long long ans=0;
		for(int i=1;i<=ran;i++)
		{
			if(n%i!=0) continue;
			(((ans+=com.C(f-1,i-1)*mu[n/i])%=mod)+=mod)%=mod;
			(((ans+=com.C(f-1,n/i-1)*mu[i])%=mod)+=mod)%=mod;
		}
		if(ran*ran==n) (((ans-=com.C(f-1,ran-1)*mu[ran])%=mod)+=mod)%=mod;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：1)

### 题意

- $q$ 次询问。每次询问给出 $n,f$，求有多少个不同的序列 $\left\{a_i\right\}_{i=1}^f$ 满足：$\displaystyle \sum_{i=1}^f a_i =n$；$\gcd\left(a_1,\dots,a_f\right)=1$，答案对 $10^9+7$ 取模。
- $1\le q\le 10^5,1\le f\le n\le 10^5$。

### 做法

答案为

$$\begin{aligned}\sum_{a_1=1}^n\sum_{a_2=1}^n\cdots\sum_{a_f=1}^n \left[\gcd\left\{a_i\right\}=1 \right]\left[\sum_{i=1}^f a_i=n \right] &=\sum_{a_1=1}^n\sum_{a_2=1}^n\cdots\sum_{a_f=1}^n\left[\sum_{i=1}^f a_i=n\right] \sum_{d\mid \gcd \left\{a_i\right\}}\mu(d)\\&=\sum_{d\mid n}\mu(d)\sum_{a_1=1}^{\frac nd}\sum_{a_2=1}^{\frac nd}\cdots\sum_{a_f=1}^{\frac nd}\left[\sum_{i=1}^f a_i=\dfrac nd\right]  \end{aligned}$$

$\displaystyle \sum_{d\mid n} \mu(d)$ 可以 $O\left(\sqrt n\right)$ 枚举因子实现，关键在于后面一坨。

用插板法去考虑，有 $\dfrac nd$ 个点，$a_i$ 从 $1$ 开始枚举，所以有 $\dfrac nd-1$ 个空。最后要分成 $f$ 段，即插 $f-1$ 个板，所以答案就是 $\Large\tbinom{\frac nd -1}{f-1}$ 。

最后式子就是 $\displaystyle \sum_{d\mid n}\mu(d)\tbinom{\frac nd -1}{f-1}$。

$O(n)$ 处理逆元，前缀积，$\mu$ 函数。$O(q\sqrt n)$ 询问。

### 代码

```cpp
#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;
int q,cnt;
int inv[100005],fac[100005];
int mu[100005],prime[100005];
bitset<100005>used;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline void sieve(int n)
{
	mu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!used[i])	prime[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*prime[j]<=n;j++)
		{
			used[i*prime[j]]=1;
			if(i%prime[j])	mu[i*prime[j]]=-mu[i];
			else	break;
		}
	}
}
inline int getc(int n,int m)
{
	if(n<m)	return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int main()
{
	q=read();
	sieve(100000),inv[0]=inv[1]=1,fac[0]=1;
	for(int i=1;i<=100000;i++)	fac[i]=1ll*fac[i-1]*i%mod;
	for(int i=2;i<=100000;i++)	inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	for(int i=2;i<=100000;i++)	inv[i]=1ll*inv[i]*inv[i-1]%mod;
	while(q--)
	{
		int n=read(),f=read(),ans=0;
		for(int d=1;d*d<=n;d++)
		{
			if(n%d!=0)	continue;
			ans=(ans+mu[d]*getc(n/d -1,f-1)%mod)%mod;
			if(d*d!=n)	ans=(ans+mu[n/d]*getc(d-1,f-1)%mod)%mod;
		}
		printf("%d\n",(ans%mod+mod)%mod);
	}
	return 0;
}

```

---

## 作者：Take_A_Single_6 (赞：0)

很标准的一道容斥题。  
首先我们研究这个 $\gcd(a_1,a_2,...,a_f)= 1$，直接算公因数为 $1$ 显然很难算，考虑逆向思维，用序列总数减去 $\gcd(a_1,a_2,...,a_f)\ne 1$ 的序列个数。  
序列总数很好算，简单的插板法 $\binom{n-1}{f-1}$ 即可算出。  
那这个不合法部分怎么算呢？显然我们可以枚举 $\gcd$ 的值，然而不同值的贡献有重合部分，所以就要容斥。推导这个容斥许多题解用了莫比乌斯函数，这里我用通俗的语言来解释一下。容易想到我们算了 $2$ 的情况，那么 $2$ 的幂次显然就不用算了，也就是说我们只需要算 $n$ 的每个质因数的贡献。但是直接加 $2$ 和 $3$ 的贡献会多算 $6$ 的贡献，考虑容斥模型 $\lvert \bigcup_{i=1}^{n} S_i \rvert =\sum_{m=1}^{n} (-1)^{m-1} \sum_{a_i<a_{i+1}} \lvert \bigcap_{i=1}^{m} S_{a_i} \rvert$。
- 由偶数个不同的质因子构成的数是正贡献。
- 由奇数个不同的质因子构成的数是负贡献。
- 含有两个及以上相同的质因子则为零贡献。  

至于具体贡献大小，仍然是插板法 $\binom{\frac{n}{p}-1}{f-1}$。  
容斥系数在做线性筛的时候算就好了，代码很好写：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 1000005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int T,n,m,ans,fac[maxn],ifac[maxn],p[maxn],cnt,mu[maxn];
bool ip[maxn];
int ksm(int b,int p)
{
	int s=1;
	while(p)
	{
		if(p&1)s=s*b%mod;
		b=b*b%mod,p>>=1;
	}
	return s;
}
int C(int x,int y)
{
	if(x>y)return 0;
	return fac[y]*ifac[x]%mod*ifac[y-x]%mod;
}
void prime()
{
	mu[1]=1; 
	for(int i=2;i<=100000;i++)
	{
		if(!ip[i])p[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*p[j]<=100000;j++)
		{
			ip[i*p[j]]=1;
			if(i%p[j]==0)break;
			mu[i*p[j]]=-mu[i];
		}
	}
}
signed main()
{
	prime();
	fac[0]=ifac[0]=1;
	for(int i=1;i<=100000;i++)fac[i]=fac[i-1]*i%mod,ifac[i]=ksm(fac[i],mod-2);
	for(T=read();T;T--)
	{
		n=read(),m=read(),ans=0;
		for(int i=1;i*i<=n;i++)
		{
			if(n%i==0)
			{
				ans=(ans+mu[i]*C(m-1,n/i-1)%mod)%mod;
				if(i!=n/i)ans=(ans+mu[n/i]*C(m-1,i-1))%mod;
			}
		}
		write((ans+mod)%mod),puts("");
	}
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：0)

小清新数学题。
### 题意
一共有 $q$ 个询问，每次询问给出两个正整数 $n$，$f$ 要求输出有多少个不同的长度为 $f$ 的序列 $a_i$ 满足:

- $\sum_{i=1}^f a_i=n$
- $\gcd(a_1,a_2,\ldots,a_f)=1$

答案对 $10^9+7$ 取模。
### 分析
暴力列出柿子，稍微推一下就好了。由题意可得：
$$Ans=\sum_{a_1=1}^n\sum_{a_2=1}^n\ldots\sum_{a_f=1}^n[\sum_{i=1}^fa_i=n][\gcd(a_1,a_2,\ldots,a_f)=1]$$
这个柿子很好处理，套路化的考虑莫比乌斯反演：
$$\begin{aligned}
Ans={}&\sum_{a_1=1}^n\sum_{a_2=1}^n\ldots\sum_{a_f=1}^n[\sum_{i=1}^fa_i=n]\sum_{d|\gcd(a_1,a_2,\ldots,a_f)}\mu(d)&\\
=&\sum_{d=1}^n\mu(d)\sum_{a_1=1}^{\lfloor \frac nd \rfloor}\sum_{a_2=1}^{\lfloor \frac nd \rfloor}\ldots\sum_{a_f=1}^{\lfloor \frac nd \rfloor}[\sum_{i=1}^f{a_id}=n]
\end{aligned}
$$
注意一下，上面 $a_i$ 的含义有所改变。这里可以发现必须满足 $d|n$ 才会有贡献，把 $d$ 除过去：
$$
Ans=\sum_{d|n}\mu(d)\sum_{a_1=1}^{\lfloor \frac nd \rfloor}\sum_{a_2=1}^{\lfloor \frac nd \rfloor}\ldots\sum_{a_f=1}^{\lfloor \frac nd \rfloor}[\sum_{i=1}^f{a_i}=\frac nd]
$$
发现后面这个柿子的本质就是把 $\frac nd$ 个物品放进 $f$ 个袋子里且不能为空，使用小学奥数经典手段插板法，可以得到：
$$Ans=\sum_{d|n}\mu(d)\dbinom{\frac nd -1}{f-1}$$
于是我们线性筛一下 $\mu$ ，预处理组合数，每次询问只需要 $\mathcal O(\sqrt n)$ 枚举一下因数就可以求了，总的时间复杂度 $\mathcal O(V+q\sqrt n)$，随便过。

如果你有线性筛 $\mu$ 的板子和组合数的板子这题几乎都不用写，找板子贺一下，写个柿子就好了。
### 代码
```cpp
const int maxn=1e5+5;
const int mod=1e9+7;
int T;
int n,f,ans;
int fac[maxn],inv[maxn];
int pw(int a,int x){
	int s=1;
	while(x){
		if(x&1) s=s*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return s%mod;
}
void init(){
	fac[0]=1;
	for(int i=1;i<maxn;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[maxn-1]=pw(fac[maxn-1],mod-2);
	for(int i=maxn-2;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}
int C(int n,int m){
	if(n<m) return 0;
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int mu[maxn],p[maxn];
vector<int> pri;
void getmu(){
	mu[1]=1;
	for(int i=2;i<maxn;i++){
		if(!p[i]){
			mu[i]=-1;
			pri.push_back(i);
		}
		for(int q:pri){
			if(i*q>=maxn) break;
			p[i*q]=1;
			if(i%q==0){
				mu[i*q]=0;
				break;
			}
			mu[i*q]=-mu[i];
		}
	}
}
signed main(){
	cin.tie(0),cout.tie(0);
	init();
	getmu(); 
	T=read();
	while(T--){
		n=read(),f=read();
		ans=0;
		for(int d=1;d*d<=n;d++){
			if(n%d==0){
				ans=(ans+mu[d]*C(n/d-1,f-1)%mod+mod)%mod;
				if(d*d!=n) ans=(ans+mu[n/d]*C(d-1,f-1)%mod+mod)%mod;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：UperFicial (赞：0)

下文中 $n,m$ 分别对应原题 $f,n$。

不难想到莫比乌斯反演。

设 $f(d)$ 表示 $\sum_{a_1,a_2,\cdots,a_n}[\sum_{i=1}^na_i=m][\gcd(a_1,a_2,\cdots,a_n)=k]$ 的结果，显然 $f(1)$ 即为所求。

设 $g(d)$ 表示 $\sum_{a_1,a_2,\cdots,a_n}[\sum_{i=1}^na_i=m][k|\gcd(a_1,a_2,\cdots,a_n)]$ 的结果。

不难发现 $f,g$ 的关系为：$g(d)=\sum_{d|k}f(k)$。

根据莫比乌斯反演可得，$f(d)=\sum_{d|k}g(k)\mu(\frac{k}{d})$。

则 $f(1)=\sum_{i=1}^mg(i)\mu(i)$。

$g(i)$ 是容易求的，即钦定每个数均为 $i$ 的倍数，总和为 $m$ 的方案数，显然当 $i\nmid m$ 时结果为 $0$，否则相当于求 $n$ 个总和为 $\frac{m}{i}$ 的正整数的方案数，运用插板法答案即为 $\binom{\frac{m}{i}-1}{n-1}$。

带入可得：

$$\sum_{d|m}\binom{\frac{m}{d}-1}{n-1}\mu(d)$$

时间复杂度 $O(m+q\sqrt{m})$。

---

## 作者：chihik (赞：0)

$$\sum_{i_1=1}^n\sum_{i_2=1}^n...\sum_{i_f=1}^n [\sum{a_i}=n][\gcd{a_i}=1]$$

$$\sum_{i_1=1}^n\sum_{i_2=1}^n...\sum_{i_f=1}^n [\sum{a_i}=n]\sum_{d|\gcd{a_i}} \mu(d)$$

$$\sum_{d|n} \mu(d) \sum_{i_1=1}^{\frac{n}{d}}\sum_{i_2=1}^{\frac{n}{d} }...\sum_{i_f=1}^{\frac{n}{d}} [\sum{a_i}=\frac{n}{d}]$$

后面枚举 $i$ 的过程可以看作将 $\frac{n}{d}$ 个相同的球放进 $f$ 个不同的盒子，且不能有空盒的方案数，利用插板法可得： $\binom{\frac{n}{d}-1}{f-1}$

那么原式即为：

$$\sum_{d|n} \mu(d) \binom{\frac{n}{d} - 1 }{f-1}$$

```cpp
#include <cstdio>

const int MAXN = 1e5 , Mod = 1e9 + 7;

int Quick_pow( int x , int po ) { int p = 1; for( ; po ; po >>= 1 , x = 1ll * x * x % Mod ) if( po & 1 ) p = 1ll * p * x % Mod; return p; }
int Inv( int x ) { return Quick_pow( x , Mod - 2 ); }

int prnum , prime[ MAXN + 5 ] , mu[ MAXN + 5 ];
bool vis[ MAXN + 5 ];
void sieve( ) {
	mu[ 1 ] = 1;
	for( int i = 2 ; i <= MAXN ; i ++ ) {
		if( !vis[ i ] ) {
			prime[ ++ prnum ] = i;
			mu[ i ] = -1;
		}
		for( int j = 1 ; j <= prnum && i * prime[ j ] <= MAXN ; j ++ ) {
			vis[ i * prime[ j ] ] = 1;
			if( i % prime[ j ] == 0 ) break;
			mu[ i * prime[ j ] ] = -mu[ i ];
		}
	}
}
int fac[ MAXN + 5 ] , ivf[ MAXN + 5 ];
void Init( ) {
	fac[ 0 ] = 1;
	for( int i = 1 ; i <= MAXN ; i ++ ) fac[ i ] = 1ll * fac[ i - 1 ] * i % Mod;
	ivf[ MAXN ] = Inv( fac[ MAXN ] );
	for( int i = MAXN ; i >= 1 ; i -- ) ivf[ i - 1 ] = 1ll * ivf[ i ] * i % Mod;
}
int C( int n , int m ) {
	return n < m ? 0 : 1ll * fac[ n ] * ivf[ m ] % Mod * ivf[ n - m ] % Mod;
}


int Solve( int n , int f ) {
	int Ans = 0;
	for( int d = 1 ; d * d <= n ; d ++ )
		if( n % d == 0 ) {
			Ans = ( Ans + mu[ d ] * C( n / d - 1 , f - 1 ) ) % Mod;
			if( d * d != n ) Ans = ( Ans + mu[ n / d ] * C( d - 1 , f - 1 ) ) % Mod;
		}
	return ( Ans + Mod ) % Mod;
}

int q , n , f;
int main( ) {
	Init(); sieve();
	scanf("%d",&q);
	while( q -- ) {
		scanf("%d %d",&n,&f);
		printf("%d\n", Solve( n , f ) );
	}
	return 0;
}
```

---

## 作者：Warriors_Cat (赞：0)

一道莫比乌斯反演后组合意义的题，有点有趣。

### $Solution:$

直接一通乱搞推式子：

$$\begin{aligned}\text{原式}&=\sum_{a_1=1}^n\sum_{a_2=1}^n...\sum_{a_f=1}^n[\gcd\{a_i\}=1\land\sum_{i=1}^fa_i=n]\\&=\sum_{a_1=1}^n\sum_{a_2=1}^n...\sum_{a_f=1}^n[\sum_{i=1}^fa_i=n]\sum_{d\mid \gcd\{a_i\}}\mu(d)\\&=\sum_{d\mid n}\mu(d)\sum_{a_1=1}^{\frac{n}{d} }\sum_{a_2=1}^{\frac{n}{d} }...\sum_{a_f=1}^{\frac{n}{d}}[\sum_{i=1}^fa_i=\frac{n}{d} ]\end{aligned}$$

首先有一个点，$d$ 一定要为 $n$ 的约数，因为 $a_i$ 均为整数。这就是这里 $d\mid n$ 的由来。

也就是说我们可以枚举 $n$ 的所有约数，线性筛预处理 $\mu$，就只剩下最后那一堆了。

考虑组合意义。这就是把 $\dfrac{n}{d}$ 个相同的小鱼分给 $f$ 个不同的猫吃，每只猫都要有鱼的方案数。于是直接插板法可得方案数为 $\dbinom {\frac{n}{d}-1} {f-1}$，注意 $\dfrac{n}{d}<f$ 时方案数为 $0$。

于是这题就做完了，时间复杂度为 $O(N + q\sqrt{N})$，可以通过此题。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define int long long
inline int read(){
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
    return x * f;
}
const int N = 100000, mod = 1000000007;
int q, n, f, fac[N + 10], inv[N + 10], mu[N + 10], pri[N + 10], len, ans; bool vis[N + 10];
inline int fpow(int x, int p){ int ans = 1; for(; p; p >>= 1, x = x * x % mod) if(p & 1) ans = ans * x % mod; return ans; }
inline void initfac(int n){
	fac[0] = 1;
	for(int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % mod;
	inv[n] = fpow(fac[n], mod - 2);
	for(int i = n - 1; ~i; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
}//预处理阶乘和阶乘逆元
inline int C(int n, int m){ if(n < m) return 0; return fac[n] * inv[m] % mod * inv[n - m] % mod; }//组合数
inline void sieve(){
	mu[1] = 1;
	for(int i = 2; i <= N; ++i){
		if(!vis[i]) pri[++len] = i, mu[i] = -1;
		for(int j = 1; j <= len && i * pri[j] <= N; ++j){
			int k = i * pri[j]; vis[k] = 1;
			if(i % pri[j] == 0) break;
			mu[k] = -mu[i];
		}
	}
}//线性筛
signed main(){
	q = read(); initfac(N); sieve();
	while(q--){
		n = read(); f = read(); ans = 0;
		for(int i = 1; i * i <= n; ++i){
			if(n % i != 0) continue;
			ans = (ans + mu[i] * C(n / i - 1, f - 1) % mod) % mod;
			if(n != i * i) ans = (ans + mu[n / i] * C(i - 1, f - 1) % mod) % mod; 
		}
		printf("%lld\n", (ans % mod + mod) % mod);
	}
	return 0;
}
```

---

## 作者：ql12345 (赞：0)

# 提示几个细节，不会涉及做法

数学这东西，写法还是规范点吧以后。。。

写这题之前我计算组合数的时候从没判过分子小于分母（也就是m<n）的情况，被卡了

还有对阶乘和其逆元的预处理，0的阶乘及逆元的取值也从不考究，也被卡了（0的阶乘一般处理成1，0的逆元一般也处理成1）

1的莫比乌斯函数，也先赋成1

em基本上就是这些了，还有就是数学题嘛，压行愉快！

---

