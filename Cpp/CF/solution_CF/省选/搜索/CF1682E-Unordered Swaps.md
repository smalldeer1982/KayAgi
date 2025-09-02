# Unordered Swaps

## 题目描述

Alice had a permutation $ p $ of numbers from $ 1 $ to $ n $ . Alice can swap a pair $ (x, y) $ which means swapping elements at positions $ x $ and $ y $ in $ p $ (i.e. swap $ p_x $ and $ p_y $ ). Alice recently learned her first sorting algorithm, so she decided to sort her permutation in the minimum number of swaps possible. She wrote down all the swaps in the order in which she performed them to sort the permutation on a piece of paper.

For example,

- $ [(2, 3), (1, 3)] $ is a valid swap sequence by Alice for permutation $ p = [3, 1, 2] $ whereas $ [(1, 3), (2, 3)] $ is not because it doesn't sort the permutation. Note that we cannot sort the permutation in less than $ 2 $ swaps.
- $ [(1, 2), (2, 3), (2, 4), (2, 3)] $ cannot be a sequence of swaps by Alice for $ p = [2, 1, 4, 3] $ even if it sorts the permutation because $ p $ can be sorted in $ 2 $ swaps, for example using the sequence $ [(4, 3), (1, 2)] $ .

Unfortunately, Bob shuffled the sequence of swaps written by Alice.

You are given Alice's permutation $ p $ and the swaps performed by Alice in arbitrary order. Can you restore the correct sequence of swaps that sorts the permutation $ p $ ? Since Alice wrote correct swaps before Bob shuffled them up, it is guaranteed that there exists some order of swaps that sorts the permutation.

## 说明/提示

In the first example, $ p = [2, 3, 4, 1] $ , $ m = 3 $ and given swaps are $ [(1, 4), (2, 1), (1, 3)] $ .

There is only one correct order of swaps i.e $ [2, 3, 1] $ .

1. First we perform the swap $ 2 $ from the input i.e $ (2, 1) $ , $ p $ becomes $ [3, 2, 4, 1] $ .
2. Then we perform the swap $ 3 $ from the input i.e $ (1, 3) $ , $ p $ becomes $ [4, 2, 3, 1] $ .
3. Finally we perform the swap $ 1 $ from the input i.e $ (1, 4) $ and $ p $ becomes $ [1, 2, 3, 4] $ which is sorted.

In the second example, $ p = [6, 5, 1, 3, 2, 4] $ , $ m = 4 $ and the given swaps are $ [(3, 1), (2, 5), (6, 3), (6, 4)] $ .

One possible correct order of swaps is $ [4, 2, 1, 3] $ .

1. Perform the swap $ 4 $ from the input i.e $ (6, 4) $ , $ p $ becomes $ [6, 5, 1, 4, 2, 3] $ .
2. Perform the swap $ 2 $ from the input i.e $ (2, 5) $ , $ p $ becomes $ [6, 2, 1, 4, 5, 3] $ .
3. Perform the swap $ 1 $ from the input i.e $ (3, 1) $ , $ p $ becomes $ [1, 2, 6, 4, 5, 3] $ .
4. Perform the swap $ 3 $ from the input i.e $ (6, 3) $ and $ p $ becomes $ [1, 2, 3, 4, 5, 6] $ which is sorted.

There can be other possible answers such as $ [1, 2, 4, 3] $ .

## 样例 #1

### 输入

```
4 3
2 3 4 1
1 4
2 1
1 3```

### 输出

```
2 3 1```

## 样例 #2

### 输入

```
6 4
6 5 1 3 2 4
3 1
2 5
6 3
6 4```

### 输出

```
4 1 3 2```

# 题解

## 作者：I_am_Accepted (赞：10)

### Analysis

**注意：** 这篇文章可能略长，但是大多是推论及证明，最终实现不难。

首先，设置换环的个数为 $c$，则 Alice 的最小交换次数为 $n-c$，证明略。

进一步地，Alice 不会 swap 两个不同置换环上的元素。

所以，我们可以将每一个置换环分开求解。设当前枚举到的环长为 $L$，则 Alice 在这里 swap 了 $L-1$ 次，若将 swap(x,y) 变为 $x,y$ 节点之间的无向边，则构成一棵树。

所以问题被我们转化为：

**给定一棵树，点编号 $1\to L$，点上有点权（记为 $a_i$），值域是 $1\to n$ 且互不相同。每次操作可以删掉一条边，并将两端的点权交换。求一个操作的顺序，使得最后每个点的点权等于点编号。**

这个问题可以 $O(L\log L)$ 实现。

#### （一）

将这颗树**随意定根**，求出每个点的**深度**，$O(L\log L)$ **预处理树上倍增**。

这样我们就可以 $O(\log L)$ 实现两种操作：

1. 判断一个点 $x$ 是否在另一个点 $y$ 的子树里。

2. 若 1. 满足，求出 $x$ 在 $y$ 的哪个儿子的子树中。

#### （二）

我们称一条边 $(x,y)$（不妨设 $x$ 是 $y$ 的父亲）「濒死」的当且仅当节点 $a_x$ 在 $y$ 的子树内且 $a_y$ 不在 $y$ 的子树内。

* * *

**引理 A：** 一条「濒死」应当尽可能操作掉。

**证明：**

因为 $a_x$ 要到 $y$ 那头，并且 $a_y$ 要到 $x$ 那头，既然两边都准备好了，那还等啥。

**引理 B：** 在任一时刻，两条「濒死」边不可能用公共顶点。

**证明：**

反证法，设存在 $(x,y),(y,z)$ 均为「濒死」边。

则 $a_y$ 既要在 $x$ 那头，又要在 $z$ 那头~~很蓝的啦~~，所以矛盾，原命题成立。

* * *

由引理 A，**遍历每一条边，若这条边「濒死」则加入队列。**

**然后依次将队列中的边操作掉，然后判断与这条边有公共顶点的边是否「濒死」，若是则加入队列。**

由引理 B，在队列中的「濒死」边不可能变回「不濒死」的。并且 Alice 给的一定合法，所以证明了正确性。

算法总时间 $O(n\log n)$。

### Code

没有压行，略显冗长。

```cpp
//Said no more counting dollars. We'll be counting stars.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define For(i,j,k) for(int i=j;i<=k;i++)
#define N 200010
#define C 17
int n,m,a[N],f[N][C+1],id[N],dep[N];
vector<pair<int,int> > e[N];
pair<int,int> g[N];
queue<int> q;
bool vis[N];
void dfs(int rt,int fa){
	dep[rt]=dep[fa]+1;
	f[rt][0]=fa; For(i,1,C) f[rt][i]=f[f[rt][i-1]][i-1];
	vis[rt]=1;
	for(auto i:e[rt]) if(i.fir!=fa) id[i.fir]=i.sec,dfs(i.fir,rt);
}
inline int up(int x,int y){//return the root of subtree of y that contains x
	int z=dep[x]-dep[y]-1;
	For(i,0,C) if(z&(1<<i)) x=f[x][i];
	return x;
}
inline bool pan(int x,int y){//Is x in the subtree rooted y?
	int z=dep[x]-dep[y];
	if(z<0) return false;
	For(i,0,C) if(z&(1<<i)) x=f[x][i];
	return x==y;
}
void dfs2(int rt,int fa){
	for(auto i:e[rt]) if(i.fir!=fa){
		if(pan(a[rt],i.fir) && !pan(a[i.fir],i.fir)) q.push(i.sec);
		dfs2(i.fir,rt);
	}
}
void check(int x){//return a[x] home
	if(a[x]==x) return ;
	if(pan(a[x],x)){
		int y=up(a[x],x);
		if(!pan(a[y],y)) q.push(id[y]);
	}else if(f[x][0]!=0){
		if(pan(a[f[x][0]],x)) q.push(id[x]);
	}
}
void work(int x){
	dfs(x,0);dfs2(x,0);
	while(!q.empty()){
		x=q.front();q.pop();
		cout<<x<<" ";
		swap(a[g[x].fir],a[g[x].sec]);
		check(g[x].fir);check(g[x].sec); 
	} 
}
signed main(){IOS;
	cin>>n>>m;
	For(i,1,n) cin>>a[i]; 
	int x,y;
	For(i,1,m){
		cin>>x>>y;
		e[x].pb(mkp(y,i));
		e[y].pb(mkp(x,i));
		g[i]=mkp(x,y);
	}
	For(i,1,n) if(!vis[i]) work(i);
return 0;}
```

---

## 作者：jrxxx (赞：7)

[link](https://www.luogu.com.cn/problem/CF1682E)

跟其他几篇题解不太一样。

# 思路

## $\text{Step 1}$

对于一个排列 $p$，将 $i$ 向 $p_i$ 连边后可以得到一张由简单环和自环组成的有向图（**以下提到的环都包括自环**）（若此处连边反着连，后续讨论也要反过来）。

结论：假如图上共有 $c$ 个环，那么将 $p$ 还原的最小操作次数为 $n-c$。

为什么呢？

设图上环的数量为 $\phi$，初始时 $\phi=c$，目标状态是 $\phi=n$（$\forall i,p_i=i$，有 $n$ 个自环）。

- 交换同一个简单环内两数，会把这个环断开重连为两个小环，$\phi$ 增加 $1$（当 $\phi<n$ 时一定能找到简单环）。
- 交换不同环的两数，会把这两个环打通成一个大环，$\phi$ 减少 $1$。

最优方案显然是一直让 $\phi$ 增加 $1$，直到 $\phi=n$ 结束。
也就是说，需要保证每一次交换都发生在同一个环内。

## $\text{Step 2}$

考虑将这 $m$ 次交换作为无向边加入到之前的有向图上，那么这些边初始时不可能跨环（两端点在不同环内），否则一定无解。

假设存在两条边 $A,B$，进行 $A$ 的交换后会导致 $B$ 跨环，考虑 $A$ 和 $B$ 的位置关系：

- 若 $A$ 和 $B$ 不在同一环内，它们不会互相影响。
- 若 $A$ 和 $B$ 完全无交（在边上和顶点上都无交），它们不会互相影响。
- 若 $A$ 和 $B$ 在边上相交，无论先做 $A$ 再做 $B$ 还是先做 $B$ 再做 $A$，都会导致后做的跨环，一定无解，所以不存在这种情况，也不用讨论。

还剩下一种情况：$A$ 和 $B$ 共顶点。

读者可以自己手玩一下题目中的两个样例（其实是我太懒了不想画图），然后就会发现：对于这种情况，需要**顺着环旋转的方向**做交换，才能保证不跨环。

于是，再建一个以 $m$ 条交换边作为顶点的新有向图记录这些"共顶点时顺着环旋转的方向做交换"的先后关系。最后拓扑排序一下，输出任意一个拓扑序即可。

复杂度 $O(n\log n)$，瓶颈在按旋转方向将边排序。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+7;
int to[N],rk[N],in[N],len[N],cir_cnt,deg[N],n,m,q[N];
vector<pii> G[N];//加入的无向交换边
vector<int> g[N];//新图
int main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	int i,j,k,x,y;
	memset(rk,-1,sizeof rk); 
	cin>>n>>m;
	for(i=1;i<=n;++i) cin>>to[i];//to存储原有向图
	for(i=1;i<=m;++i) cin>>x>>y,G[x].emplace_back(y,i),G[y].emplace_back(x,i);
	//找环
	for(i=1;i<=n;++i)if(rk[i]==-1)
	{
		rk[i]=0,in[i]=++cir_cnt;//rk-环上的排名
		for(j=to[i],k=1;j!=i;j=to[j],++k) rk[j]=k,in[j]=cir_cnt;
		len[cir_cnt]=k;//环长
	}
	//排序 建新图
	for(i=1;i<=n;++i)
	{
		int L=len[in[i]],ri=rk[i];
		sort(G[i].begin(),G[i].end(),[&](pii x,pii y)
		{
			int rx=rk[x.first]<=ri?rk[x.first]+L:rk[x.first];
			int ry=rk[y.first]<=ri?rk[y.first]+L:rk[y.first];
			return rx<ry;
		});
		for(j=1;j<(int)G[i].size();++j)
			g[G[i][j-1].second].push_back(G[i][j].second),++deg[G[i][j].second];
	}
	//拓扑排序
	int hd=1,tl=0,u;
	for(i=1;i<=m;++i)if(deg[i]==0)q[++tl]=i;
	while(hd<=tl)
	{
		u=q[hd++],cout<<u<<' ';
		for(int v:g[u])if(!--deg[v])q[++tl]=v;
	}
	return 0;
}

```

---

## 作者：lingfunny (赞：4)

# 793div2 E

可上 CF 看[本题解](https://codeforces.com/blog/entry/103097?#comment-914934)。

建模不多说，你会把排列拆成若干个轮换，然后对于长为 $k$ 的轮换，会且仅会用 $k-1$ 次交换（因为题目保证用的次数是最少的）。

把这些交换抓出来建图，会得到一个森林，你需要给每条边定向，使得每棵树的拓扑序都可以和原轮换循环同构。

考虑如果满足一个 $i\to p_i$ 的置换，那么你操作的顺序一定是在树上从 $i$ 开始走然后走到 $p_i$，这样的路径是唯一的。设经过了 $m$ 条边分别是 $e_1,e_2,\cdots,e_m$，这 $m$ 条边会有严格拓扑序 $\mathrm{opt}_{e_1}<\mathrm{opt}_{e_2}<\cdots<\mathrm{opt}_{e_m}$。

而这 $m$ 条边有这些拓扑序恰是满足 $i\to p_i$ 置换的充要条件。

充分：按这个拓扑序 $i$ 可以走到 $p_i$。

必要：树上路径唯一。

所以对于每个 $i\to p_i$，在树上抓出这些路径然后加上有向边，最后拓扑排序即可。

这样做是对的，因为一条边是交换两个数字，最多只会影响两个置换，所以会且恰好会被两条路径覆盖。

总时间复杂度是 $O(n)$ 的。

关于怎么抓出路径，无根转有根后暴力跳 $\mathrm{lca}$ 即可。

贴个代码~~以免有人说我在口胡~~：

```cpp
// Problem: E. Unordered Swaps
// From: Codeforces - Codeforces Round #793 (Div. 2)
// URL: https://codeforces.com/contest/1682/problem/E
// Time: 2022-05-22 22:36
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 2e5+10;

int n, m, a[mxn], p[mxn], dep[mxn], in[mxn];

typedef pair<int, int> edge;
vector <edge> G[mxn];
edge fa[mxn];
vector <int> nodes, g[mxn];

inline void adde(int u, int v) { ++in[v]; g[u].push_back(v); }

void dfs(int u, int f) {
	dep[u] = dep[f] + 1; nodes.push_back(u);
	for(auto [id, v]: G[u]) if(v != f) fa[v] = {id, u}, dfs(v, u);
}

inline void solve(int u) {
	vector <int>().swap(nodes);
	dfs(u, 0);
	for(int x: nodes) {
		int y = p[x];	// x -> y
		vector <int> fx, fy;
		while(dep[x] > dep[y]) fx.push_back(fa[x].first), x = fa[x].second;
		while(dep[y] > dep[x]) fy.push_back(fa[y].first), y = fa[y].second;
		while(x != y) {
			fx.push_back(fa[x].first), x = fa[x].second;
			fy.push_back(fa[y].first), y = fa[y].second;
		}
		reverse(fy.begin(), fy.end());
		fx.insert(fx.end(), fy.begin(), fy.end());
		for(int i = 1; i < (int)fx.size(); ++i)
		adde(fx[i-1], fx[i]);
	}
}

signed main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%d", p+i);
	for(int i = 1; i <= m; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		G[x].push_back({i, y});
		G[y].push_back({i, x});
	}
	for(int i = 1; i <= n; ++i) if(!dep[i]) solve(i);
	queue <int> q;
	for(int i = 1; i <= m; ++i) if(!in[i]) q.push(i);
	while(q.size()) {
		int u = q.front(); q.pop();
		printf("%d ", u);
		for(int v: g[u]) if(--in[v] == 0) q.push(v);
	}
	return 0;
}
```



---

## 作者：_Cheems (赞：0)

题意：给定排列 $p_1\dots p_n$ 与操作集合 $(x_1,y_1)\dots (x_m,y_m)$，找出一种操作顺序，满足按顺序交换 $p_x,p_y$ 最终排列升序。保证一定有解，且 $m$ 是交换任意两元素使得排列升序的最小次数。$m<n\le 2\times 10^5$。

$i\to p_i$ 建出置换环，交换 $p_x,p_y$ 等价于交换 $x,y$ 出边。由于次数最小，所以每次操作时 $x,y$ 不可能在两个不同的环上。

再次建图，$x_i,y_i$ 连一条无向边，容易发现不存在环，因为有环的话必然存在一个操作交换两个不同环。所以得到是森林。

那么问题转化为：一棵树带点权，按顺序对边操作交换两端点权，最终点权等于点编号。

考虑 $i\to p_i$ 路径，要将 $i$ 上的点权运向 $p_i$，那么路径上的边操作顺序严格递增。想到将边视为点建有向图，跑一边拓扑排序。

但是会不会出现点权 $p_i$ 在运输时被路径外的交换操作给交换走了呢？实际上是不会的。

证明：考察路径上相邻两条边 $u\to v$ 和 $v\to w$ 称为 $x_1,x_2$，记 $t_x$ 为 $x$ 操作顺序。由于 $i\to p_i$ 构成简单环，尝试观察该环在树上的形态，首先两条方向相反的链不能有 $\ge 2$ 的相交部分否则非法，那么拎起 $i\to p_i$ 路径挂着一些子树。从 $i$ 跳到 $p_i$ 后，遍历 $p_i$ 子树，然后跳到 $p_i$ 路径前一位的子树，以此类推子树倒序遍历。对于 $v$ 子树的遍历，一定是后面跳到 $v$ 的某一个子树，然后再从该子树开始依次遍历 $v$ 的其它子树，最终跳向 $u$ 子树。此过程中，$v$ 的相邻边 $y_1\dots y_q$ 被依次跨越，最终从 $y_q$ 跨越到 $x_1$，所以有 $t_{y_1}<t_{y_2}\dots t_{y_q}<x_1<x_2$，因此不可能出现上述情况。

于是暴力建图跑拓扑序即可，同时由上述证明知一条边恰被两条链覆盖，所以是 $O(n)$ 的。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define pir pair<int, int>
const int N = 2e5 + 5;
int n, m, x, y, p[N], d[N], fa[N], faw[N], in[N];
vector<pir> to[N];
vector<int> to2[N];

inline void dfs(int u, int from){
	d[u] = d[from] + 1;
	for(auto _ : to[u]){
		int v = _.first;
		if(v ^ from) fa[v] = u, faw[v] = _.second, dfs(v, u);
	}
}
inline void dist(int s, int t){
	vector<int> l0, l1;
	if(d[s] < d[t]) while(d[s] < d[t]) l1.push_back(faw[t]), t = fa[t];
	if(d[s] > d[t]) while(d[s] > d[t]) l0.push_back(faw[s]), s = fa[s];
	while(s ^ t) l0.push_back(faw[s]), l1.push_back(faw[t]), s = fa[s], t = fa[t];
	int s0 = l0.size(), s1 = l1.size();
	for(int i = 0; i < s0 - 1; ++i) to2[l0[i]].push_back(l0[i + 1]);
	if(!l1.empty()){
		reverse(l1.begin(), l1.end());
		if(!l0.empty()) to2[l0[s0 - 1]].push_back(l1[0]);
		for(int i = 0; i < s1 - 1; ++i) to2[l1[i]].push_back(l1[i + 1]);
	}
}
inline void topo(){
	for(int i = 1; i <= m; ++i) 
		for(auto j : to2[i]) ++in[j];
	queue<int> q;
	for(int i = 1; i <= m; ++i)
		if(!in[i]) q.push(i);
	while(!q.empty()){
		int u = q.front(); q.pop();
		printf("%d ", u);
		for(auto v : to2[u])
			if(!(--in[v])) q.push(v);
	}
}
signed main(){
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) scanf("%d", &p[i]);
	for(int i = 1; i <= m; ++i) scanf("%d%d", &x, &y), to[x].push_back({y, i}), to[y].push_back({x, i});
	for(int i = 1; i <= n; ++i) if(!d[i]) dfs(i, 0);
	for(int i = 1; i <= n; ++i) dist(i, p[i]);
	topo();
	return 0;
}

```

---

## 作者：daniEl_lElE (赞：0)

对于一个大小为 $x$ 的置换环，显然可以 $x-1$ 次操作完成。

由于只有 $n-1$ 次操作，置换环无法分成两组可以内部交换的部分，于是形成一棵树。

对于这棵树，考虑每一条边的两边的子树分别缺了哪个，多了哪个。当这条边两边互相有对方缺的时，就可以交换了（显然也应该交换了，否则这条边将无意义）。

建出这个，然后使用类拓扑排序的方法，每次一个位置变成一个新的就去更新对应需要的边（如果这个位置已经满足要求了就忽略）。由于题目保证有解，不必再判断无法复原的情况。总复杂度 $O(n)$，可以通过。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
#define lowbit(i) (i&(-i))
using namespace std;
vector<int> vc[1000005];
int p[1000005];
map<int,int> vv[1000005];
int pos[2][1000005],npos[2][1000005],k,cnt[1000005];
int vis[1000005],lfta[1000005],lftb[1000005];
int tag[1000005];
map<pair<int,int>,int> mp;
void dfs(int now,int fa){
	vis[now]=1;
	vector<int> tmp1,tmp2;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
	}
	for(auto v:vc[now]){
		if(v==fa) continue;
		tag[lfta[v]]++;
		tag[lftb[v]]--;
		tmp1.push_back(lfta[v]);
		tmp2.push_back(lftb[v]);
	} 
	tag[now]++;
	tag[p[now]]--;
	tmp1.push_back(now);
	tmp2.push_back(p[now]);
	for(auto v:tmp1) if(tag[v]==1) lfta[now]=v,tag[v]=0;
	for(auto v:tmp2) if(tag[v]==-1) lftb[now]=v,tag[v]=0;
	if(fa!=0){
		k++;
		pos[0][k]=fa,pos[1][k]=now;
		npos[0][k]=lfta[now],npos[1][k]=lftb[now];
		vv[fa][lfta[now]]=k,vv[now][lftb[now]]=k;
		cnt[k]=2;
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>p[i];
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
		mp[make_pair(u,v)]=mp[make_pair(v,u)]=i;
	}
	for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);
	queue<int> q;
	for(int i=1;i<=n;i++) if(p[i]!=i){
		cnt[vv[i][p[i]]]--;
		if(cnt[vv[i][p[i]]]==0) q.push(vv[i][p[i]]);
	}
	vector<int> ans;
	while(!q.empty()){
		int f=q.front(); q.pop(); ans.push_back(f);
		swap(p[pos[0][f]],p[pos[1][f]]);
		if(p[pos[0][f]]!=pos[0][f]){
			cnt[vv[pos[0][f]][p[pos[0][f]]]]--;
			if(cnt[vv[pos[0][f]][p[pos[0][f]]]]==0) q.push(vv[pos[0][f]][p[pos[0][f]]]);
		}
		if(p[pos[1][f]]!=pos[1][f]){
			cnt[vv[pos[1][f]][p[pos[1][f]]]]--;
			if(cnt[vv[pos[1][f]][p[pos[1][f]]]]==0) q.push(vv[pos[1][f]][p[pos[1][f]]]);
		}
	}
	for(auto v:ans) cout<<mp[make_pair(pos[0][v],pos[1][v])]<<" ";
	return 0;
}
```

---

## 作者：t162 (赞：0)

对于每对操作 $(x,y)$，对点 $x$ 和 点 $y$ 进行连边，最后得到的图一定是一个森林。

为什么？因为最优情况下每个操作都是在置换环内部的。而对于一个长度为 $l$ 的置换环，只需要 $l-1$ 次操作就行了，而这些操作要覆盖到置换环内部的所有点，因此对于每个置换环的操作构成了一棵树。

这样问题就变成了每次删除一条边，并交换这条边连接的两个点的权值，最终删除完所有边后要求每个点的权值等于编号。

接下来可以借鉴 CSP-S 2019 D1T3 的思路。

对于某个权值，整个操作中移动的路径就是初始位置和最终位置之间的简单路径。对于整个路径中某个点，定义 `入边` 为该权值进入这个点的边，`出边` 为该权值从这个点出发的边，特别地，对于初始位置不定义 `入边`，对于最终位置不定义 `出边`。

然后发现一个删边顺序合法，当且仅当对于某个点某个权值，若该点是该权值的初始位置，那么出边一定是所有链接该点的边中最先删除的边，若是终止位置那么入边一定最后删除，否则入边与出边的删除顺序一定连续且入边在前。

所以对于每个权值，求出其初始位置和最终位置之间的简单路径，然后对路径上的边的编号连边，最后跑拓扑就行了。

找简单路径可以直接暴力找，因为合法情况不会有任何两个路径共用一条边。

```cpp
#include<cstdio>
#include<vector>
#include<utility>
#include<queue>
int n, m, a[200005], f[200005], dep[200005], fd[200005], vis[200005], ind[200005], ans[200005], cnt;
std::vector<int> e[200005]; std::vector<std::pair<int, int>> E[200005];
void mark(int u, int v) {
	int A = 0, B = -1;
	if (dep[u] > dep[v]) {
		int lst = 0;
		while (dep[u] > dep[v]) {
			e[lst].push_back(fd[u]);
			lst = fd[u], u = f[u];
		}
		A = lst;
	} else if (dep[v] > dep[u]) {
		int lst = -1;
		while (dep[v] > dep[u]) {
			if (lst != -1) e[fd[v]].push_back(lst);
			lst = fd[v], v = f[v];
		}
		B = lst;
	}
	while (u != v) {
		e[A].push_back(fd[u]), A = fd[u], u = f[u];
		if (B != -1) e[fd[v]].push_back(B);
		B = fd[v], v = f[v];
	}
	if (B != -1) e[A].push_back(B);
}
void dfs(int u, int fa, int d) {
	f[u] = fa, fd[u] = d, vis[u] = 1;
	for (auto [v, w] : E[u]) {
		if (v == fa) continue;
		dep[v] = dep[u] + 1, dfs(v, u, w);
	}
}
std::queue<int> q;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) {
		int u, v; scanf("%d%d", &u, &v);
		E[u].emplace_back(v, i), E[v].emplace_back(u, i);
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i, 0, 0);
	for (int i = 1; i <= n; i++) {
		if (a[i] == i) continue;
		mark(i, a[i]);
	}
	for (int i = 0; i <= m; i++) {
		for (int v : e[i]) ind[v]++;
	}
	for (int i = 0; i <= m; i++) if (!ind[i]) q.push(i);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		if (u) ans[++cnt] = u;
		for (int v : e[u]) {
			ind[v]--;
			if (!ind[v]) q.push(v);
		}
	}
	for (int i = 1; i <= m; i++) printf("%d%c", ans[i], " \n"[i == m]);
}
```

---

