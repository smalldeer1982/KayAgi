# [ICPC 2020 Shanghai R] The Journey of Geor Autumn

## 题目描述

### 题意简述
给定 $1 \le k \le n$，我们规定满足以下性质的 $1 \sim n$ 的排列称之为“好排列”：

$\forall k<i \le n,~a_i > \min{a_{i-k},a_{i-k+1},...,a_{i-1}}$

求好排列的个数。对 $998244353$ 取模。

## 样例 #1

### 输入

```
1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
2 3```

### 输出

```
2```

## 样例 #3

### 输入

```
3 2```

### 输出

```
4```

## 样例 #4

### 输入

```
4 2```

### 输出

```
10```

# 题解

## 作者：SunsetLake (赞：11)

## 思路

注意到题目中的限制条件是 $a_i > $ 一坨东西的 $\min$，那么可以从 $a_i$ 的最小值入手。因为没有比 $1$ 更小的了，所以 $1$ 一定要填在 $[1,k]$ 这个区间，才能保证序列的合法。

于是考虑 $1$ 的位置，设它在 $x$。那么对于 $[1,x)$ 就可以没有限制随便填，方案数就是 $C_{n - 1}^{x - 1}\times (x - 1)!$。对于 $(x,n]$ 的前 $k$ 个位置，你会发现没有限制了！因为最小的 $1$ 已经被填在了 $x$，不会有比它更小的数了。于是这部分的方案数转化成了一个新的子问题，记其为 $f_{n - x}$。故总方案数 $f_n = \displaystyle\sum\limits_{x = 1}^{\min(n,k)}C_{n - 1}^{x - 1}\times (x - 1)! \times f_{n - x}$，相当于做一个 dp 就行了。

但是直接求是 $O(nk)$ 的，需要优化一下。把 $C_{n - 1}^{x - 1}$ 写成 $\dfrac{(n - 1) !}{(x - 1)! \times (n - x)!}$，$(x - 1)!$ 就被消掉了，再将 $(n - 1)!$ 提到 $\sum$ 外面，得到：$f_n = (n - 1)!\displaystyle\sum\limits_{x = 1}^{\min(n,k)}\dfrac{f_{n - x}}{(n - x)!}$。这玩意儿用个前缀和维护就行了。

复杂度 $O(n)$。

## code


```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N = 1e7 + 5,mod = 998244353;
int n,k;
ll f[N],sum[N],fac[N],inv[N];
ll qpow(ll x,ll y){
	ll res = 1;
	while(y){
		if(y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
ll C(ll x,ll y){
	if(x < y || x < 0 || y < 0) return 0;
	return fac[x] * inv[y] % mod * inv[x - y] % mod;
}
int main(){
	cin >> n >> k;
	fac[0] = inv[0] = 1;
	for(int i = 1;i <= n;++ i) fac[i] = fac[i - 1] * i % mod;
	inv[n] = qpow(fac[n],mod - 2);
	for(int i = n - 1;i >= 1;-- i) inv[i] = inv[i + 1] * (i + 1) % mod;
	f[0] = sum[0] = 1;
	for(int i = 1;i <= n;++ i){
		f[i] = sum[i - 1];
		if(i - 1 - k >= 0) f[i] = (f[i] - sum[i - k - 1] + mod) % mod;
		f[i] = f[i] * fac[i - 1] % mod;
		sum[i] = (sum[i - 1] + f[i] * inv[i] % mod) % mod;
	}
	cout << f[n];
	return 0;
}
```

---

## 作者：zzafanti (赞：6)


[传送门](https://www.luogu.com.cn/problem/P9823)

## description

给定 $n,k$，求有多少个 $n$ 的排列满足 $\forall i\in[k+1,n],\min\limits_{j=i-k}^{i-1} a_j < a_i$。

- $n,k\leq 10^7$

## solution

设 $f_i$ 表示对于给定的 $k$，排列长度为 $i$ 时的答案。

转移时，我们考虑在**头部**添加新的数，设添加后的序列是 $\{a\}$。根据限制，我们只需考虑新加的数能不能使 $a_{k+1}$ 大于它前面最小的数。

我们再来考虑一个性质：对于一个合法的排列，排列中的最小数一定在前 $k$ 个数中。

于是，讨论 $a_{k+1}$ 是否等于第 $2$ 到第 $i$ 个数的最小数。

- 如果是，那么只有 $a_1$ 也就是新添加的数为当前整个序列的最小数时才合法。此时第 $2$ 到第 $k$ 个数可以填除整个序列最小次小外任意的数。方案数就可以从 $f_{i-k-1}$ 乘上系数转移过来了。

- 否则，那么后面 $i-1$ 个数的最小数一定在第 $2$ 到第 $k$ 个位置，方案数就是 $f_{i-1}$ 减去后 $i-1$ 个数的最小数在第 $k+1$ 个位置的方案数，在第一种情况中已经说明了计算方法。头部新添加的数是可以任意填的，所以还要乘上系数 $i$。

综上，我们有转移：

- $f_{i}=i!,0\leq i\leq k$

- $f_{i}=(f_{i-1}-f_{i-k-1}\times A^{k-1}_{i-2})\times i+f_{i-k-1}\times A^{k-1}_{i-2}$

预处理阶乘和阶乘逆元，时间复杂度 $O(n)$。

## code

```cpp
/******
 *zz  *
 *af  *
 *an  *
 *ti  *
 ******/
#include<bits/stdc++.h>

using namespace std;

using E=long long;
using ui=uint32_t;
constexpr E inf=1e16,mod=998244353;

vector<E> fac,ifac;
E n,k;

inline E ksm(E a,E b){
  E ret=1;
  while(b){
    if(b&1) ret=ret*a%mod;
    a=a*a%mod;
    b>>=1;
  }
  return ret;
}

inline E C(E n,E m){
  if(n<0||m<0) return 0;
  return n<m?0:fac[n]*ifac[n-m]%mod*ifac[m]%mod;
}

int main(){
  cin.tie(nullptr),cout.tie(nullptr)->sync_with_stdio(false);

  cin>>n>>k;
  fac.resize(n+1),ifac.resize(n+1);
  fac[0]=ifac[0]=1;
  for(int i=1; i<=n; i++) fac[i]=fac[i-1]*i%mod;
  ifac[n]=ksm(fac[n],mod-2);
  for(int i=n-1; i; i--) ifac[i]=ifac[i+1]*(i+1)%mod;

  vector<E> f(n+1);
  for(int i=0; i<=k; i++) f[i]=fac[i];

  for(int i=k+1; i<=n; i++){
    f[i]=((f[i-1]-f[i-k-1]*fac[k-1]%mod*C(i-2,k-1)%mod+mod)%mod*i+fac[k-1]*f[i-k-1]%mod*C(i-2,k-1)%mod)%mod;
  }

  cout<<f[n];

  return 0;
}
```


---

## 作者：a1co0av5ce5az1cz0ap_ (赞：2)

题意：求对于任意 $k<i\le n$ 都有 $a_i>\min(a_{i-1},...,a_{i-k})$ 的排列 $a$ 方案数。

首先容易得到一个简单的 dp：$f_i$ 表示长度为 $n-i+1$ 的排列且第一个为最小值的方案数。

于是有状态转移方程 $f_i=\sum\limits_{j=i+1}^{\min(n,i+k)}P_{n-i-1}^{j-i-1}\cdot f_j$。这里 $P$ 指的是排列数（也可以用 $A$ 表示）。

边界是 $f_n=1$，答案是 $f_0$。

这个 dp 是 $O(nk)$ 的，会超时，于是对其进行优化。

考虑排列数本质 $P_{n}^{m}=\frac{n!}{(n-m)!}$，转移方程中即 $P_{n-i-1}^{j-i-1}=\frac{(n-i-1)!}{(n-j)!}$。

分母只与 $j$ 有关，可以乘到 $f$ 中，剩下的系数只与 $i$ 有关，可以提出来。

剩下的部分就是一段 $f$ 的和，直接用一个数记录即可。

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <stack>
#include <random>
using namespace std;
typedef long long ll;
const int N = 10000005, mod = 998244353;
ll dp[N], fac[N], inv[N];
ll ksm(ll x, int y) {
    ll res = 1;
    while (y) {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}
inline ll fc(int y, int x) {
    // cout << 
    return fac[y] * inv[y - x] % mod;
}
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[n] = ksm(fac[n], mod - 2);
    for (int i = n; i; i--) {
        inv[i - 1] = inv[i] * i % mod;
        // cout << i << ' ' << fac[i] << ' ' << inv[i] << '\n';
    }
    dp[n] = 1;ll s=1; // s 记的是这些 dp 值的和
    for (int i = n - 1; ~i; i--) {
        dp[i]=fac[n-i-1]*s%mod; // 把 (n-i-1)! 提出来
        if(i+k<=n)s=((s-inv[n-i-k]*dp[i+k]%mod)%mod+mod)%mod; // 减去已经过去的项
        s=(s+inv[n-i]*dp[i]%mod)%mod; // 增加这次新的项，这里为了方便输出就把 1/(n-i)! 拿出来了
        /*for (int j = i + 1; j <= min(n, i + k); j++) {
            dp[i] = (dp[i] + fc(n - i - 1, j - i - 1) * dp[j]) % mod; // 这里是原本的 dp 部分
            // cout << i << ' ' << j << ' ' << n - i - 1 << ' ' << j - i - 1 << ' ' << dp[j] << "!\n";
        }
        // cout << i << ' ' << dp[i] << '\n';
        */
    }
    printf("%lld\n", dp[0]);
    return 0;
}
```

---

## 作者：chen_zhe (赞：2)

以下内容转载自官方题解：

可以先尝试找规律做出此题，有公式后再思考如何证明。

考虑 $1$ 在哪个位置。一定要在前 $k$ 个位置之一。枚举这个位置 $x$。整个序列合法当且仅当 $1$ 之前任意放置，$x$ 到 $n$（里面的数字离散化后）形成一个长度为 $n-x+1$ 的合法序列。

上述递推式可以优化到线性。

---

## 作者：Federico2903 (赞：2)

## 思路

考虑朴素 $O(nk)$ DP，记 $f_i$ 表示确定了 $i \sim n$ 这些数的方案数，初始状态有 $f_n = 1$。

设我们这里放 $i$，我们枚举上一次放到了哪里（此处不应超过 $i + k$），设其为 $j$，那么中间的数字（$i + 1 \sim j$）就可以随意放了。

考虑插板法，我们有如下转移：

$$
f_i = \sum_{j = i + 1}^{\min(n, i + k)} f_j \times {{n - i - 1} \choose {j - i - 1}} \times (j - i - 1)!
$$

然后你发现后面那个组合数变成了排列数：

$$
f_i = \sum_{j = i + 1}^{\min(n, i + k)} f_j \times A_{n - i - 1}^{j - i - 1}
$$

这个东西看起来很能前缀和优化不是吗。我们考察 $i$ 向前走的时候 $f_j$ 系数的变化，不难发现若 $f_j$ 能对 $f_{i - 1}$ 产生贡献，那么其系数将变为 $A^{j - i}_{n - i}$，不难发现其实是乘了一个 $n - i$。

那么我们有初始状态 $pre_n = f_n = 1$ 和转移：

$$
\begin{cases}
f_i = pre_{i + 1}\\
pre_i = pre_{i + 1} \times (n - i) + f_i - (f_{i + k} \times A_{n - i}^k)[i + k \le n]
\end{cases}
$$

答案就是 $f_0$，时间复杂度 $O(n)$。

## AC 代码

```cpp
f[n] = 1;
int pre = 1;
_rep (i, n - 1, 0) {
	f[i] = (f[i] + pre) % MOD;
	pre = (pre * (n - i)) % MOD;
	pre = (pre + f[i]) % MOD;
	if (i + k <= n) {
		pre = (pre - f[i + k] * A(n - i, k) % MOD) % MOD;
		pre = (pre + MOD) % MOD;
	}
}
```

---

## 作者：xxr___ (赞：1)

1. 首先，我们考虑 $1$ 的位置，显然不能把 $1$ 放到 $k$ 之后，要不然前 $k$ 个数的最小值一定不小于 $1$ 所以 $1$ 的位置是 $[1,k]$。

2. 其次，我们假设此时已经确定了 $1$ 的位置为 $x\in [1,k]$ 我们发现 $[1,x)$ 的数可以随便填，因为下表小于 $k$ 方案数是 $(x-1)!\times C_{n-1}^{x-1}$ 的，并且 $[x+1,x+k]$ 也是可以随便填的，因为此时最小值是 $1$ 因为是排列，所以没有比 $1$ 更小的数了，遂合法，然后这一部分，也就是 $(x,n]$ 变成了一个子问题 $f_{n-x}$ 因为就和 $1$ 一样了嘛，都是前 $k$ 位找一个位置随便填。

3. 所以我们可以设 $f_x$ 表示 $[1,x]$ 的答案，转移是 $f_x=\sum_{y=1}^{\min(n,k)} f_{x-y}\times (y-1)!\times C_{x-1}^{y-1}$。这样是 $O(nk)$ 的。

4. 因为答案是一段连续的区间，所以考虑前缀和优化。首先把式子变形一下，变成 $C_{i}^j=\frac{i!}{j!\times (i-j)!}$ 的形式，则原式就是 $f_x = \sum_{y=1}^{\min(n,k)} f_{x-y}\times (y-1)!\times C_{x-1}^{y-1} = \sum_{y=1}^{\min(n,k)} f_{x-y}\times (y-1)!\times \frac{(x-1)!}{(y-1)!\times (x-y)!} = \sum_{y=1}^{\min(n,k)} f_{x-y}\times \frac{(x-1)!}{(x-y)!} = (x-1)!\times (\sum_{y=1}^{\min(n,k)} \frac{f_{x-y}}{(x-y)!})$。也就是 $f_x = (x-1)!\times (\sum_{y=1}^{\min(n,k)} f_{x-y}\times ((x-y)!)^{-1})$ 这个是好用前缀和维护的。

5. 综上，总的时间复杂度是 $O(n)$ 空间 $O(n)$。

6. [代码](https://www.luogu.com.cn/record/211496534)

---

## 作者：Loser_Syx (赞：1)

考虑当前答案满足的样子，显然一定是前 $k$ 个里面有个 $1$，考虑枚举 $1$ 的位置，这个位置前面一定是随便填的，而这个位置之后就又变成了一个新的最小值问题。那么就有 $f_i = \sum_{j=1}^k P_{i-1}^{j-1} \times f_{i-j}$。

展开一下 $P$，那么 $f_i = \sum_{j=1}^k \frac{(i-1)!}{(i-j)!} \times f_{i-j}$。若将 $(i-1)!$ 提出，$f_i = (i-1)! \times \sum_{j=1}^k \frac{f_{i-j}}{(i-j)!}$。

那么就简单了，递推做维护一个 $\frac{f_i}{i!}$ 的前缀和，这是好转移的。

```cpp
const int N = 1e7 + 19, mod = 998244353;
int ksm(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1LL * res * a % mod;
		a = 1LL * a * a % mod; b >>= 1;
	} return res;
}
int fac[N], inv[N], f[N], s[N];
void add(int &x, int y) {
	if ((x += y) >= mod) x -= mod;
}
void sub(int &x, int y) {
	if ((x -= y) < 0) x += mod;
}
signed main() {
	int n, k; read(n, k);
	fac[0] = inv[0] = 1;
	for (int i = 1; i < N; ++i) fac[i] = 1LL * i * fac[i-1] % mod;
	inv[N - 1] = ksm(fac[N - 1], mod - 2);
	for (int i = N - 2; i; --i) inv[i] = 1LL * inv[i+1] * (i + 1) % mod;
	f[0] = s[0] = 1;
	for (int i = 1; i <= n; ++i) {
		s[i] = f[i] = s[i - 1];
		if (i > k) sub(f[i], s[i - k - 1]);
		f[i] = 1LL * f[i] * fac[i-1] % mod;
		add(s[i], 1LL * f[i] * inv[i] % mod);
	} write(f[n]);
	return 0;
}
```

---

## 作者：wcy110614 (赞：1)

推式子。

先考虑不足以通过本题的 $\mathcal{O(n^2)}$ 式子。

发现从小到大填数并且记录方案可以顺利完成计数，方法如下：

1. 发现 $1$ 可以放进 $[1,k]$ 的位置，假设 $1$ 放在了 $p_1$ 位置。
2. 发现 $2$ 可以放进 $[1,p_1+k]$ 的位置，假设 $2$ 放在了 $p_2$ 位置。
3. 发现 $3$ 可以放进 $[1,\max\{p_1,p_2\}+k]$ 的位置，假设 $3$ 放在了 $p_3$ 位置。
4. ……

设 $f_{i,w}$ 为现在放了 $i$ 个数，并且下一个数可以放在 $[1,w]$ 的方案数。

那么 $f_{i,w}$ 可以由填 $i+1$ 的时候 $w$ 增长 $j\ (j\in[1,k])$ 转移过来。

状态转移方程如下：

$$f_{i,w}=\begin{cases}(w-k-i)f_{i+1,w}+\sum_{j=w+1}^{w+k}f_{i+1,\min\{j,n\}} & w\not=n\\ (i-1)f_{i+1,w} & w=n\end{cases}$$

这样前缀和随便处理处理就是 $\mathcal{O(n^2)}$ 的，$i$ 那一维可以滚掉，这样空间就是 $\mathcal{O(n)}$ 的了。

考虑优化。注意到当且仅当 $i$ 放在 $[w-k+1,w]$ 的时候 $f_{i,w}$ 才不会从 $f_{i+1,w}$ 转移过来。

设 $g_n$ 表示输入为 $n$ 时的答案。枚举 $1$ 放在 $j$ 位置的情况，发现如果放在 $j$ 位置，那么答案会是以下两种情况的积：

1. 在前面的 $j-1$ 个位置里面乱填数，除 $1$ 以外一共有 $n-1$ 个数，有 $A_{n-1}^{j-1}$ 种情形。
2. 填完 $1$ 以后，剩下的 $n-i$ 个位置转化为一个大小为 $n-i$ 的子问题。即有 $g_{n-i}$ 种情形。

所以，$g_n$ 就是取所有的 $j$ 的情况的和。

$$g_n=\sum_{j=1}^{\min\{n,k\}} A_{n-1}^{j-1}g_{n-j}=(n-1)!\sum_{j=1}^{\min\{n,k\}}\dfrac{g_{n-j}}{n-j}$$

这个时候前缀和处理一下就好了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e7+10,maxn=1e7;
const ll p=998244353;
ll fc[N],ifc[N],f[N],s[N];
int n,k;
inline ll qp(ll a,ll b=p-2){
	ll r=1;
	while(b){
		if(b&1)r=(r*a)%p;
		a=(a*a)%p, b>>=1;
	}
	return r;
}
int main(){
	cin>>n>>k,fc[0]=1;
	for(int i=1;i<=maxn;++i)fc[i]=fc[i-1]*i%p;
	ifc[maxn]=qp(fc[maxn]);
	for(int i=maxn-1;~i;--i)ifc[i]=ifc[i+1]*(i+1)%p;
	f[0]=s[0]=1;
	for(int i=1;i<=n;++i){
		f[i]=fc[i-1]*(s[i-1]-(i-min(i,k)-1>=0?s[i-min(i,k)-1]:0))%p;
		s[i]=(s[i-1]+f[i]*ifc[i])%p;
	}
	return cout<<(f[n]%p+p)%p<<"\n",0;
}
```

---

## 作者：Lyrella (赞：1)

# [P9823 [ICPC2020 Shanghai R] The Journey of Geor Autumn](https://www.luogu.com.cn/problem/P9823) 2024.11.20

## 简要题意

给定 $1\le k\le n$，我们规定满足下面性质的排列称为“好排列”：

$\forall k<i\le n,a_i>\min_{i-k\le j\le i-1}\{a_j\}$

求好排列的个数对 $998244353$ 取模。

**数据范围**：$1\le n\le 10^7$。

# 题解

看到这题首先有一个一眼的 $O(n^2)$ 暴力，我们设 $f_{i,j}$ 表示填到第 $i$ 个位置，已经填的最大的数为 $j$ 的方案数。然后考虑这一位怎么填。如果不填 $j$，就是 $f_{i,j}\leftarrow f_{i-1,j}\times(j-i+1)$；如果填 $j$，就是 $f_{i,j}=\sum_{l=j-k}f_{i-1,l}$。然后考虑第二个转移是一段区间，可以记录一个前缀和优化成 $O(n^2)$。

但是这个题数据范围卡的很死，显然是让你寻找线性做法。然后你会发现其实不管你怎么变化，只要第一维记录下标它就一定还需要记录别的东西。

引用大佬 $\text{max0810}$ 的话来说就是：

> 枚举下标没前途

所以果断转换第一维的状态，像这种计数题中还可以记录填的数是什么，因为题目中限制条件是大于某个数，所以我们**维护前缀最大值**。我们可以理解成把 $1$ 到 $i$ 之间的数撒在这个排列中合法的方案数。这样就可以做了！

我们设 $f_i$ 表示填了前 $i$ 个数的方案数。考虑假设我们已经填了前 $x$ 个数，下一个填什么？显然可以是 $x+1$ 到 $x+k$。假设我们在里面选择了一个数 $y$，那么对于 $x+1$ 到 $y-1$ 这些数的填法就没有了要求，对于这些数填入剩下位置的方案数就是 $A_{n-x-1}^{y-x-1}$。

然后我们的转移也就呼之欲出了：
$$
\forall j-k\le i<j,f_j\leftarrow f_i\times A_{n-i-1}^{j-i-1}
$$
这样虽然状态是 $O(n)$ 的，但是转移还是带了一个 $k$。于是考虑换一种写法，我们从前面的转移到后面，于是有：
$$
f_i=\sum_{i-k\le j<i}f_j\times A_{n-j-1}^{i-j-1}
$$
然后把后面的系数拆开：
$$
f_i=\sum_{i-k\le j<i}f_j\times\frac{(n-j-1)!}{(n-i)!}
$$
于是我们就记录 $f_j\times(n-j-1)!$ 的前缀和即可。

## 代码

```cpp
const int N = 1e7 + 5, p = 998244353;

int n, k;
ll f[N], g[N], fac[N], inv[N];

ll qmi(ll x, int y){
	ll res = 1;
	for(; y; y >>= 1, x = x * x % p)if(y & 1)res = res * x % p;
	return res;
}

int main(){
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	n = rd(), k = rd(); fac[0] = inv[0] = 1;
	for(int i = 1; i <= n; ++i)fac[i] = fac[i - 1] * i % p;
	inv[n] = qmi(fac[n], p - 2);
	for(int i = n - 1; i; --i)inv[i] = inv[i + 1] * (i + 1) % p;
	if(k == 1)return puts("1") & 0;
	for(int i = 1; i <= k; ++i)f[i] = fac[n - 1] * inv[n - i] % p;
	for(int i = 1; i <= n; ++i){
		if(i <= k)f[i] = (f[i] + g[i - 1] * inv[n - i]) % p;
		else f[i] = (f[i] + (g[i - 1] + p - g[i - k - 1]) * inv[n - i]) % p;
		g[i] = (g[i - 1] + f[i] * fac[n - i - 1]) % p;
	}
	wt(f[n]);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

首先 $1$ 必须填在前 $k$ 个位置。

不妨枚举 $1$ 填在 $p$ 位，那么 $[1,p)$ 可以随便填。

然后对于 $[p+1,x+k]$ 这一坨因为前面已经有了 $1$ 作为前缀最小值，所以它们都可以随便填。

然后就变成了一个 $n-p$ 的子问题，注意到这里的 $1$ 是在小于关系上的 $1$，即答案只跟数的数量有关，跟具体值无关。

因此定义 $f_i$ 表示长度未 $i$ 的方案数，有转移 $f_{i}\gets\sum\limits_{p=1}^{\min\{i,k\}}f_{i-p}(p-1)!C_{i-1}^{p-1}=\sum\limits_{p=1}^{\min\{i,k\}} f_{i-p}(p-1)!\dfrac{(i-1)!}{(p-1)!(i-p)!}=\sum\limits_{p=1}^{\min\{i,k\}}(i-1)!\dfrac{f_{i-p}}{(i-p)!}$。

然后用前缀和优化即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e7+5,mod=998244353;
int n,k,f[N],s[N],fac[N],inv[N];
int qpow(int a,int b){
	int s=1;
	while(b){
		if(b&1) s=s*a%mod;
		a=a*a%mod,b>>=1;
	}
	return s;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	fac[0]=1;
	for(int i=1;i<=n;++i) fac[i]=fac[i-1]*i%mod;
	inv[n]=qpow(fac[n],mod-2);
	for(int i=n-1;~i;--i) inv[i]=inv[i+1]*(i+1)%mod;
	f[0]=1,s[0]=1;
	for(int i=1;i<=n;++i){
		if(i<=min(n,k)) f[i]=s[i-1];
		else f[i]=(s[i-1]-s[i-min(n,k)-1]+mod)%mod;
		f[i]=f[i]*fac[i-1]%mod;
		s[i]=(s[i-1]+f[i]*inv[i])%mod;
	}
	cout<<f[n]<<endl;
	return 0;
}
```

---

## 作者：Laisira (赞：0)

### 思路
~~场上被爆切了。~~

显然的 $n^2$ 做法：

设选择的前缀最大数列为 $A$，则有 $f_{j}\times A_{n-i-1}^{i-j-1}\to f_{i}\ (p\leq\min(n,i+k))$。即在中间的 $i-j-1$ 个数插进 $j+1$ 到 $n$ 的那些数中。

然后发现从 $i$ 到 $i+1$ 变化只是组合数从 $A_{n-i-1}^{i-j-1}$ 变成 $A_{n-i}^{i-j}$，并如果存在 $i+k\leq n$ 则减少 $f_{i+k}$ 的贡献，新增 $f_{i}$ 的贡献。用前缀和优化一下即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
#define Maxn 10000005 
using namespace std;
const int mod = 998244353;
int f[Maxn];
int fsp(int x,int k) {
	int res = 1;
	while(k) {
		if(k&1)res = res*x%mod;
		x = x*x%mod,k >>= 1;
	} return res;
}
int fac[Maxn],fiv[Maxn];
void into() {
	fac[0] = 1;
	for(int i=1;i<Maxn;i++)
		fac[i] = fac[i-1]*i%mod;
	fiv[Maxn-1] = fsp(fac[Maxn-1],mod-2);
	for(int i=Maxn-1;i>0;i--)
		fiv[i-1] = fiv[i]*i%mod;
}
int C(int n,int m) {return fac[n]*fiv[m]%mod*fiv[n-m]%mod;}
int A(int n,int m) {return fac[n]*fiv[n-m]%mod;}
signed main()
{
	into();
	int n,k;
	cin>>n>>k;
	f[n] = 1;
	int pre = 1;
	for(int i=n-1;i>=0;i--) {
		f[i] = pre%mod;
		pre = ((pre*(n-i)%mod+f[i])%mod+(k+i <= n?(mod-f[i+k]*A(n-i,k)%mod):0)%mod)%mod;
	} cout<<f[0];
	return 0;
 } 
```

---

