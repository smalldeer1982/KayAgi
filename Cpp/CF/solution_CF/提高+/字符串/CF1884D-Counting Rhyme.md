# Counting Rhyme

## 题目描述

You are given an array of integers $ a_1, a_2, \ldots, a_n $ .

A pair of integers $ (i, j) $ , such that $ 1 \le i < j \le n $ , is called good, if there does not exist an integer $ k $ ( $ 1 \le k \le n $ ) such that $ a_i $ is divisible by $ a_k $ and $ a_j $ is divisible by $ a_k $ at the same time.

Please, find the number of good pairs.

## 说明/提示

In the first test case, there are no good pairs.

In the second test case, here are all the good pairs: $ (1, 2) $ , $ (2, 3) $ , and $ (2, 4) $ .

## 样例 #1

### 输入

```
6
4
2 4 4 4
4
2 3 4 4
9
6 8 9 4 6 8 9 4 9
9
7 7 4 4 9 9 6 2 9
18
10 18 18 15 14 4 5 6 8 9 10 12 15 16 18 17 13 11
21
12 19 19 18 18 12 2 18 19 12 12 3 12 12 12 18 19 16 18 19 12```

### 输出

```
0
3
26
26
124
82```

# 题解

## 作者：Kreado (赞：15)

[题目传送门](https://codeforces.com/contest/1884/problem/D)。

## 思路

考虑暴力，首先我们能很容易得到一个 $O(n^3)$ 做法。

现在想想怎么优化到 $O(n^2)$，我们枚举 $i,j$，不存在 $k$ 使得 $a_{k}\mid a_i$ 且 $a_k\mid a_j$，也就是不存在 $a_k\mid \gcd(a_i,a_j)$。

由于 $a_i$ 值域很小，不妨记 $lmx_i$ 表示数组 $a$ 中是否存在 $i$ 的因子，存在的话，$lmx_i=0$，否则为 $1$。

那么现在我们要求的就是 $\displaystyle \sum_{i=1}^n \sum_{j=i+1}^n lmx_{\gcd(a_i,a_j)}$。

考虑枚举 $\gcd$，令 $p_k$ 表示数组 $a$ 中有多少组 $(i,j)$ 使得 $\gcd(a_i,a_j)=k$。

那么得到答案为 $\displaystyle \sum_{i=1}^n lmx_i\times p_i$。

显然的，对于 $lmx_i$ 我们可以直接根据值域 $O(n\ln n)$ 做，对于 $p_i$，我们可以按照值域数论容斥做。

数论容斥：令 $g_k$ 表示数组 $a$ 中有多少组 $(i,j)$ 使得 $k\mid \gcd(a_i,a_j)$。

那么有 $p_i=g_i-p_{2i}-p_{3i}-\cdots-p_{ki}(ki\le n)$。

直接做即可，时间复杂度 $O(n\ln n)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=1e6+7;
ll T,n,b[Maxn],lmx[Maxn],a[Maxn],ans,p[Maxn];
int main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);ans=0;
		for(ll i=1;i<=n;i++) scanf("%lld",&a[i]),b[a[i]]++;
		
		for(ll i=1;i<=n;i++)
			for(ll j=i;j<=n;j+=i)
				lmx[j]+=b[i];
		for(ll i=n;i;i--){
			for(ll j=i;j<=n;j+=i) p[i]+=b[j];
			p[i]=(p[i]-1)*p[i]/2;
			for(ll j=i<<1;j<=n;j+=i) p[i]-=p[j];
			
		}
		for(ll i=1;i<=n;i++){
			if(!lmx[i]) ans+=p[i];
		}
		cout<<ans<<endl;
		for(ll i=1;i<=n;i++) b[i]=a[i]=lmx[i]=p[i]=0;
	}
	return 0;
}


```


当然，我应该做复杂了，也许用不到数论容斥（）

---

## 作者：Louis_lxy (赞：4)

感觉难度略微高了。

我们开个桶存每个数，然后考虑 dp。

我们设 $f_i$ 表示 $i$ 作为 $a$ 中某两个数的 $\gcd$。

我们枚举 $i$，然后枚举每个 $i$ 个倍数，统计 $i$ 作为 $a$ 中多少个数的因数，然后组合数学统计答案，注意要剪掉它倍数的答案，因为要剪掉它的倍数的答案，因此需要倒叙统计。

我们只需枚举 $a$ 中的每个数，然后统计答案即可，注意有可能重复，因此计算完一次就要清零。

AC 记录：https://www.luogu.com.cn/record/168707205

---

## 作者：mayike (赞：4)

**好题**，but 准确来说考试时我废了，开始想了会 $k\mid \gcd(a_i,a_j)$ 的情况，即可设 $\zeta(k)$ 表示 $k$ 任意某因数满足某情况（搭配其他条件使用）。

$$ans\gets \binom{n}{2}-\sum _ {i = 1} ^ {n-1} \sum _ {j = i+1} ^ n \bigcup_{k=1}^n (a_k\mid \zeta(\gcd(a_i,a_j)))$$

这里若 $a_k\mid \zeta(\gcd(a_i,a_j))$ 则返回 $1$，反之返回 $0$。

枚举 $k$ 的那一层循环是可以预处理省掉的，然后就不知道如何求 $\gcd(a_i,a_j)$ 了。

随后我换了换方向，想着处理 $a$ 之间的因数。

于是乎得到 $A_1,A_2,A_3,\cdots,A_m$ 都是可以直接整除某些 $a_i$ 且互不为倍数关系的数列。设 $w_i$ 是 $a$ 中数的因数的因数为 $i$ 的数个数（真绕），那么结合**容斥**：

$$ans\gets \binom{n}{2}-(\sum_{i=1}^{m}w_{A_i}-\sum_{i=1}^{m-1}\sum_{j=i+1}^{m}w_{\gcd(A_i, A_j)}+\sum_{i=1}^{m-2}\sum_{j=i+1}^{m-1}\sum_{k=j+1}^{m}w_{\gcd(A_i,A_j,A_k)}-\cdots+(-1)^{m+1}\times w_{\gcd_{i=1}^m A_i})$$

看着就很恶心是吧，然后我就废废了，[code](https://codeforces.com/contest/1884/submission/264105425) 复杂度甚至是 $\mathcal{O}(n\sqrt n)$。
说真的，我真害怕这个循环会把某些必要的东西去掉。

```cpp
for(int i=1;i<=n;i++)
	if(p[i])
		for(int j=i*2;j<=n;j+=i)
			if(p[i]==p[j])w[j]=0;
```

此路不通，考虑折返。突然忆起 [$\mathcal{O}(n\log n)$ 求最大公约数为 $k$ 的个数](https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/#%E5%AE%B9%E6%96%A5%E5%8E%9F%E7%90%86%E6%B1%82%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0%E4%B8%BA-k-%E7%9A%84%E6%95%B0%E5%AF%B9%E4%B8%AA%E6%95%B0)，那困惑不就解决了！

解决了原来第一种方案的问题，那么我们再枚举 $a_k$ 来使某些 $p_{a_k\times q}=0$ 即可。

$$ans\gets\sum_{i=1}^{n}p_i$$

[Acode](https://codeforces.com/contest/1884/submission/264202977)。

---

## 作者：zhlzt (赞：3)

### 题解

这题评 *2100 确实有些虚高了，顶多 *1800，这种套路题就要一眼秒。

设 $f(d)=\begin{cases}0,&\exists\, i\in[1,n]\Rightarrow a_i\mid d\\1,&\text{otherwise.}\end{cases}$，则 Good-pairs 数量为：

$$\sum_{i=1}^{n}\sum_{j=i+1}^n f(\gcd(a_i,a_j))=\sum_{d=1}^n f(d)\sum_{i=1}^n\sum_{j=i+1}^n[\gcd(a_i,a_j)=d]$$

对于 $f(d)$ 和 $\displaystyle\sum_{i=1}^n\displaystyle\sum_{j=i+1}^n[\gcd(a_i,a_j)=d]$ 显然我们可以在 $O(n\ln n)$ 的时间内处理出来。

于是这题就结束了。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int check[maxn],cnt[maxn],a[maxn];
long long dp[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1;i<=n;i++){
			check[i]=1; cnt[i]=dp[i]=0;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i]; cnt[a[i]]++;
		}
		for(int i=1;i<=n;i++){
			if(!cnt[i]) continue;
			for(int j=i;j<=n;j+=i) check[j]=0;
		}
		for(int i=1;i<=n;i++){
			for(int j=(i<<1);j<=n;j+=i) cnt[i]+=cnt[j];
		}
		long long ans=0;
		for(int i=n;i>=1;i--){
			if(!cnt[i]) continue;
			dp[i]=1ll*cnt[i]*(cnt[i]-1)/2;
			for(int j=(i<<1);j<=n;j+=i) dp[i]-=dp[j];
			ans+=check[i]*dp[i];
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：wcyQwQ (赞：2)

打 duel 想了一个莫反做法，很小丑。

记 $c_i$ 表示 $i$ 的出现次数，$f_i = \sum_{j | i} c_j$，那么 $(i, j)$ 是好的数对等价于 $f_{\gcd(i, j)} = 0$，记 $F(x) = [f_x = 0]$,
答案即为
$$
\sum_{i = 1}^n\sum_{j = 1}^n c_ic_jF(\gcd(i, j))
$$
不难发现是经典莫反，可化简为
$$
\sum_{T = 1}^n\left(\sum_{i = 1}^{\lfloor\frac{n}{T}\rfloor} c_{iT}\right)^2\sum_{d | T}\mu(d)F\left(\frac{T}{d}\right)
$$
预处理一下就是 $O(n\ln n)$ 的了。

[Code](https://codeforces.com/contest/1884/submission/232447523)

---

## 作者：Engulf (赞：2)

思路参考官方题解。

由 $a_k | a_i$ 和 $a_k | a_j$ 得到 $a_k | \gcd(a_i, a_j)$，由于值域是 $[1, n]$，考虑枚举最大公约数计算贡献。

设 $g_x$ 为 $\gcd(a_i, a_j) = x$ 的 $(i, j)$ 数量，$c_x$ 为数字 $x$ 的出现次数。

枚举 $x$，计算 $s = \sum\limits_{k = 1}^{\left\lfloor \frac{n}{x} \right\rfloor}c_{kx}$ 即 $c_x + c_{2x} + \cdots$。此时这 $s$ 个数中任意两个都有 $x$ 这个因数，但不一定是最大的，有可能它们的最大公约数是 $2x, 3x\cdots$，所以这里要去重，最终 $g_x = \binom{s}{2} - g_{2x} - g_{3x} -\cdots = \dfrac{s(s-1)}{2}-\sum\limits_{k=1}^{\left\lfloor \frac{n}{x} \right\rfloor} g_{kx}$。

这部分的时间复杂度是 $O(n\log n)$ 的。

若 $c_x \neq 0$，显然所有最大公约数为 $x, 2x, 3x\cdots$ 的对数都不能算进答案，这个也是简单枚举一下即可，时间复杂度仍为 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> cnt(n + 1);
        for (int i = 0; i < n; i++) cin >> a[i], cnt[a[i]]++;

        vector<ll> g(n + 1);
        for (int i = n; i; i--) {
            ll s = 0;
            for (int j = i; j <= n; j += i)
                s += cnt[j];
            g[i] = s * (s - 1) / 2;
            for (int j = 2 * i; j <= n; j += i)
                g[i] -= g[j];
        }

        for (int i = 1; i <= n; i++)
            if (cnt[i])
                for (int j = i; j <= n; j += i)
                    g[j] = 0;

        ll ans = 0;
        for (int i = 1; i <= n; i++) ans += g[i];

        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：xiezheyuan (赞：2)

## 简要题意

给出一个长度为 $n$ 的序列 $a$，定义一个无序二元组 $(i,j)$ 是好的，当且仅当不存在 $k$ 使得 $a_k\mid a_i,a_k\mid a_j$。求好的二元组数量。

$1\leq a_i,\sum n\leq 10^6$

## 思路

想了想就切了本题，但是 AC 后发现思路和 wcyQwQ 几乎一模一样【捂脸】。这篇题解就当是对 wcyQwQ 题解的补充吧。

首先我们转换题意，发现一个二元组 $(i,j)$ 是好的，当且仅当序列 $a$ 中不存在 $\gcd(i,j)$ 的因子。

设 $w_i$ 表示序列 $a$ 中 $i$ 出现次数，也就是 $w_i=\sum_{k=1}^{n}[a_k=i]$。

然后就变成了求下面的式子：

$$
\sum_{i=1}^{n}\sum_{j=1}^{n}\prod_{k\mid a_i,k\mid a_j}[w_k=0]
$$

但是感觉式子里面出现 $a_i$ 这样的式子后续反演会很不方便，考虑利用值域很小这个关键性质。考虑枚举值域中的两个点。

为了方便，我们设 $t_i=\prod_{k\mid i}[w_k=0]$ 也就是序列中是否不存在 $i$ 的因子。

通过乘法原理，就转变成求下面的这个式子：

$$
\sum_{i=1}^{n}\sum_{j=1}^{n}w_iw_jt_{\gcd(i,j)}
$$

套路枚举 $\gcd(i,j)$ 的取值，得：

$$
\sum_{i=1}^{n}\sum_{j=1}^{n}\sum_{d=1}^{n}w_iw_jt_d[\gcd(i,j)=d]
$$

将最大公约数约成 $1$ 得：

$$
\sum_{d=1}^{n}\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}w_{id}w_{jd}t_d[\gcd(i,j)=1]
$$

反演，得：

$$
\sum_{d=1}^{n}\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}w_{id}w_{jd}t_d\sum_{k\mid i,k\mid j}\mu(k)
$$

将 $k$ 提到 $i,j$ 之前枚举得：

$$
\sum_{d=1}^{n}t_d\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}\mu(k)\sum_{i=1}^{\lfloor\frac{n}{dk}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{dk}\rfloor}w_{idk}w_{jdk}
$$

整理求和式得：

$$
\sum_{d=1}^{n}t_d\sum_{k=1}^{\lfloor\frac{n}{d}\rfloor}\mu(k)(\sum_{i=1}^{\lfloor\frac{n}{dk}\rfloor}w_{idk})^2
$$

令 $T=dk$ 得：

$$
\sum_{T=1}^{n}(\sum_{i=1}^{\lfloor\frac{n}{T}\rfloor}w_{iT})^2\sum_{d\mid T}t_d\mu(\frac{T}{d})
$$

观察最终得到得式子，可以发现 $\sum_{i=1}^{\lfloor\frac{n}{T}\rfloor}w_{iT}$ 暴力预处理复杂度是 $O(n\log n)$ 完全可以接受，对于 $t$，显然也可以 $O(n\log n)$ 求，对于后面的那个求和式，是一个狄利克雷卷积的形式，也是可以 $O(n\log n)$ 预处理的。

由于题目要求的是无序对，所以最后答案要除以 $2$。

所以最终时间复杂度 $O(n\log n)$ 完全可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5, M = 1e6;
int pri[N],tot,mu[N],w[N],a[N],n,m,f[N],g[N];
bitset<N> vis, t;

void sieve(){
    mu[1] = 1;
    for(int i=2;i<=M;i++){
        if(!vis[i]) pri[++tot] = i, mu[i] = -1;
        for(int j=1;j<=tot&&i*pri[j]<=M;j++){
			vis[i*pri[j]] = 1;
            if(!(i%pri[j])) break;
            mu[i*pri[j]] = -mu[i];
        }
    }
}

void solve(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    m = *max_element(a + 1, a + n + 1);
    for(int i=1;i<=n;i++) w[a[i]]++;
    for(int i=1;i<=m;i++) t[i] = 1;
    for(int i=1;i<=m;i++){
        for(int j=i;j<=m;j+=i) f[i] += w[j];
        for(int j=i;j<=m;j+=i) t[j] = t[j] && (w[i] == 0);
        for(int j=i;j<=m;j+=i) g[j] += t[i] * mu[j / i];
    }
    int ans = 0;
    for(int T=1;T<=m;T++) ans += f[T] * f[T] * g[T];
    ans>>=1;
    cout<<ans<<'\n';
}

void clear(){
    for(int i=1;i<=m;i++) w[i] = f[i] = t[i] = g[i] = 0;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    sieve();
    int T;cin>>T;
    while(T--) solve(), clear();
    return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：1)

好久没见过这么水的 $\rm div2D$ 了，来水一篇题解。

记 $c_i$ 表示 $i$ 的出现次数，$g_t$ 表示选出 $i,j$ 使得 $t\mid\gcd(i,j)$ 的方案数，有 $\displaystyle g_t=\binom{\sum_{t\mid j}c_j}{2}$。

设 $f_t$ 表示选出 $i,j$ 使得 $t=\gcd(i,j)$ 的方案数，有 $\displaystyle f_t=\sum_{t\mid T}g_T\mu(\frac{T}{t})$。

依题意，一个数对 $(i,j)$ 合法当且仅当不存在 $k$ 使得 $a_k\mid\gcd(a_i,a_j)$。将所有 $a_k$ 的倍数标记为不合法，所有没被标记的数的 $f$ 之和就是答案。

复杂度 $O(n\ln n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000005

inline int read(){
	int x = 0; char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();
	while( ch >= '0' && ch <= '9' ) x = x * 10 + ch - 48,ch = getchar();
	return x;
}

int n,a[MAXN],exi[MAXN],cnt[MAXN];
long long f[MAXN];

inline void solve(){
	n = read(); for( int i = 1 ; i <= n ; i ++ ) exi[i] = 0,cnt[i] = 0,f[i] = 0;
	for( int i = 1 ; i <= n ; i ++ ) a[i] = read(),cnt[a[i]] ++,exi[a[i]] = 1;
	for( int i = 1 ; i <= n ; i ++ )
		if( exi[i] ) for( int j = i ; j <= n ; j += i ) exi[j] = 1;
	for( int g = n ; g >= 1 ; g -- ){
		int cst = 0;
		for( int c = g ; c <= n ; c += g ) cst += cnt[c];
		f[g] = 1ll * cst * ( cst - 1 ) / 2;
		for( int c = 2 * g ; c <= n ; c += g ) f[g] -= f[c];
	}
	long long Ans = 0;
	for( int i = 1 ; i <= n ; i ++ ) if( !exi[i] ) Ans += f[i];
	printf("%lld\n",Ans);
}

signed main(){
	int testcase = read();
	while( testcase -- ) solve();
	return 0;
}
```

---

## 作者：lsj2009 (赞：1)

### Problem

给定序列 $\{a_n\}$，求有多少个 $(i,j)$ 满足 $\nexists k\in[1,n]$ 使得 $a_k|a_i\bigwedge a_k|a_j$。

$1\le a_i\le n\le10^6$。

### Solution

典题（？

考虑记 $f_x=[\nexists k,a_k|x]$，这个东西可以调和级数 $\Theta(n\ln{n})$ 去求。

则题目要求 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n f_{\gcd(a_i,a_j)}$，然后就是经典套路：

$$
\begin{aligned}
 & \sum\limits_{i=1}^n\sum\limits_{j=1}^n f_{\gcd(a_i,a_j)} \\
 & =\sum\limits_{d=1}^n f_d\sum\limits_{i=1}^n\sum\limits_{j=1}^n [\gcd(a_i,a_j)=d] \\
 & =\sum\limits_{d=1}^n f_d\sum\limits_{i=1}^n\sum\limits_{j=1}^n [\gcd(\frac{a_i}{d},\frac{a_j}{d})=1][d|a_i][d|a_j]\\
 & =\sum\limits_{d=1}^n f_d\sum\limits_{i=1}^n\sum\limits_{j=1}^n \varepsilon(\gcd(\frac{a_i}{d},\frac{a_j}{d}))[d|a_i][d|a_j]\\
 & =\sum\limits_{d=1}^n f_d\sum\limits_{i=1}^n\sum\limits_{j=1}^n [d|a_i][d|a_j]\sum\limits_{t|\frac{a_i}{d}\bigwedge t|\frac{a_j}{d}} \mu(t)\\
 & =\sum\limits_{d=1}^n f_d\sum\limits_{t=1}^{\lfloor\frac{n}{d}\rfloor} \mu(t)\sum\limits_{i=1}^n\sum\limits_{j=1}^n [dt|a_i][dt|a_j]\\
 & =\sum\limits_{d=1}^n f_d\sum\limits_{t=1}^{\lfloor\frac{n}{d}\rfloor} \mu(t)(\sum\limits_{i=1}^n[dt|a_i])^2\\
\end{aligned}
$$

最后这个 $\sum$ 也可以 $\Theta(n\ln{n})$ 去预处理，然后最终整个柿子也可以 $\Theta(n\ln{n})$ 去算。

注意题目求的 $(i,j)$ 是无序对，所以最终答案要除以 $2$。

最终复杂度 $\Theta(n\ln{n})$。

### Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=1e6+5,m=1e6;
int f[N],g[N],h[N],a[N];
bool is_prime[N];
int mu[N];
vector<int> prime;
void init() {
	is_prime[1]=true; mu[1]=1;
	rep(i,2,m) {
		if(!is_prime[i])
			prime.push_back(i),mu[i]=-1;
		for(auto x:prime) {
			if(x*i>m)
				break;
			is_prime[x*i]=true;
			if(i%x==0)
				continue;
			mu[i*x]=-mu[i];
		}
	}
}
signed main() {
	init();
	int T;
	scanf("%d",&T);
	while(T--) {
		int n;
		scanf("%d",&n);
		rep(i,1,n)
			f[i]=g[i]=h[i]=0;
		rep(i,1,n) {
			scanf("%d",&a[i]); 
			++h[a[i]];
			if(!f[a[i]]) {
				rep(j,1,n/a[i])
					f[j*a[i]]=1;				
			}
		}
		rep(i,1,n) {
			rep(j,1,n/i)
				g[i]+=h[i*j];
		}
		ll ans=0;
		rep(i,1,n) {
			if(f[i])
				continue;
			rep(j,1,n/i)
				ans+=1ll*mu[j]*g[i*j]*g[i*j];
		}
		printf("%lld\n",ans/2);
	}
    return 0;
}
```

---

## 作者：banned_gutongxing (赞：1)

## 题目思路

因为 $a_k\mid a_i$ 且 $a_k\mid a_j$，所以 $a_k\mid \gcd(a_i,a_j)$。

假设 $f(x)$ 表示 $\gcd(a_i,a_j)=x$ 的对数。

我们发现这个很难求，于是我们在定义一个状态：

设 $g(x)$ 表示 $\gcd(a_i,a_j)\mid y$ 的个数，这个可以直接暴力 $O(n\ln n)$ 求。

于是 $f(x)=\displaystyle \sum_{i}\mu(i)g_{ix}$ 就行。

只需要再看 $x$ 是否合法。同样可以把不合法的筛掉，即 $gcd(a_i,a_j)$ 不能是 $a_k$ 的倍数。$O(n\ln n)$。

结束。

## 代码

```cpp
#include<bits/stdc++.h>
#pragma G++ optimize(2)
#define int long long
using namespace std;
const int MAXN = 1e6+10;
int mu[MAXN+10],prime[MAXN+10];
bitset<MAXN+10> is_prime;
void Euler_sieve(){
	mu[1] = 1;
	for(int i = 2;i<MAXN;i++){
		if(!is_prime[i]){
			prime[++prime[0]] = i;
			mu[i] = -1;
		}
		for(int j = 1;j<=prime[0]&&i*prime[j]<MAXN;j++){
			is_prime[i*prime[j]] = 1;
			if(i%prime[j]==0){
				mu[i*prime[j]] = 0;
				break;
			}else{
				mu[i*prime[j]] = -mu[i];
			}
		}
	}
}
int T,n,a[MAXN+10],g[MAXN+10];
int sum[MAXN+10] = {0};bitset<MAXN+10> vis,be;
signed main(){
	Euler_sieve();
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		vis.reset();be.set();
		for(int i = 1;i<=n;i++) sum[i] = 0;
		for(int i = 1;i<=n;i++){
			scanf("%lld",&a[i]);
			vis[a[i]] = 1;
			sum[a[i]]++;
		}
		int _ = vis._Find_first();
		while(_<=n){
			for(int i = _;i<=n;i+=_){
				be[i] = 0;
			}
			_ = vis._Find_next(_);
		}
		for(int i = 1;i<=n;i++){
			g[i] = 0;
			for(int j = i;j<=n;j+=i){
				g[i] += sum[j];
			}
			g[i] = g[i]*(g[i]-1)/2;
		}
		int ans = 0;
		for(int i = 1;i<=n;i++){
			for(int j = 1;j*i<=n;j++){
				ans += g[i*j]*mu[j]*be[i];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
## tag
`Codeforces`、`数学`、`容斥原理`

---

## 作者：Priestess_SLG (赞：0)

套路题。考虑设函数 $F(i)$：

+ $F(i)=1$，$\exists j\in[1,n]\cap\mathbb{N_+},a_j\mid i$。
+ $F(i)=0$，$\forall j\in[1,n]\cap\mathbb{N_+},a_j\nmid i$。

然后发现 $(i,j)$ 为 `Good-Pairs` 的充要条件是 $F(\gcd(a_i,a_j))=1$。因此答案为：

$$
\sum\limits_{i=1}^n
\sum\limits_{j=i+1}^n
F(\gcd(a_i,a_j))
$$

考虑套路：

$$\sum\limits_{g=1}^n\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n F(\gcd(a_i,a_j))[\gcd(a_i,a_j)=g]$$

怎么变成了 $O(n^3)$？没关系！

$$\sum\limits_{g=1}^n\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n F(g)[\gcd(a_i,a_j)=g]$$

$$\sum\limits_{g=1}^nF(g)\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [\gcd(a_i,a_j)=g]$$

令 $G(g)$ 表示 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [\gcd(a_i,a_j)=g]$ 的值。此时答案为：

$$\sum\limits_{g=1}^nF(g)G(g)$$

问题变为求 $G(g)$ 的值。~~[前几天不是刚做了一个一模一样的题吗](https://www.luogu.com.cn/article/thh7fj72)~~？

于是在调和级数时间复杂度内解决问题（$O(n\log n)$）。

---

## 作者：lyhqwq (赞：0)

# Solution

被数学题薄纱了呜呜呜。

gcd 有关的题考虑枚举 gcd。式子变为 $\sum\limits_{d=1}^n g_d \times f_d$。

$g_d=\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [\gcd(i,j)=d]$

$f_d=[\forall a_k\nmid d]$

令 $cnt_d$ 表示 $d$ 的倍数个数，有 $g_d=\binom{cnt_d}{2}-\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor} g_{i\times d}$。

$f,g$ 均可在 $O(n \ln n)$ 时间内算出。

# Code
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=1e6+5;
int _;
int n;
LL a[N],f[N],g[N],cnt[N],buc[N];
int main(){
    scanf("%d",&_);
    while(_--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) f[i]=g[i]=cnt[i]=buc[i]=0;
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]),buc[a[i]]++;
        for(int i=1;i<=n;i++){
            for(int j=i;j<=n;j+=i){
                if(buc[i]) f[j]=1;
                cnt[i]+=buc[j];
            }
        }
        for(int i=n;i>=1;i--){
            g[i]=cnt[i]*(cnt[i]-1)/2;
            for(int j=2*i;j<=n;j+=i) g[i]-=g[j];
        }
        LL ans=0;
        for(int i=1;i<=n;i++) ans+=(1-f[i])*g[i];
        printf("%lld\n",ans);
    }
    return 0;
}

```

---

## 作者：WaterSun (赞：0)

# 思路

首先可以转化一下题意，发现对于一个好的数对 $(i,j)$ 成立，一定满足无法在 $a$ 中找到一个 $a_k$ 为 $\gcd(i,j)$ 的因子。

不妨设 $dp_i$ 表示满足 $\gcd(a_p,a_q) = i$ 的数对数量，$num_i$ 表示 $i$ 在 $a$ 中出现的次数。

那么令 $t = \sum_{k = 2}^{k \times i \leq n}{num_{k \times i}}$。

显然有：

$$
dp_i = \frac{t \times (t - 1)}{2} - \sum_{k = 2}^{k \times i \leq n}{dp_{k \times i}}
$$

那么同时记录 $vis_i$ 表示在 $a$ 中是否存在 $i$ 的因子，如果没有出现过，则将答案加上 $dp_i$。

这些东西都是可以在一遍埃筛中解决的，时间复杂度为 $\Theta(n \log n)$。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

const int N = 1e6 + 10;
int T,n;
int arr[N],dp[N],num[N];
bool vis[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void solve(){
	int ans = 0;
	n = read();
	for (re int i = 1;i <= n;i++){
		dp[i] = num[i] = 0;
		vis[i] = false;
	}
	for (re int i = 1;i <= n;i++){
		arr[i] = read();
		num[arr[i]]++;
		vis[arr[i]] = true;
	}
	for (re int i = n;i;i--){
		int t = 0;
		for (re int j = i;j <= n;j += i){
			t += num[j];
			dp[i] -= dp[j];
			vis[j] |= vis[i];
		}
		dp[i] += t * (t - 1) / 2;
	}
	for (re int i = 1;i <= n;i++){
		if (!vis[i]) ans += dp[i];
	}
	printf("%lld\n",ans);
}

signed main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

