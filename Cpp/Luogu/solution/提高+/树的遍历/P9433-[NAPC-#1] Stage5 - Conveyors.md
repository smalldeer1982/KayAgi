# [NAPC-#1] Stage5 - Conveyors

## 题目背景

>![](https://cdn.luogu.com.cn/upload/image_hosting/4wcng8qe.png)
>
>— rs8

## 题目描述

### 【简要题意】

给定一棵 $n$ 个节点的无根树以及树上的 $k$ 个关键节点，边有边权（即边的长度）。$q$ 次询问，每次给出 $s,t$，问从 $s$ 到 $t$ 且经过至少一次**每个**关键节点的路径的最短长度。

### 【原始题意】

在某一面 kid 又遇到了往返跑关卡。Really popular apparently.

关卡给 kid 留下的空间形状是一棵无向带权树，边权即边的长度。这棵树有 $n$ 个节点，其中有 $k$ 个点上各**恰**有一个发光小球，kid 经过有小球的点（称为关键点）时就可以收集小球。kid 从 $s$ 点出发，当他收集到全部 $k$ 个小球时，传送门就会在 $t$ 点出现。

想速通的 kid 想知道他从 $s$ 点出发收集到全部 $k$ 个小球并进入位于 $t$ 点的传送门所需要走的最小时间（其实也就是路径长度，因为 kid 的速度恒定）。

但是 Geezer 很狡猾，塔内这一面被复制成了 $q$ 层，每层的 $s$ 和 $t$ 还可能有变动。kid 慌了，忙找到你求助。

## 说明/提示

### 【数据范围】

**本题采用捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c|c}
\textbf{Subtask} & \text{测试点编号} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1&1\sim14 & n\leqslant15,\mathbf R& 18 \r
\textsf2&15\sim20 & q=1 & 18 \r
\textsf3&46\sim48 & s=t,k=n & 6 \r
\textsf4&21\sim25 & k=n & 18 \r
\textsf5&26\sim30 & \mathbf A & 18 \r
\textsf6&31\sim45 & - & 22 \r
\end{array}
$$
友情提醒：$\text{Subtask }\textsf1$ 并没有限制 $q$ 的范围。

- 特殊性质 $\mathbf R$：保证树随机生成（对于 $i\ge2$，在 $[1,i)$ 内随机选择一个点和 $i$ 连边，边权在一固定区间内均匀随机生成）。
- 特殊性质 $\mathbf A$：定义 $f(x)$ 表示存在 $i,j\in[1,n]$（可能 $i=j$） 且 $i,j$ 均为关键点，使得 $x$ 在 $i$ 到 $j$ 的最短路径上；那么对每次询问保证 $f(s)$ 和 $f(t)$ 均成立。

对于 $100\%$ 的数据，$1\leqslant n\leqslant 10^5$，$1\leqslant q\leqslant 10^5$，$1\leqslant k\leqslant n$，$1\leqslant w\leqslant 10^4$，$1\leqslant u,v,s,t\leqslant n$。

### 【样例解释 #1】
![](https://cdn.luogu.com.cn/upload/image_hosting/3hvr33bz.png)

图中加粗节点表示关键点。

对于每组询问，以下为一种最优路径（最优路径可能有多条）：
1. $2\to1\to3$。
2. $2\to1\to3\to1$。
3. $7\to1\to2\to1\to3\to1$。
4. $4\to3\to1\to2\to1\to3\to5$。
5. $6\to2\to1\to3\to1\to2\to6$。

## 样例 #1

### 输入

```
7 5 2
1 2 3
1 3 5
3 4 2
3 5 4
2 6 1
1 7 1
2 3
2 3
2 1
7 1
4 5
6 6```

### 输出

```
8
13
17
22
18```

# 题解

## 作者：y_kx_b (赞：7)

## Stage5 - Conveyors

预计难度：\*2200 左右，绿。

前置芝士：树的 dfs，lca。

~~如果你不想看暴搜解法可以直接跳到 Sub3。~~

---

### $\textbf{Sub }{\sf1}\textbf:$ $n\leqslant15$。

看到如此小的数据（毕竟不同本质的询问只有 $q\leqslant\frac{15\times14}2=105$ 次，重复询问可以记忆化），考虑暴力。但是无脑暴力应该是跑不过的（心虚），需要优化。

首先显然同一条边同一方向最多走一次（图我不知道有没有这个性质，但树是显然的：两次都从左往右走不如第一次走了之后一股脑把右边全处理完。），那么复杂度就从无脑爆搜 $O(?)$ 成了 $O(q(2n)!)$（树中单向边的数量为 $2n$ 量级）。唔，理论复杂度还是爆炸，那么需要玄学的剪枝出场了（）。

首先显然有最优性剪枝：如果搜到当前节点时答案已经超过当前搜到的最优解那么直接返回。

然后，我们知道当 $k$ 个点全部走过一遍之后可以直接知道剩下的路该怎么走（直接从当前节点笔直走到 $t$），那么可以预处理出每个点到 $t$ 的最短路，当当前已经把 $k$ 个点走完的时候直接更新 `ans = sum + dis[u];`。同样这也可以优化上面的最优性剪枝，如果当前点直接走到 $t$ 都比当前最优解大了，那么直接返回。

虽然理论复杂度没变（什），但随机数据的表现还是不错的！至少我的代码大概 500ms 就可以跑过 $n=15,k=13$ 的脚造数据（）

[爆搜 code](https://www.luogu.com.cn/paste/1sqcxt7j)。

---
### $\textbf{Sub1 Another Solution}$
唔，如果你还是不放心，怕被卡，这里还有一个不会被这个 $\text{Sub}$ 卡的做法：状压。~~应该也好想吧，毕竟 $n$ 这么小 qwq~~

设 $dp_{j,k}$ 为当前路径在 $j$ 点结尾，所经过的重要点集合为 $k$ 的最小路径长度。那么转移就枚举路径的上一个点，有

$$
dp_{v,st} = \begin{cases}\min\limits_{u\to v} (dp_{u,\complement_{_{st}}\{v\}} + w_{u\to v})\text{, if }v\text{ is important}\\\min\limits_{u\to v} (dp_{u,st} + w_{u\to v})\text{, Otherwise.}\end{cases}
$$

如果是用刷表法 dp，就可以直接把方程写成 `dp[i][v][st | 1 << id[v]] <- dp[i][u][st] + w`（伪码）。

对每个起点跑一遍 dp 就可以得到所有询问的答案。

这个 dp 的阶段是经过的边的数量（显然不超过 $2n$），枚举路径起点和它和状压集合、$u$、$v$，时间复杂度 $O(n^32^k)$，足以通过（？）。

还能优化，发现这东西长得极其像 Bellman-ford 算法，仔细一想，可以把图拆成分层图（每个点拆成 $2^k$ 个点）跑最短路，时间复杂度 $O(2^k\times n^2\log n)$ ~~虽然这都快成常数优化了~~。

[code](https://www.luogu.com.cn/paste/xbk5rfuo)。


### $\textbf{Sub }{\sf2}\textbf:$ $q=1$。

~~唔，没想到有啥好做法呢 qwq~~

---
下面就是提示正解的部分分了。
### $\textbf{Sub }{\sf3}\textbf:$ $s=t,k=n$。

结论是显然的：答案为整棵树所有边的边权乘 $2$，因为每条边都要来回被走一遍。


### $\textbf{Sub }{\sf4}\textbf:$ $k=n$。

那么当 $s\not=t$ 时我们假设以 $t$ 为起点和终点然后像上面一样走，但是开始要先从 $t$ 笔直走到 $s$（显然存在一种这样的合法方案），这时走过的路程还是 整棵树所有的边权乘 $2$；最后减掉 $t$ 到 $s$ 的路程就是从 $s$ 到 $t$ 并且走过整棵树的点的最小距离。

![](https://cdn.luogu.com.cn/upload/image_hosting/293f0kni.png)

比如在这棵~~乙烯~~树中，设 $s=1$，$t=2$，那么有路径 $(2\to)1\to6\to1\to5\to1\to2\to4\to2\to3\to2$。加上括号内就是从 $t$ 开始遍历全树最后回到 $t$ 的路径；去掉括号内就是从 $s$ 开始经过全树节点最后到达 $t$ 的路径，也就是题目所求的最短合法路径之一。

### $\textbf{Sub }{\sf5}\textbf:$ $\mathbf A$。
和上面差不多的思路，只不过没有关键点的位置就不用搜了。也就是说，全局答案变成了（包含所有 $k$ 个关键点的连通块内的最小总边权）乘 $2$ 减去 $s$ 与 $t$ 的距离。

至于包含所有 $k$ 个关键点的最小连通块，发现其实就是 $k$ 个关键点两两路径的并（可以证明，也等于第一个关键点到第二个的路径、第二个到第三个的路径……到最后一个关键点的路径的并；那么我们把一个关键点作为根，那么一个点在该连通块内的充要条件就是该点子树内含有关键点）。也就是说，题面中定义的 $f(x)$ 其实保证的就是 $x$ 在这个连通块内。

### $\textbf{Sub }{\sf6}\textbf:$ 无特殊限制。
当 $t$ 点不在连通块内时我们设离 $t$ 最近的在连通块内的点为 $v$ 那么显然如果最后要到 $t$ 点只能通过 $v$ 点到达。那么我们可以先算出 $s$ 到 $v$ 的答案，然后从 $v$ 走到 $t$ 即可。类似地，$s$ 也可以对称地处理：设离 $s$ 最近的在连通块内的点为 $u$ 那么答案就是把 $u$ 当 `s` 算的答案加上 $s$ 和 $u$ 的距离。

code：
```cpp
int n, q, k;
int head[N], ne[N << 1], to[N << 1], w[N << 1], idx1 = 0;
void add(int u, int v, int x) {
	to[idx1] = v, w[idx1] = x, ne[idx1] = head[u], head[u] = idx1++;
}
#define ws ambiguous1
int fa[20][N], dph[N], ws[N];//ws：该点到根节点的距离
bool k0[N], k1[N];//k0：该点是否为关键点；
//k1：该点是否在（包含所有 k 个关键点的最小连通块）内
int sizk[N];//子树中关键点的数量

void dfs0(int u, int f) {
	dph[u] = dph[f] + 1, fa[0][u] = f;
	if(k0[u]) sizk[u] = 1;
	for(int i = head[u]; ~i; i = ne[i]) if(to[i] != f) {
		int &v = to[i];
		ws[v] = ws[u] + w[i];
		dfs0(v, u);
		sizk[u] += sizk[v];
	}
}
int lca(int x, int y) {
	if(dph[x] < dph[y]) swap(x, y);
	int ww = dph[x] - dph[y];
	for(int j = 0; j < 20; j++) if(ww & 1 << j) x = fa[j][x];
	if(x == y) return y;
	for(int j = 20/**/- 1; ~j; j--) if(fa[j][x] != fa[j][y]) x = fa[j][x], y = fa[j][y];
	return fa[0][x];
}
int dist(int u, int v) {return ws[u] + ws[v] - ws[lca(u, v)] * 2;}
namespace Subtask1 {
	void major() {
		while(q--) printf("%d\n", dist(read(), read()));
	}
}
int gsum = 0;//连通块的总边权
/*int*/void dfs1(int u) {//如果根是关键点，那么一个点在连通块内的充要条件就是该点子树内存在关键点。
	if(!sizk[u]) return;
	k1[u] = 1;
	for(int i = head[u]; ~i; i = ne[i]) if(to[i] != fa[0][u]) {
		int &v = to[i];
		dfs1(v);
		if(k1[u] && k1[v]) gsum += w[i];
	}
}
int getk1(int u) {//u 往上走第一个在连通块内的点
/**/if(k1[u]) return u;//如果 u 已经在连通块内了那么就不需要额外加上一条链了
//（这个函数唯一用到的地方就是询问时加上 u/v -> s/t 的链，如果 u = s 那么链的长度显然是0
	for(int j = 19; ~j; j--) if(fa[j][u] && !k1[fa[j][u]]) u = fa[j][u];
	//当然了你也可以写一个二分解决（），这是顺着 lca 板子写的
	return fa[0][u];
}
bool major(int Testcase = 1) {
	memset(head, -1, sizeof head);
	n = read(), q = read(), k = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), ww = read();
		add(u, v, ww), add(v, u, ww);
	}
	int root = 1;
	for(int i = 1; i <= k; i++) k0[root = read()] = 1;
	//k>0，这里把 root 直接设成某一个关键点（为了避免算连通块的时候的又臭又长的特判）
	dfs0(root, 0);
	for(int j = 1; j < 20; j++) for(int i = 1; i <= n; i++)
		fa[j][i] = fa[j - 1][fa[j - 1][i]];
	dfs1(root);
	while(q--) {
		int s = read(), t = read(), u = getk1(s), v = getk1(t);
		printf("%d\n", gsum * 2 - dist(u, v) + (ws[s] - ws[u]) + (ws[t] - ws[v]));
	}
	return Testcase;
}
```

---

## 作者：Weekoder (赞：4)

### 思路

由于要去到所有关键点，我们一定会遍历包含所有关键点的最小连通块。在连通块内的点 $cur$ 被标记为 $isK_{cur}=1$。

先考虑比较简单的情况：如果 $s,t$ 都在连通块内，该怎么做？或许可以再考虑更简单的情况：$s=t$ 时，该怎么做？显然，我们从 $s$ 出发，经过所有关键点路径上的边两次（一次去，一次回）回到 $t$。若连通块内的边权之和为 $w$，则答案显然为 $2w$。那如果 $s\ne t$ 怎么办？可以注意到，我们在刚刚操作的基础上，回到的点 $t$ 不一样了，**省下了从 $\bm{t}$ 再回到 $\bm{s}$ 的路程**。这段路程是树上的简单路径，LCA 维护即可，答案为 $2w-dist(u,v)$。可以发现，这两种情况是可以合并的。

接下来，再考虑 $s,t$ 不在连通块内的情况就很简单了。既然不在连通块内，那就倍增跳进去，加上这段跳的路程。

至于预处理连通块，边权和，LCA 什么的交给 DFS 就行了。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 5;

struct Edge {
	int to, w;
}; 

int n, q, k, root, deep[N], dp[N][30], sz[N], dis[N], sum;

bool isK[N];

vector<Edge> nbr[N];

int dfs(int cur, int fa) {
	deep[cur] = deep[fa] + 1;
	dp[cur][0] = fa;
	if (isK[cur])
		sz[cur] = 1;
	for (int j = 1; (1 << j) <= deep[cur]; j++)
		dp[cur][j] = dp[dp[cur][j - 1]][j - 1];
	for (auto nxt : nbr[cur])
		if (nxt.to != fa)
			dis[nxt.to] = dis[cur] + nxt.w, sz[cur] += dfs(nxt.to, cur);
	return sz[cur];
}

void get_sum(int cur, int fa) {
	if (!sz[cur])
		return ;
	isK[cur] = 1;
	for (auto nxt : nbr[cur])
		if (nxt.to != fa)
			get_sum(nxt.to, cur), sum += isK[nxt.to] * nxt.w;
}

int nbrK(int cur) {
	if (isK[cur])
		return cur;
	for (int j = 20; j >= 0; j--)
		if (dp[cur][j] && !isK[dp[cur][j]])
			cur = dp[cur][j];
	return dp[cur][0];
}

int lca(int x, int y) {
	if (deep[x] > deep[y])
		swap(x, y);
	for (int i = 20; i >= 0; i--)
		if (deep[dp[y][i]] >= deep[x])
			y = dp[y][i];
	if (x == y)
		return x;
	for (int i = 20; i >= 0; i--)
		if (dp[x][i] != dp[y][i])
			x = dp[x][i], y = dp[y][i];
	return dp[x][0];
}

int dist(int u, int v) {
	return dis[u] + dis[v] - 2 * dis[lca(u, v)];
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> q >> k;
	for (int i = 1, u, v, w; i < n; i++) {
		cin >> u >> v >> w;
		nbr[u].emplace_back((Edge){v, w});
		nbr[v].emplace_back((Edge){u, w});
	}
	for (int i = 1, u; i <= k; i++) {
		cin >> u;
		isK[u] = 1;
		root = u;
	}
	dfs(root, 0);
	get_sum(root, 0);
	while (q --) {
		int s, t, u, v;
        cin >> s >> t;
		u = nbrK(s), v = nbrK(t);
		cout << sum * 2 - dist(u, v) + dist(s, u) + dist(v, t) << "\n";
	}
	return 0;
}
```

---

## 作者：shinkuu (赞：2)

来发毒瘤分讨题解。我写了 220+ 行，可能是实现不太好。

因为要经过每个关键点，所以答案一定和包含所有点的最小连通块有关，先处理出来。

然后考虑对两点间最短路径进行分类讨论：

- 如果路径全部在连通块上。

此时容易发现，一条边在连通块上，如果它不在路径上，为了能够到达终点，我们需要先经过这条边到达某些关键点，再走回来。所以这条边贡献为 $2\times w$。否则，经过边后不用返回，贡献为 $w$。总和也可以表示为 $2\times s-l$，其中 $s$ 为连通块内边权和，$l$ 为路径长度。

- 如果路径有边在连通块上。

不难发现，耗时最短的路线一定是对路径和连通块的交集做一次上个情况的计算，然后加上剩下的路径边权之和。设 $t$ 为交集边权之和，答案即为 $l+2\times(s-t)$。

- 如果路径没有边在连通块上。

此时最短路径明显是从距离连通块最近的点走到连通块上，然后遍历一遍连通块再回来，最后走到终点。连通块中每条边都要走两遍。设 $d$ 为上述最近的点到连通块距离，答案即为 $l+2\times(s+d)$。

以上的量，$t$ 可以 dfs 预处理，$s,l$ 树剖或倍增，$d$ 我直接 dij 预处理。总复杂度 $O(n\log n)$。常数还好。

极其毒瘤的 code：

```cpp
int n,m,k,idx;bool pd[N];pii p[N];
int sum,siz[N],dep[N],fa[N],Dep[N],son[N],id[N];bool d[N][2];
int cnt,dfn[N],rk[N],top[N];
int dis[N];bool vis[N];
int tot,head[N];
struct node{
	int to,nxt,cw;
}e[N<<1];
inline void add(int u,int v,int w){
	e[++tot]={v,head[u],w};
	head[u]=tot;
}
namespace init{
	void dfs1(int u,int f){
		siz[u]=1;
		dep[u]=dep[f]+1;
		fa[u]=f;
		if(pd[u])
			d[u][1]=true;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==f)
				continue;
			Dep[v]=Dep[u]+e[i].cw;
			id[v]=i;
			dfs1(v,u);
			siz[u]+=siz[v];
			if(siz[v]>siz[son[u]])
				son[u]=v;
		}
	}
	void dfs2(int u,int t){
		dfn[u]=++cnt,rk[cnt]=u;
		top[u]=t;
		if(!son[u])
			return;
		dfs2(son[u],t);
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==son[u]||v==fa[u])
				continue;
			dfs2(v,v);
		}
	}
	void dfs3(int u){
		if(pd[u])
			d[u][1]=true;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==fa[u])
				continue;
			if(pd[u]||d[u][0])
				d[v][0]=true;
			dfs3(v);
			if(d[v][1])
				d[u][1]=true;
			if(d[v][0]&&d[v][1])
				sum+=e[i].cw;
		}
		if(d[u][0]&&d[u][1])
			pd[u]=true;
	}
	int get_lca(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]])
				swap(u,v);
			u=fa[top[u]];
		}
		if(dfn[u]>dfn[v])
			return v;
		return u;
	}
	void init_pos(){
		for(int i=1;i<=n;i++){
			if(pd[i])
				p[++idx]=Mp(dfn[i],i);
		}
		sort(p+1,p+k+1);
		for(int i=2;i<=k;i++)
			pd[get_lca(p[i-1].se,p[i].se)]=true;
	}
	void init_dis(){
		priority_queue<pii> q;
		mems(dis,0x3f);
		for(int i=1;i<=n;i++){
			if(pd[i]){
				q.push(Mp(0,i));
				dis[i]=0;
			}
		}
		while(q.size()){
			int u=q.top().se;
			q.pop();
			if(vis[u])
				continue;
			vis[u]=true;
			for(int i=head[u];i;i=e[i].nxt){
				int v=e[i].to;
				if(vis[v]||dis[v]<=dis[u]+e[i].cw)
					continue;
				dis[v]=dis[u]+e[i].cw;
				q.push(Mp(-dis[v],v));
			}
		}
	}
}
using namespace init;
namespace SGT{
	struct Node{
		int f,g,h;
		Node(){
			f=g=0,h=inf;
		}
	}tr[N<<2];
	inline Node pushup(Node lc,Node rc){
		Node o;
		o.f=lc.f+rc.f;
		o.g=lc.g+rc.g;
		o.h=min(lc.h,rc.h);
		return o;
	}
	void build(int l,int r,int o){
		if(l==r){
			if(d[rk[l]][0]&&d[rk[l]][1])
				tr[o].f=e[id[rk[l]]].cw;
			else 
				tr[o].g=e[id[rk[l]]].cw;
			tr[o].h=dis[rk[l]];
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,o<<1);
		build(mid+1,r,o<<1|1);
		tr[o]=pushup(tr[o<<1],tr[o<<1|1]);
	}
	Node query(int l,int r,int o,int x,int y){
		if(l>=x&&r<=y)
			return tr[o];
		int mid=(l+r)>>1;
		if(x<=mid&&y>mid)
			return pushup(query(l,mid,o<<1,x,y),query(mid+1,r,o<<1|1,x,y));
		if(x<=mid)
			return query(l,mid,o<<1,x,y);
		return query(mid+1,r,o<<1|1,x,y);
	}
}
using namespace SGT;
namespace run{
	int calc(int u,int v){
		int x=u,y=v;
		Node ret;
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]])
				swap(u,v);
			ret=pushup(ret,query(1,n,1,dfn[top[u]],dfn[u]));
			u=fa[top[u]];
		}
		if(dfn[u]>dfn[v])
			swap(u,v);
		if(dfn[u]<dfn[v])
			ret=pushup(ret,query(1,n,1,dfn[u]+1,dfn[v]));
		ret.h=min(ret.h,query(1,n,1,dfn[u],dfn[u]).h);
		int len=Dep[x]+Dep[y]-2*Dep[u];
		if(!ret.f&&ret.h)
			return len+2*(sum+ret.h);
		if(!ret.g)
			return 2*sum-len;
		return len+2*(sum-ret.f);
	}
}
using namespace run;
void solve(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,u,v,w;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	for(int i=1,x;i<=k;i++){
		scanf("%d",&x);
		pd[x]=true;
	}
	dfs1(1,0);
	dfs2(1,1);
	init_pos();
	dfs3(1);
	init_dis();
	build(1,n,1);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		printf("%d\n",calc(u,v));
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		solve();
}
```

---

## 作者：okra_l (赞：1)

### 题目链接 ###

[P9433 [NAPC-#1] Stage5 - Conveyors](https://www.luogu.com.cn/problem/P9433)

---

先考虑特殊性质 A 的做法，特殊性质 A 保证了对于 $s$ 到 $t$ 的简单路径一定在包含所有关键点的最小连通块上。可以发现从 $s$ 到 $t$ 的至少经过一次每个关键节点的最短路径，一定是从 $s$ 到 $t$ 的简单路径走一遍，除这个简单路径外这个连通块的其他边走两遍。


可以一次 DFS 求出这个最小连通块中所有边权之和 $sum$，那答案就是 $2 \times sum - dis(s,t)$。

当 $s$ 到 $t$ 的简单路径不在包含所有关键点的最小连通块上时，和特殊性质 A 的做法一样，也是简单路径走一遍，除这个简单路径外这个连通块的其他边走两遍。


求出这个连通块后，可以再一次在 DFS 求出任意点距离这个连通块中最近的点和到这个连通块最小距离，设 $s$ 到这个连通块的最近点为 $x$，$t$ 到这个连通块的最近点为 $y$ ，那答案就是 $dis(s,x) + dis(t,y) + 2 \times sum - dis(x,y)$。

时间复杂度 $O(n + q \log n)$。

### 代码 ###

```cpp
const int N = 1e5 + 5; 
struct node{
	int to, val;
};
vector <node> T[N];
int n, q, k;
int key[N];
int sk[N]; // 子树 x 中的关键点个数，当他的一个儿子 v 中有关键点且子树 v 外还有关键点时，那 x 一定在这个连通块上 
int is[N]; // x 是不是包含所有关键点的最小连通块上的点 
int fa[N], siz[N], dep[N], son[N], top[N];
int ds[N];
int tos[N];// x 距离这个连通块中最近的点 
int dis[N];// x 到这个连通块最小距离 
int sum;

void dfs1(int u, int f){
	siz[u] = 1;
	dep[u] = dep[f] + 1;
	fa[u] = f;
	for(int i = 0; i < (int)T[u].size(); i ++){
		int v = T[u][i].to, w = T[u][i].val;
		if(v == f) continue;
		ds[v] = ds[u] + w;
		dfs1(v, u);
		sk[u] += sk[v];
		if(sk[v] && k - sk[v] > 0) is[u] = 1; //判断这个点是否在包含所有关键点的最小连通块上 
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v]) son[u] = v;
	}
}

void dfs2(int u, int tp){
	top[u] = tp;
	if(!son[u]) return ;
	dfs2(son[u], tp);
	for(int i = 0; i < (int)T[u].size(); i ++){
		int v = T[u][i].to;
		if(v == fa[u] || son[u] == v) continue;
		dfs2(v, v);
	}
}

void dfs(int u, int fa, int nw, int dist){
	tos[u] = nw;
	dis[u] = dist; 
	for(int i = 0; i < (int)T[u].size(); i ++){
		int v = T[u][i].to, w = T[u][i].val;
		if(v == fa) continue;
		if(is[v]) sum += w, dfs(v, u, v, dist);
		else dfs(v, u, nw, dist + w);
	}
}

int lca(int u, int v){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	return v;
}

int query(int u, int v){
	int ans = ds[tos[u]] + ds[tos[v]] - 2 * ds[lca(tos[u], tos[v])];
	return 2 * sum - ans + dis[u] + dis[v];
}

signed main(){
	rd(n), rd(q), rd(k);
	for(int i = 1; i < n; i ++){
		int u, v, w;
		rd(u), rd(v), rd(w);
		T[u].PB({v, w});
		T[v].PB({u, w});
	}
	for(int i = 1; i <= k; i ++) rd(key[i]), is[key[i]] = 1, sk[key[i]] = 1;
	dfs1(1, 1);
	dfs2(1, 1); 
	dfs(key[1], 0, key[1], 0);
	for(int i = 1; i <= q; i ++){
		int u, v;
		rd(u), rd(v);
		wrt(query(u, v), "\n");
	} 
	return 0;
}
```

---

## 作者：AMlhd (赞：0)

## 题目概要

题目给定一棵带权树，其中有 $k$ 个关键节点。对于每个查询 $(s, t)$，要求求出从 $s$ 到 $t$ 的最短路径长度，且该路径必须经过所有关键节点至少一次。

## 解题思路

1. **预处理**\
   利用 DFS 遍历整棵树，计算每个节点：
   - 到根的距离 $dis_{\cdot}$，
   - 节点深度 $dep_{\cdot}$，
   - 利用倍增方法构造 LCA 数组。

2. **利用 LCA 求两点间距离**\
   对于树中任意两点 $x$ 和 $y$，它们的最短路径必定经过它们的最近公共祖先 $\operatorname{LCA}(x,y)$。设：

   - $dis_{x}$ 为从根到 $x$ 的距离，
   - $dis_{y}$ 为从根到 $y$ 的距离，
   - $dis_{ \operatorname{LCA}(x,y)}$ 为从根到最近公共祖先的距离。

   则从 $x$ 到 $y$ 的距离为：

   $$
   dist(x,y)=dis_{x}+dis_{y}-2\times dis_{ \operatorname{LCA}(x,y)}
   $$

   **解释**：\
   从 $x$ 到 $\operatorname{LCA}(x,y)$ 的距离为 $dis_{x}-dis_{ \operatorname{LCA}(x,y)}$，从 $y$ 到 $\operatorname{LCA}(x,y)$ 的距离为 $dis_{y}-dis_{ \operatorname{LCA}(x,y)}$。两部分相加后，再去掉公共部分 $2\times dis_{ \operatorname{LCA}(x,y)}$，就得到了正确的两点间距离。

3. **查询求解**\
   在预处理过程中还可能累加了关键节点之间的路径总和（记为 $tot$）。对于每次查询，通过一定的函数（如 $f(s)$）找到查询点附近的关键节点，再结合上面的距离公式计算出最终答案。

## 代码

~~当然我坚信你们最爱看这个~~

```cpp
#include <bits/stdc++.h>

#define N 500010
#define ll long long
#define ls (p << 1)
#define rs (p << 1 | 1)
#define mid ((l + r) >> 1)

using namespace std;

int n, k, q;
int nxt[N], head[N], to[N], w[N], e = 0;
int siz[N]; 
int dis[N]; 
bool kk[N];
bool iff[N]; 
int dep[N];
int lca[N][31];
int lg[N];
int r;
int tot;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

inline void write(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

inline void writeln(int x) {
    write(x);
    putchar('\n');
}

inline void add_edge(int u, int v, int c) {
    to[++e] = v;
    w[e] = c;
    nxt[e] = head[u];
    head[u] = e;
}

inline void dfs(int p, int pre) {
    dep[p] = dep[pre] + 1;
    lca[p][0] = pre;
    if(kk[p]) {
        siz[p] = 1;
    }
    for(int i = 1; i <= lg[dep[p]]; ++i) {
        lca[p][i] = lca[lca[p][i - 1]][i - 1];
    }
    for(int i = head[p]; i; i = nxt[i]) {
        if(to[i] == pre) {
            continue;
        }
        dis[to[i]] = dis[p] + w[i];
        dfs(to[i], p);
        siz[p] += siz[to[i]];
        if(siz[to[i]] > 0) {
            tot += w[i];
        }
    }
}

inline int f(int p) {
    if(iff[p]) return p;
    for(int i = lg[dep[p]]; i >= 0; --i) {
        if(lca[p][i] && !iff[lca[p][i]])
            p = lca[p][i];
    }
    return lca[p][0];
}

inline int fa(int x, int y) {
    if(dep[x] > dep[y]) {
        swap(x, y);
    }
    for(int i = lg[dep[y]]; i >= 0; --i) {
        if(dep[lca[y][i]] >= dep[x]) {
            y = lca[y][i];
        }
    }
    if(x == y) {
        return x;
    }
    for(int i = lg[dep[x]]; i >= 0; --i) {
        if(lca[x][i] != lca[y][i]) {
            x = lca[x][i];
            y = lca[y][i];
        }
    }
    return lca[x][0];
}

inline int dist(int x, int y) {
    return dis[x] + dis[y] - 2 * dis[fa(x, y)];
}

inline void tag() {
    for(int i = 1; i <= n; ++i) {
        if(siz[i]) {
            iff[i] = 1;
        }
    }
}

int main() {
    n = read();
    q = read();
    k = read();
    
    for(int i = 1; i <= n; ++i) {
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
    }
    
    for(int i = 1; i <= n - 1; ++i) {
        int u, v, c;
        u = read();
        v = read();
        c = read();
        add_edge(u, v, c);
        add_edge(v, u, c);
    }
    
    for(int i = 1; i <= k; ++i) {
        int p = read();
        kk[p] = 1;
        r = p;
    }
    
    dep[0] = 0;
    dfs(r, 0);
    tag();
    
    while(q--) {
        int s, t;
        s = read();
        t = read();
        int x = f(s), y = f(t);
        int ans = dist(s, x) + dist(y, t) + 2 * tot - dist(x, y);
        writeln(ans);
    }
    
    return 0;
}
```

---

## 作者：naroto2022 (赞：0)

# P9433 题解

### 题面

[原题传送门](luogu.com.cn/problem/P9433)

### 思路

![](https://cdn.luogu.com.cn/upload/image_hosting/p6ynixib.png)

任取一个关键点作为根，这样，关键点就构成了一个包含根节点的连通块。如图中的黑色 (关键点) 和灰色部分所示。

由于关键点连通块的根就是树根，$s$（或 $t$）一定存在一个祖先 $s'$，使得 $s'$ 以上的结点都在连通块内，而 $s'$ 以下（不含 $s'$）到 $s$ 的结点都不在连通块内。我们预处理出每个结点在不在关键点连通块，然后利用倍增数组向上跳跃，就能求出 $s'$ 和 $t'$，如下图红色部分。

所以答案就为 $2w-\operatorname{dis}(s',t')+\operatorname{dis}(s,s')+\operatorname{dis}(t,t')$。

其中，$w$ 为联通快内所有边权和。减去 $\operatorname{dis}(s',t')$ 是因为 $s'$ 到 $t'$ 不用多算一遍。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define gc()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#define ll long long
using namespace std;
const int MN=1e5+5;
ll n,q,k,x,sum[MN],sz[MN],deep[MN],head[MN],tot,fa[MN][20],cnt;
bool flag[MN],vis[MN];
char buf[1<<23],*p1=buf,*p2=buf;
struct edge{ll to,nxt,w;}e[MN<<1];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=gc();}return x*f;}
void add(ll u, ll v, ll w){e[++tot].nxt=head[u];head[u]=tot;e[tot].to=v;e[tot].w=w;}
void lca_dfs(ll u, ll lst){
    deep[u]=deep[lst]+1;fa[u][0]=lst;
    if(flag[u]) sz[u]=1;
    for(int i=1; i<20; i++) fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=head[u]; i; i=e[i].nxt){
        ll v=e[i].to,w=e[i].w;
        if(v==lst) continue;
        sum[v]=sum[u]+w;
        lca_dfs(v,u);
        sz[u]+=sz[v];
    }
}
ll lca(ll x, ll y){
    if(deep[x]<deep[y]) swap(x,y);
    for(int i=19; ~i; i--) if(deep[x]-(1<<i)>=deep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=19; ~i; i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void dfs(ll u, ll lst){
    if(!sz[u]) return;
    vis[u]=true;
    for(int i=head[u]; i; i=e[i].nxt){
        ll v=e[i].to,w=e[i].w;
        if(v==lst) continue;
        dfs(v,u);
        if(vis[u]&&vis[v]) cnt+=w;
    }
}
ll dist(ll u, ll v){return sum[u]+sum[v]-sum[lca(u,v)]*2;}
ll getrt(ll u){
    if(vis[u]) return u;
    for(int i=19; ~i; i--) if(fa[u][i]&&!vis[fa[u][i]]) u=fa[u][i];
    return fa[u][0];
}
int main(){
    //ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    n=read();q=read();k=read();
    for(int i=1; i<n; i++){
        ll u=read(),v=read(),w=read();
        add(u,v,w);add(v,u,w);
    }
    for(int i=1; i<=k; i++){x=read();flag[x]=true;}
    lca_dfs(x,0);dfs(x,0);
    while(q--){
        ll s=read(),t=read(),fs=getrt(s),ft=getrt(t);
        write(2*cnt-dist(fs,ft)+dist(s,fs)+dist(t,ft));putchar('\n');
    }
    return 0;
}//250316
```

---

