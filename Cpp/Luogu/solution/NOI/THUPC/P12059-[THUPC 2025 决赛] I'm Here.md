# [THUPC 2025 决赛] I'm Here

## 题目描述


黑猫的世界正在走向终结。 

在这个正在走向终结的世界里，Liki 和 Sasami 需要找到世界的真相。具体来说，这个世界可以看做一棵 $n$ 个结点的有根树，根结点的编号为 $1$。并且存在一种对树进行深度优先搜索的方案，使第 $i$ 次访问的结点为 $i$。也就是说 **$1\sim n$ 可以构成这棵树的一个 dfs 序**。在最开始，所有的结点都没有崩溃。

每一天，Liki 和 Sasami 会探索一个没有崩坏的结点 $u$。在这次探索后，为了引导他们发现世界真相，黑猫会使 $u$ 及子树中所有点崩坏。 

同时，在第 $i$ 天 Liki 和 Sasami 的探索结束后，由于自身力量枯竭，第 $n-i+1$ 号结点若没有崩坏，则会崩坏。 

分别对 $i \in [1,n]$ 求 Liki 和 Sasami 有多少种恰好探索 $i$ 天的探索方案，满足最后一次探索的是 $1$ 号结点，对 $998244353$ 取模。


## 说明/提示

### 样例 #1 解释


对于样例 $1$，以下 $8$ 种探索序列合法：

$\{1\},\{2,1\},\{3,1\},\{4,1\},\{3,2,1\},\{4,2,1\},\{4,3,1\},\{4,3,2,1\}$。


### 来源与致谢

来自 THUPC2025（2025 年清华大学学生程序设计竞赛暨高校邀请赛）决赛。感谢 THUSAA 的提供的题目。

数据、题面、标程、题解等请参阅 THUPC 官方仓库 <https://thusaac.com/public>。

## 样例 #1

### 输入

```
4
1 2
2 3
2 4
```

### 输出

```
1 3 3 1
```

## 样例 #2

### 输入

```
7
4 2
6 1
5 1
7 6
2 3
1 2
```

### 输出

```
1 6 23 48 43 17 1
```

# 题解

## 作者：Shui_Dream (赞：7)

现有一棵 dfs 序为 $1,2,...,n$ 的树。对于所有 $i$ 求选出 $i$ 个点的好排列的方案数。

好排列满足以下条件：

- 若点 $u,v$ 都被选中且 $u$ 是 $v$ 的祖先，那么在排列中 $u$ 在 $v$ 后面。

- 若点 $u$ 被选中，那么 $u$ 必须出现在序列中前 $(n-i+1)$ 个位置。

考虑如果没有限制 2，第一个限制是简单的内向树拓扑序计数问题。简单树上背包可以做到 $O(n^2)$。设 $g_{u,i}$ 表示 $u$ 子树内选出 $i$ 个点且 $u$ 被选中的满足限制的序列个数。

考虑限制 2，容易发现最终序列中是后缀最大值的位置的限制是更严格的。其他位置只要满足限制 1 即可。考虑从大到小将每个被选中的数插入序列，如果插入时插在了序列末尾，那么其为后缀最大值。

设 $f_{i,j,k}$ 表示填完了 $\ge i$ 的数，填了 $j$ 个，强制当前序列最后一个数填在位置 $k$ 的方案数。

分类讨论：

- $i$ 没被选中，继承 $f_{i+1}$ 的状态即可。
- $i$ 被选中，且为后缀最大值，$i$ 填在当前序列末尾，枚举一个位置 $x$，满足 $k<x\le n-i+1$，从 $f_{i+1}$ 转移过来。显然满足限制 1。
- $i$ 被选中，且不为后缀最大值，枚举子树内包括 $i$ 共选了 $x$ 个数，那么这 $x$ 个数填在 $k$ 前面即可。有 $f_{i,j+x,k}\leftarrow f_{i+sz_i,j,k}\times g_{i,x}\times \binom{k-j}{x}$。

复杂度 $O(n^4)$。代码很好写。
```cpp
#include<bits/stdc++.h>
#define psb push_back
using namespace std;
typedef long long LL;
inline int read(){
    char ch=getchar(); while(!isdigit(ch) && ch!='-') ch=getchar();
    int x=0,ff=1; if(ch=='-') ff=-1,ch=getchar();
    while(isdigit(ch)) x=(x<<3) + (x<<1) + (ch^48),ch=getchar();
    return x*ff;
}
const int N=85,P=998244353;
inline void add(int &x,int y) {x+=y; x=x>=P?x-P:x;}
int n,fz[N][N],fzu[N][N],fz2[N],sz[N],rd[N],C[N][N],f[N][N][N]; vector<int> e[N];
void dfs1(int u){
    sz[u]=0; fz[u][0]=1; rd[u]=u;
    for(int v:e[u]){
        dfs1(v); rd[u]=rd[v];
        for(int i=0;i<=sz[u]+sz[v];i++) fz2[i]=fz[u][i],fz[u][i]=0;
        for(int i=0;i<=sz[u];i++) for(int j=0;j<=sz[v];j++) add(fz[u][i+j],1ll*fz2[i]*fz[v][j]%P*C[i+j][i]%P);
        sz[u]+=sz[v];
    }
    ++sz[u]; for(int i=sz[u];i>=1;i--) fzu[u][i]=fz[u][i-1],add(fz[u][i],fzu[u][i]);
    
}
int main(){
    for(int i=0;i<N;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
    }
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(); if(u>v) swap(u,v);
        e[u].psb(v);
    }
    dfs1(1); f[n+1][0][0]=1;
    for(int i=n,bf;i>=1;i--){
        if(i>1){
            for(int j=0;j<=n-rd[i];j++) for(int k=j;k<=n;k++) if((bf=f[rd[i]+1][j][k]))
                for(int l=1;l<=sz[i] && l<=k-j;l++) add(f[i][j+l][k],1ll*C[k-j][l]*fzu[i][l]%P*bf%P);
        }
        for(int j=0;j<=n-i;j++) for(int k=j;k<=n;k++) if((bf=f[i+1][j][k])){
            if(i>1) add(f[i][j][k],bf);
            for(int l=k+1;l<=n;l++) if(l<=n-i+1) add(f[i][j+1][l],bf);
        }
    }
    for(int i=1;i<=n;i++) printf("%d ",f[1][i][i]);
    puts("");
    return 0;
}
```

---

## 作者：_Cheems (赞：5)

题意：$n$ 个点的树，$1$ 为根。保证存在一种 dfs 序为 $1\dots n$。对每个 $k\in [1,n]$，求满足如下性质的数列 $p$ 个数：

* $p\in [1,n]$ 且互不相同。
* $i<j$ 则 $p_i$ 不为 $p_j$ 的祖先。
* $p_i\le n-i+1$。

前两个限制为拓扑序计数，有平方的树上背包做法。但由于该做法是“插入计数”的，所以难以维护第三个限制，因为需要具体位置而非相对位置。

实际上插入的过程是很自由的，能否通过适当的插入顺序，来规避这个问题呢？

尝试简化限制三，注意到 $i<j$ 且 $p_i<p_j$ 则 $i$ 受到的限制肯定比 $j$ 更紧，因为非法后缀更小且位置更左。这启发我们从大到小插入元素。

记 $f_{i,j}$ 为元素 $\ge i$ 且最右一个位置在 $j$ 的方案数。对于 $i-1$，假如插入在最右边，其祖先不可能被操作，易处理；否则无需考虑限制三，但是可能影响 $i-1$ 子树内的元素，整体考虑该子树的方案再归并回去即可，因为该子树的元素整体偏小所以结论仍成立。

预处理 $g_{i,j}$ 为子树内 $j$ 个点拓扑序数量即可。转移是朴素的，简单前缀和优化为 $O(n^4)$。

---

## 作者：Lgx_Q (赞：4)

如果第 $i$ 天点 $n - i + 1$ 不崩坏是容易的。

题目多加了一个条件，如果第 $i$ 天探索了点 $x_i$，那么需要满足 $i \le n - x_i + 1$，即点 $u$ 需要在前 $n - u + 1$ 天探索，或者不探索。

所以现在我们有两个条件：

+ 对于两个探索的点 $u, v$，如果 $u$ 是 $v$ 的祖先，则需满足探索 $u$ 的时间晚于探索 $v$ 的时间。

+ 若探索点 $u$，则必须在前 $n - u + 1$ 天探索。

尝试设计 DP。观察题目给定的性质，给定的树恰好存在一个 DFS 序为 $[1, 2, \dots, n]$。

如果树是一条以 $1$ 根的菊花图，容易想到把探索的点按编号从大到小依次插入到探索序列中，只需要把每个点的方案数乘起来即可。在普通的树上，进而想到在处理到一个点 $u$ 处，按照编号从大到小依次考虑每个儿子的子树，依次插入到探索序列。

那祖先的限制怎么解决呢？一个想法是记录每个儿子子树内的最晚探索时间，很显然这样是错误的：由于 DP，不同儿子子树是独立计算的，会产生冲突（多个点挤在一天探索）。

为了适应之前的想法，即按照编号从大到小插入每个儿子子树的点，不难想到先决定祖先的探索时间 $t$，这样只需要限制 $u$ 的子树内的点的探索时间 $ < t$。

对于某个儿子的子树，由于我们是按照编号从大到小考虑每个儿子，所以在探索序列中，之前的儿子子树可能会留空位。此时填入这些空位一定是合法的。

设 $f_{u, i, j, k}$ 表示仅考虑 $u$ 的子树内的点，探索了 $i$ 个点，$u$ 的最近的探索过的祖先探索时间为 $n - u + 2 - j$，且在探索序列最前面额外提供了 $k$ 个空位，此时的方案数。

注意理解这里的 $j$ 的含义，设 $siz_u$ 为 $u$ 的子树大小，那么 $j \in [0, siz_u]$。实际上想表达的意义是：如果 $j = 0$，那么祖先的探索时间 $> n - u + 1$，即无限制。如果 $j = siz_u$，那么由于祖先的限制导致 $u$ 子树内探索的点只能填在 $k$ 个空位上。如果 $0 < j < siz_u$，那么子树内编号为 $[u, u + j - 1]$ 的点受到了限制，而 $[u + j, u + siz_u - 1]$ 的点没有限制。

具体 DP 时，先依次合并所有儿子子树，再把 $u$ 合并进去。

合并两部分的时候，设两个 DP 数组为 $f'_{u, i, j, k}$ 和 $f_{v, i, j, k}$，枚举整个 $i$ 和 $l$ 为两部分探索的点数，枚举 $j$ 为祖先探索的限制，枚举 $k$ 为最开始提供的空位数，则：

$$f'_{u, i, \max(0, j - siz_v), k} \times f_{v, l, \min(j, siz'_u), k + siz'_u - \max(0, j - siz_v) - i} \to f_{u, i + l, j, k}$$

其中 $siz'_u$ 为已经合并过的儿子子树大小总和（不包括点 $u$）。

最后把点 $u$ 合并进去。如果 $u$ 不探索是容易的，否则即是把 $j$ 重新刷新一遍。设合并前的 DP 数组为 $f'_{u, i, j, k}$，合并后的为 $f_{u, i, j, k}$。

+ 当 $u$ 不插在空位处，枚举插入的位置 $l(j\le l \le siz'_u)$：$f_{u, i, j, k} \gets f'_{u, i, l, k}$

+ 当 $u$ 插在空位处，此时子树内所有点全部受到限制，枚举插在了第 $l(1\le l\le k)$ 个空位：$f_{u, i, j, k} \gets f'_{u, i, siz'_u, l - 1}$

这部分可以前缀和优化，合并部分的时间不难分析，总时间复杂度为 $\mathcal O(n^4)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define fi first
#define se second
#define mkp make_pair
#define pir pair <ll, ll>
#define pb push_back
#define i128 __int128
using namespace std;
char buf[1 << 22], *p1, *p2;
// #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 22) - 10, stdin), p1 == p2)? EOF : *p1++)
template <class T>
const inline void rd(T &x) {
    char ch; bool neg = 0;
    while(!isdigit(ch = getchar()))
        if(ch == '-') neg = 1;
    x = ch - '0';
    while(isdigit(ch = getchar()))
        x = (x << 1) + (x << 3) + ch - '0';
    if(neg) x = -x;
}
const ll maxn = 85, inf = 1e9, mod = 998244353;
ll power(ll a, ll b = mod - 2) {
	ll s = 1;
	while(b) {
		if(b & 1) s = 1ll * s * a %mod;
		a = 1ll * a * a %mod, b >>= 1;
	} return s;
}
template <class T, class _T>
const inline ll pls(const T x, const _T y) { return x + y >= mod? x + y - mod : x + y; }
template <class T, class _T>
const inline void add(T &x, const _T y) { x = x + y >= mod? x + y - mod : x + y; }
template <class T, class _T>
const inline void chkmax(T &x, const _T y) { x = x < y? y : x; }
template <class T, class _T>
const inline void chkmin(T &x, const _T y) { x = x < y? x : y; }

ll n, f[maxn][maxn][maxn][maxn], siz[maxn];
vector <ll> to[maxn]; ll g[maxn][maxn][maxn];
ll s1[maxn][maxn][maxn], s2[maxn][maxn][maxn];

void dfs(ll u, ll fa = 0) {
    sort(to[u].begin(), to[u].end(), greater <ll> ());
    for(ll v: to[u])
        if(v ^ fa) dfs(v, u);
    for(ll i = 0; i < n; i++) f[u][0][0][i] = 1;
    siz[u] = 1;
    for(ll v: to[u])
        if(v ^ fa) {
            memset(g, 0, sizeof g);
            for(ll i = 0; i < siz[u]; i++)
                for(ll j = 0; j <= siz[u] + siz[v]; j++)
                    for(ll k = 0; k < n; k++)
                        for(ll l = 0; l <= siz[v]; l++) {
                            if(k + siz[u] - 1 + min(0ll, siz[v] - j) - i >= 0)
                                add(g[i + l][j][k], f[u][i][max(0ll, j - siz[v])][k] %mod *
                                 f[v][l][min(j, siz[v])][k + siz[u] - 1 + min(0ll, siz[v] - j) - i] %mod);
                        }
            memcpy(f[u], g, sizeof g), siz[u] += siz[v];
        }
    memcpy(g, f[u], sizeof g);
    memset(s1, 0, sizeof s1), memset(s2, 0, sizeof s2);
    for(ll i = 0; i < siz[u]; i++)
        for(ll j = siz[u] - 1; ~j; j--)
            for(ll k = 0; k < n; k++) {
                s1[i][j][k] = s2[i][j][k] = g[i][j][k];
                add(s1[i][j][k], s1[i][j + 1][k]);
                if(k) add(s2[i][j][k], s2[i][j][k - 1]);
            }
    for(ll i = 0; i <= siz[u]; i++)
        for(ll j = 0; j <= siz[u]; j++)
            for(ll k = 0; k < n; k++) {
                f[u][i][j][k] = g[i][max(0ll, j - 1)][k];
                if(i) add(f[u][i][j][k], s1[i - 1][j][k]);
                if(i && k) add(f[u][i][j][k], s2[i - 1][siz[u] - 1][k - 1]);
            }
}

int main() {
    rd(n);
    for(ll i = 1; i < n; i++) {
        ll u, v; rd(u), rd(v);
        to[u].pb(v), to[v].pb(u);
    } dfs(1);
    for(ll i = 1; i <= n; i++)
        printf("%lld ", g[i - 1][n - i][0]);
	return 0;
}
```

---

## 作者：abruce (赞：4)

出题人题解。题目 idea 与背景来源：Little Busters! EX 佐佐美线。  
另外，此题有一些空间更优的做法，也许时间也更优，希望能写出题解进行指正。

对于树上选一个点删去一个子树方案数这个经典问题，一个常见的 dp 是记 $dp_{u,k}$ 为 $u$ 子树选 $k$ 个点方案数，转移时兄弟间用组合数将其合并，然后祖先要选就必须选在它们前面，这一部分 $O(n^2)$。  

回到本题，由于存在“自动删点”的过程因此我们不能将 $u$ 子树内选的点看成只有相对顺序的操作，因为其可能不合法。但我们考虑最终的操作序列，没有的位置留空：比如样例 $1$ 中第一次选 $4$，第二次选 $3$，第三次选 $1$，那么操作序列即为 $0134$。也就是第 $i$ 次选的点放在 $n-i+1$ 的位置上。这样，我们发现一个点 $u$ 只能填在 $u$ 及以后的位置，那么对于一个点 $u$ 的子树，其 dfs 序区间为 $[l,r]$，那么 $u$ 子树的点填到 $r$ 以后的位置一定合法，而 $u$ 留的空其前面的兄弟和祖先填进去只要没有父子关系干扰一定合法，于是我们考虑 dp。  

考虑一个 dp $f_{u,i,j,k}$ 表示 $u$ 子树 $i$ 这个位置留给祖先（也就是说 $i$ 及以前不能放东西，如果 $i=0$ 就不留），有 $j$ 个空（不包含给祖先留的），有 $k$ 个点要填到 $u$ 子树以后的位置。先考虑 $i=0$ 情况。那么合并两个子树的时候就是 dfs 序更小的子树可以选一些向后的操作填到 dfs 序更大子树的空里面。然后两个子树的空合并，向后操作合并。  

具体来说，考虑 $u$ 的儿子按 dfs 序倒序枚举，对于一个儿子 $v$，那么合并 $f_{u,0,j,k}$ 和 $f_{v,0,j1,k1}$ 的时候先枚举一个 $w$ 代表选多少个 $v$ 中的向后操作填到 $u$ 的 $v$ 之后的子树，转移即为 $f_{u,0,j+j1-w,k+k1-w}\leftarrow f_{u,0,j+j1-w,k+k1-w}+f_{u,0,j,k}\times f_{v,0,j1,k1}\times \binom{j}{w}\times\binom{k+k1-w}{k}$。

再考虑 $f_{v,i,j1,k1}$ ，发现它需要给祖先留空并不影响其和后面兄弟的转移，因此转移同上，只是 $v$ 留的空 $u$ 同样需要留，所以转移到 $f_{u,i,j+j1-w,k+k1-w}$。注意这里需要预处理转移系数（因为 $i$ 取任何值转移系数相同）才能达到 $O(n^5)$。

然后考虑 $f_{u,i,j,k}$ 的转移，即 $v$ 后面的子树已经留了空。那么 $v$ 子树现在不能放任何东西，但是可以用一些向后的操作填 $i$ 后面的空，这里用 $dp_{v,k}$ 去转移即可。

子树转移完后，接下来是 $u$ 自身的操作。$u$ 可以有几种选择：

- 不填，那么会多一个空 $f_{u,i,j,k}\rightarrow f_{u,i,j+1,k}$，如果把这个空留给祖先填，那么 $f_{u,0,j,k}\rightarrow f_{u,dfn_u,j,k}$。  
- 填到子树准备的空里面，此时有两种选择：一是不再给祖先留空，那么 $f_{u,i,j,k}\rightarrow f_{u,0,j+1,k}$，一种是在 $i$ 前面重新给祖先留一个空，那么 $f_{u,i,j,k}\rightarrow f_{u,i1,j+1,k}(i1<i)$。
- 填自己，此时不能给上面留空，$f_{u,0,j,k}$ 不变。
- 让自己变为向后操作，那么 $u$ 子树内现在不能填任何东西，但是可以给祖先留空，$f_{u,i,siz_u-2,k}\rightarrow f_{u,i,siz_u-1,k+1},f_{u,0,siz_u-1,k}\rightarrow f_{u,0,siz_u,k+1}$。

最后求答案的时候，对于要求 $k$ 次操作，相当于给 $1$ 在 $n-k+1$ 的位置留了空，同时恰好只有 $n-k$ 个空（那么后面就没有空，就是合法的操作序列），输出即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace tokido_saya {
	const int maxn=81,mod=998244353;
	typedef vector<int>::iterator iter;
	int n,lp[maxn],rp[maxn],siz[maxn];
	vector<int> v[maxn];
	ll f[maxn][maxn][maxn][maxn],dp[maxn][maxn],fac[maxn],inv[maxn];
	int zc[maxn][maxn][maxn][maxn];
	ll qpow(ll x,int y)
	{
		ll w=1;
		while(y)
		{
			if(y&1)w=w*x%mod;
			x=x*x%mod,y>>=1;
		}
		return w;
	}
	ll C(int x,int y)
	{
		if(y<0||y>x)return 0;
		return fac[x]*inv[x-y]%mod*inv[y]%mod;
	}
	void dfs1(int u)
	{
		lp[u]=rp[u]=u;
		for(iter it=v[u].begin();it!=v[u].end();it++)dfs1(*it),rp[u]=max(rp[u],rp[*it]);
	}
	void dfs2(int u)
	{
		f[u][0][0][0]=1,dp[u][0]=1;
		for(iter it=v[u].begin();it!=v[u].end();it++)
		{
			int v=*it;
			dfs2(v);
			for(int i=siz[u];i>=0;i--)
				for(int j=siz[v];j;j--)dp[u][i+j]=(dp[u][i+j]+dp[u][i]*dp[v][j]%mod*C(i+j,j))%mod;
			for(int j1=0;j1<=siz[v];j1++)
				for(int k1=0;k1<=min(j1+1,siz[v]);k1++)
				{
					memset(zc[j1][k1],0,sizeof(zc[j1][k1]));
					for(int j=0;j<=siz[u];j++)
						for(int k=0;k<=j+1;k++)
							for(int w=0;w<=min(k1,j);w++)zc[j1][k1][j+j1-w][k+k1-w]=(zc[j1][k1][j+j1-w][k+k1-w]+f[u][0][j][k]*C(j,w)%mod*C(k+k1-w,k))%mod;
				}	
			memset(f[u][0],0,sizeof(f[u][0]));
			for(int j=0;j<=siz[v];j++)
				for(int k=0;k<=j+1;k++)
					for(int j1=0;j1<=siz[u]+siz[v];j1++)
						for(int k1=0;k1<=min(siz[u]+siz[v],j1+1);k1++)
							if(zc[j][k][j1][k1])
							{
								const int w=zc[j][k][j1][k1];
								f[u][0][j1][k1]=(f[u][0][j1][k1]+f[v][0][j][k]*w)%mod;
								for(int i=lp[v];i<=rp[v];i++)f[u][i][j1][k1]=(f[u][i][j1][k1]+f[v][i][j][k]*w)%mod;
							}
			for(int i=rp[v]+1;i<=rp[u];i++)
				for(int j=siz[u]-1;j>=i-rp[v]-1;j--)
					for(int k=j+1;k>=0;k--)
					{
						const int val=f[u][i][j][k];
						f[u][i][j][k]=0;
						for(int p=0;p<=siz[v];p++)
							for(int w=0;w<=min(p,j-(i-rp[v]-1));w++)f[u][i][j+siz[v]-w][k+p-w]=(f[u][i][j+siz[v]-w][k+p-w]+dp[v][p]*val%mod*C(j-(i-rp[v]-1),w)%mod*C(k+p-w,k))%mod;
					}
			siz[u]+=siz[v];
		}
		for(int i=siz[u];i>=0;i--)dp[u][i+1]=(dp[u][i+1]+dp[u][i])%mod;
		if(u!=1)for(int j=siz[u];j>=0;j--)
			for(int k=min(j+1,siz[u]);k>=0;k--)
			{
				ll sum=0;
				for(int i=rp[u];i>=lp[u];i--)
				{
					const int w=f[u][i][j][k];
					f[u][i][j+1][k]=(f[u][i][j+1][k]+w)%mod;
					if(j==siz[u]-1)f[u][i][j+1][k+1]=(f[u][i][j+1][k+1]+w)%mod;
					f[u][i][j][k]=sum,sum=(sum+w)%mod;
				}
				const int w=f[u][0][j][k];
				f[u][lp[u]][j][k]=(f[u][lp[u]][j][k]+w)%mod,f[u][0][j+1][k]=(f[u][0][j+1][k]+w+sum)%mod;
				if(j==siz[u])f[u][0][j+1][k+1]=(f[u][0][j+1][k+1]+w)%mod,f[u][lp[u]][j][k+1]=(f[u][lp[u]][j][k+1]+w)%mod;
			}
		siz[u]++;
	}
	int main() {
		int x,y;
		n=read(),fac[0]=1;
		for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
		inv[n]=qpow(fac[n],mod-2);
		for(int i=n;i;i--)inv[i-1]=inv[i]*i%mod;
		for(int i=1;i<n;i++)
		{
			x=read(),y=read();
			if(x>y)swap(x,y);
			v[x].push_back(y);
		}
		for(int i=1;i<n;i++)sort(v[i].begin(),v[i].end()),reverse(v[i].begin(),v[i].end());
		dfs1(1),dfs2(1);
		for(int i=n;i>1;i--)printf("%lld ",f[1][i][i-2][0]);
		puts("1");
		return 0;
	}
}
int main() {
	return tokido_saya::main();
}
```

---

## 作者：251Sec (赞：3)

首先我不是旮旯批。

给定的条件相当于，对于一个序列，前面的点不能是后面的点的祖先，并且 $i$ 出现的位置 $\le n - i+1$。如果只有前一个要求那就直接树上背包。对于后面一个限制，注意到序列只有后缀最大值需要考虑它。考虑从大到小插入点，设 $f(i,j,k)$ 代表插入了 $\ge i$ 的 $j$ 个点，最后一个在序列里的位置为 $k$ 的方案数。每次插入的元素如果不是后缀最大值，则可以不考虑后一个限制，把它的一整个子树一起转移；如果是后缀最大值，那就一定是插入在末尾，发现这样不需要考虑前一个限制，直接转移就好了。

---

## 作者：Petit_Souris (赞：3)

闲话：补题的时候才发现题目背景是 Little Busters EX 笹濑川佐佐美线，赛时开题的时候根本没看见啊（虽然没想多久就被拉去做签到了），回忆起一些远古的故事。

说回题目吧，这题还是比较有意思的，但是 std 的做法实在是太麻烦了。下面讲一个高度简洁的做法，没有任何细节。

首先形式化地写出一个序列 $a$ 合法的条件：

- 没有重复元素；

- $\forall u,v$，若 $u$ 是 $v$ 的祖先，且 $u,v$ 均在 $a$ 中出现，那么 $u$ 在 $v$ 的后面。

- $\forall u$，如果 $u$ 在 $a$ 中出现，那么下标 $\le n-u+1$。

先不考虑最后一条限制，那么是一个很经典的树上背包问题。设 $h_{u,i}$ 表示 $u$ 子树中选出一个长度为 $i$ 的序列的方案数。合并子树就是 $h'_{i+j}\leftarrow h_{u,i}h_{v,j}\binom{i+j}{i}$，最后还要加入点 $u$ 的贡献，可以任意选或不选（选了就只能放在末尾）。再处理出 $g_{u,i}$ 表示必须选根的方案数。

接着考虑带上下标的限制。

先思考如何快速判断合法性。我们可以从大到小插入所有的点，如果一个点 $u$ 在插入时，没有插在序列末尾，那么必定存在 $v>u$，且 $v$ 在 $u$ 前面，此时 $v$ 的限制比 $u$ 的限制紧，所以不需要考虑 $u$。

也就是说，我们只关心所有后缀最大值的位置。

那么我们可以尝试这样 dp：设 $f_{i,j,k}$ 表示目前放好了 $[i,n]$ 的点，总共放了 $j$ 个，上一次“插入在末尾”的操作插入在 $k$ 处。

这个状态可行的原因是，无论序列长度是多少，下标都是一段前缀 $[1,j]$，这样我们可以直接通过 $j-k$ 算出前面还没放入的位置数量。

但是这样还是可能会有子树间的冲突，因此转移的设计就比较重要了：

- $i$ 不选，直接 copy 上一层，这里 $i$ 必须 $>1$。

- $i$ 是后缀最大值，那么我们可以枚举一个下标 $l\in [k+1,n-i+1]$，并把 $i$ 放在 $l$ 处。因为编号更大的不可能是祖先，所以一定合法。

- $i$ 不是后缀最大值，这时候我们不能再一个一个点转移了，因为这样祖先后代顺序就不一定对了。但是我们可以考虑直接跳一段子树。枚举这个子树中选了 $l$ 个点，且必须选根。那么我们需要在 $k-j$ 个空位中选出 $l$ 个，系数是一个组合数。

这样一个一个子树跳就完全避免了祖先后代关系的错误计算。最后答案就是 $f_{1,i,i}$。

时间复杂度 $\mathcal O(n^4)$，常数超级小，甚至不需要 dfs。

```cpp
#include<bits/stdc++.h>
#define debug(x) cerr<<(#x)<<": "<<x<<endl
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=89,Mod=998244353;
ll n,g[N][N],h[N][N],C[N][N],f[N][N][N],sz[N],tmp[N];
vector<ll>to[N];
bool Med;
int main(){
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    n=read();
    rep(i,2,n){
        ll x=read(),y=read();
        if(x>y)swap(x,y);
        to[x].push_back(y);
    }
    rep(i,0,n){
        C[i][0]=1;
        rep(j,1,i)C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
    }
    f[n+1][0][0]=1;
    per(i,n,1){
        h[i][0]=1;
        for(ll y:to[i]){
            memset(tmp,0,sizeof(tmp));
            rep(j,0,sz[i]){
                if(!h[i][j])continue;
                rep(k,0,sz[y])tmp[j+k]=(tmp[j+k]+h[i][j]*h[y][k]%Mod*C[j+k][j])%Mod;
            }
            sz[i]+=sz[y];
            rep(j,0,sz[i])h[i][j]=tmp[j];
        }
        rep(j,0,sz[i])g[i][j+1]=h[i][j];
        sz[i]++;
        per(j,sz[i],1)h[i][j]=(h[i][j]+h[i][j-1])%Mod;
        rep(j,0,n-i){
            rep(k,j,n){
                if(!f[i+1][j][k])continue;
                if(i>1)f[i][j][k]=(f[i][j][k]+f[i+1][j][k])%Mod;
                rep(l,k+1,n-i+1)f[i][j+1][l]=(f[i][j+1][l]+f[i+1][j][k])%Mod;
            }
        }
        ll tar=i+sz[i];
        rep(j,0,n-tar+1){
            rep(k,j,n){
                if(!f[tar][j][k])continue;
                rep(l,1,min(k-j,sz[i])){
                    f[i][j+l][k]=(f[i][j+l][k]+f[tar][j][k]*C[k-j][l]%Mod*g[i][l])%Mod;
                }
            }
        }
    }
    rep(i,1,n)write(f[1][i][i]),putchar(' ');
    putchar('\n');
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

