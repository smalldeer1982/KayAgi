# [ABC231G] Balls in Boxes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc231/tasks/abc231_g

$ 1 $ から $ N $ の番号がついた $ N $ 個の箱があります。最初、箱 $ i $ には $ A_i $ 個のボールが入っています。

あなたは次の操作を $ K $ 回繰り返します。

- $ N $ 個の箱の中から等確率で $ 1 $ 個選ぶ(この選択は操作ごとに独立である)。選んだ箱にボールを $ 1 $ 個追加する。

$ K $ 回の操作が終了した後で箱 $ i $ に入っているボールの個数を $ B_i $ とするとき、**スコア**はボールの個数の総積 $ \prod_{i=1}^{N}B_i $ になります。

スコアの期待値を $ \bmod\ 998244353 $ で求めてください。

## 说明/提示

### 注意

求める期待値が既約分数 $ p/q $ で表されるとき、$ rq\equiv\ p\ \pmod{998244353} $ かつ $ 0\leq\ r\ <\ 998244353 $ を満たす整数 $ r $ がこの問題の制約のもとで一意に定まります。この $ r $ が求める値です。

### 制約

- $ 1\ \leq\ N\ \leq\ 1000 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $

### Sample Explanation 1

操作の結果、スコアは次のようになります。 - 操作で箱 $ 1 $ を選んだとき、$ 2\times\ 2\times\ 3=12 $ - 操作で箱 $ 2 $ を選んだとき、$ 1\times\ 3\times\ 3=9 $ - 操作で箱 $ 3 $ を選んだとき、$ 1\times\ 2\times\ 4=8 $ したがって、求める期待値は $ \frac{1}{3}(12+9+8)=\frac{29}{3} $ となります。これを $ \bmod\ 998244353 $ で表すと $ 665496245 $ になります。

### Sample Explanation 2

操作の結果、スコアは次のようになります。 - $ 1 $ 回目の操作で箱 $ 1 $ を選び、$ 2 $ 回目の操作で箱 $ 1 $ を選んだとき、$ 3\times\ 2=6 $ - $ 1 $ 回目の操作で箱 $ 1 $ を選び、$ 2 $ 回目の操作で箱 $ 2 $ を選んだとき、$ 2\times\ 3=6 $ - $ 1 $ 回目の操作で箱 $ 2 $ を選び、$ 2 $ 回目の操作で箱 $ 1 $ を選んだとき、$ 2\times\ 3=6 $ - $ 1 $ 回目の操作で箱 $ 2 $ を選び、$ 2 $ 回目の操作で箱 $ 2 $ を選んだとき、$ 1\times\ 4=4 $ したがって、求める期待値は $ \frac{1}{4}(6+6+6+4)=\frac{11}{2} $ となります。

## 样例 #1

### 输入

```
3 1
1 2 3```

### 输出

```
665496245```

## 样例 #2

### 输入

```
2 2
1 2```

### 输出

```
499122182```

## 样例 #3

### 输入

```
10 1000000000
998244350 998244351 998244352 998244353 998244354 998244355 998244356 998244357 998244358 998244359```

### 输出

```
138512322```

# 题解

## 作者：tribool4_in (赞：6)

CF1842G 的弱化版。思路可能跟已有题解不太一样？

考虑设第 $i$ 次操作随机选择的盒子编号为 $x_i$。于是答案就是 $\displaystyle E(\prod_{i=1}^n (a_i+\sum_{j=1}^m[x_j=i]))$。考虑把乘积拆开，变成 $(m+1)^n$ 项，利用期望的线性性拆成每部分的期望之和。其中每一项为 $n$ 个东西的乘积，第 $i$ 个东西可以为 $a_i$ 或 $[x_j=i]\ (j\in[1,m])$。应当注意到若某项中存在 $x_j\neq i$ 则该项直接没有贡献（因为有乘零）。

于是考虑设 $dp_{i,k}$ 表示考虑了前 $i$ 个东西，且当前已经确定了 $k$ 个 $x_j$（即出现过 $k$ 个不同的 $j$），所有情况下乘积的期望之和。考虑第 $i$ 个东西选什么，若选 $a_i$ 则有转移 $dp_{i,k}\gets dp_{i,k}+dp_{i-1,k}\times a_i$。否则只能选择一个新的 $x_j$（因为之前已经选择的 $x_j$ 一定小于 $i$，不会造成贡献），有 $m-k$ 种选择方案；且需要满足 $x_j=i$，概率为 $\frac{1}{n}$。因此有转移 $dp_{i,k+1}\gets dp_{i,k+1}+dp_{i-1,k}\times (m-k)\times \frac{1}{n}$。答案显然为 $\displaystyle\sum_{k=1}^ndp_{n,k}$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, mod = 998244353;
int n, m, v, a[N];
int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = 1ll * res * a % mod;
        a = 1ll * a * a % mod;
        b >>= 1;
    }
    return res;
}
void upd(int &x, int v) { x += v, (x >= mod) && (x -= mod); }
int f[N][N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    f[0][0] = 1;
    int In = qpow(n, mod - 2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            upd(f[i + 1][j], 1ll * f[i][j] * a[i + 1] % mod);
            if (j < n) upd(f[i + 1][j + 1], 1ll * f[i][j] * (m - j) % mod * In % mod);
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++) ans += f[n][i], (ans >= mod) && (ans -= mod);
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：stntn (赞：3)

根据题意写出 EGF：

$$
Ans=\frac{k!}{n^k} [x^k] \prod_{i=1}^n \sum _j (a_i+j)\frac{x^j}{j!}
$$

简单推一下：

$$
Ans=\frac{k!}{n^k} [x^k] \prod_{i=1}^n e^x (a_i+x)
$$

$$
Ans=\frac{k!}{n^k} [x^k] e^{nx} \prod_{i=1}^n (a_i+x)
$$

后面的 $\prod_{i=1}^n (a_i+x)$ 可以 $O(n^2)$ DP 出系数，令其为 $F(x)$，则有：

$$
Ans=\frac{k!}{n^k} \sum_{i=0}^k \frac{n^i}{i!} [x^{k-i}]F(x)
$$

因为 $F(x)$ 最高只有 $x^n$ 故可调整枚举下界，并把 $k!$ 放进来：

$$
Ans=\frac{1}{n^k} \sum_{i=k-n}^k k^{\underline{k-i}}n^i [x^{k-i}]F(x)
$$

然后就做完了。

```cpp
#include<bits/stdc++.h>
#define N 1010
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define INF 0x3f3f3f3f
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
const int mod=998244353,phi=mod-1;
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int dec(int x,int y){return x-y<0?x+mod-y:x-y;}
inline int qpow(int a,int b=mod-2)
{
	int res=1;b%=phi;a%=mod;
	for(;b;b>>=1,a=1ll*a*a%mod) if(b&1) res=1ll*a*res%mod;
	return res;
}
int n,k,ans,a[N],f[N],kfac[N];
signed main()
{
	read(n,k);kfac[0]=1;f[0]=1;
	rep(i,1,n) read(a[i]),a[i]%=mod;
	rep(i,1,min(k,n)) kfac[i]=1ll*kfac[i-1]*(k-i+1)%mod;
	rep(i,1,n) per(j,i+1,0) f[j]=add(1ll*a[i]*f[j]%mod,j?f[j-1]:0);
	rep(i,max(0,k-n),k) ans=add(ans,1ll*f[k-i]*kfac[k-i]%mod*qpow(n,i)%mod);
	printf("%lld\n",1ll*ans*qpow(qpow(n,k))%mod);
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：3)

# ABC231G 题解



## 题目大意

给 $n$ 个计数器，第 $i$ 个初值是 $a_i$，$k$ 次操作，每次随机选取一个计数器 $+1$，求最终所有计数器数值乘积的期望值

## 思路分析

考虑枚举每个计数器被选了多少次，记为 $b_i$，显然对应局面的权值为 $\prod_{i=1}^n (a_i+b_i)$，而产生对应局面的概率应该为 $\dfrac{1}{n^k}\times\binom{k}{b_1,b_2,\dots,b_n}$，因此答案可以表示成：
$$
\begin{aligned}
\mathrm{ans}
&=\dfrac{1}{n^k}\sum_{b_1+b_2+\cdots+b_n=k} \binom{k}{b_1,b_2,\dots,b_n}\prod_{i=1}^n(a_i+b_i)\\
&=\dfrac{k!}{n^k}\sum_{b_1+b_2+\cdots+b_n=k}\prod_{i=1}^n\dfrac{a_i+b_i}{b_i!}
\end{aligned}
$$
考虑对每个 $\dfrac{a_i+b_i}{b_i!}$ 分别处理，建立生成函数 $\hat F_i(x)=\sum_{j=0}^\infty \dfrac{a_i+j}{j!}x^j$，可以发现：
$$
\begin{aligned}
\mathrm{ans}
&=\dfrac{k!}{n^k}\sum_{b_1+b_2+\cdots+b_n=k}\prod_{i=1}^n\dfrac{a_i+b_i}{b_i!}\\
&=\dfrac{k!}{n^k}\left(\prod_{i=1}^n\hat F_i(x)\right)[x^k]
\end{aligned}
$$
继续化简 $\hat F_i(x)$ 可以得到：
$$
\begin{aligned}
\hat F_i(x)
&=\sum_{j=0}^\infty \dfrac{a_i+j}{j!}x^j\\
&=\sum_{j=0}^\infty \dfrac{a_i}{j!}x^j+\sum_{j=1}^\infty \dfrac{1}{(j-1)!}x^j\\
&=a_ie^x+xe^x=e^x(a_i+x)
\end{aligned}
$$
回带到答案的表达式中得到：
$$
\begin{aligned}
\mathrm{ans}
&=\dfrac{k!}{n^k}\left(\prod_{i=1}^n\hat F_i(x)\right)[x^k]\\
&=\dfrac{k!}{n^k}\left(\prod_{i=1}^n e^x(x+a_i)\right)[x^k]\\
&=\dfrac{k!}{n^k}\left(e^{nx}\prod_{i=1}^n (x+a_i)\right)[x^k]
\end{aligned}
$$
因此我们只需要求 $e^{nx}\prod_{i=1}^n (x+a_i)$ 的 $x^k$ 次项系数，不难发现 $e^{nx}=\sum_{j=0}^\infty\dfrac{(nx)^j}{j!}$，假设 $\prod_{i=1}^n(x+a_i)=\sum_{j=0}^n c_jx^j$，把卷积的形式展开得到：
$$
\begin{aligned}
\mathrm{ans}
&=\dfrac{k!}{n^k}\left(e^{nx}\prod_{i=1}^n (x+a_i)\right)[x^k]\\
&=\dfrac{k!}{n^k}\sum_{j=0}^{\min(n,k)} c_j\times \dfrac{n^{k-j}}{(k-j)!}\\
&=\sum_{j=0}^{\min(n,k)}\dfrac{c_j\times k!}{n^j\times (k-j)!}\\
&=\sum_{j=0}^{\min(n,k)}\dfrac{c_jk^{\underline j}}{n^j}
\end{aligned}
$$
注意到 $c_j$ 可以暴力卷积计算，$k^{\underline j}$ 在计算的过程中维护即可

时间复杂度 $\Theta(n^2)$，用分治 + NTT 卷积优化求 $c_j$ 可以做到到 $\Theta(n\log^2n)$

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1001,MOD=998244353;
int a[MAXN],c[MAXN];
inline int ksm(int a,int b,int p=MOD) {
	int ret=1;
	while(b) {
		if(b&1) ret=ret*a%p;
		a=a*a%p;
		b=b>>1;
	}
	return ret;
}
signed main() {
	int n,k;
	scanf("%lld%lld",&n,&k);
	c[0]=1;
	for(int i=1;i<=n;++i) {
		scanf("%lld",&a[i]);
		for(int j=n;j>=1;--j) c[j]=(a[i]*c[j]+MOD+c[j-1])%MOD;
		c[0]=c[0]*a[i]%MOD;
	}
	int ans=0;
	for(int i=0,f=1;i<=n&&i<=k;++i) {
		ans=(ans+c[i]*ksm(ksm(n,i),MOD-2)%MOD*f%MOD)%MOD;
		f=f*(k-i)%MOD;
	}
	printf("%lld\n",ans%MOD);
	return 0;
}
```



---

## 作者：MurataHimeko (赞：1)

对于 $\prod b_i$ 的形式，一般来说拆成组合意义会比较好做。一共有 $n$ 个盒子，每个盒子里有 $b_i$ 个球，每个盒子取出一个球的方案数就是 $\prod b_i$。

不妨先考虑 $a_i=0$ 该怎么做。设 $f_{i,j}$ 表示操作了 $i$ 次，已经从 $j$ 个盒子里取出了球。转移分两种，一是当前球直接放到了某个盒子里，二是放到一个没被取出过球的盒子里，然后直接取出来。

$$f_{i,j}=nf_{i-1,j}+(n-j+1)f_{i-1,j-1}$$

答案为 $f_{k,n}$。

注意到这相当于在 $k$ 次操作里，选出 $n$ 次操作执行第二种转移，剩下 $k-n$ 次操作执行第一种转移，所以可以得到：

$$f_{k,n} = \binom{k}{n} n^{k-n} n!$$

回到本题，我们只需要先求出 $g_{i}$ 表示在执行 $k$ 次操作前就已经取出 $i$ 个盒子里的球的方案数，剩下的部分跟 $a_i=0$ 是一样的。

$g$ 直接求是 $O(n^2)$ 的。优化到 $O(n\log ^2n)$ 只需要写个分治+NTT。

---

## 作者：Register_int (赞：1)

本来想当正经推柿子题做的，但是看到划分我 DNA 动了，于是就有了这篇题解。

套路性地期望转计数，将所有情况的总和除以情况数就是期望。发现加的顺序相当于有标号，那好办！无标号先赣出来。根据经典结论，这个方案数相当于 $n$ 个生成函数卷一起的 $x^k$ 次项。可以得到每个生成函数都应该是 $F_i(x)=\sum_j(a_i+j)x^j$ ，而总方案数显然是 $n^k$，则得到：

$$\dfrac1{n^k}[x^k]\prod^n_{i=1}F_i(x)$$

但是有标号，所以 $F_i(x)$ 应该为 $\sum_j\dfrac{a_i+j}{j!}x^j$，答案为：

$$\dfrac{k!}{n^k}[x^k]\prod^n_{i=1}F_i(x)$$

直接卷复杂度爆炸，但是我们可以发现 $F_i$ 中 $a_i$ 是固定的，所以可以提出来一个 $e^x$ 将原式变为 $F_i(x)=e^x(a_i+x)$。那么 $\prod^n_{i=1}F_i(x)=e^{nx}\prod^n_{i=1}(a_i+x)$。后面连乘可以用分治 + NTT 做到 $O(n\log^2n)$，那么重点在于前面。下文设 $[x^t]\prod^n_{i=1}(a_i+x)=f_t$。

$$
\begin{aligned}
&\dfrac{k!}{n^k}[x^k]\prod^n_{i=1}F_i(x)\\
=&\dfrac{k!}{n^k}[x^k]e^{nx}\sum_if_ix^i\\
=&\dfrac{k!}{n^k}\sum^{\min(n,k)}_i\dfrac{n^{k-i}}{(k-i)!}f_i\\
=&\sum^{\min(n,k)}_i\dfrac{k^{\underline{i}}}{n^i}f_i\\
\end{aligned}
$$

撒花，复杂度 $O(n\log^2n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

namespace polynomial {
	// by Register_int
}

using namespace polynomial;

const int MAXN = 1e3 + 10;

int a[MAXN];

inline 
poly<ll> solve(int l, int r) {
	if (l == r) {
		poly<ll> res(2);
		res[0] = a[l], res[1] = 1;
		return res;
	}
	int mid = l + r >> 1, t;
	poly<ll> x = solve(l, mid), y = solve(mid + 1, r); t = x.size() + y.size() - 1;
	x.resize(t), y.resize(t);
	return x * y;
}

int n, k; ll ans, t, x = 1;

int main() {
	scanf("%d%d", &n, &k), t = inv(n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]); poly<ll> f = solve(1, n);
	for (int i = 0; i <= n && i <= k; i++) ans = (ans + f[i] * x % mod) % mod, x = x * t % mod * (k - i) % mod;
	printf("%lld", ans);
}
```

---

## 作者：roger_yrj (赞：0)

## [ABC231G] Balls in Boxes

### 题解

我们记 $b_i$ 为 $i$ 被选中的次数，那么期望得分为

$$\frac{1}{n^k}\sum\limits_{b_1+b_2+\dots+b_n=k}\dbinom{n}{b_1,b_2,\dots,b_n}\prod\limits_{i=1}^n(a_i+b_i)$$

$$=\frac{k!}{n^k}\sum\limits_{b_1,b_2,\dots,b_n}\prod\limits_{i=1}^n\frac{a_i+b_i}{b_i!}$$

考虑构造 EGF：

$$\hat F_i(x)=\sum\limits_{j=0}^{\infin}\frac{a_i+j}{j!}x^j$$

$$=a_i\sum\limits_{j=0}^{\infin}\frac{1}{j!}x^j+\sum\limits_{j=0}^{\infin}\frac{1}{(j-1)!}x^j$$

$$=a_ie^x+xe^x$$

$$=(a_i+x)e^x$$

那么答案转化为：

$$[x^k]\left(\frac{k!}{n^k}\prod\limits_{i=1}^n\hat F_i(x)\right)$$

$$=[x^k]\left(\frac{k!}{n^k}e^{nx}\prod\limits_{i=1}^n(a_i+x)\right)$$

我们把 $\prod\limits_{i=1}^n(a_i+x)$ 展开成 $\prod\limits_{i=0}^{n}c_ix^i$。这一步可以 $O(n^2)$ 暴力做，也可以用一些多项式做法做到 $O(n\log^2n)$。

再把 $e$ 展开，答案为：

$$=\frac{k!}{n^k}\sum\limits_{i=0}^{\min(n,k)}c_i\frac{n^{k-i}}{(k-i)!}$$

$$=\sum\limits_{i=0}^{\min(n,k)}c_ik^{\underline{i}}n^{-i}$$

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1010,mod=998244353;
ll n,k,c[N],a[N];
ll qpow(ll x,ll y){
	ll ret=1;
	while(y){
		if(y&1)ret=ret*x%mod;
		x=x*x%mod;
		y>>=1; 
	}
	return ret;
}
int main(){
	cin>>n>>k;
	c[0]=1;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=n;j;j--)c[j]=(a[i]*c[j]+c[j-1])%mod;
		c[0]=c[0]*a[i]%mod;
	}
	ll ans=0,fac=1,p=1,inv=qpow(n,mod-2);
	for(int i=0;i<=min(n,k);i++){
		ans=(ans+c[i]*fac%mod*p%mod)%mod;
		fac=fac*(k-i)%mod;p=p*inv%mod;
	}
	cout<<ans;
}
```

---

## 作者：yanghanyv (赞：0)

考虑 DP，设 $f_{i,j}$ 表示在前 $i$ 个盒子放 $j$ 次球的所有方案得分之和，得到转移式：
$$
f_{i,j}=\sum\limits_{k=0}^{j}{j \choose k}f_{i-1,k}(a_i+j-k)\\
$$
发现这个转移式简直是为 EGF 量身定制，于是写成 EGF 的形式：
$$
\hat{F_i}(x)=\hat{F_{i-1}}(x)\hat{G_i}(x)\\
\hat{F_0}(x)=\sum\limits_{n=0}^{\infin}[n=0]\frac{x^n}{n!}=1\\
\hat{G_i}(x)=\sum\limits_{n=0}^{\infin}(n+a_i)\frac{x^n}{n!}\\
$$
此时 $\frac{[x^m]\hat{F_n}(x)}{n^m}$ 即为所求。

进行化简，考虑 $\hat{G_i}(x)$ 的封闭形式：
$$
\begin{aligned}
\hat{G_i}(x)
&=\sum\limits_{n=0}^{\infin}(n+a_i)\frac{x^n}{n!}\\
&=\sum\limits_{n=1}^{\infin}\frac{x^n}{(n-1)!}+\sum\limits_{n=0}^{\infin}a_i\frac{x^n}{(n-1)!}\\
&=x\mathrm{e}^x+a_i\mathrm{e}^x\\
&=(x+a_i)\mathrm{e}^x\\
\end{aligned}
$$
于是可以得到：
$$
\hat{F_n}(x)=\prod\limits_{i=1}^{n}\hat{G_i}(x)=\mathrm{e}^{nx}\prod\limits_{i=1}^{n}(x+a_i)\\
$$
暴力算出 $\prod\limits_{i=1}^{n}(x+a_i)$ 的展开式（一个 $n$ 次多项式），设为 $\sum\limits_{i=0}^{n}c_ix^i$，则有：
$$
\begin{aligned}
\hat{F_n}(x)
&=\mathrm{e}^{nx}\sum\limits_{i=0}^{n}c_ix^i\\
&=\sum\limits_{i=0}^{n}c_ix^i\sum\limits_{j=0}^{\infin}n^j\frac{x^j}{j!}\\
&=\sum\limits_{i=0}^{n}\sum\limits_{j=0}^{\infin}\frac{c_in^j(i+j)!}{j!}\frac{x^{i+j}}{(i+j)!}\\
&=\sum\limits_{i=0}^{\infin}\sum\limits_{j=0}^{n}\frac{c_jn^{i-j}i!}{(i-j)!}\frac{x^i}{i!}\\
\end{aligned}
$$
最后得到答案：
$$
ans=\frac{[x^m]\hat{F_{n}}(x)}{n^m}=\sum\limits_{i=0}^{n}\frac{c_i\prod\limits_{j=m-i+1}^{m}j}{n^i}\\
$$
时间复杂度 $\Omicron(n^2)$。

**Bonus：**

如果使用分治 FFT/NTT 计算 $\prod\limits_{i=1}^{n}(x+a_i)$，可以将复杂度降至 $\Omicron(n\log^2{n})$。

---

