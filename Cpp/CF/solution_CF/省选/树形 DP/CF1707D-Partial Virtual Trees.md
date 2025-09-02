# Partial Virtual Trees

## 题目描述

Kawashiro Nitori is a girl who loves competitive programming. One day she found a rooted tree consisting of $ n $ vertices. The root is vertex $ 1 $ . As an advanced problem setter, she quickly thought of a problem.

Kawashiro Nitori has a vertex set $ U=\{1,2,\ldots,n\} $ . She's going to play a game with the tree and the set. In each operation, she will choose a vertex set $ T $ , where $ T $ is a partial virtual tree of $ U $ , and change $ U $ into $ T $ .

A vertex set $ S_1 $ is a partial virtual tree of a vertex set $ S_2 $ , if $ S_1 $ is a subset of $ S_2 $ , $ S_1 \neq S_2 $ , and for all pairs of vertices $ i $ and $ j $ in $ S_1 $ , $ \operatorname{LCA}(i,j) $ is in $ S_1 $ , where $ \operatorname{LCA}(x,y) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ x $ and $ y $ on the tree. Note that a vertex set can have many different partial virtual trees.

Kawashiro Nitori wants to know for each possible $ k $ , if she performs the operation exactly $ k $ times, in how many ways she can make $ U=\{1\} $ in the end? Two ways are considered different if there exists an integer $ z $ ( $ 1 \le z \le k $ ) such that after $ z $ operations the sets $ U $ are different.

Since the answer could be very large, you need to find it modulo $ p $ . It's guaranteed that $ p $ is a prime number.

## 说明/提示

In the first test case, when $ k=1 $ , the only possible way is:

1. $ \{1,2,3,4\} \to \{1\} $ .

When $ k=2 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,3\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,4\} \to \{1\} $ .

When $ k=3 $ , there are $ 6 $ possible ways:

1. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,2\} \to \{1\} $ ;
2. $ \{1,2,3,4\} \to \{1,2,3\} \to \{1,3\} \to \{1\} $ ;
3. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,2\} \to \{1\} $ ;
4. $ \{1,2,3,4\} \to \{1,2,4\} \to \{1,4\} \to \{1\} $ ;
5. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,3\} \to \{1\} $ ;
6. $ \{1,2,3,4\} \to \{1,3,4\} \to \{1,4\} \to \{1\} $ .

## 样例 #1

### 输入

```
4 998244353
1 2
2 3
1 4```

### 输出

```
1 6 6```

## 样例 #2

### 输入

```
7 100000007
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
1 47 340 854 880 320```

## 样例 #3

### 输入

```
8 1000000007
1 2
2 3
3 4
4 5
5 6
6 7
7 8```

### 输出

```
1 126 1806 8400 16800 15120 5040```

# 题解

## 作者：Alex_Wei (赞：30)

> [CF1707D Partial Virtual Trees](https://codeforces.com/contest/1707/problem/D)

注意到 $S_1 \neq S_2$ 的限制很烦人，考虑容斥掉。

具体地，令 $G(i)$ 表示答案，$F(i)$ 表示用 $i$ 步使得 $U = \{1\}$ 且不要求相邻两个 $U$ 不等的方案数。

考虑 $F(i)$，枚举哪几步满足 $U$ 不等，可知 $F(i) = \sum\limits_{j = 1} ^ i \dbinom i j G(j)$，即从 $i$ 步中选出 $j$ 步不等，剩下来所有步 $U$ 相等，后者方案唯一，故总方案数为 $\dbinom i j G(j)$。

显然的二项式反演形式，可知 $G(i) = \sum\limits_{j = 1} ^ i (-1) ^ {i - j} \dbinom i j F(j)$，因此只需求出 $F(j)$。

回顾虚树的性质：称一个点被点亮当且仅当它为虚树关键点，若 $u$ 的两棵子树 $x, y$ 均存在节点被点亮，则 $u$ 必须点亮。

笔者一开始想设 $f_{i, k}$ 表示 $i$ 子树内恰好在第 $k$ 步变为 $\{i\}$，发现无法封闭转移。换一种定义方式，设 $f_{i, j}$ 表示 $i$ 子树直到第 $j$ 个时刻还有被点亮的点的方案数。

考虑转移，分 $i$ 在第 $k$ 时刻仍点亮和未点亮两种情况。对于前者，容易发现只要每个子树内合法，$i$ 子树内必然合法，故
$$
f_{i, k} \gets \prod\limits_{u\in son(i)}\sum\limits_{j = 0} ^ k f_{u, j}
$$
容易前缀和优化至 $\mathcal{O}(n ^ 2)$，设 $s_i$ 为 $f_i$ 的前缀和。

对于后者，枚举 $i$ 在第 $p$ 时刻至第 $p + 1$ 时刻被熄灭，则在 $p + 1$ 时刻到 $k$ 时刻 **有且仅有** $i$ 的一个儿子子树被点亮。据此，有转移式
$$
f_{i, k} \gets \sum\limits_{p = 0} ^ {k - 1} \sum\limits_{u\in son(i)} f_{u, k} \prod\limits_{v\in son(i) \land v\neq u} s_{v, p}
$$
改变求和顺序，预处理前后缀积从而预处理 $g_{u, p} = \prod\limits_{v \in son(i) \land v \neq u} s_{v, p}$，对它做一遍前缀和，那就是
$$
f_{i, k} \gets  \sum\limits_{u\in son(i)} f_{u, k} g_{u, k - 1}
$$
同样 $\mathcal{O}(n ^ 2)$ 做，最后 $\mathcal{O}(n ^ 2)$ 做一遍二项式反演即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e3 + 5;
int n, mod, f[N][N], s[N][N], g[N][N];
int F[N], C[N][N];
vector<int> e[N], son[N];
void dfs(int id, int ff) {
	f[id][0] = s[id][0] = 1;
	for(int it : e[id]) {
		if(it == ff) continue;
		son[id].push_back(it);
		dfs(it, id);
	}
	for(int k = 0; k <= n; k++) {
		int prod = 1;
		for(int it : son[id]) prod = 1ll * prod * s[it][k] % mod;
		static int pre[N], suf[N];
		int L = son[id].size();
		pre[0] = suf[L + 1] = 1;
		for(int i = 1; i <= L; i++) {
			pre[i] = 1ll * pre[i - 1] * s[son[id][i - 1]][k] % mod;
		}
		for(int i = L; i; i--) {
			suf[i] = 1ll * suf[i + 1] * s[son[id][i - 1]][k] % mod;
			g[son[id][i - 1]][k] = 1ll * pre[i - 1] * suf[i + 1] % mod;
		}
	}
	for(int it : son[id]) 
		for(int k = 1; k <= n; k++)
			add(g[it][k], g[it][k - 1]);
	for(int k = 1; k <= n; k++) {
		int prod = 1;
		for(int it : son[id]) prod = 1ll * prod * s[it][k] % mod;
		add(f[id][k], prod);
		for(int it : son[id]) {
			int coef = f[it][k];
			coef = 1ll * coef * g[it][k - 1] % mod;
			add(f[id][k], coef);
		}
	}
	for(int i = 1; i <= n; i++) {
		s[id][i] = s[id][i - 1];
		add(s[id][i], f[id][i]);
	}
}
void solve() {
	cin >> n >> mod;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= i; j++) {
			if(!j) C[i][j] = 1;
			else C[i][j] = C[i - 1][j - 1], add(C[i][j], C[i - 1][j]);
		}
	for(int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	for(int i = 1; i < n; i++) {
		F[i] = 1;
		for(int it : son[1]) F[i] = 1ll * F[i] * s[it][i - 1] % mod;
	}
	for(int i = 1; i < n; i++) {
		int ans = 0;
		for(int j = 1; j <= i; j++) {
			int coef = 1ll * C[i][j] * F[j] % mod;
			if(i - j & 1) add(ans, mod - coef);
			else add(ans, coef);
		}
		cout << ans << " ";
	}
	cout << endl;
}
int main() {
	int T = 1;
	while(T--) solve();
	return 0;
}
```

---

## 作者：Tyyyyyy (赞：10)

## CF1707D

### 题意简述
给定一棵以 $1$ 为根的有根树，你有一个集合 $S=\{1,2,\dots,n\}$。你可以对于这个集合进行如下操作：

- 选择一个集合 $T$，满足 $T\subsetneq S$，且 $T$ 关于 $\operatorname{lca}$ 运算封闭。

- 令 $S\gets T$。

请对于 $k=1\sim n-1$ 求出：有多少种方式，使得恰好操作 $k$ 次之后，$S=\{1\}$？

$1\leq n\leq 2000$。

### 题目分析
发现 $T$ 是 $S$ 的真子集这一点非常讨厌，我们考虑把这个限制去掉，换成 $T$ 是 $S$ 的子集。设此时求出的答案为 $f_i$，原答案为 $ans_i$，那么有：

$$f_i=\sum_{j=0}^i\binom{i}{j}ans_j$$

这是因为我们考虑在 $i$ 次转化后的操作中，钦定 $j$ 次使得 $T$ 是 $S$ 的真子集，那么可以得到上式。

移项一下有

$$ans_i=f_i-\sum_{j=0}^{i-1}\binom{i}{j}ans_j$$

也就是说我们现在只要求出 $f_i$ 即可。

考虑简化 ”关于 $\operatorname{lca}$ 运算封闭“ 这个条件。不难发现它等价于：

- 若某个节点 $u$ 存在两个子节点 $x,y$，满足以 $x,y$ 为根的子树各自至少有一个点还未被删除，那么 $u$ 不能被删除。

也就是说，每个节点 $u$ 子树被删除的顺序只有两种可能：

- 以 $u$ 的所有子节点为根的子树被删除，然后 $u$ 被删除。

- 除 $u$ 的某个子节点 $v$ 的子树未被删除之外，其余子节点的子树均被删除，然后 $u$ 被删除，然后 $v$ 的子树被删除。

此时容易设计出一个 dp 状态：$f_{u,i}$ 表示 $u$ 节点的子树在恰好 $i$ 次操作之后被删完的方案数。讨论上述两种情况，枚举 $u$ 被删除的时间和留下的子节点 $v$，容易用前缀和优化到 $O(n^2)$。

求出答案后，用 $f_{1,i}$ 还原出 $ans_i$ 即可。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010;
int n,mod,tot,h[N],fac[N],inv[N];
struct edge
{
	int v,nxt;
}e[N<<1];
void add(int u,int v)
{
	e[++tot]=(edge){v,h[u]};
	h[u]=tot;
}
int power(int x,int y)
{
	int t=1;
	while(y)
	{
		if(y&1)t=1ll*t*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return t;
}
int f[N][N],s[N][N],pre[N][N],suf[N][N],sum[N];
void dfs(int u,int fa)
{
	vector<int>son;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa)continue;
		dfs(v,u),son.push_back(v);
	}
	if(son.empty())
	{
		for(int i=1;i<n;i++)f[u][i]=1,s[u][i]=i;
		return;
	}
	for(int j=0;j<(int)son.size();j++)
		for(int i=1;i<n;i++)pre[i][j+1]=suf[i][j+1]=s[son[j]][i];
	for(int i=1;i<n;i++)
	{
		pre[i][0]=suf[i][son.size()+1]=1;
		for(int j=0;j<(int)son.size();j++)pre[i][j+1]=1ll*pre[i][j+1]*pre[i][j]%mod;
		for(int j=son.size()-1;j>=0;j--)suf[i][j+1]=1ll*suf[i][j+1]*suf[i][j+2]%mod;
		f[u][i]=pre[i][son.size()];
	}
	if(u==1)return;
	for(int i=1;i<n;i++)
	{
		for(int j=0,v=son[0];j<(int)son.size();j++,v=son[j])
			f[u][i]=(f[u][i]+1ll*f[v][i]*sum[v])%mod,
			sum[v]=(sum[v]+1ll*pre[i][j]*suf[i][j+2])%mod;
		s[u][i]=(s[u][i-1]+f[u][i])%mod;
	}
}
int ans[N];
int C(int n,int m)
{
	return n<0||m<0||n<m?0:1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main()
{
	scanf("%lld%lld",&n,&mod);
	for(int i=1,x,y;i<n;i++)
		scanf("%lld%lld",&x,&y),add(x,y),add(y,x);
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++)fac[i]=1ll*fac[i-1]*i%mod,inv[i]=power(fac[i],mod-2);	
	dfs(1,0);
	for(int i=1;i<n;i++)
	{
		ans[i]=f[1][i];
		for(int j=0;j<i;j++)ans[i]=(ans[i]-1ll*C(i,j)*ans[j]%mod+mod)%mod;
		printf("%lld ",ans[i]);
	}
	return 0;
}
```

---

## 作者：RyexAwl (赞：8)

### 简要题意

给定一棵 $n$ 个点的树，初始时集合 $U=\{1,2,3,...,n\}$，每次操作如下：

* 选取 $T\subseteq U$ 且 $T\ne U$。

* $\forall i,j\in T$，满足 $\mathrm{LCA}(i,j)\in T$。

* 令 $U\gets T$。

对于 $1\le k\le n-1$ 计算出有多少种不同的操作方案数使得进行恰好 $k$ 次操作后 $U=\{1\}$。

$2\le n\le 2000$。

### 题解

对于限制 $\forall i,j\in T$，满足 $\mathrm{LCA}(i,j)\in T$，等价于对于任意点 $u$，如果点 $u$ 存在两个儿子 $v_1,v_2$ 满足 $v_1$ 的子树中存在点在 $T$ 中且 $v_2$ 的子树中存在点在 $T$ 中，那么 $u$ 一定在 $T$ 中。

考虑如何枚举一种操作方案。如果进行了 $k$ 次操作 $U\to T_1\to T_2\to ...\to T_k$，每次操作保留了上次操作结果的一个子集，将其看成删除了上次操作结果的一个子集。

那么考虑枚举每个点被删除的时刻 $t_i$，表示点 $i$ 在第 $t_i$ 次操作中被“删除”，即 $\forall j<t_i$，$i\in T_j$，其可以和一组 $U\to T_1\to T_2\to ...\to T_k$ 且 $T_i\subseteq T_{i-1}$ 的操作建立双射。并且我们可以很好的刻画第二个限制。

对于第二个限制，令 $p_u$ 表示 $u$ 子树内的最大的 $t$，其可以等价于对于任意点 $u$ 至多存在一个儿子 $v$ 满足 $p_v>t_u$。

但是对于 $T\ne U$，或者说 $T_i\ne T_{i-1}$ 的限制通过枚举删除时刻并不可以很好的刻画。

这里考虑将 $T\ne U$ 的限制容斥掉，令 $f(m)$ 表示不考虑 $T\ne U$ 的限制时经过 $m$ 次操作将 $U$ 操作为 $\{1\}$ 的方案数，$g(m)$ 表示考虑 $T=U$ 的限制时经过 $m$ 次操作将 $U$ 操作为 $\{1\}$ 的方案数。这里通过组合意义建立 $f(m)$ 与 $g(m)$ 的关系，考虑枚举不考虑 $T\ne U$ 的方案中满足 $T\ne U$ 的操作步骤：

$$
f(m)=\sum_{i=1}^m\binom{m}{i}g(i)
$$

因为 $g(0)=0$，根据二项式反演：

$$
f(m)=\sum_{i=0}^m\binom{m}{i}g(i)\Leftrightarrow g(m)=\sum_{i=0}^m(-1)^{m-i}\binom{m}{i}f(i)
$$

考虑通过 DP 枚举 $t_i$，其中 $2\le i\le n$（因为点 $1$ 用不删除），那么对于一组固定的 $t_i$ 我们不难得出其对应的操作方案的操作次数为 $\max\limits_{i=2}^n(t_i)$。

并且对于任意点 $u$ 至多有一个儿子 $v$ 满足 $p_v>t_u$ 的限制我们可以分为两类看，如果 $t_u\ge \max\limits_{v\in son(u)}(p_v)$，那么我们只需要知道 $\max\limits_{v\in son(u)}(p_v)$，如果存在一个儿子 $v$ 满足 $p_v>t_u$，那么可以考虑枚举这个儿子，而其他的所有儿子我们只在意其中的 $\max(p)$。

这提示我们设计如下状态：$f[u,i]$ 表示考虑以 $u$ 为根的子树，$u$ 子树内的最大的 $t$ 恰好为 $i$ 的合法的 $t$（即对于任意点 $u$ 至多存在一个儿子 $v$ 满足 $p_v>t_u$）。当然这个状态定义在 $u=1$ 时需要稍作变通，这里不展开讨论。

对于转移，首先计算出：

$$
F[u,i]=\prod_{v\in son(u)}\sum_{1\le j\le i}f[v,j]
$$

令 $s[u,i]=\sum\limits_{1\le j\le i}f[u,j]$。

即 $F[u,i]$ 表示考虑 $u$ 的所有儿子的子树 $\max(t)\le i$ 的方案数。

如果 $t_u\ge \max\limits_{v\in son(u)}(p_v)$，那么枚举 $t_u=i$：

$$
f[u,i]\gets F[u,i]
$$

如果存在一个 $v\in son(u)$ 满足 $p_v>t_u$，那么考虑枚举 $v$ 以及 $p_v=i$：

$$
f[u,i]\gets \sum_{j<i}\frac{F[u,j]}{s[v,j]}\times f[v,i]
$$

对于 $\sum\limits_{j<i}\frac{F[u,j]}{s[v,j]}$ 的维护可以在从小到大枚举 $i$ 的时动态维护。

复杂度 $O(n^2)$。注意求 $\frac{F[u,j]}{s[v,j]}$ 不能使用单次 $O(\log V)$ 的求逆元，会 TLE 11。维护前后缀贡献即可。

```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 2005;

int n,mod,f[N][N],F[N][N],s[N][N],c[N][N],pre[N][N],suf[N][N];

std::vector<int> G[N];

void dfs(int x,int fa) {
    int cnt = 0; rep(j,1,n-1) F[x][j] = 1;
    for (auto v : G[x]) {
        if (v == fa) continue;
        dfs(v,x); ++ cnt; 
        rep(j,1,n-1) {
            pre[v][j] = F[x][j];
            F[x][j] = 1ll * F[x][j] * s[v][j] % mod;
        }
    }
    if (cnt == 0) {
        rep(i,1,n-1) f[x][i] = 1,s[x][i] = i;
        return;
    }
    if (x == 1) return;
    rep(i,1,n-1) {
        f[x][i] = F[x][i];
    }
    rep(j,1,n-1) F[x][j] = 1;
    std::reverse(G[x].begin(),G[x].end());
    for (auto v : G[x]) {
        if (v == fa) continue;
        rep(j,1,n-1) {
            suf[v][j] = F[x][j];
            F[x][j] = 1ll * F[x][j] * s[v][j] % mod;
        }
    }
    for (auto v : G[x]) {
        if (v == fa) continue;
        int cur = 0; 
        rep(j,1,n-1) {
            f[x][j] = (1ll * f[x][j] + 1ll * cur * f[v][j] % mod) % mod;
            cur = (1ll * cur + 1ll * pre[v][j] * suf[v][j] % mod) % mod;
        }
    }
    rep(j,1,n-1) s[x][j] = (s[x][j-1] + f[x][j]) % mod;
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    scanf("%d%d",&n,&mod);
    rep(i,1,n-1) {
        int x,y; scanf("%d%d",&x,&y); G[x].push_back(y); G[y].push_back(x);
    } c[0][0] = 1;
    rep(i,1,n) {
        c[i][0] = c[i][i] = 1;
        rep(j,1,i-1) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
    } dfs(1,-1);
    rep(m,1,n-1) {
        int ans = 0;
        rep(i,0,m) {
            if ((m - i) & 1) ans = (1ll * ans - 1ll * c[m][i] * F[1][i] % mod + mod) % mod;
            else ans = (ans + 1ll * c[m][i] * F[1][i] % mod) % mod;
        }
        printf("%d ",ans);
    }
}

}signed main(){wxy::main(); return 0;}
```


---

## 作者：TallBanana (赞：3)

题面：[Partial Virtual Trees](https://www.luogu.com.cn/problem/CF1707D)

首先发现是真子集的限制，考虑使限制变为子集的限制。考虑答案数组 $ans$，限制变为子集限制的数组 $f$，那么 $f_n=\sum_{i=1}^nans_i\times C_n^i$，即考虑枚举哪些次数是真正操作了的，易得这个等式。如果我们已经求出了 $f$ 数组，反推 $ans$ 数组，只要移项就好了。即 $ans_n=f_n-\sum_{i=1}^{n-1}ans_i\times C_n^i$。

对于求 $f$，我们可以考虑树形 dp。具体地，设 $F_{u,i}$ 恰好在第 $i$ 次操作后删完了 $u$ 子树内的元素的方案数。特别地，对于 $F_{1,i}$，表示删完了除 $1$ 以外的元素的方案数。

对于 $u\neq 1$ 的转移，考虑两种情况：

* $u$ 子树内的元素先删完，最后 $u$ 被删掉。
* $u$ 子树内剩余一个 $v$ 的子树内没有被删完，其余都被删除，然后 $u$ 被删除，接着 $v$ 子树内的节点被删除。

为什么考虑这两种情况？对于 $u$，只有当其的两个不同的子树内有元素时 $u$ 才会被作为 LCA。

那么转移方程有：

1. $F_{u,i}\leftarrow \prod_{v\in son_u}\sum_{j=1}^iF_{v,j}$
2. $F_{u,i}\leftarrow \sum_{del=1}^{i-1}\sum_{v\in son_u}F_{v,i}\prod_{w\in son_u,w\neq v}\sum_{t=1}^{del}F_{w,t}$

其中，$son_u$ 表示 $u$ 的儿子集合，$del$ 枚举的是 $u$ 删除的时间。直接做肯定超时，考虑优化。对于方程 1，对于 $F_v$ 做前缀和即可。对于方程 2，将 $\sum_{del}$ 提到 $F_{v,i}$ 以后，这样 $\prod_{w\in son_u,w\neq v}\sum_{t=1}^{del}F_{w,t}$ 可以前缀和优化+前后缀合并优化，并对 $\sum_{del}$ 做前缀和，然后就解决了。

再看 $u=1$ 的转移方程，其实相当于只用 转移 1 就好了。怎么理解？因为我们相当于把 $1$ 的子树在 $i$ 的时间以内删掉，而我们是子集操作，所以允许最后有若干个时刻是不动的。

求出了 $F$ 数组，那么 $f_i=F_{1,i}$，再求出 $ans$ 数组即可。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=2e3+10;
LL n,P,f[N][N],pre[N],suf[N],g[N][N],sum[N][N];
vector<LL> e[N];
void dfs(LL u,LL fa)
{
	vector<LL> son;
	for(auto v:e[u]) if(v!=fa)
		dfs(v,u),son.push_back(v);
	for(int i=1;i<n;i++)
	{
		pre[0]=1; suf[son.size()+1]=1;
		for(int j=1;j<=son.size();j++) pre[j]=pre[j-1]*sum[son[j-1]][i]%P;
		for(int j=son.size();j>=1;j--) suf[j]=suf[j+1]*sum[son[j-1]][i]%P;
		for(int j=1;j<=son.size();j++) g[j][i]=(pre[j-1]*suf[j+1]%P+g[j][i-1])%P;
	}
	for(int i=1;i<n;i++)
	{
		f[u][i]=1;
		for(auto v:son) f[u][i]=f[u][i]*sum[v][i]%P;
		if(u!=1) for(int j=1;j<=son.size();j++)
			f[u][i]=(f[u][i]+f[son[j-1]][i]*g[j][i-1]%P)%P;
		sum[u][i]=(sum[u][i-1]+f[u][i])%P;
	}
}
int main()
{
	scanf("%lld%lld",&n,&P);
	for(int i=1;i<n;i++)
	{
		LL u,v;
		scanf("%lld%lld",&u,&v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1,0);
	for(int i=0;i<=n;i++)
		for(int j=0;j<=i;j++)
			if(j==0||j==i) sum[i][j]=1;
			else sum[i][j]=(sum[i-1][j-1]+sum[i-1][j])%P;
	pre[0]=0;
	for(int i=1;i<n;i++)
	{
		pre[i]=f[1][i];
		for(int j=1;j<i;j++) pre[i]=(pre[i]-sum[i][j]*pre[j]%P+P)%P;
		printf("%lld ",pre[i]);
	}
	return 0;
}
```

---

## 作者：chroneZ (赞：3)

## CF1707 D.Partial Virtual Trees

不妨从点集对 $\text{LCA}$ 运算封闭着手，不难发现这个条件等价于

- **当一棵子树的根结点不在点集内时，根节点有且仅能有至多 1 个子结点，其中该子结点的子树内存在结点位于点集**。

这样一来可以记 $dp_{u, k}$ 表示子树 $u$ **恰好**在时刻 $k$ 被删空（另一种理解是，子树 $u$ 对应的点集在恰好 $k$ 次变换后成为空集）的方案数。按上述结论可以这样转移：

- 子树的根 $u$ 在时刻 $k$ 被删除，则子结点可以在任意时刻 $i \leq k$ 被删空。因此 $dp_{u, k} \gets \prod \limits _{v \in son_u} (\sum \limits_{i = 1} ^ k dp_{v, i})$
- 子树的根 $u$ 在时刻 $i < k$ 被删除，则需要且仅需要一个子结点在 $k$ 时刻被删空，其余子结点连同根结点 $u$ 在时刻 $i$ 被删空。对所述内容进行枚举可得 $dp_{u, k} \gets \sum \limits _{i = 1} ^ {k - 1} \sum \limits_{ws \in son_u} (dp_{ws, k} \times \prod \limits_{v \in son_u,v \neq ws} (\sum \limits_{j = 1} ^ i dp_{v, j}))$

根据题意，根结点 $1$ 不必删除，所以对于根结点不必考虑情况二。

通过处理前缀和与积可以将 $dp$ 的转移过程做到 $\mathcal{O} (n ^ 2)$。具体来讲，令 $S_{u, i} \gets \sum \limits_{j = 1} ^ i dp_{u, j}, P_{u, i} \gets \prod \limits_{v \in son_u} S_{v, i}$，则

$$dp_{u, k} = P_{u, k} + \sum \limits_{ws \in son_u} dp_{ws, k} \sum \limits_{i = 1} ^ {k - 1}  \frac{P_{u, i}}{S_{ws, i}}$$

状态数为 $\mathcal{O}(n ^ 2)$，总转移量同样是 $\mathcal{O}(n ^ 2)$，复杂度正确。

> 实现上注意不要直接按上式计算，因为 $\frac{P_{u, i}}{S_{ws, i}}$ 此部分需要对 $S_{ws, i}$ 求逆元，实际复杂度笔者实测会 T。注意到此部分本质上是去除 $ws$ 后剩余子结点的 $S$ 之积，因此可以对 $son_u$ 集合维护前缀积和后缀积作递推，具体定义可以参考如下定义方式：

> $pre_{ch, i} = \prod \limits_{j \leq ch} S_{son(u)_j,i}, suf_{ch, i} = \prod \limits_{j \geq ch} S_{son(u)_j,i}$，令 $ws$ 为 $son_u$ 中的第 $ch$ 个元素，则 $\frac{P_{u, i}}{S_{ws, i}}$ 等价于 $pre_{ch - 1, i} \times suf_{ch + 1, i}$

dp 结束后留下了一个问题：题目中要求每次变换后得到的子集是原集合的真子集，而这种转移方式包含了变换前后集合相等的情况。记 $f(i) \gets dp_{1, i}$，$g(i)$ 为真子集意义下的答案。枚举在 $k$ 次变换下哪几次变换前后集合不等，则会发现

$$f(i) = \sum_{j = 1} ^ {i} \binom{i}{j} g(j)$$

然后就会发现这是个二项式反演[(Tutorial)](https://www.cnblogs.com/GXZlegend/p/11407185.html)的标准形式，做一步反演就可得到

$$g(i) = \sum \limits_{j = 1} ^ i (-1) ^ {i - j} \binom{i}{j} f(j)$$

按序输出 $g(i)$ 就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int N = 2000 + 10;
struct edge {int v, nxt;} e[N << 1];
int head[N], tot;
inline void addedge(int u, int v) {e[++tot].nxt = head[u]; head[u] = tot; e[tot].v = v;}
i64 C[N][N];
inline i64 binom(i64 n, i64 m) {return C[n][m];}

i64 n, mod, dp[N][N], S[N][N], pre[N][N], suf[N][N];
void dfs(int u, int lst){
    for(int k = 1; k <= n; k++)
        dp[u][k] = 0, S[u][k] = 0;
    
    for(int it = head[u]; it; it = e[it].nxt){
        int v = e[it].v;
        if(v == lst) continue;
        dfs(v, u); 
    }
    int ch = 0;
    for(int it = head[u]; it; it = e[it].nxt){
        int v = e[it].v;
        if(v == lst) continue;
        ch++;
        for(int i = 1; i <= n; i++)
            pre[ch][i] = S[v][i], suf[ch][i] = S[v][i];
    }
    for(int i = 1; i <= n; i++) pre[0][i] = suf[ch + 1][i] = 1;
    for(int i = 1; i <= ch; i++)
        for(int j = 1; j <= n; j++)
            pre[i][j] = pre[i - 1][j] * pre[i][j] % mod;
    for(int i = ch; i; i--)
        for(int j = 1; j <= n; j++)
            suf[i][j] = suf[i + 1][j] * suf[i][j] % mod;
    for(int k = 1; k <= n; k++)
        dp[u][k] = pre[ch][k];
    if(u == 1) return;
    for(int it = head[u], cur = 0; it; it = e[it].nxt){
        int v = e[it].v;
        if(v == lst) continue;
        i64 sum = 0; cur++;
        for(int k = 1; k <= n; k++){
            dp[u][k] = (dp[u][k] + dp[v][k] * sum % mod) % mod;
            sum = (sum + pre[cur - 1][k] * suf[cur + 1][k] % mod) % mod;
        }
    }
    for(int k = 1; k <= n; k++)
        S[u][k] = (S[u][k - 1] + dp[u][k]) % mod;
}
void solve(){
    cin >> n >> mod;
    for(int i = 0; i <= n; i++) C[i][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;

    int u, v;
    for(int i = 1; i < n; i++){
        cin >> u >> v;
        addedge(u, v); addedge(v, u);
    }
    dfs(1, -1);
    vector<i64> f(n), g(n, 0);
    for(int i = 1; i < n; i++) f[i] = dp[1][i];
    for(int i = 1; i < n; i++){
        for(int j = 1; j <= i; j++){
            i64 t = binom(i, j) * f[j] % mod;
            if(i - j & 1) t = -t;
            g[i] = (g[i] + t) % mod;
        }
        g[i] = (g[i] % mod + mod) % mod; 
        cout << g[i] << " ";
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
}
```

> 后记：过几天就是 WC 2023，祝自己也能争金夺银/fendou

---

## 作者：Yansuan_HCl (赞：3)

**23.1.13 更正部分表述。**

神仙题。

真子集不好做。考虑子集的答案，可以钦点某些时刻不动，剩下的时刻放入真子集的操作序列。于是根据二项式反演可以用子集的答案把真子集算出来。

“选出一些点”的过程可以看作“删除一些点”。一个点能被删掉，仅当其不作为两个不同点的 LCA. 即，这个点只留下至多一个子树有点。

这启发我们，dp 状态的设计应当关于子树。显然，状态也应当包含一个时刻。在某个时刻，*一个删点的动作能否进行*将被*这个点的每棵子树*在这个时刻是否有点所影响。于是，可以考虑记录子树的最晚删点的时间。

设 $f_u(t)$ 为 $u$ 子树中，留存最晚的点在时刻 $t$ **后**被删除的方案数。

枚举哪个点贡献了最晚留存的时刻 $t$。

- $u$ 最晚留存：

$u$ 的每棵子树都应不晚于 $t$ 时刻删完。

$$f_u(t)\gets \prod_v \sum_{i\le t}f_v(i)$$

- $v \in \text{son}_u$ 子树最晚留存，且晚于 $u$：

根据定义，$u$ 只有一个子树 $v$ 能保留下来（否则 $u$ 将作为 LCA），其他子树都应当更先删除。

枚举其他子树最晚删除时刻、$u$ 的删除时刻。对于每个 $v \in \text{son}_u$，有：

$$f_u(t)\gets f_v(t)\sum_{i\lt t}\prod_{w \neq v}\sum_{j\le i}f_w(j)$$

可以记录 $F_u(t)=\prod_v\sum_{i\le t} f_v(i)$ 进行转移，加上前缀和即可优化至 $O(n^2)$。

```cpp
const int N = 2005; ll P; int n;
BS<int> g[N]; int dfn[N];
void dfs(int u, int fa) { static int p; dfn[u] = ++p; for (int v : g[u]) if (v != fa) dfs(v, u); }

// f_u(t) 表示 u 子树中最晚删除时间为 t
// F_u(t) \prod s_v(p)
ll f[N][N], s[N][N], F[N], Gs[N], Gp[N], G[N];
void dp(int u) {
	for (int v : g[u]) dp(v);
	U (t, 1, n) { // 子树在 t 时间以内删完
		F[t] = 1;
		for (int v : g[u])
			Mul(F[t], s[v][t]);
	}
	U (t, 1, n) // u 是最晚的
		f[u][t] = F[t];

	ms(G, 0);
	U (i, 1, n) { // u 的某棵子树有更晚的
		U (x, 0, g[u].size() - 1)
			Add(f[u][i], G[x] * f[g[u][x]][i]);

		Gp[0] = 1;
		U (x, 0, g[u].size() - 1)
			Gp[x + 1] = Gp[x] * s[g[u][x]][i] % P;
		Gs[g[u].size() + 1] = 1; // 后缀积开始的标号挂了，调了两天，警钟敲烂。
		D (x, g[u].size() - 1, 0)
			Gs[x + 1] = Gs[x + 2] * s[g[u][x]][i] % P;
			
		U (x, 0, g[u].size() - 1)
			Add(G[x], Gp[x] * Gs[x + 2]);
	}
	U (t, 1, n)
		s[u][t] = (s[u][t - 1] + f[u][t]) % P;
}

int main() {
	rd(n, P);
	U (i, 2, n) {
		int u, v; rd(u, v);
		g[u] += v; g[v] += u;
	}
	dfs(1, 0);
	U (i, 2, n) { // 小寄巧之删除连向父亲的边，有效减少特判。
		sort(g[i].begin(), g[i].end(), [&](int u, int v) { return dfn[u] < dfn[v]; });
		g[i].erase(g[i].begin());
	}

	dp(1);

	static ll C[N][N]; C[0][0] = 1;
	U (i, 1, N - 1) {
		C[i][0] = 1;
		U (j, 1, i)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
	}

	U (k, 1, n - 1) {
		ll ans = 0, fg = (k & 1) ? -1 : 1;
		U (i, 0, k) {
			Add(ans, fg * C[k][i] * F[i]); // 1 号点要最晚删。
			Mul(fg, -1);
		}
		printf("%lld ", (ans + P) % P);
	}
}
```

---

## 作者：DaiRuiChen007 (赞：2)

# CF1707D 题解

[Problem Link](https://www.luogu.com.cn/problem/CF1707D)

**题目大意**

> 给定 $n$ 个点的树，根为 $1$，对于每个 $k\in [1,n)$，计数以下点集序列 $S_0\sim S_k$ 的数量：
>
> - $\{1\}=S_0\subsetneq S_1\subsetneq \dots\subsetneq S_k=\{1,2,3,\dots,n\}$。
> - 所有 $S_i$ 都是原树的一棵虚树（$u,v\in S_i\implies \mathrm{LCA}(u,v)\in S_i$）。
>
> 数据范围：$n\le 2000$。

**思路分析**

考虑记录每个点 $u$ 第一次被加入 $S$ 的时间 $x_u$。

那么原问题相当于：$x_1=0,x_2\sim x_n\in [1,k]$，对于一个 $u$，其子树里 $>x_u$ 的点必须在同一个子树内，$0\sim k$ 每种颜色至少出现一次。

先不考虑每种颜色至少出现一次的限制，设 $dp_{u,k}$ 表示用 $[0,k]$ 填满 $u$ 的子树的方案数。

转移时考虑求最大值恰好为 $k$ 的方案数枚举 $x_u$，若 $x_u<k$ 则枚举 $k$ 所在子树，暴力转移得到：
$$
dp_{u,k}=dp_{u,k-1}+\prod_{v\in \mathrm{son}(u)} dp_{v,k}+\sum_{i=0}^{k-1}\sum_{v\in\mathrm{son(u)}}(dp_{v,k}-dp_{v,k-1})\prod_{w\in\mathrm{son(u)},w\ne v} dp_{w,i}
$$
最终 $f_k=\prod_{v\in\mathrm{son}(1)} dp_{v,k-1}$，但我们要满足 $[1,k]$ 每种颜色至少出现一次的限制，不妨设真实的答案为 $g_k$，容易发现两者之间的关系类似二项式反演：
$$
f_k=\sum_{i=0}^k\binom kig_i\implies g_k=\sum_{i=0}^k(-1)^{k-i}\binom ki f_i
$$
因此求出 $f_k$ 后暴力反演即可得到 $g_k$。

问题转成了如何快速求 $dp_{u,k}$，观察转移式的结构可以得到：
$$
\begin{aligned}
dp_{u,k}
&=dp_{u,k-1}+\prod_{v\in \mathrm{son}(u)} dp_{v,k}+\sum_{i=0}^{k-1}\sum_{v\in\mathrm{son(u)}}(dp_{v,k}-dp_{v,k-1})\prod_{w\in\mathrm{son(u)},w\ne v} dp_{w,i}\\
\end{aligned}
$$
容易发现瓶颈在于计算最后 $\prod dp_{w,i}$ 的形式，注意到这里的式子可以用前后缀积预处理出来，这样就能 $\mathcal O(1)$ 计算了。

时间复杂度 $\mathcal O(n^2)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2005;
int n,MOD,dp[MAXN][MAXN],tmp[MAXN][MAXN];
vector <int> G[MAXN];
int lst[MAXN],nxt[MAXN],pre[MAXN],suf[MAXN];
inline void dfs(int u,int fa) {
	vector <int> son,rson;
	for(int v:G[u]) if(v^fa) dfs(v,u),son.push_back(v);
	rson=son,reverse(rson.begin(),rson.end());
	if(!son.empty()) {
		lst[son[0]]=0;
		for(int i=1;i<(int)son.size();++i) lst[son[i]]=son[i-1];
		nxt[rson[0]]=0;
		for(int i=1;i<(int)son.size();++i) nxt[rson[i]]=rson[i-1];
	}
	for(int k=0;k<n;++k) {
		pre[0]=suf[0]=1;
		for(int v:son) pre[v]=pre[lst[v]]*dp[v][k]%MOD;
		for(int v:rson) suf[v]=suf[nxt[v]]*dp[v][k]%MOD;
		for(int v:son) tmp[v][k]=pre[lst[v]]*suf[nxt[v]]%MOD;
		if(k>0) for(int v:son) tmp[v][k]=(tmp[v][k]+tmp[v][k-1])%MOD;
	}
	for(int k=0;k<n;++k) {
		dp[u][k]=1;
		for(int v:son) dp[u][k]=dp[u][k]*dp[v][k]%MOD;
		if(k>0) {
			for(int v:son) {
				int sum=(dp[v][k]+MOD-dp[v][k-1])%MOD;
				dp[u][k]=(dp[u][k]+sum*tmp[v][k-1])%MOD;
			}
			dp[u][k]=(dp[u][k]+dp[u][k-1])%MOD;
		}
	}
}
int f[MAXN],C[MAXN][MAXN];
signed main() {
	scanf("%lld%lld",&n,&MOD);
	for(int i=0;i<=n;++i) {
		C[i][0]=1;
		for(int j=1;j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	for(int i=1,u,v;i<n;++i) {
		scanf("%lld%lld",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1,0);
	for(int k=0;k<n;++k) {
		f[k+1]=1;
		for(int v:G[1]) f[k+1]=f[k+1]*dp[v][k]%MOD;
	}
	for(int k=1;k<n;++k) {
		int ans=0;
		for(int i=1;i<=k;++i) {
			if((k-i)&1) ans=(ans+MOD-C[k][i]*f[i]%MOD)%MOD;
			else ans=(ans+C[k][i]*f[i]%MOD)%MOD;
		}
		printf("%lld ",ans);
	}
	puts("");
	return 0;
	
}
```

---

## 作者：Add_Catalyst (赞：1)

# CF1707D Partial Virtual Trees 题解

------

## 知识点

树形 DP，二项式反演，容斥。

## 分析

### 容斥

考虑先处理容斥的部分，也就是把集合关系中的 $\subsetneq$ 转为 $\subseteq$，这里需要用到容斥和反演。

设：

- $G(k)$ 表示题目要求的答案。
- $F(k)$ 表示把题目要求集合关系中的 $\subsetneq$ 转为 $\subseteq$ 后的答案。

则有：
$$
F(i) = \sum_{j=1}^i {i\choose j} G(j) \\
$$
实际组合意义：表示 $i$ 个 $\subseteq$ 中选出 $j$ 个转为 $\subsetneq$ 的。

那么根据二项式反演，有：
$$
G(i) = \sum_{j=1}^i (-1)^{i-j} {i\choose j} F(j) \\
$$

### DP

设 $f_{u,i}$ 表示在 $S_i$ 中仍有 $u$ 子树中的点的方案数，由于题目的特殊性质，要分两种情况讨论，其中第二种容易遗漏。

#### $u$ 在 $S_i$ 中

$$
\prod_{v\in son(u)} \sum_{j=0}^{i} f_{v,j} \\
$$

暴力 $O(n^3)$，前缀和优化至 $O(n^2)$。

#### $u$ 不在 $S_i$ 中

发现此时在集合 $son(u)$ 中只能有一个点 $v_0$ 满足 $S_i$ 中有 $v_0$ 子树中的点，同时还要考虑 $i$ 在哪个集合删除，则有：
$$
\sum_{v_0\in son(u)} f_{v_0,i} \sum_{j=0}^{i-1} \prod_{v\in son(u),v\neq v_0} \sum_{k=0}^{j-1} f_{v,k} \\
$$
暴力 $O(n^5)$，前缀和、前后缀积优化至 $O(n^2)$。

#### 求 $F(i)$

注意最后求答案的时候不能简单的把 $f$ 拿来直接用，因为题目限定了 $S_k = \set{1}$，所以要再 DP 一下。
$$
F(i) = \prod_{v\in son(rt)} \sum_{j=0}^{i-1} f_{v,j} \\
$$
暴力 $O(n^3)$，前缀和优化至 $O(n^2)$。

### 代码

```cpp
//#define Plus_Cat ""
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define ll long long
#define RCL(a,b,c,d) memset(a,b,sizeof(c)*(d))
#define FOR(i,a,b) for(int i(a);i<=(int)(b);++i)
#define DOR(i,a,b) for(int i(a);i>=(int)(b);--i)
#define tomax(a,...) ((a)=max({(a),__VA_ARGS__}))
#define tomin(a,...) ((a)=min({(a),__VA_ARGS__}))
#define EDGE(g,i,x,y) for(int i=(g).h[(x)],y=(g)[(i)].v;~i;y=(g)[(i=(g)[i].nxt)>0?i:0].v)
#define main Main();signed main(){ios::sync_with_stdio(0);cin.tie(0),cout.tie(0);return Main();}signed Main
using namespace std;
constexpr int N(2e3+10);

namespace IOEcat {
	//Fast IO...
} using namespace IOEcat;

namespace Modular {
	int Mod;
	int C[N][N];
	ll MOD;

	//Modular...

	int Pow(int a,int b=Mod-2) {
		int res(1);
		for(a%=Mod; b; b>>=1,tomul(a,a))if(b&1)tomul(res,a);
		return res;
	}

	void Init(const int n=N-5) {
		FOR(i,0,n) {
			C[i][0]=1;
			FOR(j,1,i)C[i][j]=add(C[i-1][j-1],C[i-1][j]);
		}
	}
} using namespace Modular;

int n,m;
int F[N];
int f[N][N];
vector<int> g[N];

void dfs(int u,int fa) {
	for(const int &v:g[u])if(v^fa)dfs(v,u);
	int tot(0);
	static int son[N],sum[N];
	for(const int &v:g[u])if(v^fa)son[++tot]=v;
	f[u][0]=1;
	FOR(i,1,m) {
		/*DE("Update");*/
		int cur(1);
		static int pre[N];
		FOR(j,pre[0]=1,tot)pre[j]=mul(pre[j-1],f[son[j]][i-1]);
		DOR(j,tot,1)toadd(sum[son[j]],mul(pre[j-1],cur)),tomul(cur,f[son[j]][i-1]);
		/*DE("Trans");*/
		f[u][i]=1;
		FOR(j,1,tot)tomul(f[u][i],f[son[j]][i]);
		FOR(j,1,tot)toadd(f[u][i],mul(add(f[son[j]][i],Mod-f[son[j]][i-1]),sum[son[j]]));
		toadd(f[u][i],f[u][i-1]);
	}
}

signed main() {
#ifdef Plus_Cat
	freopen(Plus_Cat ".in","r",stdin),freopen(Plus_Cat ".out","w",stdout);
#endif
	I(n,Mod),m=n-1,MOD=((__int128)1<<64)/Mod,Init();
	FOR(i,2,n) {
		int u,v;
		I(u,v),g[u].push_back(v),g[v].push_back(u);
	}
	for(const int &v:g[1])dfs(v,1);
	FOR(i,1,m) {
		F[i]=1;
		for(const int &v:g[1])tomul(F[i],f[v][i-1]);
	}
	FOR(i,1,m) {
		int ans(0);
		FOR(j,1,i)(i^j)&1?toadd(ans,Mod-mul(C[i][j],F[j])):toadd(ans,mul(C[i][j],F[j]));
		O(ans,' ');
	}
	return 0;
}
```

------

---

## 作者：UKE_Automation (赞：1)

### CF1707D Partial Virtual Trees

[$\text{Link}$](https://codeforces.com/problemset/problem/1707/D)

首先考虑虚树的要求：如果一个点不在虚树上，那么它最多只有一个子树内有点在虚树上。考虑树形 dp，设 $f(i,j)$ 表示 $i$ 子树内所有点在 $S_j$ 仍有点在虚树中，到 $S_{j+1}$ 所有点都不在虚树上的方案数。转移有两种：

- $i$ 在 $S_j$ 中出现：

  此时子树只需要在 $S_j$ 之前被删除即可，转移方程为：
  $$
  f(i,j)\gets \prod_{v\in son(i)} \sum_{k=0}^j f(v,k)
  $$
  令 $g(i,j)=\sum\limits_{k=0}^j f(i,k)$，上式可以直接转移。

- $i$ 不在 $S_j$ 中出现：

  这表明 $i$ 在 $S_j$ 之前就被删除，根据上面的结论，留到 $S_j$ 的只可能是 $i$ 的某一个子树的点，而其他子树则同样要在 $i$ 删除前被删除。转移为：
  $$
  f(i,j)\gets \sum_{k=0}^{j-1} \sum_{v\in son(i)} f(v,j)\times \prod_{v'\in son(i)\land v'\ne v} g(v',k)
  $$
  利用前后缀积求出 $\prod g(v',k)$ 之后求一遍前缀和，则上式也可以直接转移。

最后我们要求答案，先求出 $G(i)=\prod\limits_{v\in son(1)} g(v,i-1)$，表示 $k=i$ 时的答案。不过此时会发现一个严重的问题，我们在转移的时候实际上没有保证 $S_i\ne S_{i-1}$，但是题目里保证了是真子集。设 $F(i)$ 表示真正的答案，根据插板法经典结论，可以得到：
$$
G(i)=\sum_{j=1}^i \binom{i}{j} F(j)
$$
然后直接二项式反演就可以得到真正的 $F(i)$，直接输出即可。复杂度是 $O(n^2)$ 的，可以通过。

```cpp
#include <bits/stdc++.h>
#define il inline

using namespace std;

const int Maxn = 2e3 + 5;
const int Inf = 2e9;
int Mod;
il int Add(int x, int y) {return x + y >= Mod ? x + y - Mod: x + y;} il void pls(int &x, int y) {x = Add(x, y);}
il int Del(int x, int y) {return x - y < 0 ? x - y + Mod : x - y;} il void sub(int &x, int y) {x = Del(x, y);}
il int qpow(int a, int b) {int res = 1; for(; b; a = 1ll * a * a % Mod, b >>= 1) if(b & 1) res = 1ll * res * a % Mod; return res;}
il int Inv(int a) {return qpow(a, Mod - 2);}
template <typename T> il void chkmax(T &x, T y) {x = (x >= y ? x : y);}
template <typename T> il void chkmin(T &x, T y) {x = (x <= y ? x : y);}
template <typename T>
il void read(T &x) {
	x = 0; char ch = getchar(); bool flg = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) flg = (ch == '-');
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	flg ? x = -x : 0;
}
template <typename T>
il void write(T x, bool typ = 1) {
	static short Stk[50], Top = 0;
	x < 0 ? putchar('-'), x = -x : 0;
	do Stk[++Top] = x % 10, x /= 10; while(x);
	while(Top) putchar(Stk[Top--] | 48);
	typ ? putchar('\n') : putchar(' ');
}
il void IOS() {ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);}
il void File() {freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);}
bool Beg;

int n;
vector <int> E[Maxn];
int f[Maxn][Maxn], g[Maxn][Maxn];
int son[Maxn], cnt, s1[Maxn][Maxn], s2[Maxn][Maxn], s[Maxn][Maxn];
int p[Maxn];

void dfs(int x, int fth) {
	for(int i = 0; i < n; i++) f[x][i] = 1;
	for(auto to : E[x]) {
		if(to == fth) continue;
		dfs(to, x);
		for(int i = 0; i < n; i++) f[x][i] = 1ll * f[x][i] * g[to][i] % Mod;
	}
	cnt = 0;
	for(auto to : E[x]) if(to != fth) son[++cnt] = to;
	for(int i = 0; i < n; i++) s1[0][i] = s2[cnt + 1][i] = 1;
	for(int i = 1; i <= cnt; i++) {
		int to = son[i];
		for(int j = 0; j < n; j++) s1[i][j] = 1ll * s1[i - 1][j] * g[to][j] % Mod;
	}
	for(int i = cnt; i >= 1; i--) {
		int to = son[i];
		for(int j = 0; j < n; j++) {
			s2[i][j] = 1ll * s2[i + 1][j] * g[to][j] % Mod;	
			s[i][j] = 1ll * s1[i - 1][j] * s2[i + 1][j] % Mod;
			if(j) pls(s[i][j], s[i][j - 1]);
		}
	}
	for(int i = 1; i <= cnt; i++) {
		int to = son[i];
		for(int j = 1; j < n; j++) pls(f[x][j], 1ll * f[to][j] * s[i][j - 1] % Mod);
	}
	g[x][0] = f[x][0];
	for(int j = 1; j < n; j++) g[x][j] = Add(g[x][j - 1], f[x][j]);
}

int fac[Maxn], inv[Maxn];
void init() {
	fac[0] = 1; for(int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % Mod;
	inv[n] = Inv(fac[n]); for(int i = n; i >= 1; i--) inv[i - 1] = 1ll * inv[i] * i % Mod;
}

int C(int n, int m) {
	if(n < 0 || m < 0 || n < m) return 0;
	return 1ll * fac[n] * inv[m] % Mod * inv[n - m] % Mod;
}

bool End;
il void Usd() {cerr << (&Beg - &End) / 1024.0 / 1024.0 << "MB " << (double)clock() * 1000.0 / CLOCKS_PER_SEC << "ms\n"; }
int main() {
	read(n), read(Mod);
	init();
	for(int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		E[u].push_back(v), E[v].push_back(u);
	}
	dfs(1, 0);
	for(int i = 0; i < n; i++) p[i] = 1;
	for(auto to : E[1]) {
		for(int i = 1; i < n; i++) {
			p[i] = 1ll * p[i] * g[to][i - 1] % Mod;
		}
	}
	for(int i = 1; i < n; i++) {
		int ans = 0;
		for(int j = 1; j <= i; j++) {
			int res = 1ll * C(i, j) * p[j] % Mod;
			if((i - j) & 1) sub(ans, res);
			else pls(ans, res);
		}
		write(ans, 0);
	}
    Usd();
	return 0;
}


```

---

