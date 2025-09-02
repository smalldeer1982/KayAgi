# PAGAIN - Prime Again

## 题目描述

[English](/problems/PAGAIN/en/) [Vietnamese](/problems/PAGAIN/vn/)In this problem, you have to find the nearest prime number smaller than N. (3 <= N <= 2^32)

## 样例 #1

### 输入

```
3
5 
10
17```

### 输出

```
3
7
13```

# 题解

## 作者：ioker (赞：19)

## [题目传送门](https://www.luogu.com.cn/problem/SP3587)

## 题目大意：
求距离每个数最近且比他小的最大素数。

## 前置芝士：
Miller Rabin(如果不会的话，可以看看这个 [Miller Rabin](https://dpkajj.blog.luogu.org/solution-sp288))

## 思路
我们可以先预处理一部分，在用极短的时间内判断素数，那么我们就可以从 n 开始往下枚举直到当前数是质数。

代码比较暴力：
```cpp
#include <stdio.h>
#include <ctype.h>
#define int long long
#define N 10000007
inline int read() {
    int n = 0;
    bool m = 1;
    char c = getchar();

    while (!isdigit(c)) {
        if (c == '-')
            m = 0;

        c = getchar();
    }

    while (isdigit(c)) {
        n = (n << 1) + (n << 3) + c - '0';
        c = getchar();
    }

    return m ? n : -n;
}
int prime[N], tot, phi[N];
bool v[N];
inline void get() {
    for (int i = 2; i < N; i++) {
        if (!v[i])
            prime[++tot] = i;

        phi[i] = tot;

        for (int j = 1; j <= tot && prime[j]*i < N; j++) {
            v[prime[j]*i] = 1;

            if (!(i % prime[j]))
                break;
        }
    }
}
inline int power(int n, int m, int p) {
    int ans = 1;

    while (m) {
        if (m & 1)
            ans = (__int128)ans * n % p;

        m >>= 1;
        n = (__int128)n * n % p;
    }

    return ans;
}
inline bool millerrabin(int n, int m) {
    int k = n - 1;

    while (k) {
        int a = power(m, k, n);

        if (a != n - 1 && a != 1)
            return 0;

        if (k & 1 || a == n - 1)
            return 1;

        k >>= 1;
    }

    return 1;
}
int tx[4] {0, 2, 7, 63};
inline bool pri(int n) {
    if (n < 2)
        return 0;

    for (int i = 1; i <= 3; i++) {
        if (n == tx[i])
            return 1;

        if (!millerrabin(n, tx[i]))
            return 0;
    }

    return 1;
}
inline int ans(int n) {
    if (n < N)
        return prime[phi[n]];

    for (int i = n;; i--)
        if (pri(i))
            return i;

    return -1;
}
signed main() {
    get();
    int t = read();

    while (t--) {
        int n = read();
        printf("%lld\n", ans(n - 1));
    }

    return 0;
}
```

---

## 作者：shucai (赞：3)

思路：

这题当然考的是质数判断了，可考的当然不是试除法，考的是 Millerrabin 。

这种算法也是一种判断质数的方法，主要是依靠费马小定理：

$$a^{p-1} \equiv1\pmod{p}$$

其中 $p$ 为质数。

还有二次探测定理：

$$a^2 \equiv 1 \pmod{p},a=\pm1$$


其中 $p$ 为质数。

证明就不给了，这上面两个定理结合起来，就可意判断一个数 $p$ 是否为质数了。

将 $p-1$ 分解为 $2^k\times t$ 的形式。

任意取一数 $a$ ，计算出 $a^t \pmod p$ 的值，并使它乘上自己（一直乘到 $k$ 次，就成了 $a^{p-1}$）。

如果我们某一次发现当前数字 $b\pmod p = 1$ ，并且之前的数 $c \pmod p \ne \pm 1$，则该数为合数（即二次探测定理）。

但我们一直乘到 $k$ 次时，发现这个数 $b\pmod p \ne 1$ ，则该数为合数（即费马小定理）。

这样 millerrabin 主要流程就写完了。


millerrabin 摸板题：[SP288](https://www.luogu.com.cn/problem/SP288)

现在回来看这题：显然从 $n-1$ 开始暴力 millerrabin 往下判断就行。

但是本题规模过大，要先把一部分先筛出来，我筛到了 $10^6$。

但是还有几点要注意：

1. 在计算幂运算时，需用快速幂。


2. 在某些地方要用 __128 （可能会爆精度）。

那么这题就写完了。

## code

```cpp
#include <bits/stdc++.h>
#define int long long
#define _ 100005
using namespace std;
bool vis[_];
int prime[_], number[_], pok[5] = {0, 2, 7, 63};
int cnt;
int read() {
    int n = 0;
    bool m = 1;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-')
            m = 0;
        c = getchar();
    }
    while (isdigit(c)) {
        n = (n << 1) + (n << 3) + c - '0';
        c = getchar();
    }
    return m ? n : -n;
}
void get()
{
  for (int i = 2; i < _; ++ i)
    {
      if (!vis[i])
        prime[++ cnt] = i;
      number[i] = cnt;
      for (int j = 1; j <= cnt && prime[j] * i < _; ++ j)
        {
          vis[prime[j] * i] = 1;
          if (!(i % prime[j])) break;
        }
    }
}
int Quick_pow(int k, int c, int p)
{
  int ans = 1;
  while (c)
    {
      if (c & 1)
        ans = (__int128)ans * k % p;
      c >>= 1;
      k = (__int128)k * k % p;
    }
  return ans;
}
bool millerrabin(int n, int m)
{
  int k = n - 1;
  while (k)
    {
      int v = Quick_pow(m, k, n);
      if (v != n - 1 && v != 1)
        return 0;
      if (k & 1 || v == n - 1)
        return 1;
      k >>= 1;
    }
  return 1;
}
bool check(int n)
{
  if (n < 2) return 0;
  for (int i = 1; i <= 3; ++ i)
    {
      if (n == pok[i]) return 1;
      if (!millerrabin(n, pok[i]))
        return 0;
    }
  return 1;
}
int find(int n)
{
  if (n < _)
    return prime[number[n]];
  for (int i = n;; -- i)
    {
      if (check(i)) return i;
    }
  return -1;
}
signed main()
{
  get();
  int T;
  T = read();
  while (T --)
    {
      int n;
      n = read();
      printf("%lld\n", find(n - 1));
    }
  return 0;
}

```




---

## 作者：Kreado (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/SP3587)

#### 思路

用欧拉筛算出 $10^5$ 内的所有质数再标记，当 $n\leq 10^5$ 时直接输出，当 $n \geq 10^5$ 用 Miller_Rabin 算法从大到小枚举数字，当为质数时输出退出即可。

#### 分析

可以看一下我的[辣鸡博文](https://www.luogu.com.cn/blog/zqh158233/qian-tan-zhi-shuo)。

#### 易错点

1. $ksm$ 函数中可能会超 long long ，记得用  \_\_int128 。

2. 我用了快速幂和龟速乘

#### 贴贴代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define re register
#define lll __int128
using namespace std;
ll t,n;
const ll Maxn=1e5;
ll prime[Maxn],cnt,ji[Maxn];
bool isprime[Maxn];
inline ll qread(void){
	ll x=0,f=1;char ch;
	while((ch=getchar())<'0'||ch>'9') if(ch=='-') f=-1;x=(ch^48);
	while((ch=getchar())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
inline void Euler(ll n){
	isprime[1]=true;isprime[0]=true;
	for(re ll i=2;i<=n;i++){
		if(!isprime[i])
			prime[++cnt]=i;
		ji[i]=cnt;
		for(re ll j=1;j<=cnt&&prime[j]*i<=n;j++){
			isprime[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	return ;
}
ll Test[5]={0,2,7,41,61};
inline ll mul(ll a,ll b,ll mod){
	ll ans=0;
	while(b){
		if(b&1)
			ans=(ans+a)%mod;
		a=(a+a)%mod;
		b>>=1;
	}
	return ans;
}
inline ll ksm(ll a,ll b,ll mod){
	ll ans=1;
	while(b){
		if(b&1)
			ans=(lll)ans*a%mod;
		a=(lll)a*a%mod;
		b>>=1;
	}
	return ans;
}
inline bool Isprime(ll x){
	if(x==1)
		return false;
	ll k=0,t=x-1;
	while((t&1)^1)
		k++,t>>=1;
	for(re ll i=1;i<=4;i++){
		if(x==Test[i])
			return true;
		ll a=ksm(Test[i],t,x),Next=a;
		for(re ll j=1;j<=k;j++){
			Next=mul(a,a,x);
			if(Next==1&&a!=1&&a!=x-1)
				return false;
			a=Next;
		}
		if(a!=1)
			return false;
	}
	return true;
}
inline ll Min_num(ll n){
	if(n<Maxn) return prime[ji[n]];
	for(re ll i=n;;i--)
		if(Isprime(i)) return i;
	return 0;
}
int main(){
	t=qread();
	Euler(Maxn);
	while(t--){
		n=qread();
		printf("%lld\n",Min_num(n-1));
	}
	return 0;
}
```


---

## 作者：Leasier (赞：2)

前置芝士：[Miller-Rabin](https://oi-wiki.org/math/prime/#miller-rabin)

考虑先预处理出部分较小的质数（我预处理到了 $< 10^7$），对于这部分质数直接输出（即 $p_{\pi(n)}$），否则暴力从 $n$ 往下查找。

考虑 $n$ 范围较大，我采用了 Miller-Rabin 从 $n - 1$ 开始往下暴力找质数。时间复杂度为 $O(T \log^2 n \ln n)$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;
typedef __int128 lll;

const int N = 1e7 + 7, M = 3;
int prime[N], pi[N], test_prime[M + 7] = {0, 2, 7, 61};
bool p[N];

inline int init(){
	int cnt = 0;
	p[0] = p[1] = true;
	for (register int i = 2; i < N; i++){
		if (!p[i]) prime[++cnt] = i;
		pi[i] = cnt;
		for (register int j = 1; j <= cnt && i * prime[j] < N; j++){
			p[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
	return cnt;
}

inline ll quick_pow(ll x, ll p, ll mod){
	ll ans = 1;
	while (p){
		if (p & 1) ans = (lll)ans * x % mod;
		x = (lll)x * x % mod;
		p >>= 1;
	}
	return ans;
}

inline bool miller_rabin(ll n, ll k){
	ll nd = n - 1, m = nd;
	while (m){
		ll x = quick_pow(k, m, n);
		if (x != 1 && x != nd) return false;
		if ((m & 1) == 1 || x == nd) return true;
		m >>= 1;
	}
	return true;
}

inline bool is_prime(ll n){
	if (n < 2) return false;
	for (register int i = 1; i <= M; i++){
		if (n == test_prime[i]) return true;
		if (!miller_rabin(n, test_prime[i])) return false;
	}
	return true;
}

inline ll get_last_prime(ll n, int cnt){
	if (n < N) return prime[pi[n]];
	for (register ll i = n; ; i--){
		if (is_prime(i)) return i;
	}
	return -1;
}

int main(){
	int t, cnt;
	scanf("%d", &t);
	cnt = init();
	for (register int i = 1; i <= t; i++){
		ll n;
		scanf("%lld", &n);
		printf("%lld\n", get_last_prime(n - 1, cnt));
	}
	return 0;
}
```

---

## 作者：EXR_FAL (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/SP3587)

#### 前置芝士：`Miller_Rabin` 素性测试 & 欧拉筛

### 大致思路

~~因为最近练习到了 `Miller_Rabin`，看什么都像 `Miller_Rabin`。~~

事实上这个题一眼看过去，核心问题就是**判质数**。

最朴素的思路就是从 `n-1` 开始**枚举**然后**判定**是否为质数。

当然这样做会 `TLE` 到飞起，于是考虑优化，从两个方面下手：

1. 判质数，最明显可以优化的地方。
    

   这个地方 $O(\sqrt{n})$ 的试除法肯定是不能用的，算上 $T\le10^{5}$ 的数据会超时到飞起。\
   是的，这时候就要使用 `Miller-Rabin` 素性测试了。

   而在不考虑乘法的复杂度时，对数 `n` 进行 `k` 轮测试的时间复杂度是 $O(k \log n)$，可以接受。

   2\. 即使使用 `Miller-Rabin` 后，但仍然会超时，那么考虑预处理较小的质数直接 $O(1)$ 查询，直接上欧拉筛，线性 $O(n)$ 预处理。

优化后即可通过此题。

下面贴代码\
又及：在某些地方要用 `__int128`（可能会爆精度）。~~我比较懒，全开了 `__int128`~~。

```cpp
Ciallo～(∠・ω< )⌒★

#include<bits/stdc++.h>
using namespace std;

#define ll __int128
inline ll read(){
    ll x=0,flag=1;
	char ch=getchar();
    while(!isdigit(ch)){
		if(ch=='-') flag=-1;
		ch=getchar();
	}
    while(isdigit(ch)){
    	x=x*10+(ch^48);
		ch=getchar();
	}
	return x*flag;
}
void out(ll x){
    if(x<0) putchar('-'),x=-x;
    if(x<10) putchar(x+'0');
    else out(x/10),putchar(x%10+'0');
}

const ll N=1e7+114;

ll T,n;

// quick mul & pow 龟速乘和快速幂
ll muler(ll a,ll b,ll mod){
    ll c=(ll)a/mod*b;
    ll res=(ll)a*b-(ll)c*mod;
    return (res+mod)%mod;
}
ll power(ll a,ll n,ll mod){
    ll res=1;
    while(n){
        if(n&1) res=muler(res,a,mod);
        a=muler(a,a,mod);
        n>>=1;
    }
    return res;
}

//Miller_Rabin 素性测试
bool Miller_Rabin(ll n){
    if(n<3||n%2==0) return n==2;
    ll u=n-1,t=0;
    while(u%2==0) u/=2,++t;
    ll ud[]={0,2,7,63};
    for(ll a:ud){
        ll v=power(a,u,n);
        if(v==1||v==n-1||v==0) continue;
        for(ll j=1;j<=t;j++){
            v=muler(v,v,n);
            if(v==n-1&&j!=t){v=1;break;}
            if(v==1) return 0;
        }
        if(v!=1) return 0;
    }
    return 1;
}

ll Ca[N];//Ca[]标记最近的最小质数的下标

// Euler Sieve 线性筛
ll pri[N],cnt;
bool not_pri[N];
void Sieve(ll N){
	not_pri[1]=1;
	for(ll i=2;i<=N;i++){
		if(!not_pri[i])
			pri[++cnt]=i;
		Ca[i]=cnt;
		for(ll j=1;j<=cnt&&i*pri[j]<=N;j++){
			not_pri[i*pri[j]]=1;
			if(i%pri[j]==0) break;
		}
	}
}

//Ciallo~ 处理
ll solve(ll n){
	if(n<=N) return pri[Ca[n]];
	for(ll i=n;i>=1;i--)
		if(Miller_Rabin(i))
			return i;
	return -1;
}

int main(){
	
	Sieve(N-1);
	
	T=read();
	while(T--){
		n=read();
		out(solve(n-1));
		puts("");
	}

	return 0;
}


```

---

