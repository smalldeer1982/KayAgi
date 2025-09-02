# Trophic Balance Species

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041K/3f57ffd2f2e31a820fdb012c2016af22cc748377.png) 图像由 ChatGPT 4o 生成。在一项跨学科的合作中，一位生态系统科学家与一位计算机科学家联手，通过计算方法分析复杂生态系统的结构。生态系统科学家将整个系统建模成一个有向图 $D = (V, A)$，其中每个物种用一个节点 $v \in V$ 表示，每一对捕食关系由从被捕食者 $x$ 到捕食者 $y$ 的有向边 $(x, y) \in A$ 表示。这种图的结构可以用来模拟生态系统中能量在不同物种间的流动。

在这个系统中，有两个重要概念：

- **独立营养群**：如果集合 $S$ 中的任何物种 $x \in S$ 无法通过一系列有向捕食关系到达集合 $S$ 中的其他物种 $y \in S$（其中 $y \ne x$），那么这个集合 $S$ 就是一个独立营养群，即从 $x$ 到 $y$ 没有有向路径。

- **营养平衡物种**：一个物种如果它受到的影响来自直接或间接捕食者的数量（可以通过有向路径到达的物种，不包括自身）和来自直接或间接被捕食者的数量（可以通过有向路径达到该物种，不包括自身）之间的差值在所有物种中最小，就称为营养平衡物种。

考虑一个含有 $n = 4$ 个物种和 $m = 3$ 条捕食关系的生态系统：

- 物种 1：草（节点 1）
- 物种 2：兔子（节点 2）
- 物种 3：狐狸（节点 3）
- 物种 4：鹰（节点 4）

捕食关系用以下有向边表示：

- $(1, 2)$：草被兔子吃掉。
- $(2, 3)$：兔子被狐狸吃掉。
- $(2, 4)$：兔子也被鹰吃掉。

现在，考虑集合 $S = \{3, 4\}$（狐狸和鹰）。在节点 3（狐狸）和节点 4（鹰）之间没有有向路径；狐狸无法到达鹰，而鹰也无法到达狐狸。因此，这个集合符合独立营养群的定义。

接下来看各物种情况：

- 物种 1（草）：
  - 能到达的物种数：3（兔子、狐狸、鹰）
  - 能被到达的物种数：0（无）
  - 绝对差值：$|3 - 0| = 3$

- 物种 2（兔子）：
  - 能到达的物种数：2（狐狸、鹰）
  - 能被到达的物种数：1（草）
  - 绝对差值：$|2 - 1| = 1$

- 物种 3（狐狸）：
  - 能到达的物种数：0（无）
  - 能被到达的物种数：2（来自草和兔子）
  - 绝对差值：$|0 - 2| = 2$

- 物种 4（鹰）：
  - 能到达的物种数：0（无）
  - 能被到达的物种数：2（来自草和兔子）
  - 绝对差值：$|0 - 2| = 2$

在这些物种中，兔子的绝对差值最小，为 1，因此，兔子被认为是该生态系统的营养平衡物种。

题目已知生态系统中任何独立营养群的大小最多为 $k$。你的任务是找到生态系统中所有的营养平衡物种。

## 样例 #1

### 输入

```
4 3
1 2
2 3
2 4```

### 输出

```
2```

## 样例 #2

### 输入

```
4 5
1 2
1 3
1 4
2 3
3 2```

### 输出

```
2 3 4```

# 题解

## 作者：Nangu (赞：2)

## 题意

$n$ 个点 $m$ 条边的有向图，最长反链 $k\le16$，对于一个点 $u$，定义 $f_u$ 为能到达 $u$ 的点减去 $u$ 能到达的点的绝对值，求最小的 $f_u$。

## 题解

我们先考虑一种极端情况：最长反链等于 $0$。

此时原图中每个点对都可以从至少一端到达另一端，原图就形为一条点数为 $n$ 链再加上一些散边。注意到关键性质：倘若 $u$ 能到达 $v$ 那么 $v$ 能走到的点 $u$ 一定能走到。我们倒序枚举这个链上的点，每次将这个点加入并搜索，如果一个点满足已经被 $u$ 之前的点访问过了，那么这个点即他的后继也一定能被 $u$ 走到，我们就不需要在对这个点进行一次操作了。最后可以用 $O(n+m)$ 的复杂度算出这条链上每个点的答案。

更一般的，根据 $\text{Dilworth}$ 定理，最长反链长度就等于最少链覆盖。我们可以把 $n$ 个点拆成 $k$ 条链，每条链分别搜索，总复杂度 $O(k(n+m))$。

现在唯一的问题是如何找到最小链覆盖。这个问题用二分图网络流解决，复杂度 $O(n\sqrt m)$，并不能通过。

其实我们并不需要找到最小的链覆盖，我们只需要找到一个 **链数很小** 的覆盖就可以了。具体的，我们先把原图缩点，每个点点权为 $1$，我们每次找到原图中最长的链，并将这条链上的点的点权设为 $0$，再接着找最长链。这样做看似乱搞，实际上是正确的。

感性理解：当原图中最小链覆盖长度为 $k$ 时，最长的链长度至少在 $\frac n k$ 左右。我们每次删掉最长的链后，点数会乘 $\frac{k-1} k$ 左右，于是总次数为 $O(\log_{1+1/(k-1)} n)$，大致估算在 $O(k\log n)$ 左右。

---

其实还有另一种更加简洁的做法：缩点后每次从肯能成为答案的点中选出一个点，记为 $u$，设能到达 $u$ 的点集为 $S$，$u$ 能到达的点集为 $T$，若 $|S|\le|T|$，则 $S$ 中的点不可能成为答案；若 $|S|\ge|T|$，则 $|T|$ 中的点不可能成为答案。这样做形似随机二分，预期也只需要算 $O(k\log n)$ 个点的答案。

---

## 代码

下面给出第二种做法的代码：
```cpp
#include<bits/stdc++.h>
#define rep(i, j, k) for(int i=(j); i<=(k); ++i)
#define per(i, j, k) for(int i=(j); i>=(k); --i)
using namespace std;
const int N=5e5+7;
mt19937 rnd(time(0));
int n, m, minn=N, fr[N], to[N];
int dfn[N], low[N], times, st[N], top, tot, bel[N], siz[N];
bool vin[N], vout[N], vis[N], ins[N];
vector<int> G[N], H[N], tmp, ans, scc[N];
queue<int> q;
 
int get(int s, bool *vis, vector<int> G[N]){
	int cnt=siz[s];
	q.emplace(s), vis[s]=1;
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(auto v:G[u]) if(!vis[v]) cnt+=siz[v], vis[v]=1, q.emplace(v);
	}
	return cnt;
}
 
void tarjan(int u){
	dfn[u]=low[u]=++times, st[++top]=u, ins[u]=1;
	for(auto v:G[u])
		if(!dfn[v]) tarjan(v), low[u]=min(low[v], low[u]);
		else if(ins[v]) low[u]=min(low[u], dfn[v]);
	if(low[u]==dfn[u]){
		++tot;
		do bel[st[top]]=tot, ins[st[top]]=0; while(st[top--]!=u);
	}
}
 
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m;
	rep(i, 1, m){
		int u, v;
		cin>>u>>v;
		fr[i]=u, to[i]=v;
		G[u].emplace_back(v);
	}
	rep(i, 1, n) if(!dfn[i]) tarjan(i);
	rep(i, 1, n) G[i].clear(), ++siz[bel[i]], scc[bel[i]].emplace_back(i);
	rep(i, 1, m) G[bel[fr[i]]].emplace_back(bel[to[i]]),
				H[bel[to[i]]].emplace_back(bel[fr[i]]);
	while(1){
		tmp.clear();
		rep(i, 1, tot) if(!vis[i]) tmp.emplace_back(i);
		if(tmp.empty()) break;
		int u=tmp[rnd()%tmp.size()];
		vis[u]=1;
		rep(i, 1, tot) vin[i]=vout[i]=0;
		int in=get(u, vin, G), out=get(u, vout, H);
		int tmp=abs(in-out);
		if(tmp<minn) minn=tmp, ans.clear();
		if(minn==tmp) for(auto x:scc[u]) ans.emplace_back(x);
		if(in<=out) rep(i, 1, tot) vis[i]|=vin[i];
		if(in>=out) rep(i, 1, tot) vis[i]|=vout[i];
	}
	sort(ans.begin(), ans.end());
	for(auto x:ans) cout<<x<<' ';
}

---

