# MEXimize the Score

## 题目描述

假设我们将数组 $b$ 的元素划分为任意数量 $k$ 个非空多重集 $S_1, S_2, \ldots, S_k$，其中 $k$ 是任意正整数。定义 $b$ 的得分为所有可能划分下 $\operatorname{MEX}(S_1) + \operatorname{MEX}(S_2) + \ldots + \operatorname{MEX}(S_k)$ 的最大值。

Envy 给你一个长度为 $n$ 的数组 $a$。由于他知道你计算 $a$ 的得分太容易了，因此他要求你计算 $a$ 的所有 $2^n - 1$ 个非空子序列的得分之和。由于答案可能很大，请你输出其对 $998\,244\,353$ 取模的结果。

$\operatorname{MEX}$（Minimum EXcluded number）是指在一组整数 $c_1, c_2, \ldots, c_k$ 中未出现的最小非负整数。例如，$\operatorname{MEX}([0,1,2,2]) = 3$，$\operatorname{MEX}([1,2,2]) = 0$。

一个序列 $x$ 是序列 $y$ 的子序列，如果 $x$ 可以通过从 $y$ 中删除若干（可能为零或全部）元素得到。

## 说明/提示

在第一个测试用例中，我们需要考虑七个子序列：

- $[0]$：得分为 $1$。
- $[0]$：得分为 $1$。
- $[1]$：得分为 $0$。
- $[0,0]$：得分为 $2$。
- $[0,1]$：得分为 $2$。
- $[0,1]$：得分为 $2$。
- $[0,0,1]$：得分为 $3$。

因此，第一个测试用例的答案为 $1+1+2+2+2+3=11$。在最后一个测试用例中，所有子序列的得分均为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
3
0 0 1
4
0 0 1 1
5
0 0 1 2 2
4
1 1 1 1```

### 输出

```
11
26
53
0```

# 题解

## 作者：Exp10re (赞：8)

感觉 CF 最近的 Div.2 都很喜欢出这种组合计数题。

不太喜欢啊，但是确实 E 放这种题的话我自己上分比较快。

## 解题思路

首先考虑对于给定的序列 $b$ 如何计算其分数：注意到每一个数至多对分数产生 $1$ 的贡献，考虑对数值统计贡献。

记 $c_i$ 表示 $b$ 中存在 $c_i$ 个 $i$，则数值为 $i$ 的数会对分数产生 $\min\limits_{j\leq i} c_j$ 的贡献，总分数为 $\sum\limits_{i=1}^{n} \min\limits_{j\leq i} c_j$。

记 $\min\limits_{i\leq k} c_i$ 为“考虑到值为 $k$ 的数时的有效值个数”，容易发现，根据该定义，值为 $k$ 的数贡献一定不超过考虑到值为 $k-1$ 的数时的有效值个数。

考虑动态规划。记 $f_{i,j}$ 表示考虑到值为 $i$ 的数时的有效值个数为 $j$ 的方案数，$ans_i$ 表示考虑到值为 $i$ 的数时的分数总和，$cnt_i$ 表示 $a$ 中存在 $cnt_i$ 个 $i$，$h_i$ 表示 $\min\limits_{j\leq i} cnt_j$。

分别计算方案数和分数和。首先考虑方案数，转移如下：

$$f_{i,j}=f_{i-1,j}(\sum\limits_{k=j}^{cnt_i} C_{cnt_i}^{k})+C_{cnt_i}^{j}(\sum\limits_{k=j+1}^{h_i} f_{i-1,k})$$

如何理解上述转移？记考虑到值为 $i-1$ 的数时的有效值个数为 $k_1$，值为 $i$ 的数取了 $k_2$ 个，则当 $k_1\leq k_2$ 时 $f_{i-1,k_1}C_{cnt_i}^{k_2}$ 会对 $f_{i,k-1}$ 产生贡献，否则会对 $f_{i,k_2}$ 产生贡献。

接下来考虑维护分数和，有如下转移：

$$ans_i=2^{cnt_i}ans_{i-1}+\sum\limits_{j=0}^{h_i}f_{i,j}j$$

前半部分 $2^{cnt_i}ans_{i-1}$ 表示取值为 $i$ 的数有 $2^{cnt_i}$ 种取法，前面没考虑到 $i$ 时的方案数翻 $2^{cnt_i}$ 倍，分数也要翻 $2^{cnt_i}$ 倍。

后半部分表示每一种考虑到值为 $i$ 的数时的有效值个数为 $j$ 的方案都会对分数产生 $f_{i,j}j$ 的贡献。

方案数的转移是 $O(n^2)$ 的，但是可以套一个后缀和优化做到 $O(\sum|c_i|)=O(n)$，分数的转移也是 $O(\sum|c_i|)=O(n)$，故总时间复杂度线性。

[Submission.](https://codeforces.com/contest/2030/submission/286811539)

---

## 作者：Zeoykkk (赞：6)

## CF2030E MEXimize the Score


定义数组 $b$ 的价值为将数组 $b$ 中的元素划分成 $k$ 个非空集合 $S_1, ...S_k$ 后 $\sum_{i = 1}^k\text{MEX}(S_i)$ 的最大值，其中 $k$ 为任意正整数。

给定数组 $a$，求 $a$ 的所有子序列价值之和。$n \leq 2\times 10^5, a_i < n$。

### Sol：计数 DP

对于数组 $a$ 来说，其价值为 $C_0 + \min(C_0, C_1) + ...+\min(C_0, C_1, ...,c_{n - 1})$，其中 $C_i$ 代表 $i$ 在 $a$ 中出现次数。

考虑每个 $\min(c_0, c_1, ..., c_i)$ 对答案的贡献，即有多少个子序列满足 $\min(c_0, c_1, ..., c_i) = x$，其中 $c_i$ 代表在子序列中 $i$ 的出现次数。

定义 $dp[i][j]$ 代表只包含 $[0, i]$ 的元素，且 $\min(c_0, c_1, ..., c_i) = j$ 的子序列数量，则有 $dp[0][j] = \binom{C_0}{j}$。

考虑转移，对于 $dp[i][j]$ 来说：

* 若加入元素 $i$ 后才使得 $\min(c_0, c_1, ..., c_i) = j$，即 $c_i = j,\min(c_0, c_1, ..., c_{i - 1}) > j$，则满足条件的子序列数量为 $(\sum_{k = j + 1}^{n - 1} dp[i - 1][k]) \times \binom{C_i}{j}$；
* 若加入元素 $i$ 前 $\min(c_0, c_1, ..., c_i) = j$ 已经成立，即 $c_i \geq  j, \min(c_0, c_1, ..., c_{i - 1}) = j$，则满足条件的子序列数量为 $\sum_{k = j}^{C_i}\binom{C_i}{k} \times dp[i  - 1][j]$。

虽然看似 $O(n^2)$ 的状态数，但是实际上对于第一维 $i$ 来说，第二维 $j$ 不会超过 $\min(C_0, C_1, ..., C_i)$，又因为 $\sum C_i = n$，所以状态数实际上是 $O(n)$ 的；

对于 $O(n)$ 的转移，我们通过后缀和优化成 $O(1)$ 即可。

当然 DP 求的是只包含 $[0, i]$ 的元素满足限制的子序列数量，对于 $[i + 1, n - 1]$ 的元素并没有考虑在内，因为这些元素影响是不影响 $\min(c_0, ..., c_i)$ 的，所以满足 $\min(c_0, c_1, ..., c_i) = j$ 的子序列数量最终为 $dp[i][j] \times 2^{C_{i + 1} + C_{i + 2} + ... + C_{n - 1}}$。

所以答案为 $\sum_{i, j} dp[i][j] \times 2^{C_{i + 1} + C_{i + 2} + ... + C_{n - 1}} \times j$。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
// #define int long long
#define pb push_back
#define endl '\n'
using ll = long long;
constexpr ll inf = 1ll << 60;
constexpr ll mod = 998244353;
const int N = 2e5 + 100;

/*
dp[i][j] 代表只包含 [0, i] 的数，且 min(c[0], c[1], ..., c[i]) = j 的子序列数量
显然有 dp[0][j] = C(c[0], j)
*/

inline void add(ll &a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}
inline ll mul(ll a, ll b) {
    a *= b;
    if (a >= mod) a %= mod;
    return a;
}
inline ll sub(ll a, ll b) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}
inline ll ksm(ll a, int b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
    }
    return res;
}

ll fac[N], inv[N], ifac[N];
inline void comb_init(int n) {
    fac[0] = 1, fac[1] = 1;
    inv[0] = 0, inv[1] = 1;
    ifac[0] = 1, ifac[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        ifac[i] = ifac[i - 1] * inv[i] % mod;
    }
}
inline ll binom(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int n, a[N];
void solve() {
    cin >> n;
    vector<int> c(n + 10);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        c[a[i]] += 1;
    }
    vector<ll> suf(n + 10);
    for (int i = n - 1; i >= 0; --i) suf[i] = suf[i + 1] + c[i];
    for (int i = 0; i < n; ++i) suf[i] = ksm(2, suf[i]);
    vector<vector<ll>> dp(n + 5);
    dp[0].resize(c[0] + 1, 0);
    for (int j = 0; j <= c[0]; ++j) dp[0][j] = binom(c[0], j);
    vector<ll> s(n + 10, 0);
    for (int i = c[0]; i >= 0; --i) s[i] = (s[i + 1] + dp[0][i]) % mod;
    int m = c[0];
    for (int i = 1; i < n; ++i) {
        m = min(m, c[i]);
        dp[i].resize(m + 1, 0);
        vector<ll> binom_sum(c[i] + 5, 0);
        for (int j = c[i]; j >= 0; --j) {
            binom_sum[j] = (binom_sum[j + 1] + binom(c[i], j)) % mod;
        }
        for (int j = 0; j <= m; ++j) {
            add(dp[i][j], mul(s[j + 1], binom(c[i], j)));
            add(dp[i][j], mul(binom_sum[j], dp[i - 1][j]));
        }
        s[m + 1] = 0;
        for (int j = m; j >= 0; --j) s[j] = (s[j + 1] + dp[i][j]) % mod;
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int sz = dp[i].size();
        for (int j = 1; j < sz; ++j) {
            add(ans, mul(mul(dp[i][j], j), (suf[i + 1] == 0 ? 1 : suf[i + 1])));
        }
    }
    cout << ans << endl;
}
signed main(void) {
    comb_init(200010);
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int Test = 1;
    cin >> Test;
    while (Test--) solve();
    return 0;
}
```

---

## 作者：Twig_K (赞：5)

### 题意

- 一个序列 $b$ 的**划分** $S_1,S_2,\cdots,S_k$，定义这个**划分的权值**为所有集合 mex 之和（一个集合的 mex 是最小的不在集合中的非负整数）。
- 定义一个**序列的权值**为，它的所有划分方案中，权值的最大值。
- 给你一个序列 $a$，求 $a$ 的所有**子序列的权值之和**。

-----------------

### 做法

~~写得好长，废话好多啊。~~

先考虑如何划分，使得一个序列的权值最大。

**对于所有 mex 不为 $0$ 的集合，使它的元素是从 $0$ 开始的连续自然数，一定不会更劣。**
如果 $S=\{0,1,2,\cdots,x,m\}$ 且 $m \not= x+1$，不论 $m$ 与 $x$ 的大小关系如何，$m$ 是否在集合中并不会改变这个集合的答案，而如果不把 $m$ 加入 $S$，$m$ 反而有一定可能给别的集合做贡献。

所以对于单个序列的权值，我们可以贪心地将尽可能多的元素纳入某些从 $0$ 开始的序列中。这样，构造出的所有 mex 不为 $0$ 的集合，**mex 值就是元素个数。**

如 $\{0,0,1,2,2,2\}$，选出 $\{0,1\}$ 和 $\{0,1,2\}$，剩下没用的 $\{2,2\}$ 扔一边。 

对于 mex 不为 $0$ 的集合 $\{0,1,\cdots,x\}$，加入 $x+1$ 这个数时，$x+1$ 对当前集合产生了 $1$ 的贡献。

-----------------

赛时一开始是这么想的：对于一个数 $x$，它对全局产生的贡献为 $p \times 2^q$，其中 $p$ 为每种小于 $x$ 的数至少选一个的方案数，$q$ 为输入序列中大于 $x$ 的数的个数（比 $x$ 大的随便选不选 $x$ 都有贡献）。结果发现一个数 $x$ 可能会出现多次，相同的数之间很难不重不漏。

----------
所以换一下思路，将同一种数放在一起考虑。

设第 $k$ 种数出现次数为 $cnt_k$，这 $cnt_k$ 个 $k$ 中有若干个会产生贡献，枚举**产生贡献的** $k$ 的个数为 $i$。

如果 $mn=\min_{j=1}^{k}cnt_j$，$k$ 最多产生 $mn$ 的贡献。对于数 $k$ 产生 $i$ 个数的贡献有两种情况：
- $k$ 只选了 $i$ 个，前面的 $1$ 到 $k-1$ 每种数都至少选 $i$ 个。设为 $r_1$。
- $k$ 选了**至少** $i+1$ 个，前面 $1$ 到 $k-1$ 每种数至少选 $i$ 个且必须存在数恰好选 $i$ 个（即前面所有数至少选 $i$ 个的方案数，减去前面所有数至少选 $i+1$ 个的方案数）。设为 $r_2$。

此外，对于大于 $k$ 的每个数，都可以选或不选。所以总贡献为 $i \times (r_1+r_2) \times 2^q$，$q$ 的意义同前。

--------

实现上主要是处理各种前缀的值，会有一些细节，注释在代码里。

### 代码

```cpp
#include<bits/stdc++.h>
#define For(i,il,ir) for(register int i=il;i<=ir;++i)
#define Forr(i,ir,il) for(register int i=ir;i>=il;--i)
using namespace std;
typedef long long ll;
const ll mod=998244353;
const int maxn=2e5+10,int N=200001;

int n,a[maxn],cnt[maxn];
ll num[maxn],fac[maxn],inv[maxn],pw[maxn];
ll qp(ll x,int base){ ll res=1ll; while(base){ if(base&1) res=res*x%mod; x=x*x%mod,base>>=1; }return res; }
ll C(int x,int y){ return y==0?1ll:(fac[x]*inv[y]%mod*inv[x-y]%mod); }
void solve()
{
	scanf("%d",&n);
	For(i,0,n+1) cnt[i]=num[i]=0;
	For(i,1,n) scanf("%d",&a[i]),++cnt[a[i]];
	ll ans=0ll;
	//因为怕想不清楚，干脆把 0 拿出来单独考虑了 
	int sum=cnt[0];//sum：每种数个数的前缀和 
	num[0]=pw[cnt[0]];//num[i]：当前考虑过的所有数，每种数至少选择 i 个，方案数。 
	ll lst=pw[cnt[0]];//lst：现在正在考虑的这种数（即 0），至少选择 i 个的方案数（lst 随着 i 的增大，在循环中不断减小） 
	For(i,1,cnt[0]+1)//枚举产生贡献的 0 的个数 
	{
		ll CC=C(cnt[0],i);
		lst=(lst-C(cnt[0],i-1)+mod)%mod;//现在至少选择 i 个 0，跟前一次循环比，减去选择 i-1 个 0 的方案数 
		if(i<=cnt[0]) ll tmp=i*CC%mod*pw[n-sum]%mod,ans=(ans+tmp)%mod; // i：有 i 个 0 产生贡献（即这些方案总贡献为 i）；CC：在 cnt[0] 个 0 种选择 i 个的情况数；pw：大于 0 的数随便选不选 
		num[i]=lst;
	}
	int mn=cnt[0];// mn：cnt 数组的前缀 min 
	for(int k=1;k<=n&&mn;k++)//（没什么用的顺带的优化）当 mn==0 时，有一种数一个都没有，后面一定不可能连起来了
	{
		ll lst=pw[cnt[k]];//lst：现在正在考虑的这种数（即 k），至少选择 i 个的方案数（lst 随着 i 的增大，在循环中不断减小）
		num[0]=num[0]*lst%mod,sum+=cnt[k],mn=min(cnt[k],mn);//num[i] 就是前面所有种类，对应 lst 的积）。 
		For(i,1,mn+1)
		{
			ll CC=C(cnt[k],i);lst=(lst-C(cnt[k],i-1)+mod)%mod;//更新 lst 
			if(i<=mn){
				ll lst2=(lst-CC+mod)%mod;// lst2 就是 lst 再算一遍（至少选择 i+1 个） 
				ll cct=(CC*num[i]%mod+(num[i]-num[i+1]+mod)%mod*lst2%mod)%mod;
				//cct：能产生贡献的个数（方案数），由两部分组成：
					//1. 第 k 种数恰好选 i 个，前面每种数至少选 i 个；
					//2. 第 k 种数选择（严格）大于 i 个（lst2），前面每种数至少选 i 个且必须有数选择恰好 i 个（所以是 num[i]-num[i+1]） 
				ll tmp=i*cct%mod*pw[n-sum]%mod;
				ans=(ans+tmp)%mod;
			}
			num[i]=lst*num[i]%mod;//更新 num 
		}
	}printf("%lld\n",ans);
}
signed main()
{
	fac[0]=1ll; For(i,1,N) fac[i]=fac[i-1]*(ll)i%mod;
	inv[N]=qp(fac[N],mod-2); Forr(i,N-1,0) inv[i]=inv[i+1]*((ll)i+1ll)%mod;
	pw[0]=1ll;For(i,1,N) pw[i]=pw[i-1]*2ll%mod;
	int T;read(T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：NahX_ (赞：3)

首先考虑转化一下分值，容易发现题目中的 $\operatorname{MEX}(S_1)$  $ + \operatorname{MEX}(S_2) + \ldots + \operatorname{MEX}(S_k)$ 手玩一下就能发现让分值最大的策略就是每次让 $\operatorname{MEX}$ 尽量大，所以可以把分值转化为 $\sum \min\{cnt_i,\min_{j=1}^{i-1}cnt_j\}$，其中 $cnt_i$ 为数组 $b$ 中数 $i$ 的出现次数。

设计朴素的 dp，设 $f_{i,j},g_{i,j}$ 分别表示第 $i$ 个数有 $j$ 个 **取到答案中** 的所有方案的总和以及方案数，转移：
$$
f_{i,j}\to \sum_{k=j+1}^{cnt_{i-1}}f_{i-1,k}+j\cdot g_{i-1,k}\\
g_{i,j}\to sum_{k=j+1}^{cnt_{i-1}}g_{i-1,k}
$$ 

其中 $j=k$ 的情况需要特殊处理因为此时无论取多少个 $i$，只要个数大于 $j$，与 $k$ 取 $\min$ 后仍然是取 $j$ 个也要算入 $f_{i,j}$ 中，也就是 $f_{i,j}\to (f_{i,j}+f_{i-1,j}+j\cdot g_{i-1,j})\cdot C,g_{i,j}\to g_{i,j}+g_{i-1,j}\cdot C$ 其中 $C$ 为在 $cnt_i$ 中任意至少取 $j$ 个的组合数。

这样是最坏时间复杂度约为 $O(n^2)$。

然后发现 $f,g$ 的转移过程显然能用后缀和优化且 $g_i$ 为 $g_{i-1}$ 的后缀和，转移方程转为 
$$
f_{i,j}\to sf_{cnt_{i-1}}-sf_{j}+j\cdot(sg_{cnt_{i-1}}-sg_{j})\\
g_{i,j}\to sg_{cnt_{i-1}}-sg_{j}
$$

其中 $sf,sg$ 为 $f_{i-1},g_{i-1}$ 的前缀和。

因为元素出现次数和为 $n$，所以这样优化后就是 $O(n)$，注意取模。

---

## 作者：KazamaRuri (赞：3)

给一种我考场上的更为巧妙的做法。

## 前情

被 [dadaaa](https://www.luogu.com.cn/user/415354#main) 搬到模拟赛，耗尽浑身解数惊险战胜（其实是 T1 没能一眼切，先凹这题了）。

## 分析

首先转化题意，考虑我从草稿纸上搬下来的这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ip8esq5.png)

图中表示每个元素的出现次数。

显然的，这个集合划分 mex 之和最大应该是：

$$$
1+4+5=10
$$$

如果从每个数对 mex 的贡献来说，贡献式子应该形如前缀最小值累加的形式：

$$$
3+2+2+2+1=10
$$$

欸 ~ 前缀最小值。那么我们有新的形式化题面了：

给定长度为 $n$ 的序列 $a$，其约束了另一个长为 $n$ 的序列 $b$，满足 $b_i \in [0,a_i]$，且 $b_i=x$ 的概率为 $\frac {a_i \choose x } {2^{a_i}}$。求前缀最小值累加和的期望。保证 $\sum a_i =n$。

做到这一步很多人都能秒掉了。

当然原题肯定不是求概率和期望啦，而是每种方案的和，概率其实是方案数。

设 $f_i$ 表示前缀最小值为 $i$ 的累加和，$g_i$ 为前缀最小值为 $i$ 的方案数。默认滚动数组，记上一轮的值为 $f'_i,g'_i$，数的上界为 $a,a'$。

先说 $g_i$ 怎么推：

1.  如果上一轮最小值已经为 $i$，那么这一轮最小值还要为 $i$ 的话，那只要让当前的数 $\ge i$ 就好了吧,这样最小值就不会变了。对吧对吧，这部分方案数为：

$$$
(\, \sum^{a}_{k=i} {a \choose k} \, )\ \cdot\ g'_i
$$$

2.  只剩下~~钢琴陪我谈了一天~~最小值从 $>i$ 到当前的数恰好变小成 $i$ 的方案数了，也就是：

$$$
{a \choose i}\ \cdot\ (\, \sum^{a'}_{k=i+1} g'_k\, )
$$$

综上：

$$$
g_i=(\, \sum^{a}_{k=i} {a \choose k} \, )\ \cdot\ g'_i \  +  \ {a \choose i}\ \cdot\ (\, \sum^{a'}_{k=i+1} g'_k\, )
$$$

$i$ 的对答案的贡献次数就是 $g_i$，类似地，我们有:

$$$
f_i=(\, \sum^{a}_{k=i} {a \choose k} \, )\ \cdot\ f'_i \  +  \ {a \choose i}\ \cdot\ (\, \sum^{a'}_{k=i+1} f'_k\, )\ +\ i \cdot g_i
$$$

（注意有没有带 $'$ 哦）

最后 $ans=f_0$。

## 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+5,mod=998244353,maxn=1e6;
ll n,a[N],f[N],g[N],suff[N],sufg[N],sufc[N],fac[N],ifac[N];
ll qp(ll x,int y){ ll res=1; for(;y;y>>=1,x=x*x%mod) if(y&1) res=res*x%mod; return res; }
inline ll C(int n,int m){ return n>m?0:fac[m]*ifac[n]%mod*ifac[m-n]%mod; }
void solve(){
	scanf("%lld",&n);
	for(int i=1,x;i<=n;i++)
		scanf("%d",&x),a[x]++;
	ll v=a[0];
	for(int i=0;i<=v;i++)
		f[i]=(g[i]=C(i,v))*i%mod;
	for(int i=v;~i;i--)
		suff[i]=(suff[i+1]+f[i])%mod,
		sufg[i]=(sufg[i+1]+g[i])%mod;
	for(int k=1;k<=n;k++){
		v=min(v,a[k]),sufc[a[k]+1]=0;
		for(int i=a[k];~i;i--)
			sufc[i]=(sufc[i+1]+C(i,a[k]))%mod;
		for(int i=0;i<=v;i++){
			g[i]=(C(i,a[k])*sufg[i+1]%mod+g[i]*sufc[i]%mod)%mod,
			f[i]=(C(i,a[k])*suff[i+1]%mod+f[i]*sufc[i]%mod+i*g[i]%mod)%mod;
		}
		suff[v+1]=sufg[v+1]=0;
		for(int i=v;~i;i--)
			suff[i]=(suff[i+1]+f[i])%mod,
			sufg[i]=(sufg[i+1]+g[i])%mod;
		for(int i=v+1;i<=a[k];i++)
			f[i]=g[i]=sufc[i]=suff[i]=sufg[i]=0;
	}
	printf("%lld\n",f[0]);
	for(int i=0;i<=n+1;i++)
		f[i]=g[i]=suff[i]=sufg[i]=sufc[i]=a[i]=0;
}
int main(){
	fac[0]=1;
	for(int i=1;i<=maxn;i++)
		fac[i]=fac[i-1]*i%mod;
	ifac[maxn]=qp(fac[maxn],mod-2);
	for(int i=maxn;i;i--)
		ifac[i-1]=ifac[i]*i%mod;
	int T; scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Xy_top (赞：3)

想到了但是没写完，错失 M 机会 /kk

令 $h(a)$ 为序列 $a$ 的分数，先考虑单个 $h$ 怎么做，显然把每个 $0$ 单独分开，假设有 $i$ 个 $0$，那么分成 $i$ 个集合。如果 $1$ 的数量大于 $0$ 的数量，那就往所有 $0$ 后面都放一个 $1$，否则把所有 $1$ 都放在不同的 $0$ 后面，依次类推。

发现 $1$ 的数量多于 $0$ 的数量时，除了对方案数有贡献，对 $h$ 值是无法贡献的，于是考虑从这里下手，模拟求 $h$ 的过程。

设 $f_{i,j}$ 为 $0$ 到 $i$ 这些数字，当前形成了 $j$ 个集合的 $h$ 函数和，再令 $g_{i,j}$ 为 $0$ 到 $i$ 这些数字，形成 $j$ 个集合的方案数。

转移时枚举上一次有 $k$ 个集合，显然 $k$ 应 $\geq j$，如果 $k=j$，剩下的那些随便选然后随便插，如果 $k>j$，那么只能选 $j$ 个插到任意一些集合的后面，对答案贡献了 $j$。

这样是 $O(n^2)$ 的，考虑前缀和优化，优化后足以通过此题：


```cpp
#include <bits/stdc++.h>
#define int long long
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n;
int a[200005], b[200005], sum[200005];
int s1[200005], s2[200005];
int f[2][200005], g[2][200005];
int fac[200005], inv[200005];
const int mod = 998244353;
int q_pow (int x, int y) {
	if (y == 0) return 1;
	if (y & 1) return x * q_pow (x * x % mod, y >> 1) % mod;
	return q_pow (x * x % mod, y >> 1);
}
void init () {
	fac[0] = 1;
	For (i, 1, 200000) fac[i] = fac[i - 1] * i % mod;
	inv[200000] = q_pow (fac[200000], mod - 2);
	foR (i, 199999, 0) inv[i] = inv[i + 1] * (i + 1) % mod;
}
int C (int n, int m) {return fac[n] * inv[m] % mod * inv[n - m] % mod;}
void solve () {
	int mx = 0;
	cin >> n;
	For (i, 0, n) b[i] = 0;
	For (i, 1, n) {
		cin >> a[i];
		mx = max (mx, a[i]);
		++ b[a[i] ];
	}
	For (i, 1, b[0]) {
		g[0][i] = C (b[0], i);
		f[0][i] = g[0][i] * i % mod;
	}
	//每个数字都有 (i + 1) 种选择，要求 i 个组都要有东西
	//要求每个子序列都最优，所以不可能对 0 分到相同的组
	For (i, 1, mx) {
		int t = i & 1;
		sum[0] = 1;
		For (j, 1, b[i]) sum[j] = (sum[j - 1] + C (b[i], j) ) % mod;
		For (j, 0, b[i]) f[t][j] = g[t][j] = 0;
		s1[0] = f[t ^ 1][0];
		For (j, 1, b[i - 1]) s1[j] = (s1[j - 1] + f[t ^ 1][j]) % mod;
		s2[0] = g[t ^ 1][0];
		For (j, 1, b[i - 1]) s2[j] = (s2[j - 1] + g[t ^ 1][j]) % mod;
		For (j, 0, min (b[i], b[i - 1]) ) {
			int res = sum[b[i] - j];
			f[t][j] = (f[t][j] + f[t ^ 1][j] * res % mod + g[t ^ 1][j] * res % mod * j % mod) % mod;
			g[t][j] = (g[t][j] + g[t ^ 1][j] * res) % mod;
			int r1 = (s1[b[i - 1] ] - s1[j] + mod) % mod, r2 = (s2[b[i - 1] ] - s2[j] + mod) % mod;
			f[t][j] = (f[t][j] + r1 * C (b[i], j) % mod + r2 * C (b[i], j) % mod * j % mod) % mod;
			g[t][j] = (g[t][j] + r2 * C (b[i], j) % mod) % mod;
		}
	}
	int t = mx & 1, ans = 0;
	For (i, 0, b[mx]) ans = (ans + f[t][i]) % mod;
	For (i, 0, n) f[0][i] = g[0][i] = f[1][i] = g[1][i] = 0;
	cout << ans;
}
signed main () {
	init ();
	int _ = 1;
	cin >> _;
	while (_ --) {
		solve ();
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Moeebius (赞：2)

由于下午 ucup K 题柿子推得过于热火朝天了，我们再次考虑推柿子。

还是考虑算贡献，容易发现大小为 $v$ 的数中，**被选上** 的第 $i$ 个数对答案有 $1$ 的贡献当且仅当 $[0, v)$ 中每个数都被选了至少 $i$ 个。到这里可以直接 DP，但是我们坚持推柿子！！！

记 $tot$ 为 $\ge v$ 的数的个数，$c_i$ 为大小为 $i$ 的数的个数。不难发现，大小为 $v$ 的数的总贡献为：

$$
\text{Ans} = \sum_{i=0}^{c_v-1}2^{tot-i-1}\sum_{j=0}^{i}\binom{i}{j}\prod_{k=0}^{v-1}\sum_{o=j+1}^{v_k}\binom{c_k}{o}
$$

看起来很吓人对不对，但是冷静分析一下：

$$
\text{Ans}=2^{tot-1}\sum_{j=0}^{c_v-1}\red{\sum_{i=0}^{c_v-1}(\frac{1}{2})^{i}\binom{i}{j-1}}\cdot\blue{\prod_{k=0}^{v-1}\sum_{o=j}^{v_k}\binom{c_k}{o}}
$$

蓝色部分可以每次预处理，所以我们只要能在一个合理的时间内，对于一个 $j$ 算出红色部分就做完了！！！

相当于有 $f(n,m)=\sum_{i=0}^{n-1}z^i\binom{i}{m}$，其中 $z$ 是一个不为 $1$ 的常数，我们需要求出某一行（即：$n$ 均相同）的值。

还是考虑拆组合数：

$$
\begin{aligned}
f(n,m)&=\sum_{i=0}^{n-1}z^i[x^m](x+1)^i \\
&= [x^m]\sum_{i=0}^{n-1}z^i(x+1)^i \\
&= [x^m]\frac{1-(z(x+1))^n}{1-z(x+1)}
\end{aligned}
$$

多项式求逆即可 $O(m \log m)$ 求一行。

代码可以见[这里](https://codeforces.com/contest/2030/submission/287062110)。

~~cxy 说可以找整式递推做到线性，先咕了。~~

upd: 会了。

不用啥高深的科技，我们直接考虑拆组合数。

$$
\begin{aligned}
f(n,m)&=\sum_{i=0}^{n-1}z^i\binom{i}{m} \\
&= \sum_{i=0}^{n-1}z^i(\binom{i-1}{m-1}+\binom{i-1}{m}) \\
&= (z\sum_{i=0}^{n-1}z^i\binom{i}{m-1})+(z\sum_{i=0}^{n-1}z^i\binom{i}{m})-z^n(\binom{n-1}{m}+\binom{n-1}{m-1}) \\
&= z\cdot f(n, m-1)+z\cdot f(n,m)-z^n(\binom{n-1}{m}+\binom{n-1}{m-1})
\end{aligned}
$$

又因为 $z\neq 1$，故有

$$
f(n,m)=\frac{z\cdot f(n,m-1)-z^n(\binom{n-1}{m}+\binom{n-1}{m-1})}{1-z}
$$

$O(m)$ 递推即可。[代码](https://codeforces.com/contest/2030/submission/287162494)。

---

## 作者：Luzhuoyuan (赞：2)

赛后一分钟调出 E，What can I say.

首先考虑一个序列的得分怎么算。相当于每次取出从 $0$ 开始的一段最长的连续的权值并分到同一组，直到不能分为止，剩下的那些数任意分到一组。设 $a_i$ 表示值 $i$ 的出现次数，$mn_i$ 为 $a_i$ 的前缀最小值，则枚举 mex 值对应的集合数量，得分为

$$\sum\limits_{i=1}^{n}i(mn_{i-1}-mn_i)=\sum\limits_{i=0}^{n-1}(i+1)mn_i-\sum\limits_{i=0}^{n-1}i\cdot mn_i=\sum\limits_{i=0}^{n-1}mn_i$$

考虑对于每个 $mn_i$ 分别统计其贡献。先求出整个序列的 $mn$ 序列，之后对于每个值 $i$，在 $[0,mn_i]$ 中枚举一个值 $mn'$ 表示选出的子序列中要使得 $mn_i=mn'$，考虑满足的方案数。

对于大于 $i$ 的值，它们取的数量与 $mn'$ 无关，贡献为 $2^{\sum_{j=i+1}^{n-1}a_i}$。对于小于 $i$ 的值，有两种情况：

- 若 $a'_i=mn'$，那么前面只要全都不小于 $mn'$ 就可以随便取，方案数为 $\prod\limits_{j=0}^{i-1}\sum\limits_{k=mn'}^{a_j}\binom{a_j}{k}$。
- 若 $a'_i>mn'$，那么前面必须存在至少一个 $a'_j=mn'$，这个可以简单容斥，相当于就是“全都大于等于 $mn'$ 的方案数”减去“全都大于等于 $mn'+1$ 的方案数”。

设 $v_x=\sum\limits_{j=x}^{a_i}\binom{a_i}j,f_x=\prod\limits_{j=0}^{i-1}\sum\limits_{k=x}^{a_j}\binom{a_j}{k},g_i=2^{\sum_{j=i}^{n-1}a_j}$，则 $mn'$ 的总贡献为

$$mn'\cdot g_{i+1}\cdot (f_{mn'}\cdot\binom{a_i}{mn'}+(f_{mn'}-f_{mn'+1})\cdot v_{mn'+1})$$

$g_i$ 可以直接预处理，那么如何维护 $f,v$ 呢？考虑 $\sum\limits_{i=x}^{y}\binom y i=2^y-\sum\limits_{i=0}^{x-1}\binom y i$，我们在从小到大枚举 $mn'$ 的时候可以顺便转移 $v_{j+1}=v_j-\binom{a_i}j$，每次再把 $v$ 乘到 $f$ 上即可。

时间复杂度为 $O(\sum mn_i)=O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=2e5+5,V=2e5,mod=998244353;
int _,n,x,a[N],mi2[N],mn[N],fc[N],ifc[N],f[N],g[N],ans;
inline int ksm(int x,int y){int z=1;while(y){if(y&1)z=z*x%mod;x=x*x%mod,y>>=1;}return z;}
inline int C(int x,int y){if(x<y||y<0)return 0;return fc[x]*ifc[y]%mod*ifc[x-y]%mod;}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>_;
	fc[0]=1;for(int i=1;i<=V;i++)fc[i]=fc[i-1]*i%mod;
	ifc[V]=ksm(fc[V],mod-2);for(int i=V;i;i--)ifc[i-1]=ifc[i]*i%mod;
	mi2[0]=1;for(int i=1;i<=V;i++)mi2[i]=(mi2[i-1]<<1)%mod;
	while(_--){
		cin>>n;ans=0;
		for(int i=1;i<=n;i++)cin>>x,a[x]++;
		mn[0]=a[0];for(int i=1;i<n;i++)mn[i]=min(mn[i-1],a[i]);
		g[n]=1;for(int i=n-1;~i;i--)g[i]=g[i+1]*mi2[a[i]]%mod;
		f[n+1]=0;for(int i=0;i<=n;i++)f[i]=1;
		for(int i=0;i<n;i++){
			int v=mi2[a[i]];
			for(int j=0;j<=mn[i];j++)
				ans=(ans+j*g[i+1]%mod*(f[j]*C(a[i],j)%mod+(f[j]+mod-f[j+1])*(v+mod-C(a[i],j))%mod))%mod,
				f[j]=f[j]*v%mod,v=(v+mod-C(a[i],j))%mod;
			f[mn[i]+1]=f[mn[i]+1]*v%mod;
		}
		cout<<ans<<'\n';
		for(int i=0;i<n;i++)a[i]=0;
	}
}
```

（逃

---

## 作者：wptt (赞：1)

先考虑这个最大值是怎么算的，设 $cnt_i$ 表示数字 $i$ 的数量，那么一个数组 $a$ 最大的贡献就是 $\sum\limits_{i = 0} ^ {n} \min\limits_{j = 1} ^ i cnt_j$。

现在就对 $cnt_j$ 进行计数，$f(i, j)$ 表示前 $i$ 个最小 $cnt$ 值为 $j$ 的方案数。

$$
f(i, j) = f(i - 1, j) \times \sum\limits_{k \ge j} {cnt_i \choose k} + \sum\limits_{k > j} f(i - 1, k) \times {cnt_i \choose k}
$$
最终答案统计。

$$
ans = \sum\limits_{i = 0} ^ n 2 ^ {n - \sum\limits_{j = 0} ^ n cnt_j}\sum\limits_{j = 1} ^ {\min\limits_{k = 0} ^ i cnt_k}  f(i, j) \times j
$$

预处理后缀组合数的和以及使用前缀优化复杂度可以做到 $\mathcal{O}(\sum cnt_i) = \mathcal{O}(n)$。

---

## 作者：WRuperD (赞：1)

# CF2030E MEXimize the Score 题解

[本题解同步发表于我的个人博客之中](https://wruperd.github.io/post/2024-10-22-solution-cf2030e/)

上 CM 了，纪念一下。

考虑从小到大对于每一种数字算贡献。

设 $f_{i,j}$ 表示有 $j$ 个 $a_x = i$ 对答案产生了 1 的贡献的方案数。那么显然有:

$$f_{i,j} = \sum \limits_{k > j} f_{i-1,k}\cdot{cnt_i \choose j} + f_{i-1,j}\cdot \sum \limits_{k\geq j} {cnt_i \choose k}$$

那么最后的答案就是 $\sum f_{i,j} \cdot j$。

乍一看这个柿子是 $O(n^2)$ 的对吧，但是实际上首先转移可以前缀和优化做到 $O(1)$，其次有效注意到第二维是有一个上界为 $\min \limits_{j\leq i} (cnt_j)$ 的，而 $\sum cnt_i = n$。那么这样子其实第二维的有效状态数就是  $O(n)$ 的了。直接写就完事了。 

```cpp
// Problem: E. MEXimize the Score
// URL: https://codeforces.com/contest/2030/problem/E
// Writer:WRuperD
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')	
#define endl puts("")
const int MAX = 2e5 + 10;
const int mod = 998244353;

int cnt[MAX];
int f[MAX];
int pre2[MAX];

int preasd[MAX];
int inv123[MAX];
int F114[MAX];

int a[MAX];

int quickPower(int a,int b,int p){int base=a,ans=1;while(b){if(b&1)ans*=base,ans%=p;base*=base;base%=p;b>>=1;}return ans;}
 
int c2(int n, int m){
	if(m > n)	return 0;
	return preasd[n] * F114[m] % mod * F114[n-m] % mod;
}

void solve(){
	
	
	
	int n = read();
	pre2[0] = 1;
	for(int i = 1; i <= n; i++){
		pre2[i] = pre2[i - 1] * 2 % mod;
		a[i] = read();
		cnt[a[i]]++;
	}
	int premin = n;
	for(int i = 0; i <= n + 1; i++)	f[i] = 0;
	f[n] = 1;
	int ans = 0;
	int pree2 = n;
	for(int i = 0; i < n; i++){
		if(!cnt[i]){
			break;
		}
		int pre = 0;
		pree2 = pree2 - cnt[i];
		int pree3 = 0;
		for(int j = premin + 1; j <= cnt[i]; j++){
			pree3 = (pree3 + c2(cnt[i], j)) % mod;
		}
		for(int j = premin; j >= 1; j--){
			int prefj = f[j];
			f[j] = pre * c2(cnt[i], j) % mod;
			pree3 = (pree3 + c2(cnt[i], j)) % mod;
			f[j] = (f[j] + prefj * pree3 % mod) % mod;
			pre = (pre + prefj) % mod;
			// write(i), put(), write(j), put(), write(ans), put(), write(f[j]), put(), write(pree2), endl;	
			ans = (ans + f[j] * pre2[pree2] % mod * j  % mod) % mod;
		}
		premin = min(premin, cnt[i]);
	}
	for(int i = 0; i <= n; i++)	cnt[i] = 0;
	write(ans), endl;
}

signed main(){
	preasd[0] = F114[0] = 1;
	preasd[1] = inv123[1] = F114[1] = 1;
	for(int i = 2; i < MAX; i++){
		preasd[i] = 1ll * preasd[i - 1] * i % mod;
		inv123[i] = 1ll * inv123[mod % i] * (mod - mod / i) % mod;
		F114[i] = 1ll * F114[i - 1] * inv123[i] % mod;
	}
	int t = read();
	while(t--)	solve();
	return 0;
}
```

---

## 作者：A2_Zenith (赞：0)

CFvp 两个小时，于 1：59：27 通过此题。

首先考虑一个集合 $S$ 的权值怎么算。贪心，发现相同的数分配到不同的集合里是更优的。比如说我们有两个 $0$，就设置两个集合把这两个 $0$ 放进去。设 $c_i = \sum\limits_{x \in S}[x=i]$，那么集合的权值就是 $\sum\limits_{i=0}^{n-1}\min\limits_{j=0}^ic_j$。

然后所有子序列的权值之和肯定只和整个序列中某个元素的出现次数有关。令 $C_x = \sum\limits_{i=1}^n[a_i=x]$ 不难列出柿子，答案为

$$\sum\limits_{e_0=0}^{C_0}\sum\limits_{e_1=0}^{C_1} \cdots \sum\limits_{e_{n-1}=0}^{C_{n-1}}\prod\limits_{j=0}^{n-1}\dbinom{C_j}{e_j}\sum\limits_{k=0}^{n-1}\min\limits_{p=0}^k e_p$$

这玩意直接入手肯定是巨大难算的。

考虑计算贡献，直接考虑计算 $\min\limits_{k=0}^xe_x = p(x \in [0,n),p \in [0,C_{x}])$。

在 $x$ 后面的决策肯定是不会对 $x$ 本身的决策产生影响的。计一手 $S_x = \sum\limits_{i=x}^{n-1}cnt_i$，那么贡献有一个 $2^{S_{x+1}}$。

再考虑 $x$ 前面的决策。我们不妨令 $P_{x,i}$ 为使 $\min\limits_{k=0}^x e_k \ge i$ 的方案数，$Suf_{x,i} = \sum\limits_{j=i}^{C_x}\dbinom{C_x}{j}$。那么前面的方案数是 $P_{x,i}\dbinom{C_x}{i} + Suf_{x,i}(P_{x,i}-P_{x,i+1})$。两部分分别为计算 $e_x =i$ 与 $e_x > i,\min\limits_{k=0}^{x-1}e_k =i$ 的方案数。

最终贡献就是这两部分乘起来。可以精细实现做到 $\mathcal{O}(\sum\limits_{i=0}^{n-1}C_i) = \mathcal{O}(n)$。

细节比较多，调了挺久。不过样例挺强的。


```cpp
#include<bits/stdc++.h>
#define int long long
#define doub long double
#define PII pair<int,int>
#define fir first
#define sec second
#define ctz __builtin_ctzll
#define PC __builtin_popcount
#define clz __builtin_clzll
using namespace std;
const int N=1e6+7;
const int mod=998244353;
int n;
int a[N];
int cnt[N];
int Fac[N],iFac[N];
inline void Init(){
    Fac[0]=1;for(int i=1;i<N;i++)Fac[i]=Fac[i-1]*i%mod;
    iFac[0]=iFac[1]=1;
    for(int i=2;i<N;i++)iFac[i]=iFac[mod%i]*(mod-mod/i)%mod;
    for(int i=1;i<N;i++)(iFac[i]*=iFac[i-1])%=mod;
}
inline int C(int n,int m){
    return n<m?0:Fac[n]*iFac[m]%mod*iFac[n-m]%mod;
}
int Min;
int Prod[N];
int Suf[N];
int S[N];
inline int qpow(int a,int b){
    int Ans=1;
    while(b){
        if(b&1)Ans=Ans*a%mod;
        a=a*a%mod;b>>=1;
    }return Ans;
}
inline void slv(){
    cin>>n;
    Min=n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=0;i<=n;i++)cnt[i]=0;
    for(int i=1;i<=n;i++)cnt[a[i]]++;
    S[n]=0;
    for(int i=n-1;i>=0;i--)S[i]=S[i+1]+cnt[i];
    for(int i=0;i<=n+1;i++)Prod[i]=1;
    int Ans=0;
    for(int x=0;x<n;x++){
        // for(int i=0;i<=n;i++)cout<<Prod[i]<<" ";cout<<endl;
        Suf[cnt[x]+1]=0;
        for(int i=cnt[x];i>=0;i--)Suf[i]=C(cnt[x],i);
        for(int i=cnt[x];i>=0;i--)(Suf[i]+=Suf[i+1])%=mod;
        for(int i=0;i<=min(Min,cnt[x]);i++){
            int P1=Suf[i+1]*(Prod[i]-Prod[i+1]+mod)%mod;
            int P2=C(cnt[x],i)*Prod[i]%mod;
            int SP=(P1+P2)%mod;
            (Ans+=SP*i%mod*qpow(2,S[x+1])%mod)%=mod;
        }
        for(int i=Min;i>cnt[x];i--)Prod[i]=0;
        Min=min(Min,cnt[x]);
        for(int i=Min;i>=0;i--)(Prod[i]*=Suf[i])%=mod;
    }
    cout<<Ans<<endl;
}
signed main(){ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    Init();
    int T;
    cin>>T;
    while(T--)slv();
}
```

---

## 作者：conti123 (赞：0)

## CF2030E

考虑对于一个序列 $b$，贡献怎么算。

题意是分成任意个集合，那肯定是每个 $0$ 单独成段，每个 $1$ 放在 $0$ 后面，少了不管，多了不要，每个 $2$ 放在每个 $1$ 后面，以此类推。

于是我们可以得出表达式：

$$
val=\sum_{i=0}^{n-1}\min_{j=0}^icnt_j
$$

其中 $cnt_j$ 为 $j$ 元素的出现次数，这里做了个类似差分的拆贡献。

考虑 到 $i$ 的权值，每权值出现次数都 $\ge k$，剩下的随意对答案的贡献，也就是原序列有多少个子序列包含它。

明显有：

$$
\large ans=2^{\sum_{j=i+1}^{n-1}cnt_j}\cdot\prod_{j=0}^i\sum_{t=k}^{cnt_j}C_{cnt_j}^k
$$

字面意思，前 $i$ 位选的个数 $\ge k$，后面随便选。

考虑 $2^{\sum_{j=i+1}^{n-1}cnt_j}$ 用后缀积维护，$\sum_{t=k}^{cnt_j}C_{cnt_j}^k$ 后缀和维护，$\prod_{j=0}^i$ 暴力维护。

因为我们这个 $i$ 能枚举到的前提是 $0$ 到 $i$ 的出现次数 $\ge k$，所以 $i\le \left \lfloor \frac{n}{k} \right \rfloor $，那么复杂度的上界是 $\sum_{i=1}^n\frac{n}{i}=O(n\ln n)$，可以通过此题，而且想要跑到上界很难。

```cpp
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		cnt[x]++;
		g[x]++;
	}
	int pos=0;
	sum[n]=1;
	for(int i=n-1;i>=0;i--)
		sum[i]=sum[i+1]*qmi(2,cnt[i])%mod;
	int ans=0;
	for(int i=n;i>=1;i--){
		while(pos<n&&cnt[pos]>=i)
			pos++;
		int res=1;
		for(int j=0;j<pos;j++){
			while(g[j]>=i)
				f[j]+=C(cnt[j],g[j]),f[j]%=mod,g[j]--;
			res=res*f[j]%mod;
			ans=(ans+res*sum[j+1]%mod)%mod;
		}
	}
	cout<<ans<<"\n";
	for(int i=0;i<=n;i++)
		f[i]=g[i]=sum[i]=cnt[i]=0;
}
```

---

