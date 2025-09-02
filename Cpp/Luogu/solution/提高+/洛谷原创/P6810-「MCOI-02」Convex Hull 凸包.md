# 「MCOI-02」Convex Hull 凸包

## 题目背景

一场比赛需要一道签到题。

## 题目描述

Leasier 玩 MC 被逮到了，所以他只好算出下面这个式子的值。

$$\displaystyle\sum_{i = 1}^n \sum_{j = 1}^m \tau(i) \tau(j) \tau(\gcd(i, j))$$

由于结果可能很大，所以你只需要求出结果对 $p$ 取模的值。

如果您对本题的数学符号有疑问，请到「提示」区查看提示。

## 说明/提示

#### 数据规模和约定
**本题开启捆绑测试。**

| Subtask | $n, m$ | 分值 |
| :------: | :------: | :------: |
| $1$ | $1 \leq n, m \leq 10^3$ | $15 \operatorname{pts}$ |
| $2$ | $1 \leq n, m \leq 10^5$ | $25 \operatorname{pts}$ |
| $3$ | $1 \leq n, m \leq 10^6$ | $30 \operatorname{pts}$ |
| $4$ | 无特殊限制 | $30 \operatorname{pts}$ |

对于 $100\%$ 的数据，$1 \leq n, m \leq 2 \times 10^6$，$1 \leq p \leq 10^9$。
#### 提示
作为对萌新友好的签到题，肯定是要给提示的。

- $\sum$ 为求和符号，比如 $\displaystyle\sum_{i = 1}^n i$ 代表 $1 + 2 + \cdots + n$。
- $\tau$ 表示约数个数，比如 $\tau(6) = 4$。
- $\gcd$ 是最大公约数，比如 $\gcd(12, 15) = 3$。
#### 说明
Minecraft OI Round 2 A

- Maker：Leasier
- Tester：happydef

## 样例 #1

### 输入

```
5 7 9```

### 输出

```
5```

# 题解

## 作者：Spasmodic (赞：44)

验题人写的一个题解，感觉比出题人的式子简单多了，而且用不着莫反。

$$\sum_{i\le n}\sum_{j\le m}\tau(i)\tau(j)\tau(\gcd(i,j))$$
考虑$\tau$的定义，有：
$$=\sum_{i\le n}\sum_{j\le m}\tau(i)\tau(j)\sum_{k|i,k|j}1$$
枚举$k$：
$$=\sum_k\sum_{k|i,i\le n}\tau(i)\sum_{k|j,j\le m}\tau(j)$$
设
$$S_n(k)=\sum_{k|i,i\le n}\tau(i)$$
则
$$(*)=\sum_kS_n(k)S_m(k)$$
式子推完了！

先在 $O(n\log n)$ 时间内暴力预计算出 $\tau(i),1\le i\le n$，然后可以在 $O(n\log n)$ 时间内暴力预计算出 $S_n(k),S_m(k)$，总复杂度 $O(n\log n)$。

放个代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2000005;
int n,m,p,d[N],ans;
void init(int n){
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=i)
			d[j]++;
}
inline int calc(int n,int k){
	int ret=0;
	for(int i=k;i<=n;i+=k)ret=(ret+d[i])%p;
	return ret;
}
int main(){
	scanf("%d%d%d",&n,&m,&p);
	if(n>m)swap(n,m);
	init(m);
	for(int i=1;i<=n;i++)ans=(ans+1LL*calc(n,i)*calc(m,i)%p)%p;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：ForgotMe (赞：11)

~~这个题是真的板。~~

求
$$
\sum_{i=1}^n\sum_{j=1}^mτ(i)τ(j)τ(\gcd(i,j))
$$

直接枚举 $\gcd$

$$
\sum_{d=1}^{\min(n,m)}τ(d)\sum_{i=1}^n\sum_{j=1}^mτ(i)τ(j)[\gcd(i,j)=d]
$$

$$
\sum_{d=1}^{\min(n,m)}τ(d)\sum_{i=1}^n\sum_{j=1}^mτ(i)τ(j)[\gcd(i,j)=d]
$$
$$
\sum_{d=1}^{\min(n,m)}τ(d)\sum_{i=1}^{\frac{n}{d}}\sum_{j=1}^{\frac{m}{d}}τ(id)τ(jd)[\gcd(i,j)=1]
$$
$$
\sum_{d=1}^{\min(n,m)}τ(d)\sum_{D=1}^{\frac{n}{d}}\mu(D)\sum_{i=1}^{\frac{n}{dD}}\sum_{j=1}^{\frac{m}{dD}}τ(idD)τ(jdD)
$$

$$
\sum_{T=1}^{\min(n,m)}\sum_{d|T}τ(d)\mu(\dfrac{T}{d})\sum_{i=1}^{\frac{n}{T}}τ(iT)\sum_{j=1}^{\frac{m}{T}}τ(jT)
$$

$\sum_{d|T}τ(d)\mu(\dfrac{T}{d})$ 这个东西可以用狄利克雷卷积推出值恒为 $1$。

于是只需要算

$$
\sum_{T=1}^{\min(n,m)}\sum_{i=1}^{\frac{n}{T}}τ(iT)\sum_{j=1}^{\frac{m}{T}}τ(jT)
$$

当然你可以直接算，时间复杂度为 $\mathcal{O(\min(n,m) (\ln n+\ln m))}$ 。

这里发现后面可以用 Dirichlet 后缀和优化，只需要把 Dirichlet 前缀和倒着写就好了。

不会请左转模板区 [Dirichlet 前缀和](https://www.luogu.com.cn/problem/P5495)。

时间复杂度变为 $\mathcal{O(\min(n,m) (\log \log n+\log\log m))}$。

代码
```cpp
#include <cstdio>
#include <cmath>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <map>
using namespace std;
int n, m, p, ans, len, T[2000005], prime[2000005], a[2000005], b[2000005], e[2000005];
bool vis[2000005];
void seive() {
    T[1] = 1;
    for (int i = 2; i <= m; i++) {
        if (!vis[i])
            prime[++len] = i, T[i] = 2, e[i] = 1;
        for (int j = 1; j <= len && i * prime[j] <= m; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                T[i * prime[j]] = T[i] / (e[i] + 1) * (e[i] + 2);
                e[i * prime[j]] = e[i] + 1;
                break;
            } else
                T[i * prime[j]] = T[i] * 2, e[i * prime[j]] = 1;
        }
    }
}
int main() {
    scanf("%d %d %d", &n, &m, &p);
    if (n > m)
        swap(n, m);
    seive();
    for (int i = 1; i <= m; i++) {
        if (i <= n)
            a[i] = T[i];
        b[i] = T[i];
    }
    for (int i = 1; i <= len; i++)
        for (int j = n / prime[i]; j; j--) a[j] = (a[j] + a[j * prime[i]]) % p;
    for (int i = 1; i <= len; i++)
        for (int j = m / prime[i]; j; j--) b[j] = (b[j] + b[j * prime[i]]) % p;
    for (int i = 1; i <= n; i++) ans = (ans + 1ll * a[i] * b[i]) % p;
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：genshy (赞：9)

### 一句话题意：

求出 $\displaystyle\sum_{i=1}^{n}\sum_{j=1}^{m}\tau(i)\tau(j)\tau(gcd(i,j))$

### 前置知识

1. $dirirchlet$ 卷积

   这里我们只需要了解他的一个性质， $\tau * \mu = \epsilon$, 具体证明如下：

   > $\tau  = 1 * 1$，
   > $\epsilon = \mu * 1$
   >
   > 对于第一个柿子，两边同时卷上一个 $\mu$ 变成：
   >
   > $\tau * \mu = 1 * 1 * \mu$
   >
   > $\tau * \mu = 1 * \epsilon = 1$

 2.线性筛约数个数

​		首先，我们对一个数有唯一分解定理：$p = p_1^{k_1} \times p_2^{k2} \cdots p_n ^{kn}$

​		那么这个数的约数个数可以写为 $\prod (k_i+1)$ ~~(这小学知识啦~~)。

​		我们维护两个数组 $g[i]$ 表示 $i$ 的最小质因子的次数， $t[i]$ 表示 $i$ 的约数个数和。

​		对于 质数 $p$ 则有 $g[p] = 1, t[p] = 2$

​		对于不是质数的数 $n$ 我们在筛的时候会在 $i \times p$ 的时候筛到他。

​		若 $i \bmod p == 0$ 表明 $p$ 是 $n$ 的最小质因子 ，

则有 $g[n] = 1$, $f[n] =$ $f[i] \times (g[n]+1) \over {g[i]+1}$

​		若 $i 和 p 互质$ 可以利用积性函数的性质求解，则有 $g[n] = g[i] + 1$

$f[n] = f[i] * f[p]$ ， 也可以写成 $f[n] = f[i] * 2$

**Code**:	

```cpp
	g[1] = 1; t[1] = 1;
	for(int i = 2; i <= N-5; i++)
	{
		if(!check[i])
		{
			prime[++tot] = i;
			g[i] = 1;
			t[i] = 2;
		}
		for(int j = 1; j <= tot && i * prime[j] <= N-5; j++)
		{
			check[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				g[i * prime[j]] = g[i] + 1;
				t[i * prime[j]] = t[i] * (g[i * prime[j]] + 1) / (g[i] + 1);
				break;
			}
			else
			{
				g[i * prime[j]] = 1;
				t[i * prime[j]] = t[i] * t[prime[j]];
			}
		}
	}
```

​			

### **题解**

比较难的懵逼乌斯反演题。

首先，我们还是按照套路先枚举一个 $d$ 来变成：

$\displaystyle\sum_{d=1}^{n}\tau(d) \sum_{i=1}^{n} \sum_{j=1}^{m}\tau(i)\tau(j)[gcd(i,j) == d]$

后面那两个求和柿子可以提出一个 $d$ 出来变成：

$\displaystyle\sum_{d=1}^{n}\tau(d) \sum_{i=1}^{n\over d} \sum_{j=1}^{m\over d}\tau(i \times d)\tau(j \times d)[gcd(i,j) == 1]$

根据莫比乌斯反演，我们可以得到一个等式：

$[gc(i,j) == 1] = \displaystyle\sum_{p\mid i,p\mid j} \mu(p)$

把这个等式代回原式有：

$\displaystyle\sum_{d=1}^{n}\tau(d)\sum_{i=1}^{n\over d}\sum_{j=1}^{m \over d}\tau(i \times d)\tau(j\times d) \sum_{p\mid i p\mid j} \mu(p)$

先枚举一下 $p$ 变成：

$\displaystyle\sum_{d=1}^{n}\tau(d)\sum_{p=1}^{n\over d} \mu(p)\sum_{i=1}^{n\over d} \tau(i \times d)[p \mid i]\sum_{j=1}^{m \over d}\tau(j \times d) [p \mid j]$

后面的那个求和柿子可以变成：

$\displaystyle\sum_{d=1}^{n}\tau(d)\sum_{p=1}^{n\over d} \mu(p)\sum_{i=1}^{n\over {dp}} \tau(i \times d p) \sum_{j=1}^{m \over {dp}}\tau(j \times dp)$

设 $Q = dp$ 则 $p = {Q \over d}$,柿子可以写成：

$\displaystyle\sum_{d=1}^{n}\tau(d)\sum_{Q=1}^{n}\mu({Q\over d})\sum_{i=1}^{n\over Q}\sum_{j = 1}^{m \over Q}\tau(iQ)\tau(jQ)$

改变一下枚举顺序，先枚举一下 $Q$ 则有：

$\displaystyle\sum_{Q=1}^{n}\sum_{d\mid Q}^{n} \tau(d)\mu({Q\over d})\sum_{i=1}^{n\over Q}\sum_{j=1}^{m\over Q}\tau(iQ)\tau(jQ)$

 中间的这个 $\displaystyle\sum_{d\mid Q}^{n}\tau(d)\mu({Q\over d})$ 柿子，利用我们前置知识里的一个性质：$\tau * \mu = 1$ 也就是这个柿子恒等于 $1$

我们的柿子就可以变为：

$\displaystyle\sum_{Q=1}^{n}\sum_{i=1}^{n\over Q}\sum_{j=1}^{m\over Q} \tau(iQ)\tau(jQ)$

这个直接枚举的复杂度跟定会爆的，我们还要考虑优化。

我们可以对于每个 $Q$ 先把他后面的两个柿子先预处理出来，之后我们在枚举每个 $Q$ 时可以直接得到这个 $Q$ 的·贡献。

据说还可以用 $dirichlet$ 后缀和优化，然鹅我并不会。

**Code**

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2e6+10;
int n,m,p,tot;
int t[N],g[N],prime[N],sum1[N],sum2[N];
bool check[N];
inline int read()
{
	int s = 0,w = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') w = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){s =s * 10+ch - '0'; ch = getchar();}
	return s * w;
}
void YYCH()
{
	g[1] = 1; t[1] = 1;
	for(int i = 2; i <= N-5; i++)//预处理出每个数的约数个数
	{
		if(!check[i])
		{
			prime[++tot] = i;
			g[i] = 1;
			t[i] = 2;
		}
		for(int j = 1; j <= tot && i * prime[j] <= N-5; j++)
		{
			check[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				g[i * prime[j]] = g[i] + 1;
				t[i * prime[j]] = t[i] * (g[i * prime[j]] + 1) / (g[i] + 1);
				break;
			}
			else
			{
				g[i * prime[j]] = 1;
				t[i * prime[j]] = t[i] * t[prime[j]];
			}
		}
	}
}
int slove(int n,int m)
{
	YYCH();
	int res = 0;
	for(int d = 1; d <= n; d++)//预处理出每个 Q 的贡献
	{
		for(int j = 1; j <= n/d; j++)
		{
			sum1[d] = (sum1[d] + t[j * d]) % p;
		}
	}
	for(int d = 1; d <= m; d++)
	{
		for(int j = 1; j <= m/d; j++)
		{
			sum2[d] = (sum2[d] + t[j * d]) % p;
		}
	}
	for(int d = 1; d <= n; d++)//枚举每个Q
	{
		res = (res + 1LL * sum1[d] * sum2[d] % p) % p;//计算答案
	}
	return res % p;
}
int main()
{
	n = read(); m = read(); p = read();
	if(n > m) swap(n,m);
	printf("%d\n",slove(n,m));
	return 0;
}
```



 话说，这题感觉难度有点低，应该是紫题吧，毕竟最后的 $dirichlet$ 后缀和优化的模板也是紫的。

---

## 作者：quest_2 (赞：8)


推一下蒟蒻 [$\green{\texttt{博客}}$](https://www.luogu.com.cn/blog/quest233/#) ～

-----

粗略捞了一眼题解区，觉得有些比较重要的细节不是很懂，自己瞎撞撞终于搞明白乐。/kk

所以本篇文章用于解释一些思维上的细节。

### 一、$\tau*\mu=1 $ ?

我们了解到 $\sum_{d|n} \mu(d)\cdot 1=[n=1]$ ，表达成卷积形式有：

$$1*\mu=\epsilon$$

而当我们展开 $\tau$ 可得： 

$$\tau(n)=\sum_{d|n} 1\cdot 1$$

$$\tau=1*1$$

等式两边同卷 $\mu$ ：

$$\tau*\mu=1*1*\mu$$

用 $\epsilon$ 换 $1*\mu$ ：

$$\tau*\mu=1*\epsilon$$

因为 $1*\epsilon=1$ ，所以我们就证得了：

$$\tau*\mu=1$$

### 二、大众推柿子思路

_默认 $n<m$_

$$\sum^{n}_{i}\sum^{m}_{j}\tau(i)\tau(j)\tau(\gcd(i,j))$$

$$=\sum_{d}^{n}\tau(d)\sum^{n}_{i}\sum^{m}_{j}\tau(i)\tau(j)[\gcd(i,j)=d]\quad\texttt{随手枚举gcd}$$

$$=\sum_{d}^{n}\tau(d)\sum^{\lfloor\frac{n}{\red{d}}\rfloor}_{i}\sum^{\lfloor\frac{m}{\red{d}}\rfloor}_{j}\tau(i\red{d})\tau(j\red{d})[\gcd(i,j)=\red{1}]\quad\texttt{随手除d}$$

$$=\sum_{d}^{n}\tau(d)\sum^{\lfloor\frac{n}{\red{d}}\rfloor}_{i}\sum^{\lfloor\frac{m}{\red{d}}\rfloor}_{j}\tau(i\red{d})\tau(j\red{d})\green{\sum_{k|\gcd(i,j)}\mu(k)}\quad\texttt{随手套} \mu \texttt{性质}$$

$$=\sum_{d}^{n}\tau(d)\green{\sum_{k}^{n}\mu(k)}\sum^{\lfloor\frac{n}{\red{d}\blue{k}}\rfloor}_{i}\sum^{\lfloor\frac{m}{\red{d}\blue{k}}\rfloor}_{j}\tau(i\red{d}\blue{k})\tau(j\red{d}\blue{k})\quad\texttt{随手将}\mu\texttt{提前，拉出k}$$

$$=\purple{\sum_{\purple{T}}^{n}}\boxed{\sum_{d|\purple{T}}\tau(d)\mu(\frac{\purple{T}}{d})}\sum^{\lfloor\frac{n}{\purple{T}}\rfloor}_{i}\tau(i\purple{T})\sum^{\lfloor\frac{m}{\purple{T}}\rfloor}_{j}\tau(j\purple{T})\quad\texttt{随手用T代dk，枚举T}$$

$$=\purple{\sum_{\purple{T}}^{n}}\sum^{\lfloor\frac{n}{\purple{T}}\rfloor}_{i}\tau(i\purple{T})\sum^{\lfloor\frac{m}{\purple{T}}\rfloor}_{j}\tau(j\purple{T})\quad\texttt{随手套用}\tau*\mu=1 $$

$$=\purple{\sum_{\purple{T}}^{n}}\orange{\sum_{T|i}^{n}\tau(i)}\orange{\sum_{T|j}^{m}\tau(j)}\quad\texttt{随手换个写法}$$

这样我们就有了一个看上去最终能用的式子。

此时复杂度不严格地说应该是一只 $\log$ ，众所不知，他跑不过去。~~如果你很松那另当别论~~。

我们着手狄利克雷后缀和优化后两个 $\sum$ 。

### 三、狄利克雷后缀和？

对于形如 ：

$$\sum_{T|i}f(i)$$

的式子，我们可以用狄利克雷后缀和优化到 $\mathcal{O}(n\log\log m)$

具体实现如下：

```cpp
/*len——质数表长度；v[]——质数表；A[]——后缀和函数*/
for (int i = 0; i < len; i++)
{
	for (int j = N / v[i]; j; j--)//可以理解成考虑每个质因数对后缀和的影响
	{
		A[j] = (A[j] + A[j * v[i]]) % MOD;
	}
}
```

我们可以用这个来优化后两个 $\sum$ 。

最后获得了约为 $\mathcal{O}(n\log\log m)$ 的优秀复杂度。

------

码字不易，笔者叹气。

---

## 作者：Leasier (赞：6)

### Subtask $1$
直接暴力计算即可。时间复杂度为 $O(nm(\sqrt{n} + \sqrt{m}))$。

代码：
```cpp
#include <stdio.h>
#include <math.h>

inline int tau(int n){
	int t = sqrt(n), ans = 0;
	for (register int i = 1; i <= t; i++){
		if (n % i == 0){
			ans++;
			if (i * i != n) ans++;
		}
	}
	return ans;
}

int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

int main(){
	int n, m, p, ans = 0;
	scanf("%d %d %d", &n, &m, &p);
	for (register int i = 1; i <= n; i++){
		for (register int j = 1; j <= m; j++){
			ans = (ans + tau(i) * tau(j) % p * tau(gcd(i, j)) % p) % p;
		}
	}
	printf("%d", ans);
	return 0;
}
```
### Subtask $2$
前置芝士：[莫比乌斯反演](https://oi-wiki.org/math/mobius/)

我们先来化简原式。

原式 $= \displaystyle\sum_{d = 1}^{\min(n, m)} \tau(d) \sum_{i = 1}^n \sum_{j = 1}^m [\gcd(i, j) = d] \tau(i) \tau(j)$

$ = \displaystyle\sum_{d = 1}^{\min(n, m)} \tau(d) \sum_{i = 1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j = 1}^{\lfloor \frac{m}{d} \rfloor} [\gcd(i, j) = 1] \tau(id) \tau(jd)$

$ = \displaystyle\sum_{d = 1}^{\min(n, m)} \tau(d) \sum_{i = 1}^{\lfloor \frac{n}{d} \rfloor} \sum_{j = 1}^{\lfloor \frac{m}{d} \rfloor} \tau(id) \tau(jd) \sum_{q\ | \gcd(i, j)} \mu(q)$

$ = \displaystyle\sum_{d = 1}^{\min(n, m)} \tau(d) \sum_{q = 1}^{\lfloor \frac{\min(n, m)}{d} \rfloor} \mu(q) \sum_{i = 1}^{\lfloor \frac{n}{dq} \rfloor} \sum_{j = 1}^{\lfloor \frac{m}{dq} \rfloor} \tau(idq) \tau(jdq)$

$ = \displaystyle\sum_{d = 1}^{\min(n, m)} \tau(d) \sum_{q = 1}^{\lfloor \frac{\min(n, m)}{d} \rfloor} \mu(q) \sum_{i = 1}^{\lfloor \frac{n}{dq} \rfloor} \tau(idq) \sum_{j = 1}^{\lfloor \frac{m}{dq} \rfloor} \tau(jdq)$

$ = \displaystyle\sum_{d = 1}^{\min(n, m)} \tau(d) \sum_{q = 1}^{\lfloor \frac{\min(n, m)}{d} \rfloor} \mu(q) \sum_{dq\ |\ i}^n \tau(i) \sum_{dq\ |\ j}^m \tau(j)$

预处理 $\mu$ 和 $\tau$ 函数的值，然后直接计算即可。时间复杂度暂时无法确定，希望有读者能给出合理的时间复杂度并在评论中回复我。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 2e6 + 7;
int prime[N], mu[N], tau[N];
bool p[N];

inline void init(int n){
	int cnt = 0;
	p[0] = p[1] = true;
	mu[1] = 1;
	tau[1] = 1;
	for (register int i = 2; i <= n; i++){
		if (!p[i]){
			prime[++cnt] = i;
			mu[i] = -1;
			tau[i] = 2;
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= n; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				mu[t] = 0;
				tau[t] = tau[i] * 2 - tau[i / prime[j]];
				break;
			}
			mu[t] = -mu[i];
			tau[t] = tau[i] * 2;
		}
	}
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int f(int n, int k, int mod){
	int ans = 0;
	for (register int i = k; i <= n; i += k){
		ans = (ans + tau[i]) % mod;
	}
	return ans;
}

inline ll g(int n, int m, int k, int mod){
	int nc = n / k, mc = m / k, nmc = min(nc, mc);
	ll ans = 0;
	for (register int i = 1; i <= nmc; i++){
		int t = i * k;
		ans = ((ans + (ll)mu[i] * f(n, t, mod) % mod * f(m, t, mod) % mod) % mod + mod) % mod;
	}
	return ans;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n, m, p, nm;
	ll ans = 0;
	scanf("%d %d %d", &n, &m, &p);
	nm = min(n, m);
	init(max(n, m));
	for (register int i = 1; i <= nm; i++){
		ans = (ans + tau[i] * g(n, m, i, p) % p) % p;
	}
	printf("%lld", ans);
	return 0;
}
```
### Subtask $3$ & $4$
我们继续在 Subtask $2$ 的基础上化简原式。

原式 $= \displaystyle\sum_{T = 1}^{\min(n, m)} (\sum_{q\ |\ T} \mu(q) \tau(\frac{T}{q})) \sum_{T\ |\ i}^n \tau(i) \sum_{T\ |\ j}^m \tau(j)$

由于 $\tau = 1 \times  1$，所以 $\mu \times  \tau = \mu \times  1 \times  1 = \varepsilon \times  1 = 1$，所以 $\displaystyle\sum_{q\ |\ T} \mu(q) \tau\left(\frac{T}{q}\right)$ 的值恒为 $1$。

∴ 原式 $= \displaystyle\sum_{T = 1}^{\min(n, m)} \sum_{T\ |\ i}^n \tau(i) \sum_{T\ |\ j}^m \tau(j)$

预处理 $\tau$ 函数的值，然后直接计算即可。时间复杂度为 $O(\ln \min(n, m)(n + m))$。

代码：
```cpp
#include <stdio.h>

typedef long long ll;

const int N = 2e6 + 7;
int prime[N], tau[N];
bool p[N];

inline void init(int n){
	int cnt = 0;
	p[0] = p[1] = true;
	tau[1] = 1;
	for (register int i = 2; i <= n; i++){
		if (!p[i]){
			prime[++cnt] = i;
			tau[i] = 2;
		}
		for (register int j = 1; j <= cnt && i * prime[j] <= n; j++){
			int t = i * prime[j];
			p[t] = true;
			if (i % prime[j] == 0){
				tau[t] = tau[i] * 2 - tau[i / prime[j]];
				break;
			}
			tau[t] = tau[i] * 2;
		}
	}
}

inline int min(int a, int b){
	return a < b ? a : b;
}

inline int f(int n, int k, int mod){
	int ans = 0;
	for (register int i = k; i <= n; i += k){
		ans = (ans + tau[i]) % mod;
	}
	return ans;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

int main(){
	int n, m, p, nm;
	ll ans = 0;
	scanf("%d %d %d", &n, &m, &p);
	nm = min(n, m);
	init(max(n, m));
	for (register int i = 1; i <= nm; i++){
		ans = (ans + (ll)f(n, i, p) * f(m, i, p) % p) % p;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Warriors_Cat (赞：3)

算是个莫比乌斯反演板子题？

### $Solution:$

以下默认 $n < m$，$d(i)$ 表示 $i$ 的约数个数。

直接一顿操作猛如虎：

$$\begin{aligned}\text{原式}&=\sum_{k=1}^nd(k)\sum_{i=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\sum_{j=1}^{\left\lfloor\frac{m}{k}\right\rfloor}d(ik)d(jk)[\gcd(i, j)=1]\\&=\sum_{k=1}^nd(k)\sum_{p=1}^{\left\lfloor\frac{n}{k}\right\rfloor}\mu(p)\sum_{i=1}^{\left\lfloor\frac{n}{kp}\right\rfloor}\sum_{j=1}^{\left\lfloor\frac{m}{kp}\right\rfloor}d(ikp)d(jkp)\\&=\sum_{T=1}^n\sum_{k\mid p}d(k)\mu(\dfrac{T}{k})(\sum_{i=1}^{\left\lfloor\frac{n}{T}\right\rfloor}d(iT))\cdot(\sum_{j=1}^{\left\lfloor\frac{m}{T}\right\rfloor}d(jT))\end{aligned}$$

然后 $\sum_{k\mid p}d(k)\mu(\dfrac{T}{k})$ 是一个狄利克雷卷积的形式，其实就是 $\mu * d$。

众所周知 $1 * 1 = d$，那么 $1 * 1 * \mu = d * \mu$，即 $\mu * d = 1$。

于是 $\sum_{k\mid p}d(k)\mu(\dfrac{T}{k})=1$。

代入回到原式：

$$\text{原式}=\sum_{T=1}^n(\sum_{i=1}^{\left\lfloor\frac{n}{T}\right\rfloor}d(iT))\cdot(\sum_{j=1}^{\left\lfloor\frac{m}{T}\right\rfloor}d(jT))$$

这个东西直接暴力计算就好了，时间复杂度为 $O(n\log n)$。

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 2000000;
int n, m, mod, pri[N + 10], len, d[N + 10], num[N + 10]; bool vis[N + 10];
inline void sieve(int m){
	d[1] = 1;
	for(int i = 2; i <= m; ++i){
		if(!vis[i]) pri[++len] = i, d[i] = 2, num[i] = 1;
		for(int j = 1; j <= len && i * pri[j] <= m; ++j){
			int k = i * pri[j]; vis[i * pri[j]] = 1;
			if(i % pri[j] == 0){
				num[k] = num[i] + 1;
				d[k] = 1ll * d[i] / num[k] * (num[k] + 1) % mod;
				break;
			}
			num[k] = 1; d[k] = 1ll * d[i] * d[pri[j]] % mod;
		}
	}
}
inline int calc(int n, int m){
	int ans = 0;
	for(int i = m; i <= n; i += m) ans = (ans + d[i]) % mod;
	return ans;
}
inline int sol(int n, int m){
	if(n > m) n ^= m ^= n ^= m; int ans = 0;
	for(int i = 1; i <= n; ++i) ans = (ans + 1ll * calc(n, i) * calc(m, i) % mod) % mod;
	return ans;
}
signed main(){
	n = read(); m = read(); mod = read(); sieve(max(n, m));
	printf("%d", sol(n, m));
	return 0;
}
```


---

## 作者：Aw顿顿 (赞：2)

来一发传统推式子艺能。

首先观察题目式子：

$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\tau(i)\tau(j)\tau(\gcd(i,j))$$

由于 $\tau$ 的意义是约数个数，因此我们考虑将约数个数以把框着 $\gcd$ 部分的 $\tau$ 展开，写作：


$$\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\tau(i)\tau(j)\sum\limits_{k=1}^{\gcd(i,j)}[k|i\text{ and }k|j]$$

考虑将带着 $k$ 的合式放在整个式子前面：


$$\sum\limits_{k=1}^{\gcd(i,j)}\sum\limits_{i=1}^{n}[k|i]\tau(i)\sum\limits_{j=1}^{m}[k|j]\tau(j)$$

和式右侧的两个式子形式是类似的，由此我们考虑将其单独计算：

$$f(k,n)=\sum\limits_{i=1}^{n}[k|i]\tau(i)$$

将其代入到原式之中，得到：

$$\sum\limits_{k}f(k,n)\cdot f(k,m)$$


由于 $f$ 函数预处理的时间复杂度是 $n\log n$，因此可以通过本题，下面给出代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 2000005
using namespace std;
int n,m,p,tau[N],ans;
int f(int k,int n){
	int res=0;
	for(int i=k;i<=n;i+=k)
		res=(res+tau[i])%p;
	return res;
}signed main(){
	scanf("%lld%lld%lld",&n,&m,&p);
	if(n>m)swap(n,m);
	for(int i=1;i<=m;i++)for(int j=i;j<=m;j+=i)tau[j]++;
	for(int i=1;i<=n;i++){
		int t=f(i,n)*f(i,m)%p;
		ans=(ans+t)%p;
	}printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：弦巻こころ (赞：2)

~~时隔一个月终于发现了我们考试题竟然是洛谷原题.~~ 感谢@happydef

分享一个很妙的推导方法,不需要莫反.~~甚至刚上幼儿园都能看懂~~

考虑$τ(i)$,$τ(j)$被计算的次数为$τ(gcd(i,j))$ 。

意思就是说，只要枚举$gcd(i,j)$ 的一个因子即可使得每个点对的计算次数都是正确的。

答案就是
$$\sum_{d=1}^n(\sum_{i=1}^{\lfloor{\frac{n}{d}}\rfloor }\sum_{j=1}^{\lfloor{\frac{m}{d}}\rfloor }τ(id)τ(jd))$$

考虑证明正确性,由于我们是枚举每个约数然后去更新约数的倍数,也就是当$d|i$且$d|j$时也就是$d|gcd(i,j)$时,$τ(i)$,$τ(j)$这个点对会被计算一次,对于所有的$d|gcd(i,j)$都计算一次贡献都相当于计算了$τ(gcd(i,j))$次,也就是我们要求的式子了.

根据调和计数,暴力求答案是$O(nlogn)$的,也可以用迪利克雷前缀和优化到$(nloglogn)$.

---

## 作者：Arghariza (赞：1)

~~为啥毒瘤反演题才蓝啊。~~

题目大意：

求 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\tau(i)\tau(j)\tau(\gcd(i,j))$。

根据套路把 $\gcd$ 提出来枚举：

$$\begin{aligned}ans&=\sum\limits_{d=1}^{n}\tau(d)\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\tau(i)\tau(j)[\gcd(i,j)=d]\\&=\sum\limits_{d=1}^{n}\tau (d)\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}\tau(id)\tau(jd)[\gcd(i,j)=1]\end{aligned}$$

$$\because [\gcd(i,j)=1]=\sum\limits_{k\mid (i,j)}\mu(k)=\sum\limits_{k\mid i,k\mid j}\mu(k)$$

$$\begin{aligned}\therefore ans&=\sum\limits_{d=1}^{n}\tau(d)\sum\limits_{i=1}^{n/d}\sum\limits_{j=1}^{m/d}\tau(id)\tau(jd)\sum\limits_{k\mid i,k\mid j}\mu(k)\\&=\sum\limits_{d=1}^{n}\tau(d)\sum\limits_{k=1}^{n/d}\mu(k)\sum\limits_{i=1}^{n/dk}\tau(idk)\sum\limits_{j=1}^{m/dk}\tau(jdk)\end{aligned}$$

（上一步是把这个 $k$ 放到前面枚举了。）

然后大力设 $t=dk$，那么 $k=\frac{t}{d}$，我们去枚举这个 $t$。

$$\begin{aligned}\therefore ans&=\sum\limits_{d=1}^{n}\tau(d)\sum\limits_{d\mid t}^{n}\mu(\frac{t}{d})\sum\limits_{i=1}^{n/t}\sum\limits_{j=1}^{m/t}\tau(it)\tau(jt)\\&=\sum\limits_{t=1}^{n}\sum\limits_{d\mid t}^{n}\tau(d)\mu(\frac{t}{d})\sum\limits_{i=1}^{n/t}\sum\limits_{j=1}^{m/t}\tau(it)\tau(jt)\end{aligned}$$

（上一步是把 $t$ 丢到式子的最前面了。）

然后呢？我们发现 $\sum\limits_{d\mid t}^{n}\tau(d)\mu(\frac{t}{d})$ 是一个**狄利克雷卷积**的形式，并且 $\tau * \mu=I$ ，也就是这个式子恒等于 $1$。

为啥？

因为由 $\tau$ 的定义可得 $\tau=I*I$ ，由于 $\mu=I^{-1}$ ，所以把右式的 $I$ 搞一个过去，就变成了 $\tau*\mu=I$。

$$\therefore ans=\sum\limits_{t=1}^{n}\sum\limits_{i=1}^{n/t}\sum\limits_{j=1}^{m/t}\tau(it)\tau(jt)$$

这个 $\tau$ 可以用线性筛在 $O(n)$ 的复杂度内预处理出来，然后记录 $\tau(it)$ 和 $\tau(jt)$ 分别对每一个 $t$ 的贡献，最后枚举这个 $t$ 的时候乘起来就行了。

跑起来慢的要死，可能要多提交几遍。听说可以优化，但我不会 $\mathtt{dirichlet}$ 后缀和啊。![](https://啧.tk/doge)

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 2e6 + 200;
int n, m, p, ans, s1[maxn], s2[maxn];
int f[maxn], d[maxn], vis[maxn], pr[maxn], tot;

void init() {
	d[1] = f[1] = vis[1] = 1;
	for (int i = 2; i <= maxn - 1; i++) {
		if (!vis[i]) {
			pr[++tot] = i;
			f[i] = 1;
			d[i] = 2;
		}
		for (int j = 1; j <= tot && i <= maxn / pr[j]; j++) {
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) {
				f[i * pr[j]] = f[i] + 1;
				d[i * pr[j]] = d[i] * (f[i * pr[j]] + 1) / (f[i] + 1);
				break;
			}
			f[i * pr[j]] = 1;
			d[i * pr[j]] = d[i] * d[pr[j]];
		}
	}
}

signed main() {
    init();
    n = read();
    m = read();
    p = read();
    if (n > m) swap(n, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n / i; j++) {
            s1[i] = (s1[i] + d[i * j]) % p;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m / i; j++) {
            s2[i] = (s2[i] + d[i * j]) % p;
        }
    }
    for (int i = 1; i <= n; i++) {
        ans = (ans + s1[i] * s2[i] % p) % p;
    }
    write(ans);
    return 0;
}
```



---

## 作者：Na2PtCl6 (赞：0)

本文重点介绍如何用欧拉筛筛约数和以及约数个数

## 分析题目
题目中的式子要用到约数个数，所以我们要筛约数个数。

欧拉筛套路，设 $f(x)$ 为数 $x$ 的约数个数，数分三类：

1. 素数，约数个数为 $2$
2. 一个数（设为 $i$）乘上不被它整除的素数（设为 $p$），$f(i \times p)=f(i) \times 2 $。原因是没有重复的因数时 $p$ 与 $i$ 的每个因数相乘都能得到新的因数。
3. 一个数（设为 $i$）乘上被它整除的素数（设为 $p$），$f(i \times p)=f(i) \times 2 - f(i/p)$。原因是在 2. 的基础上，$i/p$ 的所有因数乘上 $p$ 组成的因数都重复算了两遍。

本题中，接下来一番操作就可以得出结果了,但我们不能局限于此，下面介绍筛约数和。

类似约数个数，设 $g(x)$ 为数 $x$ 的约数和，则：

1. 素数（设为 $j$），约数和为 $1+j$
2. 一个数（设为 $i$）乘上不被它整除的素数（设为 $p$），$g(i \times p)=g(i) + g(i) \times p$。原因同之前的2.
3. 一个数（设为 $i$）乘上不被它整除的素数（设为 $p$），$g(i \times p)=g(i) + (g(i)-g(i/p)) \times p $ 原因同之前的3.

## 代码实现
筛约数个数
```cpp
void get_fs(){
	fs[1]=1;
	for(int i=2;i<maxa;i++){
		if(!vis[i]){
			fs[i]=2;
			pr[++cnt]=i;
		}
		for(int j=1;j<=cnt&&pr[j]*i<maxa;j++){
			vis[i*pr[j]]=1;
			if(i%pr[j]==0){
				fs[i*pr[j]]=(fs[i]<<1)-fs[i/pr[j]];
				break;
			}
			fs[i*pr[j]]=fs[i]<<1;
		}
	}
} 
```
筛约数和
```cpp
void get_fc(){
	res[1]=fc[1]=1;
	for(int i=2;i<maxn;i++)
		res[i]=-1;
	for(int i=2;i<maxn;i++){
		if(!vis[i]){
			pr[++cnt]=i;
			fc[i]=i+1;
		}
		for(int j=1;j<=cnt&&i*pr[j]<maxn;j++){
			vis[i*pr[j]]=1;
			if(i%pr[j]==0){
				fc[i*pr[j]]=fc[i]+fc[i]*pr[j]-pr[j]*fc[i/pr[j]];
				break;
			}
			fc[i*pr[j]]=fc[i]+fc[i]*pr[j];
		}
	}
}
```

---

