# Expected Square Beauty

## 题目描述

给定一个整数数组 $x = [x_1, x_2, \dots, x_n]$。我们定义 $B(x)$ 为将 $x$ 划分为若干个子段，使得每个子段内所有元素都相等的最小划分数。例如，$B([3, 3, 6, 1, 6, 6, 6]) = 4$，一种划分方式为 $[3, 3\ |\ 6\ |\ 1\ |\ 6, 6, 6]$。

现在你并不知道 $x$ 的具体数值，但你知道 $x_i$ 可以是区间 $[l_i, r_i]$ 内的任意整数（$l_i \le r_i$），且每个 $x_i$ 独立且等概率地取值。

请计算 $(B(x))^2$ 的期望值，即 $E((B(x))^2)$。保证该期望值可以表示为最简分数 $\frac{P}{Q}$，请输出 $P \cdot Q^{-1} \bmod 10^9 + 7$。

## 说明/提示

以下是第一个样例所有可能的 $x$ 取值：

- $[1, 1, 1]$：$B(x) = 1$，$B^2(x) = 1$；
- $[1, 1, 2]$：$B(x) = 2$，$B^2(x) = 4$；
- $[1, 1, 3]$：$B(x) = 2$，$B^2(x) = 4$；
- $[1, 2, 1]$：$B(x) = 3$，$B^2(x) = 9$；
- $[1, 2, 2]$：$B(x) = 2$，$B^2(x) = 4$；
- $[1, 2, 3]$：$B(x) = 3$，$B^2(x) = 9$；

所以 $E = \frac{1}{6} (1 + 4 + 4 + 9 + 4 + 9) = \frac{31}{6}$，即 $31 \cdot 6^{-1} = 166666673$。

第二个样例所有可能的 $x$ 取值：

- $[3, 4, 5]$：$B(x) = 3$，$B^2(x) = 9$；
- $[3, 4, 6]$：$B(x) = 3$，$B^2(x) = 9$；
- $[3, 5, 5]$：$B(x) = 2$，$B^2(x) = 4$；
- $[3, 5, 6]$：$B(x) = 3$，$B^2(x) = 9$；
- $[4, 4, 5]$：$B(x) = 2$，$B^2(x) = 4$；
- $[4, 4, 6]$：$B(x) = 2$，$B^2(x) = 4$；
- $[4, 5, 5]$：$B(x) = 2$，$B^2(x) = 4$；
- $[4, 5, 6]$：$B(x) = 3$，$B^2(x) = 9$；

所以 $E = \frac{1}{8} (9 + 9 + 4 + 9 + 4 + 4 + 4 + 9) = \frac{52}{8}$，即 $13 \cdot 2^{-1} = 500000010$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 1 1
1 2 3
```

### 输出

```
166666673
```

## 样例 #2

### 输入

```
3
3 4 5
4 5 6
```

### 输出

```
500000010
```

# 题解

## 作者：whiteqwq (赞：10)

[CF1187F Expected Square Beauty](https://www.luogu.com.cn/problem/CF1187F)解题报告：

[更好的阅读体验](https://www.cnblogs.com/xiaoziyao/p/15226690.html)

## 题意

定义一个序列 $x$ 的美丽值 $B(x)$ 为将 $x$ 划分成所有元素都相等的子段的最小子段数，对于位置 $i$，它的值在 $[l_i,r_i]$ 中随机，且是一个整数，求 $E(B(x)^2)$。

$1\leqslant n\leqslant 2\times 10^5,1\leqslant l_i\leqslant r_i\leqslant 10^9$。

## 分析

套路题，来水一个题解。

首先考虑 $E(B(x))$ 怎么求，实际上它就是 $E(\sum_{i=1}^{n-1}[x_i\ne x_{i+1}])$，根据期望的线性性将它拆开求就好了。

同样地，$E(B(x)^2)$ 可以套路地转化成 $E(\sum_{i=1}^{n-1}\sum_{j=1}^{n-1}[x_i\ne x_{i+1}][x_j\ne x_{j+1}])$，拆开后我们就只要求一对位置对同时满足条件的概率。

分类讨论：（下面为了方便，设 $R(i)=E([x_i\ne x_{i+1}])$。）

- $i=j$，仍然等于 $R(i)$。
- $|i-j|>1$，不难发现两个位置互不影响，直接 $R(i)R(j)$。
- $|i-j|=1$（设 $i=j+1$），考虑容斥一下，那么概率为 $1-E([x_{i-1}=x_i])-E([x_i=x_{i+1}])+E([x_{i-1}=x_i=x_{i+1}])$，后面这个东西可以类似 $R(i)$ 一样计算。

计算上述值非常简单，时间复杂度 $O(n\log mod)$。

这里简单提一下 $R(i)$ 的计算方式吧，我们可以求相等的概率，然后发现每个取值会取遍区间 $i$ 和区间 $i+1$ 的交，我们就直接将交的长度除以两个区间的长度之积就好了。

## 代码

为了方便，可以加入一个位置 $0$，其值在 $[0,0]$ 内随机。

```cpp
#include<stdio.h>
const int maxn=200005,mod=1000000007;
int n,ans,sum;
int l[maxn],r[maxn],R[maxn],len[maxn],invlen[maxn];
inline int min(int a,int b){
	return a<b? a:b;
}
inline int max(int a,int b){
	return a>b? a:b;
}
int ksm(int a,int b){
	int res=1;
	while(b){
		if(b&1)
			res=1ll*res*a%mod;
		a=1ll*a*a%mod,b>>=1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&l[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&r[i]);
	l[0]=r[0]=0,invlen[0]=1;
	for(int i=1;i<=n;i++){
		len[i]=r[i]-l[i]+1,invlen[i]=ksm(len[i],mod-2);
		R[i]=(1-1ll*max(0ll,min(r[i],r[i-1])-max(l[i],l[i-1])+1)*invlen[i]%mod*invlen[i-1]%mod+mod)%mod;
		if(i>2)
			sum=(sum+R[i-2])%mod;
		ans=((ans+R[i])%mod+2ll*sum*R[i]%mod)%mod;
	}
	for(int i=1;i<n;i++){
		int P=(1ll*(1-(1-R[i])-(1-R[i+1]))%mod+mod)%mod,ext=1ll*max(0ll,min(min(r[i-1],r[i+1]),r[i])-max(max(l[i-1],l[i+1]),l[i])+1)*invlen[i-1]%mod*invlen[i+1]%mod*invlen[i]%mod;
		ans=(ans+2ll*(P+ext)%mod)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Mr_Wu (赞：8)

### 题面

[CF1187F](http://codeforces.com/problemset/problem/1187/F)

### 题意

对于一个长度为 $n$ 的数列 $\{x_i\}$，定义 $B(x)$ 为将 $x$ 划分为所有元素都相等的子段的最小子段数。

对 $1\le i\le n$，$x_i$ 是 $[l_i, r_i]$ 中等概率的一个整数。问 $B(x)^2$ 的期望，对 $10^9+7$ 取模。

$n\le 2\times 10^5, 1\le l_i\le r_i\le 10^9$

### 弱化

我们来试着求 $B(x)$ 的期望吧！

好像不会正解，那就先来个 $dp_{i,j}$ 表示 考虑 $[1,i]$，$x_i=j$ 时的最小子段数的期望吧！

那就枚举 $x_{i-1}$ 的值，然后判断是否会多出一个子段就行了对吧。所以有：

$$ \begin{aligned} dp_{i,j}=\frac{1}{r_{i-1}-l_{i-1}+1}\sum_{x=l_{i-1}}^{r_{i-1}} (dp_{i-1,x}+[x\not=j]) \\= \frac{1}{r_{i-1}-l_{i-1}+1}\Bigg(\sum_{x=l_{i-1}}^{r_{i-1}} (dp_{i-1,x}+1)-[l_{i-1}\le j\le r_{i-1}]\Bigg) \end{aligned}$$

那就求和吧：

$$\begin{aligned} \sum_{j=l_i}^{r_i} dp_{i,j}=\frac{r_i-l_i+1}{r_{i-1}-l_{i-1}+1}\Bigg( \sum_{x=l_{i-1}}^{r_{i-1}} dp_{i-1,x}+r_{i-1}-l_{i-1}+1\Bigg) - \frac{|[l_i,r_i]\cup [l_{i-1},r_{i-1}]|}{r_{i-1}-l_{i-1}+1} \end{aligned}$$

唉，我们发现这个式子里有两个东西好像很像呢。令 $f_i=\sum\limits_{j=l_i}^{r_i} dp_{i,j}$，那就有：

$$\begin{aligned} f_i=\frac{r_i-l_i+1}{r_{i-1}-l_{i-1}+1}( f_{i-1}+r_{i-1}-l_{i-1}+1) - \frac{|[l_i,r_i]\cup [l_{i-1},r_{i-1}]|}{r_{i-1}-l_{i-1}+1} \end{aligned} $$

答案是 $\frac{1}{r_n-l_n+1}f_n$，我们可以 $O(n\log n)$ 求这玩意了。

### 题解

那 $B(x)^2$ 怎么办呢？老套路，设 $p_{i,j}$ 为 考虑 $[1,i],x_i=j$ 时的最小子段数平方期望。

那有：

$$p_{i,j}=\frac{1}{r_{i-1}-l_{i-1}+1}\sum_{x=l_{i-1}}^{r_{i-1}} (p_{i-1,x}+2dp_{i-1,x}+1-[x=j]\times (2dp_{i-1,x}+1))$$

然后求和：
$$\sum_{j=l_i}^{r_i} p_{i,j}=\frac{1}{r_{i-1}-l_{i-1}+1}\Bigg( \sum_{x=l_{i-1}}^{r_{i-1}} p_{i-1,x} + 2\sum_{x=l_{i-1}}^{r_{i-1}} dp_{i-1,x} +r_{i-1}-l_{i-1}+1 \Bigg)-\frac{|[l_i,r_i]\cup[l_{i-1},r_{i-1}]|}{r_{i-1}-l_{i-1}+1}-2\sum_{x\in [l_i,r_i]\cup[l_{i-1},r_{i-1}]} dp_{i-1,x}$$

然后令 $g_i=\sum\limits_{x=l_i}^{r_i} p_{i,x}$，就能得到

$$g_i=\frac{g_{i-1}+2f_{i-1}+r_{i-1}-l_{i-1}+1}{r_{i-1}-l_{i-1}+1}-\frac{|[l_i,r_i]\cup[l_{i-1},r_{i-1}]|}{r_{i-1}-l_{i-1}+1}-\sum_{x\in [l_i,r_i]\cup[l_{i-1},r_{i-1}]} dp_{i-1,x}$$

若设 $[l_i,r_i]\cup[l_{i+1},r_{i+1}]=[lc_i,rc_i]$，并设 $h_i=\sum\limits_{x=lc_i}^{rc_i} dp_{i,x}$

可以推出

$$h_i=\frac{rc_i-lc_i+1}{r_{i-1}-l_{i-1}+1}( f_{i-1}+r_{i-1}-l_{i-1}+1) - \frac{|[lc_i,rc_i]\cup [l_{i-1},r_{i-1}]|}{r_{i-1}-l_{i-1}+1}$$

这下，我们有了三个递推式，他们能够完成这道题目。

时间复杂度 $O(n\log n)$。

#### 代码

```cpp
#include <cstdio>

typedef long long ll;
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

template <typename T>
void swap(T& a, T& b) { T t = a; a = b, b = t; }

ll read()
{
    ll ret = 0; char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') ret = ret * 10 + c - '0', c = getchar();
    return ret;
}
const int MAXN = 200005, MOD = 1000000007;
ll pow(ll a, ll b, ll p = MOD)
{
    ll ret = 1;
    while (b)
    {
        if (b & 1) ret = (ret * a) % p;
        a = (a * a) % p, b >>= 1;
    }
    return ret;
}
inline ll inv(ll x) { return pow(x, MOD - 2); }
ll cup(ll l1, ll r1, ll l2, ll r2, ll& lc, ll& rc)
{
    if (l1 > l2) swap(l1, l2), swap(r1, r2);
    if (l2 > r1) return 0;
    lc = l2, rc = min(r1, r2);
    return rc - lc + 1;
}

int N; ll l[MAXN], r[MAXN], f[MAXN], g[MAXN], h[MAXN], ans;
int main()
{
    N = read(); int i; ll lc, rc, len, lc2, rc2, len2;
    for (i = 1; i <= N; ++i) l[i] = read();
    for (i = 1; i <= N; ++i) r[i] = read();
    f[1] = g[1] = r[1] - l[1] + 1, h[1] = cup(l[1], r[1], l[2], r[2], lc, rc);
    for (i = 2; i <= N; ++i)
    {
        len = cup(l[i - 1], r[i - 1], l[i], r[i], lc, rc);
        f[i] = (r[i] - l[i] + 1) * inv(r[i - 1] - l[i - 1] + 1) % MOD * (f[i - 1] + r[i - 1] - l[i - 1] + 1) % MOD;
        f[i] = (f[i] - len * inv(r[i - 1] - l[i - 1] + 1)) % MOD;
        len2 = cup(l[i], r[i], l[i + 1], r[i + 1], lc2, rc2);
        if (len2)
            h[i] = (rc2 - lc2 + 1) * inv(r[i - 1] - l[i - 1] + 1) % MOD * (f[i - 1] + r[i - 1] - l[i - 1] + 1) % MOD, 
            h[i] = (h[i] - cup(l[i - 1], r[i - 1], lc2, rc2, lc, rc) * inv(r[i - 1] - l[i - 1] + 1)) % MOD;
        g[i] = (r[i] - l[i] + 1) * inv(r[i - 1] - l[i - 1] + 1) % MOD * (g[i - 1] + 2 * f[i - 1] + r[i - 1] - l[i - 1] + 1) % MOD;
        g[i] = (g[i] - len * inv(r[i - 1] - l[i - 1] + 1)) % MOD;
        g[i] = (g[i] - 2 * inv(r[i - 1] - l[i - 1] + 1) * h[i - 1]) % MOD;
    }
    ans = g[N] * inv(r[N] - l[N] + 1) % MOD;
    printf("%lld", (ans + MOD) % MOD);
    return 0;
}
```



---

## 作者：y2823774827y (赞：7)

**更好的阅读体验$\Longrightarrow$[My Blog](https://www.cnblogs.com/y2823774827y/p/11125415.html)**
## 题目
[CF1187F Expected Square Beauty](https://www.luogu.org/problemnew/show/CF1187F)
## 做法
$B(x)=\sum\limits_{i=1}^n I_i(x),I_i(x)=\begin{cases}1&x_i≠x_{i-1}\\0&x_i=x_{i-1}\end{cases}$
$E(B(x)^2)=E(\sum\limits_{i=1}^n I_i(x)\sum\limits_{j=1}^n I_j(x))=E(\sum\limits_{i=1}^n\sum\limits_{j=1}^n I_i(x)I_j(x))=\sum\limits_{i=1}^n\sum\limits_{j=1}^n E(I_i(x)I_j(x))$

分类讨论一下$E(I_i(x)I_j(x))$

- $|i-j|>1$，这两个互不影响，则$E(I_i(x)I_j(x))=E(l_i(x))E(l_j(x))$

- $i=j$，因为$l(x)$函数仅为$1$和$0$，故$E(I_i(x)I_j(x))=E(l_i(x))$

- $|i-j|=1$详细讨论一下：
$q_i=P(x_{i-1}=x_i)=E(x_{i-1}=x_i)=max(0,\frac{min(r_{i-1},r_i)-max(l_{i-1},l_i)}{(r_{i-1}-l_{i-1})(r_i-l_i)})$
$E(I_i(x))=1-q_i$
则$E(I_i(x)I_{i+1}(x))=E(x_{i-1}≠x_i\And x_i≠x_{i+1})$
故等于$1-q_i-q_{i+1}+E(x_{i-1}=x_i\And x_i=x_{i+1})$
其中$E(x_{i-1}=x_i\And x_i=x_{i+1})=\frac{min(r_{i-1},r_i,r_{i+1})-max(l_{i-1},l_i,l_{i+1})}{(r_{i-1}-l_{i-1})(r_i-l_i)(r_{i+1}-l_{i+1})})$

可以用$O(n)$算出来
## [Code](https://www.cnblogs.com/y2823774827y/p/11125415.html)

---

## 作者：流水行船CCD (赞：1)

整体 DP 才是真神。

## 思路

由于本题每一个数有值域限制，考虑 DP 记录后效性。

设 $len_i = r_i - l_i + 1$。

设 $f_i(j)$ 表示前 $i$ 个数，最后一个数是 $j$ 的连续段数期望。

设 $g_i(j)$ 表示前 $i$ 个数，最后一个数是 $j$ 的连续段数的平方的期望。

$$
\left\{\begin{aligned}
&f_i(j) = \frac{1}{len_{i-1}} \sum_{k=l_{i-1}}^{r_{i-1}} f_{i-1}(k) + [j \ne k]\\
&\begin{aligned}
g_i(j) &=  \frac{1}{len_{i-1}} \sum_{k=l_{i-1}}^{r_{i-1}} (f_{i-1}(k) + [j \ne k])^2 \\
&= \frac{1}{len_{i-1}} \sum_{k=l_{i-1}}^{r_{i-1}} g_{i-1}(k) + [j \ne k](2 f_{i-1}(k) + 1)
\end{aligned}
\end{aligned}\right.
$$

注意 $f_i(j),g_i(j)$ 仅在 $j \in [l_i,r_i]$ 中有值，其余值均为 $0$，上述转移也仅在 $j \in [l_i,r_i]$ 时成立。

直接做是 $O(nV^2)$ 的，显然很劣，考虑前缀和优化。设 $Sf_i = \sum\limits_j f_i(j)$，$Sg_i = \sum\limits_j g_i(j)$，通过分讨 $k$ 是否可以与当前枚举的 $j$ 相等，上述方程可以优化为：

$$
\begin{aligned}
&f_i(j) = \left\{\begin{aligned}
&\frac{Sf_{i-1}}{len_{i-1}} + 1 \quad \quad \quad \quad \ \ j \in [l_i,r_i] \cap [l_{i-1},r_{i-1}]\\
&\frac{Sf_{i-1}}{len_{i-1}} + \frac{len_{i-1}-1}{len_{i-1}} \ j \in [l_i,r_i], j \notin [l_{i-1},r_{i-1}]
\end{aligned}\right.\\
&g_i(j) = \left\{\begin{aligned}
&\frac{Sg_{i-1}}{len_{i-1}} + \frac{2Sf_{i-1}}{len_{i-1}} + 1 \quad \quad \quad \quad \quad \quad \ \ j \in [l_i,r_i] \cap [l_{i-1},r_{i-1}]\\
&\frac{Sg_{i-1}}{len_{i-1}} + \frac{2Sf_{i-1}-f_{j}}{len_{i-1}} + \frac{len_{i-1}-1}{len_{i-1}} \ j \in [l_i,r_i], j \notin [l_{i-1},r_{i-1}]
\end{aligned}\right.\\
\end{aligned}
$$

那么现在就可以在 $O(nV)$ 的时间中解决。但这并不足够，由于状态较多，考虑整体 DP：

观察到 $f_i$ 最多只有 $3$ 种值：$0,\frac{Sf_{i-1}}{len_{i-1}} + 1,\frac{Sf_{i-1}}{len_{i-1}} + \frac{len_{i-1}-1}{len_{i-1}}$。且 $f_i$ 的值域连续段最多只有 $5$ 个。使用一个类 ODT 的结构将值域连续段存下来可以快速转移 $f_i$。

考虑推广这个思想，由于 $f_i$ 值域连续段个数是常数级别，不难发现 $g_i$ 的值域连续段个数也是常数级别，因此我们不难在常数时间中转移 $g_i$，分讨一下即可。

$O(n \log V)$，瓶颈在于求逆。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define REP(i, l, r) for (int i = l; i <= r; ++i)
#define PER(i, l, r) for (int i = l; i >= r; --i)
#define clean(name) memset(name, 0, sizeof(name))
#define ld cin
#define jyt cout
// #define int long long
const int N = 2e5 + 7;
const int V = 1e9;
const int inf = 1e9 + 7;
const int P = 1e9 + 7;
namespace JoKing {
    inline long long qpow(long long x, long long y) {long long R = 1; for (; y; (x *= x) %= P, y >>= 1ll) if (y & 1ll) (R *= x) %= P; return R;}
    int n;
    struct Range {int l, r, len;} c[N];
    struct Node {int l, r; ll v;};
    vector<Node> f[N], g[N]; ll sumf[N], sumg[N];
    signed main() {
        ld >> n;
        REP(i, 1, n) ld >> c[i].l;
        REP(i, 1, n) ld >> c[i].r, c[i].len = c[i].r - c[i].l + 1;
        // updf(Rt, 1, V, c[1].l, c[1].r, 1);
        f[1].emplace_back((Node) {c[1].l, c[1].r, 1}), g[1].emplace_back((Node) {c[1].l, c[1].r, 1});
        for (auto &o : f[1]) sumf[1] += o.v * (o.r - o.l + 1);
        for (auto &o : g[1]) sumg[1] += o.v * (o.r - o.l + 1);
        REP(i, 2, n) {
            ll Inv = qpow(c[i - 1].len, P - 2), Pri = Inv * (c[i - 1].len - 1) % P, Sf = sumf[i - 1] * Inv % P, Sg = sumg[i - 1] * Inv % P;
            if (max(c[i - 1].l, c[i].l) <= min(c[i - 1].r, c[i].r)) {
                int L = max(c[i - 1].l, c[i].l), R = min(c[i - 1].r, c[i].r);
                f[i].emplace_back((Node) {L, R, (Sf + Pri) % P});
                if (c[i].l < c[i - 1].l) f[i].emplace_back((Node) {c[i].l, c[i - 1].l - 1, (Sf + 1) % P}), g[i].emplace_back((Node) {c[i].l, c[i - 1].l - 1, (Sg + Sf * 2ll + 1) % P});
                if (c[i - 1].r < c[i].r) f[i].emplace_back((Node) {c[i - 1].r + 1, c[i].r, (Sf + 1) % P}), g[i].emplace_back((Node) {c[i - 1].r + 1, c[i].r, (Sg + Sf * 2ll + 1) % P});
                for (auto o : f[i - 1]) {
                    o.l = max(L, o.l), o.r = min(R, o.r);
                    if (o.l <= o.r) g[i].emplace_back((Node) {o.l, o.r, (Sg + (Sf - o.v * Inv % P + P) * 2ll + Pri) % P});
                }
            } else {
                f[i].emplace_back((Node) {c[i].l, c[i].r, (Sf + 1) % P});
                g[i].emplace_back((Node) {c[i].l, c[i].r, (Sg + Sf * 2ll + 1) % P});
            }
            for (auto &o : f[i]) (sumf[i] += o.v * (o.r - o.l + 1)) %= P;
            for (auto &o : g[i]) (sumg[i] += o.v * (o.r - o.l + 1)) %= P;
            // updf(Rt, 1, V, c[i].l, c[i].r, (Sf + 1) % P);
            // updf(Rt, 1, V, max(c[i - 1].l, c[i].l), min(c[i - 1].r, c[i].r), (Sf + Pri) % P);
        }
        jyt << sumg[n] * qpow(c[n].len, P - 2) % P << '\n';
        return 0;
    }
}
signed main() {
#ifdef WYY
    freopen("files/code.in", "r", stdin);
    freopen("files/code.out", "w", stdout);
    freopen("files/code.err", "w", stderr);
#endif
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    JoKing::main(); return 0;
}


```

---

## 作者：λᴉʍ (赞：1)


神仙题Orz

$E(B(x)^2)=E((1+\sum_{i=1}^{n-1}[x_i\neq x_{i+1}])^2)$

$=E(1+\sum_{1\leq i,j\leq n-1,i\neq j}[x_i\neq x_{i+1}][x_j\neq x_{j+1}]+3\sum_{i=1}^{n-1}[x_i\neq x_{i+1}])$

用期望线性性做即可。

注意$\sum_{1\leq i,j\leq n-1,i\neq j}[x_i\neq x_{i+1}][x_j\neq x_{j+1}]$，相邻的两个单独算，否则相互独立，直接乘

https://codeforces.com/contest/1187/submission/56395322


---

## 作者：rainygame (赞：0)

duel 的时候差最后一步没有想出来，后面想一下发现还是挺简单的。

设 $c=\sum\limits_{i=1}^{n-1}[x_i\ne x_{i+1}]$。那么答案就是 $E[(c+1)^2]=E(c^2)+2E(c)+1$，设 $p_i=P(x_i\ne x_{i+1})$，那么 $E(c)=\sum\limits_{i=1}^{n-1}p_i$，难点在求 $E(c^2)$。

注意到 $c^2$ 的组合意义为选出 $i,j$ 使得 $x_i\ne x_{i+1} \wedge x_j \ne x_{j+1}$，所以 $E(c^2)=E(c)+E(\sum\limits_{1\le i,j<n,i\ne j}[x_i\ne x_{i+1}][x_j\ne x_{j+1}])$。对于 $\lvert i-j\rvert>1$ 的情况，因为这个时候 $i,j$ 是独立的，所以 $E([x_i\ne x_{i+1}][x_j\ne x_{j+1}])=p_ip_j$。

对于 $\lvert i-j\rvert=1$，不妨设 $i=j-1$，那么其实就是求 $E(x_i\ne x_{i+1}\ne x_{i+2})$。考虑容斥，可以得到 $E(x_i\ne x_{i+1}\ne x_{i+2})=P(x_i\ne x_{i+1}\ne x_{i+2})=1-P(x_i=x_{i+1})-P(x_{i+1}=x_{i+2})+P(x_i=x_{i+1}=x_{i+2})$，这三项都是好求的，原问题得到解决。

[submission](https://codeforces.com/contest/1187/submission/310698531)

---

