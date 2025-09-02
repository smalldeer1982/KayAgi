# Random Walk

## 题目描述

You are given a tree consisting of $ n $ vertices and $ n - 1 $ edges, and each vertex $ v $ has a counter $ c(v) $ assigned to it.

Initially, there is a chip placed at vertex $ s $ and all counters, except $ c(s) $ , are set to $ 0 $ ; $ c(s) $ is set to $ 1 $ .

Your goal is to place the chip at vertex $ t $ . You can achieve it by a series of moves. Suppose right now the chip is placed at the vertex $ v $ . In one move, you do the following:

1. choose one of neighbors $ to $ of vertex $ v $ uniformly at random ( $ to $ is neighbor of $ v $ if and only if there is an edge $ \{v, to\} $ in the tree);
2. move the chip to vertex $ to $ and increase $ c(to) $ by $ 1 $ ;

You'll repeat the move above until you reach the vertex $ t $ .

For each vertex $ v $ calculate the expected value of $ c(v) $ modulo $ 998\,244\,353 $ .

## 说明/提示

The tree from the first example is shown below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1823F/a73d4c18cf7700ea42c791650ad3d6a6f6490ee8.png)  Let's calculate expected value $ E[c(1)] $ : - $ P(c(1) = 0) = 0 $ , since $ c(1) $ is set to $ 1 $ from the start.
- $ P(c(1) = 1) = \frac{1}{2} $ , since there is the only one series of moves that leads $ c(1) = 1 $ . It's $ 1 \rightarrow 2 \rightarrow 3 $ with probability $ 1 \cdot \frac{1}{2} $ .
- $ P(c(1) = 2) = \frac{1}{4} $ : the only path is $ 1 \rightarrow_{1} 2 \rightarrow_{0.5} 1 \rightarrow_{1} 2 \rightarrow_{0.5} 3 $ .
- $ P(c(1) = 3) = \frac{1}{8} $ : the only path is $ 1 \rightarrow_{1} 2 \rightarrow_{0.5} 1 \rightarrow_{1} 2 \rightarrow_{0.5} 1 \rightarrow_{1} 2 \rightarrow_{0.5} 3 $ .
- $ P(c(1) = i) = \frac{1}{2^i} $ in general case.

 As a result, $ E[c(1)] = \sum\limits_{i=1}^{\infty}{i \frac{1}{2^i}} = 2 $ . Image of tree in second test ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1823F/7aa23292e797be22bf854318de16a6d413e9ce30.png)  Image of tree in third test ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1823F/acd505e0eedf66d2621a3c58c7d0b1a12d4deea1.png)

## 样例 #1

### 输入

```
3 1 3
1 2
2 3```

### 输出

```
2 2 1```

## 样例 #2

### 输入

```
4 1 3
1 2
2 3
1 4```

### 输出

```
4 2 1 2```

## 样例 #3

### 输入

```
8 2 6
6 4
6 2
5 4
3 1
2 3
7 4
8 2```

### 输出

```
1 3 2 0 0 1 0 1```

# 题解

## 作者：zlxFTH (赞：38)

考虑任意一条**有向边** $(u, v)$ 的经过的期望次数，发现对于任意一个点 $u$，他的出边的经过的期望次数都相同，因为只取决于经过 $u$ 这个点的期望次数，选取每个出边的概率相同。

设 $f(u)$ 表示 $u$ 的所有出边的经过的期望次数，如果 $u\to v$ 不在 $s\to t$ 的路径上，那么意味着每走一条 $u\to v$ 一定会走会来的，所以 $f(u) = f(v)$。如果 $u\to v$ 在 $s\to t$ 的路径上，它一定会比 $v\to u$ 多走一条边的距离，$f(u) = f(v) + 1$。

于是从 $t$ 开始递推，点 $u$ 的期望次数即为 $c(u) = deg(u)\times f(u)$（特判 $f(t) = 0, c(t) = 1$）。

---

## 作者：Fido_Puppy (赞：19)

## 题目链接

[CF1823F Random Walk](https://codeforces.com/problemset/problem/1823/F)

## 题解

看到树上随机游走题，直接考虑高斯消元。

设 $f_i$ 表示 $i$ 点的期望经过次数，然后可以列出关系式：

设 $S_i$ 表示和 $i$ 点相邻的点的集合，$d_i$ 表示 $i$ 点的度数。

1. $$f_i = \sum_{j \in S_i \land j \neq t} \dfrac{f_j}{d_j} \qquad (i \neq s \land i \neq t)$$

2. $$f_i = 1 + \sum_{j \in S_i \land j \neq t} \dfrac{f_j}{d_j} \qquad (i = s)$$

3. $$f_i = 1 \qquad (i = t)$$

---

$3$ 式比较好理解，最后肯定是要到 $t$ 点的，所以 $f_t = 1$。

$1$ 式就是比如 $j$ 点的期望经过次数为 $f_j$，那么有期望 $\dfrac{f_j}{d_j}$ 次是经过 $j$ 后再经过 $i$ 的，$j \neq t$ 是因为经过 $t$ 后就结束了。

$2$ 式和 $1$ 式很像，就是起点刚开始有一次，所以 $+1$。

然后直接高斯消元就是 $\Theta(n ^ 3)$ 的，无法通过。

但是树上高斯消元有一个常见套路，假设 $u$ 的父亲节点为 $F$，就可以将 $f_u$ 表示成 $A_u \cdot f_F + B_u$ 的形式。

设 $u$ 的儿子集合为 $T_u$，那么转移方程就类似：

$$f_u = k \cdot f_F + \sum_{v \in T_u} k_{u, v} \times (A_v \cdot f_u + B_v) + b$$

最终这个等式就只剩下 $f_u$ 和 $f_F$，直接就能转换成上述形式。

然后由于根节点没有父亲节点，所以根节点的 $f$ 值直接能求出来，然后就是再从父亲往儿子推下来就行了。

本题解代码实现的时间复杂度为 $\Theta(n \log V)$（需要求逆元）。

## 代码链接

<https://codeforces.com/contest/1823/submission/203762450>

---

## 作者：AtomAlpaca (赞：9)

## 题目
简述题意：给定一棵树和两个节点 $S, T$，从 $S$ 出发，在树上随机游走直到走到 $T$ 为止，求出每个节点的期望经过次数。

感觉树上做法很奇妙，于是写一篇题解！

## 题解
令 $d_u$ 为节点 $u$ 的度数，$f_u$ 为节点 $u$ 的期望经过次数。每次移动时，会从当前节点的所有节点中等概率选择一个节点，因此到达每个相邻节点的概率都是 $\dfrac{1}{d_u}$；从被到达节点的角度考虑，就有 $f_u = \sum_{(u, v)\in E} { \dfrac{f_v}{d_v} }$。

特别地，节点不能从 $T$ 转移过来，因为到达 $T$ 后游走就会停止；因为从 $S$ 节点出发，$f_S$ 初始值为 $1$。整理一下：

$$
f_u =
\left\{ 
\begin{aligned} 
& 1, &if \ u=T 
\\
&[u=S] + \sum_{(u, v)\in E,v\ne T} { \dfrac{f_v}{d_v} }, &otherwise
\end{aligned}
\right.
$$

然而我们发现转移是有环的，不能直接 dp。我们固然可以使用高斯消元解决这个方程组，这也是[有环图上随机游走问题](https://www.luogu.com.cn/problem/P3232)的最好解决办法，但是 $O(n^3)$ 的复杂度无法通过此题。

考虑到这道题的图是一棵树，我们可以考虑把式子化成 $f_u=g_u f_{fa} +c_u$ 的形式。由于树根是没有父亲的，我们能够直接求出树根的期望经过次数，然后 dfs 下去求得每个节点的经过次数。

$$
\begin{aligned} 
f_u &= [u=S] + \sum_{(u, v)\in E,v\ne T} { \dfrac{f_v}{d_v} } \\
&= [u=S] + \dfrac{f_{fa}}{d_{fa}} + \sum_{(u, v)\in E,v\ne T,fa} { \dfrac{f_v}{d_v}} \\
&= [u=S] + \dfrac{f_{fa}}{d_{fa}} + \sum_{(u, v)\in E,v\ne T,fa} { \dfrac{g_v f_u + c_v}{d_v}} \\
&= [u=S] + \dfrac{f_{fa}}{d_{fa}} + \sum_{(u, v)\in E,v\ne T,a} { \dfrac{g_v f_u}{d_v}} + \sum_{(u, v)\in E,v\ne T,fa} { \dfrac{c_v}{d_v}}\\
\end{aligned}
$$
移项得到：
$$
\begin{aligned} 
(1-\sum_{(u, v)\in E,v\ne T,fa}{\dfrac{g_v}{d_v}}) f_u &= [u=S] + \dfrac{f_{fa}}{d_{fa}} + \sum_{(u, v)\in E,v\ne T, fa} { \dfrac{c_v}{d_v}}
\end{aligned}
$$
$$
\begin{aligned} 
f_u&=\textcolor{red}{ \dfrac{1}{d_{fa}(1-\sum_{(u, v)\in E,v\ne T,fa}{\dfrac{g_v}{d_v}})}} f_{fa} + \textcolor{green}{\dfrac{[u=S]+\sum_{(u, v)\in E,v\ne T,fa} { \dfrac{c_v}{d_v}}}{(1-\sum_{(u, v)\in E,v\ne T, fa}{\dfrac{g_v}{d_v}})}} \\

f_u &= \textcolor{red}{g_u} f_{fa} + \textcolor{green}{c_u}
\end{aligned}
$$

于是我们得到了 $g, c$ 的转移方程，而且这个转移是仅依赖自己的子节点的！于是我们可以先一遍 dfs 求出每个节点的 $g, c$，再求出 $f$。

## 代码
```c++
#include <bits/stdc++.h>

typedef long long ll;

const int MOD = 998244353;
const int MAX = 2e5 + 5;

int n, S, T, u, v, tot;
int h[MAX], f[MAX], c[MAX], g[MAX], d[MAX];

struct E { int v, x; } e[MAX << 2];
void add(int u, int v) { e[++tot] = {v, h[u]}; h[u] = tot; e[++tot] = {u, h[v]}; h[v] = tot; }

inline int qp(int a, int x)
{
	int res = 1;
	while (x) { if (x & 1) { res = 1ll * res * a % MOD; } a = 1ll * a * a % MOD; x >>= 1; }
	return res;
}

void dfs(int u, int fa)
{
	int _g = 0, _c = (u == S);
	for (int i = h[u]; i; i = e[i].x)
	{
		int v = e[i].v; if (v == fa) { continue; }
		dfs(v, u);
		_g = (_g + 1ll * g[v] * qp(d[v], MOD - 2) % MOD) % MOD;
		_c = (_c + 1ll * c[v] * qp(d[v], MOD - 2) % MOD) % MOD;
	}
	_g = qp((1 - _g + MOD), MOD - 2);
	_c = 1ll * _c * _g % MOD;
	_g = 1ll * _g * qp(d[fa], MOD - 2) % MOD;
	g[u] = _g; c[u] = _c;
}

void _dfs(int u, int fa)
{
	f[u] = (1ll * g[u] * f[fa] % MOD + c[u]) % MOD;
	for (int i = h[u]; i; i = e[i].x)
	{
		int v = e[i].v; if (v == fa) { continue; }
		_dfs(v, u);
	}
}

int main()
{
	scanf("%d%d%d", &n, &S, &T);
	for (int i = 1; i < n; ++i) { scanf("%d%d", &u, &v); add(u, v); ++d[u]; ++d[v]; }
	dfs(T, 0); f[T] = 1; _dfs(T, 0); f[T] = 1;
	for (int i = 1; i <= n; ++i) { printf("%d ", f[i]); }
	return 0;
}
```

---

## 作者：littlebug (赞：6)

太妙了。

不想推式子，所以从纯思维的角度做。

参考了 @[zlxFTH](https://www.luogu.com.cn/user/86576) 大佬的[题解](https://www.luogu.com.cn/article/xfhixui4)。

## Solution

因为直接用点来 dp 不好做，所以我们用边来 dp！

考虑在**有向图**上，一个点的所有出边的经过次数是相同的，于是我们只要求出它的任意一条出边的期望经过次数即可！设 $f_u$ 为经过 $u$ 任意一条出边的期望次数。而我们又~~可以~~想到，对于一条边 $u \to v$：

- 如果它**不在** $s \leadsto t$ 上，那么如果我们走了这条边，为了到达 $t$ 就一定要走回来，所以经过 $u \to v$ 和 $v \to u$ 这两条边的次数一定是相等的。即 $f_u = f_v$
- 如果它**在** $s \leadsto t$ 上，那么我们在走过之后，有可能走回来，也有可能不走回来。而不走回来当且仅当走过这条边之后一直走到了 $t$（只走到 $t$ 即可，不用管后面的路径），但我们以走到 $t$ 就停止了，于是只有一次机会可以不走回来，于是 $f_u = f_v + 1$。

从 $t$ 开始 dp 即可，$c_u = f_u \times deg_u$，特判下 $c_t = 1$，做完了。

## Code

```cpp
const int MAXN=2e5+5;
int n,s,t;
vector <int> p[MAXN];
int f[MAXN];
bitset <MAXN> g;

il bool dfs_g(int u,int ufa)
{
    u==t && (g[u]=1);
    for(auto v:p[u]) if(v!=ufa) dfs_g(v,u) && (g[u]=1);
    return g[u];
}

il void dfs_f(int u,int ufa)
{
    for(auto v:p[u]) if(v!=ufa)
    {
        f[v]=f[u]+(g[u]&g[v]);
        dfs_f(v,u);
    }
}

signed main()
{
    read(n,s,t),_::r(p,n-1,0);

    dfs_g(s,0);
    dfs_f(t,0);

    rep(i,1,n) write(i==t ? 1ll : f[i]*(int)p[i].size()%mod,' ');

    return fast_io::ot(),0;
}
```

---

## 作者：littlebug (赞：5)

我正在尝试在同一道题里面交两篇题解。

这个是常规做法，不过没有[那个](https://www.luogu.com.cn/article/c3zzi4nq)从有向边经过次数关系的做法巧妙，而且复杂度 $O(n \log n)$（要求逆元）也没有那个 $O(n)$ 优秀。

## Solution

设 $f_u$ 为经过节点 $u$ 的期望次数，$d_u$ 为节点 $u$ 的度数，则一眼可以看出式子：

$$
f_u = \sum _{(u,v) \in E , v \ne t} \frac {f_v} {d_v}
$$

然后因为这是一棵树，所以考虑把它转化成 $f_u = A_u f_{fa} + B_u$ 的形式，然后推式子：

$$
\begin{aligned}
f_u &= [u=s] + \sum _{(u,v) \in E , v \ne t} \frac {f_v} {d_v} \\
&= [u=s] + \frac {f_{fa}} {d_{fa}} + \sum _{(u,v) \in E , v \ne t , v \ne fa} \frac {f_v} {d_v} \\
&= [u=s] + \frac 1 {d_{fa}} f_{fa} + \sum _{(u,v) \in E , v \ne t , v \ne fa} \frac {A_v f_u + B_v} {d_v} \\
&= [u=s] + \frac 1 {d_{fa}} f_{fa} + f_u  \times \sum _{(u,v) \in E , v \ne t , v \ne fa} \frac {A_v} {d_v} + \sum _{(u,v) \in E , v \ne t , v \ne fa} \frac {B_v} {d_v}
\end{aligned}
$$

继续：

$$
(1 - \sum _{(u,v) \in E , v \ne t , v \ne fa} \frac {A_v} {d_v}) f_u = [u=s] + \frac 1 {d_{fa}} f_{fa} + \sum _{(u,v) \in E , v \ne t , v \ne fa} \frac {B_v} {d_v} \\
f_u = {\color{66CCFF} \frac 1 {d_{fa} (1 - \sum \limits _{(u,v) \in E , v \ne t , v \ne fa} \frac {A_v} {d_v})}} f_{fa} + {\color{EEAADD} \frac {[u=s] + \sum \limits _{(u,v) \in E , v \ne t , v \ne fa} \frac {B_v} {d_v}} {(1 - \sum \limits _{(u,v) \in E , v \ne t , v \ne fa} \frac {A_v} {d_v})}}
$$

于是：

$$
A_u = {\color{66CCFF} \frac 1 {d_{fa} (1 - \sum \limits _{(u,v) \in E , v \ne t , v \ne fa} \frac {A_v} {d_v})}} \\
B_u = {\color{EEAADD} \frac {[u=s] + \sum \limits _{(u,v) \in E , v \ne t , v \ne fa} \frac {B_v} {d_v}} {(1 - \sum \limits _{(u,v) \in E , v \ne t , v \ne fa} \frac {A_v} {d_v})}}
$$

注意到 $A_u$ 和 $B_u$ 里面只有 $A_v,B_v,d_v$，所以可以先把 $A_u,B_u$ dp 出来，然后再把 $f_u$ dp 出来，做完了。

## Code

```cpp
int n,s,t;
vector <int> p[MAXN];
int f[MAXN],deg[MAXN],A[MAXN],B[MAXN]; // deg[i] 为点 i 的度数；其余含义如上文所示

il void dfs(int u,int ufa)
{
    int _A=0,_B=(u==s);

    for(auto v:p[u]) if(v!=ufa)
    {
        dfs(v,u);
        (_A+=A[v]*ginv(deg[v])%mod)%=mod; // ginv(x) 表示 x 的逆元
        (_B+=B[v]*ginv(deg[v])%mod)%=mod;
    }

    _A=ginv(1-_A+mod);
    (_B*=_A)%=mod;
    (_A*=ginv(deg[ufa]))%=mod;

    A[u]=_A,B[u]=_B;
}

il void dfs_f(int u,int ufa)
{
    f[u]=(A[u]*f[ufa]%mod+B[u])%mod;
    for(auto v:p[u]) v!=ufa && (dfs_f(v,u),1);
}

signed main()
{
    read(n,s,t),_::r(p,n-1,0);
    rep(i,1,n) deg[i]=p[i].size();

    dfs(t,0);
    f[t]=1,dfs_f(t,0);

    f[t]=1;
    _::w(f,n);

    return 0;
}
```

---

## 作者：tzl_Dedicatus545 (赞：5)

我觉得消元的正解才是值得提倡的，这篇题解大概能帮你学习乱搞？

首先我们观察样例，发现一件很不寻常的事情：**所有数的期望都是整数**，这是及其不常见的，于是我们自然地往这里思考。

以 $t$ 为根考虑问题是显然的。我们可以首先观察到几个很浅显的性质：

1. $t$ 的子树中，除了有 $s$ 那一个，其他的答案都为 $0$，于是我们直接将其删除。
2. $t$ 的到达期望为 $1$

我们不妨列出式子（如果你是 trick 大师的话，似乎这里可以直接暴力把 $\text{fa}_u$ 设出来消元，但我今天看了题解才知道这个 trick，所以接下来我会演示不用 trick 的人类智慧做法！）：

1. $c_t=1$
2. $c_u=\sum \frac{c_v}{\text{deg}_v} (u\not=s)$
3. $c_s=1+\sum\frac{c_v}{deg_v}$

等一下，你不是说所有数的期望都是整数吗，这一点也不整啊？

于是我们大胆猜测：$\text{deg}_u|c_u$，下面记 $a_u=\frac{c_u}{\text{deg}_u}\in\Z$。（后续我们会给出 $a_u\in\Z$ 的证明）

额，首先，我们观察样例，再手模记下，注意到：$s\to t$ 的路径上的点 $u$ 的任意一个不含 $s$ 的子树 $v$（形式化的，$s\not\in\text{subtree}_v\backslash\{v\}$），有：

$\forall t\in\text{subtree}_v,a_t=a_v$。

证明是简单的：上述构造满足方程。$n$ 个线性无关的方程 $n$ 个未知数，我们给出了一个自由元。

接下来，我们就把问题规约到了一条链的情况（因为显然对任何路径上的点 $u$，根据上面的结论，其他子树中的贡献都和 $\text{deg}_u$ 中的某一部分抵消了）

手动消元，即得：$a_u=\text{dep}_u$。

现在我们给出了一组符合要求的构造！因为上述有 $n+1$ 个方程 $n$ 个未知数，故此构造是唯一的，我们就做完了！

回收伏笔：因为此构造唯一，自然有 $a_u\in\Z$。

---

## 作者：Linnyx (赞：2)

设 $F_{i}$ 为经过点 $i$ 时的期望，$in_{i}$ 为点 $i$ 度数，我们易得:

$\begin{aligned} 
F_{t} &= 1\\
 F_{s} &= 1+ \frac{F_{fa}}{in_{fa}} + \sum_{v \in V_{i}}\frac{F_{v}}{in_{v}} \\
  F_{u} &= \frac{F_{fa}}{in_{fa}} + \sum_{v \in V_{i}}\frac{F_{v}}{in_{v}}\;\;\;(u\ne T,S)
 \end{aligned}$

我们发现 $F_{i}$ 只和它的父亲和有直接相连的儿子有关，可以写成一个方程组，用高斯消元解决，时间复杂度是 $\mathcal{O}(N^3)$。

不足以通过本题，但是本题有一个优秀的性质，即是这是在一棵树上,当我们来到叶子节点时，便可以求解其系数，接下来就可以从下向上的解出每一项系数。

按照我们刚才所说的列出树上高斯消元套路式子（powered by @[ckain](https://www.luogu.com.cn/blog/edisnimorF/
)）：

设 $F_{i}=g_{i}F_{fa} + c_{i}$，

将 $2,3$ 写成一个式子：

$\begin{aligned} 
\displaystyle F_{u} &= \frac{F_{fa}}{in_{fa}} + \sum_{v \in V_{i}}\frac{F_{v}}{in_{v}} + [u = S] \;\;\; (u\ne T)\\
\displaystyle &= \frac{F_{fa}}{in_{fa}}+ \sum_{v \in V_{i}}\frac{g_{v}F_{u}+c_{v}}{in_{v}}+[u=S]\\
\displaystyle &=\frac{F_{fa}}{in_{fa}}+ \sum_{v \in V_{i}}\frac{g_{v}}{in_{v}}F_{u}+\sum_{v \in V_{i}}\frac{c_{v}}{in_{v}}+[u=S]\\
\end{aligned}$

移项得:

$$(1-\sum_{v \in V_{i}}\frac{g_{v}}{in_{v}})F_{u}=\frac{F_{fa}}{in_{fa}}+\sum_{v \in V_{i}}\frac{c_{v}}{in_{v}}+[u=S]\;\;\; (u\ne T)$$

此时我们就可以得知 $g_{i}$ 和 $c_{i}$ 的式子了（把左边除过去）。

时间复杂度 $\mathcal{O}(N \log N)$。

贴个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}
const int N=2e5+10,mod=998244353;
int n;
int S,T;
int f[N],g[N],c[N],in[N];
vector<int> edge[N];
inline int qpow(int b,int p){
	int res=1;
	while(p){
		if(p&1)res=res*b%mod;
		b=b*b%mod;
		p>>=1;
	}
	return res;
}
void dfs1(int x,int fa){
	int gv=0,cv=0; 
	for(int i:edge[x]){
		if(i==fa)continue;
		dfs1(i,x);
		gv+=g[i]*qpow(in[i],mod-2)%mod;gv%=mod;
		cv+=c[i]*qpow(in[i],mod-2)%mod;cv%=mod;
	}
	gv=(1-gv+mod)%mod;
	gv=qpow(gv,mod-2);
	cv+=(x==S);
	if(fa!=T)g[x]=qpow(in[fa],mod-2)*gv%mod;
	c[x]=cv*gv%mod;
}
void dfs2(int x,int fa){
	if(x!=T)f[x]=(g[x]*f[fa]%mod+c[x])%mod;
	for(int i:edge[x]){
		if(i==fa)continue;
		dfs2(i,x);
	}
}
signed main(){
	n=rd();S=rd();T=rd();
	for(int i=1;i<n;i++){
		int x=rd(),y=rd();
		in[x]++;in[y]++;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dfs1(T,0);
	f[T]=1;
	dfs2(T,0);
	for(int i=1;i<=n;i++)printf("%lld ",f[i]);
	return 0;
}

```


---

## 作者：Mars_Dingdang (赞：1)

套路题。写在 CSP2023-S 之前，也是我最后一次 CSP 了吧。RP ++；

## 题目大意
给一棵 $n$ 个节点的树，求从 $s$ 随机游走到 $t$ 时每个点期望经过次数取模 $998244353$。

$n\le 2\times 10^5$。

## 大体思路
随机游走题，套路地想到高斯消元。由于每到一个点 $u(u\neq t)$，就有 $\dfrac {1}{deg_u}$ 的概率走到与 $u$ 相邻的一个点 $v$。因此，设 $f_u$ 表示 $u$ 被经过的期望次数，则有

$$f_u=\sum_{(u,v)\in E\ \text{and}\ v\neq t}\dfrac {f_v} {deg_v},\ u\neq s\ \text{and}\ u\neq t$$

$$f_s=1+\sum_{(s,v)\in E\ \text{and}\ v\neq t}\dfrac {f_v} {deg_v}$$

$$f_t = 1$$

这样有 $n$ 个方程和 $n$ 个未知数，高斯消元可以实现 $O(n^3)$ 复杂度。

然而，上述代码实现的是对于一般图的随机游走问题，并没有利用树的性质。

树上高斯消元还有一个套路，即可以设 $f_u=A_u f_{fa}+B_u$。然后，我们带入一般的状态转移方程，有：

$$f_u=\dfrac{f_{fa}}{deg_{fa}}+\sum \dfrac{A_vf_u+B_v}{deg_v}$$

移项化简可得 

$$A_u=\dfrac{deg_{fa}^{-1}}{1-\sum\limits_{v\in son(u)} \dfrac {A_v}{deg_v}},\ B_u=\dfrac{\sum\limits_{v\in son(u)} \dfrac{B_v}{deg_v}}{1-\sum\limits_{v\in son(u)} \dfrac {A_v}{deg_v}}$$

特殊地，$A_t=0, B_t=1$，且 $B_s$ 的分子需加上 $1$。此外，对于所有 $t$ 的儿子 $u$，有 $A_u=0$。

事实上这一类树上高斯消元的转化是比较常见的，另一道题是 [随机游走](https://www.luogu.com.cn/problem/P5643)。这题不仅需要用树上高斯消元转化 DP 式子，可能还需要浅用 Min-Max 容斥和 FWT 等小技巧。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 2e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int n, s, t;
vector <int> e[maxn];
const ll mod = 998244353;
inline ll Pow(ll a, ll b) {
	a = (a % mod + mod) % mod;
	ll res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res % mod;
}
ll f[maxn], A[maxn], B[maxn], deg[maxn];
inline void dfs1(int u, int fa) {
	ll sA = 0, sB = 0, sD = 0;
	for(auto v : e[u]) {
		if(v == fa) continue;
		dfs1(v, u);
//		if(v == t) continue;
		(sA += A[v] * Pow(deg[v], mod - 2) % mod) %= mod;
		(sB += B[v] * Pow(deg[v], mod - 2) % mod) %= mod;
		(sD += deg[v]) %= mod;
	}
	if(u == t) A[u] = 0, B[u] = 1;
	else {
		if(e[u].size() == 1) {
			A[u] = Pow(deg[fa], mod - 2);
			B[u] = (u == s ? 1 : 0);
		}
		else {
			A[u] = Pow(deg[fa], mod - 2) * Pow(1 - sA, mod - 2) % mod;
			B[u] = (sB + (u == s ? 1 : 0)) * Pow(1 - sA, mod - 2) % mod;
		}
	}
	if(fa == t) A[u] = 0;
}
inline void dfs2(int u, int fa) {
	f[u] = (A[u] * f[fa] % mod + B[u]) % mod;
	for(auto v : e[u]) {
		if(v == fa) continue;
		dfs2(v, u);
	}
}
int main () {
	read(n); read(s); read(t);
	rep(i, 1, n - 1) {
		int u, v;
		read(u); read(v);
		e[u].push_back(v);
		e[v].push_back(u);
		deg[u] ++;
		deg[v] ++;
	}
	dfs1(t, 0);
	dfs2(t, 0);
	rep(i, 1, n) write(f[i]), putchar(' ');
	
	return 0;
}
```

## 后记 
CSP 2023 RP ++；

---

## 作者：N1K_J (赞：0)

注意到，由于是随机游走，对于点 $u$，以其为起点经过与其相连的所有边的概率是相等的。

那么不妨设 $f(u)$ 是对于点 $u$ 经过其相邻边的期望次数，那么对于点 $u \not= t$，答案为 $f(u) \cdot deg_u$，特别的，点 $t$ 的答案固定为 $1$。

我们不妨来考虑一条边 $(u,v)$，记 $E_{u \rightarrow v}$ 表示了以 $u$ 为起点 $v$ 为终点经过边 $(u,v)$ 的次数，应当注意到 $E_{u \rightarrow v} = f(u)$。

如果我们走过了一次 $(u,v)$。

假如这条边并不在 $s$ 到 $t$ 的路径上，那么我们一定还要经过或者已经经过一次 $(v,u)$，不然是无法到达 $t$ 的。

也就是说 $E_{u \rightarrow v} = E_{v \rightarrow u}$，即 $f(u) = f(v)$。

反之，如果在 $s$ 到 $t$ 的路径上，不妨设 $s$ 到 $t$ 的有向路径中包括从 $u$ 走到 $v$。

那么也就是说 $u \rightarrow v$ 将比 $v \rightarrow u$ 多走一次，即 $E_{u \rightarrow v} = E_{v \rightarrow u}+1$，等价于 $f(u) = f(v)+1$。

因此，事实上 $f(u)$ 是 $u$ 到 $t$ 的路径上在 $v$ 到 $t$ 的路径上的点数（不包括 $t$），于是做完了。

时间复杂度 $O(n)$，优于大多数题解。

[Code](codeforces.com/contest/1823/submission/274649626)

---

## 作者：Purslane (赞：0)

# Solution

我不会树上随机游走。

设 $dp_u$ 为 $u$ 被经过的期望次数。那么容易写出方程：

1. 终点 $t$ 满足 $dp_t = 1$；
2. 起点 $s$ 满足：

$$
dp_s = 1 + \sum_{(s,u) \in E \text{ and } u \neq t} \dfrac{dp_u}{\deg u}
$$
3. 其他点满足

$$
dp_v = \sum_{(v,u) \in E \text{ and } u \neq t} \dfrac{dp_u}{\deg u}
$$

那么你得到了一个 $n$ 元线性方程组，使用高斯消元法可以在 $O(n^3)$ 内解决。

-------

上述方法适用于一般图上随机游走。

对于树上随机游走，我们习惯设 $dp_u = A_u dp_{fa_u} + B_u$。不妨以 $s$ 为根进行 DP。那么我们可以得到：

$$
dp_u = \dfrac{A_u^{-1}(dp_u-B_u)}{\deg fa} + \sum_{v \in son_u} \dfrac{A_v dp_u + B_v}{\deg v}
$$

$dp_u$ 是未知的，我们在消元，因此两边 $dp_u$ 的系数和常数项相等。（换句话说，我们尝试把 $u$ 子树内的很多方程消成 $dp_u = A_u dep_{fa_u} + B_u$ 的形式。）

比较 $dp_u$ 的系数得到：

$$
A_u = \dfrac{1}{\deg fa} + (\sum_{v \in son_u} \dfrac{A_v}{\deg v}) A_u
$$

即

$$
A_u = \deg^{-1}fa \cdot (1 - \sum_{v \in son_u} \dfrac{A_v}{\deg v})^{-1}
$$

比较常数项得到：

$$
\dfrac{B_u}{A_u \deg fa} = \sum_{v \in son_u} \dfrac{B_v}{\deg v}
$$

即

$$
B_u = (\sum_{v \in son_u} \dfrac{B_v}{\deg v}) \cdot (1 - \sum_{v \in son_u} \dfrac{A_v}{\deg v})^{-1}
$$

最终，全部带入关于 $s$ 的方程，解出 $dp_s$，一路带回。

值得注意的是，遍历到 $t$ 后没必要继续遍历其儿子，因为它们不会被访问到。

---------

我们这么做，本质上就是在进行消元。不过利用了树的特殊性质，在遍历树的同时把 $u$ 的子树内的变量全部消为 $dp_{fa_u}$。

时间复杂度 $O(n \log n)$。（瓶颈在于求逆元）

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=998244353;
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans=ans*base%MOD;
		base=base*base%MOD,p>>=1;
	}
	return ans;
}
int n,s,t,a[MAXN],b[MAXN],dp[MAXN];
vector<int> G[MAXN];
void dfs(int u,int f) {
	if(u==t) return a[u]=0,b[u]=1,void();
	for(auto v:G[u]) if(v!=f) dfs(v,u);
	if(f) {
		int sum=1,mul=0;
		for(auto v:G[u]) if(v!=f&&v!=t) sum=(sum-a[v]*qpow(G[v].size(),MOD-2))%MOD;
		a[u]=qpow(sum*(int)G[f].size()%MOD,MOD-2);
		for(auto v:G[u]) if(v!=f&&v!=t) mul=(mul+b[v]*qpow(G[v].size(),MOD-2))%MOD;
		b[u]=mul*qpow(sum,MOD-2)%MOD;
	}
	else {
		int K=1,B=1;
		for(auto v:G[u]) if(v!=t) {
			B=(B+b[v]*qpow(G[v].size(),MOD-2))%MOD;
			K=(K-a[v]*qpow(G[v].size(),MOD-2))%MOD;
		}
		dp[s]=B*qpow(K,MOD-2)%MOD;
	}
	return ;
}
void solve(int u,int f) {
	if(f) dp[u]=(a[u]*dp[f]+b[u])%MOD;
	for(auto v:G[u]) if(v!=f) solve(v,u);
	return ;	
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>s>>t;
	ffor(i,1,n-1) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	dfs(s,0),solve(s,0);
	ffor(i,1,n) cout<<(dp[i]%MOD+MOD)%MOD<<' ';
	return 0;
}
```

哎，负的变量不能和 `G[v].size()` 乘。

---

## 作者：gdf_yhm (赞：0)

[CF1823F](https://www.luogu.com.cn/problem/CF1823F)

### 思路

设 $f_u$ 表示经过 $u$ 的期望次数。$f_u$ 的值是所有与 $u$ 有边的点 $v$ 的答案 $f_v$ 除以走向 $u$ 的概率 $\frac{1}{d_v}$。

$$f_u=[u=s]+\sum_{(u,v)\in E,v\neq t}\frac{f_v}{d_v}$$

$$f_t=1$$

问题是 $f_u$ 的值可以从 $fa$ 得来，转移成环。直接高斯消元 $O(n^3)$，但是没有用到树的性质。成环是因为有来自父亲的转移，但根节点没有。设 $f_u=a_u\times f_{fa}+b_u$，带入 dp 方程。

$$f_u=[u=s]+\frac{f_{fa}}{d_{fa}}+\sum_{(u,v)\in E,v\neq t,v\neq fa}\frac{f_v}{d_v}$$

$$f_u=[u=s]+\frac{f_{fa}}{d_{fa}}+\sum_{(u,v)\in E,v\neq t,v\neq fa}\frac{a_v\times f_u+b_v}{d_v}$$

$$(1-\sum_{(u,v)\in E,v\neq t,v\neq fa}\frac{a_v}{d_v})\times f_u=[u=s]+\frac{f_{fa}}{d_{fa}}+\sum_{(u,v)\in E,v\neq t,v\neq fa}\frac{b_v}{d_v}$$

$$f_u=\frac{\frac{1}{d_{fa}}}{(1-\sum_{(u,v)\in E,v\neq t,v\neq fa}\frac{a_v}{d_v})}\times f_{fa}+\frac{[u=s]+\sum_{(u,v)\in E,v\neq t,v\neq fa}\frac{b_v}{d_v}}{(1-\sum_{(u,v)\in E,v\neq t,v\neq fa}\frac{a_v}{d_v}}$$

对比系数，只与 $u$ 的儿子有关，解出 $a_u,b_u$。再从跟从上往下推一遍。注意到 $v\neq t$ 很烦，直接把 $t$ 设为跟。

### code

```cpp
int n,s,t;
int head[maxn],tot;
struct nd{
	int nxt,to;
}e[maxn<<1];
void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int d[maxn],f[maxn],a[maxn],b[maxn];
void dfs(int u,int fa){
	int val=1;b[u]=(u==s);
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs(v,u);
		val+=mod-a[v]*ksm(d[v])%mod;
		b[u]+=b[v]*ksm(d[v])%mod;
	}
	val%=mod;b[u]%=mod;
	a[u]=ksm(val*d[fa]%mod);if(fa==t)a[u]=0;
	b[u]=ksm(val)*b[u]%mod;
}
void dfs1(int u,int fa){
	f[u]=(a[u]*f[fa]+b[u])%mod;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs1(v,u);
	}
}
void work(){
	n=read();s=read();t=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
		++d[u],++d[v];
	}
	dfs(t,0);
	f[t]=1;dfs1(t,0);
	for(int i=1;i<=n;i++)printf("%lld ",f[i]);
}
```


---

## 作者：Limie (赞：0)

挺神奇一个题。

## 题义简述

从树上 $s$ 点随机游走，到 $t$ 点结束，询问每个点被经过的期望次数。

## 思路
首先暴力的设 $f_u$ 表示点 $u$ 被经过的期望次数。

那么转移公式是这样的：
$$
f_u=
\begin{cases}
\sum_{(u,v) \in E} \frac{f_v}{d_v} \quad (u \neq s \vee u \neq t) \\
\sum_{(u,v) \in E} \frac{f_v}{d_v} + 1 \quad (u =s) \\
1 \quad (u=t)
\end{cases}
$$

那么这是啥意思呢？简单来说，当 $u \neq s$ 且 $u \neq t$ 时，你考虑上一步是从哪走过来的；$u=s$ 时情况类似，只是要加上 $1$ 表示开始经过的那一次；$u=t$ 时，直接结束了，所以只有一次。

那么你发现这个 DP 是有环的，考虑把环去掉。

~~高斯消元，然后 $O(n^3)$ 快乐T飞~~

这个时候有一个很厉害的 trick，假设 $f_u = a_u \times f_{father_u} + b_u$ （$father_u$ 下文简称 $fa$）

考虑带到那个式子里。

以 $u \neq s$ 且 $u \neq t$ 的情况作为例子。

$$
\begin{matrix}
f_u=\sum_{(u,v) \in E} \frac{f_v}{d_v} \\
f_u=\sum_{v \in son_u} \frac{f_v}{d_v}+\frac{f_{fa}}{d_{fa}} \\
f_u=\sum \frac{a_v \times f_u + b_v}{d_v}+\frac{f_{fa}}{d_{fa}} \\
(1-\sum \frac{a_v}{d_v}) f_u=\frac{f_{fa}}{d_{fa}} + \sum \frac{b_v}{d_v} \\
f_u=\frac{1}{d_{fa}(1-\sum \frac{a_v}{d_v})}f_{fa}+\frac{\sum \frac{b_v}{d_v}}{1-\sum \frac{a_v}{d_v}}
\end{matrix}
$$

然后你发现 $a,b$ 都只跟自己的子节点有关，$f$ 只跟它的父亲有关，于是你就可以先用一遍 dfs 求出 $a,b$ ，再用一遍求出 $f$。

## 实现细节
这个题有一个细节就是 $u=t$ 的情况，这个的话可以将 $t$ 直接作为根来解决。

## Code
```cpp
#include<bits/stdc++.h>
namespace Limie{
	#define x first
	#define y second
	using namespace std;
	typedef long long LL;
	typedef pair<int,int> PII;
	typedef unsigned long long ULL;
	typedef long double LD;
}
using namespace Limie;
const int mod=998244353;
int n,s,t;
int h[200010],e[400010],ne[400010],idx;
int a[200010],b[200010],f[200010],d[200010];
void add(int a,int b)
{
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}
int qmi(int a,int b)
{
	int ans=1;
	while(b){
		if(b&1)ans=(LL)ans*a%mod;
		a=(LL)a*a%mod;
		b>>=1;
	}
	return ans;
}
void dfs1(int u,int fa)
{
	int ans=0;
	if(u==s)b[u]=1;
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==fa)continue;
		dfs1(j,u);
		ans=(ans+(LL)a[j]*qmi(d[j],mod-2)%mod)%mod;
		b[u]=(b[u]+(LL)b[j]*qmi(d[j],mod-2)%mod);
	}
	ans=(1-ans+mod)%mod;
	if(fa)a[u]=qmi((LL)d[fa]*ans%mod,mod-2);
	b[u]=(LL)b[u]*qmi(ans,mod-2)%mod;
}
void dfs2(int u,int fa)
{
	for(int i=h[u];~i;i=ne[i]){
		int j=e[i];
		if(j==fa)continue;
		f[j]=((LL)a[j]*f[u]%mod+b[j])%mod;
		dfs2(j,u);
	}
}
int main()
{
	int i;
	cin>>n>>s>>t;
	memset(h,-1,sizeof h);
	for(i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		d[a]++,d[b]++;
		add(a,b),add(b,a);
	}
	dfs1(t,0);
	dfs2(t,0);
	f[t]=1;
	for(i=1;i<=n;i++)cout<<f[i]<<' ';
}

```

---

## 作者：User_Authorized (赞：0)

## 题意
给定一棵由 $n$ 个节点组成的树，定义每次移动的方式为等概率的移动到相邻节点上，询问从 $s$ 移动到 $t$ 的过程中每个点的期望经过次数。

（$1 \le n \le 2 \times 10^5$）。

## 题解
定义 $f_i$ 为节点 $i$ 的期望经过次数，$fa_u$ 为节点 $u$ 的父亲节点，$\operatorname{deg}_u$ 表示节点 $u$ 的度数，$\operatorname{son}_u$ 表示节点 $u$ 的子节点集合。

我们记路径 $s \rightarrow t$ 上的点为 $k_0, k_1, k_2, \cdots k_m$，其中 $k_0 = s, k_m = t$。我们可以发现对于任意 $r_i$ 在去除路径上的边连接的子树后都会形成一棵以自己为根的有根树，记为 $\operatorname{subtree}_{r_i}$。通过观察可以发现，对于这类子树叶子节点 $v$，有

$$f_v = \dfrac{1}{\operatorname{deg}_{fa_v}} f_{fa_v}$$

考虑推广这一结论，对于在子树中的节点 $u$，有 $f_u = \dfrac{\operatorname{deg}_u}{\operatorname{deg}_{fa_u}} f_{fa_u}$，下面给出数学归纳法的证明

$$\begin{aligned}
f_u &= \sum\limits_{\left(u, v\right) \in E} \dfrac{1}{\operatorname{deg}_v}f_v \\
&= \sum\limits_{v \in \operatorname{son}_u} \dfrac{1}{\operatorname{deg}_v}f_v + \dfrac{1}{\operatorname{deg}_{fa_u}}f_{fa_u} \\
&= \sum\limits_{v \in \operatorname{son}_u} \dfrac{1}{\operatorname{deg}_v} \dfrac{\operatorname{deg}_v}{\operatorname{deg}_u} f_u + \dfrac{1}{\operatorname{deg}_{fa_u}} f_{fa_u} \\
&= \sum\limits_{v \in \operatorname{son}_u} \dfrac{1}{\operatorname{deg}_u} f_u + \dfrac{1}{\operatorname{deg}_{fa_u}} f_{fa_u} \\
&= \dfrac{\operatorname{deg}_u - 1}{\operatorname{deg}_u} f_u + \dfrac{1}{\operatorname{deg}_{fa_u}} f_{fa_u} \\
&= \dfrac{\operatorname{deg}_u}{\operatorname{deg}_{fa_u}} f_{fa_u}
\end{aligned}$$

推广该结论，设 $v \in \operatorname{son}_u, pa = fa_u$

$$f_v = \dfrac{\operatorname{deg}_v}{\operatorname{deg}_u} f_u = \dfrac{\operatorname{deg}_v}{\operatorname{deg}_u} \dfrac{\operatorname{deg}_u}{\operatorname{deg}_{pa}} f_{pa} = \dfrac{deg_v}{deg_{pa}} f_{pa}$$

对于 $\forall v \in \operatorname{subtree}_{u}$，有

$$f_v = \dfrac{\operatorname{deg}_v}{\operatorname{deg}_u} f_u$$

---

现在考虑路径 $s \rightarrow t$ 上的点

$$\begin{aligned}
f_{k_0} &= 1 + \sum\limits_{\left(k_0, v\right) \in E} \dfrac{1}{\operatorname{deg}_v}f_v \\
&= 1 + \sum\limits_{\left(k_0, v\right) \in E \land v \neq k_1}\dfrac{1}{\operatorname{deg}_v}f_v + \dfrac{1}{\operatorname{deg}_{k_1}} f_{k_1} \\
&= 1 + \sum\limits_{\left(k_0, v\right) \in E \land v \neq k_1}\dfrac{1}{\operatorname{deg}_v}\dfrac{\operatorname{deg}_v}{\operatorname{deg}_{k_0}} f_{k_0} + \dfrac{1}{\operatorname{deg}_{k_1}} f_{k_1} \\
&= 1 + \dfrac{\operatorname{deg}_{k_0} - 1}{\operatorname{deg}_{k_0}} f_{k_0} + \dfrac{1}{\operatorname{deg}_{k_1}} f_{k_1} \\
&= \operatorname{deg}_{k_0} \left(1 + \dfrac{1}{\operatorname{deg}_{k_1}} f_{k_1}\right)
\end{aligned}$$

$$\begin{aligned}
f_{k_1} &= \sum\limits_{\left(k_1, v\right) \in E} \dfrac{1}{\operatorname{deg}_v} f_v \\
&= \sum\limits_{\left(k_1, v\right) \in E \land v \neq k_0 \land v \neq k_2} \dfrac{1}{\operatorname{deg}_v}f_v + \dfrac{1}{\operatorname{deg}_{k_0}}f_{k_0} + \dfrac{1}{\operatorname{deg}_{k_2}} f_{k_2} \\
&= \sum\limits_{\left(k_1, v\right) \in E \land v \neq k_0 \land v \neq k_2} \dfrac{1}{\operatorname{deg}_v}\dfrac{\operatorname{deg}_v}{\operatorname{deg}_{k_1}}f_{k_1} + \dfrac{1}{\operatorname{deg}_{k_0}}f_{k_0} + \dfrac{1}{\operatorname{deg}_{k_2}} f_{k_2} \\
&= \dfrac{\operatorname{deg}_{k_1} - 2}{\operatorname{deg}_{k_1}} f_{k_1} + \left(1 + \dfrac{1}{\operatorname{deg}_{k_0}} f_{k_1}\right) + \dfrac{1}{\operatorname{deg}_{k_2}} f_{k_2} \\
&= 1 + \dfrac{\operatorname{deg}_{k_1} - 1}{\operatorname{deg}_{k_1}} f_{k_1} + \dfrac{1}{\operatorname{deg}_{k_2}} f_{k_2} \\
&= \operatorname{deg}_{k_1} \left(1 + \dfrac{1}{\operatorname{deg}_{k_2}} f_{k_2}\right)
\end{aligned}$$

同理

$$\begin{aligned}
f_{k_{m - 1}} &= \operatorname{deg}_{k_{m - 1}} \left(1 + \dfrac{1}{\operatorname{deg}_{k_m}} f_{k_m}\right) \\
&= \operatorname{deg}_{k_{m - 1}} \left(1 + 0\right) \\
&= \operatorname{deg}_{k_{m - 1}}
\end{aligned}$$

接下来我们将该式展开

$$f_{k_{m - 2}} = \operatorname{deg}_{k_{m - 2}} \left(1 + \dfrac{1}{\operatorname{deg}_{k_{m - 2}}} f_{k_{m - 2}}\right) = 2  \cdot \operatorname{deg}_{k_{m - 2}}$$

$$f_{k_{m - 3}} = \operatorname{deg}_{k_{m - 2}} \left(1 + \dfrac{1}{\operatorname{deg}_{k_{m - 3}}} f_{k_{m - 3}}\right) = 3 \cdot \operatorname{deg}_{k_{m - 3}}$$

$$f_{k_{m - i}} = i \cdot \operatorname{deg}_{k_{m - i}}$$

---

综合以上的结论可以发现，对于路径上的各个点 $k_{m - i}$ 有

$$\forall v \in \operatorname{subtree}_{k_{m - i}}, f_v = i \cdot \operatorname{deg}_v$$

可以 $\mathcal{O}(n)$ 解决本题。

### Code

```cpp
//Codeforces - 1823F
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % mod;
}

valueType N, S, T;
ValueVector ans, distance;
ValueMatrix G;

void dfs(valueType x, valueType from) {
    if (x == T) {
        distance[x] = 0;

        return;
    }

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        dfs(iter, x);

        if (distance[iter] != -1) {
            distance[x] = distance[iter] + 1;

            return;
        }
    }
}

void calc(valueType x, valueType from, valueType k) {
    ans[x] = mul(k, G[x].size());

    for (auto const &iter: G[x]) {
        if (iter == from)
            continue;

        calc(iter, x, k);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N >> S >> T;

    ans.resize(N + 1, 0);
    distance.resize(N + 1, -1);
    G.resize(N + 1);

    for (valueType i = 1; i < N; ++i) {
        valueType u, v;

        std::cin >> u >> v;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(S, 0);

    for (valueType i = 1; i <= N; ++i) {
        if (distance[i] != -1) {
            ans[i] = mul(distance[i], G[i].size());

            for (auto const &iter: G[i])
                if (distance[iter] == -1)
                    calc(iter, i, distance[i]);
        }
    }

    ans[T] = 1;

    for (valueType i = 1; i <= N; ++i)
        std::cout << ans[i] << ' ';

    std::cout << std::endl;

    return 0;
}
```

---

## 作者：Uuuuuur_ (赞：0)

题意：给定一棵树，起点 $s$，终点 $t$，一个点会从起点开始在树上随机游走，直到走到终点，求每个点被经过的期望次数。

发现概率是极限定义的，基本就要考虑消元 DP 了。

而消元 DP 的核心思想就是通过转移方程，不断消元，将$f_i$ 与 $f_j$ 的关系式，转化为 $Kf_i=B$ 的形式。

首先这棵树是一个无根树，令 $s$ 为根，设 $d_u$ 为点的度数，然后直接设 $f_u$ 为当前点经过的期望次数。那么有两种途径到当前点。

1. 从儿子（非 $t$ ）走上去，那么每一个儿子对 $f_u$ 的贡献就是 $\displaystyle \frac{f_v}{d_v}$。

1. 从父亲走下去，这个贡献是 $\displaystyle \frac{f_{fa}}{d_{fa}}$。

就有

$$f_u =(\sum{\frac{f_v}{d_v}})+\frac{f_{fa}}{d_{fa}}$$

特别的，对于 $s$，$f_s =(\displaystyle\sum{\frac{f_v}{d_v}})+1$，对于叶子结点 $f_u=\displaystyle \frac{f_{fa}}{d_{fa}}$。

叶子结点是一个突破口，我们发现叶子结点的方程只包含两个变量，可以消元，$f_{fa}=Kf{u}$，那么对于叶子结点的父亲，就可以把方程中的 $f_v$ 都代换成 $Kf_u$，然后又可以消元……如此直到根结点，然后可以直接把 $f_u$ 算出来。

最后，从上往下，根据之前的系数，计算 $f_v$
。

式子是比较的简单的，注意点就是搜到 $t$ 就不必往下了，因为到它就停止了。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#define int long long
using namespace std;
int n, s, t;
const int N = 2e5 + 5;
const int mod = 998244353;
vector<int> g[N];
int f[N];
int d[N];
int num[N];
int pow_mod(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int inv(int x) {
	x = ((x % mod) + mod) % mod;
	return pow_mod(x, mod - 2);
}
int mult(int x, int y) {
	return x * y % mod;
}
int add(int x, int y) {
	return (x +  y) % mod;
}
int dp(int u, int fa) { // return k:  f[u] = kf[fa]
	int k = 0;
	if (u == t) {
		num[u] = inv(d[fa]);
		return 0;
	}
	for (int v : g[u]) {
		if (v != fa) {
			k = add(k, mult(inv(d[v]), dp(v, u)));
		}
	}
	if (u == s) {
		f[s] = inv(1 - k);
		return 0;
	}
	return num[u] = mult(inv(1 - k), inv(d[fa]));
}
void solve(int u, int fa) {
	if (u == t) return ;
	for (int v : g[u]) {
		if (v != fa) {
			f[v] = mult(num[v], f[u]);
			solve(v, u);
		}
	}
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> s >> t;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
		d[u]++, d[v]++;
	}
	dp(s, 0);
	
	solve(s, 0);
	for (int i = 1; i <= n; i++) cout << f[i] << ' ';
	return 0;	
}
```



---

