# Count the Arrays

## 题目描述

Your task is to calculate the number of arrays such that:

- each array contains $ n $ elements;
- each element is an integer from $ 1 $ to $ m $ ;
- for each array, there is exactly one pair of equal elements;
- for each array $ a $ , there exists an index $ i $ such that the array is strictly ascending before the $ i $ -th element and strictly descending after it (formally, it means that $ a_j < a_{j + 1} $ , if $ j < i $ , and $ a_j > a_{j + 1} $ , if $ j \ge i $ ).

## 说明/提示

The arrays in the first example are:

- $ [1, 2, 1] $ ;
- $ [1, 3, 1] $ ;
- $ [1, 4, 1] $ ;
- $ [2, 3, 2] $ ;
- $ [2, 4, 2] $ ;
- $ [3, 4, 3] $ .

## 样例 #1

### 输入

```
3 4```

### 输出

```
6```

## 样例 #2

### 输入

```
3 5```

### 输出

```
10```

## 样例 #3

### 输入

```
42 1337```

### 输出

```
806066790```

## 样例 #4

### 输入

```
100000 200000```

### 输出

```
707899035```

# 题解

## 作者：Scintilla (赞：23)

### 题意

给定 $n,m$，求满足下列条件的长度为 $n$ 的数组数量：

-  $a_i \in [1,m]$；
- 有且仅有一对相同的数字
- 具有单峰性，即 $\exists 1 \leq i \leq n$，对 $\forall 1 \leq j \leq n,j \ne i$，若 $j < i$，则 $a_j < a_i$；否则 $a_j > a_i$。

输出答案对 $998244353$ 取模的值。

### 思路
对于一个数组，如果已经确定了其中的数字，那么能确定的是：相同的数字在最大的数字两边。

考虑把其余的数字划分成两部分，把第一部分放到最大数的左边、把第二部分放到右边。因为最大数左右都没有重复的数字，所以能排成一个满足条件的数组。每种分法一一对应着一个满足条件的数组。

已经有 $3$ 个数字确定，其余的数字有两个选择（分到最大数左边或右边），所以共有 $2 ^ {n - 3}$ 个满足条件的数组。

举个例子：如果数组中的数字是 $1,2,2,3,4$

1. 可以确定的是 $2 \ 4 \ 2$。

2. 现在考虑把 $1,3$ 分到两边去。有 $4$ 种分法，分别是：$\color{red}{1} \color{black}{ \ 2 \ } \color{red}{3} \color{black}{ \ 4 \ 2}$、$\color{red}{1} \color{black}{ \ 2 \ 4 \ } \color{red}{3} \color{black}{ \ 2}$、$2 \ \color{red}{3} \color{black}{ \ 4 \ 2 \ } \color{red}{1}$和$2 \ 4 \ \color{red}{3} \color{black}{ \ 2 \ } \color{red}{1}$。


那么如何确定数组中的数字呢？很简单。我们可以先从 $1$ 到 $m$ 中选取 $n - 1$ 个数，再从中选取一个非最大值的数作为重复的数字，共 $\dbinom{m}{n - 1} \times (n - 2)$ 种选法。

综上：答案为：$2 ^ {n - 3} \times \dbinom{m}{n - 1} \times (n - 2)$。

注意： $n = 2$ 的时候必定无解，需要特判。


### $Code:$
```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

typedef long long ll;

const ll mod = 998244353;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = false; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

il ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return res;
}

il ll inv(ll x) {
    return qpow(x, mod - 2);
}

int n, m;

ll ans = 1, res =1;

int main() {
    n = read(), m = read();
    if (n == 2) {return putchar('0') & 0;}
    Rep(i, 1, m) ans = ans * i % mod;
    Rep(i, 1, n - 1) res = res * i % mod;
    Rep(i, 1, m - n + 1) res = res * i % mod;
    ans = ((ans * inv(res) % mod) * (n - 2) % mod) * qpow(2, n - 3) % mod;
    printf("%lld", ans);
    return 0;
}
```
不会乘法逆元的可以看看[这篇文章](https://www.cnblogs.com/zjp-shadow/p/7773566.html)，讲得很好。

祝大家早日上 $LGM!$

---

## 作者：CXY07 (赞：5)

# 简单计数

## 题目链接：[CF1312D 【Count the Arrays】](https://www.luogu.com.cn/problem/CF1312D)

> **本题解同步发布于 [My Blog](http://cxy07.blog/index.php/archives/19/)**

刚开始菜鸡 $CXY07$ 以为这是一道什么 $dp$，瞎想了好久好久......

首先我们可以发现，这个东西是一个单峰的数组，并且里面有且仅有一个数字出现了两次。

很快发现实际上一个这样的长度为 $n$ 的数组，实际上一共有 $n - 1$ 个不同的数字

那我们就先从 $m$ 个数字中拿 $n - 1$ 个，共 $C_{m}^{n-1}$ 种情况

那么显然中间有一个数字是最大的 ~~废话~~，这个数字必须放在峰顶(?)的位置，其他的 $n - 2$ 个数字自然可以放在峰顶的左侧或者右侧

这里一共多少种情况呢？当然是 $2^{n-2}$ 种（每一个数字可以在左右中任意选择一边）

不难发现只要我们定下这 $n-2$ 个数字分别在峰顶的左边或者右边，整个数组就只有一种构造的方法了，而距离我们完成整个数组，就只差那个重复的值了

然后我们来定这个重复的值是谁，首先这个数字肯定不能是峰顶（题中是严格大于/小于）所以我们只能从剩下 $n-2$ 个值中间选择，并且无论你选择了哪一个值，它一定就已经在数组中出现了一次了。

那么，我们如果选择一个值，那么这个值已经出现在了峰顶的一侧，为了满足 严格大于/小于 的条件，我们只能把这个重复的值放在另外一边了

所以这里我们任意从 $n-2$ 个值中选择都是可行的，这里方案有 $n-2$ 种

但是有一个问题，这里可能会出现重复的情况：

比如：

如果现在我们需要构造一个长度为 $6$ 的序列，我们已经选择了 $1$ ~ $ 5$ 这几个值了，现在有这样两种方案：

```
1 2 5 4 3

1 5 4 3 2
```

如果我们想要再加入一个 $2$，那两个序列会同时变成：```1 2 5 4 3 2``` ，但是我们把他计算了两遍......

容易发现无论你选择哪一个值，都会出现这个情况，所以我们再 $\times \frac{1}{2}$ 就好了

所以最后答案为：

$$C_m^{n-1} \times 2^{n-2} \times (n-2) \times \frac{1}{2}$$

也就是：

$$C_m^{n-1} \times 2^{n-3} \times (n-2)$$

容易发现当 $n < 3$ 时无解，特判即可，我是在判断 $2$ 的幂的时候处理的

用了费马小定理求逆元，所以复杂度貌似带个 $log$

$Code:$

```cpp
//Code By CXY
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define inv(x) ksm(x,mod - 2)

const int MAXN = 2e5 + 10;
const int INF = 2e9;
const int mod = 998244353;

int n,m;

inline int ksm(int a,int b) {
    if(b < 0) return 0;//判断一下即可
	if(a == 1) return 1;
	int res = 1;
	while(b) {
		if(b & 1) (res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}

inline int C(int a,int b) {
	int res = 1;
	for(register int i = a;i >= a - b + 1; --i)
		(res *= i) %= mod;
	for(register int i = 1;i <= b; ++i)
		(res *= inv(i)) %= mod;
	return res;
}

signed main () {
	cin >> n >> m;
	cout << ksm(2,n - 3) % mod * C(m,n - 1) % mod * (n - 2) % mod << endl;
	return 0;//End.
}
```

初三的 $OIer$，请多关照

---

## 作者：__yun__ (赞：3)

### 思路

1. 从 $m$ 个数字中选出 $n-1$ 个不同的数字，有 $C_{m}^{n-1}$ 种方案。

2. 在 $n-1$ 个不同的数字中最大数不能重复(若最大值重复则会相邻，不满足单调递增或单调递减)，剩余的 $n-2$ 个数字都可以作为重复的数字，有 $n-2$ 种方案。

3. 最大数字在中间，重复的数字在最大数字的两侧，剩余的(n-3)个数字每个数字都有在最大数字左侧、最大数字右侧两种选择（一旦选定左侧还是右侧，因为需要满足单调，所以其位置是固定的），有 $2^{n-3}$ 种方案。

最终结果： 
$$C_{m}^{n-1}\times (n-2) \times 2^{n-3}$$
  
注意 $n < 3$ 时一定无解，需要特判。

# $Code:$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=2e5+10;
const int mod=998244353;
int n,m;
int fac[M],inv[M];
int poww(int x,int y){
	if(y==0) return 1;
	int ans=poww(x,y/2)%mod;
	return (y&1?ans*ans%mod*x%mod:ans*ans%mod);
}
int exgcd(int a,int b,int &x,int &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	int r=exgcd(b,a%b,x,y);
	int t=x;
	x=y;
	y=t-a/b%mod*y%mod;
	return r;
}
void init(){
	n=2e5;
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	int x,y;
	exgcd(fac[n],mod,x,y);
	inv[n]=x%mod;
	for(int i=n-1;i>=0;i--){
		inv[i]=inv[i+1]*(i+1)%mod;
	}
}
signed main(){
	init();
	scanf("%lld %lld",&n,&m);
  	if(n<3){
	    printf("0");
	    return 0;
	}
	int res=fac[m]*inv[n-1]%mod*inv[m-n+1]%mod*(n-2)%mod*poww(2,n-3)%mod;
	res=(res+mod)%mod;
	printf("%lld",res);
	return 0;
}
```

---

## 作者：一扶苏一 (赞：3)

# 【组合计数】【CF1312D】 Count the Arrays

## Description

求满足如下条件的长度为 $n$ 的序列 $a$ 的个数：

- $\forall 1 \leq i \leq n$，都有 $1 \leq a_i \leq m$。
- $a$ 中存在且仅存在一对相同的元素
- 存在一个位置 $p$，使得 $a_1 \sim a_p$ 为严格单增序列，$a_p \sim a_n$ 为严格单减序列。即 $\forall 0 < j < p$，都有 $a_{j} < a_{j + 1}$，且 $\forall p \leq j < n$，都有 $a_j > a_{j + 1}$。

$1 \leq n, m \leq 2 \times 10^5$。

答案对 $998,244,353$ 取模。

## Solution

基础的计数题。

我们考虑整个序列的最大值是什么，不妨记为 $y$，显然 $y$ 不能是那一对相同的元素之一，不然序列就不是单峰的了。这样还剩下了 $(n - 2)$ 个不同的数需要选择（因为有一对相同的），因此 $y$ 至少应该是 $n - 1$。

考虑枚举最大值 $y$，我们要从比 $y$ 小的 $(y - 1)$ 个数字中选出 $(n - 2)$ 个，作为序列剩下的元素，这部分的方案数是 $C_{y - 1}^{n - 2}$。

确定了序列元素后，我们考虑要从这 $(n - 2)$ 个数中选择一些数字按顺序放到 $y$ 的左侧，来构造左侧的单增序列，不妨设 $y$ 左侧的数字有 $l$ 个，由于至少会有一个数作为序列中重复的那个数字出现在 $y$ 的另一侧，因此 $l$ 的范围是 $1 \leq l \leq n - 2$。

我们考虑枚举 $l$。则从 $(n - 2)$ 个数中选出 $l$ 个数的方案数为 $C_{n - 2}^l$。同时我们还要在这 $l$ 个数中选出一个数字出来作为序列唯一的重复数字，因此共有 $C_{n - 2}^l \times l$ 种情况。不难发现，这样选定左侧序列并指定重复数字以后，右侧的序列也被唯一确定了。

因此总的方案数为

$$\sum\limits_{y = n - 1}^m C_{y - 1}^{n - 2} \times \sum\limits_{l = 1}^{n - 2} (C_{n - 2}^l \times l)$$

看起来计算这个式子需要 $O(n^2)$ 的复杂度，但是注意到这两个 $\Sigma$ 是相互独立的，即他们可以单独计算然后再将答案乘起来。

考虑枚举一整列和一整行的组合数的值都是 $O(n)$ 的，因此这样就可以 $O(n + m)$ 完成计数了。

当然需要特判 $n = 2$ 时应该输出 $0$。比赛时特判输出 $m$ 白给了一发。

## Code

比赛时写的很丑。

```cpp
const int maxn = 200005;
const int MOD = 998244353;
const int DM = 998244351;

ll n, m, ans;

ll mpow(ll x, ll y) {
  ll ret = 1;
  while (y) {
    if (y & 1) (ret *= x) %= MOD;
    (x *= x) %= MOD;
    y >>= 1;
  }
  return ret;
}

ll fact(ll x) {
  ll ret = 1;
  for (ll i = 2; i <= x; ++i) {
    (ret *= i) %= MOD;
  }
  return ret;
}

int main() {
  freopen("1.in", "r", stdin);
  qr(n); qr(m);
  if (n == 2) {
    puts("0");
    return 0;
  }
  ll dn = n - 2;
  ll t = 0;
  for (ll C = 1, l = 1; l <= dn; ++l) {
    (C *= mpow(l, DM)) %= MOD;
    (C *= dn - l + 1) %= MOD;
    (t += C * l) %= MOD;
  }
  ll y = n - 1;
  ll C = fact(y - 1) * mpow(fact(n - 2), DM) % MOD * mpow(fact(y - n + 1), DM) % MOD;
  while (y <= m) {
    (ans += C * t % MOD) %= MOD;
    (C *= y) %= MOD;
    (C *= mpow(++y - n + 1, DM)) %= MOD;
  }
  qw(ans, '\n', true);
  return 0;
}
```



---

## 作者：ncwzdlsd (赞：2)

首先显然，对于相同的一对数，一定在 $a_p$ 的两边，所以一共有 $(n-2)$ 种可能。

在小于等于 $m$ 的数里选 $n-1$ 个数，一共有 $C_{m}^{n-1}$ 种可能。

然后考虑条件 $3$ 的 $a_p$ 的位置。考虑在 $a_p$ 一侧的数的可能数，一共是 $\sum\limits_{p=0}^{n-3}C_{n-3}^p$ 种可能，即 $2^{n-3}$。

所以最后的答案为 $C_m^{n-1}\times(n-2)\times 2^{n-3}$。

注意 $n=2$ 时需要特判，此时不存在满足条件的序列。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod=998244353;

int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return res;
}

signed main()
{
	int ans=1;
	int n,m;cin>>n>>m;
	if(n==2) cout<<0,exit(0);
	for(int i=m-n+2;i<=m;i++) ans=ans*i%mod;
	for(int i=1;i<=n-1;i++) ans=ans*quickpow(i,mod-2)%mod;
	ans=ans*(n-2)%mod;
	ans=ans*quickpow(2,n-3)%mod;
	cout<<ans;
	return 0;
}
```

[通过记录](https://codeforces.com/contest/1312/submission/217780012)

---

## 作者：TulipeNoire (赞：2)

给一种不同的思路。

先考虑暴力推式子。

枚举峰 $i$，峰顶元素 $j$。显然 $n-1\le j\le m$。

那么左边可以有选取 $C_{j-1}^{i-1}$ 种选取方式。考虑哪个是重复元素，去重后两边选取方案总数为 $(i-1)\times C_{j-1}^{i-1}\times C_{i-j}^{n-j-1}$。

故答案为 $\sum\limits_{i=2}^{n-1}\sum\limits_{j=n-1}^m(i-1)\times C_{j-1}^{i-1}\times C_{i-j}^{n-j-1}$。

化简得到 $\sum\limits_{i=n-1}^m \dfrac{(i-1)!}{(i-n+1)!}\times\sum\limits_{i=2}^{n-1}\dfrac{i-1}{(i-1)!(i-x-1)!}$。

两边分别维护即可。

代码:

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=200005,mod=998244353;
int n,m,fact[N],ans,x=1,y=0,ret;
void exgcd(long long A,long long B) {
	if (!B) return;
	exgcd(B,A%B);
	long long x0=y,y0=x-A/B*y;
	x=x0,y=y0;
	return;
}
inline long long inv(long long A) {
	x=1,y=0,exgcd(A,mod);
	return (x%mod+mod)%mod;
}
signed main() {
	fact[0]=1;
	for (int i=1;i<N;i++) fact[i]=fact[i-1]*i%mod;
	cin>>n>>m;
	for (int i=n-1;i<=m;i++) ret=(ret+fact[i-1]%mod*inv(fact[i-n+1])%mod)%mod;
	for (int i=2;i<n;i++) {
		long long k=(i-1)*inv(fact[i-1])%mod*inv(fact[n-i-1])%mod;
		ans=(ans+k)%mod;
	}
	printf("%lld",ans*ret%mod);
	return 0;
}
```

---

## 作者：QZJ666 (赞：2)

### 1.题意 
求有多少个序列 $a$ 满足:

1. $a$ 中存在且仅存在一对相同的元素

2. $a$ 中前 $k$ 个数字严格单调递增，后 $(n-k)$ 个元素严格单调递减(k不知道)

3. $a$ 中所有元素 $＜m$ 


### 2.思路
~~感觉是[P6475](https://www.luogu.com.cn/problem/P6475)的弱化版~~

很明显这道题在让我们求组合数

首先，因为要求全都是 **严格** 单增或 **严格** 单减,那么我们可以发现除了重复的书外每一个数都只会出现一次,而重复的那一个数会出现两次,相当于在 $m$ 个数中有 $n-1$ 个数出现过,所以我们需要用一次 $C(m,n-1)$ ，求出在 $m$ 个数中选择$n-1$个数的方案数。

之后除了这 $n-1$ 个数中的最大数外,其余 $n-2$ 个数都有可能被选择到,所以我们再乘上一个 $(n-2)$ 来表示重复的一对数值的个数。

然后我们来枚举这每一个数是在最大值左边还是右边,已经有了 $3$ 个数的值是已知的,分别是重复的数(有 $2$ 个),以及最大数。那么其余的 $n-3$ 个数我们是不知道位置的，对于每一个数有两种方案，放在最大值左边与右边,所以直接求 $2^{n-3}$ 就好了

之后在最大值左边的与右边的就只有一种从大到小的情况了

于是答案是 $C(m,n-1)*2^{n-3}*(n-2)$ 

### 3.code
```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll n,m,ans;
const ll p=998244353;
ll pm(ll a,ll n,ll p){
	ll ans=1;
	a%=p;
	while(n){
		if(n%2){
			ans=ans*a%p;
		}
		a=a*a%p;
		n/=2;
	}
	return ans;
} 
ll fac[200005];
void f(){
	fac[0]=1;
	for(int i=1;i<=200000;i++){
		fac[i]=fac[i-1]*i%p;
	}
}
ll inv(ll x,ll p){
	return pm(x,p-2,p);
}
ll C(int n,int m,int p){
	if(m>n){
		return 0;
	}
	return (fac[n]*inv(fac[n-m]*fac[m],p))%p;
}
int Lucas(int n,int m,int p){
	if(n<m||n<0||m<0)
	return 0;
	if(m==0){
		return 1;
	}
	if(n<p){
		return C(n,m,p);
	}
	else{
		return Lucas(n/p,m/p,p)*Lucas(n%p,m%p,p);
	}
}
int main(){
	scanf("%lld%lld",&n,&m);
	f();
	if(n<=2)ans=0;
	else ans=(Lucas(m,n-1,p)%p)*(pm(2,n-3,p)%p)%p*(n-2)%p;
	printf("%lld",ans%p);
	return 0;
}
```
码风极其丑陋

然后交一发就AC了

---

## 作者：Clever_Jimmy (赞：2)

**upd: 修改了一些错误**

我们选出的数中一定有 $n - 1$ 个互不相同的，因此有 $\dbinom{m}{n - 1}$ 种选择方法。

然后我们还要选一个这 $n - 1$ 个数中出现过的，但这个元素不能是我们已经选了的 $n - 1$ 个数中最大的那个，因此有 $n - 2$ 中选择方法。

为了保证是 $\bigwedge$ 的形状，我们先钦定 $3$ 个元素，剩下的元素可以被放到左支或者右支，因此有 $2^{n - 3}$ 中摆法。

综上所述，答案为 $\dbinom{m}{n - 1}(n - 2)\cdot2^{n - 3}$。

注意，有些快速幂的写法当 $n = 2$ 时会陷入死循环。

[code](https://codeforces.ml/contest/1312/submission/72821735)

```cpp
#include <bits/stdc++.h>
#define LL long long

const int mod = 998244353;

int n, m;
LL up = 1LL, down = 1LL;

LL qpow(LL base, LL power) {
	LL res = 1LL % mod;
	while(power) {
		if(power & 1)
			res = res * base % mod;
		base = base * base % mod;
		power >>= 1;
	}
	return res;
}

int main() {
	std::cin >> n >> m;
	//C(m, n - 1) Wrong!
	for(int i = m; i >= m - (n - 1) + 1; --i) up = 1LL * up * i % mod;
	for(int i = 1; i <= n - 1; ++i) down = 1LL * down * i % mod;
	if(n == 1 || n == 2)
		std::cout << 0;
	else
		std::cout << 1LL * up * qpow(down, mod - 2) % mod * qpow(2, n - 3) % mod * (n - 2) % mod;
	
	return 0;
}
```

---

## 作者：Dr_Octopus (赞：2)

### 题意

已知：一个区间长度为 $n$，需要我们从 $1\sim m$ 中选择一部分数字放入这个区间。

规定：必须有一个数字是重复的。存在下标 $i$，使得下标小于 $i$ 的数字递增，下标大于 $i$ 的数字递减。

提问：我们总共有多少种不同的方法来放这部分数字。

------------

#### 前置知识

[排列组合](https://oi-wiki.org/math/combinatorics/combination/)
[乘法逆元](https://oi-wiki.org/math/number-theory/inverse/)

------------

### 思路

首先，我们可以想到，要使数列左半递增，右半递减。那么数列中最大值肯定位于中间位置，其中两个相同的数肯定分别位于最大值的左右两侧。

然后，因为最大值不能重复，为满足约束，我们可以想到 $C^{n-1}_m$，即从中选出 $n-1$ 个数字，然后再在其中选择一个非最大值的数作为重复，即 $\times (n-2)$ 。

接着，中间最大值已经放好了，重复数字也放好了，剩下的 $n-3$ 个数既可以放左边也可以放右边，所以还有 $2^{n-3}$ 种可能。

结论：答案为：$C^{n-1}_m\times (n-2)\times 2^{n-3}$。

------------

### Code

```cpp

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm> 
#include <cmath>

using namespace std;

typedef long long LL;

const int N = 3e5 + 10, mod = 998244353;

int n, m;
LL fac[N], inv[N];

LL qpow(LL a, LL b)
{
	LL res = 1;
	while (b)
	{
		if (b & 1) res = res % mod * a % mod;
		a = a % mod * a % mod;
		b >>= 1; 
	}
	return res;
	
}

LL C(int x, int y)
{
	LL z = fac[x] % mod * inv[y] % mod;
	return z % mod * inv[x - y] % mod;
}

void init(int M = 200000)
{
	fac[0] = 1;
	for (int i = 1; i <= M; i ++ ) fac[i] = fac[i - 1] % mod * i % mod;
	inv[M] = qpow(fac[M], mod - 2);
	for (int i = M - 1; i >= 0; i -- ) inv[i] = inv[i + 1] * (i + 1) % mod; 
}

int main()
{
	init();
	
	scanf("%d%d", &n, &m);
	if (n < 3) puts("0");
	else printf("%lld\n", 1LL * qpow(2, n - 3) % mod * C(m, n - 1) % mod * (n - 2) % mod);
	
	return 0;
}
```







---

## 作者：Nuisdete (赞：1)

一共有 $n - 1$ 个不同的数和一对相同的数。

那么有 $\binom{m}{n - 1} \times (n - 2)$ 种不同的取 $n$ 个数的方案（最大值不能重复出现）。

然后考虑枚举最大值的位置，然后最大值和相同的数的位置就已经确定了，那么考虑把一些数放在最大值左面，也就是 $\binom{n - 3}{i - 2}$ 种方案，$i$ 为枚举的位置。

所以最后的答案就是 $\sum_{i = 1}^n \binom{m}{n - 1} \times (n - 2) \times \binom{n - 3}{i - 2}$。

---

## 作者：nullqtr_pwp (赞：0)

显然所有的取值方案都可以离散化成 $1,2,\cdots,n-1$。

取值有 $n-1$ 个。而我们备选的有 $m$ 个，显然从用哪些值上有 $\begin{pmatrix}
 m\\
n-1
\end{pmatrix}$ 种。

不妨设取出来的数就是 $1,2,\cdots,n-1$。那么可能出现重复的数就是 $1,2,\cdots,n-2$（最大值不能重复，因为是严格递增递减）。

对于这个单峰序列，我们称单调递增那部分为左部分，单调递减那部分为右部分，不考虑最大值。

设重复的数是 $i$，显然左右部分都要出现。那么每个不为 $i$ 且不为 $n-1$ 的数，由于只出现一次，所以需要从左右部分二选一，显然是 $2^{n-3}$ 种。

重复的可能是 $1,2,\cdots,n-2$，所以答案是
$$\begin{pmatrix}
 m\\
n-1
\end{pmatrix}(n-2)2^{n-3}$$

---

## 作者：cqbzlwz (赞：0)

### 1.分析
#### (1).前置
通过读题可以得知，这是一道计数题。

对于一个序列当中，最特殊的就是最大值和相同的值。

那么根据长期以来的做题经验，我们可以找出每一位的可能，用乘法原理相乘得到答案。并且，我们要优先处理有限制的、特殊的数，保证答案的正确性。因为有限制的数会对其它数造成影响，所以先计算它们比较简便。
#### (2).计算

由于每个元素的取值范围是 $[1,m]$，而一共需要 $n-1$ 个不同的值（因为有且只有一对数相同），因此对于取值有 $\dbinom{m}{n-1}$ 种方案。

此时最大值已确定，所以只要把其他元素放好，它自然就有了个位置。

再考虑重复的那个数。因为除去最大值不能选（不然必须和它本身相邻，而这不**严格单调**），其它的都能选，所以有 $n-1-1$ 种选择。

接下来，我们还剩 $n-3$ 个值。它们每一个都可以选择放在最大值左边或右边，因此有 $2^{n-3}$ 种选择。

确定了每个元素在最大值左边或右边，自然可以和重复的那个元素组成一个伪合法序列，此时把最大值塞进去即可。由于每一步互不影响，可以用乘法原理得出答案。

#### (3).代码
喜提[最优解](https://www.luogu.com.cn/record/82989719)
![](https://cdn.luogu.com.cn/upload/image_hosting/1o81xsli.png)

~~(话说 0ms,0B 是什么鬼，怕不是 CF 远程评测特性)~~

```cpp
#include <stdio.h>
#pragma GCC optimize(2, 3, "Ofast")
int n, m;
long long ans = 1, num = 1;
const int mod = 998244353;
inline int qpow(int x, int y) {
	long long num = 1;
	while (y) {
		if (y & 1) num = num * x % mod;
		y >>= 1, x = 1ll * x * x % mod;
	}
	return num;
}
int main() {
	scanf("%d%d", &n, &m);
	if (n == 2) {
		putchar('0');
		return 0;
	}
	for (int i = n; i <= m; ++i) ans = ans * i % mod;
	for (int i = 1; i <= m - n + 1; ++i) num = num * i % mod; 
	printf("%d\n", ans * qpow(num, mod - 2) % mod * (n - 2) % mod * qpow(2, n - 3) % mod);
	return 0;
}
```

---

## 作者：墨舞灵纯 (赞：0)

### 题意

求满足如下条件的长度为 $n$ 的序列 $a$ 的个数：

- $\forall 1 \leq i \leq n$ ，都有 $1 \leq a_i \leq m$ 。 
- $a$ 中存在且仅存在一对相同的元素。
- 存在一个位置 $p$ ，使得 $a_1 \sim a_p$	为严格单增序列，$a_p \sim a_n$ 为严格单减序列。即 $\forall 0 < j < p$ ，都有 $a_{j} < a_{j + 1}$ ，且 $\forall p \leq j < n$ ，都有 $a_j > a_{j + 1}$

$1 \leq n, m \leq 2 \times 10^5$


答案对 $998244353$ 取模。

### 题解

我们发现按照给定条件只有一个数重复，于是只有两个一样的数是必须一左一右固定放的，中间一个最大值是固定在中间的，那么剩下的 $n-3$ 个互不相同的数可以自由选择放左边右边，一定会构造出一组合法解，这样的选择是 $2^{n-3}$ 。

考虑有 $n-1$ 个互不相同的数，它们的值域是 $[1,m]$ ，那么选择方案就是 $\binom{m}{n-1}$ ，重复的那个数要选择不同于最大值的一个数，所以方案是 $n-2$ 。

总方案就是 $2^{n-3} \times \binom{m}{n-1} \times (n-2)$ 。

### 代码

```cpp
	if(n==2) return puts("0"),0;
	for(int i=(fac[0]=fac[1]=ifac[0]=ifac[1]=inv[0]=inv[1]=1)+1;i<=m;++i) fac[i]=(0ll+fac[i-1])*i%P,inv[i]=(0ll+inv[P%i])*(P-P/i)%P,ifac[i]=(0ll+ifac[i-1])*inv[i]%P;
	printf("%d",(0ll+ksm(2,n-3))*C(m,n-1)%P*(n-2ll)%P);
   

---

## 作者：Unnamed114514 (赞：0)

注意到序列中有 $n-1$ 个数，所以说我们可以先从 $m$ 个数中选择 $n-1$ 个数放入序列中，然后再选择一个非最大值的数，所以 $C_m^{n-1}\times(n-2)$。

最大的已经确定了，两个相同的因为要满足单调性，只能放在最大值两边。剩下的 $n-3$ 个数可以放在最大值左边和最大值右边，一共两种状态，所以答案就是 $2^{n-3}$。

乘法原理，答案就是 $C_m^{n-1}\times(n-2)\times2^{n-3}$。

---

