# Greedy Merchants

## 题目描述

在 ABBYY 生活着一只聪明的海狸。他现在在学习历史。当他从书上读到罗马帝国的时候，他对商人们的生活产生了兴趣。
罗马帝国由编号为 1 到 n 的 n 座城市构成。同时还有编号为 1 到 m 的 m 条双向路连接着这些城市。每一条路都连接着不同的城市。保证任意两个城市间最多只有一条路。
我们将一个城市序列t1, t2, t3, ....tp（p >= 1）称为城市 c1 和 c2 间的一条**路径**，当：
·t1 = c1
·tp = c2
·对于任意一个 i （1 <= i < p），城市 ti 与 ti + 1 间有一条道路链接。
保证罗马帝国的任意两个城市间都存在着**路径**。
在帝国里有标号为 1 到 k 的 k 个商人。对于每一个商人，我们有 si 和 li 一对数。 si 是 i 号商人的家所在的城市的编号，而 li 是他的商所在的城市的编号。他的商店和家可能在不同的城市，所以商人们可能需要把商品从家里搬到商店。
我们将一条路称为**重要的** ，当且仅当这条路被摧毁时，商人将无法从家到达他的商店。罗马的商人们非常的贪婪，所以每一个商人仅会在对他来说是**重要的**路上交税（一第纳尔）。换句话说，每一个商人需要交 di 的税， di （di >= 0）是对于第 i 个商人来说**重要的**路的数量。
收税的日子到了。来自 ABBYY 的聪明的海狸非常的好奇，所以他决定统计每一个商人需要交多少第纳尔的税。现在他需要你的帮助。

## 说明/提示

对于 20% 的数据：
·1 <= n <= 200
·1 <= m <= 200
·1 <= k <= 200
------------
对于 50% 的数据：
·1 <= n <= 2000
·1 <= m <= 2000
·1 <= k <= 2000
------------
对于 100% 的数据：
·1 <= n <= 1e5
·1 <= m <= 1e5
·1 <= k <= 1e5

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

