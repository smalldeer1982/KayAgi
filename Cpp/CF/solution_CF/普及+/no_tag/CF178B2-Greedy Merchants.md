# Greedy Merchants

## 题目描述

在 ABBYY 中住着一只聪明的海狸。这一次，它开始研究历史。当它读到有关罗马帝国的内容时，它对商人的生活产生了兴趣。

罗马帝国由编号从 $1$ 到 $n$ 的 $n$ 个城市组成。它还拥有 $m$ 条双向道路，编号从 $1$ 到 $m$。每条路连接两个不同的城市，任何两个城市之间最多只有一条路相连。

如果存在一个有限的城市序列 $t_1, t_2, \ldots, t_p$（$p \geq 1$），使得：

- $t_1 = c_1$
- $t_p = c_2$
- 对于任意 $i$（$1 \leq i < p$），城市 $t_i$ 和 $t_{i+1}$ 都通过一条道路相连。

则称城市 $c_1$ 和 $c_2$ 之间存在一条路径。

我们知道罗马帝国的任何两个城市之间都存在一条路径。

在帝国中有 $k$ 个商人，编号从1到k。对于每个商人，可以用 $s_i$ 和 $l_i$ 表示，其中 $s_i$ 是这个商人仓库所在城市的编号，$l_i$ 是他的商店所在的城市编号。商店和仓库可能位于不同的城市，因此商人们需要将货物从仓库运送到商店。


如果某一条路的破坏会让一个商人的城市和仓库之间不再存在“路径”，那么称这条路对于该商人是“重要的道路”。罗马帝国的商人们非常贪婪，因此每个商人只为对他“重要的道路”缴纳税款（$1$ 元）。换句话说，每个商人支付 $d_i$ 元的税款，其中 $d_i$（$d_i \geq 0$）是对该商人“重要的道路”的数量。

收税日到来，聪明的海狸想要计算每个商人需要缴纳的税，他需要你的帮助。

## 样例 #1

### 输入

```
7 8
1 2
2 3
3 4
4 5
5 6
5 7
3 5
4 7
4
1 5
2 4
2 6
4 7
```

### 输出

```
2
1
2
0
```

# 题解

## 作者：lzyqwq (赞：2)

这题就是让我们求从 $x$ 到 $y$ 经过了几条割边，所以我们可以用 `Tarjan` 进行边双缩点，然后缩出来的图就是一棵树，且树上的边全是割边，因此将问题转化为树上距离。

如何快速求树上距离？我们先指定一个根，搞出每个边双连通分量在树中的深度 $d$，然后求 $x$ 和 $y$ 所在边双连通分量（分别设为 $X$ 和 $Y$）的 `LCA`，最后的答案就是 $d_X-d_{LCA}+d_Y-d_{LCA}$。

注意，建缩点后的图要避免重边。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 1;
int n, m, k, dfn[N], low[N], ebc[N], cnt, sum, lg[N], d[N], f[20][N];
vector<int> g[N], e[N];
stack<int> s;
bool is[N];
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++cnt;
    s.push(x);
    is[x] = 1;
    for (int i : g[x]) {
        if (i != fa) {
            if (!dfn[i]) {
                tarjan(i, x);
                low[x] = min(low[x], low[i]);
            } else if (is[i]) {
                low[x] = min(low[x], dfn[i]);
            }
        }
    }
    if (dfn[x] == low[x]) {
        ++sum;
        while (1) {
            int p = s.top();
            s.pop();
            is[p] = 0;
            ebc[p] = sum;
            if (x == p) {
                break;
            }
        }
    }
}
void dfs(int x, int fa) {
    if (fa) {
        d[x] = d[fa] + 1;
        f[0][x] = fa;
        for (int i = 1; i <= lg[d[x]]; i++) {
            f[i][x] = f[i - 1][f[i - 1][x]];
        }
    }
    for (int i : e[x]) {
        if (i != fa) {
            dfs(i, x);
        }
    }
}
inline int lca(int x, int y) {
    if (d[x] < d[y]) {
        swap(x, y);
    }
    while (d[x] > d[y]) {
        x = f[lg[d[x] - d[y]]][x];
    }
    if (x == y) {
        return x;
    }
    for (int i = lg[d[x]]; i >= 0; i--) {
        if (f[i][x] != f[i][y]) {
            x = f[i][x];
            y = f[i][y];
        }
    }
    return f[0][x];
}
int main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tarjan(1, 0);
    for (int i = 1; i <= n; i++) {
        lg[i] = log2(i);
        for (int j : g[i]) {
            if (ebc[i] < ebc[j]) {//判重边
                e[ebc[i]].push_back(ebc[j]);
                e[ebc[j]].push_back(ebc[i]);
            }
        }
    }
    dfs(1, 0);
    cin >> k;
    for (int i = 1, u, v, q; i <= k; i++) {
        cin >> u >> v;
        if (ebc[u] == ebc[v]) {//在同一个边双中
            cout << "0\n";
            continue;
        }
        q = lca(ebc[u], ebc[v]);
        cout << d[ebc[u]] + d[ebc[v]] - (d[q] << 1) << '\n';
    }
    return 0;
}
```


---

## 作者：Yexo (赞：0)

## 写在前面
由于「极其稳定」的洛谷 RMJ 系统和「延迟极低」的 CF 平台的功劳，导致我在 Luogu 上并没有 AC 记录，故在此附上 [CF 的 AC 记录](https://codeforces.com/contest/178/submission/275535294)。

在 LA 看见的这道题，发现很水，大喜过望。

## Solution

解题方向：边双连通分量，LCA。

具体思路：由于是无向图，设一个点对 $ (u, v) $，若有一条边删去后使 $ u $ 和 $ v $ 并不连通那必然是其割边，那么我们就可以用边双连通分量将整个图转化为一棵树，变成树上问题。

那么怎么来求割边数量呢？我们可以容易观察到，点对 $ (u, v) $ 的关键边数量就是其所属的双边连通分量之间路径上边的数量，那么就是求两点路径长，也就是 LCA 可以解决的问题。设 $ u, v $ 所在的边双连通分量分别为 $ i, j $，则对于每个点对答案为 $ dep_i + dep_j - dep_{lca} \times 2 $。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m;
vector<pair<int,int> > G[N]; //原图
int dfn[N],low[N];
int cnt,sum;
int belong[N];
stack<int> st;
vector<int> NG[N]; //新图
int dep[N];
void tarjan(int x,int edge){
    ++cnt;
    dfn[x]=low[x]=cnt;
    st.push(x);
    for(auto i:G[x]){
        if(i.second==(edge^1)) continue;
        if(!dfn[i.first]) tarjan(i.first,i.second),low[x]=min(low[x],low[i.first]);
        else low[x]=min(low[x],dfn[i.first]);
    }
    if(low[x]==dfn[x]){
        int t;
        sum++;
        do{
            t=st.top();
            st.pop();
            belong[t]=sum;
        }while(t!=x);
    }
}
int f[N][32];
void dfs(int x,int fa){
    dep[x]=dep[fa]+1;
    for(int i=1;(1<<i)<=dep[x];i++) f[x][i]=f[f[x][i-1]][i-1];
    for(auto i:NG[x]){
        if(i==fa) continue;
        f[i][0]=x;
        dfs(i,x);
    }
}
int query(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=__lg(n);i>=0;i--) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
    if(x==y) return x;
    for(int i=__lg(n);i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back({v,i<<1});
        G[v].push_back({u,i<<1|1});
    }
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i,0);
    }
    for(int i=1;i<=n;i++){
        for(auto j:G[i]){
            if(belong[i]!=belong[j.first]) NG[belong[i]].push_back(belong[j.first]);
        }
    }
    dfs(1,0);
    int k;
    scanf("%d",&k);
    while(k--){
        int u,v;
        scanf("%d%d",&u,&v);
        if(belong[u]==belong[v]){
            printf("0\n");
            continue;
        }
        int lca=query(belong[u],belong[v]);
        printf("%d\n",dep[belong[u]]+dep[belong[v]]-2*dep[lca]);
    }
}
```

---

## 作者：QWQ_123 (赞：0)

显然的，这个就是求两点之间有多少个割边。

因为对于边双中的边，不论删掉哪一条边，这个边双依旧联通。

所以将边双缩成一个点，最后就是一棵树，因为如果不是一棵树，那么一定还有边双。

让后剩余的边就是割边，然后就是求两点间的边的数量，树上前缀和差分即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, m;
int bel[N], dfn[N], low[N], dfn_idx, bel_idx;
bool st[N];
vector<pair<int, int>> e[N];
vector<pair<int, int>> e1[N], Edge;
int top[N], dfn1[N], fa[N], dep[N], son[N], sz[N], idx;

void tarjan(int u, int la = 0) {
	dfn[u] = low[u] = ++dfn_idx;
	// cout << u << ' ' << la << ' ' << dfn[u] << ' ' << low[u] << endl;

	for (auto [v, id] : e[u]) {
		if (id != (la ^ 1)) {
			if (!dfn[v]) {
				tarjan(v, id);
				if (dfn[u] < low[v]) st[id] = st[id ^ 1] = true;
				low[u] = min(low[u], low[v]);
			} else low[u] = min(low[u], dfn[v]);
		}
	}
}

void dfs(int u) {
	bel[u] = bel_idx;

	for (auto [v, id] : e[u]) {
		if (!bel[v] && !st[id]) dfs(v);
	}
}

void dfs1(int u, int f = 0) {
	fa[u] = f;
	dep[u] = dep[f] + 1;
	sz[u] = 1;

	for (auto [v, j] : e1[u]) {
		if (v != f) {
			dfs1(v, u);

			sz[u] += sz[v];
			if (!son[u] || sz[son[u]] < sz[v]) son[u] = v;
		}
	}
}

void dfs2(int u, int topf) {
	top[u] = topf;
	dfn1[u] = ++idx;

	if (son[u]) dfs2(son[u], topf);

	for (auto [v, j] : e1[u]) {
		if (fa[u] != v && v != son[u]) {
			dfs2(v, v);
		}
	}
}

int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}

	if (dep[u] > dep[v]) swap(u, v);

	return u;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v; scanf("%d%d", &u, &v);
		e[u].push_back({v, i << 1});
		e[v].push_back({u, i << 1 | 1});
		Edge.push_back({u, v});
	}

	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) tarjan(i, 0);

	for (int i = 1; i <= n; ++i) if (!bel[i]) {
		++bel_idx;
		dfs(i);
	}


	for (auto [u, v] : Edge) {
		if (bel[u] != bel[v]) {
			e1[bel[u]].push_back({bel[v], bel[u]});
			e1[bel[v]].push_back({bel[u], bel[v]});
		}
	}

	dfs1(bel[1]);
	// if (n == 1300) return 0;
	dfs2(bel[1], bel[1]);


	int q; scanf("%d", &q);	

	for (int i = 1; i <= q; ++i) {
		int u, v; scanf("%d%d", &u, &v);

		printf("%d\n", dep[bel[u]] + dep[bel[v]] - 2 * dep[LCA(bel[u], bel[v])]);
	}

	return 0;
}
```

---

