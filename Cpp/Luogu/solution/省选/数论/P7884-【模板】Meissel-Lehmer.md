# 【模板】Meissel-Lehmer

## 题目描述

给定整数 $n$，求出 $\pi(n)$ 的值。

$\pi(n)$ 表示 $1 \sim n$ 的整数中质数的个数。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^{13}$。

## 样例 #1

### 输入

```
10```

### 输出

```
4```

# 题解

## 作者：渐变色 (赞：15)

[题目传送门](https://www.luogu.com.cn/problem/P7884)


------------
#### 前言

这篇题解提供一个时间复杂度为 $O(\dfrac{n^{\frac{2}{3}}}{\log ^{2}n})$ 的较易实现的方法。

------------
#### 流程
考虑朴素的 DP :

$S(n,a)=S(n,a-1)-S(\dfrac{n}{p_a},a-1)+S(p_{a-1},a-1)$

对于 $p \le n^{\frac{1}{8}}$ ，我们使用以上式子进行转移

对于 $p > n^{\frac{1}{8}}$ ，我们考虑用树状数组维护 k 以下的数。注意到含有小于 $n^{\frac{1}{8}}$ 的素因数的数已被筛去，树状数组只需进行 $O(\dfrac{k}{\log n})$ 次修改，时间复杂度 $O(k)$。

如果我们每次都使用树状数组查询 k 以下的值，时间复杂度将超出我们的预期。于是我们考虑在每一次筛完素数后，将不会再更改的值存储于静态数组中。
这一部分的时间复杂度为 $O(\sum\limits_{i=1}^{n/k}\dfrac{\sqrt{n/i}}{\log n}) = O(\dfrac{n}{\sqrt{k}\log n})$。

事实上，我们没有必要对每个 $\frac{n}{i}$ 的数进行转移，在筛完某个素数 $p$ 后，会影响结果的只有满足最小素因数大于 $p$ 的 $i$ ，我们考虑在朴素 dp 后进行这一优化 。于是这部分的时间复杂度优化为 $O(\dfrac{n}{\sqrt{k}\log ^{2}n})$。

然而我们并没有必要转移 $p$ 至 $\sqrt{n}$，将 $p$ 转移至 $n^{\frac{1}{4}}$ 后可借助容斥得到答案。于是我们再次优化为$O(\dfrac{n\pi(n^{\frac{1}{4}})}{k\log n}) = O(\dfrac{n^{\frac{5}{4}}}{k\log ^{2}n})$。取 $k = O(\dfrac{n^{\frac{5}{8}}}{\log n})$，得 $O(\dfrac{n^{\frac{5}{8}}}{\log n})$ 的时间复杂度。

容斥部分的时间复杂度为 $O(\sum\limits_{n^{\frac{1}{4}} <p\le n^{\frac{1}{3}}}\pi(\sqrt{\dfrac{n}{p}})) = O(\dfrac{n^{\frac{2}{3}}}{\log ^{2}n})$。

因此总体时间复杂度为 $O(\dfrac{n^{\frac{2}{3}}}{\log ^{2}n})$。

------------
#### 实现
代码没做过多优化，以供阅读参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 count_pi(i64 N) {
    if(N <= 1) return 0;
    int v = sqrt(N + 0.5);
    int n_4 = sqrt(v + 0.5);
    int T = min((int)sqrt(n_4) * 2, n_4);
    int K = pow(N, 0.625) / log(N) * 2;
    K = max(K, v);
    K = min<i64>(K, N);
    int B = N / K;
    B = N / (N / B);
    B = min<i64>(N / (N / B), K);

    vector<i64> l(v + 1);
    vector<int> s(K + 1);
    vector<bool> e(K + 1);
    vector<int> w(K + 1);
    for (int i = 1; i <= v; ++i) l[i] = N / i - 1;
    for (int i = 1; i <= v; ++i) s[i] = i - 1;

    const auto div = [] (i64 n, int d) -> int { return double(n) / d; };
    int p;
    for (p = 2; p <= T; ++p) 
        if (s[p] != s[p - 1]) {
            i64 M = N / p;
            int t = v / p, t0 = s[p - 1];
            for (int i = 1; i <= t; ++i) l[i] -= l[i * p] - t0;
            for (int i = t + 1; i <= v; ++i) l[i] -= s[div(M, i)] - t0;
            for (int i = v, j = t; j >= p; --j)
                for (int l = j * p; i >= l; --i)
                    s[i] -= s[j] - t0;
            for (int i = p * p; i <= K; i += p) e[i] = 1;
        }
    e[1] = 1;
    int cnt = 1;
    vector<int> roughs(B + 1);
    for (int i = 1; i <= B; ++i)
        if(!e[i]) roughs[cnt++] = i;
    roughs[cnt] = 0x7fffffff;
    for (int i = 1; i <= K; ++i) w[i] = e[i] + w[i - 1];
    for (int i = 1; i <= K; ++i) s[i] = w[i] - w[i - (i & -i)];

    const auto query = [&] (int x) -> int {
        int sum = x;
        while(x) sum -= s[x], x ^= x & -x;
        return sum;
    };
    const auto add = [&] (int x) -> void {
        e[x] = 1;
        while(x <= K) ++s[x], x += x & -x;
    };
    cnt = 1;
    for (; p <= n_4; ++p) 
        if(!e[p]) {
            i64 q = i64(p) * p, M = N / p;
            while(cnt < q) w[cnt] = query(cnt), cnt++;
            int t1 = B / p, t2 = min<i64>(B, M / q), t0 = query(p - 1);
            int id = 1, i = 1;
            for (; i <= t1; i = roughs[++id]) l[i] -= l[i * p] - t0;
            for (; i <= t2; i = roughs[++id]) l[i] -= query(div(M, i)) - t0;
            for (; i <= B; i = roughs[++id]) l[i] -= w[div(M, i)] - t0;
            for (int i = q; i <= K; i += p)
                if(!e[i]) add(i);
        }
    while(cnt <= v) w[cnt] = query(cnt), cnt++;

    vector<int> primes;
    primes.push_back(1);
    for (int i = 2; i <= v; ++i)
        if(!e[i]) primes.push_back(i);
    l[1] += i64(w[v] + w[n_4] - 1) * (w[v] - w[n_4]) / 2;
    for (int i = w[n_4] + 1; i <= w[B]; ++i) l[1] -= l[primes[i]];
    for (int i = w[B] + 1; i <= w[v]; ++i) l[1] -= query(N / primes[i]);
    for (int i = w[n_4] + 1; i <= w[v]; ++i) {
        int q = primes[i];
        i64 M = N / q;
        int e = w[M / q];
        if (e <= i)  break;
        l[1] += e - i;
        i64 t = 0;
        int m = w[sqrt(M + 0.5)];
        for (int k = i + 1; k <= m; ++k) t += w[div(M, primes[k])];
        l[1] += 2 * t - (i + m) * (m - i);
    }
    return l[1];
}
int main() {
    i64 n;
    cin >> n;
    cout << count_pi(n);
    return 0;
}
```

---

## 作者：Prean (赞：14)

是的，这是一篇使用 min25 筛的题解。。。

本题解参考[command_block大佬的博客](https://www.luogu.com.cn/blog/command-block/new-sieve)，代码是对其在 LOJ 上的提交卡常后写出来的。

ML 板子把数据开到 $ 10^{13} $ 速度还和供题人的 ML 速度差不多快就离谱。。。

这个板子的原理是使用树状数组优化的 min25 筛，在下面会详细讲解。复杂度是 $ O((\frac n {\log n})^{\frac 2 3}) $ 的。

首先有经典 DP：
$$ G(n,k)=G(n,k-1)-G(\frac n {pri_k},k-1)+G(pri_{k-1},k-1) $$
边界条件为：
$$ G(n,0)=n $$
根据积分，可以得到朴素的 DP 是 $ O(\frac {n^{\frac 3 4}} {\log n}) $ 的。接下来尝试使用树状数组维护对于 $ n $ 过小时的 $ G $。

设分治线为 $ B1 $。对 $ B1 $ 一下的所有 $ G $ 使用树状数组维护，对于 $ B1 $ 以上的 $ G $ 使用 DP。

这一部分的复杂度为 $ O(B1\log B1+\frac n {\sqrt{B1}\log n}) $，取 $ B1=\frac {n^{\frac 2 3}} {\log^{\frac 4 3} n} $ 可以得到复杂度为 $ O(\frac {n^{\frac 2 3}} {\log^{\frac 1 3} n}) $。

继续分治，令 $ B2 $ 以下的部分暴力统计。

当 $ B2=\sqrt [6] n $ 时，复杂度为 $ O(n^{\frac 2 3}\log n+\frac n {\sqrt{B1}\log n}+B1) $，取 $ B1=(\frac n {\log n})^{\frac 2 3} $ 可以得到复杂度为 $ O((\frac n {\log n})^{\frac 2 3}) $。

复杂度的具体推导可以看 blog。~~笔者看不懂于是懒得解释直接贺代码了~~
```cpp
//感谢@command_block的板子 
#include<cstdio>
#include<cmath>
const int M=3e7,Lim=8.5e7+10;
typedef unsigned long long ull;
int l2,tot,lim,BIT[Lim];
ull n,g[M],w[M];
double inv[M];
bool e[Lim];
inline ull min(const ull&a,const ull&b){
	return a>b?b:a;
}
inline ull max(const ull&a,const ull&b){
	return a>b?a:b;
}
inline void Add(int x){
	e[x]=1;
	while(x<=lim)++BIT[x],x+=x&-x;
}
inline ull Query(int x){
	ull sum=x;
	while(x)sum-=BIT[x],x^=x&-x;
	return sum;
}
signed main(){
	register int i,j,tl,tl2,tl3;
	register ull t,r,x0;
	scanf("%llu",&n);
	lim=min(max(max((pow(n/log2(n),0.66)),l2=sqrtl(n)+1),10000),n);
	for(i=1;i<=l2;i++)w[i]=i-1,inv[i]=1./i;
	for(tot=1;1ull*lim*tot<n;tot++)g[tot]=n*inv[tot]+1e-6-1;
	--tot;Add(1);
	for(i=2;1ull*i*i<=n;i++){
		if(e[i])continue;
		x0=w[i-1];t=n/i;r=1ull*i*i;
		tl=min(n/r,(ull)tot);tl2=min(tl,n/(1ull*l2*i));tl3=min(tl2,tot/i);
		for(j=1;j<=tl3;++j)g[j]-=g[j*i]-x0;
		for(j=tl3+1;j<=tl2;j++)g[j]-=Query(t*inv[j]+1e-6)-x0;
		for(j=tl2+1;j<=tl;++j)g[j]-=w[int(t*inv[j]+1e-6)]-x0;
		for(j=l2;j>=r;--j)w[j]-=w[int(j*inv[i]+1e-6)]-x0;
		if(1ull*i*i<=lim){
			for(j=i*i;j<=lim;j+=i)if(!e[j])Add(j);
		}
	}
	if(!tot)g[1]=Query(n);
	printf("%llu",g[1]);
}
```

---

## 作者：ケロシ (赞：13)

一道 Meissel-Lehmer 算法的模板题洛谷题解里没有 Meissel-Lehmer，大悲啊。

这里介绍 Meissel-Lehmer 算法。

先线性筛算出前大于等于 $n^\frac{1}{2}$ 个数内的素数和 $\pi(n)$。

然后对于求 $\pi(n)$，考虑对其产生贡献的素数分治。 
考虑对于 $n^\frac{1}{3}$ 分治，先算出 $(n^\frac{1}{3},n]$ 中对于 $n^\frac{1}{3}$ 以内的素数筛不掉的数，暂定一个 dp，$dp_{i,j}$ 表示 $[1,i]$ 中不会被前 $j$ 个素数筛掉的个数。

接下来不难发现，现在筛剩下的 $(n^\frac{1}{3},n]$ 中的数，如果是合数，则其必定为两个大于 $n^\frac{1}{3}$ 的素数的乘积，其他即为素数。

计算这类由两个素数相乘的数的个数很简单，直接考虑枚举小的素数，去计算另外一个素数的方案数即可，假设当前选取了小素数 $p$，则其筛掉的数就是 $[p,\frac{n}{p}]$ 中的素数的个数，即为 $\pi(\frac{n}{p})-\pi(p)+1$。

结合一下上述，可得出 $\pi(n)$ 的递归公式：  
$$
\pi(n)=dp_{n,\pi(n^\frac{1}{3})}-1+\pi(n^\frac{1}{3})
-\sum_{p\in(n^\frac{1}{3},n^\frac{1}{2}]} \pi(\frac{n}{p})-\pi(p)+1
$$    
公式前面减一是因为 $1$ 是筛不掉的，其中 $p$ 为素数。

然后考虑如何求 dp 数组，考虑转移。考虑计算最后一个素数的贡献，发现其贡献是其倍数中没有被前面素数筛掉的数的个数，发现可以再利用 dp 数组，所以转移为 $dp_{i,j}=dp_{i,j-1}-dp_{\frac{i}{p_j},j-1}$，其中 $p_j$ 表示第 $j$ 个素数。

考虑边界情况，显然的是 $dp_{i,0}=i$。但这样还不够优，考虑 $p_j^2\ge i$ 的情况，这时 $[1,i]$ 中的合数全被筛过，只剩下素数，所以值即为 $\max(0,\pi(i)-j+1)$，加一是为了留下 $1$，与前面同步。

这样一个基础的 Meissel-Lehmer 算法原理讲解就完成了。

接下来是实现，对于 dp 数组，可以预处理出一部分，例如 $i\le 1.8 \times 10^6,j\le 60$ 的情况。然后由于这道题空间有限，前面公式里的 $\pi(\frac{n}{p})$ 会超出预处理的范围，这是要继续递归。

由于不断递归了 $\pi(n)$，这份代码的时间复杂度我分析不出来，但是时间复杂度应该在 $O(n^\frac{2}{3})$ 级别，足以通过。

```cpp
const int N = 8e6 + 10;
const int MI = 1.8e6;
const int MJ = 60;
ll n;
int f[MI + 5][MJ + 5];
int p[N / 10], ip[N], g[N], cnt;
void init() {
	FOR(i, 2, N - 1) {
		if(!ip[i]) {
			p[++cnt] = i;
		}
		for(int j = 1; j <= cnt && p[j] * i < N; j++) {
			ip[i * p[j]] = 1;
			if(i % p[j] == 0) {
				break;
			}
		}
	}
	// 警惕！这里的 g 数组表示的 pi(n) 含有 1，是 pi(n)+1
	FOR(i, 1, N - 1) g[i] = g[i - 1] + !ip[i];
	FOR(i, 1, MI) f[i][0] = i;
	FOR(i, 1, MI) FOR(j, 1, MJ)
		f[i][j] = f[i][j - 1] - f[i / p[j]][j - 1];
}
ll dp(ll i, ll j) {
	if(i <= MI && j <= MJ) return f[i][j];
	if(!i || !j) return i;
	if(i < N && 1ll * p[j] * p[j] >= i) return max(0ll, g[i] - j);
	return dp(i, j - 1) - dp(i / p[j], j - 1);
}
ll pi(ll n) {
	if(n < N) return g[n] - 1;
	ll sn = pow(n, 1. / 3);
	ll m = g[sn] - 1;
	ll res = dp(n, m) + m - 1;
	for(m++; 1ll * p[m] * p[m] <= n; m++)
		res -= pi(n / p[m]) - pi(p[m]) + 1; // 继续递归
	return res;
}
```

---

## 作者：SAMSHAWCRAFT (赞：10)


Update：Markdown 挂了，修复一下。

------------

交了两发，上了最优解。说实话，我个人是借鉴了不少 LOJ 最优解 min_25 的[代码](https://loj.ac/s/796720)，最优解第一页上的代码几乎都是 larges,smalls,roughs 什么的（大家都是一个思路，和 min_25 的代码很像）。但是 min_25 本人其实没有解释代码为什么这么写，为什么这个代码就快，所以我猜很多人也只是借鉴了代码实现，却不知道原理，我在这里参照 min_25 大佬的代码，给一个粗浅的解释。

**前置知识**：Eratosthenes 筛法。Eratosthenes 筛法是最简单的筛法之一（代码实现来自 OI-wiki）：

``` cpp
int Eratosthenes(int n) {
  int p = 0;
  for (int i = 0; i <= n; ++i) is_prime[i] = 1;
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      prime[p++] = i;
      if ((long long)i * i <= n) for (int j = i * i; j <= n; j += i)
          is_prime[j] = 0; //(*)
    }
  }
  return p;
}
```

我们只需要知道在标星号的那一行代码执行时有多少个 is_prime 从 true 变为 false 。如果我们可以维护这个值，我们就可以知道从 1 到 n 的素数个数了。据说，这个东西在 Project Euler 上曾经有一个所谓 Lucy DP 的东西可以解决，但是这个不是现在我们想要的。

**定义：** 记 is_prime 为 a，$S(v,p)$ 为  $a_j ( 2\le j\le v)$ 在 $i=p$ 时处理完毕后为 true 的个数。

**讨论：** 如果 $p^2\gt v $，从$i=p-1$ 时开始 $a_j $ 就不再变化，此时 $S(v, p) = S(v, p-1)$，$p$ 不是素数的情况也一样。至于 $p$ 是素数，并且 $p^2\le v$ 的情况比较麻烦，需要仔细思考。对于 $j=p,p+1,p+2,...,\left\lfloor  \frac {v}{p} \right\rfloor$，$a_{pj}$ 都是 false，但小于 $p$ 的素数能筛掉的已经被筛掉了，从而 

$$S(v,p)=S(v,p-1)-(S(\left\lfloor  \frac {v}{p} \right\rfloor,p-1)-\pi(p-1))$$

又 $\pi(n)=S(n,\sqrt n)$，我们考虑根号分治，只对 $v=1,2,3,...,\left\lfloor  \sqrt n \right\rfloor$ 和 $v=\left\lfloor \frac n 1 \right\rfloor,\left\lfloor \frac n 2 \right\rfloor,\left\lfloor \frac n 3 \right\rfloor,...,\left\lfloor \frac n {\sqrt {n}} \right\rfloor$ 的情况维护即可。

在 min_25 的代码中的一些变量解释：

- $\texttt{smalls}[i] = S(i, p)$
- $\texttt{roughs}[i]$：没有被筛掉的第 $i$ 个整数。
  - 其大小由一个变量 $\texttt s$ 维护。
  - 把 1 留下，过筛时使用的素数会消失。
- $\texttt{larges}[i] = S(\lfloor n/\texttt{roughs}[i]\rfloor, p)$
- $\texttt{pc} = \pi(p-1)$
- $\texttt{skip}[i]$：$i$ 如果被筛出来的话就是真的。
  - 但是不更新偶数。

下面是 min_25 的代码，其中如何更新这些变量在代码后面解释：

```cpp
using i64 = long long;
int isqrt(i64 n) {
  return sqrtl(n);
}
__attribute__((target("avx"), optimize("O3", "unroll-loops")))
i64 prime_pi(const i64 N) {
  if (N <= 1) return 0;
  if (N == 2) return 1;
  const int v = isqrt(N);
  int s = (v + 1) / 2;
  vector<int> smalls(s); for (int i = 1; i < s; ++i) smalls[i] = i;
  vector<int> roughs(s); for (int i = 0; i < s; ++i) roughs[i] = 2 * i + 1;
  vector<i64> larges(s); for (int i = 0; i < s; ++i) larges[i] = (N / (2 * i + 1) - 1) / 2;
  vector<bool> skip(v + 1);
  const auto divide = [] (i64 n, i64 d) -> int { return double(n) / d; };
  const auto half = [] (int n) -> int { return (n - 1) >> 1; };
  int pc = 0;
  for (int p = 3; p <= v; p += 2) if (!skip[p]) {
    int q = p * p;
    if (i64(q) * q > N) break;
    skip[p] = true;
    for (int i = q; i <= v; i += 2 * p) skip[i] = true;
    int ns = 0;
    for (int k = 0; k < s; ++k) {
      int i = roughs[k];
      if (skip[i]) continue;
      i64 d = i64(i) * p;
      larges[ns] = larges[k] - (d <= v ? larges[smalls[d >> 1] - pc] : smalls[half(divide(N, d))]) + pc;
      roughs[ns++] = i;
    }
    s = ns;
    for (int i = half(v), j = ((v / p) - 1) | 1; j >= p; j -= 2) {
      int c = smalls[j >> 1] - pc;
      for (int e = (j * p) >> 1; i >= e; --i) smalls[i] -= c;
    }
    ++pc;
  }
  larges[0] += i64(s + 2 * (pc - 1)) * (s - 1) / 2;
  for (int k = 1; k < s; ++k) larges[0] -= larges[k];
  for (int l = 1; l < s; ++l) {
    int q = roughs[l];
    i64 M = N / q;
    int e = smalls[half(M / q)] - pc;
    if (e < l + 1) break;
    i64 t = 0;
    for (int k = l + 1; k <= e; ++k) t += smalls[half(divide(M, roughs[k]))];
    larges[0] += t - i64(e - l) * (pc + l - 1);
  }
  return larges[0] + 1;
}
```

仔细看上面的代码应该能大致了解算法，要是不懂可以看这里我的一些解释：

- roughs 的更新：roughs[..s]是未过筛的整数。ns 是下一个循环中的 s。ns = 0，在 roughs[ns] 中有值的话 ns 就自增。
- larges[smalls[d]-pc] 的含义：smalls[d] - pc 是 “未过筛剩下的整数中 d 是第几个数字?” 的意思。
- smalls[i] 的更新：保持 $j = \frac i p $ 被更新。当 $i \ge pj $ 时，smalls[i] 被更新，它的值被减去 smalls[j] - pc，也就是被减去 smalls[i / p] - pc。

**复杂度：** 分析省略，结论是时间复杂度为 $O(\frac {n^{0.75-\epsilon} }{\log n})$（这里的分子更准确的说是 $n^{0.75}-n^{0.5}$），空间复杂度 $O(\sqrt n)$。

**参考文献：** [えびちゃんの日記](https://rsk0315.hatenablog.com/entry/2021/05/18/015511)，本文主要译自该博客，译者只是稍微添加一些解释，译者日语水平不高，如有错误请指明。希望题解可以通过审核。



---

## 作者：缪凌锴_Mathew (赞：5)

### 前言

这篇题解可能并不是很正经，作者并不会分析时间复杂度，有人会吗？

~~其实是暴力出奇迹~~。

这个做法是我在翻找 [我一年前写的博客](https://www.luogu.com.cn/article/2io2unmf) 时~~想到~~整出来的，跪求大佬优化那篇博客那个算法。

### 做法

注：前面这一段和 [之前的博客](https://www.luogu.com.cn/article/2io2unmf) 相同。

回顾埃氏筛的过程，对于每个质数 $p$，筛掉 $p$ 的倍数。

定义函数 $S(v,p)$ 表示用不超过 $p$ 的质数筛 $1 \sim v$ 后剩余的数的个数（除去 $1$）。

比如 $S(10,3)$，$1 \sim 10$ 内，通过 $2$ 筛去 $4,6,8,10$，通过 $3$ 筛去 $6,9$，除去 $1$ 剩余 $2,3,5,7$。因此 $S(10,3)=4$.

对于 $S(v,p)$

- $p$ 不是质数，$S(v,p)=S(v,p-1)$；

- $p*p>v$，$p$ 不可能再筛任何数，$S(v,p)=S(v,p-1)$；

- $p$ 是质数且 $p*p \le v$，假设 $x=p \times k$ 能被筛掉，则 $p \le k \le v/p$ 且 $k$ 不被不超过 $p-1$ 的质数整除，这样的 $k$ 共有 $S(v/p,p-1)-S(p-1,p-1)$ 个。

于是我们发现一个重要的式子:

$S(v,p)=S(v,p-1)-(S(v/p,p-1)-S(p-1,p-1))$ （$p$ 是质数且 $p \le \sqrt{v}$）

---

到了这一步我们不再沿用之前的 DP 做法，我们直接暴力递归 $S$ 函数，但这显然会超时。考虑预处理优化。

我们发现当 $p^2>v$ 时 $S(v,p)=\pi(v)$，考虑预处理一部分的 $\pi(v)$，这里我预处理了 $v\le5\times10^7$ 的 $\pi(v)$。

然后我们可以预处理一部分比较小的 $S(v,p)$，这里我预处理了 $p\le10^3，v\le 2.5\times10^5$ 的 $S(v,p)$。

然后就过了？？？

### Code

```cpp
#include<map>
#include<set>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<cstdio>
#include<vector>
#include<string>
#include<bitset>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=5e7+10;
const int N=5e7;
const int INF=0x3f3f3f3f;
const long long LINF=0x3f3f3f3f3f3f3f3f;
int cnt=0;
int f[MAXN];
int pr[3001145];
bitset <MAXN> unp;
const int MAXM=2.5e5+10;
const int M=2.5e5;
int tot=0;
int g[170][MAXM];
inline void seive(){
    unp[0]=true;
    unp[1]=true;
    for(int i=2;i*i<=N;i++)
    {
        if(unp[i]){
            continue;
        }
        for(int j=i*i;j<=N;j+=i)
        {
            unp[j]=true;
        }
    }
    for(int i=1;i<=N;i++)
    {
        f[i]=f[i-1];
        if(!unp[i]){
            cnt++;
            pr[cnt]=i;
            f[i]++;
        }
    }
    unp.reset();
    unp[0]=true;
    unp[1]=true;
    for(int i=2;i<=1000;i++)
    {
        if(unp[i]){
            continue;
        }
        tot++;
        for(int j=i*i;j<=M;j+=i)
        {
            unp[j]=true;
        }
        g[tot][0]=0;
        for(int j=1;j<=M;j++)
        {
            g[tot][j]=g[tot][j-1]+!unp[j];
        }
    }
}
long long S(long long n,long long p){
    if(!p){
        return n-1;
    }
    if(n<1ll*pr[p]*pr[p]){
        if(n<=N){
            return f[n];
        }
        else{
            return S(n,p-1);
        }
    }
    if(n<=M){
        return g[p][n];
    }
    return S(n,p-1)-(S(n/pr[p],p-1)-S(pr[p]-1,p-1));
}
signed main(){
    seive();
    long long n;
    scanf("%lld",&n);
    printf("%lld\n",S(n,cnt));
    return 0;
}
```

---

