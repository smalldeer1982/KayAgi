# [ABC208F] Cumulative Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc208/tasks/abc208_f

非負整数 $ n,\ m $ に対して関数 $ f(n,\ m) $ を正の整数 $ K $ を用いて次のように定めます。

$ \displaystyle\ f(n,\ m)\ =\ \begin{cases}\ 0\ &amp;\ (n\ =\ 0)\ \\ n^K\ &amp;\ (n\ \gt\ 0,\ m\ =\ 0)\ \\ f(n-1,\ m)\ +\ f(n,\ m-1)\ &amp;\ (n\ \gt\ 0,\ m\ \gt\ 0)\ \end{cases} $

$ N,\ M,\ K $ が与えられるので、$ f(N,\ M) $ を $ (10\ ^\ 9\ +\ 7) $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 0\ \leq\ N\ \leq\ 10^{18} $
- $ 0\ \leq\ M\ \leq\ 30 $
- $ 1\ \leq\ K\ \leq\ 2.5\ \times\ 10^6 $
- 入力は全て整数である。

### Sample Explanation 1

$ K\ =\ 2 $ の時、 $ n\ \leq\ 3,\ m\ \leq\ 4 $ における $ f(n,\ m) $ の値は次のようになります。 $ m\ =\ 0 $ $ m\ =\ 1 $ $ m\ =\ 2 $ $ m\ =\ 3 $ $ m\ =\ 4 $ $ n\ =\ 0 $ $ 0 $ $ 0 $ $ 0 $ $ 0 $ $ 0 $ $ n\ =\ 1 $ $ 1 $ $ 1 $ $ 1 $ $ 1 $ $ 1 $ $ n\ =\ 2 $ $ 4 $ $ 5 $ $ 6 $ $ 7 $ $ 8 $ $ n\ =\ 3 $ $ 9 $ $ 14 $ $ 20 $ $ 27 $ $ 35 $

## 样例 #1

### 输入

```
3 4 2```

### 输出

```
35```

## 样例 #2

### 输入

```
0 1 2```

### 输出

```
0```

## 样例 #3

### 输入

```
1000000000000000000 30 123456```

### 输出

```
297085514```

# 题解

## 作者：do_while_true (赞：4)

给定 $n,m,k$，计算 $f(n,m)$ 的值，模 $10^9+7$．

$$
\begin{aligned}
\displaystyle f(n, m)& =
\begin{cases}
0 & (n = 0) \newline
\\
n^K & (n \gt 0, m = 0) \newline
\\
f(n-1, m) + f(n, m-1) & (n \gt 0, m \gt 0)
\end{cases}
\end{aligned}
$$

$0 \leq N \leq 10^{18},0 \leq M \leq 30,1 \leq K \leq 2.5 \times 10^6$．

易发现答案为 $1^k,2^k,3^k,\cdots ,n^k$ 的 $m$ 阶前缀和的第 $n$ 项值。

考虑 $i^k$ 对答案的贡献次数，是对 $f_0=1,f_k=0(k>0)$ 的数组作 $m$ 阶前缀和后的第 $(n-i)$ 项，也就是 $f_{n-i}$。其值为 $\binom{n-i+m-1}{m-1}$．

从组合意义上考虑，作一阶前缀和为 $1,1,1,\cdots$，设后面第 $i$ 阶前缀和的 $f_j=g_{i,j}$，有递推式 $g_{i,j}=g_{i-1,j}+g_{i,j-1}$，恰为只能向右、下走的格点计数。

故贡献的次数为 $(1,0)\to (m,n-i)$ 的路径数，即为 $\binom{n-i+m-1}{m-1}$。

所以答案为：

$$
\sum_{i=0}^n i^k\binom{n-i+m-1}{m-1}
$$

考虑 $i^k\binom{n-i+m-1}{m-1}$ 中 $i^k$ 为关于 $i$ 的 $k$ 次单项式。

$\binom{n-i+m-1}{m-1}=\frac{(n-i+m-1)!}{(m-1)!(n-i)!}$，其中 $(n-i+m-1)!$ 为关于 $i$ 的 $(n-i+m-1)$ 次多项式，$(n-i)!$ 为关于 $i$ 的 $(n-i)$ 次多项式，$(m-1)!$ 是常数。

故 $i^k\binom{n-i+m-1}{m-1}$ 是关于 $i$ 的 $(m+k-1)$ 次多项式。

对于 $i\in [0,n]$，对这个多项式求和即为答案。

其可以写成 $ans=a_0s_0+a_1s_1+a_2s_2+\cdots+a_{m+k-1}s_{m+k-1}$ 的形式，其中 $s_i=\sum\limits_{j=0}^ij^k$．

由于 $s_i$ 是关于 $i$ 的 $(i+1)$ 次多项式，故答案为关于 $n$ 的 $(m+k)$ 次多项式。

设 $l=m+k+1$，选出前 $l$ 个连续的整数，算出其作 $m$ 阶前缀和的答案，拉格朗日插值即可。

时间复杂度 $\mathcal{O}(mk)$．

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
const ll mod = 1000000007;
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template <typename T> T Add(T x, T y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
template <typename T> T Mod(T x) { return (x >= mod) ? (x - mod) : (x < 0 ? (x + mod) : x); }
template <typename T> T Mul(T x, T y) { return x * y % mod; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r <<1) + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
ll qpow(ll x, ll y) { ll sumq = 1; while(y) { if(y & 1) sumq = sumq * x % mod; x = x * x % mod; y >>= 1; } return sumq; }
const int N = 2600100;
ll n;
int m, k;
ll a[N], fac[N], inv[N], pre[N], suf[N], ans;
signed main() {
	read(n); read(m); read(k); int l = m+k+1;
	if(!n) { puts("0");	return 0; }
	for(int i = 1; i <= l; ++i) a[i] = qpow(i, k);
	for(int j = 1; j <= m; ++j)
		for(int i = 1; i <= l; ++i)
			a[i] = Add(a[i], a[i-1]);
	inv[0] = fac[0] = 1; for(int i = 1; i <= l; ++i) fac[i] = fac[i-1] * i % mod;
	inv[l] = qpow(fac[l], mod-2); n %= mod;
	for(int i = l-1; i; --i) inv[i] = inv[i+1] * (i+1) % mod;
	pre[0] = 1; for(int i = 1; i <= l; ++i) pre[i] = pre[i-1] * (n - i) % mod;
	suf[l+1] = 1; for(int i = l; i; --i) suf[i] = suf[i+1] * (n - i) % mod;
	for(int i = 1; i <= l; ++i)
		ans = Add(ans, Mod(a[i] * pre[i-1] % mod * suf[i+1] % mod * inv[i-1] % mod * inv[l-i] % mod * (((l-i)&1) ? -1 : 1)));
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：iiiiiyang (赞：3)

[迷人的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17438567.html)

[题目链接](https://www.luogu.com.cn/problem/AT_abc208_f)

观察式子得到答案为序列 $1^k,2^k,\cdots,n^k$ 的 $m$ 阶前缀和第 $n$ 项的值。

记 $i^k$ 对答案的贡献为 $f_i$，第 $j$ 阶前缀和的 $f_i = g_{j,i}$，那么有递推式子 $g_{j,i} = g_{j - 1,i} + g_{j,i - 1}$。这个东西是从 $(i,j)$ 走向 $(0,0)$ 的路径计数，于是 $f_i$ 对应了 $(1,0) \to (m,n - i)$ 的路径数，根据组合数学这个值是 $\binom{m - 1 + n - i}{m - 1}$。由此得到答案式子：
$$
\begin{aligned}
 &\sum_{i = 0}^n \binom{m - 1 + n - i}{m - 1} i^k \\
=&\sum_{i = 0}^n \dfrac{(m - 1 + n - i)!}{(m - 1)!(n - i)!} i^k
\end{aligned}
$$

以下多项式均为关于 $i$：前缀和是 $1$ 次多项式，$i^k$ 是 $k$ 次多项式；$(m - 1 + n - i)!$ 是 $m - 1 + n - i$ 次多项式，$(n - i)!$ 是 $n - i$ 次多项式，$(m - 1)!$ 则是常数，这个分数约出来是个 $m - 1$ 次多项式。综上所述，这个式子是一个 $k + m$ 次多项式。使用拉格朗日插值带入 $k + m + 1$ 个点值即可得出多项式。加上求逆元和前缀和啥的，总的时间复杂度是 $\mathcal O(k \log k + (k + m)m)$。代码实现使用的递推求逆元。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) (x*y/gcd(x,y))
#define lg(x,y)  __lg(x,y)
using namespace std;

template<typename T=int> inline T read()
{
    T s=0,w=1; char c=getchar();
    while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
    while(isdigit(c)) s=(s<<1)+(s<<3)+(c^48),c=getchar();
    return s*w;
}
template<typename T=int> inline void write(T x,char ch)
{
    if(x<0) x=-x,putchar('-');
    static char stk[25]; int top=0;
    do {stk[top++]=x%10+'0',x/=10;} while(x);
    while(top) putchar(stk[--top]);
    putchar(ch);
    return;
}

namespace MyTool
{
    static const int Mod=1e9+7;
    template<typename T> inline void Swp(T &a,T &b) {T t=a;a=b;b=t;}
    template<typename T> inline void cmax(T &a,T b) {a=a>b?a:b;}
    template<typename T> inline void cmin(T &a,T b) {a=a<b?a:b;}
    template<typename T> inline void Madd(T &a,T b) {a=a+b>Mod?a+b-Mod:a+b;}
    template<typename T> inline void Mdel(T &a,T b) {a=a-b<0?a-b+Mod:a-b;}
    template<typename T> inline void Mmul(T &a,T b) {a=a*b%Mod;}
    template<typename T> inline void Mmod(T &a)     {a=(a%Mod+Mod)%Mod;}
    template<typename T> inline T    Cadd(T a,T b)  {return a+b>=Mod?a+b-Mod:a+b;}
    template<typename T> inline T    Cdel(T a,T b)  {return a-b<0?a-b+Mod:a-b;}
    template<typename T> inline T    Cmul(T a,T b)  {return a*b%Mod;}
    template<typename T> inline T    Cmod(T a)      {return (a%Mod+Mod)%Mod;}
    inline int qpow(int a,int b) {int res=1; while(b) {if(b&1) Mmul(res,a); Mmul(a,a); b>>=1;} return res;}
    inline int qmul(int a,int b) {int res=0; while(b) {if(b&1) Madd(res,a); Madd(a,a); b>>=1;} return res;}
    inline int Qpow(int a,int b) {int res=1; while(b) {if(b&1) res=qmul(res,a); a=qmul(a,a); b>>=1;} return res;} 
}
using namespace MyTool;

inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}

bool Mbe;

namespace LgxTpre
{
    static const int MAX=2600010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;

    int n,m,k,l,ans;
    int a[MAX],fac[MAX],inv[MAX],pre[MAX],suf[MAX];

    inline void lmy_forever()
    {
    	n=read(),m=read(),k=read(),l=m+k+1; Mmod(n);
    	if(!n) return puts("0"),void();
    	for(int i=1;i<=l;++i) a[i]=qpow(i,k);
    	for(int i=1;i<=m;++i) for(int j=1;j<=l;++j) Madd(a[j],a[j-1]);
    	inv[0]=fac[0]=1;           for(int i=1;i<=l;++i) fac[i]=Cmul(fac[i-1],i);
    	inv[l]=qpow(fac[l],Mod-2); for(int i=l-1;i;--i)  inv[i]=Cmul(inv[i+1],i+1);
    	pre[0]=1;                  for(int i=1;i<=l;++i) pre[i]=Cmul(pre[i-1],n-i);
    	suf[l+1]=1;                for(int i=l;i;--i)    suf[i]=Cmul(suf[i+1],n-i);
    	for(int i=1;i<=l;++i) Madd(ans,Cmul(a[i],Cmul(Cmod(Cmul(Cmul(inv[i-1],inv[l-i]),(l-i)&1?-1ll:1ll)),Cmul(pre[i-1],suf[i+1]))));
    	write(ans,'\n');
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

## 作者：mojoege (赞：2)

## 分析
前置知识：[拉格朗日插值](https://www.bilibili.com/video/BV1ZC4y1p77B/?spm_id_from=333.337.search-card.all.click&vd_source=ae09fb18b380172d3c1330f4818beb99) 或 [OI-wiki](https://oi-wiki.org/math/numerical/interp/)；多项式请参考**七年级上册数学书**。

观察式子，最终所有式子肯定都是到第二种情况，也就是 $i^k$ 其中 $1\le i\le n$，问题就变成了每一个 $i^k$ 对答案的贡献是多少，然后累加一下。	

假设 $a_{i,j}$ 为 $n=i,m=j$ 时的总方案数，稍微打一下表，发现 $a_{i,j}=a_{i-1,j}+a_{i,j-1}$，这很类似于“只能往下或左走，请问有多少种方案”的问题，不难得出在方案数有 $C_{n-i+m-1}^{m-1}$ 其中开始位置为 $(i,0)$，终点为 $(n,m)$，也就是 $i^k$ 对答案的贡献。故最后答案为：
$$
\sum_{i=0}^{n}i^k\times C_{n-i+m-1}^{m-1}
$$
上面的办法肯定是会爆的，考虑拉格朗日插值，我们需要求 $f(n)$ 也就是只用找到多项式次数 $l$ 再加上 $0$ 次，也就是 $l+1$ 个观测点的值套一遍公式就能求出来。那次数 $l$ 是多少呢？考虑把上面的多项式拆开来看（把组合数拆开），变成：
$$
\sum_{i=0}^{n}i^k \times \frac{(n-i+m-1)!}{(m-1)!(n-i)!}
$$
这里我们要求的是关于 $i$ 的次数。$i^k$ 显然是 $k$ 次的，后面 $(n-i+m-1)!$ 是 $n-i+m-1$ 次的（$n!$ 由 $n$ 个有关于 $n$ 的式子相乘，也就是 $n$ 次），$(n-i)!$ 是 $n-i$ 次的，$(m-1)!$ 是常数（式子里没有 $i$）。当然，前面的求和符号也得算上 $1$ 次，所以最终这个式子是 $k+m$ 次的。

根据拉格朗日插值，需要带入 $k+m+1$ 个点带入多项式，现在上面的公式中的 $n$ 就变成了次数 $l=k+m$。自行阅读一下 OI-wiki，发现我们只需要使用**横坐标是连续整数的拉格朗日插值**进行操作，也就是这个公式：
$$
f(x)=\sum_{i=1}^{n+1}(-1)^{n-i+1}y_i \cdot \frac{\prod_{j=1}^{n+1}(x-j)}{(i-1)!(n-i+1)!(x-i)}
$$
把 $x$ 替换成 $n$，$1 \to n+1$ 替换成 $1\to l+1$。接下来就是 $y_i$ 的问题了，拉格朗日插值中的 $y_i$ 不仅是单个 $i_k$ 的贡献，$i^k$ 的 $m$ 阶前缀和，所以要预处理一下 $y_i$，最终就是这个问题的答案了。我们还需要预处理一下 $l-i$ 的前后缀积、阶乘的逆元才能快速求解。

注意：要开 `__int128`，~~不开也行，不过得抽象地模一下~~。

## 代码
```cpp
#include <bits/stdc++.h>
#define int __int128
using namespace std;

const int mod = 1e9 + 7;
const int N = 2.5e6 + 5;
long long n, m, k, ans;
int a[N], inv[N], fac[N], pre[N], suf[N];

int ksm(int a, int b){
	int res = 1;
	while (b){
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

signed main(){
	cin >> n >> m >> k;
	if (n == 0) return cout <<"0", 0;
	int l = m + k + 1;
	for (int i = 1; i <= l; i++) a[i] = ksm(i, k);
	for (int j = 1; j <= m; j++){
		for (int i = 1; i <= l; i++) a[i] = (a[i] + a[i - 1]) % mod;//预处理 y_i
	}
	inv[0] = fac[0] = 1;
	for (int i = 1; i <= l; i++) fac[i] = fac[i - 1] * i % mod;
	inv[l] = ksm(fac[l], mod - 2);
	for (int i = l - 1; i >= 1; i--) inv[i] = (i + 1) * inv[i + 1] % mod;//预处理阶乘的逆元
	pre[0] = suf[l + 1] = 1;
	for (int i = 1; i <= l; i++) pre[i] = pre[i - 1] * (n - i) % mod;//预处理前后缀积
	for (int i = l; i >= 1; i--) suf[i] = suf[i + 1] * (n - i) % mod;
	for (int i = 1; i <= l; i++){
		ans = (ans + (a[i] * pre[i - 1] % mod * suf[i + 1] % mod * inv[i - 1] % mod * inv[l - i] % mod * (((l - i) & 1) ? -1 : 1) + mod) % mod) % mod;//拉格朗日插值
	}
	cout << ans;
	return 0;
}
```

---

## 作者：xieziheng (赞：1)

其他两篇题解讲的很清楚了，我就是补充一下，就是这题其实是可以做到 $\mathcal{O}(k+m)$ 的。

记题目中说的那个为 $f(n)$

由拉格朗日插值，有

$f(n)=\sum_{i=0}^{k+m} f(i) \prod_{j<i} {\frac {n-j} {i-j}} \prod_{j>i} {\frac {n-j} {i-j}}$

$=\sum_{i=0}^{k+m} f(i) \frac {\prod_{j \neq i} (n-j)} {{(-1)^{k+m-i}} {i!}  {(k+m-i)!}}$

$=\sum_{i=0}^{k+m} f(i) \frac {\frac {\prod_{j=0}^{k+m} (n-j)} {n-i}} {{(-1)^{k+m-i}} {i!}  {(k+m-i)!}}$

而推一下就注意到 $f(n)=\sum_{i=1}^{n} i^k \times \frac {\prod_{j=n-i+1}^{n+m-i-1} j} {(m-1)!}$，是关于 $n$ 的 $k+m$ 次多项式。所以线性筛一下 $i^k$，算 $f(n)$ 就是每次 $i$ 加一就乘一个 $n-i+1$ 再除掉一个 $n+m-i$，除可以预处理 $n+m-i$ 前缀后缀积，但是其实会有 $\bmod {10^9+7}$ 余 $0$ 的，要跳过。然后算的时候也可以预处理 $n-i$ 的前后缀积。都是线性的，注意 $n$ 很大每次算的时候要多模一次。

但是这玩意好像常数有点大，跑得还没 $\mathcal{O} (k+m)m$ 快。

```cpp
#pragma GCC optimize("O2,O3,Ofast,inline,unroll-loops")
#pragma GCC target("avx2,sse4")
#include <bits/stdc++.h>
#define il inline
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
il ll qp(ll a,ll b){
    ll ans=1ll;a%=mod;
    while(b){
        if(b&1) ans=(ans*a)%mod;
        a=(a*a)%mod,b>>=1;
    }
    return ans;
}
il void add(ll &x,ll y){x=(x+y>=mod?x+y-mod:x+y);}
il void del(ll &x,ll y){x=(x<y?x-y+mod:x-y);}
const int N=2.5e6+50,M=1e6+5;
ll n,sum;int m,k,p[M],cnt,f[N],fac[N],inv[N],pre[N],suf[N];
bitset<N> vis;
il void init(){
    f[1]=1ll;ll x=1ll,y,z,u,v,w;
    for(int i=2;i<=k+m;++i){
        if(!vis[i]) p[++cnt]=i,f[i]=qp(i,k);
        for(int j=1;j<=cnt && i*p[j]<=k+m;++j){
            vis[i*p[j]]=1,f[i*p[j]]=(1ll*f[i]*f[p[j]])%mod;
            if(i%p[j]==0) break;
        }
    }
    for(int i=1;i<=m-1;++i) x=(x*1ll*i)%mod;
    x=qp(x,mod-2ll),y=1ll;
    for(ll j=n+m-1ll;j>=n+1ll;--j) y=(j%mod*y)%mod;
    pre[0]=suf[k+m+1]=1ll;
    for(int i=1;i<=k+m;++i) u=(n+m-i)%mod,pre[i]=((u?u:1ll)*pre[i-1])%mod;
    for(int i=k+m;i;--i) u=(n+m-i)%mod,suf[i]=((u?u:1ll)%mod*suf[i+1])%mod;
    z=qp(suf[1],mod-2ll),w=1ll;
    for(int i=1;i<=k+m;++i){
        y=((n-i+1ll)%mod*y%mod*pre[i-1]%mod*suf[i+1]%mod*z)%mod;
        f[i]=(f[i-1]+1ll*f[i]*x%mod*y)%mod;
    }
}
ll x,y=1ll,z;
int main(){
    scanf("%lld%d%d",&n,&m,&k);if(!n){printf("0");exit(0);}
    if(!m) {printf("%lld",qp(n,k));exit(0);}
    init();
    if(n<=1ll*k+m){printf("%lld",f[n]);exit(0);}
    fac[0]=1ll;
    for(int i=1;i<=k+m;++i) fac[i]=(fac[i-1]*1ll*i)%mod;
    inv[k+m]=qp(fac[k+m],mod-2ll);
    for(int i=k+m-1;i>=0;--i) inv[i]=(inv[i+1]*(i+1ll))%mod;
    suf[k+m+1]=1ll;
    for(int i=k+m;i;--i) suf[i]=((n-i)%mod*suf[i+1])%mod;
    for(int i=0;i<=k+m;++i){
        x=(1ll*f[i]*inv[i]%mod*inv[k+m-i]%mod*y%mod*suf[i+1])%mod;
        if((k+m-i)&1) del(sum,x);
        else add(sum,x);
        y=((n-i)%mod*y)%mod;
    }
    printf("%lld",sum);
    return 0;
}
```

---

