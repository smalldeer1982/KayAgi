# [ABC212G] Power Pair

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc212/tasks/abc212_g

素数 $ P $ が与えられます。

以下の条件を満たす整数の組 $ (x,\ y) $ はいくつありますか？

- $ 0\ \leq\ x\ \leq\ P-1 $
- $ 0\ \leq\ y\ \leq\ P-1 $
- ある正整数 $ n $ が存在して、$ x^n\ \equiv\ y\ \pmod{P} $ を満たす

ただし答えは非常に大きくなる可能性があるので、$ 998244353 $ で割った余りを出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ P\ \leq\ 10^{12} $
- $ P $ は素数

### Sample Explanation 1

$ (x,\ y)\ =\ (0,\ 0),\ (1,\ 1),\ (2,\ 1),\ (2,\ 2) $ の $ 4 $ 組が条件を満たします。

## 样例 #1

### 输入

```
3```

### 输出

```
4```

## 样例 #2

### 输入

```
11```

### 输出

```
64```

## 样例 #3

### 输入

```
998244353```

### 输出

```
329133417```

# 题解

## 作者：TernaryTree (赞：3)

**注：若无特殊说明，本文中，$\mathbb N$ 指不包括 $0$ 的自然数集，即正整数集。**

前置知识：数论推式子基础，原根的基本定义及其性质。

题意所求可以化为这个式子：

$$\sum_{x=0}^{p-1}\sum_{y=0}^{p-1}\left[ \exists\  n\in \mathbb{N},\ x^n\equiv y\pmod p \right]$$



首先 $x=0$ 时，仅有 $y=0$ 符合条件。同样，当 $y=0$ 是，仅有 $x=0$ 符合。故原式化为

$$1+\sum_{x=1}^{p-1}\sum_{y=1}^{p-1}\left[ \exists\  n\in \mathbb{N},\ x^n\equiv y\pmod p \right]$$

由原根的性质，设 $g$ 为 $p$ 的一个原根。因为 $p$ 是质数，故有：

$$\forall\  k\in\mathbb{N},\ 1\le k\le p-1\quad \exists\  n\in\mathbb{N},\ 1\le n\le p-1, \ g^n\equiv k\pmod p$$

也就意味着，$S=\{g^n\ |\ n\in \mathbb N, \ 1\le n\le p-1\}$ 构成了 $[1,p-1]$ 的一个排列。

我们设 $x=g^a,\ y=g^b$。则原式化为

$$1+\sum_{a=1}^{p-1}\sum_{b=1}^{p-1}\left[ \exists\  n\in \mathbb{N},\ g^{an}\equiv g^b\pmod p \right]$$

又由欧拉定理，$g^x\bmod p$ 的循环节为 $\varphi(p)=p-1$，故有原式等于

$$1+\sum_{a=1}^{p-1}\sum_{b=1}^{p-1}\left[ \exists\  n\in \mathbb{N},\ an\equiv b\pmod {p-1} \right]$$

由裴蜀定理，形如 $ax+by=c$ 的二元一次不定方程有解，当且仅当 $\gcd(a,b)\ |\ c$。原式化为

$$1+\sum_{a=1}^{p-1}\sum_{b=1}^{p-1}\left[\gcd(a,p-1)\ | \ b \right]$$

设 $b=k\gcd(a,p-1)$，其中 $k\in \mathbb N$。枚举 $k$，原式等于

$$
\begin{aligned}
&1+\sum_{a=1}^{p-1}\sum_{k=1}\left[k\gcd(a,p-1)\le p-1\right] \\
=\ &1+\sum_{a=1}^{p-1}\sum_{k=1}\left[k\le \dfrac{p-1}{\gcd(a,p-1)}\right] \\
=\ &1+\sum_{a=1}^{p-1}\dfrac{p-1}{\gcd(a,p-1)}\\
\end{aligned}
$$

接下来是一波很典的推式子。设 $f(n)=\sum\limits_{i=1}^n \dfrac{n}{\gcd(i,n)}$。

则 

$$
\begin{aligned}
f(n)&=\sum\limits_{i=1}^n \dfrac{n}{\gcd(i,n)} \\
&=\sum\limits_{i=1}^n \sum_{d| i, d |  n}\dfrac nd[{\gcd(i,n)}=d] \\
&= \sum_{d |  n}\dfrac nd\sum\limits_{i=1}^{\frac nd}[{\gcd(i,\dfrac nd)}=1] \\
&= \sum_{d |  n}\dfrac nd\varphi(\dfrac nd) \\
&= \sum_{d |  n}d\varphi(d) \\
\end{aligned}
$$

于是我们要求的式子就是

$$
\begin{aligned}
&1+f(p-1) \\
=\ &1+\sum_{d | (p-1)}\varphi(d)d
\end{aligned}
$$

这个东西最坏复杂度是 $\Theta(\operatorname{d}(n)\sqrt n)$ 的，当然常数貌似很小的样子，$10^{12}$ 轻松跑过。

代码：

```cpp
#include <stdio.h>
#define int long long

const int mod = 998244353;

int n, i, sum = 1;

int phi(int x) {
    int ans = x;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            ans = ans / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x > 1) ans = ans / x * (x - 1);
    return ans % mod;
}

signed main() {
    scanf("%lld", &n);
    --n;
    for (i = 1; i * i < n; ++i) {
        if (n % i == 0) {
            sum += i * phi(i) % mod;
            sum %= mod;
            sum += ((n / i) % mod) * (phi(n / i) % mod) % mod;
            sum %= mod;
        }
    }
    if (i * i == n) {
        sum += i * phi(i);
        sum %= mod;
    }
    printf("%lld\n", sum);
    return 0;
}
```

---

## 作者：EuphoricStar (赞：3)

设 $P$ 的原根为 $g$，那么 $x,y$ 可以表示成 $g^a, g^b$ 的形式（特判 $x = y = 0$）。那么要求 $an \equiv b \pmod {P - 1}$，其中 $a,b \in [1, P - 1]$。

考虑固定 $a$，可以把问题看成，有 $P - 1$ 个点的环，点编号 $1 \sim P - 1$，从 $1$ 开始每次跳 $a$ 步，跳到的本质不同点数。这是经典问题，考虑循环节即 $\frac{P - 1}{\gcd(P - 1, a)}$，所以本质不同点数是 $\frac{P - 1}{\gcd(P - 1, a)}$。下文令 $n = P - 1$。

于是现在要求 $\sum\limits_{x=1}^n \frac{n}{\gcd(n, x)}$。考虑求出 $n$ 的所有因数 $a_1, a_2, ..., a_m$，设 $f_i$ 为 $\sum\limits_{x=1}^n [\gcd(x, n) = a_i]$，那么 $f_i$ 可容斥得出，即 $f_i = \frac{n}{a_i} - \sum\limits_{j \in [i+1, m] \land a_i \mid a_j} f_j$，那么最终答案就是：

$$ans = \sum\limits_{i=1}^m f_i \times \frac{n}{a_i}$$

时间复杂度 $O(\sqrt{P} + d(n)^2)$，其中 $d(n)$ 为 $n$ 的因数个数。

[code](https://atcoder.jp/contests/abc212/submissions/41493241)

---

## 作者：Lazy_Labs (赞：3)

# 0.说在前面
好题！做就是了！

前置芝士：阶的定义，一些简单的数论函数的推法
# 1.转化题面
显然可以发现，题目可以变为枚举 $x$，算出对于 $x$ 的次幂模 $p$ 所能产生的数的个数。记为 $\delta_p(x)$

当 $p$ 为质数时，$\forall i,0\le i<p$ 均存在 $j$ 使得 $i^j \equiv 1 \pmod p$。

我们可以发现，$\delta_p (i)$ 为最小的 $j$，即阶。

对于质数 $p$，我们知道 $\delta_p(x)=\dfrac{\varphi(p)}{\gcd(\varphi(p),x)}$。

简单证明如下：

显然$x^\tfrac{\varphi(p)}{\gcd(\varphi(p),x)}\equiv1\pmod p$，所以 $\delta_p(x)\le\dfrac{\varphi(p)}{\gcd(\varphi(p),x)}$ （原根的定义）

而 $\delta_p(x^\tfrac{1}{\gcd(\varphi(p),x)})=\varphi(p)$，所以 $\delta_p(x)\ge\dfrac{\varphi(p)}{\gcd(\varphi(p),x)}$。

的证。

注意可以 $x=y=0$，所以原题可以变为：

$$1+\sum_{x=1}^{\varphi(p)}\frac{\varphi(p)}{\gcd(\varphi(p),x)}$$

# 2.推式子
我们令 $n=\varphi(p)$：

$$
\begin{aligned}
\sum_{x=1}^{n}\frac{n}{\gcd(n,x)}&=\sum_{d|n}\sum_{x=1}^{\tfrac{n}{d}}\frac{n}{d}[\gcd(n,xd)=d] \\
&=\sum_{d|n}\sum_{x=1}^{\tfrac{n}{d}}\frac{n}{d}[\gcd(\frac{n}{d},x)=1]\\
&=\sum_{d|n}d\sum_{x=1}^{d}[\gcd(d,x)=1]\\
&=\sum_{d|n}d\varphi(d) \\
\end{aligned}
$$

我们令 $f(x)=x\varphi(x)$（这显然是一个积性函数），则答案为：$f * 1$ 同样也是一个积性函数。

令 $g=f*1$。

可知 $p$ 为质数时，$g(p^a)=\dfrac{p^{2a}-1}{p+1}\times p$。
# 3.维护
我们发现答案为 $1+(f * 1)(\varphi(p))=1+(f*1)(p-1)$。

又因为后者为积性函数，所以可以用筛法筛 $1\le x \le \sqrt {p-1}$ ，再用积性函数的性质维护。

理论时间复杂度 $O(\sqrt p)$，实际上直接把线性筛处理到 $10^6$ 即可。（这样的时间复杂度才对嘛，玄学被卡了就不好力）
# 4.CODE
```cpp
#include<bits/stdc++.h>
#define ll long long
#define int ll
using namespace std;
inline int read()
{
	int x(0),f(1);char c=getchar();
	while(c<'0'||c>'9')f=c=='-'?-1:1,c=getchar();
	while(c<='9'&&c>='0')x=x*10+c-48,c=getchar();
	return x*f;
}
const int N=1000010,mod=998244353;
int pri[N],tot;bool vis[N];
void limit()
{
	vis[1]=1;
	for(int i=2;i<=N-10;i++)
	{
		if(!vis[i])pri[++tot]=i;
		for(int j=1;j<=tot&&pri[j]*i<=N-10;j++)
		{
			vis[pri[j]*i]=1;
			if(i%pri[j]==0)break;
		}
	}
}
int ksm(int a,int n)
{
	int ans=1;
	while(n)
	{
		if(n&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;n>>=1;
	}
	return ans;
}
signed main()
{
	limit();
	int p=read()-1,ans=1;
//	for(int i=1;i<=p;i++)printf("%d ",phi[i]);puts("");
//	for(int i=1;pri[i]<=p;i++)printf("%d ",pri[i]);
	for(int i=1;pri[i]*pri[i]<=p;i++)if(p%pri[i]==0)
	{
		ll cnt=0;while(p%pri[i]==0)p/=pri[i],cnt++;
		ans=1ll*(1ll*(ksm(pri[i],cnt<<1)-1+mod)%mod*ksm(pri[i]+1,mod-2)%mod*pri[i]%mod+1)%mod*ans%mod;
		if(ans<0)exit(114514);
	}
	if(p>1)ans=1ll*((__int128)p*(p-1)%mod+1)%mod*ans%mod;
	printf("%lld",(ans+1)%mod);
	return 0;
}
```

---

## 作者：Register_int (赞：2)

直接来推柿子。设 $g$ 为 $\bmod\ n$ 意义下的原根，则：
$$
\begin{aligned}
&\sum^{n-1}_i\sum^{n-1}_j[\exists x\in\mathbb{N},i^x\equiv j\pmod n]\\
=&1+\sum^{n-1}_{i=1}\sum^{n-1}_{j=1}[\exists x\in\mathbb{N}^+,g^{ix}\equiv g^j\pmod n]\\
=&1+\sum^{n-1}_{i=1}\sum^{n-1}_{j=1}[\exists x\in\mathbb{N}^+,ix\equiv j\pmod{n-1}]\\
=&1+\sum^{n}_{i=1}\sum^{n}_{j=1}[\gcd(i,n)|j]\ \ \{n\rightarrow n-1\}\\
=&1+\sum^{n}_{i=1}\dfrac{n}{\gcd(i,n)}\\
=&1+\sum_{d|n}\sum^{\frac nd}_{i=1}\frac nd[\gcd(i,n)=d]\\
=&1+\sum_{d|n}\dfrac nd\sum^{\frac nd}_{i=1}[\gcd(i,\frac nd)=1]\\
=&1+\sum_{d|n}\dfrac nd\varphi(\dfrac nd)\\
=&1+\sum_{d|n}d\varphi(d)\\
\end{aligned}
$$
直接计算，复杂度不会算，但大概是 $O(n^\frac23)\sim O(n^\frac34)$，可以通过。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;

inline 
ll phi(ll n) {
	ll res = n;
	for (int i = 2; i <= n / i; i++) {
		if (n % i == 0) {
			res -= res / i;
			while (n % i == 0) n /= i;
		}
	}
	if (n > 1) res -= res / n;
	return res % mod;
}

ll n, ans = 1;

int main() {
	scanf("%lld", &n), n--;
	for (int i = 1; i <= n / i; i++) {
		if (n % i == 0) {
			ans = (ans + i * phi(i) % mod) % mod;
			if (i != n / i) ans = (ans + (n / i) % mod * phi(n / i) % mod) % mod;
		}
	}
	printf("%lld", ans);
}
```

---

## 作者：Kreado (赞：2)

今天考到了，顺便水一下题解。

[题目传送门](https://www.luogu.com.cn/problem/AT_abc212_g)。

#### 思路

根据题意，可以列出

$$\sum_{x=0}^{P-1}\sum_{y=0}^{P-1}[\exists n\in \mathbb{N} ,x^n \equiv y \pmod P]$$

当然对于 $x=0$ 的情况我们要特别处理，对于下文推式子有好处，也就是

$$1+\sum_{x=1}^{P-1}\sum_{y=1}^{P-1}[\exists n\in \mathbb{N},x^n \equiv y \pmod P]$$

设 $g$ 为模 $P$ 意义下的原根，有

$$x\equiv g^a,y\equiv g^b \pmod P$$

有以下转化

$$g^{an}\equiv g^b \pmod P$$

得到

$$an\equiv b \pmod {P-1}$$

这个可以看成一个环，对于 $\exists n\in \mathbb{N}$，那么得到的 $b$ 有 $\dfrac{\operatorname{lcm}(a,P-1)}{a}$ 种，即 $\dfrac{P-1}{\gcd(a,P-1)}$。

原式即可化成

$$\begin{aligned}&1+\sum_{x=1}^{P-1}\dfrac{P-1}{\gcd(a,P-1)}\\&=1+\sum_{i|P-1}\dfrac{P-1}{i}\times \sum_{j=1}^{\frac{P-1}{i}}[\gcd(\frac{P-1}{i},j=1)]\\&=1+\sum_{i|d}\dfrac{P-1}{i}\varphi(\frac{P-1}{i})\end{aligned}$$

时间复杂度 $O(\sqrt n \times d(n^2))$，可以过。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Mod=998244353;
ll P,ans;
inline ll Getphi(ll x){
	ll phi=x;
	for(ll i=2;i*i<=x;i++)
		if(x%i==0){
			phi/=i,phi*=(i-1);
			while(!(x%i)) x/=i;
		}
	if(x!=1) phi/=x,phi*=(x-1);
	return phi;
}
void solve(ll x){
	ans=(ans+1ll*Getphi(P/x)%Mod*(P/x%Mod)%Mod)%Mod;
}
int main(){
	scanf("%lld",&P);P-=1;ans=1;
	for(ll i=1;i*i<=P;++i){
		if(P%i==0){
			solve(i);
			if(i*i!=P) solve(P/i);
		}
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：yqr123YQR (赞：0)

### 题意
> 给定质数 $P$，求有多少组 $(x,y)(0\leqslant x,y<P)$ 使得 $\exists n\in\N^*,x^n\equiv y\pmod P$，答案对 $998244353$ 取模。

### 思路
（以下 $\log$ 均代指 $\operatorname{ind}$）。

若 $x=0$，则 $y=0$，反之亦然。考虑 $x\ne0,y\ne0$：
$$
\begin{aligned}
&x^n\equiv y\pmod P\\
\Longleftrightarrow&\exists n,n\log x\equiv\log y\pmod{\varphi(P)}\\
\Longleftrightarrow&\exists n,k,n\log x+k\varphi(P)=\log y\\
\Longleftrightarrow&\gcd(\log x,\varphi(P))\mid\log y
\end{aligned}
$$
由于 $0<\log y\leqslant\varphi(P)$，固定 $x$ 时共 $\Large\frac{\varphi(P)}{\gcd(\log x,\varphi(P))}$ 个 $y$。

化简上式：
$$
\begin{aligned}
\sum\limits_{i=1}^{\varphi(P)}\frac{\varphi(P)}{\gcd(i,\varphi(P))}&=\sum_{d\mid\varphi(P)}\frac{\varphi(P)}d\sum_{i=1}^{\varphi(P)}[\gcd(i,\varphi(P))=d]\\
&=\sum_{d\mid\varphi(P)}\frac{\varphi(P)}d\sum_{d\mid i}[\gcd(i,\varphi(P))=d]\\
&=\sum_{d\mid\varphi(P)}\frac{\varphi(P)}d\sum_{i=1}^{\frac{\varphi(P)}d}[\gcd(id,\varphi(P))=d]\\
&=\sum_{d\mid\varphi(P)}\frac{\varphi(P)}d\sum_{i=1}^{\frac{\varphi(P)}d}[\gcd(i,\frac{\varphi(P)}d)=1]\\
&=\sum_{d\mid\varphi(P)}\frac{\varphi(P)}d\varphi(\frac{\varphi(P)}d)\\
&=\sum_{d\mid\varphi(P)}d\cdot\varphi(d)\\
&=\sum_{d\mid P-1}d\cdot\varphi(d)
\end{aligned}
$$
直接算。复杂度为枚举因数 $O(\sqrt P)$ 及算 $\varphi$ 两部分。由于算 $\varphi$ 的复杂度为该数的最大质因子，远不及 $\sqrt n$ 级别，其实比较快。

### 代码
```cpp
#include<stdio.h>
typedef long long ll;
const int mod = 998244353;
ll p;
ll phi(ll x)
{
	ll ret = x, nx = x;
	for(int i = 2; i <= x / i; i++)
	{
		if(x % i) continue;
		while(x % i == 0) x /= i;
		ret = ret / i * (i - 1);
	}
	if(x > 1) ret = ret / x * (x - 1);
	return ret % mod;
}
ll solve()
{
	ll t = p - 1, ret = 1;//1 是为了单独算 (0,0)
	for(int i = 1; i <= t / i; i++)
	{
		if(t % i) continue;
		(ret += i * phi(i) % mod) %= mod;
		if(t / i != i) (ret += (t / i % mod) * phi(t / i) % mod) %= mod;
	}
	return ret;
}
int main()
{
	scanf("%lld", &p);
	printf("%lld\n", solve());
	return 0;
}
```

---

## 作者：_edge_ (赞：0)

理性愉悦。

下面令 $n=p-1$。

注意到我们需要求的是 $\sum \limits _{i=1}^{n} \gcd(n,i)$，对它进行莫反得到 $\sum \limits _{d|n} \dfrac{n}{d} \times 
\varphi(\dfrac{n}{d})$，注意到这是一个积性函数，所以我们可以直接在他的质数幂次上进行操作，最后乘起来就是答案。

于是上个 Pollard-Rho 即可解决。

时间复杂度 $O(n^{\frac{1}{4}})$，目前是最优解。

[code](https://www.luogu.com.cn/paste/z4t36cwc)


---

