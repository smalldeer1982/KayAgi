# [NOI Online #2 提高组] 游戏

## 题目背景

1s 512M

## 题目描述

小 A 和小 B 正在玩一个游戏：有一棵包含 $n=2m$ 个点的有根树（点从 $1\sim n$ 编号），它的根是 $1$ 号点，初始时两人各拥有 $m$ 个点。游戏的每个回合两人都需要选出一个自己拥有且之前未被选过的点，若对手的点在自己的点的子树内，则该回合自己获胜；若自己的点在对方的点的子树内，该回合自己失败；其他情况视为平局。游戏共进行 $m$ 回合。

作为旁观者的你只想知道，在他们随机选点的情况下，第一次非平局回合出现时的回合数的期望值。

为了计算这个期望，你决定对于 $k=0,1,2,\cdots,m$，计算出非平局回合数为 $k$ 的情况数。两种情况不同当且仅当存在一个小 A 拥有的点 $x$，小 B 在 $x$ 被小 A 选择的那个回合所选择的点不同。

由于情况总数可能很大，你只需要输出答案对 $998244353$ 取模后的结果。

## 说明/提示

| 测试点编号 | $n =$ | 特殊性质 |
| :-- | :-- | :-- |
| 1 $\sim$ 4 | $20$ | 无 |
| 5 $\sim$ 8 | $50$ | 无 |
| 9 $\sim$ 10 | $300$ | 树退化为一条链 |
| 11 $\sim$ 12 | $300$ | 无 |
| 13 $\sim$ 14 | $500$ | 无 |
| 15 $\sim$ 16 | $5000$ | 树退化为一条链 |
| 17 $\sim$ 20 | $5000$ | 无 |

## 样例 #1

### 输入

```
8
10010011
1 2
1 3
2 4
2 5
5 6
3 7
3 8```

### 输出

```
0
10
10
4
0
```

# 题解

## 作者：yijan (赞：44)

由于 Latex 挂了，建议到 Luogu 博客或者 [这里](https://www.yijan.co/noiol-t3-match/) 查看。

我们记 “恰好有 $k$ 次非平局” 的方案数是 $g(k)$ ，“钦定有 $k$ 次非平局” 的方案数是 $f(k)$ 。发现这是一个二项式反演的形式，由二项式反演有公式：（不会可以百度）
$$
f(n)=\sum\limits_{i=n}^m{i\choose n}g(i)\Leftrightarrow g(n)=\sum\limits_{i=n}^m(-1)^{i-n}{i\choose n}f(i)
$$
所以我们只要求出 $f(k)$ 就做完了这个题。我们可以 dp 求出 $f$ ，设 $dp[u][x]$ 表示 $u$ 子树内钦定选择了 $x$ 对点，这 $x$ 对点均呈 祖先 - 子孙 的关系（也就是这 $x$ 局钦定会比出胜负）。于是发现这东西可以直接树形背包算。

转移就是正常的树形背包，最后还需要考虑钦定这个点和某个后代的情况，这种情况的转移就是从子树内未被钦定的点中选择一个点。

然后我交上去的代码多输出了个 $0$ 考试的时候没看到 /kk

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 5006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
#define P 998244353
int n;
int A[MAXN];

int head[MAXN] , to[MAXN << 1] , nex[MAXN << 1] , ecn;
void ade( int u , int v ) {
    to[++ ecn] = v , nex[ecn] = head[u] , head[u] = ecn;
}

int dp[MAXN][MAXN] , siz[MAXN] , sz[MAXN];
int pd[MAXN];
void dfs( int u , int fa ) {
    siz[u] = 1 , sz[u] = A[u];
    dp[u][0] = 1;
    for( int i = head[u] , v ; i ; i = nex[i] ) {
        v = to[i];
        if( v == fa ) continue;
        dfs( v , u );
        rep( k , 0 , siz[u] + siz[v] ) pd[k] = 0;
        rep( j , 0 , min( siz[u] , n / 2 ) ) if( dp[u][j] )
            rep( k , 0 , min( siz[v] , n / 2 - j ) ) if( dp[v][k] )
                pd[j + k] = ( pd[j + k] + dp[u][j] * 1ll * dp[v][k] % P ) % P;
        rep( k , 0 , siz[u] + siz[v] ) dp[u][k] = pd[k];
        siz[u] += siz[v] , sz[u] += sz[v];
    }
    per( i , min( sz[u] , siz[u] - sz[u] ) , 1 ) dp[u][i] = ( dp[u][i] + dp[u][i - 1] * 1ll * ( ( A[u] ? ( siz[u] - sz[u] ) : ( sz[u] ) ) - ( i - 1 ) ) % P ) % P;
}

int J[MAXN] , iJ[MAXN];
int Pow( int x , int a ) {
    int ret = 1;
    while( a ) {
        if( a & 1 ) ret = 1ll * ret * x % P;
        x = 1ll * x * x % P , a >>= 1;
    }
    return ret;
}
int C( int a , int b ) {
    return J[a] * 1ll * iJ[b] % P * iJ[a - b] % P;
}

void solve() {
    cin >> n;
    J[0] = iJ[0] = 1;
    rep( i , 1 , MAXN - 1 ) J[i] = J[i - 1] * 1ll * i % P , iJ[i] = Pow( J[i] , P - 2 );
    rep( i , 1 , n )
        scanf("%1d",A + i);
    int u , v;
    rep( i , 2 , n ) scanf("%d%d",&u,&v) , ade( u , v ) , ade( v , u );
    dfs( 1 , 1 );
    int re = 0;
    rep( i , 0 , n / 2 + 1 ) dp[1][i] = dp[1][i] * 1ll * J[n / 2 - i] % P;
    rep( i , 0 , n / 2 ) {
        re = 0;
        rep( j , i , n / 2 )
            re += C( j , i ) * 1ll * ( ( j - i & 1 ) ? P - 1 : 1 ) % P * dp[1][j] % P , re %= P;
        printf("%d ",re);
    }
}

signed main() {
//    freopen("match.in","r",stdin);
//    freopen("match.out","w",stdout);
//    int T;cin >> T;while( T-- ) solve();
    solve();
}


```





---

## 作者：Daniel_yuan (赞：25)

不知道怎么公式渲染炸了……可能是不支持两个美元的公式吧（已尽力修改）……可以手动进入[博客](https://www.luogu.com.cn/blog/wageneral/solution-p6478)看看。（造成的不便敬请谅解）

先安利一个二项式反演的公式：

$g(k)=\sum_{i=k}^nC_i^k\cdot f(i)$ 等价于 $f(i)=\sum_{k=i}^n(-1)^{k-i}\cdot C_k^i\cdot g(k)$

**注：十分抱歉，这个公式之前是错的，请注意右侧 $(-1)$ 的指数是 $(k-i)$，与 $n$ 是无关的，实际上这里的 $n$ 是可以枚举到正无穷的。**

不会证明，但是会用就行。

这个题先设 $f[i][j]$ 表示 $i$ 子树内，非平局对为 $j$ 对的方案数。

考虑怎么转移，先不考虑 $i$，只考虑它的子树，那么方案数就是

$f[i][j]=\sum_{k_1+k_2+...+k_n=j} f[son_1][k_1]\times f[son_2][k_2] \times...\times f[son_n][k_n]$

直接枚举显然不行，考虑每遍历一棵子树就把答案并进去，那么就是 $f[i][j+k]=\sum_{son}f[son][j]\times f[i][k]$ 。

这个式子乍一看是 $n^3$ 的，但是如果卡 $j,k$ 的上界就会变成 $n^2$，粗略的证明是每个点对 $(x,y)$ 只会在 $\text{LCA}(x,y)$ 有一个复杂度的贡献。具体的证明可以问问百度。（我也不记得是什么时候看到过这个东西了）

最后的时候再把 $i$ 个贡献加进去，分别设 $A[i],B[i]$ 为 $i$ 子树内小 A/B 的节点个数，假设当前节点是小 A 的节点，那么就有 $f[i][j]=f[i][j]+f[i][j-1]\times \max((B[i]-(j-1),0)$ 。即之前有 $j-1$ 个非平局对，那么就会消耗掉 $j-1$ 个小 B 的节点，所以现在还剩 $B[i]-(j-1)$ 个小 B 的节点可用。类似的，如果当前的节点是小 B 的节点就把上文的 $B$ 换成 $A$ 即可。

至此我们就可以在 $n^2$ 的时间复杂度内算出所有子树内选 $k$ 个非平局对的方案数。

我们先设 $G(k)=f[1][k]\times (\frac{n}{2}-k)!$，也就是说先固定选出来的 $k$ 个非平局对，然后把剩下的自由组合。

但是这样子会算重，因为自由组合也可能贡献非平局对。我们设 $H(i)$ 表示恰好有 $i$ 个非平局对的方案数，可以发现对于每个 $H(i)$，它对 $G(k)$ 的贡献是 $C_i^k\times H(i)$。

举个栗子，假设 $i=4,k=3$ 设这 $i$ 个非平局对的编号为 $1,2,3,4$，那么就有可能 $1,2,3$ 被计算在 $f[1][k]$ 内，$4$ 是自由组合出来的；也可能是 $1,2,4$ 被计算在 $f[1][k]$ 内，$3$ 是自由组合出来的……即一共有 $C_i^k$ 种情况。

那么我们就有 $G(k)=\sum_{i=k}^m C_i^k\cdot H(i) $，回到一开始提到的二项式反演，套进去就可以计算得到 $H(i)$ 。

不太会证明为什么可以这样，我只能通过这种套式子的方法来做，而且我认为 $G(k)$ 是没有实际含义的，只是一个用来反演的工具。（毕竟说它是至少 $k$ 个非平局对过于牵强，因为单拿恰好 $k+1$ 个非平局对来看，就会被算进去 $k+1$ 次）

代码如下：~~考场代码求轻喷~~

```cpp
#include <bits/stdc++.h>
#define RI register int
typedef long long LL;
#define int LL

#define FILEIO(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

using namespace std;

int const mod = 998244353, MAXN = 5005;
int f[MAXN][MAXN], g[MAXN];
int A[MAXN], B[MAXN];
char s[MAXN];
struct Edges { int to, next; } e[MAXN * 2];
int head[MAXN], tot;
int size[MAXN];
int frac[MAXN], invfrac[MAXN], inv[MAXN];

inline LL C(int n, int m) { return frac[n] * invfrac[m] % mod * invfrac[n - m] % mod; }

void Init(int Max) {
  frac[0] = invfrac[0] = 1;
  frac[1] = invfrac[1] = inv[1] = 1;
  for (RI i = 2; i <= Max; ++i) {
    frac[i] = frac[i - 1] * i % mod;
    inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    invfrac[i] = invfrac[i - 1] * inv[i] % mod;
  }
}

inline void addedge(int from, int to) {
  e[++tot] = (Edges){to, head[from]};
  head[from] = tot;
  e[++tot] = (Edges){from, head[to]};
  head[to] = tot;
}

void Dfs(int now, int fa) {
  if (s[now] == '0') ++A[now];
  else ++B[now];
  for (RI i = head[now]; i; i = e[i].next)
    if (e[i].to != fa) {
      Dfs(e[i].to, now);
      A[now] += A[e[i].to];
      B[now] += B[e[i].to];
    }
}

void Solve(int now, int fa) {
  size[now] = 0;
  f[now][0] = 1;
  for (RI i = head[now]; i; i = e[i].next)
    if (e[i].to != fa) {
      Solve(e[i].to, now);
      for (RI j = 0; j <= size[now] + size[e[i].to]; ++j) g[j] = 0;
      
      for (RI j = 0; j <= size[now]; ++j)
        for (RI k = 0; k <= size[e[i].to]; ++k)
          g[j + k] = (g[j + k] + f[now][j] * f[e[i].to][k] % mod) % mod;
      
      size[now] += size[e[i].to];
      for (RI j = 0; j <= size[now]; ++j)
        f[now][j] = g[j];
    }
  
  if (s[now] == '0') {
    for (RI i = size[now]; i >= 0; --i)
      if (B[now] - i > 0)
        f[now][i + 1] = (f[now][i + 1] + f[now][i] * (B[now] - i) % mod) % mod;
    if (f[now][size[now] + 1]) ++size[now];
  }
  else {
    for (RI i = size[now]; i >= 0; --i)
      if (A[now] - i > 0)
        f[now][i + 1] = (f[now][i + 1] + f[now][i] * (A[now] - i) % mod) % mod;
    if (f[now][size[now] + 1]) ++size[now];
  }
}

signed main() {
  
  FILEIO("match");

  ios :: sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int n; cin >> n; Init(n);
  cin >> (s + 1);
  for (RI i = 1, x, y; i < n; ++i)
    cin >> x >> y, addedge(x, y);
  Dfs(1, 0);
  Solve(1, 0);
  for (RI i = 0; i <= size[1]; ++i)
    g[i] = f[1][i] * frac[n / 2 - i] % mod;
  for (RI i = 0; i <= n / 2; ++i) {
    int Ans = 0;
    for (RI j = i, op = 1; j <= size[1]; ++j, op = op * (mod - 1) % mod)
      Ans = (Ans + op * C(j, i) % mod * g[j] % mod) % mod;
    cout << Ans << " ";
  }
  cout << endl;

  return 0;
}

// created by Daniel yuan

```


---

## 作者：GaryH (赞：16)

# P6478 题解

可能巨佬们都觉得树形背包的时间复杂度分析太简单了，

~~（只有我想了若干小时还很晕）~~

好像都没写或者只是点了一句话，那我就来补充一下。

**题意：**

给定一棵点数为 $n=2m$ 的有根树，每个点有 $0,1$ 两种边权。

现在要为每一个权为 $0$ 的点找一个权为 $1$ 的点与之配对，并对每个 $k \in [0,\frac {n}{2}]$，

求出恰有 $k$ 对点的关系是祖先和后代的配对方案数。

**做法：**

我们记 $f_k$ 为恰有 $k$ 对点的关系是祖先和后代的配对方案数，

记 $g_k$ 为钦定 $k$ 对点的关系是祖先和后代的配对方案数，

那么我们有：$g_k= \sum\limits_{i=k}^{m}\dbinom{i}{k}f_i$，式子的含义是：

先枚举一共有多少对祖先-后代点对，再枚举在这些点对中，我们钦定的是哪 $k$ 对点。

我们发现，这个式子是一个二项式反演的经典形式，故我们有：

$f_k=\sum\limits_{i=k}^{m}\dbinom{i}{k}(-1)^{i-k}g_i$，至于二项式反演的证明我就不讲了，相信大家也都会。

也就是说，我们将问题转化为了，对于每个 $k \in [0,\frac {n}{2}]$，

求出钦定 $k$ 对点的关系是祖先和后代的配对方案数。

这个问题就很好解决了，我们可以使用树上背包解决。具体来说，就是：

设 $f_{u,i}$ 为子树 $u$ 中选择了 $i$ 对祖先-后代点对的方案数，则我们有一个显然的转移：

$f_{u,i}=\sum\limits_{v,j\le i} f_{v,j}f_{u,i-j}$，代表在子树 $v$ 中选择 $j$ 对祖先-后代点，其余的在子树 $u$ 其他部位选。

当然，我们还可以在子树 $u$ 内选择一个点与 $u$ 配对，即：

$f_{u,i}=f_{u,i-1}+siz_{u,1-col_u}$，其中 $col_u$ 代表点 $u$ 属于谁，$siz_{u,c}$ 代表子树 $u$ 中 $col$ 值为 $c$ 的点数。

注意这里需要倒序枚举 $i$，因为点 $u$ 只能被配对一次，故应该做 $01$ 背包。

看上去这个做法是立方级别的做法，但实际上并不是，我们可以把复杂度的式子写下来。

先记 $son_{u,x}$ 为 $u$ 的第 $x$ 个子节点，以及 $s(u)$ 为子树 $u$ 的大小，则我们有：

$T(n)=\sum\limits_{u}\sum\limits_{v=son_{u,i}}((\sum\limits_{j=1}^{i-1}s(son_{u,j})) \times s(v))$.

我们可以将上式理解成，在枚举到 $u$ 和 $u$ 的第 $i$ 个儿子 $v$ 时，对于 $u$ 的所有已经枚举过的儿子，

这些点以及它们子树中的所有点构成了一个点集 $V$；

而我们正在进行的这一次枚举，会对时间复杂度造成 $|V| \times s(v)$ 的贡献，

并将点 $v$ 和 $v$ 的子树中所有点合并进点集 $V$ 中。

我们考虑拆开贡献计算，具体来说，是：

因为每次枚举时，任一点集 $V$ 中的点 $p$，和任一点 $v$ 及其子树中的点 $q$，

都会对上面时间复杂度中的 $|V| \times s(v)$ 造成值为 $1$ 的贡献。

又因为 $p$ 和 $q$ 在树上的最近公共祖先必然是 $u$，也就是说，在这次枚举之前，

我们一定没有枚举到过 $u,v$，故这是点对 $p,q$ 第一次造成贡献，

但我们在枚举完 $u,v$ 后，会把点 $v$ 和 $v$ 的子树中所有点合并进点集 $V$ 中，

那么这也是是点对 $p,q$ 最后一次造成贡献，因为点集 $V$ 不会分裂，

且任意同属于点集 $V$ 中的两点不会造成贡献。

以上证明说明了，对 $\forall u,v \in [1,n]$，点对 $u,v$ 只会对时间复杂度造成一次值为 $1$ 的贡献。

也就是说，最后时间复杂度只会被累加 $O(n^2)$ 次，即 $T(n)=O(n^2)$.

**code：**

```
#include<bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define int long long
#define pii pair < int , int >
#define swap(u, v) u ^= v, v ^= u, u ^= v
#define ckmax(a, b) ((a) = max((a), (b)))
#define ckmin(a, b) ((a) = min((a), (b)))
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define per(i, a, b) for (int i = (a); i >= (b); i--)
#define edg(i, v, u) for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

using namespace std;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') f = ch == '-' ? -1 : 1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}

const int N (5e3 + 10);
const int mod (998244353);

void add (int &x, int y) { x = (x + y) % mod; }

int ksm (int a, int b) {
	int r = 1;
	for (; b; a = a * a % mod, b >>= 1) if (b & 1) r = r * a % mod;
	return r;
}

int n;
int cnt;
int g[N];
char s[N];
int fac[N];
int inv[N];
int head[N];
int f[N][N];
int siz[N][2];

struct Edge { int to, nxt; } e[N << 1];

void adde (int u, int v) {
	e[++cnt] = (Edge) {v, head[u]}, head[u] = cnt;
}

int Siz (int x) { return siz[x][0] + siz[x][1]; }

int C (int bi, int sm) {
	return fac[bi] * inv[sm] % mod * inv[bi - sm] % mod;
}

void dfs (int u, int fa) {
	f[u][0] = 1;
	rep (c, 0, 1) siz[u][c] = (s[u] == ('0' + c));
	edg (pth, v, u) if (v ^ fa) {
		dfs (v, u); int Su = Siz(u), Sv = Siz(v);
		rep (i, 0, Su + Sv) g[i] = 0;
		rep (i, 0, min (Su, n / 2)) rep (j, 0, min (Sv, n / 2 - i))
		  add (g[i + j], f[v][j] * f[u][i] % mod);
		rep (i, 0, Su + Sv) f[u][i] = g[i];
		rep (c, 0, 1) siz[u][c] += siz[v][c];
	}
	per (i, min (siz[u][0], siz[u][1]), 1) {
		int x = ((s[u] == '1') ? siz[u][0] : siz[u][1]) - (i - 1);
		add (f[u][i], f[u][i - 1] * x % mod);
	}
}

signed main() {
	n = read(), cin >> (s + 1);
	rep (i, 2, n) {
		int u = read(), v = read();
		adde (u, v), adde (v, u);
	}
	fac[0] = inv[0] = 1;
	rep (i, 1, n + 2) fac[i] = fac[i - 1] * i % mod, 
					  inv[i] = ksm (fac[i], mod - 2);
	dfs (1, 0);
	rep (k, 0, n / 2 + 1) (f[1][k] *= fac[n / 2 - k]) %= mod;
	rep (k, 0, n / 2) {
		int res = 0, sgn = mod - 1;
		rep (i, k, n / 2) {
			int tmp = C (i, k) * ((i - k & 1) ? mod - 1 : 1) % mod;
			res = (res + tmp * f[1][i] % mod) % mod;
		}
		cout << res << endl;
	}
	return 0;
}
```



---

## 作者：StudyingFather (赞：7)

**恰好**这个词看上去比较头疼，考虑大力容斥一下。

我们设 $f(i)$ 表示**存在** $i$ 回合分出平局的方案数，$g(i)$ 表示**恰好** $i$ 回合分出平局的方案数，显然有：

$$
f(i)=\sum_{k=i}^m \binom{k}{i} g(k)
$$

由二项式反演可知，

$$
g(i)=\sum_{k=i}^m (-1)^{k-i} \binom{k}{i} f(k)
$$

考虑把 $f(i)$ 求出来。

设 $f(i,j)$ 表示以 $i$ 为根的子树中，**存在** $j$ 对祖先 - 后代关系，且颜色不同的点对。

有两种转移：

- 子树内的结果合并，树形背包跑一下就行。
- 根节点与未被选的一个点配对，这个在子树合并后跑一遍就行。

```cpp
// Problem: P6478 [NOI Online #2 提高组]游戏（民间数据）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6478
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <vector>
#define MOD 998244353
using namespace std;
vector<int> e[5005];
char s[5005];
int siz[5005],siz1[5005],n;
long long f[5005][5005],g[5005],fr[5005];
int c[5005][5005];
void dfs(int u,int fa)
{
 siz[u]=1,siz1[u]=(s[u]-'0');
 f[u][0]=1;
 for(auto v:e[u])
 {
  if(v==fa)continue;
  dfs(v,u);
  for(int i=0;i<=siz[u]+siz[v];i++)
   g[i]=0;
  for(int i=0;i<=min(siz[u],n/2);i++)//树形背包合并结果
   for(int j=0;j<=min(siz[v],n/2-i);j++)
    g[i+j]=(g[i+j]+f[u][i]*f[v][j])%MOD;
  for(int i=0;i<=siz[u]+siz[v];i++)
   f[u][i]=g[i];
  siz[u]+=siz[v],siz1[u]+=siz1[v];
 }
 for(int i=min(siz1[u],siz[u]-siz1[u]);i;i--)//根节点与子树内某个未被选的点配对
  if(s[u]=='1')
   f[u][i]=(f[u][i]+f[u][i-1]*(siz[u]-siz1[u]-(i-1)))%MOD;
  else
   f[u][i]=(f[u][i]+f[u][i-1]*(siz1[u]-(i-1)))%MOD;
}
int main()
{
 cin>>n;
 cin>>(s+1);
 fr[0]=1;
 for(int i=1;i<=n;i++)
  fr[i]=fr[i-1]*i%MOD,c[i][0]=1;
 c[0][0]=1;
 for(int i=1;i<=n;i++)
  for(int j=1;j<=i;j++)
   c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
 for(int i=1;i<n;i++)
 {
  int u,v;
  cin>>u>>v;
  e[u].push_back(v);
  e[v].push_back(u);
 }
 dfs(1,0);
 for(int i=0;i<=n/2;i++)
  f[1][i]=f[1][i]*fr[n/2-i]%MOD;
 for(int i=0;i<=n/2;i++)
 {
  long long ans=0;
  for(int j=i;j<=n/2;j++)//二项式反演
   if((j-i)&1)ans=(ans-c[j][i]*f[1][j]%MOD+MOD)%MOD;
   else ans=(ans+c[j][i]*f[1][j])%MOD;
  cout<<ans<<endl;
 }
 return 0;
}

---

## 作者：tzc_wk (赞：6)

UPD：题面传送错了/gg/gg

[题面传送门](https://www.luogu.com.cn/problem/P6478)

没错这就是我 boom0 的[那场 NOIOL](https://www.cnblogs.com/ET2006/p/12775259.html) 的 T3

~~一年前，我在 NOIOL #2 的赛场上折戟沉沙，一年后，我从倒下的地方爬起。~~

~~我成功了，我不再是从前那个我了~~

我们首先假设 A 拥有的点为 $p_1,p_2,\cdots,p_m$，B 拥有的点为 $q_1,q_2,\cdots,q_m$，显然 A、B 出牌的顺序是无关紧要的，因此我们不妨假设 A 就按 $p_1,p_2,\cdots,p_m$ 的顺序出牌，题目就等价于有多少个 $q$ 的排列 $r$ 满足恰好存在 $k$ 对 $(p_i,r_i)$ 是祖先关系。

其次，注意到这个“恰好”非常难受，因为它既包含匹配也包含不匹配的情况，而这两种情况是很难在一起考虑的。

这时候我们就可以很自然地想到一个套路叫“二项式反演”，我们考虑**任意钦定 $k$ 对必须匹配的点**，即记 $f_k$ 为钦定 $k$ 对必须匹配的点，剩余随便排列的方案数，再记 $g_k$ 为恰好存在 $k$ 对 $(p_i,r_i)$ 是祖先关系的方案数。那么有 $f_k=\sum\limits_{i=k}\dbinom{i}{k}g_i$，反演以下即可 $g_k=\sum\limits_{i=k}\dbinom{i}{k}(-1)^{i-k}f_i$。

接下来考虑怎样求 $f_i$，这显然是一个简单的树形背包问题，设 $dp_{u,j}$ 表示 $u$ 的子树内钦定了 $j$ 对要匹配的点的方案数。考虑转移，我们首先按照树形背包的套路将 $u$ 所有子树的 $dp$ 值合并起来，合并完之后的 $dp_{u,j}$ 的显然就是在 $u$ 所有儿子的子树中钦定 $j$ 对需匹配的点的方案数，此时我们还需再考虑 $u$ 的匹配情况，如果 $u$ 属于 A，那么我们令 $dp_{u,j+1}\leftarrow dp_{u,j}\times(c1_u-j)$，其中 $c1_u$ 表示 $u$ 子树内有多少个点属于 B，$u$ 属于 B 的情况也同理，注意，这里的 $j$ 需要倒序枚举。最终 $f_k=dp_{1,k}\times(\dfrac{n}{2}-k)!$。

时间复杂度 $\mathcal O(n^2)$

~~总之当时觉得这道题是道 dlt，现在看来，也就 just so so 罢（~~

```cpp
const int MAXN=5e3;
const int MOD=998244353;
char s[MAXN+5];
int n,c0[MAXN+5],c1[MAXN+5],dp[MAXN+5][MAXN+5];
int hd[MAXN+5],to[MAXN*2+10],nxt[MAXN*2+10],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int tmp[MAXN+5];
void dfs(int x,int f){
	dp[x][0]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];if(y==f) continue;dfs(y,x);
		memset(tmp,0,sizeof(tmp));
		for(int u=0;u<=min(c0[x],c1[x]);u++)
			for(int v=0;v<=min(c0[y],c1[y]);v++){
				tmp[u+v]=(tmp[u+v]+1ll*dp[x][u]*dp[y][v])%MOD;
			}
		c0[x]+=c0[y];c1[x]+=c1[y];
		for(int u=0;u<=min(c0[x],c1[x]);u++) dp[x][u]=tmp[u];
	}
	if(s[x]=='0'){
		for(int u=min(c0[x],c1[x]);~u;u--){
			dp[x][u+1]=(dp[x][u+1]+1ll*dp[x][u]*(c1[x]-u))%MOD;
		} c0[x]++;
	} else {
		for(int u=min(c0[x],c1[x]);~u;u--){
			dp[x][u+1]=(dp[x][u+1]+1ll*dp[x][u]*(c0[x]-u))%MOD;
		} c1[x]++;
	}
//	for(int u=0;u<=min(c0[x],c1[x]);u++) printf("%d %d %d\n",x,u,dp[x][u]);
}
int fac[MAXN+5],ifac[MAXN+5];
void init_fac(int n){
	for(int i=(fac[0]=ifac[0]=ifac[1]=1)+1;i<=n;i++) ifac[i]=1ll*ifac[MOD%i]*(MOD-MOD/i)%MOD;
	for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=1ll*ifac[i-1]*ifac[i]%MOD;
}
int binom(int n,int k){return 1ll*fac[n]*ifac[k]%MOD*ifac[n-k]%MOD;}
int f[MAXN+5],g[MAXN+5];
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=1,u,v;i<n;i++) scanf("%d%d",&u,&v),adde(u,v),adde(v,u);
	dfs(1,0);init_fac(n);
	for(int i=0;i<=n/2;i++) f[i]=1ll*fac[n/2-i]*dp[1][i]%MOD;
	for(int i=0;i<=n/2;i++){
		for(int j=i;j<=n/2;j++){
			if((j-i)&1) g[i]=(g[i]-1ll*binom(j,i)*f[j]%MOD+MOD)%MOD;
			else g[i]=(g[i]+1ll*binom(j,i)*f[j])%MOD;
		} printf("%d\n",g[i]);
	}
	return 0;
}
```



---

## 作者：_lbw_ (赞：5)

先看P1595

我们把数据范围开到 $n\leq114514$

我们先设 $f(n,k)$ 为**刚好** $k$ 个点**在**原来的位置上，答案为 $f(n,0)$

再设 $g(n,k)$ 为**钦定** $k$ 个点**在**原来的位置上，其他随意排，显然，$g(n,k)=\dbinom{n}{k}(n-k)!=n!/k!$

发现 $g(n,k)=\sum\limits_{i=k}^{}\dbinom{i}{k}f(n,i)$

使用二项式反演

$f(n,k)=\sum\limits_{i=k}^{}(-1)^{i-k}\dbinom{i}{k}g(n,i)=\sum\limits_{i=k}^{}(-1)^{i-k}\dbinom{i}{k}\dfrac{n!}{i!}$

$ans=f(n,0)=n!\sum\limits_{i=0}^{}\dfrac{(-1)^{i}}{i!}$

结束

P6478

发现刚好不会做，使用上题套路，那么就设**钦定** $k$ 个点是 $f(n,k)$，刚好 $k$ 个点是 $g(n,k)$

同上题，反演得$f(n,k)=\sum\limits_{i=k}^{}(-1)^{i-k}\dbinom{i}{k}g(n,i)$

然后 $f(n,k)$ 很好求，用背包+子树大小优化一下

考虑自己的转移，直接跑一遍

跑出来的 $f(1,k)$ 扔进去反演一下就得到了 $g(1,k)$

[代码](https://www.luogu.com.cn/paste/2nz8fq72)

---

## 作者：木xx木大 (赞：4)

[P6478 [NOI Online #2 提高组]游戏](https://www.luogu.com.cn/problem/P6478)

“恰好”的方案数不好求，我们对这个问题进行转化：设 $f_i$ 表示非平局回合数恰好为 $i$ 的方案数，  $g_i$ 表示非平局回合数至少为 $i$ 的方案数。根据二项式反演（广义容斥），
$$
g_i=\sum_{j=i}^{m}\tbinom{j}{i}f_j\Rightarrow f_i=\sum_{j=i}^{m}(-1)^{j-i}\tbinom{j}{i}g_j
$$
那么我们可以在 $O(n^2 )$ 的时间内把 $g$ 转化为 $f$。接下来考虑如何求 $g$。

设 $dp_{u,i}$ 表示在 $u$ 子树内非平局回合数至少为 $i$ （即选 $ i$ 对有“祖孙关系”的点对）的方案数。转移时，每遍历一棵子树就把答案并进去 $dp_{u,j+k}=\sum_{v\in son_u}dp_{u,j}\times dp_{v,k}$，然后再考虑 $u$ 和其子树内一点配对的情况 。根据树形背包的复杂度分析，这个转移的复杂度是 $O(n^2)$ 的。

求出 $dp$ 数组后，有 $g_i=dp_{1,k}\times(m-k)!$，也就是在已选的 $k$ 个点对以外，其他的自由组合。最后直接套二项式反演的式子求 $f$ 即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
namespace FGF
{
	int n,m;
	const int N=5005;
	const int mo=998244353;
	char s[N]; 
	struct edg{
		int to,nxt;
	}e[N<<1];
	int cnt,head[N],siz[N],sz[2][N],a[N];
	ll dp[N][N],tmp[N],fac[N],g[N],f[N],C[N][N];
	void add(int u,int v)
	{
		cnt++;
		e[cnt].to=v;
		e[cnt].nxt=head[u];
		head[u]=cnt;
	}
	void dfs(int u,int fa)
	{
		siz[u]=1,sz[a[u]][u]=1,dp[u][0]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(v==fa)continue;
			dfs(v,u);
			for(int j=0;j<=min(siz[u]+siz[v],m);j++)tmp[j]=0;
			for(int j=0;j<=min(siz[u],m);j++)
				for(int k=0;k<=min(siz[v],m-j);k++)
					tmp[j+k]=(tmp[j+k]+dp[u][j]*dp[v][k]%mo)%mo;
			siz[u]+=siz[v];
			sz[0][u]+=sz[0][v],sz[1][u]+=sz[1][v];
			for(int j=0;j<=min(siz[u],m);j++)dp[u][j]=tmp[j];
		}
		for(int i=sz[a[u]^1][u];i>=0;i--)
			dp[u][i+1]=(dp[u][i+1]+dp[u][i]*(sz[a[u]^1][u]-i)%mo)%mo;
	}
	void init()
	{
		for(int i=0;i<=n;i++)
		{
			C[i][0]=1;
			for(int j=1;j<=i;j++)
				C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
		}
		fac[0]=1;
		for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mo;
	}
	void work()
	{
		scanf("%d",&n);m=n>>1;
		scanf("%s",s+1);
		for(int i=1;i<=n;i++)a[i]=s[i]-'0';
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			add(u,v),add(v,u); 
		}
		dfs(1,0);
		init();
		for(int i=0;i<=m;i++)g[i]=dp[1][i]*fac[m-i]%mo;
		for(int i=0;i<=m;i++)
			for(int j=i;j<=m;j++)
				if((j-i)&1)f[i]=(f[i]-C[j][i]*g[j]%mo+mo)%mo;
					else f[i]=(f[i]+C[j][i]*g[j]%mo)%mo;		
		for(int i=0;i<=m;i++)
			printf("%lld\n",f[i]);
	}
}
int main()
{
	FGF::work();
	return 0;
}
```

---

## 作者：I_am_Accepted (赞：1)

树形背包 + 二项式反演 好题。

**注意这道题判情况不同的方法，回合之间交换顺序算同一种情况。**

发现「非平局回合」等价于两人选的点存在祖孙关系。

我们设 $f(i)$ 表示**恰好**有 $i$ 局非平局的方案数（也就是我们最终的答案），设 $g(i)$ 表示**钦定**有 $i$ 局非平局的方案数

当作您会了二项式反演，这里不再赘述**钦定**和**至少**的区别了。

由定义得到
$$
g(i)=\sum_{j=i}^m\binom{j}{i}f(j)
$$
二项式反演
$$
f(i)=\sum_{j=i}^m(-1)^{j-i}\binom{j}{i}g(j)
$$
也就是说我们只要求出 $g(0),g(1),\dots,g(m)$ 即可。

设 $dp^{(1)}_i$ 表示树上选择 $i$ 对祖孙关系异色点的方案数（点对之间顺序无关）。

我们有
$$
g(i)=(m-i)!dp^{(1)}_i
$$
接下来压力转到 $dp^{(1)}$。显然是树形背包。（因为 $^{(1)}$ 根节点角标都标好了）

背包转移时，我们先类似普通背包，再计算子树根节点能和子树内多少点配对。

记得用刷表法。

```cpp
//We'll be counting stars.
//#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=(j),i##_=(k);i<=i##_;i++)
#define Rof(i,j,k) for(int i=(j),i##_=(k);i>=i##_;i--)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define Fi(s) freopen(s,"r",stdin)
#define Fo(s) freopen(s,"w",stdout)
#define Fre(s) Fi(s".in"),Fo(s".out")
#define debug cerr<<"Line#"<<__LINE__<<endl
#define ll long long
const ll mod=998244353;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
#define int long long
#define N 5006
char c[N];
int dp[N][N/2],s0[N],s1[N],lim[N],n,f[N/2],ivf[N/2];
vector<int> e[N];
void dfs(int rt,int fa){
	s1[rt]=c[rt]-'0';
	s0[rt]=s1[rt]^1;
	dp[rt][0]=1;
	for(int i:e[rt]) if(i!=fa){
		dfs(i,rt);
		s0[rt]+=s0[i];
		s1[rt]+=s1[i];
		Rof(j,lim[rt],0) For(k,1,lim[i]) (dp[rt][j+k]+=dp[rt][j]*dp[i][k]%mod)%=mod;
		lim[rt]+=lim[i];
	}
	int lst=(c[rt]=='0'?s1[rt]:s0[rt]);
	Rof(i,lim[rt],0) (dp[rt][i+1]+=dp[rt][i]*max(0ll,lst-i)%mod)%=mod;
	lim[rt]++;
	while(!dp[rt][lim[rt]]) lim[rt]--;
}
inline int P(int x){return (x&1)?mod-1:1;}
inline int C(int x,int y){return f[x]*ivf[y]%mod*ivf[x-y]%mod;}
int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>(c+1);
	int x,y,m=n/2;
	f[0]=1; For(i,1,m) f[i]=f[i-1]*i%mod;
	ivf[m]=pw(f[m],mod-2); Rof(i,m,1) ivf[i-1]=ivf[i]*i%mod;
	For(i,1,n-1){
		cin>>x>>y;
		e[x].pb(y);
		e[y].pb(x);
	}
	dfs(1,0);
//	For(i,0,lim[1]) cout<<dp[1][i]<<" "; cout<<endl;
	int ans;
	For(i,0,m){
		ans=0;
		For(j,i,m) (ans+=P(i+j)*C(j,i)%mod*dp[1][j]%mod*f[m-j]%mod)%=mod;
		cout<<ans<<endl;
	}
return 0;}
```

---

## 作者：Resurgammm (赞：1)

看见 **恰好** 这种词的话可以考虑用二项式反演来大力容斥。

**注：下文推式子的 $n,m$ 与题意并不符。**

设 $f_m$ 为恰好 $m$ 局非平局的方案数，$g_m$ 为至少 $m$ 局非平局的方案数。

则对于任意的 $i\geq m$，$f_i$ 在 $g_m$ 中被计算了 $\binom{i}{m}$ 次，故有：

$$g_m=\sum\limits_{i=m}^{n}\binom{i}{m}f_i$$

然后二项式反演一波，有：

$$f_m=\sum_{i=m}^{n}(-1)^{i-m}\binom{i}{m}g_i$$

考虑求出 $g$。

设 $dp_{u,i}$ 为在以 $u$ 为根的子树中，有 $i$ 个祖先-后代非同一方关系对的方案数。

注意题中的去重条件类似于组合的意味，那么可以对一方排序，对另一方排列，有：

$$g_i=dp_{1,i}\times (m-i)!$$

按照树形背包的套路可以先把子树都合并起来，有：

$$dp_{u,j+k}=\sum_{v\in son_u}\sum_{j=0}^{m}\sum_{k=0}^{m-j} dp_{v,j}\times dp_{v,k}$$

再考虑 $u$ 点自身的贡献，有：

$$dp_{u,i+1}=dp_{u,i}\times (c_u-i)$$

其中 $c_u$ 是 $u$ 子树内与 $u$ 所属相反方的点的数量。

用子树大小卡一下上界能把复杂度降到 $O(n^2)$。

$\texttt{Code:}$

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rint register int
#define int long long
using namespace std;
namespace IO{
	#define File(x,y) freopen(#x,"r",stdin),freopen(#y,"w",stdout)
	inline int read(){
		int w=0,f=1; char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
		while(ch>='0'&&ch<='9'){w=(w<<3)+(w<<1)+(ch^48); ch=getchar();}
		return w*f;
	}
	inline void write(int x){
  		static int sta[35]; int top=0;
  		if(x<0) putchar('-'),x=-x;
  		do{sta[++top]=x%10,x/=10;}while(x);
  		while(top) putchar(sta[top--]+48); puts("");
	}
}
using namespace IO;
namespace CL{
	#define fill(x,y) memset(x,y,sizeof(x))
	#define copy(x,y) memcpy(x,y,sizeof(y))
	
	const int maxn=5e3+5,mod=998244353;
	
	int n,m;
	int a[maxn],dp[maxn][maxn],g[maxn],f[maxn],size[maxn],siz[maxn][2],tmp[maxn];
	char s[maxn];
	namespace Graph{
		int head[maxn],id;
		struct e{int v,next;}edge[maxn<<1];
		inline void add(int u,int v){
			edge[++id].v=v;
			edge[id].next=head[u];
			head[u]=id;
		}
	}using namespace Graph;
	namespace Math{
		int fac[maxn];
		inline void init(){
			fac[0]=1;
			for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
		}
		inline int qpow(int x,int y){
			int res=1; x%=mod;
			while(y){
				if(y&1) res=res*x%mod;
				x=x*x%mod;
				y>>=1;
			}
			return res;
		}
		inline int C(int n,int m){
			if(n<m || m<0) return 0;
			return fac[n]*qpow(fac[m]*fac[n-m],mod-2)%mod;
		}
	}using namespace Math;
	void dfs(int u,int fa){
		size[u]=siz[u][a[u]]=dp[u][0]=1;
		for(int i=head[u];i;i=edge[i].next){
			int v=edge[i].v;
			if(v==fa) continue;
			dfs(v,u);
			for(int j=0;j<=min(size[u]+size[v],m);j++) tmp[j]=0;
			for(int j=0;j<=min(size[u],m);j++)
				for(int k=0;k<=min(size[v],m-j);k++)
					tmp[j+k]=(tmp[j+k]+dp[u][j]*dp[v][k]%mod)%mod;
			size[u]+=size[v];
			siz[u][0]+=siz[v][0],siz[u][1]+=siz[v][1];
			for(int j=0;j<=min(size[u],m);j++) dp[u][j]=tmp[j];
		}
		for(int i=siz[u][a[u]^1];i>=0;i--)
			dp[u][i+1]=(dp[u][i+1]+dp[u][i]*(siz[u][a[u]^1]-i)%mod)%mod;
	}
	
	inline int main(){
		n=read(); m=n>>1; init();
		scanf("%s",s+1);
		for(int i=1;i<=n;i++) a[i]=(s[i]=='1');
		for(int i=1;i<n;i++){
			int x=read(),y=read();
			add(x,y); add(y,x);
		}
		dfs(1,0);
		for(int i=0;i<=m;i++) g[i]=dp[1][i]*fac[m-i]%mod;
		for(int i=0;i<=m;i++)
			for(int j=i;j<=m;j++){
				if((j-i)&1) f[i]=(f[i]-C(j,i)*g[j]%mod+mod)%mod;
				else f[i]=(f[i]+C(j,i)*g[j]%mod)%mod;
			}
		for(int i=0;i<=m;i++) printf("%lld\n",f[i]);
		return 0;
	}
}
signed main(){return CL::main();}
```

---

## 作者：chenzida (赞：1)

$\text{NOI online round2 T3}$ ，去年看是神仙题，到了今年~~依然是神仙题~~。

主要是最近刚学二项式反演，于是来练练手。

这种题也是有套路的，看到“恰好为 $k$”，发现自己不会做，于是考虑先钦定 $k$ 个非平局的场次，然后进行二项式反演。

所以我们就将这题转化为了，至少有 $k$ 个非平局的场次的情况数。~~发现自己仍然不会做~~

既然是树上问题，考虑 $f[i][j]$ 表示以 $i$ 为根的子树中钦定了 $j$ 个非平局的场次，那么可以得到 $f$ 的转移式子：

$$f_{i,j}=\sum_{k_1+k_2+...+k_m=j}\prod_{t=1}^m f_{son_t,k_t}$$

然后发现这个式子就是一个经典的树形背包的式子，直接考虑每一棵子树取几就好了。

但是一般树形背包看起来是 $n^3$ 的，如果想要变成 $n^2$ 只用先做，在把 $siz$ 加上即可。

但是那个式子不足以推出答案，因为还有一个重要的东西，那就是没有考虑 $i$ 的贡献，然后我们记录一下一棵子树中有多少个和 $i$ 颜色相反的结点，然后统计答案即可。

最后记录下来钦定 $k$ 场的方案数，直接反演即可。

只放重要部分的代码了，分部是 $dfs$ 进行树上背包的部分以及二项式反演的部分。

```
void dfs(int x,int fa_)
{
	siz[a[x]][x]=1;dp[x][0]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];if(y==fa_)continue;dfs(y,x);
		int lim=min(siz[0][x]+siz[0][y],siz[1][x]+siz[1][y]);
		for(int j=0;j<=lim;j++)f[j]=0;
		for(int j=0;j<=min(siz[0][x],siz[1][x]);j++)for(int k=0;k<=min(siz[0][y],siz[1][y]);k++)
			if(j+k<=lim)f[j+k]=(f[j+k]+dp[x][j]*dp[y][k]%mod)%mod;
		for(int j=0;j<=lim;j++)dp[x][j]=f[j];
		for(int j=0;j<=1;j++)siz[j][x]+=siz[j][y];
	}
	for(int j=0;j<=min(siz[0][x],siz[1][x]);j++)f[j]=dp[x][j];
	for(int j=1;j<=min(siz[0][x],siz[1][x]);j++)dp[x][j]=(f[j-1]*max(0ll,siz[a[x]^1][x]-j+1)%mod+f[j])%mod;
	if(x==1)for(int j=0;j<=n/2;j++)F[j]=dp[x][j];
}
```

```
for(int i=0;i<=n/2;i++)
{
	int ans=0,now=1;
	for(int j=i;j<=n/2;j++)
	{
		ans=(ans+now*F[j]*fac[n/2-j]%mod*C(i,j)%mod)%mod;
		now=now*-1;ans=(ans%mod+mod)%mod;
	}
	printf("%lld\n",ans);
}
```

---

## 作者：kouylan (赞：0)

看到题面问 “恰好”，自然的想到容斥或者二项式反演。这里我们使用二项式反演。

设 $f(k)$ 表示存在 $k$ 个胜负局的方案数，$g(k)$ 表示恰好 $k$ 个胜负局的方案数。那么 $f(k)=\sum\limits_{i=k}^n\binom{i}{k}g(i) \Leftrightarrow g(k)=\sum\limits_{i=k}^n(-1)^{i-k}\binom{i}{k}f(i)$。我们要求的就是 $g$。

所以我们主要任务是求 $f$，想到用树上背包。

设 $f(x,j)$ 表示 $x$ 为根的子树内选出 $j$ 对胜负点的方案数。转移有两种情况，第一是子树之间合并，第二是 $x$ 点跟子树内的点配对，这在子树合并后做一次就行。

最后，每一个 $f(1,j)$ 要乘上 $(n/2-j)!$，因为选点有先后关系。

下面是 AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 998244353ll;

int n,a[5005],g[5005],f[5005][5005],f1[5005];
int ee,h[5005],nex[5005<<1],to[5005<<1];
int siz[5005][3],c[5005][5005],fac[5005];

void addedge(int x,int y)
{
	nex[++ee] = h[x], to[ee] = y, h[x] = ee;
}

void dfs(int x,int pre)
{
	siz[x][a[x]] = siz[x][2] = 1;
	f[x][0] = 1;
	for(int i=h[x];i;i=nex[i])
		if(to[i]!=pre)
		{
			dfs(to[i],x);
			int y=to[i];
			for(int j=0;j<=siz[x][2]+siz[y][2];j++)
				f1[j] = 0;
			for(int j=0;j<=min(siz[x][2],n/2);j++)
				for(int k=0;k<=min(siz[y][2],n/2);k++)
					f1[j+k] = (f1[j+k]+f[x][j]*f[y][k])%M;
			for(int j=0;j<=siz[x][2]+siz[y][2];j++)
				f[x][j] = f1[j];
			siz[x][0] += siz[y][0], siz[x][1] += siz[y][1], siz[x][2] += siz[y][2];
		}
	if(a[x]==0)
	{
		for(int j=min(siz[x][0],siz[x][1]);j>=1;j--)
			f[x][j] = (f[x][j]+f[x][j-1]*(siz[x][1]-(j-1)))%M;
	}
	if(a[x]==1)
	{
		for(int j=min(siz[x][0],siz[x][1]);j>=1;j--)
			f[x][j] = (f[x][j]+f[x][j-1]*(siz[x][0]-(j-1)))%M;
	}
}

signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char ch;
		cin>>ch;
		a[i] = ch-'0';
	}
	for(int i=1,x,y;i<n&&cin>>x>>y;i++)
		addedge(x,y), addedge(y,x);
	for(int i=0;i<=n;i++)
		c[i][0] = 1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			c[i][j] = (c[i-1][j-1]+c[i-1][j])%M;
	fac[0] = 1;
	for(int i=1;i<=n;i++)
		fac[i] = fac[i-1]*i%M;
	dfs(1,0);
	for(int i=0;i<=n/2;i++)
		f[1][i] = f[1][i]*fac[n/2-i]%M;
	for(int k=0;k<=n/2;k++)
	{
		for(int i=k;i<=n/2;i++)
		{
			if((i-k)%2==0)
				g[k] = (g[k]+c[i][k]*f[1][i]%M+M)%M;
			else
				g[k] = (g[k]-c[i][k]*f[1][i]%M+M)%M;
		}
	}
	for(int i=0;i<=n/2;i++)
		cout<<g[i]<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

