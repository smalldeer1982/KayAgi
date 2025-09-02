# [ICPC 2025 NAC] Circle of Leaf

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/at1ek3bh.png)

图片来自 [Wikimedia Commons](https://commons.wikimedia.org/wiki/File:Ouroboros-Zanaq.svg)

## 题目描述

你的朋友给了你一棵有根树：一个包含 $N$ 个节点和 $N-1$ 条边的连通图。树的节点编号为 $1$ 到 $N$，其中节点 $1$ 是树的根，其他节点的编号是任意的。

然而，你最近了解到衔尾蛇（Ouroboros），一种古老的神话蛇，它咬住自己的尾巴，象征着一个无始无终的循环。你不喜欢这棵树的清晰结构——根是起点，叶子是终点，因此你决定彻底改变这棵树的结构，构建一种新的图，你称之为 *衔尾蛇图*。

为了构造这个衔尾蛇图，你取出树的所有叶子节点（没有直接子节点的节点），并在每个叶子和根之间添加特殊的“叶子”边。**如果某个叶子已经有一条连接到根的边，你仍然会添加一条重复的边。**

在这种特殊的图结构下，你可以通过删除某些边的子集来生成许多不同的树。在衔尾蛇的精神下，根和叶子的身份会随着删除的边而变化。问：通过从衔尾蛇图中删除某些边的子集，可以生成多少种不同的树？如果两棵树有一条边存在于其中一棵树但不存在于另一棵树，则认为它们是不同的。（如果一条普通边和一条“叶子”边连接同一对节点，它们被视为不同的边。）由于树的数量可能很大，请将答案对 $998\,244\,353$ 取模。

## 说明/提示

在下面的示意图中，左侧子图展示了样例输入 1 对应的衔尾蛇图，其中原始树边用黑色实线表示，新增的“叶子”边用红色虚线表示。右侧的树展示了从衔尾蛇图中删除某些边后形成的 $72$ 种可能的不同树之一：在这个例子中，原始边 $6$--$5$ 和 $1$--$3$ 以及“叶子”边 $1$--$8$ 和 $1$--$4$ 被删除了。

![](https://cdn.luogu.com.cn/upload/image_hosting/ljg58dpq.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
8
1 3
3 2
1 4
1 7
7 6
6 5
6 8```

### 输出

```
72```

# 题解

## 作者：CQ_Bab (赞：3)

# 前言
因为这题的题号（比较有意义）所以做了。

nnn 还是太强了，膜拜。
# 思路
考虑树形 dp，我们定义 $f_{i,0/1}$ 表示以 $i$ 为根的子树不考虑其上面的边是否与根联通的方案数，考虑转移。

- 如果不删这条边，那么一定不能出现两棵子树都是 $1$ 的情况，$f_{x,0}=f_{x,0}\times f_{to,0},f_{x,1}=f_{x,1}\times f_{to,0}+f_{to,1}\times f_{x,0}$。
- 如果断掉这条边，$f_{x,1}=f_{x,1}\times f_{to,1},f_{x,0}=f_{x,0}\times f_{to,1}$。

然后把这两种情况合并一下就行了，注意要考虑一下更新的顺序，然后初始化就是如果是根则 $f_{x,1}=1$ 否则如果是叶子节点则 $f_{x,1}=f_{x,0}=1$ 否则 $f_{x,0}=1$（毕竟它既不是根也不考虑上面的边）。
# 代码
```cpp
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace std;
#define pb push_back
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rep1(i,x,y) for(register int i=x;i>=y;--i)
#define int long long
#define fire signed
#define il inline
template<class T> il void print(T x) {
	if(x<0) printf("-"),x=-x;
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
template<class T> il void in(T &x) {
    x = 0; char ch = getchar();
    int f = 1;
    while (ch < '0' || ch > '9') {if(ch=='-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = (x << 3) + (x << 1) + (ch ^ 48); ch = getchar(); }
    x *= f;
}
int T=1;
const int N=2e5+10,mod=998244353;
vector<int>v[N];
int f[N][2],n;
void dfs(int x,int fa) {
	int cnt=0;
	if(x==1) {
		f[x][1]=1;
	}else {
		if(v[x].size()==1) f[x][0]=f[x][1]=1;
		else f[x][0]=1;
	}
	for(auto to:v[x]) {
		if(to==fa) continue;
		cnt++;
		dfs(to,x);
		f[x][1]=(f[x][1]*f[to][0]+f[x][0]*f[to][1]+f[x][1]*f[to][1])%mod;
		f[x][0]=(f[x][0]*f[to][0]+f[x][0]*f[to][1])%mod;
	}
}
void solve() {
	in(n);
	rep(i,1,n-1) {
		int a,b;
		in(a),in(b);
		v[a].pb(b);
		v[b].pb(a);
	}
	f[1][1]=1;
	dfs(1,0);
	printf("%lld\n",f[1][1]);
}
fire main() {
	while(T--) {
		solve();
	}
	return false;
}
```

行稳致远。

---

## 作者：hyk2019 (赞：2)

考虑遍历节点 $1$ 的每个儿子，对以这个儿子为根的节点 $1$ 的子树（包括节点 $1$）进行 DP。例如，样例中的图可以拆分为以下 $3$ 个子图，其中红色边表示原图中的“叶子”边，子图的“根节点”都是 $1$ 的儿子。

![](https://cdn.luogu.com.cn/upload/image_hosting/1gjom147.png)

一个子图能够成为一棵树，当且仅当从“根节点”出发到节点 $1$ 有且仅有一条路径。

对每个子图进行 DP。设 $f_{i,0}$ 表示节点 $i$ 到节点 $1$ **恰好存在一条路径**的方案数，$f_{i,1}$ 表示节点 $i$ 到节点 $1$ **不存在任何路径**的方案数，这些路径**都不能经过其祖先**（当然“根节点”没有祖先）。

从每个子图的“根节点”开始遍历。对于一条边 $E:u\to v$，加入这条边及其子树后，恰好存在一条路径的方案包括：

- 原来不存在任何路径，$E$ 连通，子树恰好存在一条路径，一共有 $f_{u,1}\cdot f_{v,0}$ 种方案；
- 原来恰好存在一条路径，$E$ 连通，子树不存在任何路径，一共有 $f_{u,0}\cdot f_{v,1}$ 种方案；
- 原来恰好存在一条路径，$E$ 不连通，子树恰好存在一条路径，一共有 $f_{u,0}\cdot f_{v,0}$ 种方案。

如果 $E$ 不连通，子树也不存在任何路径，那么子树内无法形成一整个连通块，不符合树的定义，因此舍去。

对于一条边 $E$，加入这条边及其子树后，不存在任何路径的方案包括：

- 原来不存在任何路径，$E$ 不连通，子树恰好存在一条路径，一共有 $f_{u,1}\cdot f_{v,0}$ 种方案；
- 原来不存在任何路径，$E$ 连通，子树不存在任何路径，一共有 $f_{u,1}\cdot f_{v,1}$ 种方案。

于是，有以下转移方程：

$$
f_{u,0}\leftarrow f_{u,1}\cdot f_{v,0}+f_{u,0}\cdot(f_{v,1}+f_{v,0})
\\
f_{u,1}\leftarrow f_{u,1}\cdot(f_{v,1}+f_{v,0})
$$

边界条件：$f_{1,0}=1$，$f_{1,1}=0$。

当且仅当每个子图都能够成为一棵树时，整个图能够成为一棵树。答案就是每个“根节点”所在的子图恰好存在一条路径的方案数的乘积，即：

$$
ans=\sum_{i\in son_1}f_{i,0}
$$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MOD 998244353
int N, hd[200005], ind[200005];
struct Edge {
	int t, n;
} es[600005];
int cnt;
void addEdge(int x, int y) {
	es[++cnt] = {y, hd[x]};
	hd[x] = cnt;
	ind[y] ++;
}
bool is[200005];
long long dp[200005][2];
void dfs(int u, int f, bool g) {
	if(!g && ind[u] != 2 && u > 1)
		is[u] = 1;
	g |= ind[u] != 2 && u > 1;
	for(int e = hd[u], v = es[e].t; e; v = es[e = es[e].n].t)
		if(f ^ v)
			dfs(v, u, g);
	if(u > 1 && ind[u] == 1)
		addEdge(u, 1);
}
void dfs2(int u, int f) {
    if(u == 1)
        return;
	for(int e = hd[u], v = es[e].t; e; v = es[e = es[e].n].t)
		if(f ^ v) {
			dfs2(v, u);
			dp[u][0] = (dp[u][1] * dp[v][0] + dp[u][0] * (dp[v][1] + dp[v][0])) % MOD;
			(dp[u][1] *= dp[v][1] + dp[v][0]) %= MOD;
		}
}
int main() {
	scanf("%d", &N);
	for(int i = 0; i <= N; i ++)
		dp[i][1] = 1;
	dp[1][0] = 1, dp[1][1] = 0;
	for(int i = 1; i < N; i ++) {
		int x, y;
		scanf("%d%d", &x, &y);
		addEdge(x, y);
		addEdge(y, x);
	}
	dfs(1, 1, 0);
	for(int e = hd[1], i = es[e].t; e; i = es[e = es[e].n].t) {
		dfs2(i, i);
		(dp[0][1] *= dp[i][0]) %= MOD;
	}
	printf("%lld", dp[0][1]);
	return 0;
}
```

---

## 作者：xinxin2022 (赞：1)

## 简述题面

给定一棵树，连接叶子和根，删若干边，求删完后仍为树时树的形态数。

## 思路

由子树状态才能推知整棵树状态，考虑 DP。

从树的性质出发，一个图为树时每个节点到根之间有且仅有一条路径，那么在本题中一个节点和根之间的连接有利用原树和利用叶子边两种情况。

不妨设 $dp_{0,u}$ 表示 $u$ 节点不利用叶子边连接时子树的形态数，$dp_{1,u}$ 表示 $u$ 节点利用叶子边连接时的子树形态数。

那么枚举 $u$ 的儿子，计算贡献时，有两种情况：

- 不连接 $u->v$
- 连接 $u->v$

若不连接 $u->v$，$u$ 通过原树或其他叶子边连接根，$v$ 通过叶子边连接根，$dp_{0,u}=dp_{0,u}\times dp_{0,v}+dp_{1,u}\times dp_{0,v}$。

若连接 $u->v$，$u$ 通过子树内叶子边或原树连接，$dp_{0,u}=dp_{0,u}\times dp_{1,v},dp_{1,u}=dp_{1,u}\times(dp_{0,v}+dp_{1,v})$

因此有：

$$dp_{0,u}=dp_{0,u}\times (dp_{0,v}+dp_{1,v})+dp_{1,u}\times dp_{0,v}$$

$$dp_{1,u}=dp_{1,u}\times(dp_{0,v}+dp_{1,v})$$

答案即为所有根节点儿子不利用叶子边连接的方案数的积。

code：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,a,b,out[200005];
vector<int> p[200005];
long long dp[2][200005],ans=1;
void dfs(int now,int fa){
    if(now==1) return;
    for(int i:p[now]){
        if(i==fa) continue;
        dfs(i,now);
        dp[0][now]=dp[0][i]*dp[1][now]%mod+dp[0][now]*dp[0][i]%mod+dp[0][now]*dp[1][i]%mod;
        dp[1][now]=dp[1][now]*dp[0][i]%mod+dp[1][now]*dp[1][i]%mod;
        dp[0][now]%=mod;
        dp[1][now]%=mod;
    }
}
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        cin>>a>>b;
        p[a].push_back(b);
        p[b].push_back(a);
        out[a]++;
    }
    for(int i=1;i<=n;i++)
        if(out[i]==0)
            p[i].push_back(1);
    for(int i=1;i<=n;i++) dp[1][i]=1;
    dp[1][1]=0;
    dp[0][1]=1;
    for(int i:p[1]){
        dfs(i,i);
        ans=ans*dp[0][i]%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Programmeryhl (赞：0)

### 题意简介

给定一棵树，在每个叶子节点和根节点之间添加连边，求删除一些边后能形成多少种不同的树。

### 思路

考虑动态规划，设 $dp_{i,1/0}$ 表示在以 $i$ 为根的子树中是/否使用“叶子”边的方案数。

对于 $u \rightarrow v$，自下而上地更新 $dp$ 值，可分为两种情况：

- 若不删去 $u \rightarrow v$ 这条边，$dp_{u,0}$ 仅有一种贡献来源即 $dp_{u,0}=dp_{u,0} \times dp_{v,0}$，而 $dp_{u,1}$ 有两种选择，分别是将“叶子”边接在 $u$ 的别的孩子上或接在 $v$ 的子树上，也就是 $dp_{u,1}=dp_{u,1} \times dp_{v,0} + dp_{u,0} \times dp_{v,1}$。

- 若删去 $u \rightarrow v$ 这条边，则 $dp_{u,0}=dp_{u,0} \times dp_{v,1}$，此时 $u$ 的别的孩子与 $v$ 的子树上均可以接“叶子”边，有 $dp_{u,1}=dp_{u,1} \times dp_{v,1}$。

时间复杂度显然 $O(n)$。

### Code

```c++
#include<iostream>
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=2e5+5;
const int MOD=998244353;
int n,head[N],nxt[N<<1],to[N<<1],cnt=0;
long long dp[N][2];
void add(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void dfs(int u,int father)
{
	if(father) dp[u][0]=1;
	int son=0;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==father) continue;
		son++;
		dfs(v,u);
		dp[u][1]=(dp[u][1]*dp[v][0]%MOD+dp[u][0]*dp[v][1]%MOD+dp[u][1]*dp[v][1]%MOD)%MOD;
		dp[u][0]=(dp[u][0]*dp[v][0]%MOD+dp[u][0]*dp[v][1]%MOD)%MOD;
	}
	if(!son) dp[u][0]=dp[u][1]=1;
}
int main()
{
	IOS;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dp[1][1]=1;
	dfs(1,0);
	cout<<max(dp[1][1],dp[1][0])<<'\n';
	return 0;
}
```

---

