# 【MX-S7-T2】「SMOI-R2」Speaker

## 题目背景

原题链接：<https://oier.team/problems/S7B>。

## 题目描述

M 国有 $n$ 个城市和 $n - 1$ 条双向道路，城市编号为 $1,2,\dots,n$，**保证这些城市连通**，即**构成了一棵树**。其中，第 $i$ 条道路连接了城市 $u_i$ 和城市 $v_i$，路费为 $w_i$。你是一名演说家，每天都要在 M 国举办三场演讲，每场演讲都会在某一个城市进行。在城市 $i$ 举办一场演讲可以获得 $c_i$ 的收入，**同一天内可以在同一个城市举办多场演讲**。

接下来有 $q$ 天，第 $i$ 天的安排如下：你的第一场演讲必须在城市 $x_i$ 举行，第三场演讲必须在城市 $y_i$ 举行，而第二场演讲所在的城市可以自由选择。设第二场演讲所在的城市为 $z_i$，你需要向交通管理局支付经过 $x_i \to z_i$ 路径以及 $z_i \to y_i$ 路径上所有道路的路费。**注意，一条道路如果被多次经过，每次经过都需要支付相应的路费**。

对于每一天，请计算当天可以获得的最大利润，即**总收入减去总路费的最大值**。**注意，答案可能是负数**。

## 说明/提示

**【样例解释 #1】**

+ 第一天选择城市 $1$，答案为 $4 + 4 + 4 - 0 - 0 = 12$。
+ 第二天选择城市 $4$，答案为 $2 + 7 + 7 - 6 - 0 = 10$。
+ 第三天选择城市 $2$，答案为 $2 + 6 + 2 - 2 - 2 = 6$。

**【样例 #2】**

见附件中的 `speaker/speaker2.in` 与 `speaker/speaker2.ans`。

该组样例满足测试点 $7\sim 8$ 的约束条件。

**【样例 #3】**

见附件中的 `speaker/speaker3.in` 与 `speaker/speaker3.ans`。

该组样例满足测试点 $11\sim 13$ 的约束条件。

**【样例 #4】**

见附件中的 `speaker/speaker4.in` 与 `speaker/speaker4.ans`。

该组样例满足测试点 $17\sim 19$ 的约束条件。

**【数据范围】**

对于所有测试数据，保证：$1\le n, q\le 2\times 10^5$，$1\le u_i, v_i \le n$，$0\le w_i, c_i\le 10^9$，所有城市和道路构成了一棵树，$1\le x_i, y_i \le n$。

|测试点编号|$n\le $|$q\le $|特殊性质|
|:-:|:-:|:-:|:-:|
|$1\sim 4$|$400$|$400$|无|
|$5$|$2000$|$2000$|A|
|$6$|$2000$|$2000$|B|
|$7\sim 8$|$2000$|$2000$|无|
|$9$|$2000$|$2\times 10^5$|A|
|$10$|$2000$|$2\times 10^5$|C|
|$11\sim 13$|$2000$|$2\times 10^5$|无|
|$14\sim 15$|$2\times 10^5$|$3$|无|
|$16$|$2\times 10^5$|$2\times 10^5$|A|
|$17\sim 19$|$2\times 10^5$|$2\times 10^5$|C|
|$20\sim 25$|$2\times 10^5$|$2\times 10^5$|无|

- 特殊性质 A：每个城市至多被两条道路连接。
- 特殊性质 B：存在一座城市 $i$（$1\le i\le n$），满足对于所有其他城市 $j$（$1\le j\le n$、$j \ne i$），都存在连接城市 $i$ 与城市 $j$ 的道路。
- 特殊性质 C：对所有 $1 \le i \le q$，都有 $x_i = 1$。

## 样例 #1

### 输入

```
4 3
4 6 2 7
1 2 5
2 3 2
2 4 4
1 1
3 4
3 3```

### 输出

```
12
10
6```

# 题解

## 作者：Lgx_Q (赞：11)

### $n, q\le 400$

考虑对于每一天，枚举 $z_i$ 表示选择的城市，然后 $\mathcal O(n)$ 在树上求出 $x_i \to z_i$ 和 $z_i \to y_i$ 两条路径的长度，时间复杂度 $\mathcal O(n^2 q)$，期望得分 $\mathtt {16pts}$。

### $n, q\le 2000$

预处理，枚举城市 $p$，在树上 DFS 一遍求出所有路径 $p \to q$ 的长度，即可做到 $\mathcal O(n ^ 2 + nq)$，期望得分  $\mathtt {32pts}$。

### $n\le 2\times 10^5$，$q\le 3$

考虑使用树上倍增求出路径长度，时间复杂度 $\mathcal O(nq\log n)$，期望得分 $\mathtt {40pts}$。

### $n\le 2000$，$q\le 2\times 10^5$

此时要求我们不能直接枚举 $z_i$，考虑直接求出所有可能的 $(x, y)$ 的答案。枚举 $x$ 为根，DFS 一遍树，设 $f_y$ 表示 $x\to y$ 路径上选择一个 $z$ 的最优答案。考虑两种情况：

+ $z$ 在 $y$ 子树内，此时可以直接树形 DP 求出。

+ $z$ 在 $y$ 子树外，考虑 $z, y$ 两点的最近公共祖先 $c$，可以先让 $z$ 走到 $c$，再从 $c$ 走到 $y$。具体的，先进行一次树形 DP，再从上到下更新一遍（也可以理解为换根 DP）。

时间复杂度 $\mathcal O(n^2 + q)$，小常数 $\mathcal O(nq)$ 做法可能也可以过这一档分。期望得分 $\mathtt {52pts}$。


### 特殊性质 C

以 $1$ 为根，进行换根 DP 即可。

时间复杂度 $\mathcal O(n + q)$，加上之前的做法，期望得分 $\mathtt {76pts}$。

### $n,q\le 2\times 10^5$

考虑对于每个点求出 $d_u = \max\limits_{v = 1} ^ n \{c_v - 2\cdot\text{dist} (u, v)\}$，其中 $\text{dist} (u, v)$ 表示 $u, v$ 两点在树上的距离。可以类似特殊性质 C 的做法，换根求出。

考虑路径 $x_i \to y_i$ 以及 $z_i$ 的关系，找到 $z_i$ 走到路径 $x_i \to y_i$ 时的第一个点 $u$，那么 $d_u$ 即计算到了 $z_i$ 的答案。

所以，总答案应为 $c_{x_i} + c_{y_i} + \max\limits_{u \in \{x_i \to y_i\}} d_u$，可以树上倍增求出一段路径的 $d_u$ 的最大值，时间复杂度 $\mathcal O((n + q)\log n)$，期望得分 $\mathtt{100pts}$。

---

## 作者：Linnyt (赞：11)

# BFS + 树链剖分

## 题目描述

[原题链接](https://www.luogu.com.cn/problem/P11324)

## 前言

什么 DP，什么换根，不会写，怎么办？

其实这道题根本**不需要**！

只需要**简单的 BFS** 也可轻松解决！

## 解题思路

我们将 $bfs_{i}$ 的初始值设为 $c_{i}$，依次将每个点 $i$ 压入队列开始 BFS，如果从 $i$ 点出发到 $j$ 点并回来的总收入更优，即 $bfs_{i} < bfs_{j} - 2 \times dis _ {ij}$，则更新 $bfs_{i}$，并将 $j$ 压入队列。

最后我们得到的 $bfs_{i}$ 表示从 $i$ 点出发，开完第二场演讲并回来到点 $i$ 可获得**利润**的最大值。

BFS 代码实现如下：

```cpp
for (int i = 1; i <= n; ++i)
	bfs[i] = c[i];
for (int i = 1; i <= n; ++i) 
{
	queue<int> q;
	q.push(i);
	while (!q.empty())
	{
		int w = q.front(); q.pop();
		for (Edge j : mp[w])
		if (bfs[j.to] < bfs[w] - j.ct * 2)
		{
			bfs[j.to] = bfs[w] - j.ct * 2;
			q.push(j.to);
		}
	}
}
```

然后我们使用**树链剖分 + ST 表**，维护区间 $bfs_{i}$ 的最大值即可。

## 代码实现

[AC 记录](https://www.luogu.com.cn/record/191383024)

```cpp
/*BFS + Heavy-Light Decomposition*/
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAXN = 2e5 + 10;

struct Edge {
	int to, ct;
	bool operator< (const Edge &rhs) const {
		return rhs.ct < ct;
	}
};
vector<Edge> mp[MAXN];

int c[MAXN];
int bfs[MAXN], ans[MAXN], dis[MAXN], pre[MAXN];
int f[MAXN], sz[MAXN],son[MAXN], top[MAXN], id[MAXN];
int st[MAXN][20 + 5];
int cnt;

void dfs1(int x, int fa)
{
	dis[x] = dis[fa] + 1;
    f[x] = fa;
    int maxson = -1;
    for (Edge i : mp[x])
	    if (i.to != fa)
		{
			pre[i.to] = pre[x] + i.ct;
	        dfs1(i.to, x);
	        sz[x] += sz[i.to];
	        if (sz[i.to] > maxson)
			{
	            maxson = sz[i.to];
	            son[x] = i.to;
	        }
	    }
    sz[x]++;
}

void dfs2(int x, int ntop)
{
    id[x] = ++cnt;
    top[x] = ntop;
    if (!son[x]) return;
    dfs2(son[x], ntop);
    for (Edge i : mp[x])
	{
        if (i.to == f[x] || i.to == son[x]) continue;
        dfs2(i.to, i.to);
    }
}

int ask(int l, int r)
{
	int k = log(r - l + 1) / log(2);
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}

signed main()
{
	//freopen("speaker.in", "r", stdin);
	//freopen("speaker.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> c[i];
	for (int i = 1; i <= n - 1; ++i)
	{
		int u, v, ct;
		cin >> u >> v >> ct;
		mp[u].push_back({v, ct});
		mp[v].push_back({u, ct});
	}
	for (int i = 1; i <= n; ++i)
		bfs[i] = c[i];
	for (int i = 1; i <= n; ++i)//BFS 
	{
		queue<int> q;
		q.push(i);
		while (!q.empty())
		{
			int w = q.front(); q.pop();
			for (Edge j : mp[w])
				if (bfs[j.to] < bfs[w] - j.ct * 2)
				{
					bfs[j.to] = bfs[w] - j.ct * 2;
					q.push(j.to);
				}
		}
	}
	dfs1(1, 1);
    dfs2(1, 1);
    for (int i = 1; i <= n; ++i)
		ans[id[i]] = bfs[i];
    for (int i = 1; i <= n; ++i)//ST
		st[i][0] = ans[i];
    int maxk = log(n) / log(2) + 1;
    for (int j = 1; j <= maxk; ++j)
		for (int i = 1; i + (1 << j) <= n + 1; ++i)
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	for (int i = 1; i <= q; ++i)
	{
		int x, y;
		cin >> x >> y;
		int val = LLONG_MIN;
	    int fx = x, fy = y;
	    while (top[x] != top[y])
		{
	        if (dis[top[x]] < dis[top[y]]) swap(x, y);
	        val = max(val, ask(id[top[x]], id[x]));
	        x = f[top[x]];
	    }
	    if (dis[x] > dis[y]) swap(x, y);
	    val = max(val, ask(id[x], id[y]));
	    val = max(val, ans[id[x]]);
	    int dxy = pre[fx] + pre[fy] - 2 * pre[x];
		cout << c[fx] + val + c[fy] - dxy << endl;
	}
	return 0;
}
```

## 特别鸣谢

感谢 [@consequence](https://www.luogu.com.cn/user/551870)协助完成树链剖分的代码。

---

## 作者：cff_0102 (赞：8)

把路径拆一下，最后的收益变成 $c_x+c_y-dis_{x,y}$ 加上在图中选一个中间点能获得的最大收益。前面的不难计算，树上差分加 LCA 即可。那么题目转化为：给出一条树上路径，在树上找到一个点使得它的权值减去到路径的最短距离的两倍最大。

对于一个节点 $x$，如果它经过一条边到另一个节点 $y$ 演讲完再回来的收益比在这个节点直接演讲的收益还要大，即 $c_x<c_y-2\times w_{x,y}$，那么可以将 $c_x$ 直接修改为 $c_y-2\times w_{x,y}$。

如果用合适的顺序把所有 $c_i$ 更新成经过 $i$ 的最大的收益，那么就只需要求出 $x$ 到 $y$ 的路径上 $c_i$ 的最大值就可以了。

这个更新可以简单用 dfs 实现。具体的，在 dfs 中按顺序更新每一对相邻的节点的 $c$ 值，第一遍 dfs 即可把每个节点的 $c$ 值用子树中所有节点的 $c$ 值更新，第二遍 dfs 即可把每个节点的祖先节点更新的 $c$ 值推到它的子树上所有节点上。这样，整棵树的 $c$ 值就都被成功更新了。

最后可以用倍增求出树上两点路径上的最大 $c$ 值。

赛时因为直接把 $O(n^2\log n)$ 更新 $c$ 的部分分代码复制过来导致没发现最后求路径上最大 $c$ 值还需要用倍增实现导致 TLE，下面是赛时代码修改后可以 AC 的代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
using pii=pair<int,int>;
#define fi first
#define se second
int c[N],oc[N];
vector<pii>g[N];
int s[N];//到 1 的距离
int dep[N];
int fa[N][20];
int mxc[N][20];
void dfs(int x,int l){
	dep[x]=dep[l]+1;
	fa[x][0]=l;
	for(int i=1;i<=19;i++){
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for(pii t:g[x]){
		int y=t.fi,w=t.se;
		if(y==l)continue;
		s[y]=s[x]+w;
		dfs(y,x);
	}
}
int lca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int dis(int x,int y){
	int t=lca(x,y);
	return s[x]+s[y]-s[t]-s[t];
}
void dfsa(int x,int l){
	for(pii pp:g[x]){
		int y=pp.fi,w=pp.se;
		if(y==l)continue;
		c[y]=max(c[y],c[x]-w-w);
		dfsa(y,x);
		c[x]=max(c[x],c[y]-w-w);
	}
}
void dfs1(int x,int l){
	mxc[x][0]=c[x];
	for(int i=1;i<=19;i++){
		mxc[x][i]=max(mxc[x][i-1],mxc[fa[x][i-1]][i-1]);
	}
	for(pii pp:g[x]){
		int y=pp.fi;
		if(y==l)continue;
		dfs1(y,x);
	}
}
int sol(int x,int y){
	int ans=0;
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;i--)if(dep[fa[x][i]]>=dep[y])ans=max(ans,mxc[x][i]),x=fa[x][i];
	if(x==y)return max(ans,c[x]);
	for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])ans=max({ans,mxc[x][i],mxc[y][i]}),x=fa[x][i],y=fa[y][i];
	//注意要先更新再跳！
	return max({ans,mxc[x][1],mxc[y][1]});
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n,q;cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>c[i];oc[i]=c[i];
	}
	for(int i=1;i<n;i++){
		int u,v,w;cin>>u>>v>>w;
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
	dfs(1,0);//初始化倍增 LCA 数组
	dfsa(1,0);dfsa(1,0);//更新 c
	dfs1(1,0);//初始化倍增求 c 最大值数组
	while(q--){
		int x,y;cin>>x>>y;
		int ans=oc[x]+oc[y]-dis(x,y);
		cout<<ans+sol(x,y)<<"\n";
	}
	return 0;
}
```

---

## 作者：AK_400 (赞：5)

首先题面这个 $c_x+c_y+c_z-dis(x,z)-dis(z,y)$（其中 $dis(x,y)$ 表示 $x$，$y$ 的距离，下同）很难算，设 $(x,y)$ 为 $x$ 到 $y$ 路径上所有点构成的点集，有 
$$\begin{aligned} 
c_x+c_y+c_z-dis(x,z)-dis(z,y)&=\max_{k\in(x,y)} c_x+c_y+c_z-dis(x,k)-dis(k,z)-dis(z,k)-dis(z,y)\\
&=\max_{k\in(x,y)} c_x+c_y-dis(x,y)+c_z-2\times dis(z,k)
\end{aligned}$$

其中 $c_x+c_y-dis(x,y)$ 为定值，只需要最大化 $c_z-2\times dis(z,k)$，记 $f_i$ 表示 $k=i$，$z$ 在以 $1$ 为根时以 $i$ 为根的子树中时最大的 $c_z-2\times dis(z,k)$，记 $son_i$ 表示 $i$ 的所有子节点构成的点集，$w(x,y)$ 表示端点为 $x,y$ 的边的边权，有
$$f_i=\max(\max_{x\in son_i}f_x-2\times w(i,x),c_i)$$

记 $g_i$ 表示 $k=i$，$z\in[1,n]$ 时最大的 $c_z-2\times dis(z,k)$，记 $fa_i$ 表示以 $1$ 为根时 $i$ 的父亲节点，有
$$g_i=\max(f_i,g_{fa_i}-2\times w(i,fa_i))$$

于是答案为 
$$c_x+c_y-dis(x,y)+\max_{k\in(x,y)}g_k$$

其中链上最大值，可以倍增或者树剖。

时间复杂度 $O(n\log n)$（倍增）或 $O(n\log^2n)$（树剖），可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
int c[200005];
vector<pair<int,int>>e[200005];
int fa[200005],faw[200005],dp[200005],sz[200005],son[200005],top[200005],dfn[200005],rnk[200005],dpw[200005],tot;
int f[200005],g[200005];
void dfs(int p){
    sz[p]=1;
    f[p]=c[p];
    for(auto x:e[p]){
        if(x.first==fa[p])continue;
        fa[x.first]=p;
        faw[x.first]=x.second;
        dp[x.first]=dp[p]+1;
        dpw[x.first]=dpw[p]+x.second;
        dfs(x.first);
        sz[p]+=sz[x.first];
        if(!son[p]||sz[x.first]>sz[son[p]])son[p]=x.first;
        f[p]=max(f[p],f[x.first]-2*x.second);
    }
}
void dfs(int p,int tp){
    rnk[dfn[p]=++tot]=p;
    top[p]=tp;
    if(son[p])dfs(son[p],tp);
    for(auto x:e[p]){
        if(x.first==fa[p]||x.first==son[p])continue;
        dfs(x.first,x.first);
    }
}
void dfs1(int p){
    g[p]=f[p];
    if(p!=1)g[p]=max(g[p],g[fa[p]]-2*faw[p]);
    for(auto x:e[p]){
        if(x.first==fa[p])continue;
        dfs1(x.first);
    }
}
int t[800005];
#define ls (p<<1)
#define rs (p<<1|1)
#define mid (l+r>>1)
void pu(int p){
    t[p]=max(t[ls],t[rs]);
}
void bd(int l,int r,int p){
    if(l==r){
        t[p]=g[rnk[l]];
        return;
    }
    bd(l,mid,ls);
    bd(mid+1,r,rs);
    pu(p);
}
int qu(int l,int r,int ml,int mr,int p){
    if(ml<=l&&r<=mr)return t[p];
    int res=-2e18;
    if(mid>=ml)res=max(res,qu(l,mid,ml,mr,ls));
    if(mid<mr)res=max(res,qu(mid+1,r,ml,mr,rs));
    return res;
}
#undef ls 
#undef rs 
#undef mid 
int lca(int x,int y){
    while(top[x]!=top[y]){
        if(dp[top[x]]<dp[top[y]])swap(x,y);
        x=fa[top[x]];
    }
    return dp[x]>dp[y]?y:x;
}
int qu_chain(int x,int y){
    int res=-2e18;
    while(top[x]!=top[y]){
        if(dp[top[x]]<dp[top[y]])swap(x,y);
        res=max(res,qu(1,n,dfn[top[x]],dfn[x],1));
        x=fa[top[x]];
    }
    if(dp[x]<dp[y])swap(x,y);
    res=max(res,qu(1,n,dfn[y],dfn[x],1));
    return res;
}
void read(int &x){
    x=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0',c=getchar();
}
void slv(){
    read(n),read(q);
    for(int i=1;i<=n;i++)read(c[i]);
    for(int i=1;i<n;i++){
        int u,v,w;
        read(u),read(v),read(w);
        e[u].push_back({v,w});
        e[v].push_back({u,w});
    }
    dfs(1);
    dfs(1,1);
    dfs1(1);
    bd(1,n,1);
    while(q--){
        int x,y;
        read(x),read(y);
        int ans=c[x]+c[y]-dpw[x]-dpw[y]+2*dpw[lca(x,y)]+qu_chain(x,y);
        printf("%lld\n",ans);
    }
    return;
}
signed main(){
    slv();
    return 0;
}
```

---

## 作者：sjzsd147 (赞：3)

## 题意简述
给出一颗带边权和点权的树，给出两个点 $x,y$，再选择一个点 $z$，求 $c_x+c_y+c_z-dis_{x,z}-dis_{z,y}$ 的最大值。

## 解法分析
注意到本题与树上路径有关，因此先使用树上倍增或是树链剖分的方法求出 $x,y$ 两点的 LCA。

接下来考虑如何选取中间点 $z$，由于这是一颗树，因此如果 $z$ 不在 $x$ 到 $y$ 的路径上，必然是从路径上一点出发前往 $z$ 并原路返回到这个点。若 $z$ 点在路径上，则我们也可以理解为从 $z$ 点出发走到 $z$ 再原路返回 $z$。因此我们只需要考虑每个点周围贡献最大的 $z$ 所提供的贡献即可。并将原过程视为从起点走到中途一个点，前往 $z$，在回到中途点，再前往终点的过程。

对于点 $i$，点 $z$ 所能提供的贡献是 $c_z-2\times dis_{i,z}$。注意到这个东西和最短路十分类似，因此我们可以用 dijkstra 求解。

具体的，我们将每个点的初值设为 $c_i$ 并将所有点压入一个大根堆。然后用边权为 $-2\times w$ 的方式扩展即可。

求解出每个点周围的最大贡献后，我们考虑求一条路径上的最大贡献，显然这种东西可以使用倍增维护。设 $f_{i,j}$ 表示 $i$ 的 $2^j$ 级祖先，$g_{i,j}$ 表示包括点 $i$ 和往上的 $2^j-1$ 个点的最大贡献（即 $g_{i,j}$ 不包括 $f_{i,j}$ 的贡献）。

显然，$g_{i,0}$ 为 $i$ 在上一步中求出的最大贡献，我们有
$$
f_{i,j}\gets f_{f_{i,j-1},j-1}
$$
$$
g_{i,j}\gets \max(g_{i,j-1},g_{f_{i,j-1},j-1})
$$

考虑每条路径时，我们只需要在倍增的同时取最大值即可。

由于我们在倍增时没有考虑最顶端的点的贡献，因此我们还需要再额外考虑从 LCA 出发前往 $z$ 产生的贡献。

总时间复杂度 $O(n\log n+q\log n)$，可以通过此题。

## 代码

```cpp
#include<bits/stdc++.h>
#define mp make_pair
using namespace std;
using ll=long long;

template<typename _T>
inline _T read(){
	_T res=0;
	char c=getchar();
	while(!isdigit(c)){
		c=getchar();
	}
	while(isdigit(c)){
		res=(res<<1)+(res<<3)+(c^48);
		c=getchar();
	}
	return res;
}

const int MAXN=2e5+5;
int n,Q;
int c[MAXN];
ll disc[MAXN];
ll dis[MAXN];
bitset<MAXN>vis;
int fa[MAXN][32];
ll g[MAXN][32];
int dep[MAXN];
int lg2[MAXN];
using Edge=pair<int,int>;
vector<Edge>e[MAXN];

void dfs(int p,int f){
	dep[p]=dep[f]+1;
	fa[p][0]=f;
	g[p][0]=disc[p];
	for(int i=1;(1<<i)<dep[p];i++){
		fa[p][i]=fa[fa[p][i-1]][i-1];
		g[p][i]=max(g[p][i-1],g[fa[p][i-1]][i-1]);
	}
	for(auto i:e[p]){
		auto [v,w]=i;
		if(v==f) continue;
		dis[v]=dis[p]+w;
		dfs(v,p);
	}
}

int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=lg2[dep[u]-dep[v]];i>=0;i--){
		if(dep[fa[u][i]]>=dep[v]){
			u=fa[u][i];
		}
	}
	if(u==v) return u;
	for(int i=lg2[dep[u]-1];i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i];
			v=fa[v][i];
		}
	}
	return fa[u][0];
}

int main(){
	ios::sync_with_stdio(0);
	cout.tie(0);
	n=read<int>();
	Q=read<int>();

	lg2[0]=-1e9;
	lg2[1]=0;
	for(int i=2;i<=n;i++){
		lg2[i]=lg2[i>>1]+1;
	}

	for(int i=1;i<=n;i++){
		c[i]=read<int>();
		disc[i]=c[i];
	}
	for(int i=1;i<n;i++){
		int u=read<int>(),v=read<int>(),w=read<int>();
		e[u].push_back(mp(v,w));
		e[v].push_back(mp(u,w));
	}

	priority_queue<pair<int,int>> q;
	for(int i=1;i<=n;i++){
		q.push(mp(disc[i],i));
	}
	while(!q.empty()){
		auto u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto i:e[u]){
			auto [v,w]=i;
			if(disc[u]-2*w>disc[v]){
				disc[v]=disc[u]-2*w;
				q.push(mp(disc[v],v));
			}
		}
	}

	dfs(1,0);

	while(Q--){
		int x=read<int>(),y=read<int>();
		int lc=lca(x,y);
		ll cst=c[x]+c[y]+dis[lc]*2-dis[x]-dis[y];
		ll res=disc[lc];
		for(int i=lg2[dep[x]-dep[lc]];i>=0;i--){
			if(dep[fa[x][i]]>=dep[lc]){
				res=max(res,g[x][i]);
				x=fa[x][i];
			}
		}
		for(int i=lg2[dep[y]-dep[lc]];i>=0;i--){
			if(dep[fa[y][i]]>=dep[lc]){
				res=max(res,g[y][i]);
				y=fa[y][i];
			}
		}
		cout<<res+cst<<"\n";
	}
	return 0;
}
```

---

## 作者：consequence (赞：3)

# 【MX-S7-T2】「SMOI-R2」Speaker 题解

先考虑特殊性质 $C$。

设 $1$ 为根节点。

设 $dp_x$ 表示以 $x$ 为根的子树所能贡献的最大值，对于 $x$ 的一个孩子 $s$，设它们之间的距离为 $d$，显然有转移：$dp_x = \max dp_s - 2d$。

$dp_x$ 的初值为 $c_x$。

对于一个点对 $(a, b)$，设两点间的路径为 $A$，答案就应当是 $c_a + c_b + \max\limits_{i \in A} dp_i - dis_{a, b}$，树剖后用 ST 表维护路径上最大值即可。

再考虑一般情况。

相较于特殊情况，一般情况的答案还可能是在 $lca_{a, b}$ 到根节点的路径上的某个点的子树上的点演出。

设 $fdp_x$ 表示点 $x$ 在这种情况下的答案的答案，设 $p$ 为 $x$ 的父亲，有转移 $fdp_x = \max(c_x, fdp_p - 2dis_{x, p})$。

$fdp_x$ 的初值为 $dp_x$。

最后答案即为 $c_a + c_b + \max\limits_{i \in A} (dp_i,fdp_{lca_{a, b}}) - dis_{a, b}$。

时间复杂度 $O(n \log n)$。

## 丑陋的赛时 AC 代码：

```cpp
#include <bits/stdc++.h>
#define mp make_pair
#define fr first
#define sc second

using namespace std;

typedef pair<long long, int> pii;
const int MAXN = 2e5 + 10;
vector<pii> v[MAXN];
long long st[MAXN][24 + 5];
long long dp[MAXN], c[MAXN], fdp[MAXN], dis[MAXN];
int f[MAXN], d[MAXN], sz[MAXN], son[MAXN], top[MAXN], id[MAXN];
int n, q, cnt;

long long ask(int l, int r) {
	int k = log(r - l + 1) / log(2);
	return max(st[l][k], st[r - (1 << k) + 1][k]);
}
long long query(int x, int y) {
    long long val = LLONG_MIN;
    int fx = x, fy = y;
    while (top[x] != top[y]) {
        if (d[top[x]] < d[top[y]]) swap(x, y);
        val = max(val, ask(id[top[x]], id[x]));
        x = f[top[x]];
    }
    if (d[x] > d[y]) swap(x, y);
    val = max(val, ask(id[x], id[y]));
    val = max(val, fdp[id[x]]);
    return val + 2 * dis[x] - dis[fx] - dis[fy] + c[fx] + c[fy];
}
void dfs1(int x, int p) {
    d[x] = d[p] + 1;
    f[x] = p;
    int maxson = -1;
    for (int i = 0; i < v[x].size(); ++i) {
        int nx = v[x][i].sc;
        if (nx == p) continue;
        dis[nx] = dis[x] + v[x][i].fr;
        dfs1(nx, x);
        sz[x] += sz[nx];
        if (sz[nx] > maxson) {
            maxson = sz[nx];
            son[x] = nx;
        }
    }
    sz[x]++;
}
void dfs2(int x, int ntop) {
    id[x] = ++cnt;
    top[x] = ntop;
    if (!son[x]) return;
    dfs2(son[x], ntop);
    for (int i = 0; i < v[x].size(); ++i) {
        int nx = v[x][i].sc;
        if (nx == f[x] || nx == son[x]) continue;
        dfs2(nx, nx);
    }   
}
void dfs3(int x, int p) {
    dp[id[x]] = c[x];
    for (int i = 0; i < v[x].size(); ++i) {
        int nx = v[x][i].sc;
        if (nx == p) continue;
        dfs3(nx, x);
        dp[id[x]] = max(dp[id[x]], dp[id[nx]] - 2 * v[x][i].fr);
    }
    fdp[id[x]] = dp[id[x]];
}
void dfs4(int x, int p) {
    for (int i = 0; i < v[x].size(); ++i) {
        int nx = v[x][i].sc;
        if (nx == p) {
            fdp[id[x]] = max(fdp[id[x]], fdp[id[nx]] - 2 * v[x][i].fr);
            break;
        }
    }
    for (int i = 0; i < v[x].size(); ++i) {
        int nx = v[x][i].sc;
        if (nx == p) continue;
        dfs4(nx, x);
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i < n; ++i) {
        int a, b;
        long long nd;
        cin >> a >> b >> nd;
        v[a].push_back(mp(nd, b));
        v[b].push_back(mp(nd, a));
    }
    dfs1(1, 1);
    dfs2(1, 1);
    //树链剖分
    dfs3(1, 1);//转移dp
    dfs4(1, 1);//转移fdp，其实可以在建ST表时直接用fdp
    int maxk = log(n) / log(2) + 1;
    for (int i = 1; i <= n; ++i) st[i][0] = dp[i];
    for (int j = 1; j <= maxk; ++j) {
		for (int i = 1; i + (1 << j) <= n + 1; ++i) {
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}//ST表
    for (int i = 1; i <= q; ++i) {
        int a, b;
        cin >> a >> b;
        cout << query(a, b) << "\n";
    }
    return 0;
}
```

---

## 作者：Rt__ (赞：2)

[P11324 【MX-S7-T2】「SMOI-R2」Speaker](https://www.luogu.com.cn/problem/P11324)
## 题意简述
给一棵树，以及每条边的代价，在点 $u$ 演讲可以获得 $c_u$ 的权值，给定 $q$ 个询问，每次询问给定 $x$ 和 $y$，求出一天在 $x$、$y$ 和其他任意一个点 $z$ 上演讲三次所能获得的最大权值

即求：
$$
W = c_x + c_z + c_y + d_{x, z} + d_{z, y}
$$
的值。
## 思路
$n$ 和 $q$ 都有 $10^5$ 级别，考虑 $q\log n$ 做法。我们可以先不考虑点 $z$，快速求出 $x$ 到 $y$ 的距离可以用树上倍增的做法求 LCA，并且顺便用倍增数组保存每一步跳的距离。这样我们就可以吧 $c_x$、$c_y$、$d_{x,y}$ 快速求出。

然后我们考虑点 $z$。他可以看作 $x->y$ 路径上伸出来的一个枝节（可以向上/下），或者它本身就是在 $x->y$ 路径上的点（例如 $x$ $y$ 的公共祖先）。

![](https://cdn.luogu.com.cn/upload/image_hosting/902xvwnl.png)

所以我们可以把每个点向下延伸出去（或者不延伸）的最大贡献求出来，再次利用一个倍增数组来保存跳一次经过所有的点的最大延伸贡献，在找 LCA 时取 max，就可以找出若向下延伸可以做的最大贡献。

再考虑向上延伸。发现若向上延伸，一定是再 LCA 处。所以我们在 DFS 时，顺便记录向上延伸的最大贡献，就可以和之前取的 max 再取 max 加到答案里就可以。

一定要注意在处理向上延伸的情况时，不只有

![](https://cdn.luogu.com.cn/upload/image_hosting/44udqxv1.png)

还可能是

![](https://cdn.luogu.com.cn/upload/image_hosting/p5a5r32i.png)

的情况，一定要考虑周全。


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

inline ll read(){
    ll res = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        res = res * 10 + c - '0';
        c = getchar();
    }
    return res * f;
}

const int N = 300010;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll c[N];
ll h[N], ne[N * 2], e[N * 2], w[N * 2], idx;
void add(ll a, ll b, ll c){
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx ++;
    return;
}

ll f[N][20], max_sp[N], cost[N][20], max_down[N][20], deep[N], max_up[N];

void dfs(ll u, ll fa){
    f[u][0] = fa;
    deep[u] = deep[fa] + 1;
    max_sp[u] = c[u];
    for(int i = 1; i <= 17; i ++){
        f[u][i] = f[f[u][i - 1]][i - 1];
        cost[u][i] = cost[u][i - 1] + cost[f[u][i - 1]][i - 1];
    }
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa)continue;
        cost[j][0] = w[i];
        dfs(j, u);
        max_sp[u] = max(max_sp[u], max_sp[j] - 2 * w[i]);
    }
    return;
}

void dfss(ll u, ll fa, ll maxx){
    max_down[u][0] = max(max_sp[u], max_sp[fa]);
    for(int i = 1; i <= 17; i ++){
        max_down[u][i] = max(max_down[u][i - 1], max_down[f[u][i - 1]][i - 1]);
    }
    max_up[u] = max(maxx, max_sp[u]);
    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(j == fa)continue;
        dfss(j, u, max_up[u] - 2 * w[i]);
    }
    return;
}

ll ans(ll u, ll v){
    ll res = c[u] + c[v];
    ll maxx = max(max_sp[u], max_sp[v]);
    if(deep[u] < deep[v])swap(u, v);
    for(int i = 17; i >= 0; i --){
        if(deep[f[u][i]] >= deep[v]){
            res -= cost[u][i];
            maxx = max(maxx, max_down[u][i]);
            u = f[u][i];
        }
    }
    if(u == v){
        maxx = max(maxx, max_up[u]);
        maxx = max(maxx, max_sp[u]);
        return res + maxx;
    }
    for(int i =17; i >= 0; i --){
        if(f[u][i] != f[v][i]){
            res -= cost[u][i];
            res -= cost[v][i];
            maxx = max(maxx, max_up[u]);
            maxx = max(maxx, max_up[v]);
            maxx = max(maxx, max_down[u][i]);
            maxx = max(maxx, max_down[v][i]);
            u = f[u][i];
            v = f[v][i];
        }
    }
    res -= cost[u][0];
    res -= cost[v][0];
    ll LCA = f[u][0];
    maxx = max(maxx, max_up[LCA]);
    maxx = max(maxx, max_down[u][0]);
    maxx = max(maxx, max_down[v][0]);
    return res + maxx;
}

signed main(){
    memset(h, -1, sizeof h);
    ll n = read(), q = read();
    for(int i = 1; i <= n; i ++){
        c[i] = read();
    }
    for(int i = 1; i < n; i ++){
        ll u = read(), v = read(), W = read();
        add(u, v, W), add(v, u, W);
    }
    dfs(1, 0);
    dfss(1, 0, 0);
    while(q --){
        ll u = read(), v = read();
        cout << ans(u, v) << endl;
    }    
    return 0;
}
```

---

## 作者：forever_nope (赞：2)

设 $\text{son}(x)$ 表示 $x$ 的儿子集合，钦定以 $1$ 为根。

设 $\text{fa(x)}$ 表示 $x$ 的父亲节点，同样钦定以 $1$ 为根。

设 $\text{path}(u,v)$ 表示 $u\to v$ 路径上所有点的集合。

设 $\text{dis}(u,v)$ 表示 $u\to v$ 的路径上所有边的边权和。

注意到查询 $x,y$ 的答案一定可以表示为：

$$
c_x+c_y-\text{dis}(x,y)+\max_{z,p\in\text{path}(x,y)}\{c_z-2\text{dis}(p,z)\}
$$

其中 $z$ 表示第二场演讲所在的城市，$p$ 为 $x\to z,z\to y$ 交点离 $z$ 最远的点。

注意到，此时 $p$ 可能会取到更多的点，但是因为我们取最大值一定能包含最优解的情况，而且其他情况（包含合法但不优的和不合法的）一定不会优于最优解，因此这个公式就是正确的。

不妨设：

$$
f(p)=\max_z\{c_z-2\text{dis}(p,z)\}
$$

则答案表示为：

$$
c_x+c_y-\text{dis}(x,y)+\max_{p\in\text{path}(x,y)}f(p)
$$

可以重链剖分或者倍增求出，现在考虑如何求 $f(p)$。

不妨设 $g(p)$ 表示在 $p$ 的子树中的答案，容易得到转移方程：

$$
g(p)=\max\left\{c_p,\max_{z\in\text{son}_p}\{g(z)-2\text{dis}(p,z)\}\right\}
$$

因此，容易得到 $f(p)$ 的转移方程：

$$
f(p)=\max\{g(p),f(\text{fa}(p))-2\text{dis}(p,\text{fa}(p))\}
$$

这就是换根 DP，直接求解即可，复杂度瓶颈在求路径 $\max$，总时间复杂度为 $\mathcal O(n\log n)$。

代码：

```cpp
constexpr int N = 2e5 + 10;

int n, q, c[N];

struct edge {
	int v, w;
	edge() = default;
	edge(int v, int w): v(v), w(w) {}
};

vector<edge> G[N];

int f[N], g[N];
int dep[N], dis[N];
int fa[N][21], mx[N][21];

void dfs1(int u, int ff) {
	dep[u] = dep[ff] + 1;
	for (int k = 1; k <= 20; ++k)
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
	g[u] = c[u];
	for (auto t : G[u]) {
		int v = t.v, w = t.w;
		if (v == ff)
			continue;
		fa[v][0] = u;
		dis[v] = dis[u] + w;
		dfs1(v, u);
		g[u] = max(g[u], g[v] - 2 * w);
	}
}

void dfs2(int u, int ff, int lt) {
	mx[u][0] = f[u] = max(g[u], f[ff] - 2 * lt);
	for (int k = 1; k <= 20; ++k)
		mx[u][k] = max(mx[u][k - 1], mx[fa[u][k - 1]][k - 1]);
	for (auto t : G[u])
		if (t.v != ff)
			dfs2(t.v, u, t.w);
}

void init() {
	dfs1(1, 0);
	dfs2(1, 0, 0);
}

int lca(int x, int y) {
	if (dep[x] < dep[y])
		swap(x, y);
	for (int k = 20; k >= 0; --k)
		if (dep[fa[x][k]] >= dep[y])
			x = fa[x][k];
	if (x == y)
		return x;
	for (int k = 20; k >= 0; --k)
		if (fa[x][k] != fa[y][k])
			x = fa[x][k], y = fa[y][k];
	return fa[x][0];
}

int path(int x, int y) {
	int res = -1e18;
	if (dep[x] < dep[y])
		swap(x, y);
	for (int k = 20; k >= 0; --k)
		if (dep[fa[x][k]] >= dep[y]) {
			res = max(res, mx[x][k]);
			x = fa[x][k];
		}
	if (x == y)
		return max(res, mx[x][0]);
	for (int k = 20; k >= 0; --k)
		if (fa[x][k] != fa[y][k]) {
			res = max(res, mx[x][k]);
			res = max(res, mx[y][k]);
			x = fa[x][k], y = fa[y][k];
		}
	res = max(res, mx[x][1]);
	res = max(res, mx[y][1]);
	return res;
}

int diss(int x, int y) {
	return dis[x] + dis[y] - 2 * dis[lca(x, y)];
}

int getans(int x, int y) {
	return c[x] + c[y] - diss(x, y) + path(x, y);
}

void Main() {
	read(n, q);
	for (int i = 1; i <= n; ++i)
		read(c[i]);
	for (int i = 2; i <= n; ++i) {
		int u, v, w;
		read(u, v, w);
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	init();
	while (q--) {
		int x = read<int>();
		int y = read<int>();
		writeln(getans(x, y));
	}
	return;
}
```

---

## 作者：Charlie_ljk (赞：2)

~~感觉 T2 严格简单于 T1。~~

考虑只有以下几种情况：

- $z$ 在 $x\to y$ 路径上，$c_x+c_y+c_z-dis(x,y)$。
- $z$ 在 $x$ 或 $y$ 的子树中，以在 $x$ 子树中为例：$c_x+c_y+c_z-dis(x,y)-2dis(x,z)$。
- $z$ 在 $lca(x,y)$ 的子树内但不在 $x$ 或 $y$ 的子树内，设 $u=lca(x,z),v=lca(y,z)$，假设 $dep_u\ge dep_v$，则答案为 $c_x+c_y+c_z-dis(x,y)-2dis(u,z)$。
- $z$ 在 $lca(x,y)$ 的子树外，$c_x+c_y+c_z-dis(x,y)-2dis(lca(x,y),z)$。

设 $subtree_x$ 表示 $x$ 的子树集合，$f_{x}$ 表示 $\max\limits_{y\in subtree_x}c_y-2dis(x,y)$。

那么前 $3$ 种情况可并为一种：设 $u$ 表示 $x\to y$ 路径上的一点，答案为 $c_x+c_y-dis(x,y)+f_u$ 的最大值，$f_x$ 是可以直接树形 DP 求出来的，后面的东西可以直接用树剖加 ST 表维护。

现考虑第四种情况，从换根 DP 的角度，我们可以求出 $g_x$ 表示 $\max\limits_{y\not\in subtree_x}c_y-2dis(x,y)$，则此时答案为 $c_x+c_y-dis(x,y)+g_{lca(x,y)}$，发现和上一种情况的格式完全相同，所以根本不需要去除 $x$ 子树内的贡献，因为若 $g_{x}<f_{x}$ 则第四种情况一定不优。

所以重新设 $g_{x}$ 表示 $\max\limits_{y=1}^{n}c_y-2dis(x,y)$，设 $u$ 表示 $x\to y$ 路径上的一点，以上四种情况的答案均为 $c_x+c_y-dis(x,y)+g_u$ 的最大值，$g_x$ 在 $f_x$ 的基础上再跑一遍树形 DP 求出，后面的一样用树剖加 ST 表维护。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define endl '\n'
#define sort stable_sort
using namespace std;
const int N=2e5+10;
template<typename Tp> inline void read(Tp&x)
{
	x=0;register bool z=true;
	register char c=getchar_unlocked();
	for(;!isdigit(c);c=getchar_unlocked()) if(c=='-') z=0;
	for(;isdigit(c);c=getchar_unlocked()) x=(x<<1)+(x<<3)+(c^48);
	x=(z?x:~x+1);
}
template<typename T,typename ...Tp> inline void read(T &x,Tp &...y){read(x);read(y...);}
template<typename Tp> inline void wt(Tp x){if(x>9)wt(x/10);putchar_unlocked((x%10)+'0');}
template<typename Tp> inline void write(Tp x){if(x<0)putchar_unlocked('-'),x=~x+1;wt(x);}
template<typename T,typename ...Tp> inline void write(T x,Tp ...y){write(x);putchar_unlocked(' ');write(y...);}
int n,m,tot,a[N],sz[N],fa[N],son[N],dep[N],dfn[N],top[N],mx[20][N];
int head[N],nxt[N<<1],to[N<<1],w[N<<1]; ll f[N],dis[N];
inline void add(int x,int y,int z)
{nxt[++tot]=head[x],to[tot]=y,w[tot]=z,head[x]=tot;}
inline void dfs1(int x,int t)
{
	dep[x]=dep[fa[x]=t]+1,sz[x]=1;
	for(int i=head[x],y;y=to[i];i=nxt[i]) if(y!=t)
	{
		dis[y]=dis[x]+w[i],dfs1(y,x);
		sz[x]+=sz[y],sz[y]>sz[son[x]]&&(son[x]=y);
	}
}
inline void dfs2(int x,int t)
{
	dfn[x]=++tot,top[x]=t; if(son[x]) dfs2(son[x],t);
	for(int i=head[x],y;y=to[i];i=nxt[i]) if(y!=fa[x]&&y!=son[x]) dfs2(y,y);
}
inline int lca(int x,int y)
{
	for(;top[x]!=top[y];x=fa[top[x]])
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
	return dep[x]<dep[y]?x:y;
}
inline ll getdis(int x,int y) {return dis[x]+dis[y]-(dis[lca(x,y)]<<1);}
inline void dfs3(int x)
{
	f[x]=a[x]; for(int i=head[x],y;y=to[i];i=nxt[i])
		if(y!=fa[x]) dfs3(y),f[x]=max(f[x],f[y]-(w[i]<<1));
}
inline void dfs4(int x)
{
	for(int i=head[x],y;y=to[i];i=nxt[i]) if(y!=fa[x])
		f[y]=max(f[y],f[x]-(w[i]<<1)),dfs4(y);
}
inline int getmax(int l,int r)
{int t=__lg(r-l+1); return max(mx[t][l],mx[t][r-(1<<t)+1]);}
inline int ask(int x,int y)
{
	int res=0; for(;top[x]!=top[y];x=fa[top[x]])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=max(res,getmax(dfn[top[x]],dfn[x]));
	}
	if(dep[x]>dep[y]) swap(x,y);
	return max(res,getmax(dfn[x],dfn[y]));
}
signed main()
{
	read(n,m); for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1,x,y,z;i<n;i++) read(x,y,z),add(x,y,z),add(y,x,z);
	tot=0,dfs1(1,0),dfs2(1,1),dfs3(1),dfs4(1);
	for(int i=1;i<=n;i++) mx[0][dfn[i]]=f[i];
	for(int i=1;i<=__lg(n);i++) for(int j=1;j+(1<<i)-1<=n;j++)
		mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
	for(int i=1,x,y;i<=m;i++,puts(""))
		read(x,y),write(a[x]+a[y]-getdis(x,y)+ask(x,y));
}
```

---

## 作者：Ling_zeroo (赞：1)

赛时感觉 T2 比 T1 好做，随便写了一发过了，但是 T1 调了半天也没调出来...

## Description

记 $path(a,b)$ 上的边权和为 $dis(a,b)$。

在一棵树上，给定两个节点 $x,y$，找到一个节点 $p$（可以和 $x,y$ 相同），使得 $c_x+c_y+c_p$ 与 $dis(x,p)+dis(p,y)$ 之差最大，**重复经过的边权计算多次**。

## Solution



发现对于任意一个 $p$，$dis(x,y)$ 一定会被计算一次且仅计算一次，而剩下的边权就是 
**$p$ 到这条路径的边权和的两倍**，因为一次是出去到 $p$，一次是从 $p$ 回来。问题转化为最大化 $c_p-2\times dis(p,u)$，其中 $u$ 是 $path(x,y)$ 上的节点。

可以预处理出每个节点 $u$ 的上述最大值 $f_u=\max\{c_p-2\times dis(p,u)\}$，树剖以后挂在 st 表或者线段树上，查询 $t=\max\limits_{u\in path(x,y)}f_u$ , 答案即为 $c_x+c_y-dis(x,y)+t$。

虽然 $\max\limits_{u\in path(x,y)}f_u$ 中，可能有部分节点 $u$ 取最大值时，到选择的 $p$ 的路径会经过 $x$ （或者 $y$），使得 $path(x,y)$ 的边权部分被计算两次。但是这也意味着 $f_u$ **一定不优于** $f_x$（或者$f_y$），最后的最大值一定不会是 $f_u$，也就不需要分出来讨论。

接着考虑怎样预处理。我会树上 dp！

记 $g_u$ 为在以 $u$ 为根的子树内，$c_p-dis(p,u)$ 的最大值。转移是简单的：

$$g_u = \max\{c_u,g_v - 2 \times w_{u,v}\}$$

其中 $v$ 是 $u$ 的儿子，$w_{u,v}$ 是 $u,v$ 间的边权。

于是可以再由 $g_u$ 求得 $f_u$，即：

$$f_u = \max\{g_u, f_{fa}-2\times w_{fa,u}\}$$

跑两个 dfs 预处理就可以了。但是要注意这里的最大值可以是负数，所以极小值的边界要开到 $-10^{18}$。

预处理时间复杂度 $O(n)$，查询时间复杂度 $O(q\log n)$。

[AC 记录](https://www.luogu.com.cn/record/190817780)
[code](https://luogu.com.cn/paste/9kv55kui)

---

## 作者：xiezheyuan (赞：1)

## 简要题意

给定一个 $n$ 个点的树，边有边权，点有点权。定义两点间的距离为这两点组成的简单路径的所有边的边权和。

有 $q$ 次询问，每次询问给出两个点 $x,y$，你需要选出树上的某一个点 $z$（$z$ 可以与 $x,y$ 中的一个或两个相同）。定义你的收益为 $x,y,z$ 三点的点权和，代价为 $x$ 到 $z$ 的距离加上 $z$ 到 $y$ 的距离，求收益与代价之差的最大值。注意这个值可能为负数。

$1\leq n,q\leq 2\times 10^5$。

## 思路

评价：只要你决定去认真想一下这道题，这道题还是非常简单的

先考虑一下我们选择的点可能在什么位置，不难发现只有下面两种不同的情况。为了方便，默认树以 $1$ 为根。

### 情况 1

![](https://cdn.luogu.com.cn/upload/image_hosting/7tqt2aku.png)

注意上图中的“边”并不对应原树上的边，而是一条挂着其他节点的链，其中 $L$ 为 $x,y$ 的 LCA，定义 $d(x,y)$ 表示 $x,y$ 之间的距离，$d_x$ 表示 $d(1,x)$，下同。

在这种情况下，$r$ 为路径 $(x,y)$ 上的点，而 $z$ 是 $r$ 的后代，这种情况下，答案为：

$$
\begin{aligned}
&c_x+c_y+c_z-(d(x,y)+2d(r,z))\\
&=(c_x+c_y-d(x,y))+(c_z-2d(r,z))\\
&=(c_x+c_y-d(x,y))+(c_z-2d_z+2d_r)
\end{aligned}
$$

不妨令 $f(r)$ 表示 $c_z-2d_z+2d_r$ 的最大值，那么就转换成求路径 $(x,y)$ 上 $f(r)$ 的最大值，直接重链剖分配合 ST 表就可以做到单次 $O(\log n)$。

现在的问题是求 $f(r)$ 了，如果用 dfn 序配合 ST 表就太笨了，不妨考虑树形 dp，根据 $f(r)$ 的意义不难得到：

$$
f(u)=\max\left(c_u, \max_{v\in\mathrm{son}(u)} f(v)-2d(u,v)\right)
$$

于是就可以 $O(n)$ 预处理出 $f$。

### 情况 2

![](https://cdn.luogu.com.cn/upload/image_hosting/prcxtanm.png)

在这种情况下，$r$ 位于路径 $(1,L)$ 上，答案为：

$$
\begin{aligned}
&c_x+c_y+c_z-(d(x,y)+2d(r,L)+2d(r,z))\\
&=c_x+c_y+c_z-(d(x,y)+2d_L-2d_r+2d_z-2d_r)\\
&=(c_x+c_y-d(x,y)-2d_L)+(c_z+4d_r-2d_z)
\end{aligned}
$$

可以转换成求 $(1,L)$ 路径上 $g(r)=c_z+4d_r-2d_z$ 的最大值，和情况 1 类似，我们也可以推导出递推式：

$$
g(u)=\max\left(c_u+2d_u, \max_{v\in\mathrm{son}(u)} g(v)-4d(u,v)\right)
$$

注意到根据贪心原理，一定不会选择绕路，所以不用担心 $z$ 最优值取到情况 $1$ 中的 $z$ 的情况。

### 花絮

一定要注意不要溢出了！注意在 `x << y` 中无论 `y` 式什么类型，表达式的类型（以及溢出条件）都是 `x` 的类型！

最后给一组可以验证自己的代码是否存在溢出问题的小数据：

```
6 3
171058112 33734694 648921431 960073898 909444560 338871030
1 2 711012123
1 3 57531393
1 4 939004479
1 5 431978718
1 6 654028339
5 3
1 4
4 2
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
const int N = 2e5 + 5;
int n, q;
i64 a[N];
vector<pair<int,i64> > g[N];

int dep[N], father[N], siz[N], son[N], top[N], seg[N], rev[N];
i64 dis[N], f[N], f2[N];

void dfs1(int u, int fa){
    dep[u] = dep[fa] + 1, father[u] = fa, siz[u] = 1;
    f[u] = a[u], f2[u] = a[u] + (dis[u] << 1ll);
    for(auto [v, w] : g[u]){
        if(v == fa) continue;
        dis[v] = dis[u] + w;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
        f[u] = max(f[u], f[v] - (w << 1ll));
        f2[u] = max(f2[u], f2[v] - (w << 2ll));
    }
}

void dfs2(int u, int fa){
    if(son[u]){
        top[son[u]] = top[u], seg[son[u]] = ++seg[0], rev[seg[0]] = son[u];
        dfs2(son[u], u);
    }
    for(auto [v, w] : g[u]){
        if(v == fa || v == son[u]) continue;
        top[v] = v, seg[v] = ++seg[0], rev[seg[0]] = v;
        dfs2(v, u);
    }
}

struct ST{
    i64 t[N][25];

    void init(function<i64(int)> getter){
        for(int i=1;i<=n;i++) t[i][0] = getter(i);
        for(int j=1;j<=20;j++){
            for(int i=1;(i+(1 << j)-1)<=n;i++){
                t[i][j] = max(t[i][j - 1], t[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    i64 query(int l, int r){
        int s = __lg(r - l + 1);
        return max(t[l][s], t[r - (1 << s) + 1][s]);
    }
} t1, t2;

auto query1(int u, int v){
    i64 ans = LLONG_MIN;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        ans = max(ans, t1.query(seg[top[u]], seg[u]));
        u = father[top[u]];
    }
    if(dep[u] > dep[v]) swap(u, v);
    ans = max(ans, t1.query(seg[u], seg[v]));
    return make_pair(ans, u);
}

auto query2(int u){
    i64 ans = LLONG_MIN;
    while(u){
        ans = max(ans, t2.query(seg[top[u]], seg[u]));
        u = father[top[u]];
    }
    return ans;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<n;i++){
        int u, v, w; cin >> u >> v >> w;
        g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    }
    top[1] = seg[0] = seg[1] = rev[1] = 1;
    dfs1(1, 0), dfs2(1, 0);
    t1.init([](int x){ return f[rev[x]]; });
    t2.init([](int x){ return f2[rev[x]]; });
    while(q--){
        int x, y; cin >> x >> y;
        i64 ans = LLONG_MIN, ans1, ans2; int lca;
        tie(ans1, lca) = query1(x, y);
        ans2 = query2(lca);
        i64 dist = dis[x] + dis[y] - (dis[lca] << 1);
        ans = max(-dist + ans1 + a[x] + a[y], -dist + ans2 + a[x] + a[y] - (dis[lca] << 1));
        cout << ans << '\n';
    }
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：zzy0618 (赞：1)

换根 DP 和 LCA 板题。

可以求出从节点 $u$ 到子树内的结点演讲并回来的最大利润，并可以通过换根求出对于整棵数的答案，设其为 $g_u$。具体的，在第一次 DP 求出最优和次优，第二次 DP 换根时更新最优的子节点时用次优的就可以。

第二次演讲一定是从 $x$ 到 $y$ 的路径上的某一点离开去演讲再回来，也就是求 $x$ 到 $y$ 路径上 $g$ 的最大值，这可以用倍增预处理然后 $O(\log_2n)$ 回答。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,INF=1e17;
int n,q,a[N];
int f[N][20],dep[N];
int g[N][20],ci[N];
int h[N][20];
int head[N],tot;
struct edge{int v,w,nxt;}e[N<<1];
void add(int u,int v,int w){
    e[++tot]=(edge){v,w,head[u]},head[u]=tot;
}
void dfs1(int u){
    g[u][0]=a[u];ci[u]=-INF;
    for(int i=1;i<20;++i)
        f[u][i]=f[f[u][i-1]][i-1],
        h[u][i]=h[f[u][i-1]][i-1]+h[u][i-1];
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].v,w=e[i].w;
        if(v==f[u][0])continue;
        f[v][0]=u,h[v][0]=w,dep[v]=dep[u]+1;
        dfs1(v);int x=g[v][0]-w*2;
        if(x>=g[u][0])ci[u]=g[u][0],g[u][0]=x;
        else if(x>ci[u])ci[u]=x;
    }
}void dfs2(int u){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].v,w=e[i].w;
        if(v==f[u][0])continue;
        int x=0;
        if(g[u][0]!=g[v][0]-w*2)x=g[u][0]-w*2;
        else x=ci[u]-w*2;
        if(x>=g[v][0])ci[v]=g[v][0],g[v][0]=x;
        else if(x>ci[v])ci[v]=x;
        dfs2(v);
    }ci[u]=g[u][0];
    g[u][0]=max(g[u][0],g[f[u][0]][0]);
}int lca(int u,int v){
    int ans=max(ci[u],ci[v]),sum=a[u]+a[v];
    if(dep[u]<dep[v])swap(u,v);
    for(int i=19;i>=0;--i)
        if(dep[f[u][i]]>=dep[v])
            ans=max(ans,g[u][i]),
            sum-=h[u][i],u=f[u][i];
    if(u==v)return ans+sum;
    for(int i=19;i>=0;--i)
        if(f[u][i]!=f[v][i])
            ans=max(ans,max(g[u][i],g[v][i])),
            sum-=h[u][i],sum-=h[v][i],
            u=f[u][i],v=f[v][i];
    sum-=h[u][0];sum-=h[v][0];
    ans=max(ans,max(g[u][0],g[v][0]));
    return ans+sum;
}signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    for(int i=1,u,v,w;i<n;++i)
        cin>>u>>v>>w,add(u,v,w),add(v,u,w);
    for(int i=0;i<N;++i)
        for(int j=0;j<20;++j)
            g[i][j]=-INF;
    dep[1]=1;dfs1(1),dfs2(1);
    for(int j=1;j<20;++j)
        for(int i=1;i<=n;++i)
            g[i][j]=max(g[i][j-1],g[f[i][j-1]][j-1]);
    int u,v;
    while(q--)cin>>u>>v,cout<<lca(u,v)<<'\n';
    
    return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

应该是做麻烦了？

设 $u \rightsquigarrow v$ 表示从 $u$ 到 $v$ 的路径。设 $\operatorname{dist}(u, v)$ 表示 $u \rightsquigarrow v$ 的路径长度。设 $d_u$ 表示 $u$ 到根节点路径上的边权和。

题目要求的东西是 $c_x + c_y + c_z - \operatorname{dist}(x, z) - \operatorname{dist}(y, z)$ 的最大值。当然我们可以先去掉 $c_x, c_y$，最大化剩余的部分。

设 $l = \operatorname{lca}(x, y)$。我们考虑一下 $x \rightsquigarrow z$ 和 $y \rightsquigarrow z$ 的并在树上是长什么样子。

首先我们可以发现，$x \rightsquigarrow y$ 这条路径一定被上面两条路径的并覆盖了恰好一遍。我们只需要关注在 $x \rightsquigarrow y$ 路径之外的部分的长度 $L$ 就可以了。**$x \rightsquigarrow y$ 之外的这条路径会被覆盖两遍。**

题目转化为：最大化 $c_z - 2L$。

不妨设 $u$ 在 $x \rightsquigarrow y$ 上的一个点且 $z$ 在 $u$ 的非 $x, y$ 方向子树上。对于 $u$ 的子树中的点 $z$，其在 $x \rightsquigarrow y$ 外的部分恰好是 $z \rightsquigarrow u$。也就是说这时 $L$ 长度为 $d_z - d_u$。题目转化为：最大化 $c_z - 2d_z + 2d_u$。

不妨设 $f(u) = \max_{z \in \mathrm{subtree(u)}} c_z - 2d_z$，则 $c_z - 2L$ 也就变成 $f(u) + 2d_u$。$f$ 是容易求的。求出 $f$ 后，$l$ 子树内的部分可以用路径最值得方法解决，可以写树剖或者倍增等等。

接下来考虑 $l$ 子树外的部分。显然这时候 $L = \operatorname{dist}(l, z)$。不妨假设 $\operatorname{lca}(l, z) = q$，则需要最大化：$c_z - 2(d_l + d_z - 2d_q) = c_z - 2d_z + 2d_q - 2d_l$。这个 $c_z - 2d_z + 2d_q$ 看起来有点熟悉，其实我们刚才已经求过这个东西了，它就是 $f(q)$。$d_l$ 是定值，$d_q$ 只与 $q$ 有关。与上面类似地，我们设 $g(u) = f(u) + 2d_u$。问题转化为求从 $l$ 至根路径上 $g$ 的最大值。

整个问题至此分析完成，实现瓶颈即为求路径最值。若使用倍增求路径最值则复杂度为 $O(q \log n)$。

```cpp
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )

const int INF = 1e15;
int fa[N][19], st[N][19], dep[N], d[N];
int f[N], g[N], c[N], n, q;
vector<array<int, 2>> E[N];
void dfs(int u, int F) {
	fa[u][0] = F, dep[u] = dep[F] + 1;
	for (auto o : E[u]) if (o[0] ^ F) {
		int v = o[0], w = o[1];
		d[v] = d[u] + w; dfs(v, u);
	}
}
void dfs2(int u) {
	f[u] = c[u] - 2 * d[u];
	for (auto o : E[u]) if (o[0] ^ fa[u][0]) {
		int v = o[0]; dfs2(v); f[u] = max(f[u], f[v]);
	}
}
void dfs3(int u) {
	for (auto o : E[u]) if (o[0] ^ fa[u][0]) {
		int v = o[0]; g[v] = max(g[v], g[u]); dfs3(v);
	}
}
int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	dep(i, 18, 0) if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	dep(i, 18, 0) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return u == v ? u : fa[u][0];
}
int qmax(int u, int v) {
	int ans = -INF; if (dep[u] < dep[v]) swap(u, v);
	dep(i, 18, 0) if (dep[fa[u][i]] >= dep[v]) 
		ans = max(ans, st[u][i]), u = fa[u][i];
	dep(i, 18, 0) if (fa[u][i] != fa[v][i])
		ans = max(ans, st[u][i]),
		ans = max(ans, st[v][i]),
		u = fa[u][i], v = fa[v][i]; 
	if (u == v) ans = max(ans, st[u][0]);
	else ans = max(ans, st[u][1]), ans = max(ans, st[v][1]);
	return ans;
}
void sub() {
	read(n, q);
	rep(i, 1, n) read(c[i]); 
	rop(i, 1, n) {
		int u, v, w; read(u, v, w);
		E[u].pb({v, w}), E[v].pb({u, w});
	} dfs(1, 0); dfs2(1);
	rep(i, 1, n) f[i] = f[i] + 2 * d[i];
	rep(i, 1, n) st[i][0] = f[i];
	rep(j, 1, 18) rep(i, 1, n) fa[i][j] = fa[fa[i][j - 1]][j - 1];
	rep(j, 1, 18) rep(i, 1, n) st[i][j] = max(st[i][j - 1], st[fa[i][j - 1]][j - 1]);
	rep(i, 1, n) g[i] = f[i] + 2 * d[i]; dfs3(1);
	while (q -- ) {
		int x, z; read(x, z); int ans = -INF;
		int l = lca(x, z); ans = max(ans, qmax(x, z));
		ans = max(ans, g[l] - 2 * d[l]);
		printf("%lld\n", ans + c[x] + c[z] - d[x] - d[z] + 2 * d[l]);
	} return;
}
```

---

## 作者：bsjsaikou10 (赞：0)

# P11324 Speaker

## 题目描述：略。

## 解题思路：

我们考虑每一次它给定的 $x,y$ 发现我们不管第二场演唱会选在哪个结点，路径 $x \to lca(x,y) \to y$ 一定会被完整经过，而且不管我们选在哪个结点开演唱会，它的路径一定是从 $x,y$ 的最短路径中的某一个结点出发然后到开演唱会的这个结点，所以我们只需要考虑对于每个结点，从这个结点出发去一个结点开演唱会能获得的最大收益是多少，然后取简单路径中收益的最大值即可。

发现这显然可以 dp，我们设 $f_u$ 表示从 $u$ 出发能获得的最大收益是多少，我们现在设这颗树的根为 $1$，那么转移就是 $f_u= \max (f_u,f_v-2 \times w)$，其中 $w$ 为 $(u,v)$ 的边权，注意这里要乘上一个 $2$，因为我们在 $(x,y)$ 的最短路径之外走的路径一定被经过了两遍。

然后我们就能得出以 $1$ 为根时每个结点的答案，但是我们现在要求的是每个结点对于整颗树的答案，我们现在的 $f_u$ 仅仅只是对于 $u$ 的子树的答案，我们还需要考虑子树外的情况，发现 $1$ 的子树就是整颗树，所以 $f_1$ 就是 $1$ 的答案，所以我们考虑换根 dp，发现转移就是 $f_v= \max (f_v,f_u-2 \times w)$。

我们现在已经处理出每个点的 $f$ 值，所以我们只需要找 $(x,y)$ 的简单路径中 $f$ 最大的那个点即可，这里可以直接倍增，而我是弱小倍增，所以我选择树剖。

## Code

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define int long long
using namespace std;
const int MAXN = 3e5 + 3;
int n,q;
int c[MAXN],f[MAXN];
vector<pair<int,int> > edge[MAXN],edge2[MAXN];
int fa[MAXN],dep[MAXN],sz[MAXN],son[MAXN];
int top[MAXN],dis[MAXN],dfn[MAXN],rdfn[MAXN];
typedef struct TR{
	int l,r,mx;
}TR;
TR tr[MAXN << 2];
int ls(int pos){
	return pos << 1;
}
int rs(int pos){
	return pos << 1 | 1;
}
void dfs(int u,int fat){
	f[u] = c[u];
	dep[u] = dep[fat] + 1;
	fa[u] = fat;
	sz[u] = 1;
	for(int i = 0; i < edge[u].size(); i++){
		int v = edge[u][i].first;
		int w = edge[u][i].second;
		if(v == fat){
			continue;
		}
		dis[v] = dis[u] + w;
		dfs(v,u);
		sz[u] += sz[v];
		f[u] = max(f[u],f[v] - 2 * w);
		if(!son[u] || sz[v] > sz[son[u]]){
			son[u] = v;
		}
	}
}
int tim = 0;
void dfs2(int u,int fat,int tp){
	top[u] = tp;
	dfn[u] = ++tim;
	rdfn[tim] = u;
	if(son[u]){
		dfs2(son[u],u,tp);
	}
	for(int i = 0; i < edge[u].size(); i++){
		int v = edge[u][i].first;
		if(v == fat || v == son[u]){
			continue;
		}
		dfs2(v,u,v);
	}
}
void push_up(int pos){
	tr[pos].mx = max(tr[ls(pos)].mx,tr[rs(pos)].mx);
}
void build(int pos,int l,int r){
	tr[pos].l = l,tr[pos].r = r;
	tr[pos].mx = -1e18;
	if(l == r){
		tr[pos].mx = f[rdfn[l]];
		//cout << f[rdfn[l]] << endl;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls(pos),l,mid);
	build(rs(pos),mid + 1,r);
	push_up(pos);
}
int query(int pos,int L,int R){
	int l = tr[pos].l,r = tr[pos].r;
	if(l >= L && r <= R){
		return tr[pos].mx;
	}
	int mid = (l + r) >> 1;
	int res = -1e18;
	if(L <= mid){
		res = max(res,query(ls(pos),L,R));
	}
	if(R > mid){
		res = max(res,query(rs(pos),L,R));
	}
	return res;
}
int lca(int u,int v){
	while(top[u] != top[v]){
		if(dep[top[u]] > dep[top[v]]){
			u = fa[top[u]];
		}
		else{
			v = fa[top[v]];
		}
	}
	return dep[u] < dep[v] ? u : v;
}
int query_mx(int u,int v){
	int res = -1e18;
	while(top[u] != top[v]){
		if(dep[top[u]] > dep[top[v]]){
			res = max(res,query(1,dfn[top[u]],dfn[u]));
			//cout << "AA: " << query(1,dfn[top[u]],dfn[u]) << endl;
			u = fa[top[u]];
		}
		else{
			res = max(res,query(1,dfn[top[v]],dfn[v]));
			//cout << "AA: " << query(1,dfn[top[u]],dfn[u]) << endl;
			v = fa[top[v]];
		}
	}
	if(dfn[u] < dfn[v]){
		res = max(res,query(1,dfn[u],dfn[v]));
	}
	else{
		res = max(res,query(1,dfn[v],dfn[u]));
	}
	return res;
}
void calc_dp(int u,int fat){
	for(int i = 0; i < edge[u].size(); i++){
		int v = edge[u][i].first;
		int w = edge[u][i].second;
		if(v == fat){
			continue;
		}
		f[v] = max(f[v],f[u] - w * 2);
		calc_dp(v,u);
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> c[i];
	}
	for(int i = 1; i < n; i++){
		int u,v,w;
		cin >> u >> v >> w;
		edge[u].push_back(make_pair(v,w));
		edge[v].push_back(make_pair(u,w));
		//opt.push_back({u,v});
	}
	dfs(1,0);
	dfs2(1,0,1);
	calc_dp(1,0);
	/*for(int i = 1; i <= n; i++){
		f[1] = max(f[1],c[i] - dis[i]);
	}*/
	build(1,1,n);
/*	for(int i = 1; i <= n; i++){
		cout << f[i] << " ";
	}
	return 0;*/
	while(q--){
		int x,y;
		cin >> x >> y;
		int ans = c[x] + c[y];
		int lc = lca(x,y);
		ans = ans - (dis[x] + dis[y] - 2 * dis[lc]);
		int maxx = query_mx(x,y);
		ans += maxx;
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：ty_xyz (赞：0)

观察到无论 $z$ 点在何处，都会在 $x$ 和 $y$ 两点演讲，以及经过一遍 $x-y$ 路径，那么我们要求的就是一个点 $z$ 使得 $c_z$ 减去两倍的到 $x-y$ 路径的距离最大。

进一步，我们发现，$x-y$ 路径上一定会有一个点 $w$，使得 $x-z$ 与 $z-y$ 路径被分割成 $x-w-z$ 与 $z-w-y$ 路径。那么考虑对每一个点都求出其作为 $w$ 点时的最优 $z$ 点的贡献，询问时通过某种方式统计。考虑换根 DP，设节点 $u$ 的贡献为 $dp_u$，感性理解一下，转移就是子结点的最大值再减掉这一条边的两倍，当然要跟在自身演讲的贡献取 $\max$，然后再取一下父结点的贡献即可。最终的答案即为 $c_x+c_y-\text{dis}(x,y)+\max(dp_w)$。路径上记录最大值有很多种方法，用树剖是一种方法，不过比较难写。

个人感觉 T1 要比这题难啊。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define get(x,y) dfn[x]<dfn[y]?x:y
struct edge{int id,d;}son[200001];
vector<edge>g[200001];
int n,q,c[200001],ff[200001],f[19][200001],top[200001],siz[200001],dfn[200001],d[200001],cnt,x,y;
long long dis[200001],t[800001],dp[200001];
void dfs1(int u,int fa)
{
    d[u]=d[ff[u]=fa]+1;
    dp[u]=c[u];
    siz[u]=1;
    for(auto&[v,w]:g[u])
    {
        if(v==fa)continue;
        dis[v]=dis[u]+w;
        dfs1(v,u);
        siz[u]+=siz[v];
        dp[u]=max(dp[u],dp[v]-(w<<1));
        if(siz[v]>siz[son[u].id])son[u]={v,w};
    }
}
void update(int p,int cl,int cr,int x,long long y)
{
    if(cl==cr)
    {
        t[p]=y;
        return;
    }
    int mid=cl+cr>>1;
    mid>=x?update(p<<1,cl,mid,x,y):update(p<<1|1,mid+1,cr,x,y);
    t[p]=max(t[p<<1],t[p<<1|1]);
}
void dfs2(int u,int fa)
{
    top[u]=fa;
    f[0][dfn[u]=++cnt]=ff[u];
    update(1,1,n,dfn[u],dp[u]);//线段树记录路径上 dp[w] 最大值
    if(son[u].id)
    {
        dp[son[u].id]=max(dp[son[u].id],dp[u]-(son[u].d<<1));//换根
        dfs2(son[u].id,fa);
    }
    for(auto&[v,w]:g[u])
    {
        if(v==ff[u]||v==son[u].id)continue;
        dp[v]=max(dp[v],dp[u]-(w<<1));//换根
        dfs2(v,v);
    }
}
long long query(int p,int cl,int cr,int x,int y)
{
    if(x<=cl&&cr<=y)return t[p];
    int mid=cl+cr>>1;
    return max(mid>=x?query(p<<1,cl,mid,x,y):0,mid<y?query(p<<1|1,mid+1,cr,x,y):0);
}
long long qph(int x,int y)
{
    long long res=0;
    while(top[x]!=top[y])//树剖板子
    {
        if(d[top[x]]<d[top[y]])swap(x,y);
        res=max(res,query(1,1,n,dfn[top[x]],dfn[x]));
        x=ff[top[x]];
    }
    if(d[x]>d[y])swap(x,y);
    return max(res,query(1,1,n,dfn[x],dfn[y]));
}
int lca(int x,int y)
{
    if(x==y)return x;
    if((x=dfn[x])>(y=dfn[y]))swap(x,y);
    int k=__lg(y-x++);
    return get(f[k][x],f[k][y-(1<<k)+1]);
}
signed main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)scanf("%d",&c[i]);
    for(int i=1,x,y,z;i<n;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        g[x].push_back(edge{y,z});
        g[y].push_back(edge{x,z});
    }
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=__lg(n);i++)for(int j=1;j+(1<<i)-1<=n;j++)f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
    while(q--)
    {
        scanf("%d%d",&x,&y);
        printf("%lld\n",qph(x,y)+c[x]+c[y]-dis[x]-dis[y]+(dis[lca(x,y)]<<1));
    }
    return 0;
}
```

---

## 作者：AzusidNya (赞：0)

很套路。支持绿。有点无聊了（

首先 $u \rightarrow k, v \rightarrow k$ 这两条路径边权和可以转化为 $u \rightarrow v$ 的边权和加上 $p \rightarrow k$ 的边权和的两倍，其中 $p$ 是 $u \rightarrow v$ 路径上的一点。设 $val(u \rightarrow v)$ 为 $u$ 到 $v$ 的路径的边权和，$path(u \rightarrow v)$ 表示 $u$ 到 $v$ 路径上的点的点集。原题要最大化的是 $c_u + c_v - val(u \rightarrow v) - 2val(p \rightarrow k) + c_k, p \in path(u \rightarrow v)$。当询问固定了 $u$ 和 $v$ 时，前面三项是确定的，所以实际上只用最大化 $c_k - 2val(p \rightarrow k)$。

设 $g(p) = \max (c_k - 2val(p \rightarrow k))$。则查询时只用查询 $u \rightarrow v$ 路径上的最大 $g(p)$。这个可以通过树上倍增在求出 $\operatorname{lca}$ 时顺带求出。

现在考虑求出 $g(p)$。这是个经典的换根 dp 问题。考虑先固定 $1$ 为根，设 $f(p)$ 为只考虑 $p$ 子树内的 $k$ 时 $c_k - 2val(p \rightarrow k)$ 的最大值。设 $son(p)$ 为 $p$ 儿子节点点集，有状态转移方程：
$$
f(p) = \max_{v \in son(p)}\left( f(v) - 2val(p \rightarrow v), c_p\right)
$$
然后换根。先令 $g(1) = f(1)$。因为这题取 $\max$ 且路径如果有重复肯定更劣，所以不用管子树的位置的问题。设 $fa_p$ 为 $p$ 的父亲节点，然后有状态转移方程：
$$
g(p) = \max \left( f(p), g(fa_p) - 2val(p \rightarrow fa_p)\right)
$$
然后就求出了所有 $g(p)$，接下来只需要实现树上倍增 $\operatorname{lca}$ 顺带求路径最大值即可，具体地，预处理出 $h(p, i)$ 表示从 $p$ 节点开始到其向上 $2^i$ 级祖先的点集的 $g$ 最大值，然后求 $\operatorname{lca}$ 时顺带对 $h$ 取 $\max$ 即可。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define eb emplace_back
#define mp make_pair
// #define DEBUG
using namespace std;
using pii = pair<int, int>;
using piii = pair<int, pii>;
using piiii = pair<pii, pii>;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned int;
const int P = 998244353;const i64 inf = 0x3f3f3f3f3f3f3f3f;
namespace azus{
	int n, q;
	int f[200005], g[200005];
	int c[200005];
	vector<pii> edge[200005];
	int h[200005][21], dep[200005], ft[200005][21];
	int dis[200005];
	int dfs(int u, int fa){
		ft[u][0] = fa;
		dep[u] = dep[fa] + 1;
		f[u] = c[u];
		for(auto [v, w] : edge[u]){
			if(v == fa) continue;
			dis[v] = dis[u] + w;
			dfs(v, u);
			f[u] = max(f[u], f[v] - w - w);
		}
		return 0;
	}
	int dfs2(int u, int fa){
		for(auto [v, w] : edge[u]){
			if(v == fa) continue;
			g[v] = max(f[v], g[u] - w - w);
			dfs2(v, u);
		}
		return 0;
	}
	pii solve(int u, int v){
		if(u == v){
			return mp(g[u], u);
		}
		if(dep[u] < dep[v]) swap(u, v);
		int mx = -inf;
		for(int i = 20; i >= 0; i --){
			if(dep[ft[u][i]] >= dep[v])
				mx = max(mx, h[u][i]), u = ft[u][i];
		}
		if(u == v) return mp(max(mx, g[u]), u);
		for(int i = 20; i >= 0; i --){
			if(ft[u][i] == ft[v][i]) continue;
			mx = max(mx, h[u][i]); mx = max(mx, h[v][i]);
			u = ft[u][i], v = ft[v][i];
		}
		mx = max(mx, g[u]), mx = max(mx, g[v]);
		u = ft[u][0];
		mx = max(mx, g[u]);
		return mp(mx, u);
	}
	int main(){
		memset(f, 0xcf, sizeof(f)); memset(g, 0xcf, sizeof(g));
		cin >> n >> q;
		for(int i = 1; i <= n; i ++){
			cin >> c[i];
		} for(int i = 1, u, v, w; i < n; i ++){
			cin >> u >> v >> w; edge[u].eb(mp(v, w)), edge[v].eb(mp(u, w));
		}
		dfs(1, 0);
		g[1] = f[1];dfs2(1, 0);
		for(int i = 1; i <= n; i ++) h[i][0] = g[i];
		for(int i = 1; i <= 20; i ++){
			for(int j = 1; j <= n; j ++){
				ft[j][i] = ft[ft[j][i - 1]][i - 1];
				h[j][i] = max(h[j][i - 1], h[ft[j][i - 1]][i - 1]);
			}
		}
		while(q --){
			int x, y;
			cin >> x >> y;
			auto [mx, lca] = solve(x, y);
			cout << mx - (dis[x] + dis[y] - dis[lca] - dis[lca]) + c[x] + c[y] << "\n";
		}
		return 0;
	}
}
signed main(){
#ifndef DEBUG
	// freopen("speaker3.in", "r", stdin);
	// freopen("speaker3.wixx", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
#endif
	int T = 1;
	while(T --)
		azus::main();
	return 0;
}
```

fun fact：写完后很快过完了所有大样例，然后太困直接睡着了没交上。

---

## 作者：XiaoJuRuoUP (赞：0)

[~~不会更好的阅读体验~~](https://www.cnblogs.com/XiaoJuRuoUP/p/-/luoguP11324)
## 题意
[原题链接](https://www.luogu.com.cn/problem/P11324)

给定一个带权无根树，第 $i$ 个节点上有一个数 $c_i$，每次询问给定两个点 $x,y$，在无根树上任选一点 $z$，使 $c_x+c_y+c_z-dist(x,z)-dist(z,y)$ 最大，输出最大的值。
## sol
考虑 $z$ 可能有两种情况，要么是 $x\to y$ 的路径上的一点 $t$，要么从路径上的一点 $t$ 向外拐出来。无论怎样，最终结果都是 $c_x+c_y-dist(x,y)+\max_{i \text{与} t \text{连通}}\{c_t-2\cdot dist(t, i)\}$，我们可以通过换根 DP 来计算最后一项，因此问题就转化为了树上路径求最大值问题，使用树剖 + RMQ 即可。

注意可能会爆 int。
## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long LL;

const int N = 200005, M = N * 2;

int h[N], e[M], w[M], ne[M], idx;
int n, q;
int c[N];
int fid[N], gid[N];
LL f[N], sf[N], g[N], sg[N];
LL sum[N];
int fa[N], dfn[N], rk[N], top[N], hson[N], sz[N], dep[N], timestamp;
int Log2[N];
LL st[N][20];

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void dp1(int u, int father){
    f[u] = c[u], fid[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        if (j == father) continue;
        dp1(j, u);
        if (f[j] - 2 * w[i] >= f[u]) fid[u] = j, sf[u] = f[u], f[u] = f[j] - 2 * w[i];
        else if (f[j] - 2 >= sf[u]) sf[u] = f[j] - 2 * w[i];
    }
}

void dp2(int u, int father, int val){
    if (u == 1) g[u] = f[u], sg[u] = sf[u], gid[u] = fid[u];
    else {
        int fans;
        if (gid[father] == u) fans = max(sf[father], g[father]);
        else fans = max(f[father], g[father]);

        g[u] = f[u], sg[u] = sf[u], gid[u] = fid[u];

        if (fans - 2 * val >= g[u]) gid[u] = father, sg[u] = g[u], g[u] = fans - 2 * val;
        else if (fans - 2 * val >= sg[u]) sg[u] = fans - 2 * val;
    }

    for (int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        if (j == father) continue;
        dp2(j, u, w[i]);
    }
}

void init(int u, int father){
    fa[u] = father, dep[u] = dep[father] + 1, sz[u] = 1, hson[u] = 0;
    for (int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        if (j == father) continue;
        sum[j] = sum[u] + w[i];
        init(j, u);
        sz[u] += sz[j];
        if (sz[j] > sz[hson[u]]) hson[u] = j;
    }
}

void init2(int u, int father, int tp){
    dfn[u] = ++ timestamp, rk[timestamp] = u, top[u] = tp;
    if (!hson[u]) return ;
    init2(hson[u], u, tp);
    for (int i = h[u]; ~i; i = ne[i]){
        int j = e[i];
        if (j == father || j == hson[u]) continue;
        init2(j, u, j);
    }
}

void rmq_init(){
    Log2[0] = Log2[1] = 0;
    for (int i = 2; i <= n; i ++ ) Log2[i] = Log2[i / 2] + 1;
    
    for (int i = 1; i <= n; i ++ ) st[i][0] = g[rk[i]];
    for (int k = 1; k <= 17; k ++ ) 
        for (int i = 1; i + (1 << k) - 1 <= n; i ++ )
            st[i][k] = max(st[i][k - 1], st[i + (1 << k - 1)][k - 1]);
}

LL rmq_query(int l, int r){
    int lg = Log2[r - l + 1];
    return max(st[l][lg], st[r - (1 << lg) + 1][lg]);
}

int lca(int x, int y){
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
}

LL path_sum(int x, int y){
    int l = lca(x, y);
    return sum[x] - sum[l] + sum[y] - sum[l];
}

LL path_max(int x, int y){
    LL res = -1;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        res = max(res, rmq_query(dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    res = max(res, rmq_query(dfn[x], dfn[y]));
    return res;
}

void INIT(){
    dp1(1, 0);
    dp2(1, 0, 0);

    init(1, 0);
    init2(1, 0, 1);
    rmq_init();
}

int main(){
    memset(h, -1, sizeof h);

    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &c[i]);

    for (int i = 1; i < n; i ++ ) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    INIT();

    while (q -- ){
        int x, y;
        scanf("%d%d", &x, &y);
        LL ans = path_max(x, y) - path_sum(x, y) + c[x] + c[y];
        printf("%lld\n", ans);
    }

    return 0;
}
```

---

## 作者：Justin0779 (赞：0)

说在前面：初看题的时候人傻了，以为需要 **树分治+换根** 来做。

# Solution

理解完题意后，很容易得出对于每次询问，所求即为：
$$
c_s+c_t-dis_{s, t} + ct
$$
这里 $dis_{s, t}$ 表示 $s$ 和 $t$ 之间的路径，而 $ct$ 就是第二座城市的最大贡献，也就是某个点 $i$ 的权值 $c_i$ 减去其到路径 $s\to t$ 上某一点 $j$ 的距离的两倍的最大值，也就是有：
$$
ct=\max_{i \in V, j \in s \to t} c_i-2\times dis_{i, j}
$$

这里 V 为点集。

那么 $dis_{s, t}$ 可以用 **倍增LCA** 预处理后 $O(\log n)$ 求得，所以只需考虑如何求出 $ct$，也就是对于每一个点，在允许的时间内求出 $ct_i$。这样，我们便能很好的得出答案了。

考虑第二座城市点 $i$ 的构成并同时考虑它所连到路径上最近的点，那么这个最大值是不会变化的，同时它只有三种可能：

1. 在 $j$ 的子树内。
2. 在 $j$ 的祖先中。
3. 在 $j$ 的祖先的子树中。

并且，这里的 2，3 可以同时处理，然后这样的形式很像 **树形DP**，考虑通过 dfs 的过程进行转移。

不难发现，转移时，对每个 $ct_i$ 有：

$$
ct_i=\max_{j\in son_i}(ct_{fa_i}-2\times w_{i, fa_i}，ct_j - 2 \times w_{i, j}，c_i)
$$

这样正反跑两遍 dfs 我们就可以求出每个 $i$ 对应的 $ct_i$ 了。然后在倍增同时处理 $s\to t$ 路径上的 $ct_i$ 的最大值即可。

最后用求 LCA 的过程求解即可，时间复杂度 $O(n\log n)$。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 2e5 + 5, LG = 19;

namespace FastIO {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
#define getchar() (p1 == p2 && (p1 = buf, p2 = (p1 + fread(buf, 1, 1 << 21, stdin))) == p1 ? EOF : *p1++)
	template <typename T> inline T read() { T x = 0, w = 0; char ch = getchar(); while (ch < '0' || ch > '9') w |= (ch == '-'), ch = getchar(); while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ '0'), ch = getchar(); return w ? -x : x; }
	template <typename T> inline void write(T x) { if (!x) return; write<T>(x / 10), putchar((x % 10) ^ '0'); }
	template <typename T> inline void print(T x) { if (x > 0) write<T>(x); else if (x < 0) putchar('-'), write<T>(-x); else putchar('0'); }
	template <typename T> inline void print(T x, char en) { print<T>(x), putchar(en); }
}; using namespace FastIO;
#undef getchar()


namespace Otakus
{
    int n;
    vector<int> qry[N];
    vector<pair<int, int>> g[N];
    ll mx[N], ans, can[N], val[N];

    int fa[20][N], dep[N];
    ll cost[20][N], cval[20][N];

    void dfs(int x) {
        for (int i = 1; i <= LG; i++) {
            fa[i][x] = fa[i - 1][fa[i - 1][x]];
            cost[i][x] = cost[i - 1][x] + cost[i - 1][fa[i - 1][x]];
            cval[i][x] = max(cval[i - 1][x], cval[i - 1][fa[i - 1][x]]);
        }

        for (auto tmp : g[x]) {
            int y = tmp.first, dis = tmp.second;
            if (!dep[y]) {
                dep[y] = dep[x] + 1;
                fa[0][y] = x;
                cost[0][y] = dis;
                cval[0][y] = mx[x];
                dfs(y);
            }
        }
    }

    int lca(int x, int y, int id) {
        if (dep[x] < dep[y])
            swap(x, y);
        for (int tmp = dep[x] - dep[y], j = 0; tmp; j++, tmp >>= 1)
            if (tmp & 1)
                ans -= cost[j][x], can[id] = max(can[id], cval[j][x]), x = fa[j][x];
        if (x == y)
            return y;

        for (int j = LG; j >= 0; j--) if (fa[j][x]!=fa[j][y]) {
                ans -= cost[j][x];
                ans -= cost[j][y];
                can[id] = max(can[id], cval[j][x]);
                can[id] = max(can[id], cval[j][y]);
                x = fa[j][x];
                y = fa[j][y];
            }
        ans -= cost[0][x];
        ans -= cost[0][y];
        can[id] = max(can[id], cval[0][x]);
        can[id] = max(can[id], cval[0][y]);
        return fa[0][x];
    }

    void prework(int x, int f) {
        mx[x] = val[x];
        for (auto tmp : g[x])
        {
            int y = tmp.first, dis = tmp.second;
            if (y != f)
            {
                prework(y, x);
                mx[x] = max(mx[x], mx[y] - 2 * dis);
            }
        }
    }

    void nxtwork(int x, int f) {
        for (auto tmp : g[x])
        {
            int y = tmp.first, dis = tmp.second;
            if (y != f)
            {
                mx[y] = max(mx[x] - 2 * dis, mx[y]);
                nxtwork(y, x);
            }
        }
    }

    void init() {
        int T;
        n = read<int>();
        T = read<int>();
        for (int i = 1; i <= n; i++)
            val[i] = read<int>();
        for (int i = 1; i < n; i++)
        {
            int u, v, w;
            u = read<int>();
            v = read<int>();
            w = read<int>();
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        prework(1, 0);
        nxtwork(1, 0);
        dep[1] = 1;
        dfs(1);
        
        for (int i = 1; i <= T; i++)
        {
            int s, t;
            s = read<int>();
            t = read<int>();
            ans = 0;
            qry[s].push_back(i);
            qry[t].push_back(i);
            int lc = lca(s, t, i);
            can[i] = max({can[i], val[lc], val[s], val[t]});
            ans += val[s] + val[t];
            can[i] = max({can[i], mx[s], mx[t], mx[lc]});
            ans += can[i];
            print(ans, '\n');
        }
    }
} // namespace Otakus

int main() {
    // freopen("main.in", "r", stdin);
    // freopen("main.out", "w", stdout);

    Otakus::init();
    return 0;
}
```

---

## 作者：SXqwq (赞：0)

### Description

有一个 $n$ 个点的树，点 $i$ 有点权 $c_i$。边有边权。$q$ 次询问，每次询问给定两个点 $u,v$。再选一个点 $k$。最大化 $c_u+c_v+c_k-\operatorname{dis}_{u,k}-\operatorname{dis}_{k,v}$。
    
$n,q\le 2\times 10^5$。
    
### Analysis


这种题一般考虑拆贡献。考虑我们实际要算什么。

$c_u+c_v$ 可以直接算。如果 $k$ 在 $u$ 到 $v$ 的路径上，$\operatorname{dis}_{u,k}+\operatorname{dis}_{k,v}=\operatorname{dis}_{u,v}$。这是定值。我们只需计算 $(u,v)$ 路径上点权最大值即可。可以树剖维护。

考虑 $k$ 在 $(u,v)$ 路径外情形。路径一定形如 $u\rightarrow p\rightarrow k\rightarrow p\rightarrow v$。即路径和等价于 $\operatorname{dis}_{u,v} +2\operatorname{dis}_{k,p}$，$p$ 在路径 $u,v$ 上。

因此，我们需要维护每个点 $p$ 的 $c_k-2\operatorname{dis}_{k,p}$ 最大值。这是经典问题，考虑二次扫描。首先从根节点开始遍历，更新每个点 $p$ 向下能延伸到的 $c_k-2\operatorname{dis}_{k,p}$ 最大值。第二次扫描，更新每个点 $p$ 向上能延伸到的最大值。最后对于每个点，向上和向下延伸的最大值取 $\max$ 即为答案。如下。

```cpp
struct INIT
{
    void dfs1(int u,int fat,int sum)
    {
        dis[u] = sum; // 前缀和处理，后续计算两点距离时使用
        f1[u] = c[u];
        for(auto [v,w]:Edge[u])
        {
            if(v == fat) continue;
            dfs1(v,u,sum + w);
            f1[u] = max(f1[u],f1[v] - 2*w); // 儿子更新父亲
        }
    }
    void dfs2(int u,int fat)
    {
        for(auto [v,w]:Edge[u])
        {
            if(v == fat) continue;
            f[v] = max({c[v],f1[u]-2*w,f[u]-2*w}); //父亲更新儿子
            dfs2(v,u);
        }
    }
}init;
```
然后就做完了。每次询问代入上述公式直接算即可。我使用了树剖维护。

代码很长，见 [剪切板](https://www.luogu.com.cn/paste/vmis5y32)。

---

## 作者：RAND_MAX (赞：0)

一道比较按部就班的题，但是个人感觉评绿真的低了。

下文中 $\operatorname{dis}(x,y)$ 表示从 $x$ 到 $y$ 上路径边权和，$\operatorname{S}(x,y)$ 表示由从 $x$ 到 $y$ 的路径上的点所组成的集合（包括 $x,y$）。

从题意可得最终答案形如 $c_x+c_y+c_z-\operatorname{dis}(x,z)-\operatorname{dis}(y,z)$。我们不妨分类讨论 $z$ 所在的位置。

若 $z\in\operatorname{S}(x,y)$，则上式可以简化为 $c_x+c_y+c_z-\operatorname{dis}(x,y)$。此时我们只需求 $\max\limits_{z\in\operatorname{S}(x,y)}c_z$ 即可。

若 $z\notin\operatorname{S}(x,y)$，我们不妨设 $z$ 到从 $x$ 到 $y$ 的路径上距离最小的点为 $p$，那么上式相当于 $c_x+c_y+c_z-\operatorname{dis}(x,p)-\operatorname{dis}(y,p)-2\times \operatorname{dis}(p,z)=c_x+c_y+c_z-\operatorname{dis}(x,y)-2\times \operatorname{dis}(p,z)$。

注意到第一种情况相当于 $p=z$。所以我们只需对于每一个$p\in\operatorname{S}(x,y)$ 处理 $\max\limits_{i=1}^n c_i-2\times \operatorname{dis}(i,p)$。我们记上式为 $f_p$，考虑换根 DP。

第一遍 dfs 先处理出 $g_i$ 表示在以 1 为根的情况下，点 $i$ 子树内最大的 $c_j-2\times \operatorname{dis}(i,j)$，容易得出转移 $g_i=\max\limits_{j\in son(i)}g_j-2
\times\operatorname{dis}(i,j)$，其中 $g_j$ 初值为 $c_j$。

第二遍 dfs 开始换根，由与第一次转移类似地，$fa_i$ 在向 $i$ 转移时也要减去 $2\times\operatorname{dis}(fa_i,i)$。一般的换根 DP 在换根时要扣除该子节点的贡献，但是此时无需扣除，因为若 $g_{fa_i}$ 由 $g_i$ 转移而来，由于边权非负，此时 $g_i$ 显然大于 $g_{fa_i}$。故我们可得 $f_i=\max(g_i,g_{fa_i}-2\times \operatorname{dis}(i,fa_i))$。

对于每个查询，答案即为 $c_x+c_y-\operatorname{dis}(x,y)-\max\limits_{i\in\operatorname{s}(x,y)}f_i$，$\operatorname{dis}(x,y)$ 可以树上前缀和后树剖求 lca 查询，$\max\limits_{i\in\operatorname{s}(x,y)}f_i$ 用树剖套 ST 表查询。具体实现细节不多，见代码。


```cpp
#include<bits/stdc++.h>
#define int long long
#define R read()
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x*f;
}
void write(int x,char xx)
{
	static int st[35],top=0;
	if(x<0){x=-x;putchar('-');}
	do
	{
		st[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(st[--top]+48);
	putchar(xx);
}
#define N 200010
#define pii pair<int,int>
#define inf 0x3f3f3f3f3f3f3f
#define fi first
#define se second
int n,q,f[N],dp[N],a[N],dis[N],ft[N],dd[N],ans;
int dep[N],top[N],siz[N],gs[N],dfn[N],id[N],tot;
vector<pii>g[N];
int mxf[N][20],lg[N];
void dfs(int x,int fa)
{
	f[x]=a[x],ft[x]=fa,dep[x]=dep[fa]+1,siz[x]=1,dd[x]=dd[fa]+dis[x];
	for(auto [i,j]:g[x])
	{
		if(i==fa) continue;
		dis[i]=j,dfs(i,x);
		siz[x]+=siz[i];
		if(siz[i]>siz[gs[x]]) gs[x]=i;
		f[x]=max(f[x],f[i]-2*j);
	}
}
void op(int x,int tp)
{
	dfn[x]=++tot,id[tot]=x,top[x]=tp;
	if(gs[x]) op(gs[x],tp);
	else return;
	for(auto[i,j]:g[x])
	{
		if(i==ft[x]||i==gs[x]) continue;
		op(i,i);
	}
}
void init(int n)
{
	for(int i=2;i<=n;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++) mxf[i][0]=dp[id[i]];
	for(int j=1;j<=lg[n];j++)
	{
		for(int i=1;i+(1<<j)-1<=n;i++)
		{
			mxf[i][j]=max(mxf[i][j-1],mxf[i+(1<<j-1)][j-1]);
		}
	}
}
int quemxf(int l,int r)
{
	int s=lg[r-l+1];
	return max(mxf[l][s],mxf[r-(1<<s)+1][s]);
}
int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=ft[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	return v;
}
int queptmxf(int u,int v)
{
	int su=-inf;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		su=max(su,quemxf(dfn[top[u]],dfn[u])),u=ft[top[u]];
	}
	if(dep[u]<dep[v]) swap(u,v);
	su=max(su,quemxf(dfn[v],dfn[u]));
	return su;
}
void dfs1(int x,int fa)
{
	dp[x]=f[x];
	for(auto[i,j]:g[x])
	{
		if(i==fa) continue;
		f[i]=max(f[i],f[x]-2*j),dfs1(i,x);
	}
}
signed main()
{
	n=R,q=R;
	for(int i=1;i<=n;i++) a[i]=R;
	for(int i=1,x,y,z;i<n;i++) x=R,y=R,z=R,g[x].push_back(pii{y,z}),g[y].push_back(pii{x,z});
	dfs(1,0),dfs1(1,0),op(1,1),init(n);
	int x,y,ll,su;
	while(q--)
	{
		x=R,y=R,ll=lca(x,y),su=dd[x]+dd[y]-2*dd[ll];
		write(queptmxf(x,y)+a[x]+a[y]-su,'\n');
	}
 	return 0;
}
```

---

## 作者：Ratio_Y (赞：0)

## 思路

容易想到无论起终点如何每个点最优的中转方案是确定的，因此可以设 $f_i$ 为点 $i$ 的最优方案的贡献，比较好想 $f_i=a_x+d(i,x)$，考虑简单换根 dp 解决。假设存在一父子关系点对 $x,y$，设存在一点 $z\in subtree_y$，容易发现若 $z$ 不是 $y$ 的最优中转点，则其一定不是 $x$ 的最优中转点。也就是说，每个点的最优中转点的候选只有相邻点的最优中转点或自身。那么先以 $1$ 为根正常 dp 跑出 $f_1$ 的值，然后再倒着转移一遍，即用父亲更新儿子，就可以在 $\mathcal{O(n)}$ 的时间内求出每个点的 $f$ 值。

此时答案已经被拆分成了 $a_{x_i}+a_{y_i}-d(x_i,y_i)+\max_{u\in x_i\rightarrow y_i} f_i$，其中 $x_i\rightarrow y_i$ 表示 $x_i$ 到 $y_i$ 的路径。发现前三项都是固定的，最后一项只需要找到树上路径最大值即可，考虑树剖维护即可。

然后就做完了，时间复杂度 $\mathcal{O(n\log^2 n)}$。

注意一个易错小细节，树剖求 lca 和统计答案时用的 $deep$ 数组不要和树上差分的 $dis$ 数组搞混！~~猜猜谁因为这个挂了 12pts。~~

## 实现

```cpp
#include<bits/stdc++.h>
#define fo(x, y, z) for(int (x) = (y); (x) <= (z); (x)++)
#define fu(x, y, z) for(int (x) = (y); (x) >= (z); (x)--)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define lx ll
inline lx qr()
{
    char ch = getchar(); lx x = 0, f = 1;
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
    return x * f;
}
#undef lx
#define qr qr()
#define pll pair<ll, ll>
#define pii pair<int, int>
#define ppp pair<pii, pii>
#define fi first
#define se second
#define M_P(x, y) make_pair(x, y)
#define P_B(x) push_back(x)
const int Ratio = 0;
const int N = 2e5 + 5;
const int mod = 998244353;
int n, m;
int a[N];
int dfn[N], dt, fx[N], top[N], son[N], siz[N], dep[N];
int hh[N], to[N << 1], ne[N << 1], cnt;
ll w[N << 1], dis[N], wt[N], f[N], v[N << 2];
namespace Wisadel
{
    inline void Wadd(int u, int v, ll val)
    {
        to[++cnt] = v;
        w[cnt] = val;
        ne[cnt] = hh[u];
        hh[u] = cnt;
    }
    inline void Wdfs(int u, int fa)
    {
        fx[u] = fa, siz[u] = 1, dep[u] = dep[fa] + 1;
        for(int i = hh[u]; i != -1; i = ne[i])
        {
            int v = to[i];
            if(v == fa) continue;
            dis[v] = dis[u] + w[i];
            Wdfs(v, u);
            siz[u] += siz[v];
            if(siz[v] > siz[son[u]]) son[u] = v;
        }
    }
    inline void Wdfs2(int u, int tpf)
    {
        dfn[u] = ++dt, wt[dt] = f[u], top[u] = tpf;
        if(son[u]) Wdfs2(son[u], tpf);
        for(int i = hh[u]; i != -1; i = ne[i])
        {
            int v = to[i];
            if(v == fx[u] || v == son[u]) continue;
            Wdfs2(v, v);
        }
    }
    inline void Wdfs3(int u, int fa)
    {
        f[u] = a[u];
        for(int i = hh[u]; i != -1; i = ne[i])
        {
            int v = to[i];
            if(v == fa) continue;
            Wdfs3(v, u);
            f[u] = max(f[u], f[v] - 2 * w[i]);
        }
    }
    inline void Wdfs4(int u, int fa)
    {
        for(int i = hh[u]; i != -1; i = ne[i])
        {
            int v = to[i];
            if(v == fa) continue;
            f[v] = max(f[v], f[u] - 2 * w[i]);
            Wdfs4(v, u);
        }
    }
    #define ls (rt << 1)
    #define rs (rt << 1 | 1)
    #define mid ((l + r) >> 1)
    inline void Wpushup(int rt){v[rt] = max(v[ls], v[rs]);}
    inline void Wbuild(int rt, int l, int r)
    {
        if(l == r)
        {
            v[rt] = wt[l];
            return ;
        }
        Wbuild(ls, l, mid), Wbuild(rs, mid + 1, r);
        Wpushup(rt);
    }
    inline ll Wq(int rt, int l, int r, int x, int y)
    {
        if(x <= l && r <= y) return v[rt];
        ll res = -2e18;
        if(x <= mid) res = max(res, Wq(ls, l, mid, x, y));
        if(y > mid) res = max(res, Wq(rs, mid + 1, r, x, y));
        return res;
    }
    #undef ls
    #undef rs
    #undef mid
    inline int Wlca(int x, int y)
    {
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]]) swap(x, y);
            x = fx[top[x]];
        }
        if(dep[x] > dep[y]) swap(x, y);
        return x;
    }
    inline ll Wque(int x, int y)
    {
        ll res = -2e18;
        while(top[x] != top[y])
        {
            if(dep[top[x]] < dep[top[y]]) swap(x, y);
            res = max(res, Wq(1, 1, n, dfn[top[x]], dfn[x]));
            x = fx[top[x]];
        }
        if(dep[x] > dep[y]) swap(x, y);
        res = max(res, Wq(1, 1, n, dfn[x], dfn[y]));
        return res;
    }
    inline ll Wd(int u, int v){return dis[u] + dis[v] - 2 * dis[Wlca(u, v)];}
    short main()
    {
        n = qr, m = qr;
        memset(hh, -1, sizeof hh);
        fo(i, 1, n) a[i] = qr;
        fo(i, 1, n - 1)
        {
            int a = qr, b = qr; ll c = qr;
            Wadd(a, b, c), Wadd(b, a, c);
        }
        Wdfs(1, 0), Wdfs3(1, 0), Wdfs4(1, 0), Wdfs2(1, 1);
        Wbuild(1, 1, n);
        fo(i, 1, m)
        {
            int x = qr, y = qr;
            ll ans = a[x] + a[y] - Wd(x, y) + Wque(x, y);
            printf("%lld\n", ans);
        }
        return Ratio;
    }
}
signed main(){return Wisadel::main();}
// All talk and never answer
```


---

完结撒花~

---

## 作者：Genius_Star (赞：0)

**本题解仅使用倍增。**

### 思路：

真的 shi。

考虑分讨一下，设 $z$ 与 $t = \operatorname{lca}(x, y)$ 的最近公共祖先为 $l$。

若 $l$ 是 $t$ 的祖先，则贡献是：

$$w_z - 2dep_z - dep_x - dep_y + 4 dep_l$$

相当于我们要找到一个 $z$ 使得 $w_z - 2dep_z$ 最大，且 $z$ 是 $l$ 子树内的点（因为只需要满足 $l$ 是 $t$ 与 $z$ 的公共祖先即可，因为如果不是最近祖先的话只加 $4dep_l$ 肯定不是最优）。

然后若 $l = t$，设其在 $h$ 子树内（在 $x \to y$ 路径上），则贡献是：

$w_z - (dep_z + dep_y - 2dep_h + dep_x - dep_t + dep_z - dep_t) = \\w_z - 2dep_z - dep_x - dep_y + 2dep_t + 2dep_h$

则考虑预处理这两个东西：

$$S_u = 4 dep_u + \max(w_v - 2dep_v)$$

$$T_u = 2 dep_u + \max(w_v - 2dep_v)$$

则相当于询问 $t \sim root$ 路径上 $\max(S_u) - dep_x - dep_y$ 和 $u \to v$ 路径上 $\max(T_u) - dep_x - dep_y + 2dep_t$。

树上倍增即可，时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10, M = 20;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
ll ans;
int n, q, u, v, w, x, y, t;
int a[N], d[N];
int fa[M][N];
ll Max[M][N];
ll dep[N], s[N], S[N], T[N];
vector<pair<int, int>> E[N];
inline void add(int u, int v, int w){
	E[u].push_back({v, w});
	E[v].push_back({u, w});
}
inline void dfs(int u, int fa){
	s[u] = a[u] - 2 * dep[u];
	for(auto t : E[u]){
		int v = t.fi, w = t.se;
		if(v == fa)
		  continue;
		d[v] = d[u] + 1;
		dep[v] = dep[u] + w;
		dfs(v, u);
		s[u] = max(s[u], s[v]); 
	}
}
inline void dfs2(int u, int f){
	Max[0][u] = T[u];
	for(int i = 1; i < M; ++i){
		fa[i][u] = fa[i - 1][fa[i - 1][u]];
		Max[i][u] = max(Max[i - 1][u], Max[i - 1][fa[i - 1][u]]);
	}
	for(auto t : E[u]){
		int v = t.fi;
		if(v == f)
		  continue;
		fa[0][v] = u;
		S[v] = max(S[v], S[u]);
		dfs2(v, u);
	}
}
inline ll Ask(int u, int k){
	if(k < 0)
	  return -1e18;
	ll ans = -1e18;
	for(int i = M - 1; i >= 0; --i){
		if((k >> i) & 1){
			ans = max(ans, Max[i][u]);
			u = fa[i][u];
		}
	}
	return max(ans, T[u]);
}
namespace Tree{
	int t[N], fa[N], dep[N], siz[N], son[N];
	inline void dfs1(int u, int f){
		siz[u] = 1;
		for(auto t : E[u]){
			int v = t.fi;
			if(v == f)
			  continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]])
			  son[u] = v;
		}
	}
	inline void dfs2(int u, int k){
		t[u] = k;
		if(!son[u])
		  return ;
		dfs2(son[u], k);
		for(auto t : E[u]){
			int v = t.fi;
			if(v == fa[u] || v == son[u])
			  continue;
			dfs2(v, v);
		}
	}
	inline int Lca(int u, int v){
		while(t[u] != t[v]){
			if(dep[t[u]] < dep[t[v]])
			  swap(u, v);
			u = fa[t[u]];
		}
		return dep[u] < dep[v] ? u : v;
	}
	inline void init(int rt = 1){
		dfs1(1, 1);
		dfs2(1, 1);
	}
};
bool End;
int main(){
//	open("A.in", "A.out");
	memset(Max, -0x3f, sizeof(Max));
	n = read(), q = read();
	for(int i = 1; i <= n; ++i)
	  a[i] = read();
	for(int i = 1; i < n; ++i){
		u = read(), v = read(), w = read();
		add(u, v, w);
	}
	dfs(1, 1);
	Tree::init();
	for(int i = 1; i <= n; ++i){
		S[i] = s[i] + 4 * dep[i];
		T[i] = s[i] + 2 * dep[i];
	} 
	dfs2(1, 1);
	while(q--){
		x = read(), y = read();
		t = Tree::Lca(x, y);
		ans = max(S[t] - dep[x] - dep[y], max(Ask(x, d[x] - d[t]), Ask(y, d[y] - d[t])) - dep[x] - dep[y] + 2 * dep[t]);
		write(ans + a[x] + a[y]);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：Redshift_Shine (赞：0)

## 闲话

把 T2 出得比 T1 简单，颇有 CSP-S 2022 复赛之遗风。

## 题解

考虑将答案拆分成两个部分。

第一个部分为无论如何选择 $z_i$ 都必然获得的利润，显然，这个值是两端点城市演讲收入之和减去两城市之间路费的值。

第二个部分为选择 $z_i$ 所获得的额外利润。额外利润的值是 $z_i$ 的演讲收入减去从 $z_i$ 走到两城市之间路径上所需的最少路费**的 $2$ 倍**。因为 $z_i$ 是第二个城市，所以需要从路径的某一个点开始走到 $z_i$ 再原路返回。

令 $d_{i,j}$ 为从城市 $i$ 到城市 $j$ 需要花费的最少路费，$d_{i,(u,v)}$ 为从城市 $i$ 走到路径 $(u,v)$ 上需花费的最少路费。显然，当 $i$ 在 $(u,v)$ 上时，$d_{i,(u,v)}=0$。

答案可表示为 $c_x+c_y-d_{x,y}+c_z-2d_{z,(x,y)}$。

答案的前三个量都可以通过树上前缀和轻松求得。考虑如何快速求最后两个量。

将最后两项捆绑起来求。

考虑对于每一个点 $x$ 求 $\max_{1\le i\le n}(c_i-2d_{x,i})$。

首先，可以按照树上广义后序遍历顺序求出 $\max_{i\in S_x}(c_i-2d_{x,i})$，其中 $S_x$ 为节点 $x$ 的**子树内节点**集合。令上述值为 $r_x$，则 $r_x\leftarrow\max_{i\in s_x}(r_i-2d_{x,i})$，其中 $s_x$ 为节点 $x$ 的**儿子节点**集合，请注意 $S_x$ 和 $s_x$ 的定义差别。

接下来，我们可以把子树信息和除了父节点以外的信息拼起来组成以每个节点为根的整棵树的答案，也就是按照树上广义前序遍历顺序求出 $\max_{1\le i\le n}(c_i-2d_{x,i})$，转移方法为 $r_x\leftarrow\max(r_x,r_{f_x}-2d_{x,f_x})$，其中 $f_x$ 为 $x$ 节点的父亲。特别的，不对遍历起点的节点进行此转移。

有了以上的信息后，使用树链剖分在每次询问时求解 $\max(c_z-2d_{z,(x,y)})$ 即可。

时间复杂度 $O(n\log^2 n)$。使用 ST 表进行实现可以做到 $O(n\log n)$，不过我并没有这样做。

**注意：以下代码为赛时代码，没有严格使用上述方法对问题进行求解，可能会有部分不必要的复杂操作，请自行辨别并在 ~~C+V~~ 借鉴时加以改进。**

```c++
#include <cctype>
#include <cstdio>
#include <set>
#include <utility>
#include <vector>
using namespace std;
const int N = 2e5 + 10;
int n, q, f[N], siz[N], ds[N], dfn[N], tp[N], idx, rnk[N], dep[N];
using ll = long long;
ll c[N], mx[N], dsv[N], fv[N];
using pil = pair<int, ll>;
vector<pil> road[N];
template <typename _Tp> inline void read(_Tp &x)
{
    static char ch;
    while (ch = getchar(), !isdigit(ch))
        ;
    x = (ch ^ 48);
    while (ch = getchar(), isdigit(ch))
        x = (x << 3) + (x << 1) + (ch ^ 48);
}
template <typename _Tp, typename... _Args> inline void read(_Tp &x, _Args &...args)
{
    read(x);
    read(args...);
}
void dfs_init(int x)
{
    dep[x] = dep[f[x]] + 1;
    mx[x] = c[x];
    siz[x] = 1;
    for (auto &[i, v] : road[x])
    {
        if (i == f[x])
            continue;
        f[i] = x;
        fv[i] = v;
        dfs_init(i);
        siz[x] += siz[i];
        if (siz[i] > siz[ds[x]])
        {
            ds[x] = i;
            dsv[x] = v;
        }
        mx[x] = max(mx[x], mx[i] - v * 2);
    }
}
void dfs_build(int x, int ttp)
{
    dfn[x] = ++idx;
    rnk[idx] = x;
    tp[x] = ttp;
    if (!ds[x])
        return;
    mx[ds[x]] = max(mx[ds[x]], mx[x] - dsv[x] * 2);
    dfs_build(ds[x], ttp);
    for (auto &[i, v] : road[x])
    {
        if (i == f[x] or i == ds[x])
            continue;
        mx[i] = max(mx[i], mx[x] - v * 2);
        dfs_build(i, i);
    }
}
ll mxtr[N << 2], edv[N << 2];
void build(int x, int l, int r)
{
    if (l == r)
    {
        mxtr[x] = mx[rnk[l]];
        edv[x] = fv[rnk[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    edv[x] = edv[x << 1] + edv[x << 1 | 1];
    mxtr[x] = max(mxtr[x << 1], mxtr[x << 1 | 1]);
}
using pll = pair<ll, ll>;
pll query(int x, int l, int r, int lb, int rb)
{
    if (l >= lb and r <= rb)
        return {mxtr[x], edv[x]};
    pll res = {0, 0};
    int mid = (l + r) >> 1;
    if (lb <= mid)
    {
        auto [r1, r2] = query(x << 1, l, mid, lb, rb);
        res.first = max(res.first, r1);
        res.second += r2;
    }
    if (rb > mid)
    {
        auto [r1, r2] = query(x << 1 | 1, mid + 1, r, lb, rb);
        res.first = max(res.first, r1);
        res.second += r2;
    }
    return res;
}
pll query(int l, int r)
{
    pll res = {0, c[l] + c[r]};
    while (tp[l] != tp[r])
    {
        if (dep[tp[l]] > dep[tp[r]])
            swap(l, r);
        auto [r1, r2] = query(1, 1, n, dfn[tp[r]], dfn[r]);
        res.first = max(res.first, r1);
        res.second -= r2;
        r = f[tp[r]];
    }
    if (dep[l] > dep[r])
        swap(l, r);
    auto [r1, r2] = query(1, 1, n, dfn[l], dfn[r]);
    res.first = max(res.first, r1);
    res.second -= r2;
    res.second += fv[l];
    return res;
}
int main()
{
    // freopen("speaker.in", "r", stdin);
    // freopen("speaker.out", "w", stdout);
    read(n, q);
    for (int i = 1; i <= n; i++)
    {
        read(c[i]);
    }
    for (int i = 1, x, y, z; i < n; i++)
    {
        read(x, y, z);
        road[x].emplace_back(y, z);
        road[y].emplace_back(x, z);
    }
    dfs_init(1);
    dfs_build(1, 1);
    build(1, 1, n);
    // for (int i = 1; i <= n; i++)
    // {
    //     printf("%lld%c", mx[i], " \n"[i == n]);
    // }
    for (int i = 1, l, r; i <= q; i++)
    {
        read(l, r);
        auto [r1, r2] = query(l, r);
        printf("%lld\n", r1 + r2);
    }
}
```

---

## 作者：Night_sea_64 (赞：0)

讲个笑话：某人赛时在代码里写了 $32$ 分暴力，但是暴力写挂了，正解写对了，$100\rarr68$。

回归题目。不妨指定 $1$ 为根。首先算出不加第二个点的答案为 $c_x+c_y-dis(x,y)$。其中 $dis(x,y)$ 为 $x$ 到 $y$ 路径边权之和。

第二个演讲点有如下三种情况：

1. $x$ 到 $\text{LCA}(x,y)$ 的路径中某个点往下走到达的；
1. $y$ 到 $\text{LCA}(x,y)$ 的路径中某个点往下走到达的；
1. $\text{LCA}(x,y)$ 到根的路径中某个点往下走到达的；

先来讲前两种。这两种情况比较相似，不妨以第一种为例。

我们设第二个演讲点为 $p$，是 $x$ 到 $\text{LCA}(x,y)$ 路径上点 $q$ 往下走到达的。那么答案比原来多了 $c_p-2\times dis(p,q)$。其中 $dis(p,q)=d_p-d_q$，$d_u$ 为根结点到 $u$ 的路径边权和。也就是答案比原来多了 $c_p-2\times d_p+2\times d_q$。

可以对于每个 $q$ 算出其子树中 $c_u-2\times d_u$ 的最大值，这样在知道 $q$ 的情况下就能很快知道上述那个值是多少了。最后求的是 $x$ 到 $\text{LCA}(x,y)$ 路径上，每个 $q$ 的上述值是多少，取最大值。这个只需像倍增求 LCA 一样，维护长度为 $2^k$ 的链上的信息，即可倍增求出整段了。

第三种情况其实也大同小异。还是设演讲点为 $p$，是 $\text{LCA}(x,y)$ 的祖先 $q$ 往下走到的。此时答案比原来多了 $c_p-2\times dis(p,\text{LCA}(x,y))$。也就是 $c_p-2\times d_p+4\times d_q-2\times d_{\text{LCA}(x,y)}$。

也是对于每个 $q$ 算出其子树中 $c_u-2\times d_u$ 的最大值，不过之前是把这个值加上 $2\times d_q$，这回加上了 $4\times d_q$。也按照倍增维护这个就行了。$d_{\text{LCA}(x,y)}$ 是询问的时候再算的。

这个过程中，虽然算的是每个点子树的信息，有可能取到沿着 $x$ 到 $y$ 路径上再多走一段的方案，但是这样明显不优，比它更优的方案在另外的 $q$ 上会取到的。

时间复杂度 $O(n+q\log n)$。

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;
int n,q,a[200010];
struct edge{int x,w;};
vector<edge>v[200010];
int dep[200010],fa[200010][20];
long long maxn[200010],max1[200010][20],max2[200010][20];
long long dis[200010];
void dfs(int x,int last)
{
    dep[x]=dep[last]+1,fa[x][0]=last;
    for(int i=1;i<=17;i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    maxn[x]=a[x]-2*dis[x];
    for(auto e:v[x])
        if(e.x!=last)
        {
            dis[e.x]=dis[x]+e.w;
            dfs(e.x,x);
            maxn[x]=max(maxn[x],maxn[e.x]);
        }
}
void dfs2(int x,int last)
{
    max1[x][0]=maxn[x]+2*dis[x];
    max2[x][0]=maxn[x]+4*dis[x];
    for(int i=1;i<=17;i++)
    {
        max1[x][i]=max(max1[x][i-1],max1[fa[x][i-1]][i-1]);
        max2[x][i]=max(max2[x][i-1],max2[fa[x][i-1]][i-1]);
    }
    for(auto e:v[x])
        if(e.x!=last)dfs2(e.x,x);
}
inline int LCA(int x,int y)
{
    if(dep[x]<dep[y])swap(x,y);
    for(int i=17;i>=0;i--)
        if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
    if(x==y)return x;
    for(int i=17;i>=0;i--)
        if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
inline long long getmax(int x,int y,int type)
{
    if(type==1)
    {
        long long ans=maxn[y]+2*dis[y];
        for(int i=17;i>=0;i--)
            if(dep[fa[x][i]]>=dep[y])ans=max(ans,max1[x][i]),x=fa[x][i];
        return ans;
    }
    else
    {
        long long ans=maxn[y]+4*dis[y];
        for(int i=17;i>=0;i--)
            if(dep[fa[x][i]]>=dep[y])ans=max(ans,max2[x][i]),x=fa[x][i];
        return ans;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<n;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        v[x].push_back((edge){y,w});
        v[y].push_back((edge){x,w});
    }
    dfs(1,0);
    dfs2(1,0);
    while(q--)
    {
        int x,y;
        cin>>x>>y;
        int lca=LCA(x,y);
        cout<<a[x]+a[y]-dis[x]-dis[y]+2*dis[lca]+max(max(getmax(x,lca,1),getmax(y,lca,1)),getmax(lca,1,2)-2*dis[lca])<<"\n";
    }
    return 0;
}
```

---

