# Edge Elimination

## 题目描述

You are given a tree (connected, undirected, acyclic graph) with $ n $ vertices. Two edges are adjacent if they share exactly one endpoint. In one move you can remove an arbitrary edge, if that edge is adjacent to an even number of remaining edges.

Remove all of the edges, or determine that it is impossible. If there are multiple solutions, print any.

## 说明/提示

Test case $ 1 $ : it is possible to remove the edge, because it is not adjacent to any other edge.

Test case $ 2 $ : both edges are adjacent to exactly one edge, so it is impossible to remove any of them. So the answer is "NO".

Test case $ 3 $ : the edge $ 2-3 $ is adjacent to two other edges. So it is possible to remove it. After that removal it is possible to remove the remaining edges too.

## 样例 #1

### 输入

```
5
2
1 2
3
1 2
2 3
4
1 2
2 3
3 4
5
1 2
2 3
3 4
3 5
7
1 2
1 3
2 4
2 5
3 6
3 7```

### 输出

```
YES
2 1
NO
YES
2 3
3 4
2 1
YES
3 5
2 3
2 1
4 3
NO```

# 题解

## 作者：OtoriEmu (赞：11)

提供一个写着比较简便的写法。

注意到一条边 $\langle u,v \rangle$ 能删除，当且仅当 $(d_u+d_g) \bmod 2 =0$（其中 $d_u$ 表示 $u$ 的度数）。

那么从叶子开始向上分别考虑每个点，对于 $u$ 这个点可以得到类似 $\langle fa_u,u \rangle$ 这条边需要在 $d_{fa_u} \bmod 2 = 0/1$（其中 $fa_u$ 表示 $u$ 在树上的父亲，根可以任意指定）时被删除。

具体的，分析一个点 $u$ 周边的点一个一个被删除，$d_u$ 的变化。注意到 $d_u$ 为偶数的时刻共有 $\lfloor \frac{d}{2} \rfloor$ 个，而为奇数则有 $\lceil \frac{d}{2} \rceil$ 个。现在未确定的边是 $\langle fa_u,u \rangle$，要按一个奇数一个偶数的删除可能不成功，这个时候我们就要删除 $\langle fa_u,u \rangle$ 跳过一次不够的删除，同时这个时候就能够对无解进行判定。同时注意到根没有父边，不能特殊处理。

最后考虑递归构造。如果现在需要删除父边可以直接删除，否则就递归下去删除那棵子树（这是为了保证父边度数奇偶性正确）。

可以查看[具体实现](https://codeforces.com/problemset/submission/1667/177661966)。

---

## 作者：yhk1001 (赞：11)

> [题目传送门](https://www.luogu.com.cn/problem/CF1667D)

一道有趣的题， 考察树形 dp 和构造。

先考虑如何判定。按照一般套路，我们考虑以 $u$ 为根的子树能否删完所有边。但状态还不完善，因为连接 $u$ 和父亲的边也会影响奇偶性。综上，我们设 $dp_{u, 0/1}$ 表示以 $u$ 为根的子树，连接 $u$ 和 $fa$ 的边需要在 $u$ 还连接着偶数或奇数个儿子时删去，能否删完子树中所有边。

设且最终按照 $v_{1}\ v_{2}\ \cdots v_{son}$ 的顺序删完 $u$ 和儿子之间的边，且连接 $u$ 和父亲的边在 $v_{k},\ v_{k + 1}$ 之间删去。分类讨论需要满足的条件。

- $1.1 \ u$ 有奇数个儿子，$<u,\ fa>$ 要在 $u$ 有奇数个儿子时删去

$$dp_{v_{1}, 1} \ \land\ dp_{v_{2}, 0} \ \land\ \cdots\ \land\ dp_{v_{k}, 0} \ \land\ dp_{v_{k + 1}, 0} \ \land\ \cdots \ dp_{v_{son - 1}, 1} \ \land\ dp_{v_{son}, 0}= \text{true}$$
$$\left(\text{0 比 1 多 1 个}\right)$$

- $1.2 \ u$ 有奇数个儿子，$<u,\ fa>$ 要在 $u$ 有偶数个儿子时删去

$$dp_{v_{1}, 1} \ \land\ dp_{v_{2}, 0} \ \land\ \cdots\ \land\ dp_{v_{k}, 1} \ \land\ dp_{v_{k + 1}, 1} \ \land\ \cdots \ dp_{v_{son - 1}, 1} \ \land\ dp_{v_{son}, 0}= \text{true}$$
$$\left(\text{1 比 0 多 1 个}\right)$$

- $2.1 \ u$ 有偶数个儿子，$<u,\ fa>$ 要在 $u$ 有奇数个儿子时删去

$$dp_{v_{1}, 0} \ \land\ dp_{v_{2}, 1} \ \land\ \cdots\ \land\ dp_{v_{k}, 0} \ \land\ dp_{v_{k + 1}, 0} \ \land\ \cdots \ dp_{v_{son - 1}, 1} \ \land\ dp_{v_{son}, 0}= \text{true}$$
$$\left(\text{0 比 1 多 2 个}\right)$$

- $2.2 \ u$ 有偶数个儿子，$<u,\ fa>$ 要在 $u$ 有偶数个儿子时删去

$$dp_{v_{1}, 0} \ \land\ dp_{v_{2}, 1} \ \land\ \cdots\ \land\ dp_{v_{k}, 1} \ \land\ dp_{v_{k + 1}, 1} \ \land\ \cdots \ dp_{v_{son - 1}, 1} \ \land\ dp_{v_{son}, 0}= \text{true}$$
$$\left(\text{0 和 1 个数相等}\right)$$

不难看出，$v_{1}\ v_{2}\ \cdots\ v_{k}$ 和 $v_{k + 1}\ \cdots\ v_{son - 1}\ v_{son}$ 都是 $\text{0 1}$ 交替的，整体上满足的数量关系也已经列在上面。我们需要统计三个数：

$$zero = \sum\limits_{v\ \in\ son}\left[\ dp_{v, 0} = \text{true} \ \land\ dp_{v, 1} = \text{false} \ \right]$$

$$one = \sum\limits_{v\ \in\ son}\left[\ dp_{v, 0} = \text{false} \ \land\ dp_{v, 1} = \text{true} \ \right]$$

$$all = \sum\limits_{v\ \in\ son}\left[\ dp_{v, 0} = \text{true} \ \land\ dp_{v, 1} = \text{true} \ \right]$$

更新 $dp_{u, 0/1}$ 时，依据上面三个数判断一下就好了。若存在 $u$ 使得 $dp_{u, 0/1}$ 均为假，或根节点不满足要求，则无解，否则有解。输出方案也不难，我们只需记录哪些点需要在 $<u,\ fa>$ 之前删，最后递归输出即可。

如果有不明白的，可以对照代码看看。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 2e5, M = N << 1;
int n;
int head[N + 5], to[M + 5], nxt[M + 5], tot;
void add_edge(int u, int v)
{
	tot++;
	to[tot] = v;
	nxt[tot] = head[u];
	head[u] = tot;
	return ;
}
void add(int u, int v)
{
	add_edge(u, v);
	add_edge(v, u);
	return ;
}

bool dp[N + 5][2], fail;
int son[N + 5];
vector<int> before_cut[N + 5][2], after_cut[N + 5][2];
void dfs(int u, int fa)
{
	vector<int> Zero, One, All;
	for (int i = head[u]; i; i = nxt[i])
	{
		int v = to[i];
		if (v == fa)
			continue;
		dfs(v, u);
		if (fail)
			return ;
		if (!dp[v][0] && !dp[v][1])
			return fail = true, void();
		son[u]++;
		if (dp[v][0] && !dp[v][1])
			Zero.push_back(v);
		if (!dp[v][0] && dp[v][1])
			One.push_back(v);
		if (dp[v][0] && dp[v][1])
			All.push_back(v);
	}
	if (!son[u])
	{
		dp[u][0] = true;
		dp[u][1] = false;
		return ;
	}
	vector<int> zero, one, all;
	if (son[u] & 1)
	{
		unsigned int Less = son[u] >> 1, More = son[u] - Less;
		dp[u][1] = (Zero.size() <= More) && (One.size() <= Less);
		dp[u][0] = (Zero.size() <= Less) && (One.size() <= More);
		zero = Zero, one = One, all = All;
		if (dp[u][1])
		{
			while (zero.size() < More)
			{
				zero.push_back(all.back());
				all.pop_back();
			}
			while (one.size() < Less)
			{
				one.push_back(all.back());
				all.pop_back();
			}
			for (unsigned int i = 0; i < one.size(); i++)
			{
				after_cut[u][1].push_back(zero[i]);
				after_cut[u][1].push_back(one[i]);
			}
			after_cut[u][1].push_back(zero.back());
		}
		zero = Zero, one = One, all = All;
		if (dp[u][0])
		{
			while (zero.size() < Less)
			{
				zero.push_back(all.back());
				all.pop_back();
			}
			while (one.size() < More)
			{
				one.push_back(all.back());
				all.pop_back();
			}
			for (unsigned int i = 0; i < zero.size(); i++)
			{
				before_cut[u][0].push_back(one[i]);
				before_cut[u][0].push_back(zero[i]); 
			}
			before_cut[u][0].push_back(one.back());
		}
	}
	else
	{
		unsigned int Middle = son[u] >> 1;
		dp[u][1] = (Zero.size() <= Middle + 1) && (One.size() <= Middle - 1);
		dp[u][0] = (Zero.size() <= Middle) && (One.size() <= Middle);
		zero = Zero, one = One, all = All;
		if (dp[u][1])
		{
			while (zero.size() < Middle + 1)
			{
				zero.push_back(all.back());
				all.pop_back();
			}
			while (one.size() < Middle - 1)
			{
				one.push_back(all.back());
				all.pop_back();
			}
			before_cut[u][1].push_back(zero.back());
			zero.pop_back();
			for (unsigned int i = 0; i < one.size(); i++)
			{
				after_cut[u][1].push_back(zero[i]);
				after_cut[u][1].push_back(one[i]);
			}
			after_cut[u][1].push_back(zero.back());
		}
		zero = Zero, one = One, all = All;
		if (dp[u][0])
		{
			while (zero.size() < Middle)
			{
				zero.push_back(all.back());
				all.pop_back();
			}
			while (one.size() < Middle)
			{
				one.push_back(all.back());
				all.pop_back();
			}
			for (unsigned int i = 0; i < zero.size(); i++)
			{
				after_cut[u][0].push_back(one[i]);
				after_cut[u][0].push_back(zero[i]);
			}
		}
	}
	return ;
}
void print(int u, int fa, int type)
{
	int sum = son[u] + 1;
	for (unsigned int i = 0; i < before_cut[u][type].size(); i++)
	{
		int v = before_cut[u][type][i];
		print(v, u, (sum - 1) & 1);
		sum--;
	}
	if (u != 1)
		printf("%d %d\n", u, fa);
	sum--;
	for (unsigned int i = 0; i < after_cut[u][type].size(); i++)
	{
		int v = after_cut[u][type][i];
		print(v, u, (sum - 1) & 1);
		sum--;
	}
	return ;
}

void clear()
{
	for (int i = 1; i <= n; i++)
	{
		head[i] = son[i] = 0;
		dp[i][0] = dp[i][1] = false;
		before_cut[i][0].clear();
		before_cut[i][1].clear();
		after_cut[i][0].clear();
		after_cut[i][1].clear();
	}
	fail = false, tot = 0;
	return ;
}
void solve()
{
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++)
	{
		scanf("%d%d", &u, &v);
		add(u, v);
	}
	dfs(1, 1);
	if (fail || !dp[1][son[1] & 1])
		printf("NO\n");
	else
	{
		printf("YES\n");
		print(1, 1, son[1] & 1);
	}
	clear();
	return ;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
```

---

## 作者：Wuyanru (赞：5)

题解区似乎没有和我相同的做法，那我来补一个很自然的做法。

[题目链接](https://www.luogu.com.cn/problem/CF1667D)。

## 题意

给定一棵 $n$ 个点的树，称两条边相邻当且仅当这两条边有公共端点。

你需要按某种顺序删掉树上的 $n-1$ 条边，每一次删的边需要保证，剩余的其他边中，和这条边相邻的恰好有偶数条。

判断无解或构造方案。

$1\le n\le 2\times 10^5$。

## 题解

下文中，树上某条路径的距离或长度，均指这条路径上的边数。

直接想比较困难，先来考虑一条链的情况。

手玩可以发现，当且仅当链的长度为奇数的时候有解。

证明很简单，首先 $1$ 有解，剩下的可以归纳法证：

对于长为奇数的链，先拿走第二条边，就可以分成两个奇数的小链，有解。

对于长为偶数的链，无论拿走哪一条边，都会产生另外一条偶数的链，所以无解。

再来考虑树的情况，手玩样例，大胆猜测：

对于一棵树，有解的充要条件是，其可以划分为若干条长度为奇数的链，使得所有链没有共同的**端点**（即一个点最多作为一条链的一端）。

---

证明分为两部分：有解的树一定满足上面的条件，和上面的条件有解，两部分都不难。先来证明第一部分。

首先有一些显然的结论，设 $d_u$ 为 $u$ 这个点的度数。

那么当 $d_u$ 为奇数的时候，$u$ 一定为某条链的端点（否则一条链只会对 $u$ 造成偶数个度数，$d_u$ 应该为偶数）。

当 $d_u$ 为偶数的时候，$u$ 一定不是任何链的端点（否则 $u$ 一定作为 $\ge 2$ 条链的端点，不符合条件）。

使用归纳法证明，$n=1$ 的时候成立（划分为 $0$ 条链，显然我们可以认为所有链长度都是奇数）。

当 $n>1$ 的时候，考虑任何一组解删去的第一条边，设这条边为 $(u,v)$。

1. 当 $d_u$ 与 $d_v$ 都是奇数的时候，我们可以将 $(u,v)$ 看作是一条长度为 $1$ 的链，此时我们将整棵树划分为两部分。

   而删去这条边之后，$d_u$ 与 $d_v$ 都是偶数，$u$ 和 $v$ 就不可能是其他链的端点，满足一个点最多是一个链端点的假设。

   所以只需要划分为的两部分都有解，这棵树就满足我们的条件。

   而对于一棵有解的树，这两部分显然都有解。

2. 当 $d_u$ 与 $d_v$ 都是偶数的时候，考虑先删去 $(u,v)$ 这两条边，对两棵子树分别构造。

   删去这条边后，对这两部分来说，$d_u$ 和 $d_v$ 都是奇数，那么他们应各是一条奇数链的端点。

   而两条奇数链和一条边拼一起，还是一条奇数链，这样我们就递归完成了构造。

   所以如果划分为的两部分都有解，我们还是能够将整棵树划分为若干条端点不同的奇数链。

综上所述，无论是那种情况，我们都能对分成的两棵子树分别构造，然后进行合并。

所以我们使用归纳法证明了，如果有解，那么一定整棵树一定可以划分为若干条链，使得所有链端点互不相同。

---

假设我们已经将这棵树划分为若干奇数链，考虑如何构造一组解。

考虑每一次删除一条完整的链（链内部的顺序，与单链相同），这样我们就不需要考虑某条链删了一半的情况了。

考虑什么时候，删除一条链是合法的。

容易发现，条件共有 $2$ 个。

1. 对于当前链的端点，这个点的度数是奇数。
2. 对于当前链的中间点，这个点的度数是偶数。

对于链的端点来说，由于没有某条链删了一半的情况，所有链的端点也互不重合，可以发现第 $1$ 个条件一直满足。

对于链的中间点来说，可以发现，若另外一条链穿过了它，只会对度数造成 $2$（偶数）的贡献，没有影响。所以我们只需要考虑这个点作为其他链的顶点的情况。

整理一下，可以发现条件为，链上每一点都不是其他链的端点。

那么我们显然可以构造一组合法的删链顺序。

对于一个点来说，我们可以先递归构造其所有子树的方案，然后在根的位置合并即可（优先删掉，根作为端点的链在的子树）。

这样我们就证明了，满足条件的树一定有解。

---

具体实现：

首先我们需要把整棵树划分为若干长度为奇数的链。

这个可以直接 dfs，然后在每一个点贪心合并所有儿子传上来的链即可（显然，一个儿子会传上来恰好一条链，所以这部分不难）。

对于确定删链的顺序来说，上面讲的构造是可行的，但其实还有另一种方法，就是拓扑排序，可能相对来说更好写。

## 代码

[代码](https://www.luogu.com.cn/paste/tqhwisyj)。

感谢观看！

---

## 作者：ningago (赞：1)

考虑剥叶子。

首先不难发现，一条边被删当且仅当其两端点（当前）度数的奇偶性相同。

所以一个叶子的父边被删当且仅当其父点的度数为奇数。

考虑普遍一点的情况：$x$ 的儿子都是叶子，并且 $x$ 有一条父边。此时该子树（包括父边，后同）有解当且仅当 $x$ 有不多于两个儿子边（不算父边）。其中有两个儿子的条件为：父边被删时两边的度数都是偶数。

考虑更普遍一点的情况：考虑 $x$ 的子树，$x$ 有一条父边，有 $c_0$ 条儿子边的限制是偶数，$c_1$ 条儿子边的限制是奇数。

令 $f(a,b)$ 表示一个没有父边的点，分别有 $a$ 条偶数限制，和 $b$ 条奇数限制，是否可行。手推不难发现 $f(a,b)=[\left\lfloor \dfrac{a+b}{2}\right\rfloor=a]$，此式也等于 $[\left\lceil \dfrac{a+b}{2}\right\rceil=b]$

于是 $x$ 子树有解的条件为 $f(c_0+1,c_1)$ 或 $f(c_0,c_1+1)$ 成立，其分别对应了父边的限制为 偶数/奇数。

于是可以从叶子向上递推，到根时直接检查 $f$ 是否成立即可。

考虑构造方案，令 $0/1$ 表示一条任意的奇/偶边（不重复），按照上述过程将父边与儿子边放在一起考虑，按 $1-0-1-\cdots-0-1$（此时总边数是奇数）或 $0-1-0-\cdots-0-1$（此时总边数是偶数）的**相对顺序**排列边即可。

由于是相对顺序，使用拓扑排序即可构造一组方案。

复杂度 $O(n)$。

```cpp
#define N 300010
int n;
int h[N], e[N << 1], ne[N << 1], idx = -1;
void add_edge(int x, int y) { ne[++idx] = h[x], h[x] = idx, e[idx] = y; }
void add(int x, int y) { add_edge(x, y), add_edge(y, x); }
int val[N];
bool check(int x, int y) /* 0 1 */ { return x == (x + y) / 2; }
std::vector <int> vec[N];
int ru[N];
void Add(int x, int y) { vec[x].push_back(y), ru[y]++; }

bool dfs1(int k, int fa)
{
	int c0 = 0, c1 = 0;
	for(int i = h[k]; ~i; i = ne[i])
	{
		int nx = e[i]; if(nx == fa) continue;
		if(!dfs1(nx, k)) return 0;
		val[nx] ? c1++ : c0++; 
	}
	if(!fa && !check(c0, c1)) return 0;
	if(check(c0 + 1, c1)) { val[k] = 0; return 1; }
	if(check(c0, c1 + 1)) { val[k] = 1; return 1; }
	return 0;
}
int sta[N][2];
void dfs2(int k, int fa, int in_edge)
{
	for(int i = h[k]; ~i; i = ne[i])
	{
		int nx = e[i]; if(nx == fa) continue;
		dfs2(nx, k, i);
	}
	int c0 = 0, c1 = 0;
	for(int i = h[k]; ~i; i = ne[i])
	{
		int nx = e[i]; if(nx == fa) continue;
		int id = (i >> 1) + 1;
		val[nx] ? sta[++c1][1] = id : sta[++c0][0] = id; 
	}
	if(fa)
	{
		if(!val[k]) sta[++c0][0] = (in_edge >> 1) + 1;
		else        sta[++c1][1] = (in_edge >> 1) + 1;
	}
	if((c0 + c1) & 1) 
	{ for(int i = 1; i <= c0; i++) Add(sta[i][1], sta[i][0]), Add(sta[i][0], sta[i + 1][1]); }
	else 
	{ for(int i = 1; i <= c0; i++) Add(sta[i][0], sta[i][1]);
	  for(int i = 1; i <  c0; i++) Add(sta[i][1], sta[i + 1][0]); }	
}
int q[N], head, tail;
void solve()
{
	n = read();
	idx = -1; for(int i = 0; i <= n + 1; i++) h[i] = -1, vec[i].clear(), ru[i] = 0;
	for(int i = 1, x, y; i < n; i++) x = read(), y = read(), add(x, y);
	if(!dfs1(1, 0)) return printstr("NO\n");
	printstr("YES\n");
	dfs2(head = 1, tail = 0, -1);
	for(int i = 1; i < n; i++) if(!ru[i]) q[++tail] = i;
	for(; head <= tail; )
	{
		int k = q[head++];
		print(e[(k - 1) << 1    ], ' '); 
		print(e[(k - 1) << 1 | 1], '\n'); 
		for(int nx : vec[k]) if(!--ru[nx]) q[++tail] = nx;
	}
}
```

---

