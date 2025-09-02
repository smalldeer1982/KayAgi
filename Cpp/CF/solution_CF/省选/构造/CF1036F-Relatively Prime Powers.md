# Relatively Prime Powers

## 题目描述

Consider some positive integer $ x $ . Its prime factorization will be of form $ x = 2^{k_1} \cdot 3^{k_2} \cdot 5^{k_3} \cdot \dots $

Let's call $ x $ elegant if the greatest common divisor of the sequence $ k_1, k_2, \dots $ is equal to $ 1 $ . For example, numbers $ 5 = 5^1 $ , $ 12 = 2^2 \cdot 3 $ , $ 72 = 2^3 \cdot 3^2 $ are elegant and numbers $ 8 = 2^3 $ ( $ GCD = 3 $ ), $ 2500 = 2^2 \cdot 5^4 $ ( $ GCD = 2 $ ) are not.

Count the number of elegant integers from $ 2 $ to $ n $ .

Each testcase contains several values of $ n $ , for each of them you are required to solve the problem separately.

## 说明/提示

Here is the list of non-elegant numbers up to $ 10 $ :

- $ 4 = 2^2, GCD = 2 $ ;
- $ 8 = 2^3, GCD = 3 $ ;
- $ 9 = 3^2, GCD = 2 $ .

The rest have $ GCD = 1 $ .

## 样例 #1

### 输入

```
4
4
2
72
10
```

### 输出

```
2
1
61
6
```

# 题解

## 作者：KKarshilov (赞：11)

题目要求的性质貌似很难直接维护啊……

我们考虑反着做这道题：n-不合法数的个数-1

对于一个不合法数，其质因子的$gcd$为$2$及以上的整数

所以说一个不合法的数$a$必然是某个数$k$的$i$次幂，即：
$$a=k^i$$

考虑构造，但是$n$的范围是$1e18$，所以直接构造所有完全平方数会T

那么构造所有$3$次方及以上的数即可，在此过程中要排除所有的完全平方数

假设最终构造出来的数组为f，将其排序，对于每个n只需在其中二分一个大于n且最小的数的位置，假设为pos，那么$2,3,4,....n$中就有$pos-1$个数是不合法的(除了完全平方数)，然而还要-1，所以直接减去pos

对于完全平方数，直接减去sqrt(n)即可

```cpp
#include <bits/stdc++.h>
using namespace std;

#define LL long long
#define db double

const int MAXN = 300300;
const int MAXE = 400400;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    int ch = getchar();
    bool fg = false;
    for (x = 0; !isdigit(ch); ch = getchar()) {
        if (ch == '-') {
            fg = true;
        }
    }
    for (; isdigit(ch); ch = getchar()) {
        x = x * 10 + ch - '0';
    }
    if (fg) {
        x = -x;
    }
}

LL T, n;
LL f[MAXN * 100], cnt;

const LL N = 1000LL * 100000LL * 100000LL * 100000LL;

bool chk(LL x) {
    LL p = (LL) sqrt(x);
    return p * p < x;
}

signed main() {
    for(LL i = 2; i <= 1000000; i++) {
        LL x = i * i;
        while(x <= N / i) {
            x *= i;
            if(chk(x)) f[++cnt] = x;
        }
    }
    sort(f + 1, f + cnt + 1); 
    cnt = (int) (unique(f + 1, f + cnt + 1) - f - 1);
    read(T);
    while(T--) {
        read(n);
        printf("%I64d\n", n - (LL) (upper_bound(f + 1, f + cnt + 1, n) - f - 1) - (LL)sqrt(n));
    }
    return 0;
} 
```


---

## 作者：Echidna (赞：9)

感觉其他的题解讲的稍微有一点不细节啊……那我来补一发题解吧。

首先看到 `gcd` 就基本可以往莫比乌斯反演的套路上靠。

首先设 $f(x)$ 为 $[2,n]$ 内质因子指数的 $\gcd$ 为 $x$ 的数的个数，  
设 $g(x)$ 为 $[2,n]$ 内质因子指数的 $\gcd$ 为 $x$ 的**倍数**的数的个数。

那么我们有如下关系：

$$g(x)=\sum_{x|d}f(d)$$

注意，这里的形式需要用莫比乌斯反演的第二种形式来转化。

$$f(x)=\sum_{x|d}\mu(\frac{d}{x})g(d)$$

得到了这个形式之后，我们就可以快速计算了。

考虑如何快速地计算函数 $g$ 在某一个点的值。容易发现，如果一个数 $x$ 所有质因子的指数的 $\gcd$ 为 $k$ ，我们可以把 $x$ 表示为 $b^k$ ，其中 $b$ 为一个非负整数。

于是我们发现， $g(x)$ 其实就是求有多少个正整数的 $x$ 次方小于 $n$ 。考虑到我们不能统计上 $1$ ，于是我们需要把最后算出来的结果减一，于是 $g(x)$ 就可以表示为 $\lfloor\sqrt[x]{n}\rfloor-1$ 。

我们最后要求出来 $f(1)$ ，最终答案就是 

$$f(1)=\sum_{x|d}\mu(\frac{d}{x})g(d)=\sum_{d=1}^{\log_2 n}\mu(d)g(d)=\sum_{d=1}^{\log_2 n}\mu(d)\left(\left\lceil
\sqrt[d]{n}\right\rceil-1\right)$$

这样的话答案就能求出来了，但是丧心病狂的出题人在出题的时候没考虑到 `pow` 函数在算小数次幂的时候可能会有大于 $1$ 的误差，所以我们在用 `pow` 算 $d$ 次方根的时候需要加加减减来防止精度误差。

$\text{Code:}$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
using namespace std;
#define ll long long
#define PII pair<int,int>
#define mp make_pair
const int N=100,M=6e3;
ll prime[N],mu[N],cnt;
bool isprime[N];
#define rg register 
ll read(){
    rg ll x=0,f=1;rg char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c))x=x*10+c-'0',c=getchar();
    return x*f;
}
inline void sieve(int n){
    memset(isprime,1,sizeof(isprime));
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(isprime[i])
            prime[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            isprime[i*prime[j]]=0;
            if(i%prime[j]==0)break;
            mu[i*prime[j]]=-mu[i];
        }
    }
}
#define double long double 
ll n;
double qpow(double a,ll b){
    if(b==1)return a;
    if(b%2==1)return qpow(a,b-1)*a;
    rg double temp=pow(a,b/2);
    return temp*temp;
}
void solve(){
    n=read();
    rg ll ans=0;
    for(rg int i=1;i<=60;i++){
        rg ll temp=(ll)(pow(n,1.l/i))+1;
        while(qpow(temp,i)>n)temp--;
        ans+=mu[i]*(temp-1);
    }
    printf("%lld\n",ans);
}
int main(){
    rg int t=read();
    sieve(100);
    while(t--)solve();
}
```







---

## 作者：Caiest_Oier (赞：6)

# [CF1036F](https://www.luogu.com.cn/problem/CF1036F)  

对于一个数 $x$，我们令 $w_x$ 表示最大的一个 $k$ 使得存在一个整数 $b$ 满足 $b^k=x$。而我们要求的就是 $\sum_{i=2}^{n}{[w_i=1]}$。   

我们发现，如果要计算所有 $x|w_k$ 的数量，那么答案就是 $\lfloor ^x\sqrt{n}\rfloor-1$。容易发现可以套一个莫比乌斯函数作为系数的容斥上去，这样就只会保留 $w_k=1$ 的数量了。   

具体的，$ans=\sum_{i=1}^{inf}\mu(i)\times(\lfloor ^i\sqrt{n}\rfloor-1)=\sum_{i=1}^{\log n}\mu(i)\times(\lfloor ^i\sqrt{n}\rfloor-1)$。    

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define MAX 1000000000000000000ll
using namespace std;
int t,n,ans,k1,k2,miu[1003];
int fsp(int X,int Y){
	int ret=1,bse=X;
	while(Y){
		if(Y&1){
			if(ret>((MAX-1+bse)/bse))return MAX+1;
			ret*=bse;
		}
		Y>>=1;
		if(!Y)break;
		if(bse>1000000000ll)return MAX+1;
		bse*=bse;
	}
	return ret;
}
bool isp(int X){
	for(int i=2;i*i<=X;i++){
		if(X%i==0)return false;
	} 
	return true;
}
int calc(int X){
	for(int i=2;i*i<=X;i++){
		if(X%(i*i)==0)return 0;
	}
	int ret=1;
	for(int i=2;i<=X;i++){
		if(X%i!=0)continue;
		if(isp(i))ret*=-1;
	}
	return ret;
}
signed main(){
	for(int i=1;i<=100;i++)miu[i]=calc(i);
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		ans=0;
		for(int i=1;;i++){
			k1=floor(pow(n,(1.0/((double)(i)))));
			while(fsp(k1+1,i)<=n)k1++;
			while(fsp(k1,i)>n)k1--;
			ans+=miu[i]*(k1-1);
			if(k1==1)break;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：NATO (赞：2)

提供一种相当抽象的做法。

### 思路：

发现合法数不好直接统计，考虑统计不合法的数。

按照题意，我们可以发现，一个数 $x$ 是不合法的当且仅当存在 $y$，使得 $y^k=x$ 且 $k\ge2$。

那么考虑如何统计不合法的数。

考虑枚举 $k$，为了防止重复计算某一个数，我们钦定一个数 $x$ 只统计满足 $y^k=x$ 且 $k$ 值最大时的结果，那么当我们统计所有 $\le x$ 的不合法数，枚举到 $k=i$ 时对于多少个数此时的 $k$ 是最大的呢？

我们从数 $x$ 的 $k$ 次方根入手考虑，可以发现如果 $\sqrt[k]{x}$ 是一个存在 $y'$，使得 $y'^{k'}=\sqrt[k]{x}$ 且 $k'\ge2$ 的数的话，那么 $y'^{kk'}=x$，此时 $k$ 对于 $x$ 就不是满足条件的那个最大数了，反之则是。把 $k$ 不是一个最大数的条件和我们的不合法的数的定义一比较，我们惊讶地发现当 $k=i$ 时，我们所需要统计数的个数即是 $\le\sqrt[k]{x}$ 的所有合法数的个数！递归计算即可。

实现上由于在 $x$ 较小时减小速度较慢，可以预处理一下 $1000000$ 以内的答案访问到时直接调用来减小时间复杂度。

时间复杂度上由于我们预处理了 $1000000$ 的答案，那么递归最多进入一个二次根号，其余直接返回，而进入二次根号后必然也是计算后直接返回的，再加上本题丧心病狂地卡精度，在开根时笔者不得不使用了一个快速幂来对开根结果进行微调，所以可以认为复杂度为：$O(v\log v^2+T\log n^2)$，其中 $v$ 为预处理的范围，可以慢但是稳定地通过本题。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN=1000000;
int p[100005],cnt,mp[1000005];
bool vis[1000005];
set<int>s;
int sum[1000005],res[1000005];
void init()
{
	for(ll i=2;i<=MAXN;++i)
	{
		if(!vis[i])
		p[++cnt]=i,mp[i]=i;
		for(ll j=1;j<=cnt&&p[j]*i<=MAXN;++j)
		{
			vis[p[j]*i]=1;
			if(!mp[p[j]*i])
			mp[p[j]*i]=p[j];
			if(i%p[j]==0)break;
		}
	}
}
bool check(ll a)
{
	s.clear();
	while(a!=1)
	{
		++sum[mp[a]];
		s.insert(mp[a]);
		a/=mp[a];
	}
	int res=0;
	for(auto it:s)
	{
		if(!res)res=sum[it];
		else res=__gcd(sum[it],res);
		sum[it]=0;
	}
	return res!=1;
}
ll t,n;
long double ksm(long double a, int n)
{
	long double res=1.0;
	while(n)
	{
		if(n&1)res*= a;
		a*=a;
		n>>=1;
	}
	return res;
}
ll solve(ll n)
{
	if(n<=MAXN)return res[n];
	ll rs=0;
	for(ll gt,i=2;;++i)
	{
	(gt=__builtin_powl(n,1.00/i)+2);
	while(ksm(gt,i)>n) --gt;
	if(gt==1)break;
	if(gt<=MAXN)
	rs+=res[gt];
	else
	rs+=solve(gt);	
	}
	return n-rs-1;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	init();
	for(ll i=2;i<=1000000;++i)
	{
		if(check(i))
		res[i]=res[i-1];
		else
		res[i]=res[i-1]+1;
	}
	cin>>t;
	while(t--)
	{
		cin>>n;
		cout<<solve(n)<<'\n';
	}
} 
```

---

## 作者：teylnol_evteyl (赞：2)

## 题目分析

对于一个不合法的数 $x(x\ge 2)$，设 $x=\prod p_i^{r_i}$，令 $g=\gcd(r_1,r_2,\ldots,r_k)$，则 $x=\left(\prod p_i^{r_i/g}\right)^g$，所以 $x$ 是一个正整数的 $g$ 次方。

所以可以枚举上文的 $g$，把每一类不合法方案排除掉，就是答案。

设 $f(i)$ 表示 $2$ 到 $n$ 中 $i$ 次方数的个数，根据容斥原理，最终答案为：

$$f(1)-\sum_{i\ge1,i\in\text{prime}}f(i)+\sum_{i\ge1,j\ge1,i\ne j,i\in\text{prime},j\in\text{prime}}f(i \cdot j) \cdots $$

即总数减奇数个质数相乘的 $f$ 值，加偶数个质数相乘的 $f$ 值。

用莫比乌斯函数 $\mu$ 可以更简单地表示这个式子：

$$ \quad\sum_{i\ge1}\mu(i) \cdot f(i) $$

$f(i)$ 的计算也很简单：

$$f(i)= \sqrt[i]n - 1 $$

但是这里有个细节问题：如果直接用 c++ 的 pow 函数开方，会出现精度问题，影响答案，这是这道题一个很恶心的地方。具体解决方案如下：

1. 对于求 $\sqrt[k]n$，初始用 pow 函数计算出比 $\sqrt[k]n$ 大的值，具体地，将用 pow 算出的值加 2。

2. 设刚才算出的值为 $t$，$t^k>n$ 则将 $t$ 减 1。

3. 求 $t^k$ 用快速幂，中间过程的变量用 long double 存。

## 示例代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long double LD;
typedef long long LL;

const int N = 70;

int prime[N], cnt;
int mu[N];
bool st[N];

void init()
{
	mu[1] = 1;
	for(int i = 2; i < N; i ++ )
	{
		if(!st[i])
		{
			prime[ ++ cnt] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= cnt && i * prime[j] < N; j ++ )
		{
			int x = i * prime[j];
			st[x] = true;
			if(i % prime[j] == 0)
			{
				mu[x] = 0;
				break;
			}
			mu[x] = -mu[i];
		}
	}
}

LD ksm(LD a, int n)
{
	LD res = 1.0;
	while(n)
	{
		if(n & 1) res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

LL solve(int k, LL n)
{
	if(k == 1) return n - 1;
	LL q = (LL)pow(n, 1.0L / k) + 2;
	while(ksm(q, k) > n) q -- ;
	return q - 1;
}

int main()
{
	init();
	int T;
	scanf("%d", &T);
	while(T -- )
	{
		LL n, res = 0;
		scanf("%lld", &n);
		
		for(int i = 1; i <= 60; i ++ )
			if(mu[i])
				res += mu[i] * solve(i, n);
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：cosf (赞：1)

## [CF1036F](https://codeforces.com/contest/1036/problem/F)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1036F)

---

## 思路

我们可以发现，所有不合法的数一定是某个整数的 $\ge 2$ 次方。

于是我们可以令 $d_in$ 表示 $2$ 到 $n$ 中 $i$ 次方数的个数。根据容斥原理，答案就是

$$(n-1) - \sum_{i \in P}f_in + \sum_{i, j \in P, i \not= j}f_in - \dots$$

其中 $P$ 为质数集合。

注意到 $10^{18}$ 以内次数最大的是 $2^{60}$，所以 $P$ 的最大值到 $61$ 就可以了。将这个式子展开，可以得到：（$n-1 = f_1n$）

$$
f_1n - f_2n - f_3n - f_5n + f_6n \dots - f_{61}n
$$

或者

$$
1f_1n + (-1)f_2n + (-1)f_3n + 0f_4n + (-1)f_5n + \dots + (-1)f_{61}n
$$

系数数列为 $\{1, -1, -1, 0, -1, 1, -1, \dots\}$。其实这个就是莫比乌斯函数 $\mu$。~~以前我不会。~~

因为我们只需要求到 $\mu(61)$，所以也不需要什么线性筛之类的，直接强行算就可以了。

但是 $f_in = \sqrt[i]{n}-1$ 可能存在精度问题，所以我们用 `pow` 求完根之后，还要进行调整，具体参考代码。

参考代码
---

```cpp
/*
... 省略了部分内容
ll 为 long long，ld 为 long double
*/
// 这里一定要用 long double，否则会 wa on T3 or T5
ld qpow(ld n, ll k)
{
    ld r = 1;
    while (k)
    {
        if (k & 1)
        {
            r *= n;
        }
        n *= n;
        k >>= 1;
    }
    return r;
}

ll root(ll n, ll k)
{
    ll r = pow(n, ld(1) / k);
    while (qpow(r, k) <= n)
    {
        r++;
    }
    while (qpow(r, k) > n)
    {
        r--;
    }
    return r - 1;
}
int main()
{
    /*
    ... 省略暴力算 mu 内容
    */
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        ll res = 0;
        for (int i = 1; i < MAXN; i++)
        {
            res += mu[i] * root(n, i);
        }
        cout << res << endl;
    }
    return 0;
}
```


---

## 作者：orz_z (赞：1)

## 题目大意

对于一个数 $x$，当且仅当将其分解后各个质因数的指数的最大公约数为 $1$ 时，我们称这个数是合法的。

有 $T$ 组数据，对于每组数据，询问区间 $[2,n]$ 中合法的数的个数。

$1 \leq T \leq 10^5,2 \leq n \leq 10^{18}$。

## 解题思路

一个数不是合法的，也就是这个 $\gcd = k$。

此时这个数字一定可以被写成 $x=i^k$。

问题就变成 $2\sim n$ 中有多少个数能被表示成 $i^k$，其中 $k\ge 2$。

考虑莫比乌斯反演。

设 $f(k)$ 表示 $\gcd = k$ 的数的个数。

设 $F(k)$ 表示 $\gcd ∣ k$ 的数的个数。

显然，$F(k)=\sum\limits_{d|k}f(d)$。

根据莫比乌斯反演，我们有 $f(x)=\sum\limits_{x|d}\mu(d)F(\frac{d}{x})$。

然后，$F(d)=\lfloor x^{1/d}\rfloor-1$。

那么 $ans=f(1)=\sum\mu(d)F(d)$。

注意精度问题即可。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 100, M = 6e3;

ll prime[N], mu[N], cnt;

bool isprime[N];

ll read()
{
    ll x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    return x * f;
}

inline void js(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!isprime[i])
            prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++)
        {
            isprime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
            mu[i * prime[j]] = -mu[i];
        }
    }
}

#define double long double

ll n;

double qpow(double a, ll b)
{
    if (b == 1)
        return a;
    if (b % 2 == 1)
        return qpow(a, b - 1) * a;
    double temp = pow(a, b / 2);
    return temp * temp;
}

void solve()
{
    n = read();
    ll ans = 0;
    for (int i = 1; i <= 60; i++)
    {
        ll temp = (ll)(pow(n, 1.l / i)) + 1;
        while (qpow(temp, i) > n)
            temp--;
        ans += mu[i] * (temp - 1);
    }
    printf("%lld\n", ans);
}

signed main()
{
    int t = read();
    js(100);
    while (t--)
        solve();
}
```



---

## 作者：codwarm (赞：0)

# CF1036F Relatively Prime Powers 题解

*2400

最近在学容斥原理，来一个纯容斥无莫反的解法，非常优美。

题意：问 $[2,n]$ 有多少个数质因数分解后指数的 $\gcd$ 为 $1$。

# 做法

首先指数最大为 $60$。

令 $f_x$ 为指数的 $\gcd$ 为 $x$ 的数的个数。

一个数要是满足指数的 $\gcd$ 为 $x$，那么他必能化成
$$
\large \prod_i \left (p_i^{\frac{k_i}{x}}\right )^{x}
$$
的形式。

我们发现他必是一个数的 $x$ 次幂。

$[2,n]$ 中的数量即为 $\sqrt[x]{n}-  1$。

但这并不是最终答案，比如说 $64$ 是 $8^2$，但实际上它是 $2^6$，应该归属于 $f_6$ 的答案。

所以应该让 $f_x$ 减去所有 $\gcd$ 等于 $x$ 的倍数的数的个数。

因此有：
$$
\large f_i = \sqrt[x]{n}-1 - \sum_{j>i}^{j=ki} f_j
$$
这个式子是经典的调和级数，直接枚举就可以做到 $O(TV\log V)$ 的时间复杂度。

其中 $V=60$。

值得注意的是这个 $\sqrt[x]{n}$ 并不好算。

一种方法是先用 $\operatorname{pow}$ 算再用快速幂上下调整，足够通过本题。

```cpp
const int N = 65;

ll  n;
ll f[N];
ld ksm(ld a,ll b)
{
	ld res = 1;
	while (b)
	{
		if (b & 1) res = res * a;
		b >>= 1;
		a = a * a;
	}
	return res;
}
ll sqr(ll n,int k)
{
	ll res = (ll)pow((ld)n,ld(1)/k) + 5;
	while(ksm((ld)res,(ld)k) > n) res--;
	return res;
}
void solvemain()
{
	cin >> n;
	for (int i = 60;i >= 1;i--)
	{									
		f[i] = sqr(n,i)-1;
		for (int j = i+i;j <= 60;j+=i) f[i] -= f[j];
	}	
	cout << f[1] << endl; 
	
}
```

---

## 作者：fanfansann (赞：0)

**Solution**

可以一眼看出这题要用容斥原理，答案就是总数 $n-1$ 减去不合法的数的数量。

先来分析一下不合法的数有什么性质。

不合法的数的质因数分解后的数的次幂的 $\gcd>1$，例如 $x=2^4\times 3^2$，这样的数就是不合法的数，发现一旦 $\gcd ≠1$，我们就可以提出公因子，使得 $x$ 变成一个 $a^b$ 的形式。例如 $x=2^4\times 3^2=(2^2\times 3^1)^2$，所以不合法的数就是所有 $a^b$ 的形式的数，那么显然 $[2,n]$ 中，$a^2$ 的数一共有 $\lfloor\sqrt{n}-1)\rfloor$ 个（减去不在范围内的 $1$） $a^3$ 的数一共有 $\lfloor^{3}\sqrt{n}-1\rfloor$，一次类推。我们使用容斥原理，奇加偶减，加上$a^2$ 的数，$a^3$ 的数，$a^5$ 的数，$\cdots$，减去被算了两次的 $a^{2\times 3}$ 的数，$\cdots$，我们要减去这个值，奇减偶加，显然系数就是莫比乌斯函数。

注意这里直接用 $pow$ 函数要被卡精度，我们可以暴力调整精度，稍微取大一点，然后暴力把得到的数调整回来即可。

**Code**

```cpp
// Problem: F. Relatively Prime Powers
// Contest: Codeforces - Educational Codeforces Round 50 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1036/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
const int N = 100 + 7;

ll n, m, k;
int t;
int primes[N], mu[N], cnt;
bool vis[N];

void init(int n)
{
	vis[1] = 1;
	mu[1] = 1;
	for(int i = 2; i <= n; ++ i) {
		if(vis[i] == 0) {
			primes[ ++ cnt] = i;
			mu[i] = -1;	
		}
		for(int j = 1; j <= cnt && i * primes[j] <= n; ++ j) {
			vis[i * primes[j]] = 1;
			if(i % primes[j] == 0) {
				mu[i * primes[j]] = 0;
				break;
			}
			mu[i * primes[j]] -= mu[i];
		}
	}
}

void solve()
{
	scanf("%lld", &n);
	ll ans = 0; 
	for(int i = 2; i <= 60; ++ i) {
		if(mu[i] == 0) continue;
		ll res = (ll)(pow(n, 1.0 / i)) + 2;
		while(pow(res, i) > n) res -- ;
		ans += (ll) mu[i] * (res - 1); 
	}  
	printf("%lld\n", n - 1 + ans);
}

int main()
{
	init(N - 7);
	scanf("%d", &t);
	while(t -- ) {
		solve();
	}
	return 0;
}
```

---

## 作者：Dovish (赞：0)

## 题解
~~为啥想那么多，爆搜都能过。~~

首先很容易发现非法方案是比合法方案容易统计的。

具体而言，对于最大公约数为 $x$ 的非法的所**都是 $^x\sqrt n$ 内的合法方案**（我们对每一个质因数的指数同时除以x，这样他们就互质了）。

所以我们令 $f(x)$ 为 $x$ 以内的合法方案数。

则有递归式：

$$f(x)=x-\sum_{x=2}^{\infty}f(^x\sqrt n)-1$$

注意当 $x>\log n$ 的时候调用的数都不足2，所以返回的都是 $0$ ,因此 $x$ 最大只有 $\log n$。

我们也非常容易证明这个东西是不重不漏的：

1. 因为如果非法，那一定是某个合法方案的幂次，而我们枚举了所有合法方案的幂次，所以不漏。

2. 假设存在 $a^x=b^y(a\not =b\not=0,x\not=y\not=0)$ 这种重复的情况，因为 $a,b,x,y$ 都为整数，所以 $a,b$ 中一者一定是另一个的幂次，但这样的数是不合法的，故假设不成立。

因为每一次 $n$ 的至多有上一层的根号，并且每一层的宽度只会有 $\log n$，本身状态就不多，加上记忆化后就能跑过了，实测随机数下的极限数据只存了三十万个状态。

另外注意 $\text{pow}$ 取 $x$ 次根的精度非常差，建议手动在算出来的结果的上下试一下。

~~时间复杂度不会算。~~
## code
```cpp
#include<bits/stdc++.h>
#define int long long
#define lowbit(x) (x&(-x))
using namespace std;
const int N=2e6+10,M=100,inf=1e9,mod=998244353;
const double ep=1e-9;
int T,n;
map<int,int>g;
int qpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)res*=a;
		a*=a;
		b/=2;
	}
	return res;
}
int f(int x)
{
	if(g[x])return g[x];
	int res=x-1;
	int lg=log2(x);
	for(int i=2;i<=lg;i++)
	{
		double to=pow(x,1.0000/i)+ep;
		if(qpow((int)to,i)>x)to-=1;
		res=res-f(to);
	}
	g[x]=res;
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		cout<<f(n)<<'\n';
	}
	return 0;
}
```

---

