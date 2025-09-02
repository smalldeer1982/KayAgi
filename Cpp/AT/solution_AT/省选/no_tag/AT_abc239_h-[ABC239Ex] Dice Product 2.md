# [ABC239Ex] Dice Product 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc239/tasks/abc239_h

すぬけ君は $ 1 $ 以上 $ N $ 以下の整数が等確率で出るサイコロと整数 $ 1 $ を持っています。  
 すぬけ君は持っている数が $ M $ 以下である間、次の操作を繰り返します。

- サイコロを振り、出た目を $ x $ とする。持っている数に $ x $ を掛ける。

操作を終了するまでにすぬけ君がサイコロを振った回数の期待値を $ \text{mod\ }\ 10^9+7 $ で求めてください。

 期待値 $ \pmod{10^9+7} $ の定義 求める期待値は必ず有理数になることが証明できます。また、この問題の制約のもとでは、その値を既約分数 $ \frac{P}{Q} $ で表した時、$ Q\ \not\equiv\ 0\ \pmod{10^9+7} $ となることも証明できます。よって、$ R\ \times\ Q\ \equiv\ P\ \pmod{10^9+7},\ 0\ \leq\ R\ \lt\ 10^9+7 $ を満たす整数 $ R $ が一意に定まります。 この $ R $ を答えてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^9 $
- $ 1\ \leq\ M\ \leq\ 10^9 $

### Sample Explanation 1

答えはサイコロで $ 2 $ が出るまでにサイコロを振る回数の期待値になります。よって $ 2 $ を出力します。

### Sample Explanation 2

答えはサイコロで $ 2 $ が $ 6 $ 回出るまでにサイコロを振る回数の期待値になります。よって $ 12 $ を出力します。

### Sample Explanation 3

答えは $ \frac{9}{4} $ です。$ 4\ \times\ 250000004\ \equiv\ 9\ \pmod{10^9+7} $ なので $ 250000004 $ を出力します。 $ \bf{10^9\ +\ 7\ =\ 1000000007} $ で $ \mathrm{mod} $ を取る必要があるのに注意してください。

## 样例 #1

### 输入

```
2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
2 39```

### 输出

```
12```

## 样例 #3

### 输入

```
3 2```

### 输出

```
250000004```

## 样例 #4

### 输入

```
2392 39239```

### 输出

```
984914531```

## 样例 #5

### 输入

```
1000000000 1000000000```

### 输出

```
776759630```

# 题解

## 作者：Pengzt (赞：6)

[ABC239H](https://www.luogu.com.cn/problem/AT_abc239_h)

简单题。

令 $f_i$ 表示乘到 $\ge i$ 的期望。

容易得到 $f_i=\dfrac{\sum\limits_{j=1}^{n}f_{\lceil\frac{i}{j}\rceil}}{n}$。

将 $f_i$ 移到同一边，去掉系数，有 $f_i=\dfrac{n\sum\limits_{j=2}^{n}f_{\lceil\frac{i}{j}\rceil}}{n-1}$。

提出 $\frac{n-1}{n}$ 后显然可以使用数论分块计算后面的一部分。由于有很多 $f$ 的值并不会用到，采用记忆化搜索即可，注意实现的细节。

使用 umap 后，时间复杂度为 $\mathcal{O}(n^{\frac{3}{4}})$，空间复杂度 $\mathcal{O}(n^{\frac{1}{2}})$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int mod=1e9+7;
int n,m;
unordered_map<int,int> f;

int power(int a,int b){
	int res=1;
	for(;b>0;a=1ll*a*a%mod,b>>=1)if(b&1)res=1ll*res*a%mod;
	return res;
}
int dfs(int x){
	if(x==1)return 0;
	if(f[x])return f[x];
	for(int l=2,r;l<=n;l=r+1){
		if((x-1)/l==0)r=n;
		else r=min(n,(x-1)/((x-1)/l));
		f[x]=(f[x]+(r-l+1)*1ll*dfs((x-1)/l+1)%mod)%mod;
	}
	f[x]=(1ll*f[x]%mod+n)*power(n-1,mod-2)%mod;
	return f[x];
}

int main(){
	cin>>n>>m;
	cout<<dfs(m+1)<<"\n";
	return 0;
}
```

---

## 作者：猫猬兽 (赞：6)

纪念第一道场切的 Ex。

一眼期望 DP。

令 $f(x)$ 表示当前值达到至少 $x$ 的期望次数。

先列一个暴力的转移方程：

$f(x)=1+\frac{1}{N} \sum_{i=1}^{N}f(\lceil\frac{x}{i}\rceil)$。

化一下式子，可得：

$f(x)=\frac{N}{N-1}+\frac{1}{N-1} \sum_{i=2}^{N}f(\lceil\frac{x}{i}\rceil)$。

$f(M+1)$ 即为问题答案。

暴力实现时空复杂度均为 $O(M)$。

记忆化，整除分块，unordered_map 优化时空复杂度后，总时空复杂度为 $O(M^{\frac{3}{4}})$。

代码如下：


```cpp
#include<iostream>
#include<cstdio>
#include<unordered_map>
using namespace std;
long long n,m,s,i;
unordered_map<int,int>f;
long long q(long long a){long long r=1,k=1000000005;while(k>0){if(k%2==1)r=a*r%1000000007;k=k/2;a=a*a%1000000007;}return r;}
long long p(long long x)
{
	if(x==1)return 0;
	if(f[x]!=0)return f[x];
	long long s=0;
	for(long long l=2,r;l<=n;l=r+1)
	{
		if((x-1)/l==0)r=n;
		else r=(x-1)/((x-1)/l);
		r=min(r,n);
		s=s+(r-l+1)*p((x-1)/l+1);
	}
	s=(s%1000000007*q(n)%1000000007+1)%1000000007;
	return f[x]=s%1000000007*n%1000000007*q(n-1)%1000000007;
}
int main()
{
	cin>>n>>m;m=m+1;
	f[2]=n*q(n-1)%1000000007;
	cout<<p(m);
	return 0;
}
```


---

## 作者：Irisss_ (赞：5)

$$
\text{令 }f(x)\text{ 为 选到至少为 }x\text{ 的最小期望步数。}
$$

$$
\begin{aligned}
f(x) & =1+\frac{1}{n}\sum_{i=1}^{n}f(\lceil \frac{x}{i} \rceil)
\\ &=1+\frac{1}{n}f(x)+\frac{1}{n}\sum_{i=2}^{n}f(\lceil \frac{x}{i} \rceil)
\\
\frac{n-1}{n}f(x)&=1+\frac{1}{n}\sum_{i=2}^{n}f(\lceil \frac{x}{i} \rceil)
\\
f(x)&=\frac{n}{n-1}+\frac{1}{n-1}\sum_{i=2}^{n}f(\lceil \frac{x}{i} \rceil)
\end{aligned}
$$
然后就可以数论分块了。
时间复杂度为 $O(n^\frac{3}{4})$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

const int mod = 1e9 + 7;

ll qPow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		b >>= 1;
		a = a * a % mod;
	}
	return res;
}

cc_hash_table<int, ll> f;
int n;
ll inv;

ll get(int x) {
	if (f.find(x) != f.end()) return f[x];
	ll res = 0;
	for (int d = n, last; d > 1; d = last - 1) {
		last = ceil(1.0 * x / ceil(1.0 * x / d));
		last = max(last, 2);
		ll val = get((int) ceil(1.0 * x / d));
		res = (res + val * (d - last + 1) % mod) % mod;
	}
	res = res * inv % mod;
	res = (res + n * inv % mod) % mod;
	return f[x] = res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int m;
	cin >> n >> m;
	f[1] = 0;
	inv = qPow(n - 1, mod - 2);
	cout << get(m + 1);

    return 0;
}
```

---

## 作者：Creeper_l (赞：3)

原题链接：[ABC239Ex](https://www.luogu.com.cn/problem/AT_abc239_h)。

题意不多赘述。

看到求期望值，我们想到可以用期望 DP。

设 $dp_{i}$ 表示最终结果大于等于 $i$ 时的操作次数的期望值。

那么我们可以得到一个基本的状态转移方程：$dp_{i}=\frac{1}{n} \times \sum_{j=1}^{n}dp_{\left \lceil \frac{i}{j} \right \rceil} + 1$。

方程表示的意义是，这次骰子的点数 $j$ 可能是 $1$ 到 $n$，所以每一种的概率为 $\frac{1}{n}$，因为乘积为 $i$，所以分别对应之前的 $\left \lceil \frac{i}{j} \right \rceil$，加上 $1$ 表示当前需要骰一次。

但是因为当 $j=1$ 时 $\left \lceil \frac{i}{j} \right \rceil=i$，整个方程不好转移，所以我们可以考虑把转移方程变一下，变成：$dp_{i}=\frac{1}{n-1} \times \sum_{j=2}^{n}dp_{\left \lceil \frac{i}{j} \right \rceil} + \frac{n}{n-1}$。这里就相当于是把 $j=1$ 的情况去掉了，但是总数就变成了 $n-1$ 个，于是整体乘上了一个 $\frac{n}{n-1}$。

显然最终我们要去求的答案就是 $dp_{m+1}$，注意不是 $dp_m$，因为要求严格大于。

如果纯暴力的话时间复杂度是 $O(nm)$ 的，加上记忆化会优化到 $O(m)$，再加上整除分块就可以过了。（```1000000000 1000000000``` 的数据本地要跑 $5$ 秒，开 O2 的话 $1.4$ 秒，但是在 Atcoder 上跑得很快）。

[评测记录](https://atcoder.jp/contests/abc239/submissions/46208086)。





---

## 作者：yhylivedream (赞：2)

[弱化版链接](https://www.luogu.com.cn/problem/AT_abc350_e)。


设状态 $f_i$ 表示将 $x$ 乘到大于等于 $i$ 的期望操作次数。


暴力转移方程：
$f_i=\dfrac{\sum_{j=1}^n f_{\lceil \frac{i}{j}\rceil}}{n}$。


化简得：$f_i=\dfrac{n}{n-1}+\dfrac{\sum_{j=2}^n f_{\lceil \frac{i}{j}\rceil}}{n-1}$。


注意到 $\dfrac{\sum_{j=2}^n f_{\lceil \frac{i}{j}\rceil}}{n-1}$ 的分子是整除分块的形式可以直接 $O
(\sqrt{n})$ 做。


合法的状态显然很少，直接记搜用 umap 存状态，细节就是题目要求 $x$ 乘到大于 $m$ 所以答案是 $f_{m+1}$。


```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;

const LL M = 1e9 + 7;

LL n, m, t;
unordered_map<LL, LL> mp;

LL qpow(LL a, LL n) {
  LL r = 1, w = a;
  for (LL i = 1; i <= n; i <<= 1, w = w * w % M) {
    n & i && (r = r * w % M);
  }
  return r;
}

LL dfs(LL x) {
  if (x == 1) {
    return mp[x] = 0;
  }
  if (mp[x]) {
    return mp[x];
  }
  LL sum = 0;
  for (LL l = 2, r; l <= n; l = r + 1) {
    r = (x - 1) / l ? min(n, (x - 1) / ((x - 1) / l)) : n;
    sum = (sum + dfs((x - 1) / l + 1) * (r - l + 1) % M) % M;
  }
  sum = (1LL * sum % M + n) * t % M;
  return mp[x] = sum;
}

signed main() {
  cin >> n >> m, t = qpow(n - 1, M - 2);
  cout << dfs(m + 1);
}
```

---

## 作者：WorldMachine (赞：1)

简单期望 dp + 整除分块。

设 $f(x)$ 表示至少乘到 $x$ 的期望次数，有：
$$
f(x)=\dfrac 1n\sum_{i=1}^nf\left(\left\lceil\dfrac{x}{i}\right\rceil\right)+1
$$
将 $i=1$ 单独提出来移到左边去：
$$
\dfrac{n-1}{n}f(n)=\dfrac1n\sum_{i=2}^nf\left(\left\lceil\dfrac{x}{i}\right\rceil\right)+1
$$
即：
$$
f(n)=\dfrac{n}{n-1}+\dfrac{1}{n-1}\sum_{i=2}^nf\left(\left\lceil\dfrac{x}{i}\right\rceil\right)
$$
类比杜教筛，整除分块+记忆化即可，时间复杂度为 $\mathcal O(n^{\frac 34})$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int p = 1e9 + 7;
int n, m, invn_1;
unordered_map<int, int> f;
int qpow(int a, int b) {
	int c = 1;
	while (b) { if (b & 1) c = (ll)c * a % p; a = (ll)a * a % p, b >>= 1; }
	return c;
}
int dp(int x) {
	if (x == 1) return 0;
	if (f[x]) return f[x];
	int sum = 0, x_1 = x - 1;
	for (int l = 2, r, k; l <= n; l = r + 1) {
		k = x_1 / l, r = k ? min(n, x_1 / k) : n;
		sum = (sum + ll(r - l + 1) * dp(k + 1)) % p;
	}
	return f[x] = ((ll)sum * invn_1 + (ll)n * invn_1) % p;
}
int main() {
	cin >> n >> m, invn_1 = qpow(n - 1, p - 2);
	cout << dp(m + 1);
}
```

---

## 作者：船酱魔王 (赞：1)

## 题意回顾

有初始值为 $ 1 $ 的变量 $ X $，每秒发生以下事件：

* 等概率随机取 $ [1,n] $ 的整数 $ r $，然后 $ X \leftarrow X \times r $。
* 若 $ X>m $，结束过程。

求结束时期望的秒数，对质数取模。

## 分析

考虑拆环，我们有结论

> 对于概率为 $ p $ 成功的操作，期望进行 $ \frac{1}{p} $ 次才能成功一次。

证明：考虑不断操作直到成功，在第 $ i $ 次成功的概率为 $ (1-p)^{i-1} \times p $，期望次数为 $ \sum_{i=1}^{+\infty}(1-p)^{i-1} \times p \times i $，设 $ S=\sum_{i=1}^{+\infty}(1-p)^{i-1}i $，$ (1-p)S=\sum_{i=2}^{+\infty}(1-p)^{i-1}(i-1) $，故次数为 $ pS=S-(1-p)S=1+\sum_{i=1}^{+\infty}(1-p)^i=1+\frac{1-p}{p}=\frac{1}{p} $。

因此我们可以将题意转化为，每次取 $ [2,n] $ 之间的整数，将次数乘 $ \frac{n}{n-1} $，因为有 $ \frac{n-1}{n} $ 的概率取到 $ [2,n] $ 之间的整数。

我们可以设计 DP 在 $ O(nm) $ 的时间复杂度内解决本问题，转移方程式为 $ dp_i=\frac{\sum_{u=2}^n dp_{iu}}{n-1}+1 $，$ dp_i $ 表示初始时 $ X=i $ 时的期望次数。

考虑优化状态转移，记 $ dp_i $ 为 $ X $ 满足 $ i $ 为最大的 $ iX \le m $，此时的期望次数。我们可以发现此时状态量为 $ O(\sqrt{n}) $。

还是不行，我们发现因为转移时转移到 $ dp_{\frac{i}{u}} $，而 $ \frac{i}{u} $ 的取值有 $ O(\sqrt{i}) $ 种。

故时间消耗为 $ \sum_{i=1}^{\sqrt{n}} \sqrt i + \sum_{i=1}^{\sqrt{n}} \sqrt {\frac{n}{i}} = O(n^{0.75}) $。

## AC 代码

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>
#include <unordered_map>
using namespace std;
const int mod = 1e9 + 7;
int n, m;
int ks = 0;
int ksm(int p, int q) {
    int res = 1;
    int mul = p;
    while(q) {
        if(q & 1) res = (long long)res * mul % mod;
        mul = (long long)mul * mul % mod, q >>= 1;
    }
    return res;
}
unordered_map<int, int> dp;
int solve(int u) {
    if(dp[u] > 0) return dp[u];
    if(u == 0) return 0;
    int sq = (int)sqrt(u);
    dp[u] = 0;
    for(int i = 2; i <= min(n, sq); i++) {
        dp[u] = (dp[u] + solve(u / i) + 1) % mod;
    }
    int dq = sq;
    if(sq * sq == u) sq--;
    for(int i = 0; i <= sq; i++) {
        dp[u] = (dp[u] + (long long)(solve(i) + 1) * max(0, min(n, (i == 0) ? n : (u / i)) -
                                                         max(u / (i + 1), dq))) % mod;
    }
    dp[u] = (long long)dp[u] * ks % mod;
    return dp[u];
}
int main() {
    cin >> n >> m;
    ks = ksm(n - 1, mod - 2);
    solve(m);
    printf("%d\n", (int)((long long)dp[m] * n % mod * ks % mod));
    return 0;
}

```

---

## 作者：skyskyCCC (赞：1)

## 前言。
可算是找到了一个期望概率 DP 好题。

这个的算法灵感是题目中的“期望”和“骰子”的启发。
## 分析。
考虑 DP 方程。我们令 $dp_i$ 为当前 $M=i$ 的期望剩余步数，则考虑每一步填什么，不难推出如下的式子：
$$dp_i=\frac{n}{n-1}\left(1+\frac{1}{n}\sum\limits_{j=1}^{n}dp_{i\ j}\right)$$

其中对于 $>m$ 的 $dp_{i\ j}$ 不妨令为 $0$ 则可以写出代码。时间复杂度为 $O\left(m\log m\right)$ 显然通过本题有一定的难度，所以考虑优化。

第一步，考虑缩小 $dp_i$ 的空间。考虑将 $\left\lfloor\dfrac{m}{i}\right\rfloor$ 作为下标。为什么？我们可以从 $m$ 下手，如果我们去计算 $\left\lfloor\dfrac{m}{i}\right\rfloor$ 时，肯定会出现某几个 $i$ 使得这个式子的结果一样。考虑到乘的数是 $1$ 到 $N$ 的整数，所以显然通过它们对应的 $i$ 所求得的 $dp_i$ 都是相等的。那么我们就可以缩小范围。此时遍历整个 $i$ 的所求的的 $dp_i$ 中，我们就可以进行删减操作，即有 $\sqrt{m}$ 段对答案有贡献的值。

当我们将它作为下标后，该式分子分母同除 $i$ 即可将分母去除，然后得到 $\left\lfloor\dfrac{m}{i\times A}\right\rfloor=\left\lfloor\dfrac{\left\lfloor m/i\right\rfloor}{A}\right\rfloor$ 其中 $A$ 是一个值。重新套到原来的转移式中，令 $y=\left\lfloor\dfrac{i}{j}\right\rfloor$ 可以得到：
$$dp_i=\frac{n}{n-1}\left(1+\frac{1}{n}\sum\limits_{j=2}^{n}dp_{y}\right)$$

显然这个玩意可以用记忆化搜索解决。套上记忆化搜索这个东西的时间复杂度，然后加上快速幂，时间复杂度大约为 $\int_{2}^{\sqrt{m}}\left(\sqrt{x},\sqrt{\dfrac{m}{x}}\right)\,dx=O\left(m^{0.75}\right)$ 的样子。

进行一个小小的优化，就是判断边界情况。当然，出题人很好，如果您不判断，它会因为越界而判错。

注意用 ```map``` 会死的很惨。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
#include<unordered_map>
using namespace std;
const int mod=1e9+7;
int n,m;
unordered_map<int,int> ma;
int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1){
            res=1ll*res*a%mod;
        }
        a=1ll*a*a%mod;
        b>>=1;
    }
    return res;
}
int dfs(int x){
	if(x==1){
		return 0;
	}
	if(ma[x]){
		return ma[x];
	}
	for (int l=2,r;l<=n;l=r+1){
		((x-1)/l==0)?(r=n) : (r=min(n,(x-1)/((x-1)/l)));
		ma[x]=(ma[x]+(r-l+1)*1ll*dfs((x-1)/l+1)%mod)%mod;
	}
	ma[x]=(1ll*ma[x]%mod+n)*ksm(n-1,mod-2)%mod;
	return ma[x];
}
int main(){
    cin>>n>>m;
    int ans=dfs(m+1);
    cout<<ans<<"\n";
    return 0;
}
```
## 后记。
实际检测后，最慢的一个点跑了 $722$ 分秒，绰绰有余。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Purslane (赞：0)

# Solution

问题可以转化为：维护一个变量 $M$。每次在 $1$ 到 $N$ 中随一个数 $x$ 出来，$M \leftarrow \lfloor \frac{M}{x} \rfloor$。问期望进行多少次操作后 $M$ 变为 $0$。

显然 $M$ 一定可以写成 $\lfloor \frac{M_0}{n} \rfloor$ 的形式，而这样的值只有 $O(\sqrt {M_0})$ 个，可以直接拉出来 DP。容易写出转移：

$$
dp_i = 1 + \frac{1}{n}\sum_{j=1}^n dp_{\lfloor \frac{i}{j} \rfloor}
$$

整除分块优化即可。

这个 DP 可以直接用线性数组存储。设立一个阈值 $B$，当 $i \le B$ 的时候存在一个数组的 $i$ 位置；否则存在另一个数组的 $\lfloor \frac{M_0}{i} \rfloor$ 位置。

时间复杂度为 $O(n^{0.75})$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e9+10,MAXM=1e5+10,MOD=1e9+7;
int n,m,dp1[MAXM],dp2[MAXM];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int calc_dp(int pos) {
	if(pos<=100000) return dp1[pos];
	return dp2[m/pos];	
}
void solve(int pos) {
	int dp=0;
	int l=2;
	while(l<=pos) {
		int r=pos/(pos/l);
		int L=l,R=min(r,n);
		if(L<=R) dp=(dp+calc_dp(pos/l)*(R-L+1))%MOD;
		l=r+1;
	}
	dp=(dp+n)%MOD;
	dp=dp*qpow(n-1,MOD-2)%MOD;
	if(pos<=100000) dp1[pos]=dp;
	else dp2[m/pos]=dp;
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	vector<int> pos;
	int l=1;
	while(l<=m) pos.push_back(m/l),l=m/(m/l)+1;
	reverse(pos.begin(),pos.end());
	for(auto id:pos) solve(id);
	cout<<(calc_dp(m))%MOD;
	return 0;
}
```

---

## 作者：liujiaxi123456 (赞：0)

#### 一眼概率期望 DP，两种思路：

- 概率 DP：枚举权值求概率。

  - 这里的权值是步数，没有很好的范围，无法枚举。
 
- 期望 DP：直接做。

  - 先想的是 $f_x $ 表示**恰好**到 $x$ 的方案数，但是这样最后不好统计答案（要枚举大于等于 $m+1$ 的所有 $x$）。
 
  - 于是启发我们把 $f$ 改成**至少**到 $x$ 的方案数。
 
#### 考虑转移：

- 基本式子很好列：$f_x = 1 + \dfrac{1}{n}\cdot \sum_{i=1}^n f_{\left \lceil \frac xi \right \rceil } $。

- 注意到有 $i=1$ 影响转移，把它提出来后得到：$f_x = \dfrac{n}{n-1} + \dfrac {1}{n-1}\cdot \sum_{i=2}^n f_{\left \lceil \frac xi \right \rceil } $。

#### 计算 f：

- 显然不能直接枚举 $x$ 转移。

- 先考虑矩阵快速幂，显然不行。

- 注意到只需要求一次 $f_{m+1}$ 即可，使用记忆化搜索 + 整除分块处理即可。

#### Code：
```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define ll long long
using namespace std;
using namespace __gnu_pbds;

const int MOD = 1e9+7;

namespace Josh_zmf {
	
	int N, M; ll inv;
	gp_hash_table <int, ll> f;

	inline ll pow(ll a, int b) {
		ll c = 1;
		while(b) {
			if(b&1)	c = c*a %MOD;
			a = a*a %MOD, b >>= 1;
		}
		return c;
	}

	inline ll F(int x) {
		if(f[x] || x==1)	return f[x];
		ll res = 0; 
		x--;
		for(int i=2, r; i<=N; i=r+1) {
			r = (x/i ?x/(x/i) :N);
			r = min(r, N);
			res += F(x/i+1)*(r-i+1) %MOD;
		}
		x++;
		return f[x] = (N*inv + res%MOD*inv) %MOD;
	}

	inline int main() {
		cin>> N>> M, inv = pow(N-1, MOD-2);
		cout<< F(M+1)<< '\n';
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```

---

## 作者：nullqtr_pwp (赞：0)

期望 dp 好题。

题意：给定正整数 $n,m$。你有一个正整数 $M$，初始 $M=1$。你将进行若干次操作，每次在 $[1,n]$ 中均匀随机选取一个整数 $x$ ，并令 $M:=M\times x$。当 $M>m$ 时停止操作。求期望进行多少次操作。$1\leq m\leq 10^9,2\leq n\leq 10^9$。

求期望的这种题怎么着都要往**期望 dp** 上去想。

设 $f_i$ 表示使得 $x\ge i$ 的期望时间。初始有 $f_1=0$。考虑转移，从最后一次选择入手，由期望的性质 $E(xy)=E(x)E(y)$，容易得到
$$f_i=1+\dfrac{\sum_{j=1}^n f_{\lceil \frac{i}{j}\rceil}}{n}$$
然而直接暴力这样做会寄，因为这样的复杂度是 $O(nm)$ 的。

两边都有 $f_i$ 的系数，考虑整理到一边，得：

 $$f_i=\dfrac{n}{n-1}+\dfrac{\sum_{j=2}^n f_{\lceil \frac{i}{j}\rceil}}{n-1}$$
 
 

能看出什么了吗？由整除分块的性质，对于给定的 $i$，$f_{\lceil \frac{i}{j}\rceil}$ 的值是只有 $O(\sqrt i)$ 的级别。对于 $m+1$，有很多状态是没有贡献的，可以直接记忆化搜索。用 ```unordered_map``` 存就好了。注意用 ```map``` 会被卡常。



---

## 作者：0x3F (赞：0)

记 $f(v)$ 表示第一次 $x>v$ 期望需要扔骰子的期望次数，则有以下转移方程：

$$f(v)=1+\frac{1}{n}\sum_{i=1}^{n}f(\lfloor\frac{v}{i}\rfloor)$$

化简得：

$$f(v)=\frac{n}{n-1}+\frac{1}{n-1}\sum_{i=2}^{n}f(\lfloor\frac{v}{i}\rfloor)$$

初始值为 $f(0)=0$，答案为 $f(m)$。

我们只对所有可以表示为 $v=\lfloor\frac{m}{k}\rfloor(k\in\mathbb{Z})$ 的 $v$ 求出 $f(v)$ 的值，转移整除分块即可。

分析一下复杂度：

当 $k\le\sqrt{m}$ 时，所需时间为：

$$\sum_{k=1}^{\lfloor\sqrt{m}\rfloor}\sqrt{\lfloor\frac{m}{k}\rfloor}\approx\int_{1}^{\sqrt{m}}\sqrt{\frac{m}{x}}\mathrm{d}x=[2\sqrt{mx}]_{1}^{\sqrt{m}}=\mathcal{O}(m^{\frac{3}{4}})$$

当 $k>\sqrt{m}$ 时，$v<\sqrt{m}$，所需时间为：

$$\sum_{v=1}^{\lceil\sqrt{m}\rceil-1}\sqrt{v}\approx\int_{1}^{\sqrt{m}}\sqrt{x}\mathrm{d}x=[\frac{2}{3}x^{\frac{3}{2}}]_{1}^{\sqrt{m}}=\mathcal{O}(m^{\frac{3}{4}})$$

综上，时间复杂度为 $\mathcal{O}(m^{\frac{3}{4}})$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
inline int qpow(int a, int b) {
    int s = 1;
    while (b) {
        if (b & 1) s = (long long) s * a % mod;
        a = (long long) a * a % mod;
        (b >>= 1);
    }
    return s;
}
int n, m, s, dp[100000];
inline int rnk(int x) {
    if (x <= s) {
        return x;
    } else {
        return s + (m / x);
    }
}
int main() {
    cin >> n >> m;
    s = sqrt(m);
    int inv = qpow(n - 1, mod - 2);
    for (int i = 1, j = 0; i <= m; i = j + 1) {
        j = m / (m / i);
        int r = rnk(j);
        int sum = n;
        for (int l = 2, r = 0; l <= j; l = r + 1) {
            int d = j / l;
            r = j / d;
            int t = rnk(d);
            if (r >= n) {
                sum = (sum + (long long) (n - l + 1) * dp[t]) % mod;
                break;
            } else {
                sum = (sum + (long long) (r - l + 1) * dp[t]) % mod;
            }
        }
        int res = (long long) sum * inv % mod;
        dp[r] = res;
        if (j == m) {
            cout << res << endl;
        }
    }
    return 0;
}
```

---

