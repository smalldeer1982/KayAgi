# Simultaneous Coloring

## 题目描述

给定一个由 $n$ 行 $m$ 列组成的矩阵。

你可以对其执行两种操作：

- 将整列涂成蓝色；
- 将整行涂成红色。

注意，你不能选择行或列要涂成哪种颜色。

在一秒内，你可以执行一次操作，也可以同时执行多次操作。如果只执行一次操作，则不需要花费。如果同时执行 $k>1$ 次操作，则需要花费 $k^2$ 个硬币。当多次操作同时进行时，对于同时受到两种操作影响的每个格子，其颜色可以独立选择。

你需要处理 $q$ 个询问。在每次询问前，所有格子都会变为无色。最初，对任何格子的颜色都没有限制。在第 $i$ 次询问中，会增加如下形式的限制：

- $x_i~y_i~c_i$ ——第 $x_i$ 行第 $y_i$ 列的格子必须被涂成颜色 $c_i$。

因此，在第 $i$ 次询问后，共有 $i$ 个格子的颜色有要求。每次询问后，输出按照所有限制涂色所需的最小花费。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 2 4
1 1 R
2 2 R
1 2 B
2 1 B```

### 输出

```
0
0
0
16```

## 样例 #2

### 输入

```
3 5 10
1 1 B
2 5 B
2 2 B
2 3 R
2 1 B
3 2 R
3 3 B
1 2 R
1 3 B
3 1 B```

### 输出

```
0
0
0
0
0
0
16
16
25
25```

# 题解

## 作者：Alex_Wei (赞：13)

### [CF1989F Simultaneous Coloring](https://www.luogu.com.cn/problem/CF1989F)

假设某行或某列被染色两次，那么将前一次染色取消不影响最终的染色结果，而代价不会变大。因此，可以认为每行每列至多被染色一次。

对于一条限制，不妨设染成红色，则要求第 $y_i$ 列的染色不晚于第 $x_i$ 行的染色。这启发我们从图论的角度解决本题。

具体地，将对每行每列的染色抽象为总共 $n + m$ 个点，$u$ 向 $v$ 连边表示 $u$ 对应的染色不晚于 $v$，得到一张有向图。对每个强连通分量，必须同时执行其内部所有点对应的染色。每个大小大于 $1$ 的强连通分量产生大小平方的代价，求和即得答案。

问题转化为加边并维护强连通分量，允许离线（这很重要）。将每个强连通分量缩成一个点，则对于一条边，如果它在某次询问时两端已经处于同一个强连通分量，那么它在之后的询问中没有用，否则它在之前的询问中没有用。

类似整体二分的思想，使用当前区间内时间不超过 $mid$ 的所有边计算第 $mid$ 次询问时图的强连通分量分解。对于一条边 $u\to v$，若 $u, v$ 强连通，则丢入 $[l, mid]$ 区间内，否则丢入 $[mid + 1, r]$ 区间内。特别地，若时间超过 $mid$，则直接丢入 $[mid + 1, r]$。

使用并查集维护缩点，时间复杂度 $\mathcal{O}(q\log q\log n)$。直接维护强连通分量并按秩合并维护每个点的代表元的时间复杂度为 $\mathcal{O}(q\log q)$。空间复杂度 $\mathcal{O}(q)$。[代码](https://codeforces.com/contest/1989/submission/269501718)。

*本题解将同步发表于清华大学学生算法协会微信公众号「酒井算协」。

---

## 作者：Moeebius (赞：5)

类似 [P5163](https://www.luogu.com.cn/problem/P5163)。

棋盘模型转二分图，如果要求染红则从左部（行）连向右部（列），否则从右部连向左部。

容易发现答案即为大小 $ >1 $ 的 SCC 大小平方和，转化仅加边的动态图 SCC 问题。考虑用整体二分求出每条边什么时候被缩到一个 SCC 里面，就可以转成无向图连通分量问题用并查集维护。

具体而言，我们整体二分的时候先将 $[l, mid]$ 的边取出来跑 Tarjan，将每个 SCC 设一个代表元（例如，SCC 内最小的点编号）；然后对于 $(mid, r]$，我们可以将每条边的左右端点设成其所在 SCC 代表元，这样就将 SCC 的信息传了下去，并且避免了写可撤销并查集。

注意遍历的时候不能遍历到孤点，否则复杂度错误。

---

## 作者：sunzz3183 (赞：4)

# CF1989F Simultaneous Coloring 题解

## 前言

2024/7/6 update：修改了时间复杂度。

## 题意

给定一个 $n\times m$ 的网格。你可以把一行染成 $R$ 或者把一列 $B$，你可以同时染色多行或者多列，并如果有交叉的染色你可以控制它为 $R$ 或 $B$。定义一次染色的代价为选择的行和列的数量的平方。现在有 $q$ 个要求，每个要求为方格 $(x,y)$ 为 $R$ 或 $B$，问你将达成前 $i(i\le q)$ 个要求的代价分别为多少。

## 分析

很像一年前的~~某音~~的小游戏。

首先考虑平方代价这个东西，显然每次操作选择的数量越少越好，所以我们考虑如何选择。

再考虑，某个格子的颜色是由**该格子最后一次染色**来决定的，假如第 $(x,y)$ 为 $R$，那么一定是先染列 $y$ 再染行 $x$，这样就有了一种**顺序**，所以我们就可以把行和列抽象成点，然后连边。

这样就可以构造出一张有向图。假设图为 DAG，那么直接拓扑排序就可以构造出一组解，显然此时答案为 $0$。但是如果图中出现了环，我们就必须同时选择一个环才能成功染色，更具体的，每次通过 Tarjan 来跑出来每个 SCC，对于每个 SCC 单独操作，然后缩点跑拓扑就是一组解。综上，代价即为图的每个大小 $>1$ 的 SCC 的大小的平方和。

但是此时时间复杂度为 $O(q(n+m))$，显然无法通过此题。

容易想到用并查集来维护 SCC 的合并，所以我们需要用到一种算法来判断每一条边会合并哪些 SCC。

可以考虑把加边通过**每个要求的先后时间**来**整体二分**。

我们对于一个当前区间 $[l,r]$，把 $[l,mid]$ 的边取出来跑  Tarjan，并且在实际跑的时候，只需要跑 $[l,r]$ 的边的左右端点即可，这样一次 Tarjan 的复杂度即为 $O(|V|),V\approx \min\{n,2(r-l+1)\}$。

如果当前区间 $l<r$，那么我们把 $[l,mid]$ 且端点在同一 SCC 的边（即有可能在 $mid$ 时刻连接了两个 SCC）递推到下一层 $[l,mid]$ ，把 $[1,r]$ 且不在同一 SCC 的边递推到下一层 $[mid+1,r]$。

否则如果 $l=r$，那就记录一下当前 $[l,r]$ 且端点在同一 SCC 的边的时刻，用于最后跑并查集。

整体二分复杂度 $O((n+m+q)\log(q))$，并查集复杂度 $O(q\alpha(n))$。

## 代码

```cpp
const int N=4e5+2;
int n,m,q,ans;
struct Graph{
    int u,v,tim;
};
vector<int>E[N];
struct edge{
    int nxt,v;
}ed[N];
int en,first[N];
void add(int u,int v){
    ed[++en]={first[u],v};
    first[u]=en;
}
int dfn[N],low[N],cnt;
int num,id[N];
bool vis[N],flg[N];
stack<int>st;
void dfs(int u){
    dfn[u]=low[u]=++cnt;
    st.push(u);vis[u]=1;
    for(int i=first[u];i;i=ed[i].nxt)
        if(!dfn[ed[i].v])dfs(ed[i].v),low[u]=min(low[u],low[ed[i].v]);
        else if(vis[ed[i].v])low[u]=min(low[u],low[ed[i].v]);
    if(dfn[u]==low[u]){
        num++;int x;
        do{
            x=st.top();st.pop();
            id[x]=num,vis[x]=0;
        }while(x!=u);
    }
    return;
}
void solve(int l,int r,vector<Graph>G){
    int mid=(l+r)>>1;
    en=cnt=num=0;
    for(Graph i:G)
        first[i.u]=first[i.v]=
        dfn[i.u]=dfn[i.v]=0,
        vis[i.u]=vis[i.v]=0;
    for(Graph i:G)
        if(i.tim<=mid)add(i.u,i.v);
    for(Graph i:G){
        if(!dfn[i.u])dfs(i.u);
        if(!dfn[i.v])dfs(i.v);
    }
    if(l==r){
        for(Graph i:G)if(id[i.u]==id[i.v])E[mid].push_back(i.tim);
        return;
    }
    vector<Graph>Gl,Gr;
    for(Graph i:G){
        if(id[i.u]==id[i.v]){
            if(i.tim<=mid)Gl.push_back(i);
        }
        else Gr.push_back({id[i.u],id[i.v],i.tim});
    }
    solve(l,mid,Gl);solve(mid+1,r,Gr);
}
int fa[N],siz[N];
inline int find(int v){return fa[v]==v?v:fa[v]=find(fa[v]);}
inline int pf(const int x){return x==1?0:x*x;}
void merge(int x,int y){
    x=find(x);y=find(y);
    if(x!=y){
        ans-=pf(siz[x]),ans-=pf(siz[y]);
        if(siz[x]<siz[y])swap(x,y);
        fa[y]=x,siz[x]+=siz[y];
        ans+=pf(siz[x]);
    }
}
signed main(){
    n=read();m=read();q=read();
    vector<Graph>G;
    for(int i=1;i<=q;i++){
        int x=read(),y=read()+n;
        if(getchar()=='R')G.push_back({y,x,i});
        else G.push_back({x,y,i});
    }
    solve(1,q,G);
    for(int i=1;i<=n+m;i++)fa[i]=i,siz[i]=1;
    for(int i=1;i<=q;i++){
        for(int j:E[i])
            merge(G[j-1].u,G[j-1].v);
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：WRuperD (赞：3)

非常 Educational 的好题。

题目条件非常难看，考虑转化为如下形式：

- 对于每一行每一列建立一个虚点表示该行该列。总点数 $n+m$。
- 如果要求 $a_{i,j}$ 为红色，则 $i$ 向 $j+n$ 连一条有向边，否则 $j+n$ 向 $i$ 连一条有向边。
- 容易发现，如果图是一个 DAG 的话那么我们显然只需要按照拓扑序依次进行操作即可。
- 于是转化为计数图中每个点数大于一的强连通分量的点数平方和。需要支持每次加一条边。

考虑直接做的复杂度，每一次加一条边都暴力地区跑一遍 Tarjan 计算一下强连通块复杂度 $O(q(n+m))$ 十分垃圾。

注意到复杂度主要是在我们每加一次边都要遍历全图，这非常劣。事实上可能有的边在后面的计算里是完全没有用的。于是我们考虑整体二分。

对于每一条边，我们需要注意到的事情是：。
- 如果在加这一条边之前两侧的点已经处于同一个强连通分量之中，那么这条边没用。
- 否则它可能在之后的某个时间有用，和其它的边构成一个新的强连通分量。

这个性质非常好，非常的像二分。于是我们整体二分当前的时间点属于 $[l,r]$ 并记录此时可能有用的边。

具体地，我们每次加入时间为 $[l,mid]$ 的边然后暴力跑 Tarjan 去计算强连通分量。首先，根据上面的观察，对于时间在 [l, mid] 并且加了之后 $u,v$ 联通一条边 $u \to v$，显然要把它扔到 $[l,mid]$ 里面去计算。否则按照强连通分量缩点后扔到 $[mid+1,r]$ 里面去处理（这里有一个简便的实现是直接把这条边的 $u,v$ 变成相对应的强连通分量的标号）。

对于所有 $l=r$ 的时刻。显然的，此时做完一遍 Tarjan 后两边节点属于一个强连通分量的边都是会在时刻 $l$ 产生新的强连通分量的边。于是我们呢对于每一个询问 $i$ 记录下此时需要加的边。根据前面的推理，这些边加了之后两侧一定会合并成新的强连通分量。于是我们做完整体二分之后再直接用并查集维护一下每个强连通分量以及大小即可。

``` cpp
// Problem: Simultaneous Coloring
// URL: https://www.luogu.com.cn/problem/CF1989F
// Written by WRuperD

#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 4e5 + 10;
struct node{
	int u, v, tim;
};

int dfn[MAX], low[MAX], id[MAX], ins[MAX], stc[MAX], clk, topp;
vector <int> g[MAX];
int scc;

void cov(int u){
	g[u].clear();
	dfn[u] = low[u] = id[u] = ins[u] = 0;
}

void dfs(int u){
	dfn[u] = low[u] = ++clk;
	stc[++topp] = u;
	ins[u] = 1;
	for(int v : g[u]){
		if(!dfn[v]){
			dfs(v);
			low[u] = min(low[u], low[v]);
		}else if(ins[v]){
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]){
		++scc;
		int v;
		do{
			v = stc[topp--];
			id[v] = scc;
			ins[v] = 0;
		}while(v != u);
	}
}

vector <int> Ans[MAX];

void solve2(int l, int r, vector <node> G){
	if(l > r)	return ;
	int mid = (l + r) >> 1;
	topp = clk = 0;
	scc = 0;
	for(auto U : G){
		cov(U.u), cov(U.v);
	}
	for(auto U : G){
		if(U.tim <= mid){
			g[U.u].pb(U.v);
		}
	}
	for(auto U : G){
		if(!dfn[U.u])	dfs(U.u);
	}
	if(l == r){
		for(auto U : G){
			if(id[U.u] == id[U.v]){
				Ans[l].pb(U.tim);
			}
		}
		return ;
	}
	vector <node> G1, G2;
	for(auto U : G){
		if(id[U.u] == id[U.v]){
			if(U.tim <= mid)	G1.pb(U);
		}else{
			G2.pb(node{id[U.u], id[U.v], U.tim});
		}
	}
	solve2(l, mid, G1), solve2(mid + 1, r, G2);
}

int ret;
int fa[MAX], siz[MAX];

int find(int x){
	if(fa[x] == x)	return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y){
	if(find(x) == find(y))	return ;
	if(siz[find(x)] > 1)	ret -= siz[find(x)] * siz[find(x)];
	if(siz[find(y)] > 1)	ret -= siz[find(y)] * siz[find(y)];
	siz[find(x)] += siz[find(y)];
	siz[find(y)] = 0;
	fa[find(y)] = find(x);
	ret += siz[find(x)] * siz[find(x)];
}

void solve(){
	int n = read(), m = read(), q = read();
	vector <node> G;
	for(int i = 1; i <= q; i++){
		int u = read(), v = read();
		char ch = getchar();	while(ch != 'R' and ch != 'B'){ch = getchar();}
		if(ch == 'R'){
			G.pb(node{u, v + n, i});
		}else{
			G.pb(node{v + n, u, i});
		}
	}
	solve2(1, q, G);
	for(int i = 1; i <= n + m; i++)	fa[i] = i, siz[i] = 1;
	for(int i = 1; i <= q; i++){
		for(auto u : Ans[i]){
			merge(G[u - 1].u, G[u - 1].v);
		}
		write(ret), endl;
	}
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

有一个 $n\times m$ 的网格，初始时每个格子都是白色的。有两种染色方法：将一行所有格子染红、将一列所有格子染蓝。

有 $q$ 次操作，每次操作给出 $(x,y,c)$ 表示单元格 $(x,y)$ 的颜色必须为 $c$。

每次操作结束后，你需要先将网格恢复到初始状态，然后进行若干次染色。注意你可以将 $k$ 个染色策略同时进行，花费 $[k>1]k^2$ 的代价，如果一个单元格受到多个染色方法控制，你可以独立选择其中一种染色方法对其染色。输出满足目前所有限制的最小代价总和。

$1\leq n,m,q\leq 2\times 10^5$。

## 思路

染色操作受到染色的时刻影响。对于限制 $(x,y,\mathrm{R})$ 即对行 $x$ 的操作必须在 $y$ 之后，$(x,y,\mathrm{B})$ 即对列 $y$ 的操作必须在 $x$ 之后。

可以考虑建图，对于第一种限制，连边 $(C(y),R(x))$，对于第二种限制，连边 $(R(x),C(y))$，则同一个强连通分量的所有点必须同时完成。

由于 $a_1^2+a_2^2+\cdots+a_n^2<(a_1+a_2+\cdots+a_n)^2$，所以答案就是所有大于 $1$ 的强连通分量的大小平方和。于是我们就需要动态加边维护强连通分量。

对于动态加边维护强连通分量的问题，由于每条边在一个时刻后称为某个强连通分量的一部分后，就永远会在强连通分量中，所以可以考虑二分，由于一个一个二分时间复杂度太大，于是可以整体二分。

对于当前二分区间 $[l,r]$，先对 $[l,\mathrm{mid}]$ 跑一遍 tarjan，对于此时在强连通分量的边，就放到左区间，否则放入右区间。注意对于一条边的端点，应该表示缩点后的点，这个可以用并查集维护。最后我们需要维护强连通分量的大小平方和，同样可以用并查集维护。

时间复杂度 $O(q\log q)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;
int n, m, q, fa[N], siz[N];
long long ans;

int find(int x){ return x == fa[x] ? x : fa[x] = find(fa[x]); }

void merge(int x, int y){
    x = find(x), y = find(y);
    if(x == y) return;
    if(siz[x] != 1) ans -= 1ll * siz[x] * siz[x];
    if(siz[y] != 1) ans -= 1ll * siz[y] * siz[y];
    siz[x] += siz[y], fa[y] = x;
    ans += 1ll * siz[x] * siz[x];
}


int dfn[N], low[N], stk[N], top, cnt, bel[N];
bool vis[N];
vector<int> g[N];

void tarjan(int u){
    dfn[u] = low[u] = ++dfn[0], stk[++top] = u, vis[u] = true;
    for(auto v : g[u]){
        if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if(vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]){
        cnt++;
        while(stk[top] != u){
            bel[stk[top]] = cnt, vis[stk[top--]] = false;
        }
        bel[u] = cnt, vis[u] = false, top--;
    }
}

void solve(int l, int r, const vector<tuple<int,int,int>> &vct){
    if(l == r){
        if(l > q) return;
        for(auto [x, y, z] : vct) merge(x, y);
        cout << ans << '\n';
        return;
    }
    int mid = (l + r) >> 1;
    vector<tuple<int,int,int>> run, lft, rgt;
    for(auto [x, y, z] : vct) (z <= mid ? run : rgt).emplace_back(x, y, z);
    for(auto& [x, y, z] : run) x = find(x), y = find(y), g[x].push_back(y);
    for(auto [x, y, z] : run){
        if(!dfn[x]) tarjan(x);
    }
    for(auto [x, y, z] : run){
        (bel[x] == bel[y] ? lft : rgt).emplace_back(x, y, z);
    }
    top = 0;
    for(auto [x, y, z] : run) dfn[x] = dfn[y] = 0, g[x].clear();
    solve(l, mid, lft), solve(mid + 1, r, rgt);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> m >> q;
    vector<tuple<int,int,int>> vct;
    iota(fa + 1, fa + n + m + 1, 1);
    fill(siz + 1, siz + n + m + 1, 1);
    for(int i=1;i<=q;i++){
        int x, y; char ch;
        cin >> x >> y >> ch;
        if(ch == 'R') vct.emplace_back(y + n, x, i);
        else vct.emplace_back(x, y + n, i);
    }
    solve(1, q + 1, vct);
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：TernaryTree (赞：1)

很深刻的整体二分题目，感觉其他题解讲的并不太清楚。

前几步的观察转化比较明显：每行每列最多染一次，多染没用。那么我们对每个格子考虑，一个格子是红色代表其所在行被染色时间晚于所在列被染色时间，蓝色同理。这启发我们去建一个有向图图，每行每列是一个点，然后时间上存在一些先后关系，用有向边表示。

显然，若图是 DAG，答案为 $0$，因为我们总能找到符合条件的时间先后关系。继续考虑，若存在一个强连通分量大小 $\gt 1$，那么这整个连通块一定要在一起染色，代价为大小的平方。

于是我们将问题转化为了，有向图动态加边，每次加完边求所有大小 $\gt 1$ 的强连通分量大小平方和。

考虑离线。我们定义一条边在时刻 $t$ 是“好的”当且仅当它在时刻 $t$ 时两端点在同一强连通分量内。注意到，一条边只会由“不好的”变成“好的”，所以这具有单调性。假设我们对一条边 $i$ 求出了，最早在 $t_i$ 的时候 $i$ 从不好变成了好的，那么我们就可以回答所有询问：扫一遍时间轴，每次在并查集上合并 $t_i=T$ 的边，同时更新答案即可。

接下来考虑如何求 $t_i$。有单调性，启发我们去做二分，而且应该是整体二分。假设我们拿出来一些边，确定了它们的 $t_i$ 在 $[l,r]$ 之间。将这些边里面所有编号 $\le mid$ 的边加入图中跑 tarjan，再考虑这些边往左分配还是往右。显然，我们对于在同一个强连通里，且编号 $\le mid$ 的边，会分到左边去；在同一个强连通里，编号 $\gt mid$ 的边，没有用，扔到垃圾桶里；不在同一个强连通里，就把端点所在强连通的编号对应加入右边，因为需要保留左边的信息。

这样就做完了，复杂度是 $\Theta(q\log q)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1989F)

**题目大意**

> $n\times m$ 棋盘，每次操作可以选择 $k$ 个行或列，给行染红，列染蓝，代价 $[k>1]k^2$。
>
> $q$ 次询问，每次告诉你一个位置最终的颜色，求得到满足当前限制的棋盘的最小代价。
>
> 数据范围：$n,m,q\le 2\times 10^5$。

**思路分析**

设第 $i$ 行在第 $x_i$ 次被操作，第 $j$ 列在第 $y_j$ 次被操作，那么一个点的颜色就是限定 $x_i\ge y_j$ 或 $x_i\le y_j$。

把所有限制关系画成图，如果有强联通分量，说明强连通分量中的点一定相等，不同强连通分量中的点可以按拓扑序操作。

由于答案有凸性，因此合并两个强联通分量一定不优，答案就是每个强连通分量大小的平方和，我们就是要在 $q$ 次加边后动态维护这个值。

这种动态连通性问题，考虑整体二分，对每条边 $e$ 确定在什么时候 $t_e$ 被缩进强连通分量。

那么我们加入时间 $\le mid$ 的边然后 tarjan 缩点，如果这条边被缩进强联通分量，说明 $t_e\le mid$，否则 $t_e>mid$。

分别把这些点递归到 $[l,mid]$ 和 $[mid+1,r]$ 中，先递归 $[l,mid]$，然后把强联通分量都用并查集缩成一个点再处理 $[mid+1,r]$。

时间复杂度 $\mathcal O(q\log q)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=4e5+5;
vector <int> G[MAXN];
int dfn[MAXN],low[MAXN],dcnt,stk[MAXN],tp,bel[MAXN],scnt;
bool ins[MAXN];
void tarjan(int u) {
	dfn[u]=low[u]=++dcnt,stk[++tp]=u,ins[u]=true;
	for(int v:G[u]) {
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		++scnt;
		while(ins[u]) bel[stk[tp]]=scnt,ins[stk[tp--]]=false;
	}
}
struct Edge { int u,v,t; };
int R,C,n,q,dsu[MAXN],siz[MAXN];
ll ans=0;
ll W(int k) { return k>1?1ll*k*k:0; }
int find(int x) { return dsu[x]^x?dsu[x]=find(dsu[x]):x; }
void merge(int u,int v) {
	u=find(u),v=find(v);
	if(u==v) return ;
	ans-=W(siz[u])+W(siz[v]);
	siz[u]+=siz[v],dsu[v]=u,ans+=W(siz[u]);
}
void solve(int l,int r,vector<Edge>&E) {
	if(E.empty()) {
		for(int i=l;i<=min(r,q);++i) cout<<ans<<"\n";
		return ;
	}
	if(l==r) {
		for(auto e:E) merge(e.u,e.v);
		if(l<=q) cout<<ans<<"\n";
		return ;
	}
	int mid=(l+r)>>1;
	vector <Edge> LE,RE;
	for(auto &e:E) {
		e.u=find(e.u),e.v=find(e.v);
		if(e.t<=mid) G[e.u].push_back(e.v);
	}
	for(auto e:E) {
		if(e.t<=mid) {
			if(!dfn[e.u]) tarjan(e.u);
			if(!dfn[e.v]) tarjan(e.v);
			(bel[e.u]==bel[e.v]?LE:RE).push_back(e);
		} else RE.push_back(e);
	}
	dcnt=scnt=0;
	for(auto e:E) if(e.t<=mid) dfn[e.u]=dfn[e.v]=0,G[e.u].clear(),G[e.v].clear();
	solve(l,mid,LE),solve(mid+1,r,RE);
}
signed main() {
	ios::sync_with_stdio(false);
	cin>>R>>C>>q,n=R+C;
	for(int i=1;i<=n;++i) dsu[i]=i,siz[i]=1;
	vector <Edge> E;
	for(int i=1,u,v;i<=q;++i) {
		char op;
		cin>>u>>v>>op,v+=R;
		if(op=='R') swap(u,v);
		E.push_back({u,v,i});
	}
	solve(1,q+1,E);
	return 0;
}
```

---

