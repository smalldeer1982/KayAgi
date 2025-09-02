# Maximizing Root

## 题目描述

You are given a rooted tree consisting of $ n $ vertices numbered from $ 1 $ to $ n $ . Vertex $ 1 $ is the root of the tree. Each vertex has an integer value. The value of $ i $ -th vertex is $ a_i $ . You can do the following operation at most $ k $ times.

- Choose a vertex $ v $ that has not been chosen before and an integer $ x $ such that $ x $ is a common divisor of the values of all vertices of the subtree of $ v $ . Multiply by $ x $ the value of each vertex in the subtree of $ v $ .

What is the maximum possible value of the root node $ 1 $ after at most $ k $ operations? Formally, you have to maximize the value of $ a_1 $ .

A tree is a connected undirected graph without cycles. A rooted tree is a tree with a selected vertex, which is called the root. The subtree of a node $ u $ is the set of all nodes $ y $ such that the simple path from $ y $ to the root passes through $ u $ . Note that $ u $ is in the subtree of $ u $ .

## 说明/提示

Both examples have the same tree:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/6a70ae0aa91307af0a5148283774844759a80b11.png)For the first test case, you can do two operations as follows:

- Choose the subtree of vertex $ 4 $ and $ x = 2 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/efd9ed3fe3fe146d2c3ad22bdc3a0d5094263862.png)  After this operation, the node values become $ \{24, 12, 24, 12, 12\}. $
- Choose the subtree of vertex $ 1 $ and $ x = 12 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/448b3697478f6bf92a71b275bb4b714ad3a39227.png)  After this operation, the node values become $ \{288, 144, 288, 144, 144\}. $

 The value of the root is $ 288 $ and it is the maximum.For the second test case, you can do three operations as follows:

- Choose the subtree of vertex $ 4 $ and $ x = 2 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/efd9ed3fe3fe146d2c3ad22bdc3a0d5094263862.png)  After this operation, the node values become $ \{24, 12, 24, 12, 12\}. $
- Choose the subtree of vertex $ 2 $ and $ x = 4 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/7004889d13c9800ff61e810a176c843b3201729c.png)  After this operation, the node values become $ \{24, 48, 24, 48, 48\}. $
- Choose the subtree of vertex $ 1 $ and $ x = 24 $ .  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1778F/33e11b130545753fb9dc63bbfb2deaf72c859447.png)  After this operation, the node values become $ \{576, 1152, 576, 1152, 1152\}. $

 The value of the root is $ 576 $ and it is the maximum.

## 样例 #1

### 输入

```
2
5 2
24 12 24 6 12
1 2
1 3
2 4
2 5
5 3
24 12 24 6 12
1 2
1 3
2 4
2 5```

### 输出

```
288
576```

# 题解

## 作者：irris (赞：6)

> 树形 dp / 简单数论

被骗得不轻。

首先应当注意到从下往上操作比从上往下操作优。这样 gcd 才有可能变大。

设 $f_{u,i}$ 表示不经过对 $u$ 操作，$u$ 子树内所有点的权值都是 $i$ 的倍数的最小步数，$g_{u,i}$ 表示经过对 $u$ 操作，$u$ 子树内所有点的权值都是 $i$ 的倍数的最小步数。

转移显然：

- $f_{u,i} = \sum\limits_{v \in son(u)} g_{v,i}$，且若 $i \nmid a_u$，让 $f_{u,i} \gets \inf$；
- $g_{u,i} = \min\limits_{i \mid j^2} (f_{u,j} + [i \neq j])$。

**来计算一下时间复杂度吧**。我们考虑 $a_i \gets \gcd(a_1, a_i)$，这样答案显然不变。此外，我们注意到有用的第二维只有 $a_1$ 的因数，而 $d(v)_{\max} = 32(v \leq 1000)$。

统计答案：最后一次操作显然应该在 $1$ 上，因此为 $\max\limits_{f_{1,i} \leq k - 1}(i) \times a_1$。

时间复杂度 $\mathcal O(nd(a_1)^2)$。

---

## 作者：灵茶山艾府 (赞：5)

提供一个**自顶向下**的做法，不是 DP。加上快读后可以跑到 Rank 1。

### 定义

定义 $\text{subGcd}(v)$ 为子树 $v$ 所有数（点权）的 GCD。

定义 $\text{ceilSqrt}(x)$ 为最小的 $c$，满足 $c^2$ 是 $x$ 的倍数。这可以通过把 $x$ 分解质因数，每个质因子的幂次 $e$ 改成 $\lceil e/2 \rceil$ 得到。

### 思考

1. 既然要让答案最大，每次操作选的 $x$ 应当是子树所有数的 GCD。
2. 按照从叶子到根的顺序操作，可以让答案尽量大。例如从上到下是 $16,4,2$，先操作上面，只能把 $16$ 乘以 $2$；先操作下面，最后可以让 $16$ 乘以 $16$。
3. 答案一定是 $a_1$ 乘以它的一个因子。由于 $1000$ 以内的数至多有 $32$ 个因子（例如 $840$），所以我们可以**从大到小**地枚举 $a_1$ 的因子 $d$。如果 $1$ 的每个儿子子树都能通过操作（操作次数之和小于 $k$），使得子树所有数的 GCD 是 $d$ 的倍数，那么答案就是 $a_1\cdot d$。
4. 写一个自顶向下的 DFS，额外传入参数 $d$。考虑 $1$ 的儿子 $v$，分类讨论：
     1. 如果 $\text{subGcd}(v)$ 已经是 $d$ 的倍数，那么无需操作子树 $v$ 中的任何节点。
     2. 否则，如果 $\text{subGcd}(v)^2$ 是 $d$ 的倍数，那么只需要在节点 $v$ 上操作一次，无需操作更下面的节点。
     3. 否则，如果 $v$ 是叶子，或者 $a_v^2$ 不是 $d$ 的倍数，那么无法完成操作。
     4. 否则，应该先操作 $v$ 的后代，然后操作 $v$。我们的目标是，对于 $v$ 的每个儿子子树 $w$，通过操作，使得 $\text{subGcd}(w)$ 是 $\text{ceilSqrt}(d)$ 的倍数，这样就可以让 $\text{subGcd}(v)^2$ 是 $d$ 的倍数。**这个结论是本题的核心结论**。根据该结论，继续往下递归 $v$ 的儿子 $w$，额外传入参数 $\text{ceilSqrt}(d)$。
5. 累加 DFS 中的操作次数。如果操作次数小于 $k$（注意不是小于等于，因为最后还要对节点 $1$ 操作一次），那么答案就是 $a_1\cdot d$。

细节：特判 $k=0$ 的情况。

Go 语言代码（下标从 $0$ 开始）：

```go
package main
import ("bufio";."fmt";"os")
func gcd(a, b int) int { for a != 0 { a, b = b%a, a }; return b }

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	const mx = 1000
	divisors := [mx + 1][]int{}
	for i := mx; i > 0; i-- { // 方便后面从大到小遍历因子
		for j := i; j <= mx; j += i {
			divisors[j] = append(divisors[j], i)
		}
	}

	// ceilSqrt[i]^2 是 i 的倍数
	ceilSqrt := [mx + 1]int{}
	for i := 1; i <= mx; i++ {
		ceilSqrt[i] = 1
		x := i
		for p := 2; p*p <= x; p++ {
			for p2 := p * p; x%p2 == 0; x /= p2 {
				ceilSqrt[i] *= p
			}
			if x%p == 0 {
				ceilSqrt[i] *= p
				x /= p
			}
		}
		if x > 1 {
			ceilSqrt[i] *= x
		}
	}

	var T, n, k int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n, &k)
		a := make([]int, n)
		for i := range a {
			Fscan(in, &a[i])
		}
		g := make([][]int, n)
		for i := 1; i < n; i++ {
			var v, w int
			Fscan(in, &v, &w)
			v--
			w--
			g[v] = append(g[v], w)
			g[w] = append(g[w], v)
		}
		if k == 0 {
			Fprintln(out, a[0])
			continue
		}

		subGcd := make([]int, n)
		var dfs0 func(int, int)
		dfs0 = func(v, fa int) {
			subGcd[v] = a[v]
			for _, w := range g[v] {
				if w != fa {
					dfs0(w, v)
					subGcd[v] = gcd(subGcd[v], subGcd[w])
				}
			}
		}
		dfs0(0, -1)

		var cnt int
		var dfs func(int, int, int)
		dfs = func(v, fa, d int) {
			if subGcd[v]%d == 0 {
				// 无需操作
				return
			}
			if subGcd[v]*subGcd[v]%d == 0 {
				cnt++ // 操作 v
				return
			}
			if len(g[v]) == 1 || a[v]*a[v]%d > 0 {
				cnt = 1e9 // 无法操作
				return
			}
			for _, w := range g[v] {
				if w != fa {
					dfs(w, v, ceilSqrt[d])
				}
			}
			cnt++ // 操作 v
		}

		for _, d := range divisors[a[0]] {
			cnt = 0
			for _, v := range g[0] {
				dfs(v, 0, d)
			}
			if cnt < k {
				Fprintln(out, a[0]*d)
				break
			}
		}
	}
}
```

时间复杂度：$\mathcal{O}(Dn)$，其中 $D=32$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：hgzxwzf (赞：5)

## [CF1778F](https://codeforces.com/contest/1778/problem/F)

### Tutorial：

设 $dp_{i,j}$ 表示在不操作 $i$ 好点的前提下，使得 $a_i$ 的 $j$ 小因子（从 $0$ 开始编号）是 $i$ 子树内所有节点的权值的公约数的最小操作次数。

假设 $v$ 是 $i$ 的儿子，$a_k$ 的因子个数为 $c_k$，$div_{i,j}$ 为 $a_i$ 的 $j$ 小因子。

$$dp_{i,j}=\sum_{v}\min_{k=0}^{C_v}w(div_{v,k},div_{i,j})$$

当 $x\bmod y=0$，$w(x,y)=dp_{v,k}$；当 $x\bmod y\ne0\land x^2\bmod y=0$，$w(x,y)=dp_{v,k}+1$；当 $x\bmod y\ne0\land x^2\bmod y\ne0$，$w(x,y)=+\infty$。

如果 $x\bmod y=0$，就说明已经满足 $v$ 的子树内所有节点的公约数是 $y$ 的倍数，不需要操作；

如果 $x\bmod y\ne 0\land x^2\bmod y=0$，就说明还没有满足 $v$ 的子树内所有节点的公约数是 $y$ 的倍数，但通过一次操作就可以满足；

否则，就说明不管怎样都无法满足。

因为值域很小，所以这样转移的时间复杂度是对的。

$ans=\max_{j,dp_{1,j}<k}a_1\times div_{1,j}$。

### Code：
```cpp
const int N=1e5+10,M=1e3+10;
 
vector<int>e[N],dp[N],divd[N];
int k,a[N];
 
void dfs(int cur,int fa)
{
	dp[cur].clear();
	dp[cur].resize(divd[a[cur]].size());
	for(auto &nt: e[cur])
	{
		if(nt==fa) continue;
		dfs(nt,cur);
		rep(i,0,(int) dp[cur].size()-1)
		{
			int mi=k+1;
			rep(j,0,(int) dp[nt].size()-1)
			{
				if(divd[a[nt]][j]%divd[a[cur]][i]==0) mi=min(mi,dp[nt][j]);
				else if(divd[a[nt]][j]*divd[a[nt]][j]%divd[a[cur]][i]==0) mi=min(mi,dp[nt][j]+1);
			}
			dp[cur][i]=min(dp[cur][i]+mi,k+1);
		}
	}
	dp[cur][0]=0;
}
 
int main()
{
//	freopen("in","r",stdin);
//	freopen("out","w",stdout);
	rep(i,1,M-1)
		for(int j=i;j<M;j+=i)
			divd[j].push_back(i);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		cin>>n>>k;
		rep(i,1,n) e[i].clear();
		rep(i,1,n) cin>>a[i];
		rep(i,1,n-1)
		{
			int u,v;
			cin>>u>>v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		dfs(1,1);
		int ans=a[1];
		per(i,0,(int) dp[1].size()-1) if(dp[1][i]<k) {ans=divd[a[1]][i]*a[1];break;}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：bsdsdb (赞：2)

题意：有一棵点权为 $\{a_n\}$，值域为 $[1,V=1000]$ 的树，对一个节点进行操作可以将一个点的子树内所有数乘上他们的一个公共因数，问对 $k$ 个不同点进行操作后 $a_1$ 最大值。

提示：

1. 所有公共因数都用得到吗？
2. 操作顺序？
3. 想个 $\Omicron(nV)$ 状态数的 dp；
4. 把状态数压到 $\Omicron(nd(V))$。

公共因数换成 $\gcd$ 显然不劣。定义「有向树」为有向图 $([1,n],\{(p_i,i)\mid i\text{ not root}\}$，即上向下连边做成的有向图。我们来证明，把操作顺序变成一个有向树拓扑排序的子序列，总是不劣的，原来的公共因数不会消失，只会增加。该命题等价于：「给一个序列 $\{b_m\}$ 和一个位置集合 $S$。对一个集合 $A$ 操作定义为：$g\gets\gcd_{i\in A}b_i$，然后 $i\in A:b_i\gets gb_i$。则：先操作 $S$ 再操作 $U$ 得到 $g_S$，先操作 $U$ 再操作 $S$ 得到 $g_U$，有 $g_U\mid g_S$」（$U,S$ 对应树上一个上面的操作点和下面的操作点）。

设 $v_p(x):=\max\{y\mid(p^y\mid x)\}$，则原命题等价于 $\forall \text{ prime }p:v_p(g_U)\le v_p(g_S)$。令 $T:=\complement_U^S,r_A:=\min_{i\in A}v_p(a_i)$，那么命题又被我们转化为：「先 $S$ 后 $U$ 得到的 $r_U$」不小于「先 $U$ 后 $S$ 得到的 $r_U$」。接下来考察 $r_U=\min(r_S,r_T)$ 怎么变化。

| 步骤 \\ 值 | $r_S$ | $r_T$ | $r_U$ |
| :-: | :-: | :-: | :-: |
| 先 $S$ | ${r_S}'=2r_S$ | ${r_T}'=r_T$ | ${r_U}'=\min(2r_S,r_T)$ |
| 后 $U$ | ${r_S}''={r_S}'+{r_U}'$ | ${r_T}''={r_T}'+{r_U}'$ | ${r_U}''=2{r_U}'=2\min(2r_S,r_T)$ |
| 先 $U$ | ${r_S}'=r_S+r_U$ | ${r_T}'=r_T+r_U$ |${r_U}'=2r_U$ |
| 后 $S$ | ${r_S}''=2{r_S}'=2r_S+2r_U$ | ${r_T}''={r_T}'=r_T+r_U$ | ${r_U}''=\min(2r_S+2r_U,r_T+r_U)$ |

下文将 $r_S,r_T$ 分别简写为 $S,T$，问就是懒。命题进一步被转化为：证明两个非负整数 $S,T$ 一定满足 $2\min(2S,T)\ge\min(2S+2\min(S,T),T+\min(S,T))$。分类讨论：

- $S<\frac T2:\Leftrightarrow2\cdot2S\ge\min(4S,S+T)$；
- $\frac T2\le S<T:\Leftrightarrow2T\ge\min(4S,S+T)\Leftarrow2T\ge T+S\ge\min(4S,S+T)$
- $S\ge T:\Leftrightarrow2T\ge\min(2S+2T,2T)$。

证毕。操作顺序是一个拓扑序的子序列的时候能得到答案。由于不重合的子树之间操作顺序不影响，所以拓扑序换成更严格的 dfs 序也是成立的。接下来就是树形 dp 了。设 $\mathrm{dp}_{x,v,0/1}$ 表示 $x$ 子树中，选 / 没选 $x$ 达成整个子树都是 $v$ 的倍数的最小步数。对于叶节点：

$$
\mathrm{dp}_{x,v,0}=
\begin{aligned}\begin{cases}
0,\quad&v\mid a_x\\
+\infty,\quad&\text{otherwise.}
\end{cases}\end{aligned}
$$

对于非叶节点：

$$
\mathrm{dp}_{x,v,0}=
\begin{aligned}\begin{cases}
\sum_{p_i=x}\min\mathrm{dp}_{i,v},\quad&v\mid a_x\\
+\infty,\quad&\text{otherwise.}
\end{cases}\end{aligned}
$$

对于所有节点：

$$
\mathrm{dp}_{x,v,1}=\min_{j\mid i,ij=v}\mathrm{dp}_{x,i,0}
$$

最后答案：

$$
\mathrm{ans}=a_1\max_{\mathrm{dp}_{1,v,0}<k}v
$$

状态数看似是 $\Omicron(nV)$ 的，其实不然。只有第二维 $v$ 满足 $v\mid a_1$ 的才会用到，状态数 $\Omicron(nd(V))$，总复杂度 $\Omicron(n\max_{i=1}^V\sum_{j\mid i}d(j))$。接下来证明 $\Omicron(\max_{i=1}^V\sum_{j\mid i}d(j))\le\Omicron(\sqrt{V\log V})$，我们考虑一个更强的结论：$\Omicron(\sum_{d\mid V})\sqrt d\le\Omicron(\sqrt{V\log V})$。记 $V=:\prod_{i=1}^k{p_i}^{\alpha_i}$，则：

$$
\begin{aligned}
\sum_{d|V}d^\frac12=&\prod_{i=1}^k\sum_{j=0}^{\alpha_i}{p_i}^\frac j2\\
=&\prod_{i=1}^k\dfrac{{p_i}^\frac{\alpha_i+1}2-1}{{p_i}^\frac12-1}\\
\le&\prod_{i=1}^k\sqrt\dfrac{{p_i}^{\alpha_i+1}}{({p_i}^\frac12-1)({p_i}^\frac12+1)}\\
=&\sqrt{\prod_{i=1}^k{p_i}^{\alpha_i}\cdot\dfrac{{p_i}}{{p_i}-1}}\\
=&\sqrt{V\cdot\dfrac{{p_i}}{{p_i}-1}}\\
\le&\sqrt{V\prod_{\text{prime }p\le V}\dfrac p{p-1}}\\
\xlongequal{\text{Mertens' Third Theorem*}}&\sqrt{V\log V}
\end{aligned}
$$

\*Mertens' 第三定理：$\lim_{n\rightarrow+\infty}\log n\prod_{\text{prime }p\le n}\frac{p-1}p=e^{-\gamma}$，两边同时取倒数得 $\lim_{n\rightarrow+\infty}\frac{\prod_{\text{prime }p\le n}\frac p{p-1}}{\log n}=e^{\gamma}$，也即 $\Omicron(\prod_{\text{prime }p\le n}\frac p{p-1})=\Omicron(\log n)$。其中 $\gamma$ 是 Euler-Mascheroni 常数，定义为 $\lim_{n\rightarrow+\infty}\sum_{i=1}^n\frac 1i-\ln n$，值约为 $0.5772$。该常数由 Euler 开始研究，算到了小数后 6 位~~后来 Mascheroni 将其算到了小数后 32 位，算错了 19 位~~。

```cpp
#pragma GCC optimize(1,2,3,"Ofast","inline")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/exception.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/list_update_policy.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
// using namespace __gnu_pbds;
// tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>T;
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ldb;
//#define umap unordered_map
#define umap __gnu_pbds::cc_hash_table
#define mkp make_pair
#define prque priority_queue
#define emp emplace
#define empb emplace_back
#define empf emplace_front
#define invarg invalid_argument
#define cus_throw(msg) throw invarg(string(msg) + " at " + __FILE__ + ":" + to_string(__LINE__))
random_device rndv;
mt19937 rd(rndv());
const ll inf = 1e6;
const vector<ll> millerrabin = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
const double eps = 1e-8;
inline void enter(){putchar('\n');}
inline void space(){putchar(' ');}
inline ll readll(){ll ret=0,k=1;char c;do{c=getchar();if(c=='-'){k=-1;}}while(('0'>c)|('9'<c));do{ret=(ret<<3)+(ret<<1)+c-48;c=getchar();}while(('0'<=c)&(c<='9'));return ret*k;}
inline void read(ll&x){x=readll();}
inline char readchar(){char ret;do{ret=getchar();}while(ret<=32);return ret;}
inline void read(char&x){x=readchar();}
inline string readstr(){string ret;char c;do{c=getchar();}while(c<=32);do{ret+=c;c=getchar();}while((c>32)&(c!=EOF));return ret;}
inline void read(string&x){x=readstr();}
inline void write(ll x){if(!x){putchar('0');return;}if(x<0){putchar('-');x*=-1;}char op[20]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){putchar(op[cur--]);}}
inline ostream& operator<<(ostream& out, __int128 x){if(!x){out<<"0";return out;}if(x<0){out<<"-";x*=-1;}char op[40]={};ll cur=0;while(x){op[++cur]=x%10+48;x/=10;}while(cur){out<<op[cur--];}return out;}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

const ll MAXN = 2e5 + 5;

ll n, k, a[MAXN], dp[MAXN][40][2], pos[MAXN];
vector<ll> e[MAXN], frac[MAXN], fr2[MAXN], V;

void setdp(ll x, ll pr) {
	if (e[x].size() == bool(pr)) {
		for (ll i : V) {
			if (a[x] % i == 0) dp[x][pos[i]][0] = 0;
			else dp[x][pos[i]][0] = inf;
		}
	}
	for (ll i : V) dp[x][pos[i]][0] = 0;
	for (ll i : e[x]) {
		if (i == pr) continue;
		setdp(i, x);
		for (ll j : V) dp[x][pos[j]][0] += min(dp[i][pos[j]][0], dp[i][pos[j]][1]);
	}
	for (ll i : V) {
		if (a[x] % i) dp[x][pos[i]][0] = inf;
	}
	for (ll i : V) {
		for (ll j : fr2[i]) {
			dp[x][pos[i]][1] = min(dp[x][pos[i]][1], 1 + dp[x][pos[j]][0]);
		}
	}
}

void init() {
	for (ll i = 1; i <= n; ++i) {
		a[i] = 0;
		e[i].clear();
	}
	V.clear();
}
int mian() {
	read(n), read(k);
	for (ll i = 1; i <= n; ++i) read(a[i]);
	for (ll i = 1; i <= a[1]; ++i) if (a[1] % i == 0) pos[i] = V.size(), V.empb(i);
	for (ll i = 1, u, v; i < n; ++i) read(u), read(v), e[u].empb(v), e[v].empb(u);
	for (ll i = 1; i <= n; ++i) {
		for (ll j = 0; j <= V.size(); ++j) dp[i][j][0] = dp[i][j][1] = inf;
	}
	setdp(1, 0);
	ll ans = a[1];
	for (ll i : V) {
		ans = max(ans, a[1] * (1 + (i - 1) * (k > dp[1][pos[i]][0])));
	}
	write(ans), enter();
	return 0;
}

int main() {
	for (ll i = 1; i <= 1000; ++i) {
		for (ll j = i; j <= 1000; j += i) frac[j].empb(i);
		for (ll j : frac[i]) if (j % (i / j) == 0) fr2[i].empb(j);
	}
	ll T;
	read(T);
	while (T--) {
		init();
		mian();
	}
	return 0;
}

;             ;;;;;;;;          ;
;                   ;          ; ;
;                  ;          ;   ;
;                 ;          ;     ;
;                ;          ;;;;;;;;;
;               ;          ;         ;
;              ;          ;           ;
;;;;;;;;;;;   ;;;;;;;;   ;             ;

   ;                        ;
  ;                          ;
 ;                            ;
;                              ;
;                              ;
;                              ;
 ;                            ;
  ;         ;;          ;;   ;
   ;        ;;          ;;  ;
```

---

## 作者：E1_de5truct0r (赞：1)

比较简单的题。（算是 *2600 里相对容易的了吧）

令 $G_i$ 表示 $i$ 子树内的点的 $\gcd$。

首先，由于 $\gcd$ 的性质，一个点 $u$ 一直到根 $1$ 的路径上，$G_i$ 是单调不升的。这意味着对一个子树操作，先操作深度大的节点，可以使答案不劣。

所以可以树形 DP，当我们操作一个点的时候一定意味着其子树内的点不会再操作了。

不难发现朴素做法：就是树形背包，复杂度 $O(n^2)$ 不能接受。

接下来考虑正解做法：观察到值域 $V \leq 1000$，比较小；这也意味着每个点只有最多 $2\sqrt{V}$ 个因数，而且严重跑不满。所以考虑把这个压进状态中。

令 $f_{i,j}$ 表示暂时不在 $i$ 操作，只在其子树内操作，使得其子树内的点全部为 $j$ 的倍数的最小操作次数。这里的 $j$ 显然是 $a_i$ 的因数。

每次转移的时候，对子节点进行考虑：

- 不在子节点操作：贡献为 $f_{v,p}$，需要满足 $v$ 的第 $p$ 个因数等于 $u$ 的第 $j$ 个因数。

- 在子节点操作一次：贡献为 $\min\limits_{k^2\mid j} (f_{v,k}+1)$。

这两种操作都是有可能的，对所有子节点取 $\min$ 之后加起来即为 $f_{i,j}$。

最后的答案显然是 $\max\limits_{i\mid a_1}[f_{1,i} \leq k]\cdot i \cdot a_1$。

把每个数的因数个数粗略看成 $\sqrt{V}$ 级别的，那么复杂度为 $O(n \cdot (\sqrt{V})^2)=O(nV)$。不难发现 $nV \leq 2 \times 10^8$，可以勉强卡过去。

吐槽：是我常数大还是 CF 老年机不行，我加了 fread fwrite 和卡常火车头才勉强以 1980ms 卡过！建议各位写的时候不要用 vector！

[Code & Submission](https://codeforces.com/contest/1778/submission/225602839)

---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1778F)

## 思路

比较傻逼的 $\rm Div2\ F$。

首先每个数都可以跟 $a_1$ 求一遍 $\gcd$，这样显然答案不变。

由于题目的限制，$a_1$ 至多乘一次，考虑枚举它乘了哪个数，显然是 $a_1$ 的某个因子，由于 $a_i \le 1000$，所以 $a_i$ 的因子非常少，我们可以把因子记录到 $\rm DP$ 状态里。

设 $f_{x,i}$ 表示点 $x$ 的子树内都是因子 $i$ 的倍数的最小操作次数。

转移就暴力转移，以 $\mathcal O(s^2)$ 的复杂度合并两个连通块，其中 $s$ 表示 $a_1$ 的因子个数。

我们把一个数 $i$ 表示成以下的形式：$\prod_{k=1}^{s_i} p_{i,k}^{a_{i,k}}$，其中 $p_{i,k}$ 是质数。

然后考虑在自身操作的情况，一个状态 $f_{x,i}$ 能转移到 $f_{x,j}$ 当且仅当所有的 $p_{i,k}=p_{j,k},2 \times a_{i,k} \le a_{j,k}$，且 $s_i=s_j$。

注意特判一些特殊情况，我 $\rm WA$ 了 $11$ 发才过。

时间复杂度 $\mathcal O(ns^2)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
int const N=1e5+10;
int const M=1e3+10;
int f1[M],a[N],n,k,cnt,f[N][M],g[M][M],cet[M][M];
vector<int>b[N],vec,d[M],p[M];
inline void dfs(int x,int fa){
    for (auto v:b[x]){
        if (v==fa) continue;
        dfs(v,x);
        memset(f1,0x3f,sizeof(int)*(vec.size()));
        for (int i=0;i<vec.size();++i)
            for (int j=0;j<vec.size();++j)
                f1[g[i][j]]=min(f1[g[i][j]],f[x][i]+f[v][j]);
        for (int i=0;i<vec.size();++i) f[x][i]=f1[i];
    }
    if (x!=1){
        for (int i=vec.size()-1;~i;--i)
            for (int j=i+1;j<vec.size();++j)
                if (cet[i][j]) f[x][j]=min(f[x][j],f[x][i]+cet[i][j]);
    }
}
inline void solve(){
    cin>>n>>k;--k;int u,v;vec.clear();
    for (int i=1;i<=n;++i) cin>>a[i],a[i]=__gcd(a[i],a[1]),b[i].clear();
    for (int i=1;i<n;++i) cin>>u>>v,b[u].push_back(v),b[v].push_back(u);
    if (k<0) return cout<<a[1]<<'\n',void();
    for (int i=1;i<=a[1];++i) if (a[1]%i==0) vec.push_back(i);
    for (int i=0;i<vec.size();++i)
        for (int j=0;j<vec.size();++j)
            g[i][j]=lower_bound(all(vec),__gcd(vec[i],vec[j]))-vec.begin();
    for (int i=0;i<vec.size();++i){
        d[i].clear();p[i].clear();
        int y=vec[i];for (int j=2;j*j<=y;++j){
            if (y%j==0) d[i].push_back(j),p[i].push_back(0);
            while (y%j==0) y/=j,++p[i][d[i].size()-1];
        }
        if (y^1) d[i].push_back(y),p[i].push_back(0),++p[i][d[i].size()-1];
    }
    for (int i=0;i<vec.size();++i)
        for (int j=i+1;j<vec.size();++j) if (d[i]==d[j]){
            int Max=1;
            for (int k=0;k<d[i].size();++k)
                Max=max(Max,(p[j][k]-p[i][k]+p[i][k]-1)/p[i][k]);
            if (Max>1) cet[i][j]=0;else cet[i][j]=Max;
        }else cet[i][j]=0;
    for (int i=1;i<=n;++i){
        memset(f[i],0x3f,sizeof(int)*(vec.size()));
        a[i]=lower_bound(all(vec),a[i])-vec.begin();
        f[i][a[i]]=0;
    }
    dfs(1,0);
    for (int i=a[1];i;--i) if (f[1][i]<=k) return cout<<vec[a[1]]*vec[i]<<'\n',void();
    return cout<<vec[a[1]]<<'\n',void();
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t;cin>>t;while (t--) solve();
    return 0;
}
```

---

## 作者：RainWetPeopleStart (赞：0)

首先，观察到最后操作 $1$ 一定最优，而此时 $a_1$ 乘上的值一定是此时所有点权的 $\gcd$。

因为随着操作次数的增加，$\gcd$ 是不降的，有一个朴素 DP，就是 $f_{i,j}$ 表示在以 $i$ 为根的子树内操作了 $j$ 次的 $\gcd$ 最大值，使用形如树上背包的转移可以 $O(n^2)$。

但是我们可以优化，在 $\gcd$ 增加时操作次数是不降的，于是就交换第二维和答案，即 $f_{i,j}$ 表示以 $i$ 为根的子树内操作到 $\gcd$ 为 $j$ 的最小操作次数。

我们在转移时考虑是否操作 $i$，则此时一定有 $j\mid a_i$，可得状态数是 $O(nd(V))$ 的，转移时考虑 $f_{v,*}$ 对 $f_{u,x}$ 的贡献 $g_{v,x}$。

1. 操作点 $v$，从 $f_{v,y}$ 贡献到 $g_{v,\gcd(y^2,a_u)}$。

2. 不操作点 $v$，从 $f_{v,y}$ 贡献到 $g_{v,\gcd(y,a_u)}$。

贡献是指 checkmin 操作。

最后让 $f_{u,x}=\sum\limits_{v\in son(u)}g_{v,x}$ 即可。

计算答案可以通过 $f_{1,x}+1$ 与 $k$ 的大小关系，来确定 $a_1$ 是否能取到 $xa_1$。

这样是 $O(nd^2(V))$ 的，瓶颈在 $f\rightarrow g$ 的部分。

发现这一部分可以看作一个维度为 $w(a_u)$ 的高维后缀 $\min$，可以把复杂度优化到 $O(nd(V)w(V))$。

---

## 作者：Helenty (赞：0)

容易发现从叶子往根操作是不劣的。

考虑 $u$ 下面再怎么操作子树 $u$ 的最大公约数也是 $a_u$ 的因数。

因此我们可以记录 $f_{u,x}$ 表示 $u$ 子树搞完了且最大公约数是 $x$ 的倍数的最小代价。

显然 $x$ 是 $a_u^2$ 的因数，那么这个级别就是 $d(V^2)$ 的。

考虑转移到 $f_{u,x}$，如果 $x|a^2_v$ 那么直接用 $f_{v,x}$ 即可，否则无解。

复杂度就是 $O(nd(V^2))$。

实际上也可以枚举 $a_u$ 变成 $a_u$ 乘它的因数。

然后注意到一个数应当在祖先 $\log\log V$ 次操作内合法。

我们只需要考虑取到最小值的质因数的幂次。

然后就是 $O(nd(V)\log\log V)$ 的了。

---

## 作者：居然有个高手 (赞：0)

咋大家都是 $O(nV)$，来个神秘复杂度做法。

因为每个点只能操作一次，所以最终答案一定是 $a_1$ 乘上它的某个因数。我们可以枚举这个因数，记作 $x$，判定是否可行。

将 $x$ 分解为 $\prod p_i^{a_i}$，可以先特判若 $\exist 1\le j \le n,p_i \nmid a_j $，则一定不可行。在此基础上，我们可以发现，对于点 $x$，我们只关心那些可以在某个质因数的指数上取到最小值的 $a_j$，而我们发现，在一次操作后，取到最小值的 $a_j$ 的指数将会翻倍。因此，必然存在一种方案，使得一个点在被其祖先操作 $\log \log V$ 次后合法。

这使得我们可以考虑记录一个状态 $dp_{i,j}$ 表示 $i$ 子树内还需要 $j$ 次操作时，子树内操作次数和的最小值。定义 $b_j$ 为还需要 $j$ 次操作时的值，则初始状态为 $dp_{i,j} = [j \nmid a_i]inf$。转移则 $dp_{i,j} = \sum_{y \in son(i)}dp_{y,j}$。在其子树内转移完毕，且 $i \not = 1$ 时，转移 $dp_{i,j} = \min(dp_{i,j},dp_{i,j+1}+1)$。

最后，若 $dp_{1,0} \le k-1$，则 $x \times a_1$ 是可以取到的答案。

时间复杂度：$O(nd(V)\log\log V)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5,inf=1e9;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*f;
}
int n,head[N],T,tot,a[N],k,b[5];
long long dp[N][5];
vector<pair<int,int>>v;
struct edge{
    int nxt,to;
}e[N<<1];
inline void add(int a,int b){
    e[++tot]={head[a],b};head[a]=tot;
}
inline void dfs(int x,int fa){
    for(int i = 0;i<5;i++){
        if(a[x]%b[i]==0)dp[x][i]=0;
        else dp[x][i]=inf;
    }
    for(int i = head[x],y;i;i=e[i].nxt){
        y=e[i].to;
        if(y!=fa){
            dfs(y,x);
            for(int j = 0;j<5;j++)dp[x][j]+=dp[y][j];
        }
    }
    if(x^1)for(int j = 0;j<4;j++)dp[x][j]=min(dp[x][j],dp[x][j+1]+1);
    // for(int j = 0;j<5;j++)cout<<x<<' '<<j<<' ' <<dp[x][j]<<endl;
}
int main(){
    T=read();   
    while(T--){
        tot=0;
        n=read();k=read();
        for(int i = 1;i<=n;i++)a[i]=read(),head[i]=0;
        for(int i = 1,x,y;i<n;i++)x=read(),y=read(),add(x,y),add(y,x);
        if(!k){
            printf("%d\n",a[1]);
            continue;
        }
        int ans = a[1];
        for(int i = 2;i<=a[1];i++){
            if(a[1]%i == 0){
                int x = i;v.clear();
                for(int j = 2;j<=x;j++){
                    if(x%j==0){
                        v.push_back({j,0});
                        while(x%j==0)v[v.size()-1].second++,x/=j;
                    }
                }
                if(x^1)v.push_back({x,1});
                for(int j = 0;j<5;j++){
                    b[j] = 1;
                    for(auto [h,o] : v){
                        o=(o-1)/(1<<j)+1;
                        while(o--)b[j]*=h;
                    }
                }
                dfs(1,0);
                if(dp[1][0]<=k-1)ans=a[1]*i;
                // cout<<' '<<a[1]<<' '<<i<<' '<<dp[1][0]<<endl;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

首先不难证明不操作根节点一定不优，因此我们考虑操作根节点的情况。

现在我们的问题转化为了：最大化操作根节点前的整个树的节点权值的最大公约数。

由于可能的最大公约数值只有 $\mathcal{O}(\sqrt{V})$ 种。因此我们考虑将其压入状态进行动态规划。

设 $f_{u, j}$ 表示使得 $u$ 子树内的所有节点点权和根节点点权最大公约数为 $j$ 的最小操作次数。转移时枚举子树的最大公约数即可，复杂度为 $\mathcal{O}(n \sqrt{V}^2) = \mathcal{O}(nV)$，可以通过。

[Submission.](https://codeforces.com/contest/1778/submission/243477401)

---

