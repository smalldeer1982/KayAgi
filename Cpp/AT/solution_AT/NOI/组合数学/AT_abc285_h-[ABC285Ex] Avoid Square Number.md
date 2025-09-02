# [ABC285Ex] Avoid Square Number

## 题目描述

给定整数 $N,K$ 和一个长度为 $K$ 的数列 $E$。  
请计算满足以下所有条件的长度为 $N$ 的正整数序列的总数，并将答案对 $10^9+7$ 取模后输出。

- 每个元素都不是完全平方数。
- 所有元素的乘积等于 $\displaystyle\prod_{i=1}^{K} p_i^{E_i}$。

其中，

- $p_i$ 表示从小到大第 $i$ 个质数。
- 对于两个长度相等的正整数序列 $A,B$，如果存在某个整数 $i$ 使得 $A$ 的第 $i$ 项与 $B$ 的第 $i$ 项不同，则 $A$ 与 $B$ 被认为是不同的序列。

## 说明/提示

### 限制条件

- 所有输入均为整数。
- $1 \leq N,K,E_i \leq 10000$

### 样例解释 1

所有元素的乘积为 $72=2^3 \times 3^2$ 的长度为 $3$ 的数列如下：

- $(1,1,72)$ 及其排列（$3$ 种）……$1$ 是完全平方数，不满足条件。
- $(1,2,36)$ 及其排列（$6$ 种）……$1,36$ 是完全平方数，不满足条件。
- $(1,3,24)$ 及其排列（$6$ 种）……$1$ 是完全平方数，不满足条件。
- $(1,4,18)$ 及其排列（$6$ 种）……$1,4$ 是完全平方数，不满足条件。
- $(1,6,12)$ 及其排列（$6$ 种）……$1$ 是完全平方数，不满足条件。
- $(1,8,9)$ 及其排列（$6$ 种）……$1,9$ 是完全平方数，不满足条件。
- $(2,2,18)$ 及其排列（$3$ 种）……满足条件。
- $(2,3,12)$ 及其排列（$6$ 种）……满足条件。
- $(2,4,9)$ 及其排列（$6$ 种）……$4,9$ 是完全平方数，不满足条件。
- $(2,6,6)$ 及其排列（$3$ 种）……满足条件。
- $(3,3,8)$ 及其排列（$3$ 种）……满足条件。
- $(3,4,6)$ 及其排列（$6$ 种）……$4$ 是完全平方数，不满足条件。

因此，满足条件的数列共有 $15$ 个。

### 样例解释 2

请注意，答案需要对 $10^9+7$ 取模。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
3 2```

### 输出

```
15```

## 样例 #2

### 输入

```
285 10
3141 5926 5358 9793 2384 6264 3383 279 5028 8419```

### 输出

```
672860525```

# 题解

## 作者：DaiRuiChen007 (赞：5)

# ABC285Ex 题解



## 思路分析

显然立刻想到容斥，记 $S_i$ 为至少存在 $i$ 个平方数的方案数，那么得到：
$$
\text{Answer}=\sum_{i=0}^n (-1)^i\times \binom ni\times S_i
$$
那么原问题转化为求 $S_i$，$S_i$ 可以转化为对于每个质因数 $p_j$，求出把 $E_j$ 拆成至少 $i$ 个偶数的方案数的总乘积。

考虑一次性处理出对于所有 $E_j$ 的答案，对使用质因子数量建立生成函数，即 $F_i(x)=\sum_{k=0}^\infty x^k\times f_{i,k}$，其中 $f_{i,k}$ 为把 $k$ 拆成至少 $i$ 个偶数的方案数，那么我们知道 $S_i=\prod_{j=1}^n f_{i,E_j}$。

而 $F_i(x)$ 的值也是一个非常经典的问题，推导形过程如下：
$$
\begin{aligned}
F_i(x)
&=(x^0+x^2+x^4+x^6+\cdots)^i\times(x^0+x^1+x^2+x^3+\cdots)^{n-i}\\[2ex]
&=\left(\dfrac{1}{1-x^2}\right)^i\times\left(\dfrac 1{1-x}\right)^{n-i}\\
&=\dfrac{1}{(1-x)^n\times (1+x)^i}
\end{aligned}
$$
注意到我们可以每次暴力卷积计算出 $F_0(x)$，而每次转移 $F_{i}(x)\to F_{i+1}(x)$ 只需要乘上 $(1+x)^{-1}=1-x+x^2-x^3+x^4\cdots$ 就可以得到下一个 $F$。

设 $w=\max_{i}^k\{E_i\}$，那么所有的多项式都只需要在 $\bmod x^{w+1}$ 意义下进行。

注意到乘 $\dfrac 1{1-x}$ 等价于做前缀和，乘 $\dfrac 1{1+x}$ 等价于做前缀差（不等于差分，可以自己推导一下），因此多项式操作的复杂度都是 $\Theta(w)$。

求出 $F_0(x)$ 的复杂度是 $\Theta(nw)$，而接下来依次计算 $F_1(x)\sim F_n(x)$ 的总复杂度也是 $\Theta(nw)$，每次通过 $F_i(x)$ 求 $S_i$ 的复杂度是 $\Theta(k)$，执行 $n$ 次，而容斥的复杂度是 $\Theta(n)$。

综上，时间复杂度为 $\Theta(nw+nk)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e4+1,MOD=1e9+7;
int n,k,E[MAXN],p[MAXN];
inline void sum(vector <int> &F) {
	for(int i=1;i<MAXN;++i) F[i]=(F[i]+F[i-1])%MOD;
}
inline void del(vector <int> &F) {
	for(int i=1;i<MAXN;++i) F[i]=(F[i]+MOD-F[i-1])%MOD;
}
int fac[MAXN],inv[MAXN];
inline int binom(int n,int m) {
	return fac[n]*inv[m]%MOD*inv[n-m]%MOD;
}
inline int ksm(int a,int b,int m=MOD) {
	int ret=1;
	while(b) {
		if(b&1) ret=ret*a%m;
		a=a*a%m;
		b=b>>1;
	}
	return ret;
}
signed main() {
	scanf("%lld%lld",&n,&k);
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i%MOD,inv[i]=ksm(fac[i],MOD-2);
	for(int i=1;i<=k;++i) scanf("%lld",&E[i]);
	vector <int> F(MAXN);
	F[0]=1;
	for(int i=1;i<=n;++i) sum(F);
	for(int i=0;i<=n;++i) {
		p[i]=1;
		for(int j=1;j<=k;++j) p[i]=(p[i]*F[E[j]])%MOD;
		del(F);
	}
	int ans=0;
	for(int i=0,f=1;i<=n;++i,f*=-1) {
		ans=(ans+MOD+f*binom(n,i)*p[i]%MOD)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：3)

## 题意简述
给定两个数 $n,m$ 和一个长度为 $m$ 的数列 $b_i$，计算有多少个 $n \times m$ 矩阵 $A_{i,j}$ 满足
* $\forall i \forall j, A_{i,j} \in \mathbb N$
* $\forall i \exists j, 2 \nmid A_{i,j}$
* $\forall i, \sum\limits_j A_{i,j}=b_i$

## 题解
定义一个序列 $A$ 是**偶**的 $\iff \forall i,2 \mid A_i$，否则这个序列是**奇**的。  
正难则反。  
考虑二项式反演。设 $g(x)$ 是钦定前 $x$ 列都是偶的，剩余的 $n-x$ 列可以是偶也可以是奇的的方案数。设 $f(x)$ 是钦定前 $x$ 列是偶的，剩余 $n-x$ 列是奇的的方案数。  
于是有
$$f(0)=\sum_{i=0}^{n} (-1)^i \binom ni g(i)$$
，而 $g(i)$ 的计算可以用生成函数完成：
$$g(a) = \prod_{i=1}^n [x^{b_i}] \dfrac{1}{(1-x)^{n-a}(1-x^2)^a}$$
，考虑在 $a \to a+1$ 的过程中，生成函数乘上了 $\dfrac{(1-x)}{(1-x^2)}$：
### 乘上 $1-x$
暴力卷积即可。另外地，
$$(1-x)\sum_{i\ge0}a_ix^i=\sum\limits_{i\ge0}(a_i-a_{i-1})x^i$$
，也就是差分。证显。
### 除以 $1-x^2$
首先考虑乘上 $1-x^2$ 的情况：
$$(1-x^2)\sum_{i\ge0}a_ix^i=\sum\limits_{i\ge0}(a_i-a_{i-2})x^i$$
，于是我们的问题变成了：给定数列 $b_i = a_i-a_{i-2}$，求 $a_i$。一位得到 $a_i=a_{i-2}+b_i$。

所以计算 $n$ 个生成函数一共是 $\Theta(n^2)$，预处理组合数即可。

---

## 作者：Register_int (赞：2)

特别鸣谢 @BreakPlus。

设 $f_i$ 为钦定最终方案里前 $i$ 个数是平方数（后续没有限制）的方案数，那么答案如下：

$$\sum^n_{i=0}(-1)^i\dbinom nif_i$$

再考虑计算 $f_i$。可以考虑从所有因子里面拆出来 $i$ 个平方数，剩下的放任自流。由于每种质数间是相互独立的，所以可以单独计算再累加。设将 $k$ 分为至少 $i$ 个偶数，剩下随便分的方案数为 $g_i(k)$，可以得出：

$$f_i=\prod_jg_i(E_j)$$

接着来研究 $g_i$，计算它的生成函数 $G_i(x)=\sum_k g_i(k)x^k$。考察组合意义：

- 前半部分相当于将 $n$ 分为 $m$ 段每段都是偶数的方案数，插板可得 $[n\bmod2=0]\dbinom{\frac n2+m-1}{m-1}=\dfrac1{(1-x^2)^m}[x^n]$
- 后半部分相当于将 $n$ 分为 $m$ 段的方案数，插板可得 $\dbinom{n+m-1}{m-1}=\dfrac1{(1-x)^m}[x^n]$

综上：

$$G_i(x)=\dfrac1{(1-x^2)^i(1-x)^{n-i}}$$

复杂度 $O(n^3)$ 或 $O(n^2\log n)$，无法接受。考虑优化卷积过程：

$$
\begin{aligned}
G_i(x)&=\dfrac1{(1-x^2)^i(1-x)^{n-i}}\\
&=\dfrac1{(1+x)^i(1-x)^i(1-x)^{n-i}}\\
&=\dfrac1{(1+x)^i(1-x)^n}\\

\end{aligned}
$$

其中，$\dfrac1{(1-x)^n}$ 可以直接预处理组合数，而 $\dfrac1{1+x}$ 通过展开为 $\left(\sum_k(-1)^kx^k\right)$ 可以发现是做一次前缀差。那么单次复杂度为 $O(n)$，总复杂度 $O(n^2)$，完结撒花。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e4 + 10;
const int mod = 1e9 + 7;

inline 
ll qpow(ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res = res * b % mod;
		b = b * b % mod, p >>= 1;
	}
	return res;
}

ll fac[MAXN], ifac[MAXN];

inline 
void init(int n) {
	*fac = 1;
	for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	for (int i = n; i; i--) ifac[i - 1] = ifac[i] * i % mod;
}

inline 
ll c(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, m, k, a[MAXN], g[MAXN];

ll ans, res;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]), k = max(k, a[i]);
	init(n + k - 1);
	for (int i = 0; i <= k; i++) g[i] = c(i + n - 1, n - 1);
	for (int i = 0; i <= n; i++) {
		res = 1;
		for (int j = 1; j <= m; j++) res = res * g[a[j]] % mod;
		ans = (ans + (i & 1 ? mod - 1 : 1) * c(n, i) % mod * res % mod) % mod;
		for (int i = 1; i <= k; i++) g[i] = (g[i] + mod - g[i - 1]) % mod;
	}
	printf("%lld", ans);
}
```

---

## 作者：Aysct (赞：2)

很好的题目，使我螺旋升天。

讨论题目要求，容易想到容斥，设 $x_i$ 表示钦定有 $i$ 个元素是完全平方数的方案数，则有答案：

$$
\sum_{i=0}^{n}\begin{pmatrix}n \\ i\end{pmatrix}(-1)^{i}x_i
$$

考虑如何求 $x_i$，显然我们要把每个 $E_j$ 分成至少 $i$ 个偶数。

设这个方案数为 $f_{i,E_j}$，发现它可以很方便的用生成函数表达：

$$
G_i(x) = (1-x^2)^{-i} \times (1-x)^{i - n} = (1+x)^{-i}(1-x)^{-n}
$$

考虑到 $(1-x)^{-1}$ 相当于前缀和，$(1+x)^{-1}$ 相当于前缀差，我们可以在 $O(nw)$ 的时间求出 $G_0$，并通过 $O(w)$ 的时间从 $G_{i-1}$ 转移到 $G_i$，所以总时间复杂度为 $O(nw)$（$w = \max_j(e_j)$）。

在求出 $G_i$ 后，我们可以通过 $O(k)$ 的时间复杂度求出 $x_i$。

总时间复杂度 $O(nw+nk)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define poly vector<int>
const int mod = 1e9 + 7;
using namespace std;
int fpow(int a,int b)
{
    int r = 1;
    while(b)
    {
        if(b & 1)r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r % mod;
}
void presum(poly& f)
{
    for(int i=1,sz=f.size();i<sz;i++)
    {
        f[i] = (f[i] + f[i-1]) % mod;
    }
}
void presub(poly& f)
{
    for(int i=1,sz=f.size();i<sz;i++)
    {
        f[i] = (f[i] - f[i-1] + mod) % mod;
    }
}
int n,k,e[10005],mxe;
int c[10005];
int ans;
poly f;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    for(int i=1;i<=k;i++)
    {
        cin>>e[i];
        mxe = max(mxe,e[i]);
    }
    f.resize(mxe+1);
    f[0] = 1;
    for(int i=1;i<=n;i++)presum(f);
    c[0] = 1;
    for(int i=1;i<=n;i++)
    {
        c[i] = c[i-1] * (n - i + 1) % mod * fpow(i,mod-2) % mod;
    }
    for(int i=0;i<=n;i++)
    {
        int res = c[i];
        if(i & 1)res = mod - res;
        for(int j=1;j<=k;j++)res = res * f[e[j]] % mod;
        ans = (ans + res) % mod;
        presub(f);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：1)

有趣的计数题。

首先考虑容斥，假若钦定 $i$ 个位置为完全平方数，则要计算 $\sum_{i=1}^n {n \choose i} (-1)^i \prod_{j=1}^k \sum_{z=0} {z+i-1 \choose i-1} \times {E_j - 2 \times z + n-i-1 \choose n-i-1}$。

我们希望快速对于一个 $t$ 知道 $\sum_{z=0} {z+i-1 \choose i-1} \times {t - 2 \times z + n-i-1 \choose n-i-1}$ 的值，由于式子比较奇怪，考虑用生成函数来刻画。

不难构造出 $f(x) = (\sum_{z} x^{2 \times z})^i \times (\sum_{z} x^z)^{n-i}$，显然 $f(x)$ 中 $x^t$ 的系数就是我们对于 $t$ 要求的值。

等差数列变形一下可以得到 $f(x) = (1+x)^{-i} \times (1-x)^{-n}$，到这里我就不会做了\ll。

下面的部分求助了伟大的 u 群群 u，考察 $f'(x)$ 得到 $f'(x) = (\frac{n}{1-x} - \frac{i}{1+x}) f(x)$，不妨将 $f(x)$ 先写成幂级数的形式 $f(x) = \sum_{i=0} a_i x^i$，有 $f'(x) = \sum_{i=1} i \times a_i x^{i-1}$，变形 $f'(x),f(x)$ 间的式子得到 $(1-x^2)f'(x)=(n-i)f(x)+(n+i)xf(x)$，考察等式左右两边 $x^i$ 的系数，可以得到 $a_{i+1}$ 与 $a_{i},a_{i-1}$ 间的递推关系，而 $a_0=1,a_1=n-i$，于是可以在 $O(n)$ 的时间复杂度内递推出所有需要的项，故时间复杂度 $O(n^2)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+7;
const int maxn = 1e4+114;
int fac[maxn<<1],inv[maxn<<1];
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a;
    int res=qpow(a,b/2);
    res=res*res%mod;
    if(b%2==1) res=res*a%mod;
    return res;
}
int n;
int C(int n,int m){
    if(m>n) return 0;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
int f[maxn];
int E[maxn],k;
signed main(){
    cin>>n>>k;
    for(int i=1;i<=k;i++) cin>>E[i];
    fac[0]=inv[0]=1;
    int res=1;
    for(int i=1;i<(maxn<<1);i++) fac[i]=fac[i-1]*i%mod,inv[i]=qpow(fac[i],mod-2);
    for(int j=1;j<=k;j++){
        res=res*C(E[j]+n-1,n-1)%mod;
    }  
    for(int i=1;i<=n;i++){
        f[0]=1;
        f[1]=n-i;
        for(int j=2;j<maxn;j++) f[j]=((n-i)*f[j-1]%mod+(n+i+j-2)*f[j-2]%mod)%mod*inv[j]%mod*fac[j-1]%mod;
        int g=1;
        for(int j=1;j<=k;j++) g=g*f[E[j]]%mod;
        res=(res+C(n,i)*g%mod*(i%2==1?mod-1:1)%mod)%mod;
    }
    cout<<res<<"\n";
}
```

---

## 作者：zhouyuhang (赞：1)

首先 $O(n^3)$ 是简单的，考虑二项式反演将问题转化为钦定 $k$ 个完全平方数，然后对于每一个的 $p_i^{e_i}$ 单独考虑，其答案为 $\sum_{j=0}^{e_i/2}\binom{s+k-1}{k-1}\binom{e_i-2s+n-k-1}{n-k-1}$。由于这些质因子之间是相互独立的，因此将它们的答案乘起来即为钦定 $k$ 个平方数的答案。

优化的突破口在于那个很长的式子的 GF 意义是 

$$[x^{e_i}]\frac{1}{(1-x^2)^k(1-x)^{n-k}}$$

注意到，上述做法之所以慢是因为每次都算了 $n$ 遍卷积的单项，但是其实GF 本身是可以递推的。注意到

$$\frac{1}{(1-x^2)^k(1-x)^{n-k}}$$
$$=\frac{1}{(1-x^2)^{k-1}(1-x)^{n-k+1}}\cdot\frac{1-x}{1-x^2}$$
$$=\frac{1}{(1-x^2)^{k-1}(1-x)^{n-k+1}}\cdot\frac{1}{1+x}$$
$$=\frac{1}{(1-x^2)^{k-1}(1-x)^{n-k+1}}\cdot\left(\sum_{i=0}^{\infty}(-1)^ix^i\right)$$

至于一个东西卷上 $\sum_{i=0}^{\infty}(-1)^ix^i$，显然无需 NTT，显然有 $f'_i=f_i-f'_{i-1}$，因此也是线性的。那么总复杂度就变成了 $O(n^2)$。

---

