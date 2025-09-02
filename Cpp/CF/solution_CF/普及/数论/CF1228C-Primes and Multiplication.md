# Primes and Multiplication

## 题目描述

Let's introduce some definitions that will be needed later.

Let $ prime(x) $ be the set of prime divisors of $ x $ . For example, $ prime(140) = \{ 2, 5, 7 \} $ , $ prime(169) = \{ 13 \} $ .

Let $ g(x, p) $ be the maximum possible integer $ p^k $ where $ k $ is an integer such that $ x $ is divisible by $ p^k $ . For example:

- $ g(45, 3) = 9 $ ( $ 45 $ is divisible by $ 3^2=9 $ but not divisible by $ 3^3=27 $ ),
- $ g(63, 7) = 7 $ ( $ 63 $ is divisible by $ 7^1=7 $ but not divisible by $ 7^2=49 $ ).

Let $ f(x, y) $ be the product of $ g(y, p) $ for all $ p $ in $ prime(x) $ . For example:

- $ f(30, 70) = g(70, 2) \cdot g(70, 3) \cdot g(70, 5) = 2^1 \cdot 3^0 \cdot 5^1 = 10 $ ,
- $ f(525, 63) = g(63, 3) \cdot g(63, 5) \cdot g(63, 7) = 3^2 \cdot 5^0 \cdot 7^1 = 63 $ .

You have integers $ x $ and $ n $ . Calculate $ f(x, 1) \cdot f(x, 2) \cdot \ldots \cdot f(x, n) \bmod{(10^{9} + 7)} $ .

## 说明/提示

In the first example, $ f(10, 1) = g(1, 2) \cdot g(1, 5) = 1 $ , $ f(10, 2) = g(2, 2) \cdot g(2, 5) = 2 $ .

In the second example, actual value of formula is approximately $ 1.597 \cdot 10^{171} $ . Make sure you print the answer modulo $ (10^{9} + 7) $ .

In the third example, be careful about overflow issue.

## 样例 #1

### 输入

```
10 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
20190929 1605
```

### 输出

```
363165664
```

## 样例 #3

### 输入

```
947 987654321987654321
```

### 输出

```
593574252
```

# 题解

## 作者：Steven_Meng (赞：4)

## 广告
想要更佳的食用体验，请前往[蒟蒻のBlog](https://stevenmhy.tk/archives/9b983113.html)

## $Pro3$

[传送门](https://codeforces.com/contest/1228/problem/C)

定义$prime(x)$为$x$的质因子的集合，比如说$prime(140)=\{2,5,7\}$

设$g(x,p)$是能够整除$x$的最大的$p^k$，比如说$g(45,3)=9$

设$f(x,y)$为$\prod _{p \in prime(x)} g(y,p)$，比如说$f(30, 70) = g(70, 2) \cdot g(70, 3) \cdot g(70, 5) = 2^1 \cdot 3^0 \cdot 5^1 = 10$

给你$x,n$，计算$\prod _{i=1}^n f(x,i)$

## $Sol3$

~~数论不会先打表~~

先计算一下$x=10,n=10$的情况：

$f(10,1)=1$ $f(10,2)=2$ $f(10,3)=1$ $f(10,4)=4$ $f(10,5)=5$

$f(10,6)=2$ $f(10,7)=1$ $f(10,8)=8$ $f(10,9)=1$ $f(10,10)=10$

如何考虑，不妨对$prime(x)$中的元素分别考虑，考虑质因子$2$对答案的贡献，他会分别对$f(x,2 \times i)$做出一个$2$的贡献，同时对$f(x,2^2 \times i)$做出一个$2$的贡献，对$f(x,2^3 \times i)$做出一个$2$的贡献。

于是总的贡献是$2^ {[n/2]} \times 2 ^ {[n/2^2]} \times 2^{[n/2^3]} ...$

还要继续考虑$5$对答案的贡献，这里省略。

于是我们得到核心代码：

```cpp
inline int Calc(int x,int n){
	while (n){
		ans=(ans*ksm(x,n/x,MOD))%MOD;
		n/=x;
	}
	return 0;
}
```

就是计算每一个质因子$x$对于答案的贡献。

## $Code3$

```cpp
#include <bits/stdc++.h>
#define MAXN 200005
#define int long long
#define MOD 1000000007
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
int ans=1;
inline int ksm(int b,int p,int k){
    int ans=1;
    while (p>0){
        if (p&1ll){
            ans=(b*ans)%k;
        }
        b=(b*b)%k;
        p>>=1ll;
    }
    return ans%MOD;
}
inline int Calc(int x,int n){
	while (n){
		ans=(ans*ksm(x,n/x,MOD))%MOD;
		n/=x;
	}
	return 0;
}
int cnt,primes[MAXN];
inline void Sieve(int x){//找出x的质因数
	int bd=sqrt(x);
	for (register int i=2;i<=bd;++i){
		if (x%i==0){
			primes[++cnt]=i;
			while (x%i==0) x/=i;
		}
	}
	if (x>1) primes[++cnt]=x;//x是质数
}
#undef int
int main(){
#define int long long
	int x,n;
	cin>>x>>n;
	Sieve(x);//找出x的所有质因子
	for (register int i=1;i<=cnt;++i){
		Calc(primes[i],n);
	}
	cout<<ans;
}
```
原谅`define int long long`，qwq

---

## 作者：blue_ice (赞：1)

* 求 $\prod\limits_{i=1}^nf(x,i)\bmod(10^9+7)$ 的值。（$f$ 的定义如题）
* $2\le x\le10^9,1\le n\le10^{18}$。

首先，把式子拆开，得到 $\prod\limits_{i=1}^n\prod\limits_{p\in prime(x)}g(i,p)$。  
观察一下 $g$ 的性质，发现 $g(a,p)\cdot g(b,p)=g(ab,p)$，于是化简式子为 $\prod\limits_{p\in prime(x)}g(n!,p)$。  
推导发现：
$$
\begin{aligned}
\log_p(g(n!,p))&=(0,n]\text{ 里能被 }p\text{ 整除的数的个数 }+\ (0,n]\text{ 里能被 }p^2\text{ 整除的数的个数 }+ \ (0,n]\text{ 里能被 }p^3\text{ 整除的数的个数 }+\ \ldots\\
&=\left\lfloor\frac{n}{p}\right\rfloor+\left\lfloor\frac{n}{p^2}\right\rfloor+\left\lfloor\frac{n}{p^3}\right\rfloor+\ \ldots\\
&=\left\lfloor\frac{n}{p}\right\rfloor+\left\lfloor\frac{\left\lfloor\frac{n}{p}\right\rfloor}{p}\right\rfloor+\left\lfloor\frac{\left\lfloor\frac{\left\lfloor\frac{n}{p}\right\rfloor}{p}\right\rfloor}{p}\right\rfloor+\ \ldots
\end{aligned}
$$
所以只需 $O(\log n)$ 递推算出指数再快速幂求解即可。对于每个 $p\in prime(x)$，把结果乘起来就能得出答案。  
总共的时间复杂度为 $O(\sqrt x +\log x\log n)$。

代码：
```c++
#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

const int MOD = 1e9 + 7;

int x;
LL n;

bool is_prime(int x) // 判断 x 是否为质数
{
	if (x < 2) return false;
    for (int i = 2; i <= x / i; i ++ )
        if (!(x % i))
            return false;
    return true;
}

vector<int> prime_divisors(int x) // 求出 prime(x)
{
    vector<int> res;
    for (int i = 1; i <= x / i; i ++ ) // 注意，要从 1 开始，因为可能 x 本身就是质数
        if (!(x % i))
        {
            if (is_prime(i)) res.push_back(i);
            if (i ^ x / i && is_prime(x / i)) res.push_back(x / i);
        }
    return res;
}

int qpow(int a, LL b) // 快速幂，求出 a^b mod 1000000007
{
    int res = 1;
    while (b)
    {
        if (b & 1) res = (LL)res * a % MOD;
        a = (LL)a * a % MOD, b >>= 1;
    }
    return res;
}

int main()
{
    cin >> x >> n;
    
    vector<int> primes = prime_divisors(x);
    
    int res = 1; // 结果
    for (int i = 0; i < primes.size(); i ++ ) // 枚举每个质数
    {
    	int prime = primes[i];
//    	cout << prime << '\n'; 调试用，如果一个质数都没输出，那一般是 prime(x) 的计算出了问题
        LL cnt = 0, tmp = n;
        do tmp /= prime, cnt += tmp; // 下面两行求 prime 在 n! 中的指数
        while (tmp);
        res = (LL)res * qpow(prime, cnt) % MOD;
    }
    
    cout << res;
    
    return 0;
}
```

---

## 作者：Karry5307 (赞：1)

### 题意

定义$prime(x)$为由$x$的所有质因子构成的集合，$g(x,p)$为满足$p^k\mid x$并且$p^{k+1}\nmid x$的$k$，$f(x,y)=\prod\limits_{p\in prime(x)}g(y,p)$。

给定$x,n$，求$\prod\limits_{i=1}^{n}f(x,i)\bmod10^9+7$。

$\texttt{Data Range:}1\leq x\leq 10^9,1\leq n\leq 10^{18}$

### 题解

还是一道挺清新的$\texttt{C}$题。~~上次`1195C`那题读错题然后就掉分啦qwq~~

我们首先来推一下柿子：

$$\prod\limits_{i=1}^{n}f(x,i)=\prod\limits_{i=1}^{n}\prod\limits_{p\in prime(x)}g(i,p)$$

$$\prod\limits_{i=1}^{n}\prod\limits_{p\in prime(x)}g(i,p)=\prod\limits_{p\in prime(x)}\prod\limits_{i=1}^{n}g(i,p)$$

现在我们的目标是对某一个特定的质数$p$，求$\prod\limits_{i=1}^{n}g(i,p)$

~~这不随便做啊qwq~~

首先考虑$1$到$n$中只有$\lfloor\frac{n}{p}\rfloor$个数整除$p$，于是剩下$n-\lfloor\frac{n}{p}\rfloor$的贡献为$1^{n-\lfloor\frac{n}{p}\rfloor}$

然后剩下的数我们表示成$p,2p\cdots$，每个数的贡献为$p$的倍数，于是我们先把答案乘上$p^{\lfloor\frac{n}{p}\rfloor}$，这些数变成$1,2,\cdots\lfloor\frac{n}{p}\rfloor$，然后我们就可以递归做了qwq

这里举个栗子吧qwq

比如说我们要求$\prod\limits_{i=1}^{8}g(i,2)$

首先我们知道有$8-\lfloor\frac{8}{2}\rfloor=4$个数的贡献为$1$，所以这$4$个数的贡献为$1^4$。

然后继续递归剩下$4$个数，有$4-\lfloor\frac{4}{2}\rfloor=2$个数贡献为$2$，这两个数贡献为$2^2$。

剩下$2$个数中有$2-\lfloor\frac{2}{2}\rfloor=1$个数贡献为$2^2=4$，贡献为$4^1$。

剩下一个数中有$1-\lfloor\frac{1}{2}\rfloor=1$个数贡献为$2^3=8$，贡献为$8^1$。

剩下没有数了，答案为$1^4\times 2^2\times 4^1\times 8^1$。

这样做是$O(\log n)$的。

所以总复杂度是$O(\log x\log n)$的，而实际上没有达到这个上界，因为$x$的质因子个数没达到$\ln x$啊qwq~~我们机房大佬说的~~

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=1e4+51,MOD=1e9+7;
ll x,cnt,tot,res;
ll factor[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline void getFact(ll x)
{
	for(register int i=2;i<=sqrt(x);i++)
	{
		if(!(x%i))
		{
			factor[++tot]=i;
			while(!(x%i))
			{
				x/=i;
			}
		}
	}
	if(x!=1)
	{
		factor[++tot]=x;
	}
}
inline ll qpow(ll base,ll exponent)
{
	ll res=1;
	while(exponent)
	{
		if(exponent&1)
		{
			res=res*base%MOD;
		}
		base=base*base%MOD,exponent>>=1;
	}
	return res;
}
inline ll calc(ll cnt,ll x,ll p)
{
	if(cnt==0)
	{
		return 1;
	}
	return qpow(p,(cnt-cnt/x)%(MOD-1))*calc(cnt/x,x,p*x%MOD)%MOD;
}
int main()
{
	x=read(),cnt=read(),getFact(x),res=1;
	for(register int i=1;i<=tot;i++)
	{
		res=res*calc(cnt,factor[i],1)%MOD;
	}
	cout<<res<<endl;
}
```

---

## 作者：_Day_Tao_ (赞：0)

题意不再赘述，题面已经解释的很清楚了。

考虑将答案的柿子写出并展开：

$$\begin{aligned}\prod_{i=1}^n f(x,i) &= \prod_{i=1}^n\prod_{p\in prime(x)}g(i,p) \\ &= \prod_{p\in prime(x)}\prod_{i=1}^n g(i,p)\ (\bmod \ 10^9+7)\end{aligned}$$

然后我们对于 $\prod_{i=1}^n g(i,p)$ 进行分析。我们可以枚举 $p^k$，对于每个 $p^k$，在上面这个柿子里的贡献就是 $(p^k)^{\lfloor\frac{n}{p^k} \rfloor}$，但是题目中要求的是对于每个数字找出最大的 $k$，直接这样做会有重复，需要减去 $k$ 更大的贡献，所以说我们可以先找到最大的 $k$，从大到小枚举，每次次幂的贡献都要减去 $\lfloor\frac{n}{p^{k+1}}\rfloor$，即上一个次幂的贡献（由于更大 $k$ 的贡献可以理解为包含在 $k+1$ 的贡献中，所以直接这样操作即可）。然后要注意找最大 $k$ 的时候可能两数相乘的时候爆 `long long`，所以可以利用高中最基本的 $\log$ 计算，$\log_{10}res+\log_{10}p>18$ 时就不用乘下去了；另外快速幂的时候记得把底数先取模，不然乘的时候也会爆。

时间复杂度为 $O(\sqrt{x} + prime(x)\log n)$。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define ls root << 1
#define rs root << 1 | 1
#define int long long
#define mid ((l+r)>>1)
inline int read(){
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const int mod = 1e9+7;
const int INF = 0x7fffffff;
const int MAX = 2e5 + 5;
vector<int>prime;
int x,n,ans=1;
inline int qpow(int a,int b)
{
	int res=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) res=res*a%mod;
	return res;
}
signed main()
{
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	x=read(),n=read();
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
		{
			prime.push_back(i);
			while(x%i==0) x/=i;
		}
	if(x!=1) prime.push_back(x);
	for(int p:prime)
	{
		int cnt=0,res=1,t=0;
		while(log10(res)+log10(p)<=18&&res*p<=n) res*=p,t++;
		for(int i=t;i>=1;i--) ans=ans*qpow(res%mod,n/res-cnt)%mod,cnt=n/res,res/=p;
	}
	printf("%lld\n",ans);
	system("pause");
	return 0;
}
```

---

## 作者：紪絽 (赞：0)

# CF1228C 题解

数论题我真不会 ；；

## 题意
$\operatorname{prime}(x)$ 表示 $x$ 的质因子集合。$g(x,p)=p^k$，其中 $k \in \mathbb{N}^*, p^k \mid x$ 且 $p ^ {k + 1} \nmid x$。$f(x,y) = \prod_{p \in \operatorname{prime}(x)}g(y,p)$。给出 $x, n$，求 $\prod_{i=1}^n f(x,i) \bmod 10^9 + 7$。

## 分析

对于任意 $g(a,p)$ 与 $g(b,p)$ 有 $g(a,p)\times g(b,p) = g(ab,p)$。

设 $a=p_1^{x_1}p_2^{x_2} \dots p_n^{x_n},b = p_1^{y_1}p_2^{y_2} \dots p_n^{y_n}$，于是 $g(a,p_i)=p_i^{x_i}, g(b,p_i)=p_i^{y_i}, g(a,p)\times g(b,p) =p_i^{x_i+y_i}=g(ab,p)$。

所以
$$\prod_{i=1}^n f(x,i) = \prod_{i=1}^n \prod_{{p \in \operatorname{prime}(x)}}g(i,p)=\prod_{\mathclap{p \in \operatorname{prime}(x)}}g(n!,p)$$

可以看出，我们要求出 $n!$ 中所有 $p_i\in \operatorname{prime}(x)$ 的次数。  
对于任一 $\log_{p_i}(g(n!,p_i))$（设其为 $m_i$），即质因子 $p_i$ 的次数，有

$$m_i=\left\lfloor \dfrac{n}{p_i} \right\rfloor + \left\lfloor \dfrac{n}{p_i^2} \right\rfloor +  \left\lfloor \dfrac{n}{p_i^3} \right\rfloor \dots $$

$\left\lfloor \dfrac{n}{p_i} \right\rfloor$ 表示能被 $p_i$ 整除的数的个数。举个例子，设 $n = 20, p_i=3$，列举一下 $1$ 到 $n$ 有 $3$ 作为因子的数：

$$
3=3^1 \\ 6=2^1 \times 3^1 \\ \red{9=3^2} \\ 12=2^2 \times3^1 \\ 15=3^1 \times 5^1 \\ \red{18=2^1 \times 3^2} 
$$

在这个例子中，$\left\lfloor \dfrac{n}{p_i} \right\rfloor = 6$。不过，我们要求的是质因子 $p_i$ 的个数，这些标红的数有两个因数 $p_i$，却只被统计了一次。所以，我们还要再计算 $\left\lfloor \dfrac{n}{p_i^2} \right\rfloor$ 才能把标红的数统计起来。

再比如 $p_i=2$ 时：
$20!=(\red{2} \times \orange{2} \times 5) \times 19 \times (\red{2}  \times 3^2) \times 17  \times (\red{2} \times \orange{2} \times \green{2} \times \blue{2}) \times (3 \times 5) \times (\red{2} \times 7) \times 13 \times (\red{2} \times \orange{2} \times 3) \times 11 \times (\red{2} \times 5) \times (3^2) \times (\red{2} \times \orange{2} \times \green{2}) \times 7 \times (\red{2} \times 3) \times 5 \times (\red{2}  \times \orange{2}) \times 3 \times \red{2} \times 1$。
标着颜色的数分别被标着对应颜色的式子统计：$\red{\left\lfloor \dfrac{n}{p_i} \right\rfloor} + \orange{\left\lfloor \dfrac{n}{p_i^2} \right\rfloor} + \green{\left\lfloor \dfrac{n}{p_i^3} \right\rfloor} + \blue{\left\lfloor \dfrac{n}{p_i^4} \right\rfloor} $。

那么最后的答案就是 $p_1^{m_1}p_2^{m_2}p_3^{m_3} \dots p_k^{m_k}$，$k$ 为 $\operatorname{prime}(x)$ 的元素数量。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1e9 + 7;
vector<ll> p;
ll n, x, ans = 1;

ll ksm(ll a, ll b) // 快速幂 
{
	ll res = 1;
	while (b)
	{
		if (b & 1) res = (res * a) % MOD;
		a = (a * a) % MOD, b >>= 1;
	}
	return res;
}

ll calc(ll n, ll p) // 计算因子次数 
{
	ll s = 0;
	while (n)
		s += n / p, n /= p;
	return s;
}

int main()
{
	cin >> x >> n;
	
	for (int i = 2; i * i <= x; i++) // 求出 x 的所有质因子 
		if (!(x % i))
		{
			while (!(x % i)) x /= i;
			p.push_back(i);		
		}
	if (x > 1) p.push_back(x);
	
	for (int i = 0; i < p.size(); i++)
		ans = (ans * ksm(p[i], calc(n, p[i]))) % MOD;

	cout << ans;
    return 0;
}
```

---

## 作者：songhn (赞：0)

### 1.题解
首先我们可以把$x$质因数分解 然后考虑$x$的因子$p$ 

对于每一个$p$ 我们都要求出$g(1,p)\cdot g(2,p)\cdots g(n,p)$ 而$g(x,p)$的含义其实就是对于$x$质因数分解后的$p^k$所以我们可以按阶乘分解那么考虑 考虑每个因子$p$对于答案的贡献 

首先考虑$p$ 显然有$\lfloor \frac{n}{p} \rfloor$个数至少包含一个$p$ 那么贡献就是$p^{\lfloor \frac{n}{p} \rfloor}$

之后再考虑$p^2$ 有$\lfloor \frac{n}{p^2} \rfloor$个数可以分解出$p^2$ 但由于之前我们在统计$p$时已经加了一遍 所以这时候的贡献不需要乘2 只需要再加上$\lfloor \frac{n}{p^2} \rfloor$就好了

以此类推 总共需要统计$\log_{p}{n}$次 记贡献总数为$t$ 那么该$p$对答案的贡献便是$p^t$ 之后快速幂统计即可 要注意的是在统计贡献数时有可能会爆long long（实际上不会）我们不用考虑那么多 因为$t$是次幂不能直
接%mod 但是我们有欧拉定理 我们把次幂模$\phi(mod)$答案是不变的 因为题目给的mod是$1e9+7$是一个质数所以直接模(mod-1)即可
### 2.AC代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#define ll long long
using namespace std;
const ll mod=1e9+7;
ll x,n;
vector<ll> prime;
ll ksm(ll a,ll b)
{
	ll res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main()
{
	cin>>x>>n;
	for(ll i=2;i<=x/i;i++)
	{
		if(x%i==0)
		{
			prime.push_back(i);
			while(x%i==0) x/=i;
		}
	}
	if(x>1) prime.push_back(x);
	ll l=prime.size();
	ll ans=1;
	for(int i=0;i<l;i++)
	{
		ll p=prime[i];
		ll t=n,t1=0;
		while(t)
		{
			t1=(t1+t/p)%(mod-1);
			t/=p;
		}
		ans=(ans%mod*ksm(p,t1)%mod)%mod;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：弦巻こころ (赞：0)

~~这道题不难,学过小学奥数都能做出来~~

题意,让你求 $\sum_{i=1}^n f(x,i)$

由于f函数的性质,我们可以考虑将x的素因子拆出来,再进行处理.

我们将x的素因子拆出来和,这道题变为求

$\sum_ {i=1}^{n} \sum_ {p \in prime(x)}  g(i,p) $

我们稍加观察就可以发现.我们只需要知道每个质因数对答案的贡献即可.

那怎么求每个质因数对答案的贡献呢? 

~~当然是用小学奥数.~~

我们根据之前所学的知识. 假设这个质因数为2,那么2一定出现过$n/2$次, 4一定出现过 $n/4$次,如此循环下去,直至这个数大于n.

这样就方便算贡献了.

总时间复杂度为$sqrt(xlogx)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
 
long long ksm(long long a,long long b)
{
	long long ans=1,base=a;
	while(b)
	{
		if(b&1) ans*=base,ans%=mod;
		base*=base, base%=mod;
		b>>=1;
	}
	return ans%=mod;
}
long long x,n,pd;
long long ans=1,cnt[100005];
long long p[200005];
bool vis[1000005];
void get_pri(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			p[++p[0]]=i;
		}
		for(int j=1;i*p[j]<=n&&j<=p[0];j++)
		{
			vis[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
	
}
int main()
{
	scanf("%I64d%I64d",&x,&n);
 
	int len=sqrt(x);
	get_pri(len);
	p[++p[0]]=1e9;	
	for(int i=1;p[i]<=len;i++)
	{
		if(x%p[i]==0)
		{
			cnt[++cnt[0]]=p[i];
			while(x%p[i]==0)
			{
				x/=p[i];
			}
		}
	}
	if(x!=1)
	{
		cnt[++cnt[0]]=x;
	}//处理出x的素因子.
	for(int i=1;i<=cnt[0];i++)
	{
		long long c=n;
		while(c)//每个数的贡献为它的出现次数*素因子
		{
			ans*=ksm(cnt[i],c/cnt[i]);
			c/=cnt[i];
			ans%=mod;
		}
	}
	cout<<ans;
	return 0;
}
```


---

