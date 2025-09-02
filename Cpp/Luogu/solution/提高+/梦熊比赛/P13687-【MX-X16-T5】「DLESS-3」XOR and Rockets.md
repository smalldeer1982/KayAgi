# 【MX-X16-T5】「DLESS-3」XOR and Rockets

## 题目背景

[火箭][头盔][毛毛虫][奶龙][滑板].jpg

## 题目描述

小 H 有两个长度为 $n$ 的非负整数序列 $a_1, \ldots, a_n$ 与 $b_1, \ldots, b_n$。

他可以进行若干次操作：
- 选择一个整数 $x\in[1,n]$ 与一个正整数 $y$。
- 进行操作 $\forall i\in[1,x],a_i\gets a_i\oplus y$。即将 $[1,x]$ 中数异或上 $y$。
- 这次操作的代价为 $b_x$。

小 H 想通过若干次操作使得 $a$ 变为不下降序列，你需要帮他最小化代价的和。

## 说明/提示

**【样例解释】**

对于第一组数据，$a$ 本来就是不下降序列，不需要操作，故答案为 $0$。

对于第二组数据，选择 $x=2,y=1$ 操作，代价为 $b_2=2$。操作后 $a=[0,2,2,4]$，符合条件，故答案为 $2$。

对于第三组数据，操作两次：
- 选择 $x=4,y=28$，代价为 $b_4=1$，操作后序列变为 $a=[20,21,24,30,5]$。
- 选择 $x=5,y=16$，代价为 $b_5=2$，操作后序列变为 $a=[4,5,8,14,21
]$。

故答案为 $1+2=3$。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\le T,n,\sum n\le 5000$，$0\le a_i<2^{13}$，$1\le b_i\le 10^9$。

各子任务特殊限制如下：

| 子任务编号 | $\sum n\le$ | $a_i<$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5000$ | $16$ | A | $5$ |
| $2$ | $50$ | $64$ | B | $15$ |
| $3$ | $50$ | $64$ | 无 | $15$ |
| $4$ | $500$ | $2^9$ | 无 | $10$ |
| $5$ | $500$ | $2^{13}$ | 无 | $20$ |
| $6$ | $5000$ | $2^9$ | 无 | $10$ |
| $7$ | $5000$ | $2^{13}$ | 无 | $25$ |

- 特殊性质 A：保证 $n\le 3$。
- 特殊性质 B：保证存在一种最优解，使得操作后的 $a$ 有 $a_n<64$。

## 样例 #1

### 输入

```
5
3
1 2 3
1 1 1
4
1 3 2 4
1 2 3 4
5
8 9 4 2 5
1 2 2 1 2
8
1 8 7 4 2 5 3 6
1 4 2 3 5 4 2 3
10
128 983 238 123 823 723 91 324 12 747
13 23 12 52 23 12 42 82 21 34```

### 输出

```
0
2
3
11
111```

# 题解

## 作者：luogu_gza (赞：5)

记 $x$ 的从低到高的第 $b$ 位为 $F(x,b)$。

我们分两种情况讨论，最后一个数操作和不操作。

### 不操作

不操作的话整个序列的值域不超过 $8192$，设 $f_{i,j}$ 表示当前处理到了 $i$ 这个位置，$a_i$ 异或后的值是 $j$，直接 dp 是 $O(nV^2)$ 的，简单优化可以做到 $O(nV)$。

### 操作

我们称区间 $[l,r]$ 是好的当且仅当存在 $x$ 满足 $a_l\oplus x\leq \cdots \leq a_r\oplus x$，然后记最小的合法的 $x$ 为 $f(l,r)$。

我们用操作点将整个序列分为若干部分，显然这些部分都需要的好的，记他们分别是 $[l_i,r_i](1 \leq i \leq m)$。

我们记 $g_i=f(l_i,r_i) \oplus 2^{1000i}$。将第 $i$ 个部分异或上 $g_i$，即可满足条件。这样我们就不必考虑相邻部分交界点是否递增，而只需要保证内部递增就行了。

也就是说，经过这样的转化后，每个部分都独立了。

于是问题就转移到了，如何在可接受的时间复杂度内求出每一个区间 $[l,r]$ 是否是好的，将 $a_l \sim a_r$ 提取出来变成一个序列 $c$。

对于一个区间内的相邻点 $i,i+1$，我们限制了 $c_i\oplus x\leq c_{i+1}\oplus x$。也就是说，假设 $c_i$ 和 $c_{i+1}$ 在第 $b$ 位第一次出现了分歧（不同），那么这一位异或后的结果一定是 $c_i$ 是 $0$，$c_{i+1}$ 是 $1$。

也就是说，如果 $F(c_i,b)=1$，$F(c_{i+1},b)=0$，那么 $F(x,b)=1$，如果 $F(c_i,b)=0$，$F(c_{i+1},b)=1$，那么 $F(x,b)=0$，显然这些限制不难记录在一个数组里面，只需要看所有的限制有没有冲突就行了。

核心代码：

```cpp
const int N=5010,V=8192,inf=1e17;
int n;
int a[N],b[N];
int f[N];
bool can[N][N];
signed nd[N][N];
int dp[N][V],pre[V],suf[V];
void solve()
{
  n=R;
  fo(i,1,n) a[i]=R;
  fo(i,1,n) b[i]=R;
  fo(i,1,n) fo(j,1,n) can[i][j]=0,nd[i][j]=0;
  fo(i,1,n) f[i]=inf;
  f[0]=0;
  fo(i,1,n)
  {
    can[i][i]=1,nd[i][i]=0;
    int nd0[13]={0},nd1[13]={0};
    m1(nd0,0),m1(nd1,0);
    fo(j,i+1,n)
    {
      if(a[j]>a[j-1])
      {
        rep(k,12,0) if((a[j]>>k&1)!=(a[j-1]>>k&1)){nd0[k]=1;break;}
      }
      if(a[j]<a[j-1])
      {
        rep(k,12,0) if((a[j]>>k&1)!=(a[j-1]>>k&1)){nd1[k]=1;break;}
      }
      bool flag=1;
      fo(k,0,12) flag&=(nd0[k]==0||nd1[k]==0);
      if(!flag) break;
      can[i][j]=1;
      fo(k,0,12) if(nd1[k]) nd[i][j]+=(1<<k);
      // cout<<i<<' '<<j<<' '<<nd[i][j]<<endl;
    }
  }
  fo(i,1,n) fo(j,0,i-1) if(can[j+1][i])
  {
    f[i]=min(f[i],f[j]+b[i]);
  }
  int ans1=f[n];
  fo(i,1,n) fo(j,0,V-1) dp[i][j]=1e17;
  fo(j,0,V-1) dp[n][j^a[n]]=(j!=0)*b[n];
  // cout<<dp[n][0]<<endl;
  rep(i,n,1)
  {
    if(i!=n)
    {
      fo(j,0,V-1)
      {
        int val=(a[i]^j^a[i+1]);
        fo(k,val,val) if(j<=k) dp[i][j]=min(dp[i][j],dp[i+1][k]);
        dp[i][j]=min(dp[i][j],suf[j]+b[i]);
      }
    }
    pre[0]=dp[i][0];
    fo(j,1,V-1) pre[j]=min(pre[j-1],dp[i][j]);
    suf[V-1]=dp[i][V-1];
    rep(j,V-2,0) suf[j]=min(suf[j+1],dp[i][j]);
  }
  int ans=1e17;
  fo(i,0,V-1) ans=min(ans,dp[1][i]);
  write(min(ans1,ans)),puts("");
}
void main(){
  MT solve();
}
```

---

## 作者：P2441M (赞：2)

## 题意

给定两个长度为 $n$ 的序列 $a,b$，你可以进行若干次操作：

- 选择一个整数 $x\in[1,n]$ 和正整数 $y$，然后 $\forall i\in [1,x],a_i\leftarrow a_i\oplus y$。这次操作会产生 $b_x$ 的代价。

需要在若干次操作后使 $a$ 不降，最小化代价总和。多测，$1\leq T,n,\sum{n}\leq 5\times 10^3$，$0\leq a_i<2^{13}$。

## 题解

这么牛。

显然我们最多只会做 $n$ 次操作，因为 $x$ 相同的操作可以合并。设我们在 $x=i$ 处选择的 $y$ 为 $y_i$，若没在 $x=i$ 处操作则记 $y_i$ 为 $0$。再设 $c$ 为最终操作后的序列，那么容易得到

$$
c_i=a_i\oplus\bigoplus_{j=i}^ny_j\Leftrightarrow \bigoplus_{j=i}^ny_j=a_i\oplus c_i
$$

差分一下得到

$$
y_{i-1}=(a_{i-1}\oplus c_{i-1})\oplus(a_i\oplus c_i)
$$

于是最小操作代价就是

$$
\sum_{i=1}^{n-1}[y_i\neq 0]b_i=\sum_{i=2}^n[(a_{i-1}\oplus c_{i-1})\neq(a_i\oplus c_i)]b_{i-1}
$$

我们发现这样子考虑不到 $y_n$，由此启发我们分类讨论是否在 $x=n$ 处进行操作。

### 不在 $x=n$ 处操作

此时 $c_i\leq a_n(1\leq i<n)$，有值域的限制，我们直接 DP。令 $f_{i,j}$ 表示确定了 $c[1,i]$，其中 $c_i=j$，**在 $1\leq x<i$ 位置的最小操作代价和**（也就是说，我们在这里不加入 $b_i$，因为这个值会受到 $c_{i+1}$ 的影响）。枚举 $c_{i-1}=k$，可以得到转移：

$$
f_{i,j}=\min_{k=1}^j\left\{f_{i-1,k}+[a_{i-1}\oplus k\neq a_i\oplus j]b_{i-1}\right\}
$$

这部分答案即为 $f_{n,a_n}$。

令 $V=a_n$，暴力做是 $\mathcal{O}(nV^2)$ 的。不难注意到 $[a_{i-1}\oplus k\neq a_i\oplus j]b_{i-1}$ 仅在 $k=a_{i-1}\oplus a_i\oplus j$ 时值为 $0$，于是我们先从 $f_{i-1}$ 的前缀 $\min$ 加上 $b_{i-1}$ 转移过来，然后若 $a_{i-1}\oplus a_i\oplus j\leq j$ 就令 $f_{i,j}\leftarrow \min(f_{i,j},f_{i-1,a_{i-1}\oplus a_i\oplus j})$ 即可。

这样我们就 $\mathcal{O}(nV)$ 地解决了这部分。

### 在 $x=n$ 处操作

我们发现此时没了值域的限制，我们可以通过操作一些高位来消除低位的限制。更具体地，我们考察一种对于 $a$ 的划段方式，使得对于每个段 $a[l,r]$ 都存在一个数 $x$，使得 $a_l\oplus x\leq a_{l+1}\oplus x\leq\cdots\leq a_r\oplus x$。而此时我们无需保证段之间的单调性，因为对于第 $i$ 个段，我们可以令 $x\leftarrow x\oplus 2^{100i}$，强制让段之间满足单调性。

还是考虑 DP。令 $g_i$ 表示对 $a[1,i]$ 进行划段的最小代价和，转移显然：

$$
g_i=b_i+\min_{\substack{1\leq j\leq i\\valid(j,i)}}g_{j-1}
$$

其中 $valid(j,i)$ 表示是否存在 $x$ 使得 $a[j,i]$ 全体异或上 $x$ 后单调不减。

那么考察如何快速判定 $a[j,i]$ 是否合法。这里参考官方题解，设 $x_i$ 表示 $x$ 的二进制表示下从低位起的第 $i$ 位，我们指出一个性质：若 $a\neq b$，设 $k$ 为最高的位使得 $a_k\neq b_k$，则 $a\oplus x\leq b\oplus x\Leftrightarrow a_k=x_k$。

:::info[证明]
对于高于 $k$ 位的部分，显然 $a,b$ 异或上 $x$ 后保持相同；而对于第 $k$ 位，显然此时 $(a\oplus x)_k\neq (b\oplus x)_k$，因此我们需要有 $(a\oplus x)_k=0,(b\oplus x)_k=1$，也即 $a_k=x_k$。$\Box$
:::

由此考虑倒序枚举 $j$，向当前 $a_i$ 所在段中加入 $a_j$ 的过程，此时设 $a_j,a_{j+1}$ 最高的不同位为 $k$，于是我们得到了一条 $x_k=a_k$ 的限制。于是我们只需存储所有的限制，每次添加一条新限制时，判断其是否与前面的限制冲突即可。

$\mathcal{O}(n\log\max{a_i})$ 预处理 $a_i,a_{i+1}$ 最高的不同位，那么 DP 部分的总体复杂度就是 $\mathcal{O}(n^2)$ 的。

---

综合两部分的做法即可通过本题，时间复杂度为 $\mathcal{O}(n^2+nV)$。

## 代码

```cpp
// Problem: T620320 【MX-X16-T5】「DLESS-3」XOR and Rockets
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T620320?contestId=265699

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define lowbit(x) ((x) & -(x))
#define chk_min(x, v) (x) = min((x), (v))
#define chk_max(x, v) (x) = max((x), (v))
typedef long long ll;
typedef pair<int, int> pii;
const int N = 5e3 + 5, V = 1 << 13, B = 13 + 5;
const ll INF = 1e18;

int T, n, v, a[N], b[N], bit[N], val[B];
ll f[2][V + 5], mn[2][V + 5], g[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> T;
    while (T--) {
    	cin >> n;
    	for (int i = 1; i <= n; ++i) cin >> a[i];
    	for (int i = 1; i <= n; ++i) cin >> b[i];
    	v = a[n];
    	int p = 1;
    	fill(f[p], f[p] + v + 1, 0), fill(mn[p], mn[p] + v + 1, 0);
    	for (int i = 2; i <= n; ++i) {
    		p ^= 1;
    		for (int j = 0; j <= v; ++j) {
    			f[p][j] = mn[p ^ 1][j] + b[i - 1];
    			if ((a[i] ^ a[i - 1] ^ j) <= j) chk_min(f[p][j], f[p ^ 1][a[i] ^ a[i - 1] ^ j]);
    			mn[p][j] = f[p][j];
	    	}
	    	for (int j = 1; j <= v; ++j) chk_min(mn[p][j], mn[p][j - 1]);
	    }
    	for (int i = 1; i < n; ++i) {
    		int p = 12;
    		for (; ~p && (a[i] >> p & 1) == (a[i + 1] >> p & 1); --p);
    		bit[i] = p;
    	}
    	for (int i = 1; i <= n; ++i) {
    		g[i] = g[i - 1];
    		fill(val, val + 13, -1);
    		for (int j = i - 1; j; --j) {
    			if (bit[j] == -1) { chk_min(g[i], g[j - 1]); continue; }
    			bool b = a[j] >> bit[j] & 1;
    			if (val[bit[j]] == !b) break;
    			chk_min(g[i], g[j - 1]), val[bit[j]] = b;
    		}
    		g[i] += b[i];
    	}
    	cout << min(f[p][a[n]], g[n]) << '\n';
    }
    return 0;
}
```

---

## 作者：喵仔牛奶 (赞：2)

## Solution

设最优解的数列为 $a'$。考虑 $a_n$ 是否被操作。

---

如果 $a_n$ 没有被操作，说明 $a'_i\le a_n$。设 $f_{i,j}$ 为前 $i$ 个数进行操作后 $a'_i=j$ 的最少操作次数，转移：
$$f_{i,j}=\min_{k\le j}\{f_{i-1,k}+b_i\cdot[a_i\oplus j\neq a_{i-1}\oplus k]\}$$

使用观察到对于 $f_{i,j}$，只有 $f_{i-1,a_i\oplus a_{i-1}\oplus j}$ 满足后面那项为 $0$。因此使用前缀 min 优化即可做到 $\mathcal O(na)$。

---

如果 $a_n$ 被操作，那么序列可以被划分为若干连续段，每个连续段内部的数异或上的数相同。由于每个数都被异或，我们不需要在意不同连续段之间的大小关系，因为把第 $i$ 个连续段全体异或上 $2^{100i}$ 即可满足条件。

定义序列 $a$ 合法当且仅当存在一个数 $x$ 使得将所有 $a_i$ 异或上 $x$ 后 $a$ 变成不降序列。设 $g_{i}$ 为将 $[1,i]$ 划分为若干合法序列的最小代价。DP 转移容易，问题在如何快速判断一个序列是否合法。

令 $x_i$ 表示 $x$ 二进制下从低到高第 $i$ 位。

引理：对于 $a\neq b$，设 $k$ 为最高的使得 $a_k\neq b_k$ 的位，$a\oplus x\le b\oplus x$ 的充要条件 $x_k=a_k$。

证明：
- 考虑 $a\oplus x$ 和 $b\oplus x$ 最高的不同为也是 $k$。
- 而 $(a\oplus x)_k\neq(b\oplus x)_k$。因此需要 $(a\oplus x)_k=0$，也就是 $x_k=a_k$。

DP 时每次在序列开头加入一个数，然后需要判断序列是否合法。每次在开头加入数后，$(a_1,a_2)$ 就限制了可以异或的数 $x$ 的某一位。如果限制冲突则不合法，否则显然可以构造出一个合法的 $x$。

这部分复杂度 $\mathcal O(n^2)$。

总复杂度 $\mathcal O(n^2+na)$，可以通过此题。

---

![](https://cdn.luogu.com.cn/upload/image_hosting/383sfqm7.png?x-oss-process=image/resize,m_lfit,h_255,w_337)

---

## 作者：godmoo (赞：1)

[Link](https://www.luogu.com.cn/problem/P13687) & [Cnblogs](https://www.cnblogs.com/godmoo/p/19005878).

妙妙题。

前缀异或很丑，考虑放在 $a$ 的差分上刻画，操作 $(x, y)$ 转换成 $\Delta a_1 \gets \Delta a_1 \oplus y$ 和 $\Delta a_{x + 1} \gets \Delta a_{x + 1} \oplus y$。

这里有个小技巧：我们先将 $a$ 翻转，此时修改变为后缀，再做差分，操作 $(x, y)$ 等价于 $\Delta a_{n - x + 1} \gets \Delta a_{n - x + 1} \oplus y$。

翻转后问题变为求单调不增的 $a$，即其差分的前缀异或积单调不增，容易想到一种 dp：记 $f_{i, j}$ 为考虑到 $\Delta a_i$，前缀异或积为 $j$ 的方案，考虑当前这个位置是否进行修改。

若不修改，枚举 $k \lt 2^{13}$，若有 $k\oplus a_i \le a_i$，则可以从 $f_{i - 1, k}$ 转移而来；若修改，则可以由所有 $k \ge j$ 的 $f_{i - 1, k}$ 转移而来。随便维护可以 $\mathcal O(nV)$。

但这个 dp 是错误的。修改的 $y$ 没有限定范围，实际上修改后的值域不一定为 $[0, 2^{13})$！但发现当 $a_1$ 不进行修改时，由于序列单调不增，所以这么做是对的。接下来钦定 $a_1$ 进行了修改。

考虑整个东西的形态，对于一个进行操作的位置 $i$，记下一个进行操作的位置为 $j$，考虑前面所有修改的影响，若总的对 $a_i$ 的贡献是 $a_i \gets a_i \oplus s$，那么 $[i, j)$ 整一段的数都异或了 $s$，称整个段**局部合法**当且仅当所有 $a_p\oplus s$ 单调不增，其中 $i\le p\lt j$。

最厉害的一步：假设我们已经构造出了一种方案使每个段都局部合法，实际上我们仅需 $0$ 的代价就可以使全局合法！记从右往左第 $i$ 段的第一个数上进行的操作的 $y$ 为 $y_i$，那么仅需让 $y_i \gets y_i\oplus 2^{100i}$ 即可，这不改变局部合法性，且在不同的两段之间，极大的位数差距使得低位的内容已经不重要了。

所以可以直接忽略这部分，仅需再用一个类似的 dp 求满足局部合法性的答案，记为 $g_{i, j}$，和 $f$ 的部分去以下 $\min$ 即为最终答案。仍是 $\mathcal O(nV)$ 的。


```cpp
// godmoo's code
#define ckmn(a, b) (a = min(a, b))
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 5005;
const int V = 1 << 13;
int n, a[N], b[N]; ll f[2][1 << 13], g[2][1 << 13], ans;
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i]; reverse(a + 1, a + n + 1);
    for(int i = 1; i <= n; i++) cin >> b[i]; reverse(b + 1, b + n + 1);
    for(int i = n; i; i--) a[i] ^= a[i - 1];

    mem(f, 0x3f), mem(g, 0x3f);

    fill(f[1], f[1] + V, b[1]), f[1][a[1]] = 0;
    for(int i = 2; i <= n; i++){
        mem(f[i & 1], 0x3f);
        for(ll j = V - 1, mn = 1e18; ~j; j--){
            if((a[i] ^ j) <= j) ckmn(f[i & 1][a[i] ^ j], f[~i & 1][j]);
            ckmn(f[i & 1][j], ckmn(mn, f[~i & 1][j]) + b[i]);
        }
    }
    ans = *min_element(f[n & 1], f[n & 1] + V);

    fill(g[1], g[1] + V, b[1]);
    for(int i = 2; i <= n; i++){
        mem(g[i & 1], 0x3f);
        ll mn = *min_element(g[~i & 1], g[~i & 1] + V);
        for(int j = 0; j < V; j++){
            g[i & 1][j] = mn + b[i];
            if((a[i] ^ j) <= j) ckmn(g[i & 1][a[i] ^ j], g[~i & 1][j]);
        }
    }
    ckmn(ans, *min_element(g[n & 1], g[n & 1] + V));

    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int Cas; for(cin >> Cas; Cas; Cas--) solve();
    cout << flush;
    return 0;
}
```

---

## 作者：Pigsyy (赞：1)

## 前言

:::epigraph[]
只有我赛时写的 Trie 树优化转移，然后卡了一年的常吗？
:::

状态定义的方式不同，转移优化的难度和时间复杂度是不同的。这个还是第一次见，感觉挺深刻的。

:::info[题目描述]
给定两个长度为 $n$ 的非负整数序列 $a,b$。接下来进行若干次操作：
- 选择一个整数 $x\in[1,n]$ 与一个正整数 $y$。
- 进行操作 $\forall i\in[1,x],a_i\gets a_i\oplus y$。即将 $[1,x]$ 中数异或上 $y$。
- 这次操作的代价为 $b_x$。

输出通过若干次操作使得 $a$ 变为单调不降的最小代价。
:::

## 思路

不难想到用 DP 求解。由于每次是将前缀异或，所以倒着做会比较方便（应该正着做也行，没细想）。

需要观察到答案分为两种情况：

1. $a_n$ 不操作：任何时刻，后缀操作的异或和不会超过 $V$。
2. $a_n$ 操作：最优异或 $2^{10000}+x$，其中 $x$ 为任意不超过 $V$ 的非负整数。一旦某个位置要操作，只需要将 $2$ 的指数次幂减少 $1$，并随意改动 $x$。

### 情况 1（$a_n$ 不操作）

令 $f_{i,j}$ 表示 $i\sim n$ 位置中，所有位置的操作的异或和为 $j$。这时候，如果 $i$ 位置操作为异或 $k$，则需满足 $a_i\oplus k\oplus j\le a_{i+1}\oplus j$。所有合法的 $k$ 是 Trie 树上 $\log V$ 个子树。这样，复杂度即可做到 $O(nV\log V)$。

不过，这样太不好了。我们将限制放在转移中，但实际上可以将限制放在状态里。即，令 $f_{i,j}$ 表示 $i\sim n$ 位置中，$a_i$ 最终的值为 $j$。如果操作，则 $a_{i}$ 可以变成任何值。这样，转移只需要做后缀 $\max$ 即可（也就是转化成了一段区间）。

时间复杂度：$O(nV)$。

### 情况 2（$a_n$ 操作）

根据上述分析，只要操作，异或值可以变成任何值。于是，令 $f_{i,j}$ 表示 $i\sim n$ 位置，所有操作的异或和为 $j$。转移是容易做到 $O(1)$ 的。

时间复杂度：$O(nV)$。

## 代码

:::success[赛时代码 $O(nV\log V)$]
```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int n;
int a[1 << 13], b[1 << 13];
i64 dp[2][1 << 13], fg[13][1 << 13];

inline void chmin(i64 &a, i64 b) { a = min(a, b); }
void solve() {
	cin >> n;
	for (int i = 1; i <= n; i ++)
		cin >> a[i];
	for (int i = 1; i <= n; i ++)
		cin >> b[i];

	memset(dp, 0x3f, sizeof dp);
	dp[n & 1][0] = 0;
	for (int i = n - 1; i >= 1; i --) {
		memset(dp[i & 1], 0x3f, sizeof dp[i & 1]);
		memset(fg, 0x3f, sizeof fg);
		for (int j = 0; j < 1 << 13; j ++) {
			if (dp[~i & 1][j] >= 1E18) continue;
			int x = a[i] ^ j, y = a[i + 1] ^ j;
			int S = j;
			for (int k = 12; k >= 0; k --)
				if (y >> k & 1) {
					chmin(fg[k][(S ^ ((x >> k & 1) << k)) >> k], dp[~i & 1][j]);
					S ^= (~x >> k & 1) << k;
				} else if (x >> k & 1) S ^= 1 << k;
			fg[0][S] = min(fg[0][S], dp[~i & 1][j]);
			if (x <= y)
				dp[i & 1][j] = min(dp[i & 1][j], dp[~i & 1][j]);
		}
		for (int k = 12; k >= 0; k --)
			for (int x = 0; x < 1 << 13 - k; x ++)
				if (fg[k][x] < 1E18)
					for (int y = 0; y < 1 << k; y ++)
						dp[i & 1][x << k | y] = min(dp[i & 1][x << k | y], fg[k][x] + b[i]);
	}
	i64 res = 1ll << 60;
	for (int i = 0; i < 1 << 13; i ++)
		res = min(res, dp[1][i]);

	for (int i = 0; i < 1 << 13; i ++)
		dp[n & 1][i] = b[n];
	for (int i = n - 1; i >= 1; i --) {
		i64 mn = 1ll << 60;
		for (int j = 0; j < 1 << 13; j ++)
			mn = min(mn, dp[~i & 1][j]);
		for (int j = 0; j < 1 << 13; j ++) {
			dp[i & 1][j] = mn + b[i];
			if ((a[i] ^ j) <= (a[i + 1] ^ j))
				dp[i & 1][j] = min(dp[i & 1][j], dp[~i & 1][j]);
		}
	}
	for (int i = 0; i < 1 << 13; i ++)
		res = min(res, dp[1][i]);

	cout << res << '\n';
}

int main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);

	int T;
	cin >> T;

	while (T -- ) solve();

	return 0;
}
```
:::

:::success[$O(nV)$ 代码]{open}
```cpp
void solve() {
	cin >> n;
	int mx = 0;
	for (int i = 1; i <= n; i ++)
		cin >> a[i], mx = max(mx, a[i]);
	for (int i = 1; i <= n; i ++)
		cin >> b[i];
	mx = (1 << __lg(mx) + 1);

	memset(dp, 0x3f, sizeof dp);
	dp[n & 1][a[n]] = 0;
	for (int i = n - 1; i >= 1; i --) {
		memset(dp[i & 1], 0x3f, sizeof dp[i & 1]);
		i64 mn = 1ll << 60;
		for (int j = mx - 1; j >= 0; j --) {
			int k = a[i] ^ j ^ a[i + 1];
			if (k <= j) dp[i & 1][k] = min(dp[i & 1][k], dp[~i & 1][j]);
			mn = min(mn, dp[~i & 1][j]);
			dp[i & 1][j] = min(dp[i & 1][j], mn + b[i]);
		}
	}
	i64 res = 1ll << 60;
	for (int i = 0; i < mx; i ++)
		res = min(res, dp[1][i]);

	for (int i = 0; i < mx; i ++)
		dp[n & 1][i] = b[n];
	for (int i = n - 1; i >= 1; i --) {
		i64 mn = 1ll << 60;
		for (int j = 0; j < mx; j ++)
			mn = min(mn, dp[~i & 1][j]);
		for (int j = 0; j < mx; j ++) {
			dp[i & 1][j] = mn + b[i];
			if ((a[i] ^ j) <= (a[i + 1] ^ j))
				dp[i & 1][j] = min(dp[i & 1][j], dp[~i & 1][j]);
		}
	}
	for (int i = 0; i < mx; i ++)
		res = min(res, dp[1][i]);

	cout << res << '\n';
}
```
:::

---

## 作者：Null_h (赞：1)

## 前言

又是看数据范围知复杂度的一集。

## 思路

首先看眼数据范围猜是 $O(n2^k)$ 的算法，这里 $k=13$，可能是状压什么的，此为看到题的第一感觉。

看到前缀异或，那么肯定考虑差分之后变成单点修改怎么做（此处的差分都是定义在异或意义上的），然后前缀的话每次改两个点不好维护，那么把序列倒过来，就是要后缀异或使其单调不增（此后出现的数组都默认是倒转后的）。

考虑一个自然的 dp，在异或的差分数组往后扫，记 $f_{i,j}$ 为扫到第 $i$ 个时，值为 $j$ 的最小花费，那么显然会有两种转移：

如果不修改，那么枚举上一次的状态 $x$，如果 $a_i\oplus x \le x$，即加入这个能使得序列不增，那么直接更新。

如果修改，那么枚举当前 $i$ 的最终值，那么大于等于它的都可以转移，再加上修改的花销 $b_i$。

然后写写写，交一发，35 pts。

当 $a_i$ 较大的时候无法通过，为什么呢？

$a_i$ 的最终取值真的一定 $\le 2^{13}$ 吗？

由于单调不增，实际上只要考虑 $a_1$ ，如果进行了修改，那么对于高于 $2^{13}$ 的位，实际上可以任意取值，那么对于后面的有什么影响呢？考虑上面转移的第二种情况，对于高于 $2^{13}$ 的位，显然可以随便构造一下让它小一点，也就是说，对于低位来说就没有限制了。

即，钦定第一个必须修改，同时此后修改的转移是没有大小限制的，再 dp 一遍两者取较小值。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e16;
const int N=1ll<<13,M=5010;
int f[2][N],g[2][N],n,a[M],b[M];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[n-i+1];
		}
		a[0]=0;
		for(int i=n;i>=1;i--){
			a[i]=a[i]^a[i-1];
		}
		for(int i=1;i<=n;i++){
			cin>>b[n-i+1];
		}
		int mx=N;
		for(int x=0;x<mx;x++){
			f[1][x]=b[1];
			g[1][x]=0;
		}
		f[1][a[1]]=0;
		int ans=0;
		for(int i=2;i<=n;i++){
			for(int x=0;x<mx;x++){
				f[i&1][x]=INF;
				g[i&1][x]=INF;	
			}
			for(int x=0;x<mx;x++){
				if((x^a[i])<=x){
					f[i&1][x^a[i]]=min(f[i&1][x^a[i]],f[(i&1)^1][x]);
					g[i&1][x^a[i]]=min(g[i&1][x^a[i]],g[(i&1)^1][x]);
				}
			}
			int mn;
			mn=ans=INF;
			int mnn=INF;
			for(int x=mx-1;x>=0;x--){
				mn=min(f[(i&1)^1][x],mn);
				mnn=min(g[(i&1)^1][x],mnn);
				f[i&1][x]=min(f[i&1][x],mn+b[i]);
				ans=min(f[i&1][x],ans);
			}
			for(int x=0;x<mx;x++){
				g[i&1][x]=min(g[i&1][x],mnn+b[i]);
				ans=min(g[i&1][x]+b[1],ans);
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

如果我们最终序列总是小于 $2^{13}$，我们设 $dp_{i,j}$ 表示第 $i$ 个数变成了 $j$，并且 $i$ 到 $n$ 单调不降的最小代价。

然后随便优化转移就是 $O(nV)$。

然而事与愿违，我们在获得 $35$ 分成功发现序列可能大于 $2^{13}$，具体的，我们操作最后一个数，在 $2^{114514}$ 位添加 $1$，然后操作倒数第二个数干掉前缀，这样就只有最后一个数有这一位，自然最大，并且可以对前面没啥影响。

我们考虑如果操作，怎么最优。我们每个修改的数都连带着一段需要保证只考虑 $2^{13}$ 以内的位是单调不降，因为更高位肯定相同。

考虑向前时又要操作一个数，这时候这个数发现可以不必须影响 $2^{13}$ 情况下干掉上一个的最高位，然后新添加一个低一些的最高位，追求这一段一定都比后面那段小。

于是我们设 $dp_i$ 表示 $i$ 开始的后缀的答案，容易发现上面这些发生必须有最后一个数操作。

转移就是寻找 $i$ 之后第一个修改的位置 $j$，然后需要保证 $i$ 到 $j$ 仅考虑 $2^{13}$ 内位置足以通过都异或一个数来单调不降。

然后就可以由 $dp_{j+1}$ 转移了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[5009];
int b[5009];
int dp[10009];
int mi[10009];
int d[10009];
void _main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int v;
	v=(1ll<<13);
	for(int i=0;i<v;i++){
		dp[i]=0;
	}
	for(int i=n;i>=1;i--){
		for(int i=0;i<v;i++){
			d[i]=1e18,mi[i]=1e18;
		}
		for(int j=0;j<v;j++){
			int z;
			if(i==n){
				z=a[i];
			}else
			z=a[i]^j^a[i+1];
			if(z<=j){
				d[z]=min(dp[j],d[z]);
			}
			mi[j]=min(mi[j],dp[j]);
		}
		for(int i=v-2;i>=0;i--){
			mi[i]=min(mi[i],mi[i+1]);
		}
		for(int j=0;j<v;j++){
			dp[j]=min(d[j],mi[j]+b[i]);
		}
	}
	int ans;
	ans=1e18;
	for(int i=0;i<v;i++){
		ans=min(ans,dp[i]);
	}
	dp[n+1]=0;
	for(int i=n;i>=1;i--){
		dp[i]=dp[i+1]+b[i];
		int q,x;
		q=x=0;
		for(int j=i+1;j<=n;j++){
			int z;
			z=(a[j]^a[j-1]);
			z=(1ll<<__lg(z));
			if(q&z){
				if((a[j]&z)^(x&z)){
					break;
				}
			}else{
				q|=z;
				x|=(a[j]&z);
			}
			dp[i]=min(dp[i],dp[j+1]+b[j]);
		}
	}
	ans=min(ans,dp[1]);
	cout<<ans<<endl;
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		_main();
	}
	return 0;
}
```

---

