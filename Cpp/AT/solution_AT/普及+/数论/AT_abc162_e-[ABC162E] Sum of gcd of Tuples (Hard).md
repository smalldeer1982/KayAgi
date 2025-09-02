# [ABC162E] Sum of gcd of Tuples (Hard)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc162/tasks/abc162_e

$ 1 $ 以上 $ K $ 以下の整数からなる長さ $ N $ の数列 $ \{A_1,...,A_N\} $ を考えます。

そのようなものは $ K^N $ 個ありますが、その全てについての $ \gcd(A_1,...,A_N) $ の和を求めてください。

ただし、答えは非常に大きくなる可能性があるため、和を $ (10^9+7) $ で割ったあまりを出力してください。

なお、$ \gcd(A_1,...,A_N) $ は $ A_1,...,A_N $ の最大公約数を表します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 10^5 $
- 入力は全て整数

### Sample Explanation 1

$ \gcd(1,1,1)+\gcd(1,1,2)+\gcd(1,2,1)+\gcd(1,2,2) $ $ +\gcd(2,1,1)+\gcd(2,1,2)+\gcd(2,2,1)+\gcd(2,2,2) $ $ =1+1+1+1+1+1+1+2=9 $ となるため、答えは $ 9 $ です。

### Sample Explanation 3

和を $ 10^9+7 $ で割った余りを出力してください。

## 样例 #1

### 输入

```
3 2```

### 输出

```
9```

## 样例 #2

### 输入

```
3 200```

### 输出

```
10813692```

## 样例 #3

### 输入

```
100000 100000```

### 输出

```
742202979```

# 题解

## 作者：Hisaishi_Kanade (赞：16)

**upd on 2022-7-13： 修改若干不合适叙述。**

### 一、题意

很明了，给出 $n,k$，求下面这个复杂式子的值：

$$
\sum_{a_1=1}^k\sum_{a_1=1}^k\cdots\sum_{a_{n-1}=1}^k\sum_{a_n=1}^k\gcd\left\{a_i\right\}
$$

### 二、思路

一眼莫反，但是个人觉得有点小题大做。

首先我们要认识到，$\gcd\left\{a_i\right\}\leq k$，结合 $k\le10^5$，所以可以令 $f_j$ 表示 $\gcd\left\{a_i\right\}=j$ 的次数，就很好做很好想了。

如果要让 $\gcd\left\{a_i\right\}=mj$，则 $\forall a_i=nk$ （此处 $n,m$ 为正整数），易得 $\forall a_i$ 有 $\lfloor\dfrac k j\rfloor$ 种取值，共 $\lfloor \dfrac k i\rfloor^n$ 种可能。

注意是 $mj$ 而不是 $j$，此时 $f_j$ 不是我们想要的答案，有重复，所以要去重：

```cpp
for(y=x<<1;y<=k;y+=x)
	f[x]=(f[x]-f[y]+mod)%mod;
```

为了去重和转移的方便，倒序枚举 $i$，复杂度 $O\left(k\log k\log n\right)$，比莫反慢得多，但是可以忍受。

### 三、代码
```cpp
#include <stdio.h>
const int mod=1000000007;//对1e9+7取模
long long n,k,i,x,y,ans;
long long f[100005];
long long repow(long long a,long long b){//快速幂
	long long ans=1,base=a;
	while(b){
		if(b&1)
			ans=((ans%mod)*(base%mod))%mod;
		base=((base%mod)*(base%mod))%mod;
		b>>=1;
	}
	return ans;
}
int main(){
	scanf("%lld %lld",&n,&k);
	for(x=k;x;--x){//倒序枚举
		f[x]=repow(k/x,n);
		for(y=x<<1;y<=k;y+=x)
			f[x]=(f[x]-f[y]+mod)%mod;//去重
		ans=(ans+x*f[x]%mod)%mod;//计算答案
	}
	printf("%lld",ans);//输出
	return 0;
}
```

---

## 作者：Aleph1022 (赞：11)

不妨直接上手推式子。

$$
\begin{aligned}
\sum\limits_{1\le A_1,\dots,A_N\le K} \gcd(A_1,\dots,A_N)
&= \sum\limits_{1\le A_1,\dots,A_N\le K} \sum\limits_{d|\gcd(A_1,\dots,A_N)} \varphi(d) \\
&= \sum\limits_{d=1}^K \varphi(d) \left\lfloor\frac Kd\right\rfloor^N
\end{aligned}
$$

线性筛之后直接计算即可。

加强版：<https://loj.ac/p/6491>。

---

## 作者：m256i (赞：8)

# 推导
考虑无脑欧拉反演。

$$
\begin{aligned}
&\sum_{a_1=1}^n\sum_{a_2=1}^n\cdots\sum_{a_k=1}^n\gcd(a_1,a_2,\cdots,a_k)\\
=&\sum_{a_1=1}^n\sum_{a_2=1}^n\cdots\sum_{a_k=1}^n\sum_{d \mid \gcd(a_1,a_2,\cdots,a_k)}\varphi(d)\\
=&\sum_{a_1=1}^n\sum_{a_2=1}^n\cdots\sum_{a_k=1}^n\sum_{d=1}^n[d \mid \gcd(a_1,a_2,\cdots,a_k)]\varphi(d)\\
=&\sum_{a_1=1}^n\sum_{a_2=1}^n\cdots\sum_{a_k=1}^n\sum_{d=1}^n[d \mid a_1][d \mid a_2]\cdots[d \mid a_k]\varphi(d)\\
=&\sum_{d=1}^n\varphi(d)\sum_{a_1=1}^n[d \mid a_1]\sum_{a_2=1}^n[d \mid a_2]\cdots\sum_{a_k=1}^n[d \mid a_k]\\
=&\sum_{d=1}^n\varphi(d)\left(\sum_{a_1=1}^n[d \mid a_1]\right)\left(\sum_{a_2=1}^n[d \mid a_2]\right)\cdots\left(\sum_{a_k=1}^n[d \mid a_k]\right)\\
=&\sum_{d=1}^n\varphi(d)\left\lfloor\dfrac{n}{d}\right\rfloor^k
\end{aligned}
$$

**注意，$\bm n$ 和 $\bm k$ 与原题相反。**

杜教筛套分块，时间复杂度 $\Theta\left(n^{\frac{2}{3}}+\sqrt n\log n\right)$。

这种方法可以解决 $n \le 10^{10}$ 级别的情况。

升级版在[此](//loj.ac/p/6491)，3s 时间能过。

# 杜教筛
杜教筛用于求满足 $f*g=h$ 的数论函数 $f$，其中 $*$ 是狄利克雷卷积，$g$ 与 $h$ 是另外两个方便计算的数论函数。

我们定义 $S(n)=\displaystyle\sum_{i=1}^nf(i)$。

杜教筛基于这个基本式子：

$$\sum_{i=1}^nh(i)=\sum_{i=1}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)$$

证明：

$$
\begin{aligned}
\sum_{i=1}^nh(i)&=\sum_{i=1}^n(f*g)(i)\\
&=\sum_{i=1}^n(g*f)(i)\\
&=\sum_{i=1}^n\sum_{d \mid i}g(d)f\left(\dfrac{i}{d}\right)\\
&=\sum_{d=1}^n\sum_{i=1}^n[d \mid i]g(d)f\left(\dfrac{i}{d}\right)\\
&=\sum_{d=1}^n\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}g(d)f(i)\\
&=\sum_{d=1}^ng(d)\sum_{i=1}^{\left\lfloor\frac{n}{d}\right\rfloor}f(i)\\
&=\sum_{d=1}^ng(d)S\left(\left\lfloor\dfrac{n}{d}\right\rfloor\right)\\
&=\sum_{i=1}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)
\end{aligned}
$$

那么我们在这个等式两边同时减去 $\displaystyle\sum_{i=2}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)$，则有：

$$
\begin{aligned}
\left(\sum_{i=1}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)\right)-\sum_{i=2}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)&=\left(\sum_{i=1}^nh(i)\right)-\sum_{i=2}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)\\
g(1)S(n)&=\left(\sum_{i=1}^nh(i)\right)-\sum_{i=2}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)\\
S(n)&=\dfrac{1}{g(1)}\left(\left(\sum_{i=1}^nh(i)\right)-\sum_{i=2}^ng(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)\right)
\end{aligned}
$$

这个式子可以直接数论分块，递归解决即可，边界条件为 $n=1$，此时结果为 $f(1)$。我们需要在计算过程中将 $S(n)$ 存储下来。

在本题中，由于 $\varphi*\mathbf{1}=\operatorname{id}$，我们可以令 $f=\varphi,g=\mathbf{1},h=\operatorname{id}$，那么：

$$
\begin{aligned}
S(n)&=\dfrac{1}{\mathbf{1}(1)}\left(\left(\sum_{i=1}^n\operatorname{id}(i)\right)-\sum_{i=2}^n\mathbf{1}(i)S\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)\right)\\
&=\dfrac{1}{1}\left(\left(\sum_{i=1}^ni\right)-\sum_{i=2}^nS\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)\right)\\
&=\dfrac{n(n+1)}{2}-\sum_{i=2}^nS\left(\left\lfloor\dfrac{n}{i}\right\rfloor\right)
\end{aligned}
$$

# 时间复杂度
由于记忆化的存在，杜教筛的时间复杂度不是很方便分析。

我们考虑画出递归树。以 $n=12$ 为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/hhmye9v9.png)

加上记忆化后，一些递归树被砍掉了：

![](https://cdn.luogu.com.cn/upload/image_hosting/r23mjenr.png)

我们尝试从右往左计算，而不是从左往右：

![](https://cdn.luogu.com.cn/upload/image_hosting/ux0meae6.png)

可以看到，这时的递归树只剩一层了！事实上，由于 $\left\lfloor\dfrac{\left\lfloor\frac{a}{b}\right\rfloor}{c}\right\rfloor=\left\lfloor\dfrac{a}{bc}\right\rfloor$，那么在深层计算的一定在浅层出现。

并且我们发现，改变计算顺序后复杂度不变（因为每个 $n$ 始终会递归恰好一次）。

所以复杂度为：

$$
\sum_{i \in S}\sqrt i
$$

其中 $S$ 是由所有不同的 $\left\lfloor\dfrac{n}{i}\right\rfloor$ 构成的集合。

用和数论分块一样的方法，它渐进等于：

$$
\sum_{i=1}^{\sqrt n}\sqrt i+\sqrt{\dfrac{n}{i}}
$$

显然 $\displaystyle\sum_{i=1}^{\sqrt n}\sqrt i$ 在这里是可以忽略的（因为它不会大于右边）。我们只需要计算：

$$
\sum_{i=1}^{\sqrt n}\sqrt{\dfrac{n}{i}}
$$

根据[这篇文章](//www.luogu.com.cn/blog/_post/450521)中的技巧，我们将和式转换成定积分，在渐进意义上相等。因此计算：

$$
\begin{aligned}
T(n)&\asymp\sum_{i=1}^{\sqrt n}\sqrt{\dfrac{n}{i}}\\
&\sim\int_1^{\sqrt n}\sqrt{\dfrac{n}{x}}\mathrm dx\\
&\sim\int_0^{\sqrt n}\sqrt{\dfrac{n}{x}}\mathrm dx\\
&=\int_0^{\sqrt n}\dfrac{\sqrt n}{\sqrt x}\mathrm dx\\
&=\sqrt n\int_0^{\sqrt n}x^{-0.5}\mathrm dx\\
&=\sqrt n\dfrac{(\sqrt n)^{0.5}}{0.5}\\
&=2n^{0.75}
\end{aligned}
$$

因此不加优化的杜教筛复杂度为 $\Theta\left(n^{\frac{3}{4}}\right)$。

# 优化 1：预处理
我们考虑线性筛预处理 $S(1),S(2),\cdots,S(c)\;[c \ge \sqrt n]$，复杂度为：

$$
\begin{aligned}
T(n)&\asymp\Theta(c)+\sum_{i=1}^{\sqrt n}\left[\dfrac{n}{i} \ge c\right]\sqrt{\dfrac{n}{i}}\\
&\asymp c+\sum_{i=1}^{\sqrt n}\left[i \le \dfrac{n}{c}\right]\sqrt{\dfrac{n}{i}}\\
&=c+\sum_{i=1}^{\frac{n}{c}}\sqrt{\dfrac{n}{i}}\\
&\sim c+\int_1^{\frac{n}{c}}\sqrt{\dfrac{n}{x}}\mathrm dx\\
&\sim c+\int_0^{\frac{n}{c}}\sqrt{\dfrac{n}{x}}\mathrm dx\\
&=c+\sqrt n\int_0^{\frac{n}{c}}x^{-0.5}\mathrm dx\\
&=c+\sqrt n\dfrac{\left(\frac{n}{c}\right)^{0.5}}{0.5}\\
&=c+\dfrac{2n}{\sqrt c}\\
&\asymp c+\dfrac{n}{\sqrt c}
\end{aligned}
$$

显然，当加号两边相等时结果最小。

$$
\begin{aligned}
c&=nc^{-\frac{1}{2}}\\
c^{\frac{3}{2}}&=n\\
c&=n^{\frac{2}{3}}
\end{aligned}
$$

因此，当我们预处理 $n^{\frac{2}{3}}$ 以内的结果时复杂度最小，为 $\Theta\left(n^{\frac{2}{3}}\right)$。

# 优化 2：记忆化
我们的记忆化需要用到 `map` 或哈希，而这会增大常数（如果用 `map` 还会使复杂度增加一个 $\log$），这是我们不希望看到的。于是我们有了一种更简便的方法：加入一个数组 $h$，记录 $h_x=S\left(\left\lfloor\dfrac{n}{x}\right\rfloor\right)$，由于当 $x \le n^{\frac{2}{3}}$ 时会直接访问线性筛，$h$ 数组的大小开到 $n^{\frac{1}{3}}$ 即可。

这个 $x$ 如何确定？可以证明，如果 $a=\left\lfloor\dfrac{n}{b}\right\rfloor$，那么 $\left\lfloor\dfrac{n}{a}\right\rfloor$ 一定可以作为 $x$。

请注意，这种方法对多组重复数据不友好（因为每次 $h$ 数组都要清空）。

# 代码
```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <bitset>
#include <algorithm>
typedef long long ll;
typedef unsigned long long ull;

template <typename T>
inline T max(T a, T b){return (a>b) ? a : b;}
template <typename T>
inline T min(T a, T b){return (a<b) ? a : b;}

template <typename T>
void read(T &x){
    static char ch;
    x = 0;
    while (!isdigit(ch=getchar()));
    do x = (x<<3)+(x<<1)+(ch^'0');
    while (isdigit(ch=getchar()));
}

template <typename T>
void write(T x, char c = ' '){
    static char st[100], *p;
    if (x < 0) putchar('-'), x = -x;
    if (x == 0) putchar('0');
    for (p = st; x; x /= 10) *++p = x%10;
    for (; p != st; --p) putchar(*p|'0');
    putchar(c);
}

template <typename T>
inline void writeln(T x){write(x, '\n');}

constexpr int MAXN = 1000006; // n^2/3
constexpr ll P = 1e9+7;
bool isp[MAXN];
int primes[MAXN];
ll phi[MAXN];
ll h[1003]; // n^1/3

template <typename T>
inline T mod(T n){
    T ans = n%P;
    return (ans<0)?ans+P:ans;
}

template <typename T>
inline T pow(T x, T y){
    if (x >= P) x %= P;
    if (y >= P-1) y %= P-1;
    T ans = 1;
    while (y){
        if (y&1) ans = (ans*x)%P;
        x = (x*x)%P;
        y >>= 1;
    }
    return ans;
}

void init(){
    memset(isp, 1, sizeof isp);
    int cnt = 0;
    phi[1] = 1;
    for (int i = 2; i < MAXN; ++i){
        if (isp[i]) primes[cnt++] = i, phi[i] = i-1;
        for (int j = 0; j < cnt && i*primes[j] < MAXN; ++j){
            isp[i*primes[j]] = 0;
            if (!(i%primes[j])){
                phi[i*primes[j]] = phi[i]*primes[j]; break;
            }
            phi[i*primes[j]] = phi[i]*phi[primes[j]];
        }
    }
    for (int i = 2; i < MAXN; ++i) phi[i] = (phi[i]+phi[i-1])%P;
}

ll N;

ll sum_phi(ll n){
    if (n < MAXN) return phi[n];
    int x = N/n;
    if (h[x]) return h[x];
    ll ans = (n*(n+1)>>1)%P;
    for (ll l = 2, r; l <= n; l = r+1){
        r = n/(n/l);
        ans = mod(ans-(r-l+1)*sum_phi(n/l));
    }
    return h[x]=ans;
}

ll solve(ll n, ll k){
    ll ans = 0;
    for (ll l = 1, r; l <= n; l = r+1){
        r = n/(n/l);
        ans = mod(ans+(sum_phi(r)-sum_phi(l-1))*pow(n/l, k));
    }
    return ans;
}

int main(){
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    init(); ll k;
    read(k); read(N); sum_phi(N);
    writeln(solve(N, k));
    
    
    return 0;
}
```

---

## 作者：_jimmywang_ (赞：4)

### 题意：

给定 $n,k$，求

$$\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}\dots\sum^k_{a_n=1}gcd(a_1,a_2,a_3,\dots,a_n)\ mod\ 1000000007$$ 

### 方法：

传统异能，推 式 子。

以 $n=3$ 为例（以下除法均约定为向下取整）。

$$ans=\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}gcd(a_1,a_2,a_3)$$
$$=\sum^k_{i=1}i*\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}[gcd(a_1,a_2,a_3)=i]$$
传统莫反：
$$=\sum^k_{i=1}i*\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}\sum_{d|gcd(a_1,a_2,a_3)}\mu(d)$$
转化：
$$=\sum^{k}_{i=1}i*\sum^{\frac{k}{i}}_{d=1}(\frac{k}{id})^3*\mu(d)$$

所以答案就可以表示为：

$$\sum^{k}_{i=1}i*\sum^{\frac{k}{i}}_{d=1}(\frac{k}{id})^n*\mu(d)$$

然后线性筛一下 $\mu$ 函数，然后暴力处理就行了。

$code:$

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(int i=a;i<=b;i++)
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
#define d rd()
const ll maxn=100010;
bool vis[maxn];
ll cnt,prim[maxn];
ll mu[maxn];
void gt(){
    mu[1]=1;
    f(i,2,maxn){
        if(!vis[i]) prim[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&prim[j]*i<=maxn;++j){
            vis[prim[j]*i]=1;
            if(i%prim[j]==0)break;
            mu[i*prim[j]]=-mu[i];
        }
    }
}
ll n,k,ans;
ll qp(ll a,ll b,ll p){
	ll ans=1;
	while(b){
		if(b&1)ans=(ans*a)%p;
		a=(a*a)%p;
		b>>=1;
	}
	return ans;
}
int main(){
	gt();
	n=d,k=d;
	f(i,1,k){
		ll cmp=0;
		f(j,1,k/i)cmp+=mu[j]*qp(k/i/j,n,1000000007),cmp%=1000000007;
		ans+=i*cmp,ans%=1000000007;
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：SpeedStar (赞：4)

### 算法分析
如果我们计算每个$gcd(A_1, A_2, \cdots, A_n)$，那么我们将无法在时限内完成任务。然后，对于每个$1\leqslant x \leqslant K$，我们不妨考虑“存在多少个序列$\{A_i\}$使得$gcd(A_1, A_2, \cdots, A_n)$？”。如果这个问题解决了，那么原来的问题自然也就迎刃而解了。

注意到，最大公因数为$x$的倍数的充要条件是$A_1, A_2, \cdots, A_n$都是$x$的倍数。所以这样的序列数为${\left\lfloor {\frac{K}{x}} \right\rfloor ^N}$个。

此外序列的最大公因数严格为$x$的充要条件是最大公因数只能为$x$的$1$倍，而不能为$x$的$k$倍($k$为大于$1$的正整数)。所以如果按$x$的降序计算，则可以通过减去$2x$，$3x$，...的数量来求得已转化问题的答案。（实际上就是容斥原理）


### C++代码
```cpp
#include <iostream>

using namespace std;
using ll = long long;

const int K = 1e5 + 10;
const int mod = 1e9 + 7;

ll dp[K];

ll qmi(int m, int k, int p) {
    ll res = 1 % p, t = m;
    while (k) {
        if (k & 1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i = k; i >= 1; --i) {
        dp[i] = qmi(k / i, n, mod);
        for (int j = 2 * i; j <= k; j += i) {
            dp[i] -= dp[j];
            dp[i] = (dp[i] % mod + mod) % mod;
        }
    }

    ll res = 0;
    for (int i = 1; i <= k; i++) (res += dp[i] * i % mod) %= mod;
    cout << res << '\n';

    return 0;
}

```

---

## 作者：w33z8kqrqk8zzzx33 (赞：3)

首先，发现直接统计答案是很难的，但是所有 gcd 都在 $1$ 到 $n$ 的范围内，所以可以统计有多少个序列 gcd 是某一个在 $1$ 到 $n$ 之间的数。

第二，一个含有 $1$ 到 $n$ 的长度为 $k$ 的序列并且 gcd 等于 $v$ 的数量 **等于**  一个含有 $1$ 到 $\lfloor\frac{n}{v}\rfloor$ 的长度为 $k$ 的序列并且 gcd 等于 $1$ 的数量（应为在 gcd 等于 $1$ 的序列里，每个数乘以 $v$ 就得到一个 gcd 等于 $v$ 的序列了）

这里就直接套莫比乌斯反演了：

$$f(n,k)=\underbrace{\sum_{a_1=1}^n\sum_{a_2=1}^n\dots\sum_{a_k=1}^n}_\text{k summations}[\gcd(a)=1]$$

$$f(n,k)=\underbrace{\sum_{a_1=1}^n\sum_{a_2=1}^n\dots\sum_{a_k=1}^n}_\text{k summations}\sum_{d|gcd(a)}\mu(d)$$

$$f(n,k)=\underbrace{\sum_{a_1=1}^n\sum_{a_2=1}^n\dots\sum_{a_k=1}^n}_\text{k summations}\sum_{d=1}^n\mu(d)\prod_{i=1}^k[d|a_i]$$

$$f(n,k)=\sum_{d=1}^n\mu(d)\prod_{i=1}^k\sum_{a_i=1}^n[d|a_i]$$

$$f(n,k)=\sum_{d=1}^n\mu(d)\prod_{i=1}^k\lfloor\frac{n}{d}\rfloor$$

$$f(n,k)=\sum_{d=1}^n\mu(d)\lfloor\frac{n}{d}\rfloor^k$$

计算完 $\mu$ 就好了。

主要代码：

```cpp
int findcoprime(int n, int k) {
	int ans = 0;
	rep1(i, n) {
		if(mu[i] == 0) continue;
		ans = (ans + mu[i]*qpow(n/i, k));
		if(ans < 0) ans += MOD;
		if(ans >= MOD) ans -= MOD;
	}
	return ans;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; gi(k), gi(n);
	sieve(200000);
	fm();
	int ans = 0;
	rep1(i, n) {
		ans = (ans + 1ll * i * findcoprime(n/i, k))%MOD;
	}
	print(ans);
}
```

注意到应为这个题目没有多组询问，不用数论分块，但是然而可以用数论分块达到快 3 倍：

```cpp
int findcoprime(int n, int k) {
	int ans = 0, r;
	for(int l=1; l<=n; l=r) {
		r = n/(n/l)+1;
		ans = (ans + 1ll*(mu[r-1]-mu[l-1])*qpow(n/l, k)) % MOD;
	}
	return ans;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; gi(k), gi(n);
	sieve(200000);
	fm();
	int ans = 0; ll r;
	for(ll l=1; l<=n; l=r) {
		r = n/(n/l)+1;
		ans = (ans + 1ll * (r*(r-1)/2 - l*(l-1)/2) * findcoprime(n/l, k))%MOD;
	}
	print(ans);
}
```

---

## 作者：清烛 (赞：2)

## Description
给定 $2\le N\le 10^5$，$1\le K\le 10^5$，求

$$
\sum_{a_1 = 1}^K\sum_{a_2 = 1}^K\cdots\sum_{a_N = 1}^K\gcd_{i = 1}^N\{a_i\}\bmod {10^9 + 7}
$$

## Solution 1
第一反应是，由于 $\gcd_{i=1}^N\{a_i\}\in[1, K]$，那么我们就考虑对于 $[1, K]$ 里面的每一个数字，其作为了多少次 $\gcd$。

然后发现， 若 $\gcd_{i = 1}^N\{a_i\} = X$，则 $a_i$ 一定都是 $X$ 的倍数，这样的方案数有 $\lfloor K / X\rfloor^N$ 种，但是要抠掉 $\gcd\{a_i\} = 2X, 3X,\cdots$ 的情况。所以我们倒序枚举统计答案，复杂度 $O(K\log K\log N )$。

## Implementation 1
```cpp
const int maxn = 1e5 + 5;
int n, k;
modint f[maxn];
 
int main() {
    read(n, k);
    modint ans = 0;
    DEC(x, k, 1) {
        f[x] = qPow(k / x, n);
        for (int y = 2 * x; y <= k; y += x) f[x] -= f[y];
        ans += x * f[x];
    }
    print(ans);
    return output(), 0;
}
```

## Solution 2
另外的解法是直接考虑反演：

$$
\begin{aligned}
&\sum_{a_1 = 1}^K\sum_{a_2 = 1}^K\cdots\sum_{a_N = 1}^K\gcd_{i = 1}^N\{a_i\}\\
=&\sum_{a_1 = 1}^K\cdots\sum_{a_N = 1}^K\sum_{d\mid a_1,\cdots d\mid a_N}\varphi(d)\\
=&\sum_{d = 1}^K\varphi(d)\sum_{a_1 = 1}^K\cdots\sum_{a_N = 1}^K[d\mid \gcd\{a_i\}]\\
=&\sum_{d = 1}^K\varphi(d)\left\lfloor\frac Kd\right\rfloor^N
\end{aligned}
$$

其中，第二行是欧拉反演（$\operatorname{id} = 1 * \varphi$），第三行是枚举 $d$，第四行的意义应该比较好理解。这个东西可以先线性筛 $\varphi$ 然后数论分块，复杂度为 $O(K + \sqrt K\log N)$。

其实这个东西还可以用一些更高妙的方法（杜教筛之类的）快速求，见 [LOJ6491](https://loj.ac/p/6491)。

---

## 作者：ioker (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/AT5310)
## 题目大意：
给定 $n,k$,求：

$$\sum\limits_{a_1=1}^{k}{
\sum\limits_{a_2=1}^{k}{
\sum\limits_{a_3=1}^{k}{
…
\sum\limits_{a_n=1}^{k}{
\gcd(a_1,a_2,a_3,…,a_n)
}
}
}
}$$
的结果对 $10^9+7$ 取模

推式子

$$\sum\limits_{a_1=1}^{k}{
\sum\limits_{a_2=1}^{k}{
\sum\limits_{a_3=1}^{k}{
…
\sum\limits_{a_n=1}^{k}{
\gcd(a_1,a_2,a_3,…,a_n)
}
}
}
}$$

$$=\sum\limits_{a_1=1}^{k}{
\sum\limits_{a_2=1}^{k}{
\sum\limits_{a_3=1}^{k}{
…
\sum\limits_{a_n=1}^{k}{
\sum\limits_{x|a_1}{
\sum\limits_{x|a_2}{
\sum\limits_{x|a_3}{
…
\sum\limits_{x|a_n}{
\varphi(x)
}
}
}
}
}
}
}
}$$

枚举 $x$

$$=
\sum\limits_{x=1}^{k}{
\varphi(x)
\sum\limits_{a_1=1}^{k}{
\sum\limits_{a_2=1}^{k}{
\sum\limits_{a_3=1}^{k}{
…
\sum\limits_{a_n=1}^{k}{
[x|a_1][x|a_2][x|a_3]…[x|a_n]
}
}
}
}
}
$$

$$=
\sum\limits_{x=1}^{k}{
\varphi(x)
\sum\limits_{a_1=1}^{k}{
[x|a_1]
\sum\limits_{a_2=1}^{k}{
[x|a_2]
\sum\limits_{a_3=1}^{k}{
[x|a_3]
…
\sum\limits_{a_n=1}^{k}{
[x|a_n]
}
}
}
}
}
$$

$$=
\sum\limits_{x=1}^{k}{
\varphi(x)
{\left \lfloor \frac{k}{x} \right \rfloor}^{n}
}
$$

用线性筛将 $\varphi$ 函数筛出，用快速幂暴力求 ${\left \lfloor \frac{k}{x} \right \rfloor}^{n}$ 

```cpp
#include <stdio.h>
#include <ctype.h>
#define int long long
#define p 1000000007
#define N 1000001
namespace stream {
template <typename T> inline T read() {
    T n = 0, m = 0;
    char c = getchar();

    while (!isdigit(c)) {
        m |= c == '-';
        c = getchar();
    }

    while (isdigit(c)) {
        n = n * 10 + c - '0';
        c = getchar();
    }

    return m ? -n : n;
}
template <typename T> inline void write(T n, char c) {
    int tot = 0, a[101];

    if (n < 0)
        n = -n, putchar('-');

    while (n)
        a[++tot] = n % 10, n /= 10;

    if (!tot)
        putchar('0');

    while (tot)
        putchar(a[tot--] + 48);

    if (c)
        putchar(c);
}
}
using namespace stream;
int prime[N], phi[N], tot;
bool v[N];
void get() {
    phi[1] = 1;

    for (int i = 2; i < N; i++) {
        if (!v[i])
            prime[++tot] = i, phi[i] = i - 1;

        for (int j = 1; j <= tot && prime[j]*i < N; j++) {
            v[prime[j]*i] = 1;

            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }

            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
}
int power(int n, int m) {
    int ans = 1;

    while (m) {
        if (m & 1)
            ans = 1ll * ans * n % p;

        m >>= 1;
        n = 1ll * n * n % p;
    }

    return ans;
}
signed main() {
    get();
    int n = read<int>(), k = read<int>(), ans = 0;

    for (int i = 1; i <= k; i++) {
        ans += phi[i] * power(k / i, n) % p;
        ans %= p;
    }

    write<int>(ans, 10);
    return 0;
}
```

---

## 作者：JWRuixi (赞：1)

经过一番思考，我成功荣获最劣解。

- 题意

给定 $n$ 和 $k$，求：

$$\sum^n_{a_1=1}\sum^n_{a_2=1}\dots\sum^n_{a_k=1}\gcd(a_1,a_2,a_3,\dots,a_k)\ mod\ 1000000007$$

- 解法

Solution 1

这里提供最劣解 $O(n \sqrt n)$ 解法。

考虑 gcd 单调不增，就是说 $1 \le gcd \le n$，所以可以枚举 gcd。

对于一个可能的最大公约数 $g$，考虑什么样的数运算后会得到这个结果，即去除因子 $g$ 后，$k$ 个数互质，这些数可以从区间 $[1,\frac{k}{g}]$ 取。

所以可以设 $f_s=\sum^n_{a_1=1}\sum^n_{a_2=1}\dots\sum^n_{a_k=1}[\gcd(a_1,a_2,a_3,\dots,a_k)=1]$。

那么可以容斥一下，先随便取，在减去 gcd 大于 $g$ 的情况，即：

$$f_s = s^k - \sum_{i=2}^s f_{\frac{s}{i}}$$ 

解释一下就是枚举这个大于 $g$ 的 gcd 为 $x \times g$，$x$ 的取值范围显然是 $[2,s]$，那么就可以套用上面的 $f$。

可以数论分块，预处理复杂度根号级别，线性运算，总复杂度，$O(n\log n + n\sqrt n + n)$。

Solution 2

怎么优化？推柿子！！

$$\sum^n_{a_1=1}\sum^n_{a_2=1}\dots\sum^n_{a_k=1}\gcd(a_1,a_2,a_3,\dots,a_k)=\sum_{1 \le a_1,a_2,\dots a_k \le n}\sum_{d | \gcd(a_1,a_2,\dots,a_k)}\varphi(d)$$

换个顺序就是：

$$\sum_{d=1}^n \varphi(d)\lfloor \frac{n}{d}\rfloor^k$$

那线性筛直接秒杀。

- code

Solution 1

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 2e5 + 500, mod = 1e9 + 7;

int n, k, f[maxn], ans;

int ksm (int b, int k) {
	int res = 1;
	for (; k; k >>= 1, b = b * b % mod) if (k & 1) res = res * b % mod;
	return res;
}

signed main () {
	k = read(), n = read();
	f[1] = 1;
	for (int i = 2; i <= n; i++) {
		f[i] = ksm(i, k);
		for (int l = 2, r; l <= i; l = r + 1) {
			r = i / (i / l);
			f[i] = (f[i] - (r - l + 1) * f[i / l] % mod + mod) % mod;
		}
	}
	for (int i = 1; i <= n; i++) ans = (ans + i * f[n / i] % mod) % mod;
	write(ans);
}
```

Solution 2

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
 	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9')   t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn = 2e5 + 500, mod = 1e9 + 7;

int n, k, pr[maxn], tot, phi[maxn], sphi[maxn], ans;
bool vis[maxn];

void init () {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) pr[++tot] = i, phi[i] = i - 1;
		for (int j = 1; j <= tot && i * pr[j] <= n; j++) {
			vis[i * pr[j]] = 1;
			if (i % pr[j]) phi[i * pr[j]] = phi[i] * phi[pr[j]];
			else {
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
		}
	}
	for (int i = 1; i <= n; i++) sphi[i] = (sphi[i - 1] + phi[i]) % mod;
}

int ksm (int b, int k) {
	int res = 1;
	for (; k; k >>= 1, b = b * b % mod) if (k & 1) res = res * b % mod;
	return res;
}

signed main () {
	k = read(), n = read();
	init();
	for (int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans = (ans + (sphi[r] - sphi[l - 1] + mod) % mod * ksm(n / l, k) % mod) % mod;
	}
	write(ans);
}
```

---

## 作者：Arghariza (赞：1)

草，竟然不用整除分块。

---

不妨把题目一大堆西格玛写成这样：

$$ans=\sum_{1\le a_1,a_2,...,a_n\le k}\gcd_{i=1}^{n}\left(a_i\right)$$

然后由 $id=\varphi *I$：

$$\begin{aligned}ans&=\sum_{1\le a_1,a_2,...,a_n\le k}\gcd_{i=1}^{n}\left(a_i\right)\\&=\sum_{1\le a_1,a_2,...,a_n\le k}\;\sum\limits_{d\mid a_1,d\mid a_2,...,d\mid a_n}\varphi(d)\\&=\sum\limits_{d=1}^{k}\varphi(d)\left\lfloor\dfrac{k}{d}\right\rfloor^n\end{aligned}$$

然后这个就可以开始整除分块了，其实暴力也能过。

整除分块复杂度 $O(\sqrt{n}\log k)$。

---

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

const int mod = 1e9 + 7;
const int maxn = 1e5 + 100;
int n, k, tot, pr[maxn], v[maxn], phi[maxn];

int ksm(int p, int q) {
    int res = 1;
    while (q) {
        if (q & 1) res = res * p % mod;
        p = p * p % mod, q >>= 1;
    }
    return res;
}

void init(int lim) {
    phi[1] = 1;
    for (int i = 2; i <= lim; i++) {
        if (!v[i]) pr[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && i * pr[j] <= lim; j++) {
            v[i * pr[j]] = 1;
            if (i % pr[j] == 0) {
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            }
            phi[i * pr[j]] = phi[i] * phi[pr[j]];
        }
    }
    for (int i = 2; i <= lim; i++) phi[i] = (phi[i] + phi[i - 1]) % mod;
}

int calc(int n, int k) {
    int res = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        res = (res + (phi[r] - phi[l - 1] + mod) % mod * ksm(n / l, k)) % mod;
    }
    return res;
}

signed main() {
    k = read(), n = read();
    init(1e5);
    write(calc(n, k)), puts("");
    return 0;
}
```

---

## 作者：Dreamweaver (赞：1)

# Description
给定 $n,k$，求 $\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}\dots\sum^k_{a_n=1}gcd(a_1,a_2,a_3,\dots,a_n)\bmod \ 1000000007$ 的值。
# Solution
莫比乌斯反演。

也许有不用反演的方法，但是本萌新只会反演。

$\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}\dots\sum^k_{a_n=1}\gcd(a_1,a_2,a_3,\dots,a_n)$

$=\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}\dots\sum^k_{a_n=1}id(\gcd(a_1,a_2,a_3,\dots,a_n))$

$=\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}\dots\sum^k_{a_n=1}\sum^k_{d|\gcd(a_1,a_2,a_3,\dots,a_n)}\varphi(d)$



$=\sum^k_{d=1}\varphi(d)\sum^k_{a_1=1}\sum^k_{a_2=1}\sum^k_{a_3=1}\dots\sum^k_{a_n=1}[d|\gcd(a_1,a_2,a_3,\dots,a_n)]$


$=\sum^k_{d=1}\varphi(d)\sum^k_{a_1=1}[d|a_1]\sum^k_{a_2=1}[d|a_2]\sum^k_{a_3=1}[d|a_3]\dots\sum^k_{a_n=1}[d|a_n]$


$=\sum^k_{d=1}\varphi(d)\left\lfloor\dfrac{k}{d}\right\rfloor^n$


直接线性筛预处理欧拉函数即可，复杂度 $O(k \log n)$。

用杜教筛的话可以做到 $10^{10}$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define re register
#define maxn 100010
#define int long long
#define Orz cout<<"stO %王队% Orz"<'\n';
int n,k,pri[maxn],phi[maxn],cnt,ans;
bool vis[maxn];
void pre(int n)
{
	phi[1]=1;
	for(re int i=2;i<=n;++i)
	{
		if(!vis[i])
			pri[++cnt]=i,phi[i]=i-1;
		for(re int j=1;j<=cnt&&pri[j]*i<=n;++j)
		{
			vis[i*pri[j]]=1;
			if(i%pri[j]==0)
			{
				phi[i*pri[j]]=phi[i]*pri[j];
				break;	
			}
			phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
}//线性筛欧拉函数 
int qpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)		ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans%mod;
}//快速幂 
signed main()
{
	cin>>n>>k;
	pre(k);//预处理 
	for(re int d=1;d<=k;++d)
		ans=(ans+phi[d]*qpow(k/d,n)%mod)%mod;	//统计答案 
	cout<<ans;
	return 0;
}
```



---

## 作者：jijidawang (赞：0)

UPD on 8.14 更新时间复杂度分析
***
这里欧拉反演的优势就体现出来了 .

主要就是借助范德蒙德卷积恒等式 $\varphi*1=\mathrm{Id}$，也就是
$$\sum_{d\mid n}\varphi(d)=n$$
接下来对原式进行一些基本操作

$$\begin{aligned}\sum_{a_1=1}^k\sum_{a_2=1}^k\dots\sum_{a_n=1}^k\gcd(a_1,a_2,\dots,a_n)&=\sum_{a_1=1}^k\sum_{a_2=1}^k\dots\sum_{a_n=1}^k\sum_{d\mid\gcd(a_1,a_2,\dots,a_n)}\varphi(d)\\&=\sum_{d=1}^k\varphi(d)\left\lfloor\dfrac kd\right\rfloor^n\end{aligned}$$

然后就是老生常谈的东西了，先整除分块，然后肯定要线性筛欧拉函数 .

此时的时间复杂度是 $O(k+\sqrt n\log k)$，带一个快速幂的 $\log$ .

然而指数一定我们就可以线性筛 $f(x)=x^n$，因为 $f$ 是完全积性函数所以非常好实现 .

然而此时预处理的时间复杂度变成
$$T(n)=\sum_{\substack{p\le n\cr p\text{ is prime}}}\log p$$
根据素数定理 $\pi(n)\sim\dfrac n{\ln n}$，有预处理时间复杂度上界 $T(n)=O\left(\pi(n)\log n+n\right)=O(n)$

于是可以做到 $O(k+\sqrt n)$，非常的优秀啊 .

目前是最优解 rk4 .

![](https://cdn.luogu.com.cn/upload/image_hosting/69lzxevs.png)

至少在我发这篇题解的时候是这样，前面仨老哥都是带 $\log$ 复杂度然后卡卡常 .

可能我代码自带大常数吧 QwQ .

代码：
```cpp
#include <bits/stdc++.h>
template<typename T>
inline T chkmin(T& x, const T& y){if (x > y) x = y; return x;}
template<typename T>
inline T chkmax(T& x, const T& y){if (x < y) x = y; return x;}
using namespace std;
const int N = 114514, P = 1e9+7;
bool notprime[N];
int n, k, phi[N], power[N];
vector<int> plist;
inline int qpow(int a, int n)
{
	int ans = 1;
	while (n)
	{
		if (n & 1) ans = 1ll * ans * a % P;
		a = 1ll * a * a % P; n >>= 1;
	} return ans; 
}
inline void linear_sieve()
{
    notprime[1] = true; phi[1] = power[1] = 1;
    for (int i=2; i<=k; i++)
    {
        if (!notprime[i]){plist.emplace_back(i); power[i] = qpow(i, n); phi[i] = i-1;}
        for (auto x : plist)
        {
            int now = i*x;
            if (now > k) break;
            notprime[now] = true;
            if (!(i%x)){phi[now] = phi[i] * x; power[now] = 1ll * power[i] * power[x] % P; break;}
            power[now] = 1ll * power[i] * power[x] % P; phi[now] = phi[i] * phi[x];
        }
    }
	for (int i=1; i<=k; i++) phi[i] = (phi[i] + phi[i-1]) % P;
}
int main()
{
	scanf("%d%d", &n, &k); linear_sieve();
	int ans = 0;
	for (int l=1, r; l <= k; l = r+1)
	{
		r = k / (k / l);
		ans = (ans + 1ll * (phi[r] - phi[l-1]) % P * power[k / l] % P) % P; 
	} printf("%d\n", (ans + P) % P);
	return 0;
}
```

---

