# [ABC228E] Integer Sequence Fair

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc228/tasks/abc228_e

整数列を一堂に集めてその優劣を定める、整数列品評会が行われます。 品評会では、$ 1 $ 以上 $ K $ 以下の整数からなる長さ $ N $ の整数列すべてが審査対象となり、 審査対象の数列それぞれに対して $ 1 $ 以上 $ M $ 以下の整数の点数をつけます。

「審査対象の数列それぞれに対して $ 1 $ 以上 $ M $ 以下の整数の点数をつける方法」が何通りあるかを $ 998244353 $ で割ったあまりを出力してください。

ただし、$ 2 $ つの方法が異なるとは「審査対象となるある数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ が存在して、 $ A $ に対してつける点数が $ 2 $ つの方法で異なる」ことを言います。

## 说明/提示

### 制約

- $ 1\ \leq\ N,\ K,\ M\ \leq\ 10^{18} $
- $ N,\ K,\ M $ は整数

### Sample Explanation 1

審査対象となる数列は、$ (1,\ 1),\ (1,\ 2),\ (2,\ 1),\ (2,\ 2) $ の $ 4 $ つです。「審査対象の数列それぞれに対して $ 1 $ 以上 $ 2 $ 以下の整数の点数をつける方法」は、以下の $ 16 $ 通りあります。 - $ (1,\ 1) $ に $ 1 $ 点、$ (1,\ 2) $ に $ 1 $ 点、$ (2,\ 1) $ に $ 1 $ 点、$ (2,\ 2) $ に $ 1 $ 点をつける方法 - $ (1,\ 1) $ に $ 1 $ 点、$ (1,\ 2) $ に $ 1 $ 点、$ (2,\ 1) $ に $ 1 $ 点、$ (2,\ 2) $ に $ 2 $ 点をつける方法 - $ (1,\ 1) $ に $ 1 $ 点、$ (1,\ 2) $ に $ 1 $ 点、$ (2,\ 1) $ に $ 2 $ 点、$ (2,\ 2) $ に $ 1 $ 点をつける方法 - $ (1,\ 1) $ に $ 1 $ 点、$ (1,\ 2) $ に $ 1 $ 点、$ (2,\ 1) $ に $ 2 $ 点、$ (2,\ 2) $ に $ 2 $ 点をつける方法 - $ \cdots $ - $ (1,\ 1) $ に $ 2 $ 点、$ (1,\ 2) $ に $ 2 $ 点、$ (2,\ 1) $ に $ 2 $ 点、$ (2,\ 2) $ に $ 2 $ 点をつける方法 よって、$ 16 $ を出力します。

### Sample Explanation 2

$ 998244353 $ で割ったあまりを出力することに注意してください。

## 样例 #1

### 输入

```
2 2 2```

### 输出

```
16```

## 样例 #2

### 输入

```
3 14 15926535```

### 输出

```
109718301```

# 题解

## 作者：FFTotoro (赞：3)

首先，根据乘法原理，很显然这道题的答案是 $M^{\left(K^N\right)}$。

本题的难点在于——如何计算这个式子。

这时，我们就需要用到著名的**费马小定理**：

对于一个质数 $P$，如果 $M$ 不是 $P$ 的倍数，那么 $M^{P-1}\equiv 1\pmod P$。

由上面的定理，易得：

$$M^{\left(K^N\right)}\equiv M^{\left(K^N\bmod (P-1)\right)}\pmod P$$

所以，本题可以使用快速幂解决。注意特判 $M$ 是 $P$ 的倍数的情况。

放代码：

```cpp
#include<atcoder/all>
#define int long long
const int mod=998244353;
using namespace std;
main(){
    ios::sync_with_stdio(false);
    int n,k,m; cin>>n>>k>>m;
    cout<<(m%mod?atcoder::pow_mod(m,atcoder::pow_mod(k,n,mod-1),mod):0)<<endl; // 使用 ACL pow_mod
    return 0;
}
```

---

## 作者：zeekliu (赞：2)

首先观察样例或者用~~深奥的~~乘法原理可得，答案就是

$M^{K^N} \bmod 998244353$。

但考虑到 $N,K,M \le 10^{18}$，所以正常的快速幂肯定会挂。

所以，最好能把 $K^N$ 取模，使其变小，那样就变成常规快速幂了。

显然，看到 $998244353$，你就会想到那是一个 ~~坑~~ 素数，所以使用**费马小定理**。

先复习一下：

对于一个素数 $p$，若 $p \nmid n$，则 $n^{p-1} \equiv 1 \, (\bmod \, p)$。

所以，$M^{K^N} \equiv M^{(K^N \bmod (p-1))} \, (\bmod \, p)$。

然后就简单了，先处理 $K^N \bmod (p-1)$，然后记录结果，再算以 $M$ 为底数的就可以了。

代码：

```cpp
//ABC228E 23.01.02
#include <bits/stdc++.h>
using namespace std;
long long n,k,m;
long long MOD=998244353;

inline long long qpow(long long a,long long b,long long c)
{
    if (a==0) return 0;
    long long ans=1;
    while (b)
    {
        if (b&1) ans=ans*a%c;
        a=a*a%c;
        b>>=1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>n>>k>>m;
    k%=(MOD-1),m%=MOD;
    long long _=qpow(k,n,MOD-1);
    cout<<qpow(m,_,MOD)<<endl;
    exit(0);
}
```

---

## 作者：lmy_2011 (赞：2)

### 方法
题范围 $[1,k]$，值位于 $[1,m]$，序列长度 $n$，与乘法原理的例题大同小异。

乘法原理例题：
一个事情，分为 $n$ 步，做第 $1$ 步有 $a_1$ 种不同的方法，做第 $2$ 步有 $a_2$ 种不同的方法，$\cdots$，做第 $n$ 步有 $a_n$ 种不同的方法，那么完成这件事的方法数 $ans$ 可以得解：$ans=a_1\times a_2\times a_3\times \cdots \times a_{n-2}\times a_{n-1}\times a_{n}$。

将本题带入进去，则答案为 $m^{k^n}\bmod 998244353$。
### 解法
本题解法需要用费马小定理，费马小定理如下：

如果 $p$ 是一个质数，而整数 $a$ 与 $p$ 没有倍数与因数关系，则有解 $a^{p-1}≡1(\bmod\ p)$。

在带入到题目里：
$$m^{k^n}≡m^{k^n\bmod (p-1)}(\bmod\ p)$$

当然 $p$ 要求出来。

---

## 作者：Meickol (赞：1)

一道不错的数论题，不过题解区讲的都不是很清楚，于是来写一个详细清晰的版本。



先对构成的序列考虑，显然每个位置有 $k$ 种选择，而我们序列长度为 $n$，即 $n$ 个位置，共 $k^n$ 种选择。

接下来考虑每个序列可以得多少分，因为每个序列可以有 $m$ 种选择，所以是 $\large m^{k^n}$ 种选择。

接下来就是考虑如何计算这个值了。



一开始我的做法是直接两个快速幂，代码如下，但是 WA 了。

当时以为是乘法爆 long long 了。但是尝试改用 int128 甚至使用快速乘依然 WA。

```cpp
typedef long long LL;
const int MOD=998244353;
LL n,k,m;
LL fastpow(LL a,LL n,LL mod){
	LL res=1;
	while(n){
		if(n&1) res=res*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return res;
}
void solve(){
	cin>>n>>k>>m;
	cout<<fastpow(m,fastpow(k,n,MOD),MOD);
}
```





后来才想起来其实是因为**幂指数取模**和**结果取模**是**不一样**的。

即 $\large (m^{k^n} \bmod p) \neq (m^{k^n \bmod p} \bmod p)$。

也就是你不能对指数部分直接用快速幂处理，否则结果就变了。

那么你应该想到费马小定理，当 $p$ 为质数时，且 $a$ 与 $p$ 互质时，有 $\large a^{p-1} \equiv 1 \pmod p$。

而 $998244353$ 显然是一个质数，满足使用条件。

接着考虑对 $\large m^{k^n}$ 进行变形，考虑借助费马小定理将原式等价替换，即考虑将 $k^n$ 转化为含有 $p-1$ 的式子。

根据带余数除法我们知道一个数 $A$ 必然可以用 $B \ (B \neq 0)$ 表示出来，即：$A=q \times B +r \ (0 \le r <B)$。

因而，我们的 $k^n$ 必然可以用 $p-1$ 表示出来，即 $k^n = q \times (p-1) +r$。

故 $\large m^{k^n} \bmod p$ 等价于 $\large m^{q \times (p-1)+r} \bmod p$。

又根据指数运算法则，$\large m^{q \times (p-1)+r} \bmod p$ 可转化为 $\large (m^{q \times (p-1)} \times m^r)\bmod p$。

又因为 $m^{p-1} \equiv 1 \pmod p$，故实际上我们需要计算的是 $m^r \bmod p$ 的值。

而 $k^n \equiv r \pmod{ p-1}$，因此我们最终计算 $\large m^{k^{n} \bmod (p-1)} \bmod p$ 即可。



不过注意上述使用了费马小定理，是基于 $m$ 与 $p$ 互质的前提下。

我们需要注意特判 $m$ 与 $p$ 不互质的情况。不互质那么最后取模 $p$ 显然就是 $0$ 了。



然后你写出了下面这份代码，以为大功告成时，还是 WA 了。

```cpp
typedef long long LL;
const int MOD=998244353;
LL n,k,m;
LL fastpow(LL a,LL n,LL mod){
	LL res=1;
	while(n){
		if(n&1) res=res*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return res;
}
void solve(){
	cin>>n>>k>>m;
	if(m%MOD==0) cout<<0;
	else cout<<fastpow(m,fastpow(k,n,MOD-1),MOD);
}
```





注意到快速幂计算时，由于底数很大，乘法可能会爆 long long，因而在快速幂函数中注意对底数取模一下，这样就能 AC 了，代码如下。

```cpp
typedef long long LL;
const int MOD=998244353;
LL n,k,m;
LL fastpow(LL a,LL n,LL mod){
	a%=mod;
	LL res=1;
	while(n){
		if(n&1) res=res*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return res;
}
void solve(){
	cin>>n>>k>>m;
	if(m%MOD==0) cout<<0;
	else cout<<fastpow(m,fastpow(k,n,MOD-1),MOD);
}
```

当然你也可以一开始就对底数取模，代码如下。

```cpp
typedef long long LL;
const int MOD=998244353;
LL n,k,m;
LL fastpow(LL a,LL n,LL mod){
	LL res=1;
	while(n){
		if(n&1) res=res*a%mod;
		a=a*a%mod;
		n>>=1;
	}
	return res;
}
void solve(){
	cin>>n>>k>>m;
	m%=MOD,k%=(MOD-1);
	if(!m) cout<<0;
	else cout<<fastpow(m,fastpow(k,n,MOD-1),MOD);
}
```

---

## 作者：cosf (赞：1)

依题意，答案为 $M^{K^N}$。

计算的几个要点（令 $p=998244353$）：

- $M^{K^N} \equiv M^{K^N \bmod (p-1)} \pmod p$。
- 计算快速幂时先对底数取模。
- 不特判 $M$ 是 $p$ 的倍数会挂，我也不知道为什么。

```cpp
#include <iostream>
using namespace std;

#define MOD 998244353

using ll = long long;

ll pow(ll b, ll p, ll m)
{
    b %= m;
    ll r = 1;
    while (p)
    {
        if (p & 1)
        {
            r = r * b % m;
        }
        b = b * b % m;
        p >>= 1;
    }
    return r;
}

int main()
{
    ll n, k, m;
    cin >> n >> k >> m;
    if (m % MOD < 2)
    {
        cout << m % MOD << endl;
        return 0;
    }
    cout << pow(m, pow(k, n, MOD - 1), MOD) << endl;
    return 0;
}

```

---

## 作者：xd244 (赞：0)

题目描述：有一个长度为 $n$ 的整数序列，它里面的每一个元素的值都在 $[1,k]$ 范围内。对于每一个满足条件的序列，都给出一个值在 $[1,m]$ 之间的得分。请求出有多少种不同的方法满足题目要求？答案对 $998244353$ 取模。

经过~~高深莫测的~~乘法原理可知，答案为 $M^{K^N}\bmod 998244353$。所以第一个想到的是快速幂。

研究之后发现（用 $p$ 来代替 $998244353$），$M^{K^N}\bmod p=(M^K)^N \bmod p=(M^K\bmod p)^N$。

所以我敲出了下面的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
long quick_pow(long a,long b,long p){//快速幂
    long ans=1;
    long ansa=a;long ansb=b;
    while(b>0){
        if(b&1)ans=ans*a%p;
        a=a*a%p;
        b=b>>1;
    }return ans%p;
}int main(){
    long m,k,n;cin>>n>>k>>m;
    long a=quick_pow(k%(mod-1),n,mod-1),ans=quick_pow(m%mod,a,mod);
    cout<<ans<<"\n";
}
```
结果......
WA on #17

于是我开始思考，想到了有一个东西叫做**费马小定理**：

当 $p$ 是质数且 $p∤n$ 时，$n^{p-1}≡1(\bmod p)$。

所以 $M^{K^N}=M^{K^N\bmod(p-1)}(\bmod p)$。

只需要先求 $a=K^N\bmod(p-1)$，再求出 $M^a\bmod p$ 即可。

时间复杂度为 $O(\log n)$，其中 $n=\max(a,b,c)$。

AC Code：
```cpp
#include<iostream>
using namespace std;
#define mod 998244353
long quick_pow(long a,long b,long p){//快速幂模板
    if(a==0)return 0;//先特判 a==0 的情况（虽然没什么用）
    long ans=1;
    while(b){
        if(b&1)ans=ans*a%p;
        a=a*a%p;
        b=b>>1;//不要用 /2 否则速度很慢
    }return ans%p;
}int main(){
    long m,k,n;cin>>n>>k>>m;
    k%=(mod-1);m%=mod;//预先求模否则会 WA
    long a=quick_pow(k,n,mod-1),ans=quick_pow(m,a,mod);//费马小定理求值
    cout<<ans<<"\n";//换行！！！
}
```

---

