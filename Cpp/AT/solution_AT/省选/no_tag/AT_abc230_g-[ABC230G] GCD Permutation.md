# [ABC230G] GCD Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc230/tasks/abc230_g

<!-- 
$ 1 $ 以上 $ N $ 以下の整数の並び替え $ P=(P_1,P_2,\ldots,P_N) $ が与えられます。
次の条件をみたす整数の組 $ (i,j) $ $ (1\leq\ i\leq\ j\leq\ N) $ の個数を求めてください。

- $ GCD(i,j)\neq\ 1 $ かつ $ GCD(P_i,P_j)\neq\ 1 $

ただし、正整数 $ x $, $ y $ に対して、$ GCD(x,y) $ で $ x $ と $ y $ の最大公約数を表します。
-->$ 1 $ 以上 $ N $ 以下の整数の並び替え $ P=(P_1,P_2,\ldots,P_N) $ が与えられます。

$ 1\leq\ i\leq\ j\leq\ N $ をみたす整数の組 $ (i,j) $ であって、$ GCD(i,j)\neq\ 1 $ かつ $ GCD(P_i,P_j)\neq\ 1 $ をみたすものの個数を求めてください。  
 ただし、正整数 $ x $, $ y $ に対して、$ GCD(x,y) $ で $ x $ と $ y $ の最大公約数を表します。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ (P_1,P_2,\ldots,P_N) $ は $ (1,2,\ldots,N) $ の並び替えである。
- 入力は全て整数である。

### Sample Explanation 1

条件をみたす組は $ (3,3) $, $ (3,6) $, $ (4,4) $, $ (4,6) $, $ (5,5) $, $ (6,6) $ の $ 6 $ つです。 よって、 $ 6 $ を出力します。

## 样例 #1

### 输入

```
6
5 1 3 2 4 6```

### 输出

```
6```

## 样例 #2

### 输入

```
12
1 2 3 4 5 6 7 8 9 10 11 12```

### 输出

```
32```

# 题解

## 作者：Demeanor_Roy (赞：8)

- 一个最暴力的做法。

---

首先容斥为 $\gcd(i,j)=1$ 且 $\gcd(p_i,p_j)=1$ 的对数。

套路莫反，化简式子至：

$$\sum_{x1}\sum_{x2}\mu(x1)\mu(x2)\dfrac{f(x1,x2)(f(x1,x2)+1)}{2}$$

其中 $f(x1,x2)$ 表示下标为 $x1$ 倍数，值为 $x2$ 倍数的元素数。

对于每个 $(i,p_i)$，我们暴力对 $d1 \mid i,d2 \mid p_i$ 的 $f(d1,d2)$ 计数器累加，再暴力计算每个 $(d1,d2)$ 的贡献。

考虑该做法的复杂度，即为：$\sum_{i=1}^{n}d_id_{p_i}$。其中 $d_x$ 表示 $x$ 的因子数。显然该式子在 $p_i=i$ 时取得极值  $\sum\limits_x {d_x}^2$ 。而该值在 $n= 2\times 10^5$ 时仅为 $6 \times 10^7$，卡卡常可以通过。

对于 $\sum\limits_x {d_x}^2$ 具体上界分析可以看[这儿](https://www.luogu.com.cn/discuss/937862)。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
#define ll long long
vector<int> d[N];
unordered_map<int,int> mp[N];
int n,id,v[N],mu[N],phi[N],prime[N];
inline void init()
{
	mu[1]=1;phi[1]=1;
	for(int i=2;i<N;i++)
	{
		if(!v[i]) v[i]=i,mu[i]=-1,phi[i]=i-1,prime[++id]=i;
		for(int j=1;j<=id;j++)
		{
			if(v[i]<prime[j]||i*prime[j]>=N) break;
			v[i*prime[j]]=prime[j];
			mu[i*prime[j]]=(v[i]==prime[j]?0:-mu[i]);
			phi[i*prime[j]]=phi[i]*(v[i]==prime[j]?prime[j]:prime[j]-1);
		}
	}
}
inline ll S(int x){return 1ll*x*(x+1)/2;} 
inline int read()
{
	int x=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x;
}
int main()
{
	init();
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=i) d[j].emplace_back(i);
	ll ans=0,sum=0;
	for(int i=1;i<=n;i++) 
	{
		int w;
		w=read();	
		for(auto x:d[i])
			for(auto y:d[w]) ++mp[x][y]; 
		sum+=phi[i];
	}
	for(int i=1;i<=n;i++) for(auto it:mp[i]) ans+=mu[i]*mu[it.first]*S(it.second);
	printf("%lld",1ll*n*(n+1)/2+ans-sum*2);
	return 0;
}
```

---

## 作者：EuphoricStar (赞：6)

题目可以转化成所有 $\gcd(p_i,p_j) \ne 1$ 的对数减去 $\gcd(i,j) = 1$ 且 $\gcd(p_i,p_j) \ne 1$ 的对数。

可以考虑外面套一层容斥，枚举 $d$，计算下标为 $d$ 的倍数的数中满足 $\gcd(p_i,p_j) \ne 1$ 的 $(i,j)$ 有多少对。就是先算出 $d|\gcd(i,j)$ 的答案，最后容斥得出 $d = \gcd(i,j)$ 的答案。

现在考虑子问题：给定一些数，求 $\gcd(a_i,a_j) \ne 1$ 的 $(i,j)$ 对数。可以用总对数减去 $\gcd(a_i,a_j) = 1$ 的对数。

记 $c_x$ 为 $x$ 在 $a$ 中的出现次数，然后推式子：

$$\sum\limits_{i=1}^n \sum\limits_{j=1}^n [\gcd(a_i,a_j)=1]$$

$$= \sum\limits_{i=1}^n \sum\limits_{j=1}^n c_i c_j [\gcd(i,j)=1]$$

$$= \sum\limits_{i=1}^n \sum\limits_{j=1}^n c_i c_j \sum\limits_{p|i,p|j} \mu(p)$$

$$= \sum\limits_{p=1}^n \mu(p) \sum\limits_{i=1}^{\left\lfloor\frac{n}{p}\right\rfloor}c_{ip} \sum\limits_{j=1}^{\left\lfloor\frac{n}{p}\right\rfloor}c_{jp}$$

$$= \sum\limits_{p=1}^n \mu(p) ( \sum\limits_{i=1}^{\left\lfloor\frac{n}{p}\right\rfloor} c_{ip} )^2$$

考虑每加进来一个数 $x$，答案的变化量。对于每个 $k|x$，记 $b_k$ 表示已经加进来的数中 $k$ 的倍数的数量，答案新增 $\mu(k) \times [(b_k + 1)^2 - b_k^2] = \mu(k) \times (2b_k + 1)$。预处理出因数，动态维护答案即可。

总时间复杂度大约是 $O(n \log n \max\limits_{i=1}^n d(i))$，其中 $d(i)$ 为 $i$ 的因数个数。

[code](https://atcoder.jp/contests/abc230/submissions/36476089)

同类题目：[CF1575G GCD Festival](https://www.luogu.com.cn/problem/CF1575G)

---

## 作者：LiuIR (赞：2)

## 题目大意

[题目传送门](https://www.luogu.com.cn/problem/AT_abc230_g)

给定一个长为 $n$ 的排列 $p$，求有多少对 $1\le i\le j\le n$ 满足 $\gcd(i,j)\not=1\land \gcd(p_i,p_j)\not=1$

$1\le n\le 2\times10^5$。

## 题目分析

容易得到：

$$
\begin{aligned}
ans&=\sum_{i=1}^n\sum_{j=i}^n[\gcd(i,j)\not=1\land \gcd(p_i,p_j)\not=1]\\
&=\frac{1}{2}\left(\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)\not=1\land \gcd(p_i,p_j)\not=1]+\sum_{i=1}^n[\gcd(i,i)\not=1\land \gcd(p_i,p_i)\not=1]\right)
\end{aligned}
$$

于是现在的答案转变为求出

$$
res=\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)\not=1\land \gcd(p_i,p_j)\not=1]
$$

记

$$
\begin{aligned}
A&=\{(i,j)|[gcd(i,j)\not=1]\}\\
B&=\{(i,j)|[gcd(p_i,p_j)\not=1]\}\\
\end{aligned}
$$

那么有

$$
res=\left|A\cap B\right|=\left|U\right|-\left|\overline{A}\right|-\left|\overline{B}\right|+\left|\overline{A}\cap\overline{B}\right|
$$

$\left|U\right|$ 是显然的。于是只需求出 $\left|\overline{A}\right|,\left|\overline{B}\right|,\left|\overline{A}\cap\overline{B}\right|$。

### $\left|\overline{A}\right|$

$$
\begin{aligned}
\left|\overline{A}\right|&=\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=1]\\
&=\sum_{i=1}^n\sum_{j=1}^n\sum_{d|i,d|j}\mu(d)\\
&=\sum_{d=1}^n\mu(d)\left(\sum_{i=1}^n[d|i]\right)^2\\
&=\sum_{d=1}^n\mu(d)\left(\lfloor\frac{n}{d}\rfloor\right)^2
\end{aligned}
$$

### $\left|\overline{B}\right|$

先设 $f(d)=\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(p_{id},p_{jd})=1]$，具体怎么求下文再讲。

那么有 $\left|\overline{B}\right|=f(1)$。

### $\left|\overline{A}\cap\overline{B}\right|$

$$
\begin{aligned}
\left|\overline{A}\cap\overline{B}\right|&=\sum_{i=1}^n\sum_{j=1}^n[\gcd(i,j)=1\land\gcd(p_i,p_j)=1]\\
&=\sum_{i=1}^n\sum_{j=1}^n[gcd(p_i,p_j)=1]\sum_{d|i,d|j}\mu(d)\\
&=\sum_{d=1}^n\mu(d)\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(p_{id},p_{jd})=1]\\
&=\sum_{d=1}^n\mu(d)f(d)
\end{aligned}
$$

### $f(d)$

$$
\begin{aligned}
f(d)&=\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}[\gcd(p_{id},p_{jd})=1]\\
&=\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{t|p_{id},t|p_{jd}}\mu(t)\\
&=\sum_{t=1}^n\mu(t)\left(\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}[d|p_{id}]\right)^2
\end{aligned}
$$

由于 $id$ 的总数是 $O(n\ln n)$ 的，所以可以想到暴力枚举每一个 $id$。那么此时只会对 $p_{id}$ 的因数产生贡献。

若记 $buc_t=\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}[d|p_{id}]$，那么贡献就会从 $\mu(t)buc_t^2$ 变成 $\mu(t)(buc_t+1)^2$。拆开后可以得到贡献增加了 $\mu(t)(2buc_t+1)$。

预处理出因数就可以动态维护答案了。时间复杂度 $O(n\log n\max_{i=1}^nd(i))$。

## 代码

主要代码如下：

``` c++
signed main()
{
    SetIO();
    cin >> n;
    Init(n);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j += i)
            factor[j].eb(i);
    for (int d = 1; d <= n; d++)
    {
        for (int i = d; i <= n; i += d)
            for (int t : factor[a[i]])
            {
                f[d] += mu[t] * (2 * buc[t] + 1);
                buc[t]++;
            }
        for (int i = d; i <= n; i += d)
            for (int t : factor[a[i]])
                buc[t]--;
    }
    ans = 1ll * n * n;
    for (int d = 1; d <= n; d++)
        ans -= mu[d] * (n / d) * (n / d);
    ans -= f[1];
    for (int d = 1; d <= n; d++)
        ans += f[d] * mu[d];
    for (int i = 2; i <= n; i++)if (a[i] != 1)
        ans++;
    cout << ans / 2;
    return 0;
}
```

---

## 作者：robinyqc (赞：1)

轻量级莫反。

看到 $\gcd$ 的数量统计想莫反。莫反标准形式处理的是 $[\gcd(a, b) = 1]$，而本题是 $[\gcd(a, b)\neq 1]$。

所以正难则反，考虑
1. 用总方案数 $\binom n2$，
2. 减去 $[\gcd(i, j) = 1]$ 的 $(i, j)$ 数量，
3. 减去 $[\gcd(p_i, p_j) = 1]$ 的 $(i, j)$ 数量，
4. 最后加上 $[\gcd(i, j) = 1]\wedge [\gcd(p_i, p_j) = 1]$ 的 $(i, j)$ 数量。

注意以上都是算的 $i < j$ 的 $(i, j)$ 对数量，对于 $(i, i)$ 对，易于统计，不赘述了。

对于第二种和第三种情况，因为 $p$ 是排列，所以他们是等价的——根据 $\varphi$ 的定义，都是 $\sum_{i = 2}^n \varphi(i)$ 个 $(i, j)$ 对。但其实你不需要单独筛 $\varphi$，因为第四种情况要算。

重点是第四种情况，化一下式子：

$$
\begin{aligned}
&\sum_{i = 1}^n\sum_{j = i + 1}^n[\gcd(i, j) = 1]\cdot[\gcd(p_i, p_j) = 1]\\
=&\sum_{i = 1}^n\sum_{j = i + 1}^n\left(\sum_{d\mid \gcd(i, j)} \mu(d)\right)\cdot[\gcd(p_i, p_j) = 1]\\
=&\sum_{d = 1}^n \mu(d)\boxed{\sum_{i = 1}^{\left\lfloor\frac nd\right\rfloor}\sum_{j = i + 1}^{\left\lfloor\frac nd\right\rfloor}[\gcd(p_{id}, p_{jd}) = 1]}
\end{aligned}
$$

思考被框起来的式子的含义：$p$ 下标为 $d$ 倍数的子序列中，互质的二元组有多少个。不妨设当前这个子序列为 $q$，长度为 $m = \left\lfloor\frac nd\right\rfloor$，那么（这不和刚刚做的一样嘛）：

$$
\begin{aligned}
&\sum_{i = 1}^{m}\sum_{j = i + 1}^{m}[\gcd(q_{i}, q_{j}) = 1] \\
= &\sum_{k = 1}^n\mu(k)\sum_{i = 1}^{m}\sum_{j = i + 1}^{m}[k\mid q_i]\cdot [k\mid q_j] \\
= &\sum_{k = 1}^n\mu(k) \cdot \binom {q\text{ 中 } k \text{ 的倍数的数量 }}2
\end{aligned}
$$

$k$ 显然不能每次都从 $1$ 枚举到 $n$，不然枚举 $d$ 再枚举 $k$ 复杂度就是 $O(n^2)$ 的了。

但是如果 $q$ 中没有数是 $k$ 的倍数那么 $k$ 不必被枚举。所以 $k$ 就只用遍历 $q$ 中的数的因数构成的集合。整个问题就做完了。如果觉得这里说的有点抽象可以看下面的代码实现。

那么复杂度呢？对于一个下标 $i$ 他会被枚举 $\sigma_0(i)$ 次，每次贡献 $\sigma_0(p_i)$ 的复杂度（$\sigma_0(x)$ 指 $x$ 的因数个数）。所以总复杂度 $O\left[\sum_{i = 1}^n \sigma_0(i)\sigma_0(p_i)\right] = O\left[\sum_{i = 1}^n {\sigma_0}^2(i)\right]$。不管是感觉上还是实际上这都是非常可过的。可以参考 [A061502](https://oeis.org/A061502)。

### 代码实现

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template<typename T> using vec = vector<T>;

signed main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 n;
    cin >> n;

    vec<u32> p(n + 1);
    for (u32 i = 1; i <= n; i++) {
        cin >> p[i];
    }

    // 预处理因数
    vec<vec<u32>> fac(n + 1);
    for (u32 i = 1; i <= n; i++) {
        for (u32 j = i; j <= n; j += i) {
            fac[j].emplace_back(i);
        }
    }

    // 计算 mu
    vec<int> mu(n + 1);
    {
        vec<u32> prime;
        vec<bool> vis(n + 1);
        prime.reserve(n / 15);
        mu[1] = 1;
        for (u32 i = 2; i <= n; i++) {
            if (!vis[i]) {
                mu[i] = -1;
                prime.emplace_back(i);
            }
            for (u32 j: prime) {
                if (i * j > n) break;
                vis[i * j] = true;
                if (i % j == 0) {
                    mu[i * j] = 0;
                    break;
                }
                mu[i * j] = -mu[i];
            }
        }
    }

    // 正式开始计算
    i64 ans = 0;

    // q 中 k 的倍数的数量
    vec<u64> cnt(n + 1);
    // k 需要遍历的集合
    vec<u32> ps;

    // 枚举 d
    for (u32 d = 1; d <= n; d++) {
        // 枚举 d 的倍数处的下标
        for (u32 i = d; i <= n; i += d) {
            // 枚举 p[i] 的因子，加入桶中，并顺便维护 k 需要遍历的集合。
            for (auto j: fac[p[i]]) {
                if ((++cnt[j]) == 1) {
                    ps.emplace_back(j);
                }
            }
        }
        i64 vn = 0;
        // 按照式子计算答案
        for (u32 k: ps) {
            vn += mu[k] * i64(cnt[k] * (cnt[k] - 1) / 2);
            cnt[k] = 0;
        }
        // 注意到 d = 1 时正好算出了情况二和三的答案，所以可以在这里简单处理掉。
        if (d > 1) ans += mu[d] * vn;
        else ans -= vn;
        ps.clear();
    }

    cout << n * i64(n - 1) / 2 + ans + n - 2 + (p[1] == 1) << endl;
    return 0;
}
```

---

## 作者：Phobia (赞：1)

首先注意到 $\gcd\left(x,y\right)\neq1$ 不好，考虑容斥，计算 $\gcd\left(x,y\right)=1$ 的个数。

则原题目转化为求 $\left|\text{总对数}\right|-\left|\gcd\left(i,j\right)=1\right|-\left|\gcd\left(p_i,p_j\right)=1\right|+\left|\gcd\left(i,j\right)=1\land\gcd\left(p_i,p_j\right)=1\right|$

总对数平凡，注意到 $\gcd\left(i,j\right)=1$ 和 $\gcd\left(p_i,p_j\right)=1$ 本质相同，即 $\sum\limits_{i=1}^n\varphi\left(i\right)$，然后二倍一下就转而求

$$\begin{aligned}
\sum\limits_{i=1}^n\sum\limits_{j=1}^n\left[\gcd\left(i,j\right)=1\right]\left[\gcd\left(p_i,p_j\right)=1\right]&=\sum\limits_{d=1}^n\mu\left(d\right)\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j=1}^{\lfloor\frac{n}{d}\rfloor}\left[\gcd\left(p_{id},p_{jd}\right)=1\right]\\
&=\sum\limits_{d=1}^n\mu\left(d\right)\sum\limits_{k=1}^n\mu\left(k\right)\left(\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\left[\left.k\middle| p_{id}\right.\right]\right)^2
\end{aligned}$$

注意到 $p$ 是 $n$ 的一排列，且 $\forall i$ 对答案有贡献的 $d$ 至多有 $\sigma_0\left(i\right)$ 个，即如果 $\forall d$， 在添加 $p_{id}$ 到答案中时枚举 $k\mid p_{id}$ 则时间复杂度为

$$
\begin{aligned}
\sum\limits_{d=1}^n\sum\limits_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sigma_0\left(p_{id}\right)&=\sum\limits_{i=1}^n\sigma_0\left(i\right)\sigma_0\left(p_{id}\right)\\
&\le\sum\limits_{i=1}^n\sigma_0^2\left(i\right)\text{(由排序不等式可得)}\\
&=\frac{1}{\pi^2}n\log^3{n}+\omicron\left(n\log^2{n}\right)\\
&=\mathcal{O}\left(n\log^3{n}\right)
\end{aligned}$$

上述后半部分见 [OEIS A061502](https://oeis.org/A061502)

然后就做完了。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

int read()
{
	int res = 0, ch = getchar();
	for (; !isdigit(ch); ch = getchar())
		;
	for (; isdigit(ch); ch = getchar())
		res = (res << 3) + (res << 1) + (ch & 15);
	return res;
}

typedef long long i64;

const int N = 2e5 + 5;

int n, a[N];

int pri[N], tot, phi[N], mu[N];

vector<int> divisor[N];

void init()
{
	phi[1] = mu[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		if (!phi[i])
			pri[++tot] = i, phi[i] = i - 1, mu[i] = -1;
		for (int j = 1; j <= tot && i * pri[j] <= n; ++j)
		{
			if (i % pri[j] == 0)
			{
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			}
			phi[i * pri[j]] = phi[i] * phi[pri[j]];
			mu[i * pri[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!mu[i])
			continue;
		for (int j = i; j <= n; j += i)
			divisor[j].push_back(i);
	}
}

i64 ans, sum, buc[N];

void update(int x, int v)
{
	sum -= mu[x] * buc[x] * buc[x];
	buc[x] += v;
	sum += mu[x] * buc[x] * buc[x];
}

int main()
{
	n = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	init();;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i; j <= n; j += i)
		{
			for (auto d : divisor[a[j]])
				update(d, 1);
		}
		ans += mu[i] * sum;
		for (int j = i; j <= n; j += i)
		{
			for (auto d : divisor[a[j]])
				update(d, -1);
		}
	}
	ans = ans + (a[1] == 1) >> 1;
	for (int i = 1; i <= n; ++i)
		ans -= phi[i] << 1;
	ans += (i64)n * (n + 1) >> 1;
	printf("%lld\n", ans);
	return 0;
}
~~~

---

## 作者：Register_int (赞：1)

$$
\begin{aligned}
&\sum^n_{i=1}\sum^{i}_{j=1}[\gcd(i,j)\not=1][\gcd(a_i,a_j)\not=1]\\
=&\dfrac12\left(\sum^n_{i=1}\sum^{n}_{j=1}[\gcd(i,j)\not=1][\gcd(a_i,a_j)\not=1]+\sum^n_{i=2}[a_i>1]\right)\\
\end{aligned}
$$
后半部分直接线性。接着，设 $f(d)=\sum^n_{i=1}\sum^{n}_{j=1}[\gcd(i,j)=d][\gcd(a_i,a_j)\not=1]$，则：
$$
\begin{aligned}
&\dfrac12\left(\sum^n_{i=1}\sum^{n}_{j=1}[\gcd(i,j)\not=1][\gcd(a_i,a_j)\not=1]+\sum^n_{i=2}[a_i>1]\right)\\
=&\dfrac12\left(\sum^n_{d=2}f(d)+[a_d>1]\right)\\
\end{aligned}
$$
转化为如何求 $f(d)$。可以枚举下标的倍数 $d$，再扣减 $\gcd(i,j)=2d,3d,\cdots\left\lfloor\dfrac nd\right\rfloor d$ 的情况，得出：
$$f(d)=\sum^{\left\lfloor\frac nd\right\rfloor}_{i=1}\sum^{\left\lfloor\frac nd\right\rfloor}_{j=1}[\gcd(a_{di},a_{dj})\not=1]-\sum^{\left\lfloor\frac nd\right\rfloor}_{i=2}f(di)$$
将 $\sum^{\left\lfloor\frac nd\right\rfloor}_{i=1}\sum^{\left\lfloor\frac nd\right\rfloor}_{j=1}[\gcd(a_{di},a_{dj})\not=1]$ 求出后便可以 $O(n\ln n)$ 容斥，再次转化为求解该式。设 $m=\left\lfloor\dfrac nd\right\rfloor$，$b_i=a_{di}$，$c_i$ 为 $i$ 在 $b$ 中的出现次数，则：
$$
\begin{aligned}
&\sum^{\left\lfloor\frac nd\right\rfloor}_{i=1}\sum^{\left\lfloor\frac nd\right\rfloor}_{j=1}[\gcd(a_{di},a_{dj})\not=1]\\
=&\sum^m_{i=1}\sum^m_{j=1}[\gcd(b_i,b_j)\not=1]\\
=&\ m^2-\sum^m_{i=1}\sum^m_{j=1}[\gcd(b_i,b_j)=1]\\
=&\ m^2-\sum^n_{i=1}\sum^n_{j=1}c_ic_j[\gcd(i,j)=1]\\
=&\ m^2-\sum^n_{i=1}\sum^n_{j=1}c_ic_j\sum_{T|i,T|j}\mu(T)\\
=&\ m^2-\sum^n_{T=1}\mu(T)\sum^{\left\lfloor\frac nT\right\rfloor}_{i=1}c_{Ti}\sum^{\left\lfloor\frac nT\right\rfloor}_{i=j}c_{Tj}\\
=&\ m^2-\sum^n_{T=1}\mu(T)\left(\sum^{\left\lfloor\frac nT\right\rfloor}_{i=1}c_{Ti}\right)\left(\sum^{\left\lfloor\frac nT\right\rfloor}_{j=1}c_{Tj}\right)\\
=&\ m^2-\sum^n_{T=1}\mu(T)\left(\sum^{\left\lfloor\frac nT\right\rfloor}_{i=1}c_{Ti}\right)^2\\
\end{aligned}
$$

然而这样是不行的，单次求值为 $O(n\ln n)$，总复杂度 $O(n^2\ln n)$。我们需要优化。发现平方内的式子实际上是求当前序列中 $T$ 的倍数数量，将其设为 $s_T$。考虑往 $b$ 中加入一个 $x$，则他的所有约数 $T$ 在平方内的贡献都会 $+1$，平方过后即为加上 $2s_T+1$，复杂度降为 $O(n\sqrt n\ln n)$，仍然无法通过。发现值域很小，可以 $O(n\ln n)$ 预处理出每个数的约数，复杂度再次降为 $O(n\tau(n)\ln n)$，可以通过。

~~淦了我一个下午啊呜呜呜~~

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int p[MAXN], mu[MAXN], tot;
bool vis[MAXN];

inline 
void init(int n) {
	mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) p[++tot] = i, mu[i] = -1;
		for (int j = 1; j <= tot; j++) {
			if (i * p[j] > n) break;
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
			mu[i * p[j]] = -mu[i];
		}
	}
}

int n, a[MAXN], c[MAXN], s[MAXN];

vector<int> fac[MAXN];

inline 
ll calc(int d) {
	int m = n / d; ll res = 0;
	for (int i = d; i <= n; i += d) {
		for (auto t : fac[a[i]]) res += mu[t] * (s[t]++ << 1 | 1);
	}
	for (int i = d; i <= n; i += d) {
		for (auto t : fac[a[i]]) s[t]--;
	}
	return (ll)m * m - res;
}

ll f[MAXN], ans;

int main() {
	scanf("%d", &n), init(n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) fac[j].push_back(i);
	}
	for (int i = 2; i <= n; i++) f[i] = calc(i);
	for (int i = n; i > 1; i--) {
		for (int j = i << 1; j <= n; j += i) f[i] -= f[j];
	}
	for (int i = 2; i <= n; i++) ans += f[i] + (a[i] > 1);
	printf("%lld", ans >> 1);
}
```

---

## 作者：Luzhuoyuan (赞：0)

大家好，我不会莫反，我是暴力老哥。

考虑给定序列 $a$ 求 $\gcd(a_i,a_j)\ne 1$ 的 $(i,j)$ 数量，这是容易做的。我们先对于每个值统计出 $\gcd(a_i,a_j)$ 是其倍数的数量，然后枚举倍数容斥一下即可。

我们考虑本题就相当于做两次上面的东西套起来：先枚举一个值 $x$，并计算 $x|\gcd(i,j)$ 的数量，然后容斥。计算这个就是将每个满足 $x|i$ 的 $p_i$ 提出来做上面的东西。

但是直接做跑得很慢。考虑对每个 $x$ 计算的过程。我们先用一个数组 $d$ 记录所有 $x|i$ 的 $p_i$ 的因数 $y$ 并统计每个因数出现次数，之后将 $d$ 排序，从大到小计算对数，然后枚举 $y$ 的倍数并减去倍数的方案数。

我们发现枚举倍数的这部分有两种方法：直接枚举 $y$ 的倍数，或者枚举在 $d$ 中比 $y$ 索引大的位置，并选取其中的倍数。当然两种都无法直接通过。但两者各有优劣，第一种对于较大的 $y$ 运算量很小，而 $y$ 较小时很慢，但第二种中可取的范围总是比较有限。所以考虑每次枚举倍数时选择两种中运算量小的一种。

不会算复杂度，但是没怎么卡常就过了，时间 $3.9\text s$。第二种方法中取模比较慢，调一下参可能更快。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N=2e5+5;
int n,a[N],d[N];
ll f[N],g[N],ans;
basic_string<int> ve[N];
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=2;i<=n;i++)
		for(int j=i;j<=n;j+=i)
			ve[j].pb(i);
	for(int i=2;i<=n;i++){
		int t=0;
		for(int j=i;j<=n;j+=i)
			for(int v:ve[a[j]])
				if(!g[v]++)d[++t]=v;
		sort(d+1,d+t+1);
		for(int j=t;j;j--){
			g[d[j]]=g[d[j]]*(g[d[j]]+1)/2;
			if(n/d[j]<t-j)
				for(int k=d[j]*2;k<=n;k+=d[j])
					g[d[j]]-=g[k];
			else for(int k=j+1;k<=t;k++)
				if(d[k]/d[j]*d[j]==d[k])g[d[j]]-=g[d[k]];
			f[i]+=g[d[j]];
		}
		for(int j=1;j<=t;j++)g[d[j]]=0;
	}
	for(int i=n;i>1;i--){
		for(int j=i*2;j<=n;j+=i)
			f[i]-=f[j];
		ans+=f[i];
	}
	cout<<ans<<'\n';
	return 0;
}
```

（逃

---

## 作者：六楼溜刘 (赞：0)

# [ABC230G] GCD Permutation

[传送门](https://www.luogu.com.cn/problem/AT_abc230_g)

## 题意

- 给定长度为 $n$ 的排列 $a$，求：

    $$
    \sum_{i=1}^n\sum_{j=i}^n[\gcd(i,j)\ne 1\land \gcd(a_i,a_j)\ne 1]
    $$

- 其中中括号是艾佛森括号，若内部表达式为真值为 $1$，否则为 $0$，下同。
- $1\le n\le 2\times 10^5$


## 题解

简单题。

注意到两个 $\gcd$ 同时不为 $1$ 不太好搞，不妨先解决其中一个。

考虑设 $f(k)$ 表示将下标为 $k$ 倍数的数拎出来，所得到的不互质的数对数。

显然直接算 $\sum_{k=2}^nf(k)$ 是不对的，会算重，于是考虑何时会算重。容易发现只要 $k\mid \gcd(i,j)$，那么 $i,j$ 之间的答案就会在 $k$ 处被统计一遍，于是我们希望找到一个容斥系数 $g(i)$，使得对于 $p\ge 2$ 有 $\sum_{k\mid p}^{k\ge 2}g(k)=1$，注意到其实就是 $(g\ast I)(p)-g(1)=1$，一眼瞪出 $g(i)$ 可以取 $-\mu(i)$。于是答案就是 $\sum_{k=2}^n-\mu(k)f(k)$，那么考虑如何计算 $f$。

相当于给定一个长度为 $L=\left\lfloor\frac{n}{k}\right\rfloor$ 的序列 $b$，求出 $\sum_{i=1}^L\sum_{j=i}^L[\gcd(b_i,b_j)\ne 1]=\frac{L(L+1)}{2}-\sum_{i=1}^L\sum_{j=i}^L[\gcd(b_i,b_j)=1]$，于是只看后者，考虑很经典地推一推式子：

$$
\begin{aligned}
&\sum_{i=1}^L\sum_{j=i}^L[\gcd(b_i,b_j)= 1]\\\\
&\sum_{i=1}^L\sum_{j=i}^L\sum_{d\mid \gcd(b_i,b_j)}\mu(d)\\\\
&\sum_{d}\mu(d)\frac{cnt_d(cnt_d+1)}{2}\\\\
\end{aligned}
$$

其中 $cnt_d=\sum_{i=1}^L[d\mid b_i]$，即 $b$ 中 $d$ 倍数的数量。

发现 $cnt_d$ 的总和大致是 $O(L\max\tau(b_i))\approx O(L\sqrt[3]{n})$ 级别的（其中 $\tau$ 表示因数个数），而我们枚举的 $d$ 也只需要枚举 $b$ 的因数。根据经典结论，$\sum L$ 是 $O(n\log n)$ 级别的，于是总复杂度大约是 $O(n\log n\sqrt[3]{n})$，实际上因为 $\tau$ 取满上界的点并不多，应该会略小于这个数。


## code

```cpp
#include<bits/stdc++.h>
#define forup(i,s,e) for(i64 i=(s),E123123123=(e);i<=E123123123;++i)
#define fordown(i,s,e) for(i64 i=(s),E123123123=(e);i>=E123123123;--i)
#define mem(a,b) memset(a,b,sizeof(a))
#ifdef DEBUG
#define msg(args...) fprintf(stderr,args)
#else
#define msg(...) void();
#endif
using namespace std;
using i64=long long;
using pii=pair<i64,i64>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
i64 read(){
    i64 x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const i64 N=2e5+5;
i64 n,a[N],ans;
i64 vv[N],mu[N];
vector<i64> pri;
vector<i64> fct[N];
void init(i64 n){
    mu[1]=1;
    forup(i,2,n){
        if(!vv[i]){
            mu[i]=-1;
            pri.push_back(i);
        }
        for(auto j:pri){
            if(1ll*i*j>n) break;
            if(i%j){
                mu[i*j]=-mu[i];
                vv[i*j]=1;
            }else{
                mu[i*j]=0;
                vv[i*j]=1;
                break;
            }
        }
    }
}
vector<i64> vec;
i64 cnt[N];
i64 work(){
    i64 sz=vec.size();
    i64 res=sz*(sz+1)/2;
    vector<i64> seq;
    for(auto i:vec){
        for(auto j:fct[i]){
            seq.push_back(j);
            ++cnt[j];
        }
    }
    sort(seq.begin(),seq.end());
    seq.erase(unique(seq.begin(),seq.end()),seq.end());
    for(auto i:seq){
        res-=mu[i]*cnt[i]*(cnt[i]+1)/2;
        cnt[i]=0;
    }
    return res;
}
signed main(){
    n=read();
    init(n);
    forup(i,1,n){
        for(i64 j=i;j<=n;j+=i){
            fct[j].push_back(i);
        }
    }
    forup(i,1,n){
        a[i]=read();
    }
    forup(i,2,n){
        if(!mu[i]) continue;
        vec.clear();
        for(i64 j=i;j<=n;j+=i){
            vec.push_back(a[j]);
        }
        ans-=mu[i]*work();
    }
    printf("%lld\n",ans);
}
```

---

## 作者：Feyn (赞：0)

[My blog](https://www.cnblogs.com/Feyn/p/16977678.html)

外面先套一层容斥，然后问题就变成了有一些数，求不互质的数对的数量。正难则反，考虑求互质的数量。记每个数的数量（也就是是否出现过）为 $c$，那么有：

$$
\begin{aligned}
\text{ans}=&\sum\limits_{i=1}\sum\limits_{j=1}\varepsilon(\gcd(i,j))c_ic_j\\
=&\sum\limits_{i,j}c_ic_j\sum\limits_{t|i,t|j}\mu(t)\\
=&\sum\limits_{t}\mu(t)\sum\limits_{t|i,t|j}c_ic_j\\
=&\sum\limits_{t}\mu(t)(\sum\limits_{t|i}c_i)^2
\end{aligned}
$$

考虑对每个 $t$ 求贡献，那么每个新加入的数直接暴力遍历所有的因数更新即可。理论复杂度似乎高于 $O(n\log^2n)$，但容易想到剪枝可以剪去很多无用计算，于是就可以通过了。

```cpp
#include<bits/stdc++.h>
//#define feyn
#define int long long
using namespace std;
const int N=200010;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

int m,a[N];

int mu[N],p[N>>2],cnt;
bool vis[N];
void init(){
	mu[1]=1;
	for(int i=2;i<=m;i++){
		if(vis[i]==false)p[++cnt]=i,mu[i]=-1;
		for(int j=1;p[j]*i<=m;j++){
			vis[i*p[j]]=true;
			if(i%p[j]==0)break;
			mu[i*p[j]]=-mu[i];
		}
	}
}

vector<int>d[N];

int an,nt,num[N],ti[N];
inline void add(int val){
	for(int now:d[val]){
		if(ti[now]^nt)ti[now]=nt,num[now]=0;
		an-=num[now]*num[now]*mu[now];
		num[now]++;
		an+=num[now]*num[now]*mu[now];
	}
	if(val==1)an--;
}
int solve(int wh){
	++nt,an=0;
	for(int i=wh;i<=m;i+=wh)add(a[i]);
	int Num=(m/wh)*(m/wh-1);
	return (Num-an)/2;
}

signed main(){
	
	#ifdef feyn
	freopen("in.txt","r",stdin);
	#endif
	
	read(m);
	for(int i=1;i<=m;i++)read(a[i]);
	init();
	for(int i=1;i<=m;i++){
		if(mu[i]==0)continue;
		for(int j=i;j<=m;j+=i)d[j].push_back(i);
	}
	int ans=0;
	for(int i=2;i<=m;i++){
		if(mu[i]==0)continue;
		ans-=mu[i]*solve(i);
	}
	--ans;
	for(int i=2;i<=m;i++)ans-=a[i]==1;
	printf("%lld\n",ans+m);
	
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

讲种很暴力的做法吧。

## 思路

首先我们先考虑钦定 $x|\gcd(i,j)$，令 $f(x)$ 为满足 $x|\gcd(i,j),\gcd(a_i,a_j)\not=1$ 的方案数，最后做一个 Dirichlet 差分。

考虑怎么计算 $f(x)$，重新钦定 $g(x,y)=x|\gcd(i,j),y=\gcd(a_i,a_j)$ 的 $(i,j)$ 数量。我们可以先对每个 $a_i,x|i$ 扔到桶中，做一遍 Dirichlet 前缀和，得到 $h(x,y)$，令 $h(x,y)=\dfrac{h(x,y)\times (h(x,y)-1)}{2}$，此时 $h(x,y)$ 是 $g(x,y)=x|\gcd(i,j),y|\gcd(a_i,a_j)$ 的 $(i,j)$ 数量，然后做一遍差分即可得到 $g(x,y)$，意义是先考虑所有满足 $x|i,y|a_i$ 的 $i$ 位置，从满足要求的数中任意选择两个然后做一遍差分得到。

此时 $f(x)=\lfloor\frac{n}{x}\rfloor\times(\lfloor\frac{n}{x}\rfloor-1)-g(x,1)$。

考虑复杂度，直接做是 $O(n^2)$ 的，显然不可过，容易发现实质上我们要扔到桶中数的数量是 $O(n\ln n)$（调和级数）的，于是我们可以根号分治，对于 $x\leq \sqrt{n\ln n}$ 进行前缀和/差分，大于等于的直接暴力即可。复杂度是大约 $O(n\ln n\log n+n\log\log n\times\sqrt{n\ln n})$，后者显然已经爆炸，于是我们不能把界限定在 $\sqrt{n\ln n}$，我是定的 $500$，此时前者会比较慢，$\gcd$ 函数有一定常数，需要卡常，我用的做法是判断是否 $2|a_i,2|a_j$，$3|a_i,3|a_j$，$5|a_i,5|a_j$，都不满足再用 $\gcd$。

最终复杂度 $O(n\ln^2 n+n\log\log n\times \sqrt{n})$，其中前者有一定常数（需要 $\gcd$ 的组），后者可以通过 $\max{a_i}$ 来减小常数。实际循环次数大约 $4\times 10^8$。

膜拜 $\texttt{\color{black}z\color{red}ltqwq}$ 快速解法。

## 代码

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
#define double long double
#define mid ((L+R)>>1)
using namespace std;
int prm[200005],tot;
bool isp[200005];
const int mod=998244353;
int f[200005],g[200005];
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
int ok2[200005],ok3[200005],ok5[200005];
signed main(){
	for(int i=1;i<=200000;i++) isp[i]=1;
	for(int i=2;i<=200000;i++){
		if(isp[i]){
			tot++;
			prm[tot]=i;
			for(int j=2;j*i<=200000;j++){
				isp[j*i]=0;
			}
		}
	}
	for(int i=2;i<=200000;i+=2) ok2[i]=1;
	for(int i=3;i<=200000;i+=3) ok3[i]=1;
	for(int i=5;i<=200000;i+=5) ok5[i]=1;
	int n=200000;
	n=read();
	int a[n+1];
	for(int i=1;i<=n;i++){
		a[i]=i;
		a[i]=read();
	}
	for(int i=1;i<=n;i++){
		if(i<=500){
			memset(g,0,sizeof(g));
			for(int j=1;j*i<=n;j++){
				g[a[i*j]]=1;
			}
			for(int k=1;k<=tot;k++){
				for(int j=n/prm[k];j>=1;j--){
					g[j]+=g[j*prm[k]];
				}
			}
			for(int j=1;j<=n;j++) if(g[j]) g[j]=g[j]*(g[j]-1)/2;
			for(int k=1;k<=tot;k++){
				int top=n/prm[k];
				for(int j=1;j<=top;j++){
					g[j]-=g[j*prm[k]];
				}
			}
			f[i]=(n/i)*(n/i-1)/2-g[1];
		}
		else{
			for(int j=1;j*i<=n;j++){
				for(int k=j+1;k*i<=n;k++){
					if(ok2[a[j*i]]&&ok2[a[k*i]]){
						f[i]++; continue;
					}
					if(ok3[a[j*i]]&&ok3[a[k*i]]){
						f[i]++; continue;
					}
					if(ok3[a[j*i]]&&ok3[a[k*i]]){
						f[i]++; continue;
					}
					if(__gcd(a[j*i],a[k*i])!=1){
						f[i]++;
					}
				}
			}
		}
	}
	for(int k=1;k<=tot;k++){
		for(int j=1;j*prm[k]<=n;j++){
			f[j]-=f[j*prm[k]];
		}
	}
	int ans=0;
	for(int j=2;j<=n;j++) ans+=f[j];
	cout<<ans+n-1-(a[1]!=1);
	return 0;
}
```

---

