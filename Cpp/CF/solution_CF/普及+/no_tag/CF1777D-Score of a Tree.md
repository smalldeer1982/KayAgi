# Score of a Tree

## 题目描述

You are given a tree of $ n $ nodes, rooted at $ 1 $ . Every node has a value of either $ 0 $ or $ 1 $ at time $ t=0 $ .

At any integer time $ t>0 $ , the value of a node becomes the [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of the values of its children at time $ t - 1 $ ; the values of leaves become $ 0 $ since they don't have any children.

Let $ S(t) $ denote the sum of values of all nodes at time $ t $ .

Let $ F(A) $ denote the sum of $ S(t) $ across all values of $ t $ such that $ 0 \le t \le 10^{100} $ , where $ A $ is the initial assignment of $ 0 $ s and $ 1 $ s in the tree.

The task is to find the sum of $ F(A) $ for all $ 2^n $ initial configurations of $ 0 $ s and $ 1 $ s in the tree. Print the sum modulo $ 10^9+7 $ .

## 说明/提示

Let us find $ F(A) $ for the configuration $ A = [0,1,0,0,1,1] $ ( $ A[i] $ denotes the value of node $ i $ ). Initially (at $ t = 0 $ ) our tree is as shown in the picture below. In each node, two values are shown: the number and the value of this node. $ S(0) $ for this configuration is $ 3 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/10211706e57f1b1e88b0d4ddb7c1af191838660c.png)At $ t = 1 $ the configuration changes to $ [1,0,0,0,0,0] $ . The tree looks as shown below. $ S(1) = 1 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/c3bc7f260147d61f562afc931fe76e6b883432c7.png)At $ t = 2 $ the configuration changes to $ [0,0,0,0,0,0] $ . The tree looks as shown below. $ S(2) = 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1777D/fa1abea375196a437b8f0800465795a0a4b9553a.png)For all $ t>2 $ , the graph remains unchanged, so $ S(t)=0 $ for all $ t > 2 $ . So, for the initial configuration $ A = [0,1,0,0,1,1] $ , the value of $ F(A) = 3 + 1 = 4 $ .

Doing this process for all possible $ 2^{6} $ configurations yields us an answer of $ \textbf{288} $ .

## 样例 #1

### 输入

```
1
6
1 2
1 3
3 4
3 5
3 6```

### 输出

```
288```

# 题解

## 作者：yemuzhe (赞：10)

### 简化题意

- 有一颗 $n$ 个节点的数，第 $i$ 条边连接 $u _ i, v _ i$ 两个节点，每个节点刚开始的权值为 $A _ i$，$A _ i$ 等于 $0$ 或 $1$。
- 之后每过一秒，树中每个节点的权值会变成它所有子节点上一秒的权值的异或。特别地，叶子节点没有子节点，权值变为 $0$。
- 记 $S (t)$ 为第 $t$ 秒时树中的权值总和。设 $F (A)$ 为 $\sum \limits _ {t = 0} ^ {10 ^ {100}} S (t)$。
- 对于 $A$ 数组有 $2 ^ n$ 种不同的取值，对于这 $2 ^ n$ 种不同的 $A$，求 $\sum F (A)$ 对 $10 ^ 9 + 7$ 取模的值。
- 本题有 $t$ 组输入数据。$1 \le t \le 10 ^ 5, 1 \le u _ i, v _ i \le n \le 2 \cdot 10 ^ 5, \sum n \le 2 \cdot 10 ^ 5$。

### 解题思路

本题有点类似结论题，我们先推结论：

![](https://s1.ax1x.com/2023/01/23/pSJL2ND.png)

我们观察上图中根节点对 $F (A)$ 的贡献。很显然，第 $0$ 秒时根节点贡献为 $1$，第 $1$ 秒时根节点贡献为 $0 \oplus 1 = 1$。

第 $1$ 秒时，根节点的左右两个子节点的权值分别为 $1, 1$，第 $2$ 秒时根节点贡献为 $1 \oplus 1 = 0$（其中 $\oplus$ 为按位异或符号）。

而我们发现第 $0$ 秒时根节点的五个孙子节点的异或为 $0 \oplus 0 \oplus 1 \oplus 0 \oplus 1 = 0$，就是第 $2$ 秒时根节点的权值！

为什么会出现这样的情况呢？这是因为第 $1$ 秒时根节点的左子节点权值为 $0 \oplus 0 \oplus 1$，右子节点为 $0 \oplus 1$，第 $2$ 秒时根节点权值为 $(0 \oplus 0 \oplus 1) \oplus (0 \oplus 1)$。

然而异或具有结合律，$(0 \oplus 0 \oplus 1) \oplus (0 \oplus 1) = 0 \oplus 0 \oplus 1 \oplus 0 \oplus 1$。

这就说明，第 $0$ 秒时根节点的权值为它本身，第 $1$ 秒时为它所有子节点的异或，第 $2$ 秒时为它所有孙子节点的异或，第 $3$ 秒时为它所有曾孙子节点的异或……直到时间 $t$ 超过这个树的深度（根节点深度为 $0$）。

容易发现，不仅是根节点，树中的每个节点都遵循这个规律。

接下来考虑 $2 ^ n$ 种情况。对于某个节点，有一半的概率它第 $0$ 秒的权值为 $1$，有一半的概率它第 $1$ 秒的权值即它的子节点的异或为 $1$，有一半的概率它第 $2$ 秒的权值即它的孙子节点的异或为 $1$……而这一半的概率对应的是 $2 ^ {n - 1}$ 种情况。

我们如果设叶子结点为第 $1$ 层，第 $i$ 个节点为第 $s _ i$ 层且 $s _ i = \max \{s _ {ver _ {i, j}}\} + 1$，其中 $ver _ {i, j}$ 为节点 $i$ 的某个子节点。则上图例子的 $s$ 如下图所示：

![](https://s1.ax1x.com/2023/01/23/pSJO3Pe.md.png)

这说明，第 $i$ 个节点在时间 $0 \sim s _ i - 1$ 时对答案有 $2 ^ {n - 1}$ 的贡献，共有 $2 ^ {n - 1}s _ i$ 的贡献。

于是我们用树形 dp 处理出 $s _ i$，答案为 $2 ^ {n - 1} \sum s _ i$。

特别提醒：由于数据组数 $t$ 可能很大，数组初始化时不要用 `memset`。

### AC Code

```cpp
#include <cstdio>
#define maxn 200000
#define MOD 1000000007
#define N 200005
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

int T, n, x, y, tot, ans, s[N], p[N];
int head[N], nxt[N << 1], ver[N << 1];
bool v[N];

void insert (int x, int y) // 插入一条有向边 (x, y)
{
    ver[++ tot] = y, nxt[tot] = head[x], head[x] = tot;
    return ;
}

int dfs (int x)
{
    int res = 0, mx = 0; // res 为此子树内的 s[i] 之和，mx 是子节点 s[i] 的最大值
    v[x] = 1; // 此节点已经被访问过了
    for (int i = head[x], y; i; i = nxt[i])
    {
        if (v[y = ver[i]]) // 如果被访问过（即父节点）
        {
            continue;
        }
        res = (res + dfs (y)) % MOD; // 总和加上以子节点为代表的子树内的 s[i] 之和
        mx = max (mx, s[y]); // 子节点 s[i] 取 max
    }
    res = (res + (s[x] = mx + 1)) % MOD; // 等价于下面语句：
    // s[x] = mx + 1; // s[i] 为子节点 s[i] 最大值加 1
    // res = (res + s[x]) % MOD // 答案加上当前节点 s[i]
    return res;
}

int main ()
{
    scanf ("%d", &T), p[0] = 1;
    for (int i = 1; i <= maxn; i ++)
    {
        p[i] = (p[i - 1] << 1) % MOD; // 预处理 2 ^ n
    }
    while (T --)
    {
        scanf ("%d", &n), tot = 0;
        for (int i = 1; i <= n; i ++)
        {
            head[i] = v[i] = 0; // 数组初始化，不要用 memset
        }
        for (int i = 1; i < n; i ++)
        {
            scanf ("%d%d", &x, &y), insert (x, y), insert (y, x); // 插入一条无向边 (x, y)
        }
        ans = (long long) p[n - 1] * dfs (1) % MOD, printf ("%d\n", ans); // 处理并输出答案
    }
    return 0;
}
```

---

## 作者：ExplodingKonjac (赞：10)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1777D)**

卡了我半个小时，我愿称之为神仙题，这个 idea 放在 D 委屈它了。

2023.6.29 upd: 修改了对称性的构造方法。

## 题目分析

这个东西看上去很奇怪，看不出什么东西，先分析一下。记一个节点 $u$ 距离子树内叶子的最远距离为 $h_u$，那么可以发现，从第 $h_u+1$ 个时刻开始，该节点权值必然为 $0$。

然后，就什么都没有了。

接着你发现函数 $F(A)$ 具有对称性：我们发现，对于一种节点初始权值方案方案，对于一个节点 $u$，在 $[0,h_u]$ 时间内的权值，我们可以找到另一种方案，使得 $u$ 在 $[0,h_u]$ 时间内的权值和当前这个正好相反。构造很简单，让该节点子树内每一个深度都选择一个点，反转其初始权值即可。这样构造显然一一对应。

那么就好办多了，对于两种配对的方案，节点 $u$ 的贡献加起来不多不少刚好是 $h_u+1$。答案就是 $2^{n-1}\sum_u (h_u+1)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

template<int MOD>
class Modint
{
 private:
	int val;
	template<typename T> static T inverse(T a,T b)
		{ T x=0,y=1,t;for(;a;t=b/a,swap(a,b-=t*a),swap(y,x-=t*y));return x; }
	template<typename T> static T fix(T x)
		{ return (x%=MOD)<0?x+MOD:x; }
 public:
	Modint(): val(0){}
	template<typename T> Modint(const T &x): val(fix(x)){}
	inline int operator ()() { return val; }
	inline Modint &operator +=(const Modint &rhs)
		{ return (val+=rhs.val)>=MOD?val-=MOD:0,*this; }
	inline Modint &operator -=(const Modint &rhs)
		{ return (val-=rhs.val)<0?val+=MOD:0,*this; }
	inline Modint &operator *=(const Modint &rhs)
		{ return val=fix(1ll*val*rhs.val),*this; }
	inline Modint &operator /=(const Modint &rhs)
		{ return val=fix(1ll*val*inverse(rhs.val,MOD)),*this; }
	inline Modint &operator ++()
		{ return (++val)>=MOD?val-=MOD:0,*this; }
	inline Modint &operator --()
		{ return (--val)<0?val+=MOD:0,*this; }
	inline Modint operator ++(int)
		{ Modint res(*this);return ++*this,res; }
	inline Modint operator --(int)
		{ Modint res(*this);return --*this,res; }
	inline Modint operator +()
		{ return *this; }
	inline Modint operator -()
		{ return Modint(MOD-val); }
	inline Modint inv()const
		{ return Modint(inverse(val,MOD)); }
	friend inline Modint operator +(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)+=rhs; }
	friend inline Modint operator -(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)-=rhs; }
	friend inline Modint operator *(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)*=rhs; }
	friend inline Modint operator /(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)/=rhs; }
	friend inline bool operator ==(const Modint &lhs,const Modint &rhs)
		{ return lhs.val==rhs.val; }
	friend inline bool operator !=(const Modint &lhs,const Modint &rhs)
		{ return lhs.val!=rhs.val; }
	template<typename T> friend inline Modint qpow(Modint x,T y)
		{ Modint res(1);for(;y;x*=x,y>>=1)if(y&1)res*=x;return res; }
};
constexpr int MOD=1e9+7;
using Mint=Modint<MOD>;

int T,n,dep[200005];
Mint ans;
vector<int> g[200005];
void dfs(int u,int fa=0)
{
	dep[u]=1;
	for(auto &v: g[u])
	{
		if(v==fa) continue;
		dfs(v,u);
		dep[u]=max(dep[u],dep[v]+1);
	}
	ans+=dep[u];
}
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n;
		for(int i=1;i<=n;i++) g[i].clear();
		ans=0;
		for(int i=1,u,v;i<n;i++)
		{
			qin>>u>>v;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs(1);
		for(int i=1;i<n;i++) ans*=2;
		qout.writeln(ans());
	}
	return 0;
}
```


---

## 作者：NaN_HQJ2007_NaN (赞：8)

[Score of a Tree](https://www.luogu.com.cn/problem/CF1777D)

思维题。

我们考虑一个点 $u$ 在所有时刻内的点权为多少。

可以发现，假如 $u$ 的深度为 $0$，那么 $t$ 时刻时它的权值为其子树内所有深度为 $t$ 的点的初始权值异或和。

现在只考虑每个子树内相同深度的点集在 $2^n$ 种情况中的贡献。

根据异或的性质可知，当且仅当点集内有奇数个 $1$ 时才会造成贡献，而满足这种情况的方案数为 $\sum\limits_{i=1}^{cnt}[i\equiv 1\pmod 2]\dbinom{cnt}{i}$，也就是 $2^{cnt-1}$ 种。

其中 $cnt$ 为点集的大小。

为什么呢？根据二项式定理可知：

$$\sum\limits_{i=0}^{cnt}(-1)^i\cdot \dbinom{cnt}{i}=(-1+1)^{cnt}=0$$

$$\sum\limits_{i=0}^{cnt}\dbinom{cnt}{i}=(1+1)^{cnt}=2^{cnt}$$

所以 $\sum\limits_{i=1}^{cnt}[i\equiv 1\pmod 2]\dbinom{cnt}{i}=\frac{2^{cnt}-0}{2}=2^{cnt-1}$。

因此每个点集的贡献数为 $2^{cnt-1}\times 2^{n-cnt}=2^{n-1}$。

点集的个数好求，只需要把以每个子树的深度累加起来即可，即 $\sum\limits_{u}\operatorname{dep}(u)$。

最终答案为 $\left [\sum\limits_{u}\operatorname{dep}(u)\right ]\cdot 2^{n-1}$。

复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, dis[N];
vector<int> adj[N];
void dfs(int u, int lst) {
	dis[u] = 1;
	for (int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i]; if (v == lst) continue;
		dfs(v, u); dis[u] = max(dis[u], 1 + dis[v]);
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; ++i) adj[i].clear();
		ll mi = 1;
		for (int i = 1; i < n; ++i) {
			int u, v; cin >> u >> v;
			adj[u].push_back(v); adj[v].push_back(u);
			mi = mi * 2 % mod;
		}
		dfs(1, 0);
		ll x = 0;
		for (int i = 1; i <= n; ++i) x = (x + dis[i]) % mod;
		cout << mi * x % mod << endl;
	}
	return 0;
}
```

---

## 作者：2huk (赞：4)

upd：原来的代码锅了。

考虑转化成一个概率论的问题，即每个点的权 $01$ 随机，求期望点权和。这个东西再乘 $2^n$ 即答案。

显然节点 $u$ 在时刻 $t$ 时的值，是**初始所有（$u$ 子树内）距离 $u$ 为 $t$ 的点的点权异或和**。这里若 $u$ 子树内没有距离为 $t$ 的点则 $u$ 点权必为 $0$。而当这种情况发生及之后其贡献都为 $0$，也就不需要考虑了。令这种情况发生时 $t = f(u)$。不难发现 $f(u) = \max_{v \in \operatorname{son}_u}f(v)+1$。

因为所有点都是完全随机，所以我们并不注重距离 $u$ 为 $t$ 的点具体是哪些，而只需要注重**数量**。

即，令 $u$ 子树内距离 $u$ 为 $t$ 的点的数量为 $k$。[可以证明](https://www.luogu.com.cn/paste/cq094d2m)这 $k$ 个点里有奇数个点的初值为 $1$ 的概率为 $\frac 12$，即其异或和为 $1$ 的概率为 $\frac 12$。

所以这个东西和 $t$ 也无关了。也就是说，只要 $t \le f(u)$ 则点 $u$ 的期望点权为 $\frac 12$。否则期望为 $0$。

所以答案为：

$$
\sum\left( \dfrac 12 f(i)+0 \times (10^{100}-f(i))\right)=\dfrac 12 \sum f(i)
$$

别忘了再乘上 $2^n$。真正答案为 $2^{n-1}\sum f(i)$。

代码：<https://codeforces.com/contest/1777/submission/289078704>

---

## 作者：masonpop (赞：2)

思维性极强的好题。

首先发现题目定义的这些量我们一个也不会高效的求。那么只能利用对称性整体考虑了。

我们以点为单位考虑。考虑点 $x$ 在第 $t$ 秒的结果。可以发现，$x$ 在第 $t$ 秒的权值就是其 $t$ 级儿子的原始权值异或和。其中定义 $x$ 为其自身的 $0$ 级儿子。

发现这种把 $2^n$ 种树情况加起来的方法具有高度对称性。设 $x$ 的子树深度为 $dep_x$。容易发现，由于对称性，对于 $x$ 子树的第 $k$ 层（$1\leq k\leq dep_x$），其在 $2^n$ 颗树中异或和为 $0$ 和 $1$ 的情况各占 $2^{n-1}$ 种情况。那么其贡献为 $2^{n-1}$。累加其贡献可得，点 $x$ 的权值对整体的贡献就是 $2^{n-1}\times dep_x$。也可以从数学期望的角度解释。 

那么，对于整棵树 $T$ 的答案就是 $2^{n-1}\times \sum\limits_{x\in T}dep_x$。树形 $dp$ 一下即可。复杂度 $O(n)$。[代码](https://codeforces.com/contest/1777/submission/210014970)。

---

## 作者：eason1021 (赞：2)

# 题目简述
给你一个 $n$ 个结点根为 $1$ 的树。在 $t = 0$ 时，每个结点都有一个值，为 $0$ 或 $1$。

在每一个 $t > 0$ 时，每个结点的值都会变成其子结点在 $t - 1$ 时的值的异或和。

定义 $S(t)$ 为 $t$ 时所有结点值的和。

定义 $F(A)$ 为树在 $0 \le t \le 10^{100}$ 中所有 $S(t)$ 的和。其中 $A$ 为树在时刻 $0$ 时每个结点的值。

求所有 $2^n$ 个 $F(A)$ 的和。

# 思路
## 引理
引理：设 $d_i$ 为第 $i$ 个结点与其子树中结点距离的最大值。如果 $d_i > t$ 则该结点在 $t$ 时刻的值为 $0$ 。如果 $d_i \le t$ 则该结点在 $t$ 时刻是 $1$ 的几率为 $50\%$ 。

归纳证明：

在 $t = 0$ 时成立。

假设在 $t = k$ 时成立。

则在 $t = k + 1$ 时：

1.如果结点 $i$ 的任意一子结点 $u, d_u > k$ 。

$\because d_i = \max\{d_u\}+1$

$\therefore d_i > k + 1$

2.如果结点 $i$ 的子结点在 $t = k$ 时有 $j$ 个结点有 $d_u \le k$ 。

所以一共有 $2^j$ 种选取方法。异或和为 $1$ 的方案数为 $C_j^1 + C_j^3 + C_j^5 + \cdots$ 。

$\because C_j^1 + C_j^3 + C_j^5 + \cdots$

$= C_{j-1}^0+C_{j-1}^1+C_{j-1}^2+C_{j-1}^3+C_{j-1}^4+C_{j-1}^5+\cdots+C_{j-1}^{j-1}$(若 $j$ 为奇数， $C_{j-1}^j=0$ )

$=2^{j-1}$

$=2^j\times50\%$

$\therefore$ 此时结点 $i$ 为 $1$ 的概率为 $50\%$ 。

证毕

由于 $d_i \leq n \leq 2\times 10^5 \leq10^{100}$ 。

由于 $t$ 值很大，所以最后所有结点的值均为 $0$ 。

根据引理，每个结点对答案的贡献即为 $2 ^ {n - 1} \times (d_i + 1)$ 。

所以用 DFS 来求 $d_i$ 即可。

# 代码
```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
const int N = 2E5 + 5, M = 1E9 + 7;
int n, t;
int u, v;
long long tmp = 0; 
vector<int> G[N];
long long dfs(int u, int f) {
	long long ans = 1;
	for (int v : G[u]) {
		if (v == f) continue;
		ans = max(ans, dfs(v, u) + 1);
	}
	tmp += ans;
	tmp %= M;
	return ans;
}
int main()
{
	cin >> t;
	while (t--) {
		cin >> n;
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i < n; i++) {
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		long long ans = 1;
		for (int i = 1; i < n; i++) {
			ans *= 2;
			ans %= M;
		}
		tmp = 0;
		dfs(1, 0);
		ans = ans * tmp;
		ans %= M;
		cout << ans << ' ';
	}
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1777D 题解



## 思路分析

注意到第 $i$ 个点在第 $j$ 秒的值 $a_{i,j}$ 实际上是 $i$ 的子树中深度为 $dep_i+j$ 的点的点权异或和，设这样的点有 $k$ 个。

那么我们知道，$a_{i,j}=1$ 的情况共有 $C_1=\sum_{d=0}^k [d\bmod 2=1]\times\binom dk$ 种，而 $a_{i,j}=0$ 的情况共有 $C_0=\sum_{d=0}^k[d\bmod 2=0]\times \binom dk$ 种。

而根据组合数学的基本结论，$\forall k\in \mathbb{Z^+}:C_0=C_1$，证明如下：

> 根据二项式定理，有如下的推导：
>
> $$
> \begin{aligned}
> C_0+C_1
> &=\sum_{d=0}^k \binom kd\\
> &=\sum_{d=0}^k 1^{d}\times 1^{k-d}\times \binom dk\\
> &=(1+1)^{k}=2^k\\[3ex]
> C_0-C_1&=\sum_{d=0}^k (-1)^d\times \binom kd\\
> &=\sum_{d=0}^k (-1)^d\times 1^{k-d}\times \binom kd\\
> &=[(-1)+1]^k=0
> \end{aligned}
> $$
>
> 因此 $C_0=C_1=2^{k-1}$，证明完毕。

因此，每个节点在任何时刻为 $0$ 或 $1$ 的概率是均等的，假如 $i$ 的子树中有深度为 $dep_i+j$ 的点，那么其在时刻 $j$ 对答案的贡献是 $2^{n-1}$。

因此树形 dp 维护一下每个点的最长链大小即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+1,MOD=1e9+7;
inline int ksm(int a,int b,int m=MOD) {
	int ret=1;
	while(b) {
		if(b&1) ret=ret*a%m;
		a=a*a%m;
		b=b>>1;
	}
	return ret;
}
vector <int> G[MAXN];
int dp[MAXN];
inline void dfs(int p,int f) {
	for(int v:G[p]) {
		if(v==f) continue;
		dfs(v,p);
		dp[p]=max(dp[p],dp[v]+1);
	}
}
inline void solve() {
	int n
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) G[i].clear(),dp[i]=1;
	for(int i=1;i<n;++i) {
		int u,v;
		scanf("%lld%lld",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	int ans=0;
	for(int i=1;i<=n;++i) ans=(ans+dp[i]%MOD)%MOD;
	printf("%lld\n",ans*ksm(2,n-1)%MOD);
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：yyz1005 (赞：0)

第一眼把子节点看成了子树，有点若至在里面的。

应当注意到在 $t=k$ 时，节点 $x$ 的值是其 $k$ 级子孙在 $t=0$ 时的异或和，如果其无 $k$ 级子孙，则为 $0$。

我们记节点 $x$ 第 $k$ 级子孙的异或和期望为 $P_{x,k}$。

那么节点 $x$ 在 $2^n$ 种情况中对 $\sum F(A)$ 的贡献为 $\sum\limits_{k = 1}^{+\infty}P_{x,k}$。

而对于节点 $x$ 的每一层子孙，只要该层非空，那么该层的异或和为 $1$ 或 $0$ 的概率应当是均为 $\dfrac{1}{2}$。

我们考虑从下往上的定义点 $x$ 的层数 $s_x = \max\{1,s_v+1\}$，其中 $v$ 是 $x$ 的子节点。

那么 $\sum\limits_{k = 1}^{+\infty}P_{x,k} = \sum\limits_{k = 1}^{s_x}\dfrac{1}{2} = \dfrac{s_x}{2}$。

综上，$\sum F(A) = 2^n \times \sum{\dfrac{s_x}{2}} = 2^{n-1}\sum s_x$。

做完了。

[Code](https://codeforces.com/contest/1777/submission/261732569)

---

