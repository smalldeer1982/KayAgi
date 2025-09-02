# Sum of Remainders

## 题目描述

计算以下式子的和：$n \bmod 1 + n \bmod 2 + n \bmod 3 + \dots + n \bmod m$。由于结果可能很大，你需要输出其对 $10^9+7$ 取模的结果。

## 样例 #1

### 输入

```
3 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
```

### 输出

```
1
```

## 样例 #3

### 输入

```
1 1
```

### 输出

```
0
```

# 题解

## 作者：冒泡ioa (赞：7)

其实和[余数求和](https://www.luogu.org/problemnew/show/P2261)是同一道题...  
但是范围加大取模就有点容易载坑

还是说一下思路吧

首先我们要求的是:

$$\displaystyle\sum_{i=1}^m n\ mod \ i$$

其实取模操作特殊在没有什么特殊性  
基本上看到这种形式就会想到 $n\ mod\ i=n-  \left\lfloor\frac{n}{i}\right\rfloor\times i$

于是我们其实就是要求
$$n\times m-\displaystyle\sum_{i=1}^m\left\lfloor\frac{n}{i}\right\rfloor\times i$$

左边这一坨很好求,右边这一坨就要用到**整除分块**

其实也不是什么难理解的东西,其实就是**整除中,被除数一定的情况下,商随除数的增大而减小**  
由于是整数,所以这个减小是呈现出阶梯状的.  
于是我们就想通过当前的商,来推出当前阶梯在截止(~~在哪里需要减小~~)

听起来很难,其实稍微理解下就好(以下为非严谨但是易于理解的证明)  
首先我们设 $t=\left\lfloor\dfrac{n}{i}\right\rfloor$  
这个就是我们当前阶梯的高度了  
$t$ 的数学含义是, $n$ 里面包含了几个 $i$  
假设我们现在每个阶梯高度都是 $t$  
那么最多能维持多少个阶梯呢  
答案显然是 $\left\lfloor\dfrac{n}{\left\lfloor\frac{n}{i}\right\rfloor}\right\rfloor$  个  
于是我们的右边界就算出来了(还要对边界取min),时间复杂度$O(\sqrt{N})$

好吧我承认这样可能更难理解orz

```cpp
/*要特别注意边界情况*/
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mod=1e9+7;
LL n,m,ans,up,sum,r;
int main(){
    cin>>n>>m;
    ans=(n%mod)*(m%mod)%mod;
    up=min(n,m);
    sum=0;
    for(LL i=1;i<=up;++i){
        r=min(n/(n/i),up);
        LL a=i+r;
        LL b=r-i+1;
        if(a&1)b/=2;
        else a/=2;
        sum=(sum+((a%mod)*(b%mod)%mod)*(n/i)%mod)%mod;
        i=r;
    }
    cout<<(ans-sum+mod)%mod<<endl;
    return 0;
}
```
好吧 我就给出严谨一点的证明  
对于 $x\in [1,n]$ , 设 $g(x)=\left\lfloor\dfrac{n}{\left\lfloor\frac{n}{x}\right\rfloor}\right\rfloor$  
设 $f(x)=\dfrac{n}{x}$  注意这里的 $n$ 为常数  
对 $f(x)$ 求导得到 $f'(x)=-\dfrac{n}{x^2}$ 在 $[1,n]$ 衡小于0  
$f(x)$ 在 $[1,n]$ 单调递减  
而 $g(x)\ge \left\lfloor\dfrac{n}{\frac{n}{x}}\right\rfloor=x$  
所以 $\left\lfloor\dfrac{n}{x}\right\rfloor\ge \left\lfloor\dfrac{n}{g(x)}\right\rfloor$  

而且, $\left\lfloor\dfrac{n}{g(x)}\right\rfloor\ge \left\lfloor\dfrac{n}{\dfrac{n}{\left\lfloor\frac{n}{x}\right\rfloor}}\right\rfloor=\left\lfloor\dfrac{n}{x}\right\rfloor$

所以 $\left\lfloor\dfrac{n}{x}\right\rfloor=\left\lfloor\dfrac{n}{g(x)}\right\rfloor$

这个 $x$ 就是我们刚刚枚举的 $i$  
可以注意到,我们求出了一个 $g(x)$ 肯定是不小于 $x$ 但是它们的整除 $n$ 的值却是一样的,且它是符合要求的数里面最大的.

---

## 作者：喵仔牛奶 (赞：2)

题意：求

$$\sum_{i=1}^{i\leq m}n\text{ mod } i$$

化简式子：

$$\sum_{i=1}^{i\leq m}n-\lfloor\frac{n}{i}\rfloor \times i$$

$$nm-\sum_{i=1}^{i\leq m}\lfloor\frac{n}{i}\rfloor \times i$$

$$nm-\sum_{(l,r)}\lfloor\frac{n}{i}\rfloor \times \frac{r-l+1}{2}$$

然后后面一坨除法分块求一下即可，注意 $\frac{1}{2}\text{ mod }(10^9+7)=5\times10^8+4$ 。

时间复杂度 $O(n^{0.5})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
long long n, k, ans;
int main() {
	cin >> k >> n, ans = (n % mod) * (k % mod) % mod;
	for (long long l = 1, r; l <= n && l <= k; l = r + 1) {
		r = min(k / (k / l), n);
		ans = (ans - (k / l) % mod * ((l + r) % mod) % mod * ((r - l + 1) % mod) % mod * ((mod + 1) / 2) % mod) % mod;
	}
	cout << (ans + mod) % mod << '\n';
	return 0;
}
```

---

## 作者：Tony102 (赞：2)

# CF616E Sum of Remainders

[link](https://www.luogu.com.cn/problem/CF616E)

[更好的阅读体验](https://tony102.xyz/index.php/2020/11/14/cf616e-sum-of-remainders/)

### Sol

现在让你求的是 

$$\sum_{i = 1}^{m} n \ mod \ i$$

模运算这种东西就是带余除法，然后你发现余数你也很不好算。就考虑把模运算改成带余除法的形式

我们知道: $x \div i = \lfloor \frac{x}{i} \rfloor + x - (i \times \lfloor \frac{x}{i} \rfloor)$

所以现在要求的东西就是

$$\sum_{i=1}^{m} n - (i \times \lfloor \frac{n}{i} \rfloor)$$

$$n \times m - \sum_{i=1}^{m} i \times \lfloor \frac{n}{i} \rfloor$$

所以后面的东西整除分块一下就好了



### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int mod = 1e9 + 7;

int n, m;

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

inline int qPow(int a, int b)
{
	int ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % mod;
		b >>= 1, a = a * a % mod;
	}
	return ans % mod;
}

inline int minux(int a, int b) { return (a - b + 10 * mod) % mod; }

signed main()
{
	// freopen("code.in", "r", stdin);
	// freopen("code.out", "w", stdout);
	n = read(), m = read();
	int ans = (n % mod) * (m % mod) % mod, mul = qPow(2, mod - 2);
	for (int l = 1, r = 0; l <= m; l = r + 1) {
		if (n / l == 0) r = m;
		else r = std::min(m, (n / (n / l)));
		ans = (ans - 1ll * (n / l) % mod * ((l + r) % mod) % mod * ((r - l + 1ll) % mod) % mod * mul % mod + 10ll * mod) % mod;
	}
	printf("%lld\n", ans % mod);
	return 0;
}
```



---

## 作者：yizcdl2357 (赞：1)

[双倍经验](https://www.luogu.com.cn/problem/P2261)

# 题意简述

给定 $n,m$，求

$$\left(\sum_{i=1}^mn\bmod i\right)\bmod (10^9+7)$$

# 前置知识

[整除分块](https://www.luogu.com.cn/blog/340940/shuo-lun-han-shuo-di-shi-jie)，一定的数学推导能力。

# 解法

首先看到 $\bmod$ 我们就想到可能要用类似于整除分块的方法做。考虑利用如下式子：

$$a\bmod b=a-b\times \lfloor\dfrac{a}{b}\rfloor$$

（就是小学学过的，余数 $=$ 被除数 $-$ 除数 $\times$ 商）。

原式化为

$$\begin{aligned}
	 &\sum_{i=1}^m n\bmod i\\
   =&\sum_{i=1}^m (n-i\times \lfloor\dfrac{n}{i}\rfloor)&\text{（去掉 mod）}\\
   =&\left(\sum_{i=1}^m n\right)-\left(\sum_{i=1}^m i\times\lfloor\dfrac{n}{i}\rfloor\right)&\text{（减法性质）}\\
   =&\ mn-\left(\sum_{i=1}^m i\times\lfloor\dfrac{n}{i}\rfloor\right)&\text{（化简前半部分）}
\end{aligned}$$

接下来用整除分块计算后半部分，考虑把所有 $\lfloor\dfrac{n}{i}\rfloor$ 相等的 $i$ 的取值分成一个个区间。

假设 $\lfloor\dfrac{n}{i}\rfloor$ 在 $i\in[l,r]$ 上的值均为 $\lfloor\dfrac{n}{l}\rfloor$（当然也为 $\lfloor\dfrac{n}{r}\rfloor$，毕竟都相等）。那么我们有 

$$\begin{aligned}
	 &\sum_{i=1}^m i\times\lfloor\dfrac{n}{i}\rfloor\\
   =&\sum_{l,r}\sum_{i=l}^r i\times\lfloor\dfrac{n}{i}\rfloor&\text{（变成整除分块的形式）}\\
   =&\sum_{l,r}\lfloor\dfrac{n}{l}\rfloor\sum_{i=l}^r i&\text{（}\lfloor\dfrac{n}{i}\rfloor\text{为常数提到前面来）}\\
   =&\sum_{l,r}\lfloor\dfrac{n}{l}\rfloor\times(l+r)\times(r-l+1)\times\dfrac{1}{2}&\text{（等差数列求和）}
\end{aligned}$$

至此数学推导完成。

# 坑点：关于取模

1. 如果你是做完了 [P2261](https://www.luogu.com.cn/problem/P2261) 才过来的，那么，请记得取模。
2. 一定要步步取模，甚至计算 $mn$ 时，要先对 $n$ 和 $m$ 分别取模，乘起来后再模一次。具体见代码。
3. 式子里面最后那个 $\dfrac{1}{2}$ 在计算过程中不能直接除以 $2$，要乘上 $2$ 对模 $10^9+7$ 的[逆元](https://www.luogu.com.cn/problem/P3811)。
4. C++ 有一个特性：负数除以正数的余数仍然是负数。因此，如果想要得到余数的正数值，请不要使用 `x%y`，而是使用 `(x%y+y)%y`。

# 代码
```cpp
#include<iostream>
#include<cstdio>
#define int long long
#define M 1000000007
#define i2 500000004
using namespace std;
int m,n,ans; 
signed main()
{
	cin>>m>>n;
	ans=(n%M)*(m%M)%M;
	int r=1;
	for(int l=1;l<=min(n,m);l=r+1)
		r=min(m/(m/l),n),
		ans=(ans-(m/l)%M*((l+r)%M)%M*((r-l+1)%M)%M*i2%M)%M;
	cout<<(ans+M)%M;
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 分析

整除分块板子题（几乎与 [P2261](https://www.luogu.com.cn/problem/P2261) 完全相同）

首先，我们来推一波式子

$$
\begin{aligned}
\sum \limits_{i = 1}^m n \bmod i &= \sum \limits_{i = 1}^m(n - \lfloor\dfrac n i \rfloor i)\\
&= nm - \sum \limits_{i = 1}^m\lfloor\dfrac n i \rfloor i\\
\end{aligned}
$$

我们发现，$\sum \limits_{i = 1}^m\lfloor\dfrac n i \rfloor i$ 可以通过枚举不同的 $\lfloor\dfrac n i \rfloor$ 处理，而这个枚举可以通过整除分块来实现。

不难发现不同的 $\lfloor\dfrac n i \rfloor$ 仅有 $O(\sqrt n)$ 个，通过整除分块枚举一遍是 $O(\sqrt n)$ 复杂度

## 代码

```cpp
#include <stdio.h>
template<class T>
inline T min(const T &x, const T &y) { return x < y ? x : y; }
template<class T>
inline T max(const T &x, const T &y) { return x < y ? y : x; }
#define lld long long
const lld mod = 1e9 + 7;
lld n, m;
lld l, r;
lld ans;
int main() {
	scanf("%lld%lld", &m, &n);
	ans = (n % mod) * (m % mod);
	lld inv2 = (mod + 1) >> 1;
	for (l = 1; l <= n && l <= m; l = r + 1) {
		r = min(m / (m / l), n);
		ans = (ans - (m / l) % mod * ((l + r) % mod) % mod * ((r - l + 1) % mod) % mod * inv2 % mod) % mod; // 记得取模
	} // 整除分块
	printf("%lld\n", (ans + mod) % mod);
}
```

---

## 作者：wind_whisper (赞：0)

[更糟的阅读体验](https://blog.csdn.net/BUG_Creater_jie/article/details/122254012)
## $\text{Descripion}$
计算以下式子的和：$n \bmod 1 + n \bmod 2 + n \bmod 3 + \dots + n \bmod m$。由于结果可能很大，你需要输出其对 $10^9+7$ 取模的结果。
$n,m\le 10^{13}$
## $\text{Solution}$
式子可以写成：
$$\sum_{i=1}^mn-\lfloor\frac{n}{i}\rfloor\times i$$
直接上整除分块即可。
## $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

const int N=1e6+100;
const int mod=1e9+7;

ll n,m,ans;
ll ksm(ll x,ll k){
  ll res(1);
  while(k){
    if(k&1) res=res*x%mod;
    x=x*x%mod;
    k>>=1;
  }
  return res;
}

inline ll calc(ll l,ll r){return ((l+r)%mod)*((r-l+1)%mod)%mod*500000004%mod;}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  ans=(m%mod)*(n%mod)%mod;
  for(ll l=1,r;l<=min(n,m);l=r+1){
    r=min(m,n/(n/l));
    ll o=n/l%mod;
    ans=(ans+mod-o*calc(l,r)%mod)%mod;
    //printf("(%lld %lld) o=%lld\n",l,r,o);
  }
  printf("%lld\n",ans);
  return 0;
}
/*
 */

```


---

## 作者：FutaRimeWoawaSete (赞：0)

$n,m \leq 10 ^ {13}$ 是可以 $\sqrt n$ 级别过掉的，考虑整除分块。       

假设对于 $m$ 的一段取值 $[l,r]$，满足 $x \in [l,r] , \lfloor \frac{n}{x}\rfloor = k$。        

将 $l$ 写成 $l \times k + sim_1 = n$ 的形式，那么对于 $(l + 1) \times k + sim_2 = n,(l + 2) \times k + sim_3 = n......$ 而言，余数 $sim_i$ 每次针对于上一项 $sim_{i - 1}$ 会减少 $k$，这是一个经典的等差数列求和问题可以 $O(1)$ 算。             

对于 $m > n$ 的部分直接加上 $(m - n) \times n$ 即可。          

那么答案的时间复杂度就是形如 $i \in [1,n], \lfloor \frac{n}{i} \rfloor$ 的种类个数，这个用整除分块可以证明数量级是 $O(\sqrt n)$ 的。

```cpp
/*
举个例子，比如说对于n / x而言
如过x\in[l,r]时，ceil(n/x)值相等为k
那么就是l * k + sim1,(l+1) * k + sim2,(l + 2) * k + sim3
然后你发现sim是一个等差数列，直接算就好了 
*/
#include "bits/stdc++.h"
using namespace std;
const long long MOD = 1e9 + 7;
long long n,m,res,Inv2;
long long qpow(long long a,long long b)
{
	long long res = 1;
	while(b)
	{
		if(b & 1) res = res * a % MOD;
		b = b >> 1;
		a = a * a % MOD;
	}
	return res;
}
long long Fac(long long st,long long ed,long long len)
{
	long long s1 = (st + ed) , s2 = len;
	return (s1 % MOD) * (s2 % MOD) % MOD * Inv2 % MOD;
} 
signed main()
{
	scanf("%lld %lld",&n,&m);
	Inv2 = qpow(2 , MOD - 2);
	for(long long l = 1 , r ; l <= min(n , m) ; l = r + 1)
	{
		long long K = n / l;
		r = min(n / K , min(m , n));
		long long ST = n - (l * K) , ED = n - (r * K) , LEN = (ST - ED) / K + 1; 
		res += Fac(ST , ED , LEN);
		res %= MOD;
	} 
	if(m > n) res += (m - n) % MOD * (n % MOD) % MOD , res %= MOD;
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：chenxia25 (赞：0)

说到底是一道简单题，只不过不知道为啥是紫题？

考虑整除分块，把 $\bmod$ 号后面的数分成三段：$[1,\sqrt n],[\sqrt n,n],[n+1,m]$。第一段显然就暴力就可以了，第三段的值都是 $n$ 乘一下就可以了。重点在第二段。

我们枚举 $\left\lfloor\dfrac ni\right\rfloor$ 的值，然后由 $\left\lfloor\dfrac ni\right\rfloor=x$ 有 $x\leq \dfrac ni<x+1$，即 $\dfrac n{x+1}<i\leq \dfrac nx$。然后算出左右端点之后把 $\bmod$ 拆开：$\sum\limits_{i=l}^rn\bmod i=\sum\limits_{i=1}^r\left(n-i\left\lfloor\dfrac ni\right\rfloor\right)$，等差数列一下就可以了。

注意有几个小坑点，容易 WA，1A 的（如 tzc）都是神仙。

---

