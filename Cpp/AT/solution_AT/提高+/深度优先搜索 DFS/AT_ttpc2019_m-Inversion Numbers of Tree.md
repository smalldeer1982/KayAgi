# Inversion Numbers of Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ttpc2019/tasks/ttpc2019_m

$ 1 $ から $ N $ までの番号がつけられた $ N $ 個の頂点を持つ木があります。 この木の $ i $ 番目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。

この木に対し、頂点 $ r $ を根としたときの転倒数を以下のように定義します。

- 頂点 $ r $ から頂点 $ u $ の単純パスの端点または辺上に頂点 $ v $ が含まれるような組 $ (u,\ v)\ (u\ \lt\ v) $ の個数

$ 1 $ 以上 $ N $ 以下の全ての整数 $ r $ に対し、頂点 $ r $ を根としたときの転倒数を求めてください。

## 说明/提示

### 制約

- 入力は全て整数
- $ 2\ \leq\ N\ \leq\ 10^{5} $
- $ 1\ \leq\ A_i,\ B_i\ \leq\ N $
- 与えられるグラフは木である。

### Sample Explanation 1

\- 頂点 $ 1 $ を根としたときの転倒数は、$ (u,\ v)\ =\ (2,\ 3) $ より $ 1 $ です - 頂点 $ 2 $ を根としたときの転倒数は、$ (u,\ v)\ =\ (1,\ 2),\ (1,\ 3) $ より $ 2 $ です - 頂点 $ 3 $ を根としたときの転倒数は、$ (u,\ v)\ =\ (1,\ 3),\ (2,\ 3) $ より $ 2 $ です。

## 样例 #1

### 输入

```
3
1 3
2 3```

### 输出

```
1
2
2```

## 样例 #2

### 输入

```
7
1 4
1 6
2 4
2 5
3 4
4 7```

### 输出

```
2
3
4
3
7
7
9```

# 题解

## 作者：OldDriverTree (赞：0)

双倍经验：ABC337G。

# Solution

换根 $\texttt{DP}$，设 $f_x$ 表示以 $x$ 为根的逆序对个数。

先求出 $f_1$ 的值，枚举路径的另一个端点 $u$，$u$ 对 $f_1$ 的贡献就是 $u$ 到 $1$ 的路径上大于 $u$ 的节点个数，$\texttt{DFS}$ 一遍，拿树状数组搞一下就行了。

再考虑求出 $f_{fa_u}$ 后，怎么求出 $f_u$ 的值。

先考虑对于在 $u$ 子树内的节点 $x$ 对 $f_u$ 贡献的变化，由于到 $u$ 的路径上都少了一个节点 $fa_u$，答案就减少了 $\sum_{x\in tree_u} [y<fa_x]$。

再考虑子树外的节点 $x$ 对 $f_u$ 贡献的变化，由于到 $u$ 的路径上都多了一个节点 $u$，答案就增加了 $\sum_{x\not\in tree_u} [x<u]$。考虑补集转化，用整棵树的个数减去子树内的个数，就是 $u-1-\sum_{x\in tree_u} [x<u]$。

那么只需要维护 $u$ 子树内的所有数构成的树状数组就能求出 $f_u$，$\texttt{DSU on tree}$ 即可，时间复杂度 $O(n\log^2 n)$。

# Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+1;
int siz[N],son[N];
vector<int> g[N];
long long f[N];
int n,Son,T[N];
int w[N];

int read() {
	int x=0; char c=0; while (!isdigit(c) ) c=getchar();
	while (isdigit(c) ) x=(x<<3)+(x<<1)+(c&15),c=getchar();
	return x;
}
void add(int x,int v) { while (x<=n) T[x]+=v,x+=x&-x; }
int query(int x,int sum=0) { while (x) sum+=T[x],x&=x-1; return sum; }

void dfs1(int u,int fa)
{
	siz[u]=1,add(u,1);
	f[1]+=query(n)-query(u);
	for (int v:g[u]) if (v^fa) {
		dfs1(v,u),siz[u]+=siz[v];
		if (siz[v]>siz[son[u] ]) son[u]=v;
	}
	add(u,-1);
}
void add(int u,int fa,int w) {
	add(u,w); for (int v:g[u])
	if (v^fa&&v^Son) add(v,u,w);
}
void dfs(int u,int fa) {
	for (int v:g[u]) if (v^fa&&v^son[u]) dfs(v,u),add(v,u,-1);
	if (son[u]) dfs(son[u],u),Son=son[u]; add(u,fa,1),Son=0;
	if (fa) w[u]=-query(fa-1)+u-1-query(u-1);
}
void solve(int u,int fa) {
	for (int v:g[u]) if (v^fa)
	f[v]=f[u]+w[v],solve(v,u);
}
main()
{
	n=read();
	for (int i=1,x,y;i<n;i++)
	{
		x=read(),y=read();
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfs1(1,0),dfs(1,0),solve(1,0);
	for (int i=1;i<=n;i++) printf("%lld\n",f[i]);
	return 0;
}
```

---

