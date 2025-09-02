# [AGC035B] Even Degrees

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc035/tasks/agc035_b

$ N $ 頂点 $ M $ 辺の単純連結無向グラフが与えられます。頂点には $ 1 $ から $ N $ までの番号がついており、$ i $ 本目の辺は頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。 高橋君は、与えられたグラフのすべての辺にどちらかの向きをつけて有向グラフを作ります。 どの頂点から出る辺の本数も偶数になるような有向グラフを作ることが可能かどうか判定し、可能ならそのような例をひとつ構成してください。

## 说明/提示

### ノート

無向グラフが単純であるとは、自己ループと多重辺を含まないことを指します。

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N\ (1\leq\ i\leq\ M) $
- 与えられるグラフは単純かつ連結

### Sample Explanation 1

このように向き付けることで、頂点 $ 1,3 $ からは $ 2 $ 本、頂点 $ 2,4 $ からは $ 0 $ 本の辺が出るようになります。

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
4 1```

### 输出

```
1 2
1 4
3 2
3 4```

## 样例 #2

### 输入

```
5 5
1 2
2 3
3 4
2 5
4 5```

### 输出

```
-1```

# 题解

## 作者：ForgotMe (赞：8)

一道很好的构造题目。

首先边数为奇数肯定无解，输出 $-1$ 即可。

然后怎么办？

考虑 dfs 出原图的一棵生成树，除了生成树上的边先直接定个向（随便定向），然后来考虑生成树上的边。

设 $\operatorname{solve(u)}$ 表示使子树 $u$ 中的节点度数都变为偶数。

对于一个点 $u$，先递归执行 $\operatorname{solve(v)}$，其中 $v\in son(u)$。然后考虑怎么解决点 $u$ 的问题，如果当前点 $u$ 的度数为奇数，就将点 $u$ 向父亲的边定为 $u\to fa_{u}$，否则 $fa_{u}\to u$。注意定向后要修改保存度数的数组（最开始随便定向时也要统计）。

这样 dfs 一遍后只有根结点没有保证为偶数度，但是总度数为偶数，除了根节点外的度数和也为偶数，所以根结点度数为偶数，所以满足条件，时间复杂度 $\mathcal{O(n)}$。

```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include<queue>
#include <cstring>
#include <cmath>
using namespace std;
int n,m,u[100005],v[100005],du[100005],dep[100005],f[100005];
bool vis[100005],used[100005];
struct node{
	int to,id;
};
vector<node>G[100005];
vector<int>g[100005];
void dfs(int u,int fa){
	dep[u]=dep[fa]+1;
	f[u]=fa;
	vis[u]=1;
	for(int i=0;i<G[u].size();i++){
		int to=G[u][i].to;
		if(vis[to])continue;
		g[u].push_back(to);
		used[G[u][i].id]=1;
		dfs(to,u);
	}
}
void solve(int u){
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		solve(v);
	}
	if(u!=1){
		if(du[u]%2==1)printf("%d %d\n",u,f[u]);
		else printf("%d %d\n",f[u],u),du[f[u]]++;
	} 
}
int main() {
	scanf("%d %d",&n,&m);
	if(m%2==1){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=m;i++){
		scanf("%d %d",&u[i],&v[i]);
		G[u[i]].push_back(node{v[i],i});
		G[v[i]].push_back(node{u[i],i});
	}
	dfs(1,0);
	for(int i=1;i<=m;i++){
		if(used[i])continue;
		du[u[i]]++;
		printf("%d %d\n",u[i],v[i]);
	}
	solve(1);
    return 0;
}
```

---

## 作者：Azazеl (赞：2)

#### 题意

> $~~~~$ 给出一张 $n$ 个点 $m$ 条边的无向简单连通图，给每一条边定向，使得每一个点出度为偶数，输出任意一种方案，或者说明无解。

---

#### 题解

$~~~~$ 不难想到，当 $m$ 为奇数时，由于每条边都会有 $1$ 的出度贡献，故一定会有一个点其出度为奇数，此时无解。

$~~~~$ 然后，我们只关心每个点出度的奇偶性，不妨按输入的方向先将图转化为有向图，然后进行调整。将所有出度为奇数的点提出来。

$~~~~$ 此时，改变原图的某一条边 $(u_i,v_i)$ 的方向，就相当于让 $u_i$ 的度 $-1$ ，$v_i$ 的度 $+1$ 。如上所述，我们只关心每个点出度的**奇偶性**，因此 $-1$ 和 $+1$ 相对于奇偶性是等价的，不妨把操作都转化为 $\operatorname{xor} 1$ 。因此改变某条边的方向就是将这条边两个端点的权值 $\operatorname{xor} 1$ 。不难发现，这样的操作进行偶数次是无意义的，也就是说进行偶数次就相当于不调整方向。

$~~~~$ 现在来考虑如何调整，我们发现对于一条路径，改变路径上所有的边，只会影响这条路径的两个端点的权值，因此直接将任意两个权值为 $1$ 的点路径上的所有边全部进行一次操作即可。由于奇数权值的点在合法的前提下一定只有偶数个，因此不存在剩余单独一个点的情况。

$~~~~$ 当然进行上述的操作时，如果用 DFS/BFS 会达到 $\Theta(n^2)$ 的复杂度，因此考虑建出原图的一个生成树，然后对于每次操作进行**树上差分**。最后对于每条边，若为树边，根据操作次数进行判断；若为非树边，由于原图联通，故我们生成的一定是树而不是森林，那么非树边一定不会被经过，按原序输出即可。

---

#### 代码

```cpp
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define mp(a,b) make_pair(a,b)
using namespace std;
struct Edge{
	int u,v,On;
}E[100005];
bool vis[100005];
int cf[100005],lg[100005],dep[100005],f[100005][25],arr[100005],pre[100005];
vector < pair<int,int> > G[100005];
void dfs(int u,int fa)
{
	vis[u]=true;
	f[u][0]=fa;
	dep[u]=dep[fa]+1;
	for(int i=1;i<=21;i++) f[u][i]=f[f[u][i-1]][i-1];
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i].first;
		if(vis[v]) continue;
		E[G[u][i].second].On=1;
		dfs(v,u);
	}
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	while(dep[x]>dep[y]) x=f[x][lg[dep[x]-dep[y]]-1];
	if(x==y) return x;
	for(int k=lg[dep[x]]-1;k>=0;k--)
	{
		if(f[x][k]!=f[y][k]) x=f[x][k],y=f[y][k];
	}
	return f[x][0];
}
void dfs2(int u)
{
	vis[u]=true;
	for(int i=0;i<G[u].size();i++)
	{
		int v=G[u][i].first;
		if(vis[v]) continue;
		dfs2(v);
		cf[u]+=cf[v];
	}
}
int main() {
	int n,m;
	scanf("%d %d",&n,&m);
	if(m&1) return puts("-1")&0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d %d",&E[i].u,&E[i].v);
		arr[E[i].u]^=1;
		G[E[i].u].push_back(mp(E[i].v,i));
		G[E[i].v].push_back(mp(E[i].u,i));
	}
	int cnt=0,Last=0;
	for(int i=1;i<=n;i++)
	{
		if(arr[i]) cnt++;
		lg[i]=lg[i>>1]+1;	
	}
	if(cnt&1) return puts("-1")&0;
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		if(arr[i])
		{
			if(!Last) Last=i;
			else
			{
				int anc=LCA(Last,i);
				cf[anc]-=2;cf[Last]++;cf[i]++;
				Last=0;
			}
		}
	}
	memset(vis,0,sizeof(vis));dfs2(1);
	for(int i=1;i<=m;i++)
	{
		int u=E[i].u,v=E[i].v;
		if(!E[i].On) printf("%d %d\n",u,v);
		else if(dep[u]<dep[v])
		{
			if(cf[v]&1) printf("%d %d\n",v,u);
			else printf("%d %d\n",u,v);
		}
		else
		{
			if(cf[u]&1) printf("%d %d\n",v,u);
			else printf("%d %d\n",u,v);
		}
	}
	return 0;
}
```

---

## 作者：听取MLE声一片 (赞：1)

不难看出总边数为奇数时一定无解，因为一条边一定会贡献一个入度和一个出度。

一个有趣的想法是，把它扔到树上是可以做的，我们先考虑树的做法。

对于一棵树从根节点往下找，对于每个点先处理它的子树。如果儿子节点的出度为奇数则连一条儿子到父亲的边，否则连父亲到儿子的边。

这样除了根节点我们都可以处理了，而又因为总边数是偶数所以总出度为偶数，除了根节点所有点的出度也是偶数，所以保证根节点的出度是偶数。这就对应了我们开头所说的。

然后我们推广到图的情况，先随便找出一棵生成树，然后把其它边随便连上，最后按照上面方法处理即可。

证明就是往上面连边不影响处理树的方案，然后依然保证总边数为偶数。

---

## 作者：251Sec (赞：0)

我们先随意给每条边定向，然后考虑调整使得点度合法。

我们称出度为偶数的点为白点，出度为奇数的点为黑点。

如果给一条边反向，我们发现，对于它连接的两个端点，它们都会被反色。而如果我们考虑将一条路径反向，我们发现它会使得路径的两个端点反色，而中间的点颜色不变。

因此，我们首先发现：无论如何操作，黑色点的奇偶性不变。也就是说如果黑点有奇数个那么无解。并且我们可以发现黑点如果有偶数个那么一定有解：我们将黑点两两配对，由于题目保证图连通，所以我们每一对配对的点之间都存在一条路径可以用来翻转，然后这两个黑点会一起变成白点。

具体实现时，我们求出原图的任意一棵生成树，然后随意选择一个根节点，将所有黑点到根节点的路径翻转。可以发现这和上一段的表述是等价的。这一算法可以用树上差分快速实现，于是本题完成。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m;
struct Edge {
    int to, next;
} e[200005];
int head[100005], len;
void Insert(int u, int v) {
    if (!len) len = 1;
    e[++len] = { v, head[u] };
    head[u] = len;
}
int fa[100005];
int Find(int u) { return fa[u] == u ? u : fa[u] = Find(fa[u]); }
bool deg[100005], rev[100005];
int eU[100005], eV[100005], eC;
int dC;
void DFS(int u, int fa) {
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        DFS(v, u);
        deg[u] ^= (rev[i >> 1] = deg[v]);
    }
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        int fu = Find(u), fv = Find(v);
        if (fu != fv) {
            fa[fu] = fv;
            Insert(u, v); Insert(v, u);
        }
        else {
            eU[++eC] = u; eV[eC] = v;
        }
        deg[u] ^= 1;
    }
    for (int i = 1; i <= n; i++) dC += deg[i];
    if (dC & 1) return puts("-1"), 0;
    DFS(1, 0);
    for (int u = 1; u <= n; u++) {
        for (int i = head[u]; i; i = e[i].next) {
            if (i & 1) continue;
            if (rev[i >> 1]) printf("%d %d\n", e[i].to, u);
            else printf("%d %d\n", u, e[i].to);
        }
    }
    for (int i = 1; i <= eC; i++) printf("%d %d\n", eU[i], eV[i]);
    return 0;
}
```

---

