# [AGC056B] Range Argmax

## 题目描述

给定一个整数 $N$ 和 $M$ 个整数对。第 $i$ 个整数对为 $(L_i, R_i)$。

请你求出，按照以下步骤可以生成的整数序列 $x=(x_1, x_2, \cdots, x_M)$ 的种数，答案对 $998244353$ 取模。

- 准备一个 $1$ 到 $N$ 的排列 $p=(p_1, p_2, \cdots, p_N)$。
- 对于每个 $i$（$1 \leq i \leq M$），令 $x_i$ 为 $p_{L_i}, p_{L_i+1}, \cdots, p_{R_i}$ 中最大值的下标。即，$\max(p_{L_i}, p_{L_i+1}, \cdots, p_{R_i}) = p_{x_i}$。

## 说明/提示

### 限制条件

- $2 \leq N \leq 300$
- $1 \leq M \leq \dfrac{N(N-1)}{2}$
- $1 \leq L_i < R_i \leq N$
- $(L_i, R_i) \neq (L_j, R_j)$（$i \neq j$）
- 所有输入的值均为整数

### 样例解释 1

例如，当 $p=(2,1,3)$ 时，$x=(1,3)$。满足条件的数列有 $x=(1,1),(1,3),(2,2),(2,3)$ 共 $4$ 种。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
1 2
1 3```

### 输出

```
4```

## 样例 #2

### 输入

```
6 3
1 2
3 4
5 6```

### 输出

```
8```

## 样例 #3

### 输入

```
10 10
8 10
5 8
5 7
2 5
1 7
4 5
5 9
2 8
7 8
3 9```

### 输出

```
1060```

# 题解

## 作者：joke3579 (赞：8)

## $\text{statement}$

给定整数 $n$ 以及 $m$ 对整数。第 $i$ 对整数为 $(l_i, r_i)$ 。

请输出可以通过如下方式生成的整数序列 $x = (x_1, x_2,\cdots,x_m)$ 的个数。答案对 $998244353$ 取模。

生成方式：
- 取排列 $p = (p_1, p_2,\cdots,p_n)$，满足其为一个 $1$ 至 $n$ 的排列。
- 对于任意 $1\le i \le m$ 的 $i$，令 $x_i$ 为 $p_{l_i}， p_{l_i + 1},\cdots ,p_{r_i}$ 中最大值对应的下标。即 $p_{x_i} = \max\{p_{l_i}， p_{l_i + 1},\cdots, p_{r_i}\}$。

$2\le n\le 300,\ 1\le m\le \frac{n(n - 1)}2$。

## $\text{solution}$

同一个 $x$ 可能对应多个 $p$，因此这样计数比较困难。   
考虑反过来计数。

对于给定的 $x$，我们将按照以下的方式构造 $p$：
- 令 $p = (-1,-1,\cdots,-1)$ 。
- 我们从 $n$ 开始依次递减地考虑每个值 $v$。对于每个值，我们找到 $v$ 能放的最左侧的位置，放进去。
  
计数可以通过这种方式生成的 $p$ 。

设当前最值为 $v$。我们首先确定下标 $m$，使得 $p_m = v$。对于所有包含 $m$ 的区间 $i$，有 $x_i = m$。删除这些包含 $m$ 的区间后，我们可以分别考虑位于 $m$ 左右两侧的区间。由于 $m$ 为最左侧的可以放 $v$ 的位置，右侧的数均小于左侧的数，这部分是和原问题等价但规模更小的子问题。

现在考虑左侧。我们令 $k$ 为 $m$ 左侧最大元素对应的下标。有：必定存在一个左侧区间同时包含 $k$ 和 $m$。  
考虑反证。如果左侧没有区间同时包含 $k$ 和 $m$，那我们可以令 $p_k = v$，这必定是更优且满足要求的。这与假设矛盾，因此必定存在同时包含 $k$ 和 $m$ 的左侧区间。  
因此，左侧区间所填的数的最大值必定大于等于 $v$。

考虑区间 dp。我们设 $f(l,r,m)$ 为 $[l,r]$ 区间满足最大值的下标大于等于 $m$ 的方案数。可以通过枚举中点以及预处理区间最大值的方式转移。转移时加入后缀和即可快速得到最终答案。

时间复杂度 $O(n^3)$。

$\text{code : }$

```cpp
#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int,int>; 
template <typename T> void get(T & x) {
	x = 0; char ch = getchar(); bool f = false; while (ch < '0' or ch > '9') f = f or ch == '-', ch = getchar();
	while ('0' <= ch and ch <= '9') x = (x << 1) + (x << 3) + ch - '0', ch = getchar(); f && (x = -x); 
} template <typename T, typename ... Args> void get(T & a, Args & ... b) { get(a); get(b...); }
template <typename T1, typename T2> T1 min(T1 a, T2 b) { T1 _b = static_cast<T1>(b); return a < b ? a : b; }
#define rep(i,s,t) for (register int i = (s), i##_ = (t) + 1; i < i##_; ++ i)
#define pre(i,s,t) for (register int i = (s), i##_ = (t) - 1; i > i##_; -- i)
const int N = 5e2 + 10;

const int mod = 998244353;
const int inv2 = (mod + 1) >> 1;
template <typename T1, typename T2> T1 add(T1 a, T2 b) { return (a += b) >= mod ? a - mod : a; }
template <typename T1, typename ...Args> T1 add(T1 a, Args ... b) { return add(a, add(b...)); }
struct FastMod { int m; ll b; void init(int _m) { m = _m; if (m == 0) m = 1; b = ((lll)1<<64) / m; } FastMod(int _m) { init(_m); } int operator() (ll a) {ll q = ((lll)a * b) >> 64; a -= q * m; if (a >= m) a -= m; return a; } } Mod(mod);
int mul(int a, int b) { return Mod(1ll * a * b); } template <typename ...Args> int mul(int a, Args ...b) { return mul(a, mul(b...)); }
template <typename T1, typename T2> T1 qp(T1 a, T2 b) { T1 ret = 1; for (; b > 0; a = mul(a, a), b >>= 1) if (b & 1) ret = mul(ret, a); return ret; }

int n, m, f[N][N][N], g[N][N][N];
pii v[N * (N - 1) >> 1];

int main() {
	get(n, m); rep(i,1,m) get(v[i].first, v[i].second);
	rep(i,0,n+1) rep(j,0,n+1) rep(k,0,n+1) g[i][j][k] = n + 1;
	rep(i,1,m) rep(k,v[i].first,v[i].second) g[v[i].first][v[i].second][k] = min(g[v[i].first][v[i].second][k], v[i].first);
	pre(l,n,1) rep(r,l+1,n) rep(k,l,r) g[l][r][k] = min( { g[l][r][k], g[l+1][r][k], g[l][r-1][k] } );
	rep(l,1,n+1) rep(k,1,n+1) f[l][l-1][k] = 1;
	pre(l,n,1) rep(r,l,n) pre(k,r,l) f[l][r][k] = add(f[l][r][k + 1], mul(f[l][k - 1][g[l][r][k]], f[k + 1][r][k + 1])); 
	cout << f[1][n][1] << '\n';
}
```

---

## 作者：OptimisticForever (赞：6)

### [AGC056B] Range Argmax

upd on 10.24：更改了数组 $a$ 的定义，感谢 eastcloud。

首先，我们知道一个 $x$ 数组对应了多个 $p$ 数组。

这样子很不好计数，考虑计数 $x$ 使得 $p$ 只有一种。

一种合法的方案：

>考虑枚举 $i=n\to 1$，把 $i$ 能放置的最前位置找出来，放进去，删掉包含 $i$ 的所有区间。

观察这个过程，我们感受到可以区间 dp。

设 $f_{i,j,k}$ 表示区间 $[i,j]$，其中区间 $[i,j]$ 的最大值的位置 $\geq k$ 的答案。

我们记当前区间的最大值位置为 $k$。考虑计算最大值位置为 $k$ 的答案，其余直接继承 $k+1$。

对于最大值位置为 $k$ 的答案，把序列分成 $[l,k-1],[k+1,r]$。对于 $[k+1,r]$ 的部分，比较简单，没有别的限制。

对于 $[l,k-1]$ 的部分，考虑这部分的最大值最前可以取到什么位置。

>结论：设 $[l,k-1]$ 的最大值为 $k'$，则若不存在一个限制区间包含 $k',k$ 这两个点，则不合法。
>
>证明：
>
>若不存在的话，我们可以交换 $k,k'$ 这两个点，即最大值的最前位置不只是 $k$。

由此，我们需要满足 $[l,k-1]$ 的最大值要与 $k$ 被同样的限制区间包含，即预处理 $a_{l,r,k}$ 表示覆盖 $k$ 这个位置的**被 $[l,r]$ 包含**的限制区间中左端点的最小值。

于是 $f_{l,r,k+1}+f_{l,k-1,a_{l,r,k}}\times f_{k+1,r,k+1}\to f_{l,r,k}$。时间复杂度 $O(n^3)$。

---

## 作者：DaiRuiChen007 (赞：6)

# AGC056B 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_agc056_b)

**题目大意**

> 给定 $m$ 个 $[1,n]$ 的子区间 $[l_1,r_1]\sim [l_m,r_m]$，对于一个 $1\sim n$ 的排列 $p$，定义 $x_i$ 表示 $p[l_i,r_i]$ 中最大值的下标。
>
> 求有多少个可能被生成的 $x_1\sim x_m$。
>
> 数据范围：$n\le 300,m\le \dfrac{n(n-1)}2$。

**思路分析**

考虑把每组 $\{x_i\}$ 唯一对应的一组 $\{p_i\}$ 上，考虑用插入的方式刻画。

依次插入 $n\sim 1$，每次把对应值插到当前的最左边的可能位置。

设当前最大值插到了 $u$ 上，那么所有包含 $u$ 的区间的 $x_i$ 都已经确定了，原问题被分成了 $[1,u),(u,n]$ 两个部分。

但是我们还要限制 $u$ 是第一个可能的取值，那么考虑 $[1,u)$ 中的最大值 $v$，当且仅当存在一个区间同时包含 $u,v$。

因此我们可以发现如下的子结构并 dp：$dp_{l,r,u}$ 表示 $[l,r]$ 内，最大值的最小取值必须填在 $[u,r]$ 中的方案数。

我们设 $pos(L,R,u)$ 表示所有 $u\in [l_i,r_i]\subseteq[L,R]$ 的最小 $l_i$，那么有如下转移：
$$
dp_{l,r,u}=dp_{l,r,u+1}+dp_{l,u-1,pos(l,r,u)}\times dp_{u+1,r,u+1}
$$
预处理出 $pos$ 后暴力转移即可。

时间复杂度 $\mathcal O(nm+n^3)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=305,MOD=998244353;
ll dp[MAXN][MAXN][MAXN];
int lim[MAXN][MAXN][MAXN];
signed main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for(int len=1;len<=n;++len) for(int l=1,r=len;r<=n;++l,++r) {
		for(int i=l;i<=r;++i) lim[l][r][i]=n+1;
	}
	for(int i=1,l,r;i<=m;++i) {
		scanf("%d%d",&l,&r);
		for(int j=l;j<=r;++j) lim[l][r][j]=min(lim[l][r][j],l);
	}
	for(int len=2;len<=n;++len) for(int l=1,r=len;r<=n;++l,++r) {
		for(int i=l+1;i<=r;++i) lim[l][r][i]=min(lim[l][r][i],lim[l+1][r][i]);
		for(int i=l;i<=r-1;++i) lim[l][r][i]=min(lim[l][r][i],lim[l][r-1][i]);
	}
	for(int i=1;i<=n+1;++i) for(int j=1;j<=n+1;++j) dp[i][i-1][j]=1;
	for(int len=1;len<=n;++len) for(int l=1,r=len;r<=n;++l,++r) {
		for(int i=r;i>=l;--i) {
			dp[l][r][i]=(dp[l][r][i+1]+dp[l][i-1][lim[l][r][i]]*dp[i+1][r][i+1])%MOD;
		}
	}
	printf("%lld\n",dp[1][n][1]);
	return 0;
}
```

---

## 作者：sky_landscape (赞：4)

考虑整数序列 $x$ 是很不好算的，尝试建立一个由 $x$ 到 $p$ 的映射。

如果直接对应是不行的，一个简单的反例就是在 $m$ 很小时一个序列 $x$ 可能对应多个 $p$。所以需要对于每一组 $x$，构造一组与它对应的 $p$。

具体来说，从 $n$ 枚举到 $1$，每一次把枚举的数插到 $p$ 排列中尽可能靠左的位置，那么 $x$ 就可以一一对应上这组 $p$。

观察数据范围 $n\le 300$，可以区间 $dp$。

设 $dp[l][r][k]$ 为区间 $[l,r]$ 内 $p$ 最大的位置大于等于 $k$ 的方案数。

观察到转移有限制。限制主要在左侧，因为没有限制 $k$ 可以更靠左。设 $q$ 为 $[l,r]$ 内 $k$ 左侧 $p$ 最大的位置。如果 $[l,r]$ 内没有区间同时包含 $q,k$ 那么 $k$ 在 $q$ 的位置上显然更优。

所以需要维护辅助数组 $f$，$f[l][r][k]$ 表示区间 $[l,r]$ 内包含 $k$ 的所有区间的最小左端点。

最后 $dp[l][r][k]$ 的转移就很明了了。

$dp[l][r][k]=dp[l][r][k+1]+dp[l][k-1][f[l][r][k]]\times dp[k+1][r][k+1]$。

左半部分不用解释，右半部分中 $dp[l][k-1][f[l][r][k]]$ 是受上文限制的左侧方案数，$dp[k+1][r][k+1]$ 是右侧方案数。

记得输出答案后换行，不然会显示错误......

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int N=310;
int n,m;
int dp[N][N][N];//dp[i][j][k]表示[i,j]中的最大值的位置大于等于k的方案数 
int f[N][N][N];//在[i,j]中的包含k的最小的区间的左端点 
int add(int x,int y){
    return (x+y)%mod;
}

int mul(int x,int y){
    return (x*y)%mod;
}

inline int read(){
    char ch;int x=0;bool f=false;
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=true;
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    if(f) x=-x;
    return x;
}

signed main(){
    n=read(),m=read();
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                dp[i][j][k]=0,f[i][j][k]=n+1;
            }
        }
    }
    int l,r;
    for(int i=1;i<=m;i++){
        l=read(),r=read();
        for(int k=l;k<=r;k++){
            f[l][r][k]=min(f[l][r][k],l);
        }
    }
    for(int i=1;i<=n;i++){
        for(int l=1;l<=n;l++){
            int r=(l+i-1);
            if(r>n) continue;
            for(int k=l;k<=r;k++){
                f[l][r][k]=min(f[l][r][k],min(f[l][r-1][k],f[l+1][r][k]));
            }
        }
    }
    for(int i=1;i<=n+1;i++){
        for(int j=1;j<=n+1;j++) dp[i][i-1][j]=1;
    }
    for(int i=1;i<=n;i++){
        for(int l=1;l<=n;l++){
            int r=(l+i-1);
            if(r>n) continue;
            for(int k=r;k>=l;k--){
                dp[l][r][k]=add(dp[l][r][k+1],mul(dp[l][k-1][f[l][r][k]],dp[k+1][r][k+1]));
            }
        }
    }
    cout<<dp[1][n][1]<<"\n";
    return 0;
}
```

---

## 作者：mskqwq (赞：2)

先考虑将 $x$ 与 $p$ 建立一个简单的双射，假设固定 $x$ 去生成 $p$。从 $n$ 到 $1$ 枚举一个 $v$ 插入到 $p$ 中最左边的能插入的位置，这个位置要么没有被区间覆盖，要么所有覆盖这个位置的区间的 $x_i$ 都是这个位置。

然后发现插入 $v$ 之后左右两边独立了，考虑区间 dp。设当前区间为 $[l,r]$，最大值位置为 $p$。注意我们需要 $p$ 是左边第一个合法的位置，那么对于 $[l,p-1]$ 内的最大值位置 $k$，需要有**至少一个**区间包含 $p$ 和 $k$，否则把 $p$ 换成 $k$ 更优。对于右半部分的最大值位置则没有要求。

然后无需在意 $[l,p-1]$ 内取 $k$ 作为最大值位置是否合法，因为不合法的 dp 值为 $0$。

设 $f_{l,r,p}$ 表示区间 $[l,r]$ 内，最大值位置为 $p$ 的方案数。预处理 $g_{l,r,j}$ 表示 $[l,r]$ 内的区间，包含 $j$ 的区间的左端点的最小值，然后对 $f$ 做后缀和优化，时间复杂度 $O(n^3)$。

```cpp
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#define fi first
#define se second
#define ep emplace
#define MISAKA main
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define rg(x) x.begin(),x.end()
#define mems(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _rep(i,a,b) for(int i=(a);i>=(b);--i)
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define FIO(FILE) freopen(FILE".in","r",stdin),freopen(FILE".out","w",stdout)
using namespace std;
bool __st;
inline int read(){
    char c=getchar();int f=1,x=0;
    for(;c<48||c>57;c=getchar())if(c=='-') f=-1;
    for(;47<c&&c<58;c=getchar()) x=(x<<3)+(x<<1)+(c^48);
    return x*f;
}
const int N=310,mod=998244353;
ll n,m,f[N][N][N],g[N][N][N];
void qmn(ll &a,ll b){if(b<a)a=b;}
void misaka(){
    n=read(),m=read();
    rep(i,1,n)rep(j,1,n)rep(k,1,n) g[i][j][k]=n+1;
    rep(i,1,m){
        int l=read(),r=read();
        rep(j,l,r) qmn(g[l][r][j],l);
    }
    rep(_,2,n)rep(l,1,n-_+1){
        int r=l+_-1;
        rep(j,l,r) qmn(g[l][r][j],min(g[l+1][r][j],g[l][r-1][j]));
    }
    rep(i,1,n+1)rep(j,1,n+1) f[i][i-1][j]=1;
    rep(_,1,n)rep(l,1,n-_+1){
        int r=l+_-1;
        _rep(p,r,l) f[l][r][p]=(f[l][r][p+1]+f[l][p-1][g[l][r][p]]*f[p+1][r][p+1])%mod;
    }
    printf("%lld\n",f[1][n][1]);
}
bool __ed;
signed MISAKA(){
    #ifdef LOCAL_MSK
    atexit([](){
    debug("\n%.3lfs  ",(double)clock()/CLOCKS_PER_SEC);
    debug("%.3lfMB\n",abs(&__st-&__ed)/1024./1024);});
    #endif
    
    int T=1;
    while(T--) misaka();
    return 0;
}

```

---

## 作者：wjyppm1403 (赞：1)

[可能更好的阅读体验](https://worldcpu.github.io/posts/500326e7/)

# 正解

首先在分析问题的时候不难发现操作的一个性质就是同一个 $x_i$ 对应多个所谓的 $p_{[l,r]}$ 序列。 

对于这种操作对应多个序列不好计数的限制，一般情况下我们有下面两种思路

- 探究一下什么序列能够被得到，而不是操作序列的角度设计 DP 状态。
- 若硬是从操作序列入手，我们可以通过给操作附上某种特定的顺序，让每一个序列都附上一个唯一的代表元，而这个代表元就是我们需要分题目去设计的。

如果你从第一个思路想的话你会很快陷入瓶颈，不建议自行尝试不然你会很痛苦。

我们从第二个思路入手，那么我们要对操作序列确定一个顺序，使得我们的决策可以唯一化。

考虑用插入法，我们可以从大到小钦定每一个值的位置，就是倒着遍历 $n,n-1,n-2,\dots,2,1$。每一次我们把对应的值插到当前最左端的位置。

通过这种方式，我们可以将问题从对 $x$ 计数变为对上面合法构造的排列 $p$ 进行计数。

考虑如果 DP，注意到每一次操作都是涉及的是 $\max$ 操作，不妨考虑利用大根堆笛卡尔树的形态进行刻画，笛卡尔树一个很好的特性就是形态是确定的而不是变化的。

那么原题目中的最大值位置 $x_i$ 能够产生贡献的区间一定是一个排列上的连续区间，对应到笛卡尔树上就是笛卡尔树的一个子树。那么现在问题转化为对笛卡尔树形态计数，考虑枚举最大值 DP，设 $f(l,r,k)$ 表示当前枚举的最大值位置在大于等于 $k$ 的范围，管辖的子树区间为 $[l,r]$ 的笛卡尔树形态数量。

转移显然可以考虑递归处理 $[l,k-1],[k+1,r]$，或者从 $f[l,r,k+1]$ 传递过来，对于 $f(k+1,r,*)$ 的这个第三维是好说的，就是 $k+1$。但是 $f(l,k-1,*)$ 是比较难以确定的，因为我们不好确定这个范围。

这里有一个结论，设 $k'$ 表示 $[l,k-1]$ 最大值的位置，那么 $[l,r]$ 合法的充要条件是：$[l,k-1],[k+1,r]$ 是合法的，并且不能存在一个 $l\le l_i \le k' \le k \le r_i \le r$。

必要性是显然的，假设不存在 $l\le l_i \le k' \le k \le r_i \le r$ 的话那么我直接把最大值钦定为 $k'$ 也是合法的。考虑证明充分性，如果存在 $l\le l_i \le k' \le k \le r_i \le r$，那么根据前提条件左区间合法性可以知道把最大值钦定在 $k'$ 的左边都是不合法的，而如果把最大值钦定在 $[k',k)$ 中某个位置，那么 $x_i \neq k$ 了，所以最左端和发位置就是 $k$ 了，证毕。

那么我们可以预处理 $g(l,r,k)$ 表示 $[l,r]$ 最大值在 $k$ 的时候，$[l,k-1]$ 的最大值位置最小是多少，预处理是 $O(n^3)$ 的，转移可以做到 $O(1)$，时间复杂度为 $O(n^3)$。

[提交记录](https://atcoder.jp/contests/agc056/submissions/67873167)

# 反思

这个题还是比较好的，我们在遇见这种操作序列出现多个对应一个的时候，我们要找出的就是那个序列对应的唯一**代表元**。通过将结果与唯一的操作序列对应起来，从而设计出无重复的 DP。

- 探究一下什么序列能够被得到，而不是从操作序列的角度设计 DP 状态。
- 若硬是从操作序列入手，我们可以通过给操作附上某种特定的顺序，让每一个序列都附上一个唯一的代表元，而这个代表元就是我们需要分题目去设计的。

笛卡尔树形态特别适合这种计数思想，尤其是当最大值反复横跳的时候考虑笛卡尔树会有奇效，其实笛卡尔树上的 DP，就是所谓的枚举最大值转移。

---

## 作者：lalaouye (赞：1)

发现一个序列 $x$ 不止可以用一个 $p$ 得到，肯定不能直接计数，考虑构造一个映射。

假如已经定下了 $x$，我们通过一种固定的操作得到 $p$，这样就能改为统计可以由操作得到的 $p$ 的数量，他们同样唯一对应一个 $x$。

我们考虑枚举从 $n$ 到 $1$ 去枚举 $v$，对每个 $v$ 找到一个能找到的最左边的点赋值。一个位置 $pos$ 能赋值 $v$ 当且仅当所有 $l_i,r_i$ 包含 $pos$ 的 $x_i$ 等于 $pos$。

接下来我们就可以处理左区间和右区间的位置了。容易发现其右边的值都要小于左边的值，这将变成两个子问题。

现在 $x$ 并不固定，我们需要分析条件才能计数。

注意到，若当前我们在 $pos$ 这里赋值，那么对于左侧的最大值的位置 $k$，一定存在一个区间满足 $l_i\le k\le pos\le r_i$，因为若没有区间同时包含 $k,pos$，那么显然我可以让 $p_{pos}=v$，所以一定存在这样的区间。之所以存在这种情况那只能是因为这个区间的 $x_i$ 等于 $pos$。我们需要用一个大数在这里填，填完以后再将区间删去才能更新 $k$。

这启发我们进行一个区间 dp，设 $f_{l,r,i}$ 表示在区间 $l,r$ 中最大值位置在 $i$ 的方案数。但是由于这样子复杂度很劣，我们将状态改为在区间 $l,r$ 中最大值位置大于等于 $i$ 的方案数就能 $\mathcal{O}(n^3)$ 解决问题了，具体就是先维护区间如果要选 $pos$ 赋值，包含 $pos$ 的区间的最小 $l_i$，然后再后缀和转移即可。

代码：

````
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = l; i <= r; ++ i)
#define rrp(i, l, r) for (int i = r; i >= l; -- i)
#define pii pair <int, int>
#define eb emplace_back
#define id(x, y) n * (x - 1) + y
#define ls p << 1
#define rs ls | 1
using namespace std;
constexpr int N = 300 + 5, M = (1ll << 31) - 1, P = 998244353;
constexpr double PI = acos (-1.0);
inline int rd () {
  int x = 0, f = 1;
  char ch = getchar ();
  while (! isdigit (ch)) {
    if (ch == '-') f = -1;
    ch = getchar ();
  }
  while (isdigit (ch)) {
    x = (x << 1) + (x << 3) + ch - 48;
    ch = getchar ();
  }
  return x * f;
}
int qpow (int x, int y) {
  int ret = 1;
  for (; y; y >>= 1, x = x * x % P) if (y & 1) ret = ret * x % P;
  return ret;
}
int f[N][N][N], g[N][N][N];
int n, m;
long long fac[N], ifac[N];
int C (int n, int m) {
  if (m < 0 || m > n) return 0;
  return fac[n] * ifac[m] % P * ifac[n - m] % P;
}
int l[N * N], r[N * N];
signed main () {
  // freopen ("1.in", "r", stdin);
  // freopen ("1.out", "w", stdout);
  n = rd (), m = rd ();
  rep (i, 1, m) l[i] = rd (), r[i] = rd ();
  rep (i, 0, n + 1) rep (j, 0, n + 1) rep (k, 0, n + 1) g[i][j][k] = n + 1;
  rep (i, 1, m) {
    rep (j, l[i], r[i]) {
      g[l[i]][r[i]][j] = min (g[l[i]][r[i]][j], l[i]); 
    }
  }
  rep (len, 1, n) {
    rep (l, 1, n - len + 1) {
      int r = l + len - 1;
      rep (k, 1, n) g[l][r][k] = min (g[l][r][k], min (g[l + 1][r][k], g[l][r - 1][k]));
    }
  }
  rep (l, 1, n + 1) rep (k, 1, n + 1) f[l][l - 1][k] = 1;
  rep (len, 1, n) {
    rep (l, 1, n - len + 1) {
      int r = l + len - 1;
      rrp (k, l, r) {
        (f[l][r][k] += f[l][r][k + 1] + f[l][k - 1][g[l][r][k]] * f[k + 1][r][k + 1]) %= P;
      }
    }
  } cout << f[1][n][1];
}
````

---

