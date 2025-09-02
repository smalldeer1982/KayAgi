# 挑战 NPC IV

## 题目背景

要是什么都和 NPC 问题一样简单就好了啊。

## 题目描述

小 A 想为小 B 写一首情诗。他现在想出了 $n$ 个句子，每个句子的优美度分别为 $1, 2 \dots n$。小 A 需要按照一定的顺序将他们组合起来，拼成一首完整的诗。换句话说，小 A 需要重新排列这 $n$ 个句子，形成一个 $1 \sim n$ 的排列 $p_1, p_2\dots p_n$；第 $i$ 行诗句的优美度就是原先第 $p_i$ 个句子的优美度，也就是 $p_i$。

不过，由于小 A 是位 OIer，所以他的文采并不是很稳定。他实际上会严重高估自己诗句的优美程度。若一条诗句在小 A 眼里的优美度为 $x$，那么小 B 认为它的优美度是 **$x$ 在二进制表示下最低位的 $1$ 的位置**。其中，小 B 认为最低位的位置是 $1$，次低位为 $2$，以此类推。也就是说，小 B 眼中的优美度 $f(x)$ 为 $1 + \log_2 \operatorname{lowbit}(x)$。

小 A 知道，小 B 拿到诗后，只会选取诗的一段来看，而她感受到的优美度是所有她读到的诗句之和。具体的，若诗有 $n$ 句，则小 B 会在 $[1, n]$ 的所有长度 $> 0$ 的区间中抽取一个 $[l, r]$，感受到 $\displaystyle\sum_{l \leq i \leq r}f(p_i)$ 的优美度。小 A 为了衡量一首诗的优美度，决定将一首诗的总优美度定义为 **所有情况下小 B 感受到的优美度之和**。

照理来说，总优美度最大的组合方式必然是最好的。遗憾的是，在小 A 的精密计算下，他发现，只有他选择总优美度恰好为 **第 $k$ 小** 的情诗时，他才最有可能和小 B 走到一起。于是，小 A 想要知道，对于 $n!$ 首本质不同的诗，第 $k$ 小可能的总优美度是多少。两首诗本质相同当且仅当原排列 $p_1 \dots p_n$ 相同。

小 A 发现这是一个 NPC 问题，他只好来向你求助了。由于总优美度过于巨大，你只需要帮他求出答案对 $998244353$ 取模后的结果。

特别的，小 A 写了 $q$ 组诗句，所以你需要分别回答他的 $q$ 个问题。

## 说明/提示

#### 【样例 1 解释】

例如，当 $p = [1, 3, 2]$ 时，小 B 眼中每句诗的优美度分别为 $[1, 1, 2]$。那么：

- 当 $l = 1$，$r = 1$ 时，优美度之和为 $1$。
- 当 $l = 2$，$r = 2$ 时，优美度之和为 $1$。
- 当 $l = 3$，$r = 3$ 时，优美度之和为 $2$。
- 当 $l = 1$，$r = 2$ 时，优美度之和为 $1 + 1 = 2$。
- 当 $l = 2$，$r = 3$ 时，优美度之和为 $1 + 2 = 3$。
- 当 $l = 1$，$r = 3$ 时，优美度之和为 $1 + 1 + 2 = 4$。

所以 $p = [1, 3, 2]$ 的总优美度为 $1 + 1 + 2 + 2 + 3 + 4 = 13$。

对于所有 $3! = 6$ 个排列 $p$，其总优美度从小到大排序后分别为 $13, 13, 13, 13, 14, 14$，因此当 $k = 2$ 与 $k = 6$ 时答案分别为 $13$ 和 $14$。

---

#### 【样例 2】

见附件下的 $\verb!npc/npc2.in!$ 与 $\verb!npc/npc2.ans!$。

---

#### 【样例 3】

见附件下的 $\verb!npc/npc3.in!$ 与 $\verb!npc/npc3.ans!$。

---

#### 【数据范围】

**本题各测试点时间限制不相同。具体地，每个点的时间限制为 $\max(q\times 0.5, 2)\ \rm{s}$**。

| 测试点编号 | $n$ | $k \leq$ | $q = $ |
| :--------: | :-: | :------: | :----: |
| $1 \sim 3$ | $\leq 10$ | $n!$ | $2$ |
| $4 \sim 8$ | $\leq 10^3$ | $2$ | $7$ |
| $9 \sim 13$ | $\in [10^5, 10^6]$ | $\min(10^{18}, n!)$ | $7$ |
| $14 \sim 17$ | $\leq 10^6$ | $\min(10^{18}, n!)$ | $7$ |
| $18 \sim 25$ | $\leq 10^{18}$ | $\min(10^{18}, n!)$ | $10$|

对于 $100\%$ 的数据，保证 $1 \leq n \leq 10^{18}$，$1 \leq k \leq \min(10^{18}, n!)$，$1 \leq q\le 10$。

## 样例 #1

### 输入

```
2
3 2
3 6```

### 输出

```
13
14
```

## 样例 #2

### 输入

```
5
4 1
4 10
4 16
4 20
4 24```

### 输出

```
32
34
36
36
38```

## 样例 #3

### 输入

```
10
1000000000000000000 1000000000000000000
1145141919810 19260817998244353
15 131413141314
36 93930322810121243
172 354354645654567654
666 233
1048576 2147483648
1000000007 1000000009
99824 44353
10 1```

### 输出

```
36226088
846277092
1096
12356
1239174
70731494
274614617
511280969
625722816
330```

# 题解

## 作者：樱雪喵 (赞：32)


### Part 1. $k=1$

首先考虑 $k=1$ 的时候怎么做。

考虑最终的位置 $i$ 会被多少个区间统计到，不难发现它计入贡献的次数是 $b_i=i(n-i+1)$。  
也就是说问题转化成，令 $a_i=f(i)$，$b_i=i(n-i+1)$，我们要对 $a$ 序列指定一个顺序，最小化 $\sum\limits_{i=1}^n a_i\times b_i$。  
这个问题有显然的贪心，$a$ 序列升序排序，$b$ 序列降序排序，对应位相乘即为最小值。证明是容易的：设 $a<b$ 且 $c<d$，有 $(b-a)d>(b-a)c$，移项即得 $ac+bd>ad+bc$。

### Part 2. $n\in [29,10^6]$

在上述过程中发现这么一个问题，方案本质不同的定义是 $p$ 不相同，但 $f(p_i)$ 中有很多数相同。交换它们中的一部分不会使贡献序列改变，但可以使 $p$ 改变。因此我们估计，在不改变贡献序列的情况下，本质不同的 $p$ 是相当多的。

考虑估计这个具体数目，$a$ 序列中大约有 $\frac{n}{2}$ 个 $1$，$\frac{n}{2^2}$ 个 $2$（暂不讨论上下取整的问题），那么我们至少能搞出 $cnt=\prod\limits_{i=1}^{\log_2 n} (\frac{n}{2^i})! $ 种取到最小值的排列。这里没考虑交换 $b$ 序列的情况，因此实际值会比这更多。

这说明 $k\le cnt$ 的时候答案都可以取到最小值。写个代码求上面的式子，可以发现 $n=29$ 的时候 $cnt$ 就超过了 $10^{18}$。也就是说，$n>29$ 时 $k$ 为任何值的答案都和 $k=1$ 相等。

$O(n)$ 地模拟上述贪心，配合爆搜可以通过前 $13$ 个点。有 52pts 暴力分，好良心！

### Part 3. $n\in [29,10^{18}]$

这一部分没有单独的部分分，但我们需要加速贪心的过程。  
只要快速求出 $a$ 序列中每个数的数量，就能找到它们在 $b$ 序列中对应的连续区间。根据基础位运算知识可以得出值为 $i$ 的出现次数。  
令 $s(l,r)=\sum\limits_{i=l}^r b_i$，推式子：
$$
\begin{aligned}
s(l,r)&=\sum_{i=l}^r i(n-i+1)\\
&=(n+1)(\sum_{i=l}^r i)-\sum_{i=l}^r i^2\\
&=(n+1)\frac{(l+r)(r-l+1)}{2} - \frac{r(r+1)(2r+1)}{6}+\frac{l(l-1)(2l-1)}{6}
\end{aligned}
$$
现在这两个序列都能快速计算，我们可以在 $O(\log n)$ 的时间复杂度内处理单次询问。

### Part 4. $n\le 28$

看起来即使仅考虑本质不同的 $a$ 序列，这样的数量依然很多。但是我们发现一条关键性质：这种情况下**优美度的值域**很小，只有 $10^4$ 左右。  
考虑基于这个进行 dp。进一步观察，$a$ 序列中至多有 $5$ 种不同的值。因为优美度已经计入了状态，我们显然只关心它们填了几个，而不关心它们的位置。

故设 $f_{a,b,c,d,e,sum}$ 表示 $1,2,3,4,5$ 分别填了 $a,b,c,d,e$ 个，总优美度为 $sum$ 的方案数。  
转移时枚举当前位填什么数，式子是容易写出的。

这样的有效状态数在 $n=28$ 时取到上界，大致有 $16\times 9\times 5\times 3\times 2\times 1.1\times 10^4=4.752\times 10^7$ 种状态。开数组时请注意空间消耗。

结合 Part 3 的做法即可获得 100pts。

```cpp
#define int long long
const int N=1e6+5,mod=998244353;
int T,n,k;
int f[16][9][5][3][2][11005];
int a[N],b[N],cnt[N],mx=11000,now[6],jc[N];
il int qpow(int n,int k=mod-2)
{
    int res=1;
    for(;k;n=n*n%mod,k>>=1) if(k&1) res=res*n%mod;
    return res;
}
il int S(int x) {x%=mod;return x*(x+1)%mod*(2*x+1)%mod*qpow(6)%mod;}
il int get(int l,int r,int n)
{
    if(l>r) return 0;
    if(r>n/2&&l<=n/2) return (get(l,n/2,n)+get(n/2+1,r,n))%mod; 
    if(l>n/2) l=n-l,r=n-r,swap(l,r);
    int res=n%mod*((l+r)%mod)%mod*((r-l+1)%mod)%mod*qpow(2)%mod-(S(r)-S(l-1)+mod)%mod;
    return (res%mod+mod)%mod;
}
il void solve(int n)
{
    int l=1,r=n,res=0;
    for(int i=__lg(n)+1;i;i--)
    {
        int sum=(n>>i)+(n>>(i-1)&1);
        int ls=sum/2,rs=sum-ls;
        if(l<n-r+1) swap(ls,rs);
        (res+=i*get(l,l+ls-1,n+1)%mod)%=mod,(res+=i*get(r-rs+1,r,n+1)%mod)%=mod;
        l+=ls,r-=rs;
    }
    printf("%lld\n",res);
}
signed main()
{
    T=read(); jc[0]=1;
    for(int i=1;i<=15;i++) jc[i]=jc[i-1]*i;
    while(T--)
    {
        n=read(),k=read();
        if(n>28) {solve(n);continue;}
        for(int i=1;i<=n;i++) a[i]=1+__lg(i&(-i));
        for(int i=1;i<=n;i++) b[i]=i*(n-i+1);
        sort(a+1,a+n+1),sort(b+1,b+n+1);
        for(int i=1;i<=n;i++) cnt[i]=0;
        for(int i=1;i<=n;i++) cnt[a[i]]++;
        int Cnt=1;
        if(n<=28) for(int i=1;i<=__lg(n)+1;i++) Cnt=Cnt*jc[cnt[i]];
        f[0][0][0][0][0][0]=1;
        for(now[1]=0;now[1]<=cnt[1];now[1]++)
        for(now[2]=0;now[2]<=cnt[2];now[2]++)
        for(now[3]=0;now[3]<=cnt[3];now[3]++)
        for(now[4]=0;now[4]<=cnt[4];now[4]++)
        for(now[5]=0;now[5]<=cnt[5];now[5]++)
        {
            int sum=0;
            for(int i=1;i<=5;i++) sum+=now[i];
            if(!sum) continue;
            for(int j=0;j<=mx;j++)
            {
                int i=0;
                for(int k=1;k<=5;k++)
                {
                    if(now[k]==0) continue;
                    if(j-k*b[sum]<0) continue;
                    now[k]--;
                    i+=f[now[1]][now[2]][now[3]][now[4]][now[5]][j-k*b[sum]];
                    now[k]++;
                }
                f[now[1]][now[2]][now[3]][now[4]][now[5]][j]=i;
            }
        }
        int ans=0;
        for(int i=0;i<=mx;i++)
        {
            ans+=Cnt*f[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][i];
            if(ans>=k) {printf("%lld\n",i);break;}
        }
    }
    return 0;
}
```

---

## 作者：Register_int (赞：13)

非常好搜题。

考虑如何对一个排列求总和。实际上每个 $p_i$ 会被 $i(n-i+1)$ 个不同的区间算进去，所以总和为 $\sum f(p_i)\times i(n-i+1)$。

先考虑 $n$ 较小时暴力的做法。考虑到 $f$ 值相同的数有很多，不同的只有 $\log n$ 种。所以可以考虑一个 $dp_{c_1,c_2,\cdots,c_x,T}$，表示当前 $f(p_i)=j$ 的数填了 $c_j$ 个，当前填完的总和为 $T$ 的方案数。直接暴力转移出来即可。时间、空间复杂度为 $O(n^{\log_2 n}V)$，其中 $V$ 是待定常数。大概可以通过 $n\le 32$ 的数据。

考虑 $n>32$ 怎么做。实际上，我们可以发现，$f$ 值相同的数可以任意轮换，并且两个位置关于中心对称的数也可以互换，所以一个值的方案数至少为 $\prod c_i!$。这个数实际上是很大的，通过简单实验可以得知，最小值的方案数在 $n>28$ 时就会 $\ge10^{18}$。所以我们只需要求出最小值即可。

最小值怎么算呢？一个数对全局的贡献显然只和他的位置有关，所以我们可以按照 $f$ 值从小到大，从中间往两边放，得到的值就是最小值。这个可以用数学方法快速计算。时间、空间复杂度为 $O(\log n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;
const int inv2 = mod + 1 >> 1;
const int inv6 = (mod + 1) / 6;

ll dp[15][8][5][3][2][5983];

ll dfs(int n, int t1, int t2, int t3, int t4, int t5, int k) {
	if (k < 0 || t1 < 0 || t2 < 0 || t3 < 0 || t4 < 0 || t5 < 0) return 0;
	if (!k) return t1 || t2 || t3 || t4 || t5 ? 0 : 1;
	ll &ans = dp[t1][t2][t3][t4][t5][k];
	if (~ans) return ans; ans = 0;
	int p = t1 + t2 + t3 + t4 + t5; p = p * (n - p + 1);
	ans += dfs(n, t1 - 1, t2, t3, t4, t5, k - 1 * p);
	ans += dfs(n, t1, t2 - 1, t3, t4, t5, k - 2 * p);
	ans += dfs(n, t1, t2, t3 - 1, t4, t5, k - 3 * p);
	ans += dfs(n, t1, t2, t3, t4 - 1, t5, k - 4 * p);
	ans += dfs(n, t1, t2, t3, t4, t5 - 1, k - 5 * p);
	return ans;
}

inline 
ll calc(ll n, ll m) {
	n %= mod, m %= mod;
	ll ans = (n + 1) * m % mod * (m + 1) % mod * inv2 % mod;
	ans -= m * (m + 1) % mod * (2 * m + 1) % mod * inv6 % mod;
	return (ans + mod) % mod;
}

ll cnt[61];

inline 
ll calc(ll n) {
	ll m = n >> 1, ans = 0;
	for (int i = 0; i < 60; i++) cnt[i + 1] = n >> i;
	for (int i = 1; i < 60; i++) cnt[i] -= cnt[i + 1];
	if (n & 1) ans = (m + 1) % mod * ((n - m) % mod) % mod, cnt[1]--;
	for (int i = 1; i <= 60; i++) {
		ll t = cnt[i] >> 1; m -= t;
		ans = (ans + 2 * (calc(n, m + t) - calc(n, m) + mod) % mod * i % mod) % mod;
		if (cnt[i] & 1) {
			ans = (ans + m % mod * ((n - m + 1) % mod) % mod * i % mod) % mod;
			ans = (ans + m % mod * ((n - m + 1) % mod) % mod * (i + 1) % mod) % mod;
			cnt[i + 1]--, m--;
		}
	}
	for (int i = 0; i < 60; i++) cnt[i + 1] = n >> i;
	for (int i = 1; i < 60; i++) cnt[i] -= cnt[i + 1];
	return ans;
}

ll fac[16];

int t; ll n, k, x, y;

int main() {
	*fac = 1;
	for (int i = 1; i <= 15; i++) fac[i] = fac[i - 1] * i;
	for (scanf("%d", &t); t--;) {
		scanf("%lld%lld", &n, &k), x = calc(n);
		if (n > 28) { printf("%lld\n", x); continue; }
		for (int i = 1; i <= 5; i++) k = (k - 1) / fac[cnt[i]] + 1;
		for (memset(dp, 0xff, sizeof dp); ;) {
			y = dfs(n, cnt[1], cnt[2], cnt[3], cnt[4], cnt[5], x);
			if (y >= k) { printf("%lld\n", x); break; } k -= y, x++;
		}
	}
}
```

---

## 作者：JiaY19 (赞：8)

什么神秘暴搜题，考场上已经可以跑 $20$ 了，加个记忆化就过了。

### 思路

#### Subtask1 

考虑一个序列的权值是多少。

对每一个位置分别进行考虑。

容易得知包含第 $i$ 个位置的区间有 $i\times (n-i+1)$ 个。

那么只需要在乘上每个位置的权值。

那么对于 $n\le 10$，可以直接枚举全排列。

#### Subtask2

考虑 $k=2$ 怎么做。

容易发现，由于答案相同的排列很多，在 $n\ge 2$ 时，$k=2$ 与 $k=1$ 答案相同。

那么问题可以变为考虑 $k=1$ 怎么做。

由于要求的是最小的。

那么我们贪心的把权值更大的放在出现次数少的位置上去。

只需要一次排序即可。

#### Subtask3

考虑一个排列会有那些与它完全相同的排列。

由于 $f(x)$ 有很多相同的值，那么对于所有 $f(x)=i$ 的都可以随意调换位置。

可以计算出，在 $n\ge 30$ 时，最小的排列的次数已经远超过了 $10^{18}$。

所以对于 $n\in[10^5,10^6]$，答案必然与 $k=1$ 相同。

所以只需要套上 $\text{subtask2}$ 的做法即可。

#### Subtask3.5

考虑 $n\in[10,30]$ 怎么做。

有一种我考场上的做法。

由于对于所有 $f(x)=i$ 的都可以随意调换位置。

那么我们搜索每个位置的出现次数放入 $f(x)=i$ 所开的桶里。

搜出所有情况，并算出方案数。

这样就可以跑 $n\in[10,20]$。

但还是暴力分。

#### Subtask4

考虑上面的做法还能如何优化。

由于 $n$ 只有 $30$，那么对于一些尽管拥有略微不同的方案，答案也同样可能相同。

那么我们只要对于上面的做法对答案一维加个记忆化。

记 $dp_{i,j,k,l,r,s}$ 为 $f(x)=1$ 放了 $i$ 个位置的出现次数， $f(x)=1$ 放了 $i$ 个位置的出现次数， $f(x)=2$ 放了 $j$ 个位置的出现次数……最终的答案为 $s$。

这样就有节省了很多状态，可以跑 $n\in[10,30]$。

#### Subtask5

考虑优化 $\text{Subtask2}$ 的做法。

由于 $f(x)$ 的种类很少。

那么可以枚举 $f(x)$，算出 $f(x)=i$ 的方案数。

考虑每个位置的出现次数从小到大是多少。

两个 $1\times n$，两个 $2\times (n-1)$……

我们需要快速算出从 $l-r$ 的和。

可以转换为算前缀和。

对于两个的，我们先只算一个，最后再乘个 $2$，并对边界情况特殊处理。

那么我们现在变成了求 $\sum_{i=1}^l i\times (n-i+1)$。

有一个不需要思考的方法。

容易看出这个东西是一个低次多项式，通过尝试后发现是一个四次多项式。

那么直接拉插一下即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 1000010;
const int mod = 998244353;

i64 n, m;

inline i64 lb(i64 x)
	{ return x&(-x); }
inline i64 f(i64 x)
	{ return 1+ __lg(lb(x)); }
inline i64 g(i64 x)
	{ return x * (n - x + 1); }
inline i64 gmod(i64 x)
	{ return x % mod * ((n - x + 1) % mod) % mod; }
inline void mo(i64 &x)
	{ x = (x % mod + mod) % mod; }
inline i64 pos(i64 x)
	{ i64 res = 1; while(x) res *= x, x--; return res; }

namespace subtask1
{
	i64 mx, q, s[N], dp[15][8][5][3][2][10000];
	inline void dfs(int a, int b, int c, int d, int e, int t)
	{
		int x = a + b + c + d + e + 1;
		if(x == n + 1 || !dp[a][b][c][d][e][t]) return;
		mx = max(mx, (i64)t);
		if(a != s[1]) dp[a + 1][b][c][d][e][t + g(x) * 1] += dp[a][b][c][d][e][t] * (s[1] - a);
		if(b != s[2]) dp[a][b + 1][c][d][e][t + g(x) * 2] += dp[a][b][c][d][e][t] * (s[2] - b);
		if(c != s[3]) dp[a][b][c + 1][d][e][t + g(x) * 3] += dp[a][b][c][d][e][t] * (s[3] - c);
		if(d != s[4]) dp[a][b][c][d + 1][e][t + g(x) * 4] += dp[a][b][c][d][e][t] * (s[4] - d);
		if(e != s[5]) dp[a][b][c][d][e + 1][t + g(x) * 5] += dp[a][b][c][d][e][t] * (s[5] - e);
	}
	inline void solve()
	{
		mx = 0;
		memset(dp, 0, sizeof dp);
		fro(i, 1, n) s[i] = 0;
		fro(i, 1, n) s[f(i)]++;
		dp[0][0][0][0][0][0] = 1;
		fro(i, 0, s[1]) fro(j, 0, s[2])
			fro(k, 0, s[3]) fro(l, 0, s[4])
				fro(r, 0, s[5]) fro(p, 0, 9999)
					dfs(i, j, k, l, r, p);
		fro(p, 0, 9999)
		{
			if(!dp[s[1]][s[2]][s[3]][s[4]][s[5]][p]) continue;
			if(m <= dp[s[1]][s[2]][s[3]][s[4]][s[5]][p])
				return cout << p << "\n", void();
			m -= dp[s[1]][s[2]][s[3]][s[4]][s[5]][p];
		}
	}
}
namespace subtask2
{
namespace Math
{
	i64 val[N], id[N], pw[N];
	inline i64 power(i64 x, i64 y = mod - 2, i64 z = mod)
	{
		i64 res = 1; x %= z;
		while(y)
		{
			if(y & 1) res = res * x % z;
			x = x * x % z, y /= 2;
		}
		return res;
	}
	inline i64 Largran(i64 *a, i64 *b, int n, i64 k)
	{
		i64 ans = 0;
		fro(i, 1, n)
		{
			i64 s1 = 1, s2 = 1;
			fro(j, 1, n) if(i != j)
				s1 = s1 * ((k - a[j]) % mod) % mod,
				s2 = s2 * ((a[i] - a[j]) % mod) % mod;
			ans = (ans + b[i] * s1 % mod * power(s2) % mod) % mod;
		}
		return (ans % mod + mod) % mod;
	}
	inline i64 ask(i64 l, i64 r)
	{
		if(l > r) return 0;
		i64 ls = (l + 1) / 2 - 1;
		i64 rs = (r + 0) / 2 - 0;
		i64 res = 0;
		if(l % 2 == 0) res -= gmod(ls + 1);
		if(r % 2 == 1) res += gmod(rs + 1);
		res += Largran(id, val, 10, rs) * 2;
		res -= Largran(id, val, 10, ls) * 2;
		return mo(res), res;
	}
	inline void solve()
	{
		pw[0] = 1;
		fro(i, 1, 10) val[i] = (gmod(i) + val[i - 1]) % mod;
		iota(id + 1, id + 11, 1);
		fro(i, 1, 61) pw[i] = pw[i - 1] * 2;
		i64 now = 0, ans = 0;
		pre(i, 61, 1)
		{
			i64 x = ((n - pw[i - 1])>>i) + 1;
			ans += ask(now + 1, now + x) * i, now += x, mo(ans);
		}
		cout << ans << "\n";
	}
}
	inline void solve() { Math::solve(); }
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 512;
	assert(Mib<=Lim), cerr << " Memory: " << Mib << "\n";
	int t; cin >> t;
	while(t--)
	{
		cin >> n >> m;
		if(n <= 28) subtask1::solve();
		else        subtask2::solve();
	}
	return 0;
}
```

---

## 作者：EnofTaiPeople (赞：4)

一道在 Ad-hoc 随机区分中让我勉强进入线下榜前十的题目，感谢出题人，NOIP2023rp++！

容易发现题面的 $f(x)$ 的值等于 `__builtin_ctzll(x)+1`，不妨设 $c_d=\sum\limits_{x=1}^n[f(x)=d]$，考虑 $\sum\limits_{x=1}^n[f(x)\ge d]=\sum\limits_{x=1}^n[2^{d-1}|x]=\lfloor\dfrac n{2^{d-1}}\rfloor$，于是 $c_d=\lfloor\dfrac n{2^{d-1}}\rfloor-\lfloor\dfrac n{2^{d}}\rfloor$，可以 $O(1)$ 计算。

所有本质相同的 $p_x$ 共有 $C=\prod c_d!$ 个，于是我们可以只需要求基于本质相同排列的第 $\lceil\dfrac KC\rceil$ 小，$n\ge30$ 时，$C>10^{18}\ge K,\lceil\dfrac KC\rceil=1$，即只需要求最小值。

这部分是平凡的，只需要将最大的 $f(x)$ 和序列两边匹配即可，我们只需要快速算 $\sum\limits_{k=l}^rk(n-k+1)$ 的值即可，可以直接利用 $\sum\limits_{k=1}^nk^2=\dfrac{n(n+1)(2n+1)}6$ 的公式得出，硬是没有背可以现推（我小学推出来过）或拉插（更方便）：
```cpp

int S1(ll r){
    r%=M;
    return (r*(r+1)/2%M*(n%M+1)%M+M-LL(r+r+1)*(r+1)*r/6%M)%M;
}
int S1(ll l,ll r){
    if(l>r)return 0;
    int res=S1(r);
    if(l)del(res,S1(l-1));
    return res;
}
namespace sol1{
    void sol(){
        ll L,R,d;
        int k,ans=0;
        for(L=R=0,k=61;L+R<n;--k){
            d=(n>>k)-(n>>k+1);
            add(ans,k+1,S1(L+1,L+(d+1>>1))),L+=d+1>>1;
            add(ans,k+1,S1(R+1,R+(d>>1))),R+=d>>1;
            if(L>R)swap(L,R);
        }printf("%d\n",ans);
    }
}
```

否则，如果直接枚举本质不同 $p_x$ 的全排列可以通过 $n\le15$ 的数据，获得 $65$ 分。

考虑不使用如此暴力的方法，发现 $n\le29$ 时最后算出来的结果的数值在 $9990$ 以内，所有 $c_d$ 剩余的状态数 $\prod (c_d+1)$ 在 $3920$ 以内，可以设 $F_{S,V}$ 表示剩余 $c_d$ 的状态为 $S$，当前值为 $V$ 的方案数，发现每次转移只会转移 $\sum rest_d$ 等于特定值的方案，所以每个状态只会转移一次。

时空复杂度 $O(SV)$ 跑得很快：
```cpp

namespace sol3{
    int p[N],v[N],ct[N],c[6],V;
    ll f[3925][9997];
    int b[3925],bt,id[1<<21];
    vector<int>lk[55];
    void sol(){
        int i,j,k,l,r,x,y;
        for(i=1;i<=5;++i)c[i]=0;
        for(i=1;i<=n;++i){
            ++c[p[i]=val(i)],v[i]=i*(n-i+1);
            lk[i].clear();
        }
        sort(p+1,p+n+1);
        for(i=1,--K;i<=5;++i)
            for(j=1;j<=c[i];++j)K/=j;
        if(!K)return sol1::sol();
        ++K,sort(v+1,v+n+1);
        for(i=1,V=0;i<=n;++i)V+=p[i]*v[i];
        for(int a=bt=0;a<=c[1];++a)
            for(int t=0;t<=c[2];++t)
                for(int d=0;d<=c[3];++d)
                    for(int e=0;e<=c[4];++e)
                        for(int h=0;h<=c[5];++h){
                            id[b[++bt]=a<<12|t<<9|d<<6|e<<3|h]=bt;
                            lk[a+t+d+e+h].push_back(bt);
                        }
        for(l=1;l<=bt;++l)
            for(r=0;r<=V;++r)f[l][r]=0;
        f[bt][0]=1;
        for(i=1;i<=n;++i){
            for(int l:lk[n-i+1]){
                for(r=0;r<=V;++r){
                    if(!f[l][r])continue;
                    for(x=0;x<4;++x)
                        if((b[l]>>x*3)&7)
                            f[id[b[l]-(1<<x*3)]][r+(5-x)*v[i]]+=f[l][r];
                    if(b[l]>>12)f[id[b[l]-(1<<12)]][r+v[i]]+=f[l][r];
                }
            }
        }
        for(l=0;f[1][l]<K;K-=f[1][l++]);
        printf("%d\n",l);
    }
}
```
再次祝所有人 NOIP2023rp++！

---

## 作者：ykzzldz (赞：3)

神题！

显然，每个位置出现的次数 $b_i=i\times(n-i+1)$，容易发现 $b_1=b_n$，所以当 $k\le2$ 时答案均为最小值，这部分可以将 $f_i$ 降序排序，将 $b_i$ 升序排序，然后将 $f_i$ 和 $b_i$ 结合即可，这样可以获得 $20$ 分。

这时，我们发现有一档非常奇怪的部分分 $n\in[10^5,10^6]$，这档部分分是非常有启发性意义的，我们不禁想：为什么题目中要给我们一个 $n$ 的下界？我们猜想，由于 $f$ 中有大量元素是相同的，而 $n$ 这么大所构成排列的数量也是巨大的，所以一定有许多排列的答案是相同的。猜想 $n$ 比较大时，答案全部为最小值。具体来说，当 $n\ge29$ 的时候就已经是最小值了。

于是，我们现在需要设计两个算法，当 $n\le28$ 跑一个，$n\ge29$ 时跑另一个。

- $n\le28$

$n$ 这么小，所以 $f$ 的值非常小，不会超过 $5$。容易发现，此时答案的范围也比较小，考虑 dp。设 $dp_{a,b,c,d,e,sum}$ 为 $a$ 中五种数值分别填了几个，且答案为 $sum$ 的方案数。我看其他题解都没怎么写转移（可能是觉得太简单了），但为了帮助和我一样的蒟蒻，在这里我还是写一下转移方程：

$$
dp_{a,b,c,d,e,sum}=dp_{a-1,b,c,d,e,sum-b_i}\times (jsq_1-a+1)+dp_{a,b-1,c,d,e,sum-b_i\times2}\times (jsq_2-b+1)+dp_{a,b,c-1,d,e,sum-b_i\times3}\times (jsq_3-c+1)+dp_{a,b,c,d-1,e,sum-b_i\times4}\times (jsq_4-d+1)+dp_{a,b,c,d,e-1,sum-b_i\times5}\times (jsq_5-e+1)
$$

其中 $i=a+b+c+d+e$，$b_i$ 为 $i$ 位置的出现次数，$jsq_i$ 表示 $f$ 中 $i$ 的出现次数，这其实就是枚举最后一位放什么，想到了就还是比较简单的。

求解答案的时候，枚举最后一维累加即可，看什么时候超过 $k$。

也是这个 dp，时间和空间卡的非常精妙，这也是这题成为神题的一个重要部分。

- $n\ge29$

我们上面那个贪心的过程是 $O(n)$ 的，考虑怎么优化。其实 $f$ 的值是非常少的，考虑每个 $f_i$ 对答案的贡献。

我们可以枚举 $f_i$，我们可以简单的知道每个 $f_i$ 出现的次数，现在的问题在于求：

$$
\sum _{i=l}^rb_i
$$

~~这拉插不是秒了吗？~~ 显然，拉插是蒟蒻不应该会的东西，于是我们考虑最原始的方式，把式子拆开：

$$
\sum _{i=l}^rb_i
=\sum _{i=l}^ri\times(n-i+1)
=(n+1)\sum_{i=l}^ri-\sum_{i=l}^ri^2=\frac{(n+1)(l+r)(r−l+1)}{2}−\frac{r(r+1)(2r+1)−l(l−1)(2l−1)}{6}
$$

其实只是比较简单的等比数列求和。到这里，这题就基本上做完了。这题启示我们，在遇到一些奇怪的部分分是应该要多加留意。

---

## 作者：Iniaugoty (赞：3)

正解是数据分治的题真的是太吊了。~~也可能是我见识太少。~~

#### $n \le 10$

直接枚举全排列。

#### $k \le 2$

根据定义，具有相同 $f(x)$ 值的数一定是很多的，随便交换其中几个都能得到一样的优美度，那么应当有好几个最小值。那么求最小值就行了。

拆贡献，显然有 $\displaystyle \sum _ {l = 1} ^ {n} \sum _ {r = l} ^ {n} \sum _ {i = l} ^ r f(p _ i) = \sum _ {i = 1} ^ {n} f(p _ i) \times i (n - i + 1)$（也就是满足 $l \in [1, i], r \in [i, n]$ 的有序对 $(l, r)$ 一共有 $i (n - i + 1)$ 个）。

设 $a _ i = f(i), b _ i = i  (n - i + 1)$，即对 $a, b$ 排序最小化 $\displaystyle \sum _ {i = 1} ^ {n} a _ i \times b _ i$。先对 $a$ 升序排序，考虑要怎样的 $b$。若 $a _ i \times b _ i + a _ j \times b _ j < a _ i \times b _ j +  a _ j \times b _ i$ 则 $b _ i$ 是在 $b _ j$ 前面的。移项得 $(a _ i - a _ j) \times b _ i < (a _ i - a _ j) \times b _ j$，由于 $a _ i < a _ j$，直接约掉得 $b _ i > b _ j$。即对 $a$ 升序排序，对 $b$ 降序排序，可以得到最小值。

#### $n \in [10 ^ 5, 10 ^ 6]$

相当诈骗。将 $f(1) \sim f(n)$ 的值写出来，可以得到一个 $1, 2, 1, 3, 1, 2, 1, 4, 1, 2, 1, 3, 1, 2, 1, 5, \cdots$ 这样的数列。观察可以发现，$1$ 出现了约 $\dfrac{n}{2}$ 次，$2$ 出现了约 $\dfrac {n} {4}$ 次，$i$ 出现了约 $\dfrac {n} {2 ^ i}$ 次。那么相同的优美度应当有至少 $\displaystyle \prod _ {i = 1} ^ {\log _ 2 n} (\dfrac {n} {2 _ i}) !$ 个。当 $n \ge 29$ 时，这个值就已远大于 $10 ^ {18}$，但 $k \le 10 ^ {18}$。那么在 $n \ge 29$ 时答案就与 $k$ 无关，更何况 $10 ^5$，直接用上一部分的方法求最小值即可。

#### $n \le 10 ^ 6$

比上一部分多了一个 $n \le 28$ 要解决。考虑 DP。

由于 $a$ 中出现的数字种类很少，最多只有到 $\lceil \log _ 2 28 \rceil=5$ 种，可以考虑枚举每个数的出现次数。又由于优美度的值域较小，经过计算，发现只有 $10 ^ 4$ 左右，可以求出得到每种优美度的排列数。
设 $dp _ {a, b, c, d, e, s}$ 表示前 $f = a + b + c + d + e$ 个数中有 $a$ 个 $1$，$b$ 个 $2$，$c$ 个 $3$，$d$ 个 $4$，$e$ 个 $5$，优美度为 $s$ 的方案数。这样只要找到最小的 $i$ 满足 $\displaystyle \sum _ {j = 1} ^ {i} dp _ {a, b, c, d, e, j} \ge k$ 即为答案。

转移显然，枚举第 $f$ 位是什么数，但比较繁琐：

$$dp _ {a, b, c, d, e, s} =
\begin{aligned}
& dp _ {a - 1, b, c, d, e, s - f(n - f + 1)} \times (ct _ {1} - a + 1) \\
&+ dp _ {a, b - 1, c, d, e, s - 2 f(n - f + 1)} \times (ct _ {2} - b + 1) \\
&+ dp _ {a, b, c - 1, d, e, s - 3 f(n - f + 1)} \times (ct _ {3} - c + 1) \\
&+ dp _ {a, b, c, d - 1, e, s - 4 f(n - f + 1)} \times (ct _ {4} - d + 1) \\
&+ dp _ {a, b, c, d, e - 1, s - 5 f(n - f + 1)} \times (ct _ {5} - e + 1) \\
\end{aligned} $$

其中 $ct _ i$ 表示序列 $a$ 中数字 $i$ 的出现次数。

注意要处理一下不合法状态越界问题。

时间复杂度不太好分析，你可以认为有约 $16 \times 9 \times 5 \times 3 \times 2 \times 10 ^ 4 \times 5$ 的计算次数。

#### $n \le 10 ^ {18}$

$n \le 28$ 的情况还是照上一部分来做，$n \ge 29$ 的情况下求最小值的过程需要优化。

那种搞法是将 $a, b$ 两数组排序，实际上可以 $\mathcal O (n)$ 的模拟，把 $a$ 中的数从大到小、从两边到中间放，这样大数对应了 $b$ 的小数，小数对应了大数。这里要加速这个过程。

一个数字在 $a$ 中的出现次数很好求，找找规律就出来了，那样就很好搞一搞某个数对应的 $b$ 的区间（可能是左右两个），对优美度的贡献也很好算。设 $x$ 对应了区间 $[l, r]$，那么其贡献就是 $x \times \displaystyle \sum _ {i = l} ^ {r} b _ i$。

$\displaystyle \sum _ {i = l} ^ {r} b _ i$ 要推一推。具体地，

$$\begin{aligned} \sum _ {i = l} ^ {r} b _ i
&=\sum _ {i = l} ^ {r} i(n - i + 1)\\
&= (n \times \sum _ {i = l} ^ {r} i) - (\sum _ {i = l} ^ {r} i ^ 2) + (\sum _ {i = l} ^ {r} i)\\
&= \frac{(n + 1)(l + r)(r - l + 1)}{2} - \frac{r (r + 1) (2r + 1) - l (l - 1) (2l - 1)}{6}
\end{aligned}$$

~~这么好看的式子就不用再化简了吧~~。

时间复杂度是 $\mathcal O (\log n)$，即 $a$ 中不同数字个数。

***

完整代码如下，实现对我这种啥笔来说还是很有细节的，调了好久：

```cpp
#include <bits/stdc++.h>

#define int LL
#define F(i, a, b) for(int i = a; i <= (b); ++i)
#define dF(i, a, b) for(int i = a; i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int mod = 998244353;
const int inv2 = 499122177;
const int inv6 = 166374059;
const int M = 1e4;

int _, n, k, ans;

int ct[6], dp[16][9][5][3][2][M + 5];
int lowbit(int x) { return x & -x; }
int f(int x) { return log2(lowbit(x)) + 1; }
void Solve1() {
	dp[0][0][0][0][0][0] = 1;
	F(i, 1, 5) ct[i] = 0;
	F(i, 1, n) ++ct[f(i)];
	F(a, 0, ct[1]) F(b, 0, ct[2]) F(c, 0, ct[3]) F(d, 0, ct[4]) F(e, 0, ct[5]) F(s, 1, M) {
		int f = a + b + c + d + e;
		f = f * (n - f + 1);
		dp[a][b][c][d][e][s] = 0;
		if (a && s >= 1 * f) dp[a][b][c][d][e][s] += dp[a - 1][b][c][d][e][s - 1 * f] * (ct[1] - a + 1);
		if (b && s >= 2 * f) dp[a][b][c][d][e][s] += dp[a][b - 1][c][d][e][s - 2 * f] * (ct[2] - b + 1);
		if (c && s >= 3 * f) dp[a][b][c][d][e][s] += dp[a][b][c - 1][d][e][s - 3 * f] * (ct[3] - c + 1);
		if (d && s >= 4 * f) dp[a][b][c][d][e][s] += dp[a][b][c][d - 1][e][s - 4 * f] * (ct[4] - d + 1);
		if (e && s >= 5 * f) dp[a][b][c][d][e][s] += dp[a][b][c][d][e - 1][s - 5 * f] * (ct[5] - e + 1);
	}
	int sum = 0;
	F(i, 1, M) {
		sum += dp[ct[1]][ct[2]][ct[3]][ct[4]][ct[5]][i];
		if (sum >= k) { ans = i; break; }
	}
	return ;
}

int sum(int l, int r) {
	if (l > r) return 0;
	l %= mod, r %= mod;
	int s1 = (n + 1) % mod * (l + r) % mod * (r - l + 1) % mod * inv2 % mod;
	int s2 = r * (r + 1) % mod * (2 * r + 1) % mod * inv6 % mod;
	int s3 = l * (l - 1) % mod * (2 * l - 1) % mod * inv6 % mod;
	return ((s1 - s2 + s3) % mod + mod) % mod;
}
void Solve2() {
	int l = 1, r = n, c, dl, dr;
	dF(i, log2(n) + 1, 1) {
		c = (n >> i - 1) - (n >> i);
		dl = c >> 1, dr = c - dl;
		if (l < n - r + 1) swap(dl, dr);
		ans = (ans + i * sum(l, l + dl - 1)) % mod,
		ans = (ans + i * sum(r - dr + 1, r)) % mod;
		l += dl, r -= dr;
	}
	return ;
}

signed main() {
	freopen("npc.in", "r", stdin);
	freopen("npc.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> _;
	while (_--) {
		cin >> n >> k;
		ans = 0;
		if (n >= 29 || k <= 2) Solve2();
		else Solve1();
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：TernaryTree (赞：3)

~~题目背景由真实事件改编，也可能未经改编，大家不妨猜一下小 R 和小 H 是谁~~

先来明确一点定义。定义一个排列为 $p$，其每个元素的优美度构成的序列为 $q$，定义 $q$ 中数字 $i$ 出现的次数为 $cnt_i$。

首先考虑一个 $q$ 序列可以被还原成几个 $p$ 序列。$q$ 中每个相同的数字都可以被替换为 $p$ 中未被选择过的优美度为其自身的数，所以方案数是

$$\prod cnt_i!$$

接下来解决 $cnt_i$ 的计算问题。若 $1+\operatorname{lowbit}(p_i)=q_i$，则有 $p_i=2^{q_i-1}\cdot (2k+1)$，其中 $k$ 为非负整数。通过解不等式，得到 $cnt_i=\left\lfloor\dfrac{n+2^{i-1}}{2^i}\right\rfloor$。

上面那个阶乘的柿子引导我们去思考，对于一个非常大的 $n$ 结果会如何。那么就是，当我们按总优美度最小的方案填入 $q$ 中，这个 $q$ 所对应的 $p$ 个数就足够多以至于远远大于我们的 $k$ 了。通过计算/打表可以得出，当 $n\gt 28$ 时，最小值的个数已经超过了 $10^{18}$。于是对于这种情况，我们只需要构造出其最小值即可。

进行一个套路式贡献的拆。一个数的优美度被计算到答案里，当且仅当选择的区间包含它；而包含它的区间是 $i\cdot (n-i+1)$ 个。这是一个单峰函数，越往中心的 $i$ 其值越大。而为了让答案最小，我们显然要把 $q$ 值最大的放在两边，把最小的放在中间。通过枚举 $\log V\to 1$ 的 $q$ 值，维护前面放了几个，计算出这一次选择的 $q$ 值放在哪两段区间（因为显然是一左一右，放在两边），推一小段柿子即可得到这个值的贡献。在代码中，这一部分实现了函数 `F` 和 `calc`。

接下来考虑如何解决 $n\le 28$ 的部分。这个时候只会有 $5$ 种 $q$ 值，即 $1\sim 5$。我们考虑一个 dp：令 $f_{i,j_1,j_2,j_3,j_4,j_5,z}$ 表示前 $i$ 个位置，填了 $j_1$ 个 $1$，$j_2$ 个 $2$，以此类推；并且所有位置上的数乘上其贡献（即 $i(n-i+1)$）的和是 $z$ 的 $q$ 个数。注意到 $j1$ 是没用的，因为 $j_1=i-j_2-j_3-j_4-j_5$；其次 $i$ 可以通过滚动数组滚掉。又 $28$ 以内 $cnt_2\le 7$，$cnt_3\le 4$，$cnt_4\le 2$，$cnt_5\le 1$，并且计算/打表出 $z$ 最大就 $6\times 10^3$，我们把 dp 数组压缩到了 $8\times5\times3\times2\times(6\times 10^3)$ 的大小。此处的转移是简单的。

最后计算答案时，从 $0\sim 6\times 10^3$ 枚举 $z$，查看 $f_{cnt_2,cnt_3,cnt_4,cnt_5,z}$ 乘上一个 $q$ 对应的方案数是否 $\le k$，若成立输出 $z$，否则将减去对应的个数即可。

最后是有趣的时间复杂度分析。对于 $n\gt 28$ 的部分，复杂度为 $\Theta(\log V)$；对于 $\le 28$ 的部分，我们有 $6$ 维的 dp，其中 $z$ 的理论上界甚至还是 $n^3$ 的。这就是高贵的 $\Theta(n^8)$ 吗？这个 $8$ 哪来的？这不是 $3+\log n$ 吗？更搞笑了，复杂度是高贵的 $\Theta(n^{3+\log n})$。然而实际上远远跑不满，因为 $j_k$ 带一个 $\dfrac{1}{2^k}$ 的常数，总共就是 $\dfrac{1}{2^{15}}$。再加上那个 $n^3$ 实际上只有 $6\times 10^3$，也让这个 dp 做法成为一道常数神题。

最后 Ri 好闪，拜谢 Ri。

代码及考场题解：

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int mod = 998244353;
const int inv2 = 499122177;
const int inv6 = 166374059;
const int maxn = 30;

int Q, n, k;

int F(int l, int r, int n) {
	int s1 = (n + 1) % mod * ((l % mod + r % mod) % mod) % mod * ((r % mod - l % mod + mod + 1) % mod) % mod * inv2 % mod;
	l--;
	int s2 = r % mod * ((r + 1) % mod) % mod * ((r * 2 % mod + 1) % mod) % mod * inv6 % mod;
	int s3 = l % mod * ((l + 1) % mod) % mod * ((l * 2 % mod + 1) % mod) % mod * inv6 % mod;
	return ((s1 - s2 + mod) % mod + s3) % mod;
}

int calc(int n) {
	int l = 0, r = n + 1, c = 0;
	for (int i = 62; i >= 1; i--) {
		int s = (n / (1ll << (i - 1)) + 1) / 2;
		if (!s) continue;
		if (l == n - r + 1) {
			(c += (F(l + 1, l + s / 2, n) + F(r - s + s / 2, r - 1, n)) % mod * i % mod) %= mod;
			l += s / 2;
			r -= s - s / 2;
		} else {
			(c += (F(l + 1, l + s - s / 2, n) + F(r - s / 2, r - 1, n)) % mod * i % mod) %= mod;
			l += s - s / 2;
			r -= s / 2;
		}
	}
	return c;
}

int f[8][5][3][2][6011];
int g[8][5][3][2][6011];

signed main() {
	freopen("npc.in", "r", stdin);
	freopen("npc.out", "w", stdout);
	cin >> Q;
	while (Q--) {
		cin >> n >> k;
		if (n > 28) {
			cout << calc(n) << endl;
		} else {
			int c1 = (n / 1 + 1) / 2;
			int c2 = (n / 2 + 1) / 2;
			int c3 = (n / 4 + 1) / 2;
			int c4 = (n / 8 + 1) / 2;
			int c5 = (n / 16 + 1) / 2;
			memset(f, 0, sizeof(f));
			f[0][0][0][0][0] = 1;
			for (int i = 1; i <= n; i++) {
				memset(g, 0, sizeof(g));
				for (int j2 = 0; j2 <= min(c2, i); j2++) {
					for (int j3 = 0; j3 <= min(c3, i - j2); j3++) {
						for (int j4 = 0; j4 <= min(c4, i - j2 - j3); j4++) {
							for (int j5 = 0; j5 <= min(c5, i - j2 - j3 - j4); j5++) {
								int j1 = i - j2 - j3 - j4 - j5; 
								for (int z = 0; z <= 6000; z++) {
									if (z >= 1 * i * (n - i + 1)) (g[j2][j3][j4][j5][z] += f[j2][j3][j4][j5][z - 1 * i * (n - i + 1)]) %= mod;
									if (z >= 2 * i * (n - i + 1)) (g[j2][j3][j4][j5][z] += f[j2 - 1][j3][j4][j5][z - 2 * i * (n - i + 1)]) %= mod;
									if (z >= 3 * i * (n - i + 1)) (g[j2][j3][j4][j5][z] += f[j2][j3 - 1][j4][j5][z - 3 * i * (n - i + 1)]) %= mod;
									if (z >= 4 * i * (n - i + 1)) (g[j2][j3][j4][j5][z] += f[j2][j3][j4 - 1][j5][z - 4 * i * (n - i + 1)]) %= mod;
									if (z >= 5 * i * (n - i + 1)) (g[j2][j3][j4][j5][z] += f[j2][j3][j4][j5 - 1][z - 5 * i * (n - i + 1)]) %= mod;
								}
							}
						}
					}
				}
				memcpy(f, g, sizeof(g));
			}
			int mul = 1;
			for (int i = 1; i <= c1; i++) mul = mul * i;
			for (int i = 1; i <= c2; i++) mul = mul * i;
			for (int i = 1; i <= c3; i++) mul = mul * i;
			for (int i = 1; i <= c4; i++) mul = mul * i;
			for (int i = 1; i <= c5; i++) mul = mul * i;
			for (int z = 0; z <= 6000; z++) {
				__int128 v = (__int128) f[c2][c3][c4][c5][z] * mul;
				if (k <= v) {
					cout << z << endl;
					break;
				} else {
					k -= v;
				}
			}
		}
	}
	return 0;
}
/*
首先进行一个贡献的拆：每个位置对排列的贡献是 (1 + log lowbit p_i) * i * (n - i + 1)
考虑对于一个 lowbit 序列，对应的排列有多少个。
这是某个经典的组合柿子：\prod (cnt_i)!$
其中 cnt_i 表示该序列中同样的数出现次数。
而 n > 28 时这个东西就 3e17 了，乘上方案数 > 1e18，所以直接求其最小值即可。具体地，从大到小两边填即可。
n <= 28 时就 dp。f[i][j1..j5][z] 表示前 i 个里面，有 j_k 个 1 + log lowbit 为 k，所有贡献为 z 的情况。
首先我们可以压掉 j1，因为 j1 可以通过 i, j2..j5 求出。
然后 i 可以滚动数组掉。
dp 数组变为 f[j2..j5][z]。更具体地，由于 28 以内 1 + log lowbit 为 2,3,4,5 的分别最多 7,4,2,1 个，并且打表发现 ans 大概不会超过 7e3，所以开 f[8][5][3][2][7e3] 即可。 
最后通过遍历最终 dp 数组计算第 k 名即可。
时间复杂度：
当 n > 28 时 O(log V)
当 n <= 28 时 O(n^5 ans)，ans 理论上界是 5n^3 实际上才 7e3，而且这个 n^5 带一个大概 1/2^15 的常数，非常的搞笑。 
哎呀，这个 5 是哪里来的呢，明明就是 logn 对吧。所以复杂度是 O(Qn^{logn + 3})，哈哈。 
*/
```

---

## 作者：MistZero (赞：1)

部分分的 $k \le 2$ 以及抽象的 $\in [10^5,10^6]$ 确实可以说明一些性质。

首先值域是 $\log$ 级别的，而每个数的个数又很多，所以不难想到有很多方案的和其实是一样的。

打个爆搜验证一下发现确实是这样的，且大量的 $k$ 与 $k=1$ 时的答案相等。

---

- $n \le 28$

由于优美度之和相同的方案很多，且 $n>28$ 时前 $10^{18}$ 小的方案均与 $k=1$ 时的答案相同，所以考虑对 $n \le 28$ 的情况跑 DP。

这个时候的和比较小，打个表发现最大的优美度之和似乎是 $9056$，可用的数 $\in [1,5]$。

那么就可以设 $f_{i,j,l,r,p,q}$ 表示选了 $i$ 个 $1$，$j$ 个 $2$，$l$ 个 $3$，$r$ 个 $4$，$p$ 个 $5$，优美度之和为 $q$ 的方案数。

那么转移就很简单了，枚举已有的 $1,2,3,4,5$ 的个数和当前优美度之和即可。

---

- $n > 28$

$k=1$ 时可以进行贪心：把所有数从小到大排序，从中间开始向两边排开。

因为值相同的数的个数很好算，所以只要 $\mathcal{O}(\log n)$ 地模拟这个过程即可。

即维护 $l,r$ 表示当前要从左边的 $l$ 和右边的 $r$ 开始放数，设当前左端和右端均要移动 $w$ 位，则产生 $2i\sum\limits_{j=l-w+1}^l j(n-j+1)$ 的贡献，特殊处理只移动左 / 右一端的情况。

---

代码中 `qsum(l,r)` 表示 $\sum\limits_{i=l+1}^r i$，`qsqr(l,r)` 表示 $\sum\limits_{i=l+1}^r i^2$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int P=998244353,lim=9056;
const int inv2=499122177,inv6=166374059;
void md(int &x,int y) { ((x+=y)>=P)&&(x-=P); }

int T,n,k,cnt[6],fac[16],tot[29];
int f[17][9][5][3][2][9100];
int sum(int x) { return (x%P)*((x+1)%P)%P*inv2%P; }
int qsum(int l,int r) { return (sum(r)+P-sum(l))%P; }
int sqr(int x) { return (x%P)*((x+1)%P)%P*((2*x+1)%P)%P*inv6%P; }
int qsqr(int l,int r) { return (sqr(r)+P-sqr(l))%P; }

void odd() {
    int limit=__lg(n)+1;
    vector<int>num(limit+1);
    for(int i=1;i<=limit;++i) num[i]=(n>>i)+(n>>(i-1)&1)-(i==1);
    int l=n>>1,r=l+2,res=((l+1)%P)*((l+1)%P)%P; bool typ=false;
    for(int i=1;i<=limit;++i) {
        if(typ) md(res,(r%P)*((n-r+1)%P)%P*i%P),++r,--num[i],typ=false;
        if(!num[i]) continue; int now=num[i]>>1;
        md(res,2*((n+1)%P*qsum(l-now,l)%P+P-qsqr(l-now,l))%P*i%P),l-=now,r+=now;
        if(num[i]&1) md(res,(l%P)*((n-l+1)%P)%P*i%P),--l,typ=true;
    }
    cout<<res<<"\n";
}

void even() {
    int limit=__lg(n)+1;
    vector<int>num(limit+1);
    for(int i=1;i<=limit;++i) num[i]=(n>>i)+(n>>(i-1)&1);
    int l=n>>1,r=l+1,res=0; bool typ=false;
    for(int i=1;i<=limit;++i) {
        if(typ) md(res,(r%P)*((n-r+1)%P)%P*i%P),++r,--num[i],typ=false;
        int now=num[i]>>1;
        if(now) md(res,2*((n+1)%P*qsum(l-now,l)%P+P-qsqr(l-now,l))%P*i%P),l-=now,r+=now,num[i]&=1;
        if(num[i]) md(res,(l%P)*((n-l+1)%P)%P*i%P),--l,typ=true;
    }
    cout<<res<<"\n";
}

void solve() {
    cin>>n>>k;
    if(n>28) return (n&1)?odd():even();
    int limit=__lg(n)+1,bas=1;
    memset(cnt,0,sizeof(int)*6);
    for(int i=1;i<=n;++i) ++cnt[__lg(i&(-i))+1],tot[i]=i*(n-i+1);
    sort(tot+1,tot+1+n);
    for(int i=1;i<=limit;++i) bas*=fac[cnt[i]];
    f[0][0][0][0][0][0]=1;
    for(int i=0;i<=cnt[1];++i)
        for(int j=0;j<=cnt[2];++j)
            for(int l=0;l<=cnt[3];++l)
                for(int r=0;r<=cnt[4];++r)
                    for(int p=0;p<=cnt[5];++p) {
                        int all=i+j+l+r+p;
                        if(!all) continue;
                        for(int q=0;q<=lim;++q) {
                            int &now=f[i][j][l][r][p][q]; now=0;
                            if(i&&q>=tot[all]) now+=f[i-1][j][l][r][p][q-tot[all]];
                            if(j&&q>=2*tot[all]) now+=f[i][j-1][l][r][p][q-2*tot[all]];
                            if(l&&q>=3*tot[all]) now+=f[i][j][l-1][r][p][q-3*tot[all]];
                            if(r&&q>=4*tot[all]) now+=f[i][j][l][r-1][p][q-4*tot[all]];
                            if(p&&q>=5*tot[all]) now+=f[i][j][l][r][p-1][q-5*tot[all]];
                        }
                    }
    for(int i=0;i<=lim;++i)
        if((k-=bas*f[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][i])<=0)
            return cout<<i<<"\n",void();
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T,fac[0]=1;
    for(int i=1;i<16;++i) fac[i]=fac[i-1]*i;
    while(T--) solve();
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

> 本文做法参考樱雪喵，如实现等，在笔者完成这道题目的时候，也得到了樱雪喵的指导与帮助，樱雪喵好闪，拜谢樱雪喵。

比较容易观察到的一点是在所有可能的排列中，会有很多相等的值，这是因为 $f(x)$ 有的种类的规模是 $\log n$ 级别的，所以有很多重复 $f(x)$，那这些 $x$ 又不相同，所以一种 $f(x)$ 对应的这些 $x$ 可以随便排列。

一种排列的等价排列有：

$$
\prod_{i=1}cnt_i!
$$

其中 $cnt_i$ 表示 $f(x)=i$ 的 $x$ 的数量。

那么我们打个表，我们发现当 $n>28$ 时与最小值相等的可能排列数量已经超过了 $10^{18}$，这时你求最小值就可以了。

最小值咋求呢，我们考虑贪心，设每个位置出现在区间数量的数组为 $B$，我们发现最小化应该把最小的 $f(x)$ 和最大 $B_i$ 的配对，次小 $f(x)$ 的和次大 $B_i$ 的配对，仔细的证明就不给了，你可以考虑在这种配对的情况下交换任意两个 $f(x)$ 然后比较大小就可以了。

然后考虑快速求出，我们发现对于 $x$ 来说，$f(x)$ 种类很少，每种种类的数量利用位运算也很好求，而 $B_i=i(n-i+1)$ 只有单峰性质没有单调性，所以我们考虑枚举 $f(x)$，然后给其安排位置。

然后安排的时候由于 $B$ 数组的值对称，且具有两边各自具有单调性，所以找最小值可以考虑把 $f(x)$ 按数量平分，左边放一半，右边放一半，如果数量是奇数多的可以随便放，但是如果前面的放置使得某一边多一个就把现在这个多的放在另外一边，灵活调整调整就行了。

然后我们只需要求一个 $B$ 数组的区间和，考虑推推式子：

$$
\sum_{i=l}^r i(n-i+1)
$$

过程就不给了，反正结果是：

$$
\frac 1 2(n+1)(l+r)(r-l+1)+\sum_{i=l}^ri^2
$$

右边可以改为前缀和作差形式，我们都知道：

$$
\sum_{i=1}^xi^2
$$

证明可以数学归纳法，这个太典了我就不证明了。

但是实际上的 $B$ 不长这样，只有左半部分长这样，所以我们需要转化一下：

- 如果区间既有左半部分，又有右半部分，那么拆开成两个区间。
- 如果区间在右半部分，那么对称到左半部分。

参考代码如下：

```cpp
LL S(LL x)//求i^2 的前缀和
{
	x%=mod;
	LL ans=x*(x+1)%mod*(2*x+1)%mod*ksm(6,mod-2)%mod;
	return (ans%mod+mod)%mod;
}
LL Log(LL x)//乱写的，感觉不如 __lg(x)
{
	LL ans=0,cnt=1;
	while(cnt*2<=x)ans++,cnt*=2;
	return ans;
}
LL gt(LL l,LL r)//用于求解 B 数组 [l,r] 的区间和
{
//	cout<<l<<' '<<r<<endl;
	if(l>r)return 0;
	LL mid=(n+1)/2;
	if(l<=mid&&mid<r)return (gt(l,mid)+gt(mid+1,r))%mod;//拆开
	if(l>mid)l=n-l+1,r=n-r+1,swap(l,r);//对称到左半部分
	LL ans=(n+1)%mod*((l+r)%mod)%mod*((r-l+1)%mod)%mod*ksm(2,mod-2)%mod-(S(r)-S(l-1)+mod)%mod;//可以套式子
	ans=(ans%mod+mod)%mod;
	return ans;
}
LL cal(LL n)
{
	LL l=1,r=n,ans=0;
	for(LL i=Log(n)+1;i>=1;i--)
	{
		LL num=(n>>i)+(n>>(i-1)&1);//求数量
		LL ls=(num/2),rs=num-ls;//左右平方
		if(l<=n-r+1)swap(ls,rs);//灵活调整
		//cout<<i<<' '<<l<<' '<<r<<' '<<num<<' '<<ls<<' '<<rs<<endl;
		ans=(ans+i*gt(l,l+ls-1)%mod+i*gt(r-rs+1,r)%mod)%mod;//算贡献
		l+=ls,r-=rs;//缩小可选区间范围
		
	}
	return ans;
}
```

然后是对于 $n\leq 28$，此时 $n$ 很小可以考虑暴力动态规划。

注意到 $4<\log _2 25<5$，所以我们设 $F_{a,b,c,d,e,i}$ 表示 $f(x)=1,f(x)=2,f(x)=3,f(x)=4,f(x)=5$ 的项各选了 $a,b,c,d,e$ 项，目前的权值为 $i$ 的方案数，然后直接动态规划就行了。

不过你还是认为每个 $x$ 是不相等不太好做，我们还是认为其是相等的，然后这样求出的每一种方案都要乘上我们前面推出的等价的排列数量那个式子。

这里的代码就没啥好说的了，可以直接看看代码，应该不难懂。

然后最后我们从小到大枚举一个 $i$ 表示我们现在统计权值为 $i$ 的方案数，记得乘上等价的排列的数量，注意，如果统计的方案数超过了 $k$，那么此时的 $i$ 就是答案。

时间复杂度不好描述，建议手算，然后空间吃得比较紧，需要压着开。

好久没写过这么长的题解和如此多的注释了，主要是第一眼看题解代码的时候确实是很茫然，所以就想将明白一点。

这题确实是好题，就是有点小烦，拆成两题就好了。

樱雪喵的实现，尤其是动态规划那一部分，写得真的很优雅。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
//const LL inf;
const LL N=1e6+5;
const LL M=11000;
const LL mod=998244353;
//const LF eps;
//const LL P;
LL T,n,k,a[N],lg[N],b[N],cnt[6],tot,fac[N],now[6],f[16][9][5][3][2][11005];
LL lowbit(LL x)
{
	return x&-x;
}
LL ksm(LL x,LL y)
{
	LL ans=1;
	while(y)
	{
		if(y&1)ans=ans*x%mod;
		x=x*x%mod,y>>=1;
	}
	return ans;
}
LL S(LL x)
{
	x%=mod;
	LL ans=x*(x+1)%mod*(2*x+1)%mod*ksm(6,mod-2)%mod;
	return (ans%mod+mod)%mod;
}
LL Log(LL x)
{
	LL ans=0,cnt=1;
	while(cnt*2<=x)ans++,cnt*=2;
	return ans;
}
LL gt(LL l,LL r)
{
//	cout<<l<<' '<<r<<endl;
	if(l>r)return 0;
	LL mid=(n+1)/2;
	if(l<=mid&&mid<r)return (gt(l,mid)+gt(mid+1,r))%mod;
	if(l>mid)l=n-l+1,r=n-r+1,swap(l,r);
	LL ans=(n+1)%mod*((l+r)%mod)%mod*((r-l+1)%mod)%mod*ksm(2,mod-2)%mod-(S(r)-S(l-1)+mod)%mod;
	ans=(ans%mod+mod)%mod;
	return ans;
}
LL cal(LL n)
{
	LL l=1,r=n,ans=0;
	for(LL i=Log(n)+1;i>=1;i--)
	{
		LL num=(n>>i)+(n>>(i-1)&1);
		LL ls=(num/2),rs=num-ls;
		if(l<=n-r+1)swap(ls,rs);
		//cout<<i<<' '<<l<<' '<<r<<' '<<num<<' '<<ls<<' '<<rs<<endl;
		ans=(ans+i*gt(l,l+ls-1)%mod+i*gt(r-rs+1,r)%mod)%mod;
		l+=ls,r-=rs;
		
	}
	return ans;
}

int main()
{
//	freopen("npc.in","r",stdin);
//	freopen("npc.out","w",stdout);
	fac[0]=1;
	for(LL i=1;i<=15;i++)fac[i]=fac[i-1]*i;
	for(int i=2;i<=N-5;i++)
	{
		lg[i]=lg[i/2]+1;
	}
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		LL x=cal(n);
		tot=1;
		if(n>28)
		{
			printf("%lld\n",x);
			continue;
		}
		for(int i=1;i<=5;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)
		{
			a[i]=1+lg[lowbit(i)];
			b[i]=i*(n-i+1);
			cnt[a[i]]++;
		}
		for(int i=1;i<=lg[n];i++)tot=tot*fac[cnt[i]];
		f[0][0][0][0][0][0]=1;
		for(now[1]=0;now[1]<=cnt[1];now[1]++)
		for(now[2]=0;now[2]<=cnt[2];now[2]++)
		for(now[3]=0;now[3]<=cnt[3];now[3]++)
		for(now[4]=0;now[4]<=cnt[4];now[4]++)
		for(now[5]=0;now[5]<=cnt[5];now[5]++)
		{
			LL sum=0;
			for(int i=1;i<=5;i++)sum+=now[i];
			if(!sum)continue;
			for(int i=0;i<=M;i++)
			{
				LL cnt=0;
				for(int j=1;j<=5;j++)
				{
					if(now[j]==0)continue;
					if(i-j*b[sum]<0)continue;
					now[j]--;
					cnt+=f[now[1]][now[2]][now[3]][now[4]][now[5]][i-j*b[sum]];
					now[j]++;
				}
				f[now[1]][now[2]][now[3]][now[4]][now[5]][i]=cnt;
			}
		}
		LL sum=0;
		for(LL i=1;i<=M;i++)
		{
			sum+=tot*f[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][i];
			if(sum>=k)
			{
				printf("%lld\n",i);
				break;
			}
		}
	}
	return 0;
}
//RP++
```

---

## 作者：_lbw_ (赞：1)

哎呀呀呀呀，怎么每个挑战 NPC 都是爆搜。(~~NPC 不是只能爆搜吗~~)。

我们考虑一下，转化过后即为有数组 $a_i=\log\textsf{lowbit(i)}+1，b_i=i(n-i+1)$。

任意排 $a$，求 $\sum a_ib_i$ 第 $k$ 小的值。

我们发现看上去确实非常 NPC 啊，但题目有一个性质：$a$ 的值域很小。

于是预处理出最低位为 $i$ 的个数 $L_i$，由于重复的很多，我们考虑让 $b$ 唯一对应一个 $i$，然后每个 $i$ 的被对应的次数恰好为 $L_i$，那么每种对应方式实际上有 $v=\prod L_i!$ 种内部排法，先将 $k$ 变为 $k$ 除以 $v$ 上取整。

然后我们发现在 $n$ 稍微大一点时 $v$ 绝对大于 $k$，答案即为最小值。

根据排序不等式，最小值是一个正着排一个倒着排，这个东西分段计算一下是容易的。

经过一通计算，我们发现 $30$ 甚至 $29$ 都满足答案是最小值。

那么接下来只要计算 $n\leq 29$ 的情况了，NPC 是很难的，我们只能爆搜了。

但是乱搜是不行的，考虑 dp，把每个数当前对应了多少次和优美度总和记进状态里。

这时我一通计算，得出状态数有 $10^{11}$ 的惊人结论(这个结论是错的)。

于是我使用了 map 进行实现，在 $29$ 时要跑 1.5s，这可怎么办。

没事，打表会出手，因为当 $n\geq24$ 时转化后的 $k$ 很小，直接对 dp 跑出来的结果进行打表，而 $n<24$ 跑的飞快!

时间复杂度 $\mathcal{O}(????)$。

[瑇码](https://www.luogu.com.cn/paste/oaoi1eom)。



---

## 作者：E1_de5truct0r (赞：1)

数据分治诈骗题，不过我赛时不会。

---

首先，经过观察，可以发现这个序列中会包含很多的相同的数，比如 $1$ 就有 $\lfloor n/2\rfloor$ 个。因此大胆猜想在 $n$ 很大的时候，这个第 $k$ 小的大小和最小的大小是一样的（因为 $\operatorname{lowbit}$ 相同的数任意排列对答案无影响，会产生阶乘级别的贡献，显然随着 $n$ 增大很快就会超过 $10^{18}$）。

用放缩法，跑一下 $\prod\limits_{i=1}^{\log n}(n/2^i)!$。显然答案不小于左式，而发现左式在 $n=29$ 的时候就跑炸了。

然后就可以对 $n \lt 29$ 和 $n \geq 29$ 数据分治。

- $n \lt 29$

观察到此时 $\forall 1 \leq i \lt 29,\lfloor\log_2 \operatorname{lowbit(i)}\rfloor+\,1 \leq 5$ 都成立。而对于一种排列，答案为 $\sum f(p_i)i(n-i+1)$，大概是在 $10^4$ 量级的。

于是可以打一个 DP，$f_{i,a,b,c,d,x}$ 表示排列长度为 $i$，$1$ 有 $a$ 个，$2$ 有 $b$ 个，$3$ 有 $c$ 个，$4$ 有 $d$ 个，$5$ 有 $i-a-b-c-d$ 个，答案为 $x$ 的方案数。可以预处理每种类型的数的数量，转移就枚举加什么类型的数，乘一下方案数即可。最后统计答案就从大到小枚举 $x$，当方案数累加 $\geq k$ 的时候就退出，此时的 $x$ 就是答案。

这个大约会跑 $nW \cdot 5^5$ 次（$W$ 为最大值域，大约为 $10^4$），不过常数很小。（实在不行可以把表打出来）

- $n \geq 29$

直接算答案是颇困难的，考虑对于一个数 $f(i)$ 它如果放在 $p_i$，它会被计算 $p_i(n-p_i+1)$ 次，即产生这么多次贡献。

那么我们就是要让 $f(i)$ 和 $i(n-i+1)$ 两两匹配，使得乘积和最小。显然根据小奥或者高中数学知识我们知道，一个升序一个降序排列出来的答案是最小的。

于是就有了一个暴力排序的 $O(n \log n)$ 做法。但是这样还是太慢了。我们观察到 $f(i)$ 的值域很小，所以我们考虑把所有的 $i(n-i+1)$ 从大到小排序之后分成若干段，只需要知道每个值的数量，他们对一段的贡献是相等的，乘上对应段的和就是答案。

首先，这个排序我们可以免去。从小奥的“和一定差小积大”可以得到，$i$ 和 $n/2$ 越接近，$i(n-i+1)$ 越大。由于这个 $i$ 在 $n/2$ 的左边还是右边其实是对称的，我们对于每一种 $f(i)$ 的值，所需的一定是在 $n/2$ 的一左一右的某两个接近对称区间内的 $i(n-i+1)$。这个我们可以使用双指针，对于边界问题，我们优先扩展离 $n/2$ 更近的一端。

接下来，我们要求的就是快速求形如 $\sum_{i=l}^{r} i(n-i+1)$ 这样的式子。显然我们可以把 $n-i+1$ 拆开，得到：

$$\sum_{i=l}^{r} in-i^2+i$$

拆开得到：

$$n\sum_{i=l}^{r} i-\sum_{i=l}^{r} i^2+\sum_{i=l}^{r}i$$

小奥讲过两个式子：

- $\sum_{i=l}^{r}i=\dfrac{(l+r)(r-l+1)}{2}$。

- $\sum_{i=1}^{x} i^2=\dfrac{i(i+1)(2i+1)}{6}$，我们令其为 $g(x)$。

显然 $\sum_{i=l}^{r} i^2=g(r)-g(l-1)$。把这两个式子带回去就可以得到等价求法：

$$\dfrac{n(l+r)(r-l+1)}{2}-\left(\dfrac{r(r+1)(2r+1)}{6}-\dfrac{(l-1)l(2l-1)}{6}\right)+\dfrac{(l+r)(r-l+1)}{2}$$

因此我们可以在 $O(1)$ 的时间内快速求出一段区间内的 $i(n-i+1)$ 之和。加上枚举每一种 $f(i)$ 的取值即可做到 $O(\log n)$。

---

将两种做法拼起来即可通过本题。

---

## 作者：TonviaSzt (赞：0)

#### 绝世好题。逐步推导部分分逼近正解。

题解稍长，请耐心读完。

---

题目大意：给定序列 $a=\lbrace1,2,\dots n\rbrace$，求 $n!$ 种排列中 $\sum_{i=1}^n\sum_{j=i}^n\sum_{k=i}^{j}1+\log_2{\operatorname{lowbit}(a_i)}$ 的第 $k$ 小值。

照搬具体范围如下：

----

#### 【数据范围】

**本题各测试点时间限制不相同。具体地，每个点的时间限制为 $\max(q\times 0.5, 2)\ \rm{s}$**。

|  测试点编号  |        $n$         |      $k \leq$       | $q = $ |
| :----------: | :----------------: | :-----------------: | :----: |
|  $1 \sim 3$  |     $\leq 10$      |        $n!$         |  $2$   |
|  $4 \sim 8$  |    $\leq 10^3$     |         $2$         |  $7$   |
| $9 \sim 13$  | $\in [10^5, 10^6]$ | $\min(10^{18}, n!)$ |  $7$   |
| $14 \sim 17$ |    $\leq 10^6$     | $\min(10^{18}, n!)$ |  $7$   |
| $18 \sim 25$ |   $\leq 10^{18}$   | $\min(10^{18}, n!)$ |  $10$  |

---

### 题解：

显然地，式子可以化简成 $\sum_{i=1}^ni\times (n-i+1)(1+\log_2{\operatorname{lowbit}(a_i)})$。
为了描述方便，将 $a_i$ 赋值为 $(1+\log_2{\operatorname{lowbit}(a_i)}$，原式化为 $\sum_{i=1}^ni\times (n-i+1)\times a_i$。

**对于 $1\sim 3$ 测试点**，直接暴力求出 $n!$ 种取值即可，不再赘述。
**对于 $4\sim 8$ 测试点**，发现 $k$ 极小，

- 考虑 $k=1$，由小奥得，设序列 $b$，$b_i=i\times (n-i+1)$，答案即为 $a$ 中最小的 $a_i$ 乘上 $b$ 中最大的 $b_i$ 加上 $a$ 中次小的 $a_i$ 乘上 $b$ 中次大的 $b_i$，以此类推求和。
- 考虑 $k=2$，设 $k=1$ 时 $a$ 的答案序列为 $A$，发现由于 $b_1=b_n$ ，只需调换 $A_1,A_n$ 位置即可，答案大小不变，仍为最小值。

**对于 $9\sim 13$ 测试点**， 受 $4\sim 8$ 测试点启发，可以发现 $Ans$ 为最小值的答案实际上有很多，
设序列 $A,B$ 分别为 $a,b$ 排序后的序列，容易发现 $A_i$ 的取值极小，考虑计算答案同为最小值的方案数，即计算与序列 $A$ 同构的序列总数，易得答案为 $A_i$ 中每个值个数的阶乘的乘积，举个例子，设 $A=\lbrace1,1,1,1,1,2,2,3,4\rbrace$，同构数即 $5!\times 2!\times 1!\times 1!=240$ 种。
可以发现当 $n\ge 39$ 时，$A$ 中光是 $1$ 的个数就达到了 $20$，同构数超过了 $10^{18}$，所以对于该段测试点，答案与 $k=1$ 时相等，$O(n)$ 计算即可。

**对于 $14\sim 17$ 测试点**，手算一下发现同构数小于等于 $10^{18}$ 的 $n$ 上界为 $28$，因此我们只需计算 $n\le28$ 时第 $k$ 小值的大小，此时 $A$ 的取值只有 $1,2,3,4,5$ 五种（$A$ 与上文含义相同），考虑 dp 求方案数，设 $f[a][b][c][d][e][i]$ 表示 $A$ 中前 $a+b+c+d+e$ 位中 $1,2,3,4,5$ 的个数分别是 $a,b,c,d,e$ 且此时总价值为 $i$ 的方案数 **（不考虑同构情况）**，可得转移方程为

 $
\begin{aligned}
f[a][b][c][d][e][i] &=f[a-1][b][c][d][e][i-sum\times (n-sum+1)]\\ &+f[a][b-1][c][d][e][i-sum\times (n-sum+1)\times 2]\\ &+f[a][b][c-1][d][e][i-sum\times (n-sum+1)\times 3]\\ &+f[a][b][c][d-1][e][i-sum\times (n-sum+1)\times 4]\\ &+f[a][b][c][d][e-1][i-sum\times (n-sum+1)\times 5]
\end{aligned}
$，其中 $sum=a+b+c+d+e$。

注意到 $f[0][0][0][0][0][0]=1$。

想到状态的设置，式子还是比较好推的，不建议细看上面的式子。

求解的时候从 $i=0$ 向上累加 $f[\text{a 中 1 的个数}][\text{a 中 2 的个数}][\text{a 中 3 的个数}][\text{a 中 4 的个数}][\text{a 中 5 的个数}][i]$，记得考虑乘上相同 $a_j$ 的排列情况，累加的和超过 $k$ 时立刻得到答案为 $i$。

**对于 $18\sim 25$ 测试点**，唯一的问题在于 $n$ 极大时如何处理，由于 $a$ 的取值不超过 $\log n$，可以 $\log n$ 时间内求出每个不同 $a_i$ 的个数，然后推式子求答案即可。

推式子部分明显比 dp 部分容易，毕竟考试时没有选手拿 68pts 的部分分。

在一步步攻取部分分的努力下，最后这题就 AC 了，这是这题得出的最重要的方法。

---

---

## 作者：Graphcity (赞：0)

这道题看起来就不是很正常，所以我们也得想些不正常的做法。看到第 $k$ 小要取模，猜测 $n$ 大于等于某个数时前 $10^{18}$ 个全是最优解。

这个阈值很小，至少不会达到 32。因为 $n=32$ 时，不同的 $f(x)$ 只有五种，每一种分别有 $16,8,4,2,1$ 个。由于相同的 $f(x)$ 在排列中随意调换顺序结果都不会改变，所以最优解至少有 $16!\times 8!\times 4\times 2!\times 1!\ge 10^{18}$ 种。

这就好办了。我们先对 $n$ 大于等于阈值的情况做考虑。第一步是统计每一种 $f$ 值对应多少个 $x$。

不妨枚举 $x$ 与 $n$ 在二进制下的最长公共前缀（高位在前面），如果这个前缀的后一位是 1，那就把 $x$ 这一位强制变为 0，这样 $x$ 再后面的位可以随便填了，每种 $f$ 的个数也是好统计的。

整个过程类似数位 DP。接下来是第二步，也就是统计答案。容易发现整个排列中第 $i$ 个数的贡献次数为 $cnt_i=i(n-i+1)$，这是一个单峰的序列。

根据排序不等式，$f$ 正序排列后一一对应 $cnt$ 倒序排列可以达到最小值。那么 $f$ 的一段前缀填的位置就是一段 $cnt$ 的区间。

不妨枚举前缀，这样可以求出这个前缀对应的区间。$\sum_{i=l}^rcnt_i$ 是好计算的。通过差分的方式就可以求出所有答案。时间复杂度 $O(q\log n)$。

接下来是小于等于阈值的部分。通过打表可以发现阈值不超过 30，那我们就以 30 为阈值吧。

还是一样，根据排序不等式，可以算出来 $n=30$ 的最劣解不超过 $6\times 10^3$。那我们完全可以统计出每一个最终答案对应的排列个数。

设 $f_{s_{0\cdots 4},k}$ 表示 $f=0\cdots 4$ 的值分别填了 $s_{0\cdots 4}$ 个，当前答案为 $k$ 的排列个数。转移就是枚举下一位填的数字的 $f$ 是多少。

算一下，$16\times 8\times 4\times 2\times 6000=6144000$，完全是可以接受的。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,lim=31,Max=6000,Mod=998244353;
const int i2=(Mod+1)/2,i6=(Mod+1)/6;

int T,n,m,ans;
int f[17][9][5][3][2][Max+5];

inline int PointCost(int x) {x%=Mod; return x*(n%Mod-x+1+Mod)%Mod;}
inline int Cost(int n)
{return ((::n+1)%Mod*(n+1)%Mod*n%Mod*i2%Mod-n*(n+1)%Mod*(n+n+1)%Mod*i6%Mod+Mod+Mod)%Mod;}
inline int Cost(int l,int r) {l%=Mod,r%=Mod; return (Cost(r)-Cost(l-1)+Mod)%Mod;}
inline int lowbit(int x) {return __lg(x&-x);}
inline void Work()
{
    static int s[64]; memset(s,0,sizeof(s));
    s[lowbit(n)]++; Rof(i,60,0) if(n&(1ll<<i))
    {
        int m=n-(n&((1ll<<i+1)-1));
        For(j,0,i-1) s[j]+=(1ll<<i-j-1);
        if(m) s[lowbit(m)]++;
    }
    for(int i=0,sum=0,pre=0;i<=60;++i)
    {
        sum+=s[i]; if(sum<=0) continue; int res;
        if(n&1)
        {
            res=(Cost((n+1)/2+1,(n+1)/2+sum/2)*2+PointCost((n+1)/2))%Mod;
            if(sum%2==0) res=(res-PointCost((n+1)/2+sum/2)+Mod)%Mod;
        }
        else
        {
            res=Cost(n/2+1,n/2+sum/2)*2%Mod;
            if(sum%2==1) res=(res+PointCost(n/2+sum/2+1))%Mod;
        }
        ans=(ans+i*(res-pre+Mod))%Mod,pre=res;
    }
    cout<<ans<<endl;
}
inline int Fac(int x) {int res=1; For(i,1,x) res*=i; return res;}
inline void Solve()
{
    cin>>n>>m;
    if(n&1) ans=(Cost(1,n/2)*2+PointCost(n/2+1))%Mod;
    else ans=Cost(1,n/2)*2%Mod;
    if(n>=lim) {Work(); return;}
    memset(f,0,sizeof(f));
    static int s[64]; memset(s,0,sizeof(s));
    For(i,1,n) s[lowbit(i)]++;
    f[0][0][0][0][0][0]=1;
    int w=1; For(i,0,60) w*=Fac(s[i]);
    For(a,0,s[0]) For(b,0,s[1]) For(c,0,s[2]) For(d,0,s[3]) For(e,0,s[4])
    {
        int pos=a+b+c+d+e+1,res=pos*(n-pos+1);
        For(k,0,Max) if(f[a][b][c][d][e][k])
        {
            int now=f[a][b][c][d][e][k];
            if(a<s[0]) f[a+1][b][c][d][e][k]+=now;
            if(b<s[1]) f[a][b+1][c][d][e][k+res]+=now;
            if(c<s[2]) f[a][b][c+1][d][e][k+res*2]+=now;
            if(d<s[3]) f[a][b][c][d+1][e][k+res*3]+=now;
            if(e<s[4]) f[a][b][c][d][e+1][k+res*4]+=now;
        }
    }
    for(int i=0,sum=0;i<=Max;++i)
    {
        sum+=f[s[0]][s[1]][s[2]][s[3]][s[4]][i];
        if(sum*w>=m) {cout<<ans+i<<endl; return;}
    }
}

signed main()
{
    cin>>T;
    while(T--) Solve();
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题目传送门

[P9839](https://www.luogu.com.cn/problem/P9838)

洛谷 NOIP2023 模拟赛 T3。

祝大家 NOIP2023 rp++。

### 分析

题意比较冗长，但只要包含某个位置的区间数算作其贡献，就比较好算了。

位置 $x$ 会被 $i \times (n-i+1)$ 个区间包含，即贡献为 $i \times (n-i+1)$。贡献是一个关于 $i$ 的二次函数，对称轴在 $[1,n]$ 的中心。

先看部分分，有 $[10^5,10^6]$ 这一档。同时限制上界和下界是很少见的，这启发我们进行数据点分治。

同时，我们发现，对于 $n \ge 2$ 的数据，由于贡献的对称性，有不少于两个最小值。启发我们找最小值的个数。发现贡献对称轴两边可以调换，优美度相同的诗内部可以排列，次数很多。当 $n > 28$ 时，最小值的个数一定超过 $10^{18}$ 个，此时算最小值即可。

根据排序不等式，如果取得最小值，一定是优美度最大的诗搭配贡献最小的位置，优美度次大的诗搭配贡献次小的位置，以此类推。

为了以亚线性的时间复杂度算出来，我们需要推出 $\displaystyle\sum_{i=1}^{x} (i \times (n-i+1))$ 的通项公式。

$$\displaystyle\sum_{i=1}^{x} (i \times (n-i+1))$$

$$=\displaystyle\sum_{i=1}^{x} (i \times (n+1) - i^2)$$

$$=(n+1)\displaystyle\sum_{i=1}^{x}i - \displaystyle\sum_{i=1}^{x} i^2$$

$$=\frac{(n+1)(x+1)x}{2} - \frac{x(x+1)(2x+1)}{6}$$

注意这里为了防止爆 ```long long```，的除二和除六应当使用逆元，事实上，对与两个常用模数 $10^9+7$ 和 $998244353$，$x = 2,3,6$ 的逆元为模数加一除 $x$。

然后，算出每种优美度为 $i$ 的诗有 $\lfloor \frac{n+2^{i-1}}{2^i} \rfloor$ 个。

由于要枚举每种优美度的诗，这里的时间复杂度为 $O(\log{n})$。

对于 $n \le 28$ 的数据，可以进行 DP。发现优美度一定只有最多 $5$ 种取值，不妨把它们出现的次数都记下来，再记下权值，就是一个六维的 DP 数组，计算权值最大为 $5982$，在 $n = 28$ 且 $k = 10^{18}$ 时取得。

发现很多权值都是取不到的，也就是定义了很多无用状态，所以此时记忆化搜索会更快。

这里的时间复杂度相当于实际访问的状态数。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO
{
	#ifdef ONLINE_JUDGE
	constexpr int fsize = 1<<24;
	#define getchar() ((IO::si!=IO::ti||(IO::ti=(IO::si=IO::input)+fread(IO::input,1,IO::fsize,stdin))),IO::si!=IO::ti?*(IO::si++):EOF)
	#define putchar(c) ((IO::out.so!=IO::out.to||(fwrite(IO::out.output,1,IO::fsize,stdout),IO::out.so=IO::out.output)),*(IO::out.so++)=c)
	char input[fsize],*si = input,*ti = input;
	struct output_stream
	{
		char output[fsize],*so = output,*to = output + fsize;
		inline ~output_stream()
		{
			if(so == output) return;
			fwrite(output,1,so-output,stdout);
			so = output;
		}
	}out;
	#endif
	template<typename T = int>inline T read()
	{
		int c = getchar(),p = 1;
		T x = 0;
		while(c < 48||c > 57)
		{
			if(c == 45) p = -1;
			c = getchar();
		}
		while(48 <= c&&c <= 57)
		{
			x = (x<<3)+(x<<1)+(c^48);
			c = getchar();
		}
		return x*p;
	}
	template<typename T>inline void write(T x)
	{
		static int c[40],cnt = 0;
		if(x < 0) putchar(45),x = -x;
		if(!x) putchar(48);
		while(x) c[++cnt] = x%10^48,x /= 10;
		while(cnt) putchar(c[cnt--]);
	}
}
using IO::read;
using IO::write;
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define ull unsigned long long
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define debug(x) cerr<<#x<<'='<<x<<'\n'
constexpr int mod = 998244353;
constexpr int p2 = (mod + 1) >> 1,p6 = (mod + 1) / 6;
constexpr void add(ll &x,ll y) {(x += y) >= mod&&(x -= mod);}
int dp[15][8][5][3][2][6000],t,w;
ll fac[20],cnt[70],n,k;
int dfs(int a,int b,int c,int d,int e,int v)
{
	if(a < 0||b < 0||c < 0||d < 0||e < 0||v < 0) return 0;
	int &u = dp[a][b][c][d][e][v]; 
	if(~u) return u;
	int l = a+b+c+d+e;
	l = l * (n-l+1);
	return u = dfs(a-1,b,c,d,e,v-l)+dfs(a,b-1,c,d,e,v-2*l)+dfs(a,b,c-1,d,e,v-3*l)+dfs(a,b,c,d-1,e,v-4*l)+dfs(a,b,c,d,e-1,v-5*l);
}
inline ll calc(ll x)
{
	x %= mod;
	return x * (x+1) % mod * ((n+1) % mod * p2 % mod - (x<<1|1) * p6 % mod + mod) % mod;
}
int main()
{
	t = read();
	fac[0] = fac[1] = 1;
	F(i,2,16) fac[i] = fac[i-1] * i;
	while(t--)
	{
		n = read<ll>(),k = read<ll>();
		w = 0;
		while((1ll<<w) <= n) ++w;
		F(i,1,w) cnt[i] = (n+(1ll<<(i-1)))>>i;
		F(i,w+1,64) cnt[i] = 0;
		if(n <= 28)
		{
			F(i,1,w) k = (k - 1) / fac[cnt[i]] + 1;
			memset(dp,0xff,sizeof(dp));
			dp[0][0][0][0][0][0] = 1;
			F(i,1,5982) 
			{
				k -= dfs(cnt[1],cnt[2],cnt[3],cnt[4],cnt[5],i);	
				if(k <= 0) 
				{
					write(i);
					break;
				}
			}
		}
		else
		{
			ll l = 1,r = n,ret = 0;
			D(i,w,2)
			{
				ll s1 = cnt[i] >> 1,s2 = (cnt[i] + 1) >> 1;
				if(l-1 < n-r) swap(s1,s2);
				add(ret,i*(calc(l+s1-1)-calc(l-1)+calc(r)-calc(r-s2)+mod+mod)%mod);
				l += s1,r -= s2;
			}
			add(ret,calc(r)),add(ret,mod - calc(l-1));
			write(ret);
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：shinkuu (赞：0)

非常好的题！赞美出题人。具体讲讲如何想出来这种题。

容易发现直接做非常难做，一是数据范围非常之大，二是这本身就是相当于一个重排一个序列的问题，计数也很困难。

这种题就大概率要从**找性质**入手（类似 P2150 寿司晚宴），于是先观察样例及解释，如果你注意力比较集中的话，会注意到，$n=3$ 时就已经出现了很多重复的答案值了。

于是思考这个性质是否具有一般性，为什么会有这个性质。我们发现原来的 $f(x)$ 中就有很多**重复的值**。于是，我们只需要构造出来一个答案最小的序列，再将其中 $\forall i, f(x)=i$ 的 $x$ 重新排顺序，这样序列的答案**仍然是最小的**。

于是**对于 $n$ 比较大的情况，我们就可以直接构造出最小的答案**。具体怎么构造呢？显然是要把 $f(x)$ 大的尽可能靠边。模拟这个过程即可，按照 $f(x)$ 从大到小枚举，则 $f(x)$ 的贡献就要乘上 $\sum_{i\in[l,r]}(i\times(n+1-i))$ 以及一些零散的 $i\times(n+1-i)$ 这样的值。上面的式子的求法就是转成 $S(r)-S(l-1),S(x)=\sum_{i\le x}(i\times(n+1-i))=\sum (i\times(n+1)-i\times i)=(n+1)\times \sum i-\sum i^2$ 于是就可以 $O(1)$ 求了。

同时发现我们这个思路和第 $2,3$ 档分的思想相符，也从侧面说明正确性。（bushi）

接下来就是解决 $n$ 比较小的情况了。毛估估一下需要解决的 $n$ 的上界 $\ge20$（其实是 $28$），$n!$ 的暴力不可过。思考状压，但是又大概要 $O(n3^n)$。

此时突然发现，为什么需要状压呢？实际上 $f(x)\le 5$，为什么不能**强行记录每个 $f(x)$ 剩余的数量**呢？

于是考虑一个类似背包的 dp，设当前 dp 到第 $i$ 位，要求剩下的 $f(x)$ 贡献之和为 $j$，剩下的 $f(x)=k$ 的 $k$ 数量为 $g_k$ 的方案数。这个东西记忆化搜索一下，发现总状态数小于 $11\times6\times4\times2\times2\times28\times10000\approx3\times 10^7$，大概手写一个哈希表就可以过了。

code：

```cpp
bool Mbe;
ll n,m,k,a[107];
const int base=19260817;
const int p=1e7+7;
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
struct HashTable{
	int tot,head[M];
	struct node{
		ll val;int k,nxt;
	}e[N];
	il ll insert(ll x,int k,int y){
		e[++tot]={x,k,head[y]},head[y]=tot;
		return x;
	}
	ll find(int x,int y){
		go(i,x){
			if(e[i].k==y){
				return e[i].val;
			}
		}
		return -1;
	}
}H;
il int getSum(ll x){
	int ret=0;
	ll a=x,b=x+1,c;
	if(a%2==0){
		a/=2;
	}else{
		b/=2;
	}
	ret=Mod(ret,(a%mod)*(b%mod)%mod*((n+1)%mod)%mod);
	a=x,b=x+1,c=2*x+1;
	if(a%2==0){
		a/=2;
	}else{
		b/=2;
	}
	if(a%3==0){
		a/=3;
	}else if(b%3==0){
		b/=3;
	}else{
		c/=3;
	}
	ret=Mod(ret,mod-(a%mod)*(b%mod)%mod*(c%mod)%mod);
	return ret;
}
il int getHash(int x,int y,vector<int> &g){
	int ret=(x*100000+y)%p;
	for(int i:g){
		ret=(1ll*ret*base+i)%p;
	}
	return ret;
}
ll dfs(int u,int s,vector<int> &g){
	if(s<0){
		return 0;
	}
	if(u==n+1){
		return !s;
	}
	int x=getHash(u,s,g);
	ll ret;
	if(~(ret=H.find(x,u*100000+s))){
		return ret;
	}
	ret=0;
	rep(i,1,k){
		if(g[i-1]){
			g[i-1]--;
			ret+=(g[i-1]+1)*dfs(u+1,s-1ll*u*(n+1-u)*i,g);
			g[i-1]++;
		}
	}
	return H.insert(ret,u*100000+s,x);
}
void Yorushika(){
	scanf("%lld%lld",&n,&m);
	bool fl=0;
	int ans=0;
	ll p=1,tmp=n;
	k=0;
	while(tmp){
		a[++k]=(tmp+1)/2;
		tmp-=(tmp+1)/2;
	}
	drep(i,k,1){
		ll x=a[i];
		if(fl){
			ans=Mod(ans,(p%mod)*((n+1-p)%mod)%mod*(i%mod)%mod);
			p++,fl=0,x--;
		}
		ans=Mod(ans,(i128)2*Mod(getSum(p+x/2-1),mod-getSum(p-1))*i%mod);
		p+=x/2,x&=1;
		if(x){
			ans=Mod(ans,(p%mod)*((n+1-p)%mod)%mod*(i%mod)%mod);
			fl=1;
		}
	}
	if(n>28){
		printf("%d\n",ans);
		return;
	}
	vector<int> g;
	tmp=n;
	while(tmp){
		g.eb((tmp+1)/2);
		tmp-=g.back();
	}
	i128 sum=0;
	rep(i,ans,1e9){
		sum+=dfs(1,i,g);
		if(sum>=m){
			printf("%d\n",i);
			return;
		}
	}
}
bool Med;
signed main(){
	cerr<<(&Mbe-&Med)/1048576.0<<'\n';
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：xs_siqi (赞：0)

思维题和 dp 的结合题。可惜场上连最基本的结论都没想到。

这题的部分分设的很强，很有启发性。

### $k\leq 2$

我们考虑这档部分分怎么做。首先对于一个点，我们可以算出它被哪些区间所包含。设这个点的位置为 $x$，稍微画图再结合乘法原理可知，它会被 $x\times (n-x+1)$ 个区间包含。

如何构造出一组最小的解？注意到这个贡献的两个项相加是一个定值，即 $n+1$，说明了这个贡献随 $x$ 增大先变大后变小，是一个反比函数。

设 $x$ 最后一个 $1$ 的位置为 $w$，那么我们按 $w$ 从大到小排序，然后分别从两端往中间放就好了。

然后我们发现一个惊人的性质：对于所有 $n$，$k=1$ 与 $k=2$ 的答案完全一样！这也为下一个部分有所启发。

### $n\in [29,10^6]$

继续考虑这个部分分怎么做。首先有一个性质是，假如两个点的 $w$ 相等，那么将他们的位置互换不会影响答案的大小。

猜一个结论：当 $k$ 比较大的时候，所有情况的答案都是最小值。

我们发现当 $n=29$ 时，分别会产生 $16$ 个 $w=1$，$8$ 个 $w=2$，$4$ 个 $w=3$，$2$ 个 $w=4$，$1$ 个 $w=5$，此时至少有 $16!\times 8!\times 4!\times 2!\times 1$ 个状态是相同的。简单算一下这个东西已经超过 $10^{18}$ 了。所以我们对于 $n\geq 29$ 的情况我们只需要处理最小值就好了，最小值考虑上面那种构造就可以了。

### $n\in [29,10^{18}]$

考虑到 $10^{18}$ 时，这个东西显然不能再让我们去一个一个填了，那么我们考虑能否用一种方式将他们整体计算贡献。

不难想到对于 $w$ 相同的，我们一起处理。这个时候遇到了第一个问题，如何快速计算 $[1,n]$ 内 $w$ 相等的值有多少个？

你发现这个东西本来就很像树状数组跳的操作。或者我们直接枚举一下：

```
1 2  3  4   5   6   7   8    9    10   11   12
1 10 11 100 101 110 111 1000 1001 1010 1011 1100
```

注意到一个性质：对于 $w=2$ 的，在 $x=2,6,10$ 时出现，对于 $w=3$ 的，在 $x=4,12$ 时出现，可以发现，对于一个 $w$ 起始的 $x$，就是 $2^{w-1}$，两个元素相隔的距离，恰为 $2^w$。这样就能 $O(1)$ 做了。

然后接下来还有一个难点：我们知道了这些元素有多少个，以及这些元素具体会被放到哪些地方（不难发现这些地方肯定是两个区间，一个在左边，一个在右边，当然这两个区间也可能相连）。那么我们如何快速计算一个区间对答案的贡献？考虑推式子。

首先，一个区间的贡献是 $w\sum_{i=l}^{r}i(n-i+1)$（区间每个元素所被包含的区间个数，乘上 $w$ 的总和）。

考虑把 $(n+1)$ 提出来，然后就会变成 $(n+1)(\sum_{i=l}^ri-\sum_{i=l}^ri^2)$。前后两个部分可以分别用数学方法 $O(1)$ 求出（具体地，前面求和公式，后面和的平方的那个公式）。

这样就可以做到 $O(\log n)$ 处理一个询问了。

### $n\in [1,28]$

那么现在唯一的问题就是 $28$ 以内如何做了。这个东西可以设一个 dp 式子简单求出。

首先这个东西可以转化为方案数 dp。

考虑这个东西可以无序取，但是无序的状态比较难设，对于这种算方案数的 dp，一种常用方法是钦定有序。我们直接钦定这个东西是有序的，必须以 $1$ 到 $n$ 的顺序取，然后最后对于 $w$ 相同的算个排列数是同理的。

设 $f_{i,p_1,p_2,p_3,p_4,p_5,st}$ 表示目前考虑了前 $i$ 个，$w=1,w=2,w=3,w=4,w=5$ 分别取了 $p_1,p_2,p_3,p_4,p_5$ 个，和为 $st$ 的方案数。简单算一下状态数大概在八亿左右。需要进一步优化。

发现 $p_1+p_2+p_3+p_4+p_5=i$。我们直接把第一维省掉，状态数四千万左右，可以朴素转移。

具体地，每一个元素可以让其对应的 $w$ 加 $1$，然后对 $st$ 算上它的贡献，考虑这个思路转移就可以了。

然后因为我们这里钦定有序了，所以最后对相同的元素还要乘排列数。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,q;
const int mod=998244353;
int lowbit(int x){
	return log2(x&(-x))+1;
}
int qpow(int a,int p){
	int ans=1ll;
	while(p){
		if(p&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		p>>=1;
	}
	return ans;
}
namespace subtask1{
	int f[16][9][8][3][2][11005],cnt[6],now,inv[17];
	void solve(){
		inv[0]=1;
		for(int i=1;i<=16;i++)inv[i]=inv[i-1]*i;
		for(int i=1;i<=n;i++)cnt[lowbit(i)]++;
		f[0][0][0][0][0][0]=1;
		for(int p1=0;p1<=cnt[1];p1++)
			for(int p2=0;p2<=cnt[2];p2++)
				for(int p3=0;p3<=cnt[3];p3++)
					for(int p4=0;p4<=cnt[4];p4++)
						for(int p5=0;p5<=cnt[5];p5++)
							for(int st=0;st<=11000;st++){
								now=p1+p2+p3+p4+p5;
								if(!f[p1][p2][p3][p4][p5][st])continue;
								if(p1<cnt[1]&&st+1*(n-now)*(now+1)<=11000)
									(f[p1+1][p2][p3][p4][p5][st+1*(n-now)*(now+1)]+=f[p1][p2][p3][p4][p5][st])%=mod;
								if(p2<cnt[2]&&st+2*(n-now)*(now+1)<=11000)
									(f[p1][p2+1][p3][p4][p5][st+2*(n-now)*(now+1)]+=f[p1][p2][p3][p4][p5][st])%=mod;
								if(p3<cnt[3]&&st+3*(n-now)*(now+1)<=11000)
									(f[p1][p2][p3+1][p4][p5][st+3*(n-now)*(now+1)]+=f[p1][p2][p3][p4][p5][st])%=mod;
								if(p4<cnt[4]&&st+4*(n-now)*(now+1)<=11000)
									(f[p1][p2][p3][p4+1][p5][st+4*(n-now)*(now+1)]+=f[p1][p2][p3][p4][p5][st])%=mod;
								if(p5<cnt[5]&&st+5*(n-now)*(now+1)<=11000)
									(f[p1][p2][p3][p4][p5+1][st+5*(n-now)*(now+1)]+=f[p1][p2][p3][p4][p5][st])%=mod;
							}
		int res=0;
		for(int st=0;st<=11000;st++){
			res+=f[cnt[1]][cnt[2]][cnt[3]][cnt[4]][cnt[5]][st]*inv[cnt[1]]*inv[cnt[2]]*inv[cnt[3]]*inv[cnt[4]]*inv[cnt[5]];
			if(res>=k){printf("%lld\n",st);break;}
		}
		for(int p1=0;p1<=cnt[1];p1++)
			for(int p2=0;p2<=cnt[2];p2++)
				for(int p3=0;p3<=cnt[3];p3++)
					for(int p4=0;p4<=cnt[4];p4++)
						for(int p5=0;p5<=cnt[5];p5++)
							for(int st=0;st<=11000;st++)
								f[p1][p2][p3][p4][p5][st]=0;
		for(int i=1;i<=5;i++)cnt[i]=0;
	} 
}
namespace subtask2{
	int ans;
	int get(int l,int r){
		if(l>r)return 0;
		l%=mod,r%=mod;
		return 
		((((n+1)%mod*(l+r)%mod*(r-l+mod+1)%mod*qpow(2,mod-2)%mod)-
		(r*(r+1)%mod*(2*r+1)%mod*qpow(6,mod-2)%mod)+mod)%mod+
		(l*(l-1)%mod*(2*l-1+mod)%mod*qpow(6,mod-2)%mod))%mod;
	}
	void solve(){
		ans=0;
		int t=log2(n)+1;
		int ql=0,qr=n+1,lst=1;
		for(int i=t;i>=1;i--){
			int sum=n/(1ll<<i)+((n-((n/(1ll<<i))*(1ll<<i)))>=(1ll<<(i-1)));
			int nl=ql+((sum+lst)/2);
			int nr=qr-(sum-(sum+lst)/2);
			lst^=(sum&1);
			(ans+=i*((get(ql+1,nl)+get(nr,qr-1))%mod)%mod)%=mod;
			ql=nl,qr=nr;
		}
		printf("%lld\n",ans);
	}
}
signed main(){
	scanf("%lld",&q);
	while(q--){
		scanf("%lld%lld",&n,&k);
		if(n>28)subtask2::solve();
		else subtask1::solve();
	}
	return 0;
}
```


---

